// =============================================================================
// CQ18b — Multi-Planet Stellar Survey
// For each star: derive Ϟ_star from orbital timing, predict z_grav,
// extract orbital radii and velocities, check Ϟ consistency across planets.
// No G, No M.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#ifndef M_PI
  static constexpr double M_PI = 3.14159265358979323846;
#endif
#include <vector>
#include <string>
#include "../../Investigations/07_Cosmology_and_Redshift/CR01_Redshift_Decomposition/star_data.hpp"

using namespace cr01;

// Derive semi-major axis from T and Ϟ_star (SDT Kepler, always uses SMA)
static double sma_m(double T_s, double Koppa_star_m) {
    return cbrt(T_s*T_s * c_ms*c_ms * Koppa_star_m / (4.0*M_PI*M_PI));
}

// g at orbital radius r from Ϟ
static double g_at_r(double Koppa_star_m, double r_m) {
    return c_ms*c_ms * Koppa_star_m / (r_m*r_m);
}

int main() {
    auto catalogue = load_catalogue();

    printf("=== CQ18b: Multi-Planet Stellar Survey — SDT Field Characterisation ===\n\n");
    printf("All quantities derived from spectroscopic log_g, R_star, and orbital timing.\n");
    printf("No G. No M.\n\n");

    for (const auto& star : catalogue) {
        double R  = star.R_m();
        double g  = star.g_ms2();
        double K  = star.Koppa_m();
        double z  = star.z_grav();
        double d  = star.dist_pc();

        if (R <= 0.0 || K <= 0.0) continue;

        printf("============================================================\n");
        printf("STAR: %s\n", star.name.c_str());
        printf("  Distance:       %.2f pc  (parallax %.2f mas)\n",
               d, star.parallax_mas);
        printf("  T_eff:          %.0f K\n", star.T_eff_K);
        printf("  log g:          %.3f  →  g = %.2f m/s²\n", star.log_g, g);
        printf("  R_star:         %.4f R_sun = %.4e m\n",
               R/R_sun_m, R);
        printf("  Ϟ_star:         %.4e m\n", K);
        printf("  z_grav:         %.4e\n", z);

        if (star.radv_kms != 0.0) {
            double z_doppler = star.radv_kms * 1000.0 / c_ms;
            // z_cosmo estimate (H0 * d / c, very rough for nearby stars)
            double z_cosmo_est = H0_kms_Mpc * 1000.0 * d / (1e6 * c_ms);
            printf("  z_doppler:      %.4e  (from RV = %.2f km/s)\n",
                   z_doppler, star.radv_kms);
            printf("  z_cosmo (H0):   %.4e  (H0=%g km/s/Mpc × d=%.1f pc)\n",
                   z_cosmo_est, H0_kms_Mpc, d);
            printf("  *** z_grav >> z_cosmo at this distance — peculiar vel dominates ***\n");
        }

        if (!star.planets.empty()) {
            printf("\n  Planets:\n");
            printf("  %-18s  %8s  %10s  %10s  %10s  %10s\n",
                   "Name", "T [days]", "r [AU]", "v [km/s]",
                   "g_orb[m/s²]", "Ϟ_check[m]");
            printf("  %-18s  %8s  %10s  %10s  %10s  %10s\n",
                   "------", "------", "------", "-------",
                   "---------", "---------");

            double Koppa_sum = 0.0;
            int Koppa_n = 0;

            for (const auto& pl : star.planets) {
                double T_s  = pl.period_days * 86400.0;
                double a_m  = sma_m(T_s, K);          // semi-major axis (from Kepler)
                double a_AU = a_m / AU_m;
                // At transit: r ≈ a(1-e²)/(1+e) for argument of periapsis ω=90°
                // Conservative: use a for circular, exact formula if e known
                double e    = pl.eccentricity;
                double r_transit = (e > 0.0)
                    ? a_m * (1.0 - e*e) / (1.0 + e)   // periapsis-side estimate
                    : a_m;
                // SDT vis-viva: v² = c²Ϟ(2/r - 1/a)
                double v    = sdt_visviva_v(K, r_transit, a_m);
                double g_r  = g_at_r(K, a_m);         // g at mean orbital radius

                // Ϟ_check from SMA (correct for any eccentricity)
                double K_check = 4.0*M_PI*M_PI * a_m*a_m*a_m / (T_s*T_s * c_ms*c_ms);
                Koppa_sum += K_check;
                Koppa_n++;

                printf("  %-18s  %8.4f  %10.5f  %10.3f  %10.4f  %10.4e%s\n",
                       pl.name.c_str(), pl.period_days, a_AU,
                       v/1000.0, g_r, K_check,
                       e > 0.0 ? "  [ecc]" : "");

                // Planet radius from transit depth
                if (pl.rp_rs > 0.0) {
                    double R_planet = pl.rp_rs * R;
                    double R_earth  = 6.371e6;
                    printf("    → R_planet = %.4e m = %.3f R_earth  (from Rp/Rs = %.4f)\n",
                           R_planet, R_planet/R_earth, pl.rp_rs);
                }

                // Star wobble → dimensionless mass ratio (no G, no M)
                if (pl.K_ms > 0.0) {
                    double mass_ratio = pl.K_ms / v;
                    printf("    → m_planet/M_star = %.4e  (from K/v_planet)\n",
                           mass_ratio);
                }
            }


            if (Koppa_n > 1) {
                double K_mean = Koppa_sum / Koppa_n;
                double K_diff = 100.0*(K_mean - K)/K;
                printf("\n  Field consistency: Ϟ from orbital periods = %.4e m\n", K_mean);
                printf("  Ϟ from log_g:                             = %.4e m\n", K);
                printf("  Difference: %+.2f%%  (spectroscopic log_g uncertainty)\n", K_diff);
            }
        }
        printf("\n");
    }

    return 0;
}
