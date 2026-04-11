#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

constexpr double c_mps  = 2.99792458e8;
constexpr double z_sun  = 2.12270e-6;
constexpr double R_sun  = 6.95700e8;
constexpr double kappa_sun = R_sun * z_sun;  // 1476.76 m — constant for the body

struct Band {
    std::string name;
    double lambda_m;
    double R_ratio;     // R/R_sun where this wavelength decouples
};

// Linear regression: y = a + b*x, returns {a, b, r_squared}
struct LinFit { double a; double b; double r2; };
LinFit linreg(const std::vector<double>& x, const std::vector<double>& y) {
    int n = (int)x.size();
    double sx = 0, sy = 0, sxy = 0, sx2 = 0, sy2 = 0;
    for (int i = 0; i < n; i++) {
        sx += x[i]; sy += y[i]; sxy += x[i]*y[i];
        sx2 += x[i]*x[i]; sy2 += y[i]*y[i];
    }
    double b = (n*sxy - sx*sy) / (n*sx2 - sx*sx);
    double a = (sy - b*sx) / n;
    double ss_res = 0, ss_tot = 0;
    double y_mean = sy / n;
    for (int i = 0; i < n; i++) {
        double pred = a + b*x[i];
        ss_res += (y[i] - pred)*(y[i] - pred);
        ss_tot += (y[i] - y_mean)*(y[i] - y_mean);
    }
    return {a, b, 1.0 - ss_res/ss_tot};
}

int main() {
    // === DATA ===
    // Solar apparent radius at each wavelength band.
    // Sources: SDO/AIA, ALMA, VLA, LOFAR, Vernazza+ 1981 (VAL-C),
    // Selhorst+ 2019 (radio), Brajsa+ 2018 (ALMA),
    // Neckel 1995 (limb darkening), Foukal+ 2004 (IR)
    std::vector<Band> bands = {
        // IR — sees deepest (opacity minimum)
        {"1.6 um (H-band)",      1.6e-6,   0.9980},
        {"2.2 um (K-band)",      2.2e-6,   0.9990},
        {"4.7 um (M-band)",      4.7e-6,   0.9995},
        // Visible — photosphere
        {"0.85 um (z-band)",     8.5e-7,   0.9998},
        {"0.66 um (R-band)",     6.6e-7,   1.0000},
        {"0.55 um (V-band)",     5.5e-7,   1.0000},
        {"0.45 um (B-band)",     4.5e-7,   1.0005},
        {"0.36 um (U-band)",     3.6e-7,   1.0008},
        // UV
        {"0.28 um (Mg II k)",    2.8e-7,   1.0020},
        {"0.16 um (C IV)",       1.6e-7,   1.0030},
        {"0.12 um (Ly-alpha)",   1.216e-7, 1.005},
        // EUV
        {"30.4 nm (He II)",      3.04e-8,  1.050},
        {"19.5 nm (Fe XII)",     1.95e-8,  1.080},
        {"17.1 nm (Fe IX)",      1.71e-8,  1.100},
        {"9.4 nm  (Fe XVIII)",   9.4e-9,   1.200},
        // X-ray
        {"5.0 nm  (soft X)",     5.0e-9,   1.300},
        {"1.0 nm  (hard X)",     1.0e-9,   1.500},
        // Submm/mm (ALMA)
        {"0.35 mm (ALMA B10)",   3.5e-4,   1.005},
        {"0.85 mm (ALMA B7)",    8.5e-4,   1.007},
        {"1.3 mm  (ALMA B6)",    1.3e-3,   1.010},
        {"3.0 mm  (ALMA B3)",    3.0e-3,   1.015},
        // Radio
        {"2.0 cm",               2.0e-2,   1.15},
        {"6.0 cm",               6.0e-2,   1.30},
        {"20 cm",                2.0e-1,   1.70},
        {"50 cm",                5.0e-1,   2.20},
        {"1.0 m",                1.0,      3.00},
        {"2.0 m",                2.0,      3.80},
        {"3.0 m",                3.0,      4.50},
        {"5.0 m",                5.0,      6.00},
        {"10 m",                 10.0,     10.0},
    };

    // Sort by wavelength
    std::sort(bands.begin(), bands.end(),
              [](const Band& a, const Band& b){ return a.lambda_m < b.lambda_m; });

    // === FIND THE MINIMUM ===
    double min_R = 1e10;
    double lambda_min = 0;
    for (auto& b : bands) {
        if (b.R_ratio < min_R) {
            min_R = b.R_ratio;
            lambda_min = b.lambda_m;
        }
    }

    // === OUTPUT ===
    std::cout << "# Spation Geometry from Solar Multi-Wavelength Radii\n\n";
    std::cout << "> Full mathematical analysis of the wavelength-dependent\n";
    std::cout << "> solar radius as a map of spation compression.\n\n";
    std::cout << "> Anchor: z_sun = " << z_sun << ", R_sun = " << R_sun << " m\n";
    std::cout << "> kappa_sun = R*z = " << std::fixed << std::setprecision(2) << kappa_sun << " m (invariant)\n\n";
    std::cout << "---\n\n";

    // === SECTION 1: RAW DATA ===
    std::cout << "## 1. Decoupling Radii by Wavelength\n\n";
    std::cout << "```\n";
    std::cout << std::left << std::setw(24) << "Band"
              << std::right << std::setw(12) << "lambda"
              << std::setw(10) << "R/R_sun"
              << std::setw(14) << "z(R)"
              << std::setw(10) << "k(R)"
              << std::setw(14) << "v_surf(m/s)"
              << std::setw(10) << "dR/R_sun"
              << "\n";
    std::cout << std::string(94, '-') << "\n";

    for (auto& b : bands) {
        double R_act = b.R_ratio * R_sun;
        double z_R = z_sun * R_sun / R_act;
        double k_R = 1.0 / std::sqrt(z_R);
        double v_R = c_mps / k_R;
        double dR = b.R_ratio - 1.0;

        // Format lambda
        char lbuf[32];
        if (b.lambda_m >= 1.0)         snprintf(lbuf, 32, "%.0f m", b.lambda_m);
        else if (b.lambda_m >= 1e-2)   snprintf(lbuf, 32, "%.0f cm", b.lambda_m*100);
        else if (b.lambda_m >= 1e-3)   snprintf(lbuf, 32, "%.1f mm", b.lambda_m*1e3);
        else if (b.lambda_m >= 1e-6)   snprintf(lbuf, 32, "%.2f um", b.lambda_m*1e6);
        else                           snprintf(lbuf, 32, "%.1f nm", b.lambda_m*1e9);

        std::cout << std::left << std::setw(24) << b.name
                  << std::right << std::setw(12) << lbuf
                  << std::fixed << std::setprecision(4) << std::setw(10) << b.R_ratio
                  << std::scientific << std::setprecision(4) << std::setw(14) << z_R
                  << std::fixed << std::setprecision(2) << std::setw(10) << k_R
                  << std::scientific << std::setprecision(4) << std::setw(14) << v_R
                  << std::showpos << std::fixed << std::setprecision(4) << std::setw(10) << dR
                  << std::noshowpos
                  << "\n";
    }
    std::cout << "```\n\n";

    // === SECTION 2: THE MINIMUM ===
    std::cout << "## 2. The Opacity Minimum — Spation Natural Wavelength\n\n";
    std::cout << "The minimum apparent radius occurs at:\n\n";
    std::cout << "```\n";
    std::cout << "lambda_0 = " << lambda_min*1e6 << " um\n";
    std::cout << "R/R_sun  = " << std::fixed << std::setprecision(4) << min_R << "\n";
    std::cout << "```\n\n";
    std::cout << "This is the wavelength that propagates MOST EFFICIENTLY\n";
    std::cout << "through the spation lattice. It sees deepest into the\n";
    std::cout << "pressure gradient. Both shorter AND longer wavelengths\n";
    std::cout << "decouple at larger radii.\n\n";

    double f_0 = c_mps / lambda_min;
    double T_0 = lambda_min / c_mps;
    std::cout << "```\n";
    std::cout << "f_0     = c/lambda_0 = " << std::scientific << std::setprecision(4) << f_0 << " Hz\n";
    std::cout << "T_0     = lambda_0/c = " << std::scientific << std::setprecision(4) << T_0 << " s\n";
    std::cout << "E_0     = hf_0 = " << std::scientific << std::setprecision(4) << 6.626e-34 * f_0 << " J = "
              << std::fixed << std::setprecision(4) << 6.626e-34 * f_0 / 1.602e-19 << " eV\n";
    std::cout << "kappa/lambda_0 = " << std::scientific << std::setprecision(6) << kappa_sun / lambda_min << "\n";
    std::cout << "```\n\n";

    // === SECTION 3: POWER LAW FITS ===
    std::cout << "## 3. Power Law Analysis\n\n";
    std::cout << "### Short side (lambda < lambda_0): UV/EUV/X-ray\n\n";

    // Short side: lambda < lambda_min, take log(R/R_sun - 1) vs log(lambda_0/lambda)
    std::vector<double> short_x, short_y;
    for (auto& b : bands) {
        if (b.lambda_m < lambda_min && b.R_ratio > 1.0001) {
            short_x.push_back(std::log10(lambda_min / b.lambda_m));
            short_y.push_back(std::log10(b.R_ratio - 1.0));
        }
    }

    if (short_x.size() >= 2) {
        auto sf = linreg(short_x, short_y);
        std::cout << "Fit: log10(R/R_sun - 1) = " << std::fixed << std::setprecision(4) << sf.a
                  << " + " << sf.b << " * log10(lambda_0/lambda)\n\n";
        std::cout << "```\n";
        std::cout << "Exponent (short side): " << std::fixed << std::setprecision(4) << sf.b << "\n";
        std::cout << "R-squared:             " << std::fixed << std::setprecision(6) << sf.r2 << "\n";
        std::cout << "Amplitude (10^a):      " << std::scientific << std::setprecision(4) << std::pow(10.0, sf.a) << "\n\n";
        std::cout << "=> dR/R_sun = " << std::scientific << std::setprecision(4) << std::pow(10.0, sf.a)
                  << " * (lambda_0/lambda)^" << std::fixed << std::setprecision(3) << sf.b << "\n";
        std::cout << "```\n\n";

        std::cout << "Residuals:\n```\n";
        for (int i = 0; i < (int)short_x.size(); i++) {
            double pred = sf.a + sf.b * short_x[i];
            double actual = short_y[i];
            // find matching band
            for (auto& b : bands) {
                if (b.lambda_m < lambda_min && b.R_ratio > 1.0001) {
                    double test_x = std::log10(lambda_min / b.lambda_m);
                    if (std::abs(test_x - short_x[i]) < 0.001) {
                        std::cout << std::left << std::setw(24) << b.name
                                  << "  actual=" << std::fixed << std::setprecision(4) << actual
                                  << "  pred=" << std::setprecision(4) << pred
                                  << "  diff=" << std::showpos << std::setprecision(4) << (actual-pred)
                                  << std::noshowpos << "\n";
                        break;
                    }
                }
            }
        }
        std::cout << "```\n\n";
    }

    std::cout << "### Long side (lambda > lambda_0): Radio\n\n";

    std::vector<double> long_x, long_y;
    for (auto& b : bands) {
        if (b.lambda_m > lambda_min && b.R_ratio > 1.001) {
            long_x.push_back(std::log10(b.lambda_m / lambda_min));
            long_y.push_back(std::log10(b.R_ratio - 1.0));
        }
    }

    if (long_x.size() >= 2) {
        auto lf = linreg(long_x, long_y);
        std::cout << "Fit: log10(R/R_sun - 1) = " << std::fixed << std::setprecision(4) << lf.a
                  << " + " << lf.b << " * log10(lambda/lambda_0)\n\n";
        std::cout << "```\n";
        std::cout << "Exponent (long side):  " << std::fixed << std::setprecision(4) << lf.b << "\n";
        std::cout << "R-squared:             " << std::fixed << std::setprecision(6) << lf.r2 << "\n";
        std::cout << "Amplitude (10^a):      " << std::scientific << std::setprecision(4) << std::pow(10.0, lf.a) << "\n\n";
        std::cout << "=> dR/R_sun = " << std::scientific << std::setprecision(4) << std::pow(10.0, lf.a)
                  << " * (lambda/lambda_0)^" << std::fixed << std::setprecision(3) << lf.b << "\n";
        std::cout << "```\n\n";

        std::cout << "Residuals:\n```\n";
        for (int i = 0; i < (int)long_x.size(); i++) {
            double pred = lf.a + lf.b * long_x[i];
            double actual = long_y[i];
            for (auto& b : bands) {
                if (b.lambda_m > lambda_min && b.R_ratio > 1.001) {
                    double test_x = std::log10(b.lambda_m / lambda_min);
                    if (std::abs(test_x - long_x[i]) < 0.001) {
                        std::cout << std::left << std::setw(24) << b.name
                                  << "  actual=" << std::fixed << std::setprecision(4) << actual
                                  << "  pred=" << std::setprecision(4) << pred
                                  << "  diff=" << std::showpos << std::setprecision(4) << (actual-pred)
                                  << std::noshowpos << "\n";
                        break;
                    }
                }
            }
        }
        std::cout << "```\n\n";
    }

    // === SECTION 4: DERIVED QUANTITIES ===
    std::cout << "## 4. Spation Geometry\n\n";
    std::cout << "### The natural wavelength\n\n";
    std::cout << "```\n";
    std::cout << "lambda_0 = 1.6 um = 1.6e-6 m\n\n";
    std::cout << "This is where the spation is 'transparent' — the wavelength\n";
    std::cout << "that couples LEAST to the lattice. The spation geometry\n";
    std::cout << "selects this wavelength for maximum penetration.\n\n";

    double spation_crossings = kappa_sun / lambda_min;
    std::cout << "kappa / lambda_0 = " << std::scientific << std::setprecision(6) << spation_crossings << "\n";
    std::cout << "This is the number of natural wavelengths in one kappa length.\n\n";

    double period_ratio = (2.0 * M_PI * R_sun / c_mps) / (lambda_min / c_mps);
    std::cout << "Light circumference periods / lambda_0 periods:\n";
    std::cout << "  (2*pi*R_sun/c) / (lambda_0/c) = 2*pi*R_sun/lambda_0\n";
    std::cout << "  = " << std::scientific << std::setprecision(6) << 2.0 * M_PI * R_sun / lambda_min << "\n";
    std::cout << "```\n\n";

    // === SECTION 5: PRESSURE PROFILE ===
    std::cout << "## 5. Pressure Gradient Profile\n\n";
    std::cout << "At each decoupling radius r, the displacement z(r) gives\n";
    std::cout << "the local pressure. The mapping R(lambda) therefore gives\n";
    std::cout << "the pressure at which each wavelength becomes free:\n\n";
    std::cout << "```\n";
    std::cout << std::left << std::setw(24) << "Band"
              << std::right << std::setw(12) << "R/R_sun"
              << std::setw(14) << "z(R)"
              << std::setw(14) << "z/z_sun"
              << std::setw(14) << "dz/z_sun"
              << "\n";
    std::cout << std::string(78, '-') << "\n";

    for (auto& b : bands) {
        double R_act = b.R_ratio * R_sun;
        double z_R = z_sun * R_sun / R_act;
        double z_frac = z_R / z_sun;
        double dz_frac = 1.0 - z_frac;

        std::cout << std::left << std::setw(24) << b.name
                  << std::right << std::fixed << std::setprecision(4) << std::setw(12) << b.R_ratio
                  << std::scientific << std::setprecision(4) << std::setw(14) << z_R
                  << std::fixed << std::setprecision(6) << std::setw(14) << z_frac
                  << std::showpos << std::setprecision(6) << std::setw(14) << dz_frac
                  << std::noshowpos
                  << "\n";
    }
    std::cout << "```\n\n";
    std::cout << "z/z_sun = 1/R_ratio = displacement fraction relative to photosphere.\n";
    std::cout << "Short wavelengths (X-ray) decouple at z = 0.77 z_sun (23% pressure drop).\n";
    std::cout << "Long wavelengths (10m radio) decouple at z = 0.10 z_sun (90% pressure drop).\n\n";

    // === SECTION 6: THE ASYMMETRY ===
    std::cout << "## 6. Short-vs-Long Asymmetry\n\n";
    std::cout << "The decoupling curve is NOT symmetric about lambda_0.\n\n";
    
    // Find pairs at same dR on each side
    std::cout << "### Same R/R_sun, different lambdas:\n\n";
    std::cout << "```\n";
    // Find closest matches
    double targets[] = {1.005, 1.01, 1.05, 1.10, 1.30};
    for (double t : targets) {
        // Find closest short-side
        double best_short_lam = 0, best_short_d = 1e10;
        double best_long_lam = 0, best_long_d = 1e10;
        for (auto& b : bands) {
            double d = std::abs(b.R_ratio - t);
            if (b.lambda_m < lambda_min && d < best_short_d) {
                best_short_d = d; best_short_lam = b.lambda_m;
            }
            if (b.lambda_m > lambda_min && d < best_long_d) {
                best_long_d = d; best_long_lam = b.lambda_m;
            }
        }
        if (best_short_lam > 0 && best_long_lam > 0) {
            double ratio = best_long_lam / best_short_lam;
            std::cout << "R/R_sun ~ " << std::fixed << std::setprecision(3) << t
                      << ":  short=" << std::scientific << std::setprecision(2) << best_short_lam << " m"
                      << "  long=" << std::scientific << std::setprecision(2) << best_long_lam << " m"
                      << "  ratio=" << std::scientific << std::setprecision(3) << ratio
                      << "\n";
        }
    }
    std::cout << "```\n\n";
    std::cout << "The ratio between the long-side and short-side wavelengths\n";
    std::cout << "at each R/R_sun tells us how ASYMMETRICALLY the spation\n";
    std::cout << "couples to wavelengths above vs below its natural frequency.\n\n";

    // === SECTION 7: KEY IDENTITY ===
    std::cout << "## 7. Key Identity: k * lambda_0\n\n";
    double k_sun = 1.0 / std::sqrt(z_sun);
    double k_lam0 = k_sun * lambda_min;
    std::cout << "```\n";
    std::cout << "k_sun * lambda_0 = " << std::fixed << std::setprecision(2) << k_sun
              << " * " << std::scientific << std::setprecision(2) << lambda_min
              << " = " << std::scientific << std::setprecision(6) << k_lam0 << " m\n\n";

    double v_sun = c_mps / k_sun;
    double lam_v = lambda_min * c_mps / v_sun;  // lambda scaled by c/v
    std::cout << "v_surface = c/k = " << std::fixed << std::setprecision(1) << v_sun << " m/s\n";
    std::cout << "lambda_0 * c / v_surface = lambda_0 * k = " << std::scientific << std::setprecision(6) << k_lam0 << " m\n";
    std::cout << "                                         = " << std::fixed << std::setprecision(4) << k_lam0 * 1e3 << " mm\n\n";

    std::cout << "This is the wavelength that lambda_0 BECOMES when Doppler-\n";
    std::cout << "shifted by the surface orbital velocity. It maps the\n";
    std::cout << "spation's natural wavelength into the displacement frame.\n";
    std::cout << "```\n";

    return 0;
}
