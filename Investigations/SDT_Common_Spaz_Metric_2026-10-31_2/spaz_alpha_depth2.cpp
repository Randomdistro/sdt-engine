// ============================================================================
//  spaz_alpha_depth2.cpp — Common Spaz Metric run 2, workstream W12
//  Author: James Christopher Tyndall, Melbourne.
//
//  Berkeley Cs alpha measurements (Zhong thesis Fig. 4.4, digitised from the
//  PDF vector paths into cs_alpha_fig44_digitised2.csv) against Earth's solar
//  depth z = koppa_Sun / r(date). Weighted fit value = c + k (z - zbar).
//
//  Build: g++ -std=c++20 -O2 -IEngine/include spaz_alpha_depth2.cpp
//  Run:   ./a.out <csv in> <csv out>
// ============================================================================

#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <fstream>
#include <numbers>
#include <sstream>
#include <string>
#include <vector>

namespace {

constexpr double PI = std::numbers::pi;
constexpr double e_orb = 0.0167086;            // Earth orbital eccentricity
constexpr double P_days = 365.256363;          // anomalistic year ~ sidereal (sufficient here)

struct Pt { int idx, N; std::string date; double v, s, z, t; };

int days_from_civil(int y, unsigned m, unsigned d) {   // days since 1970-01-01
    y -= m <= 2;
    const int era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = unsigned(y - era * 400);
    const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + int(doe) - 719468;
}

double depth(int day) {
    const int peri = days_from_civil(2017, 1, 4);
    const double Mn = 2 * PI * (day - peri) / P_days;
    double E = Mn;
    for (int i = 0; i < 20; ++i) E = Mn + e_orb * std::sin(E);
    const double r = sdt::laws::measured::AU * (1 - e_orb * std::cos(E));
    return sdt::laws::bridge::koppa_Sun / r;
}

struct Fit { double c, k, sc, sk, chi2; int n; };

Fit wls(const std::vector<Pt>& p) {
    double S = 0, Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;
    double zb = 0, w = 0;
    for (auto& q : p) { zb += q.z / (q.s * q.s); w += 1 / (q.s * q.s); }
    zb /= w;
    for (auto& q : p) {
        const double wi = 1 / (q.s * q.s), x = (q.z - zb) * 1e9;   // x in units of 1e-9
        S += wi; Sx += wi * x; Sy += wi * q.v; Sxx += wi * x * x; Sxy += wi * x * q.v;
    }
    const double D = S * Sxx - Sx * Sx;
    Fit f{(Sxx * Sy - Sx * Sxy) / D, (S * Sxy - Sx * Sy) / D, std::sqrt(Sxx / D), std::sqrt(S / D), 0, int(p.size())};
    for (auto& q : p) {
        const double r = (q.v - f.c - f.k * (q.z - zb) * 1e9) / q.s;
        f.chi2 += r * r;
    }
    return f;   // k in ppb per 1e-9 of z  == dimensionless coupling k (dalpha/alpha = k dz)
}

} // namespace

int main(int argc, char** argv) {
    if (argc < 3) { std::printf("usage: <csv in> <csv out>\n"); return 1; }
    std::ifstream in(argv[1]);
    std::string line;
    std::vector<Pt> pts;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#' || line.rfind("index", 0) == 0) continue;
        std::stringstream ss(line); std::string f[5];
        for (auto& x : f) std::getline(ss, x, ',');
        const int y = 2000 + std::stoi(f[1].substr(0, 2)), m = std::stoi(f[1].substr(2, 2)),
                  d = std::stoi(f[1].substr(4, 2));
        const int day = days_from_civil(y, m, d);
        pts.push_back({std::stoi(f[0]), std::stoi(f[2]), f[1], std::stod(f[3]), std::stod(f[4]),
                       depth(day), double(day - days_from_civil(2016, 12, 13))});
    }
    std::printf("spaz_alpha_depth2 — W12 Berkeley Cs alpha vs solar depth (%zu points)\n", pts.size());

    // digitisation validation
    double w = 0, wv = 0;
    for (auto& p : pts) { w += 1 / (p.s * p.s); wv += p.v / (p.s * p.s); }
    const double mean = wv / w, sig = 1 / std::sqrt(w);
    double chi = 0;
    for (auto& p : pts) chi += std::pow((p.v - mean) / p.s, 2);
    std::printf("  validation: weighted mean %+.3f ppb (0 +- 0.05)  combined sigma %.3f ppb (0.16 +- 0.01)  "
        "reduced chi2 %.2f (1.2 +- 0.1)\n", mean, sig, chi / (pts.size() - 1));

    const double zmin = [&] { double m = 1; for (auto& p : pts) m = std::min(m, p.z); return m; }();
    const double zmax = [&] { double m = 0; for (auto& p : pts) m = std::max(m, p.z); return m; }();
    std::printf("  depth range z = %.6e .. %.6e (spread %.3e)\n", zmin, zmax, zmax - zmin);

    auto report = [](const char* name, const Fit& f) {
        std::printf("  %-26s n=%2d  k = %+7.2f +- %5.2f  (%.1f sigma from 0; k=3.5 is %+.1f sigma; "
            "k=-3.5 is %+.1f sigma)  chi2/dof = %.2f\n", name, f.n, f.k, f.sk, std::abs(f.k) / f.sk,
            (3.5 - f.k) / f.sk, (-3.5 - f.k) / f.sk, f.chi2 / (f.n - 2));
    };
    const Fit all = wls(pts);
    report("all 28", all);
    std::vector<Pt> n125;
    for (auto& p : pts) if (p.N == 125) n125.push_back(p);
    const Fit sub = wls(n125);
    report("N = 125 subset", sub);

    // depth vs time collinearity (a slope in z cannot be told from a slope in time)
    double mz = 0, mt = 0;
    for (auto& p : pts) { mz += p.z; mt += p.t; }
    mz /= pts.size(); mt /= pts.size();
    double szz = 0, stt = 0, szt = 0;
    for (auto& p : pts) { szz += (p.z - mz) * (p.z - mz); stt += (p.t - mt) * (p.t - mt); szt += (p.z - mz) * (p.t - mt); }
    std::printf("  correlation(depth, date) = %.3f\n", szt / std::sqrt(szz * stt));

    // ── W12b (post-registration, James 2026-10-31): movement-budget regressors ──
    // (i) heliocentric orbital speed: v^2/c^2 = koppa (2/r - 1/a) = 2 z - koppa/a,
    //     an exact linear function of z, so its fit is the depth fit with k_v = k/2.
    // (ii) speed relative to the CMB rest frame (the dipole): v = v_Sun,CMB + v_Earth.
    //     Sun-CMB velocity 369.82 km/s toward RA 167.942 deg, Dec -6.944 deg
    //     (Planck 2018, MEASURED-INPUT). Earth velocity from a low-precision solar
    //     ephemeris (Astronomical Almanac formulae), numerically differentiated.
    {
        const double deg = PI / 180, eps = 23.4393 * deg, c = sdt::laws::measured::c;
        const double ra = 167.942 * deg, de = -6.944 * deg, vS = 369.82e3;
        const double ex = std::cos(de) * std::cos(ra), ey0 = std::cos(de) * std::sin(ra), ez0 = std::sin(de);
        const double vSx = vS * ex, vSy = vS * (ey0 * std::cos(eps) + ez0 * std::sin(eps)),
                     vSz = vS * (-ey0 * std::sin(eps) + ez0 * std::cos(eps));
        const int j2000 = days_from_civil(2000, 1, 1);
        auto earth = [&](double dd, double& x, double& y) {     // heliocentric ecliptic [m]
            const double g = (357.528 + 0.9856003 * dd) * deg;
            const double L = (280.460 + 0.9856474 * dd) * deg + (1.915 * std::sin(g) + 0.020 * std::sin(2 * g)) * deg;
            const double R = sdt::laws::measured::AU * (1.00014 - 0.01671 * std::cos(g) - 0.00014 * std::cos(2 * g));
            x = R * std::cos(L + PI); y = R * std::sin(L + PI);
        };
        std::vector<Pt> cmb = pts, hel = pts;
        double vmin = 1e9, vmax = 0;
        for (size_t i = 0; i < pts.size(); ++i) {
            const double dd = pts[i].t + days_from_civil(2016, 12, 13) - j2000 - 0.5 + 0.5;
            double x1, y1, x2, y2;
            earth(dd - 0.05, x1, y1); earth(dd + 0.05, x2, y2);
            const double vx = (x2 - x1) / (0.1 * 86400), vy = (y2 - y1) / (0.1 * 86400);
            const double vh2 = vx * vx + vy * vy;
            const double tx = vSx + vx, ty = vSy + vy, tz = vSz;
            const double u = (tx * tx + ty * ty + tz * tz) / (c * c);
            cmb[i].z = u * 1e-2;          // scaled so the fit's 1e9 factor reports k per unit u x 1e-7
            hel[i].z = vh2 / (c * c);
            vmin = std::min(vmin, std::sqrt(u) * c); vmax = std::max(vmax, std::sqrt(u) * c);
        }
        const Fit fh = wls(hel), fc = wls(cmb);
        std::printf("\n  W12b movement-budget regressors (post-registration)\n");
        std::printf("    heliocentric v^2/c^2      : k_v = %+7.2f +- %5.2f  chi2 = %.2f  (depth fit chi2 = %.2f)\n",
            fh.k, fh.sk, fh.chi2, all.chi2);
        std::printf("    CMB-frame |v|: %.1f .. %.1f km/s over the campaign\n", vmin / 1e3, vmax / 1e3);
        std::printf("    CMB-frame v^2/c^2         : k_u = %+.3e +- %.3e  (%.1f sigma)  chi2 = %.2f\n",
            fc.k * 1e-2, fc.sk * 1e-2, std::abs(fc.k) / fc.sk, fc.chi2);
        // "plus depth" (James): movement budget plus solar depth, w = v^2/c^2 + z
        std::vector<Pt> hz = pts, cz = pts;
        for (size_t i = 0; i < pts.size(); ++i) {
            hz[i].z = hel[i].z + pts[i].z;
            cz[i].z = (cmb[i].z * 1e2 + pts[i].z) * 1e-2;
        }
        const Fit fhz = wls(hz), fcz = wls(cz);
        std::printf("    heliocentric v^2/c^2 + z  : k_w = %+7.3f +- %6.3f  (%.1f sigma)  chi2 = %.2f\n",
            fhz.k, fhz.sk, std::abs(fhz.k) / fhz.sk, fhz.chi2);
        std::printf("    CMB-frame v^2/c^2 + z     : k_w = %+.3e +- %.3e  (%.1f sigma)  chi2 = %.2f\n",
            fcz.k * 1e-2, fcz.sk * 1e-2, std::abs(fcz.k) / fcz.sk, fcz.chi2);
        double mu = 0;
        for (auto& p : cmb) mu += p.z;
        mu /= cmb.size();
        double suu = 0, szz2 = 0, suz = 0;
        for (size_t i = 0; i < pts.size(); ++i) {
            suu += (cmb[i].z - mu) * (cmb[i].z - mu); szz2 += (pts[i].z - mz) * (pts[i].z - mz);
            suz += (cmb[i].z - mu) * (pts[i].z - mz);
        }
        std::printf("    correlation(CMB-frame v^2, depth) = %.3f\n", suz / std::sqrt(suu * szz2));
    }

    std::ofstream out(argv[2]);
    out << "index,date,N,z,day_since_20161213,value_ppb,sigma_ppb\n";
    for (auto& p : pts)
        out << p.idx << ',' << p.date << ',' << p.N << ',' << p.z << ',' << p.t << ',' << p.v << ',' << p.s << '\n';
    out << "# fit_all c=" << all.c << " k=" << all.k << " sk=" << all.sk << "\n";
    return 0;
}
