// Chapter 41 — the Spaz state and Sz: worked-example instrument (generic test functions).
// Pre-registration: Textbook/validation/ch41_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <cstdint>
#include <functional>
#include <vector>

namespace {

using F = std::function<double(double)>;

double dln(const F& q, double s) {
    auto g = [&](double h) { return (std::log(q(s + h)) - std::log(q(s - h))) / (2.0 * h); };
    return (4.0 * g(0.5e-3) - g(1e-3)) / 3.0;
}

struct Rng {
    std::uint64_t s;
    double next() {
        s = s * 6364136223846793005ULL + 1442695040888963407ULL;
        return static_cast<double>(s >> 11) * (1.0 / 9007199254740992.0);
    }
};

// random positive smooth function exp(a1 S + a2 sin(b S + p))
F rnd(Rng& g) {
    const double a1 = 2.0 * g.next() - 1.0, a2 = 0.5 * g.next(), b = 0.5 + 2.0 * g.next(), p = 6.0 * g.next();
    return [=](double s) { return std::exp(a1 * s + a2 * std::sin(b * s + p)); };
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 log-derivative known answers");
    {
        tb::check("V1", "d ln e^{2S}/dS = 2", dln([](double s) { return std::exp(2 * s); }, 0.7), 2.0, 1e-8);
        tb::check("V1", "d ln S^3/dS at S = 2 is 3/2", dln([](double s) { return s * s * s; }, 2.0), 1.5, 1e-8);
    }

    tb::heading("T1 reparameterisation: ratios invariant, derivatives transform by 1/f'");
    {
        const F Q = [](double s) { return std::exp(0.7 * s + 0.2 * std::sin(3.0 * s)); };
        const F f = [](double s) { return s + 0.3 * s * s * s; };
        const F fp = [](double s) { return 1.0 + 0.9 * s * s; };
        const double S0 = 0.1;
        // inverse of f by Newton
        auto finv = [&](double y) { double s = y; for (int i = 0; i < 100; ++i) { const double d = (f(s) - y) / fp(s); s -= d; if (std::fabs(d) < 1e-15) break; } return s; };
        const F Qp = [&](double y) { return Q(finv(y)); };  // Q as a function of S' = f(S)
        double wr = 0.0, wd = 0.0;
        for (int i = 0; i < 50; ++i) {
            const double s = 0.1 + 1.4 * i / 49.0;
            wr = std::fmax(wr, std::fabs(Qp(f(s)) / Qp(f(S0)) / (Q(s) / Q(S0)) - 1.0));
            const double a = dln(Q, s), ap = dln(Qp, f(s));
            wd = std::fmax(wd, std::fabs(ap / (a / fp(s)) - 1.0));
        }
        tb::check("T1", "ratio Q(S)/Q(S0) computed in S' equals the original, worst relative", wr, 0.0, 1e-14, false);
        tb::check("T1", "d ln Q/dS' = (d ln Q/dS)/f', worst relative", wd, 0.0, 1e-7, false);
    }

    tb::heading("T2 compatibility relations among log-derivatives");
    {
        Rng g{41};
        double w1 = 0, w2 = 0, w3 = 0;
        for (int rep = 0; rep < 20; ++rep) {
            const F Pl = rnd(g), Pt = rnd(g), r = rnd(g), Om = rnd(g), cc = rnd(g);
            const double s = 0.05 + 0.1 * rep;
            const F ratio = [&](double x) { return Pl(x) / Pt(x); };
            w1 = std::fmax(w1, std::fabs(dln(ratio, s) - (dln(Pl, s) - dln(Pt, s))));
            const F k = [&](double x) { return std::sqrt(r(x) / Om(x)); };
            w2 = std::fmax(w2, std::fabs(dln(k, s) - 0.5 * (dln(r, s) - dln(Om, s))));
            const F v = [&](double x) { return cc(x) / k(x); };
            w3 = std::fmax(w3, std::fabs(dln(v, s) - (dln(cc, s) - dln(k, s))));
        }
        tb::check("T2", "a_c = a_Pl - a_Pt, worst deviation", w1, 0.0, 1e-7, false);
        tb::check("T2", "2 a_k = a_r - a_Om, worst deviation", w2, 0.0, 1e-7, false);
        tb::check("T2", "a_v = a_c - a_k, worst deviation", w3, 0.0, 1e-7, false);
    }

    tb::heading("T3 compatibility leaves constitutive freedom");
    {
        double worst = 0.0;
        for (int i = 0; i <= 40; ++i) {
            const double s = 0.05 * i;
            const double cA = std::exp(s) / std::exp(0.5 * s), cB = std::exp(2.0 * s) / std::exp(1.5 * s);
            worst = std::fmax(worst, std::fabs(cA / cB - 1.0));
        }
        tb::check("T3", "routes A and B give the same c = e^{S/2}, worst relative difference", worst, 0.0, 1e-14, false);
        tb::check("T3", "a_Pl differs between the routes (1 and 2)", dln([](double s) { return std::exp(2 * s); }, 0.3) - dln([](double s) { return std::exp(s); }, 0.3), 1.0, 1e-7);
    }

    tb::heading("T4 charts: logarithm fails at zeros, the signed chart does not add");
    {
        int fail = 0, fin = 0;
        for (int i = 0; i < 1000; ++i) {
            const double s = 0.1 + 6.1 * i / 999.0, q = std::sin(s);
            if (!(q > 0.0)) ++fail;
            if (std::isfinite(std::asinh(q / 0.5))) ++fin;
        }
        tb::note("logarithmic chart fails at %d of 1000 points ; sinh^-1 chart finite at %d", fail, fin);
        tb::check_true("T4", "the logarithmic chart fails at some points and the sinh^-1 chart at none", fail > 0 && fin == 1000);
        double wl = 0.0, wa = 0.0;
        for (int i = 0; i < 200; ++i) {
            const double A = 0.2 + 4.0 * i / 199.0, B = 0.3 + 3.0 * (199 - i) / 199.0;
            wl = std::fmax(wl, std::fabs(std::log(A * B) - std::log(A) - std::log(B)));
            wa = std::fmax(wa, std::fabs(std::asinh(A * B) - std::asinh(A) - std::asinh(B)));
        }
        tb::check("T4", "ln(AB) = ln A + ln B, worst deviation", wl, 0.0, 1e-14, false);
        tb::note("largest violation of additivity for sinh^-1: %.4f", wa);
        tb::check_true("T4", "sinh^-1 additivity is violated by more than 1e-2 somewhere", wa > 1e-2);
    }

    tb::heading("T5 Sz spacing is not a law");
    {
        const double k = 0.8;
        auto cv = [](const std::vector<double>& v) { double m = 0; for (double x : v) m += x; m /= v.size(); double s = 0; for (double x : v) s += (x - m) * (x - m); return std::sqrt(s / v.size()) / std::fabs(m); };
        std::vector<double> a, ap;
        for (int i = 0; i < 200; ++i) {
            const double Sp = 0.5 + 8.5 * i / 199.0;
            const F Q = [&](double s) { return std::exp(-k * s); };
            a.push_back(dln(Q, 1.0 + 0.01 * i));
            ap.push_back(-k / (2.0 * std::sqrt(Sp)));
        }
        const double cva = cv(a), cvp = cv(ap);
        tb::note("coefficient of variation of the log-derivative: in S %.2e ; in S' = S^2 %.3f", cva, cvp);
        tb::check_true("T5", "constant in S (to 1e-8) and not constant in S' (variation above 0.3)", cva < 1e-8 && cvp > 0.3);
    }

    return tb::finish();
}
