'use strict';
// Independent conditional-equation check; see registration before interpretation.
const fs=require('fs'),path=require('path'),crypto=require('crypto');
const dir=__dirname, inv=JSON.parse(fs.readFileSync(path.join(dir,'inventory.json')));
const hashes={};
for(const id of [4591,4599,4604,4609,4594,6791,6793,6795,6797]){
 const r=inv.records.find(r=>r.id===id);
 const h=crypto.createHash('sha256').update(fs.readFileSync(r.path)).digest('hex');
 if(h!==r.sha256)throw Error('source changed '+id);
 hashes[id]={path:r.path,sha256:h};
}
const checks=[];
function check(name,condition,detail){checks.push({name,passed:!!condition,detail});if(!condition)throw Error(name);}
function integrate(epsilon,xi,dt,T=epsilon?Math.log(2)/epsilon:10){
 const n=Math.ceil(T/dt),h=T/n, v0=(xi-.5)*epsilon;
 let y=[1,v0,0]; const E0=(4*v0*v0+1)/2;
 function rhs(t,y){const q=.5*Math.exp(epsilon*t),B=q**-2,Bdot=-2*epsilon*B;
  return [y[1],2*xi*epsilon*y[1]-q*q*y[0],(.5-xi)*Bdot*y[1]*y[1]];}
 const shift=(a,b,f)=>a.map((v,i)=>v+f*b[i]);
 for(let i=0;i<n;i++){
  const t=i*h,k1=rhs(t,y),k2=rhs(t+h/2,shift(y,k1,h/2)),k3=rhs(t+h/2,shift(y,k2,h/2)),k4=rhs(t+h,shift(y,k3,h));
  y=y.map((v,j)=>v+h*(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6);
 }
 const qf=.5*Math.exp(epsilon*T),Bf=qf**-2,Ef=(Bf*y[1]*y[1]+y[0]*y[0])/2;
 return {epsilon,xi,dt,steps:n,x:y[0],v:y[1],initial_energy:E0,final_energy:Ef,integrated_medium_parameter_work:y[2],work_residual:(Ef-E0-y[2])/E0,action_ratio:(Ef/qf)/(E0/.5)};
}
const control=integrate(0,0,.005);
check('constant-position',Math.abs(control.x-Math.cos(5))<1e-7,control.x);
check('constant-velocity',Math.abs(control.v+.5*Math.sin(5))<1e-7,control.v);
check('constant-energy',Math.abs(control.final_energy/control.initial_energy-1)<1e-7);
const resistance=[];
for(const epsilon of [.004,.002])for(const xi of [0,1]){
 const coarse=integrate(epsilon,xi,.03),fine=integrate(epsilon,xi,.015),expected=.5**(2*(1-xi));
 const refinement=Math.abs(fine.action_ratio/coarse.action_ratio-1);
 check('work-'+epsilon+'-'+xi,Math.abs(fine.work_residual)<1e-5,fine.work_residual);
 check('refinement-'+epsilon+'-'+xi,refinement<1e-5,refinement);
 resistance.push({...fine,refinement,expected_adiabatic_action_ratio:expected,finite_rate_fractional_residual:fine.action_ratio/expected-1});
}
for(const xi of [0,1]){
 const r=resistance.filter(r=>r.xi===xi);
 check('rate-reduction-'+xi,Math.abs(r[1].finite_rate_fractional_residual)<Math.abs(r[0].finite_rate_fractional_residual));
}
const c0=2.99792458e8,T0=2.7255,sigma=5.670374419e-8,b=2.897771955e-3,kB=1.380649e-23,h=6.62607015e-34,mp=1.67262192369e-27,eta=6.1e-10,zeta3=1.2020569031595943;
const a=4*sigma/c0,P0=a*T0**4/3,ng=16*Math.PI*zeta3*(kB*T0/(h*c0))**3,nb=eta*ng,rhog=a*T0**4/c0**2,R0=.75*nb*mp/rhog;
const polynomial=N=>N**3-3*N-3*R0;
let lo=1,hi=100;
check('crossing-bracket',polynomial(lo)<0&&polynomial(hi)>0);
for(let i=0;i<100;i++){const m=(lo+hi)/2;if(polynomial(m)>0)hi=m;else lo=m;}
const N=(lo+hi)/2,cEM=c0/N,csFixed=c0/Math.sqrt(3*(1+R0/N));
check('fixed-reference-crossing',Math.abs(csFixed/cEM-1)<1e-10,csFixed/cEM-1);
const state=N=>({N,T_K:T0*N,c_EM_m_s:c0/N,P_rad_fixed_coefficient_Pa:P0*N**4,R:R0/N,lambda_fixed_Wien_m:b/(T0*N),sound_fixed_reference_m_s:c0/Math.sqrt(3*(1+R0/N)),sound_same_state_reference_m_s:c0/N/Math.sqrt(3*(1+R0/N))});
const result={date:'2026-10-28',status:'conditional equations checked; native contact selection unresolved',source_hashes:hashes,checks,resistance,
 CR17:{calibration:'historical literals, not newly inferred measurements',R0,present_baryon_number_density_m3:nb,P0_Pa:P0,clearing:state(R0),drag_reference:state(R0/.6),one_micrometre_reference:state(b/(T0*1e-6)),fixed_reference_sound_crossing:state(N),temperature_0_01_K:state(.01/T0)},
 exponent_comparison:{S10:{c:1,hbar:-2,kB:0,T:-1,a_rad:3,u:-1,b_Wien:-1,intrinsic_lambda_peak:0},historical_fixed_coefficients:{T:-1,a_rad:0,u:-4,b_Wien:0,intrinsic_lambda_peak:1}},
 limitations:['No BAO observation map or acoustic contact equation independently derived.','No finite-temperature speed halt follows from c=c0/N alone.','Present-unit wavelength labels must not be silently substituted for intrinsic wavelengths under varying coefficients.','No new physical fit, canonical edit, cosmic elapsed-time inference or native response selection.']};
fs.writeFileSync(path.join(dir,'PPT20_CR17_CHECK_RESULTS.json'),JSON.stringify(result,null,2)+'\n');
console.log(JSON.stringify({checks:checks.length,failed:checks.filter(c=>!c.passed).length,resistance:resistance.map(r=>({epsilon:r.epsilon,xi:r.xi,action:r.action_ratio,work_residual:r.work_residual})),CR17:result.CR17},null,2));
