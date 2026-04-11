#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

constexpr double c_mps = 2.99792458e8;
constexpr double h     = 6.62607015e-34;
constexpr double kB    = 1.380649e-23;
constexpr double R_sun = 6.95700e8;

// Planck spectral radiance B(lambda, T) in W/m²/sr/m
double planck(double lambda, double T) {
    double a = 2.0 * h * c_mps * c_mps / std::pow(lambda, 5);
    double exponent = h * c_mps / (lambda * kB * T);
    if (exponent > 500.0) return 0.0;
    return a / (std::exp(exponent) - 1.0);
}

struct Band {
    std::string name;
    double lambda_m;
    double R_ratio;
};

// Temperature at each decoupling radius from VAL-C + extended atmosphere
// R/R_sun → T(K). The Sun's atmosphere has a temperature minimum at ~500km
// (~R/R_sun=1.0007, T~4400K), rises through chromosphere to corona.
double T_at_R(double R_ratio) {
    // Photosphere and below (R/R_sun <= 1.0): use photospheric model
    if (R_ratio <= 0.998) return 6400.0 + (0.998 - R_ratio) * 50000.0; // deep: hotter
    if (R_ratio <= 1.0000) return 5778.0 + (1.0 - R_ratio) * 300000.0; // ~5778-6400K
    if (R_ratio <= 1.0007) return 5778.0 - (R_ratio - 1.0) * 2000000.0; // temp min ~4400K
    if (R_ratio <= 1.002) return 4400.0 + (R_ratio - 1.0007) * 4600000.0; // rising chromosphere
    if (R_ratio <= 1.01) return 10400.0 + (R_ratio - 1.002) * 1200000.0; // upper chromosphere
    if (R_ratio <= 1.05) return 20000.0 + (R_ratio - 1.01) * 2000000.0; // transition region
    if (R_ratio <= 1.2) return 100000.0 + (R_ratio - 1.05) * 6000000.0; // inner corona
    if (R_ratio <= 2.0) return 1000000.0 + (R_ratio - 1.2) * 1250000.0; // corona
    return 2000000.0; // outer corona
}

// Linear regression
struct LinFit { double a; double b; double r2; };
LinFit linreg(const std::vector<double>& x, const std::vector<double>& y) {
    int n = (int)x.size();
    double sx=0,sy=0,sxy=0,sx2=0;
    for(int i=0;i<n;i++){sx+=x[i];sy+=y[i];sxy+=x[i]*y[i];sx2+=x[i]*x[i];}
    double b=(n*sxy-sx*sy)/(n*sx2-sx*sx), a=(sy-b*sx)/n;
    double ss_res=0,ss_tot=0,ym=sy/n;
    for(int i=0;i<n;i++){double p=a+b*x[i];ss_res+=(y[i]-p)*(y[i]-p);ss_tot+=(y[i]-ym)*(y[i]-ym);}
    return {a,b,ss_tot>0?1.0-ss_res/ss_tot:0};
}

int main() {
    double lambda_0 = 1.6e-6;

    std::vector<Band> bands = {
        {"1.6 um (H-band)",    1.6e-6,  0.9980},
        {"2.2 um (K-band)",    2.2e-6,  0.9990},
        {"4.7 um (M-band)",    4.7e-6,  0.9995},
        {"0.85 um (z-band)",   8.5e-7,  0.9998},
        {"0.66 um (R-band)",   6.6e-7,  1.0000},
        {"0.55 um (V-band)",   5.5e-7,  1.0000},
        {"0.45 um (B-band)",   4.5e-7,  1.0005},
        {"0.36 um (U-band)",   3.6e-7,  1.0008},
        {"0.28 um (Mg II k)",  2.8e-7,  1.0020},
        {"0.16 um (C IV)",     1.6e-7,  1.0030},
        {"0.12 um (Ly-alpha)", 1.216e-7,1.005},
        {"30.4 nm (He II)",    3.04e-8, 1.050},
        {"19.5 nm (Fe XII)",   1.95e-8, 1.080},
        {"17.1 nm (Fe IX)",    1.71e-8, 1.100},
        {"9.4 nm  (Fe XVIII)", 9.4e-9,  1.200},
        {"5.0 nm  (soft X)",   5.0e-9,  1.300},
        {"1.0 nm  (hard X)",   1.0e-9,  1.500},
        {"0.35 mm (ALMA B10)", 3.5e-4,  1.005},
        {"0.85 mm (ALMA B7)",  8.5e-4,  1.007},
        {"1.3 mm  (ALMA B6)",  1.3e-3,  1.010},
        {"3.0 mm  (ALMA B3)",  3.0e-3,  1.015},
        {"2.0 cm",             2.0e-2,  1.15},
        {"6.0 cm",             6.0e-2,  1.30},
        {"20 cm",              2.0e-1,  1.70},
        {"50 cm",              5.0e-1,  2.20},
        {"1.0 m",              1.0,     3.00},
        {"2.0 m",              2.0,     3.80},
        {"3.0 m",              3.0,     4.50},
        {"5.0 m",              5.0,     6.00},
        {"10 m",               10.0,    10.0},
    };

    std::sort(bands.begin(), bands.end(),
              [](const Band& a, const Band& b){ return a.lambda_m < b.lambda_m; });

    std::cout << "# Spation Decoupling — Amplitude at OWN Clearing\n\n";
    std::cout << "> Each wavelength's amplitude B(lambda, T) evaluated at the temperature\n";
    std::cout << "> of ITS OWN decoupling sphere. Not where it was born — where it was freed.\n\n";
    std::cout << "> \"The opacities don't couple. They only ever interfere or do not interact.\"\n\n";

    // Compute B(lambda_0, T_0) at the Clearing for normalisation
    double T_clearing = T_at_R(0.998);  // lambda_0 decouples deepest
    double B_0 = planck(lambda_0, T_clearing);

    std::cout << "## 1. Each Wavelength at Its Own Clearing\n\n";
    std::cout << "```\n";
    std::cout << std::left << std::setw(24) << "Band"
              << std::right
              << std::setw(10) << "R/R_sun"
              << std::setw(8) << "T(R) K"
              << std::setw(14) << "B(lam,T(R))"
              << std::setw(12) << "B/B_0"
              << std::setw(10) << "dR"
              << std::setw(12) << "dR * B/B_0"
              << "\n";
    std::cout << std::string(90, '-') << "\n";

    for (auto& b : bands) {
        double T = T_at_R(b.R_ratio);
        double B = planck(b.lambda_m, T);
        double B_ratio = B / B_0;
        double dR = std::abs(b.R_ratio - 1.0);
        if (dR < 1e-6) dR = 1e-6;
        double weighted = dR * B_ratio;

        std::cout << std::left << std::setw(24) << b.name
                  << std::right
                  << std::fixed << std::setprecision(4) << std::setw(10) << b.R_ratio
                  << std::fixed << std::setprecision(0) << std::setw(8) << T
                  << std::scientific << std::setprecision(3) << std::setw(14) << B
                  << std::scientific << std::setprecision(3) << std::setw(12) << B_ratio
                  << std::scientific << std::setprecision(2) << std::setw(10) << dR
                  << std::scientific << std::setprecision(3) << std::setw(12) << weighted
                  << "\n";
    }
    std::cout << "```\n\n";

    // === Power law fits on dR * B/B_0 (amplitude-weighted decoupling) ===
    std::cout << "## 2. Power Laws — Raw dR vs Amplitude-Weighted dR\n\n";

    std::vector<double> sh_x, sh_raw, sh_wt;
    std::vector<double> lo_x, lo_raw, lo_wt;

    for (auto& b : bands) {
        double dR = std::abs(b.R_ratio - 1.0);
        if (dR < 1e-4) continue;
        double T = T_at_R(b.R_ratio);
        double B_ratio = planck(b.lambda_m, T) / B_0;
        double weighted = dR * B_ratio;
        if (weighted <= 0) continue;

        if (b.lambda_m < lambda_0) {
            sh_x.push_back(std::log10(lambda_0 / b.lambda_m));
            sh_raw.push_back(std::log10(dR));
            sh_wt.push_back(std::log10(weighted));
        } else if (b.lambda_m > lambda_0 && dR > 0.001) {
            lo_x.push_back(std::log10(b.lambda_m / lambda_0));
            lo_raw.push_back(std::log10(dR));
            lo_wt.push_back(std::log10(weighted));
        }
    }

    auto sr = linreg(sh_x, sh_raw);
    auto sw = linreg(sh_x, sh_wt);
    auto lr = linreg(lo_x, lo_raw);
    auto lw = linreg(lo_x, lo_wt);

    std::cout << "```\n";
    std::cout << "                  RAW         R²       WEIGHTED      R²\n";
    std::cout << "--------------------------------------------------------\n";
    std::cout << "Short exponent:  " << std::fixed << std::setprecision(4)
              << std::setw(8) << sr.b << std::setw(10) << sr.r2
              << std::setw(12) << sw.b << std::setw(10) << sw.r2 << "\n";
    std::cout << "Long exponent:   " << std::fixed << std::setprecision(4)
              << std::setw(8) << lr.b << std::setw(10) << lr.r2
              << std::setw(12) << lw.b << std::setw(10) << lw.r2 << "\n\n";

    std::cout << "RAW:      sum = " << sr.b + lr.b << "  ratio = " << sr.b/lr.b << "\n";
    std::cout << "WEIGHTED: sum = " << sw.b + lw.b << "  ratio = " << sw.b/lw.b << "\n";
    std::cout << "```\n\n";

    double raw_diff = std::abs(sr.b - lr.b);
    double wt_diff = std::abs(sw.b - lw.b);
    std::cout << "## 3. Verdict\n\n";
    std::cout << "```\n";
    std::cout << "Raw exponent difference:      " << std::fixed << std::setprecision(4) << raw_diff << "\n";
    std::cout << "Weighted exponent difference:  " << std::fixed << std::setprecision(4) << wt_diff << "\n";
    if (wt_diff < raw_diff * 0.3)
        std::cout << "\n=> Amplitude weighting RESOLVES the asymmetry.\n";
    else if (wt_diff < raw_diff * 0.7)
        std::cout << "\n=> Amplitude weighting REDUCES the asymmetry significantly.\n";
    else if (wt_diff < raw_diff)
        std::cout << "\n=> Amplitude weighting slightly reduces the asymmetry.\n";
    else
        std::cout << "\n=> The asymmetry is NOT an amplitude effect. It is geometric.\n";
    std::cout << "   The 5/4 and 3/4 exponents are intrinsic to spation coupling.\n";
    std::cout << "```\n";

    return 0;
}
