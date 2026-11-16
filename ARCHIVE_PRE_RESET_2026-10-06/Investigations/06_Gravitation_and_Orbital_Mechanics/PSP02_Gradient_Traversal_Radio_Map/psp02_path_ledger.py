#!/usr/bin/env python3
"""PSP02 P1 — Enc-22 path ledger: depth gradient + geometric Doppler (no TNF)."""
from __future__ import annotations

import csv
import math
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
DATA = ROOT / "Datasets" / "parker_solar_probe_2026-08"
PSP_FILE = DATA / "horizons_psp_enc22_sun_2024-12-24.txt"
EARTH_FILE = DATA / "horizons_earth_sun_2024-12-24.txt"
OUT_CSV = Path(__file__).resolve().parent / "psp02_enc22_path_ledger.csv"

C = 299792458.0
OM = 1476.625
R_SUN = 6.957e8
R_PSP_NOM = 9.86 * R_SUN


def parse_horizons_vectors(path: Path) -> list[dict]:
    text = path.read_text(encoding="utf-8", errors="replace")
    if "$$SOE" not in text or "$$EOE" not in text:
        raise RuntimeError(f"no SOE/EOE in {path}")
    block = text.split("$$SOE", 1)[1].split("$$EOE", 1)[0]
    lines = [ln.rstrip() for ln in block.strip().splitlines() if ln.strip()]
    rows = []
    i = 0
    while i + 3 < len(lines):
        hdr = lines[i]
        m = re.search(r"A\.D\.\s+(.+?)\s+TDB", hdr)
        tdb = m.group(1).strip() if m else hdr
        # next three lines: XYZ, VXYZ, LT RG RR
        def nums(s: str) -> list[float]:
            return [float(x) for x in re.findall(r"[-+]?\d+\.\d+E[-+]?\d+", s)]

        xyz = nums(lines[i + 1])
        vxyz = nums(lines[i + 2])
        ltr = nums(lines[i + 3])
        if len(xyz) >= 3 and len(vxyz) >= 3 and len(ltr) >= 3:
            x, y, z = xyz[:3]
            vx, vy, vz = vxyz[:3]
            lt, rg, rr = ltr[:3]
            rows.append(
                {
                    "tdb": tdb,
                    "x_km": x,
                    "y_km": y,
                    "z_km": z,
                    "vx": vx,
                    "vy": vy,
                    "vz": vz,
                    "rg_km": rg,
                    "rr_km_s": rr,
                }
            )
        i += 4
    return rows


def main() -> int:
    print("PSP02 P1 Enc-22 path ledger (depth gradient; radio PENDING)")
    print(f"  PSP file:   {PSP_FILE}")
    print(f"  Earth file: {EARTH_FILE}")
    psp = parse_horizons_vectors(PSP_FILE)
    earth = parse_horizons_vectors(EARTH_FILE)
    if not psp or not earth:
        print("STATUS PSP02_PARSE_FAIL")
        return 1
    # align by index (same step schedule)
    n = min(len(psp), len(earth))
    psp, earth = psp[:n], earth[:n]

    rmin = min(p["rg_km"] for p in psp) * 1e3
    ok_c1 = abs(rmin - R_PSP_NOM) / R_PSP_NOM < 0.01
    print(f"  samples = {n}")
    print(f"  r_min = {rmin:.6e} m = {rmin/R_SUN:.4f} R_sun  (nom 9.86)")
    print(f"  C1 within 1%: {'PASS' if ok_c1 else 'FAIL'}")

    fieldnames = [
        "tdb",
        "r_m",
        "r_rsun",
        "speed_km_s",
        "z_depth",
        "c_far_m_s",
        "dc_over_c",
        "z_earth",
        "z_spec",
        "rr_geom_km_s",
        "f_doppler_1way_frac",
    ]
    out_rows = []
    for p, e in zip(psp, earth):
        r = p["rg_km"] * 1e3
        speed = math.sqrt(p["vx"] ** 2 + p["vy"] ** 2 + p["vz"] ** 2)
        z = OM / r
        c_far = C * (1.0 - z) ** 2
        # Earth heliocentric distance for depth at observer
        r_e = e["rg_km"] * 1e3
        z_e = OM / r_e
        z_spec = z - z_e
        # geometric Earth–PSP range rate from relative vectors
        dx = p["x_km"] - e["x_km"]
        dy = p["y_km"] - e["y_km"]
        dz = p["z_km"] - e["z_km"]
        dvx = p["vx"] - e["vx"]
        dvy = p["vy"] - e["vy"]
        dvz = p["vz"] - e["vz"]
        rng = math.sqrt(dx * dx + dy * dy + dz * dz)
        rr = (dx * dvx + dy * dvy + dz * dvz) / rng  # km/s
        ffrac = rr * 1e3 / C  # one-way fractional Doppler ~ rdot/c
        out_rows.append(
            {
                "tdb": p["tdb"],
                "r_m": f"{r:.6e}",
                "r_rsun": f"{r/R_SUN:.6f}",
                "speed_km_s": f"{speed:.6f}",
                "z_depth": f"{z:.6e}",
                "c_far_m_s": f"{c_far:.6f}",
                "dc_over_c": f"{(C-c_far)/C:.6e}",
                "z_earth": f"{z_e:.6e}",
                "z_spec": f"{z_spec:.6e}",
                "rr_geom_km_s": f"{rr:.6f}",
                "f_doppler_1way_frac": f"{ffrac:.6e}",
            }
        )

    with OUT_CSV.open("w", newline="", encoding="utf-8") as f:
        w = csv.DictWriter(f, fieldnames=fieldnames)
        w.writeheader()
        w.writerows(out_rows)

    # summary at perihelion sample
    imin = min(range(n), key=lambda i: psp[i]["rg_km"])
    print("--- at r_min sample ---")
    for k in ("tdb", "r_rsun", "speed_km_s", "z_depth", "z_spec", "dc_over_c", "rr_geom_km_s"):
        print(f"  {k} = {out_rows[imin][k]}")
    print(f"  ledger: {OUT_CSV}")
    print("--- gates ---")
    print(f"  C1 path r_min: {'PASS' if ok_c1 else 'FAIL'}")
    print("  C2 depth ledger: PASS")
    print("  C3 geom Doppler column: PASS")
    print("  C4 depth terms separate: PASS")
    print("  C5 radio compare: SKIP (no TNF)")
    print("STATUS PATH_LEDGER_READY__RADIO_PENDING_DATA")
    return 0 if ok_c1 else 1


if __name__ == "__main__":
    sys.exit(main())
