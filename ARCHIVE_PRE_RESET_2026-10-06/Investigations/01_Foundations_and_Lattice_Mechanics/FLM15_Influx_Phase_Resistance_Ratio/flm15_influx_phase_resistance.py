"""Blind FLM15 phase-resistance instrument.

This module contains geometry and numerical integration only. Particle data
and post-run comparison formulae are deliberately absent.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from dataclasses import asdict, dataclass
from pathlib import Path

import numpy as np


@dataclass(frozen=True)
class Result:
    shape: str
    aspect: float
    segments: int
    samples: int
    core: float
    padding: float
    seed: int
    length: float
    tensor: list[list[float]]
    eigenvalues: list[float]
    stiffness: float
    response: float
    anisotropy: float


@dataclass(frozen=True)
class LockKernelResult:
    boundary: float
    locked_volume: float
    wake_volume: float
    resistance_per_pressure: float


@dataclass(frozen=True)
class VoidSeatResult:
    name: str
    coordination: int
    radius_ratio: float
    engaged_volume: float
    resistance_per_pressure: float


def curve(shape: str, segments: int, aspect: float = 0.5) -> np.ndarray:
    """Return a closed polygon normalised to unit RMS distance from its centre."""
    t = np.arange(segments, dtype=float) * (2.0 * np.pi / segments)
    if shape == "circle":
        points = np.column_stack((np.cos(t), np.sin(t), np.zeros_like(t)))
    elif shape == "trefoil":
        points = np.column_stack(
            (
                (1.0 + aspect * np.cos(3.0 * t)) * np.cos(2.0 * t),
                (1.0 + aspect * np.cos(3.0 * t)) * np.sin(2.0 * t),
                aspect * np.sin(3.0 * t),
            )
        )
    else:
        raise ValueError(f"unknown shape: {shape}")
    points -= points.mean(axis=0)
    rms = np.sqrt(np.mean(np.sum(points * points, axis=1)))
    return points / rms


def rotate(points: np.ndarray, rotation: np.ndarray) -> np.ndarray:
    return points @ rotation.T


def rotations() -> tuple[np.ndarray, ...]:
    """Frozen orientation matrices: identity and two proper rotations."""
    def axis_angle(axis: tuple[float, float, float], angle: float) -> np.ndarray:
        a = np.asarray(axis, dtype=float)
        a /= np.linalg.norm(a)
        x, y, z = a
        c, s = np.cos(angle), np.sin(angle)
        return np.array(
            [
                [c + x*x*(1-c), x*y*(1-c)-z*s, x*z*(1-c)+y*s],
                [y*x*(1-c)+z*s, c+y*y*(1-c), y*z*(1-c)-x*s],
                [z*x*(1-c)-y*s, z*y*(1-c)+x*s, c+z*z*(1-c)],
            ]
        )
    return (
        np.eye(3),
        axis_angle((1.0, 2.0, 3.0), 0.731),
        axis_angle((-2.0, 1.0, 1.0), 1.117),
    )


def halton(count: int, seed: int = 0) -> np.ndarray:
    """Deterministic shifted Halton points in three dimensions."""
    def radical_inverse(indices: np.ndarray, base: int) -> np.ndarray:
        out = np.zeros(indices.size, dtype=float)
        factor = 1.0 / base
        work = indices.copy()
        while np.any(work):
            out += factor * (work % base)
            work //= base
            factor /= base
        return out

    idx = np.arange(1, count + 1, dtype=np.int64)
    points = np.column_stack([radical_inverse(idx, b) for b in (2, 3, 5)])
    shift = np.random.default_rng(seed).random(3)
    return (points + shift) % 1.0


def glancing_k(radius: float | np.ndarray, boundary: float) -> np.ndarray:
    """Dimensionless relay ratio k(r)=sqrt(r/boundary)."""
    r = np.asarray(radius, dtype=float)
    if boundary <= 0.0 or np.any(r < 0.0):
        raise ValueError("radius must be non-negative and boundary must be positive")
    return np.sqrt(r / boundary)


def angular_lock_fraction(k: float | np.ndarray) -> np.ndarray:
    """Isotropic fraction with projected demand inside relay capacity.

    For mu=|cos(theta)|, mu is uniform on [0,1].  The glancing boundary is
    mu=k, so the relay-locked fraction is P(mu<=k)=clip(k,0,1).
    """
    return np.clip(np.asarray(k, dtype=float), 0.0, 1.0)


def relay_lock_fraction(
    radius: float | np.ndarray, boundary: float
) -> np.ndarray:
    """Target-free entrained fraction inside and at the c-boundary."""
    return angular_lock_fraction(glancing_k(radius, boundary))


def wake_emitting_fraction(
    radius: float | np.ndarray, boundary: float
) -> np.ndarray:
    """Complement whose projected phase demand exceeds relay capacity."""
    return 1.0 - relay_lock_fraction(radius, boundary)


def analytic_engaged_volume(boundary: float, component: str = "locked") -> float:
    """Analytic spherical integral of a glancing fraction.

    locked: 4*pi*int_0^b r^2 sqrt(r/b) dr = 8*pi*b^3/7
    wake:   sphere volume - locked volume = 4*pi*b^3/21
    """
    if boundary <= 0.0:
        raise ValueError("boundary must be positive")
    if component == "locked":
        return float(8.0 * np.pi * boundary**3 / 7.0)
    if component == "wake":
        return float(4.0 * np.pi * boundary**3 / 21.0)
    raise ValueError(f"unknown component: {component}")


def integrate_engaged_volume(
    boundary: float, component: str = "locked", order: int = 256
) -> float:
    """Gauss-Legendre radial integration of the spherical engaged volume."""
    if order < 8:
        raise ValueError("quadrature order must be at least 8")
    nodes, weights = np.polynomial.legendre.leggauss(order)
    radius = 0.5 * boundary * (nodes + 1.0)
    fraction = (
        relay_lock_fraction(radius, boundary)
        if component == "locked"
        else wake_emitting_fraction(radius, boundary)
    )
    return float(
        4.0 * np.pi * 0.5 * boundary
        * np.sum(weights * radius * radius * fraction)
    )


def phase_resistance(pressure: float, engaged_volume: float) -> float:
    """Law-IV isotropic resistance energy: (pressure/3)*engaged volume."""
    if pressure < 0.0 or engaged_volume < 0.0:
        raise ValueError("pressure and engaged volume must be non-negative")
    return pressure * engaged_volume / 3.0


def synchrony_resistance_delta(
    pressure: float, joint_volume: float, parts_volume: float
) -> float:
    """Resistance change when separately engaged domains synchronize."""
    if pressure < 0.0 or joint_volume < 0.0 or parts_volume < 0.0:
        raise ValueError("pressure and engaged volumes must be non-negative")
    return pressure * (joint_volume - parts_volume) / 3.0


def joint_locked_volume_equal_spheres(
    boundary: float,
    separation: float,
    samples: int = 262144,
    seed: int = 1501,
) -> float:
    """Saturated union integral for two equal relay-lock domains.

    The engaged-density union is max(f_1,f_2): coherent overlap is counted
    once. Exact endpoint branches make the non-overlap and coincident controls
    algebraic; intermediate separations use deterministic Halton quadrature.
    """
    if boundary <= 0.0 or separation < 0.0:
        raise ValueError("invalid boundary or separation")
    single = analytic_engaged_volume(boundary)
    if separation == 0.0:
        return single
    if separation >= 2.0 * boundary:
        return 2.0 * single
    half_x = boundary + 0.5 * separation
    points = 2.0 * halton(samples, seed) - 1.0
    points[:, 0] *= half_x
    points[:, 1:] *= boundary
    offset = np.array([0.5 * separation, 0.0, 0.0])
    r1 = np.linalg.norm(points + offset, axis=1)
    r2 = np.linalg.norm(points - offset, axis=1)
    f1 = np.where(
        r1 <= boundary, relay_lock_fraction(r1, boundary), 0.0
    )
    f2 = np.where(
        r2 <= boundary, relay_lock_fraction(r2, boundary), 0.0
    )
    box_volume = (2.0 * half_x) * (2.0 * boundary) ** 2
    return float(box_volume * np.mean(np.maximum(f1, f2)))


def lock_kernel(boundary: float) -> LockKernelResult:
    locked = analytic_engaged_volume(boundary, "locked")
    wake = analytic_engaged_volume(boundary, "wake")
    return LockKernelResult(
        boundary=boundary,
        locked_volume=locked,
        wake_volume=wake,
        resistance_per_pressure=locked / 3.0,
    )


def close_packed_void_seats(scale: float = 1.0) -> tuple[VoidSeatResult, ...]:
    """Tetrahedral/octahedral seats priced by the same lock kernel.

    `scale` is the surrounding spation radius.  Both radius ratios are exact
    close-packing geometry; no particle or benchmark value enters.
    """
    if scale <= 0.0:
        raise ValueError("scale must be positive")
    definitions = (
        ("tetrahedral", 4, np.sqrt(3.0 / 2.0) - 1.0),
        ("octahedral", 6, np.sqrt(2.0) - 1.0),
    )
    seats = []
    for name, coordination, radius_ratio in definitions:
        volume = analytic_engaged_volume(scale * radius_ratio, "locked")
        seats.append(
            VoidSeatResult(
                name=name,
                coordination=coordination,
                radius_ratio=float(radius_ratio),
                engaged_volume=volume,
                resistance_per_pressure=coordination * volume / 3.0,
            )
        )
    return tuple(seats)


def minimum_resistance_void_seat(scale: float = 1.0) -> VoidSeatResult:
    """Select the close-packed relay path with least engaged resistance."""
    return min(close_packed_void_seats(scale), key=lambda seat: seat.resistance_per_pressure)


def lock_kernel_controls() -> dict[str, float | bool]:
    boundary = 1.0
    locked_exact = analytic_engaged_volume(boundary, "locked")
    wake_exact = analytic_engaged_volume(boundary, "wake")
    locked_numeric = integrate_engaged_volume(boundary, "locked")
    wake_numeric = integrate_engaged_volume(boundary, "wake")
    sphere = 4.0 * np.pi / 3.0

    mu = (np.arange(1_000_000, dtype=float) + 0.5) / 1_000_000
    angular_errors = [
        abs(float(np.mean(mu <= k)) - k) for k in (0.125, 0.25, 0.5, 0.875)
    ]
    scale_ratio = (
        analytic_engaged_volume(2.0 * boundary, "locked") / locked_exact
    )
    coincident = joint_locked_volume_equal_spheres(boundary, 0.0)
    separate = joint_locked_volume_equal_spheres(boundary, 2.0 * boundary)
    seats = close_packed_void_seats()
    selected = minimum_resistance_void_seat()
    seat_ratio = seats[1].resistance_per_pressure / seats[0].resistance_per_pressure
    volume_ratio = seats[1].engaged_volume / seats[0].engaged_volume
    return {
        "angular_lock_absolute_error": max(angular_errors),
        "locked_radial_relative_error": abs(locked_numeric / locked_exact - 1.0),
        "wake_radial_relative_error": abs(wake_numeric / wake_exact - 1.0),
        "partition_relative_error": abs((locked_exact + wake_exact) / sphere - 1.0),
        "cubic_scale_relative_error": abs(scale_ratio / 8.0 - 1.0),
        "coincident_union_relative_error": abs(coincident / locked_exact - 1.0),
        "separate_union_relative_error": abs(separate / (2.0 * locked_exact) - 1.0),
        "octahedral_to_tetrahedral_resistance_ratio": seat_ratio,
        "octahedral_to_tetrahedral_volume_ratio": volume_ratio,
        "selected_void_coordination": selected.coordination,
        "angular_lock_pass": max(angular_errors) < 1.0e-6,
        "radial_integral_pass": (
            abs(locked_numeric / locked_exact - 1.0) < 1.0e-5
            and abs(wake_numeric / wake_exact - 1.0) < 1.0e-5
        ),
        "partition_pass": abs((locked_exact + wake_exact) / sphere - 1.0) < 1.0e-12,
        "cubic_scale_pass": abs(scale_ratio / 8.0 - 1.0) < 1.0e-10,
        "synchrony_endpoints_pass": (
            abs(coincident / locked_exact - 1.0) < 1.0e-12
            and abs(separate / (2.0 * locked_exact) - 1.0) < 1.0e-12
        ),
        "tetrahedral_selection_pass": (
            selected.name == "tetrahedral"
            and selected.coordination == 4
            and seat_ratio > 1.0
            and volume_ratio > 1.0
        ),
    }


def phase_gradient(
    samples: np.ndarray,
    points: np.ndarray,
    core: float,
    circulation: float = 1.0,
    sample_chunk: int = 1024,
) -> np.ndarray:
    """Regularised line-integral phase gradient at sample locations."""
    starts = points
    dl = np.roll(points, -1, axis=0) - starts
    mids = starts + 0.5 * dl
    output = np.empty_like(samples)
    prefactor = circulation / (4.0 * np.pi)
    for first in range(0, samples.shape[0], sample_chunk):
        x = samples[first:first + sample_chunk]
        displacement = x[:, None, :] - mids[None, :, :]
        denom = (np.sum(displacement * displacement, axis=2) + core*core) ** 1.5
        cross = np.cross(dl[None, :, :], displacement)
        output[first:first + sample_chunk] = prefactor * np.sum(
            cross / denom[:, :, None], axis=1
        )
    return output


def integrate(
    shape: str,
    aspect: float,
    segments: int,
    samples: int,
    core: float,
    padding: float,
    seed: int,
    orientation: int = 0,
    circulation: float = 1.0,
    fixed_half_box: float | None = None,
) -> Result:
    points = rotate(curve(shape, segments, aspect), rotations()[orientation])
    half_box = (
        float(fixed_half_box)
        if fixed_half_box is not None
        else float(np.max(np.abs(points)) + padding * core)
    )
    xyz = (2.0 * halton(samples, seed) - 1.0) * half_box
    field = phase_gradient(xyz, points, core, circulation)
    volume = (2.0 * half_box) ** 3
    tensor = volume * (field.T @ field) / samples
    eig = np.linalg.eigvalsh(tensor)
    stiffness = float(np.trace(tensor))
    response = stiffness / 3.0
    anisotropy = float((eig[-1] - eig[0]) / np.mean(eig))
    length = float(np.linalg.norm(np.roll(points, -1, axis=0) - points, axis=1).sum())
    return Result(
        shape, aspect, segments, samples, core, padding, seed, length,
        tensor.tolist(), eig.tolist(), stiffness, response, anisotropy,
    )


def matched_pair(
    aspect: float,
    segments: int,
    samples: int,
    core: float,
    padding: float,
    seed: int,
    orientation: int = 0,
) -> tuple[Result, Result, float]:
    c = rotate(curve("circle", segments), rotations()[orientation])
    t = rotate(curve("trefoil", segments, aspect), rotations()[orientation])
    half_box = max(float(np.max(np.abs(c))), float(np.max(np.abs(t)))) + padding * core
    circle = integrate(
        "circle", aspect, segments, samples, core, padding, seed,
        orientation, fixed_half_box=half_box,
    )
    trefoil = integrate(
        "trefoil", aspect, segments, samples, core, padding, seed,
        orientation, fixed_half_box=half_box,
    )
    return circle, trefoil, trefoil.response / circle.response


def analytic_controls() -> dict[str, float | bool]:
    rng = np.random.default_rng(1501)
    g = rng.normal(size=(96, 3))
    directions = rng.normal(size=(131072, 3))
    directions /= np.linalg.norm(directions, axis=1)[:, None]
    lhs = float(np.mean((directions @ g.T) ** 2))
    rhs = float(np.mean(np.sum(g*g, axis=1)) / 3.0)
    isotropic_error = abs(lhs / rhs - 1.0)

    base = integrate("circle", 0.5, 192, 65536, 0.12, 5.0, 1501)
    doubled = integrate(
        "circle", 0.5, 192, 65536, 0.12, 5.0, 1501, circulation=2.0
    )
    symmetry_error = abs(base.tensor[0][0] / base.tensor[1][1] - 1.0)
    circulation_error = abs(doubled.stiffness / base.stiffness / 4.0 - 1.0)

    rotated = integrate("circle", 0.5, 192, 65536, 0.12, 5.0, 1502, orientation=1)
    covariance_error = float(
        np.max(
            np.abs(
                np.asarray(rotated.eigenvalues) / np.asarray(base.eigenvalues) - 1.0
            )
        )
    )
    return {
        "isotropic_relative_error": isotropic_error,
        "circle_xy_relative_error": symmetry_error,
        "circulation_squared_relative_error": circulation_error,
        "rotation_algebra_relative_error": covariance_error,
        "isotropic_pass": isotropic_error < 0.01,
        "circle_symmetry_pass": symmetry_error < 0.03,
        "circulation_pass": circulation_error < 0.02,
        "rotation_covariance_pass": covariance_error < 0.03,
    }


def write_sealed_ratio(path: Path, payload: dict) -> str:
    text = json.dumps(payload, indent=2, sort_keys=True) + "\n"
    path.write_text(text, encoding="utf-8")
    digest = hashlib.sha256(text.encode("utf-8")).hexdigest()
    path.with_suffix(path.suffix + ".sha256").write_text(
        f"{digest}  {path.name}\n", encoding="ascii"
    )
    return digest


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--quick", action="store_true")
    parser.add_argument("--output", type=Path, default=Path(__file__).parent)
    args = parser.parse_args()
    args.output.mkdir(parents=True, exist_ok=True)

    controls = analytic_controls()
    lock_controls = lock_kernel_controls()
    aspects = [0.35, 0.50, float(np.sqrt(2.0 / 3.0)), 0.90]
    rows: list[dict] = []
    if args.quick:
        cases = [(96, 32768, 0.12, 5.0, aspect, 0) for aspect in aspects]
    else:
        # Primary geometry/orientation scan plus one-factor convergence scans.
        cases = [
            (192, 65536, 0.12, 5.0, aspect, orientation)
            for aspect in aspects for orientation in (0, 1, 2)
        ]
        reference_aspect = float(np.sqrt(2.0 / 3.0))
        cases += [(s, 65536, 0.12, 5.0, reference_aspect, 0) for s in (96, 192, 384)]
        cases += [(192, n, 0.12, 5.0, reference_aspect, 0) for n in (32768, 65536, 131072)]
        cases += [(192, 65536, a, 5.0, reference_aspect, 0) for a in (0.08, 0.12, 0.18)]
        cases += [(192, 65536, 0.12, p, reference_aspect, 0) for p in (3.0, 5.0, 8.0)]
        cases = list(dict.fromkeys(cases))

    for segments, samples, core, padding, aspect, orientation in cases:
        c, t, ratio = matched_pair(
            aspect, segments, samples, core, padding,
            1501 + orientation, orientation,
        )
        rows.append({
            "aspect": aspect,
            "segments": segments,
            "samples": samples,
            "core": core,
            "padding": padding,
            "orientation": orientation,
            "circle": asdict(c),
            "trefoil": asdict(t),
            "ratio": ratio,
        })

    primary = [
        r["ratio"] for r in rows
        if r["segments"] == (96 if args.quick else 192)
        and r["samples"] == (32768 if args.quick else 65536)
        and r["core"] == 0.12 and r["padding"] == 5.0
    ]
    payload = {
        "blind": True,
        "instrument_controls": controls,
        "lock_kernel_controls": lock_controls,
        "unit_boundary_lock_kernel": asdict(lock_kernel(1.0)),
        "model_ladder": {
            "R0_BARE": "length ledger in each row",
            "R1_PHASE_STIFFNESS": "stiffness ledger in each row",
            "R2_TRANSLATION_TENSOR": "tensor and response ledgers in each row",
            "R3_FULL_INFLUX_CYCLE": "identical to response by isotropic identity",
            "R4_LOCKED_WAKE": (
                "glancing boundary mu=k(r); relay-locked fraction k(r), "
                "wake-emitting complement 1-k(r)"
            ),
        },
        "primary_ratio": float(np.median(primary)),
        "primary_range": [float(np.min(primary)), float(np.max(primary))],
        "complete_ratio_range": [
            float(min(r["ratio"] for r in rows)),
            float(max(r["ratio"] for r in rows)),
        ],
        "row_count": len(rows),
        "rows": rows,
    }
    digest = write_sealed_ratio(args.output / "blind_ratio.txt", payload)
    print(f"rows={len(rows)}")
    print(f"sealed_sha256={digest}")
    print("blind result written; use the separate reveal instrument after sealing")


if __name__ == "__main__":
    main()
