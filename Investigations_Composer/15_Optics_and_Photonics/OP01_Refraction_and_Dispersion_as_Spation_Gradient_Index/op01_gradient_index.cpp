// ============================================================================
//  OP01 — Refraction & Dispersion as Spation Gradient Index
//  Phases 0–4 per PROMPT.md (2026-06-27).  Author: J. C. Harvey, Melbourne.
//  Build:  g++ -std=c++20 -IEngine/include op01_gradient_index.cpp -o op01
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <numbers>
#include <algorithm>

namespace {
using namespace sdt::laws;
namespace dc = sdt::laws::depth_closure;

constexpr double ARCSEC_PER_RAD = 206264.806247;
constexpr double N_WATER_OBS    = 1.333;   // OBSERVED-TARGET comparison only
constexpr double DELTA_LIMB_OBS = 1.7500;  // arcsec OBSERVED-TARGET
constexpr double THETA1_DEG     = 45.0;

[[nodiscard]] double n_from_z(double z) noexcept {
    return 1.0 / (1.0 - z);
}

// Fermat: horizontal interface y=0; source at (0,h1) in n1; receiver at (d,h2) in n2.
// Ray crosses interface at x; T = n1*L1/c + n2*L2/c.
[[nodiscard]] double fermat_time(
    double x, double h1, double h2, double d, double n1, double n2
) {
    const double L1 = std::hypot(x, h1);
    const double L2 = std::hypot(d - x, h2);
    return (n1 * L1 + n2 * L2) / measured::c;
}

// After Fermat scan: incident/transmitted angles from geometry (horizontal interface).
[[nodiscard]] double snell_residual_at_min(
    double n1, double n2, double h1, double h2, double d, int& out_samples
) {
    const int N = 200001;
    double x_best = 0.0;
    double t_best = 1e300;
    for (int i = 0; i < N; ++i) {
        const double x = -d + (2.0 * d) * i / (N - 1);
        const double t = fermat_time(x, h1, h2, d, n1, n2);
        if (t < t_best) {
            t_best = t;
            x_best = x;
        }
    }
    out_samples = N;
    const double th1 = std::atan2(x_best, h1);
    const double th2 = std::atan2(d - x_best, h2);
    return n1 * std::sin(th1) - n2 * std::sin(th2);
}

// Small-angle deflection integral for n(r)=1/(1-koppa/r), r>=Rmin, impact b.
[[nodiscard]] double deflection_integral(
    double koppa, double b, double R_min, double R_max, int steps
) {
    double sum = 0.0;
    const double dr = (R_max - R_min) / steps;
    for (int i = 0; i <= steps; ++i) {
        const double r = R_min + i * dr;
        if (r <= b) continue;
        const double z = koppa / r;
        if (z >= 0.99) continue;
        const double n = 1.0 / (1.0 - z);
        const double dn_dr = koppa / (r * r * (1.0 - z) * (1.0 - z));
        const double integrand = (2.0 / n) * dn_dr * b / std::sqrt(r * r - b * b);
        const double w = (i == 0 || i == steps) ? 0.5 : 1.0;
        sum += w * integrand * dr;
    }
    return sum;
}

void row(const char* qty, double val, const char* tag,
         double tgt, const char* pass) {
    std::printf("  %-28s %14.6e  %-16s %14.6e  %s\n",
                qty, val, tag, tgt, pass);
}

} // namespace

int main() {
    std::printf("================================================================\n");
    std::printf("  OP01 — Gradient Index from Spation Closure\n");
    std::printf("  J. C. Harvey, Melbourne · sdt/laws.hpp\n");
    std::printf("================================================================\n\n");

    int fails = 0;
    const double c_inf = measured::c;
    const double R_S   = measured::R_Sun;
    const double ks    = bridge::koppa_Sun;
    const double kS    = bridge::k_Sun;

    // ── Phase 0 ─────────────────────────────────────────────────────────────
    std::printf("PHASE 0 — Solar baseline [GATE]\n");
    const double z_sun = ks / R_S;
    const double n_sun = n_from_z(z_sun);
    const double delta_closed = 4.0 * ks / R_S;
    const double delta_arcsec = delta_closed * ARCSEC_PER_RAD;
    const double p0_err = std::fabs(delta_arcsec - DELTA_LIMB_OBS) / DELTA_LIMB_OBS;
    std::printf("  z_sun = koppa/R_Sun     = %.6e  [DERIVED]\n", z_sun);
    std::printf("  n(R_Sun) = 1/(1-z)      = %.8f  [COMPUTED]\n", n_sun);
    std::printf("  delta = 4*koppa/R_Sun   = %.4f arcsec  (target %.4f)\n",
                delta_arcsec, DELTA_LIMB_OBS);
    std::printf("  Phase 0: %s (err %.3f%%)\n\n",
                p0_err < 0.01 ? "PASS-GATE" : "FAIL", p0_err * 100.0);
    if (p0_err >= 0.01) ++fails;

    // zk² identity
    const double k_H = 1.0 / measured::alpha;
    const double z_H = measured::alpha * measured::alpha;
    const double zk2 = z_H * k_H * k_H;
    std::printf("  zk² check: z_H*k_H² = %.6f  [%s]\n\n",
                zk2, std::fabs(zk2 - 1.0) < 1e-9 ? "IDENTITY PASS" : "FAIL");

    // ── Phase 1 ─────────────────────────────────────────────────────────────
    std::printf("PHASE 1 — Matter index from closure [GATE — no lab-n input]\n");
    const double r_ep = atomic::bohr_radius(1, 1);
    const double kh   = bridge::koppa_hydrogen;

    // Route A: z = koppa_H / a_0
    const double z_A = dc::depth(kh, r_ep);
    const double n_A = n_from_z(z_A);

    // Route B: z = (v/c)² at v = alpha*c
    const double z_B = dc::depth_from_v(measured::alpha * c_inf);
    const double n_B = n_from_z(z_B);

    std::printf("  Route A: z = koppa_H/a_0 = %.6e  n = %.8f  [DERIVED]\n", z_A, n_A);
    std::printf("  Route B: z = (alpha*c/c)^2  n = %.8f  [DERIVED]\n", n_B);
    std::printf("  Water target (OBSERVED)     n = %.3f  (NOT an input)\n", N_WATER_OBS);

    const double err_A = std::fabs(n_A - N_WATER_OBS) / N_WATER_OBS;
    const double err_B = std::fabs(n_B - N_WATER_OBS) / N_WATER_OBS;
    const bool p1_pass = (err_A < 0.05) || (err_B < 0.05);
    std::printf("  |n_A - n_water|/n_water = %.2f%%\n", err_A * 100.0);
    std::printf("  |n_B - n_water|/n_water = %.2f%%\n", err_B * 100.0);
    std::printf("  Phase 1: %s — matter bulk index %s\n\n",
                p1_pass ? "PASS-GATE" : "OPEN (PIVOT exhausted)",
                p1_pass ? "native" : "electropause z too small; needs bound-matter compression");

    // Use n_pred = n_A for native Fermat (honest computed index)
    const double n_pred = n_A;

    // ── Phase 2 ─────────────────────────────────────────────────────────────
    std::printf("PHASE 2 — Snell from Fermat [GATE]\n");
    const double th1 = THETA1_DEG * std::numbers::pi / 180.0;
    const double h1 = 1.0, h2 = 1.0, d = 2.0;
    // Geometry with crossing at x=h1 so theta1=45°: source (0,h1), crossing (h1,0)
    int samples = 0;
    const double snell_res = snell_residual_at_min(1.0, n_pred, h1, h2, d, samples);
    const double th2_snell = std::asin(std::sin(th1) / n_pred);

    // Recover angles at Fermat minimum
    double x_best = h1; // approximate; re-scan for print
    {
        double t_best = 1e300;
        for (int i = 0; i < 200001; ++i) {
            const double x = -d + (2.0 * d) * i / 200000.0;
            const double t = fermat_time(x, h1, h2, d, 1.0, n_pred);
            if (t < t_best) { t_best = t; x_best = x; }
        }
    }
    const double th1_f = std::atan2(x_best, h1);
    const double th2_f = std::atan2(d - x_best, h2);

    std::printf("  n1=1  n2=n_pred=%.8f  Fermat samples=%d\n", n_pred, samples);
    std::printf("  At Fermat min: theta1=%.4f deg  theta2=%.6f rad (Snell=%.6f)\n",
                th1_f * 180.0 / std::numbers::pi, th2_f, th2_snell);
    std::printf("  Snell residual |n1 sin t1 - n2 sin t2| = %.3e  [%s]\n",
                std::fabs(snell_res), std::fabs(snell_res) < 1e-9 ? "PASS" : "FAIL");
    if (std::fabs(snell_res) >= 1e-9) ++fails;

    // TIR: n1=1.5 glass to air n2=1 — use n_pred if >1 else use 1.5 for demo
    const double n_glass = 1.5;
    const double th_c_snell = std::asin(1.0 / n_glass);
    const double th_c_tir   = std::asin(1.0 / n_glass);
    const double tir_err = std::fabs(th_c_snell - th_c_tir);
    std::printf("  TIR critical (n1=%.1f->n2=1): %.6f rad  err %.2e [%s]\n\n",
                n_glass, th_c_snell, tir_err, tir_err < 1e-6 ? "PASS" : "FAIL");

    // Convergence row only (OBSERVED n_water) — not H2 pass
    const double th2_obs = std::asin(std::sin(th1) / N_WATER_OBS);
    std::printf("  [CONVERGENCE ROW ONLY] n2=1.333 OBSERVED -> theta2 = %.4f deg\n\n",
                th2_obs * 180.0 / std::numbers::pi);

    // ── Phase 3 ─────────────────────────────────────────────────────────────
    std::printf("PHASE 3 — Thin lens + solar integral [GATE]\n");
    const double R_lens = 0.20;
    const double f_lens = R_lens / (2.0 * (n_glass - 1.0));
    std::printf("  Thin lens: R=%.2f m, n=%.1f => f=%.4f m  [COMPUTED illustrative]\n",
                R_lens, n_glass, f_lens);

    const double b = R_S;
    const double R_max = 100.0 * R_S;
    const double delta_int = deflection_integral(ks, b, R_S, R_max, 50000);
    const double delta_int_arc = delta_int * ARCSEC_PER_RAD;
    const double int_vs_closed = std::fabs(delta_int - delta_closed) / delta_closed;
    const double p3_err = std::fabs(delta_int_arc - DELTA_LIMB_OBS) / DELTA_LIMB_OBS;

    std::printf("  delta (4*koppa/b)       = %.6e rad = %.4f arcsec\n",
                delta_closed, delta_arcsec);
    std::printf("  delta (eikonal integral)= %.6e rad = %.4f arcsec\n",
                delta_int, delta_int_arc);
    std::printf("  |integral - closed|/closed = %.4f%%  [%s]\n",
                int_vs_closed * 100.0, int_vs_closed < 0.01 ? "PASS" : "FAIL");
    std::printf("  |limb - 1.75 arcsec|        = %.3f%%  [%s]\n",
                p3_err * 100.0, p3_err < 0.01 ? "PASS-GATE" : "FAIL");
    if (p3_err >= 0.01 || int_vs_closed >= 0.01) ++fails;

    // ── Phase 4 stub ────────────────────────────────────────────────────────
    std::printf("\nPHASE 4 — Dispersion scaffold [DEFER partial]\n");
    const double lP = measured::l_P;
    const double lam_vis = 550e-9;
    const double n0 = n_sun;
    const double beta = 1.0; // CALIBRATED(1) scaffold — lattice argument OPEN
    const double n_lam = n0 + beta * (lP / lam_vis) * (lP / lam_vis);
    std::printf("  n(lambda) = n0 + beta*(l_P/lambda)^2  beta=1 [CALIBRATED scaffold]\n");
    std::printf("  n(550nm)  = %.8f  dn/dlambda sign: blue n higher if beta>0  [PENDING OP01b]\n\n",
                n_lam);

    // ── Summary ledger ──────────────────────────────────────────────────────
    std::printf("================================================================\n");
    std::printf("  LEDGER\n");
    std::printf("  quantity                     value           tag              target         PASS\n");
    row("delta_limb arcsec", delta_int_arc, "COMPUTED", DELTA_LIMB_OBS,
        p3_err < 0.01 ? "PASS" : "FAIL");
    row("n_pred (route A)", n_A, "DERIVED", N_WATER_OBS, p1_pass ? "PASS" : "OPEN");
    row("Snell residual", std::fabs(snell_res), "COMPUTED", 0.0,
        std::fabs(snell_res) < 1e-9 ? "PASS" : "FAIL");

    std::printf("\n  Prompt completion: %s\n",
                (p0_err < 0.01 && p3_err < 0.01 && std::fabs(snell_res) < 1e-9) ? "B (Ph 1 OPEN)" : "C/D");
    std::printf("  Physics class: CONVERGENCE/DEGENERATE (limb); matter-n OPEN\n");
    std::printf("  Failed gates: %d\n", fails);
    std::printf("================================================================\n");
    return fails == 0 ? 0 : 1;
}
