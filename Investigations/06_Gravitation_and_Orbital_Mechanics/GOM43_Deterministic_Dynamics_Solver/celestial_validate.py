#!/usr/bin/env python3
"""Whole-range validator for the GOM43-C celestial solver."""

from __future__ import annotations

import copy
import json
import math
import pathlib
import subprocess
import sys
import tempfile
from typing import Any


ROOT = pathlib.Path(__file__).resolve().parent
EXAMPLES = ROOT / "examples" / "celestial"
DATASETS = ROOT / "datasets"


def run_case(executable: pathlib.Path, case: dict[str, Any]) -> dict[str, Any]:
    with tempfile.NamedTemporaryFile(
        mode="w",
        suffix=".sdtcase.json",
        encoding="utf-8",
        delete=False,
    ) as stream:
        json.dump(case, stream, separators=(",", ":"))
        path = pathlib.Path(stream.name)
    try:
        process = subprocess.run(
            [str(executable), str(path)],
            check=False,
            capture_output=True,
            text=True,
            timeout=300,
        )
        if not process.stdout:
            raise RuntimeError(process.stderr.strip() or "solver emitted no JSON")
        result = json.loads(process.stdout)
        if process.returncode not in (0, 1):
            raise RuntimeError(process.stderr.strip() or "solver process failed")
        return result
    finally:
        path.unlink(missing_ok=True)


def vector_error(first: list[float], second: list[float]) -> float:
    return math.sqrt(sum((a - b) ** 2 for a, b in zip(first, second)))


def transformed_case(
    source: dict[str, Any],
    angle: float,
    translation: tuple[float, float, float],
) -> dict[str, Any]:
    result = copy.deepcopy(source)
    cosine = math.cos(angle)
    sine = math.sin(angle)

    def rotate(value: list[float], translate: bool) -> list[float]:
        rotated = [
            cosine * value[0] - sine * value[1],
            sine * value[0] + cosine * value[1],
            value[2],
        ]
        return [
            rotated[index] + (translation[index] if translate else 0.0)
            for index in range(3)
        ]

    for body in result["bodies"]:
        body["position_m"] = rotate(body["position_m"], True)
        body["velocity_m_s"] = rotate(body["velocity_m_s"], False)
    result["case_id"] += "-transformed"
    return result


def aligned_eclipse_case() -> dict[str, Any]:
    provenance = {
        "baryons": "geometry fixture",
        "radius": "geometry fixture",
        "state": "geometry fixture",
    }
    return {
        "contract_version": "2.0.0",
        "case_id": "aligned-eclipse-limit",
        "problem_class": "celestial_three_body",
        "frame": {
            "type": "inertial_cartesian",
            "units": "SI",
            "epoch": "t=0",
        },
        "force": {
            "type": "retarded_seven_cone_occlusion",
            "propagation_speed": "c",
            "pressure_source": "sdt_law_I_P_conv",
            "enable_eclipse_shielding": True,
            "comparison_route": "point_koppa",
        },
        "bodies": [
            {
                "id": "target",
                "baryon_count": "42",
                "radius_m": 10,
                "position_m": [0, 0, 0],
                "velocity_m_s": [0, 0, 0],
                "provenance": provenance,
            },
            {
                "id": "source",
                "baryon_count": "70",
                "radius_m": 100,
                "position_m": [10000, 0, 0],
                "velocity_m_s": [0, 0, 0],
                "provenance": provenance,
            },
            {
                "id": "occluder",
                "baryon_count": "105",
                "radius_m": 60,
                "position_m": [5000, 0, 0],
                "velocity_m_s": [0, 0, 0],
                "provenance": provenance,
            },
        ],
        "integrator": "velocity_verlet",
        "timestep_s": 0.001,
        "max_steps": 1,
        "record_every_steps": 1,
        "tolerances": {
            "retarded_time_s": 1e-12,
            "channel_closure": 1e-13,
            "medium_momentum_relative": 1e-11,
            "lagrange_residual_m_s2": 1e-9,
            "max_retarded_iterations": 32,
        },
        "provenance": {
            "classification": "COMPUTED",
            "description": "eclipse known answer",
            "sources": [],
        },
    }


def main() -> int:
    if len(sys.argv) != 2:
        print("usage: celestial_validate.py PATH_TO_SOLVER", file=sys.stderr)
        return 2
    executable = pathlib.Path(sys.argv[1]).resolve()
    if not executable.is_file():
        print(f"solver not found: {executable}", file=sys.stderr)
        return 2

    names = [
        "jpl-sun-earth-moon-j2000.sdtcase.json",
        "figure-eight.sdtcase.json",
        "stable-lagrange.sdtcase.json",
        "restricted-runner.sdtcase.json",
        "sun-earth-spacecraft.sdtcase.json",
        "sun-jupiter-trojan.sdtcase.json",
    ]
    rows: dict[str, dict[str, Any]] = {}
    all_structural = True
    loaded: dict[str, dict[str, Any]] = {}
    results: dict[str, dict[str, Any]] = {}
    for name in names:
        case = json.loads((EXAMPLES / name).read_text(encoding="utf-8"))
        loaded[name] = case
        result = run_case(executable, case)
        results[name] = result
        diagnostics = result.get("diagnostics", {})
        structural = (
            result.get("status") == "completed"
            and len(result.get("cones", [])) == 42
            and result.get("packet_ledger", {}).get("reconstruction_passed") is True
            and diagnostics.get("maximum_channel_closure_relative", 1.0)
            <= case["tolerances"]["channel_closure"]
            and diagnostics.get("maximum_retarded_residual_s", 1.0)
            <= case["tolerances"]["retarded_time_s"]
            and diagnostics.get("body_plus_medium_momentum_residual", 1.0)
            <= case["tolerances"]["medium_momentum_relative"]
            and diagnostics.get("maximum_effective_resistance_ratio", 0.0) >= 1.0
        )
        all_structural = all_structural and structural
        rows[name] = {
            "status": result.get("status"),
            "structural_pass": structural,
            "trajectory_sha256": result.get("trajectory_sha256"),
            "lagrange_count": len(result.get("lagrange", [])),
            "maximum_retarded_residual_s": diagnostics.get(
                "maximum_retarded_residual_s"
            ),
            "maximum_eclipse_shield": diagnostics.get("maximum_eclipse_shield"),
            "minimum_pair_distance_m": diagnostics.get("minimum_pair_distance_m"),
        }

    expected = json.loads(
        (DATASETS / "jpl-de441-j2000-60s.json").read_text(encoding="utf-8")
    )
    jpl_result = results[names[0]]
    terminal = jpl_result["trajectory"][-1]["states"]
    expected_by_id = {
        state["id"]: state for state in expected["terminal_states_si"]
    }
    position_errors = []
    velocity_errors = []
    for state in terminal:
        reference = expected_by_id[state["id"]]
        position_errors.append(
            vector_error(state["position_m"], reference["position_m"])
        )
        velocity_errors.append(
            vector_error(state["velocity_m_s"], reference["velocity_m_s"])
        )
    jpl_comparison = {
        "maximum_position_residual_m": max(position_errors),
        "maximum_velocity_residual_m_s": max(velocity_errors),
        "classification": "OBSERVED comparison; not fitted",
    }

    figure = results["figure-eight.sdtcase.json"]["trajectory"]
    figure_initial = figure[0]["states"]
    figure_terminal = figure[-1]["states"]
    figure_position_rms = math.sqrt(
        sum(
            vector_error(a["position_m"], b["position_m"]) ** 2
            for a, b in zip(figure_initial, figure_terminal)
        )
        / 3
    )
    figure_velocity_rms = math.sqrt(
        sum(
            vector_error(a["velocity_m_s"], b["velocity_m_s"]) ** 2
            for a, b in zip(figure_initial, figure_terminal)
        )
        / 3
    )

    base_case = copy.deepcopy(loaded["restricted-runner.sdtcase.json"])
    base_case["max_steps"] = 1
    base_case["record_every_steps"] = 1
    base = run_case(executable, base_case)
    transformed = transformed_case(base_case, 0.713, (2e8, -3e8, 5e7))
    transformed_result = run_case(executable, transformed)
    transformed_back = transformed_result["trajectory"][-1]["states"]
    base_terminal = base["trajectory"][-1]["states"]
    covariance_error = 0.0
    cosine = math.cos(0.713)
    sine = math.sin(0.713)
    for original, changed in zip(base_terminal, transformed_back):
        rotated = [
            cosine * original["position_m"][0]
            - sine * original["position_m"][1]
            + 2e8,
            sine * original["position_m"][0]
            + cosine * original["position_m"][1]
            - 3e8,
            original["position_m"][2] + 5e7,
        ]
        covariance_error = max(
            covariance_error,
            vector_error(rotated, changed["position_m"]),
        )

    eclipse = run_case(executable, aligned_eclipse_case())
    eclipse_limit = eclipse["diagnostics"]["maximum_eclipse_shield"]
    eclipse_pass = eclipse_limit >= 1.0 - 1e-14

    catalog = json.loads((EXAMPLES / "catalog.json").read_text(encoding="utf-8"))
    catalog_rows: dict[str, dict[str, Any]] = {}
    catalog_pass = (
        catalog.get("count") == 25
        and len(catalog.get("presets", [])) == 25
        and len({item["id"] for item in catalog.get("presets", [])}) == 25
    )
    for item in catalog.get("presets", []):
        case = json.loads((EXAMPLES / item["file"]).read_text(encoding="utf-8"))
        case["max_steps"] = 1
        case.pop("duration_s", None)
        case["record_every_steps"] = 1
        result = run_case(executable, case)
        diagnostics = result.get("diagnostics", {})
        passed = (
            result.get("status") == "completed"
            and result.get("executed_steps") == 1
            and len(result.get("cones", [])) == 42
            and result.get("packet_ledger", {}).get("reconstruction_passed") is True
            and diagnostics.get("maximum_channel_closure_relative", 1.0)
            <= case["tolerances"]["channel_closure"]
        )
        catalog_pass = catalog_pass and passed
        catalog_rows[item["id"]] = {
            "file": item["file"],
            "status": result.get("status"),
            "cones": len(result.get("cones", [])),
            "passed": passed,
        }

    summary = {
        "schema": "GOM43-C-VALIDATION-1",
        "status": (
            "passed"
            if all_structural and eclipse_pass and catalog_pass
            else "failed"
        ),
        "whole_range": rows,
        "preset_catalog": {
            "declared_count": catalog.get("count"),
            "validated_count": len(catalog_rows),
            "passed": catalog_pass,
            "simulations": catalog_rows,
        },
        "jpl_de441_60s": jpl_comparison,
        "figure_eight": {
            "position_closure_rms_m": figure_position_rms,
            "velocity_closure_rms_m_s": figure_velocity_rms,
            "classification": "finite-retardation observation",
        },
        "covariance": {
            "transformed_position_residual_m": covariance_error,
            "passed": covariance_error <= 1e-5,
        },
        "eclipse": {
            "totality_shield_fraction": eclipse_limit,
            "passed": eclipse_pass,
        },
    }
    print(json.dumps(summary, indent=2, sort_keys=True))
    return 0 if summary["status"] == "passed" else 1


if __name__ == "__main__":
    raise SystemExit(main())

