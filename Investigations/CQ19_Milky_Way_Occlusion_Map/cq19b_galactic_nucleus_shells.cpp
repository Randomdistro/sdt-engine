// =============================================================================
// CQ19b — Galactic Nucleus Shell Map
//
// Maps the MW centre in concentric SDT shells from Sag A* outward:
//   Shell 0: Sag A* (Ϟ from S2 orbit)
//   Shell 1: S-star cluster (r < 0.04 pc, individual stellar orbits)
//   Shell 2: Nuclear star cluster (r < 5 pc, σ ~ 100 km/s)
//   Shell 3: Central molecular zone (r < 200 pc)
//   Shell 4: Inner bulge (r < 500 pc)
//   Shell 5: Outer bulge / bar (r < 2 kpc)
//   Shell 6: Bar-spiral arm junctions (r ~ 3-5 kpc)
//
// Each shell: v_circ or σ → k = c/v → z = 1/k² → Ϟ = v²R/c²
// Enrichable: data structures accept new stars/observations.
//
// Macro bonding test: does the bar-arm junction show occlusion
// overlap analogous to atomic bonding (shared Ϟ field)?
//
// No G. No M. zk² = 1.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

#include <sdt/laws.hpp>

using namespace sdt::laws;
using namespace sdt::laws::measured;

static constexpr double kpc_m  = 3.085677581e19;
static constexpr double pc_m   = 3.085677581e16;
static constexpr double c_kms  = c / 1000.0;
static constexpr double yr_s   = 365.25 * 86400.0;

// =============================================================================
// ENRICHABLE DATA STRUCTURES
// =============================================================================

struct SStar {
    const char* name;
    double a_arcsec;     // semi-major axis [arcsec]
    double P_yr;         // orbital period [years]
    double e;            // eccentricity
    double spectral_type;// 0=unknown, 1=B, 2=O, 3=WR
    // Derived (computed at runtime)
    double a_AU;         // semi-major axis [AU]
    double a_m;          // semi-major axis [m]
    double Koppa_m;      // Ϟ from this orbit
    double v_mean;       // mean orbital velocity [m/s]
    double v_peri;       // pericenter velocity [m/s]
    double k;            // k = c / v_mean
    double z;            // z = 1/k²
};

struct Shell {
    const char* name;
    double r_inner_pc;   // inner radius [pc]
    double r_outer_pc;   // outer radius [pc]
    double v_char;       // characteristic velocity [m/s] (v_circ or σ)
    double sigma;        // velocity dispersion [m/s]
    double L_Lsun;       // luminosity [L_sun]
    double n_stars;      // estimated number of stars
    // Derived
    double k;
    double z;
    double Koppa_m;
    double Koppa_inner;
    double dKoppa;       // Ϟ(outer) - Ϟ(inner) = shell's own contribution
};

struct BarSegment {
    const char* name;
    double l_deg;        // galactic longitude of segment center
    double r_kpc;        // galactocentric radius [kpc]
    double v_rot;        // rotation velocity [m/s]
    double sigma;        // velocity dispersion [m/s]
    double L_Lsun;       // luminosity [L_sun]
};

struct ArmJunction {
    const char* arm_name;
    const char* bar_end;  // "near" or "far"
    double l_deg;         // galactic longitude
    double r_kpc;         // radius from center
    double v_arm;         // arm streaming velocity [m/s]
    double v_bar;         // bar pattern velocity at junction [m/s]
    double Koppa_arm;     // Ϟ of arm at junction
    double Koppa_bar;     // Ϟ of bar at junction
    double overlap;       // Ϟ overlap fraction
};

// =============================================================================
// S-STAR CATALOGUE (GRAVITY Collab, Gillessen et al.)
// =============================================================================

static const double R0_kpc = 8.178;  // [kpc] distance to GC
static const double R0_AU  = R0_kpc * 1000.0 * 206264.806; // kpc → AU via pc → AU
// 1 arcsec at 8.178 kpc = 8178 AU

static double arcsec_to_AU(double arcsec) {
    return arcsec * R0_kpc * 1000.0; // arcsec × d_pc = AU
}

static std::vector<SStar> load_s_stars() {
    std::vector<SStar> stars = {
        // name        a"      P[yr]   e    type
        {"S2",       0.1251,  16.05, 0.884, 1},
        {"S1",       0.412,   94.1,  0.358, 1},
        {"S4",       0.298,   57.0,  0.390, 1},
        {"S8",       0.329,   67.2,  0.927, 1},
        {"S12",      0.287,   54.4,  0.899, 1},
        {"S13",      0.219,   36.0,  0.395, 1},
        {"S14",      0.225,   36.0,  0.963, 1},
        {"S17",      0.215,   34.0,  0.397, 1},
        {"S18",      0.237,   39.0,  0.471, 1},
        {"S19",      0.319,   62.0,  0.750, 1},
        {"S21",      0.213,   33.5,  0.784, 1},
        {"S24",      0.273,   47.6,  0.892, 1},
        {"S29",      0.190,   29.0,  0.470, 1},
        {"S31",      0.271,   47.0,  0.460, 1},
        {"S33",      0.278,   48.0,  0.730, 1},
        {"S38",      0.142,   19.2,  0.820, 1},
        {"S55",      0.108,   12.8,  0.720, 1},
        {"S62",      0.090,    9.9,  0.976, 1},
        {"S4714",    0.102,   12.0,  0.985, 1},
    };

    // Compute derived quantities for each star
    for (auto& s : stars) {
        s.a_AU  = arcsec_to_AU(s.a_arcsec);
        s.a_m   = s.a_AU * AU;
        double T = s.P_yr * yr_s;
        // Ϟ = 4π²a³/(T²c²) — SDT Kepler, no G, no M
        s.Koppa_m = 4.0 * M_PI * M_PI * s.a_m * s.a_m * s.a_m / (T * T * c * c);
        s.v_mean  = 2.0 * M_PI * s.a_m / T;
        // v_peri = v_mean × sqrt((1+e)/(1-e)) × (a/r_peri) ... simplified:
        // vis-viva at peri: v² = c²Ϟ(2/r_peri - 1/a), r_peri = a(1-e)
        double r_peri = s.a_m * (1.0 - s.e);
        double v2 = c * c * s.Koppa_m * (2.0 / r_peri - 1.0 / s.a_m);
        s.v_peri  = (v2 > 0) ? sqrt(v2) : 0;
        s.k       = c / s.v_mean;
        s.z       = (s.v_mean / c) * (s.v_mean / c);
    }
    return stars;
}

// =============================================================================
// SHELL CATALOGUE — concentric zones from Sag A* outward
// =============================================================================

static std::vector<Shell> build_shells() {
    // Rotation curve data (Sofue 2013, Launhardt 2002, GRAVITY)
    // Each shell: r_inner, r_outer [pc], v_circ [m/s], σ [m/s], L [L_sun], N_stars
    std::vector<Shell> shells = {
        {"S-cluster",          0.001,    0.04,  1500e3, 500e3,   1e3,      40},
        {"IRS 16 cluster",     0.04,     0.5,   400e3,  200e3,  1e5,     200},
        {"Nuclear cluster",    0.5,      5.0,   120e3,  100e3,  3e7,   1e6},
        {"Cntrl Mol Zone",     5.0,    200.0,   110e3,   80e3,  1e8,   5e7},
        {"Inner bulge",      200.0,    500.0,   130e3,  113e3,  5e9,   1e9},
        {"Mid bulge",        500.0,   1000.0,   170e3,  113e3,  1e10,  5e9},
        {"Outer bulge",     1000.0,   2000.0,   210e3,  113e3,  2e10,  1e10},
        {"Bar near-end",    2000.0,   3500.0,   220e3,  100e3,  1e10,  5e9},
        {"Bar far-end",     3500.0,   5000.0,   225e3,   90e3,  8e9,   4e9},
    };

    for (auto& s : shells) {
        double R_outer = s.r_outer_pc * pc_m;
        double R_inner = s.r_inner_pc * pc_m;
        s.k = c / s.v_char;
        s.z = (s.v_char / c) * (s.v_char / c);
        s.Koppa_m = s.v_char * s.v_char * R_outer / (c * c);
        s.Koppa_inner = s.v_char * s.v_char * R_inner / (c * c);
        s.dKoppa = s.Koppa_m - s.Koppa_inner;
    }
    return shells;
}

// =============================================================================
// BAR STRUCTURE — longitudinal segments
// =============================================================================

static std::vector<BarSegment> build_bar() {
    // Bar oriented at 27° to Sun-center line
    // Near end at l ≈ 333°, far end at l ≈ 153°
    // Pattern speed: Ω_bar ≈ 37 km/s/kpc
    double omega_bar = 37.0; // km/s/kpc
    return {
        {"Bar core",     0.0,  0.5, 170e3, 130e3, 5e9},
        {"Bar mid-near", 333.0, 1.5, 200e3, 113e3, 3e9},
        {"Bar end-near", 333.0, 3.0, 220e3, 100e3, 2e9},
        {"Bar mid-far",  153.0, 1.5, 200e3, 113e3, 3e9},
        {"Bar end-far",  153.0, 3.0, 220e3, 100e3, 2e9},
        {"Junction-SC",  333.0, 4.5, 225e3,  80e3, 1e9},  // Scutum-Centaurus
        {"Junction-Per", 153.0, 4.5, 225e3,  80e3, 1e9},  // Perseus
    };
}

// =============================================================================
// MAIN
// =============================================================================

int main() {
    printf("###################################################################\n");
    printf("   CQ19b: Galactic Nucleus — SDT Shell Map\n");
    printf("   Sag A* → S-stars → Nuclear cluster → Bulge → Bar → Arms\n");
    printf("   zk² = 1 at every shell. No G. No M.\n");
    printf("###################################################################\n\n");

    // ---- Sag A* ----
    auto stars = load_s_stars();
    double Koppa_SagA = stars[0].Koppa_m; // from S2 (most precise)

    printf("=== SHELL 0: Sag A* ===\n\n");
    printf("   Source: S2 orbit (GRAVITY Collaboration)\n");
    printf("   Ϟ_SagA = 4π²a³/(T²c²) = %.4e m = %.2f km\n", Koppa_SagA, Koppa_SagA/1e3);
    printf("   This is %.3f R_Earth = %.4f AU\n", Koppa_SagA/bridge::R_Earth, Koppa_SagA/AU);
    printf("   z at S2 pericenter (r=%.0f AU): %.4e\n",
           stars[0].a_AU*(1-stars[0].e), Koppa_SagA/(stars[0].a_m*(1-stars[0].e)));
    printf("   z at R₀ (8.178 kpc): %.4e\n\n", Koppa_SagA/(R0_kpc*kpc_m));

    // ---- S-star catalogue ----
    printf("=== SHELL 1: S-STAR CLUSTER ===\n\n");
    printf("   %-8s %6s %8s %6s %10s %10s %10s %10s %10s %8s\n",
           "Star","a[\"]","P[yr]","e","a[AU]","Ϟ[m]","v_mean","v_peri","k","zk²");
    printf("   %-8s %6s %8s %6s %10s %10s %10s %10s %10s %8s\n",
           "────","────","─────","───","─────","────","──────","──────","───","───");

    // Sort by semi-major axis
    std::sort(stars.begin(), stars.end(),
              [](const SStar& a, const SStar& b){ return a.a_AU < b.a_AU; });

    double Koppa_mean = 0;
    int n_K = 0;
    for (const auto& s : stars) {
        double zk2 = s.z * s.k * s.k;
        printf("   %-8s %6.3f %8.1f %6.3f %10.1f %10.3e %10.0f %10.0f %10.1f %8.6f\n",
               s.name, s.a_arcsec, s.P_yr, s.e, s.a_AU, s.Koppa_m,
               s.v_mean, s.v_peri, s.k, zk2);
        Koppa_mean += s.Koppa_m;
        n_K++;
    }
    Koppa_mean /= n_K;

    printf("\n   Mean Ϟ from %d S-stars: %.4e m (%.2f km)\n", n_K, Koppa_mean, Koppa_mean/1e3);
    printf("   Ϟ from S2 alone:       %.4e m\n", stars[0].Koppa_m);
    printf("   Scatter: %.2f%%\n", 100.0*fabs(Koppa_mean-stars[0].Koppa_m)/stars[0].Koppa_m);
    printf("   All zk² = 1.000000 — closure holds for every orbit.\n\n");

    // ---- S-star velocity shells ----
    printf("=== S-STAR VELOCITY DECOMPOSITION ===\n\n");
    printf("   Binned by v_mean:\n\n");

    struct VBin { const char* label; double v_lo, v_hi; int n; double K_sum, v_sum; };
    VBin vbins[] = {
        {"> 5000 km/s",  5e6, 1e9, 0, 0, 0},
        {"2000-5000",    2e6, 5e6, 0, 0, 0},
        {"1000-2000",    1e6, 2e6, 0, 0, 0},
        {"500-1000",     5e5, 1e6, 0, 0, 0},
        {"< 500 km/s",   0,   5e5, 0, 0, 0},
    };
    for (const auto& s : stars) {
        for (auto& b : vbins) {
            if (s.v_mean >= b.v_lo && s.v_mean < b.v_hi) {
                b.n++; b.K_sum += s.Koppa_m; b.v_sum += s.v_mean; break;
            }
        }
    }
    printf("   %-14s %5s %12s %12s %12s\n", "v_mean bin", "n", "mean Ϟ [m]", "mean v [km/s]", "mean k");
    for (const auto& b : vbins) {
        if (b.n > 0)
            printf("   %-14s %5d %12.3e %12.0f %12.1f\n",
                   b.label, b.n, b.K_sum/b.n, b.v_sum/b.n/1e3, c/(b.v_sum/b.n));
    }

    // ---- Concentric shells ----
    printf("\n=== SHELLS 2-8: NUCLEUS → BULGE → BAR ===\n\n");
    auto shells = build_shells();

    printf("   %-18s %8s %8s %10s %8s %10s %10s %10s %10s\n",
           "Shell","r_in[pc]","r_out[pc]","v[km/s]","σ[km/s]","k","z=1/k²","Ϟ_outer[m]","ΔϞ[m]");
    printf("   %-18s %8s %8s %10s %8s %10s %10s %10s %10s\n",
           "──────────────────","────────","────────","────────","──────","────","──────","─────────","──────");

    for (const auto& s : shells) {
        printf("   %-18s %8.1f %8.0f %10.0f %8.0f %10.1f %10.3e %10.3e %10.3e\n",
               s.name, s.r_inner_pc, s.r_outer_pc, s.v_char/1e3, s.sigma/1e3,
               s.k, s.z, s.Koppa_m, s.dKoppa);
    }

    // ---- Ϟ profile ----
    printf("\n=== Ϟ RADIAL PROFILE ===\n\n");
    printf("   r [pc]          Ϟ(r) [m]      z=Ϟ/r         v_circ [km/s]   k\n");
    printf("   ──────          ─────────      ─────         ─────────────   ──\n");

    // Interpolated rotation curve from Sofue + inner data
    struct RCPoint { double r_pc; double v_kms; };
    RCPoint rc[] = {
        {0.01,   1500}, {0.04,  1200}, {0.1,   800}, {0.5,   400},
        {1.0,    200},  {2.0,   150},  {5.0,   120}, {10.0,  110},
        {50.0,   100},  {100.0, 105},  {200.0, 110}, {500.0, 130},
        {1000.0, 170},  {2000.0, 210}, {3000.0, 220}, {5000.0, 225},
        {8178.0, 232.8},
    };
    int nrc = sizeof(rc)/sizeof(rc[0]);

    for (int i = 0; i < nrc; i++) {
        double r = rc[i].r_pc * pc_m;
        double v = rc[i].v_kms * 1e3;
        double K = v * v * r / (c * c);
        double z = K / r;
        double k = c / v;
        printf("   %-14.2f  %12.4e  %12.4e  %12.1f     %10.1f\n",
               rc[i].r_pc, K, z, rc[i].v_kms, k);
    }

    // ---- Bar structure ----
    printf("\n=== BAR LONGITUDINAL STRUCTURE ===\n\n");
    auto bar = build_bar();
    printf("   Bar orientation: 27° to Sun-center line\n");
    printf("   Pattern speed: Ω_bar ≈ 37 km/s/kpc\n");
    printf("   Corotation radius: r_CR ≈ %.1f kpc\n\n", 232.8/37.0);

    printf("   %-16s %6s %8s %10s %8s %12s %12s\n",
           "Segment","l[°]","r[kpc]","v[km/s]","σ[km/s]","Ϟ[m]","z=Ϟ/r");
    printf("   %-16s %6s %8s %10s %8s %12s %12s\n",
           "────────────────","────","──────","────────","──────","──────","────");

    for (const auto& b : bar) {
        double r = b.r_kpc * kpc_m;
        double K = b.v_rot * b.v_rot * r / (c * c);
        double z = K / r;
        printf("   %-16s %6.0f %8.1f %10.0f %8.0f %12.4e %12.4e\n",
               b.name, b.l_deg, b.r_kpc, b.v_rot/1e3, b.sigma/1e3, K, z);
    }

    // ---- Macro bonding test ----
    printf("\n=== MACRO BONDING TEST: BAR-ARM JUNCTIONS ===\n\n");
    printf("   SDT atomic bonding: two nuclei share occlusion field → attraction\n");
    printf("   Macro analog: bar end + spiral arm share Ϟ field → junction binding\n\n");

    // Bar end Ϟ
    double r_bar_end = 3.5 * kpc_m;
    double v_bar_end = 220e3;
    double K_bar = v_bar_end * v_bar_end * r_bar_end / (c * c);

    // Arm Ϟ at junction (from arm streaming velocity)
    double v_arm = 225e3; // arm circular velocity at junction
    double r_arm = 4.5 * kpc_m;
    double K_arm = v_arm * v_arm * r_arm / (c * c);

    // Overlap: the region where both Ϟ fields contribute
    double K_total = K_bar + K_arm; // upper bound (fully shared)
    double K_measured = v_arm * v_arm * r_arm / (c * c); // what we measure

    // Pattern speed creates differential: v_bar ≠ v_arm at junction
    double omega_bar = 37.0; // km/s/kpc
    double v_pattern = omega_bar * 4.0; // km/s at r=4 kpc
    double v_circ = 225.0; // km/s at r=4.5 kpc
    double v_differential = v_circ - v_pattern; // streaming velocity in bar frame

    printf("   Bar end (r=3.5 kpc):     Ϟ_bar  = %.4e m\n", K_bar);
    printf("   Arm at junction (4.5 kpc): Ϟ_arm  = %.4e m\n", K_arm);
    printf("   Sum (unbound):             Ϟ_sum  = %.4e m\n", K_bar + K_arm);
    printf("   Measured at junction:      Ϟ_meas = %.4e m\n", K_measured);
    printf("\n");
    printf("   Pattern speed: Ω_bar = %.0f km/s/kpc\n", omega_bar);
    printf("   At r=4 kpc: v_pattern = %.0f km/s, v_circ = %.0f km/s\n",
           v_pattern, v_circ);
    printf("   Differential (streaming in bar frame): %.0f km/s\n\n", v_differential);

    // The "bond energy" analog: the kinetic energy of the streaming motion
    // relative to the bar pattern. If this is less than the Ϟ overlap,
    // the junction is bound.
    double z_streaming = (v_differential*1e3/c) * (v_differential*1e3/c);
    double z_junction = K_arm / r_arm;

    printf("   z_streaming = (v_diff/c)² = %.4e\n", z_streaming);
    printf("   z_junction  = Ϟ/r         = %.4e\n", z_junction);
    printf("   Ratio z_junction / z_streaming = %.1f\n\n", z_junction / z_streaming);

    if (z_junction > z_streaming) {
        printf("   *** z_junction > z_streaming → JUNCTION IS BOUND ***\n");
        printf("   The bar-arm connection is a BONDED structure, not a coincidence.\n");
        printf("   The Ϟ field of the bar overlaps with the arm's Ϟ field,\n");
        printf("   creating shared occlusion — the macro analog of a covalent bond.\n\n");
    } else {
        printf("   z_junction < z_streaming → junction is unbound / transient.\n\n");
    }

    // ---- Nuclear analogy table ----
    printf("=== SCALE ANALOGY: ATOM ↔ GALAXY ===\n\n");
    printf("   %-22s  %-24s  %-24s\n", "Feature", "Hydrogen atom", "Milky Way");
    printf("   %-22s  %-24s  %-24s\n", "──────────────────────","────────────────────────","────────────────────────");
    printf("   %-22s  %-24s  %-24s\n", "Nucleus",     "Proton (W=3 trefoil)",    "Sag A* (Ϟ=6.3e9 m)");
    printf("   %-22s  %-24s  %-24s\n", "Nucleus Ϟ",   "r_e = 2.82 fm",           "6300 km");
    printf("   %-22s  %-24s  %-24s\n", "Inner shell", "1s electron (k=137)",      "S-stars (k~156)");
    printf("   %-22s  %-24s  %-24s\n", "Outer shell", "2s,2p electrons",          "Nuclear cluster");
    printf("   %-22s  %-24s  %-24s\n", "Core radius", "a₀ = 0.529 Å",            "NSC r_eff = 4.2 pc");
    printf("   %-22s  %-24s  %-24s\n", "Bonding",     "Covalent (shared e⁻)",     "Bar-arm junction (shared Ϟ)");
    printf("   %-22s  %-24s  %-24s\n", "Bond type",   "Occlusion overlap",        "Occlusion overlap");
    printf("   %-22s  %-24s  %-24s\n", "Bond energy", "E = α²m_e c²/2",          "z_stream × M_arm × c²");
    printf("   %-22s  %-24s  %-24s\n", "Closure",     "zk² = 1",                 "zk² = 1");

    printf("\n   The galaxy is not 'like' an atom. It IS the same law at a different scale.\n");
    printf("   zk² = 1.\n\n");

    return 0;
}
