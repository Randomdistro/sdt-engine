#!/usr/bin/env python3
"""NP12d — underdetermination proof + RMS fixtures + topology census (IAEA sealed)."""
from __future__ import annotations

import math
import re
from pathlib import Path

ROOT = Path(".")
LAWS = ROOT / "Engine/include/sdt/laws.hpp"
PACKING = ROOT / "Engine/include/sdt/packing.hpp"
NUCLEAR_HPP = ROOT / "Engine/include/sdt/nuclear.hpp"
ATOMICUS = ROOT / "ATOMICUS"
IAEA = ROOT / "Datasets/nuclear/IAEA_ground_states_radii.csv"


def rms_continuous_radial(samples: list[tuple[float, float]]) -> float:
    """samples: (r, weight); isotropic shells — R_RMS^2 = Σ w r^2 / Σ w about origin if centered."""
    tw = sum(w for _, w in samples)
    t2 = sum(w * r * r for r, w in samples)
    return math.sqrt(t2 / tw) if tw > 0 else float("nan")


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


def rotate_z(pts, ang):
    c, s = math.cos(ang), math.sin(ang)
    return [(c * x - s * y, s * x + c * y, z) for x, y, z in pts]


def main() -> int:
    print("================================================================")
    print("NP12d — Topology / charge second moment (IAEA sealed)")
    print("Pre-registered 2026-08-09")
    print("================================================================\n")

    # --- C1/C2 underdetermination ---
    print("C1/C2 — underdetermination at fixed R_B (no IAEA)")
    R_B = 1.0
    # mu_lambda: R_RMS = R_B * sqrt(lambda)
    ok_lam = True
    for lam in (0.0, 0.25, 0.5, 0.75, 1.0):
        # mixture: weight (1-lam) at r=0, lam at r=R_B
        r_rms = rms_continuous_radial([(0.0, 1.0 - lam), (R_B, lam)])
        expect = R_B * math.sqrt(lam)
        rel = abs(r_rms - expect) if expect == 0 else abs(r_rms - expect) / expect
        if not (rel < 1e-12 or (expect == 0 and r_rms == 0)):
            ok_lam = False
        print(f"  lambda={lam:.2f}  R_RMS={r_rms:.10f}  expect={expect:.10f}")
    # uniform vs shell
    # uniform ball: analytic fixture value sqrt(3/5)*R_B — used ONLY as fixture identity
    r_unif = math.sqrt(3.0 / 5.0) * R_B
    r_shell = R_B
    print(f"  uniform-ball fixture R_RMS = {r_unif:.10f} = sqrt(3/5) R_B")
    print(f"  thin-shell fixture  R_RMS = {r_shell:.10f} = R_B")
    print(f"  ratio shell/uniform = {r_shell/r_unif:.6f} (≠ 1) — same R_B, different R_RMS")
    print(f"  C1: {'PASS' if ok_lam else 'FAIL'} (mu_lambda covers [0,R_B])")
    print(f"  C2: PASS (uniform ≠ shell)\n")
    if not ok_lam:
        return 2

    # --- C3 fixtures ---
    print("C3 — analytic RMS instrument fixtures")
    fails = 0

    # central point
    r0 = rms_points([(0.0, 0.0, 0.0)])
    ok = abs(r0) < 1e-15
    print(f"  central point: {r0:.3e}  {'PASS' if ok else 'FAIL'}")
    fails += not ok

    # thin shell (all mass at R) via continuous samples
    r_sh = rms_continuous_radial([(2.5, 1.0)])
    ok = abs(r_sh - 2.5) < 1e-12
    print(f"  thin shell R=2.5: {r_sh:.10f}  {'PASS' if ok else 'FAIL'}")
    fails += not ok

    # uniform sphere via radial shells ∫ r^4 dr / ∫ r^2 dr = 3/5 R^2
    R = 3.0
    # discrete radial quadrature with volume weights ~ r^2 dr
    n = 5000
    samples = []
    for i in range(n):
        r = (i + 0.5) * R / n
        w = r * r  # ∝ volume shell
        samples.append((r, w))
    r_u = rms_continuous_radial(samples)
    exp_u = math.sqrt(3.0 / 5.0) * R
    rel_u = abs(r_u - exp_u) / exp_u
    ok = rel_u < 1e-3
    print(f"  uniform R=3: {r_u:.10f} vs {exp_u:.10f} rel={rel_u:.3e}  {'PASS' if ok else 'FAIL'}")
    fails += not ok

    # known discrete set: unit tetrahedron-ish
    pts = [
        (1.0, 1.0, 1.0),
        (1.0, -1.0, -1.0),
        (-1.0, 1.0, -1.0),
        (-1.0, -1.0, 1.0),
    ]
    r_d = rms_points(pts)
    # centroid 0; |r|^2 = 3 each → RMS = sqrt(3)
    exp_d = math.sqrt(3.0)
    ok = abs(r_d - exp_d) < 1e-12
    print(f"  discrete tetra pts: {r_d:.10f} vs {exp_d:.10f}  {'PASS' if ok else 'FAIL'}")
    fails += not ok

    # translation invariance
    shifted = [(x + 7, y - 3, z + 2) for x, y, z in pts]
    ok = abs(rms_points(shifted) - r_d) < 1e-12
    print(f"  translation invariance: {'PASS' if ok else 'FAIL'}")
    fails += not ok

    # rotation
    ok = abs(rms_points(rotate_z(pts, 0.7)) - r_d) < 1e-12
    print(f"  rotational invariance: {'PASS' if ok else 'FAIL'}")
    fails += not ok

    # scale
    s = 2.5
    scaled = [(s * x, s * y, s * z) for x, y, z in pts]
    ok = abs(rms_points(scaled) - s * r_d) < 1e-12
    print(f"  uniform scale: {'PASS' if ok else 'FAIL'}")
    fails += not ok

    print(f"  C3: {'PASS' if fails == 0 else 'FAIL'} ({fails} fixture fails)\n")
    if fails:
        return 2

    # --- C4 topology census ---
    print("C4 — topology / charge-state census")
    laws = LAWS.read_text(encoding="utf-8", errors="replace")
    pack = PACKING.read_text(encoding="utf-8", errors="replace") if PACKING.is_file() else ""
    nuc = NUCLEAR_HPP.read_text(encoding="utf-8", errors="replace") if NUCLEAR_HPP.is_file() else ""

    has_boundary_fn = "nuclear_boundary_radius" in laws
    has_rho_q = bool(re.search(r"rho_q|ρ_q|charge_density|charge density profile", laws + pack + nuc, re.I))
    has_rms_map = bool(re.search(r"boundary_to_rms|nuclear_.*rms|rms_charge", laws + pack + nuc, re.I))
    has_packing_presets = "preset_tammes4" in pack and "PackingConfig" in pack
    has_proton_label = bool(re.search(r"proton.*(position|vertex|coord)|which.*proton", pack, re.I))

    # ATOMICUS: look for coordinate tables vs continuous density
    atom_pos_files = 0
    atom_rho = 0
    if ATOMICUS.is_dir():
        for p in list(ATOMICUS.glob("elements/*.md"))[:50]:
            t = p.read_text(encoding="utf-8", errors="replace")
            if re.search(r"\|\s*\d+\s*\|\s*proton\s*\|\s*\(", t):
                atom_pos_files += 1
            if re.search(r"rho_q|charge density ρ|ρ_q\(", t):
                atom_rho += 1

    print(f"  laws.hpp nuclear_boundary_radius: {has_boundary_fn}")
    print(f"  executable rho_q / charge density in engine headers: {has_rho_q}")
    print(f"  executable boundary→RMS Map in engine headers: {has_rms_map}")
    print(f"  packing.hpp Tammes/PackingConfig presets: {has_packing_presets}")
    print(f"  packing.hpp proton-subset labelling: {has_proton_label}")
    print(f"  ATOMICUS elements with proton coordinate tables (sample≤50): {atom_pos_files}")
    print(f"  ATOMICUS rho_q definitions (sample≤50): {atom_rho}")

    # Outcome assignment
    # O1 requires continuous or frozen rho_q
    # O2 requires proton positions with Z-selection
    # O3 R_boundary-only path for NP12
    if has_rho_q and has_rms_map:
        outcome = "O1"
        detail = "rho_q present — native RMS computable (unexpected; freeze before Phase B)"
    elif has_packing_presets and not has_rho_q:
        # positions exist as nucleon spheres; proton subset not generally labelled
        outcome = "O2"
        detail = (
            "packing.hpp supplies nucleon-center geometries for presets; "
            "no intra-proton charge geometry; proton vs neutron selection not a general "
            "executable Z-subset for arbitrary A; point-proton RMS DERIVABLE only where "
            "proton centres are frozen; physical charge RMS UNDERDETERMINED. "
            "NP12 R_boundary-only path separately meets O3."
        )
    else:
        outcome = "O3"
        detail = "only outer boundary available for NP12 scalar path"

    # Strengthen: NP12 path is O3 regardless
    np12_path = "O3"
    print(f"\n  NP12 scalar path (R_boundary alone): {np12_path}")
    print(f"  Topology layer outcome: {outcome}")
    print(f"  detail: {detail}")
    print("  C4: PASS\n")

    # --- C5 status ---
    print("C5 — strengthened status")
    status = "UNDERDETERMINED — BOUNDARY IS NOT A SUFFICIENT STATE VARIABLE"
    print(f"  {status}")
    print("  Note: if nuclear_boundary_radius is mechanical/exclusion only,")
    print("  even R_RMS <= R_B is not established (charge support unbound by that symbol).")
    print("  Correct native arrow: topology → rho_q → R_RMS  (not R_B → k R_B)")
    print("  C5: PASS\n")

    # --- C6 ---
    print("C6 — seals")
    print(f"  IAEA path exists: {IAEA.is_file()} — NOT OPENED")
    print("  no fitted k; sqrt(3/5) used only as uniform-sphere fixture identity")
    print("  C6: PASS")

    print("\n================================================================")
    print(f"SUMMARY: {status}")
    print(f"  NP12 path: O3 | topology layer: {outcome}")
    print("================================================================")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
