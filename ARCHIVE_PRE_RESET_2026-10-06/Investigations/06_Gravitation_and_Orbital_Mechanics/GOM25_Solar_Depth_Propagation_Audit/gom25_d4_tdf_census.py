from __future__ import annotations

import argparse
import hashlib
import re
import sys
from collections import Counter
from pathlib import Path


EXPECTED_SHA256 = {
    "tdf": "354d6904bc19431894a921df4a9f9b8ca95fca7d490a8cb03dd8819f0164be30",
    "label": "b64981fb2c4b2e39d4fdd936753ff0fc11ece50e49c4083756fb620bf6e45081",
}
LOGICAL_RECORD_BYTES = 288
PHYSICAL_BLOCK_BYTES = 8064
DECLARED_RECORD_TYPES = {0: "EOF", 10: "file identification", 30: "transponder", 90: "low-rate tracking", 91: "high-rate tracking"}
EXPECTED_FORMATS = {10: 2048, 30: 2048, 90: 8, 91: 8}


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def read_bits(record: bytes, start_bit: int, width: int) -> int:
    value = 0
    for bit_index in range(start_bit - 1, start_bit - 1 + width):
        value = (value << 1) | ((record[bit_index // 8] >> (7 - (bit_index % 8))) & 1)
    return value


def label_value(label: str, name: str) -> str:
    match = re.search(rf"^{re.escape(name)}\s*=\s*(.+)$", label, re.MULTILINE)
    if not match:
        raise ValueError(f"missing label property: {name}")
    return match.group(1).strip().strip('"')


def timestamp(record: bytes) -> tuple[int, int, int, int, int]:
    return (
        1900 + read_bits(record, 73, 12),
        read_bits(record, 85, 16),
        read_bits(record, 101, 8),
        read_bits(record, 109, 12),
        read_bits(record, 121, 8),
    )


def format_timestamp(value: tuple[int, int, int, int, int]) -> str:
    year, day, hour, minute, second = value
    return f"{year:04d}-{day:03d}T{hour:02d}:{minute:02d}:{second:02d}"


def main() -> int:
    parser = argparse.ArgumentParser(description="Fail-closed GOM25 D4 Cassini TDF structural census.")
    parser.add_argument("--tdf", type=Path, default=Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_tdf.tdf"))
    parser.add_argument("--label", type=Path, default=Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_tdf.lbl"))
    arguments = parser.parse_args()

    tdf_hash = sha256(arguments.tdf)
    label_hash = sha256(arguments.label)
    label = arguments.label.read_text(encoding="ascii")
    data = arguments.tdf.read_bytes()

    record_bytes = int(label_value(label, "RECORD_BYTES"))
    file_records = int(label_value(label, "FILE_RECORDS"))
    label_timestamp = label_value(label, "PRODUCT_CREATION_TIME")
    data_set_id = label_value(label, "DATA_SET_ID")
    expected_bytes = record_bytes * file_records

    if record_bytes != LOGICAL_RECORD_BYTES:
        raise ValueError(f"unsupported label record width: {record_bytes}")
    if len(data) % LOGICAL_RECORD_BYTES:
        raise ValueError("file has a partial logical record")

    pairs: Counter[tuple[int, int]] = Counter()
    zero_records = 0
    file_id_records: list[bytes] = []
    undeclared_types: Counter[int] = Counter()
    for offset in range(0, len(data), LOGICAL_RECORD_BYTES):
        record = data[offset : offset + LOGICAL_RECORD_BYTES]
        if not any(record):
            zero_records += 1
        record_type = read_bits(record, 41, 32)
        record_format = read_bits(record, 5, 32) if record_type in {10, 30} else read_bits(record, 1, 32)
        pairs[(record_format, record_type)] += 1
        if record_type not in DECLARED_RECORD_TYPES:
            undeclared_types[record_type] += 1
        if record_type == 10:
            file_id_records.append(record)

    file_id = file_id_records[0] if len(file_id_records) == 1 else None
    decoded_timestamp = format_timestamp(timestamp(file_id)) if file_id else "UNDECODED"
    spacecraft_id = read_bits(file_id, 141, 16) if file_id else None
    raw_data_id_hex = file_id[16:30].hex() if file_id else "UNDECODED"
    size_ok = len(data) == expected_bytes
    block_ok = len(data) % PHYSICAL_BLOCK_BYTES == 0
    timestamp_ok = decoded_timestamp == label_timestamp
    structure_ok = size_ok and block_ok and not undeclared_types and len(file_id_records) == 1
    format_mismatches = {
        (record_format, record_type): count
        for (record_format, record_type), count in pairs.items()
        if record_type in EXPECTED_FORMATS and record_format != EXPECTED_FORMATS[record_type]
    }

    print("GOM25 D4 CASSINI TDF CENSUS")
    print(f"tdf_sha256={tdf_hash}")
    print(f"label_sha256={label_hash}")
    print(f"tdf_checksum={'PASS' if tdf_hash == EXPECTED_SHA256['tdf'] else 'FAIL'}")
    print(f"label_checksum={'PASS' if label_hash == EXPECTED_SHA256['label'] else 'FAIL'}")
    print(f"label_dataset_id={data_set_id}")
    print(f"bytes={len(data)} expected_bytes={expected_bytes} size={'PASS' if size_ok else 'FAIL'}")
    print(f"physical_blocks={len(data) // PHYSICAL_BLOCK_BYTES} block_alignment={'PASS' if block_ok else 'FAIL'}")
    print(f"logical_records={len(data) // LOGICAL_RECORD_BYTES} label_records={file_records}")
    print(f"zero_records={zero_records}")
    for (record_format, record_type), count in sorted(pairs.items()):
        declared = DECLARED_RECORD_TYPES.get(record_type, "UNDECLARED")
        print(f"pair format={record_format} type={record_type} count={count} declared_as={declared}")
    print(f"undeclared_type_count={sum(undeclared_types.values())}")
    print(f"declared_format_pairs={'PASS' if not format_mismatches else 'FAIL'}")
    for (record_format, record_type), count in sorted(format_mismatches.items()):
        print(f"format_mismatch type={record_type} actual={record_format} expected={EXPECTED_FORMATS[record_type]} count={count}")
    print(f"file_id_records={len(file_id_records)}")
    print(f"file_id_timestamp={decoded_timestamp} label_timestamp={label_timestamp} timestamp={'PASS' if timestamp_ok else 'FAIL'}")
    print(f"file_id_spacecraft_id={spacecraft_id}")
    print(f"file_id_data_id_raw_hex={raw_data_id_hex}")
    print(f"file_id_record_format={read_bits(file_id, 5, 32) if file_id else 'UNDECODED'} expected_by_tdf1_late_date=2048")
    print("observables=UNDECODED")
    print(f"status={'STRUCTURE_PARTIAL' if structure_ok and timestamp_ok and format_mismatches else 'STRUCTURE_VALIDATED' if structure_ok and timestamp_ok else 'STRUCTURE_FAILED'}")
    return 0 if structure_ok and timestamp_ok else 1


if __name__ == "__main__":
    sys.exit(main())
