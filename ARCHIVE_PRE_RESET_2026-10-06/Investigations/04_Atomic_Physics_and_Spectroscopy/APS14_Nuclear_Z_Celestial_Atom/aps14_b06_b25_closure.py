"""B06/B25 target-independent close-packed occlusion closure.

The forward model is a classical SDT action/occlusion functional:

    E/Ry = sum_i[n_i^2/x_i^2 - 2 Z/x_i]
           + 2 sum_{i<j} R_ij/d_ij,

where x=r/a0. The 2s dyad remains polar and the 2p lanes occupy the six-ring.
The exact R_ij prices come from FLM15 lock/wake fractions, coincident synchrony,
and swept path/chord geometry. Shell radii are minimized before any measured
energy is read. No screening coefficient or energy amplitude is fitted.
"""

from __future__ import annotations

import csv
import math
from dataclasses import dataclass
from pathlib import Path

import numpy as np
from scipy.optimize import least_squares, minimize
from scipy.special import ellipk

from aps14 import constants as K

ROOT = Path(__file__).resolve().parent


def counterphase_to_chord(angle: float) -> float:
    """Complete circular-path resistance relative to its frozen chord."""
    cosine = math.cos(angle)
    parameter = (1.0 - cosine) / 2.0
    path_inverse = float(ellipk(parameter)) / math.pi
    chord_inverse = 1.0 / math.sqrt(2.0 - 2.0 * cosine)
    return path_inverse / chord_inverse


LOCK_FRACTION = 6.0 / 7.0
WAKE_FRACTION = 1.0 / 7.0
COINCIDENT_SYNCHRONY = 1.0 / 2.0
S_DYAD_RESISTANCE = 8.0 / 7.0
SP_RESISTANCE = math.pi / 3.0
P60_RESISTANCE = 1.0
P120_RESISTANCE = (
    LOCK_FRACTION * counterphase_to_chord(2.0 * math.pi / 3.0)
    + WAKE_FRACTION * COINCIDENT_SYNCHRONY
)
P180_RESISTANCE = WAKE_FRACTION * COINCIDENT_SYNCHRONY


@dataclass(frozen=True)
class Seat:
    shell: str
    n: int
    direction: np.ndarray


@dataclass(frozen=True)
class StatePrediction:
    Z: int
    electrons: int
    energy_eV: float
    radii_a0: tuple[float, ...]
    force_residual: float
    converged: bool


def _unit(vector: tuple[float, float, float]) -> np.ndarray:
    value = np.asarray(vector, dtype=float)
    return value / np.linalg.norm(value)


def ring_direction(index: int) -> np.ndarray:
    """Dodecardinal n=2 six-ring, offset 30 degrees."""
    angle = math.pi / 6.0 + index * math.pi / 3.0
    return np.array([math.cos(angle), math.sin(angle), 0.0])


OUTER_ORDER = (
    Seat("2s", 2, _unit((0.0, 0.0, 1.0))),
    Seat("2s", 2, _unit((0.0, 0.0, -1.0))),
    Seat("2p", 2, ring_direction(0)),
    Seat("2p", 2, ring_direction(2)),
    Seat("2p", 2, ring_direction(4)),
    Seat("2p", 2, ring_direction(3)),
    Seat("2p", 2, ring_direction(5)),
    Seat("2p", 2, ring_direction(1)),
)


def seats_for(electrons: int) -> list[Seat]:
    if not 0 <= electrons <= 10:
        raise ValueError("closure corpus supports 0..10 electrons")
    inner = (
        np.array([0.0, 0.0, 1.0]),
        np.array([0.0, 0.0, -1.0]),
    )
    seats = [
        Seat("1s", 1, inner[index]) for index in range(min(2, electrons))
    ]
    seats.extend(OUTER_ORDER[: max(0, electrons - 2)])
    return seats


def orbital_plane_layout(
    seats: list[Seat],
) -> tuple[np.ndarray, list[tuple[int, int | None]], np.ndarray]:
    """Return signed cycle rates, antipodal pairs, and frozen phase starts."""
    normals = np.asarray([seat.direction for seat in seats])
    principal_cubes = [seat.n**3 for seat in seats]
    common = math.lcm(*principal_cubes)
    cycles = np.zeros(len(seats))
    planes: list[tuple[int, int | None]] = []
    defaults: list[float] = []
    for shell in tuple(dict.fromkeys(seat.shell for seat in seats)):
        indices = [
            index for index, seat in enumerate(seats)
            if seat.shell == shell
        ]
        pending = set(indices)
        shell_planes: list[tuple[int, int | None]] = []
        while pending:
            first = min(pending)
            pending.remove(first)
            partner = next(
                (
                    second for second in sorted(pending)
                    if float(normals[first] @ normals[second])
                    < -1.0 + 1.0e-12
                ),
                None,
            )
            if partner is not None:
                pending.remove(partner)
            shell_planes.append((first, partner))
        shell_offset = (seats[indices[0]].n - 1) * math.pi / 6.0
        for plane_index, (first, partner) in enumerate(shell_planes):
            magnitude = common / principal_cubes[first]
            cycles[first] = magnitude
            if partner is not None:
                cycles[partner] = -magnitude
            planes.append((first, partner))
            defaults.append(
                shell_offset
                + 2.0 * math.pi * plane_index / max(1, len(shell_planes))
            )
    return cycles, planes, np.asarray(defaults)


def swept_inverse_distance(
    seats: list[Seat],
    radii: dict[str, float],
    plane_phases: np.ndarray,
    samples: int = 144,
) -> np.ndarray:
    """Complete-path inverse separation for phase-locked finite wakes."""
    normals = np.asarray([seat.direction for seat in seats])
    first_basis = np.zeros_like(normals)
    second_basis = np.zeros_like(normals)
    for index, normal in enumerate(normals):
        reference = np.array([0.0, 0.0, 1.0])
        if abs(float(normal @ reference)) > 0.90:
            reference = np.array([1.0, 0.0, 0.0])
        first_basis[index] = np.cross(normal, reference)
        first_basis[index] /= np.linalg.norm(first_basis[index])
        second_basis[index] = np.cross(normal, first_basis[index])
    cycles, planes, _ = orbital_plane_layout(seats)
    offsets = np.zeros(len(seats))
    for phase, (first, partner) in zip(plane_phases, planes):
        offsets[first] = phase
        if partner is not None:
            offsets[partner] = phase
    inverse_sum = np.zeros((len(seats), len(seats)))
    wake_diameter = 2.0 * K.R_E / K.A0
    for sample in range(samples):
        tau = (sample + 0.5) / samples
        angle = 2.0 * math.pi * cycles * tau + offsets
        radial = (
            np.cos(angle)[:, None] * first_basis
            + np.sin(angle)[:, None] * second_basis
        )
        position = np.asarray([
            radii[seat.shell] * radial[index]
            for index, seat in enumerate(seats)
        ])
        delta = position[:, None, :] - position[None, :, :]
        distance = np.linalg.norm(delta, axis=2)
        distance = np.sqrt(
            distance * distance + wake_diameter * wake_diameter
        )
        np.fill_diagonal(distance, np.inf)
        inverse_sum += 1.0 / distance
    return inverse_sum / samples


def dodecardinal_pair_resistance(first: Seat, second: Seat) -> float:
    """Target-free resistance price for one fixed pair of SDT lanes."""
    same_shell = first.shell == second.shell
    cosine = float(first.direction @ second.direction)
    antipodal = cosine < -1.0 + 1.0e-12
    if first.n != second.n:
        # n=1 and n=2 paths share 1/8 of the common n^3 period.
        return 7.0 / 8.0
    if same_shell and first.shell.endswith("s"):
        # FLM15 V_lock/(pi b^3) = 8/7 for a polar dyad.
        return S_DYAD_RESISTANCE
    if same_shell and antipodal:
        # Only the 1/7 wake remains, then coincident-domain synchrony
        # counts the shared resistance once rather than twice.
        return P180_RESISTANCE
    if (
        same_shell
        and first.shell.endswith("p")
        and cosine < -0.5 + 1.0e-12
    ):
        # 120-degree counterphase path, lock/wake weighted.
        return P120_RESISTANCE
    if same_shell and first.shell.endswith("p"):
        # A 60-degree chord equals one radius.
        return P60_RESISTANCE
    if not same_shell:
        # Polar-to-ring glancing arc/chord ratio: (pi/3)/1.
        return SP_RESISTANCE
    return 1.0


def _state_objective(
    variables: np.ndarray,
    Z: int,
    electrons: int,
    groups: tuple[str, ...],
    kernel: str,
) -> float:
    radii = {group: math.exp(float(variables[index]))
             for index, group in enumerate(groups)}
    seats = seats_for(electrons)
    energy = 0.0
    for seat in seats:
        radius = radii[seat.shell]
        energy += seat.n * seat.n / (radius * radius) - 2.0 * Z / radius
    if kernel == "swept":
        _, planes, defaults = orbital_plane_layout(seats)
        phase_values = np.asarray(variables[len(groups):], dtype=float)
        plane_phases = defaults.copy()
        if len(planes) > 1:
            plane_phases[1:] = phase_values
        inverse_mean = swept_inverse_distance(
            seats, radii, plane_phases, samples=144
        )
        upper = np.triu_indices(len(seats), 1)
        energy += 2.0 * float(np.sum(inverse_mean[upper]))
    else:
        position = np.asarray([
            radii[seat.shell] * seat.direction for seat in seats
        ])
        for first in range(len(seats)):
            for second in range(first + 1, len(seats)):
                distance = float(
                    np.linalg.norm(position[first] - position[second])
                )
                if distance <= 1.0e-10:
                    return 1.0e30
                if kernel == "pair_swept":
                    first_seat = seats[first]
                    second_seat = seats[second]
                    first_radius = radii[first_seat.shell]
                    second_radius = radii[second_seat.shell]
                    if first_seat.n != second_seat.n:
                        energy += 2.0 * (7.0 / 8.0) / distance
                        continue
                    cosine = float(
                        first_seat.direction @ second_seat.direction
                    )
                    antipodal = cosine < -1.0 + 1.0e-12
                    if antipodal and first_seat.shell.endswith("s"):
                        energy += (5.0 / 4.0) / first_radius
                        continue
                    if antipodal:
                        energy += (1.0 / 7.0) / first_radius
                        continue
                    a_term = (
                        first_radius * first_radius
                        + second_radius * second_radius
                        + 2.0 * first_radius * second_radius * cosine
                    )
                    b_term = (
                        2.0 * first_radius * second_radius
                        * (1.0 - cosine)
                    )
                    total = a_term + b_term
                    parameter = b_term / total
                    inverse_path = (
                        2.0 * float(ellipk(parameter))
                        / (math.pi * math.sqrt(total))
                    )
                    energy += 2.0 * inverse_path
                    continue
                if kernel == "full":
                    relative_resistance = 1.0
                elif kernel == "common_phase":
                    relative_resistance = (
                        min(seats[first].n, seats[second].n)
                        / max(seats[first].n, seats[second].n)
                    ) ** 3
                elif kernel == "relative_phase":
                    if seats[first].n == seats[second].n:
                        relative_resistance = 1.0
                    else:
                        common_phase = (
                            min(seats[first].n, seats[second].n)
                            / max(seats[first].n, seats[second].n)
                        ) ** 3
                        relative_resistance = 1.0 - common_phase
                elif kernel == "relative_wake":
                    if seats[first].n == seats[second].n:
                        antipodal = float(
                            seats[first].direction @ seats[second].direction
                        ) < -1.0 + 1.0e-12
                        relative_resistance = (
                            1.0 / 7.0 if antipodal else 1.0
                        )
                    else:
                        common_phase = (
                            min(seats[first].n, seats[second].n)
                            / max(seats[first].n, seats[second].n)
                        ) ** 3
                        relative_resistance = 1.0 - common_phase
                elif kernel == "relay_lock":
                    # A complete W=1 dyad sweep carries the 5/4 same-tier
                    # resistance. Unlike-tier n=1/n=2 paths coincide for
                    # 1/8 of their n^3 period and retain 7/8 resistance.
                    relative_resistance = (
                        5.0 / 4.0
                        if seats[first].n == seats[second].n
                        else 7.0 / 8.0
                    )
                elif kernel == "dodecardinal_lock":
                    relative_resistance = dodecardinal_pair_resistance(
                        seats[first], seats[second]
                    )
                else:
                    raise ValueError(f"unknown kernel: {kernel}")
                energy += 2.0 * relative_resistance / distance
    return energy


def _dodecardinal_gradient(
    variables: np.ndarray,
    Z: int,
    electrons: int,
    groups: tuple[str, ...],
    kernel: str,
) -> np.ndarray:
    """Exact dE/d(log r) for the sealed static resistance functional."""
    if kernel != "dodecardinal_lock":
        raise ValueError("analytic gradient belongs to dodecardinal_lock")
    radii = {
        group: math.exp(float(variables[index]))
        for index, group in enumerate(groups)
    }
    group_index = {group: index for index, group in enumerate(groups)}
    seats = seats_for(electrons)
    gradient = np.zeros(len(variables))
    for seat in seats:
        radius = radii[seat.shell]
        gradient[group_index[seat.shell]] += (
            -2.0 * seat.n * seat.n / (radius * radius)
            + 2.0 * Z / radius
        )
    for first_index in range(len(seats)):
        first = seats[first_index]
        first_radius = radii[first.shell]
        for second_index in range(first_index + 1, len(seats)):
            second = seats[second_index]
            second_radius = radii[second.shell]
            cosine = float(first.direction @ second.direction)
            distance_squared = (
                first_radius * first_radius
                + second_radius * second_radius
                - 2.0 * first_radius * second_radius * cosine
            )
            if distance_squared <= 1.0e-20:
                return np.full(len(variables), 1.0e30)
            distance = math.sqrt(distance_squared)
            resistance = dodecardinal_pair_resistance(first, second)
            common = -2.0 * resistance / (distance**3)
            gradient[group_index[first.shell]] += (
                common
                * first_radius
                * (first_radius - second_radius * cosine)
            )
            gradient[group_index[second.shell]] += (
                common
                * second_radius
                * (second_radius - first_radius * cosine)
            )
    return gradient


def solve_state(
    Z: int, electrons: int, kernel: str = "dodecardinal_lock"
) -> StatePrediction:
    if electrons == 0:
        return StatePrediction(Z, 0, 0.0, (), 0.0, True)
    initial_seats = seats_for(electrons)
    groups = tuple(dict.fromkeys(seat.shell for seat in initial_seats))
    _, planes, default_phases = orbital_plane_layout(initial_seats)
    phase_count = max(0, len(planes) - 1) if kernel == "swept" else 0
    phase_starts = [np.empty(0)]
    if phase_count:
        wrap = lambda values: (
            np.asarray(values) + math.pi
        ) % (2.0 * math.pi) - math.pi
        phase_starts = [
            wrap(default_phases[1:]),
            np.zeros(phase_count),
            wrap(
                np.arange(1, phase_count + 1)
                * math.pi * (3.0 - math.sqrt(5.0))
            ),
        ]
    starts = []
    for scale in (0.75, 1.0, 1.5, 2.0):
        logs = []
        for group in groups:
            n = 1 if group == "1s" else 2
            inner_count = 0 if group == "1s" else min(2, electrons)
            effective = max(0.5, Z - 0.75 * inner_count)
            logs.append(math.log(scale * n * n / effective))
        for phases in phase_starts:
            starts.append(np.asarray([*logs, *phases]))

    best = None
    bounds = [
        (math.log(1.0e-3), math.log(50.0)) for _ in groups
    ] + [(-math.pi, math.pi)] * phase_count
    for start in starts:
        method = "Powell" if kernel == "swept" else "L-BFGS-B"
        options = (
            {"ftol": 1.0e-11, "xtol": 1.0e-9, "maxiter": 4000}
            if method == "Powell"
            else {"ftol": 1.0e-13, "gtol": 1.0e-10, "maxiter": 2000}
        )
        result = minimize(
            _state_objective,
            start,
            args=(Z, electrons, groups, kernel),
            method=method,
            bounds=bounds,
            options=options,
        )
        if best is None or result.fun < best.fun:
            best = result
    assert best is not None
    stationary_success = bool(best.success)
    if kernel == "dodecardinal_lock":
        refined = minimize(
            _state_objective,
            best.x,
            args=(Z, electrons, groups, kernel),
            method="BFGS",
            jac=_dodecardinal_gradient,
            options={"gtol": 1.0e-12, "maxiter": 2000},
        )
        if np.isfinite(refined.fun) and refined.fun <= best.fun + 1.0e-10:
            best = refined
        stationary = least_squares(
            _dodecardinal_gradient,
            best.x,
            args=(Z, electrons, groups, kernel),
            xtol=1.0e-14,
            ftol=1.0e-14,
            gtol=1.0e-14,
            max_nfev=1000,
        )
        stationary_energy = _state_objective(
            stationary.x, Z, electrons, groups, kernel
        )
        if (
            np.isfinite(stationary_energy)
            and stationary_energy <= best.fun + 1.0e-10
        ):
            best.x = stationary.x
            best.fun = stationary_energy
            stationary_success = bool(stationary.success)
    radii = tuple(
        math.exp(float(value)) for value in best.x[: len(groups)]
    )
    gradient = (
        _dodecardinal_gradient(
            best.x, Z, electrons, groups, "dodecardinal_lock"
        )
        if kernel == "dodecardinal_lock"
        else np.asarray(getattr(best, "jac", np.zeros(len(best.x))))
    )
    force_residual = float(
        np.max(np.abs(gradient)) / max(1.0, abs(float(best.fun)))
    )
    return StatePrediction(
        Z=Z,
        electrons=electrons,
        energy_eV=float(best.fun * K.RY_EV),
        radii_a0=radii,
        force_residual=force_residual,
        converged=bool(stationary_success and force_residual < 1.0e-8),
    )


def predict_corpus(
    kernel: str = "dodecardinal_lock",
) -> tuple[list[dict[str, float]], StatePrediction]:
    rows = []
    helium = None
    for Z in range(2, 11):
        neutral = solve_state(Z, Z, kernel)
        ion = solve_state(Z, Z - 1, kernel)
        if Z == 2:
            helium = neutral
        rows.append({
            "Z": Z,
            "predicted_first_ie_eV": ion.energy_eV - neutral.energy_eV,
            "neutral_energy_eV": neutral.energy_eV,
            "ion_energy_eV": ion.energy_eV,
            "force_residual": max(
                neutral.force_residual, ion.force_residual
            ),
            "converged": float(neutral.converged and ion.converged),
        })
    assert helium is not None
    return rows, helium


def load_comparisons(
) -> tuple[dict[int, float], float, list[tuple[int, int, float]]]:
    first: dict[int, float] = {}
    helium_total = 0.0
    all_rows: list[tuple[int, int, float]] = []
    with (ROOT / "data" / "ionisation.csv").open(
        newline="", encoding="utf-8"
    ) as handle:
        for row in csv.DictReader(handle):
            if not row["energy_eV"]:
                continue
            Z = int(row["Z"])
            step = int(row["step"])
            energy = float(row["energy_eV"])
            if 2 <= Z <= 10:
                all_rows.append((Z, step, energy))
            if 2 <= Z <= 10 and step == 1:
                first[Z] = energy
            if Z == 2:
                helium_total += energy
    return first, helium_total, all_rows


def main() -> int:
    predictions, helium = predict_corpus()
    one_electron_errors = []
    for Z in range(2, 11):
        state = solve_state(Z, 1)
        radius_error = abs(state.radii_a0[0] * Z - 1.0)
        energy_error = abs(
            state.energy_eV / (-Z * Z * K.RY_EV) - 1.0
        )
        one_electron_errors.extend((radius_error, energy_error))
    one_electron_max = max(one_electron_errors)
    max_force_residual = max(
        float(row["force_residual"]) for row in predictions
    )

    print("APS14 B06/B25 CLOSE-PACKED OCCLUSION - SEALED PREDICTIONS")
    print(
        "resistance=(8/7, pi/3, 1, "
        "6/7*counterphase(120)+1/14, 1/14)"
    )
    print("Z  IE1_pred[eV]  E_neutral[eV]")
    for row in predictions:
        print(
            f"{int(row['Z']):2d}  {row['predicted_first_ie_eV']:12.6f}"
            f"  {row['neutral_energy_eV']:14.6f}"
        )
    helium_binding = -helium.energy_eV
    print(f"He_total_binding_pred_eV={helium_binding:.9f}")
    print(f"one_electron_max_relative_error={one_electron_max:.3e}")
    print(f"max_force_residual={max_force_residual:.3e}")

    observed, helium_observed, all_observed = load_comparisons()
    errors = []
    print("\nPOST-SEAL COMPARISON")
    for row in predictions:
        Z = int(row["Z"])
        error = abs(row["predicted_first_ie_eV"] / observed[Z] - 1.0)
        errors.append(error)
        print(
            f"Z={Z:2d} pred={row['predicted_first_ie_eV']:10.6f}"
            f" obs={observed[Z]:10.6f} rel={100.0 * error:8.3f}%"
        )
    median = float(np.median(errors))
    maximum = max(errors)
    helium_error = abs(helium_binding / helium_observed - 1.0)
    print(f"B06_median_relative_error={100.0 * median:.6f}%")
    print(f"B06_max_relative_error={100.0 * maximum:.6f}%")
    print(f"B25_He_relative_error={100.0 * helium_error:.6f}%")

    holdout_errors = []
    for Z, step, measured_energy in all_observed:
        if step == 1:
            continue
        electrons = Z - step + 1
        before = solve_state(Z, electrons)
        after = solve_state(Z, electrons - 1)
        predicted_energy = after.energy_eV - before.energy_eV
        holdout_errors.append(
            abs(predicted_energy / measured_energy - 1.0)
        )
    holdout_median = float(np.median(holdout_errors))
    holdout_maximum = max(holdout_errors)
    print(f"sequential_holdout_rows={len(holdout_errors)}")
    print(
        "sequential_holdout_median_relative_error="
        f"{100.0 * holdout_median:.6f}%"
    )
    print(
        "sequential_holdout_max_relative_error="
        f"{100.0 * holdout_maximum:.6f}%"
    )

    states_pass = all(bool(row["converged"]) for row in predictions)
    control_pass = one_electron_max < 1.0e-10
    residual_pass = max_force_residual < 1.0e-8
    holdout_pass = holdout_median <= 0.05 and holdout_maximum <= 0.10
    b06_pass = (
        states_pass
        and control_pass
        and residual_pass
        and median <= 0.05
        and maximum <= 0.15
    )
    b25_pass = helium.converged and helium_error <= 0.02
    print(f"SEQUENTIAL_HOLDOUT={'PASS' if holdout_pass else 'FAIL'}")
    print(f"B06_GATE={'PASS' if b06_pass else 'FAIL'}")
    print(f"B25_GATE={'PASS' if b25_pass else 'FAIL'}")
    return 0 if b06_pass and b25_pass and holdout_pass else 1


if __name__ == "__main__":
    raise SystemExit(main())
