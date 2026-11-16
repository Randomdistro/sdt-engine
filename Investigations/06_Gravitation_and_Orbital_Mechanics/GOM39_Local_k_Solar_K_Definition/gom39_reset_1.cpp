// GOM39 blank-slate run 1 (2026-10-11). Registration: GOM39_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
// Local-k / K (= R/k^2) grammar: validation A (identity), validation B (chord integral), SCE1 Earth main sequence (literal R1 and corrected R2), local-k ledger.
// Author: J. C. Harvey, Melbourne.
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
static const char* HE = "Datasets/solar_propagation_2026-08/raw/jpl_horizons_earth_heliocentric_2002_157.csv";
static const char* HC = "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_heliocentric_2002_157.csv";
static const double C = 299792458.0, AU = 149597870700.0, RSUN = 6.957e8, KGOM26 = 1476.351, AGOM26 = 1.496262e11, KPRM = 1476.35;
static std::vector<std::string> splitc(const std::string& ln) { std::vector<std::string> f; size_t p = 0; while (true) { size_t q = ln.find(',', p); if (q == std::string::npos) break; f.push_back(ln.substr(p, q - p)); p = q + 1; } return f; }
struct St { std::vector<std::array<double, 6>> v; };
#include <array>
static std::vector<std::array<double, 6>> readSt(const char* path) { std::vector<std::array<double, 6>> o; std::ifstream h(path); std::string ln; bool in = false; while (std::getline(h, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue; auto f = splitc(ln); if (f.size() < 8) continue; std::array<double, 6> a; for (int i = 0; i < 6; ++i) a[i] = std::stod(f[2 + i]) * 1e3; o.push_back(a); } return o; }
static double med(std::vector<double> v) { std::sort(v.begin(), v.end()); size_t n = v.size(); return n % 2 ? v[n / 2] : 0.5 * (v[n / 2 - 1] + v[n / 2]); }
static double mean(const std::vector<double>& v) { double s = 0; for (double a : v) s += a; return s / v.size(); }
static double sd(const std::vector<double>& v) { double m = mean(v), s = 0; for (double a : v) s += (a - m) * (a - m); return std::sqrt(s / (v.size() - 1)); }
static double chordExact(double K, double b, double r1, double r2) { double s1 = -std::sqrt(r1 * r1 - b * b), s2 = std::sqrt(r2 * r2 - b * b); return 2.0 * K / C * (std::log(s2 + r2) - std::log(s1 + r1)); }
static double chordNum(double K, double b, double r1, double r2, long N) { double s1 = -std::sqrt(r1 * r1 - b * b), s2 = std::sqrt(r2 * r2 - b * b), h = (s2 - s1) / N; auto z = [&](double l) { return K / std::sqrt(b * b + l * l); }; double s = z(s1) + z(s2); for (long i = 1; i < N; ++i) s += z(s1 + i * h) * (i % 2 ? 4.0 : 2.0); return 2.0 / C * s * h / 3.0; }

int main() {
    std::printf("GOM39 blank-slate run 1 (registered in GOM39_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    int fails = 0;
    // Validation A
    { const double R = 1.496e11, v = 29780.0, k = C / v, K = R / (k * k); double worst = 0; for (int e = 9; e <= 13; ++e) for (double m : {1.0, 3.0}) { if (e == 13 && m > 1) continue; double r = m * std::pow(10.0, e); double vr = (C / k) * std::sqrt(R / r), kr = C / vr, Kr = r / (kr * kr); worst = std::max(worst, std::fabs(Kr / K - 1)); }
      bool ok = worst < 1e-12; std::printf("[A] synthetic main sequence R = %.3e m, v = %.0f m/s: k = %.4f, K = R/k^2 = %.6f m ; r/k(r)^2 over r = 1e9 ... 1e13 m : worst relative %.2e (gate 1e-12) -> %s (IDENTITY)\n", R, v, k, K, worst, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    auto E = readSt(HE), Cs = readSt(HC);
    // geometry at the middle sample
    size_t mid = E.size() / 2; double e[3] = {E[mid][0], E[mid][1], E[mid][2]}, c[3] = {Cs[mid][0], Cs[mid][1], Cs[mid][2]}; double d[3] = {c[0] - e[0], c[1] - e[1], c[2] - e[2]}, dl = std::sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]); double cr[3] = {e[1] * d[2] - e[2] * d[1], e[2] * d[0] - e[0] * d[2], e[0] * d[1] - e[1] * d[0]};
    const double bSce = std::sqrt(cr[0] * cr[0] + cr[1] * cr[1] + cr[2] * cr[2]) / dl, rE = std::sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]), rC = std::sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    // Validation B
    { double ex = chordExact(KPRM, bSce, rE, rC), nu = chordNum(KPRM, bSce, rE, rC, 2000000), rel = std::fabs(nu / ex - 1);
      double b2 = 0.01 * rE, ex2 = chordExact(KPRM, b2, rE, rC), as2 = 2.0 * KPRM / C * std::log(4.0 * rE * rC / (b2 * b2)), exs = chordExact(KPRM, bSce, rE, rC), ass = 2.0 * KPRM / C * std::log(4.0 * rE * rC / (bSce * bSce));
      bool ok = rel < 1e-6 && std::fabs(as2 / ex2 - 1) < 1e-3; std::printf("[B] chord at the SCE1 geometry (b = %.2f R_sun, r1 = %.4f AU, r2 = %.4f AU): numerical Simpson %.9e s, exact %.9e s, relative %.2e (gate 1e-6) ; far-zone asymptotic (b = 0.01 r1): %.3e vs exact %.3e, relative %.2e (gate 1e-3) ; asymptotic at the SCE1 b: relative %.2e (reported) -> %s (calculus)\n\n", bSce / RSUN, rE / AU, rC / AU, nu, ex, rel, as2, ex2, std::fabs(as2 / ex2 - 1), std::fabs(ass / exs - 1), ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    // SCE1 main sequence
    std::vector<double> ks, Ks, K2, Rs; for (auto& s : E) { double R = std::sqrt(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]), v = std::sqrt(s[3] * s[3] + s[4] * s[4] + s[5] * s[5]), k = C / v, K = R / (k * k); ks.push_back(k); Ks.push_back(K); Rs.push_back(R); K2.push_back(K / (2.0 - R / AGOM26)); }
    std::printf("SCE1 Earth main sequence (%zu samples, day 157): R = %.5e to %.5e m (%.5f AU) ; v = %.2f m/s at the middle\n", E.size(), *std::min_element(Rs.begin(), Rs.end()), *std::max_element(Rs.begin(), Rs.end()), mean(Rs) / AU, std::sqrt(E[mid][3] * E[mid][3] + E[mid][4] * E[mid][4] + E[mid][5] * E[mid][5]));
    std::printf("  R1 (literal, instantaneous speed): median k = %.4f ; median K = %.4f m ; CV(K) = %.2e\n", med(ks), med(Ks), sd(Ks) / mean(Ks));
    std::printf("  factor (2 - R/a) with a = %.6e m : %.5f ; R2 (corrected, circular-speed reading): median K = %.4f m ; CV = %.2e ; against the GOM26 invariant %.3f m : %+.3e (gate 4e-4: %s)\n", AGOM26, 2.0 - mean(Rs) / AGOM26, med(K2), sd(K2) / mean(K2), KGOM26, med(K2) / KGOM26 - 1, std::fabs(med(K2) / KGOM26 - 1) < 4e-4 ? "met" : "NOT MET");
    std::printf("  R1 against the GOM26 invariant: %+.3e (the literal procedure misses by the eccentricity factor)\n\n", med(Ks) / KGOM26 - 1);
    // local-k ledger
    std::printf("LOCAL-k LEDGER k(r) = sqrt(r/K): radius r, k with K = 1476.351 m (R2), k with the literal K_inst median\n");
    struct Rr { const char* nm; double r; } rr[3] = {{"Earth R", rE}, {"impact parameter b", bSce}, {"Cassini R", rC}}; double kv[3];
    for (int i = 0; i < 3; ++i) { kv[i] = std::sqrt(rr[i].r / KGOM26); std::printf("  %-20s r = %.5e m (%.4f AU, %.2f R_sun) : k = %.2f ; with K_inst %.2f ; z = K/r = %.3e\n", rr[i].nm, rr[i].r, rr[i].r / AU, rr[i].r / RSUN, kv[i], std::sqrt(rr[i].r / med(Ks)), KGOM26 / rr[i].r); }
    std::printf("  pairwise distinct: %s\n", (kv[0] != kv[1] && kv[1] != kv[2] && kv[0] != kv[2]) ? "yes" : "NO");
    std::printf("\nStatus: ODF Doppler-solar-K path definition CLOSED (grammar); the empirical status is unchanged (GOM36/37: UNADJUDICATED_BY_SENSITIVITY).\n");
    return 0;
}
