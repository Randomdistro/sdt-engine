#!/usr/bin/env python3
"""NSEQ07 — D42 topology: spherical surface triangulation + genus-1 full graph."""
from __future__ import annotations

import math
import sys
from itertools import combinations
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
OUT = ROOT / ".audit-tmp" / "nseq07_run.txt"
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


def build_layers(branch: str):
    """Return pos, surface edges S, QQ chords, full edges — same as NSEQ06."""
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
    labels = [n[0] for n in nodes]
    pos = [unit(nodes[i][1]) for i in range(len(nodes))]
    key = {nodes[i][1]: i for i in range(len(nodes))}

    def eid(a, b):
        i, j = key[a], key[b]
        return (min(i, j), max(i, j))

    surface = set()
    # T−Q cuboct face adjacencies
    for _, (sx, sy, sz) in tris:
        surface.add(eid((sx, sy, sz), (sx, 0.0, 0.0)))
        surface.add(eid((sx, sy, sz), (0.0, sy, 0.0)))
        surface.add(eid((sx, sy, sz), (0.0, 0.0, sz)))
    # T−T tetra edges (Hamming distance 1 among cube corners)
    for (_, a), (_, b) in combinations(tris, 2):
        ham = sum(1 for k in range(3) if a[k] != b[k])
        if ham == 1:
            surface.add(eid(a, b))

    qq = set()
    if branch == "triangles":
        pairs = [
            ((0.0, 0.0, 1.0), (1.0, 0.0, 0.0)),
            ((0.0, 0.0, 1.0), (0.0, 1.0, 0.0)),
            ((1.0, 0.0, 0.0), (0.0, 1.0, 0.0)),
            ((0.0, 0.0, -1.0), (-1.0, 0.0, 0.0)),
            ((0.0, 0.0, -1.0), (0.0, -1.0, 0.0)),
            ((-1.0, 0.0, 0.0), (0.0, -1.0, 0.0)),
        ]
    elif branch == "hexagon":
        cyc = [
            (1.0, 0.0, 0.0),
            (0.0, 1.0, 0.0),
            (0.0, 0.0, 1.0),
            (-1.0, 0.0, 0.0),
            (0.0, -1.0, 0.0),
            (0.0, 0.0, -1.0),
        ]
        pairs = [(cyc[k], cyc[(k + 1) % 6]) for k in range(6)]
    else:
        raise ValueError(branch)
    for a, b in pairs:
        qq.add(eid(a, b))

    full = set(surface) | set(qq)
    return pos, labels, surface, qq, full


def degrees(n, edges):
    deg = [0] * n
    for i, j in edges:
        deg[i] += 1
        deg[j] += 1
    return deg


def connected(n, edges):
    adj = {i: set() for i in range(n)}
    for i, j in edges:
        adj[i].add(j)
        adj[j].add(i)
    seen = {0}
    stack = [0]
    while stack:
        u = stack.pop()
        for v in adj[u]:
            if v not in seen:
                seen.add(v)
                stack.append(v)
    return len(seen) == n


def euler_triangulation(V, E):
    """Assume all faces triangles: 2E=3F ⇒ F=2E/3; χ=V−E+F."""
    if (2 * E) % 3 != 0:
        return None, None
    F = (2 * E) // 3
    chi = V - E + F
    return F, chi


def doublet_provenance(pos, surface, qq, full):
    """Cluster oriented midpoint rays; classify each doublet's edge pair."""
    edge_list = sorted(full)
    mids = [scale(add(pos[i], pos[j]), 0.5) for i, j in edge_list]
    dirs = [unit(m) for m in mids]
    clusters: list[list[int]] = []
    for i, d in enumerate(dirs):
        found = None
        for ci, members in enumerate(clusters):
            if near_vec(d, dirs[members[0]], 1e-8):
                found = ci
                break
        if found is None:
            clusters.append([i])
        else:
            clusters[found].append(i)

    doublets = [c for c in clusters if len(c) == 2]
    singles = [c for c in clusters if len(c) == 1]
    classes = []
    for c in doublets:
        kinds = []
        for idx in c:
            e = edge_list[idx]
            if e in qq:
                kinds.append("QQ")
            elif e in surface:
                kinds.append("S")
            else:
                kinds.append("?")
        classes.append(tuple(sorted(kinds)))
    n_sq = sum(1 for k in classes if k == ("QQ", "S"))
    n_ss = sum(1 for k in classes if k == ("S", "S"))
    n_qq = sum(1 for k in classes if k == ("QQ", "QQ"))
    return {
        "n_dir": len(clusters),
        "n_doublet": len(doublets),
        "n_single": len(singles),
        "n_SQ": n_sq,
        "n_SS": n_ss,
        "n_QQ": n_qq,
        "classes": classes,
    }


def analyze(branch: str) -> dict:
    pos, labels, surface, qq, full = build_layers(branch)
    V = len(pos)
    deg_full = degrees(V, full)
    deg_S = degrees(V, surface)
    F_S, chi_S = euler_triangulation(V, len(surface))
    F_f, chi_f = euler_triangulation(V, len(full))
    prov = doublet_provenance(pos, surface, qq, full)
    return {
        "branch": branch,
        "V": V,
        "n_T": labels.count("T"),
        "n_Q": labels.count("Q"),
        "|S|": len(surface),
        "|QQ|": len(qq),
        "|full|": len(full),
        "S_subset_full": surface <= full,
        "QQ_disjoint_S": qq.isdisjoint(surface),
        "connected_S": connected(V, surface),
        "connected_full": connected(V, full),
        "deg_full": deg_full,
        "regular6": all(d == 6 for d in deg_full),
        "deg_S_Q": sorted(deg_S[i] for i, L in enumerate(labels) if L == "Q"),
        "deg_S_T": sorted(deg_S[i] for i, L in enumerate(labels) if L == "T"),
        "F_S": F_S,
        "chi_S": chi_S,
        "F_full": F_f,
        "chi_full": chi_f,
        "excess": len(full) - (3 * V - 6),
        "prov": prov,
    }


def main() -> int:
    lines: list[str] = []

    def p(s: str = "") -> None:
        lines.append(s)
        print(s)

    p("NSEQ07 D42 genus-1 topology")
    p("pre-reg: NSEQ07_PRE_REGISTRATION.md")
    p("")

    all_ok = True
    c4_ok = True
    for branch in ("triangles", "hexagon"):
        r = analyze(branch)
        p(f"branch={branch}")
        p(f"  V={r['V']} T={r['n_T']} Q={r['n_Q']}")
        p(f"  |S|={r['|S|']} |QQ|={r['|QQ|']} |full|={r['|full|']}")
        p(f"  S_subset_full={r['S_subset_full']} QQ_disjoint_S={r['QQ_disjoint_S']}")
        p(f"  connected S/full = {r['connected_S']}/{r['connected_full']}")
        p(f"  deg_S on Q={r['deg_S_Q']} on T={r['deg_S_T']}")
        p(f"  full regular-6={r['regular6']} deg={r['deg_full']}")
        p(f"  surface triangulation: F={r['F_S']} chi={r['chi_S']} (expect F=24 chi=2)")
        p(f"  full triangulation:    F={r['F_full']} chi={r['chi_full']} (expect F=28 chi=0)")
        p(f"  excess over 3V-6={r['excess']} (expect 6)")
        pr = r["prov"]
        p(
            f"  doublets={pr['n_doublet']} dirs={pr['n_dir']} singles={pr['n_single']} "
            f"SQ={pr['n_SQ']} SS={pr['n_SS']} QQ={pr['n_QQ']}"
        )
        p(f"  doublet classes={pr['classes']}")

        c1 = (
            r["|S|"] == 36
            and r["F_S"] == 24
            and r["chi_S"] == 2
            and r["connected_S"]
            and r["QQ_disjoint_S"]
        )
        c2 = (
            r["|QQ|"] == 6
            and r["excess"] == 6
            and pr["n_doublet"] == 6
            and r["|full|"] - r["|S|"] == 6
        )
        c3 = (
            r["regular6"]
            and r["|full|"] == 3 * r["V"]
            and r["F_full"] == 28
            and r["chi_full"] == 0
            and r["connected_full"]
        )
        c4 = pr["n_SQ"] == 6 and pr["n_SS"] == 0 and pr["n_QQ"] == 0

        p(f"  C1 surface chi=2 triangulation: {'PASS' if c1 else 'FAIL'}")
        p(f"  C2 excess=|QQ|=doublets=6: {'PASS' if c2 else 'FAIL'}")
        p(f"  C3 full chi=0 (genus-1) triangulation: {'PASS' if c3 else 'FAIL'}")
        p(f"  C4 doublet = QQ+surface pair: {'PASS' if c4 else 'FAIL'}")
        p("")
        all_ok = all_ok and c1 and c2 and c3
        c4_ok = c4_ok and c4

    p("---")
    p(f"  C1: {'PASS' if all_ok else 'see above'}")
    if all_ok and c4_ok:
        status = "D42_GENUS1_TOPOLOGY_SURVIVES"
        code = 0
    elif all_ok:
        status = "TOPOLOGY_CLASSIFIED__DOUBLET_PROVENANCE_OPEN"
        code = 0
    else:
        status = "D42_TOPOLOGY_FAIL"
        code = 1
    p(f"STATUS {status}")

    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return code


if __name__ == "__main__":
    sys.exit(main())
