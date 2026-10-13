// CR14 blank-slate run 1 (2026-10-11). Registration: CR14_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
// Saha ionisation balance, pure hydrogen: Branch A (LCDM-type dilution), Branch B (static vessel), density sweep D. No outcome is labelled DERIVED (R4).
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = 3.14159265358979323846, eV = 1.602176634e-19;
static double Sfun(double T) { const double kT = M::k_B * T, B = M::Ry_eV * eV; return std::pow(M::m_e * kT / (2.0 * PI * M::hbar * M::hbar), 1.5) * std::exp(-B / kT); }
static double xe(double T, double n) { const double r = Sfun(T) / n; // x^2/(1-x) = r  ->  x = (-r + sqrt(r^2 + 4r))/2
    if (r > 1e15) return 1.0; return 0.5 * (-r + std::sqrt(r * r + 4.0 * r)); }
static double Thalf(double n, double crit) { double lo = 300.0, hi = 1e6; for (int i = 0; i < 300; ++i) { double mid = 0.5 * (lo + hi); if (xe(mid, n) < crit) lo = mid; else hi = mid; } return 0.5 * (lo + hi); }
int main() {
    std::printf("CR14 blank-slate run 1 (registered in CR14_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    const double T0 = M::T_CMB, nb0 = bridge::release_acoustics::eta_bbn_deuterium * bridge::release_acoustics::photon_count(T0), B_over_k = M::Ry_eV * eV / M::k_B; int fails = 0;
    std::printf("n_gamma(T0) = %.6e m^-3 ; eta = %.2e (BBN deuterium, external input) ; n_b0 = n_H = %.6f m^-3 ; B/k_B = %.2f K\n\n", bridge::release_acoustics::photon_count(T0), bridge::release_acoustics::eta_bbn_deuterium, nb0, B_over_k);
    // V1 limits on Branch A densities
    { double z1 = 1e5 / T0 - 1.0, n1 = nb0 * std::pow(1 + z1, 3.0), z2 = 1e3 / T0 - 1.0, n2 = nb0 * std::pow(1 + z2, 3.0); double xh = xe(1e5, n1), xl = xe(1e3, n2); bool ok = xh > 0.999999 && xl < 1e-6; std::printf("[V1] x_e(1e5 K, Branch A density) = %.9f ; x_e(1e3 K, Branch A density) = %.3e -> %s\n", xh, xl, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // Branch A: solve for z at criterion
    auto branchA = [&](double crit, double& z, double& T, double& n) { double lo = 100.0, hi = 5000.0; for (int i = 0; i < 300; ++i) { double mid = 0.5 * (lo + hi), Tm = T0 * (1 + mid), nm = nb0 * std::pow(1 + mid, 3.0); if (xe(Tm, nm) > crit) hi = mid; else lo = mid; } z = 0.5 * (lo + hi); T = T0 * (1 + z); n = nb0 * std::pow(1 + z, 3.0); };
    double zA, TA, nA; branchA(0.5, zA, TA, nA);
    { bool ok = zA >= 1250 && zA <= 1450; std::printf("[V2] Branch A at x_e = 1/2: z = %.2f (window 1250-1450; textbook ~1370), T = %.1f K, n = %.4e m^-3 -> %s\n", zA, TA, nA, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { double T = Thalf(nb0, 0.5), a = 1.0 / (1.5 + B_over_k / T), h = 1e-4, nume = (std::log(Thalf(nb0 * std::exp(h), 0.5)) - std::log(Thalf(nb0 * std::exp(-h), 0.5))) / (2 * h); bool ok = std::fabs(nume / a - 1) < 0.01; std::printf("[V3] d ln T_half / d ln n at Branch B density: analytic %.6f, numeric %.6f, relative difference %.2e -> %s\n", a, nume, std::fabs(nume / a - 1), ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("\nVALIDATIONS NOT MET -> G0 (no branch result reportable)\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    std::printf("BRANCHES (criterion ; Branch A: z, T, n ; Branch B: T_half, N = T/T0 ; density ratio n_A/n_B ; sensitivity d ln T/d ln n at B (analytic))\n");
    for (double crit : {0.5, 0.1, 0.01}) { double z, T, n; branchA(crit, z, T, n); double TB = Thalf(nb0, crit); std::printf("  x_e = %.2f : A: z = %7.2f, T = %8.2f K, n = %.4e ; B: T = %8.2f K, N = %7.2f ; n_A/n_B = %.4e ; sensitivity %.5f\n", crit, z, T, n, TB, TB / T0, n / nb0, 1.0 / (1.5 + B_over_k / TB)); }
    { double TB = Thalf(nb0, 0.5), sens = 1.0 / (1.5 + B_over_k / TB); std::printf("\nR3 (non-discriminating iff sensitivity < 0.05): Branch B sensitivity %.5f -> %s\n", sens, sens < 0.05 ? "FIRES: a 9-order density difference moves the half-ionisation temperature by only the factor below; the Branch-B number cannot be cited as evidence for the vessel" : "does not fire"); std::printf("  the density difference between the branches at x_e = 1/2: n_A/n_B = %.4e (%.2f decades) ; T_half ratio T_A/T_B = %.4f\n", nA / nb0, std::log10(nA / nb0), TA / TB); }
    std::printf("\nDENSITY SWEEP D (n [m^-3] : T_half at x_e = 1/2 [K], N = T/T0, sensitivity):\n"); for (int e = -6; e <= 14; e += 2) { double n = std::pow(10.0, e), T = Thalf(n, 0.5); std::printf("  1e%+03d : %9.2f K  N = %8.2f  s = %.5f\n", e, T, T / T0, 1.0 / (1.5 + B_over_k / T)); }
    { double zr = bridge::release_acoustics::equality_loading; (void)zr; double TB = Thalf(nb0, 0.5); std::printf("\nAFTER THE FACT (not a target): engine entry T_release = %.1f K (T_CMB (1 + z_release), z_release = 1089, labelled OBSERVED in laws.hpp); Branch B T_half(1/2) = %.1f K, N = %.1f ; Branch A T_half(1/2) = %.1f K, z = %.1f\n", M::T_release, TB, TB / T0, TA, zA); }
    std::printf("\nLabel: COMPUTED (consistency of an imported relation, R4); no outcome is DERIVED.\n");
    return 0;
}
