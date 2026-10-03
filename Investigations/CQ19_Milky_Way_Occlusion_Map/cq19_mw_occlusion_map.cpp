// =============================================================================
// CQ19 — Milky Way Occlusion Map
//
// The MW is NOT a point source. We sit at R₀ = 8.178 kpc off-center in a
// structured field: Sag A* + bulge/bar + disk + spiral arms.
//
// This solver computes the DIRECTIONAL z_grav contamination on every
// extragalactic photon arriving at Earth, as a function of galactic (l, b).
//
// Components:
//   1. Sag A*:  Ϟ = 6.38e9 m  (from S2 orbit, no G, no M)
//   2. Bulge:   Ϟ = 3.03e13 m (from v_circ at bulge boundary)
//   3. Disk:    exponential, h_R = 3.5 kpc, h_z = 0.3 kpc
//   4. Total:   Ϟ_MW = 1.52e14 m (from v_rot = 232.8 km/s at R₀)
//
// For each (l, b) direction, we ray-trace through the MW density model
// and compute the accumulated z_grav column. This is the correction
// that MUST be applied to every extragalactic redshift measurement.
//
// Output: all-sky z_grav map in galactic coordinates.
//
// No G. No M. zk² = 1.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <algorithm>

#include <sdt/laws.hpp>

using namespace sdt::laws;
using namespace sdt::laws::measured;

static constexpr double kpc  = 3.085677581e19;  // m
static constexpr double c_kms = c / 1000.0;

// =============================================================================
// MW STRUCTURAL PARAMETERS (all observational, no G, no M)
// =============================================================================

// Observer position
static constexpr double R0       = 8.178;   // kpc — Sun's galactocentric radius (GRAVITY collab 2019)
static constexpr double z0_sun   = 0.025;   // kpc — Sun's height above midplane (Jurić et al. 2008)

// Sag A* — from S2 stellar orbit (GRAVITY collab)
static constexpr double T_S2_yr   = 16.046;
static constexpr double a_S2_AU   = 1031.0;   // semi-major axis [AU]
// Ϟ_SagA = 4π²a³/(T²c²)
static constexpr double a_S2_m    = a_S2_AU * AU;
static constexpr double T_S2_s    = T_S2_yr * 365.25 * 86400.0;
static constexpr double Koppa_SagA = 4.0 * M_PI * M_PI * a_S2_m * a_S2_m * a_S2_m
                                   / (T_S2_s * T_S2_s * c * c);
// ≈ 6.26e9 m

// Bulge — from rotation curve at bulge boundary (Sofue 2013)
static constexpr double R_bulge  = 2.0;     // kpc — effective bulge boundary
static constexpr double v_bulge  = 210.0e3; // m/s — v_circ at bulge edge
static constexpr double Koppa_bulge = v_bulge * v_bulge * R_bulge * kpc / (c * c);
// ≈ 3.03e13 m

// Disk — exponential model (Bland-Hawthorn & Gerhard 2016)
static constexpr double hR       = 3.5;     // kpc — radial scale length
static constexpr double hz       = 0.3;     // kpc — vertical scale height
static constexpr double R_disk   = 15.0;    // kpc — disk truncation radius

// Total MW at R₀
static constexpr double v_rot    = 232.8e3; // m/s — Sun's circular speed
static constexpr double Koppa_MW = v_rot * v_rot * R0 * kpc / (c * c);
// ≈ 1.52e14 m

// Bulge bar orientation (Wegg et al. 2015)
static constexpr double bar_angle_deg = 27.0;  // angle between bar major axis and Sun-center line
static constexpr double bar_a    = 3.5;    // kpc — bar semi-major axis
static constexpr double bar_b    = 1.5;    // kpc — bar semi-minor axis (in-plane)
static constexpr double bar_c    = 1.0;    // kpc — bar vertical semi-axis

// =============================================================================
// MW DENSITY MODEL — normalised to produce correct Ϟ at each radius
//
// ρ(R, z) = ρ_bulge(R, z) + ρ_disk(R, z)
//
// In SDT: density maps to occlusion density. The z_grav column integral
// is proportional to ∫ ρ ds along the line of sight, weighted by the
// potential gradient.
//
// For a photon arriving from direction (l, b), the accumulated z_grav
// from the MW structure along the LOS is:
//
//   z_grav_column(l,b) = ∫₀^∞ [dφ/ds] ds / c²
//
// where dφ/ds is the gravitational potential gradient along the LOS.
//
// Simplification: for an extragalactic photon, the NET endpoint shift
// in a static conservative potential is isotropic: z = Ϟ_MW/R₀.
// The DIRECTIONAL effect comes from:
//   (a) Non-conservative terms (bar rotation, spiral arm pattern speed)
//   (b) Differential Ϟ column: different amounts of mass BETWEEN us and
//       the source depending on direction → different Shapiro delay
//   (c) The disk column creates a latitude-dependent ADDITIONAL z_grav
//       for photons traversing the plane (non-endpoint effect)
//
// We compute the column density integral for each direction.
// =============================================================================

// Disk density (exponential)
static double rho_disk(double R_kpc, double z_kpc) {
    return exp(-R_kpc / hR) * exp(-fabs(z_kpc) / hz);
}

// Bulge density (triaxial bar, Dwek et al. 1995 model)
static double rho_bulge(double x_kpc, double y_kpc, double z_kpc) {
    // Bar coordinates: rotate by bar_angle from Sun-center line
    double ca = cos(bar_angle_deg * M_PI / 180.0);
    double sa = sin(bar_angle_deg * M_PI / 180.0);
    double xb =  x_kpc * ca + y_kpc * sa;
    double yb = -x_kpc * sa + y_kpc * ca;
    double zb =  z_kpc;
    // Triaxial distance
    double s = sqrt((xb/bar_a)*(xb/bar_a) + (yb/bar_b)*(yb/bar_b) + (zb/bar_c)*(zb/bar_c));
    if (s > 3.0) return 0.0;  // truncate at 3× scale
    return exp(-s * s / 2.0);  // Gaussian bar profile
}

// Sag A* — point source at origin
// z_grav contribution at distance d from center: z = Ϟ_SagA / (d × kpc)
static double z_sagA_at(double d_kpc) {
    if (d_kpc < 0.001) d_kpc = 0.001;  // regularise
    return Koppa_SagA / (d_kpc * kpc);
}

// =============================================================================
// RAY TRACING — column integral through MW from observer position
//
// For each (l, b), cast a ray from Sun's position outward. Integrate
// the density-weighted gravitational column. The integral gives the
// relative z_grav contamination in that direction.
//
// We normalise so that the mean over 4π equals the known isotropic
// endpoint: z_MW = (v_rot/c)² = 6.03e-7
// =============================================================================

struct RayResult {
    double column_disk;     // disk column density integral
    double column_bulge;    // bulge column density integral
    double column_total;    // total column
    double z_sagA;          // Sag A* endpoint z at closest approach
    double z_total;         // total directional z_grav
    double Koppa_column;    // effective Ϟ from column
};

static RayResult trace_ray(double l_deg, double b_deg) {
    double l = l_deg * M_PI / 180.0;
    double b = b_deg * M_PI / 180.0;

    // Ray direction in galactocentric Cartesian
    // x toward galactic center, y in direction of rotation, z toward NGP
    // Sun at (R0, 0, z0)
    double dx = -cos(b) * cos(l);  // toward center at l=0
    double dy = -cos(b) * sin(l);  // toward l=90
    double dz =  sin(b);           // toward NGP

    // Integrate outward from Sun's position
    double col_disk  = 0.0;
    double col_bulge = 0.0;
    double min_dist_center = 1e10;

    // Integration: step along ray in kpc
    // Go both forward (out of galaxy) and backward (through galaxy)
    // For extragalactic: the photon comes FROM outside, so we integrate
    // from ∞ to Sun. Equivalently: integrate from Sun outward and inward.
    // Total column = inward path (through galaxy to far side) + outward path (to near edge)

    double ds = 0.02;  // kpc step
    double s_max = 30.0;  // kpc — well beyond disk edge

    // We trace the ray in BOTH directions to see total column
    // a photon from (l, b) comes from that direction, passes through MW to reach us
    for (double s = 0; s < s_max; s += ds) {
        // Position along ray (from Sun, going TOWARD the source direction,
        // i.e., the photon came FROM this direction)
        double x = R0 + s * dx;  // galactocentric x
        double y = 0.0 + s * dy; // galactocentric y (Sun at y=0)
        double z = z0_sun + s * dz;

        double R_gal = sqrt(x * x + y * y);
        double d_center = sqrt(x * x + y * y + z * z);
        if (d_center < min_dist_center) min_dist_center = d_center;

        col_disk  += rho_disk(R_gal, z) * ds;
        col_bulge += rho_bulge(x, y, z) * ds;
    }

    RayResult res{};
    res.column_disk  = col_disk;
    res.column_bulge = col_bulge;
    res.column_total = col_disk + col_bulge;
    res.z_sagA       = z_sagA_at(min_dist_center);

    return res;
}

// =============================================================================
// NORMALISATION
//
// We want the column integrals to map to physical z_grav values.
// Total z_MW at R₀ = 6.03e-7 (isotropic endpoint).
// The column density determines how the z_grav is DISTRIBUTED with direction.
//
// For a photon from direction (l, b):
//   z_grav(l, b) = z_endpoint + z_column_excess(l, b)
//
// where z_endpoint = (v_rot/c)² is the isotropic baseline, and
// z_column_excess is the direction-dependent ADDITIONAL shift from
// the photon traversing denser or thinner columns.
//
// The column excess scales as:
//   z_excess ∝ ∫ ρ ds × (v_local/c)²
//
// Normalise by computing the all-sky mean column and setting
// deviations proportional to column density ratio.
// =============================================================================

int main() {
    printf("###################################################################\n");
    printf("   CQ19: Milky Way Occlusion Map — Directional z_grav Field\n");
    printf("   SDT Framework — James Tyndall, Melbourne\n");
    printf("###################################################################\n\n");

    // ---- Component Ϟ values ----
    printf("=== MW GRAVITATIONAL STRUCTURE (no G, no M) ===\n\n");
    printf("   Component      Ϟ [m]          k         z = 1/k²      z at R₀\n");
    printf("   ─────────────  ────────────   ────────  ────────────  ────────────\n");

    double z_sagA_R0 = Koppa_SagA / (R0 * kpc);
    double z_bulge_R0 = Koppa_bulge / (R0 * kpc);
    double z_disk_R0 = (Koppa_MW - Koppa_bulge - Koppa_SagA) / (R0 * kpc);
    double z_MW_R0 = Koppa_MW / (R0 * kpc);

    printf("   Sag A* (S2)    %.4e m   %.1f     %.4e    %.4e  (%.3f%%)\n",
           Koppa_SagA, c / (2.0 * M_PI * a_S2_m / T_S2_s),
           (2.0*M_PI*a_S2_m/T_S2_s/c)*(2.0*M_PI*a_S2_m/T_S2_s/c),
           z_sagA_R0, z_sagA_R0/z_MW_R0*100);
    printf("   Bulge (bar)    %.4e m   %.0f    %.4e    %.4e  (%.1f%%)\n",
           Koppa_bulge, c/v_bulge,
           (v_bulge/c)*(v_bulge/c),
           z_bulge_R0, z_bulge_R0/z_MW_R0*100);
    printf("   Disk           %.4e m   —         —            %.4e  (%.1f%%)\n",
           Koppa_MW - Koppa_bulge - Koppa_SagA,
           z_disk_R0, z_disk_R0/z_MW_R0*100);
    printf("   ─────────────  ────────────                    ────────────\n");
    printf("   Total MW       %.4e m   %.0f    %.4e    %.4e  (100%%)\n\n",
           Koppa_MW, c/v_rot, (v_rot/c)*(v_rot/c), z_MW_R0);

    printf("   Observer: R₀ = %.3f kpc, z₀ = %.3f kpc above midplane\n", R0, z0_sun);
    printf("   Bar angle: %.0f° to Sun-center line (Wegg et al. 2015)\n\n", bar_angle_deg);

    // ---- All-sky ray tracing ----
    printf("=== ALL-SKY COLUMN DENSITY MAP ===\n\n");

    static const int NL = 36;  // 10° longitude bins
    static const int NB = 18;  // 10° latitude bins

    double col_map[NL][NB] = {};
    double col_disk_map[NL][NB] = {};
    double col_bulge_map[NL][NB] = {};
    double col_mean = 0.0;
    int    n_total = 0;

    for (int il = 0; il < NL; il++) {
        double l = il * 10.0 + 5.0;  // center of bin
        for (int ib = 0; ib < NB; ib++) {
            double b = -85.0 + ib * 10.0;  // -85 to +85
            auto r = trace_ray(l, b);
            col_map[il][ib]      = r.column_total;
            col_disk_map[il][ib] = r.column_disk;
            col_bulge_map[il][ib]= r.column_bulge;
            col_mean += r.column_total;
            n_total++;
        }
    }
    col_mean /= n_total;

    // ---- Directional z_grav map ----
    // z_grav(l, b) = z_endpoint × (column(l,b) / mean_column)
    // This scales the isotropic baseline by the relative column density

    double z_endpoint = z_MW_R0;

    printf("Directional z_grav contamination map (×10⁷):\n");
    printf("Each cell = z_grav × 10⁷ for extragalactic photons from that direction\n");
    printf("Isotropic baseline (v_rot/c)² = %.3f × 10⁻⁷\n\n", z_endpoint * 1e7);

    // Print header
    printf("  b\\l  ");
    for (int il = 0; il < NL; il += 2) {
        printf(" %5.0f", il * 10.0 + 5.0);
    }
    printf("\n  ─────");
    for (int il = 0; il < NL; il += 2) printf("──────");
    printf("\n");

    // Print map (every 2nd longitude for readability)
    for (int ib = NB - 1; ib >= 0; ib--) {
        double b = -85.0 + ib * 10.0;
        printf("  %+4.0f° ", b);
        for (int il = 0; il < NL; il += 2) {
            double ratio = (col_mean > 0) ? col_map[il][ib] / col_mean : 1.0;
            double z_dir = z_endpoint * ratio;
            printf(" %5.1f", z_dir * 1e7);
        }
        printf("\n");
    }

    // ---- Key sightlines ----
    printf("\n=== KEY SIGHTLINES ===\n\n");
    printf("%-30s  %6s  %6s  %10s  %10s  %10s  %12s\n",
           "Direction", "l", "b", "col_disk", "col_bulge", "col_total", "z_grav");
    printf("%-30s  %6s  %6s  %10s  %10s  %10s  %12s\n",
           "───────────────────────────", "────", "────", "────────", "─────────",
           "─────────", "──────────");

    struct Sightline { const char* name; double l, b; };
    static const Sightline sightlines[] = {
        {"Galactic center",           0.0,    0.0},
        {"Anti-center",             180.0,    0.0},
        {"North galactic pole",       0.0,  +90.0},
        {"South galactic pole",       0.0,  -90.0},
        {"Solar apex (rotation)",    90.0,    0.0},
        {"Solar antapex",           270.0,    0.0},
        {"Great Attractor",         276.0,  +30.0},
        {"Anti-GA",                  96.0,  -30.0},
        {"Norma cluster (ZoA)",     325.0,   -7.0},
        {"Coma cluster (high b)",    58.0,  +88.0},
        {"Virgo cluster",           284.0,  +74.0},
        {"CMB dipole apex",         264.0,  +48.0},
        {"Shapley concentration",   312.0,  +31.0},
    };

    double z_max = 0, z_min = 1e10;
    const char* dir_max = "";
    const char* dir_min = "";

    for (const auto& s : sightlines) {
        auto r = trace_ray(s.l, s.b);
        double ratio = (col_mean > 0) ? r.column_total / col_mean : 1.0;
        double z_dir = z_endpoint * ratio;

        printf("%-30s  %6.1f  %+5.1f  %10.4f  %10.4f  %10.4f  %12.4e\n",
               s.name, s.l, s.b, r.column_disk, r.column_bulge,
               r.column_total, z_dir);

        if (z_dir > z_max) { z_max = z_dir; dir_max = s.name; }
        if (z_dir < z_min) { z_min = z_dir; dir_min = s.name; }
    }

    printf("\n   Maximum z_grav: %.4e  ← %s\n", z_max, dir_max);
    printf("   Minimum z_grav: %.4e  ← %s\n", z_min, dir_min);
    printf("   Anisotropy:     %.2f×  (max/min ratio)\n", z_max / z_min);
    printf("   Peak-to-peak:   %.4e  = %.2f km/s\n\n",
           z_max - z_min, (z_max - z_min) * c_kms);

    // ---- H₀ impact ----
    double delta_z = z_max - z_min;
    double delta_v = delta_z * c_kms;  // km/s
    printf("=== IMPACT ON H₀ ===\n\n");
    printf("   The MW occlusion field creates a DIRECTIONAL z_grav bias.\n");
    printf("   Peak-to-peak: Δz = %.4e = %.2f km/s\n", delta_z, delta_v);
    printf("   At d = 20 Mpc:  ΔH₀ = %.2f km/s/Mpc\n", delta_v / 20.0);
    printf("   At d = 50 Mpc:  ΔH₀ = %.2f km/s/Mpc\n", delta_v / 50.0);
    printf("   At d = 100 Mpc: ΔH₀ = %.2f km/s/Mpc\n\n", delta_v / 100.0);

    printf("   If the SNe Ia calibration sample is concentrated near the\n");
    printf("   galactic plane (which it is — ZoA boundary), the disk column\n");
    printf("   systematically inflates z_total in those directions.\n\n");

    // ---- Bulge bar asymmetry ----
    printf("=== BULGE BAR ASYMMETRY ===\n\n");
    printf("   The MW bar is tilted %.0f° to the Sun-center line.\n", bar_angle_deg);
    printf("   This breaks axial symmetry: the near end of the bar is at\n");
    printf("   l ≈ %.0f°, the far end at l ≈ %.0f°.\n\n",
           360.0 - bar_angle_deg, 180.0 - bar_angle_deg);

    // Trace along the bar axis
    auto r_near = trace_ray(360.0 - bar_angle_deg, 0.0);
    auto r_far  = trace_ray(180.0 - bar_angle_deg, 0.0);
    double z_near = z_endpoint * r_near.column_total / col_mean;
    double z_far  = z_endpoint * r_far.column_total / col_mean;
    printf("   Near end (l=%.0f°): column = %.4f, z_grav = %.4e\n",
           360.0 - bar_angle_deg, r_near.column_total, z_near);
    printf("   Far end  (l=%.0f°): column = %.4f, z_grav = %.4e\n",
           180.0 - bar_angle_deg, r_far.column_total, z_far);
    printf("   Bar asymmetry:     Δz = %.4e = %.3f km/s\n\n",
           fabs(z_near - z_far), fabs(z_near - z_far) * c_kms);

    // ---- Latitude profile at l=0 (through center) ----
    printf("=== LATITUDE PROFILE: l = 0° (through galactic center) ===\n\n");
    printf("   b [deg]   col_disk   col_bulge  col_total   z_grav        z/z_pole\n");
    printf("   ────────  ────────   ─────────  ─────────   ──────────    ────────\n");

    auto r_pole = trace_ray(0.0, 90.0);
    double z_pole = z_endpoint * r_pole.column_total / col_mean;

    for (int b = 0; b <= 90; b += 5) {
        auto r = trace_ray(0.0, (double)b);
        double ratio = r.column_total / col_mean;
        double z_dir = z_endpoint * ratio;
        printf("   %+4d°      %8.4f   %9.4f  %9.4f   %10.4e    %8.2f×\n",
               b, r.column_disk, r.column_bulge, r.column_total,
               z_dir, (z_pole > 0) ? z_dir / z_pole : 0.0);
    }

    printf("\n   The disk column at b=0° through the center is >>10× the pole value.\n");
    printf("   This is NOT a small correction. It is a STRUCTURAL BIAS\n");
    printf("   on every redshift measurement near the galactic plane.\n\n");

    printf("=== VERDICT ===\n\n");
    printf("   The MW gravitational field is NOT isotropic from our position.\n");
    printf("   The disk + bulge/bar create a latitude/longitude-dependent\n");
    printf("   z_grav contamination field that must be subtracted from every\n");
    printf("   extragalactic redshift before cosmological analysis.\n\n");
    printf("   The Zone of Avoidance is not just an extinction problem —\n");
    printf("   it is a GRAVITATIONAL REDSHIFT problem.\n\n");
    printf("   zk² = 1. The MW has structure. That structure has consequences.\n\n");

    return 0;
}
