"""Calibration and scoring for APS14a angular transition models."""

from __future__ import annotations

import math
from dataclasses import dataclass

import numpy as np
from scipy.optimize import least_squares

from . import constants as K
from .angular_models import predict_transition
from .transitions import TransitionStates


@dataclass
class AngularFit:
    model: str
    eta: float
    rho: float
    n: int
    k: int
    rss: float
    aicc: float
    bic: float
    covariance: list[list[float]]
    success: bool


def information_criteria(residual: np.ndarray, k: int) -> tuple[float, float, float]:
    n = len(residual)
    rss = float(residual @ residual)
    if rss <= 0:
        return rss, -math.inf, -math.inf
    aic = n * math.log(rss / n) + 2 * k
    aicc = aic + (2 * k * (k + 1) / (n - k - 1) if n > k + 1 else math.inf)
    bic = n * math.log(rss / n) + k * math.log(n)
    return rss, aicc, bic


def _parameters(model: str, vector: np.ndarray) -> tuple[float, float]:
    if model == "A3_ANISOTROPIC_OCCLUSION":
        return float(vector[0]), 0.0
    if model == "A4_CORE_DEPTH":
        return float(vector[0]), float(vector[1])
    return 0.0, 0.0


def signed_log_residual(prediction: np.ndarray, observed: np.ndarray) -> np.ndarray:
    result = np.empty(len(observed))
    positive = np.isfinite(prediction) & (prediction > 0)
    result[positive] = np.log(prediction[positive] / observed[positive])
    invalid = ~positive
    magnitude = np.where(np.isfinite(prediction[invalid]),
                         np.abs(prediction[invalid]), observed[invalid] * 100)
    result[invalid] = 4.0 + np.log1p(magnitude / observed[invalid])
    return result


def predict_rows(
    model: str,
    rows: list[dict],
    eta: float = 0.0,
    rho: float = 0.0,
    samples: int = 120,
    phase_divisions: int = 8,
) -> np.ndarray:
    values = []
    for row in rows:
        prediction = predict_transition(
            model, row["Z"], row["A"], row["states"], eta, rho,
            samples=samples, phase_divisions=phase_divisions,
        )
        values.append(prediction.energy_eV)
    return np.asarray(values)


def fit_angular_model(
    model: str,
    rows: list[dict],
    max_nfev: int = 24,
    grid_search: bool = True,
    initial: tuple[float, ...] | None = None,
) -> AngularFit:
    if model in {"A0_TRANSITION_FIX", "A1_PATHWAY", "A2_AXIS_AROUND"}:
        prediction = predict_rows(model, rows)
        observed = np.asarray([row["energy_eV"] for row in rows])
        residual = signed_log_residual(prediction, observed)
        rss, aicc, bic = information_criteria(residual, 0)
        return AngularFit(model, 0.0, 0.0, len(rows), 0, rss, aicc, bic, [], True)

    start = np.array([0.6]) if model == "A3_ANISOTROPIC_OCCLUSION" else np.array([0.6, 0.3])
    if initial is not None:
        start = np.asarray(initial, dtype=float)
    lower = np.array([-0.9]) if len(start) == 1 else np.array([-0.9, 0.0])
    upper = np.array([0.9]) if len(start) == 1 else np.array([0.9, 1.5])
    observed = np.asarray([row["energy_eV"] for row in rows])

    def objective(vector):
        eta, rho = _parameters(model, vector)
        prediction = predict_rows(
            model, rows, eta, rho, samples=72, phase_divisions=6
        )
        return signed_log_residual(prediction, observed)

    if grid_search:
        eta_grid = np.linspace(-0.8, 0.8, 9)
        rho_grid = [0.0] if len(start) == 1 else np.linspace(0.0, 1.5, 6)
        candidates = [
            np.array([eta]) if len(start) == 1 else np.array([eta, rho])
            for eta in eta_grid for rho in rho_grid
        ]
        scored = []
        for vector in candidates:
            trial = objective(vector)
            scored.append((float(trial @ trial), vector))
        start = min(scored, key=lambda item: item[0])[1]

    fit = least_squares(
        objective, start, bounds=(lower, upper), loss="soft_l1",
        f_scale=0.25, max_nfev=max_nfev,
        xtol=1e-5, ftol=1e-5, gtol=1e-5,
    )
    eta, rho = _parameters(model, fit.x)
    residual = objective(fit.x)
    rss, aicc, bic = information_criteria(residual, len(fit.x))
    covariance = np.linalg.pinv(fit.jac.T @ fit.jac).tolist()
    return AngularFit(
        model, eta, rho, len(rows), len(fit.x), rss, aicc, bic,
        covariance, bool(fit.success),
    )


def score(observed: np.ndarray, predicted: np.ndarray) -> dict:
    valid = np.isfinite(predicted) & (predicted > 0)
    if not np.any(valid):
        return {
            "n": 0, "coverage": 0.0, "median": math.nan,
            "rms": math.nan, "max": math.nan, "log_rmse": math.nan,
        }
    fraction = np.abs(predicted[valid] / observed[valid] - 1.0)
    return {
        "n": int(np.sum(valid)),
        "coverage": float(np.mean(valid)),
        "median": float(np.median(fraction)),
        "rms": float(np.sqrt(np.mean(fraction * fraction))),
        "max": float(np.max(fraction)),
        "log_rmse": float(np.sqrt(np.mean(
            np.log(predicted[valid] / observed[valid]) ** 2
        ))),
    }


def fit_quantum_defect(rows: list[dict]) -> np.ndarray:
    observed = np.asarray([row["energy_eV"] for row in rows])

    def predict(vector, source):
        sigma, ds, dp, dd = vector
        defect = {"s": ds, "p": dp, "d": dd, "f": dd}
        result = []
        for row in source:
            transition: TransitionStates = row["states"]
            nl, kl = transition.removed_subshell
            nu, ku = transition.added_subshell
            q = max(0.05, row["Z"] - sigma * (len(transition.lower) - 1))
            lower = max(0.2, nl - defect[kl])
            upper = max(0.2, nu - defect[ku])
            result.append(K.RY_EV * q * q * (1 / lower ** 2 - 1 / upper ** 2))
        return np.asarray(result)

    fit = least_squares(
        lambda vector: np.where(
            predict(vector, rows) > 0,
            np.log(np.maximum(predict(vector, rows), 1e-300) / observed),
            8.0,
        ),
        np.array([0.7, 0.2, 0.05, 0.02]),
        bounds=(np.zeros(4), np.array([1.2, 0.8, 0.8, 0.8])),
        loss="soft_l1", f_scale=0.25,
    )
    return fit.x


def predict_quantum_defect(vector: np.ndarray, rows: list[dict]) -> np.ndarray:
    sigma, ds, dp, dd = vector
    defect = {"s": ds, "p": dp, "d": dd, "f": dd}
    result = []
    for row in rows:
        transition: TransitionStates = row["states"]
        nl, kl = transition.removed_subshell
        nu, ku = transition.added_subshell
        q = max(0.05, row["Z"] - sigma * (len(transition.lower) - 1))
        lower = max(0.2, nl - defect[kl])
        upper = max(0.2, nu - defect[ku])
        result.append(K.RY_EV * q * q * (1 / lower ** 2 - 1 / upper ** 2))
    return np.asarray(result)
