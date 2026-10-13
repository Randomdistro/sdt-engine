#!/usr/bin/env python3
"""OM01 — one solar om drives deflection + redshift (+ delay marker)."""
from __future__ import annotations

import math
import sys

C = 299792458.0
R_SUN = 6.957e8
V_SURF = 436762.0
AU = 1.495978707e11
R_EARTH_ORBIT = AU


def main() -> int:
    print("OM01 shared solar om profile")
    print("pre-reg: OM01_PRE_REGISTRATION.md")

    om = (V_SURF * V_SURF * R_SUN) / (C * C)
    k = C / V_SURF
    om_from_k = R_SUN / (k * k)
    print(f"  om = v^2 R / c^2 = {om:.6f} m")
    print(f"  om = R / k^2     = {om_from_k:.6f} m")
    print(f"  construction match: {'PASS' if abs(om - om_from_k) / om < 1e-12 else 'FAIL'}")

    alpha_rad = 4.0 * om / R_SUN
    alpha_as = alpha_rad * (180.0 / math.pi) * 3600.0
    z = om / R_SUN
    # Order-of-magnitude two-way logarithmic marker (b = R_sun limb)
    b = R_SUN
    dt = (2.0 / C) * 2.0 * om * math.log(4.0 * R_EARTH_ORBIT * R_EARTH_ORBIT / (b * b))

    print(f"  limb deflection alpha = {alpha_as:.6f} arcsec  (target ~1.75)")
    print(f"  surface redshift z    = {z:.6e}")
    print(f"  Shapiro-like marker dt~ {dt:.6e} s  (COMPUTED order; not held-out data)")

    # Same-om consistency: changing om would move both proportionally
    ok = abs(om - om_from_k) / om < 1e-12 and 1.74 < alpha_as < 1.76 and z > 0
    print("---")
    print("CLASSIFICATION: CONDITIONAL / KNOWN-MATCH construction (not EMPIRICALLY SURVIVES)")
    print("  shared om used once for alpha and z: PASS" if ok else "  FAIL")
    if ok:
        print("STATUS OM01_SHARED_OM_CONDITIONAL_SURVIVES")
        return 0
    print("STATUS OM01_FAIL")
    return 1


if __name__ == "__main__":
    sys.exit(main())
