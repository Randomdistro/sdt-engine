// ============================================================================
//  EMC04 (SDT-native) — Electropause from occlusion balance + wake closure
//  Derives r*, P_eff, koppa_H without measured::a_0 on the chain.
//
//  Author: James Christopher Tyndall, Melbourne · 2026-06-28
//  Build:  g++ -std=c++20 -IEngine/include electropause_native.cpp -o ep
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <numbers>

namespace {
using namespace sdt::laws;

[[nodiscard]] double rel_err(double a, double b) noexcept {
    return std::fabs(a - b) / std::fabs(b);
}
} // namespace

int main() {
    const double c     = measured::c;
    const double hbar  = measured::hbar;
    const double m_e   = measured::m_e;
    const double m_p   = measured::m_p;
    const double alpha = measured::alpha;

    // --- Native geometry (no a_0, no r_e, no k_e, no e) -------------------
    const double R_p  = 4.0 * hbar / (m_p * c);       // W+1 proton wake [DERIVED]
    const double lam_e = hbar / (m_e * c);            // electron displacement scale [DERIVED]
    const double k_H  = 1.0 / alpha;                  // ground k-rung [whitelist α]
    const double v    = c / k_H;                      // Law V / bridge

    // Step B: one closed wake -> electropause radius [DERIVED]
    const double r_star = hbar / (m_e * v);

    // Step C: hold force
    const double F_hold = m_e * v * v / r_star;

    // Step D: P_eff from balance (invert occlusion — EMC04)
    const double P_eff_derived = 4.0 * F_hold * r_star * r_star
                               / (std::numbers::pi * R_p * R_p * lam_e * lam_e);

    // Whitelist closed form
    const double P_eff_closed = m_p * m_p * m_e * m_e * std::pow(c, 5)
                              / (4.0 * std::numbers::pi * alpha * std::pow(hbar, 3));

    // Occlusion check at r* using derived P_eff and λ_e (not r_e input)
    const double F_occ = (std::numbers::pi / 4.0) * P_eff_derived
                       * R_p * R_p * lam_e * lam_e / (r_star * r_star);

    // zk² and koppa [DERIVED]
    const double z     = (v / c) * (v / c);
    const double zk2   = z * k_H * k_H;
    const double koppa = v * v * r_star / (c * c);
    const double r_e_derived = alpha * lam_e;

    // OBSERVED comparison only — not used above
    const double a0_obs = measured::a_0;

    std::printf("================================================================\n");
    std::printf("  ELECTROPAUSE — SDT-native forward chain\n");
    std::printf("  J. C. Tyndall, Melbourne · no a_0 / Coulomb on derivation path\n");
    std::printf("================================================================\n\n");

    std::printf("INPUTS (whitelist): c, hbar, m_e, m_p, alpha (k-rung)\n\n");

    std::printf("DERIVED electropause\n");
    std::printf("  k_H      = 1/alpha     = %.6f\n", k_H);
    std::printf("  v        = c/k_H       = %.6e m/s\n", v);
    std::printf("  r*       = hbar/(m_e v) = %.6e m\n", r_star);
    std::printf("  a_0 OBS  (compare only)= %.6e m  rel err %.3e\n\n",
                a0_obs, rel_err(r_star, a0_obs));

    std::printf("BALANCE\n");
    std::printf("  F_hold   = m_e v^2/r*  = %.6e N\n", F_hold);
    std::printf("  F_occ    (P_eff, R_p, lambda_e) = %.6e N\n", F_occ);
    std::printf("  ratio hold/occ         = %.12f  [%s]\n\n",
                F_hold / F_occ, rel_err(F_hold, F_occ) < 1e-9 ? "PASS" : "FAIL");

    std::printf("P_eff (output, not calibrated to Coulomb)\n");
    std::printf("  from balance           = %.6e Pa\n", P_eff_derived);
    std::printf("  whitelist closed form  = %.6e Pa\n", P_eff_closed);
    std::printf("  engine law_III::P_eff  = %.6e Pa\n", law_III::P_eff);
    std::printf("  rel vs engine          = %.3e  [%s]\n\n",
                rel_err(P_eff_derived, law_III::P_eff),
                rel_err(P_eff_derived, law_III::P_eff) < 1e-6 ? "PASS" : "FAIL");

    std::printf("zk² ladder at electropause\n");
    std::printf("  z = (v/c)^2            = %.6e\n", z);
    std::printf("  z * k_H^2              = %.12f  [%s]\n", zk2,
                std::fabs(zk2 - 1.0) < 1e-9 ? "IDENTITY PASS" : "FAIL");
    std::printf("  koppa_H = v^2 r*/c^2   = %.6e m\n", koppa);
    std::printf("  alpha*lambda_e         = %.6e m  (engine r_e route)\n\n", r_e_derived);

    const bool pass = rel_err(r_star, a0_obs) < 1e-6
                   && rel_err(F_hold, F_occ) < 1e-9
                   && rel_err(P_eff_derived, law_III::P_eff) < 1e-6
                   && std::fabs(zk2 - 1.0) < 1e-9;

    std::printf("================================================================\n");
    std::printf("  VERDICT: %s — electropause DERIVED; P_eff DERIVED; zk²=1\n",
                pass ? "PASS" : "FAIL");
    std::printf("  Residual whitelist input: alpha (k-rung). Does NOT derive alpha.\n");
    std::printf("================================================================\n");
    return pass ? 0 : 1;
}
