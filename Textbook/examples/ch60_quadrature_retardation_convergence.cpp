// Chapter 60 — quadrature, retardation and convergence: worked-example instrument.
// Pre-registration: Textbook/validation/ch60_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/occlusion_sphere.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <numbers>
#include <random>
#include <vector>

namespace {

constexpr double PI = std::numbers::pi;

double simpson(const std::function<double(double)>& f, double a, double b, long n) {
    const double h = (b - a) / n;
    double s = f(a) + f(b);
    for (long i = 1; i < n; ++i) s += f(a + i * h) * ((i % 2) ? 4.0 : 2.0);
    return s * h / 3.0;
}
double trapezoid(const std::function<double(double)>& f, double a, double b, long n) {
    const double h = (b - a) / n;
    double s = 0.5 * (f(a) + f(b));
    for (long i = 1; i < n; ++i) s += f(a + i * h);
    return s * h;
}
double order(double q1, double q2, double q3) { return std::log2(std::fabs((q1 - q2) / (q2 - q3))); }

// Disc quadrature: n_r Gauss-Legendre radial nodes (the engine's six when n_r = 6), n_phi azimuth midpoints with phase offset eps (fraction of a cell).
double disc(const std::function<double(double, double)>& f, int nr, int nphi, double eps = 0.0) {
    std::vector<double> xr, wr;
    if (nr == 6) {
        for (double x : sdt::occlusion_sphere::radial_nodes) xr.push_back(x);
        for (double w : sdt::occlusion_sphere::radial_weights) wr.push_back(w);
    } else {
        const auto g = tb::gauss_legendre(nr);
        xr = g.x;
        wr = g.w;
    }
    double s = 0.0;
    for (int i = 0; i < nr; ++i) {
        const double r = 0.5 * (xr[i] + 1.0), w = 0.5 * wr[i];
        for (int j = 0; j < nphi; ++j) {
            const double phi = 2.0 * PI * (j + 0.5 + eps) / nphi;
            s += f(r * std::cos(phi), r * std::sin(phi)) * r * w * (2.0 * PI / nphi);
        }
    }
    return s;
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    tb::check("V1", "Simpson of exp on [0,1], n = 64", simpson([](double x) { return std::exp(x); }, 0.0, 1.0, 64), std::exp(1.0) - 1.0, 1e-9);
    const double area_exact = PI - (std::acos(0.3) - 0.3 * std::sqrt(0.91));
    {
        // independent smooth route (run 2): chord integral with y = sin(theta); run 1 used the discontinuous quadrature, which cannot reach 1e-6
        const double ths = std::asin(std::sqrt(0.91));
        const double a1 = tb::integrate([](double t) { return 0.3 * std::cos(t) + std::cos(t) * std::cos(t); }, -ths, ths, 32, 8);
        const double a2 = 4.0 * tb::integrate([](double t) { return std::cos(t) * std::cos(t); }, ths, PI / 2.0, 32, 8);  // two symmetric ranges, chord length 2w (run 2 had a factor 2)
        tb::check("V1", "unit disc area with x < 0.3: analytic value equals the smooth chord integral", a1 + a2, area_exact, 1e-12);
    }
    tb::note("analytic area = %.9f", area_exact);

    tb::heading("T1 order estimates and where they fail");
    {
        auto ex = [](double x) { return std::exp(x); };
        const double ps = order(simpson(ex, 0, 1, 8), simpson(ex, 0, 1, 16), simpson(ex, 0, 1, 32));
        const double pt = order(trapezoid(ex, 0, 1, 8), trapezoid(ex, 0, 1, 16), trapezoid(ex, 0, 1, 32));
        tb::note("Simpson order estimate %.5f ; trapezoid order estimate %.5f", ps, pt);
        tb::check_true("T1", "Simpson order estimate in [3.98, 4.02]", ps >= 3.98 && ps <= 4.02);
        tb::check_true("T1", "trapezoid order estimate in [1.98, 2.02]", pt >= 1.98 && pt <= 2.02);
        auto step = [](double x) { return x < 1.0 / PI ? 1.0 : 0.0; };
        std::vector<double> ph;
        for (int k = 3; k <= 10; ++k) ph.push_back(order(trapezoid(step, 0, 1, 1L << k), trapezoid(step, 0, 1, 1L << (k + 1)), trapezoid(step, 0, 1, 1L << (k + 2))));
        double mn = 1e300, mx = -1e300;
        std::printf("       step integrand, order estimates over 8 triples:");
        for (double p : ph) { std::printf(" %.4f", p); mn = std::fmin(mn, p); mx = std::fmax(mx, p); }
        std::printf("\n");
        tb::note("RECORDED REJECTION (run 1 criterion kept): range of the estimates %.4f (registered: above 0.5)", mx - mn);
        tb::check_true("T1", "the registered statement (step-integrand estimates with a range above 0.5) is rejected", !(mx - mn > 0.5));
        // post-run exploration, report only: other edge positions
        for (double xe : {0.3, 0.41, 0.6180339887498949, 0.7071067811865476, 0.9}) {
            auto st = [xe](double x) { return x < xe ? 1.0 : 0.0; };
            double lo = 1e300, hi = -1e300;
            for (int k = 3; k <= 10; ++k) {
                const double p = order(trapezoid(st, 0, 1, 1L << k), trapezoid(st, 0, 1, 1L << (k + 1)), trapezoid(st, 0, 1, 1L << (k + 2)));
                lo = std::fmin(lo, p); hi = std::fmax(hi, p);
            }
            tb::note("POST-RUN exploration (report only): edge at %.6f: estimates range from %.4f to %.4f", xe, lo, hi);
        }
        const double pc = order(simpson(ex, 0, 1, 1L << 14), simpson(ex, 0, 1, 1L << 15), simpson(ex, 0, 1, 1L << 16));
        tb::note("Simpson at n = 2^14..2^16 (differences at rounding level): estimate %.3f", pc);
        tb::check_true("T1", "near cancellation the estimate misses 4 by more than 1 (or is not finite)", !std::isfinite(pc) || std::fabs(pc - 4.0) > 1.0);
    }

    tb::heading("T2 independent quadrature controls");
    {
        const double smooth_exact = PI * (1.0 - std::exp(-1.0));
        auto smooth = [](double x, double y) { return std::exp(-(x * x + y * y)); };
        auto shadow = [](double x, double) { return x < 0.3 ? 1.0 : 0.0; };
        const double Es = std::fabs(disc(smooth, 6, 16) / smooth_exact - 1.0);
        tb::note("smooth integrand at (6,16): relative error %.3e", Es);
        tb::check_true("T2", "the smooth integrand at (6,16) has an error below 1e-7", Es < 1e-7);
        auto E = [&](int nr, int nphi) { return std::fabs(disc(shadow, nr, nphi) - area_exact); };
        const double e616 = E(6, 16), e6256 = E(6, 256), e9616 = E(96, 16), e96256 = E(96, 256);
        tb::note("shadow integrand absolute errors: E(6,16) = %.3e ; E(6,256) = %.3e ; E(96,16) = %.3e ; E(96,256) = %.3e", e616, e6256, e9616, e96256);
        tb::check_true("T2", "E(6,16) > 1e-3", e616 > 1e-3);
        tb::check_true("T2", "E(6,256) > 1e-5 (the radial control sets a floor)", e6256 > 1e-5);
        tb::note("RECORDED REJECTION (run 1 criterion kept): E(96,16) = %.3e (registered: above 1e-3)", e9616);
        tb::check_true("T2", "the registered statement (E(96,16) > 1e-3) is rejected", !(e9616 > 1e-3));
        tb::check_true("T2", "POST-RUN clause: E(96,16) lies in [1e-4, 1e-3] (the azimuthal control sets a floor)", e9616 >= 1e-4 && e9616 <= 1e-3);
        tb::check_true("T2", "E(96,256) is below E(6,256) and below E(96,16)", e96256 < e6256 && e96256 < e9616);
    }

    tb::heading("T3 phase origin of the azimuth grid");
    {
        auto smooth = [](double x, double y) { return std::exp(-(x * x + y * y)); };
        auto shadow = [](double x, double) { return x < 0.3 ? 1.0 : 0.0; };
        double spread_smooth16 = 0.0;
        double sh[2];
        int idx = 0;
        for (int N : {16, 64}) {
            double smn = 1e300, smx = -1e300, hmn = 1e300, hmx = -1e300;
            for (int k = 0; k < 10; ++k) {
                const double eps = 0.1 * k;
                const double qs = disc(smooth, 6, N, eps), qh = disc(shadow, 6, N, eps);
                smn = std::fmin(smn, qs); smx = std::fmax(smx, qs);
                hmn = std::fmin(hmn, qh); hmx = std::fmax(hmx, qh);
            }
            tb::note("N = %d: smooth spread %.3e ; shadow spread %.3e", N, smx - smn, hmx - hmn);
            if (N == 16) spread_smooth16 = smx - smn;
            sh[idx++] = hmx - hmn;
        }
        tb::check_true("T3", "the smooth axisymmetric integral varies by less than 1e-13 with the phase", spread_smooth16 < 1e-13);
        tb::check_true("T3", "the shadow integral's spread exceeds 1e-4 at N = 16", sh[0] > 1e-4);
        tb::check_true("T3", "the spread at N = 64 is at least 3 times smaller", sh[1] * 3.0 <= sh[0]);
    }

    tb::heading("T4 retardation: smooth regions and a shadow edge");
    {
        const double v = 0.5, xo = 3.0, edge = 0.5;
        auto tret = [&](double t, int n) {  // fixed-point iteration t_ret <- t - (xo - v t_ret) from t_ret = t
            double tr = t;
            for (int i = 0; i < n; ++i) tr = t - (xo - v * tr);
            return tr;
        };
        auto F = [](double s) { return 1.0 / ((2.0 - s) * (2.0 - s)); };
        std::mt19937_64 rng(20261110ULL);
        std::uniform_real_distribution<double> U(0.0, 2.0);
        const int NS = 200000;
        double dF4 = 0.0, dF8 = 0.0;
        long flip4 = 0, flip8 = 0;
        bool jump_ok = true;
        for (int i = 0; i < NS; ++i) {
            const double tstar = U(rng);                 // converged retarded time
            const double t = tstar + (xo - v * tstar);   // the observation time that has this retarded time
            const double s_conv = v * tstar;
            for (int n : {4, 8}) {
                const double s_n = v * tret(t, n);
                const double dF = std::fabs(F(s_n) - F(s_conv));
                if (n == 4) dF4 = std::fmax(dF4, dF); else dF8 = std::fmax(dF8, dF);
                const bool flip = (s_n < edge) != (s_conv < edge);
                if (flip) {
                    if (n == 4) ++flip4; else ++flip8;
                    // a flipped visibility changes the force by the whole force value at the true position (0 <-> F)
                    const double jump = std::fabs(((s_n < edge) ? F(s_n) : 0.0) - ((s_conv < edge) ? F(s_conv) : 0.0));
                    if (jump < 0.2 * std::fmin(F(s_n), F(s_conv))) jump_ok = false;
                }
            }
        }
        tb::note("smooth-only maximum force error: n = 4: %.4e ; n = 8: %.4e ; ratio %.3f", dF4, dF8, dF4 / dF8);
        tb::note("flipped visibility among %d samples: n = 4: %ld ; n = 8: %ld ; ratio %.3f", NS, flip4, flip8, static_cast<double>(flip4) / static_cast<double>(flip8));
        tb::check_true("T4", "the smooth-only maximum force error falls by a factor in [12, 20] from n = 4 to n = 8", dF4 / dF8 >= 12.0 && dF4 / dF8 <= 20.0);
        tb::check_true("T4", "the fraction of flipped visibilities falls by a factor in [12, 20] from n = 4 to n = 8", static_cast<double>(flip4) / static_cast<double>(flip8) >= 12.0 && static_cast<double>(flip4) / static_cast<double>(flip8) <= 20.0);
        tb::check_true("T4", "a flipped sample's force error is the full force value, independent of n", jump_ok);
    }

    return tb::finish();
}
