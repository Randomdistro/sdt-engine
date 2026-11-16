// Chapter 28 — emission, absorption and linewidth: worked-example instrument.
// Pre-registration: Textbook/validation/ch28_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <complex>
#include <vector>

namespace {

constexpr double kPi = std::numbers::pi;
using cd = std::complex<double>;

double bessel(int n, double x) {
    return tb::integrate([&](double t) { return std::cos(n * t - x * std::sin(t)); }, 0.0, kPi, 48, 8) / kPi;
}

double lorentz(double x, double G) { return (G / (2.0 * kPi)) / (x * x + G * G / 4.0); }
double gauss(double x, double s) { return std::exp(-0.5 * x * x / (s * s)) / (s * std::sqrt(2.0 * kPi)); }

// Central-force route: a = -r^-2 rhat (mu = 1). Returns x(t) sampled N points over the period 2 pi.
std::vector<double> route_x(double e, int N) {
    const double ra = 1.0 + e, va = std::sqrt(2.0 / ra - 1.0);
    double x = ra, y = 0.0, vx = 0.0, vy = va;
    auto acc = [](double X, double Y, double& ax, double& ay) {
        const double r = std::hypot(X, Y), k = -1.0 / (r * r * r);
        ax = k * X;
        ay = k * Y;
    };
    std::vector<double> out;
    const double h = 2.0 * kPi / N;
    const int sub = 8;
    const double hs = h / sub;
    for (int i = 0; i < N; ++i) {
        out.push_back(x);
        for (int s = 0; s < sub; ++s) {
            double a1x, a1y, a2x, a2y, a3x, a3y, a4x, a4y;
            acc(x, y, a1x, a1y);
            acc(x + 0.5 * hs * vx, y + 0.5 * hs * vy, a2x, a2y);
            const double v2x = vx + 0.5 * hs * a1x, v2y = vy + 0.5 * hs * a1y;
            acc(x + 0.5 * hs * v2x, y + 0.5 * hs * v2y, a3x, a3y);
            const double v3x = vx + 0.5 * hs * a2x, v3y = vy + 0.5 * hs * a2y;
            acc(x + hs * v3x, y + hs * v3y, a4x, a4y);
            const double v4x = vx + hs * a3x, v4y = vy + hs * a3y;
            const double nx = x + hs / 6.0 * (vx + 2 * v2x + 2 * v3x + v4x), ny = y + hs / 6.0 * (vy + 2 * v2y + 2 * v3y + v4y);
            const double nvx = vx + hs / 6.0 * (a1x + 2 * a2x + 2 * a3x + a4x), nvy = vy + hs / 6.0 * (a1y + 2 * a2y + 2 * a3y + a4y);
            x = nx; y = ny; vx = nvx; vy = nvy;
        }
    }
    return out;
}

double harmonic(const std::vector<double>& s, int n) {
    cd acc = 0.0;
    const int N = static_cast<int>(s.size());
    for (int i = 0; i < N; ++i) acc += s[i] * std::exp(cd(0.0, -2.0 * kPi * n * i / N));
    return 2.0 * std::abs(acc) / N;
}

}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    namespace A = sdt::laws::atomic;
    tb::validate_helpers();

    tb::heading("V1 Bessel by the integral representation");
    tb::check("V1", "J0(0) = 1", bessel(0, 0.0), 1.0, 1e-8);
    tb::check("V1", "J1(0) = 0", bessel(1, 0.0) + 1.0, 1.0, 1e-8);
    tb::check("V1", "J0(2.404826) = 0", bessel(0, 2.404826) + 1.0, 1.0, 1e-6);
    tb::check("V1", "J1(1.0) = 0.4400505857", bessel(1, 1.0), 0.4400505857, 1e-8);

    tb::heading("T1 causal exponential response and its width");
    {
        double worst = 0.0;
        for (double d : {0.0, 0.3, 1.0, 3.0}) {
            const double re = tb::integrate([&](double t) { return std::exp(-0.5 * t) * std::cos(d * t); }, 0.0, 60.0, 48, 40);
            const double im = tb::integrate([&](double t) { return std::exp(-0.5 * t) * std::sin(d * t); }, 0.0, 60.0, 48, 40);
            const cd exact = 1.0 / cd(0.5, -d);
            worst = std::fmax(worst, std::abs(cd(re, im) - exact));
        }
        tb::check("T1", "numerical transform vs 1/(1/2 - i delta), worst absolute", worst, 0.0, 1e-9, false);
        auto p = [](double d) { return 1.0 / (0.25 + d * d); };
        double lo = 0.0, hi = 5.0;
        for (int i = 0; i < 200; ++i) {
            const double mid = 0.5 * (lo + hi);
            (p(mid) > 0.5 * p(0.0) ? lo : hi) = mid;
        }
        tb::check("T1", "half-maximum point of |A|^2 is delta = 1/2 (FWHM = Gamma)", 0.5 * (lo + hi), 0.5, 1e-8);
    }

    tb::heading("T2 independent broadenings");
    {
        const double R = 4000.0;
        double wl = 0.0, wg = 0.0;
        for (double x : {0.0, 1.0, 3.0}) {
            const double conv = tb::integrate([&](double y) { return lorentz(x - y, 1.0) * lorentz(y, 2.0); }, -R, R, 48, 4000);
            wl = std::fmax(wl, std::fabs(conv / lorentz(x, 3.0) - 1.0));
            const double cg = tb::integrate([&](double y) { return gauss(x - y, 1.0) * gauss(y, 2.0); }, -40.0, 40.0, 48, 40);
            wg = std::fmax(wg, std::fabs(cg / gauss(x, std::sqrt(5.0)) - 1.0));
        }
        tb::check("T2a", "Lorentzian widths add (1 + 2 = 3), worst relative", wl, 0.0, 2e-3, false);
        tb::check("T2b", "Gaussian variances add (1 + 4 = 5), worst relative", wg, 0.0, 1e-10, false);
        tb::check("T2c", "intrinsic sigma 1 through detector sigma 0.5 gives sqrt(1.25)", std::sqrt(1.0 + 0.25), std::sqrt(1.25), 1e-14);
        // Voigt FWHM, Gamma = 1, Gaussian FWHM = 1 (sigma = 1/2.3548)
        const double sg = 1.0 / (2.0 * std::sqrt(2.0 * std::log(2.0)));
        auto V = [&](double x) { return tb::integrate([&](double y) { return lorentz(x - y, 1.0) * gauss(y, sg); }, -30.0, 30.0, 48, 120); };
        // tail of the Lorentzian beyond the Gaussian window is negligible at x ~ 1
        const double half = 0.5 * V(0.0);
        double lo = 0.0, hi = 10.0;
        for (int i = 0; i < 80; ++i) {
            const double mid = 0.5 * (lo + hi);
            (V(mid) > half ? lo : hi) = mid;
        }
        const double fv = 2.0 * 0.5 * (lo + hi), approx = 0.5346 * 1.0 + std::sqrt(0.2166 * 1.0 + 1.0);
        tb::note("Voigt FWHM (numerical) = %.5f ; approximate formula = %.5f ; relative difference %.2e", fv, approx, fv / approx - 1.0);
        tb::check_true("T2d", "numerical Voigt FWHM agrees with the approximate formula within 0.5%", std::fabs(fv / approx - 1.0) < 0.005);
    }

    tb::heading("T3 harmonic content of the emission of a closed route");
    {
        const int N = 4096;
        {
            const auto s = route_x(0.0, N);
            const double h1 = harmonic(s, 1);
            tb::check("T3", "circular route: |x_2|/|x_1|", harmonic(s, 2) / h1 + 1.0, 1.0, 1e-9);
            tb::check("T3", "circular route: |x_3|/|x_1|", harmonic(s, 3) / h1 + 1.0, 1.0, 1e-9);
        }
        const double e = 0.51;
        const auto s = route_x(e, N);
        double worst = 0.0;
        for (int n = 1; n <= 3; ++n) {
            const double want = std::fabs(bessel(n - 1, n * e) - bessel(n + 1, n * e)) / n;
            worst = std::fmax(worst, std::fabs(harmonic(s, n) / want - 1.0));
        }
        tb::check("T3", "e = 0.51: |x_n| = (1/n)|J_{n-1}(ne) - J_{n+1}(ne)| for n = 1..3, worst relative", worst, 0.0, 1e-6, false);
        tb::note("e = 0.51: |x_2/x_1| = %.6f ; |x_3/x_1| = %.6f", harmonic(s, 2) / harmonic(s, 1), harmonic(s, 3) / harmonic(s, 1));
    }

    tb::heading("T4 recoil term of the event ledger (hydrogen 1 -> 2)");
    {
        const double c2 = M::c * M::c, MeV = M::MeV_to_J;
        const double dE = (A::level_energy_eV(1, 2, M::m_p) - A::level_energy_eV(1, 1, M::m_p)) * 1e-6;  // MeV
        const double Mf = (M::m_p + M::m_e) * c2 / MeV;                                              // MeV
        const double Mi = Mf + dE;
        const double Eg = dE * (1.0 - dE / (2.0 * Mi));
        const double T_exact = dE * dE / (2.0 * Mi);
        const double T_stable = Eg * Eg / (std::sqrt(Mf * Mf + Eg * Eg) + Mf);
        tb::check("T4", "stable recoil energy equals dE^2/(2 M_i c^2)", T_stable, T_exact, 1e-8);
        tb::check("T4", "E_gamma + T_recoil = dE, relative to dE", (Eg + T_stable) / dE, 1.0, 1e-14);
        tb::note("dE = %.6f eV ; recoil T = %.4e eV ; T/dE = %.3e", dE * 1e6, T_stable * 1e6, T_stable / dE);
    }

    return tb::finish();
}
