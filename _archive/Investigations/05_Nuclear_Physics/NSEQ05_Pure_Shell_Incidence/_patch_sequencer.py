#!/usr/bin/env python3
"""Apply NSEQ05 pure-shell packer to site + docs sequencers."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]

NEW = r"""
  // ── Pure-shell packing (NSEQ05): species-alternating shells, not all-d then all-t ──
  // Sequence: D6→D12→T8→D12→T10→D20→T12→D30→T14→D42→T16→…
  // Capacities unchanged; geometry: T8=stella, post-T8 D12=cuboct, T14=cuboct face-normals.
  const PHI=(1+Math.sqrt(5))/2;
  const R_OPEN_SCALE=1.05, R_CLOSE_SCALE=0.95;
  const dirsOct=()=>[[1,0,0],[-1,0,0],[0,1,0],[0,-1,0],[0,0,1],[0,0,-1]];
  const dirsIco=()=>[[0,1,PHI],[0,-1,PHI],[0,1,-PHI],[0,-1,-PHI],[1,PHI,0],[-1,PHI,0],
    [1,-PHI,0],[-1,-PHI,0],[PHI,0,1],[-PHI,0,1],[PHI,0,-1],[-PHI,0,-1]].map(vnorm);
  const dirsCuboct=()=>{ const o=[]; for(const x of[-1,1]) for(const y of[-1,1]){
      o.push([x,y,0],[x,0,y],[0,x,y]); } return o.map(vnorm); };
  const dirsFib=(m,seed)=>{ const out=[]; for(let i=0;i<m;i++){ const zz=1-(2*i+1)/m,
      rr=Math.sqrt(Math.max(0,1-zz*zz)), th=2*Math.PI*((i+(seed||0)*0.37)%m)/(PHI*PHI);
      out.push([rr*Math.cos(th),rr*Math.sin(th),zz]); } return out; };
  // Polar / stella family: poles + interleaved tropics at ±arcsin(1/3); open on even index
  const dirsPolar=(cap,seed)=>{ const nBand=cap/2-1, z=1/3, rho=Math.sqrt(1-z*z),
    az0=(seed||0)*0.15, s=[[0,0,1],[0,0,-1]];
    for(let k=0;k<nBand;k++){ const thO=az0+k*(2*Math.PI/nBand), thC=az0+Math.PI/nBand+k*(2*Math.PI/nBand);
      s.push(vnorm([rho*Math.cos(thO),rho*Math.sin(thO),-z]));
      s.push(vnorm([rho*Math.cos(thC),rho*Math.sin(thC),+z])); }
    return s; };
  // T14 = cuboct face normals: 8△ (±1,±1,±1) ∪ 6□ (±e_i)
  const dirsT14=()=>{ const s=1/Math.sqrt(3);
    return [[s,s,s],[s,-s,-s],[-s,s,-s],[-s,-s,s],[-s,-s,-s],[-s,s,s],[s,-s,s],[s,s,-s],
      [1,0,0],[-1,0,0],[0,1,0],[0,-1,0],[0,0,1],[0,0,-1]].map(vnorm); };
  const SHELL_SEQ=[
    {sp:'d',cap:6, geom:'oct'},
    {sp:'d',cap:12,geom:'ico'},
    {sp:'t',cap:8, geom:'stella'},
    {sp:'d',cap:12,geom:'cuboct'},
    {sp:'t',cap:10,geom:'polar'},
    {sp:'d',cap:20,geom:'fib'},
    {sp:'t',cap:12,geom:'polar'},
    {sp:'d',cap:30,geom:'fib'},
    {sp:'t',cap:14,geom:'t14'},
    {sp:'d',cap:42,geom:'fib'},
    {sp:'t',cap:16,geom:'polar'},
    {sp:'d',cap:56,geom:'fib'},
    {sp:'t',cap:18,geom:'polar'},
  ];
  const shellDirs=(geom,cap,seed)=>{
    if(geom==='oct') return dirsOct();
    if(geom==='ico') return dirsIco();
    if(geom==='cuboct') return dirsCuboct();
    if(geom==='stella') return dirsPolar(8,seed);
    if(geom==='t14') return dirsT14();
    if(geom==='polar') return dirsPolar(cap,seed);
    return dirsFib(cap,seed);
  };
  let rTier=alphaOut+D*1.05, dSub=0, tSub=0, shellIdx=0;
  let ndLeft=nd, ntLeft=nt, lastP=[];
  const restBond=(nId,scale)=>{
    let bi=-1,bd_=1e18;
    const rest=lastP.length?lastP:alphaIds.filter(i=>nuc[i].type==='p');
    for(const i of rest){ const q=nuc[i].pos,
      dd=Math.hypot(q[0]-nuc[nId].pos[0],q[1]-nuc[nId].pos[1],q[2]-nuc[nId].pos[2]);
      if(dd<bd_){bd_=dd;bi=i;} }
    if(bi>=0&&bd_<=scale*D) bond(bi,nId);
  };
  for(const sh of SHELL_SEQ){
    if(sh.sp==='d'){
      const m=Math.min(ndLeft,sh.cap); if(m<=0) continue;
      const dirs=shellDirs(sh.geom,sh.cap,shellIdx).slice(0,m);
      const newP=[];
      for(const v of dirs){
        const nIn =push([v[0]*(rTier-D/2),v[1]*(rTier-D/2),v[2]*(rTier-D/2)],'n','deuteron',dSub,[ v[0], v[1], v[2]],shellIdx+1);
        const pOut=push([v[0]*(rTier+D/2),v[1]*(rTier+D/2),v[2]*(rTier+D/2)],'p','deuteron',dSub,[-v[0],-v[1],-v[2]],shellIdx+1);
        bond(nIn,pOut); newP.push(pOut); restBond(nIn,1.6); dSub++;
      }
      lastP=newP; ndLeft-=m; shellIdx++; rTier+=2*D;
    }else{
      const m=Math.min(ntLeft,sh.cap); if(m<=0) continue;
      const dirs=shellDirs(sh.geom,sh.cap,shellIdx).slice(0,m);
      for(let i=0;i<dirs.length;i++){
        const v=dirs[i], open=(i%2===0);
        const rc=rTier*(open?R_OPEN_SCALE:R_CLOSE_SCALE);
        const n1=push([v[0]*(rc-D),v[1]*(rc-D),v[2]*(rc-D)],'n','triton',tSub,[ v[0], v[1], v[2]],shellIdx+1);
        const p =push([v[0]* rc,   v[1]* rc,   v[2]* rc   ],'p','triton',tSub,[-v[0],-v[1],-v[2]],shellIdx+1);
        const n2=push([v[0]*(rc+D),v[1]*(rc+D),v[2]*(rc+D)],'n','triton',tSub,[-v[0],-v[1],-v[2]],shellIdx+1);
        bond(n1,p); bond(p,n2); restBond(n1,1.8); tSub++;
      }
      ntLeft-=m; shellIdx++; rTier+=2.2*D;
    }
  }
  while(ndLeft>0){
    const m=Math.min(ndLeft,56); const dirs=dirsFib(m,shellIdx).slice(0,m); const newP=[];
    for(const v of dirs){
      const nIn =push([v[0]*(rTier-D/2),v[1]*(rTier-D/2),v[2]*(rTier-D/2)],'n','deuteron',dSub,[ v[0], v[1], v[2]],shellIdx+1);
      const pOut=push([v[0]*(rTier+D/2),v[1]*(rTier+D/2),v[2]*(rTier+D/2)],'p','deuteron',dSub,[-v[0],-v[1],-v[2]],shellIdx+1);
      bond(nIn,pOut); newP.push(pOut); restBond(nIn,1.6); dSub++;
    }
    lastP=newP; ndLeft-=m; shellIdx++; rTier+=2*D;
  }
  while(ntLeft>0){
    const m=Math.min(ntLeft,18); const dirs=dirsPolar(Math.max(m + (m%2), 2),shellIdx).slice(0,m);
    for(let i=0;i<dirs.length;i++){
      const v=dirs[i], open=(i%2===0), rc=rTier*(open?R_OPEN_SCALE:R_CLOSE_SCALE);
      const n1=push([v[0]*(rc-D),v[1]*(rc-D),v[2]*(rc-D)],'n','triton',tSub,[ v[0], v[1], v[2]],shellIdx+1);
      const p =push([v[0]* rc,   v[1]* rc,   v[2]* rc   ],'p','triton',tSub,[-v[0],-v[1],-v[2]],shellIdx+1);
      const n2=push([v[0]*(rc+D),v[1]*(rc+D),v[2]*(rc+D)],'n','triton',tSub,[-v[0],-v[1],-v[2]],shellIdx+1);
      bond(n1,p); bond(p,n2); restBond(n1,1.8); tSub++;
    }
    ntLeft-=m; shellIdx++; rTier+=2.2*D;
  }
  return nuc;
}
"""


def patch(path: Path) -> None:
    t = path.read_text(encoding="utf-8")
    start = t.find("  // ── deuteron tiers:")
    if start < 0:
        start = t.find("  // ── Pure-shell packing")
    if start < 0:
        start = t.find("  // ── triton shells")
    if start < 0:
        raise RuntimeError(f"no start in {path}")
    end_marker = "\n/* ---- number of subunits"
    end = t.find(end_marker, start)
    if end < 0:
        raise RuntimeError(f"no end in {path}")
    new_t = t[:start] + NEW.strip("\n") + "\n" + t[end:]
    path.write_text(new_t, encoding="utf-8")
    print(f"patched {path} SHELL_SEQ={('SHELL_SEQ' in new_t)}")


def main() -> int:
    for rel in [
        "Release/HTML_SDT_Website/nuclear-packing-sequencer.html",
        "docs/nuclear-packing-sequencer.html",
    ]:
        patch(ROOT / rel)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
