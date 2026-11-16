#!/usr/bin/env python3
"""Whole-range gates for GOM43-D composition, displacement and slingshot routes."""

from __future__ import annotations

import argparse
import json
import math
from pathlib import Path
import subprocess
import sys


ROOT = Path(__file__).resolve().parent
CASES = ROOT / "examples" / "celestial"
LEDGER = ROOT / "datasets" / "displacement-ledgers.json"
OBSERVED = ROOT / "datasets" / "earth-flyby-observed-comparison.json"
SUMMARY = ROOT / "displacement_slingshot_validation.json"


def close(left: float, right: float, tolerance: float) -> bool:
    return abs(left - right) <= tolerance * max(1.0, abs(left), abs(right))


def run_case(solver: Path, name: str) -> dict:
    completed = subprocess.run(
        [str(solver), str(CASES / name)],
        check=False,
        capture_output=True,
        text=True,
        encoding="utf-8",
        timeout=240,
    )
    if completed.returncode != 0:
        raise RuntimeError(
            f"{name} failed ({completed.returncode}): "
            f"{completed.stderr or completed.stdout}"
        )
    return json.loads(completed.stdout)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("solver", type=Path)
    arguments = parser.parse_args()
    solver = arguments.solver.resolve()

    subprocess.run(
        [sys.executable, str(ROOT / "build_displacement_ledgers.py")],
        check=True,
        capture_output=True,
        text=True,
    )
    ledger = json.loads(LEDGER.read_text(encoding="utf-8"))
    observed = json.loads(OBSERVED.read_text(encoding="utf-8"))
    gates: list[dict[str, object]] = []

    def gate(identifier: str, passed: bool, value: object, limit: object) -> None:
        gates.append(
            {
                "id": identifier,
                "passed": bool(passed),
                "value": value,
                "limit": limit,
            }
        )

    bodies = {body["id"]: body for body in ledger["bodies"]}
    for body_id, body in bodies.items():
        proton_count = int(body["proton_count"])
        neutron_count = int(body["neutron_count"])
        baryons = int(body["baryon_count"])
        burden = int(body["weighted_trefoil_burden"])
        gate(
            f"composition-{body_id.lower()}-coverage",
            body["material_volume_coverage"] >= 0.98
            and body["represented_atomic_mass_coverage"] >= 0.98,
            [
                body["material_volume_coverage"],
                body["represented_atomic_mass_coverage"],
            ],
            "both >= 0.98",
        )
        gate(
            f"composition-{body_id.lower()}-exact-pn",
            proton_count + neutron_count == baryons,
            str(proton_count + neutron_count),
            body["baryon_count"],
        )
        gate(
            f"composition-{body_id.lower()}-exact-burden",
            1836 * proton_count + 1838 * neutron_count == burden,
            str(1836 * proton_count + 1838 * neutron_count),
            body["weighted_trefoil_burden"],
        )

    case_names = [
        "earth-tail-flyby-controlled.sdtcase.json",
        "earth-tail-flyby-down-tail.sdtcase.json",
        "earth-tail-flyby-sunward.sdtcase.json",
        "earth-tail-flyby-mirrored.sdtcase.json",
        "earth-tail-stage-scan.sdtcase.json",
    ]
    results = {name: run_case(solver, name) for name in case_names}
    for name, result in results.items():
        gate(
            f"{name}-completed",
            result["status"] == "completed",
            result["status"],
            "completed",
        )
        gate(
            f"{name}-tail-nondriving",
            result["slingshot"]["ablation"]["tail_drives_state"] is False
            and result["slingshot"]["ablation"][
                "canonical_state_changed_by_tail"
            ]
            is False,
            result["slingshot"]["ablation"],
            "both false",
        )

    base = results[case_names[0]]
    stage_scan = results[case_names[-1]]
    expected_k = float(ledger["earth_sun"]["K_SDT"])
    actual_k = base["slingshot"]["K_SDT"]
    gate("k-sdt-ledger", close(actual_k, expected_k, 2e-15), actual_k, expected_k)

    displacement_rows = {row["id"]: row for row in base["displacement_ledger"]}
    for body_id in ("Sun", "Earth"):
        expected_rest = float(
            bodies[body_id]["law_IV_displacement"]["rest_volume_m3"]
        )
        actual_rest = displacement_rows[body_id]["rest_volume_m3"]
        gate(
            f"law-iv-{body_id.lower()}-rest-volume",
            close(actual_rest, expected_rest, 3e-15),
            actual_rest,
            expected_rest,
        )
        row = displacement_rows[body_id]
        gate(
            f"law-iv-{body_id.lower()}-effective-volume",
            close(
                row["effective_volume_m3"],
                row["rest_volume_m3"] * row["resistance_ratio"],
                3e-15,
            )
            and close(
                row["engaged_volume_m3"],
                row["effective_volume_m3"] - row["rest_volume_m3"],
                3e-15,
            ),
            [row["rest_volume_m3"], row["engaged_volume_m3"], row["effective_volume_m3"]],
            "effective=rest+engaged",
        )

    stages = stage_scan["slingshot"]["stages"]
    conservation = max(
        stage["burden_conservation_relative"] for stage in stages
    )
    gate("stage-count", len(stages) == 9, len(stages), 9)
    gate("stage-burden-conservation", conservation <= 2e-15, conservation, 2e-15)
    gate(
        "stage-monotonic",
        all(
            stages[index + 1]["solid_angle_sr"] < stages[index]["solid_angle_sr"]
            and stages[index + 1]["K_n"] > stages[index]["K_n"]
            and stages[index + 1]["z_n_m"] > stages[index]["z_n_m"]
            for index in range(8)
        ),
        True,
        True,
    )
    stage8 = stages[8]
    gate(
        "stage8-half-angle",
        abs(stage8["cone_half_angle_deg"] - 7.1666) <= 0.05,
        stage8["cone_half_angle_deg"],
        "7.1666 +/- 0.05 deg",
    )
    gate(
        "stage8-z",
        abs(stage8["z_n_m"] - 4.27e9) <= 3.0e7,
        stage8["z_n_m"],
        "4.27e9 +/- 3e7 m",
    )
    gate(
        "stage8-classification",
        stage8["classification"] == "PENDING/candidate-not-terminal",
        stage8["classification"],
        "PENDING/candidate-not-terminal",
    )

    endpoint = base["slingshot"]["endpoint"]
    gate(
        "equal-radius-endpoints",
        endpoint["equal_radius_passed"],
        endpoint["radius_mismatch_m"],
        endpoint["equal_radius_tolerance_m"],
    )
    gate(
        "position-angle-inbound",
        close(
            endpoint["cos_psi_in"],
            sum(
                endpoint["rho_hat_in"][axis] * endpoint["tail_hat_in"][axis]
                for axis in range(3)
            ),
            2e-15,
        ),
        endpoint["cos_psi_in"],
        "rho_hat_in dot tail_hat_in",
    )
    gate(
        "endpoint-integral-closure",
        close(
            endpoint["supplied_endpoint_delta_v_m_s"],
            endpoint["trajectory_integrated_delta_v_m_s"],
            2e-15,
        ),
        endpoint["integral_closure_relative"],
        2e-15,
    )
    kinematics = base["slingshot"]["kinematics"]
    gate(
        "straight-line-control",
        math.isfinite(kinematics["straight_line_2c2koppa_over_bv_m_s"])
        and kinematics["straight_line_2c2koppa_over_bv_m_s"] > 0,
        kinematics["straight_line_2c2koppa_over_bv_m_s"],
        "> 0 and finite",
    )
    gate(
        "energy-transfer-ledger",
        all(
            math.isfinite(kinematics[key])
            for key in (
                "flyby_frame_speed_change_m_s",
                "host_frame_specific_kinetic_energy_change_j_kg",
                "host_frame_kinetic_energy_change_j",
                "endpoint_displacement_work_j",
            )
        ),
        "finite",
        "finite",
    )
    gate(
        "mirrored-position-angle",
        results["earth-tail-flyby-mirrored.sdtcase.json"]["slingshot"][
            "endpoint"
        ]["cos_psi_in"]
        < 0
        < endpoint["cos_psi_in"],
        [
            endpoint["cos_psi_in"],
            results["earth-tail-flyby-mirrored.sdtcase.json"]["slingshot"][
                "endpoint"
            ]["cos_psi_in"],
        ],
        "opposite signs",
    )
    gate(
        "observed-comparison-isolation",
        all(
            row["sdt_status"] == "NOT-EXECUTED"
            and row["equal_radius_heliocentric_state_vectors_available"] is False
            for row in observed["rows"]
        ),
        len(observed["rows"]),
        "all rows comparison-only",
    )

    passed = all(row["passed"] for row in gates)
    summary = {
        "status": "passed" if passed else "failed",
        "classification": "COMPUTED with PENDING transported-tail branch",
        "solver": str(solver),
        "gate_count": len(gates),
        "passed_count": sum(bool(row["passed"]) for row in gates),
        "gates": gates,
        "key_results": {
            "K_SDT": actual_k,
            "stage8_half_angle_deg": stage8["cone_half_angle_deg"],
            "stage8_z_m": stage8["z_n_m"],
            "endpoint_delta_v_m_s": endpoint["supplied_endpoint_delta_v_m_s"],
            "observed_rows_not_executed": len(observed["rows"]),
        },
    }
    SUMMARY.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(summary, indent=2))
    return 0 if passed else 1


if __name__ == "__main__":
    raise SystemExit(main())
