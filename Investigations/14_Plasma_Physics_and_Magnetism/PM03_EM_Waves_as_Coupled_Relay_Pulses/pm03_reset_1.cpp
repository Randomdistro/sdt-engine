// PM03 blank-slate run 1 (2026-10-10). Registration: PM03_RESET_ASSESSMENT_2026-10-10.md sections 0-2 (written before this file existed).
//  Leapfrog u^{n+1} = 2u^n - u^{n-1} + C^2 (u_{i+1} - 2u_i + u_{i-1}) on a ring of 512 cells; right-moving Gaussian, u^{-1}(x) = f(x + C dx).
//  Phase 0 identity; V1 exact shift at C=1; V2 d'Alembert at C=0.5; V3 discrete energy; Phase 1 peak speed over 1500 steps; stability at C=1.05; analytic dispersion; Phase 2 labels only.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <vector>
namespace M = sdt::laws::measured;

static const int N = 512;
struct Run { double vpeak_over_c, amp_end_over_0, maxamp_over_0, e_drift; };
static double wrapd(double x) { while (x < -N / 2.0) x += N; while (x >= N / 2.0) x -= N; return x; }
static double gauss(double i, double x0, double s) { double d = wrapd(i - x0); return std::exp(-d * d / (2 * s * s)); }

// Evolve `steps` leapfrog steps; positions are tracked at levels 0..steps-1; the returned finalState is level `steps`.
static Run run(double C, double sigma, int steps, std::vector<double>* finalState = nullptr) {
    const double x0 = 100.0; std::vector<double> um(N), u(N), un(N);
    for (int i = 0; i < N; ++i) { u[i] = gauss(i, x0, sigma); um[i] = gauss(i + C, x0, sigma); }       // u^0 = f(x), u^{-1} = f(x + C dx): right-moving
    auto energy = [&](const std::vector<double>& a, const std::vector<double>& b) { double e = 0; for (int i = 0; i < N; ++i) { double da = a[i] - b[i]; e += da * da / (C * C) + (a[(i + 1) % N] - a[i]) * (b[(i + 1) % N] - b[i]); } return e; };
    double amp0 = 0; for (double v : u) amp0 = std::max(amp0, std::fabs(v));
    std::vector<double> posn, stp; double prev = 0, unwrapped = 0, maxamp = amp0, emax = 0, eref = 0;
    for (int n = 0; n < steps; ++n) {
        int im = 0; for (int i = 1; i < N; ++i) if (std::fabs(u[i]) > std::fabs(u[im])) im = i;
        double yl = u[(im + N - 1) % N], yc = u[im], yr = u[(im + 1) % N], den = yl - 2 * yc + yr, off = den != 0 ? 0.5 * (yl - yr) / den : 0.0, pos = im + off;
        if (n == 0) unwrapped = pos; else { double d = pos - prev; while (d < -N / 2.0) d += N; while (d >= N / 2.0) d -= N; unwrapped += d; }
        prev = pos; posn.push_back(unwrapped); stp.push_back(n);
        for (int i = 0; i < N; ++i) un[i] = 2 * u[i] - um[i] + C * C * (u[(i + 1) % N] - 2 * u[i] + u[(i + N - 1) % N]);
        double e = energy(un, u); if (n == 0) eref = e; if (eref != 0) emax = std::max(emax, std::fabs(e / eref - 1));
        um = u; u = un; double a = 0; for (double v : u) a = std::max(a, std::fabs(v)); maxamp = std::max(maxamp, a);
    }
    double mx = 0, my = 0; size_t m = posn.size(); for (size_t i = 0; i < m; ++i) { mx += stp[i]; my += posn[i]; } mx /= m; my /= m; double sxy = 0, sxx = 0; for (size_t i = 0; i < m; ++i) { sxy += (stp[i] - mx) * (posn[i] - my); sxx += (stp[i] - mx) * (stp[i] - mx); }
    double amp_end = 0; for (double v : u) amp_end = std::max(amp_end, std::fabs(v)); if (finalState) *finalState = u;
    return {sxy / sxx / C, amp_end / amp0, maxamp / amp0, emax};
}

int main() {
    std::printf("PM03 blank-slate run 1 (registered in PM03_RESET_ASSESSMENT_2026-10-10.md sections 0-2)\n=======================================================================\n\n");
    int fails = 0;
    const double mu0 = 1.25663706212e-6, eps0 = 8.8541878128e-12; double id = std::fabs(M::c - 1.0 / std::sqrt(mu0 * eps0)) / M::c; std::printf("[Phase 0] |c - 1/sqrt(mu0 eps0)|/c = %.3e (gate 1e-9) -> %s\n", id, id < 1e-9 ? "met" : "NOT MET");
    { std::vector<double> s; run(1.0, 8.0, 300, &s); double err = 0; for (int i = 0; i < N; ++i) err = std::max(err, std::fabs(s[i] - gauss(i, 100.0 + 300, 8.0))); bool ok = err < 1e-12; std::printf("[V1] C = 1, 300 steps: max |u - shifted initial| = %.2e -> %s\n", err, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // Amendment 1 (2026-10-10, after attempt 1 was seen; attempt-1 output kept as pm03_reset_1_attempt1_G0.txt): the registered V2 gate "agreement with d'Alembert to 1e-3" was a tolerance I had not derived.
    // The lattice dispersion (-(1-C^2) q^2/24, about -5e-4 in speed for sigma = 8) shifts the pulse by about 0.2 cells over 500 cells of travel, a few percent in shape; attempt 1 measured 4.35e-2.
    // V1 (8e-25) and V3 (6e-15) already showed the stencil is right. Corrected V2: the finite-difference result equals the EXACT DISCRETE solution (Fourier modes with omega = (2/dt) asin(C sin(k/2))) to 1e-10;
    // the d'Alembert difference is reported as a descriptive measure of numerical dispersion, not a gate.
    { std::vector<double> s; Run r = run(0.5, 8.0, 1000, &s); const double C = 0.5; const int steps = 1000; std::vector<double> ex(N, 0.0); const double TWO_PI = 6.28318530717958647692;
      std::vector<double> f0(N), fm(N); for (int i = 0; i < N; ++i) { f0[i] = gauss(i, 100.0, 8.0); fm[i] = gauss(i + C, 100.0, 8.0); }
      for (int kk = 0; kk < N; ++kk) { const double k = TWO_PI * kk / N; const double w = 2.0 * std::asin(C * std::sin(k / 2.0)); const std::complex<double> I(0, 1);
          std::complex<double> u0 = 0, um1 = 0; for (int i = 0; i < N; ++i) { std::complex<double> e = std::exp(std::complex<double>(0, -k * i)); u0 += f0[i] * e; um1 += fm[i] * e; } u0 /= double(N); um1 /= double(N);
          std::complex<double> un;
          if (kk == 0) un = u0 + double(steps) * (u0 - um1);                                   // zero mode: u^{n+1} = 2u^n - u^{n-1}
          else { std::complex<double> A = (um1 - u0 * std::exp(I * w)) / (std::exp(-I * w) - std::exp(I * w)), B = u0 - A; un = A * std::exp(I * w * double(steps)) + B * std::exp(-I * w * double(steps)); }   // u^n = A e^{iwn} + B e^{-iwn}
          for (int i = 0; i < N; ++i) ex[i] += (un * std::exp(std::complex<double>(0, k * i))).real(); }
      double errD = 0, errA = 0; for (int i = 0; i < N; ++i) { errD = std::max(errD, std::fabs(s[i] - ex[i])); errA = std::max(errA, std::fabs(s[i] - gauss(i, 100.0 + 0.5 * 1000, 8.0))); }
      bool ok = errD < 1e-10, ok3 = r.e_drift < 1e-10;
      std::printf("[V2] C = 0.5, sigma = 8, 1000 steps vs the exact discrete (Fourier) solution: max error %.2e (gate 1e-10) -> %s ; descriptive: difference from d'Alembert %.2e (numerical dispersion)\n[V3] discrete energy drift over 1000 steps %.2e (gate 1e-10) -> %s\n", errD, ok ? "met" : "NOT MET", errA, r.e_drift, ok3 ? "met" : "NOT MET"); if (!ok || !ok3) ++fails; }
    if (fails) { std::printf("VALIDATIONS NOT MET -> G0\n"); return 1; } std::printf("VALIDATIONS: met\n\n");
    struct Cfg { double C, s; } cf[7] = {{1.0, 8}, {1.0, 1}, {0.9, 8}, {0.9, 2}, {0.5, 8}, {0.5, 2}, {0.5, 1}}; bool all = true;
    for (auto& c : cf) { Run r = run(c.C, c.s, 1500); bool ok = std::fabs(r.vpeak_over_c - 1) < 0.01 && r.maxamp_over_0 <= 1.01; if (!ok) all = false; std::printf("[Phase 1] C = %.2f, sigma = %g cells: v_peak/c = %.8f ; final peak / initial = %.4f ; max|u| over run / initial = %.4f ; energy drift %.1e -> %s\n", c.C, c.s, r.vpeak_over_c, r.amp_end_over_0, r.maxamp_over_0, r.e_drift, ok ? "criterion met" : "criterion NOT met"); }
    std::printf("Phase 1 (all seven): %s\n", all ? "met" : "NOT met in at least one configuration");
    { Run r = run(1.05, 8.0, 1500); std::printf("[F3 stability] C = 1.05, sigma = 8: max|u| over 1500 steps / initial = %.3e ; final peak / initial = %.3e -> %s\n\n", r.maxamp_over_0, r.amp_end_over_0, r.maxamp_over_0 > 1e3 ? "UNSTABLE (class populated)" : "bounded"); }
    const double PI = 3.14159265358979323846; std::printf("---- Analytic lattice dispersion ----\n1-D leapfrog: q, then v_p/c and v_g/c for C = 0.5 and C = 1\n");
    for (double q : {0.1, 0.5, 1.0, PI / 2, PI}) { std::printf("  q = %.4f :", q); for (double C : {0.5, 1.0}) { double s = C * std::sin(q / 2), vp = 2.0 / (C * q) * std::asin(s), vg = std::cos(q / 2) / std::sqrt(1 - s * s); std::printf("  C = %.1f: v_p/c = %.6f, v_g/c = %.6f ;", C, vp, vg); } std::printf("\n"); }
    const double C3 = 1.0 / std::sqrt(3.0); std::printf("3-D cubic, C = 1/sqrt(3): v_p/c along the axis and along the diagonal (|q| fixed)\n");
    for (double q : {0.1, 0.5, 1.0}) { double sa = C3 * std::sin(q / 2), va = 2.0 / (C3 * q) * std::asin(sa); double qd = q / std::sqrt(3.0), sd = C3 * std::sqrt(3.0) * std::sin(qd / 2), vd = 2.0 / (C3 * q) * std::asin(sd); std::printf("  |q| = %.2f : axis %.8f ; diagonal %.8f ; (axis - diagonal) = %.3e\n", q, va, vd, va - vd); }
    { const double Ej = 31e9 * 1.602176634e-19; double q = Ej * M::l_P / (M::hbar * M::c); std::printf("Physical scale: 31 GeV photon, dx = l_P: q = E l_P/(hbar c) = %.3e ; delta v_p/c = -q^2/36 (3-D axis, C = 1/sqrt3) = %.3e ; -(1-C^2) q^2/24 with C = 0.5 = %.3e\n\n", q, -q * q / 36.0, -(1 - 0.25) * q * q / 24.0); }
    std::printf("[Phase 2] c_T = c = %.1f m/s ; c_L = c/sqrt(3) = %.1f m/s : IDENTIFICATION (FD05); not computed or tested here (D3)\n[Phase 3] DEFER\n", M::c, M::c / std::sqrt(3.0));
    return 0;
}
