"""Freeze APS14a term-labelled lines and optionally cache NIST ASD responses."""

from __future__ import annotations

import argparse
import csv
import hashlib
import urllib.parse
import urllib.request
from pathlib import Path

HERE = Path(__file__).resolve().parent
DATA = HERE / "data"
RAW = DATA / "raw/nist_asd"
HOLDOUT = {3, 7, 10, 11, 18, 19, 26, 29}


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def cache_nist(z: int, symbol: str) -> Path:
    RAW.mkdir(parents=True, exist_ok=True)
    destination = RAW / f"{z:02d}_{symbol}_I.tsv"
    if destination.exists():
        return destination
    query = urllib.parse.urlencode({
        "spectra": f"{symbol} I", "low_w": 0.1, "upp_w": 100000,
        "format": 3, "output": 0, "unit": 1,
        "page_size": 200, "show_obs_wl": 1, "show_calc_wl": 1,
        "show_av": 3, "order_out": 0, "en_unit": 1, "line_out": 1,
        "A_out": 0, "g_out": "on", "submit": "Retrieve Data",
        "allowed_out": 1, "forbid_out": 1, "conf_out": "on",
        "term_out": "on", "enrg_out": "on", "J_out": "on",
    })
    request = urllib.request.Request(
        "https://physics.nist.gov/cgi-bin/ASD/lines1.pl?" + query,
        headers={"User-Agent": "APS14a/1.0"},
    )
    destination.write_bytes(urllib.request.urlopen(request, timeout=45).read())
    return destination


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--fetch-nist", action="store_true")
    args = parser.parse_args()
    with (DATA / "elements.csv").open(encoding="utf-8") as handle:
        elements = {int(row["Z"]): row for row in csv.DictReader(handle)}
    with (DATA / "resonance.csv").open(encoding="utf-8") as handle:
        source = list(csv.DictReader(handle))
    rows = []
    for row in source:
        z = int(row["Z"])
        control = row["set"] == "HLIKE_CONTROL"
        rows.append({
            **row,
            "A": elements[z]["A"],
            "split": (
                "CONTROL" if control
                else "HOLDOUT" if z in HOLDOUT else "CALIBRATION"
            ),
            "family": (
                "HLIKE" if control
                else "SAME_N" if any(token in row["transition"]
                                     for token in ("2s→2p", "3s→3p", "4s→4p"))
                else "CROSS_N"
            ),
        })
    output = DATA / "aps14a_lines.csv"
    with output.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows(rows)
    fetched = []
    if args.fetch_nist:
        for z, element in elements.items():
            try:
                fetched.append(cache_nist(z, element["symbol"]))
            except Exception as error:
                error_path = RAW / f"{z:02d}_{element['symbol']}_I.error.txt"
                error_path.parent.mkdir(parents=True, exist_ok=True)
                error_path.write_text(repr(error), encoding="utf-8")
                fetched.append(error_path)
    manifest = [
        "# APS14a Line Data Manifest", "",
        f"- Frozen scored ledger: `{output.relative_to(HERE).as_posix()}`",
        f"- SHA256: `{sha256(output)}`",
        "- Neutral lines: APS01 NIST measured comparison columns.",
        "- H-like rows: controls only; never fitted.",
        f"- Whole-element hold-outs: `{sorted(HOLDOUT)}`.",
        "- NIST ASD raw responses are discovery cache, not silently promoted",
        "  into the scored ledger.", "",
        "## Raw response hashes", "",
    ]
    for path in fetched:
        manifest.append(
            f"- `{path.relative_to(HERE).as_posix()}`: `{sha256(path)}`"
        )
    (HERE / "DATA_MANIFEST_APS14A.md").write_text(
        "\n".join(manifest) + "\n", encoding="utf-8"
    )
    print(
        f"rows={len(rows)} calibration={sum(r['split']=='CALIBRATION' for r in rows)} "
        f"holdout={sum(r['split']=='HOLDOUT' for r in rows)} controls="
        f"{sum(r['split']=='CONTROL' for r in rows)} raw={len(fetched)}"
    )


if __name__ == "__main__":
    main()
