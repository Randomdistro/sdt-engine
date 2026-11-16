"""Ionisation and emitted frequency/wavelength observables."""

from __future__ import annotations

import math
from dataclasses import dataclass

from . import constants as K
from .configurations import SeatLabel, after_removals, ionisation_order, promoted
from .dynamics import AtomicState, ModelParameters, solve_state
from .state_energy import frozen_seat_binding_eV, state_energy_eV


@dataclass
class Emission:
    energy_eV: float
    frequency_hz: float
    omega_rad_s: float
    wavelength_m: float
    lower_energy_eV: float
    upper_energy_eV: float


def _from_delta(delta: float, lower: float, upper: float) -> Emission:
    if not math.isfinite(delta) or delta <= 0:
        return Emission(delta, math.nan, math.nan, math.nan, lower, upper)
    frequency = delta * K.E_CHARGE / K.H
    return Emission(
        delta, frequency, K.TWO_PI * frequency, K.C / frequency, lower, upper
    )


def ionisation_prediction(
    Z: int,
    full_seats: list[SeatLabel],
    removed_before: int,
    parameters: ModelParameters,
    relaxed: bool,
    A: int | None = None,
) -> tuple[float, AtomicState, AtomicState | None, float]:
    current_seats = after_removals(full_seats, removed_before)
    current = solve_state(Z, current_seats, parameters)
    if not current_seats:
        return math.nan, current, None, math.nan
    if relaxed:
        next_seats = after_removals(full_seats, removed_before + 1)
        following = solve_state(Z, next_seats, parameters)
        current_energy = state_energy_eV(current, parameters, A)
        next_energy = state_energy_eV(following, parameters, A)
        predicted = next_energy - current_energy
        active = ionisation_order(current_seats)[0]
        frozen = frozen_seat_binding_eV(current, active, A)
        return predicted, current, following, predicted - frozen
    active = ionisation_order(current_seats)[0]
    predicted = frozen_seat_binding_eV(current, active, A)
    return predicted, current, None, 0.0


def excitation_observables(
    Z: int,
    ground_seats: list[SeatLabel],
    parameters: ModelParameters,
    A: int | None = None,
) -> tuple[Emission, AtomicState, AtomicState]:
    lower = solve_state(Z, ground_seats, parameters)
    upper = solve_state(Z, promoted(ground_seats), parameters)
    lower_energy = state_energy_eV(lower, parameters, A)
    upper_energy = state_energy_eV(upper, parameters, A)
    return _from_delta(upper_energy - lower_energy, lower_energy, upper_energy), lower, upper


def hlike_line(
    Z: int,
    n_lo: int,
    n_hi: int,
    parameters: ModelParameters,
    A: int | None = None,
) -> tuple[Emission, AtomicState, AtomicState]:
    lower = solve_state(Z, [SeatLabel(n_lo, "s", 0)], parameters)
    upper = solve_state(Z, [SeatLabel(n_hi, "s", 0)], parameters)
    lower_energy = state_energy_eV(lower, parameters, A)
    upper_energy = state_energy_eV(upper, parameters, A)
    return _from_delta(upper_energy - lower_energy, lower_energy, upper_energy), lower, upper
