#!/usr/bin/env python3
"""NSEQ15 — packed contact lengths vs NSEQ09 SEAL 4.242 MeV. No B_d leak."""
from __future__ import annotations

import math
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pack_nucleus import R_P, dist, pack_nucleus

SEAL = 4.242
AHC = 1.4400
K_E = 8.9875517923e9
E = 1.602176634e-19
R_P_M = R_P * 1e-15
R_E = 2.8179403262e-15
MEV_J = 1.602176634e-13
PI = math.pi
P_EFF = 4.0 * K_E * (E**2) / (PI * R_P_M * R_P_M * R_E * R_E)

FROZEN = [("He4", 2, 4), ("C12", 6, 12), ("O16", 8, 16), ("Fe56", 26, 56)]


def F_occ(r_m: float) -> float:
    return (PI / 4.0) * P_EFF * (R_P_M**2) * (R_P_M**2) / (r_m * r_m)


def E_Fr(r_fm: float) -> float:
    r_m = r_fm * 1e-15
    return F_occ(r_m) * r_m / MEV_J


def rel(a, b):
    return abs(a - b) / abs(b)


def mean_contact(nuc) -> tuple[float, float]:
    all_d = []
    pn_d = []
    for i, j in nuc.contacts:
        d = dist(nuc[i]["pos"], nuc[j]["pos"])
        all_d.append(d)
        types = {nuc[i]["type"], nuc[j]["type"]}
        if types == {"p", "n"}:
            pn_d.append(d)
    return (sum(all_d) / len(all_d), sum(pn_d) / len(pn_d) if pn_d else float("nan"))


def tag(r: float) -> str:
    if r < 0.15:
        return "MATCH"
    if r < 10:
        return "ORDER"
    return "EXCLUDED"


def main() -> int:
    print("NSEQ15 packed contact energy")
    print("pre-reg: PACKER_REOPEN_PRE_REGISTRATION.md")
    print(f"  hold-out SEAL medD = {SEAL} MeV")
    print("  no B_d/B_t")
    print("--- packed mean contact d (fm) ---")
    ds_all = []
    ds_pn = []
    for name, Z, A in FROZEN:
        nuc = pack_nucleus(A, Z)
        m_all, m_pn = mean_contact(nuc)
        ds_all.append(m_all)
        ds_pn.append(m_pn)
        print(f"  {name:5s}  mean_all={m_all:.4f}  mean_pn={m_pn:.4f}  n_bonds={len(nuc.contacts)}")
    d_all = sum(ds_all) / len(ds_all)
    d_pn = sum(ds_pn) / len(ds_pn)
    print(f"  ensemble mean_all={d_all:.4f}  mean_pn={d_pn:.4f}")

    cands = {
        "αℏc / mean_pn": AHC / d_pn,
        "αℏc / mean_all": AHC / d_all,
        "αℏc / dnn(1.45)": AHC / 1.45,
        "F(Rp,Rp)×mean_pn": E_Fr(d_pn),
        "F(Rp,Rp)×mean_all": E_Fr(d_all),
        "F(Rp,Rp)×2 Rp  [NSEQ14 control]": E_Fr(2 * R_P),
        "αℏc / Rp": AHC / R_P,
    }
    print("--- candidates vs SEAL ---")
    matches = []
    for name, val in cands.items():
        r = rel(val, SEAL)
        t = tag(r)
        print(f"  {name:32s} = {val:.6e} MeV  rel={r:.3e}  {t}")
        if t == "MATCH":
            matches.append(name)
    print("---")
    if matches:
        print(f"STATUS NSEQ15_CONTACT_ENERGY_SURVIVES matches={matches}")
    else:
        print("STATUS NSEQ15_UNDERDETERMINED")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
