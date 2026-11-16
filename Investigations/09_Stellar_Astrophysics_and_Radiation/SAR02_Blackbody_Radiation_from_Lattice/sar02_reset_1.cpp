// SAR02 blank-slate run 1 (2026-10-08). REGISTRATION (fixed before the run; measured values are loaded only in the comparisons marked [CMP]).
//
// Question (native): the prompt bundles three ingredients as "lattice properties": (M) the mode count, (Q) the rule for the energy a mode can hold, (W) the weighting by temperature.
//  Each is registered with a prediction computed from the registered rule alone.
//
// Lattice model (registered): nearest-neighbour scalar relay on a cubic-symmetry lattice (SC z=6, BCC z=8, FCC z=12), nearest-neighbour distance d, relay speed c at long wave:
//   omega^2(k) = kappa * sum_{j=1..z} (1 - cos(k.delta_j)),  kappa = 6 c^2/(z d^2)  (so omega -> c|k| as k -> 0).   Units in the tool: c = d = 1.
// PHASE 1 (M). Cumulative mode count per cell below omega_c, divided by the continuum count V_cell (4 pi/3)(omega_c/c)^3/(2 pi)^3:  R(s), s = omega_c d / c.  R = 1 + q s^2 + O(s^4).
//   Route A: direction integral (Gauss-Legendre 48 x uniform 96) of k_c(direction)^3/3, valid for omega_c <= 0.3 omega_max.  Route B: uniform grid of M = 240 points per reciprocal axis (13.8e6 modes), whole range 0.1..1.0 omega_max.
//   q by Richardson from s = 0.05, 0.10.  Thermal evaluation: delta = q s^2 at s = 2 pi nu_peak d / c with nu_peak = x_nu k T / h (x_nu from Phase 3), for d = l_P (engine reference) and d = 3.1e8 l_P (bound carried from the 2026-10-08 shadow analysis, GRB 090510).
//   Spacing d* at which |delta| = 1e-4 (the prompt's 0.01% target), at T_CMB.
//   RC1: |delta| < 1e-4 at d = l_P for all three lattices => lattice discreteness cannot supply the thermal cutoff (outcome class "detectable" is populated for d >= d*).
// PHASE 2 (Q, W). Mean energy per mode under four registered quantisation rules, energy density u = p <e> / V_cell with p = 2 branches per cell, V_cell = l_P^3 (SC, d = l_P), T = T_CMB (and toy temperatures 300 K, 6000 K for the T-exponent only):
//   A  continuous amplitude (no quantum): <e> = k T (equipartition).
//   B  tick quantum: one hop-action per relay tick, e_t = hbar c / d, independent of the mode frequency; levels n e_t, weights exp(-n e_t / kT).
//   B' Law-I relay content per shell, e = law_I::epsilon, independent of the mode frequency; same level sum.
//   C  action per mode cycle: levels n h nu, weights exp(-n h nu / kT); u(nu) = p 4 pi nu^2/c^3 <e>; level sums evaluated explicitly (no closed form), integrated by Gauss-Legendre 16 x 60 panels over x = h nu / kT in [0, 60].
//   [CMP] u_meas = measured::a_rad T_CMB^4.   RC2: A, B, B' excluded if |ln(u/u_meas)| > ln 2; C consistent if |u_C/u_meas - 1| < 1e-4.  T-exponent d ln u / d ln T computed for A and C.
//   W: the Gibbs weight is derived from counting (stars and bars), not postulated: R oscillators of one quantum e, M quanta in total, all microstates equally weighted; exact P(n) for one oscillator; counting temperature e/kT = [ln W(M+1) - ln W(M-1)]/2, W(M) = C(M+R-1, M);
//   compared with 1/(exp(e/kT) - 1).  R = 50, 200, 800, 3200; mean occupation M/R = 0.1, 1, 5.   RC3: relative deviation at R = 3200 <= 1e-3 for all three, and decreasing in R.
// PHASE 3. From rule C with p = 2: a = p 4 pi (pi^4/15) k^4/(h^3 c^3); sigma = a c/4 (isotropic flux);  x_nu: peak of x^3/(e^x - 1);  x_lambda: peak of x^5/(e^x - 1) (x = hc/lambda kT);  b = hc/(k x_lambda).  Each by two routes (bisection on the derivative equation; golden-section on the function).
//   [CMP] table values of the prompt: sigma = 5.670374e-8 W/m^2/K^4, a = measured::a_rad, b = 2.898e-3 m K, nu_max = 2.821 kT/h.  RC4: a, sigma, b within 1e-4; x_nu within the table rounding (0.0005).
//   Registered check of the prompt's "equivalently lambda_max T = 2.898e-3": c T/nu_max versus b, consistent if within 1e-4.
//   Conditional (p_eff): an extra branch with speed c_L adds (c/c_L)^3 to p; reported for c_L = c/sqrt(3) (the speed appearing in release_acoustics) as an example only.
// VALIDATIONS (known answers, before the object is touched): V1 1D chain cumulative count = (2/pi) asin(omega_c/2) (grid, M = 1e5, tol 1e-4); V2 SC omega_max = 2 sqrt(3) (tol 1e-12) ; V3 long-wave speed c for all three lattices (k = 1e-3, six directions, tol 1e-6);
//   V4 Gauss-Legendre n = 16 integrates x^8 on [-1,1] to 2/9 (tol 1e-14); V5 Planck integral by explicit level sums = 6 sum n^-4 (1e5 terms) (tol 1e-10); V6 route A gives q_SC = 3/40 (analytic, tol 1%); V7 routes A and B agree within 1% at omega_c/omega_max = 0.2, 0.3 for each lattice;
//   V8 root equations x = 3(1 - e^-x) and x = 5(1 - e^-x): residual < 1e-12.
// Gradation (REOPEN protocol 5): G0 any validation not met; G1 a rule excluded by its criterion; G2 open premise; G3 consistent, shared-input (named input); G4 consistent, independent origin; G5 discriminating.
// Look-elsewhere: 4 rules registered (A, B, B', C), 3 lattices, all reported; no selection of a best member.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <functional>
#include <vector>
using namespace sdt::laws;
using V3 = std::array<double, 3>;
static const double PI = std::numbers::pi;

static void gauleg(int n, std::vector<double>& x, std::vector<double>& w) {
    x.assign(n, 0); w.assign(n, 0);
    for (int i = 0; i < (n + 1) / 2; ++i) {
        double z = std::cos(PI * (i + 0.75) / (n + 0.5)), pp = 1;
        for (int it = 0; it < 200; ++it) { double p1 = 1, p2 = 0; for (int j = 0; j < n; ++j) { double p3 = p2; p2 = p1; p1 = ((2 * j + 1) * z * p2 - j * p3) / (j + 1); } pp = n * (z * p1 - p2) / (z * z - 1); double z1 = z; z = z1 - p1 / pp; if (std::fabs(z - z1) < 1e-15) break; }
        { double p1 = 1, p2 = 0; for (int j = 0; j < n; ++j) { double p3 = p2; p2 = p1; p1 = ((2 * j + 1) * z * p2 - j * p3) / (j + 1); } pp = n * (z * p1 - p2) / (z * z - 1); }
        x[i] = -z; x[n - 1 - i] = z; w[i] = w[n - 1 - i] = 2.0 / ((1 - z * z) * pp * pp);
    }
}
static V3 cross(const V3& a, const V3& b) { return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]}; }
static double dot(const V3& a, const V3& b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }

struct Lattice {
    const char* name; int z; std::vector<V3> nn; V3 a1, a2, a3, b1, b2, b3; double Vcell, kap;
    double omega(const V3& k) const { double s = 0; for (auto& d : nn) s += 1.0 - std::cos(dot(k, d)); return std::sqrt(kap * s); }
};
static Lattice make(int kind) {
    Lattice L{};
    if (kind == 0) { L.name = "SC"; L.a1 = {1, 0, 0}; L.a2 = {0, 1, 0}; L.a3 = {0, 0, 1}; for (int i = 0; i < 3; ++i) for (int s = -1; s <= 1; s += 2) { V3 v{0, 0, 0}; v[i] = s; L.nn.push_back(v); } }
    if (kind == 1) { L.name = "BCC"; double ac = 2.0 / std::sqrt(3.0), h = ac / 2; L.a1 = {-h, h, h}; L.a2 = {h, -h, h}; L.a3 = {h, h, -h}; for (int sx = -1; sx <= 1; sx += 2) for (int sy = -1; sy <= 1; sy += 2) for (int sz = -1; sz <= 1; sz += 2) L.nn.push_back({sx * h, sy * h, sz * h}); }
    if (kind == 2) { L.name = "FCC"; double ac = std::sqrt(2.0), h = ac / 2; L.a1 = {0, h, h}; L.a2 = {h, 0, h}; L.a3 = {h, h, 0}; for (int i = 0; i < 3; ++i) for (int sa = -1; sa <= 1; sa += 2) for (int sb = -1; sb <= 1; sb += 2) { V3 v{0, 0, 0}; v[(i + 1) % 3] = sa * h; v[(i + 2) % 3] = sb * h; L.nn.push_back(v); } }
    L.z = (int)L.nn.size(); L.kap = 6.0 / L.z; // d = 1, c = 1
    double vol = dot(L.a1, cross(L.a2, L.a3)); L.Vcell = std::fabs(vol);
    auto rec = [&](const V3& a, const V3& b) { V3 c = cross(a, b); for (auto& t : c) t *= 2 * PI / vol; return c; };
    L.b1 = rec(L.a2, L.a3); L.b2 = rec(L.a3, L.a1); L.b3 = rec(L.a1, L.a2);
    return L;
}
static double Ncont(const Lattice& L, double w) { return L.Vcell * (4.0 * PI / 3.0) * w * w * w / (8.0 * PI * PI * PI); }

// Route A: direction integral, valid for small omega_c
static double routeA(const Lattice& L, double wc, const std::vector<double>& xm, const std::vector<double>& wm) {
    const int nphi = 96; double sum = 0;
    for (size_t i = 0; i < xm.size(); ++i) { double mu = xm[i], st = std::sqrt(1 - mu * mu);
        for (int j = 0; j < nphi; ++j) { double ph = 2 * PI * (j + 0.5) / nphi; V3 n{st * std::cos(ph), st * std::sin(ph), mu};
            double k = 0, dk = 0.002; while (L.omega({n[0] * (k + dk), n[1] * (k + dk), n[2] * (k + dk)}) < wc) k += dk;
            double lo = k, hi = k + dk; for (int it = 0; it < 60; ++it) { double m = 0.5 * (lo + hi); if (L.omega({n[0] * m, n[1] * m, n[2] * m}) < wc) lo = m; else hi = m; }
            double kc = 0.5 * (lo + hi); sum += wm[i] * (2 * PI / nphi) * kc * kc * kc / 3.0; } }
    return L.Vcell * sum / (8.0 * PI * PI * PI);
}
// Planck pieces
static double nbar_explicit(double x) { // sum n e^{-n x} / sum e^{-n x}, explicit
    int N = (int)(42.0 / x) + 5; double num = 0, den = 0, t = 1; double q = std::exp(-x);
    for (int n = 0; n <= N; ++n) { num += n * t; den += t; t *= q; } return num / den; }
static double planck_integral(const std::vector<double>& gx, const std::vector<double>& gw) { // int_0^60 x^3 nbar(x) dx
    double s = 0; for (int p = 0; p < 60; ++p) for (size_t i = 0; i < gx.size(); ++i) { double x = p + 0.5 * (gx[i] + 1); s += 0.5 * gw[i] * x * x * x * nbar_explicit(x); } return s; }
static double bisect(const std::function<double(double)>& f, double lo, double hi) { for (int i = 0; i < 200; ++i) { double m = 0.5 * (lo + hi); if (f(lo) * f(m) <= 0) hi = m; else lo = m; } return 0.5 * (lo + hi); }
static double golden(const std::function<double(double)>& f, double lo, double hi) { const double g = (std::sqrt(5.0) - 1) / 2; double a = lo, b = hi, c = b - g * (b - a), d = a + g * (b - a), fc = f(c), fd = f(d); for (int i = 0; i < 200; ++i) { if (fc > fd) { b = d; d = c; fd = fc; c = b - g * (b - a); fc = f(c); } else { a = c; c = d; fc = fd; d = a + g * (b - a); fd = f(d); } } return 0.5 * (a + b); }
static double lnC(double n, double r) { return std::lgamma(n + 1) - std::lgamma(r + 1) - std::lgamma(n - r + 1); }

int main() {
    using namespace measured;
    std::printf("SAR02 blank-slate run 1 (registered in the tool header, 2026-10-08)\n====================================================================\n\n");
    int fails = 0; auto V = [&](const char* n, bool ok, const char* d) { std::printf("[%s] %s -> %s\n", n, d, ok ? "met" : "NOT MET"); if (!ok) ++fails; };
    std::vector<double> gx, gw; gauleg(16, gx, gw); std::vector<double> mx, mw; gauleg(48, mx, mw);
    Lattice lat[3] = {make(0), make(1), make(2)};

    // ---- validations
    { double s = 0; for (size_t i = 0; i < gx.size(); ++i) s += gw[i] * std::pow(gx[i], 8); char b[160]; std::snprintf(b, 160, "GL16 integral of x^8 = %.16f (2/9 = %.16f)", s, 2.0 / 9); V("V4", std::fabs(s - 2.0 / 9) < 1e-14, b); }
    { const int M = 100000; bool ok = true; for (double wc : {0.5, 1.0, 1.5}) { int c = 0; for (int i = 0; i < M; ++i) if (2 * std::sin(PI * (i + 0.5) / M) < wc) ++c; // k = 2 pi u, omega = 2 |sin(k/2)|
            double f = double(c) / M, ex = 2.0 / PI * std::asin(wc / 2); ok = ok && std::fabs(f - ex) < 1e-4; std::printf("      1D chain omega_c = %.1f: grid %.6f, exact %.6f\n", wc, f, ex); } V("V1", ok, "1D chain cumulative count against (2/pi) asin(omega_c/2)"); }
    { double mx_ = 0; const int M = 40; for (int i = 0; i < M; ++i) for (int j = 0; j < M; ++j) for (int k = 0; k < M; ++k) mx_ = std::max(mx_, lat[0].omega({2 * PI * i / M, 2 * PI * j / M, 2 * PI * k / M})); char b[160]; std::snprintf(b, 160, "SC omega_max (grid, M = 40) = %.15f ; 2 sqrt(3) = %.15f", mx_, 2 * std::sqrt(3.0)); V("V2", std::fabs(mx_ - 2 * std::sqrt(3.0)) < 1e-12, b); }
    { bool ok = true; double worst = 0; for (auto& L : lat) for (V3 n : {V3{1, 0, 0}, V3{0, 1, 0}, V3{0, 0, 1}, V3{1, 1, 0}, V3{1, 1, 1}, V3{1, 2, 3}}) { double nn = std::sqrt(dot(n, n)); V3 k{n[0] / nn * 1e-3, n[1] / nn * 1e-3, n[2] / nn * 1e-3}; double c = L.omega(k) / 1e-3; worst = std::max(worst, std::fabs(c - 1)); } ok = worst < 1e-6; char b[160]; std::snprintf(b, 160, "long-wave speed omega/k at k = 1e-3: worst |c - 1| over 3 lattices x 6 directions = %.2e", worst); V("V3", ok, b); }
    { double ref = 0; for (int n = 1; n <= 100000; ++n) ref += 6.0 / ((double)n * n * n * n); double q = planck_integral(gx, gw); char b[200]; std::snprintf(b, 200, "explicit-sum integral of x^3 nbar = %.12f ; 6 sum n^-4 = %.12f ; rel diff %.2e", q, ref, std::fabs(q / ref - 1)); V("V5", std::fabs(q / ref - 1) < 1e-10, b); }
    const double xnu = bisect([](double x) { return x - 3 * (1 - std::exp(-x)); }, 1, 5), xlam = bisect([](double x) { return x - 5 * (1 - std::exp(-x)); }, 3, 6);
    { double r1 = std::fabs(xnu - 3 * (1 - std::exp(-xnu))), r2 = std::fabs(xlam - 5 * (1 - std::exp(-xlam))); char b[160]; std::snprintf(b, 160, "root residuals %.1e (x_nu = %.10f), %.1e (x_lambda = %.10f)", r1, xnu, r2, xlam); V("V8", r1 < 1e-12 && r2 < 1e-12, b); }

    // Phase 1 numbers needed by V6/V7
    double q[3]; double wmax[3];
    std::printf("\n[P1] mode count R(s) = N_lattice / N_continuum, s = omega_c d / c\n");
    std::vector<float> om;
    for (int li = 0; li < 3; ++li) { const Lattice& L = lat[li];
        double qs[2]; int si = 0; for (double s : {0.05, 0.10}) { double R = routeA(L, s, mx, mw) / Ncont(L, s); qs[si++] = (R - 1) / (s * s); }
        q[li] = (4 * qs[0] - qs[1]) / 3; }
    { bool ok = std::fabs(q[0] - 3.0 / 40) / (3.0 / 40) < 0.01; char b[160]; std::snprintf(b, 160, "route A: q_SC = %.6f ; analytic 3/40 = %.6f", q[0], 3.0 / 40); V("V6", ok, b); }
    const int M = 240; double R_B[3][10];
    for (int li = 0; li < 3; ++li) { const Lattice& L = lat[li]; om.assign((size_t)M * M * M, 0); size_t idx = 0; double mxv = 0;
        for (int i = 0; i < M; ++i) for (int j = 0; j < M; ++j) for (int k = 0; k < M; ++k) { V3 kk{(double(i) / M) * L.b1[0] + (double(j) / M) * L.b2[0] + (double(k) / M) * L.b3[0], (double(i) / M) * L.b1[1] + (double(j) / M) * L.b2[1] + (double(k) / M) * L.b3[1], (double(i) / M) * L.b1[2] + (double(j) / M) * L.b2[2] + (double(k) / M) * L.b3[2]}; float w = (float)L.omega(kk); om[idx++] = w; mxv = std::max(mxv, (double)w); }
        wmax[li] = mxv; std::sort(om.begin(), om.end());
        for (int f = 1; f <= 10; ++f) { double wc = 0.1 * f * wmax[li]; size_t cnt = std::lower_bound(om.begin(), om.end(), (float)wc) - om.begin(); if (f == 10) cnt = om.size(); R_B[li][f - 1] = (double(cnt) / om.size()) / Ncont(L, wc); } }
    { bool ok = true; double worst = 0; for (int li = 0; li < 3; ++li) for (int f : {2, 3}) { double wc = 0.1 * f * wmax[li]; double RA = routeA(lat[li], wc, mx, mw) / Ncont(lat[li], wc); double dv = std::fabs(RA / R_B[li][f - 1] - 1); worst = std::max(worst, dv); ok = ok && dv < 0.01; } char b[160]; std::snprintf(b, 160, "routes A and B at omega_c/omega_max = 0.2, 0.3: worst relative difference %.3f%%", worst * 100); V("V7", ok, b); }
    std::printf("\nVALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0 (object not assessed)"); if (fails) return 1;

    // ---- Phase 1 results
    for (int li = 0; li < 3; ++li) std::printf("[P1] %s: z = %d, V_cell = %.6f d^3, omega_max = %.6f c/d, q = %.6f (R = 1 + q s^2)\n", lat[li].name, lat[li].z, lat[li].Vcell, wmax[li], q[li]);
    std::printf("[P1] route B (grid %d^3) R at omega_c/omega_max = 0.1 ... 1.0:\n", M);
    for (int li = 0; li < 3; ++li) { std::printf("     %s:", lat[li].name); for (int f = 0; f < 10; ++f) std::printf(" %.4f", R_B[li][f]); std::printf("\n"); }
    const double T = T_CMB, nu_pk = xnu * k_B * T / h;
    std::printf("[P1] thermal peak at T_CMB: nu_peak = x_nu k T/h = %.6e Hz ; c/nu_peak = %.6e m\n", nu_pk, c / nu_pk);
    bool rc1 = true;
    for (int li = 0; li < 3; ++li) { double s1 = 2 * PI * nu_pk * l_P / c, s2 = 2 * PI * nu_pk * 3.1e8 * l_P / c; double d1 = q[li] * s1 * s1, d2 = q[li] * s2 * s2; double sstar = std::sqrt(1e-4 / std::fabs(q[li])), dstar = sstar * c / (2 * PI * nu_pk);
        std::printf("[P1] %s: delta(d = l_P) = %.3e ; delta(d = 3.1e8 l_P) = %.3e ; d* (|delta| = 1e-4) = %.3e m = %.3e l_P\n", lat[li].name, d1, d2, dstar, dstar / l_P); rc1 = rc1 && std::fabs(d1) < 1e-4; }
    std::printf("     RC1 (|delta| < 1e-4 at d = l_P, all lattices): %s\n\n", rc1 ? "met -> lattice discreteness is invisible at thermal frequencies" : "NOT met");

    // ---- Phase 2
    const double Vc = l_P3, p = 2.0, umeas = a_rad * std::pow(T, 4);
    std::printf("[P2] SC lattice, d = l_P, V_cell = %.6e m^3, p = %.0f branches per cell; T = T_CMB = %.4f K; u_meas = a_rad T^4 = %.6e J/m^3 [CMP]\n", Vc, p, T, umeas);
    double uA = p * k_B * T / Vc; std::printf("[A ] continuous amplitude: u = p k T / V_cell = %.6e J/m^3 ; u/u_meas = %.6e ; ln = %.3f -> %s\n", uA, uA / umeas, std::log(uA / umeas), std::fabs(std::log(uA / umeas)) > std::log(2.0) ? "excluded" : "consistent");
    { double et = hbar * c / l_P, y = et / (k_B * T); double lnu = std::log(p) + std::log(et) - y - std::log1p(-std::exp(-y)) - std::log(Vc); std::printf("[B ] tick quantum e_t = hbar c/d = %.6e J (%.6e kT): ln u = %.6e ; ln(u/u_meas) = %.6e -> %s\n", et, y, lnu, lnu - std::log(umeas), std::fabs(lnu - std::log(umeas)) > std::log(2.0) ? "excluded" : "consistent"); }
    { double e = law_I::epsilon, y = e / (k_B * T); double lne = std::log(e) - std::log(std::expm1(y)); double u = p * std::exp(lne) / Vc; std::printf("[B'] Law-I relay content e = %.6e J (%.3e kT): u = %.6e ; u/u_meas = %.6e -> %s ; (e is defined from u_CMB: shared-input as a predictor)\n", e, y, u, u / umeas, std::fabs(std::log(u / umeas)) > std::log(2.0) ? "excluded" : "consistent"); }
    const double Ipl = planck_integral(gx, gw);
    auto uC = [&](double TT) { double kT = k_B * TT; return p * 4 * PI * std::pow(kT, 4) / (h * h * h * c * c * c) * Ipl; };
    std::printf("[C ] action per cycle: explicit-sum integral I = %.12f ; u_C(T_CMB) = %.6e J/m^3 ; u_C/u_meas = %.8f ; |u_C/u_meas - 1| = %.2e -> %s\n", Ipl, uC(T), uC(T) / umeas, std::fabs(uC(T) / umeas - 1), std::fabs(uC(T) / umeas - 1) < 1e-4 ? "consistent within 1e-4" : "inconsistent");
    std::printf("[P2] T-exponent d ln u/d ln T (toy T = 300 K and 6000 K): A: %.6f ; C: %.6f\n", std::log((p * k_B * 6000 / Vc) / (p * k_B * 300 / Vc)) / std::log(20.0), std::log(uC(6000) / uC(300)) / std::log(20.0));
    std::printf("[P2] required classical spacing for u_A = u_meas at T_CMB: d_A = (p k T/u_meas)^(1/3) = %.4e m ; at 300 K d_A would be %.4e m (a fixed lattice cannot match both)\n", std::cbrt(p * k_B * T / umeas), std::cbrt(p * k_B * 300 / (a_rad * std::pow(300.0, 4))));

    // ---- W: counting derivation
    std::printf("\n[W ] Gibbs weight from counting: R oscillators, M quanta, equal weight; one oscillator holds n\n");
    bool rc3 = true; double prev[3] = {1, 1, 1};
    for (int R : {50, 200, 800, 3200}) { std::printf("     R = %4d:", R); int ni = 0; for (double nb : {0.1, 1.0, 5.0}) { int Mq = (int)std::lround(R * nb);
            double Z = lnC(Mq + R - 1, R - 1), mean = 0, tot = 0; for (int n = 0; n <= Mq; ++n) { double pn = std::exp(lnC(Mq - n + R - 2, R - 2) - Z); tot += pn; mean += n * pn; }
            auto lnW = [&](int m) { return lnC(m + R - 1, m); }; double x = (lnW(Mq + 1) - lnW(Mq - 1)) / 2; double bose = 1.0 / std::expm1(x); double dev = std::fabs(mean / bose - 1);
            std::printf("  <n> = %.6f vs 1/(e^x-1) = %.6f (dev %.2e, sum P = %.12f);", mean, bose, dev, tot); if (R == 3200) rc3 = rc3 && dev <= 1e-3; if (dev > prev[ni] + 1e-12) rc3 = false; prev[ni++] = dev; } std::printf("\n"); }
    std::printf("     RC3 (deviation <= 1e-3 at R = 3200 and decreasing in R): %s\n", rc3 ? "met" : "NOT met");

    // ---- Phase 3
    std::printf("\n[P3] constants from rule C, p = 2\n");
    const double xnu_g = golden([](double x) { return x * x * x / std::expm1(x); }, 0.5, 6), xlam_g = golden([](double x) { return std::pow(x, 5) / std::expm1(x); }, 0.5, 8);
    std::printf("     x_nu: bisection %.10f, golden-section %.10f (diff %.1e) ; x_lambda: bisection %.10f, golden-section %.10f (diff %.1e)\n", xnu, xnu_g, std::fabs(xnu - xnu_g), xlam, xlam_g, std::fabs(xlam - xlam_g));
    const double a_C = p * 4 * PI * (Ipl) * std::pow(k_B, 4) / (h * h * h * c * c * c), sig_C = a_C * c / 4, b_C = h * c / (k_B * xlam);
    const double sig_tab = 5.670374e-8, b_tab = 2.898e-3; // prompt table (CODATA); not in measured::
    std::printf("[CMP] a = %.8e J/m^3/K^4 vs measured::a_rad %.5e : rel %.2e -> %s\n", a_C, a_rad, a_C / a_rad - 1, std::fabs(a_C / a_rad - 1) < 1e-4 ? "within 1e-4" : "outside");
    std::printf("[CMP] sigma = a c/4 = %.8e vs table %.6e : rel %.2e -> %s\n", sig_C, sig_tab, sig_C / sig_tab - 1, std::fabs(sig_C / sig_tab - 1) < 1e-4 ? "within 1e-4" : "outside");
    std::printf("[CMP] b = hc/(k x_lambda) = %.8e m K vs table %.3e : rel %.2e -> %s\n", b_C, b_tab, b_C / b_tab - 1, std::fabs(b_C / b_tab - 1) < 1e-4 ? "within 1e-4" : "outside");
    std::printf("[CMP] x_nu = %.6f vs table 2.821 : diff %.4f -> %s (table rounding 0.0005)\n", xnu, xnu - 2.821, std::fabs(xnu - 2.821) <= 0.0005 ? "within" : "outside");
    { double lam_nu_T = h * c / (k_B * xnu); std::printf("[CHK] prompt's \"equivalently lambda_max T\": c T/nu_max = %.6e m K ; b = %.6e m K ; ratio %.4f -> %s\n", lam_nu_T, b_C, lam_nu_T / b_C, std::fabs(lam_nu_T / b_C - 1) < 1e-4 ? "equivalent" : "NOT equivalent (different peaks: per frequency and per wavelength)"); }
    { double cl = c / std::sqrt(3.0), pe = 2 + std::pow(c / cl, 3); std::printf("[P3] conditional p_eff: a branch at c_L = c/sqrt(3) adds (c/c_L)^3 = %.4f ; p_eff = %.4f ; a would be %.4f x the p = 2 value (the p = 2 value is the one within 1e-4 of the table)\n", std::pow(c / cl, 3), pe, pe / 2); }
    return 0;
}
