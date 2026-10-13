#!/usr/bin/env python3
"""NP39 — monoisotopy vs NSEQ05 pack staircase. Frozen NP23 C1 sets."""
from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pack_nucleus import grammar, last_stop, walk_schedule

# NP23 C1 width-1 (26). Be is the even-Z exception.
SINGLES = [
    ("Be", 4, 9),
    ("F", 9, 19),
    ("Na", 11, 23),
    ("Al", 13, 27),
    ("P", 15, 31),
    ("Sc", 21, 45),
    ("V", 23, 51),
    ("Mn", 25, 55),
    ("Co", 27, 59),
    ("As", 33, 75),
    ("Rb", 37, 85),
    ("Y", 39, 89),
    ("Nb", 41, 93),
    ("Rh", 45, 103),
    ("In", 49, 113),
    ("I", 53, 127),
    ("Cs", 55, 133),
    ("La", 57, 139),
    ("Pr", 59, 141),
    ("Eu", 63, 153),
    ("Tb", 65, 159),
    ("Ho", 67, 165),
    ("Tm", 69, 169),
    ("Lu", 71, 175),
    ("Re", 75, 185),
    ("Au", 79, 197),
]
LIGHT = {("F", 19), ("Na", 23), ("Al", 27), ("P", 31)}
# NP23 odd-Z doubles (Z>7)
DOUBLES = [
    ("Cl", 17, [35, 37]),
    ("K", 19, [39, 41]),
    ("Cu", 29, [63, 65]),
    ("Ga", 31, [69, 71]),
    ("Br", 35, [79, 81]),
    ("Ag", 47, [107, 109]),
    ("Sb", 51, [121, 123]),
    ("Ir", 77, [191, 193]),
    ("Tl", 81, [203, 205]),
]


def tag_stop(st: dict) -> str:
    if st["sp"] == "α":
        return "α"
    return f"{st['name']} {st['fill']}/{st['cap']}"


def mid_t(st: dict) -> bool:
    return st["sp"] == "t" and 0 < st["fill"] < st["cap"]


def main() -> int:
    print("NP39 monoisotopy vs pack staircase")
    print("pre-reg: PACKER_REOPEN_PRE_REGISTRATION.md")
    print("frozen NP23 C1 singles + odd-Z doubles; no IAEA; no WHICH-A")
    print("--- instrument ---")
    nd, nt = grammar(9, 19)
    st = last_stop(nd, nt)
    assert nd == 6 and nt == 1, (nd, nt)
    assert st["name"] == "T8" and st["fill"] == 1, st
    print("  F-19 grammar+stop T8 1/8  PASS")

    print("--- singles pack-stop ---")
    g1_hit = 0
    g3_odd = 0
    odd_singles = 0
    for sym, Z, A in SINGLES:
        nd, nt = grammar(Z, A)
        st = last_stop(nd, nt)
        mid = mid_t(st)
        t8x1 = st["name"] == "T8" and st["fill"] == 1
        if Z % 2 == 1:
            odd_singles += 1
            if mid:
                g3_odd += 1
        if (sym, A) in LIGHT and t8x1:
            g1_hit += 1
        print(f"  {sym}-{A:3d}  (nd,nt)=({nd:2d},{nt:2d})  {tag_stop(st):16s}  {'mid-T' if mid else 'other':6s}  {'T8x1' if t8x1 else ''}")

    print("--- odd-Z doubles ---")
    t8x1_doubles = []
    for sym, Z, As in DOUBLES:
        row = []
        for A in As:
            nd, nt = grammar(Z, A)
            st = last_stop(nd, nt)
            t8x1 = st["name"] == "T8" and st["fill"] == 1
            row.append(f"{A}:{tag_stop(st)}")
            if t8x1:
                t8x1_doubles.append(f"{sym}-{A}")
        print(f"  {sym:2s}  " + "  ".join(row))

    print("--- gates ---")
    g1 = g1_hit == 4
    g2 = len(t8x1_doubles) == 0
    g3 = g3_odd == 25
    print(f"  G1 light T8x1 4/4: {g1_hit}/4  {'MATCH' if g1 else 'FAIL'}")
    print(f"  G2 no T8x1 double: n={len(t8x1_doubles)} {t8x1_doubles}  {'MATCH' if g2 else 'FAIL'}")
    print(f"  G3 odd-Z singles mid-T 25/25: {g3_odd}/25  {'MATCH' if g3 else 'FAIL'}")
    if g1 and g2 and g3:
        print("STATUS NP39_STAIRCASE_SURVIVES")
    elif g1 and not g2:
        print("STATUS NP39_LIGHT_PATTERN_ONLY  width discriminator FAIL (G2)")
    else:
        print("STATUS NP39_STAIRCASE_FAIL")
    print("  Not native WHICH-A. G3 even-cap T-shells + odd Z is near-identity.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
