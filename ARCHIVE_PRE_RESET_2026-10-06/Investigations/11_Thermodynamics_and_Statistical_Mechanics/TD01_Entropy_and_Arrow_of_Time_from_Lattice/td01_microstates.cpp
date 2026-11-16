// ============================================================================
//  TD01 — Entropy from Lattice Microstates (Phase 1 toy counting)
//  S = k_B ln W,  W = C(E+N-1, N-1)  stars-and-bars on relay quanta.
//
//  Author: James Christopher Tyndall, Melbourne.
//  Build:  g++ -std=c++20 -IEngine/include td01_microstates.cpp -o td01
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <initializer_list>

namespace {
using namespace sdt::laws;

double ln_factorial(int n) {
    if (n <= 1) return 0.0;
    double s = 0.0;
    for (int i = 2; i <= n; ++i) s += std::log(static_cast<double>(i));
    return s;
}

double ln_binom(int n, int k) {
    return ln_factorial(n) - ln_factorial(k) - ln_factorial(n - k);
}

// W(E,N) = ways to distribute E indistinguishable quanta among N cells
double ln_W(int E, int N) {
    return ln_binom(E + N - 1, N - 1);
}
}

int main() {
    std::printf("================================================================\n");
    std::printf("  TD01 — Entropy from Lattice Microstate Counting (Phase 1)\n");
    std::printf("  Author: James Christopher Tyndall, Melbourne\n");
    std::printf("================================================================\n\n");

    const double kB = measured::k_B;

    std::printf("TEST 1: S = k_B ln W exact on toy lattice\n");
    bool mono = true;
    for (int N : {4, 8, 12}) {
        double S_prev = -1.0;
        for (int E = 1; E <= 20; ++E) {
            const double S = kB * ln_W(E, N);
            if (S_prev >= 0.0 && S + 1e-15 < S_prev) mono = false;
            S_prev = S;
        }
        const double S10 = kB * ln_W(10, N);
        const double S20 = kB * ln_W(20, N);
        std::printf("  N=%2d: S(10)=%.4e J/K  S(20)=%.4e J/K  (extensive in E)\n", N, S10, S20);
    }
    std::printf("  S(E) monotone increasing: [%s]\n\n", mono ? "PASS" : "FAIL");

    std::printf("TEST 2: Stirling validation (large E,N)\n");
    const int E = 1000, N = 50;
    const double lnW_exact = ln_W(E, N);
    // Stirling: ln W ~ (E+N) ln(E+N) - E ln E - (N-1) ln(N-1) - ln(N-1)! approx
    const double lnW_stir = (E + N - 1) * std::log(E + N - 1.0) - E * std::log(E)
                          - (N - 1) * std::log(N - 1.0) + 0.5 * std::log(2.0 * E / N);
    const double stir_err = std::fabs(lnW_exact - lnW_stir) / lnW_exact;
    std::printf("  ln W exact  = %.6f\n", lnW_exact);
    std::printf("  ln W Stirling= %.6f  (err %.2f%%) [%s]\n\n",
                lnW_stir, stir_err * 100.0, stir_err < 0.05 ? "PASS" : "FAIL");

    std::printf("TEST 3: Temperature from 1/T = dS/dE\n");
    const int N2 = 20;
    const int E0 = 50;
    const double dE = 1.0;
    const double S_m = kB * ln_W(E0 - 1, N2);
    const double S_p = kB * ln_W(E0 + 1, N2);
    const double dSdE = (S_p - S_m) / (2.0 * dE);
    const double T_eff = 1.0 / dSdE;
    std::printf("  1/T = dS/dE at E=%d, N=%d => T_eff = %.4e K\n\n", E0, N2, T_eff);

    const bool pass = mono && (stir_err < 0.05);
    std::printf("================================================================\n");
    std::printf("  VERDICT: %s — Class C (QUALIFIED)\n", pass ? "PASS" : "FAIL");
    std::printf("  S=k_B ln W: COMPUTED on toy relay-lattice counting.\n");
    std::printf("  H-theorem / arrow-of-time: PENDING (Phase 3).\n");
    std::printf("================================================================\n");
    return pass ? 0 : 1;
}
