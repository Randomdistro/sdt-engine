// NP16A04 reset, instrument 1 (2026-10-10): magnitude of the SDT displacement-volume cross-section. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <numbers>
using namespace sdt::laws; namespace M = sdt::laws::measured;
int main() {
    const double PI = std::numbers::pi;
    auto Rdisp = [&](double A) { double V = law_IV::V_disp_from_mass(A * M::m_p); return std::cbrt(3 * V / (4 * PI)); };
    { double V = law_IV::V_disp_from_mass(M::m_p), hand = 3 * M::m_p * M::c * M::c / law_I::P_conv; std::printf("[V1] V_disp(m_p) engine %.4e m^3 vs 3 m_p c^2/P_conv %.4e (rel %.1e) -> %s\n\n", V, hand, V / hand - 1, std::fabs(V / hand - 1) < 1e-12 ? "met" : "NOT MET"); }
    std::printf("target   R_disp(p)+R_disp(t) [m]   sigma_SDT [m^2]    [mb]          geometric scale pi(R_p(1+A^1/3))^2 [mb]   ratio\n");
    for (double A : {6.0, 12.0, 27.0, 56.0, 208.0, 238.0}) { double r = Rdisp(1) + Rdisp(A), s = PI * r * r, g = PI * std::pow(M::R_p * (1 + std::cbrt(A)), 2);
        std::printf("A=%5.0f  %.4e               %.4e        %.4e    %.4e                       %.2e\n", A, r, s, s / 1e-31, g / 1e-31, s / g); }
    std::printf("\nR_disp(proton) / R_p = %.3e\n", Rdisp(1) / M::R_p);
    return 0;
}
