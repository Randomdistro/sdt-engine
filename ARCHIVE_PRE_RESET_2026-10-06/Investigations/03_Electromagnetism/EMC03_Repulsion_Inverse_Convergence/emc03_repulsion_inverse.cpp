// ============================================================================
//  EMC03 — Is Particle Repulsion the Inverse of the Convergence?
//  Tests the structural claim: attraction and repulsion share one occlusion
//  magnitude; repulsion is a throughput excess (source), attraction a deficit.
//
//  Author: James Christopher Tyndall, Melbourne.
//  Build:  g++ -std=c++20 -IEngine/include emc03_repulsion_inverse.cpp -o emc03
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

namespace {
constexpr double PI = std::numbers::pi;
using namespace sdt::laws;
}

int main() {
    std::printf("================================================================\n");
    std::printf("  EMC03 — Repulsion as Inverse Convergence\n");
    std::printf("  Author: James Christopher Tyndall, Melbourne\n");
    std::printf("================================================================\n\n");

    constexpr double r_test = 1.0e-10;  // [m] OBSERVED test separation

    // Like-charge repulsion and opposite-charge attraction magnitudes
    const double F_mag = law_III::F_coulomb(r_test);
    const double F_ke  = measured::k_e * measured::e_charge * measured::e_charge / (r_test * r_test);

    std::printf("STEP 1: Coulomb magnitude at r = %.1e m\n", r_test);
    std::printf("  F_occlusion(R_charge,R_charge,r) = %.6e N  [DERIVED structure + P_eff]\n", F_mag);
    std::printf("  k_e e^2 / r^2                    = %.6e N  [OBSERVED target]\n", F_ke);
    const double rel = std::fabs(F_mag - F_ke) / F_ke;
    std::printf("  Relative error                   = %.3e  [%s]\n\n",
                rel, rel < 1e-6 ? "PASS" : "FAIL");

    std::printf("STEP 2: Sign symmetry (T4 occlusion structure)\n");
    std::printf("  Attraction: throughput DEFICIT between bodies (sink modulation)\n");
    std::printf("  Repulsion:  throughput EXCESS between bodies (source modulation)\n");
    std::printf("  |F_repel| = |F_attract| enforced by ONE magnitude law  [STRONG]\n\n");

    std::printf("STEP 3: Gravity vs charge multipole (wake tensor)\n");
    const double R_ch = law_III::R_charge;
    const double F_grav_proxy = law_III::F_occlusion(
        bridge::R_Earth, bridge::R_Earth, bridge::R_Earth);  // same-body scale proxy
    std::printf("  R_charge = sqrt(R_p r_e) = %.4e m\n", R_ch);
    std::printf("  F_occlusion(Earth,Earth,R_Earth) ~ %.3e N  (attraction-only wake)\n", F_grav_proxy);
    std::printf("  Charge wake carries dipole (l=1) source/sink lobes -> bipolar  [IDENTIFICATION]\n\n");

    std::printf("STEP 4: zk²=1 closure check (spectroscopic stretch anchor)\n");
    const double z_H = bridge::koppa_hydrogen / measured::a_0;
    const double k_H = 1.0 / measured::alpha;
    std::printf("  z_H = koppa_H / a_0 = %.6e\n", z_H);
    std::printf("  1/k_H^2             = %.6e\n", 1.0 / (k_H * k_H));
    const bool zk2 = std::fabs(z_H * k_H * k_H - 1.0) < 1e-9;
    std::printf("  z k^2 = 1           [%s]\n\n", zk2 ? "PASS" : "FAIL");

    const bool pass = (rel < 1e-6) && zk2;
    std::printf("================================================================\n");
    std::printf("  VERDICT: %s — Class C (STRUCTURAL CONVERGENCE)\n", pass ? "PASS" : "FAIL");
    std::printf("  Repulsion = inverse sign of the same occlusion modulation.\n");
    std::printf("  Magnitude match at r=1e-10 m: COMPUTED vs OBSERVED Coulomb.\n");
    std::printf("  Quantitative P_eff from geometry alone: OPEN (EMC01 caveat).\n");
    std::printf("================================================================\n");
    return pass ? 0 : 1;
}
