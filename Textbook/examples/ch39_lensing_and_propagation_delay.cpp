// Chapter 39 — lensing and propagation delay: worked-example instrument.
// Pre-registration: Textbook/validation/ch39_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <array>
#include <cmath>
#include <functional>

namespace {

constexpr double kPi = std::numbers::pi;
using F = std::function<double(double)>;

// Gauss-Legendre 8-point nodes/weights on [-1,1]
const double gx[8] = {-0.9602898564975363, -0.7966664774136267, -0.5255324099163290, -0.1834346424956498, 0.1834346424956498, 0.5255324099163290, 0.7966664774136267, 0.9602898564975363};
const double gw[8] = {0.1012285362903763, 0.2223810344533745, 0.3137066458778873, 0.3626837833783620, 0.3626837833783620, 0.3137066458778873, 0.2223810344533745, 0.1012285362903763};

double gl(const F& f, double a, double b, int panels) {
    double s = 0.0;
    const double h = (b - a) / panels;
    for (int p = 0; p < panels; ++p) {
        const double lo = a + p * h, mid = lo + 0.5 * h;
        for (int i = 0; i < 8; ++i) s += gw[i] * f(mid + 0.5 * h * gx[i]);
    }
    return 0.5 * h * s;
}

// Deflection (rad) of a ray with periapsis r0 in the index n(r), Bouguer integral; returns alpha and the impact parameter b.
double deflection(const F& n, double r0, double* b_out) {
    const double n0 = n(r0), b = n0 * r0;
    if (b_out) *b_out = b;
    // alpha = 2 int_0^1 n0 du / sqrt(n(r0/u)^2 - n0^2 u^2) - pi ; u = 1 - t^2, du = 2 t dt
    auto g = [&](double t) {
        const double u = 1.0 - t * t;
        const double rr = r0 / u;
        const double d = n(rr) * n(rr) - n0 * n0 * u * u;
        // d ~ t^2 near t = 0; guard
        return 2.0 * t * n0 / std::sqrt(std::fmax(d, 1e-300));
    };
    // near t=0 the integrand is finite; use the limit by evaluating at tiny t
    auto g2 = [&](double t) { return t < 1e-8 ? g(1e-8) : g(t); };
    const double I = gl(g2, 0.0, 1.0, 4000);
    return 2.0 * I - kPi;
}

}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    namespace DC = sdt::laws::depth_closure;
    tb::validate_helpers();
    const double c = M::c;

    tb::heading("V1 integrals and the Bouguer deflection on known cases");
    {
        const double b = 1.0, s1 = 3.0, s2 = 7.0;
        const double q = gl([&](double s) { return 1.0 / std::sqrt(b * b + s * s); }, -s1, s2, 200);
        tb::check("V1", "integral of ds/sqrt(b^2+s^2) = asinh(s1/b) + asinh(s2/b)", q, std::asinh(s1 / b) + std::asinh(s2 / b), 1e-10);
        double bb;
        const double a0 = deflection([](double) { return 1.5; }, 1.0, &bb);
        tb::check("V1", "constant index: deflection 0 (quadrature accuracy 1e-9)", a0 + 1.0, 1.0, 1e-9);
        const double eps = 1e-4;
        double b2;
        const double a1 = deflection([&](double r) { return 1.0 + eps / r; }, 1.0, &b2);
        tb::check("V1", "n = 1 + eps/r: deflection = 2 eps / b", a1, 2.0 * eps / b2, 1e-3);
    }

    const double varpi = sdt::laws::bridge::koppa_Sun, Rsun = M::R_Sun, AU = M::AU;

    tb::heading("T1 series and delay");
    {
        const double z = 1e-2;
        const double ex = std::pow(1.0 - z, -2.0), ser = 1.0 + 2 * z + 3 * z * z + 4 * z * z * z;
        tb::check_true("T1", "(1-z)^-2 differs from 1 + 2z + 3z^2 + 4z^3 by at most 5.1 z^4 (corrected bound)", std::fabs(ex - ser) <= 5.1 * std::pow(z, 4));
        const double r1 = AU, r2 = 1.524 * AU, b = Rsun;
        const double eng = DC::shapiro_delay(varpi, r1, r2, b);
        tb::check("T1", "shapiro_delay equals (2 varpi/c) ln(4 r1 r2/b^2)", eng, 2.0 * varpi / c * std::log(4.0 * r1 * r2 / (b * b)), 1e-13);
        const double s1 = std::sqrt(r1 * r1 - b * b), s2 = std::sqrt(r2 * r2 - b * b);
        const double first = 2.0 * varpi / c * (std::asinh(s1 / b) + std::asinh(s2 / b));
        tb::check("T1", "first-order delay with exact endpoints vs far-endpoint form", first, eng, 1e-6);
        // exact integrand, numerically (log-spaced panels in s)
        auto integrand = [&](double s) { const double z2 = varpi / std::sqrt(b * b + s * s); return (1.0 / ((1.0 - z2) * (1.0 - z2)) - 1.0) / c; };
        auto I = [&](double sa, double sb) {
            // integrate in t = asinh(s/b) to resolve the b scale
            return gl([&](double t) { const double s = b * std::sinh(t); return integrand(s) * b * std::cosh(t); }, std::asinh(sa / b), std::asinh(sb / b), 400);
        };
        const double exact = I(0.0, s1) + I(0.0, s2);
        const double second = 3.0 * varpi * varpi / c * (std::atan(s1 / b) + std::atan(s2 / b)) / b;
        const double third_and_up = exact - first - second;
        tb::note("one-way delay: exact integrand %.9e s ; first order %.9e s ; second-order term %.4e s ; remainder %.3e s ; round trip (first order) %.3f microseconds", exact, first, second, third_and_up, 2.0 * first * 1e6);
        tb::check("T1", "(exact - first order) equals the second-order term 3 varpi^2/c int ds/(b^2+s^2) to 1%", exact - first, second, 1e-2);
    }

    auto fit = [&](const std::function<double(double, double)>& nfun, double& c1, double& c2, double& c3) {
        // nfun(r, varpi) -> index. Use varpi = 1; choose r0 so that x = varpi/b = target.
        const double xs[3] = {1e-3, 2e-3, 4e-3};
        double A[3][4];
        for (int i = 0; i < 3; ++i) {
            double r0 = 1.0 / xs[i];
            for (int it = 0; it < 60; ++it) {  // adjust r0 so that b = n0 r0 = 1/x
                const double b = nfun(r0, 1.0) * r0;
                r0 *= (1.0 / xs[i]) / b;
            }
            double b;
            const double alpha = deflection([&](double r) { return nfun(r, 1.0); }, r0, &b);
            const double x = 1.0 / b;
            A[i][0] = x; A[i][1] = x * x; A[i][2] = x * x * x; A[i][3] = alpha;
        }
        for (int col = 0; col < 3; ++col) {
            int p = col;
            for (int r = col + 1; r < 3; ++r) if (std::fabs(A[r][col]) > std::fabs(A[p][col])) p = r;
            for (int k = 0; k < 4; ++k) std::swap(A[col][k], A[p][k]);
            for (int r = col + 1; r < 3; ++r) {
                const double f = A[r][col] / A[col][col];
                for (int k = col; k < 4; ++k) A[r][k] -= f * A[col][k];
            }
        }
        double sol[3];
        for (int r = 2; r >= 0; --r) {
            double v = A[r][3];
            for (int k = r + 1; k < 3; ++k) v -= A[r][k] * sol[k];
            sol[r] = v / A[r][r];
        }
        c1 = sol[0]; c2 = sol[1]; c3 = sol[2];
    };

    tb::heading("T2 bending in the active profile c_far = c (1 - z)^2");
    double c2_active = 0.0;
    {
        double c1, c2, c3;
        fit([](double r, double w) { const double z = w / r; return 1.0 / ((1.0 - z) * (1.0 - z)); }, c1, c2, c3);
        c2_active = c2;
        tb::note("alpha = c1 x + c2 x^2 + c3 x^3 with x = varpi/b : c1 = %.7f ; c2 = %.5f ; c3 = %.3f", c1, c2, c3);
        tb::note("solar limb: 4 varpi_sun/R_sun = %.4e rad = %.5f arcsec", 4.0 * varpi / Rsun, 4.0 * varpi / Rsun * 180.0 / kPi * 3600.0);
        tb::check_true("T2", "c1 = 4 to 4e-5", std::fabs(c1 - 4.0) <= 4e-5);
    }

    tb::heading("T3 branch discrimination");
    {
        double c1b, c2b, c3b, c1a, c2a, c3a, c1c, c2c, c3c;
        fit([](double r, double w) { const double z = w / r; return 1.0 / (1.0 - 2.0 * z); }, c1b, c2b, c3b);                      // a = 4
        fit([](double r, double w) { const double z = w / r; return 1.0 + 2.0 * z + 2.0 * z * z; }, c1a, c2a, c3a);               // a = 2
        fit([](double r, double w) { const double z = w / r; return 1.0 + 2.0 * z + 3.0 * z * z; }, c1c, c2c, c3c);               // a = 3
        tb::note("c1: a=2: %.6f ; a=3: %.6f ; a=4 (alternative profile): %.6f", c1a, c1c, c1b);
        tb::note("c2: a=2: %.5f ; a=3: %.5f ; a=4: %.5f ; active profile (1-z)^-2: %.5f", c2a, c2c, c2b, c2_active);
        tb::check_true("T3", "c1 = 4 for the alternative profile to 4e-5", std::fabs(c1b - 4.0) <= 4e-5);
        const double d1 = c2c - c2a, d2 = c2b - c2c;
        tb::check_true("T3", "c2 is linear in the coefficient a of z^2: (c2(3)-c2(2)) = (c2(4)-c2(3)) to 1%", std::fabs(d1 / d2 - 1.0) < 1e-2);
        const double dc2 = c2b - c2_active;
        tb::check_true("T3", "c2 differs between the active and the alternative branch", std::fabs(dc2) > 0.5);
        const double x = varpi / Rsun;
        tb::note("delta c2 = %.5f ; deflection difference at the solar limb = %.3e rad = %.3e arcsec", dc2, dc2 * x * x, dc2 * x * x * 180.0 / kPi * 3600.0);
        tb::note("second-order delay difference pi varpi^2/(b c) at the solar limb = %.3e s one way", kPi * varpi * varpi / (Rsun * c));
    }

    return tb::finish();
}
