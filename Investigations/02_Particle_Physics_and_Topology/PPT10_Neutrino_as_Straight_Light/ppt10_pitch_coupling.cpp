// ppt10_pitch_coupling.cpp
// PPT10 — The Neutrino as Straight Light: pitch = grip, and the coupling gap.
//
//   Executes the SPEC at PPT10/PROMPT.md.  Reuses the canonical engine only:
//     #include <sdt/laws.hpp>      (measured whitelist, law_V budget, law_VI winding)
//     #include <sdt/neutrino.hpp>  (W=0, wake_radius, R_wake_nu1, R_excl_nu1)
//   NO local constant namespaces.  NO G/M/GM.  NO "charge radius".  NO G_F / virtual-W /
//   flavour / wavefunction in the SDT chain — those appear ONLY as OBSERVED columns.
//
//   Every printed number carries one ledger tag:
//     MEASURED-INPUT | DERIVED | COMPUTED | OBSERVED-TARGET | ASSUMED | PENDING
//
//   Build (MSVC):  cl /std:c++20 /utf-8 /EHsc /O2 /I Engine\include ppt10_pitch_coupling.cpp
//   Build (g++):   g++ -std=c++20 -I Engine/include ppt10_pitch_coupling.cpp -o ppt10
//
//   Author: J. C. Harvey, Melbourne.  Executed 2026-07-01.

#include <sdt/laws.hpp>
#include <sdt/neutrino.hpp>

#include <cstdio>
#include <cmath>

using sdt::laws::measured::c;
using sdt::laws::measured::hbar;
using sdt::laws::measured::m_e;
using sdt::laws::measured::m_p;
using sdt::laws::measured::eV_to_J;

// ---------------------------------------------------------------------------
//  P1 — transverse pitch from the Law-V movement budget.
//
//  Law V:  v_||^2 + v_perp^2 = c^2   (sdt::laws::law_V::v_circ / v_trans).
//  Define  p_T = v_perp / v_|| = tan(theta_w).   DIMENSIONLESS.  Straight = p_T -> 0.
//
//  Native geometric proxy (no free angle):  the wake-cone half-angle set by the body
//  footprint R_excl at the wake reach R_wake:   tan(theta_w) ~ R_excl / R_wake.
//  This is EXACTLY the inverse of neutrino.hpp's headline R_wake/R_excl ratio, so p_T
//  is a re-reading of an already-canonical SDT number, not a new fitted angle.
// ---------------------------------------------------------------------------
[[nodiscard]] static double pitch_from_geometry(double R_excl, double R_wake) noexcept {
    return R_excl / R_wake;                 // = tan(theta_w) proxy = 1 / (R_wake/R_excl)
}

// Consistency check: recover p_T through the Law-V budget from a wake angle.
[[nodiscard]] static double pitch_from_lawV(double v_perp) noexcept {
    const double v_par = sdt::laws::law_V::v_circ(v_perp);   // sqrt(c^2 - v_perp^2)
    return v_perp / v_par;                                    // tan(theta_w)
}

// ---------------------------------------------------------------------------
//  P2 — coupling law.  Grip = transverse FOOTPRINT the wake presents to an incoming
//  relay.  A footprint is an AREA => sigma scales as the square of the transverse
//  extent measured against the forward reach:   sigma proportional to p_T^2.
//  n = 2 is DERIVED from a transverse-area argument, NOT fitted.  (Pre-committed in
//  RUN_LOG BEFORE the neutrino sigma was read.)
// ---------------------------------------------------------------------------
inline constexpr double N_AREA = 2.0;       // DERIVED exponent (transverse area)

int main() {
    std::printf("======================================================================\n");
    std::printf(" PPT10  Neutrino as Straight Light — pitch = grip, and the coupling gap\n");
    std::printf(" Engine: sdt::laws (measured, law_V, law_VI) + sdt::neutrino.  No G/M/GF.\n");
    std::printf("======================================================================\n\n");

    // ---- whitelist constants (reused, not redefined) ----
    std::printf("[MEASURED-INPUT] c    = %.6e m/s   (laws.hpp:110)\n", c);
    std::printf("[MEASURED-INPUT] hbar = %.6e J s   (laws.hpp:111)\n", hbar);
    std::printf("[MEASURED-INPUT] m_e  = %.6e kg    (laws.hpp:151)\n", m_e);
    std::printf("[MEASURED-INPUT] m_p  = %.6e kg    (laws.hpp:152)\n\n", m_p);

    // =====================================================================
    //  PHASE 1 — pitch axis
    // =====================================================================
    std::printf("--- PHASE 1: transverse pitch p_T (Law V budget; geometric proxy) ---\n\n");

    // Emitter/particle wake geometry (from neutrino.hpp comment block + canonical radii).
    // electron: R_wake = classical electron radius r_e (its c-boundary wake); body R_excl.
    const double R_wake_e = sdt::laws::measured::r_e;   // electron wake  (laws.hpp measured)
    const double R_excl_e = 2.88e-21;                    // [ASSUMED] electron body (neutrino.hpp cmt)
    const double R_wake_p = 8.41e-16;                    // [ASSUMED] proton wake  (neutrino.hpp cmt)
    const double R_excl_p = 3.52e-20;                    // [ASSUMED] proton body  (neutrino.hpp cmt)
    const double R_wake_n = sdt::neutrino::R_wake_nu1;   // DERIVED  hbar/(m_nu c)  (neutrino.hpp:74)
    const double R_excl_n = sdt::neutrino::R_excl_nu1;   // canonical body (neutrino.hpp:92)

    const double pT_e = pitch_from_geometry(R_excl_e, R_wake_e);
    const double pT_p = pitch_from_geometry(R_excl_p, R_wake_p);
    const double pT_n = pitch_from_geometry(R_excl_n, R_wake_n);

    std::printf("  rung          R_excl [m]     R_wake [m]     p_T = R_excl/R_wake    W\n");
    std::printf("  electron(W1)  %.3e     %.3e     %.4e   [DERIVED]  1\n", R_excl_e, R_wake_e, pT_e);
    std::printf("  proton  (W3)  %.3e     %.3e     %.4e   [DERIVED]  3  (closed trefoil; off-ladder)\n",
                R_excl_p, R_wake_p, pT_p);
    std::printf("  neutrino(W0)  %.3e     %.3e     %.4e   [DERIVED]  0  <= straight, p_T->0\n\n",
                R_excl_n, R_wake_n, pT_n);

    // Law-V cross-check: reconstruct pT_n from a wake angle and confirm the budget closes.
    const double theta_n = std::atan(pT_n);
    const double v_perp_n = c * std::sin(theta_n);
    const double pT_n_lawV = pitch_from_lawV(v_perp_n);
    std::printf("  Law-V check: theta_w(nu)=%.3e rad  v_perp=%.3e m/s  p_T(Law V)=%.4e\n",
                theta_n, v_perp_n, pT_n_lawV);
    std::printf("               budget v_||^2+v_perp^2 = c^2 closes to %.15f  [DERIVED]\n\n",
                (sdt::laws::law_V::v_circ(v_perp_n)*sdt::laws::law_V::v_circ(v_perp_n)
                 + v_perp_n*v_perp_n) / (c*c));

    // Wake-ratio sanity tie (neutrino.hpp headline ~1e18)
    std::printf("  wake/body tie: R_wake/R_excl (nu) = %.3e  vs neutrino.hpp 1.01e18  [COMPUTED]\n",
                R_wake_n / R_excl_n);
    std::printf("  ==> F1: p_T monotone-decreasing on the W1->W0 straight-light line to p_T=0.\n");
    std::printf("      CAVEAT (ADJ-001): proton (closed W3) is NOT a rung on this line; the naive\n");
    std::printf("      proxy is non-monotone e->p, so proton is a comparison point only.\n\n");

    // =====================================================================
    //  PHASE 2 — coupling = f(pitch)
    // =====================================================================
    std::printf("--- PHASE 2: sigma(p_T) = A0 * p_T^n, n=2 DERIVED (transverse area) ---\n\n");

    // Sign test F2: dsigma/dp_T = n A0 p_T^(n-1) > 0  => sigma FALLS as p_T->0.
    std::printf("  F2 sign test: dsigma/dp_T = n*A0*p_T^(n-1) > 0 for n=%.0f  => sigma DECREASES\n", N_AREA);
    std::printf("                as p_T->0.  Straightening removes grip.  [DERIVED]  F2 PASSES.\n\n");

    // Ratio-only prediction (scale-free): electron-referenced, NO absolute A0 fit.
    const double dlog_pT = std::log10(pT_e / pT_n);         // pitch decades e->nu
    const double pred_orders = N_AREA * dlog_pT;            // DERIVED suppression e->nu
    std::printf("  pitch decades electron->neutrino:  log10(p_T,e / p_T,nu) = %.3f  [DERIVED]\n", dlog_pT);
    std::printf("  DERIVED suppression (n=2):         %.0f * %.3f = %.2f orders  [DERIVED]\n\n",
                N_AREA, dlog_pT, pred_orders);

    // ---- OBSERVED comparison column (read ONLY now; pre-commit already fixed n) ----
    const double sigma_photon = 6.6524587e-29;   // [OBSERVED-TARGET] Thomson sigma_T [m^2]
    const double sigma_nu_10MeV = 1.0e-47;       // [OBSERVED-TARGET] nu-nucleon ~10 MeV [m^2]
    const double sigma_nu_1MeV  = 1.0e-48;       // [OBSERVED-TARGET] nu-nucleon ~1 MeV  [m^2]
    const double obs_orders_10  = std::log10(sigma_photon / sigma_nu_10MeV);
    const double obs_orders_1   = std::log10(sigma_photon / sigma_nu_1MeV);

    std::printf("  OBSERVED photon (Thomson) sigma = %.3e m^2                 [OBSERVED-TARGET]\n", sigma_photon);
    std::printf("  OBSERVED neutrino sigma  ~10 MeV = %.3e m^2                 [OBSERVED-TARGET]\n", sigma_nu_10MeV);
    std::printf("  OBSERVED neutrino sigma  ~1  MeV = %.3e m^2                 [OBSERVED-TARGET]\n", sigma_nu_1MeV);
    std::printf("  OBSERVED suppression: %.2f orders (10 MeV) .. %.2f orders (1 MeV)\n\n",
                obs_orders_10, obs_orders_1);

    // ---- verdict on P2 pre-committed band (+/-2 orders on ~20) ----
    const double delta = pred_orders - obs_orders_10;
    const double n_needed = obs_orders_10 / dlog_pT;         // exponent that WOULD hit it (= a FIT)
    std::printf("  COMPARE: DERIVED %.1f  vs  OBSERVED %.1f  =>  Delta = %.1f orders\n",
                pred_orders, obs_orders_10, delta);
    std::printf("  Committed band = +/-2 orders on ~20.  |Delta|=%.1f => OUTSIDE band.\n", std::fabs(delta));
    std::printf("  Exponent that WOULD hit 18.8: n = %.2f  <= FITTING this is IDENTITY-PASS (FORBIDDEN).\n",
                n_needed);
    std::printf("  ==> F3 fires as NEAR-MISS: right sign (F2), right order-class (tens of orders),\n");
    std::printf("      but geometry OVERSHOOTS by ~%.0f orders; NOT a clean +/-2 PASS, NOT fitted.\n",
                std::fabs(delta));
    std::printf("      Grade held C (CONVERGENCE with residual).  [COMPUTED]\n\n");

    // =====================================================================
    //  PHASE 3 — CONTINUOUS vs SNAP: where does the missing middle sit?
    // =====================================================================
    std::printf("--- PHASE 3: the missing middle (CONTINUOUS vs SNAP) ---\n\n");
    std::printf("  P2's sigma(p_T)=A0 p_T^2 is CONTINUOUS => predicts intermediate-pitch,\n");
    std::printf("  half-gripping emissions.  Tabulate the predicted (p_T, suppression) middle:\n\n");
    std::printf("     p_T           decades below e-pitch   predicted suppression vs photon\n");
    const double pT_mid[] = { 1e-9, 1e-12, 1e-15 };
    for (double pm : pT_mid) {
        const double dl = std::log10(pT_e / pm);
        const double sup = N_AREA * dl;
        std::printf("     %.1e        %6.2f                 %6.2f orders     [COMPUTED predicted middle]\n",
                    pm, dl, sup);
    }
    std::printf("\n  Search for occupants: collinear/forward soft radiation & coherent forward\n");
    std::printf("  scattering ARE low-sigma strongly-forward channels (candidate occupants), but\n");
    std::printf("  none is cleanly a measured 'half-neutrino'.  Middle NOT observed populated,\n");
    std::printf("  but ALSO NOT provably empty (mislabelled forward channels not excluded).\n\n");
    std::printf("  Topological snap available? W is discrete (Alexander invariant, law_VI::winding;\n");
    std::printf("  PPT09).  BUT p_T (continuous Law-V partition) != W (discrete label): a W-snap does\n");
    std::printf("  NOT force a p_T-snap.  Asserting one on p_T to save the fit = PLUG (forbidden).\n");
    std::printf("  W_neutrino = %d (open) vs W_electron = %d (closed).  [DERIVED topology]\n\n",
                sdt::neutrino::W_neutrino, sdt::laws::law_VI::winding::W_electron);
    std::printf("  DECISION (against pre-written rule): middle neither populated (CONTINUOUS not\n");
    std::printf("  earned) nor provably empty with an admissible p_T-snap (SNAP not earned)\n");
    std::printf("  ==> **OPEN** — ship the sharpened fork.  P3 does NOT retro-PASS.\n\n");

    // =====================================================================
    //  PHASE 4 — the nu_e -> e- grounding prediction (NP18 test)
    // =====================================================================
    std::printf("--- PHASE 4: nu_e -> e- direct grounding (SDT) vs SM ---\n\n");
    std::printf("  SDT: a neutrino is straight-running electron-stuff.  Hit a GAPLESS wall (no\n");
    std::printf("       through-channel at the incoming pitch) and the thread cannot stay straight\n");
    std::printf("       => it grounds into a wiggling electron (nu_e -> e-), NO mediator.  Observable:\n");
    std::printf("       an electron with the neutrino's forward energy, continuum-distributed.\n");
    std::printf("  SM : flavour conserved at the vertex; e- only via weak CC through a virtual W\n");
    std::printf("       (rate ~ G_F^2).  DIRECT free nu_e -> e- is FORBIDDEN.   [OBSERVED-TARGET]\n");
    std::printf("  DISCRIMINATOR: presence (SDT) vs absence (SM) of a direct, mediator-free\n");
    std::printf("  conversion channel + its continuum electron spectrum.  Not degenerate.\n");
    std::printf("  Numeric apparatus design handed to NP18.  P4 PASS-GATE.\n\n");

    // =====================================================================
    //  SUMMARY
    // =====================================================================
    std::printf("======================================================================\n");
    std::printf(" SUMMARY (dual verdict in PPT10_VERDICT.md)\n");
    std::printf("  P1 pitch axis .............. PASS-GATE (Law V + geometry; e/p caveat)\n");
    std::printf("  P2 sigma~p_T^2 (n=2 DERIVED) QUALIFIED: F2 pass; F3 near-miss (24 vs 18.8),\n");
    std::printf("                               NOT fitted -> Class C CONVERGENCE with residual\n");
    std::printf("  P3 CONTINUOUS vs SNAP ...... OPEN (sharpened fork; middle unproven either way)\n");
    std::printf("  P4 nu_e->e- vs SM .......... PASS-GATE (discriminating; handed to NP18)\n");
    std::printf("  PHYSICS CLASS: OPEN (sharpened fork).  The ~20-order gap is a REAL DEBT.\n");
    std::printf("======================================================================\n");
    return 0;
}
