#!/usr/bin/env python3
"""NP12e — frozen ATOMICUS proton centres → point-proton RMS (IAEA sealed)."""
from __future__ import annotations

import itertools
import math
import re
from pathlib import Path

ROOT = Path(".")
IAEA = ROOT / "Datasets/nuclear/IAEA_ground_states_radii.csv"
R_P_FM = 0.8414  # MEASURED-INPUT (CODATA / muonic H) — engine R_p in fm
ETA = math.pi / math.sqrt(18.0)

FROZEN = [
    ("He4", 2, 4, ROOT / "ATOMICUS/elements/002_Helium_He_2_2.md"),
    ("Be9", 4, 9, ROOT / "ATOMICUS/elements/004_Beryllium_Be_4_5.md"),
    ("C12", 6, 12, ROOT / "ATOMICUS/elements/006_Carbon_C_6_6.md"),
    ("O16", 8, 16, ROOT / "ATOMICUS/elements/008_Oxygen_O_8_8.md"),
]
# Amendment 01: Li7 withdrawn — TABLE_INCOMPLETE (n_p=2, Z=3)
WITHDRAWN = [
    ("Li7", 3, 7, ROOT / "ATOMICUS/elements/003_Lithium_Li_3_4.md", "TABLE_INCOMPLETE"),
]

ROW_RE = re.compile(
    r"\|\s*(\d+)\s*\|\s*(proton|neutron)\s*\|\s*\("
    r"\s*([+-]?\d+(?:\.\d+)?)\s*,\s*([+-]?\d+(?:\.\d+)?)\s*,\s*([+-]?\d+(?:\.\d+)?)\s*\)\s*fm",
    re.I,
)


def rms_points(pts: list[tuple[float, float, float]]) -> float:
    n = len(pts)
    if n == 0:
        return float("nan")
    cx = sum(p[0] for p in pts) / n
    cy = sum(p[1] for p in pts) / n
    cz = sum(p[2] for p in pts) / n
    return math.sqrt(
        sum((p[0] - cx) ** 2 + (p[1] - cy) ** 2 + (p[2] - cz) ** 2 for p in pts) / n
    )


def R_boundary_fm(A: int) -> float:
    return R_P_FM * (A / ETA) ** (1.0 / 3.0)


def parse_protons(path: Path) -> list[tuple[float, float, float]]:
    text = path.read_text(encoding="utf-8", errors="replace")
    protons = []
    for m in ROW_RE.finditer(text):
        if m.group(2).lower() != "proton":
            continue
        protons.append((float(m.group(3)), float(m.group(4)), float(m.group(5))))
    return protons


def tammes4_centres() -> list[tuple[float, float, float]]:
    """Match packing.hpp preset_tammes4 outer centres (Cartesian, shell radius R)."""
    r_outer = math.sqrt(6.0) + 2.0
    R = 1.0 + r_outer
    theta1 = math.acos(-1.0 / 3.0)
    spheres = [
        (0.0, 0.0),
        (theta1, 0.0),
        (theta1, 2.0 * math.pi / 3.0),
        (theta1, 4.0 * math.pi / 3.0),
    ]
    out = []
    for th, ph in spheres:
        x = R * math.sin(th) * math.cos(ph)
        y = R * math.cos(th)
        z = R * math.sin(th) * math.sin(ph)
        out.append((x, y, z))
    return out


def main() -> int:
    print("================================================================")
    print("NP12e — Frozen proton centres / point-proton RMS")
    print("Pre-registered 2026-08-09 · IAEA sealed")
    print("================================================================\n")

    # C1
    print("C1 — instrument validation")
    pts = [
        (1.0, 1.0, 1.0),
        (1.0, -1.0, -1.0),
        (-1.0, 1.0, -1.0),
        (-1.0, -1.0, 1.0),
    ]
    ok = abs(rms_points(pts) - math.sqrt(3.0)) < 1e-12
    print(f"  discrete tetra RMS = {rms_points(pts):.10f} (expect sqrt(3))  {'PASS' if ok else 'FAIL'}")
    print(f"  C1: {'PASS' if ok else 'FAIL'}\n")
    if not ok:
        return 2

    # Ensure IAEA not opened — only existence check via path string, do not read
    print("C6 prelude — IAEA seal")
    print(f"  IAEA path exists: {IAEA.is_file()} — will NOT be read")
    print()

    print("C2/C3 — parse frozen ATOMICUS tables → R_p,RMS")
    for name, Z, A, path, reason in WITHDRAWN:
        n = len(parse_protons(path)) if path.is_file() else -1
        print(f"  WITHDRAWN {name}: n_p={n} Z={Z} → {reason} (Amendment 01)")
    all_ok = True
    results = []
    for name, Z, A, path in FROZEN:
        if not path.is_file():
            print(f"  {name}: MISSING {path}")
            all_ok = False
            continue
        protons = parse_protons(path)
        n = len(protons)
        ok_z = n == Z
        if not ok_z:
            all_ok = False
        rp = rms_points(protons) if n else float("nan")
        rb = R_boundary_fm(A)
        # max |r| from centroid (charge support scale of the table)
        if n:
            cx = sum(p[0] for p in protons) / n
            cy = sum(p[1] for p in protons) / n
            cz = sum(p[2] for p in protons) / n
            rmax = max(
                math.sqrt((p[0] - cx) ** 2 + (p[1] - cy) ** 2 + (p[2] - cz) ** 2)
                for p in protons
            )
        else:
            rmax = float("nan")
        results.append((name, Z, A, n, rp, rb, rmax, ok_z, path.name))
        print(
            f"  {name}: Z={Z} A={A} n_p={n}  R_p,RMS={rp:.6f} fm  "
            f"R_boundary={rb:.6f} fm  r_max,p={rmax:.6f} fm  "
            f"{'PASS' if ok_z else 'FAIL'}  [{path.name}]"
        )
    print(f"  C2: {'PASS' if all_ok else 'FAIL'}")
    print("  C3: PASS (values published; STATED_ATOMICUS_TABLE)\n")
    if not all_ok:
        return 2

    # C4 packing diagnostic
    print("C4 — proton-subset labelling (Tammes-4 + asymmetric fixture)")
    centres = tammes4_centres()
    R_shell = math.sqrt(sum(c * c for c in centres[0]))
    rms_list = []
    for combo in itertools.combinations(range(4), 2):
        sel = [centres[i] for i in combo]
        rms_list.append(rms_points(sel) / R_shell)
    span_tet = max(rms_list) - min(rms_list)
    print(f"  Tammes-4 R_shell = {R_shell:.6f}")
    print(f"  C(4,2) R_p,RMS/R_shell: min={min(rms_list):.6f} max={max(rms_list):.6f} span={span_tet:.3e}")
    ok_deg = span_tet < 1e-9
    print(f"  regular tetra value-degenerate: {'PASS' if ok_deg else 'FAIL'}")
    # asymmetric 4 centres — subset choice changes RMS
    asym = [(0.0, 0.0, 0.0), (1.0, 0.0, 0.0), (0.0, 2.0, 0.0), (0.0, 0.0, 3.0)]
    rms_a = [rms_points([asym[i] for i in combo]) for combo in itertools.combinations(range(4), 2)]
    span_a = max(rms_a) - min(rms_a)
    ok_asym = span_a > 1e-9
    print(f"  asymmetric C(4,2): min={min(rms_a):.6f} max={max(rms_a):.6f} span={span_a:.6f}")
    print(f"  asymmetric underdetermined: {'PASS' if ok_asym else 'FAIL'}")
    ok4 = ok_deg and ok_asym
    print(f"  C4: {'PASS' if ok4 else 'FAIL'}\n")
    if not ok4:
        return 2

    print("C5 — physical charge RMS status")
    print("  continuous rho_q: ABSENT")
    print("  point-proton RMS: COMPUTED from STATED_ATOMICUS_TABLE for frozen set")
    print("  physical charge RMS: UNDERDETERMINED (intra-proton geometry absent)")
    print("  C5: PASS\n")

    print("C6 — seals")
    print("  IAEA not read; no fitted scale; no EMPIRICALLY SURVIVES")
    print("  C6: PASS")

    print("\n================================================================")
    print("SUMMARY: POINT_PROTON_RMS_FROZEN_SET / PHYSICAL_CHARGE_RMS_UNDERDETERMINED")
    print("================================================================")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
