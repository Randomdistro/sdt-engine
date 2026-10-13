// CR03 reset, instrument 1 (2026-10-10): transfer-function closure algebra checked against the engine. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <numbers>
using namespace sdt::laws; namespace M = sdt::laws::measured;
int main() {
    const double PI = std::numbers::pi, h = 2 * PI * M::hbar;
    double Peff_closed = M::m_p * M::m_p * M::m_e * M::m_e * std::pow(M::c, 5) / (4 * PI * M::alpha * std::pow(M::hbar, 3));
    double arad_prompt = 2 * std::pow(PI, 5) * std::pow(M::k_B, 4) / (15 * h * h * h * M::c * M::c);   /* the prompt's expression: this is sigma (Stefan-Boltzmann) */
    double arad = 8 * std::pow(PI, 5) * std::pow(M::k_B, 4) / (15 * h * h * h * M::c * M::c * M::c);   /* attempt 2: radiation constant a = 4 sigma / c */
    double f_closed = Peff_closed * M::l_P / (M::R_CMB * arad * std::pow(M::T_CMB, 4));
    std::printf("CR03 reset instrument 1 (2026-10-10)\n====================================\n");
    std::printf("Stage 1: P_eff closed form m_p^2 m_e^2 c^5/(4 pi alpha hbar^3) = %.6e Pa ; engine law_III::P_eff = %.6e Pa ; rel %.2e\n", Peff_closed, law_III::P_eff, Peff_closed / law_III::P_eff - 1);
    std::printf("         (the engine form uses R_p_lock = 4 hbar/(m_p c) and r_e = alpha^2 a_0; a_0 = hbar/(m_e c alpha) makes them identical)\n");
    std::printf("         prompt expression 2 pi^5 k^4/(15 h^3 c^2) = %.6e (= sigma, W m^-2 K^-4; not a_rad)\n", arad_prompt);
    std::printf("         a_rad from {k_B, hbar, c} = %.6e ; engine measured a_rad = %.6e ; rel %.2e\n", arad, M::a_rad, arad / M::a_rad - 1);
    std::printf("Stage 2: f closed = %.6e ; engine f_transfer = %.6e ; rel %.2e\n", f_closed, law_III::f_transfer, f_closed / law_III::f_transfer - 1);
    std::printf("         dependence: f proportional to R_CMB^-1 (doubling R_CMB halves f: %.6f)\n", (Peff_closed * M::l_P / (2 * M::R_CMB * arad * std::pow(M::T_CMB, 4))) / f_closed);
    return 0;
}

