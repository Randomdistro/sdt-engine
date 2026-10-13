#!/usr/bin/env python3
"""NSEQ13b — occupation/emission energy map from Shared seating (hold-out NSEQ09 MeV)."""
from __future__ import annotations

import math
import sys

# Frozen from NSEQ11
SHARED_CONTACTS = 4
PRIV_PER_BRANCH = 2

# OBSERVED hold-out (NSEQ09) — not an input to candidates
SEAL_MEAN_MED_D_MEV = 4.242
OPEN_D_MEAN_MED_D_MEV = 0.895

# Measured / engine scales
ALPHA = 7.2973525693e-3
M_E = 9.1093837015e-31
C = 299792458.0
HBAR = 1.054571817e-34
M_P = 1.67262192369e-27
E_CHARGE = 1.602176634e-19
MEV = 1e6 * E_CHARGE

# Binding scales (MEASURED-ish nuclear)
B_DEUTERON_MEV = 2.224
B_ALPHA_MEV = 28.3
B_TRITON_MEV = 8.482


def rel(a, b):
    return abs(a - b) / abs(b) if b else float("inf")


def main() -> int:
    print("NSEQ13b occupation/emission energy screen")
    print("pre-reg: OUTSTANDING_CLOSURE_43_PRE_REGISTRATION.md")
    print(f"  Shared contacts = {SHARED_CONTACTS}  private/branch = {PRIV_PER_BRANCH}")
    print(f"  HOLD-OUT SEAL mean medD = {SEAL_MEAN_MED_D_MEV:.3f} MeV")

    # Candidates from seating integers and dependency-traced bridges only;
    # no measured nuclear B_* imports.
    e_ryd_mev = (0.5 * M_E * C * C * (ALPHA**2)) / MEV  # ~13.6 eV in MeV
    candidates = {
        "E1 Shared * m_e c^2": SHARED_CONTACTS * (M_E * C * C) / MEV,
        "E2 Shared * Rydberg": SHARED_CONTACTS * e_ryd_mev,
        "E3 priv * Rydberg": PRIV_PER_BRANCH * e_ryd_mev,
        "E4 alpha^2 * m_p c^2": (ALPHA**2) * (M_P * C * C) / MEV,
        "E5 Shared * alpha^2 * m_p c^2": SHARED_CONTACTS * (ALPHA**2) * (M_P * C * C) / MEV,
        "E6 (Shared+priv) * Rydberg": (SHARED_CONTACTS + PRIV_PER_BRANCH) * e_ryd_mev,
        "E7 LEAK B_d*Shared/2": B_DEUTERON_MEV * SHARED_CONTACTS / 2.0,
        "E8 LEAK B_t/2": B_TRITON_MEV / 2.0,
        "E9 LEAK SEAL medD": SEAL_MEAN_MED_D_MEV,
    }

    print("--- candidates vs SEAL medD (derivation screen) ---")
    matches = []
    for name, val in candidates.items():
        r = rel(val, SEAL_MEAN_MED_D_MEV)
        tag = "MATCH" if r < 0.15 else "MISS"
        if name.startswith("E7") or name.startswith("E8") or name.startswith("E9"):
            tag = "SHARED_INPUT_LEAK" if r < 0.15 else "LEAK_MISS"
        print(f"  {name:36s} = {val:.6e} MeV  rel={r:.3e}  {tag}")
        if tag == "MATCH":
            matches.append(name)

    # Delete-test: energy must come from seating rule, not from borrowing gap or B_*
    print("---")
    print("  Delete Shared count: no remaining SDT energy quantum defined.")
    print("  Borrowed B_d/B_t/B_alpha matches are SHARED-INPUT, not derivation.")
    print("  NSEQ09 locations DERIVED; heights OBSERVED — energy map still missing.")

    if matches:
        print(f"STATUS NSEQ13_ENERGY_MAP_SURVIVES matches={matches}")
        return 0

    print("STATUS NSEQ13_UNDERDETERMINED")
    print("  Seating geometry (Shared/matching) does not yet fix MeV heights.")
    print("  E7/E8 show binding imports can numerically hit the hold-out — not allowed.")
    print("  Next: axiom for contact energy quantum, then held-out isotope gaps.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
