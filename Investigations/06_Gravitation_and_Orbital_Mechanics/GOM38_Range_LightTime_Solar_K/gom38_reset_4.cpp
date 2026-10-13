// GOM38 blank-slate run 4 (2026-10-11), Amendment 2 (section 8 of the assessment): diagnostic unwrapped slope per segment. Derived from gom38_reset_2.cpp.
// (run 2 text:) Stage 2: DSS-25 type-37 range against a barycentric two-way light-time model; RU-closure test; frozen-K Shapiro ledger.
// Registration: GOM38_RESET_ASSESSMENT_2026-10-11.md section 4 (written before this file existed).
// Author: J. C. Harvey, Melbourne.
#include <algorithm>
#include <array>
#include <cmath>
#include <complex>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

typedef std::array<double, 3> V3;
static const std::string RAW = "Datasets/solar_propagation_2026-08/raw/";
static const double C = 299792.458, AUKM = 149597870.7, KSUN = 1476.35e-3 /* km */, PI = 3.14159265358979323846, TT_UTC = 64.184, JD0 = 2452431.708333333, MOD = 33554432.0;
static uint32_t be32(const uint8_t* p) { return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3]; }
static uint64_t bits(const uint8_t* p, int start1, int n) { uint64_t v = 0; for (int i = 0; i < n; ++i) { int b = start1 - 1 + i; v = (v << 1) | ((p[b / 8] >> (7 - b % 8)) & 1); } return v; }
static int labelRows(const std::string& lbl) { std::ifstream f(lbl); std::string ln; bool in = false; while (std::getline(f, ln)) { if (ln.find("= ODF3C_TABLE") != std::string::npos && ln.find("OBJECT") != std::string::npos) in = true; if (in && ln.find("ROWS") != std::string::npos) { size_t p = ln.find('='); return std::stoi(ln.substr(p + 1)); } } return -1; }
static std::vector<std::string> splitc(const std::string& ln) { std::vector<std::string> f; size_t p = 0; while (true) { size_t q = ln.find(',', p); if (q == std::string::npos) break; f.push_back(ln.substr(p, q - p)); p = q + 1; } return f; }
struct Tab { std::vector<double> t; std::vector<V3> x; };   // t = seconds since JD0 (TDB), x in km
static Tab readVec(const std::string& path) { Tab T; std::ifstream h(path); std::string ln; bool in = false; while (std::getline(h, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue; auto f = splitc(ln); if (f.size() < 5) continue; T.t.push_back((std::stod(f[0]) - JD0) * 86400.0); T.x.push_back({std::stod(f[2]), std::stod(f[3]), std::stod(f[4])}); } return T; }
static V3 interp(const Tab& T, double t) { size_t i = std::upper_bound(T.t.begin(), T.t.end(), t) - T.t.begin(); long a = (long)i - 2; if (a < 0) a = 0; if (a + 3 >= (long)T.t.size()) a = (long)T.t.size() - 4; V3 s = {0, 0, 0}; for (int j = 0; j < 4; ++j) { double L = 1; for (int k = 0; k < 4; ++k) if (k != j) L *= (t - T.t[a + k]) / (T.t[a + j] - T.t[a + k]); for (int c = 0; c < 3; ++c) s[c] += L * T.x[a + j][c]; } return s; }
static V3 add(V3 a, V3 b) { return {a[0] + b[0], a[1] + b[1], a[2] + b[2]}; }
static V3 sub(V3 a, V3 b) { return {a[0] - b[0], a[1] - b[1], a[2] - b[2]}; }
static double nrm(V3 a) { return std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]); }
static long long days_from_civil(int y, int m, int d) { y -= m <= 2; long long era = (y >= 0 ? y : y - 399) / 400; unsigned yoe = unsigned(y - era * 400); unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; return era * 146097 + (long long)doe - 719468; }
static const char* MON[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

static Tab EA, CA, SB;   // Earth heliocentric, Cassini heliocentric, Sun barycentric
static V3 ecefDSS25() { const double a = 6378.137, f = 1.0 / 298.257223563, e2 = f * (2 - f), lon = 243.1246368 * PI / 180, lat = 35.337612 * PI / 180, h = 0.959628; double N = a / std::sqrt(1 - e2 * std::sin(lat) * std::sin(lat)); return {(N + h) * std::cos(lat) * std::cos(lon), (N + h) * std::cos(lat) * std::sin(lon), (N * (1 - e2) + h) * std::sin(lat)}; }
// rotate ECEF -> ecliptic J2000 at TDB-second t (since JD0): GMST, IAU-1976 precession, obliquity
static V3 ecefToEcl(V3 r, double t) {
    double jdtdb = JD0 + t / 86400.0, jdut = jdtdb - TT_UTC / 86400.0, d = jdut - 2451545.0, Tu = d / 36525.0; double th = (280.46061837 + 360.98564736629 * d + 0.000387933 * Tu * Tu - Tu * Tu * Tu / 38710000.0) * PI / 180.0;
    V3 q = {r[0] * std::cos(th) - r[1] * std::sin(th), r[0] * std::sin(th) + r[1] * std::cos(th), r[2]};   // mean-of-date equatorial (no nutation)
    double T = (jdtdb - 2451545.0) / 36525.0, as = PI / 180.0 / 3600.0; double zeta = (2306.2181 * T + 0.30188 * T * T + 0.017998 * T * T * T) * as, zz = (2306.2181 * T + 1.09468 * T * T + 0.018203 * T * T * T) * as, thp = (2004.3109 * T - 0.42665 * T * T - 0.041833 * T * T * T) * as;
    // r_J2000 = R3(zeta) R2(-thp) R3(z) r_date, with the passive rotations R3(a) = [[c,s,0],[-s,c,0],[0,0,1]], R2(a) = [[c,0,-s],[0,1,0],[s,0,c]] inverted: apply P^T = R3(zeta)^T ... implemented as explicit inverse sequence
    auto R3 = [](V3 v, double a) { return V3{std::cos(a) * v[0] + std::sin(a) * v[1], -std::sin(a) * v[0] + std::cos(a) * v[1], v[2]}; };
    auto R2 = [](V3 v, double a) { return V3{std::cos(a) * v[0] - std::sin(a) * v[2], v[1], std::sin(a) * v[0] + std::cos(a) * v[2]}; };
    // r_date = R3(-z) R2(thp) R3(-zeta) r_J2000  =>  r_J2000 = R3(zeta) R2(-thp) R3(z) r_date
    V3 u = R3(q, zz); u = R2(u, -thp); u = R3(u, zeta);
    double eps = 84381.448 * as; return {u[0], std::cos(eps) * u[1] + std::sin(eps) * u[2], -std::sin(eps) * u[1] + std::cos(eps) * u[2]}; }
static V3 stationHelio(double t) { return add(interp(EA, t), ecefToEcl(ecefDSS25(), t)); }
static V3 scHelio(double t) { return interp(CA, t); }
static V3 sunBary(double t) { return interp(SB, t); }
static V3 stationBary(double t) { return add(stationHelio(t), sunBary(t)); }
static V3 scBary(double t) { return add(scHelio(t), sunBary(t)); }
struct LT { double td, tu, ts; };
static LT lighttime(double tr) { double tau = 0; V3 xs = stationBary(tr); for (int i = 0; i < 8; ++i) tau = nrm(sub(scBary(tr - tau), xs)) / C; double td = tau, ts = tr - td; V3 xc = scBary(ts); double tu = 0; for (int i = 0; i < 8; ++i) tu = nrm(sub(xc, stationBary(ts - tu))) / C; return {td, tu, ts}; }
static double leg(V3 A, V3 B) { double rA = nrm(A), rB = nrm(B), L = nrm(sub(A, B)); return 2.0 * KSUN / C * std::log((rA + rB + L) / (rA + rB - L)); }
static double med(std::vector<double> v) { std::sort(v.begin(), v.end()); size_t n = v.size(); return n % 2 ? v[n / 2] : 0.5 * (v[n / 2 - 1] + v[n / 2]); }
struct Row { double tutc; double obs; double f; int day; long i18, i19; };

int main() {
    std::printf("GOM38 blank-slate run 2, Stage 2 (registered in GOM38_RESET_ASSESSMENT_2026-10-11.md section 4)\n=======================================================================\n\n");
    EA = readVec(RAW + "jpl_horizons_earth_heliocentric_2002_157_160.csv"); CA = readVec(RAW + "jpl_horizons_cassini_heliocentric_2002_157_160.csv"); SB = readVec(RAW + "jpl_horizons_sun_barycentric_2002_157_160.csv");
    std::printf("tables: Earth %zu, Cassini %zu, Sun(bary) %zu epochs\n", EA.t.size(), CA.t.size(), SB.t.size());
    { V3 e = ecefDSS25(); std::printf("DSS-25 ECEF cylindrical: Dxy %.5f km (Horizons 5209.63556), Dz %.5f km (3669.04057)\n", std::hypot(e[0], e[1]), e[2]); }
    int fails = 0;
    // V1: down-leg against the Horizons DSS-25 range column
    { std::ifstream h(RAW + "jpl_horizons_cassini_dss25_rr_2002_157_160.csv"); std::string ln; bool in = false; std::vector<double> d; while (std::getline(h, ln)) { if (ln.find("$$SOE") != std::string::npos) { in = true; continue; } if (ln.find("$$EOE") != std::string::npos) break; if (!in) continue; auto f = splitc(ln); if (f.size() < 5) continue; std::string s = f[0]; size_t p = s.find_first_not_of(' '); s = s.substr(p); int y = std::stoi(s.substr(0, 4)); std::string mn = s.substr(5, 3); int m = 0; for (int i = 0; i < 12; ++i) if (mn == MON[i]) m = i + 1; int dd = std::stoi(s.substr(9, 2)), hh = std::stoi(s.substr(12, 2)), mi = std::stoi(s.substr(15, 2));
            double jdutc = 2440587.5 + double(days_from_civil(y, m, dd)) + hh / 24.0 + mi / 1440.0; double tr = (jdutc + TT_UTC / 86400.0 - JD0) * 86400.0; if (tr < 3600 || tr > (CA.t.back() - 3600)) continue; LT l = lighttime(tr); double dkm = std::stod(f[3]) * AUKM; d.push_back((l.td * C - dkm) / C * 1e6); }
        double s2 = 0, mx = 0; for (double v : d) { s2 += v * v; mx = std::max(mx, std::fabs(v)); } double rms = std::sqrt(s2 / d.size()); bool ok = rms < 3.0 && mx < 10.0;
        std::printf("[V1] model down-leg light time minus Horizons delta/c over %zu table epochs: rms %.3f us, max %.3f us, median %+.3f us (gates: rms < 3, max < 10) -> %s\n", d.size(), rms, mx, med(d), ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // V2: wrap arithmetic
    { double M = MOD * 1.0586e-9, off = 123.456e-6, worst = 0; for (double base : {0.0, 1.0e4, 8334.123456789, 12345.6789}) { double obs = std::fmod(base + off, M); double rho = obs - base; rho -= M * std::round(rho / M); worst = std::max(worst, std::fabs(rho - off)); } bool ok = worst < 1e-9; std::printf("[V2] wrap arithmetic: worst error %.2e s (gate 1e-9 for double precision at 1e4 s) -> %s\n", worst, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("\nVALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("\nVALIDATIONS: met\n\n");
    // rows
    std::vector<Row> rows;
    for (int day = 157; day <= 160; ++day) { char b1[256], b2[256]; std::snprintf(b1, sizeof b1, "cassini_sce1/cors_0021/sce1_%d/odf/c32easc2002_%d_0000xmmmv0.odf", day, day); std::snprintf(b2, sizeof b2, "cassini_sce1/cors_0021/sce1_%d/odf/c32easc2002_%d_0000xmmmv0.lbl", day, day); std::ifstream f(RAW + b1, std::ios::binary); std::vector<uint8_t> b((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); int n = labelRows(RAW + b2);
        for (int r = 6; r <= 5 + n; ++r) { const uint8_t* p = b.data() + 36 * (r - 1); const uint8_t* q = p + 16; int type = int(bits(q, 20, 6)), rx = int(bits(q, 4, 7)), tx = int(bits(q, 11, 7)), valid = int(bits(q, 32, 1)); if (type != 37 || valid || rx != 25 || tx != 25) continue;
            Row w; w.tutc = double(be32(p)) + double(bits(p + 4, 1, 10)) / 1000.0; w.obs = double(int32_t(be32(p + 8))) + double(int32_t(be32(p + 12))) / 1e9; w.i18 = (long)bits(q, 51, 22); w.i19 = (long)bits(q, 73, 24); w.f = (double(w.i18) * 16777216.0 + double(w.i19)) / 1000.0; w.day = day; rows.push_back(w); } }
    std::printf("used rows (type 37, valid, rx25 tx25): %zu\n", rows.size());
    // per-row
    struct Out { int day; long i18, i19; double rho_w, th, M, dK, rtlt, T_obs, T_model; };
    std::vector<Out> out;
    for (auto& w : rows) { double jdutc = 2433282.5 + w.tutc / 86400.0; double tr = (jdutc + TT_UTC / 86400.0 - JD0) * 86400.0; if (tr < 3600 || tr > CA.t.back() - 3600) continue; LT l = lighttime(tr); double RU = (221.0 / 1498.0) * 1e-18 * w.f, M = MOD * RU, Tobs = w.obs * RU, Tm = l.td + l.tu, rho = Tobs - Tm; rho -= M * std::round(rho / M);
        V3 sc = scHelio(l.ts), stU = stationHelio(l.ts - l.tu), stR = stationHelio(tr); double dK = leg(stU, sc) + leg(sc, stR); out.push_back({w.day, w.i18, w.i19, rho, 2 * PI * rho / M, M, dK, Tm, Tobs, Tm}); }
    std::printf("rows inside the table span: %zu\n\n", out.size());
    for (size_t i = 0; i < out.size() && i < 4; ++i) std::printf("  sample row %zu: day %d, f_ref %.3f Hz, T_obs %.9e s (wrapped), T_model %.6f s, residual (wrapped) %+.6e s, M %.6e s\n", i, out[i].day, (double(out[i].i18) * 16777216.0 + double(out[i].i19)) / 1000.0, out[i].T_obs, out[i].T_model, out[i].rho_w, out[i].M);
    std::printf("\nPER-DAY: n, circular concentration Rbar, circular sd (s), median Shapiro two-way (s), median round trip (s), ratio\n");
    for (int day = 157; day <= 160; ++day) { std::complex<double> z = 0; int n = 0; std::vector<double> dk, rt, Ms; for (auto& o : out) if (o.day == day) { z += std::polar(1.0, o.th); ++n; dk.push_back(o.dK); rt.push_back(o.rtlt); Ms.push_back(o.M); } if (!n) continue; double Rb = std::abs(z / double(n)), sc = Rb > 0 ? (med(Ms) / (2 * PI)) * std::sqrt(-2 * std::log(Rb)) : 1e9; std::printf("  day %d: n %3d  Rbar %.4f  sigma_c %.4e s  dK %.6e s  RTLT %.3f s  dK/RTLT %.3e  dK/sigma_c %.3e\n", day, n, Rb, sc, med(dk), med(rt), med(dk) / med(rt), med(dk) / sc); }
    std::printf("\nPER-SEGMENT (consecutive rows of equal reference-frequency pair (Item 18, Item 19), n >= 5): day, Item18, Item19, n, Rbar, mean residual direction (s), sigma_c (s)\n");
    int nClosed = 0, nSeg = 0; size_t i = 0;
    while (i < out.size()) { size_t j = i; while (j < out.size() && out[j].day == out[i].day && out[j].i18 == out[i].i18 && out[j].i19 == out[i].i19) ++j; size_t n = j - i; if (n >= 5) { std::complex<double> z = 0; double M = 0; for (size_t k = i; k < j; ++k) { z += std::polar(1.0, out[k].th); M += out[k].M; } M /= n; double Rb = std::abs(z / double(n)), mean = std::arg(z) * M / (2 * PI), sc = Rb > 0 ? (M / (2 * PI)) * std::sqrt(-2 * std::log(Rb)) : 1e9; ++nSeg; bool cl = Rb >= 0.9; if (cl) ++nClosed; std::printf("  day %d  %ld %ld  n %zu  Rbar %.4f  mean %+.6e s  sigma_c %.4e s  %s\n", out[i].day, out[i].i18, out[i].i19, n, Rb, mean, sc, cl ? "CLOSES" : "no closure"); } i = j; }
    std::printf("\nDIAGNOSTIC (Amendment 2): unwrapped residual versus model round-trip time, per segment (reported only)\n");
    { size_t i2 = 0; while (i2 < out.size()) { size_t j = i2; while (j < out.size() && out[j].day == out[i2].day && out[j].i18 == out[i2].i18 && out[j].i19 == out[i2].i19) ++j; size_t n = j - i2; if (n >= 5) {
        std::vector<double> x, y; double prev = out[i2].rho_w, off = 0, maxstep = 0; for (size_t k = i2; k < j; ++k) { double d = out[k].rho_w - prev; double stepv = d; if (d > out[k].M / 2) { off -= out[k].M; stepv = d - out[k].M; } else if (d < -out[k].M / 2) { off += out[k].M; stepv = d + out[k].M; } maxstep = std::max(maxstep, std::fabs(stepv)); prev = out[k].rho_w; y.push_back(out[k].rho_w + off); x.push_back(out[k].rtlt - out[i2].rtlt); }
        double M = out[i2].M; double mx = 0, my = 0; for (size_t k = 0; k < x.size(); ++k) { mx += x[k]; my += y[k]; } mx /= x.size(); my /= x.size(); double sxy = 0, sxx = 0; for (size_t k = 0; k < x.size(); ++k) { sxy += (x[k] - mx) * (y[k] - my); sxx += (x[k] - mx) * (x[k] - mx); } double s = sxy / sxx, a = my - s * mx, r2 = 0, ymin = 1e30, ymax = -1e30; for (size_t k = 0; k < x.size(); ++k) { double e = y[k] - (a + s * x[k]); r2 += e * e; ymin = std::min(ymin, y[k]); ymax = std::max(ymax, y[k]); } double rms = std::sqrt(r2 / x.size());
        std::printf("  day %d  %ld %ld  n %zu  max step %.3e s (gate < M/4 = %.3e: %s)  slope s = %+.6f  fit rms %.3e s  span of unwrapped rho %.4e s  T_model span %.3f s\n", out[i2].day, out[i2].i18, out[i2].i19, n, maxstep, M / 4, maxstep < M / 4 ? "ok" : "NOT unwrappable", s, rms, ymax - ymin, x.back() - x.front()); } i2 = j; } }
    std::printf("\nsegments with n >= 5: %d ; closing (Rbar >= 0.9): %d\n", nSeg, nClosed);
    std::printf("Status: %s\n", nClosed == 0 ? "no segment closes with the row reference frequency: RANGE_K_UNRESOLVED (no RU closure; not an exclusion)" : "some segments close: change-based sensitivity to be registered separately on the closed segments");
    return 0;
}
