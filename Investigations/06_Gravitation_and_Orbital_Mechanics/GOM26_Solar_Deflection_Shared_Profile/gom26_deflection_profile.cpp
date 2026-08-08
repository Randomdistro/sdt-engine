// GOM26 — solar deflection from shared c_far profile (PROMPT.md)
// Frozen ϟ from GOM25b; no retuning.
//
// Index from far-frame relay speed: n = c / c_far = 1/(1 − ϟ/r)²
// Ray integral (isotropic spherical medium):
//   φ_half = ∫_0^1 n(r0) du / √( n(r0/u)² − n(r0)² u² )
//   δ = 2 φ_half − π
// with impact parameter b = n(r0) r0 (turning-point condition).

#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <numbers>
#include <vector>

using namespace sdt::laws;

namespace {

constexpr double kKoppaSun_m = 1476.664437; // GOM25b freeze
constexpr double kArcsecPerRad = 206264.806247;

[[nodiscard]] constexpr auto n_of_r(double r, double koppa) -> double {
    const double z = koppa / r;
    if (!(z >= 0.0) || !(z < 1.0)) return -1.0;
    const double omz = 1.0 - z;
    return 1.0 / (omz * omz);
}

// Solve b = n(r0) r0 for r0 given impact parameter b.
[[nodiscard]] auto turning_radius(double b, double koppa) -> double {
    // Start from weak-field guess r0 ≈ b - 2 koppa (n≈1+2ϟ/r).
    double r = b - 2.0 * koppa;
    if (r <= koppa * 1.01) r = b * 0.999;
    for (int k = 0; k < 80; ++k) {
        const double n = n_of_r(r, koppa);
        if (n < 0.0) { r = 0.5 * (r + b); continue; }
        const double f = n * r - b;
        // df/dr ≈ n + r n'(r); n=(1-ϟ/r)^{-2}, n' = -2(1-ϟ/r)^{-3}*(ϟ/r²)
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
    // u = 1 - t² densifies samples at the turning point u→1
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
        // du = -2 t dt; integrate t:0→1 ⇒ factor 2t dt
        const double dt = t1 - t0;
        acc += (n0 * 2.0 * t * dt) / std::sqrt(inside);
    }
    return 2.0 * acc - std::numbers::pi;
}

[[nodiscard]] bool validate() {
    std::puts("VALIDATION");
    bool ok = true;

    // A: reduced-koppa continuity (koppa=0 is analytic δ=0; ϟ=1e-6 m underflows
    // 2φ−π against double precision, so use ϟ = ϟ_Sun/1000 still ≪ solar weak field).
    const double b = 5.0 * measured::R_Sun;
    const double k_small = kKoppaSun_m / 1000.0;
    const double d_small = deflection_rad(b, k_small, 400000);
    const double wf_small = 4.0 * k_small / b;
    std::printf("  A reduced-koppa δ/(4ϟ/b) = %.6f\n", d_small / wf_small);
    ok = ok && std::abs(d_small / wf_small - 1.0) < 0.05;

    // B: weak field at b=5 R_Sun with solar koppa should approach 4ϟ/b
    const double d_num = deflection_rad(b, kKoppaSun_m, 800000);
    const double d_wf = 4.0 * kKoppaSun_m / b;
    const double rel = std::abs(d_num - d_wf) / d_wf;
    std::printf("  B weak-field b=5 R_Sun\n");
    std::printf("    numerical = %.6e rad = %.6f arcsec\n", d_num, d_num * kArcsecPerRad);
    std::printf("    4ϟ/b      = %.6e rad = %.6f arcsec\n", d_wf, d_wf * kArcsecPerRad);
    std::printf("    |num-wf|/wf = %.3e\n", rel);
    ok = ok && d_num > 0.0 && rel < 0.02;

    // C: step refinement
    const double d_coarse = deflection_rad(b, kKoppaSun_m, 100000);
    const double conv = std::abs(d_num - d_coarse) / d_num;
    std::printf("  C refinement |fine-coarse|/fine = %.3e  %s\n",
                conv, conv < 1e-3 ? "PASS" : "FAIL");
    ok = ok && conv < 1e-3;

    // D: turning-point identity b = n(r0)r0
    const double r0 = turning_radius(b, kKoppaSun_m);
    const double bi = n_of_r(r0, kKoppaSun_m) * r0;
    std::printf("  D turning |n r0 - b|/b = %.3e  %s\n\n",
                std::abs(bi - b) / b, std::abs(bi - b) / b < 1e-10 ? "PASS" : "FAIL");
    ok = ok && std::abs(bi - b) / b < 1e-10;

    std::printf("  VALIDATION: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

} // namespace

int main()
{
    std::puts("================================================================");
    std::puts("GOM26 — Shared-profile solar deflection prediction");
    std::printf("Frozen ϟ_Sun = %.6f m (GOM25b)\n", kKoppaSun_m);
    std::puts("n(r) = 1/(1-ϟ/r)^2 = c/c_far");
    std::puts("================================================================\n");

    if (!validate()) {
        std::puts("INSTRUMENT VALIDATION FAILED — no prediction ledger published");
        return 2;
    }

    const std::vector<double> b_over_R = {
        1.01, 1.05, 1.1, 1.2, 1.5, 2.0, 3.0, 5.0, 10.0
    };

    std::puts("COMPUTED PREDICTION LEDGER δ(b)");
    std::puts("  b/R_Sun   δ[arcsec]    4ϟ/b[arcsec]   rel(δ-4ϟ/b)");
    for (double x : b_over_R) {
        const double b = x * measured::R_Sun;
        const double d = deflection_rad(b, kKoppaSun_m, 800000);
        const double d_as = d * kArcsecPerRad;
        const double wf_as = (4.0 * kKoppaSun_m / b) * kArcsecPerRad;
        std::printf("  %7.2f  %11.6f  %11.6f  %+.3e\n",
                    x, d_as, wf_as, (d_as - wf_as) / wf_as);
    }

    const double d_limb = deflection_rad(measured::R_Sun, kKoppaSun_m, 1200000);
    std::printf("\n  limb b=R_Sun: δ = %.6f arcsec\n", d_limb * kArcsecPerRad);
    std::printf("  weak-field 4ϟ/R_Sun = %.6f arcsec\n",
                (4.0 * kKoppaSun_m / measured::R_Sun) * kArcsecPerRad);

    std::puts("\nDATA GATE");
    std::puts("  VLBI/optical limb summaries (~1.75\") are single-point,");
    std::puts("  reduction-dependent comparators — not a b-scan table.");
    std::puts("  STATUS: PENDING_DATA for whole-range empirical adjudication");
    std::puts("  Limb single-point comparison capped UNADJUDICATED if quoted.\n");

    // Optional single-point note (not a pass criterion)
    const double limb_obs_nominal = 1.7510; // arcsec — literature scale, MODEL-PROCESSED
    std::printf("  NOTE (not a decision): limb COMPUTED=%.6f vs nominal %.4f arcsec\n",
                d_limb * kArcsecPerRad, limb_obs_nominal);

    std::puts("================================================================");
    return 0;
}
