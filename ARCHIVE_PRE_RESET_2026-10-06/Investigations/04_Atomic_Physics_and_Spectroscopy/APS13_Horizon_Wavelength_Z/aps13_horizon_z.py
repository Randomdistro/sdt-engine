#!/usr/bin/env python3
"""APS13 — horizon z as wavelength modifier. Exploratory 2026-08-13.

Tests the black-hole / same-wavelength claim APS12 did not test.
Calibration allowed on a named train slice; verdict is the hold-out.
Constants from Engine/include/sdt/laws.hpp.
"""
from __future__ import annotations

import csv
import json
import math
import os
import statistics
import sys

# ── laws.hpp ──────────────────────────────────────────────────────────────
c = 299_792_458.0
h = 6.626_070_15e-34
e_charge = 1.602_176_634e-19
alpha = 7.297_352_5693e-3
a_0 = 5.291_772_109_03e-11
r_e = 2.817_940_3262e-15
R_p = 8.414e-16
m_e = 9.109_383_7015e-31
Ry_eV = 13.605_693_122_994
PI = math.pi

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, "..", "..", ".."))
JSON_IE = os.path.join(ROOT, "Datasets", "nuclear", "ionisation_energies.json")

ME_C2_EV = m_e * c * c / e_charge
HC_EV_NM = (h * c / e_charge) * 1e9
LAM_C_M = h / (m_e * c)
LAM_C_NM = LAM_C_M * 1e9

# OBSERVED stickers (APS12 T1)
LYA_H_NM = 121.567
LYB_H_NM = 102.5722
HA_H_NM = 656.4614
LYA_HE_NM = 30.3785
LYA_LI_NM = 13.5006
LYA_FE_NM = 0.178074  # Fe XXVI 2→1 centroid

COMMON_A = {
    1: 1, 2: 4, 3: 7, 4: 9, 5: 11, 6: 12, 7: 14, 8: 16, 9: 19, 10: 20,
    11: 23, 12: 24, 13: 27, 14: 28, 15: 31, 16: 32, 17: 35, 18: 40, 19: 39,
    20: 40, 26: 56, 29: 63,
}

TRAIN_Z = [2, 4, 6, 8, 10]
HOLD_Z = [3, 5, 7, 9, 11, 12, 18, 20, 26]


def nuclear_boundary_radius(A: int) -> float:
    eta = PI / math.sqrt(18.0)
    return R_p * (A / eta) ** (1.0 / 3.0)


def alpha_grammar(Z: int, A: int) -> tuple[int, int, bool]:
    n_t = A - 2 * Z
    n_d = 3 * Z - A - 2
    return n_d, n_t, (n_d >= 0 and n_t >= 0)


def n_of_outermost(N: int) -> int:
    if N <= 0:
        return 1
    if N <= 2:
        return 1
    if N <= 10:
        return 2
    if N <= 18:
        return 3
    if N <= 20:
        return 4
    if N <= 30:
        return 3
    if N <= 36:
        return 4
    if N <= 38:
        return 5
    if N <= 48:
        return 4
    if N <= 54:
        return 5
    if N <= 56:
        return 6
    if N <= 80:
        return 4 if N <= 70 else 5
    return 6


def z_seat(Zeff: float, n: int) -> float:
    return (Zeff * alpha / n) ** 2


def E_lead_eV(z_lo: float, z_hi: float) -> float:
    return 0.5 * ME_C2_EV * (z_lo - z_hi)


def E_LV_bind_eV(z: float) -> float:
    if z >= 1.0:
        return float("nan")
    return ME_C2_EV * (1.0 - math.sqrt(1.0 - z))


def rel_err(pred: float, obs: float) -> float:
    if obs == 0:
        return float("nan")
    return abs(pred - obs) / abs(obs)


def pct(x: float) -> str:
    if x != x:
        return "nan"
    return f"{100.0 * x:.4f}%"


def write_csv(path: str, rows: list[dict], fields: list[str]) -> None:
    with open(path, "w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fields, extrasaction="ignore")
        w.writeheader()
        for r in rows:
            w.writerow(r)


def geometry() -> list[dict]:
    rows = []

    def add(name, koppa, r, note):
        z = koppa / r if r > 0 else float("nan")
        k = math.sqrt(r / koppa) if koppa > 0 and r > 0 else float("nan")
        cfar = c * (1.0 - z) ** 2 if z < 1 else 0.0
        rows.append({
            "seat": name,
            "koppa_m": koppa,
            "r_m": r,
            "z": z,
            "k": k,
            "inside_horizon": z >= 1.0,
            "c_far_over_c": (cfar / c) if z < 1 else 0.0,
            "fill_R_over_koppa": r / koppa if koppa else float("nan"),
            "note": note,
        })

    add("H koppa (c-boundary)", r_e, r_e, "this atom, z=1")
    add("H proton surface", r_e, R_p, "this nucleus vs this ϟ")
    add("H electron n=1", r_e, a_0, "this n=1 vs this ϟ")
    add("H electron n=2", r_e, 4.0 * a_0, "this n=2 vs this ϟ")
    add("H electron n=3", r_e, 9.0 * a_0, "this n=3 vs this ϟ")
    add("He+ koppa", 2.0 * r_e, 2.0 * r_e, "this ion, z=1")
    add("He+ electron n=1", 2.0 * r_e, a_0 / 2.0, "this n=1 vs this ϟ")
    add("Fe26+ koppa", 26.0 * r_e, 26.0 * r_e, "this ion, z=1")
    add("Fe26+ electron n=1", 26.0 * r_e, a_0 / 26.0, "this n=1 vs this ϟ")
    R_Fe = nuclear_boundary_radius(56)
    add("Fe-56 nuclear boundary vs Fe koppa", 26.0 * r_e, R_Fe, "this nucleus vs this ϟ")
    return rows


def maps_from_ref(n_hi: int, n_lo: int, Z: float, lam_ref: float, z_ref_lo: float, z_ref_hi: float, obs: float, name: str) -> dict:
    z_lo = z_seat(Z, n_lo)
    z_hi = z_seat(Z, n_hi)
    lam_A = lam_ref * (1.0 + z_lo) / (1.0 + z_ref_lo)
    lam_B1 = lam_ref * (1.0 - z_ref_lo) / (1.0 - z_lo)
    lam_B2 = lam_ref * ((1.0 - z_ref_lo) / (1.0 - z_lo)) ** 2
    dZ_ref = z_ref_lo - z_ref_hi
    dZ = z_lo - z_hi
    lam_D = lam_ref * dZ_ref / dZ
    E_C = E_lead_eV(z_lo, z_hi)
    lam_C = HC_EV_NM / E_C
    return {
        "target": name,
        "Z": Z,
        "n_high": n_hi,
        "n_low": n_lo,
        "lam_obs_nm": obs,
        "lam_A_frac_nm": lam_A,
        "rel_A": rel_err(lam_A, obs),
        "lam_B_clock_nm": lam_B1,
        "rel_B": rel_err(lam_B1, obs),
        "lam_B_cfar_nm": lam_B2,
        "rel_B2": rel_err(lam_B2, obs),
        "lam_D_stretch_nm": lam_D,
        "rel_D": rel_err(lam_D, obs),
        "lam_C_halfmc2_nm": lam_C,
        "rel_C": rel_err(lam_C, obs),
        "z_low": z_lo,
        "dZ": dZ,
    }


def d0_hydrogen_self() -> list[dict]:
    """Hydrogen series from hydrogen's own Lyα and own z_n."""
    z1, z2 = z_seat(1.0, 1), z_seat(1.0, 2)
    return [
        maps_from_ref(3, 1, 1.0, LYA_H_NM, z1, z2, LYB_H_NM, "H I Lyβ 3→1"),
        maps_from_ref(3, 2, 1.0, LYA_H_NM, z1, z2, HA_H_NM, "H I Hα 3→2"),
    ]


def d1_Hlike_family() -> list[dict]:
    """Same 2→1 on the H-like family. Rest = H I Lyα."""
    z1, z2 = z_seat(1.0, 1), z_seat(1.0, 2)
    return [
        maps_from_ref(2, 1, 2.0, LYA_H_NM, z1, z2, LYA_HE_NM, "He II 2→1"),
        maps_from_ref(2, 1, 3.0, LYA_H_NM, z1, z2, LYA_LI_NM, "Li III 2→1"),
    ]


def d2_Hlike() -> list[dict]:
    rows = []
    zH1, zH2 = z_seat(1, 1), z_seat(1, 2)
    dZ_H = zH1 - zH2
    # remainder coeff from Z=1,2,3 last-electron-style 2→1 vs stretch,
    # using Law V ratio at those Z (not a free a from Fe)
    for Z, obs, tag in [
        (1, LYA_H_NM, "H I"),
        (2, LYA_HE_NM, "He II"),
        (3, LYA_LI_NM, "Li III"),
        (26, LYA_FE_NM, "Fe XXVI"),
    ]:
        z1, z2 = z_seat(Z, 1), z_seat(Z, 2)
        lam_D = LYA_H_NM * dZ_H / (z1 - z2)
        E_C = E_lead_eV(z1, z2)
        lam_C = HC_EV_NM / E_C
        E_LV = E_LV_bind_eV(z1) - E_LV_bind_eV(z2)
        lam_LV = HC_EV_NM / E_LV
        rows.append({
            "species": tag,
            "Z": Z,
            "lam_obs_nm": obs,
            "lam_stretch_from_H_nm": lam_D,
            "rel_D": rel_err(lam_D, obs),
            "lam_halfmc2_nm": lam_C,
            "rel_C": rel_err(lam_C, obs),
            "lam_LawV_nm": lam_LV,
            "rel_LV": rel_err(lam_LV, obs),
            "z1": z1,
            "dLV_over_E": (E_LV / E_C - 1.0),
        })
    # one-parameter a from Z=1,2,3: E = E_C (1 + a z1), fit median a, test Z=26
    a_vals = []
    for Z, obs in [(1, LYA_H_NM), (2, LYA_HE_NM), (3, LYA_LI_NM)]:
        z1, z2 = z_seat(Z, 1), z_seat(Z, 2)
        E_C = E_lead_eV(z1, z2)
        E_obs = HC_EV_NM / obs
        a_vals.append((E_obs / E_C - 1.0) / z1)
    a_med = statistics.median(a_vals)
    z1, z2 = z_seat(26, 1), z_seat(26, 2)
    E_C = E_lead_eV(z1, z2)
    E_fit = E_C * (1.0 + a_med * z1)
    lam_fit = HC_EV_NM / E_fit
    rows.append({
        "species": "Fe XXVI CALIBRATED(1) a from Z=1,2,3",
        "Z": 26,
        "lam_obs_nm": LYA_FE_NM,
        "lam_stretch_from_H_nm": float("nan"),
        "rel_D": float("nan"),
        "lam_halfmc2_nm": lam_fit,
        "rel_C": rel_err(lam_fit, LYA_FE_NM),
        "lam_LawV_nm": float("nan"),
        "rel_LV": float("nan"),
        "z1": z1,
        "dLV_over_E": a_med,
    })
    return rows, a_med, a_vals


def load_ie() -> dict[int, list[float]]:
    with open(JSON_IE, encoding="utf-8") as f:
        raw = json.load(f)
    out = {}
    for k, v in raw.items():
        out[int(k)] = [float(x) for x in v]
    return out


def invert_sigma(Z: int, k: int, IE: float) -> tuple[int, float, float, float]:
    N_e = Z - k + 1
    n = n_of_outermost(N_e)
    # IE = Ry Z_eff^2 / n^2
    if IE <= 0:
        return n, float("nan"), float("nan"), float("nan")
    Zeff = n * math.sqrt(IE / Ry_eV)
    if N_e <= 1:
        return n, Zeff, float("nan"), 0.0
    sig = (Z - Zeff) / (N_e - 1)
    return n, Zeff, sig, float(N_e - 1)


def d3_occupancy(ie: dict[int, list[float]]):
    train_rows = []
    sig_by_n: dict[int, list[float]] = {}
    for Z in TRAIN_Z:
        series = ie.get(Z, [])
        for k, E in enumerate(series, start=1):
            n, Zeff, sig, Ninner = invert_sigma(Z, k, E)
            rec = {
                "split": "train",
                "Z": Z,
                "k": k,
                "n": n,
                "IE_eV": E,
                "Zeff_obs": Zeff,
                "sigma_inv": sig,
                "N_inner": Ninner,
            }
            train_rows.append(rec)
            if sig == sig and Ninner > 0:
                sig_by_n.setdefault(n, []).append(sig)

    sigma_n = {n: statistics.median(v) for n, v in sorted(sig_by_n.items())}
    sigma_global = statistics.median(
        [r["sigma_inv"] for r in train_rows if r["sigma_inv"] == r["sigma_inv"]]
    )

    def predict(Z, k, E, split, sigma_map, tag):
        N_e = Z - k + 1
        n = n_of_outermost(N_e)
        Ninner = max(N_e - 1, 0)
        if tag == "bare":
            Zeff = float(Z)
        elif tag == "ion":
            Zeff = float(k)
        elif tag == "sigma_n":
            s = sigma_map.get(n, sigma_global)
            Zeff = Z - s * Ninner
        else:
            Zeff = Z - sigma_global * Ninner
        if Zeff <= 0:
            Epred = float("nan")
        else:
            Epred = Ry_eV * (Zeff ** 2) / (n ** 2)
        A = COMMON_A.get(Z)
        n_d = n_t = None
        ok = False
        if A is not None:
            n_d, n_t, ok = alpha_grammar(Z, A)
        return {
            "split": split,
            "model": tag,
            "Z": Z,
            "k": k,
            "n": n,
            "A": A if A else "",
            "n_d": n_d if ok else "",
            "n_t": n_t if ok else "",
            "IE_obs": E,
            "IE_pred": Epred,
            "rel": rel_err(Epred, E) if Epred == Epred else float("nan"),
            "Zeff": Zeff,
        }

    hold_rows = []
    models = ("bare", "ion", "sigma_n", "sigma_1")
    for Z in HOLD_Z:
        series = ie.get(Z, [])
        for k, E in enumerate(series, start=1):
            if E <= 0:
                continue
            for tag in models:
                hold_rows.append(predict(Z, k, E, "hold", sigma_n, tag))

    train_score = []
    for Z in TRAIN_Z:
        series = ie.get(Z, [])
        for k, E in enumerate(series, start=1):
            for tag in models:
                train_score.append(predict(Z, k, E, "train", sigma_n, tag))

    return train_rows, sigma_n, sigma_global, hold_rows, train_score


def summarise(rows: list[dict], model: str, split: str) -> dict:
    xs = [r["rel"] for r in rows if r["model"] == model and r["split"] == split and r["rel"] == r["rel"]]
    if not xs:
        return {"n": 0, "median": float("nan"), "p80": float("nan"), "frac10": float("nan")}
    xs.sort()
    n = len(xs)
    p80 = xs[min(n - 1, int(0.8 * n))]
    frac10 = sum(1 for x in xs if x < 0.10) / n
    return {"n": n, "median": statistics.median(xs), "p80": p80, "frac10": frac10}


def main() -> int:
    print("APS13 horizon z as wavelength modifier")
    print("exploratory; calibration allowed; verdict = hold-out")
    print()

    geo = geometry()
    write_csv(os.path.join(HERE, "aps13_geometry.csv"), geo, list(geo[0].keys()))
    print("GEOMETRY")
    for r in geo:
        print(
            f"  {r['seat']:<32s} z={r['z']:.6g}  k={r['k']:.4g}  "
            f"inside={r['inside_horizon']}  {r['note']}"
        )
    print(f"  H nucleus fill of H koppa: {R_p / r_e:.4f}")
    print(f"  H n=1 in units of H koppa: {a_0 / r_e:.4f}")
    print(f"  H n=2 / n=1 radius: {4.0:.1f}   z1/z2 = {z_seat(1,1)/z_seat(1,2):.1f}")
    print(f"  Fe XXVI n=1 in units of Fe koppa: {(a_0 / 26.0) / (26.0 * r_e):.4f}")
    print()

    def dump_maps(label: str, rows: list[dict], path: str) -> None:
        write_csv(os.path.join(HERE, path), rows, list(rows[0].keys()))
        print(label)
        for r in rows:
            print(
                f"  {r['target']}: obs={r['lam_obs_nm']} nm"
                f"  A_frac rel={pct(r['rel_A'])}"
                f"  B_clock rel={pct(r['rel_B'])}"
                f"  D_stretch rel={pct(r['rel_D'])}"
                f"  C_½mc² rel={pct(r['rel_C'])}"
            )

    d0 = d0_hydrogen_self()
    dump_maps("D0  hydrogen against itself (rest = H I Lyα)", d0, "aps13_D0_hydrogen.csv")
    print("  A,B: fractional/clock cannot make Hα from Lyα on hydrogen's own z_n.")
    print("  D: stretch by Δz on this atom's seats.")
    print()

    d1 = d1_Hlike_family()
    dump_maps("D1  H-like family, same 2→1 (rest = H I Lyα)", d1, "aps13_D1_same_wavelength.csv")
    print("  same well, deeper ϟ_Z. D is Z² at fixed excitation.")
    print()

    d2, a_med, a_vals = d2_Hlike()
    write_csv(os.path.join(HERE, "aps13_D2_Hlike.csv"), d2, list(d2[0].keys()))
    print("D2  H-like 2→1")
    for r in d2:
        print(
            f"  {r['species']:<40s} D={pct(r['rel_D'])}  "
            f"C={pct(r['rel_C'])}  LV={pct(r['rel_LV'])}"
        )
    print(f"  CALIBRATED(1) a from Z=1,2,3: a={a_med:.6g}  (per-Z a={a_vals})")
    print()

    ie = load_ie()
    train_inv, sigma_n, sigma_g, hold, train_sc = d3_occupancy(ie)
    write_csv(
        os.path.join(HERE, "aps13_D3_train_sigma.csv"),
        train_inv,
        list(train_inv[0].keys()),
    )
    write_csv(os.path.join(HERE, "aps13_D3_holdout.csv"), hold, list(hold[0].keys()))
    print("D3  occupancy  train Z={2,4,6,8,10}  hold Z={3,5,7,9,11,12,18,20,26}")
    print("  CALIBRATED sigma_n (median inverted on train, N_e>1):")
    for n, s in sorted(sigma_n.items()):
        print(f"    n={n}  σ={s:.5f}")
    print(f"  CALIBRATED(1) global σ={sigma_g:.5f}")
    print("  hold-out relative error:")
    for model in ("bare", "ion", "sigma_n", "sigma_1"):
        h = summarise(hold, model, "hold")
        t = summarise(train_sc, model, "train")
        print(
            f"    {model:<8s} hold N={h['n']:3d}  med={pct(h['median'])}  "
            f"p80={pct(h['p80'])}  <10%={h['frac10']:.3f}   "
            f"train med={pct(t['median'])}  <10%={t['frac10']:.3f}"
        )

    def slice_print(label, pred):
        print(f"  hold-out {label}:")
        for model in ("bare", "ion", "sigma_n", "sigma_1"):
            xs = [r["rel"] for r in hold if r["model"] == model and pred(r) and r["rel"] == r["rel"]]
            if not xs:
                print(f"    {model:<8s} n=0")
                continue
            xs.sort()
            n = len(xs)
            print(
                f"    {model:<8s} N={n:3d}  med={pct(statistics.median(xs))}  "
                f"p80={pct(xs[min(n - 1, int(0.8 * n))])}  "
                f"<10%={sum(x < 0.10 for x in xs) / n:.3f}  max={pct(max(xs))}"
            )

    slice_print("first IE (k=1)", lambda r: r["k"] == 1)
    slice_print("inner (1<k<Z)", lambda r: 1 < r["k"] < r["Z"])
    slice_print("last electron (k=Z)", lambda r: r["k"] == r["Z"])
    slice_print("n=1 seats", lambda r: r["n"] == 1)
    slice_print("n>1 seats", lambda r: r["n"] > 1)

    print()
    print("CLASS")
    print("  map A fractional (1+z): excluded on hydrogen's own series")
    print("  map B clock/c_far:      excluded on hydrogen's own series")
    print("  map D stretch Δz:       MATCH on H series and H-like 2→1")
    print("  map C ½mc²Δz:           same closed form as D; origin this atom's Δz")
    print("  Law V H-like:           scored on this ion's z; Fe XXVI discriminator")
    print("  occupancy:              hold-out of this table; first vs inner vs last")
    print("END APS13")
    return 0


if __name__ == "__main__":
    sys.exit(main())
