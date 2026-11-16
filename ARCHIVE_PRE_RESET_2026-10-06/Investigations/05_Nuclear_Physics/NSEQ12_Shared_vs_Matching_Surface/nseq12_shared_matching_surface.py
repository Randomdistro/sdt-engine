#!/usr/bin/env python3
"""NSEQ12 — Shared vs matching QQ doublet surface-partner species (no C3, no MeV)."""
from __future__ import annotations

import itertools
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
OUT = ROOT / ".audit-tmp" / "nseq12_run.txt"

QX, MX = (1.0, 0.0, 0.0), (-1.0, 0.0, 0.0)
QY, MY = (0.0, 1.0, 0.0), (0.0, -1.0, 0.0)
QZ, MZ = (0.0, 0.0, 1.0), (0.0, 0.0, -1.0)


def eid(a, b):
    return tuple(sorted((a, b)))


def unit(v):
    n = sum(x * x for x in v) ** 0.5
    return tuple(x / n for x in v)


def add(a, b):
    return (a[0] + b[0], a[1] + b[1], a[2] + b[2])


def near(a, b, tol=1e-8):
    return all(abs(a[i] - b[i]) <= tol for i in range(3))


def lab(v):
    # Classify node as T (body diagonal) or Q (axis)
    if abs(abs(v[0]) - abs(v[1])) < 1e-9 and abs(abs(v[1]) - abs(v[2])) < 1e-9:
        return "T"
    return "Q"


def edge_species(e, pos):
    i, j = e
    return "".join(sorted([lab(pos[i]), lab(pos[j])]))  # QQ, TQ, or TT


def build_nodes():
    tris = [unit((float(sx), float(sy), float(sz))) for sx in (-1, 1) for sy in (-1, 1) for sz in (-1, 1)]
    squares = [QX, MX, QY, MY, QZ, MZ]
    # Keep Q as exact axis tuples for edge keys matching branches
    nodes = [("T", t) for t in tris] + [("Q", q) for q in squares]
    pos = [n[1] for n in nodes]
    labels = [n[0] for n in nodes]
    key = {}
    for i, (L, v) in enumerate(nodes):
        key[v] = i
        if L == "Q":
            key[v] = i
    # also key unit tris
    for i, (L, v) in enumerate(nodes):
        key[v] = i
    return pos, labels, key


def edge_index(key, a, b):
    return tuple(sorted((key[a], key[b])))


def surface_edges(key):
    """TQ cuboct adjacency + TT Hamming-1 among cube corners."""
    tris = [unit((float(sx), float(sy), float(sz))) for sx in (-1, 1) for sy in (-1, 1) for sz in (-1, 1)]
    S = set()
    for sx, sy, sz in itertools.product((-1.0, 1.0), repeat=3):
        t = unit((sx, sy, sz))
        S.add(edge_index(key, t, (sx, 0.0, 0.0)))
        S.add(edge_index(key, t, (0.0, sy, 0.0)))
        S.add(edge_index(key, t, (0.0, 0.0, sz)))
    for a, b in itertools.combinations(
        [unit((float(sx), float(sy), float(sz))) for sx in (-1, 1) for sy in (-1, 1) for sz in (-1, 1)],
        2,
    ):
        # recover signs
        pass
    # TT via raw signs
    raw = list(itertools.product((-1.0, 1.0), repeat=3))
    for a, b in itertools.combinations(raw, 2):
        if sum(1 for k in range(3) if a[k] != b[k]) == 1:
            S.add(edge_index(key, unit(a), unit(b)))
    return S


def branch_qq(key, name: str):
    if name == "triangles":
        pairs = [
            (QZ, QX),
            (QZ, QY),
            (QX, QY),
            (MZ, MX),
            (MZ, MY),
            (MX, MY),
        ]
    else:
        cyc = [QX, QY, QZ, MX, MY, MZ]
        pairs = [(cyc[k], cyc[(k + 1) % 6]) for k in range(6)]
    return frozenset(edge_index(key, a, b) for a, b in pairs)


def doublet_map(pos, edges):
    """Map each edge index -> partner edge in its radial doublet (or None)."""
    elist = sorted(edges)
    dirs = [unit(add(pos[i], pos[j])) for i, j in elist]
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
    return partner, clusters


def main() -> int:
    lines: list[str] = []

    def p(s: str = "") -> None:
        lines.append(s)
        print(s)

    p("NSEQ12 Shared vs matching surface partners")
    p("pre-reg: NSEQ12_PRE_REGISTRATION.md")
    p("forbidden: C3 gates; MeV; post-hoc amend")
    p("")

    pos, labels, key = build_nodes()
    S = surface_edges(key)
    tri_qq = branch_qq(key, "triangles")
    hex_qq = branch_qq(key, "hexagon")
    shared = tri_qq & hex_qq
    priv_t = tri_qq - shared
    priv_h = hex_qq - shared

    # C4
    builder_names = (
        branch_qq.__code__.co_names
        + surface_edges.__code__.co_names
        + doublet_map.__code__.co_names
    )
    c4 = not any(n in ("orbit_invariant", "rot_c3") for n in builder_names)
    p(f"C4 no C3 in builders: {'PASS' if c4 else 'FAIL'}")

    p(f"|Shared|={len(shared)} |Priv_t|={len(priv_t)} |Priv_h|={len(priv_h)}")
    p(f"|S|={len(S)} (expect 36)")

    all_ok = c4
    for branch, qq, priv in (
        ("triangles", tri_qq, priv_t),
        ("hexagon", hex_qq, priv_h),
    ):
        full = set(S) | set(qq)
        partner, clusters = doublet_map(pos, full)
        n_doublet = sum(1 for c in clusters if len(c) == 2)
        # each QQ should be in a doublet
        qq_in = [e for e in qq if e in partner]
        p(f"branch={branch}")
        p(f"  doublet clusters={n_doublet} (expect 6); QQ with partners={len(qq_in)}/{len(qq)}")

        shared_species = []
        match_species = []
        for e in sorted(qq):
            if e not in partner:
                continue
            pe = partner[e]
            sp = edge_species(pe, pos)
            kind = "Shared" if e in shared else "Matching"
            if e in shared:
                shared_species.append(sp)
            else:
                match_species.append(sp)
            p(f"  {kind} QQ partner species={sp}")

        c1_b = n_doublet == 6 and len(qq_in) == 6 and len(shared) == 4 and len(priv) == 2
        c2_b = len(shared_species) == 4 and all(s == "TT" for s in shared_species)
        c3_b = len(match_species) == 2 and all(s == "TQ" for s in match_species)
        p(f"  C1 exhaustion: {'PASS' if c1_b else 'FAIL'}")
        p(f"  C2 Shared->TT: {'PASS' if c2_b else 'FAIL'} {shared_species}")
        p(f"  C3 Matching->TQ: {'PASS' if c3_b else 'FAIL'} {match_species}")
        all_ok = all_ok and c1_b and c2_b and c3_b

    p("")
    p("---")
    status = (
        "SHARED_TT__MATCHING_TQ_SURVIVES" if all_ok else "SHARED_VS_MATCHING_SURFACE_EXCLUDED"
    )
    p(f"STATUS {status}")
    p("note: gates frozen; FAIL is terminal for this pre-reg")

    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
