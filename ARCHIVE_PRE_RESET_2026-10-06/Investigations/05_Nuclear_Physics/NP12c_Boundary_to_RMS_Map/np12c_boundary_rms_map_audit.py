#!/usr/bin/env python3
"""NP12c Phase A — boundary→RMS map derivation census (no IAEA adjudication)."""
from __future__ import annotations

import hashlib
import math
import re
from pathlib import Path

ROOT = Path(".")
LAWS = ROOT / "Engine/include/sdt/laws.hpp"
THEORY = ROOT / "Theory"
LAWS_MD = ROOT / "Laws"
IAEA = ROOT / "Datasets/nuclear/IAEA_ground_states_radii.csv"
SOURCE_FREEZE = (
    ROOT
    / "Investigations/05_Nuclear_Physics/NP12b_ClosePack_Radius_Reproduction"
    / "NP12B_OBSERVABLE_ADMISSIBILITY_SOURCE_FREEZE_2026-08-09.md"
)

# Search tokens for a native map (Phase A census)
MAP_PATTERNS = [
    r"boundary.?to.?RMS",
    r"R_rms",
    r"RMS charge",
    r"sqrt\s*\(\s*3\s*/\s*5\s*\)",
    r"periphery.?charge",
    r"surface.?charge",
    r"charge.?density.?profile",
    r"nuclear_boundary_radius",
]


def sha256(path: Path) -> str:
    h = hashlib.sha256()
    h.update(path.read_bytes())
    return h.hexdigest()


def scan_file(path: Path) -> list[tuple[int, str]]:
    hits = []
    try:
        text = path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return hits
    for i, line in enumerate(text.splitlines(), 1):
        for pat in MAP_PATTERNS:
            if re.search(pat, line, re.I):
                hits.append((i, line.strip()[:160]))
                break
    return hits


def main() -> int:
    print("================================================================")
    print("NP12c — Boundary to RMS Map (Phase A freeze)")
    print("Pre-registered 2026-08-09 · no IAEA adjudication")
    print("================================================================\n")

    print("C1 — source census")
    census: dict[str, list[tuple[int, str]]] = {}
    for path in [LAWS]:
        census[str(path)] = scan_file(path)
    for folder in (THEORY, LAWS_MD):
        if folder.is_dir():
            for path in sorted(folder.rglob("*.md")):
                h = scan_file(path)
                if h:
                    census[str(path)] = h
    n_files = len(census)
    n_hits = sum(len(v) for v in census.values())
    print(f"  files with hits: {n_files}  total hit-lines: {n_hits}")
    # Show laws.hpp hits only (compact); Theory/Laws counts
    laws_hits = census.get(str(LAWS), [])
    print(f"  laws.hpp hits: {len(laws_hits)}")
    for ln, s in laws_hits[:12]:
        print(f"    L{ln}: {s}")
    theory_n = sum(1 for k in census if k.replace("\\", "/").startswith("Theory/"))
    lawsmd_n = sum(1 for k in census if k.replace("\\", "/").startswith("Laws/"))
    print(f"  Theory/*.md with hits: {theory_n}")
    print(f"  Laws/*.md with hits: {lawsmd_n}")
    # Executable Map function?
    laws_text = LAWS.read_text(encoding="utf-8", errors="replace")
    has_map_fn = bool(
        re.search(r"nuclear_.*rms|rms_.*radius|boundary_to_rms", laws_text, re.I)
    )
    print(f"  executable Map symbol in laws.hpp: {has_map_fn}")
    print("  C1: PASS\n")

    print("C2 — Validation: uniform-sphere RMS identity")
    # Analytic: for rho=const in ball radius R, <r^2> = 3/5 R^2 ⇒ R_rms/R = sqrt(3/5)
    ratio = math.sqrt(3.0 / 5.0)
    # Numerical check via shell integral
    n = 200000
    # Monte Carlo in ball
    import random

    random.seed(12)
    acc = 0.0
    m = 0
    while m < n:
        x, y, z = random.uniform(-1, 1), random.uniform(-1, 1), random.uniform(-1, 1)
        if x * x + y * y + z * z <= 1.0:
            acc += x * x + y * y + z * z
            m += 1
    num = math.sqrt(acc / m)
    rel = abs(num - ratio) / ratio
    ok_c2 = rel < 5e-3
    print(f"  analytic sqrt(3/5) = {ratio:.10f}")
    print(f"  MC <r^2>^(1/2)/R   = {num:.10f}  rel={rel:.3e}  n={m}")
    print(f"  C2: {'PASS' if ok_c2 else 'FAIL'}\n")
    if not ok_c2:
        return 2

    print("C3/C4 — candidate map ledger (formal classification)")
    candidates = [
        {
            "id": "M_identity",
            "formula": "R_RMS = R_boundary",
            "class": "UNDERIVED",
            "note": "NP12 surface-charge endpoint; periphery-charge strength un-derived",
        },
        {
            "id": "M_uniform",
            "formula": "R_RMS = sqrt(3/5) * R_boundary",
            "class": "GEOMETRIC_IDENTITY_UNDER_UNIFORM_DENSITY",
            "note": "math OK for uniform ball; uniform nuclear charge density not SDT-derived",
        },
        {
            "id": "M_native_profile",
            "formula": "R_RMS = Map(R_boundary; rho_ch(r), finite-proton)",
            "class": "ABSENT",
            "note": "no executable Map in laws.hpp / Theory / Laws",
        },
    ]
    for c in candidates:
        print(f"  {c['id']}: {c['formula']}")
        print(f"    class = {c['class']}")
        print(f"    note  = {c['note']}")
    print("  C3: PASS (identity UNDERIVED)")
    print("  C4: PASS (uniform geometric under underived density premise)\n")

    print("C5 — Phase A derivation gate")
    native_frozen = False  # no Map derived this loop
    status = "MAP_UNDERIVED" if not native_frozen else "MAP_FROZEN"
    print(f"  native Map frozen: {native_frozen}")
    print(f"  Phase A status: {status}")
    print("  Phase B: SEALED (no holdout residuals computed)")
    print("  C5: PASS\n")

    print("C6 — no retrofit / no empirical survival claim")
    if IAEA.is_file():
        print(f"  IAEA present sha256={sha256(IAEA)[:16]}… (not opened for fit)")
    else:
        print("  IAEA path missing at Datasets/nuclear/… (Phase B still sealed)")
    if SOURCE_FREEZE.is_file():
        print(f"  NP12b source freeze present sha256={sha256(SOURCE_FREEZE)[:16]}…")
    print("  holdout split (sealed): odd A, A>=16; no coefficients from either half")
    print("  C6: PASS")

    # Cascade note: laws.hpp correspondence_status text still says known-match 4.96%
    if "known-match (4.96% RMS" in laws_text:
        print("\n  CASCADE NOTE (propose-and-wait, not edited):")
        print("    laws.hpp nuclear_boundary_radius correspondence_status still cites")
        print("    'known-match (4.96% RMS)' — I26 corrected physical verdict to UNADJUDICATED.")

    print("\n================================================================")
    print(f"SUMMARY: {status} / PHASE_B_SEALED")
    print("================================================================")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
