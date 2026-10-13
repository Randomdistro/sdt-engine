// OP01 v2 (audit correction 2026-10-05): banner derived from gates; Snell round trip labelled IDENTITY; solar deflection integrated.
// Matter index n(water) from bound-vortex z is NOT computed here (OPEN: the alpha^2-scale matter-index problem).
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
using namespace sdt::laws;
static double dlnn_db(double b, double s, double kp, double p) { const double r = std::sqrt(b*b + s*s); return (-p * (kp/(r*r)) / (1.0 - kp/r)) * (b/r); }
static double deflection(double b, double kp, double p, int N) {
    const double U = 14.0, h = 2.0*U/N; double sum = 0.0;
    for (int i = 0; i <= N; ++i) { const double u = -U + i*h, s = b*std::sinh(u); const double w = (i==0||i==N)?1.0:(i%2?4.0:2.0); sum += w*dlnn_db(b,s,kp,p)*b*std::cosh(u); }
    return -(h/3.0)*sum;
}
int main() {
    const double AS = 206264.806247, tgt = 1.7500;
    std::printf("OP01 v2\n");
    const double th1 = 45.0*std::numbers::pi/180.0, th2 = std::asin(std::sin(th1)/1.333);
    std::printf("Snell round trip (air->water) err %.2e rad  [IDENTITY - not scored]\n", std::fabs(th1 - std::asin(1.333*std::sin(th2))));
    int fails = 0;
    for (double p : {1.0, 2.0}) {
        const double a = deflection(measured::R_Sun, bridge::koppa_Sun, p, 40000)*AS;
        const bool ok = std::fabs(a/tgt - 1.0) < 0.01; if (p == 2.0 && !ok) ++fails;
        std::printf("solar limb deflection, n=(1-z)^-%.0f : %.4f arcsec rel %+.2f%% gate<1%% %s%s\n", p, a, (a/tgt-1.0)*100.0, ok ? "PASS" : "FAIL", p == 1.0 ? "  (profile stated in the old prompt)" : "  (c_far=c(1-z)^2, laws.hpp)");
    }
    std::printf("matter index n(water) from bound-vortex z : OPEN (not computed)\n");
    std::printf("VERDICT: %s - banner derived from gates; matter-index phase OPEN, class CONVERGENCE for the solar-limb row\n", fails ? "FAIL" : "PARTIAL");
    return fails ? 1 : 0;
}
