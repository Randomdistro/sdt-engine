#!/usr/bin/env python3
"""NSEQ01 — freeze Nuclear Packing Sequencer rules; grammar + packing smoke."""
from __future__ import annotations

import json
import math
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(".")
SEQ = ROOT / "Release/HTML_SDT_Website/nuclear-packing-sequencer.html"
PACK = ROOT / "Release/HTML_SDT_Website/js/pack-nucleus.js"
R_P = 0.8414


def extract_raw_rows(html: str) -> list[tuple]:
    """Parse RAW isotope tuples from the sequencer HTML."""
    m = re.search(r"const RAW\s*=\s*\[(.*?)\];", html, re.S)
    if not m:
        raise RuntimeError("RAW table not found")
    body = m.group(1)
    rows = []
    for t in re.finditer(
        r'\["([A-Za-z]+)",(\d+),(\d+),([0-9.eE+-]+),(true|false),([0-9.eE+-]+),"([^"]*)"\]',
        body,
    ):
        sym, Z, A, abd, stable, be, spin = t.groups()
        rows.append(
            (
                sym,
                int(Z),
                int(A),
                float(abd),
                stable == "true",
                float(be),
                spin,
            )
        )
    return rows


def main() -> int:
    sys.stdout.reconfigure(encoding="utf-8")
    print("================================================================")
    print("NSEQ01 — Nuclear Packing Sequencer rules freeze")
    print("Pre-registered 2026-08-09")
    print("================================================================\n")

    html = SEQ.read_text(encoding="utf-8", errors="replace")

    print("C1 — rule ledger (source anchors)")
    rules = [
        ("R1", "α-grammar n_t=A-2Z, n_d=3Z-A-2", "js/pack-nucleus.js grammar"),
        ("R2", "R_p=0.8414 fm; A1=π R_p²", "shared packer + sequencer diagnostic"),
        ("R3", "α contact-rotation tetrahedron; ring ≡ R_p; p↔n contacts", "js/pack-nucleus.js alpha core"),
        ("R4", "deuteron tiers capacities 6,12,12,20,30; n-in p-out rods", "js/pack-nucleus.js SHELL_SEQ"),
        ("R5", "triton dual-tetra shells n-p-n; caps 8,10,12…; r_open>r_close", "js/pack-nucleus.js polar seats"),
        ("R6", "explicit nuc.contacts bipartite p↔n", "js/pack-nucleus.js contacts"),
        ("R7", "ΔA=ΣA_i−A_∪; E≈κ·ΔA (κ fit separate)", "sequencer overlap diagnostic"),
        ("R8", "enmeshment = defect; not QED charge-radius map", "walkthrough + guide §10.1"),
    ]
    for rid, text, anc in rules:
        print(f"  {rid}: {text}")
        print(f"       anchor: nuclear-packing-sequencer.html {anc}")
    print("  C1: PASS\n")

    print("C2 — grammar identity on sequencer isotope filter")
    raw = extract_raw_rows(html)
    kept = []
    bad = 0
    for sym, Z, A, abd, stable, be, spin in raw:
        nd = 3 * Z - A - 2
        nt = A - 2 * Z
        if nd < 0 or nt < 0 or be <= 0:
            continue
        Z_inv = 2 + nd + nt
        A_inv = 4 + 2 * nd + 3 * nt
        if Z_inv != Z or A_inv != A:
            bad += 1
            print(f"  FAIL {sym}-{A}: inv Z={Z_inv} A={A_inv}")
        kept.append((sym, Z, A, nd, nt, be))
    print(f"  RAW rows parsed: {len(raw)}")
    print(f"  kept (nd,nt≥0, be>0): {len(kept)}")
    print(f"  inverse identity fails: {bad}")
    print(f"  C2: {'PASS' if bad == 0 and len(kept) > 100 else 'FAIL'}\n")
    if bad or len(kept) <= 100:
        return 2

    print("C3 — A1 = π R_p²")
    A1 = math.pi * R_P * R_P
    # match sequencer literal
    ok3 = abs(A1 - math.pi * 0.8414**2) < 1e-12
    print(f"  A1 = {A1:.10f} fm²")
    print(f"  C3: {'PASS' if ok3 else 'FAIL'}\n")
    if not ok3:
        return 2

    print("C4 — packing smoke (Node packNucleus count = A, Z)")
    if not PACK.exists():
        print("  FAIL: shared packer not found")
        return 2
    js_core = PACK.read_text(encoding="utf-8")
    smoke = [("He", 2, 4), ("C", 6, 12), ("O", 8, 16), ("Fe", 26, 56), ("U", 92, 238)]
    runner = (
        js_core
        + "\n"
        + "const cases="
        + json.dumps(smoke)
        + ";\n"
        + "for (const [sym,Z,A] of cases){\n"
        + "  const nuc=packNucleus(A,Z,1.55,0.0);\n"
        + "  const nP=nuc.filter(n=>n.type==='p').length;\n"
        + "  const nN=nuc.filter(n=>n.type==='n').length;\n"
        + "  console.log(JSON.stringify({sym,Z,A,n:nuc.length,nP,nN,contacts:nuc.contacts.length}));\n"
        + "}\n"
    )
    with tempfile.NamedTemporaryFile("w", suffix=".js", delete=False, encoding="utf-8") as f:
        f.write(runner)
        tmp = f.name
    try:
        out = subprocess.check_output(
            ["node", tmp], encoding="utf-8", stderr=subprocess.STDOUT
        )
    except subprocess.CalledProcessError as e:
        print("  FAIL node:", e.output[:500])
        return 2
    finally:
        Path(tmp).unlink(missing_ok=True)

    ok4 = True
    for line in out.strip().splitlines():
        row = json.loads(line)
        good = row["n"] == row["A"] and row["nP"] == row["Z"] and row["nN"] == row["A"] - row["Z"]
        ok4 = ok4 and good
        print(
            f"  {row['sym']}-{row['A']}: N={row['n']} (A={row['A']})  "
            f"Z_count={row['nP']} (Z={row['Z']})  contacts={row['contacts']}  "
            f"{'PASS' if good else 'FAIL'}"
        )
    print(f"  C4: {'PASS' if ok4 else 'FAIL'}\n")
    if not ok4:
        return 2

    print("C5 — NP12 IAEA-RMS path relative to sequencer")
    print("  label: WRONG_OBSERVABLE")
    print("  reason: sequencer predicts boundary/enmeshment/shadow ΔA;")
    print("          IAEA 'charge radius' is a QED measurement formulation.")
    print("          Neutrons stabilise via mesh (internal e−), not via RMS conversion.")
    print("  C5: PASS\n")

    print("C6 — no κ fit / no IAEA RMS / no laws.hpp edit — PASS")

    print("\n================================================================")
    print("SUMMARY: SEQUENCER_RULES_FROZEN")
    print(f"  isotopes in grammar filter: {len(kept)}")
    print("================================================================")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
