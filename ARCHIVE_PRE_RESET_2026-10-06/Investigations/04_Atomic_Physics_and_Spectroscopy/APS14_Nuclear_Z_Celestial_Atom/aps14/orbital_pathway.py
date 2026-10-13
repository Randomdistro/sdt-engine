"""Orbital path observables and deterministic swept-occlusion quadrature."""

from __future__ import annotations

import math
from dataclasses import dataclass

import numpy as np

from . import constants as K
from .dynamics import AtomicState, ModelParameters


@dataclass(frozen=True)
class SeatPath:
    circumference_m: float
    period_s: float
    angular_rate_rad_s: float
    action_closure_residual: float


@dataclass(frozen=True)
class TransitionPath:
    lower: SeatPath
    upper: SeatPath
    path_ratio: float
    period_ratio: float
    angular_rate_ratio: float
    delta_length_m: float
    delta_period_s: float


@dataclass
class SweptOcclusion:
    samples: int
    pair_mean_inverse_distance: np.ndarray
    pair_min_distance: np.ndarray
    pair_max_distance: np.ndarray
    pair_distance_variance: np.ndarray
    seat_screening_mean: np.ndarray
    seat_screening_variance: np.ndarray


def seat_path(state: AtomicState, index: int) -> SeatPath:
    radius = float(state.radii[index])
    velocity = float(state.velocities[index])
    length = K.TWO_PI * radius
    period = length / velocity
    angular_rate = velocity / radius
    action = K.M_E * velocity * length
    expected = K.TWO_PI * K.HBAR * float(state.n_eff[index])
    return SeatPath(
        length, period, angular_rate, action / expected - 1.0,
    )


def transition_path(
    lower: AtomicState,
    upper: AtomicState,
    lower_index: int,
    upper_index: int,
) -> TransitionPath:
    low = seat_path(lower, lower_index)
    high = seat_path(upper, upper_index)
    return TransitionPath(
        low, high,
        high.circumference_m / low.circumference_m,
        high.period_s / low.period_s,
        high.angular_rate_rad_s / low.angular_rate_rad_s,
        high.circumference_m - low.circumference_m,
        high.period_s - low.period_s,
    )


def _orbit_basis(normals: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
    first = np.zeros_like(normals)
    second = np.zeros_like(normals)
    for index, normal in enumerate(normals):
        normal = normal / np.linalg.norm(normal)
        reference = np.array([0.0, 0.0, 1.0])
        if abs(float(normal @ reference)) > 0.90:
            reference = np.array([1.0, 0.0, 0.0])
        first[index] = np.cross(normal, reference)
        first[index] /= np.linalg.norm(first[index])
        second[index] = np.cross(normal, first[index])
    return first, second


def _common_cycles(state: AtomicState) -> np.ndarray:
    principal_cubes = [max(1, seat.n ** 3) for seat in state.seats]
    common = 1
    for value in principal_cubes:
        common = math.lcm(common, value)
    common = min(common, 4096)
    return np.asarray([common / value for value in principal_cubes])


def swept_occlusion(
    state: AtomicState,
    parameters: ModelParameters,
    samples: int = 720,
) -> SweptOcclusion:
    count = len(state.seats)
    if count < 2:
        shape = (count, count)
        zeros = np.zeros(shape)
        return SweptOcclusion(
            samples, zeros, zeros, zeros, zeros,
            np.zeros(count), np.zeros(count),
        )
    first, second = _orbit_basis(state.directions)
    cycles = _common_cycles(state)
    offsets = np.arange(count) * (K.TWO_PI / max(1, count))
    g_matrix = np.array([
        [parameters.coupling(a, b) if i != j else 0.0
         for j, b in enumerate(state.seats)]
        for i, a in enumerate(state.seats)
    ])
    distances = np.empty((samples, count, count))
    screening = np.empty((samples, count))
    for sample in range(samples):
        tau = sample / samples
        angle = K.TWO_PI * cycles * tau + offsets
        radial = (
            np.cos(angle)[:, None] * first
            + np.sin(angle)[:, None] * second
        )
        position = state.radii[:, None] * radial
        delta = position[:, None, :] - position[None, :, :]
        distance = np.linalg.norm(delta, axis=2)
        floor = max(1e-24, float(np.min(state.radii)) * 1e-6)
        distance = np.maximum(distance, floor)
        np.fill_diagonal(distance, np.inf)
        projection = np.einsum("ijc,ic->ij", delta, radial)
        contribution = (
            g_matrix * state.radii[:, None] ** 2
            * projection / distance ** 3
        )
        distances[sample] = distance
        screening[sample] = np.sum(contribution, axis=1)
    finite = np.where(np.isfinite(distances), distances, np.nan)
    diagonal = np.arange(count)
    finite[:, diagonal, diagonal] = 0.0
    inverse = np.where(np.isfinite(distances), 1.0 / distances, 0.0)
    return SweptOcclusion(
        samples,
        np.mean(inverse, axis=0),
        np.nanmin(finite, axis=0),
        np.nanmax(finite, axis=0),
        np.nanvar(finite, axis=0),
        np.mean(screening, axis=0),
        np.var(screening, axis=0),
    )


def hlike_pathway_controls() -> list[dict[str, float]]:
    from .configurations import SeatLabel
    from .dynamics import solve_state

    rows = []
    parameters = ModelParameters()
    for z in (1, 2, 3):
        for lower_n, upper_n in ((1, 2), (1, 3), (2, 3)):
            lower = solve_state(z, [SeatLabel(lower_n, "s", 0)], parameters)
            upper = solve_state(z, [SeatLabel(upper_n, "p", 0)], parameters)
            path = transition_path(lower, upper, 0, 0)
            rows.append({
                "Z": z, "lower_n": lower_n, "upper_n": upper_n,
                "path_ratio": path.path_ratio,
                "path_expected": (upper_n / lower_n) ** 2,
                "period_ratio": path.period_ratio,
                "period_expected": (upper_n / lower_n) ** 3,
                "angular_rate_ratio": path.angular_rate_ratio,
                "angular_rate_expected": (lower_n / upper_n) ** 3,
                "lower_action_residual": path.lower.action_closure_residual,
                "upper_action_residual": path.upper.action_closure_residual,
            })
    return rows
