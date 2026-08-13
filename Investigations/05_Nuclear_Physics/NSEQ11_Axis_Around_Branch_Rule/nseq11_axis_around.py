#!/usr/bin/env python3
"""NSEQ11 — axis/around branch rule from polar constructions (no C3)."""
from __future__ import annotations

import itertools
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
OUT = ROOT / ".audit-tmp" / "nseq11_run.txt"

QX, MX = (1.0, 0.0, 0.0), (-1.0, 0.0, 0.0)
QY, MY = (0.0, 1.0, 0.0), (0.0, -1.0, 0.0)
QZ, MZ = (0.0, 0.0, 1.0), (0.0, 0.0, -1.0)
AXES = {
    "x": (QX, MX),
    "y": (QY, MY),
    "z": (QZ, MZ),
}


def eid(a, b):
    return tuple(sorted((a, b)))


def lab(v):
    i = max(range(3), key=lambda k: abs(v[k]))
    return ("+" if v[i] > 0 else "-") + "xyz"[i]


def fmt(e):
    a, b = e
    return f"{lab(a)}-{lab(b)}"


def branch_triangles():
    return frozenset(
        [
            eid(QZ, QX),
            eid(QZ, QY),
            eid(QX, QY),
            eid(MZ, MX),
            eid(MZ, MY),
            eid(MX, MY),
        ]
    )


def branch_hexagon():
    cyc = [QX, QY, QZ, MX, MY, MZ]
    return frozenset(eid(cyc[k], cyc[(k + 1) % 6]) for k in range(6))


def k22_edges(pair_u, pair_v):
    u0, u1 = pair_u
    v0, v1 = pair_v
    return frozenset(
        [eid(u0, v0), eid(u0, v1), eid(u1, v0), eid(u1, v1)]
    )


def perfect_matchings(pair_u, pair_v):
    """Two perfect matchings of K({±u},{±v})."""
    u0, u1 = pair_u
    v0, v1 = pair_v
    m1 = frozenset([eid(u0, v0), eid(u1, v1)])
    m2 = frozenset([eid(u0, v1), eid(u1, v0)])
    return m1, m2


def main() -> int:
    lines: list[str] = []

    def p(s: str = "") -> None:
        lines.append(s)
        # ASCII-only stdout for Windows cp1252
        print(s)

    p("NSEQ11 axis/around branch rule")
    p("pre-reg: NSEQ11_PRE_REGISTRATION.md")
    p("forbidden: C3 x inversion as gate")
    p("")

    # C4: builders must not call C3 orbit helpers (names not in co_names).
    builder_names = (
        branch_triangles.__code__.co_names
        + branch_hexagon.__code__.co_names
        + k22_edges.__code__.co_names
        + perfect_matchings.__code__.co_names
    )
    c4 = not any(n in ("orbit_invariant", "rot_c3", "invert") for n in builder_names)
    p(f"C4 no C3 machinery in builders: {'PASS' if c4 else 'FAIL'}")
    p(f"  builder co_names sample={builder_names[:12]}...")

    tri = branch_triangles()
    hex_ = branch_hexagon()
    shared = tri & hex_
    priv_t = tri - shared
    priv_h = hex_ - shared
    p(f"|Shared|={len(shared)} |Priv_tri|={len(priv_t)} |Priv_hex|={len(priv_h)}")
    p(f"  Shared: {[fmt(e) for e in sorted(shared)]}")
    p(f"  Priv_tri: {[fmt(e) for e in sorted(priv_t)]}")
    p(f"  Priv_hex: {[fmt(e) for e in sorted(priv_h)]}")
    c1 = len(shared) == 4 and len(priv_t) == 2 and len(priv_h) == 2
    p(f"C1 shared/private cardinalities: {'PASS' if c1 else 'FAIL'}")
    p("")

    # H2: search cube-axis pairs
    found = None
    for a, b in itertools.combinations(AXES.keys(), 2):
        ku = k22_edges(AXES[a], AXES[b])
        m1, m2 = perfect_matchings(AXES[a], AXES[b])
        priv_union = priv_t | priv_h
        if priv_union != ku:
            continue
        if priv_t & priv_h:
            continue
        if {priv_t, priv_h} == {m1, m2}:
            found = (a, b, m1, m2, ku)
            break

    if found:
        a, b, m1, m2, ku = found
        p(f"C2 K2,2 on axes {{{a}, {b}}}: PASS")
        p(f"  K2,2 edges: {[fmt(e) for e in sorted(ku)]}")
        p(f"  matching1: {[fmt(e) for e in sorted(m1)]}")
        p(f"  matching2: {[fmt(e) for e in sorted(m2)]}")
        c2 = True
    else:
        p("C2 K2,2 on some cube-axis pair: FAIL")
        c2 = False
        ku = frozenset()

    p("")
    if found:
        a, b, m1, m2, ku = found
        shared_disjoint = shared.isdisjoint(ku)
        recover_t = (shared | priv_t) == tri
        recover_h = (shared | priv_h) == hex_
        c3 = shared_disjoint and recover_t and recover_h
        p(f"  Shared disjoint from K2,2: {shared_disjoint}")
        p(f"  Shared U Priv recovers both branches: {recover_t and recover_h}")
        p(f"C3 branch = Shared U matching: {'PASS' if c3 else 'FAIL'}")
    else:
        c3 = False
        p("C3 branch = Shared U matching: FAIL (no K2,2)")

    p("")
    p("---")
    if c1 and c2 and c3 and c4:
        status = "AXIS_AROUND_BRANCH_RULE_SURVIVES"
        code = 0
    else:
        status = "AXIS_AROUND_BRANCH_RULE_EXCLUDED"
        code = 1
    p(f"STATUS {status}")
    # Explicit: no gate rewrite path
    p("note: gates frozen; FAIL is terminal for this pre-reg")

    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return code


if __name__ == "__main__":
    sys.exit(main())
