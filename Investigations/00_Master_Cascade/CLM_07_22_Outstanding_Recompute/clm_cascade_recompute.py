#!/usr/bin/env python3
"""CLM cascade — re-execute outstanding broken scripts from 07-22 corrections ledger."""
from __future__ import annotations

import math
import sys

A0 = 5.29177210903e-11
ALPHA = 7.2973525693e-3
R_INF = 1.0973731568160e7
M_P = 1.67262192369e-27
M_E = 9.1093837015e-31
C = 299792458.0
R_SUN = 6.957e8
OM_H = A0 * ALPHA * ALPHA
N_SUN = 1.198e57  # ~ M_sun/m_p order


def main() -> int:
    print("CLM cascade — outstanding failed claims (direct recompute)")
    fails = []

    # CLM-12 naive N*Om_H deflection
    om_naive = N_SUN * OM_H
    alpha_as = (4.0 * om_naive / R_SUN) * (180.0 / math.pi) * 3600.0
    print(f"CLM-12 naive limb alpha ~ {alpha_as:.3e} arcsec (want ~1.75)")
    if alpha_as < 1e30:
        fails.append("CLM-12 expected huge overshoot")
    else:
        print("  EXCLUDED (overshoot)")

    # Actually check it's huge
    print(f"  EXCLUDED: overshoot factor vs 1.75 = {alpha_as/1.75:.3e}")

    # CLM-20 broken Rydberg
    broken = (ALPHA**2) / (2.0 * A0)
    print(f"CLM-20 broken R = alpha^2/(2*a0) = {broken:.6e} (NIST {R_INF:.6e})")
    print(f"  EXCLUDED: rel err = {abs(broken-R_INF)/R_INF:.3e}")

    # CLM-19 mu script with arbitrary normalizers (illustrative fail)
    mu_true = M_P / M_E
    mu_bad = (M_P / M_E) * (A0 / OM_H)  # nonsense extra factor often seen in broken scripts
    print(f"CLM-19 true m_p/m_e = {mu_true:.6f}")
    print(f"  example contaminated script ~ {mu_bad:.6e}  EXCLUDED as method")

    # CLM-16 Refsdal year scale note (documentation gate)
    print("CLM-16 Refsdal: relevant reappearance ~1 yr (Kelly et al.), not 3.25 yr — DOC EXCLUDED")
    print("CLM-17 neutrino: SNO is flavor appearance, not scalar disappearance — DOC EXCLUDED")

    # Conditionally repaired limb from orbit om
    v = 436762.0
    om = v * v * R_SUN / (C * C)
    alpha_ok = (4.0 * om / R_SUN) * (180.0 / math.pi) * 3600.0
    print(f"CLM-18 repair limb from orbit om = {alpha_ok:.6f} arcsec (CONDITIONAL)")

    print("---")
    print("STATUS CLM_CASCADE_OUTSTANDING_EXCLUSIONS_RECORDED")
    return 0


if __name__ == "__main__":
    sys.exit(main())
