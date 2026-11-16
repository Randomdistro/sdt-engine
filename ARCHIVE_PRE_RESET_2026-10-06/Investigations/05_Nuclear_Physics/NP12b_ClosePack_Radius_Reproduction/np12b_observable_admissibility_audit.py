"""Source-gated replication and observable-admissibility audit for NP12b."""

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
RADIUS_DATA = ROOT / "Datasets/nuclear/IAEA_ground_states_radii.csv"

INPUTS = {
    "radius_data": (
        RADIUS_DATA,
        900613,
        "8aee5dc431af1e35fcb49746387b83e927b3c300e7787defbda621a08212c795",
    ),
    "canonical_law": (
        ROOT / "Engine/include/sdt/laws.hpp",
        97482,
        "ae41f3cb12e567cb90b5518795e62da1dc7fa516536739c56a7fcc54d255835b",
    ),
    "historical_pre_registration": (
        AUDIT_DIRECTORY / "NP12b_PRE_REGISTRATION.md",
        3635,
        "dda4c4a5c3ebcc63f41eda47b85dab6297d9ab803a813d167ce72530ca086267",
    ),
    "historical_assessment": (
        AUDIT_DIRECTORY / "NP12b_ASSESSMENT.md",
        2288,
        "fb22d0308d53e9ae9b5cead86c95743ae055651d860508e017754c5f2a21feff",
    ),
    "historical_instrument": (
        AUDIT_DIRECTORY / "np12b_closepack_radius_audit.cpp",
        7375,
        "8e9c2e8362858a6abc7bf398c46ba61f5ae93fc83752c8be2de74e4d5644ce16",
    ),
    "dataset_manifest": (
        ROOT / "Datasets/MANIFEST.md",
        13230,
        "f10ff411dada8654c00ffd30f3679186b2de8b5c355bb0abc8d2c224a1efbfe0",
    ),
    "prior_np12_model": (
        ROOT / "Investigations/05_Nuclear_Physics/NP12_Nuclear_Charge_Radius_Scaling/np12_radius_scaling.py",
        7044,
        "a2401e9aa0c1231ce02422f61971fedf95ef7948090f6c5fbc6dd87e7c09c21a",
    ),
    "prior_np12_verdict": (
        ROOT / "Investigations/05_Nuclear_Physics/NP12_Nuclear_Charge_Radius_Scaling/NP12_VERDICT.md",
        6383,
        "547d962d2f663ae3c679b7b5ebc625ee455fdfda973213450a31f82a3b552bb7",
    ),
}

PROTON_RADIUS_FM = 0.8414
PACKING_DENOMINATOR = 4.242640687119285


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


def direct_radius_fm(mass_number: int) -> float:
    packing_fraction = math.pi / PACKING_DENOMINATOR
    return PROTON_RADIUS_FM * math.cbrt(mass_number / packing_fraction)


def relative_error(predicted_radius: float, measured_radius: float) -> float:
    return predicted_radius / measured_radius - 1.0


def rms(values: list[float]) -> float:
    if not values:
        raise ValueError("empty metric set")
    return math.sqrt(sum(value * value for value in values) / len(values))


def reproduce_direct_proxy() -> dict[str, Any]:
    expected_columns = {"z", "n", "radius"}
    all_errors: list[float] = []
    light_errors: list[float] = []
    middle_errors: list[float] = []
    heavy_errors: list[float] = []
    adjudication_errors: list[float] = []
    parsed_rows = 0
    skipped_rows = 0
    with RADIUS_DATA.open(encoding="utf-8", newline="") as handle:
        reader = csv.DictReader(handle)
        if reader.fieldnames is None or not expected_columns.issubset(reader.fieldnames):
            raise ValueError(f"missing required CSV columns: {sorted(expected_columns)}")
        for record in reader:
            try:
                proton_count = int(record["z"])
                neutron_count = int(record["n"])
                measured_radius = float(record["radius"])
            except (KeyError, TypeError, ValueError):
                skipped_rows += 1
                continue
            if (
                proton_count < 1
                or neutron_count < 0
                or not math.isfinite(measured_radius)
                or measured_radius <= 0.1
            ):
                skipped_rows += 1
                continue
            mass_number = proton_count + neutron_count
            predicted_radius = direct_radius_fm(mass_number)
            error = relative_error(predicted_radius, measured_radius)
            all_errors.append(error)
            if mass_number < 16:
                light_errors.append(error)
            elif mass_number < 40:
                middle_errors.append(error)
            else:
                heavy_errors.append(error)
            if mass_number >= 16:
                adjudication_errors.append(error)
            parsed_rows += 1
    return {
        "parsed_rows": parsed_rows,
        "skipped_rows": skipped_rows,
        "formula": "R_p * cbrt(A / (pi / 4.242640687119285))",
        "proton_radius_fm": PROTON_RADIUS_FM,
        "metrics": {
            "all": {"count": len(all_errors), "rms_relative": rms(all_errors)},
            "mass_less_than_16": {"count": len(light_errors), "rms_relative": rms(light_errors)},
            "mass_16_to_39": {"count": len(middle_errors), "rms_relative": rms(middle_errors)},
            "mass_at_least_40": {"count": len(heavy_errors), "rms_relative": rms(heavy_errors)},
            "adjudication_mass_at_least_16": {
                "count": len(adjudication_errors),
                "rms_relative": rms(adjudication_errors),
                "mean_absolute_relative": statistics.fmean(abs(error) for error in adjudication_errors),
                "median_absolute_relative": statistics.median(abs(error) for error in adjudication_errors),
                "maximum_absolute_relative": max(abs(error) for error in adjudication_errors),
            },
        },
    }


def observable_audit() -> dict[str, Any]:
    law_text = INPUTS["canonical_law"][0].read_text(encoding="utf-8")
    pre_registration_text = INPUTS["historical_pre_registration"][0].read_text(encoding="utf-8")
    assessment_text = INPUTS["historical_assessment"][0].read_text(encoding="utf-8")
    prior_model_text = INPUTS["prior_np12_model"][0].read_text(encoding="utf-8")
    prior_verdict_text = INPUTS["prior_np12_verdict"][0].read_text(encoding="utf-8")
    canonical_boundary_label = "Nuclear boundary radius" in law_text
    target_rms_label = "RMS charge radii" in pre_registration_text
    assessment_discloses_mismatch = "IAEA column is RMS charge radius" in assessment_text
    prior_surface_limit = "SDT pack, surface" in prior_model_text and "surface-charge limit" in prior_verdict_text
    prior_uniform_mapping = "math.sqrt(3/5) * R_P" in prior_model_text
    prior_underived_strength = "periphery-charge strength is un-derived" in prior_verdict_text
    native_map = False
    return {
        "canonical_formula_output_labeled_boundary_radius": canonical_boundary_label,
        "historical_target_labeled_rms_charge_radius": target_rms_label,
        "historical_assessment_discloses_observable_difference": assessment_discloses_mismatch,
        "prior_np12_has_uniform_limit_conversion": prior_uniform_mapping,
        "prior_np12_identifies_direct_form_as_surface_charge_limit": prior_surface_limit,
        "prior_np12_records_surface_strength_as_underived": prior_underived_strength,
        "native_boundary_to_rms_map_derived_and_executed_in_audited_path": native_map,
        "physical_interpretation": "DIRECT_PROXY_DEPENDS_ON_UNDERIVED_SURFACE_CHARGE_LIMIT"
        if prior_surface_limit and prior_underived_strength and not native_map
        else "OBSERVABLE_MAPPING_STATUS_REQUIRES_MANUAL_REVIEW",
    }


def historical_numeric_status(adjudication_rms: float) -> str:
    if adjudication_rms <= 0.08:
        return "CLOSE_PACK_RADIUS_SURVIVES_THIS_REPRODUCTION"
    if adjudication_rms > 0.20:
        return "CLOSE_PACK_RADIUS_EXCLUDED"
    return "CLOSE_PACK_RADIUS_UNADJUDICATED"


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--output",
        type=Path,
        default=AUDIT_DIRECTORY / "np12b_observable_admissibility_audit_results.json",
    )
    arguments = parser.parse_args()
    source_records = source_gate()
    source_gate_passed = all(record["passed"] for record in source_records.values())
    if not source_gate_passed:
        result = {
            "audit_status": "PROVENANCE_BLOCKED",
            "source_records": source_records,
            "raw_csv_parsed": False,
        }
        arguments.output.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        return 2
    proxy = reproduce_direct_proxy()
    observables = observable_audit()
    adjudication_rms = proxy["metrics"]["adjudication_mass_at_least_16"]["rms_relative"]
    numerical_status = historical_numeric_status(adjudication_rms)
    result = {
        "audit_status": "COMPLETE",
        "source_gate": "PASS",
        "source_records": source_records,
        "direct_proxy_reproduction": proxy,
        "historical_numerical_gate": {
            "rms_relative": adjudication_rms,
            "historical_status": numerical_status,
        },
        "observable_audit": observables,
        "classification": {
            "direct_proxy_status": "REPRODUCED",
            "physical_boundary_law_verdict": "UNADJUDICATED",
            "required_correction": "PROXY_REPRODUCED_UNDER_UNDERIVED_SURFACE_CHARGE_MAPPING",
        },
    }
    arguments.output.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
