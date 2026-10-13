#!/usr/bin/env python3
"""MM02 — screen ε_agg candidates (held-out target; no R_g in candidates)."""
from __future__ import annotations

import math
import sys

# MEASURED-INPUT (CODATA-family; mirror laws.hpp / MM01)
A0 = 5.29177210903e-11
ALPHA = 7.2973525693e-3
C = 299792458.0
G = 6.67430e-11
HBAR = 1.054571817e-34
L_P = 1.616255e-35
M_P = 1.67262192369e-27
M_SUN = 1.98847e30
M_U = 1.66053906660e-27
R_E = 2.8179403262e-15
R_P = 0.8414e-15


def log10_ratio(a: float, b: float) -> float:
    return math.log10(a / b)


def classify(cand: float, target: float) -> str:
    lr = abs(log10_ratio(cand, target))
    if lr < 1e-5:
        return "IDENTITY"
    if lr < 0.05:
        return "MATCH"
    if lr < 1.0:
        return "ORDER"
    return "EXCLUDED"


def main() -> int:
    print("MM02 epsilon_agg occlusion/packing candidate screen")
    print("pre-reg: MM02_PRE_REGISTRATION.md")
    print("--- validation ---")

    om_h = A0 * (ALPHA ** 2)
    r_g = G * M_SUN / (C * C)
    n_u = M_SUN / M_U
    n_p = M_SUN / M_P
    eps_u = r_g / (n_u * om_h)
    eps_p = r_g / (n_p * om_h)

    koppa_b = (L_P * L_P * C * M_P) / HBAR
    koppa_b_via_G = G * M_P / (C * C)
    lambda_p = HBAR / (M_P * C)

    ok_om = abs(om_h - R_E) / R_E < 1e-6
    ok_koppa = abs(koppa_b - koppa_b_via_G) / koppa_b_via_G < 1e-6
    c0 = koppa_b / om_h
    ok_id = abs(c0 - eps_p) / eps_p < 1e-5
    ok_census = abs((eps_u / eps_p) - (M_U / M_P)) / (M_U / M_P) < 1e-6

    print(f"  Om_H = a0*alpha^2 = {om_h:.10e} m")
    print(f"  r_e (CODATA)      = {R_E:.10e} m")
    print(f"  Om_H == r_e: {'PASS' if ok_om else 'FAIL'}")
    print(f"  koppa_per_baryon = l_P^2*c*m_p/hbar = {koppa_b:.10e} m")
    print(f"  G*m_p/c^2 (match)                    = {koppa_b_via_G:.10e} m")
    print(f"  koppa delete-test vs G*m_p/c^2: {'PASS' if ok_koppa else 'FAIL'}")
    print(f"  eps_u (MM01 m_u census) = {eps_u:.10e}")
    print(f"  eps_p (m_p census)      = {eps_p:.10e}")
    print(f"  eps_u/eps_p vs m_u/m_p: {'PASS' if ok_census else 'FAIL'}")
    print(f"  C0 = koppa_b/Om_H       = {c0:.10e}")
    print(f"  C0 == eps_p: {'PASS' if ok_id else 'FAIL'}")

    if not (ok_om and ok_koppa and ok_id and ok_census):
        print("STATUS MM02_INSTRUMENT_FAIL")
        return 1

    print("--- candidates (compare to eps_p; R_g/G/M forbidden in formulas) ---")
    cands = [
        ("C0", "koppa_b/Om_H", c0, "IDENTITY_ROUTE"),
        ("C1", "(l_P/r_e)^2", (L_P / om_h) ** 2, "packing"),
        ("C2", "4*pi*(l_P/r_e)^2", 4.0 * math.pi * (L_P / om_h) ** 2, "packing"),
        ("C3", "(l_P/R_p)^2", (L_P / R_P) ** 2, "packing"),
        ("C4", "R_p^2/(4*a0^2)", (R_P ** 2) / (4.0 * A0 * A0), "solid_angle"),
        ("C5", "alpha^4", ALPHA ** 4, "em_scale"),
        ("C6", "alpha^18", ALPHA ** 18, "alpha_power"),
        ("C7", "alpha^19", ALPHA ** 19, "alpha_power"),
        ("C8", "l_P^2/(lambda_p*r_e)", (L_P * L_P) / (lambda_p * om_h), "IDENTITY_TWIN"),
    ]

    n_match_non_twin = 0
    for cid, formula, val, kind in cands:
        cls = classify(val, eps_p)
        lr = log10_ratio(val, eps_p)
        note = ""
        if cid in ("C0", "C8") and cls == "IDENTITY":
            note = " SHARED-INPUT-risk: recovers G*m_p/(c^2*r_e) via l_P"
        if kind not in ("IDENTITY_ROUTE", "IDENTITY_TWIN") and cls == "MATCH":
            n_match_non_twin += 1
        print(
            f"  {cid} {formula:24s} = {val:.6e}  "
            f"log10(c/t)={lr:+.4f}  {cls}{note}"
        )

    print("--- relationship ---")
    print("  Wrong: Om_body = N * Om_H   (Om_H = EM c-boundary alpha^2 a0 = r_e)")
    print("  Engine micro quantum: koppa_per_baryon = l_P^2 * c * m_p / hbar")
    print("  Om_body = N_p * koppa_per_baryon recovers R_g (known-match)")
    print("  eps debt = koppa_per_baryon/Om_H — unit mismatch, not Om_H packing")
    print("  OPEN: Law-III origin of koppa_per_baryon without l_P<->G risk flag")
    alpha_mu = ALPHA * (M_P / 9.1093837015e-31)
    print(
        f"  C2 diagnostic: alpha*m_p/m_e = {alpha_mu:.6f}; 4*pi = {4*math.pi:.6f}; "
        f"ratio={alpha_mu/(4*math.pi):.6f} (C2 MATCH rides this near-equality)"
    )

    print("--- classification ---")
    if n_match_non_twin == 0:
        print("  packing/solid-angle/alpha candidates: no MATCH (C1-C7)")
        print("STATUS EPSILON_AGG_UNIT_CORRECTED")
        return 0
    print(f"  non-twin MATCH count = {n_match_non_twin} (see assessment for mechanism gate)")
    print("STATUS EPSILON_AGG_UNIT_CORRECTED__C2_NUMERIC_MATCH_OPEN")
    return 0


if __name__ == "__main__":
    sys.exit(main())
