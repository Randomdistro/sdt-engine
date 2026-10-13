// GOM_DAT9 blank-slate run 1 (2026-10-11). Registration: GOM_DAT9_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
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

struct Ramp { double t0, t1, rate, fT; int station; bool sky; };
static Ramp decodeRamp(const uint8_t* r) { Ramp R; R.t0 = double(be32(r)) + double(be32(r + 4)) * 1e-9; R.rate = double(int32_t(be32(r + 8))) + double(int32_t(be32(r + 12))) * 1e-9; uint32_t w5 = be32(r + 16); uint32_t ghz = w5 >> 10; R.station = int(w5 & 0x3ff); R.fT = double(ghz) * 1e9 + double(be32(r + 20)) + double(be32(r + 24)) * 1e-9; R.t1 = double(be32(r + 28)) + double(be32(r + 32)) * 1e-9; R.sky = ghz != 0; return R; }
int main() {
    std::printf("GOM_DAT9 blank-slate run 1 (registered in GOM_DAT9_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    int fails = 0;
    // V3: decode on a synthetic record
    { uint8_t r[36] = {0}; auto put = [&](int w, uint32_t v) { r[4 * w] = v >> 24; r[4 * w + 1] = v >> 16; r[4 * w + 2] = v >> 8; r[4 * w + 3] = v; }; put(0, 1654539733u); put(1, 500000000u); put(2, (uint32_t)(int32_t)-3); put(3, (uint32_t)(int32_t)-250000000); put(4, (34u << 10) | 25u); put(5, 317852320u); put(6, 250000000u); put(7, 1654570323u); put(8, 0);
      Ramp R = decodeRamp(r); bool ok = std::fabs(R.t0 - 1654539733.5) < 1e-6 && std::fabs(R.rate - (-3.25)) < 1e-9 && R.station == 25 && std::fabs(R.fT - 34317852320.25) < 1e-3 && R.sky; std::printf("[V3] synthetic ramp record round trip (t0 %.3f, rate %.3f Hz/s, station %d, f_T %.2f Hz, sky %d) -> %s\n", R.t0, R.rate, R.station, R.fT, (int)R.sky, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    std::vector<Rec> v; int rl = 0, ra = 0; bool mono = true; if (!loadDay(157, v, rl, ra, mono)) { std::printf("file missing\n"); return 1; }
    Tab t5 = readTab(RAW + "jpl_horizons_cassini_dss25_rr_2002_157.csv"), t15 = readTab(RAW + "jpl_horizons_cassini_dss25_rr_2002_157_160.csv");
    { double wc = 0; for (size_t i = 0; i < t5.t.size(); ++i) wc = std::max(wc, std::fabs(interpC(t15.t, t15.dd, t5.t[i]) / t5.dd[i] - 1)); bool ok = wc < 1e-7; std::printf("[V2] cubic interpolation of the 15-min table at the 5-min epochs: worst relative %.2e -> %s\n", wc, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // locate the ramp group 25
    std::ifstream f(RAW + "cassini_sce1/cors_0021/sce1_157/odf/c32easc2002_157_0000k252v0.odf", std::ios::binary); std::vector<uint8_t> b((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); long nrec = (long)(b.size() / 36); std::vector<Ramp> ramps; long hdr = -1;
    for (long i = 0; i < nrec; ++i) { const uint8_t* r = b.data() + 36 * i; if ((int32_t)be32(r) == 2030 && be32(r + 4) == 25) { hdr = i; break; } }
    if (hdr < 0) { std::printf("[C1] no ramp group header with key 2030 and secondary key 25 -> PENDING_DATA / C1 NOT MET\n"); return 1; }
    for (long i = hdr + 1; i < nrec; ++i) { const uint8_t* r = b.data() + 36 * i; int32_t w0 = (int32_t)be32(r); if (w0 == 2030 || w0 == 105 || w0 == -1 || w0 == 0) break; ramps.push_back(decodeRamp(r)); }
    std::printf("[C1] ramp group 25 header at record %ld ; data records decoded: %zu\n", hdr + 1, ramps.size());
    for (size_t i = 0; i < ramps.size(); ++i) std::printf("  ramp %zu: station %d, start %.3f s, end %.3f s (duration %.1f s), rate %.9f Hz/s, start frequency %.3f Hz (%s)\n", i, ramps[i].station, ramps[i].t0, ramps[i].t1, ramps[i].t1 - ramps[i].t0, ramps[i].rate, ramps[i].fT, ramps[i].sky ? "sky level" : "reference level");
    if (ramps.empty()) { std::printf("C1 NOT MET (no ramp data row)\n"); return 1; }
    const Ramp& R = ramps[0];
    // V1: ramp interval contains every transmit epoch
    std::vector<double> obs, pL, p1a, p1c, ttx; double fTmin = 1e30, fTmax = -1e30; bool cover = true;
    for (auto& x : v) { double rx = interpC(t15.t, t15.dd, x.t), rt = 2.0 * interpC(t15.t, t15.delta, x.t) * AUKM / CKM, r2w = 0.5 * (rx + interpC(t15.t, t15.dd, x.t - rt)); double ttxv = x.t - rt; if (ttxv < R.t0 || ttxv > R.t1) cover = false; double fT = R.fT + R.rate * (ttxv - R.t0); fTmin = std::min(fTmin, fT); fTmax = std::max(fTmax, fT);
        obs.push_back(x.obs); pL.push_back(-2.0 * rx / CKM * x.ref); p1a.push_back(-2.0 * r2w / CKM * (209.0 / 15.0) * x.ref); p1c.push_back(-2.0 * r2w / CKM * (14.0 / 15.0) * fT); ttx.push_back(ttxv); }
    { std::printf("[V1] ramp interval [%.1f, %.1f] contains every transmit epoch (range %.1f to %.1f): %s ; f_T over the window %.3f to %.3f Hz\n", R.t0, R.t1, *std::min_element(ttx.begin(), ttx.end()), *std::max_element(ttx.begin(), ttx.end()), cover ? "yes -> met" : "NO -> NOT MET", fTmin, fTmax); if (!cover) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    double fref = v[0].ref, fTm = 0.5 * (fTmin + fTmax);
    std::printf("C2: f_ref (Items 18-19) = %.3f Hz ; Fbias_a = (209/15) f_ref = %.6e Hz ; Fbias_b = (209/15) f_T = %.6e Hz (dimensionally not a physical Fbias, D2) ; Fbias_c = (14/15) f_T = %.6e Hz (sky level, T1/T2 for Ka transmitters)\n", fref, 209.0 / 15.0 * fref, 209.0 / 15.0 * fTm, 14.0 / 15.0 * fTm);
    auto absv = [](std::vector<double> a) { for (double& x : a) x = std::fabs(x); return a; };
    double mo = med(absv(obs));
    struct P { const char* nm; std::vector<double> f; }; std::vector<P> ps = {{"P0 = -2(rdot_rx/c) f_ref", pL}, {"P1_a = -2(rdot_2w/c) (209/15) f_ref", p1a}, {"P1_c = -2(rdot_2w/c) (14/15) f_T", p1c}};
    // P2 (sky residual) for each Fbias: obs + 2 rdot Fbias / c  == obs - P1 (same sign convention)
    bool anyPass = false;
    std::printf("\nC3/C4 LEVEL (median |obs| = %.1f Hz): predictor ; median |f| ; ratio ; rel_resid(+) ; rel_resid(-) ; gates (+ sign / - sign)\n", mo);
    for (auto& p : ps) { std::vector<double> rp, rm; for (size_t i = 0; i < obs.size(); ++i) { rp.push_back(std::fabs(obs[i] - p.f[i])); rm.push_back(std::fabs(obs[i] + p.f[i])); } double mf = med(absv(p.f)), ratio = mf / mo, rrp = med(rp) / mo, rrm = med(rm) / mo; bool gp = rrp < 0.15 && std::fabs(ratio - 1) < 0.15, gm = rrm < 0.15 && std::fabs(ratio - 1) < 0.15; anyPass = anyPass || gp || gm; std::printf("  %-38s %12.1f  %8.4f  %9.4f  %9.4f  %s / %s\n", p.nm, mf, ratio, rrp, rrm, gp ? "PASS" : "fail", gm ? "PASS" : "fail"); }
    { std::vector<double> r2; for (size_t i = 0; i < obs.size(); ++i) r2.push_back(obs[i] - p1c[i]); std::printf("  P2 sky residual for Fbias_c (obs - P1_c): median %.1f Hz, mean %.1f Hz, sd %.3f Hz\n", med(r2), meanv(r2), sdv(r2)); std::vector<double> r3; for (size_t i = 0; i < obs.size(); ++i) r3.push_back(obs[i] - p1a[i]); std::printf("  P2 sky residual for Fbias_a (obs - P1_a): median %.1f Hz, mean %.1f Hz, sd %.3f Hz\n", med(r3), meanv(r3), sdv(r3)); }
    auto ols = [&](const std::vector<double>& x, const std::vector<double>& y, double& a, double& s, double& r) { double mx = meanv(x), my = meanv(y), sxy = 0, sxx = 0, syy = 0; for (size_t i = 0; i < x.size(); ++i) { sxy += (x[i] - mx) * (y[i] - my); sxx += (x[i] - mx) * (x[i] - mx); syy += (y[i] - my) * (y[i] - my); } s = sxy / sxx; a = my - s * mx; r = sxy / std::sqrt(sxx * syy); };
    std::printf("\nCHANGE-BASED (descriptive; the offset is free): obs on predictor: slope ; correlation ; offset\n"); for (auto& p : ps) { double a, s, r; ols(p.f, obs, a, s, r); std::printf("  %-38s slope %+9.5f  corr %+9.6f  offset %.1f Hz\n", p.nm, s, r, a); }
    { double a, s, r; ols(p1c, obs, a, s, r); std::printf("  effective carrier from the P1_c slope: %.6e Hz against (14/15) f_T = %.6e Hz: ratio %.6f\n", s * 14.0 / 15.0 * fTm, 14.0 / 15.0 * fTm, s); }
    std::printf("\nOutcome: %s\n", anyPass ? "C4 PASS (a level predictor meets the gates)" : "C5 FBIAS_RECON_UNRESOLVED (no level predictor meets rel_resid < 0.15 and |ratio - 1| < 0.15; no scale fitted)");
    std::printf("C6: solar K unused.\n");
    return 0;
}
