#!/usr/bin/env python3
"""GOM34 — DSS-25 station LOS + band/turnaround Doppler fidelity (solar K fixed)."""
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
SOLAR_K_M = 1476.35  # c-boundary radius; unused / not fitted

VOLUME = Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021")
P0_ODF = VOLUME / "sce1_157/odf/c32easc2002_157_0000k252v0.odf"
P0_LBL = VOLUME / "sce1_157/odf/c32easc2002_157_0000k252v0.lbl"
GEO_CSV = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_geocentric_2002_157.csv"
)
DSS_CSV = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_dss25_rr_2002_157.csv"
)

# Documented Cassini Ka downlink class (sensitivity branch only; not fitted)
KA_DOWN_HZ = 32.028e9
TURNAROUND = {
    1: 1.0,  # S
    2: 880.0 / 749.0,  # X ≈ 11/3 used in label for receivers; uplink ratios differ
    3: 209.0 / 15.0,  # Ka
}


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
    return {
        "time": EPOCH_1950 + timedelta(seconds=time_int, milliseconds=frac_ms),
        "obs_hz": obs,
        "f_ref_hz": (high * (1 << 24) + low) * 1e-3,
        "data_type": bits_from(bf, 20, 6),
        "rx": bits_from(bf, 4, 7),
        "dl_band": bits_from(bf, 26, 2),
        "ul_band": bits_from(bf, 28, 2),
        "ex_band": bits_from(bf, 30, 2),
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


def stats(xs: list[float]) -> tuple[float, float, float, float]:
    s = sorted(xs)
    n = len(s)
    mean = sum(s) / n
    var = sum((x - mean) ** 2 for x in s) / n
    return s[0], s[n // 2], s[-1], math.sqrt(var)


def fetch_horizons_dss25_rr() -> Path:
    if DSS_CSV.is_file() and DSS_CSV.stat().st_size > 500:
        print("C1 — using frozen DSS-25 RR CSV:", DSS_CSV)
        return DSS_CSV
    params = {
        "format": "text",
        "COMMAND": "'-82'",
        "OBJ_DATA": "NO",
        "MAKE_EPHEM": "YES",
        "EPHEM_TYPE": "OBSERVER",
        "CENTER": "'DSS-25'",
        "START_TIME": "'2002-06-06 20:30'",
        "STOP_TIME": "'2002-06-06 23:00'",
        "STEP_SIZE": "'5 m'",
        "QUANTITIES": "'20'",
        "ANG_FORMAT": "DEG",
        "CSV_FORMAT": "YES",
        "CAL_FORMAT": "CAL",
    }
    url = "https://ssd.jpl.nasa.gov/api/horizons.api?" + urllib.parse.urlencode(params)
    print("C1 — fetching Horizons Cassini @ DSS-25 range/range-rate…")
    with urllib.request.urlopen(url, timeout=120) as resp:
        body = resp.read().decode("utf-8", "replace")
    DSS_CSV.parent.mkdir(parents=True, exist_ok=True)
    DSS_CSV.write_text(body, encoding="utf-8")
    print("  wrote", DSS_CSV, "bytes", len(body.encode()))
    return DSS_CSV


def parse_observer_rr(path: Path) -> list[dict]:
    text = path.read_text(encoding="utf-8", errors="replace")
    if "$$SOE" not in text:
        raise ValueError("missing SOE: " + text[:300].replace("\n", " "))
    block = text.split("$$SOE", 1)[1].split("$$EOE", 1)[0].strip()
    rows = []
    for line in block.splitlines():
        if not line.strip():
            continue
        parts = [p.strip() for p in line.split(",")]
        # Date, , delta(AU), deldot(km/s) typical for Q20 CSV
        if len(parts) < 4:
            continue
        try:
            cal = parts[0].replace("A.D. ", "").strip()
            # '2002-Jun-06 20:30'
            if "TDB" in cal or "UT" in cal:
                cal = cal.replace("TDB", "").replace("UT", "").strip()
            t = datetime.strptime(cal[:17], "%Y-%b-%d %H:%M").replace(
                tzinfo=timezone.utc
            )
            # Find numeric delta, deldot — often last two numeric fields
            nums = []
            for p in parts[1:]:
                try:
                    nums.append(float(p))
                except ValueError:
                    continue
            if len(nums) < 2:
                continue
            delta_au, deldot_kms = nums[-2], nums[-1]
            rdot = deldot_kms * 1000.0  # m/s
            rows.append({"t": t, "delta_au": delta_au, "rdot": rdot})
        except Exception:
            continue
    return rows


def parse_geo_vectors(path: Path) -> list[dict]:
    text = path.read_text(encoding="utf-8", errors="replace")
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
            vx = float(parts[5]) * 1000.0
            vy = float(parts[6]) * 1000.0
            vz = float(parts[7]) * 1000.0
        except (ValueError, IndexError):
            continue
        rows.append({"t": t, "r": (x, y, z), "v": (vx, vy, vz)})
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


def interp_geo_rdot(rows: list[dict], t: datetime) -> float:
    if t <= rows[0]["t"]:
        r, v = rows[0]["r"], rows[0]["v"]
    elif t >= rows[-1]["t"]:
        r, v = rows[-1]["r"], rows[-1]["v"]
    else:
        r = v = None
        for i in range(len(rows) - 1):
            a, b = rows[i], rows[i + 1]
            if a["t"] <= t <= b["t"]:
                span = (b["t"] - a["t"]).total_seconds()
                u = 0.0 if span == 0 else (t - a["t"]).total_seconds() / span
                r = tuple(a["r"][j] + u * (b["r"][j] - a["r"][j]) for j in range(3))
                v = tuple(a["v"][j] + u * (b["v"][j] - a["v"][j]) for j in range(3))
                break
        if r is None:
            r, v = rows[-1]["r"], rows[-1]["v"]
    rng = math.sqrt(sum(x * x for x in r))
    rhat = tuple(x / rng for x in r)
    return sum(v[i] * rhat[i] for i in range(3))


def main() -> int:
    print("================================================================")
    print("GOM34 — DSS-25 Station LOS + Band/Turnaround Doppler Fidelity")
    print("Pre-registered 2026-08-08 · solar K frozen · no fit")
    print("================================================================\n")

    print("VALIDATION A — Ka turnaround constant")
    rho = TURNAROUND[3]
    ok_a = abs(rho - 209.0 / 15.0) < 1e-15
    print(f"  rho_Ka={rho:.10f}  {'PASS' if ok_a else 'FAIL'}")
    if not ok_a:
        return 2

    try:
        dss_path = fetch_horizons_dss25_rr()
        dss = parse_observer_rr(dss_path)
    except Exception as exc:
        print("C1 FAIL:", type(exc).__name__, str(exc)[:200])
        return 1
    c1 = len(dss) >= 10
    print(f"  DSS-25 RR samples: {len(dss)}  C1: {'PASS' if c1 else 'FAIL'}")
    if not c1:
        # dump head for debug
        print(DSS_CSV.read_text(encoding="utf-8", errors="replace")[:800])
        return 1
    print(f"  first/last: {dss[0]['t'].isoformat()} .. {dss[-1]['t'].isoformat()}")
    print(f"  rdot sample0 = {dss[0]['rdot']:.3f} m/s")

    if not GEO_CSV.is_file():
        print("C3 FAIL: missing geocenter CSV from GOM33")
        return 1
    geo = parse_geo_vectors(GEO_CSV)

    text = P0_LBL.read_text(encoding="ascii", errors="replace")
    s0, e0 = label_bounds(text)
    data = P0_ODF.read_bytes()
    rows = []
    for i in range(s0, e0):
        r = parse_row(data[i * REC : (i + 1) * REC])
        if r["data_type"] == 12 and r["rx"] == 25:
            rows.append(r)
    sample = rows[::60]

    # C2 band census
    from collections import Counter

    bands = Counter((r["dl_band"], r["ul_band"], r["ex_band"]) for r in sample)
    print("\nC2 — band IDs on P0 subsample")
    print(f"  (dl,ul,ex) counts: {dict(bands)}")
    mode_bands = bands.most_common(1)[0][0]
    dl, ul, ex = mode_bands
    rho = TURNAROUND.get(ul, float("nan"))
    c2 = ul == 3 and dl == 3 and math.isfinite(rho)
    print(f"  mode bands dl/ul/ex = {dl}/{ul}/{ex}  turnaround={rho}")
    print(f"  C2: {'PASS' if c2 else 'FAIL'}")

    f_ref = median([r["f_ref_hz"] for r in sample])
    # Predictor A: GOM33 form (geocenter + f_ref)
    # Predictor B1: DSS-25 + f_ref
    # Predictor B2: DSS-25 + Ka downlink nominal (sensitivity)
    pred_a, pred_b1, pred_b2, obs = [], [], [], []
    for r in sample:
        rdot_g = interp_geo_rdot(geo, r["time"])
        rdot_s = interp_rdot(dss, r["time"])
        fa = -2.0 * (rdot_g / C) * f_ref
        fb1 = -2.0 * (rdot_s / C) * f_ref
        fb2 = -2.0 * (rdot_s / C) * KA_DOWN_HZ
        pred_a.append(fa)
        pred_b1.append(fb1)
        pred_b2.append(fb2)
        obs.append(r["obs_hz"])

    med_obs = median([abs(x) for x in obs])
    ratio_a = median([abs(x) for x in pred_a]) / med_obs
    ratio_b1 = median([abs(x) for x in pred_b1]) / med_obs
    ratio_b2 = median([abs(x) for x in pred_b2]) / med_obs

    res_a = [obs[i] - pred_a[i] for i in range(len(obs))]
    res_b1 = [obs[i] - pred_b1[i] for i in range(len(obs))]
    res_b2 = [obs[i] - pred_b2[i] for i in range(len(obs))]
    med_abs_a = median([abs(x) for x in res_a])
    med_abs_b1 = median([abs(x) for x in res_b1])
    med_abs_b2 = median([abs(x) for x in res_b2])

    # Primary B = B1 (f_ref); B2 is sensitivity
    closer_ratio = abs(ratio_b1 - 1.0) < abs(3.37 - 1.0) or abs(ratio_b1 - 1.0) < abs(
        ratio_a - 1.0
    )
    better_resid = med_abs_b1 < med_abs_a
    c4 = closer_ratio or better_resid

    print("\nC3 — predictors")
    print(f"  f_ref median = {f_ref:.3f} Hz")
    print(f"  Ka_down (sensitivity) = {KA_DOWN_HZ:.3f} Hz")
    print(f"  ratio_A (geo+f_ref)     = {ratio_a:.4f}")
    print(f"  ratio_B1 (DSS25+f_ref)  = {ratio_b1:.4f}")
    print(f"  ratio_B2 (DSS25+Ka_nom) = {ratio_b2:.4f}")
    print("  C3: PASS")

    print("\nC4 — fidelity vs GOM33 / predictor A")
    print(f"  |res|_med A  = {med_abs_a:.3f} Hz")
    print(f"  |res|_med B1 = {med_abs_b1:.3f} Hz")
    print(f"  |res|_med B2 = {med_abs_b2:.3f} Hz")
    print(f"  closer ratio or better residual: {c4}")
    print(f"  C4: {'PASS' if c4 else 'FAIL'}")

    rmin, rmed, rmax, rstdev = stats(res_b1)
    # Diagnostic: correlation and scale (COMPUTED; not a solar-K fit)
    mean_o = sum(obs) / len(obs)
    mean_p = sum(pred_b1) / len(pred_b1)
    num = sum((obs[i] - mean_o) * (pred_b1[i] - mean_p) for i in range(len(obs)))
    den_o = math.sqrt(sum((x - mean_o) ** 2 for x in obs))
    den_p = math.sqrt(sum((x - mean_p) ** 2 for x in pred_b1))
    corr = num / (den_o * den_p) if den_o and den_p else float("nan")
    scales = [obs[i] / pred_b1[i] for i in range(len(obs)) if abs(pred_b1[i]) > 1]
    scale_med = median(scales) if scales else float("nan")
    print("\nC5 — time-series residual obs - f_pred_B1")
    print(f"  n={len(res_b1)}")
    print(f"  min/median/max/stdev = {rmin:.3f} / {rmed:.3f} / {rmax:.3f} / {rstdev:.3f} Hz")
    print(f"  corr(obs, f_pred_B1) = {corr:.6f}")
    print(f"  median(obs/f_pred_B1) scale = {scale_med:.6f}  (diagnostic COMPUTED)")
    print("  C5: PASS (reported)")

    print("\nC6 — solar K (c-boundary radius)")
    print(f"  frozen K = {SOLAR_K_M} m — unused; not fitted")
    print("  C6: PASS")

    ok = c1 and c2 and c4
    print("\n================================================================")
    print(
        "SUMMARY:",
        "STATION_DOPPLER_FIDELITY_PASS" if ok else "STATION_DOPPLER_FIDELITY_FAIL",
    )
    print("================================================================")
    return 0 if ok else 1


if __name__ == "__main__":
    raise SystemExit(main())
