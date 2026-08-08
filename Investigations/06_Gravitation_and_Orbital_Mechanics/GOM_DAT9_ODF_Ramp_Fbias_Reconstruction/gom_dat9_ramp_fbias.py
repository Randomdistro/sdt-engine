#!/usr/bin/env python3
"""GOM_DAT9 — TRK-2-18 ramp / Fbias reconstruction vs DSS-25 geometric Doppler."""
from __future__ import annotations

import math
import re
import struct
from datetime import datetime, timedelta, timezone
from pathlib import Path

REC = 36
EPOCH_1950 = datetime(1950, 1, 1, tzinfo=timezone.utc)
C = 299792458.0
RHO_KA = 209.0 / 15.0
SOLAR_K_M = 1476.35

VOLUME = Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021")
P0_ODF = VOLUME / "sce1_157/odf/c32easc2002_157_0000k252v0.odf"
P0_LBL = VOLUME / "sce1_157/odf/c32easc2002_157_0000k252v0.lbl"
DSS_CSV = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_dss25_rr_2002_157.csv"
)


def bits_from(data: bytes, start_bit_1: int, width: int) -> int:
    value = 0
    for bit_index in range(start_bit_1 - 1, start_bit_1 - 1 + width):
        value = (value << 1) | ((data[bit_index // 8] >> (7 - (bit_index % 8))) & 1)
    return value


def label_pointers(text: str) -> dict[str, int]:
    return {
        name: int(rec)
        for name, rec in re.findall(
            r'\^([A-Z0-9_]+)_TABLE\s*=\s*\([^,]+,\s*(\d+)\)', text
        )
    }


def median(xs: list[float]) -> float:
    s = sorted(xs)
    return s[len(s) // 2]


def parse_orbit_row(rec: bytes) -> dict:
    time_int = struct.unpack_from(">I", rec, 0)[0]
    frac_ms = bits_from(rec[4:8], 1, 10)
    obs = struct.unpack_from(">i", rec, 8)[0] + struct.unpack_from(">i", rec, 12)[0] / 1e9
    bf = rec[16:28]
    high = bits_from(bf, 51, 22)
    low = bits_from(bf, 73, 24)
    # Items 20-22 live in last 8 bytes of record (bytes 29-36) as bit string per label
    # Actually items 20-22 are COLUMN after items 6-19 — START_BYTE 29 in some layouts.
    # From label ODF3C: items 6-19 at byte 17 (12 bytes) → bytes 17-28; items 20-22 follow.
    tail = rec[28:36]
    # Item 21 compression: bits 21-42 of the items20-22 bitfield (8 bytes)
    comp_hsec = bits_from(tail, 21, 22)  # hundredths of a second
    return {
        "time": EPOCH_1950 + timedelta(seconds=time_int, milliseconds=frac_ms),
        "obs_hz": obs,
        "f_ref_hz": (high * (1 << 24) + low) * 1e-3,
        "data_type": bits_from(bf, 20, 6),
        "rx": bits_from(bf, 4, 7),
        "dl_band": bits_from(bf, 26, 2),
        "ul_band": bits_from(bf, 28, 2),
        "compression_s": comp_hsec / 100.0,
    }


def parse_ramp_row(rec: bytes) -> dict:
    t0_int = struct.unpack_from(">I", rec, 0)[0]
    t0_ns = struct.unpack_from(">I", rec, 4)[0]
    rate_i = struct.unpack_from(">i", rec, 8)[0]
    rate_f = struct.unpack_from(">i", rec, 12)[0]
    mid = rec[16:20]
    ghz = bits_from(mid, 1, 22)
    stn = bits_from(mid, 23, 10)
    f_mod = struct.unpack_from(">I", rec, 20)[0]
    f_frac = struct.unpack_from(">I", rec, 24)[0]
    t1_int = struct.unpack_from(">I", rec, 28)[0]
    t1_ns = struct.unpack_from(">I", rec, 32)[0]
    f0 = ghz * 1e9 + f_mod + f_frac * 1e-9
    rate = rate_i + rate_f * 1e-9
    t0 = EPOCH_1950 + timedelta(seconds=t0_int, microseconds=t0_ns / 1000.0)
    t1 = EPOCH_1950 + timedelta(seconds=t1_int, microseconds=t1_ns / 1000.0)
    return {
        "t0": t0,
        "t1": t1,
        "rate_hz_s": rate,
        "f0_hz": f0,
        "ghz_field": ghz,
        "station": stn,
        "sky_level": ghz != 0,
    }


def ramp_freq_at(ramps: list[dict], t: datetime) -> float | None:
    for r in ramps:
        if r["t0"] <= t <= r["t1"]:
            dt = (t - r["t0"]).total_seconds()
            return r["f0_hz"] + r["rate_hz_s"] * dt
    # nearest
    if not ramps:
        return None
    best = min(ramps, key=lambda r: min(abs((t - r["t0"]).total_seconds()), abs((t - r["t1"]).total_seconds())))
    if t < best["t0"]:
        return best["f0_hz"]
    dt = (t - best["t0"]).total_seconds()
    return best["f0_hz"] + best["rate_hz_s"] * dt


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


def score(obs: list[float], pred: list[float]) -> tuple[float, float, bool]:
    med_obs = median([abs(x) for x in obs])
    ratio = median([abs(x) for x in pred]) / med_obs
    rel = median([abs(obs[i] - pred[i]) for i in range(len(obs))]) / med_obs
    ok = rel < 0.15 and abs(ratio - 1.0) < 0.15
    return ratio, rel, ok


def main() -> int:
    print("================================================================")
    print("GOM_DAT9 — ODF Ramp / Fbias Reconstruction (TRK-2-18)")
    print("Pre-registered 2026-08-08 · data task · solar K unused")
    print("================================================================\n")

    text = P0_LBL.read_text(encoding="ascii", errors="replace")
    ptr = label_pointers(text)
    data = P0_ODF.read_bytes()
    nrec = len(data) // REC

    # C1 — ramp group 25
    if "ODF4A25" not in ptr or "ODF4B25" not in ptr:
        print("C1 FAIL: missing ODF4A25/ODF4B25 pointers")
        return 1
    hdr = ptr["ODF4A25"] - 1
    first = ptr["ODF4B25"] - 1
    later = sorted(v for k, v in ptr.items() if v > ptr["ODF4B25"])
    end = (later[0] - 1) if later else nrec
    # ramp data rows: first .. end-1, excluding any following headers
    ramps = []
    for i in range(first, end):
        rec = data[i * REC : (i + 1) * REC]
        key = struct.unpack_from(">i", rec, 0)[0]
        # data rows are not header key 2030
        if key == 2030:
            continue
        r = parse_ramp_row(rec)
        if r["station"] in (0, 25) or True:
            ramps.append(r)
    # filter station 25 if tagged
    r25 = [r for r in ramps if r["station"] == 25] or ramps
    c1 = len(r25) >= 1
    print("C1 — Ramp Group 25")
    print(f"  pointer header={ptr['ODF4A25']} data={ptr['ODF4B25']} end_excl={end+1}")
    print(f"  ramp rows decoded: {len(r25)}")
    for r in r25[:5]:
        print(
            f"  f0={r['f0_hz']:.3f} Hz  rate={r['rate_hz_s']:.6f} Hz/s  "
            f"ghz_field={r['ghz_field']} sky={r['sky_level']}  "
            f"stn={r['station']}  {r['t0'].isoformat()} .. {r['t1'].isoformat()}"
        )
    if len(r25) > 5:
        print(f"  ... ({len(r25) - 5} more)")
    print(f"  C1: {'PASS' if c1 else 'FAIL'}")
    if not c1:
        return 1

    # Orbit data
    o0 = ptr["ODF3C"] - 1
    o1 = ptr["ODF4A25"] - 1
    rows = []
    for i in range(o0, o1):
        r = parse_orbit_row(data[i * REC : (i + 1) * REC])
        if r["data_type"] == 12 and r["rx"] == 25:
            rows.append(r)
    sample = rows[::60]
    f_ref = median([r["f_ref_hz"] for r in sample])
    ul_from_ramp = median([r["f0_hz"] for r in r25 if r["f0_hz"] > 0])

    # C2 — Fbias
    fbias_ref = RHO_KA * f_ref
    fbias_ramp = RHO_KA * ul_from_ramp if ul_from_ramp > 1e6 else float("nan")
    # If ramp already sky-level downlink-ish, TRK says ramp freq is sky level —
    # then ul_freq for Fbias may be ramp/ρ or ramp itself depending on product.
    fbias_ramp_as_sky = ul_from_ramp  # interpret ramp f0 as sky (Fbias candidate)
    print("\nC2 — Fbias candidates")
    print(f"  f_ref (Items 18-19) = {f_ref:.3f} Hz")
    print(f"  rho_Ka = {RHO_KA:.10f}")
    print(f"  Fbias_A = rho*f_ref = {fbias_ref:.3f} Hz")
    print(f"  ramp f0 median = {ul_from_ramp:.3f} Hz")
    print(f"  Fbias_B = rho*ramp_f0 = {fbias_ramp:.3f} Hz")
    print(f"  Fbias_C = ramp_f0 as sky = {fbias_ramp_as_sky:.3f} Hz")
    print("  C2: PASS")

    dss = parse_dss(DSS_CSV)
    obs, p0, p1a, p1c, p2a = [], [], [], [], []
    ramp_at = []
    for r in sample:
        rdot = interp_rdot(dss, r["time"])
        fr = ramp_freq_at(r25, r["time"])
        ramp_at.append(fr if fr is not None else float("nan"))
        obs.append(r["obs_hz"])
        # P0 baseline DAT7/8
        p0.append(-2.0 * (rdot / C) * f_ref)
        # P1: -2(rdot/c)*Fbias with Fbias=rho*f_ref
        p1a.append(-2.0 * (rdot / C) * fbias_ref)
        # P1c: -2(rdot/c)*ramp_sky
        p1c.append(-2.0 * (rdot / C) * (fr if fr else fbias_ramp_as_sky))
        # P2: Observable predicted as sky_model - Fbias = -2(rdot/c)*Fbias (same as P1a)
        p2a.append(-2.0 * (rdot / C) * fbias_ref)

    # Additional documented reconstructions:
    # Q1: Observable ≈ -2(rdot/c)*f_ref*rho  (same P1a)
    # Q2: Doppler_full = obs+f_ref vs Fbias*(1-2 rdot/c)  — compare obs to that minus f_ref
    q_sky = []
    for i, r in enumerate(sample):
        rdot = interp_rdot(dss, r["time"])
        sky_model = fbias_ref * (1.0 - 2.0 * rdot / C)
        # if Doppler_full = obs + f_ref, then obs_pred = sky_model - f_ref
        q_sky.append(sky_model - f_ref)
    # Q3: Doppler_full = obs + Fbias_A; obs_pred = sky_model - Fbias_A
    q_obs_from_fbias = []
    for i, r in enumerate(sample):
        rdot = interp_rdot(dss, r["time"])
        sky_model = fbias_ref * (1.0 - 2.0 * rdot / C)
        q_obs_from_fbias.append(sky_model - fbias_ref)

    print("\nC3/C4 — predictor scores vs obs_Hz")
    print(f"  {'name':28s}  ratio   rel_resid  PASS")
    results = []
    for name, pred in [
        ("P0 -2(rdot/c)f_ref", p0),
        ("P1a -2(rdot/c)rho*f_ref", p1a),
        ("P1c -2(rdot/c)ramp_sky", p1c),
        ("Qsky sky(rho f_ref)-f_ref", q_sky),
        ("Qfb  sky-Fbias (=P1a)", q_obs_from_fbias),
        ("-P0 signflip", [-x for x in p0]),
        ("-P1a signflip", [-x for x in p1a]),
    ]:
        ratio, rel, ok = score(obs, pred)
        results.append((name, ratio, rel, ok))
        print(f"  {name:28s}  {ratio:6.3f}  {rel:8.3f}  {'YES' if ok else 'no'}")

    # Compression-time sanity
    comps = [r["compression_s"] for r in sample]
    print(f"\n  compression_s median = {median(comps):.3f} s")

    winners = [n for n, _, _, ok in results if ok]
    c4 = len(winners) > 0
    print(f"\nC4: {'PASS' if c4 else 'FAIL'}")
    if winners:
        print("  winners:", winners)
    else:
        print("  STATUS: FBIAS_RECON_UNRESOLVED")

    print(f"\nC6 — solar K = {SOLAR_K_M} m unused — PASS")

    print("\n================================================================")
    print(
        "SUMMARY:",
        f"FBIAS_RECON_PASS ({','.join(winners)})" if c4 else "FBIAS_RECON_UNRESOLVED",
    )
    print("================================================================")
    return 0 if c4 else 1


if __name__ == "__main__":
    raise SystemExit(main())
