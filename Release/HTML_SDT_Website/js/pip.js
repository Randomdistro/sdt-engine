/* ═══════════════════════════════════════════════════════════════════
   PIP — Nuclear Shell Structure Mini-Render
   
   The NUCLEAR shell geometry mirrors the ELECTRONIC shell geometry.
   Carbon (1α+4d): 4 L-shell positions + 2 α-poles = octahedron ✓
   Neon   (1α+8d): full square antiprism, 2s defect bonds to alpha ✓
   Cr half-fill:   3d pentagonal antiprism half-fill = closure gate ✓
   ═══════════════════════════════════════════════════════════════════ */
(function initPip() {
  const pipEl  = document.getElementById("pip");
  const pipC   = document.getElementById("pipCanvas");
  const pipCtx = pipC.getContext("2d");
  const pipLbl = document.getElementById("pipLabel");
  let pipAngle = 0;
  let pipIso   = null;
  let pipTilt  = 0.38; // slight X-tilt for depth

  pipEl.addEventListener("click", () => {
    if (!pipIso) return;
    window.open(`atomicus-stick.html#Z=${pipIso.Z}&A=${pipIso.A}`, "_blank");
  });
  window.__pipSetIso = function(iso) {
    pipIso = iso;
    if (pipLbl) pipLbl.textContent = iso
      ? `${iso.sym}-${iso.A} · 1α + ${iso.nd}d + ${iso.nt}t · click→stick`
      : "hover an isotope";
  };

  // ── Compact geometry helpers ──
  function pipV3(x,y,z){ return {x,y,z}; }
  function pipNorm(v){ const l=Math.sqrt(v.x*v.x+v.y*v.y+v.z*v.z)||1; return {x:v.x/l,y:v.y/l,z:v.z/l}; }
  function pipScale(v,s){ return {x:v.x*s,y:v.y*s,z:v.z*s}; }
  function pipAdd(a,b){ return {x:a.x+b.x,y:a.y+b.y,z:a.z+b.z}; }
  function pipDist(a,b){ const dx=a.x-b.x,dy=a.y-b.y,dz=a.z-b.z; return Math.sqrt(dx*dx+dy*dy+dz*dz); }

  function pipAntiprism(n, crush, rot) {
    if (rot === undefined) rot = 0;
    const pts=[];
    for(let i=0;i<n;i++){const a=(i/n)*2*Math.PI+rot;pts.push(pipV3(Math.cos(a),-crush,Math.sin(a)));}
    for(let i=0;i<n;i++){const a=(i/n)*2*Math.PI+rot+Math.PI/n;pts.push(pipV3(Math.cos(a),crush,Math.sin(a)));}
    return pts;
  }

  function pN(x,y,z){ const l=Math.sqrt(x*x+y*y+z*z); return pipV3(x/l,y/l,z/l); }
  const L_HUND = [
    pN( 1, 1, 1), pN( 1,-1,-1),
    pN(-1, 1,-1), pN(-1,-1, 1),
    pN(-1,-1,-1),
    pN(-1, 1, 1), pN( 1,-1, 1), pN( 1, 1,-1),
  ];
  const M_HUND = [
    pN(-1,-1,-1), pN(-1, 1, 1),
    pN( 1,-1, 1), pN( 1, 1,-1),
    pN( 1, 1, 1),
    pN( 1,-1,-1), pN(-1, 1,-1), pN(-1,-1, 1),
  ];
  const D_CR = 0.40;
  const D3_HUND = [
    ...Array.from({length:5},(_,i)=>{ const a=(i/5)*2*Math.PI; return pN(Math.cos(a),D_CR,Math.sin(a)); }),
    ...Array.from({length:5},(_,i)=>{ const a=(i/5)*2*Math.PI+Math.PI/5; return pN(Math.cos(a),-D_CR,Math.sin(a)); }),
  ];
  const P4_HUND = [pN(1,0,0),pN(0,1,0),pN(0,0,1), pN(-1,0,0),pN(0,-1,0),pN(0,0,-1)];
  const D4_HUND = [
    ...Array.from({length:5},(_,i)=>{ const a=(i/5)*2*Math.PI+Math.PI/10; return pN(Math.cos(a),D_CR,Math.sin(a)); }),
    ...Array.from({length:5},(_,i)=>{ const a=(i/5)*2*Math.PI+Math.PI/10+Math.PI/5; return pN(Math.cos(a),-D_CR,Math.sin(a)); }),
  ];
  const F4_CR = 0.36;
  const F4_HUND = [
    ...Array.from({length:7},(_,i)=>{ const a=(i/7)*2*Math.PI; return pN(Math.cos(a),F4_CR,Math.sin(a)); }),
    ...Array.from({length:7},(_,i)=>{ const a=(i/7)*2*Math.PI+Math.PI/7; return pN(Math.cos(a),-F4_CR,Math.sin(a)); }),
  ];

  const SC = 1.65;
  const PIP_SHELLS = [
    {s:'2s', cap:2,  sc:SC,   pts:L_HUND.slice(0,2)},
    {s:'2p', cap:6,  sc:SC,   pts:L_HUND.slice(2,8)},
    {s:'3s', cap:2,  sc:2.40, pts:M_HUND.slice(0,2)},
    {s:'3p', cap:6,  sc:2.40, pts:M_HUND.slice(2,8)},
    {s:'4s', cap:2,  sc:3.00, pts:[pN(0,1,0),pN(0,-1,0)]},
    {s:'3d', cap:10, sc:2.80, pts:D3_HUND},
    {s:'4p', cap:6,  sc:3.15, pts:P4_HUND},
    {s:'5s', cap:2,  sc:3.75, pts:[pN(0,1,0),pN(0,-1,0)]},
    {s:'4d', cap:10, sc:3.50, pts:D4_HUND},
    {s:'5p', cap:6,  sc:3.90, pts:[pN(0,1,0),pN(1,0,0),pN(0,0,1),pN(0,-1,0),pN(-1,0,0),pN(0,0,-1)]},
    {s:'6s', cap:2,  sc:4.50, pts:[pN(0,1,0),pN(0,-1,0)]},
    {s:'4f', cap:14, sc:4.20, pts:F4_HUND},
    {s:'5d', cap:10, sc:4.55, pts:D4_HUND.map(p=>pipV3(p.x,p.y,p.z))},
  ];
  const AUFBAU_PIP = ['2s','2p','3s','3p','4s','3d','4p','5s','4d','5p','6s','4f','5d'];

  const SCSS = {'2s':'255,145,40','2p':'210,230,45','3s':'255,235,55','3p':'140,55,240',
    '4s':'60,130,255','3d':'255,80,160','4p':'40,210,120','5s':'255,55,55',
    '4d':'165,70,255','5p':'35,230,230','6s':'35,180,160','4f':'255,185,35','5d':'190,228,90'};

  function buildPipGeo(iso) {
    const Z=iso.Z, nd=iso.nd, nt=iso.nt;
    const nodes=[], bonds=[];

    const aR=0.82;
    const alphaTetU=[pN(1,1,1),pN(1,-1,-1),pN(-1,1,-1),pN(-1,-1,1)];
    alphaTetU.forEach((u,i)=>nodes.push({
      p:pipV3(u.x*aR,u.y*aR,u.z*aR),
      r:6.5, isAlpha:true, isProton:i<2, shell:'alpha', slot:-1
    }));
    for(let i=0;i<4;i++) for(let j=i+1;j<4;j++) bonds.push({a:i,b:j,col:'rgba(160,60,220,0.65)',w:2,d:'solid'});

    if(nd===0&&nt===0) return {nodes,bonds};

    const slots=[];
    let rem=Z-2;
    for(const sn of AUFBAU_PIP){
      if(rem<=0) break;
      const def=PIP_SHELLS.find(d=>d.s===sn); if(!def) continue;
      const nf=Math.min(rem,def.cap);
      for(let i=0;i<nf;i++) slots.push({unitPos:def.pts[i],s:sn,sc:def.sc});
      rem-=nf;
    }

    const triSet=new Set();
    if(nt>0&&slots.length>0){
      let si=0,bY=-Infinity;
      slots.forEach((sl,i)=>{if(sl.unitPos.y>bY){bY=sl.unitPos.y;si=i;}});
      triSet.add(si);
      while(triSet.size<Math.min(nt,slots.length)){
        let best=-1,bd=-1;
        for(let i=0;i<slots.length;i++){
          if(triSet.has(i)) continue;
          let md=Infinity;
          for(const ti of triSet){const a=slots[i].unitPos,b=slots[ti].unitPos;const dx=a.x-b.x,dy=a.y-b.y,dz=a.z-b.z;const d=dx*dx+dy*dy+dz*dz;if(d<md)md=d;}
          if(md>bd){bd=md;best=i;}
        }
        if(best>=0) triSet.add(best); else break;
      }
    }

    const innerMap={'2s':['alpha'],'2p':['2s'],'3s':['2p','2s'],'3p':['3s','2p'],
      '4s':['3p','3s'],'3d':['4s','3p'],'4p':['3d','4s'],'5s':['4p','3d'],
      '4d':['5s','4p'],'5p':['4d','5s'],'6s':['5p','4d'],'4f':['6s','5p'],'5d':['4f','6s']};

    slots.forEach((sl,slotIdx)=>{
      const isTri=triSet.has(slotIdx);
      const sc=sl.sc, u=sl.unitPos;
      const ctr=pipScale(u,sc);
      const pPos=pipAdd(ctr,pipScale(u,0.26));
      const nPos=pipAdd(ctr,pipScale(u,-0.18));
      const rgb=SCSS[sl.s]||'40,200,220';
      const col=isTri?'rgba(220,40,220,0.85)':`rgba(${rgb},0.85)`;
      const pIdx=nodes.length;
      nodes.push({p:pPos,r:5.5,isProton:true,shell:sl.s,slot:slotIdx});
      const n1Idx=nodes.length;
      nodes.push({p:nPos,r:5,isProton:false,shell:sl.s,slot:slotIdx});
      bonds.push({a:pIdx,b:n1Idx,col,w:2.2,d:'solid'});

      if(isTri){
        const lat=pipNorm({x:-u.z,y:0,z:u.x});
        const n2Pos=pipAdd(pipAdd(ctr,pipScale(u,-0.28)),pipScale(lat,0.22));
        const n2Idx=nodes.length;
        nodes.push({p:n2Pos,r:4.5,isProton:false,shell:sl.s,slot:slotIdx,extra:true});
        bonds.push({a:n1Idx,b:n2Idx,col:'rgba(60,80,160,0.6)',w:1.5,d:'solid'});
      }

      const targets=innerMap[sl.s]||[];
      let bt=-1,bd=Infinity;
      for(let ni=0;ni<pIdx;ni++){
        if(!nodes[ni].isProton) continue;
        if(!targets.includes(nodes[ni].shell)) continue;
        const dp=pipDist(pPos,nodes[ni].p);
        if(dp<bd){bd=dp;bt=ni;}
      }
      if(bt<0){for(let ni=0;ni<pIdx;ni++){if(!nodes[ni].isProton) continue; const dp=pipDist(pPos,nodes[ni].p); if(dp<bd){bd=dp;bt=ni;}}}
      if(bt>=0){
        const op=sl.s==='2s'?0.50:0.16;
        bonds.push({a:bt,b:pIdx,col:`rgba(200,200,255,${op})`,w:sl.s==='2s'?1.5:0.8,d:sl.s==='2s'?'solid':'dashed'});
      }
    });

    return {nodes,bonds};
  }

  function pipProj(v, cx,cy, scl, sinA,cosA) {
    const rx = v.x*cosA - v.z*sinA;
    const ry = v.y;
    const rz = v.x*sinA + v.z*cosA;
    const sinT=Math.sin(pipTilt), cosT=Math.cos(pipTilt);
    const ry2 = ry*cosT - rz*sinT;
    const rz2 = ry*sinT + rz*cosT;
    const fov=3.5, d=fov/(fov+rz2*0.4);
    return {sx:cx+rx*scl*d, sy:cy-ry2*scl*d, dz:rz2};
  }

  function drawPip() {
    requestAnimationFrame(drawPip);
    pipAngle += 0.007;
    const pw=pipC.width/dpr, ph=pipC.height/dpr;
    pipCtx.setTransform(dpr,0,0,dpr,0,0);
    pipCtx.clearRect(0,0,pw,ph);

    const iso=pipIso;
    if(!iso){
      pipCtx.font="11px 'Segoe UI',sans-serif";
      pipCtx.fillStyle="rgba(80,70,60,0.55)";
      pipCtx.textAlign="center";
      pipCtx.fillText("hover an isotope",pw/2,ph/2-6);
      pipCtx.fillText("click → open stick model",pw/2,ph/2+8);
      return;
    }

    const geo=buildPipGeo(iso);
    const {nodes,bonds}=geo;
    const cx=pw/2, cy=ph/2;
    const maxSc = nodes.reduce((m,n)=>Math.max(m,Math.abs(n.p.x),Math.abs(n.p.y),Math.abs(n.p.z)),0)||1;
    const scl = Math.min(pw,ph)*0.36 / (maxSc+0.5);

    const sinA=Math.sin(pipAngle), cosA=Math.cos(pipAngle);
    const projected=nodes.map(n=>{const pr=pipProj(n.p,cx,cy,scl,sinA,cosA);return {...n,...pr};});

    const projBonds=bonds.map(b=>{
      const A=projected[b.a], B=projected[b.b];
      return {...b, ax:A.sx,ay:A.sy, bx:B.sx,by:B.sy, dz:(A.dz+B.dz)/2};
    });

    const allObjs=[
      ...projBonds.map(b=>({...b,type:'bond'})),
      ...projected.map(n=>({...n,type:'node'}))
    ].sort((a,b)=>a.dz-b.dz);

    allObjs.forEach(o=>{
      if(o.type==='bond'){
        pipCtx.save();
        if(o.d==='dashed') pipCtx.setLineDash([3,3]);
        pipCtx.beginPath();
        pipCtx.moveTo(o.ax,o.ay);
        pipCtx.lineTo(o.bx,o.by);
        pipCtx.strokeStyle=o.col;
        pipCtx.lineWidth=o.w;
        pipCtx.stroke();
        pipCtx.restore();
      } else {
        const r=o.r;
        const g=pipCtx.createRadialGradient(o.sx,o.sy,0,o.sx,o.sy,r*2);
        const gc=o.isAlpha?'130,50,220':o.isProton?'210,60,40':'40,110,200';
        g.addColorStop(0,`rgba(${gc},0.15)`); g.addColorStop(1,'transparent');
        pipCtx.beginPath(); pipCtx.arc(o.sx,o.sy,r*2,0,Math.PI*2);
        pipCtx.fillStyle=g; pipCtx.fill();
        const sg=pipCtx.createRadialGradient(o.sx-r*0.3,o.sy-r*0.3,r*0.05,o.sx,o.sy,r);
        if(o.isAlpha){sg.addColorStop(0,'rgba(200,120,255,0.95)');sg.addColorStop(1,'rgba(100,30,180,0.9)');}
        else if(o.isProton){sg.addColorStop(0,'rgba(255,120,90,0.95)');sg.addColorStop(1,'rgba(180,40,20,0.9)');}
        else{sg.addColorStop(0,'rgba(80,160,255,0.9)');sg.addColorStop(1,'rgba(20,60,160,0.85)');}
        pipCtx.beginPath(); pipCtx.arc(o.sx,o.sy,r,0,Math.PI*2);
        pipCtx.fillStyle=sg; pipCtx.fill();
      }
    });

    const topShell=iso.Z<=2?'K':iso.Z<=10?'L':iso.Z<=18?'M':iso.Z<=36?'N':iso.Z<=54?'O':iso.Z<=86?'P':'Q';
    pipCtx.font="bold 9px 'Segoe UI',sans-serif";
    pipCtx.fillStyle="rgba(212,160,92,0.75)";
    pipCtx.textAlign="left";
    pipCtx.fillText(`${topShell}-shell`, 6, ph-6);
  }

  drawPip();
})();
