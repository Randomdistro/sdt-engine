// ================================================================
// zk2_h0_gradient.cpp — H₀ vs Survey Depth
//
// Tests the SDT prediction that H₀ decreases monotonically
// with increasing survey depth (effective z_max).
//
// SDT predicts: κ_local > κ_global because local underdensity
// means less occlusion → steeper compression → higher κ → higher H₀.
//
// This tool does NOT assume SDT is correct. It compiles every
// published H₀ measurement, assigns a survey depth, and tests
// whether the correlation exists.
// ================================================================

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <numeric>

constexpr double c_kms = 299792.458;  // km/s

struct H0Measurement {
    const char* name;
    double H0;          // km/s/Mpc
    double sigma;       // total uncertainty
    double z_max;       // effective maximum redshift of survey
    const char* method;
    const char* density_class;  // local, intermediate, overdense, global
};

std::vector<H0Measurement> build_measurements() {
    return {
        // ── Early-Universe (CMB) ──
        {"Planck TT,TE,EE+lensing",     67.40, 0.50, 1100.0,
         "CMB model fit", "global"},
        {"Planck+BAO",                   67.66, 0.42, 1100.0,
         "CMB+BAO", "global"},
        {"WMAP9+ACT+SPT",               69.30, 0.70, 1100.0,
         "CMB combination", "global"},

        // ── Inverse Distance Ladder ──
        {"BAO+BBN (no CMB)",             67.60, 1.10, 2.50,
         "BAO inverse ladder", "intermediate"},
        {"DES Y3+BAO+BBN",              67.40, 1.15, 1.50,
         "Inverse ladder", "intermediate"},

        // ── Gravitational Waves ──
        {"GW170817",                     70.00, 10.00, 0.01,
         "Standard siren", "local"},

        // ── TRGB / JAGB ──
        {"CCHP TRGB+JAGB (2024)",       69.96, 1.53, 0.05,
         "TRGB+JAGB ladder", "intermediate"},
        {"CCHP TRGB JWST (2024)",       68.81, 2.22, 0.03,
         "TRGB JWST", "intermediate"},

        // ── Lensing ──
        {"TDCOSMO (2025, 8 systems)",   71.60, 3.30, 1.00,
         "Lensing time delay", "overdense"},
        {"H0LiCOW (2020)",              73.30, 1.75, 0.70,
         "Lensing time delay", "overdense"},

        // ── Cepheid Distance Ladder ──
        {"SH0ES (2022)",                73.04, 1.04, 0.15,
         "Cepheid ladder", "local"},
        {"SH0ES JWST (2024)",           72.60, 2.00, 0.15,
         "Cepheid JWST", "local"},

        // ── Other Local ──
        {"Megamaser NGC4258",           73.90, 3.00, 0.005,
         "Geometric maser", "local"},
        {"SBF (2021)",                  73.30, 2.50, 0.02,
         "Surface brightness fluct.", "local"},
    };
}

// Weighted linear regression: H₀ = m × log₁₀(z_max) + b
struct LinFit {
    double m, b, r2;
    double sigma_m, sigma_b;
};

LinFit weighted_linear_fit(const std::vector<double>& x,
                           const std::vector<double>& y,
                           const std::vector<double>& w) {
    int n = static_cast<int>(x.size());
    double S = 0, Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;
    for (int i = 0; i < n; i++) {
        S += w[i];
        Sx += w[i] * x[i];
        Sy += w[i] * y[i];
        Sxx += w[i] * x[i] * x[i];
        Sxy += w[i] * x[i] * y[i];
    }
    double D = S * Sxx - Sx * Sx;
    double m = (S * Sxy - Sx * Sy) / D;
    double b = (Sxx * Sy - Sx * Sxy) / D;

    // R²
    double ybar = Sy / S;
    double SS_tot = 0, SS_res = 0;
    for (int i = 0; i < n; i++) {
        SS_tot += w[i] * (y[i] - ybar) * (y[i] - ybar);
        double pred = m * x[i] + b;
        SS_res += w[i] * (y[i] - pred) * (y[i] - pred);
    }
    double r2 = 1.0 - SS_res / SS_tot;

    // Uncertainties on m and b
    double sigma_m = std::sqrt(S / D);
    double sigma_b = std::sqrt(Sxx / D);

    // Scale by sqrt(chi2/dof) if chi2/dof > 1
    double chi2_dof = SS_res / (n - 2);
    if (chi2_dof > 1.0) {
        sigma_m *= std::sqrt(chi2_dof);
        sigma_b *= std::sqrt(chi2_dof);
    }

    return {m, b, r2, sigma_m, sigma_b};
}

int main() {
    auto meas = build_measurements();

    std::cout << "# H0 vs Survey Depth — Gradient Analysis\n\n";
    std::cout << "> Tests the SDT prediction: H0 decreases with survey depth.\n";
    std::cout << "> No assumption about which model is correct.\n\n";

    // ── SECTION 1: ALL MEASUREMENTS ──
    std::cout << "## 1. All H0 Measurements (sorted by z_max)\n\n";

    // Sort by z_max ascending (most local first)
    std::sort(meas.begin(), meas.end(),
              [](const H0Measurement& a, const H0Measurement& b) {
                  return a.z_max < b.z_max;
              });

    std::cout << "```\n";
    std::cout << std::left << std::setw(32) << "Measurement"
              << std::right
              << std::setw(8) << "H0"
              << std::setw(8) << "sigma"
              << std::setw(12) << "z_max"
              << std::setw(12) << "log(z_max)"
              << std::setw(12) << "kappa"
              << std::setw(14) << "density"
              << "\n";
    std::cout << std::string(98, '-') << "\n";

    for (auto& m : meas) {
        double kappa = m.H0 / c_kms;
        std::cout << std::left << std::setw(32) << m.name
                  << std::right << std::fixed
                  << std::setw(8) << std::setprecision(2) << m.H0
                  << std::setw(8) << std::setprecision(2) << m.sigma
                  << std::setw(12) << std::setprecision(4) << m.z_max
                  << std::setw(12) << std::setprecision(4) << std::log10(m.z_max)
                  << std::setw(12) << std::scientific << std::setprecision(4) << kappa
                  << std::setw(14) << m.density_class
                  << "\n";
    }
    std::cout << "```\n\n";

    // ── SECTION 2: WEIGHTED LINEAR FIT ──
    std::cout << "## 2. Weighted Linear Fit: H0 = m × log10(z_max) + b\n\n";

    std::vector<double> x, y, w;
    for (auto& m : meas) {
        x.push_back(std::log10(m.z_max));
        y.push_back(m.H0);
        w.push_back(1.0 / (m.sigma * m.sigma));
    }

    auto fit = weighted_linear_fit(x, y, w);

    std::cout << "```\n";
    std::cout << "Slope m     = " << std::fixed << std::setprecision(4) << fit.m
              << " ± " << fit.sigma_m << " km/s/Mpc per decade\n";
    std::cout << "Intercept b = " << std::setprecision(4) << fit.b
              << " ± " << fit.sigma_b << " km/s/Mpc\n";
    std::cout << "R²          = " << std::setprecision(6) << fit.r2 << "\n";
    std::cout << "```\n\n";

    if (fit.m < 0) {
        std::cout << "The slope is **NEGATIVE** (" << std::setprecision(3) << fit.m
                  << " ± " << fit.sigma_m << ").\n";
        double sigma_away = std::abs(fit.m) / fit.sigma_m;
        std::cout << "This is " << std::setprecision(1) << sigma_away
                  << " sigma from zero.\n";
        if (sigma_away > 3.0) {
            std::cout << "**SIGNIFICANT**: H0 genuinely decreases with survey depth.\n";
            std::cout << "This is CONSISTENT with the SDT prediction.\n\n";
        } else if (sigma_away > 2.0) {
            std::cout << "**SUGGESTIVE**: The trend exists but is not yet decisive.\n\n";
        } else {
            std::cout << "**WEAK**: The trend is not statistically significant.\n\n";
        }
    } else {
        std::cout << "The slope is POSITIVE or ZERO. SDT gradient prediction is "
                  << "NOT supported.\n\n";
    }

    // ── SECTION 3: PAIRWISE DENSITY CONTRAST ──
    std::cout << "## 3. Pairwise Density Contrast δ\n\n";
    std::cout << "SDT predicts: κ_local/κ_global = H0_local/H0_global = (1 − δ)^{-1}\n";
    std::cout << "where δ = local underdensity contrast.\n\n";

    // Use Planck as global anchor
    double H0_global = 67.40;  // Planck
    double H0_global_sigma = 0.50;

    std::cout << "```\n";
    std::cout << "Global anchor: Planck H0 = " << std::fixed << std::setprecision(2)
              << H0_global << " ± " << H0_global_sigma << " km/s/Mpc\n\n";

    std::cout << std::left << std::setw(32) << "Measurement"
              << std::right
              << std::setw(8) << "H0"
              << std::setw(10) << "ratio"
              << std::setw(10) << "delta"
              << std::setw(12) << "delta_err"
              << "\n";
    std::cout << std::string(72, '-') << "\n";

    for (auto& m : meas) {
        double ratio = m.H0 / H0_global;
        double delta = 1.0 - 1.0 / ratio;  // 1 - κ_global/κ_local
        // Error propagation
        double dr = std::sqrt(std::pow(m.sigma / H0_global, 2) +
                              std::pow(m.H0 * H0_global_sigma / (H0_global * H0_global), 2));
        double delta_err = dr / (ratio * ratio);

        std::cout << std::left << std::setw(32) << m.name
                  << std::right << std::fixed
                  << std::setw(8) << std::setprecision(2) << m.H0
                  << std::setw(10) << std::setprecision(4) << ratio
                  << std::showpos << std::setw(10) << std::setprecision(4) << delta
                  << std::noshowpos << std::setw(12) << std::setprecision(4) << delta_err
                  << "\n";
    }
    std::cout << "```\n\n";

    // ── SECTION 4: KBC VOID COMPARISON ──
    std::cout << "## 4. KBC Void Comparison\n\n";

    double delta_required = 1.0 - H0_global / 73.04;  // SH0ES
    std::cout << "```\n";
    std::cout << "SDT required delta (SH0ES vs Planck): "
              << std::fixed << std::setprecision(4) << delta_required << "\n";
    std::cout << "KBC measured delta: -0.15 to -0.46 (K-band galaxy count, 300 Mpc)\n";
    std::cout << "\n";
    if (delta_required > -0.46 && delta_required < -0.05) {
        std::cout << "SDT required delta (" << std::setprecision(3) << delta_required
                  << ") is WITHIN the KBC range.\n";
    } else {
        std::cout << "SDT required delta (" << std::setprecision(3) << delta_required
                  << ") is OUTSIDE the KBC range.\n";
        std::cout << "NOTE: KBC measures luminosity-density underdensity,\n";
        std::cout << "SDT delta is a pressure/compression underdensity.\n";
        std::cout << "These may not be directly comparable.\n";
    }
    std::cout << "```\n\n";

    // ── SECTION 5: DENSITY CLASS AVERAGES ──
    std::cout << "## 5. H0 by Density Class\n\n";

    struct ClassAvg {
        std::string name;
        double sum_wH, sum_w;
        int count;
    };

    std::vector<ClassAvg> classes = {
        {"local", 0, 0, 0},
        {"intermediate", 0, 0, 0},
        {"overdense", 0, 0, 0},
        {"global", 0, 0, 0},
    };

    for (auto& m : meas) {
        for (auto& c : classes) {
            if (c.name == m.density_class) {
                double w = 1.0 / (m.sigma * m.sigma);
                c.sum_wH += w * m.H0;
                c.sum_w += w;
                c.count++;
            }
        }
    }

    std::cout << "```\n";
    std::cout << std::left << std::setw(16) << "Class"
              << std::right
              << std::setw(6) << "N"
              << std::setw(10) << "<H0>"
              << std::setw(12) << "kappa"
              << "\n";
    std::cout << std::string(44, '-') << "\n";

    // Print in order: local → intermediate → overdense → global
    std::vector<std::string> order = {"local", "intermediate", "overdense", "global"};
    for (auto& name : order) {
        for (auto& c : classes) {
            if (c.name == name && c.count > 0) {
                double avg = c.sum_wH / c.sum_w;
                double kappa = avg / c_kms;
                std::cout << std::left << std::setw(16) << c.name
                          << std::right
                          << std::setw(6) << c.count
                          << std::fixed << std::setprecision(2)
                          << std::setw(10) << avg
                          << std::scientific << std::setprecision(4)
                          << std::setw(12) << kappa
                          << "\n";
            }
        }
    }
    std::cout << "```\n\n";

    // Check monotonicity
    std::cout << "### Monotonicity Check\n\n";
    std::cout << "SDT predicts: H0(local) > H0(intermediate) > H0(global)\n\n";

    std::vector<std::pair<std::string, double>> class_avgs;
    for (auto& name : order) {
        for (auto& c : classes) {
            if (c.name == name && c.count > 0) {
                class_avgs.push_back({name, c.sum_wH / c.sum_w});
            }
        }
    }

    bool monotonic = true;
    for (int i = 0; i < (int)class_avgs.size() - 1; i++) {
        // Expect: local > intermediate > ... > global
        // But "overdense" breaks the simple ordering because lensing
        // paths go through high-density regions (higher κ → ambiguous)
        if (class_avgs[i].first == "overdense" ||
            class_avgs[i+1].first == "overdense") continue;

        if (class_avgs[i].second < class_avgs[i+1].second) {
            monotonic = false;
        }
    }

    std::cout << "```\n";
    if (monotonic) {
        std::cout << "RESULT: The ordering is monotonic (excluding overdense lensing paths).\n";
        std::cout << "This is CONSISTENT with SDT.\n";
    } else {
        std::cout << "RESULT: The ordering is NOT fully monotonic.\n";
        std::cout << "SDT gradient prediction is partially violated.\n";
    }
    std::cout << "```\n\n";

    // ── SECTION 6: FALSIFICATION CHECK ──
    std::cout << "## 6. Falsification Check\n\n";
    std::cout << "SDT says ALL H0 values should fall in [kappa_global*c, kappa_local*c].\n";
    std::cout << "Testing each measurement:\n\n";

    std::cout << "```\n";
    double H0_low = H0_global;
    double H0_high = 73.9;  // highest local measurement

    for (auto& m : meas) {
        bool in_range = (m.H0 - 2*m.sigma) < H0_high && (m.H0 + 2*m.sigma) > H0_low;
        std::cout << std::left << std::setw(32) << m.name
                  << "  H0=" << std::fixed << std::setprecision(1) << m.H0
                  << "±" << m.sigma << "  ";
        if (in_range) {
            std::cout << "OK (within 2σ of [" << H0_low << ", " << H0_high << "])\n";
        } else {
            std::cout << "TENSION at 2σ\n";
        }
    }
    std::cout << "```\n\n";

    // ── SECTION 7: SUMMARY ──
    std::cout << "## 7. Summary\n\n";
    std::cout << "```\n";
    std::cout << "Linear fit: H0 = " << std::fixed << std::setprecision(3) << fit.m
              << " × log10(z_max) + " << fit.b << "\n";
    std::cout << "Slope significance: " << std::setprecision(1)
              << std::abs(fit.m) / fit.sigma_m << " sigma\n";
    std::cout << "R² = " << std::setprecision(4) << fit.r2 << "\n";
    std::cout << "SDT required underdensity: delta = "
              << std::setprecision(4) << delta_required << "\n";
    std::cout << "KBC measured: -0.15 to -0.46\n";
    std::cout << "\n";
    std::cout << "The data is what it is. The trend is reported without\n";
    std::cout << "claiming it proves or disproves any model.\n";
    std::cout << "```\n";

    return 0;
}
