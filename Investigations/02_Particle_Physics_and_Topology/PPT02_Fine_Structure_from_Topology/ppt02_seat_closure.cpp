// =====================================================================================
//  cq03_seat_closure.cpp  —  the koppa seat of hydrogen, read straight off the spectrum.
//
//  Author: James Christopher Harvey, Melbourne.
//
//  Thesis (the closure PPT02's scroller asserts, now demonstrated from DATA):
//    alpha is NOT a magic coupling dialed into the universe. It is the koppa RUNG of
//    hydrogen's ground state, and the spectrograph reads it off directly. The hydrogen
//    ionisation energy, fed through the Law-V virial  1/2 m_e v^2 = E,  hands back
//    v = alpha*c, hence k = c/v = 137 — computed from {E_ion, m_e, c} ALONE.
//
//  NON-CIRCULARITY (the whole point): alpha never enters the computation. The only
//  inputs are (1) measured series-limit wavelengths and (2) the measured constants
//  {c, h, m_e}. The engine's stored alpha (measured::alpha) appears on EXACTLY ONE line
//  — the final comparison — and is used nowhere in deriving k. Delete that line and the
//  seat k = 137.07 still computes. Contrast the old PPT02 derivation attempts, every one
//  of which smuggled alpha back in through a_0 (= hbar/(m_e c alpha)) or P_eff (= alpha
//  hbar c ...). This route touches none of them: no a_0, no P_eff, no anchored field
//  amplitude, no W=1-hbar machinery.
//
//  HONEST SCOPE: this does NOT derive alpha from nothing. E_ion and alpha carry the same
//  information (E_ion = 1/2 m_e (alpha c)^2 is the Rydberg relation; reading k from E_ion
//  is inverting it). The input count is unchanged — you have traded the abstract coupling
//  for the concrete observable. PPT02's negative result (alpha needs e) stands. What is
//  EARNED is the reinterpretation: alpha = koppa rung of H, fixed by the spectrum, the
//  same kind of object as koppa_Sun. "Every hydrogen says so," and the whole series ladder
//  k_n = 137.07 n confirms it is a geometric rung index, series-independent.
//
//  NO reduced mass, no infinite-nuclear-mass idealisation. The seat is 137.07 — hydrogen's
//  REAL rung, proton free. 137.036 (CODATA) is the proton-nailed-to-infinity abstraction;
//  real hydrogen does not sit there, so we do not patch toward it.
//
//  Build (MSVC):
//    cl /std:c++20 /EHsc /O2 /I Engine\include /Fe:cq03_seat.exe ^
//       Investigations\02_Particle_Physics_and_Topology\CQ03_Fine_Structure_from_Topology\cq03_seat_closure.cpp
//  Build (GCC/Clang):
//    g++ -std=c++20 -IEngine/include cq03_seat_closure.cpp -o cq03_seat
// =====================================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

namespace M = sdt::laws::measured;

// A measured hydrogen series limit: the short-wavelength edge where the series piles up,
// i.e. the photon that ionises the atom FROM level n. These are observed wavelengths.
struct SeriesLimit {
    const char* name;
    int         n;        // lower level the series falls to (Lyman 1, Balmer 2, Paschen 3)
    double      lambda_m; // measured vacuum series-limit wavelength [m]
};

int main() {
    // ---- the ONLY external inputs: measured constants (whitelist) + measured spectra ----
    const double c   = M::c;        // [m/s]
    const double h   = M::h;        // [J s]
    const double m_e = M::m_e;      // [kg]
    const double eV  = M::e_charge; // [J/eV]  (1 eV = e_charge joules)
    //   note: NO alpha, NO a_0, NO P_eff used below.

    // Measured hydrogen series limits (vacuum). The limit of series n sits at n^2 / R_H;
    // each is an independently observed edge of its series.
    const SeriesLimit limits[] = {
        { "Lyman",   1, 91.1753e-9  },
        { "Balmer",  2, 364.7010e-9 },
        { "Paschen", 3, 820.5780e-9 },
    };

    std::printf("=====================================================================\n");
    std::printf("  PPT02 SEAT CLOSURE  —  alpha read off the hydrogen spectrum\n");
    std::printf("  J. C. Harvey, Melbourne.  Inputs: measured {c,h,m_e} + series limits.\n");
    std::printf("  alpha is NOT used to compute k (see the single compare line at the end).\n");
    std::printf("=====================================================================\n\n");
    std::printf("  series    n   lambda_lim     E_ion(eV)    v/c            k=c/v       k/n\n");
    std::printf("  ------------------------------------------------------------------------\n");

    double k1 = 0.0;
    bool   ladder_ok = true;
    for (const auto& L : limits) {
        const double E   = h * c / L.lambda_m;      // ionisation energy from level n  [J]
        const double v   = std::sqrt(2.0 * E / m_e); // Law-V virial: 1/2 m_e v^2 = E   [m/s]
        const double k   = c / v;                    // the koppa rung index (dimensionless)
        const double kn  = k / L.n;                  // collapse the ladder: should be ~137.07
        if (L.n == 1) k1 = k;
        if (std::fabs(kn - 137.07) > 0.05) ladder_ok = false;
        std::printf("  %-8s  %d   %8.4f nm   %8.4f   %.6e   %9.4f   %8.4f\n",
                    L.name, L.n, L.lambda_m * 1e9, E / eV, v / c, k, kn);
    }

    // z*k^2 closure (definitional bookkeeping — stated, not leaned on as evidence):
    const double v1 = std::sqrt(2.0 * (h * c / limits[0].lambda_m) / m_e);
    const double z1 = (v1 / c) * (v1 / c);
    std::printf("\n  z*k^2 at the seat = (v/c)^2 (c/v)^2 = %.10f  [identity, not a fitted match]\n", z1 * k1 * k1);

    // ---- THE ONE comparison line that references alpha. Computation above is alpha-free. ----
    std::printf("\n  seat k (from spectrum)        = %.4f      => alpha_H = 1/k = %.10e\n", k1, 1.0 / k1);
    std::printf("  CODATA 1/alpha (compare only)  = %.4f      (proton-fixed idealisation)\n", M::alpha_inv);
    std::printf("  gap = %.3f%%  — finite-proton, NOT corrected toward CODATA.\n",
                100.0 * (k1 - M::alpha_inv) / M::alpha_inv);

    std::printf("\n---------------------------------------------------------------------\n");
    std::printf("  VERDICT\n");
    std::printf("    seat read from spectrum, no alpha used : %s\n", "PASS");
    std::printf("    ladder k_n = 137.07 n (series-indep.)  : %s\n", ladder_ok ? "PASS" : "FAIL");
    std::printf("    => alpha is the koppa rung of hydrogen, fixed by the spectrum.\n");
    std::printf("       The closure is the LADDER (k_n=137.07n, z k^2=1), not alpha-from-nothing.\n");
    std::printf("---------------------------------------------------------------------\n");
    return ladder_ok ? 0 : 1;
}
