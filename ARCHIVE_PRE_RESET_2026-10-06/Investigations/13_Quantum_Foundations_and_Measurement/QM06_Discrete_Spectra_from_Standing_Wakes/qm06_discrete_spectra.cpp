// ============================================================================
//  QM06 — Discrete Spectra from Standing Wakes (Hydrogen ladder)
//  E_n = -Ry/n^2; Balmer H-alpha; zk²=1 closure.
//
//  Author: James Christopher Tyndall, Melbourne.
//  Build:  g++ -std=c++20 -IEngine/include qm06_discrete_spectra.cpp -o qm06
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <initializer_list>

namespace {
using namespace sdt::laws;
constexpr double NM = 1.0e-9;
constexpr double H_ALPHA_NM = 656.279;  // OBSERVED
}

int main() {
    std::printf("================================================================\n");
    std::printf("  QM06 — Discrete Spectra from Standing Wakes\n");
    std::printf("  Author: James Christopher Tyndall, Melbourne\n");
    std::printf("================================================================\n\n");

    const int Z = 1;
    const double Ry = measured::Ry_eV;

    std::printf("RYDBERG LADDER (closure + electropause balance)\n");
    for (int n : {1, 2, 3, 4}) {
        const double E = atomic::ionisation_energy_eV(Z, n);
        const double r = atomic::bohr_radius(Z, n);
        std::printf("  n=%d: E_n = %8.4f eV   r_n = %.4e m\n", n, -E, r);
    }
    const double E1_err = std::fabs(atomic::ionisation_energy_eV(Z, 1) - Ry) / Ry;
    std::printf("  E_1 vs Ry: %.2e rel err  [%s]\n\n", E1_err, E1_err < 1e-6 ? "PASS" : "FAIL");

    std::printf("BALMER H-alpha (n=3 -> 2)\n");
    const double dE = atomic::rydberg_energy_eV(Z, 2, 3);
    const double h  = measured::hbar * 2.0 * std::numbers::pi;
    const double lam_m = h * measured::c / (dE * measured::eV_to_J);
    const double lam_nm = lam_m / NM;
    std::printf("  delta E = %.6f eV\n", dE);
    std::printf("  lambda  = %.4f nm  (target %.4f nm)\n", lam_nm, H_ALPHA_NM);
    const double ha_err = std::fabs(lam_nm - H_ALPHA_NM) / H_ALPHA_NM;
    std::printf("  |error| = %.3f%%  [%s]\n\n", ha_err * 100.0, ha_err < 0.01 ? "PASS" : "FAIL");

    std::printf("STANDING-WAKE CLOSURE (2 pi r = n lambda)\n");
    const double a0 = measured::a_0;
    const double lam1 = h / (measured::m_e * atomic::bohr_velocity(Z, 1));
    const double r1 = atomic::bohr_radius(Z, 1);
    const double closure = 2.0 * std::numbers::pi * r1 / lam1;
    std::printf("  2 pi r_1 / lambda_1 = %.6f  (target 1.0) [%s]\n\n",
                closure, std::fabs(closure - 1.0) < 0.01 ? "PASS" : "FAIL");

    const bool pass = (E1_err < 1e-6) && (ha_err < 0.01) && (std::fabs(closure - 1.0) < 0.01);
    std::printf("================================================================\n");
    std::printf("  VERDICT: %s — Class C (CONVERGENCE)\n", pass ? "PASS" : "FAIL");
    std::printf("  Rydberg/Balmer: COMPUTED from engine atomic namespace.\n");
    std::printf("  Native l-degeneracy / fine structure: OPEN (ANGULAR-DOF).\n");
    std::printf("================================================================\n");
    return pass ? 0 : 1;
}
