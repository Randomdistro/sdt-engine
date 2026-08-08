#!/usr/bin/env python3
"""GOM30 — ODF Doppler observable decode (Hz) + cumindex freeze list."""
from __future__ import annotations

import argparse
import csv
import hashlib
import math
import struct
import sys
from collections import Counter
from datetime import datetime, timedelta, timezone
from pathlib import Path

EXPECTED = {
    "odf": "c2ea51d9b5e795bd3eb9b4f1c5174cc44325080623188dce5e01c0ea914bfaf7",
    "label": "b27da74ca62187475860e8214c2b76b8b69af760bbe44d27aac93d1c1a5593bf",
}
REC = 36
EPOCH_1950 = datetime(1950, 1, 1, tzinfo=timezone.utc)


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def bits_from(data: bytes, start_bit_1: int, width: int) -> int:
    value = 0
    for bit_index in range(start_bit_1 - 1, start_bit_1 - 1 + width):
        value = (value << 1) | ((data[bit_index // 8] >> (7 - (bit_index % 8))) & 1)
    return value


def i32(rec: bytes, start: int) -> int:
    return struct.unpack_from(">i", rec, start - 1)[0]


def u32(rec: bytes, start: int) -> int:
    return struct.unpack_from(">I", rec, start - 1)[0]


def parse_row(rec: bytes) -> dict:
    time_int = u32(rec, 1)
    items23 = rec[4:8]
    frac_ms = bits_from(items23, 1, 10)
    obs_int = i32(rec, 9)
    obs_frac = i32(rec, 13)
    bitfield = rec[16:28]
    # Items 18-19 live in the 12-byte bitfield starting at bit 51 and 73
    # (1-based within items 6-19 bit string).
    high_mhz = bits_from(bitfield, 51, 22)
    low_mhz = bits_from(bitfield, 73, 24)
    f_ref = (high_mhz * (1 << 24) + low_mhz) * 1e-3
    return {
        "time": EPOCH_1950 + timedelta(seconds=time_int, milliseconds=frac_ms),
        "obs_hz": obs_int + obs_frac / 1e9,
        "f_ref_hz": f_ref,
        "format_id": bits_from(bitfield, 1, 3),
        "data_type": bits_from(bitfield, 20, 6),
        "validity": bits_from(bitfield, 32, 1),
        "rx": bits_from(bitfield, 4, 7),
    }


def stats(xs: list[float]) -> tuple[float, float, float, float]:
    xs_sorted = sorted(xs)
    n = len(xs)
    mean = sum(xs) / n
    var = sum((x - mean) ** 2 for x in xs) / n
    return xs_sorted[0], xs_sorted[n // 2], xs_sorted[-1], math.sqrt(var)


def validate_synthetic() -> bool:
    obs_int, obs_frac = 12, 345678901
    # Item 18 is 22 bits (max 4194303); Item 19 is 24 bits.
    high, low = 1_000_000, 123456
    bitfield = bytearray(12)
    # format=2
    bitfield[0] = 0b01000000
    # data type 12 at bits 20-25
    for i, bit in enumerate([0, 0, 1, 1, 0, 0]):
        abs_bit = 19 + i
        if bit:
            bitfield[abs_bit // 8] |= 1 << (7 - (abs_bit % 8))
    # pack high into bits 51-72 and low into 73-96
    for i in range(22):
        bit = (high >> (21 - i)) & 1
        abs_bit = 50 + i
        if bit:
            bitfield[abs_bit // 8] |= 1 << (7 - (abs_bit % 8))
    for i in range(24):
        bit = (low >> (23 - i)) & 1
        abs_bit = 72 + i
        if bit:
            bitfield[abs_bit // 8] |= 1 << (7 - (abs_bit % 8))
    rec = (
        struct.pack(">I", 1_000_000)
        + bytes(4)
        + struct.pack(">i", obs_int)
        + struct.pack(">i", obs_frac)
        + bytes(bitfield)
        + bytes(8)
    )
    p = parse_row(rec)
    ok = (
        abs(p["obs_hz"] - (obs_int + obs_frac / 1e9)) < 1e-12
        and abs(p["f_ref_hz"] - (high * (1 << 24) + low) * 1e-3) < 1e-6
    )
    print("VALIDATION A — synthetic obs/ref decode")
    print(f"  obs_hz={p['obs_hz']:.9f} f_ref={p['f_ref_hz']:.6f}  {'PASS' if ok else 'FAIL'}")
    return ok


def cumindex_odf_list(path: Path) -> list[dict]:
    rows = []
    text = path.read_text(encoding="ascii", errors="replace")
    for line in text.splitlines():
        if "/ODF/" not in line.upper() and ".ODF" not in line.upper():
            continue
        # crude CSV: fields in quotes
        parts = next(csv.reader([line]))
        if len(parts) < 6:
            continue
        product = parts[2].strip()
        if not product.upper().endswith(".ODF"):
            continue
        rows.append(
            {
                "path": parts[1].strip(),
                "product": product,
                "start": parts[4].strip(),
                "stop": parts[5].strip(),
            }
        )
    return rows


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--odf",
        type=Path,
        default=Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_odf.odf"),
    )
    parser.add_argument(
        "--label",
        type=Path,
        default=Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_odf.lbl"),
    )
    parser.add_argument(
        "--cumindex",
        type=Path,
        default=Path(
            "Datasets/solar_propagation_2026-08/raw/cassini_sce1_cors0021_cumindex.tab"
        ),
    )
    args = parser.parse_args()

    print("================================================================")
    print("GOM30 — ODF Doppler Observable Decode (Hz)")
    print("Pre-registered 2026-08-08 · no residual / no koppa fit")
    print("================================================================\n")

    if not validate_synthetic():
        return 2
    if sha256(args.odf) != EXPECTED["odf"] or sha256(args.label) != EXPECTED["label"]:
        print("HASH GATE FAIL")
        return 3
    print("HASH GATE PASS\n")

    data = args.odf.read_bytes()
    # Label bounds from GOM29: records 6..7452 -> indices 5..7451
    rows = [parse_row(data[i * REC : (i + 1) * REC]) for i in range(5, 7452)]
    print(f"Rows decoded: {len(rows)}")

    # C1
    finite = all(math.isfinite(r["obs_hz"]) for r in rows)
    types = Counter(r["data_type"] for r in rows)
    print("\nC1 — observable Hz finiteness")
    print(f"  all finite: {'PASS' if finite else 'FAIL'}")
    print(f"  data types: {dict(types)}")

    # C2
    ref_pos = all(r["f_ref_hz"] > 0 for r in rows)
    refs = [r["f_ref_hz"] for r in rows]
    rmin, rmed, rmax, rstdev = stats(refs)
    print("\nC2 — reference frequency")
    print(f"  all f_ref > 0: {'PASS' if ref_pos else 'FAIL'}")
    print(f"  f_ref min/median/max/stdev Hz = {rmin:.3f} / {rmed:.3f} / {rmax:.3f} / {rstdev:.3f}")

    # C3
    obs = [r["obs_hz"] for r in rows]
    omin, omed, omax, ostdev = stats(obs)
    valid = Counter(r["validity"] for r in rows)
    print("\nC3 — observable series (Hz)")
    print(f"  min/median/max/stdev = {omin:.9f} / {omed:.9f} / {omax:.9f} / {ostdev:.9f}")
    print(f"  validity flag counts (0=good,1=bad): {dict(valid)}")
    print(f"  time first/last = {rows[0]['time'].isoformat()} .. {rows[-1]['time'].isoformat()}")
    print("  NOTE: whether field is raw Doppler or nav pseudo-residual = UNADJUDICATED")

    # C4 freeze list
    print("\nC4 — cumindex ODF freeze list (CORS_0021)")
    odfs = cumindex_odf_list(args.cumindex)
    for row in odfs:
        day = "SCE1_???"
        for token in row["path"].replace("\\", "/").split("/"):
            if token.startswith("SCE1_"):
                day = token
        have = "HAVE" if "157_0000K252" in row["product"] else "PENDING_FETCH"
        print(f"  [{have:13s}] {day} {row['product']:34s} {row['start']} -> {row['stop']}")
    print(f"  products listed: {len(odfs)}")

    print("\nC5 — residual")
    print("  STATUS: PENDING_DATA — not computed")

    ok = finite and ref_pos and len(rows) == 7447
    print("\n================================================================")
    print("SUMMARY:", "OBSERVABLE_DECODE_PASS" if ok else "OBSERVABLE_DECODE_FAIL")
    print("================================================================")
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
