// Chapter 44 — thermal recurrence: worked-example instrument.
// Pre-registration: Textbook/validation/ch44_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/cosmology.hpp>
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <numbers>
#include <vector>

namespace {

namespace M = sdt::laws::measured;
constexpr double PI = std::numbers::pi;

// Uniform grid in ln(nu); trapezoid rule (spectrally accurate for these decaying analytic integrands).
constexpr double LN_LO = 16.118095650958319;  // ln(1e7)
constexpr double LN_HI = 36.841361487904734;  // ln(1e16)
constexpr int NG = 80000;
constexpr double DL = (LN_HI - LN_LO) / NG;

double nu_at(int i) { return std::exp(LN_LO + DL * i); }

double trap(const std::function<double(double)>& f_of_nu_times_nu) {  // integral f dnu = sum f(nu) nu dlnnu
    double s = 0.0;
    for (int i = 0; i <= NG; ++i) {
        const double w = (i == 0 || i == NG) ? 0.5 : 1.0;
        s += w * f_of_nu_times_nu(nu_at(i));
    }
    return s * DL;
}

// Native Stefan radiation constant from {hbar, c, k_B} (registration: the computed value of T1, not the stored a_rad).
const double A_NATIVE = PI * PI * std::pow(M::k_B, 4) / (15.0 * std::pow(M::hbar, 3) * std::pow(M::c, 3));

struct Comp {
    double T;  // temperature [K]
    double w;  // amplitude weight
};

// u_nu = w (8 pi h / c^3) nu^3 / (exp(h nu / k T) - 1)
double u_nu(const std::vector<Comp>& mix, double nu) {
    double s = 0.0;
    for (const auto& c : mix) {
        const double x = M::h * nu / (M::k_B * c.T);
        s += c.w * (8.0 * PI * M::h / std::pow(M::c, 3)) * nu * nu * nu / std::expm1(x);
    }
    return s;
}

double energy_density(const std::vector<Comp>& mix) { return trap([&](double nu) { return u_nu(mix, nu) * nu; }); }
double number_density(const std::vector<Comp>& mix) { return trap([&](double nu) { return u_nu(mix, nu) / (M::h * nu) * nu; }); }

// d ln-derivative sums. Peak in nu of u_nu: sum g_i (3 - x e^x/(e^x-1)) = 0, g_i = w nu^3/(e^x-1).
// Peak in lambda of u_lambda = u_nu nu^2/c: nu^5 terms, power 5.
double dpeak(const std::vector<Comp>& mix, double nu, double power) {
    double s = 0.0;
    for (const auto& c : mix) {
        const double x = M::h * nu / (M::k_B * c.T);
        const double g = c.w * std::pow(nu, power) / std::expm1(x);
        s += g * (power - x * std::exp(x) / std::expm1(x));
    }
    return s;
}

// Find the highest-frequency sign change from positive to negative of the derivative (global peak of unimodal mixtures here).
double peak_nu(const std::vector<Comp>& mix, double power) {
    // scan the log grid for the sign change, then bisect
    double best = -1.0, best_val = -1.0;
    double prev_nu = nu_at(0), prev = dpeak(mix, prev_nu, power);
    std::vector<std::pair<double, double>> brackets;
    for (int i = 1; i <= NG; i += 20) {
        const double n = nu_at(i), d = dpeak(mix, n, power);
        if (prev > 0 && d <= 0) brackets.push_back({prev_nu, n});
        prev_nu = n;
        prev = d;
    }
    for (auto br : brackets) {
        double a = br.first, b = br.second;
        for (int it = 0; it < 200; ++it) {
            const double m = std::sqrt(a * b);
            if (dpeak(mix, m, power) > 0) a = m; else b = m;
        }
        const double nu = std::sqrt(a * b);
        const double val = u_nu(mix, nu) * (power == 5.0 ? nu * nu : 1.0);
        if (val > best_val) { best_val = val; best = nu; }
    }
    return best;
}

double root_x(double power) {  // x = power (1 - e^-x)
    double a = power - 1.5, b = power + 1.0;
    auto f = [&](double x) { return x - power * (1.0 - std::exp(-x)); };
    for (int it = 0; it < 200; ++it) {
        const double m = 0.5 * (a + b);
        if (f(m) < 0) a = m; else b = m;
    }
    return 0.5 * (a + b);
}

struct Readings {
    double Tpeak, Tu, Tn, nu_peak, lambda_peak;
};

Readings read(const std::vector<Comp>& mix, double b) {
    Readings r{};
    const double nu5 = peak_nu(mix, 5.0);
    r.lambda_peak = M::c / nu5;
    r.Tpeak = b / r.lambda_peak;
    r.nu_peak = peak_nu(mix, 3.0);
    r.Tu = std::pow(energy_density(mix) / A_NATIVE, 0.25);
    const double zeta3 = 1.2020569031595942;
    const double n = number_density(mix);
    r.Tn = (M::hbar * M::c / M::k_B) * std::cbrt(n * PI * PI / (2.0 * zeta3));
    return r;
}

// Best single-Planck fit of u_nu(mixture) over (T, A): relative L2 residual (ln-nu measure) and best T.
std::pair<double, double> best_fit(const std::vector<Comp>& mix, double T_lo, double T_hi) {
    std::vector<double> f(NG + 1), nus(NG + 1);
    double ff = 0.0;
    for (int i = 0; i <= NG; ++i) { nus[i] = nu_at(i); f[i] = u_nu(mix, nus[i]) * nus[i]; ff += f[i] * f[i]; }
    auto cosine = [&](double T) {
        std::vector<Comp> one = {{T, 1.0}};
        double mf = 0.0, mm = 0.0;
        for (int i = 0; i <= NG; ++i) {
            const double m = u_nu(one, nus[i]) * nus[i];
            mf += m * f[i];
            mm += m * m;
        }
        return mf * mf / (mm * ff);
    };
    double a = std::log(T_lo), b = std::log(T_hi);
    const double gr = (std::sqrt(5.0) - 1.0) / 2.0;
    double c = b - gr * (b - a), d = a + gr * (b - a);
    double fc = cosine(std::exp(c)), fd = cosine(std::exp(d));
    for (int it = 0; it < 80; ++it) {
        if (fc > fd) { b = d; d = c; fd = fc; c = b - gr * (b - a); fc = cosine(std::exp(c)); }
        else { a = c; c = d; fc = fd; d = a + gr * (b - a); fd = cosine(std::exp(d)); }
    }
    const double Tbest = std::exp(0.5 * (a + b));
    const double cos2 = cosine(Tbest);
    return {std::sqrt(std::fmax(0.0, 1.0 - cos2)), Tbest};
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    {
        const double zeta3 = 1.2020569031595942;
        // dimensionless check on its own uniform ln x grid, ln x from ln 1e-8 to ln 100
        auto trap_x = [](const std::function<double(double)>& f) {
            const double lo = std::log(1e-8), hi = std::log(100.0);
            const int n = 40000;
            const double dl = (hi - lo) / n;
            double s = 0.0;
            for (int i = 0; i <= n; ++i) {
                const double x = std::exp(lo + dl * i);
                s += ((i == 0 || i == n) ? 0.5 : 1.0) * f(x) * x;
            }
            return s * dl;
        };
        const double i3 = trap_x([](double x) { return x * x * x / std::expm1(x); });
        const double i2 = trap_x([](double x) { return x * x / std::expm1(x); });
        tb::check("V1", "int x^3/(e^x-1) dx = pi^4/15", i3, std::pow(PI, 4) / 15.0, 1e-10);
        tb::check("V1", "int x^2/(e^x-1) dx = 2 zeta(3)", i2, 2.0 * zeta3, 1e-10);
        tb::check("V1", "root of x = 5(1-e^-x)", root_x(5.0), 4.965114231744276, 1e-10);
        tb::check("V1", "root of x = 3(1-e^-x)", root_x(3.0), 2.821439372122079, 1e-10);
    }

    const double xl = root_x(5.0), xn = root_x(3.0);

    tb::heading("T1 native constants, then the engine's stored values");
    const double b_native = M::h * M::c / (M::k_B * xl);
    const double a_native = PI * PI * std::pow(M::k_B, 4) / (15.0 * std::pow(M::hbar, 3) * std::pow(M::c, 3));
    tb::note("native: b = %.9e m K ; a = %.9e J m^-3 K^-4", b_native, a_native);
    tb::check("T1", "b = hc/(k x_lambda) = 2.897771955e-3", b_native, 2.897771955e-3, 1e-6);
    tb::check("T1", "a = pi^2 k^4/(15 hbar^3 c^3) = 7.565733e-16", a_native, 7.565733e-16, 1e-6);
    tb::note("engine: wien constant 2.898e-3 (in cosmology::wien_peak) ; a_rad = %.4e", M::a_rad);
    const double engine_b = sdt::cosmology::wien_peak(1.0);
    tb::check("T1", "engine Wien constant vs native b", engine_b, b_native, 1e-4);
    tb::check("T1", "engine a_rad vs native a", M::a_rad, a_native, 1e-5);

    tb::heading("T2 one reading, one temperature for a Planck spectrum");
    for (double T : {2.7255, 3000.0}) {
        const std::vector<Comp> p = {{T, 1.0}};
        const auto r = read(p, b_native);
        char lab[128];
        std::snprintf(lab, sizeof lab, "T = %g K: peak-wavelength reading", T);
        tb::check("T2", lab, r.Tpeak, T, 1e-8);
        std::snprintf(lab, sizeof lab, "T = %g K: energy-density reading", T);
        tb::check("T2", lab, r.Tu, T, 1e-8);
        std::snprintf(lab, sizeof lab, "T = %g K: photon-number reading", T);
        tb::check("T2", lab, r.Tn, T, 1e-8);
        std::snprintf(lab, sizeof lab, "T = %g K: lambda_peak nu_peak / c = x_nu / x_lambda", T);
        tb::check("T2", lab, r.lambda_peak * r.nu_peak / M::c, xn / xl, 1e-8);
        tb::note("T = %g K: x_nu/x_lambda = %.9f ; b/(c/nu_peak) is %.6f times T", T, xn / xl, b_native * r.nu_peak / M::c / T);
        const double T_stored = std::pow(energy_density(p) / M::a_rad, 0.25);
        tb::note("T = %g K: energy reading with the stored a_rad = %.9f (relative bias %+.3e, %+.3e K)", T, T_stored, T_stored / T - 1.0, T_stored - T);
    }

    tb::heading("T3 spectral ancestry: mixtures of Planck spectra");
    {
        const double T1 = 2.7255;
        // equal energy: component energy = a T^4 w, so w2 = (T1/T2)^4 w1
        const std::vector<Comp> mix = {{T1, 1.0}, {2.0 * T1, 1.0 / 16.0}};
        const auto r = read(mix, b_native);
        const double e1 = energy_density({mix[0]}), e2 = energy_density({mix[1]});
        tb::note("component energies: %.6e and %.6e J/m^3 (ratio %.9f)", e1, e2, e1 / e2);
        tb::check("T3", "energy reading reproduces the integrated energy", A_NATIVE * std::pow(r.Tu, 4), energy_density(mix), 1e-9);
        const double lo = std::fmin(r.Tpeak, std::fmin(r.Tu, r.Tn)), hi = std::fmax(r.Tpeak, std::fmax(r.Tu, r.Tn));
        tb::note("readings of the mixture (T1 = %.4f K): peak %.5f, energy %.5f, number %.5f K", T1, r.Tpeak, r.Tu, r.Tn);
        tb::check_true("T3", "the three readings span at least 10 per cent of the energy reading", (hi - lo) >= 0.10 * r.Tu);
        const auto fit = best_fit(mix, 0.5 * T1, 4.0 * T1);
        tb::note("best single-Planck fit: T = %.5f K, relative L2 residual %.5f", fit.second, fit.first);
        tb::check_true("T3", "best single-Planck fit residual is at least 0.02", fit.first >= 0.02);
        const double T2 = 1.01 * T1;
        const std::vector<Comp> close = {{T1, 1.0}, {T2, std::pow(T1 / T2, 4)}};
        const auto fit2 = best_fit(close, 0.5 * T1, 2.0 * T1);
        tb::note("T2/T1 = 1.01: best-fit T = %.6f K, relative residual %.3e", fit2.second, fit2.first);
        tb::check_true("T3", "for components 1 per cent apart the best-fit residual is below 1e-3", fit2.first < 1e-3);
    }

    tb::heading("T4 octaves");
    {
        const double D = 760e-9 * std::ldexp(1.0, 44);
        const double a = M::a_rad;
        double worstT = 0.0, worstU = 0.0;
        for (int n = 0; n < 10; ++n) {
            const double Tn0 = (b_native / D) * std::ldexp(1.0, n), Tn1 = (b_native / D) * std::ldexp(1.0, n + 1);
            worstT = std::fmax(worstT, std::fabs(Tn1 / Tn0 - 2.0));
            worstU = std::fmax(worstU, std::fabs(a * std::pow(Tn1, 4) / (a * std::pow(Tn0, 4)) - 16.0));
        }
        tb::check("T4", "T_W(n+1)/T_W(n) = 2 (worst absolute deviation)", worstT, 0.0, 1e-12, false);
        tb::check("T4", "u(n+1)/u(n) = 16 (worst absolute deviation)", worstU, 0.0, 1e-12, false);
        tb::check("T4", "lambda(44) = D 2^-44 = 760 nm", D * std::ldexp(1.0, -44), 760e-9, 1e-12);
        tb::check("T4", "T_W(44) = b / 760 nm", (b_native / D) * std::ldexp(1.0, 44), b_native / 760e-9, 1e-12);
        const double lam_cmb = b_native / M::T_CMB;
        tb::note("CMB Wien peak %.6e m; octaves to 760 nm: %.4f ; to 975 nm: %.4f", lam_cmb, std::log2(lam_cmb / 760e-9), std::log2(lam_cmb / 975e-9));
        const double DE = 2.0 * sdt::laws::bridge::R_Earth;
        const double nE = std::log2(DE / 760e-9);
        tb::note("D_Earth = 2 R_Earth = %.6e m ; log2(D_Earth/760 nm) = %.4f ; offset from 44 = %+.4f octave (factor %.4f in length)", DE, nE, nE - 44.0, DE / D);
        tb::check_true("T4", "the nearest integer to log2(D_Earth / 760 nm) is 44", std::lround(nE) == 44);
    }

    tb::heading("T5 engine temperature functions");
    {
        const double z = 1100.0;
        tb::check("T5", "T_at_z and z_at_T are inverses", sdt::cosmology::z_at_T(sdt::cosmology::T_at_z(z)), z, 1e-12);
        tb::check("T5", "T_at_z(1100) = T_CMB * 1101", sdt::cosmology::T_at_z(z), M::T_CMB * 1101.0, 1e-12);
        const double Te = sdt::cosmology::T_at_z(z);
        tb::note("T(1100) = %.4f K ; engine Wien peak %.6e m ; native %.6e m", Te, sdt::cosmology::wien_peak(Te), b_native / Te);
        tb::check("T5", "engine wien_peak at T(1100) vs native b/T", sdt::cosmology::wien_peak(Te), b_native / Te, 1e-4);
    }

    return tb::finish();
}
