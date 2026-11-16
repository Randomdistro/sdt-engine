#!/usr/bin/env python3
"""Fit and cross-validate APS12b universal-carrier models."""
from __future__ import annotations

import csv
import math
from collections import defaultdict
from pathlib import Path

import numpy as np

HERE = Path(__file__).resolve().parent
INPUT = HERE / "data" / "atomic_lines.csv"
PRED_OUT = HERE / "carrier_predictions.csv"
SUMMARY_OUT = HERE / "carrier_model_summary.csv"
STRUCT_OUT = HERE / "carrier_structural_tests.csv"

ALPHA = 7.297_352_5693e-3
C = 299_792_458.0
R_INF = 1.097_373_156_8160e7
M_E = 9.109_383_7015e-31
M_P = 1.672_621_923_69e-27
M_N = 1.674_927_498_04e-27
E_CHARGE = 1.602_176_634e-19


def mev_mass(value: float) -> float:
    return value * 1e6 * E_CHARGE / (C * C)


M_D = M_P + M_N - mev_mass(2.224)
M_HE4 = 2 * M_P + 2 * M_N - mev_mass(28.296)


def mass(Z: int, A: int) -> float:
    if (Z, A) == (1, 1):
        return M_P
    if (Z, A) == (1, 2):
        return M_D
    if (Z, A) == (2, 4):
        return M_HE4
    return A * M_P


def mu_fraction(Z: int, A: int) -> float:
    m = mass(Z, A)
    return m / (M_E + m)


def load_rows() -> list[dict[str, object]]:
    rows: list[dict[str, object]] = []
    with INPUT.open(encoding="utf-8") as handle:
        for raw in csv.DictReader(handle):
            n_u = math.inf if raw["n_upper"] == "inf" else int(raw["n_upper"])
            n_l = int(raw["n_lower"])
            Z, A = int(raw["Z"]), int(raw["A"])
            z_u = 0.0 if math.isinf(n_u) else (Z * ALPHA / n_u) ** 2
            z_l = (Z * ALPHA / n_l) ** 2
            rows.append({
                **raw, "Z": Z, "A": A, "n_upper_value": n_u,
                "n_lower_value": n_l, "nu": float(raw["frequency_Hz"]),
                "z_upper": z_u, "z_lower": z_l, "delta_z": z_l - z_u,
            })
    return rows


def design(model: str, rows: list[dict[str, object]]) -> np.ndarray:
    if model.startswith("U_upper"):
        x = np.array([math.log1p(-float(r["z_upper"])) for r in rows])
    elif model.startswith("U_lower"):
        x = np.array([math.log1p(-float(r["z_lower"])) for r in rows])
    elif model.startswith("U_ratio"):
        x = np.array([
            math.log1p(-float(r["z_upper"])) -
            math.log1p(-float(r["z_lower"])) for r in rows
        ])
    elif model == "U_poly":
        x = np.array([float(r["delta_z"]) for r in rows])
        return np.column_stack([np.ones(len(rows)), x, x * x])
    else:
        raise ValueError(model)
    if model.endswith("_p1"):
        return np.ones((len(rows), 1))
    return np.column_stack([np.ones(len(rows)), x])


def fit_carrier(model: str, rows: list[dict[str, object]]) -> np.ndarray:
    X = design(model, rows)
    y = np.log([float(r["nu"]) for r in rows])
    if model.endswith("_p1"):
        if model.startswith("U_upper"):
            offset = np.array([math.log1p(-float(r["z_upper"])) for r in rows])
        elif model.startswith("U_lower"):
            offset = np.array([math.log1p(-float(r["z_lower"])) for r in rows])
        else:
            offset = np.array([
                math.log1p(-float(r["z_upper"])) -
                math.log1p(-float(r["z_lower"])) for r in rows
            ])
        return np.array([float(np.mean(y - offset))])
    return np.linalg.lstsq(X, y, rcond=None)[0]


def predict_carrier(model: str, params: np.ndarray,
                    rows: list[dict[str, object]]) -> np.ndarray:
    X = design(model, rows)
    y = X @ params
    if model.endswith("_p1"):
        if model.startswith("U_upper"):
            y += np.array([math.log1p(-float(r["z_upper"])) for r in rows])
        elif model.startswith("U_lower"):
            y += np.array([math.log1p(-float(r["z_lower"])) for r in rows])
        else:
            y += np.array([
                math.log1p(-float(r["z_upper"])) -
                math.log1p(-float(r["z_lower"])) for r in rows
            ])
    # Preserve catastrophic extrapolation as a finite scored residual rather
    # than allowing floating-point overflow to erase the row.
    return np.exp(np.clip(y, -700.0, 700.0))


def rydberg(rows: list[dict[str, object]]) -> np.ndarray:
    out = []
    for row in rows:
        n_u = float(row["n_upper_value"])
        n_l = int(row["n_lower_value"])
        delta = 1 / n_l**2 if math.isinf(n_u) else 1 / n_l**2 - 1 / n_u**2
        out.append(C * R_INF * mu_fraction(int(row["Z"]), int(row["A"]))
                   * int(row["Z"]) ** 2 * delta)
    return np.array(out)


def fit_ritz(rows: list[dict[str, object]]) -> np.ndarray:
    adjusted = []
    log_z = []
    for row in rows:
        n_u = float(row["n_upper_value"])
        n_l = int(row["n_lower_value"])
        delta = 1 / n_l**2 if math.isinf(n_u) else 1 / n_l**2 - 1 / n_u**2
        adjusted.append(math.log(float(row["nu"])) -
                        math.log(mu_fraction(int(row["Z"]), int(row["A"])) * delta))
        log_z.append(math.log(int(row["Z"])))
    X = np.column_stack([np.ones(len(rows)), log_z])
    return np.linalg.lstsq(X, np.array(adjusted), rcond=None)[0]


def predict_ritz(params: np.ndarray,
                 rows: list[dict[str, object]]) -> np.ndarray:
    out = []
    for row in rows:
        n_u = float(row["n_upper_value"])
        n_l = int(row["n_lower_value"])
        delta = 1 / n_l**2 if math.isinf(n_u) else 1 / n_l**2 - 1 / n_u**2
        if delta <= 0:
            out.append(0.0)
        else:
            out.append(
                math.exp(params[0]) * mu_fraction(int(row["Z"]), int(row["A"]))
                * int(row["Z"]) ** params[1] * delta
            )
    return np.array(out)


def metrics(obs: np.ndarray, pred: np.ndarray) -> dict[str, float]:
    frac = np.abs(pred - obs) / obs
    positive = pred > 0
    log_rmse = (
        float(np.sqrt(np.mean((np.log(pred[positive]) - np.log(obs[positive])) ** 2)))
        if np.any(positive) else math.inf
    )
    return {
        "log_rmse": log_rmse,
        "median_fractional": float(np.median(frac)),
        "max_fractional": float(np.max(frac)),
    }


def information_criteria(obs: np.ndarray, pred: np.ndarray,
                         parameter_count: int) -> tuple[float, float]:
    residual = np.log(obs) - np.log(pred)
    n = len(obs)
    rss = max(float(residual @ residual), 1e-300)
    aic = n * math.log(rss / n) + 2 * parameter_count
    aicc = (
        aic + 2 * parameter_count * (parameter_count + 1)
        / (n - parameter_count - 1)
        if n > parameter_count + 1 else math.inf
    )
    bic = n * math.log(rss / n) + parameter_count * math.log(n)
    return aicc, bic


def group_name(row: dict[str, object]) -> str:
    if row["corpus"] == "H_LINES":
        return "H_train" if row["split"] == "train" else "H_test"
    if row["corpus"] == "HLIKE_LINES":
        return "HeLi_holdout"
    if row["corpus"] == "HLIKE_LIMIT":
        return "series_limit_holdout"
    return "multi_final"


def structural_tests(rows: list[dict[str, object]]) -> list[dict[str, object]]:
    h_rows = [r for r in rows if r["corpus"] == "H_LINES"]
    output: list[dict[str, object]] = []
    for endpoint, key in [("upper", "n_upper_value"), ("lower", "n_lower_value")]:
        grouped: dict[float, list[float]] = defaultdict(list)
        for row in h_rows:
            grouped[float(row[key])].append(float(row["nu"]))
        for seat, values in sorted(grouped.items()):
            if len(values) < 2:
                continue
            ratio = max(values) / min(values)
            output.append({
                "model": f"U_{endpoint}", "shared_seat": seat,
                "transition_count": len(values),
                "max_to_min_frequency": ratio,
                "degeneracy_prediction": 1.0,
                "decision": "EXCLUDED" if ratio > 1.000001 else "SURVIVES",
            })
    return output


def main() -> None:
    rows = load_rows()
    train = [r for r in rows if r["corpus"] == "H_LINES" and r["split"] == "train"]
    ritz_train = train + [
        r for r in rows if r["corpus"] == "HLIKE_LINES" and int(r["Z"]) == 2
    ]
    carrier_models = [
        "U_upper_p1", "U_lower_p1", "U_ratio_p1",
        "U_upper", "U_lower", "U_ratio", "U_poly",
    ]

    structural = structural_tests(rows)
    with STRUCT_OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(structural[0]))
        writer.writeheader()
        writer.writerows(structural)

    predictions: list[dict[str, object]] = []
    summaries: list[dict[str, object]] = []

    fitted: dict[str, np.ndarray] = {
        model: fit_carrier(model, train) for model in carrier_models
    }
    ritz_params = fit_ritz(ritz_train)

    all_models = carrier_models + ["Ritz", "Rydberg"]
    for model in all_models:
        for group in ["H_train", "H_test", "HeLi_holdout",
                      "series_limit_holdout", "multi_final"]:
            subset = [r for r in rows if group_name(r) == group]
            if not subset:
                continue
            obs = np.array([float(r["nu"]) for r in subset])
            if model == "Rydberg":
                pred = rydberg(subset)
                params_text = "fixed"
                parameter_count = 0
            elif model == "Ritz":
                pred = predict_ritz(ritz_params, subset)
                params_text = ";".join(f"{x:.12g}" for x in ritz_params)
                parameter_count = 2
            else:
                pred = predict_carrier(model, fitted[model], subset)
                params_text = ";".join(f"{x:.12g}" for x in fitted[model])
                parameter_count = len(fitted[model])
            score = metrics(obs, pred)
            if group == "H_train" and np.all(pred > 0):
                aicc, bic = information_criteria(obs, pred, parameter_count)
            else:
                aicc = bic = math.nan
            summaries.append({
                "model": model, "evaluation_group": group,
                "n": len(subset), **score, "AICc_train": aicc,
                "BIC_train": bic, "parameters": params_text,
            })
            for row, value in zip(subset, pred):
                predictions.append({
                    "model": model, "evaluation_group": group,
                    "corpus": row["corpus"], "species": row["species"],
                    "Z": row["Z"], "n_upper": row["n_upper"],
                    "n_lower": row["n_lower"], "observed_Hz": row["nu"],
                    "predicted_Hz": value,
                    "fractional_error":
                        abs(value - float(row["nu"])) / float(row["nu"]),
                })

    with SUMMARY_OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(summaries[0]))
        writer.writeheader()
        writer.writerows(summaries)
    with PRED_OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(predictions[0]))
        writer.writeheader()
        writer.writerows(predictions)

    print("STRUCTURAL TESTS")
    for model in ["U_upper", "U_lower"]:
        relevant = [r for r in structural if r["model"] == model]
        worst = max(float(r["max_to_min_frequency"]) for r in relevant)
        print(f"{model}: EXCLUDED; worst shared-seat frequency ratio={worst:.6g}")
    print("MODEL TEST LOG-RMSE")
    for group in ["H_test", "HeLi_holdout", "series_limit_holdout", "multi_final"]:
        print(group)
        for model in all_models:
            row = next(r for r in summaries
                       if r["model"] == model and r["evaluation_group"] == group)
            print(f"  {model:12s} logRMSE={float(row['log_rmse']):.6g} "
                  f"median_frac={float(row['median_fractional']):.6g} "
                  f"max_frac={float(row['max_fractional']):.6g}")
    print(f"Ritz parameters logA={ritz_params[0]:.12g} s={ritz_params[1]:.12g}")


if __name__ == "__main__":
    main()
