#!/usr/bin/env python3
"""Freeze APS12a observed inputs only. Contains no prediction formula."""
from __future__ import annotations

import csv
import hashlib
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
IE_PATH = ROOT / "Datasets" / "nuclear" / "ionisation_energies.json"
OUT = HERE / "aps12a_holdouts.csv"

FIELDS = [
    "corpus", "species", "Z", "A", "stage", "transition", "quantity",
    "value", "unit", "n_low", "n_high", "source",
]


def main() -> None:
    rows: list[dict[str, object]] = []

    def add(**values: object) -> None:
        rows.append(values)

    # APS01 NIST comparison columns.
    for n, value in [(2, 121.5670), (3, 102.5722), (4, 97.2537),
                     (5, 94.9743), (6, 93.7803)]:
        add(corpus="EXC_H", species="H I", Z=1, A=1, stage="I",
            transition=f"{n}->1", quantity="lambda_nm", value=value,
            unit="nm", n_low=1, n_high=n, source="APS01 NIST column")
    for n, value in [(3, 656.4614), (4, 486.2712), (5, 434.1692),
                     (6, 410.2892), (7, 397.1233)]:
        add(corpus="EXC_H", species="H I", Z=1, A=1, stage="I",
            transition=f"{n}->2", quantity="lambda_nm", value=value,
            unit="nm", n_low=2, n_high=n, source="APS01 NIST column")
    for n, value in [(4, 1875.6200), (5, 1282.1700),
                     (6, 1094.1200), (7, 1005.2200)]:
        add(corpus="EXC_H", species="H I", Z=1, A=1, stage="I",
            transition=f"{n}->3", quantity="lambda_nm", value=value,
            unit="nm", n_low=3, n_high=n, source="APS01 NIST column")
    for species, Z, A, values in [
        ("He II", 2, 4, [(2, 30.3785), (3, 25.6317), (4, 24.3034)]),
        ("Li III", 3, 7, [(2, 13.5006), (3, 11.3921), (4, 10.7982)]),
    ]:
        for n, value in values:
            add(corpus="EXC_LIGHT", species=species, Z=Z, A=A,
                stage="H-like", transition=f"{n}->1",
                quantity="lambda_nm", value=value, unit="nm", n_low=1,
                n_high=n, source="APS01 NIST column")

    # Independent high-Z and multi-electron measured values.
    add(corpus="EXC_FE", species="Fe XXVI", Z=26, A=56, stage="XXVI",
        transition="2->1 centroid", quantity="E_eV", value=6962.5,
        unit="eV", n_low=1, n_high=2,
        source="Fe XXVI 6.973/6.952 keV unresolved centroid")
    for species, Z, A, transition, value, nlo, nhi in [
        ("He I", 2, 4, "1s2-1s2p", 21.218, 1, 2),
        ("Be I", 4, 9, "2s2-2s2p", 5.279, 2, 2),
        ("Na I", 11, 23, "3s-3p", 2.105, 3, 3),
        ("Fe XXV", 26, 56, "1s2-1s2p w", 6700.0, 1, 2),
    ]:
        add(corpus="MULTI", species=species, Z=Z, A=A, stage="measured",
            transition=transition, quantity="E_eV", value=value, unit="eV",
            n_low=nlo, n_high=nhi, source="APS01/NIST standard")

    # Hydrogen-deuterium Ly-alpha observed wavelengths.
    add(corpus="ISO_MASS", species="H I", Z=1, A=1, stage="I",
        transition="2->1", quantity="lambda_nm", value=121.5670, unit="nm",
        n_low=1, n_high=2, source="APS01 NIST column")
    add(corpus="ISO_MASS", species="D I", Z=1, A=2, stage="I",
        transition="2->1", quantity="lambda_nm", value=121.5339, unit="nm",
        n_low=1, n_high=2, source="NIST deuterium Ly-alpha reference")

    # APS07 measured sequential Ca charge-radius differences.
    for a, ap, dr2 in [(40, 42, 0.213), (42, 44, 0.069),
                       (44, 46, -0.158), (46, 48, -0.127)]:
        add(corpus="ISO_CA", species=f"Ca-{a}->{ap}", Z=20, A=a,
            stage="Ca+", transition=f"{a}->{ap}", quantity="delta_r2_fm2",
            value=dr2, unit="fm2", n_low=4, n_high="",
            source="APS07 measured-data ledger")

    with IE_PATH.open(encoding="utf-8") as handle:
        ionisation = json.load(handle)
    for Z in range(2, 31):
        values = ionisation.get(str(Z), [])
        value = values[Z - 1] if len(values) >= Z else ""
        add(corpus="ION_LAST", species=f"Z={Z}", Z=Z, A=2 * Z,
            stage=Z, transition=f"IE_{Z}", quantity="IE_eV", value=value,
            unit="eV", n_low=1, n_high="", source="ionisation_energies.json")
    for Z in [2, 4, 6, 8, 10, 12, 18, 20, 26]:
        values = ionisation[str(Z)]
        for k in range(1, Z + 1):
            value = values[k - 1] if len(values) >= k else ""
            add(corpus="ION_FULL", species=f"Z={Z}", Z=Z, A=2 * Z,
                stage=k, transition=f"IE_{k}", quantity="IE_eV",
                value=value, unit="eV", n_low="", n_high="",
                source="ionisation_energies.json")

    with OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=FIELDS)
        writer.writeheader()
        writer.writerows({field: row.get(field, "") for field in FIELDS}
                         for row in rows)
    digest = hashlib.sha256(OUT.read_bytes()).hexdigest()
    print(f"rows={len(rows)}")
    print(f"sha256={digest}")


if __name__ == "__main__":
    main()
