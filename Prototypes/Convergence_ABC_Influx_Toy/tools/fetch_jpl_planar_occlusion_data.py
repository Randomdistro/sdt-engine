#!/usr/bin/env python3
"""Fetch the fixed JPL Horizons state-vector inputs for the planar test."""

from __future__ import annotations

import json
from datetime import datetime, timezone
from pathlib import Path
from urllib.parse import urlencode
from urllib.request import urlopen


START_JD_TDB = 2451545.0
MERCURY_PERIOD_DAYS = 87.969
TERMINAL_JD_TDB = START_JD_TDB + MERCURY_PERIOD_DAYS
API_URL = "https://ssd.jpl.nasa.gov/api/horizons.api"
OUTPUT_DIR = Path("Datasets/solar_occlusion_2026-08-19")

BODIES = (
    ("Sun", "10", 695700.0, 1.9885e30),
    ("Mercury", "199", 2439.7, 3.3011e23),
    ("Venus", "299", 6051.8, 4.8675e24),
    ("Earth", "399", 6371.0, 5.97237e24),
    ("Mars", "499", 3389.5, 6.4171e23),
    ("Jupiter", "599", 69911.0, 1.89819e27),
    ("Saturn", "699", 58232.0, 5.6834e26),
    ("Uranus", "799", 25362.0, 8.6810e25),
    ("Neptune", "899", 24622.0, 1.02413e26),
)


def request_parameters(command: str) -> dict[str, str]:
    return {
        "format": "json",
        "COMMAND": f"'{command}'",
        "OBJ_DATA": "NO",
        "MAKE_EPHEM": "YES",
        "EPHEM_TYPE": "VECTORS",
        "CENTER": "'@0'",
        "REF_PLANE": "ECLIPTIC",
        "REF_SYSTEM": "J2000",
        "OUT_UNITS": "KM-S",
        "VEC_TABLE": "2",
        "VEC_CORR": "NONE",
        "CSV_FORMAT": "YES",
        "VEC_LABELS": "NO",
        "TIME_TYPE": "TDB",
        "TLIST": f"'{START_JD_TDB}','{TERMINAL_JD_TDB}'",
        "TLIST_TYPE": "JD",
    }


def parse_states(result: str) -> list[dict[str, object]]:
    try:
        ephemeris = result.split("$$SOE", 1)[1].split("$$EOE", 1)[0]
    except IndexError as error:
        raise ValueError("Horizons response did not contain a vector table") from error
    states: list[dict[str, object]] = []
    for row in ephemeris.splitlines():
        values = [value.strip() for value in row.split(",")]
        if len(values) < 8 or not values[0]:
            continue
        numeric = [float(value) for value in values[2:8]]
        states.append(
            {
                "jd_tdb": float(values[0]),
                "position_m": [coordinate * 1_000.0 for coordinate in numeric[:3]],
                "velocity_m_s": [coordinate * 1_000.0 for coordinate in numeric[3:]],
            }
        )
    if len(states) != 2:
        raise ValueError(f"Expected two JPL time-list states, received {len(states)}")
    return states


def fetch_body(name: str, command: str, raw_dir: Path) -> dict[str, object]:
    parameters = request_parameters(command)
    url = f"{API_URL}?{urlencode(parameters)}"
    with urlopen(url, timeout=60) as response:
        payload = json.loads(response.read().decode("utf-8"))
    if "result" not in payload:
        raise ValueError(f"Horizons response for {name} has no result field")
    raw_path = raw_dir / f"jpl_horizons_de441_{name.lower()}_j2000.json"
    raw_path.write_text(json.dumps(payload, indent=2) + "\n", encoding="utf-8")
    return {"query_url": url, "states": parse_states(payload["result"])}


def main() -> None:
    raw_dir = OUTPUT_DIR / "raw"
    raw_dir.mkdir(parents=True, exist_ok=True)
    bodies = []
    for name, command, radius_km, mass_kg in BODIES:
        downloaded = fetch_body(name, command, raw_dir)
        bodies.append(
            {
                "name": name,
                "horizons_command": command,
                "radius_km": radius_km,
                "mass_kg": mass_kg,
                "states": downloaded["states"],
                "query_url": downloaded["query_url"],
            }
        )
        print(f"Fetched {name}")
    dataset = {
        "schema": "planar-occlusion-jpl-state-series/v1",
        "source": "NASA/JPL Horizons API 1.3",
        "ephemeris": "DE441 (reported in each raw response)",
        "centre": "Solar System Barycenter (0)",
        "reference_frame": "Ecliptic of J2000.0",
        "time_scale": "TDB",
        "vector_correction": "NONE (geometric state vectors)",
        "start_jd_tdb": START_JD_TDB,
        "terminal_jd_tdb": TERMINAL_JD_TDB,
        "duration_days": MERCURY_PERIOD_DAYS,
        "retrieved_utc": datetime.now(timezone.utc).isoformat(),
        "physical_inputs": {
            "radius": {
                "description": "IAU nominal solar radius and NASA/JPL Planetary Fact Sheet mean radii",
                "source_url": "https://nssdc.gsfc.nasa.gov/planetary/factsheet/",
            },
            "mass": {
                "description": "NASA/JPL Planetary Fact Sheet masses",
                "source_url": "https://nssdc.gsfc.nasa.gov/planetary/factsheet/",
            },
        },
        "bodies": bodies,
    }
    output_path = OUTPUT_DIR / "jpl_de441_ecliptic_j2000_mercury_orbit.json"
    output_path.write_text(json.dumps(dataset, indent=2) + "\n", encoding="utf-8")
    print(f"Wrote {output_path}")


if __name__ == "__main__":
    main()
