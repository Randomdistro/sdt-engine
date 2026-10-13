// GOM40a blank-slate run 1 (2026-10-11): the GOM37 run-1 reduction with K as a run-time argument. Registration: GOM40a_RESET_ASSESSMENT_2026-10-11.md sections 0-2.
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
static double KSUN = 1476.35;   // metres; run-time argument (GOM40a)
static const double CKM = 299792.458, AUKM = 149597870.7, RSUNKM = 695700.0, C = 299792458.0, FKA = 32.028e9, FREF = 2116648992.0;
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

int main(int argc, char** argv) {
    if (argc > 1) KSUN = std::atof(argv[1]);
    std::printf("GOM40a run: fixed K = %.3f m (GOM37 run-1 reduction, K a run-time argument)\n", KSUN);
    std::printf("GOM37 blank-slate run 1 (registered in GOM37_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    int fails = 0; std::vector<Rec> all; std::map<int, std::vector<Rec>> byDay;
    std::printf("INVENTORY (K252, type 12, valid, receive and transmit station 25)\n");
    for (int d = 157; d <= 160; ++d) { std::vector<Rec> v; int rl = 0, ra = 0; bool mono = true; if (!loadDay(d, v, rl, ra, mono)) { std::printf("day %d: file missing\n", d); ++fails; continue; }
        std::set<double> refs; std::set<int> bands; for (auto& x : v) { refs.insert(x.ref); bands.insert(x.dl * 100 + x.ul * 10 + x.ex); } double span = v.empty() ? 0 : v.back().t - v.front().t;
        std::printf("  day %d: label rows %d, rows read %d (%s), selected %zu records, time span %.0f s, distinct reference frequencies %zu (first %.3f Hz), band codes (dl*100+ul*10+ex):", d, rl, ra, rl == ra ? "V2 ok" : "V2 MISMATCH", v.size(), span, refs.size(), refs.empty() ? 0.0 : *refs.begin()); for (int bcode : bands) std::printf(" %d", bcode); std::printf(" ; increasing time tags: %s\n", mono ? "yes (V3 ok)" : "NO"); if (rl != ra || !mono) ++fails; byDay[d] = v; for (auto& x : v) all.push_back(x); }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; }
    Tab t5 = readTab(RAW + "jpl_horizons_cassini_dss25_rr_2002_157.csv"), t15 = readTab(RAW + "jpl_horizons_cassini_dss25_rr_2002_157_160.csv"); Vec E = readVec(RAW + "jpl_horizons_earth_heliocentric_2002_157_160.csv"), Cs = readVec(RAW + "jpl_horizons_cassini_heliocentric_2002_157_160.csv");
    // V4: cubic vs linear, 15-min table at 5-min epochs of day 157
    { double wl = 0, wc = 0; for (size_t i = 0; i < t5.t.size(); ++i) { wl = std::max(wl, std::fabs(interpL(t15.t, t15.dd, t5.t[i]) / t5.dd[i] - 1)); wc = std::max(wc, std::fabs(interpC(t15.t, t15.dd, t5.t[i]) / t5.dd[i] - 1)); } bool ok = wc < 1e-7; std::printf("[V4] 15-min table at the 5-min epochs of day 157: linear interpolation worst relative %.2e (about %.1f Hz in the observable), cubic worst %.2e (about %.4f Hz) -> %s\n", wl, wl * 12.0 * 213700.0, wc, wc * 12.0 * 213700.0, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { G g{100.0 * RSUNKM, AUKM, 7.0 * AUKM, 0}; double dt = delayf(g), an = (2.0 * KSUN / C) * std::log(4.0 * AUKM * 7.0 * AUKM / (100.0 * RSUNKM * 100.0 * RSUNKM)); bool ok = std::fabs(dt / an - 1) < 1e-12; std::printf("[V5] delay formula against its closed form: %s\n", ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // predictors
    auto rdot2w = [&](double t, const Tab& T, bool cubic) { auto I = [&](const std::vector<double>& y, double tt) { return cubic ? interpC(T.t, y, tt) : interpL(T.t, y, tt); }; double rx = I(T.dd, t), rt = 2.0 * I(T.delta, t) * AUKM / CKM; return 0.5 * (rx + I(T.dd, t - rt)); };
    // V1: day 157 with the 5-minute table, global offset: sd 2.639
    { auto& v = byDay[157]; std::vector<double> r; double m = 0; for (auto& x : v) { double f = 2.0 / CKM * FKA * rdot2w(x.t, t5.t.size() ? t15 : t15, false); (void)f; } // placeholder to keep structure; actual V1 below
      std::vector<double> rr; for (auto& x : v) { double rx = interpL(t5.t, t5.dd, x.t), rt = 2.0 * interpL(t5.t, t5.delta, x.t) * AUKM / CKM, r2w = 0.5 * (rx + interpL(t15.t, t15.dd, x.t - rt)); rr.push_back(x.obs - 2.0 / CKM * FKA * r2w); } m = meanv(rr); for (double& a : rr) a -= m; double s = sdv(rr); bool ok = v.size() == 7447 && std::fabs(s - 2.639) < 0.01; std::printf("[V1] day 157 reproduced: %zu records, residual sd %.3f Hz (GOM_DAT8 2.639) -> %s\n\n", v.size(), s, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    // per record quantities with the 15-min cubic tables
    struct Q { double fB, fA, fp, dd, b, sep; }; std::map<int, std::vector<Q>> qs;
    for (int d = 157; d <= 160; ++d) for (auto& x : byDay[d]) { Q q; double r2w = rdot2w(x.t, t15, true); q.fB = 2.0 / CKM * FKA * r2w; double rx = interpC(t15.t, t15.dd, x.t); q.fA = -2.0 * rx / CKM * FREF; G g = geom(E, Cs, x.t), gp = geom(E, Cs, x.t + 150.0), gm = geom(E, Cs, x.t - 150.0); q.dd = (delayf(gp) - delayf(gm)) / 300.0; q.fp = 2.0 * FKA * q.dd; q.b = g.b / RSUNKM; q.sep = g.sep; qs[d].push_back(q); }
    // day 157 with cubic 15-min table (effect of the coarser table)
    { auto& v = byDay[157]; std::vector<double> rr; for (size_t i = 0; i < v.size(); ++i) rr.push_back(v[i].obs - qs[157][i].fB); double m = meanv(rr); for (double& a : rr) a -= m; std::printf("day 157 residual sd with the 15-min cubic table and a global offset: %.3f Hz (5-min linear: 2.639)\n\n", sdv(rr)); }
    // M1 / M2
    double c0 = 0; { auto& v = byDay[157]; for (size_t i = 0; i < v.size(); ++i) c0 += v[i].obs - qs[157][i].fB; c0 /= v.size(); }
    std::printf("OFFSET MODELS. M1: C0 = %.3f Hz (day 157 mean). Per day: records ; elongation ; b [R_sun] ; Delta_f_pred daily mean [Hz] ; M1 residual mean, sd, within-day drift [Hz/h] ; M2 residual sd [Hz]\n", c0);
    std::map<int, double> mM1, fpMean, sdWithin, hours; for (int d = 157; d <= 160; ++d) { auto& v = byDay[d]; std::vector<double> r1, r2, t, fp; for (size_t i = 0; i < v.size(); ++i) { r1.push_back(v[i].obs - qs[d][i].fB - c0); t.push_back(v[i].t); fp.push_back(qs[d][i].fp); } double m1 = meanv(r1); for (size_t i = 0; i < r1.size(); ++i) r2.push_back(r1[i] - m1);
        std::set<long> hb; for (double tt : t) hb.insert((long)(tt / 3600.0)); mM1[d] = m1; fpMean[d] = meanv(fp); sdWithin[d] = sdv(r2); hours[d] = (double)hb.size();
        std::printf("  day %d: %6zu ; %.3f to %.3f deg ; %.2f to %.2f ; %+.4f ; M1 mean %+.3f, sd %.3f (incl. day offset), drift %+.3f ; M2 sd %.3f ; coverage %.0f hourly bins\n", d, v.size(), qs[d].front().sep, qs[d].back().sep, qs[d].front().b, qs[d].back().b, fpMean[d], m1, sdv(r1), slope(t, r1) * 3600.0, sdv(r2), hours[d]); }
    // day-to-day comparison
    std::printf("\nDAY-TO-DAY: M1 daily mean residual minus day 157 against the predicted change of the daily mean Delta_f_pred minus day 157\n"); bool sens = true; double maxPred = 0;
    for (int d = 158; d <= 160; ++d) { double dm = mM1[d] - mM1[157], dp = fpMean[d] - fpMean[157], se = sdWithin[d] / std::sqrt(hours[d]), se0 = sdWithin[157] / std::sqrt(hours[157]), sc = std::sqrt(se * se + se0 * se0); maxPred = std::max(maxPred, std::fabs(dp)); if (std::fabs(dp) <= 3 * sc) sens = false;
        std::printf("  day %d: measured %+9.3f Hz ; predicted %+.4f Hz ; scale sqrt(se^2 + se157^2) = %.3f Hz (se = within-day sd / sqrt(hours)) ; predicted/scale = %.3f\n", d, dm, dp, sc, std::fabs(dp) / sc); }
    // Procedure A' (prompt literal) and pooled statistics on the test days
    std::vector<double> ratio; for (size_t i = 0; i < byDay[157].size(); ++i) ratio.push_back(byDay[157][i].obs / qs[157][i].fA); double sA = med(ratio); std::vector<double> t157, r157; for (size_t i = 0; i < byDay[157].size(); ++i) { t157.push_back(byDay[157][i].t); r157.push_back(byDay[157][i].obs - sA * qs[157][i].fA); }
    double mt = meanv(t157), my = meanv(r157), beta = slope(t157, r157), alpha = my - beta * mt; std::vector<double> tT, rA, dd, fpT, rM1, rM2, rM1d; double sumAbs = 0; std::vector<double> absF;
    for (int d = 158; d <= 160; ++d) { auto& v = byDay[d]; std::vector<double> t, r1; for (size_t i = 0; i < v.size(); ++i) { tT.push_back(v[i].t); rA.push_back(v[i].obs - sA * qs[d][i].fA - (alpha + beta * v[i].t)); dd.push_back(qs[d][i].dd); fpT.push_back(qs[d][i].fp); absF.push_back(std::fabs(qs[d][i].fp)); double r = v[i].obs - qs[d][i].fB - c0; rM1.push_back(r); t.push_back(v[i].t); r1.push_back(r); } double m1 = meanv(r1); for (double a : r1) rM2.push_back(a - m1);
        // per-day linear detrend of M1 residual for the detrended correlation
        double sl = slope(t, r1), mtd = meanv(t); for (size_t i = 0; i < r1.size(); ++i) rM1d.push_back(r1[i] - m1 - sl * (t[i] - mtd)); }
    (void)sumAbs; std::printf("\nPROCEDURE A' (prompt literal): s = %.5f (median obs/f_A, day 157), linear detrend on day 157 alpha = %.4e Hz, beta = %.4e Hz/s ; test residual r_perp (days 158-160): median %.3f, sd %.3f Hz\n", sA, alpha, beta, med(rA), sdv(rA));
    double cA = corr(rA, dd), cT = corr(rA, tT), amp = sdv(rA) / med(absF); std::printf("  pooled |corr(r_perp, d(delay)/dt)| = %.4f ; |corr(r_perp, time)| = %.4f ; amplitude ratio stdev(r_perp)/median|F d(delay)/dt| = %.3e\n", std::fabs(cA), std::fabs(cT), amp);
    const char* label = (amp >= 100) ? "UNADJUDICATED (amplitude ratio >= 100)" : (std::fabs(cT) >= std::fabs(cA) - 0.05 ? "UNADJUDICATED (delete-test: confounded with time)" : (std::fabs(cA) >= 0.5 ? "SOLAR_K_RESIDUAL_SIGNAL" : (std::fabs(cA) < 0.2 ? "NO_SOLAR_K_RESIDUAL_SIGNAL" : "UNADJUDICATED")));
    std::printf("  prompt's C4-C7 outcome: %s\n", label);
    std::printf("\nAMENDED (M1 and M2, pooled test days): corr(r_M1, d(delay)/dt) %+.4f ; corr(r_M1, time) %+.4f ; corr(r_M2, d(delay)/dt) %+.4f ; corr(r_M1 per-day detrended, d(delay)/dt) %+.4f ; sd r_M1 %.3f, sd r_M2 %.3f ; amplitude ratios sd/median|F d(delay)/dt|: M1 %.3e, M2 %.3e\n", corr(rM1, dd), corr(rM1, tT), corr(rM2, dd), corr(rM1d, dd), sdv(rM1), sdv(rM2), sdv(rM1) / med(absF), sdv(rM2) / med(absF));
    std::printf("SENSITIVITY GATE (every predicted day-to-day change exceeds 3 x the scale): %s (largest predicted change %.4f Hz)\n", sens ? "met" : "NOT MET", maxPred);
    std::printf("AMENDED OUTCOME: %s\n", sens ? "decided by the day-to-day comparison" : "UNADJUDICATED_BY_SENSITIVITY");
    return 0;
}
