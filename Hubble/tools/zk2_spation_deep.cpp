#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

constexpr double c_mps  = 2.99792458e8;
constexpr double z_sun  = 2.12270e-6;
constexpr double R_sun  = 6.95700e8;
constexpr double kappa_sun = R_sun * z_sun;
const     double k_sun  = 1.0 / std::sqrt(z_sun);
const     double v_sun  = c_mps / k_sun;
const     double T_surf = 2.0 * M_PI * R_sun / v_sun;
constexpr double kB     = 8.617333e-5;  // eV/K
constexpr double h_eV   = 4.135668e-15; // eV·s
constexpr double lambda_0 = 1.6e-6;     // m
const     double E_0    = h_eV * c_mps / lambda_0;  // eV

struct Band {
    std::string name;
    double lambda_m;
    double R_ratio;
};

int main() {
    std::vector<Band> bands = {
        {"1.0 nm  (hard X)",     1.0e-9,   1.500},
        {"5.0 nm  (soft X)",     5.0e-9,   1.300},
        {"9.4 nm  (Fe XVIII)",   9.4e-9,   1.200},
        {"17.1 nm (Fe IX)",      1.71e-8,  1.100},
        {"30.4 nm (He II)",      3.04e-8,  1.050},
        {"121.6 nm (Ly-alpha)",  1.216e-7, 1.005},
        {"160 nm (C IV)",        1.6e-7,   1.003},
        {"280 nm (Mg II k)",     2.8e-7,   1.002},
        {"550 nm (V-band)",      5.5e-7,   1.000},
        {"1.6 um (H-band)",      1.6e-6,   0.998},  // MINIMUM
        {"2.2 um (K-band)",      2.2e-6,   0.999},
        {"350 um (ALMA B10)",    3.5e-4,   1.005},
        {"1.3 mm (ALMA B6)",     1.3e-3,   1.010},
        {"3.0 mm (ALMA B3)",     3.0e-3,   1.015},
        {"2.0 cm",               2.0e-2,   1.150},
        {"6.0 cm",               6.0e-2,   1.300},
        {"20 cm",                2.0e-1,   1.700},
        {"1.0 m",                1.0,      3.000},
        {"3.0 m",                3.0,      4.500},
        {"10 m",                 10.0,     10.00},
    };

    std::sort(bands.begin(), bands.end(),
              [](const Band& a, const Band& b){ return a.lambda_m < b.lambda_m; });

    // Power law coefficients from previous run
    double A_short = 2.0403e-4, p_short = 1.2344;  // dR = A*(lambda_0/lambda)^p
    double A_long  = 7.5903e-5, p_long  = 0.7552;  // dR = A*(lambda/lambda_0)^p

    // ===================================================================
    std::cout << "# Spation Deep Analysis — Cross-Normalisation & Connections\n\n";
    std::cout << "---\n\n";

    // ===================================================================
    // QUESTION 1: Cross-normalisation
    // ===================================================================
    std::cout << "## 1. Cross-Normalisation of Power Laws\n\n";
    std::cout << "Short-side law: dR/R_sun = " << A_short << " * (lambda_0/lambda)^" << p_short << "\n";
    std::cout << "Long-side law:  dR/R_sun = " << A_long  << " * (lambda/lambda_0)^" << p_long << "\n\n";

    // Part A: Apply SHORT-side law to LONG-side wavelengths
    std::cout << "### A. Short-side law extrapolated to long wavelengths\n\n";
    std::cout << "If the short-side coupling applied on the long side too,\n";
    std::cout << "long wavelengths would decouple at these radii:\n\n";
    std::cout << "```\n";
    std::cout << std::left << std::setw(24) << "Band"
              << std::right << std::setw(10) << "R_actual"
              << std::setw(10) << "R_short"
              << std::setw(10) << "ratio"
              << "\n";
    std::cout << std::string(54, '-') << "\n";
    for (auto& b : bands) {
        if (b.lambda_m <= lambda_0) continue;
        double actual_dR = b.R_ratio - 1.0;
        if (actual_dR < 0.0001) continue;
        // Short law says: for lambda > lambda_0, the "distance from minimum"
        // is lambda/lambda_0, and the short law used lambda_0/lambda.
        // Mirror: use lambda/lambda_0 with SHORT exponent
        double ratio_to_min = b.lambda_m / lambda_0;
        double pred_dR_short = A_short * std::pow(ratio_to_min, p_short);
        double pred_R_short = 1.0 + pred_dR_short;

        std::cout << std::left << std::setw(24) << b.name
                  << std::right << std::fixed << std::setprecision(4)
                  << std::setw(10) << b.R_ratio
                  << std::setw(10) << pred_R_short
                  << std::setw(10) << pred_R_short / b.R_ratio
                  << "\n";
    }
    std::cout << "```\n\n";

    // Part B: Apply LONG-side law to SHORT-side wavelengths
    std::cout << "### B. Long-side law extrapolated to short wavelengths\n\n";
    std::cout << "If the long-side coupling applied on the short side too,\n";
    std::cout << "short wavelengths would decouple at these radii:\n\n";
    std::cout << "```\n";
    std::cout << std::left << std::setw(24) << "Band"
              << std::right << std::setw(10) << "R_actual"
              << std::setw(10) << "R_long"
              << std::setw(10) << "ratio"
              << "\n";
    std::cout << std::string(54, '-') << "\n";
    for (auto& b : bands) {
        if (b.lambda_m >= lambda_0) continue;
        double actual_dR = b.R_ratio - 1.0;
        if (actual_dR < 0.0001) continue;
        double ratio_from_min = lambda_0 / b.lambda_m;
        double pred_dR_long = A_long * std::pow(ratio_from_min, p_long);
        double pred_R_long = 1.0 + pred_dR_long;

        std::cout << std::left << std::setw(24) << b.name
                  << std::right << std::fixed << std::setprecision(4)
                  << std::setw(10) << b.R_ratio
                  << std::setw(10) << pred_R_long
                  << std::setw(10) << pred_R_long / b.R_ratio
                  << "\n";
    }
    std::cout << "```\n\n";

    std::cout << "### C. Exponent ratio\n\n";
    std::cout << "```\n";
    std::cout << "Short exponent: " << std::fixed << std::setprecision(4) << p_short << "\n";
    std::cout << "Long exponent:  " << std::fixed << std::setprecision(4) << p_long << "\n";
    std::cout << "Sum:            " << std::fixed << std::setprecision(4) << p_short + p_long << "\n";
    std::cout << "Product:        " << std::fixed << std::setprecision(4) << p_short * p_long << "\n";
    std::cout << "Ratio (s/l):    " << std::fixed << std::setprecision(4) << p_short / p_long << "\n";
    std::cout << "Ratio (l/s):    " << std::fixed << std::setprecision(4) << p_long / p_short << "\n\n";
    double p_sum = p_short + p_long;
    double p_ratio = p_short / p_long;
    std::cout << "Sum ~ " << std::fixed << std::setprecision(2) << p_sum
              << " (is this 2?  deviation = " << std::showpos << (p_sum - 2.0) / 2.0 * 100 << "%)" << std::noshowpos << "\n";
    std::cout << "Ratio ~ " << std::fixed << std::setprecision(2) << p_ratio
              << " (is this 5/3? deviation = " << std::showpos << (p_ratio - 5.0/3.0) / (5.0/3.0) * 100 << "%)" << std::noshowpos << "\n";
    std::cout << "```\n\n";

    // ===================================================================
    // QUESTION 2: Recombination at the Clearing
    // ===================================================================
    std::cout << "## 2. lambda_0 vs Recombination at 3000 K\n\n";

    double T_recomb = 3000.0;  // K
    double kT_recomb = kB * T_recomb;  // eV
    double lambda_wien = 2.8977719e-3 / T_recomb;  // Wien peak wavelength
    double E_wien = h_eV * c_mps / lambda_wien;    // eV at Wien peak
    double ratio_E = E_0 / kT_recomb;

    std::cout << "```\n";
    std::cout << "Spation natural wavelength:\n";
    std::cout << "  lambda_0 = 1.600 um\n";
    std::cout << "  E_0      = " << std::fixed << std::setprecision(4) << E_0 << " eV\n";
    std::cout << "  f_0      = " << std::scientific << std::setprecision(4) << c_mps / lambda_0 << " Hz\n\n";

    std::cout << "Recombination at T = " << (int)T_recomb << " K:\n";
    std::cout << "  kT       = " << std::fixed << std::setprecision(4) << kT_recomb << " eV\n";
    std::cout << "  Wien peak: lambda_Wien = " << std::fixed << std::setprecision(3) << lambda_wien * 1e6 << " um\n";
    std::cout << "  Wien peak: E_Wien      = " << std::fixed << std::setprecision(4) << E_wien << " eV\n\n";

    std::cout << "RATIOS:\n";
    std::cout << "  E_0 / kT            = " << std::fixed << std::setprecision(6) << ratio_E << "\n";
    std::cout << "  E_0 / (3kT)         = " << std::fixed << std::setprecision(6) << E_0 / (3.0 * kT_recomb) << "\n";
    std::cout << "  lambda_Wien / lambda_0 = " << std::fixed << std::setprecision(6) << lambda_wien / lambda_0 << "\n";
    std::cout << "  E_0 / E_Wien        = " << std::fixed << std::setprecision(6) << E_0 / E_wien << "\n\n";

    // What temperature gives E = E_0 exactly?
    double T_exact_1kT = E_0 / kB;
    double T_exact_3kT = E_0 / (3.0 * kB);
    std::cout << "Temperature where kT = E_0:  T = " << std::fixed << std::setprecision(0) << T_exact_1kT << " K\n";
    std::cout << "Temperature where 3kT = E_0: T = " << std::fixed << std::setprecision(0) << T_exact_3kT << " K\n\n";

    // Wien displacement for lambda_0
    double T_wien_match = 2.8977719e-3 / lambda_0;
    std::cout << "Temperature where Wien peak = lambda_0: T = " << std::fixed << std::setprecision(0) << T_wien_match << " K\n";
    std::cout << "```\n\n";

    std::cout << "### Interpretation\n\n";
    std::cout << "```\n";
    std::cout << "E_0 / kT = " << std::fixed << std::setprecision(2) << ratio_E << "\n\n";
    std::cout << "The spation's natural wavelength has energy = "
              << std::fixed << std::setprecision(1) << ratio_E << " kT\n";
    std::cout << "at the recombination temperature.\n\n";

    if (std::abs(ratio_E - 3.0) < 0.1) {
        std::cout << "E_0 = 3kT at 3000K to within "
                  << std::fixed << std::setprecision(1) << std::abs(ratio_E - 3.0)/3.0*100 << "%\n\n";
        std::cout << "3kT = total thermal energy per particle in 3 dimensions\n";
        std::cout << "    = kinetic + potential per degree of freedom * 3\n\n";
        std::cout << "The spation's natural wavelength carries the TOTAL\n";
        std::cout << "thermal energy of one particle at the Clearing.\n";
    }

    // Planck spectral radiance at lambda_0 for T = 3000K
    double x = E_0 / kT_recomb;  // hf/kT
    double planck_frac = (std::exp(x) - 1.0);
    std::cout << "\nAt T=3000K, the Planck occupation number at lambda_0:\n";
    std::cout << "  n(lambda_0) = 1/(exp(hf/kT) - 1) = 1/(exp("
              << std::fixed << std::setprecision(2) << x << ") - 1) = "
              << std::fixed << std::setprecision(6) << 1.0/planck_frac << "\n";
    std::cout << "```\n\n";

    // ===================================================================
    // QUESTION 3: The 10,007 seconds
    // ===================================================================
    std::cout << "## 3. The 10,007 Seconds and the Spation\n\n";

    std::cout << "```\n";
    std::cout << "T_surface = 2*pi*R_sun / v_surface = " << std::fixed << std::setprecision(1) << T_surf << " s\n";
    std::cout << "          = (2*pi*R_sun/c) * k = " << std::setprecision(2)
              << 2.0*M_PI*R_sun/c_mps << " s * " << std::setprecision(2) << k_sun
              << " = " << std::setprecision(1) << T_surf << " s\n\n";

    double d_Tsurf = T_surf * c_mps;  // distance light travels
    std::cout << "Distance light travels in T_surface:\n";
    std::cout << "  d = c * T = " << std::scientific << std::setprecision(4) << d_Tsurf << " m\n";
    std::cout << "  d / R_sun = " << std::fixed << std::setprecision(2) << d_Tsurf / R_sun << "\n";
    std::cout << "  d / (2*pi*R_sun) = " << std::fixed << std::setprecision(2) << d_Tsurf / (2.0*M_PI*R_sun) << " = k\n";
    std::cout << "  d in AU = " << std::fixed << std::setprecision(2) << d_Tsurf / 1.496e11 << "\n\n";

    // Number of lambda_0 in the distance
    double N_lambda = d_Tsurf / lambda_0;
    std::cout << "Number of lambda_0 wavelengths in d:\n";
    std::cout << "  N = d / lambda_0 = " << std::scientific << std::setprecision(6) << N_lambda << "\n\n";

    // Number of lambda_0 in one circumference
    double N_circ = 2.0 * M_PI * R_sun / lambda_0;
    std::cout << "Number of lambda_0 in one circumference:\n";
    std::cout << "  N_circ = 2*pi*R_sun / lambda_0 = " << std::scientific << std::setprecision(6) << N_circ << "\n";
    std::cout << "  N / N_circ = " << std::fixed << std::setprecision(2) << N_lambda / N_circ << " = k\n\n";

    // T_surface in units of lambda_0 period
    double T_lambda0 = lambda_0 / c_mps;
    std::cout << "T_surface / T_lambda0 = " << std::scientific << std::setprecision(6) << T_surf / T_lambda0 << "\n";
    std::cout << "  = N (same number — obvious: T_surf = N * T_lambda0)\n\n";

    // The DEEPER connection: T_surface and the decoupling profile
    std::cout << "THE CONNECTION TO DECOUPLING:\n\n";

    // At each decoupling radius R_d, the orbital period is T(R_d) = T_surf * (R_d/R_sun)^(3/2) / (R_d/R_sun)^(1/2)
    // v(r) = (c/k)*sqrt(R/r), so T(r) = 2*pi*r/v(r) = 2*pi*r*k/(c*sqrt(R/r)) = 2*pi*k*r^(3/2)/(c*R^(1/2))
    // T(R_sun) = 2*pi*k*R_sun/c = T_surface
    // T(r) = T_surface * (r/R_sun)^(3/2)

    std::cout << "v(r) = (c/k)*sqrt(R_sun/r)\n";
    std::cout << "T_orbital(r) = 2*pi*r / v(r) = T_surface * (r/R_sun)^(3/2)\n\n";

    std::cout << "For each decoupling radius:\n\n";
    std::cout << std::left << std::setw(24) << "Band"
              << std::right << std::setw(10) << "R/R_sun"
              << std::setw(14) << "T_orb (s)"
              << std::setw(14) << "T_orb/T_surf"
              << std::setw(14) << "N_lambda_0"
              << "\n";
    std::cout << std::string(76, '-') << "\n";

    for (auto& b : bands) {
        double r_ratio = b.R_ratio;
        double T_orb = T_surf * std::pow(r_ratio, 1.5);
        double N_lam = T_orb * c_mps / b.lambda_m;  // number of THIS wavelength in orbital distance

        std::cout << std::left << std::setw(24) << b.name
                  << std::right << std::fixed << std::setprecision(4) << std::setw(10) << r_ratio
                  << std::scientific << std::setprecision(4) << std::setw(14) << T_orb
                  << std::fixed << std::setprecision(4) << std::setw(14) << T_orb / T_surf
                  << std::scientific << std::setprecision(4) << std::setw(14) << N_lam
                  << "\n";
    }
    std::cout << "\n";
    std::cout << "N_lambda_0 = how many of THIS wavelength fit in the\n";
    std::cout << "distance light travels during one LOCAL orbital period.\n";
    std::cout << "This is the 'coherence count' — how many oscillations\n";
    std::cout << "the photon makes per orbital cycle at its decoupling radius.\n";
    std::cout << "```\n\n";

    // Key insight: what if the decoupling condition IS the coherence count?
    std::cout << "### The coherence count hypothesis\n\n";
    std::cout << "```\n";
    std::cout << "At the surface (lambda_0, R = 0.998 R_sun):\n";
    double T_orb_min = T_surf * std::pow(0.998, 1.5);
    double N_at_min = T_orb_min * c_mps / lambda_0;
    std::cout << "  T_orb = " << std::scientific << std::setprecision(4) << T_orb_min << " s\n";
    std::cout << "  N_lambda_0 = " << std::scientific << std::setprecision(6) << N_at_min << "\n\n";

    std::cout << "At R = 1.3 R_sun:\n";
    // Short side: lambda = 5nm
    double T_orb_13 = T_surf * std::pow(1.3, 1.5);
    double N_5nm = T_orb_13 * c_mps / 5.0e-9;
    double N_6cm = T_orb_13 * c_mps / 6.0e-2;
    std::cout << "  T_orb = " << std::scientific << std::setprecision(4) << T_orb_13 << " s\n";
    std::cout << "  N(5nm)  = " << std::scientific << std::setprecision(6) << N_5nm << "\n";
    std::cout << "  N(6cm)  = " << std::scientific << std::setprecision(6) << N_6cm << "\n";
    std::cout << "  N(5nm)/N(6cm) = " << std::scientific << std::setprecision(4) << N_5nm/N_6cm << "\n";
    std::cout << "  = 6cm/5nm = " << std::scientific << std::setprecision(4) << 6.0e-2/5.0e-9 << "\n";
    std::cout << "  These are the SAME ratio — the coherence count\n";
    std::cout << "  separates by wavelength ratio, nothing else.\n\n";

    std::cout << "What is constant across the decoupling curve?\n";
    std::cout << "N_lambda * lambda = c * T_orb(R) = c * T_surf * (R/R_sun)^(3/2)\n";
    std::cout << "This is just the orbital circumference at each R.\n";
    std::cout << "The product N*lambda = const at each R is trivially the distance.\n\n";

    std::cout << "The NON-trivial question: why does lambda_d decouple at R_d?\n";
    std::cout << "The power law dR = A * |log(lambda/lambda_0)|^p tells us\n";
    std::cout << "the PRESSURE coupling. The 3/4 exponent on the long side\n";
    std::cout << "and the 5/4 exponent on the short side encode the spation\n";
    std::cout << "geometry in each direction from its natural frequency.\n";
    std::cout << "```\n";

    return 0;
}
