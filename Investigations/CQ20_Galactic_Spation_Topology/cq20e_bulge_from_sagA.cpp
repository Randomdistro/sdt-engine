// =============================================================================
// CQ20e — Milky Way Galactic Topology: Full Orbital Map
//
// CORE (Sag A* + NSC): settled.  IRS9 defines the surface.
//   R_core   = 5.25 pc = 1.620e17 m
//   v_core   = 370 km/s
//   Ϟ_core   = v²R/c² = 2.466e11 m
//   k_core   = c/v = 810
//
// From the core surface outward, step through every known orbital
// path, computing SDT quantities at each: Ϟ, k, z, v, zk² = 1.
//
// ZONES:
//   Zone 0: Core interior (0 → 5.25 pc) — IRS9 boundary
//   Zone 1: Central Molecular Zone (5.25 → 200 pc)
//   Zone 2: Inner bulge (200 pc → 1 kpc)
//   Zone 3: Bulge/bar (1 kpc → 3.5 kpc)
//   Zone 4: Transition (3.5 → 5 kpc)
//   Zone 5: Disk (5 → 25 kpc)
//
// REGIMES:
//   A: Core-dominated (Keplerian from core, v ∝ 1/√r)
//   B: Bulge-rising (enclosed engines increasing faster than r)
//   C: Flat disk (interior + exterior occlusion balance)
//   D: Declining edge (exterior occlusion falls off)
//
// No G. No M in kg. Only v, R, c, Ϟ, k, z.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <sdt/laws.hpp>

using namespace sdt::laws;
using namespace sdt::laws::measured;

static constexpr double kpc_m = 3.085677581e19;
static constexpr double pc_m  = 3.085677581e16;
static constexpr double AU_m  = 1.495978707e11;

int main() {
    printf("###################################################################\n");
    printf("###################################################################\n");
    printf("##                                                               ##\n");
    printf("##   CQ20e: MILKY WAY GALACTIC TOPOLOGY                         ##\n");
    printf("##   Full Orbital Map — SDT Framework                            ##\n");
    printf("##   James Tyndall, Melbourne                                    ##\n");
    printf("##                                                               ##\n");
    printf("##   Core: IRS9 @ 5.25 pc, v=370 km/s, Koppa=2.466e11 m        ##\n");
    printf("##   No G. No M. Only v, R, c, Koppa, k, z.                     ##\n");
    printf("##                                                               ##\n");
    printf("###################################################################\n");
    printf("###################################################################\n\n");

    // =================================================================
    // CORE DEFINITION
    // =================================================================
    double R_core = 5.25 * pc_m;       // 1.620e17 m
    double v_core = 370.0e3;           // 370 km/s
    double K_core = v_core * v_core * R_core / (c * c);
    double k_core = c / v_core;
    double z_core = 1.0 / (k_core * k_core);

    printf("=================================================================\n");
    printf("   CORE DEFINITION (Sag A* + NSC = single engine)\n");
    printf("=================================================================\n\n");
    printf("   Calibration:     IRS9 (non-S star, apoapsis = 5.25 pc)\n");
    printf("   v_IRS9:          370 +/- 1.2 km/s (3D, measured)\n");
    printf("   R_core:          5.25 pc = %.6e m\n", R_core);
    printf("   Enclosed engines: ~45 million suns\n\n");
    printf("   Koppa_core:      v²R/c² = %.6e m\n", K_core);
    printf("   k_core:          c/v    = %.4f\n", k_core);
    printf("   z_core:          1/k²   = %.6e\n", z_core);
    printf("   zk²:             %.12f\n", z_core * k_core * k_core);
    printf("   R_S(core):       2*Koppa = %.6e m = %.4f AU\n\n",
           2.0*K_core, 2.0*K_core/AU_m);

    // Sag A* uncollapsed (for reference)
    double R_sagA = std::cbrt(3.0 * 4.0e6 * (4.0/3.0)*M_PI
                   * R_Sun*R_Sun*R_Sun / (4.0*M_PI));
    printf("   Sag A* uncollapsed: R = %.4e m = %.4f AU\n", R_sagA, R_sagA/AU_m);
    printf("   Core is %.0f× larger than Sag A* uncollapsed.\n",
           R_core / R_sagA);
    printf("   (Core contains Sag A* + ~45M suns of NSC)\n\n");

    // =================================================================
    // FULL ORBITAL MAP
    //
    // Every known orbital path from the core surface outward.
    // At each radius R:
    //   Ϟ_obs = v²R/c²        (from observed v at R)
    //   k     = c/v
    //   z     = 1/k²
    //   Ϟ_kep = Ϟ_core × 1    (Keplerian from core alone)
    //   v_kep = c√(Ϟ_core/R)  (what core alone would give)
    //   delta = v_obs - v_kep  (excess = additional engines)
    //   Ϟ_add = Ϟ_obs - Ϟ_core (additional Koppa from enclosed)
    //
    // ZONE classification:
    //   0 = Core interior
    //   1 = CMZ (5.25 - 200 pc)
    //   2 = Inner bulge (200 - 1000 pc)
    //   3 = Bulge/bar (1 - 3.5 kpc)
    //   4 = Transition (3.5 - 5 kpc)
    //   5 = Disk (5 - 25 kpc)
    //
    // REGIME classification:
    //   A = Core-dominated (v_obs ≈ v_kep, Ϟ_add ≈ 0)
    //   B = Bulge-rising (v_obs > v_kep, Ϟ_add growing)
    //   C = Flat (v_obs ≈ constant)
    //   D = Declining (v_obs falling)
    // =================================================================

    struct OrbitalPath {
        const char* name;       // Object or measurement
        const char* source;     // Data source
        double r_pc;            // Distance from Sag A* [pc]
        double v_kms;           // Observed velocity [km/s]
        int    zone;            // Zone number
    };

    OrbitalPath paths[] = {
        // ZONE 0: Core interior (for reference — we don't Keplerian here)
        // ZONE 1: CMZ (5.25 - 200 pc)
        {"IRS9 (core surf)",    "ALMA/HST",       5.25,   370,  1},
        {"Arches cluster",      "Stolte+2008",   26.0,    232,  1},
        {"Quintuplet cluster",  "Stolte+2014",   30.0,    167,  1},
        {"Sgr B2 complex",      "Sofue 2013",   120.0,    130,  1},
        {"CMZ outer",           "Sofue 2013",   200.0,    140,  1},

        // ZONE 2: Inner bulge (200 - 1000 pc)
        {"Inner bulge 300pc",   "Sofue 2013",   300.0,    160,  2},
        {"Inner bulge 500pc",   "Sofue 2013",   500.0,    175,  2},
        {"Bulge 700pc",         "Sofue 2013",   700.0,    190,  2},
        {"Bulge 1.0kpc",        "Sofue 2013",  1000.0,    210,  2},

        // ZONE 3: Bulge/bar (1 - 3.5 kpc)
        {"Bulge 1.5kpc",        "Sofue 2013",  1500.0,    225,  3},
        {"Bulge 2.0kpc",        "Sofue 2013",  2000.0,    230,  3},
        {"Bar 2.5kpc",          "Sofue 2013",  2500.0,    235,  3},
        {"Bar 3.0kpc",          "Sofue 2013",  3000.0,    235,  3},
        {"Bar terminus",        "Sofue 2013",  3500.0,    220,  3},

        // ZONE 4: Transition (3.5 - 5 kpc)
        {"Arm root 4.0kpc",     "Sofue 2013",  4000.0,    220,  4},
        {"Transition 4.5kpc",   "Sofue 2013",  4500.0,    222,  4},

        // ZONE 5: Disk (5 - 25 kpc)
        {"Disk 5.0kpc",         "Eilers 2019", 5000.0,    228,  5},
        {"Disk 6.0kpc",         "Eilers 2019", 6000.0,    229,  5},
        {"Disk 7.0kpc",         "Eilers 2019", 7000.0,    231,  5},
        {"Sun (R0=8.0kpc)",     "Eilers 2019", 8000.0,    229,  5},
        {"Disk 9.0kpc",         "Eilers 2019", 9000.0,    230,  5},
        {"Disk 10.0kpc",        "Eilers 2019",10000.0,    232,  5},
        {"Disk 11.0kpc",        "Eilers 2019",11000.0,    230,  5},
        {"Disk 12.0kpc",        "Eilers 2019",12000.0,    228,  5},
        {"Disk 14.0kpc",        "Eilers 2019",14000.0,    225,  5},
        {"Disk 16.0kpc",        "Huang 2016", 16000.0,    218,  5},
        {"Disk 18.0kpc",        "Huang 2016", 18000.0,    210,  5},
        {"Disk 20.0kpc",        "Huang 2016", 20000.0,    200,  5},
        {"Disk 25.0kpc",        "Huang 2016", 25000.0,    185,  5},
    };
    int npaths = sizeof(paths) / sizeof(paths[0]);

    const char* zone_names[] = {
        "Core", "CMZ", "Inner bulge", "Bulge/bar", "Transition", "Disk"
    };

    // =================================================================
    // MAIN TABLE
    // =================================================================
    printf("=================================================================\n");
    printf("   FULL ORBITAL MAP: SDT QUANTITIES AT EACH PATH\n");
    printf("=================================================================\n\n");

    printf("   %-24s %4s %8s %8s %12s %10s %10s %8s %8s %12s %6s\n",
           "Path", "Zone", "r [pc]", "v [km/s]",
           "Koppa [m]", "k", "z",
           "v_kep", "dv", "K_add [m]", "Regime");
    printf("   %-24s %4s %8s %8s %12s %10s %10s %8s %8s %12s %6s\n",
           "----", "----", "------", "-------",
           "---------", "--", "--",
           "-----", "---", "---------", "------");

    int prev_zone = -1;

    for (int i = 0; i < npaths; i++) {
        auto& p = paths[i];
        double R = p.r_pc * pc_m;
        double v = p.v_kms * 1e3;

        // SDT quantities
        double K_obs = v * v * R / (c * c);
        double k_val = c / v;
        double z_val = 1.0 / (k_val * k_val);

        // Keplerian from core alone
        double v_kep = c * std::sqrt(K_core / R);
        double dv = v - v_kep;

        // Additional Koppa above core
        double K_add = K_obs - K_core;

        // Regime classification
        const char* regime;
        double ratio = v / v_kep;
        if (ratio < 1.15 && ratio > 0.85)
            regime = "A";  // core-dominated
        else if (dv > 0 && p.v_kms > 200 && p.zone <= 3)
            regime = "B";  // bulge-rising
        else if (p.zone >= 4 && std::abs(dv) < 30e3 && p.v_kms > 200)
            regime = "C";  // flat
        else if (p.zone == 5 && p.v_kms < 215)
            regime = "D";  // declining
        else if (dv < 0)
            regime = "A-";  // sub-Keplerian (core over-predicts)
        else
            regime = "B+";  // excess above core

        // Zone separator
        if (p.zone != prev_zone) {
            printf("   --- ZONE %d: %-12s ------------------------------------"
                   "-----------------------------------------------\n",
                   p.zone, zone_names[p.zone]);
            prev_zone = p.zone;
        }

        printf("   %-24s %4d %8.1f %8.0f %12.4e %10.2f %10.4e %8.1f %8.1f %12.4e %6s\n",
               p.name, p.zone, p.r_pc, p.v_kms,
               K_obs, k_val, z_val,
               v_kep/1e3, dv/1e3, K_add, regime);
    }

    // =================================================================
    // REGIME ANALYSIS
    // =================================================================
    printf("\n=================================================================\n");
    printf("   REGIME ANALYSIS\n");
    printf("=================================================================\n\n");

    printf("   REGIME A (Core-dominated): v_obs ≈ v_kep from core alone\n");
    printf("   -------------------------------------------------------\n");
    for (int i = 0; i < npaths; i++) {
        double R = paths[i].r_pc * pc_m;
        double v = paths[i].v_kms * 1e3;
        double v_kep = c * std::sqrt(K_core / R);
        double ratio = v / v_kep;
        if (ratio > 0.85 && ratio < 1.15) {
            printf("   %-24s  v_obs/v_kep = %.4f  (%.0f / %.0f km/s)\n",
                   paths[i].name, ratio, v/1e3, v_kep/1e3);
        }
    }

    printf("\n   REGIME B (Bulge-rising): v_obs >> v_kep, bulge adds Koppa\n");
    printf("   ---------------------------------------------------------\n");
    for (int i = 0; i < npaths; i++) {
        double R = paths[i].r_pc * pc_m;
        double v = paths[i].v_kms * 1e3;
        double v_kep = c * std::sqrt(K_core / R);
        double K_obs = v * v * R / (c * c);
        double K_add = K_obs - K_core;
        if (v/v_kep >= 1.15 && paths[i].zone <= 4) {
            printf("   %-24s  v_obs/v_kep = %.2f  K_add = %.4e m (%.1fx core)\n",
                   paths[i].name, v/v_kep, K_add, K_add/K_core);
        }
    }

    printf("\n   REGIME C/D (Disk flat/declining): v ≈ 200-232 km/s\n");
    printf("   ---------------------------------------------------\n");
    for (int i = 0; i < npaths; i++) {
        if (paths[i].zone == 5) {
            double R = paths[i].r_pc * pc_m;
            double v = paths[i].v_kms * 1e3;
            double K_obs = v * v * R / (c * c);
            printf("   %-24s  v = %3.0f km/s  K_obs = %.4e m (%.1fx core)\n",
                   paths[i].name, paths[i].v_kms, K_obs, K_obs/K_core);
        }
    }

    // =================================================================
    // KOPPA GROWTH PROFILE
    // =================================================================
    printf("\n=================================================================\n");
    printf("   KOPPA GROWTH PROFILE: K_obs / K_core at each radius\n");
    printf("=================================================================\n\n");

    printf("   The core provides K_core = %.4e m.\n", K_core);
    printf("   Everything above this is ADDITIONAL enclosed engines.\n\n");

    printf("   %-24s %8s %12s %8s %12s\n",
           "Path", "r [pc]", "K_obs [m]", "K/K_core", "K_add [m]");
    printf("   %-24s %8s %12s %8s %12s\n",
           "----", "------", "---------", "--------", "---------");

    for (int i = 0; i < npaths; i++) {
        double R = paths[i].r_pc * pc_m;
        double v = paths[i].v_kms * 1e3;
        double K_obs = v * v * R / (c * c);
        printf("   %-24s %8.0f %12.4e %8.2f %12.4e\n",
               paths[i].name, paths[i].r_pc, K_obs,
               K_obs/K_core, K_obs - K_core);
    }

    // =================================================================
    // CRITICAL RADII
    // =================================================================
    printf("\n=================================================================\n");
    printf("   CRITICAL RADII\n");
    printf("=================================================================\n\n");

    // Core c-boundary
    printf("   Koppa_core (c-boundary): %.4e m = %.4f AU\n", K_core, K_core/AU_m);
    printf("     (where v_orb = c around the core)\n\n");

    // Core Schwarzschild
    double rS_core = 2.0 * K_core;
    printf("   R_S (core):              %.4e m = %.4f AU\n", rS_core, rS_core/AU_m);
    printf("     (where v_orb = c/sqrt(2) = 0.707c)\n\n");

    // Core surface
    printf("   R_core (surface):        %.4e m = %.2f pc\n", R_core, R_core/pc_m);
    printf("     IRS9 apoapsis, v = 370 km/s, k = %.1f\n\n", k_core);

    // v=2piR radius for core
    double r_vC = std::cbrt(c*c*K_core / (4.0*M_PI*M_PI));
    printf("   v=2piR radius:           %.4e m = %.4f AU\n", r_vC, r_vC/AU_m);
    printf("     (inside core, v = %.2fc)\n\n",
           c*std::sqrt(K_core/r_vC)/c);

    // Where does core Keplerian drop below observed?
    printf("   Core Keplerian breakdown:\n");
    printf("     At core surface: v_kep = v_obs = 370 km/s (by definition)\n");
    for (int i = 1; i < npaths; i++) {
        double R = paths[i].r_pc * pc_m;
        double v_kep = c * std::sqrt(K_core / R);
        double v = paths[i].v_kms * 1e3;
        if (v > v_kep * 1.3 && i > 0) {
            printf("     At %.0f pc: v_kep = %.0f km/s, v_obs = %.0f km/s "
                   "(core under-predicts by %.0f%%)\n",
                   paths[i].r_pc, v_kep/1e3, v/1e3,
                   100.0*(v-v_kep)/v_kep);
            printf("     => Regime B begins. Bulge engines dominate.\n");
            break;
        }
    }

    // =================================================================
    // ZONE BOUNDARY SUMMARY
    // =================================================================
    printf("\n=================================================================\n");
    printf("   ZONE BOUNDARY KOPPA VALUES\n");
    printf("=================================================================\n\n");

    double boundaries[] = {5.25, 200, 1000, 3500, 5000, 25000};
    const char* bnd_names[] = {"Core surface", "CMZ→Bulge", "InBulge→Bar",
                               "Bar→Trans", "Trans→Disk", "Disk edge"};
    int nbnds = 6;

    // Find observed v at each boundary (closest path)
    for (int b = 0; b < nbnds; b++) {
        double r_bnd = boundaries[b];
        double best_dist = 1e30;
        int best_idx = 0;
        for (int i = 0; i < npaths; i++) {
            double d = std::abs(paths[i].r_pc - r_bnd);
            if (d < best_dist) { best_dist = d; best_idx = i; }
        }
        double R = paths[best_idx].r_pc * pc_m;
        double v = paths[best_idx].v_kms * 1e3;
        double K = v * v * R / (c * c);
        double k = c / v;

        printf("   %-16s (%.0f pc):  Koppa = %.4e m,  k = %.1f,  v = %.0f km/s\n",
               bnd_names[b], paths[best_idx].r_pc, K, k, v/1e3);
    }

    printf("\n   Each zone boundary's Koppa is the FLOOR for the next zone.\n");
    printf("   The bulge adds engines → Koppa grows.\n");
    printf("   The disk maintains Koppa → v stays flat.\n");
    printf("   Beyond 20 kpc, Koppa growth slows → v declines.\n");

    return 0;
}
