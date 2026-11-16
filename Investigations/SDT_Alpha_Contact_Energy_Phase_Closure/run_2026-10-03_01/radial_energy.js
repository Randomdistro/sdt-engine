'use strict';
const fs=require('fs'),path=require('path');
const RUN=__dirname,ROOT=path.resolve(RUN,'../../..');
require(path.join(ROOT,'Release/HTML_SDT_Website/js/nuclear-inputs.js'));require(path.join(ROOT,'Release/HTML_SDT_Website/js/traction-gear-engine.js'));
const g=global.SDT_TRACTION_GEAR,base=JSON.parse(fs.readFileSync(path.join(RUN,'BASELINE.json'),'utf8')),radial=JSON.parse(fs.readFileSync(path.join(RUN,'RADIAL_KINEMATIC_CONTROL.json'),'utf8')),finite=JSON.parse(fs.readFileSync(path.join(RUN,'RADIAL_FINITE_GEOMETRY.json'),'utf8'));
const seat=g.seedMeasured,scaleMeV=seat.fineStructureConstant*seat.hbarJouleSeconds*seat.speedOfLightMetresPerSecond/(1e6*seat.electronVoltJoules)*1e15/seat.protonRadiusFm;
const results=[];
function frozenSegments(p,n){const cal=base.calibration,common={...p,handedness:1};let s=g.transformWakeSegments(common,n).map(e=>({...e,weight:e.weight*cal.protonBridgeMuNPerGeometricMoment}));if(p.type==='n')s=s.concat(g.transformWakeSegments({...common,handedness:-1,toroidalPhase:(p.toroidalPhase||0)+cal.phaseOffsetRadians},n).map(e=>({...e,weight:e.weight*cal.seatedElectronCoefficientMuNPerGeometricMoment})));return s;}
for(const [name,centreScale] of [['radial_original',1],...finite.rows.map(r=>[r.model+'_radial_reseated',r.selectedCentreScale])]){
 const poses=radial.poses.map(p=>({...p,centreRp:p.centreRp.map(v=>v*centreScale)}));
 let absolute=0,signed=0;const pairs=[];
 for(const e of base.contacts){const m=g.wakeMeshPairMetrics(poses[e.a],poses[e.b],8);absolute+=m.contactCoupling;signed+=m.coupling;pairs.push({a:e.a,b:e.b,...m});}
 const moment=g.segmentMoment(poses.flatMap(p=>frozenSegments(p,16)));
 results.push({name,centreScale,absoluteContactProxy:absolute,signedCrossTerm:signed,existingEnergyProxyMeV:absolute*scaleMeV,magneticVectorMuN:moment,pairs,classification:'conditional inherited proxy; state selected by geometry/kinematics; finite traction and physical energy remain OPEN'});
}
fs.writeFileSync(path.join(RUN,'RADIAL_ENERGY_PROXY.json'),JSON.stringify(results,null,2));
console.log(JSON.stringify(results.map(({name,existingEnergyProxyMeV,magneticVectorMuN})=>({name,existingEnergyProxyMeV,magneticVectorMuN}))));
