// Demonstrations of the algebraic structures found in the pasted text (2026-10-08). Two demonstrations (A, B) per structure.
// Engine constants from sdt::laws. External constants are marked [ext] (CODATA/IAU/textbook values used only to illustrate a formula) or [B] (from memory, to be checked).
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <numbers>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = std::numbers::pi;
static const double c = M::c;
// [ext] illustrative constants
static const double EPS0 = 8.8541878128e-12, MU0 = 1.25663706212e-6, GNEWT = 6.67430e-11;
static const double SOLAR_CONST = 1361.0, R_EARTH = 6.371e6, G_SURF = 9.80665, M_EARTH = 5.972e24;
static double gam(double b) { return 1.0 / std::sqrt(1 - b * b); }

int main() {
    std::printf("Algebraic structures of the pasted text: two demonstrations each (2026-10-08)\n=============================================================================\n\n");
    int fails = 0;
    // ---- validation: finite-difference second derivative on a known function; Simpson quadrature on a known integral
    { double h = 1e-4, x = 0.7, d2 = (std::sin(x + h) - 2 * std::sin(x) + std::sin(x - h)) / (h * h) + std::sin(x);
      int n = 100000; double s = 0, a = 0, b = PI, dx = (b - a) / n; for (int i = 0; i <= n; ++i) s += std::sin(a + i * dx) * ((i == 0 || i == n) ? 1 : (i % 2 ? 4 : 2)); s *= dx / 3;
      bool v = std::fabs(d2) < 1e-6 && std::fabs(s - 2) < 1e-9; std::printf("[V] finite-difference d2 residual %.2e ; Simpson integral of sin on [0,pi] = %.12f -> %s\n\n", d2, s, v ? "met" : "NOT MET"); if (!v) ++fails; }
    if (fails) return 1;
    const double kopS = bridge::koppa_Sun_from_precession, R_S = M::R_Sun, lP = M::l_P, R0 = 8.4e-16;

    // ===================== A. kinematics and dynamics =====================
    std::printf("A1 gamma = (1 - v^2/c^2)^(-1/2)\n");
    std::printf("  A: gamma at beta = 0.1, 0.5, 0.9, 0.99, 0.999: "); for (double b : {0.1, 0.5, 0.9, 0.99, 0.999}) std::printf("%.6f ", gam(b)); std::printf("\n");
    { double b = 30e3 / c, g1 = b * b / (std::sqrt(1 - b * b) * (1 + std::sqrt(1 - b * b))); std::printf("  B: v = 30 km/s: gamma - 1 = %.6e ; series beta^2/2 = %.6e ; ratio %.9f\n\n", g1, 0.5 * b * b, g1 / (0.5 * b * b)); }
    std::printf("A2 longitudinal and transverse masses m_par = gamma^3 m, m_perp = gamma m\n");
    for (double b : {0.5, 0.9, 0.99}) std::printf("  A: beta = %.2f : m_par/m = %.4f, m_perp/m = %.4f (Einstein 1905 transverse gamma^2 m = %.4f)\n", b, std::pow(gam(b), 3), gam(b), gam(b) * gam(b));
    { double b = 0.9, h = 1e-5, p1 = gam(b + h) * (b + h), p0 = gam(b - h) * (b - h), dpdv = (p1 - p0) / (2 * h);
      double w = 0.37, dt = 1e-6, px = gam(b) * b * std::cos(w * dt), py = gam(b) * b * std::sin(w * dt), dpx = px - gam(b) * b, dpy = py, dp = std::sqrt(dpx * dpx + dpy * dpy) / dt, acc = b * w;
      std::printf("  B: dp/dv by central difference at beta = 0.9: %.8f ; gamma^3 = %.8f (relative %.1e) ; circular motion: |dp/dt|/(v omega) = %.8f against gamma = %.8f\n\n", dpdv, std::pow(gam(b), 3), std::fabs(dpdv / std::pow(gam(b), 3) - 1), dp / acc, gam(b)); }
    std::printf("A3 P^mu = m U^mu, E = gamma m c^2, p = gamma m v, E^2 - p^2 c^2 = m^2 c^4\n");
    for (double b : {0.1, 0.9, 0.999}) { double m = M::m_e, E = gam(b) * m * c * c, p = gam(b) * m * b * c; std::printf("  A: beta = %.3f : (E^2 - p^2 c^2)/(m^2 c^4) - 1 = %+.1e (electron)\n", b, (E * E - p * p * c * c) / (m * m * std::pow(c, 4)) - 1); }
    for (double b : {0.01, 0.1}) std::printf("  B: beta = %.2f : (E - mc^2)/((1/2) m v^2) = %.8f ; series 1 + 3 beta^2/4 = %.8f\n", b, (gam(b) - 1) / (0.5 * b * b), 1 + 0.75 * b * b);
    std::printf("\nA4 U^mu U_mu = -c^2 (hyperbolic constraint)\n");
    { double b[3] = {0.3, 0.4, 0.1}, bb = std::sqrt(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]), g = gam(bb), U0 = g * c, Ux = g * b[0] * c, Uy = g * b[1] * c, Uz = g * b[2] * c;
      double B = 0.6, gB = gam(B), U0p = gB * (U0 - B * Ux / 1.0), Uxp = gB * (Ux - B * U0); double inv = -U0 * U0 + Ux * Ux + Uy * Uy + Uz * Uz, invp = -U0p * U0p + Uxp * Uxp + Uy * Uy + Uz * Uz;
      std::printf("  A: U^2/c^2 before boost = %.12f, after a boost of 0.6 c along x = %.12f (both -1)\n", inv / (c * c), invp / (c * c)); }
    { double e1 = std::atanh(0.5), e2 = std::atanh(0.7); std::printf("  B: rapidities add: tanh(eta1 + eta2) = %.10f ; (b1 + b2)/(1 + b1 b2) = %.10f ; cosh^2 - sinh^2 = %.12f\n\n", std::tanh(e1 + e2), (0.5 + 0.7) / (1 + 0.35), std::cosh(e1) * std::cosh(e1) - std::sinh(e1) * std::sinh(e1)); }
    std::printf("A5 null cone s^2 = -c^2 (t - t0)^2 + |x - x0|^2 = 0 and the lookback radius r = c (t0 - t)\n");
    { double yr = 365.25 * 86400, r = c * yr, s2 = -c * c * yr * yr + r * r; std::printf("  A: one year of lookback: r = %.6e m = %.6f light-years ; s^2/(c^2 dt^2) = %.1e\n", r, r / (c * yr * 1.0), s2 / (c * c * yr * yr)); }
    { double dt = 3.0, dx = 1.0 * c, dy = 0.5 * c, s2 = -c * c * dt * dt + dx * dx + dy * dy, B = 0.8, g = gam(B), dtp = g * (dt - B * dx / c), dxp = g * (dx - B * c * dt), s2p = -c * c * dtp * dtp + dxp * dxp + dy * dy;
      std::printf("  B: s^2 invariant under a boost of 0.8 c: %.10e and %.10e (relative difference %.1e)\n\n", s2, s2p, std::fabs(s2p / s2 - 1)); }

    // ===================== B. electromagnetism and wave structure =====================
    std::printf("B1 c = 1/sqrt(eps0 mu0): speed = sqrt(stiffness/density)\n");
    std::printf("  A [ext]: 1/sqrt(eps0 mu0) = %.6f m/s against c = %.6f m/s (relative %.1e)\n", 1 / std::sqrt(EPS0 * MU0), c, 1 / std::sqrt(EPS0 * MU0) / c - 1);
    std::printf("  B [ext]: sqrt(gamma P/rho), air 1.4, 101325 Pa, 1.204 kg/m^3 = %.1f m/s ; sqrt(K/rho), water 2.2e9 Pa, 998 = %.0f m/s ; sqrt(E/rho), steel rod 200e9 Pa, 7850 = %.0f m/s\n\n", std::sqrt(1.4 * 101325 / 1.204), std::sqrt(2.2e9 / 998), std::sqrt(200e9 / 7850));
    std::printf("B2 Maxwell stress tensor T_ij = eps0 (E_i E_j - (1/2) delta_ij E^2) + (1/mu0)(B_i B_j - (1/2) delta_ij B^2)\n");
    { double E = 1e6, Tzz = EPS0 * (E * E - 0.5 * E * E), Txx = EPS0 * (0 - 0.5 * E * E); std::printf("  A [ext]: static field E = 1e6 V/m along z: T_zz = %.4f Pa (tension along the lines) = eps0 E^2/2 = %.4f ; T_xx = %.4f Pa (pressure across)\n", Tzz, 0.5 * EPS0 * E * E, Txx); }
    { const double u = law_I::u_CMB; double acc[3] = {0, 0, 0}; int N = 0; // isotropic radiation: average momentum-flux diagonal over directions
      for (int i = 0; i < 400; ++i) for (int j = 0; j < 800; ++j) { double mu = -1 + 2 * (i + 0.5) / 400, ph = 2 * PI * (j + 0.5) / 800, st = std::sqrt(1 - mu * mu), n[3] = {st * std::cos(ph), st * std::sin(ph), mu}; for (int k = 0; k < 3; ++k) acc[k] += u * n[k] * n[k]; ++N; }
      std::printf("  B: isotropic radiation, momentum flux Pi_ii = u <n_i^2> = %.6e, %.6e, %.6e Pa ; u/3 = %.6e ; engine law_I::P_rad = %.6e (u = a T^4 = %.5e J/m^3)\n\n", acc[0] / N, acc[1] / N, acc[2] / N, u / 3, law_I::P_rad, u); }
    std::printf("B3 time-averaged flux <T_rr> = (1/2)(eps0 <E^2> + <B^2>/mu0)\n");
    { double I = SOLAR_CONST, E0 = std::sqrt(2 * I / (c * EPS0)), B0 = E0 / c, avg = 0.5 * (EPS0 * E0 * E0 / 2 + B0 * B0 / 2 / MU0); std::printf("  A [ext]: solar constant 1361 W/m^2: E0 = %.2f V/m, B0 = %.3e T ; <T_rr> = %.6e Pa ; I/c = %.6e Pa (absorber pressure); reflector 2I/c = %.6e Pa\n", E0, B0, avg, I / c, 2 * I / c); }
    { double u = law_I::u_CMB; std::printf("  B: CMB beam (one direction): pressure u = %.5e Pa ; isotropic: u/3 = %.5e Pa ; ratio of a beam to the isotropic pressure = %.3f\n\n", u, u / 3, 3.0); }
    std::printf("B4 Helmholtz: laplacian(psi) + k^2 psi = 0, and the Fresnel number F = a^2/(lambda L)\n");
    { double k = 2 * PI, h = 1e-3, x = 0.37, psi = std::cos(k * x), d2 = (std::cos(k * (x + h)) - 2 * psi + std::cos(k * (x - h))) / (h * h), res1 = d2 + k * k * psi;
      double r = 1.3, f = [&](double rr) { return std::sin(k * rr); }(r), d2f = (std::sin(k * (r + h)) - 2 * f + std::sin(k * (r - h))) / (h * h), res2 = d2f + k * k * f;  // (1/r) d2(r psi)/dr2 with psi = e^{ikr}/r: r psi = e^{ikr}
      std::printf("  A: plane wave residual %.1e (relative to k^2 psi = %.3f) ; spherical wave e^{ikr}/r, (1/r) d2(r psi)/dr2 + k^2 psi: residual %.1e\n", res1, k * k * psi, res2); }
    { struct Cs { const char* nm; double a, L, lam; } cs[] = {{"Earth, 1 AU, lambda = l_P", R_EARTH, M::AU, lP}, {"Earth, 1 AU, lambda = 1.06 mm (CMB peak)", R_EARTH, M::AU, 1.06e-3}, {"baryon (0.84 fm), 1 m, lambda = 1.06 mm", 8.4e-16, 1.0, 1.06e-3}, {"baryon (0.84 fm), 1 m, lambda = l_P", 8.4e-16, 1.0, lP}};
      for (auto& x : cs) std::printf("  B: %-44s F = %.3e (%s)\n", x.nm, x.a * x.a / (x.lam * x.L), x.a * x.a / (x.lam * x.L) > 1 ? "geometric shadow persists" : "diffraction fills the shadow"); std::printf("\n"); }
    std::printf("B5 dispersion omega(k) and group velocity v_g = d omega/dk\n");
    { double wp = 1.0; for (double w : {2.0, 1.1, 1.001}) { double vg = std::sqrt(1 - wp * wp / (w * w)), vp = 1 / vg; std::printf("  A: plasma omega^2 = c^2 k^2 + wp^2, omega = %.3f wp : v_g/c = %.5f, v_p/c = %.5f, v_p v_g/c^2 = %.10f\n", w, vg, vp, vg * vp); } }
    for (double kl : {0.5 * PI, PI * (1 - 1e-3), PI * (1 - 1e-6)}) std::printf("  B: discrete chain omega = (2c/l) sin(k l/2), k l = %.6f : v_g/c = cos(k l/2) = %.6e (v_g -> 0 at the zone edge k = pi/l)\n", kl, std::cos(kl / 2));
    std::printf("\n");

    // ===================== C. a moving body in radiation =====================
    std::printf("C1 Doppler factor D(theta) = sqrt(1 - beta^2)/(1 - beta cos theta)\n");
    { double b = 370e3 / c, T0 = M::T_CMB; double Df = std::sqrt((1 + b) / (1 - b)), Db = std::sqrt((1 - b) / (1 + b)), Dp = std::sqrt(1 - b * b);
      std::printf("  A: v = 370 km/s (beta = %.4e): forward D = %.8f -> T = %.6f K, dipole T0 (D - 1) = %.4f mK (to first order T0 beta = %.4f mK)\n", b, Df, T0 * Df, T0 * (Df - 1) * 1e3, T0 * b * 1e3);
      std::printf("  B: backward D = %.8f ; D(0)/D(pi) = %.8f = (1+beta)/(1-beta) = %.8f ; transverse D(90 deg) = %.10f = 1/gamma = %.10f\n\n", Db, Df / Db, (1 + b) / (1 - b), Dp, 1 / gam(b)); }
    std::printf("C2 momentum-flux integral over the sphere and the drag F = -(4/3) u sigma beta\n");
    { auto Fint = [&](double b) { int n = 200000; double s = 0, g = gam(b); for (int i = 0; i < n; ++i) { double mu = -1 + 2 * (i + 0.5) / n; s += mu * std::pow(g * (1 - b * mu), -4); } return -0.5 * s * 2.0 / n; };  // F/(u sigma) = -(1/2) integral mu [g(1-b mu)]^-4 dmu
      for (double b : {1e-3, 1e-2, 0.1, 0.5}) std::printf("  A: beta = %-6.3f : F/(u sigma) = %.8e ; -(4/3) beta = %.8e ; ratio %.6f\n", b, Fint(b), -4.0 / 3 * b, Fint(b) / (-4.0 / 3 * b));
      double vE = 29.78e3, b = vE / c, sigma = PI * R_EARTH * R_EARTH, F = 4.0 / 3 * law_I::u_CMB * sigma * b, Fg = M_EARTH * vE * vE / M::AU;
      std::printf("  B [ext]: the Earth (sigma = pi R^2 = %.3e m^2, v = 29.78 km/s): CMB drag F = %.3e N ; the centripetal force M v^2/AU = %.3e N ; ratio %.1e\n\n", sigma, F, Fg, F / Fg); }
    std::printf("C3 Fresnel drag v' = c/n + v (1 - 1/n^2)\n");
    { double n = 1.333, v = 7.0, ex = (c / n + v) / (1 + v / (n * c)) - c / n, fr = v * (1 - 1 / (n * n)); std::printf("  A [ext]: water n = 1.333, v = 7 m/s: drag v(1 - 1/n^2) = %.6f m/s (coefficient %.4f) ; exact relativistic velocity addition gives %.6f m/s (relative %.1e)\n", fr, 1 - 1 / (n * n), ex, ex / fr - 1); }
    { double n = 1.5, v = 0.5 * c, ex = (c / n + v) / (1 + v / (n * c)) - c / n, fr = v * (1 - 1 / (n * n)); std::printf("  B: limits: n = 1 gives %.1f, n -> infinity gives v ; at v = 0.5c, n = 1.5 the first-order formula gives %.4f c and the exact addition %.4f c\n\n", 0.0, fr / c, ex / c); }

    // ===================== D. gravitation =====================
    std::printf("D1 orbit equation d2u/dphi2 + u = GM/h^2 + 3 GM u^2/c^2 (u = 1/r; with koppa: GM = c^2 koppa)\n");
    auto integ = [&](double u0, double up0, double Ufun, double three, double phimax, int steps, std::vector<double>* out) { // integrate u'' = -u + Ufun + three*koppa_u^2 with koppa = 1
        double u = u0, p = up0, h = phimax / steps; for (int i = 0; i < steps; ++i) { auto f = [&](double uu, double) { return -uu + Ufun + three * uu * uu; };
            double k1u = p, k1p = f(u, p), k2u = p + 0.5 * h * k1p, k2p = f(u + 0.5 * h * k1u, 0), k3u = p + 0.5 * h * k2p, k3p = f(u + 0.5 * h * k2u, 0), k4u = p + h * k3p, k4p = f(u + h * k3u, 0);
            u += h / 6 * (k1u + 2 * k2u + 2 * k3u + k4u); p += h / 6 * (k1p + 2 * k2p + 2 * k3p + k4p); if (out) out->push_back(u); } return u; };
    { double a = bridge::a_Mercury / kopS, e = bridge::e_Mercury, U = 1.0 / (a * (1 - e * e)); // units of koppa
      int N = 40, spo = 200000; double dphi = 2 * PI / spo, u = 1.0 / (a * (1 - e)), p = 0, ph = 0; std::vector<double> peri;
      auto f = [&](double uu) { return -uu + U + 3.0 * uu * uu; };
      double pp = p; (void)pp; double uprev = u, pprev = p; int orbit = 0; long long step = 0;
      while (orbit < N + 1) { double k1u = p, k1p = f(u), k2u = p + 0.5 * dphi * k1p, k2p = f(u + 0.5 * dphi * k1u), k3u = p + 0.5 * dphi * k2p, k3p = f(u + 0.5 * dphi * k2u), k4u = p + dphi * k3p, k4p = f(u + dphi * k3u);
          double nu = u + dphi / 6 * (k1u + 2 * k2u + 2 * k3u + k4u), np = p + dphi / 6 * (k1p + 2 * k2p + 2 * k3p + k4p); ++step; ph = step * dphi; if (pprev > 0 && np <= 0 && ph > PI) { double fr = pprev / (pprev - np); peri.push_back((step - 1) * dphi + fr * dphi); ++orbit; }
          pprev = p = np; uprev = u = nu; (void)uprev; }
      double prec = (peri.back() - peri.front()) / (peri.size() - 1) - 2 * PI, an = 6 * PI / (a * (1 - e * e));
      std::printf("  A: Mercury (a, e from the engine, koppa = %.4f m), 40 orbits: perihelion advance %.6e rad/orbit = %.4f arcsec/century ; 6 pi koppa/(a(1-e^2)) = %.6e (relative %.1e)\n", kopS, prec, prec * bridge::mercury_orbits_per_cy * 180 * 3600 / PI, an, prec / an - 1); }
    { double u0 = 1.0 / 3.0, res = -u0 + 3 * u0 * u0; double pert = 1e-8; std::vector<double> tr; double uend = integ(u0 * (1 + pert), 0, 0.0, 3.0, 5.0, 50000, &tr);
      std::printf("  B: photon sphere: u = koppa/(3 koppa) solves u'' = -u + 3 u^2 = 0 (residual %.1e) ; a perturbation 1e-8 grows to %.3e of u0 over 5 radians (cosh(5) = %.2f, unstable)\n\n", res, (uend - u0) / u0 / pert, std::cosh(5.0)); }
    std::printf("D2 light deflection: scalar form 2 GM/(c^2 b) against tensor form 4 GM/(c^2 b)\n");
    { double b = R_S / kopS; // in units of koppa
      auto defl = [&](double three) { double u = 0, p = 1.0 / b, h = 1e-4, ph = 0; double prevu = u; while (true) { auto f = [&](double uu) { return -uu + three * uu * uu; };
            double k1u = p, k1p = f(u), k2u = p + 0.5 * h * k1p, k2p = f(u + 0.5 * h * k1u), k3u = p + 0.5 * h * k2p, k3p = f(u + 0.5 * h * k2u), k4u = p + h * k3p, k4p = f(u + h * k3u);
            double nu = u + h / 6 * (k1u + 2 * k2u + 2 * k3u + k4u), np = p + h / 6 * (k1p + 2 * k2p + 2 * k3p + k4p); ph += h; if (ph > 0.5 && nu <= 0) { double fr = prevu / (prevu - nu); return ph - h + fr * h - PI; } prevu = nu; u = nu; p = np; } };
      double dt = defl(3.0), dn = 4.0 / b; std::printf("  A: Sun, b = R_Sun: integrating u'' + u = 3 koppa u^2: deflection %.6e rad = %.4f arcsec ; 4 koppa/b = %.6e rad = %.4f arcsec (relative %.1e)\n", dt, dt * 180 * 3600 / PI, dn, dn * 180 * 3600 / PI, dt / dn - 1);
      std::printf("  B: the scalar-index (1911) value 2 koppa/b = %.6e rad = %.4f arcsec ; tensor/scalar = %.4f\n\n", 2.0 / b, 2.0 / b * 180 * 3600 / PI, dt / (2.0 / b)); }
    std::printf("D3 time dilation dtau = dt (1 + Phi/c^2) (Phi = -c^2 koppa/r), g00 = -(1 + 2 Phi/c^2)\n");
    { double x = kopS / R_S, exact = std::sqrt(1 - 2 * x), lin = 1 - x; std::printf("  A: Sun surface: koppa/R = %.6e ; sqrt(1 - 2 koppa/R) = %.15f ; 1 - koppa/R = %.15f ; difference %.2e (second order) ; note: the paste writes (1 - Phi/c^2) with Phi the positive magnitude and (1 + Phi/c^2), (1 + 2 Phi/c^2) with Phi negative\n", x, exact, lin, exact - lin); }
    { double GME = G_SURF * R_EARTH * R_EARTH, rg = 26571e3, vg = 3874.0, dg = GME / (c * c) * (1 / R_EARTH - 1 / rg) * 86400 * 1e6, ds = -0.5 * vg * vg / (c * c) * 86400 * 1e6; std::printf("  B [ext, B]: GPS: GM from g R^2 = %.4e m^3/s^2 ; gravitational offset %+.2f us/day ; velocity offset %+.2f us/day ; net %+.2f us/day\n\n", GME, dg, ds, dg + ds); }
    std::printf("D4 Einstein 1911 scalar form c(r) = c0 (1 + Phi/c^2) and the delay it implies\n");
    { double z = kopS / R_S; std::printf("  A: at the Sun's surface c(R) = c (1 - z) : c z = %.3f m/s lower (z = %.6e)\n", c * z, z); }
    { double b = 1.5 * R_S, r1 = M::AU, r2 = 1.52 * M::AU, x1 = std::sqrt(r1 * r1 - b * b), x2 = std::sqrt(r2 * r2 - b * b), L = std::asinh(x1 / b) + std::asinh(x2 / b);
      for (double a : {1.0, 2.0}) std::printf("  B: radar path Earth (1 AU) to 1.52 AU, impact parameter 1.5 R_Sun: a = %.0f: one-way delay (a koppa/c) L = %.3f us, round trip %.3f us (L = %.4f)\n", a, a * kopS / c * L * 1e6, 2 * a * kopS / c * L * 1e6, L); std::printf("\n"); }

    // ===================== E. phase and throughput =====================
    std::printf("E1 phase lag delta_phi = omega delta_t = omega (d/v - d/c)\n");
    { double d = 1e-3, n = 1.5, lam = 500e-9, dphi = 2 * PI * d * (n - 1) / lam; std::printf("  A [ext]: glass plate 1 mm, n = 1.5, 500 nm: delta_phi = %.2f rad = %.1f cycles\n", dphi, dphi / (2 * PI)); }
    { double d = 1e-3, n = 1.5; std::printf("  B: delta_t = d (n - 1)/c = %.4e s, the same for 400, 500, 700 nm: %.4e, %.4e, %.4e s (delta_phi/omega with omega = 2 pi c/lambda)\n\n", d * (n - 1) / c, (2 * PI * d * (n - 1) / 400e-9) / (2 * PI * c / 400e-9), (2 * PI * d * (n - 1) / 500e-9) / (2 * PI * c / 500e-9), (2 * PI * d * (n - 1) / 700e-9) / (2 * PI * c / 700e-9)); }
    std::printf("E2 conservation of throughput: closed integral S.dA in = closed integral S.dA out\n");
    { double Ptot = 1.0; std::printf("  A: point source P = 1 W: flux through spheres of radius 1, 10, 1e3 m: "); for (double r : {1.0, 10.0, 1e3}) std::printf("%.12f ", Ptot / (4 * PI * r * r) * 4 * PI * r * r); std::printf("W\n"); }
    { double n = 1.5, R = std::pow((n - 1) / (n + 1), 2); double minT = 1, maxT = 0, worst = 0; for (int i = 0; i <= 1000; ++i) { double del = 2 * PI * i / 1000, F = 4 * R / std::pow(1 - R, 2), T = 1 / (1 + F * std::pow(std::sin(del / 2), 2)), Rr = F * std::pow(std::sin(del / 2), 2) / (1 + F * std::pow(std::sin(del / 2), 2)); minT = std::min(minT, T); maxT = std::max(maxT, T); worst = std::max(worst, std::fabs(T + Rr - 1)); }
      std::printf("  B: lossless slab n = 1.5 (Airy): T ranges %.4f .. %.4f with the phase; worst |T + R - 1| = %.1e (all the throughput is transmitted or reflected)\n\n", minT, maxT, worst); }
    std::printf("E3 cosmic shell: T = T0 (1 + z), area ~ (1 + z)^-2, octave 1 + z = 2^n\n");
    { double T0 = M::T_CMB; std::printf("  A: T(z = 1100) = T0 (1 + z) = %.2f K ; the z for 3000 K: 1 + z = %.2f\n", T0 * 1101, 3000.0 / T0); }
    { double z = 1100; std::printf("  B: area ratio (1 + z)^-2 = %.4e ; octaves n = log2(1 + z) = %.4f ; T0 2^10 = %.1f K ; 2^n = %.4f\n\n", std::pow(1 + z, -2), std::log2(1 + z), M::T_CMB * 1024, std::pow(2, std::log2(1 + z))); }

    // ===================== F. the displacement construct =====================
    std::printf("F1 Planck length l_P = sqrt(hbar G/c^3) and the Planck force c^4/G\n");
    { double lp = std::sqrt(M::hbar * GNEWT / (c * c * c)); std::printf("  A [ext G]: sqrt(hbar G/c^3) = %.6e m against the engine l_P = %.6e m (relative %.1e, the uncertainty of G is 2e-5) ; c^4/G = %.5e N\n", lp, lP, lp / lP - 1, std::pow(c, 4) / GNEWT); }
    { double FP = std::pow(c, 4) / GNEWT, EP = std::sqrt(M::hbar * std::pow(c, 5) / GNEWT); std::printf("  B [ext G]: (c^4/G) l_P = %.5e J ; sqrt(hbar c^5/G) = %.5e J = %.4e GeV (equal)\n\n", FP * std::sqrt(M::hbar * GNEWT / (c * c * c)), EP, EP / M::MeV_to_J / 1e3); }
    std::printf("F2 N_disp = Omega0/v0 = 8 (R0/l_P)^3 with v0 = (pi/6) l_P^3\n");
    for (double R : {R0, law_III::R_p_lock}) { double Om = 4.0 / 3 * PI * R * R * R; std::printf("  A: R0 = %.5e m : Omega0 = %.4e m^3, N_disp = %.4e\n", R, Om, Om / (PI / 6 * lP * lP * lP)); }
    { double Om = 4.0 / 3 * PI * R0 * R0 * R0, l3 = lP * lP * lP; std::printf("  B: cell choices for Omega0 at R0 = 8.4e-16 m: sphere volume (pi/6) l^3: %.4e ; face-centred cell l^3/sqrt2: %.4e ; cubic cell l^3: %.4e\n\n", Om / (PI / 6 * l3), Om / (l3 / std::sqrt(2.0)), Om / l3); }
    std::printf("F3 shell capacity N_cap(r) = 4 pi r^2 l_P / v0 = 24 (r/l_P)^2\n");
    for (double r : {R0, 1e-9}) std::printf("  A: r = %.3e m : N_cap = %.4e\n", r, 24 * std::pow(r / lP, 2));
    for (double n : {1e3, 1e6}) { double sum = 4.0 * n * (n + 1) * (2 * n + 1), cl = 8 * n * n * n; std::printf("  B: n = %.0e shells of thickness l_P: exact sum of 24 j^2 = 4n(n+1)(2n+1) = %.6e ; 8 n^3 = %.6e ; ratio %.6f (1 + 1.5/n + ... = %.6f)\n", n, sum, cl, sum / cl, 1 + 1.5 / n + 0.5 / (n * n)); }
    std::printf("\nF4 conserved-volume displacement u(r) = Omega0/(4 pi r^2) = R0^3/(3 r^2)\n");
    { double Om = 4.0 / 3 * PI * R0 * R0 * R0; std::printf("  A: surface integral of u over spheres of radius 1e-15, 1e-12, 1e-9, 1e-6 m divided by Omega0: "); for (double r : {1e-15, 1e-12, 1e-9, 1e-6}) std::printf("%.12f ", Om / (4 * PI * r * r) * 4 * PI * r * r / Om); std::printf("\n");
      std::printf("  B: u(R0) = %.4e m = R0/3 = %.4e ; u(1 nm) = %.4e m ; u(1 um) = %.4e m\n\n", Om / (4 * PI * R0 * R0), R0 / 3, std::pow(R0, 3) / (3 * 1e-18), std::pow(R0, 3) / (3 * 1e-12)); }
    std::printf("F5 terminal radius R_term = sqrt(R0^3/(3 l_P)) (u(R_term) = l_P) and its scaling with the baryon number\n");
    { double Rt = std::sqrt(R0 * R0 * R0 / (3 * lP)); std::printf("  A: R_term = %.4e m ; u(R_term) = %.4e m against l_P = %.4e m\n", Rt, std::pow(R0, 3) / (3 * Rt * Rt), lP);
      double Nb_E = M_EARTH / M::m_p, Nb_S = 1.989e30 / M::m_p;
      std::printf("  B [ext masses]: R_term(N_b) = R_term(1) sqrt(N_b): N_b = 1: %.3e m ; Earth (N_b = %.3e): %.3e m = %.3e AU ; Sun (N_b = %.3e): %.3e m = %.3e Mpc ; R_term = R_CMB at N_b = %.3e\n\n", Rt, Nb_E, Rt * std::sqrt(Nb_E), Rt * std::sqrt(Nb_E) / M::AU, Nb_S, Rt * std::sqrt(Nb_S), Rt * std::sqrt(Nb_S) / 3.0857e22, std::pow(M::R_CMB / Rt, 2)); }
    std::printf("F6 strain energy of the displacement field: shear energy density 6 mu (Omega0/4pi)^2 / r^6 (K (div u)^2 = 0)\n");
    { double Om = 4.0 / 3 * PI * R0 * R0 * R0, mu = 1.0, cl = 8 * PI * mu * std::pow(Om / (4 * PI), 2) / (R0 * R0 * R0); int n = 400000; double s = 0, x0 = 1.0, x1 = 1e-6; (void)x1; // integrate in t = R0/r from 0 to 1: r = R0/t, dr = -R0/t^2 dt
      for (int i = 0; i < n; ++i) { double t = (i + 0.5) / n, r = R0 / t; s += 6 * mu * std::pow(Om / (4 * PI), 2) / std::pow(r, 6) * 4 * PI * r * r * (R0 / (t * t)) / n; }
      std::printf("  A: total shear energy outside R0 (mu = 1): quadrature %.6e ; closed form 8 pi mu (Omega0/4pi)^2/R0^3 = %.6e (relative %.1e)\n", s, cl, s / cl - 1); }
    { double Om = 4.0 / 3 * PI * R0 * R0 * R0, worst = 0; for (double r : {2e-15, 1e-12, 1e-9}) { double h = r * 1e-4; auto ur = [&](double x) { return Om / (4 * PI * x * x); }; double dv = ((r + h) * (r + h) * ur(r + h) - (r - h) * (r - h) * ur(r - h)) / (2 * h) / (r * r); worst = std::max(worst, std::fabs(dv) / (ur(r) / r)); }
      std::printf("  B: bulk term K (div u)^2: worst |div u|/(u/r) = %.1e -> zero ; the energy comes from the shear and is r^-6\n\n", worst); }
    std::printf("F7 the stated density variation rho(r) = rho0 (1 - Omega0/(4 pi r^3))\n");
    for (double f : {1.0, 2.0, 10.0}) std::printf("  A: r = %.0f R0 : rho/rho0 = %.6f (Omega0/(4 pi r^3) = R0^3/(3 r^3))\n", f, 1 - 1 / (3 * f * f * f));
    for (double f : {1e1, 1e3, 1e6}) std::printf("  B: volume removed from R0 to %.0e R0, integral of (1 - rho/rho0) dV = Omega0 ln(r_max/R0) = %.3f Omega0 (the displaced volume is Omega0: the integral diverges logarithmically)\n", f, std::log(f));
    std::printf("\nF8 the stated index n(r) = 1 + alpha Omega0/r\n");
    { double kb = bridge::koppa_per_baryon, Om = 4.0 / 3 * PI * R0 * R0 * R0, al = 2 * kb / Om; std::printf("  A: to give n - 1 = 2 koppa/r per body of N_b baryons, alpha N_b Omega0 = 2 N_b koppa_b, so alpha = 2 koppa_b/Omega0 = %.4e m^-2 (koppa_b = %.4e m per baryon, engine) : alpha is not dimensionless\n", al, kb); }
    { double Nb = kopS / bridge::koppa_per_baryon; std::printf("  B: the baryon census of the Sun from koppa_Sun/koppa_b = %.4e ; M_Sun/m_p [ext, 1.989e30 kg] = %.4e (relative %.1e)\n\n", Nb, 1.989e30 / M::m_p, Nb / (1.989e30 / M::m_p) - 1); }
    std::printf("F9 Gauss form: div g = -4 pi G rho  <->  div u = Omega0 delta(r)\n");
    { std::printf("  A: flux of g = c^2 koppa/r^2 over spheres of radius 1e6, 1e9, 1e12 m (Sun's koppa): "); for (double r : {1e6, 1e9, 1e12}) std::printf("%.6e ", kopS * c * c / (r * r) * 4 * PI * r * r); std::printf("(= 4 pi c^2 koppa = %.6e m^3/s^2)\n", 4 * PI * c * c * kopS); }
    { double Om = 4.0 / 3 * PI * R0 * R0 * R0, kb = bridge::koppa_per_baryon; std::printf("  B: for one baryon u/g = Omega0/(4 pi c^2 koppa_b) at r = 1e-12, 1e-9, 1e-6 m: "); for (double r : {1e-12, 1e-9, 1e-6}) std::printf("%.6e ", (Om / (4 * PI * r * r)) / (kb * c * c / (r * r))); std::printf("s^2 (constant, both fall as 1/r^2)\n\n"); }

    // ===================== G. koppa structures =====================
    std::printf("G1 v = c sqrt(koppa/r) = c/k(r), k(r) = k0 sqrt(r/R), koppa = R/k0^2\n");
    { double a0 = M::a_0, k0 = 1 / M::alpha; std::printf("  A: hydrogen (R = a_0, k0 = 1/alpha): v(a_0) = %.4f alpha c = %.5e m/s ; v(4 a_0) = %.4f alpha c ; koppa = a_0 alpha^2 = %.5e m (r_e = %.5e m)\n", (c / k0) / (c * M::alpha), c / k0, (c / (k0 * std::sqrt(4.0))) / (c * M::alpha), a0 * M::alpha * M::alpha, M::r_e); }
    { double v1 = c * std::sqrt(kopS / R_S), vE = c * std::sqrt(kopS / M::AU); std::printf("  B: Sun (koppa = %.4f m): surface v = %.1f m/s (engine v_surface_Sun = %.0f) ; at 1 AU v = %.3f km/s (the Earth's orbital speed)\n\n", kopS, v1, bridge::v_surface_Sun, vE / 1e3); }
    std::printf("G2 z k^2 = 1: the spectroscopic redshift gives koppa = z R, the surface speed v = c sqrt(z) and the baryon census N_b = koppa/koppa_b\n");
    { double z = 80.42e3 / c, RB = 5.84e6, kop = z * RB, Nb = kop / bridge::koppa_per_baryon; std::printf("  A: Sirius B (z = 80.42 km/s/c = %.4e [search result, Barstow et al. 2005]; R = 5.84e6 m [B]): v = c sqrt(z) = %.3f km/s ; koppa = zR = %.1f m ; N_b = %.3e = %.3e kg = %.3f solar masses [ext 1.989e30] (dynamical 1.018 +/- 0.011, from the search result)\n", z, c * std::sqrt(z) / 1e3, kop, Nb, Nb * M::m_p, Nb * M::m_p / 1.989e30); }
    { double z = kopS / R_S; std::printf("  B: Sun: predicted shift c z = %.2f m/s ; error propagation d(koppa)/koppa = dz/z + dR/R: a 50 m/s uncertainty on a 636 m/s shift [B] gives %.1f%% on koppa, against about 1e-10 for GM from the orbits [B]\n\n", c * z, 50.0 / (c * z) * 100); }
    std::printf("G3 modified Kepler a = -(c^2 koppa/r^2)(1 + beta koppa/r)\n");
    { double a = bridge::a_Mercury / kopS, e = bridge::e_Mercury, U = 1.0 / (a * (1 - e * e)); double beta = 6.0; int spo = 200000, N = 40; double dphi = 2 * PI / spo, u = 1.0 / (a * (1 - e)), p = 0, ph = 0, pprev = 0; std::vector<double> peri; int orbit = 0; long long step = 0;
      auto f = [&](double uu) { return -uu * (1 - beta * U) + U; };   // u'' + u (1 - beta koppa U) = U, in units of koppa (u = koppa/r)
      while (orbit < N + 1) { double k1u = p, k1p = f(u), k2u = p + 0.5 * dphi * k1p, k2p = f(u + 0.5 * dphi * k1u), k3u = p + 0.5 * dphi * k2p, k3p = f(u + 0.5 * dphi * k2u), k4u = p + dphi * k3p, k4p = f(u + dphi * k3u);
          double nu = u + dphi / 6 * (k1u + 2 * k2u + 2 * k3u + k4u), np = p + dphi / 6 * (k1p + 2 * k2p + 2 * k3p + k4p); ++step; ph = step * dphi; if (pprev > 0 && np <= 0 && ph > PI) { double fr = pprev / (pprev - np); peri.push_back((step - 1) * dphi + fr * dphi); ++orbit; } pprev = p = np; u = nu; }
      double prec = (peri.back() - peri.front()) / (peri.size() - 1) - 2 * PI, an = PI * beta / (a * (1 - e * e)); std::printf("  A: orbit equation u'' + u (1 - beta koppa U) = U, U = 1/(a(1-e^2)), beta = 6, Mercury: advance %.6e rad/orbit ; exact 2 pi (1/sqrt(1 - beta koppa U) - 1) = %.6e ; first order pi beta koppa/(a(1-e^2)) = %.6e\n", prec, 2 * PI * (1 / std::sqrt(1 - beta * U) - 1), an); }
    { double lo = 1e-9, hi = 10; for (int i = 0; i < 200; ++i) { double mid = 0.5 * (lo + hi); (mid * (1 + 6 * mid) < 1 ? lo : hi) = mid; } std::printf("  B: circular-orbit speed v^2 = c^2 x (1 + 6x): v = c at x = %.6f (r = 3 koppa) ; stability margin 1/(1 + 6x) at x = 1e-3, 1/3, 10: %.4f, %.4f, %.4f (positive for all x)\n\n", lo, 1 / (1 + 6e-3), 1 / (1 + 2.0), 1 / (1 + 60.0)); }

    // ===================== H. implicit structures =====================
    std::printf("H1 attenuation through a body: transmitted fraction exp(-tau), tau = (sigma/m) Sigma; force proportional to mass only while tau << 1\n");
    for (double tau : {1e-14, 0.1, 1.0, 10.0}) std::printf("  A: tau = %.0e : (1 - e^-tau)/tau = %.10f (the fraction of the linear force that survives)\n", tau, -std::expm1(-tau) / tau);
    { double Sigma = 5515.0 * 2 * R_EARTH; std::printf("  B [ext mean density 5515 kg/m^3]: column density through the Earth Sigma = %.3e kg/m^2 ; tau < 1e-13 requires sigma/m < %.2e m^2/kg ; tau = 1 would need sigma/m = %.2e m^2/kg\n", Sigma, 1e-13 / Sigma, 1 / Sigma); }
    return 0;
}
