#!/usr/bin/env python3
"""Build independent APS12b measured corpora.

Reads canonical upstream files and the IAEA LiveChart API. It never reads
APS12 or APS12a generated artifacts.
"""
from __future__ import annotations

import csv
import hashlib
import json
import urllib.request
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
DATA = HERE / "data"
RAW = DATA / "raw"
ATOMIC_OUT = DATA / "atomic_lines.csv"
RADII_OUT = DATA / "nuclear_radii.csv"
GAMMA_OUT = DATA / "gamma_transitions.csv"

ATOMIC_FIELDS = [
    "corpus", "split", "species", "Z", "A", "n_upper", "n_lower",
    "frequency_Hz", "unc_frequency_Hz", "source", "source_quantity",
]

NUCLIDES = [
    "12c", "16o", "24mg", "40ca", "57fe", "60ni", "90zr",
    "119sn", "137ba", "152sm", "197au", "208pb", "241am",
]


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def write_atomic() -> None:
    c = 299_792_458.0
    e_charge = 1.602_176_634e-19
    h = 6.626_070_15e-34
    rows: list[dict[str, object]] = []

    def wavelength(corpus: str, split: str, species: str, Z: int, A: int,
                   n_upper: int, n_lower: int, nm: float, source: str) -> None:
        rows.append({
            "corpus": corpus, "split": split, "species": species, "Z": Z,
            "A": A, "n_upper": n_upper, "n_lower": n_lower,
            "frequency_Hz": c / (nm * 1e-9), "unc_frequency_Hz": "",
            "source": source, "source_quantity": f"{nm} nm",
        })

    h_l = [(2, 121.5670), (3, 102.5722), (4, 97.2537),
           (5, 94.9743), (6, 93.7803)]
    h_b = [(3, 656.4614), (4, 486.2712), (5, 434.1692),
           (6, 410.2892), (7, 397.1233)]
    h_p = [(4, 1875.6200), (5, 1282.1700),
           (6, 1094.1200), (7, 1005.2200)]
    for n, nm in h_l:
        wavelength("H_LINES", "train" if n <= 4 else "test", "H I",
                   1, 1, n, 1, nm, "NIST ASD comparison column in APS01")
    for n, nm in h_b:
        wavelength("H_LINES", "train" if n <= 4 else "test", "H I",
                   1, 1, n, 2, nm, "NIST ASD comparison column in APS01")
    for n, nm in h_p:
        wavelength("H_LINES", "test", "H I", 1, 1, n, 3, nm,
                   "NIST ASD comparison column in APS01")
    for species, Z, A, values in [
        ("He II", 2, 4, [(2, 30.3785), (3, 25.6317), (4, 24.3034)]),
        ("Li III", 3, 7, [(2, 13.5006), (3, 11.3921), (4, 10.7982)]),
    ]:
        for n, nm in values:
            wavelength("HLIKE_LINES", "element_holdout", species, Z, A,
                       n, 1, nm, "NIST ASD comparison column in APS01")

    # Measured hydrogenic series limits from the final IE in the canonical
    # ionisation ladder. These extend the cross-element test through Cu.
    ie_path = ROOT / "Datasets" / "nuclear" / "ionisation_energies.json"
    ionisation = json.loads(ie_path.read_text(encoding="utf-8"))
    for Z in range(2, 31):
        values = ionisation.get(str(Z), [])
        if len(values) < Z:
            continue
        energy_eV = float(values[Z - 1])
        rows.append({
            "corpus": "HLIKE_LIMIT", "split": "element_holdout",
            "species": f"Z={Z} H-like limit", "Z": Z, "A": 2 * Z,
            "n_upper": "inf", "n_lower": 1,
            "frequency_Hz": energy_eV * e_charge / h,
            "unc_frequency_Hz": "", "source": "ionisation_energies.json",
            "source_quantity": f"{energy_eV} eV",
        })

    for species, Z, A, n_u, n_l, energy in [
        ("He I", 2, 4, 2, 1, 21.218),
        ("Be I", 4, 9, 2, 2, 5.279),
        ("Na I", 11, 23, 3, 3, 2.105),
        ("Fe XXV", 26, 56, 2, 1, 6700.0),
    ]:
        rows.append({
            "corpus": "MULTI", "split": "final_holdout", "species": species,
            "Z": Z, "A": A, "n_upper": n_u, "n_lower": n_l,
            "frequency_Hz": energy * e_charge / h, "unc_frequency_Hz": "",
            "source": "NIST/APS01 measured comparison",
            "source_quantity": f"{energy} eV",
        })

    with ATOMIC_OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=ATOMIC_FIELDS)
        writer.writeheader()
        writer.writerows(rows)


def copy_radii() -> dict[tuple[int, int], float]:
    source = ROOT / "Datasets" / "nuclear" / "IAEA_ground_states_radii.csv"
    kept: list[dict[str, str]] = []
    lookup: dict[tuple[int, int], float] = {}
    with source.open(encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            try:
                Z = int(row["z"])
                N = int(row["n"])
                radius = float(row["radius"])
            except (ValueError, TypeError):
                continue
            if Z <= 0 or radius <= 0:
                continue
            A = Z + N
            kept.append({
                "Z": str(Z), "N": str(N), "A": str(A),
                "symbol": row["symbol"], "radius_fm": row["radius"],
                "unc_radius_fm": row["unc_r"], "source": "IAEA LiveChart",
            })
            lookup[(Z, A)] = radius
    with RADII_OUT.open("w", newline="", encoding="utf-8") as handle:
        fields = ["Z", "N", "A", "symbol", "radius_fm", "unc_radius_fm", "source"]
        writer = csv.DictWriter(handle, fieldnames=fields)
        writer.writeheader()
        writer.writerows(kept)
    return lookup


def fetch_gamma(nuclide: str) -> bytes:
    url = (
        "https://nds.iaea.org/relnsd/v1/data"
        f"?fields=gammas&nuclides={nuclide}"
    )
    request = urllib.request.Request(
        url,
        headers={"User-Agent": "Mozilla/5.0 APS12b research",
                 "Accept": "text/csv"},
    )
    with urllib.request.urlopen(request, timeout=60) as response:
        return response.read()


def parse_nuclide(nuclide: str) -> tuple[int, str]:
    digits = "".join(ch for ch in nuclide if ch.isdigit())
    letters = "".join(ch for ch in nuclide if ch.isalpha())
    return int(digits), letters.capitalize()


def write_gamma(radius_lookup: dict[tuple[int, int], float]) -> None:
    selected: list[dict[str, object]] = []
    for nuclide in NUCLIDES:
        raw_path = RAW / f"IAEA_gammas_{nuclide}.csv"
        payload = fetch_gamma(nuclide)
        raw_path.write_bytes(payload)
        text = payload.decode("utf-8-sig", errors="replace")
        reader = csv.DictReader(text.splitlines())
        A_expected, _ = parse_nuclide(nuclide)
        for row in reader:
            try:
                Z = int(row["z"])
                N = int(row["n"])
                energy = float(row["energy"])
                intensity = float(row["relative_intensity"])
            except (ValueError, TypeError, KeyError):
                continue
            if energy <= 0 or intensity <= 0:
                continue
            A = Z + N
            if A != A_expected:
                continue
            icc_text = row.get("tot_conv_coeff", "")
            try:
                icc = float(icc_text)
            except (ValueError, TypeError):
                icc = ""
            selected.append({
                "nuclide": nuclide, "Z": Z, "A": A,
                "start_level_keV": row.get("start_level_energy", ""),
                "end_level_keV": row.get("end_level_energy", ""),
                "gamma_energy_keV": energy,
                "relative_intensity": intensity,
                "multipolarity": row.get("multipolarity", ""),
                "tot_conv_coeff": icc,
                "gamma_fraction_from_icc":
                    1 / (1 + icc) if isinstance(icc, float) else "",
                "radius_fm_measured": radius_lookup.get((Z, A), ""),
                "source": "IAEA LiveChart ENSDF adopted gammas",
                "extraction_date": row.get("Extraction_date", ""),
            })
    fields = [
        "nuclide", "Z", "A", "start_level_keV", "end_level_keV",
        "gamma_energy_keV", "relative_intensity", "multipolarity",
        "tot_conv_coeff", "gamma_fraction_from_icc", "radius_fm_measured",
        "source", "extraction_date",
    ]
    with GAMMA_OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=fields)
        writer.writeheader()
        writer.writerows(selected)


def main() -> None:
    DATA.mkdir(exist_ok=True)
    RAW.mkdir(exist_ok=True)
    write_atomic()
    radius_lookup = copy_radii()
    write_gamma(radius_lookup)
    for path in [ATOMIC_OUT, RADII_OUT, GAMMA_OUT]:
        with path.open(encoding="utf-8") as handle:
            rows = sum(1 for _ in handle) - 1
        print(f"{path.name}: rows={rows} sha256={sha256(path)}")


if __name__ == "__main__":
    main()
