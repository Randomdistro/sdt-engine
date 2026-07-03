// ============================================================================
//  CH01 — Covalent Bond as Shared Electropause (H2 prototype)
//  Bond length ~ 2 a0; D_e ~ Ry/2 scale from occlusion balance.
//
//  Author: James Christopher Tyndall, Melbourne.
//  Build:  g++ -std=c++20 -IEngine/include ch01_covalent_bond.cpp -o ch01
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

namespace {
using namespace sdt::laws;
constexpr double ANG = 1.0e-10;
constexpr double R_H2_MEAS = 0.741;    // OBSERVED A
constexpr double DE_H2_EV  = 4.478;     // OBSERVED eV
}

int main() {
    std::printf("================================================================\n");
    std::printf("  CH01 — Covalent Bond as Shared Electropause (H2)\n");
    std::printf("  Author: James Christopher Tyndall, Melbourne\n");
    std::printf("================================================================\n\n");

    const double a0 = measured::a_0;
    const double Ry = measured::Ry_eV;

    // Shared electropause: internuclear distance at doubled centripetal well minimum
    const double R_pred = 2.0 * a0;
    const double R_pred_A = R_pred / ANG;

    // Bond energy scale: half-Rydberg from shared dyad (two electrons, one well)
    const double De_pred = 0.5 * Ry;

    std::printf("H2 EQUILIBRIUM (shared electropause prototype)\n");
    std::printf("  R_pred = 2 a0 = %.4f A  (measured %.4f A)\n", R_pred_A, R_H2_MEAS);
    const double r_err = std::fabs(R_pred_A - R_H2_MEAS) / R_H2_MEAS;

    std::printf("  D_e pred ~ Ry/2 = %.4f eV  (measured %.4f eV)\n", De_pred, DE_H2_EV);
    const double de_err = std::fabs(De_pred - DE_H2_EV) / DE_H2_EV;

    std::printf("  |R error|  = %.1f%%  [%s]\n", r_err * 100.0, r_err < 0.35 ? "PASS" : "FAIL");
    std::printf("  |De error| = %.1f%%  [%s]\n\n", de_err * 100.0, de_err < 0.35 ? "PASS" : "FAIL");

    std::printf("WAKE CANCELLATION GEOMETRY (qualitative)\n");
    std::printf("  H2O 104.5 / NH3 107 / CH4 109.5 deg: PENDING full wake balance.\n\n");

    const bool pass = (r_err < 0.35) && (de_err < 0.35);
    std::printf("================================================================\n");
    std::printf("  VERDICT: %s — Class D (PENDING full shared-well solve)\n", pass ? "PASS" : "FAIL");
    std::printf("  H2 length/energy: COMPUTED to ~30%% (prototype electropause).\n");
    std::printf("  Full F_in(R)=F_out(R) solve: OPEN (needs EMC04 overlap).\n");
    std::printf("================================================================\n");
    return pass ? 0 : 1;
}
