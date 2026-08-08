#!/usr/bin/env python3
"""Independent, zero-fit reproduction audit of NP21's geometric floor claim."""

from __future__ import annotations

import hashlib
import json
import math
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]
CANONICAL_AME = ROOT / "Datasets/nuclear/AME2020_mass_excess.txt"
LEGACY_AME = ROOT / (
    "Investigations/04_Atomic_Physics_and_Spectroscopy/"
    "APS03_Universal_Drafting_Crossover/mass_1.mas20.txt"
)
NP21_INSTRUMENT = ROOT / (
    "Investigations/05_Nuclear_Physics/"
    "NP21_Binding_Curve_Resistance_Landscape/np21_landscape.py"
)
NUCLEAR_HEADER = ROOT / "Engine/include/sdt/nuclear.hpp"
OUTPUT = ROOT / (
    "Investigations/05_Nuclear_Physics/"
    "NP21_AME2020_Geometric_Floor_Reproduction/np21_ame2020_audit_results.json"
)

FROZEN_SOURCES = {
    "canonical_ame2020": (
        CANONICAL_AME,
        "e8599c6d7f724fac91934e59f1b9de8fb8f63e820f4b39456b790665ed2a3307",
        "EVALUATED_EXPERIMENTAL_TARGET",
    ),
    "legacy_ame_duplicate": (
        LEGACY_AME,
        "e8599c6d7f724fac91934e59f1b9de8fb8f63e820f4b39456b790665ed2a3307",
        "DUPLICATE_SOURCE_HYGIENE_CHECK",
    ),
    "np21_reference_instrument": (
        NP21_INSTRUMENT,
        "38aeee91edcca845253a6c039eb270da3bf3d358f913aeda26bf397e75b8827f",
        "FROZEN_HYPOTHESIS_REFERENCE",
    ),
    "nuclear_header": (
        NUCLEAR_HEADER,
        "606f2fdf2e86a05500d9b76d79964e652870eb401fc470da033a6c9b4ce04791",
        "FROZEN_SCAN_DOMAIN",
    ),
}
ALPHA = 1.0 / 137.035999084
GEOMETRIC_COEFFICIENTS = {"surface": 6.0, "spread": ALPHA, "asymmetry": 1.0}
FLOOR_WINDOW = range(54, 65)


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def source_results() -> dict[str, dict[str, str | bool | int]]:
    results = {}
    for name, (path, expected_hash, evidence_class) in FROZEN_SOURCES.items():
        actual_hash = sha256(path)
        results[name] = {
            "path": str(path.relative_to(ROOT)).replace("\\", "/"),
            "bytes": path.stat().st_size,
            "sha256": actual_hash,
            "hash_matches_pre_registration": actual_hash == expected_hash,
            "evidence_class": evidence_class,
        }
    return results


def load_binding_per_nucleon(path: Path) -> dict[tuple[int, int], float]:
    binding_by_nuclide = {}
    for line in path.read_text(encoding="latin-1").splitlines():
        if len(line) < 25:
            continue
        try:
            proton_number = int(line[9:14])
            mass_number = int(line[14:19])
        except ValueError:
            continue
        tokens = line[23:].replace("#", " ").replace("*", " ").split()
        beta_index = next(
            (
                index
                for index, token in enumerate(tokens)
                if token in {"B-", "B+", "B", "B-x"}
            ),
            None,
        )
        if beta_index is None or beta_index < 3:
            continue
        try:
            binding_kev = float(tokens[beta_index - 2])
        except ValueError:
            continue
        if 0.0 < binding_kev < 12000.0:
            binding_by_nuclide[(proton_number, mass_number)] = binding_kev / 1000.0
    return binding_by_nuclide


def load_natural_basis(path: Path) -> set[tuple[int, int]]:
    header_text = path.read_text(encoding="latin-1")
    match = re.search(r"natural_basis\[287\]\s*=\s*\{(.*?)\};", header_text, re.DOTALL)
    if match is None:
        raise ValueError("natural_basis[287] was not found in the frozen nuclear header")
    return {
        (int(proton_number), int(mass_number))
        for proton_number, mass_number in re.findall(
            r"\{\s*(\d+)\s*,\s*(\d+)\s*\}", match.group(1)
        )
    }


def alpha_grammar(proton_number: int, mass_number: int) -> tuple[int, int, bool]:
    deuteron_count = 3 * proton_number - mass_number - 2
    triton_count = mass_number - 2 * proton_number
    return deuteron_count, triton_count, deuteron_count >= 0 and triton_count >= 0


def resistance_per_nucleon(proton_number: int, mass_number: int) -> float:
    deuteron_count, triton_count, _ = alpha_grammar(proton_number, mass_number)
    surface_term = GEOMETRIC_COEFFICIENTS["surface"] * mass_number ** (-1.0 / 3.0)
    spread_term = (
        GEOMETRIC_COEFFICIENTS["spread"]
        * proton_number
        * (proton_number - 1)
        * mass_number ** (-4.0 / 3.0)
    )
    asymmetry_term = (
        GEOMETRIC_COEFFICIENTS["asymmetry"]
        * (triton_count - deuteron_count) ** 2
        / mass_number**2
    )
    return surface_term + spread_term + asymmetry_term


def average_ranks(values: list[float]) -> list[float]:
    ordered_indices = sorted(range(len(values)), key=lambda index: values[index])
    ranks = [0.0] * len(values)
    start_index = 0
    while start_index < len(values):
        end_index = start_index
        while (
            end_index + 1 < len(values)
            and values[ordered_indices[end_index + 1]] == values[ordered_indices[start_index]]
        ):
            end_index += 1
        average_rank = (start_index + end_index) / 2.0 + 1.0
        for ordered_index in range(start_index, end_index + 1):
            ranks[ordered_indices[ordered_index]] = average_rank
        start_index = end_index + 1
    return ranks


def spearman(first: list[float], second: list[float]) -> float:
    first_ranks = average_ranks(first)
    second_ranks = average_ranks(second)
    first_mean = sum(first_ranks) / len(first_ranks)
    second_mean = sum(second_ranks) / len(second_ranks)
    numerator = sum(
        (first_ranks[index] - first_mean) * (second_ranks[index] - second_mean)
        for index in range(len(first_ranks))
    )
    first_norm = math.sqrt(sum((value - first_mean) ** 2 for value in first_ranks))
    second_norm = math.sqrt(sum((value - second_mean) ** 2 for value in second_ranks))
    return numerator / (first_norm * second_norm)


def main() -> None:
    sources = source_results()
    hashes_valid = all(
        source["hash_matches_pre_registration"] for source in sources.values()
    )
    duplicate_equal = sources["canonical_ame2020"]["sha256"] == sources[
        "legacy_ame_duplicate"
    ]["sha256"]
    if not hashes_valid or not duplicate_equal:
        result = {
            "audit_date": "2026-08-09",
            "source_hashes_valid": hashes_valid,
            "duplicate_equal_to_canonical": duplicate_equal,
            "source_results": sources,
            "classification": "PROVENANCE_CONFLICT_NO_NUMERIC_REPRODUCTION",
            "empirical_sdt_verdict": "UNADJUDICATED",
        }
        OUTPUT.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        print(json.dumps(result, indent=2, sort_keys=True))
        return

    binding_by_nuclide = load_binding_per_nucleon(CANONICAL_AME)
    natural_basis = load_natural_basis(NUCLEAR_HEADER)
    rows = []
    for proton_number, mass_number in sorted(natural_basis):
        deuteron_count, triton_count, valid = alpha_grammar(proton_number, mass_number)
        if not valid or not 2 <= proton_number <= 92:
            continue
        binding_energy = binding_by_nuclide.get((proton_number, mass_number))
        if binding_energy is None:
            continue
        rows.append(
            {
                "z": proton_number,
                "a": mass_number,
                "n_d": deuteron_count,
                "n_t": triton_count,
                "binding_mev_per_nucleon": binding_energy,
                "resistance": resistance_per_nucleon(proton_number, mass_number),
            }
        )
    if not rows:
        raise RuntimeError("no alpha-valid natural-basis rows were parsed from AME2020")

    floor_row = min(rows, key=lambda row: row["resistance"])
    diagnostic_spearman = spearman(
        [-row["resistance"] for row in rows],
        [row["binding_mev_per_nucleon"] for row in rows],
    )
    floor_in_window = floor_row["a"] in FLOOR_WINDOW
    result = {
        "audit_date": "2026-08-09",
        "source_hashes_valid": True,
        "duplicate_equal_to_canonical": True,
        "source_results": sources,
        "scan_counts": {
            "ame_binding_per_nucleon_rows": len(binding_by_nuclide),
            "natural_basis_rows": len(natural_basis),
            "alpha_valid_observed_rows": len(rows),
        },
        "target_availability": {
            "fe_56": binding_by_nuclide.get((26, 56)),
            "ni_62": binding_by_nuclide.get((28, 62)),
        },
        "fixed_zero_fit_functional": {
            "surface_coefficient": GEOMETRIC_COEFFICIENTS["surface"],
            "spread_coefficient": GEOMETRIC_COEFFICIENTS["spread"],
            "asymmetry_coefficient": GEOMETRIC_COEFFICIENTS["asymmetry"],
        },
        "floor": {
            "z": floor_row["z"],
            "a": floor_row["a"],
            "resistance_per_nucleon": floor_row["resistance"],
            "distance_from_fe_56_a": abs(floor_row["a"] - 56),
            "in_fe_ni_window": floor_in_window,
        },
        "diagnostic_spearman_negative_resistance_vs_ame_binding": diagnostic_spearman,
        "classification": (
            "GEOMETRIC_FLOOR_SURVIVES_THIS_REPRODUCTION"
            if floor_in_window
            else "GEOMETRIC_FLOOR_KILL_CONFIRMED"
        ),
        "empirical_sdt_verdict": "NARROW_CLAIM_ADJUDICATED_ONLY",
        "excluded_actions": [
            "coefficient_fit",
            "exponent_change",
            "coefficient_ratio_sweep",
            "semi_empirical_mass_formula_input",
            "standard_framework_rejection_rule",
        ],
    }
    OUTPUT.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    print(json.dumps(result, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()
