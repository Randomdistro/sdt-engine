// GOM36 blank-slate run 1 (2026-10-11). Registration: GOM36_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
// Procedure A (prompt literal: level-ratio scale) and B (amended: fixed Ka carrier, two-way geometry, offset from the train half); solar geometry and delay-rate proxy from helio vectors with K = 1476.35 m.
// Author: J. C. Harvey, Melbourne.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

static const char* ODF = "Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_odf.odf";
static const char* H5 = "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_dss25_rr_2002_157.csv";
static const char* H15 = "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_dss25_rr_2002_157_160.csv";
static const char* HC = "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_heliocentric_2002_157.csv";
static const char* HE = "Datasets/solar_propagation_2026-08/raw/jpl_horizons_earth_heliocentric_2002_157.csv";
static const double CKM = 299792.458, AUKM = 149597870.7, RSUNKM = 695700.0, KSUN = 1476.35, C = 299792458.0, FKA = 32.028e9, FREF = 2116648992.0;
static uint32_t be32(const uint8_t* p) { return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3]; }
static uint64_t bits(const uint8_t* p, int start1, int n) { uint64_t v = 0; for (int i = 0; i < n; ++i) { int b = start1 - 1 + i; v = (v << 1) | ((p[b / 8] >> (7 - b % 8)) & 1); } return v; }
static long long days_from_civil(int y, int m, int d) { y -= m <= 2; long long era = (y >= 0 ? y : y - 399) / 400; unsigned yoe = unsigned(y - era * 400); unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; return era * 146097 + (long long)doe - 719468; }
static double sec1950(int y, int m, int d, int hh, int mm) { return double(days_from_civil(y, m, d) + 7305) * 86400.0 + hh * 3600.0 + mm * 60.0; }
static const char* MON[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
static std::vector<std::string> splitc(const std::string& ln) { std::vector<std::string> f; size_t p = 0; while (true) { size_t q = ln.find(',', p); if (q == std::string::npos) break; f.push_back(ln.substr(p, q - p)); p = q + 1; } return f; }
static double parseDate(std::string d) { size_t s = d.find("A.D."); if (s != std::string::npos) d = d.substr(s + 5); else d = d.substr(d.find_first_not_of(' ')); int y = std::stoi(d.substr(0, 4)); std::string mn = d.substr(5, 3); int m = 0; for (int i = 0; i < 12; ++i) if (mn == MON[i]) m = i + 1; return sec1950(y, m, std::stoi(d.substr(9, 2)), std::stoi(d.substr(12, 2)), std::stoi(d.substr(15, 2))); }
struct Tab { std::vector<double> t, delta, dd; };
static Tab readTab(const char* path) { Tab T; std::ifstream h(path); std::string ln; bool in = false; while (std::getline(h, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue; auto f = splitc(ln); if (f.size() < 5) continue; T.t.push_back(parseDate(f[0])); T.delta.push_back(std::stod(f[3])); T.dd.push_back(std::stod(f[4])); } return T; }
struct Vec { std::vector<double> t, x, y, z; };
static Vec readVec(const char* path) { Vec V; std::ifstream h(path); std::string ln; bool in = false; while (std::getline(h, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue; auto f = splitc(ln); if (f.size() < 8) continue; V.t.push_back(parseDate(f[1]) - 64.184); V.x.push_back(std::stod(f[2])); V.y.push_back(std::stod(f[3])); V.z.push_back(std::stod(f[4])); } return V; }
static double interp(const std::vector<double>& x, const std::vector<double>& y, double t) { size_t i = std::upper_bound(x.begin(), x.end(), t) - x.begin(); if (i == 0) i = 1; if (i >= x.size()) i = x.size() - 1; double w = (t - x[i - 1]) / (x[i] - x[i - 1]); return y[i - 1] + w * (y[i] - y[i - 1]); }
static double med(std::vector<double> v) { std::sort(v.begin(), v.end()); size_t n = v.size(); return n % 2 ? v[n / 2] : 0.5 * (v[n / 2 - 1] + v[n / 2]); }
static double meanv(const std::vector<double>& v) { double s = 0; for (double a : v) s += a; return s / v.size(); }
static double sdv(const std::vector<double>& v) { double m = meanv(v), s = 0; for (double a : v) s += (a - m) * (a - m); return std::sqrt(s / (v.size() - 1)); }
static double corr(const std::vector<double>& a, const std::vector<double>& b) { double ma = meanv(a), mb = meanv(b), sab = 0, saa = 0, sbb = 0; for (size_t i = 0; i < a.size(); ++i) { sab += (a[i] - ma) * (b[i] - mb); saa += (a[i] - ma) * (a[i] - ma); sbb += (b[i] - mb) * (b[i] - mb); } return sab / std::sqrt(saa * sbb); }
static std::vector<double> detrend(const std::vector<double>& t, const std::vector<double>& y) { double mt = meanv(t), my = meanv(y), sxy = 0, sxx = 0; for (size_t i = 0; i < t.size(); ++i) { sxy += (t[i] - mt) * (y[i] - my); sxx += (t[i] - mt) * (t[i] - mt); } double s = sxy / sxx; std::vector<double> r(t.size()); for (size_t i = 0; i < t.size(); ++i) r[i] = y[i] - my - s * (t[i] - mt); return r; }
static double slope(const std::vector<double>& t, const std::vector<double>& y) { double mt = meanv(t), my = meanv(y), sxy = 0, sxx = 0; for (size_t i = 0; i < t.size(); ++i) { sxy += (t[i] - mt) * (y[i] - my); sxx += (t[i] - mt) * (t[i] - mt); } return sxy / sxx; }
static void summ(const char* nm, const std::vector<double>& r) { std::vector<double> c = r; std::printf("  %-34s min %.4f ; median %.4f ; max %.4f ; sd %.4f\n", nm, *std::min_element(c.begin(), c.end()), med(c), *std::max_element(c.begin(), c.end()), sdv(c)); }
struct G { double b, rE, rC, sep; };
static G geom(const Vec& E, const Vec& Cs, double t) {
    double e[3] = {interp(E.t, E.x, t), interp(E.t, E.y, t), interp(E.t, E.z, t)}, c[3] = {interp(Cs.t, Cs.x, t), interp(Cs.t, Cs.y, t), interp(Cs.t, Cs.z, t)};
    double d[3] = {c[0] - e[0], c[1] - e[1], c[2] - e[2]}, dl = std::sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]); double cr[3] = {e[1] * d[2] - e[2] * d[1], e[2] * d[0] - e[0] * d[2], e[0] * d[1] - e[1] * d[0]};
    G g; g.b = std::sqrt(cr[0] * cr[0] + cr[1] * cr[1] + cr[2] * cr[2]) / dl; g.rE = std::sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); g.rC = std::sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    double ds = -(e[0] * d[0] + e[1] * d[1] + e[2] * d[2]) / (g.rE * dl); g.sep = std::acos(std::max(-1.0, std::min(1.0, ds))) * 180.0 / 3.14159265358979323846; return g; }
static double delay(const G& g) { return (2.0 * KSUN / C) * std::log(4.0 * g.rE * g.rC / (g.b * g.b)); }

int main() {
    std::printf("GOM36 blank-slate run 1 (registered in GOM36_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    std::ifstream f(ODF, std::ios::binary); std::vector<uint8_t> buf((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    std::vector<double> T, OBS;
    for (int r = 6; r <= 7452; ++r) { const uint8_t* p = buf.data() + 36 * (r - 1); const uint8_t* q = p + 16; int type = int(bits(q, 20, 6)), rx = int(bits(q, 4, 7)), tx = int(bits(q, 11, 7)), valid = int(bits(q, 32, 1)); if (type != 12 || valid || rx != 25 || tx != 25) continue; T.push_back(double(be32(p)) + double(bits(p + 4, 1, 10)) / 1000.0); OBS.push_back(double(int32_t(be32(p + 8))) + double(int32_t(be32(p + 12))) / 1e9); }
    const size_t n = T.size(); Tab a = readTab(H5), b15 = readTab(H15); Vec E = readVec(HE), Cs = readVec(HC); int fails = 0;
    // V3 analytic delay check
    { G g{100.0 * RSUNKM, AUKM, 7.0 * AUKM, 0}; double dt = delay(g), an = (2.0 * KSUN / C) * std::log(4.0 * AUKM * 7.0 * AUKM / (100.0 * RSUNKM * 100.0 * RSUNKM)); bool ok = std::fabs(dt / an - 1) < 1e-12; std::printf("[V3] delay formula: %.9e s against the closed form %.9e s -> %s\n", dt, an, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // V2
    { double t0 = T[n / 2]; G g = geom(E, Cs, t0); double d = 0; { double e[3] = {interp(E.t, E.x, t0), interp(E.t, E.y, t0), interp(E.t, E.z, t0)}, c[3] = {interp(Cs.t, Cs.x, t0), interp(Cs.t, Cs.y, t0), interp(Cs.t, Cs.z, t0)}; d = std::sqrt((c[0] - e[0]) * (c[0] - e[0]) + (c[1] - e[1]) * (c[1] - e[1]) + (c[2] - e[2]) * (c[2] - e[2])); }
      double dd = interp(a.t, a.delta, t0) * AUKM; bool ok = g.rE / AUKM > 0.98 && g.rE / AUKM < 1.02 && g.rC / AUKM > 7.2 && g.rC / AUKM < 7.6 && std::fabs(d / dd - 1) < 1e-3; std::printf("[V2] |E| = %.4f AU, |C| = %.4f AU, Earth-Cassini from vectors %.6e km against DSS-25 table %.6e km (relative %.1e) -> %s\n", g.rE / AUKM, g.rC / AUKM, d, dd, d / dd - 1, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // predictors
    std::vector<double> fA(n), f2w(n); for (size_t i = 0; i < n; ++i) { double rrx = interp(a.t, a.dd, T[i]); double rt = 2.0 * interp(a.t, a.delta, T[i]) * AUKM / CKM; double r2w = 0.5 * (rrx + interp(b15.t, b15.dd, T[i] - rt)); fA[i] = -2.0 * rrx / CKM * FREF; f2w[i] = 2.0 / CKM * FKA * r2w; }
    // V1: GOM_DAT8 reproduction
    { std::vector<double> r(n); double m = 0; for (size_t i = 0; i < n; ++i) { r[i] = OBS[i] - f2w[i]; m += r[i]; } m /= n; for (double& x : r) x -= m; double s = sdv(r); bool ok = std::fabs(s - 2.639) < 0.01; std::printf("[V1] two-way predictor, offset from the whole span: residual sd %.3f Hz (GOM_DAT8: 2.639) -> %s\n\n", s, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    // split
    const size_t mid = n / 2; std::vector<double> tTest(T.begin() + mid, T.end()), oTest(OBS.begin() + mid, OBS.end());
    // Procedure A
    std::vector<double> ratio; for (size_t i = 0; i < mid; ++i) ratio.push_back(OBS[i] / fA[i]); double sA = med(ratio); std::vector<double> rA; for (size_t i = mid; i < n; ++i) rA.push_back(OBS[i] - sA * fA[i]);
    std::printf("PROCEDURE A (prompt literal): s = median(obs/f_A) on train = %.5f (CALIBRATED(1)); test residual r_A = obs - s f_A [Hz]\n", sA); summ("r_A", rA); { std::vector<double> ao; for (size_t i = mid; i < n; ++i) ao.push_back(std::fabs(OBS[i])); std::vector<double> ar; for (double x : rA) ar.push_back(std::fabs(x)); std::printf("  median|r_A| / median|obs| = %.3f (a scale that explained the observable would leave a small ratio)\n\n", med(ar) / med(ao)); }
    // Procedure B
    double c0 = 0; for (size_t i = 0; i < mid; ++i) c0 += OBS[i] - f2w[i]; c0 /= mid; std::vector<double> rB; for (size_t i = mid; i < n; ++i) rB.push_back(OBS[i] - f2w[i] - c0);
    std::printf("PROCEDURE B (amended): f_B = (2/c) F rdot_2w with F = 32.028 GHz fixed ; offset C0 = %.3f Hz from the train half (CALIBRATED(1)); test residual r_B [Hz]\n", c0); summ("r_B", rB);
    std::printf("  test-half residual drift (OLS) = %+.3f Hz/hour ; train-half-defined offset change relative to the test half mean: %+.3f Hz\n\n", slope(tTest, rB) * 3600.0, meanv(rB));
    // solar geometry on the test half
    std::vector<double> bR, sep, dt, ddt, fp, inb; for (size_t i = mid; i < n; ++i) { double t = T[i]; G g = geom(E, Cs, t); G gp = geom(E, Cs, t + 150.0), gm = geom(E, Cs, t - 150.0); double rate = (delay(gp) - delay(gm)) / 300.0; bR.push_back(g.b / RSUNKM); sep.push_back(g.sep); dt.push_back(delay(g) * 1e6); ddt.push_back(rate); fp.push_back(2.0 * FKA * rate); inb.push_back(1.0 / g.b); }
    std::printf("SOLAR GEOMETRY (test half, K = %.2f m): elongation %.3f to %.3f deg ; b = %.2f to %.2f R_sun (%.4f to %.4f AU) ; one-way delay %.3f to %.3f us ; d(delay)/dt = %.4e to %.4e\n", KSUN, sep.front(), sep.back(), bR.front(), bR.back(), bR.front() * RSUNKM / AUKM, bR.back() * RSUNKM / AUKM, dt.front(), dt.back(), ddt.front(), ddt.back());
    std::printf("  predicted Doppler contribution 2 F d(delay)/dt : mean %.4f Hz ; sd over the test half %.3e Hz ; peak-to-peak %.3e Hz ; drift %+.3e Hz/hour\n\n", meanv(fp), sdv(fp), *std::max_element(fp.begin(), fp.end()) - *std::min_element(fp.begin(), fp.end()), slope(tTest, fp) * 3600.0);
    // correlations
    auto rep = [&](const char* nm, const std::vector<double>& r) { std::vector<double> rd = detrend(tTest, r), fd = detrend(tTest, fp), id = detrend(tTest, inb); std::printf("  %-4s corr(r, dDelay/dt) raw %+.4f ; corr(r, 1/b) raw %+.4f ; detrended: corr(r, dDelay/dt) %+.4f ; corr(r, 1/b) %+.4f\n", nm, corr(r, ddt), corr(r, inb), corr(rd, fd), corr(rd, id)); };
    std::printf("CORRELATIONS (test half):\n"); rep("r_A", rA); rep("r_B", rB);
    double cr = std::fabs(corr(rB, ddt)); std::printf("  prompt's rule on the raw |corr(r_B, d(delay)/dt)| = %.4f : %s\n", cr, cr >= 0.5 ? "SOLAR_K_RESIDUAL_SIGNAL" : (cr < 0.2 ? "NO_SOLAR_K_RESIDUAL_SIGNAL" : "UNADJUDICATED"));
    { double cv = 0, vf = 0, mr = meanv(rB), mf = meanv(fp); for (size_t i = 0; i < rB.size(); ++i) { cv += (rB[i] - mr) * (fp[i] - mf); vf += (fp[i] - mf) * (fp[i] - mf); } double kappa = cv / vf; std::printf("  regression coefficient kappa = cov(r_B, Df_pred)/var(Df_pred) = %+.3e (SDT value 1) ; sd(r_B)/sd(Df_pred) = %.3e\n", kappa, sdv(rB) / sdv(fp)); }
    bool sens = sdv(fp) > 0.03 * sdv(rB); std::printf("SENSITIVITY GATE (predicted sd over the test half > 3%% of the residual sd = %.4f Hz): predicted sd %.3e Hz -> %s\n", 0.03 * sdv(rB), sdv(fp), sens ? "met" : "NOT MET");
    std::printf("AMENDED OUTCOME: %s\n", sens ? "decided by the correlation" : "UNADJUDICATED_BY_SENSITIVITY (the correlation is time-confounded)");
    return 0;
}
