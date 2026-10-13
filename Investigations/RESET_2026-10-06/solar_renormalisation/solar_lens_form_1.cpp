// Displaced space as the solar prism, formulation round 1 (2026-10-10).
// Pre-registration: ../SOLAR_LENS_FORMULATION_2026-10-10_PRE_REGISTRATION.md.
// R_app(lambda) = n(R_t, lambda) R_t (ray invariant); n^2 = 1 + A f(lambda; lU) + B f(lambda; lI), f = lambda^2/(lambda^2 - p^2).
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
struct Pt { double lam, R, s; std::string inst; };
static double f(double l, double p) { return l * l / (l * l - p * p); }
struct Fit { double b[3], cov[3][3], chi2; };
static Fit lin3(const std::vector<Pt>& P, double lU, double lI) {          // R = Rt + a f(lU) + b f(lI)
    double A[3][4] = {}; for (auto& q : P) { double g[3] = {1, f(q.lam, lU), f(q.lam, lI)}, w = 1 / (q.s * q.s); for (int r = 0; r < 3; ++r) { for (int k = 0; k < 3; ++k) A[r][k] += w * g[r] * g[k]; A[r][3] += w * g[r] * q.R; } }
    double N[3][3], I[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; for (int r = 0; r < 3; ++r) for (int k = 0; k < 3; ++k) N[r][k] = A[r][k];
    for (int c = 0; c < 3; ++c) { int pv = c; for (int r = c + 1; r < 3; ++r) if (std::fabs(N[r][c]) > std::fabs(N[pv][c])) pv = r; for (int k = 0; k < 3; ++k) { std::swap(N[c][k], N[pv][k]); std::swap(I[c][k], I[pv][k]); }
        double d = N[c][c]; for (int k = 0; k < 3; ++k) { N[c][k] /= d; I[c][k] /= d; } for (int r = 0; r < 3; ++r) if (r != c) { double x = N[r][c]; for (int k = 0; k < 3; ++k) { N[r][k] -= x * N[c][k]; I[r][k] -= x * I[c][k]; } } }
    Fit F; for (int r = 0; r < 3; ++r) { F.b[r] = 0; for (int k = 0; k < 3; ++k) { F.b[r] += I[r][k] * A[k][3]; F.cov[r][k] = I[r][k]; } }
    F.chi2 = 0; for (auto& q : P) { double m = F.b[0] + F.b[1] * f(q.lam, lU) + F.b[2] * f(q.lam, lI); F.chi2 += (q.R - m) * (q.R - m) / (q.s * q.s); } return F;
}
// edge of the evanescent band just short of wall p (n^2 < 0 between edge and p), by bisection; returns 0 if none
static double band_edge(double A, double lU, double B, double lI, double p) {
    auto n2 = [&](double l) { return 1 + A * f(l, lU) + B * f(l, lI); };
    double hi = p * (1 - 1e-12), lo = p * 0.5; if (n2(hi) >= 0 || n2(lo) < 0) return 0;
    for (int i = 0; i < 200; ++i) { double m = 0.5 * (lo + hi); (n2(m) < 0 ? hi : lo) = m; } return 0.5 * (lo + hi);
}
static void eng(char* out, double v) { double e = std::floor(std::log10(std::fabs(v)) / 3) * 3, m = v / std::pow(10, e); if (std::round(m * 100) / 100 >= 1000) { e += 3; m = v / std::pow(10, e); } std::snprintf(out, 32, "%.2fe%d", m, (int)e); }

int main(int argc, char** argv) {
    const char* path = argc > 1 ? argv[1] : "Investigations/RESET_2026-10-06/solar_renormalisation/R_lambda_points.csv";
    std::printf("Displaced space as the solar prism: formulation round 1 (2026-10-10)\n=====================================================================\n\n");
    int bad = 0;
    { std::vector<Pt> T; for (double l : {165.0, 200.0, 600.0, 2000.0, 1.0e6, 3.0e6}) T.push_back({l, 959.3 + 0.05 * f(l, 150.0) + 2.0 * f(l, 1.5e5), 0.1, ""}); Fit F = lin3(T, 150.0, 1.5e5);
      bool ok = std::fabs(F.b[0] - 959.3) < 1e-9 && std::fabs(F.b[1] - 0.05) < 1e-9 && std::fabs(F.b[2] - 2.0) < 1e-9; std::printf("[V1] linear fit recovers (959.3, 0.05, 2.0): (%.10f, %.10f, %.10f) -> %s\n", F.b[0], F.b[1], F.b[2], ok ? "met" : "NOT MET"); bad += !ok; }
    { std::vector<Pt> T; for (double l : {160.0, 170.0, 200.0, 600.0, 1.0e6, 3.0e6}) T.push_back({l, 959.3 + 0.05 * f(l, 143.7) + 2.0 * f(l, 1.5e5), 0.1, ""}); double best = 1e300, bl = 0; for (int i = 0; i <= 580; ++i) { double lU = 100.0 + 0.1 * i; Fit F = lin3(T, lU, 1.5e5); if (F.chi2 < best) { best = F.chi2; bl = lU; } }
      bool ok = std::fabs(bl - 143.7) < 0.051; std::printf("[V2] grid scan recovers wall 143.7 nm: %.1f nm -> %s\n", bl, ok ? "met" : "NOT MET"); bad += !ok; }
    { bool ok = f(160, 158) > 1 && f(156, 158) < 0 && f(1.0e6, 1.5e5) > 1 && f(1.4e5, 1.5e5) < 0; std::printf("[V3] f sign: long side > 1, short side < 0 -> %s\n", ok ? "met" : "NOT MET"); bad += !ok; }
    { double Bc = 1e-3, p = 1.5e5, e = band_edge(0, 158, Bc, p, p), an = p / std::sqrt(1 + Bc); bool ok = std::fabs(e / an - 1) < 1e-10; std::printf("[V4] evanescent edge %.6f nm against analytic p/sqrt(1+B) = %.6f nm -> %s\n\n", e, an, ok ? "met" : "NOT MET"); bad += !ok; }
    if (bad) { std::printf("VALIDATIONS NOT MET\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");

    std::vector<Pt> P; { std::ifstream fi(path); std::string s; std::getline(fi, s); while (std::getline(fi, s)) { std::stringstream ss(s); std::string t[4]; for (int i = 0; i < 4; ++i) std::getline(ss, t[i], ','); P.push_back({std::stod(t[0]), std::stod(t[1]), std::stod(t[2]), t[3]}); } }
    // Step 2 magnitudes
    { double z = bridge::koppa_Sun_from_precession / M::R_Sun, Vd = 3 * M::m_p * M::c * M::c / law_I::P_conv;
      std::printf("Step 2: gravitational depth z = %.3e (limb shift %.3e m) ; law-IV V_disp per baryon = %.3e m^3, x 1e23 m^-3 = %.1e\n\n", z, bridge::koppa_Sun_from_precession, Vd, Vd * 1e23); }
    const double lI = 150000.0;
    auto show = [&](const char* name, double lU, const Fit& F, int k) {
        int dof = (int)P.size() - k; double r = F.chi2 / dof, Rt = F.b[0], A = 2 * F.b[1] / Rt, B = 2 * F.b[2] / Rt;
        std::printf("%s: lambda_U = %.1f nm, lambda_I = %.0f nm ; R_t = %.4f +/- %.4f arcsec ; a = %.5f, b = %.4f arcsec ; A = %.3e, B = %.3e ; chi2/dof = %.2f (dof %d), AIC = %.1f %s\n",
                    name, lU, lI, Rt, std::sqrt(F.cov[0][0]), F.b[1], F.b[2], A, B, r, dof, F.chi2 + 2 * k, r > 10 ? "[INADEQUATE]" : "[adequate]");
        for (auto& q : P) { double m = Rt + F.b[1] * f(q.lam, lU) + F.b[2] * f(q.lam, lI); std::printf("     %10.1f nm  measured %8.3f  form %8.3f  resid %+6.2f sigma\n", q.lam, q.R, m, (q.R - m) / q.s); }
        char e1[32], e2[32], e3[32]; double eI = band_edge(A, lU, B, lI, lI), eU = band_edge(A, lU, B, lI, lU);
        if (eI > 0) { eng(e1, eI * 1e-9); eng(e2, lI * 1e-9); eng(e3, (lI - eI) * 1e-9); std::printf("   P1 far-IR evanescent band: %s to %s m (width %s m)\n", e1, e2, e3); } else std::printf("   P1 far-IR evanescent band: none (B sign or size)\n");
        if (eU > 0) { eng(e1, eU * 1e-9); eng(e2, lU * 1e-9); eng(e3, (lU - eU) * 1e-9); std::printf("   P3 UV evanescent band: %s to %s m (width %s m)\n", e1, e2, e3); } else std::printf("   P3 UV evanescent band: none\n");
        double mn = 1e9, ml = 0; for (int i = 0; i <= 4000; ++i) { double l = 1000.0 * std::pow(lI / 1000.0, i / 4000.0); double n2 = 1 + A * f(l, lU) + B * f(l, lI); if (n2 <= 0) continue; double Ra = Rt * std::sqrt(n2); if (Ra < mn) { mn = Ra; ml = l; } }
        eng(e1, ml * 1e-9); std::printf("   P2 gap 1e-6 to 150e-6 m: minimum apparent radius %.3f arcsec at %s m (%.3f arcsec below R_t)\n", mn, e1, Rt - mn);
        for (double l : {1.0e3, 3.0e3, 1.0e4, 3.0e4, 1.0e5, 1.4e5, 1.49e5}) { double n2 = 1 + A * f(l, lU) + B * f(l, lI); eng(e1, l * 1e-9); if (n2 > 0) std::printf("     %s m: R_app %.3f arcsec\n", e1, Rt * std::sqrt(n2)); else std::printf("     %s m: evanescent (n^2 = %.3e)\n", e1, n2); }
        std::printf("\n");
    };
    { Fit F = lin3(P, 158.0, lI); show("F2a (walls at the dips)", 158.0, F, 3); }
    { double best = 1e300, bl = 0; Fit bF{}; for (int i = 0; i <= 580; ++i) { double lU = 100.0 + 0.1 * i; Fit F = lin3(P, lU, lI); if (F.chi2 < best) { best = F.chi2; bl = lU; bF = F; } }
      double lo = bl, hi = bl; for (int i = 0; i <= 580; ++i) { double lU = 100.0 + 0.1 * i; if (lin3(P, lU, lI).chi2 <= best + 1) { lo = std::min(lo, lU); hi = std::max(hi, lU); } }
      std::printf("F2b scan: best UV wall %.1f nm (delta-chi2 = 1 range %.1f-%.1f nm)\n", bl, lo, hi); show("F2b (UV wall free)", bl, bF, 4); }
    std::printf("F3 (round 2, floor only): R_t = 959.589 +/- 0.019, chi2 = %.2f on 5 points (dof 4), AIC = %.1f -- different point set; not directly comparable\n", 3.45 * 4, 3.45 * 4 + 2);
    return 0;
}
