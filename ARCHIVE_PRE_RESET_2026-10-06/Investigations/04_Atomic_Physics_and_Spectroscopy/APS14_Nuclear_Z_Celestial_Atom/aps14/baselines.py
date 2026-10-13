"""Empirical comparators. Not SDT inputs. Provenance labelled at use."""

from __future__ import annotations

import math

from . import constants as K
from .configurations import SeatLabel, after_removals, ionisation_order


def _group(seat: SeatLabel) -> tuple[int, str]:
    if seat.kind in ("s", "p"):
        return seat.n, "sp"
    return seat.n, seat.kind


def slater_zeff(seats: list[SeatLabel], index: int) -> float:
    """Classical Slater screening. Provenance: empirical comparator, not native."""
    target = seats[index]
    tgroup = _group(target)
    sigma = 0.0
    for j, other in enumerate(seats):
        if j == index:
            continue
        ogroup = _group(other)
        if ogroup == tgroup:
            sigma += 0.30 if target.n == 1 else 0.35
        elif other.n == target.n - 1 and target.kind in ("s", "p"):
            sigma += 0.85
        elif other.n < target.n:
            sigma += 1.00
        elif other.n == target.n and target.kind == "d" and other.kind in ("s", "p"):
            sigma += 1.00
    return sigma


def slater_ie_eV(Z: int, seats: list[SeatLabel]) -> float:
    if not seats:
        return math.nan
    active = ionisation_order(seats)[0]
    sigma = slater_zeff(seats, active)
    n = seats[active].n
    zeff = max(Z - sigma, 0.05)
    return K.RY_EV * (zeff / n) ** 2


def rydberg_ie_eV(Z: int, seats: list[SeatLabel]) -> float:
    if not seats:
        return math.nan
    active = ionisation_order(seats)[0]
    n = seats[active].n
    return K.RY_EV * (Z / n) ** 2


def zeff_ie_eV(Z: int, seats: list[SeatLabel], sigma: float) -> float:
    if not seats:
        return math.nan
    active = ionisation_order(seats)[0]
    n = seats[active].n
    n_e = len(seats)
    zeff = max(Z - sigma * max(n_e - 1, 0), 0.05)
    return K.RY_EV * (zeff / n) ** 2


def sequential_seats(full: list[SeatLabel], step: int) -> list[SeatLabel]:
    """Seats present before ionisation step k (1-based)."""
    return after_removals(full, step - 1)
