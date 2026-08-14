#!/usr/bin/env python3
"""NP36 — jacket Z from seating vs frozen NP35 obs A_H. N_H=82 frozen."""
from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pack_nucleus import prefix_through

# Frozen from .audit-tmp/np35_run.txt (not re-opened IAEA this loop)
OBS_AH = {
    "U-235": 136.5,
    "U-233": 137.2,
    "Pu-239": 136.3,
    "Pu-241": 136.0,
    "Np-237": 136.4,
    "Am-241": 137.6,
    "U-238": 137.2,
    "Th-232": 139.8,
}
SYSTEMS = [
    ("U-235", 92, 236),
    ("U-233", 92, 234),
    ("Pu-239", 94, 240),
    ("Pu-241", 94, 242),
    ("Np-237", 93, 238),
    ("Am-241", 95, 242),
    ("U-238", 92, 239),
    ("Th-232", 90, 233),
]
N_H = 82


def classify(delta: float) -> str:
    ad = abs(delta)
    if ad < 8:
        return "MATCH"
    if ad < 20:
        return "ORDER"
    return "EXCLUDED"


def main() -> int:
    print("NP36 jacket Z from seating")
    print("pre-reg: PACKER_REOPEN_PRE_REGISTRATION.md")
    print("  N_H=82 frozen (NP35 F3). obs A_H frozen from np35_run.txt")
    print("  IAEA yields not re-opened")

    nd, nt, Z12, N12 = prefix_through("T12")
    print("--- instrument: T12 prefix ---")
    print(f"  through T12: nd={nd} nt={nt} Z={Z12} N_actual={N12} A={Z12+N12}")
    assert Z12 == 82 and N12 == 112, (Z12, N12)
    print("  T12 actual Z=82 N=112 A=194  PASS")

    print("--- predictions (no yield files) ---")
    print(f"  {'sys':8s} {'obs':>6s}  R_ratio Z/A  class   R_T12act A=194  class   R_T12lab A=164  class")
    n_ratio = n_act = n_lab = 0
    for name, Z, Astar in SYSTEMS:
        N_p = Astar - Z
        z_ratio = int(round(N_H * Z / N_p))
        a_ratio = z_ratio + N_H
        a_act = Z12 + N12  # 194
        a_lab = 82 + 82  # 164
        obs = OBS_AH[name]
        d_r, d_a, d_l = a_ratio - obs, a_act - obs, a_lab - obs
        c_r, c_a, c_l = classify(d_r), classify(d_a), classify(d_l)
        if c_r == "MATCH":
            n_ratio += 1
        if c_a == "MATCH":
            n_act += 1
        if c_l == "MATCH":
            n_lab += 1
        print(
            f"  {name:8s} {obs:6.1f}  {z_ratio:3d}/{a_ratio:<3d} {c_r:8s}  "
            f"{a_act:3d} {d_a:+6.1f} {c_a:8s}  {a_lab:3d} {d_l:+6.1f} {c_l:8s}"
        )

    print("--- gates (8 systems) ---")
    print(f"  R_ratio MATCH count: {n_ratio}/8  (control, not seating)")
    print(f"  R_T12_actual A=194 MATCH count: {n_act}/8")
    print(f"  R_T12_label  A=164 MATCH count: {n_lab}/8")
    seating_ok = n_act == 8 or n_lab == 8
    if seating_ok:
        print("STATUS NP36_SEATING_ZH_SURVIVES")
    elif n_act == 0 and n_lab == 0:
        print("STATUS NP36_SEATING_ZH_EXCLUDED  parent-ratio control still MATCH-class")
    else:
        print("STATUS NP36_SEATING_ZH_ORDER")
    print("  Mixed T10-Z + T12-N is F_Z50 (NP35 control); not scored as seating.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
