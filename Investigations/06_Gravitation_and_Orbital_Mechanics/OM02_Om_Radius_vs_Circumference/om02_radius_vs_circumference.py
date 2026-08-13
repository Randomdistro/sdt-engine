#!/usr/bin/env python3
"""OM02 — solar Om radius vs C=2π Om circumference against solar anchors."""
from __future__ import annotations

import math
import sys

C_LIGHT = 299792458.0
R_SUN = 6.957e8
AU = 1.495978707e11
A_MERC = 5.7909175e10
E_MERC = 0.205630
T_MERC_YR = 0.2408467

# Representative solar Om freezes used in-repo (metres, radial)
OMS = {
    "laws_k686.3": R_SUN / (686.3**2),
    "OM01": 1476.625,
    "GOM25b": 1476.664437,
    "GOM26": 1476.351201,
    "L_standard": 1476.62504,
}


def arcsec(rad: float) -> float:
    return rad * 206264.80624709636


def main() -> int:
    print("OM02 solar Om radius vs circumference C=2*pi*Om")
    print("Author relation: Om = radial location; C = length to test")
    print("--- freeze ---")
    for name, om in OMS.items():
        circ = 2.0 * math.pi * om
        print(f"  {name:12s}  Om={om:.6f} m   C={circ:.3f} m = {circ/1000:.6f} km")

    om = OMS["OM01"]
    circ = 2.0 * math.pi * om
    print(f"  working Om (OM01) = {om:.6f} m")
    print(f"  working C         = {circ:.6f} m = {circ/1000:.6f} km")
    print(f"  C/Om = 2*pi       = {2*math.pi:.10f}")

    peri = A_MERC * (1.0 - E_MERC * E_MERC)
    century_orbits = 100.0 / T_MERC_YR

    # (observable, L_label, predicted, anchor, unit)
    rows = []
    for lab, L in (("Om", om), ("C", circ)):
        rows.append(("limb deflection 4L/R", lab, arcsec(4 * L / R_SUN), 1.7510, "arcsec"))
        rows.append(("surface redshift L/R", lab, L / R_SUN, 2.12e-6, "1"))
        dphi = 6.0 * math.pi * L / peri
        rows.append(
            (
                "Mercury precession",
                lab,
                arcsec(dphi) * century_orbits,
                42.98,
                "arcsec/cy",
            )
        )
        # GR-equivalent Shapiro marker (4L/c) ln(4 r_e^2 / R^2)
        dt = (4.0 * L / C_LIGHT) * math.log(4.0 * AU * AU / (R_SUN * R_SUN))
        rows.append(("Shapiro superior marker", lab, dt * 1e6, 240.0, "us"))

    print("--- single-pass vs anchors (naive L substitution) ---")
    print(
        f"{'observable':28s} {'L':4s} {'pred':14s} {'anchor':12s} "
        f"{'ratio':10s} {'abs_log10':9s} class"
    )
    n_om_ok = 0
    n_c_ok = 0
    for obs, lab, pred, anc, unit in rows:
        ratio = pred / anc
        lr = abs(math.log10(ratio)) if pred > 0 and anc > 0 else float("nan")
        if lr < 0.05:
            cls = "MATCH"
            if lab == "Om":
                n_om_ok += 1
            else:
                n_c_ok += 1
        elif lr < 1.0:
            cls = "ORDER"
        else:
            cls = "EXCLUDED"
        print(
            f"{obs:28s} {lab:4s} {pred:14.6g} {anc:12.6g} "
            f"{ratio:10.4f} {lr:9.3f} {cls:8s} [{unit}]"
        )

    print("--- formula audit (structure) ---")
    print("  Existing solar matches use L ~ Om ~ 1477 m in:")
    print("    alpha = 4 L / b")
    print("    z     = L / R")
    print("    dphi  = 6 pi L / (a(1-e^2))")
    print("    delay ~ 4 L / c * ln(...)")
    print("  Replacing L by C=2*pi*Om multiplies every linear-in-L prediction by 2*pi.")
    print("  Ontology rewrite that keeps physics: call length C, but formulas use C/(2*pi)=Om.")

    print("--- classification ---")
    print(f"  Om MATCH count = {n_om_ok}")
    print(f"  C  MATCH count = {n_c_ok}")
    if n_om_ok >= 3 and n_c_ok == 0:
        print("STATUS OM_RADIUS_REQUIRED__CIRCUMFERENCE_NAIVE_EXCLUDED")
        return 0
    if n_c_ok >= 3 and n_om_ok == 0:
        print("STATUS CIRCUMFERENCE_LENGTH_PREFERRED")
        return 0
    print("STATUS MIXED_OR_INCONCLUSIVE")
    return 0


if __name__ == "__main__":
    sys.exit(main())
