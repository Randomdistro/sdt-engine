"""Independent, source-gated audit of NP30 radius-contraction claims."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import math
import statistics
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[3]
AUDIT_DIRECTORY = Path(__file__).resolve().parent
MAGIC_NUMBERS = (2, 8, 20, 28, 50, 82, 126)
NEUTRON_CLOSURES = (8, 20, 28, 50, 82, 126)

INPUTS = {
    "radius_data": (
        ROOT / "Datasets/nuclear/IAEA_ground_states_radii.csv",
        900613,
        "8aee5dc431af1e35fcb49746387b83e927b3c300e7787defbda621a08212c795",
    ),
    "historical_radius_data_copy": (
        ROOT / "ATOMICUS/tools/_iaea_ground_states.csv",
        900613,
        "8aee5dc431af1e35fcb49746387b83e927b3c300e7787defbda621a08212c795",
    ),
    "compact_radius_data": (
        ROOT / "Datasets/nuclear/radii_compact.csv",
        955,
        "7bb8c087189db292d2ab7f33be138fecccb32dff35256c3df4bc290b06176fd2",
    ),
    "dataset_manifest": (
        ROOT / "Datasets/MANIFEST.md",
        13230,
        "f10ff411dada8654c00ffd30f3679186b2de8b5c355bb0abc8d2c224a1efbfe0",
    ),
    "np30_claim": (
        AUDIT_DIRECTORY / "NP30_INTERLEAVED_TREFOIL_COMPLETE.md",
        24316,
        "552531f64231f76890a329f29cd05b4843c074aed859316434c390e4ac472ef5",
    ),
    "contraction_reference": (
        ROOT / "ATOMICUS/reference/BOUNDARY_RADIUS_TRITON_CONTRACTION.md",
        20849,
        "79b076f6623aeec6744d36ec44f3fcaab10bf38a8e847bcc2f34e17025e05dfc",
    ),
    "historical_enrichment_tool": (
        ROOT / "ATOMICUS/tools/enrich_boundary_radius.py",
        7500,
        "87201001a38ed49f92e170b63a76880cbdbaafabbab9a11350c672eceb367b3a",
    ),
    "closure_invariant_reference": (
        ROOT / "ATOMICUS/reference/CLOSURE_KINK_ISOTONE_INVARIANT.md",
        3064,
        "0392a45530bfba8fc454f0774549e4bf107372e6d5dc4917f919b31ab29d76c5",
    ),
    "historical_closure_tool": (
        ROOT / "ATOMICUS/tools/closure_kink_isotone.py",
        8664,
        "cfb098f3f80bc4569dd728ccf0f07351e7a90aeec8fe4acdbfa222cb8586de65",
    ),
    "historical_closure_report": (
        ROOT / "ATOMICUS/reports/CLOSURE_KINK_ISOTONE_REPORT.md",
        2279,
        "b74d0997010701abba417c779c9a19b9b9c12cc7c58f8285f63b92479b223fab",
    ),
    "np32_downstream_precommit": (
        ROOT / "Investigations/05_Nuclear_Physics/NP32_Scission_Surface_Selection/NP32_PREDICT_PRECOMMIT_2026-07-25.md",
        3641,
        "9246b48fe0b5959bd2b0c4c44057eebf4d8060e3afe66fe5239fefbe8fb72b7b",
    ),
}


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def file_record(path: Path, expected_bytes: int, expected_hash: str) -> dict[str, Any]:
    observed_bytes = path.stat().st_size
    observed_hash = sha256(path)
    return {
        "path": path.relative_to(ROOT).as_posix(),
        "expected_bytes": expected_bytes,
        "observed_bytes": observed_bytes,
        "expected_sha256": expected_hash,
        "observed_sha256": observed_hash,
        "passed": observed_bytes == expected_bytes and observed_hash == expected_hash,
    }


def source_gate() -> dict[str, dict[str, Any]]:
    return {
        name: file_record(path, expected_bytes, expected_hash)
        for name, (path, expected_bytes, expected_hash) in INPUTS.items()
    }


def parse_radii() -> dict[tuple[int, int], float]:
    radii: dict[tuple[int, int], float] = {}
    source_path = INPUTS["radius_data"][0]
    with source_path.open(encoding="utf-8", newline="") as handle:
        reader = csv.DictReader(handle)
        required_columns = {"z", "n", "radius"}
        if reader.fieldnames is None or not required_columns.issubset(reader.fieldnames):
            raise ValueError(f"missing required columns: {sorted(required_columns)}")
        for record in reader:
            try:
                proton_count = int(record["z"])
                neutron_count = int(record["n"])
                radius = float(record["radius"])
            except (KeyError, TypeError, ValueError):
                continue
            if proton_count < 1 or neutron_count < 0 or not math.isfinite(radius) or radius <= 0.1:
                continue
            radii[(proton_count, neutron_count)] = radius
    return radii


def grammar_counts(proton_count: int, neutron_count: int) -> tuple[int, int]:
    deuteron_count = 2 * proton_count - neutron_count - 2
    triton_count = neutron_count - proton_count
    return deuteron_count, triton_count


def grammar_valid(proton_count: int, neutron_count: int) -> bool:
    deuteron_count, triton_count = grammar_counts(proton_count, neutron_count)
    return deuteron_count >= 0 and triton_count >= 0


def summarize(values: list[float]) -> dict[str, Any]:
    if not values:
        return {"count": 0}
    return {
        "count": len(values),
        "negative_count": sum(value < 0.0 for value in values),
        "negative_fraction": sum(value < 0.0 for value in values) / len(values),
        "mean_milli_fm": statistics.fmean(values),
        "median_milli_fm": statistics.median(values),
        "minimum_milli_fm": min(values),
        "maximum_milli_fm": max(values),
    }


def adjacent_step_reconstruction(radii: dict[tuple[int, int], float]) -> dict[str, Any]:
    groups: dict[str, list[float]] = {
        "all_grammar_adjacent_pairs": [],
        "endpoint_mass_at_least_40": [],
        "endpoint_mass_120_to_140": [],
        "neutron_closure_endpoint": [],
        "nonclosure_endpoint": [],
    }
    reduced_radius_groups: dict[str, list[float]] = {
        name: [] for name in groups
    }
    for (proton_count, neutron_count), radius in sorted(radii.items()):
        next_key = (proton_count, neutron_count + 1)
        next_radius = radii.get(next_key)
        if next_radius is None:
            continue
        if not grammar_valid(proton_count, neutron_count) or not grammar_valid(*next_key):
            continue
        current_mass = proton_count + neutron_count
        next_mass = current_mass + 1
        expected_next_radius = radius * math.cbrt(next_mass / current_mass)
        excess_milli_fm = (next_radius - expected_next_radius) * 1000.0
        reduced_radius_delta_milli_fm = (
            next_radius / math.cbrt(next_mass) - radius / math.cbrt(current_mass)
        ) * 1000.0
        categories = ["all_grammar_adjacent_pairs"]
        if next_mass >= 40:
            categories.append("endpoint_mass_at_least_40")
        if 120 <= next_mass <= 140:
            categories.append("endpoint_mass_120_to_140")
        if next_key[1] in NEUTRON_CLOSURES:
            categories.append("neutron_closure_endpoint")
        else:
            categories.append("nonclosure_endpoint")
        for category in categories:
            groups[category].append(excess_milli_fm)
            reduced_radius_groups[category].append(reduced_radius_delta_milli_fm)
    return {
        "historical_excess_over_A_cuberoot_step_milli_fm": {
            category: summarize(values) for category, values in groups.items()
        },
        "reduced_radius_delta_milli_fm": {
            category: summarize(values) for category, values in reduced_radius_groups.items()
        },
    }


def kink_milli_fm(radii: dict[tuple[int, int], float], proton_count: int, neutron_count: int) -> float | None:
    previous_radius = radii.get((proton_count, neutron_count - 2))
    current_radius = radii.get((proton_count, neutron_count))
    next_radius = radii.get((proton_count, neutron_count + 2))
    if previous_radius is None or current_radius is None or next_radius is None:
        return None
    return (current_radius - (previous_radius + next_radius) / 2.0) * 1000.0


def root_mean_square(values: list[float]) -> float:
    return math.sqrt(sum(value * value for value in values) / len(values))


def closure_kink_reconstruction(radii: dict[tuple[int, int], float]) -> dict[str, Any]:
    closure_summaries: dict[str, Any] = {}
    all_constant_wins = True
    for neutron_closure in NEUTRON_CLOSURES:
        members: list[dict[str, float | int]] = []
        for proton_count in range(2, 101):
            if neutron_closure - proton_count < 0:
                continue
            kink = kink_milli_fm(radii, proton_count, neutron_closure)
            if kink is None:
                continue
            members.append(
                {
                    "proton_count": proton_count,
                    "triton_count": neutron_closure - proton_count,
                    "kink_milli_fm": kink,
                }
            )
        summary: dict[str, Any] = {"members": members, "count": len(members)}
        if len(members) >= 2:
            kinks = [float(member["kink_milli_fm"]) for member in members]
            triton_counts = [float(member["triton_count"]) for member in members]
            constant_mean = statistics.fmean(kinks)
            constant_rms = root_mean_square([kink - constant_mean for kink in kinks])
            denominator = sum(count * count for count in triton_counts)
            proportional_coefficient = (
                sum(kink * count for kink, count in zip(kinks, triton_counts)) / denominator
                if denominator
                else 0.0
            )
            proportional_rms = root_mean_square(
                [kink - proportional_coefficient * count for kink, count in zip(kinks, triton_counts)]
            )
            constant_wins = constant_rms < proportional_rms
            summary.update(
                {
                    "mean_kink_milli_fm": constant_mean,
                    "constant_rms_milli_fm": constant_rms,
                    "proportional_rms_milli_fm": proportional_rms,
                    "constant_model_wins": constant_wins,
                }
            )
            all_constant_wins = all_constant_wins and constant_wins
        closure_summaries[str(neutron_closure)] = summary
    calculated_kinks = [
        float(member["kink_milli_fm"])
        for summary in closure_summaries.values()
        for member in summary["members"]
    ]
    return {
        "neutron_closure_input": list(NEUTRON_CLOSURES),
        "closures": closure_summaries,
        "all_calculated_closure_kinks_negative": all(kink < 0.0 for kink in calculated_kinks),
        "calculated_closure_kink_count": len(calculated_kinks),
        "constant_model_wins_every_adjudicable_closure": all_constant_wins,
    }


def mechanism_audit() -> dict[str, Any]:
    np30_text = INPUTS["np30_claim"][0].read_text(encoding="utf-8")
    reference_text = INPUTS["contraction_reference"][0].read_text(encoding="utf-8")
    closure_tool_text = INPUTS["historical_closure_tool"][0].read_text(encoding="utf-8")
    np32_text = INPUTS["np32_downstream_precommit"][0].read_text(encoding="utf-8")
    return {
        "historical_triton_count_definition": "n_t = N - Z" in reference_text,
        "historical_step_excess_program_present": "expected_next_radius" in closure_tool_text,
        "closure_list_hard_coded_in_historical_tool": "MAGIC = [8, 20, 28, 50, 82, 126]" in closure_tool_text,
        "closure_tool_explicitly_tests_constant_against_occupancy_proportional_kinks": "occupancy-proportional" in closure_tool_text,
        "np30_section_11_marked_measured_this_phase": "[measured, this phase]" in np30_text,
        "np32_uses_n82_z50_lock_as_measured_session_output": "measured this session" in np32_text,
        "closure_location_status": "EMPIRICALLY_IMPORTED_MAGIC_LIST",
        "mechanism_status": "NO_NATIVE_GEOMETRIC_PREDICTOR_OF_CLOSURE_LOCATION_PRESENT",
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--output",
        type=Path,
        default=AUDIT_DIRECTORY / "np30_contraction_root_audit_results.json",
    )
    arguments = parser.parse_args()
    source_records = source_gate()
    if not all(record["passed"] for record in source_records.values()):
        result = {
            "audit_status": "PROVENANCE_BLOCKED",
            "source_records": source_records,
            "raw_csv_parsed": False,
        }
        arguments.output.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        return 2
    radii = parse_radii()
    step_reconstruction = adjacent_step_reconstruction(radii)
    kink_reconstruction = closure_kink_reconstruction(radii)
    result = {
        "audit_status": "COMPLETE",
        "source_gate": "PASS",
        "source_records": source_records,
        "valid_observational_radius_rows": len(radii),
        "grammar_valid_radius_rows": sum(
            grammar_valid(proton_count, neutron_count)
            for proton_count, neutron_count in radii
        ),
        "adjacent_step_reconstruction": step_reconstruction,
        "closure_kink_reconstruction": kink_reconstruction,
        "mechanism_audit": mechanism_audit(),
        "classification": {
            "observational_status": "RADIUS_REGULARITIES_RECONSTRUCTED_DESCRIPTIVELY",
            "closure_location_status": "CLOSURE_LOCATION_EMPIRICALLY_IMPORTED",
            "interleave_mechanism_status": "UNADJUDICATED_NO_NATIVE_CLOSURE_LOCATION_PREDICTOR",
            "np32_anchor_status": "NOT_AN_INDEPENDENTLY_DERIVED_SDT_ANCHOR",
        },
    }
    arguments.output.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
