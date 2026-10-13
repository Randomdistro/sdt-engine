// GOM_DAT8 blank-slate run 2, Phase B (2026-10-10). Registration: GOM_DAT8_RESET_ASSESSMENT_2026-10-10.md sections 2 (frozen prompt hypotheses) and 3 (native change-based addendum, registered before this file existed).
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
    std::printf("GOM_DAT8 blank-slate run 2, Phase B (registered in GOM_DAT8_RESET_ASSESSMENT_2026-10-10.md sections 2-3)\n==================================================================================\n\n");
    std::ifstream f(ODF, std::ios::binary); std::vector<uint8_t> buf((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    std::vector<double> T, OBS, REF;
    for (int r = 6; r <= 7452; ++r) { const uint8_t* p = buf.data() + 36 * (r - 1); const uint8_t* q = p + 16; int type = int(bits(q, 20, 6)), rx = int(bits(q, 4, 7)), tx = int(bits(q, 11, 7)), valid = int(bits(q, 32, 1)); if (type != 12 || valid || rx != 25 || tx != 25) continue;
        T.push_back(double(be32(p)) + double(bits(p + 4, 1, 10)) / 1000.0); OBS.push_back(double(int32_t(be32(p + 8))) + double(int32_t(be32(p + 12))) / 1e9); REF.push_back((double(bits(q, 51, 22)) * 16777216.0 + double(bits(q, 73, 24))) / 1000.0); }
    const size_t n = T.size(); std::printf("selection: %zu records\n", n);
    Tab a = readTab(H5), b = readTab(H15); std::printf("tables: 5-min %zu rows, 15-min %zu rows\n", a.t.size(), b.t.size());
    int fails = 0;
    // VB1
    { double worst = 0; int cnt = 0; for (size_t i = 0; i < a.t.size(); ++i) { for (size_t j = 0; j < b.t.size(); ++j) if (std::fabs(a.t[i] - b.t[j]) < 1e-6) { worst = std::max(worst, std::fabs(a.dd[i] / b.dd[j] - 1)); ++cnt; } }
      bool ok = cnt == 11 && worst < 1e-5; std::printf("[VB1] common epochs %d ; worst relative difference of deldot %.2e -> %s\n", cnt, worst, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // VB2
    { double lo = 1e9, hi = -1e9; for (size_t i = 0; i < n; ++i) { double rt = 2.0 * interp(a.t, a.delta, T[i]) * AUKM / CKM; lo = std::min(lo, rt); hi = std::max(hi, rt); } bool ok = lo > 8300 && hi < 8400; std::printf("[VB2] RTLT range %.1f to %.1f s -> %s\n", lo, hi, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // VB3
    { double worst = 0; for (size_t i = 0; i < a.t.size(); ++i) worst = std::max(worst, std::fabs(interp(b.t, b.dd, a.t[i]) / a.dd[i] - 1)); bool ok = worst < 1e-4; std::printf("[VB3] 15-min table interpolated at the 5-min epochs: worst relative difference %.2e -> %s\n\n", worst, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("PHASE B VALIDATIONS NOT MET -> G0\n"); return 1; }
    std::printf("PHASE B VALIDATIONS: met\n\n");
    // predictors
    std::vector<double> rrx(n), r2w(n), f0(n); for (size_t i = 0; i < n; ++i) { rrx[i] = interp(a.t, a.dd, T[i]); double rt = 2.0 * interp(a.t, a.delta, T[i]) * AUKM / CKM; r2w[i] = 0.5 * (rrx[i] + interp(b.t, b.dd, T[i] - rt)); f0[i] = -2.0 * rrx[i] / CKM * REF[i]; }
    // ---- frozen Phase B
    const double sH[8] = {1.0, -1.0, -0.5, -1.0 / 3.14159265358979323846, -221.0 / 240.0, -240.0 / 749.0, -2.116e9 / 8.4e9, -8.4e9 / 32.028e9}; const char* nH[8] = {"H0 f=f0", "H1 f=-f0", "H2 f=-f0/2", "H3 f=-f0/pi", "H4 f=-f0*221/240", "H5 f=-f0*240/749", "H6 f=-f0*2.116e9/8.4e9", "H7 f=-f0*8.4e9/32.028e9"};
    std::vector<double> ao(n); for (size_t i = 0; i < n; ++i) ao[i] = std::fabs(OBS[i]); double mo = med(ao); int npass = 0; std::string which;
    std::printf("---- Frozen prompt hypotheses (levels) ----\nmedian |obs| = %.3f Hz ; median |f0| = %.3f Hz\n", mo, med([&] { std::vector<double> v(n); for (size_t i = 0; i < n; ++i) v[i] = std::fabs(f0[i]); return v; }()));
    for (int h = 0; h < 8; ++h) { std::vector<double> d(n), af(n); for (size_t i = 0; i < n; ++i) { double fh = sH[h] * f0[i]; d[i] = std::fabs(OBS[i] - fh); af[i] = std::fabs(fh); } double A = med(d) / mo, B = med(af) / mo; bool ok = A < 0.15 && std::fabs(B - 1) < 0.15; if (ok) { ++npass; which += std::string(nH[h]) + "; "; }
        std::printf("  %-26s scale %+.5f : med|obs-f|/med|obs| = %.4f ; med|f|/med|obs| = %.4f -> C3 %s\n", nH[h], sH[h], A, B, ok ? "MET" : "not met"); }
    std::printf("  outcome: %s\n", npass == 1 ? ("SCALE_CONVENTION_PASS (" + which + ")").c_str() : npass > 1 ? ("SCALE_CONVENTION_NONUNIQUE (" + which + ")").c_str() : "SCALE_CONVENTION_UNRESOLVED");
    { std::vector<double> ratio(n); int sg = 0; for (size_t i = 0; i < n; ++i) { ratio[i] = OBS[i] / f0[i]; if ((OBS[i] > 0) == (f0[i] > 0)) ++sg; }
      std::vector<double> d1o, d1f; for (size_t i = 60; i < n; i += 60) { d1o.push_back(OBS[i] - OBS[i - 60]); d1f.push_back(f0[i] - f0[i - 60]); }
      std::printf("  descriptive: corr(obs, f0) = %.5f ; corr of 60-record differences = %.5f ; fraction with sign(obs) = sign(f0): %.3f ; obs/f0: median %.4f, 10th %.4f, 90th %.4f\n\n", corr(OBS, f0), corr(d1o, d1f), double(sg) / n, med(ratio), pct(ratio, 0.1), pct(ratio, 0.9)); }
    // ---- native change-based
    std::printf("---- Native change-based reading ----\n");
    struct W { const char* nm; size_t a0, a1, b0, b1; } wins[4] = {{"third 1", 0, 100, n / 3 - 100, n / 3}, {"third 2", n / 3, n / 3 + 100, 2 * n / 3 - 100, 2 * n / 3}, {"third 3", 2 * n / 3, 2 * n / 3 + 100, n - 100, n}, {"whole span", 0, 300, n - 300, n}};
    const double Fc[4] = {2116648992.0, 8.4e9, 32.028e9, 34.316e9}; const char* Fn[4] = {"2.1166e9 (ODF ref)", "8.4e9", "32.028e9", "34.316e9"};
    double dObs[4], dRx[4], d2w[4], dtw[4]; for (int w = 0; w < 4; ++w) { dObs[w] = mean(OBS, wins[w].b0, wins[w].b1) - mean(OBS, wins[w].a0, wins[w].a1); dRx[w] = mean(rrx, wins[w].b0, wins[w].b1) - mean(rrx, wins[w].a0, wins[w].a1); d2w[w] = mean(r2w, wins[w].b0, wins[w].b1) - mean(r2w, wins[w].a0, wins[w].a1); dtw[w] = mean(T, wins[w].b0, wins[w].b1) - mean(T, wins[w].a0, wins[w].a1); }
    for (int w = 0; w < 4; ++w) std::printf("  %-10s: span %.0f s ; d(obs) = %+.3f Hz ; d(rdot_rx) = %+.6f km/s ; d(rdot_2w) = %+.6f km/s ; rdot_2w/rdot_rx change ratio %.4f\n", wins[w].nm, dtw[w], dObs[w], dRx[w], d2w[w], d2w[w] / dRx[w]);
    int nn = 0; std::string nw;
    for (int pr = 0; pr < 2; ++pr) { const double* dr = pr == 0 ? dRx : d2w; std::printf("\n  predictor %s\n", pr == 0 ? "P_rx (receive-time rdot)" : "P_2w (two-way average, up-leg at t - RTLT)");
        std::printf("    descriptive effective carrier F_eff = |d obs| / ((2/c)|d rdot|):"); for (int w = 0; w < 4; ++w) std::printf(" %s %.5e Hz", wins[w].nm, std::fabs(dObs[w]) / (2.0 / CKM * std::fabs(dr[w]))); std::printf("\n");
        for (int fi = 0; fi < 4; ++fi) for (int sg = 0; sg < 2; ++sg) { double s = sg == 0 ? 1.0 : -1.0; bool ok = true; double Rr[4]; for (int w = 0; w < 4; ++w) { double df = s * (-2.0 / CKM) * Fc[fi] * dr[w]; Rr[w] = dObs[w] / df; if (!(std::fabs(Rr[w] - 1) < 0.05)) ok = false; }
            std::printf("    F = %-20s sign %+d : R = %+.4f (third 1), %+.4f (third 2), %+.4f (third 3), %+.4f (whole) -> %s\n", Fn[fi], sg == 0 ? 1 : -1, Rr[0], Rr[1], Rr[2], Rr[3], ok ? "NATIVE PASS" : "not met"); if (ok) { ++nn; nw += std::string(pr == 0 ? "P_rx " : "P_2w ") + Fn[fi] + (sg == 0 ? " +; " : " -; "); } } }
    std::printf("\n  native outcome: %s\n", nn == 1 ? ("PASS (" + nw + ")").c_str() : nn > 1 ? ("NONUNIQUE (" + nw + ")").c_str() : "UNRESOLVED");
    return 0;
}
