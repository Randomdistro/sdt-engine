#!/usr/bin/env python3
"""NSEQ05 — pure-shell expansion + stella→cuboct→14→42 (pre-registered)."""
from __future__ import annotations

import math
import sys
from collections import defaultdict
from itertools import combinations
from typing import Iterable

TOL = 1e-9
INV_SQRT3 = 1.0 / math.sqrt(3.0)


def near(a: float, b: float, tol: float = TOL) -> bool:
    return abs(a - b) <= tol


def unit(v: tuple[float, float, float]) -> tuple[float, float, float]:
    n = math.sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2])
    return (v[0] / n, v[1] / n, v[2] / n)


def dot(a, b) -> float:
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]


def add(a, b):
    return (a[0] + b[0], a[1] + b[1], a[2] + b[2])


def sub(a, b):
    return (a[0] - b[0], a[1] - b[1], a[2] - b[2])


def scale(a, s):
    return (a[0] * s, a[1] * s, a[2] * s)


def lat_deg(v) -> float:
    return math.degrees(math.asin(max(-1.0, min(1.0, v[2]))))


# ── capacity forms (laws.hpp) ───────────────────────────────────────────
def F(n: int) -> int:
    return (n + 1) * (n + 2)


def B(n: int) -> int:
    return 2 * (n + 1)


def R(n: int) -> int:
    return n * (n + 1)


def gate_c1() -> bool:
    print("C1 - pure-shell expansion after N=20")
    seq = [20]
    steps = [
        ("T", B(3)),  # 8
        ("D", R(3)),  # 12
        ("T", B(4)),  # 10
        ("D", R(4)),  # 20
        ("T", B(5)),  # 12
        ("D", R(5)),  # 30
        ("T", B(6)),  # 14
        ("D", R(6)),  # 42
        ("T", B(7)),  # 16
    ]
    for kind, dn in steps:
        seq.append(seq[-1] + dn)
        print(f"  +{kind}{dn} -> N={seq[-1]}")
    magic = {28, 50, 82, 126}
    intermediates = {40, 70, 112, 168}
    hit_magic = magic.issubset(set(seq))
    hit_inter = intermediates.issubset(set(seq))
    hit_184 = seq[-1] == 184
    # grouped increments that hide pure shells
    grouped = [
        (20, 28, B(3)),
        (28, 50, R(3) + B(4)),
        (50, 82, R(4) + B(5)),
        (82, 126, R(5) + B(6)),
        (126, 184, R(6) + B(7)),
    ]
    grouped_ok = all(b - a == g for a, b, g in grouped)
    ok = hit_magic and hit_inter and hit_184 and grouped_ok
    print(f"  magic subset: {hit_magic}")
    print(f"  intermediates subset: {hit_inter}")
    print(f"  N=184: {hit_184}")
    print(f"  grouped increments match engine: {grouped_ok}")
    print(f"  C1: {'PASS' if ok else 'FAIL'}")
    return ok


def gate_c2() -> bool:
    print("C2 - face-rule vs link-rule for deuteron counts")
    # Triangulated-cube-style face growth (wrong continuation): 12,16,20,...
    # = 4(n+2) for n=1,2,3... starting at first post-T8 shell index
    face = [4 * (k + 2) for k in range(1, 4)]  # 12,16,20
    link = [R(n) for n in (3, 4, 5)]  # 12,20,30
    target = [12, 20, 30]
    face_ok = face != target
    link_ok = link == target
    print(f"  face sequence: {face}  != target? {face_ok}")
    print(f"  link sequence: {link}  == target? {link_ok}")
    ok = face_ok and link_ok
    print(f"  C2: {'PASS' if ok else 'FAIL'}")
    return ok


def stella_vertices() -> list[tuple[float, float, float]]:
    # Dual regular tetrahedra = stella octangula vertices = cube (±1,±1,±1)
    verts = []
    for sx in (-1, 1):
        for sy in (-1, 1):
            for sz in (-1, 1):
                verts.append(unit((sx, sy, sz)))
    return verts


def nearest_links(verts: list[tuple[float, float, float]]):
    # Cube edges: chord length sqrt(2) before unit-normalization of verts;
    # after unit: distance between adjacent = 2/√3 * something...
    # Adjacent cube corners share two coordinates of equal sign pattern with
    # Hamming distance 1 in the ±1 cube. Use angular nearest-neighbour:
    # each vertex has degree 3 at exact cube-edge angle.
    pairs = []
    for i, j in combinations(range(len(verts)), 2):
        d = math.sqrt(sum((verts[i][k] - verts[j][k]) ** 2 for k in range(3)))
        pairs.append((d, i, j))
    pairs.sort()
    # 12 cube edges are the shortest 12 distinct pairs (each appears once)
    # Minimum distance among unit(±1,±1,±1): between Hamming-1 = √(4/3)=1.1547...
    dmin = pairs[0][0]
    edges = [(i, j) for d, i, j in pairs if near(d, dmin, 1e-8)]
    return edges, dmin


def gate_c3() -> bool:
    print("C3 - T8 stella -> 12 cuboct midpoints (3+6+3)")
    verts = stella_vertices()
    edges, dmin = nearest_links(verts)
    print(f"  |V|={len(verts)} |E_nearest|={len(edges)} dmin={dmin:.6f}")
    mids = [unit(add(verts[i], verts[j])) for i, j in edges]
    # Polar axis through opposite stella vertices: +z and -z of body diagonal
    # Use (1,1,1) as north pole direction
    pole = unit((1.0, 1.0, 1.0))
    # Rotate so pole → +z for latitude census: build orthonormal frame
    # Householder-ish: project
    def to_pole_frame(v):
        # orthonormal basis with e3 = pole
        e3 = pole
        # pick helper not parallel
        helper = (1.0, 0.0, 0.0) if abs(e3[0]) < 0.9 else (0.0, 1.0, 0.0)
        e1 = unit(sub(helper, scale(e3, dot(helper, e3))))
        e2 = unit(
            (
                e3[1] * e1[2] - e3[2] * e1[1],
                e3[2] * e1[0] - e3[0] * e1[2],
                e3[0] * e1[1] - e3[1] * e1[0],
            )
        )
        return (dot(v, e1), dot(v, e2), dot(v, e3))

    framed = [to_pole_frame(m) for m in mids]
    lats = sorted(lat_deg(m) for m in framed)
    # Bucket: north tropical / equator / south tropical
    north = sum(1 for L in lats if L > 20)
    eq = sum(1 for L in lats if abs(L) <= 20)
    south = sum(1 for L in lats if L < -20)
    print(f"  latitude split N/E/S = {north}/{eq}/{south}")
    print(f"  latitudes(deg) = {[round(L, 3) for L in lats]}")
    # Cuboctahedron: 12 vertices; expected 3+6+3 under this polar axis
    ok = len(edges) == 12 and (north, eq, south) == (3, 6, 3)
    print(f"  C3: {'PASS' if ok else 'FAIL'}")
    return ok


def cuboct_face_normals() -> list[tuple[float, float, float]]:
    """14 cuboctahedral face normals: 8 triangular + 6 square."""
    tris = []
    for sx in (-1, 1):
        for sy in (-1, 1):
            for sz in (-1, 1):
                tris.append(unit((sx, sy, sz)))
    squares = [
        unit((1, 0, 0)),
        unit((-1, 0, 0)),
        unit((0, 1, 0)),
        unit((0, -1, 0)),
        unit((0, 0, 1)),
        unit((0, 0, -1)),
    ]
    return tris + squares


def gate_c4() -> bool:
    print("C4 - 14 face normals: poles + arcsin(1/sqrt3) + arcsin(1/3)")
    normals = cuboct_face_normals()
    print(f"  |normals|={len(normals)}")
    pole = unit((0.0, 0.0, 1.0))
    # Orient so a square normal is the pole (standard): already have ±z
    # Square-pole frame is DIAGNOSTIC only (shows 0° belt). Author seating uses
    # the triangle pole; PASS/FAIL below is triangle-pole only.
    lats = sorted(lat_deg(n) for n in normals)
    a35 = math.degrees(math.asin(INV_SQRT3))
    a19 = math.degrees(math.asin(1.0 / 3.0))
    print(f"  target |lat| (triangle pole) ≈ 90, {a35:.3f}, {a19:.3f}")
    print(f"  square-pole latitudes (diagnostic) = {[round(L, 3) for L in lats]}")

    def count_near(target: float) -> int:
        return sum(1 for L in lats if near(abs(L), target, 0.05))

    # With z-pole = square normal: poles ±90 (2), ±35.264 from remaining
    # Actually: square normals give ±90 and four equator 0°; triangle normals
    # give ±arcsin(1/√3).
    # Author's polar axis through *stella/triangle* poles gives different split.
    # Re-frame with triangle pole (1,1,1):
    pole_t = unit((1.0, 1.0, 1.0))

    def frame(v):
        e3 = pole_t
        helper = (1.0, 0.0, 0.0) if abs(e3[0]) < 0.9 else (0.0, 1.0, 0.0)
        e1 = unit(sub(helper, scale(e3, dot(helper, e3))))
        e2 = (
            e3[1] * e1[2] - e3[2] * e1[1],
            e3[2] * e1[0] - e3[0] * e1[2],
            e3[0] * e1[1] - e3[1] * e1[0],
        )
        e2 = unit(e2)
        return (dot(v, e1), dot(v, e2), dot(v, e3))

    lats_t = sorted(lat_deg(frame(n)) for n in normals)
    print(f"  triangle-pole latitudes = {[round(L, 3) for L in lats_t]}")
    n90 = sum(1 for L in lats_t if near(abs(L), 90.0, 0.05))
    n35 = sum(1 for L in lats_t if near(abs(L), a35, 0.05))
    n19 = sum(1 for L in lats_t if near(abs(L), a19, 0.05))
    print(f"  counts |lat|~90/35.264/19.471 = {n90}/{n35}/{n19}")
    # Expected: 2 poles + 6 at 35.264 + 6 at 19.471
    ok = len(normals) == 14 and n90 == 2 and n35 == 6 and n19 == 6
    print(f"  C4: {'PASS' if ok else 'FAIL'}")
    return ok


def build_face_graph(branch: str):
    """
    14 sites = 8 triangle + 6 square face normals.
    Relations:
      24 T–Q edge adjacencies (each triangle meets 3 squares; 8*3=24)
      12 T–T vertex adjacencies (cube dual edges among triangle normals)
      6  Q–Q chosen by polar branch
    """
    tris = []
    for sx in (-1, 1):
        for sy in (-1, 1):
            for sz in (-1, 1):
                tris.append(("T", (sx, sy, sz)))
    squares = [
        ("Q", (1, 0, 0)),
        ("Q", (-1, 0, 0)),
        ("Q", (0, 1, 0)),
        ("Q", (0, -1, 0)),
        ("Q", (0, 0, 1)),
        ("Q", (0, 0, -1)),
    ]
    nodes = tris + squares
    idx = {nodes[i][1]: i for i in range(len(nodes))}
    edges = set()

    def add_edge(a, b):
        i, j = idx[a], idx[b]
        if i == j:
            return
        edges.add((min(i, j), max(i, j)))

    # T–Q: triangle (sx,sy,sz) meets the three axis squares of matching signs
    for _, (sx, sy, sz) in tris:
        add_edge((sx, sy, sz), (sx, 0, 0))
        add_edge((sx, sy, sz), (0, sy, 0))
        add_edge((sx, sy, sz), (0, 0, sz))

    # T–T: Hamming distance 1 among cube corners
    for (_, a), (_, b) in combinations(tris, 2):
        ham = sum(1 for k in range(3) if a[k] != b[k])
        if ham == 1:
            add_edge(a, b)

    # Q–Q polar branches on the six axis directions
    # Branch A: two same-hemisphere triangles among ±x±y at z>0 and z<0 style
    # Encode as: among equatorial cycle (±x,±y) take opposite-edge pairs, plus poles?
    # Pre-registered: "six square–square relations are either two same-hemisphere
    # triangles or one mixed-hemisphere 6-cycle"
    qx = [(1, 0, 0), (-1, 0, 0), (0, 1, 0), (0, -1, 0), (0, 0, 1), (0, 0, -1)]
    if branch == "triangles":
        # two triangles: +z with +x,+y ; -z with -x,-y ; and +x with -y ; -x with +y
        # Actually "two same-hemisphere triangles":
        # north: +z–+x–+y ; south: -z––x––y  that's 6 edges
        add_edge((0, 0, 1), (1, 0, 0))
        add_edge((0, 0, 1), (0, 1, 0))
        add_edge((1, 0, 0), (0, 1, 0))
        add_edge((0, 0, -1), (-1, 0, 0))
        add_edge((0, 0, -1), (0, -1, 0))
        add_edge((-1, 0, 0), (0, -1, 0))
    elif branch == "hexagon":
        # mixed-hemisphere 6-cycle through all six squares
        cyc = [
            (1, 0, 0),
            (0, 1, 0),
            (0, 0, 1),
            (-1, 0, 0),
            (0, -1, 0),
            (0, 0, -1),
        ]
        for k in range(6):
            add_edge(cyc[k], cyc[(k + 1) % 6])
    else:
        raise ValueError(branch)

    return nodes, edges


def graph_stats(n: int, edges: set) -> tuple[bool, list[int], bool]:
    deg = [0] * n
    for i, j in edges:
        deg[i] += 1
        deg[j] += 1
    # connectivity BFS
    adj = defaultdict(list)
    for i, j in edges:
        adj[i].append(j)
        adj[j].append(i)
    seen = {0}
    stack = [0]
    while stack:
        u = stack.pop()
        for v in adj[u]:
            if v not in seen:
                seen.add(v)
                stack.append(v)
    connected = len(seen) == n
    regular6 = all(d == 6 for d in deg)
    return regular6, deg, connected


def gate_c5() -> bool:
    print("C5 - 14->42 face-graph, both polar Q-Q branches")
    ok_all = True
    for branch in ("triangles", "hexagon"):
        nodes, edges = build_face_graph(branch)
        # Count relation classes approximately via size
        E = len(edges)
        regular6, deg, connected = graph_stats(len(nodes), edges)
        print(
            f"  branch={branch}: V={len(nodes)} E={E} "
                f"regular6={regular6} connected={connected} deg={deg}"
        )
        # Must have E=42 and 2E=V*6
        ok = E == 42 and regular6 and connected and 2 * E == len(nodes) * 6
        ok_all = ok_all and ok
        print(f"    -> {'PASS' if ok else 'FAIL'}")
    # Distinctness: edge sets differ
    _, eA = build_face_graph("triangles")
    _, eB = build_face_graph("hexagon")
    distinct = eA != eB
    print(f"  branches distinct: {distinct}")
    ok_all = ok_all and distinct
    print(f"  C5: {'PASS' if ok_all else 'FAIL'}")
    return ok_all


def gate_c6() -> bool:
    print("C6 - diagnostic: E=42 > 3V-6=36 (OPEN topology debt)")
    V, E = 14, 42
    bound = 3 * V - 6
    print(f"  3V-6={bound}; E={E}; excess={E - bound}")
    print("  STATUS OPEN - not a spherical simple polyhedron edge graph")
    print("  C6: RECORDED (diagnostic)")
    return True  # diagnostic always "records"


def main() -> int:
    print("NSEQ05 pure-shell / stella-cuboct-14-42")
    print("pre-reg: NSEQ05_PRE_REGISTRATION.md")
    results = {
        "C1": gate_c1(),
        "C2": gate_c2(),
        "C3": gate_c3(),
        "C4": gate_c4(),
        "C5": gate_c5(),
        "C6": gate_c6(),
    }
    core = all(results[k] for k in ("C1", "C2", "C3", "C4", "C5"))
    print("---")
    for k, v in results.items():
        print(f"  {k}: {'PASS' if v else 'FAIL'}")
    if core:
        print("STATUS PURE_SHELL_STELLA_CUBOCT_RELATIONS_SURVIVE")
        return 0
    print("STATUS RELATION_EXCLUDED")
    return 1


if __name__ == "__main__":
    sys.exit(main())
