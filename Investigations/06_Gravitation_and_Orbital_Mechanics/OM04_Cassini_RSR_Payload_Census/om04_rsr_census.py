#!/usr/bin/env python3
"""OM04 — Cassini RSR payload census; residual definition still DAT9-blocked."""
from __future__ import annotations

import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[3]
SCE1 = REPO / "Datasets" / "solar_propagation_2026-08" / "raw" / "cassini_sce1"
EXT = Path(r"C:\sdt-data\cassini_sce1")


def main() -> int:
    print("OM04 Cassini RSR payload vs label census")
    print("pre-reg: OUTSTANDING_CLOSURE_44_PRE_REGISTRATION.md")

    if not SCE1.exists():
        print("STATUS OM04_DEFINITION_STILL_BLOCKED")
        print("  SCE1 tree missing")
        return 1

    lbl = list(SCE1.rglob("*.lbl"))
    rsr_lbl = [p for p in lbl if "rsr" in str(p).lower()]
    payloads = []
    for p in rsr_lbl:
        # labels point at PRODUCT_ID .1A1 beside the label
        stem = p.with_suffix("")
        for ext in (".1A1", ".1a1", ".rsr", ".RSR"):
            q = p.parent / (p.stem + ext)
            if q.exists():
                payloads.append(q)
        # also PRODUCT without .lbl
        q2 = p.parent / (p.stem + ".1A1")
        if q2.exists() and q2 not in payloads:
            payloads.append(q2)

    odf = list(SCE1.rglob("*.odf"))
    print(f"  labels total={len(lbl)}  rsr-folder labels={len(rsr_lbl)}")
    print(f"  RSR payloads (.1A1/.rsr) found={len(payloads)}")
    print(f"  ODF={len(odf)}")
    print(f"  external {EXT} exists={EXT.exists()}")
    print("  DAT9 Fbias reconstruction: still UNRESOLVED (not re-scanned)")
    print("  residual definition closed: False")

    print("---")
    if payloads:
        print("STATUS OM04_RSR_PAYLOAD_PRESENT__DEFINITION_STILL_BLOCKED")
        print("  Payload on disk does not close DAT9; no EMPIRICALLY SURVIVES.")
        return 0
    print("STATUS OM04_RSR_PAYLOAD_ABSENT")
    print("  Labels present; binary RSR (.1A1) not fetched (historical disk-full).")
    print("  ODF/TDF inventory still insufficient for shared-om residual.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
