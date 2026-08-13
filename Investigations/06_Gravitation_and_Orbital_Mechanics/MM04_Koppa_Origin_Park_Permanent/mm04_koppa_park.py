#!/usr/bin/env python3
"""MM04 — expand Law-III candidate screen; park permanent if no independent match."""
from __future__ import annotations

import math
import sys

C = 299792458.0
HBAR = 1.054571817e-34
L_P = 1.616255e-35
M_P = 1.67262192369e-27
M_E = 9.1093837015e-31
ALPHA = 7.2973525693e-3
A0 = 5.29177210903e-11
R_E = 2.8179403262e-15
R_P = 8.414e-16
G = 6.67430e-11
R_CHARGE = math.sqrt(R_P * R_E)
# Law III structural scales (no G): unit area ~ R_p^2 * r_e^2, pressure via calibrated P_eff not used as free fit
P_EFF = 4.0 * (8.9875517923e9) * (1.602176634e-19)**2 / (math.pi * R_P**2 * R_E**2)


def rel(a, b):
    return abs(a - b) / abs(b) if b else float("inf")


def main() -> int:
    print("MM04 koppa_per_baryon independent-route screen + permanent park gate")
    print("pre-reg: OUTSTANDING_CLOSURE_43_PRE_REGISTRATION.md")

    k0 = (L_P * L_P * C * M_P) / HBAR
    print(f"  K0 target = {k0:.10e} m")
    print(f"  G m_p/c^2 = {G*M_P/(C*C):.10e} m  (SHARED via CODATA; not independent)")

    # New families beyond MM03 (still no fitted kappa)
    candidates = {
        "L1 R_p^4 / (a0 r_e^2)": (R_P**4) / (A0 * R_E**2),
        "L2 R_charge^4 / a0^3": (R_CHARGE**4) / (A0**3),
        "L3 r_e (R_p/a0)^3": R_E * (R_P / A0) ** 3,
        "L4 a0 * alpha^20": A0 * (ALPHA**20),
        "L5 hbar/(m_e c) * (m_e/m_p)^2 * alpha^2": (HBAR / (M_E * C)) * (M_E / M_P) ** 2 * (ALPHA**2),
        "L6 R_p * (m_e/m_p) * alpha^4": R_P * (M_E / M_P) * (ALPHA**4),
        "L7 R_e^2 / a0 * (m_e/m_p)": (R_E**2 / A0) * (M_E / M_P),
        "L8 (hbar/(m_p c))^2 / a0": (HBAR / (M_P * C)) ** 2 / A0,
        "L9 R_p^2 * r_e / a0^2": (R_P**2) * R_E / (A0**2),
        "L10 P_eff * R_p^6 / (hbar c)  [dim check]": P_EFF * (R_P**6) / (HBAR * C),
    }

    print("--- new candidates vs K0 ---")
    matches = []
    for name, val in candidates.items():
        # dimensional sanity: action-pressure form may not be meters
        r = rel(val, k0) if val > 0 else float("inf")
        tag = "MATCH" if r < 1e-3 else ("ORDER" if val > 0 and abs(math.log10(max(r, 1e-99))) < 1.5 else "EXCLUDED")
        if "hbar" in name.lower() and "l_P" not in name:
            # still uses hbar — allowed as measured input, but not Law-III occlusion geometry alone
            pass
        print(f"  {name:48s} = {val:.6e}  rel={r:.3e}  {tag}")
        if tag == "MATCH":
            matches.append(name)

    print("---")
    if matches:
        print(f"STATUS MM04_INDEPENDENT_SURVIVES matches={matches}")
        return 0

    print("STATUS MM04_PARKED_PERMANENT")
    print("  PUBLIC CLAIM BAN: do not state koppa_per_baryon is Law-III derived.")
    print("  Engine identity remains MEASURED/SHARED via l_P<->G risk_flag.")
    print("  Reopen only with new axiom or lattice simulation pre-registration.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
