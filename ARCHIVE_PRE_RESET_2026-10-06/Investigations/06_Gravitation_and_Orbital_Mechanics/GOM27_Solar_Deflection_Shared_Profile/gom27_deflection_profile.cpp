// GOM27 — Solar deflection from shared c_far profile
// Pre-registered: PROMPT.md. Frozen ϟ from GOM26 cal (Horizons 2025).
// Codebase audits are not inputs.

#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <numbers>
#include <vector>

using namespace sdt::laws;

namespace {

// GOM26 calibration invariant — DERIVED from Horizons 2025 pairwise μ.
// Must match .audit-tmp/gom26_run.txt (koppa_inv cal). Do not retune.
constexpr double kKoppaSun_m = 1476.351201;
constexpr double kArcsecPerRad = 206264.806247;

[[nodiscard]] constexpr auto n_of_r(double r, double koppa) -> double {
    const double z = koppa / r;
    if (!(z >= 0.0) || !(z < 1.0)) return -1.0;
    const double omz = 1.0 - z;
    return 1.0 / (omz * omz);
}

[[nodiscard]] auto turning_radius(double b, double koppa) -> double {
    double r = b - 2.0 * koppa;
    if (r <= koppa * 1.01) r = b * 0.999;
    for (int k = 0; k < 80; ++k) {
        const double n = n_of_r(r, koppa);
        if (n < 0.0) {
            r = 0.5 * (r + b);
            continue;
        }
        const double f = n * r - b;
        const double omz = 1.0 - koppa / r;
        const double np = -2.0 * std::pow(omz, -3.0) * (koppa / (r * r));
        const double df = n + r * np;
        const double step = f / df;
        r -= step;
        if (r <= koppa) r = koppa * 1.0000001;
        if (std::abs(step) < 1e-15 * b) break;
    }
    return r;
}

[[nodiscard]] auto deflection_rad(double b, double koppa, long N) -> double {
    const double r0 = turning_radius(b, koppa);
    const double n0 = n_of_r(r0, koppa);
    double acc = 0.0;
    for (long i = 0; i < N; ++i) {
        const double t0 = static_cast<double>(i) / static_cast<double>(N);
        const double t1 = static_cast<double>(i + 1) / static_cast<double>(N);
        const double t = 0.5 * (t0 + t1);
        const double u = 1.0 - t * t;
        if (u <= 0.0) continue;
        const double r = r0 / u;
        const double n = n_of_r(r, koppa);
        if (n < 0.0) continue;
        const double inside = n * n - n0 * n0 * u * u;
        if (inside <= 0.0) continue;
        const double dt = t1 - t0;
        acc += (n0 * 2.0 * t * dt) / std::sqrt(inside);
    }
    return 2.0 * acc - std::numbers::pi;
}

[[nodiscard]] bool validate() {
    std::puts("VALIDATION");
    bool ok = true;

    const double b = 5.0 * measured::R_Sun;
    const double k_small = kKoppaSun_m / 1000.0;
    const double d_small = deflection_rad(b, k_small, 400000);
    const double wf_small = 4.0 * k_small / b;
    const double ratio_a = d_small / wf_small;
    std::printf("  A reduced-koppa δ/(4ϟ/b) = %.6f  %s\n",
                ratio_a, std::abs(ratio_a - 1.0) < 0.05 ? "PASS" : "FAIL");
    ok = ok && std::abs(ratio_a - 1.0) < 0.05;

    const double d_num = deflection_rad(b, kKoppaSun_m, 800000);
    const double d_wf = 4.0 * kKoppaSun_m / b;
    const double rel = std::abs(d_num - d_wf) / d_wf;
    std::printf("  B weak-field b=5 R_Sun |num-wf|/wf = %.3e  %s\n",
                rel, rel < 0.02 ? "PASS" : "FAIL");
    ok = ok && d_num > 0.0 && rel < 0.02;

    const double d_coarse = deflection_rad(b, kKoppaSun_m, 100000);
    const double conv = std::abs(d_num - d_coarse) / d_num;
    std::printf("  C refinement |fine-coarse|/fine = %.3e  %s\n",
                conv, conv < 1e-3 ? "PASS" : "FAIL");
    ok = ok && conv < 1e-3;

    const double r0 = turning_radius(b, kKoppaSun_m);
    const double bi = n_of_r(r0, kKoppaSun_m) * r0;
    const double turn_err = std::abs(bi - b) / b;
    std::printf("  D turning |n r0 - b|/b = %.3e  %s\n",
                turn_err, turn_err < 1e-10 ? "PASS" : "FAIL");
    ok = ok && turn_err < 1e-10;

    std::printf("  VALIDATION: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

} // namespace

int main()
{
    std::puts("================================================================");
    std::puts("GOM27 — Shared-profile solar deflection");
    std::printf("Frozen ϟ_Sun = %.6f m (GOM26 cal; DERIVED; no retune)\n", kKoppaSun_m);
    std::puts("n(r) = 1/(1-ϟ/r)^2 = c/c_far");
    std::puts("Evidence: Horizons/HARPS/GOM26 stdout + this run; audits not inputs");
    std::puts("================================================================\n");

    // Delete-test: engine koppa unused
    std::printf("DELETE CHECK\n");
    std::printf("  bridge::koppa_Sun NOT USED = %.6f m\n", bridge::koppa_Sun);
    std::printf("  frozen GOM26 cal USED      = %.6f m\n\n", kKoppaSun_m);

    if (!validate()) {
        std::puts("INSTRUMENT VALIDATION FAILED — no prediction ledger");
        return 2;
    }

    const std::vector<double> b_over_R = {
        1.01, 1.05, 1.1, 1.2, 1.5, 2.0, 3.0, 5.0, 10.0
    };

    std::puts("COMPUTED PREDICTION LEDGER δ(b)  [LABEL: COMPUTED]");
    std::puts("  b/R_Sun   δ[arcsec]    4ϟ/b[arcsec]   (δ-4ϟ/b)/(4ϟ/b)");
    for (double x : b_over_R) {
        const double b = x * measured::R_Sun;
        const double d = deflection_rad(b, kKoppaSun_m, 800000);
        const double d_as = d * kArcsecPerRad;
        const double wf_as = (4.0 * kKoppaSun_m / b) * kArcsecPerRad;
        std::printf("  %7.2f  %11.6f  %11.6f  %+.3e\n",
                    x, d_as, wf_as, (d_as - wf_as) / wf_as);
    }

    const double d_limb = deflection_rad(measured::R_Sun, kKoppaSun_m, 1200000);
    const double d_limb_as = d_limb * kArcsecPerRad;
    const double wf_limb_as = (4.0 * kKoppaSun_m / measured::R_Sun) * kArcsecPerRad;
    std::printf("\n  limb b=R_Sun: δ = %.6f arcsec  (COMPUTED)\n", d_limb_as);
    std::printf("  weak-field 4ϟ/R_Sun = %.6f arcsec\n", wf_limb_as);

    std::puts("\nDATA GATE D5 — Fomalont VLBA 2009");
    std::puts("  Frozen PDF/HTML present under Datasets/solar_propagation_2026-08/raw/");
    std::puts("  Table products embed PPN propagation fits → MODEL-PROCESSED");
    std::puts("  No impact-parameter b-scan of absolute δ(b) independent of γ fit");
    std::puts("  STATUS: PENDING_DATA for whole-range empirical adjudication");
    std::puts("  Limb single-point literature scale (~1.75\") → UNADJUDICATED only\n");

    const double limb_lit = 1.7510; // arcsec — literature scale; not a pass criterion
    std::printf("  NOTE (not a decision rule): limb COMPUTED=%.6f vs lit-scale %.4f arcsec\n",
                d_limb_as, limb_lit);
    std::printf("  |Δ| = %.6f arcsec (informational; not EMPIRICALLY SURVIVES)\n",
                std::abs(d_limb_as - limb_lit));

    std::puts("\nDATA GATE D4 — Cassini ODF/TDF");
    std::puts("  Products frozen; residual reconstruction not performed this loop");
    std::puts("  STATUS: PENDING_DATA\n");

    std::puts("================================================================");
    std::puts("END GOM27 — see GOM27_ASSESSMENT.md");
    std::puts("================================================================");
    return 0;
}
