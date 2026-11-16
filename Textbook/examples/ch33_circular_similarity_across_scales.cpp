// Chapter 33 — circular similarity across scales: worked-example instrument.
// Pre-registration: Textbook/validation/ch33_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <vector>

namespace {
constexpr double kPi = std::numbers::pi;
}

int main() {
    namespace M = sdt::laws::measured;
    namespace A = sdt::laws::atomic;
    namespace B = sdt::laws::bridge;
    tb::validate_helpers();
    const double c = M::c;

    tb::heading("V1 illustrative values at x = 4");
    {
        const double x = 4.0;
        tb::check("V1", "v/c = x^(-1/2) = 1/2", std::pow(x, -0.5), 0.5, 1e-14);
        tb::check("V1", "a Om/c^2 = x^-2 = 1/16", std::pow(x, -2.0), 1.0 / 16.0, 1e-14);
        tb::check("V1", "P c/Om = 2 pi x^(3/2) = 16 pi", 2.0 * kPi * std::pow(x, 1.5), 16.0 * kPi, 1e-14);
    }

    struct Sys { const char* name; double r, v; };
    std::vector<Sys> systems;
    systems.push_back({"H n=1", A::bohr_radius(1, 1), A::bohr_velocity(1, 1)});
    systems.push_back({"Earth surface", B::R_Earth, B::v_Earth});
    const double AU = M::AU, day = 86400.0;
    struct Pl { const char* n; double a_AU, T_d; };
    const Pl planets[6] = {{"Mercury", 0.38709927, 87.9691}, {"Venus", 0.72333566, 224.7008}, {"Earth", 1.00000261, 365.25636}, {"Mars", 1.52371034, 686.9801}, {"Jupiter", 5.20288700, 4332.589}, {"Saturn", 9.53667594, 10759.22}};
    for (const auto& p : planets) {
        const double a = p.a_AU * AU, T = p.T_d * day;
        systems.push_back({p.n, a, 2.0 * kPi * a / T});
    }
    const double a_moon = 3.844e8, T_moon = 27.321661 * day;
    systems.push_back({"Moon orbit", a_moon, 2.0 * kPi * a_moon / T_moon});

    tb::heading("T1 master relations");
    {
        double worst = 0.0;
        for (const auto& s : systems) {
            const double Om = s.v * s.v * s.r / (c * c), x = s.r / Om, acc = s.v * s.v / s.r, P = 2.0 * kPi * s.r / s.v;
            worst = std::fmax(worst, std::fabs(s.v / c / std::pow(x, -0.5) - 1.0));
            worst = std::fmax(worst, std::fabs(acc * Om / (c * c) / std::pow(x, -2.0) - 1.0));
            worst = std::fmax(worst, std::fabs(P * c / Om / (2.0 * kPi * std::pow(x, 1.5)) - 1.0));
            tb::note("%-14s r = %.6e m ; Om = %.6e m ; x = %.4e ; v/c = %.4e", s.name, s.r, Om, x, s.v / c);
        }
        tb::check("T1", "three master relations, worst relative over all system points", worst, 0.0, 1e-12, false);
    }

    tb::heading("T2 hydrogen ladder");
    {
        double w = 0.0;
        for (int n = 1; n <= 8; ++n) w = std::fmax(w, std::fabs(A::bohr_velocity(1, n) * A::bohr_velocity(1, n) * A::bohr_radius(1, n) / (c * c) / M::r_e - 1.0));
        tb::check("T2", "Om_n = r_e for n = 1..8 (shared-input), worst relative", w, 0.0, 1e-14, false);
    }

    tb::heading("T3 the Sun's planets");
    {
        std::vector<double> Om, lnx;
        for (const auto& p : planets) {
            const double a = p.a_AU * AU, T = p.T_d * day, v = 2.0 * kPi * a / T;
            const double om = v * v * a / (c * c);
            Om.push_back(om);
            lnx.push_back(std::log(a / om));
            tb::note("%-8s Om = %.6f m", p.n, om);
        }
        double mn = 1e300, mx = 0.0, mean = 0.0;
        for (double o : Om) { mn = std::fmin(mn, o); mx = std::fmax(mx, o); mean += o / 6.0; }
        const double spread = mx / mn - 1.0;
        // slope of ln Om against ln x (least squares)
        double sx = 0, sy = 0, sxx = 0, sxy = 0;
        for (int i = 0; i < 6; ++i) { const double y = std::log(Om[i]); sx += lnx[i]; sy += y; sxx += lnx[i] * lnx[i]; sxy += lnx[i] * y; }
        const double slope = (6.0 * sxy - sx * sy) / (6.0 * sxx - sx * sx);
        tb::note("mean Om_sun = %.6f m ; spread (max/min - 1) = %.3e ; slope d ln Om/d ln x = %.3e", mean, spread, slope);
        tb::check_true("T3", "spread of Om over the six planets is at most 2e-3", spread <= 2e-3);
        tb::check_true("T3", "|slope of ln Om against ln x| is below 1e-4", std::fabs(slope) < 1e-4);
    }

    tb::heading("T4 Earth: surface against lunar orbit");
    {
        const double OmS = B::v_Earth * B::v_Earth * B::R_Earth / (c * c);
        const double v = 2.0 * kPi * a_moon / T_moon, OmM = v * v * a_moon / (c * c);
        tb::note("Om_Earth (surface) = %.6e m, x = %.4e ; Om_Earth (lunar orbit) = %.6e m, x = %.4e ; ratio %.5f", OmS, B::R_Earth / OmS, OmM, a_moon / OmM, OmM / OmS);
        tb::check_true("T4", "ratio of the two determinations lies in [0.98, 1.02]", OmM / OmS > 0.98 && OmM / OmS < 1.02);
    }

    tb::heading("T5 logarithmic derivative of the circular speed");
    {
        const double c0 = 3.0, Om0 = 2.0, r0 = 5.0;
        auto cc = [&](double S) { return c0 * (1.0 + 0.3 * S); };
        auto om = [&](double S) { return Om0 * std::exp(0.2 * S); };
        auto rr = [&](double S) { return r0 * (1.0 + S * S); };
        auto lv = [&](double S) { return std::log(cc(S) * std::sqrt(om(S) / rr(S))); };
        const double S = 0.4, h = 1e-5;
        const double lhs = (lv(S + h) - lv(S - h)) / (2 * h);
        const double rhs = 0.3 / (1.0 + 0.3 * S) + 0.5 * 0.2 - 0.5 * (2.0 * S / (1.0 + S * S));
        tb::check("T5", "d ln v/dS = d ln c/dS + (1/2) d ln Om/dS - (1/2) d ln r/dS", lhs, rhs, 1e-8);
    }

    tb::heading("T6 hydrogen boundary and the proton radii");
    {
        const double ratio1 = M::r_e / M::R_p, ratio2 = M::r_e / sdt::laws::law_III::R_p_lock;
        tb::note("r_e/R_p = %.5f ; Om_H/R_p,lock = %.5f", ratio1, ratio2);
        tb::check_true("T6", "neither ratio is 1 (Om_H and the proton radii are distinct objects)", std::fabs(ratio1 - 1.0) > 0.5 && std::fabs(ratio2 - 1.0) > 0.5);
    }

    return tb::finish();
}
