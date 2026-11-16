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
const rows=[];
for(const [symbol,Z,A,,stable,binding] of raw){
  const nd=3*Z-A-2,nt=A-2*Z; if(Z<2||nd<0||nt<0||!(binding>0)) continue;
  const m=gear.buildNuclide(Z,A,{Rp:0.8414,symbol,skipObservableLedger:true});
  const k={}; for(const e of m.contacts) k[e.kind]=(k[e.kind]||0)+1;
  rows.push({sym:symbol+'-'+A,Z,A,Bmeas:binding,kinds:k});
}
orig(path.join(__dirname,'np41_kinds.json'),JSON.stringify(rows));
console.log('rows',rows.length,'kinds',[...new Set(rows.flatMap(r=>Object.keys(r.kinds)))]);
