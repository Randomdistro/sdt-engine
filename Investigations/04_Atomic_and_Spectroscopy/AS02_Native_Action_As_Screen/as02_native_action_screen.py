#!/usr/bin/env python3
"""AS02 — native A_s candidate screen (no fitted multipliers; ℏ held out as target)."""
from __future__ import annotations

import math
import sys

# CODATA 2018 / engine whitelist (measured)
C = 299792458.0
HBAR = 1.054571817e-34  # target / H0 only
H = 2.0 * math.pi * HBAR
M_E = 9.1093837015e-31
M_P = 1.67262192369e-27
A0 = 5.29177210903e-11
ALPHA = 7.2973525693e-3
R_E = 2.8179403262e-15
L_P = 1.616255e-35
K_B = 1.380649e-23
T_CMB = 2.72548
R_INF_NIST = 1.0973731568160e7
LAMBDA_C_NIST = 2.42631023867e-12

TOL = 1e-3


def rel(a: float, b: float) -> float:
    return abs(a - b) / abs(b)


def main() -> int:
    print("AS02 native A_s candidate screen")
    print("pre-reg: AS02_PRE_REGISTRATION.md")
    print(f"  target hbar = {HBAR:.10e} J.s")

    candidates = {
        "H0_hbar_control": HBAR,
        "H1_me_c_a0": M_E * C * A0,
        "H2_me_c_re": M_E * C * R_E,
        "H3_me_c_lambdaC_LEAK": M_E * C * LAMBDA_C_NIST,
        "H4_mp_c_lP": M_P * C * L_P,
        "H5_kB_T_a0_over_c": K_B * T_CMB * A0 / C,
        "H6_me_c_a0_alpha": M_E * C * A0 * ALPHA,
        "H7_me_c_a0_alpha2": M_E * C * A0 * (ALPHA**2),
        "H8_me_c_lP": M_E * C * L_P,
        "H9_me_c_a0_over_alpha": M_E * C * A0 / ALPHA,
    }

    print("--- candidates vs hbar ---")
    survivors = []
    for name, val in candidates.items():
        r = rel(val, HBAR)
        tag = "MATCH" if r < TOL else "MISS"
        if name == "H0_hbar_control":
            tag = "CONTROL_PASS" if r < 1e-15 else "CONTROL_FAIL"
        if name == "H3_me_c_lambdaC_LEAK":
            tag = "CIRCULAR_HOLD_OUT_LEAK"
        print(f"  {name:28s}  {val:.6e}  rel={r:.3e}  {tag}")
        if tag == "MATCH" and not name.startswith("H0") and not name.startswith("H3"):
            survivors.append(name)

    # Identity checks
    print("--- identity notes ---")
    re_from_a0 = A0 * (ALPHA**2)
    print(f"  H7 == me*c*(a0*alpha^2): {'YES' if rel(candidates['H7_me_c_a0_alpha2'], M_E * C * re_from_a0) < 1e-12 else 'NO'}")
    print(f"  H2 vs H7 (literal r_e vs a0*alpha^2): rel={rel(candidates['H2_me_c_re'], candidates['H7_me_c_a0_alpha2']):.3e}")
    # Bohr: hbar = alpha * m_e * c * a0 is the QM identity — MATCH is not a new derivation
    h6 = candidates["H6_me_c_a0_alpha"]
    print(f"  H6 vs hbar: rel={rel(h6, HBAR):.3e}  (QM identity hbar=alpha*m_e*c*a0 if MATCH)")
    if rel(h6, HBAR) < TOL:
        print("  CLASSIFY H6: IDENTITY with measured alpha,a0,m_e — SHARED-INPUT, not native A_s derivation")
        # remove from "survivors" as earned derivation
        survivors = [s for s in survivors if s != "H6_me_c_a0_alpha"]

    # Delete-test on engine Rydberg
    print("--- Rydberg delete-test ---")
    r_with_h = M_E * C * (ALPHA**2) / (2.0 * H)
    r_no_h_bohr = ALPHA / (4.0 * math.pi * A0)  # AS01 form — uses a0,α only
    print(f"  R_inf with h:     {r_with_h:.10e}  rel NIST={rel(r_with_h, R_INF_NIST):.3e}")
    print(f"  R_inf Bohr(no h): {r_no_h_bohr:.10e}  rel NIST={rel(r_no_h_bohr, R_INF_NIST):.3e}")
    print("  DELETE h from mass-form Rydberg: formula undefined (needs action or a0)")
    print("  Bohr form survives without h ONLY because a0 is MEASURED-INPUT (holds α definition path)")

    # Compton without hbar
    print("--- Compton delete-test ---")
    lam_from_hbar = 2.0 * math.pi * HBAR / (M_E * C)
    lam_from_a0 = 2.0 * math.pi * A0 * ALPHA
    print(f"  lambda from hbar: {lam_from_hbar:.10e}  rel={rel(lam_from_hbar, LAMBDA_C_NIST):.3e}")
    print(f"  lambda from a0α:  {lam_from_a0:.10e}  rel={rel(lam_from_a0, LAMBDA_C_NIST):.3e}")
    print("  a0α form is IDENTITY with measured a0,α — does not invent A_s")

    # Implied A_s if we force Compton = NIST with only m_e,c
    a_s_implied = LAMBDA_C_NIST * M_E * C / (2.0 * math.pi)
    print(f"  A_s implied by NIST lambda_C: {a_s_implied:.10e}  (=hbar by definition)")
    print(f"  rel to hbar: {rel(a_s_implied, HBAR):.3e}  — TARGET LEAK if used as derivation")

    control_ok = rel(candidates["H0_hbar_control"], HBAR) < 1e-15
    print("---")
    if not control_ok:
        print("STATUS AS02_INSTRUMENT_FAIL")
        return 1

    if survivors:
        print(f"STATUS AS02_NATIVE_AS_SURVIVES survivors={survivors}")
        return 0

    print("STATUS AS02_AS_REMAINS_IMPORTED")
    print("  No non-circular, non-identity candidate recovers hbar to 1e-3.")
    print("  H6 is the Bohr identity ħ=α m_e c a0 (SHARED-INPUT), not a new mechanism.")
    print("  Native A_s ≠ ℏ remains OPEN / UNDERDETERMINED.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
