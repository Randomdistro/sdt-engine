"""Fetch processed ephemeris data (JPL Horizons, DE441) for Chapter 36.

Writes raw responses and parsed tables to Textbook/data/horizons/. Observational data only: these are
processed ephemeris vectors (fits of DE441 to ranging, VLBI and optical data), labelled as such in the book.
No value is typed in from memory: the gravitational parameters are read from the Horizons object data.
Run: python Textbook/tools/fetch_horizons.py
"""
import csv
import re
import sys
import urllib.parse
import urllib.request
from pathlib import Path

OUT = Path(__file__).resolve().parent.parent / "data" / "horizons"
OUT.mkdir(parents=True, exist_ok=True)
API = "https://ssd.jpl.nasa.gov/api/horizons.api"


def get(params):
    q = urllib.parse.urlencode(params)
    with urllib.request.urlopen(API + "?" + q, timeout=60) as r:
        return r.read().decode("utf-8", "replace")


def vectors(body):
    p = {
        "format": "text", "COMMAND": f"'{body}'", "OBJ_DATA": "'NO'", "MAKE_EPHEM": "'YES'",
        "EPHEM_TYPE": "'VECTORS'", "CENTER": "'500@0'", "START_TIME": "'2000-01-01 12:00'",
        "STOP_TIME": "'2020-01-01 12:00'", "STEP_SIZE": "'10 d'", "REF_PLANE": "'ECLIPTIC'",
        "REF_SYSTEM": "'ICRF'", "OUT_UNITS": "'AU-D'", "VEC_TABLE": "'2'", "TIME_TYPE": "'TDB'",
    }
    return get(p)


def parse_vectors(text):
    block = text.split("$$SOE")[1].split("$$EOE")[0]
    rows = []
    lines = [l for l in block.strip().splitlines() if l.strip()]
    for i in range(0, len(lines), 3):
        jd = float(lines[i].split("=")[0])
        nums = [float(x) for x in re.findall(r"[-+]?\d\.\d+E[-+]\d+", lines[i + 1] + " " + lines[i + 2])]
        rows.append([jd] + nums)
    return rows


def gm(body):
    t = get({"format": "text", "COMMAND": f"'{body}'", "OBJ_DATA": "'YES'", "MAKE_EPHEM": "'NO'"})
    m = re.search(r"GM[^=\n]*km\^3/s\^2\)?\s*=\s*([0-9.]+(?:E[-+]?\d+)?)", t)
    if not m:
        m = re.search(r"GM, km\^3/s\^2\s*=\s*([0-9.]+)", t)
    return float(m.group(1)) if m else None, t


def main():
    bodies = {"Sun": "10", "Mercury": "1", "Venus": "2", "EMB": "3", "Mars": "4", "Jupiter": "5", "Saturn": "6", "Uranus": "7", "Neptune": "8"}
    for name, cid in bodies.items():
        txt = vectors(cid)
        (OUT / f"vec_{name}.txt").write_text(txt, encoding="utf-8")
        rows = parse_vectors(txt)
        with open(OUT / f"vec_{name}.csv", "w", newline="") as f:
            w = csv.writer(f)
            w.writerow(["JDTDB", "X_AU", "Y_AU", "Z_AU", "VX_AUd", "VY_AUd", "VZ_AUd"])
            w.writerows(rows)
        print(name, cid, len(rows), "rows", file=sys.stderr)
    gmbodies = {"Sun": "10", "Mercury": "199", "Venus": "299", "Earth": "399", "Moon": "301", "Mars": "499", "Jupiter": "599", "Saturn": "699", "Uranus": "799", "Neptune": "899"}
    with open(OUT / "gm.csv", "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["body", "GM_km3_s2"])
        for name, cid in gmbodies.items():
            v, t = gm(cid)
            (OUT / f"obj_{name}.txt").write_text(t, encoding="utf-8")
            w.writerow([name, v])
            print(name, v, file=sys.stderr)


if __name__ == "__main__":
    main()
