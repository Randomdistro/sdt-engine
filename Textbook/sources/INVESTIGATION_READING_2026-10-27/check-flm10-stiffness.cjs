'use strict';
const fs=require('fs'),path=require('path'),crypto=require('crypto');
const dir=__dirname,inv=JSON.parse(fs.readFileSync(path.join(dir,'inventory.json')));
const hashes={};for(const id of [4245,4247]){const r=inv.records.find(r=>r.id===id);const h=crypto.createHash('sha256').update(fs.readFileSync(r.path)).digest('hex');if(h!==r.sha256)throw Error('changed source');hashes[id]={path:r.path,sha256:h};}
const checks=[];function check(name,ok,detail){checks.push({name,passed:!!ok,detail});if(!ok){fs.writeFileSync(path.join(dir,'FLM10_STIFFNESS_CHECK_FAILURE.json'),JSON.stringify({hashes,checks},null,2));throw Error(name);}}
const pos=[[0,0,0],[0,.5,.5],[.5,0,.5],[.5,.5,0],[.25,.25,.25],[.25,.75,.75],[.75,.25,.75],[.75,.75,.25]];
const dot=(a,b)=>a.reduce((s,v,i)=>s+v*b[i],0),mic=v=>v.map(x=>x-Math.round(x));
const nbr=pos.map(()=>[]),bonds=[];for(let i=0;i<8;i++)for(let j=i+1;j<8;j++){const v=mic(pos[j].map((x,k)=>x-pos[i][k]));if(dot(v,v)<.55**2){nbr[i].push(j);nbr[j].push(i);bonds.push([i,j]);}}
check('diamond-coordination',nbr.every(n=>n.length===4)&&bonds.length===16,{bonds:bonds.length,coordination:nbr.map(n=>n.length)});
function energy(alpha,beta,eta){const H=[[1+eta[0],eta[5]/2,eta[4]/2],[eta[5]/2,1+eta[1],eta[3]/2],[eta[4]/2,eta[3]/2,1+eta[2]]];const d2=3/16,cs=alpha*3/16/d2,cb=beta*3/8/d2;
 const arm=(i,j)=>{const v=mic(pos[j].map((x,k)=>x-pos[i][k]));return H.map(row=>dot(row,v));};
 let E=0;for(const [i,j] of bonds){const v=arm(i,j);E+=cs*(dot(v,v)-d2)**2;}
 for(let i=0;i<8;i++)for(let a=0;a<4;a++)for(let b=a+1;b<4;b++){const x=arm(i,nbr[i][a]),y=arm(i,nbr[i][b]);E+=cb*(dot(x,y)+d2/3)**2;}return E;}
const zero=()=>[0,0,0,0,0,0];check('reference-energy',energy(1,.285,zero())<1e-25);
function calculate(alpha,beta,h){const E0=energy(alpha,beta,zero());const diagonal=[];for(let i=0;i<6;i++){let a=zero(),b=zero();a[i]=h;b[i]=-h;diagonal.push((energy(alpha,beta,a)+energy(alpha,beta,b)-2*E0)/h**2);}
 let cross=0;for(const a of [-1,1])for(const b of [-1,1]){const e=zero();e[0]=a*h;e[1]=b*h;cross+=a*b*energy(alpha,beta,e);}const C12=cross/(4*h*h),C11=diagonal[0],C44=diagonal[3],D=C11-C12;
 const GV=(D+3*C44)/5,GR=5*D*C44/(4*C44+3*D),AU=5*GV/GR-5;
 return {alpha,beta,h,diagonal,C11,C12,C44,AU};}
const control=calculate(1,.5,5e-5);check('isotropic-control',Math.abs(control.AU)<1e-7,control);
const base=calculate(1,.285,5e-5),scaled=calculate(3,.855,5e-5);check('cubic-control',Math.max(...base.diagonal.slice(0,3))-Math.min(...base.diagonal.slice(0,3))<1e-7&&Math.max(...base.diagonal.slice(3))-Math.min(...base.diagonal.slice(3))<1e-7,base.diagonal);
check('common-scale-invariance',Math.abs(base.AU-scaled.AU)<1e-7,{base:base.AU,scaled:scaled.AU});
const results=[];for(const beta of [.2,.285,.5,.8]){const coarse=calculate(1,beta,1e-4),fine=calculate(1,beta,5e-5);const error=Math.max(...['C11','C12','C44','AU'].map(k=>Math.abs(fine[k]-coarse[k])/Math.max(1,Math.abs(fine[k]))));check('refinement-'+beta,error<1e-6,error);results.push(fine);}
const result={date:'2026-10-28',status:'affine diamond control only; no native stiffness selection',source_hashes:hashes,checks,results,ratio_cancels:false,common_scale_cancels:true};
fs.writeFileSync(path.join(dir,'FLM10_STIFFNESS_CHECK_RESULTS.json'),JSON.stringify(result,null,2)+'\n');console.log(JSON.stringify({controls:checks.length,failed:checks.filter(r=>!r.passed).length,results},null,2));
