// E-series prediction curve: emitter depth-shift vs heliocentric radius.
// SDT: z(r)=ϟ_Sun/r ; Δλ/λ between emitter at r and reference at r_ref = z(r)-z(r_ref).
// Local light/clock: dτ/dt=√(1-z); fractional emission shift ≈ Δz (z<<1).
const c=299792458.0, koppaSun=1477.046, AU=1.495978707e11, R_Sun=6.957e8;
const koppaEarth=4.434e-3, R_E=6.371e6;
const L=x=>x.toExponential(4);
const z=r=>koppaSun/r;
const r_ref=AU;  // reference spectrometer at 1 AU (Earth orbit)
console.log("EMITTER depth-shift vs reference at 1 AU. Δλ/λ = z(r) − z(1AU).\n");
console.log("  r [AU]".padStart(9), "z(r)=ϟ/r".padStart(13), "Δλ/λ vs 1AU".padStart(14),
            "Δc-equiv [m/s]".padStart(15), "instr. needed".padStart(15));
for(const rAU of [1.0,0.7,0.5,0.3,0.2,0.1,0.046,0.02]){
  const r=rAU*AU, dz=z(r)-z(r_ref), dv=dz*c;
  const need = Math.abs(dz);
  console.log(rAU.toFixed(3).padStart(9), L(z(r)).padStart(13), (dz>=0?"+":"")+L(dz),
    (dv>=0?"+":"")+dv.toFixed(2).padStart(13), L(need).padStart(15));
}
console.log("\n  (0.046 AU = ~10 R_sun, Parker perihelion class; 0.02 AU = 4.3 R_sun)");
console.log("\n=== calibration anchor (ALREADY MEASURED) ===");
const dz_gps=koppaEarth/R_E - koppaEarth/(R_E+2.02e7); // surface vs GPS alt
console.log("  GPS gravitational redshift surface→20200km: Δz =", L(dz_gps),
            " (~38 µs/day) — operationally confirmed daily. SDT z=ϟ/r reproduces it.");
console.log("\n=== instrument reality ===");
console.log("  astro-comb / ultrastable cavity spectrometers: ~1e-10 to 1e-11 fractional.");
console.log("  Parker-class perihelion 0.046 AU emitter vs 1 AU ref: Δλ/λ =",
            L(z(0.046*AU)-z(r_ref)), " -> ~",((z(0.046*AU)-z(r_ref))*c).toFixed(0),"m/s. EASILY resolved.");
console.log("\n=== deep-space falsifiers (SDT-only) ===");
const M_MW=6.0e10, R0=8.178*3.0857e19, z_gal=M_MW*koppaSun/R0;
console.log("  galactic depth floor z_gal =", L(z_gal), " = ", (z_gal*c).toFixed(1),
            "m/s c-deficit vs absolute c_inf (constant, isotropic — a DC offset).");
const r_lumio=Math.sqrt(3.828e26/(4*Math.PI*3.1289e-6));
console.log("  lumiopause (surface-area L/4πr²=F_CMB):", (r_lumio/AU).toFixed(0),
            "AU — emission/closure regime handover, deep-space probe only.");
