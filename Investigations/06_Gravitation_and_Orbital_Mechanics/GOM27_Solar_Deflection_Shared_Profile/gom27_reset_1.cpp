// GOM27 blank-slate run 1 (2026-10-11). Registration: GOM27_RESET_ASSESSMENT_2026-10-11.md sections 0-2 (written before this file existed).
// Exact ray-traced deflection for n(r) = 1/(1 - K/r)^2 (K = koppa), by the algebraically stable half-angle integral (u = 1 - s^2), Gauss-Legendre.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = 3.14159265358979323846;

static void gauleg(int n, std::vector<double>& x, std::vector<double>& w) { x.assign(n, 0); w.assign(n, 0); for (int i = 0; i < (n + 1) / 2; ++i) { double z = std::cos(PI * (i + 0.75) / (n + 0.5)), pp = 0; for (int it = 0; it < 100; ++it) { double p1 = 1, p2 = 0; for (int j = 0; j < n; ++j) { double p3 = p2; p2 = p1; p1 = ((2.0 * j + 1.0) * z * p2 - j * p3) / (j + 1); } pp = n * (z * p1 - p2) / (z * z - 1); double z1 = z; z = z1 - p1 / pp; if (std::fabs(z - z1) < 1e-15) break; } x[i] = 0.5 * (1 - z); x[n - 1 - i] = 0.5 * (1 + z); w[i] = w[n - 1 - i] = 1.0 / ((1 - z * z) * pp * pp); } }   // nodes mapped to [0,1], weights sum to 1
static double solveR0(double K, double b) { double r = b; for (int i = 0; i < 200; ++i) { double h = r * r * r / ((r - K) * (r - K)), dh = (3 * r * r * (r - K) - 2 * r * r * r) / std::pow(r - K, 3); double rn = r - (h - b) / dh; if (std::fabs(rn - r) < 1e-15 * r) { r = rn; break; } r = rn; } return r; }
static double deflection(double K, double r0, int N, double* bOut = nullptr) {
    static std::vector<double> x, w; static int nn = 0; if (nn != N) { gauleg(N, x, w); nn = N; }
    const double h0 = r0 * r0 * r0 / ((r0 - K) * (r0 - K)), n0 = h0 / r0, p0 = std::sqrt(r0); if (bOut) *bOut = h0; double sum = 0;
    for (int i = 0; i < N; ++i) { double s = x[i], u = 1 - s * s, r = r0 / u, p = std::sqrt(r); double dr = r0 * s * s / u, dp = dr / (p + p0);
        double Q1 = r * r0 - K * (r + p * p0 + r0), Q2 = p * p * p * (r0 - K) + p0 * p0 * p0 * (r - K); double h = r * r * r / ((r - K) * (r - K)); double hmh0 = dp * Q1 * Q2 / ((r - K) * (r - K) * (r0 - K) * (r0 - K));
        double g = hmh0 * (h + h0) / (r * r); double f = 2.0 * s * n0 / std::sqrt(g) - 2.0 / std::sqrt(2.0 - s * s); sum += w[i] * f; }
    return 2.0 * sum; }

int main() {
    std::printf("GOM27 blank-slate run 1 (registered in GOM27_RESET_ASSESSMENT_2026-10-11.md sections 0-2)\n=======================================================================\n\n");
    int fails = 0; const double KS = 1476.351201, RS = M::R_Sun, asec = 206264.806247, KGM = 1.32712440e20 / (M::c * M::c);
    // E: K -> 0
    { double K = 1e-9, r0 = solveR0(K, 1e9), d = deflection(K, r0, 64); bool ok = std::fabs(d) < 1e-14 + 10 * 4 * K / 1e9; std::printf("[E] tiny K (1e-9 m) at b = 1e9 m: delta = %.3e (4K/b = %.3e) -> %s\n", d, 4 * K / 1e9, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // A
    for (double ratio : {1e-3, 1e-4}) { double b = 1.0e9, K = ratio * b, r0 = solveR0(K, b), d = deflection(K, r0, 64), wf = 4 * K / b; bool ok = std::fabs(d / wf - 1) < 0.05; std::printf("[A] reduced case K/b = %.0e: delta = %.9e, 4K/b = %.9e, relative %+.3e (gate 5%%) -> %s\n", ratio, d, wf, d / wf - 1, ok ? "met" : "NOT MET"); if (!ok) ++fails; }
    // B, C, D
    { double b = 5 * RS, r0 = solveR0(KS, b), d = deflection(KS, r0, 64), d2 = deflection(KS, r0, 128), wf = 4 * KS / b; bool okB = std::fabs(d / wf - 1) < 0.02, okC = std::fabs(d2 / d - 1) < 1e-3; double h0 = r0 * r0 * r0 / ((r0 - KS) * (r0 - KS)); bool okD = std::fabs(h0 / b - 1) < 1e-10;
      std::printf("[B] solar K at b = 5 R_sun: delta = %.9e, 4K/b = %.9e, relative %+.3e (gate 2%%) -> %s\n[C] 64 against 128 nodes: relative change %.2e (gate 1e-3) -> %s\n[D] turning identity |n(r0) r0 - b|/b = %.2e (gate 1e-10) -> %s\n\n", d, wf, d / wf - 1, okB ? "met" : "NOT MET", std::fabs(d2 / d - 1), okC ? "met" : "NOT MET", std::fabs(h0 / b - 1), okD ? "met" : "NOT MET"); if (!okB || !okC || !okD) ++fails; }
    if (fails) { std::printf("INSTRUMENT TESTS NOT MET -> G0\n"); return 1; } std::printf("INSTRUMENT TESTS A-E: met\n\n");
    // second-order coefficient
    { double b = 1.0e9, K = 1e-4 * b, r0 = solveR0(K, b), d = deflection(K, r0, 128), c2 = (d - 4 * K / b) / ((K / b) * (K / b)); double K2 = 1e-3 * b, r02 = solveR0(K2, b), d2 = deflection(K2, r02, 128), c22 = (d2 - 4 * K2 / b) / ((K2 / b) * (K2 / b));
      std::printf("Second-order coefficient c2 = (delta - 4K/b)/(K/b)^2: %.4f at K/b = 1e-4, %.4f at K/b = 1e-3 (Schwarzschild 15 pi/4 = %.4f)\n\n", c2, c22, 15 * PI / 4); }
    // scan
    std::printf("SCAN with the frozen K = %.6f m: b/R_sun, r0/R_sun, delta [rad], delta [arcsec], delta/delta_wf - 1, c2-equivalent\n", KS);
    const double bs[10] = {1.0, 1.01, 1.05, 1.1, 1.2, 1.5, 2, 3, 5, 10};
    for (double fb : bs) { double b = fb * RS, r0 = solveR0(KS, b), d = deflection(KS, r0, 128), wf = 4 * KS / b; std::printf("  %5.2f %12.9f %.9e %.6f %+.3e %.3f\n", fb, r0 / RS, d, d * asec, d / wf - 1, (d - wf) / ((KS / b) * (KS / b))); }
    { double K1 = M::R_Sun / (bridge::k_Sun * bridge::k_Sun), b = RS, r0a = solveR0(KS, b), da = deflection(KS, r0a, 128), r0b = solveR0(K1, b), db = deflection(K1, r0b, 128), K24 = 1476.8693, r0c = solveR0(K24, b), dc = deflection(K24, r0c, 128);
      std::printf("\nLimb (b = R_sun): K = 1476.3512 m: %.6f arcsec ; engine koppa_Sun = %.4f m: %.6f arcsec ; GOM26 2024 value 1476.8693 m: %.6f arcsec\n", da * asec, K1, db * asec, dc * asec);
      std::printf("Reference (information only): the general-relativistic weak-field value for GM_sun/c^2 = %.4f m : 4 GM/(c^2 R) = %.6f arcsec\n", KGM, 4 * KGM / RS * asec);
      double ge = 2 * KS / KGM - 1, sg = 2 * 4e-4 * KS / KGM; std::printf("gamma-equivalent of K = 1476.3512 m: 2K/(GM/c^2) - 1 = %.5f (sigma from the K systematic 4e-4: +-%.5f; from 6e-4: +-%.5f) against the VLBA gamma = 0.9998 +- 0.0003 : difference %+.5f = %.2f sigma (combined with 0.0003 and 4e-4)\n", ge, sg, 2 * 6e-4 * KS / KGM, ge - 0.9998, std::fabs(ge - 0.9998) / std::sqrt(0.0003 * 0.0003 + sg * sg)); }
    std::printf("\nD5 data gate: row-level tables are MODEL-PROCESSED residuals about the GR (gamma = 1) differential bending (D not tabulated); only the global gamma summary is comparable -> PENDING_DATA / UNADJUDICATED; no bin excluded.\n");
    return 0;
}
