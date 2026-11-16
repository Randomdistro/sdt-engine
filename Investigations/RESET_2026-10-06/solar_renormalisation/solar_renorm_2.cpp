// Renormalising the Sun, round 2 (2026-10-10): chase the real figure, no target.
// Pre-registration: ../SOLAR_RENORMALISATION_ROUND2_2026-10-10_PRE_REGISTRATION.md. Forms F1 (dip-pivot prism), F2 (free pivot), F3 (floor) on sets S1, S2, S3.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <numbers>
#include <sstream>
#include <string>
#include <vector>
namespace M = sdt::laws::measured;
struct Pt { double lam, R, s; std::string inst; };
// generic weighted least squares with p <= 3 basis functions
struct Fit { int p; double b[3], cov[3][3], chi2; int n; };
template <class F> static Fit wls(const std::vector<Pt>& P, int p, F basis) {
    double A[3][4] = {}; for (auto& q : P) { double f[3]; basis(q.lam, f); double w = 1 / (q.s * q.s); for (int r = 0; r < p; ++r) { for (int k = 0; k < p; ++k) A[r][k] += w * f[r] * f[k]; A[r][3] += w * f[r] * q.R; } }
    double N[3][3] = {}, I[3][3] = {}; for (int r = 0; r < p; ++r) { for (int k = 0; k < p; ++k) N[r][k] = A[r][k]; I[r][r] = 1; }
    for (int c = 0; c < p; ++c) { int pv = c; for (int r = c + 1; r < p; ++r) if (std::fabs(N[r][c]) > std::fabs(N[pv][c])) pv = r; for (int k = 0; k < p; ++k) { std::swap(N[c][k], N[pv][k]); std::swap(I[c][k], I[pv][k]); }
        double d = N[c][c]; for (int k = 0; k < p; ++k) { N[c][k] /= d; I[c][k] /= d; } for (int r = 0; r < p; ++r) if (r != c) { double f = N[r][c]; for (int k = 0; k < p; ++k) { N[r][k] -= f * N[c][k]; I[r][k] -= f * I[c][k]; } } }
    Fit F{p, {}, {}, 0, (int)P.size()}; for (int r = 0; r < p; ++r) { F.b[r] = 0; for (int k = 0; k < p; ++k) { F.b[r] += I[r][k] * A[k][3]; F.cov[r][k] = I[r][k]; } }
    for (auto& q : P) { double f[3]; basis(q.lam, f); double m = 0; for (int r = 0; r < p; ++r) m += f[r] * F.b[r]; F.chi2 += (q.R - m) * (q.R - m) / (q.s * q.s); }
    return F;
}
static const double LD = std::sqrt(158.0 * 150000.0);   // dip pivot [nm]
static Fit fitF1(const std::vector<Pt>& P) { return wls(P, 2, [](double l, double* f) { double x = std::log(l / LD); f[0] = 1; f[1] = x * x; }); }
static Fit fitF2(const std::vector<Pt>& P) { return wls(P, 3, [](double l, double* f) { double x = std::log(l / 1000.0); f[0] = 1; f[1] = x; f[2] = x * x; }); }
static Fit fitF3(const std::vector<Pt>& P) { return wls(P, 1, [](double, double* f) { f[0] = 1; }); }
static void report(const char* form, const char* set, const Fit& F, double Rt, double sRt, const char* where) {
    int dof = F.n - F.p; double r = dof > 0 ? F.chi2 / dof : 0; double sc = (dof > 0 && r > 1) ? sRt * std::sqrt(r) : sRt;
    std::printf("  %-3s %-3s n=%2d dof=%d chi2/dof=%9.2f  R_true = %8.3f +/- %.3f (scaled %.3f) arcsec  %-26s %s\n", form, set, F.n, dof, r, Rt, sRt, sc, where, dof == 0 ? "[exactly determined]" : (r > 10 ? "[INADEQUATE]" : "[adequate]"));
}

int main(int argc, char** argv) {
    const char* path = argc > 1 ? argv[1] : "Investigations/RESET_2026-10-06/solar_renormalisation/R_lambda_points.csv";
    std::printf("Renormalising the Sun, round 2 (2026-10-10): the real figure, no target\n========================================================================\n\n");
    int bad = 0;
    { std::vector<Pt> T; for (double l : {200.0, 600.0, 2000.0, 20000.0}) { double x = std::log(l / LD); T.push_back({l, 958.4 + 0.7 * x * x, 0.1, ""}); } Fit F = fitF1(T); bool ok = std::fabs(F.b[0] - 958.4) < 1e-9 && std::fabs(F.b[1] - 0.7) < 1e-9;
      std::printf("[V1] F1 recovers (958.4, 0.7): (%.12f, %.12f) -> %s\n", F.b[0], F.b[1], ok ? "met" : "NOT MET"); bad += !ok; }
    { std::vector<Pt> T = {{500, 959.0, 0.1, ""}, {800, 960.0, 0.2, ""}}; Fit F = fitF3(T); double hand = (959.0 / 0.01 + 960.0 / 0.04) / (1 / 0.01 + 1 / 0.04); bool ok = std::fabs(F.b[0] - hand) < 1e-12;
      std::printf("[V2] F3 weighted mean %.12f against hand %.12f -> %s\n", F.b[0], hand, ok ? "met" : "NOT MET"); bad += !ok; }
    { std::vector<Pt> T; for (double l : {150.0, 400.0, 900.0, 2500.0, 8000.0, 30000.0}) { double x = std::log(l / 1000.0); T.push_back({l, 960 + 0.5 * (x - std::log(2.0)) * (x - std::log(2.0)), 0.1, ""}); } Fit F = fitF2(T); double lp = 1000 * std::exp(-F.b[1] / (2 * F.b[2]));
      bool ok = std::fabs(lp - 2000) < 1e-6; std::printf("[V3] F2 constructed pivot 2000 nm: %.9f -> %s\n\n", lp, ok ? "met" : "NOT MET"); bad += !ok; }
    if (bad) { std::printf("VALIDATIONS NOT MET\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");

    std::vector<Pt> all; { std::ifstream f(path); std::string s; std::getline(f, s); while (std::getline(f, s)) { std::stringstream ss(s); std::string t[4]; for (int i = 0; i < 4; ++i) std::getline(ss, t[i], ','); all.push_back({std::stod(t[0]), std::stod(t[1]), std::stod(t[2]), t[3]}); } }
    std::vector<Pt> S1, S2, S3 = all; for (auto& p : all) { if (p.inst.find("SDO") != std::string::npos) S1.push_back(p); if (p.lam >= 158.0 && p.lam <= 150000.0) S2.push_back(p); }
    std::printf("dip pivot lambda_d = %.1f nm ; sets: S1 %zu points (SDO), S2 %zu (between the dips), S3 %zu (all)\n\n", LD, S1.size(), S2.size(), S3.size());
    struct SetRef { const char* n; const std::vector<Pt>* v; } sets[] = {{"S1", &S1}, {"S2", &S2}, {"S3", &S3}};
    for (auto& st : sets) {
        Fit a = fitF1(*st.v); report("F1", st.n, a, a.b[0], std::sqrt(a.cov[0][0]), "at lambda_d = 4868 nm");
        if (st.v->size() >= 3) { Fit b = fitF2(*st.v); double x = -b.b[1] / (2 * b.b[2]), Rt = b.b[0] + b.b[1] * x + b.b[2] * x * x; double g[3] = {1, x, x * x}, v = 0; for (int r = 0; r < 3; ++r) for (int k = 0; k < 3; ++k) v += g[r] * g[k] * b.cov[r][k];
            char w[64]; std::snprintf(w, sizeof w, "at lambda_p = %.0f nm", 1000 * std::exp(x)); report("F2", st.n, b, Rt, std::sqrt(v), w); }
        std::vector<Pt> fl; for (auto& p : *st.v) if (p.lam >= 316.0 && p.lam <= 75000.0) fl.push_back(p);
        if (!fl.empty()) { Fit c = fitF3(fl); char w[64]; std::snprintf(w, sizeof w, "floor %.0f-%.0f nm", fl.front().lam, fl.back().lam); double lo = 1e9, hi = 0; for (auto& p : fl) { lo = std::min(lo, p.lam); hi = std::max(hi, p.lam); } std::snprintf(w, sizeof w, "floor %.0f-%.0f nm", lo, hi); report("F3", st.n, c, c.b[0], std::sqrt(c.cov[0][0]), w); }
        std::printf("\n");
    }
    const double arcsec_m = M::AU * std::numbers::pi / 648000.0;
    std::printf("context only (not targets): seismic 695.68 Mm = %.3f arcsec ; IAU nominal 6.957e8 m = %.3f arcsec ; Auwers 959.63 arcsec\n", 695.68e6 / arcsec_m, 6.957e8 / arcsec_m);
    return 0;
}
