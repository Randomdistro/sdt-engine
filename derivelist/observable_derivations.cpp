// Observable-ratio derivations of the listed scales. Pre-registered in OBSERVABLE_DERIVATION_PREREG.md.
// Build: g++ -std=c++20 -O2 -I../Engine/include observable_derivations.cpp -o observable_derivations
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
using namespace sdt::laws;
namespace obs {  // raw observed inputs not exposed by the engine (provenance: PREREG)
    constexpr double dnu_fs   = 10'969.04e6;        // Hz  2P3/2-2P1/2, u = 0.15e6
    constexpr double nu_1S2S  = 2'466'061'413'187'035.0;  // Hz
    constexpr double G        = 6.674'30e-11;       // m^3 kg^-1 s^-2  u_rel 2.2e-5
    constexpr double KJ90     = 483'597.9e9;        // Hz/V
    constexpr double RK90     = 25'812.807;         // ohm
    constexpr double c_1972   = 299'792'456.2, u_c_1972 = 1.1;
}
static int earned = 0, total = 0, controls_missed = 0;
static void gate(const char* id, const char* what, double got, double ref, double tol, const char* tag) {
    double rel = (got - ref) / ref; bool ok = std::fabs(rel) <= tol;
    std::printf("%-3s %-44s got=%.6e ref=%.6e rel=%+.3e tol=%.1e %s [%s]\n", id, what, got, ref, rel, tol, ok ? "within" : "outside", tag);
    ++total; if (ok) ++earned;
}
static void control(const char* id, const char* what, double got, double ref, double tol) {
    double rel = (got - ref) / ref; bool missed = std::fabs(rel) > tol;
    std::printf("%-3s %-44s rel=%+.3e tol=%.1e control %s\n", id, what, rel, tol, missed ? "MISSES gate (as required)" : "DOES NOT MISS (technique not falsifiable)");
    if (missed) ++controls_missed;
}
int main() {
    const double Rinf_Hz = measured::R_inf * measured::c;
    // A1: pure ratio of two measured frequencies. No m_e, e, h.
    double aB  = std::sqrt(16.0 * obs::dnu_fs / Rinf_Hz);
    gate("A1", "1/alpha from 16*dnu_fs/(c R_inf)", 1.0 / aB, measured::alpha_inv, 2e-3, "OBSERVED ratio");
    // A2: raw hydrogen line, reduced-mass Rydberg R_H = (4/3) nu(1S-2S)
    double RH  = (4.0 / 3.0) * obs::nu_1S2S;
    double aH  = std::sqrt(16.0 * obs::dnu_fs / RH);
    gate("A2", "1/alpha from 16*dnu_fs/R_H(1S-2S)", 1.0 / aH, measured::alpha_inv, 2e-3, "OBSERVED ratio");
    control("A3", "1/alpha with degeneracy 8 (wrong)", 1.0 / std::sqrt(8.0 * obs::dnu_fs / Rinf_Hz), measured::alpha_inv, 2e-3);
    std::printf("    k_H = 1/alpha: route A1 %.4f, route A2 %.4f, CODATA %.4f; residual = measured excess over closed form, not corrected\n",
                1.0 / aB, 1.0 / aH, measured::alpha_inv);
    // L1: l_P from the observed baryon koppa and the observed proton boundary
    double u_rel = std::sqrt(std::pow(1.9e-18 / measured::R_p, 2) + std::pow(2.2e-5, 2)) / 2.0;
    double vb = obs::G * measured::m_p / (measured::c * measured::c);
    for (int W1 : {4, 3, 5}) {
        double lP = std::sqrt(vb * (measured::R_p / W1));
        if (W1 == 4) gate("L1", "l_P = sqrt(G m_p/c^2 * R_p/4)", lP, measured::l_P, 3.0 * u_rel, "OBSERVED inputs");
        else control(W1 == 3 ? "L2a" : "L2b", W1 == 3 ? "l_P with W+1=3 (wrong)" : "l_P with W+1=5 (wrong)", lP, measured::l_P, 3.0 * u_rel);
    }
    std::printf("    koppa_b(obs)=%.6e m  wake=R_p/4=%.6e m  sigma_rel(l_P)=%.2e\n", vb, measured::R_p / 4, u_rel);
    // H1: action as ground-state m*v*R with v = alpha c, R = a0 = alpha/(4 pi R_inf)
    double a0B = aB / (4.0 * std::numbers::pi * measured::R_inf);
    gate("H1", "hbar = m_e (alpha_B c) a0_B", measured::m_e * aB * measured::c * a0B, measured::hbar, 5e-3, "OBSERVED seat");
    // E1: Josephson x von Klitzing
    gate("E1", "e = 2/(K_J R_K)", 2.0 / (obs::KJ90 * obs::RK90), measured::e_charge, 1e-6, "OBSERVED ratio");
    // C1: Evenson 1972 (IDENTITY-CLASS since 1983)
    double sig = std::fabs(measured::c - obs::c_1972) / obs::u_c_1972;
    std::printf("C1  c: Evenson 1972 %.1f +- %.1f vs SI %.0f -> %.2f sigma %s [IDENTITY-CLASS, outside tally]\n",
                obs::c_1972, obs::u_c_1972, measured::c, sig, sig <= 3 ? "within 3 sigma" : "outside");
    std::printf("K1  k_B: PENDING raw blackbody peak/thermometer pair\nT1  T_CMB: OBSERVED boundary state (FIRAS), not derived\n");
    std::printf("\nEarned gates within tolerance: %d/%d ; controls that miss as required: %d/3\n", earned, total, controls_missed);
}
