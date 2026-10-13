#!/usr/bin/env python3
"""APS11 — Lamb pair-breaking occupancy vs frozen experimental table.

Constants from Engine/include/sdt/laws.hpp measured (cited). No fitted k_Lamb.
"""
from __future__ import annotations

import math
import sys

# laws.hpp measured
C = 299_792_458.0
HBAR = 1.054_571_817e-34
H = 6.626_070_15e-34
ALPHA = 7.297_352_5693e-3
A0 = 5.291_772_109_03e-11
R_P = 8.414e-16  # m (laws.hpp measured; muonic)
M_E = 9.109_383_7015e-31
M_P = 1.672_621_923_69e-27
M_N = 1.674_927_498_04e-27
M_D = M_P + M_N - 2.224e6 * 1.602176634e-19 / C**2  # deuteron mass from B_d; FLAG
RY_EV = 13.605_693_122_994
EV = 1.602_176_634e-19
# He-4 nucleus mass (alpha); binding 28.3 MeV
M_ALPHA = 2 * M_P + 2 * M_N - 28.3e6 * EV / C**2
M_MU = 1.883_531_627e-28  # muon mass, CODATA-class; used only for μH control

# Frozen OBSERVED hold-outs (pre-reg)
H2_MHZ = 1057.8450
D2_MHZ = 1059.2341
H3_MHZ = 314.819
HE2_MHZ = 14041.13
H1_MHZ = 8172.840
MU_MEV = 202.3706  # CREMA whole 2S-2P

PPT08_DR_FM = 0.2722
PPT08_DV = 0.7034

MHZ_TO_J = H * 1e6
MEV_TO_J = 1e6 * EV


def mu_red(M: float) -> float:
    return M_E * M / (M_E + M)


def seat(Z: int, n: int, M: float) -> tuple[float, float, float]:
    mu = mu_red(M)
    r = A0 * (n * n) / Z * (M_E / mu)
    v = Z * ALPHA * C / n
    E = RY_EV * EV * (mu / M_E) * (Z * Z) / (n * n)  # |E_n| joules
    return r, v, E


def koppa_from_f(f_mhz: float, Z: int, n: int, M: float) -> tuple[float, float, float]:
    r, v, _E = seat(Z, n, M)
    dE = f_mhz * MHZ_TO_J
    mu = mu_red(M)
    dv = dE / (mu * v)
    dr = r * 2.0 * dv / v
    return dv, dr, r


def f_from_dE(dE_j: float) -> float:
    return dE_j / MHZ_TO_J


def rel(a: float, b: float) -> float:
    return abs(a - b) / abs(b)


def tag(r: float) -> str:
    if r < 0.10:
        return "MATCH"
    if r < 1.0:
        return "ORDER"
    return "EXCLUDED"


def main() -> int:
    print("APS11 Lamb pair-breaking occupancy")
    print("pre-reg: APS11_PRE_REGISTRATION.md")
    print("forbidden: 1051.8 literal, k_Lamb, QED as SDT, 137-fishing")
    print()

    # --- V1 instrument: PPT08 H2 map ---
    dv, dr, r2 = koppa_from_f(H2_MHZ, 1, 2, M_P)
    dr_fm = dr * 1e15
    v1_r = rel(dr_fm, PPT08_DR_FM)
    v1_v = rel(dv, PPT08_DV)
    v1 = v1_r < 0.01 and v1_v < 0.01
    print("--- V1 instrument (H2 koppa vs PPT08) ---")
    print(f"  r_2 = {r2:.6e} m")
    print(f"  dV = {dv:.4f} m/s  PPT08 {PPT08_DV}  rel={v1_v:.3e}")
    print(f"  |dR| = {dr_fm:.4f} fm  PPT08 {PPT08_DR_FM}  rel={v1_r:.3e}")
    print(f"  V1: {'PASS' if v1 else 'FAIL'}")

    print()
    print("--- Phase A: koppa re-expression (OBSERVED -> dV, dR) ---")
    rows = [
        ("H2", H2_MHZ, 1, 2, M_P, "MHz"),
        ("D2", D2_MHZ, 1, 2, M_D, "MHz"),
        ("H3", H3_MHZ, 1, 3, M_P, "MHz"),
        ("He2", HE2_MHZ, 2, 2, M_ALPHA, "MHz"),
        ("H1*", H1_MHZ, 1, 1, M_P, "MHz"),
    ]
    print(f"  {'id':5s} {'f_obs':>12s} {'dV m/s':>10s} {'|dR| fm':>10s} {'r_n fm':>12s}")
    for name, f, Z, n, M, _u in rows:
        dv_i, dr_i, r_i = koppa_from_f(f, Z, n, M)
        print(f"  {name:5s} {f:12.4f} {dv_i:10.4f} {dr_i*1e15:10.4f} {r_i*1e15:12.4f}")
    print("  H1* is L(1S) mapped as if a 1S-seat spacing (discriminator, not 1S-1P).")

    print()
    print("--- G_sign ---")
    print("  Measured: 2S_{1/2} ABOVE 2P_{1/2}.")
    print("  S1 complete-dyad => 2S lower: EXCLUDED by measurement")
    print("  S2 incomplete-dyad strain => 2S higher: MATCH sign")
    print("  G_sign: PASS (S2)")

    delta = {"Rp/3": R_P / 3.0, "Rp": R_P}

    # table seats for scoring
    table = [
        ("H2", H2_MHZ, 1, 2, M_P),
        ("H3", H3_MHZ, 1, 3, M_P),
        ("He2", HE2_MHZ, 2, 2, M_ALPHA),
    ]

    print()
    print("--- Phase B: declared cells vs table (rel<0.10 MATCH) ---")

    def pred_f(rule: str, delta_m: float, Z: int, n: int, M: float) -> float:
        r, v, En = seat(Z, n, M)
        mu = mu_red(M)
        if rule == "L1":
            dr_pred = delta_m
            dv_pred = 0.5 * v * (dr_pred / r)
            return f_from_dE(mu * v * dv_pred)
        if rule == "L2":
            dr_pred = delta_m * (n / 2.0)
            dv_pred = 0.5 * v * (dr_pred / r)
            return f_from_dE(mu * v * dv_pred)
        if rule == "E1":
            return f_from_dE(En * (delta_m / r))
        if rule == "E2":
            return f_from_dE(2.0 * En * (delta_m / r))
        if rule == "E3":
            return f_from_dE(En * (delta_m / A0))
        raise KeyError(rule)

    cells = []
    for dname, dval in delta.items():
        for rule in ("L1", "L2", "E1", "E2", "E3"):
            cells.append((rule, dname, dval))

    table_hits = []
    print(f"  {'cell':16s} {'H2 pred':>10s} {'H2':>8s} {'H3 pred':>10s} {'H3':>8s} {'He2 pred':>10s} {'He2':>8s} {'3/3':>4s}")
    for rule, dname, dval in cells:
        preds = []
        tags = []
        for name, fobs, Z, n, M in table:
            fp = pred_f(rule, dval, Z, n, M)
            preds.append(fp)
            tags.append(tag(rel(fp, fobs)))
        ok = all(t == "MATCH" for t in tags)
        if ok:
            table_hits.append(f"{rule}[{dname}]")
        print(
            f"  {rule+'['+dname+']':16s} "
            f"{preds[0]:10.2f} {tags[0]:>8s} "
            f"{preds[1]:10.2f} {tags[1]:>8s} "
            f"{preds[2]:10.2f} {tags[2]:>8s} "
            f"{'YES' if ok else 'no':>4s}"
        )

    print()
    print("--- HD reduced-mass (CONVERGENCE cap) ---")
    muH = mu_red(M_P)
    muD = mu_red(M_D)
    fD_pred = H2_MHZ * (muD / muH)
    r_hd = rel(fD_pred, D2_MHZ)
    print(f"  muD/muH = {muD/muH:.9f}")
    print(f"  f_D pred = {fD_pred:.4f}  obs {D2_MHZ:.4f}  rel={r_hd:.3e}  {tag(r_hd)}")
    print(f"  obs isotope split {D2_MHZ-H2_MHZ:.4f} MHz; pred {fD_pred-H2_MHZ:.4f} MHz")

    print()
    print("--- H1 discriminator (not table) ---")
    for rule, dname, dval in (("E1", "Rp/3", R_P / 3), ("E2", "Rp/3", R_P / 3)):
        fp = pred_f(rule, dval, 1, 1, M_P)
        print(f"  {rule}[{dname}] L(1S) pred={fp:.1f} MHz  obs={H1_MHZ:.1f}  rel={rel(fp,H1_MHZ):.3e}  {tag(rel(fp,H1_MHZ))}")

    print()
    print("--- muonic whole 2S-2P (G_mu; APS04 Fork-B death control) ---")
    # 202.3706 meV -> MHz
    mu_mhz = MU_MEV * 1e-3 * EV / MHZ_TO_J
    print(f"  obs 202.3706 meV = {mu_mhz:.3e} MHz")
    for rule in ("E1", "E2"):
        fp = pred_f(rule, R_P / 3, 1, 2, M_MU)
        # pred_f returns MHz via h; compare energy
        pred_mev = pred_f(rule, R_P / 3, 1, 2, M_MU) * MHZ_TO_J / EV * 1e3
        print(
            f"  {rule}[Rp/3] pred={pred_mev:.3e} meV  obs={MU_MEV:.4f}  "
            f"rel={rel(pred_mev, MU_MEV):.3e}  {tag(rel(pred_mev, MU_MEV))}"
        )

    print()
    print("--- rival leading (NOT SDT): ~ alpha^5 m c^2 Z^4 / n^3 ---")
    # Hartree: (alpha^5 m c^2)/ (2 pi) * Z^4/n^3  is order of magnitude; use
    # (ALPHA**5 * M_E * C**2 / H) * Z^4 / n^3  in Hz, no Bethe log.
    pre = (ALPHA**5 * M_E * C**2 / H)
    print(f"  prefactor alpha^5 m c^2 / h = {pre/1e6:.3f} MHz")
    for name, fobs, Z, n, M in table:
        fr = (pre / 1e6) * (Z**4) / (n**3)
        print(f"  RIV {name}: {fr:.1f} MHz vs {fobs:.1f}  rel={rel(fr,fobs):.3e}  {tag(rel(fr,fobs))}  [RIVAL]")

    print()
    print("--- APS04 nuclear-geometry term (named addend, not this quantum) ---")
    print("  +0.761 MHz on H n=2 quadrupole (APS04 2026-07-26). Fraction of H2:")
    print(f"  0.761/{H2_MHZ:.3f} = {0.761/H2_MHZ:.3e}")

    print()
    print("--- gates ---")
    print(f"  V1 instrument: {'PASS' if v1 else 'FAIL'}")
    print("  G_sign S2 (2S higher): PASS")
    print(f"  G_table 3/3 same cell: {table_hits or 'none'}")
    print(f"  G_HD reduced-mass: {tag(r_hd)}")
    g_table = len(table_hits) > 0
    if g_table:
        print(f"STATUS APS11_PAIR_BREAK_TABLE_SURVIVES cells={table_hits}")
    else:
        h2_only = []
        for rule, dname, dval in cells:
            fp = pred_f(rule, dval, 1, 2, M_P)
            if tag(rel(fp, H2_MHZ)) == "MATCH":
                h2_only.append(f"{rule}[{dname}]")
        print(f"  H2-only MATCH cells (look-elsewhere): {h2_only or 'none'}")
        print("STATUS APS11_SIGN_SURVIVES_MAGNITUDE_OPEN")
        print("  Pair-breaking names the forms and the sign (incomplete dyad => 2S high).")
        print("  No declared cell hits H2+H3+He2 together. PPT08 amplitude remains OPEN.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
