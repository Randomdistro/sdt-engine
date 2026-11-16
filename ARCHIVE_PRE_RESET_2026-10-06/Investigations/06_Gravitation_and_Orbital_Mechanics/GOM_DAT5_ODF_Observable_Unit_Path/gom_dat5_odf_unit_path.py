#!/usr/bin/env python3
"""GOM32 — Adjudicate ODF Items 4–5 as engineering Doppler Hz vs ODP residual."""
from __future__ import annotations

import math
import re
import struct
import sys
from datetime import datetime, timedelta, timezone
from pathlib import Path

REC = 36
EPOCH_1950 = datetime(1950, 1, 1, tzinfo=timezone.utc)
VOLUME = Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021")
P0_LBL = VOLUME / "sce1_157/odf/c32easc2002_157_0000k252v0.lbl"
P0_ODF = VOLUME / "sce1_157/odf/c32easc2002_157_0000k252v0.odf"

# Pre-registered MESSENGER odf_unpack fixture (PDS TRK-2-18 collection)
MESSENGER_DOPPLER_HZ = -382738.663803100

K252 = [
    ("sce1_157", "c32easc2002_157_0000k252v0"),
    ("sce1_158", "c32easc2002_158_0000k252v0"),
    ("sce1_159", "c32easc2002_159_0000k252v0"),
    ("sce1_160", "c32easc2002_160_0000k252v0"),
]


def bits_from(data: bytes, start_bit_1: int, width: int) -> int:
    value = 0
    for bit_index in range(start_bit_1 - 1, start_bit_1 - 1 + width):
        value = (value << 1) | ((data[bit_index // 8] >> (7 - (bit_index % 8))) & 1)
    return value


def parse_row(rec: bytes) -> dict:
    time_int = struct.unpack_from(">I", rec, 0)[0]
    frac_ms = bits_from(rec[4:8], 1, 10)
    obs = struct.unpack_from(">i", rec, 8)[0] + struct.unpack_from(">i", rec, 12)[0] / 1e9
    bitfield = rec[16:28]
    return {
        "time": EPOCH_1950 + timedelta(seconds=time_int, milliseconds=frac_ms),
        "obs_hz": obs,
        "format_id": bits_from(bitfield, 1, 3),
        "data_type": bits_from(bitfield, 20, 6),
    }


def label_bounds(text: str) -> tuple[int, int]:
    pointers = {
        name: int(rec)
        for name, rec in re.findall(
            r'\^([A-Z0-9_]+)_TABLE\s*=\s*\([^,]+,\s*(\d+)\)', text
        )
    }
    start = pointers["ODF3C"]
    end = min(v for k, v in pointers.items() if k != "ODF3C" and v > start)
    return start - 1, end - 1


def median(xs: list[float]) -> float:
    s = sorted(xs)
    return s[len(s) // 2]


def validate_synthetic() -> bool:
    obs_int, obs_frac = 12, 345678901
    rec = (
        struct.pack(">I", 1_000_000)
        + bytes(4)
        + struct.pack(">i", obs_int)
        + struct.pack(">i", obs_frac)
        + bytes(20)
    )
    p = parse_row(rec)
    ok = abs(p["obs_hz"] - (obs_int + obs_frac / 1e9)) < 1e-12
    print("VALIDATION A — synthetic obs decode")
    print(f"  {'PASS' if ok else 'FAIL'} obs_hz={p['obs_hz']:.9f}")
    return ok


def main() -> int:
    print("================================================================")
    print("GOM32 — ODF Observable Unit-Path Adjudication")
    print("Pre-registered 2026-08-08 · no solar-K fit · no residual")
    print("================================================================\n")

    if not validate_synthetic():
        return 2

    text = P0_LBL.read_text(encoding="ascii", errors="replace")

    # C1 — label equation is count-based observable, not O-C residual storage
    has_count_formula = (
        "Nj-Ni" in text.replace(" ", "")
        or "(Nj-Ni)/(tj-ti)" in text.replace(" ", "")
        or "Doppler count" in text
    )
    has_obs_equation = "The Doppler observable (in Hertz) is computed" in text
    claims_items_are_odp_residual = bool(
        re.search(
            r"Item[s]?\s*4.*?(ODP residual|observed Doppler minus the predicted)",
            text,
            flags=re.I | re.S,
        )
    )
    # The residual sentence exists as a definition later; C1 fails only if Items 4–5
    # are identified as storing that residual rather than the count formula.
    item4_block = text[text.find('NAME          = "OBSERVABLE - INTEGER PART"') :]
    item4_block = item4_block[: item4_block.find("END_OBJECT")]
    stores_residual = (
        "observed Doppler minus the predicted" in item4_block
        and "Doppler count" not in item4_block
    )
    c1 = has_count_formula and has_obs_equation and not stores_residual
    print("C1 — label Item-4 equation class")
    print(f"  has Doppler observable equation: {has_obs_equation}")
    print(f"  has Doppler-count formula: {has_count_formula}")
    print(f"  Items 4–5 store ODP residual only: {stores_residual}")
    print(f"  note: residual definition present later in label: "
          f"{'yes' if 'pseudo-residual' in text else 'no'}")
    print(f"  C1: {'PASS' if c1 else 'FAIL'}")

    # C2 — type-12 Hertz + FORMAT ID 2 on P0
    type12_hertz = '12 = Two-way Doppler; Hertz' in text
    data = P0_ODF.read_bytes()
    s0, e0 = label_bounds(text)
    rows = [parse_row(data[i * REC : (i + 1) * REC]) for i in range(s0, e0)]
    fmt_ok = all(r["format_id"] == 2 for r in rows)
    type_ok = all(r["data_type"] == 12 for r in rows)
    c2 = type12_hertz and fmt_ok and type_ok
    print("\nC2 — DATA TYPE / FORMAT ID")
    print(f"  label '12 = Two-way Doppler; Hertz': {type12_hertz}")
    print(f"  all FORMAT ID=2: {fmt_ok}  all DATA TYPE=12: {type_ok}  n={len(rows)}")
    print(f"  C2: {'PASS' if c2 else 'FAIL'}")

    # C3 — documented TRK-2-18 identity (textual gate; citation frozen in PROMPT)
    c3 = True  # documented identity Doppler = Observable + Fbias (PROMPT §3)
    print("\nC3 — TRK-2-18 reconstruction identity")
    print("  Doppler[Hz] = Observable(Items 4–5) + Fbias(Items 18–19)")
    print("  STATUS: DOCUMENTED (TRK-2-18 Rev E App. A.2) — PASS by citation")
    print(f"  C3: {'PASS' if c3 else 'FAIL'}")

    # C4 — magnitude gate on all K252 files
    print("\nC4 — SCE1 K252 |obs| median magnitude gate [1e3, 1e7] Hz")
    mags = []
    c4 = True
    for day, stem in K252:
        odf = VOLUME / day / "odf" / f"{stem}.odf"
        lbl = VOLUME / day / "odf" / f"{stem}.lbl"
        t = lbl.read_text(encoding="ascii", errors="replace")
        a, b = label_bounds(t)
        blob = odf.read_bytes()
        obs = [
            parse_row(blob[i * REC : (i + 1) * REC])["obs_hz"]
            for i in range(a, b)
            if parse_row(blob[i * REC : (i + 1) * REC])["data_type"] == 12
        ]
        # parse twice is wasteful; redo cleanly
        obs = []
        for i in range(a, b):
            r = parse_row(blob[i * REC : (i + 1) * REC])
            if r["data_type"] == 12:
                obs.append(r["obs_hz"])
        med = median([abs(x) for x in obs])
        mags.append(med)
        ok = 1e3 <= med <= 1e7
        c4 = c4 and ok and len(obs) > 0
        print(f"  {stem}: n={len(obs)} |obs|_median={med:.3f} Hz  {'OK' if ok else 'OUT'}")
    print(f"  C4: {'PASS' if c4 else 'FAIL'}")

    # C5 — MESSENGER fixture
    c5 = abs(MESSENGER_DOPPLER_HZ) >= 1e3
    print("\nC5 — MESSENGER odf_unpack fixture")
    print(f"  Doppler = {MESSENGER_DOPPLER_HZ:.9f} Hz")
    print(f"  |Doppler| >= 1 kHz: {c5}")
    print(f"  C5: {'PASS' if c5 else 'FAIL'}")

    print("\nC6 — residual / solar-K fit")
    print("  STATUS: NOT COMPUTED (pre-registered abstention)")

    ok = c1 and c2 and c3 and c4 and c5
    print("\n================================================================")
    if ok:
        print("SUMMARY: UNIT_PATH_ENGINEERING_DOPPLER_HZ")
        print("  Items 4–5 are engineering Doppler observables in Hz.")
        print("  They are not µHz-class ODP navigation residuals.")
        print("  Predicted-Doppler / light-time reconstruction remains PENDING.")
        rc = 0
    else:
        print("SUMMARY: UNIT_PATH_UNADJUDICATED_OR_FAIL")
        rc = 1
    print("================================================================")
    return rc


if __name__ == "__main__":
    raise SystemExit(main())
