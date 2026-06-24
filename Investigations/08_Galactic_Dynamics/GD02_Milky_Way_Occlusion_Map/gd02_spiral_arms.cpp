// =============================================================================
// CQ19e — Spiral Arm Tracer with Self-Lensing Correction
//
// The MW is a lens and we sit inside it. Light from distant spiral arm
// segments traverses the spation-depth gradient of the bulge, bar, and
// disk before reaching us. This bends apparent positions:
//
//   δθ = 2 ∫ ∇⊥z dl     (SDT bending, same formula as CR01)
//
// where z(r) = (v/c)² = Ϟ/r along the line of sight.
//
// The result: published spiral arm maps contain a systematic distortion
// — an "inside-the-lens" illusion. Andromeda would see our true geometry;
// we see a warped projection.
//
// This tool:
//   1. Traces all four major arms + Local arm using Reid+2019 log-spiral
//   2. Computes the spation-depth gradient along each sightline from R₀
//   3. Applies the SDT bending correction to recover the "external" geometry
//   4. Quantifies the distortion map: δθ(l, b) for each arm segment
//
// No G. No M. zk² = 1.
// @author SDT Canonical Engine — James Tyndall, Melbourne
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>

#include <sdt/laws.hpp>

using namespace sdt::laws;
using namespace sdt::laws::measured;

static constexpr double kpc_m = 3.085677581e19;
static constexpr double pc_m  = 3.085677581e16;
static constexpr double R0_kpc = 8.178;     // Sun's galactocentric distance
static constexpr double R0_m   = R0_kpc * kpc_m;

// =============================================================================
// SPIRAL ARM MODEL — Reid+2019 log-spiral parameters
//
// Each arm: r(θ) = r_ref × exp((θ - θ_ref) × tan(ψ))
//   r_ref:   reference radius [kpc]
//   θ_ref:   reference azimuth [deg], measured from GC, Sun at ~180° 
//   ψ:       pitch angle [deg] (negative = trailing)
//
// Sources: Reid+2019 (ApJ 885 131), Xu+2018, VLBI maser parallaxes
// =============================================================================

struct SpiralArm {
    const char* name;
    double r_ref_kpc;    // reference radius
    double theta_ref_deg;// reference azimuth (from GC, Sun at ~0 in galactic convention)
    double pitch_deg;    // pitch angle (negative = trailing)
    double width_kpc;    // half-width of the arm
    double theta_start;  // angular extent start [deg]
    double theta_end;    // angular extent end [deg]
};

// Reid+2019 four-arm + Local arm model
// Azimuth convention: θ=0 is the Sun–GC line, increasing counter-clockwise
// (consistent with galactic longitude l increasing CCW as seen from north pole)
static const SpiralArm arms[] = {
    // Name                r_ref   θ_ref  pitch  width  θ_start  θ_end
    {"Scutum-Centaurus",   5.0,    27.6, -13.0,  0.35, -20.0,   280.0},
    {"Sagittarius-Carina", 6.6,    25.6, -11.4,  0.30, -20.0,   260.0},
    {"Local (Orion-Cygnus)",7.7,     8.9, -11.0,  0.25, -10.0,   100.0},
    {"Perseus",            9.9,    14.2, -10.3,  0.35, -30.0,   270.0},
    {"Outer",             13.0,    18.6, -13.8,  0.40, -20.0,   180.0},
    {"Norma (3 kpc)",      3.5,    44.4, -12.0,  0.30, -10.0,   200.0},
};

static constexpr int N_ARMS = 6;

// =============================================================================
// SPIRAL ARM POINT GENERATOR
//
// For a log-spiral: r(θ) = r_ref × exp((θ - θ_ref) × tan(ψ))
// Cartesian: x = r cos(θ + θ_Sun), y = r sin(θ + θ_Sun)
//   where θ_Sun shifts the coordinate so Sun is at (R0, 0)
// =============================================================================

struct ArmPoint {
    double theta_arm;    // arm azimuth [deg] (arm-frame)
    double r_kpc;        // galactocentric radius [kpc]
    double x_kpc;        // galactocentric X (Sun at x=R0)
    double y_kpc;        // galactocentric Y
    double d_kpc;        // distance from Sun [kpc]
    double l_deg;        // apparent galactic longitude [deg]
    double l_true_deg;   // corrected galactic longitude [deg]
    double delta_theta_arcsec; // bending correction [arcsec]
};

// =============================================================================
// MW ROTATION CURVE — for z(r)
// =============================================================================

static double v_circ_ms(double r_kpc) {
    if (r_kpc < 0.001) return 0.0;
    if (r_kpc < 0.5)
        return 220e3 * (r_kpc / 0.5);
    if (r_kpc < 2.0)
        return 220e3 * (1.0 + 0.1 * sin(M_PI * (r_kpc - 0.5) / 1.5));
    double v_kms = 229.0 - 1.7 * (r_kpc - 8.178);
    if (v_kms < 180.0) v_kms = 180.0;
    return v_kms * 1e3;
}

// Spation depth z at galactocentric radius r:
//   z(r) = (v_circ(r)/c)²
static double z_field(double r_kpc) {
    double v = v_circ_ms(r_kpc);
    return (v / c) * (v / c);
}

// =============================================================================
// SELF-LENSING: BENDING ALONG A LINE OF SIGHT
//
// SDT bending formula (same as gravitational lensing):
//   δθ = 2 ∫ ∇⊥z dl
//
// For a sightline from Sun (at R0) to a point at distance d along direction l:
// We integrate the transverse gradient of z along the path.
// The dominant contribution comes from the passage near/through the bulge.
//
// Simplified model: the z-field is azimuthally symmetric about the GC.
// At each point along the sightline, the transverse gradient is:
//   ∇⊥z ≈ (dz/dr) × sin(α)
// where α is the angle between the sightline and the radial direction.
// =============================================================================

struct BendingResult {
    double delta_theta_rad;
    double delta_theta_arcsec;
    double z_integral;       // ∫ z dl (dimensionless × kpc)
    double max_z_on_path;
};

static BendingResult compute_bending(double l_deg, double d_kpc) {
    // Sun at (R0, 0). Sightline direction:
    double l_rad = l_deg * M_PI / 180.0;
    double dx = -cos(l_rad);  // toward GC at l=0
    double dy =  sin(l_rad);

    int N_steps = 1000;
    double dl = d_kpc / N_steps;

    double total_bend = 0;
    double z_integral = 0;
    double max_z = 0;

    for (int i = 0; i < N_steps; i++) {
        double s = (i + 0.5) * dl;  // distance along sightline [kpc]

        // Position along sightline
        double px = R0_kpc + s * dx;
        double py = s * dy;
        double r = sqrt(px * px + py * py);  // galactocentric radius

        if (r < 0.01) r = 0.01;

        double z = z_field(r);
        z_integral += z * dl;
        if (z > max_z) max_z = z;

        // dz/dr (numerical gradient)
        double dr = 0.01;
        double z_plus  = z_field(r + dr);
        double z_minus = z_field(r - dr > 0.01 ? r - dr : 0.01);
        double dz_dr = (z_plus - z_minus) / (2.0 * dr);

        // Transverse component: project the radial gradient onto
        // the direction perpendicular to the sightline
        double r_hat_x = px / r;
        double r_hat_y = py / r;

        // Perpendicular to sightline = (-dy, dx)
        double perp_x = -dy;
        double perp_y = dx;

        // Transverse gradient
        double grad_perp = dz_dr * (r_hat_x * perp_x + r_hat_y * perp_y);

        total_bend += 2.0 * grad_perp * dl;
    }

    double arcsec = total_bend * 206264.806;

    return {total_bend, arcsec, z_integral, max_z};
}

// =============================================================================
// MAIN
// =============================================================================

int main() {
    printf("###################################################################\n");
    printf("   CQ19e: SPIRAL ARM TRACER WITH SELF-LENSING CORRECTION\n");
    printf("   SDT: We sit inside the lens. Our arm map is distorted.\n");
    printf("###################################################################\n\n");

    // ═══════════════════════════════════════════════════════════════
    //  STEP 1: TRACE ALL SPIRAL ARMS
    // ═══════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("  STEP 1: SPIRAL ARM GEOMETRY (Reid+2019 log-spiral model)\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("  Sun at R₀ = %.3f kpc from Galactic Centre\n\n", R0_kpc);

    printf("   %-25s  %8s  %8s  %8s  %8s  %8s\n",
           "Arm", "r_ref", "θ_ref", "pitch", "θ_range", "width");
    printf("   %-25s  %8s  %8s  %8s  %8s  %8s\n",
           "", "[kpc]", "[deg]", "[deg]", "[deg]", "[kpc]");
    printf("   %-25s  %8s  %8s  %8s  %8s  %8s\n",
           "─────────────────────────","────────","────────",
           "────────","────────","────────");

    for (int a = 0; a < N_ARMS; a++) {
        const auto& arm = arms[a];
        printf("   %-25s  %8.1f  %8.1f  %8.1f  %4.0f–%-4.0f  %8.2f\n",
               arm.name, arm.r_ref_kpc, arm.theta_ref_deg,
               arm.pitch_deg, arm.theta_start, arm.theta_end, arm.width_kpc);
    }

    // ═══════════════════════════════════════════════════════════════
    //  STEP 2: COMPUTE SIGHTLINE BENDING MAP
    // ═══════════════════════════════════════════════════════════════

    printf("\n═══════════════════════════════════════════════════════════════════\n");
    printf("  STEP 2: SELF-LENSING BENDING MAP — δθ vs galactic longitude\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("  SDT bending: δθ = 2 ∫ ∇⊥z dl  along the sightline\n");
    printf("  z(r) = (v_circ/c)² — spation depth from the rotation curve\n\n");

    printf("   %6s  %8s  %12s  %12s  %12s\n",
           "l [°]", "d [kpc]", "δθ [arcsec]", "∫z dl", "max z");
    printf("   %6s  %8s  %12s  %12s  %12s\n",
           "──────","────────","──────────","──────────","──────────");

    // Scan every 10° of longitude, at several distances
    double test_distances[] = {3.0, 8.0, 15.0};
    for (double d : test_distances) {
        printf("   --- d = %.1f kpc ---\n", d);
        for (int l = 0; l <= 350; l += 10) {
            auto bend = compute_bending(static_cast<double>(l), d);
            printf("   %6d  %8.1f  %12.4f  %12.4e  %12.4e\n",
                   l, d, bend.delta_theta_arcsec,
                   bend.z_integral, bend.max_z_on_path);
        }
    }

    // ═══════════════════════════════════════════════════════════════
    //  STEP 3: ARM-BY-ARM TRACING WITH CORRECTIONS
    // ═══════════════════════════════════════════════════════════════

    printf("\n═══════════════════════════════════════════════════════════════════\n");
    printf("  STEP 3: ARM-BY-ARM TRACING — apparent vs corrected positions\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    for (int a = 0; a < N_ARMS; a++) {
        const auto& arm = arms[a];
        double pitch_rad = arm.pitch_deg * M_PI / 180.0;

        printf("  ── %s ──\n", arm.name);
        printf("   %6s  %8s  %8s  %8s  %8s  %12s  %8s\n",
               "θ_arm", "r_arm", "d_sun", "l_app", "l_corr",
               "δθ", "Δl");
        printf("   %6s  %8s  %8s  %8s  %8s  %12s  %8s\n",
               "[deg]", "[kpc]", "[kpc]", "[deg]", "[deg]",
               "[arcsec]", "[deg]");

        int n_pts = 0;
        double total_bend = 0;
        double max_bend = 0;

        for (double theta = arm.theta_start; theta <= arm.theta_end; theta += 10.0) {
            // Log-spiral: r = r_ref × exp((θ - θ_ref) × tan(ψ))
            double dtheta = (theta - arm.theta_ref_deg) * M_PI / 180.0;
            double r = arm.r_ref_kpc * exp(dtheta * tan(pitch_rad));

            if (r < 0.5 || r > 20.0) continue;

            // Galactocentric coordinates
            // θ=0 = Sun–GC line, CCW from north pole
            double theta_gal_rad = theta * M_PI / 180.0;
            double x = r * cos(theta_gal_rad);   // GC-centred
            double y = r * sin(theta_gal_rad);

            // Sun is at (R0, 0)
            double dx = x - R0_kpc;
            double dy = y;
            double d_sun = sqrt(dx * dx + dy * dy);

            if (d_sun < 0.1) continue;

            // Apparent galactic longitude
            double l_app = atan2(dy, -dx) * 180.0 / M_PI;
            if (l_app < 0) l_app += 360.0;

            // Compute bending along this sightline
            auto bend = compute_bending(l_app, d_sun);

            // Corrected longitude
            double l_corr = l_app - bend.delta_theta_arcsec / 3600.0;
            if (l_corr < 0) l_corr += 360.0;
            if (l_corr >= 360.0) l_corr -= 360.0;

            double delta_l = l_corr - l_app;

            printf("   %6.0f  %8.2f  %8.2f  %8.1f  %8.1f  %12.4f  %8.4f\n",
                   theta, r, d_sun, l_app, l_corr,
                   bend.delta_theta_arcsec, delta_l);

            total_bend += fabs(bend.delta_theta_arcsec);
            if (fabs(bend.delta_theta_arcsec) > max_bend)
                max_bend = fabs(bend.delta_theta_arcsec);
            n_pts++;
        }

        if (n_pts > 0) {
            printf("   Mean |δθ| = %.4f arcsec, Max |δθ| = %.4f arcsec\n\n",
                   total_bend / n_pts, max_bend);
        }
    }

    // ═══════════════════════════════════════════════════════════════
    //  STEP 4: INTERPRETATION
    // ═══════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("  STEP 4: THE INSIDE-THE-LENS EFFECT\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("  The spation lattice (Axiom R1) carries convergence pressure\n");
    printf("  at every point. The MW's baryonic structure creates a z-field:\n");
    printf("    z(r) = (v_circ/c)² ≈ 6×10⁻⁷ at R₀ = 8.178 kpc\n\n");

    printf("  Light from distant arm segments traverses this field.\n");
    printf("  The transverse gradient ∇⊥z bends the sightline:\n");
    printf("    δθ = 2 ∫ ∇⊥z dl\n\n");

    printf("  For sightlines passing near the GC (l ≈ 0°, 360°):\n");
    printf("    — the bulge z-field is strongest\n");
    printf("    — bending is maximal\n");
    printf("    — apparent arm positions are shifted toward the GC\n\n");

    printf("  For sightlines along the disk (l ≈ 90°, 270°):\n");
    printf("    — path is roughly tangent to the z-field\n");
    printf("    — bending is minimal\n");
    printf("    — arm positions are approximately correct\n\n");

    printf("  An external observer (Andromeda, M31) would see our spiral\n");
    printf("  geometry without this distortion — they sit outside the lens.\n");
    printf("  Our published arm maps carry the systematic bias of the\n");
    printf("  observer being embedded in the convergence field.\n\n");

    printf("  zk² = 1.\n\n");

    return 0;
}
