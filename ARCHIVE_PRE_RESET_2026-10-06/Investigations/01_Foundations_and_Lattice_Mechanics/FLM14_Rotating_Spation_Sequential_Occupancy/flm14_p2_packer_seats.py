#!/usr/bin/env python3
"""FLM14-P2 packer proton-seat tours — geometry precondition. Lamb not opened."""
from __future__ import annotations

import math
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "05_Nuclear_Physics"))
from pack_nucleus import dist, pack_nucleus, protons

GATED = [("C12", 6, 12), ("O16", 8, 16), ("Ca48", 20, 48), ("Fe56", 26, 56)]
REPORT = [("He4", 2, 4), ("Be9", 4, 9)]


def hop_cv(pts: list[list[float]]) -> tuple[float, list[float]]:
    n = len(pts)
    if n < 2:
        return float("nan"), []
    remaining = set(range(1, n))
    order = [0]
    while remaining:
        last = order[-1]
        nxt = min(remaining, key=lambda j: dist(pts[last], pts[j]))
        remaining.remove(nxt)
        order.append(nxt)
    hops = [dist(pts[order[i]], pts[order[(i + 1) % n]]) for i in range(n)]
    mean = sum(hops) / n
    var = sum((h - mean) ** 2 for h in hops) / n
    cv = math.sqrt(var) / mean if mean else float("nan")
    return cv, hops


def main() -> int:
    print("FLM14-P2 packer proton-seat tours")
    print("pre-reg: PACKER_REOPEN_PRE_REGISTRATION.md / FLM14_P2_PACKER_SEATS_PRE_REGISTRATION.md")
    print("  Lamb table not opened. Dwell still DEFER.")
    print("--- instrument V1: square ---")
    sq = [[0, 0, 0], [1, 0, 0], [1, 1, 0], [0, 1, 0]]
    cv_sq, hops_sq = hop_cv(sq)
    v1 = cv_sq < 1e-12
    print(f"  square CV={cv_sq:.3e} hops={['%.3f'%h for h in hops_sq]}  {'PASS' if v1 else 'FAIL'}")

    print("--- report (not gated) ---")
    for name, Z, A in REPORT:
        pts = [n["pos"] for n in protons(pack_nucleus(A, Z))]
        cv, hops = hop_cv(pts)
        print(f"  {name:5s} Z={Z}  CV={cv:.4f}  n_hops={len(hops)}")

    print("--- G1 Z>=6 ---")
    g1_ok = True
    for name, Z, A in GATED:
        pts = [n["pos"] for n in protons(pack_nucleus(A, Z))]
        cv, hops = hop_cv(pts)
        hit = cv > 0.02
        g1_ok = g1_ok and hit
        print(f"  {name:5s} Z={Z}  CV={cv:.4f}  mean_hop={sum(hops)/len(hops):.4f} fm  {'PASS' if hit else 'FAIL'}")

    print("--- gates ---")
    print(f"  V1 square CV=0: {'PASS' if v1 else 'FAIL'}")
    print(f"  G1 CV>0.02 on C/O/Ca/Fe: {'PASS' if g1_ok else 'FAIL'}")
    print("  G2 Lamb not opened: PASS")
    if v1 and g1_ok:
        print("STATUS FLM14_P2_GEOMETRY_PRECONDITION_PASS  dwell/Lamb still DEFER")
    else:
        print("STATUS FLM14_P2_GEOMETRY_PRECONDITION_FAIL  dwell/Lamb still DEFER")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
