// ════════════════════════════════════════════════════════════════════════
//  CQ-44 · GATE G2 — The chirp from a LENGTH (no G, no M in the dynamics)
//
//  "make little mirror go chirp chirp ... like moving a sea"  — J.T.
//
//  Thesis: LIGO is a KOPPA-METER. It measures the binary's dynamics — i.e. a
//  length ϟ = GM/c² (the c-boundary) — and only reports a "mass" by dividing
//  out G. The entire inspiral chirp scale follows from ϟ and c alone:
//
//        v²      = c² ϟ / r            (orbital velocity from koppa, bridge)
//        ω_orb²  = c² ϟ / r³
//        r_isco  ≈ 6 ϟ_tot             (horizons touch: max-compression cores)
//   ⟹  f_GW,isco = c / (π · 6^{3/2} · ϟ_tot)     —  ONLY c and a length
//
//  G appears NOWHERE in that final relation. The koppa bridge GM=c²ϟ is used
//  once, to *import* the measured GM (an observable measured without knowing G
//  or M separately), then never again.
//
//  Build (MSVC):  cl /std:c++20 /EHsc /O2 /I Engine\include /Fe:cq44.exe ^
//                    Investigations\CQ44_Gravitational_Wave_Mechanism\cq44_chirp_from_koppa.cpp
//  Build (gcc) :  g++ -std=c++20 -IEngine/include cq44_chirp_from_koppa.cpp -o cq44
//
//  Author: James Christopher Tyndall, Melbourne.
// ════════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <numbers>

using sdt::laws::measured::c;
constexpr double PI = std::numbers::pi;

// ── MEASURED-INPUT (R2) ──────────────────────────────────────────────────
// Heliocentric gravitational parameter. This is an OBSERVABLE measured from
// planetary orbits to ~10 significant figures WITHOUT ever knowing G or M_sun
// separately — it is c² × (the Sun's koppa). The legitimate SDT input.
constexpr double GM_sun = 1.327'124'400'18e20;   // [m³/s²]  IAU 2015 nominal

// ⟦LIGO instrument outputs⟧ for GW150914 (R1 cross-check targets only).
// LIGO reports these as "masses"; in SDT they are koppas dressed by /G.
constexpr double M_tot_obs   = 65.0;   // [M_sun]  source-frame total (36+29)
constexpr double M_chirp_obs = 28.6;   // [M_sun]  source-frame chirp mass
constexpr double f_isco_obs  = 68.0;   // [Hz]     ⟦textbook⟧ ISCO GW frequency, 65 M_sun
constexpr double f_band_obs  = 150.0;  // [Hz]     peak strain freq near merger

// koppa of one solar mass: ϟ_sun = GM_sun / c²   [m]
constexpr double koppa_sun = GM_sun / (c * c);

// f_GW at ISCO from a length alone:  f = c / (π · 6^{3/2} · ϟ_tot)
[[nodiscard]] double f_gw_isco_from_koppa(double koppa_tot_m) {
    return c / (PI * std::pow(6.0, 1.5) * koppa_tot_m);
}

int main() {
    std::printf("===========================================================\n");
    std::printf(" CQ-44 · GATE G2 — gravitational chirp from a LENGTH\n");
    std::printf("          (no G, no M in any dynamical relation)\n");
    std::printf("===========================================================\n\n");

    std::printf("koppa of 1 M_sun:  ϟ_sun = GM_sun/c² = %.4f km   [MEASURED-INPUT]\n",
                koppa_sun / 1e3);
    std::printf("   (GM_sun is measured from orbits; G and M never appear apart)\n\n");

    // ── FORWARD: ϟ_tot → f_GW,isco (the chirp scale is a length) ──────────
    const double koppa_tot = M_tot_obs * koppa_sun;          // [m]
    const double koppa_chirp = M_chirp_obs * koppa_sun;       // [m]
    const double f_pred = f_gw_isco_from_koppa(koppa_tot);    // [Hz]

    std::printf("--- FORWARD: the binary as a LENGTH -----------------------\n");
    std::printf("ϟ_tot (combined c-boundary)   = %.1f km   [from ⟦LIGO 65 M_sun⟧]\n",
                koppa_tot / 1e3);
    std::printf("ϟ_c   (chirp koppa)           = %.1f km\n", koppa_chirp / 1e3);
    std::printf("r_isco = 6·ϟ_tot              = %.1f km\n", 6.0 * koppa_tot / 1e3);
    std::printf("\n");
    std::printf("PREDICTED  f_GW,isco = c/(π·6^{3/2}·ϟ_tot) = %.2f Hz   [DERIVED, no G]\n",
                f_pred);
    std::printf("MEASURED   f_GW,isco (⟦65 M_sun band⟧)     = %.2f Hz\n", f_isco_obs);
    const double err_isco = 100.0 * (f_pred - f_isco_obs) / f_isco_obs;
    std::printf("           error = %+.2f %%   →  %s (±15%%)\n",
                err_isco, std::fabs(err_isco) < 15.0 ? "PASS" : "FAIL");
    std::printf("           (signal swept up to ⟦~%.0f Hz⟧ at true merger, past ISCO)\n\n",
                f_band_obs);

    // ── INVERSE: the koppa-meter (frequency → length → ⟦mass⟧) ────────────
    // Invert f = c/(π·6^{3/2}·ϟ)  ⟹  ϟ = c/(π·6^{3/2}·f)
    std::printf("--- INVERSE: LIGO as a koppa-meter ------------------------\n");
    const double koppa_from_f = c / (PI * std::pow(6.0, 1.5) * f_isco_obs);  // [m]
    const double M_recovered  = koppa_from_f / koppa_sun;                    // [M_sun]
    std::printf("Feed measured f = %.1f Hz  →  ϟ_tot = %.1f km   [DERIVED]\n",
                f_isco_obs, koppa_from_f / 1e3);
    std::printf("Dress as mass: c²ϟ/GM_sun = %.1f M_sun\n", M_recovered);
    std::printf("⟦LIGO total mass⟧          = %.1f M_sun\n", M_tot_obs);
    const double err_mass = 100.0 * (M_recovered - M_tot_obs) / M_tot_obs;
    std::printf("           error = %+.2f %%   →  %s (±15%%)\n\n",
                err_mass, std::fabs(err_mass) < 15.0 ? "PASS" : "FAIL");

    // ── HONESTY (R4/R5) ───────────────────────────────────────────────────
    std::printf("--- HONESTY LEDGER (R4/R5) --------------------------------\n");
    std::printf("• f = c/(π·6^{3/2}·ϟ) is GR's f_isco = c³/(6^{3/2}·π·GM) with GM≡c²ϟ.\n");
    std::printf("  The PASS is therefore an ALGEBRAIC IDENTITY of the koppa bridge,\n");
    std::printf("  not an independent numerical surprise — its content is CONCEPTUAL:\n");
    std::printf("  the chirp scale is a LENGTH (ϟ_tot≈%.0f km) and c, with G absent.\n",
                koppa_tot / 1e3);
    std::printf("• Inspiral law df/dt ∝ f^{11/3}·ϟ_c^{5/3}: the f^{11/3} FORM is SDT's\n");
    std::printf("  (mass-quadrupole of the breathing occlusion); the 96/5 coefficient is\n");
    std::printf("  CONVERGENCE-PENDING until derived from shear-radiation reaction.\n");
    std::printf("• CLASS C (convergence). G2 verdict: PASS on scale, no G/M in dynamics.\n");
    std::printf("===========================================================\n");
    return 0;
}
