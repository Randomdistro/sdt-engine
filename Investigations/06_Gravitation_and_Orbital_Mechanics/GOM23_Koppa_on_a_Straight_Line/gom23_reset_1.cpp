// GOM23 blank-slate run 1 (2026-10-10). Registration: GOM23_RESET_ASSESSMENT_2026-10-10.md sections 0-2 (written before this file existed).
//  Registration slip corrected before the run: P4 speeds were registered as 3e4 m/s (Sun) and 1e4 m/s (Earth), both below the escape speed at b (the "line" would be a hyperbolic dive).
//  Used: v = 3e7 m/s for the Sun (b = R_Sun) and v = 1e6 m/s for the Earth (b = R_Earth), where the deflection is a small fraction of v (4.2e-4, 1.3e-4).
//  P1 pi-audit; P2 I1 standing still is thrust, I2 clock tower, I3 photoionisation; P3 synthetic ascent; P4 null-steered line; P5 closure table (Earth, hydrogen; Sun PENDING).
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

static const double C = M::c;
static double simpson(double (*f)(double, void*), void* p, double a, double b, int n) { double h = (b - a) / n, s = f(a, p) + f(b, p); for (int i = 1; i < n; ++i) s += f(a + i * h, p) * (i % 2 ? 4.0 : 2.0); return s * h / 3.0; }
struct LineP { double K, b, v; };
static double lineIntegrand(double u, void* q) { LineP* p = (LineP*)q; double x = p->b * std::sinh(u); double r2 = p->b * p->b + x * x; return p->K * p->b / (r2 * std::sqrt(r2)) * (p->b * std::cosh(u)) / p->v; }   // a_perp dx/v with x = b sinh u
struct Tst { double b; };
static double tf(double u, void* q) { double b = ((Tst*)q)->b; return b * std::cosh(u) / std::pow(b * b + b * b * std::sinh(u) * std::sinh(u), 1.5); }
static double trajectory(double K, double b, double v, double X) {
    double x = -X, y = b, vx = v, vy = 0; auto acc = [&](double X1, double Y1, double& ax, double& ay) { double r2 = X1 * X1 + Y1 * Y1, r3 = r2 * std::sqrt(r2); ax = -K * X1 / r3; ay = -K * Y1 / r3; };
    long steps = 0; while (x < X && steps < 5000000) { double r = std::sqrt(x * x + y * y), sp = std::sqrt(vx * vx + vy * vy), dt = 2e-3 * r / sp; double a1x, a1y, a2x, a2y, a3x, a3y, a4x, a4y; acc(x, y, a1x, a1y);
        double x2 = x + 0.5 * dt * vx, y2 = y + 0.5 * dt * vy, vx2 = vx + 0.5 * dt * a1x, vy2 = vy + 0.5 * dt * a1y; acc(x2, y2, a2x, a2y);
        double x3 = x + 0.5 * dt * vx2, y3 = y + 0.5 * dt * vy2, vx3 = vx + 0.5 * dt * a2x, vy3 = vy + 0.5 * dt * a2y; acc(x3, y3, a3x, a3y);
        double x4 = x + dt * vx3, y4 = y + dt * vy3, vx4 = vx + dt * a3x, vy4 = vy + dt * a3y; acc(x4, y4, a4x, a4y);
        x += dt / 6 * (vx + 2 * vx2 + 2 * vx3 + vx4); y += dt / 6 * (vy + 2 * vy2 + 2 * vy3 + vy4); vx += dt / 6 * (a1x + 2 * a2x + 2 * a3x + a4x); vy += dt / 6 * (a1y + 2 * a2y + 2 * a3y + a4y); ++steps; }
    return vy; }   // transverse velocity change toward the source is negative in y; magnitude returned by caller

int main() {
    std::printf("GOM23 blank-slate run 1 (registered in GOM23_RESET_ASSESSMENT_2026-10-10.md sections 0-2)\n=======================================================================\n\n");
    int fails = 0;
    const double kE = bridge::koppa_Earth, kS = bridge::koppa_Sun, kH = bridge::koppa_hydrogen, RE = bridge::R_Earth, RS = M::R_Sun;
    const double g0 = 9.80665, gEq = 9.780327, gPole = 9.832186, Req = 6378137.0, omega = 7.292115e-5, hTower = 450.0, tower = 4.9e-14;
    const double Eion = 13.598434599702, Ry = 13.605693122994, eV = 1.602176634e-19;
    // validations
    { Tst t{3.7}; double X = 250.0, ua = std::asinh(X / t.b); double num = simpson(tf, &t, -ua, ua, 4000), an = 2 * X / (t.b * t.b * std::sqrt(t.b * t.b + X * X)); double e = std::fabs(num / an - 1); bool ok = e < 1e-10; std::printf("[V1] Simpson (x = b sinh u) against 2X/(b^2 sqrt(b^2 + X^2)): relative %.2e -> %s\n", e, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { // free fall energy conservation, a_prop = 0
        double r = RE, v = 0, K = C * C * kE; double E0 = 0.5 * v * v - K / r; double dt = 0.01; for (int i = 0; i < 30000; ++i) { auto a = [&](double rr) { return -K / (rr * rr); }; double k1r = v, k1v = a(r), k2r = v + 0.5 * dt * k1v, k2v = a(r + 0.5 * dt * k1r), k3r = v + 0.5 * dt * k2v, k3v = a(r + 0.5 * dt * k2r), k4r = v + dt * k3v, k4v = a(r + dt * k3r); r += dt / 6 * (k1r + 2 * k2r + 2 * k3r + k4r); v += dt / 6 * (k1v + 2 * k2v + 2 * k3v + k4v); }
        double E1 = 0.5 * v * v - K / r; double e = std::fabs((E1 - E0) / E0); bool ok = e < 1e-9; std::printf("[V2] RK4 free fall for 300 s from R_Earth: relative energy change %.2e -> %s\n", e, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    { bool ok = std::fabs(M::r_e - M::alpha * M::alpha * M::a_0) < 1e-30 && C == 299792458.0; std::printf("[V3] r_e = alpha^2 a_0 and c exact in laws.hpp -> %s\n\n", ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    // P1
    { struct Ch { const char* nm; const char* formula; const char* consumes; } ch[3] = {{"I1/I2 (Earth, force and clock)", "xi = g R^2 / c^2 ; dnu/nu = xi h / R^2", "g0, R_E, h, c"}, {"I3 (hydrogen, escape)", "xi = a0 / k^2 ; k = c / sqrt(2 E_ion / m_e)", "a0, E_ion, m_e, c"}, {"P3/P4 (extraction, line)", "xi = (a_prop - rddot) r^2 / c^2 ; dv_perp = 2 c^2 xi / (b v)", "a_prop, r(t), b, v, c"}};
      int pis = 0; for (auto& c : ch) { std::string s = c.formula; size_t p = 0; while ((p = s.find("pi", p)) != std::string::npos) { ++pis; p += 2; } std::printf("[P1] %-34s : %s ; consumes %s\n", c.nm, c.formula, c.consumes); }
      std::printf("[P1] occurrences of pi in the chain formulas: %d -> %s (VERIFICATION: by the form of the chains; the measured a0 and alpha carry h/2pi in their definitions)\n\n", pis, pis == 0 ? "zero" : "PRESENT"); }
    // P2 I1
    const double aPred = C * C * kE / (RE * RE);
    { bool g1 = std::fabs(aPred / g0 - 1) < 0.005, band = aPred >= gEq && aPred <= gPole; double aEq = C * C * kE / (Req * Req) - omega * omega * Req; bool g2 = std::fabs(aEq / gEq - 1) < 0.005; double rec = g0 * RE * RE / (C * C);
      std::printf("[I1] a = c^2 koppa_E / R_E^2 = %.5f m/s^2 against g0 = %.5f : %+.4f%% (gate 0.5%%: %s) ; inside the polar-equatorial band [%.6f, %.6f]: %s\n     equatorial: c^2 koppa_E/R_eq^2 = %.5f, centrifugal omega^2 R_eq = %.5f, difference %.5f against %.6f : %+.4f%% (gate 0.5%%: %s)\n     recovery koppa_rec = g0 R^2/c^2 = %.6e m against koppa_E = %.6e m : %+.4f%%\n", aPred, g0, (aPred / g0 - 1) * 100, g1 ? "met" : "NOT MET", gEq, gPole, band ? "yes" : "NO", C * C * kE / (Req * Req), omega * omega * Req, aEq, gEq, (aEq / gEq - 1) * 100, g2 ? "met" : "NOT MET", rec, kE, (rec / kE - 1) * 100); if (!g1 || !g2) ++fails; }
    // I2
    { double d = kE * hTower / (RE * RE), gh = g0 * hTower / (C * C); bool a = std::fabs(d / gh - 1) < 0.01, b = std::fabs(d / tower - 1) < 0.02; std::printf("[I2] tower h = %.0f m: koppa_E h/R^2 = %.4e ; g0 h/c^2 = %.4e (ratio %.5f, gate 1%%: %s) ; measured class %.1e (%+.3f%%, gate 2%%: %s)\n", hTower, d, gh, d / gh, a ? "met" : "NOT MET", tower, (d / tower - 1) * 100, b ? "met" : "NOT MET"); if (!a || !b) ++fails; }
    // I3
    { double k = C / std::sqrt(2 * Eion * eV / M::m_e), kInf = C / std::sqrt(2 * Ry * eV / M::m_e); double kh = M::a_0 / (k * k), khInf = M::a_0 / (kInf * kInf); bool ok = std::fabs(kh / kH - 1) < 0.001; std::printf("[I3] k = c/sqrt(2 E_ion/m_e) = %.5f (1/alpha = %.5f) ; koppa_H,rec = a0/k^2 = %.6e m against r_e = %.6e m : %+.4f%% (gate 0.1%%: %s)\n     with the infinite-mass Rydberg energy: koppa = %.6e m, %+.2e relative to r_e (the finite-proton seat offset is %+.4f%%)\n\n", k, 1.0 / M::alpha, kh, kH, (kh / kH - 1) * 100, ok ? "met" : "NOT MET", khInf, khInf / kH - 1, (kh / khInf - 1) * 100); if (!ok) ++fails; }
    // P3
    { const double T = 300, dt = 0.01; const int n = int(T / dt); const double K = C * C * kE; std::vector<double> r(n + 1), ap(n + 1); double rr = RE, vv = 0;
      auto aprop = [&](double t) { return 15.0 + 10.0 * t / T; };
      for (int i = 0; i <= n; ++i) { double t = i * dt; r[i] = rr; ap[i] = aprop(t); auto a = [&](double tt, double q) { return aprop(tt) - K / (q * q); }; double k1r = vv, k1v = a(t, rr), k2r = vv + 0.5 * dt * k1v, k2v = a(t + 0.5 * dt, rr + 0.5 * dt * k1r), k3r = vv + 0.5 * dt * k2v, k3v = a(t + 0.5 * dt, rr + 0.5 * dt * k2r), k4r = vv + dt * k3v, k4v = a(t + dt, rr + dt * k3r); rr += dt / 6 * (k1r + 2 * k2r + 2 * k3r + k4r); vv += dt / 6 * (k1v + 2 * k2v + 2 * k3v + k4v); }
      double s = 0; int m = 0; double worst = 0; for (int i = 1; i < n; ++i) { double rdd = (r[i + 1] - 2 * r[i] + r[i - 1]) / (dt * dt); double xi = (ap[i] - rdd) * r[i] * r[i] / (C * C); s += xi; ++m; worst = std::max(worst, std::fabs(xi / kE - 1)); }
      double mean = s / m; bool ok = std::fabs(mean / kE - 1) < 0.001; std::printf("[P3] synthetic ascent: r from %.0f to %.0f m in %.0f s ; mean recovered koppa = %.6e m against injected %.6e m : %+.3e (gate 0.1%%: %s) ; worst single sample %.2e\n     required kinematic precision for 0.1%%: delta a < %.3f m/s^2 (accelerometer bias, drag and thrust alignment must be below it)\n\n", r[0], r[n], T, mean, kE, mean / kE - 1, ok ? "met" : "NOT MET", worst, 0.001 * K / (RE * RE)); if (!ok) ++fails; }
    // P4
    struct Cs { const char* nm; double K, b, v; } cs[2] = {{"Sun, v = 3e7 m/s", C * C * kS, RS, 3.0e7}, {"Earth, v = 1e6 m/s", C * C * kE, RE, 1.0e6}};
    for (auto& c : cs) { double closed = 2 * c.K / (c.b * c.v); for (double xb : {1e3, 1e4}) { LineP p{c.K, c.b, c.v}; double ua = std::asinh(xb), num = simpson(lineIntegrand, &p, -ua, ua, 8000), ex = closed * xb / std::sqrt(1 + xb * xb); bool ok = std::fabs(num / closed - 1) < 0.005;
            std::printf("[P4] %-20s X/b = %.0e : line integral %.6e m/s ; closed form 2 c^2 koppa/(b v) = %.6e m/s ; relative %+.2e (gate 0.5%%: %s) ; finite-X exact %.6e\n", c.nm, xb, num, closed, num / closed - 1, ok ? "met" : "NOT MET", ex); if (!ok) ++fails; }
        double vy = trajectory(c.K, c.b, c.v, 1e3 * c.b); std::printf("     trajectory integration (RK4, step ~ r/v): transverse velocity change %.6e m/s, relative to the closed form %+.3e (descriptive; deflection/v = %.1e)\n", -vy, -vy / closed - 1, closed / c.v); }
    // P5
    { double rec = g0 * RE * RE / (C * C), kh = M::a_0 / std::pow(C / std::sqrt(2 * Eion * eV / M::m_e), 2); std::printf("\n[P5] closure table (straight-line recovery against the circular-ladder anchor):\n  Earth    : %.6e m against %.6e m : %+.4f%% (gate 1%%: %s)\n  hydrogen : %.6e m against %.6e m : %+.4f%% (gate 1%%: %s)\n  Sun      : PENDING (no straight-line measurement of the Sun's koppa in the local data that is not a fitted post-Newtonian coefficient)\n", rec, kE, (rec / kE - 1) * 100, std::fabs(rec / kE - 1) < 0.01 ? "met" : "NOT MET", kh, kH, (kh / kH - 1) * 100, std::fabs(kh / kH - 1) < 0.01 ? "met" : "NOT MET"); }
    std::printf("\nAnchors: koppa_Earth = %.6e m, koppa_Sun = %.4f m, koppa_hydrogen = %.6e m\n", kE, kS, kH);
    return fails ? 1 : 0;
}
