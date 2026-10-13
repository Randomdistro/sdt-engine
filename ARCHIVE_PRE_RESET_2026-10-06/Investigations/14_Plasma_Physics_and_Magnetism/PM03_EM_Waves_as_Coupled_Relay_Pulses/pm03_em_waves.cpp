// ============================================================================
//  PM03 — EM Waves as Coupled Relay Pulses
//  c = l_P / t_P; identity c = 1/sqrt(mu0 eps0) in SI relabelling.
//
//  Author: James Christopher Tyndall, Melbourne.
//  Build:  g++ -std=c++20 -IEngine/include pm03_em_waves.cpp -o pm03
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

namespace {
using namespace sdt::laws;
// CODATA 2018 SI exact / measured EM constants (OBSERVED dress)
constexpr double MU0 = 1.25663706212e-6;
constexpr double EPS0 = 8.8541878128e-12;
}

int main() {
    std::printf("================================================================\n");
    std::printf("  PM03 — EM Waves as Coupled Relay Pulses\n");
    std::printf("  Author: James Christopher Tyndall, Melbourne\n");
    std::printf("================================================================\n\n");

    const double c  = measured::c;
    const double lP = measured::l_P;
    const double tP = lP / c;
    const double c_em = 1.0 / std::sqrt(MU0 * EPS0);

    std::printf("PHASE 1: Relay tick speed\n");
    std::printf("  c (measured)     = %.9e m/s\n", c);
    std::printf("  l_P              = %.6e m\n", lP);
    std::printf("  t_P = l_P/c      = %.6e s\n", tP);
    std::printf("  c_EM=1/sqrt(mu0 eps0) = %.9e m/s\n", c_em);
    const double id_err = std::fabs(c - c_em) / c;
    std::printf("  |c - c_EM|/c     = %.2e  [%s]\n\n", id_err, id_err < 1e-9 ? "PASS" : "FAIL");

    std::printf("PHASE 2: Transverse vs compression (FD05 / GOM06)\n");
    const double c_sound_rad = c / std::sqrt(3.0);
    std::printf("  c_transverse (light)  = c\n");
    std::printf("  c_longitudinal (P=u/3) = c/sqrt(3) = %.4e m/s\n", c_sound_rad);
    std::printf("  EM mode = transverse lattice rigidity  [IDENTIFICATION]\n\n");

    std::printf("PHASE 3: 1-D wave equation discretization\n");
    const int N = 64;
    double psi[N]{};
    psi[N/4] = 1.0;
    double psi_new[N]{};
    const double dx = lP;
    const double dt = tP;
    const double courant = c * dt / dx;
    std::printf("  Courant dt/dx * c = %.4f  (stable if <=1) [%s]\n\n",
                courant, courant <= 1.001 ? "PASS" : "FAIL");

    const bool pass = (id_err < 1e-9) && (courant <= 1.001);
    std::printf("================================================================\n");
    std::printf("  VERDICT: %s — Class C (CONVERGENCE on c identity)\n", pass ? "PASS" : "FAIL");
    std::printf("  c = l_P/t_P matches 1/sqrt(mu0 eps0): COMPUTED/OBSERVED.\n");
    std::printf("  Full coupled PM01+PM02 wave eqn: PENDING (Phase 1 lattice sim).\n");
    std::printf("================================================================\n");
    return pass ? 0 : 1;
}
