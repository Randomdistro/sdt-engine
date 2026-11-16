// Chapter 15 — energy and momentum balance: worked-example instrument.
// Pre-registration: Textbook/validation/ch15_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch15_energy_and_momentum_balance
#include <sdt/dynamics.hpp>
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <vector>

namespace {

namespace D = sdt::dynamics;
constexpr double kPi = std::numbers::pi;

struct Rng {
    std::uint64_t s;
    double next() {
        s = s * 6364136223846793005ULL + 1442695040888963407ULL;
        return static_cast<double>(s >> 11) * (1.0 / 9007199254740992.0);
    }
};

double weighted_momentum(const std::vector<D::Body>& b, double& scale) {
    D::Vec3 p{};
    double w = 0.0, vmax = 0.0;
    for (const auto& x : b) {
        p += x.velocity * x.koppa_m;
        w += x.koppa_m;
        vmax = std::fmax(vmax, D::norm(x.velocity));
    }
    scale = w * vmax;
    return D::norm(p);
}

template <class Stepper>
double energy_error_one_orbit(int N, double k1, double k2, double d, Stepper stepper) {
    using sdt::laws::measured::c;
    auto bodies = D::circular_pair(k1, k2, d);
    const double omega = c * std::sqrt((k1 + k2) / (d * d * d));
    const double T = 2.0 * kPi / omega;
    const double E0 = D::invariants(bodies).energy;
    for (int i = 0; i < N; ++i) (void)stepper(bodies, T / N);
    return std::fabs(D::invariants(bodies).energy - E0) / std::fabs(E0);
}

}  // namespace

int main() {
    namespace M = sdt::laws::measured;
    tb::validate_helpers();

    const double k1 = 1e3, k2 = 3e3, d = 1e9;
    const double omega = M::c * std::sqrt((k1 + k2) / (d * d * d)), T = 2.0 * kPi / omega;

    tb::heading("V1 circular pair closes after one period (RK4, 4000 steps)");
    {
        auto bodies = D::circular_pair(k1, k2, d);
        const auto start = bodies;
        for (int i = 0; i < 4000; ++i) (void)D::step_rk4(bodies, T / 4000);
        double worst = 0.0;
        for (std::size_t i = 0; i < bodies.size(); ++i) worst = std::fmax(worst, D::norm(bodies[i].position - start[i].position) / d);
        tb::check("V1", "position error after one period, relative to d", worst, 0.0, 1e-6, false);
        tb::note("omega = %.6e rad per SI second ; period %.6e s (unit bridge)", omega, T);
    }

    tb::heading("T1 chain ledger (TOY relay chain, s = 0.3)");
    {
        const int n = 200, a = 50, b = 149, counts = 100;
        const double s = 0.3;
        Rng g{424242};
        std::vector<double> R(n), L(n);
        for (int i = 0; i < n; ++i) { R[i] = g.next(); L[i] = g.next(); }
        double worst_u = 0.0, worst_p = 0.0, worst_omit = 0.0, recoil_total = 0.0;
        for (int m = 0; m < counts; ++m) {
            auto Ru = [&](int i) { return (i >= 0 && i < n) ? R[i] : 0.0; };
            auto Lu = [&](int i) { return (i >= 0 && i < n) ? L[i] : 0.0; };
            double U0 = 0.0, P0 = 0.0, recoil = 0.0;
            for (int i = a; i <= b; ++i) { U0 += R[i] + L[i]; P0 += R[i] - L[i]; recoil += 2.0 * s * (R[i] - L[i]); }
            // interface fluxes of this count (parcels crossing between cell b and b+1, and a-1 and a)
            const double out_right = (1.0 - s) * R[b] + s * L[b];                 // R_{b+1}(m+1)
            const double out_left = (1.0 - s) * L[a] + s * R[a];                  // L_{a-1}(m+1)
            const double in_left = (1.0 - s) * Ru(a - 1) + s * Lu(a - 1);         // R_a(m+1)
            const double in_right = (1.0 - s) * Lu(b + 1) + s * Ru(b + 1);        // L_b(m+1)
            std::vector<double> R2(n, 0.0), L2(n, 0.0);
            for (int j = 0; j < n; ++j) {
                if (j + 1 < n) R2[j + 1] += (1.0 - s) * R[j] + s * L[j];
                if (j - 1 >= 0) L2[j - 1] += (1.0 - s) * L[j] + s * R[j];
            }
            R.swap(R2);
            L.swap(L2);
            double U1 = 0.0, P1 = 0.0;
            for (int i = a; i <= b; ++i) { U1 += R[i] + L[i]; P1 += R[i] - L[i]; }
            worst_u = std::fmax(worst_u, std::fabs((U1 - U0) - ((in_left + in_right) - (out_left + out_right))) / U0);
            // momentum: flux in = in_left - in_right (right-moving counts +, left-moving -), out = out_right - out_left
            const double flux_net = (in_left - in_right) - (out_right - out_left);
            worst_p = std::fmax(worst_p, std::fabs((P1 - P0) + recoil - flux_net));
            worst_omit = std::fmax(worst_omit, std::fabs(std::fabs((P1 - P0) - flux_net) - std::fabs(recoil)));
            recoil_total += std::fabs(recoil);
        }
        tb::check("T1", "content: (DeltaU - (inflow - outflow)) / U_start, worst over 100 counts", worst_u, 0.0, 1e-14, false);
        tb::check("T1", "momentum with the recoil of the scatterer: residual, worst", worst_p, 0.0, 1e-14, false);
        tb::check("T1", "momentum without the recoil: |residual| equals |recoil|, worst deviation", worst_omit, 0.0, 1e-14, false);
        tb::check_true("T1", "the omitted recoil is not zero (sum of |recoil| over the run > 0)", recoil_total > 1e-3);
        tb::note("sum of |recoil| over 100 counts: %.6f (units of content x hop)", recoil_total);
    }

    tb::heading("T2 engine ledger: bridge kernel, two bodies of unequal source length");
    {
        double scale = 0.0;
        for (int which = 0; which < 2; ++which) {
            auto bodies = D::circular_pair(k1, k2, d);
            const auto inv0 = D::invariants(bodies);
            double worst_p = 0.0;
            const int N = 2000;
            for (int i = 0; i < N; ++i) {
                (void)(which == 0 ? D::step(bodies, T / N) : D::step_rk4(bodies, T / N));
                worst_p = std::fmax(worst_p, weighted_momentum(bodies, scale) / scale);
            }
            const auto inv1 = D::invariants(bodies);
            const double dL = D::norm(inv1.angular_momentum - inv0.angular_momentum) / D::norm(inv0.angular_momentum);
            tb::check(which == 0 ? "T2" : "T2", which == 0 ? "Verlet: weighted momentum / (varpi_tot v_max), worst over 2000 steps" : "RK4: weighted momentum / (varpi_tot v_max), worst over 2000 steps", worst_p, 0.0, 1e-12, false);
            tb::check(which == 0 ? "T2" : "T2", which == 0 ? "Verlet: weighted angular momentum drift over one orbit" : "RK4: weighted angular momentum drift over one orbit", dL, 0.0, 1e-9, false);
        }
        auto verlet = [](std::vector<D::Body>& b, double dt) { return D::step(b, dt); };
        auto rk4 = [](std::vector<D::Body>& b, double dt) { return D::step_rk4(b, dt); };
        const double ev[3] = {energy_error_one_orbit(200, k1, k2, d, verlet), energy_error_one_orbit(400, k1, k2, d, verlet), energy_error_one_orbit(800, k1, k2, d, verlet)};
        const double er[3] = {energy_error_one_orbit(200, k1, k2, d, rk4), energy_error_one_orbit(400, k1, k2, d, rk4), energy_error_one_orbit(800, k1, k2, d, rk4)};
        const double ov1 = std::log2(ev[0] / ev[1]), ov2 = std::log2(ev[1] / ev[2]);
        const double or1 = std::log2(er[0] / er[1]), or2 = std::log2(er[1] / er[2]);
        tb::note("energy error after one orbit, N = 200/400/800: Verlet %.3e %.3e %.3e ; RK4 %.3e %.3e %.3e", ev[0], ev[1], ev[2], er[0], er[1], er[2]);
        tb::note("circular-orbit observed order (reported only; symmetric orbit, see registration record): Verlet %.3f, %.3f ; RK4 %.3f, %.3f", ov1, ov2, or1, or2);
    }

    tb::heading("T2(c) eccentric orbit: order of the step in the energy invariant");
    {
        const int Ns[3] = {400, 800, 1600};
        const double a = d / (2.0 - 0.49);
        const double Te = 2.0 * kPi * std::sqrt(a * a * a / (M::c * M::c * (k1 + k2)));
        double eps[2][3];
        for (int which = 0; which < 2; ++which) {
            for (int q = 0; q < 3; ++q) {
                auto bodies = D::circular_pair(k1, k2, d);
                for (auto& b : bodies) b.velocity = b.velocity * 0.7;
                const double E0 = D::invariants(bodies).energy;
                double worst = 0.0;
                for (int i = 0; i < Ns[q]; ++i) {
                    (void)(which == 0 ? D::step(bodies, Te / Ns[q]) : D::step_rk4(bodies, Te / Ns[q]));
                    worst = std::fmax(worst, std::fabs(D::invariants(bodies).energy - E0) / std::fabs(E0));
                }
                eps[which][q] = worst;
            }
        }
        tb::note("max energy deviation over one period, N = 400/800/1600: Verlet %.3e %.3e %.3e ; RK4 %.3e %.3e %.3e", eps[0][0], eps[0][1], eps[0][2], eps[1][0], eps[1][1], eps[1][2]);
        const double v1 = std::log2(eps[0][0] / eps[0][1]), v2 = std::log2(eps[0][1] / eps[0][2]);
        const double r1 = std::log2(eps[1][0] / eps[1][1]), r2 = std::log2(eps[1][1] / eps[1][2]);
        tb::note("observed order: Verlet %.3f, %.3f ; RK4 %.3f, %.3f", v1, v2, r1, r2);
        tb::check_true("T2(c)", "Verlet observed order in [1.8, 2.2]", v1 > 1.8 && v1 < 2.2 && v2 > 1.8 && v2 < 2.2);
        tb::check_true("T2(c)", "RK4 observed order in [3.5, 4.5]", r1 > 3.5 && r1 < 4.5 && r2 > 3.5 && r2 < 4.5);
    }

    tb::heading("T3 Lagrange equilateral configuration, quarter period (RK4)");
    {
        const double k = 1e3, side = 1e9;
        auto bodies = D::equilateral_three(k, side);
        const double om = M::c * std::sqrt(3.0 * k / (side * side * side)), Tq = 0.25 * 2.0 * kPi / om;
        for (int i = 0; i < 2000; ++i) (void)D::step_rk4(bodies, Tq / 2000);
        const double s01 = D::norm(bodies[0].position - bodies[1].position), s12 = D::norm(bodies[1].position - bodies[2].position),
                     s20 = D::norm(bodies[2].position - bodies[0].position);
        const double spread = std::fmax(std::fabs(s01 - side), std::fmax(std::fabs(s12 - side), std::fabs(s20 - side))) / side;
        double scale = 0.0;
        tb::check("T3", "side lengths vs the initial side, worst relative", spread, 0.0, 1e-8, false);
        tb::check("T3", "weighted momentum / scale", weighted_momentum(bodies, scale) / std::fmax(scale, 1e-300), 0.0, 1e-12, false);
    }

    tb::heading("T4 contact: refusal of a step");
    {
        const double kk = 1e3, dd = 1e8, rc = 1e6;
        std::vector<D::Body> bodies{{{-0.5 * dd, 0, 0}, {}, kk, rc}, {{0.5 * dd, 0, 0}, {}, kk, rc}};
        const double Tff = std::pow(dd, 1.5) / (M::c * std::sqrt(2.0 * 2.0 * kk));
        const double dt = Tff / 1e4;
        D::StepStatus status = D::StepStatus::advanced;
        int steps = 0;
        std::vector<D::Body> before;
        while (status == D::StepStatus::advanced && steps < 200000) {
            before = bodies;
            status = D::step(bodies, dt);
            ++steps;
        }
        const double sep_last = D::norm(before[0].position - before[1].position);
        bool unchanged = true;
        for (std::size_t i = 0; i < bodies.size(); ++i)
            unchanged = unchanged && bodies[i].position.x == before[i].position.x && bodies[i].velocity.x == before[i].velocity.x;
        tb::check_true("T4", "the engine returns `collision` at some step", status == D::StepStatus::collision);
        tb::check_true("T4", "the refused step leaves the state unmodified", unchanged);
        tb::check_true("T4", "the last accepted separation exceeds the contact distance 2e6 m", sep_last > 2.0 * rc);
        tb::note("refused at step %d ; last accepted separation %.6e m ; contact distance %.6e m", steps, sep_last, 2.0 * rc);
    }

    tb::heading("T5 dipole emitter recoil");
    {
        double worst = 0.0;
        for (double eps : {0.0, 1e-3, 0.5, 1.0}) {
            const double flux = tb::integrate([&](double mu) { return (1.0 + eps * mu) * mu; }, -1.0, 1.0, 48, 4) * 2.0 * kPi /
                                (tb::integrate([&](double mu) { return 1.0 + eps * mu; }, -1.0, 1.0, 48, 4) * 2.0 * kPi);
            worst = std::fmax(worst, std::fabs(flux - eps / 3.0));
            tb::note("eps = %-6g: net momentum flux = %.12f (L/c); eps/3 = %.12f", eps, flux, eps / 3.0);
        }
        tb::check("T5", "net momentum flux minus eps/3, worst over 4 patterns (L/c units)", worst, 0.0, 1e-13, false);
    }

    return tb::finish();
}
