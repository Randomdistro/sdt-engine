/**
 * @file cq09c_bond_energy.cpp
 * @brief CQ09c: Bond Energy from Mutual Traction — 40-Bond Survey
 *
 * Tests whether the discrepancy between the SDT rotation-field bond
 * energy estimate and measured bond energies is:
 *   (a) SCALED — constant ratio (missing universal factor)
 *   (b) METRICISED — ratio is a function of some bond property
 *   (c) INDEPENDENT — no pattern (model is wrong)
 *
 * For each bond A–B at measured distance d:
 *   v_A(d/2) = cα√(a₀/(d/2))   — atom A's unified field at midpoint
 *   v_B(d/2) = same (symmetric)  — atom B's field at midpoint
 *   ΔE_naive = m_e × v² (single-field KE surplus)
 *   ΔE_mutual = including both bodies' traction + electron's own W=1 wake
 *
 * Then: ratio = ΔE_predicted / D_e(measured) for each bond.
 * If ratio ≈ const → scaled. If ratio = f(Z, d, n) → metricised.
 *
 * @author SDT Canonical Engine — James Tyndall, Melbourne
 * @date May 2026
 */

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <numbers>
#include <algorithm>

using namespace sdt::laws;
using namespace sdt::laws::measured;

// ═══════════════════════════════════════════════════════════════
//  BOND DATABASE — measured bond lengths & dissociation energies
//  Sources: CRC Handbook, NIST CCCBDB
// ═══════════════════════════════════════════════════════════════

struct Bond {
    const char* name;
    int Z1, Z2;          // atomic numbers
    double d_m;           // bond length [m]
    double De_eV;         // dissociation energy D_e [eV]
    int bond_order;       // 1=single, 2=double, 3=triple
    int n_bonding_e;      // number of bonding electrons
};

static constexpr Bond bonds[] = {
    // ─── Homonuclear diatomics ───
    {"H-H",    1,  1,  0.741e-10,  4.478,  1, 2},
    {"Li-Li",  3,  3,  2.673e-10,  1.046,  1, 2},
    {"B-B",    5,  5,  1.590e-10,  3.02,   1, 2},
    {"C-C",    6,  6,  1.243e-10,  6.29,   2, 4},
    {"N≡N",    7,  7,  1.098e-10,  9.759,  3, 6},
    {"O=O",    8,  8,  1.208e-10,  5.116,  2, 4},
    {"F-F",    9,  9,  1.412e-10,  1.602,  1, 2},
    {"Na-Na", 11, 11,  3.079e-10,  0.750,  1, 2},
    {"Si-Si", 14, 14,  2.246e-10,  3.21,   1, 2},
    {"P-P",   15, 15,  1.893e-10,  5.03,   3, 6},
    {"S-S",   16, 16,  1.889e-10,  4.37,   2, 4},
    {"Cl-Cl", 17, 17,  1.988e-10,  2.514,  1, 2},
    {"Br-Br", 35, 35,  2.281e-10,  1.971,  1, 2},
    {"I-I",   53, 53,  2.666e-10,  1.542,  1, 2},

    // ─── Heteronuclear diatomics ───
    {"H-F",    1,  9,  0.917e-10,  5.869,  1, 2},
    {"H-Cl",   1, 17,  1.275e-10,  4.434,  1, 2},
    {"H-Br",   1, 35,  1.414e-10,  3.758,  1, 2},
    {"H-I",    1, 53,  1.609e-10,  3.054,  1, 2},
    {"C-O",    6,  8,  1.128e-10,  11.09,  3, 6},
    {"C-H",    6,  1,  1.120e-10,  3.51,   1, 2},
    {"N-H",    7,  1,  1.036e-10,  3.42,   1, 2},
    {"O-H",    8,  1,  0.970e-10,  4.41,   1, 2},
    {"N-O",    7,  8,  1.151e-10,  6.497,  2, 4},
    {"S-H",   16,  1,  1.336e-10,  3.67,   1, 2},
    {"Si-O",  14,  8,  1.510e-10,  8.26,   2, 4},
    {"Li-H",   3,  1,  1.595e-10,  2.429,  1, 2},
    {"Na-Cl", 11, 17,  2.361e-10,  4.23,   1, 2},
    {"Li-F",   3,  9,  1.564e-10,  5.98,   1, 2},
    {"Na-F",  11,  9,  1.926e-10,  4.97,   1, 2},
    {"K-Cl",  19, 17,  2.667e-10,  4.34,   1, 2},
    {"B-H",    5,  1,  1.232e-10,  3.42,   1, 2},
    {"C-F",    6,  9,  1.272e-10,  5.71,   1, 2},
    {"C-Cl",   6, 17,  1.767e-10,  3.40,   1, 2},
    {"Si-H",  14,  1,  1.520e-10,  3.06,   1, 2},

    // ─── Multiply bonded ───
    {"C=C",    6,  6,  1.339e-10,  6.29,   2, 4},
    {"C≡C",    6,  6,  1.203e-10,  8.67,   3, 6},
    {"C=O",    6,  8,  1.200e-10,  7.72,   2, 4},
    {"N=N",    7,  7,  1.252e-10,  4.18,   2, 4},

    // ─── Weak bonds ───
    {"Cs-Cs", 55, 55,  4.470e-10,  0.452,  1, 2},
    {"Rb-Rb", 37, 37,  4.170e-10,  0.490,  1, 2},
};

static constexpr int N_BONDS = sizeof(bonds) / sizeof(bonds[0]);

int main() {
    std::puts("════════════════════════════════════════════════════════════════════════");
    std::puts("  CQ09c: 40-BOND SURVEY — Is the Discrepancy Scaled, Metricised, or Independent?");
    std::puts("════════════════════════════════════════════════════════════════════════\n");

    // ─── Compute SDT estimates for each bond ───
    //
    // The unified field velocity at the bond midpoint:
    //   v(d/2) = cα√(a₀/(d/2)) = cα√(2a₀/d)
    //
    // Naive estimate (electron as test particle):
    //   ΔE_naive = m_e [v(d/2)² - v(a₀)²]
    //            = m_e c²α² [2a₀/d - 1]
    //            = 2Ry × [2a₀/d - 1]
    //   where Ry = 13.606 eV
    //
    // With τ = 1/3 traction fraction:
    //   ΔE_τ = (1/3) × ΔE_naive
    //
    // With bond order (n_bonding_electrons / 2):
    //   ΔE_order = ΔE_τ × (n_bonding_e / 2)
    //
    // With proton repulsion subtracted:
    //   V_PP = k_e Z₁Z₂ e² / d (for ionic; for covalent, screened)

    constexpr double Ry = 13.60569;  // Rydberg in eV

    std::printf("  %-10s %5s %5s %8s %8s %3s %8s %8s %8s %8s %8s\n",
                "Bond", "Z1", "Z2", "d(Å)", "De(eV)", "BO",
                "Naive", "τ=1/3", "Ratio_N", "Ratio_τ", "d/a₀");
    std::puts("  ────────── ───── ───── ──────── ──────── ─── ──────── ──────── ──────── ──────── ────────");

    double sum_ratio_naive = 0, sum_ratio_tau = 0;
    double min_ratio_n = 1e9, max_ratio_n = 0;
    double min_ratio_t = 1e9, max_ratio_t = 0;
    double ratios_naive[N_BONDS], ratios_tau[N_BONDS];
    double d_over_a0[N_BONDS];

    for (int i = 0; i < N_BONDS; ++i) {
        auto& b = bonds[i];
        double d = b.d_m;
        double r_mid = d / 2.0;

        // Unified field velocity at midpoint
        double v_mid = c * alpha * std::sqrt(a_0 / r_mid);
        double v_a0  = c * alpha;  // = αc at ground state

        // Energy surplus: electron KE at midpoint vs at a₀
        // ΔE = m_e(v_mid² - v_a0²) = m_e c² α² (a₀/r_mid - 1) = 2Ry(2a₀/d - 1)
        double ratio_r = 2.0 * a_0 / d;  // = a₀/(d/2)... wait, 2a₀/d
        double dE_naive_eV = 2.0 * Ry * (ratio_r - 1.0);

        // Scale by bond order
        double n_pairs = b.n_bonding_e / 2.0;
        dE_naive_eV *= n_pairs;

        // With τ = 1/3
        double dE_tau_eV = dE_naive_eV / 3.0;

        // Ratios
        double r_naive = dE_naive_eV / b.De_eV;
        double r_tau   = dE_tau_eV / b.De_eV;
        double d_a0    = d / a_0;

        ratios_naive[i] = r_naive;
        ratios_tau[i]   = r_tau;
        d_over_a0[i]    = d_a0;

        sum_ratio_naive += r_naive;
        sum_ratio_tau   += r_tau;
        min_ratio_n = std::min(min_ratio_n, r_naive);
        max_ratio_n = std::max(max_ratio_n, r_naive);
        min_ratio_t = std::min(min_ratio_t, r_tau);
        max_ratio_t = std::max(max_ratio_t, r_tau);

        std::printf("  %-10s %5d %5d %8.3f %8.3f %3d %8.2f %8.2f %8.3f %8.3f %8.3f\n",
                    b.name, b.Z1, b.Z2,
                    d * 1e10, b.De_eV, b.bond_order,
                    dE_naive_eV, dE_tau_eV,
                    r_naive, r_tau, d_a0);
    }

    double mean_n = sum_ratio_naive / N_BONDS;
    double mean_t = sum_ratio_tau / N_BONDS;

    // Standard deviation
    double var_n = 0, var_t = 0;
    for (int i = 0; i < N_BONDS; ++i) {
        var_n += (ratios_naive[i] - mean_n) * (ratios_naive[i] - mean_n);
        var_t += (ratios_tau[i]   - mean_t) * (ratios_tau[i]   - mean_t);
    }
    double sd_n = std::sqrt(var_n / N_BONDS);
    double sd_t = std::sqrt(var_t / N_BONDS);
    double cv_n = sd_n / mean_n;  // coefficient of variation
    double cv_t = sd_t / mean_t;

    std::puts("\n  ════════════════════════════════════════════════════════");
    std::puts("  STATISTICAL ANALYSIS OF DISCREPANCY RATIOS");
    std::puts("  ════════════════════════════════════════════════════════\n");

    std::printf("  NAIVE (no τ):\n");
    std::printf("    Mean ratio:  %.3f\n", mean_n);
    std::printf("    Std dev:     %.3f\n", sd_n);
    std::printf("    CV:          %.3f (%.1f%%)\n", cv_n, cv_n*100);
    std::printf("    Range:       [%.3f, %.3f]\n", min_ratio_n, max_ratio_n);
    std::printf("    Spread:      %.1f×\n\n", max_ratio_n / min_ratio_n);

    std::printf("  WITH τ = 1/3:\n");
    std::printf("    Mean ratio:  %.3f\n", mean_t);
    std::printf("    Std dev:     %.3f\n", sd_t);
    std::printf("    CV:          %.3f (%.1f%%)\n", cv_t, cv_t*100);
    std::printf("    Range:       [%.3f, %.3f]\n", min_ratio_t, max_ratio_t);
    std::printf("    Spread:      %.1f×\n\n", max_ratio_t / min_ratio_t);

    // ─── Classify ───
    std::puts("  CLASSIFICATION:");
    if (cv_t < 0.15) {
        std::printf("    CV = %.1f%% < 15%% → SCALED (constant universal factor)\n", cv_t*100);
        std::printf("    Missing factor ≈ 1/%.2f\n", mean_t);
    } else if (cv_t < 0.40) {
        std::printf("    CV = %.1f%% → METRICISED (ratio depends on bond property)\n", cv_t*100);
    } else {
        std::printf("    CV = %.1f%% > 40%% → INDEPENDENT (no universal pattern)\n", cv_t*100);
    }

    // ─── Check for correlation with d/a₀ ───
    // Compute Pearson r between ratio_tau and d/a₀
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0, sum_y2 = 0;
    for (int i = 0; i < N_BONDS; ++i) {
        double x = d_over_a0[i];
        double y = ratios_tau[i];
        sum_x += x; sum_y += y;
        sum_xy += x*y; sum_x2 += x*x; sum_y2 += y*y;
    }
    double n = static_cast<double>(N_BONDS);
    double r_pearson = (n*sum_xy - sum_x*sum_y) /
        std::sqrt((n*sum_x2 - sum_x*sum_x) * (n*sum_y2 - sum_y*sum_y));

    std::printf("\n  CORRELATION: ratio_τ vs d/a₀\n");
    std::printf("    Pearson r = %.4f\n", r_pearson);
    if (std::abs(r_pearson) > 0.7)
        std::printf("    STRONG correlation → ratio is a function of bond length\n");
    else if (std::abs(r_pearson) > 0.4)
        std::printf("    MODERATE correlation → partial dependence on bond length\n");
    else
        std::printf("    WEAK correlation → bond length alone does not explain it\n");

    // ─── Check for correlation with Z_eff = Z1*Z2 ───
    sum_x = sum_y = sum_xy = sum_x2 = sum_y2 = 0;
    for (int i = 0; i < N_BONDS; ++i) {
        double x = std::sqrt(static_cast<double>(bonds[i].Z1 * bonds[i].Z2));
        double y = ratios_tau[i];
        sum_x += x; sum_y += y;
        sum_xy += x*y; sum_x2 += x*x; sum_y2 += y*y;
    }
    double r_Z = (n*sum_xy - sum_x*sum_y) /
        std::sqrt((n*sum_x2 - sum_x*sum_x) * (n*sum_y2 - sum_y*sum_y));

    std::printf("\n  CORRELATION: ratio_τ vs √(Z₁Z₂)\n");
    std::printf("    Pearson r = %.4f\n", r_Z);
    if (std::abs(r_Z) > 0.7)
        std::printf("    STRONG correlation → ratio depends on nuclear charge\n");
    else if (std::abs(r_Z) > 0.4)
        std::printf("    MODERATE correlation\n");
    else
        std::printf("    WEAK correlation\n");

    // ─── Check for correlation with bond order ───
    sum_x = sum_y = sum_xy = sum_x2 = sum_y2 = 0;
    for (int i = 0; i < N_BONDS; ++i) {
        double x = static_cast<double>(bonds[i].bond_order);
        double y = ratios_tau[i];
        sum_x += x; sum_y += y;
        sum_xy += x*y; sum_x2 += x*x; sum_y2 += y*y;
    }
    double r_BO = (n*sum_xy - sum_x*sum_y) /
        std::sqrt((n*sum_x2 - sum_x*sum_x) * (n*sum_y2 - sum_y*sum_y));

    std::printf("\n  CORRELATION: ratio_τ vs bond_order\n");
    std::printf("    Pearson r = %.4f\n", r_BO);
    if (std::abs(r_BO) > 0.7)
        std::printf("    STRONG correlation → ratio depends on bond order\n");
    else if (std::abs(r_BO) > 0.4)
        std::printf("    MODERATE correlation\n");
    else
        std::printf("    WEAK correlation\n");

    // ─── Sorted by ratio to see the pattern visually ───
    int idx[N_BONDS];
    for (int i = 0; i < N_BONDS; ++i) idx[i] = i;
    std::sort(idx, idx + N_BONDS, [&](int a, int b) {
        return ratios_tau[a] < ratios_tau[b];
    });

    std::puts("\n  ════════════════════════════════════════════════════════");
    std::puts("  BONDS SORTED BY τ-RATIO (lowest first)");
    std::puts("  ════════════════════════════════════════════════════════\n");
    std::printf("  %-10s %8s %8s %8s %5s %8s\n",
                "Bond", "De(eV)", "τ-est", "Ratio", "BO", "d/a₀");
    std::puts("  ────────── ──────── ──────── ──────── ───── ────────");

    for (int i = 0; i < N_BONDS; ++i) {
        int j = idx[i];
        double d = bonds[j].d_m;
        double ratio_r = 2.0 * a_0 / d;
        double dE = 2.0 * Ry * (ratio_r - 1.0) * (bonds[j].n_bonding_e / 2.0) / 3.0;
        std::printf("  %-10s %8.3f %8.2f %8.3f %5d %8.3f\n",
                    bonds[j].name, bonds[j].De_eV, dE,
                    ratios_tau[j], bonds[j].bond_order, d / a_0);
    }

    std::puts("\n  ════════════════════════════════════════════════════════");
    std::puts("  DIAGNOSTIC: Is the ratio = f(d/a₀)?");
    std::puts("  If ratio ~ (d/a₀)^n then log(ratio) vs log(d/a₀) is linear");
    std::puts("  ════════════════════════════════════════════════════════\n");

    // Log-log correlation
    sum_x = sum_y = sum_xy = sum_x2 = sum_y2 = 0;
    for (int i = 0; i < N_BONDS; ++i) {
        double x = std::log(d_over_a0[i]);
        double y = std::log(ratios_tau[i]);
        sum_x += x; sum_y += y;
        sum_xy += x*y; sum_x2 += x*x; sum_y2 += y*y;
    }
    double r_log = (n*sum_xy - sum_x*sum_y) /
        std::sqrt((n*sum_x2 - sum_x*sum_x) * (n*sum_y2 - sum_y*sum_y));
    // Slope = power law exponent
    double slope = (n*sum_xy - sum_x*sum_y) / (n*sum_x2 - sum_x*sum_x);
    double intercept = (sum_y - slope * sum_x) / n;

    std::printf("  log-log regression: ln(ratio) = %.4f × ln(d/a₀) + %.4f\n",
                slope, intercept);
    std::printf("  Power law exponent: %.4f\n", slope);
    std::printf("  Pearson r (log-log): %.4f\n", r_log);
    std::printf("  If slope ≈ 1: ratio ∝ d/a₀ (linear in bond length)\n");
    std::printf("  If slope ≈ 0: ratio ≈ const (scaled)\n");
    std::printf("  Prefactor: exp(%.4f) = %.4f\n\n", intercept, std::exp(intercept));

    return 0;
}
