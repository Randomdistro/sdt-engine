#!/usr/bin/env python3
"""NSEQ06 — 42 link midpoints → 36 directions + 6 radial doublets (both branches)."""
from __future__ import annotations

import math
import sys
from collections import defaultdict
from itertools import combinations

TOL = 1e-9


def unit(v):
    n = math.sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2])
    return (v[0] / n, v[1] / n, v[2] / n)


def add(a, b):
    return (a[0] + b[0], a[1] + b[1], a[2] + b[2])


def scale(a, s):
    return (a[0] * s, a[1] * s, a[2] * s)


def near_vec(a, b, tol=1e-8):
    return all(abs(a[i] - b[i]) <= tol for i in range(3))


def build_face_graph(branch: str):
    tris = []
    for sx in (-1, 1):
        for sy in (-1, 1):
            for sz in (-1, 1):
                tris.append(("T", (float(sx), float(sy), float(sz))))
    squares = [
        ("Q", (1.0, 0.0, 0.0)),
        ("Q", (-1.0, 0.0, 0.0)),
        ("Q", (0.0, 1.0, 0.0)),
        ("Q", (0.0, -1.0, 0.0)),
        ("Q", (0.0, 0.0, 1.0)),
        ("Q", (0.0, 0.0, -1.0)),
    ]
    nodes = tris + squares
    # Place vertices at unit face-normal positions
    pos = [unit(nodes[i][1]) for i in range(len(nodes))]
    key = {nodes[i][1]: i for i in range(len(nodes))}
    edges = set()

    def add_edge(a, b):
        i, j = key[a], key[b]
        if i == j:
            return
        edges.add((min(i, j), max(i, j)))

    for _, (sx, sy, sz) in tris:
        add_edge((sx, sy, sz), (sx, 0.0, 0.0))
        add_edge((sx, sy, sz), (0.0, sy, 0.0))
        add_edge((sx, sy, sz), (0.0, 0.0, sz))

    for (_, a), (_, b) in combinations(tris, 2):
        ham = sum(1 for k in range(3) if a[k] != b[k])
        if ham == 1:
            add_edge(a, b)

    if branch == "triangles":
        add_edge((0.0, 0.0, 1.0), (1.0, 0.0, 0.0))
        add_edge((0.0, 0.0, 1.0), (0.0, 1.0, 0.0))
        add_edge((1.0, 0.0, 0.0), (0.0, 1.0, 0.0))
        add_edge((0.0, 0.0, -1.0), (-1.0, 0.0, 0.0))
        add_edge((0.0, 0.0, -1.0), (0.0, -1.0, 0.0))
        add_edge((-1.0, 0.0, 0.0), (0.0, -1.0, 0.0))
    elif branch == "hexagon":
        cyc = [
            (1.0, 0.0, 0.0),
            (0.0, 1.0, 0.0),
            (0.0, 0.0, 1.0),
            (-1.0, 0.0, 0.0),
            (0.0, -1.0, 0.0),
            (0.0, 0.0, -1.0),
        ]
        for k in range(6):
            add_edge(cyc[k], cyc[(k + 1) % 6])
    else:
        raise ValueError(branch)
    return pos, edges


def midpoint_analysis(branch: str):
    pos, edges = build_face_graph(branch)
    mids = []
    for i, j in edges:
        mids.append(scale(add(pos[i], pos[j]), 0.5))
    # Distinct Euclidean midpoints
    uniq_pos = []
    for m in mids:
        if not any(near_vec(m, u) for u in uniq_pos):
            uniq_pos.append(m)
    # Angular directions (unit rays from origin through midpoints)
    dirs = [unit(m) for m in mids]
    # Cluster directions
    clusters: list[list[int]] = []
    assigned = [-1] * len(dirs)
    for i, d in enumerate(dirs):
        found = None
        for ci, members in enumerate(clusters):
            if near_vec(d, dirs[members[0]], 1e-8):
                found = ci
                break
        if found is None:
            clusters.append([i])
            assigned[i] = len(clusters) - 1
        else:
            clusters[found].append(i)
            assigned[i] = found
    multiplicities = sorted(len(c) for c in clusters)
    doublets = [c for c in clusters if len(c) == 2]
    singles = [c for c in clusters if len(c) == 1]
    doublet_dirs = frozenset(
        tuple(round(dirs[c[0]][k], 10) for k in range(3)) for c in doublets
    )
    return {
        "E": len(edges),
        "n_mid_euclid": len(uniq_pos),
        "n_dir": len(clusters),
        "n_doublet": len(doublets),
        "n_single": len(singles),
        "multiplicities": multiplicities,
        "doublet_dirs": doublet_dirs,
    }


def main() -> int:
    print("NSEQ06 link midpoint direction doublets")
    print("pre-reg: NSEQ06_PRE_REGISTRATION.md")
    results = {}
    doublet_sets = {}
    ok = True
    for branch in ("triangles", "hexagon"):
        r = midpoint_analysis(branch)
        results[branch] = r
        doublet_sets[branch] = r["doublet_dirs"]
        print(f"branch={branch}")
        print(f"  E={r['E']} euclid_mids={r['n_mid_euclid']} dirs={r['n_dir']}")
        print(f"  doublets={r['n_doublet']} singles={r['n_single']}")
        print(f"  multiplicities={r['multiplicities']}")
        gate = (
            r["E"] == 42
            and r["n_mid_euclid"] == 42
            and r["n_dir"] == 36
            and r["n_doublet"] == 6
            and r["n_single"] == 30
        )
        print(f"  C1 counts: {'PASS' if gate else 'FAIL'}")
        ok = ok and gate

    inter = doublet_sets["triangles"] & doublet_sets["hexagon"]
    # Complementarity: empty intersection of doubled ray sets
    comp = len(inter) == 0
    print(f"C2 doublet-ray sets complementary (intersect empty): {comp} (|inter|={len(inter)})")
    union = doublet_sets["triangles"] | doublet_sets["hexagon"]
    print(f"  |union of doublet rays|={len(union)} (expect 12 if complementary)")
    ok = ok and comp and len(union) == 12

    print("---")
    if ok:
        print("STATUS NSEQ06_MIDPOINT_DOUBLETS_SURVIVE")
        return 0
    print("STATUS NSEQ06_MIDPOINT_DOUBLETS_FAIL_OR_OPEN")
    return 1


if __name__ == "__main__":
    sys.exit(main())
