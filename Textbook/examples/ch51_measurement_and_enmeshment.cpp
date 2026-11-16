// Chapter 51 — measurement and enmeshment: worked-example instrument (generic stand-ins, no engine function).
// Pre-registration: Textbook/validation/ch51_PRE_REGISTRATION.md (registered before this file existed).
#include "tb_common.hpp"

#include <array>
#include <cmath>
#include <numbers>
#include <random>
#include <vector>

namespace {

constexpr double PI = std::numbers::pi;
using Joint = std::array<std::array<std::array<std::array<double, 2>, 2>, 2>, 2>;  // p[x][y][a][b], a,b in {+1,-1} -> index 0,1

double sgn(int i) { return i == 0 ? 1.0 : -1.0; }

double E_of(const Joint& p, int x, int y) {
    double e = 0.0;
    for (int a = 0; a < 2; ++a)
        for (int b = 0; b < 2; ++b) e += sgn(a) * sgn(b) * p[x][y][a][b];
    return e;
}
double S_of(const Joint& p) { return E_of(p, 0, 0) + E_of(p, 0, 1) + E_of(p, 1, 0) - E_of(p, 1, 1); }

double norm_err(const Joint& p) {
    double w = 0.0;
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < 2; ++y) {
            double s = 0.0;
            for (int a = 0; a < 2; ++a)
                for (int b = 0; b < 2; ++b) s += p[x][y][a][b];
            w = std::fmax(w, std::fabs(s - 1.0));
        }
    return w;
}

// marginal of A: p(a|x,y) ; of B: p(b|x,y)
double margA(const Joint& p, int x, int y, int a) { return p[x][y][a][0] + p[x][y][a][1]; }
double margB(const Joint& p, int x, int y, int b) { return p[x][y][0][b] + p[x][y][1][b]; }

Joint deterministic(int a0, int a1, int b0, int b1) {  // a(x) = sgn(a_x), b(y) = sgn(b_y); indices 0 -> +1, 1 -> -1
    Joint p{};
    const int a[2] = {a0, a1}, b[2] = {b0, b1};
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < 2; ++y) p[x][y][a[x]][b[y]] = 1.0;
    return p;
}

Joint mix(const Joint& u, const Joint& v, double w) {
    Joint p{};
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < 2; ++y)
            for (int a = 0; a < 2; ++a)
                for (int b = 0; b < 2; ++b) p[x][y][a][b] = w * u[x][y][a][b] + (1.0 - w) * v[x][y][a][b];
    return p;
}

Joint target(double thA0, double thA1, double thB0, double thB1) {
    const double thA[2] = {thA0, thA1}, thB[2] = {thB0, thB1};
    Joint p{};
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < 2; ++y) {
            const double E = -std::cos(thA[x] - thB[y]);
            for (int a = 0; a < 2; ++a)
                for (int b = 0; b < 2; ++b) p[x][y][a][b] = 0.25 * (1.0 + sgn(a) * sgn(b) * E);
        }
    return p;
}

Joint pr_box() {
    Joint p{};
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < 2; ++y)
            for (int a = 0; a < 2; ++a)
                for (int b = 0; b < 2; ++b) {
                    // outcomes satisfy a*b = (-1)^{x y} ... use product: sgn(a) sgn(b) = +1 unless x = y = 1
                    const double prod = sgn(a) * sgn(b);
                    const double want = (x == 1 && y == 1) ? -1.0 : 1.0;
                    p[x][y][a][b] = (prod == want) ? 0.5 : 0.0;
                }
    return p;
}

// Signalling strategy: A's outcome depends on both settings, a(x,y) = want_xy * b (b = +1 fixed)
Joint signalling() {
    Joint p{};
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < 2; ++y) {
            const double want = (x == 1 && y == 1) ? -1.0 : 1.0;  // a = want (b = +1): E = want
            const int ai = want > 0 ? 0 : 1;
            p[x][y][ai][0] = 1.0;
        }
    return p;
}

struct Sample {
    double S, sigma;
};

Sample sample_S(const Joint& p, int n, std::mt19937_64& rng) {
    std::uniform_real_distribution<double> U(0.0, 1.0);
    double S = 0.0, var = 0.0;
    for (int x = 0; x < 2; ++x)
        for (int y = 0; y < 2; ++y) {
            double sum = 0.0;
            for (int t = 0; t < n; ++t) {
                double u = U(rng), acc = 0.0;
                int ra = 0, rb = 0;
                bool done = false;
                for (int a = 0; a < 2 && !done; ++a)
                    for (int b = 0; b < 2 && !done; ++b) {
                        acc += p[x][y][a][b];
                        if (u <= acc) { ra = a; rb = b; done = true; }
                    }
                sum += sgn(ra) * sgn(rb);
            }
            const double Ehat = sum / n;
            const double sgnS = (x == 1 && y == 1) ? -1.0 : 1.0;
            S += sgnS * Ehat;
            var += (1.0 - Ehat * Ehat) / n;
        }
    return {S, std::sqrt(var)};
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    {
        const Joint s1 = deterministic(0, 0, 0, 0);
        const Joint s2 = deterministic(0, 1, 0, 0);
        tb::check("V1", "S = 2 for a(x) = +1, b(y) = +1", S_of(s1), 2.0, 1e-15);
        tb::check("V1", "S = 2 for a(x) = (-1)^x, b(y) = +1", S_of(s2), 2.0, 1e-15);
        tb::check("V1", "normalisation of the target", norm_err(target(0, PI / 2, PI / 4, 3 * PI / 4)), 0.0, 1e-15, false);
        tb::check("V1", "normalisation of the PR box", norm_err(pr_box()), 0.0, 1e-15, false);
    }

    tb::heading("T1 local deterministic strategies");
    {
        bool all = true;
        std::vector<Joint> strat;
        for (int a0 = 0; a0 < 2; ++a0)
            for (int a1 = 0; a1 < 2; ++a1)
                for (int b0 = 0; b0 < 2; ++b0)
                    for (int b1 = 0; b1 < 2; ++b1) {
                        const Joint p = deterministic(a0, a1, b0, b1);
                        const double S = S_of(p);
                        all = all && (std::fabs(std::fabs(S) - 2.0) < 1e-15);
                        strat.push_back(p);
                    }
        tb::check_true("T1", "all 16 deterministic strategies give S = +2 or -2", all && strat.size() == 16);
        std::mt19937_64 rng(20261110ULL);
        std::uniform_real_distribution<double> U(0.0, 1.0);
        double maxS = 0.0;
        for (int t = 0; t < 1000000; ++t) {
            // random convex mixture of 16 strategies by normalised exponentials; evaluate S linearly in the weights
            double w[16], tot = 0.0;
            for (int i = 0; i < 16; ++i) { w[i] = -std::log(U(rng) + 1e-300); tot += w[i]; }
            double S = 0.0;
            for (int i = 0; i < 16; ++i) S += (w[i] / tot) * S_of(strat[i]);
            maxS = std::fmax(maxS, std::fabs(S));
        }
        tb::note("largest |S| among 1e6 uniform random mixtures: %.9f", maxS);
        tb::check_true("T1", "no random mixture exceeds 2 (to 1e-12)", maxS <= 2.0 + 1e-12);
        tb::note("RECORDED REJECTION (run 1 criterion kept): uniform random mixtures do not approach the vertices");
        tb::check_true("T1", "the registered statement (largest of 1e6 uniform mixtures within 1e-3 of 2) is rejected", !(maxS >= 2.0 - 1e-3));
        double maxSparse = 0.0;
        for (int t = 0; t < 100000; ++t) {
            double w[16], tot = 0.0;
            for (int i = 0; i < 16; ++i) { w[i] = std::pow(U(rng), 20.0); tot += w[i]; }
            double S = 0.0;
            for (int i = 0; i < 16; ++i) S += (w[i] / tot) * S_of(strat[i]);
            maxSparse = std::fmax(maxSparse, std::fabs(S));
        }
        tb::note("largest |S| among 1e5 sparse mixtures: %.9f", maxSparse);
        tb::check_true("T1", "POST-RUN clause: sparse mixtures reach within 1e-3 of 2 and never exceed it", maxSparse >= 2.0 - 1e-3 && maxSparse <= 2.0 + 1e-12);
    }

    tb::heading("T2 other assumption sets");
    {
        const Joint tg = target(0, PI / 2, PI / 4, -PI / 4);  // run 2: corrected angle set (run 1 used 3 pi/4 and gave S = 0)
        const double S = S_of(tg);
        tb::note("target: S = %.12f ; 2 sqrt 2 = %.12f", S, 2.0 * std::sqrt(2.0));
        // sign of S: the target gives -2 sqrt 2 with E = -cos ; report |S|
        tb::check("T2", "target |S| = 2 sqrt 2", std::fabs(S), 2.0 * std::sqrt(2.0), 1e-12);
        double wm = 0.0;
        for (int a = 0; a < 2; ++a)
            for (int x = 0; x < 2; ++x) wm = std::fmax(wm, std::fabs(margA(tg, x, 0, a) - margA(tg, x, 1, a)));
        for (int b = 0; b < 2; ++b)
            for (int y = 0; y < 2; ++y) wm = std::fmax(wm, std::fabs(margB(tg, 0, y, b) - margB(tg, 1, y, b)));
        tb::check("T2", "target marginals are independent of the other station's setting (worst difference)", wm, 0.0, 1e-15, false);
        tb::check("T2", "target margin over the local limit is 2(sqrt 2 - 1)", std::fabs(S) - 2.0, 2.0 * (std::sqrt(2.0) - 1.0), 1e-12);
        const Joint pr = pr_box();
        double wmp = 0.0;
        for (int a = 0; a < 2; ++a)
            for (int x = 0; x < 2; ++x) wmp = std::fmax(wmp, std::fabs(margA(pr, x, 0, a) - margA(pr, x, 1, a)));
        for (int b = 0; b < 2; ++b)
            for (int y = 0; y < 2; ++y) wmp = std::fmax(wmp, std::fabs(margB(pr, 0, y, b) - margB(pr, 1, y, b)));
        tb::check("T2", "PR box |S| = 4", std::fabs(S_of(pr)), 4.0, 1e-15);
        tb::check("T2", "PR box marginals are independent of the other station's setting", wmp, 0.0, 1e-15, false);
        const Joint sg = signalling();
        double wms = 0.0;
        for (int a = 0; a < 2; ++a)
            for (int x = 0; x < 2; ++x) wms = std::fmax(wms, std::fabs(margA(sg, x, 0, a) - margA(sg, x, 1, a)));
        tb::note("signalling strategy: S = %.3f ; largest marginal difference of A between the two settings of B = %.3f", S_of(sg), wms);
        tb::check("T2", "signalling strategy |S| = 4", std::fabs(S_of(sg)), 4.0, 1e-15);
        tb::check("T2", "signalling strategy: marginal of A depends on B's setting (difference 1)", wms, 1.0, 1e-15);
    }

    tb::heading("T3 timing: the speed a relay would need");
    {
        const double c = 299792458.0;
        bool ok = true;
        for (double D : {10.0, 400.0, 1300.0})
            for (double dl : {1e-9, 100e-9, 10e-6}) {
                const double vmin = D / dl;
                const bool in_time_at_c = D <= c * dl;
                tb::note("D = %6.0f m, delta = %.0e s: v_min/c = %.4e ; a relay at c can carry the setting in time: %s", D, dl, vmin / c, in_time_at_c ? "yes" : "no");
                const bool expected = (D == 10.0 && dl >= 100e-9) || (D == 400.0 && dl >= 10e-6) || (D == 1300.0 && dl >= 10e-6);
                ok = ok && (in_time_at_c == expected);
            }
        tb::check_true("T3", "a relay at v = c carries the setting in time exactly in the registered cells", ok);
    }

    tb::heading("T4 protocol: sampled data");
    {
        std::mt19937_64 rng(20261110ULL);
        const int n = 1000;
        const Joint tg = target(0, PI / 2, PI / 4, -PI / 4);
        const Sample st = sample_S(tg, n, rng);
        tb::note("sampled target: S = %.5f +/- %.5f ; |S| - 2 = %.2f sigma", st.S, st.sigma, (std::fabs(st.S) - 2.0) / st.sigma);
        tb::check_true("T4", "target: |S| within 4 sigma of 2 sqrt 2", std::fabs(std::fabs(st.S) - 2.0 * std::sqrt(2.0)) <= 4.0 * st.sigma);
        tb::check_true("T4", "target: |S| exceeds 2 by at least 10 sigma", std::fabs(st.S) - 2.0 >= 10.0 * st.sigma);
        const Joint loc = mix(deterministic(0, 0, 0, 0), deterministic(0, 1, 0, 0), 0.5);
        const Sample sl = sample_S(loc, n, rng);
        tb::note("sampled local mixture: S = %.5f +/- %.5f", sl.S, sl.sigma);
        tb::check_true("T4", "local mixture: S within 4 sigma of 2", std::fabs(sl.S - 2.0) <= 4.0 * sl.sigma);
        const double need = 2.0 * std::pow(5.0 / (2.0 * std::sqrt(2.0) - 2.0), 2.0);
        tb::note("trials per pair for a 5 sigma separation: %.2f", need);
        tb::check_true("T4", "the trials per pair needed for 5 sigma lies in [72, 74]", need >= 72.0 && need <= 74.0);
    }

    return tb::finish();
}
