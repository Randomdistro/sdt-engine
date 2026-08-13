#!/usr/bin/env python3
"""NSEQ14 — Law-III F*r contact energy vs NSEQ09 SEAL hold-out (no B_d leak)."""
from __future__ import annotations

import math
import sys

SEAL = 4.242  # MeV hold-out
SHARED = 4
K_E = 8.9875517923e9
E = 1.602176634e-19
R_P = 0.8414e-15
R_E_CL = 2.8179403262e-15
MEV_J = 1.602176634e-13
PI = math.pi
# P_eff from laws.hpp: 4 k_e e^2 / (pi R_p^2 r_e^2)
P_EFF = 4.0 * K_E * (E**2) / (PI * R_P * R_P * R_E_CL * R_E_CL)


def F_occ(R1: float, R2: float, r: float) -> float:
    return (PI / 4.0) * P_EFF * (R1**2) * (R2**2) / (r * r)


def E_mev(F: float, r: float) -> float:
    return F * r / MEV_J


def rel(a: float, b: float) -> float:
    return abs(a - b) / abs(b)


def main() -> int:
    print("NSEQ14 Law-III contact energy screen")
    print("pre-reg: OUTSTANDING_CLOSURE_44_PRE_REGISTRATION.md")
    print(f"  hold-out SEAL medD = {SEAL} MeV")
    print(f"  Shared = {SHARED} (geometry count only)")

    cands = {
        "F(Rp,Rp)*2Rp": E_mev(F_occ(R_P, R_P, 2 * R_P), 2 * R_P),
        "F(Rp,Rp)*Rp": E_mev(F_occ(R_P, R_P, R_P), R_P),
        "F(Rp,re)*re": E_mev(F_occ(R_P, R_E_CL, R_E_CL), R_E_CL),
        "Shared*F(Rp,Rp)*2Rp": SHARED * E_mev(F_occ(R_P, R_P, 2 * R_P), 2 * R_P),
        "F(Rp,Rp)*2re": E_mev(F_occ(R_P, R_P, 2 * R_E_CL), 2 * R_E_CL),
        "k_e e^2 / Rp  [Coulomb MeV]": (K_E * E * E / R_P) / MEV_J,
    }

    matches = []
    print("--- candidates ---")
    for name, val in cands.items():
        r = rel(val, SEAL)
        tag = "MATCH" if r < 0.15 else ("ORDER" if r < 10 else "EXCLUDED")
        print(f"  {name:32s} = {val:.6e} MeV  rel={r:.3e}  {tag}")
        if tag == "MATCH":
            matches.append(name)

    print("---")
    print("  P_eff is class-E (calibrated Coulomb identity) — magnitude not a new nuclear axiom.")
    print("  No B_d/B_t imported.")
    if matches:
        print(f"STATUS NSEQ14_CONTACT_ENERGY_SURVIVES matches={matches}")
        return 0
    print("STATUS NSEQ14_UNDERDETERMINED")
    return 0


if __name__ == "__main__":
    sys.exit(main())
