// =============================================================================
// CQ18c — AGN z_grav Systematic
// Quantify gravitational redshift from BLR emission line widths.
// SDT prediction: z_grav_BLR = (Δv/c)²
// Data: published reverberation mapping campaigns.
// No G, No M.
// =============================================================================

#include <cstdio>
#include <cmath>

static constexpr double c_ms = 2.99792458e8; // m/s

struct AGN {
    const char* name;
    double z_total;         // total observed redshift (spectroscopic)
    double delta_v_kms;     // BLR line width FWHM [km/s]  (from spectroscopy)
    double tau_days;        // reverberation lag [days]  (from RM campaign)
    double z_host_grav_est; // estimated host galaxy z_grav (from galaxy mass models)
};

// Well-characterised AGN with reverberation mapping data
// Sources: Peterson et al. 2004, Bentz et al. 2009-2015
static const AGN agn_table[] = {
    // Name            z_total   Δv [km/s]  τ [days]  z_host_est
    { "NGC 4151",      0.003319,  5600.0,   6.6,      1.5e-6 },
    { "NGC 5548",      0.017175,  5765.0,  13.0,      1.8e-6 },
    { "NGC 3783",      0.009730,  3720.0,   4.0,      1.2e-6 },
    { "NGC 4051",      0.002336,  1200.0,   6.3,      0.8e-6 },
    { "NGC 7469",      0.016317,  4200.0,  12.5,      1.6e-6 },
    { "3C 273",        0.158339, 30000.0, 380.0,      3.0e-6 },
    { "Mrk 110",       0.035291,  4300.0,  25.6,      1.4e-6 },
    { "Mrk 509",       0.034397,  5600.0,  80.1,      1.8e-6 },
    { "PG 2130+099",   0.062985,  7900.0,  22.9,      2.0e-6 },
    { "Mrk 79",        0.022189,  6200.0,  15.6,      1.6e-6 },
};

int main() {
    printf("=== CQ18c: AGN z_grav Systematic — BLR Gravitational Redshift ===\n\n");
    printf("SDT prediction: z_grav_BLR = (Δv/c)²\n");
    printf("This is the gravitational redshift of photons emitted at the BLR radius.\n\n");

    printf("%-20s  %10s  %10s  %10s  %12s  %12s  %10s\n",
           "AGN", "z_total", "Δv [km/s]", "τ [days]",
           "r_BLR [lt-d]", "z_grav_BLR", "z_grav/z_tot");
    printf("%-20s  %10s  %10s  %10s  %12s  %12s  %10s\n",
           "---", "-------", "---------", "--------",
           "------------", "----------", "------------");

    for (const auto& agn : agn_table) {
        // BLR radius from reverberation lag: r_BLR = c × τ
        double r_BLR_m = agn.tau_days * 86400.0 * c_ms;
        double r_BLR_ld = agn.tau_days; // light-days

        // SDT z_grav prediction from BLR line width
        double dv = agn.delta_v_kms * 1000.0; // m/s
        double z_grav_BLR = (dv/c_ms) * (dv/c_ms);

        // Ϟ_BH from BLR orbital data
        // In SDT: Ϟ_BH = (Δv/2)² × r_BLR / c²  (FWHM → dispersion: divide by ~√2)
        // Actually: v_orbital = Δv_FWHM / 2 for disk inclination (simplified)
        double v_orb  = dv / 2.0; // approximate
        double Koppa_BH = v_orb*v_orb * r_BLR_m / (c_ms*c_ms);
        double z_grav_surface = Koppa_BH / r_BLR_m; // = (v_orb/c)²

        double ratio = z_grav_BLR / agn.z_total;

        printf("%-20s  %10.6f  %10.1f  %10.1f  %12.2f  %12.4e  %10.4f%%\n",
               agn.name, agn.z_total, agn.delta_v_kms, agn.tau_days,
               r_BLR_ld, z_grav_BLR, ratio*100.0);
    }

    printf("\n--- Interpretation ---\n");
    printf("z_grav_BLR is a systematic FLOOR on the gravitational contribution.\n");
    printf("For nearby AGN (z_total << 0.1), this is a few percent of z_total.\n");
    printf("For high-z AGN, it becomes negligible but is still present.\n\n");

    printf("--- Ϟ_BH for each system ---\n");
    printf("%-20s  %12s  %12s\n", "AGN", "Ϟ_BH [AU]", "r_BLR/Ϟ");
    for (const auto& agn : agn_table) {
        double r_BLR_m = agn.tau_days * 86400.0 * c_ms;
        double v_orb   = agn.delta_v_kms * 500.0; // half FWHM in m/s
        double Koppa_BH = v_orb*v_orb * r_BLR_m / (c_ms*c_ms);
        double AU_m = 1.496e11;
        printf("%-20s  %12.4f  %12.2f\n",
               agn.name, Koppa_BH/AU_m, r_BLR_m/Koppa_BH);
    }

    printf("\nNote: r_BLR/Ϟ >> 1 confirms these are far outside the c-boundary\n");
    printf("(the photon sphere equivalent). The BLR is in the Keplerian zone.\n");

    return 0;
}
