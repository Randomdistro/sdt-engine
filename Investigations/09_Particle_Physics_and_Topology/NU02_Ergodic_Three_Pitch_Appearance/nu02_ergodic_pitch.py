#!/usr/bin/env python3
"""NU02 — ergodic 3-pitch appearance vs SNO (no PDG mixing in the claim)."""
from __future__ import annotations

import sys

SNO_CC_OVER_SSM = 0.34
SNO_NC_OVER_SSM = 1.0
N_PITCH = 3  # W=0 open winding: three stable pitches (engine narrative)


def main() -> int:
    print("NU02 ergodic 3-pitch appearance map")
    print("pre-reg: OUTSTANDING_CLOSURE_44_PRE_REGISTRATION.md")
    print(f"  N_pitch = {N_PITCH} (topology count, not PDG angles)")

    # Destruction (NU01 Model A): NC tracks survivors
    nc_destroy = 1.0 / N_PITCH
    cc_destroy = 1.0 / N_PITCH
    print("--- Model D destruction (control, already EXCLUDED) ---")
    print(f"  CC/SSM={cc_destroy:.4f}  NC/SSM={nc_destroy:.4f}")

    # Appearance: all pitches remain; CC sees only electron-pitch occupation
    # Ergodic: equal occupation after many precession cycles
    pee = 1.0 / N_PITCH
    nc_app = 1.0
    print("--- Model E ergodic 3-pitch appearance ---")
    print(f"  Pee=CC/SSM={pee:.4f}  NC/SSM={nc_app:.4f}")
    print(f"  hold-out CC={SNO_CC_OVER_SSM:.2f}  NC={SNO_NC_OVER_SSM:.2f}")

    cc_ok = abs(pee - SNO_CC_OVER_SSM) < 0.15
    nc_ok = abs(nc_app - SNO_NC_OVER_SSM) < 0.15
    destroy_nc_fail = abs(nc_destroy - SNO_NC_OVER_SSM) >= 0.15

    print(f"  CC MATCH: {'PASS' if cc_ok else 'FAIL'}")
    print(f"  NC MATCH: {'PASS' if nc_ok else 'FAIL'}")
    print(f"  destruction NC still EXCLUDED: {'PASS' if destroy_nc_fail else 'FAIL'}")

    print("--- limitations ---")
    print("  Equal occupation is an ergodic assumption, not a beat equation.")
    print("  Why three pitches, and why solar birth in e-pitch, remain OPEN.")
    print("  Masses/splittings still MEASURED-INPUT; no native L_osc derivation here.")

    print("---")
    if cc_ok and nc_ok and destroy_nc_fail:
        print("STATUS NU02_APPEARANCE_CONDITIONAL")
        return 0
    print("STATUS NU02_PITCH_MAP_EXCLUDED")
    return 0


if __name__ == "__main__":
    sys.exit(main())
