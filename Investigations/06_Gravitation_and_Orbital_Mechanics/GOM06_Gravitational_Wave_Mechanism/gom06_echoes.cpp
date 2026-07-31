// ════════════════════════════════════════════════════════════════════════
//  CQ-44 · STRONG-FIELD FRONTIER — ringdown & echoes (where SDT ≠ GR)
//
//  "they meld into one, and the pulse, she stop"  — the ringdown.
//
//  Two predictions for the merged remnant:
//
//  (A) RINGDOWN (convergence) — the remnant is a max-compression vortex (E68).
//      Its damped shear mode rings at  f_QNM = f̂ · c / (2π ϟ_f),  a LENGTH
//      result (ϟ_f = final koppa). f̂ ≈ 0.53 is the ⟦Kerr-fit⟧ O(1) factor
//      (CONVERGENCE, like G2's 96/5 — native shear-mode derivation OPEN).
//
//  ⚠ GOM22 DEPENDENCY (2026-07-30): the echo prediction below rests on WHERE
//    the relay speed vanishes, and that is now an OPEN second-order fork. The
//    repaired canon adopts c_far = c(1−z)², which still vanishes at r = ϟ and
//    so PRESERVES this prediction. The rival first-order-identical form
//    c(1−2z) vanishes at r = 2ϟ = r_s exactly — a horizon — and would kill it.
//    Nothing here is evidence for either form; the discriminator is strong-field
//    (a 1.4 M☉ NS surface splits them by 8.6%). Read this section as
//    CONDITIONAL on form (a). Record: GOM22_Shapiro_Velocity_Profile/.
//
//  (B) ECHOES (DISTINCTIVE — SDT ≠ GR) — GR has a perfectly-absorbing horizon;
//      SDT has NO horizon. The relay speed c_far = c(1−z)² → 0 only at z=1
//      (r = ϟ), and CQ-42's closure floor (z=1 self-boundary) is a HARD WALL:
//      the spation cannot compress below ℓ_P. So the ringdown partially
//      REFLECTS off that wall and re-emerges as delayed echoes, spaced by the
//      cavity light-travel time in the depth-slowed relay:
//
//        Δt_echo = (2/c) ∫_{r_wall}^{r_peak} dr/(1−ϟ/r)
//                = (2ϟ_f/c) · [ (r_peak−r_wall)/ϟ + ln( (r_peak−ϟ)/δ_wall ) ]
//
//      with the wall one closure-cell from the edge: δ_wall ~ ℓ_P (CQ-42).
//      The ln(ϟ_f/ℓ_P) factor is the cavity depth in closure units.
//
//  Build (MSVC):  cl /std:c++20 /EHsc /O2 /I Engine\include /Fe:cq44e.exe ^
//                    Investigations\CQ44_Gravitational_Wave_Mechanism\cq44_echoes.cpp
//  Author: James Christopher Tyndall, Melbourne.
// ════════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <numbers>

using sdt::laws::measured::c;
using sdt::laws::measured::l_P;
constexpr double PI = std::numbers::pi;

constexpr double GM_sun    = 1.327'124'400'18e20;   // [m³/s²] IAU 2015
constexpr double koppa_sun = GM_sun / (c * c);       // [m] ≈ 1.4766 km

// ⟦LIGO⟧ GW150914 remnant (R1 cross-check)
constexpr double M_f   = 62.0;    // [M_sun] final mass
constexpr double a_f   = 0.68;    // [-]     final dimensionless spin
constexpr double f_rd_obs = 250.0;// [Hz]    observed ringdown frequency

// Kerr fundamental l=m=2 QNM fits (⟦convergence input⟧, GR perturbation theory)
double f_hat(double a)  { return 1.5251 - 1.1568 * std::pow(1.0 - a, 0.1292); }
double Q_fac(double a)  { return 0.7000 + 1.4187 * std::pow(1.0 - a, -0.4990); }

int main() {
    std::printf("===========================================================\n");
    std::printf(" CQ-44 · STRONG-FIELD — ringdown 'she stop' & echoes (SDT≠GR)\n");
    std::printf("===========================================================\n\n");

    const double koppa_f = M_f * koppa_sun;            // [m] final koppa
    std::printf("Remnant (⟦GW150914⟧): M_f=%.0f M_sun, a_f=%.2f → ϟ_f = %.1f km\n\n",
                M_f, a_f, koppa_f / 1e3);

    // (A) Ringdown — the pulse 'she stop'
    const double fhat = f_hat(a_f);
    const double f_qnm = fhat * c / (2.0 * PI * koppa_f);
    const double Q = Q_fac(a_f);
    const double tau = Q / (PI * f_qnm);
    std::printf("--- (A) RINGDOWN (convergence) ----------------------------\n");
    std::printf("f_QNM = f̂·c/(2π·ϟ_f),  f̂=%.3f (⟦Kerr-fit⟧)  = %.1f Hz   vs obs %.0f Hz (%.0f%%)\n",
                fhat, f_qnm, f_rd_obs, 100.0*(f_qnm-f_rd_obs)/f_rd_obs);
    std::printf("Q = %.2f → damping time τ = Q/(πf) = %.2f ms  ('she stop' in ~%.0f cycles)\n\n",
                Q, tau * 1e3, Q);

    // (B) Echoes — the SDT-distinctive 'she go forever' (in the ringdown)
    std::printf("--- (B) ECHOES (DISTINCTIVE: SDT has NO horizon) ----------\n");
    const double r_peak = 3.0 * koppa_f;      // light-ring ~ 1.5 r_s = 3 ϟ
    const double r_wall = koppa_f + l_P;      // wall one closure-cell from z=1 (r=ϟ)
    const double dr = r_peak - r_wall;
    const double logterm = std::log((r_peak - koppa_f) / l_P);   // ln(2ϟ_f/ℓ_P)
    const double dt_echo = (2.0 / c) * (dr + koppa_f * logterm);
    std::printf("wall at r = ϟ_f + ℓ_P (CQ-42 closure floor); light-ring r_peak = 3ϟ_f\n");
    std::printf("cavity depth  ln(2ϟ_f/ℓ_P) = %.1f   (the closure-unit depth)\n", logterm);
    std::printf("Δt_echo = (2ϟ_f/c)·[2 + ln(2ϟ_f/ℓ_P)] = %.1f ms\n", dt_echo * 1e3);
    std::printf("   → SDT predicts a train of echoes spaced ~%.0f ms after the main ringdown.\n\n",
                dt_echo * 1e3);

    std::printf("--- HONESTY (R4/R5) ---------------------------------------\n");
    std::printf("• f̂ and Q are ⟦Kerr-fit⟧ CONVERGENCE inputs (GR pert. theory); the native\n");
    std::printf("  shear-mode-of-a-max-compression-vortex derivation is OPEN.\n");
    std::printf("• Echo delay is logarithmic in the wall offset δ_wall: setting δ_wall=ℓ_P\n");
    std::printf("  (CQ-42 floor) gives ~%.0f ms; the ln makes it sensitive to wall placement\n",
                dt_echo*1e3);
    std::printf("  (range ~tens–hundreds of ms). This is a POSIT (reflecting wall), not derived.\n");
    std::printf("• OBSERVATIONAL STATUS: echo claims (Abedi+ 2017, ~0.3 s) are CONTESTED —\n");
    std::printf("  independent reanalyses (Westerweck+, Nielsen+) find low/no significance.\n");
    std::printf("  SDT-distinctive, falsifiable, NOT confirmed. This is the SDT≠GR test.\n");
    std::printf("===========================================================\n");
    return 0;
}
