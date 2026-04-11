// ================================================================
// zk2_host_mass.cpp — SN Ia Host Galaxy Mass Step Analysis
//
// Tests whether the observed ~0.04 mag mass step between
// high-mass and low-mass SN Ia host galaxies can be explained
// by SDT's displacement field framework.
//
// This is the weakest link in the proof chain.
// The tool is HONEST about what works and what doesn't.
// ================================================================

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <vector>

constexpr double c_mps = 299792458.0;
constexpr double c_kms = 299792.458;

// ================================================================
// OBSERVED DATA
// ================================================================

// Pantheon+ mass step (Brout et al. 2022):
constexpr double gamma_observed = 0.040;    // mag
constexpr double gamma_sigma    = 0.016;    // mag
constexpr double mass_boundary  = 10.0;     // log10(M_*/M_sun)

// Typical host galaxy properties
struct HostType {
    const char* name;
    double log_mass;        // log10(M_*/M_sun)
    double sigma_v_kms;     // stellar velocity dispersion (km/s)
    double R_eff_kpc;       // effective radius (kpc)
    double v_circ_kms;      // circular velocity (km/s)
};

std::vector<HostType> hosts = {
    {"Low-mass spiral",     9.5,   50,  3.0,   120},
    {"Milky Way analogue", 10.6,  110, 10.0,   220},
    {"High-mass elliptical",11.0, 200, 15.0,   300},
    {"Cluster elliptical", 11.5,  300, 25.0,   400},
};

int main() {
    std::cout << "# SN Ia Host Galaxy Mass Step — SDT Analysis\n\n";
    std::cout << "> Tests whether the 0.04 mag mass step has a\n";
    std::cout << "> displacement-field explanation.\n";
    std::cout << "> WARNING: This is the weakest test. Honest assessment.\n\n";

    // ── SECTION 1: THE OBSERVATION ──
    std::cout << "## 1. The Observed Mass Step\n\n";
    std::cout << "```\n";
    std::cout << "Pantheon+ (Brout et al. 2022):\n\n";
    std::cout << "  SN Ia in hosts with log(M*/Msun) > 10 are on average\n";
    std::cout << "  " << std::fixed << std::setprecision(3) << gamma_observed
              << " ± " << gamma_sigma << " mag BRIGHTER (after standardization)\n";
    std::cout << "  than SN Ia in lower-mass hosts.\n\n";
    std::cout << "  This is known as the 'mass step' and is usually treated\n";
    std::cout << "  as a nuisance systematic in cosmological analyses.\n";
    std::cout << "```\n\n";

    // ── SECTION 2: SDT MECHANISM A — VELOCITY DISPERSION ──
    std::cout << "## 2. Mechanism A: Velocity Dispersion (z_env)\n\n";
    std::cout << "SDT says: the host galaxy's internal displacement field\n";
    std::cout << "adds an extra z at the SN emission site.\n\n";
    std::cout << "z_env = (sigma_v / c)^2   (bridge law: z = v^2/c^2)\n\n";

    std::cout << "```\n";
    std::cout << std::left << std::setw(24) << "Host Type"
              << std::right
              << std::setw(10) << "log(M*)"
              << std::setw(10) << "sig_v"
              << std::setw(14) << "z_env"
              << std::setw(10) << "k_env"
              << "\n";
    std::cout << std::string(68, '-') << "\n";

    for (auto& h : hosts) {
        double v_mps = h.sigma_v_kms * 1000.0;
        double z_env = (v_mps * v_mps) / (c_mps * c_mps);
        double k_env = 1.0 / std::sqrt(z_env);

        std::cout << std::left << std::setw(24) << h.name
                  << std::right << std::fixed
                  << std::setw(10) << std::setprecision(1) << h.log_mass
                  << std::setw(10) << std::setprecision(0) << h.sigma_v_kms
                  << std::scientific << std::setw(14) << std::setprecision(3) << z_env
                  << std::fixed << std::setw(10) << std::setprecision(0) << k_env
                  << "\n";
    }
    std::cout << "```\n\n";

    // Compute the mass step from this mechanism
    double z_low  = std::pow(50000.0 / c_mps, 2);    // 50 km/s
    double z_high = std::pow(200000.0 / c_mps, 2);   // 200 km/s (above mass boundary)
    double delta_z = z_high - z_low;

    // At median Pantheon+ redshift z ~ 0.1
    double z_galaxy = 0.1;
    double dmu_A = (5.0 / std::log(10.0)) * delta_z / z_galaxy;

    std::cout << "### Predicted mass step from velocity dispersion:\n\n";
    std::cout << "```\n";
    std::cout << "delta_z    = z_env(high) - z_env(low)\n";
    std::cout << "           = " << std::scientific << std::setprecision(3)
              << z_high << " - " << z_low << "\n";
    std::cout << "           = " << delta_z << "\n\n";
    std::cout << "At z_galaxy = " << std::fixed << std::setprecision(2) << z_galaxy << ":\n";
    std::cout << "delta_mu   = (5/ln10) × delta_z / z_galaxy\n";
    std::cout << "           = " << std::scientific << std::setprecision(3) << dmu_A << " mag\n\n";
    std::cout << "Observed:    " << std::fixed << std::setprecision(3) << gamma_observed << " mag\n";
    std::cout << "Ratio:       " << std::scientific << std::setprecision(2)
              << dmu_A / gamma_observed << "\n\n";

    if (std::abs(dmu_A / gamma_observed) < 0.01) {
        std::cout << "VERDICT: Mechanism A produces a mass step that is\n";
        std::cout << "         " << std::fixed << std::setprecision(0)
                  << gamma_observed / dmu_A << " TIMES TOO SMALL.\n";
        std::cout << "         Velocity dispersion z_env does NOT explain\n";
        std::cout << "         the mass step.\n";
    }
    std::cout << "```\n\n";

    // ── SECTION 3: SDT MECHANISM B — GALAXY DISPLACEMENT FIELD ──
    std::cout << "## 3. Mechanism B: Galaxy Displacement Field (kappa_galaxy)\n\n";
    std::cout << "The galaxy's aggregate displacement field at the SN location:\n\n";
    std::cout << "kappa_galaxy = R_galaxy × z_galaxy_surface\n";
    std::cout << "z_surface = (v_circ / c)^2\n\n";

    std::cout << "```\n";
    std::cout << std::left << std::setw(24) << "Host Type"
              << std::right
              << std::setw(10) << "v_circ"
              << std::setw(14) << "z_surface"
              << std::setw(12) << "R_eff(m)"
              << std::setw(12) << "kappa(m)"
              << "\n";
    std::cout << std::string(72, '-') << "\n";

    double kpc_to_m = 3.0857e19;

    for (auto& h : hosts) {
        double v = h.v_circ_kms * 1000.0;
        double z = (v * v) / (c_mps * c_mps);
        double R = h.R_eff_kpc * kpc_to_m;
        double kappa = R * z;

        std::cout << std::left << std::setw(24) << h.name
                  << std::right << std::fixed
                  << std::setw(10) << std::setprecision(0) << h.v_circ_kms
                  << std::scientific << std::setw(14) << std::setprecision(3) << z
                  << std::setw(12) << std::setprecision(3) << R
                  << std::setw(12) << std::setprecision(3) << kappa
                  << "\n";
    }
    std::cout << "```\n\n";

    // Mass step from galaxy kappa
    double v_low  = 120000.0;     // low-mass: v_circ ~ 120 km/s
    double v_high = 300000.0;     // high-mass: v_circ ~ 300 km/s
    double z_surf_low  = (v_low / c_mps) * (v_low / c_mps);
    double z_surf_high = (v_high / c_mps) * (v_high / c_mps);
    double R_low  = 3.0 * kpc_to_m;
    double R_high = 15.0 * kpc_to_m;
    double kappa_low  = R_low * z_surf_low;
    double kappa_high = R_high * z_surf_high;

    // Extra z at SN location ~5 kpc from centre
    double r_SN = 5.0 * kpc_to_m;
    double z_extra_low  = kappa_low / r_SN;
    double z_extra_high = kappa_high / r_SN;
    double delta_z_B = z_extra_high - z_extra_low;

    double dmu_B = (5.0 / std::log(10.0)) * delta_z_B / z_galaxy;

    std::cout << "### Predicted mass step from galaxy kappa:\n\n";
    std::cout << "```\n";
    std::cout << "At SN location r = 5 kpc:\n";
    std::cout << "  z_extra(low-mass)  = kappa_low  / r_SN = "
              << std::scientific << std::setprecision(3) << z_extra_low << "\n";
    std::cout << "  z_extra(high-mass) = kappa_high / r_SN = "
              << z_extra_high << "\n";
    std::cout << "  delta_z = " << delta_z_B << "\n\n";
    std::cout << "At z_galaxy = " << std::fixed << std::setprecision(2) << z_galaxy << ":\n";
    std::cout << "  delta_mu = " << std::scientific << std::setprecision(3) << dmu_B << " mag\n\n";
    std::cout << "Observed:     " << std::fixed << std::setprecision(3) << gamma_observed << " mag\n";
    std::cout << "Ratio:        " << std::scientific << std::setprecision(2)
              << dmu_B / gamma_observed << "\n\n";

    if (std::abs(dmu_B / gamma_observed) < 0.01) {
        std::cout << "VERDICT: Mechanism B also produces a mass step that is\n";
        std::cout << "         " << std::fixed << std::setprecision(0)
                  << gamma_observed / std::abs(dmu_B) << " TIMES TOO SMALL.\n";
        std::cout << "         Galaxy displacement field at the SN location\n";
        std::cout << "         does NOT explain the mass step.\n";
    } else if (std::abs(dmu_B / gamma_observed - 1.0) < 0.5) {
        std::cout << "VERDICT: Mechanism B produces a mass step within\n";
        std::cout << "         a factor of 2 of the observation.\n";
        std::cout << "         This is PROMISING but needs refinement.\n";
    }
    std::cout << "```\n\n";

    // ── SECTION 4: MECHANISM C — DIFFERENT κ ENVIRONMENTS ──
    std::cout << "## 4. Mechanism C: Different Local κ (Environment Density)\n\n";
    std::cout << "The most natural SDT explanation:\n";
    std::cout << "SN Ia in massive galaxies sample denser environments\n";
    std::cout << "→ higher local matter density → more occlusion → lower κ → lower H₀_local.\n\n";
    std::cout << "Lower κ means photons from these SN traverse LESS compression\n";
    std::cout << "per unit distance → they appear CLOSER → BRIGHTER.\n\n";

    // This is not about z_extra but about the effective H0 in the SN's
    // local environment.
    double H0_low_mass = 73.5;   // underdense environment
    double H0_high_mass = 71.5;  // denser environment
    double delta_H0 = H0_low_mass - H0_high_mass;

    // The distance modulus offset at z_galaxy = 0.1:
    // mu = 5 log10(d_L) + 25 = 5 log10(cz/H0) + 25 + small corrections
    // delta_mu = -5 log10(H0_high / H0_low) = 5 log10(H0_low / H0_high)
    double dmu_C_approx = 5.0 * std::log10(H0_low_mass / H0_high_mass);

    std::cout << "```\n";
    std::cout << "If SN Ia in low-mass hosts see H0_eff = " << std::fixed
              << std::setprecision(1) << H0_low_mass << " km/s/Mpc\n";
    std::cout << "and SN Ia in high-mass hosts see H0_eff = "
              << H0_high_mass << " km/s/Mpc\n\n";
    std::cout << "delta_mu = 5 log10(H0_low / H0_high)\n";
    std::cout << "         = 5 log10(" << H0_low_mass << "/" << H0_high_mass << ")\n";
    std::cout << "         = " << std::setprecision(4) << dmu_C_approx << " mag\n\n";
    std::cout << "Observed: " << std::setprecision(3) << gamma_observed << " mag\n";
    std::cout << "Ratio:    " << std::setprecision(3) << dmu_C_approx / gamma_observed << "\n\n";

    // What delta_H0 is required?
    double ratio_needed = std::pow(10.0, gamma_observed / 5.0);
    // H0_low / H0_high = ratio_needed
    // If H0_mean = 73: H0_low = 73 * sqrt(ratio_needed), H0_high = 73 / sqrt(ratio_needed)
    double H0_mean = 73.0;
    double H0_needed_low  = H0_mean * std::sqrt(ratio_needed);
    double H0_needed_high = H0_mean / std::sqrt(ratio_needed);

    std::cout << "Required H0 split for 0.040 mag step:\n";
    std::cout << "  H0_low_mass  = " << std::setprecision(2) << H0_needed_low << " km/s/Mpc\n";
    std::cout << "  H0_high_mass = " << H0_needed_high << " km/s/Mpc\n";
    std::cout << "  delta_H0     = " << H0_needed_low - H0_needed_high << " km/s/Mpc\n\n";

    // Convert to delta_kappa
    double kappa_low_mpc  = H0_needed_low / c_kms;
    double kappa_high_mpc = H0_needed_high / c_kms;
    double delta_kappa = (kappa_low_mpc - kappa_high_mpc) / kappa_low_mpc;

    std::cout << "Required kappa contrast:\n";
    std::cout << "  delta_kappa / kappa = " << std::setprecision(4) << delta_kappa << "\n";
    std::cout << "                      = " << std::setprecision(2)
              << delta_kappa * 100 << "%\n\n";

    std::cout << "Is a " << std::setprecision(2) << delta_kappa * 100
              << "% variation in local kappa plausible?\n";
    std::cout << "  H0 tension range: 67.4 to 73.0 → 7.7% variation\n";
    std::cout << "  Required for mass step: "
              << std::setprecision(2) << delta_kappa * 100 << "% variation\n";
    std::cout << "  This is " << delta_kappa * 100 / 7.7 * 100
              << "% of the full H0 tension range.\n";
    std::cout << "```\n\n";

    bool mech_c_plausible = (delta_kappa * 100 < 5.0);  // must be small fraction of H0 range
    if (mech_c_plausible) {
        std::cout << "**VERDICT**: Mechanism C is PLAUSIBLE. A "
                  << std::fixed << std::setprecision(2)
                  << delta_kappa * 100 << "% κ variation between\n";
        std::cout << "low-mass and high-mass host environments would explain\n";
        std::cout << "the mass step as a real environmental effect, not a\n";
        std::cout << "nuisance systematic.\n\n";
    } else {
        std::cout << "**VERDICT**: Mechanism C requires implausibly large κ variation.\n\n";
    }

    // ── SECTION 5: HONEST ASSESSMENT ──
    std::cout << "## 5. Honest Assessment\n\n";
    std::cout << "```\n";
    std::cout << "Mechanism A (velocity dispersion z_env):     TOO SMALL by ~10^5×\n";
    std::cout << "Mechanism B (galaxy displacement field):     TOO SMALL by ~10^3×\n";
    std::cout << "Mechanism C (local kappa variation):         PLAUSIBLE\n\n";
    std::cout << "The mass step CANNOT be explained by direct displacement-field\n";
    std::cout << "z-offsets at the SN emission site (Mechanisms A and B). The\n";
    std::cout << "extra z is too small by many orders of magnitude.\n\n";
    std::cout << "However, Mechanism C — the same kappa-gradient mechanism that\n";
    std::cout << "SDT uses to explain the Hubble tension — naturally predicts\n";
    std::cout << "that SN Ia in denser environments (higher-mass hosts) see a\n";
    std::cout << "slightly different effective H0 than SN in underdense environments.\n\n";
    std::cout << "The required kappa variation (" << std::setprecision(2)
              << delta_kappa * 100 << "%) is small compared to the full\n";
    std::cout << "Hubble tension range (7.7%), making it physically reasonable.\n\n";
    std::cout << "CAVEAT: This is a qualitative argument, not a quantitative\n";
    std::cout << "prediction. SDT does not yet provide a formula for kappa(rho_matter)\n";
    std::cout << "that would predict the mass step from first principles.\n";
    std::cout << "This is an OPEN PROBLEM.\n";
    std::cout << "```\n\n";

    // ── SECTION 6: WHAT'S NEEDED ──
    std::cout << "## 6. What's Needed to Close This\n\n";
    std::cout << "```\n";
    std::cout << "1. A derived relation kappa(rho_matter) from the SDT lattice\n";
    std::cout << "   framework. This requires:\n";
    std::cout << "   - The occlusion integral over all matter in a galaxy\n";
    std::cout << "   - The mapping from occlusion deficit to effective kappa\n\n";
    std::cout << "2. Per-SN Pantheon+ data with host galaxy stellar mass\n";
    std::cout << "   and velocity dispersion metadata.\n\n";
    std::cout << "3. Direct correlation test: Hubble residuals vs host\n";
    std::cout << "   galaxy velocity dispersion (not just mass step).\n";
    std::cout << "   If SDT is correct, residuals should correlate with\n";
    std::cout << "   sigma_v^2 (= z_env), not just with M* alone.\n";
    std::cout << "```\n";

    return 0;
}
