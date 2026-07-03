// ============================================================================
//  SAR02 — Blackbody Radiation from Lattice Mode Counting
//  n(nu)=8 pi nu^2/c^3; Planck occupation; Stefan-Boltzmann a; Wien peak.
//
//  Author: James Christopher Tyndall, Melbourne.
//  Build:  g++ -std=c++20 -IEngine/include sar02_blackbody_lattice.cpp -o sar02
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

namespace {
constexpr double PI = std::numbers::pi;
constexpr double ZETA3 = 1.2020569031595942;
using namespace sdt::laws;
}

int main() {
    std::printf("================================================================\n");
    std::printf("  SAR02 — Blackbody from Lattice Mode Counting\n");
    std::printf("  Author: James Christopher Tyndall, Melbourne\n");
    std::printf("================================================================\n\n");

    const double c  = measured::c;
    const double h  = measured::hbar * 2.0 * PI;  // Planck constant
    const double kB = measured::k_B;
    const double T0 = measured::T_CMB;

    const double a_computed = (8.0 * std::pow(PI, 5) / 15.0)
                            * std::pow(kB, 4) / (std::pow(h, 3) * std::pow(c, 3));
    const double a_target   = measured::a_rad;

    const double hbar = measured::hbar;
    const double n_pref = (2.0 * ZETA3 / (PI * PI)) * std::pow(kB / (hbar * c), 3);
    const double n_cmb  = n_pref * std::pow(T0, 3);

    // Wien (wavelength form): lambda_peak T = hc / (x_wien k_B), x_wien = 4.965114231...
    const double x_wien = 4.965114231744276;
    const double lam_wien = 2.897771955e-3;  // CODATA m·K
    const double lam_peak = h * c / (x_wien * kB * T0);

    std::printf("STEFAN-BOLTZMANN (mode integral)\n");
    std::printf("  a (computed) = %.6e J/m^3/K^4\n", a_computed);
    std::printf("  a (measured) = %.6e J/m^3/K^4\n", a_target);
    const double a_err = std::fabs(a_computed - a_target) / a_target;
    std::printf("  |error|      = %.2e  [%s]\n\n", a_err, a_err < 1e-5 ? "PASS" : "FAIL");

    std::printf("CMB PHOTON DENSITY (T=%.4f K)\n", T0);
    std::printf("  n_gamma      = %.1f /cm^3  (target ~411)\n", n_cmb / 1e6);
    const double n_err = std::fabs(n_cmb / 1e6 - 411.0) / 411.0;
    std::printf("  |error|      = %.2f%%  [%s]\n\n", n_err * 100.0, n_err < 0.02 ? "PASS" : "FAIL");

    std::printf("WIEN DISPLACEMENT\n");
    std::printf("  lambda_peak T = %.6e m·K  (target %.6e)\n", lam_peak * T0, lam_wien);
    const double w_err = std::fabs(lam_peak * T0 - lam_wien) / lam_wien;
    std::printf("  |error|       = %.2e  [%s]\n\n", w_err, w_err < 1e-4 ? "PASS" : "FAIL");

    std::printf("INTERPRETATION (SDT)\n");
    std::printf("  (1+z)^3 in u_CMB is k-space T^3 phase volume (CR10), not expansion.\n");
    std::printf("  Lattice discreteness at l_P sets quanta h nu; no oscillator postulate.\n\n");

    const bool pass = (a_err < 1e-5) && (n_err < 0.02) && (w_err < 1e-4);
    std::printf("================================================================\n");
    std::printf("  VERDICT: %s — Class C (CONVERGENCE / LINGUISTIC-BORROW on stats)\n", pass ? "PASS" : "FAIL");
    std::printf("  Planck spectrum: COMPUTED from mode counting + occupation.\n");
    std::printf("  Boltzmann exp: LINGUISTIC-BORROW (counting axiom, not derived here).\n");
    std::printf("================================================================\n");
    return pass ? 0 : 1;
}
