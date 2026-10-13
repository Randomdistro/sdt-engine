// PPT05 R2 (2026-10-06) — dependence of the string tension on the choice of trefoil length R, and a candidate census.
// Pre-registered in R2_REOPEN_2026-10-05.md §4 before this file existed. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
#include <vector>
#include <numbers>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = std::numbers::pi;

int main() {
    std::printf("PPT05 R2 — sigma(R) and census (pre-registered 2026-10-06)\n==========================================================\n\n");
    int fails = 0;
    const double hb = M::hbar, c = M::c, mp = M::m_p, eV = 1.602176634e-19;
    const double lam = hb / (mp * c), hbarc_GeVfm = hb * c / eV / 1e9 * 1e15, mpc2_GeV = mp * c * c / eV / 1e9;
    bool v1 = std::fabs(lam * 1e15 - 0.210309) < 1e-5 * 0.21 && std::fabs(hbarc_GeVfm - 0.197327) < 1e-5 && std::fabs(mpc2_GeV - 0.938272) < 1e-6;
    std::printf("[V1] lam_p = %.6f fm ; hbar c = %.6f GeV fm ; m_p c^2 = %.6f GeV -> %s\n", lam * 1e15, hbarc_GeVfm, mpc2_GeV, v1 ? "PASS" : "FAIL");
    if (!v1) ++fails;
    double worst = 0; const double R0 = 1.0;
    for (double a : {0.1, 0.5, 1.0, 2.0}) {
        const int n = 4000; double s = 0, dr = a / n;
        for (int i = 0; i < n; ++i) { double r = (i + 0.5) * dr; s += 2 * PI * r * dr / (2 * PI * PI * R0 * a * a); }
        worst = std::max(worst, std::fabs(s - 1.0 / (2 * PI * R0)) / (1.0 / (2 * PI * R0)));
    }
    bool v2 = worst < 1e-9;
    std::printf("[V2] cross-section integral of rho c^2 = m c^2/(2 pi R) for a = 0.1R..2R: worst relative error %.2e -> %s\n\n", worst, v2 ? "PASS" : "FAIL");
    if (!v2) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    // PPT01 general closure: R = nT hbar/(m vT), a = nP hbar/(m vP) for (p,q) = (2,3)
    auto geom = [&](int nT, int nP, double& R, double& a, double& vT, double& vP) {
        const int p = 2, q = 3; const double x = std::sqrt(double(q) * nT / (double(p) * nP)), r = (double(q) / p) / x;
        vT = 1.0 / std::sqrt(1 + r * r); vP = r * vT; R = nT * lam / vT; a = nP * lam / vP; (void)x;
    };
    double RA, aA, vTA, vPA, RB, aB, vTB, vPB, RC, aC, vTC, vPC;
    geom(1, 1, RA, aA, vTA, vPA); geom(2, 3, RB, aB, vTB, vPB); geom(3, 2, RC, aC, vTC, vPC);
    struct L { const char* nm; double R; } Ls[] = {
        {"PPT05 (lam_p/sqrt3)", lam / std::sqrt(3.0)},
        {"PPT01 rule A (1,1)", RA}, {"PPT01 rule B (p,q)=(2,3)", RB}, {"PPT01 rule C (q,p)=(3,2)", RC},
        {"FLM05/FLM07 R = R_p", M::R_p}, {"sqrt3 lam_p ((1,2) partition, no /q)", std::sqrt(3.0) * lam}};
    std::printf("[T1] sigma = m_p c^2/(2 pi R)\n     %-40s R [fm]    R/lam_p   sigma [GeV/fm]  vs 0.9 [%%]\n", "length used");
    double smin = 1e9, smax = 0;
    for (auto& l : Ls) { double s = mpc2_GeV / (2 * PI * l.R * 1e15); smin = std::min(smin, s); smax = std::max(smax, s);
        std::printf("     %-40s %.5f   %.4f    %.4f          %+6.1f\n", l.nm, l.R * 1e15, l.R / lam, s, (s / 0.9 - 1) * 100); }
    std::printf("     sigma spans %.4f .. %.4f GeV/fm (factor %.1f)\n     PPT01 rules: R_A = %.4e, R_B = %.4e, R_C = %.4e m ; a_A = %.4e, a_B = %.4e, a_C = %.4e m\n\n", smin, smax, smax / smin, RA, RB, RC, aA, aB, aC);

    double vT5 = 1.0 / std::sqrt(3.0), vP5 = std::sqrt(2.0 / 3.0), a5 = lam * std::sqrt(1.5) / 2, R5 = lam * std::sqrt(3.0) / 3;
    std::printf("[T2] PPT05 vs PPT01 (2,3) rule A\n     PPT05 : v_T/c %.4f  v_P/c %.4f  R/lam %.4f  a/lam %.4f  R/a %.4f\n     rule A: v_T/c %.4f  v_P/c %.4f  R/lam %.4f  a/lam %.4f  R/a %.4f\n",
                vT5, vP5, R5 / lam, a5 / lam, R5 / a5, vTA, vPA, RA / lam, aA / lam, RA / aA);
    std::printf("     rule A gives v_T^2/c^2 = p/(p+q) = 1/3 for (p,q) = (1,2): v_T = %.4f c, v_P = %.4f c (PPT05's partition)\n     -> PPT05's partition equals the (1,2) curve's under rule A, applied to a (2,3) geometry\n\n", std::sqrt(1.0 / 3), std::sqrt(2.0 / 3));

    const double lo = 0.88, hi = 1.00;
    double Rn_lo = mpc2_GeV / (2 * PI * hi), Rn_hi = mpc2_GeV / (2 * PI * lo);
    double ql = Rn_lo / (lam * 1e15), qh = Rn_hi / (lam * 1e15);
    std::printf("[T3] census: band sigma in [%.2f, %.2f] GeV/fm requires R in [%.5f, %.5f] fm = R/lam_p in [%.4f, %.4f]\n", lo, hi, Rn_lo, Rn_hi, ql, qh);
    std::set<long> uniq; std::vector<std::pair<double, std::pair<int, int>>> cand;
    for (int a = 1; a <= 6; ++a) for (int b = 1; b <= 6; ++b) { double v = std::sqrt(double(a) / b); long key = std::lround(v * 1e9); if (uniq.insert(key).second) cand.push_back({v, {a, b}}); }
    int inband = 0;
    std::printf("     distinct candidates sqrt(a/b), a,b in 1..6: %zu ; inside the band:", cand.size());
    for (auto& cd : cand) if (cd.first >= ql && cd.first <= qh) { ++inband; std::printf(" sqrt(%d/%d)=%.4f", cd.second.first, cd.second.second, cd.first); }
    std::printf("\n     count inside band: %d of %zu (%.1f%%) ; census criterion (count >= 3: not discriminating): %s\n", inband, cand.size(), 100.0 * inband / cand.size(), inband >= 3 ? "MET" : "not met");
    std::printf("     PPT05's 1/sqrt3 = %.4f is %s the band\n", 1 / std::sqrt(3.0), (1 / std::sqrt(3.0) >= ql && 1 / std::sqrt(3.0) <= qh) ? "inside" : "outside");
    return 0;
}
