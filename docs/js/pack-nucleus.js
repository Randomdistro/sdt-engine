/* Shared spherical-tier packing — same geometry as nuclear-packing-sequencer.html.
   packNucleus(A, Z, dnn=1.45, coulSpread=0) → nucleon array with .contacts, .alphaGear, .alphaTetra. */
(function (global) {
  'use strict';
  const R_p = 0.8414;
  function vnorm(v){const l=Math.hypot(v[0],v[1],v[2])||1;return[v[0]/l,v[1]/l,v[2]/l];}
  function packNucleus(A, Z, dnn, coulSpread){
    dnn = dnn == null ? 1.45 : dnn;
    coulSpread = coulSpread == null ? 0 : coulSpread;
    const nd=3*Z-A-2, nt=A-2*Z;
    const spread=1+coulSpread*(Z*Z)/Math.pow(A,4/3);
    const D=dnn*spread;
    const nuc=[]; nuc.contacts=[]; nuc.bondD=D;
    const push=(pos,type,group,sub,axis,tier)=>{
      const n={pos,type,group,sub,axis,tier:tier||0,id:nuc.length}; nuc.push(n); return n.id; };
    const bond=(i,j)=>nuc.contacts.push([i,j]);

    const GAM=0.95;
    const b_=GAM, h_=Math.sqrt(1-b_*b_/4), y0_=(h_*h_-b_*b_/4)/(2*h_);
    const r_=Math.hypot(b_/4, y0_-h_/2);
    const aEdge=R_p/r_;
    const bEdge=GAM*aEdge, zT=Math.sqrt(aEdge*aEdge-bEdge*bEdge/2)/2;
    const VT=[[ bEdge/2,0, zT],[-bEdge/2,0, zT],
              [0, bEdge/2,-zT],[0,-bEdge/2,-zT]];
    const FACES=[ {v:[0,1,2],w:2,t:'p'}, {v:[0,1,3],w:3,t:'p'},
                  {v:[0,2,3],w:0,t:'n'}, {v:[1,2,3],w:1,t:'n'} ];
    const alphaIds=[];
    for(const f of FACES){
      const W=VT[f.w], oth=f.v.filter(i=>i!==f.w);
      const M=[(VT[oth[0]][0]+VT[oth[1]][0])/2,(VT[oth[0]][1]+VT[oth[1]][1])/2,(VT[oth[0]][2]+VT[oth[1]][2])/2];
      const s=y0_/h_;
      const c=[M[0]+(W[0]-M[0])*s, M[1]+(W[1]-M[1])*s, M[2]+(W[2]-M[2])*s];
      const e1=[VT[f.v[1]][0]-VT[f.v[0]][0],VT[f.v[1]][1]-VT[f.v[0]][1],VT[f.v[1]][2]-VT[f.v[0]][2]];
      const e2=[VT[f.v[2]][0]-VT[f.v[0]][0],VT[f.v[2]][1]-VT[f.v[0]][1],VT[f.v[2]][2]-VT[f.v[0]][2]];
      let nx=e1[1]*e2[2]-e1[2]*e2[1], ny=e1[2]*e2[0]-e1[0]*e2[2], nz=e1[0]*e2[1]-e1[1]*e2[0];
      if(nx*c[0]+ny*c[1]+nz*c[2]<0){nx=-nx;ny=-ny;nz=-nz;}
      const id=push(c,f.t,'alpha',0,vnorm([nx,ny,nz]),0);
      nuc[id].ringR=R_p; alphaIds.push(id);
    }
    bond(alphaIds[0],alphaIds[2]); bond(alphaIds[0],alphaIds[3]);
    bond(alphaIds[1],alphaIds[2]); bond(alphaIds[1],alphaIds[3]);
    const eMid=(i,j)=>[(VT[i][0]+VT[j][0])/2,(VT[i][1]+VT[j][1])/2,(VT[i][2]+VT[j][2])/2];
    nuc.alphaGear=[eMid(0,2),eMid(1,2),eMid(0,3),eMid(1,3)];
    nuc.alphaTetra=VT;
    nuc.subSeq=[{group:'alpha',sub:0,sp:'α',name:'α',cap:1}];
    const alphaOut=Math.max(...alphaIds.map(i=>Math.hypot(...nuc[i].pos)));

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
    const dirsPolar=(cap,seed)=>{ const nBand=cap/2-1, z=1/3, rho=Math.sqrt(1-z*z),
      az0=(seed||0)*0.15, s=[[0,0,1],[0,0,-1]];
      for(let k=0;k<nBand;k++){ const thO=az0+k*(2*Math.PI/nBand), thC=az0+Math.PI/nBand+k*(2*Math.PI/nBand);
        s.push(vnorm([rho*Math.cos(thO),rho*Math.sin(thO),-z]));
        s.push(vnorm([rho*Math.cos(thC),rho*Math.sin(thC),+z])); }
      return s; };
    const dirsT14=()=>{ const s=1/Math.sqrt(3);
      return [[s,s,s],[s,-s,-s],[-s,s,-s],[-s,-s,s],[-s,-s,-s],[-s,s,s],[s,-s,s],[s,s,-s],
        [1,0,0],[-1,0,0],[0,1,0],[0,-1,0],[0,0,1],[0,0,-1]].map(vnorm); };
    const SHELL_SEQ=[
      {sp:'d',cap:6, geom:'oct'}, {sp:'d',cap:12,geom:'ico'}, {sp:'t',cap:8, geom:'stella'},
      {sp:'d',cap:12,geom:'cuboct'}, {sp:'t',cap:10,geom:'polar'}, {sp:'d',cap:20,geom:'fib'},
      {sp:'t',cap:12,geom:'polar'}, {sp:'d',cap:30,geom:'fib'}, {sp:'t',cap:14,geom:'t14'},
      {sp:'d',cap:42,geom:'fib'}, {sp:'t',cap:16,geom:'polar'}, {sp:'d',cap:56,geom:'fib'},
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
    let ndLeft=Math.max(0,nd), ntLeft=Math.max(0,nt), lastP=[];
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
          bond(nIn,pOut); newP.push(pOut); restBond(nIn,1.6);
          nuc.subSeq.push({group:'deuteron',sub:dSub,sp:'d',name:'D'+sh.cap,geom:sh.geom,cap:sh.cap});
          dSub++;
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
          bond(n1,p); bond(p,n2); restBond(n1,1.8);
          nuc.subSeq.push({group:'triton',sub:tSub,sp:'t',name:'T'+sh.cap,geom:sh.geom,cap:sh.cap});
          tSub++;
        }
        ntLeft-=m; shellIdx++; rTier+=2.2*D;
      }
    }
    while(ndLeft>0){
      const m=Math.min(ndLeft,56); const dirs=dirsFib(m,shellIdx).slice(0,m); const newP=[];
      for(const v of dirs){
        const nIn =push([v[0]*(rTier-D/2),v[1]*(rTier-D/2),v[2]*(rTier-D/2)],'n','deuteron',dSub,[ v[0], v[1], v[2]],shellIdx+1);
        const pOut=push([v[0]*(rTier+D/2),v[1]*(rTier+D/2),v[2]*(rTier+D/2)],'p','deuteron',dSub,[-v[0],-v[1],-v[2]],shellIdx+1);
        bond(nIn,pOut); newP.push(pOut); restBond(nIn,1.6);
        nuc.subSeq.push({group:'deuteron',sub:dSub,sp:'d',name:'D*',geom:'fib',cap:56});
        dSub++;
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
        bond(n1,p); bond(p,n2); restBond(n1,1.8);
        nuc.subSeq.push({group:'triton',sub:tSub,sp:'t',name:'T*',geom:'polar',cap:18});
        tSub++;
      }
      ntLeft-=m; shellIdx++; rTier+=2.2*D;
    }
    return nuc;
  }
  global.SDT_R_p = R_p;
  global.packNucleus = packNucleus;
})(typeof window !== 'undefined' ? window : globalThis);
