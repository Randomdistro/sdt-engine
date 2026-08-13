#!/usr/bin/env python3
"""NSEQ13 — TT doublet partner flip-axis vs K2,2 frame {x,z} (no C3, no MeV)."""
from __future__ import annotations

import itertools
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
OUT = ROOT / ".audit-tmp" / "nseq13_run.txt"

QX, MX = (1.0, 0.0, 0.0), (-1.0, 0.0, 0.0)
QY, MY = (0.0, 1.0, 0.0), (0.0, -1.0, 0.0)
QZ, MZ = (0.0, 0.0, 1.0), (0.0, 0.0, -1.0)

# NSEQ11 matching frame (frozen)
FRAME = ("x", "z")
SPECTATOR = "y"


def eid(a, b):
    return tuple(sorted((a, b)))


def unit(v):
    n = sum(x * x for x in v) ** 0.5
    return tuple(x / n for x in v)


def add(a, b):
    return (a[0] + b[0], a[1] + b[1], a[2] + b[2])


def near(a, b, tol=1e-8):
    return all(abs(a[i] - b[i]) <= tol for i in range(3))


def build():
    raw = list(itertools.product((-1.0, 1.0), repeat=3))
    tris = [unit(r) for r in raw]
    squares = [QX, MX, QY, MY, QZ, MZ]
    nodes = tris + squares
    key = {v: i for i, v in enumerate(nodes)}
    # map unit tris from raw
    for r in raw:
        key[unit(r)] = key[unit(r)]
    return nodes, key, raw


def edge_index(key, a, b):
    return tuple(sorted((key[a], key[b])))


def surface_and_qq(key, raw):
    S = set()
    for sx, sy, sz in raw:
        t = unit((sx, sy, sz))
        S.add(edge_index(key, t, (sx, 0.0, 0.0)))
        S.add(edge_index(key, t, (0.0, sy, 0.0)))
        S.add(edge_index(key, t, (0.0, 0.0, sz)))
    for a, b in itertools.combinations(raw, 2):
        if sum(1 for k in range(3) if a[k] != b[k]) == 1:
            S.add(edge_index(key, unit(a), unit(b)))
    tri_qq = frozenset(
        edge_index(key, a, b)
        for a, b in [
            (QZ, QX),
            (QZ, QY),
            (QX, QY),
            (MZ, MX),
            (MZ, MY),
            (MX, MY),
        ]
    )
    cyc = [QX, QY, QZ, MX, MY, MZ]
    hex_qq = frozenset(
        edge_index(key, cyc[k], cyc[(k + 1) % 6]) for k in range(6)
    )
    return S, tri_qq, hex_qq


def flip_axis(nodes, e):
    """For a TT Hamming-1 edge, which coordinate flips (x/y/z)."""
    i, j = e
    a, b = nodes[i], nodes[j]
    # both should be body diagonals
    diffs = [k for k in range(3) if abs(a[k] - b[k]) > 1e-9]
    if len(diffs) != 1:
        return None
    return "xyz"[diffs[0]]


def doublet_partners(nodes, edges):
    elist = sorted(edges)
    dirs = [unit(add(nodes[i], nodes[j])) for i, j in elist]
    clusters = []
    for i, d in enumerate(dirs):
        hit = None
        for ci, members in enumerate(clusters):
            if near(d, dirs[members[0]]):
                hit = ci
                break
        if hit is None:
            clusters.append([i])
        else:
            clusters[hit].append(i)
    partner = {}
    for c in clusters:
        if len(c) != 2:
            continue
        e0, e1 = elist[c[0]], elist[c[1]]
        partner[e0] = e1
        partner[e1] = e0
    n_doub = sum(1 for c in clusters if len(c) == 2)
    return partner, n_doub


def main() -> int:
    lines: list[str] = []

    def p(s: str = "") -> None:
        lines.append(s)
        print(s)

    p("NSEQ13 TT partner flip-axis split")
    p("pre-reg: NSEQ13_PRE_REGISTRATION.md")
    p(f"frame M={FRAME} spectator={SPECTATOR}")
    p("forbidden: C3; MeV; post-hoc amend")
    p("")

    nodes, key, raw = build()
    S, tri_qq, hex_qq = surface_and_qq(key, raw)
    shared = tri_qq & hex_qq
    priv_t = tri_qq - shared
    priv_h = hex_qq - shared

    builder_names = (
        surface_and_qq.__code__.co_names
        + flip_axis.__code__.co_names
        + doublet_partners.__code__.co_names
    )
    c4 = not any(n in ("orbit_invariant", "rot_c3") for n in builder_names)
    p(f"C4 no C3 in builders: {'PASS' if c4 else 'FAIL'}")
    p(f"|Shared|={len(shared)} |S|={len(S)}")

    all_ok = c4
    for name, qq, priv in (
        ("triangles", tri_qq, priv_t),
        ("hexagon", hex_qq, priv_h),
    ):
        partner, n_doub = doublet_partners(nodes, set(S) | set(qq))
        qq_hit = [e for e in qq if e in partner]
        shared_flips = []
        match_flips = []
        p(f"branch={name}")
        p(f"  doublets={n_doub} QQ_with_partner={len(qq_hit)}/{len(qq)}")
        for e in sorted(qq):
            if e not in partner:
                p(f"  QQ missing partner — fail")
                continue
            pe = partner[e]
            fa = flip_axis(nodes, pe)
            kind = "Shared" if e in shared else "Matching"
            if e in shared:
                shared_flips.append(fa)
            else:
                match_flips.append(fa)
            p(f"  {kind} TT flip-axis={fa}")

        c1 = n_doub == 6 and len(qq_hit) == 6 and len(shared) == 4 and len(priv) == 2
        c2 = len(shared_flips) == 4 and all(f == SPECTATOR for f in shared_flips)
        c3 = len(match_flips) == 2 and all(f in FRAME for f in match_flips)
        p(f"  C1 exhaustion: {'PASS' if c1 else 'FAIL'}")
        p(f"  C2 Shared->spectator y: {'PASS' if c2 else 'FAIL'} {shared_flips}")
        p(f"  C3 Matching->frame xz: {'PASS' if c3 else 'FAIL'} {match_flips}")
        all_ok = all_ok and c1 and c2 and c3

    p("")
    p("---")
    status = (
        "TT_FLIP_AXIS_SPLIT_SURVIVES" if all_ok else "TT_FLIP_AXIS_SPLIT_EXCLUDED"
    )
    p(f"STATUS {status}")
    p("note: gates frozen; FAIL is terminal for this pre-reg")

    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
