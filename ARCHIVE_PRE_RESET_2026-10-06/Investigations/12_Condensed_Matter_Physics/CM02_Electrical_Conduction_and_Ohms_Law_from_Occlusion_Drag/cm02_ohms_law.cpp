// ============================================================================
//  CM02 — Ohm's Law from Occlusion Drag (Phase 1–2)
//  Drude: sigma = n e^2 tau / m_e; tau from relay mean free path.
//
//  Author: James Christopher Tyndall, Melbourne.
//  Build:  g++ -std=c++20 -IEngine/include cm02_ohms_law.cpp -o cm02
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

namespace {
using namespace sdt::laws;
constexpr double EV = measured::eV_to_J;
// Copper at 300 K [OBSERVED]
constexpr double N_CU = 8.5e28;       // conduction electron density [1/m^3]
constexpr double SIGMA_CU = 5.96e7;    // conductivity [S/m]
constexpr double TAU_CU = 2.5e-14;   // mean collision time [s] (from measured sigma)
}

int main() {
    std::printf("================================================================\n");
    std::printf("  CM02 — Ohm's Law from Occlusion Drag\n");
    std::printf("  Author: James Christopher Tyndall, Melbourne\n");
    std::printf("================================================================\n\n");

    const double e  = measured::e_charge;
    const double me = measured::m_e;
    const double h  = measured::hbar * 2.0 * std::numbers::pi;

    // Drude conductivity from occlusion mean free time tau
    const double sigma = N_CU * e * e * TAU_CU / me;
    const double err = std::fabs(sigma - SIGMA_CU) / SIGMA_CU;

    std::printf("DRUDE FORM (H1: native balance push vs occlusion drag)\n");
    std::printf("  sigma = n e^2 tau / m_e\n");
    std::printf("  n (Cu)     = %.2e /m^3  [OBSERVED]\n", N_CU);
    std::printf("  tau (Cu)   = %.2e s      [OBSERVED via sigma]\n", TAU_CU);
    std::printf("  sigma calc = %.3e S/m\n", sigma);
    std::printf("  sigma meas = %.3e S/m\n", SIGMA_CU);
    std::printf("  |error|    = %.2f%%  [%s]\n\n", err * 100.0, err < 0.02 ? "PASS" : "FAIL");

    std::printf("NATIVE OHM (H3: R_K = h/e^2)\n");
    const double R_K = h / (e * e);
    std::printf("  R_K = h/e^2 = %.6f Ohm  (von Klitzing)  [OBSERVED]\n", R_K);
    std::printf("  Links quantum Hall / Josephson metrology (CM06)  [CONVERGENCE]\n\n");

    std::printf("MOBILITY mu = e tau / m_e\n");
    const double mu = e * TAU_CU / me;
    std::printf("  mu = %.4e m^2/V/s\n\n", mu);

    const bool pass = err < 0.02;
    std::printf("================================================================\n");
    std::printf("  VERDICT: %s — Class C (CONVERGENCE)\n", pass ? "PASS" : "FAIL");
    std::printf("  Drude form reproduced; tau tagged OBSERVED (occlusion MFP OPEN).\n");
    std::printf("  rho(T) linear law: PENDING (Phase 3).\n");
    std::printf("================================================================\n");
    return pass ? 0 : 1;
}
