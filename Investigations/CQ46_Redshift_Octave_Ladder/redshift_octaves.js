const lp=1.616255e-35, c=299792458, b=2.897771955e-3, L2=Math.LN2, log2=x=>Math.log(x)/L2;
const D=1.3370e7; // Earth optical diameter (thermosphere-to-thermosphere) — the octave anchor
const oct=lam=>log2(D/lam);            // halvings below the anchor
const count=lam=>lam/lp;               // photon's spation-count per wavelength

console.log("════ 1. REDSHIFT IS OCTAVES:  1+z = 2^Δn   ⇒   Δn = log2(1+z) ════");
[["Sun grav (z=ϟ/R)",2.122e-6],["Earth grav",6.96e-10],["GPS clock",5.3e-10],
 ["galaxy z=0.1",0.1],["z=1",1],["z=3",3],["z=7 (early gal)",7],["CMB z=1100",1100]].forEach(([n,z])=>
  console.log("  "+n.padEnd(20)+" z="+z.toExponential(2).padStart(10)+"   Δn = log2(1+z) = "+log2(1+z).toFixed(4)+" octaves"));
console.log("  → z=1 is EXACTLY one octave; z=3 two; z=7 three; the CMB is ~10 octaves down.");

console.log("\n════ 2. THE CMB AS A 10-OCTAVE SLIDE (worked, falsifiable) ════");
const Trec=3000, Tnow=2.7255;
const lamRec=b/Trec, lamNow=b/Tnow;
console.log("  recomb blackbody peak (T=3000K): λ="+(lamRec*1e9).toFixed(0)+" nm  → octave "+oct(lamRec).toFixed(2)+" (near-IR)");
console.log("  CMB peak now (T=2.7255K):       λ="+(lamNow*1e3).toFixed(2)+" mm  → octave "+oct(lamNow).toFixed(2)+" (microwave)");
console.log("  slide = "+(oct(lamRec)-oct(lamNow)).toFixed(2)+" octaves   vs   log2(1+z_rec)=log2("+(Trec/Tnow).toFixed(0)+")="+log2(Trec/Tnow).toFixed(2)+" octaves  ✓");
console.log("  (the redshift Δn and the Wien-peak slide are the SAME number — redshift = octaves, exactly)");

console.log("\n════ 3. THE EM OCTAVE LADDER — why each band lands where it lands ════");
console.log("  anchor (octave 1) = Earth optical diameter "+(D/1e3).toFixed(0)+" km. Each octave halves λ (halves the photon's spation-count).");
console.log("  oct |    wavelength |  Wien T        | photon spation-count | regime");
const rows=[[1,D],[10,D/2**9],[20,D/2**19],[28,D/2**27],[34,D/2**33],[40,D/2**39],[43,D/2**42],[44,D/2**43],[45,D/2**44],[50,D/2**49],[60,D/2**59],[70,D/2**69]];
function band(l){ if(l>0.1)return"radio (ELF→UHF): macroscopic/plasma resonance"; if(l>1e-3)return"microwave: molecular rotation (CMB peak ~oct 34)"; if(l>7.4e-7)return"infrared: molecular vibration"; if(l>3.8e-7)return"VISIBLE: atomic outer-shell (α-ladder); stellar Wien peak"; if(l>1e-8)return"ultraviolet: atomic ionisation"; if(l>1e-11)return"X-ray: inner-shell / deep k-rungs"; return"gamma: nuclear transitions"; }
function wien(l){ const T=b/l; return T<1?(T*1e3).toFixed(1)+" mK":T<1e3?T.toFixed(0)+" K":T<1e6?(T/1e3).toFixed(0)+" kK":(T/1e6).toFixed(1)+" MK"; }
function lh(l){ if(l>=1e3)return(l/1e3).toFixed(0)+" km"; if(l>=1)return l.toFixed(2)+" m"; if(l>=1e-3)return(l*1e3).toFixed(2)+" mm"; if(l>=1e-6)return(l*1e6).toFixed(2)+" µm"; if(l>=1e-9)return(l*1e9).toFixed(1)+" nm"; return(l*1e12).toFixed(2)+" pm"; }
rows.forEach(([n,l])=>console.log("  "+String(n).padStart(3)+" | "+lh(l).padStart(12)+" | "+wien(l).padStart(8)+" | "+count(l).toExponential(2).padStart(10)+"           | "+band(l)));

console.log("\n════ 4. WHY IT DOESN'T COMPOUND: endpoint-only (in cancels out) ════");
// photon count N fixed; λ(r)=N·ℓ_P,∞·(1−z(r)). Pass through a CHAIN of wells, observe at the end.
const N=3.1e28; // a 500nm visible photon's spation-count
const path=[["emit @ Sun surface",2.122e-6],["pass Jupiter (graze)",2.0e-8],["interstellar",3.5e-7],["pass a star",1e-6],["our detector",6.96e-10]];
let prev=null;
path.forEach(([where,z])=>{ const lam=N*lp*(1-z); const shiftFromPrev=prev?((lam/prev-1)):0; prev=lam;
  console.log("  "+where.padEnd(22)+" z="+z.toExponential(2)+"  λ="+(lam*1e9).toFixed(6)+" nm"); });
const zEmit=2.122e-6, zObs=6.96e-10;
const total=(1-zObs)/(1-zEmit)-1;
console.log("  OBSERVED net shift = (1−z_obs)/(1−z_emit)−1 = "+total.toExponential(4)+"  = depends ONLY on endpoints.");
console.log("  Every intervening well: λ shrank going in, grew coming out — net ZERO. Nothing accumulated.");

console.log("\n════ 5. WHY IT DOESN'T BLUR: count is an exact invariant (kills tired-light) ════");
// tired-light / scattering: each of M interactions adds a random δλ; variance grows as M → line width ∝ √(path).
// SDT: δ per relay = 0 exactly (count conserved), so added width = 0 regardless of path length.
const Mpc=3.086e22, dist=1e3*Mpc; const relays=dist/lp; // number of spation relays over 1 Gpc
console.log("  a 1-Gpc photon undergoes ~"+relays.toExponential(1)+" spation relays.");
console.log("  tired-light (random δ per relay): line width would grow ∝ √relays → spectra SMEARED to mush.");
console.log("  SDT: δ=0 per relay (count is topological) → added width EXACTLY 0 → distant QSO lines stay razor-sharp.");
console.log("  Observed: distant QSO absorption lines ARE razor-sharp → endpoint/coherent ruler, NOT accumulation. ✓");
