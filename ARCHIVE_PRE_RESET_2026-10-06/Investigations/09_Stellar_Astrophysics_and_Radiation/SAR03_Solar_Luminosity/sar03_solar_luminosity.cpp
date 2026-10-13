// ============================================================================
// SAR03 — Solar Luminosity from Convergence Recycling
// Author: J. C. Harvey, Melbourne. Date: 2026-07-03.
//
// Question: does the SDT convergence-recycling budget produce L_Sun = 3.828e26 W
// natively? Pre-registered chains C1-C5 (RUN_LOG.md), gate 20% (prompt),
// order-of-magnitude NATIVE gate x10. No exponent fishing: only the prompt's
// own chains are evaluated. L_Sun is the OBSERVED target, never an input to
// any chain claiming to derive it (C5 consumes it and is labelled so).
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::laws;

static const char* gate(double Lchain, double Ltarget) {
    const double r = Lchain / Ltarget;
    if (std::fabs(r - 1.0) <= 0.20) return "PASS (20% gate)";
    if (r >= 0.1 && r <= 10.0)      return "ORDER-OF-MAGNITUDE only";
    return "FAIL";
}

int main() {
    const double L_Sun  = law_II::L_Sun;          // 3.828e26 W (OBSERVED anchor / target)
    const double R_Sun  = measured::R_Sun;
    const double T_eff  = 5778.0;                 // K (IAU, OBSERVED)
    const double A_Sun  = 4.0 * std::numbers::pi * R_Sun * R_Sun;
    const double disc   = std::numbers::pi * R_Sun * R_Sun;
    const double z_Sun  = 1.0 / (bridge::k_Sun * bridge::k_Sun);   // 2.124e-6
    const double sigma_SB = 5.670374419e-8;       // W/m^2/K^4 = a_rad*c/4 (derivation basis {k_B,hbar,c})
    const double sigma_from_arad = measured::a_rad * measured::c / 4.0;

    std::printf("SAR03 — Solar Luminosity from Convergence Recycling (J. C. Harvey, 2026-07-03)\n");
    std::printf("================================================================================\n\n");
    std::printf("[0] Inputs (sdt::laws)\n");
    std::printf("    L_Sun (target, OBSERVED) = %.4e W\n", L_Sun);
    std::printf("    R_Sun = %.4e m   A_surf = %.4e m^2   disc = %.4e m^2\n", R_Sun, A_Sun, disc);
    std::printf("    k_Sun = %.1f -> z_Sun = 1/k^2 = %.4e (= depth_closure::z_spectral_Sun %.4e)\n",
                bridge::k_Sun, z_Sun, depth_closure::z_spectral_Sun);
    std::printf("    P_conv = %.4e Pa   f = %.4e   F_CMB = %.4e W/m^2\n",
                law_I::P_conv, law_III::f_transfer, law_II::F_CMB);
    std::printf("    sigma_SB check: a_rad*c/4 = %.6e vs CODATA %.6e (%.3f%%)\n\n",
                sigma_from_arad, sigma_SB, (sigma_from_arad/sigma_SB - 1.0)*100.0);

    // ---- C1: prompt chain — L = z_Sun * 4 pi R^2 * P_conv * c -----------------
    const double C1 = z_Sun * A_Sun * law_I::P_conv * measured::c;
    std::printf("[C1] L = z_Sun x 4piR^2 x P_conv x c = %.4e W\n", C1);
    std::printf("     ratio to L_Sun = %.3e  -> %s (off by 10^%.1f)\n\n",
                C1/L_Sun, gate(C1, L_Sun), std::log10(C1/L_Sun));

    // ---- C2: C1 x f_transfer ---------------------------------------------------
    const double C2 = C1 * law_III::f_transfer;
    std::printf("[C2] C1 x f_transfer = %.4e W\n", C2);
    std::printf("     ratio to L_Sun = %.3e  -> %s (off by 10^%.1f)\n\n",
                C2/L_Sun, gate(C2, L_Sun), std::log10(C2/L_Sun));

    // ---- C3: CMB interception --------------------------------------------------
    const double C3 = disc * law_II::F_CMB;
    std::printf("[C3] CMB interception pi R^2 x F_CMB = %.4e W\n", C3);
    std::printf("     ratio to L_Sun = %.3e  -> %s (off by 10^%.1f)\n", C3/L_Sun, gate(C3, L_Sun),
                std::log10(C3/L_Sun));
    std::printf("     NOTE: the PROMPT's data table says 4.77e7 W for this row — that value is\n");
    std::printf("     arithmetically WRONG by ~1e5 (correct: %.3e W). Table error, flagged.\n\n", C3);

    // ---- C4: Stefan-Boltzmann identity ------------------------------------------
    const double C4 = A_Sun * sigma_from_arad * T_eff*T_eff*T_eff*T_eff;
    std::printf("[C4] L = 4piR^2 sigma T_eff^4 = %.4e W  (ratio %.4f)\n", C4, C4/L_Sun);
    std::printf("     STATUS: IDENTITY, not a derivation — T_eff is measured FROM the solar\n");
    std::printf("     radiance; this line cannot count as an SDT prediction of L. Excluded.\n\n");

    // ---- C5: pressure-domain consistency (consumes L) ---------------------------
    const double C5 = law_II::pressure_domain(L_Sun);
    const double C5_AU = C5 / measured::AU;
    std::printf("[C5] r_domain = sqrt(L_Sun / 4pi F_CMB) = %.4e m = %.0f AU\n", C5, C5_AU);
    std::printf("     vs Oort centreline ~20,000 AU (OBSERVED, order-of-mag): ratio %.2f -> %s\n",
                C5_AU/20000.0, (C5_AU/20000.0 < 2.0 && C5_AU/20000.0 > 0.5) ? "CONSISTENT" : "FAIL");
    std::printf("     STATUS: consistency check only — CONSUMES L_Sun as input; cannot count\n");
    std::printf("     toward deriving L. (Engine constant r_domain_Sun = %.3e m agrees.)\n\n",
                law_II::r_domain_Sun);

    // ---- Diagnostic (not a chain): what WOULD close the budget -------------------
    const double P_req = L_Sun / (A_Sun * measured::c);   // required radiating pressure
    const double u_surf = measured::a_rad * T_eff*T_eff*T_eff*T_eff;
    std::printf("[Diag] Required effective radiating pressure L/(4piR^2 c) = %.4e Pa\n", P_req);
    std::printf("       = u(T_eff)/4 = %.4e Pa (photon-gas identity) — i.e. the budget closes\n", u_surf/4.0);
    std::printf("       ONLY at the surface-radiation identity (C4), 47 orders below P_conv\n");
    std::printf("       and 14 orders above the CMB flux. No pre-registered SDT chain spans it.\n\n");

    std::printf("VERDICT LINES\n");
    std::printf("  C1 (prompt chain): %.1e x L_Sun -> KILLED\n", C1/L_Sun);
    std::printf("  C2 (coupled variant): %.1e x L_Sun -> KILLED\n", C2/L_Sun);
    std::printf("  C3 (CMB interception): %.1e x L_Sun -> KILLED as luminosity source\n", C3/L_Sun);
    std::printf("  C4: IDENTITY (excluded)   C5: CONSISTENT but consumes L (excluded)\n");
    std::printf("  Native convergence-recycling derivation of L_Sun: NOT ACHIEVED.\n");
    return 0;
}
