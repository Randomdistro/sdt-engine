"""Deterministic phase-minimised shell geometry."""

from __future__ import annotations

import math

import numpy as np

from .configurations import SeatLabel

GOLDEN_ANGLE = math.pi * (3.0 - math.sqrt(5.0))


def fibonacci_sphere(count: int, phase: float = 0.0) -> np.ndarray:
    if count == 1:
        return np.array([[0.0, 0.0, 1.0]])
    points = []
    for index in range(count):
        y = 1.0 - 2.0 * (index + 0.5) / count
        radius = math.sqrt(max(0.0, 1.0 - y * y))
        angle = index * GOLDEN_ANGLE + phase
        points.append([radius * math.cos(angle), y, radius * math.sin(angle)])
    return np.asarray(points)


def seat_directions(seats: list[SeatLabel]) -> np.ndarray:
    directions = np.zeros((len(seats), 3))
    by_shell: dict[int, list[int]] = {}
    for index, seat in enumerate(seats):
        by_shell.setdefault(seat.n, []).append(index)
    for n, indices in by_shell.items():
        points = fibonacci_sphere(len(indices), phase=n * GOLDEN_ANGLE / 3.0)
        for local, global_index in enumerate(indices):
            directions[global_index] = points[local]
    return directions


def positions(radii: np.ndarray, directions: np.ndarray) -> np.ndarray:
    return radii[:, None] * directions


def pair_distances(pos: np.ndarray) -> np.ndarray:
    delta = pos[:, None, :] - pos[None, :, :]
    distance = np.linalg.norm(delta, axis=2)
    np.fill_diagonal(distance, np.inf)
    return distance
