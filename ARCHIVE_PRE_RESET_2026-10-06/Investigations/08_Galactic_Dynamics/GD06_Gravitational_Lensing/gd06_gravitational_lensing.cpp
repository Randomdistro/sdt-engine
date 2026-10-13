// ============================================================================
//  GD06 — Gravitational Lensing from Convergence Gradient (Refraction)
//  Deflection: delta = 4 koppa / b  (GOM01 depth engine, T1)
//
//  Author: James Christopher Tyndall, Melbourne.
//  Build:  g++ -std=c++20 -IEngine/include gd06_gravitational_lensing.cpp -o gd06
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

namespace {
constexpr double ARCSEC_PER_RAD = 206264.806247;
using namespace sdt::laws;
}

int main() {
    std::printf("================================================================\n");
    std::printf("  GD06 — Gravitational Lensing (convergence-gradient refraction)\n");
    std::printf("  Author: James Christopher Tyndall, Melbourne\n");
    std::printf("================================================================\n\n");

    const double R_S = measured::R_Sun;
    const double kS  = bridge::k_Sun;
    const double ks  = bridge::koppa_Sun;

    // delta = 4 koppa / b; solar limb: b = R_Sun
    const double delta_rad = 4.0 * ks / R_S;
    const double delta_arcsec = delta_rad * ARCSEC_PER_RAD;

    std::printf("SOLAR LIMB DEFLECTION\n");
    std::printf("  R_Sun        = %.4e m\n", R_S);
    std::printf("  k_Sun        = %.1f\n", kS);
    std::printf("  koppa_Sun    = %.4f m  (= R_Sun/k_Sun^2)\n", ks);
    std::printf("  delta        = 4 koppa / R_Sun\n");
    std::printf("             = %.6e rad\n", delta_rad);
    std::printf("             = %.4f arcsec\n", delta_arcsec);
    std::printf("  Target (VLBI)= 1.7500 arcsec  [OBSERVED]\n");

    const double tgt = 1.7500;
    const double err = std::fabs(delta_arcsec - tgt) / tgt;
    std::printf("  |error|      = %.2f%%  [%s]\n\n", err * 100.0, err < 0.01 ? "PASS" : "FAIL");

    std::printf("REFRACTIVE INDEX (zk² closure)\n");
    const double z_surf = 1.0 / (kS * kS);
    const double n_lim = 1.0 / (1.0 - z_surf);
    std::printf("  z_sun surf   = (v/c)^2 = %.6e\n", z_surf);
    std::printf("  n(R_Sun)     = 1/(1-z)  ~ %.6f  (weak-field)\n\n", n_lim);

    std::printf("GALAXY SCALE (illustrative)\n");
    const double koppa_gal = 1.0e15;  // illustrative cluster koppa scale [m]
    const double b_gal = 1.0e20;      // impact parameter ~ few kpc
    const double delta_gal = 4.0 * koppa_gal / b_gal;
    std::printf("  koppa = %.1e m, b = %.1e m => delta = %.3e rad (~%.1f arcsec)\n",
                koppa_gal, b_gal, delta_gal, delta_gal * ARCSEC_PER_RAD);
    std::printf("  SLACS Einstein radii: OPEN (needs per-lens koppa from v,R)\n\n");

    const bool pass = err < 0.01;
    std::printf("================================================================\n");
    std::printf("  VERDICT: %s — Class C (CONVERGENCE at solar limb)\n", pass ? "PASS" : "FAIL");
    std::printf("  Solar 1.75 arcsec: COMPUTED from koppa, no G/M.\n");
    std::printf("  Cluster/galaxy SLACS fit: PENDING (needs lens k-hierarchy).\n");
    std::printf("================================================================\n");
    return pass ? 0 : 1;
}
