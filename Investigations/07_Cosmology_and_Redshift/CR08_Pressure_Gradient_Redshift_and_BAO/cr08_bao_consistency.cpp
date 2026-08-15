// ============================================================================
// CR08 — Pressure-Gradient Redshift and BAO
// Author: James Christopher Tyndall, Melbourne. Date: 2026-07-03.
//
// SDT static strain law (fixed, no shape freedom — RUN_LOG):
//   d(z) = ln(1+z) c/H0;  "D_M/r_d" -> d/147;  "D_H/r_d" -> (c/H0)/(1+z)/147.
// Anchors: BOSS DR12 / eBOSS final consolidated BAO + Planck theta*.
// (Memory-transcribed OBSERVED anchors, ±2% risk — see RUN_LOG.)
// LCDM column = rival OBSERVED-comparison ONLY (HUNTER SecB), not in SDT chain.
// Gates: G1 3% (survey), G3 5% (CMB angle), G2 audit-only (circular as coded).
// ============================================================================

#include <sdt/laws.hpp>
#include <sdt/cosmology.hpp>
#include <algorithm>
#include <array>
#include <cstdio>
#include <cmath>
#include <numbers>
#include <vector>
#include <string>

using namespace sdt::laws;
namespace sdc = sdt::cosmology;

namespace b15 {

inline constexpr double zeta3 = 1.2020569031595943;
inline constexpr double eta_bbn_deuterium = 6.1e-10;
inline constexpr double equality_loading = 3.0 / 4.0;

struct Closure {
    double photon_count_m3;
    double baryon_count_m3;
    double equality_index;
    double equality_baryon_count_m3;
    double sound_speed_ms;
    double escape_rate_s;
    double escape_rate_numeric_s;
    double resolution_change;
    double standing_radius_m;
    double present_equivalent_m;
    double proton_tau;
    double free_tau;
    double bound_tau;
    double depinning_control_m;
    double orbital_control_m;
    double travelling_control_m;
};

[[nodiscard]] constexpr auto photon_count(double temperature_K) noexcept
    -> double {
    const double thermal_wave_number =
        measured::k_B * temperature_K
        / (measured::h * measured::c);
    return 16.0 * std::numbers::pi * zeta3
        * thermal_wave_number * thermal_wave_number * thermal_wave_number;
}

[[nodiscard]] constexpr auto baryon_count(
    double epoch_index,
    double present_count
) noexcept -> double {
    return present_count * epoch_index * epoch_index * epoch_index;
}

[[nodiscard]] inline auto escape_rate(
    double baryon_count_m3
) noexcept -> double {
    return measured::c * std::sqrt(
        (8.0 * std::numbers::pi / 3.0)
        * bridge::koppa_per_baryon
        * baryon_count_m3
    );
}

[[nodiscard]] inline auto integrated_koppa(
    double radius,
    double baryon_count_m3,
    int intervals
) noexcept -> double {
    const double step = radius / static_cast<double>(intervals);
    double sum = 0.0;
    for (int index = 0; index < intervals; ++index) {
        const double r =
            (static_cast<double>(index) + 0.5) * step;
        sum += 4.0 * std::numbers::pi * r * r
            * baryon_count_m3 * bridge::koppa_per_baryon * step;
    }
    return sum;
}

[[nodiscard]] inline auto numeric_escape_rate(
    double baryon_count_m3,
    int intervals
) noexcept -> double {
    constexpr double trial_radius = 1.0;
    const double total_koppa = integrated_koppa(
        trial_radius,
        baryon_count_m3,
        intervals
    );
    const double orbital_speed = measured::c * std::sqrt(
        total_koppa / trial_radius
    );
    return bridge::v_escape(orbital_speed) / trial_radius;
}

[[nodiscard]] inline auto sound_speed(double loading) noexcept -> double {
    return measured::c / std::sqrt(3.0 * (1.0 + loading));
}

[[nodiscard]] inline auto scale_at(
    double epoch_index,
    double present_baryon_count_m3,
    double loading,
    bool use_escape,
    bool use_round_trip
) noexcept -> double {
    const double count = baryon_count(
        epoch_index,
        present_baryon_count_m3
    );
    double rate = measured::c * std::sqrt(
        (4.0 * std::numbers::pi / 3.0)
        * bridge::koppa_per_baryon * count
    );
    if (use_escape) {
        rate *= std::numbers::sqrt2;
    }
    const double path_factor = use_round_trip ? 2.0 : 1.0;
    return epoch_index * sound_speed(loading)
        / (path_factor * rate);
}

[[nodiscard]] inline auto derive() noexcept -> Closure {
    const double photons = photon_count(measured::T_CMB);
    const double baryons = eta_bbn_deuterium * photons;
    const double radiation_resistance_density =
        measured::a_rad
        * measured::T_CMB * measured::T_CMB
        * measured::T_CMB * measured::T_CMB
        / (measured::c * measured::c);
    const double baryon_resistance_density =
        baryons * measured::m_p;
    const double equality_index =
        baryon_resistance_density / radiation_resistance_density;
    const double equality_count = baryon_count(
        equality_index,
        baryons
    );
    const double cs = sound_speed(equality_loading);
    const double rate = escape_rate(equality_count);
    const double numeric_rate_20k =
        numeric_escape_rate(equality_count, 20'000);
    const double numeric_rate_40k =
        numeric_escape_rate(equality_count, 40'000);
    const double standing_radius = cs / (2.0 * rate);
    const double present_equivalent =
        equality_index * standing_radius;

    const double sigma_proton =
        law_IV::transport::collision_measure(measured::R_p);
    const double sigma_free =
        sigma_proton
        + law_IV::transport::collision_measure(measured::r_e);
    const double sigma_bound =
        law_IV::transport::collision_measure(measured::a_0);

    const double depinning_index =
        equality_loading * equality_index;
    return {
        photons,
        baryons,
        equality_index,
        equality_count,
        cs,
        rate,
        numeric_rate_40k,
        std::abs(numeric_rate_40k / numeric_rate_20k - 1.0),
        standing_radius,
        present_equivalent,
        equality_count * sigma_proton * standing_radius,
        equality_count * sigma_free * standing_radius,
        equality_count * sigma_bound * standing_radius,
        scale_at(
            depinning_index,
            baryons,
            1.0,
            true,
            true
        ),
        scale_at(
            equality_index,
            baryons,
            equality_loading,
            false,
            true
        ),
        scale_at(
            equality_index,
            baryons,
            equality_loading,
            true,
            false
        )
    };
}

} // namespace b15

struct BAOPoint {
    const char* survey; double z;
    double DM_rd, DM_err;   // transverse (0 = not measured)
    double DH_rd, DH_err;   // line-of-sight (0 = not measured)
    double DV_rd, DV_err;   // isotropic (0 = not measured)
};

// OBSERVED anchors (Alam et al. 2021 consolidation; Planck 2018), memory-transcribed
static const std::vector<BAOPoint> DATA = {
    {"SDSS MGS",   0.15,  0,0,      0,0,      4.47,0.17},
    {"BOSS gal",   0.38,  10.23,0.17, 25.00,0.76, 0,0},
    {"BOSS gal",   0.51,  13.36,0.21, 22.33,0.58, 0,0},
    {"eBOSS LRG",  0.698, 17.86,0.33, 19.78,0.46, 0,0},
    {"eBOSS QSO",  1.48,  30.69,0.80, 13.26,0.55, 0,0},
    {"eBOSS Lya",  2.33,  37.60,1.90,  8.93,0.28, 0,0},
};
static const double theta_star = 0.0104109;  // rad, Planck 2018 (100*theta*=1.04109)
static const double r_star_Mpc = 144.4;      // sound horizon at z*, OBSERVED (vs r_drag 147.09)

struct Model {
    double c_H0_Mpc;   // c/H0 in Mpc
    double rd;         // ruler, Mpc
    double DM_rd(double z) const { return std::log(1.0+z) * c_H0_Mpc / rd; }        // SDT static
    double DH_rd(double z) const { return c_H0_Mpc / (1.0+z) / rd; }
    double DV_rd(double z) const {
        return std::cbrt(z * DH_rd(z) * DM_rd(z)*DM_rd(z));
    }
};

// LCDM rival column (flat, Om=0.31) — OBSERVED-comparison only
static double lcdm_E(double z) { return std::sqrt(0.31*std::pow(1.0+z,3) + 0.69); }
static double lcdm_DM_rd(double z, double c_H0, double rd) {
    const int N = 4000; double s = 0.0;
    for (int i = 0; i < N; ++i) { double zi = (i+0.5)*z/N; s += 1.0/lcdm_E(zi); }
    return (s * z/N) * c_H0 / rd;
}

int main() {
    const double Mpc = sdc::pre_clearing::Mpc;
    const b15::Closure closure = b15::derive();

    std::printf("================================================================\n");
    std::printf("B15 - SDT phase-resistance standing-equilibrium closure\n");
    std::printf("James Christopher Tyndall, Melbourne - 2026-08-15\n");
    std::printf("================================================================\n");
    std::printf("  INPUTS BEFORE BAO COMPARISON\n");
    std::printf("    FIRAS T_CMB                  = %.7g K\n", measured::T_CMB);
    std::printf("    BBN-deuterium eta            = %.7g\n",
                b15::eta_bbn_deuterium);
    std::printf("    photon count now             = %.9e m^-3\n",
                closure.photon_count_m3);
    std::printf("    baryon resistance count now  = %.9e m^-3\n",
                closure.baryon_count_m3);
    std::printf("  ENERGY-EQUALITY STATE\n");
    std::printf("    N_eq                         = %.9f\n",
                closure.equality_index);
    std::printf("    n_b(N_eq)                    = %.9e m^-3\n",
                closure.equality_baryon_count_m3);
    std::printf("    R_eq                         = 3/4\n");
    std::printf("    c_s(N_eq)                    = %.9e m/s = %.6f c\n",
                closure.sound_speed_ms,
                closure.sound_speed_ms / measured::c);
    std::printf("    phase-resistance escape rate = %.9e s^-1\n",
                closure.escape_rate_s);
    std::printf("    finite-volume escape rate    = %.9e s^-1 (residual %.3e)\n",
                closure.escape_rate_numeric_s,
                std::abs(
                    closure.escape_rate_numeric_s
                    / closure.escape_rate_s - 1.0
                ));
    std::printf("    resolution change 20k->40k   = %.3e\n",
                closure.resolution_change);
    std::printf("  OPACITY BRACKETS ACROSS THE PHYSICAL STANDING RADIUS\n");
    std::printf("    proton-boundary tau          = %.6f\n",
                closure.proton_tau);
    std::printf("    free electron+proton tau     = %.6f\n",
                closure.free_tau);
    std::printf("    bound-seat tau               = %.6e\n",
                closure.bound_tau);
    std::printf("  REGISTERED CONTROLS (present-equivalent)\n");
    std::printf("    R=1 depinning endpoint       = %.6f Mpc\n",
                closure.depinning_control_m / Mpc);
    std::printf("    orbital, not escape          = %.6f Mpc\n",
                closure.orbital_control_m / Mpc);
    std::printf("    travelling, not standing     = %.6f Mpc\n",
                closure.travelling_control_m / Mpc);
    std::printf("  SEALED B15 PREDICTION (comparison not yet read)\n");
    std::printf("    physical standing radius     = %.9e m = %.6f Mpc\n",
                closure.standing_radius_m,
                closure.standing_radius_m / Mpc);
    std::printf("    present-equivalent scale     = %.9e m = %.6f Mpc\n\n",
                closure.present_equivalent_m,
                closure.present_equivalent_m / Mpc);

    const double observed_bao_Mpc = 147.09;
    const double predicted_bao_Mpc =
        closure.present_equivalent_m / Mpc;
    const double canonical_residual = std::abs(
        closure.present_equivalent_m
        / bridge::release_acoustics::present_equivalent_scale_m
        - 1.0
    );
    const double b15_residual =
        std::abs(predicted_bao_Mpc / observed_bao_Mpc - 1.0);
    const bool b15_upstream =
        std::abs(
            closure.escape_rate_numeric_s
            / closure.escape_rate_s - 1.0
        ) < 0.005
        && closure.resolution_change < 0.005
        && canonical_residual < 1.0e-12
        && closure.proton_tau > 1.0;
    const bool b15_pass = b15_upstream && b15_residual < 0.03;
    std::printf("  BAO COMPARISON LOADED AFTER SEAL\n");
    std::printf("    predicted / observed         = %.6f / %.6f Mpc\n",
                predicted_bao_Mpc, observed_bao_Mpc);
    std::printf("    residual                     = %.4f %%\n",
                100.0 * b15_residual);
    std::printf("    instrument/canonical residual= %.3e\n",
                canonical_residual);
    std::printf("    finite-volume + opacity gate = %s\n",
                b15_upstream ? "PASS" : "FAIL");
    std::printf("    B15 COMPUTED gate            = %s\n\n",
                b15_pass ? "PASS" : "FAIL");

    const double rd  = sdc::pre_clearing::BAO_scale / Mpc;   // 147.0 (engine)
    std::printf("CR08 — Pressure-gradient redshift vs BAO (James Christopher Tyndall, 2026-07-03)\n");
    std::printf("SDT law: d = ln(1+z) c/H0 (static). Ruler = %.1f Mpc constant (engine bao::scale).\n\n", rd);

    for (double H0 : {67.4, 73.04}) {
        const double c_H0 = measured::c / (H0*1e3/Mpc) / Mpc;   // Mpc
        Model m{c_H0, rd};
        std::printf("=== H0 anchor = %.2f km/s/Mpc (OBSERVED, not fitted)  c/H0 = %.0f Mpc ===\n", H0, c_H0);
        std::printf("  %-10s  z      obs          SDT      dev%%    LCDM     dev%%   (type)\n", "survey");
        double chi2_sdt = 0, chi2_lcdm = 0; int npt = 0, nfail3 = 0, nfail5 = 0;
        for (const auto& p : DATA) {
            auto line = [&](const char* type, double obs, double err, double sdt, double lcdm) {
                const double dev  = (sdt/obs - 1.0)*100.0;
                const double devL = (lcdm/obs - 1.0)*100.0;
                chi2_sdt  += (sdt-obs)*(sdt-obs)/(err*err);
                chi2_lcdm += (lcdm-obs)*(lcdm-obs)/(err*err);
                ++npt; if (std::fabs(dev) > 3.0) ++nfail3; if (std::fabs(dev) > 5.0) ++nfail5;
                std::printf("  %-10s %5.3f  %7.2f+-%.2f %8.2f  %+6.1f  %7.2f  %+5.1f   (%s)\n",
                            p.survey, p.z, obs, err, sdt, dev, lcdm, devL, type);
            };
            const double lcdm_dm = lcdm_DM_rd(p.z, c_H0, rd);
            const double lcdm_dh = c_H0 / lcdm_E(p.z) / rd;
            if (p.DM_rd > 0) line("DM/rd", p.DM_rd, p.DM_err, m.DM_rd(p.z), lcdm_dm);
            if (p.DH_rd > 0) line("DH/rd", p.DH_rd, p.DH_err, m.DH_rd(p.z), lcdm_dh);
            if (p.DV_rd > 0) line("DV/rd", p.DV_rd, p.DV_err, m.DV_rd(p.z),
                                  std::cbrt(p.z*lcdm_dh*lcdm_dm*lcdm_dm));
        }
        std::printf("  chi2 (11 pts): SDT = %.1f   LCDM(Om=0.31) = %.1f\n", chi2_sdt, chi2_lcdm);
        std::printf("  G1 gate: %d/%d points beyond 3%%, %d/%d beyond 5%% -> %s\n",
                    nfail3, npt, nfail5, npt,
                    nfail5 > 0 ? "FAIL" : (nfail3 > 0 ? "PROVISIONAL" : "PASS"));

        // G3: CMB acoustic angle. SDT: physical ruler at the Clearing / distance to Clearing.
        const double d_star = m.DM_rd(measured::z_rec) * rd;               // Mpc
        const double th_sdt_147 = rd / d_star;
        const double th_sdt_144 = r_star_Mpc / d_star;
        std::printf("  G3 CMB angle: d(1100) = %.0f Mpc (R_CMB engine: %.0f Mpc, %.1f%%)\n",
                    d_star, law_I::R_CMB/Mpc, (d_star/(law_I::R_CMB/Mpc)-1.0)*100.0);
        std::printf("     theta_SDT = %.4f mrad (147 ruler) / %.4f mrad (144.4)\n",
                    th_sdt_147*1e3, th_sdt_144*1e3);
        std::printf("     theta_obs = %.4f mrad  ->  SDT/obs = %.3f  (factor %.2f MISS) -> %s\n\n",
                    theta_star*1e3, th_sdt_147/theta_star, theta_star/th_sdt_147,
                    std::fabs(th_sdt_147/theta_star - 1.0) > 0.05 ? "FAIL" : "PASS");
    }

    // G2 audit: the engine's own 147-Mpc "derivation"
    std::printf("=== G2 audit: 147 Mpc = c_s x t_coupled? ===\n");
    std::printf("  cosmology.hpp: c_s = c/sqrt(3) = %.4e m/s (real content: opacity bound, CR13)\n",
                sdc::pre_clearing::c_s);
    std::printf("  t_coupled = BAO_scale / c_s = %.3e s — DEFINED from the 147 Mpc target.\n",
                sdc::pre_clearing::t_coupled);
    std::printf("  IDENTITY as coded: criterion 2 cannot PASS until t_coupled is derived\n");
    std::printf("  independently (Clearing dynamics). Same root as CR03 Route B.\n\n");

    std::printf("VERDICT LINES\n");
    std::printf("  B15: standing-equilibrium scale - %s (%.4f%% residual)\n",
                b15_pass ? "COMPUTED" : "PENDING",
                100.0 * b15_residual);
    std::printf("  G1: survey BAO — see per-point table (gates 3%%/5%%)\n");
    std::printf("  G2-old: IDENTITY (target-defined duration in cosmology.hpp remains excluded)\n");
    std::printf("  G3: CMB acoustic angle — factor ~2 class miss for the static ln-law\n");
    std::printf("  G4: no dark energy in SDT chain — true but earns nothing while G1/G3 fail\n");
    return b15_pass ? 0 : 1;
}

