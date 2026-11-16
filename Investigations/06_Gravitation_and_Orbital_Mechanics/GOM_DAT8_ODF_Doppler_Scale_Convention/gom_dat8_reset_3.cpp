// GOM_DAT8 run 3 (2026-10-10), POST-SEEN DESCRIPTIVE (no criterion): residual of the identified model obs = +(2/c) F rdot + C0 with F = 32.028e9 Hz, after the Phase B result was seen. GOM_DAT8 run 2 was the registered Phase B.
// (header of run 2 follows for the helpers)  Registration: GOM_DAT8_RESET_ASSESSMENT_2026-10-10.md sections 2 (frozen prompt hypotheses) and 3 (native change-based addendum, registered before this file existed).
//  Selection: type 12, valid, rx 25, tx 25. f_ref = the record's reference frequency (Items 18-19). f0 = -2 (rdot/c) f_ref (receive-time rdot, 5-min table, linear interpolation).
//  Frozen: H0..H7 as scale factors s on f0; A = median|obs-f|/median|obs|; B = median|f|/median|obs|; C3 met iff A < 0.15 and |B-1| < 0.15. Outcomes PASS(Hi) / NONUNIQUE / UNRESOLVED.
//  Native: change-based. Predictors P_rx and P_2w (rdot_2w(t) = 0.5 [deldot(t) + deldot(t - RTLT)], RTLT = 2 delta AU / c, 15-min table for the up-leg). Candidates F in {2116648992, 8.4e9, 32.028e9, 34.316e9} Hz, both signs.
//  Delta over a window = mean(last 100 records) - mean(first 100) within each third; whole span = mean(last 300) - mean(first 300). Native pass for (predictor, F, sign) iff |R - 1| < 0.05 in all three thirds and the whole span, R = dObs / dF.
//  Validations: VB1 the 5-min and 15-min tables agree at their common epochs (11 epochs, 20:30..23:00 every 15 min; the registration text said 33, an arithmetic slip, corrected here before the run) to 1e-5; VB2 RTLT in 8300..8400 s; VB3 linear interpolation of the 15-min table reproduces the 5-min deldot to 1e-4.
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
static const double CKM = 299792.458, AUKM = 149597870.7;
static uint32_t be32(const uint8_t* p) { return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3]; }
static uint64_t bits(const uint8_t* p, int start1, int n) { uint64_t v = 0; for (int i = 0; i < n; ++i) { int b = start1 - 1 + i; v = (v << 1) | ((p[b / 8] >> (7 - b % 8)) & 1); } return v; }
static long long days_from_civil(int y, int m, int d) { y -= m <= 2; long long era = (y >= 0 ? y : y - 399) / 400; unsigned yoe = unsigned(y - era * 400); unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; return era * 146097 + (long long)doe - 719468; }
static double sec1950(int y, int m, int d, int hh, int mm) { return double(days_from_civil(y, m, d) + 7305) * 86400.0 + hh * 3600.0 + mm * 60.0; }
struct Tab { std::vector<double> t, delta, dd; };
static Tab readTab(const char* path) {
    Tab T; std::ifstream h(path); std::string ln; bool in = false; const char* mon[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    while (std::getline(h, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue;
        std::vector<std::string> f; size_t p = 0; while (true) { size_t q = ln.find(',', p); if (q == std::string::npos) break; f.push_back(ln.substr(p, q - p)); p = q + 1; } if (f.size() < 5) continue;
        std::string d = f[0]; size_t s = d.find_first_not_of(' '); d = d.substr(s); int y = std::stoi(d.substr(0, 4)); std::string mn = d.substr(5, 3); int m = 0; for (int i = 0; i < 12; ++i) if (mn == mon[i]) m = i + 1; int dy = std::stoi(d.substr(9, 2)), hh = std::stoi(d.substr(12, 2)), mi = std::stoi(d.substr(15, 2));
        T.t.push_back(sec1950(y, m, dy, hh, mi)); T.delta.push_back(std::stod(f[3])); T.dd.push_back(std::stod(f[4])); }
    return T;
}
static double interp(const std::vector<double>& x, const std::vector<double>& y, double t) { size_t i = std::upper_bound(x.begin(), x.end(), t) - x.begin(); if (i == 0) i = 1; if (i >= x.size()) i = x.size() - 1; double w = (t - x[i - 1]) / (x[i] - x[i - 1]); return y[i - 1] + w * (y[i] - y[i - 1]); }
static double med(std::vector<double> v) { std::sort(v.begin(), v.end()); size_t n = v.size(); return n % 2 ? v[n / 2] : 0.5 * (v[n / 2 - 1] + v[n / 2]); }
static double pct(std::vector<double> v, double p) { std::sort(v.begin(), v.end()); return v[size_t(p * (v.size() - 1))]; }
static double mean(const std::vector<double>& v, size_t a, size_t b) { double s = 0; for (size_t i = a; i < b; ++i) s += v[i]; return s / double(b - a); }
static double corr(const std::vector<double>& a, const std::vector<double>& b) { size_t n = a.size(); double ma = 0, mb = 0; for (size_t i = 0; i < n; ++i) { ma += a[i]; mb += b[i]; } ma /= n; mb /= n; double sab = 0, saa = 0, sbb = 0; for (size_t i = 0; i < n; ++i) { sab += (a[i] - ma) * (b[i] - mb); saa += (a[i] - ma) * (a[i] - ma); sbb += (b[i] - mb) * (b[i] - mb); } return sab / std::sqrt(saa * sbb); }

int main() {
    std::printf("GOM_DAT8 run 3: POST-SEEN descriptive residuals of obs = (2/c) F rdot + C0, F = 32.028e9 Hz (Phase B identified F; no criterion)\n====================================================================\n\n");
    std::ifstream f(ODF, std::ios::binary); std::vector<uint8_t> buf((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    std::vector<double> T, OBS;
    for (int r = 6; r <= 7452; ++r) { const uint8_t* p = buf.data() + 36 * (r - 1); const uint8_t* q = p + 16; int type = int(bits(q, 20, 6)), rx = int(bits(q, 4, 7)), tx = int(bits(q, 11, 7)), valid = int(bits(q, 32, 1)); if (type != 12 || valid || rx != 25 || tx != 25) continue;
        T.push_back(double(be32(p)) + double(bits(p + 4, 1, 10)) / 1000.0); OBS.push_back(double(int32_t(be32(p + 8))) + double(int32_t(be32(p + 12))) / 1e9); }
    const size_t n = T.size(); Tab a = readTab(H5), b = readTab(H15); const double F = 32.028e9;
    for (int pr = 0; pr < 2; ++pr) {
        std::vector<double> res(n); for (size_t i = 0; i < n; ++i) { double rrx = interp(a.t, a.dd, T[i]); double rt = 2.0 * interp(a.t, a.delta, T[i]) * AUKM / CKM; double rd = pr == 0 ? rrx : 0.5 * (rrx + interp(b.t, b.dd, T[i] - rt)); res[i] = OBS[i] - (2.0 / CKM) * F * rd; }
        double m = mean(res, 0, n), sd = 0, mn = 1e99, mx = -1e99; for (double v : res) { sd += (v - m) * (v - m); mn = std::min(mn, v); mx = std::max(mx, v); } sd = std::sqrt(sd / (n - 1));
        double mt = 0; for (double t : T) mt += t; mt /= n; double sxy = 0, sxx = 0; for (size_t i = 0; i < n; ++i) { sxy += (T[i] - mt) * (res[i] - m); sxx += (T[i] - mt) * (T[i] - mt); } double slope = sxy / sxx; double sd2 = 0; for (size_t i = 0; i < n; ++i) { double d = res[i] - m - slope * (T[i] - mt); sd2 += d * d; } sd2 = std::sqrt(sd2 / (n - 2));
        std::printf("predictor %s: residual mean C0 = %.3f Hz ; sd %.3f Hz ; min %.3f ; max %.3f ; linear trend %+.4f Hz per hour ; sd after trend %.3f Hz\n", pr == 0 ? "P_rx" : "P_2w", m, sd, mn, mx, slope * 3600.0, sd2);
        std::printf("  block means (10 blocks of ~745 records), Hz about C0:"); for (int k = 0; k < 10; ++k) std::printf(" %+.2f", mean(res, k * n / 10, (k + 1) * n / 10) - m); std::printf("\n");
        std::printf("  obs range %.3f to %.3f Hz ; (2/c)F rdot range %.3f to %.3f Hz\n\n", *std::min_element(OBS.begin(), OBS.end()), *std::max_element(OBS.begin(), OBS.end()), OBS.front() - res.front(), OBS.back() - res.back());
    }
    return 0;
}
