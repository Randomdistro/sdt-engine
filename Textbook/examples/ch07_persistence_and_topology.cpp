// Chapter 7 — persistence and topology: worked-example instrument.
// Pre-registration: Textbook/validation/ch07_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch07_persistence_and_topology
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <numeric>
#include <string>
#include <vector>

namespace {

using Poly = std::vector<long long>;  // coefficient of t^i at index i

Poly trim(Poly p) {
    while (!p.empty() && p.back() == 0) p.pop_back();
    return p;
}

Poly pmul(const Poly& a, const Poly& b) {
    Poly r(a.size() + b.size() - 1, 0);
    for (std::size_t i = 0; i < a.size(); ++i)
        for (std::size_t j = 0; j < b.size(); ++j) r[i + j] += a[i] * b[j];
    return trim(r);
}

// Exact division by a polynomial with leading coefficient +-1. Returns false if the remainder is not zero.
bool pdiv(Poly num, const Poly& den, Poly& quot) {
    num = trim(num);
    const Poly d = trim(den);
    const long long lead = d.back();
    if (lead != 1 && lead != -1) return false;
    if (num.size() < d.size()) {
        quot.clear();
        return num.empty();
    }
    quot.assign(num.size() - d.size() + 1, 0);
    for (std::size_t k = num.size(); k-- >= d.size();) {
        if (k + 1 < d.size()) break;
        const long long c = num[k] / lead;
        const std::size_t shift = k + 1 - d.size();
        quot[shift] = c;
        for (std::size_t j = 0; j < d.size(); ++j) num[shift + j] -= c * d[j];
        if (k + 1 == d.size()) break;
    }
    return trim(num).empty();
}

Poly tpow_minus_one(int n) {  // t^n - 1
    Poly p(n + 1, 0);
    p[n] = 1;
    p[0] = -1;
    return p;
}

// Alexander polynomial of the torus knot T(p,q), gcd = 1, normalised to non-zero constant term and positive lead.
bool alexander(int p, int q, Poly& out) {
    const Poly N = pmul(tpow_minus_one(p * q), tpow_minus_one(1));
    const Poly D = pmul(tpow_minus_one(p), tpow_minus_one(q));
    Poly r;
    if (!pdiv(N, D, r)) return false;
    r = trim(r);
    std::size_t lo = 0;
    while (lo < r.size() && r[lo] == 0) ++lo;
    r.erase(r.begin(), r.begin() + static_cast<std::ptrdiff_t>(lo));
    if (!r.empty() && r.back() < 0)
        for (long long& c : r) c = -c;
    out = r;
    return true;
}

std::string show(const Poly& p) {
    std::string s = "[";
    for (std::size_t i = 0; i < p.size(); ++i) s += (i ? "," : "") + std::to_string(p[i]);
    return s + "]";
}

double peval(const Poly& p, double t) {
    double v = 0.0;
    for (std::size_t i = p.size(); i-- > 0;) v = v * t + static_cast<double>(p[i]);
    return v;
}

}  // namespace

int main() {
    namespace L = sdt::laws;
    namespace Tp = sdt::laws::law_VI::topology;
    tb::validate_helpers();

    tb::heading("V1 polynomial division");
    {
        Poly q;
        tb::check_true("V1", "(t^2-1)/(t-1) = t+1 exactly", pdiv(tpow_minus_one(2), tpow_minus_one(1), q) && q == Poly{1, 1});
        tb::check_true("V1", "(t^6-1)/(t^2-1) = t^4+t^2+1 exactly",
                       pdiv(tpow_minus_one(6), tpow_minus_one(2), q) && q == Poly{1, 0, 1, 0, 1});
        tb::check_true("V1", "(t^5-1)/(t^2-1) has a non-zero remainder and is reported as inexact",
                       !pdiv(tpow_minus_one(5), tpow_minus_one(2), q));
    }
    tb::heading("V2 formula against tabulated Alexander polynomials");
    {
        Poly a;
        tb::check_true("V2", "trefoil T(2,3): t^2 - t + 1", alexander(2, 3, a) && a == Poly{1, -1, 1});
        tb::check_true("V2", "cinquefoil T(2,5): t^4 - t^3 + t^2 - t + 1", alexander(2, 5, a) && a == Poly{1, -1, 1, -1, 1});
        tb::check_true("V2", "T(3,4) (8_19): t^6 - t^5 + t^3 - t + 1", alexander(3, 4, a) && a == Poly{1, -1, 0, 1, 0, -1, 1});
    }

    tb::heading("T1 unknot modes (1,q)");
    {
        bool ok = true;
        for (int q = 1; q <= 12; ++q) {
            Poly a;
            ok = ok && alexander(1, q, a) && a == Poly{1};
        }
        tb::check_true("T1", "Delta_{1,q} = 1 for q = 1..12", ok);
    }

    tb::heading("T2 the proton mode (2,3) and the engine's quoted polynomial");
    {
        Poly a23, a25;
        alexander(2, 3, a23);
        alexander(2, 5, a25);
        const Poly quoted{1, -1, 1, -1, 1};  // t^-2 - t^-1 + 1 - t + t^2 read as coefficients of a degree-4 polynomial
        tb::check_true("T2", "Delta_{2,3} = [1,-1,1] and is not 1", a23 == Poly{1, -1, 1});
        tb::check_true("T2", "the polynomial quoted in the header equals Delta_{2,5}", quoted == a25);
        tb::check_true("T2", "the polynomial quoted in the header differs from Delta_{2,3}", quoted != a23);
        tb::note("Delta_{2,3} = %s ; Delta_{2,5} = %s ; quoted = %s", show(a23).c_str(), show(a25).c_str(), show(quoted).c_str());
    }

    tb::heading("T3 structure of Delta_{p,q} for coprime 2 <= p < q <= 12");
    {
        int pairs = 0, bad = 0;
        for (int p = 2; p <= 11; ++p)
            for (int q = p + 1; q <= 12; ++q) {
                if (std::gcd(p, q) != 1) continue;
                ++pairs;
                Poly a;
                const bool ok_div = alexander(p, q, a);
                bool ok = ok_div && a != Poly{1} && static_cast<int>(a.size()) - 1 == (p - 1) * (q - 1);
                if (ok) {
                    for (std::size_t i = 0; i < a.size(); ++i) ok = ok && a[i] == a[a.size() - 1 - i];
                    long long at1 = 0, atm1 = 0;
                    for (std::size_t i = 0; i < a.size(); ++i) {
                        at1 += a[i];
                        atm1 += (i % 2 ? -a[i] : a[i]);
                    }
                    ok = ok && at1 == 1 && (std::llabs(atm1) % 2 == 1);
                }
                if (!ok) {
                    ++bad;
                    tb::note("structure fails for (%d,%d)", p, q);
                }
            }
        tb::check_true("T3", ("all " + std::to_string(pairs) + " coprime pairs: Delta != 1, degree (p-1)(q-1), palindromic, Delta(1) = 1, |Delta(-1)| odd").c_str(),
                       pairs > 0 && bad == 0);
    }

    tb::heading("T4 crossing change connects trefoil and unknot");
    {
        Poly a23;
        alexander(2, 3, a23);  // t^2 - t + 1  ->  Delta(t)/t = t - 1 + 1/t
        double worst = 0.0, skein_worst = 0.0;
        for (double t : {0.5, 2.0, 3.7}) {
            const double z = std::sqrt(t) - 1.0 / std::sqrt(t);
            const double nabla_tref = 1.0 + z * z;
            worst = std::fmax(worst, std::fabs(peval(a23, t) / t - nabla_tref));
            const double nabla_plus = nabla_tref, nabla_minus = 1.0, nabla_zero = z;
            skein_worst = std::fmax(skein_worst, std::fabs((nabla_plus - nabla_minus) - z * nabla_zero));
        }
        tb::check("T4", "Conway polynomial 1+z^2 of the trefoil equals Delta_{2,3}(t)/t (worst of 3)", worst, 0.0, 1e-13, false);
        tb::check("T4", "skein relation nabla_+ - nabla_- = z nabla_0 for (trefoil, unknot, Hopf) (worst of 3)", skein_worst, 0.0, 1e-13, false);
    }

    tb::heading("T5 movement budget over the mode formulas");
    {
        const double c = L::measured::c;
        double worst_budget = 0.0, worst_form = 0.0;
        for (int p = 1; p <= 12; ++p)
            for (int q = 1; q <= 12; ++q) {
                const double vt = Tp::v_toroidal(p, q), vp = Tp::v_poloidal(p, q);
                worst_budget = std::fmax(worst_budget, std::fabs(Tp::budget_residual(p, q) - 1.0));
                worst_budget = std::fmax(worst_budget, std::fabs((vt * vt + vp * vp) / (c * c) - 1.0));
                worst_form = std::fmax(worst_form, std::fabs(vt / (c * std::sqrt(double(p) / (p + q))) - 1.0));
                worst_form = std::fmax(worst_form, std::fabs(vp / (c * std::sqrt(double(q) / (p + q))) - 1.0));
                worst_form = std::fmax(worst_form, std::fabs(Tp::aspect_ratio(p, q) / std::sqrt(double(q) / p) - 1.0));
            }
        tb::check("T5", "budget residual (v_T^2+v_P^2)/c^2 - 1, worst over 144 modes", worst_budget, 0.0, 1e-15, false);
        tb::check("T5", "mode formulas vs closed forms, worst relative over 144 modes", worst_form, 0.0, 1e-15, false);
        tb::check("T5", "electron (1,1): v_T = c/sqrt2", Tp::v_toroidal(Tp::electron_p, Tp::electron_q) / c, 1.0 / std::numbers::sqrt2, 1e-15);
        tb::check("T5", "electron (1,1): v_P = c/sqrt2", Tp::v_poloidal(Tp::electron_p, Tp::electron_q) / c, 1.0 / std::numbers::sqrt2, 1e-15);
        tb::check("T5", "proton (2,3): v_T / c = 0.632456", Tp::v_toroidal(Tp::proton_p, Tp::proton_q) / c, std::sqrt(0.4), 1e-6);
        tb::check("T5", "proton (2,3): v_P / c = 0.774597", Tp::v_poloidal(Tp::proton_p, Tp::proton_q) / c, std::sqrt(0.6), 1e-6);
        tb::note("aspect ratios R/a: electron %.6f, proton %.6f", Tp::aspect_ratio(1, 1), Tp::aspect_ratio(2, 3));
    }

    tb::heading("T6 smoothing rates of the engine");
    {
        namespace Cf = sdt::laws::law_VI::confinement;
        const int p = Tp::proton_p, q = Tp::proton_q;
        const double vT = Tp::v_toroidal(p, q), vP = Tp::v_poloidal(p, q);
        const double R = 1.0, a = R / Tp::aspect_ratio(p, q);
        double worst = 0.0;
        bool positive = true;
        for (int n = 1; n <= 6; ++n) {
            worst = std::fmax(worst, std::fabs(Cf::harmonic_rate_sq(0, n, vT, R, vP, a) / Cf::harmonic_rate_sq(0, 1, vT, R, vP, a) / (double(n) * n) - 1.0));
            worst = std::fmax(worst, std::fabs(Cf::harmonic_rate_sq(n, 0, vT, R, vP, a) / Cf::harmonic_rate_sq(1, 0, vT, R, vP, a) / (double(n) * n) - 1.0));
        }
        for (int m = 0; m <= 6; ++m)
            for (int n = 0; n <= 6; ++n)
                if ((m || n) && !(Cf::harmonic_rate_sq(m, n, vT, R, vP, a) > 0.0)) positive = false;
        tb::check("T6", "omega^2_{0,n}/omega^2_{0,1} = n^2 and omega^2_{m,0}/omega^2_{1,0} = m^2 (worst relative)", worst, 0.0, 1e-14, false);
        tb::check_true("T6", "omega^2_{m,n} > 0 for (m,n) != (0,0)", positive);
        tb::check_true("T6", "omega^2_{0,0} = 0 (the uniform mode is a symmetry direction)", Cf::harmonic_rate_sq(0, 0, vT, R, vP, a) == 0.0);
    }

    return tb::finish();
}
