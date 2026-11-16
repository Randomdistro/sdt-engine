// S301 -> Sgr A* velocity map (2026-10-11). Om of Sgr A* from S301's period, eccentricity and pericentre speed alone
// (no distance, no GM, no R_S input); then circular / escape / S301-energy speeds mapped down to R_S = 2 Om.
// Inputs: arXiv:2609.06936 abstract (P = 8.68 yr, e = 0.9832, v_p = 25,600 km/s; "within 136 R_S"). Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <numbers>
namespace M = sdt::laws::measured;
int main() {
    const double c = M::c, PI = std::numbers::pi, yr = 365.25 * 86400.0;
    const double P = 8.68 * yr, e = 0.9832, vp = 2.56e7;                         // [MEASURED-INPUT] arXiv:2609.06936
    std::printf("S301 -> Sgr A* velocity map (2026-10-11)\n========================================\n");
    // V1: Kepler-in-Om round trip on a synthetic orbit (a = 1e14 m, Om = 6e9 m, e = 0.9): recover a and Om from (P, e, v_p)
    { double a0 = 1e14, O0 = 6e9, e0 = 0.9, P0 = 2 * PI * std::sqrt(a0 * a0 * a0 / (c * c * O0)), v0 = c * std::sqrt(O0 * (1 + e0) / (a0 * (1 - e0)));
      double a1 = v0 * P0 * std::sqrt((1 - e0) / (1 + e0)) / (2 * PI), O1 = 4 * PI * PI * a1 * a1 * a1 / (c * c * P0 * P0);
      bool ok = std::fabs(a1 / a0 - 1) < 1e-12 && std::fabs(O1 / O0 - 1) < 1e-12; std::printf("[V1] synthetic round trip: a %.3e, Om %.3e -> %s\n", a1, O1, ok ? "met" : "NOT MET"); if (!ok) return 1; }
    const double a = vp * P * std::sqrt((1 - e) / (1 + e)) / (2 * PI), Om = 4 * PI * PI * a * a * a / (c * c * P * P), rp = a * (1 - e), RS = 2 * Om, AU = 1.495978707e11;
    std::printf("\nS301 orbit from (P, e, v_p): a = %.4e m = %.1f AU ; r_p = %.4e m = %.2f AU\n", a, a / AU, rp, rp / AU);
    std::printf("Om(Sgr A*) = %.4e m = %.5f AU ; R_S = 2 Om = %.4e m\n", Om, Om / AU, RS);
    std::printf("check: r_p / R_S = %.1f (abstract: 'within 136 R_S') ; Om/r_p at pericentre = %.4e ; beta_p = %.5f\n", rp / RS, Om / rp, vp / c);
    // sensitivity: last-digit rounding of the three inputs
    { double dP = 0.005 / 8.68, de = 0.00005 / (1 - e) * 0.5 + 0.00005 / (1 + e) * 0.5, dv = 50.0 / 25600.0;   // half last digit; d ln a
      double dlna = std::sqrt(dP * dP + de * de + dv * dv), dlnO = std::sqrt(std::pow(3 * dv, 2) + std::pow(dP, 2) + std::pow(3 * de, 2));
      std::printf("rounding sensitivity (half last digit of P, e, v_p): a +/- %.2f%%, Om +/- %.2f%%\n\n", 100 * dlna, 100 * dlnO); }
    std::printf("Velocity map, r in units of Om (R_S = 2 Om). All speeds in units of c.\n");
    std::printf("  r/Om    r/R_S   ladder v=c*sqrt(Om/r)   1/r^2+1/r^3 law (C-009) v=c*sqrt(x(1+6x))   escape c*sqrt(2Om/r)   S301-energy orbit at this pericentre c*sqrt((1+e)Om/r)\n");
    const double rs[] = {272.0, 137.0, 100.0, 50.0, 20.0, 10.0, 6.0, 3.0, 2.0, 1.0};
    for (double r : rs) { double x = 1 / r; std::printf("  %6.1f  %6.1f   %10.5f              %10.5f                                  %10.5f             %10.5f\n", r, r / 2, std::sqrt(x), std::sqrt(x * (1 + 6 * x)), std::sqrt(2 * x), std::sqrt((1 + e) * x)); }
    std::printf("\nAt R_S (r = 2 Om): ladder circular %.4fc ; C-009 circular %.4fc ; escape %.4fc ; S301-energy pericentre %.4fc = %.0f km/s\n",
                std::sqrt(0.5), std::sqrt(0.5 * 4), 1.0, std::sqrt((1 + e) * 0.5), std::sqrt((1 + e) * 0.5) * c / 1e3);
    return 0;
}
