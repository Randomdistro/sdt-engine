#!/usr/bin/env python3
"""Fail-closed provenance and specification audit for GOM20's GPS anchor."""

from __future__ import annotations

import hashlib
import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]
PROMPT = ROOT / "Investigations/06_Gravitation_and_Orbital_Mechanics/GOM20_Clock_Transport_GPS/PROMPT.md"
MECHANISM_AMENDMENT = ROOT / "Investigations/06_Gravitation_and_Orbital_Mechanics/GOM20_Clock_Transport_GPS/GOM20_GPS_MECHANISM_AMENDMENT_01.md"
CANONICAL_LAWS = ROOT / "Engine/include/sdt/laws.hpp"
GOM22_ASSESSMENT = ROOT / "Investigations/06_Gravitation_and_Orbital_Mechanics/GOM22_Shapiro_Velocity_Profile/GOM22_ASSESSMENT_2026-07-30.md"
BENCHMARK_SUITE = ROOT / "Benchmarks/B01_B25/benchmarks_suite.cpp"
OUTPUT = ROOT / "Investigations/06_Gravitation_and_Orbital_Mechanics/GOM20_Clock_Transport_GPS/gom20_gps_anchor_audit_results.json"
SOURCES = {
    "nist_summary": (
        ROOT / "Datasets/gps_clock_2026-08/raw/nist_putting_einstein_to_the_test.html",
        "1ba074908c7261f2f515edd96505c06f8640836ff47ac5f23902a8cf83220baf",
        "EXPLANATORY_SECONDARY",
    ),
    "gps_interface": (
        ROOT / "Datasets/gps_clock_2026-08/raw/is_gps_200n.pdf",
        "54ec544bfe7e6acd97daaa1de0ca248e5abec6b418f23c1a69991e5c7bcf749a",
        "ENGINEERING_CONFIGURATION",
    ),
    "nasa_gnss_intro": (
        ROOT / "Datasets/gps_clock_2026-08/raw/nasa_2012_gnss_relativity_introduction.pdf",
        "402b87a7193e929ec5316e446ada53aa2d7c9daa60877a6717605034318b109b",
        "EXPLANATORY_ENGINEERING",
    ),
    "navstar4_metadata": (
        ROOT / "Datasets/gps_clock_2026-08/raw/nasa_1980_navstar4_metadata.json",
        "0255b566bca1011144ed8b76afa94489bdf93842f2de0bc78ad0d643697cb467",
        "MODEL_PROCESSED_OBSERVATION",
    ),
}
CANONICAL_AUTHORITY_SOURCES = {
    "canonical_laws": (CANONICAL_LAWS, "ae41f3cb12e567cb90b5518795e62da1dc7fa516536739c56a7fcc54d255835b"),
    "gom22_assessment": (GOM22_ASSESSMENT, "2361629a18296d7bef4009f4118ac3f2e07f9d5b4dc41f96629c264fd0356de5"),
    "benchmark_suite": (BENCHMARK_SUITE, "ec33026c916a051731a2ceabdfe9559c5e3137a1c3717135a7f0d24ed3c981bf"),
    "gom20_mechanism_amendment": (MECHANISM_AMENDMENT, "d772bcf1190b2acec57f8f055f7740f89579be2a7907505ff4923d5889b7f84c"),
}
COMPILED_SOURCE_ROOTS = (
    "Benchmarks",
    "Compiler",
    "Experiments",
    "Investigations",
    "Papers",
    "Theory",
    "Laws",
    "Engine",
    "Release",
)
COMPILED_SOURCE_EXTENSIONS = {".cpp", ".cc", ".cxx", ".hpp", ".h"}

SECONDS_PER_DAY = 86_400
GPS_INTERFACE_FRACTIONAL_OFFSET = -4.4647e-10
GOM20_NET_CLAIM_US_PER_DAY = 38.7
GOM20_TOLERANCE_US_PER_DAY = 0.1


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def phrase_present(text: str, phrase: str) -> bool:
    prefix = r"(?<!\w)" if phrase[0].isalnum() else ""
    suffix = r"(?!\w)" if phrase[-1].isalnum() else ""
    return re.search(prefix + re.escape(phrase) + suffix, text, re.IGNORECASE) is not None


def compiled_callers(qualified_name: str) -> list[str]:
    pattern = re.compile(r"(?<![\w:])" + re.escape(qualified_name) + r"\s*\(")
    callers = []
    for root_name in COMPILED_SOURCE_ROOTS:
        root = ROOT / root_name
        for path in root.rglob("*"):
            if path.suffix.lower() not in COMPILED_SOURCE_EXTENSIONS:
                continue
            if pattern.search(path.read_text(encoding="utf-8", errors="replace")):
                callers.append(str(path.relative_to(ROOT)).replace("\\", "/"))
    return sorted(callers)


def main() -> None:
    prompt_text = PROMPT.read_text(encoding="utf-8")
    mechanism_text = MECHANISM_AMENDMENT.read_text(encoding="utf-8")
    canonical_laws_text = CANONICAL_LAWS.read_text(encoding="utf-8")
    gom22_assessment_text = GOM22_ASSESSMENT.read_text(encoding="utf-8")
    benchmark_suite_text = BENCHMARK_SUITE.read_text(encoding="utf-8")
    source_results = {}
    for name, (path, expected_hash, evidence_class) in SOURCES.items():
        actual_hash = sha256(path)
        source_results[name] = {
            "path": str(path.relative_to(ROOT)).replace("\\", "/"),
            "sha256": actual_hash,
            "hash_matches_manifest": actual_hash == expected_hash,
            "evidence_class": evidence_class,
        }
    canonical_authority_results = {}
    for name, (path, expected_hash) in CANONICAL_AUTHORITY_SOURCES.items():
        actual_hash = sha256(path)
        canonical_authority_results[name] = {
            "path": str(path.relative_to(ROOT)).replace("\\", "/"),
            "sha256": actual_hash,
            "hash_matches_frozen_authority_source": actual_hash == expected_hash,
        }

    configuration_compensation_us_per_day = (
        -GPS_INTERFACE_FRACTIONAL_OFFSET * SECONDS_PER_DAY * 1_000_000
    )
    target_delta_us_per_day = (
        GOM20_NET_CLAIM_US_PER_DAY - configuration_compensation_us_per_day
    )

    specification_checks = {
        "states_depth_relation": phrase_present(prompt_text, "z =")
        and phrase_present(prompt_text, "/r"),
        "states_motion_term": phrase_present(prompt_text, "v²"),
        "states_exact_composition_rule": any(
            phrase_present(prompt_text, phrase)
            for phrase in ("clock_rate(", "time_dilation(", "dτ/dt =", "dÏ„/dt =")
        ),
        "states_coordinate_time_scale": any(
            phrase_present(prompt_text, phrase)
            for phrase in ("gps time", "eci", "ecef", "coordinate time", "proper time")
        ),
        "states_ground_velocity_definition": any(
            phrase_present(prompt_text, phrase)
            for phrase in ("earth rotation", "ground velocity", "station velocity")
        ),
        "states_eccentric_orbit_treatment": phrase_present(prompt_text, "eccentric"),
        "contains_direct_clock_series": any(
            phrase_present(prompt_text, phrase)
            for phrase in ("time series", "timestamp", "all an", "uncertainty budget")
        ),
        "binds_gom20_to_canonical_depth_rate": any(
            phrase_present(prompt_text + mechanism_text, phrase)
            for phrase in ("gravitational_time_dilation", "depth_closure::clock_rate")
        ),
    }
    missing = [name for name, present in specification_checks.items() if not present]
    source_hashes_valid = all(
        item["hash_matches_manifest"] for item in source_results.values()
    )
    canonical_authority_hashes_valid = all(
        item["hash_matches_frozen_authority_source"]
        for item in canonical_authority_results.values()
    )
    qualified_direct_observation = False
    canonical_depth_rules = {
        "t16_square_root_rate_present": "return std::sqrt(1.0 - z * R / r);"
        in canonical_laws_text,
        "depth_closure_linear_rate_present": "return 1.0 - z;" in canonical_laws_text,
    }
    compiled_clock_rate_callers = {
        "legacy_square_root_rate": compiled_callers(
            "law_V::gravitational_time_dilation"
        ),
        "repaired_linear_rate": compiled_callers("depth_closure::clock_rate"),
    }
    canonical_authority_checks = {
        "legacy_square_root_rate_present": canonical_depth_rules[
            "t16_square_root_rate_present"
        ],
        "repaired_linear_rate_present": canonical_depth_rules[
            "depth_closure_linear_rate_present"
        ],
        "gom22_repair_marked_applied": phrase_present(
            gom22_assessment_text, "APPLIED to canon"
        ),
        "benchmark_uses_repaired_linear_rate": "depth_closure::clock_rate("
        in benchmark_suite_text,
        "gom20_explicit_rate_binding": specification_checks[
            "binds_gom20_to_canonical_depth_rate"
        ],
    }
    if (
        all(
            canonical_authority_checks[name]
            for name in (
                "legacy_square_root_rate_present",
                "repaired_linear_rate_present",
                "gom22_repair_marked_applied",
                "benchmark_uses_repaired_linear_rate",
            )
        )
        and not canonical_authority_checks["gom20_explicit_rate_binding"]
        and not compiled_clock_rate_callers["legacy_square_root_rate"]
        and compiled_clock_rate_callers["repaired_linear_rate"]
    ):
        canonical_depth_law_state = (
            "REPAIRED_LINEAR_ENGINE_DEFAULT_WITH_GOM20_BINDING_ABSENT"
        )
    else:
        canonical_depth_law_state = "UNRESOLVED"
    required_recovery_ingredients = {
        "polar_radius_for_koppa": phrase_present(mechanism_text, "polar radius"),
        "baryon_count_volume_exclusion": phrase_present(
            mechanism_text, "baryon count and volume"
        ),
        "spation_shell_exclusion": phrase_present(
            mechanism_text, "spation shell"
        ),
        "inverse_square_falloff": phrase_present(mechanism_text, "inverse-square"),
        "movement_budget": phrase_present(mechanism_text, "movement-budget"),
    }

    result = {
        "audit_date": "2026-08-09",
        "audit_revision": "canonical-authority-correction",
        "source_hashes_valid": source_hashes_valid,
        "source_results": source_results,
        "canonical_authority_hashes_valid": canonical_authority_hashes_valid,
        "canonical_authority_results": canonical_authority_results,
        "configuration_calculation": {
            "fractional_frequency_offset": GPS_INTERFACE_FRACTIONAL_OFFSET,
            "seconds_per_day": SECONDS_PER_DAY,
            "compensation_magnitude_us_per_day": configuration_compensation_us_per_day,
            "gom20_net_claim_us_per_day": GOM20_NET_CLAIM_US_PER_DAY,
            "difference_us_per_day": target_delta_us_per_day,
            "exceeds_gom20_declared_tolerance": abs(target_delta_us_per_day)
            > GOM20_TOLERANCE_US_PER_DAY,
            "interpretation": "engineering configuration arithmetic, not a clock observation",
        },
        "specification_checks": specification_checks,
        "missing_specification_items": missing,
        "canonical_depth_rules": canonical_depth_rules,
        "compiled_clock_rate_callers": compiled_clock_rate_callers,
        "canonical_authority_checks": canonical_authority_checks,
        "canonical_depth_law_state": canonical_depth_law_state,
        "mechanism_amendment_path": str(MECHANISM_AMENDMENT.relative_to(ROOT)).replace(
            "\\", "/"
        ),
        "required_recovery_ingredients": required_recovery_ingredients,
        "required_recovery_ingredients_complete": all(
            required_recovery_ingredients.values()
        ),
        "qualified_direct_observation": qualified_direct_observation,
        "anchor_classification": "ENGINEERING_ONLY",
        "mechanism_classification": "PENDING_MECHANISM",
        "physical_model_verdict": "UNADJUDICATED",
        "fail_closed_reason": (
            "No qualified direct observation is present, and the GOM20 seed does not "
            "supply a unique rate-composition rule or all required state definitions; "
            "it does not bind its composition rule to the repair-marked linear engine "
            "default."
        ),
    }
    OUTPUT.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    print(json.dumps(result, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()
