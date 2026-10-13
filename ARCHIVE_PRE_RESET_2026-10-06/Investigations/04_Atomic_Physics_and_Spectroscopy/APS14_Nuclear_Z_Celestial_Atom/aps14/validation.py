"""Whole-corpus and held-out scoring, plus required physical diagnostics."""

from __future__ import annotations

import math

import numpy as np

from . import constants as K
from .baselines import rydberg_ie_eV, sequential_seats, slater_ie_eV, zeff_ie_eV
from .configurations import SeatLabel
from .dynamics import ModelParameters, solve_state
from .observables import excitation_observables, hlike_line, ionisation_prediction


def rel_err(pred: float, obs: float) -> float:
    if not math.isfinite(pred) or not math.isfinite(obs) or obs == 0:
        return math.nan
    return abs(pred - obs) / abs(obs)


def summarise(values: list[float]) -> dict:
    xs = [x for x in values if math.isfinite(x)]
    if not xs:
        return {
            "n": 0, "median": math.nan, "rms": math.nan,
            "max": math.nan, "frac10": math.nan,
        }
    arr = np.asarray(xs)
    return {
        "n": len(xs),
        "median": float(np.median(arr)),
        "rms": float(np.sqrt(np.mean(arr * arr))),
        "max": float(np.max(arr)),
        "frac10": float(np.mean(arr < 0.10)),
    }


def hlike_recovery_tests() -> list[dict]:
    params = ModelParameters()
    rows = []
    for Z in (1, 2, 3, 26):
        state = solve_state(Z, [SeatLabel(1, "s", 0)], params)
        r_exp = K.A0 / Z
        v_exp = Z * K.ALPHA * K.C
        z_exp = (Z * K.ALPHA) ** 2
        f_exp = K.OCCLUSION_K * Z / (r_exp ** 2)
        stiffness_exp = 2.0 * K.OCCLUSION_K * Z / (r_exp ** 3)
        rows.append({
            "Z": Z,
            "r_rel": rel_err(float(state.radii[0]), r_exp),
            "v_rel": rel_err(float(state.velocities[0]), v_exp),
            "z_rel": rel_err(float(state.depth_z[0]), z_exp),
            "F_rel": rel_err(float(state.force_nuclear[0]), f_exp),
            "stiff_rel": rel_err(float(state.stiffness[0]), stiffness_exp),
            "zk2": float(state.depth_z[0] * state.k_ratio[0] ** 2),
            "r_over_koppa": float(state.radii[0] / state.koppa_felt[0]),
            "physical": state.physical,
        })
    s1 = solve_state(1, [SeatLabel(1, "s", 0)], params)
    s2 = solve_state(2, [SeatLabel(1, "s", 0)], params)
    rows.append({
        "Z": "1/2-scale",
        "r_rel": rel_err(float(s1.radii[0] / s2.radii[0]), 2.0),
        "v_rel": rel_err(float(s2.velocities[0] / s1.velocities[0]), 2.0),
        "z_rel": rel_err(float(s2.depth_z[0] / s1.depth_z[0]), 4.0),
        "F_rel": rel_err(float(s2.force_nuclear[0] / s1.force_nuclear[0]), 8.0),
        "stiff_rel": rel_err(float(s2.stiffness[0] / s1.stiffness[0]), 16.0),
        "zk2": math.nan,
        "r_over_koppa": math.nan,
        "physical": s1.physical and s2.physical,
    })
    return rows


def score_ionisation(
    rows: list[dict],
    configs: dict,
    masses: dict,
    params: ModelParameters,
    relaxed: bool,
) -> tuple[list[dict], dict]:
    ledger = []
    rels = []
    for row in rows:
        if row["status"] != "MEASURED":
            continue
        z = int(row["Z"])
        step = int(row["step"])
        obs = float(row["energy_eV"])
        pred, state, _, relaxation = ionisation_prediction(
            z, configs[z], step - 1, params, relaxed, masses.get(z)
        )
        rel = rel_err(pred, obs)
        rels.append(rel)
        active = 0
        has_seats = bool(state.seats)
        ledger.append({
            **row,
            "pred_eV": pred,
            "rel": rel,
            "r_outer_m": float(state.radii[active]) if has_seats else math.nan,
            "z_outer": float(state.depth_z[active]) if has_seats else math.nan,
            "koppa_outer_m": (
                float(state.koppa_felt[active]) if has_seats else math.nan
            ),
            "q_outer": (
                float(state.q_effective[active]) if has_seats else math.nan
            ),
            "force_residual": (
                float(np.max(np.abs(state.force_residual)))
                if has_seats else math.nan
            ),
            "relaxation_eV": relaxation,
            "physical": state.physical,
            "converged": state.converged,
            "tag": "COMPUTED",
        })
    return ledger, summarise(rels)


def score_baselines(rows: list[dict], configs: dict, sigma: float) -> dict[str, dict]:
    buckets = {"rydberg": [], "slater": [], "zeff": []}
    for row in rows:
        if row["status"] != "MEASURED":
            continue
        z = int(row["Z"])
        seats = sequential_seats(configs[z], int(row["step"]))
        obs = float(row["energy_eV"])
        buckets["rydberg"].append(rel_err(rydberg_ie_eV(z, seats), obs))
        buckets["slater"].append(rel_err(slater_ie_eV(z, seats), obs))
        buckets["zeff"].append(rel_err(zeff_ie_eV(z, seats, sigma), obs))
    return {name: summarise(values) for name, values in buckets.items()}


def fit_zeff_sigma(rows: list[dict], configs: dict) -> float:
    """One global screening fraction. CALIBRATED(1) comparator."""
    from scipy.optimize import minimize_scalar

    def rss(sigma):
        total = 0.0
        count = 0
        for row in rows:
            if row["status"] != "MEASURED":
                continue
            z = int(row["Z"])
            seats = sequential_seats(configs[z], int(row["step"]))
            pred = zeff_ie_eV(z, seats, float(sigma))
            obs = float(row["energy_eV"])
            if pred > 0 and obs > 0:
                total += (math.log(pred) - math.log(obs)) ** 2
                count += 1
        return total if count else 1e9

    result = minimize_scalar(rss, bounds=(0.0, 1.2), method="bounded")
    return float(result.x)


def score_resonance(
    rows: list[dict],
    configs: dict,
    masses: dict,
    params: ModelParameters,
) -> tuple[list[dict], dict, dict]:
    untouched, hlike = [], []
    for row in rows:
        z = int(row["Z"])
        observed = float(row["energy_eV"])
        if row["set"] == "HLIKE_CONTROL" and row["lower_n"] and row["upper_n"]:
            emission, _, _ = hlike_line(
                z, int(row["lower_n"]), int(row["upper_n"]),
                params, masses.get(z),
            )
            bucket = hlike
        else:
            emission, _, _ = excitation_observables(
                z, configs[z], params, masses.get(z)
            )
            bucket = untouched
        record = {
            **row,
            "pred_eV": emission.energy_eV,
            "pred_hz": emission.frequency_hz,
            "pred_omega": emission.omega_rad_s,
            "pred_nm": (
                emission.wavelength_m * 1e9
                if math.isfinite(emission.wavelength_m) else math.nan
            ),
            "rel": rel_err(emission.energy_eV, observed),
            "tag": "COMPUTED",
        }
        bucket.append(record)
    return (
        untouched + hlike,
        summarise([row["rel"] for row in untouched]),
        summarise([row["rel"] for row in hlike]),
    )
