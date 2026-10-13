#!/usr/bin/env python3
"""Run the registered 1,000-body, one-step GOM43-E throughput gate."""

from __future__ import annotations

import argparse
import json
import subprocess
import tempfile
import time
from pathlib import Path


def build_case(count: int) -> dict:
    bodies = []
    for index in range(count):
        bodies.append(
            {
                "id": f"body-{index:04d}",
                "baryon_count": "1",
                "radius_m": 1.0,
                "collision_radius_m": 1.0,
                "position_m": [
                    float((index * 73856093) % 1009) * 1.0e8,
                    float((index * 19349663) % 1013) * 1.0e8,
                    float((index * 83492791) % 1019) * 1.0e8,
                ],
                "velocity_m_s": [0.0, 0.0, 0.0],
            }
        )
    return {
        "contract_version": "3.0.0",
        "case_id": "multibody-performance-1000",
        "problem_class": "sdt_occlusion_nbody",
        "frame": {"type": "inertial_cartesian", "units": "SI"},
        "forces": [
            {
                "type": "retarded_seven_circle_occlusion",
                "pressure_source": "sdt_law_I_P_conv",
                "propagation_speed": "c",
            }
        ],
        "bodies": bodies,
        "integrator": "velocity_verlet",
        "timestep_s": 1.0,
        "duration_s": 1.0,
        "record_every_steps": 1,
        "tolerances": {
            "retarded_time_s": 1e-12,
            "max_retarded_iterations": 32,
        },
        "gates": [{"id": "M1"}, {"id": "M12"}],
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("solver", type=Path)
    parser.add_argument("--limit-s", type=float, default=60.0)
    parser.add_argument("--bodies", type=int, default=1000)
    arguments = parser.parse_args()
    expected = 49 * arguments.bodies * (arguments.bodies - 1)
    with tempfile.TemporaryDirectory() as directory:
        case_path = Path(directory) / "performance.sdtcase.json"
        case_path.write_text(
            json.dumps(build_case(arguments.bodies)),
            encoding="utf-8",
        )
        started = time.perf_counter()
        completed = subprocess.run(
            [str(arguments.solver.resolve()), str(case_path)],
            check=False,
            capture_output=True,
            text=True,
            timeout=arguments.limit_s,
        )
        elapsed = time.perf_counter() - started
    result = json.loads(completed.stdout)
    if "diagnostics" not in result:
        print(json.dumps(result, indent=2))
        return 1
    diagnostics = result["diagnostics"]
    passed = (
        result["status"] == "completed"
        and diagnostics["evaluated_channel_relations"] == expected
        and diagnostics["detail_output_truncated"] is True
        and not result["interactions"]
        and not result["pair_matrix"]
        and elapsed < arguments.limit_s
    )
    print(
        json.dumps(
            {
                "classification": "COMPUTED",
                "status": "passed" if passed else "failed",
                "bodies": arguments.bodies,
                "steps": 1,
                "evaluated_channel_relations": expected,
                "elapsed_s": elapsed,
                "limit_s": arguments.limit_s,
                "detail_output_truncated": diagnostics[
                    "detail_output_truncated"
                ],
            },
            indent=2,
        )
    )
    return 0 if passed else 1


if __name__ == "__main__":
    raise SystemExit(main())
