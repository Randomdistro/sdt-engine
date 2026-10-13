// PPT16 reset, instrument 1 (2026-10-10): muon lifetime from the Law V movement budget.
// Pre-registration: PROMPT.md section "Pre-registration (2026-10-03)" (carried unchanged); record PPT16_RESET_ASSESSMENT_2026-10-10.md.
// Written afresh from the prompt and law_V; the old tool and output were not opened. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
int main() {
    std::printf("PPT16 reset instrument 1 (2026-10-10)\n=====================================\n\n");
    const double c = M::c;
    // [MEASURED-INPUT, local; propose-and-wait for sdt::laws::measured] PDG muon rest energy and rest lifetime; Bailey et al. 1977 magic momentum
    const double mc2 = 105.658, tau0 = 2.1969811, pc = 3094.0, s_pc = 0.5;
    int bad = 0;
    { double r = 1.0 / law_V::time_dilation(0.0); bool ok = r == 1.0; std::printf("[V1] v = 0: ratio %.15f -> %s\n", r, ok ? "met" : "NOT MET"); bad += !ok; }
    { double v = 0.6 * c, vc = law_V::v_circ(v) / c, r = 1 / law_V::time_dilation(v); bool ok = std::fabs(vc - 0.8) < 1e-12 && std::fabs(r - 1.25) < 1e-12; std::printf("[V2] beta 0.6: v_circ/c %.12f, ratio %.12f -> %s\n", vc, r, ok ? "met" : "NOT MET"); bad += !ok; }
    { double v = 0.8 * c, vc = law_V::v_circ(v) / c, r = 1 / law_V::time_dilation(v); bool ok = std::fabs(vc - 0.6) < 1e-12 && std::fabs(r - 5.0 / 3) < 1e-12; std::printf("[V3] beta 0.8: v_circ/c %.12f, ratio %.12f -> %s\n", vc, r, ok ? "met" : "NOT MET"); bad += !ok; }
    { double worst = 0; for (int i = 0; i < 10; ++i) { double b = 0.9999 * i / 9.0, v = b * c, vc = law_V::v_circ(v); worst = std::max(worst, std::fabs((vc * vc + v * v) / (c * c) - 1)); }
      bool ok = worst < 1e-12; std::printf("[V4] budget v_circ^2 + v^2 = c^2 at ten speeds 0-0.9999c: worst %.1e -> %s\n", worst, ok ? "met" : "NOT MET"); bad += !ok; }
    const double beta = pc / std::sqrt(pc * pc + mc2 * mc2), v = beta * c, ratio = 1 / law_V::time_dilation(v), closed = std::sqrt(1 + (pc / mc2) * (pc / mc2));
    { bool ok = std::fabs(ratio / closed - 1) < 1e-12; std::printf("[V5] law_V ratio %.12f against sqrt(1 + (pc/mc^2)^2) = %.12f (rel %.1e) -> %s\n\n", ratio, closed, ratio / closed - 1, ok ? "met" : "NOT MET"); bad += !ok; }
    if (bad) { std::printf("VALIDATIONS NOT MET\n"); return 1; }
    std::printf("VALIDATIONS: met\n\n");
    const double tau = tau0 * ratio, dratio = (pc / (mc2 * mc2)) / closed * s_pc, s_pred = tau0 * dratio;   // d ratio/d pc = (pc/mc2^2)/ratio
    std::printf("beta = %.9f ; budget ratio c/v_circ = %.6f ; tau_pred = %.4f +/- %.4f us (sigma from pc +/- 0.5 MeV)\n\n", beta, ratio, tau, s_pred);
    struct A { const char* n; double t, s; } an[] = {{"mu+ (Bailey 1977)", 64.419, 0.058}, {"mu- (Bailey 1977)", 64.368, 0.029}, {"weighted", 64.378, 0.026}};   // [MEASURED-INPUT, secondary transcription per PROMPT]
    bool met = false;
    for (auto& a : an) { double s = std::sqrt(a.s * a.s + s_pred * s_pred), d = (a.t - tau) / s; if (std::fabs(d) > 2) met = true; std::printf("  %-18s %.3f +/- %.3f us : measured - predicted = %+.4f us (%+.2f sigma)\n", a.n, a.t, a.s, a.t - tau, d); }
    std::printf("\nrejection criterion (any anchor beyond 2 sigma): %s\n", met ? "MET -> budget ratio excluded at this precision" : "not met -> consistent within error");
    std::printf("fractional agreement with weighted anchor: %+.2e (experimental 1-sigma %.1e)\n", 64.378 / tau - 1, 0.026 / 64.378);
    return 0;
}
