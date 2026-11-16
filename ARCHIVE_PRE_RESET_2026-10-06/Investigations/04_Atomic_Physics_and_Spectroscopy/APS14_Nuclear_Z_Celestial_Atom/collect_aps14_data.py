"""Build APS14's independent Z<=30 data ledgers."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
import urllib.parse
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
HERE = Path(__file__).resolve().parent
DATA = HERE / "data"
RAW = DATA / "raw"
HEADER = ROOT / "Investigations/04_Atomic_Physics_and_Spectroscopy/APS01_Emissions/aps01_element_data.hpp"
APS01 = ROOT / "Investigations/04_Atomic_Physics_and_Spectroscopy/APS01_Emissions/aps01_emissions.cpp"
IE_JSON = ROOT / "Datasets/nuclear/ionisation_energies.json"
RADIUS_URL = "https://raw.githubusercontent.com/theochem/horton/master/data/elements.csv"
HOLDOUT = {2, 10, 11, 18, 19, 24, 26, 29}


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def write_csv(path: Path, fieldnames: list[str], rows: list[dict]) -> None:
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)


def collect_elements() -> list[dict]:
    text = HEADER.read_text(encoding="utf-8")
    pattern = re.compile(
        r'\{(\d+),(\d+),\d+,\{[^}]*\},([^,]+),"([^"]+)",'
        r'"[^"]+",\d+,"([^"]+)"\}'
    )
    rows = []
    for match in pattern.finditer(text):
        z = int(match.group(1))
        if z > 30:
            break
        eex = float(match.group(3))
        rows.append({
            "Z": z, "A": int(match.group(2)), "symbol": match.group(4),
            "configuration": match.group(5), "first_excitation_eV": eex if eex > 0 else "",
            "split": "HOLDOUT" if z in HOLDOUT else "CALIBRATION",
            "origin": "MEASURED" if eex > 0 else "NO_DATA",
            "source": "APS01/NIST+CRC",
        })
    return rows


def collect_ionisation(elements: list[dict]) -> list[dict]:
    values = json.loads(IE_JSON.read_text(encoding="utf-8"))
    symbols = {int(row["Z"]): row["symbol"] for row in elements}
    rows = []
    for z in range(1, 31):
        sequence = values[str(z)]
        for step in range(1, z + 1):
            available = step <= len(sequence)
            rows.append({
                "Z": z, "symbol": symbols[z], "step": step,
                "energy_eV": sequence[step - 1] if available else "",
                "status": "MEASURED" if available else "NO_DATA",
                "split": "HOLDOUT" if z in HOLDOUT else "CALIBRATION",
                "source": "Datasets/nuclear/ionisation_energies.json",
            })
    return rows


def collect_resonance() -> list[dict]:
    text = APS01.read_text(encoding="utf-8")
    block = text.split("static const ResLine FIRST_RES[] = {", 1)[1].split("};", 1)[0]
    pattern = re.compile(
        r'\{\s*(\d+),\s*"([^"]+)",\s*([0-9.]+),'
        r'\s*eV_from_nm\(\s*[0-9.]+\),\s*"([^"]+)"\}'
    )
    rows = []
    for match in pattern.finditer(block):
        z, wavelength = int(match.group(1)), float(match.group(3))
        rows.append({
            "Z": z, "symbol": match.group(2), "charge": 0,
            "lower_n": "", "upper_n": "", "transition": match.group(4),
            "wavelength_nm": wavelength, "energy_eV": 1239.8419843320025 / wavelength,
            "set": "FINAL_UNTOUCHED", "origin": "MEASURED",
            "source": "APS01 NIST comparison column",
        })
    hlike = [
        (1, "H", 0, 1, 2, 121.5670), (1, "H", 0, 1, 3, 102.5722),
        (1, "H", 0, 2, 3, 656.4614), (2, "He", 1, 1, 2, 30.3785),
        (2, "He", 1, 1, 3, 25.6317), (3, "Li", 2, 1, 2, 13.5006),
        (3, "Li", 2, 1, 3, 11.3921),
    ]
    for z, symbol, charge, lower, upper, wavelength in hlike:
        rows.append({
            "Z": z, "symbol": symbol, "charge": charge, "lower_n": lower,
            "upper_n": upper, "transition": f"{upper}->{lower}",
            "wavelength_nm": wavelength, "energy_eV": 1239.8419843320025 / wavelength,
            "set": "HLIKE_CONTROL", "origin": "MEASURED",
            "source": "APS01 NIST comparison column",
        })
    return rows


def collect_radii() -> list[dict]:
    raw_path = RAW / "horton_elements.csv"
    if not raw_path.exists():
        request = urllib.request.Request(RADIUS_URL, headers={"User-Agent": "APS14/1.0"})
        raw_path.write_bytes(urllib.request.urlopen(request, timeout=30).read())
    rows = []
    lines = raw_path.read_text(encoding="utf-8").splitlines()
    header_index = next(
        index for index, line in enumerate(lines) if line.startswith("number,symbol")
    )
    records = csv.DictReader(lines[header_index:])
    if records.fieldnames is None:
        raise ValueError("covalent-radius header not found")
    for record in records:
        raw_z = record["number"].strip()
        if not raw_z.isdigit():
            continue
        z = int(raw_z)
        if 1 <= z <= 30:
            rows.append({
                "Z": z, "symbol": record["symbol"],
                "radius_angstrom": record["cov_radius_cordero"],
                "origin": "MEASURED", "source": "Cordero et al. 2008",
            })
    return rows


def cache_nist(elements: list[dict]) -> None:
    nist_dir = RAW / "nist_asd"
    nist_dir.mkdir(exist_ok=True)
    base = "https://physics.nist.gov/cgi-bin/ASD/lines1.pl?"
    for row in elements:
        spectrum = f'{row["symbol"]} I'
        query = urllib.parse.urlencode({
            "spectra": spectrum, "format": 3, "output": 0, "unit": 1,
            "page_size": 15, "show_obs_wl": 1, "show_calc_wl": 1,
            "en_unit": 1, "line_out": 0, "submit": "Retrieve Data",
        })
        request = urllib.request.Request(
            base + query, headers={"User-Agent": "APS14/1.0"}
        )
        try:
            (nist_dir / f'{int(row["Z"]):02d}_{row["symbol"]}_I.tsv').write_bytes(
                urllib.request.urlopen(request, timeout=30).read()
            )
        except Exception as error:
            (nist_dir / f'{int(row["Z"]):02d}_{row["symbol"]}_I.error.txt').write_text(
                repr(error), encoding="utf-8"
            )


def write_manifest() -> None:
    files = sorted(path for path in DATA.rglob("*") if path.is_file())
    lines = [
        "# APS14 Data Manifest", "",
        "All forward-model targets are external measured values or explicit `NO_DATA`.",
        "Generated predictions are never inputs.", "",
        "| File | SHA256 | Status |",
        "|---|---|---|",
    ]
    for path in files:
        lines.append(f"| `{path.relative_to(HERE).as_posix()}` | `{sha256(path)}` | cached input |")
    lines += [
        "", "## Sources", "",
        "- Sequential IE: repository JSON compiled from NIST/CRC.",
        "- Configurations and resonance lines: APS01 measured columns.",
        "- Covalent radii: Cordero et al., Dalton Trans. 2008, DOI 10.1039/B801115J.",
        "- Raw NIST ASD responses are discovery cache only; the untouched scored",
        "  resonance set is the APS01 measured comparison corpus.",
        "- Zn absent sequential entries are `NO_DATA`, not zeros or fitted values.",
    ]
    (HERE / "DATA_MANIFEST.md").write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--fetch-nist", action="store_true")
    args = parser.parse_args()
    RAW.mkdir(parents=True, exist_ok=True)
    elements = collect_elements()
    write_csv(DATA / "elements.csv", list(elements[0]), elements)
    ionisation = collect_ionisation(elements)
    write_csv(DATA / "ionisation.csv", list(ionisation[0]), ionisation)
    resonance = collect_resonance()
    write_csv(DATA / "resonance.csv", list(resonance[0]), resonance)
    radii = collect_radii()
    write_csv(DATA / "covalent_radii.csv", list(radii[0]), radii)
    if args.fetch_nist:
        cache_nist(elements)
    write_manifest()
    print(f"elements={len(elements)} IE_rows={len(ionisation)} "
          f"resonance_rows={len(resonance)} radii={len(radii)}")


if __name__ == "__main__":
    main()
