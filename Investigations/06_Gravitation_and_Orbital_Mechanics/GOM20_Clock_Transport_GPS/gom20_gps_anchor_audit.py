#!/usr/bin/env python3
"""Current fail-closed specification audit for GOM20 clock transport."""

from __future__ import annotations

import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
BASE = ROOT / "Investigations/06_Gravitation_and_Orbital_Mechanics/GOM20_Clock_Transport_GPS"
PROMPT = BASE / "PROMPT.md"
ASSESSMENT = BASE / "GOM20_ASSESSMENT.md"
LAWS = ROOT / "Engine/include/sdt/laws.hpp"
OUTPUT = BASE / "gom20_gps_anchor_audit_results.json"

DATA = {
    "nist_summary": ROOT / "Datasets/gps_clock_2026-08/raw/nist_putting_einstein_to_the_test.html",
    "gps_interface": ROOT / "Datasets/gps_clock_2026-08/raw/is_gps_200n.pdf",
    "nasa_gnss_intro": ROOT / "Datasets/gps_clock_2026-08/raw/nasa_2012_gnss_relativity_introduction.pdf",
    "navstar4_metadata": ROOT / "Datasets/gps_clock_2026-08/raw/nasa_1980_navstar4_metadata.json",
}


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def has(text: str, pattern: str) -> bool:
    return re.search(pattern, text, re.IGNORECASE) is not None


def main() -> None:
    prompt = PROMPT.read_text(encoding="utf-8")
    assessment = ASSESSMENT.read_text(encoding="utf-8")
    laws = LAWS.read_text(encoding="utf-8")
    combined = prompt + "\n" + assessment

    specification = {
        "signed_composition_equation": has(prompt, r"d\s*(?:tau|τ).*d\s*(?:t|tau|τ)\s*="),
        "reference_surface": has(prompt, r"reference (?:surface|radius)"),
        "coordinate_time_and_frames": has(prompt, r"coordinate time") and has(prompt, r"frame"),
        "ground_and_satellite_states": has(prompt, r"ground") and has(prompt, r"satellite"),
        "eccentric_orbit_treatment": has(prompt, r"eccentric"),
        "uncertainty_budget": has(prompt, r"uncertainty budget"),
        "direct_clock_series": has(prompt, r"time series|timestamps?"),
        "linear_engine_rate_bound": "depth_closure::clock_rate" in combined,
    }
    required_mechanism = {
        "polar_radius_koppa": has(combined, r"polar radius"),
        "baryon_volume_exclusion": has(combined, r"baryon.*volume"),
        "spation_shell_exclusion": has(combined, r"spation.shell"),
        "inverse_square_operation": has(combined, r"inverse.square"),
        "movement_budget": has(combined, r"movement.budget"),
    }

    legacy_present = "gravitational_time_dilation(" in laws
    linear_present = "clock_rate(double z)" in laws and "return 1.0 - z;" in laws
    missing = [name for name, ok in specification.items() if not ok]

    result = {
        "audit_date": "2026-08-14",
        "source_results": {
            name: {"path": str(path.relative_to(ROOT)).replace("\\", "/"), "sha256": sha256(path)}
            for name, path in DATA.items()
        },
        "specification_checks": specification,
        "missing_specification_items": missing,
        "required_recovery_ingredients": required_mechanism,
        "required_recovery_ingredients_complete": all(required_mechanism.values()),
        "canonical_depth_rules": {
            "legacy_square_root_api_present": legacy_present,
            "linear_rate_present": linear_present,
        },
        "qualified_direct_observation": False,
        "anchor_classification": "ENGINEERING_ONLY",
        "mechanism_classification": "PENDING_MECHANISM",
        "physical_model_verdict": "UNADJUDICATED",
        "fail_closed": bool(missing) or not all(required_mechanism.values()) or legacy_present or not linear_present,
    }
    OUTPUT.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    print(json.dumps(result, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()
