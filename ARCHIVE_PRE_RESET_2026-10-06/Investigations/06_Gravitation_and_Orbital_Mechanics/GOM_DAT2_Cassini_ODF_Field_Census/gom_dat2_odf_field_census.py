#!/usr/bin/env python3
"""GOM29 — ODF orbit-data field census (metadata only). Pre-registered in PROMPT.md."""
from __future__ import annotations

import argparse
import hashlib
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
DATA_TYPE_NAMES = {
    11: "1-way Doppler",
    12: "2-way Doppler",
    13: "3-way Doppler",
    36: "PRA range",
    37: "SRA range",
}


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
    bitfield = rec[16:28]  # items 6-19, 12 bytes
    return {
        "time": EPOCH_1950 + timedelta(seconds=time_int, milliseconds=frac_ms),
        "format_id": bits_from(bitfield, 1, 3),
        "rx": bits_from(bitfield, 4, 7),
        "tx": bits_from(bitfield, 11, 7),
        "data_type": bits_from(bitfield, 20, 6),
        "validity": bits_from(bitfield, 32, 1),
    }


def validate_synthetic() -> bool:
    # Build a minimal synthetic orbit-data row.
    time_int = int((datetime(2002, 6, 6, 20, 41, 30, tzinfo=timezone.utc) - EPOCH_1950).total_seconds())
    items23 = bytearray(4)
    # frac_ms = 0 in first 10 bits; leave rest 0
    bitfield = bytearray(12)
    # format=2 in bits 1-3 → top bits of first byte: 010..... = 0x40
    bitfield[0] = 0b01000000
    # data type 12 at bits 20-25 of bitfield: bit 20 is bit index 19 of the 96-bit field
    # Place carefully via bits_from inverse: set bits 20..25 = 001100 (12)
    for i, bit in enumerate([0, 0, 1, 1, 0, 0]):
        abs_bit = 19 + i  # 0-based within bitfield
        if bit:
            bitfield[abs_bit // 8] |= 1 << (7 - (abs_bit % 8))
    # 4+4+4+4+12+8 = 36 (time, items2-3, obs int, obs frac, items6-19, remainder)
    rec = (
        struct.pack(">I", time_int)
        + bytes(items23)
        + bytes(4)
        + bytes(4)
        + bytes(bitfield)
        + bytes(8)
    )
    assert len(rec) == REC
    parsed = parse_row(rec)
    ok = parsed["format_id"] == 2 and parsed["data_type"] == 12
    print("VALIDATION A — synthetic orbit-data row")
    print(f"  format_id={parsed['format_id']} data_type={parsed['data_type']}  {'PASS' if ok else 'FAIL'}")
    return ok


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
    args = parser.parse_args()

    print("================================================================")
    print("GOM29 — Cassini SCE1 ODF Orbit-Data Field Census")
    print("Pre-registered 2026-08-08 · metadata only · no residual")
    print("================================================================\n")

    if not validate_synthetic():
        return 2

    if sha256(args.odf) != EXPECTED["odf"] or sha256(args.label) != EXPECTED["label"]:
        print("HASH GATE FAIL")
        return 3
    print("HASH GATE PASS\n")

    data = args.odf.read_bytes()
    # Label pointers (1-based): ODF3A=5 header, ODF3C=6 first data, ODF4A25=7453 next header.
    # Orbit-data rows = records 6..7452 inclusive = 7447 rows (label ROWS=7447).
    header_idx = 4
    first_data = 5
    next_header = 7452  # 0-based index of ODF4A25
    expected_rows = 7447

    print("VALIDATION B — orbit data group location")
    hdr = data[header_idx * REC : (header_idx + 1) * REC]
    header_ok = i32(hdr, 1) == 109
    print(f"  record 5 primary key = {i32(hdr, 1)} (expect 109): {'PASS' if header_ok else 'FAIL'}")
    print(f"  data records 6..7452 (label), expected rows={expected_rows}")

    rows = []
    formats = Counter()
    types = Counter()
    rx_ids = Counter()
    tx_ids = Counter()
    for i in range(first_data, next_header):
        rec = data[i * REC : (i + 1) * REC]
        parsed = parse_row(rec)
        rows.append(parsed)
        formats[parsed["format_id"]] += 1
        types[parsed["data_type"]] += 1
        rx_ids[parsed["rx"]] += 1
        tx_ids[parsed["tx"]] += 1

    print(f"\nOrbit-data rows decoded: {len(rows)}  (expect {expected_rows})")
    if len(rows) != expected_rows:
        print("  row-count mismatch vs label ROWS")
    if not rows:
        print("NO ROWS")
        return 1

    # C1 format
    print("\nC1 — FORMAT ID")
    for fid, count in sorted(formats.items()):
        print(f"  format_id={fid}: {count}")
    c1 = formats.get(2, 0) == len(rows) and len(formats) == 1
    print(f"  all format_id==2: {'PASS' if c1 else 'FAIL'}")

    # C2 time window from label: 2002-157T20:41:30 to 2002-157T22:45:36
    # DOY 157 in 2002 = 2002-06-06
    t0 = datetime(2002, 6, 6, 20, 41, 30, tzinfo=timezone.utc)
    t1 = datetime(2002, 6, 6, 22, 45, 36, tzinfo=timezone.utc)
    times = [r["time"] for r in rows]
    mono = all(times[i] <= times[i + 1] for i in range(len(times) - 1))
    pad = timedelta(days=1)
    in_window = all((t0 - pad) <= t <= (t1 + pad) for t in times)
    print("\nC2 — time tags")
    print(f"  first = {times[0].isoformat()}")
    print(f"  last  = {times[-1].isoformat()}")
    print(f"  label window = {t0.isoformat()} .. {t1.isoformat()}")
    print(f"  monotonic non-decreasing: {'PASS' if mono else 'FAIL'}")
    print(f"  within label ±1 day: {'PASS' if in_window else 'FAIL'}")

    print("\nC3 — DATA TYPE ID histogram")
    for dtype, count in sorted(types.items()):
        name = DATA_TYPE_NAMES.get(dtype, "other")
        print(f"  type {dtype:02d} ({name}): {count}")
    has_doppler = any(t in {11, 12, 13} for t in types)
    has_range = any(t in {36, 37} for t in types)
    print(f"  Doppler types present: {has_doppler}")
    print(f"  Range types present: {has_range}")

    allowed_stations = {25, 45, 54}
    print("\nC4 — station IDs")
    print(f"  RX histogram: {dict(sorted(rx_ids.items()))}")
    print(f"  TX histogram: {dict(sorted(tx_ids.items()))}")
    rx_ok = all((s in allowed_stations) or s == 0 for s in rx_ids)
    tx_ok = all((s in allowed_stations) or s == 0 for s in tx_ids)
    print(f"  RX subset of label DSN set or 0: {'PASS' if rx_ok else 'FAIL'}")
    print(f"  TX subset of label DSN set or 0: {'PASS' if tx_ok else 'FAIL'}")

    print("\nC5 — residual")
    print("  STATUS: PENDING_DATA — not computed (protocol)")

    print("\n================================================================")
    print(
        "SUMMARY:",
        "FIELD_CENSUS_PASS"
        if c1 and mono and in_window and rx_ok and tx_ok
        else "FIELD_CENSUS_PARTIAL/FAIL",
    )
    print("================================================================")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
