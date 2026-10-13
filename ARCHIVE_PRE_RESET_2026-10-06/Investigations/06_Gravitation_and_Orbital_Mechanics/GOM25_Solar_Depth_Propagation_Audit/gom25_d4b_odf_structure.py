#!/usr/bin/env python3
"""Fail-closed structure audit for the frozen Cassini SCE1 ODF fixture."""

from __future__ import annotations

import hashlib
import json
from collections import Counter
from datetime import UTC, datetime, timedelta
from pathlib import Path


ROOT = Path(__file__).resolve().parents[3]
RAW = ROOT / "Datasets/solar_propagation_2026-08/raw"
ODF_PATH = RAW / "cassini_sce1_157_odf.odf"
LABEL_PATH = RAW / "cassini_sce1_157_odf.lbl"
OUTPUT_PATH = Path(__file__).with_name("gom25_d4b_odf_structure_results.json")

EXPECTED_HASHES = {
    ODF_PATH: "c2ea51d9b5e795bd3eb9b4f1c5174cc44325080623188dce5e01c0ea914bfaf7",
    LABEL_PATH: "b27da74ca62187475860e8214c2b76b8b69af760bbe44d27aac93d1c1a5593bf",
}
RECORD_BYTES = 36
FILE_RECORDS = 7616
ODF3C_START = 5
ODF3C_STOP = 7452
ALLOWED_DATA_TYPES = {
    1,
    2,
    3,
    4,
    5,
    6,
    11,
    12,
    13,
    21,
    22,
    23,
    36,
    37,
    41,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
}
EXPECTED_HEADERS = {
    0: (101, 0, 1, 0),
    2: (107, 0, 1, 2),
    4: (109, 0, 1, 4),
    7452: (2030, 25, 1, 7452),
    7454: (2030, 45, 1, 7454),
    7455: (2030, 54, 1, 7455),
    7456: (105, 0, 1, 7456),
    7458: (-1, 0, 0, 7458),
}
REFERENCE_EPOCH = datetime(1950, 1, 1, tzinfo=UTC)


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def unsigned32(record: bytes, offset: int) -> int:
    return int.from_bytes(record[offset : offset + 4], byteorder="big", signed=False)


def signed32(record: bytes, offset: int) -> int:
    return int.from_bytes(record[offset : offset + 4], byteorder="big", signed=True)


def extract_bits(word: int, width: int, start_bit: int, bits: int) -> int:
    shift = width - (start_bit - 1) - bits
    return (word >> shift) & ((1 << bits) - 1)


def iso_time(seconds: int, milliseconds: int) -> str:
    timestamp = REFERENCE_EPOCH + timedelta(seconds=seconds, milliseconds=milliseconds)
    return timestamp.isoformat().replace("+00:00", "Z")


def pds_time(value: str) -> datetime:
    return datetime.strptime(value, "%Y-%jT%H:%M:%S").replace(tzinfo=UTC)


def header_values(record: bytes) -> tuple[int, int, int, int]:
    return (
        signed32(record, 0),
        unsigned32(record, 4),
        unsigned32(record, 8),
        unsigned32(record, 12),
    )


def orbit_record_metadata(record: bytes) -> dict[str, int | str]:
    item_two_three = unsigned32(record, 4)
    metadata_word = int.from_bytes(record[16:28], byteorder="big", signed=False)
    seconds = unsigned32(record, 0)
    milliseconds = extract_bits(item_two_three, 32, 1, 10)
    return {
        "time_seconds": seconds,
        "time_milliseconds": milliseconds,
        "time_utc": iso_time(seconds, milliseconds),
        "format_id": extract_bits(metadata_word, 96, 1, 3),
        "primary_station_id": extract_bits(metadata_word, 96, 4, 7),
        "transmitting_station_id": extract_bits(metadata_word, 96, 11, 7),
        "data_type_id": extract_bits(metadata_word, 96, 20, 6),
        "downlink_band_id": extract_bits(metadata_word, 96, 26, 2),
        "uplink_band_id": extract_bits(metadata_word, 96, 28, 2),
        "exciter_band_id": extract_bits(metadata_word, 96, 30, 2),
        "data_validity_indicator": extract_bits(metadata_word, 96, 32, 1),
    }


def parse_file_label_data(record: bytes) -> dict[str, int | str]:
    return {
        "system_id": record[0:8].decode("ascii").strip(),
        "program_id": record[8:16].decode("ascii").strip(),
        "spacecraft_id": unsigned32(record, 16),
        "file_creation_date": f"{unsigned32(record, 20):06d}",
        "file_creation_time": f"{unsigned32(record, 24):06d}",
        "reference_date": f"{unsigned32(record, 28):08d}",
        "reference_time": f"{unsigned32(record, 32):06d}",
    }


def parse_data_summary(record: bytes) -> dict[str, int | str]:
    first_seconds = unsigned32(record, 0)
    first_nanoseconds = unsigned32(record, 4)
    last_seconds = unsigned32(record, 28)
    last_nanoseconds = unsigned32(record, 32)
    return {
        "first_time_utc": iso_time(first_seconds, first_nanoseconds // 1_000_000),
        "station_id": unsigned32(record, 8),
        "network_or_doppler_id": unsigned32(record, 12),
        "band_id": unsigned32(record, 16),
        "data_type_id": unsigned32(record, 20),
        "number_of_samples": unsigned32(record, 24),
        "last_time_utc": iso_time(last_seconds, last_nanoseconds // 1_000_000),
    }


def main() -> None:
    hash_results = {
        str(path.relative_to(ROOT)).replace("\\", "/"): {
            "expected": expected,
            "actual": sha256(path),
        }
        for path, expected in EXPECTED_HASHES.items()
    }
    for result in hash_results.values():
        result["matches"] = result["actual"] == result["expected"]
    if not all(result["matches"] for result in hash_results.values()):
        raise RuntimeError("Frozen input checksum mismatch")

    data = ODF_PATH.read_bytes()
    if len(data) != RECORD_BYTES * FILE_RECORDS:
        raise RuntimeError("ODF does not match the labelled record framing")
    records = [data[offset : offset + RECORD_BYTES] for offset in range(0, len(data), RECORD_BYTES)]

    header_checks = {
        str(index): {
            "expected": expected,
            "actual": header_values(records[index]),
        }
        for index, expected in EXPECTED_HEADERS.items()
    }
    for result in header_checks.values():
        result["matches"] = tuple(result["actual"]) == result["expected"]

    file_label_data = parse_file_label_data(records[1])
    file_label_checks = {
        "system_id": file_label_data["system_id"] == "AXP2300",
        "program_id": file_label_data["program_id"] == "ODE V2.0",
        "spacecraft_id": file_label_data["spacecraft_id"] == 82,
        "creation_date": file_label_data["file_creation_date"] == "020615",
        "creation_time": file_label_data["file_creation_time"] == "020918",
        "reference_date": file_label_data["reference_date"] == "19500101",
        "reference_time": file_label_data["reference_time"] == "000000",
    }

    orbit_rows = [orbit_record_metadata(record) for record in records[ODF3C_START:ODF3C_STOP]]
    format_counts = Counter(int(row["format_id"]) for row in orbit_rows)
    type_counts = Counter(int(row["data_type_id"]) for row in orbit_rows)
    receive_station_counts = Counter(int(row["primary_station_id"]) for row in orbit_rows)
    transmit_station_counts = Counter(int(row["transmitting_station_id"]) for row in orbit_rows)
    validity_counts = Counter(int(row["data_validity_indicator"]) for row in orbit_rows)
    first_row = orbit_rows[0]
    last_row = orbit_rows[-1]
    start_bound = pds_time("2002-157T20:41:30")
    stop_bound = pds_time("2002-157T22:45:36")
    actual_start = REFERENCE_EPOCH + timedelta(
        seconds=int(first_row["time_seconds"]), milliseconds=int(first_row["time_milliseconds"])
    )
    actual_stop = REFERENCE_EPOCH + timedelta(
        seconds=int(last_row["time_seconds"]), milliseconds=int(last_row["time_milliseconds"])
    )
    summary = parse_data_summary(records[7457])
    summary_first_milliseconds = unsigned32(records[7457], 4) // 1_000_000
    summary_last_milliseconds = unsigned32(records[7457], 32) // 1_000_000
    first_offset_milliseconds = int(first_row["time_milliseconds"]) - summary_first_milliseconds
    last_offset_milliseconds = int(last_row["time_milliseconds"]) - summary_last_milliseconds

    structure_checks = {
        "record_count_matches_label": len(records) == FILE_RECORDS,
        "orbit_data_rows_match_label": len(orbit_rows) == 7447,
        "all_orbit_format_ids_are_two": set(format_counts) == {2},
        "all_data_type_ids_declared": set(type_counts).issubset(ALLOWED_DATA_TYPES),
        "all_primary_stations_declared": set(receive_station_counts).issubset({25, 45, 54}),
        "all_validity_flags_declared": set(validity_counts).issubset({0, 1}),
        "time_tags_within_label_bounds": start_bound <= actual_start <= actual_stop <= stop_bound,
        "data_summary_sample_count_matches": summary["number_of_samples"] == len(orbit_rows),
        "data_summary_time_bounds_match": (
            summary["first_time_utc"] == first_row["time_utc"]
            and summary["last_time_utc"] == last_row["time_utc"]
        ),
    }
    structure_checks_pass = (
        all(structure_checks.values())
        and all(result["matches"] for result in header_checks.values())
        and all(file_label_checks.values())
    )
    result = {
        "audit_date": "2026-08-08",
        "scope": "ODF structure, metadata, and time-tag audit only; observable values intentionally unread",
        "input_hashes": hash_results,
        "record_bytes": RECORD_BYTES,
        "file_records": len(records),
        "physical_blocks_8064": len(data) // 8064,
        "header_checks": header_checks,
        "file_label_data": file_label_data,
        "file_label_checks": file_label_checks,
        "orbit_data_metadata": {
            "row_count": len(orbit_rows),
            "first_time_utc": first_row["time_utc"],
            "last_time_utc": last_row["time_utc"],
            "format_id_counts": dict(sorted(format_counts.items())),
            "data_type_id_counts": dict(sorted(type_counts.items())),
            "primary_station_id_counts": dict(sorted(receive_station_counts.items())),
            "transmitting_station_id_counts": dict(sorted(transmit_station_counts.items())),
            "data_validity_indicator_counts": dict(sorted(validity_counts.items())),
        },
        "data_summary": summary,
        "orbit_data_minus_summary_time_milliseconds": {
            "first": first_offset_milliseconds,
            "last": last_offset_milliseconds,
        },
        "structure_checks": structure_checks,
        "structure_checks_pass": structure_checks_pass,
        "observable_status": "UNDECODED",
        "classification": (
            "READY_FOR_ODF_FIXTURE_ONLY" if structure_checks_pass else "STRUCTURE_PARTIAL"
        ),
    }
    OUTPUT_PATH.write_text(json.dumps(result, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    print(json.dumps(result, indent=2, sort_keys=True))


if __name__ == "__main__":
    main()
