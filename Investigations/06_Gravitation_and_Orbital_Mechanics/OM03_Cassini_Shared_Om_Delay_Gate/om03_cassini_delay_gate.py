#!/usr/bin/env python3
"""OM03 — Cassini SCE1 shared-om delay gate (inventory + definition + data gates)."""
from __future__ import annotations

import math
import os
import sys
from pathlib import Path

C = 299792458.0
R_SUN = 6.957e8
V_SURF = 436762.0
AU = 1.495978707e11

REPO = Path(__file__).resolve().parents[3]
SCE1 = REPO / "Datasets" / "solar_propagation_2026-08" / "raw" / "cassini_sce1"
EXT_RSR = Path(r"C:\sdt-data\cassini_sce1")


def main() -> int:
    print("OM03 Cassini shared-om delay gate")
    print("pre-reg: OUTSTANDING_CLOSURE_43_PRE_REGISTRATION.md")

    om = (V_SURF * V_SURF * R_SUN) / (C * C)
    b = R_SUN
    # Two-way log marker (order); NOT held-out residual
    dt = (2.0 / C) * 2.0 * om * math.log(4.0 * AU * AU / (b * b))
    print(f"  om_sun = {om:.6f} m")
    print(f"  Shapiro-like order dt = {dt:.6e} s  (COMPUTED; literature ~1e-4 s scale)")

    odf = list(SCE1.rglob("*.odf")) if SCE1.exists() else []
    tdf = list(SCE1.rglob("*.tdf")) if SCE1.exists() else []
    lbl = list(SCE1.rglob("*.lbl")) if SCE1.exists() else []
    rsr_bin = list(SCE1.rglob("*.rsr")) + list(SCE1.rglob("*.1a*")) if SCE1.exists() else []
    print(f"  in-repo ODF={len(odf)} TDF={len(tdf)} LBL={len(lbl)} RSR-like={len(rsr_bin)}")
    print(f"  external RSR root exists: {EXT_RSR.exists()}  path={EXT_RSR}")

    # Definition gate: DAT9 / closed residual still unresolved in prior GOM ladder
    definition_closed = False  # frozen from GOM_DAT9 FBIAS_RECON_UNRESOLVED
    print(f"  closed residual definition (post-DAT9): {definition_closed}")

    data_ok = EXT_RSR.exists() and len(odf) >= 40
    print("---")
    if not definition_closed:
        print("STATUS OM03_DEFINITION_BLOCKED")
        print("  ODF/TDF inventory alone cannot adjudicate EMPIRICALLY SURVIVES.")
        print("  Shared-om CONDITIONAL (OM01) unchanged; Cassini residual PARKED.")
        return 0
    if not data_ok:
        print("STATUS OM03_PARKED_PARTIAL_FETCH")
        return 0
    print("STATUS OM03_READY_FOR_RESIDUAL")  # unreachable until definition+data
    return 0


if __name__ == "__main__":
    sys.exit(main())
