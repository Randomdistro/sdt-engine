// FLM06 Phase 2 — Planck's floor, recast in KOPPA. James's bet: simpler via koppa.
// Planck's original logic: the spation is the scale where a mass's TWO lengths meet:
//   gravitational radius  r_g = Gm/c²   ==  in SDT this IS koppa:  ϟ = v²R/c² = Gm/c²
//   coherence wake        ƛ   = ℏ/mc    ==  in SDT the wake radius (g = R_wake·mc/ℏ)
// Planck mass = where they're equal; ℓ_P = that common length.
const c=299792458.0, hbar=1.054571817e-34, G=6.674e-11;     // G,ℏ: reference only
const m_p=1.67262192369e-27, R_p=8.414e-16, lP=1.616255e-35;
const L=x=>x.toExponential(5);

// the engine's per-baryon koppa (defined in laws.hpp as ℓ_P²·c·m_p/ℏ = G·m_p/c²)
const koppa_per_baryon = lP*lP*c*m_p/hbar;
const lam_Cp = hbar/(m_p*c);            // proton coherence wake (reduced Compton)
console.log("koppa_per_baryon ϟ_b =", L(koppa_per_baryon), "m   (= G·m_p/c² =", L(G*m_p/c/c),")");
console.log("proton wake ƛ_p      =", L(lam_Cp), "m");
console.log("R_p (measured)        =", L(R_p), "m   = ƛ_p ×", (R_p/lam_Cp).toFixed(4), "(= W+1 = 4, trefoil)\n");

console.log("=== THE KOPPA RESTATEMENT OF THE PLANCK FLOOR ===");
console.log("Planck (ref):  ℓ_P = √(ℏG/c³)          =", L(Math.sqrt(hbar*G/c/c/c)));
const gm = Math.sqrt(koppa_per_baryon*lam_Cp);
console.log("KOPPA form:    ℓ_P = √(ϟ_b · ƛ_p)       =", L(gm), "  ×ℓ_P:", (gm/lP).toFixed(6));
console.log("               i.e. ℓ_P = GEOMETRIC MEAN of a c-boundary (koppa) and a wake\n");

console.log("=== mass-independence (the elegant part) ===");
for(const [nm,m] of [["electron",9.109e-31],["proton",m_p],["1 GeV",1.783e-27],["1 ng",1e-12]]){
  const kop=G*m/c/c, wake=hbar/(m*c), g=Math.sqrt(kop*wake);
  console.log("  "+nm.padEnd(9)+": ϟ="+L(kop)+"  ƛ="+L(wake)+"  √(ϟ·ƛ)="+L(g)+"  ×ℓ_P:"+(g/lP).toFixed(4));
}
console.log("  -> √(ϟ·ƛ) = ℓ_P for EVERY mass: the m cancels. ℓ_P is where ϟ = ƛ (the crossover).\n");

console.log("=== via the proton wake R_p + topology W+1=4 (no explicit ƛ) ===");
const fromRp = Math.sqrt(koppa_per_baryon*R_p/4.0);
console.log("  ℓ_P = √(ϟ_b · R_p/(W+1)) = √(ϟ_b · R_p/4) =", L(fromRp), "  ×ℓ_P:", (fromRp/lP).toFixed(6));
console.log("  (since R_p = 4ƛ_p, this = √(ϟ_b·ƛ_p) exactly)\n");

console.log("=== the zk²=1 / k=1 reading ===");
console.log("  koppa ϟ = R/k² = R·z ;  zk²=1.  The spation is the k=1 self-boundary:");
console.log("  the cell whose c-boundary (where v=c) IS its own size → ϟ = R_wake, z=1, k=1.");
console.log("  ℓ_P is the fixed point where the two lengths coincide: ϟ(m_P)=ƛ(m_P)=ℓ_P.\n");

console.log("=== HONESTY: does koppa ESCAPE ℏ and G, or REPACKAGE them? ===");
console.log("  ϟ carries G  (ϟ=Gm/c²) UNLESS taken from kinematics ϟ=v²R/c² (GOM04, G-free).");
console.log("  ƛ carries ℏ  (ƛ=ℏ/mc) UNLESS taken as a measured length (R_p, muonic-H).");
console.log("  geometric mean: the MASS cancels, but √(ℏG/c³) remains if both via constants.");
console.log("  -> SIMPLER & more geometric (2 constants → 1 koppa + 1 wake length + integer 4).");
console.log("  -> but per FLM06 seed theorem, ONE absolute anchor still required (the koppa/mass).");
