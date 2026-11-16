// Chapter 4 worked-example instruments: shell cancellation, finite-shell corrections, displaced
// observer, relay fidelity, and the engine's Law-I / Law-IV closed forms.
// Pre-registered in Textbook/validation/ch04_PRE_REGISTRATION.md (2026-10-27).
//
//   cl /std:c++20 /EHsc /O2 /I Engine/include /Fe:ch04.exe Textbook/examples/ch04_shell_cancellation.cpp
//   g++ -std=c++20 -O2 -IEngine/include Textbook/examples/ch04_shell_cancellation.cpp -o ch04
//
// Lattice units throughout the lattice sections: cell edge l = 1, content eps = 1, cross-section sigma = 1.
// Author: James Christopher Tyndall, Melbourne.

#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <numbers>

namespace {

using ld = long double;
constexpr ld kPi = std::numbers::pi_v<ld>;

int g_fail = 0;

void report(bool ok, const char* id, const char* what) {
    std::printf("  [%s] %s  %s\n", ok ? "consistent  " : "INCONSISTENT", id, what);
    if (!ok) ++g_fail;
}

long count_ball(int R) {
    long n = 0;
    const long R2 = static_cast<long>(R) * R;
    for (int x = -R; x <= R; ++x)
        for (int y = -R; y <= R; ++y)
            for (int z = -R; z <= R; ++z)
                if (static_cast<long>(x) * x + static_cast<long>(y) * y + static_cast<long>(z) * z <= R2) ++n;
    return n;
}

// sum over 0 < |p| <= R of |p|^-power
ld power_sum(int R, int power) {
    ld s = 0;
    const long R2 = static_cast<long>(R) * R;
    for (int x = -R; x <= R; ++x)
        for (int y = -R; y <= R; ++y)
            for (int z = -R; z <= R; ++z) {
                const long r2 = static_cast<long>(x) * x + static_cast<long>(y) * y + static_cast<long>(z) * z;
                if (r2 == 0 || r2 > R2) continue;
                s += 1.0L / std::pow(static_cast<ld>(r2), static_cast<ld>(power) / 2);
            }
    return s;
}

// Point-kernel and exact-solid-angle sums, one pass.
struct KernelSums { ld point; ld sphere; };

KernelSums kernel_sums(int R) {
    ld sp = 0, ss = 0;
    const ld a2 = 1.0L / kPi;   // sphere target of cross-section sigma = 1
    const long R2 = static_cast<long>(R) * R;
    for (int x = -R; x <= R; ++x)
        for (int y = -R; y <= R; ++y)
            for (int z = -R; z <= R; ++z) {
                const long r2 = static_cast<long>(x) * x + static_cast<long>(y) * y + static_cast<long>(z) * z;
                if (r2 == 0 || r2 > R2) continue;
                const ld d2 = static_cast<ld>(r2);
                sp += 1.0L / (4.0L * kPi * d2);
                ss += 0.5L * (1.0L - std::sqrt(1.0L - a2 / d2));
            }
    return {sp, ss};
}

// Vector arrival imbalance at lattice target t = (s,0,0) from sources in the ball |p| <= R.
struct Vec3 { ld x, y, z; };

Vec3 displaced_vector(int R, int s) {
    Vec3 f{0, 0, 0};
    const long R2 = static_cast<long>(R) * R;
    for (int x = -R; x <= R; ++x)
        for (int y = -R; y <= R; ++y)
            for (int z = -R; z <= R; ++z) {
                if (static_cast<long>(x) * x + static_cast<long>(y) * y + static_cast<long>(z) * z > R2) continue;
                const ld dx = static_cast<ld>(x - s), dy = y, dz = z;
                const ld d2 = dx * dx + dy * dy + dz * dz;
                if (d2 == 0) continue;
                const ld w = 1.0L / (4.0L * kPi * d2 * std::sqrt(d2));
                f.x += dx * w; f.y += dy * w; f.z += dz * w;
            }
    return f;
}

ld rel(ld a, ld b) { return std::fabs(a - b) / std::fabs(b); }

}  // namespace

int main() {
    using namespace sdt::laws;

    std::printf("Chapter 4 instruments â€” shell cancellation\n\n");

    // â”€â”€ Instrument validation â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    std::printf("INSTRUMENT VALIDATION (known answers)\n");
    {
        const int Rs[6] = {1, 2, 3, 4, 5, 10};
        const long ref[6] = {7, 33, 123, 257, 515, 4169};
        bool ok = true;
        for (int i = 0; i < 6; ++i) {
            const long n = count_ball(Rs[i]);
            std::printf("    ball R=%2d  points = %ld  (known %ld)\n", Rs[i], n, ref[i]);
            ok = ok && (n == ref[i]);
        }
        report(ok, "V1", "lattice-point counts in balls");
    }
    {
        const ld s6 = power_sum(64, 6), s12 = power_sum(64, 12);
        std::printf("    sum |p|^-6  = %.6Lf  (known 8.40192)\n", s6);
        std::printf("    sum |p|^-12 = %.6Lf  (known 6.20215)\n", s12);
        report(rel(s6, 8.40192L) < 1e-5L && rel(s12, 6.20215L) < 1e-5L, "V2", "simple-cubic lattice sums");
    }
    const bool instrument_ok = (g_fail == 0);
    if (!instrument_ok) {
        std::printf("\nInstrument validation failed; no T-result is quoted.\n");
        return 2;
    }

    // â”€â”€ T3: lattice shell identity â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    std::printf("\nT3  LATTICE SHELL IDENTITY  (continuum value of each sum is R)\n");
    std::printf("    %5s  %14s  %14s  %12s  %12s\n", "R", "S_pt(R)", "S_sph(R)", "S_pt-R", "S_sph-R");
    {
        bool ok = true;
        for (int R : {16, 32, 64, 128, 256}) {
            const KernelSums k = kernel_sums(R);
            std::printf("    %5d  %14.6Lf  %14.6Lf  %12.6Lf  %12.6Lf\n", R, k.point, k.sphere, k.point - R, k.sphere - R);
            ok = ok && std::fabs(k.point - R) <= 1.0L && std::fabs(k.sphere - R) <= 1.0L;
        }
        report(ok, "T3", "|S - R| <= 1 for all R");
    }

    // Single-shell kernel corrections (feeds Section 4.4)
    std::printf("\n    single-source kernel: exact sphere-target fraction / point kernel - 1\n");
    for (int d : {1, 2, 3, 5, 10, 100}) {
        const ld a2 = 1.0L / kPi, d2 = static_cast<ld>(d) * d;
        const ld exact = 0.5L * (1.0L - std::sqrt(1.0L - a2 / d2));
        const ld point = 1.0L / (4.0L * kPi * d2);
        const ld pred = a2 / (4.0L * d2);   // leading correction +a^2/(4 d^2)
        std::printf("    d=%3d  exact/point - 1 = %+.6Lf   leading-order a^2/(4d^2) = %+.6Lf\n", d, exact / point - 1.0L, pred);
    }

    // â”€â”€ T4: displaced observer â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    std::printf("\nT4  DISPLACED OBSERVER  (continuum: |F| = s/3, toward ball centre => x-component negative)\n");
    {
        bool ok = true;
        const int cases[3][2] = {{64, 4}, {96, 8}, {96, 24}};
        for (const auto& c : cases) {
            const int R = c[0], s = c[1];
            const Vec3 f = displaced_vector(R, s);
            const ld mag = std::sqrt(f.x * f.x + f.y * f.y + f.z * f.z);
            const ld expect = static_cast<ld>(s) / 3.0L;
            std::printf("    R=%3d s=%2d  Fx=%+.5Lf Fy=%+.2Le Fz=%+.2Le  |F|=%.5Lf  s/3=%.5Lf  rel.diff=%.3Le\n",
                        R, s, f.x, f.y, f.z, mag, expect, rel(mag, expect));
            ok = ok && f.x < 0 && rel(mag, expect) <= 0.02L;
        }
        report(ok, "T4", "|F| within 2% of s/3, directed toward centre");
    }

    // â”€â”€ T5: relay fidelity â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    std::printf("\nT5  RELAY FIDELITY  (per-hop loss delta; sum_{d=1}^{N} (1-delta)^d)\n");
    {
        bool ok = true;
        const struct { long N; ld delta; } cases[2] = {{1000, 1e-4L}, {100000, 1e-7L}};
        for (const auto& c : cases) {
            // Both routes use the one stored tau (long double is 64-bit under MSVC, so 1-delta is
            // rounded once and shared); the direct sum is compensated (Kahan) over independent powers.
            const ld tau = 1.0L - c.delta;
            ld direct = 0, comp = 0;
            for (long d = 1; d <= c.N; ++d) {
                const ld y = std::pow(tau, static_cast<ld>(d)) - comp;
                const ld s = direct + y;
                comp = (s - direct) - y;
                direct = s;
            }
            const ld closed = tau * (-std::expm1(static_cast<ld>(c.N) * std::log(tau))) / (1.0L - tau);
            const ld first_order = static_cast<ld>(c.N) * (1.0L - static_cast<ld>(c.N) * c.delta / 2.0L);
            std::printf("    N=%7ld delta=%.1Le  direct=%.9Lf  closed=%.9Lf  N(1-N*delta/2)=%.9Lf  rel(direct,closed)=%.2Le\n",
                        c.N, c.delta, direct, closed, first_order, rel(direct, closed));
            ok = ok && rel(direct, closed) <= 1e-12L;
        }
        report(ok, "T5", "closed form equals direct summation");
    }

    // â”€â”€ T6 and engine values â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    std::printf("\nT6  ENGINE IMPLEMENTATION (Engine/include/sdt/laws.hpp)\n");
    const double N     = law_I::N;
    const double eps   = law_I::epsilon;
    const double Phi   = law_I::Phi;
    const double Pconv = law_I::P_conv;
    const double u     = law_I::u_CMB;
    const double R     = law_I::R_CMB;
    const double grad  = law_IV::convergence_floor::pressure_gradient(R);

    std::printf("    l_P     = %.6e m     (measured::l_P, stored numeric)\n", measured::l_P);
    std::printf("    R_CMB   = %.6e m     (measured::R_CMB)\n", R);
    std::printf("    T_CMB   = %.4f K      a_rad = %.4e J m^-3 K^-4\n", measured::T_CMB, measured::a_rad);
    std::printf("    u_CMB   = %.6e J/m^3\n", u);
    std::printf("    N       = %.6e\n", N);
    std::printf("    eps     = %.6e J\n", eps);
    std::printf("    Phi     = %.6e J\n", Phi);
    std::printf("    P_conv  = %.6e Pa\n", Pconv);
    std::printf("    grad P  = %.6e Pa/m   (convergence_floor::pressure_gradient)\n", grad);
    std::printf("    N*eps = %.6e   N*u_CMB = %.6e   P_conv/(3R) = %.6e\n", N * eps, N * u, Pconv / (3.0 * R));
    report(rel(Phi, N * eps) <= 1e-12L && rel(Pconv, N * u) <= 1e-12L && rel(grad, Pconv / (3.0 * R)) <= 1e-12L,
            "T6", "Phi = N eps ; P_conv = N u_CMB ; grad P = P_conv/(3R)");

    std::printf("\nDERIVED FIGURES FOR THE CHAPTER\n");
    std::printf("    relay fidelity: per-hop loss for a 1%% departure from N*eps: delta <= 0.02/N = %.3e\n", 0.02 / N);
    std::printf("    kernel exponent q (3-D): Phi ~ N^(3-q): q=1 -> N^2 = %.3e ; q=0 -> N^3 = %.3e (in units of N)\n",
                N * N, N * N * N);

    std::printf("\nSUMMARY: %s\n", g_fail == 0 ? "all pre-registered criteria met" : "one or more pre-registered criteria were not met");
    return g_fail == 0 ? 0 : 1;
}
