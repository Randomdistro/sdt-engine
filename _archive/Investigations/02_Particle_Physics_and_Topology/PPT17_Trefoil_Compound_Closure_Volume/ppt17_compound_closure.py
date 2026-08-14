#!/usr/bin/env python3
"""PPT17: audit the six-phase trefoil closure and 6*pi^5 assignment."""

from __future__ import annotations

import math
import re
from dataclasses import dataclass
from pathlib import Path


HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
LAWS = ROOT / "Engine" / "include" / "sdt" / "laws.hpp"
OUTPUT = HERE / "ppt17_results.txt"


@dataclass(frozen=True)
class Recurrence:
    p: int
    q: int
    states: tuple[tuple[int, int], ...]
    return_step: int


def phase_pair(p: int, q: int, j: int) -> tuple[int, int]:
    modulus = p * q
    return ((p * j) % modulus, (q * j) % modulus)


def recurrence(p: int, q: int) -> Recurrence:
    if p < 1 or q < 1 or math.gcd(p, q) != 1:
        raise ValueError("p and q must be positive and coprime")
    initial = phase_pair(p, q, 0)
    states: list[tuple[int, int]] = [initial]
    for j in range(1, 10 * p * q + 1):
        state = phase_pair(p, q, j)
        if state == initial:
            return Recurrence(p, q, tuple(states), j)
        states.append(state)
    raise RuntimeError("recurrence search did not close")


def read_laws_constant(name: str) -> float:
    text = LAWS.read_text(encoding="utf-8")
    match = re.search(
        rf"inline constexpr double {name}\s*=\s*([0-9.eE+'-]+);", text
    )
    if not match:
        raise RuntimeError(f"could not read {name} from laws.hpp")
    return float(match.group(1).replace("'", ""))


def read_measured_ratio() -> float:
    return read_laws_constant("m_p") / read_laws_constant("m_e")


def run_controls() -> list[str]:
    lines: list[str] = []
    for p, q in ((1, 1), (1, 2), (2, 3), (3, 4), (4, 5)):
        result = recurrence(p, q)
        expected = math.lcm(p, q)
        if result.return_step != expected:
            raise RuntimeError(f"recurrence control failed for ({p},{q})")
        if len(set(result.states)) != expected:
            raise RuntimeError(f"state uniqueness control failed for ({p},{q})")
        lines.append(
            f"CONTROL recurrence ({p},{q}): return={result.return_step}, "
            f"distinct={len(set(result.states))}, expected={expected} PASS"
        )

    for exponent in range(10):
        direct = 1.0
        for _ in range(exponent):
            direct *= math.pi
        reference = math.pi**exponent
        relative = abs(direct - reference) / max(abs(reference), 1.0)
        if relative > 1e-14:
            raise RuntimeError(f"pi-power control failed at exponent {exponent}")
    lines.append("CONTROL pi powers 0..9: tolerance=1e-14 PASS")
    return lines


def main() -> None:
    lines = ["PPT17 TREFOIL COMPOUND CLOSURE", "=" * 38]
    lines.extend(run_controls())

    trefoil = recurrence(2, 3)
    compound = [
        (j, *phase_pair(2, 3, j), (-1) ** j)
        for j in range(trefoil.return_step + 1)
    ]
    lines.extend(
        [
            "",
            "ROUTE A — RECURRENCE",
            "j  toroidal  poloidal  contra_parity",
        ]
    )
    lines.extend(f"{j}  {a:8d}  {b:8d}  {parity:13d}" for j, a, b, parity in compound)
    lines.append(
        f"A_GATE: distinct_pre_return={len(trefoil.states)}, "
        f"first_full_return={trefoil.return_step}, PASS"
    )

    seats = trefoil.return_step
    k_surface_stored = read_laws_constant("k_proton_surface")
    alpha_inv = read_laws_constant("alpha_inv")
    proton_radius = read_laws_constant("R_p")
    bohr_radius = read_laws_constant("a_0")
    k_surface = alpha_inv * math.sqrt(proton_radius / bohr_radius)
    beta = 1.0 / k_surface
    demanded_rotations = seats * beta
    locked_rotations = round(demanded_rotations)
    lock_residual = demanded_rotations - locked_rotations
    locked_beta = locked_rotations / seats
    speed_error_pct = (beta - locked_beta) / locked_beta * 100.0
    surplus_rotations = locked_rotations - seats
    lock_pass = abs(lock_residual) < 0.25 and abs(speed_error_pct) < 0.25

    lines.extend(
        [
            "",
            "ROUTE B — ROTATION PHASE LOCK (AMENDMENT 01)",
            "n is a traversal count, not a dimension count.",
            f"k_proton_surface_stored_rounded={k_surface_stored:.12f}",
            f"k_proton_surface_reconstructed={k_surface:.12f}",
            f"beta=v_phase/c={beta:.12f}",
            f"six_seat_demanded_rotations={demanded_rotations:.12f}",
            f"nearest_integer_lock={locked_rotations}",
            f"lock_residual_turns={lock_residual:+.12f}",
            f"locked_beta={locked_beta:.12f}",
            f"speed_error_vs_lock_pct={speed_error_pct:+.9f}",
            f"lattice_rotations_per_closure={seats}",
            f"surplus_rotations={surplus_rotations}",
            "B_GATE: " + (
                "unique 11-turn lock; 11-6=5 surplus rotations; PASS"
                if lock_pass and surplus_rotations == 5
                else "phase-lock or five-surplus condition failed; FAIL"
            ),
        ]
    )

    lines.extend(
        [
            "",
            "ROUTE C — VOLUME-MEASURE STATUS",
            "The integer exponent five now comes from rotation surplus:",
            "  6 seats * (11/6 locked turns per seat - 1 lattice turn per seat) = 5.",
            "This does not by itself establish one multiplicative pi factor per",
            "surplus rotation or prove six equal non-overlapping seat volumes.",
            "C_GATE: exponent home CONDITIONAL on the same-path one-c-turn seat clock;",
            "seat clock and displaced-volume map PENDING",
        ]
    )

    six_pi_5 = 6.0 * math.pi**5
    raw_surplus = demanded_rotations - seats
    raw_candidate = 6.0 * math.pi**raw_surplus
    measured = read_measured_ratio()
    residual_ppm = (six_pi_5 - measured) / measured * 1.0e6
    raw_residual_pct = (raw_candidate - measured) / measured * 100.0
    lines.extend(
        [
            "",
            "ROUTE D — CORRESPONDENCE (opened after A-C)",
            f"unlocked_surplus_exponent={raw_surplus:.12f}",
            f"6*pi^unlocked_surplus={raw_candidate:.12f}",
            f"unlocked_candidate_residual_pct={raw_residual_pct:+.9f}",
            f"6*pi^5={six_pi_5:.12f}",
            f"measured_m_p_over_m_e={measured:.12f}",
            f"signed_residual_ppm={residual_ppm:.6f}",
            "",
            "DISPOSITION: WITHDRAWN",
            "The factor six is generated by the (2,3) compound recurrence.",
            "The 11-turn/6-turn subtraction is not a displaced-volume operator.",
            "Do not use this phase-lock diagnostic as support for 6*pi^5.",
            "See CORRECTED_VOLUME_ROUTE.md for the tube-volume construction.",
        ]
    )
    OUTPUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print("\n".join(lines))


if __name__ == "__main__":
    main()

