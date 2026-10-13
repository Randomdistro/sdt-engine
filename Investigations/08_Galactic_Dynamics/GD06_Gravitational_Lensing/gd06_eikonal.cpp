// GD06 — eikonal deflection by numerical integration (audit correction 2026-10-05)
// Replaces the closed-form-only print of gd06_gravitational_lensing.cpp. Index profile n(r) = (1 - koppa/r)^(-p).
//   p = 1 : the profile stated in PROMPT.md (c_local = c(1-z))
//   p = 2 : the profile of the GOM22 repair, c_far = c(1-z)^2 (n = c/c_far)
// Deflection of a straight-ray first-order eikonal: alpha(b) = integral over the path of d(ln n)/db, db perpendicular.
// koppa comes from the engine bridge (v^2 R / c^2 from orbit); no G, no M, no GM anywhere.
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
using namespace sdt::laws;
namespace { constexpr double AS = 206264.806247; }
static double dlnn_db(double b, double s, double kp, double p) {   // d(ln n)/db at (b, s along path)
    const double r = std::sqrt(b * b + s * s);
    const double dlnn_dr = -p * (kp / (r * r)) / (1.0 - kp / r);   // d/dr of -p ln(1 - kp/r)
    return dlnn_dr * (b / r);
}
static double deflection(double b, double kp, double p, int N) {
    // substitution s = b*sinh(u), u in [-U, U], ds = b*cosh(u) du ; Simpson in u
    const double U = 14.0; const double h = 2.0 * U / N; double sum = 0.0;
    for (int i = 0; i <= N; ++i) {
        const double u = -U + i * h, s = b * std::sinh(u);
        const double w = (i == 0 || i == N) ? 1.0 : (i % 2 ? 4.0 : 2.0);
        sum += w * dlnn_db(b, s, kp, p) * b * std::cosh(u);
    }
    return -(h / 3.0) * sum;   // bending toward the mass (positive magnitude)
}
int main() {
    const double kp = bridge::koppa_Sun, b = measured::R_Sun;
    std::printf("GD06 eikonal integration, koppa_Sun = %.4f m, b = R_Sun = %.4e m\n", kp, b);
    // V1: weak-field analytic check with a tiny koppa (alpha -> 2 p kp / b)
    for (double p : {1.0, 2.0}) {
        const double tiny = 1.0e-3, a = deflection(b, tiny, p, 40000), ex = 2.0 * p * tiny / b;
        std::printf("V1 p=%.0f weak-field check: numeric %.9e vs analytic %.9e rel %.2e %s\n", p, a, ex, a / ex - 1.0, std::fabs(a / ex - 1.0) < 1e-6 ? "PASS" : "FAIL");
    }
    // V2: two resolutions agree
    for (double p : {1.0, 2.0}) {
        const double a1 = deflection(b, kp, p, 20000), a2 = deflection(b, kp, p, 40000);
        std::printf("V2 p=%.0f resolution change %.2e %s\n", p, a2 / a1 - 1.0, std::fabs(a2 / a1 - 1.0) < 1e-8 ? "PASS" : "FAIL");
    }
    const double tgt = 1.7500;
    for (double p : {1.0, 2.0}) {
        const double a = deflection(b, kp, p, 40000) * AS;
        std::printf("p=%.0f : delta = %.4f arcsec  (VLBI %.4f)  rel %+.2f%%  gate <1%% : %s\n", p, a, tgt, (a / tgt - 1.0) * 100.0, std::fabs(a / tgt - 1.0) < 0.01 ? "PASS" : "FAIL");
    }
    return 0;
}
