// Chapter 31 — molecular bonding and reactions: worked-example instrument (TOY model functions).
// Pre-registration: Textbook/validation/ch31_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <cstdint>
#include <functional>
#include <vector>

namespace {

using F = std::function<double(double)>;

double d1(const F& f, double x, double h) { return (f(x + h) - f(x - h)) / (2.0 * h); }
double d2(const F& f, double x, double h) { return (f(x + h) - 2.0 * f(x) + f(x - h)) / (h * h); }
double d3(const F& f, double x, double h) { return (f(x + 2 * h) - 2.0 * f(x + h) + 2.0 * f(x - h) - f(x - 2 * h)) / (2.0 * h * h * h); }
double rich(const std::function<double(double)>& g) { return (4.0 * g(0.5e-3) - g(1e-3)) / 3.0; }

F mie(double A, double B, double m) { return [=](double R) { return -A / R + B / std::pow(R, m); }; }
F morse(double D, double a, double R0) { return [=](double R) { double e = 1.0 - std::exp(-a * (R - R0)); return D * e * e; }; }

struct Rng {
    std::uint64_t s;
    double next() {
        s = s * 6364136223846793005ULL + 1442695040888963407ULL;
        return static_cast<double>(s >> 11) * (1.0 / 9007199254740992.0);
    }
};

}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    tb::validate_helpers();

    tb::heading("V1 Morse derivatives");
    {
        const F e = morse(2.0, 1.5, 1.0);
        tb::check("V1", "E''(R0) = 2 D a^2 = 9", rich([&](double h) { return d2(e, 1.0, h); }), 9.0, 1e-4);
        tb::check("V1", "E'''(R0) = -6 D a^3 = -40.5", rich([&](double h) { return d3(e, 1.0, h * 10); }), -40.5, 1e-4);
    }

    tb::heading("T1 when is there a bond");
    {
        const F inv = mie(1.0, 0.0, 2.0);
        bool pos = true;
        for (int i = 0; i < 2000; ++i) {
            const double R = std::pow(10.0, -3.0 + 6.0 * i / 1999.0);
            pos = pos && (1.0 / (R * R) > 0.0) && (d1(inv, R, 1e-6 * R) > 0.0);
        }
        tb::check_true("T1", "E = -1/R has E' > 0 on 2000 log-spaced R in [1e-3, 1e3] (no stationary point)", pos);
        double best = 1e300, Rbest = 0.0;
        for (int i = 0; i <= 4000; ++i) {
            const double R = 1.0 + 9.0 * i / 4000.0;
            if (inv(R) < best) { best = inv(R); Rbest = R; }
        }
        tb::check_true("T1", "with a wall at R_c = 1 the minimum is on the wall and E'(R_c) = 1 (not a restoring response)", Rbest == 1.0 && std::fabs(d1(inv, 1.0, 1e-6) - 1.0) < 1e-6);
        const double fam[4][3] = {{1, 1, 2}, {1, 0.5, 3}, {2, 1, 6}, {3, 2, 12}};
        double wR = 0, wD = 0, wm = 0;
        bool conv = true;
        for (const auto& p : fam) {
            const double A = p[0], B = p[1], m = p[2];
            const F e = mie(A, B, m);
            auto g = [&](double R) { return A / (R * R) - m * B / std::pow(R, m + 1.0); };
            double lo = 1e-3, hi = 1e3;
            for (int i = 0; i < 400; ++i) {
                const double mid = std::sqrt(lo * hi);
                (g(mid) < 0.0 ? lo : hi) = mid;
            }
            const double Rs = std::sqrt(lo * hi);
            const double Rf = std::pow(m * B / A, 1.0 / (m - 1.0));
            const double k = A / (Rs * Rs * Rs) * (m - 1.0);
            const double kn = rich([&](double h) { return d2(e, Rs, h * Rs); });
            const double D = -e(Rs), Df = A / Rs * (1.0 - 1.0 / m);
            wR = std::fmax(wR, std::fabs(Rs / Rf - 1.0));
            wD = std::fmax(wD, std::fabs(D / Df - 1.0));
            wm = std::fmax(wm, std::fabs(k * Rs * Rs / D / m - 1.0));
            conv = conv && kn > 0.0;
        }
        tb::check("T1", "stationary point equals (mB/A)^(1/(m-1)), worst relative", wR, 0.0, 1e-10, false);
        tb::check("T1", "D = (A/R*)(1 - 1/m), worst relative", wD, 0.0, 1e-10, false);
        tb::check("T1", "k R*^2/D = m, worst relative", wm, 0.0, 1e-10, false);
        tb::check_true("T1", "E'' > 0 at every Mie stationary point (numerical curvature)", conv);
    }

    tb::heading("T2 isotope scaling of the small-oscillation frequency");
    {
        const double mH2 = M::m_p / 2.0, mHD = M::m_p * M::m_d / (M::m_p + M::m_d), mD2 = M::m_d / 2.0;
        std::vector<F> fams{mie(1, 1, 2), mie(1, 0.5, 3), mie(2, 1, 6), mie(3, 2, 12), morse(2.0, 1.5, 1.0)};
        const double R0[5] = {1.0, std::pow(1.5, 0.5), std::pow(6.0 * 0.5 / 1.0 * 1.0, 1.0 / 5.0) , 0.0, 1.0};
        (void)R0;
        const double Rstar[5] = {std::pow(2.0 * 1.0 / 1.0, 1.0 / 1.0), std::pow(3.0 * 0.5 / 1.0, 1.0 / 2.0), std::pow(6.0 * 1.0 / 2.0, 1.0 / 5.0), std::pow(12.0 * 2.0 / 3.0, 1.0 / 11.0), 1.0};
        double w1 = 0, w2 = 0;
        for (int i = 0; i < 5; ++i) {
            const double k = rich([&](double h) { return d2(fams[i], Rstar[i], h * Rstar[i]); });
            const double wH = std::sqrt(k / mH2), wHD = std::sqrt(k / mHD), wD = std::sqrt(k / mD2);
            w1 = std::fmax(w1, std::fabs(wH / wD / std::sqrt(mD2 / mH2) - 1.0));
            w2 = std::fmax(w2, std::fabs(wH / wHD / std::sqrt(mHD / mH2) - 1.0));
        }
        tb::check("T2", "omega(H2)/omega(D2) = sqrt(mu_D2/mu_H2) for five families, worst relative", w1, 0.0, 1e-12, false);
        tb::check("T2", "omega(H2)/omega(HD) = sqrt(mu_HD/mu_H2), worst relative", w2, 0.0, 1e-12, false);
        tb::note("mu(H2) = %.6e kg ; mu(HD) = %.6e kg ; mu(D2) = %.6e kg ; omega(H2)/omega(D2) = %.6f", mH2, mHD, mD2, std::sqrt(mD2 / mH2));
    }

    tb::heading("T3 three observables are absorbed exactly; a fourth discriminates");
    {
        Rng g{3131};
        double w = 0.0;
        int made = 0, none = 0;
        for (int i = 0; i < 2000 && made < 1000; ++i) {
            const double Rs = 0.5 + 2.0 * g.next(), k = 0.5 + 30.0 * g.next(), D = 0.2 + 5.0 * g.next();
            const double m = k * Rs * Rs / D;
            if (m <= 1.0) { ++none; continue; }
            const double A = k * Rs * Rs * Rs / (m - 1.0), B = A * std::pow(Rs, m - 1.0) / m;
            const F e = mie(A, B, m);
            const double kk = -2.0 * A / (Rs * Rs * Rs) + m * (m + 1.0) * B / std::pow(Rs, m + 2.0), DD = -e(Rs);
            const double dprime = A / (Rs * Rs) - m * B / std::pow(Rs, m + 1.0);
            w = std::fmax(w, std::fmax(std::fabs(kk / k - 1.0), std::fmax(std::fabs(DD / D - 1.0), std::fabs(dprime) / (A / (Rs * Rs)))));
            ++made;
        }
        tb::note("%d triples absorbed ; %d triples with kR*^2/D <= 1 have no Mie member", made, none);
        tb::check_true("T3", "1000 triples: k, D and E'(R*) = 0 reproduced to 1e-10 by the analytic derivatives", made == 1000 && w < 1e-10);
        const double Rs = 1.0, k = 20.0, D = 2.0, m = k * Rs * Rs / D;
        const double A = k * Rs * Rs * Rs / (m - 1.0), B = A * std::pow(Rs, m - 1.0) / m;
        const F em = mie(A, B, m), eo = morse(D, std::sqrt(k / (2.0 * D)), Rs);
        const double c3m = rich([&](double h) { return d3(em, Rs, h * 10); }), c3o = rich([&](double h) { return d3(eo, Rs, h * 10); });
        tb::note("m = %.1f ; Mie E''' = %.4f (formula %.4f) ; Morse E''' = %.4f (formula %.4f)", m, c3m, -k * (m + 4.0) / Rs, c3o, -6.0 * D * std::pow(k / (2.0 * D), 1.5));
        tb::check("T3", "Mie E''' = -k (m+4)/R* = -280", c3m, -280.0, 1e-3);
        tb::check("T3", "Morse E''' = -6 D (k/2D)^(3/2) = -134.16", c3o, -6.0 * D * std::pow(k / (2.0 * D), 1.5), 1e-3);
        tb::check_true("T3", "the two families with identical (R*, k, D) differ in E''' by a factor above 2", std::fabs(c3m / c3o) > 2.0);
    }

    tb::heading("T4 pathway dependence on a TOY surface");
    {
        auto E = [](double x, double y, double g, double w) { return std::pow(x * x - 1.0, 2) + 2.0 * std::pow(y - 0.3 * x * x, 2) - g * std::exp(-(x * x + y * y) / (w * w)); };
        auto Emin = [&](double x, double g, double w) {
            double y = 0.3 * x * x;
            for (int it = 0; it < 100; ++it) {
                const double h = 1e-5;
                const double d1y = (E(x, y + h, g, w) - E(x, y - h, g, w)) / (2 * h), d2y = (E(x, y + h, g, w) - 2 * E(x, y, g, w) + E(x, y - h, g, w)) / (h * h);
                const double step = d1y / std::fmax(d2y, 1e-3);
                y -= std::fmax(-0.1, std::fmin(0.1, step));
                if (std::fabs(step) < 1e-13) break;
            }
            return E(x, y, g, w);
        };
        const double w = 0.15;
        auto barrier = [&](double g, double* endp) {
            double mx = -1e300;
            for (int i = 0; i <= 2000; ++i) mx = std::fmax(mx, Emin(-1.0 + 2.0 * i / 2000.0, g, w));
            *endp = Emin(1.0, g, w);
            return mx - *endp;
        };
        double e0, e1;
        const double b0 = barrier(0.0, &e0), b1 = barrier(0.4, &e1);
        tb::note("barrier g=0: %.6f ; g=0.4: %.6f ; endpoint energies %.3e and %.3e", b0, b1, e0, e1);
        tb::check("T4", "endpoint energy unchanged by the localised term", e1, e0, 1e-12, false);
        tb::check_true("T4", "barrier lowered by at least 0.1 and at most g = 0.4", (b0 - b1) >= 0.1 && (b0 - b1) <= 0.4 + 1e-9);
    }

    return tb::finish();
}
