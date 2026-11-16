"""Coupled APS14a solver with angular templates and swept-path energy."""

from __future__ import annotations

from dataclasses import dataclass

import numpy as np

from . import constants as K
from .angular_geometry import angular_directions, angular_pair_tensor, phase_grid
from .configurations import SeatLabel
from .dynamics import AtomicState, ModelParameters
from .orbital_pathway import swept_occlusion


@dataclass(frozen=True)
class AngularParameters:
    g: float = 0.6433536129861085
    eta: float = 0.0
    rho: float = 0.0

    def baseline(self) -> ModelParameters:
        return ModelParameters(g_same=self.g, g_cross=self.g)


@dataclass
class OptimisedAngularState:
    state: AtomicState
    phases: dict[int, float]
    energy_eV: float
    swept_energy_eV: float


def orientation_matrix(directions: np.ndarray, eta: float) -> np.ndarray:
    cosine = directions @ directions.T
    p2 = 0.5 * (3.0 * cosine * cosine - 1.0)
    factor = np.clip(1.0 + eta * p2, 0.05, 3.0)
    np.fill_diagonal(factor, 0.0)
    return factor


def core_shadow(
    seats: list[SeatLabel],
    directions: np.ndarray,
) -> np.ndarray:
    result = np.zeros(len(seats))
    for i, seat in enumerate(seats):
        for j, inner in enumerate(seats):
            if inner.n >= seat.n:
                continue
            alignment = abs(float(directions[i] @ directions[j]))
            result[i] += alignment * (inner.n / seat.n) ** 2
    return result


def solve_angular_state(
    Z: int,
    seats: list[SeatLabel],
    parameters: AngularParameters,
    phases: dict[int, float] | None = None,
    max_iterations: int = 80,
    tolerance: float = 1e-9,
) -> AtomicState:
    empty = np.array([], dtype=float)
    if not seats:
        return AtomicState(
            Z, [], np.empty((0, 3)), empty, empty, empty, empty, empty,
            empty, empty, empty, empty, empty, empty, empty, True, 0,
            True, True,
        )
    directions = angular_directions(seats, phases)
    shadow = core_shadow(seats, directions)
    delta = parameters.rho * shadow / (1.0 + shadow)
    n_eff = np.maximum(
        0.2, np.asarray([seat.n for seat in seats], dtype=float) - delta
    )
    q = np.full(len(seats), float(Z))
    shell = np.asarray([seat.n for seat in seats])
    base_g = np.where(
        shell[:, None] == shell[None, :], parameters.g, parameters.g
    )
    np.fill_diagonal(base_g, 0.0)
    orient = orientation_matrix(directions, parameters.eta)
    g_matrix = base_g * orient
    screening = np.zeros(len(seats))
    converged = False
    iteration = 0
    for iteration in range(1, max_iterations + 1):
        radii = K.A0 * n_eff * n_eff / q
        distance, projection, _ = angular_pair_tensor(radii, directions)
        screening = np.sum(
            g_matrix * radii[:, None] ** 2 * projection / distance ** 3,
            axis=1,
        )
        target = np.clip(Z - screening, 0.05, float(Z))
        updated = 0.55 * q + 0.45 * target
        relative = np.max(np.abs(updated - q) / np.maximum(q, 1e-12))
        q = updated
        if relative < tolerance:
            converged = True
            break
    radii = K.A0 * n_eff * n_eff / q
    velocities = K.ALPHA * K.C * q / n_eff
    depth = (velocities / K.C) ** 2
    koppa = depth * radii
    k_ratio = K.C / velocities
    nuclear_force = K.OCCLUSION_K * Z / radii ** 2
    pair_force = K.OCCLUSION_K * screening / radii ** 2
    residual = (
        K.M_E * velocities ** 2 / radii - (nuclear_force - pair_force)
    ) / nuclear_force
    stiffness = 2.0 * K.OCCLUSION_K * q / radii ** 3
    shell_means = {
        n: float(np.mean([radii[index] for index, seat in enumerate(seats)
                          if seat.n == n]))
        for n in sorted(set(shell))
    }
    means = list(shell_means.values())
    shell_order = all(
        means[index] <= means[index + 1] * 1.05
        for index in range(len(means) - 1)
    )
    physical = bool(
        converged and np.all(np.isfinite(radii)) and np.all(depth < 1.0)
        and np.all(radii > koppa) and np.all(q > 0.0)
    )
    return AtomicState(
        Z, seats, directions, radii, velocities, k_ratio, depth, koppa,
        q, screening, nuclear_force, pair_force, residual, stiffness,
        n_eff, converged, iteration, physical, shell_order,
    )


def angular_energy_eV(
    state: AtomicState,
    parameters: AngularParameters,
    swept: bool,
    samples: int = 360,
    A: int | None = None,
) -> float:
    if not state.seats:
        return 0.0
    attraction = state.Z * float(np.sum(1.0 / state.radii))
    orient = orientation_matrix(state.directions, parameters.eta)
    if swept:
        path = swept_occlusion(state, parameters.baseline(), samples=samples)
        inverse = path.pair_mean_inverse_distance
    else:
        distance, _, _ = angular_pair_tensor(state.radii, state.directions)
        inverse = 1.0 / distance
    pair = 0.0
    for i in range(len(state.seats)):
        for j in range(i + 1, len(state.seats)):
            pair += parameters.g * orient[i, j] * inverse[i, j]
    nuclear_z = K.R_E * (attraction - pair)
    energy = -0.5 * K.ME_C2_EV * nuclear_z
    return energy if A is None else energy * K.mu_over_me(A, state.Z)


def optimise_phases(
    Z: int,
    seats: list[SeatLabel],
    parameters: AngularParameters,
    swept: bool,
    divisions: int = 12,
    samples: int = 360,
    A: int | None = None,
) -> OptimisedAngularState:
    candidates = []
    for phases in phase_grid(seats, divisions):
        state = solve_angular_state(Z, seats, parameters, phases)
        # Phase choice uses the converged endpoint functional. Swept quadrature
        # is evaluated at higher resolution after selection, avoiding phase-grid
        # aliasing when two commensurate paths approach one another.
        energy = angular_energy_eV(state, parameters, swept=False, A=A)
        candidates.append((energy, phases, state))
    energy, phases, state = min(candidates, key=lambda item: item[0])
    swept_energy = angular_energy_eV(
        state, parameters, swept=True, samples=samples, A=A
    )
    return OptimisedAngularState(state, phases, energy, swept_energy)
