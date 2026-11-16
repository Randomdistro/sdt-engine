#!/usr/bin/env python3
"""NSEQ12 — Shared vs matching QQ distinguished by doublet surface-partner class."""
from __future__ import annotations

import itertools
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
OUT = ROOT / ".audit-tmp" / "nseq12_run.txt"

Vec = tuple[float, float, float]


def unit(v: Vec) -> Vec:
    n = (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]) ** 0.5
    return (v[0] / n, v[1] / n, v[2] / n)


def add(a: Vec, b: Vec) -> Vec:
    return (a[0] + b[0], a[1] + b[1], a[2] + b[2])


def near(a: Vec, b: Vec, tol: float = 1e-8) -> bool:
    return all(abs(a[i] - b[i]) <= tol for i in range(3))


def eid(i: int, j: int) -> tuple[int, int]:
    return (i, j) if i < j else (j, i)


def build_geometry():
    """14 nodes: 8 T (cube corners) + 6 Q (axes). Surface + both QQ branches."""
    tris = list(itertools.product((-1.0, 1.0), repeat=3))
    squares = [
        (1.0, 0.0, 0.0),
        (-1.0, 0.0, 0.0),
        (0.0, 1.0, 0.0),
        (0.0, -1.0, 0.0),
        (0.0, 0.0, 1.0),
        (0.0, 0.0, -1.0),
    ]
    labels = ["T"] * 8 + ["Q"] * 6
    raw = tris + squares
    pos = [unit(p) for p in raw]
    key = {raw[i]: i for i in range(14)}

    def idx(v: Vec) -> int:
        return key[v]

    surface: set[tuple[int, int]] = set()
    # T-Q cuboct adjacencies
    for sx, sy, sz in tris:
        surface.add(eid(idx((sx, sy, sz)), idx((sx, 0.0, 0.0))))
        surface.add(eid(idx((sx, sy, sz)), idx((0.0, sy, 0.0))))
        surface.add(eid(idx((sx, sy, sz)), idx((0.0, 0.0, sz))))
    # T-T Hamming-1
    for a, b in itertools.combinations(tris, 2):
        if sum(1 for k in range(3) if a[k] != b[k]) == 1:
            surface.add(eid(idx(a), idx(b)))

    def q(v: Vec) -> int:
        return idx(v)

    tri_qq = {
        eid(q((0, 0, 1)), q((1, 0, 0))),
        eid(q((0, 0, 1)), q((0, 1, 0))),
        eid(q((1, 0, 0)), q((0, 1, 0))),
        eid(q((0, 0, -1)), q((-1, 0, 0))),
        eid(q((0, 0, -1)), q((0, -1, 0))),
        eid(q((-1, 0, 0)), q((0, -1, 0))),
    }
    hex_qq = set()
    cyc = [
        (1.0, 0.0, 0.0),
        (0.0, 1.0, 0.0),
        (0.0, 0.0, 1.0),
        (-1.0, 0.0, 0.0),
        (0.0, -1.0, 0.0),
        (0.0, 0.0, -1.0),
    ]
    for k in range(6):
        hex_qq.add(eid(q(cyc[k]), q(cyc[(k + 1) % 6])))

    return pos, labels, surface, tri_qq, hex_qq


def edge_kind(labels, e: tuple[int, int]) -> str:
    a, b = labels[e[0]], labels[e[1]]
    return "".join(sorted([a, b]))  # QQ, TT, or QT (sorted Q,T -> QT)


def doublet_map(pos, edges: set[tuple[int, int]]):
    """Cluster midpoint rays; return list of member edge-index pairs for doublets."""
    elist = sorted(edges)
    mids = [unit(add(pos[i], pos[j])) for i, j in elist]
    clusters: list[list[int]] = []
    for i, d in enumerate(mids):
        hit = None
        for ci, members in enumerate(clusters):
            if near(d, mids[members[0]]):
                hit = ci
                break
        if hit is None:
            clusters.append([i])
        else:
            clusters[hit].append(i)
    doublets = []
    for members in clusters:
        if len(members) == 2:
            doublets.append((elist[members[0]], elist[members[1]]))
        elif len(members) != 1:
            doublets.append(None)  # unexpected multiplicity
    return doublets, elist


def analyze_branch(name, pos, labels, surface, qq):
    full = set(surface) | set(qq)
    doublets, _ = doublet_map(pos, full)
    # Keep only QQ+S doublets
    pairs = []
    for d in doublets:
        if d is None:
            return {"ok_mult": False}
        e0, e1 = d
        k0, k1 = edge_kind(labels, e0), edge_kind(labels, e1)
        if {k0, k1} == {"QQ", "TT"}:
            qq_e, s_e = (e0, e1) if k0 == "QQ" else (e1, e0)
            pairs.append((qq_e, s_e, "TT"))
        elif {k0, k1} == {"QQ", "QT"}:
            qq_e, s_e = (e0, e1) if k0 == "QQ" else (e1, e0)
            pairs.append((qq_e, s_e, "TQ"))
        elif {k0, k1} == {"QQ", "QQ"}:
            pairs.append((e0, e1, "QQQQ"))
        else:
            pairs.append((e0, e1, k0 + "+" + k1))

    qq_in_doublet = [p[0] for p in pairs if p[2] in ("TT", "TQ")]
    return {
        "ok_mult": True,
        "n_doublet_qq_s": len(qq_in_doublet),
        "qq_covered": set(qq_in_doublet),
        "pairs": pairs,
        "qq_set": set(qq),
    }


def main() -> int:
    lines: list[str] = []

    def p(s: str = "") -> None:
        lines.append(s)
        print(s)

    p("NSEQ12 Shared vs matching surface partners")
    p("pre-reg: NSEQ12_PRE_REGISTRATION.md")
    p("gates frozen; FAIL is terminal")
    p("")

    pos, labels, surface, tri_qq, hex_qq = build_geometry()
    shared = tri_qq & hex_qq
    priv_t = tri_qq - shared
    priv_h = hex_qq - shared

    # C4
    builder_names = (
        build_geometry.__code__.co_names
        + doublet_map.__code__.co_names
        + analyze_branch.__code__.co_names
    )
    c4 = not any(n in ("orbit_invariant", "rot_c3") for n in builder_names)
    p(f"C4 no C3 helpers: {'PASS' if c4 else 'FAIL'}")

    all_ok = c4
    for name, qq, priv in (
        ("triangles", tri_qq, priv_t),
        ("hexagon", hex_qq, priv_h),
    ):
        r = analyze_branch(name, pos, labels, surface, qq)
        p(f"branch={name}")
        if not r.get("ok_mult", False):
            p("  unexpected midpoint multiplicity: FAIL")
            all_ok = False
            continue
        covered = r["qq_covered"]
        c1 = covered == set(qq) and r["n_doublet_qq_s"] == 6
        p(f"  QQ covered in QQ+S doublets: {len(covered)}/6  C1: {'PASS' if c1 else 'FAIL'}")

        shared_kinds = []
        priv_kinds = []
        for qq_e, s_e, kind in r["pairs"]:
            if kind not in ("TT", "TQ"):
                p(f"  non QQ+S doublet class {kind}: counted against H1/H2")
                continue
            if qq_e in shared:
                shared_kinds.append(kind)
            elif qq_e in priv:
                priv_kinds.append(kind)
            else:
                p(f"  QQ edge not in Shared/priv for this branch — FAIL")
                c1 = False

        p(f"  Shared partner kinds: {shared_kinds}")
        p(f"  matching partner kinds: {priv_kinds}")
        c2 = len(shared_kinds) == 4 and all(k == "TT" for k in shared_kinds)
        c3 = len(priv_kinds) == 2 and all(k == "TQ" for k in priv_kinds)
        p(f"  C2 Shared->TT: {'PASS' if c2 else 'FAIL'}")
        p(f"  C3 matching->TQ: {'PASS' if c3 else 'FAIL'}")
        all_ok = all_ok and c1 and c2 and c3
        p("")

    p("---")
    status = (
        "SHARED_VS_MATCHING_SURFACE_SURVIVES"
        if all_ok
        else "SHARED_VS_MATCHING_SURFACE_EXCLUDED"
    )
    p(f"STATUS {status}")
    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
