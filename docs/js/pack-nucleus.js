/* Legacy NSEQ05 geometric comparison control.
   It preserves the constitutional 1α + nd·d + nt·t inventory and the NSEQ05
   shell-template experiment. It does NOT solve rim contact, whole-atom
   valence-stage construction order, or an alpha-governed polar spherical
   packing, and is therefore not the Atomicus nucleus.

   packNucleus(A, Z, dnn=1.45, coulSpread=0) → nucleon array carrying
   .contacts, .alphaGear, .alphaTetra, .subSeq, .shells and .grammar. */
(function (global) {
  'use strict';
  const R_p = 0.8414;
  const VERSION = 'NSEQ05-CONTROL-3';
  const DEFAULT_BOND_FM = 1.45;
  const SHELL_SEQ = Object.freeze([
    Object.freeze({sp:'d',cap:6, geom:'oct',    label:'D6'}),
    Object.freeze({sp:'d',cap:12,geom:'ico',    label:'D12-pre'}),
    Object.freeze({sp:'t',cap:8, geom:'stella', label:'T8'}),
    Object.freeze({sp:'d',cap:12,geom:'cuboct', label:'D12-cuboct'}),
    Object.freeze({sp:'t',cap:10,geom:'polar',  label:'T10'}),
    Object.freeze({sp:'d',cap:20,geom:'fib',    label:'D20'}),
    Object.freeze({sp:'t',cap:12,geom:'polar',  label:'T12'}),
    Object.freeze({sp:'d',cap:30,geom:'fib',    label:'D30'}),
    Object.freeze({sp:'t',cap:14,geom:'t14',    label:'T14'}),
    Object.freeze({sp:'d',cap:42,geom:'fib',    label:'D42'}),
    Object.freeze({sp:'t',cap:16,geom:'polar',  label:'T16'}),
    Object.freeze({sp:'d',cap:56,geom:'fib',    label:'D56'}),
    Object.freeze({sp:'t',cap:18,geom:'polar',  label:'T18'}),
  ]);

  function vnorm(v){const l=Math.hypot(v[0],v[1],v[2])||1;return[v[0]/l,v[1]/l,v[2]/l];}
  function grammar(A,Z){
    const nd=3*Z-A-2, nt=A-2*Z;
    return {A,Z,nd,nt,valid:Number.isInteger(A)&&Number.isInteger(Z)&&Z>=2&&A>=Z&&nd>=0&&nt>=0};
  }
  function packNucleus(A, Z, dnn, coulSpread){
    const g=grammar(A,Z);
    if(!g.valid) throw new RangeError(`invalid alpha grammar for Z=${Z}, A=${A}`);
    dnn = dnn == null ? DEFAULT_BOND_FM : dnn;
    coulSpread = coulSpread == null ? 0 : coulSpread;
    const {nd,nt}=g;
    const spread=1+coulSpread*(Z*Z)/Math.pow(A,4/3);
    const D=dnn*spread;
    const nuc=[];
    nuc.version=VERSION;
    nuc.classification='LEGACY_GEOMETRIC_CONTROL';
    nuc.contactGeometry=false;
    nuc.grammar=g;
    nuc.contacts=[];
    nuc.shells=[];
    nuc.bondD=D;
    nuc.coulombSpread=coulSpread;
    nuc.partialSeatPolicy='registered seats: deuterons use a maximum-separation subset; tritons retain N/S-first fill order';
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
    nuc.subSeq=[{group:'alpha',sub:0,sp:'α',name:'α',cap:1,shell:0,seat:0}];
    nuc.shells.push({
      index:0, scheduleIndex:-1, species:'alpha', label:'α core',
      capacity:1, occupancy:1, geometry:'contact tetrahedron', full:true,
    });
    const alphaOut=Math.max(...alphaIds.map(i=>Math.hypot(...nuc[i].pos)));

    const PHI=(1+Math.sqrt(5))/2;
    const R_OPEN_SCALE=1.05, R_CLOSE_SCALE=0.95;
    const dirsOct=()=>[[0,0,1],[0,0,-1],[1,0,0],[-1,0,0],[0,1,0],[0,-1,0]];
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
    const shellDirs=(geom,cap,seed)=>{
      if(geom==='oct') return dirsOct();
      if(geom==='ico') return dirsIco();
      if(geom==='cuboct') return dirsCuboct();
      if(geom==='stella') return dirsPolar(8,seed);
      if(geom==='t14') return dirsT14();
      if(geom==='polar') return dirsPolar(cap,seed);
      return dirsFib(cap,seed);
    };
    const rotateDirs=(dirs,seed)=>{
      const a=(seed||0)*Math.PI*(3-Math.sqrt(5)), c=Math.cos(a),s=Math.sin(a);
      return dirs.map(v=>[c*v[0]-s*v[1],s*v[0]+c*v[1],v[2]]);
    };
    const openDirs=(m,seed)=>{
      if(m<=0) return [];
      let out;
      if(m===1) out=[[0,0,(seed%2)?-1:1]];
      else if(m===2) out=[[0,0,1],[0,0,-1]];
      else if(m===3) out=[[1,0,0],[-0.5,Math.sqrt(3)/2,0],[-0.5,-Math.sqrt(3)/2,0]];
      else if(m===4) out=[[1,1,1],[1,-1,-1],[-1,1,-1],[-1,-1,1]].map(vnorm);
      else if(m===5) out=[[0,0,1],[0,0,-1],[1,0,0],[-0.5,Math.sqrt(3)/2,0],[-0.5,-Math.sqrt(3)/2,0]];
      else if(m===6) out=dirsOct();
      else if(m===7){
        out=[[0,0,1],[0,0,-1]];
        for(let k=0;k<5;k++) out.push([Math.cos(2*Math.PI*k/5),Math.sin(2*Math.PI*k/5),0]);
      } else out=dirsFib(m,seed);
      return rotateDirs(out,seed);
    };
    const farthestSeats=(dirs,m)=>{
      const seats=dirs.map((dir,seat)=>({dir,seat}));
      if(m>=seats.length) return seats;
      const chosen=[0];
      while(chosen.length<m){
        let best=-1,bestScore=-1;
        for(let i=0;i<seats.length;i++){
          if(chosen.includes(i)) continue;
          let nearest=Infinity;
          for(const j of chosen){
            const a=seats[i].dir,b=seats[j].dir;
            const d2=(a[0]-b[0])**2+(a[1]-b[1])**2+(a[2]-b[2])**2;
            nearest=Math.min(nearest,d2);
          }
          if(nearest>bestScore+1e-12){best=i;bestScore=nearest;}
        }
        chosen.push(best);
      }
      return chosen.map(i=>seats[i]);
    };
    const occupiedSeats=(sh,m,seed)=>{
      const dirs=shellDirs(sh.geom,sh.cap,seed);
      if(m===sh.cap) return dirs.map((dir,seat)=>({dir,seat}));
      if(sh.sp==='t') return dirs.slice(0,m).map((dir,seat)=>({dir,seat}));
      return farthestSeats(dirs,m);
    };
    let rTier=alphaOut+D*1.05, dSub=0, tSub=0, shellIdx=0;
    let ndLeft=Math.max(0,nd), ntLeft=Math.max(0,nt), lastP=[];
    const restBond=nId=>{
      let bi=-1,bd_=1e18;
      const rest=lastP.length?lastP:alphaIds.filter(i=>nuc[i].type==='p');
      for(const i of rest){ const q=nuc[i].pos,
        dd=Math.hypot(q[0]-nuc[nId].pos[0],q[1]-nuc[nId].pos[1],q[2]-nuc[nId].pos[2]);
        if(dd<bd_){bd_=dd;bi=i;} }
      if(bi>=0) bond(bi,nId);
    };
    for(let scheduleIndex=0;scheduleIndex<SHELL_SEQ.length;scheduleIndex++){
      const sh=SHELL_SEQ[scheduleIndex];
      if(sh.sp==='d'){
        const m=Math.min(ndLeft,sh.cap); if(m<=0) continue;
        const seats=occupiedSeats(sh,m,shellIdx);
        const shell={index:shellIdx+1,scheduleIndex,species:'d',label:sh.label,
          capacity:sh.cap,occupancy:m,geometry:sh.geom,full:m===sh.cap};
        nuc.shells.push(shell);
        const newP=[];
        for(const occupied of seats){
          const v=occupied.dir, seat=occupied.seat;
          const nIn =push([v[0]*(rTier-D/2),v[1]*(rTier-D/2),v[2]*(rTier-D/2)],'n','deuteron',dSub,[ v[0], v[1], v[2]],shellIdx+1);
          const pOut=push([v[0]*(rTier+D/2),v[1]*(rTier+D/2),v[2]*(rTier+D/2)],'p','deuteron',dSub,[-v[0],-v[1],-v[2]],shellIdx+1);
          bond(nIn,pOut); newP.push(pOut); restBond(nIn);
          nuc.subSeq.push({group:'deuteron',sub:dSub,sp:'d',name:sh.label,geom:sh.geom,
            cap:sh.cap,shell:shell.index,seat,occupancy:m,full:shell.full});
          dSub++;
        }
        lastP=newP; ndLeft-=m; shellIdx++; rTier+=2*D;
      }else{
        const m=Math.min(ntLeft,sh.cap); if(m<=0) continue;
        const seats=occupiedSeats(sh,m,shellIdx);
        const shell={index:shellIdx+1,scheduleIndex,species:'t',label:sh.label,
          capacity:sh.cap,occupancy:m,geometry:sh.geom,full:m===sh.cap};
        nuc.shells.push(shell);
        const newP=[];
        for(const occupied of seats){
          const v=occupied.dir, seat=occupied.seat, open=(seat%2===0);
          const rc=rTier*(open?R_OPEN_SCALE:R_CLOSE_SCALE);
          const n1=push([v[0]*(rc-D),v[1]*(rc-D),v[2]*(rc-D)],'n','triton',tSub,[ v[0], v[1], v[2]],shellIdx+1);
          const p =push([v[0]* rc,   v[1]* rc,   v[2]* rc   ],'p','triton',tSub,[-v[0],-v[1],-v[2]],shellIdx+1);
          const n2=push([v[0]*(rc+D),v[1]*(rc+D),v[2]*(rc+D)],'n','triton',tSub,[-v[0],-v[1],-v[2]],shellIdx+1);
          bond(n1,p); bond(p,n2); restBond(n1); newP.push(p);
          nuc.subSeq.push({group:'triton',sub:tSub,sp:'t',name:sh.label,geom:sh.geom,
            cap:sh.cap,shell:shell.index,seat,occupancy:m,full:shell.full});
          tSub++;
        }
        lastP=newP; ntLeft-=m; shellIdx++; rTier+=2.2*D;
      }
    }
    while(ndLeft>0){
      const m=Math.min(ndLeft,56), dirs=openDirs(m,shellIdx), newP=[];
      const shell={index:shellIdx+1,scheduleIndex:SHELL_SEQ.length,species:'d',label:'D*',
        capacity:56,occupancy:m,geometry:'fib',full:m===56};
      nuc.shells.push(shell);
      for(let seat=0;seat<dirs.length;seat++){
        const v=dirs[seat];
        const nIn =push([v[0]*(rTier-D/2),v[1]*(rTier-D/2),v[2]*(rTier-D/2)],'n','deuteron',dSub,[ v[0], v[1], v[2]],shellIdx+1);
        const pOut=push([v[0]*(rTier+D/2),v[1]*(rTier+D/2),v[2]*(rTier+D/2)],'p','deuteron',dSub,[-v[0],-v[1],-v[2]],shellIdx+1);
        bond(nIn,pOut); newP.push(pOut); restBond(nIn);
        nuc.subSeq.push({group:'deuteron',sub:dSub,sp:'d',name:'D*',geom:'fib',
          cap:56,shell:shell.index,seat,occupancy:m,full:shell.full});
        dSub++;
      }
      lastP=newP; ndLeft-=m; shellIdx++; rTier+=2*D;
    }
    while(ntLeft>0){
      const m=Math.min(ntLeft,18), dirs=openDirs(m,shellIdx);
      const shell={index:shellIdx+1,scheduleIndex:SHELL_SEQ.length+1,species:'t',label:'T*',
        capacity:18,occupancy:m,geometry:'polar',full:m===18};
      nuc.shells.push(shell);
      const newP=[];
      for(let i=0;i<dirs.length;i++){
        const v=dirs[i], open=(i%2===0), rc=rTier*(open?R_OPEN_SCALE:R_CLOSE_SCALE);
        const n1=push([v[0]*(rc-D),v[1]*(rc-D),v[2]*(rc-D)],'n','triton',tSub,[ v[0], v[1], v[2]],shellIdx+1);
        const p =push([v[0]* rc,   v[1]* rc,   v[2]* rc   ],'p','triton',tSub,[-v[0],-v[1],-v[2]],shellIdx+1);
        const n2=push([v[0]*(rc+D),v[1]*(rc+D),v[2]*(rc+D)],'n','triton',tSub,[-v[0],-v[1],-v[2]],shellIdx+1);
        bond(n1,p); bond(p,n2); restBond(n1); newP.push(p);
        nuc.subSeq.push({group:'triton',sub:tSub,sp:'t',name:'T*',geom:'polar',
          cap:18,shell:shell.index,seat:i,occupancy:m,full:shell.full});
        tSub++;
      }
      lastP=newP; ntLeft-=m; shellIdx++; rTier+=2.2*D;
    }
    return nuc;
  }
  global.SDT_R_p = R_p;
  global.SDT_NUCLEAR_PACKING = Object.freeze({
    version:VERSION,
    classification:'LEGACY_GEOMETRIC_CONTROL',
    contactGeometry:false,
    R_p,
    defaultBondFm:DEFAULT_BOND_FM,
    shellSequence:SHELL_SEQ,
    grammar,
  });
  global.packNucleus = packNucleus;
})(typeof window !== 'undefined' ? window : globalThis);
