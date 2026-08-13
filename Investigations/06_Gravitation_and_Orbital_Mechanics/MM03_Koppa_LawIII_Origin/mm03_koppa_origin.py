#!/usr/bin/env python3
"""MM03 — Law-III / micro candidates for koppa_per_baryon without promoting l_P<->G."""
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
R_P = 8.414e-16  # engine proton radius (fm-scale)
G = 6.67430e-11

# Law-III-ish quantities from laws.hpp (approx constants used in engine)
# f_transfer is tiny (~2e-17); use symbolic forms only when numbers available.
R_CHARGE = math.sqrt(R_P * R_E)


def rel(a, b):
    return abs(a - b) / abs(b) if b != 0 else float("inf")


def main() -> int:
    print("MM03 Law-III / micro origin screen for koppa_per_baryon")
    print("pre-reg: MM03_PRE_REGISTRATION.md")

    k0 = (L_P * L_P * C * M_P) / HBAR
    g_form = G * M_P / (C * C)
    print(f"  K0 engine = {k0:.10e} m")
    print(f"  G*m_p/c^2 = {g_form:.10e} m")
    print(f"  K0 vs G-form: {'PASS' if rel(k0, g_form) < 1e-6 else 'FAIL'}")

    # Delete-test: without l_P, can we rebuild K0 from Law-III micros?
    candidates = {
        "K1 hbar/(m_p c)": HBAR / (M_P * C),
        "K2 R_p^3/a0^2": (R_P**3) / (A0**2),
        "K3 R_p^2/a0": (R_P**2) / A0,
        "K4 r_e*(R_p/a0)^2": R_E * (R_P / A0) ** 2,
        "K5 r_e*alpha^4": R_E * (ALPHA**4),
        "K6 r_e*(m_e/m_p)": R_E * (M_E / M_P),
        "K7 lambda_bar_p*alpha^2": (HBAR / (M_P * C)) * (ALPHA**2),
        "K8 R_charge^3/a0^2": (R_CHARGE**3) / (A0**2),
        "K9 r_e*(R_p/r_e)^3": R_E * (R_P / R_E) ** 3,
        "K10 a0*alpha^18": A0 * (ALPHA**18),
        "K11 r_e*(l_P/r_e)^2": R_E * (L_P / R_E) ** 2,  # uses l_P — not independent
    }

    print("--- candidates vs K0 (target) ---")
    matches = []
    for name, val in candidates.items():
        r = rel(val, k0)
        tag = "MATCH" if r < 1e-3 else ("ORDER" if abs(math.log10(max(r, 1e-99))) < 1.5 else "EXCLUDED")
        # K11 uses l_P explicitly — classify SHARED even if match
        if "l_P" in name or name.startswith("K11"):
            tag = "SHARED-INPUT" if r < 1e-3 else tag
        print(f"  {name:28s} = {val:.6e}  rel={r:.3e}  {tag}")
        if tag == "MATCH":
            matches.append(name)

    independent = [m for m in matches if "SHARED" not in m]
    print("--- decision ---")
    print(f"  independent MATCH count = {len(independent)}")
    if independent:
        print("STATUS MM03_INDEPENDENT_ROUTE_SURVIVES")
        return 0

    # Honesty park
    print("  No Law-III/micro route matches K0 without l_P or G-encoding.")
    print("  Engine formula remains: koppa_per_baryon = l_P^2*c*m_p/hbar")
    print("  with disclosed risk_flag: CODATA l_P encodes G.")
    print("STATUS MM03_KOPPA_ORIGIN_PARKED_OPEN")
    return 0  # parked open is a completed adjudication, not instrument fail


if __name__ == "__main__":
    sys.exit(main())
