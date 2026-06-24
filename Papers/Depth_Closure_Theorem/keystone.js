// KEYSTONE — every headline number the paper cites, one reproducible run.
const c=299792458.0, alpha=7.2973525693e-3, a_0=5.29177210903e-11, r_e=2.8179403262e-15;
const R_p=8.414e-16, lP=1.616255e-35, hbar=1.054571817e-34;
const mp=1.672621923690e-27, me=9.1093837015e-31;
const koppaSun=1477.046, R_Sun=6.957e8, AU=1.495978707e11;
const G=6.674e-11, Msun=1.98847e30, H0=67.4e3/3.0856775814e22;
const P=(k,v)=>console.log("  "+k.padEnd(46)+v);
const L=x=>x.toExponential(6);

console.log("=== I. THE CENTRAL IDENTITY: z = ϟ/r = v²R/c² ===");
P("solar redshift z_obs = GM/(c²R_Sun):", L(G*Msun/(c*c*R_Sun)));
P("SDT depth z_sdt = koppa_Sun/R_Sun:", L(koppaSun/R_Sun));
P("ratio (match):", (koppaSun/R_Sun)/(G*Msun/(c*c*R_Sun)));

console.log("\n=== II. ONE CENTRIPETAL LAW v=c√(ϟ/r) ACROSS SCALES ===");
P("292 AU solar orbit  v=c√(ϟ/r) [km/s]:", (c*Math.sqrt(koppaSun/(292.48*AU))/1e3).toFixed(4));
P("Earth orbit 1AU     v=c√(ϟ/r) [km/s]:", (c*Math.sqrt(koppaSun/AU)/1e3).toFixed(3)+"  (obs 29.78)");
P("H ground state      v=αc → k_H=c/v:", (c/(alpha*c)).toFixed(4)+"  (=1/α)");
P("koppa_H = α²a_0 [m]:", L(alpha*alpha*a_0)+"  (=r_e "+L(r_e)+")");
P("proton surface k=(1/α)√(R_p/a_0):", ((1/alpha)*Math.sqrt(R_p/a_0)).toFixed(4));
P("proton surface v_phase [c]:", (1/((1/alpha)*Math.sqrt(R_p/a_0))).toFixed(4));

console.log("\n=== III. k AS TIMER, 137 AS COUNTDOWN ===");
P("dτ/dt = √(1−1/k²) at k=1/α (hydrogen):", Math.sqrt(1-alpha*alpha).toFixed(9));
P("countdown steps to c-boundary k=1:", (1/alpha).toFixed(3));

console.log("\n=== IV. c IS LOCAL (Earth's rung) ===");
const z_gal=6.0e10*koppaSun/(8.178*3.0857e19);
P("galactic depth floor z_gal:", L(z_gal));
P("absolute ceiling c_∞=c/(1−z) [m/s]:", (c/(1-z_gal)).toFixed(1)+"  (+"+(c/(1-z_gal)-c).toFixed(1)+")");

console.log("\n=== V. a₀ DERIVED (the floor scale) ===");
P("a₀ = cH₀/2π [m/s²]:", L(c*H0/(2*Math.PI)));

console.log("\n=== VI. SPATION FLOOR (koppa form, FLM06) ===");
const lamCp=hbar/(mp*c);
P("ℓ_P=√(ϟ_b·ƛ_p), ϟ_b=ℓ_P²cm_p/ℏ:", L(Math.sqrt((lP*lP*c*mp/hbar)*lamCp))+"  (ℓ_P "+L(lP)+")");

console.log("\n=== VII. LUMIOPAUSE (surface-area) ===");
const F_CMB=c*(7.5657e-16*Math.pow(2.7255,4))/4;
P("r_lumio=√(L_Sun/4πF_CMB) [AU]:", (Math.sqrt(3.828e26/(4*Math.PI*F_CMB))/AU).toFixed(0));

console.log("\n=== VIII. GD05 / APS03 (galaxy + cross-scale, prior runs) ===");
P("GD05 M4 floor law RMS / BTFR:", "23.8% / 3.58 (SPARC 135 gal)");
P("APS03 collapse RMS / neg-control:", "8.8% / 6× worse (3 scales)");

console.log("\n=== IX. mass ratio (6π⁵) — distinct from 1.830c ===");
P("6π⁵:", (6*Math.pow(Math.PI,5)).toFixed(3)+"  (m_p/m_e=1836.153)");
