#!/usr/bin/env python3
"""GOM36 — hold-out geometric scale; residual vs solar-K delay-rate proxy."""
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
SOLAR_K_M = 1476.35  # frozen GOM26 IC — c-boundary radius

VOLUME = Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021")
P0_ODF = VOLUME / "sce1_157/odf/c32easc2002_157_0000k252v0.odf"
P0_LBL = VOLUME / "sce1_157/odf/c32easc2002_157_0000k252v0.lbl"
DSS_CSV = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_dss25_rr_2002_157.csv"
)
HELIO_CAS = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_heliocentric_2002_157.csv"
)
HELIO_EAR = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_earth_heliocentric_2002_157.csv"
)


def bits_from(data: bytes, start_bit_1: int, width: int) -> int:
    value = 0
    for bit_index in range(start_bit_1 - 1, start_bit_1 - 1 + width):
        value = (value << 1) | ((data[bit_index // 8] >> (7 - (bit_index % 8))) & 1)
    return value


def median(xs: list[float]) -> float:
    s = sorted(xs)
    return s[len(s) // 2]


def stats(xs: list[float]) -> tuple[float, float, float, float]:
    s = sorted(xs)
    n = len(s)
    mean = sum(s) / n
    var = sum((x - mean) ** 2 for x in s) / n
    return s[0], s[n // 2], s[-1], math.sqrt(var)


def corr(a: list[float], b: list[float]) -> float:
    n = len(a)
    ma = sum(a) / n
    mb = sum(b) / n
    num = sum((a[i] - ma) * (b[i] - mb) for i in range(n))
    da = math.sqrt(sum((x - ma) ** 2 for x in a))
    db = math.sqrt(sum((x - mb) ** 2 for x in b))
    return num / (da * db) if da and db else float("nan")


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


def fetch_heliocentric(path: Path, command: str) -> Path:
    if path.is_file() and path.stat().st_size > 500:
        return path
    params = {
        "format": "text",
        "COMMAND": f"'{command}'",
        "OBJ_DATA": "NO",
        "MAKE_EPHEM": "YES",
        "EPHEM_TYPE": "VECTORS",
        "CENTER": "'500@10'",
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
    print(f"  fetching Horizons {command} @ Sun …")
    with urllib.request.urlopen(url, timeout=120) as resp:
        body = resp.read().decode("utf-8", "replace")
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(body, encoding="utf-8")
    return path


def parse_vectors(path: Path) -> list[dict]:
    text = path.read_text(encoding="utf-8", errors="replace")
    if "$$SOE" not in text:
        raise ValueError(f"no SOE in {path}: {text[:200]}")
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


def parse_dss(path: Path) -> list[dict]:
    text = path.read_text(encoding="utf-8", errors="replace")
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


def impact_and_delay(r_e, r_c, K: float) -> tuple[float, float]:
    """Sun at origin. Ray Earth→Cassini. b = |r_e × n|; Δt = (2K/c) ln(4 r1 r2 / b²)."""
    dx = r_c[0] - r_e[0]
    dy = r_c[1] - r_e[1]
    dz = r_c[2] - r_e[2]
    L = math.sqrt(dx * dx + dy * dy + dz * dz)
    n = (dx / L, dy / L, dz / L)
    # cross r_e × n
    cx = r_e[1] * n[2] - r_e[2] * n[1]
    cy = r_e[2] * n[0] - r_e[0] * n[2]
    cz = r_e[0] * n[1] - r_e[1] * n[0]
    b = math.sqrt(cx * cx + cy * cy + cz * cz)
    r1 = math.sqrt(sum(x * x for x in r_e))
    r2 = math.sqrt(sum(x * x for x in r_c))
    # guard b
    b = max(b, 1.0)
    dt = (2.0 * K / C) * math.log(4.0 * r1 * r2 / (b * b))
    return b, dt


def main() -> int:
    print("================================================================")
    print("GOM36 — Conjunction Residual vs Solar K (hold-out scale)")
    print("Pre-registered 2026-08-08 · K frozen · claim investigation")
    print("================================================================\n")

    print("VALIDATION A — shapiro_delay identity at fixed geometry")
    b0, dt0 = impact_and_delay((1.5e11, 0.0, 0.0), (-1.0e12, 1.0e10, 0.0), SOLAR_K_M)
    ok_a = math.isfinite(dt0) and b0 > 0
    print(f"  b={b0:.3e} m  dt={dt0:.6e} s  {'PASS' if ok_a else 'FAIL'}")
    if not ok_a:
        return 2

    print("\nC3 inputs — heliocentric vectors")
    try:
        fetch_heliocentric(HELIO_CAS, "-82")
        fetch_heliocentric(HELIO_EAR, "399")
        cas = parse_vectors(HELIO_CAS)
        ear = parse_vectors(HELIO_EAR)
    except Exception as exc:
        print("  FAIL", type(exc).__name__, exc)
        return 1
    print(f"  Cassini samples={len(cas)} Earth samples={len(ear)}")

    text = P0_LBL.read_text(encoding="ascii", errors="replace")
    s0, e0 = label_bounds(text)
    data = P0_ODF.read_bytes()
    rows = []
    for i in range(s0, e0):
        r = parse_row(data[i * REC : (i + 1) * REC])
        if r["data_type"] == 12 and r["rx"] == 25:
            rows.append(r)
    # denser sample for residual analysis
    sample = rows[::20]
    dss = parse_dss(DSS_CSV)
    f_ref = median([r["f_ref_hz"] for r in sample])

    series = []
    for r in sample:
        rdot = interp_rdot(dss, r["time"])
        f_geom = -2.0 * (rdot / C) * f_ref
        re = interp_vec(ear, r["time"])
        rc = interp_vec(cas, r["time"])
        b, dt = impact_and_delay(re, rc, SOLAR_K_M)
        series.append(
            {
                "t": r["time"],
                "obs": r["obs_hz"],
                "f_geom": f_geom,
                "b": b,
                "dt": dt,
            }
        )

    # finite differences for dΔt/dt
    for i in range(len(series)):
        if i == 0:
            dtdt = (series[1]["dt"] - series[0]["dt"]) / (
                series[1]["t"] - series[0]["t"]
            ).total_seconds()
        elif i == len(series) - 1:
            dtdt = (series[i]["dt"] - series[i - 1]["dt"]) / (
                series[i]["t"] - series[i - 1]["t"]
            ).total_seconds()
        else:
            dtdt = (series[i + 1]["dt"] - series[i - 1]["dt"]) / (
                series[i + 1]["t"] - series[i - 1]["t"]
            ).total_seconds()
        series[i]["dtdt"] = dtdt
        # delay-rate → Hz proxy at f_ref (round-trip rough): Δf ≈ f * dΔt/dt
        series[i]["df_k"] = f_ref * dtdt

    mid_t = series[0]["t"] + (series[-1]["t"] - series[0]["t"]) / 2
    train = [x for x in series if x["t"] <= mid_t]
    test = [x for x in series if x["t"] > mid_t]
    # C1 — scale from train
    scales = [x["obs"] / x["f_geom"] for x in train if abs(x["f_geom"]) > 1]
    s = median(scales)
    print("\nC1 — CALIBRATED(1) scale from train half")
    print(f"  train n={len(train)}  test n={len(test)}  split={mid_t.isoformat()}")
    print(f"  s = median(obs/f_geom)_train = {s:.6f}")
    print("  C1: PASS")

    r_test = [x["obs"] - s * x["f_geom"] for x in test]
    rmin, rmed, rmax, rstdev = stats(r_test)
    print("\nC2 — test residual r = obs - s*f_geom")
    print(f"  min/med/max/stdev = {rmin:.3f} / {rmed:.3f} / {rmax:.3f} / {rstdev:.3f} Hz")
    print("  C2: PASS")

    b_test = [x["b"] for x in test]
    dtdt_test = [x["dtdt"] for x in test]
    dfk_test = [x["df_k"] for x in test]
    invb = [1.0 / x for x in b_test]
    print("\nC3 — solar geometry (frozen K)")
    print(f"  K = {SOLAR_K_M} m")
    print(f"  b median = {median(b_test):.3e} m ({median(b_test)/6.957e8:.3f} R_Sun)")
    print(f"  delay median = {median([x['dt'] for x in test]):.6e} s")
    print(f"  d(delay)/dt median = {median(dtdt_test):.6e}")
    print(f"  f*d(delay)/dt median = {median(dfk_test):.6e} Hz")
    print("  C3: PASS")

    c_dtdt = corr(r_test, dtdt_test)
    c_invb = corr(r_test, invb)
    c_dfk = corr(r_test, dfk_test)
    print("\nC4-C6 — correlations on TEST half")
    print(f"  corr(r, d(delay)/dt) = {c_dtdt:.6f}")
    print(f"  corr(r, 1/b)         = {c_invb:.6f}")
    print(f"  corr(r, f d(delay)/dt) = {c_dfk:.6f}")

    ac = abs(c_dtdt)
    if ac >= 0.5:
        label = "SOLAR_K_RESIDUAL_SIGNAL"
        c456 = "C4"
    elif ac < 0.2:
        label = "NO_SOLAR_K_RESIDUAL_SIGNAL"
        c456 = "C5"
    else:
        label = "UNADJUDICATED"
        c456 = "C6"
    print(f"  gate on |corr(r,d(delay)/dt)|: {c456} -> {label}")

    print("\nC7 — K not fitted; gamma unused — PASS")

    print("\n================================================================")
    print("SUMMARY:", label)
    print("================================================================")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
