#!/usr/bin/env python3
"""NSEQ10 — QQ 2-factor census, C3×inversion survivors, QQ∩ core, N=184 diagnostic."""
from __future__ import annotations

import hashlib
import itertools
import math
import statistics
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
AME = ROOT / "Datasets" / "nuclear" / "AME2020_mass_excess.txt"
OUT = ROOT / ".audit-tmp" / "nseq10_run.txt"
EXPECTED_SHA = "e8599c6d7f724fac91934e59f1b9de8fb8f63e820f4b39456b790665ed2a3307"

# Q labels as axis unit vectors (tuple keys)
QX = (1.0, 0.0, 0.0)
MX = (-1.0, 0.0, 0.0)
QY = (0.0, 1.0, 0.0)
MY = (0.0, -1.0, 0.0)
QZ = (0.0, 0.0, 1.0)
MZ = (0.0, 0.0, -1.0)
QS = [QX, MX, QY, MY, QZ, MZ]


def eid(a, b):
    return tuple(sorted((a, b)))


def all_qq_edges():
    """12 right-angle pairs among ±x,±y,±z (exclude antipodes)."""
    edges = []
    for a, b in itertools.combinations(QS, 2):
        if abs(sum(a[i] * b[i] for i in range(3))) < 1e-12:  # dot=0
            edges.append(eid(a, b))
    return edges


def is_2factor(edge_set, qq_all):
    """Each of 6 Q vertices has degree exactly 2 in edge_set."""
    if len(edge_set) != 6:
        return False
    deg = {q: 0 for q in QS}
    for e in edge_set:
        if e not in qq_all:
            return False
        u, v = e
        deg[u] += 1
        deg[v] += 1
    return all(d == 2 for d in deg.values())


def enumerate_2factors(qq_all):
    """All 6-edge subsets that are 2-factors (C(12,6)=924 — fine)."""
    out = []
    for combo in itertools.combinations(qq_all, 6):
        s = frozenset(combo)
        if is_2factor(s, set(qq_all)):
            out.append(s)
    return out


def rot_c3(v):
    """Axis cycle x→y→z→x (NSEQ06 C3 on square normals)."""
    return (v[2], v[0], v[1])


def invert(v):
    return (-v[0], -v[1], -v[2])


def map_edge(e, fn):
    a, b = e
    return eid(fn(a), fn(b))


def orbit_invariant(edge_set):
    """Invariant under all C3 turns × inversion (NSEQ06 group)."""
    s = set(edge_set)

    def apply(fn):
        return {map_edge(e, fn) for e in s}

    for turns in range(3):
        for inv in (False, True):
            def fn(v, t=turns, flip=inv):
                out = v
                for _ in range(t):
                    out = rot_c3(out)
                if flip:
                    out = invert(out)
                return out

            if apply(fn) != s:
                return False
    return True


def connected_components_Q(edge_set) -> int:
    adj = {q: set() for q in QS}
    for a, b in edge_set:
        adj[a].add(b)
        adj[b].add(a)
    seen = set()
    comps = 0
    for start in QS:
        if start in seen:
            continue
        comps += 1
        stack = [start]
        seen.add(start)
        while stack:
            u = stack.pop()
            for v in adj[u]:
                if v not in seen:
                    seen.add(v)
                    stack.append(v)
    return comps


def branch_triangles():
    """NSEQ05 polar triangle-pair construction (diagnostic overlap)."""
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
    """NSEQ05 polar hexagon construction (diagnostic overlap)."""
    cyc = [QX, QY, QZ, MX, MY, MZ]
    return frozenset(eid(cyc[k], cyc[(k + 1) % 6]) for k in range(6))


# ── AME diagnostic (NSEQ09 route) ───────────────────────────────────────────

def sha256_file(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as fh:
        for chunk in iter(lambda: fh.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def load_ame_binding_experimental(path: Path) -> dict[tuple[int, int], float]:
    out: dict[tuple[int, int], float] = {}
    for ln in path.read_text(encoding="latin-1").splitlines():
        if len(ln) < 25:
            continue
        try:
            Z = int(ln[9:14])
            A = int(ln[14:19])
        except ValueError:
            continue
        tail = ln[23:]
        bpos = len(tail)
        for mark in ("B-", "B+", " B "):
            i = tail.find(mark)
            if i != -1:
                bpos = min(bpos, i)
        if "#" in tail[:bpos]:
            continue
        toks = tail.replace("*", " ").split()
        bidx = None
        for i, t in enumerate(toks):
            if t in ("B-", "B+", "B", "B-x"):
                bidx = i
                break
        if bidx is None or bidx < 3:
            continue
        try:
            ba_kev = float(toks[bidx - 2])
        except ValueError:
            continue
        if 0.0 < ba_kev < 12000.0:
            out[(Z, A)] = (ba_kev / 1000.0) * A
    return out


def median_D(bind, N_target):
    by_zn = {}
    for (Z, A), Btot in bind.items():
        N = A - Z
        if Z % 2 == 0 and N % 2 == 0 and Z >= 2 and N >= 2:
            by_zn[(Z, N)] = Btot
    S2n = {}
    for (Z, N), Btot in by_zn.items():
        if (Z, N - 2) in by_zn:
            S2n[(Z, N)] = Btot - by_zn[(Z, N - 2)]
    vals = []
    for (Z, N), s in S2n.items():
        if N != N_target:
            continue
        if (Z, N + 2) in S2n:
            vals.append(s - S2n[(Z, N + 2)])
    if len(vals) < 3:
        return None, len(vals)
    return float(statistics.median(vals)), len(vals)


def fmt_edge(e):
    def lab(v):
        ax = "xyz"[max(range(3), key=lambda i: abs(v[i]))]
        sgn = "+" if v[max(range(3), key=lambda i: abs(v[i]))] > 0 else "-"
        return f"{sgn}{ax}"

    a, b = e
    return f"{lab(a)}-{lab(b)}"


def main() -> int:
    lines: list[str] = []

    def p(s: str = "") -> None:
        lines.append(s)
        print(s)

    p("NSEQ10 QQ branch selection rule")
    p("pre-reg: NSEQ10_PRE_REGISTRATION.md")
    p("")

    qq_all = all_qq_edges()
    p(f"|QQ candidates|={len(qq_all)} (expect 12)")
    factors = enumerate_2factors(qq_all)
    p(f"|2-factors|={len(factors)} (expect 20)")
    c1 = len(qq_all) == 12 and len(factors) == 20
    p(f"C1 census: {'PASS' if c1 else 'FAIL'}")

    survivors = [f for f in factors if orbit_invariant(f)]
    p(f"|C3 x inversion invariant|={len(survivors)} (expect 2)")
    comps = sorted(
        connected_components_Q(f) for f in survivors
    ) if survivors else []
    p(f"  survivor component counts: {comps} (expect [1, 2])")
    tri, hex_ = branch_triangles(), branch_hexagon()
    polar_overlap = sum(1 for f in survivors if f in (tri, hex_))
    p(f"  overlap with NSEQ05 polar triangle/hexagon pair: {polar_overlap}/2")
    for i, f in enumerate(survivors):
        kind = "triangle-pair" if connected_components_Q(f) == 2 else "six-cycle"
        p(f"  survivor[{i}] {kind}: {[fmt_edge(e) for e in sorted(f)]}")
    c2 = len(survivors) == 2 and comps == [1, 2]
    p(f"C2 symmetry cut: {'PASS' if c2 else 'FAIL'}")

    if len(survivors) == 2:
        core = survivors[0] & survivors[1]
    else:
        core = frozenset()
    p(f"|S1 cap S2|={len(core)} (expect 0 under partition)")
    if len(survivors) == 2:
        a, b = survivors[0], survivors[1]
        union = a | b
        unused = set(qq_all) - union
        c3 = (
            len(a) == 6
            and len(b) == 6
            and len(core) == 0
            and len(union) == 12
            and len(unused) == 0
        )
        p(f"  |union|={len(union)} |unused|={len(unused)}")
    else:
        c3 = False
    p(f"C3 complementary partition of 12 QQ: {'PASS' if c3 else 'FAIL'}")

    # C4 polar diagnostic
    tri, hex_ = branch_triangles(), branch_hexagon()
    polar_cap = tri & hex_
    tri_in = tri in survivors
    hex_in = hex_ in survivors
    p(f"  polar triangles in survivors: {tri_in}")
    p(f"  polar hexagon in survivors: {hex_in}")
    p(f"  polar |cap|={len(polar_cap)} (expect 4)")
    c4 = tri_in and (not hex_in) and len(polar_cap) == 4
    p(f"C4 polar vs symmetry diagnostic: {'PASS' if c4 else 'FAIL'}")

    p("")
    p("C5 N=168 / N=184 diagnostic")
    sha = sha256_file(AME)
    p(f"  AME hash match: {sha == EXPECTED_SHA}")
    c5 = None
    c5_note = "OPEN"
    if sha == EXPECTED_SHA:
        bind = load_ame_binding_experimental(AME)
        for N, cls in ((168, "OPEN_D"), (184, "SEAL_fwd")):
            med, nZ = median_D(bind, N)
            if med is None:
                p(f"  N={N} ({cls}): INSUFFICIENT nZ={nZ}")
            else:
                p(f"  N={N} ({cls}): medD={med:+.3f} MeV nZ={nZ}")
        med168, n168 = median_D(bind, 168)
        med184, n184 = median_D(bind, 184)
        if med168 is not None and med184 is not None:
            # SEAL-like at 184 (>= control~1 + margin): use med184 >= 2.0 and med168 < med184 - 1
            c5 = (med184 >= 2.0) and (med184 - med168 >= 1.0)
            c5_note = "PASS" if c5 else "FAIL"
        else:
            c5 = None
            c5_note = "OPEN (sparse)"
    else:
        c5_note = "OPEN (provenance)"
    p(f"C5 forward gap diagnostic: {c5_note}")

    p("")
    p("---")
    if c1 and c2 and c3 and c4:
        status = "QQ_BRANCH_SELECTION_RULE_SURVIVES"
        if c5 is True:
            status += "__N184_GAP_PASS"
        elif c5 is False:
            status += "__N184_GAP_FAIL"
        else:
            status += "__N184_SPARSE"
        code = 0
    else:
        status = "QQ_BRANCH_SELECTION_FAIL"
        code = 1
    p(f"STATUS {status}")

    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return code


if __name__ == "__main__":
    sys.exit(main())
