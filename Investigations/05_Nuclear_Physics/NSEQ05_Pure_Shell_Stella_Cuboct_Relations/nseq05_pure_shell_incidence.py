#!/usr/bin/env python3
"""NSEQ05 — pure-shell sequence, V/E vs face, stella→cuboct→14, 14→42 graph."""
from __future__ import annotations

import itertools
import math
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
OUT = ROOT / ".audit-tmp" / "nseq05_run.txt"

Vec = tuple[float, float, float]


def vadd(a: Vec, b: Vec) -> Vec:
    return (a[0] + b[0], a[1] + b[1], a[2] + b[2])


def vsub(a: Vec, b: Vec) -> Vec:
    return (a[0] - b[0], a[1] - b[1], a[2] - b[2])


def vscale(a: Vec, s: float) -> Vec:
    return (a[0] * s, a[1] * s, a[2] * s)


def vdot(a: Vec, b: Vec) -> float:
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]


def vnorm(a: Vec) -> float:
    return math.sqrt(vdot(a, a))


def vunit(a: Vec) -> Vec:
    n = vnorm(a)
    return (a[0] / n, a[1] / n, a[2] / n)


def lat_deg(d: Vec) -> float:
    return math.degrees(math.asin(max(-1.0, min(1.0, d[2]))))


def ang_deg(a: Vec, b: Vec) -> float:
    c = max(-1.0, min(1.0, vdot(vunit(a), vunit(b))))
    return math.degrees(math.acos(c))


def nearly(a: float, b: float, tol: float = 1e-9) -> bool:
    return abs(a - b) <= tol


def uniq_dirs(dirs: list[Vec], tol: float = 1e-9) -> list[Vec]:
    out: list[Vec] = []
    for d in dirs:
        u = vunit(d)
        if all(vnorm(vsub(u, o)) > tol for o in out):
            out.append(u)
    return out


# ── capacities ─────────────────────────────────────────────────────────────

def B(n: int) -> int:
    return 2 * (n + 1)


def R(n: int) -> int:
    return n * (n + 1)


def F(n: int) -> int:
    return (n + 1) * (n + 2)


PURE_SHELLS = [
    ("D", 6, None),
    ("D", 12, "pre20"),
    ("T", 8, 3),
    ("D", 12, 3),
    ("T", 10, 4),
    ("D", 20, 4),
    ("T", 12, 5),
    ("D", 30, 5),
    ("T", 14, 6),
    ("D", 42, 6),
    ("T", 16, 7),
]


def pure_shell_cumulatives() -> list[tuple[str, int, int]]:
    n = 2
    rows = [("α", 2, 2)]
    for sp, cap, _ in PURE_SHELLS:
        n += cap
        rows.append((f"{sp}{cap}", cap, n))
    return rows


# ── T8 stella / dual tetra ─────────────────────────────────────────────────

def t8_stella() -> list[Vec]:
    """Polar-aligned dual tetrahedra = cube vertices with body? face? —
    vertices (±1,±1,±1) with polar axis through (1,1,1)-type after rotation
    so poles are ±z. Equivalent construction used in NSEQ02."""
    z_base = 1.0 / 3.0
    rho = math.sqrt(1.0 - z_base * z_base)
    seats = [(0.0, 0.0, 1.0), (0.0, 0.0, -1.0)]
    for k in range(3):
        th = k * 2.0 * math.pi / 3.0
        seats.append(vunit((rho * math.cos(th), rho * math.sin(th), -z_base)))
    for k in range(3):
        th = math.pi / 3.0 + k * 2.0 * math.pi / 3.0
        seats.append(vunit((rho * math.cos(th), rho * math.sin(th), +z_base)))
    return seats


def cube_vertices_aligned() -> list[Vec]:
    """Same 8 directions as cube corners with space diagonal → z after rotation.
    For link test we use explicit cube then rotate so (1,1,1) → +z."""
    s = 1.0 / math.sqrt(3.0)
    raw = [
        (s, s, s),
        (s, -s, -s),
        (-s, s, -s),
        (-s, -s, s),
        (-s, -s, -s),
        (-s, s, s),
        (s, -s, s),
        (s, s, -s),
    ]
    # Rotate (1,1,1) to z: use orthonormal frame
    z_hat = vunit((1.0, 1.0, 1.0))
    # pick x' perpendicular
    tmp = (1.0, -1.0, 0.0)
    x_hat = vunit(tmp)
    y_hat = vunit(
        (
            z_hat[1] * x_hat[2] - z_hat[2] * x_hat[1],
            z_hat[2] * x_hat[0] - z_hat[0] * x_hat[2],
            z_hat[0] * x_hat[1] - z_hat[1] * x_hat[0],
        )
    )
    out = []
    for p in raw:
        out.append(
            (
                vdot(p, x_hat),
                vdot(p, y_hat),
                vdot(p, z_hat),
            )
        )
    return [vunit(p) for p in out]


def nearest_links(verts: list[Vec]) -> list[tuple[int, int]]:
    """Edges at the minimal pairwise chord length (unique min)."""
    n = len(verts)
    dists = []
    for i, j in itertools.combinations(range(n), 2):
        dists.append((vnorm(vsub(verts[i], verts[j])), i, j))
    dmin = min(d for d, _, _ in dists)
    return [(i, j) for d, i, j in dists if nearly(d, dmin, 1e-9)]


def midpoints(verts: list[Vec], edges: list[tuple[int, int]]) -> list[Vec]:
    return [vunit(vadd(verts[i], verts[j])) for i, j in edges]


def cuboctahedron() -> list[Vec]:
    """12 vertices: even perms of (±1,±1,0)."""
    base = []
    for x, y in itertools.product((-1.0, 1.0), repeat=2):
        base.extend([(x, y, 0.0), (x, 0.0, y), (0.0, x, y)])
    return uniq_dirs(base)


def face_normals_cuboct() -> tuple[list[Vec], list[str]]:
    """8 triangular face normals (cube corners) + 6 square (axis)."""
    s = 1.0 / math.sqrt(3.0)
    tris = [
        (s, s, s),
        (s, -s, -s),
        (-s, s, -s),
        (-s, -s, s),
        (-s, -s, -s),
        (-s, s, s),
        (s, -s, s),
        (s, s, -s),
    ]
    sq = [
        (1.0, 0.0, 0.0),
        (-1.0, 0.0, 0.0),
        (0.0, 1.0, 0.0),
        (0.0, -1.0, 0.0),
        (0.0, 0.0, 1.0),
        (0.0, 0.0, -1.0),
    ]
    labels = ["T"] * 8 + ["Q"] * 6
    return [vunit(v) for v in tris + sq], labels


def rotate_to_poles(dirs: list[Vec], pole: Vec) -> list[Vec]:
    """Rotate so `pole` → +z."""
    z_hat = vunit(pole)
    # if already ±z
    if abs(z_hat[0]) < 1e-12 and abs(z_hat[1]) < 1e-12:
        return [vunit(d) for d in dirs]
    tmp = (0.0, 0.0, 1.0) if abs(z_hat[2]) < 0.9 else (1.0, 0.0, 0.0)
    x_hat = vunit(
        (
            tmp[1] * z_hat[2] - tmp[2] * z_hat[1],
            tmp[2] * z_hat[0] - tmp[0] * z_hat[2],
            tmp[0] * z_hat[1] - tmp[1] * z_hat[0],
        )
    )
    y_hat = vunit(
        (
            z_hat[1] * x_hat[2] - z_hat[2] * x_hat[1],
            z_hat[2] * x_hat[0] - z_hat[0] * x_hat[2],
            z_hat[0] * x_hat[1] - z_hat[1] * x_hat[0],
        )
    )
    out = []
    for p in dirs:
        out.append((vdot(p, x_hat), vdot(p, y_hat), vdot(p, z_hat)))
    return [vunit(p) for p in out]


# ── 14→42 contact graph ────────────────────────────────────────────────────

def build_tq_relations(dirs: list[Vec], labels: list[str]):
    """Classify pairwise angular relations among 14 face normals."""
    n = len(dirs)
    # Precompute all angles
    edges_tq = []  # triangle-square: face-edge adjacency of cuboct ~ arccos(1/√3)
    edges_tt = []
    edges_qq = []
    target_tq = math.degrees(math.acos(1.0 / math.sqrt(3.0)))  # ~54.735
    for i, j in itertools.combinations(range(n), 2):
        a = ang_deg(dirs[i], dirs[j])
        li, lj = labels[i], labels[j]
        if {li, lj} == {"T", "Q"} and nearly(a, target_tq, 1e-6):
            edges_tq.append((i, j))
        elif li == "T" and lj == "T" and nearly(a, 70.528779, 1e-4):
            # tetra angle among triangle normals that are vertex-adjacent
            edges_tt.append((i, j))
        elif li == "Q" and lj == "Q" and nearly(a, 90.0, 1e-6):
            edges_qq.append((i, j))
    return edges_tq, edges_tt, edges_qq


def polar_qq_branches(dirs: list[Vec], labels: list[str], edges_qq: list[tuple[int, int]]):
    """Two symmetry-preserving choices of 6 of 12 Q–Q right-angle pairs."""
    q_idx = [i for i, L in enumerate(labels) if L == "Q"]
    # Identify poles among Q: max |z| after aligning a T as pole? Use ±z axis squares.
    # Square normals are ±x,±y,±z. Poles = ±z indices.
    poles = [i for i in q_idx if abs(dirs[i][2]) > 0.9]
    eq = [i for i in q_idx if abs(dirs[i][2]) < 0.9]
    # Branch A: same-hemisphere triangles among equatorial Q? 
    # Author: six Q–Q are either two same-hemisphere triangles or one mixed 6-cycle.
    # Equatorial Q are ±x,±y (4) plus we need poles in Q set: ±z (2) = 6 Q total.
    # Actually all 6 squares: ±x,±y,±z. Q–Q at 90°: every distinct axis pair.
    # There are C(6,2)-3 antipodal = 15-3=12 right angles? Antipodal are 180°.
    # Pairs among 6 with 90°: each of 3 axes pairs with 4 others = 12/2 = 6? 
    # ±x with ±y (4), ±x with ±z (4), ±y with ±z (4) = 12. Yes 12 edges.
    #
    # Branch "two same-hemisphere triangles": 
    # north: +x,+y,+z triangle; south: -x,-y,-z triangle. That's 3+3=6.
    def idx_of(target: Vec) -> int:
        for i in q_idx:
            if vnorm(vsub(dirs[i], vunit(target))) < 1e-9:
                return i
        raise RuntimeError("missing Q")

    px, mx = idx_of((1, 0, 0)), idx_of((-1, 0, 0))
    py, my = idx_of((0, 1, 0)), idx_of((0, -1, 0))
    pz, mz = idx_of((0, 0, 1)), idx_of((0, 0, -1))
    branch_A = [
        (px, py),
        (py, pz),
        (pz, px),
        (mx, my),
        (my, mz),
        (mz, mx),
    ]
    # Branch B: mixed-hemisphere 6-cycle e.g. +x→+y→-x→-y→+x plus poles?
    # Author: one mixed-hemisphere 6-cycle. Try:
    # +z–+x–-z–-x–+z and +z–+y–-z–-y? that's 8. 
    # Cycle of 6: +x,+y,-x,-y,+z,-z interleaved:
    branch_B = [
        (px, py),
        (py, mx),
        (mx, my),
        (my, px),
        (pz, mz),  # antipodal — NOT 90°
    ]
    # Fix B: equatorial 4-cycle + two pole-equator pairs that close polar symmetry
    # +z to +x,+y; -z to -x,-y; and equatorial cross? 
    # Polar choice documented in I37: "two same-hemisphere triangles" vs "mixed 6-cycle"
    # Mixed 6-cycle on the 6 Q vertices of octahedron dual: the octahedron itself
    # has equatorial 4-cycle + ... 
    # Octahedron edges = the 12 Q–Q at 90°. Selecting a 6-cycle Hamiltonian:
    branch_B = [
        (px, py),
        (py, mx),
        (mx, my),
        (my, pz),
        (pz, mz),  # 180 — invalid
    ]
    # Hamiltonian 6-cycle on octahedron vertices using only edges:
    # +x → +y → +z → -x → -y → -z → +x
    branch_B = [
        (px, py),
        (py, pz),
        (pz, mx),
        (mx, my),
        (my, mz),
        (mz, px),
    ]
    # normalize undirected
    def norm_e(edges):
        return [tuple(sorted(e)) for e in edges]

    return norm_e(branch_A), norm_e(branch_B)


def graph_stats(n: int, edges: list[tuple[int, int]]):
    deg = [0] * n
    for i, j in edges:
        deg[i] += 1
        deg[j] += 1
    # connected?
    adj = defaultdict(set)
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
    return deg, len(seen) == n, len(edges)


def main() -> int:
    lines: list[str] = []

    def p(s: str = "") -> None:
        lines.append(s)
        print(s)

    p("=" * 64)
    p("NSEQ05 — Pure-shell incidence / stella→cuboct→14 / 14→42")
    p("=" * 64)

    # C1
    p("\nC1 — pure-shell ledger (species-by-species)")
    rows = pure_shell_cumulatives()
    magic = {28, 50, 82, 126, 184}
    for name, dN, N in rows:
        tag = "  MAGIC" if N in magic else ""
        p(f"  {name:6s}  +{dN:<3d} → N={N}{tag}")
    # verify key points
    byN = {N: name for name, _, N in rows}
    ok1 = (
        byN.get(28, "").startswith("T")
        and byN.get(50, "").startswith("T")
        and byN.get(82, "").startswith("T")
        and byN.get(126, "").startswith("T")
        and byN.get(40, "").startswith("D")
        and byN.get(184, "").startswith("T")
    )
    p(f"  C1: {'PASS' if ok1 else 'FAIL'}")

    # C2 H1/H2/H3
    p("\nC2 — V/E vs face discriminator")
    p(f"  H1: B(3..6)={ [B(n) for n in range(3,7)] }  R(3..6)={ [R(n) for n in range(3,7)] }")
    link_pred = [R(n) for n in range(3, 6)]
    face_pred = [12, 16, 20]  # triangulated-cube continuation from first lucky 12
    sched_D = [12, 20, 30]
    h2 = link_pred == sched_D
    h3 = face_pred == sched_D
    p(f"  H2 link E=n(n+1) → {link_pred} vs schedule {sched_D}: {'PASS' if h2 else 'FAIL'}")
    p(f"  H3 face 12→16→20 → {face_pred} vs schedule {sched_D}: {'FAIL (excluded)' if not h3 else 'UNEXPECTED PASS'}")
    # spherical polyhedron bound for T14→D42
    V, E = 14, 42
    max_simple = 3 * V - 6
    p(f"  Bound: simple spherical polyhedron E≤3V−6={max_simple}; D42 needs E={E} → {'EXCEEDS (3-D/crossing debt)' if E > max_simple else 'OK'}")
    ok2 = h2 and (not h3)
    p(f"  C2: {'PASS' if ok2 else 'FAIL'}")

    # C3 H4 stella links → cuboct
    p("\nC3 — H4/H5 stella → cuboct midpoints → 14 face normals")
    stella = t8_stella()
    # Also verify match to rotated cube vertices (same set)
    cube = cube_vertices_aligned()
    # Match sets
    def set_match(a: list[Vec], b: list[Vec], tol=1e-6) -> bool:
        if len(a) != len(b):
            return False
        used = [False] * len(b)
        for x in a:
            hit = False
            for j, y in enumerate(b):
                if not used[j] and vnorm(vsub(x, y)) < tol:
                    used[j] = True
                    hit = True
                    break
            if not hit:
                return False
        return True

    # Stella from NSEQ02 may equal cube after rotation — check pairwise angles
    stella_edges = nearest_links(stella)
    p(f"  T8 seats: {len(stella)}; nearest-link count: {len(stella_edges)}")
    mids = midpoints(stella, stella_edges)
    mids_u = uniq_dirs(mids)
    p(f"  unique midpoint directions: {len(mids_u)}")
    cub = cuboctahedron()
    # Align both to compare: rotate cuboct so a vertex? better compare as multisets of |z| and NN
    # Rotate cuboct to put a triangular? For 3+6+3 split, polar axis through opposite square? 
    # Author: polar axis through opposite stella vertices. Midpoints of cube edges with
    # that axis → cuboct with 3+6+3.
    stella_for_links = cube_vertices_aligned()  # exact cube with (111)→z
    edges_c = nearest_links(stella_for_links)
    mids_c = uniq_dirs(midpoints(stella_for_links, edges_c))
    p(f"  cube nearest links: {len(edges_c)} (expect 12)")
    p(f"  cube-edge midpoint dirs: {len(mids_c)} (expect 12)")
    # latitudes of mids
    lats = sorted(lat_deg(d) for d in mids_c)
    # bucket
    north = sum(1 for L in lats if L > 20)
    south = sum(1 for L in lats if L < -20)
    eq = sum(1 for L in lats if abs(L) <= 20)
    p(f"  midpoint lat split: N={north} eq={eq} S={south} (expect 3+6+3)")
    h4 = len(edges_c) == 12 and len(mids_c) == 12 and north == 3 and eq == 6 and south == 3

    # Also check NSEQ02 stella nearest links
    edges_s = nearest_links(stella)
    p(f"  NSEQ02-stella nearest links: {len(edges_s)} (cube edges if 12; tetra edges if 12 too — distinguish length)")
    # Cube has 12 equal short edges; dual tetra compound has 12 tetra edges longer? 
    # Stella octangula as 8 points: short edges = cube edges.
    h4 = h4 and len(edges_s) == 12

    fn, labels = face_normals_cuboct()
    # Align face normals so +z is a square normal (pole)
    fn_al = rotate_to_poles(fn, (0.0, 0.0, 1.0))
    # relabel after rotation — labels stay with original order; rotate dirs in place
    fn = fn_al
    # poles among 14
    poles = sum(1 for d in fn if abs(abs(d[2]) - 1.0) < 1e-9)
    lats14 = [lat_deg(d) for d in fn]
    band_19 = sum(1 for L in lats14 if nearly(abs(L), math.degrees(math.asin(1.0 / 3.0)), 1e-3))
    band_35 = sum(1 for L in lats14 if nearly(abs(L), math.degrees(math.asin(1.0 / math.sqrt(3.0))), 1e-3))
    p(f"  face normals: {len(fn)} (expect 14); labels T={labels.count('T')} Q={labels.count('Q')}")
    p(f"  poles(|lat|=90): {poles}; |lat|≈19.471°: {band_19}; |lat|≈35.264°: {band_35}")
    # Expect: 2 poles (from ±z squares) + 8 from tris at ±arcsin(1/√3)? + remaining
    # Triangle normals (±1,±1,±1)/√3 have |z|=1/√3 → lat ±35.264° (8 of them? only those with |z|=1/√3 all 8)
    # Square ±z = poles; ±x,±y have lat 0 — equatorial 4, not 19.471.
    # Author said: pole + 3 at 35.264 + 3 at 19.471 mirrored.
    # That requires polar axis through a TRIANGLE normal (stella vertex), not a square!
    fn0, labels0 = face_normals_cuboct()
    fn_t = rotate_to_poles(fn0, fn0[0])  # first triangle normal as pole
    lats_t = [lat_deg(d) for d in fn_t]
    poles_t = sum(1 for L in lats_t if abs(abs(L) - 90) < 1e-6)
    b19 = sum(1 for L in lats_t if nearly(abs(L), math.degrees(math.asin(1 / 3)), 5e-2))
    b35 = sum(1 for L in lats_t if nearly(abs(L), math.degrees(math.asin(1 / math.sqrt(3))), 5e-2))
    p(f"  with triangular polar axis: poles={poles_t} ~19.47°={b19} ~35.26°={b35}")
    h5 = len(fn0) == 14 and labels0.count("T") == 8 and labels0.count("Q") == 6 and poles_t == 2
    # Adjacency note
    p("  ADJACENCY: 14-set = T14 orientation, NOT immediate post-D12 triton shell (that is T10).")
    ok3 = h4 and h5
    p(f"  H4: {'PASS' if h4 else 'FAIL'}  H5: {'PASS' if h5 else 'FAIL'}")
    p(f"  C3: {'PASS' if ok3 else 'FAIL'}")

    # C4 H6 14→42
    p("\nC4 — H6 face-graph → 42 links")
    dirs14, lab14 = face_normals_cuboct()
    etq, ett, eqq = build_tq_relations(dirs14, lab14)
    p(f"  T−Q (~54.74°) relations: {len(etq)} (expect 24)")
    p(f"  T−T candidate relations: {len(ett)}")
    p(f"  Q−Q (90°) relations: {len(eqq)} (expect 12)")
    # TT: among 8 cube corners, angle arccos(1/3)≈70.53 are tetra edges within one tetra
    # Dual tetras: each tetra has C(4,2)=6 edges; two tetras → 12. Good.
    ett = []
    target_tt = math.degrees(math.acos(1.0 / 3.0))
    t_idx = [i for i, L in enumerate(lab14) if L == "T"]
    for i, j in itertools.combinations(t_idx, 2):
        a = ang_deg(dirs14[i], dirs14[j])
        if nearly(a, target_tt, 1e-6):
            ett.append(tuple(sorted((i, j))))
    p(f"  T−T (arccos 1/3) relations: {len(ett)} (expect 12)")

    brA, brB = polar_qq_branches(dirs14, lab14, eqq)
    p(f"  Q−Q branch A (2 hemisphere triangles): {len(brA)}")
    p(f"  Q−Q branch B (mixed 6-cycle): {len(brB)}")

    def run_branch(name, qq_sel):
        edges = [tuple(sorted(e)) for e in etq] + ett + qq_sel
        # unique
        edges = list({e for e in edges})
        deg, conn, ne = graph_stats(14, edges)
        ok = ne == 42 and all(d == 6 for d in deg) and conn
        p(f"  {name}: E={ne}  deg={deg}  connected={conn}  → {'PASS' if ok else 'FAIL'}")
        # midpoint direction multiplicity
        mids = [vunit(vadd(dirs14[i], dirs14[j])) for i, j in edges]
        # cluster by direction up to sign? author: 42 positions, 36 angular directions
        dirs_u = uniq_dirs(mids, tol=1e-7)
        # also count unsigned rays (identify antipodes)
        rays = []
        for d in mids:
            u = vunit(d)
            if any(vnorm(vsub(u, r)) < 1e-7 or vnorm(vadd(u, r)) < 1e-7 for r in rays):
                continue
            rays.append(u)
        p(f"    midpoint dirs (oriented unique)={len(dirs_u)}  unsigned rays={len(rays)}")
        return ok

    okA = run_branch("branch_A", brA)
    okB = run_branch("branch_B", brB)
    ok4 = okA and okB and len(etq) == 24 and len(ett) == 12
    p(f"  C4: {'PASS' if ok4 else 'FAIL'}")

    # Summary
    p("\n" + "=" * 64)
    all_ok = ok1 and ok2 and ok3 and ok4
    p(f"SUMMARY: {'PURE_SHELL_INCIDENCE_FORMALIZED' if all_ok else 'PARTIAL'}")
    p("  H3 face-rule EXCLUDED for deuteron schedule.")
    p("  T14=cuboct face normals; T10 remains distinct intermediate.")
    p("  D42: E=42>3V−6 ⇒ non-simple / internal contact OPEN debt noted.")
    p("=" * 64)

    OUT.parent.mkdir(parents=True, exist_ok=True)
    OUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    return 0 if all_ok else 2


if __name__ == "__main__":
    raise SystemExit(main())
