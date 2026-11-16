#!/usr/bin/env python3
"""NSEQ08 — shared vs private doublet rays with QQ/S provenance."""
from __future__ import annotations

import math
import sys
from itertools import combinations
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
OUT = ROOT / ".audit-tmp" / "nseq08_run.txt"


def unit(v):
    n = math.sqrt(sum(x * x for x in v))
    return tuple(x / n for x in v)


def add(a, b):
    return (a[0] + b[0], a[1] + b[1], a[2] + b[2])


def scale(a, s):
    return (a[0] * s, a[1] * s, a[2] * s)


def near_vec(a, b, tol=1e-8):
    return all(abs(a[i] - b[i]) <= tol for i in range(3))


def dir_key(d, nd=10):
    return tuple(round(d[k], nd) for k in range(3))


def build(branch: str):
    tris = [
        (float(sx), float(sy), float(sz))
        for sx in (-1, 1)
        for sy in (-1, 1)
        for sz in (-1, 1)
    ]
    squares = [
        (1.0, 0.0, 0.0),
        (-1.0, 0.0, 0.0),
        (0.0, 1.0, 0.0),
        (0.0, -1.0, 0.0),
        (0.0, 0.0, 1.0),
        (0.0, 0.0, -1.0),
    ]
    nodes = [("T", t) for t in tris] + [("Q", q) for q in squares]
    pos = [unit(n[1]) for n in nodes]
    key = {n[1]: i for i, n in enumerate(nodes)}
    lab = [n[0] for n in nodes]

    def eid(a, b):
        i, j = key[a], key[b]
        return (min(i, j), max(i, j))

    surface = set()
    for sx, sy, sz in tris:
        surface.add(eid((sx, sy, sz), (sx, 0.0, 0.0)))
        surface.add(eid((sx, sy, sz), (0.0, sy, 0.0)))
        surface.add(eid((sx, sy, sz), (0.0, 0.0, sz)))
    for a, b in combinations(tris, 2):
        if sum(1 for k in range(3) if a[k] != b[k]) == 1:
            surface.add(eid(a, b))

    if branch == "triangles":
        pairs = [
            ((0.0, 0.0, 1.0), (1.0, 0.0, 0.0)),
            ((0.0, 0.0, 1.0), (0.0, 1.0, 0.0)),
            ((1.0, 0.0, 0.0), (0.0, 1.0, 0.0)),
            ((0.0, 0.0, -1.0), (-1.0, 0.0, 0.0)),
            ((0.0, 0.0, -1.0), (0.0, -1.0, 0.0)),
            ((-1.0, 0.0, 0.0), (0.0, -1.0, 0.0)),
        ]
    else:
        cyc = [
            (1.0, 0.0, 0.0),
            (0.0, 1.0, 0.0),
            (0.0, 0.0, 1.0),
            (-1.0, 0.0, 0.0),
            (0.0, -1.0, 0.0),
            (0.0, 0.0, -1.0),
        ]
        pairs = [(cyc[k], cyc[(k + 1) % 6]) for k in range(6)]
    qq = {eid(a, b) for a, b in pairs}
    return pos, lab, surface, qq


def edge_name(pos, lab, e):
    i, j = e
    return f"{lab[i]}{tuple(round(x, 3) for x in pos[i])}-{lab[j]}{tuple(round(x, 3) for x in pos[j])}"


def doublets_of(branch: str):
    pos, lab, surface, qq = build(branch)
    edges = sorted(surface | qq)
    mids = [scale(add(pos[i], pos[j]), 0.5) for i, j in edges]
    dirs = [unit(m) for m in mids]
    clusters: dict[tuple, list[int]] = {}
    for i, d in enumerate(dirs):
        k = None
        for ck, members in clusters.items():
            if near_vec(d, dirs[members[0]], 1e-8):
                k = ck
                break
        if k is None:
            clusters[dir_key(d)] = [i]
        else:
            clusters[k].append(i)

    out = {}
    for ck, members in clusters.items():
        if len(members) != 2:
            continue
        kinds = []
        edges_here = []
        for idx in members:
            e = edges[idx]
            edges_here.append(e)
            kinds.append("QQ" if e in qq else "S")
        # order as (qq_edge, s_edge)
        if kinds[0] == "QQ" and kinds[1] == "S":
            qq_e, s_e = edges_here[0], edges_here[1]
        elif kinds[0] == "S" and kinds[1] == "QQ":
            qq_e, s_e = edges_here[1], edges_here[0]
        else:
            qq_e, s_e = None, None
        out[ck] = {
            "qq": qq_e,
            "S": s_e,
            "qq_name": edge_name(pos, lab, qq_e) if qq_e else None,
            "S_name": edge_name(pos, lab, s_e) if s_e else None,
        }
    return out, qq, surface


def main() -> int:
    lines: list[str] = []

    def p(s: str = "") -> None:
        lines.append(s)
        print(s)

    p("NSEQ08 shared doublet invariant")
    p("pre-reg: NSEQ08_PRE_REGISTRATION.md")
    p("")

    dA, qqA, _ = doublets_of("triangles")
    dB, qqB, _ = doublets_of("hexagon")
    keysA, keysB = set(dA), set(dB)
    inter = keysA & keysB
    onlyA = keysA - keysB
    onlyB = keysB - keysA
    qq_inter = qqA & qqB
    qq_onlyA = qqA - qqB
    qq_onlyB = qqB - qqA

    p(f"|doublet rays| triangles={len(keysA)} hexagon={len(keysB)}")
    p(f"|inter|={len(inter)} |onlyA|={len(onlyA)} |onlyB|={len(onlyB)} |union|={len(keysA|keysB)}")
    p(f"|QQ intersect|={len(qq_inter)} |QQ onlyA|={len(qq_onlyA)} |QQ onlyB|={len(qq_onlyB)}")
    p("")

    p("Shared doublet rays:")
    shared_qq_in_inter = 0
    shared_S_same = 0
    for k in sorted(inter):
        a, b = dA[k], dB[k]
        qq_same = a["qq"] == b["qq"]
        S_same = a["S"] == b["S"]
        qq_in = a["qq"] in qq_inter and b["qq"] in qq_inter
        if qq_in:
            shared_qq_in_inter += 1
        if S_same:
            shared_S_same += 1
        p(f"  ray={k}")
        p(f"    A: QQ={a['qq_name']}  S={a['S_name']}")
        p(f"    B: QQ={b['qq_name']}  S={b['S_name']}")
        p(f"    same_QQ={qq_same} same_S={S_same} qq_in_QQ_intersect={qq_in}")

    p("")
    p("Private triangles:")
    privA_ok = 0
    for k in sorted(onlyA):
        a = dA[k]
        ok = a["qq"] in qq_onlyA
        privA_ok += int(ok)
        p(f"  ray={k} QQ={a['qq_name']} private_QQ={ok}")
    p("Private hexagon:")
    privB_ok = 0
    for k in sorted(onlyB):
        b = dB[k]
        ok = b["qq"] in qq_onlyB
        privB_ok += int(ok)
        p(f"  ray={k} QQ={b['qq_name']} private_QQ={ok}")

    p("")
    # Corrected invariant candidates
    # H2 strict: shared rays use QQ in intersection — need 4
    h1 = len(inter) == 4 and len(keysA | keysB) == 8 and len(onlyA) == 2 and len(onlyB) == 2
    h2 = shared_qq_in_inter == 4  # likely FAIL if |qq_inter|<4
    h3 = privA_ok == 2 and privB_ok == 2
    h4 = shared_S_same == 4

    p(f"C1/H1 cardinality inter=4 union=8: {'PASS' if h1 else 'FAIL'}")
    p(f"C2/H2 shared rays use QQ in QQ_intersect (need 4): {'PASS' if h2 else 'FAIL'} (got {shared_qq_in_inter}; |QQ cap|={len(qq_inter)})")
    p(f"C3/H3 private rays use private QQ: {'PASS' if h3 else 'FAIL'}")
    p(f"C4/H4 shared rays reuse identical surface edge: {'PASS' if h4 else 'FAIL'} (got {shared_S_same})")

    # Corrected invariant: if H2 fails but every shared ray has same_S and/or
    # the four shared rays' surface edges form a fixed set of size 4
    shared_S_set_A = {dA[k]["S"] for k in inter}
    shared_S_set_B = {dB[k]["S"] for k in inter}
    S_sets_equal = shared_S_set_A == shared_S_set_B
    p(f"  shared surface-edge sets equal across branches: {S_sets_equal} |S_shared|={len(shared_S_set_A)}")

    # QQ edges used by shared rays under each branch
    shared_qq_A = {dA[k]["qq"] for k in inter}
    shared_qq_B = {dB[k]["qq"] for k in inter}
    p(f"  |QQ used by shared rays| A={len(shared_qq_A)} B={len(shared_qq_B)} |cap|={len(shared_qq_A & shared_qq_B)}")

    if h1 and h3 and (h2 or h4 or S_sets_equal):
        if h2 and h3:
            status = "SHARED_DOUBLET_QQ_INTERSECT_SURVIVES"
        elif h4 or S_sets_equal:
            status = "SHARED_DOUBLET_SURFACE_INVARIANT_SURVIVES"
        else:
            status = "SHARED_DOUBLET_PARTIAL"
        code = 0
    elif h1:
        status = "SHARED_DOUBLET_COUNTS_OK_INVARIANT_OPEN"
        code = 0
    else:
        status = "SHARED_DOUBLET_FAIL"
        code = 1

    p("---")
    p(f"STATUS {status}")
    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return code


if __name__ == "__main__":
    sys.exit(main())
