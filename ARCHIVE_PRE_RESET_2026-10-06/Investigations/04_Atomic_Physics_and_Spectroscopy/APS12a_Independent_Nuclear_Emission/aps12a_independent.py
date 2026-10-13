#!/usr/bin/env python3
"""APS12a independent nuclear-koppa emission test.

Reads only APS12a's frozen hold-outs and canonical repository inputs.
"""
from __future__ import annotations

import csv
import hashlib
import math
from pathlib import Path

HERE = Path(__file__).resolve().parent
HOLDOUT = HERE / "aps12a_holdouts.csv"

# Canonical decimal literals from Engine/include/sdt/laws.hpp.
C = 299_792_458.0
H = 6.626_070_15e-34
E_CHARGE = 1.602_176_634e-19
ALPHA = 7.297_352_5693e-3
A0 = 5.291_772_109_03e-11
R_E = 2.817_940_3262e-15
R_P = 8.414e-16
M_E = 9.109_383_7015e-31
M_P = 1.672_621_923_69e-27
M_N = 1.674_927_498_04e-27
RY_EV = 13.605_693_122_994
R_INF = 1.097_373_156_8160e7

HC_EV_NM = H * C / E_CHARGE * 1e9
ME_C2_EV = M_E * C * C / E_CHARGE
R_DERIVED = M_E * C * ALPHA * ALPHA / (2 * H)


def reduced_mass_fraction(mass: float) -> float:
    return mass / (M_E + mass)


def mev_mass(value: float) -> float:
    return value * 1e6 * E_CHARGE / (C * C)


M_D = M_P + M_N - mev_mass(2.224)
M_T = M_P + 2 * M_N - mev_mass(8.482)
M_HE4 = 2 * M_P + 2 * M_N - mev_mass(28.296)


def nuclear_mass(Z: int, A: int) -> float:
    if (Z, A) == (1, 1):
        return M_P
    if (Z, A) == (1, 2):
        return M_D
    if (Z, A) == (1, 3):
        return M_T
    if (Z, A) == (2, 4):
        return M_HE4
    return A * M_P


def z_seat(Z_eff: int, n: int) -> float:
    return (Z_eff * ALPHA / n) ** 2


def lead_energy(Z_eff: int, n_low: int, n_high: int | None,
                mu_fraction: float) -> float:
    z_low = z_seat(Z_eff, n_low)
    z_high = z_seat(Z_eff, n_high) if n_high else 0.0
    return 0.5 * ME_C2_EV * (z_low - z_high) * mu_fraction


def law_v_energy(Z_eff: int, n_low: int, n_high: int | None,
                 mu_fraction: float) -> float:
    z_low = z_seat(Z_eff, n_low)
    z_high = z_seat(Z_eff, n_high) if n_high else 0.0

    def binding(z: float) -> float:
        return ME_C2_EV * (1.0 - math.sqrt(1.0 - z))

    return (binding(z_low) - binding(z_high)) * mu_fraction


def wavelength_route(Z: int, n_low: int, n_high: int, mass: float) -> float:
    inv = Z * Z * (1 / n_low**2 - 1 / n_high**2)
    return 1e9 / (R_DERIVED * reduced_mass_fraction(mass) * inv)


def rel(pred: float, obs: float) -> float:
    return abs(pred - obs) / abs(obs)


def ppm(pred: float, obs: float) -> float:
    return 1e6 * (pred - obs) / obs


def principal_n(electrons: int) -> int:
    # Frozen principal shell of the outermost occupied ground-state electron.
    if electrons <= 2:
        return 1
    if electrons <= 10:
        return 2
    if electrons <= 18:
        return 3
    if electrons <= 20:
        return 4
    if electrons <= 30:
        return 3
    return 4


def radius(A: int) -> float:
    eta = math.pi / math.sqrt(18)
    return R_P * (A / eta) ** (1 / 3)


def grammar(Z: int, A: int) -> tuple[int, int]:
    return 3 * Z - A - 2, A - 2 * Z


def read_rows() -> list[dict[str, str]]:
    with HOLDOUT.open(encoding="utf-8") as handle:
        return list(csv.DictReader(handle))


def write_csv(name: str, rows: list[dict[str, object]]) -> None:
    if not rows:
        return
    with (HERE / name).open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)


def main() -> None:
    frozen = read_rows()
    digest = hashlib.sha256(HOLDOUT.read_bytes()).hexdigest()
    print("APS12a INDEPENDENT RUN")
    print(f"holdout_rows={len(frozen)} sha256={digest}")
    print("APS12/Grok artifacts read: 0")

    # Phase 0
    koppa_rel = rel(ALPHA * ALPHA * A0, R_E)
    rydberg_rel = rel(0.5 * ME_C2_EV * ALPHA * ALPHA, RY_EV)
    rinf_rel = rel(R_DERIVED, R_INF)
    v0_pred = wavelength_route(1, 1, 2, M_P)
    v0_ppm = ppm(v0_pred, 121.5670)
    constants_ok = max(koppa_rel, rydberg_rel, rinf_rel) <= 1e-10
    v0_ok = constants_ok and abs(v0_ppm) <= 15
    print(f"P0 koppa_rel={koppa_rel:.6e} rydberg_rel={rydberg_rel:.6e} "
          f"rinf_rel={rinf_rel:.6e}")
    print(f"P0 H_2to1_nm={v0_pred:.9f} dppm={v0_ppm:.6f}")
    print(f"GATE V0={'MATCH' if v0_ok else 'INSTRUMENT_FAIL'}")
    if not v0_ok:
        raise SystemExit(1)

    # Phase 1
    excitation: list[dict[str, object]] = []
    for row in frozen:
        if row["corpus"] not in {"EXC_H", "EXC_LIGHT", "EXC_FE"}:
            continue
        Z, A = int(row["Z"]), int(row["A"])
        nlo, nhi = int(row["n_low"]), int(row["n_high"])
        obs = float(row["value"])
        mass = nuclear_mass(Z, A)
        mu = reduced_mass_fraction(mass)
        energy = lead_energy(Z, nlo, nhi, mu)
        lv = law_v_energy(Z, nlo, nhi, mu)
        lambda_dz = HC_EV_NM / energy
        lambda_r = wavelength_route(Z, nlo, nhi, mass)
        two_route = rel(lambda_dz, lambda_r)
        if row["quantity"] == "lambda_nm":
            residual = ppm(lambda_r, obs)
            obs_energy = HC_EV_NM / obs
        else:
            residual = rel(energy, obs)
            obs_energy = obs
        excitation.append({
            "corpus": row["corpus"], "species": row["species"], "Z": Z,
            "A": A, "transition": row["transition"], "n_low": nlo,
            "n_high": nhi, "koppa_fm": Z * R_E * 1e15,
            "z_low": z_seat(Z, nlo), "z_high": z_seat(Z, nhi),
            "delta_z": z_seat(Z, nlo) - z_seat(Z, nhi),
            "mu_over_me": mu, "E_lead_eV": energy, "E_LV_eV": lv,
            "dLV_over_lead": (lv - energy) / energy,
            "lambda_pred_nm": lambda_r, "lambda_obs_nm":
                obs if row["quantity"] == "lambda_nm" else HC_EV_NM / obs,
            "E_obs_eV": obs_energy, "residual":
                residual, "residual_unit":
                "ppm" if row["quantity"] == "lambda_nm" else "relative",
            "two_route_rel": two_route, "tag": "COMPUTED",
        })
    h = [abs(float(r["residual"])) for r in excitation
         if r["corpus"] == "EXC_H"]
    light = [abs(float(r["residual"])) for r in excitation
             if r["corpus"] == "EXC_LIGHT"]
    fe = next(r for r in excitation if r["corpus"] == "EXC_FE")
    g_h = max(h) <= 15
    g_light = max(light) <= 1000
    g_fe = float(fe["residual"]) <= 0.005
    g_two = max(float(r["two_route_rel"]) for r in excitation) <= 1e-9
    print(f"GATE G_EXC_H={'MATCH' if g_h else 'EXCLUDED'} max_ppm={max(h):.6f}")
    print(f"GATE G_EXC_light={'MATCH' if g_light else 'EXCLUDED'} "
          f"max_ppm={max(light):.6f}")
    print(f"GATE G_EXC_Fe={'MATCH' if g_fe else 'EXCLUDED'} "
          f"relative={float(fe['residual']):.9f} "
          f"dLV={float(fe['dLV_over_lead']):.9f}")
    print(f"GATE two_route={'MATCH' if g_two else 'INSTRUMENT_FAIL'}")
    write_csv("aps12a_excitation.csv", excitation)

    # Phase 2
    last_rows: list[dict[str, object]] = []
    for row in frozen:
        if row["corpus"] != "ION_LAST":
            continue
        Z, A = int(row["Z"]), int(row["A"])
        if not row["value"]:
            last_rows.append({"Z": Z, "A": A, "IE_pred_eV": "",
                              "IE_obs_eV": "", "relative": "",
                              "tag": "NO_DATA"})
            continue
        obs = float(row["value"])
        mu = reduced_mass_fraction(nuclear_mass(Z, A))
        pred = lead_energy(Z, 1, None, mu)
        last_rows.append({"Z": Z, "A": A, "IE_pred_eV": pred,
                          "IE_obs_eV": obs, "relative": rel(pred, obs),
                          "tag": "COMPUTED"})
    low = [float(r["relative"]) for r in last_rows
           if r["tag"] == "COMPUTED" and int(r["Z"]) <= 20]
    high = [float(r["relative"]) for r in last_rows
            if r["tag"] == "COMPUTED" and int(r["Z"]) > 20]
    g_last = max(low) <= 0.01 and max(high) <= 0.02
    print(f"GATE G_ION_last={'MATCH' if g_last else 'EXCLUDED'} "
          f"max_low={max(low):.9f} max_high={max(high):.9f}")
    write_csv("aps12a_ionisation_last.csv", last_rows)

    full_rows: list[dict[str, object]] = []
    hit_bare = hit_ion = scored = 0
    for row in frozen:
        if row["corpus"] != "ION_FULL" or not row["value"]:
            continue
        Z, A, k = int(row["Z"]), int(row["A"]), int(row["stage"])
        obs = float(row["value"])
        electrons_before = Z - k + 1
        n = principal_n(electrons_before)
        mu = reduced_mass_fraction(nuclear_mass(Z, A))
        bare = lead_energy(Z, n, None, mu)
        ion = lead_energy(k, n, None, mu)
        rb, ri = rel(bare, obs), rel(ion, obs)
        if k < Z:
            scored += 1
            hit_bare += int(rb < 0.10)
            hit_ion += int(ri < 0.10)
        full_rows.append({
            "Z": Z, "k": k, "electrons_before": electrons_before,
            "n_frozen": n, "E_bare_eV": bare, "E_ion_eV": ion,
            "E_obs_eV": obs, "rel_bare": rb, "rel_ion": ri,
            "closer": "bare" if rb < ri else "ion", "tag": "COMPUTED",
        })
    fraction_bare = hit_bare / scored
    fraction_ion = hit_ion / scored
    g_screen = max(fraction_bare, fraction_ion) >= 0.8
    print(f"GATE G_ION_S={'MATCH' if g_screen else 'OPEN'} "
          f"bare={hit_bare}/{scored} ion={hit_ion}/{scored}")
    write_csv("aps12a_ionisation_full.csv", full_rows)

    # Phase 3
    isotope: list[dict[str, object]] = []
    h_obs = next(float(r["value"]) for r in frozen
                 if r["corpus"] == "ISO_MASS" and r["species"] == "H I")
    d_obs = next(float(r["value"]) for r in frozen
                 if r["corpus"] == "ISO_MASS" and r["species"] == "D I")
    h_pred = wavelength_route(1, 1, 2, M_P)
    d_pred = wavelength_route(1, 1, 2, M_D)
    shift_pred, shift_obs = h_pred - d_pred, h_obs - d_obs
    mass_shift_rel = rel(shift_pred, shift_obs)
    g_mass = mass_shift_rel <= 0.05
    isotope.append({
        "channel": "I_mass", "pair": "H-D", "prediction": shift_pred,
        "observed": shift_obs, "metric": mass_shift_rel,
        "decision": "MATCH" if g_mass else "EXCLUDED",
    })
    sign_agree = 0
    for row in frozen:
        if row["corpus"] != "ISO_CA":
            continue
        A, Ap = map(int, row["transition"].split("->"))
        r_n = A0 * 4**2 / 20
        theta = 0.25 * (radius(A) / r_n) ** 2
        theta_p = 0.25 * (radius(Ap) / r_n) ** 2
        dtheta = theta_p - theta
        dr2 = float(row["value"])
        agree = (dtheta > 0) == (dr2 > 0)
        sign_agree += int(agree)
        isotope.append({
            "channel": "I_size", "pair": f"Ca-{A}->{Ap}",
            "prediction": dtheta, "observed": dr2,
            "metric": int(agree), "decision": "SIGN_AGREE" if agree else "SIGN_MISS",
        })
    g_size = sign_agree == 4
    for species, Z, masses in [("Ca", 20, [40, 42, 44, 46, 48]),
                               ("Yb", 70, [168, 170, 172, 174, 176])]:
        for A in masses:
            nd, nt = grammar(Z, A)
            landmark = "nt0" if nt == 0 else ("ntd" if nt == nd else "none")
            isotope.append({
                "channel": "I_grammar", "pair": f"{species}-{A}",
                "prediction": f"nd={nd};nt={nt}", "observed": "",
                "metric": landmark, "decision": "REPORT_ONLY",
            })
    print(f"GATE G_ISO_mass={'MATCH' if g_mass else 'EXCLUDED'} "
          f"relative={mass_shift_rel:.9f}")
    print(f"GATE G_ISO_size={'MATCH' if g_size else 'OPEN'} "
          f"sign={sign_agree}/4")
    write_csv("aps12a_isotope.csv", isotope)

    # Phase 4
    multi: list[dict[str, object]] = []
    for row in frozen:
        if row["corpus"] != "MULTI":
            continue
        Z, A = int(row["Z"]), int(row["A"])
        nlo, nhi, obs = int(row["n_low"]), int(row["n_high"]), float(row["value"])
        mu = reduced_mass_fraction(nuclear_mass(Z, A))
        same_n = nlo == nhi
        if same_n:
            bare = ion = 0.0
            note = "SAME_N_NULL"
        else:
            bare = lead_energy(Z, nlo, nhi, mu)
            z_ion = Z - 1 if row["species"] == "Fe XXV" else 1
            ion = lead_energy(z_ion, nlo, nhi, mu)
            note = ""
        multi.append({
            "species": row["species"], "transition": row["transition"],
            "E_obs_eV": obs, "E_bare_eV": bare, "E_ion_eV": ion,
            "rel_bare": rel(bare, obs), "rel_ion": rel(ion, obs),
            "note": note, "tag": "COMPUTED",
        })
    write_csv("aps12a_multi.csv", multi)
    print("GATE G_MULTI=TABLE_COMPLETE rows=4")

    native = g_h and g_light and (g_screen or g_size)
    if native:
        parent = "NATIVE_DISTINCT"
    elif g_h and g_light and g_last:
        parent = "CONVERGENCE_WITH_OPEN_DISTINCT_CHANNELS"
    else:
        parent = "EXCLUDED_OR_MIXED_SEE_GATES"
    print(f"PARENT_CLASS={parent}")
    print("END APS12a")


if __name__ == "__main__":
    main()
