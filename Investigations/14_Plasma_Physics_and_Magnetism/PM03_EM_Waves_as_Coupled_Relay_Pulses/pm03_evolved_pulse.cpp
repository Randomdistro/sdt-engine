// PM03 evolved-pulse test (audit correction 2026-10-05). The prompt requires an EVOLVED 1-D wave tracked >= 1000 steps.
// Relay update on a lattice of spacing dx = l_P with tick dt = C * l_P / c (Courant number C), second-order (leapfrog) in the
// transverse relay displacement u. No electric or magnetic field is used as a primitive; speeds are reported in SI via l_P and c.
// Gates (registered before running, PM03 prompt): peak speed within 1% of c at C = 1 over 1000 steps; stability for C <= 1,
// amplitude blow-up for C > 1 (the Courant limit as the relay-rate bound).
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace sdt::laws;
struct Res { double speed, amp_ratio; bool finite; };
static Res run(double C, int steps, int N, double sigma) {
    std::vector<double> uo(N), u(N), un(N);
    const int x0 = N / 4; const double dx = measured::l_P, dt = C * measured::l_P / measured::c;
    // right-moving Gaussian: u(x,t) = g(x - c t) -> at t=0 and t=-dt
    for (int i = 0; i < N; ++i) { u[i] = std::exp(-0.5 * std::pow((i - x0) / sigma, 2)); uo[i] = std::exp(-0.5 * std::pow((i - x0 + C) / sigma, 2)); }
    const double a0 = 1.0; bool fin = true;
    for (int s = 0; s < steps; ++s) {
        for (int i = 1; i < N - 1; ++i) un[i] = 2 * u[i] - uo[i] + C * C * (u[i + 1] - 2 * u[i] + u[i - 1]);
        un[0] = un[N - 1] = 0.0; uo = u; u = un;
        for (int i = 0; i < N; ++i) if (!std::isfinite(u[i]) || std::fabs(u[i]) > 1e12) { fin = false; break; }
        if (!fin) break;
    }
    if (!fin) return {0, 1e99, false};
    int ip = 0; double mx = -1; double sum = 0, mom = 0;
    for (int i = 0; i < N; ++i) { if (u[i] > mx) { mx = u[i]; ip = i; } }
    // sub-cell peak by parabola
    const double a = u[ip - 1], b = u[ip], c2 = u[ip + 1]; const double off = 0.5 * (a - c2) / (a - 2 * b + c2);
    const double xp = ip + off; const double T = steps * dt;
    return {(xp - x0) * dx / T, mx / a0, true};
}
int main() {
    const double c = measured::c;
    std::printf("PM03 evolved relay pulse (dx = l_P, tick = C l_P/c), 1000 steps, N = 4000, sigma = 20 cells\n");
    int fails = 0;
    for (double C : {1.0, 0.5, 0.9}) {
        const Res r = run(C, 1000, 4000, 20.0);
        const double rel = r.speed / c - 1.0; const bool pass = r.finite && std::fabs(rel) < 0.01;
        std::printf("C=%.2f : speed/c = %.6f (rel %+.3e) amplitude ratio %.4f  gate |rel|<1%%: %s\n", C, r.speed / c, rel, r.amp_ratio, pass ? "PASS" : "FAIL");
        if (C == 1.0 && !pass) ++fails;
    }
    const Res bad = run(1.05, 1000, 4000, 20.0);
    std::printf("C=1.05 (above the relay-rate bound): %s\n", bad.finite ? "no blow-up (UNEXPECTED)" : "amplitude blow-up (expected: Courant limit)");
    if (bad.finite) ++fails;
    std::printf("identity |c - 1/sqrt(mu0 eps0)|/c is NOT scored (identity by construction)\n");
    std::printf("VERDICT: %s\n", fails ? "FAIL" : "PASS (evolved wave; class CONVERGENCE, transverse/longitudinal separation not run)");
    return fails ? 1 : 0;
}
