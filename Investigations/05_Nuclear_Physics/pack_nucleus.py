"""NSEQ05 spherical-tier packer — Python port of Release/HTML_SDT_Website/js/pack-nucleus.js.

Default dnn=1.45 fm, coulSpread=0 (lab PIP / shared JS). Not the sequencer slider
(1.45×R_p). Do not retune dnn to binding or RMS.
"""
from __future__ import annotations

import math
from typing import Any

R_P = 0.8414  # fm — same literal as pack-nucleus.js
PHI = (1.0 + math.sqrt(5.0)) / 2.0
GAM = 0.95
R_OPEN_SCALE = 1.05
R_CLOSE_SCALE = 0.95

SHELL_SEQ = [
    {"sp": "d", "cap": 6, "geom": "oct"},
    {"sp": "d", "cap": 12, "geom": "ico"},
    {"sp": "t", "cap": 8, "geom": "stella"},
    {"sp": "d", "cap": 12, "geom": "cuboct"},
    {"sp": "t", "cap": 10, "geom": "polar"},
    {"sp": "d", "cap": 20, "geom": "fib"},
    {"sp": "t", "cap": 12, "geom": "polar"},
    {"sp": "d", "cap": 30, "geom": "fib"},
    {"sp": "t", "cap": 14, "geom": "t14"},
    {"sp": "d", "cap": 42, "geom": "fib"},
    {"sp": "t", "cap": 16, "geom": "polar"},
    {"sp": "d", "cap": 56, "geom": "fib"},
    {"sp": "t", "cap": 18, "geom": "polar"},
]


def vnorm(v: list[float]) -> list[float]:
    l = math.hypot(v[0], v[1], v[2]) or 1.0
    return [v[0] / l, v[1] / l, v[2] / l]


def grammar(Z: int, A: int) -> tuple[int, int]:
    return 3 * Z - A - 2, A - 2 * Z


def dirs_oct() -> list[list[float]]:
    return [[1, 0, 0], [-1, 0, 0], [0, 1, 0], [0, -1, 0], [0, 0, 1], [0, 0, -1]]


def dirs_ico() -> list[list[float]]:
    return [
        vnorm(v)
        for v in [
            [0, 1, PHI],
            [0, -1, PHI],
            [0, 1, -PHI],
            [0, -1, -PHI],
            [1, PHI, 0],
            [-1, PHI, 0],
            [1, -PHI, 0],
            [-1, -PHI, 0],
            [PHI, 0, 1],
            [-PHI, 0, 1],
            [PHI, 0, -1],
            [-PHI, 0, -1],
        ]
    ]


def dirs_cuboct() -> list[list[float]]:
    o: list[list[float]] = []
    for x in (-1, 1):
        for y in (-1, 1):
            o.append([x, y, 0])
            o.append([x, 0, y])
            o.append([0, x, y])
    return [vnorm(v) for v in o]


def dirs_fib(m: int, seed: int = 0) -> list[list[float]]:
    out = []
    for i in range(m):
        zz = 1 - (2 * i + 1) / m
        rr = math.sqrt(max(0.0, 1 - zz * zz))
        th = 2 * math.pi * ((i + seed * 0.37) % m) / (PHI * PHI)
        out.append([rr * math.cos(th), rr * math.sin(th), zz])
    return out


def dirs_polar(cap: int, seed: int = 0) -> list[list[float]]:
    n_band = cap / 2 - 1
    z = 1 / 3
    rho = math.sqrt(1 - z * z)
    az0 = seed * 0.15
    s = [[0.0, 0.0, 1.0], [0.0, 0.0, -1.0]]
    k = 0
    while k < n_band:
        th_o = az0 + k * (2 * math.pi / n_band)
        th_c = az0 + math.pi / n_band + k * (2 * math.pi / n_band)
        s.append(vnorm([rho * math.cos(th_o), rho * math.sin(th_o), -z]))
        s.append(vnorm([rho * math.cos(th_c), rho * math.sin(th_c), +z]))
        k += 1
    return s


def dirs_t14() -> list[list[float]]:
    s = 1 / math.sqrt(3)
    return [
        vnorm(v)
        for v in [
            [s, s, s],
            [s, -s, -s],
            [-s, s, -s],
            [-s, -s, s],
            [-s, -s, -s],
            [-s, s, s],
            [s, -s, s],
            [s, s, -s],
            [1, 0, 0],
            [-1, 0, 0],
            [0, 1, 0],
            [0, -1, 0],
            [0, 0, 1],
            [0, 0, -1],
        ]
    ]


def shell_dirs(geom: str, cap: int, seed: int) -> list[list[float]]:
    if geom == "oct":
        return dirs_oct()
    if geom == "ico":
        return dirs_ico()
    if geom == "cuboct":
        return dirs_cuboct()
    if geom == "stella":
        return dirs_polar(8, seed)
    if geom == "t14":
        return dirs_t14()
    if geom == "polar":
        return dirs_polar(cap, seed)
    return dirs_fib(cap, seed)


class Nucleus(list):
    """Nucleon list plus packer extras (contacts, subSeq, …)."""


def pack_nucleus(A: int, Z: int, dnn: float = 1.45, coul_spread: float = 0.0) -> Nucleus:
    nd, nt = grammar(Z, A)
    spread = 1 + coul_spread * (Z * Z) / (A ** (4 / 3))
    D = dnn * spread
    nuc: Nucleus = Nucleus()
    contacts: list[tuple[int, int]] = []

    def push(pos, typ, group, sub, axis, tier=0) -> int:
        n = {
            "pos": list(pos),
            "type": typ,
            "group": group,
            "sub": sub,
            "axis": list(axis),
            "tier": tier,
            "id": len(nuc),
        }
        nuc.append(n)
        return n["id"]

    def bond(i: int, j: int) -> None:
        contacts.append((i, j))

    b_ = GAM
    h_ = math.sqrt(1 - b_ * b_ / 4)
    y0_ = (h_ * h_ - b_ * b_ / 4) / (2 * h_)
    r_ = math.hypot(b_ / 4, y0_ - h_ / 2)
    a_edge = R_P / r_
    b_edge = GAM * a_edge
    z_t = math.sqrt(a_edge * a_edge - b_edge * b_edge / 2) / 2
    VT = [
        [b_edge / 2, 0, z_t],
        [-b_edge / 2, 0, z_t],
        [0, b_edge / 2, -z_t],
        [0, -b_edge / 2, -z_t],
    ]
    FACES = [
        {"v": [0, 1, 2], "w": 2, "t": "p"},
        {"v": [0, 1, 3], "w": 3, "t": "p"},
        {"v": [0, 2, 3], "w": 0, "t": "n"},
        {"v": [1, 2, 3], "w": 1, "t": "n"},
    ]
    alpha_ids = []
    for f in FACES:
        W = VT[f["w"]]
        oth = [i for i in f["v"] if i != f["w"]]
        M = [
            (VT[oth[0]][0] + VT[oth[1]][0]) / 2,
            (VT[oth[0]][1] + VT[oth[1]][1]) / 2,
            (VT[oth[0]][2] + VT[oth[1]][2]) / 2,
        ]
        s = y0_ / h_
        c = [
            M[0] + (W[0] - M[0]) * s,
            M[1] + (W[1] - M[1]) * s,
            M[2] + (W[2] - M[2]) * s,
        ]
        e1 = [
            VT[f["v"][1]][0] - VT[f["v"][0]][0],
            VT[f["v"][1]][1] - VT[f["v"][0]][1],
            VT[f["v"][1]][2] - VT[f["v"][0]][2],
        ]
        e2 = [
            VT[f["v"][2]][0] - VT[f["v"][0]][0],
            VT[f["v"][2]][1] - VT[f["v"][0]][1],
            VT[f["v"][2]][2] - VT[f["v"][0]][2],
        ]
        nx = e1[1] * e2[2] - e1[2] * e2[1]
        ny = e1[2] * e2[0] - e1[0] * e2[2]
        nz = e1[0] * e2[1] - e1[1] * e2[0]
        if nx * c[0] + ny * c[1] + nz * c[2] < 0:
            nx, ny, nz = -nx, -ny, -nz
        nid = push(c, f["t"], "alpha", 0, vnorm([nx, ny, nz]), 0)
        nuc[nid]["ringR"] = R_P
        alpha_ids.append(nid)
    bond(alpha_ids[0], alpha_ids[2])
    bond(alpha_ids[0], alpha_ids[3])
    bond(alpha_ids[1], alpha_ids[2])
    bond(alpha_ids[1], alpha_ids[3])

    def e_mid(i, j):
        return [
            (VT[i][0] + VT[j][0]) / 2,
            (VT[i][1] + VT[j][1]) / 2,
            (VT[i][2] + VT[j][2]) / 2,
        ]

    nuc_extra = {
        "contacts": contacts,
        "bondD": D,
        "alphaGear": [e_mid(0, 2), e_mid(1, 2), e_mid(0, 3), e_mid(1, 3)],
        "alphaTetra": VT,
        "subSeq": [{"group": "alpha", "sub": 0, "sp": "α", "name": "α", "cap": 1}],
    }
    alpha_out = max(math.hypot(*nuc[i]["pos"]) for i in alpha_ids)

    r_tier = alpha_out + D * 1.05
    d_sub = 0
    t_sub = 0
    shell_idx = 0
    nd_left = max(0, nd)
    nt_left = max(0, nt)
    last_p: list[int] = []

    def rest_bond(n_id: int, scale: float) -> None:
        bi = -1
        bd_ = 1e18
        rest = last_p if last_p else [i for i in alpha_ids if nuc[i]["type"] == "p"]
        p = nuc[n_id]["pos"]
        for i in rest:
            q = nuc[i]["pos"]
            dd = math.hypot(q[0] - p[0], q[1] - p[1], q[2] - p[2])
            if dd < bd_:
                bd_ = dd
                bi = i
        if bi >= 0 and bd_ <= scale * D:
            bond(bi, n_id)

    def place_d_shell(cap: int, geom: str, name: str) -> None:
        nonlocal r_tier, d_sub, shell_idx, nd_left, last_p
        m = min(nd_left, cap)
        if m <= 0:
            return
        dirs = shell_dirs(geom, cap, shell_idx)[:m]
        new_p: list[int] = []
        for v in dirs:
            n_in = push(
                [v[0] * (r_tier - D / 2), v[1] * (r_tier - D / 2), v[2] * (r_tier - D / 2)],
                "n",
                "deuteron",
                d_sub,
                [v[0], v[1], v[2]],
                shell_idx + 1,
            )
            p_out = push(
                [v[0] * (r_tier + D / 2), v[1] * (r_tier + D / 2), v[2] * (r_tier + D / 2)],
                "p",
                "deuteron",
                d_sub,
                [-v[0], -v[1], -v[2]],
                shell_idx + 1,
            )
            bond(n_in, p_out)
            new_p.append(p_out)
            rest_bond(n_in, 1.6)
            nuc_extra["subSeq"].append(
                {"group": "deuteron", "sub": d_sub, "sp": "d", "name": name, "geom": geom, "cap": cap}
            )
            d_sub += 1
        last_p = new_p
        nd_left -= m
        shell_idx += 1
        r_tier += 2 * D

    def place_t_shell(cap: int, geom: str, name: str, dir_cap: int | None = None) -> None:
        nonlocal r_tier, t_sub, shell_idx, nt_left
        m = min(nt_left, cap)
        if m <= 0:
            return
        dc = dir_cap if dir_cap is not None else cap
        dirs = shell_dirs(geom, dc, shell_idx)[:m]
        for i, v in enumerate(dirs):
            open_ = i % 2 == 0
            rc = r_tier * (R_OPEN_SCALE if open_ else R_CLOSE_SCALE)
            n1 = push(
                [v[0] * (rc - D), v[1] * (rc - D), v[2] * (rc - D)],
                "n",
                "triton",
                t_sub,
                [v[0], v[1], v[2]],
                shell_idx + 1,
            )
            p = push(
                [v[0] * rc, v[1] * rc, v[2] * rc],
                "p",
                "triton",
                t_sub,
                [-v[0], -v[1], -v[2]],
                shell_idx + 1,
            )
            n2 = push(
                [v[0] * (rc + D), v[1] * (rc + D), v[2] * (rc + D)],
                "n",
                "triton",
                t_sub,
                [-v[0], -v[1], -v[2]],
                shell_idx + 1,
            )
            bond(n1, p)
            bond(p, n2)
            rest_bond(n1, 1.8)
            nuc_extra["subSeq"].append(
                {"group": "triton", "sub": t_sub, "sp": "t", "name": name, "geom": geom, "cap": cap}
            )
            t_sub += 1
        nt_left -= m
        shell_idx += 1
        r_tier += 2.2 * D

    for sh in SHELL_SEQ:
        if sh["sp"] == "d":
            place_d_shell(sh["cap"], sh["geom"], "D" + str(sh["cap"]))
        else:
            place_t_shell(sh["cap"], sh["geom"], "T" + str(sh["cap"]))

    while nd_left > 0:
        place_d_shell(min(nd_left, 56), "fib", "D*")
    while nt_left > 0:
        m = min(nt_left, 18)
        place_t_shell(m, "polar", "T*", dir_cap=max(m + (m % 2), 2))

    for k, v in nuc_extra.items():
        setattr(nuc, k, v)  # type: ignore[attr-defined]
    nuc.contacts = contacts  # type: ignore[attr-defined]
    nuc.bondD = D  # type: ignore[attr-defined]
    nuc.alphaGear = nuc_extra["alphaGear"]  # type: ignore[attr-defined]
    nuc.alphaTetra = VT  # type: ignore[attr-defined]
    nuc.subSeq = nuc_extra["subSeq"]  # type: ignore[attr-defined]
    nuc.nd = nd  # type: ignore[attr-defined]
    nuc.nt = nt  # type: ignore[attr-defined]
    return nuc


def dist(a: list[float], b: list[float]) -> float:
    return math.hypot(a[0] - b[0], a[1] - b[1], a[2] - b[2])


def protons(nuc: list[dict[str, Any]]) -> list[dict[str, Any]]:
    return [n for n in nuc if n["type"] == "p"]


def point_rms(pts: list[list[float]]) -> float:
    n = len(pts)
    if n == 0:
        return float("nan")
    cx = sum(p[0] for p in pts) / n
    cy = sum(p[1] for p in pts) / n
    cz = sum(p[2] for p in pts) / n
    return math.sqrt(sum((p[0] - cx) ** 2 + (p[1] - cy) ** 2 + (p[2] - cz) ** 2 for p in pts) / n)


def walk_schedule(nd: int, nt: int) -> list[dict[str, Any]]:
    """Species-pure fill: skip empty shells. Returns per-subunit stops."""
    stops = [{"sp": "α", "name": "α", "fill": 1, "cap": 1, "nd": 0, "nt": 0}]
    nd_left, nt_left = max(0, nd), max(0, nt)
    nd_acc = nt_acc = 0
    for sh in SHELL_SEQ:
        if sh["sp"] == "d":
            m = min(nd_left, sh["cap"])
            if m <= 0:
                continue
            for k in range(m):
                nd_acc += 1
                nd_left -= 1
                stops.append(
                    {
                        "sp": "d",
                        "name": "D" + str(sh["cap"]),
                        "geom": sh["geom"],
                        "fill": k + 1,
                        "cap": sh["cap"],
                        "nd": nd_acc,
                        "nt": nt_acc,
                    }
                )
        else:
            m = min(nt_left, sh["cap"])
            if m <= 0:
                continue
            for k in range(m):
                nt_acc += 1
                nt_left -= 1
                stops.append(
                    {
                        "sp": "t",
                        "name": "T" + str(sh["cap"]),
                        "geom": sh["geom"],
                        "fill": k + 1,
                        "cap": sh["cap"],
                        "nd": nd_acc,
                        "nt": nt_acc,
                    }
                )
    return stops


def last_stop(nd: int, nt: int) -> dict[str, Any]:
    return walk_schedule(nd, nt)[-1]


def prefix_through(name: str) -> tuple[int, int, int, int]:
    """nd, nt, Z, N_actual after completing named shells up to `name` inclusive.

    N_actual = 2 + nd + 2*nt (true neutrons). Z = 2 + nd + nt.
    """
    nd = nt = 0
    for sh in SHELL_SEQ:
        if sh["sp"] == "d":
            nd += sh["cap"]
        else:
            nt += sh["cap"]
        tag = ("D" if sh["sp"] == "d" else "T") + str(sh["cap"])
        if tag == name:
            Z = 2 + nd + nt
            N = 2 + nd + 2 * nt
            return nd, nt, Z, N
    raise KeyError(name)
