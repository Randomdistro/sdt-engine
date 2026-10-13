#!/usr/bin/env python3
"""NU01 — SNO-shaped appearance vs scalar attenuation screen."""
from __future__ import annotations

import math
import sys

# SNO published ratios (OBSERVED comparison columns; not SDT inputs)
# Approximate canonical SNO results: CC/NC ~ 0.34, ES intermediate; NC ~ SSM total
SNO_PHI_NC_OVER_SSM = 1.0  # NC measures total active flux ~ SSM (appearance of non-e)
SNO_PHI_CC_OVER_SSM = 0.34  # electron flavour only
SNO_PHI_ES_OVER_SSM = 0.45  # approx

# PDG mixing (MEASURED-INPUT for oscillation phenomenology)
SIN2_TH12 = 0.307


def main() -> int:
    print("NU01 SNO appearance vs scalar attenuation")
    print("pre-reg: OUTSTANDING_CLOSURE_43_PRE_REGISTRATION.md")

    # Model A: scalar loss / 1/3 survival (CLM-17 style) — EXCLUDED a priori vs SNO
    scalar_survival = 1.0 / 3.0
    print(f"  Model A scalar survival = {scalar_survival:.4f}")
    print(f"  SNO CC/SSM ~ {SNO_PHI_CC_OVER_SSM:.2f}  (electron disappearance OK order)")
    print(f"  SNO NC/SSM ~ {SNO_PHI_NC_OVER_SSM:.2f}  (total active ~ SSM)")
    # Scalar loss predicts NC << SSM if neutrinos destroyed; SNO NC ~ SSM => EXCLUDE
    scalar_predicts_nc = scalar_survival  # if destroyed, NC tracks survivors
    print(f"  Model A predicts NC/SSM ~ {scalar_predicts_nc:.2f} vs OBSERVED ~1 => EXCLUDED")

    # Model B: flavour conversion (appearance): Pee ~ 1 - 0.5*sin^2(2th) averaged ~ 0.55 day
    # Two-flavour solar average survival (rough): 1 - 0.5*sin^2(2theta12)
    s2 = 4.0 * SIN2_TH12 * (1.0 - SIN2_TH12)
    pee_avg = 1.0 - 0.5 * s2
    print(f"  Model B avg Pee (2-flavour vac avg) = {pee_avg:.4f}")
    print(f"  vs SNO CC/SSM ~ {SNO_PHI_CC_OVER_SSM:.2f}  (order only; MSW not SDT-derived)")

    # SDT engine narrative: pitch precession — no native beat equation => UNDERDETERMINED
    has_native_beat = False
    has_native_appearance_channels = False
    print(f"  SDT native beat/cadence equation present: {has_native_beat}")
    print(f"  SDT NC/CC/ES channel map present: {has_native_appearance_channels}")

    print("---")
    print("STATUS NU01_SCALAR_EXCLUDED__MECH_UNDERDETERMINED")
    print("  Scalar attenuation EXCLUDED by SNO NC~SSM (appearance, not destruction).")
    print("  Oscillation phenomenology MATCHES order with MEASURED mixing angles")
    print("  but is not an SDT-derived state machine (PPT11 unpaid phase).")
    print("  Required: native pitch->flavour map with NC/CC/ES signatures.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
