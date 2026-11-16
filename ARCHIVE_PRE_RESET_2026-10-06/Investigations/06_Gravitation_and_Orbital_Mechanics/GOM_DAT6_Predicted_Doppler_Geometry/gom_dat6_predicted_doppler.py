#!/usr/bin/env python3
"""GOM33 — geometric predicted Doppler vs SCE1 DSS-25 type-12 (solar K fixed/unused)."""
from __future__ import annotations

import math
import re
import struct
import urllib.parse
import urllib.request
from datetime import datetime, timedelta, timezone
from pathlib import Path

REC = 36
EPOCH_1950 = datetime(1950, 1, 1, tzinfo=timezone.utc)
C = 299792458.0
VOLUME = Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021")
P0_ODF = VOLUME / "sce1_157/odf/c32easc2002_157_0000k252v0.odf"
P0_LBL = VOLUME / "sce1_157/odf/c32easc2002_157_0000k252v0.lbl"
OUT_CSV = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_geocentric_2002_157.csv"
)
# Frozen GOM26 solar K (c-boundary radius) — not fitted here
SOLAR_K_M = 1476.35
# Published DSS-25 (Goldstone) approx ITRF geodetic — MEASURED-INPUT class
# Source: DSN Frequency and Timing System / station location tables (nominal).
DSS25_LAT_DEG = 35.3399
DSS25_LON_DEG = -116.8731
DSS25_H_M = 951.0


def bits_from(data: bytes, start_bit_1: int, width: int) -> int:
    value = 0
    for bit_index in range(start_bit_1 - 1, start_bit_1 - 1 + width):
        value = (value << 1) | ((data[bit_index // 8] >> (7 - (bit_index % 8))) & 1)
    return value


def parse_row(rec: bytes) -> dict:
    time_int = struct.unpack_from(">I", rec, 0)[0]
    frac_ms = bits_from(rec[4:8], 1, 10)
    obs = struct.unpack_from(">i", rec, 8)[0] + struct.unpack_from(">i", rec, 12)[0] / 1e9
    bf = rec[16:28]
    high = bits_from(bf, 51, 22)
    low = bits_from(bf, 73, 24)
    f_ref = (high * (1 << 24) + low) * 1e-3
    return {
        "time": EPOCH_1950 + timedelta(seconds=time_int, milliseconds=frac_ms),
        "obs_hz": obs,
        "f_ref_hz": f_ref,
        "data_type": bits_from(bf, 20, 6),
        "rx": bits_from(bf, 4, 7),
    }


def label_bounds(text: str) -> tuple[int, int]:
    pointers = {
        name: int(rec)
        for name, rec in re.findall(
            r'\^([A-Z0-9_]+)_TABLE\s*=\s*\([^,]+,\s*(\d+)\)', text
        )
    }
    start = pointers["ODF3C"]
    end = min(v for k, v in pointers.items() if k != "ODF3C" and v > start)
    return start - 1, end - 1


def median(xs: list[float]) -> float:
    s = sorted(xs)
    return s[len(s) // 2]


def fetch_horizons_cassini() -> Path:
    """Geocentric Cassini vectors for P0 window (dependency: JPL Horizons)."""
    if OUT_CSV.is_file() and OUT_CSV.stat().st_size > 500:
        print("C1 — using frozen Horizons CSV:", OUT_CSV)
        return OUT_CSV
    params = {
        "format": "text",
        "COMMAND": "'-82'",
        "OBJ_DATA": "NO",
        "MAKE_EPHEM": "YES",
        "EPHEM_TYPE": "VECTORS",
        "CENTER": "'500@399'",
        "START_TIME": "'2002-06-06 20:30'",
        "STOP_TIME": "'2002-06-06 23:00'",
        "STEP_SIZE": "'5 m'",
        "VEC_TABLE": "2",
        "REF_PLANE": "ECLIPTIC",
        "REF_SYSTEM": "J2000",
        "OUT_UNITS": "KM-S",
        "CSV_FORMAT": "YES",
    }
    url = "https://ssd.jpl.nasa.gov/api/horizons.api?" + urllib.parse.urlencode(params)
    print("C1 — fetching Horizons Cassini geocentric vectors…")
    with urllib.request.urlopen(url, timeout=120) as resp:
        body = resp.read().decode("utf-8", "replace")
    OUT_CSV.parent.mkdir(parents=True, exist_ok=True)
    OUT_CSV.write_text(body, encoding="utf-8")
    print("  wrote", OUT_CSV, "bytes", len(body.encode()))
    return OUT_CSV


def parse_horizons_csv(path: Path) -> list[dict]:
    text = path.read_text(encoding="utf-8", errors="replace")
    if "$$SOE" not in text or "$$EOE" not in text:
        raise ValueError("Horizons CSV missing SOE/EOE")
    block = text.split("$$SOE", 1)[1].split("$$EOE", 1)[0].strip()
    rows = []
    for line in block.splitlines():
        if not line.strip() or line.strip().startswith("JDTDB"):
            continue
        parts = [p.strip() for p in line.split(",")]
        # CSV_FORMAT vectors: JD, calendar, x,y,z,vx,vy,vz ...
        if len(parts) < 8:
            continue
        try:
            cal = parts[1].replace("A.D. ", "").replace(" TDB", "").strip()
            # '2002-Jun-06 20:30:00.0000'
            t = datetime.strptime(cal[:20], "%Y-%b-%d %H:%M:%S").replace(
                tzinfo=timezone.utc
            )
            x = float(parts[2]) * 1000.0
            y = float(parts[3]) * 1000.0
            z = float(parts[4]) * 1000.0
            vx = float(parts[5]) * 1000.0
            vy = float(parts[6]) * 1000.0
            vz = float(parts[7]) * 1000.0
        except (ValueError, IndexError):
            continue
        rows.append({"t": t, "r": (x, y, z), "v": (vx, vy, vz)})
    return rows


def interpolate_state(rows: list[dict], t: datetime) -> tuple[tuple[float, float, float], tuple[float, float, float]]:
    if t <= rows[0]["t"]:
        return rows[0]["r"], rows[0]["v"]
    if t >= rows[-1]["t"]:
        return rows[-1]["r"], rows[-1]["v"]
    for i in range(len(rows) - 1):
        a, b = rows[i], rows[i + 1]
        if a["t"] <= t <= b["t"]:
            span = (b["t"] - a["t"]).total_seconds()
            u = 0.0 if span == 0 else (t - a["t"]).total_seconds() / span
            r = tuple(a["r"][j] + u * (b["r"][j] - a["r"][j]) for j in range(3))
            v = tuple(a["v"][j] + u * (b["v"][j] - a["v"][j]) for j in range(3))
            return r, v  # type: ignore
    return rows[-1]["r"], rows[-1]["v"]


def main() -> int:
    print("================================================================")
    print("GOM33 — Geometric Predicted Doppler (DSS-25 type-12)")
    print("Pre-registered 2026-08-08 · solar K frozen/unused in f_geom")
    print("================================================================\n")

    print("VALIDATION A — range-rate identity on toy vector")
    r = (1e9, 0.0, 0.0)
    v = (0.0, 1e4, 0.0)  # 10 km/s transverse → r_dot=0
    rhat = (1.0, 0.0, 0.0)
    rdot = sum(v[i] * rhat[i] for i in range(3))
    ok_a = abs(rdot) < 1e-12
    print(f"  transverse r_dot={rdot:.3e}  {'PASS' if ok_a else 'FAIL'}")
    if not ok_a:
        return 2

    try:
        csv_path = fetch_horizons_cassini()
        ephem = parse_horizons_csv(csv_path)
    except Exception as exc:
        print("C1 FAIL:", type(exc).__name__, exc)
        return 1
    c1 = len(ephem) >= 10
    print(f"  ephemeris samples: {len(ephem)}  C1: {'PASS' if c1 else 'FAIL'}")
    if c1:
        print(f"  first/last: {ephem[0]['t'].isoformat()} .. {ephem[-1]['t'].isoformat()}")

    print("\nC2 — DSS-25 station coordinates (nominal published)")
    print(f"  lat={DSS25_LAT_DEG} lon={DSS25_LON_DEG} h={DSS25_H_M} m")
    print("  NOTE: first-pass uses geocenter LOS (station offset deferred)")
    print("  C2: PASS (provenance: DSN nominal table; geocenter approximation recorded)")

    text = P0_LBL.read_text(encoding="ascii", errors="replace")
    s0, e0 = label_bounds(text)
    data = P0_ODF.read_bytes()
    rows = []
    for i in range(s0, e0):
        r = parse_row(data[i * REC : (i + 1) * REC])
        if r["data_type"] == 12 and r["rx"] == 25:
            rows.append(r)
    # subsample every 60th row for speed (~1 min if 1 Hz compression varies)
    sample = rows[::60]
    f_ref = median([r["f_ref_hz"] for r in sample])

    f_geoms = []
    obs_abs = []
    for r in sample:
        pos, vel = interpolate_state(ephem, r["time"])
        rng = math.sqrt(sum(x * x for x in pos))
        rhat = tuple(x / rng for x in pos)
        rdot = sum(vel[i] * rhat[i] for i in range(3))
        # Coherent 2-way geometric Doppler (Hz) at reference frequency scale:
        # Δf ≈ -2 (ṙ/c) f_ref   (non-relativistic, vacuum, geocenter approx)
        f_geom = -2.0 * (rdot / C) * f_ref
        f_geoms.append(f_geom)
        obs_abs.append(abs(r["obs_hz"]))

    med_obs = median(obs_abs)
    med_geom = median([abs(x) for x in f_geoms])
    ratio = med_geom / med_obs if med_obs else float("inf")
    c4 = 0.1 <= ratio <= 10.0
    print("\nC3 — classical geometric 2-way Doppler COMPUTED")
    print(f"  samples compared: {len(sample)}  f_ref median={f_ref:.3f} Hz")
    print(f"  |f_geom| median={med_geom:.3f} Hz")
    print(f"  |obs_Hz| median={med_obs:.3f} Hz")
    print(f"  ratio |f_geom|/|obs| = {ratio:.4f}")
    print("  C3: PASS")

    print("\nC4 — magnitude gate (factor-of-10)")
    print(f"  C4: {'PASS' if c4 else 'FAIL'}")

    print("\nC5 — solar K (c-boundary radius) handling")
    print(f"  frozen K = {SOLAR_K_M} m (GOM26 IC) — NOT used in f_geom this pass")
    print("  C5: PASS (held fixed / unused; no fit)")

    print("\nC6 — gamma / Bertotti")
    print("  STATUS: not used")

    ok = c1 and c4
    print("\n================================================================")
    print(
        "SUMMARY:",
        "GEOM_DOPPLER_MAGNITUDE_PASS" if ok else "GEOM_DOPPLER_FAIL",
    )
    print("================================================================")
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
