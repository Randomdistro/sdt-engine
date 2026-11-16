"""Export seat and pair diagnostics for the final APS14a model."""

from __future__ import annotations

import csv
import json
from pathlib import Path

import numpy as np

from aps14.angular_geometry import angular_pair_tensor
from aps14.angular_models import predict_transition
from aps14.dynamics import ModelParameters
from aps14.orbital_pathway import seat_path, swept_occlusion
from run_aps14a import load_rows

HERE = Path(__file__).resolve().parent
OUT = HERE / "outputs_aps14a"


def write_csv(path: Path, rows: list[dict]) -> None:
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)


def main() -> None:
    summary = json.loads((OUT / "summary.json").read_text(encoding="utf-8"))
    fit = summary["fits"]["A4_CORE_DEPTH"]
    eta, rho = float(fit["eta"]), float(fit["rho"])
    seats_out, pairs_out = [], []
    for line_index, row in enumerate(load_rows()):
        prediction = predict_transition(
            "A4_CORE_DEPTH", row["Z"], row["A"], row["states"],
            eta, rho, samples=360, phase_divisions=12,
        )
        for level, state, phases in (
            ("lower", prediction.lower_state, prediction.lower_phases),
            ("upper", prediction.upper_state, prediction.upper_phases),
        ):
            path_stats = swept_occlusion(
                state, ModelParameters(g_same=fit.get("g", 0.6433536129861085),
                                       g_cross=fit.get("g", 0.6433536129861085)),
                samples=360,
            )
            distance, projection, cosine = angular_pair_tensor(
                state.radii, state.directions
            )
            for index, seat in enumerate(state.seats):
                path = seat_path(state, index)
                seats_out.append({
                    "line_index": line_index, "Z": row["Z"],
                    "symbol": row["symbol"], "split": row["split"],
                    "transition": row["transition"], "level": level,
                    "seat_index": index, "n": seat.n, "subshell": seat.kind,
                    "occupancy_index": seat.index,
                    "direction_x": state.directions[index, 0],
                    "direction_y": state.directions[index, 1],
                    "direction_z": state.directions[index, 2],
                    "phase_rad": phases.get(seat.n, 0.0),
                    "r_m": state.radii[index],
                    "v_m_s": state.velocities[index],
                    "k": state.k_ratio[index], "z": state.depth_z[index],
                    "koppa_felt_m": state.koppa_felt[index],
                    "n_eff": state.n_eff[index],
                    "q_effective": state.q_effective[index],
                    "static_screening": state.screening[index],
                    "swept_screening_mean": path_stats.seat_screening_mean[index],
                    "swept_screening_variance":
                        path_stats.seat_screening_variance[index],
                    "force_residual": state.force_residual[index],
                    "path_length_m": path.circumference_m,
                    "period_s": path.period_s,
                    "angular_rate_rad_s": path.angular_rate_rad_s,
                    "action_closure_residual": path.action_closure_residual,
                })
            for i in range(len(state.seats)):
                for j in range(i + 1, len(state.seats)):
                    pairs_out.append({
                        "line_index": line_index, "Z": row["Z"],
                        "symbol": row["symbol"], "transition": row["transition"],
                        "level": level, "seat_i": i, "seat_j": j,
                        "static_distance_m": distance[i, j],
                        "static_radial_projection_m": projection[i, j],
                        "lane_cosine": cosine[i, j],
                        "swept_mean_inverse_distance_m-1":
                            path_stats.pair_mean_inverse_distance[i, j],
                        "swept_min_distance_m":
                            path_stats.pair_min_distance[i, j],
                        "swept_max_distance_m":
                            path_stats.pair_max_distance[i, j],
                        "swept_distance_variance_m2":
                            path_stats.pair_distance_variance[i, j],
                    })
    write_csv(OUT / "seat_diagnostics.csv", seats_out)
    write_csv(OUT / "pair_diagnostics.csv", pairs_out)
    print(f"seat_rows={len(seats_out)} pair_rows={len(pairs_out)}")


if __name__ == "__main__":
    main()
