"""Execute APS14a angular-occlusion emission calibration and validation."""

from __future__ import annotations

import csv
import json
import math
from dataclasses import asdict
from pathlib import Path

import numpy as np

from aps14 import constants as K
from aps14.angular_calibration import (
    fit_angular_model, fit_quantum_defect, predict_quantum_defect,
    predict_rows, score,
)
from aps14.angular_models import predict_transition
from aps14.configurations import expand_configuration
from aps14.orbital_pathway import hlike_pathway_controls
from aps14.transitions import build_hlike, build_transition

HERE = Path(__file__).resolve().parent
DATA = HERE / "data"
OUT = HERE / "outputs_aps14a"
MODELS = [
    "A0_TRANSITION_FIX", "A1_PATHWAY", "A2_AXIS_AROUND",
    "A3_ANISOTROPIC_OCCLUSION", "A4_CORE_DEPTH",
]


def write_csv(path: Path, rows: list[dict]) -> None:
    if not rows:
        return
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)


def load_rows() -> list[dict]:
    with (DATA / "elements.csv").open(encoding="utf-8") as handle:
        elements = {int(row["Z"]): row for row in csv.DictReader(handle)}
    with (DATA / "aps14a_lines.csv").open(encoding="utf-8") as handle:
        source = list(csv.DictReader(handle))
    rows = []
    for row in source:
        z = int(row["Z"])
        if row["split"] == "CONTROL":
            states = build_hlike(int(row["lower_n"]), int(row["upper_n"]))
        else:
            ground = expand_configuration(elements[z]["configuration"])
            states = build_transition(ground, row["transition"])
        rows.append({
            **row, "Z": z, "A": int(row["A"]),
            "energy_eV": float(row["energy_eV"]), "states": states,
        })
    return rows


def serial_row(row: dict) -> dict:
    return {key: value for key, value in row.items() if key != "states"}


def main() -> int:
    OUT.mkdir(exist_ok=True)
    rows = load_rows()
    calibration = [row for row in rows if row["split"] == "CALIBRATION"]
    holdout = [row for row in rows if row["split"] == "HOLDOUT"]
    controls = [row for row in rows if row["split"] == "CONTROL"]
    print("APS14a ANGULAR OCCLUSION EMISSION")
    print(
        f"lines={len(rows)} calibration={len(calibration)} "
        f"holdout={len(holdout)} controls={len(controls)}"
    )

    pathway_controls = hlike_pathway_controls()
    write_csv(OUT / "hlike_pathway_controls.csv", pathway_controls)
    max_path_error = max(
        abs(row["path_ratio"] / row["path_expected"] - 1.0)
        for row in pathway_controls
    )
    max_action_error = max(
        max(abs(row["lower_action_residual"]), abs(row["upper_action_residual"]))
        for row in pathway_controls
    )
    print(
        f"pathway_controls max_path_error={max_path_error:.3e} "
        f"max_action_error={max_action_error:.3e}"
    )

    fits = {}
    scores = []
    prediction_ledger = []
    for model in MODELS:
        print(f"fitting {model} ...", flush=True)
        fit = fit_angular_model(model, calibration)
        fits[model] = fit
        print(
            f"  eta={fit.eta:.6g} rho={fit.rho:.6g} "
            f"rss={fit.rss:.5g} AICc={fit.aicc:.5g} success={fit.success}"
        )
        for split, subset in (
            ("CALIBRATION", calibration), ("HOLDOUT", holdout),
            ("CONTROL", controls),
        ):
            details = [
                predict_transition(
                    model, row["Z"], row["A"], row["states"],
                    fit.eta, fit.rho, samples=360, phase_divisions=12,
                )
                for row in subset
            ]
            predicted = np.asarray([detail.energy_eV for detail in details])
            observed = np.asarray([row["energy_eV"] for row in subset])
            result = {"model": model, "split": split, **score(observed, predicted)}
            scores.append(result)
            print(
                f"  {split.lower()} coverage={result['coverage']:.3f} "
                f"median={100*result['median']:.3f}% "
                f"logRMSE={result['log_rmse']:.4g}"
            )
            for row, value, detail in zip(subset, predicted, details):
                prediction_ledger.append({
                    "model": model, **serial_row(row),
                    "predicted_energy_eV": value,
                    "predicted_frequency_hz": detail.frequency_hz,
                    "predicted_omega_rad_s": detail.omega_rad_s,
                    "predicted_wavelength_nm": detail.wavelength_nm,
                    "fractional_energy_residual": (
                        value / row["energy_eV"] - 1.0
                        if math.isfinite(value) else math.nan
                    ),
                    "path_ratio": detail.path_ratio,
                    "period_ratio": detail.period_ratio,
                    "angular_rate_ratio": detail.angular_rate_ratio,
                    "delta_active_path_m": detail.delta_path_m,
                    "delta_companion_path_m": detail.companion_path_delta_m,
                    "delta_active_swept_screening":
                        detail.active_swept_screening_delta,
                    "lower_phases": json.dumps(detail.lower_phases, sort_keys=True),
                    "upper_phases": json.dumps(detail.upper_phases, sort_keys=True),
                    "origin": "COMPUTED",
                })

    qd = fit_quantum_defect(calibration)
    print("quantum_defect", qd.tolist())
    for split, subset in (("CALIBRATION", calibration), ("HOLDOUT", holdout)):
        predicted = predict_quantum_defect(qd, subset)
        observed = np.asarray([row["energy_eV"] for row in subset])
        scores.append({
            "model": "BASE_QUANTUM_DEFECT", "split": split,
            **score(observed, predicted),
        })
    bare = np.zeros(4)
    for split, subset in (("CALIBRATION", calibration), ("HOLDOUT", holdout)):
        predicted = predict_quantum_defect(bare, subset)
        observed = np.asarray([row["energy_eV"] for row in subset])
        scores.append({
            "model": "BASE_RYDBERG", "split": split,
            **score(observed, predicted),
        })

    # Whole-element leave-one-out and element-bootstrap on the final model.
    loeo = []
    final_start = (
        fits["A4_CORE_DEPTH"].eta, fits["A4_CORE_DEPTH"].rho
    )
    for z in sorted({row["Z"] for row in calibration}):
        train = [row for row in calibration if row["Z"] != z]
        test = [row for row in calibration if row["Z"] == z]
        fit = fit_angular_model(
            "A4_CORE_DEPTH", train, max_nfev=14,
            grid_search=False, initial=final_start,
        )
        predicted = predict_rows(
            "A4_CORE_DEPTH", test, fit.eta, fit.rho,
            samples=180, phase_divisions=8,
        )
        result = score(
            np.asarray([row["energy_eV"] for row in test]), predicted
        )
        loeo.append({
            "held_out_Z": z, "symbol": test[0]["symbol"],
            "eta": fit.eta, "rho": fit.rho, **result,
        })
        print(f"LOEO Z={z} eta={fit.eta:.4g} rho={fit.rho:.4g}")

    rng = np.random.default_rng(1414)
    z_values = sorted({row["Z"] for row in calibration})
    bootstrap = []
    for draw in range(8):
        chosen = rng.choice(z_values, size=len(z_values), replace=True)
        sample = [
            row for z in chosen for row in calibration if row["Z"] == int(z)
        ]
        fit = fit_angular_model(
            "A4_CORE_DEPTH", sample, max_nfev=14,
            grid_search=False, initial=final_start,
        )
        bootstrap.append({"draw": draw, "eta": fit.eta, "rho": fit.rho})
        print(f"bootstrap={draw} eta={fit.eta:.4g} rho={fit.rho:.4g}")

    # Delete-test: observed energy mutation cannot change a fixed forward result.
    best = fits["A4_CORE_DEPTH"]
    original = predict_rows(
        "A4_CORE_DEPTH", holdout, best.eta, best.rho,
        samples=180, phase_divisions=8,
    )
    mutated = [{**row, "energy_eV": row["energy_eV"] * 31} for row in holdout]
    delete_test = bool(np.array_equal(
        original,
        predict_rows(
            "A4_CORE_DEPTH", mutated, best.eta, best.rho,
            samples=180, phase_divisions=8,
        ),
    ))

    write_csv(OUT / "model_scores.csv", scores)
    write_csv(OUT / "transition_predictions.csv", prediction_ledger)
    write_csv(OUT / "leave_one_element_out.csv", loeo)
    write_csv(OUT / "bootstrap_parameters.csv", bootstrap)
    summary = {
        "fits": {name: asdict(fit) for name, fit in fits.items()},
        "scores": scores,
        "quantum_defect_parameters": qd.tolist(),
        "max_hlike_path_error": max_path_error,
        "max_action_closure_error": max_action_error,
        "delete_test": delete_test,
        "loeo": loeo,
        "bootstrap": bootstrap,
        "laws_hpp_edited": False,
    }
    (OUT / "summary.json").write_text(
        json.dumps(summary, indent=2, allow_nan=True) + "\n", encoding="utf-8"
    )
    print(f"delete_test={delete_test}")
    print("COMPLETE")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
