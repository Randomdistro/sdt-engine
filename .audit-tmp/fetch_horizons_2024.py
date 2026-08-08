"""Fetch EMB–Sun Horizons vectors for 2024 with quoted STEP_SIZE variants."""
from __future__ import annotations

import hashlib
import pathlib
import urllib.parse
import urllib.request

BASE = {
    "format": "text",
    "COMMAND": "3",
    "OBJ_DATA": "YES",
    "MAKE_EPHEM": "YES",
    "EPHEM_TYPE": "VECTORS",
    "CENTER": "500@10",
    "START_TIME": "2024-01-01",
    "STOP_TIME": "2025-01-01",
    "VEC_TABLE": "2",
    "OUT_UNITS": "KM-S",
    "CSV_FORMAT": "YES",
    "REF_PLANE": "ECLIPTIC",
}
VARIANTS = [
    {"STEP_SIZE": "'14 days'"},
    {"STEP_SIZE": "'20160 minutes'"},
    {"STEP_SIZE": "14d"},
    {"STEP_SIZE": "'1 mon'"},
]
SCIENCE = pathlib.Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_emb_sun_vectors_2024.csv"
)
ERROR = pathlib.Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_API_ERROR_2024_latest.txt"
)


def main() -> int:
    for variant in VARIANTS:
        query = dict(BASE)
        query.update(variant)
        url = "https://ssd.jpl.nasa.gov/api/horizons.api?" + urllib.parse.urlencode(query)
        print("TRY", variant, flush=True)
        data = urllib.request.urlopen(url, timeout=90).read()
        text = data.decode("utf-8", "replace")
        center = next(
            (
                line.strip()
                for line in text.splitlines()
                if "Center body" in line or "INPUT ERROR" in line
            ),
            "?",
        )
        print(" ", len(data), "B |", center[:120], flush=True)
        if "Sun (10)" in text and "$$SOE" in text and len(data) > 1000:
            SCIENCE.write_bytes(data)
            print("SAVED", SCIENCE, hashlib.sha256(data).hexdigest())
            return 0
    ERROR.write_bytes(data)
    print("FAILED; last body written to", ERROR)
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
