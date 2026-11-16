// CR16 blank-slate run 1 (2026-10-11). Registration: CR16_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
// T1: P0 = a T0^4 / 3 against the quoted 1.3916e-14 Pa; T2: P_N = N^4 P0 identity. T3-T5 need the cosmological-sector document (not in the repository): PENDING_DATA.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <string>
namespace M = sdt::laws::measured;
static int agreeFigures(double a, double b) { // number of leading significant figures on which a and b agree (rounded comparison)
    int n = 0; for (int k = 1; k <= 8; ++k) { char sa[32], sb[32]; std::snprintf(sa, sizeof sa, "%.*e", k - 1, a); std::snprintf(sb, sizeof sb, "%.*e", k - 1, b); if (std::string(sa) == std::string(sb)) n = k; else break; } return n; }
int main() {
    std::printf("CR16 blank-slate run 1 (registered in CR16_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    const double a = M::a_rad, T0 = M::T_CMB, quoted = 1.3916e-14;
    const double P0 = a * T0 * T0 * T0 * T0 / 3.0; const double u = a * T0 * T0 * T0 * T0;
    std::printf("T1: a_rad = %.4e J/m^3/K^4, T_CMB = %.4f K : u = a T^4 = %.6e J/m^3 ; P0 = a T^4 / 3 = %.6e Pa ; quoted P0 = %.4e Pa ; relative difference %.3e ; agreeing significant figures (rounded) %d\n", a, T0, u, P0, quoted, P0 / quoted - 1.0, agreeFigures(P0, quoted));
    for (double dT : {-0.0006, 0.0, 0.0006}) { double T = T0 + dT, P = a * T * T * T * T / 3.0; std::printf("  FIRAS T = %.4f K : P0 = %.6e Pa (relative to the quoted %.3e)\n", T, P, P / quoted - 1.0); }
    double Tq = std::pow(3.0 * quoted / a, 0.25); std::printf("  the temperature that gives exactly the quoted P0: %.6f K (T_CMB %.4f K : difference %.2e K, %.2f of the FIRAS 1-sigma 0.0006 K)\n", Tq, T0, Tq - T0, (Tq - T0) / 0.0006);
    std::printf("  T1 rule (>= 4 significant figures): %s\n\n", agreeFigures(P0, quoted) >= 4 ? "MET: P0 is a function of T0, not an independent input" : "NOT MET");
    double worst = 0; std::printf("T2: P_N = N^4 P0 against a (N T0)^4 / 3:\n");
    for (double N : {1.0, 10.0, 100.0, 1100.0}) { double PN = std::pow(N, 4) * P0, PT = a * std::pow(N * T0, 4) / 3.0; double r = PN / PT - 1.0; worst = std::fmax(worst, std::fabs(r)); std::printf("  N = %6.0f : P_N = %.6e Pa, a T_N^4/3 = %.6e Pa, relative difference %.2e\n", N, PN, PT, r); }
    std::printf("  worst relative difference %.2e : the clause P_N = N^4 P0 follows from T_N = N T0 by Stefan-Boltzmann once P0 = a T0^4/3 (IDENTITY); postulate count reduced by one if T1 holds\n\n", worst);
    std::printf("T3 (dependency audit), T4 (parameter ledger), T5 (zero-parameter subset): PENDING_DATA (the Cosmological Sector document is not in the repository).\n");
    return 0;
}
