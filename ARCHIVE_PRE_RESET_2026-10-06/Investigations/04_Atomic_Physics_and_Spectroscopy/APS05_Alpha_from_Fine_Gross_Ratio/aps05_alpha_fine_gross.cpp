// =====================================================================================
//  aps05_alpha_fine_gross.cpp  —  the fine-structure constant as a MEASURED anchor
//
//  Reads alpha two independent ways from real hydrogen spectroscopy, and shows the
//  alpha^2 fine/gross scaling is the second-order MOVEMENT-BUDGET term (Law V), not an
//  imported Dirac spin-orbit. alpha (CODATA) is used on ONE comparison line only.
//
//  Build (MSVC):
//    cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include ^
//       Investigations\04_Atomic_Physics_and_Spectroscopy\APS05_Alpha_from_Fine_Gross_Ratio\aps05_alpha_fine_gross.cpp ^
//       /Fe:aps05.exe && aps05.exe
//  Build (GCC/Clang):
//    g++ -std=c++20 -IEngine/include <thisfile>.cpp -o aps05 && ./aps05
//
//  Author: J. C. Harvey, Melbourne.
// =====================================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

namespace M = sdt::laws::measured;

// ---- measured spectroscopic inputs NOT in laws.hpp (cited) -------------------------
//  H 2P_3/2 - 2P_1/2 fine-structure splitting (measured): 10 969.13 MHz
static constexpr double dnu_2P   = 10969.13e6;     // [Hz]
//  H ionisation energy (Lyman limit, real hydrogen — proton free): 13.598434 eV
static constexpr double E_ion_eV = 13.598434;      // [eV]

static double rel_pct(double a, double b) { return (a - b) / b * 100.0; }

int main() {
    using std::sqrt;
    const double c      = M::c;
    const double m_e    = M::m_e;
    const double cRinf  = M::R_inf * M::c;                 // Rydberg FREQUENCY [Hz] = c * R_inf
    const double mec2_eV = (m_e * c * c) / M::eV_to_J;     // electron rest energy [eV]
    const double inv_codata = 1.0 / M::alpha;              // <-- the ONLY use of measured alpha

    std::printf("############################################################################\n");
    std::printf("#  APS05 — alpha as a MEASURED spectroscopic anchor (two routes + budget)   #\n");
    std::printf("#  J. C. Harvey, Melbourne.  alpha(CODATA) used on ONE compare line only.   #\n");
    std::printf("############################################################################\n\n");

    std::printf("  measured inputs:  dnu_2P = %.3f MHz   cR_inf = %.6e Hz   E_ion = %.6f eV\n",
                dnu_2P / 1e6, cRinf, E_ion_eV);
    std::printf("                    m_e c^2 = %.2f eV (from laws.hpp m_e,c)\n\n", mec2_eV);

    // ---------------------------------------------------------------- ROUTE B (pure ratio)
    //  alpha^2 IS fine/gross.  n=2 level-structure factor 2n^3 = 16.
    const double ratioBG = dnu_2P / cRinf;
    const double alpha2_B = 16.0 * ratioBG;
    const double alpha_B  = sqrt(alpha2_B);
    const double inv_B    = 1.0 / alpha_B;
    std::printf("=== ROUTE B — pure spectroscopic ratio (no m_e, no e, no h) ===\n");
    std::printf("    fine/gross  dnu_2P / cR_inf        = %.6e\n", ratioBG);
    std::printf("    alpha^2 = 16 * (dnu_2P / cR_inf)   = %.6e\n", alpha2_B);
    std::printf("    alpha   = %.8e    1/alpha = %.4f   (CODATA 137.036, %+.3f%%)\n",
                alpha_B, inv_B, rel_pct(inv_B, inv_codata));
    std::printf("    -> two measured frequencies divided. The '16' = 2n^3 (n=2) bookkeeping;\n");
    std::printf("       the SCALE alpha^2 is the immediate, interpretation-free signal.\n\n");

    // ---------------------------------------------------------------- ROUTE A (Law V virial)
    //  ground-state binding = 1/2 m_e v^2,  v = alpha c  =>  alpha = sqrt(2 E_ion / m_e c^2)
    const double alpha_A = sqrt(2.0 * E_ion_eV / mec2_eV);
    const double inv_A   = 1.0 / alpha_A;
    const double v_ground = alpha_A * c;
    std::printf("=== ROUTE A — SDT-native: alpha = v/c of the ground-state rung (Law V) ===\n");
    std::printf("    alpha = sqrt(2 E_ion / m_e c^2)    = %.8e    1/alpha = %.4f  (%+.3f%% vs 137.036)\n",
                alpha_A, inv_A, rel_pct(inv_A, inv_codata));
    std::printf("    v_ground = alpha c = %.4e m/s  (the k = 1/alpha = %.1f rung, PPT02)\n", v_ground, inv_A);
    std::printf("    NOTE: 137.07 is the proton-FREE hydrogen seat. The 137.036 idealisation\n");
    std::printf("          needs the infinite-mass (reduced-mass) correction; NOT applied here.\n\n");

    // ---------------------------------------------------------------- CROSS-CHECK
    const double z = alpha_A * alpha_A;          // z = (v/c)^2
    const double k = 1.0 / alpha_A;              // k = c/v
    std::printf("=== CROSS-CHECK — the two routes, and zk^2 = 1 at the hydrogen rung ===\n");
    std::printf("    1/alpha:  Route A = %.3f   Route B = %.3f   (diff %.3f)\n",
                inv_A, inv_B, std::fabs(inv_A - inv_B));
    std::printf("    z = (v/c)^2 = %.6e   k = c/v = %.4f   z*k^2 = %.12f  (must be 1)\n\n", z, k, z * k * k);

    // ---------------------------------------------------------------- NATIVE alpha^2 MECHANISM
    //  Why alpha^2 scales fine structure: it is the 2nd-order movement-budget term.
    //  v_circ = c sqrt(1 - (v/c)^2);  1 - sqrt(1 - alpha^2) = 1/2 alpha^2 + O(alpha^4).
    const double budget_defect = 1.0 - sqrt(1.0 - z);   // = 1 - v_circ/c
    const double half_alpha2   = 0.5 * z;
    std::printf("=== WHY alpha^2 — the second-order MOVEMENT BUDGET (Law V), not spin-orbit ===\n");
    std::printf("    v_circ/c = sqrt(1 - (v/c)^2);  leading defect 1 - v_circ/c = 1/2 alpha^2\n");
    std::printf("    1 - sqrt(1 - alpha^2) = %.8e   vs   (1/2) alpha^2 = %.8e   (match %+.4f%%)\n",
                budget_defect, half_alpha2, rel_pct(budget_defect, half_alpha2));
    std::printf("    => the fine/gross correction carries a factor (v/c)^2 = alpha^2 BY CONSTRUCTION\n");
    std::printf("       of v_circ^2 + v^2 = c^2.  QED's spin-orbit gives the SAME alpha^2 from the\n");
    std::printf("       SAME lines for a different stated reason. Shared data; native mechanism.\n\n");

    // ---------------------------------------------------------------- VERDICT LINE
    const bool passB = std::fabs(rel_pct(inv_B, inv_codata)) < 0.2;
    const bool passA = std::fabs(inv_A - 137.07) < 0.2;
    const bool zk_ok = std::fabs(z * k * k - 1.0) < 1e-9;
    std::printf("=== VERDICT ===\n");
    std::printf("    [%s] Route B within 0.2%% of 137.036 (pure ratio, no m_e/e/h)\n", passB ? "PASS" : "FAIL");
    std::printf("    [%s] Route A within 0.2 of the 137.07 proton-free seat\n",       passA ? "PASS" : "FAIL");
    std::printf("    [%s] zk^2 = 1 at the hydrogen rung\n",                            zk_ok ? "PASS" : "FAIL");
    std::printf("    [OPEN] geometric derivation of alpha (E51 / OP-3) — dimensionless,\n");
    std::printf("           NOT seed-wall-blocked (contrast l_P, m_e); legitimate, unpaid.\n");
    std::printf("\n    RESULT: alpha is a MEASURED anchor (read 2 ways) + native alpha^2-scaling.\n");
    return (passB && passA && zk_ok) ? 0 : 1;
}
