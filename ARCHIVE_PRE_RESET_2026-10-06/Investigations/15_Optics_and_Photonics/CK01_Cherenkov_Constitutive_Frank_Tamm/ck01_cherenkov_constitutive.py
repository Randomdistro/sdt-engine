#!/usr/bin/env python3
"""CK01 — Cherenkov constitutive n(omega) + Frank-Tamm screen."""
from __future__ import annotations

import math
import sys

C = 299792458.0
ALPHA = 7.2973525693e-3
HBAR = 1.054571817e-34
E = 1.602176634e-19
# Vacuum permittivity (imported EM; not SDT-derived)
EPS0 = 8.8541878128e-12

N_WATER_OBS = 1.3330  # OBSERVED only
THETA_WATER_OBS_DEG = 41.4


def rel(a, b):
    return abs(a - b) / abs(b) if b else float("inf")


def main() -> int:
    print("CK01 Cherenkov constitutive + Frank-Tamm screen")
    print("pre-reg: OUTSTANDING_CLOSURE_43_PRE_REGISTRATION.md")

    # Angle from OBSERVED n (B32 path) — COMPUTED, not constitutive survival
    theta = math.acos(1.0 / N_WATER_OBS) * 180.0 / math.pi
    print(f"  acos(1/n_obs) = {theta:.4f} deg  vs ~{THETA_WATER_OBS_DEG}  rel={rel(theta, THETA_WATER_OBS_DEG):.3e}")
    print("  CLASS: COMPUTED from OBSERVED n (B32) — not constitutive derivation")

    # OP01: n = 1/(1-z). Invert OBSERVED n => z — then check if z is independently derived
    z_from_n = 1.0 - 1.0 / N_WATER_OBS
    print(f"  z implied by n_water = {z_from_n:.6f}")
    print("  Without independent water z from occlusion packing, this is CIRCULAR.")

    # Candidate constitutive without lab n: solar-surface z = om/R ~ 2e-6 -> n~1+2e-6 (not water)
    R_SUN = 6.957e8
    V = 436762.0
    om = V * V * R_SUN / (C * C)
    z_sun = om / R_SUN
    n_sun = 1.0 / (1.0 - z_sun)
    print(f"  solar surface z={z_sun:.6e} n={n_sun:.9f}  (not bulk water)")

    # Frank-Tamm spectral factor (classical): (e^2/c^2) * (1 - 1/(n^2 beta^2)) * omega
    # Use ultra-rel beta->1, n=n_water: dimensionless (1-1/n^2)
    ft_fac = 1.0 - 1.0 / (N_WATER_OBS**2)
    print(f"  Frank-Tamm factor (1-1/n^2) with n_obs = {ft_fac:.6f}")
    # Energy scale needs A_s or hbar — AS02 parked import
    print("  Frank-Tamm absolute yield requires action (hbar) — AS02 A_s REMAINS_IMPORTED")
    print("  No SDT-native n(omega) dispersion law present in candidates.")

    constitutive_derived = False
    print("---")
    if constitutive_derived:
        print("STATUS CK01_CONSTITUTIVE_SURVIVES")
        return 0
    print("STATUS CK01_ANGLE_COMPUTED__CONSTITUTIVE_OPEN")
    print("  Threshold angle from observed n: COMPUTED.")
    print("  Matter bulk n(omega) from relay/occlusion: OPEN (OP01 dispersion PENDING).")
    print("  Frank-Tamm normalisation: OPEN pending constitutive n + native A_s.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
