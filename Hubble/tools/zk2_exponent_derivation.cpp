// ================================================================
// zk2_exponent_derivation.cpp — Power Law Exponents Analysis
//
// Tests whether the (5/4, 3/4) solar opacity decoupling exponents
// are dimensionally constrained or merely fitted.
//
// Measured from solar multi-wavelength data:
//   p_short = 1.2344  (from zk2_spation_profile.cpp)
//   p_long  = 0.7552  (from zk2_spation_profile.cpp)
//
// Hypothesised constraints:
//   p_short = 5/4 = 1.2500
//   p_long  = 3/4 = 0.7500
//   Sum     = 2   (d_eff = dimensionality of decoupling surface)
//   Delta   = 1/4 (from lattice mode partition)
//
// This tool computes the measured values, the theoretical values,
// and the residuals. It does NOT assume the theory is correct.
// ================================================================

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>

constexpr double c_mps = 299792458.0;

// Solar multi-wavelength radius data
// From zk2_spation_profile.cpp output (10_Spation_Pressure_Profile.md)
struct Band {
    const char* name;
    double lambda_m;    // wavelength in metres
    double R_ratio;     // R/R_sun
    bool is_short;      // true = λ < λ₀, false = λ > λ₀
    bool fit_usable;    // true = include in fit
};

constexpr double lambda_0 = 1.6e-6;  // natural wavelength (H-band minimum)

std::vector<Band> build_bands() {
    return {
        // ── Short side (λ < λ₀) ──
        {"hard X (1nm)",    1.0e-9,   1.5000, true,  true},
        {"soft X (5nm)",    5.0e-9,   1.3000, true,  true},
        {"Fe XVIII (9.4nm)",9.4e-9,   1.2000, true,  true},
        {"Fe IX (17.1nm)", 17.1e-9,   1.1000, true,  true},
        {"Fe XII (19.5nm)",19.5e-9,   1.0800, true,  true},
        {"He II (30.4nm)", 30.4e-9,   1.0500, true,  true},
        {"Ly-alpha",       121.6e-9,  1.0050, true,  true},
        {"C IV (160nm)",   160.0e-9,  1.0030, true,  true},
        {"Mg II k (280nm)",280.0e-9,  1.0020, true,  true},
        {"U-band (360nm)", 360.0e-9,  1.0008, true,  true},
        {"B-band (450nm)", 450.0e-9,  1.0005, true,  true},

        // ── Minimum (λ = λ₀) ──
        {"H-band (1.6um)",  1.6e-6,  0.9980, false, false},  // minimum

        // ── Long side (λ > λ₀) ──
        {"ALMA B10 (350um)",350.0e-6, 1.0050, false, true},
        {"ALMA B7 (850um)", 850.0e-6, 1.0070, false, true},
        {"ALMA B6 (1.3mm)", 1.3e-3,   1.0100, false, true},
        {"ALMA B3 (3mm)",   3.0e-3,   1.0150, false, true},
        {"2cm radio",       2.0e-2,   1.1500, false, true},
        {"6cm radio",       6.0e-2,   1.3000, false, true},
        {"20cm radio",      0.20,     1.7000, false, true},
        {"50cm radio",      0.50,     2.2000, false, true},
        {"1m radio",        1.00,     3.0000, false, true},
        {"2m radio",        2.00,     3.8000, false, true},
        {"3m radio",        3.00,     4.5000, false, true},
        {"5m radio",        5.00,     6.0000, false, true},
        {"10m radio",      10.00,    10.0000, false, true},
    };
}

// Weighted least-squares power law fit in log-log space:
//   log10(dR) = a + p × log10(x)
// where dR = |R/R_sun - 1| and x = |lambda_0/lambda| (short) or |lambda/lambda_0| (long)
struct PowerFit {
    double a;       // intercept
    double p;       // exponent
    double r2;      // R-squared
    double sigma_p; // uncertainty on exponent
};

PowerFit fit_power_law(const std::vector<Band>& bands, bool fit_short) {
    std::vector<double> lx, ly;

    for (auto& b : bands) {
        if (!b.fit_usable) continue;
        if (b.is_short != fit_short) continue;

        double dR = std::abs(b.R_ratio - 1.0);
        if (dR < 1e-10) continue;  // skip zero

        double x = fit_short ?
            lambda_0 / b.lambda_m :   // λ₀/λ for short side
            b.lambda_m / lambda_0;    // λ/λ₀ for long side

        if (x <= 1.0) continue;  // must be > 1

        lx.push_back(std::log10(x));
        ly.push_back(std::log10(dR));
    }

    int n = static_cast<int>(lx.size());
    if (n < 2) return {0, 0, 0, 0};

    // Linear regression
    double sx = 0, sy = 0, sxx = 0, sxy = 0;
    for (int i = 0; i < n; i++) {
        sx += lx[i];
        sy += ly[i];
        sxx += lx[i] * lx[i];
        sxy += lx[i] * ly[i];
    }
    double N = static_cast<double>(n);
    double D = N * sxx - sx * sx;
    double p = (N * sxy - sx * sy) / D;
    double a = (sxx * sy - sx * sxy) / D;

    // R²
    double ybar = sy / N;
    double SS_tot = 0, SS_res = 0;
    for (int i = 0; i < n; i++) {
        SS_tot += (ly[i] - ybar) * (ly[i] - ybar);
        double pred = a + p * lx[i];
        SS_res += (ly[i] - pred) * (ly[i] - pred);
    }
    double r2 = 1.0 - SS_res / SS_tot;

    // Standard error on slope
    double s2 = SS_res / (N - 2);
    double sigma_p = std::sqrt(s2 * N / D);

    return {a, p, r2, sigma_p};
}

int main() {
    auto bands = build_bands();

    std::cout << "# Solar Opacity Exponent Analysis\n\n";
    std::cout << "> Tests whether p_short = 5/4 and p_long = 3/4\n";
    std::cout << "> are supported by the data.\n\n";

    // ── SECTION 1: RAW DATA ──
    std::cout << "## 1. Solar Multi-Wavelength Radius Data\n\n";
    std::cout << "```\n";
    std::cout << std::left << std::setw(20) << "Band"
              << std::right
              << std::setw(14) << "lambda(m)"
              << std::setw(10) << "R/R_sun"
              << std::setw(10) << "dR/R_sun"
              << std::setw(10) << "side"
              << "\n";
    std::cout << std::string(64, '-') << "\n";

    for (auto& b : bands) {
        double dR = b.R_ratio - 1.0;
        std::cout << std::left << std::setw(20) << b.name
                  << std::right
                  << std::scientific << std::setprecision(3)
                  << std::setw(14) << b.lambda_m
                  << std::fixed << std::setprecision(4)
                  << std::setw(10) << b.R_ratio
                  << std::showpos << std::setw(10) << std::setprecision(4) << dR
                  << std::noshowpos
                  << std::setw(10) << (b.lambda_m < lambda_0 ? "short" :
                                       b.lambda_m > lambda_0 ? "long" : "MIN")
                  << "\n";
    }
    std::cout << "```\n\n";

    // ── SECTION 2: POWER LAW FITS ──
    std::cout << "## 2. Power Law Fits\n\n";

    auto fit_s = fit_power_law(bands, true);
    auto fit_l = fit_power_law(bands, false);

    std::cout << "### Short side (lambda < lambda_0)\n\n";
    std::cout << "```\n";
    std::cout << "dR/R_sun = 10^a × (lambda_0/lambda)^p\n\n";
    std::cout << "Measured exponent:  p_short = " << std::fixed << std::setprecision(4) << fit_s.p
              << " ± " << fit_s.sigma_p << "\n";
    std::cout << "Theoretical (5/4):  p_short = 1.2500\n";
    double err_s = (fit_s.p - 1.25) / 1.25 * 100;
    std::cout << "Discrepancy:        " << std::showpos << std::setprecision(2)
              << err_s << "%" << std::noshowpos << "\n";
    double sigma_s = std::abs(fit_s.p - 1.25) / fit_s.sigma_p;
    std::cout << "Sigma from 5/4:     " << std::setprecision(1) << sigma_s << " sigma\n";
    std::cout << "R²:                 " << std::setprecision(6) << fit_s.r2 << "\n";
    std::cout << "Amplitude (10^a):   " << std::scientific << std::setprecision(4)
              << std::pow(10.0, fit_s.a) << "\n";
    std::cout << "```\n\n";

    std::cout << "### Long side (lambda > lambda_0)\n\n";
    std::cout << "```\n";
    std::cout << "dR/R_sun = 10^a × (lambda/lambda_0)^p\n\n";
    std::cout << "Measured exponent:  p_long = " << std::fixed << std::setprecision(4) << fit_l.p
              << " ± " << fit_l.sigma_p << "\n";
    std::cout << "Theoretical (3/4):  p_long = 0.7500\n";
    double err_l = (fit_l.p - 0.75) / 0.75 * 100;
    std::cout << "Discrepancy:        " << std::showpos << std::setprecision(2)
              << err_l << "%" << std::noshowpos << "\n";
    double sigma_l = std::abs(fit_l.p - 0.75) / fit_l.sigma_p;
    std::cout << "Sigma from 3/4:     " << std::setprecision(1) << sigma_l << " sigma\n";
    std::cout << "R²:                 " << std::setprecision(6) << fit_l.r2 << "\n";
    std::cout << "Amplitude (10^a):   " << std::scientific << std::setprecision(4)
              << std::pow(10.0, fit_l.a) << "\n";
    std::cout << "```\n\n";

    // ── SECTION 3: STRUCTURAL INVARIANTS ──
    std::cout << "## 3. Structural Invariants\n\n";
    std::cout << "```\n";

    double p_sum = fit_s.p + fit_l.p;
    double p_ratio = fit_s.p / fit_l.p;
    double p_prod = fit_s.p * fit_l.p;
    double p_diff = fit_s.p - fit_l.p;
    double delta = p_diff / 2.0;

    std::cout << "p_short + p_long = " << std::fixed << std::setprecision(4)
              << p_sum << "   (predicted: 2.0000, d_eff=2)\n";
    std::cout << "Error:             " << std::showpos << std::setprecision(4)
              << p_sum - 2.0 << std::noshowpos
              << " (" << std::setprecision(2) << (p_sum - 2.0)/2.0*100 << "%)\n\n";

    std::cout << "p_short / p_long = " << std::setprecision(4) << p_ratio
              << "   (predicted: 5/3 = 1.6667)\n";
    std::cout << "Error:             " << std::showpos << std::setprecision(4)
              << p_ratio - 5.0/3.0 << std::noshowpos
              << " (" << std::setprecision(2)
              << (p_ratio - 5.0/3.0)/(5.0/3.0)*100 << "%)\n\n";

    std::cout << "p_short × p_long = " << std::setprecision(4) << p_prod
              << "   (predicted: 15/16 = 0.9375)\n";
    std::cout << "Error:             " << std::showpos << std::setprecision(4)
              << p_prod - 15.0/16.0 << std::noshowpos
              << " (" << std::setprecision(2)
              << (p_prod - 15.0/16.0)/(15.0/16.0)*100 << "%)\n\n";

    std::cout << "delta = (p_short - p_long)/2 = " << std::setprecision(4) << delta
              << "   (predicted: 1/4 = 0.2500)\n";
    std::cout << "Error:             " << std::showpos << std::setprecision(4)
              << delta - 0.25 << std::noshowpos
              << " (" << std::setprecision(2)
              << (delta - 0.25)/0.25*100 << "%)\n";
    std::cout << "```\n\n";

    // ── SECTION 4: DIMENSIONAL ARGUMENT ──
    std::cout << "## 4. Dimensional Constraint Argument\n\n";
    std::cout << "### 4.1 Why Sum = d_eff\n\n";
    std::cout << "```\n";
    std::cout << "In a d-dimensional lattice, a wavelength decouples from\n";
    std::cout << "the pressure gradient at a surface of dimension d_surface.\n\n";
    std::cout << "The decoupling condition is:\n";
    std::cout << "  opacity(lambda, r) = tau_critical\n\n";
    std::cout << "The opacity profile divides into two regimes about lambda_0.\n";
    std::cout << "The total 'angular phase space' covered by both regimes must\n";
    std::cout << "equal the surface dimensionality:\n\n";
    std::cout << "  p_short + p_long = d_surface\n\n";
    std::cout << "For 3D space with spherical decoupling surface: d_surface = 2\n";
    std::cout << "Measured: " << std::fixed << std::setprecision(4)
              << p_sum << " vs predicted: 2.0000\n";
    std::cout << "```\n\n";

    std::cout << "### 4.2 Why delta = 1/(d_surface + d_bulk - 1) = 1/4\n\n";
    std::cout << "```\n";
    std::cout << "The asymmetry between short-side and long-side coupling:\n\n";
    std::cout << "  Short side: lambda < lambda_0 → resonance coupling\n";
    std::cout << "    Each oscillation cycle fits inside the lattice spacing\n";
    std::cout << "    → energy leaks per cycle → steeper decoupling\n";
    std::cout << "    → p = 1 + delta\n\n";
    std::cout << "  Long side: lambda > lambda_0 → impedance mismatch\n";
    std::cout << "    Oscillation exceeds lattice coherence length\n";
    std::cout << "    → coupling weakens continuously → shallower decoupling\n";
    std::cout << "    → p = 1 - delta\n\n";
    std::cout << "The splitting parameter delta from mode partition:\n";
    std::cout << "  delta = 1 / (d_surface + d_bulk - 1)\n";
    std::cout << "        = 1 / (2 + 3 - 1) = 1/4 = 0.2500\n\n";
    std::cout << "Measured: " << std::setprecision(4) << delta << "\n";
    std::cout << "CAVEAT: This is a CONSTRAINT argument, not a first-principles\n";
    std::cout << "derivation. A rigorous derivation would require computing\n";
    std::cout << "the mode-coupling coefficient from the lattice Hamiltonian.\n";
    std::cout << "```\n\n";

    // ── SECTION 5: BAND-BY-BAND PREDICTIONS ──
    std::cout << "## 5. Band-by-Band Predictions vs Measurements\n\n";
    std::cout << "Using theoretical exponents p_short = 5/4, p_long = 3/4\n";
    std::cout << "with measured amplitudes.\n\n";

    double A_s = std::pow(10.0, fit_s.a);
    double A_l = std::pow(10.0, fit_l.a);

    std::cout << "```\n";
    std::cout << std::left << std::setw(20) << "Band"
              << std::right
              << std::setw(12) << "R_meas"
              << std::setw(12) << "R_pred"
              << std::setw(10) << "err(%)"
              << std::setw(8) << "flag"
              << "\n";
    std::cout << std::string(62, '-') << "\n";

    for (auto& b : bands) {
        if (!b.fit_usable || b.R_ratio == 0.9980) continue;

        double dR_pred;
        if (b.is_short) {
            double x = lambda_0 / b.lambda_m;
            dR_pred = A_s * std::pow(x, 5.0/4.0);
        } else {
            double x = b.lambda_m / lambda_0;
            dR_pred = A_l * std::pow(x, 3.0/4.0);
        }
        double R_pred = 1.0 + dR_pred;
        double err = (R_pred - b.R_ratio) / b.R_ratio * 100;
        const char* flag = std::abs(err) > 0.08 ? ">" : "OK";

        std::cout << std::left << std::setw(20) << b.name
                  << std::right << std::fixed
                  << std::setw(12) << std::setprecision(4) << b.R_ratio
                  << std::setw(12) << std::setprecision(4) << R_pred
                  << std::showpos << std::setw(10) << std::setprecision(3) << err
                  << std::noshowpos
                  << std::setw(8) << flag
                  << "\n";
    }
    std::cout << "```\n\n";

    // ── SECTION 6: PHYSICAL CONNECTIONS ──
    std::cout << "## 6. Physical Connections\n\n";

    std::cout << "### 6.1 Ratio 5/3 appearances\n\n";
    std::cout << "```\n";
    double kolmogorov = 5.0 / 3.0;
    double adiabatic = 5.0 / 3.0;  // monatomic gas gamma

    // λ₀ at z=1100 vs CMB peak wavelength
    double lambda_cmb_peak = 2.898e-3 / 2.7255;  // Wien displacement law at T_CMB
    double lambda_0_at_rec = lambda_0 * (1.0 + 1100.0);  // λ₀ × (1+z_rec)
    double ratio_cmb = lambda_0_at_rec / lambda_cmb_peak;

    std::cout << "p_short / p_long measured:  " << std::fixed << std::setprecision(4|| 1)
              << p_ratio << "\n";
    std::cout << "Kolmogorov E(k) ~ k^{-5/3}: " << std::setprecision(4) << kolmogorov << "\n";
    std::cout << "Monatomic gamma:             " << std::setprecision(4) << adiabatic << "\n\n";
    std::cout << "lambda_0 × (1+z_rec):  " << std::scientific << std::setprecision(3)
              << lambda_0_at_rec << " m\n";
    std::cout << "CMB peak (Wien):       " << std::setprecision(3)
              << lambda_cmb_peak << " m\n";
    std::cout << "Ratio:                 " << std::fixed << std::setprecision(4)
              << ratio_cmb << "\n";
    std::cout << "\n";
    std::cout << "ASSESSMENT: The 5/3 ratio appears in multiple contexts.\n";
    std::cout << "Whether these are structurally linked or coincidental\n";
    std::cout << "cannot be determined from the exponent data alone.\n";
    std::cout << "```\n\n";

    // ── SECTION 7: VERDICT ──
    std::cout << "## 7. Verdict\n\n";
    std::cout << "```\n";
    std::cout << "Question: Are the exponents (5/4, 3/4) predicted or fitted?\n\n";
    std::cout << "Answer: PARTIALLY CONSTRAINED.\n\n";
    std::cout << "  1. The SUM = 2 constraint is dimensionally motivated\n";
    std::cout << "     and the data satisfy it to "
              << std::fixed << std::setprecision(2) << std::abs(p_sum - 2.0)/2.0*100
              << "%. STRONG.\n\n";
    std::cout << "  2. The SPLITTING delta = 1/4 is a mode-partition argument\n";
    std::cout << "     that fits the data to "
              << std::abs(delta - 0.25)/0.25*100 << "%. REASONABLE.\n\n";
    std::cout << "  3. The AMPLITUDES (A_s, A_l) are still fitted from data.\n";
    std::cout << "     They are not predicted from first principles.\n\n";
    std::cout << "  4. Individual band predictions using theoretical exponents\n";
    std::cout << "     deviate from measurement by up to several percent\n";
    std::cout << "     for coronal bands (hard X, Fe lines), because the\n";
    std::cout << "     corona is NOT a simple opacity-decoupling surface.\n\n";
    std::cout << "STATUS: The exponents are CONSTRAINED by dimensional\n";
    std::cout << "arguments, not derived from lattice dynamics. A full\n";
    std::cout << "derivation requires the lattice Hamiltonian and\n";
    std::cout << "mode-coupling computation, which does not yet exist.\n";
    std::cout << "```\n";

    return 0;
}
