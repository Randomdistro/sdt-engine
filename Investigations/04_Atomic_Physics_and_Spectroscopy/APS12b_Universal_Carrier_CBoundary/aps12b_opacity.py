#!/usr/bin/env python3
"""Evaluate APS12b c-boundary geometry and gamma opacity models."""
from __future__ import annotations

import csv
import math
from collections import Counter
from pathlib import Path

import numpy as np

HERE = Path(__file__).resolve().parent
RADII = HERE / "data" / "nuclear_radii.csv"
GAMMAS = HERE / "data" / "gamma_transitions.csv"
GEOMETRY_OUT = HERE / "boundary_geometry.csv"
SUMMARY_OUT = HERE / "opacity_model_summary.csv"
PRED_OUT = HERE / "opacity_predictions.csv"
STABILITY_OUT = HERE / "opacity_beta_stability.csv"

R_E_FM = 2.817_940_3262
HELD_OUT = {"137ba", "152sm", "197au", "208pb", "241am"}


def read_csv(path: Path) -> list[dict[str, str]]:
    with path.open(encoding="utf-8") as handle:
        return list(csv.DictReader(handle))


def geometry() -> tuple[list[dict[str, object]], dict[str, float]]:
    rows = []
    for raw in read_csv(RADII):
        Z, A, radius = int(raw["Z"]), int(raw["A"]), float(raw["radius_fm"])
        beta1 = radius / (Z * R_E_FM)
        beta2 = radius / (2 * Z * R_E_FM)
        rows.append({
            "Z": Z, "A": A, "symbol": raw["symbol"],
            "radius_fm": radius, "unc_radius_fm": raw["unc_radius_fm"],
            "c_boundary_q1_fm": Z * R_E_FM,
            "c_boundary_q2_fm": 2 * Z * R_E_FM,
            "beta_q1": beta1, "beta_q2": beta2,
            "inside_q1": int(beta1 < 1), "inside_q2": int(beta2 < 1),
        })
    beta1 = np.array([float(r["beta_q1"]) for r in rows])
    beta2 = np.array([float(r["beta_q2"]) for r in rows])
    stats = {
        "n": len(rows), "inside_q1": int(np.sum(beta1 < 1)),
        "inside_q2": int(np.sum(beta2 < 1)),
        "min_beta_q1": float(np.min(beta1)),
        "median_beta_q1": float(np.median(beta1)),
        "max_beta_q1": float(np.max(beta1)),
        "min_beta_q2": float(np.min(beta2)),
        "median_beta_q2": float(np.median(beta2)),
        "max_beta_q2": float(np.max(beta2)),
    }
    return rows, stats


def multipolarity_class(value: str) -> str:
    text = value.strip().upper()
    if not text:
        return "UNKNOWN"
    # Preserve common pure/mixed classes; rare forms become OTHER.
    for token in ["E1", "M1", "E2", "M2", "E3", "M3", "E4"]:
        if text == token:
            return token
    if "+" in text:
        return "MIXED"
    return "OTHER"


def gamma_rows() -> list[dict[str, object]]:
    rows = []
    for raw in read_csv(GAMMAS):
        if not raw["tot_conv_coeff"] or not raw["radius_fm_measured"]:
            continue
        try:
            icc = float(raw["tot_conv_coeff"])
            energy = float(raw["gamma_energy_keV"])
            Z = int(raw["Z"])
            radius = float(raw["radius_fm_measured"])
        except ValueError:
            continue
        if icc <= 0 or energy <= 0:
            continue
        beta = radius / (Z * R_E_FM)
        fraction = 1 / (1 + icc)
        rows.append({
            **raw, "Z_value": Z, "energy_value": energy,
            "icc_value": icc, "fraction_value": fraction,
            "beta_value": beta,
            "class": multipolarity_class(raw["multipolarity"]),
            "split": "test" if raw["nuclide"] in HELD_OUT else "train",
        })
    return rows


def classes_for(rows: list[dict[str, object]]) -> list[str]:
    counts = Counter(str(r["class"]) for r in rows)
    return sorted(name for name, count in counts.items()
                  if name not in {"UNKNOWN", "OTHER"} and count >= 10)


def design(rows: list[dict[str, object]], classes: list[str],
           include_beta: bool) -> np.ndarray:
    columns = [
        np.ones(len(rows)),
        np.array([math.log(float(r["energy_value"])) for r in rows]),
        np.array([math.log(float(r["Z_value"])) for r in rows]),
    ]
    if include_beta:
        columns.append(
            np.array([math.log(float(r["beta_value"])) for r in rows])
        )
    for name in classes:
        columns.append(np.array([1.0 if r["class"] == name else 0.0
                                 for r in rows]))
    return np.column_stack(columns)


def response(rows: list[dict[str, object]]) -> np.ndarray:
    # logit(1/(1+ICC)) = -log(ICC)
    return np.array([-math.log(float(r["icc_value"])) for r in rows])


def fit(rows: list[dict[str, object]], classes: list[str],
        include_beta: bool) -> np.ndarray:
    return np.linalg.lstsq(
        design(rows, classes, include_beta), response(rows), rcond=None
    )[0]


def score(rows: list[dict[str, object]], classes: list[str],
          params: np.ndarray, include_beta: bool) -> dict[str, float]:
    truth = response(rows)
    pred = design(rows, classes, include_beta) @ params
    fraction_truth = 1 / (1 + np.exp(-np.clip(truth, -700, 700)))
    fraction_pred = 1 / (1 + np.exp(-np.clip(pred, -700, 700)))
    return {
        "logit_rmse": float(np.sqrt(np.mean((pred - truth) ** 2))),
        "fraction_mae": float(np.mean(np.abs(fraction_pred - fraction_truth))),
        "fraction_max": float(np.max(np.abs(fraction_pred - fraction_truth))),
    }


def main() -> None:
    geometry_rows, stats = geometry()
    with GEOMETRY_OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(geometry_rows[0]))
        writer.writeheader()
        writer.writerows(geometry_rows)

    gamma_all = gamma_rows()
    train = [r for r in gamma_all if r["split"] == "train"]
    test = [r for r in gamma_all if r["split"] == "test"]
    classes = classes_for(train)

    summaries = []
    predictions = []
    fits: dict[str, tuple[np.ndarray, bool]] = {}
    for name, include_beta in [("controls_only", False),
                               ("controls_plus_beta", True)]:
        params = fit(train, classes, include_beta)
        fits[name] = (params, include_beta)
        for split_name, subset in [("train", train), ("test", test)]:
            result = score(subset, classes, params, include_beta)
            summaries.append({
                "model": name, "split": split_name, "n": len(subset),
                **result,
                "beta_coefficient":
                    params[3] if include_beta else "",
                "parameters": ";".join(f"{x:.12g}" for x in params),
                "multipolarity_classes": ";".join(classes),
            })
            pred_logit = design(subset, classes, include_beta) @ params
            pred_fraction = 1 / (1 + np.exp(-np.clip(pred_logit, -700, 700)))
            for row, value, logit in zip(subset, pred_fraction, pred_logit):
                predictions.append({
                    "model": name, "split": split_name,
                    "nuclide": row["nuclide"], "Z": row["Z_value"],
                    "gamma_energy_keV": row["energy_value"],
                    "multipolarity_class": row["class"],
                    "beta_q1": row["beta_value"],
                    "observed_gamma_fraction": row["fraction_value"],
                    "predicted_gamma_fraction": value,
                    "predicted_logit": logit,
                })

    with SUMMARY_OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(summaries[0]))
        writer.writeheader()
        writer.writerows(summaries)
    with PRED_OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(predictions[0]))
        writer.writeheader()
        writer.writerows(predictions)

    stability = []
    for nuclide in sorted({str(r["nuclide"]) for r in train}):
        fold_train = [r for r in train if r["nuclide"] != nuclide]
        fold_test = [r for r in train if r["nuclide"] == nuclide]
        if len(fold_train) <= len(classes) + 4 or not fold_test:
            continue
        params = fit(fold_train, classes, True)
        fold_score = score(fold_test, classes, params, True)
        stability.append({
            "held_out_nuclide": nuclide, "n_test": len(fold_test),
            "beta_coefficient": params[3],
            "test_logit_rmse": fold_score["logit_rmse"],
            "test_fraction_mae": fold_score["fraction_mae"],
        })
    with STABILITY_OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(stability[0]))
        writer.writeheader()
        writer.writerows(stability)

    observed_inside = sum(
        1 for row in read_csv(GAMMAS)
        if float(row["radius_fm_measured"]) /
        (int(row["Z"]) * R_E_FM) < 1
    )
    control_test = next(r for r in summaries
                        if r["model"] == "controls_only" and r["split"] == "test")
    beta_test = next(r for r in summaries
                     if r["model"] == "controls_plus_beta" and r["split"] == "test")
    beta_train = next(r for r in summaries
                      if r["model"] == "controls_plus_beta" and r["split"] == "train")

    print("GEOMETRY")
    print(f"measured_radii={int(stats['n'])} "
          f"inside_q1={int(stats['inside_q1'])} "
          f"inside_q2={int(stats['inside_q2'])}")
    print(f"beta_q1 min={stats['min_beta_q1']:.9g} "
          f"median={stats['median_beta_q1']:.9g} "
          f"max={stats['max_beta_q1']:.9g}")
    print("STRICT OPACITY")
    print(f"observed_gamma_transitions_inside_q1={observed_inside}")
    print("decision=EXCLUDED for zero-direct-gamma model")
    print("BOUNDARY RE-EMISSION BENCHMARK")
    print(f"ICC rows train={len(train)} test={len(test)} "
          f"classes={','.join(classes)}")
    print(f"controls test logit_RMSE={float(control_test['logit_rmse']):.6g} "
          f"fraction_MAE={float(control_test['fraction_mae']):.6g}")
    print(f"+beta test logit_RMSE={float(beta_test['logit_rmse']):.6g} "
          f"fraction_MAE={float(beta_test['fraction_mae']):.6g} "
          f"beta_coef={float(beta_train['beta_coefficient']):.6g}")
    improvement = (
        float(control_test["logit_rmse"]) -
        float(beta_test["logit_rmse"])
    )
    print(f"beta test improvement={improvement:.6g}")
    coefficients = np.array([float(r["beta_coefficient"]) for r in stability])
    print(f"beta LOO coefficient min={np.min(coefficients):.6g} "
          f"median={np.median(coefficients):.6g} "
          f"max={np.max(coefficients):.6g}")
    unique_train = {}
    for row in train:
        unique_train[str(row["nuclide"])] = (
            math.log(float(row["Z_value"])),
            math.log(float(row["beta_value"])),
        )
    z_values = np.array([value[0] for value in unique_train.values()])
    beta_values = np.array([value[1] for value in unique_train.values()])
    correlation = float(np.corrcoef(z_values, beta_values)[0, 1])
    condition = float(np.linalg.cond(design(train, classes, True)))
    print(f"effective_train_nuclides={len(unique_train)} "
          f"corr_logZ_logbeta={correlation:.6g} "
          f"design_condition={condition:.6g}")


if __name__ == "__main__":
    main()
