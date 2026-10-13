#!/usr/bin/env python3
"""AS01 — Rydberg/Compton spine with Om naming collision resolved."""
from __future__ import annotations

import math
import sys

A0 = 5.29177210903e-11
ALPHA = 7.2973525693e-3
R_INF_NIST = 1.0973731568160e7
LAMBDA_C_NIST = 2.42631023867e-12
HBAR = 1.054571817e-34
M_E = 9.1093837015e-31
C = 299792458.0


def rel(a, b):
    return abs(a - b) / abs(b)


def main() -> int:
    print("AS01 Rydberg/Compton conditional spine (naming-collision corrected)")
    print("pre-reg: AS01_PRE_REGISTRATION.md")

    # Length Om (EM c-boundary) — MUST NOT be plugged into Rydberg spine
    om_len = A0 * (ALPHA**2)
    print(f"  Om_length = a0*alpha^2 = r_e = {om_len:.10e} m")

    # Spectroscopic Om in the corrected-proofs product identity is dimensionless 1/alpha
    om_dimless = 1.0 / ALPHA
    print(f"  Om_spec (dimensionless) = 1/alpha = {om_dimless:.10e}")
    print("  RELATIONSHIP: these are NOT the same object (naming collision)")

    # Surviving Bohr/Rydberg forms
    r_inf = ALPHA / (4.0 * math.pi * A0)
    lam_c = 2.0 * math.pi * A0 * ALPHA
    prod = r_inf * lam_c
    prod_target = (ALPHA**2) / 2.0

    print(f"  R_inf = alpha/(4*pi*a0) = {r_inf:.10e}")
    print(f"  NIST R_inf              = {R_INF_NIST:.10e}")
    print(f"  rel(R): {rel(r_inf, R_INF_NIST):.3e}  {'PASS' if rel(r_inf, R_INF_NIST) < 1e-9 else 'FAIL'}")

    print(f"  lambda_C = 2*pi*a0*alpha = {lam_c:.10e}")
    print(f"  NIST lambda_C            = {LAMBDA_C_NIST:.10e}")
    print(f"  rel(L): {rel(lam_c, LAMBDA_C_NIST):.3e}  {'PASS' if rel(lam_c, LAMBDA_C_NIST) < 1e-9 else 'FAIL'}")

    print(f"  product = {prod:.10e}  target alpha^2/2 = {prod_target:.10e}")
    print(f"  product identity: {'PASS' if rel(prod, prod_target) < 1e-12 else 'FAIL'}")

    # Equivalent writing with Om_spec=1/alpha
    r_via = 1.0 / (4.0 * math.pi * A0 * om_dimless)
    lam_via = 2.0 * math.pi * A0 / om_dimless
    print(f"  via Om_spec: R={r_via:.10e} L={lam_via:.10e} (IDENTITY with alpha forms)")
    print(f"  via Om_spec match: {'PASS' if rel(r_via, r_inf) < 1e-12 and rel(lam_via, lam_c) < 1e-12 else 'FAIL'}")

    # EXCLUDE plugging length Om into spine
    r_wrong = 1.0 / (4.0 * math.pi * A0 * om_len)
    lam_wrong = 2.0 * math.pi * A0 / om_len
    print(f"  WRONG length-Om spine: R={r_wrong:.6e} L={lam_wrong:.6e}")
    print(f"  length-Om spine: EXCLUDED (rel R to NIST = {rel(r_wrong, R_INF_NIST):.3e})")

    broken = (ALPHA**2) / (2.0 * A0)
    print(f"  BROKEN alpha^2/(2*a0) = {broken:.6e}  EXCLUDED (rel={rel(broken, R_INF_NIST):.3e})")

    # Action debt
    lam_hbar = 2.0 * math.pi * HBAR / (M_E * C)
    print("--- action ---")
    print(f"  lambda from hbar: {lam_hbar:.10e}  match NIST: {'PASS' if rel(lam_hbar, LAMBDA_C_NIST) < 1e-9 else 'FAIL'}")
    print("  A_s = hbar remains IMPORTED for mass link; Om_spec=1/alpha is not a new mechanism")

    ok = (
        rel(r_inf, R_INF_NIST) < 1e-9
        and rel(lam_c, LAMBDA_C_NIST) < 1e-9
        and rel(prod, prod_target) < 1e-12
        and rel(r_wrong, R_INF_NIST) > 0.1
        and rel(broken, R_INF_NIST) > 0.1
    )
    print("---")
    if ok:
        print("STATUS AS01_SPINE_SURVIVES__LENGTH_OM_EXCLUDED__AS_OPEN")
        return 0
    print("STATUS AS01_FAIL")
    return 1


if __name__ == "__main__":
    sys.exit(main())
