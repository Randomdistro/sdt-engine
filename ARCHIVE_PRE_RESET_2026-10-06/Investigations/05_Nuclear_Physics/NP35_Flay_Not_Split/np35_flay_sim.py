#!/usr/bin/env python3
"""NP35 — flay-not-split: emit splits, then compare IAEA independent yields.

Instrument validation (known answers) runs before any yield file is opened.
Predictions for all eight systems are printed before CSV load.
"""
from __future__ import annotations

import csv
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]

# NSEQ05 species-pure neutron sequence (engine capacities). Not fitted.
SEQ = [2, 8, 20, 28, 40, 50, 70, 82, 112, 126, 168]
T_SHELLS = (28, 50, 82, 126)  # T8, T10, T12, T14
# Next deuteron completion after each T-shell:
T_NEXT_D = {28: 40, 50: 70, 82: 112, 126: 168}

SYSTEMS = [
    ("U-235", ROOT / "Datasets/nuclear/IAEA_U235_independent_FY.csv", 92, 235, 236, "thermal"),
    ("U-233", ROOT / "Datasets/nuclear/fission_yields/IAEA_233U_independent_FY.csv", 92, 233, 234, "thermal"),
    ("Pu-239", ROOT / "Datasets/nuclear/fission_yields/IAEA_239Pu_independent_FY.csv", 94, 239, 240, "thermal"),
    ("Pu-241", ROOT / "Datasets/nuclear/fission_yields/IAEA_241Pu_independent_FY.csv", 94, 241, 242, "thermal"),
    ("Np-237", ROOT / "Datasets/nuclear/fission_yields/IAEA_237Np_independent_FY.csv", 93, 237, 238, "fast"),
    ("Am-241", ROOT / "Datasets/nuclear/fission_yields/IAEA_241Am_independent_FY.csv", 95, 241, 242, "fast"),
    ("U-238", ROOT / "Datasets/nuclear/fission_yields/IAEA_238U_independent_FY.csv", 92, 238, 239, "fast"),
    ("Th-232", ROOT / "Datasets/nuclear/fission_yields/IAEA_232Th_independent_FY.csv", 90, 232, 233, "fast"),
]


def alpha_grammar(Z: int, A: int) -> tuple[int, int]:
    return 3 * Z - A - 2, A - 2 * Z


def outermost_complete(N: int) -> int:
    reached = [c for c in SEQ if c <= N]
    if not reached:
        raise ValueError("N below sequence")
    return reached[-1]


def outermost_sealed_T(N: int) -> int | None:
    sealed = [t for t, d_done in T_NEXT_D.items() if N >= d_done]
    return max(sealed) if sealed else None


def split_from_NH(Z: int, Astar: int, N_H: int) -> dict:
    N_p = Astar - Z
    Z_H = int(round(N_H * Z / N_p))
    A_H = Z_H + N_H
    A_L = Astar - A_H
    Z_L = Z - Z_H
    nd_p, nt_p = alpha_grammar(Z, Astar)
    nd_h, nt_h = alpha_grammar(Z_H, A_H)
    nd_l, nt_l = alpha_grammar(Z_L, A_L)
    return {
        "N_H": N_H,
        "Z_H": Z_H,
        "A_H": A_H,
        "Z_L": Z_L,
        "A_L": A_L,
        "N_p": N_p,
        "nd_p": nd_p,
        "nt_p": nt_p,
        "ledger_T": nt_l + nt_h - nt_p,
        "ledger_D": (nd_l + nd_h) - (nd_p - 2),
    }


def classify_dA(delta: float) -> str:
    ad = abs(delta)
    if ad < 8:
        return "MATCH"
    if ad < 20:
        return "ORDER"
    return "EXCLUDED"


def massyield(path: Path, energy: str) -> dict[int, float]:
    col = f"independent_{energy}_fy"
    Y: dict[int, float] = {}
    with path.open(newline="") as f:
        for row in csv.DictReader(f):
            a = int(row["a_daughter"])
            v = (row.get(col) or "").strip()
            if v:
                Y[a] = Y.get(a, 0.0) + float(v)
    return Y


def hump_centroid(Y: dict[int, float], lo: int, hi: int) -> tuple[float, int]:
    w = {a: Y.get(a, 0.0) for a in range(lo, hi + 1)}
    mode = max(w, key=w.get)
    lo2, hi2 = mode - 8, mode + 8
    num = sum(a * Y.get(a, 0.0) for a in range(lo2, hi2 + 1))
    den = sum(Y.get(a, 0.0) for a in range(lo2, hi2 + 1))
    return num / den, mode


def slope(xs: list[float], ys: list[float]) -> float:
    n = len(xs)
    mx = sum(xs) / n
    my = sum(ys) / n
    den = sum((x - mx) ** 2 for x in xs)
    if den == 0:
        return 0.0
    return sum((x - mx) * (y - my) for x, y in zip(xs, ys)) / den


def validate_instrument() -> None:
    print("--- instrument validation (no yield files) ---")
    assert outermost_complete(144) == 126, outermost_complete(144)
    assert outermost_sealed_T(144) == 82, outermost_sealed_T(144)
    assert outermost_sealed_T(100) == 50, outermost_sealed_T(100)
    assert outermost_sealed_T(200) == 126, outermost_sealed_T(200)
    assert outermost_sealed_T(30) is None
    s = split_from_NH(92, 236, 82)
    assert s["ledger_T"] == 0 and s["ledger_D"] == 0, s
    print("  F1(U-236 N=144) complete = 126  PASS")
    print("  F3(U-236 N=144) sealed T = 82   PASS")
    print("  F3(N=100) sealed T = 50         PASS")
    print("  F3(N=200) sealed T = 126        PASS (superheavy switch)")
    print("  2d->alpha ledger on F3 pair     PASS")
    print("VALIDATION PASS")


def main() -> int:
    print("NP35 flay-not-split")
    print("pre-reg: NP35_PRE_REGISTRATION.md")
    validate_instrument()

    print("\n--- predictions (yield files not opened) ---")
    preds = []
    print(f"{'sys':>8} {'A*':>4} {'N':>4} {'F1 N_H':>7} {'F1 A_H':>7} {'F3 N_H':>7} {'F3 Z_H':>7} {'F3 A_H':>7} {'F3 A_L':>7} {'F50 A_H':>8}")
    for lab, path, Z, A, Astar, energy in SYSTEMS:
        N = Astar - Z
        n1 = outermost_complete(N)
        n3 = outermost_sealed_T(N)
        if n3 is None:
            print(f"STATUS NP35_NO_SEALED_T for {lab}")
            return 1
        f1 = split_from_NH(Z, Astar, n1)
        f3 = split_from_NH(Z, Astar, n3)
        f50 = {"A_H": 50 + 82, "A_L": Astar - 132, "Z_H": 50, "N_H": 82}
        preds.append((lab, path, Z, Astar, energy, f1, f3, f50, N))
        print(
            f"{lab:>8} {Astar:>4} {N:>4} {f1['N_H']:>7} {f1['A_H']:>7} "
            f"{f3['N_H']:>7} {f3['Z_H']:>7} {f3['A_H']:>7} {f3['A_L']:>7} {f50['A_H']:>8}"
        )

    print("\n--- comparison (IAEA independent FY opened now) ---")
    print(f"{'sys':>8} {'obs A_L':>8} {'obs A_H':>8} {'F1 dAH':>8} {'F1':>8} {'F3 dAH':>8} {'F3':>8} {'F3 dAL':>8} {'F50 dAH':>8}")
    rows_f3 = []
    g1_excl = None
    g2_cls = None
    g3_ok = True
    g5_vals = []
    for lab, path, Z, Astar, energy, f1, f3, f50, N in preds:
        Y = massyield(path, energy)
        mid = Astar / 2.0
        AL, _ = hump_centroid(Y, 70, int(mid))
        AH, _ = hump_centroid(Y, int(mid) + 1, 175)
        d1 = f1["A_H"] - AH
        d3 = f3["A_H"] - AH
        dL = f3["A_L"] - AL
        d50 = f50["A_H"] - AH
        c1, c3 = classify_dA(d1), classify_dA(d3)
        print(
            f"{lab:>8} {AL:>8.1f} {AH:>8.1f} {d1:>+8.1f} {c1:>8} "
            f"{d3:>+8.1f} {c3:>8} {dL:>+8.1f} {d50:>+8.1f}"
        )
        rows_f3.append((Astar, f3["A_H"], AH, AL, dL, c3))
        if lab == "U-235":
            g1_excl = abs(d1) >= 20
            g2_cls = c3
        if not (128 <= f3["A_H"] <= 148):
            g3_ok = False
        g5_vals.append(dL)

    sl_pred = slope([r[0] for r in rows_f3], [r[1] for r in rows_f3])
    sl_obs = slope([r[0] for r in rows_f3], [r[2] for r in rows_f3])
    g4_ok = abs(sl_pred) < 0.25
    g5_ok = all(1.0 <= v <= 8.0 for v in g5_vals)

    print("\n--- gates ---")
    print(f"  G1 F1 U-235 |dAH|>=20 (EXCLUDE F1): {g1_excl}  (need True)")
    print(f"  G2 F3 U-235 class: {g2_cls}  (need MATCH)")
    print(f"  G3 F3 A_H in [128,148] all 8: {g3_ok}")
    print(f"  G4 F3 A_H vs A* slope={sl_pred:+.3f} (obs {sl_obs:+.3f}); |pred|<0.25: {g4_ok}")
    print(f"  G5 F3 A_L_pre-A_L_obs in [1,8] all 8: {g5_ok}  values={[round(v,2) for v in g5_vals]}")

    print("\n--- limitations ---")
    print("  Z_H from parent Z/N is a composition assumption, not a seating derivation.")
    print("  nu is not predicted; G5 only checks the residue class.")
    print("  Jacket 2d->alpha is ledger, not a coordinate unwrap.")
    print("  Superheavy N>=168 switch not scored (no FY in-repo).")

    if g1_excl and g2_cls == "MATCH" and g3_ok and g4_ok and g5_ok:
        print("STATUS NP35_FLAY_CONDITIONAL")
        return 0
    if g1_excl and g2_cls in ("MATCH", "ORDER") and g3_ok:
        print("STATUS NP35_FLAY_ORDER_PARTIAL")
        return 0
    if not g1_excl:
        print("STATUS NP35_F1_NOT_EXCLUDED")
        return 0
    print("STATUS NP35_FLAY_EXCLUDED")
    return 0


if __name__ == "__main__":
    sys.exit(main())
