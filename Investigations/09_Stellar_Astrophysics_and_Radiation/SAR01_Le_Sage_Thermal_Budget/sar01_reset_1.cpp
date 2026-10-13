// SAR01 blank-slate run 1 (2026-10-08): leakage ceilings eta = (heat budget)/(throughput intercepted) for the throughput candidates the engine defines.
// The three candidates are fixed here before the run: (1) the CMB flux through the Earth's cross-section; (2) the convergence flux P_conv c through it; (3) P_eff c through it.
// Constants from sdt::laws; the Earth radius and the geothermal budget are [ext]/[prompt]. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <numbers>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

int main() {
    std::printf("SAR01 blank-slate run 1: leakage ceilings for three throughput definitions\n=========================================================================\n\n");
    const double PI = std::numbers::pi, c = M::c, R_E = 6.371e6, geo = 47e12;                    // [ext] Earth radius; [prompt] 47 TW geothermal
    const double A = PI * R_E * R_E;
    // validation: the CMB flux of the engine equals u c / 4 (the flux through one side of a surface in an isotropic bath), and the engine's P_rad = u/3
    double Fchk = law_I::u_CMB * c / 4.0;
    bool v = std::fabs(Fchk / law_II::F_CMB - 1) < 5e-3 && std::fabs(law_I::P_rad * 3 / law_I::u_CMB - 1) < 1e-12;
    std::printf("[V] u c/4 = %.5e W/m^2 against law_II::F_CMB = %.5e (relative %.1e) ; 3 P_rad/u - 1 = %.1e -> %s\n\n", Fchk, law_II::F_CMB, Fchk / law_II::F_CMB - 1, law_I::P_rad * 3 / law_I::u_CMB - 1, v ? "met" : "NOT MET");
    if (!v) return 1;
    struct C { const char* nm; double flux; } cs[3] = {{"(1) CMB flux F_CMB (one side of the cross-section)", law_II::F_CMB}, {"(2) convergence flux P_conv c", law_I::P_conv * c}, {"(3) P_eff c", law_III::P_eff * c}};
    std::printf("Earth cross-section pi R^2 = %.4e m^2 ; heat budget (geothermal) = %.3e W\n", A, geo);
    for (auto& k : cs) { double P = k.flux * A; std::printf("  %-52s flux %.4e W/m^2 ; throughput through pi R^2 = %.4e W ; eta_max = 47 TW / throughput = %.4e\n", k.nm, k.flux, P, geo / P); }
    std::printf("\nspread of the ceilings over the three definitions: log10(eta_max) from %.1f to %.1f\n", std::log10(geo / (cs[1].flux * A)), std::log10(geo / (cs[0].flux * A)));
    std::printf("the prompt's quoted earlier ceiling 4.4e-18 corresponds to a throughput of %.3e W (47 TW / 4.4e-18); ratios to the three throughputs: %.3e, %.3e, %.3e\n", geo / 4.4e-18, geo / 4.4e-18 / (cs[0].flux * A), geo / 4.4e-18 / (cs[1].flux * A), geo / 4.4e-18 / (cs[2].flux * A));
    // Amendment 1 (made after the run above and after the prompt's quoted ceiling was compared; found by back-solving the quoted ceiling, therefore not a test):
    // candidate (4): the power redirected to produce a force F is F c (a flux moving at c carries energy = momentum x c); F = the Sun's pull on the Earth = M_E c^2 koppa_Sun/AU^2 (M_E [ext] 5.972e24 kg).
    { const double M_E = 5.972e24, kop = bridge::koppa_Sun_from_precession, g1 = c * c * kop / (M::AU * M::AU), F = M_E * g1, P = F * c;
      std::printf("\n[Amendment 1, post-seen] (4) redirected power F c with F = M_E c^2 koppa/AU^2: acceleration at 1 AU = %.5e m/s^2, F = %.4e N, F c = %.4e W ; eta_max = 47 TW/(F c) = %.4e\n", g1, F, P, geo / P);
      std::printf("     against the prompt's quoted ceiling 4.4e-18: ratio %.4f ; the same definition with the Earth's weight (M_E g, g = 9.80665 [ext]): F c = %.4e W, eta_max = %.4e\n", geo / P / 4.4e-18, M_E * 9.80665 * c, geo / (M_E * 9.80665 * c)); }
    return 0;
}
