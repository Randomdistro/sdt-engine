// PPT16 — muon lifetime as a Law V movement-budget test.
// Pre-registration: PROMPT.md, section "Pre-registration (2026-10-03)".
// Build: cl /std:c++20 /EHsc /O2 /I Engine\include ppt16_muon_budget.cpp
#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>

namespace {
using sdt::laws::law_V::time_dilation;
using sdt::laws::law_V::v_circ;
using sdt::laws::measured::c;

// MEASURED-INPUT, not yet in sdt::laws::measured (addition is propose-and-wait).
constexpr double mc2_MeV = 105.658;          // muon rest energy, PDG
constexpr double tau0_us = 2.1969811;        // muon rest lifetime, PDG
constexpr double sigma_tau0_us = 2.2e-6;
constexpr double pc_MeV = 3094.0;            // storage-ring magic momentum, Bailey 1977
constexpr double sigma_pc_MeV = 0.5;         // last quoted digit, half-unit

struct Anchor { const char* name; double tau_us; double sigma_us; };
constexpr Anchor anchors[] = {
    {"tau+ (mu+)", 64.419, 0.058},
    {"tau- (mu-)", 64.368, 0.029},
    {"weighted  ", 64.378, 0.026},
};

double beta_from_momentum(double pc, double mc2) { return pc / std::sqrt(pc * pc + mc2 * mc2); }

// Law V route: dtau/dt = v_circ(v)/c, lab lifetime = rest lifetime / (dtau/dt).
double tau_lab_us(double pc, double mc2, double tau0) {
    const double v = beta_from_momentum(pc, mc2) * c;
    return tau0 * c / v_circ(v);
}

bool near(double a, double b, double rel) { return std::fabs(a - b) <= rel * std::fabs(b); }

int validate() {
    int fail = 0;
    auto check = [&](const char* what, bool ok) {
        std::printf("  [%s] %s\n", ok ? "ok" : "FAIL", what);
        if (!ok) ++fail;
    };
    std::printf("INSTRUMENT VALIDATION (known answers; anchors not yet opened)\n");
    check("v=0 gives v_circ/c = 1, ratio 1", near(v_circ(0.0) / c, 1.0, 1e-15));
    check("beta=0.6 gives v_circ/c = 0.8, ratio 1.25",
          near(v_circ(0.6 * c) / c, 0.8, 1e-12) && near(c / v_circ(0.6 * c), 1.25, 1e-12));
    check("beta=0.8 gives v_circ/c = 0.6, ratio 5/3",
          near(v_circ(0.8 * c) / c, 0.6, 1e-12) && near(c / v_circ(0.8 * c), 5.0 / 3.0, 1e-12));
    bool budget = true;
    const double betas[] = {1e-6, 0.01, 0.1, 0.3, 0.5, 0.7, 0.9, 0.99, 0.999, 0.9999};
    for (double b : betas) {
        const double v = b * c, vc = v_circ(v);
        budget = budget && near(vc * vc + v * v, c * c, 1e-12);
    }
    check("budget v_circ^2 + v^2 = c^2 to 1e-12 at ten velocities (0 to 0.9999c)", budget);
    const double gamma_closed = std::sqrt(1.0 + (pc_MeV / mc2_MeV) * (pc_MeV / mc2_MeV));
    const double gamma_lawV = 1.0 / time_dilation(beta_from_momentum(pc_MeV, mc2_MeV) * c);
    check("two routes agree: law_V::time_dilation vs closed form sqrt(1+(pc/mc2)^2) to 1e-12",
          near(gamma_lawV, gamma_closed, 1e-12));
    std::printf("  gamma at registered inputs: law_V %.9f, closed form %.9f\n", gamma_lawV, gamma_closed);
    return fail;
}
}  // namespace

int main() {
    std::printf("PPT16 muon lifetime budget test\n");
    std::printf("pre-registration: PROMPT.md (2026-10-03). Labels: COMPUTED; CONVERGENT with SR; not discriminating.\n\n");
    if (validate() != 0) {
        std::printf("\nVALIDATION FAILED: instrument fault, no result reported.\n");
        return 2;
    }
    std::printf("VALIDATION PASS\n\n");

    const double tau_pred = tau_lab_us(pc_MeV, mc2_MeV, tau0_us);
    const double tau_hi = tau_lab_us(pc_MeV + sigma_pc_MeV, mc2_MeV, tau0_us);
    const double tau_lo = tau_lab_us(pc_MeV - sigma_pc_MeV, mc2_MeV, tau0_us);
    const double sigma_p = 0.5 * (tau_hi - tau_lo);
    const double sigma_t0 = tau_pred * sigma_tau0_us / tau0_us;
    const double sigma_pred = std::sqrt(sigma_p * sigma_p + sigma_t0 * sigma_t0);

    std::printf("inputs (MEASURED-INPUT): mc2 = %.3f MeV, tau0 = %.7f us, pc = %.1f +/- %.1f MeV\n",
                mc2_MeV, tau0_us, pc_MeV, sigma_pc_MeV);
    std::printf("COMPUTED: tau_pred = %.4f us, sigma_pred = %.4f us (momentum rounding %.4f, tau0 %.4f)\n\n",
                tau_pred, sigma_pred, sigma_p, sigma_t0);

    bool rejected = false;
    std::printf("%-12s %10s %9s %10s %9s %8s\n", "anchor", "tau_meas", "sigma", "diff(us)", "diff/sig", "gate 2s");
    for (const Anchor& a : anchors) {
        const double sig = std::sqrt(a.sigma_us * a.sigma_us + sigma_pred * sigma_pred);
        const double d = tau_pred - a.tau_us;
        const bool inside = std::fabs(d) <= 2.0 * sig;
        if (!inside) rejected = true;
        std::printf("%-12s %10.3f %9.3f %+10.4f %+9.2f %8s\n", a.name, a.tau_us, sig, d, d / sig,
                    inside ? "inside" : "OUTSIDE");
    }
    std::printf("\nrejection criterion (any anchor beyond 2 sigma): %s\n", rejected ? "MET" : "not met");

    const double tau_g2933 = tau0_us * 29.33;
    std::printf("\nreport-only sensitivity: Bailey quoted gamma = 29.33 gives tau = %.4f us "
                "(registered route uses gamma from pc, mc2: %.4f)\n",
                tau_g2933, tau_pred);
    std::printf("altitude-survival flux pairs: PENDING_DATA (not scored)\n");
    return 0;
}
