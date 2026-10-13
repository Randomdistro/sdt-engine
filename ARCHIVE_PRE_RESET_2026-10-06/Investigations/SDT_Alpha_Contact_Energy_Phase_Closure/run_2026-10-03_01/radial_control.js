'use strict';
const fs=require('fs'),path=require('path');
const RUN=__dirname,ROOT=path.resolve(RUN,'../../..');
require(path.join(ROOT,'Release/HTML_SDT_Website/js/nuclear-inputs.js'));require(path.join(ROOT,'Release/HTML_SDT_Website/js/traction-gear-engine.js'));
const g=global.SDT_TRACTION_GEAR,base=JSON.parse(fs.readFileSync(path.join(RUN,'BASELINE.json'),'utf8'));
const qmul=(a,b)=>[a[3]*b[0]+a[0]*b[3]+a[1]*b[2]-a[2]*b[1],a[3]*b[1]-a[0]*b[2]+a[1]*b[3]+a[2]*b[0],a[3]*b[2]+a[0]*b[1]-a[1]*b[0]+a[2]*b[3],a[3]*b[3]-a[0]*b[0]-a[1]*b[1]-a[2]*b[2]];
const poses=base.observableLedger.poses.map((p,i)=>{const phi=i*Math.PI/2;return {...p,orientation:qmul([0,0,Math.sin(phi/2),Math.cos(phi/2)],[0,Math.SQRT1_2,0,Math.SQRT1_2])};});
const norm=v=>Math.hypot(...v),sub=(a,b)=>a.map((v,i)=>v-b[i]),add=(a,b)=>a.map((v,i)=>v+b[i]),mul=(a,s)=>a.map(v=>v*s),cross=(a,b)=>[a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]];
const centres=poses.map(p=>p.centreRp),axes=centres.map(c=>mul(c,1/norm(c)));
const slips=base.contacts.map(e=>{const n=mul(sub(centres[e.b],centres[e.a]),.5);const wa=mul(axes[e.a],poses[e.a].type==='p'?1:-1),wb=mul(axes[e.b],poses[e.b].type==='p'?1:-1);return {a:e.a,b:e.b,slip:norm(cross(add(wa,wb),n))};});
function frozenSegments(p,n){const cal=base.calibration,common={...p,handedness:1};let s=g.transformWakeSegments(common,n).map(e=>({...e,weight:e.weight*cal.protonBridgeMuNPerGeometricMoment}));if(p.type==='n')s=s.concat(g.transformWakeSegments({...common,handedness:-1,toroidalPhase:(p.toroidalPhase||0)+cal.phaseOffsetRadians},n).map(e=>({...e,weight:e.weight*cal.seatedElectronCoefficientMuNPerGeometricMoment})));return s;}
const moments=poses.map(p=>g.segmentMoment(frozenSegments(p,16))),sum=moments.reduce(add,[0,0,0]);
const result={scope:'conditional spherical rigid-rolling and calibrated circulation proxy at radial symmetry frames; frozen baseline bridges; no state-energy or finite-contact promotion',frozenBaselineCalibration:true,poses,moments,sumVectorMuN:sum,magnitudeMuN:norm(sum),normalizedCancellation:norm(sum)/moments.reduce((s,m)=>s+norm(m),0),slips};
fs.writeFileSync(path.join(RUN,'RADIAL_KINEMATIC_CONTROL.json'),JSON.stringify(result,null,2));
console.log(JSON.stringify({moment:sum,magnitude:norm(sum),maxSlip:Math.max(...slips.map(e=>e.slip))}));
