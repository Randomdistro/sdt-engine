#!/usr/bin/env python3
"""CK02 — bulk n from packing identities (lab n not in formulas)."""
from __future__ import annotations

import math
import sys

N_WATER = 1.3330  # OBSERVED hold-out
ETA = math.pi / math.sqrt(18.0)  # close-pack fraction (laws.hpp nuclear_boundary_radius)


def classify(n: float) -> str:
    lr = abs(math.log10(n / N_WATER))
    if lr < 0.05:
        return "MATCH"
    if lr < 1.0:
        return "ORDER"
    return "EXCLUDED"


def main() -> int:
    print("CK02 packing-identity bulk n screen")
    print("pre-reg: OUTSTANDING_CLOSURE_44_PRE_REGISTRATION.md")
    print(f"  eta = pi/sqrt(18) = {ETA:.8f}")
    print(f"  hold-out n_water = {N_WATER}")

    cands = [
        ("C1 1/eta", 1.0 / ETA, "FCC filling inverse"),
        ("C2 eta**(-1/3)", ETA ** (-1.0 / 3.0), "linear-size packing"),
        ("C3 4/3", 4.0 / 3.0, "tetrahedral/alpha count — coincidence risk"),
        ("C4 1/(1-eta)", 1.0 / (1.0 - ETA), "void fraction inverse"),
        ("C5 F(3)/F(2)=20/12", 20.0 / 12.0, "tier capacity ratio"),
        ("C6 1+eta", 1.0 + ETA, "naive fill add"),
        ("C7 1/(1-z_sun)^2", 1.0 / (1.0 - 2.1225e-6) ** 2, "grav depth — wrong domain"),
    ]

    n_match = 0
    c3_match = False
    other_match = False
    for name, val, why in cands:
        cls = classify(val)
        lr = math.log10(val / N_WATER)
        print(f"  {name:24s} = {val:.6f}  log10={lr:+.4f}  {cls:8s}  ({why})")
        if cls == "MATCH":
            n_match += 1
            if name.startswith("C3"):
                c3_match = True
            elif not name.startswith("C7"):
                other_match = True

    print("---")
    print("  Gravitational z cannot supply bulk n~1.33 (CK01).")
    print("  C3=4/3 matches water by the well-known 4/3~1.333 identity;")
    print("  that is not a relay constitutive law unless tetrahedral 4 is derived.")
    if other_match:
        print("STATUS CK02_PACKING_NUMERIC_MATCH__CONSTITUTIVE_OPEN")
        print("  C1 1/eta is inside MATCH dex; n=1/eta is not a derived relay law.")
        return 0
    if c3_match and n_match == 1:
        print("STATUS CK02_CONSTITUTIVE_STILL_OPEN")
        print("  Only 4/3 MATCH — coincidence, not occlusion n(omega).")
        return 0
    print("STATUS CK02_CONSTITUTIVE_STILL_OPEN")
    return 0


if __name__ == "__main__":
    sys.exit(main())
