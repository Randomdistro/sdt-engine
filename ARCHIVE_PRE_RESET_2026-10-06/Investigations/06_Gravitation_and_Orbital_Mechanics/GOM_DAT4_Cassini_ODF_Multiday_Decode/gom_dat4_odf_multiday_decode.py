#!/usr/bin/env python3
"""GOM31 — Multi-day CORS_0021 ODF observable decode (Hz)."""
from __future__ import annotations

import argparse
import hashlib
import math
import re
import struct
import sys
from collections import Counter
from datetime import datetime, timedelta, timezone
from pathlib import Path

REC = 36
EPOCH_1950 = datetime(1950, 1, 1, tzinfo=timezone.utc)

PRODUCTS = [
    ("sce1_157", "c32easc2002_157_0000k252v0"),
    ("sce1_157", "c32easc2002_157_0000xmmmv0"),
    ("sce1_158", "c32easc2002_158_0000k252v0"),
    ("sce1_158", "c32easc2002_158_0000xmmmv0"),
    ("sce1_159", "c32easc2002_159_0000k252v0"),
    ("sce1_159", "c32easc2002_159_0000xmmmv0"),
    ("sce1_160", "c32easc2002_160_0000k252v0"),
    ("sce1_160", "c32easc2002_160_0000xmmmv0"),
]


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def bits_from(data: bytes, start_bit_1: int, width: int) -> int:
    value = 0
    for bit_index in range(start_bit_1 - 1, start_bit_1 - 1 + width):
        value = (value << 1) | ((data[bit_index // 8] >> (7 - (bit_index % 8))) & 1)
    return value


def i32(rec: bytes, start: int) -> int:
    return struct.unpack_from(">i", rec, start - 1)[0]


def u32(rec: bytes, start: int) -> int:
    return struct.unpack_from(">I", rec, start - 1)[0]


def parse_row(rec: bytes) -> dict:
    time_int = u32(rec, 1)
    items23 = rec[4:8]
    frac_ms = bits_from(items23, 1, 10)
    obs_int = i32(rec, 9)
    obs_frac = i32(rec, 13)
    bitfield = rec[16:28]
    high_mhz = bits_from(bitfield, 51, 22)
    low_mhz = bits_from(bitfield, 73, 24)
    f_ref = (high_mhz * (1 << 24) + low_mhz) * 1e-3
    return {
        "time": EPOCH_1950 + timedelta(seconds=time_int, milliseconds=frac_ms),
        "obs_hz": obs_int + obs_frac / 1e9,
        "f_ref_hz": f_ref,
        "format_id": bits_from(bitfield, 1, 3),
        "data_type": bits_from(bitfield, 20, 6),
        "validity": bits_from(bitfield, 32, 1),
        "rx": bits_from(bitfield, 4, 7),
    }


def stats(xs: list[float]) -> tuple[float, float, float, float]:
    xs_sorted = sorted(xs)
    n = len(xs)
    mean = sum(xs) / n
    var = sum((x - mean) ** 2 for x in xs) / n
    return xs_sorted[0], xs_sorted[n // 2], xs_sorted[-1], math.sqrt(var)


def validate_synthetic() -> bool:
    obs_int, obs_frac = 12, 345678901
    high, low = 1_000_000, 123456
    bitfield = bytearray(12)
    bitfield[0] = 0b01000000
    for i, bit in enumerate([0, 0, 1, 1, 0, 0]):
        abs_bit = 19 + i
        if bit:
            bitfield[abs_bit // 8] |= 1 << (7 - (abs_bit % 8))
    for i in range(22):
        bit = (high >> (21 - i)) & 1
        abs_bit = 50 + i
        if bit:
            bitfield[abs_bit // 8] |= 1 << (7 - (abs_bit % 8))
    for i in range(24):
        bit = (low >> (23 - i)) & 1
        abs_bit = 72 + i
        if bit:
            bitfield[abs_bit // 8] |= 1 << (7 - (abs_bit % 8))
    rec = (
        struct.pack(">I", 1_000_000)
        + bytes(4)
        + struct.pack(">i", obs_int)
        + struct.pack(">i", obs_frac)
        + bytes(bitfield)
        + bytes(8)
    )
    p = parse_row(rec)
    ok = (
        abs(p["obs_hz"] - (obs_int + obs_frac / 1e9)) < 1e-12
        and abs(p["f_ref_hz"] - (high * (1 << 24) + low) * 1e-3) < 1e-6
    )
    print("VALIDATION A — synthetic obs/ref decode")
    print(f"  obs_hz={p['obs_hz']:.9f} f_ref={p['f_ref_hz']:.6f}  {'PASS' if ok else 'FAIL'}")
    return ok


def parse_label_bounds(label_text: str) -> tuple[int, int, int | None]:
    """Return 0-based [start, end) for orbit-data rows and label ROWS if found."""
    pointers: dict[str, int] = {}
    for name, rec in re.findall(
        r'\^([A-Z0-9_]+)_TABLE\s*=\s*\([^,]+,\s*(\d+)\)', label_text
    ):
        pointers[name] = int(rec)
    if "ODF3C" not in pointers:
        raise ValueError("missing ^ODF3C_TABLE pointer")
    start_1 = pointers["ODF3C"]
    later = sorted(v for k, v in pointers.items() if k != "ODF3C" and v > start_1)
    if not later:
        raise ValueError("no group after ODF3C")
    end_1_excl = later[0]
    rows_label = None
    m = re.search(
        r"OBJECT\s*=\s*ODF3C_TABLE.*?ROWS\s*=\s*(\d+)",
        label_text,
        flags=re.S | re.I,
    )
    if m:
        rows_label = int(m.group(1))
    return start_1 - 1, end_1_excl - 1, rows_label


def decode_file(odf: Path, label: Path) -> dict:
    text = label.read_text(encoding="ascii", errors="replace")
    start0, end0, rows_label = parse_label_bounds(text)
    data = odf.read_bytes()
    n_file = len(data) // REC
    if end0 > n_file:
        raise ValueError(f"pointer end {end0} beyond file records {n_file}")
    rows = [parse_row(data[i * REC : (i + 1) * REC]) for i in range(start0, end0)]
    n = len(rows)
    if rows_label is not None and n != rows_label:
        bound_ok = False
    else:
        bound_ok = True
    obs = [r["obs_hz"] for r in rows]
    refs = [r["f_ref_hz"] for r in rows]
    omin, omed, omax, ostdev = stats(obs)
    rmin, rmed, rmax, rstdev = stats(refs)
    finite = all(math.isfinite(x) for x in obs)
    ref_pos = all(x > 0 for x in refs)
    types = Counter(r["data_type"] for r in rows)
    rxs = Counter(r["rx"] for r in rows)
    valid = Counter(r["validity"] for r in rows)
    return {
        "product": odf.name,
        "sha256": sha256(odf),
        "n": n,
        "rows_label": rows_label,
        "bound_ok": bound_ok,
        "finite": finite,
        "ref_pos": ref_pos,
        "t0": rows[0]["time"],
        "t1": rows[-1]["time"],
        "obs": (omin, omed, omax, ostdev),
        "f_ref": (rmin, rmed, rmax, rstdev),
        "types": dict(types),
        "rx": dict(rxs),
        "validity": dict(valid),
        "pass": bound_ok and finite and ref_pos and n > 0,
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--volume",
        type=Path,
        default=Path(
            "Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021"
        ),
    )
    args = parser.parse_args()

    print("================================================================")
    print("GOM31 — Multi-Day CORS_0021 ODF Observable Decode")
    print("Pre-registered 2026-08-08 · no residual / no koppa fit")
    print("================================================================\n")

    if not validate_synthetic():
        return 2

    print("\nC1 — local product inventory")
    missing = []
    paths: list[tuple[Path, Path]] = []
    for day, stem in PRODUCTS:
        odf = args.volume / day / "odf" / f"{stem}.odf"
        lbl = args.volume / day / "odf" / f"{stem}.lbl"
        if odf.is_file() and lbl.is_file():
            print(f"  [HAVE] {day}/{stem}.odf  {odf.stat().st_size} B")
            paths.append((odf, lbl))
        else:
            print(f"  [MISS] {day}/{stem}")
            missing.append(stem)
    c1 = len(missing) == 0
    print(f"  C1: {'PASS' if c1 else 'FAIL'} ({len(paths)}/8)")

    if not c1:
        print("\nSUMMARY: MULTIDAY_DECODE_FAIL (inventory)")
        return 1

    print("\nC2–C4 — per-file decode")
    results = []
    all_ok = True
    for odf, lbl in paths:
        try:
            r = decode_file(odf, lbl)
        except Exception as exc:
            print(f"\n  FAIL {odf.name}: {type(exc).__name__}: {exc}")
            all_ok = False
            continue
        results.append(r)
        status = "PASS" if r["pass"] else "FAIL"
        if not r["pass"]:
            all_ok = False
        omin, omed, omax, ostdev = r["obs"]
        _, rmed, _, _ = r["f_ref"]
        print(f"\n  [{status}] {r['product']}")
        print(f"    sha256={r['sha256'][:16]}…")
        print(
            f"    rows={r['n']} label_ROWS={r['rows_label']} "
            f"bound={'OK' if r['bound_ok'] else 'MISMATCH'}"
        )
        print(f"    time={r['t0'].isoformat()} .. {r['t1'].isoformat()}")
        print(
            f"    obs_Hz min/med/max/stdev = "
            f"{omin:.6f} / {omed:.6f} / {omax:.6f} / {ostdev:.6f}"
        )
        print(f"    f_ref_Hz median = {rmed:.3f}")
        print(f"    data_types={r['types']}  rx={r['rx']}  validity={r['validity']}")

    print("\nC5 — residual")
    print("  STATUS: PENDING_DATA — not computed")

    print("\n================================================================")
    if c1 and all_ok and len(results) == 8:
        print("SUMMARY: MULTIDAY_DECODE_PASS")
        rc = 0
    else:
        print("SUMMARY: MULTIDAY_DECODE_FAIL")
        rc = 1
    print("================================================================")
    return rc


if __name__ == "__main__":
    raise SystemExit(main())
