// Chapter 50 — interference and detection: worked-example instrument (generic stand-ins, no engine function).
// Pre-registration: Textbook/validation/ch50_PRE_REGISTRATION.md (registered before this file existed).
#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <complex>
#include <numbers>
#include <random>
#include <vector>

namespace {

constexpr double PI = std::numbers::pi;
using cd = std::complex<double>;

constexpr double LAM = 500e-9, K0 = 2.0 * PI / LAM;

// exact path from a point source at (0, ys) to a screen point (L, y)
double path(double ys, double y, double L) { return std::hypot(L, y - ys); }

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    {
        const cd a(1.0, 2.0), b(-0.5, 0.25);
        tb::check("V1", "|A1 + A2|^2 = |A1|^2 + |A2|^2 + 2 Re(A1 A2*)", std::norm(a + b), std::norm(a) + std::norm(b) + 2.0 * std::real(a * std::conj(b)), 1e-12);
        const double sig = 0.05 * K0;
        const double z0 = tb::integrate([&](double k) { return std::exp(-0.5 * (k - K0) * (k - K0) / (sig * sig)); }, K0 - 10 * sig, K0 + 10 * sig, 48, 20);
        tb::check("V1", "Gaussian spectrum zeroth moment = sigma sqrt(2 pi)", z0, sig * std::sqrt(2.0 * PI), 1e-12);
        const double mu = 20.5;
        const double mean = tb::integrate([&](double ph) { return std::floor(mu + ph); }, 0.0, 0.5, 8, 1) + tb::integrate([&](double ph) { return std::floor(mu + ph); }, 0.5, 1.0 - 1e-15, 8, 1);
        const double m2 = tb::integrate([&](double ph) { const double v = std::floor(mu + ph); return v * v; }, 0.0, 0.5, 8, 1) + tb::integrate([&](double ph) { const double v = std::floor(mu + ph); return v * v; }, 0.5, 1.0 - 1e-15, 8, 1);
        tb::check("V1", "variance of floor(20.5 + phi), phi uniform = 0.25", m2 - mean * mean, 0.25, 1e-9);
    }

    tb::heading("T1 two apertures");
    {
        const double d = 1e-3, L = 1.0;
        double worst_I = 0.0, worst_sa = 0.0;
        for (int n = 1; n <= 5; ++n) {
            // solve r1 - r2 = n lambda, with sources at +d/2 and -d/2
            auto f = [&](double y) { return path(d / 2, y, L) - path(-d / 2, y, L) + n * LAM; };
            double a = 0.0, b = 0.01;
            // r1 - r2 is negative for y > 0 (nearer to the +d/2 source): look for the root of f
            for (int it = 0; it < 200; ++it) { const double m = 0.5 * (a + b); if (f(m) > 0) a = m; else b = m; }
            const double y = 0.5 * (a + b);
            const cd A1 = std::exp(cd(0, K0 * path(d / 2, y, L))), A2 = std::exp(cd(0, K0 * path(-d / 2, y, L)));
            worst_I = std::fmax(worst_I, std::fabs(std::norm(A1 + A2) - 4.0));
            const double ysa = n * LAM * L / d;
            worst_sa = std::fmax(worst_sa, std::fabs(y / ysa - 1.0));
            tb::note("n = %d: exact maximum y = %.9e m ; small-angle %.9e m ; relative difference %.3e", n, y, ysa, y / ysa - 1.0);
        }
        tb::check("T1", "intensity at the exact maxima equals 4 (worst absolute deviation)", worst_I, 0.0, 1e-10, false);
        tb::check_true("T1", "exact maxima differ from n lambda L/d by less than 1e-4 relative", worst_sa < 1e-4);
        double imax = -1e300, imin = 1e300;
        const double r = 0.5;
        for (int i = 0; i <= 20000; ++i) {
            const double ph = 2.0 * PI * i / 20000.0;
            const double I = std::norm(cd(1.0, 0.0) + r * std::exp(cd(0, ph)));
            imax = std::fmax(imax, I);
            imin = std::fmin(imin, I);
        }
        tb::check("T1", "visibility for amplitudes 1 and 0.5 equals 2r/(1+r^2) = 0.8", (imax - imin) / (imax + imin), 0.8, 1e-9);
    }

    tb::heading("T2 finite bandwidth reduces visibility");
    {
        const double sig = 0.05 * K0;
        const double z0 = sig * std::sqrt(2.0 * PI);
        for (double dl : {1e-6, 3e-6, 1e-5}) {
            const double re = tb::integrate([&](double k) { return std::exp(-0.5 * (k - K0) * (k - K0) / (sig * sig)) * std::cos(k * dl); }, K0 - 10 * sig, K0 + 10 * sig, 48, 400);
            const double im = tb::integrate([&](double k) { return std::exp(-0.5 * (k - K0) * (k - K0) / (sig * sig)) * std::sin(k * dl); }, K0 - 10 * sig, K0 + 10 * sig, 48, 400);
            const double V = std::hypot(re, im) / z0;
            const double Vexp = std::exp(-0.5 * sig * sig * dl * dl);
            char lab[96];
            std::snprintf(lab, sizeof lab, "visibility at path difference %.0f um", dl * 1e6);
            if (dl < 5e-6) tb::check("T2", lab, V, Vexp, 1e-8);
            else tb::check("T2", lab, V, Vexp, 1e-14, false);  // value 2.7e-9 is at the double-precision floor of the integral: absolute tolerance
            tb::note("path difference %.1e m: visibility %.6f", dl, V);
        }
    }

    tb::heading("T3 blocking one aperture changes the pattern");
    double Z2 = 0.0;
    std::vector<double> ys, I2, I1;
    {
        const double a = 0.1e-3, d = 1e-3, L = 1.0, win = 5e-3;
        const int NY = 4001;
        double Zc = 0.0, Z1 = 0.0, Zcross = 0.0;
        auto amp = [&](double y, double yc) {
            const double re = tb::integrate([&](double s) { return std::cos(K0 * path(yc + s, y, L)); }, -a / 2, a / 2, 32, 8);
            const double im = tb::integrate([&](double s) { return std::sin(K0 * path(yc + s, y, L)); }, -a / 2, a / 2, 32, 8);
            return cd(re, im);
        };
        for (int i = 0; i < NY; ++i) {
            const double y = -win + 2.0 * win * i / (NY - 1);
            const cd A1 = amp(y, d / 2), A2 = amp(y, -d / 2);
            const double i2 = std::norm(A1 + A2), i1 = std::norm(A1), i1b = std::norm(A2);
            const double cross = 2.0 * std::real(A1 * std::conj(A2));
            ys.push_back(y);
            I2.push_back(i2);
            I1.push_back(i1);
            Z2 += i2;
            Z1 += i1;
            Zc += i1 + i1b;
            Zcross += cross;
        }
        double tv = 0.0;
        for (int i = 0; i < NY; ++i) tv += std::fabs(I2[i] / Z2 - I1[i] / Z1);
        tv *= 0.5;
        tb::note("total-variation distance between the normalised two-slit and single-slit patterns: %.5f (1/pi = %.5f)", tv, 1.0 / PI);
        tb::check_true("T3", "the total-variation distance lies in [0.28, 0.35]", tv >= 0.28 && tv <= 0.35);
        tb::note("window integral of the cross term / single-slit integral = %.5f", Zcross / Z1);
        tb::check("T3", "the two-slit pattern equals the sum of single-slit patterns plus the cross term", Z2, Zc + Zcross, 1e-10);
        tb::check_true("T3", "the cross-term integral over the window is below 5 per cent of the single-slit integral", std::fabs(Zcross) / Z1 < 0.05);
    }

    tb::heading("T4 detection as an endpoint: two rules for event statistics");
    {
        const double mu = 20.37;
        std::mt19937_64 rng(20261110ULL);
        std::uniform_real_distribution<double> U(0.0, 1.0);
        const int NT = 200000;
        double s = 0.0, s2 = 0.0;
        bool below = true;
        for (int i = 0; i < NT; ++i) {
            const double n = std::floor(mu + U(rng));
            s += n;
            s2 += n * n;
        }
        double m = s / NT, v = s2 / NT - m * m;
        const double F_thr = v / m;
        tb::note("threshold accumulate-and-fire: mean %.5f variance %.5f Fano %.6f (predicted %.6f ; bound 1/(4 mu) = %.6f)", m, v, F_thr, 0.37 * 0.63 / mu, 0.25 / mu);
        below = F_thr <= 0.25 / mu * 1.0001;
        tb::check_true("T4", "threshold detector Fano factor lies in [0.010, 0.0125]", F_thr >= 0.010 && F_thr <= 0.0125);
        tb::check_true("T4", "threshold detector Fano factor does not exceed 1/(4 mu)", below);
        std::poisson_distribution<int> P(mu);
        s = s2 = 0.0;
        for (int i = 0; i < NT; ++i) {
            const double n = P(rng);
            s += n;
            s2 += n * n;
        }
        m = s / NT;
        v = s2 / NT - m * m;
        tb::note("Poisson sampling: mean %.5f variance %.5f Fano %.6f", m, v, v / m);
        tb::check_true("T4", "Poisson sampling Fano factor lies in [0.98, 1.02]", v / m >= 0.98 && v / m <= 1.02);
        // inverse-CDF sampling of event positions from the two-slit pattern, 40 bins
        std::vector<double> cdf(ys.size());
        double acc = 0.0;
        for (size_t i = 0; i < ys.size(); ++i) { acc += I2[i]; cdf[i] = acc / Z2; }
        const int NB = 40;
        std::vector<double> counts(NB, 0.0), expect(NB, 0.0);
        const int NE = 200000;
        for (int e = 0; e < NE; ++e) {
            const double u = U(rng);
            const size_t idx = std::lower_bound(cdf.begin(), cdf.end(), u) - cdf.begin();
            const int bin = std::min(NB - 1, static_cast<int>(idx * NB / ys.size()));
            counts[bin] += 1.0;
        }
        for (size_t i = 0; i < ys.size(); ++i) expect[std::min<size_t>(NB - 1, i * NB / ys.size())] += NE * I2[i] / Z2;
        double chi2 = 0.0;
        for (int b = 0; b < NB; ++b) chi2 += (counts[b] - expect[b]) * (counts[b] - expect[b]) / expect[b];
        tb::note("event positions sampled from the pattern: chi^2/dof = %.4f (%d bins)", chi2 / (NB - 1), NB);
        tb::check_true("T4", "chi^2/dof lies in [0.7, 1.3] (comparison-rule consistency)", chi2 / (NB - 1) >= 0.7 && chi2 / (NB - 1) <= 1.3);
    }

    return tb::finish();
}
