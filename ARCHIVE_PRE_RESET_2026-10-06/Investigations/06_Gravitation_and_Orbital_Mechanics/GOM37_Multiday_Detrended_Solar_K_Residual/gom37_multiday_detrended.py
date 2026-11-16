#!/usr/bin/env python3
"""GOM37 — multi-day DSS-25 K252; time-detrended residual vs solar-K delay-rate."""
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
R_SUN = 6.957e8
SOLAR_K_M = 1476.35

VOLUME = Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021")
K252 = [
    ("sce1_157", "c32easc2002_157_0000k252v0", 157),
    ("sce1_158", "c32easc2002_158_0000k252v0", 158),
    ("sce1_159", "c32easc2002_159_0000k252v0", 159),
    ("sce1_160", "c32easc2002_160_0000k252v0", 160),
]
DSS_CSV = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_dss25_rr_2002_157_160.csv"
)
HELIO_CAS = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_heliocentric_2002_157_160.csv"
)
HELIO_EAR = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_earth_heliocentric_2002_157_160.csv"
)


def bits_from(data: bytes, start_bit_1: int, width: int) -> int:
    value = 0
    for bit_index in range(start_bit_1 - 1, start_bit_1 - 1 + width):
        value = (value << 1) | ((data[bit_index // 8] >> (7 - (bit_index % 8))) & 1)
    return value


def median(xs: list[float]) -> float:
    s = sorted(xs)
    return s[len(s) // 2]


def corr(a: list[float], b: list[float]) -> float:
    n = len(a)
    ma = sum(a) / n
    mb = sum(b) / n
    num = sum((a[i] - ma) * (b[i] - mb) for i in range(n))
    da = math.sqrt(sum((x - ma) ** 2 for x in a))
    db = math.sqrt(sum((x - mb) ** 2 for x in b))
    return num / (da * db) if da and db else float("nan")


def stdev(xs: list[float]) -> float:
    m = sum(xs) / len(xs)
    return math.sqrt(sum((x - m) ** 2 for x in xs) / len(xs))


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


def parse_row(rec: bytes) -> dict:
    time_int = struct.unpack_from(">I", rec, 0)[0]
    frac_ms = bits_from(rec[4:8], 1, 10)
    obs = struct.unpack_from(">i", rec, 8)[0] + struct.unpack_from(">i", rec, 12)[0] / 1e9
    bf = rec[16:28]
    high = bits_from(bf, 51, 22)
    low = bits_from(bf, 73, 24)
    return {
        "time": EPOCH_1950 + timedelta(seconds=time_int, milliseconds=frac_ms),
        "obs_hz": obs,
        "f_ref_hz": (high * (1 << 24) + low) * 1e-3,
        "data_type": bits_from(bf, 20, 6),
        "rx": bits_from(bf, 4, 7),
    }


def fetch_horizons(path: Path, command: str, center: str, ephem: str, extra: dict) -> Path:
    if path.is_file() and path.stat().st_size > 800:
        print(f"  using frozen {path.name}")
        return path
    params = {
        "format": "text",
        "COMMAND": f"'{command}'",
        "OBJ_DATA": "NO",
        "MAKE_EPHEM": "YES",
        "EPHEM_TYPE": ephem,
        "CENTER": f"'{center}'",
        "START_TIME": "'2002-06-06 05:00'",
        "STOP_TIME": "'2002-06-10 08:00'",
        "STEP_SIZE": "'15 m'",
        "CSV_FORMAT": "YES",
        **extra,
    }
    url = "https://ssd.jpl.nasa.gov/api/horizons.api?" + urllib.parse.urlencode(params)
    print(f"  fetching {command} center={center} …")
    with urllib.request.urlopen(url, timeout=180) as resp:
        body = resp.read().decode("utf-8", "replace")
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(body, encoding="utf-8")
    print(f"  wrote {path} ({len(body)} chars)")
    return path


def parse_dss(path: Path) -> list[dict]:
    text = path.read_text(encoding="utf-8", errors="replace")
    if "$$SOE" not in text:
        raise ValueError("DSS RR missing SOE: " + text[:240].replace("\n", " "))
    block = text.split("$$SOE", 1)[1].split("$$EOE", 1)[0].strip()
    rows = []
    for line in block.splitlines():
        parts = [p.strip() for p in line.split(",")]
        nums = []
        for p in parts[1:]:
            try:
                nums.append(float(p))
            except ValueError:
                continue
        if len(nums) < 2:
            continue
        cal = parts[0].replace("A.D. ", "").replace("UT", "").strip()
        t = datetime.strptime(cal[:17], "%Y-%b-%d %H:%M").replace(tzinfo=timezone.utc)
        rows.append({"t": t, "rdot": nums[-1] * 1000.0})
    return rows


def parse_vectors(path: Path) -> list[dict]:
    text = path.read_text(encoding="utf-8", errors="replace")
    if "$$SOE" not in text:
        raise ValueError("vectors missing SOE: " + text[:240].replace("\n", " "))
    block = text.split("$$SOE", 1)[1].split("$$EOE", 1)[0].strip()
    rows = []
    for line in block.splitlines():
        parts = [p.strip() for p in line.split(",")]
        if len(parts) < 8:
            continue
        try:
            cal = parts[1].replace("A.D. ", "").replace(" TDB", "").strip()
            t = datetime.strptime(cal[:20], "%Y-%b-%d %H:%M:%S").replace(
                tzinfo=timezone.utc
            )
            x = float(parts[2]) * 1000.0
            y = float(parts[3]) * 1000.0
            z = float(parts[4]) * 1000.0
        except (ValueError, IndexError):
            continue
        rows.append({"t": t, "r": (x, y, z)})
    return rows


def interp_rdot(rows: list[dict], t: datetime) -> float:
    if t <= rows[0]["t"]:
        return rows[0]["rdot"]
    if t >= rows[-1]["t"]:
        return rows[-1]["rdot"]
    for i in range(len(rows) - 1):
        a, b = rows[i], rows[i + 1]
        if a["t"] <= t <= b["t"]:
            span = (b["t"] - a["t"]).total_seconds()
            u = 0.0 if span == 0 else (t - a["t"]).total_seconds() / span
            return a["rdot"] + u * (b["rdot"] - a["rdot"])
    return rows[-1]["rdot"]


def interp_vec(rows: list[dict], t: datetime) -> tuple[float, float, float]:
    if t <= rows[0]["t"]:
        return rows[0]["r"]
    if t >= rows[-1]["t"]:
        return rows[-1]["r"]
    for i in range(len(rows) - 1):
        a, b = rows[i], rows[i + 1]
        if a["t"] <= t <= b["t"]:
            span = (b["t"] - a["t"]).total_seconds()
            u = 0.0 if span == 0 else (t - a["t"]).total_seconds() / span
            return tuple(a["r"][j] + u * (b["r"][j] - a["r"][j]) for j in range(3))  # type: ignore
    return rows[-1]["r"]


def impact_delay(r_e, r_c, K: float) -> tuple[float, float]:
    dx = r_c[0] - r_e[0]
    dy = r_c[1] - r_e[1]
    dz = r_c[2] - r_e[2]
    L = math.sqrt(dx * dx + dy * dy + dz * dz)
    n = (dx / L, dy / L, dz / L)
    cx = r_e[1] * n[2] - r_e[2] * n[1]
    cy = r_e[2] * n[0] - r_e[0] * n[2]
    cz = r_e[0] * n[1] - r_e[1] * n[0]
    b = max(math.sqrt(cx * cx + cy * cy + cz * cz), 1.0)
    r1 = math.sqrt(sum(x * x for x in r_e))
    r2 = math.sqrt(sum(x * x for x in r_c))
    dt = (2.0 * K / C) * math.log(4.0 * r1 * r2 / (b * b))
    return b, dt


def linfit(tsec: list[float], y: list[float]) -> tuple[float, float]:
    n = len(tsec)
    mt = sum(tsec) / n
    my = sum(y) / n
    num = sum((tsec[i] - mt) * (y[i] - my) for i in range(n))
    den = sum((t - mt) ** 2 for t in tsec)
    beta = num / den if den else 0.0
    alpha = my - beta * mt
    return alpha, beta


def main() -> int:
    print("================================================================")
    print("GOM37 — Multi-Day Time-Detrended Residual vs Solar K")
    print("Pre-registered 2026-08-08 · K frozen · claim investigation")
    print("================================================================\n")

    print("C1 — K252 inventory")
    files = []
    for day, stem, doy in K252:
        odf = VOLUME / day / "odf" / f"{stem}.odf"
        lbl = VOLUME / day / "odf" / f"{stem}.lbl"
        ok = odf.is_file() and lbl.is_file()
        print(f"  [{'HAVE' if ok else 'MISS'}] {stem}")
        if ok:
            files.append((odf, lbl, doy))
    c1 = len(files) == 4
    print(f"  C1: {'PASS' if c1 else 'FAIL'}")
    if not c1:
        return 1

    print("\nEphemeris")
    try:
        fetch_horizons(
            DSS_CSV,
            "-82",
            "DSS-25",
            "OBSERVER",
            {"QUANTITIES": "'20'", "CAL_FORMAT": "CAL"},
        )
        fetch_horizons(
            HELIO_CAS,
            "-82",
            "500@10",
            "VECTORS",
            {
                "VEC_TABLE": "2",
                "REF_PLANE": "ECLIPTIC",
                "REF_SYSTEM": "J2000",
                "OUT_UNITS": "KM-S",
            },
        )
        fetch_horizons(
            HELIO_EAR,
            "399",
            "500@10",
            "VECTORS",
            {
                "VEC_TABLE": "2",
                "REF_PLANE": "ECLIPTIC",
                "REF_SYSTEM": "J2000",
                "OUT_UNITS": "KM-S",
            },
        )
        dss = parse_dss(DSS_CSV)
        cas = parse_vectors(HELIO_CAS)
        ear = parse_vectors(HELIO_EAR)
    except Exception as exc:
        print("  FAIL", type(exc).__name__, str(exc)[:200])
        return 1
    print(f"  DSS RR n={len(dss)}  Cas n={len(cas)}  Ear n={len(ear)}")

    # Load ODF samples (every 60th type-12 RX25 row)
    series = []
    for odf, lbl, doy in files:
        text = lbl.read_text(encoding="ascii", errors="replace")
        a, b = label_bounds(text)
        blob = odf.read_bytes()
        rows = []
        for i in range(a, b):
            r = parse_row(blob[i * REC : (i + 1) * REC])
            if r["data_type"] == 12 and r["rx"] == 25:
                rows.append(r)
        for r in rows[::60]:
            rdot = interp_rdot(dss, r["time"])
            f_geom = -2.0 * (rdot / C) * r["f_ref_hz"]
            re = interp_vec(ear, r["time"])
            rc = interp_vec(cas, r["time"])
            b_m, delay = impact_delay(re, rc, SOLAR_K_M)
            series.append(
                {
                    "t": r["time"],
                    "doy": doy,
                    "obs": r["obs_hz"],
                    "f_geom": f_geom,
                    "f_ref": r["f_ref_hz"],
                    "b": b_m,
                    "delay": delay,
                }
            )

    series.sort(key=lambda x: x["t"])
    # d(delay)/dt via neighbors
    for i in range(len(series)):
        if 0 < i < len(series) - 1:
            dt = (series[i + 1]["t"] - series[i - 1]["t"]).total_seconds()
            dtdt = (series[i + 1]["delay"] - series[i - 1]["delay"]) / dt if dt else 0.0
        elif i == 0:
            dt = (series[1]["t"] - series[0]["t"]).total_seconds()
            dtdt = (series[1]["delay"] - series[0]["delay"]) / dt if dt else 0.0
        else:
            dt = (series[i]["t"] - series[i - 1]["t"]).total_seconds()
            dtdt = (series[i]["delay"] - series[i - 1]["delay"]) / dt if dt else 0.0
        series[i]["dtdt"] = dtdt
        series[i]["dfk"] = series[i]["f_ref"] * dtdt

    train = [x for x in series if x["doy"] == 157]
    test = [x for x in series if x["doy"] in (158, 159, 160)]
    print(f"\nSamples: total={len(series)} train157={len(train)} test158-160={len(test)}")
    if len(train) < 10 or len(test) < 10:
        print("C1 FAIL: insufficient samples")
        return 1

    # C2 scale + detrend
    s = median([x["obs"] / x["f_geom"] for x in train if abs(x["f_geom"]) > 1])
    t0 = train[0]["t"]
    r_train = [x["obs"] - s * x["f_geom"] for x in train]
    t_train = [(x["t"] - t0).total_seconds() for x in train]
    alpha, beta = linfit(t_train, r_train)
    print("\nC2 — CALIBRATED scale + train-only linear detrend")
    print(f"  s = {s:.6f}")
    print(f"  alpha = {alpha:.6f} Hz")
    print(f"  beta  = {beta:.6e} Hz/s")
    print("  C2: PASS")

    r_test = [x["obs"] - s * x["f_geom"] for x in test]
    t_test = [(x["t"] - t0).total_seconds() for x in test]
    r_perp = [r_test[i] - (alpha + beta * t_test[i]) for i in range(len(test))]
    dtdt = [x["dtdt"] for x in test]
    dfk = [x["dfk"] for x in test]
    b_rs = [x["b"] / R_SUN for x in test]

    print("\nC3 — solar geometry on test")
    print(f"  K = {SOLAR_K_M} m")
    print(f"  b min/max = {min(b_rs):.3f} / {max(b_rs):.3f} R_Sun")
    print(f"  delay median = {median([x['delay'] for x in test]):.6e} s")
    print(f"  f*d(delay)/dt median | | = {median([abs(x) for x in dfk]):.6e} Hz")
    print("  C3: PASS")

    c_dtdt = corr(r_perp, dtdt)
    c_time = corr(r_perp, t_test)
    c_invb = corr(r_perp, [1.0 / x["b"] for x in test])
    amp_ratio = stdev(r_perp) / max(median([abs(x) for x in dfk]), 1e-30)

    print("\nC4-C7 — test detrended residual")
    print(f"  stdev(r_perp) = {stdev(r_perp):.3f} Hz")
    print(f"  amp_ratio = stdev(r_perp)/med|f dtdt| = {amp_ratio:.3e}")
    print(f"  corr(r_perp, d(delay)/dt) = {c_dtdt:.6f}")
    print(f"  corr(r_perp, 1/b)         = {c_invb:.6f}")
    print(f"  corr(r_perp, time)        = {c_time:.6f}  (delete-test)")

    confounded = abs(c_time) >= abs(c_dtdt) - 0.05
    if abs(c_dtdt) >= 0.5 and amp_ratio < 100 and not confounded:
        label = "SOLAR_K_RESIDUAL_SIGNAL"
    elif abs(c_dtdt) < 0.2 and not confounded:
        label = "NO_SOLAR_K_RESIDUAL_SIGNAL"
    else:
        label = "UNADJUDICATED"
    if confounded:
        print("  delete-test: CONFOUNDED with time -> force UNADJUDICATED")
        label = "UNADJUDICATED"
    if amp_ratio >= 100:
        print("  amplitude gate: ratio >= 100 -> UNADJUDICATED")
        label = "UNADJUDICATED"

    print(f"\nC8 — K not fitted — PASS")
    print("\n================================================================")
    print("SUMMARY:", label)
    print("================================================================")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
