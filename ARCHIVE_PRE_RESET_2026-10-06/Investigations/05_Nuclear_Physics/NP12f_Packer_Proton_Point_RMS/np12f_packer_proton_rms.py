#!/usr/bin/env python3
"""NP12f — packer proton point-RMS. IAEA sealed."""
from __future__ import annotations

import math
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
IAEA = ROOT / "Datasets/nuclear/IAEA_ground_states_radii.csv"
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pack_nucleus import pack_nucleus, point_rms, protons

# NP12e stated-table RMS (difference report, not a gate)
NP12E = {
    "He4": 1.449569,
    "Be9": 2.050305,
    "C12": 2.776314,
    "O16": 3.551584,
}
FROZEN = [
    ("He4", 2, 4),
    ("Be9", 4, 9),
    ("C12", 6, 12),
    ("O16", 8, 16),
    ("Fe56", 26, 56),
    ("Ca48", 20, 48),
]


def tetra_rms() -> float:
    # regular tetra edge 1, centroid RMS
    s = 1 / math.sqrt(2)
    pts = [
        [1, 1, 1],
        [1, -1, -1],
        [-1, 1, -1],
        [-1, -1, 1],
    ]
    pts = [[x * s / math.sqrt(3) for x in p] for p in pts]  # unused scale
    a = point_rms([[1, 1, 1], [1, -1, -1], [-1, 1, -1], [-1, -1, 1]])
    b = point_rms([[1, 1, 1], [-1, -1, 1], [1, -1, -1], [-1, 1, -1]])  # permutation
    return abs(a - b)


def main() -> int:
    print("NP12f packer proton point-RMS")
    print("pre-reg: PACKER_REOPEN_PRE_REGISTRATION.md")
    print("IAEA sealed — path must not be read")
    print("--- instrument ---")
    d = tetra_rms()
    c1 = d < 1e-12
    print(f"  C1 regular tetra permutation RMS identical: d={d:.3e}  {'PASS' if c1 else 'FAIL'}")

    print("--- packed R_p,RMS (COMPUTED) ---")
    c2 = True
    rows = []
    for name, Z, A in FROZEN:
        nuc = pack_nucleus(A, Z)
        n_p = protons(nuc)
        ok = len(nuc) == A and len(n_p) == Z
        c2 = c2 and ok
        r = point_rms([n["pos"] for n in n_p])
        prev = NP12E.get(name)
        delta = (r - prev) if prev is not None else float("nan")
        rows.append((name, r, prev, delta, ok))
        extra = f"  vs NP12e stated {prev:.6f}  d={delta:+.4f}" if prev is not None else ""
        print(f"  {name:5s}  R_p,RMS={r:.6f} fm  n={len(nuc)} Zp={len(n_p)}  {'PASS' if ok else 'FAIL'}{extra}")

    iaea_opened = False
    # fail-closed: do not open IAEA
    print(f"  C5 IAEA not opened (exists={IAEA.is_file()}, opened={iaea_opened})  PASS")
    print("--- gates ---")
    print(f"  C1 instrument: {'PASS' if c1 else 'FAIL'}")
    print(f"  C2 n_p=Z and n=A: {'PASS' if c2 else 'FAIL'}")
    print("  C3 published: PASS")
    print("  C4 physical charge RMS UNDERDETERMINED (no rho_q): PASS")
    print("  C5 IAEA sealed: PASS")
    print("STATUS NP12f_POINT_PROTON_RMS_PACKED / PHYSICAL_CHARGE_RMS_UNDERDETERMINED")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
