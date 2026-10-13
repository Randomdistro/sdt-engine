// Renormalising the Sun, instrument 1 (2026-10-09). Pre-registration: ../SOLAR_RENORMALISATION_2026-10-09_PRE_REGISTRATION.md.
// C1 smallest disc, C2 pivot of a bending quadratic in ln(lambda), C3 crossing with the seismic radius. Bet: 925-975 nm.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <numbers>
#include <sstream>
#include <string>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
struct Pt { double lam, R, s; std::string inst, ver; };
struct Q { double a, b, c, cov[3][3], chi2; };
static Q fitq(const std::vector<Pt>& P) {           // R = a + b x + c x^2, x = ln(lambda / 1 um), weights 1/s^2
    double A[3][4] = {}; for (auto& p : P) { double x = std::log(p.lam / 1000.0), f[3] = {1, x, x * x}, w = 1 / (p.s * p.s); for (int r = 0; r < 3; ++r) { for (int k = 0; k < 3; ++k) A[r][k] += w * f[r] * f[k]; A[r][3] += w * f[r] * p.R; } }
    double N[3][3], I[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; for (int r = 0; r < 3; ++r) for (int k = 0; k < 3; ++k) N[r][k] = A[r][k];
    for (int c = 0; c < 3; ++c) { int pv = c; for (int r = c + 1; r < 3; ++r) if (std::fabs(N[r][c]) > std::fabs(N[pv][c])) pv = r; for (int k = 0; k < 3; ++k) { std::swap(N[c][k], N[pv][k]); std::swap(I[c][k], I[pv][k]); }
        double d = N[c][c]; for (int k = 0; k < 3; ++k) { N[c][k] /= d; I[c][k] /= d; } for (int r = 0; r < 3; ++r) if (r != c) { double f = N[r][c]; for (int k = 0; k < 3; ++k) { N[r][k] -= f * N[c][k]; I[r][k] -= f * I[c][k]; } } }
    Q q; double bb[3] = {}; for (int r = 0; r < 3; ++r) for (int k = 0; k < 3; ++k) bb[r] += I[r][k] * A[k][3]; q.a = bb[0]; q.b = bb[1]; q.c = bb[2];
    for (int r = 0; r < 3; ++r) for (int k = 0; k < 3; ++k) q.cov[r][k] = I[r][k]; q.chi2 = 0; for (auto& p : P) { double x = std::log(p.lam / 1000.0), m = q.a + q.b * x + q.c * x * x; q.chi2 += (p.R - m) * (p.R - m) / (p.s * p.s); }
    return q;
}
static double pivot_x(const Q& q) { return -q.b / (2 * q.c); }
static double pivot_sx(const Q& q) { double x = pivot_x(q), gb = -1 / (2 * q.c), gc = x / q.c * 0.5 * 2 / 2; gc = q.b / (2 * q.c * q.c); return std::sqrt(gb * gb * q.cov[1][1] + 2 * gb * gc * q.cov[1][2] + gc * gc * q.cov[2][2]); }
static int crossings(double a, double b, double c, double R, double x[2]) { double A = c, B = b, C = a - R, D = B * B - 4 * A * C; if (D < 0) return 0; x[0] = (-B - std::sqrt(D)) / (2 * A); x[1] = (-B + std::sqrt(D)) / (2 * A); return 2; }

int main(int argc, char** argv) {
    const char* path = argc > 1 ? argv[1] : "Investigations/RESET_2026-10-06/solar_renormalisation/R_lambda_points.csv";
    std::printf("Renormalising the Sun, instrument 1 (2026-10-09)\n================================================\n\n");
    const double arcsec_m = M::AU * std::numbers::pi / 648000.0;   // metres per arcsec at 1 AU
    int bad = 0;
    { double km = 959.63 * arcsec_m / 1e3; bool ok = std::fabs(km - 696000) < 100; std::printf("[V1] 959.63 arcsec at 1 AU = %.1f km (expect ~696000) ; 1 arcsec = %.3f km -> %s\n", km, arcsec_m / 1e3, ok ? "met" : "NOT MET"); bad += !ok; }
    { std::vector<Pt> T; for (double l : {150.0, 400.0, 900.0, 2500.0, 8000.0, 30000.0}) { double x = std::log(l / 1000.0); T.push_back({l, 960 + 0.5 * (x - std::log(2.0)) * (x - std::log(2.0)), 0.1, "", ""}); }
      Q q = fitq(T); double lp = 1000 * std::exp(pivot_x(q)); bool ok = std::fabs(lp - 2000) < 1e-6; std::printf("[V2] constructed pivot 2000 nm recovered: %.9f nm -> %s\n", lp, ok ? "met" : "NOT MET"); bad += !ok; }
    { double x[2]; int n = crossings(960 + 0.5 * std::log(2.0) * std::log(2.0), -std::log(2.0), 0.5, 960.5, x); double l0 = 1000 * std::exp(x[0]), l1 = 1000 * std::exp(x[1]);
      double e0 = 960 + 0.5 * std::pow(x[0] - std::log(2.0), 2) - 960.5; bool ok = n == 2 && std::fabs(e0) < 1e-9; std::printf("[V3] crossing finder on a constructed curve: %.3f nm and %.3f nm, residual %.1e -> %s\n\n", l0, l1, e0, ok ? "met" : "NOT MET"); bad += !ok; }
    if (bad) { std::printf("VALIDATIONS NOT MET\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");

    std::vector<Pt> P; { std::ifstream f(path); std::string s; std::getline(f, s); while (std::getline(f, s)) { std::stringstream ss(s); std::string t[7]; for (int i = 0; i < 7; ++i) std::getline(ss, t[i], ','); P.push_back({std::stod(t[0]), std::stod(t[1]), std::stod(t[2]), t[3], t[6]}); } }
    std::printf("R(lambda) points: %zu\n", P.size()); for (auto& p : P) std::printf("  %10.1f nm  %8.3f +/- %.3f arcsec  %-30s [%s]\n", p.lam, p.R, p.s, p.inst.c_str(), p.ver.substr(0, 26).c_str());
    const double Rseis = 695.68e6 / arcsec_m, sRseis = 0.03e6 / arcsec_m;   // [MEASURED-INPUT, Schou et al. 1997 f-mode, 695.68 +/- 0.03 Mm]
    std::printf("seismic radius 695.68 +/- 0.03 Mm = %.3f +/- %.3f arcsec\n\n", Rseis, sRseis);

    // ---- C1 smallest disc: homogeneous series bracketing 925-975 nm (SODISM II: 782.2 and 1025.0)
    { const Pt *lo = nullptr, *hi = nullptr; for (auto& p : P) if (p.inst.find("SODISM II") != std::string::npos) { if (p.lam < 925 && (!lo || p.lam > lo->lam)) lo = &p; if (p.lam > 975 && (!hi || p.lam < hi->lam)) hi = &p; }
      int inband = 0; for (auto& p : P) if (p.lam >= 925 && p.lam <= 975) ++inband;
      std::printf("C1 smallest disc: in-band points %d ; bracketing series SODISM II %.1f nm %.3f +/- %.3f and %.1f nm %.3f +/- %.3f ; difference %+.3f +/- %.3f arcsec\n", inband, lo->lam, lo->R, lo->s, hi->lam, hi->R, hi->s, hi->R - lo->R, std::hypot(lo->s, hi->s));
      double mn = 1e9, mx = -1e9; for (auto& p : P) if (p.inst.find("SODISM II") != std::string::npos) { mn = std::min(mn, p.R); mx = std::max(mx, p.R); }
      std::printf("   SODISM II spread 535.7-1025 nm: %.3f arcsec (series sigmas 0.10-0.20) -> %s\n\n", mx - mn, inband == 0 ? "OPEN (no point in band; series flat within 2 sigma)" : "evaluate"); }

    // ---- C2 pivot
    { Q q = fitq(P); double xp = pivot_x(q), sx = pivot_sx(q), lp = 1000 * std::exp(xp);
      std::printf("C2 pivot, my fit R = a + b x + c x^2, x = ln(lambda/1 um): a = %.4f, b = %.4f, c = %.5f, chi2/dof = %.2f (%zu points)\n", q.a, q.b, q.c, q.chi2 / (P.size() - 3), P.size());
      std::printf("   pivot lambda_p = %.1f nm, sigma(ln lambda_p) = %.3f -> 2-sigma range %.1f-%.1f nm ; R at pivot %.3f arcsec ; band 925-975 nm %s\n", lp, sx, lp * std::exp(-2 * sx), lp * std::exp(2 * sx), q.a + q.b * xp + q.c * xp * xp,
                  (sx > 1) ? "-> OPEN (unconstrained)" : ((std::log(950.0 / lp) / sx > -2 && std::log(950.0 / lp) / sx < 2) ? "within 2 sigma -> CONFIRMED" : "outside 2 sigma -> REJECTED"));
      std::printf("   bet band offset: ln(950/lambda_p)/sigma = %+.2f\n", std::log(950.0 / lp) / sx);
      // published full-range fit (Rozelot & Kosovichev 2015, Fig. 4 of arXiv:1609.02710): R = 3.120 X^2 - 23.828 X + 1000.100, X = log10(lambda/nm)
      double X = 23.828 / (2 * 3.120), Rm = 1000.100 - 23.828 * 23.828 / (4 * 3.120);
      std::printf("   published fit (log10, X-EUV to radio, ~40 points): minimum X = %.4f -> %.1f nm, R_min = %.2f arcsec ; quoted 6.6 +/- 1.9 um ; bet offset (950 nm) = %.1f sigma (linear)\n", X, std::pow(10, X), Rm, (950 - 6600) / 1900.0);
      std::printf("   symmetric-dip pivot (registered before data): 4870 nm (4920 with 153.3 um) ; offset from published 6.6 +/- 1.9 um = %.2f sigma\n\n", (4870 - 6600) / 1900.0);
      // ---- C3 crossing with the seismic radius
      double xc[2]; int n = crossings(q.a, q.b, q.c, Rseis, xc);
      if (n) { std::printf("C3 my fit crosses R_seis at %.1f nm and %.1f nm\n", 1000 * std::exp(xc[0]), 1000 * std::exp(xc[1]));   // run 2: crossing sigma added (registered quantity omitted in run 1)
        for (int i = 0; i < 2; ++i) { double x = xc[i], g[3] = {1, x, x * x}, den = q.b + 2 * q.c * x, v = 0; for (int r = 0; r < 3; ++r) for (int k = 0; k < 3; ++k) v += g[r] * g[k] * q.cov[r][k]; double sx = std::sqrt(v + sRseis * sRseis) / std::fabs(den), off = std::log(950.0 / (1000 * std::exp(x))) / sx;
          std::printf("   crossing %d: %.1f nm, sigma(ln) = %.3f (statistical, chi2 not rescaled) ; bet offset ln(950/lambda_x)/sigma = %+.2f -> %s\n", i + 1, 1000 * std::exp(x), sx, off, std::fabs(off) <= 2 ? "within 2 sigma" : "outside 2 sigma"); } }
      else std::printf("C3 my fit never reaches R_seis (minimum above it)\n");
      double Xc[2]; int m = crossings(1000.100, -23.828, 3.120, Rseis, Xc); if (m) std::printf("   published fit crosses R_seis at %.1f nm and %.1f nm\n", std::pow(10, Xc[0]), std::pow(10, Xc[1]));
      int above = 0; double minex = 1e9; for (auto& p : P) { double ex = (p.R - Rseis) / std::hypot(p.s, sRseis); if (ex > 2) ++above; minex = std::min(minex, ex); }
      std::printf("   measured points above R_seis by > 2 sigma: %d of %zu (smallest excess %.1f sigma) -> %s\n", above, P.size(), minex, above == (int)P.size() ? "every point above by > 2 sigma" : "not every point is above by > 2 sigma (the remainder are the ALMA points, sigma 2.5-4.5 arcsec); no measured point lies below R_seis"); }
    return 0;
}

