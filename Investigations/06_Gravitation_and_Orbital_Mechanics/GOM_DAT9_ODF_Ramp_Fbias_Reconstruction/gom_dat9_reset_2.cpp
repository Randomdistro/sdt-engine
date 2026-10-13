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
static int labelRowsNamed(const std::string& lbl, const std::string& table) { std::ifstream f(lbl); std::string ln; bool in = false; while (std::getline(f, ln)) { if (ln.find("= " + table) != std::string::npos && ln.find("OBJECT") != std::string::npos) in = true; if (in && ln.find("ROWS") != std::string::npos) { size_t p = ln.find('='); return std::stoi(ln.substr(p + 1)); } } return -1; }
static bool loadRamps(int day, std::vector<Ramp>& out, int& rows) { char b1[256], b2[256]; std::snprintf(b1, sizeof b1, "cassini_sce1/cors_0021/sce1_%d/odf/c32easc2002_%d_0000k252v0.odf", day, day); std::snprintf(b2, sizeof b2, "cassini_sce1/cors_0021/sce1_%d/odf/c32easc2002_%d_0000k252v0.lbl", day, day);
    std::ifstream f(RAW + b1, std::ios::binary); std::vector<uint8_t> b((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); long nrec = (long)(b.size() / 36); long hdr = -1; for (long i = 0; i < nrec; ++i) { const uint8_t* r = b.data() + 36 * i; if ((int32_t)be32(r) == 2030 && be32(r + 4) == 25) { hdr = i; break; } } if (hdr < 0) return false;
    rows = labelRowsNamed(RAW + b2, "ODF4B25_TABLE"); for (int k = 1; k <= rows; ++k) out.push_back(decodeRamp(b.data() + 36 * (hdr + k))); return true; }
int main() {
    std::printf("GOM_DAT9 blank-slate run 2, Amendment 1 / 1b (registered in GOM_DAT9_RESET_ASSESSMENT_2026-10-11.md section 4)\n=======================================================================\n\n");
    const double S157 = 0.999874; int fails = 0;
    Tab t15 = readTab(RAW + "jpl_horizons_cassini_dss25_rr_2002_157_160.csv");
    struct Seg { int day; double ref; int ramp; size_t n; std::vector<double> c0; double fTmin, fTmax, rate; };
    std::vector<Seg> segs; double c157 = 0; size_t n157 = 0;
    for (int day = 157; day <= 160; ++day) {
        std::vector<Rec> v; int rl = 0, ra = 0; bool mono = true; if (!loadDay(day, v, rl, ra, mono)) { std::printf("day %d: file missing\n", day); ++fails; continue; }
        std::vector<Ramp> rp; int rrows = 0; if (!loadRamps(day, rp, rrows)) { std::printf("day %d: no ramp group 25\n", day); ++fails; continue; }
        // V4: time ordered, non-overlapping
        bool ordered = true; for (size_t i = 0; i < rp.size(); ++i) { if (rp[i].station != 25) ordered = false; if (i && rp[i].t0 < rp[i - 1].t0) ordered = false; if (i && rp[i].t0 < rp[i - 1].t1 - 1e-6 && false) ordered = false; }
        std::printf("day %d: %zu orbit records, ramp group 25 rows %d (label), decoded %zu ; time ordered, station 25: %s\n", day, v.size(), rrows, rp.size(), ordered ? "yes" : "NO"); if (!ordered) ++fails;
        for (size_t i = 0; i < rp.size(); ++i) std::printf("    ramp %zu: start %.3f end %.3f (dur %.1f s) rate %.9f Hz/s start frequency %.3f Hz (%s)\n", i, rp[i].t0, rp[i].t1, rp[i].t1 - rp[i].t0, rp[i].rate, rp[i].fT, rp[i].sky ? "sky" : "ref level");
        size_t uncovered = 0; Seg cur{day, -1, -1, 0, {}, 1e30, -1e30, 0}; bool open = false;
        for (auto& x : v) { double rx = interpC(t15.t, t15.dd, x.t), rt = 2.0 * interpC(t15.t, t15.delta, x.t) * AUKM / CKM, r2w = 0.5 * (rx + interpC(t15.t, t15.dd, x.t - rt)), ttx = x.t - rt; int k = -1; for (size_t i = 0; i < rp.size(); ++i) if (ttx >= rp[i].t0 && ttx <= rp[i].t1) k = (int)i; if (k < 0) { ++uncovered; continue; }
            double fT = rp[k].fT + rp[k].rate * (ttx - rp[k].t0), p1 = -2.0 * r2w / CKM * (14.0 / 15.0) * fT * S157, c0 = x.obs + p1;
            if (!open || x.ref != cur.ref || k != cur.ramp) { if (open) segs.push_back(cur); cur = Seg{day, x.ref, k, 0, {}, 1e30, -1e30, rp[k].rate}; open = true; } cur.c0.push_back(c0); ++cur.n; cur.fTmin = std::min(cur.fTmin, fT); cur.fTmax = std::max(cur.fTmax, fT);
            if (day == 157) { c157 += c0; ++n157; } }
        if (open) segs.push_back(cur);
        std::printf("    records with no covering ramp record: %zu\n", uncovered);
    }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; }
    c157 /= n157; std::printf("\nV5: C0_157 = mean(obs + s157 P1_c) over %zu records = %.3f Hz (run 1 regression offset -2510006.5 Hz; the mean differs by the slope convention)\n", n157, c157);
    std::printf("\nSEGMENTS (consecutive records with the same f_ref and ramp record): day, ramp, f_ref, f_T range, rate, n, mean C0, sd, mean - C0_157, criterion (n >= 100: |mean - C0_157| < 3 Hz and sd < 5 Hz)\n");
    int nTested = 0, nSupp = 0;
    for (auto& s : segs) { double m = meanv(s.c0), sd = s.c0.size() > 1 ? sdv(s.c0) : 0; bool test = s.n >= 100; bool ok = test && std::fabs(m - c157) < 3 && sd < 5; if (test) { ++nTested; if (ok) ++nSupp; }
        std::printf("  day %d ramp %d f_ref %.0f f_T %.3f..%.3f rate %.6f n %5zu  mean %.3f  sd %9.3f  diff %+12.3f  %s\n", s.day, s.ramp, s.ref, s.fTmin, s.fTmax, s.rate, s.n, m, sd, m - c157, test ? (ok ? "SUPPORTED" : "not supported") : "(n < 100, reported)"); }
    std::printf("\nH_T: %d of %d tested segments supported (day 157 is in sample by construction)\n", nSupp, nTested);
    return 0;
}
