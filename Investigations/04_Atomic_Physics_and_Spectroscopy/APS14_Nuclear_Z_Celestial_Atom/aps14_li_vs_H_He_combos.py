#!/usr/bin/env python3
"""Li I 2s→2p against H / He / H+He drops and Kepler path lengths.

Energy, photon wavelength, and orbital path L=2πr with r = a0 × Ry / E_bind
(H-well Kepler after subtracting hydrogen). Combinatorial screen, not a
pre-registered MATCH. Identities (cascade telescopes) are tagged.
"""
from __future__ import annotations

import csv
import json
import math
from itertools import combinations
from pathlib import Path

from aps14.constants import A0, HC_EV_NM, RY_EV, TWO_PI, mu_over_me

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
IE = json.loads((ROOT / "Datasets/nuclear/ionisation_energies.json").read_text(encoding="utf-8"))

# APS14 resonance.csv MEASURED
H_LY = 10.198836726512972
H_LYB = 12.08750503871422
H_HA = 1.888674618693502
HE_I_RES = 21.218181238889027
HE_II_LY = 40.813140356897236
LI_I_RES = 1.8483696261225844
LI_I_LAM = 670.776  # nm

E_H1 = RY_EV * mu_over_me(1, 1)
E_HEI = IE["2"][0]
E_HEII = IE["2"][1]
E_LII = IE["3"][0]
E_LIII = IE["3"][1]
E_LIIII = IE["3"][2]


def bind_hlike(Z: int, n: int, A: int) -> float:
    return RY_EV * mu_over_me(A, Z) * Z * Z / (n * n)


def r_over_a0(e_bind: float) -> float:
    return RY_EV / e_bind


def path_m(e_bind: float) -> float:
    return TWO_PI * A0 * r_over_a0(e_bind)


def lam_nm(energy: float) -> float:
    return HC_EV_NM / energy


class Piece:
    def __init__(self, name: str, family: str, e_ev: float, e_lo: float, e_hi: float,
                 origin: str, identity: bool = False):
        self.name = name
        self.family = family
        self.e_ev = e_ev
        self.e_lo = e_lo  # leftover bind of lower (deeper)
        self.e_hi = e_hi  # leftover bind of upper
        self.origin = origin
        self.identity = identity
        self.lam = lam_nm(e_ev) if e_ev > 0 else math.nan
        self.r_lo = r_over_a0(e_lo)
        self.r_hi = r_over_a0(e_hi)
        self.dL_a0 = TWO_PI * (self.r_hi - self.r_lo)  # in units of a0; L/(a0)
        self.L_lo_a0 = TWO_PI * self.r_lo
        self.L_hi_a0 = TWO_PI * self.r_hi
        self.path_ratio = self.r_hi / self.r_lo


def hlike_trans(label: str, Z: int, A: int, n_hi: int, n_lo: int, measured: float | None) -> Piece:
    e_lo = bind_hlike(Z, n_lo, A)
    e_hi = bind_hlike(Z, n_hi, A)
    e_calc = e_lo - e_hi
    origin = "MEASURED" if measured is not None else "COMPUTED Rydberg+μ"
    energy = measured if measured is not None else e_calc
    return Piece(f"{label} {n_hi}→{n_lo}", label, energy, e_lo, e_hi, origin)


def main() -> None:
    pieces: list[Piece] = []

    meas_H = {(2, 1): H_LY, (3, 1): H_LYB, (3, 2): H_HA}
    meas_HeII = {(2, 1): HE_II_LY}
    for n_hi, n_lo in ((2, 1), (3, 1), (3, 2), (4, 1), (4, 2), (4, 3)):
        pieces.append(hlike_trans("H I", 1, 1, n_hi, n_lo, meas_H.get((n_hi, n_lo))))
        pieces.append(hlike_trans("He II", 2, 4, n_hi, n_lo, meas_HeII.get((n_hi, n_lo))))

    # He I MEASURED resonance; n=3,4 COMPUTED from 2¹P quantum defect in H well
    he_i_2p_left = E_HEI - HE_I_RES
    nstar_2 = math.sqrt(RY_EV / he_i_2p_left)
    delta = 2.0 - nstar_2
    pieces.append(Piece("He I 2¹P→1s²", "He I", HE_I_RES, E_HEI, he_i_2p_left, "MEASURED"))
    he_i_levels = {}
    for n in (2, 3, 4):
        nstar = n - delta
        left = RY_EV / (nstar * nstar)
        exc = E_HEI - left
        he_i_levels[n] = (exc, left)
        if n > 2:
            pieces.append(Piece(
                f"He I {n}¹P→1s²", "He I", exc, E_HEI, left,
                f"COMPUTED δ={delta:.4f} from 2¹P",
            ))
    # He I n→m among 4,3,2
    for n_hi, n_lo in ((3, 2), (4, 2), (4, 3)):
        e_hi, left_hi = he_i_levels[n_hi]
        e_lo, left_lo = he_i_levels[n_lo]
        pieces.append(Piece(
            f"He I {n_hi}¹P→{n_lo}¹P", "He I", e_hi - e_lo, left_lo, left_hi,
            f"COMPUTED δ={delta:.4f} from 2¹P",
        ))

    # Cascade sums (energy and path telescope — identities within one species)
    def cascade(label: str, family: str, steps: list[tuple[int, int]], Z: int, A: int) -> Piece:
        names = "→".join(str(s[0]) for s in steps) + f"→{steps[-1][1]}"
        e = 0.0
        dL = 0.0
        e_lo = bind_hlike(Z, steps[-1][1], A)
        e_hi = bind_hlike(Z, steps[0][0], A)
        for n_hi, n_lo in steps:
            e += bind_hlike(Z, n_lo, A) - bind_hlike(Z, n_hi, A)
        return Piece(f"{label} cascade {names}", family, e, e_lo, e_hi, "CASCADE identity", True)

    pieces.append(cascade("H I", "H I", [(4, 3), (3, 2)], 1, 1))
    pieces.append(cascade("H I", "H I", [(4, 3), (3, 2), (2, 1)], 1, 1))
    pieces.append(cascade("H I", "H I", [(3, 2), (2, 1)], 1, 1))
    pieces.append(cascade("He II", "He II", [(4, 3), (3, 2)], 2, 4))
    pieces.append(cascade("He II", "He II", [(4, 3), (3, 2), (2, 1)], 2, 4))
    pieces.append(cascade("He II", "He II", [(3, 2), (2, 1)], 2, 4))

    # Targets: Li I 2s→2p from leftover Kepler (not principal-n freeze)
    li_2p_left = E_LII - LI_I_RES
    target = Piece("Li I 2s→2p", "Li I", LI_I_RES, E_LII, li_2p_left, "MEASURED")
    # Secondary: Li II leftover vs Li III (He-like continuation), no measured Li II resonance
    li_ii_left_frac = E_LIIII - E_LIII  # not a line; skip as target
    target_liii = hlike_trans("Li III", 3, 7, 2, 1, None)

    print("=== TARGETS (H-well Kepler r = a0 Ry/E_bind, L = 2πr) ===")
    print(f"Li I 2s→2p  E={target.e_ev:.6f} eV  λ={LI_I_LAM:.3f} nm (APS14)")
    print(f"  leftover bind 2s={E_LII:.5f}  2p={li_2p_left:.5f} eV")
    print(f"  r_2s/a0={target.r_lo:.4f}  r_2p/a0={target.r_hi:.4f}  "
          f"ΔL/(2π a0)={target.r_hi-target.r_lo:.4f}  path ratio={target.path_ratio:.4f}")
    print(f"  principal-n freeze ΔL=0 (same n=2). Kepler leftover ΔL is the 2s vs 2p depth.")
    print(f"Li I IE={E_LII:.5f}  Li II IE={E_LIII:.5f}  Li III IE={E_LIIII:.5f}")
    print(f"He I 2¹P leftover n*={nstar_2:.4f}  δ={delta:.4f}  (n=3,4 COMPUTED from this)")
    print()

    print("=== PRIMITIVES ===")
    print(f"{'name':<28} {'E eV':>10} {'λ nm':>10} {'r_lo':>8} {'r_hi':>8} {'Δr/a0':>8} {'origin'}")
    for p in pieces:
        tag = " ID" if p.identity else ""
        print(f"{p.name:<28} {p.e_ev:10.5f} {p.lam:10.3f} {p.r_lo:8.3f} {p.r_hi:8.3f} "
              f"{p.r_hi-p.r_lo:8.3f} {p.origin}{tag}")
    print()

    singles = [p for p in pieces if not p.identity]
    # Combos: 1, 2, 3 terms. Ops: sum, difference (sorted |a-b|), a+b-c
    rows = []

    def add(kind: str, formula: str, families: str, pred: float, obs: float, origin: str) -> None:
        if pred <= 0 or not math.isfinite(pred):
            return
        rel = abs(pred - obs) / obs
        rows.append({
            "kind": kind, "formula": formula, "families": families,
            "pred": pred, "obs": obs, "rel": rel, "origin": origin,
        })

    # Energy and path (Δr/a0) and wavelength
    obs_E = target.e_ev
    obs_dr = target.r_hi - target.r_lo
    obs_lam = LI_I_LAM
    obs_ratio = target.path_ratio
    obs_rlo = target.r_lo
    obs_rhi = target.r_hi

    for p in pieces:
        fam = p.family
        add("energy", p.name, fam, p.e_ev, obs_E, p.origin)
        add("path_Δr/a0", p.name, fam, p.r_hi - p.r_lo, obs_dr, p.origin)
        add("lambda_nm", p.name, fam, p.lam, obs_lam, p.origin)
        add("path_ratio", p.name, fam, p.path_ratio, obs_ratio, p.origin)
        add("r_lower/a0", p.name + " r_lo", fam, p.r_lo, obs_rlo, p.origin)
        add("r_upper/a0", p.name + " r_hi", fam, p.r_hi, obs_rhi, p.origin)

    for a, b in combinations(singles, 2):
        fam = "+".join(sorted({a.family, b.family}))
        origin = ";".join(sorted({a.origin.split()[0], b.origin.split()[0]}))
        add("energy", f"{a.name} + {b.name}", fam, a.e_ev + b.e_ev, obs_E, origin)
        add("energy", f"|{a.name} − {b.name}|", fam, abs(a.e_ev - b.e_ev), obs_E, origin)
        add("path_Δr/a0", f"{a.name} + {b.name}", fam, (a.r_hi-a.r_lo)+(b.r_hi-b.r_lo), obs_dr, origin)
        add("path_Δr/a0", f"|{a.name} − {b.name}|", fam, abs((a.r_hi-a.r_lo)-(b.r_hi-b.r_lo)), obs_dr, origin)
        add("lambda_nm", f"{a.name} + {b.name}", fam, a.lam + b.lam, obs_lam, origin)
        add("lambda_nm", f"|{a.name} − {b.name}|", fam, abs(a.lam - b.lam), obs_lam, origin)

    # Three-term: only mixed H+He, energy and path, sums/one-minus to keep N honest
    h_s = [p for p in singles if p.family == "H I"]
    he_s = [p for p in singles if p.family in ("He I", "He II")]
    for a in h_s:
        for b, c in combinations(he_s, 2):
            fam = "H I+He"
            add("energy", f"{a.name} + {b.name} + {c.name}", fam,
                a.e_ev + b.e_ev + c.e_ev, obs_E, "3-term")
            add("energy", f"{a.name} + {b.name} − {c.name}", fam,
                abs(a.e_ev + b.e_ev - c.e_ev), obs_E, "3-term")
            add("energy", f"{a.name} − {b.name} − {c.name}", fam,
                abs(a.e_ev - b.e_ev - c.e_ev), obs_E, "3-term")
            dra, drb, drc = a.r_hi-a.r_lo, b.r_hi-b.r_lo, c.r_hi-c.r_lo
            add("path_Δr/a0", f"{a.name} + {b.name} + {c.name}", fam, dra+drb+drc, obs_dr, "3-term")
            add("path_Δr/a0", f"{a.name} + {b.name} − {c.name}", fam, abs(dra+drb-drc), obs_dr, "3-term")
            add("path_Δr/a0", f"{a.name} − {b.name} − {c.name}", fam, abs(dra-drb-drc), obs_dr, "3-term")

    out = HERE / "aps14_li_vs_H_He_combos.csv"
    with out.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0].keys()))
        writer.writeheader()
        writer.writerows(rows)

    print(f"N combos scored: {len(rows)}  wrote {out.name}")
    print()
    print("This is a combinatorial screen. Tight residuals are candidates, not MATCH.")
    print("Cascade rows are algebraic identities (4→3→2 = 4→2).")
    print()

    for kind in ("energy", "path_Δr/a0", "lambda_nm", "path_ratio", "r_lower/a0", "r_upper/a0"):
        subset = [r for r in rows if r["kind"] == kind]
        subset.sort(key=lambda r: r["rel"])
        print(f"=== TOP {kind} vs Li I 2s→2p  (obs={subset[0]['obs']:.6g}) ===")
        print(f"  {'rel':>8}  {'pred':>12}  formula")
        shown = 0
        for r in subset:
            if r["rel"] > 0.08 and shown >= 8:
                break
            print(f"  {100*r['rel']:7.3f}%  {r['pred']:12.6f}  {r['formula']}  [{r['families']}]")
            shown += 1
            if shown >= 12:
                break
        n1 = sum(1 for r in subset if r["rel"] < 0.01)
        n5 = sum(1 for r in subset if r["rel"] < 0.05)
        print(f"  (of {len(subset)}: {n1} below 1%, {n5} below 5%)")
        print()

    # Explicit named comparisons the previous turns used
    print("=== NAMED CROSS-CHECKS ===")
    named = [
        ("H I 3→2 (Hα) energy", H_HA, obs_E),
        ("H I 3→2 wavelength", lam_nm(H_HA), obs_lam),
        ("H I 2→1 energy", H_LY, obs_E),
        ("He I 2¹P→ground energy", HE_I_RES, obs_E),
        ("He II 2→1 energy", HE_II_LY, obs_E),
        ("H 4→3 energy", bind_hlike(1, 3, 1) - bind_hlike(1, 4, 1), obs_E),
        ("H 4→2 energy", bind_hlike(1, 2, 1) - bind_hlike(1, 4, 1), obs_E),
        ("He II 4→3 energy", bind_hlike(2, 3, 4) - bind_hlike(2, 4, 4), obs_E),
        ("He I 3¹P→2¹P energy", he_i_levels[3][0] - he_i_levels[2][0], obs_E),
        ("H 3→2 − He I 3→2", abs(H_HA - (he_i_levels[3][0] - he_i_levels[2][0])), obs_E),
        ("Li III 2→1 / 9 vs H 2→1", target_liii.e_ev / 9.0, H_LY),
    ]
    for name, pred, obs in named:
        rel = abs(pred - obs) / obs
        print(f"  {100*rel:7.3f}%  {pred:12.6f} vs {obs:12.6f}  {name}")

    print()
    print("Li II 1s²→1s2p resonance: NO_DATA in APS14 corpus (not scored).")
    print(f"Li II IE leftover vs Li III (He-like, previous script): "
          f"E_LiII/E_LiIII={E_LIII/E_LIIII:.4f}  Kepler r/R={E_LIIII/E_LIII:.4f}")


if __name__ == "__main__":
    main()
