#!/usr/bin/env python3
"""NSEQ05-C5 — packing smoke + geometry markers after pure-shell rewrite."""
from __future__ import annotations

import json
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
SEQ = ROOT / "Release/HTML_SDT_Website/nuclear-packing-sequencer.html"
DOC = ROOT / "docs/nuclear-packing-sequencer.html"
PACK = ROOT / "Release/HTML_SDT_Website/js/pack-nucleus.js"


def extract_pack() -> str:
    if not PACK.exists():
        raise RuntimeError("shared pack-nucleus.js not found")
    return PACK.read_text(encoding="utf-8")


def main() -> int:
    sys.stdout.reconfigure(encoding="utf-8")
    print("NSEQ05-C5 packer smoke")
    html = SEQ.read_text(encoding="utf-8", errors="replace")
    doc = DOC.read_text(encoding="utf-8", errors="replace")
    js = extract_pack()
    markers = ["SHELL_SEQ", "dirsCuboct", "dirsT14", "dirsPolar", "NSEQ05"]
    ok_m = True
    for label, text in [("site", html), ("docs", doc)]:
        hit = 'src="js/pack-nucleus.js"' in text
        ok_m = ok_m and hit
        print(f"  {label} shared packer link: {'PASS' if hit else 'FAIL'}")
    for marker in markers:
        hit = marker in js
        ok_m = ok_m and hit
        print(f"  packer {marker}: {'PASS' if hit else 'FAIL'}")
    if not ok_m:
        return 2

    smoke = [("He", 2, 4), ("C", 6, 12), ("O", 8, 16), ("Fe", 26, 56), ("U", 92, 238), ("Ca", 20, 48)]
    runner = (
        js
        + "\nconst cases="
        + json.dumps(smoke)
        + ";\n"
        + "for (const [sym,Z,A] of cases){\n"
        + "  const nuc=packNucleus(A,Z,1.55,0.0);\n"
        + "  const nP=nuc.filter(n=>n.type==='p').length;\n"
        + "  const nT=nuc.filter(n=>n.group==='triton'&&n.type==='p').length;\n"
        + "  const nD=nuc.filter(n=>n.group==='deuteron'&&n.type==='p').length;\n"
        + "  console.log(JSON.stringify({sym,Z,A,n:nuc.length,nP,nT,nD}));\n"
        + "}\n"
        # Ca-48: full T8 — check not coplanar
        + """
{
  const nuc=packNucleus(48,20,1.55,0);
  const rods=nuc.filter(n=>n.group==='triton'&&n.type==='p');
  const maxAbsZ=Math.max(...rods.map(p=>Math.abs(p.pos[2]/Math.hypot(...p.pos))));
  const rs=rods.map(p=>Math.hypot(...p.pos));
  console.log(JSON.stringify({tag:'Ca48geom', nT:rods.length, maxAbsZ, rMax:Math.max(...rs), rMin:Math.min(...rs)}));
}
"""
    )
    with tempfile.NamedTemporaryFile("w", suffix=".js", delete=False, encoding="utf-8") as f:
        f.write(runner)
        tmp = f.name
    try:
        out = subprocess.check_output(
            ["node", tmp], encoding="utf-8", stderr=subprocess.STDOUT
        )
    finally:
        Path(tmp).unlink(missing_ok=True)

    ok = True
    for line in out.strip().splitlines():
        row = json.loads(line)
        if row.get("tag") == "Ca48geom":
            gok = row["nT"] == 8 and row["maxAbsZ"] > 0.9 and row["rMax"] > row["rMin"]
            ok = ok and gok
            print(
                f"  Ca-48 geom: nT={row['nT']} max|z|={row['maxAbsZ']:.3f} "
                f"rMax>rMin={row['rMax']>row['rMin']} {'PASS' if gok else 'FAIL'}"
            )
            continue
        good = row["n"] == row["A"] and row["nP"] == row["Z"]
        ok = ok and good
        print(
            f"  {row['sym']}-{row['A']}: N={row['n']} Zp={row['nP']} "
            f"d_p={row['nD']} t_p={row['nT']} {'PASS' if good else 'FAIL'}"
        )
    print(f"C5: {'PASS' if ok else 'FAIL'}")
    return 0 if ok else 2


if __name__ == "__main__":
    raise SystemExit(main())
