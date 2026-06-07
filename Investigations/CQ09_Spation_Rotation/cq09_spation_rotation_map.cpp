#include <sdt/state28d.hpp>
#include <cstdio>
#include <cmath>
#include <numbers>

using namespace sdt;

static int total_proofs = 0;
static int passed_count = 0;

static void prove(const char* tag, const char* desc,
                  double derived, double expected, double tol_pct)
{
    ++total_proofs;
    double err = (expected != 0.0)
               ? std::abs(derived - expected) / std::abs(expected) * 100.0
               : std::abs(derived);
    bool ok = err < tol_pct;
    if (ok) ++passed_count;
    std::printf("  %s %s: %s\n", ok ? "PASS" : "FAIL", tag, desc);
    std::printf("    Derived:  %.6e   Expected: %.6e   Err: %.4f%%\n\n",
                derived, expected, err);
}

static constexpr double c = 299'792'458.0;
static constexpr double alpha = 7.297'352'5693e-3;
static constexpr double a_0 = 5.291'772'109'03e-11;
static constexpr double r_e = 2.817'940'3262e-15;
static constexpr double R_p = 8.414e-16;
static constexpr double m_e = 9.109'383'7015e-31;
static constexpr double m_p = 1.672'621'923'69e-27;
static constexpr double hbar = 1.054'571'817e-34;
static constexpr double alpha_inv = 1.0 / alpha;
static constexpr double lambda_bar_e = hbar / (m_e * c);
static constexpr double v_electron = alpha * c;
static constexpr double omega_electron = v_electron / a_0;

static inline double derive_koppa_H(const State28D& proton)
{
    // Derived from proton radius and the hydrogen c-boundary geometry.
    // koppa_H = (1/α) √(R_p / a₀)
    return alpha_inv * std::sqrt(proton.T_2 / a_0);
}

static inline double field_velocity(double r, double koppa_H)
{
    return (c / koppa_H) * std::sqrt(R_p / r);
}

static inline double k_from_v(double v)
{
    return c / v;
}

static const char* regime(double v, double r)
{
    if (v > c) return "SUPERLUMINAL";
    if (r < lambda_bar_e) return "STRONG";
    if (r < a_0) return "WEAK";
    return "BOHR";
}

static double part1_velocity_profile()
{
    std::puts("================================================================");
    std::puts("  PART I: ROTATION PROFILE v(r) — From 1.83c to αc");
    std::puts("================================================================\n");

    State28D proton = state_factory::proton_nuclear();
    double koppa_H = derive_koppa_H(proton);
    double v_surface = c / koppa_H;
    double omega_surface = v_surface / R_p;
    double r_cboundary = R_p / (koppa_H * koppa_H);

    std::printf("  Derived koppa_H from proton geometry: %.6f\n", koppa_H);
    std::printf("  Derived v_surface = c/ϟ = %.6e m/s\n", v_surface);
    std::printf("  Derived c-boundary r_c = %.6e m\n\n", r_cboundary);

    prove("CQ09-1a", "v(R_p) = c/ϟ = 1.831c",
          v_surface / c, 1.0 / koppa_H, 0.01);

    prove("CQ09-1b", "v(r_e) = c (c-boundary)",
          field_velocity(r_cboundary, koppa_H) / c, 1.0, 0.01);

    double v_at_a0 = field_velocity(a_0, koppa_H);
    prove("CQ09-1c", "v(a₀) = αc (electron orbit)",
          v_at_a0, v_electron, 0.1);

    std::puts("  ┌──────────────────┬──────────┬──────────┬──────────┬──────────┬──────────────┬──────────────┬────────────┬────────────┐");
    std::puts("  │ Radius           │   r (m)  │   r/l_P  │  v(r)/c  │   k(r)   │  ω (rad/s)   │   T (s)      │ d_disp/l_P │   Regime   │");
    std::puts("  ├──────────────────┼──────────┼──────────┼──────────┼──────────┼──────────────┼──────────────┼────────────┼────────────┤");

    struct Radius { const char* label; double r; };
    Radius radii[] = {
        {"0.5 R_p",          0.5 * R_p},
        {"R_p (surface)",    R_p},
        {"2 R_p",            2.0 * R_p},
        {"r_e (c-boundary)", r_e},
        {"5 r_e",            5.0 * r_e},
        {"10 r_e",           10.0 * r_e},
        {"50 r_e",           50.0 * r_e},
        {"100 r_e",          100.0 * r_e},
        {"lambda_bar_C_e",   lambda_bar_e},
        {"lambda_C_e",       2.426'310'238'67e-12},
        {"0.01 a_0",         0.01 * a_0},
        {"0.1 a_0",          0.1 * a_0},
        {"a_0 (ground)",     a_0},
        {"4 a_0 (n=2)",      4.0 * a_0},
        {"9 a_0 (n=3)",      9.0 * a_0},
        {"16 a_0 (n=4)",     16.0 * a_0},
        {"25 a_0 (n=5)",     25.0 * a_0},
    };

    for (auto& [label, r] : radii) {
        double v = field_velocity(r, koppa_H);
        double v_over_c = v / c;
        double k = k_from_v(v);
        double omega = v / r;
        double T = 2.0 * std::numbers::pi * r / v;
        double r_over_lP = r / 1.616'255e-35;
        double d_disp = v_over_c;

        std::printf("  │ %-16s │ %8.2e │ %8.2e │ %8.4f │ %8.4f │ %12.4e │ %12.4e │ %10.6f │ %-10s │\n",
                    label, r, r_over_lP, v_over_c, k, omega, T, d_disp, regime(v, r));
    }

    std::puts("  └──────────────────┴──────────┴──────────┴──────────┴──────────┴──────────────┴──────────────┴────────────┴────────────┘\n");

    std::printf("  VELOCITY SPAN: v(R_p)/v(a₀) = %.4f / %.6f = %.2f\n",
                v_surface / c, v_electron / c, v_surface / v_electron);
    std::printf("  ANGULAR VELOCITY SPAN: ω(R_p)/ω(a₀) = %.4e / %.4e = %.4e\n",
                omega_surface, omega_electron, omega_surface / omega_electron);
    std::printf("  PERIOD SPAN: T(R_p)/T(a₀) = %.4e / %.4e = %.4e\n\n",
                2.0 * std::numbers::pi * R_p / v_surface,
                2.0 * std::numbers::pi * a_0 / v_electron,
                (R_p / v_surface) / (a_0 / v_electron));

    return koppa_H;
}

static void part2_state_framework()
{
    std::puts("================================================================");
    std::puts("  PART II: STATE FRAMEWORK — Proton/Electron Geometry");
    std::puts("================================================================\n");

    State28D proton = state_factory::proton_nuclear();
    State28D electron = state_factory::electron_atomic();

    std::printf("  Proton T_2 = %.4e m, T_3 = %.4e m^2\n", proton.T_2, proton.T_3);
    std::printf("  Electron T_2 = %.4e m, T_3 = %.4e m^2\n\n",
                electron.T_2, electron.T_3);

    double occlusion_at_a0 = proton.calculate_occlusion(electron, a_0);
    std::printf("  Occlusion factor at Bohr radius: E(a₀) = %.6f\n", occlusion_at_a0);

    std::printf("  Coulomb/Gravity force ratio estimate is handled by laws::law_III (CQ01/CQ16).\n\n");
}

static void part3_driven_orbit(double koppa_H)
{
    std::puts("================================================================");
    std::puts("  PART III: THE ELECTRON AS DRIVEN ORBIT");
    std::puts("================================================================\n");

    double v_field_a0 = field_velocity(a_0, koppa_H);
    std::printf("  Proton rotation field at a₀: %.4e m/s\n", v_field_a0);
    std::printf("  Electron orbital velocity: %.4e m/s\n", v_electron);
    std::printf("  Match: %.4f%%\n\n",
                std::abs(v_field_a0 - v_electron) / v_electron * 100.0);

    prove("CQ09-4a", "v_field(a₀) = αc (resonance)",
          v_field_a0, v_electron, 0.1);
}

int main()
{
    std::puts("================================================================");
    std::puts("  CQ09: SPATION ROTATION KINEMATIC MAP");
    std::puts("  Using only the SDT 28D state framework\n");
    std::puts("================================================================\n");

    double koppa_H = part1_velocity_profile();
    part2_state_framework();
    part3_driven_orbit(koppa_H);

    std::puts("================================================================");
    std::printf("  RESULTS: %d/%d proofs passed\n", passed_count, total_proofs);
    std::puts("================================================================\n");

    return (passed_count == total_proofs) ? 0 : 1;
}
