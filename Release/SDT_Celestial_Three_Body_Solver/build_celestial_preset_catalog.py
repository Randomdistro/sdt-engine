#!/usr/bin/env python3
"""Build persistent celestial scenarios and their solver-driven explainer tours."""

from __future__ import annotations

import json
import math
from pathlib import Path


ROOT = Path(__file__).resolve().parent
CASE_DIRECTORIES = (
    ROOT / "examples" / "celestial",
    ROOT / "web" / "cases" / "celestial",
)


def scenario(
    identifier: str,
    label: str,
    filename: str,
    classification: str,
    explainer: str,
) -> dict[str, str]:
    return {
        "id": identifier,
        "label": label,
        "file": filename,
        "classification": classification,
        "explainer": explainer,
    }


SCENARIOS = (
    scenario("jpl-sun-earth-moon", "Sun · Earth · Moon (DE441 J2000)", "jpl-sun-earth-moon-j2000.sdtcase.json", "OBSERVED comparison", "Observed J2000 channel geometry"),
    scenario("sun-earth-spacecraft", "Sun · Earth · L1 spacecraft", "sun-earth-spacecraft.sdtcase.json", "COMPUTED", "L1 spacecraft occlusion trace"),
    scenario("sun-jupiter-trojan", "Sun · Jupiter · L4 Trojan", "sun-jupiter-trojan.sdtcase.json", "COMPUTED", "Trojan triangle influence trace"),
    scenario("restricted-l4", "Restricted L4 runner", "restricted-runner.sdtcase.json", "DERIVED", "Restricted L4 balance trace"),
    scenario("stable-lagrange", "Unequal Lagrange triangle", "stable-lagrange.sdtcase.json", "DERIVED", "Unequal Lagrange balance trace"),
    scenario("figure-eight", "Equal-baryon figure-eight", "figure-eight.sdtcase.json", "DERIVED", "Figure-eight retarded response trace"),
    scenario("earth-tail-flyby-controlled", "Earth flyby · controlled transverse", "earth-tail-flyby-controlled.sdtcase.json", "PENDING non-driving", "Controlled Earth-flyby tail diagnostic"),
    scenario("figure-eight-reversed", "Figure-eight · reversed", "figure-eight-reversed.sdtcase.json", "COMPUTED", "Time-reversed figure-eight trace"),
    scenario("figure-eight-inclined-30", "Figure-eight · inclined 30°", "figure-eight-inclined-30.sdtcase.json", "COMPUTED", "Inclined figure-eight trace"),
    scenario("figure-eight-rk4", "Figure-eight · RK4 verification", "figure-eight-rk4.sdtcase.json", "COMPUTED", "Integrator cross-check trace"),
    scenario("figure-eight-translated", "Figure-eight · translated frame", "figure-eight-translated.sdtcase.json", "COMPUTED", "Translated-frame covariance trace"),
    scenario("figure-eight-rotated-90", "Figure-eight · rotated 90°", "figure-eight-rotated-90.sdtcase.json", "COMPUTED", "Rotated-frame covariance trace"),
    scenario("stable-lagrange-reversed", "Lagrange triangle · reversed", "stable-lagrange-reversed.sdtcase.json", "COMPUTED", "Reversed triangle circulation trace"),
    scenario("stable-lagrange-inclined-45", "Lagrange triangle · inclined 45°", "stable-lagrange-inclined-45.sdtcase.json", "COMPUTED", "Inclined triangle response trace"),
    scenario("stable-lagrange-compact", "Lagrange triangle · compact", "stable-lagrange-compact.sdtcase.json", "COMPUTED", "Compact similarity trace"),
    scenario("stable-lagrange-expanded-15", "Lagrange triangle · expanded 15%", "stable-lagrange-expanded-15.sdtcase.json", "COMPUTED", "Expanded similarity trace"),
    scenario("restricted-runner-l5", "Restricted L5 runner", "restricted-runner-l5.sdtcase.json", "COMPUTED", "L5 mirror geometry trace"),
    scenario("restricted-runner-inclined-30", "Restricted runner · inclined 30°", "restricted-runner-inclined-30.sdtcase.json", "COMPUTED", "Inclined restricted-runner trace"),
    scenario("hierarchical-triple-compact", "Hierarchical triple · compact", "hierarchical-triple-compact.sdtcase.json", "COMPUTED", "Compact hierarchical influence trace"),
    scenario("hierarchical-triple-wide", "Hierarchical triple · wide", "hierarchical-triple-wide.sdtcase.json", "COMPUTED", "Wide hierarchical influence trace"),
    scenario("collinear-partial-eclipse", "Collinear eclipse · partial", "collinear-partial-eclipse.sdtcase.json", "COMPUTED", "Partial-eclipse shielding trace"),
    scenario("collinear-total-eclipse", "Collinear eclipse · totality", "collinear-total-eclipse.sdtcase.json", "COMPUTED", "Total-eclipse shielding trace"),
    scenario("earth-tail-flyby-down-tail", "Earth flyby · down-tail", "earth-tail-flyby-down-tail.sdtcase.json", "PENDING non-driving", "Down-tail flyby diagnostic"),
    scenario("earth-tail-flyby-sunward", "Earth flyby · sunward", "earth-tail-flyby-sunward.sdtcase.json", "PENDING non-driving", "Sunward flyby diagnostic"),
    scenario("earth-tail-flyby-mirrored", "Earth flyby · mirrored", "earth-tail-flyby-mirrored.sdtcase.json", "PENDING non-driving", "Mirrored flyby diagnostic"),
    scenario("earth-tail-stage-scan", "Earth tail · stage scan n=0…8", "earth-tail-stage-scan.sdtcase.json", "PENDING non-driving", "Tail-stage diagnostic scan"),
)


def write_json(path: Path, value: dict) -> None:
    path.write_text(
        json.dumps(value, indent=2) + "\n",
        encoding="utf-8",
        newline="\n",
    )


def make_persistent(case_path: Path) -> None:
    case = json.loads(case_path.read_text(encoding="utf-8"))
    if "max_steps" not in case:
        return
    case.pop("max_steps")
    write_json(case_path, case)


def write_expanded_lagrange_control(directory: Path) -> None:
    source = json.loads(
        (directory / "stable-lagrange.sdtcase.json").read_text(encoding="utf-8")
    )
    scale = 1.15
    velocity_scale = 1 / math.sqrt(scale)
    for body in source["bodies"]:
        body["position_m"] = [scale * value for value in body["position_m"]]
        body["velocity_m_s"] = [velocity_scale * value for value in body["velocity_m_s"]]
        body["radius_m"] *= scale
        body["provenance"]["state"] += "; 15% similarity-expanded control"
    source.pop("max_steps", None)
    source["case_id"] = "mathematical-stable-lagrange-expanded-15"
    source["timestep_s"] *= scale**1.5
    source["provenance"] = {
        "classification": "COMPUTED",
        "description": "Fifteen-percent similarity expansion of the persistent unequal Lagrange control.",
        "sources": ["stable-lagrange.sdtcase.json"],
    }
    write_json(directory / "stable-lagrange-expanded-15.sdtcase.json", source)


def build() -> None:
    catalog = {
        "schema": "sdt-celestial-preset-catalog-1.1.0",
        "count": len(SCENARIOS),
        "presets": list(SCENARIOS),
    }
    for directory in CASE_DIRECTORIES:
        write_expanded_lagrange_control(directory)
        for item in SCENARIOS:
            case_path = directory / item["file"]
            if not case_path.is_file():
                raise FileNotFoundError(case_path)
            make_persistent(case_path)
        write_json(directory / "catalog.json", catalog)
    print(f"Generated {catalog['count']} persistent celestial scenarios")


if __name__ == "__main__":
    build()
