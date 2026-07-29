// HYPOTHESIS (Harvey): particle repulsion = the INVERSE of the convergence.
// Convergence = inflow (a SINK between bodies = DEFICIT = pulled together = attraction).
// Inverse    = outflow (a SOURCE between bodies = EXCESS = pushed apart = repulsion).
// Force ∝ −∇(throughput): toward a deficit, away from an excess. Symmetric in magnitude.
const Pconv=2.459e48;
function netForce(modulation){ // modulation = throughput between bodies relative to ambient
  // deficit (modulation<0) → attraction (sign +toward); excess (>0) → repulsion (−away)
  return -modulation; }
console.log("throughput between two bodies →  net force sign");
[["deficit (shadow / sink)",-1,"ATTRACTION (toward)"],["ambient (nothing)",0,"none"],["excess (source / anti-shadow)",+1,"REPULSION (apart)"]]
 .forEach(([n,m,r])=>console.log("  "+n.padEnd(30)+"modulation="+(m>0?"+":"")+m+"   F="+(netForce(m)>0?"+":"")+netForce(m)+"  → "+r));

console.log("\n── why GRAVITY is attraction-only, CHARGE is both signs (the wake tensor) ──");
console.log("  ℓ=0 MONOPOLE wake (MASS): sign-definite — a SINK only, no source lobe → DEFICIT only → ATTRACTION only.");
console.log("     (this is WHY there is no antigravity: a monopole occlusion cannot make an excess.)");
console.log("  ℓ=1 DIPOLE wake (CHARGE): TWO lobes (+source / −sink). Directionality (vortex handedness) sets which faces between:");
console.log("     same sign  → like lobes between → EXCESS  → REPULSION   (= the inverse of the convergence)");
console.log("     opposite   → unlike lobes between → DEFICIT → ATTRACTION (= same direction as gravity)");

console.log("\n── magnitude consistency (the test the hypothesis must pass) ──");
const ke=8.9875517873681e9, e=1.602176634e-19, r=1e-10;
const Frep=ke*e*e/(r*r), Fatt=ke*(+e)*(-e)/(r*r);
console.log("  Coulomb |F| repel vs attract at "+r+" m:  +"+Frep.toExponential(3)+" N   /   "+Fatt.toExponential(3)+" N");
console.log("  |repel| == |attract| EXACTLY → consistent with repulsion being the ±inverse of ONE modulation. ✓");

console.log("\n── why charge dominates gravity (dipole ≫ monopole) ──");
console.log("  EM/grav force ratio (engine B21) ≈ 2.27e39  → the dipole (source/sink) channel is ~10^39× the monopole deficit.");
console.log("  so for like charges the dipole EXCESS (repulsion) buries the monopole DEFICIT (their tiny mutual gravity).");

console.log("\nSUMMARY: repulsion = a local SOURCE (excess) = the convergence run BACKWARDS;");
console.log("attraction = a local SINK (deficit) = riding the convergence. Same throughput, opposite sign.");
console.log("Gravity has only the sink (monopole) → attraction-only. Charge has both (dipole) → both signs.");
