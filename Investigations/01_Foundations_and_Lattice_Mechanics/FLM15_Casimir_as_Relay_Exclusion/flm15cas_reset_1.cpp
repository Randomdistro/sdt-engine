// FLM15-cas blank-slate run 1 (2026-10-07): Casimir pressure from relay-mode counting; Round 1 (thermal pricing at T_CMB) and Round 2 (scale-free price).
// Registered in the PROMPT (2026-10-03) and FLM15cas_RESET_ASSESSMENT_2026-10-07.md §4 before this file existed. Author: J. C. Harvey, Melbourne.
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
static double gq(double q, double lam) { return std::exp(-lam * q) * (q * q / lam + 2 * q / (lam * lam) + 2 / (lam * lam * lam)) / (2 * PI); }
static double Ghat(double w, double lam) { std::complex<double> z = std::pow(std::complex<double>(lam, -w), -3.0); return 2.0 / (PI * w) * z.imag(); }
static double simpson(double (*f)(double, void*), void* p, double a, double b, int n) { double h = (b - a) / n, s = f(a, p) + f(b, p); for (int i = 1; i < n; ++i) s += f(a + i * h, p) * (i % 2 ? 4 : 2); return s * h / 3; }
struct QP { double q, lam; };
static double integrandG(double s, void* p) { QP* qp = (QP*)p; return s * s * std::exp(-qp->lam * s) / (2 * PI); }
static double bose(double x, void*) { return x < 1e-12 ? 0.0 : x * x * x / std::expm1(x); }
// direct sum minus integral, compensated
static double Ediff_direct(double d, double lam) {
    double h = PI / d, sum = 0, comp = 0; int N = (int)(80.0 / (lam * h)) + 10;
    for (int n = N; n >= 1; --n) { double y = 2 * gq(n * h, lam) - comp, t = sum + y; comp = (t - sum) - y; sum = t; }
    return gq(0, lam) + sum - (2 * d / PI) * 3.0 / (PI * lam * lam * lam * lam);
}
static double Ediff_poisson(double d, double lam) { double s = 0; for (int k = 200000; k >= 1; --k) s += Ghat(2.0 * k * d, lam); return (2 * d / PI) * s; }

int main() {
    std::printf("FLM15-cas blank-slate run 1 (registered 2026-10-03 in the PROMPT; assessment 2026-10-07)\n==========================================================================================\n\n");
    int fails = 0;
    // ---- V1 Poisson summation
    bool v1 = true; double w1 = 0;
    for (double t : {0.37, 1.9}) { double l = 0, r = 0; for (int n = -60; n <= 60; ++n) l += std::exp(-PI * n * n * t); for (int k = -60; k <= 60; ++k) r += std::exp(-PI * k * k / t); r /= std::sqrt(t); w1 = std::max(w1, std::fabs(l / r - 1)); }
    v1 = w1 < 1e-13; std::printf("[V1] Poisson summation identity at t = 0.37, 1.9: worst relative difference %.2e -> %s\n", w1, v1 ? "met" : "NOT MET"); if (!v1) ++fails;
    // ---- V2 closed form of g(q)
    double w2 = 0; for (double q : {0.0, 1.5, 4.0}) { double lam = 1.0; QP p{q, lam}; double num = simpson(integrandG, &p, q, q + 60.0, 400000); w2 = std::max(w2, std::fabs(num / gq(q, lam) - 1)); }
    bool v2 = w2 < 1e-9; std::printf("[V2] g(q) closed form against quadrature at q = 0, 1.5, 4: worst relative difference %.2e -> %s\n", w2, v2 ? "met" : "NOT MET"); if (!v2) ++fails;
    // ---- V3 Bose integral
    double b = simpson(bose, nullptr, 0, 80, 400000), b0 = std::pow(PI, 4) / 15; bool v3 = std::fabs(b / b0 - 1) < 1e-8;
    std::printf("[V3] integral of x^3/(e^x - 1) = %.10f against pi^4/15 = %.10f (relative %.2e) -> %s\n", b, b0, std::fabs(b / b0 - 1), v3 ? "met" : "NOT MET"); if (!v3) ++fails;
    // ---- V4 two routes
    double d0 = 1.0, e1 = Ediff_direct(d0, 0.08 * d0), e2 = Ediff_poisson(d0, 0.08 * d0); double lim = 0; for (int k = 1; k <= 2000000; ++k) lim += 1.0 / std::pow(2.0 * k, 4); lim = -(2.0 / PI) * (2.0 / PI) * lim; // -(2d/pi)(2/pi) sum 1/(2kd)^4 with d = 1
    bool v4 = std::fabs(e1 / e2 - 1) < 1e-8 && std::fabs(lim / (-PI * PI / 360) - 1) < 1e-6;
    std::printf("[V4] lambda/d = 0.08: direct %.10e, Poisson %.10e (relative %.2e) ; lambda -> 0 Poisson limit %.8e vs -pi^2/360 = %.8e (relative %.2e) -> %s\n\n", e1, e2, std::fabs(e1 / e2 - 1), lim, -PI * PI / 360, std::fabs(lim / (-PI * PI / 360) - 1), v4 ? "met" : "NOT MET"); if (!v4) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    // ---- Round 1
    const double hb = M::hbar, c = M::c, kB = M::k_B, T = M::T_CMB, kT = kB * T, uC = law_I::u_CMB, Pout = uC / 3;
    const double zeta3 = 1.2020569031595942; const double F0 = -kT * std::pow(kT / (hb * c), 2) * zeta3 / (2 * PI);
    std::printf("[R1] thermal pricing at T_CMB = %.4f K: k_B T = %.4e eV ; u_CMB/3 = %.5e Pa (pi^2/45 (kT)^4/(hbar c)^3 = %.5e) ; n = 0 gap free energy per area = %.4e J/m^2 (independent of d)\n", T, kT / M::eV_to_J, Pout, PI * PI / 45 * std::pow(kT, 4) / std::pow(hb * c, 3), F0);
    std::vector<double> ld, lP; std::printf("     d [um]     n=1 exponent (ln occupation)   P_net [Pa]     P_ideal = pi^2 hbar c/(240 d^4) [Pa]   P_net/P_ideal\n");
    for (double dum : {0.1, 0.2, 0.4, 0.8, 1.6, 3.2, 6.4, 10.0}) { double d = dum * 1e-6, x1 = PI * hb * c / (d * kT), Pid = PI * PI * hb * c / (240 * std::pow(d, 4)), Pn = Pout; ld.push_back(std::log(d)); lP.push_back(std::log(Pn));
        std::printf("     %-10.2f %-31.1f %-14.5e %-38.5e %.3e\n", dum, -x1, Pn, Pid, Pn / Pid); }
    double sx = 0, sy = 0, sxx = 0, sxy = 0; int n = (int)ld.size(); for (int i = 0; i < n; ++i) { sx += ld[i]; sy += lP[i]; sxx += ld[i] * ld[i]; sxy += ld[i] * lP[i]; } double slope = (n * sxy - sx * sy) / (n * sxx - sx * sx);
    double Pid1 = PI * PI * hb * c / (240 * 1e-24);
    std::printf("     fitted exponent of P(d) = %.6f (the net pressure scales as d^%.6f) ; at d = 1 um: P_net/P_ideal = %.3e\n", -slope, slope, Pout / Pid1);
    bool R1 = std::fabs(-slope - 4) > 1e-3 || std::fabs(Pout / Pid1 - 1) > 0.05;
    std::printf("     Round 1 rejection criterion (exponent != 4 or coefficient outside +/-5%% of pi^2 hbar c/240): %s\n\n", R1 ? "MET (rejected)" : "not met");

    // ---- Round 2
    std::printf("[R2] scale-free price a hbar omega: E_diff(lambda)/(a hbar c/d^3), d = 1 (units), routes 1 (direct) and 2 (Poisson)\n");
    const double xs[5] = {0.08, 0.06, 0.04, 0.03, 0.02}; double Ev[5];
    for (int i = 0; i < 5; ++i) { double d = 1.0, lam = xs[i] * d, a = Ediff_direct(d, lam), bb = Ediff_poisson(d, lam); Ev[i] = bb; std::printf("     lambda/d = %.2f : direct %.10e   Poisson %.10e   relative %.2e\n", xs[i], a, bb, std::fabs(a / bb - 1)); }
    // Richardson: polynomial in (lambda/d)^2 through the five points
    double A[5][5], rhs[5]; for (int i = 0; i < 5; ++i) { double x2 = xs[i] * xs[i]; for (int j = 0; j < 5; ++j) A[i][j] = std::pow(x2, j); rhs[i] = Ev[i]; }
    for (int i = 0; i < 5; ++i) { int p = i; for (int r = i + 1; r < 5; ++r) if (std::fabs(A[r][i]) > std::fabs(A[p][i])) p = r; for (int j = 0; j < 5; ++j) std::swap(A[i][j], A[p][j]); std::swap(rhs[i], rhs[p]); for (int r = i + 1; r < 5; ++r) { double f = A[r][i] / A[i][i]; for (int j = i; j < 5; ++j) A[r][j] -= f * A[i][j]; rhs[r] -= f * rhs[i]; } }
    double sol[5]; for (int i = 4; i >= 0; --i) { double s = rhs[i]; for (int j = i + 1; j < 5; ++j) s -= A[i][j] * sol[j]; sol[i] = s / A[i][i]; }
    double E0 = sol[0], Eex = -PI * PI / 360;
    std::printf("     Richardson (polynomial in (lambda/d)^2): E(0) = %.10e ; exact -pi^2/360 = %.10e ; relative difference %.2e\n", E0, Eex, std::fabs(E0 / Eex - 1));
    // exponent of the force from E(d) = C/d^3 at fixed extrapolated coefficient, checked with the direct route at lambda/d = 0.02 over d = 0.5..8
    double sl[2] = {0, 0}; { std::vector<double> lx, ly; for (double d : {0.5, 1.0, 2.0, 4.0, 8.0}) { double lam = 0.02 * d, E = Ediff_poisson(d, lam); lx.push_back(std::log(d)); ly.push_back(std::log(std::fabs(E))); } int m = (int)lx.size(); double a1 = 0, a2 = 0, a3 = 0, a4 = 0; for (int i = 0; i < m; ++i) { a1 += lx[i]; a2 += ly[i]; a3 += lx[i] * lx[i]; a4 += lx[i] * ly[i]; } sl[0] = (m * a4 - a1 * a2) / (m * a3 - a1 * a1); }
    std::printf("     |E_diff| ~ d^%.8f at fixed lambda/d = 0.02 (the force exponent is 1 - %.8f = %.8f in magnitude)\n", sl[0], sl[0], -sl[0] + 1);
    bool R2c = std::fabs(E0 / Eex - 1) > 1e-6, R2e = std::fabs(-sl[0] + 1 - 4) > 1e-6;
    std::printf("     Round 2 instrument-level criteria: coefficient off by > 1e-6 : %s ; exponent off by > 1e-6 : %s\n", R2c ? "MET" : "not met", R2e ? "MET" : "not met");
    std::printf("     force per unit a: P = a pi^2 hbar c/(120 d^4) ; ratio to the ideal form pi^2 hbar c/(240 d^4) = 2a\n");
    struct C { const char* nm; double a; } cs[3] = {{"a = 1/2 (zero-point quantum; prohibited input as a derivation, rival form)", 0.5}, {"a = 1/2 (720-degree double cover of the PPT17 Bohr-seat tube; underived)", 0.5}, {"a = 1 (one full tick per mode)", 1.0}};
    for (auto& cc : cs) std::printf("     %-80s ratio to ideal = %.3f ; constraint 1.000 +/- 0.010 -> %s\n", cc.nm, 2 * cc.a, std::fabs(2 * cc.a - 1) <= 0.01 ? "consistent" : "excluded");
    const double nuc = 3e15, kc = 2 * PI * nuc / c, uf = 0.5 * hb * c * std::pow(kc, 4) / (4 * PI * PI);
    std::printf("\n[report-only] a = 1/2 floor to nu_c = 3e15 Hz (given by the prompt): u = a hbar c k_c^4/(4 pi^2) = %.4e J/m^3 ; law_I::P_conv = %.4e Pa ; ratio %.3e\n", uf, law_I::P_conv, uf / law_I::P_conv);
    return 0;
}
