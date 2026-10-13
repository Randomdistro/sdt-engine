// =====================================================================================
//  np09_deuteron_binding.cpp — deuteron binding from Law III occlusion integral
//
//  E_B = integral_{r0..inf} F_occlusion dr = (pi/4) P_eff R_p^2 R_n^2 / r0
//
//  Build (MSVC):
//    cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include np09_deuteron_binding.cpp /Fe:np09.exe
//  Author: James Christopher Tyndall, Melbourne.
// =====================================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

namespace M = sdt::laws::measured;
namespace L3 = sdt::laws::law_III;

static double rel_pct(double a, double b) { return (a - b) / b * 100.0; }

int main() {
    const double R_p   = M::R_p;
    const double R_n   = M::R_p;              // same W=3 topology, l>=3 wake
    const double r0    = 2.14e-15;            // measured deuteron separation [m]
    const double B_meas = M::B_deuteron;      // 2.224 MeV

    const double E_J = (std::numbers::pi / 4.0) * L3::P_eff * R_p * R_p * R_n * R_n / r0;
    const double E_MeV = E_J / M::MeV_to_J;

    const double R_n_req = std::sqrt(4.0 * r0 * B_meas * M::MeV_to_J
                                     / (std::numbers::pi * L3::P_eff * R_p * R_p));
    const double R_n_W1 = 4.0 * M::hbar / (M::m_n * M::c);

    std::printf("############################################################################\n");
    std::printf("#  NP09 — Deuteron binding from occlusion geometry (Law III)               #\n");
    std::printf("#  No G, no M.  P_eff from hydrogen calibration (class E coefficient).    #\n");
    std::printf("############################################################################\n\n");

    std::printf("  P_eff     = %.4e Pa  (law_III, hydrogen-calibrated)\n", L3::P_eff);
    std::printf("  R_p       = %.4e m\n", R_p);
    std::printf("  R_n (hyp) = R_p (same trefoil topology)\n");
    std::printf("  r0        = %.4e m  (measured separation)\n\n", r0);

    std::printf("  E_bind (occlusion integral) = %.4f MeV\n", E_MeV);
    std::printf("  measured B_d                = %.4f MeV\n", B_meas);
    std::printf("  relative error              = %+.2f%%\n\n", rel_pct(E_MeV, B_meas));

    std::printf("=== Reverse: R_n,eff required to match B_d ===\n");
    std::printf("  R_n,eff = %.4e m  (%.3f fm)\n", R_n_req, R_n_req * 1e15);
    std::printf("  R_p     = %.4e m  (%.3f fm)  ratio R_n/R_p = %.4f\n",
                R_p, R_p * 1e15, R_n_req / R_p);
    std::printf("  W+1 neutron radius 4hbar/(m_n c) = %.4e m  (%.3f fm)\n\n",
                R_n_W1, R_n_W1 * 1e15);

    const bool pass_order = std::fabs(rel_pct(E_MeV, B_meas)) < 50.0;
    const bool pass_10 = std::fabs(rel_pct(E_MeV, B_meas)) < 10.0;

    std::printf("================================================================\n");
    std::printf("  VERDICT: %s\n", pass_10 ? "PASS (within 10%)" :
                                      pass_order ? "PARTIAL (order-of-magnitude)" : "FAIL");
    std::printf("  Class: %s — 1/r^2 occlusion structure is native; magnitude via P_eff (E).\n",
                pass_10 ? "C (CONVERGENCE at 10%)" : "E/PARTIAL — P_eff scale mismatch");
    std::printf("  NP17 shared-electron route gives 2.224 MeV exactly (factor 3 geometry).\n");
    std::printf("  Occlusion alone %s the measured binding without nuclear P_eff rescaling.\n",
                pass_10 ? "matches" : "does NOT match");
    std::printf("================================================================\n");

    return pass_order ? 0 : 1;
}
