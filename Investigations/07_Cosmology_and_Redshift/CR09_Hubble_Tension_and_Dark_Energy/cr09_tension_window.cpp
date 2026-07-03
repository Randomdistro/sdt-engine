// ============================================================================
// CR09 — Hubble Tension: does any radial strain-gradient window survive?
// Author: J. C. Harvey, Melbourne. Date: 2026-07-03.
//
// H0 is NOT derived. Both H0 values are OBSERVED anchors (engine strain::).
// Model: piecewise strain sigma(d) = sigma_l (d < d_t), sigma_g beyond.
// Gates W1-W4 pre-committed in RUN_LOG.md. Scan z_t; report the window.
// Phase B (Pantheon fit) = CR12, not re-run. Phase D (BAO) = CR08, not re-run.
// ============================================================================

#include <sdt/laws.hpp>
#include <sdt/cosmology.hpp>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace sdt::laws;
namespace sdc = sdt::cosmology;

struct Piecewise {
    double sig_l, sig_g, d_t;                 // strains [1/m], transition depth [m]
    double z_of_d(double d) const {
        const double s = sig_l*std::min(d,d_t) + sig_g*std::max(0.0, d-d_t);
        return std::exp(s) - 1.0;
    }
    double d_of_z(double z) const {
        const double s = std::log(1.0+z);
        const double s_t = sig_l*d_t;
        return (s <= s_t) ? s/sig_l : d_t + (s - s_t)/sig_g;
    }
    // path-averaged strain to redshift z -> "inferred H0" = c * sbar
    double sbar(double z) const { return std::log(1.0+z) / d_of_z(z); }
};

int main() {
    const double Mpc  = sdc::pre_clearing::Mpc;
    const double sig_g = sdc::strain::sigma_CMB;     // 67.4  -> 7.29e-27 1/m (OBSERVED anchor)
    const double sig_l = sdc::strain::sigma_local;   // 73.04 -> 7.90e-27 1/m (OBSERVED anchor)
    const double H0g = 67.4, H0l = 73.04;

    std::printf("CR09 — Hubble-tension radial-window scan (J. C. Harvey, 2026-07-03)\n");
    std::printf("======================================================================\n");
    std::printf("sigma_local/sigma_global = %.4f (engine strain:: tension %.2f%%) — OBSERVED anchors, not derived\n\n",
                sig_l/sig_g, sdc::strain::tension_pct);

    // The ratio the tension implies (the guardrail question):
    std::printf("[0] Required kappa_local/kappa_global = %.4f, coherent across the WHOLE\n", sig_l/sig_g);
    std::printf("    SH0ES Hubble-flow window 0.023 < z < 0.15 (d = %.0f to %.0f Mpc).\n\n",
                std::log(1.023)/sig_l/Mpc, std::log(1.15)/sig_l/Mpc);

    // BAO anchor redshifts for W3 (inverse ladder, H0 = 67.4 +- 1.1)
    const std::vector<double> z_bao = {0.38, 0.51, 0.698, 1.48, 2.33};

    std::printf("[Scan] z_t grid (log, 0.001 -> 1100); gates W1>=72.0, W2<0.05 mag, W3<=68.5, W4<1%%\n");
    std::printf("  %-8s %-8s %-10s %-10s %-8s %-8s %s\n",
                "z_t", "W1:H0sh", "W2:step", "W3:H0bao", "W4:cmb%", "pass", "");
    int n_pass = 0;
    std::vector<double> zt_grid;
    for (double lz = -3.0; lz <= 3.05; lz += 0.05) zt_grid.push_back(std::pow(10.0, lz));
    // print a representative subset, evaluate all
    const std::vector<double> zt_print = {0.01, 0.023, 0.05, 0.10, 0.15, 0.23, 0.38, 0.51,
                                          1.0, 2.33, 5.0, 20.0, 100.0, 1100.0};
    auto evaluate = [&](double z_t, bool print) -> bool {
        Piecewise pw{sig_l, sig_g, std::log(1.0+z_t)/sig_l};
        // W1: SH0ES-style recovered H0 = mean over log-spaced SNe in window of c*z/d (low-z)
        double sum = 0; int n = 0;
        for (double lgz = std::log10(0.023); lgz <= std::log10(0.15)+1e-12; lgz += 0.02) {
            const double z = std::pow(10.0, lgz);
            sum += measured::c * std::log(1.0+z) / pw.d_of_z(z);  // strain-consistent estimator
            ++n;
        }
        const double H0_sh = (sum/n) * Mpc / 1e3;
        // W2: max |mu(piecewise) - mu(uniform sig_l)| over SN range
        double step = 0.0;
        for (double lgz = std::log10(0.023); lgz <= std::log10(2.3); lgz += 0.01) {
            const double z = std::pow(10.0, lgz);
            const double dmu = 5.0*std::log10(pw.d_of_z(z) / (std::log(1.0+z)/sig_l));
            step = std::max(step, std::fabs(dmu));
        }
        // W3: worst implied H0 at BAO redshifts
        double H0_bao = 0.0;
        for (double zb : z_bao) H0_bao = std::max(H0_bao, pw.sbar(zb)*measured::c*Mpc/1e3);
        // W4: CMB path-average shift
        const double cmb_shift = (pw.sbar(measured::z_rec)/sig_g - 1.0)*100.0;
        const bool p1 = H0_sh >= 72.0, p2 = step < 0.05, p3 = H0_bao <= 68.5,
                   p4 = std::fabs(cmb_shift) < 1.0;
        const bool pass = p1 && p2 && p3 && p4;
        if (print)
            std::printf("  %-8.3f %-8.2f %-10.3f %-10.2f %-8.3f %s%s%s%s -> %s\n",
                        z_t, H0_sh, step, H0_bao, cmb_shift,
                        p1?"1":"-", p2?"2":"-", p3?"3":"-", p4?"4":"-", pass?"PASS":"fail");
        return pass;
    };
    for (double zt : zt_grid) if (evaluate(zt, false)) ++n_pass;
    for (double zt : zt_print) evaluate(zt, true);

    std::printf("\n  Full grid: %d of %zu z_t values pass W1-W4 jointly.\n\n", n_pass, zt_grid.size());

    // The pincer, stated numerically
    Piecewise pw15{sig_l, sig_g, std::log(1.15)/sig_l};
    double step15 = 0;
    for (double lgz = std::log10(0.023); lgz <= std::log10(2.3); lgz += 0.01) {
        const double z = std::pow(10.0, lgz);
        step15 = std::max(step15, std::fabs(5.0*std::log10(pw15.d_of_z(z)/(std::log(1.0+z)/sig_l))));
    }
    std::printf("[Pincer]\n");
    std::printf("  z_t >= 0.15 (needed for W1): asymptotic mu-step = 5log10(sig_l/sig_g) = %.3f mag\n",
                5.0*std::log10(sig_l/sig_g));
    std::printf("    (at z_t = 0.15 the realised step is %.3f mag > 0.05 -> Pantheon+ sees it)\n", step15);
    std::printf("  z_t <= 0.023 (hides from SNe): SH0ES window then sits ENTIRELY in the global\n");
    std::printf("    zone -> recovered H0 = %.1f, not 73.0 -> tension unexplained.\n", H0g);
    std::printf("  z_t > 2.33 (hides from SNe the other way): BAO bins sit in the enhanced zone\n");
    std::printf("    -> implied BAO-ladder H0 = %.1f vs measured 67.4+-1.1 -> excluded.\n", H0l);
    std::printf("  No radial placement threads all three. (Phase B: CR12, DEGENERATE, not re-run.\n");
    std::printf("   Phase D: CR08, KILLED, not re-run.)\n\n");

    std::printf("VERDICT LINES\n");
    std::printf("  Isotropic radial sigma-gradient dissolution of the 8.4%% tension: %s\n",
                n_pass == 0 ? "KILLED (window scan empty)" : "window found (see table)");
    std::printf("  Anisotropic / line-of-sight-variance version (CR06 emission half): OPEN, out of scope.\n");
    std::printf("  H0 was not derived anywhere in this tool (anchors: 67.4, 73.04 OBSERVED).\n");
    return 0;
}
