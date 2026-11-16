// Spations: COMPRESSIBLE (shrink), NOT deformable (keep shape). Smaller hard against matter, set by V_disp.
// Depth-Closure already says exactly this: ℓ_P(r)=ℓ_P,∞(1−z), z=ϟ/r. The size-gradient IS dz/dr.
// gap-free + shrinking ⇒ MORE spations pack near mass (the Shapiro "more, smaller cells" picture).
const Pconv=2.459e48, f=2.125e-17, Peff=5.225e31;
function grad(koppa,R,name,rho,g){
  const z=koppa/R, dzdr=koppa/(R*R);            // fractional size-gradient per metre, at the surface
  console.log("\n"+name+":  z=ϟ/R="+z.toExponential(3)+"   size-gradient dz/dr="+dzdr.toExponential(3)+" /m");
  // NAIVE size-gradient force density if the FULL convergence pressure acted across the gradient:
  const fd_naive=Pconv*dzdr;                      // N/m^3
  const weight=rho*g;                             // actual gravitational weight density
  console.log("  naive (P_conv·dz/dr) = "+fd_naive.toExponential(2)+" N/m³   vs real weight ρg = "+weight.toExponential(2)+" N/m³");
  console.log("  overshoot = "+(fd_naive/weight).toExponential(2)+"×   (even ×f="+f.toExponential(2)+" → still "+(fd_naive*f/weight).toExponential(2)+"× too big)");
}
grad(4.435e-3, 6.371e6, "Earth surface", 3000, 9.81);
grad(1476.6,   6.957e8, "Sun surface",   1408, 274);
console.log("\nCONCLUSION: a size-gradient force riding the FULL P_conv overshoots gravity by ~10^27-28.");
console.log("So the size-gradient CANNOT be an extra force ADDED to occlusion (that breaks gravity by 10^28).");
console.log("It must BE the occlusion force — the local mechanism of the same differential push (f-suppressed).");
console.log("Same single gradient then does BOTH: ×P_conv-residual → ordinary FORCE; ×1 → tiny OPTICS (z~1e-6).");
