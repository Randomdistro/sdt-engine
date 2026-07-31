// ═══════════════════════════════════════════════════════════════════════
//  derivelist_rederive.cpp — single-pass re-derivation of every whitelisted
//  input, run against the canonical engine (sdt/laws.hpp).
//
//  Author: J. C. Harvey, Melbourne. Direct run 2026-07-30.
//
//  Purpose: for each member of the measured whitelist
//      { c, hbar, l_P, alpha, m_e, m_p, k_B, T_CMB, e }
//  recompute the repo's earned derivation route(s), state the deviation
//  against the measured anchor, and print the standing status:
//      DERIVED / EXTRACTED / IDENTITY-CLASS / UNIT-BRIDGE / OPEN / AXIOM.
//
//  Register: excluded / ruled out / withdrawn where applicable. Every route
//  is labelled with its provenance; circular routes are printed AS circular,
//  never as derivations.
//
//  Build (VS2022, from repo root):
//    cl /std:c++20 /EHsc /O2 /W4 /I Engine\include derivelist\derivelist_rederive.cpp
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>

using namespace sdt::laws;

static void line(const char* route, double got, double ref, const char* tag)
{
    double dev = (ref != 0.0) ? (got / ref - 1.0) * 100.0 : 0.0;
    std::printf("  %-52s %- .10e  ref %- .10e  dev %+9.4f%%  [%s]\n",
                route, got, ref, dev, tag);
}

int main()
{
    std::puts("DERIVELIST — re-derivation of the measured whitelist (direct run)");
    std::puts("=================================================================");

    // ── 1. c — the relay speed ─────────────────────────────────────────
    std::puts("\n[1] c — speed of light (relay speed, Law V)");
    // Spectroscopic route: one hydrogen ladder measured twice — once as
    // frequency (comb), once as wavenumber (length standard). Their ratio
    // is the relay speed. CODATA: cR_inf [Hz] and R_inf [1/m].
    const double cRinf_freq = 3.2898419602508e15;   // [Hz]  Rydberg frequency (measured)
    const double c_spec     = cRinf_freq / measured::R_inf;
    line("c = (cR_inf freq)/(R_inf wavenumber), H ladder", c_spec, measured::c, "IDENTITY (CODATA tabulates cR_inf = c*R_inf)");
    // Orbital route (GOM04/B27): c = k_Sun x v_surface from Mercury precession.
    // PROVENANCE OBJECTION (recorded 2026-07-30): the ephemeris orbital
    // elements feeding k_from_precession (eccentricity, precession rate) are
    // produced by fits that model light propagation with c. The route is
    // WITHDRAWN as a derivation of c; retained as a cross-domain consistency
    // closure only.
    line("c = k_Sun*v_surface (Mercury closure, GOM04)", bridge::c_from_closure,
         measured::c, "CONSISTENCY-ONLY (withdrawn as derivation)");
    // Since 1983 the metre is defined via c: the SI number is a unit bridge.
    std::puts("  note: SI 1983 defines the metre from c — the numerical value is");
    std::puts("        definitional; the physical content is ONE relay speed closing");
    std::puts("        every hydrogen line (Law V movement budget).");

    // ── 2. alpha — the wake coupling ───────────────────────────────────
    std::puts("\n[2] alpha — fine-structure ratio (koppa rung of hydrogen)");
    // Route B (APS05): pure fine/gross frequency ratio — no m_e, no e, no h.
    const double dnu_2P  = 1.096913e10;             // [Hz] H 2P3/2-2P1/2 splitting (measured)
    const double alpha_B = std::sqrt(16.0 * dnu_2P / cRinf_freq);
    line("Route B: alpha^2 = 16*(dnu_2P/cR_inf)  -> 1/alpha", 1.0 / alpha_B,
         measured::alpha_inv, "EXTRACTED (pure ratio)");
    // Route A (APS05/B35): Law-V virial seat from the ionisation limit.
    const double E_ion_eV = 13.598434;              // [eV] H ionisation (series limit)
    const double mec2_eV  = measured::m_e * measured::c * measured::c / measured::eV_to_J;
    const double alpha_A  = std::sqrt(2.0 * E_ion_eV / mec2_eV);
    line("Route A: alpha = sqrt(2*E_ion/m_e c^2) -> 1/alpha", 1.0 / alpha_A,
         measured::alpha_inv, "EXTRACTED (proton-free seat 137.07)");
    // The reading (PPT02): alpha is the koppa rung of the hydrogen ground
    // state — koppa_H = alpha^2 * a_0 = r_e, same law as koppa_Sun.
    const double koppa_H = measured::alpha * measured::alpha * measured::a_0;
    line("koppa_H = alpha^2*a_0  vs  r_e (same length)", koppa_H,
         measured::r_e, "IDENTITY-CLASS (the rung reading)");
    std::puts("  status: read off the spectrum two ways (0.1%); geometric derivation");
    std::puts("          OPEN. The CONDENSA closed-form search is excluded (no clean");
    std::puts("          a*pi^b form exists for alpha — contrast 6pi^5).");

    // ── 3. hbar — the circulation quantum ──────────────────────────────
    std::puts("\n[3] hbar — action quantum (FLM13: W=1 circulation, one seat)");
    // ROLE: hbar is the Onsager-Feynman circulation action of the W=1 vortex.
    const double hbar_role = measured::m_e * (measured::alpha * measured::c) * measured::a_0;
    line("hbar = m_e*(alpha c)*a_0 (W=1 circulation)", hbar_role,
         measured::hbar, "IDENTITY-CLASS (role, not value)");
    const double hbar_role2 = measured::r_e * measured::m_e * measured::c / measured::alpha;
    line("hbar = r_e*m_e*c/alpha (same rung, restated)", hbar_role2,
         measured::hbar, "IDENTITY-CLASS");
    // Kilogram-free observable: hbar/m_e (photon-recoil class).
    line("hbar/m_e = kappa/2pi [m^2/s] (kg-free observable)",
         measured::hbar / measured::m_e, 1.15767635e-4, "OBSERVED");
    // W=3 rung: R_p*m_p*c/hbar = W+1 = 4.
    line("R_p*m_p*c/hbar (should be W+1 = 4)",
         measured::R_p * measured::m_p * measured::c / measured::hbar, 4.0, "DERIVED (W+1)");
    std::puts("  status: ROLE derived; VALUE has no hbar-free path (FLM13 dimensional");
    std::puts("          theorem). {hbar, m_e, m_p} collapse to ONE mass/action seat —");
    std::puts("          a baryon-count anchor. Two constants leave the list; one seat stays.");

    // ── 4. l_P — the spation floor ─────────────────────────────────────
    std::puts("\n[4] l_P — Planck length (Axiom R1, the one dimensional seed)");
    // FLM06 clean candidates reach ~10^3; required subdivision is ~10^61.
    const double N_needed = measured::R_CMB / measured::l_P;
    const double N_clean  = measured::z_rec;   // best hbar/G-free candidate
    std::printf("  cleanest hbar/G-free subdivision N = z_rec = %.4g; required N = %.4g\n",
                N_clean, N_needed);
    std::printf("  shortfall factor = %.3e  -> route EXCLUDED (FLM06 Phase 1 negative)\n",
                N_needed / N_clean);
    // Koppa re-expression (circular w.r.t. l_P — printed as such):
    const double koppa_pb   = measured::l_P * measured::l_P * measured::c * measured::m_p / measured::hbar;
    const double lambdabar_p = measured::hbar / (measured::m_p * measured::c);
    line("l_P = sqrt(koppa_per_baryon * lambdabar_p)", std::sqrt(koppa_pb * lambdabar_p),
         measured::l_P, "CIRCULAR (re-expression, not derivation)");
    std::puts("  status: NOT derivable from SDT-native quantities — Seed Theorem");
    std::puts("          (FLM06, PROVEN): exactly one action/mass/length anchor is");
    std::puts("          unavoidable. l_P stays AXIOM R1. No line drawn.");

    // ── 5. m_e — electron mass ─────────────────────────────────────────
    std::puts("\n[5] m_e — electron mass (velocity-resistance form, FLM12/FLM13)");
    // The velocity-resistance formula: resistance = action / (seat velocity x seat radius).
    const double m_e_vr = measured::hbar / ((measured::alpha * measured::c) * measured::a_0);
    line("m_e = hbar/(v_seat*a_0), v_seat = alpha*c", m_e_vr,
         measured::m_e, "IDENTITY-CLASS (seat form)");
    // Law IV occlusion-cost role: V_disp from m, m from V_disp (round trip).
    line("m_e = Phi*V_disp_e/(3 l_P^3 c^2) (Law IV role)",
         law_IV::mass_from_V_disp(law_IV::V_disp_e), measured::m_e, "CIRCULAR (round trip: V_disp from m, m from V_disp)");
    std::puts("  status: MECHANISM native (FLM12: mass = field resistance to change");
    std::puts("          of vector; recovers Newton I/II, E=mc^2, equivalence as");
    std::puts("          theorem). VALUE = the one seat (shared with hbar, m_p).");

    // ── 6. m_p — proton mass ───────────────────────────────────────────
    std::puts("\n[6] m_p — proton mass (occlusion formula + W+1 boundary route)");
    // Occlusion formula (Law IV): m = Phi*V_disp/(3 l_P^3 c^2).
    line("m_p = Phi*V_disp_p/(3 l_P^3 c^2) (occlusion cost)",
         law_IV::mass_from_V_disp(law_IV::V_disp_p), measured::m_p, "CIRCULAR (round trip)");
    // W+1 boundary route: the measured proton boundary radius returns the mass.
    const double m_p_W1 = 4.0 * measured::hbar / (measured::R_p * measured::c);
    line("m_p = 4*hbar/(R_p*c) (W+1, muonic R_p input)", m_p_W1,
         measured::m_p, "DERIVED (from measured boundary radius)");
    // Topological ratio: 6pi^5 (PPT07: OPEN — privileged, unexplained, 19 ppm).
    line("m_p = 6*pi^5*m_e (topological ratio)", law_VI::mass_ratio::six_pi_5 * measured::m_e,
         measured::m_p, "OPEN (privileged 19-ppm match, mechanism owed)");
    // hbar-free pure-ratio statement (FLM13 P3):
    const double ratio_pure = (4.0 / measured::alpha) * (measured::r_e / measured::R_p);
    line("m_p/m_e = (4/alpha)*(r_e/R_p) (hbar eliminated)", ratio_pure,
         measured::m_p / measured::m_e, "DERIVED (pure ratio, one 0.02% residual)");
    std::puts("  status: role + boundary-radius route drawn; ratio mechanism (wake");
    std::puts("          phase-space integral -> 6pi^5) is the named open problem.");

    // ── 7. k_B — Boltzmann constant ────────────────────────────────────
    std::puts("\n[7] k_B — Boltzmann constant (TD02: kelvin unit bridge)");
    // TD02 delete-test: k_B enters only as the kelvin bridge; temperature and
    // the exponential occupation are counted natively. Consistency: a_rad.
    const double pi = std::numbers::pi;
    const double a_rad_calc = pi * pi * std::pow(measured::k_B, 4)
                            / (15.0 * std::pow(measured::hbar, 3) * std::pow(measured::c, 3));
    line("a_rad = pi^2 k_B^4/(15 hbar^3 c^3) (TD06 4.4ppm)", a_rad_calc,
         measured::a_rad, "DERIVED (blackbody suite from counted modes)");
    std::puts("  status: SI-exact since 2019 — k_B DEFINES the kelvin. Reclassified");
    std::puts("          UNIT BRIDGE: no physical content to derive. Line drawn by");
    std::puts("          reclassification (TD02 P4 delete-test).");

    // ── 8. T_CMB — present convergence temperature ─────────────────────
    std::puts("\n[8] T_CMB — CMB temperature (boundary state, not a constant)");
    // CR13 backtrack: emission at the transparency edge, Wien inverse.
    const double lambda_emit = 974.7e-9;            // [m] CR13 closest-contact wavelength
    const double b_wien      = 2.897771955e-3;      // [m K] Wien displacement (derived, B07)
    const double T_rec_calc  = b_wien / lambda_emit;
    line("T_rec = b/lambda_emit (CR13, 974.7 nm edge)", T_rec_calc,
         measured::T_rec, "COMPUTED (convergence chain)");
    const double T_cmb_back = T_rec_calc / (1.0 + measured::z_rec);
    line("T_CMB = T_rec/(1+z_rec) (shared-input check)", T_cmb_back,
         measured::T_CMB, "CONSISTENCY (z_rec shared input — not a derivation)");
    std::printf("  octave count (CR07): log2(1+z_rec) = %.3f octaves\n",
                std::log2(1.0 + measured::z_rec));
    std::puts("  status: remains MEASURED (FIRAS). Reclassified: a boundary-state");
    std::puts("          reading (the present convergence temperature — a clock, not");
    std::puts("          a constant of nature). Absolute value not derivable from");
    std::puts("          within; it is the state the cycle is currently in.");

    // ── 9. e — elementary charge ───────────────────────────────────────
    std::puts("\n[9] e — elementary charge (EMC02: irreducible unit bridge)");
    // Coulomb identity route — exact and CIRCULAR (definitional):
    const double e_coul = std::sqrt(measured::alpha * measured::hbar * measured::c / measured::k_e);
    line("e = sqrt(alpha*hbar*c/k_e) (Coulomb identity)", e_coul,
         measured::e_charge, "CIRCULAR (definitional, printed as such)");
    // The earned object behind 'charge' is the redirection magnitude (EMC04):
    const double P_eff_calc = measured::m_p * measured::m_p * measured::m_e * measured::m_e
                            * std::pow(measured::c, 5)
                            / (4.0 * pi * measured::alpha * std::pow(measured::hbar, 3));
    line("P_eff = m_p^2 m_e^2 c^5/(4 pi alpha hbar^3) (EMC04)", P_eff_calc,
         5.225e31, "DERIVED (the physical target behind e)");
    std::puts("  status: whitelist {l_P,c,hbar,k_B,T_CMB} has no current dimension [A];");
    std::puts("          no combination yields coulombs (EMC02 dimensional result).");
    std::puts("          e is a UNIT BRIDGE (no charge substance — handed redirection);");
    std::puts("          line drawn by reclassification, not by derivation.");

    // ── Summary ────────────────────────────────────────────────────────
    std::puts("\n=================================================================");
    std::puts("REDUCED WHITELIST (after the lines are drawn):");
    std::puts("  l_P            AXIOM R1 — the one dimensional seed (Seed Theorem)");
    std::puts("  ONE mass seat  {hbar = m_e = m_p} collapsed via W=1/W=3 (FLM13)");
    std::puts("  alpha          extracted from the H spectrum; derivation open");
    std::puts("  a_0            MEASURED — the length the seat form rides on");
    std::puts("                 (audit F3: m_e = hbar/(alpha c a_0) consumes it;");
    std::puts("                  no derived route for a_0 exists in laws.hpp)");
    std::puts("  T_CMB          boundary state (thermal seat), measured");
    std::puts("  c, k_B, e      unit bridges — SI definitions, no physics to derive");
    std::puts("  [R_p == m_p    one fact, not two: the 0.02% residual is shared]");
    std::puts("  => FIVE external inputs, not four. The collapse moves the");
    std::puts("     mystery from a mass to a length; closing a_0 (c^2/C_H) or");
    std::puts("     the 6pi^5 wake integral is what would actually shorten it.");
    std::puts("Open mechanisms owed: 6pi^5 wake integral; alpha geometric route;");
    std::puts("the seat's absolute magnitude (FLM12 D-series).");
    return 0;
}
