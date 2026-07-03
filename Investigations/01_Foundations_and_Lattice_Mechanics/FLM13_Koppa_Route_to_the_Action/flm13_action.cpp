// FLM13 — The Koppa Route to the Action (hbar)
// J. C. Harvey, Melbourne. Executed 2026-07-03 (HUNTER).
// Job: (P1) hbar's ROLE as the W=1 circulation quantum — three ladder forms;
//      (P2) the delete-test table: which inputs encode hbar;
//      (P3) the {hbar, m_e, m_p} -> ONE seat collapse (handed to FLM12);
//      (P4) the hbar-free frontier verdict.
// R5 discipline: every hbar-identity is LABELLED identity. The tool's job is the
// delete-test table, not the number.
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

int main() {
    using namespace sdt::laws;
    const double c   = measured::c;
    const double hb  = measured::hbar;      // reference ONLY — never an extraction input
    const double al  = measured::alpha;
    const double ali = measured::alpha_inv;
    const double a0  = measured::a_0;
    const double re  = measured::r_e;
    const double Rp  = measured::R_p;
    const double me  = measured::m_e;
    const double mp  = measured::m_p;

    std::puts("=== FLM13: the koppa route to the action ===\n");

    // ---------- P1: the ROLE — hbar as the W=1 rung's circulation quantum ----------
    // Onsager–Feynman: a quantised vortex in a superfluid carries circulation
    // kappa = oint v.dl = n·h/m. The W=1 unknot is the single-quantum vortex (n=1).
    // The rung's MECHANICAL circulation is 2π·(rung radius)·(rung speed) = 2π·a0·(αc).
    // The claim: this equals kappa = h/m_e, i.e. hbar = m_e·(αc)·a0.
    const double kappa_mech = 2.0 * M_PI * a0 * (al * c);   // 2π a0 v — mechanical circulation
    const double h1 = me * kappa_mech / (2.0 * M_PI);        // = m_e·αc·a0
    const double h2 = me * (al * c) * a0;                    // same, written as angular momentum
    const double h3 = re * me * c / al;                      // r_e form (r_e = koppa of hydrogen)
    std::puts("P1  hbar three ladder ways [IDENTITY-CLASS: a0, r_e are hbar-defined lengths]");
    std::printf("    m_e*kappa/2pi   = %.9e   ratio to hbar = %.9f\n", h1, h1 / hb);
    std::printf("    m_e*(ac)*a0     = %.9e   ratio to hbar = %.9f\n", h2, h2 / hb);
    std::printf("    r_e*m_e*c/a     = %.9e   ratio to hbar = %.9f\n", h3, h3 / hb);
    // Proton-geometry path: r_e' = R_p / k_ps^2 with the ENGINE'S stored k_ps = 0.5464
    // (laws.hpp:663; pre-computed (1/α)√(R_p/a0) — 4 s.f. rounding lives in the residual).
    const double k_ps_stored = 0.5464;
    const double re_proton   = Rp / (k_ps_stored * k_ps_stored);
    const double h4          = re_proton * me * c / al;
    std::printf("    proton path (R_p/0.5464^2)*m_e*c/a = %.9e  ratio = %.9f\n", h4, h4 / hb);
    std::puts("    [residual on the proton path = stored-constant rounding + R_p measurement,");
    std::puts("     NOT physics. All four forms are the SAME statement: hbar is the action of");
    std::puts("     the ladder's bottom rung. ROLE derived; VALUE not extracted here (R5).]\n");
    const bool p1_gate = std::abs(h1 / hb - 1) < 1e-6 && std::abs(h2 / hb - 1) < 1e-6
                      && std::abs(h3 / hb - 1) < 1e-6;

    // ---------- P2: the delete-test — which inputs encode hbar ----------
    std::puts("P2  delete-test table (input | how its number is obtained | encodes hbar?)");
    std::puts("    r_e    | DEFINED a*hbar/(m_e c)                          | YES (definition)");
    std::puts("    a_0    | DEFINED hbar/(m_e c a)                          | YES (definition)");
    std::puts("    R_p    | muonic-H spectroscopy (2S-2P transitions)       | YES (spectroscopy is hbar-metered)");
    std::puts("    psi_H  | ionisation-energy kinematics (spectroscopy)     | YES");
    std::puts("    E_ion  | spectroscopy                                    | YES");
    std::puts("    m_e[kg]| SI-2019 kilogram is DEFINED via fixed h (Kibble)| YES (post-2019)");
    std::puts("    alpha  | dimensionless spectral ratio (APS05 Route B)    | NO");
    std::puts("    c      | Mercury precession inversion (GOM04) / defined  | NO");
    std::puts("    VERDICT P2: no hbar-free VALUE path exists among the atomic inputs.");
    std::puts("    Dimensional theorem: koppa fixes Length, c fixes Length/Time, alpha is a pure");
    std::puts("    number. Action = Mass*Length^2/Time. No combination of lengths, times and pure");
    std::puts("    numbers manufactures the Mass dimension -> no ratio is an action. ROLE-only.\n");

    // ---------- P3: the seat collapse {hbar, m_e, m_p} -> ONE ----------
    // Bijection 1 (W=1): hbar/m_e = kappa/2pi = (ac)*a0 — the ladder fixes the RATIO of
    // action to mass. That ratio is measurable KILOGRAM-FREE (photon-recoil h/m experiments).
    const double ratio_action_mass = hb / me;                 // [m^2/s] — the kg-free observable
    std::printf("P3  bijection 1 (W=1): hbar/m_e = %.9e m^2/s = kappa/2pi (kg-free observable)\n",
                ratio_action_mass);
    // Bijection 2 (W=3): the trefoil relation R_p*m_p*c/hbar = W+1 = 4 (laws.hpp law_VI).
    const double Wp1 = Rp * mp * c / hb;
    std::printf("    bijection 2 (W=3): R_p*m_p*c/hbar = %.6f  vs 4 (W+1): dev = %+.4f%%\n",
                Wp1, (Wp1 / 4.0 - 1) * 100);
    // Collapse cross-check: eliminate hbar between the two rung relations:
    //   r_e*m_e*c = a*hbar   and   R_p*m_p*c = 4*hbar
    //   => m_p/m_e = (4/a)*(r_e/R_p)   — a PURE RATIO statement, no action, no kg.
    const double mass_ratio_geom = (4.0 / al) * (re / Rp);
    const double mass_ratio_meas = mp / me;
    std::printf("    collapse cross-check: (4/a)*(r_e/R_p) = %.3f vs measured m_p/m_e = %.3f  dev = %+.4f%%\n",
                mass_ratio_geom, mass_ratio_meas, (mass_ratio_geom / mass_ratio_meas - 1) * 100);
    std::puts("    [CONSISTENCY exhibit of the one-seat collapse, NOT a derivation of the ratio:");
    std::puts("     R_p is measured, and W+1=4 carries its own 0.03%-class residual.]");
    const bool p3_gate = std::abs(Wp1 / 4.0 - 1) < 0.01
                      && std::abs(mass_ratio_geom / mass_ratio_meas - 1) < 0.005;
    std::puts("    SEAT COUNT: fix ANY ONE of {hbar, m_e, m_p} -> the other two follow from the");
    std::puts("    ladder geometry (W=1 ratio, W=3 trefoil). ONE mass/action seat survives -> FLM12.\n");

    // ---------- P4: the hbar-free frontier ----------
    std::puts("P4  hbar-free frontier (macroscopic routes):");
    std::puts("    - He-II circulation (Vinen): measures kappa = h/m_He in m^2/s — kilogram-free,");
    std::puts("      but yields the RATIO h/m only. Absolute hbar needs a mass in kg.");
    std::puts("    - Flux quantum / Josephson: yield h/(2e), 2e/h — ratios against the charge");
    std::puts("      unit-bridge, not an absolute action.");
    std::puts("    - Pre-2019 SI: the kilogram was an ARTIFACT — a counted lump of baryons. That");
    std::puts("      was the one historically hbar-free mass anchor: a BARYON COUNT.");
    std::puts("    VERDICT P4: NO hbar-free path to the VALUE. The irreducible seat is one");
    std::puts("    macroscopic mass anchor == a baryon count times the per-baryon seat; the ladder");
    std::puts("    then distributes it (W=1, W=3). Seed theorem stands. OPEN as pre-committed.\n");

    // ---------- reduced whitelist ----------
    std::puts("REDUCED WHITELIST after the collapse:");
    std::puts("  { l_P <- koppa(g,rho,R) [length seed],");
    std::puts("    c   <- Mercury precession (GOM04),");
    std::puts("    a   <- pure spectral ratio (PPT02/APS05 Route B),");
    std::puts("    ONE mass/action seat (hbar == m_e == m_p via W=1/W=3) -> FLM12,");
    std::puts("    k_B, T_CMB [thermal seat — its own investigation] }");
    std::printf("\nGATES: P1 %s (three forms <=1e-6), P3 %s (W+1 within 1%%, cross-check within 0.5%%)\n",
                p1_gate ? "PASS" : "FAIL", p3_gate ? "PASS" : "FAIL");
    std::puts("DUAL VERDICT: prompt completion A; physics class NATIVE (ROLE + one-seat collapse);");
    std::puts("VALUE: OPEN behind the seed theorem (as pre-committed in RUN_LOG.md).");
    return (p1_gate && p3_gate) ? 0 : 1;
}
