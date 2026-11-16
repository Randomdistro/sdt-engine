"""Nested APS14a transition models A0 through A4."""

from __future__ import annotations

import math
from dataclasses import dataclass

import numpy as np

from . import constants as K
from .angular_dynamics import AngularParameters, optimise_phases
from .dynamics import AtomicState, ModelParameters, solve_state
from .orbital_pathway import swept_occlusion, transition_path
from .state_energy import state_energy_eV
from .transitions import TransitionStates

APS14_G = 0.6433536129861085


@dataclass
class AngularPrediction:
    model: str
    energy_eV: float
    frequency_hz: float
    omega_rad_s: float
    wavelength_nm: float
    lower_state: AtomicState
    upper_state: AtomicState
    lower_energy_eV: float
    upper_energy_eV: float
    path_ratio: float
    period_ratio: float
    angular_rate_ratio: float
    delta_path_m: float
    active_swept_screening_delta: float
    companion_path_delta_m: float
    lower_phases: dict[int, float]
    upper_phases: dict[int, float]


def _swept_baseline_energy(
    state: AtomicState,
    parameters: ModelParameters,
    samples: int,
    A: int | None,
) -> tuple[float, np.ndarray]:
    path = swept_occlusion(state, parameters, samples)
    attraction = state.Z * float(np.sum(1.0 / state.radii))
    pair = 0.0
    for i, first in enumerate(state.seats):
        for j in range(i + 1, len(state.seats)):
            pair += (
                parameters.coupling(first, state.seats[j])
                * path.pair_mean_inverse_distance[i, j]
            )
    energy = -0.5 * K.ME_C2_EV * K.R_E * (attraction - pair)
    if A is not None:
        energy *= K.mu_over_me(A, state.Z)
    return energy, path.seat_screening_mean


def _movement_energy_eV(
    state: AtomicState,
    swept_screening: np.ndarray,
    A: int | None,
) -> float:
    """Movement-budget state energy after path-averaged occlusion."""
    q_path = np.clip(state.Z - swept_screening, 0.05, float(state.Z))
    depth_path = (K.ALPHA * q_path / state.n_eff) ** 2
    energy = -0.5 * K.ME_C2_EV * float(np.sum(depth_path))
    return energy if A is None else energy * K.mu_over_me(A, state.Z)


def _companion_path_delta(
    lower: AtomicState,
    upper: AtomicState,
    transition: TransitionStates,
) -> float:
    low_active = transition.lower_active_index
    high_active = transition.upper_active_index
    lower_common = {
        seat: index for index, seat in enumerate(lower.seats)
        if index != low_active
    }
    upper_common = {
        seat: index for index, seat in enumerate(upper.seats)
        if index != high_active
    }
    total = 0.0
    for seat in lower_common.keys() & upper_common.keys():
        low_length = K.TWO_PI * float(lower.radii[lower_common[seat]])
        high_length = K.TWO_PI * float(upper.radii[upper_common[seat]])
        total += high_length - low_length
    return total


def predict_transition(
    model: str,
    Z: int,
    A: int,
    transition: TransitionStates,
    eta: float = 0.0,
    rho: float = 0.0,
    samples: int = 360,
    phase_divisions: int = 12,
) -> AngularPrediction:
    baseline = ModelParameters(g_same=APS14_G, g_cross=APS14_G)
    lower_phases: dict[int, float] = {}
    upper_phases: dict[int, float] = {}
    if model in {"A0_TRANSITION_FIX", "A1_PATHWAY"}:
        lower = solve_state(Z, transition.lower, baseline)
        upper = solve_state(Z, transition.upper, baseline)
        if model == "A0_TRANSITION_FIX":
            lower_energy = state_energy_eV(lower, baseline, A)
            upper_energy = state_energy_eV(upper, baseline, A)
            lower_screen = lower.screening
            upper_screen = upper.screening
        else:
            _, lower_screen = _swept_baseline_energy(
                lower, baseline, samples, A
            )
            _, upper_screen = _swept_baseline_energy(
                upper, baseline, samples, A
            )
            lower_energy = _movement_energy_eV(lower, lower_screen, A)
            upper_energy = _movement_energy_eV(upper, upper_screen, A)
    else:
        angular_parameters = AngularParameters(
            g=APS14_G,
            eta=eta if model in {"A3_ANISOTROPIC_OCCLUSION", "A4_CORE_DEPTH"} else 0.0,
            rho=rho if model == "A4_CORE_DEPTH" else 0.0,
        )
        lower_result = optimise_phases(
            Z, transition.lower, angular_parameters, swept=True,
            divisions=phase_divisions, samples=samples, A=A,
        )
        upper_result = optimise_phases(
            Z, transition.upper, angular_parameters, swept=True,
            divisions=phase_divisions, samples=samples, A=A,
        )
        lower, upper = lower_result.state, upper_result.state
        lower_phases, upper_phases = lower_result.phases, upper_result.phases
        lower_screen = swept_occlusion(
            lower, angular_parameters.baseline(), samples
        ).seat_screening_mean
        upper_screen = swept_occlusion(
            upper, angular_parameters.baseline(), samples
        ).seat_screening_mean
        lower_energy = _movement_energy_eV(lower, lower_screen, A)
        upper_energy = _movement_energy_eV(upper, upper_screen, A)

    path = transition_path(
        lower, upper,
        transition.lower_active_index, transition.upper_active_index,
    )
    if model == "A0_TRANSITION_FIX":
        delta = upper_energy - lower_energy
    else:
        reduced_mass = K.mu_over_me(A, Z)
        lower_binding = (
            0.5 * K.ME_C2_EV
            * float(lower.depth_z[transition.lower_active_index])
            * reduced_mass
        )
        # The lower-seat movement budget is released according to the
        # fractional increase in complete orbital pathway. This is exactly the
        # Rydberg difference for one electron because L scales as n^2/Z.
        delta = lower_binding * (1.0 - 1.0 / path.path_ratio)
        if model == "A4_CORE_DEPTH":
            low_common = {
                seat: index for index, seat in enumerate(lower.seats)
                if index != transition.lower_active_index
            }
            high_common = {
                seat: index for index, seat in enumerate(upper.seats)
                if index != transition.upper_active_index
            }
            companion_depth = sum(
                float(lower.depth_z[low_common[seat]]
                      - upper.depth_z[high_common[seat]])
                for seat in low_common.keys() & high_common.keys()
            )
            delta += 0.5 * K.ME_C2_EV * reduced_mass * companion_depth
    if delta > 0 and math.isfinite(delta):
        frequency = delta * K.E_CHARGE / K.H
        omega = K.TWO_PI * frequency
        wavelength = K.C / frequency * 1e9
    else:
        frequency = omega = wavelength = math.nan
    return AngularPrediction(
        model, delta, frequency, omega, wavelength,
        lower, upper, lower_energy, upper_energy,
        path.path_ratio, path.period_ratio, path.angular_rate_ratio,
        path.delta_length_m,
        float(upper_screen[transition.upper_active_index]
              - lower_screen[transition.lower_active_index]),
        _companion_path_delta(lower, upper, transition),
        lower_phases, upper_phases,
    )
