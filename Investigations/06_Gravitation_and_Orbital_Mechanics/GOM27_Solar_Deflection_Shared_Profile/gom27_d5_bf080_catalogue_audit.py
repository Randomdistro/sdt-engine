from __future__ import annotations

import csv
import hashlib
import sys
from collections import Counter
from datetime import datetime, timedelta, timezone
from pathlib import Path


EXPECTED_SHA256 = {
    "catalogue": "d5116e07f356015ae4211b0842c6d8b992af87adc41e98c50a46a2172688497d",
    "retrieval_doc": "f4a4405297dd1fe72ab6dc89417e80dba96889a6e1b2a9632ad5079d167d9112",
    "tap_doc": "74264f370f81db999d6e3d4249f4711476cba4b4178062b123da24fe8372b80c",
}
RAW_DIRECTORY = Path("Datasets/solar_propagation_2026-08/raw")
EXPECTED_TARGETS = {"3C279", "J1246-0730", "J1248-0632", "J1304-0346"}
EXPECTED_DATES = {
    "2005-10-01",
    "2005-10-05",
    "2005-10-06",
    "2005-10-07",
    "2005-10-09",
    "2005-10-10",
    "2005-10-11",
    "2005-10-18",
}


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def mjd_date(value: str) -> str:
    epoch = datetime(1858, 11, 17, tzinfo=timezone.utc)
    return (epoch + timedelta(days=float(value))).date().isoformat()


def main() -> int:
    paths = {
        "catalogue": RAW_DIRECTORY / "nrao_bf080_obscore_catalogue.csv",
        "retrieval_doc": RAW_DIRECTORY / "nrao_vlba_data_retrieval.html",
        "tap_doc": RAW_DIRECTORY / "nrao_tap_scripted_access.html",
    }
    checksums = {name: sha256(path) for name, path in paths.items()}
    with paths["catalogue"].open(newline="", encoding="utf-8") as handle:
        rows = list(csv.DictReader(handle))

    projects = {row["project_code"] for row in rows}
    target_rows = [row for row in rows if row["target_name"] in EXPECTED_TARGETS and 53644 <= float(row["t_min"]) < 53662]
    target_counts = Counter(row["target_name"] for row in target_rows)
    dates = {mjd_date(row["t_min"]) for row in target_rows}
    formats = set(row["access_format"] for row in target_rows)
    statuses = set(row["proprietary_status"] for row in target_rows)
    product_sizes = {}
    for row in target_rows:
        product_sizes[row["obs_id"]] = int(row["access_estsize"])
    required_observable_columns = {"angular_offset", "uncertainty", "solar_elongation", "impact_parameter"}
    column_gate = required_observable_columns.issubset(set(rows[0]))
    checksum_gate = all(checksums[name] == EXPECTED_SHA256[name] for name in checksums)
    campaign_gate = projects == {"BF080"} and set(target_counts) == EXPECTED_TARGETS and dates == EXPECTED_DATES

    print("GOM27 D5 BF080 CATALOGUE AUDIT")
    for name in ("catalogue", "retrieval_doc", "tap_doc"):
        print(f"{name}_sha256={checksums[name]}")
        print(f"{name}_checksum={'PASS' if checksums[name] == EXPECTED_SHA256[name] else 'FAIL'}")
    print(f"catalogue_rows={len(rows)}")
    print(f"project_codes={','.join(sorted(projects))}")
    print("target_row_counts=" + ",".join(f"{target}:{target_counts[target]}" for target in sorted(target_counts)))
    print("session_dates=" + ",".join(sorted(dates)))
    print(f"public_product_formats={','.join(sorted(formats))}")
    print(f"public_statuses={','.join(sorted(statuses))}")
    print(f"public_candidate_products={len(product_sizes)}")
    print(f"reported_product_size_sum={sum(product_sizes.values())}")
    print(f"campaign_identity={'PASS' if campaign_gate else 'FAIL'}")
    print(f"observable_column_gate={'PASS' if column_gate else 'FAIL'}")
    print("deflection_observable=UNDECODED")
    print(f"status={'PENDING_RECONSTRUCTION' if checksum_gate and campaign_gate and not column_gate else 'DATA_AUDIT_FAILED'}")
    return 0 if checksum_gate and campaign_gate else 1


if __name__ == "__main__":
    sys.exit(main())
