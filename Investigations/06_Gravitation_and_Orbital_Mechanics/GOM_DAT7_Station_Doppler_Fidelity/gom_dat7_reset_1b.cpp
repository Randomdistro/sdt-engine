// ERRATUM RUN 2026-10-11: identical to gom_dat7_reset_1.cpp except that the 1-D table interpolation is the 4-point (cubic) Lagrange form instead of linear (GOM37 V4: linear worst error 19.7 Hz at 15-min / ~6 Hz at 5-min, cubic 0.02 Hz). Criteria and registration unchanged.
// GOM_DAT7 blank-slate run 1 (2026-10-10). Registration: GOM_DAT7_RESET_ASSESSMENT_2026-10-10.md sections 0-2 (written before this file existed).
//  Predictors A (geocentre, f_ref), B1 (DSS-25 receive-time, 209/15 x f_ref), B2 (DSS-25 receive-time, 32.028e9 Hz), and two-way B1w/B2w.
//  Gates: G-rel (prompt: closer to 1 than 3.37 or smaller residual than A), G-abs (|median|f|/median|obs| - 1| < 0.15 and median|obs-f|/median|obs| < 0.15), C4 = both; G-chg (|R-1| < 0.05 in 3 thirds + whole span, both signs).
//  Validations: VC1 |r_geo| = delta AU to 1e-4; VC2 |rdot_geo - deldot| < 0.5 km/s; VC3 7447 records; VC4 RTLT 8300-8400 s. Geocentre TDB -> UTC: -64.184 s.
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
static const char* HG = "Datasets/solar_propagation_2026-08/raw/jpl_horizons_cassini_geocentric_2002_157.csv";
static const double CKM = 299792.458, AUKM = 149597870.7;
static uint32_t be32(const uint8_t* p) { return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3]; }
static uint64_t bits(const uint8_t* p, int start1, int n) { uint64_t v = 0; for (int i = 0; i < n; ++i) { int b = start1 - 1 + i; v = (v << 1) | ((p[b / 8] >> (7 - b % 8)) & 1); } return v; }
static long long days_from_civil(int y, int m, int d) { y -= m <= 2; long long era = (y >= 0 ? y : y - 399) / 400; unsigned yoe = unsigned(y - era * 400); unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; return era * 146097 + (long long)doe - 719468; }
static double sec1950(int y, int m, int d, int hh, int mm) { return double(days_from_civil(y, m, d) + 7305) * 86400.0 + hh * 3600.0 + mm * 60.0; }
static const char* MON[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
static std::vector<std::string> splitc(const std::string& ln) { std::vector<std::string> f; size_t p = 0; while (true) { size_t q = ln.find(',', p); if (q == std::string::npos) break; f.push_back(ln.substr(p, q - p)); p = q + 1; } return f; }
static double parseDate(std::string d) { size_t s = d.find("A.D."); if (s != std::string::npos) d = d.substr(s + 5); else d = d.substr(d.find_first_not_of(' ')); int y = std::stoi(d.substr(0, 4)); std::string mn = d.substr(5, 3); int m = 0; for (int i = 0; i < 12; ++i) if (mn == MON[i]) m = i + 1; return sec1950(y, m, std::stoi(d.substr(9, 2)), std::stoi(d.substr(12, 2)), std::stoi(d.substr(15, 2))); }
struct Tab { std::vector<double> t, delta, dd; };
static Tab readTab(const char* path) { Tab T; std::ifstream h(path); std::string ln; bool in = false; while (std::getline(h, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue; auto f = splitc(ln); if (f.size() < 5) continue; T.t.push_back(parseDate(f[0])); T.delta.push_back(std::stod(f[3])); T.dd.push_back(std::stod(f[4])); } return T; }
struct Geo { std::vector<double> t, r, rd; };
static Geo readGeo() { Geo G; std::ifstream h(HG); std::string ln; bool in = false; while (std::getline(h, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue; auto f = splitc(ln); if (f.size() < 8) continue;
        double X = std::stod(f[2]), Y = std::stod(f[3]), Z = std::stod(f[4]), VX = std::stod(f[5]), VY = std::stod(f[6]), VZ = std::stod(f[7]); double rr = std::sqrt(X * X + Y * Y + Z * Z); G.t.push_back(parseDate(f[1]) - 64.184); G.r.push_back(rr); G.rd.push_back((X * VX + Y * VY + Z * VZ) / rr); } return G; }
static double interp(const std::vector<double>& x, const std::vector<double>& y, double t) { size_t i = std::upper_bound(x.begin(), x.end(), t) - x.begin(); if (i == 0) i = 1; if (i >= x.size()) i = x.size() - 1; long a = (long)i - 2; if (a < 0) a = 0; if (a + 3 >= (long)x.size()) a = (long)x.size() - 4; double s = 0; for (int j = 0; j < 4; ++j) { double L = 1; for (int k = 0; k < 4; ++k) if (k != j) L *= (t - x[a + k]) / (x[a + j] - x[a + k]); s += L * y[a + j]; } return s; }
static double med(std::vector<double> v) { std::sort(v.begin(), v.end()); size_t n = v.size(); return n % 2 ? v[n / 2] : 0.5 * (v[n / 2 - 1] + v[n / 2]); }
static double mean(const std::vector<double>& v, size_t a, size_t b) { double s = 0; for (size_t i = a; i < b; ++i) s += v[i]; return s / double(b - a); }

int main() {
    std::printf("GOM_DAT7 blank-slate run 1 (registered in GOM_DAT7_RESET_ASSESSMENT_2026-10-10.md sections 0-2)\n=================================================================================\n\n");
    std::ifstream f(ODF, std::ios::binary); std::vector<uint8_t> buf((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    std::vector<double> T, OBS, REF;
    for (int r = 6; r <= 7452; ++r) { const uint8_t* p = buf.data() + 36 * (r - 1); const uint8_t* q = p + 16; int type = int(bits(q, 20, 6)), rx = int(bits(q, 4, 7)), tx = int(bits(q, 11, 7)), valid = int(bits(q, 32, 1)); if (type != 12 || valid || rx != 25 || tx != 25) continue;
        T.push_back(double(be32(p)) + double(bits(p + 4, 1, 10)) / 1000.0); OBS.push_back(double(int32_t(be32(p + 8))) + double(int32_t(be32(p + 12))) / 1e9); REF.push_back((double(bits(q, 51, 22)) * 16777216.0 + double(bits(q, 73, 24))) / 1000.0); }
    const size_t n = T.size(); Tab a = readTab(H5), b = readTab(H15); Geo G = readGeo(); int fails = 0;
    { bool ok = n == 7447; std::printf("[VC3] selected %zu records -> %s\n", n, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { double v1 = 0, v2 = 0; for (size_t i = 0; i < a.t.size(); ++i) { v1 = std::max(v1, std::fabs(interp(G.t, G.r, a.t[i]) / (a.delta[i] * AUKM) - 1)); v2 = std::max(v2, std::fabs(interp(G.t, G.rd, a.t[i]) - a.dd[i])); }
      bool ok1 = v1 < 1e-4, ok2 = v2 < 0.5; std::printf("[VC1] %zu epochs (geocentre interpolated to the DSS-25 UTC epochs): |r_geo|/(delta AU) - 1 worst %.2e -> %s\n[VC2] |rdot_geo - deldot_DSS25| worst %.4f km/s -> %s\n", a.t.size(), v1, ok1 ? "met" : "NOT MET", v2, ok2 ? "met" : "NOT MET"); if (!ok1) ++fails; if (!ok2) ++fails; }
    { double lo = 1e9, hi = -1e9; for (size_t i = 0; i < n; ++i) { double rt = 2.0 * interp(a.t, a.delta, T[i]) * AUKM / CKM; lo = std::min(lo, rt); hi = std::max(hi, rt); } bool ok = lo > 8300 && hi < 8400; std::printf("[VC4] RTLT %.1f to %.1f s -> %s\n\n", lo, hi, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");
    { double sl = (G.rd.back() - G.rd.front()) / (G.t.back() - G.t.front()); double dl = interp(a.t, a.delta, T[n / 2]) * AUKM / CKM; std::printf("A light-time bound: d(rdot_geo)/dt = %.3e km/s^2 ; x delta/c (%.0f s) = %.4f km/s (%.2e of rdot)\n\n", sl, dl, sl * dl, sl * dl / interp(G.t, G.rd, T[n / 2])); }
    const double fref = REF[0], rho = 209.0 / 15.0, FKA = 32.028e9;
    std::vector<double> rA(n), rrx(n), r2w(n);
    for (size_t i = 0; i < n; ++i) { rA[i] = interp(G.t, G.rd, T[i]); rrx[i] = interp(a.t, a.dd, T[i]); double rt = 2.0 * interp(a.t, a.delta, T[i]) * AUKM / CKM; r2w[i] = 0.5 * (rrx[i] + interp(b.t, b.dd, T[i] - rt)); }
    struct P { const char* nm; const std::vector<double>* rd; double F; } ps[5] = {{"A  (geocentre, f_ref)", &rA, fref}, {"B1 (DSS-25 rx, 209/15 f_ref)", &rrx, rho * fref}, {"B2 (DSS-25 rx, 32.028e9)", &rrx, FKA}, {"B1w (two-way, 209/15 f_ref)", &r2w, rho * fref}, {"B2w (two-way, 32.028e9)", &r2w, FKA}};
    std::vector<double> ao(n); for (size_t i = 0; i < n; ++i) ao[i] = std::fabs(OBS[i]); const double mo = med(ao);
    std::vector<std::vector<double>> fp(5, std::vector<double>(n)); for (int k = 0; k < 5; ++k) for (size_t i = 0; i < n; ++i) fp[k][i] = -2.0 * (*ps[k].rd)[i] / CKM * ps[k].F;
    std::printf("---- Level gates (prompt C4 relative; audit-corrected absolute) ; median |obs| = %.3f Hz ----\n", mo);
    double resA = 0; { std::vector<double> d(n); for (size_t i = 0; i < n; ++i) d[i] = std::fabs(OBS[i] - fp[0][i]); resA = med(d); }
    for (int k = 0; k < 5; ++k) { std::vector<double> d(n), af(n); for (size_t i = 0; i < n; ++i) { d[i] = std::fabs(OBS[i] - fp[k][i]); af[i] = std::fabs(fp[k][i]); } double rB = med(af) / mo, resB = med(d), Aab = resB / mo; bool gabs = std::fabs(rB - 1) < 0.15 && Aab < 0.15; bool grel = std::fabs(rB - 1) < std::fabs(3.37 - 1) || resB < resA;
        std::printf("  %-30s median|f|/median|obs| = %9.4f ; median|obs-f| = %.1f Hz (/median|obs| = %.3f) ; G-rel %s ; G-abs %s ; C4 %s\n", ps[k].nm, rB, resB, Aab, k == 0 ? "(baseline)" : (grel ? "met" : "not met"), gabs ? "met" : "not met", k == 0 ? "(baseline)" : ((grel && gabs) ? "MET" : "not met")); }
    std::printf("\n---- Residual summary obs - f (prompt C5; sign as defined) ----\n");
    for (int k : {1, 2}) { std::vector<double> d(n); double mn = 1e99, mx = -1e99, m = 0; for (size_t i = 0; i < n; ++i) { d[i] = OBS[i] - fp[k][i]; mn = std::min(mn, d[i]); mx = std::max(mx, d[i]); m += d[i]; } m /= n; double sd = 0; for (double v : d) sd += (v - m) * (v - m); sd = std::sqrt(sd / (n - 1)); std::printf("  %-30s min %.1f ; median %.1f ; max %.1f ; mean %.1f ; sd %.2f Hz\n", ps[k].nm, mn, med(d), mx, m, sd); }
    std::printf("\n---- Change-based gate G-chg (|R - 1| < 0.05 in thirds and whole span; both signs) ----\n");
    struct W { size_t a0, a1, b0, b1; } wins[4] = {{0, 100, n / 3 - 100, n / 3}, {n / 3, n / 3 + 100, 2 * n / 3 - 100, 2 * n / 3}, {2 * n / 3, 2 * n / 3 + 100, n - 100, n}, {0, 300, n - 300, n}};
    double dObs[4]; for (int w = 0; w < 4; ++w) dObs[w] = mean(OBS, wins[w].b0, wins[w].b1) - mean(OBS, wins[w].a0, wins[w].a1);
    for (int k = 0; k < 5; ++k) { double Rr[4]; for (int w = 0; w < 4; ++w) { double df = mean(fp[k], wins[w].b0, wins[w].b1) - mean(fp[k], wins[w].a0, wins[w].a1); Rr[w] = dObs[w] / df; }
        bool pos = true, neg = true; for (int w = 0; w < 4; ++w) { if (!(std::fabs(Rr[w] - 1) < 0.05)) pos = false; if (!(std::fabs(-Rr[w] - 1) < 0.05)) neg = false; }
        std::printf("  %-30s R = %+9.4f, %+9.4f, %+9.4f (thirds), %+9.4f (whole) -> sign as defined: %s ; flipped: %s\n", ps[k].nm, Rr[0], Rr[1], Rr[2], Rr[3], pos ? "PASS" : "not met", neg ? "PASS" : "not met"); }
    std::printf("\n---- Descriptive: residual obs + f - mean (f as defined, i.e. sign flipped) after the constant offset is removed ----\n");
    for (int k = 0; k < 5; ++k) { std::vector<double> d(n); double m = 0; for (size_t i = 0; i < n; ++i) { d[i] = OBS[i] + fp[k][i]; m += d[i]; } m /= n; double sd = 0; for (double v : d) sd += (v - m) * (v - m); sd = std::sqrt(sd / (n - 1)); std::printf("  %-30s offset %.2f Hz ; sd %.2f Hz\n", ps[k].nm, m, sd); }
    return 0;
}
