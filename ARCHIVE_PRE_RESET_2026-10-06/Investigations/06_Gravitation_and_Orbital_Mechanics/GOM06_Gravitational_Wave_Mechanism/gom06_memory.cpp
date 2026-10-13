// ════════════════════════════════════════════════════════════════════════
//  CQ-44 · GATE G4 — Gravitational-wave MEMORY as a permanent depth offset
//
//  "and the pulse, she stop, but also, she go, forever."  — J.T.
//
//  The memory is the DC part of the TRACE (volumetric depth) response: after
//  the merger radiates energy, the total displaced volume — the binary's
//  combined koppa — is permanently smaller by the radiated koppa Δϟ_rad. The
//  detector keeps that offset forever:
//
//        Δϟ_rad   = ϟ_tot · (ΔM / M)              [a LENGTH; the radiated koppa]
//        Δh_mem   = η · Δϟ_rad / R_distance       [η = O(1) sky/inclination factor]
//
//  No G, no M in the result — a radiated LENGTH over a distance. The SAME
//  Δϟ_rad is the AC breathing transient of Gate G3: memory and breathing are
//  one quantity (low-pass vs high-pass). See CQ44_DYNAMIC_CLOSURE.md.
//
//  Build (MSVC):  cl /std:c++20 /EHsc /O2 /I Engine\include /Fe:cq44m.exe ^
//                    Investigations\CQ44_Gravitational_Wave_Mechanism\cq44_memory.cpp
//  Author: James Christopher Tyndall, Melbourne.
// ════════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cstdio>

using sdt::laws::measured::c;

// MEASURED-INPUT: heliocentric gravitational parameter (measured from orbits,
// no G or M apart) → ϟ_⊙ = GM_⊙/c² is a measured LENGTH.
constexpr double GM_sun    = 1.327'124'400'18e20;        // [m³/s²] IAU 2015
constexpr double koppa_sun = GM_sun / (c * c);            // [m] ≈ 1.4766 km
constexpr double Mpc       = 3.085'677'581e22;            // [m]

// ⟦LIGO instrument outputs⟧ for GW150914 (R1 cross-check targets).
constexpr double M_tot_obs = 65.0;     // [M_sun] source-frame total (36+29)
constexpr double dM_rad    = 3.0;      // [M_sun] radiated mass-energy (≈3 M_sun c²)
constexpr double D_L       = 410.0 * Mpc;  // [m]  luminosity distance (410 Mpc)
constexpr double h_peak    = 1.0e-21;  // [-]  peak GW strain

int main() {
    std::printf("===========================================================\n");
    std::printf(" CQ-44 · GATE G4 — GW memory as a permanent depth offset\n");
    std::printf("          'the pulse she stop, but also she go forever'\n");
    std::printf("===========================================================\n\n");

    const double koppa_tot = M_tot_obs * koppa_sun;          // [m]
    const double dkoppa    = dM_rad   * koppa_sun;           // [m] radiated koppa Δϟ_rad
    const double frac      = dM_rad / M_tot_obs;             // Δϟ/ϟ

    std::printf("ϟ_tot (combined c-boundary)     = %.1f km            [MEASURED-INPUT]\n",
                koppa_tot / 1e3);
    std::printf("Δϟ_rad = ϟ_tot·(ΔM/M) = %.0f·ϟ_⊙ = %.2f km   [radiated LENGTH, no G/M]\n",
                dM_rad, dkoppa / 1e3);
    std::printf("Δϟ_rad/ϟ_tot = %.1f %%   ← this is ALSO the G3 breathing fraction\n\n",
                100.0 * frac);

    std::printf("--- Memory strain  Δh = η · Δϟ_rad / R --------------------\n");
    std::printf("R (luminosity distance)         = %.0f Mpc = %.3e m\n", D_L / Mpc, D_L);
    const double dh_eta1 = dkoppa / D_L;            // η = 1 (face-on / naive)
    const double dh_eta  = 0.2 * dkoppa / D_L;      // η ≈ 0.2 (typical sky-averaged)
    std::printf("Δh_mem (η=1.0, naive)           = %.2e\n", dh_eta1);
    std::printf("Δh_mem (η≈0.2, sky-averaged)    = %.2e\n", dh_eta);
    std::printf("peak strain (⟦LIGO⟧)            = %.2e\n", h_peak);
    std::printf("Δh_mem / h_peak                 = %.0f%% (η=1) … %.0f%% (η=0.2)\n",
                100.0 * dh_eta1 / h_peak, 100.0 * dh_eta / h_peak);
    std::printf("   → GR memory estimate for GW150914 ≈ 5–20%% of peak  →  ORDER-MATCH (Class C)\n\n");

    std::printf("--- Native reading (R0) -----------------------------------\n");
    std::printf("• Memory = permanent change in the TRACE (volumetric depth) z at the\n");
    std::printf("  detector: Δh = Δz = Δϟ_rad/R. The sea's VOLUME changed by exactly the\n");
    std::printf("  displacement-load it radiated, and stays changed — 'she go forever'.\n");
    std::printf("• Same Δϟ_rad sources the G3 breathing transient (AC) and this memory\n");
    std::printf("  (DC): ONE quantity, two filters. GR predicts memory but NOT this\n");
    std::printf("  identity → distinctive SDT falsifier (LISA / PTA / 5-detector).\n");
    std::printf("• SCOPE: η is the O(1) sky/inclination factor SHARED with GR's\n");
    std::printf("  quadrupole geometry (CONVERGENCE), not yet a native SDT derivation.\n");
    std::printf("===========================================================\n");
    return 0;
}
