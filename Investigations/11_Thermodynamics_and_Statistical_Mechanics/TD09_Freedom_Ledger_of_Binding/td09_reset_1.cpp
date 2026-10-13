// TD09 reset, instrument 1 (2026-10-10): freedom ledger of binding; flip temperature.
// Record: TD09_RESET_ASSESSMENT_2026-10-10.md (gates from PROMPT.md, unchanged). Written afresh. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <numbers>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = std::numbers::pi, Eb = 2.224573 * M::MeV_to_J, eta = 6.13e-10;   // [MEASURED-INPUT per PROMPT]
static double n_gamma(double kT) { double x = kT / (M::hbar * M::c); return 2 * bridge::release_acoustics::zeta3 / (PI * PI) * x * x * x; }
static double S0(double kT) { return 0.75 * std::pow(M::m_d / (M::m_p * M::m_n), 1.5) * std::pow(2 * PI * M::hbar * M::hbar / kT, 1.5); }
static double ratio(double kT, double Xn) { double nb = eta * n_gamma(kT); return Xn * nb * S0(kT) * std::exp(Eb / kT); }   // n_d/n_p, undepleted n_n
static double dfree(double kT, double Xn) { double nb = eta * n_gamma(kT); double dlnW = std::log(1.0) - std::log(Xn * nb * S0(kT)); return Eb / kT - dlnW; }  // ledger at n_d/n_p = 1
template <class F> static double bisect(F f, double lo, double hi) { double flo = f(lo); for (int i = 0; i < 300; ++i) { double m = 0.5 * (lo + hi), fm = f(m); if ((fm > 0) == (flo > 0)) { lo = m; flo = fm; } else hi = m; } return 0.5 * (lo + hi); }
int main() {
    std::printf("TD09 reset instrument 1 (2026-10-10)\n====================================\n\n");
    const double MeV = M::MeV_to_J; int bad = 0;
    { double n = n_gamma(M::k_B * 2.7255); bool ok = std::fabs(n / 4.107e8 - 1) < 1e-3; std::printf("[V1] n_gamma(2.7255 K) = %.4e m^-3 (known ~4.107e8) -> %s\n", n, ok ? "met" : "NOT MET"); bad += !ok; }
    { double kT = 0.1 * MeV, a = S0(kT) * n_gamma(kT), L = 2.0, Ms = 3.0, T = 0.5; (void)L; (void)Ms; (void)T;  // S0 [m^3] x n [m^-3] dimensionless: check by scaling hbar^2/kT -> length^2 consistency
      double r1 = S0(kT) / std::pow(M::hbar * M::hbar / (M::m_p * kT), 1.5), r2 = S0(2 * kT) / std::pow(M::hbar * M::hbar / (M::m_p * 2 * kT), 1.5); bool ok = std::fabs(r1 / r2 - 1) < 1e-12 && a > 0;
      std::printf("[V2] S0 scales as (hbar^2/(m kT))^(3/2) (m^3): ratio at kT, 2kT = %.15f -> %s\n", r1 / r2, ok ? "met" : "NOT MET"); bad += !ok; }
    { double r = bisect([](double x) { return x * x - 2; }, 0, 2); bool ok = std::fabs(r - std::sqrt(2.0)) < 1e-14; std::printf("[V3] bisection root of x^2 - 2: %.15f -> %s\n\n", r, ok ? "met" : "NOT MET"); bad += !ok; }
    if (bad) { std::printf("VALIDATIONS NOT MET\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");
    // P2 cold universe
    { double kT = M::k_B * 300.0; std::printf("P2 (statement): at 300 K, E_b/kT = %.4e nats ; configurational cost ln(1/(Xn n_b S0)) at the 300 K bath with n_b = eta n_gamma: %.2f nats\n\n", Eb / kT, -std::log((1.0 / 8) * eta * n_gamma(kT) * S0(kT))); }
    for (double Xr : {1.0 / 7, 1.0}) {
        double Xn = Xr / (1 + Xr);
        double Ts = bisect([&](double kT) { return ratio(kT, Xn) - 1; }, 0.005 * MeV, 1.0 * MeV) / MeV;
        double Tl = bisect([&](double kT) { return dfree(kT, Xn); }, 0.005 * MeV, 1.0 * MeV) / MeV;
        double kT = Ts * MeV;
        std::printf("X_n/X_p = %s : T_flip (Saha route) = %.6f MeV ; (ledger route) = %.6f MeV ; agreement %.1e %s\n", Xr < 0.5 ? "1/7 (primary)" : "1   (sensitivity)", Ts, Tl, Tl / Ts - 1, std::fabs(Tl / Ts - 1) < 1e-12 ? "[P1 identity met]" : "[P1 NOT met]");
        std::printf("   at T_flip: E_b/kT = %.3f nats ; configurational cost = %.3f nats ; ln(1/eta) = %.3f ; T_flip = %.3e K -> G3 %s\n", Eb / kT, -std::log(Xn * eta * n_gamma(kT) * S0(kT)), std::log(1 / eta), kT / M::k_B, (Ts >= 0.035 && Ts <= 0.17) ? "PASS (in [0.035, 0.17] MeV)" : "FAIL");
    }
    return 0;
}

