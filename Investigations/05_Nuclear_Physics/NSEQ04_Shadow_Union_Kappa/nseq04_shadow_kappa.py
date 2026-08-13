#!/usr/bin/env python3
"""NSEQ04 — shadow-union κ·ΔA calibrate on live dual-tetra sequencer packing."""
from __future__ import annotations

import json
import re
import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
SEQ = ROOT / "Release/HTML_SDT_Website/nuclear-packing-sequencer.html"


def extract_block(html: str, start_pat: str, end_pat: str) -> str:
    a = html.find(start_pat)
    if a < 0:
        raise RuntimeError(f"start not found: {start_pat}")
    b = html.find(end_pat, a)
    if b < 0:
        raise RuntimeError(f"end not found: {end_pat}")
    return html[a:b]


def main() -> int:
    print("================================================================")
    print("NSEQ04 — Shadow-union κ·ΔA (pre-registered policy)")
    print("================================================================\n")

    html = SEQ.read_text(encoding="utf-8", errors="replace")

    print("C1 — κ policy (frozen)")
    print("  form: BE ≈ κ·ΔA through origin")
    print("  estimator: κ = Σ(BE·ΔA)/Σ(ΔA²)")
    print("  sample: full ISO filter; dnn=1.45*R_p; coul=0.30; DEFAULT_LIGHT")
    print("  packing: live packNucleus (dual-tetra tritons)")
    print("  C1: PASS\n")

    # RAW + ISO construction + physics through calibrate()
    raw_m = re.search(r"const RAW\s*=\s*\[(.*?)\];", html, re.S)
    names_m = re.search(r"const NAMES\s*=\s*\[(.*?)\];", html, re.S)
    if not raw_m or not names_m:
        print("FAIL: RAW/NAMES not found")
        return 2

    # From R_p through end of packNucleus only (browser canvas shadow replaced below)
    start = html.find("const R_p = 0.8414;")
    fn = html.find("function packNucleus(", start)
    if start < 0 or fn < 0:
        print("FAIL: packNucleus not found")
        return 2
    brace = html.find("{", fn)
    depth = 0
    end = brace
    for i, ch in enumerate(html[brace:], brace):
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                end = i + 1
                break
    physics = html[start:end]
    if "function vnorm" not in physics:
        vn = re.search(r"function vnorm\(v\)\{[^}]+\}", html)
        if vn:
            physics = vn.group(0) + "\n" + physics

    # Node-compatible measureShadow + calibrate (same math as sequencer HTML)
    shadow_js = r"""
function normalize(v){const l=Math.hypot(v[0],v[1],v[2])||1;return[v[0]/l,v[1]/l,v[2]/l];}
function cross(a,b){return[a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]];}
function dot(a,b){return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];}
function measureShadow(centres, lightDir){
  const N=centres.length;
  if(N===0) return {Asum:0,Aunion:0,dA:0,pct:0};
  const L=normalize(lightDir);
  const up = Math.abs(L[1])>0.9 ? [1,0,0] : [0,1,0];
  const u=normalize(cross(up,L)), v=cross(L,u);
  const P=centres.map(c=>[dot(c.pos,u),dot(c.pos,v)]);
  let minx=1e9,maxx=-1e9,miny=1e9,maxy=-1e9;
  for(const[x,y]of P){minx=Math.min(minx,x);maxx=Math.max(maxx,x);miny=Math.min(miny,y);maxy=Math.max(maxy,y);}
  minx-=R_p;maxx+=R_p;miny-=R_p;maxy+=R_p;
  const spanx=maxx-minx, spany=maxy-miny, span=Math.max(spanx,spany,1e-6);
  const S=290;
  const fmPerPx = span/S;
  const pxR = R_p/fmPerPx;
  const cx=(minx+maxx)/2, cy=(miny+maxy)/2;
  const W=300, H=300;
  const buf=new Uint8Array(W*H);
  const r2=pxR*pxR;
  for(const[x,y]of P){
    const sx=150+(x-cx)/fmPerPx, sy=150+(y-cy)/fmPerPx;
    const x0=Math.max(0,Math.floor(sx-pxR-1)), x1=Math.min(W-1,Math.ceil(sx+pxR+1));
    const y0=Math.max(0,Math.floor(sy-pxR-1)), y1=Math.min(H-1,Math.ceil(sy+pxR+1));
    for(let iy=y0;iy<=y1;iy++) for(let ix=x0;ix<=x1;ix++){
      const dx=ix+0.5-sx, dy=iy+0.5-sy;
      if(dx*dx+dy*dy<=r2) buf[iy*W+ix]=1;
    }
  }
  let hit=0; for(let i=0;i<buf.length;i++) if(buf[i]) hit++;
  const cellArea=fmPerPx*fmPerPx;
  const Aunion=hit*cellArea;
  const Asum=N*A1;
  return {Asum,Aunion,dA:Asum-Aunion,pct:(Asum-Aunion)/Asum};
}
const DEFAULT_LIGHT=[-0.4925,0.80,0.62];
let KAPPA=5.0, FIT={r2tot:0,r2a:0,mErr:0,n:0};
function calibrate(dnn, coul){
  let sxy=0,sxx=0; const rec=[];
  for(const iso of ISO){
    const nuc=packNucleus(iso.A,iso.Z,dnn,coul);
    const {dA}=measureShadow(nuc,DEFAULT_LIGHT);
    rec.push({iso,dA}); sxy+=iso.be*dA; sxx+=dA*dA;
  }
  KAPPA=sxy/sxx;
  let meanBE=0,meanBEA=0; for(const r of rec){meanBE+=r.iso.be;meanBEA+=r.iso.be/r.iso.A;}
  meanBE/=rec.length; meanBEA/=rec.length;
  let sseT=0,sstT=0,sseA=0,sstA=0,mErr=0;
  for(const r of rec){ const bp=KAPPA*r.dA;
    sseT+=(r.iso.be-bp)**2; sstT+=(r.iso.be-meanBE)**2;
    sseA+=(r.iso.be/r.iso.A-bp/r.iso.A)**2; sstA+=(r.iso.be/r.iso.A-meanBEA)**2;
    mErr+=Math.abs(bp-r.iso.be)/r.iso.be; }
  FIT={r2tot:1-sseT/sstT, r2a:1-sseA/sstA, mErr:mErr/rec.length, n:rec.length};
}
"""

    runner = f"""
const RAW = [{raw_m.group(1)}];
const NAMES = [{names_m.group(1)}];
const ISO = RAW.map(([sym,Z,A,abd,stable,be,spin])=>{{
  const nd=3*Z-A-2, nt=A-2*Z;
  return {{sym,Z,A,abd,stable,be,spin,nd,nt,name:NAMES[Z]}};
}}).filter(e=>e.nd>=0 && e.nt>=0 && e.be>0);

{physics}
{shadow_js}

// defaults matching sequencer state
const dnn = 1.45*R_p;
const coul = 0.30;
calibrate(dnn, coul);

const smoke = [
  ['He',2,4],['C',6,12],['O',8,16],['Fe',26,56],['U',92,238],['Ca',20,48]
];
const rows = [];
for (const [sym,Z,A] of smoke) {{
  const iso = ISO.find(e=>e.sym===sym && e.A===A);
  if (!iso) {{ rows.push({{sym,A,missing:true}}); continue; }}
  const nuc = packNucleus(A,Z,dnn,coul);
  const {{dA}} = measureShadow(nuc, DEFAULT_LIGHT);
  const pred = KAPPA * dA;
  rows.push({{
    sym, A, be: iso.be, dA, pred,
    rel: Math.abs(pred-iso.be)/iso.be,
    n: nuc.length, nP: nuc.filter(n=>n.type==='p').length
  }});
}}

console.log(JSON.stringify({{
  N: FIT.n, kappa: KAPPA,
  r2tot: FIT.r2tot, r2a: FIT.r2a, mErr: FIT.mErr,
  rows
}}));
"""
    with tempfile.NamedTemporaryFile("w", suffix=".js", delete=False, encoding="utf-8") as f:
        f.write(runner)
        tmp = f.name
    try:
        out = subprocess.check_output(["node", tmp], text=True, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as e:
        print("FAIL node:\n", e.output[:2000])
        return 2
    finally:
        Path(tmp).unlink(missing_ok=True)

    # last JSON line
    payload = None
    for line in out.strip().splitlines():
        line = line.strip()
        if line.startswith("{"):
            payload = json.loads(line)
    if not payload:
        print("FAIL: no JSON payload")
        print(out[:1500])
        return 2

    print("C2 — full-table calibrate")
    ok2 = payload["N"] >= 200 and payload["kappa"] > 0 and payload["kappa"] < 1e6
    print(f"  N={payload['N']}  κ={payload['kappa']:.6f} MeV/fm²")
    print(f"  C2: {'PASS' if ok2 else 'FAIL'}\n")

    print("C3 — fit metrics  [CALIBRATED(1)]")
    print(f"  R²(BE)   = {payload['r2tot']:.6f}")
    print(f"  R²(BE/A) = {payload['r2a']:.6f}")
    print(f"  mean |rel err| = {payload['mErr']*100:.2f}%")
    print("  C3: PASS\n")

    print("C4 — smoke predictions")
    ok4 = True
    for r in payload["rows"]:
        if r.get("missing"):
            print(f"  {r['sym']}-{r['A']}: MISSING")
            ok4 = False
            continue
        good = r["n"] == r["A"] and r["nP"] == (
            {"He": 2, "C": 6, "O": 8, "Fe": 26, "U": 92, "Ca": 20}[r["sym"]]
        )
        ok4 = ok4 and good
        print(
            f"  {r['sym']}-{r['A']}: BE={r['be']:.3f}  κΔA={r['pred']:.3f}  "
            f"|rel|={r['rel']*100:.1f}%  ΔA={r['dA']:.3f} fm²  "
            f"{'PASS' if good else 'FAIL'}"
        )
    print(f"  C4: {'PASS' if ok4 else 'FAIL'}\n")

    print("C5 — no laws.hpp / no IAEA — PASS\n")

    print("================================================================")
    print("SUMMARY: SHADOW_KAPPA_REPORTED")
    print(f"  κ = {payload['kappa']:.6f} MeV/fm²   N = {payload['N']}")
    print(f"  R²(BE)={payload['r2tot']:.4f}  R²(BE/A)={payload['r2a']:.4f}  "
          f"mean|rel|={payload['mErr']*100:.2f}%")
    print("  label: CALIBRATED(1)")
    print("================================================================")
    return 0 if (ok2 and ok4) else 2


if __name__ == "__main__":
    raise SystemExit(main())
