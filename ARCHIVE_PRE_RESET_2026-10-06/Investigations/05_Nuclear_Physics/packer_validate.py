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
CASES = [
    ("He", 2, 4),
    ("C", 6, 12),
    ("O", 8, 16),
    ("Fe", 26, 56),
    ("Ca", 20, 48),
    ("U", 92, 238),
]


def main() -> int:
    sys.stdout.reconfigure(encoding="utf-8")
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
  const nodes=nuc.map(n=>({pos:n.pos,type:n.type,group:n.group,sub:n.sub,tier:n.tier}));
  console.log(JSON.stringify({
    sym,Z,A,n:nuc.length,nP,version:nuc.version,
    classification:nuc.classification,contactGeometry:nuc.contactGeometry,nodes,
    contacts:nuc.contacts,seq:nuc.subSeq,shells:nuc.shells
  }));
}
let invalidRejected=false;
try { packNucleus(7,4); } catch (e) { invalidRejected=e instanceof RangeError; }
console.log(JSON.stringify({tag:'invalid-grammar',invalidRejected}));
"""
    )
    with tempfile.NamedTemporaryFile("w", suffix=".js", delete=False, encoding="utf-8") as f:
        f.write(runner)
        tmp = f.name
    try:
        out = subprocess.check_output(
            ["node", tmp], encoding="utf-8", stderr=subprocess.STDOUT
        )
    except (subprocess.CalledProcessError, FileNotFoundError) as e:
        print(f"NODE FAIL: {e}")
        return 2
    finally:
        Path(tmp).unlink(missing_ok=True)

    ok = True
    for line in out.strip().splitlines():
        row = json.loads(line)
        if row.get("tag") == "invalid-grammar":
            good = row["invalidRejected"]
            try:
                pack_nucleus(7, 4)
                good = False
            except ValueError:
                pass
            print(f"  invalid grammar rejected: {'PASS' if good else 'FAIL'}")
            ok = ok and good
            continue
        nuc = pack_nucleus(row["A"], row["Z"], 1.45, 0)
        nP = sum(1 for n in nuc if n["type"] == "p")
        nd, nt = grammar(row["Z"], row["A"])
        count_ok = len(nuc) == row["A"] == row["n"] and nP == row["Z"] == row["nP"]
        node_ok = len(nuc) == len(row["nodes"])
        for py_node, js_node in zip(nuc, row["nodes"]):
            node_ok = node_ok and all(py_node[key] == js_node[key] for key in ("type", "group", "sub", "tier"))
            node_ok = node_ok and max(abs(a - b) for a, b in zip(py_node["pos"], js_node["pos"])) < 1e-9
        seq_ok = nuc.subSeq == row["seq"]
        shell_ok = nuc.shells == row["shells"]
        bond_ok = [list(link) for link in nuc.contacts] == row["contacts"]
        parity_ok = all(nuc[i]["type"] != nuc[j]["type"] for i, j in nuc.contacts)
        adjacency_ok = all(abs(nuc[i]["tier"] - nuc[j]["tier"]) <= 1 for i, j in nuc.contacts)
        occupancy_ok = sum(s["occupancy"] for s in nuc.shells[1:]) == nd + nt
        version_ok = nuc.version == row["version"] == "NSEQ05-CONTROL-3"
        classification_ok = (
            nuc.classification
            == row["classification"]
            == "LEGACY_GEOMETRIC_CONTROL"
            and nuc.contactGeometry is False
            and row["contactGeometry"] is False
        )
        good = all(
            (
                count_ok,
                node_ok,
                seq_ok,
                shell_ok,
                bond_ok,
                parity_ok,
                adjacency_ok,
                occupancy_ok,
                version_ok,
                classification_ok,
            )
        )
        ok = ok and good
        seq_s = "".join("a" if s["sp"] == "α" else s["sp"] for s in nuc.subSeq[:12])
        print(
            f"  {row['sym']}-{row['A']}: n={len(nuc)} Zp={nP} nd,nt={nd},{nt} "
            f"seq={seq_s}{'...' if len(nuc.subSeq)>12 else ''} "
            f"{'PASS' if good else 'FAIL'}"
        )
        if not good:
            print(
                f"    nodes={node_ok} contacts={bond_ok} seq={seq_ok} shells={shell_ok} "
                f"parity={parity_ok} adjacency={adjacency_ok} occupancy={occupancy_ok} "
                f"classification={classification_ok}"
            )
            if not seq_ok:
                print(
                    "    py seq[0]="
                    + json.dumps(nuc.subSeq[0], ensure_ascii=True)
                    + " js seq[0]="
                    + json.dumps(row["seq"][0], ensure_ascii=True)
                )
            if not shell_ok:
                print(
                    "    py shell[0]="
                    + json.dumps(nuc.shells[0], ensure_ascii=True)
                    + " js shell[0]="
                    + json.dumps(row["shells"][0], ensure_ascii=True)
                )
    # Fe-56 species order: a + 6d + 12d + 4t + 2d
    fe = pack_nucleus(56, 26)
    fe_sp = [s["sp"] for s in fe.subSeq]
    fe_ok = fe_sp[:1] == ["α"] and fe_sp[1:7] == ["d"] * 6 and fe_sp[7:19] == ["d"] * 12
    fe_ok = fe_ok and fe_sp[19:23] == ["t"] * 4 and fe_sp[23:] == ["d"] * 2
    fe_ok = fe_ok and [s["seat"] for s in fe.subSeq if s["name"] == "T8"] == [0, 1, 2, 3]
    print(f"  Fe-56 interleaved subSeq a+6d+12d+4t+2d: {'PASS' if fe_ok else 'FAIL'} count={len(fe_sp)}")
    ok = ok and fe_ok
    print("STATUS PACKER_VALIDATE_" + ("PASS" if ok else "FAIL"))
    return 0 if ok else 2


if __name__ == "__main__":
    raise SystemExit(main())
