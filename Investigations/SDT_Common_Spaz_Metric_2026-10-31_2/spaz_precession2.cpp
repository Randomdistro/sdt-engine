// ============================================================================
//  spaz_precession2.cpp — Common Spaz Metric run 2, workstream W3
//  Author: James Christopher Tyndall, Melbourne.
//
//  Apsidal advance per orbit for a central Law-III occlusion acceleration
//  a = -(c^2 koppa / r^2) r_hat, optionally with
//    (i)  the engine's Law V response  sdt::occlusion::law_v_response
//         (T10: a_par / gamma^3 + a_perp / gamma), and
//    (ii) a static correction factor (1 + lambda koppa / r).
//  Advance is reported as a fraction of the reference 6 pi koppa / (a(1-e^2)).
//
//  Validation (pre-registered): Kepler -> 0; Law V -> 1/6; static lambda=6 -> 1.
//
//  Units: c^2 koppa = 1, a = 1, so koppa/a = eps and c^2 = 1/eps.
//
//  Build: g++ -std=c++20 -O2 -IEngine/include spaz_precession2.cpp
// ============================================================================

#include <sdt/laws.hpp>
#include <sdt/occlusion.hpp>

#include <cmath>
#include <cstdio>
#include <numbers>

namespace {

namespace M = sdt::laws::measured;
namespace Br = sdt::laws::bridge;
using sdt::dynamics::Vec3;
constexpr double PI = std::numbers::pi;

struct State { double x, y, vx, vy; };

struct Model {
    double eps;      // koppa / a
    bool law_v;      // engine Law V response on
    double lambda;   // static (1 + lambda koppa / r) factor
};

// Law V response written in scaled units: identical algebra to
// sdt::occlusion::law_v_response but with c^2 = 1/eps (the engine routine
// uses SI c). Cross-checked against the engine routine in validate_law_v().
auto accel(const Model& m, const State& s) -> std::pair<double, double> {
    const double r = std::hypot(s.x, s.y);
    const double f = -(1.0 + m.lambda * m.eps / r) / (r * r * r);
    double ax = f * s.x, ay = f * s.y;
    if (m.law_v) {
        const double c2 = 1.0 / m.eps;
        const double v2 = s.vx * s.vx + s.vy * s.vy;
        const double g = 1.0 / std::sqrt(1.0 - v2 / c2);
        const double v = std::sqrt(v2);
        const double ux = s.vx / v, uy = s.vy / v;
        const double ap = ax * ux + ay * uy;
        const double px = ap * ux, py = ap * uy;
        ax = px / (g * g * g) + (ax - px) / g;
        ay = py / (g * g * g) + (ay - py) / g;
    }
    return {ax, ay};
}

auto rk4(const Model& m, State s, double h) -> State {
    auto d = [&](const State& q) {
        auto [ax, ay] = accel(m, q);
        return State{q.vx, q.vy, ax, ay};
    };
    auto add = [](State a, State b, double k) {
        return State{a.x + k * b.x, a.y + k * b.y, a.vx + k * b.vx, a.vy + k * b.vy};
    };
    const State k1 = d(s), k2 = d(add(s, k1, h / 2)), k3 = d(add(s, k2, h / 2)),
                k4 = d(add(s, k3, h));
    return State{
        s.x + h / 6 * (k1.x + 2 * k2.x + 2 * k3.x + k4.x),
        s.y + h / 6 * (k1.y + 2 * k2.y + 2 * k3.y + k4.y),
        s.vx + h / 6 * (k1.vx + 2 * k2.vx + 2 * k3.vx + k4.vx),
        s.vy + h / 6 * (k1.vy + 2 * k2.vy + 2 * k3.vy + k4.vy)};
}

/// Mean perihelion-to-perihelion drift per orbit [rad] over n_orbits passages.
/// The polar angle is accumulated continuously; each perihelion is the linear
/// root of r.v crossing from negative to positive within one step.
auto advance(const Model& m, double e, int n_orbits = 12, int steps = 40000) -> double {
    const double vp = std::sqrt((1 + e) / (1 - e));
    State s{1 - e, 0, 0, vp};
    const double h = 2 * PI / steps;
    double theta = 0.0, first = 0.0, last = 0.0;
    int count = 0;
    for (long i = 0; count <= n_orbits; ++i) {
        const State n = rk4(m, s, h);
        double dth = std::atan2(n.y, n.x) - std::atan2(s.y, s.x);
        if (dth < -PI) dth += 2 * PI;
        if (dth > PI) dth -= 2 * PI;
        const double rv0 = s.x * s.vx + s.y * s.vy, rv1 = n.x * n.vx + n.y * n.vy;
        if (i > 10 && rv0 < 0 && rv1 >= 0) {
            const double peri = theta + rv0 / (rv0 - rv1) * dth;
            if (count == 0) first = peri;
            last = peri;
            ++count;
        }
        theta += dth;
        s = n;
    }
    return (last - first) / (count - 1) - 2 * PI;
}

auto ratio(const Model& m, double e) -> double {
    const double ref = 6 * PI * m.eps / (1 - e * e);
    return advance(m, e) / ref;
}

void validate_law_v() {
    // engine routine in SI: compare to scaled algebra at one state
    const Vec3 a{-1.0, 0.3, 0.0}, v{0.2 * M::c, 0.5 * M::c, 0.0};
    const Vec3 r = sdt::occlusion::law_v_response(a, v);
    const double g = sdt::laws::law_V::gamma(std::sqrt(0.29) * M::c);
    const double vn = std::sqrt(0.29);
    const double ux = 0.2 / vn, uy = 0.5 / vn, ap = -1.0 * ux + 0.3 * uy;
    const double ex = ap * ux / (g * g * g) + (-1.0 - ap * ux) / g;
    std::printf("  validation: engine law_v_response x = %.12f, scaled algebra %.12f\n",
        r.x, ex);
}

} // namespace

int main() {
    std::printf("spaz_precession2 — W3 apsidal advance (RK4, 40000 steps/orbit, 12 orbits)\n");
    validate_law_v();
    const double eps = 3e-4, e = 0.2;
    const double kep = advance({eps, false, 0.0}, e);
    std::printf("  validation Kepler: advance %.3e rad/orbit (criterion < 1e-8)\n", kep);
    const double fV = ratio({eps, true, 0.0}, e);
    const double f6 = ratio({eps, false, 6.0}, e);
    std::printf("  validation Law V: %.5f (criterion 1/6 = 0.16667 +- 0.5 %%)\n", fV);
    std::printf("  validation lambda=6: %.5f (criterion 1 +- 0.5 %%)\n", f6);

    std::printf("\n  %-34s %8s %8s %10s\n", "dynamics", "eps", "e", "adv/ref");
    for (double ee : {0.2, 0.5}) {
        for (double ep : {3e-4, 1e-4}) {
            const double a = ratio({ep, true, 0.0}, ee);
            const double b = ratio({ep, false, 5.0}, ee);
            const double c = ratio({ep, true, 5.0}, ee);
            std::printf("  %-34s %8.0e %8.2f %10.5f\n", "Law V only", ep, ee, a);
            std::printf("  %-34s %8.0e %8.2f %10.5f\n", "static lambda=5 only", ep, ee, b);
            std::printf("  %-34s %8.0e %8.2f %10.5f\n", "Law V + static lambda=5", ep, ee, c);
        }
    }
    // lambda required with Law V on (two-route: linear solve, then verify)
    const double f0 = fV, f5 = ratio({eps, true, 5.0}, e);
    const double lam_req = 5.0 * (1.0 - f0) / (f5 - f0);
    const double check = ratio({eps, true, lam_req}, e);
    std::printf("\n  lambda_req (Law V on) = %.4f   verify ratio = %.5f\n", lam_req, check);

    // GOM04 closure sensitivity and multi-body table
    std::printf("\n  GOM04 c-closure sensitivity to Mercury's anomalous advance\n");
    const double vS = Br::v_surface_Sun;
    for (double arc : {42.94, 42.98, 43.02, 42.98077}) {
        const double dphi = arc / Br::mercury_orbits_per_cy * PI / 648000.0;
        const double k = Br::k_from_precession(M::R_Sun, Br::a_Mercury, Br::e_Mercury, dphi);
        std::printf("    %9.5f\"/cy  k = %9.4f  c = k v_surf = %.6e  (c-c0)/c0 = %+.2e\n",
            arc, k, k * vS, k * vS / M::c - 1);
    }
    std::printf("\n  Reference advance 6 pi koppa_Sun/(a(1-e^2)) per body, koppa_Sun=%.3f m "
        "(engine k_Sun); predicted = ref x (f_V + lambda/6)\n", Br::koppa_Sun);
    struct Body { const char* n; double a, e, P_days; const char* meas; };
    const Body bs[] = {
        {"Mercury", 5.7909e10, 0.20563, 87.969, "42.98 +- 0.04 (engine, MEASURED-INPUT)"},
        {"Venus",   1.0821e11, 0.00677, 224.701, "PENDING source"},
        {"Earth",   1.4960e11, 0.01671, 365.256, "PENDING source"},
        {"Mars",    2.2794e11, 0.09339, 686.980, "PENDING source"},
    };
    const double lam_fit_scale = 42.98 / (6 * PI * Br::koppa_Sun / (5.7909e10 * (1 - 0.20563 * 0.20563))
        * 36525.0 / 87.969 * 648000.0 / PI);
    const double lam_fit = 6.0 * (lam_fit_scale - fV);
    std::printf("  lambda fitted to Mercury (CALIBRATED(1)) = %.4f\n", lam_fit);
    for (const auto& b : bs) {
        const double ref = 6 * PI * Br::koppa_Sun / (b.a * (1 - b.e * b.e))
                           * 36525.0 / b.P_days * 648000.0 / PI;
        std::printf("    %-8s ref %8.4f\"/cy  Law V only %7.4f  fitted %8.4f  measured: %s\n",
            b.n, ref, ref * fV, ref * (fV + lam_fit / 6), b.meas);
    }
    return 0;
}
