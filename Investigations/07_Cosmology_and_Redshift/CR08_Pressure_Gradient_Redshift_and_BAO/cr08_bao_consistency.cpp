// ============================================================================
// CR08 â€” Pressure-Gradient Redshift and BAO
// Author: J. C. Harvey, Melbourne. Date: 2026-07-03.
//
// SDT static strain law (fixed, no shape freedom â€” RUN_LOG):
//   d(z) = ln(1+z) c/H0;  "D_M/r_d" -> d/147;  "D_H/r_d" -> (c/H0)/(1+z)/147.
// Anchors: BOSS DR12 / eBOSS final consolidated BAO + Planck theta*.
// (Memory-transcribed OBSERVED anchors, +-2% risk â€” see RUN_LOG.)
// LCDM column = rival OBSERVED-comparison ONLY (HUNTER SecB), not in SDT chain.
// Gates: G1 3% (survey), G3 5% (CMB angle), G2 audit-only (circular as coded).
// ============================================================================

#include <sdt/laws.hpp>
#include <sdt/cosmology.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>

using namespace sdt::laws;
namespace sdc = sdt::cosmology;

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

// LCDM rival column (flat, Om=0.31) â€” OBSERVED-comparison only
static double lcdm_E(double z) { return std::sqrt(0.31*std::pow(1.0+z,3) + 0.69); }
static double lcdm_DM_rd(double z, double c_H0, double rd) {
    const int N = 4000; double s = 0.0;
    for (int i = 0; i < N; ++i) { double zi = (i+0.5)*z/N; s += 1.0/lcdm_E(zi); }
    return (s * z/N) * c_H0 / rd;
}

int main() {
    const double Mpc = sdc::pre_clearing::Mpc;
    const double rd  = sdc::pre_clearing::BAO_scale / Mpc;   // 147.0 (engine)
    std::printf("CR08 â€” Pressure-gradient redshift vs BAO (J. C. Harvey, 2026-07-03)\n");
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
    std::printf("  t_coupled = BAO_scale / c_s = %.3e s â€” DEFINED from the 147 Mpc target.\n",
                sdc::pre_clearing::t_coupled);
    std::printf("  IDENTITY as coded: criterion 2 cannot PASS until t_coupled is derived\n");
    std::printf("  independently (Clearing dynamics). Same root as CR03 Route B.\n\n");

    std::printf("VERDICT LINES\n");
    std::printf("  G1: survey BAO â€” see per-point table (gates 3%%/5%%)\n");
    std::printf("  G2: IDENTITY (circular in cosmology.hpp)\n");
    std::printf("  G3: CMB acoustic angle â€” factor ~2 class miss for the static ln-law\n");
    std::printf("  G4: no dark energy in SDT chain â€” true but earns nothing while G1/G3 fail\n");
    return 0;
}

