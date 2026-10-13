// Mechanism: the photon's COUNT (cycles, = transition energy) is gated/fixed at emission.
// Physical wavelength = count × LOCAL spation size = N·ℓ_P,∞(1−z).  The ruler changes, not the photon.
// λ_obs/λ_emit = (1−z_obs)/(1−z_emit).  Emitter deeper (z_emit>z_obs, SMALLER spations) ⇒ redshift.
// So:  redshift = how much SMALLER the spations were at the source than at the detector = exactly z (for z_obs≈0).
const koppa1=1476.6;                 // ϟ for 1 solar mass (m)
function row(name,M_sun,R_m){ const k=koppa1*M_sun, z=k/R_m;
  const deficit=z;                    // fractional spation-size deficit at the source
  const zsh=1/(1-z)-1;                // observed redshift (observer at z_obs≈0)
  console.log(name.padEnd(20)+" z=ϟ/R="+z.toExponential(3).padStart(11)+
    "   spations smaller by "+(deficit<1e-3?(deficit*1e6).toFixed(2)+" ppm":(deficit*100).toFixed(1)+" %").padStart(12)+
    "   redshift "+(zsh<1e-3?zsh.toExponential(2):zsh.toFixed(3))); }
console.log("source                  depth          spation-size deficit        z_spectral");
row("Earth surface",      1/333000, 6.371e6);
row("Sun surface",        1,        6.957e8);
row("white dwarf (Sirius B)",1.0,   5.6e6);
row("neutron star",       1.4,      1.2e4);
row("BH photon ring",     1.0,      3*koppa1);   // r=3ϟ
row("BH event horizon",   1.0,      2*koppa1);   // z=1/2
console.log("\n'a scale or two smaller' (10-100×, z≈0.9-0.99) only happens at a black-hole horizon /");
console.log("the koppa boundary. At the SUN the spations are smaller by 2.12 ppm — which is exactly why");
console.log("the solar gravitational redshift IS 2.12e-6 (keystone C1, 0.03%). The deficit = the redshift.");
