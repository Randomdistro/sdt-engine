// ============================================================================
//  spaz_g2_depth2.cpp — Common Spaz Metric run 2, workstream W13
//  Author: James Christopher Tyndall, Melbourne.
//
//  Northwestern electron g-2 (Fan, Harvard PhD 2022): 11 field sets,
//  Dec 2021 – Jul 2022. Value per set = raw + cavity correction. Full
//  covariance = statistical + correlated cavity (thesis Fig. 4.37) + common
//  mode (thesis Table 4.8). GLS fits of alpha against Earth's solar depth and
//  three frame speeds; extraction validated on the thesis's own average.
//
//  Build: g++ -std=c++20 -O2 -IEngine/include spaz_g2_depth2.cpp
//  Run:   ./a.out <table csv> <correlation csv>
// ============================================================================

#include <sdt/laws.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <numbers>
#include <sstream>
#include <string>
#include <vector>

namespace {

namespace M = sdt::laws::measured;
constexpr double PI = std::numbers::pi;
constexpr double deg = PI / 180;
constexpr int n = 11;
using Mat = std::array<std::array<double, n>, n>;

int days_from_civil(int y, unsigned m, unsigned d) {
    y -= m <= 2;
    const int era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = unsigned(y - era * 400);
    const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + int(doe) - 719468;
}
int parse_day(const std::string& s) {
    return days_from_civil(std::stoi(s.substr(0, 4)), std::stoi(s.substr(5, 2)), std::stoi(s.substr(8, 2)));
}

// low-precision solar ephemeris (Astronomical Almanac), heliocentric ecliptic Earth [m]
void earth(double dj2000, double& x, double& y) {
    const double g = (357.528 + 0.9856003 * dj2000) * deg;
    const double L = (280.460 + 0.9856474 * dj2000) * deg + (1.915 * std::sin(g) + 0.020 * std::sin(2 * g)) * deg;
    const double R = M::AU * (1.00014 - 0.01671 * std::cos(g) - 0.00014 * std::cos(2 * g));
    x = R * std::cos(L + PI); y = R * std::sin(L + PI);
}

struct Regs { double z, vh2, vcmb2, vgal2; };

Regs regressors(double dj2000) {
    const double c = M::c, eps = 23.4393 * deg;
    double x, y, x1, y1, x2, y2;
    earth(dj2000, x, y);
    earth(dj2000 - 0.05, x1, y1); earth(dj2000 + 0.05, x2, y2);
    const double vx = (x2 - x1) / (0.1 * 86400), vy = (y2 - y1) / (0.1 * 86400);
    Regs r{};
    r.z = sdt::laws::bridge::koppa_Sun / std::hypot(x, y);
    r.vh2 = (vx * vx + vy * vy) / (c * c);
    auto to_ecl = [&](double ex, double ey, double ez, double s, double& X, double& Y, double& Z) {
        X = s * ex; Y = s * (ey * std::cos(eps) + ez * std::sin(eps)); Z = s * (-ey * std::sin(eps) + ez * std::cos(eps));
    };
    {   // Sun vs CMB: 369.82 km/s toward RA 167.942, Dec -6.944 (Planck 2018)
        const double ra = 167.942 * deg, de = -6.944 * deg;
        double X, Y, Z;
        to_ecl(std::cos(de) * std::cos(ra), std::cos(de) * std::sin(ra), std::sin(de), 369.82e3, X, Y, Z);
        r.vcmb2 = ((X + vx) * (X + vx) + (Y + vy) * (Y + vy) + Z * Z) / (c * c);
    }
    {   // Sun vs Sgr A*: (U,V,W) = (11.1, 245.64, 7.25) km/s, galactic -> equatorial eq = R gal
        const double R[3][3] = {{-0.0548755604, 0.4941094279, -0.8676661490},
                                {-0.8734370902, -0.4448296300, -0.1980763734},
                                {-0.4838350155, 0.7469822445, 0.4559837762}};
        const double gv[3] = {11.1e3, 245.64e3, 7.25e3};
        double eq[3] = {};
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) eq[i] += R[i][j] * gv[j];
        double X, Y, Z;
        to_ecl(eq[0], eq[1], eq[2], 1.0, X, Y, Z);
        r.vgal2 = ((X + vx) * (X + vx) + (Y + vy) * (Y + vy) + Z * Z) / (c * c);
    }
    return r;
}

bool invert(Mat a, Mat& inv) {
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) inv[i][j] = i == j;
    for (int c = 0; c < n; ++c) {
        int p = c;
        for (int r = c + 1; r < n; ++r) if (std::abs(a[r][c]) > std::abs(a[p][c])) p = r;
        if (std::abs(a[p][c]) < 1e-300) return false;
        std::swap(a[p], a[c]); std::swap(inv[p], inv[c]);
        const double d = a[c][c];
        for (int j = 0; j < n; ++j) { a[c][j] /= d; inv[c][j] /= d; }
        for (int r = 0; r < n; ++r) if (r != c) {
            const double f = a[r][c];
            for (int j = 0; j < n; ++j) { a[r][j] -= f * a[c][j]; inv[r][j] -= f * inv[c][j]; }
        }
    }
    return true;
}

} // namespace

int main(int argc, char** argv) {
    if (argc < 3) { std::printf("usage: <table csv> <corr csv>\n"); return 1; }
    struct Row { int set; double B, raw, rs, corr, cs, mid; };
    std::vector<Row> rows;
    {
        std::ifstream f(argv[1]); std::string line;
        while (std::getline(f, line)) {
            if (line.empty() || line[0] == '#' || line.rfind("set", 0) == 0) continue;
            std::stringstream ss(line); std::string v[9];
            for (auto& x : v) std::getline(ss, x, ',');
            const double mid = 0.5 * (parse_day(v[7]) + parse_day(v[8]) + 1);
            rows.push_back({std::stoi(v[0]), std::stod(v[1]), std::stod(v[3]), std::stod(v[4]),
                            std::stod(v[5]), std::stod(v[6]), mid});
        }
    }
    // correlation matrix is in ascending-field order; sort rows by field to match
    std::sort(rows.begin(), rows.end(), [](auto& a, auto& b) { return a.B < b.B; });
    Mat C{};
    {
        std::ifstream f(argv[2]); std::string line; int i = 0;
        while (std::getline(f, line) && i < n) {
            if (line.empty() || line[0] == '#') continue;
            std::stringstream ss(line); std::string x;
            for (int j = 0; j < n; ++j) { std::getline(ss, x, ','); C[i][j] = std::stod(x); }
            ++i;
        }
    }
    const double common2 = 0.094 * 0.094 + 0.005 * 0.005 + 0.010 * 0.010 + 0.003 * 0.003
                         + 0.003 * 0.003 + 0.009 * 0.009 + 0.012 * 0.012;   // Table 4.8 common mode
    Mat V{};
    std::array<double, n> y{};
    for (int i = 0; i < n; ++i) {
        y[i] = rows[i].raw + rows[i].corr;
        for (int j = 0; j < n; ++j)
            V[i][j] = C[i][j] * rows[i].cs * rows[j].cs + common2 + (i == j ? rows[i].rs * rows[i].rs : 0.0);
    }
    Mat W;
    if (!invert(V, W)) { std::printf("covariance singular\n"); return 1; }

    // validation: GLS mean, its uncertainty, chi2
    double sw = 0, swy = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) { sw += W[i][j]; swy += W[i][j] * y[j]; }
    const double mean = swy / sw, sig = 1 / std::sqrt(sw);
    double chi = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) chi += (y[i] - mean) * W[i][j] * (y[j] - mean);
    std::printf("spaz_g2_depth2 — W13 Northwestern g-2 (Fan 2022), 11 field sets\n");
    std::printf("  validation: GLS mean %+.3f (0.00 +- 0.02)  sigma %.3f (0.13 +- 0.01)  chi2 %.2f / 10 (13.04 +- 0.5)  [1e-12 of g/2]\n",
        mean, sig, chi);

    constexpr double a_e = 1.15965218e-3;
    const double ppb = 1e-12 / a_e * 1e9;       // ppb in alpha per 1e-12 in g/2
    const int j2000 = days_from_civil(2000, 1, 1);
    std::vector<Regs> R(n);
    std::printf("\n  %5s %6s %11s %9s %11s %9s\n", "set", "B (T)", "mid-date", "value", "z", "v_gal");
    for (int i = 0; i < n; ++i) {
        R[i] = regressors(rows[i].mid - j2000);
        const int d = int(rows[i].mid);
        std::printf("  %5d %6.3f %11d %+9.2f %11.5e %9.1f\n", rows[i].set, rows[i].B, d - days_from_civil(2021, 12, 1),
            y[i], R[i].z, std::sqrt(R[i].vgal2) * M::c / 1e3);
    }
    std::printf("  (mid-date in days after 2021-12-01; value in 1e-12 of g/2 = %.3f ppb in alpha)\n", ppb);

    auto gls = [&](auto pick, const char* name, double scale, double k_cs, double s_cs) {
        // design [1, x]; x centred is not required for GLS
        double A00 = 0, A01 = 0, A11 = 0, b0 = 0, b1 = 0;
        std::array<double, n> x{};
        for (int i = 0; i < n; ++i) x[i] = pick(R[i]) * scale;
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
            A00 += W[i][j]; A01 += W[i][j] * x[j]; A11 += x[i] * W[i][j] * x[j];
            b0 += W[i][j] * y[j]; b1 += x[i] * W[i][j] * y[j];
        }
        const double det = A00 * A11 - A01 * A01;
        const double k = (A00 * b1 - A01 * b0) / det, sk = std::sqrt(A00 / det);
        const double c0 = (A11 * b0 - A01 * b1) / det;
        double ch = 0;
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
            ch += (y[i] - c0 - k * x[i]) * W[i][j] * (y[j] - c0 - k * x[j]);
        // k is in (1e-12 g/2) per (scaled x); convert to dalpha/alpha per unit x
        const double kk = k * ppb * 1e-9 * scale, sks = sk * ppb * 1e-9 * scale;
        const double comb = std::sqrt(sks * sks + s_cs * s_cs);
        const bool nz = std::abs(kk) > 2 * sks, agree = std::abs(kk - k_cs) < 2 * comb;
        std::printf("  %-26s k_NW = %+.4g +- %.3g (%.1f sigma)  k_Cs = %+.4g +- %.3g  diff %.1f sigma  chi2 %.2f/9  -> %s\n",
            name, kk, sks, std::abs(kk) / sks, k_cs, s_cs, std::abs(kk - k_cs) / comb, ch,
            !agree ? "CONTRADICTS" : (nz ? "REPLICATES" : "UNINFORMATIVE"));
    };
    std::printf("\n  GLS slope against each regressor (Berkeley Cs values from W12/W12b/W12d)\n");
    gls([](const Regs& r) { return r.z; }, "solar depth z", 1e9, -3.81, 1.32);
    gls([](const Regs& r) { return r.vh2; }, "heliocentric v^2/c^2", 1e8, -1.89, 0.65);
    gls([](const Regs& r) { return r.vcmb2; }, "CMB-frame v^2/c^2", 1e6, -2.244e-3, 0.837e-3);
    gls([](const Regs& r) { return r.vgal2; }, "galactic-frame v^2/c^2", 1e6, 6.493e-3, 2.542e-3);

    double mb = 0, mz = 0;
    for (int i = 0; i < n; ++i) { mb += rows[i].B; mz += R[i].z; }
    mb /= n; mz /= n;
    double sbb = 0, szz = 0, sbz = 0;
    for (int i = 0; i < n; ++i) {
        sbb += (rows[i].B - mb) * (rows[i].B - mb); szz += (R[i].z - mz) * (R[i].z - mz);
        sbz += (rows[i].B - mb) * (R[i].z - mz);
    }
    std::printf("\n  confound: corr(B, z) = %+.3f (cavity correction depends on B)\n", sbz / std::sqrt(sbb * szz));
    return 0;
}
