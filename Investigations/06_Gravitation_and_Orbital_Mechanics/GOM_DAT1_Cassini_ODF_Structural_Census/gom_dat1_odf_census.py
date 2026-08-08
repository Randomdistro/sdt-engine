#!/usr/bin/env python3
"""GOM28 — Cassini SCE1 ODF structural census (fail-closed). Pre-registered in PROMPT.md."""
from __future__ import annotations

import argparse
import hashlib
import re
import struct
import sys
from collections import Counter
from pathlib import Path

EXPECTED_SHA256 = {
    "odf": "c2ea51d9b5e795bd3eb9b4f1c5174cc44325080623188dce5e01c0ea914bfaf7",
    "label": "b27da74ca62187475860e8214c2b76b8b69af760bbe44d27aac93d1c1a5593bf",
}
RECORD_BYTES = 36
BLOCK_BYTES = 8064
DECLARED_HEADER_KEYS = {
    101: "file label group header",
    105: "ramp group header",
    107: "identifier group header",
    109: "orbit data group header",
    2030: "clock/bias or related group header",
    -1: "end-of-file group header",
}


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def label_value(label: str, name: str) -> str:
    match = re.search(rf"^{re.escape(name)}\s*=\s*(.+)$", label, re.MULTILINE)
    if not match:
        raise ValueError(f"missing label property: {name}")
    return match.group(1).strip().strip('"')


def u32(record: bytes, start_byte_1based: int) -> int:
    return struct.unpack_from(">I", record, start_byte_1based - 1)[0]


def i32(record: bytes, start_byte_1based: int) -> int:
    return struct.unpack_from(">i", record, start_byte_1based - 1)[0]


def header_like(record: bytes) -> bool:
    return u32(record, 5) == 0 and u32(record, 9) in {0, 1}


def validate_synthetic() -> bool:
    payload = struct.pack(">iiii", 101, 0, 1, 1) + bytes(20)
    ok = len(payload) == RECORD_BYTES and i32(payload, 1) == 101 and u32(payload, 5) == 0
    print("VALIDATION A — synthetic 36-byte big-endian header")
    print(f"  round-trip primary key=101: {'PASS' if ok else 'FAIL'}")
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
    print("GOM28 — Cassini SCE1 ODF Structural Census")
    print("Pre-registered 2026-08-07 · no residual extraction")
    print("================================================================\n")

    if not validate_synthetic():
        print("INSTRUMENT VALIDATION FAILED")
        return 2

    odf_hash = sha256(args.odf)
    label_hash = sha256(args.label)
    print("HASH GATE")
    print(f"  odf   {odf_hash}  {'PASS' if odf_hash == EXPECTED_SHA256['odf'] else 'FAIL'}")
    print(f"  label {label_hash}  {'PASS' if label_hash == EXPECTED_SHA256['label'] else 'FAIL'}")
    if odf_hash != EXPECTED_SHA256["odf"] or label_hash != EXPECTED_SHA256["label"]:
        print("INSTRUMENT INVALID — checksum mismatch")
        return 3

    label = args.label.read_text(encoding="ascii", errors="replace")
    data = args.odf.read_bytes()
    record_bytes = int(label_value(label, "RECORD_BYTES"))
    file_records = int(label_value(label, "FILE_RECORDS"))
    creation = label_value(label, "PRODUCT_CREATION_TIME")
    data_set_id = label_value(label, "DATA_SET_ID")
    expected_bytes = record_bytes * file_records

    print("\nC1/C2 — size and packing")
    print(f"  label RECORD_BYTES={record_bytes} FILE_RECORDS={file_records}")
    print(f"  expected bytes={expected_bytes} actual={len(data)}")
    size_ok = record_bytes == RECORD_BYTES and len(data) == expected_bytes
    block_ok = len(data) % BLOCK_BYTES == 0
    print(f"  size match: {'PASS' if size_ok else 'FAIL'}")
    print(
        f"  8064-block packing ({len(data) // BLOCK_BYTES} blocks): "
        f"{'PASS' if block_ok else 'FAIL'}"
    )
    print("\nVALIDATION B — no partial record")
    print(f"  len % 36 == 0: {'PASS' if len(data) % RECORD_BYTES == 0 else 'FAIL'}")

    keys: Counter[int] = Counter()
    for index in range(len(data) // RECORD_BYTES):
        rec = data[index * RECORD_BYTES : (index + 1) * RECORD_BYTES]
        primary = i32(rec, 1)
        if primary in DECLARED_HEADER_KEYS and header_like(rec):
            keys[primary] += 1

    undeclared: Counter[int] = Counter()
    print("\nC3 — group headers at label pointer records")
    print("  rule: only tables whose name matches ODF*A* are headers; *B*/*C* are data")
    for match in re.finditer(
        r'^\^(ODF\w+_TABLE)\s*=\s*\("[^"]+",\s*(\d+)\)\s*$', label, re.M
    ):
        table = match.group(1)
        recno = int(match.group(2))
        if recno < 1 or recno > file_records:
            continue
        rec = data[(recno - 1) * RECORD_BYTES : recno * RECORD_BYTES]
        primary = i32(rec, 1)
        # Header tables: ODF1A, ODF2A, ODF3A, ODF4A25, ODF7A, ODF8A, ...
        is_header_table = re.match(r"ODF\d+A", table) is not None
        if is_header_table:
            status = "DECLARED" if primary in DECLARED_HEADER_KEYS else "UNDECLARED"
            if primary not in DECLARED_HEADER_KEYS:
                undeclared[primary] += 1
            print(
                f"  {table:16s} record {recno:5d} primary={primary:6d}  HEADER {status}"
            )
        else:
            print(
                f"  {table:16s} record {recno:5d} primary={primary:6d}  DATA (skipped)"
            )

    print(f"\n  declared-header census (full file): {dict(keys)}")
    print(
        f"  undeclared keys on header-table pointers: "
        f"{dict(undeclared) if undeclared else 'none'}"
    )
    c3_ok = not undeclared and keys.get(101, 0) >= 1 and keys.get(109, 0) >= 1

    label_data = data[RECORD_BYTES : 2 * RECORD_BYTES]
    sc_id = u32(label_data, 17)
    system_id = label_data[0:8].decode("ascii", errors="replace").strip("\x00 ")
    program_id = label_data[8:16].decode("ascii", errors="replace").strip("\x00 ")
    print("\nC4 — file label group fields")
    print(f"  label PRODUCT_CREATION_TIME={creation}")
    print(f"  label DATA_SET_ID={data_set_id}")
    print(f"  decoded SYSTEM ID={system_id!r} PROGRAM ID={program_id!r}")
    print(f"  decoded SPACECRAFT ID={sc_id}")
    sc_ok = sc_id == 82
    print(
        f"  spacecraft id == 82 (Cassini common id): "
        f"{'PASS' if sc_ok else 'UNADJUDICATED/FAIL'}"
    )
    print(
        "  creation date/time integer decode: UNADJUDICATED "
        "(no revision-matched TRK-2-18 fixture)"
    )

    print("\nC5 — residual extraction")
    print("  STATUS: PENDING_DATA — intentionally not performed")

    structure_ok = size_ok and block_ok and c3_ok
    if structure_ok and sc_ok:
        summary = "STRUCTURE_PASS"
    elif structure_ok:
        summary = "STRUCTURE_PARTIAL"
    else:
        summary = "STRUCTURE_FAIL"

    print("\n================================================================")
    print("SUMMARY:", summary)
    print("No Doppler/range/delay residual decoded.")
    print("================================================================")
    return 0 if structure_ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
