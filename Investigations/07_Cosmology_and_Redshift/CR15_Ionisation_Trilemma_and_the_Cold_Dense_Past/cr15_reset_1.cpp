// CR15 blank-slate run 1 (2026-10-12). Registration: CR15_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
// Saha balance under the postulate sets of the trilemma: T2 (B ~ N^-2, T ~ N, n ~ N^3), T3 (Prop 5: T ~ N^-2), T4 (diluting branch), T5 (bridge exponent scan).
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = 3.14159265358979323846, eV = 1.602176634e-19;
// ln(S/n) with B, T, n given
static double lnSn(double T, double B, double n) { const double kT = M::k_B * T; return 1.5 * std::log(M::m_e * kT / (2.0 * PI * M::hbar * M::hbar)) - B / kT - std::log(n); }
static double xeFromLn(double L) { if (L > 700) return 1.0; if (L < -700) return std::exp(0.5 * L); double r = std::exp(L); return 2.0 / (1.0 + std::sqrt(1.0 + 4.0 / r)); }   // stable root of x^2/(1-x) = r (x ~ sqrt(r) for small r)
int main() {
    std::printf("CR15 blank-slate run 1 (registered in CR15_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    const double T0 = M::T_CMB, B0 = M::Ry_eV * eV, nb0 = bridge::release_acoustics::eta_bbn_deuterium * bridge::release_acoustics::photon_count(T0), B0kT0 = B0 / (M::k_B * T0); int fails = 0;
    auto xe_cr14 = [&](double T, double n) { return xeFromLn(lnSn(T, B0, n)); };
    { double xh = xe_cr14(1e5, nb0 * std::pow(1e5 / T0, 3.0)), xl = xe_cr14(1e3, nb0 * std::pow(1e3 / T0, 3.0)); bool ok = xh > 0.999999 && xl < 1e-6; std::printf("[V1] limits: x_e(1e5 K) = %.9f, x_e(1e3 K) = %.3e -> %s\n", xh, xl, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    auto zhalf = [&](double crit) { double lo = 100, hi = 5000; for (int i = 0; i < 300; ++i) { double mid = 0.5 * (lo + hi); double x = xe_cr14(T0 * (1 + mid), nb0 * std::pow(1 + mid, 3.0)); if (x > crit) hi = mid; else lo = mid; } return 0.5 * (lo + hi); };
    double zA = zhalf(0.5); { bool ok = zA >= 1250 && zA <= 1450; std::printf("[V2] Branch A (n ~ N^3, T = N T0) at x_e = 1/2: z = %.2f (window 1250-1450) -> %s\n", zA, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { auto Th = [&](double n) { double lo = 300, hi = 1e6; for (int i = 0; i < 300; ++i) { double mid = 0.5 * (lo + hi); if (xe_cr14(mid, n) < 0.5) lo = mid; else hi = mid; } return 0.5 * (lo + hi); }; double h = 1e-4, T = Th(nb0), a = 1.0 / (1.5 + B0kT0 * T0 / T), nu = (std::log(Th(nb0 * std::exp(h))) - std::log(Th(nb0 * std::exp(-h)))) / (2 * h); bool ok = std::fabs(nu / a - 1) < 0.01; std::printf("[V3] sensitivity analytic %.6f, numeric %.6f -> %s\n", a, nu, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\nT1: PENDING_DATA (the [D]-tagged numbers of Parts VI-IX are in a document that is not in the repository)\n\n");
    // T2
    std::printf("T2: B = B0/N^2, T = T0 N, n = n_b0 N^3 ; B0/(k T0) = %.1f ; ln(S/n) and x_e over N:\n", B0kT0);
    auto L2 = [&](double N) { return lnSn(T0 * N, B0 / (N * N), nb0 * N * N * N); };
    double Nprev = 1, Lprev = L2(1), Nhalf = -1; for (double N = 1.0; N <= 3000.0; N *= 1.01) { double L = L2(N); if (Nhalf < 0 && L > std::log(0.5) && Lprev <= std::log(0.5)) { double lo = Nprev, hi = N; for (int i = 0; i < 200; ++i) { double mid = 0.5 * (lo + hi); if (L2(mid) > std::log(0.5)) hi = mid; else lo = mid; } Nhalf = 0.5 * (lo + hi); } Nprev = N; Lprev = L; }
    for (double N : {1.0, 3.0, 5.0, 8.0, 10.0, 11.0, 12.0, 15.0, 20.0, 50.0, 100.0, 300.0, 1100.0, 3000.0}) { double L = L2(N); std::printf("  N = %7.1f : B/kT = %12.4f, ln(S/n) = %12.4f, x_e = %.6e\n", N, B0kT0 / (N * N * N), L, xeFromLn(L)); }
    bool ionAbove = true; for (double N = (Nhalf > 0 ? Nhalf * 1.001 : 1); N <= 3000; N *= 1.05) if (xeFromLn(L2(N)) <= 0.5) ionAbove = false;
    std::printf("  half-ionisation crossing x_e = 1/2 at N_half = %.4f ; x_e > 1/2 for every N above it up to 3000: %s ; at N = 1100: x_e = %.9f\n\n", Nhalf, ionAbove ? "yes" : "NO", xeFromLn(L2(1100.0)));
    // T3
    std::printf("T3: Prop 5 as written: B = B0/N^2, T = T0/N^2 (B/kT = %.1f constant), n = n_b0 N^3 :\n", B0kT0); bool mono = true; double prev = 1e300, maxx = 0;
    for (double N = 1.0; N <= 3000.0; N *= 1.01) { double L = lnSn(T0 / (N * N), B0 / (N * N), nb0 * N * N * N); if (L > prev + 1e-9) mono = false; prev = L; maxx = std::fmax(maxx, xeFromLn(L)); }
    for (double N : {1.0, 10.0, 100.0, 1100.0}) { double L = lnSn(T0 / (N * N), B0 / (N * N), nb0 * N * N * N); std::printf("  N = %7.1f : T = %.3e K, ln(S/n) = %14.4f, ln x_e ~ %14.4f\n", N, T0 / (N * N), L, L); }
    std::printf("  ln(S/n) monotonically decreasing in N: %s ; maximum x_e over N in [1, 3000]: %.3e (underflows to 0 in double) -> %s\n\n", mono ? "yes" : "NO", maxx, (mono && maxx < 0.5) ? "no ionised era exists under Prop 5 as written" : "an ionised era exists");
    // T4
    std::printf("T4: the diluting branch (n = n_b0 N^3, T = T0 N, B constant) is CR14 Branch A: z(x_e = 1/2) = %.2f (identity with V2). Optical-depth half (Thomson tau over the document's path length): PENDING_DATA.\n\n", zA);
    // T5
    std::printf("T5: n = n_b0 N^(4s), T = T0 N, B constant: N_half(s):\n");
    auto Nh = [&](double s) { double lo = 2, hi = 5e4; for (int i = 0; i < 300; ++i) { double mid = 0.5 * (lo + hi); double x = xeFromLn(lnSn(T0 * mid, B0, nb0 * std::pow(mid, 4.0 * s))); if (x > 0.5) hi = mid; else lo = mid; } return 0.5 * (lo + hi); };
    for (double s : {0.0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 1.0}) std::printf("  s = %.3f (n ~ N^%.2f): N_half = %8.2f, T = %8.1f K\n", s, 4 * s, Nh(s), T0 * Nh(s));
    { double lo = 0.0, hi = 1.0; for (int i = 0; i < 200; ++i) { double mid = 0.5 * (lo + hi); if (Nh(mid) > 1100.0) hi = mid; else lo = mid; } std::printf("  the exponent that the struck target N = 1100 would require (reported as such, not as a result): s = %.5f (n ~ N^%.4f)\n", 0.5 * (lo + hi), 4 * 0.5 * (lo + hi)); }
    std::printf("\nLabel: COMPUTED; Saha is imported (R4 of CR14); nothing is DERIVED. No comparison with the reionisation epoch is made (D5).\n");
    return 0;
}
