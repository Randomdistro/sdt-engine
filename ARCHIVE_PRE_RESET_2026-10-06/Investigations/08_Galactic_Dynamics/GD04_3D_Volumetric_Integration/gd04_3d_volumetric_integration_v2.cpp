#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <sdt/galactic.hpp>

using namespace sdt::galactic;

static constexpr double kpc_to_m = 3.085677581e19;
static constexpr double km_s     = 1000.0;
static constexpr double M_Sun    = 1.989e30;

struct RealGalaxy {
    std::string name;
    double M_bar_Msun;
    double h_R_kpc;
    double h_z_kpc; // Added vertical scale height
    double v_flat_meas;
    std::string classification;
};

// Real SPARC data from Lelli+2016 for 10 well-studied galaxies
// Adding h_z_kpc estimates (~0.4 - 0.5 kpc for most disks, puffier for some).
// This natively tests the (h_R / h_z) multiplier effect.
static const std::vector<RealGalaxy> sparc_sample = {
    // name          M_bar[M☉]  h_R[kpc] h_z[kpc] v_flat[km/s] Class
    { "NGC 6503",    2.0e10,    2.1,     0.4,     116.0,       "HSB Spiral" },
    { "NGC 3198",    4.0e10,    3.1,     0.5,     150.0,       "HSB Spiral" },
    { "NGC 2403",    1.5e10,    2.1,     0.4,     131.0,       "HSB Spiral" },
    { "UGC 128",     3.0e9,     5.0,     0.5,      64.0,       "LSB Galaxy" },
    { "NGC 7331",    1.2e11,    3.8,     0.6,     240.0,       "Massive HSB" },
    { "NGC 2998",    8.0e10,    4.5,     0.6,     213.0,       "Massive HSB" },
    { "NGC 801",     1.2e11,    7.0,     0.8,     218.0,       "Massive HSB" },
    { "DDO 154",     1.0e8,     0.9,     0.2,      47.0,       "Dwarf" },
    { "NGC 3741",    3.0e8,     1.2,     0.2,      50.0,       "Dwarf" },
    { "IC 2574",     4.0e9,     3.7,     0.5,      67.0,       "LSB Galaxy" }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << " GOM03: 3D Volumetric Eclipse Saturation (Zero Parameter)\n";
    std::cout << " Testing Scale-Inversion and Radial Column Density\n";
    std::cout << "========================================================\n\n";

    double sum_sq_err = 0.0;
    double max_err = 0.0;

    std::cout << std::left << std::setw(15) << "Galaxy" 
              << std::right << std::setw(15) << "M_bar (M_sun)"
              << std::setw(15) << "h_R/h_z Ratio"
              << std::setw(12) << "V_obs (km/s)"
              << std::setw(12) << "V_SDT (km/s)"
              << std::setw(12) << "Residual (%)"
              << "\n";
    std::cout << std::string(81, '-') << "\n";

    for (const auto& g : sparc_sample) {
        Galaxy3DProfile profile;
        profile.baryonic_mass_kg = g.M_bar_Msun * M_Sun;
        profile.radial_scale_length_m = g.h_R_kpc * kpc_to_m;
        profile.vertical_scale_height_m = g.h_z_kpc * kpc_to_m;
        profile.gas_fraction = 0.0; // not used in this base calc
        profile.inclination_rad = PI / 2.0;

        // Evaluate at R = 3 * h_R (typical flat region)
        double R_eval = 3.0 * profile.radial_scale_length_m;

        VolumetricEclipseResult res = predicted_velocity_3d(R_eval, profile);
        double v_flat_p = res.predicted_velocity_m_s / km_s;

        double residual = (g.v_flat_meas - v_flat_p) / g.v_flat_meas * 100.0;
        sum_sq_err += residual * residual;
        if (std::abs(residual) > max_err) max_err = std::abs(residual);

        double ratio = g.h_R_kpc / g.h_z_kpc;

        std::cout << std::left << std::setw(15) << g.name
                  << std::right << std::setw(15) << std::scientific << std::setprecision(2) << g.M_bar_Msun
                  << std::setw(15) << std::fixed << std::setprecision(1) << ratio
                  << std::setw(12) << std::fixed << std::setprecision(1) << g.v_flat_meas
                  << std::setw(12) << v_flat_p
                  << std::setw(12) << std::showpos << residual << std::noshowpos
                  << "\n";
    }

    double rms_err = std::sqrt(sum_sq_err / sparc_sample.size());

    std::cout << std::string(81, '-') << "\n\n";
    std::cout << "=== RESULTS ===\n";
    std::cout << "Galaxies Analyzed:     " << sparc_sample.size() << "\n";
    std::cout << "RMS Residual Error:    " << std::fixed << std::setprecision(2) << rms_err << " %\n";
    std::cout << "Max Residual Error:    " << max_err << " %\n\n";
    
    // Audit correction 2026-10-05: gates derived from the residuals (the old "any nonzero velocity" test could not fail).
    int n_within25 = 0, n_lsb = 0, n_lsb_ok = 0;
    for (const auto& g : sparc_sample) {
        Galaxy3DProfile pr; pr.baryonic_mass_kg = g.M_bar_Msun * M_Sun; pr.radial_scale_length_m = g.h_R_kpc * kpc_to_m;
        pr.vertical_scale_height_m = g.h_z_kpc * kpc_to_m; pr.gas_fraction = 0.0; pr.inclination_rad = PI / 2.0;
        const double v = predicted_velocity_3d(3.0 * pr.radial_scale_length_m, pr.vertical_scale_height_m > 0 ? pr : pr).predicted_velocity_m_s / km_s;
        const double rel = std::abs(g.v_flat_meas - v) / g.v_flat_meas;
        if (rel <= 0.25) ++n_within25;
        if (g.classification.find("LSB") != std::string::npos) { ++n_lsb; if (rel <= 0.25) ++n_lsb_ok; }
    }
    const bool g1 = n_within25 >= (int)(0.8 * sparc_sample.size() + 0.999);
    const bool g2 = (n_lsb > 0) && (n_lsb_ok == n_lsb);
    const bool g3 = rms_err < 30.0;
    std::cout << "GATE A  at least 80% of galaxies within 25% of V_obs : " << n_within25 << "/" << sparc_sample.size() << "  " << (g1 ? "PASS" : "FAIL") << "" << "\n";
    std::cout << "GATE B  every LSB galaxy within 25% of V_obs         : " << n_lsb_ok << "/" << n_lsb << "  " << (g2 ? "PASS" : "FAIL") << "" << "\n";
    std::cout << "GATE C  RMS residual < 30%                           : " << rms_err << "%  " << (g3 ? "PASS" : "FAIL") << "" << "\n";
    std::cout << "VERDICT: " << ((g1 && g2 && g3) ? "PASS" : "FAIL") << "  [gates derived from residuals; the earlier 'any nonzero velocity passes' test is withdrawn]" << "\n";
    return (g1 && g2 && g3) ? 0 : 1;
}
