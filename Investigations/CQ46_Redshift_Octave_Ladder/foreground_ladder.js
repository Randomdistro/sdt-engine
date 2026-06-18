// "The microwave background was once the infrared foreground." Walk it BACKWARD up the octave ladder.
// The universe's own blackbody glow peaks at λ=b/T; earlier = hotter = shorter λ = higher octave.
// Redshift from an epoch to now = octaves climbed = log2(T_epoch / T_now).
const D=1.3370e7, b=2.897771955e-3, L2=Math.LN2, log2=x=>Math.log(x)/L2, Tnow=2.7255;
const oct=T=>log2(D*T/b);                 // octave of the blackbody peak at temperature T
const lh=l=> l>=1e-3?(l*1e3).toFixed(2)+" mm": l>=1e-6?(l*1e6).toFixed(2)+" µm": l>=1e-9?(l*1e9).toFixed(0)+" nm":(l*1e12).toFixed(2)+" pm";
function band(l){ if(l>1e-3)return"MICROWAVE"; if(l>7.4e-7)return"INFRARED"; if(l>3.8e-7)return"VISIBLE"; if(l>1e-8)return"ULTRAVIOLET"; if(l>1e-11)return"X-RAY"; return"GAMMA"; }
console.log("epoch / T            λ_peak      band         octave   redshift-to-now (octaves = log2(T/2.7255))   transparent?");
const rows=[
 ["now (2.7255 K)",2.7255,"yes — what we see"],
 ["recomb / the Clearing (3000 K)",3000,"← becomes transparent HERE (last scattering)"],
 ["red-star sky (3800 K)",3800,"no — opaque glowing fog"],
 ["Sun-surface sky (5772 K)",5772,"no — opaque"],
 ["blue-white sky (7600 K)",7600,"no — opaque"],
 ["UV sky (15000 K)",15000,"no — opaque"],
 ["X-ray sky (3e6 K)",3e6,"no — opaque"],
 ["gamma sky (3e9 K)",3e9,"no — opaque, near the prior detonation"],
];
rows.forEach(([n,T,note])=>{ const l=b/T; console.log("  "+n.padEnd(30)+lh(l).padStart(8)+"  "+band(l).padEnd(12)+" "+oct(T).toFixed(2).padStart(6)+"     "+log2(T/Tnow).toFixed(2).padStart(6)+"        "+note); });
console.log("\nVISIBLE-foreground window (the answer): the peak is in visible light for T = b/760nm..b/380nm:");
console.log("   red edge  T = "+(b/760e-9).toFixed(0)+" K   (z = "+((b/760e-9)/Tnow-1).toFixed(0)+")");
console.log("   violet edge T = "+(b/380e-9).toFixed(0)+" K   (z = "+((b/380e-9)/Tnow-1).toFixed(0)+")");
console.log("\n=> 'just before the infrared foreground' = a VISIBLE foreground that swept the entire stellar");
console.log("   colour sequence (red→orange→white→blue) as you run the clock back — the whole sky glowing");
console.log("   the colour of a star's surface, because the universe passed through stellar surface temperatures.");
console.log("   Before THAT: UV, X-ray, gamma foregrounds — but all OPAQUE (behind last scattering / the Clearing).");
