// =============================================================================
// SDT Galactic Calculator
// Investigations/GalacticCalculator/sdt_galaxy_calc.cpp
//
// PURPOSE:
//   Universal SDT-native rotation curve calculator for any galaxy type.
//   Inputs: name, M_bar [M_sun], h_R [kpc], R_bar [kpc], q_bulge, type.
//   Output: v(R), Koppa(R), zk²(R), flat-zone, bar streak, GA direction.
//
// PHYSICS (from GD01 eclipse saturation model):
//   v²(R) = c² × f_occ(R) × Ϟ_gal / R     [disk]
//   v²(R) += bulge spheroid correction (CQ20g ^1.3 factor)
//   v²(R) += bar solid-line occlusion (CQ20d streak model)
//
//   Ϟ_gal = M_bar [M_sun] × Ϟ_sun          [no G, no kg]
//   f_occ(R) = Σ_enc(R) / Σ_sat             [eclipse fraction]
//   zk² = 1 at every radius                  [closure identity]
//
// GALAXY TYPES:
//   Spiral   — disk + optional bar + optional bulge
//   Dwarf    — same formula, low M_bar
//   LSB      — same formula, large h_R / low Σ₀
//   Elliptical — de Vaucouleurs profile, spheroid factor throughout
//   Cluster  — flat occlusion profile, mega-Ϟ
//
// No G. No M (in kg). No dark matter. zk² = 1.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <numbers>
#include <algorithm>
#include <sdt/laws.hpp>

namespace K  = sdt::laws::measured;
namespace B  = sdt::laws::bridge;

// =============================================================================
// CONSTANTS
// =============================================================================
static constexpr double PI        = std::numbers::pi;
static constexpr double kpc_m     = 3.085677581e19;
static constexpr double pc_m      = 3.085677581e16;
static constexpr double M_sun_kg  = 1.989e30;
static constexpr double H0_SI     = 67.4e3 / 3.085677581e22; // [s⁻¹]

// =============================================================================
// SDT FIELD SCALARS (from GD01, all from laws.hpp — no G imported)
// =============================================================================
static constexpr double Koppa_sun     = B::koppa_Sun;          // 1477.046 m
static constexpr double Koppa_per_bar = B::koppa_per_baryon;   // 1.242e-54 m
static constexpr double a0_SDT        = K::c * H0_SI / (2.0 * PI); // Milgrom scale
static constexpr double Sigma_sat     = 175.0 * M_sun_kg / (pc_m * pc_m); // MW-calibrated

// =============================================================================
// GALAXY TYPE
// =============================================================================
enum class GType { Spiral, Dwarf, LSB, Elliptical, Cluster };

// =============================================================================
// GALAXY INPUT
// =============================================================================
struct Galaxy {
    const char* name;
    GType       type;
    double      M_bar;      // baryonic mass [M_sun]
    double      h_R;        // disk scale length [kpc]
    double      R_bar;      // bar half-length [kpc], 0 = no bar
    double      q_bulge;    // bulge axial ratio [0,1], 0 = no bulge
    double      R_bulge;    // bulge half-mass radius [kpc]
    double      R_max;      // outer integration radius [kpc]
    double      v_obs;      // observed flat velocity [km/s], 0 = unknown
    double      R_obs;      // observed flat onset [kpc], 0 = unknown
};

// =============================================================================
// CORE PHYSICS
// =============================================================================

// Total galactic Koppa from baryon mass (GD01 derivation chain, no G)
static double Koppa_gal(double M_bar_msun) {
    return M_bar_msun * Koppa_sun;  // = N_bar × Koppa_per_baryon
}

// Enclosed mean surface density within R for exponential disk (GD01)
// <Σ>(R) = Σ₀ × (2h²/R²) × [1 - (1 + R/h)exp(-R/h)]
static double Sigma_enc(double Sigma_0, double R_m, double h_m) {
    if (R_m < 1e3) return Sigma_0;
    double x = R_m / h_m;
    return Sigma_0 * 2.0 / (x * x) * (1.0 - (1.0 + x) * std::exp(-x));
}

// Eclipse fraction from enclosed surface density (GD01)
static double f_eclipse(double Sigma_enc_val, double /*Sigma_0*/) {
    return 1.0 - std::exp(-Sigma_enc_val / Sigma_sat);
}

// Bulge spheroid factor: extra occlusion from oblate 3D volume (CQ20g)
// Factor = (R/R_ref)^0.3 where R_ref = R_bulge (half-mass radius)
static double spheroid_factor(double R_kpc, double R_bulge_kpc, double q) {
    if (R_bulge_kpc <= 0.0 || q <= 0.0) return 1.0;
    double axial_boost = 1.0 + (1.0 - q) * 0.5;  // oblate compression bonus
    double r_ratio     = R_kpc / R_bulge_kpc;
    return axial_boost * std::pow(r_ratio < 1.0 ? r_ratio : 1.0, 0.3);
}

// Central surface density from M_bar and h_R (exponential disk)
// M_disk = 2π Σ₀ h_R²  →  Σ₀ = M_disk / (2π h_R²)
static double Sigma_0(const Galaxy& g) {
    double h_m  = g.h_R * kpc_m;
    double M_kg = g.M_bar * M_sun_kg;
    return M_kg / (2.0 * PI * h_m * h_m);
}

// De Vaucouleurs enclosed fraction for ellipticals:
// f_deV(R) = gamma(8, b_n(R/R_eff)^(1/4)) / Gamma(8)
// Approximated as: 1 - exp(- (R/R_eff)^0.25 × 7.67)
static double f_deVauc(double R_kpc, double R_eff_kpc) {
    if (R_eff_kpc <= 0.0) return 0.5;
    double x = 7.67 * std::pow(R_kpc / R_eff_kpc, 0.25);
    return 1.0 - std::exp(-x);
}

// Disk velocity from eclipse saturation model (GD01 Step 7)
// v²(R) = c² × f_enc(R) × min(Σ₀/Σ_sat, 1) × Ϟ_gal / R
// f_enc(R) = 1 - (1+x)exp(-x)  [enclosed fraction]
// The Σ₀/Σ_sat factor captures the eclipse depth for sub-critical disks.
// For Σ₀ >> Σ_sat (MW-class): saturates → pure f_enc.
// For Σ₀ << Σ_sat (dwarfs/LSB): linear in Σ₀ → sub-eclipse regime.
static double v_disk(double R_kpc, const Galaxy& g) {
    double R_m    = R_kpc * kpc_m;
    double h_m    = g.h_R  * kpc_m;
    double x      = R_m / h_m;
    double f_enc  = 1.0 - (1.0 + x) * std::exp(-x);
    double S0     = Sigma_0(g);
    double sat_fac = std::min(S0 / Sigma_sat, 1.0);  // eclipse depth
    double K      = Koppa_gal(g.M_bar);
    double v2     = K::c * K::c * f_enc * sat_fac * K / R_m;
    return (v2 > 0.0) ? std::sqrt(v2) / 1e3 : 0.0;  // km/s
}

// Bulge velocity: spheroid-corrected disk for the inner region (CQ20g)
static double v_bulge(double R_kpc, const Galaxy& g) {
    if (g.q_bulge <= 0.0 || g.R_bulge <= 0.0) return 0.0;
    double R_m   = R_kpc * kpc_m;
    double h_m   = g.R_bulge * kpc_m;  // use R_bulge as scale for bulge component
    double S0    = Sigma_0(g) * 2.5;   // bulge has higher central density
    double Senc  = Sigma_enc(S0, R_m, h_m);
    double f     = f_eclipse(Senc, S0);
    // Spheroid factor: interior bulge gets ^1.3 boost on the solid angle
    double sfac  = (R_kpc < g.R_bulge) ?
                   std::pow(R_kpc / g.R_bulge + 0.01, 0.3) : 1.0;
    double Kbulge = Koppa_gal(g.M_bar * 0.15);  // bulge ~ 15% of total M_bar
    double v2    = K::c * K::c * f * sfac * Kbulge / R_m;
    return (v2 > 0.0) ? std::sqrt(v2) / 1e3 : 0.0;  // km/s
}

// Bar solid-line occlusion velocity addition (CQ20d)
// Within the bar: the solid angle subtended by the bar adds occlusion
// Beyond the bar: contribution falls as (R_bar/R)²
static double v_bar(double R_kpc, const Galaxy& g) {
    if (g.R_bar <= 0.0) return 0.0;
    double bar_w = 0.5;  // bar half-width [kpc] (canonical MW value)
    double K     = Koppa_gal(g.M_bar * 0.08);  // bar ~ 8% of total M_bar
    double R_m   = R_kpc * kpc_m;
    double Rbar_m = g.R_bar * kpc_m;
    double f_bar;
    if (R_kpc <= g.R_bar) {
        // Inside bar: solid-line occlusion fraction grows as bar fills hemisphere
        f_bar = 0.5 * (bar_w / g.R_bar);
    } else {
        // Outside bar: falls as (R_bar/R)²
        f_bar = 0.5 * (bar_w / g.R_bar) * (Rbar_m / R_m) * (Rbar_m / R_m);
    }
    double v2 = K::c * K::c * f_bar * K / R_m;
    return (v2 > 0.0) ? std::sqrt(v2) / 1e3 : 0.0;
}

// Elliptical / de Vaucouleurs total velocity
static double v_elliptical(double R_kpc, const Galaxy& g) {
    double R_m   = R_kpc * kpc_m;
    double K     = Koppa_gal(g.M_bar);
    double f     = f_deVauc(R_kpc, g.R_bulge > 0 ? g.R_bulge : g.h_R);
    double sfac  = spheroid_factor(R_kpc, g.R_bulge > 0 ? g.R_bulge : g.h_R, g.q_bulge);
    double v2    = K::c * K::c * f * sfac * K / R_m;
    return (v2 > 0.0) ? std::sqrt(v2) / 1e3 : 0.0;
}

// Cluster: use f_occ = 0.5 (half-sky saturation at cluster scales)
static double v_cluster(double R_kpc, const Galaxy& g) {
    double R_m = R_kpc * kpc_m;
    double K   = Koppa_gal(g.M_bar);
    double v2  = K::c * K::c * 0.5 * K / R_m;
    return (v2 > 0.0) ? std::sqrt(v2) / 1e3 : 0.0;
}

// Total rotation velocity dispatched by galaxy type
static double v_total(double R_kpc, const Galaxy& g) {
    if (R_kpc < 1e-6) return 0.0;
    switch (g.type) {
        case GType::Elliptical: return v_elliptical(R_kpc, g);
        case GType::Cluster:    return v_cluster(R_kpc, g);
        default: {
            // Disk + bulge + bar: add in quadrature (independent occlusion zones)
            double vd = v_disk(R_kpc, g);
            double vb = v_bulge(R_kpc, g);
            double vr = v_bar(R_kpc, g);
            return std::sqrt(vd*vd + vb*vb + vr*vr);
        }
    }
}

// =============================================================================
// PROFILE PRINTER
// =============================================================================
static void print_profile(const Galaxy& g, double R_min, double R_max_kpc, int N) {
    printf("  R [kpc]   v_SDT [km/s]    Ϟ [m]         z=v²/c²     zk²\n");
    printf("  -------   ------------    -----         -------     ---\n");
    double dR = (R_max_kpc - R_min) / N;
    double v_flat_found = 0.0;
    double R_flat_found = 0.0;
    double v_prev       = 0.0;
    for (int i = 0; i <= N; i++) {
        double R_kpc = R_min + i * dR;
        double R_m   = R_kpc * kpc_m;
        double v     = v_total(R_kpc, g);   // km/s
        double v_ms  = v * 1e3;             // m/s
        double Koppa = v_ms * v_ms * R_m / (K::c * K::c);
        double z     = (v_ms / K::c) * (v_ms / K::c);
        double k     = (v_ms > 0.0) ? K::c / v_ms : 1e9;
        double zk2   = z * k * k;
        // Detect flat zone onset: v changes < 5%
        if (i > 0 && v_prev > 0.0 &&
            std::fabs(v - v_prev) / v_prev < 0.05 &&
            R_flat_found < 0.1) {
            R_flat_found = R_kpc;
            v_flat_found = v;
        }
        printf("  %7.3f   %12.2f    %12.4e   %10.4e   %10.6f\n",
               R_kpc, v, Koppa, z, zk2);
        v_prev = v;
    }
    if (v_flat_found > 0.0) {
        printf("\n  Flat zone onset: R ~ %.2f kpc,  v_flat ~ %.1f km/s\n",
               R_flat_found, v_flat_found);
    }
    if (g.v_obs > 0.0) {
        double v_pred = v_total(g.R_obs > 0.0 ? g.R_obs * 2.0 : g.h_R * 3.0, g);
        printf("  Observed v_flat: %.1f km/s   SDT prediction: %.1f km/s   error: %.1f%%\n",
               g.v_obs, v_pred,
               std::fabs(v_pred - g.v_obs) / g.v_obs * 100.0);
    }
    printf("\n");
}

// =============================================================================
// CLOSURE TABLE
// =============================================================================
static void print_closure(const Galaxy& g) {
    printf("  CLOSURE TABLE (zk^2 = 1 at every radius):\n");
    printf("  %-14s  %8s  %8s  %12s  %8s\n",
           "Zone", "R [kpc]", "v [km/s]", "Ϟ [m]", "zk^2");
    printf("  %-14s  %8s  %8s  %12s  %8s\n",
           "----", "-------", "-------", "-----", "---");
    double radii[] = { 0.5, 1.0, g.h_R, g.h_R*2, g.h_R*4,
                       g.R_max*0.5, g.R_max };
    const char* labels[] = { "inner", "inner2", "h_R", "2h_R", "4h_R", "mid", "edge" };
    for (int i = 0; i < 7; i++) {
        double R = radii[i];
        double v = v_total(R, g);
        double vm = v * 1e3;
        double Rm = R * kpc_m;
        double K  = vm * vm * Rm / (K::c * K::c);
        double z  = (vm / K::c) * (vm / K::c);
        double k  = vm > 0.0 ? K::c / vm : 1e9;
        printf("  %-14s  %8.2f  %8.1f  %12.4e  %8.6f\n",
               labels[i], R, v, K, z*k*k);
    }
    printf("\n");
}

// =============================================================================
// GREAT ATTRACTOR STREAK
// =============================================================================
static void print_ga_streak(const Galaxy& g) {
    // From observer at R_obs (≈ R_max/2 for MW analogue),
    // the bar terminus subtends angle theta toward l=0°.
    // The GA-equivalent direction is at l = 180° - theta (bar terminus projected).
    double R_obs = g.R_max * 0.5;
    double theta_bar = std::atan(g.R_bar / R_obs) * 180.0 / PI;
    double l_GA_equiv = 180.0 - theta_bar;
    printf("  OCCLUSION STREAK (bar at R_bar=%.1f kpc from observer at R=%.1f kpc):\n",
           g.R_bar, R_obs);
    printf("  Bar subtends %.2f° — 'GA-equivalent' direction: l ~ %.1f°\n",
           theta_bar, l_GA_equiv);
    printf("  This is the direction of maximum occlusion deficit\n");
    printf("  (apparent streaming — no external mass required).\n\n");
}

// =============================================================================
// GALAXY CATALOGUE
// =============================================================================
static const Galaxy catalogue[] = {
    // Milky Way
    { "Milky Way",    GType::Spiral,     5.17e10, 2.6, 3.5, 0.6, 1.5, 25.0, 220.0, 3.0 },
    // Giant spirals
    { "NGC 7331",     GType::Spiral,     1.2e11,  3.8, 0.0, 0.4, 0.8, 30.0, 240.0, 4.0 },
    { "NGC 3198",     GType::Spiral,     4.0e10,  3.1, 0.0, 0.0, 0.0, 25.0, 150.0, 3.5 },
    { "NGC 2403",     GType::Spiral,     1.5e10,  2.1, 0.0, 0.3, 0.5, 20.0, 131.0, 2.5 },
    // Standard spirals
    { "NGC 6503",     GType::Spiral,     2.0e10,  2.1, 0.0, 0.2, 0.4, 20.0, 116.0, 2.0 },
    // Dwarf galaxies
    { "DDO 154",      GType::Dwarf,      1.0e8,   0.9, 0.0, 0.0, 0.0,  5.0,  47.0, 1.5 },
    { "NGC 3741",     GType::Dwarf,      3.0e8,   1.2, 0.0, 0.0, 0.0,  6.0,  50.0, 2.0 },
    // LSB galaxies
    { "UGC 128",      GType::LSB,        3.0e9,   5.0, 0.0, 0.0, 0.0, 30.0,  64.0, 8.0 },
    { "IC 2574",      GType::LSB,        4.0e9,   3.7, 0.0, 0.0, 0.0, 25.0,  67.0, 5.0 },
    // Elliptical
    { "M87",          GType::Elliptical, 6.0e12,  3.0, 0.0, 0.9, 4.0, 50.0, 350.0, 5.0 },
    // Cluster
    { "Coma Cluster", GType::Cluster,    3.0e14,  500.0,0.0,0.0, 0.0,2000.0,1000.0,200.0},
};
static constexpr int N_GAL = (int)(sizeof(catalogue)/sizeof(catalogue[0]));

// =============================================================================
// MAIN
// =============================================================================
int main() {
    printf("###################################################################\n");
    printf("   SDT Galactic Calculator — Universal Rotation Curve Engine\n");
    printf("   From proton occlusion engine to Laniakea filaments.\n");
    printf("   No G. No dark matter. zk^2 = 1.\n");
    printf("###################################################################\n\n");

    for (int i = 0; i < N_GAL; i++) {
        const Galaxy& g = catalogue[i];
        printf("╔══════════════════════════════════════════════════════════════╗\n");
        printf("║  %s\n", g.name);
        printf("║  M_bar = %.2e M_sun | h_R = %.1f kpc | R_bar = %.1f kpc\n",
               g.M_bar, g.h_R, g.R_bar);
        printf("╚══════════════════════════════════════════════════════════════╝\n\n");

        print_profile(g, 0.1, g.R_max, 20);
        print_closure(g);
        if (g.R_bar > 0.0) print_ga_streak(g);
        printf("\n");
    }

    return 0;
}
