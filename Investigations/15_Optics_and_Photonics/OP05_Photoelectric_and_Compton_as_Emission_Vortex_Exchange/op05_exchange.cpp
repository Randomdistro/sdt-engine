// ============================================================================
// OP05 — Photoelectric and Compton as Emission↔Vortex Exchange
// Author: J. C. Harvey, Melbourne · 2026-07-04
//
// MACHINERY ONLY. The emission enters the ledger as an extended relay train
// with energy rate E = h*f (h = MEASURED tick->energy conversion, whitelist
// input) and momentum rate p = E/c. The electron is a bound vortex of rest
// ledger m_e c^2 (m_e MEASURED). All results below are conservation
// bookkeeping solved NUMERICALLY; closed forms appear only as OBSERVED
// comparison columns.
//
// PRE-DECLARED (RUN_LOG.md): if this is SR kinematics with renamed nouns, it
// is classed CONVERGENCE and said so. The ledger uses the Law-V movement
// budget (v_circ^2 + v^2 = c^2 -> the gamma bookkeeping); that budget
// converges with SR by construction.
// ============================================================================

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <vector>
#include <numbers>

using namespace sdt::laws;
using std::numbers::pi;

static int g_fail = 0;
static void gate(const char* id, bool pass, const char* detail) {
    std::printf("  [%s] %s  %s\n", pass ? "PASS" : "FAIL", id, detail);
    if (!pass) ++g_fail;
}

// Numeric conservation solve: incident emission (energy E, +x), vortex at rest.
// Unknown: scattered emission energy Ep at angle th. The vortex recoil is
// eliminated by momentum components; residual is the energy ledger.
static double compton_solve(double E, double th, double mc2) {
    auto residual = [&](double Ep) {
        const double qx = (E - Ep * std::cos(th));            // vortex momentum * c
        const double qy = (-Ep * std::sin(th));
        const double q2 = qx * qx + qy * qy;
        return E + mc2 - Ep - std::sqrt(mc2 * mc2 + q2);
    };
    double lo = 1e-9 * E, hi = E;                              // bracket
    for (int i = 0; i < 200; ++i) {
        const double mid = 0.5 * (lo + hi);
        (residual(lo) * residual(mid) <= 0.0) ? hi = mid : lo = mid;
    }
    return 0.5 * (lo + hi);
}

int main() {
    std::printf("OP05 — Photoelectric & Compton as emission<->vortex exchange (J. C. Harvey, 2026-07-04)\n");
    std::printf("Machinery only: conservation ledger, numerically solved. h, m_e, W = MEASURED.\n\n");

    const double h = measured::h, c = measured::c, me = measured::m_e;
    const double mc2 = me * c * c;
    const double eV = measured::eV_to_J;

    // ---------------- Phase 1: the emission ledger ----------------
    std::printf("Phase 1 — emission energy/momentum ledger (named hbar entry point)\n");
    const double lam1 = 589e-9, f1 = c / lam1;
    const double E1 = h * f1, p1 = E1 / c;
    std::printf("  589 nm relay train: E = h*f = %.6f eV, p = E/c = %.4e kg m/s, E/(p c) = %.15f\n",
                E1 / eV, p1, E1 / (p1 * c));
    gate("P1-ledger", std::fabs(E1 / (p1 * c) - 1.0) < 1e-12, "self-consistent (IDENTITY by construction — labelled, not claimed)");
    std::printf("  NAMED ENTRY POINT: WHY the lattice exchanges energy in f-proportional units\n"
                "  (E = h f) is NOT derived here or anywhere in the engine — h enters as the\n"
                "  measured tick->energy conversion. This is the hbar debt of the OP suite.\n");

    // ---------------- Phase 2: photoelectric line ----------------
    std::printf("\nPhase 2 — photoelectric line KE_max = h f - W (W = MEASURED-INPUT)\n");
    struct Metal { const char* name; double W_eV, lam_obs_nm; };
    for (Metal m : { Metal{"Na", 2.28, 544.0}, Metal{"Cs", 2.14, 579.0}, Metal{"W ", 4.55, 273.0} }) {
        const double lam_th = h * c / (m.W_eV * eV) * 1e9;
        std::printf("  %s: W = %.2f eV -> threshold %.1f nm (observed-order %.0f nm)\n",
                    m.name, m.W_eV, lam_th, m.lam_obs_nm);
    }
    { // Millikan slope by least squares over 6 tick rates (Na)
        const double W = 2.28 * eV;
        std::vector<double> fs, ks;
        for (int i = 0; i < 6; ++i) { const double f = (6.0 + i) * 1e14; fs.push_back(f); ks.push_back(h * f - W); }
        double n = 6, sx = 0, sy = 0, sxx = 0, sxy = 0;
        for (int i = 0; i < 6; ++i) { sx += fs[i]; sy += ks[i]; sxx += fs[i] * fs[i]; sxy += fs[i] * ks[i]; }
        const double slope = (n * sxy - sx * sy) / (n * sxx - sx * sx);
        const double icept = (sy - slope * sx) / n;
        std::printf("  Millikan fit: slope = %.6e J s (h = %.6e), intercept = %.3f eV (W = 2.28)\n",
                    slope, h, -icept / eV);
        gate("P2-slope", std::fabs(slope - h) / h < 1e-9,
             "slope = h — an IDENTITY under the E=hf anchor (the line is bookkeeping, labelled honestly)");
    }
    std::printf("  F3 prompt-absorption (OBSERVED anchor): attosecond streaking measures relative\n"
                "  emission delays of TENS of attoseconds (e.g. ~21 as, Ne 2p vs 2s) and NO\n"
                "  intensity-dependent build-up at any measured flux (classical accumulation would\n"
                "  need ~seconds at nW). This supports threshold-not-accumulation but NOT the\n"
                "  prompt's literal 'sub-attosecond' claim. F3 row: OPEN — tension reported as-is.\n");

    // ---------------- Phase 3: Compton by numeric ledger ----------------
    std::printf("\nPhase 3 — Compton shift from the conservation ledger (numeric solve)\n");
    const double lamC = h / (me * c);
    std::printf("  lambda_C = h/(m_e c) = %.6e m vs measured::lambda_C_e = %.6e m\n", lamC, measured::lambda_C_e);
    std::printf("  -> agreement is DEFINITIONAL (IDENTITY). An independent Law-VI vortex-geometry\n"
                "     route to lambda_C does not exist in the engine: row OPEN, not claimed.\n");
    double worstC = 0.0;
    for (double E_in : { h * c / 0.0711e-9, 511e3 * eV }) {    // Mo K-alpha (Compton's anchor), 511 keV
        for (double deg : { 30.0, 60.0, 90.0, 120.0, 180.0 }) {
            const double th = deg * pi / 180.0;
            const double Ep = compton_solve(E_in, th, mc2);
            const double dlam = h * c / Ep - h * c / E_in;
            const double target = lamC * (1.0 - std::cos(th));  // OBSERVED comparison column
            const double rel = std::fabs(dlam - target) / target;
            worstC = std::max(worstC, rel);
            if (deg == 90.0)
                std::printf("  E_in = %8.1f keV, th = 90: dLambda = %.6e m vs lambda_C(1-cos) = %.6e m (rel %.1e)\n",
                            E_in / eV / 1e3, dlam, target, rel);
        }
    }
    std::printf("  worst relative deviation over all cases: %.3e  (gate 1e-6)\n", worstC);
    gate("P3-compton", worstC < 1e-6, "ledger reproduces the full angular law; NO point quantum used, but the");
    std::printf("       bookkeeping IS two-body kinematics with renamed nouns -> CONVERGENCE, said plainly.\n");

    // ---------------- Phase 4: limits ----------------
    std::printf("\nPhase 4 — Thomson and moving-vortex limits\n");
    {
        const double lam = 600e-9;
        std::printf("  600 nm backscatter: dLambda/lambda = %.2e -> shift vanishes for soft emissions (Thomson)\n",
                    2.0 * lamC / lam);
        // moving vortex, head-on (inverse case): Law-V budget bookkeeping
        const double beta = 0.6, gamma = 1.0 / std::sqrt(1.0 - beta * beta);
        const double E_lab = 2.0 * eV;                          // soft emission, head-on
        const double E_rest = gamma * (1.0 + beta) * E_lab;     // tick rate seen by the vortex
        const double Ep_rest = compton_solve(E_rest, pi, mc2);  // backscatter in vortex frame
        const double Ep_lab = gamma * (1.0 + beta) * Ep_rest;   // back to lab
        const double gain = Ep_lab / E_lab, ref = gamma * gamma * (1.0 + beta) * (1.0 + beta);
        std::printf("  vortex at 0.6c head-on, 2 eV in: gain = %.4f vs gamma^2(1+beta)^2 = %.4f\n", gain, ref);
        gate("P4-limits", gain > 1.0 && gain / ref > 0.5 && gain / ref < 2.0,
             "energy GAIN, correct sign, within x2 of the head-on factor");
    }

    // ---------------- Honesty block ----------------
    std::printf("\nHONESTY FLAGS:\n"
                "  1. Every number above is conservation bookkeeping + the E = hf anchor. That IS\n"
                "     the standard two-body kinematics with renamed nouns. CLASS: CONVERGENCE.\n"
                "     The renaming is ontological (extended relay train, not point quantum) and is\n"
                "     NOT tested by these numbers.\n"
                "  2. Named debts: (a) E = hf underived (the hbar entry point); (b) lambda_C from\n"
                "     Law-VI vortex geometry ABSENT (identity via measured m_e only); (c) prompt-\n"
                "     absorption timing claim in tension with measured tens-of-attosecond delays.\n"
                "  3. What the ledger DOES earn: the threshold structure (KE_max = hf - W) and the\n"
                "     recoil shift need no point-photon POSTULATE — an extended train carrying\n"
                "     (E, E/c) closes the same books. Duality dissolves only if QM01/OP03 carry\n"
                "     the interference side; see F4 there.\n");

    std::printf("\nOP05 exit: %s (%d gate failures)\n", g_fail == 0 ? "ALL COMMITTED GATES PASS" : "GATE FAILURES", g_fail);
    return g_fail == 0 ? 0 : 1;
}
