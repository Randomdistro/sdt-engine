'use strict';
const fs=require('fs'),path=require('path');
const tau=2*Math.PI,major=.62,minor=.22;
const point=(p,lane,theta)=>{const u=(theta+tau*lane)/4,phi=4*u,psi=Math.PI+p*u,r=major+minor*Math.cos(psi);return [r*Math.cos(phi),r*Math.sin(phi),minor*Math.sin(psi)];};
const distance=(a,b)=>Math.hypot(...a.map((v,i)=>v-b[i]));
const rows=[3,4,5].map(p=>{let laneGap=Infinity,maxCoincidenceResidual=0,seam=0;for(let k=0;k<=256;k++){const theta=tau*k/256;for(let i=0;i<4;i++)for(let j=i+1;j<4;j++){const d=distance(point(p,i,theta),point(p,j,theta));laneGap=Math.min(laneGap,d);maxCoincidenceResidual=Math.max(maxCoincidenceResidual,d);}}for(let lane=0;lane<4;lane++)seam=Math.max(seam,distance(point(p,lane,tau),point(p,(lane+1)%4,0)));return {p,toroidalTours:4,physicalPoloidalTurns:p,physicalPassagesPerTour:p/4,physicalPoloidalAdvancePerTour:p*tau/4,minimumLaneSeparationRp:laneGap,maximumLaneSeparationRp:maxCoincidenceResidual,seamResidualRp:seam,naiveFourPassageLaneDegeneracy:p===4};});
const out={scope:'phase/lane implementation audit; no new physical lane embedding or contraction law',rows,operatorPhysicalCountingConvention:'PENDING'};
fs.writeFileSync(path.join(__dirname,'FOUR_TOUR_PHASE_AUDIT.json'),JSON.stringify(out,null,2));
console.log(JSON.stringify(out));
