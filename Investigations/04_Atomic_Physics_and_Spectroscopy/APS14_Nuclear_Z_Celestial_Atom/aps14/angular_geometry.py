"""Axis/around/diagonal seat templates for APS14a."""

from __future__ import annotations

import math

import numpy as np

from .configurations import SeatLabel
from .geometry import fibonacci_sphere


def _unit(vector) -> np.ndarray:
    array = np.asarray(vector, dtype=float)
    return array / np.linalg.norm(array)


def _rotation_z(angle: float) -> np.ndarray:
    c, s = math.cos(angle), math.sin(angle)
    return np.array([[c, -s, 0.0], [s, c, 0.0], [0.0, 0.0, 1.0]])


def subshell_template(kind: str) -> np.ndarray:
    if kind == "s":
        return np.asarray([[0.0, 0.0, 1.0], [0.0, 0.0, -1.0]])
    if kind == "p":
        first = [
            [math.cos(2 * math.pi * index / 3),
             math.sin(2 * math.pi * index / 3), 0.0]
            for index in range(3)
        ]
        return np.asarray(first + [(-np.asarray(value)).tolist() for value in first])
    if kind == "d":
        tilt = math.sqrt(1.0 / 3.0)
        radial = math.sqrt(1.0 - tilt * tilt)
        first = [
            [radial * math.cos(2 * math.pi * index / 5),
             radial * math.sin(2 * math.pi * index / 5), tilt]
            for index in range(5)
        ]
        return np.asarray(first + [(-np.asarray(value)).tolist() for value in first])
    if kind == "f":
        return fibonacci_sphere(14)
    raise ValueError(f"unknown subshell {kind!r}")


def angular_directions(
    seats: list[SeatLabel],
    shell_phases: dict[int, float] | None = None,
) -> np.ndarray:
    phases = shell_phases or {}
    directions = np.zeros((len(seats), 3))
    groups: dict[tuple[int, str], list[int]] = {}
    for index, seat in enumerate(seats):
        groups.setdefault((seat.n, seat.kind), []).append(index)
    kind_offset = {"s": 0.0, "p": math.pi / 6, "d": math.pi / 10, "f": 0.0}
    for (n, kind), indices in groups.items():
        template = subshell_template(kind)
        if len(indices) > len(template):
            raise ValueError(f"{n}{kind} occupancy exceeds geometric capacity")
        rotation = _rotation_z(phases.get(n, 0.0) + kind_offset[kind])
        for local, global_index in enumerate(indices):
            directions[global_index] = rotation @ template[local]
    return directions


def phase_grid(seats: list[SeatLabel], divisions: int = 12) -> list[dict[int, float]]:
    shells = sorted({seat.n for seat in seats})
    if len(shells) <= 1:
        return [{shells[0]: 0.0}] if shells else [{}]
    # Fix the innermost shell as the rotational gauge; scan each outer shell
    # with one common phase to avoid an exponential element-specific search.
    anchor = shells[0]
    return [
        {anchor: 0.0, **{
            shell: K * 2.0 * math.pi / divisions for shell in shells[1:]
        }}
        for K in range(divisions)
    ]


def angular_pair_tensor(
    radii: np.ndarray,
    directions: np.ndarray,
) -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    positions = radii[:, None] * directions
    delta = positions[:, None, :] - positions[None, :, :]
    distance = np.linalg.norm(delta, axis=2)
    np.fill_diagonal(distance, np.inf)
    projection = np.einsum("ijc,ic->ij", delta, directions)
    cosine = directions @ directions.T
    return distance, projection, cosine
