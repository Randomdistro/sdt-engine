/**
 * @file sct_melting.cpp
 * @brief Structural Coding Theorem — Crystal Melting Point Predictor
 *
 * Models each crystal as an error-correcting code against thermal noise.
 * Channel: AWGN (Gaussian thermal displacement)
 * Signal:  lattice spacing (nearest-neighbor distance)
 * Noise:   thermal vibration amplitude (Debye model)
 *
 * Melting condition: Channel capacity C(T) drops below code rate R
 *   C(T) = 0.5 * log2(1 + SNR(T))
 *   SNR(T) = d_nn^2 * kappa / (4 * k_B * T)
 *   kappa = m * (k_B * Theta_D / hbar)^2   (Einstein spring constant)
 *
 * Solving C(T_m) = R:
 *   T_m = d_nn^2 * m * k_B * Theta_D^2 / (4 * hbar^2 * (2^(2R) - 1))
 *
 * R is the code rate = structural information bits per degree of freedom.
 * We fit R per structure type and test universality.
 *
 * @author SDT Engine — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

// ═══════════════════════════════════════════════════════════════════════
//  PHYSICAL CONSTANTS
// ═══════════════════════════════════════════════════════════════════════

namespace constants {
    constexpr double k_B   = 1.380649e-23;      // J/K
    constexpr double hbar  = 1.054571817e-34;    // J·s
    constexpr double amu   = 1.66053906660e-27;  // kg per atomic mass unit
    constexpr double eV    = 1.602176634e-19;    // J per eV
}

// ═══════════════════════════════════════════════════════════════════════
//  CRYSTAL DATA
// ═══════════════════════════════════════════════════════════════════════

enum class Structure { FCC, BCC, DIAMOND, HCP, SC };

const char* structure_str(Structure s) {
    switch (s) {
        case Structure::FCC:     return "FCC";
        case Structure::BCC:     return "BCC";
        case Structure::DIAMOND: return "DIA";
        case Structure::HCP:     return "HCP";
        case Structure::SC:      return "SC ";
        default: return "???";
    }
}

struct Crystal {
    std::string name;
    std::string symbol;
    Structure   structure;
    double      atomic_mass;   // amu
    double      a_lattice;     // Angstroms (lattice parameter)
    double      theta_D;       // Debye temperature (K)
    double      T_melt_obs;    // Observed melting point (K)
    int         coord_z;       // Coordination number
    int         group_order;   // Point group order |G|
    double      E_coh;         // Cohesive energy (eV/atom)
};

auto crystal_database() -> std::vector<Crystal> {
    return {
        // FCC metals (Oh, |G|=48, z=12)
        {"Copper",     "Cu", Structure::FCC, 63.546,  3.615, 343, 1358, 12, 48, 3.49},
        {"Silver",     "Ag", Structure::FCC, 107.868, 4.086, 225, 1235, 12, 48, 2.95},
        {"Gold",       "Au", Structure::FCC, 196.967, 4.078, 165, 1337, 12, 48, 3.81},
        {"Aluminum",   "Al", Structure::FCC, 26.982,  4.050, 428,  933, 12, 48, 3.39},
        {"Nickel",     "Ni", Structure::FCC, 58.693,  3.524, 450, 1728, 12, 48, 4.44},
        {"Platinum",   "Pt", Structure::FCC, 195.084, 3.924, 240, 2041, 12, 48, 5.84},
        {"Lead",       "Pb", Structure::FCC, 207.2,   4.951, 105,  601, 12, 48, 2.03},

        // BCC metals (Oh, |G|=48, z=8)
        {"Iron",       "Fe", Structure::BCC, 55.845,  2.870, 470, 1811,  8, 48, 4.28},
        {"Tungsten",   "W",  Structure::BCC, 183.84,  3.165, 400, 3695,  8, 48, 8.90},
        {"Chromium",   "Cr", Structure::BCC, 51.996,  2.910, 630, 2180,  8, 48, 4.10},
        {"Molybdenum", "Mo", Structure::BCC, 95.95,   3.147, 450, 2896,  8, 48, 6.82},
        {"Sodium",     "Na", Structure::BCC, 22.990,  4.225, 158,  371,  8, 48, 1.113},
        {"Potassium",  "K",  Structure::BCC, 39.098,  5.328, 91,   337,  8, 48, 0.934},
        {"Lithium",    "Li", Structure::BCC, 6.941,   3.510, 344,  454,  8, 48, 1.63},

        // Diamond cubic (Td, |G|=24, z=4)
        {"Silicon",    "Si", Structure::DIAMOND, 28.086, 5.431, 645, 1687, 4, 24, 4.63},
        {"Germanium",  "Ge", Structure::DIAMOND, 72.630, 5.658, 374, 1211, 4, 24, 3.85},

        // HCP metals (D6h, |G|=24, z=12)
        {"Titanium",   "Ti", Structure::HCP, 47.867,  2.951, 420, 1941, 12, 24, 4.85},
        {"Zinc",       "Zn", Structure::HCP, 65.38,   2.665, 327,  693, 12, 24, 1.35},
        {"Magnesium",  "Mg", Structure::HCP, 24.305,  3.209, 400,  923, 12, 24, 1.51},
    };
}

// ═══════════════════════════════════════════════════════════════════════
//  SCT MELTING POINT MODEL
// ═══════════════════════════════════════════════════════════════════════

// Nearest-neighbor distance from lattice parameter
double d_nn(const Crystal& c) {
    double a = c.a_lattice * 1e-10; // Convert Angstroms to meters
    switch (c.structure) {
        case Structure::FCC:     return a / std::sqrt(2.0);
        case Structure::BCC:     return a * std::sqrt(3.0) / 2.0;
        case Structure::DIAMOND: return a * std::sqrt(3.0) / 4.0;
        case Structure::HCP:     return a; // c/a ≈ ideal, d_nn ≈ a
        case Structure::SC:      return a;
    }
    return a;
}

// AWGN channel model: T_m from code rate R
// T_m = d_nn^2 * m * k_B * Theta_D^2 / (4 * hbar^2 * (2^(2R) - 1))
double predict_T_melt(const Crystal& c, double R) {
    double d = d_nn(c);
    double m = c.atomic_mass * constants::amu;
    double num = d * d * m * constants::k_B * c.theta_D * c.theta_D;
    double den = 4.0 * constants::hbar * constants::hbar * (std::pow(2.0, 2.0 * R) - 1.0);
    return num / den;
}

// Solve for the rate R that gives a specific melting point
double solve_R(const Crystal& c) {
    double d = d_nn(c);
    double m = c.atomic_mass * constants::amu;
    double num = d * d * m * constants::k_B * c.theta_D * c.theta_D;
    double den = 4.0 * constants::hbar * constants::hbar * c.T_melt_obs;
    double snr = num / den;
    return 0.5 * std::log2(1.0 + snr);
}

// Lindemann parameter from code rate
double lindemann_from_R(double R) {
    return 1.0 / std::sqrt(std::pow(2.0, 2.0 * R) - 1.0);
}

// ═══════════════════════════════════════════════════════════════════════
//  MAIN
// ═══════════════════════════════════════════════════════════════════════

int main() {
    auto crystals = crystal_database();

    std::printf("═══════════════════════════════════════════════════════════════════\n");
    std::printf("  STRUCTURAL CODING THEOREM — MELTING POINT PREDICTOR\n");
    std::printf("═══════════════════════════════════════════════════════════════════\n\n");
    std::printf("  Model: AWGN channel capacity = code rate at T_melt\n");
    std::printf("  C(T) = 0.5 log2(1 + SNR(T)),  SNR = d_nn² κ / (4 k_B T)\n");
    std::printf("  κ = m (k_B Θ_D / ℏ)²   (Einstein spring constant)\n\n");

    // ── Phase 1: Solve for R from measured data ──
    std::printf("  ┌─────────────────────────────────────────────────────────────────────────┐\n");
    std::printf("  │  PHASE 1: INVERSE SOLVE — R from measured melting points                │\n");
    std::printf("  ├────────┬────┬─────┬──────────┬──────────┬──────────┬─────────┬──────────┤\n");
    std::printf("  │ Symbol │ Ty │  z  │  Θ_D (K) │  T_m (K) │  E_coh   │  R_inv  │  c_L     │\n");
    std::printf("  ├────────┼────┼─────┼──────────┼──────────┼──────────┼─────────┼──────────┤\n");

    double R_sum_fcc = 0, R_sum_bcc = 0, R_sum_dia = 0, R_sum_hcp = 0;
    int n_fcc = 0, n_bcc = 0, n_dia = 0, n_hcp = 0;

    for (auto& c : crystals) {
        double R = solve_R(c);
        double cL = lindemann_from_R(R);

        std::printf("  │   %2s   │ %s│  %2d │  %6.0f  │  %6.0f  │  %5.2f eV │  %5.3f  │  %6.4f  │\n",
                    c.symbol.c_str(), structure_str(c.structure),
                    c.coord_z, c.theta_D, c.T_melt_obs, c.E_coh, R, cL);

        switch (c.structure) {
            case Structure::FCC:     R_sum_fcc += R; ++n_fcc; break;
            case Structure::BCC:     R_sum_bcc += R; ++n_bcc; break;
            case Structure::DIAMOND: R_sum_dia += R; ++n_dia; break;
            case Structure::HCP:     R_sum_hcp += R; ++n_hcp; break;
            default: break;
        }
    }

    std::printf("  └────────┴────┴─────┴──────────┴──────────┴──────────┴─────────┴──────────┘\n\n");

    double R_fcc = R_sum_fcc / n_fcc;
    double R_bcc = R_sum_bcc / n_bcc;
    double R_dia = R_sum_dia / n_dia;
    double R_hcp = R_sum_hcp / n_hcp;

    std::printf("  Mean code rates by structure type:\n");
    std::printf("    FCC      R = %.3f  (n=%d)\n", R_fcc, n_fcc);
    std::printf("    BCC      R = %.3f  (n=%d)\n", R_bcc, n_bcc);
    std::printf("    Diamond  R = %.3f  (n=%d)\n", R_dia, n_dia);
    std::printf("    HCP      R = %.3f  (n=%d)\n\n", R_hcp, n_hcp);

    // ── Phase 2: Predict with structure-type R ──
    std::printf("  ┌─────────────────────────────────────────────────────────────────────────┐\n");
    std::printf("  │  PHASE 2: FORWARD PREDICT — T_m from structure-type R                   │\n");
    std::printf("  ├────────┬────┬──────────┬──────────┬──────────┬──────────┬────────────────┤\n");
    std::printf("  │ Symbol │ Ty │ R_struct │ T_pred K │ T_obs  K │ Error %%  │ Verdict        │\n");
    std::printf("  ├────────┼────┼──────────┼──────────┼──────────┼──────────┼────────────────┤\n");

    double total_abs_err = 0;
    int count = 0;

    for (auto& c : crystals) {
        double R_use = 0;
        switch (c.structure) {
            case Structure::FCC:     R_use = R_fcc; break;
            case Structure::BCC:     R_use = R_bcc; break;
            case Structure::DIAMOND: R_use = R_dia; break;
            case Structure::HCP:     R_use = R_hcp; break;
            default: break;
        }

        double T_pred = predict_T_melt(c, R_use);
        double err_pct = 100.0 * (T_pred - c.T_melt_obs) / c.T_melt_obs;
        total_abs_err += std::abs(err_pct);
        ++count;

        const char* verdict = std::abs(err_pct) < 10 ? "EXCELLENT" :
                              std::abs(err_pct) < 25 ? "GOOD     " :
                              std::abs(err_pct) < 50 ? "FAIR     " : "POOR     ";

        std::printf("  │   %2s   │ %s│  %5.3f  │  %6.0f  │  %6.0f  │  %+6.1f  │ %s     │\n",
                    c.symbol.c_str(), structure_str(c.structure),
                    R_use, T_pred, c.T_melt_obs, err_pct, verdict);
    }

    std::printf("  └────────┴────┴──────────┴──────────┴──────────┴──────────┴────────────────┘\n\n");

    double mean_err = total_abs_err / count;
    std::printf("  Mean absolute error: %.1f%%\n\n", mean_err);

    // ── Phase 3: Universal R prediction ──
    double R_all = 0;
    for (auto& c : crystals) R_all += solve_R(c);
    R_all /= crystals.size();

    std::printf("  ┌─────────────────────────────────────────────────────────────────────────┐\n");
    std::printf("  │  PHASE 3: UNIVERSAL R = %.3f — single rate for all crystals             │\n", R_all);
    std::printf("  ├────────┬────┬──────────┬──────────┬──────────┬────────────────────────────┤\n");
    std::printf("  │ Symbol │ Ty │ T_pred K │ T_obs  K │ Error %%  │ Assessment               │\n");
    std::printf("  ├────────┼────┼──────────┼──────────┼──────────┼────────────────────────────┤\n");

    total_abs_err = 0;
    for (auto& c : crystals) {
        double T_pred = predict_T_melt(c, R_all);
        double err_pct = 100.0 * (T_pred - c.T_melt_obs) / c.T_melt_obs;
        total_abs_err += std::abs(err_pct);

        const char* assessment = std::abs(err_pct) < 10 ? "EXCELLENT" :
                                 std::abs(err_pct) < 25 ? "GOOD     " :
                                 std::abs(err_pct) < 50 ? "FAIR     " : "POOR     ";

        std::printf("  │   %2s   │ %s│  %6.0f  │  %6.0f  │  %+6.1f  │ %s                  │\n",
                    c.symbol.c_str(), structure_str(c.structure),
                    T_pred, c.T_melt_obs, err_pct, assessment);
    }

    std::printf("  └────────┴────┴──────────┴──────────┴──────────┴────────────────────────────┘\n\n");

    mean_err = total_abs_err / crystals.size();
    std::printf("  Universal R mean absolute error: %.1f%%\n\n", mean_err);

    // ── Phase 4: Key insight ──
    std::printf("  ═══════════════════════════════════════════════════════════════════\n");
    std::printf("  STRUCTURAL CODING THEOREM — ASSESSMENT\n");
    std::printf("  ═══════════════════════════════════════════════════════════════════\n\n");
    std::printf("  The Lindemann parameter c_L is NOT universal — it varies by\n");
    std::printf("  structure type. The SCT predicts this variation:\n\n");
    std::printf("    c_L(FCC)     = %.4f   (from R = %.3f)\n", lindemann_from_R(R_fcc), R_fcc);
    std::printf("    c_L(BCC)     = %.4f   (from R = %.3f)\n", lindemann_from_R(R_bcc), R_bcc);
    std::printf("    c_L(Diamond) = %.4f   (from R = %.3f)\n", lindemann_from_R(R_dia), R_dia);
    std::printf("    c_L(HCP)     = %.4f   (from R = %.3f)\n\n", lindemann_from_R(R_hcp), R_hcp);
    std::printf("  If c_L varies systematically with crystal symmetry, the SCT\n");
    std::printf("  explains WHY — it is the channel capacity threshold of the\n");
    std::printf("  crystal's error-correcting code.\n\n");

    return 0;
}
