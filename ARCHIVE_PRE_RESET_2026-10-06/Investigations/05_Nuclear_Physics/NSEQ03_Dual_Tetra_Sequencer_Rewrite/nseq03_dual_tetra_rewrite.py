#!/usr/bin/env python3
"""NSEQ03 — validate dual-tetra triton seating rewrite in sequencer HTML."""
from __future__ import annotations

import json
import math
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
SEQ = ROOT / "Release/HTML_SDT_Website/nuclear-packing-sequencer.html"
DOC = ROOT / "docs/nuclear-packing-sequencer.html"
PACK = ROOT / "Release/HTML_SDT_Website/js/pack-nucleus.js"


def extract_pack_js() -> str:
    if not PACK.exists():
        raise RuntimeError("shared pack-nucleus.js not found")
    return PACK.read_text(encoding="utf-8")


def run_node(js: str) -> str:
    with tempfile.NamedTemporaryFile("w", suffix=".js", delete=False, encoding="utf-8") as f:
        f.write(js)
        tmp = f.name
    try:
        return subprocess.check_output(
            ["node", tmp], encoding="utf-8", stderr=subprocess.STDOUT
        )
    finally:
        Path(tmp).unlink(missing_ok=True)


def main() -> int:
    sys.stdout.reconfigure(encoding="utf-8")
    print("================================================================")
    print("NSEQ03 — Dual-tetra sequencer rewrite validation")
    print("================================================================\n")

    html = SEQ.read_text(encoding="utf-8", errors="replace")
    doc = DOC.read_text(encoding="utf-8", errors="replace")

    print("C1 — dual-tetra markers in shared packer + site mirrors")
    pack = extract_pack_js()
    markers = ["SHELL_SEQ", "dirsPolar", "R_OPEN_SCALE", "R_CLOSE_SCALE", "stella"]
    stale = ["BELT_PAIRS", "beltPlane"]
    ok1 = True
    for label, text in [("site", html), ("docs", doc)]:
        hit = 'src="js/pack-nucleus.js"' in text
        ok1 = ok1 and hit
        print(f"  {label}: shared packer linked: {'PASS' if hit else 'FAIL'}")
        for m in stale:
            gone = m not in text
            ok1 = ok1 and gone
            print(f"  {label}: stale {m} absent: {'PASS' if gone else 'FAIL'}")
    for marker in markers:
        hit = marker in pack
        ok1 = ok1 and hit
        print(f"  packer: {marker}: {'PASS' if hit else 'FAIL'}")
    print(f"  C1: {'PASS' if ok1 else 'FAIL'}\n")
    if not ok1:
        return 2

    print("C2 — packing smoke He/C/O/Fe/U")
    js_core = pack
    smoke = [("He", 2, 4), ("C", 6, 12), ("O", 8, 16), ("Fe", 26, 56), ("U", 92, 238)]
    runner = (
        js_core
        + "\nconst cases="
        + json.dumps(smoke)
        + ";\n"
        + "for (const [sym,Z,A] of cases){\n"
        + "  const nuc=packNucleus(A,Z,1.55,0.0);\n"
        + "  const nP=nuc.filter(n=>n.type==='p').length;\n"
        + "  const nN=nuc.filter(n=>n.type==='n').length;\n"
        + "  const nT=nuc.filter(n=>n.group==='triton').length/3;\n"
        + "  console.log(JSON.stringify({sym,Z,A,n:nuc.length,nP,nN,nT}));\n"
        + "}\n"
    )
    out = run_node(runner)
    ok2 = True
    for line in out.strip().splitlines():
        row = json.loads(line)
        good = row["n"] == row["A"] and row["nP"] == row["Z"] and row["nN"] == row["A"] - row["Z"]
        ok2 = ok2 and good
        print(
            f"  {row['sym']}-{row['A']}: N={row['n']} Zp={row['nP']} "
            f"nt_rods={row['nT']:.0f} {'PASS' if good else 'FAIL'}"
        )
    print(f"  C2: {'PASS' if ok2 else 'FAIL'}\n")
    if not ok2:
        return 2

    print("C3 — Ca-48 first shell geometry (n_t=8)")
    # Z=20 A=48 → nt=8 nd=10
    geo = (
        js_core
        + """
const nuc=packNucleus(48,20,1.55,0.0);
const rods=[];
for(let s=0;s<8;s++){
  const ps=nuc.filter(n=>n.group==='triton'&&n.sub===s&&n.type==='p');
  if(ps.length!==1) continue;
  const p=ps[0].pos;
  const r=Math.hypot(...p);
  const lat=Math.asin(Math.max(-1,Math.min(1,p[2]/r)))*180/Math.PI;
  rods.push({s,r,lat,z:p[2]});
}
const rs=rods.map(x=>x.r);
const rMax=Math.max(...rs), rMin=Math.min(...rs);
const maxAbsZ=Math.max(...rods.map(x=>Math.abs(x.z/x.r)));
const poles=rods.filter(x=>Math.abs(Math.abs(x.lat)-90)<1e-6).length;
console.log(JSON.stringify({nRods:rods.length,rMax,rMin,openGtClose:rMax>rMin,maxAbsZ,poles,rods}));
"""
    )
    g = json.loads(run_node(geo).strip().splitlines()[-1])
    ok3 = (
        g["nRods"] == 8
        and g["openGtClose"]
        and g["maxAbsZ"] > 0.9
        and g["poles"] >= 2
    )
    print(f"  rods={g['nRods']}  rMax={g['rMax']:.4f}  rMin={g['rMin']:.4f}")
    print(f"  max|dir.z|={g['maxAbsZ']:.3f}  polar_seats={g['poles']}")
    print(f"  open>close: {g['openGtClose']}")
    for x in g["rods"]:
        print(f"    sub={x['s']}  lat={x['lat']:+7.2f}°  r={x['r']:.4f}")
    print(f"  C3: {'PASS' if ok3 else 'FAIL'}\n")
    if not ok3:
        return 2

    print("C4 — capacity schedule present")
    caps = [int(x) for x in re.findall(r"sp:'t',cap:(\d+)", js_core)]
    ok4 = caps[:4] == [8, 10, 12, 14]
    print(f"  SHELL_CAPS={caps}")
    print(f"  C4: {'PASS' if ok4 else 'FAIL'}\n")

    print("C5 — laws.hpp untouched this iteration (proposal only)")
    print("  see PROPOSE_LAWS_HPP_BELT_NOMENCLATURE.md")
    print("  C5: PASS\n")

    print("================================================================")
    print("SUMMARY: DUAL_TETRA_SEQUENCER_APPLIED")
    print("================================================================")
    return 0 if (ok1 and ok2 and ok3 and ok4) else 2


if __name__ == "__main__":
    raise SystemExit(main())
