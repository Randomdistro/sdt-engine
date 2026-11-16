// PPT14 reset, instrument 1 (2026-10-10): the SDT mass unit M0 = [pi^2 hbar^3 P_conv sqrt3 / (2 c^5)]^(1/4).
// Record: PPT14_RESET_ASSESSMENT_2026-10-10.md (scoped audit). Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <numbers>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static double M0(double hbar, double P, double c) { return std::pow(std::numbers::pi * std::numbers::pi * hbar * hbar * hbar * P * std::sqrt(3.0) / (2 * std::pow(c, 5)), 0.25); }
int main() {
    std::printf("PPT14 reset instrument 1 (2026-10-10)\n=====================================\n\n");
    // [V] units: scale length by L, time by T, mass by m -> hbar ~ m L^2/T, P ~ m/(L T^2), c ~ L/T ; M0 must scale as m^1 only
    { double L = 3.7, T = 0.41, m = 2.3, a = M0(M::hbar, law_I::P_conv, M::c), b = M0(M::hbar * m * L * L / T, law_I::P_conv * m / (L * T * T), M::c * L / T); bool ok = std::fabs(b / a / m - 1) < 1e-12;
      std::printf("[V] unit scaling: M0 scales as mass^%.12f (expect 1) -> %s\n\n", std::log(b / a) / std::log(m), ok ? "met" : "NOT MET"); if (!ok) return 1; }
    double P1 = law_I::P_conv, P2 = (M::R_CMB / M::l_P) * M::a_rad * std::pow(M::T_CMB, 4);
    double m1 = M0(M::hbar, P1, M::c), m2 = M0(M::hbar, P2, M::c), E = m1 * M::c * M::c / M::MeV_to_J / 1e6;
    std::printf("route 1 (engine P_conv = %.4e Pa): M0 = %.6e kg\nroute 2 (N u_CMB = %.4e Pa):       M0 = %.6e kg ; agreement %.1e -> %s\n", P1, m1, P2, m2, m2 / m1 - 1, std::fabs(m2 / m1 - 1) < 1e-12 ? "met" : "NOT MET");
    std::printf("M0 c^2 = %.4f TeV -> %s (registered band 0.5-2 TeV)\n\n", E, (E >= 0.5 && E <= 2.0) ? "CONFIRMED" : "NOT CONFIRMED");
    std::printf("input dependence: M0 = [pi^2 sqrt3/2]^(1/4) hbar^(3/4) c^(-5/4) (R_CMB/l_P)^(1/4) a^(1/4) T_CMB\n");
    std::printf("sensitivity: dM0/M0 = (1/4) dR_CMB/R_CMB ; R_CMB x2 -> M0 x %.4f ; T_CMB enters linearly\n", std::pow(2.0, 0.25));
    std::printf("in proton masses: M0/m_p = %.2f\n", m1 / M::m_p);
    return 0;
}
