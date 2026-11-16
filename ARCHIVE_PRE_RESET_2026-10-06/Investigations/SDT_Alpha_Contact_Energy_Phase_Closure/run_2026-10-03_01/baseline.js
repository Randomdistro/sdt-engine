'use strict';
const fs=require('fs'),path=require('path'),vm=require('vm');
const RUN=__dirname,ROOT=path.resolve(RUN,'../../..');
const inputs=fs.readFileSync(path.join(ROOT,'Release/HTML_SDT_Website/js/nuclear-inputs.js'),'utf8');
const engine=fs.readFileSync(path.join(ROOT,'Release/HTML_SDT_Website/js/traction-gear-engine.js'),'utf8');
function load(removeAlpha=false,grid=null){const ctx=vm.createContext({console});vm.runInContext(inputs,ctx);if(removeAlpha){const old=ctx.SDT_NUCLEAR_INPUTS;ctx.SDT_NUCLEAR_INPUTS=Object.freeze({...old,observables:Object.freeze({...old.observables,He4:undefined})});}
 let code=engine;if(grid){const token='const counts = [5, 5, 7];';if(!code.includes(token))throw Error('Stencil source changed');code=code.replace(token,`const counts = [${grid.join(',')}];`);}
 vm.runInContext(code,ctx);return ctx.SDT_TRACTION_GEAR;}
const gear=load(),bare=load(true);
const model=gear.buildNuclide(2,4,{Rp:0.8414}),without=bare.buildNuclide(2,4,{Rp:0.8414}),withMetadata=gear.buildNuclide(2,4,{Rp:0.8414,bindingEnergyMeV:28.296});
const state=m=>JSON.stringify({nodes:m.nodes,contacts:m.contacts,modules:m.modules,fingerprint:m.fingerprint,poses:m.observableLedger.poses});
const poses=model.observableLedger.poses,calibration=gear.neutronMagneticCalibration(4);
const add=(a,b)=>a.map((v,i)=>v+b[i]),norm=a=>Math.hypot(...a),sub=(a,b)=>a.map((v,i)=>v-b[i]);
function segments(g,p,n,frozen=true){if(!frozen)return g.speciesMagneticSegments(p,n);const common={...p,handedness:1};let s=g.transformWakeSegments(common,n).map(e=>({...e,weight:e.weight*calibration.protonBridgeMuNPerGeometricMoment,source:'proton-form'}));if(p.type==='n')s=s.concat(g.transformWakeSegments({...common,handedness:-1,toroidalPhase:(p.toroidalPhase||0)+calibration.phaseOffsetRadians},n).map(e=>({...e,weight:e.weight*calibration.seatedElectronCoefficientMuNPerGeometricMoment,source:'seated-electron-counter'})));return s;}
const mag=[];
for(const n of [4,8,16,32]){const byBody=poses.map(p=>segments(gear,p,n)),s=byBody.flat(),m=gear.segmentMoment(s),componentMoments=byBody.map(s=>gear.segmentMoment(s)),sumMagnitude=componentMoments.reduce((sum,m)=>sum+norm(m),0);const translation=[2.3,-1.7,0.8];const moved=s.map(e=>({...e,a:add(e.a,translation),b:add(e.b,translation)}));const rotate=v=>[v[0],-v[2],v[1]];const rotated=s.map(e=>({...e,a:rotate(e.a),b:rotate(e.b)}));const translationResidual=norm(sub(gear.segmentMoment(moved),m))/Math.max(sumMagnitude,1);const rotationResidual=norm(sub(gear.segmentMoment(rotated),rotate(m)))/Math.max(sumMagnitude,1);
 mag.push({samples:n,momentVectorMuN:m,magnitudeMuN:norm(m),componentMoments,sumMagnitude,normalizedCancellation:norm(m)/sumMagnitude,translationResidual,rotationResidual,farFieldExisting:gear.farFieldDipoleFit(s),frozenCalibration:true});
 if(n===16)fs.writeFileSync(path.join(RUN,'MAGNETIC_SEGMENTS.json'),JSON.stringify(s));
}
const surfaces=[];for(const n of [1500,3000,6000]){const curves=poses.map(p=>Array.from({length:n},(_,i)=>{const point=gear.h1Point(2*Math.PI*i/n,model.Rp,0);return add(point,p.centreRp.map(v=>v*model.Rp));}));surfaces.push({samples:n,curves});}
fs.writeFileSync(path.join(RUN,'FINITE_CURVES.json'),JSON.stringify({units:'fm',scope:'existing H1 curve at identity body orientation and zero body-shape phase; wake phase is a separate proxy coordinate',coreRadiusFm:gear.h1Spec.strandRadiusFraction*model.Rp,modelNodes:model.nodes,contacts:model.contacts,surfaces}));
const wake=[];for(const grid of [[5,5,7],[10,10,14],[20,20,28]]){const g=load(false,grid);let total=0,signedTotal=0;const pairs=[];for(const edge of model.contacts){const metrics=g.wakeMeshPairMetrics(poses[edge.a],poses[edge.b],8);total+=metrics.contactCoupling;signedTotal+=metrics.coupling;pairs.push({a:edge.a,b:edge.b,...metrics});}
 wake.push({grid,filamentSamples:8,totalAbsoluteContactCoupling:total,totalSignedCoupling:signedTotal,pairs});console.log(JSON.stringify({grid,absolute:total,signed:signedTotal}));}
const alphaBaseline={schema:'ALPHA-PHASE0-1',nodes:model.nodes,contacts:model.contacts,modules:model.modules,metrics:model.metrics,observableLedger:model.observableLedger,h1Spec:gear.h1Spec,wakeSpec:gear.h1WakeSpec,calibration,metadataInvariance:{alphaMomentRemoved:state(model)===state(without),bindingMetadataAdded:state(model)===state(withMetadata)},magneticRefinement:mag,wakeRefinement:wake};
fs.writeFileSync(path.join(RUN,'BASELINE.json'),JSON.stringify(alphaBaseline,null,2));
fs.writeFileSync(path.join(RUN,'MAGNETIC_LEDGER.csv'),'samples,x_muN,y_muN,z_muN,magnitude_muN,normalized_cancellation,translation_residual,rotation_residual\n'+mag.map(r=>[r.samples,...r.momentVectorMuN,r.magnitudeMuN,r.normalizedCancellation,r.translationResidual,r.rotationResidual].join(',')).join('\n')+'\n');
console.log(JSON.stringify({binding:model.observableLedger.massDefect.calculatedBindingMeV,moment:model.observableLedger.magnetic.integralVectorMuN,metadataInvariance:alphaBaseline.metadataInvariance,normalizedCancellation:mag.at(-1).normalizedCancellation}));
