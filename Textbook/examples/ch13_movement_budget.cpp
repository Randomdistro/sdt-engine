// Chapter 13 — movement budget: worked-example instrument.
// Pre-registration: Textbook/validation/ch13_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch13_movement_budget
#include <sdt/laws.hpp>
#include <sdt/occlusion_sphere.hpp>
#include <sdt/sphere_frame.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <functional>

namespace {

constexpr double kPi = std::numbers::pi;

double central_diff(const std::function<double(double)>& f, double x, double h) { return (f(x + h) - f(x - h)) / (2.0 * h); }

}  // namespace

int main() {
    namespace L = sdt::laws;
    namespace M = sdt::laws::measured;
    namespace V = sdt::laws::law_V;
    namespace DC = sdt::laws::depth_closure;
    namespace S = sdt::sphere;
    namespace OS = sdt::occlusion_sphere;
    tb::validate_helpers();

    const double c = M::c, m0 = 3.7;  // m0 is arbitrary: every relation below is linear in it
    const double E0 = m0 * c * c;
    const double betas[] = {0.0, 0.1, 0.6, 0.8, 0.99, 0.9999};

    tb::heading("V1 Pythagorean fixtures (instrument arithmetic)");
    {
        auto chi = [](double b) { return std::sqrt((1.0 - b) * (1.0 + b)); };
        tb::check("V1", "beta = 0.6: chi = 0.8", chi(0.6), 0.8, 1e-15);
        tb::check("V1", "beta = 0.6: gamma = 1.25", 1.0 / chi(0.6), 1.25, 1e-15);
        tb::check("V1", "beta = 0.8: chi = 0.6", chi(0.8), 0.6, 1e-15);
        tb::check("V1", "beta = 0.8: gamma = 5/3", 1.0 / chi(0.8), 5.0 / 3.0, 1e-15);
        tb::check("V1", "beta = 0: chi = 1", chi(0.0), 1.0, 1e-15);
    }
    tb::heading("V2 central-difference routine");
    tb::check("V2", "d/dx x^3 at 2 = 12", central_diff([](double x) { return x * x * x; }, 2.0, 1e-3), 12.0, 1e-6);
    tb::check("V2", "d/dx sin at 0.7 = cos 0.7", central_diff([](double x) { return std::sin(x); }, 0.7, 1e-4), std::cos(0.7), 1e-8);

    tb::heading("T1 chi, clock fraction, gamma, energy, momentum, invariant");
    {
        double w_vc = 0, w_td = 0, w_g = 0, w_E = 0, w_p = 0, w_inv = 0;
        for (double b : betas) {
            const double v = b * c, chi = std::sqrt((1.0 - b) * (1.0 + b)), g = 1.0 / chi;
            w_vc = std::fmax(w_vc, std::fabs(V::v_circ(v) / (chi * c) - 1.0));
            w_td = std::fmax(w_td, std::fabs(V::time_dilation(v) / chi - 1.0));
            w_g = std::fmax(w_g, std::fabs(V::gamma(v) / g - 1.0));
            w_E = std::fmax(w_E, std::fabs(V::total_energy(m0, v) / (g * E0) - 1.0));
            if (b > 0.0) w_p = std::fmax(w_p, std::fabs(V::momentum(m0, v) / (g * m0 * v) - 1.0));
            const double E = V::total_energy(m0, v), p = V::momentum(m0, v);
            const double inv = (E * E - c * c * p * p) / (E0 * E0) - 1.0;
            w_inv = std::fmax(w_inv, std::fabs(inv));
            tb::note("beta = %-7g chi = %.12f  gamma = %.10f  E/E0 = %.10f  p/(m0 c) = %.10f  invariant residual %.2e", b, chi, V::gamma(v),
                     E / E0, p / (m0 * c), inv);
        }
        tb::check("T1", "v_circ / (chi c) - 1, worst over 6 beta", w_vc, 0.0, 1e-10, false);
        tb::check("T1", "time_dilation / chi - 1, worst", w_td, 0.0, 1e-10, false);
        tb::check("T1", "gamma / (1/chi) - 1, worst", w_g, 0.0, 1e-10, false);
        tb::check("T1", "total_energy / (gamma E0) - 1, worst", w_E, 0.0, 1e-10, false);
        tb::check("T1", "momentum / (gamma m0 v) - 1, worst (beta > 0)", w_p, 0.0, 1e-10, false);
        tb::check("T1", "(E^2 - c^2 p^2)/E0^2 - 1, worst", w_inv, 0.0, 1e-9, false);
    }

    tb::heading("T2 round-trip closure and longitudinal contraction");
    {
        double worst = 0.0, worst_t = 0.0;
        for (double b : betas) {
            const double v = b * c, g = V::gamma(v), L0 = 2.5;
            const double L = L0 / g;
            const double Tround = 2.0 * L0 * c / (c * c - v * v);   // extent L0 as seen in the reference frame with the contracted partner
            worst_t = std::fmax(worst_t, std::fabs(Tround / (2.0 * L0 * g * g / c) - 1.0));
            // synchronisation T_round = gamma T_round,0 with T_round = 2 L gamma^2 / c  =>  L = L0 / gamma
            const double L_sync = (g * (2.0 * L0 / c)) / (2.0 * g * g / c);
            worst = std::fmax(worst, std::fabs(L_sync / V::length_contraction(L0, v) - 1.0));
            worst = std::fmax(worst, std::fabs(L / V::length_contraction(L0, v) - 1.0));
        }
        tb::check("T2", "T_round = 2 L c /(c^2 - v^2) = 2 L gamma^2 / c, worst relative", worst_t, 0.0, 1e-12, false);
        tb::check("T2", "L from synchronisation vs law_V::length_contraction, worst relative", worst, 0.0, 1e-12, false);
    }

    tb::heading("T3 kinetic energy: cancellation-free form and series");
    {
        double worst = 0.0;
        for (double b : {0.01, 0.1, 0.6, 0.8, 0.99}) {
            const double g = 1.0 / std::sqrt((1.0 - b) * (1.0 + b));
            const double direct = (g - 1.0), free = g * g * b * b / (g + 1.0);
            worst = std::fmax(worst, std::fabs(direct / free - 1.0));
        }
        tb::check("T3", "(gamma - 1) vs gamma^2 beta^2/(gamma + 1), beta >= 0.01 (worst relative)", worst, 0.0, 1e-9, false);
        {
            const double b = 0.01, g = 1.0 / std::sqrt((1.0 - b) * (1.0 + b));
            const double free = g * g * b * b / (g + 1.0), series = b * b / 2.0 + 3.0 * std::pow(b, 4) / 8.0 + 5.0 * std::pow(b, 6) / 16.0;
            const double next = 35.0 * std::pow(b, 8) / 128.0;
            tb::check("T3", "(K/E0 - three-term series) equals the next term 35 b^8/128 at beta = 0.01", free - series, next, 1e-2);
            tb::check("T3", "four-term series vs K/E0 at beta = 0.01", series + next, free, 1e-14);
        }
        {
            const double b = 1e-4, g = 1.0 / std::sqrt((1.0 - b) * (1.0 + b));
            const double direct = g - 1.0, free = g * g * b * b / (g + 1.0);
            const double loss = std::fabs(direct / free - 1.0);
            tb::note("beta = 1e-4: (gamma - 1) = %.12e ; cancellation-free = %.12e ; relative difference %.2e", direct, free, loss);
            tb::check_true("T3", "the direct form loses at least 4 digits at beta = 1e-4", loss > 1e-12);
        }
    }

    tb::heading("T4 directional response (spherical loci)");
    {
        double w_mag = 0.0, w_head = 0.0, w_special = 0.0;
        for (double b : {0.1, 0.6, 0.8, 0.99}) {
            const double chi = std::sqrt((1.0 - b) * (1.0 + b));
            const S::Locus vel(b * c, 1.1, 0.9);
            const S::Direction along = S::unit(vel);
            for (double deg : {0.0, 45.0, 90.0, 135.0, 180.0}) {
                const double psi = deg * kPi / 180.0;
                const double A = 2.5;
                S::Vector acc;
                if (deg == 0.0) acc = along;
                else if (deg == 180.0) acc = S::antipode(along);
                else acc = S::offset_direction(along, psi, 0.7);
                acc = S::scaled(acc, A);  // radius A
                S::Vector out;
                if (deg == 0.0) out = OS::law_v_response(S::Vector{S::Locus{A, along.theta(), along.phi()}}, S::Vector{vel});
                else out = OS::law_v_response(acc, S::Vector{vel});
                if (!out) {
                    w_mag = 1.0;
                    continue;
                }
                const double mag_exp = A * std::sqrt(std::pow(chi, 6) * std::cos(psi) * std::cos(psi) + chi * chi * std::sin(psi) * std::sin(psi));
                w_mag = std::fmax(w_mag, std::fabs(out->radius() / mag_exp - 1.0));
                if (deg != 0.0 && deg != 180.0) {
                    const double head = S::separation(*out, along);
                    const double head_exp = std::atan2(chi * std::sin(psi), std::pow(chi, 3) * std::cos(psi));
                    w_head = std::fmax(w_head, std::fabs(head - head_exp));
                }
                if (deg == 0.0) w_special = std::fmax(w_special, std::fabs(out->radius() / (A * std::pow(chi, 3)) - 1.0));
                if (deg == 90.0) w_special = std::fmax(w_special, std::fabs(out->radius() / (A * chi) - 1.0));
            }
        }
        tb::check("T4", "response magnitude vs A sqrt(chi^6 cos^2 psi + chi^2 sin^2 psi), worst relative over 20 cases", w_mag, 0.0, 1e-9, false);
        tb::check("T4", "response heading vs atan2(chi sin psi, chi^3 cos psi), worst over 12 cases (rad)", w_head, 0.0, 1e-9, false);
        tb::check("T4", "parallel factor chi^3 and perpendicular factor chi (worst relative)", w_special, 0.0, 1e-12, false);
        const S::Locus a0(2.5, 0.8, 0.4);
        const S::Vector same = OS::law_v_response(S::Vector{a0}, std::nullopt);
        tb::check_true("T4", "at v = 0 the acceleration is returned unchanged", same && same->radius() == 2.5 && same->theta() == a0.theta() && same->phi() == a0.phi());
    }

    tb::heading("T5 independent derivative of the engine momentum");
    {
        double worst = 0.0;
        for (double b : {0.1, 0.6, 0.8, 0.99}) {
            const double v = b * c, h = c * (1.0 - b) * 1e-4;
            const double dp = central_diff([&](double x) { return V::momentum(m0, x); }, v, h);
            const double g = V::gamma(v);
            worst = std::fmax(worst, std::fabs(dp / (m0 * g * g * g) - 1.0));
            tb::note("beta = %.2f: numerical dp/dv / (m0 gamma^3) = %.10f", b, dp / (m0 * g * g * g));
        }
        tb::check("T5", "dp/dv / (m0 gamma^3) - 1, worst over 4 beta", worst, 0.0, 2e-6, false);
        double wg = 0.0;
        for (double b : {0.1, 0.6, 0.8}) {
            const double dg = central_diff([&](double x) { return 1.0 / std::sqrt((1.0 - x) * (1.0 + x)); }, b, 1e-5);
            wg = std::fmax(wg, std::fabs(dg / (b * std::pow(1.0 / std::sqrt((1.0 - b) * (1.0 + b)), 3)) - 1.0));
        }
        tb::check("T5", "d gamma / d beta = beta gamma^3, worst relative over 3 beta", wg, 0.0, 1e-8, false);
    }

    tb::heading("T6 depth budget compatibility (engine depth relations; the depth is the engine's)");
    {
        double w_id = 0.0, w_clock = 0.0;
        for (double z : {0.0, 0.01, 0.1, 0.25, 0.5, 0.9}) {
            w_id = std::fmax(w_id, std::fabs((1.0 - z) * (1.0 - z) + (2.0 * z - z * z) - 1.0));
            w_clock = std::fmax(w_clock, std::fabs(DC::clock_rate(z) - (1.0 - z)) + std::fabs(DC::c_far(c, z) / c - (1.0 - z) * (1.0 - z)));
            const double Hh = z < 0.5 ? (1.0 - z) * (1.0 - z) / (1.0 - 2.0 * z) : 0.0;
            tb::note("z = %.2f: clock %.4f, far-speed factor %.4f, required squared loading %.4f%s", z, DC::clock_rate(z), (1.0 - z) * (1.0 - z), 2 * z - z * z,
                     z < 0.5 ? ("; linear branch needs H_h = " + std::to_string(Hh)).c_str() : "");
        }
        tb::check("T6", "(1-z)^2 + (2z - z^2) = 1, worst over 6 depths", w_id, 0.0, 1e-12, false);
        tb::check("T6", "engine clock_rate and c_far match 1 - z and (1 - z)^2", w_clock, 0.0, 1e-15, false);
    }

    tb::heading("T7 variable c at fixed velocity");
    {
        double worst = 0.0;
        const double eps = 1e-3;
        for (double b0 : {0.3, 0.8}) {
            const double v = b0 * c;
            auto gam = [&](double t) { const double cc = c * (1.0 + eps * t); return 1.0 / std::sqrt(1.0 - v * v / (cc * cc)); };
            const double num = central_diff(gam, 0.0, 1e-3);
            const double g = gam(0.0);
            const double analytic = -g * g * g * b0 * b0 * (c * eps) / c;
            worst = std::fmax(worst, std::fabs(num / analytic - 1.0));
        }
        tb::check("T7", "d gamma/dt = -gamma^3 beta^2 (dc/dt)/c at fixed v, worst relative", worst, 0.0, 1e-6, false);
    }

    tb::heading("T8 controlled radiative limit");
    {
        const double Estar = 1.0, b = 1.0 - 1e-8, g = 1.0 / std::sqrt((1.0 - b) * (1.0 + b));
        const double E = g * (Estar / g), p = E * b / c;
        tb::check("T8", "E = E_* for E_0 = E_*/gamma", E, Estar, 1e-14);
        tb::check("T8", "p c / E_* = beta at beta = 1 - 1e-8", p * c / Estar, b, 1e-12);
    }

    tb::heading("T9 worked headings");
    {
        const double b8 = 0.8, chi8 = 0.6, g8 = 1.0 / chi8;
        tb::check("T9", "beta = 0.8: a_perp/a_par = gamma^2 = 25/9 at psi = 45 deg", (chi8 * std::sin(kPi / 4)) / (std::pow(chi8, 3) * std::cos(kPi / 4)), 25.0 / 9.0, 1e-14);
        const double psi_a = std::atan2(chi8 * std::sin(kPi / 4), std::pow(chi8, 3) * std::cos(kPi / 4)) * 180.0 / kPi;
        tb::check("T9", "response heading (degrees) = 70.2 to the printed digit", std::round(psi_a * 10.0) / 10.0, 70.2, 1e-12);
        tb::check("T9", "beta = 0.6, equal components: tan(psi_a) = 0.8/0.512 = 1.5625", 0.8 / 0.512, 1.5625, 1e-14);
        tb::note("beta = 0.8: gamma = %.10f ; response heading %.4f deg", g8, psi_a);
        (void)b8;
    }

    return tb::finish();
}
