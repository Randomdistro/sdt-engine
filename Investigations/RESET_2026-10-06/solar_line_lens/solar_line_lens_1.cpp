// Solar line lens, instrument 1 (2026-10-09). Pre-registration: ../SOLAR_LINE_LENS_2026-10-09_PRE_REGISTRATION.md.
// Route E (edge reading) and route T (twin-dip reading) on HARPS-LFC table A1 raw line-core shifts (no convective model).
// Om = R/k^2; Om_Sun from the engine's Mercury route. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

struct Line { double lam, ew, eew, v, ev, chi, loggf; std::string el; int ion; };

static std::vector<double> ranks(const std::vector<double>& x) {
    std::vector<size_t> idx(x.size()); std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(), [&](size_t a, size_t b) { return x[a] < x[b]; });
    std::vector<double> r(x.size());
    for (size_t i = 0; i < idx.size();) { size_t j = i; while (j + 1 < idx.size() && x[idx[j + 1]] == x[idx[i]]) ++j; double rk = 0.5 * (i + j) + 1; for (size_t k = i; k <= j; ++k) r[idx[k]] = rk; i = j + 1; }
    return r;
}
static double pearson(const std::vector<double>& a, const std::vector<double>& b) {
    double ma = 0, mb = 0; size_t n = a.size(); for (size_t i = 0; i < n; ++i) { ma += a[i]; mb += b[i]; } ma /= n; mb /= n;
    double sab = 0, saa = 0, sbb = 0; for (size_t i = 0; i < n; ++i) { sab += (a[i] - ma) * (b[i] - mb); saa += (a[i] - ma) * (a[i] - ma); sbb += (b[i] - mb) * (b[i] - mb); }
    return sab / std::sqrt(saa * sbb);
}
static double spearman(const std::vector<double>& a, const std::vector<double>& b) { return pearson(ranks(a), ranks(b)); }
static double p_two_sided(double rho, size_t n) { double t = rho * std::sqrt((n - 2) / (1 - rho * rho)); return std::erfc(std::fabs(t) / std::sqrt(2.0)); } // large-n normal approximation
// weighted least squares y = X beta; returns beta and covariance (3x3 max)
struct Fit { std::vector<double> b; std::vector<std::vector<double>> cov; double chi2; };
static Fit wls(const std::vector<std::vector<double>>& X, const std::vector<double>& y, const std::vector<double>& w) {
    size_t p = X[0].size(), n = y.size(); std::vector<std::vector<double>> A(p, std::vector<double>(p + 1, 0.0));
    for (size_t i = 0; i < n; ++i) for (size_t r = 0; r < p; ++r) { for (size_t c = 0; c < p; ++c) A[r][c] += w[i] * X[i][r] * X[i][c]; A[r][p] += w[i] * X[i][r] * y[i]; }
    std::vector<std::vector<double>> inv(p, std::vector<double>(p, 0.0)); for (size_t r = 0; r < p; ++r) inv[r][r] = 1;
    auto N = A; for (size_t r = 0; r < p; ++r) N[r].resize(p);
    for (size_t c = 0; c < p; ++c) { size_t piv = c; for (size_t r = c + 1; r < p; ++r) if (std::fabs(N[r][c]) > std::fabs(N[piv][c])) piv = r; std::swap(N[c], N[piv]); std::swap(inv[c], inv[piv]);
        double d = N[c][c]; for (size_t k = 0; k < p; ++k) { N[c][k] /= d; inv[c][k] /= d; }
        for (size_t r = 0; r < p; ++r) if (r != c) { double f = N[r][c]; for (size_t k = 0; k < p; ++k) { N[r][k] -= f * N[c][k]; inv[r][k] -= f * inv[c][k]; } } }
    Fit F; F.b.assign(p, 0); for (size_t r = 0; r < p; ++r) for (size_t c = 0; c < p; ++c) F.b[r] += inv[r][c] * A[c][p];
    F.cov = inv; F.chi2 = 0; for (size_t i = 0; i < n; ++i) { double m = 0; for (size_t r = 0; r < p; ++r) m += X[i][r] * F.b[r]; F.chi2 += w[i] * (y[i] - m) * (y[i] - m); }
    return F;
}

int main(int argc, char** argv) {
    const char* path = argc > 1 ? argv[1] : "Datasets/solar_propagation_2026-08/raw/harps_lfc_tablea1.dat";
    std::printf("Solar line lens, instrument 1 (2026-10-09)\n==========================================\n\n");
    const double c = M::c;
    std::vector<Line> L; { std::ifstream f(path); std::string s;
        while (std::getline(f, s)) { if (s.size() < 75) continue; Line l; l.lam = std::stod(s.substr(0, 9)) * 0.1; l.el = s.substr(38, 2); l.ion = std::stoi(s.substr(41, 1)); l.chi = std::stod(s.substr(43, 4)); l.loggf = std::stod(s.substr(48, 5));
            l.ew = std::stod(s.substr(54, 5)) * 0.1; l.eew = std::stod(s.substr(60, 4)) * 0.1; l.v = std::stod(s.substr(65, 5)); l.ev = std::stod(s.substr(71, 4)); L.push_back(l); } }
    int bad = 0;
    { bool ok = L.size() == 188 && std::fabs(L[0].lam - 477.94394) < 1e-9 && std::fabs(L[0].ew - 4.09) < 1e-9 && std::fabs(L[0].v - 189.1) < 1e-9 && std::fabs(L[0].ev - 25.0) < 1e-9 && L[0].el == "Fe" && L[0].ion == 1;
      std::printf("[V1] rows %zu ; row 1: lambda %.5f nm, %s %d, EW %.2f pm, v %.1f +/- %.1f m/s -> %s\n", L.size(), L[0].lam, L[0].el.c_str(), L[0].ion, L[0].ew, L[0].v, L[0].ev, ok ? "met" : "NOT MET"); bad += !ok; }
    { std::vector<double> a = {1, 2, 3, 4, 5, 6}, up = {2, 4, 6, 8, 10, 12}, dn = {6, 5, 4, 3, 2, 1}, z = {1, 2, 3, 3, 2, 1};
      double r1 = spearman(a, up), r2 = spearman(a, dn), r0 = spearman(a, z); bool ok = std::fabs(r1 - 1) < 1e-12 && std::fabs(r2 + 1) < 1e-12 && std::fabs(r0) < 1e-12;
      std::printf("[V2] Spearman known cases: %+.3f %+.3f %+.3f (expect +1 -1 0) -> %s\n", r1, r2, r0, ok ? "met" : "NOT MET"); bad += !ok; }
    { std::vector<std::vector<double>> X; std::vector<double> y, w; for (int i = 0; i < 10; ++i) { X.push_back({1.0, (double)i, (double)(i * i % 7)}); y.push_back(3 - 0.5 * i + 0.25 * (i * i % 7)); w.push_back(1 + i); }
      Fit F = wls(X, y, w); bool ok = std::fabs(F.b[0] - 3) < 1e-10 && std::fabs(F.b[1] + 0.5) < 1e-10 && std::fabs(F.b[2] - 0.25) < 1e-10;
      std::printf("[V3] weighted fit recovers (3, -0.5, 0.25): (%.12f, %.12f, %.12f) -> %s\n", F.b[0], F.b[1], F.b[2], ok ? "met" : "NOT MET"); bad += !ok; }
    { double lab = 500.0, v = 636.30, obs = lab * (1 + v / c), back = c * (obs - lab) / lab; bool ok = std::fabs(back - v) < 1e-6;   // attempt 2: tolerance set to the cancellation floor (c eps ~ 7e-8 m/s); attempt 1 used 1e-9 (G0)
      std::printf("[V4] v = c(lambda_obs - lambda_lab)/lambda_lab round trip: %.12f m/s -> %s\n\n", back, ok ? "met" : "NOT MET"); bad += !ok; }
    if (bad) { std::printf("VALIDATIONS NOT MET\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");

    // predictions fixed before the data
    const double surf = c * bridge::koppa_Sun_from_precession / M::R_Sun, d = c * bridge::koppa_Sun_from_precession / M::AU + c * bridge::koppa_Earth / bridge::R_Earth;
    struct P { const char* name; double v; } pred[] = {{"subtract", surf + d}, {"none", surf}, {"add", surf - d}, {"double", surf - 2 * d}};
    std::printf("predictions (c z_obs at Earth): surface %.2f, observer terms %.2f ; subtract %.2f, none %.2f, add %.2f, double %.2f m/s\n\n", surf, d, pred[0].v, pred[1].v, pred[2].v, pred[3].v);

    const size_t n = L.size(); std::vector<double> ew(n), v(n), lg(n), lam(n), w(n);
    for (size_t i = 0; i < n; ++i) { ew[i] = L[i].ew; v[i] = L[i].v; lg[i] = std::log10(L[i].ew); lam[i] = L[i].lam; w[i] = 1 / (L[i].ev * L[i].ev); }
    std::printf("sample: %zu lines, lambda %.2f-%.2f nm, EW %.2f-%.2f pm, v %.1f-%.1f m/s\n\n", n, *std::min_element(lam.begin(), lam.end()), *std::max_element(lam.begin(), lam.end()), *std::min_element(ew.begin(), ew.end()), *std::max_element(ew.begin(), ew.end()), *std::min_element(v.begin(), v.end()), *std::max_element(v.begin(), v.end()));

    // ---- Route E
    double rho = spearman(ew, v), p = p_two_sided(rho, n);
    std::printf("ROUTE E (edge)\n  E1 Spearman rho(EW, v) = %+.4f, p = %.2e -> E-R1 %s\n", rho, p, (rho > 0 && p < 0.01) ? "met (shift rises with line strength)" : "NOT MET -> G1");
    std::vector<size_t> idx(n); std::iota(idx.begin(), idx.end(), 0); std::sort(idx.begin(), idx.end(), [&](size_t a, size_t b) { return ew[a] > ew[b]; });
    const size_t k = 19; double m = 0; for (size_t i = 0; i < k; ++i) m += v[idx[i]]; m /= k; double sd = 0; for (size_t i = 0; i < k; ++i) sd += (v[idx[i]] - m) * (v[idx[i]] - m); sd = std::sqrt(sd / (k - 1)); double se2 = sd / std::sqrt((double)k);
    std::printf("  E2 strongest 10%% (n = %zu, EW >= %.2f pm): mean v = %.2f +/- %.2f m/s (sd %.1f)\n", k, ew[idx[k - 1]], m, se2, sd);
    std::vector<std::vector<double>> X1; for (size_t i = 0; i < n; ++i) X1.push_back({1.0, lg[i]}); Fit F1 = wls(X1, v, w);
    double lmax = std::log10(ew[idx[0]]), e3 = F1.b[0] + F1.b[1] * lmax, se3 = std::sqrt(F1.cov[0][0] + 2 * lmax * F1.cov[0][1] + lmax * lmax * F1.cov[1][1]);
    std::printf("  E3 fit v = a + b log10(EW): a = %.1f, b = %.1f m/s per dex (chi2/dof %.2f) ; at EW_max = %.2f pm: %.2f +/- %.2f m/s\n", F1.b[0], F1.b[1], F1.chi2 / (n - 2), ew[idx[0]], e3, se3);
    double diff = m - e3, sdiff = std::sqrt(se2 * se2 + se3 * se3); std::printf("  E-R2 E2 - E3 = %+.2f +/- %.2f m/s -> %s\n", diff, sdiff, std::fabs(diff) <= 2 * sdiff ? "met (edge determined)" : "NOT MET (edge not determined, G2)");
    std::printf("  E-R3 edge value %.2f +/- %.2f against the handlings:\n", m, se2); int within = 0; const char* best = nullptr; double bd = 1e9;
    for (auto& q : pred) { double dv = m - q.v, s = dv / se2; if (std::fabs(s) <= 2) ++within; if (std::fabs(dv) < bd) { bd = std::fabs(dv); best = q.name; } std::printf("     %-8s %.2f m/s : edge - prediction = %+7.2f m/s (%+.2f sigma)\n", q.name, q.v, dv, s); }
    std::printf("     closest: %s ; handlings within 2 sigma: %d -> %s ; sigma needed to separate adjacent handlings at 2 sigma: %.2f m/s\n\n", best, within, within == 0 ? "G1 (edge lies off all four)" : (within == 1 ? "one handling chosen" : "data do not choose (G2)"), d / 4);

    // ---- Route T
    double tz = 0, tw = 0; for (size_t i = 0; i < n; ++i) { tz += w[i] * v[i] / c; tw += w[i]; } double z0 = tz / tw, lbar = 0; for (double x : lam) lbar += x; lbar /= n;
    std::printf("ROUTE T (twin dip)\n  T1 power: handlings differ by %.2f m/s = %.2e in z ; at 158 nm that is %.2e nm, at 150 um %.2e nm ; no brightness temperature changes -> the dips cannot choose a handling\n", d, d / c, 158.0 * d / c, 150e3 * d / c);
    std::vector<double> s(n), ws(n); for (size_t i = 0; i < n; ++i) { s[i] = v[i] / c - z0; ws[i] = w[i] * c * c; }
    std::vector<std::vector<double>> X2, X3; for (size_t i = 0; i < n; ++i) { X2.push_back({1.0, lam[i] - lbar}); X3.push_back({1.0, lam[i] - lbar, lg[i]}); }
    Fit F2 = wls(X2, s, ws), F3 = wls(X3, s, ws);
    double s1 = F2.b[1], ss1 = std::sqrt(F2.cov[1][1]), p1 = std::erfc(std::fabs(s1 / ss1) / std::sqrt(2.0)), q1 = F3.b[1], sq1 = std::sqrt(F3.cov[1][1]), pq = std::erfc(std::fabs(q1 / sq1) / std::sqrt(2.0));
    std::printf("  T2 one stretch z0 = %.4e (c z0 = %.2f m/s) ; residual stretch slope s1 = %+.3e +/- %.3e per nm (p = %.2e) -> %s\n", z0, c * z0, s1, ss1, p1, p1 < 0.01 ? "wavelength-dependent stretch present" : "no wavelength dependence in the lines (G2)");
    std::printf("     with line strength held: slope %+.3e +/- %.3e per nm (p = %.2e) ; strength term %+.3e per dex\n", q1, sq1, pq, F3.b[2]);
    std::printf("     carried to the dips (linear, for scale only): s at 158 nm %+.2e, at 150 um %+.2e\n", s1 * (158 - lbar), s1 * (150e3 - lbar));
    { const double Tu = 4430, sTu = 50, Ti = 4370, sTi = 260; double dT = Tu - Ti, sdT = std::sqrt(sTu * sTu + sTi * sTi);   // [MEASURED-INPUT, as quoted in E109 section 2; to be verified]
      std::printf("  T3 twin identity: T_UV - T_FIR = %+.0f +/- %.0f K (%+.2f sigma) -> %s ; resolution set by the far-IR record (+/-%.0f K)\n", dT, sdT, dT / sdT, std::fabs(dT) <= 2 * sdT ? "consistent" : "rejected", sTi); }
    return 0;
}
