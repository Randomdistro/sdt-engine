// TD09 Round 2 (2026-10-14): the flip temperature for the old list {p, n, d} (validation) and the native list {p, e, d}.
// Registration: TD09_RESET_ASSESSMENT_2026-10-14.md sections 0-2 (written before this file existed).
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = 3.14159265358979323846;
static double mp, me, mn;
static const double eta0 = 6.13e-10, Bold = 2.224573, Bnat = 1.442246;
static double ngam(double T) { return 2.0 * bridge::release_acoustics::zeta3 / (PI * PI) * T * T * T; }
// old list: f(T) = ln(K n_n) with n_d = n_p, n_n = n_p r, n_B = n_p (1 + r + 2) = eta n_gamma
static double fOld(double T, double r, double eta) {
    const double md = mp + mn - Bold, gd = 3, gp = 2, gn = 2; const double np = eta * ngam(T) / (1.0 + r), nn = r * np;   // Amendment 1: free-nucleon convention n_B = n_p + n_n (deuterons not counted)
    const double lnK = std::log(gd / (gp * gn)) + 1.5 * std::log(md / (mp * mn)) + 1.5 * std::log(2.0 * PI / T) + Bold / T;
    return lnK + std::log(nn); }
// native list: n_d = n_p, n_e = 2 n_p, n_B = 3 n_p; f = ln(K n_p n_e) = ln(2 K n_p^2)
static int conv = 1;   // 1: free-baryon convention n_B = n_p (deuterons not counted; the convention that reproduces V1); 2: full count n_B = n_p + 2 n_d = 3 n_p
static double fNat(double T, double gd, double eta, double B) {
    const double md = 2 * mp + me - B, gp = 2, ge = 2; const double np = eta * ngam(T) / (conv == 1 ? 1.0 : 3.0), ne = 2.0 * np;
    const double lnK = std::log(gd / (gp * gp * ge)) + 1.5 * std::log(md / (mp * mp * me)) + 3.0 * std::log(2.0 * PI / T) + B / T;
    return lnK + std::log(np * ne); }
template <class F> static double bisect(F f) { double lo = 0.01, hi = 1.0; // f decreases with T? find sign structure: f(lo) > 0 (bound dominates), f(hi) < 0
    for (int i = 0; i < 200; ++i) { double mid = 0.5 * (lo + hi); if (f(mid) > 0) lo = mid; else hi = mid; } return 0.5 * (lo + hi); }
int main() {
    std::printf("TD09 Round 2 (registered in TD09_RESET_ASSESSMENT_2026-10-14.md)\n=======================================================================\n\n");
    const double MeVJ = 1.602176634e-13; mp = M::m_p * M::c * M::c / MeVJ; me = M::m_e * M::c * M::c / MeVJ; mn = mp + me + 0.782347;
    std::printf("m_p = %.6f MeV, m_e = %.6f MeV, m_n (m_p + m_e + 0.782347) = %.6f MeV ; eta = %.3e ; B_old = %.6f ; B_native = %.6f\n\n", mp, me, mn, eta0, Bold, Bnat);
    // V1
    double t7 = bisect([&](double T) { return fOld(T, 1.0 / 7.0, eta0); }), t1 = bisect([&](double T) { return fOld(T, 1.0, eta0); });
    bool ok = std::fabs(t7 / 0.062445 - 1) < 1e-3 && std::fabs(t1 / 0.065 - 1) < 0.01;
    std::printf("[V1] old list {p, n, d}: T_flip(X_n/X_p = 1/7) = %.6f MeV (prompt 0.062445) ; T_flip(X_n/X_p = 1) = %.6f MeV (prompt 0.065) -> %s\n", t7, t1, ok ? "met" : "NOT MET");
    if (!ok) { std::printf("VALIDATION NOT MET -> G0 (native result not read)\n"); return 1; }
    for (conv = 1; conv <= 2; ++conv) {
    std::printf("\nNATIVE LIST {p, e, d}, convention C%d (%s): T_flip as a function of the input g_d (g_p = g_e = 2):\n", conv, conv == 1 ? "free baryons n_B = n_p" : "full count n_B = 3 n_p");
    double tref = 0;
    for (double gd : {1.0, 2.0, 3.0, 4.0, 6.0, 8.0}) { double T = bisect([&](double x) { return fNat(x, gd, eta0, Bnat); }); if (gd == 3.0) tref = T; std::printf("  g_d = %.0f : T_flip = %.6f MeV ; difference from the old value %.6f : %+.3f%%\n", gd, T, t7, 100 * (T / t7 - 1)); }
    { double a = bisect([&](double x) { return fNat(x, 3.0, eta0, Bnat); }), b = bisect([&](double x) { return fNat(x, 8.0, eta0, Bnat); }); std::printf("  sensitivity dT/dln g_d (between g_d = 3 and 8): %.3e MeV per nat ; relative %.3e\n", (b - a) / std::log(8.0 / 3.0), (b - a) / a / std::log(8.0 / 3.0)); }
    std::printf("\nSensitivity at g_d = 3 (standard value, for comparison only):\n");
    for (double f : {0.5, 2.0}) std::printf("  eta x %.1f : T_flip = %.6f MeV (%+.3f%% from the reference %.6f)\n", f, bisect([&](double x) { return fNat(x, 3.0, eta0 * f, Bnat); }), 100 * (bisect([&](double x) { return fNat(x, 3.0, eta0 * f, Bnat); }) / tref - 1), tref);
    for (double dB : {-0.001, 0.001}) std::printf("  B_native %+.3f MeV : T_flip = %.6f MeV (%+.3f%%)\n", dB, bisect([&](double x) { return fNat(x, 3.0, eta0, Bnat + dB); }), 100 * (bisect([&](double x) { return fNat(x, 3.0, eta0, Bnat + dB); }) / tref - 1));
    }
    std::printf("\nLabel: COMPUTED; convergent with equilibrium counting by construction; no gate against the BBN band.\n");
    return 0;
}
