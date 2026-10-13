// =============================================================================
// Saturn Gradient Dominance Check
//
// Question: Does Saturn's own convergence gradient exceed the Sun's gradient
//           at Saturn's orbital distance?
//
// SDT gradient: dz/dr = -2 v_surface^2 R / (c^2 r^2) = -2 koppa / r^2
//
// Compare: dz/dr|_Saturn_surface  vs  dz/dr|_Sun_at_Saturn_orbit
//
// @author SDT Canonical Engine — James Tyndall, Melbourne
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>

int main() {
    // Fundamental
    constexpr double c = 299792458.0;

    // Sun parameters
    constexpr double R_Sun    = 6.957e8;      // [m]
    constexpr double v_Sun    = 436762.0;      // [m/s] surface orbital velocity
    constexpr double k_Sun    = c / v_Sun;     // ~686.3
    constexpr double koppa_Sun = v_Sun * v_Sun * R_Sun / (c * c);  // ~1477 m

    // Saturn parameters
    constexpr double R_Saturn = 5.8232e7;      // [m] equatorial radius
    constexpr double v_Saturn = 25087.4;       // [m/s] surface orbital velocity
    constexpr double k_Saturn = c / v_Saturn;  // ~11,951
    constexpr double koppa_Saturn = v_Saturn * v_Saturn * R_Saturn / (c * c);

    // Saturn's orbital distance from the Sun
    constexpr double d_Saturn = 9.5826 * 1.496e11;  // ~9.58 AU in metres

    // z values (spation depth)
    constexpr double z_Sun    = 1.0 / (k_Sun * k_Sun);
    constexpr double z_Saturn = 1.0 / (k_Saturn * k_Saturn);

    // ─── GRADIENT COMPARISON ───
    //
    // The z-gradient (convergence pressure gradient) around a body:
    //   dz/dr = d/dr [ (v_surf^2 R) / (c^2 r) ] = - v_surf^2 R / (c^2 r^2)
    //         = - koppa / r^2
    //
    // At Saturn's surface, Saturn's own gradient:
    //   |dz/dr|_Saturn = koppa_Saturn / R_Saturn^2
    //
    // At Saturn's orbital distance, Sun's gradient:
    //   |dz/dr|_Sun = koppa_Sun / d_Saturn^2

    double grad_Saturn_surface = koppa_Saturn / (R_Saturn * R_Saturn);
    double grad_Sun_at_Saturn  = koppa_Sun / (d_Saturn * d_Saturn);

    double ratio = grad_Saturn_surface / grad_Sun_at_Saturn;

    // Surface gravitational acceleration comparison
    double g_Saturn = v_Saturn * v_Saturn / R_Saturn;
    double g_Sun_at_Saturn = v_Sun * v_Sun * R_Sun / (d_Saturn * d_Saturn);

    printf("================================================================\n");
    printf("  SATURN GRADIENT DOMINANCE CHECK\n");
    printf("================================================================\n\n");

    printf("── Sun ──\n");
    printf("  v_surface       = %.1f m/s\n", v_Sun);
    printf("  k               = %.2f\n", k_Sun);
    printf("  z               = %.6e\n", z_Sun);
    printf("  koppa           = %.2f m\n\n", koppa_Sun);

    printf("── Saturn ──\n");
    printf("  v_surface       = %.1f m/s\n", v_Saturn);
    printf("  k               = %.2f\n", k_Saturn);
    printf("  z               = %.6e\n", z_Saturn);
    printf("  koppa           = %.6f m\n", koppa_Saturn);
    printf("  R_Saturn        = %.4e m\n\n", R_Saturn);

    printf("── Saturn orbital distance ──\n");
    printf("  d_Saturn        = %.4e m (%.2f AU)\n\n", d_Saturn, d_Saturn / 1.496e11);

    printf("── Gradient comparison ──\n");
    printf("  |dz/dr| at Saturn's surface (Saturn's own):\n");
    printf("    = koppa_Saturn / R_Saturn^2\n");
    printf("    = %.6e / (%.4e)^2\n", koppa_Saturn, R_Saturn);
    printf("    = %.6e m^-1\n\n", grad_Saturn_surface);

    printf("  |dz/dr| at Saturn's orbit (Sun's):\n");
    printf("    = koppa_Sun / d_Saturn^2\n");
    printf("    = %.2f / (%.4e)^2\n", koppa_Sun, d_Saturn);
    printf("    = %.6e m^-1\n\n", grad_Sun_at_Saturn);

    printf("  ╔═══════════════════════════════════════════════════════╗\n");
    printf("  ║  RATIO = Saturn_grad / Sun_grad = %.4f             ║\n", ratio);
    printf("  ║  Saturn's gradient is %.1f%% of the Sun's           ║\n", ratio * 100.0);
    if (ratio > 1.0) {
        printf("  ║  Saturn DOMINATES the Sun at its own surface        ║\n");
        printf("  ║  Excess: +%.1f%% above solar gradient               ║\n", (ratio - 1.0) * 100.0);
    } else {
        printf("  ║  Sun still dominates at Saturn's surface            ║\n");
    }
    printf("  ╚═══════════════════════════════════════════════════════╝\n\n");

    // g-force comparison
    printf("── Surface gravity comparison ──\n");
    printf("  g_Saturn (own surface)      = %.3f m/s^2\n", g_Saturn);
    printf("  g_Sun (at Saturn's orbit)   = %.6e m/s^2\n", g_Sun_at_Saturn);
    printf("  g_ratio = %.2f\n\n", g_Saturn / g_Sun_at_Saturn);

    // Magnetopause argument: if Saturn's gradient dominates,
    // the solar wind pressure gradient is weaker than Saturn's own
    // convergence gradient → Saturn's wake (magnetic field) can
    // extend further without being compressed
    printf("── Magnetosphere implications ──\n");
    printf("  If gradient_ratio > 1:\n");
    printf("    Saturn's convergence field exceeds the Sun's at its surface.\n");
    printf("    The solar wind encounters a body whose own pressure gradient\n");
    printf("    is steeper than the gradient it's flowing down.\n");
    printf("    → Saturn's wake (magnetic field) expands into a weaker\n");
    printf("      opposing gradient.\n");
    printf("    → Rings can persist: lighter particles in the equatorial\n");
    printf("      plane are protected from solar wind erosion.\n\n");

    // Compare with other planets
    struct Planet {
        const char* name;
        double v_surface;
        double R;
        double d_orbit;
    };

    Planet planets[] = {
        {"Mercury", 3010.0,   2.440e6, 0.387 * 1.496e11},
        {"Venus",   7326.0,   6.052e6, 0.723 * 1.496e11},
        {"Earth",   7909.0,   6.371e6, 1.000 * 1.496e11},
        {"Mars",    3555.0,   3.390e6, 1.524 * 1.496e11},
        {"Jupiter", 42100.0,  6.991e7, 5.203 * 1.496e11},
        {"Saturn",  25087.4,  5.823e7, 9.537 * 1.496e11},
        {"Uranus",  15060.0,  2.536e7, 19.19 * 1.496e11},
        {"Neptune", 16700.0,  2.462e7, 30.07 * 1.496e11},
    };

    printf("── All planets: gradient ratio (planet / Sun at orbit) ──\n\n");
    printf("  %-10s  %10s  %12s  %12s  %10s  %s\n",
           "Planet", "v*", "koppa [m]", "grad_planet", "grad_Sun", "ratio");
    printf("  %-10s  %10s  %12s  %12s  %10s  %s\n",
           "──────────", "──────────", "────────────", "────────────", "──────────", "──────");

    for (auto& p : planets) {
        double kop = p.v_surface * p.v_surface * p.R / (c * c);
        double gp = kop / (p.R * p.R);
        double gs = koppa_Sun / (p.d_orbit * p.d_orbit);
        double r = gp / gs;
        printf("  %-10s  %10.1f  %12.6e  %12.4e  %10.4e  %8.2f  %s\n",
               p.name, p.v_surface, kop, gp, gs, r,
               (r > 1.0) ? "DOMINATES" : "");
    }

    printf("\n");
    return 0;
}
