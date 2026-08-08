from __future__ import annotations

import csv
import hashlib
import json
import sys
from pathlib import Path


RAW_DIRECTORY = Path("Datasets/solar_propagation_2026-08/raw")
EXPECTED_SHA256 = {
    "catalogue": "d5116e07f356015ae4211b0842c6d8b992af87adc41e98c50a46a2172688497d",
    "retrieval_doc": "f4a4405297dd1fe72ab6dc89417e80dba96889a6e1b2a9632ad5079d167d9112",
    "tap_doc": "74264f370f81db999d6e3d4249f4711476cba4b4178062b123da24fe8372b80c",
    "product_details": "2c1908cb9c1ce482f21100a9efde058a2a18bf0da7c35359abf84a5be0ae605b",
}
EXPECTED_TARGETS = {"3C279", "J1246-0730", "J1248-0632", "J1304-0346"}


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def find_delivery_values(value: object, path: str = "") -> list[tuple[str, str]]:
    found: list[tuple[str, str]] = []
    if isinstance(value, dict):
        for key, child in value.items():
            child_path = f"{path}.{key}" if path else key
            if any(token in key.lower() for token in ("url", "download", "delivery", "href")) and isinstance(child, str):
                found.append((child_path, child))
            found.extend(find_delivery_values(child, child_path))
    elif isinstance(value, list):
        for index, child in enumerate(value):
            found.extend(find_delivery_values(child, f"{path}[{index}]"))
    return found


def main() -> int:
    paths = {
        "catalogue": RAW_DIRECTORY / "nrao_bf080_obscore_catalogue.csv",
        "retrieval_doc": RAW_DIRECTORY / "nrao_vlba_data_retrieval.html",
        "tap_doc": RAW_DIRECTORY / "nrao_tap_scripted_access.html",
        "product_details": RAW_DIRECTORY / "nrao_bf080_file3_product_details.json",
    }
    checksums = {name: sha256(path) for name, path in paths.items()}
    with paths["catalogue"].open(newline="", encoding="utf-8") as handle:
        catalogue_rows = list(csv.DictReader(handle))
    details = json.loads(paths["product_details"].read_text(encoding="utf-8"))["details"]
    execution_blocks = details["execution_blocks"]
    block = execution_blocks[0]
    configured_targets = {
        item["target_name"]
        for configuration in block["configurations"]
        for item in configuration["target_durs"]
    }
    scan_targets = {item["target_name"] for item in block["scan_rows"]}
    delivery_values = find_delivery_values(details)
    tap_document = paths["tap_doc"].read_text(encoding="utf-8")
    retrieval_document = paths["retrieval_doc"].read_text(encoding="utf-8")
    checksum_gate = all(checksums[name] == EXPECTED_SHA256[name] for name in checksums)
    catalogue_gate = any(row["obs_id"] == "uid://vlba/correlation/c42283a7-61dc-4184-9b5e-37f8e6e4deed" for row in catalogue_rows)
    coverage_gate = EXPECTED_TARGETS.issubset(configured_targets) and EXPECTED_TARGETS.issubset(scan_targets)
    documentation_gate = "Downloads are not yet possible through this scripted interface." in tap_document and "notification e-mail" in retrieval_document

    print("GOM27 D5 BF080 STAGING AUDIT")
    for name in ("catalogue", "retrieval_doc", "tap_doc", "product_details"):
        print(f"{name}_sha256={checksums[name]}")
        print(f"{name}_checksum={'PASS' if checksums[name] == EXPECTED_SHA256[name] else 'FAIL'}")
    print(f"fixed_product_file={details['dataset_title']}")
    print(f"fixed_product_project={block['project_code']}")
    print(f"fixed_product_calibration_status={block['cal_status']}")
    print(f"fixed_product_scan_rows={len(block['scan_rows'])}")
    print("configured_targets=" + ",".join(sorted(configured_targets)))
    print("scan_targets=" + ",".join(sorted(scan_targets)))
    print(f"catalogue_locator_gate={'PASS' if catalogue_gate else 'FAIL'}")
    print(f"target_coverage_gate={'PASS' if coverage_gate else 'FAIL'}")
    print(f"documented_staging_gate={'PASS' if documentation_gate else 'FAIL'}")
    print(f"direct_delivery_values={len(delivery_values)}")
    print("raw_file=UNSTAGED")
    print(f"status={'PENDING_ACCESS' if checksum_gate and catalogue_gate and coverage_gate and documentation_gate and not delivery_values else 'ACCESS_AUDIT_FAILED'}")
    return 0 if checksum_gate and catalogue_gate and coverage_gate and documentation_gate else 1


if __name__ == "__main__":
    sys.exit(main())
