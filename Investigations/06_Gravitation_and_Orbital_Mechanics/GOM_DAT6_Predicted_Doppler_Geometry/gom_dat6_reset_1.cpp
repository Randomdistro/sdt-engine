// GOM_DAT6 blank-slate run 1 (2026-10-11). Registration: GOM_DAT6_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
// Helpers (decoder, tables, interpolation, geometry) copied from gom37_reset_1.cpp; the main program is new.
// GOM37 blank-slate run 1 (2026-10-11). Registration: GOM37_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
// Multi-day (157-160) K252 ODF Doppler against the two-way Ka predictor; offset models M1 (global, day 157), M2 (per day), A' (prompt literal: level-ratio scale + train-only linear detrend);
// solar delay-rate proxy with K = 1476.35 m (never fitted); sensitivity gate and the prompt's C4-C7.
// Author: J. C. Harvey, Melbourne.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

static const std::string RAW = "Datasets/solar_propagation_2026-08/raw/";
static const double CKM = 299792.458, AUKM = 149597870.7, RSUNKM = 695700.0, KSUN = 1476.35, C = 299792458.0, FKA = 32.028e9, FREF = 2116648992.0;
static uint32_t be32(const uint8_t* p) { return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3]; }
static uint64_t bits(const uint8_t* p, int start1, int n) { uint64_t v = 0; for (int i = 0; i < n; ++i) { int b = start1 - 1 + i; v = (v << 1) | ((p[b / 8] >> (7 - b % 8)) & 1); } return v; }
static long long days_from_civil(int y, int m, int d) { y -= m <= 2; long long era = (y >= 0 ? y : y - 399) / 400; unsigned yoe = unsigned(y - era * 400); unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; return era * 146097 + (long long)doe - 719468; }
static double sec1950(int y, int m, int d, int hh, int mm) { return double(days_from_civil(y, m, d) + 7305) * 86400.0 + hh * 3600.0 + mm * 60.0; }
static const char* MON[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
static std::vector<std::string> splitc(const std::string& ln) { std::vector<std::string> f; size_t p = 0; while (true) { size_t q = ln.find(',', p); if (q == std::string::npos) break; f.push_back(ln.substr(p, q - p)); p = q + 1; } return f; }
static double parseDate(std::string d) { size_t s = d.find("A.D."); if (s != std::string::npos) d = d.substr(s + 5); else d = d.substr(d.find_first_not_of(' ')); int y = std::stoi(d.substr(0, 4)); std::string mn = d.substr(5, 3); int m = 0; for (int i = 0; i < 12; ++i) if (mn == MON[i]) m = i + 1; return sec1950(y, m, std::stoi(d.substr(9, 2)), std::stoi(d.substr(12, 2)), std::stoi(d.substr(15, 2))); }
struct Tab { std::vector<double> t, delta, dd; };
static Tab readTab(const std::string& path) { Tab T; std::ifstream h(path); std::string ln; bool in = false; while (std::getline(h, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue; auto f = splitc(ln); if (f.size() < 5) continue; T.t.push_back(parseDate(f[0])); T.delta.push_back(std::stod(f[3])); T.dd.push_back(std::stod(f[4])); } return T; }
struct Vec { std::vector<double> t, x, y, z; };
static Vec readVec(const std::string& path) { Vec V; std::ifstream h(path); std::string ln; bool in = false; while (std::getline(h, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue; auto f = splitc(ln); if (f.size() < 8) continue; V.t.push_back(parseDate(f[1]) - 64.184); V.x.push_back(std::stod(f[2])); V.y.push_back(std::stod(f[3])); V.z.push_back(std::stod(f[4])); } return V; }
static double interpL(const std::vector<double>& x, const std::vector<double>& y, double t) { size_t i = std::upper_bound(x.begin(), x.end(), t) - x.begin(); if (i == 0) i = 1; if (i >= x.size()) i = x.size() - 1; double w = (t - x[i - 1]) / (x[i] - x[i - 1]); return y[i - 1] + w * (y[i] - y[i - 1]); }
static double interpC(const std::vector<double>& x, const std::vector<double>& y, double t) { size_t i = std::upper_bound(x.begin(), x.end(), t) - x.begin(); if (i == 0) i = 1; if (i >= x.size()) i = x.size() - 1; long a = (long)i - 2; if (a < 0) a = 0; if (a + 3 >= (long)x.size()) a = (long)x.size() - 4; double s = 0; for (int j = 0; j < 4; ++j) { double L = 1; for (int k = 0; k < 4; ++k) if (k != j) L *= (t - x[a + k]) / (x[a + j] - x[a + k]); s += L * y[a + j]; } return s; }
static double med(std::vector<double> v) { std::sort(v.begin(), v.end()); size_t n = v.size(); return n % 2 ? v[n / 2] : 0.5 * (v[n / 2 - 1] + v[n / 2]); }
static double meanv(const std::vector<double>& v) { double s = 0; for (double a : v) s += a; return s / v.size(); }
static double sdv(const std::vector<double>& v) { double m = meanv(v), s = 0; for (double a : v) s += (a - m) * (a - m); return std::sqrt(s / (v.size() - 1)); }
static double corr(const std::vector<double>& a, const std::vector<double>& b) { double ma = meanv(a), mb = meanv(b), sab = 0, saa = 0, sbb = 0; for (size_t i = 0; i < a.size(); ++i) { sab += (a[i] - ma) * (b[i] - mb); saa += (a[i] - ma) * (a[i] - ma); sbb += (b[i] - mb) * (b[i] - mb); } return sab / std::sqrt(saa * sbb); }
static double slope(const std::vector<double>& t, const std::vector<double>& y) { double mt = meanv(t), my = meanv(y), sxy = 0, sxx = 0; for (size_t i = 0; i < t.size(); ++i) { sxy += (t[i] - mt) * (y[i] - my); sxx += (t[i] - mt) * (t[i] - mt); } return sxy / sxx; }
struct G { double b, rE, rC, sep; };
static G geom(const Vec& E, const Vec& Cs, double t) { double e[3] = {interpL(E.t, E.x, t), interpL(E.t, E.y, t), interpL(E.t, E.z, t)}, c[3] = {interpL(Cs.t, Cs.x, t), interpL(Cs.t, Cs.y, t), interpL(Cs.t, Cs.z, t)};
    double d[3] = {c[0] - e[0], c[1] - e[1], c[2] - e[2]}, dl = std::sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]); double cr[3] = {e[1] * d[2] - e[2] * d[1], e[2] * d[0] - e[0] * d[2], e[0] * d[1] - e[1] * d[0]};
    G g; g.b = std::sqrt(cr[0] * cr[0] + cr[1] * cr[1] + cr[2] * cr[2]) / dl; g.rE = std::sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); g.rC = std::sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
    double ds = -(e[0] * d[0] + e[1] * d[1] + e[2] * d[2]) / (g.rE * dl); g.sep = std::acos(std::max(-1.0, std::min(1.0, ds))) * 180.0 / 3.14159265358979323846; return g; }
static double delayf(const G& g) { return (2.0 * KSUN / C) * std::log(4.0 * g.rE * g.rC / (g.b * g.b)); }

struct Rec { double t, obs; int day; int dl, ul, ex; double ref; };
static int labelRows(const std::string& lbl) { std::ifstream f(lbl); std::string ln; bool in = false; while (std::getline(f, ln)) { if (ln.find("= ODF3C_TABLE") != std::string::npos && ln.find("OBJECT") != std::string::npos) in = true; if (in && ln.find("ROWS") != std::string::npos) { size_t p = ln.find('='); return std::stoi(ln.substr(p + 1)); } } return -1; }
static bool loadDay(int day, std::vector<Rec>& out, int& rowsLabel, int& rowsAll, bool& mono) {
    char buf1[256], buf2[256]; std::snprintf(buf1, sizeof buf1, "cassini_sce1/cors_0021/sce1_%d/odf/c32easc2002_%d_0000k252v0.odf", day, day); std::snprintf(buf2, sizeof buf2, "cassini_sce1/cors_0021/sce1_%d/odf/c32easc2002_%d_0000k252v0.lbl", day, day);
    std::ifstream f(RAW + buf1, std::ios::binary); if (!f) return false; std::vector<uint8_t> b((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); rowsLabel = labelRows(RAW + buf2); rowsAll = 0; mono = true; double prev = 0;
    for (int r = 6; r <= 5 + rowsLabel; ++r) { const uint8_t* p = b.data() + 36 * (r - 1); ++rowsAll; const uint8_t* q = p + 16; double t = double(be32(p)) + double(bits(p + 4, 1, 10)) / 1000.0; if (t < prev) mono = false; prev = t;
        int type = int(bits(q, 20, 6)), rx = int(bits(q, 4, 7)), tx = int(bits(q, 11, 7)), valid = int(bits(q, 32, 1)); if (type != 12 || valid || rx != 25 || tx != 25) continue;
        Rec x; x.t = t; x.obs = double(int32_t(be32(p + 8))) + double(int32_t(be32(p + 12))) / 1e9; x.day = day; x.dl = int(bits(q, 26, 2)); x.ul = int(bits(q, 28, 2)); x.ex = int(bits(q, 30, 2)); x.ref = (double(bits(q, 51, 22)) * 16777216.0 + double(bits(q, 73, 24))) / 1000.0; out.push_back(x); }
    return true; }

int main() {
    std::printf("GOM_DAT6 blank-slate run 1 (registered in GOM_DAT6_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    int fails = 0; std::vector<Rec> v; int rl = 0, ra = 0; bool mono = true; if (!loadDay(157, v, rl, ra, mono)) { std::printf("file missing\n"); return 1; }
    { bool ok = rl == ra && mono; std::printf("[V1] label rows %d, rows read %d, increasing time tags %s ; selected %zu type-12 valid 25/25 records -> %s\n", rl, ra, mono ? "yes" : "NO", v.size(), ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    Tab t5 = readTab(RAW + "jpl_horizons_cassini_dss25_rr_2002_157.csv"), t15 = readTab(RAW + "jpl_horizons_cassini_dss25_rr_2002_157_160.csv"); Vec E = readVec(RAW + "jpl_horizons_earth_heliocentric_2002_157_160.csv"), Cs = readVec(RAW + "jpl_horizons_cassini_heliocentric_2002_157_160.csv");
    { double t0 = v.front().t, t1 = v.back().t, rtlt = 2.0 * interpC(t15.t, t15.delta, t0) * AUKM / CKM; bool ok = t15.t.front() < t0 - rtlt - 1000 && t15.t.back() > t1 + 1000; std::printf("[V2] table coverage: Horizons %.0f to %.0f ; window %.0f to %.0f ; window - RTLT starts %.0f -> %s\n", t15.t.front(), t15.t.back(), t0, t1, t0 - rtlt, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { double wc = 0; for (size_t i = 0; i < t5.t.size(); ++i) wc = std::max(wc, std::fabs(interpC(t15.t, t15.dd, t5.t[i]) / t5.dd[i] - 1)); bool ok = wc < 1e-7; std::printf("[V3] cubic interpolation of the 15-min table at the 5-min epochs: worst relative %.2e -> %s\n", wc, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { double worst = 0; for (size_t i = 2; i + 2 < t5.t.size(); ++i) { double dl = (t5.delta[i + 1] - t5.delta[i - 1]) * AUKM / (t5.t[i + 1] - t5.t[i - 1]); worst = std::max(worst, std::fabs(dl - t5.dd[i]) / std::fabs(t5.dd[i])); } bool ok = worst < 1e-3; std::printf("[V4] d(delta)/dt from the table against deldot (5-min table): worst relative %.2e -> %s\n", worst, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    std::printf("C2: DSS-25 Earth-fixed coordinates (Horizons site record in the table header): E-lon 243.1246368 deg, lat 35.337612 deg, alt 0.959628 km -> MEASURED-INPUT, provenance the Horizons site database (not a TRK-2-25 station table)\n\n");
    std::vector<double> obs, pL, p2, fp, tt; for (auto& x : v) { double rx = interpC(t15.t, t15.dd, x.t), rt = 2.0 * interpC(t15.t, t15.delta, x.t) * AUKM / CKM, r2w = 0.5 * (rx + interpC(t15.t, t15.dd, x.t - rt)); obs.push_back(x.obs); pL.push_back(-2.0 * rx / CKM * FREF); p2.push_back(2.0 / CKM * FKA * r2w); tt.push_back(x.t);
        G gp = geom(E, Cs, x.t + 150.0), gm = geom(E, Cs, x.t - 150.0); fp.push_back(2.0 * FKA * (delayf(gp) - delayf(gm)) / 300.0); }
    auto absv = [](std::vector<double> a) { for (double& x : a) x = std::fabs(x); return a; };
    double mo = med(absv(obs)), mL = med(absv(pL)), m2 = med(absv(p2));
    std::printf("LEVEL (%zu records): median |obs| = %.1f Hz ; median |P_lit| = %.1f Hz (ratio %.4f) ; median |P_2w| = %.1f Hz (ratio %.4f)\n", v.size(), mo, mL, mL / mo, m2, m2 / mo);
    std::printf("  original gate (ratio in [0.1, 10]): P_lit %s, P_2w %s ; corrected gate (|ratio - 1| <= 0.05): P_lit %s, P_2w %s\n", (mL / mo >= 0.1 && mL / mo <= 10) ? "met" : "NOT MET", (m2 / mo >= 0.1 && m2 / mo <= 10) ? "met" : "NOT MET", std::fabs(mL / mo - 1) <= 0.05 ? "met" : "NOT MET", std::fabs(m2 / mo - 1) <= 0.05 ? "met" : "NOT MET");
    auto ols = [&](const std::vector<double>& x, const std::vector<double>& y, double& a, double& s, double& r) { double mx = meanv(x), my = meanv(y), sxy = 0, sxx = 0, syy = 0; for (size_t i = 0; i < x.size(); ++i) { sxy += (x[i] - mx) * (y[i] - my); sxx += (x[i] - mx) * (x[i] - mx); syy += (y[i] - my) * (y[i] - my); } s = sxy / sxx; a = my - s * mx; r = sxy / std::sqrt(sxx * syy); };
    { double a, s, r; ols(p2, obs, a, s, r); std::printf("CHANGE-BASED, obs on P_2w: slope %.5f, correlation %.6f, offset %.1f Hz\n", s, r, a); }
    { double a, s, r; ols(pL, obs, a, s, r); std::printf("CHANGE-BASED, obs on P_lit: slope %.5f, correlation %.6f, offset %.1f Hz\n", s, r, a); }
    { double mn = 1e30, mx = -1e30; for (double x : fp) { mn = std::min(mn, x); mx = std::max(mx, x); } std::printf("C5 (reported separately; K = %.2f m frozen, not fitted): Delta f = 2F d(delay)/dt over the window: mean %.4f Hz, range %.4f to %.4f Hz\n", KSUN, meanv(fp), mn, mx); }
    std::printf("\nC6: no gamma, no Bertotti residual used. Status: VERIFICATION / COMPUTED; no SDT survival or exclusion claimed.\n");
    return 0;
}
