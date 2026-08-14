#!/usr/bin/env python3
"""NP17b — Li-6 deuteron and He-4 electrostatics from packed distances."""
from __future__ import annotations

import math
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pack_nucleus import dist, pack_nucleus

AHC = 1.4400  # MeV·fm — NP17 record
B_D = 2.224  # hold-out MEASURED
B_A = 28.296  # hold-out MEASURED


def rel(a: float, b: float) -> float:
    return abs(a - b) / abs(b)


def classify(r: float) -> str:
    if r < 0.20:
        return "MATCH"
    if r < 10:
        return "ORDER"
    return "EXCLUDED"


def main() -> int:
    print("NP17b packed geometry binding")
    print("pre-reg: PACKER_REOPEN_PRE_REGISTRATION.md")
    print(f"  scale αℏc = {AHC} MeV·fm  dnn frozen 1.45 fm")
    print("  no B_d/B_α in candidates (hold-outs only)")

    print("--- instrument: He-4 count ---")
    he = pack_nucleus(4, 2)
    assert len(he) == 4 and sum(n["type"] == "p" for n in he) == 2
    print("  He-4 n=4 Zp=2  PASS")

    li = pack_nucleus(6, 3)
    d_nucs = [n for n in li if n["group"] == "deuteron"]
    d_p = next(n for n in d_nucs if n["type"] == "p")
    d_n = next(n for n in d_nucs if n["type"] == "n")
    D_pn = dist(d_p["pos"], d_n["pos"])
    E_d = 3 * AHC / D_pn
    r1 = rel(E_d, B_D)
    print("--- G1 Li-6 packed deuteron ---")
    print(f"  D_pn = {D_pn:.6f} fm  (packer bondD={li.bondD:.6f})")
    print(f"  E = 3 αℏc / D_pn = {E_d:.4f} MeV  vs {B_D}  rel={r1:.3e}  {classify(r1)}")

    ps = [n for n in he if n["type"] == "p"]
    ns = [n for n in he if n["type"] == "n"]
    r_pp = dist(ps[0]["pos"], ps[1]["pos"])
    r_nn = dist(ns[0]["pos"], ns[1]["pos"])
    r_pn = [dist(p["pos"], n["pos"]) for p in ps for n in ns]
    mean_pn = sum(r_pn) / len(r_pn)
    E_pp = AHC / r_pp
    E_4pn = 4 * (AHC / mean_pn)
    E_4well = 4 * (3 * AHC / mean_pn)
    E_net = E_4well - E_pp
    print("--- G2 He-4 packed pairwise ---")
    print(f"  r_pp={r_pp:.4f}  r_nn={r_nn:.4f}  mean r_pn={mean_pn:.4f} fm")
    print(f"  contacts={len(he.contacts)} (packer bonds; p-p not bonded)")
    cands = {
        "αℏc/r_pp": E_pp,
        "4×αℏc/mean_pn": E_4pn,
        "4×(3αℏc/mean_pn)  [NP17 deuteron factor]": E_4well,
        "4×(3αℏc/mean_pn) − αℏc/r_pp": E_net,
    }
    g2_match = []
    for name, val in cands.items():
        r = rel(val, B_A)
        tag = classify(r)
        print(f"  {name:44s} = {val:8.3f} MeV  rel={r:.3e}  {tag}")
        if tag == "MATCH":
            g2_match.append(name)

    g1 = r1 < 0.20
    g2 = len(g2_match) > 0
    print("--- gates ---")
    print(f"  G1 Li-6 deuteron rel<0.20: {g1}  ({classify(r1)})")
    print(f"  G2 He-4 vs 28.296 rel<0.20: {g2}  matches={g2_match or 'none'}")
    if g1 and g2:
        print("STATUS NP17b_PACKED_BINDING_SURVIVES")
    elif g1 and not g2:
        print("STATUS NP17b_DEUTERON_ONLY  alpha still PENDING")
    else:
        print("STATUS NP17b_PACKED_BINDING_MISS")
    print("  dnn not retuned.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
