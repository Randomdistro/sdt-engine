// Chapter 52 — thermal and radiation puzzles: worked-example instrument.
// Pre-registration: Textbook/validation/ch52_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <numbers>
#include <vector>

namespace {

namespace M = sdt::laws::measured;
constexpr double PI = std::numbers::pi;

double g_of(double q, double lam) {
    return std::exp(-lam * q) * (q * q / lam + 2.0 * q / (lam * lam) + 2.0 / (lam * lam * lam)) / (2.0 * PI);
}

// Neumaier compensated sum
struct Sum {
    double s = 0.0, c = 0.0;
    void add(double x) {
        const double t = s + x;
        if (std::fabs(s) >= std::fabs(x)) c += (s - t) + x; else c += (x - t) + s;
        s = t;
    }
    double value() const { return s + c; }
};

// Regularised per-area energy difference in units a hbar c / d^3, for plate separation d (length unit), cutoff lam
double Ediff(double d, double lam) {
    const double h = PI / d;
    Sum acc;
    const int N = static_cast<int>(60.0 / (lam * h)) + 20;
    for (int n = N; n >= 1; --n) acc.add(g_of(n * h, lam));
    acc.add(0.5 * g_of(0.0, lam));
    acc.add(-(d / PI) * 3.0 / (PI * lam * lam * lam * lam));
    return 2.0 * acc.value();
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    {
        const double lam = 1.0;
        const double I = tb::integrate([&](double q) { return g_of(q, lam); }, 0.0, 60.0, 48, 60);
        tb::check("V1", "int_0^inf g dq = 3/(pi lam^4) at lam = 1", I, 3.0 / (PI * lam * lam * lam * lam), 1e-9);
        const double B = tb::integrate([](double x) { return x < 1e-12 ? 0.0 : x * x * x / std::expm1(x); }, 0.0, 80.0, 48, 80);
        tb::check("V1", "int x^3/(e^x - 1) dx = pi^4/15", B, std::pow(PI, 4) / 15.0, 1e-10);
        // g'''(0) by a central finite difference of the exact g (lam = 1): g(q) is smooth; use step 0.05 with 5-point stencil
        const double hh = 0.05;
        auto g = [&](double q) { return g_of(q, 1.0); };
        auto d3of = [&](double s) { return (-g(-2 * s) + 2.0 * g(-s) - 2.0 * g(s) + g(2 * s)) / (2.0 * s * s * s); };
        const double d3 = (4.0 * d3of(0.5 * hh) - d3of(hh)) / 3.0;  // one Richardson step: O(h^2) -> O(h^4)
        tb::check("V1", "g'''(0) = -1/pi (central finite difference with one Richardson step)", d3, -1.0 / PI, 1e-3);
    }

    tb::heading("T1 scale-free price: regularised energy and its cutoff-free limit");
    {
        const double E0 = -PI * PI / 360.0;
        const double xs[4] = {0.08, 0.06, 0.04, 0.03};
        double Ev[4];
        for (int i = 0; i < 4; ++i) {
            Ev[i] = Ediff(1.0, xs[i]);
            tb::note("x = lambda/d = %.2f : E = %.12e ; E/E0 - 1 = %+.6e", xs[i], Ev[i], Ev[i] / E0 - 1.0);
        }
        // Lagrange extrapolation in u = x^2 to u = 0
        double ext = 0.0;
        for (int i = 0; i < 4; ++i) {
            double w = 1.0;
            for (int j = 0; j < 4; ++j) if (j != i) w *= (0.0 - xs[j] * xs[j]) / (xs[i] * xs[i] - xs[j] * xs[j]);
            ext += w * Ev[i];
        }
        tb::note("extrapolated E(0) = %.12e ; -pi^2/360 = %.12e", ext, E0);
        tb::check("T1", "extrapolated E(0) equals -pi^2/360", ext, E0, 1e-6);
        const double c1 = Ev[1] / E0 - 1.0, c3 = Ev[3] / E0 - 1.0;
        tb::note("leading correction: (E(0.06)/E0 - 1)/(E(0.03)/E0 - 1) = %.5f ; E(x)/E0 - 1 = %+.4f x^2", c1 / c3, c3 / (xs[3] * xs[3]));
        tb::check_true("T1", "the leading correction is negative", c1 < 0.0 && c3 < 0.0);
        tb::check("T1", "the leading correction scales as x^2 (ratio 4)", c1 / c3, 4.0, 2e-2);
    }

    tb::heading("T2 occupation at the present temperature");
    {
        const double a_native = PI * PI * std::pow(M::k_B, 4) / (15.0 * std::pow(M::hbar, 3) * std::pow(M::c, 3));
        const double u = a_native * std::pow(M::T_CMB, 4);
        const double Pth = u / 3.0;
        tb::note("u_CMB = %.6e J/m^3 ; u/3 = %.6e Pa", u, Pth);
        tb::check("T2", "u/3 = 1.3916e-14 Pa", Pth, 1.3916e-14, 1e-4);
        auto Pid = [&](double d) { return PI * PI * M::hbar * M::c / (240.0 * std::pow(d, 4)); };
        const double r1 = Pth / Pid(1e-6);
        tb::note("u/3 over the ideal-plate pressure at d = 1 um: %.4e", r1);
        tb::check_true("T2", "the ratio at 1 um lies in [1.0e-11, 1.1e-11]", r1 >= 1.0e-11 && r1 <= 1.1e-11);
        const double dstar = std::pow(PI * PI * M::hbar * M::c / (80.0 * u), 0.25);
        tb::note("d_* where the two pressures are equal: %.5e m", dstar);
        tb::check_true("T2", "d_* lies in [4e-4, 7e-4] m", dstar >= 4e-4 && dstar <= 7e-4);
        tb::check("T2", "the ideal-plate pressure equals u/3 at d_*", Pid(dstar), Pth, 1e-12);
        const double u2 = a_native * std::pow(M::T_CMB, 4);
        tb::check("T2", "the thermal pressure is a function of T only (identical for any d)", u2 / 3.0, Pth, 1e-15);
    }

    tb::heading("T3 a finite transparency cutoff changes the scaling");
    {
        const double lam = 1.0;
        auto neff = [&](double d) {
            const double e = 1e-3;
            return -(std::log(std::fabs(Ediff(d * (1 + e), lam))) - std::log(std::fabs(Ediff(d * (1 - e), lam)))) / (std::log(1 + e) - std::log(1 - e));
        };
        const double n100 = neff(100.0);
        tb::note("local exponent at d/lambda = 100: %.6f", n100);
        tb::check_true("T3", "the local exponent at d/lambda = 100 lies in [2.99, 3.01]", n100 >= 2.99 && n100 <= 3.01);
        const double Eq = Ediff(0.1, lam), Ec = Ediff(100.0, lam);
        tb::note("E(d/lambda = 0.1) = %+.6e ; E(100) = %+.6e", Eq, Ec);
        tb::check_true("T3", "Delta E is positive at d/lambda = 0.1", Eq > 0.0);
        double lo = 0.1, hi = 100.0;
        for (int it = 0; it < 100; ++it) {
            const double mid = std::sqrt(lo * hi);
            if (Ediff(mid, lam) > 0.0) lo = mid; else hi = mid;
        }
        tb::note("sign change of Delta E at d/lambda = %.5f", std::sqrt(lo * hi));
        tb::check_true("T3", "a sign change of Delta E exists between d/lambda = 0.1 and 100", Ec < 0.0 && std::sqrt(lo * hi) > 0.1 && std::sqrt(lo * hi) < 100.0);
    }

    tb::heading("T4 a fitted length makes a prediction");
    {
        const double E0 = -PI * PI / 360.0;
        double lo = 0.02, hi = 0.2;
        for (int it = 0; it < 100; ++it) {
            const double mid = 0.5 * (lo + hi);
            if (std::fabs(Ediff(1.0, mid)) / std::fabs(E0) > 0.99) lo = mid; else hi = mid;
        }
        const double x1 = 0.5 * (lo + hi);
        // same absolute cutoff length lambda = x1 (d = 1 units) at d = 2; the ideal energy scales as 1/d^3
        const double def2 = 1.0 - std::fabs(Ediff(2.0, x1)) * 8.0 / std::fabs(E0);
        tb::note("fitted lambda/d at d = 1: %.6f ; deficit at d = 2 with the same lambda: %.6e (prediction 0.0025)", x1, def2);
        tb::check("T4", "deficit at d = 2 equals 0.01/4", def2, 0.0025, 4e-2);
    }

    return tb::finish();
}
