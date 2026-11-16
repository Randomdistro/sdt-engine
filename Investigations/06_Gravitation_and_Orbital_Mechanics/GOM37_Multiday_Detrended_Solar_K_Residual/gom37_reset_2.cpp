// GOM37 run 2 (2026-10-11): Addendum A (model M3, offset linear in the reference frequency). Registration: GOM37_RESET_ASSESSMENT_2026-10-11.md section 5 (written before this file existed).
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
    std::printf("GOM37 run 2, Addendum A (registered in GOM37_RESET_ASSESSMENT_2026-10-11.md section 5)\n=======================================================================\n\n");
    std::map<int, std::vector<Rec>> byDay; for (int d = 157; d <= 160; ++d) { std::vector<Rec> v; int rl = 0, ra = 0; bool mono = true; if (!loadDay(d, v, rl, ra, mono) || rl != ra || !mono) { std::printf("load failure day %d\n", d); return 1; } byDay[d] = v; }
    Tab t15 = readTab(RAW + "jpl_horizons_cassini_dss25_rr_2002_157_160.csv"); Vec E = readVec(RAW + "jpl_horizons_earth_heliocentric_2002_157_160.csv"), Cs = readVec(RAW + "jpl_horizons_cassini_heliocentric_2002_157_160.csv");
    auto rdot2w = [&](double t) { double rx = interpC(t15.t, t15.dd, t), rt = 2.0 * interpC(t15.t, t15.delta, t) * AUKM / CKM; return 0.5 * (rx + interpC(t15.t, t15.dd, t - rt)); };
    std::map<int, std::vector<double>> fB, fp; for (int d = 157; d <= 160; ++d) for (auto& x : byDay[d]) { fB[d].push_back(2.0 / CKM * FKA * rdot2w(x.t)); G gp = geom(E, Cs, x.t + 150.0), gm = geom(E, Cs, x.t - 150.0); fp[d].push_back(2.0 * FKA * (delayf(gp) - delayf(gm)) / 300.0); }
    auto dayMean = [&](int d) { double s = 0; for (size_t i = 0; i < byDay[d].size(); ++i) s += byDay[d][i].obs - fB[d][i]; return s / byDay[d].size(); };
    const double ref157 = byDay[157][0].ref, ref160 = byDay[160][0].ref, c157 = dayMean(157), c160 = dayMean(160), kappa = (c160 - c157) / (ref160 - ref157);
    std::printf("C0_157 = %.4f Hz (ref %.3f) ; C0_160 = %.4f Hz (ref %.3f) ; kappa = (C0_160 - C0_157)/(ref_160 - ref_157) = %.6f Hz per Hz\n\n", c157, ref157, c160, ref160, kappa);
    std::printf("M3 residual r3 = obs - f_B - C0_157 - kappa (ref - ref_157): per day and per reference-value segment\n"); bool pass = true; std::map<int, double> mean3, se3, fpm;
    for (int d = 157; d <= 160; ++d) { auto& v = byDay[d]; std::vector<double> r, t, fpv; std::map<double, std::vector<double>> seg; for (size_t i = 0; i < v.size(); ++i) { double x = v[i].obs - fB[d][i] - c157 - kappa * (v[i].ref - ref157); r.push_back(x); t.push_back(v[i].t); fpv.push_back(fp[d][i]); seg[v[i].ref].push_back(x); }
        std::set<long> hb; for (double tt : t) hb.insert((long)(tt / 3600.0)); mean3[d] = meanv(r); fpm[d] = meanv(fpv); se3[d] = sdv(r) / std::sqrt((double)hb.size());
        std::printf("  day %d: records %zu ; r3 mean %+.4f Hz ; sd %.4f Hz ; drift %+.3f Hz/h ; reference values %zu\n", d, v.size(), mean3[d], sdv(r), slope(t, r) * 3600.0, seg.size());
        if (d == 158 || d == 159) { for (auto& kv : seg) std::printf("      ref %.3f Hz (d from ref157 %+.0f) : %6zu records, mean %+.3f, sd %.3f\n", kv.first, kv.first - ref157, kv.second.size(), meanv(kv.second), kv.second.size() > 1 ? sdv(kv.second) : 0.0); bool ok = std::fabs(mean3[d]) < 3.0 && sdv(r) < 5.0; if (!ok) pass = false; std::printf("      criterion (|mean| < 3 Hz and sd < 5 Hz): %s\n", ok ? "met" : "NOT MET"); } }
    std::printf("\nM3 (offset linear in the reference frequency, out-of-sample on days 158 and 159): %s\n", pass ? "SUPPORTED" : "NOT SUPPORTED");
    if (pass) { std::printf("\nSECOND STAGE: daily mean M3 residual against the predicted solar Doppler change relative to day 157\n"); bool sens = true; for (int d : {158, 159}) { double pred = fpm[d] - fpm[157], meas = mean3[d] - mean3[157], sc = std::sqrt(se3[d] * se3[d] + se3[157] * se3[157]); if (std::fabs(pred) <= 3 * sc) sens = false; std::printf("  day %d: measured %+.4f Hz ; predicted %+.4f Hz ; scale %.4f Hz (within-day sd/sqrt(hours), two days) ; predicted/scale = %.3f\n", d, meas, pred, sc, std::fabs(pred) / sc); }
        std::printf("  sensitivity (each predicted change > 3 x scale): %s -> %s\n", sens ? "met" : "NOT MET", sens ? "decided by the comparison" : "UNADJUDICATED_BY_SENSITIVITY"); }
    return 0;
}
