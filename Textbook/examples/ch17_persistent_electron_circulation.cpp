// Chapter 17 — persistent electron circulation: worked-example instrument.
// Pre-registration: Textbook/validation/ch17_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch17_persistent_electron_circulation
#include <sdt/dynamics.hpp>
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <vector>

namespace {

namespace D = sdt::dynamics;
constexpr double kPi = std::numbers::pi;

// Central-force integrator: a = -r^{-p} rhat in the plane, RK4, fixed step.
struct State {
    double x, y, vx, vy;
};

State deriv(const State& s, double p) {
    const double r = std::hypot(s.x, s.y);
    const double a = -std::pow(r, -p) / r;
    return {s.vx, s.vy, a * s.x, a * s.y};
}

State add(const State& s, const State& d, double h) { return {s.x + h * d.x, s.y + h * d.y, s.vx + h * d.vx, s.vy + h * d.vy}; }

State rk4(const State& s, double p, double h) {
    const State k1 = deriv(s, p);
    const State k2 = deriv(add(s, k1, 0.5 * h), p);
    const State k3 = deriv(add(s, k2, 0.5 * h), p);
    const State k4 = deriv(add(s, k3, h), p);
    return {s.x + h / 6.0 * (k1.x + 2 * k2.x + 2 * k3.x + k4.x), s.y + h / 6.0 * (k1.y + 2 * k2.y + 2 * k3.y + k4.y),
            s.vx + h / 6.0 * (k1.vx + 2 * k2.vx + 2 * k3.vx + k4.vx), s.vy + h / 6.0 * (k1.vy + 2 * k2.vy + 2 * k3.vy + k4.vy)};
}

// Radial deviation r(t)-1 at the requested times, starting at (1,0) with v=(delta,1).
std::vector<double> radial_deviation(double p, double delta, const std::vector<double>& times, double h = 1e-3) {
    State s{1.0, 0.0, delta, 1.0};
    std::vector<double> out;
    double t = 0.0;
    for (double target : times) {
        const int steps = static_cast<int>(std::lround((target - t) / h));
        for (int i = 0; i < steps; ++i) s = rk4(s, p, h);
        t += steps * h;
        out.push_back(std::hypot(s.x, s.y) - 1.0);
    }
    return out;
}

}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    tb::validate_helpers();
    const double c = M::c, alpha = M::alpha, a0 = M::a_0, re = M::r_e, hbar = M::hbar, me = M::m_e;

    tb::heading("V1 method on the isotropic oscillator (p = -1, kappa = 2 omega)");
    {
        const double delta = 1e-6;
        const std::vector<double> ts{0.7, 1.9, 3.1};
        const auto dev = radial_deviation(-1.0, delta, ts);
        double worst = 0.0;
        for (std::size_t i = 0; i < ts.size(); ++i) worst = std::fmax(worst, std::fabs(dev[i] - delta * std::sin(2.0 * ts[i]) / 2.0) / (delta / 2.0));
        tb::check("V1", "radial deviation vs delta sin(2t)/2, worst relative to delta/2", worst, 0.0, 1e-4, false);
    }

    tb::heading("T1 hydrogen rung ledger");
    {
        const double lamC = hbar / (me * c);
        tb::check("T1a", "r_e = alpha hbar/(m_e c) (shared-input: CODATA relations)", re, alpha * lamC, 1e-9);
        tb::check("T1b", "alpha a_0 / lambda_C-bar = 1 (shared-input)", alpha * a0 / lamC, 1.0, 1e-9);
        tb::check("T1c", "r_e / a_0 = alpha^2", re / a0, alpha * alpha, 1e-14);
        tb::check("T1c", "alpha c / a_0 equals law_VI::omega_electron_locked", alpha * c / a0, sdt::laws::law_VI::winding::omega_electron_locked, 1e-14);
        tb::note("a_0 = %.12e m ; lambda_C-bar = %.12e m ; r_e = %.12e m ; omega = alpha c/a_0 = %.9e rad/s", a0, lamC, re, alpha * c / a0);
        tb::note("a_0 : lambda_C-bar : r_e = 1 : %.9e : %.9e ; a_0/r_e = %.6f", lamC / a0, re / a0, a0 / re);
    }

    tb::heading("T2 circulation ladder Z = 1..5, n = 1..10");
    {
        double w_vr = 0.0, w_close = 0.0, w_T = 0.0;
        const double T11 = 2.0 * kPi * sdt::laws::atomic::bohr_radius(1, 1) / sdt::laws::atomic::bohr_velocity(1, 1);
        for (int Z = 1; Z <= 5; ++Z) {
            for (int n = 1; n <= 10; ++n) {
                const double v = sdt::laws::atomic::bohr_velocity(Z, n), r = sdt::laws::atomic::bohr_radius(Z, n);
                w_vr = std::fmax(w_vr, std::fabs(v * v * r / (c * c) / (Z * re) - 1.0));
                w_close = std::fmax(w_close, std::fabs(me * v * r / hbar / n - 1.0));
                const double T = 2.0 * kPi * r / v;
                w_T = std::fmax(w_T, std::fabs(T / T11 / (double(n) * n * n / (double(Z) * Z)) - 1.0));
            }
        }
        tb::check("T2", "v^2 r / (c^2 Z r_e) = 1 over 50 states, worst relative", w_vr, 0.0, 1e-14, false);
        tb::check("T2", "m_e v r / (n hbar) = 1 over 50 states, worst relative (shared-input)", w_close, 0.0, 1e-9, false);
        tb::check("T2", "T_Zn / T_11 = n^3 / Z^2 over 50 states, worst relative", w_T, 0.0, 1e-14, false);
    }

    tb::heading("T3 equilibrium and small-oscillation response on a_r = -r^{-p}");
    {
        const double delta = 1e-6;
        const std::vector<double> ts{1.0, 2.0, 3.0, 5.0};
        for (double p : {1.0, 2.0, 2.9}) {
            const double kap = std::sqrt(3.0 - p);
            const auto dev = radial_deviation(p, delta, ts);
            double worst = 0.0;
            for (std::size_t i = 0; i < ts.size(); ++i) worst = std::fmax(worst, std::fabs(dev[i] - delta * std::sin(kap * ts[i]) / kap) / (delta / kap));
            char label[128];
            std::snprintf(label, sizeof label, "p=%.1f: kappa = %.6f ; worst deviation relative to delta/kappa", p, kap);
            tb::check("T3", label, worst, 0.0, 1e-4, false);
        }
        {
            const auto dev = radial_deviation(3.0, delta, {6.0});
            tb::check("T3", "p=3 (marginal): delta r(6) = 6 delta", dev[0], 6.0 * delta, 1e-4);
        }
        {
            const double lam = std::sqrt(0.5);
            const auto dev = radial_deviation(3.5, delta, {6.0});
            tb::check("T3", "p=3.5 (route unstable): delta r(6) = delta sinh(6 lambda)/lambda", dev[0], delta * std::sinh(6.0 * lam) / lam, 1e-4);
            tb::note("p=3.5: growth factor over 6 counts of the route = %.3f (stable routes show no growth)", dev[0] / delta);
        }
        const auto dev2 = radial_deviation(2.0, delta, {kPi, 2.0 * kPi}, kPi / 3000.0);
        tb::note("p=2: delta r(pi) = %.3e, delta r(2 pi) = %.3e (radial and azimuthal frequencies coincide: the route closes)", dev2[0], dev2[1]);
        tb::check_true("T3", "p=2: radial deviation returns to zero at t = pi and 2 pi (kappa = omega)", std::fabs(dev2[0]) < 1e-4 * delta && std::fabs(dev2[1]) < 1e-4 * delta);
    }

    tb::heading("T4 the engine's bridge kernel: radial response of a two-body route");
    {
        const double k1 = 1e3, k2 = 3e3, d = 1e9;
        const double omega = c * std::sqrt((k1 + k2) / (d * d * d)), T = 2.0 * kPi / omega;
        const double u = 1e-6 * omega * d;
        auto bodies = D::circular_pair(k1, k2, d);
        bodies[0].velocity.x = -u * k2 / (k1 + k2);
        bodies[1].velocity.x = u * k1 / (k1 + k2);
        const int N = 4000;
        double worst = 0.0;
        const int marks[4] = {N / 8, N / 4, 3 * N / 8, N / 2};
        int done = 0;
        for (int q = 0; q < 4; ++q) {
            for (; done < marks[q]; ++done) (void)D::step_rk4(bodies, T / N);
            const double sep = D::norm(bodies[1].position - bodies[0].position);
            const double pred = (u / omega) * std::sin(omega * T * marks[q] / N);
            worst = std::fmax(worst, std::fabs((sep - d) - pred) / (u / omega));
        }
        tb::check("T4", "separation minus d vs (u/omega) sin(omega t), worst relative to u/omega", worst, 0.0, 1e-4, false);
    }

    tb::heading("T5 three radii");
    {
        const double Rint = std::sqrt(sdt::laws::law_III::R_p_lock * re);
        tb::note("a_0 = %.9e m (path seat) ; r_e = %.9e m (boundary) ; sqrt(R_p_lock r_e) = %.9e m (interaction radius) ; R_p_lock = %.9e m", a0, re, Rint, sdt::laws::law_III::R_p_lock);
        const double v[3] = {a0, re, Rint};
        bool distinct = true;
        for (int i = 0; i < 3; ++i)
            for (int j = i + 1; j < 3; ++j) distinct = distinct && (std::fmax(v[i], v[j]) / std::fmin(v[i], v[j]) > 1.5);
        tb::check_true("T5", "pairwise ratios of the three radii exceed 1.5", distinct);
        tb::check("T5", "a_0 / r_e = 1/alpha^2", a0 / re, 1.0 / (alpha * alpha), 1e-14);
        tb::note("ratios: a_0/r_e = %.4f ; r_e/R_int = %.4f ; R_int/R_p_lock = %.4f", a0 / re, re / Rint, Rint / sdt::laws::law_III::R_p_lock);
    }

    return tb::finish();
}
