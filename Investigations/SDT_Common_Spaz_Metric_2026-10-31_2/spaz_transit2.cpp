// ============================================================================
//  spaz_transit2.cpp — Common Spaz Metric run 2, workstream W11
//  Author: James Christopher Tyndall, Melbourne.
//
//  Transit-rule permutations: cosmic tick exponent a, hop exponent b
//  (c_far ~ N^-(a+b)), halt at P = P_eff or at Wien peak = l_P.
//  Gates G4 (release epoch) and G5 (onset spacing vs the stated 1e-70 m) are
//  the discriminating ones; G1-G3 hold for every member by construction.
//
//  Build: g++ -std=c++20 -O2 -IEngine/include spaz_transit2.cpp
//  Run:   ./a.out <output dir>
// ============================================================================

#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <fstream>
#include <numbers>
#include <string>

namespace {

namespace M = sdt::laws::measured;
constexpr double PI = std::numbers::pi;
constexpr double eta = 6.1e-10;
constexpr double sigma_T = 6.6524587321e-29;          // [m^2] Thomson (CODATA)
constexpr double Mpc = 3.0856775814913673e22;
constexpr double x_W = 4.965114231744276;

double saha_x(double T) {
    const double kT = M::k_B * T;
    const double ng = 2 * 1.2020569031595942 / (PI * PI) * std::pow(kT / (M::hbar * M::c), 3);
    const double S = std::pow(M::m_e * kT / (2 * PI * M::hbar * M::hbar), 1.5)
        * std::exp(-M::Ry_eV * M::eV_to_J / kT) / (eta * ng);
    return (-S + std::sqrt(S * S + 4 * S)) / 2;
}
double n_b(double T) {
    const double kT = M::k_B * T;
    return eta * 2 * 1.2020569031595942 / (PI * PI) * std::pow(kT / (M::hbar * M::c), 3);
}

/// T_local at which tau_Thomson reaches 1, integrating in u = ln N.
double release_T(double a, double p, double H0, double du) {
    const double H = H0 / a;
    double tau = 0;
    for (double u = 0; u < 20; u += du) {
        const double N = std::exp(u + du / 2), T = M::T_CMB * std::pow(N, a);
        tau += saha_x(T) * n_b(T) * sigma_T * M::c * N * du / (H * std::pow(N, p + a));
        if (tau >= 1) return T;
    }
    return NAN;
}

} // namespace

int main(int argc, char** argv) {
    const std::string out = argc > 1 ? argv[1] : ".";
    const double H0 = 70e3 / Mpc;
    const double T_Peff = M::T_CMB * std::pow(sdt::laws::law_III::P_eff / sdt::laws::law_I::P_rad, 0.25);
    const double T_lP = 2 * PI / x_W * M::hbar * M::c / (M::k_B * M::l_P);
    std::printf("spaz_transit2 — W11 transit permutations (H0 = 70, eta = 6.1e-10)\n");
    std::printf("  halt temperatures: P = P_eff %.4e K; Wien peak = l_P %.4e K\n", T_Peff, T_lP);

    // validation
    for (auto [b, want] : {std::pair{1.0, 734.1}, std::pair{-1.0, 1064.2}}) {
        const double p = (1 - 0.28) - (1 + b);
        const double T1 = release_T(1, p, H0, 1e-3), T2 = release_T(1, p, H0, 1e-4);
        std::printf("  validation (1,%+.0f): release N %.1f (W6b %.1f)  step agreement %.2e %s\n",
            b, T2 / M::T_CMB, want, std::abs(T1 / T2 - 1),
            std::abs(T2 / M::T_CMB / want - 1) < 1e-3 && std::abs(T1 / T2 - 1) < 1e-3 ? "PASS" : "FAIL");
    }

    std::ofstream f(out + "/transit_permutations2.csv");
    f << "a,b,q,p,halt,T_release_K,G4,N_halt,hop_halt_m,G5,t_halt_H0inv\n";
    std::printf("\n  %3s %3s %3s %7s %-7s %11s %4s %11s %11s %4s %12s\n", "a", "b", "q", "p",
        "halt", "T_rel K", "G4", "N_halt", "hop_halt m", "G5", "t / (1/H0)");
    for (double a : {1.0, 2.0}) {
        for (double b : {-1.0, 0.0, 1.0, 2.0, 3.0}) {
            const double q = a + b, p = (1 - 0.28 * a) - q;
            const double T1 = release_T(a, p, H0, 1e-3), Tr = release_T(a, p, H0, 1e-4);
            const bool g4 = std::abs(Tr / 2971.0 - 1) < 0.05 || std::abs(Tr / 2892.0 - 1) < 0.05;
            for (int h = 0; h < 2; ++h) {
                const double Th = h == 0 ? T_Peff : T_lP;
                const double Nh = std::pow(Th / M::T_CMB, 1 / a);
                const double hop = M::l_P * std::pow(Nh, -b);
                const bool g5 = std::abs(std::log10(hop / 1e-70)) <= 1.0;
                const double t = a * (std::abs(1 - p) < 1e-12 ? std::log(Nh)
                                    : (std::pow(Nh, 1 - p) - 1) / (1 - p));
                std::printf("  %3.0f %3.0f %3.0f %7.3f %-7s %11.1f %4s %11.3e %11.3e %4s %12.3e%s\n",
                    a, b, q, p, h == 0 ? "P_eff" : "l_P", Tr, g4 ? "PASS" : "fail", Nh, hop,
                    g5 ? "PASS" : "fail", t, std::abs(T1 / Tr - 1) > 1e-3 ? "  (step!)" : "");
                f << a << ',' << b << ',' << q << ',' << p << ',' << (h == 0 ? "P_eff" : "l_P") << ','
                  << Tr << ',' << g4 << ',' << Nh << ',' << hop << ',' << g5 << ',' << t << '\n';
            }
        }
    }
    // exponent b needed for exactly 1e-70 m at each halt, per a
    for (double a : {1.0, 2.0})
        for (int h = 0; h < 2; ++h) {
            const double Nh = std::pow((h == 0 ? T_Peff : T_lP) / M::T_CMB, 1 / a);
            std::printf("  b for hop = 1e-70 m: a=%.0f halt %-5s -> b = %.4f\n", a,
                h == 0 ? "P_eff" : "l_P", std::log(M::l_P / 1e-70) / std::log(Nh));
        }
    // release depends on b/a only (substitute Z = N^a); continuous scan for the G4 window
    std::ofstream g(out + "/transit_release_scan2.csv");
    g << "b_over_a,T_release_K\n";
    double lo = NAN, hi = NAN;
    for (double r = -2.0; r <= 3.0001; r += 0.01) {
        const double T = release_T(1, 0.72 - (1 + r), H0, 1e-4);
        g << r << ',' << T << '\n';
        const bool ok = std::abs(T / 2971.0 - 1) < 0.05 || std::abs(T / 2892.0 - 1) < 0.05;
        if (ok && std::isnan(lo)) lo = r;
        if (ok) hi = r;
    }
    std::printf("  G4 window (continuous): b/a in [%.2f, %.2f]; hop then GROWS with depth "
        "(b < 0) -> far-frame transit speed c_far ~ N^-(a+b)\n", lo, hi);
    return 0;
}
