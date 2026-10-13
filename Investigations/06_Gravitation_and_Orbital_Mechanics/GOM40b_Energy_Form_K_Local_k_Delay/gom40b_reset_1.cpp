// GOM40b blank-slate run 1 (2026-10-11). Registration: GOM40b_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
// Pairwise-energy K on the SCE1 geocentre arc (the prompt's route) and on the 2025/2024 EMB year arcs (the C3c route); conjunction delay ledger with the year-route K.
// Author: J. C. Harvey, Melbourne.
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

static const std::string RAW = "Datasets/solar_propagation_2026-08/raw/";
static const double C = 299792458.0, AU = 149597870700.0, RSUN = 6.957e8, FKA = 32.028e9, JD0 = 2452431.708333333, KINV = 1476.351201;
typedef std::array<double, 3> V3;
struct Orb { std::vector<double> r, v2; };
struct Tab { std::vector<double> t; std::vector<V3> x; };
static std::vector<std::string> splitc(const std::string& ln) { std::vector<std::string> f; size_t p = 0; while (true) { size_t q = ln.find(',', p); if (q == std::string::npos) break; f.push_back(ln.substr(p, q - p)); p = q + 1; } return f; }
static Orb readOrb(const std::string& path) { Orb o; std::ifstream f(path); std::string ln; bool in = false; while (std::getline(f, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue; auto t = splitc(ln); if (t.size() < 8) continue; double X = std::stod(t[2]) * 1e3, Y = std::stod(t[3]) * 1e3, Z = std::stod(t[4]) * 1e3, VX = std::stod(t[5]) * 1e3, VY = std::stod(t[6]) * 1e3, VZ = std::stod(t[7]) * 1e3; o.r.push_back(std::sqrt(X * X + Y * Y + Z * Z)); o.v2.push_back(VX * VX + VY * VY + VZ * VZ); } return o; }
static Tab readTab(const std::string& path) { Tab T; std::ifstream h(path); std::string ln; bool in = false; while (std::getline(h, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue; auto f = splitc(ln); if (f.size() < 5) continue; T.t.push_back((std::stod(f[0]) - JD0) * 86400.0); T.x.push_back({std::stod(f[2]) * 1e3, std::stod(f[3]) * 1e3, std::stod(f[4]) * 1e3}); } return T; }
static V3 interp(const Tab& T, double t) { size_t i = std::upper_bound(T.t.begin(), T.t.end(), t) - T.t.begin(); long a = (long)i - 2; if (a < 0) a = 0; if (a + 3 >= (long)T.t.size()) a = (long)T.t.size() - 4; V3 s = {0, 0, 0}; for (int j = 0; j < 4; ++j) { double L = 1; for (int k = 0; k < 4; ++k) if (k != j) L *= (t - T.t[a + k]) / (T.t[a + j] - T.t[a + k]); for (int c = 0; c < 3; ++c) s[c] += L * T.x[a + j][c]; } return s; }
static double nrm(V3 a) { return std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]); }
static V3 sub(V3 a, V3 b) { return {a[0] - b[0], a[1] - b[1], a[2] - b[2]}; }
static double med(std::vector<double> v) { std::sort(v.begin(), v.end()); size_t n = v.size(); return n % 2 ? v[n / 2] : 0.5 * (v[n / 2 - 1] + v[n / 2]); }
struct Res { double mu, a, cv, K; int pairs, usable; };
static Res analyse(const Orb& o) {
    const int n = (int)o.r.size(); std::vector<double> mus; int pairs = 0; const double eps = 1e-15;
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) { ++pairs; double d = 1.0 / o.r[j] - 1.0 / o.r[i]; if (std::fabs(d) > eps) mus.push_back((o.v2[j] - o.v2[i]) / (2.0 * d)); }
    Res R{}; R.pairs = pairs; R.usable = (int)mus.size(); if (mus.empty()) { R.mu = R.a = R.cv = R.K = 0; return R; } R.mu = med(mus);
    double Em = 0; for (int i = 0; i < n; ++i) Em += o.v2[i] / 2 - R.mu / o.r[i]; Em /= n; R.a = -R.mu / (2 * Em);
    std::vector<double> k; for (int i = 0; i < n; ++i) { double den = 2.0 / o.r[i] - 1.0 / R.a; if (den > 0) k.push_back(o.v2[i] / (C * C * den)); }
    double m = 0; for (double x : k) m += x; m /= k.size(); double s = 0; for (double x : k) s += (x - m) * (x - m); s = k.size() > 1 ? std::sqrt(s / (k.size() - 1)) : 0; R.cv = s / m; R.K = R.mu / (C * C); return R; }
static Orb mockArc(double e, double mu, double a, int n, double dt, double M0deg) { Orb o; double nn = std::sqrt(mu / (a * a * a)); for (int k = 0; k < n; ++k) { double Mk = M0deg * 3.14159265358979323846 / 180.0 + nn * dt * k, E = Mk; for (int it = 0; it < 80; ++it) E -= (E - e * std::sin(E) - Mk) / (1 - e * std::cos(E)); double r = a * (1 - e * std::cos(E)); o.r.push_back(r); o.v2.push_back(mu * (2.0 / r - 1.0 / a)); } return o; }
static double delayf(double K, double r1, double r2, double b) { return (2.0 * K / C) * std::log(4.0 * r1 * r2 / (b * b)); }

int main() {
    std::printf("GOM40b blank-slate run 1 (registered in GOM40b_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    int fails = 0;
    // Validation A: mock on the SCE1 sampling near aphelion
    { const double muT = 1.0e20; Orb o = mockArc(0.0167, muT, 1.496e11, 397, 900.0, 152.2); Res r = analyse(o); bool ok = r.usable > 0 && std::fabs(r.mu / muT - 1) < 1e-6; std::printf("[VA] Kepler mock e = 0.0167 on the SCE1 sampling (397 epochs x 900 s from M = 152.2 deg, Amendment 1): usable pairs %d of %d, mu recovered %.9e vs 1e20 (relative %.2e) -> %s\n", r.usable, r.pairs, r.mu, r.usable ? r.mu / muT - 1 : 0.0, ok ? "met" : "NOT MET"); if (!ok) ++fails;
      // spans for the mock with a year arc, for reference
      Orb o2 = mockArc(0.0167, muT, 1.496e11, 27, 14.0 * 86400.0, 0.0); Res r2 = analyse(o2); std::printf("[VA2] same mock on a year arc (27 x 14 d): mu relative %.2e\n", r2.mu / muT - 1); }
    // Validation B, C
    { double a = 1.496262e11, K = 1476.3512, k = std::sqrt(a / K), Kc = a / (k * k); bool okB = std::fabs(Kc / K - 1) < 1e-12; std::printf("[VB] K = a/k^2 with k = sqrt(a/K): relative %.2e -> %s (IDENTITY)\n", std::fabs(Kc / K - 1), okB ? "met" : "NOT MET"); if (!okB) ++fails;
      double dt = delayf(1476.35, 1.0 * AU, 7.0 * AU, 100.0 * RSUN), an = (2.0 * 1476.35 / C) * std::log(4.0 * AU * 7.0 * AU / (100.0 * RSUN * 100.0 * RSUN)); bool okC = std::fabs(dt / an - 1) < 1e-12; std::printf("[VC] delay formula against its closed form: %s\n", okC ? "met" : "NOT MET"); if (!okC) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    // SCE1 arc, the prompt's route
    Orb arc = readOrb(RAW + "jpl_horizons_earth_heliocentric_2002_157_160.csv"); Res ra = analyse(arc);
    { double rmin = 1e30, rmax = 0; for (double r : arc.r) { rmin = std::min(rmin, r); rmax = std::max(rmax, r); }
      std::printf("SCE1 ARC (geocentre, %zu epochs): r from %.6e to %.6e m (%.6f to %.6f AU) ; pairs %d, usable (|d(1/r)| > 1e-15) %d (%.1f%%)\n", arc.r.size(), rmin, rmax, rmin / AU, rmax / AU, ra.pairs, ra.usable, 100.0 * ra.usable / ra.pairs);
      bool smaOK = ra.a >= 1.4e11 && ra.a <= 1.6e11; std::printf("  mu (median) = %.6e m^3/s^2 ; K = mu/c^2 = %.4f m ; a = %.6e m (%.4f AU) ; CV(K_i) = %.3e\n", ra.mu, ra.K, ra.a, ra.a / AU, ra.cv);
      std::printf("  C3b: SMA in [1.4, 1.6]e11 m: %s ; C4 (CV < 1e-3): %s ; continuity |K - 1476.351|/1476.351 = %.3e (gate 6e-4: %s)\n", smaOK ? "yes" : "NO -> ARC_INSUFFICIENT", ra.cv < 1e-3 ? "met" : "NOT MET", std::fabs(ra.K / 1476.351 - 1), std::fabs(ra.K / 1476.351 - 1) < 6e-4 ? "met" : "NOT MET"); }
    // quantify the pairwise spread on the arc
    { const int n = (int)arc.r.size(); std::vector<double> mus; for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) { double d = 1.0 / arc.r[j] - 1.0 / arc.r[i]; if (std::fabs(d) > 1e-15) mus.push_back((arc.v2[j] - arc.v2[i]) / (2.0 * d)); } if (!mus.empty()) { std::sort(mus.begin(), mus.end()); std::printf("  pairwise mu quantiles (usable pairs): 10%% %.3e, 25%% %.3e, 50%% %.3e, 75%% %.3e, 90%% %.3e (m^3/s^2) ; the standard value is not used\n", mus[mus.size() / 10], mus[mus.size() / 4], mus[mus.size() / 2], mus[3 * mus.size() / 4], mus[9 * mus.size() / 10]); } }
    // Year route
    Orb cal = readOrb(RAW + "jpl_horizons_emb_sun_vectors_2025.csv"), hold = readOrb(RAW + "jpl_horizons_emb_sun_vectors_2024.csv"); Res rc = analyse(cal), rh = analyse(hold);
    std::printf("\nYEAR ROUTE (C3c; GOM26 estimator, EMB): calibration 2025 (%zu epochs): usable %d of %d ; K_cal = %.6f m ; a = %.6e m ; CV %.3e (gate 1e-3: %s)\n", cal.r.size(), rc.usable, rc.pairs, rc.K, rc.a, rc.cv, rc.cv < 1e-3 ? "met" : "NOT MET");
    std::printf("  hold-out 2024: K_hold = %.6f m ; CV %.3e ; |K_hold - K_cal|/K_cal = %.3e (gate 1e-3: %s)\n", rh.K, rh.cv, std::fabs(rh.K - rc.K) / rc.K, std::fabs(rh.K - rc.K) / rc.K < 1e-3 ? "met" : "NOT MET");
    // Conjunction ledger with K_cal
    Tab E = readTab(RAW + "jpl_horizons_earth_heliocentric_2002_157_160.csv"), Cs = readTab(RAW + "jpl_horizons_cassini_heliocentric_2002_157_160.csv"); const double K = rc.K;
    auto geom = [&](double t, double& rE, double& rC, double& b) { V3 e = interp(E, t), c = interp(Cs, t); V3 d = sub(c, e); double dl = nrm(d); V3 cr = {e[1] * d[2] - e[2] * d[1], e[2] * d[0] - e[0] * d[2], e[0] * d[1] - e[1] * d[0]}; b = nrm(cr) / dl; rE = nrm(e); rC = nrm(c); };
    std::vector<double> df, dts; size_t n0 = 0; double rE0, rC0, b0, rE1, rC1, b1;
    for (size_t i = 3; i + 3 < E.t.size(); ++i) { double t = E.t[i], rE, rC, b, rEp, rCp, bp, rEm, rCm, bm; geom(t, rE, rC, b); geom(t + 300.0, rEp, rCp, bp); geom(t - 300.0, rEm, rCm, bm); double dt = delayf(K, rE, rC, b), rate = (delayf(K, rEp, rCp, bp) - delayf(K, rEm, rCm, bm)) / 600.0; dts.push_back(dt); df.push_back(2.0 * FKA * rate); if (n0++ == 0) { rE0 = rE; rC0 = rC; b0 = b; } rE1 = rE; rC1 = rC; b1 = b; }
    std::printf("\nCONJUNCTION LEDGER (K = K_cal = %.6f m, %zu epochs): first b = %.2f R_sun, last b = %.2f R_sun ; Delta t (one-way) first %.6e s, last %.6e s (rise %.3e s) ; Delta f = 2F d(Delta t)/dt: first %.4f Hz, last %.4f Hz, median |Delta f| %.4f Hz\n", K, dts.size(), b0 / RSUN, b1 / RSUN, dts.front(), dts.back(), dts.back() - dts.front(), df.front(), df.back(), med([&] { std::vector<double> a; for (double x : df) a.push_back(std::fabs(x)); return a; }()));
    { size_t i = E.t.size() / 2; double t = E.t[i], rE, rC, b; geom(t, rE, rC, b); std::printf("  local k(r) = sqrt(r/K) at the middle epoch: Earth r = %.4f AU : k = %.2f ; b = %.2f R_sun : k = %.2f ; Cassini r = %.4f AU : k = %.2f ; z = K/r: %.3e, %.3e, %.3e\n", rE / AU, std::sqrt(rE / K), b / RSUN, std::sqrt(b / K), rC / AU, std::sqrt(rC / K), K / rE, K / b, K / rC); }
    std::printf("\nStatus: no residual-correlation claim (C6); K carried from the year route is not fitted to Doppler or delay.\n");
    return 0;
}
