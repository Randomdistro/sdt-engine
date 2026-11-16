"""Coupled occlusion / Keplerian seat solver."""

from __future__ import annotations

from dataclasses import dataclass

import numpy as np

from . import constants as K
from .configurations import SeatLabel
from .geometry import pair_distances, positions, seat_directions


@dataclass(frozen=True)
class ModelParameters:
    g_same: float = 0.0
    g_cross: float = 0.0
    delta_s: float = 0.0
    delta_p: float = 0.0
    delta_d: float = 0.0

    def delta(self, kind: str) -> float:
        return {"s": self.delta_s, "p": self.delta_p,
                "d": self.delta_d, "f": self.delta_d}[kind]

    def coupling(self, first: SeatLabel, second: SeatLabel) -> float:
        return self.g_same if first.n == second.n else self.g_cross

    def as_tuple(self) -> tuple[float, float, float, float, float]:
        return (self.g_same, self.g_cross, self.delta_s,
                self.delta_p, self.delta_d)


@dataclass
class AtomicState:
    Z: int
    seats: list[SeatLabel]
    directions: np.ndarray
    radii: np.ndarray
    velocities: np.ndarray
    k_ratio: np.ndarray
    depth_z: np.ndarray
    koppa_felt: np.ndarray
    q_effective: np.ndarray
    screening: np.ndarray
    force_nuclear: np.ndarray
    force_pair_radial: np.ndarray
    force_residual: np.ndarray
    stiffness: np.ndarray
    n_eff: np.ndarray
    converged: bool
    iterations: int
    physical: bool
    shell_order_ok: bool


def _coupling_matrix(seats: list[SeatLabel],
                     parameters: ModelParameters) -> np.ndarray:
    n_vals = np.array([seat.n for seat in seats], dtype=int)
    same = n_vals[:, None] == n_vals[None, :]
    gmat = np.where(same, parameters.g_same, parameters.g_cross).astype(float)
    np.fill_diagonal(gmat, 0.0)
    return gmat


def _shell_order_ok(seats: list[SeatLabel], radii: np.ndarray) -> bool:
    by_n: dict[int, list[float]] = {}
    for seat, radius in zip(seats, radii):
        by_n.setdefault(seat.n, []).append(float(radius))
    means = [float(np.mean(by_n[n])) for n in sorted(by_n)]
    return all(means[i] <= means[i + 1] * 1.05 for i in range(len(means) - 1))


def solve_state(
    Z: int,
    seats: list[SeatLabel],
    parameters: ModelParameters,
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

    n_eff = np.array([
        max(0.2, seat.n - parameters.delta(seat.kind)) for seat in seats
    ], dtype=float)
    gmat = _coupling_matrix(seats, parameters)
    q = np.full(len(seats), float(Z), dtype=float)
    directions = seat_directions(seats)
    screening = np.zeros(len(seats), dtype=float)
    converged = False
    iteration = 0

    for iteration in range(1, max_iterations + 1):
        radii = K.A0 * n_eff * n_eff / q
        pos = positions(radii, directions)
        delta = pos[:, None, :] - pos[None, :, :]
        dist = np.linalg.norm(delta, axis=2)
        np.fill_diagonal(dist, np.inf)
        proj = np.einsum("ijc,ic->ij", delta, directions)
        screening = np.sum(
            gmat * (radii * radii)[:, None] * proj / (dist ** 3), axis=1
        )
        q_target = np.clip(Z - screening, 0.05, float(Z))
        q_new = 0.55 * q + 0.45 * q_target
        relative = np.max(np.abs(q_new - q) / np.maximum(q, 1e-12))
        q = q_new
        if relative < tolerance:
            converged = True
            break

    radii = K.A0 * n_eff * n_eff / q
    velocities = K.ALPHA * K.C * q / n_eff
    depth_z = (velocities / K.C) ** 2
    koppa_felt = depth_z * radii
    k_ratio = K.C / np.maximum(velocities, 1e-30)
    force_nuclear = K.OCCLUSION_K * Z / (radii * radii)
    force_pair = K.OCCLUSION_K * screening / (radii * radii)
    force_net = force_nuclear - force_pair
    force_centripetal = K.M_E * velocities * velocities / radii
    residual = (force_centripetal - force_net) / force_nuclear
    stiffness = 2.0 * K.OCCLUSION_K * q / (radii ** 3)
    physical = bool(
        np.all(np.isfinite(radii))
        and np.all(depth_z < 1.0)
        and np.all(radii > koppa_felt)
        and np.all(q > 0.0)
        and converged
    )
    return AtomicState(
        Z, seats, directions, radii, velocities, k_ratio, depth_z,
        koppa_felt, q, screening, force_nuclear, force_pair, residual,
        stiffness, n_eff, converged, iteration, physical,
        _shell_order_ok(seats, radii),
    )
