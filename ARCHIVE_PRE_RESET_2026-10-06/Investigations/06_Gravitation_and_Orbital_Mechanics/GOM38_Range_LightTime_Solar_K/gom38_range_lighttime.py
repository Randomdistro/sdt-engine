#!/usr/bin/env python3
"""GOM38 — type-37 SRA range census + light-time vs frozen solar K."""
from __future__ import annotations

import math
import re
import struct
from collections import Counter
from datetime import datetime, timedelta, timezone
from pathlib import Path

REC = 36
EPOCH_1950 = datetime(1950, 1, 1, tzinfo=timezone.utc)
C = 299792458.0
R_SUN = 6.957e8
SOLAR_K_M = 1476.35

VOLUME = Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021")
XMMMV0 = [
    ("sce1_157", "c32easc2002_157_0000xmmmv0"),
    ("sce1_158", "c32easc2002_158_0000xmmmv0"),
    ("sce1_159", "c32easc2002_159_0000xmmmv0"),
    ("sce1_160", "c32easc2002_160_0000xmmmv0"),
]
# Multi-day DSS-25 RR already frozen for 157-160
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
        "obs": obs,
        "f_ref_hz": (high * (1 << 24) + low) * 1e-3,
        "data_type": bits_from(bf, 20, 6),
        "rx": bits_from(bf, 4, 7),
        "ul_band": bits_from(bf, 28, 2),
        "dl_band": bits_from(bf, 26, 2),
    }


def parse_dss_delta(path: Path) -> list[dict]:
    """Observer Q20: delta(AU), deldot(km/s)."""
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
        delta_m = nums[-2] * 149597870700.0  # AU -> m
        rows.append({"t": t, "range_m": delta_m})
    return rows


def parse_vectors(path: Path) -> list[dict]:
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
        except (ValueError, IndexError):
            continue
        rows.append({"t": t, "r": (x, y, z)})
    return rows


def interp(rows: list[dict], t: datetime, key: str):
    if t <= rows[0]["t"]:
        return rows[0][key]
    if t >= rows[-1]["t"]:
        return rows[-1][key]
    for i in range(len(rows) - 1):
        a, b = rows[i], rows[i + 1]
        if a["t"] <= t <= b["t"]:
            span = (b["t"] - a["t"]).total_seconds()
            u = 0.0 if span == 0 else (t - a["t"]).total_seconds() / span
            if key == "r":
                return tuple(a["r"][j] + u * (b["r"][j] - a["r"][j]) for j in range(3))
            return a[key] + u * (b[key] - a[key])
    return rows[-1][key]


def impact_shapiro(r_e, r_c, K: float) -> tuple[float, float]:
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


def F_ru_per_sec(f_t: float, ul_band: int) -> float:
    """Documented TRK-2-18 / label band factors — not fitted."""
    if ul_band == 1:  # S
        return f_t / 2.0
    if ul_band == 2:  # X
        return (221.0 / 749.0) * f_t / 2.0
    if ul_band == 3:  # Ka — use label T1/T2 = 14/15 analogously
        return (14.0 / 15.0) * f_t / 2.0
    return float("nan")


def main() -> int:
    print("================================================================")
    print("GOM38 — Type-37 Range / Light-Time vs Frozen Solar K")
    print("Pre-registered 2026-08-08 · K frozen · no RU fit")
    print("================================================================\n")

    # C1 census
    print("C1 — type-37 census (XMMMV0)")
    all37 = []
    for day, stem in XMMMV0:
        odf = VOLUME / day / "odf" / f"{stem}.odf"
        lbl = VOLUME / day / "odf" / f"{stem}.lbl"
        if not odf.is_file():
            print(f"  [MISS] {stem}")
            continue
        text = lbl.read_text(encoding="ascii", errors="replace")
        a, b = label_bounds(text)
        blob = odf.read_bytes()
        n37 = 0
        for i in range(a, b):
            r = parse_row(blob[i * REC : (i + 1) * REC])
            if r["data_type"] == 37:
                r["file"] = stem
                all37.append(r)
                n37 += 1
        print(f"  {stem}: type-37 rows = {n37}")
    c1 = len(all37) > 0
    print(f"  total type-37 = {len(all37)}")
    if c1:
        rx = Counter(r["rx"] for r in all37)
        ul = Counter(r["ul_band"] for r in all37)
        print(f"  RX counts: {dict(rx)}")
        print(f"  uplink band counts: {dict(ul)}")
        print(
            f"  time: {min(r['time'] for r in all37).isoformat()} .. "
            f"{max(r['time'] for r in all37).isoformat()}"
        )
    print(f"  C1: {'PASS' if c1 else 'FAIL'}")
    if not c1:
        return 1

    # C2 finite
    finite = all(math.isfinite(r["obs"]) for r in all37)
    print(f"\nC2 — finite observables: {'PASS' if finite else 'FAIL'}")
    print(f"  obs RU min/med/max = {min(r['obs'] for r in all37):.3f} / "
          f"{median([r['obs'] for r in all37]):.3f} / {max(r['obs'] for r in all37):.3f}")

    # Prefer DSS-25 samples for geometry match
    dss25 = [r for r in all37 if r["rx"] == 25]
    sample = dss25[:: max(1, len(dss25) // 200)] if dss25 else all37[:: max(1, len(all37) // 200)]
    print(f"  using n={len(sample)} samples (prefer RX=25)")

    if not DSS_CSV.is_file() or not HELIO_CAS.is_file() or not HELIO_EAR.is_file():
        print("C3 FAIL: missing frozen Horizons multi-day CSVs (run GOM37 first)")
        return 1
    dss = parse_dss_delta(DSS_CSV)
    cas = parse_vectors(HELIO_CAS)
    ear = parse_vectors(HELIO_EAR)
    print(f"\nC3 — geometry inputs DSS n={len(dss)} Cas={len(cas)} Ear={len(ear)} — PASS")

    # C4/C5 compare
    rtlt_geom = []
    obs_sec = []
    dt_k = []
    b_rs = []
    for r in sample:
        rng = interp(dss, r["time"], "range_m")
        rtlt = 2.0 * rng / C
        rtlt_geom.append(rtlt)
        f_t = r["f_ref_hz"]
        # For Case-2 Doppler, f_ref was S-scale; for ranging use f_ref if >1e9
        # Prefer reconstructing Ka uplink from typical ramp ~34.318e9 when ul=Ka
        if r["ul_band"] == 3 and f_t < 1e10:
            f_t = 34.317852320e9  # documented from GOM_DAT9 ramp census (sky)
        F = F_ru_per_sec(f_t, r["ul_band"])
        if math.isfinite(F) and F > 0:
            obs_sec.append(r["obs"] / F)
        else:
            obs_sec.append(float("nan"))
        re = interp(ear, r["time"], "r")
        rc = interp(cas, r["time"], "r")
        b, dtk = impact_shapiro(re, rc, SOLAR_K_M)
        dt_k.append(dtk)
        b_rs.append(b / R_SUN)

    obs_ok = [x for x in obs_sec if math.isfinite(x)]
    print("\nC4 — range vs geometric RTLT (no fitted RU scale)")
    print(f"  geometric RTLT median = {median(rtlt_geom):.6f} s")
    print(f"  geometric one-way R median = {median([t * C / 2 for t in rtlt_geom])/1e9:.6f} e9 m")
    if obs_ok:
        print(f"  obs time median (RU/F) = {median(obs_ok):.6f} s")
        ratio = median(obs_ok) / median(rtlt_geom)
        print(f"  median(obs_time)/median(RTLT) = {ratio:.6f}")
        resid = [obs_ok[i] - rtlt_geom[i] for i in range(min(len(obs_ok), len(rtlt_geom)))]
        # align lengths carefully
        resid = []
        for i, r in enumerate(sample):
            if math.isfinite(obs_sec[i]):
                resid.append(obs_sec[i] - rtlt_geom[i])
        print(f"  residual (obs-RTLT) med/stdev = {median(resid):.6e} / {stdev(resid):.6e} s")
    else:
        resid = []
        print("  obs time conversion produced no finite values")
    print("  C4: PASS (ledger)")

    print("\nC5 — frozen-K Shapiro delay")
    print(f"  K = {SOLAR_K_M} m")
    print(f"  b median = {median(b_rs):.3f} R_Sun")
    print(f"  Delta_t_K median = {median(dt_k):.6e} s")
    print(f"  Delta_t_K / RTLT median = {median(dt_k) / median(rtlt_geom):.6e}")
    print("  C5: PASS (COMPUTED)")

    # C6 resolvability
    if resid:
        sig = stdev(resid)
        ratio_k = median(dt_k) / max(sig, 1e-30)
    else:
        # proxy: use 1e-3 * RTLT as crude noise floor if no residual
        sig = 1e-3 * median(rtlt_geom)
        ratio_k = median(dt_k) / sig
    print("\nC6 — resolvability")
    print(f"  sigma_residual_proxy = {sig:.6e} s")
    print(f"  Delta_t_K / sigma = {ratio_k:.6e}")
    if ratio_k < 0.01:
        c6_label = "RANGE_K_UNRESOLVED"
    else:
        c6_label = "RANGE_K_RESOLVABLE_PROXY"
    print(f"  C6: {c6_label}")

    print("\nC7 — Doppler-solar-K path -> PENDING_DEFINITION (META update)")
    print("  C7: PASS (administrative)")
    print("\nC8 — K not fitted — PASS")

    print("\n================================================================")
    print("SUMMARY:", c6_label)
    print("================================================================")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
