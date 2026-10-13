#!/usr/bin/env python3
"""Build exact Sun/Earth proton, neutron and Law-IV displacement ledgers."""

from __future__ import annotations

from decimal import Decimal, ROUND_FLOOR, ROUND_HALF_EVEN, getcontext
import hashlib
import json
import math
from pathlib import Path


ROOT = Path(__file__).resolve().parent
INPUT = ROOT / "datasets" / "displacement-composition-inputs.json"
OUTPUT = ROOT / "datasets" / "displacement-ledgers.json"

getcontext().prec = 90


def dec(value: object) -> Decimal:
    return Decimal(str(value))


def canonical_sha256(value: object) -> str:
    text = json.dumps(value, sort_keys=True, separators=(",", ":"), ensure_ascii=False)
    return hashlib.sha256(text.encode("utf-8")).hexdigest()


def allocate_integer(total: int, fractions: dict[str, object]) -> dict[str, int]:
    exact = {key: Decimal(total) * dec(value) for key, value in fractions.items()}
    allocated = {
        key: int(value.to_integral_value(rounding=ROUND_FLOOR))
        for key, value in exact.items()
    }
    missing = total - sum(allocated.values())
    order = sorted(
        exact,
        key=lambda key: (exact[key] - allocated[key], -int(key)),
        reverse=True,
    )
    for key in order[:missing]:
        allocated[key] += 1
    if sum(allocated.values()) != total:
        raise RuntimeError("isotope integer allocation did not close")
    return allocated


def scientific(value: Decimal) -> str:
    return f"{value:.17E}"


def main() -> None:
    source = json.loads(INPUT.read_text(encoding="utf-8"))
    constants = source["constants"]
    u = dec(constants["atomic_mass_constant_kg"])
    c = dec(constants["speed_of_light_m_s"])
    l_planck = dec(constants["planck_length_m"])
    r_cmb = dec(constants["cmb_boundary_radius_m"])
    temperature = dec(constants["cmb_temperature_k"])
    radiation_constant = dec(constants["radiation_constant_j_m3_k4"])
    proton_mass = dec(constants["proton_mass_kg"])
    neutron_mass = dec(constants["neutron_mass_kg"])
    u_cmb = radiation_constant * temperature**4
    p_conv = (r_cmb / l_planck) * u_cmb
    proton_displacement = Decimal(3) * proton_mass * c**2 / p_conv
    neutron_displacement = Decimal(3) * neutron_mass * c**2 / p_conv

    body_ledgers: list[dict[str, object]] = []
    for body in source["bodies"]:
        radius = dec(body["radius_m"])
        body_volume = dec(4) * dec(math.pi) * radius**3 / dec(3)
        proton_count = 0
        neutron_count = 0
        element_rows: list[dict[str, object]] = []
        volume_coverage = Decimal(0)
        represented_mass_fraction = Decimal(0)

        for material in body["materials"]:
            volume_fraction = dec(material["volume_fraction"])
            volume_coverage += volume_fraction
            material_volume = body_volume * volume_fraction
            material_mass = material_volume * dec(body["bulk_density_kg_m3"])
            material_coverage = sum(
                (dec(value) for value in material["elements_by_mass"].values()),
                Decimal(0),
            )
            represented_mass_fraction += volume_fraction * material_coverage
            for symbol, mass_fraction_raw in material["elements_by_mass"].items():
                isotope = source["isotopes"][symbol]
                z = int(isotope["Z"])
                fractions = isotope["fractions"]
                fraction_sum = sum((dec(value) for value in fractions.values()), Decimal(0))
                if fraction_sum != Decimal(1):
                    raise RuntimeError(f"{symbol} isotope fractions do not close")
                mean_a = sum(
                    (dec(a) * dec(fraction) for a, fraction in fractions.items()),
                    Decimal(0),
                )
                exact_atoms = (
                    material_mass * dec(mass_fraction_raw) / (mean_a * u)
                )
                atom_count = int(
                    exact_atoms.to_integral_value(rounding=ROUND_HALF_EVEN)
                )
                isotope_counts = allocate_integer(atom_count, fractions)
                element_protons = atom_count * z
                element_neutrons = sum(
                    count * (int(a) - z) for a, count in isotope_counts.items()
                )
                proton_count += element_protons
                neutron_count += element_neutrons
                effective_atomic_volume = material_volume / Decimal(atom_count)
                element_rows.append(
                    {
                        "material": material["name"],
                        "symbol": symbol,
                        "Z": z,
                        "material_volume_fraction": float(volume_fraction),
                        "element_mass_fraction": float(dec(mass_fraction_raw)),
                        "effective_atomic_volume_m3": scientific(effective_atomic_volume),
                        "atom_count": str(atom_count),
                        "isotope_counts": {
                            a: str(count) for a, count in isotope_counts.items()
                        },
                        "proton_count": str(element_protons),
                        "neutron_count": str(element_neutrons),
                    }
                )

        baryon_count = proton_count + neutron_count
        weighted_burden = 1836 * proton_count + 1838 * neutron_count
        proton_volume = Decimal(proton_count) * proton_displacement
        neutron_volume = Decimal(neutron_count) * neutron_displacement
        total_displacement = proton_volume + neutron_volume
        geometric_fill = total_displacement / body_volume
        if volume_coverage < dec("0.98") or represented_mass_fraction < dec("0.98"):
            raise RuntimeError(f"{body['id']} composition coverage is below 98%")
        body_ledgers.append(
            {
                "id": body["id"],
                "classification": "COMPUTED from OBSERVED inputs",
                "body_volume_m3": scientific(body_volume),
                "material_volume_coverage": float(volume_coverage),
                "represented_atomic_mass_coverage": float(represented_mass_fraction),
                "residual_atomic_mass_fraction": float(
                    max(Decimal(0), Decimal(1) - represented_mass_fraction)
                ),
                "declared_relative_uncertainty": body[
                    "declared_relative_uncertainty"
                ],
                "proton_count": str(proton_count),
                "neutron_count": str(neutron_count),
                "baryon_count": str(baryon_count),
                "weighted_trefoil_burden": str(weighted_burden),
                "law_IV_displacement": {
                    "proton_trefoil_volume_m3": scientific(proton_volume),
                    "neutron_trefoil_volume_m3": scientific(neutron_volume),
                    "rest_volume_m3": scientific(total_displacement),
                    "rest_to_geometric_volume_ratio": scientific(geometric_fill),
                    "classification": "COMPUTED",
                },
                "elements": element_rows,
                "provenance": body["provenance"],
            }
        )

    by_id = {row["id"]: row for row in body_ledgers}
    earth_burden = Decimal(by_id["Earth"]["weighted_trefoil_burden"])
    sun_burden = Decimal(by_id["Sun"]["weighted_trefoil_burden"])
    ratio = earth_burden / sun_burden
    relative_uncertainty = (
        dec(next(row for row in source["bodies"] if row["id"] == "Earth")[
            "declared_relative_uncertainty"
        ])
        + dec(next(row for row in source["bodies"] if row["id"] == "Sun")[
            "declared_relative_uncertainty"
        ])
    )
    output = {
        "ledger_version": "1.0.0",
        "source_sha256": canonical_sha256(source),
        "classification": source["classification"],
        "method": source["method"],
        "constants": {
            "law_I_P_conv_pa": scientific(p_conv),
            "proton_trefoil_volume_each_m3": scientific(proton_displacement),
            "neutron_trefoil_volume_each_m3": scientific(neutron_displacement),
            "source": "Engine/include/sdt/laws.hpp values and law_IV::V_disp_from_mass",
        },
        "bodies": body_ledgers,
        "earth_sun": {
            "K_SDT": scientific(ratio),
            "relative_uncertainty": float(relative_uncertainty),
            "lower": scientific(ratio * (Decimal(1) - relative_uncertainty)),
            "upper": scientific(ratio * (Decimal(1) + relative_uncertainty)),
            "formula": "(1836*Np_Earth+1838*Nn_Earth)/(1836*Np_Sun+1838*Nn_Sun)",
            "classification": "COMPUTED",
        },
    }
    OUTPUT.write_text(json.dumps(output, indent=2) + "\n", encoding="utf-8")
    print(
        json.dumps(
            {
                "output": str(OUTPUT.relative_to(ROOT)),
                "K_SDT": output["earth_sun"]["K_SDT"],
                "sun_coverage": by_id["Sun"]["represented_atomic_mass_coverage"],
                "earth_coverage": by_id["Earth"]["represented_atomic_mass_coverage"],
                "passed": True,
            },
            indent=2,
        )
    )


if __name__ == "__main__":
    main()
