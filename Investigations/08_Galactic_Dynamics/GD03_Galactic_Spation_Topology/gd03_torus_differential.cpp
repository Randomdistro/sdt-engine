// =============================================================================
// CQ20c — Torus Differential Rotation: Keplerian Profile
//
// The proton IS the torus. R_p = 0.84 fm is the proton's radius.
// SDT Keplerian: v(r) = v_surface × sqrt(R_surface / r) from the axis.
//
// What is the velocity at the inner circumference?
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <sdt/laws.hpp>

using namespace sdt::laws;
using namespace sdt::laws::measured;

static constexpr double r_s = l_P / 2.0;

int main() {
    printf("###################################################################\n");
    printf("   CQ20c: Proton Torus Differential Rotation\n");
    printf("   The proton IS the torus. R_p = 0.84 fm.\n");
    printf("###################################################################\n\n");

    // The proton charge radius R_p = 0.84 fm is the measured extent.
    // For a torus: R = major radius, r = minor (tube) radius.
    // We explore: what if R_p is the major radius?
    // Then the tube radius r < R_p.

    // The proton surface velocity at the OUTER equator = 1.831c.
    double v_surface = 1.831 * c;

    printf("=== PROTON SCALES ===\n\n");
    printf("   R_p              = %.4e m  (0.84 fm — the proton)\n", R_p);
    printf("   R_p / r_s        = %.4e    (spations across)\n", R_p / r_s);
    printf("   v_surface        = %.4fc = %.6e m/s\n\n", 1.831, v_surface);

    // ============================================================
    // SCENARIO: R_p is the major radius of the torus.
    // Tube radius r is a free parameter — try several.
    // ============================================================

    printf("=== KEPLERIAN VELOCITY AT INNER EQUATOR ===\n");
    printf("   v(r) = v_outer × sqrt(r_outer / r)  from torus axis\n\n");

    printf("   %-12s  %10s  %10s  %10s  %10s  %10s  %10s\n",
           "r/R ratio", "R [m]", "r_tube [m]",
           "r_outer", "r_inner", "v_inner/c", "v_outer/c");
    printf("   %-12s  %10s  %10s  %10s  %10s  %10s  %10s\n",
           "--------", "------", "--------",
           "-------", "-------", "---------", "---------");

    double R_major = R_p;

    double ratios[] = {0.1, 0.2, 0.25, 1.0/3.0, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
    int nr = 10;

    for (int i = 0; i < nr; i++) {
        double frac = ratios[i];
        double r_tube = frac * R_major;
        double r_outer = R_major + r_tube;
        double r_inner = R_major - r_tube;

        // v_surface = 1.831c is at the outer equator (r = R + r_tube)
        double v_inner = v_surface * std::sqrt(r_outer / r_inner);
        double v_mid   = v_surface * std::sqrt(r_outer / R_major);

        printf("   r/R = %.3f     %10.3e  %10.3e  %10.3e  %10.3e  %10.4f  %10.4f\n",
               frac, R_major, r_tube, r_outer, r_inner, v_inner/c, v_surface/c);
    }

    // ============================================================
    // DETAILED CROSS-SECTION for r/R = 1/3 (a reasonable trefoil)
    // ============================================================
    printf("\n=== DETAILED CROSS-SECTION: r_tube = R_p / 3 ===\n\n");

    double r_tube = R_major / 3.0;
    double r_outer = R_major + r_tube;
    double r_inner = R_major - r_tube;

    printf("   R (major)  = %.4e m\n", R_major);
    printf("   r (tube)   = %.4e m  (= R_p/3)\n", r_tube);
    printf("   r_outer    = %.4e m  (= 4R_p/3)\n", r_outer);
    printf("   r_inner    = %.4e m  (= 2R_p/3)\n", r_inner);
    printf("   v_outer    = %.4f c  (at outer equator)\n\n", v_surface/c);

    printf("   %-16s  %6s  %12s  %8s  %12s\n",
           "Position", "theta", "r_axis [m]", "v/c", "k");
    printf("   %-16s  %6s  %12s  %8s  %12s\n",
           "--------", "-----", "----------", "---", "--");

    for (int deg = 0; deg <= 360; deg += 30) {
        double theta = deg * M_PI / 180.0;
        double r_ax = R_major + r_tube * std::cos(theta);

        double v_local = v_surface * std::sqrt(r_outer / r_ax);
        double k_local = c / v_local;

        const char* label = "";
        if (deg == 0)   label = "Outer equator";
        else if (deg == 90)  label = "Top";
        else if (deg == 180) label = "Inner equator";
        else if (deg == 270) label = "Bottom";
        else if (deg == 360) label = "Outer (= 0)";
        else {
            static char buf[12][32];
            snprintf(buf[deg/30], 32, "%d deg", deg);
            label = buf[deg/30];
        }

        printf("   %-16s  %4d    %12.4e  %8.4f  %12.6e\n",
               label, deg, r_ax, v_local/c, k_local);
    }

    // Key derived quantities
    double v_inner_val = v_surface * std::sqrt(r_outer / r_inner);
    double v_mid_val   = v_surface * std::sqrt(r_outer / R_major);
    double v_shear     = v_inner_val - v_surface;

    printf("\n=== KEY RESULTS ===\n\n");
    printf("   v_outer = %.6f c  (outer equator)\n", v_surface/c);
    printf("   v_mid   = %.6f c  (tube centre, on major C)\n", v_mid_val/c);
    printf("   v_inner = %.6f c  (inner equator)\n", v_inner_val/c);
    printf("\n");
    printf("   Differential: v_inner/v_outer = %.6f\n", v_inner_val/v_surface);
    printf("   Shear: v_inner - v_outer = %.6f c\n", v_shear/c);
    printf("   Angular vel: omega_in/omega_out = %.6f\n",
           (v_inner_val/r_inner) / (v_surface/r_outer));

    // Poloidal roll from shear
    double C_tube = 2.0 * M_PI * r_tube;
    double T_pol  = C_tube / std::abs(v_shear);
    double T_tor  = 2.0 * M_PI * R_major / v_mid_val;

    printf("\n   Poloidal roll period:  %.4e s\n", T_pol);
    printf("   Toroidal orbit period: %.4e s\n", T_tor);
    printf("   T_tor / T_pol = %.4f\n", T_tor / T_pol);
    printf("   (Trefoil (2,3) expects ratio related to 3/2)\n\n");

    // Surface spation count
    double S_torus = 4.0 * M_PI * M_PI * R_major * r_tube;
    double N_spat  = S_torus / (M_PI * r_s * r_s);

    printf("   Torus surface area:    %.4e m²\n", S_torus);
    printf("   Spations on surface:   %.4e\n", N_spat);
    printf("   Each at its local Keplerian velocity.\n\n");

    // ============================================================
    // SCAN: what r/R ratio gives trefoil winding 3:2?
    // ============================================================
    printf("=== TREFOIL RATIO SCAN ===\n");
    printf("   Looking for r/R where T_tor/T_pol = 3/2 = 1.500\n\n");

    for (int pct = 5; pct <= 95; pct += 5) {
        double f = pct / 100.0;
        double rt = f * R_major;
        double ro = R_major + rt;
        double ri = R_major - rt;
        double vi = v_surface * std::sqrt(ro / ri);
        double vm = v_surface * std::sqrt(ro / R_major);
        double sh = vi - v_surface;
        double Ct = 2.0 * M_PI * rt;
        double Tp = Ct / std::abs(sh);
        double Tt = 2.0 * M_PI * R_major / vm;
        double ratio = Tt / Tp;

        printf("   r/R = %.2f  ->  T_tor/T_pol = %.4f", f, ratio);
        if (std::abs(ratio - 1.5) < 0.05) printf("  <--- NEAR 3:2");
        printf("\n");
    }

    return 0;
}
