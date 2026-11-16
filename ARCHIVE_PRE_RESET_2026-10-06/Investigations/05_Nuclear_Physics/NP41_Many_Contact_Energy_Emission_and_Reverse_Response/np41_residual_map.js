'use strict';
const fs=require('fs'),path=require('path');
const root='C:/Users/Jimmi/OneDrive/Desktop/sdt-engine';
const orig=fs.writeFileSync; fs.writeFileSync=function(p,...a){ if(path.basename(String(p))==='nseq18_results.json') return; return orig.call(fs,p,...a); };
const ol=console.log; console.log=()=>{};
try{ require(path.join(root,'Investigations/05_Nuclear_Physics/NSEQ18_Universal_Interstitial_Sequencer/nseq18_universal_validate.js')); }catch(e){}
console.log=ol; fs.writeFileSync=orig;
const gear=global.SDT_TRACTION_GEAR;
const html=fs.readFileSync(path.join(root,'Release/HTML_SDT_Website/nuclear-packing-sequencer.html'),'utf8');
const raw=Function('return '+html.match(/const RAW\s*=\s*(\[[\s\S]*?\n\]);/)[1])();
const out=[];let bad=[];
for(const [symbol,Z,A,,stable,binding] of raw){
  const nd=3*Z-A-2,nt=A-2*Z; if(Z<2||nd<0||nt<0||!(binding>0)) continue;
  try{
    const m=gear.buildNuclide(Z,A,{Rp:0.8414,symbol});
    const L=m.observableLedger; const bc=L&&L.massDefect?L.massDefect.calculatedBindingMeV:NaN;
    const deg=Array(A).fill(0); for(const e of m.contacts){deg[e.a]++;deg[e.b]++;}
    if(!Number.isFinite(bc)) bad.push(symbol+A); else out.push({sym:symbol+'-'+A,Z,A,stable,Bmeas:binding,Bcalc:bc,maxdeg:Math.max(...deg),contacts:m.contacts.length});
  }catch(e){ bad.push(symbol+A+':'+String(e.message).slice(0,40)); }
}
orig(path.join(__dirname,'np41_residual_map.json'),JSON.stringify({n:out.length,bad,rows:out}));
console.log('built',out.length,'non-finite/failed',bad.length,bad.slice(0,8));
