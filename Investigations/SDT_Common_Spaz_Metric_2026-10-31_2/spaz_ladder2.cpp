// ============================================================================
//  spaz_ladder2.cpp — Common Spaz Metric run 2, workstream W10
//  Author: James Christopher Tyndall, Melbourne.
//
//  The Spaz ladder (candidate D): today's ratios traced from N = 1 back through
//  release to the halt of light. Every landmark is a locked local quantity
//  meeting the bath; every far-frame value follows from N alone:
//    z_S = 1 - 1/N,  c_far = c/N^2,  hop = l_P/N,  tick = N t_P,
//    P = N^4 P_rad,  Wien peak (local rulers) = lambda_now / N.
//
//  Build: g++ -std=c++20 -O2 -IEngine/include spaz_ladder2.cpp
//  Run:   ./a.out <output dir>
// ============================================================================

#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <fstream>
#include <numbers>
#include <string>
#include <vector>

namespace {

namespace M = sdt::laws::measured;
namespace L1 = sdt::laws::law_I;
constexpr double PI = std::numbers::pi;
constexpr double x_W = 4.965114231744276;          // Wien x: x = 5(1 - e^-x)
const double b_W = 2 * PI * M::hbar * M::c / (x_W * M::k_B);   // Wien b [m K]
const double lam_now = b_W / M::T_CMB;
const double kT0 = M::k_B * M::T_CMB;
const double eV = M::eV_to_J;

constexpr double eta = 6.1e-10, Y = 0.245;         // shared-input (stated)

double n_gamma(double T) {
    const double kT = M::k_B * T;
    return 2 * 1.2020569031595942 / (PI * PI) * std::pow(kT / (M::hbar * M::c), 3);
}
double saha_rhs(double T, double E_eV, double g) {
    const double kT = M::k_B * T;
    return g * std::pow(M::m_e * kT / (2 * PI * M::hbar * M::hbar), 1.5)
           * std::exp(-E_eV * eV / kT);
}
// N at which n_upper/n_lower = 1 for a stage, with n_e supplied by f_e * n_H
double half_point(double E_eV, double g, double f_e) {
    double lo = 1, hi = 1e7;
    for (int i = 0; i < 300; ++i) {
        const double N = std::sqrt(lo * hi), T = M::T_CMB * N;
        const double nH = (1 - Y) * eta * n_gamma(T);
        const double r = saha_rhs(T, E_eV, g) / (f_e * nH);
        (r < 1 ? lo : hi) = N;
    }
    return std::sqrt(lo * hi);
}
double h_half() {   // hydrogen x_e = 0.5 (n_e = n_p), as W6
    double lo = 1, hi = 1e5;
    for (int i = 0; i < 300; ++i) {
        const double N = std::sqrt(lo * hi), T = M::T_CMB * N;
        const double S = saha_rhs(T, M::Ry_eV, 1.0) / (eta * n_gamma(T));
        const double x = (-S + std::sqrt(S * S + 4 * S)) / 2;
        (x < 0.5 ? lo : hi) = N;
    }
    return std::sqrt(lo * hi);
}

struct Mark { std::string name, defn, label; double N; };

} // namespace

int main(int argc, char** argv) {
    const std::string out = argc > 1 ? argv[1] : ".";
    std::printf("spaz_ladder2 — W10 Spaz ladder to the halt of light (candidate D)\n");
    std::printf("  lambda_now (Wien) = %.6e m; P_rad now = %.4e Pa; P_eff = %.4e Pa\n",
        lam_now, L1::P_rad, sdt::laws::law_III::P_eff);

    const double fHe = Y / (4 * (1 - Y));
    const double mec2 = M::m_e * M::c * M::c, mpc2 = M::m_p * M::c * M::c;
    const double Bd = M::B_deuteron * M::MeV_to_J, Ba = M::B_alpha * M::MeV_to_J;
    const double T_P = M::hbar * M::c / (M::k_B * M::l_P);

    std::vector<Mark> m = {
        {"now", "today", "OBSERVED", 1.0},
        {"c_far = today's orbital speed of Earth", "c/N^2 = 29.78 km/s (far frame only)", "COMPUTED", std::sqrt(M::c / 29780.0)},
        {"H release, rate law q=2 (W6b)", "tau_T = 1", "COMPUTED (post-inspection)", 734.1},
        {"H release, rate law q=0 (W6b)", "tau_T = 1", "COMPUTED (post-inspection)", 1064.2},
        {"FIRAS release", "z_release + 1", "OBSERVED", 1090.0},
        {"H Saha half-point", "x_e = 0.5", "COMPUTED", h_half()},
        {"visible red edge", "Wien peak = 700 nm", "COMPUTED", lam_now / 700e-9},
        {"He I -> He II Saha half", "n(He+)/n(He) = 1", "COMPUTED", half_point(24.587387, 4.0, 1.0)},
        {"visible violet edge", "Wien peak = 380 nm", "COMPUTED", lam_now / 380e-9},
        {"He II -> He III Saha half", "n(He++)/n(He+) = 1", "COMPUTED", half_point(54.417760, 1.0, 1.0 + fHe)},
        {"Lyman-alpha Wien peak", "Wien peak = 121.567 nm", "COMPUTED", lam_now / 121.567e-9},
        {"kT = E1", "kT = 13.6057 eV", "COMPUTED", M::Ry_eV * eV / kT0},
        {"solar-centre temperature", "T = 1.57e7 K (solar model, comparator)", "COMPUTED", 1.57e7 / M::T_CMB},
        {"Wien photon = 2 m_e c^2", "pair threshold", "COMPUTED", 2 * mec2 / (x_W * kT0)},
        {"kT = m_e c^2", "electron rest energy", "COMPUTED", mec2 / kT0},
        {"kT = B_d", "deuteron binding 2.2246 MeV", "COMPUTED", Bd / kT0},
        {"kT = B_alpha", "alpha binding 28.296 MeV", "COMPUTED", Ba / kT0},
        {"P = P_eff", "N^4 P_rad = P_eff", "COMPUTED", std::pow(sdt::laws::law_III::P_eff / L1::P_rad, 0.25)},
        {"Wien peak = r_e", "lambda = r_e", "COMPUTED", lam_now / M::r_e},
        {"Wien peak = R_p", "lambda = R_p", "COMPUTED", lam_now / M::R_p},
        {"kT = m_p c^2", "proton rest energy", "COMPUTED", mpc2 / kT0},
        {"P = P_conv (post-registration)", "N^4 P_rad = law_I::P_conv", "COMPUTED", std::pow(L1::P_conv / L1::P_rad, 0.25)},
        {"Planck temperature", "T = hbar c / (k l_P)", "COMPUTED", T_P / M::T_CMB},
        {"halt of light", "Wien peak = l_P (one hop)", "COMPUTED", lam_now / M::l_P},
    };

    // validation against the repository table (SDT_THEORETICAL_MODEL.md section 6)
    auto vrow = [](const char* n, double got, double want, double tol = 0.01) {
        std::printf("  validation %-28s %.4e vs %.4e  rel %.2e %s\n", n, got, want,
            std::abs(got / want - 1), std::abs(got / want - 1) < tol ? "PASS" : "FAIL");
    };
    vrow("c_far at N=1090 [m/s]", M::c / (1090.0 * 1090.0), 252.0);
    vrow("N at P = P_eff", m[17].N, 2.48e11);
    vrow("N at lambda = l_P", m[23].N, 6.58e31);
    vrow("He II half-point 1+z (~6000)", m[9].N, 6000.0, 0.2);
    vrow("He I half-point 1+z (~2500)", m[7].N, 2500.0, 0.2);
    std::printf("  (He validations carry a pre-registered 20 %% tolerance)\n\n");

    std::printf("  %-38s %11s %13s %11s %11s %11s %11s %11s\n", "landmark", "N", "1 - z_S",
        "T_local K", "c_far m/s", "hop/l_P", "P/P_now", "lambda_loc");
    std::ofstream f(out + "/spaz_ladder2.csv");
    f << "landmark,definition,label,N,one_minus_zS,T_local_K,c_far_ms,hop_over_lP,tick_over_tP,P_over_Pnow,P_Pa,lambda_local_m,kT_eV,t_q0_H0inv,t_q2_H0inv\n";
    for (const auto& k : m) {
        const double N = k.N;
        const double t0 = (std::pow(N, 0.28) - 1) / 0.28;      // p = 0.720
        const double t2 = (std::pow(N, 2.28) - 1) / 2.28;      // p = -1.280
        std::printf("  %-38s %11.4e %13.4e %11.4e %11.4e %11.4e %11.4e %11.4e\n",
            k.name.c_str(), N, 1 / N, M::T_CMB * N, M::c / (N * N), 1 / N,
            std::pow(N, 4), lam_now / N);
        f << '"' << k.name << "\",\"" << k.defn << "\"," << k.label << ',' << N << ','
          << 1 / N << ',' << M::T_CMB * N << ',' << M::c / (N * N) << ',' << 1 / N << ','
          << N << ',' << std::pow(N, 4) << ',' << std::pow(N, 4) * L1::P_rad << ','
          << lam_now / N << ',' << kT0 * N / eV << ',' << t0 << ',' << t2 << '\n';
    }

    std::printf("\n  halt identities:\n");
    std::printf("    T_halt / T_Planck = %.6f   (2 pi / x_W = %.6f)\n",
        m[23].N / m[22].N, 2 * PI / x_W);
    std::printf("    far-frame hop at halt = l_P^2 / lambda_now = %.4e m\n",
        M::l_P / m[23].N);
    std::printf("    c_far at halt = %.4e m/s; P at halt = %.4e Pa = %.3e P_eff\n",
        M::c / (m[23].N * m[23].N), std::pow(m[23].N, 4) * L1::P_rad,
        std::pow(m[23].N, 4) * L1::P_rad / sdt::laws::law_III::P_eff);
    std::printf("    P_eff landmark: Wien peak there = %.4e m (R_p = %.4e, r_e = %.4e)\n",
        lam_now / m[17].N, M::R_p, M::r_e);

    std::printf("\n  locked at every N (candidate D, local units): alpha = 1/%.6f, "
        "m_p/m_e = %.6f, R_p/lbar_p = %.5f, E1/(m_e c^2) = %.6e, a0/hop fixed\n",
        M::alpha_inv, M::m_p / M::m_e, M::R_p * M::m_p * M::c / M::hbar,
        M::Ry_eV * eV / mec2);
    std::printf("  elapsed time (non-identifiable): t(N->1) = (N^(1-p) - 1)/(1-p) / H0, "
        "p = 0.720 (q=0) or -1.280 (q=2); see CSV\n");
    for (int i : {4, 17, 21, 23})
        std::printf("    %-20s q=0: %.3e / H0   q=2: %.3e / H0\n", m[i].name.c_str(),
            (std::pow(m[i].N, 0.28) - 1) / 0.28, (std::pow(m[i].N, 2.28) - 1) / 2.28);
    return 0;
}
