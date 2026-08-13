#!/usr/bin/env python3
"""MM01 — compute ε_agg debt from naive N·ϟ_H vs solar GM/c² (no mechanism claim)."""
from __future__ import annotations

import math
import sys

# CODATA / IAU-style constants (MEASURED-INPUT)
A0 = 5.29177210903e-11          # m
ALPHA = 7.2973525693e-3
C = 299792458.0                   # m/s
G = 6.67430e-11                   # m^3 kg^-1 s^-2
M_SUN = 1.98847e30                # kg
M_U = 1.66053906660e-27           # kg (atomic mass unit)


def main() -> int:
    print("MM01 micro->macro aggregation factor eps_agg")
    print("pre-reg: MM01_PRE_REGISTRATION.md")

    om_h = A0 * (ALPHA ** 2)
    r_g = G * M_SUN / (C * C)
    n = M_SUN / M_U
    naive = n * om_h
    eps = r_g / naive
    ratio = naive / r_g

    print(f"  Om_H = a0*alpha^2 = {om_h:.10e} m   (expect ~2.81794e-15)")
    print(f"  R_g_sun = GM/c^2 = {r_g:.6f} m   (expect ~1476.6)")
    print(f"  N ~ M_sun/m_u = {n:.6e}")
    print(f"  N*Om_H = {naive:.6e} m")
    print(f"  eps_agg := R_g/(N*Om_H) = {eps:.6e}")
    print(f"  (N*Om_H)/R_g = {ratio:.6e}")

    ok_om = abs(om_h - 2.8179403262e-15) / 2.8179403262e-15 < 1e-6
    ok_rg = abs(r_g - 1476.6) / 1476.6 < 5e-3
    ok_eps = 1e-41 < eps < 1e-38
    print(f"  identity Om_H~r_e: {'PASS' if ok_om else 'FAIL'}")
    print(f"  R_g~1476.6 m: {'PASS' if ok_rg else 'FAIL'}")
    print(f"  eps_agg in 1e-41..1e-38: {'PASS' if ok_eps else 'FAIL'}")

    print("---")
    print("CLASSIFICATION:")
    print("  naive Om_body=N*Om_H : FORMAL_DEFECT (overshoot ~1e40)")
    print("  eps_agg magnitude    : COMPUTED debt (not a prediction)")
    print("  occlusion derivation of eps_agg : OPEN / UNDERDETERMINED")
    if ok_om and ok_rg and ok_eps:
        print("STATUS MM01_EPSILON_AGG_DEBT_RECORDED")
        return 0
    print("STATUS MM01_EPSILON_AGG_INSTRUMENT_FAIL")
    return 1


if __name__ == "__main__":
    sys.exit(main())
