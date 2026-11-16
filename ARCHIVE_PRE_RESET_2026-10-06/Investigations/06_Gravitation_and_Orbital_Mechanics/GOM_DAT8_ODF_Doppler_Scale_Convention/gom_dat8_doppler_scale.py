#!/usr/bin/env python3
"""GOM35 — discrete documented scale/sign hypotheses for ODF Doppler."""
from __future__ import annotations

import math
import re
import struct
import sys
from datetime import datetime, timedelta, timezone
from pathlib import Path

REC = 36
EPOCH_1950 = datetime(1950, 1, 1, tzinfo=timezone.utc)
C = 299792458.0
SOLAR_K_M = 1476.35

VOLUME = Path("Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021")
P0_ODF = VOLUME / "sce1_157/odf/c32easc2002_157_0000k252v0.odf"
P0_LBL = VOLUME / "sce1_157/odf/c32easc2002_157_0000k252v0.lbl"
DSS_CSV = Path(
    "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_dss25_rr_2002_157.csv"
)

HYP = [
    ("H0", "f0", lambda f0: f0),
    ("H1", "-f0", lambda f0: -f0),
    ("H2", "-0.5*f0", lambda f0: -0.5 * f0),
    ("H3", "-f0/pi", lambda f0: -f0 / math.pi),
    ("H4", "-f0*(221/240)", lambda f0: -f0 * (221.0 / 240.0)),
    ("H5", "-f0*(240/749)", lambda f0: -f0 * (240.0 / 749.0)),
    ("H6", "-f0*(f_ref/8.4e9)", None),  # needs f_ref
    ("H7", "-f0*(8.4e9/32.028e9)", lambda f0: -f0 * (8.4e9 / 32.028e9)),
]


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


def main() -> int:
    print("================================================================")
    print("GOM35 — ODF Doppler Scale/Sign Convention (discrete hypotheses)")
    print("Pre-registered 2026-08-08 · no LS scale · solar K unused")
    print("================================================================\n")

    if not DSS_CSV.is_file():
        print("C1 FAIL: missing DSS-25 CSV")
        return 1
    dss = parse_dss(DSS_CSV)
    text = P0_LBL.read_text(encoding="ascii", errors="replace")
    s0, e0 = label_bounds(text)
    data = P0_ODF.read_bytes()
    rows = [
        parse_row(data[i * REC : (i + 1) * REC])
        for i in range(s0, e0)
    ]
    rows = [r for r in rows if r["data_type"] == 12 and r["rx"] == 25]
    sample = rows[::60]
    f_ref = median([r["f_ref_hz"] for r in sample])
    print(f"C1 — frozen inputs: DSS RR n={len(dss)}; ODF samples={len(sample)}; f_ref={f_ref:.3f}")
    print("  C1: PASS\n")

    f0s, obs = [], []
    for r in sample:
        rdot = interp_rdot(dss, r["time"])
        f0s.append(-2.0 * (rdot / C) * f_ref)
        obs.append(r["obs_hz"])
    med_obs = median([abs(x) for x in obs])

    print("C2 — hypothesis table")
    print(f"  {'ID':4s}  {'model':22s}  ratio  rel_resid  PASS?")
    winners = []
    for hid, name, fn in HYP:
        if hid == "H6":
            pred = [-f0 * (f_ref / 8.4e9) for f0 in f0s]
            # H6: -f0*(f_ref/8.4e9); f0 already includes sign from formula
            # Wait: H6 in table is f = -f0 * (f_ref/8.4e9). f0 is already -2*rdot/c*f_ref.
            # Using lambda style: -f0 * ratio means flip and scale.
            pred = [-f0 * (f_ref / 8.4e9) for f0 in f0s]
        else:
            assert fn is not None
            pred = [fn(f0) for f0 in f0s]
        ratio = median([abs(x) for x in pred]) / med_obs
        rel = median([abs(obs[i] - pred[i]) for i in range(len(obs))]) / med_obs
        ok = rel < 0.15 and abs(ratio - 1.0) < 0.15
        if ok:
            winners.append(hid)
        print(f"  {hid:4s}  {name:22s}  {ratio:6.3f}  {rel:8.3f}  {'YES' if ok else 'no'}")

    print(f"\nC3 — any documented hypothesis passes: {'PASS' if winners else 'FAIL'}")
    if winners:
        print(f"  winners: {winners}")
    print("\nC4 — if none:", "N/A" if winners else "SCALE_CONVENTION_UNRESOLVED")
    print(f"\nC5 — solar K = {SOLAR_K_M} m unused; not fitted — PASS")

    print("\n================================================================")
    if winners:
        print(f"SUMMARY: SCALE_CONVENTION_PASS ({','.join(winners)})")
        rc = 0
    else:
        print("SUMMARY: SCALE_CONVENTION_UNRESOLVED")
        rc = 1
    print("================================================================")
    return rc


if __name__ == "__main__":
    raise SystemExit(main())
