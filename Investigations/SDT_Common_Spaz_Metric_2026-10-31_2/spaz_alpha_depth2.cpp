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

        // ── W12c (post-registration, James): Earth above / below and ahead / behind the Sun ──
        // g_gal : Earth's heliocentric offset along the galactic north pole [AU]
        //         (NGP RA 192.85948 deg, Dec 27.12825 deg)
        // g_dip : Earth's heliocentric offset along the Sun's CMB motion [AU] (lead / trail)
        // Fits: single regressor, and depth + regressor jointly (3x3 normal equations).
        const double nra = 192.85948 * deg, nde = 27.12825 * deg;
        const double nx = std::cos(nde) * std::cos(nra), ny0 = std::cos(nde) * std::sin(nra), nz0 = std::sin(nde);
        const double Nx = nx, Ny = ny0 * std::cos(eps) + nz0 * std::sin(eps), Nz = -ny0 * std::sin(eps) + nz0 * std::cos(eps);
        const double Dx = vSx / vS, Dy = vSy / vS, Dz = vSz / vS;
        std::vector<double> ggal(pts.size()), gdip(pts.size());
        for (size_t i = 0; i < pts.size(); ++i) {
            const double dd = pts[i].t + days_from_civil(2016, 12, 13) - j2000;
            double x, y;
            earth(dd, x, y);
            const double AU = sdt::laws::measured::AU;
            ggal[i] = (x * Nx + y * Ny) / AU;
            gdip[i] = (x * Dx + y * Dy) / AU;
        }
        (void)Nz; (void)Dz;
        auto fit2 = [&](const std::vector<double>& g, const char* name) {
            // value = c + k1 (z - zbar) 1e9 + k2 g
            double A[3][3] = {}, b[3] = {};
            for (size_t i = 0; i < pts.size(); ++i) {
                const double w = 1 / (pts[i].s * pts[i].s);
                const double f[3] = {1.0, (pts[i].z - mz) * 1e9, g[i]};
                for (int r = 0; r < 3; ++r) { b[r] += w * f[r] * pts[i].v; for (int q = 0; q < 3; ++q) A[r][q] += w * f[r] * f[q]; }
            }
            // invert 3x3
            const double det = A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1]) - A[0][1] * (A[1][0] * A[2][2] - A[1][2] * A[2][0])
                             + A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);
            double I[3][3];
            I[0][0] = (A[1][1] * A[2][2] - A[1][2] * A[2][1]) / det; I[0][1] = (A[0][2] * A[2][1] - A[0][1] * A[2][2]) / det;
            I[0][2] = (A[0][1] * A[1][2] - A[0][2] * A[1][1]) / det; I[1][0] = (A[1][2] * A[2][0] - A[1][0] * A[2][2]) / det;
            I[1][1] = (A[0][0] * A[2][2] - A[0][2] * A[2][0]) / det; I[1][2] = (A[0][2] * A[1][0] - A[0][0] * A[1][2]) / det;
            I[2][0] = (A[1][0] * A[2][1] - A[1][1] * A[2][0]) / det; I[2][1] = (A[0][1] * A[2][0] - A[0][0] * A[2][1]) / det;
            I[2][2] = (A[0][0] * A[1][1] - A[0][1] * A[1][0]) / det;
            double p[3] = {};
            for (int r = 0; r < 3; ++r) for (int q = 0; q < 3; ++q) p[r] += I[r][q] * b[q];
            double chi = 0, gm = 0, gmin = 1e9, gmax = -1e9;
            for (size_t i = 0; i < pts.size(); ++i) {
                const double res = (pts[i].v - p[0] - p[1] * (pts[i].z - mz) * 1e9 - p[2] * g[i]) / pts[i].s;
                chi += res * res; gm += g[i]; gmin = std::min(gmin, g[i]); gmax = std::max(gmax, g[i]);
            }
            gm /= pts.size();
            double sgg = 0, szg = 0;
            for (size_t i = 0; i < pts.size(); ++i) { sgg += (g[i] - gm) * (g[i] - gm); szg += (g[i] - gm) * (pts[i].z - mz); }
            // single-regressor fit on g
            std::vector<Pt> gp = pts;
            for (size_t i = 0; i < pts.size(); ++i) gp[i].z = g[i] * 1e-9;
            const Fit fg = wls(gp);
            std::printf("    %-28s range %+.3f..%+.3f AU  corr(g, depth) %+.3f\n", name, gmin, gmax, szg / std::sqrt(sgg * szz2));
            std::printf("      alone        : k_g = %+.3f +- %.3f ppb/AU  chi2 = %.2f\n", fg.k, fg.sk, fg.chi2);
            std::printf("      with depth   : k_z = %+.2f +- %.2f   k_g = %+.3f +- %.3f ppb/AU  chi2 = %.2f (25 dof)\n",
                p[1], std::sqrt(I[1][1]), p[2], std::sqrt(I[2][2]), chi);
        };
        std::printf("\n  W12c Earth above/below and ahead/behind the Sun (post-registration)\n");
        fit2(ggal, "galactic above/below (g_gal)");
        fit2(gdip, "CMB lead/trail (g_dip)");

        // ── W12d (post-registration, James): speed relative to the Galactic Centre ──
        // Sun's velocity relative to Sgr A* in galactic (U toward GC, V rotation, W NGP):
        // U = 11.1, V = 233.4 + 12.24, W = 7.25 km/s (Schoenrich 2010 peculiar + Reid 2019
        // circular speed; MEASURED-INPUT, from memory, source check PENDING).
        const double Ug = 11.1e3, Vg = (233.4 + 12.24) * 1e3, Wg = 7.25e3;
        // galactic -> equatorial (J2000): eq = R gal (column 0 = Sgr A* direction, RA 266.4, Dec -28.9)
        const double R[3][3] = {{-0.0548755604, 0.4941094279, -0.8676661490},
                                {-0.8734370902, -0.4448296300, -0.1980763734},
                                {-0.4838350155, 0.7469822445, 0.4559837762}};
        const double gv[3] = {Ug, Vg, Wg};
        double eq[3] = {};
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) eq[i] += R[i][j] * gv[j];
        const double Gx = eq[0], Gy = eq[1] * std::cos(eps) + eq[2] * std::sin(eps), Gz = -eq[1] * std::sin(eps) + eq[2] * std::cos(eps);
        const double vG = std::sqrt(Gx * Gx + Gy * Gy + Gz * Gz);
        std::printf("\n  W12d speed relative to the Galactic Centre (post-registration)\n");
        std::printf("    Sun vs Sgr A*: %.1f km/s; ecliptic latitude of that motion %.1f deg -> "
            "Earth's 29.8 km/s projects at most %.1f km/s onto it\n", vG / 1e3,
            std::asin(Gz / vG) / deg, 29.78 * std::cos(std::asin(Gz / vG)));
        auto vgal = [&](double dd) {
            double x1, y1, x2, y2;
            earth(dd - 0.05, x1, y1); earth(dd + 0.05, x2, y2);
            const double vx = (x2 - x1) / (0.1 * 86400), vy = (y2 - y1) / (0.1 * 86400);
            return std::sqrt((Gx + vx) * (Gx + vx) + (Gy + vy) * (Gy + vy) + Gz * Gz);
        };
        double ymin = 1e9, ymax = 0; int dmin = 0, dmax = 0;
        const int y17 = days_from_civil(2017, 1, 1) - j2000;
        for (int d = 0; d < 365; ++d) {
            const double v = vgal(y17 + d);
            if (v < ymin) { ymin = v; dmin = d; }
            if (v > ymax) { ymax = v; dmax = d; }
        }
        std::printf("    over 2017: %.1f km/s (day %d) .. %.1f km/s (day %d of year)\n", ymin / 1e3, dmin + 1, ymax / 1e3, dmax + 1);
        std::vector<Pt> gp = pts;
        double cmin = 1e9, cmax = 0;
        for (size_t i = 0; i < pts.size(); ++i) {
            const double v = vgal(pts[i].t + days_from_civil(2016, 12, 13) - j2000);
            gp[i].z = v * v / (c * c) * 1e-2;
            cmin = std::min(cmin, v); cmax = std::max(cmax, v);
        }
        const Fit fgal = wls(gp);
        double mg = 0; for (auto& q : gp) mg += q.z; mg /= gp.size();
        double sgg = 0, sgz = 0;
        for (size_t i = 0; i < pts.size(); ++i) { sgg += (gp[i].z - mg) * (gp[i].z - mg); sgz += (gp[i].z - mg) * (pts[i].z - mz); }
        std::printf("    campaign: %.1f .. %.1f km/s; corr(v_gal^2, depth) = %+.3f\n", cmin / 1e3, cmax / 1e3, sgz / std::sqrt(sgg * szz2));
        std::printf("    galactic-frame v^2/c^2   : k = %+.3e +- %.3e  (%.1f sigma)  chi2 = %.2f\n",
            fgal.k * 1e-2, fgal.sk * 1e-2, std::abs(fgal.k) / fgal.sk, fgal.chi2);
    }

    std::ofstream out(argv[2]);
    out << "index,date,N,z,day_since_20161213,value_ppb,sigma_ppb\n";
    for (auto& p : pts)
        out << p.idx << ',' << p.date << ',' << p.N << ',' << p.z << ',' << p.t << ',' << p.v << ',' << p.s << '\n';
    out << "# fit_all c=" << all.c << " k=" << all.k << " sk=" << all.sk << "\n";
    return 0;
}
