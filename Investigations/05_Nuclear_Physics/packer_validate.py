#!/usr/bin/env python3
"""Validate Python pack_nucleus.py against node pack-nucleus.js. Known-answer first."""
from __future__ import annotations

import json
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))
from pack_nucleus import pack_nucleus, grammar

JS = ROOT / "Release/HTML_SDT_Website/js/pack-nucleus.js"
CASES = [("He", 2, 4), ("C", 6, 12), ("O", 8, 16), ("Fe", 26, 56), ("Ca", 20, 48)]


def main() -> int:
    print("PACKER VALIDATE — Python vs node pack-nucleus.js")
    print("pre-reg: PACKER_REOPEN_PRE_REGISTRATION.md")
    print("dnn=1.45 fm  coulSpread=0")
    js = JS.read_text(encoding="utf-8")
    runner = (
        js
        + "\nconst cases="
        + json.dumps(CASES)
        + """;
for (const [sym,Z,A] of cases){
  const nuc=packNucleus(A,Z,1.45,0);
  const nP=nuc.filter(n=>n.type==='p').length;
  const seq=nuc.subSeq.map(s=>s.sp);
  const p0=nuc.find(n=>n.type==='p').pos;
  console.log(JSON.stringify({sym,Z,A,n:nuc.length,nP,nC:nuc.contacts.length,seq,p0}));
}
"""
    )
    with tempfile.NamedTemporaryFile("w", suffix=".js", delete=False, encoding="utf-8") as f:
        f.write(runner)
        tmp = f.name
    try:
        out = subprocess.check_output(["node", tmp], text=True, stderr=subprocess.STDOUT)
    except (subprocess.CalledProcessError, FileNotFoundError) as e:
        print(f"NODE FAIL: {e}")
        return 2
    finally:
        Path(tmp).unlink(missing_ok=True)

    ok = True
    for line in out.strip().splitlines():
        row = json.loads(line)
        nuc = pack_nucleus(row["A"], row["Z"], 1.45, 0)
        nP = sum(1 for n in nuc if n["type"] == "p")
        seq = [s["sp"] for s in nuc.subSeq]
        p0 = next(n["pos"] for n in nuc if n["type"] == "p")
        nd, nt = grammar(row["Z"], row["A"])
        count_ok = len(nuc) == row["A"] == row["n"] and nP == row["Z"] == row["nP"]
        def norm_sp(s):
            return s if s in ("d", "t") else "a"
        seq_ok = [norm_sp(s) for s in seq] == [norm_sp(s) for s in row["seq"]]
        pos_ok = max(abs(a - b) for a, b in zip(p0, row["p0"])) < 1e-9
        bond_ok = len(nuc.contacts) == row["nC"]
        good = count_ok and seq_ok and pos_ok and bond_ok
        ok = ok and good
        seq_s = "".join("a" if s == "α" else s for s in seq[:12])
        print(
            f"  {row['sym']}-{row['A']}: n={len(nuc)} Zp={nP} nd,nt={nd},{nt} "
            f"seq={seq_s}{'...' if len(seq)>12 else ''} "
            f"{'PASS' if good else 'FAIL'}"
        )
        if not good:
            print(f"    js nC={row['nC']} py nC={len(nuc.contacts)} seq_ok={seq_ok} pos_ok={pos_ok}")
            print(f"    py seq={ [norm_sp(s) for s in seq] } js seq={ [norm_sp(s) for s in row['seq']] }")
    # Fe-56 species order: a + 6d + 12d + 4t + 2d
    fe = pack_nucleus(56, 26)
    fe_sp = [s["sp"] for s in fe.subSeq]
    fe_ok = fe_sp[:1] == ["α"] and fe_sp[1:7] == ["d"] * 6 and fe_sp[7:19] == ["d"] * 12
    fe_ok = fe_ok and fe_sp[19:23] == ["t"] * 4 and fe_sp[23:] == ["d"] * 2
    print(f"  Fe-56 interleaved subSeq a+6d+12d+4t+2d: {'PASS' if fe_ok else 'FAIL'} count={len(fe_sp)}")
    ok = ok and fe_ok
    print("STATUS PACKER_VALIDATE_" + ("PASS" if ok else "FAIL"))
    return 0 if ok else 2


if __name__ == "__main__":
    raise SystemExit(main())
