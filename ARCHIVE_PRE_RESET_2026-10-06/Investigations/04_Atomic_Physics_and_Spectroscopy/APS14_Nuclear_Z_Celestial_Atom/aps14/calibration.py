"""Bounded global fitting of nested APS14 models."""

from __future__ import annotations

import math
from dataclasses import dataclass

import numpy as np

from .configurations import expand_configuration
from .dynamics import ModelParameters
from .observables import ionisation_prediction


@dataclass
class FitResult:
    name: str
    parameters: ModelParameters
    n_params: int
    n_rows: int
    rss: float
    aicc: float
    bic: float
    success: bool
    message: str
    covariance: list[list[float]] | None


def parameters_from_vector(name: str, vector: np.ndarray) -> ModelParameters:
    if name == "M0_HLIKE":
        return ModelParameters()
    if name in ("M1_MEAN_OCCLUSION", "M3_RELAXED_STATE"):
        g = float(vector[0])
        return ModelParameters(g_same=g, g_cross=g)
    g_same, g_cross, ds, dp, dd = [float(x) for x in vector]
    return ModelParameters(g_same, g_cross, ds, dp, dd)


def vector_bounds(name: str) -> tuple[np.ndarray, np.ndarray]:
    if name in ("M1_MEAN_OCCLUSION", "M3_RELAXED_STATE"):
        return np.array([0.0]), np.array([2.0])
    return (
        np.array([0.0, 0.0, 0.0, 0.0, 0.0]),
        np.array([2.0, 2.0, 0.8, 0.8, 0.8]),
    )


def _aicc_bic(rss: float, n: int, k: int) -> tuple[float, float]:
    if n <= 0 or rss <= 0:
        return math.nan, math.nan
    aic = n * math.log(rss / n) + 2 * k
    bic = n * math.log(rss / n) + k * math.log(n)
    if n > k + 1:
        aic += 2 * k * (k + 1) / (n - k - 1)
    return aic, bic


def residual_vector(
    name: str,
    vector: np.ndarray,
    rows: list[dict],
    configs: dict[int, list],
    masses: dict[int, int],
) -> np.ndarray:
    params = parameters_from_vector(name, vector)
    relaxed = name == "M3_RELAXED_STATE"
    out = []
    for row in rows:
        z = int(row["Z"])
        step = int(row["step"])
        obs = float(row["energy_eV"])
        pred, state, _, _ = ionisation_prediction(
            z, configs[z], step - 1, params, relaxed, masses.get(z)
        )
        if not math.isfinite(pred) or pred <= 0 or not state.physical:
            out.append(8.0)
            continue
        out.append(math.log(pred) - math.log(obs))
    return np.asarray(out, dtype=float)


def fit_model(
    name: str,
    rows: list[dict],
    configs: dict[int, list],
    masses: dict[int, int],
) -> FitResult:
    if name == "M0_HLIKE":
        resid = residual_vector(name, np.array([]), rows, configs, masses)
        rss = float(np.dot(resid, resid))
        aicc, bic = _aicc_bic(rss, len(resid), 0)
        return FitResult(
            name, ModelParameters(), 0, len(resid), rss, aicc, bic,
            True, "zero-parameter control", None,
        )

    from scipy.optimize import least_squares

    lo, hi = vector_bounds(name)
    x0 = (
        np.array([0.64])
        if name in ("M1_MEAN_OCCLUSION", "M3_RELAXED_STATE")
        else np.array([0.7, 0.35, 0.15, 0.05, 0.0])
    )
    result = least_squares(
        lambda x: residual_vector(name, x, rows, configs, masses),
        x0, bounds=(lo, hi), loss="soft_l1", f_scale=0.25,
        max_nfev=25 if name == "M3_RELAXED_STATE" else 80,
        xtol=1e-5, ftol=1e-5, gtol=1e-5,
    )
    resid = result.fun
    rss = float(np.dot(resid, resid))
    k = len(result.x)
    aicc, bic = _aicc_bic(rss, len(resid), k)
    covariance = None
    try:
        covariance = np.linalg.pinv(result.jac.T @ result.jac).tolist()
    except Exception:
        pass
    return FitResult(
        name, parameters_from_vector(name, result.x), k, len(resid),
        rss, aicc, bic, bool(result.success), result.message, covariance,
    )


def load_tables(data_dir):
    import csv
    from pathlib import Path

    data_dir = Path(data_dir)
    elements = list(csv.DictReader((data_dir / "elements.csv").open(encoding="utf-8")))
    ionisation = list(csv.DictReader((data_dir / "ionisation.csv").open(encoding="utf-8")))
    resonance = list(csv.DictReader((data_dir / "resonance.csv").open(encoding="utf-8")))
    configs = {
        int(row["Z"]): expand_configuration(row["configuration"])
        for row in elements
    }
    masses = {int(row["Z"]): int(row["A"]) for row in elements}
    splits = {int(row["Z"]): row["split"] for row in elements}
    return elements, ionisation, resonance, configs, masses, splits
