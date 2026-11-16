// Chapter 8 — mathematical well-posedness: worked-example instrument.
// Pre-registration: Textbook/validation/ch08_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch08_mathematical_well_posedness
#include <sdt/laws.hpp>
#include <sdt/sphere_frame.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

namespace {

namespace S = sdt::sphere;
constexpr double kPi = std::numbers::pi;
constexpr double kU = 1.11e-16;

// TOY relay update on a chain: each cell passes the fraction f of its content to each neighbour.
std::vector<double> relay_steps(int n, int steps, double f) {
    std::vector<double> u(n, 0.0);
    u[n / 2] = 1.0;
    for (int s = 0; s < steps; ++s) {
        std::vector<double> v(n, 0.0);
        for (int i = 1; i + 1 < n; ++i) v[i] = (1.0 - 2.0 * f) * u[i] + f * (u[i - 1] + u[i + 1]);
        u = v;
    }
    return u;
}

// Accumulated displacement I(T) = int_1^T t^-s dt in the log variable t = e^x.
double accumulated(double s, double T) {
    return tb::integrate([&](double x) { return std::exp((1.0 - s) * x); }, 0.0, std::log(T), 48, 8);
}
double accumulated_exact(double s, double T) {
    return s == 1.0 ? std::log(T) : (std::pow(T, 1.0 - s) - 1.0) / (1.0 - s);
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 relay update, f = 1/3, one step");
    {
        const auto u = relay_steps(9, 1, 1.0 / 3.0);
        tb::check("V1", "central three cells each hold 1/3", u[3], 1.0 / 3.0, 1e-15);
        tb::check("V1", "...", u[4], 1.0 / 3.0, 1e-15);
        tb::check("V1", "...", u[5], 1.0 / 3.0, 1e-15);
        tb::check("V1", "total content is 1", std::accumulate(u.begin(), u.end(), 0.0), 1.0, 1e-15);
    }
    tb::heading("V2 log-variable quadrature of the accumulated displacement");
    tb::check("V2", "s = 2, T = 1e4 vs (T^(1-s) - 1)/(1-s)", accumulated(2.0, 1e4), accumulated_exact(2.0, 1e4), 1e-12);
    tb::check("V2", "s = 1, T = 1e4 vs ln T", accumulated(1.0, 1e4), std::log(1e4), 1e-12);
    tb::heading("V3 step_locus on a known path");
    {
        const S::Locus from(1.0, kPi / 2, kPi), along(1.0, kPi / 2, 2.0 * kPi);
        const S::Locus got = S::step_locus(from, along, 0.5);
        const S::Locus want(0.5, kPi / 2, kPi);
        tb::check("V3", "(-1,0,0) advanced +x by 0.5 is (-0.5,0,0): distance to the reference", got.distance_to(want), 0.0, 1e-12, false);
        tb::check("V3", "radius 0.5", got.radius(), 0.5, 1e-12);
    }

    tb::heading("T1 TOY: positivity and conservation of the relay update");
    {
        // (a) double precision, 201 cells, 50 steps
        for (double f : {0.25, 0.5, 0.55, 0.75, 1.0}) {
            const auto u = relay_steps(201, 50, f);
            const double total = std::accumulate(u.begin(), u.end(), 0.0);
            const double mn = *std::min_element(u.begin(), u.end());
            if (f <= 0.5) {
                tb::check("T1", ("double precision, total content, f = " + std::to_string(f)).c_str(), total, 1.0, 1e-12);
                tb::check_true("T1", ("double precision, minimum content >= 0 for f = " + std::to_string(f)).c_str(), mn >= 0.0);
            } else {
                tb::check_true("T1", ("double precision, minimum content < 0 for f = " + std::to_string(f)).c_str(), mn < 0.0);
            }
            tb::note("f = %.2f: total %.12e, minimum cell content %.6e, maximum %.6e", f, total, mn, *std::max_element(u.begin(), u.end()));
        }
        // (b) exact rational arithmetic, 25 cells, 8 steps
        using tb::rat::Fr;
        const Fr fs[] = {tb::rat::make(1, 4), tb::rat::make(1, 2), tb::rat::make(3, 5), tb::rat::make(3, 4), tb::rat::make(1, 1)};
        for (const Fr& f : fs) {
            tb::rat::overflow = false;
            std::vector<Fr> u(25, tb::rat::make(0));
            u[12] = tb::rat::make(1);
            const Fr c0 = tb::rat::sub(tb::rat::make(1), tb::rat::mul(tb::rat::make(2), f));
            for (int s = 0; s < 8; ++s) {
                std::vector<Fr> v(25, tb::rat::make(0));
                for (int i = 1; i + 1 < 25; ++i)
                    v[i] = tb::rat::add(tb::rat::mul(c0, u[i]), tb::rat::mul(f, tb::rat::add(u[i - 1], u[i + 1])));
                u = v;
            }
            Fr total = tb::rat::make(0);
            bool any_negative = false;
            for (const Fr& x : u) {
                total = tb::rat::add(total, x);
                if (x.n < 0) any_negative = true;
            }
            const bool half_or_less = tb::rat::to_double(f) <= 0.5;
            tb::check_true("T1", ("exact: total content = 1 and sign of the minimum correct, f = " + std::to_string(f.n) + "/" + std::to_string(f.d)).c_str(),
                           !tb::rat::overflow && tb::rat::eq(total, tb::rat::make(1)) && (half_or_less ? !any_negative : any_negative));
        }
    }

    tb::heading("T2 arrest and accumulated displacement, I(T) = int_1^T t^(-ab) dt");
    {
        double worst = 0.0;
        for (double ab : {0.5, 1.0, 2.0})
            for (double T : {1e2, 1e4, 1e6, 1e8}) {
                const double q = accumulated(ab, T), e = accumulated_exact(ab, T);
                worst = std::fmax(worst, std::fabs(q / e - 1.0));
                tb::note("ab = %.1f, T = %.0e: I = %.9e", ab, T, q);
            }
        tb::check("T2", "quadrature vs closed form, worst relative over 12 cases", worst, 0.0, 1e-10, false);
        tb::check_true("T2", "ab = 0.5: I(1e8) > 1e4 (diverging accumulated displacement)", accumulated(0.5, 1e8) > 1e4);
        tb::check("T2", "ab = 1: I(1e8)/I(1e6) = 4/3 (logarithmic growth)", accumulated(1.0, 1e8) / accumulated(1.0, 1e6), 4.0 / 3.0, 1e-10);
        tb::check("T2", "ab = 2: |I(1e8) - 1| (finite remaining displacement)", std::fabs(accumulated(2.0, 1e8) - 1.0), 0.0, 1e-7, false);
    }

    tb::heading("T3 a straight path across the polar axis of the chart");
    {
        const double z0 = 0.5, h = 0.1;
        const S::Locus start(std::sqrt(1.0 + z0 * z0), std::acos(z0 / std::sqrt(1.0 + z0 * z0)), kPi);
        const S::Locus plus_x(1.0, kPi / 2, 2.0 * kPi);
        std::vector<S::Locus> path{start};
        S::Locus cur = start;
        for (int k = 1; k <= 20; ++k) {
            cur = S::step_locus(cur, plus_x, h);
            path.push_back(cur);
        }
        double worst_step = 0.0, worst_ref = 0.0;
        for (int k = 1; k <= 20; ++k) worst_step = std::fmax(worst_step, std::fabs(path[k].distance_to(path[k - 1]) - h));
        for (int k = 0; k <= 20; ++k) {
            const double x = -1.0 + h * k;
            const double r = std::sqrt(x * x + z0 * z0);
            const S::Locus ref(r, std::acos(z0 / r), x < 0 ? kPi : 2.0 * kPi);
            worst_ref = std::fmax(worst_ref, path[k].distance_to(ref));
        }
        const double jump = std::fabs(path[11].phi() - path[9].phi());
        const double jump_wrapped = std::fmin(jump, 2.0 * kPi - jump);
        tb::check("T3", "chord between consecutive loci minus 0.1 (worst of 20)", worst_step, 0.0, 1e-12, false);
        tb::check("T3", "distance from each locus to the Cartesian reference (worst of 21)", worst_ref, 0.0, 1e-12, false);
        tb::check("T3", "azimuth change between k = 9 and k = 11 is pi", jump_wrapped, kPi, 1e-9);
        tb::check("T3", "polar angle at the crossing (k = 10)", path[10].theta(), 0.0, 1e-9, false);
        tb::note("polar angle at k = 9, 10, 11: %.6f, %.3e, %.6f ; azimuth at k = 9, 11: %.6f, %.6f", path[9].theta(), path[10].theta(),
                 path[11].theta(), path[9].phi(), path[11].phi());
    }

    tb::heading("T4 the centre: step_locus near and at r = 0");
    {
        const S::Locus from(1.0, 1.0, 1.0);
        const S::Locus anti = S::antipode(S::unit(from));
        bool labels_ok = true;
        bool budget_ok = true;
        double err_at_1e8 = 0.0;
        for (double rho : {1e-2, 1e-4, 1e-6, 1e-8}) {
            for (int side : {-1, 1}) {
                const double d = 1.0 + side * rho;  // side -1: short of the centre; +1: past it
                const S::Locus got = S::step_locus(from, anti, d);
                const double rel = std::fabs(got.radius() / rho - 1.0);
                const S::Locus want_dir = side < 0 ? S::unit(from) : anti;
                const bool dir_ok = got.angular_distance(want_dir) < 1e-3;
                if (rho >= 1e-6) labels_ok = labels_ok && dir_ok;
                budget_ok = budget_ok && (rel <= 8.0 * kU / (rho * rho) + 1e-15);
                if (rho == 1e-8 && side < 0) err_at_1e8 = rel;
                tb::note("rho = %.0e, %s the centre: radius %.9e (exact %.0e), relative error %.2e, budget 8u/rho^2 = %.2e, direction %s", rho,
                         side < 0 ? "short of" : "past", got.radius(), rho, rel, 8.0 * kU / (rho * rho), dir_ok ? "correct" : "not recovered");
            }
        }
        tb::check_true("T4", "relative error of the radius <= 8u/rho^2 in all 8 cases", budget_ok);
        tb::check_true("T4", "relative error of the radius at rho = 1e-8 exceeds 0.1", err_at_1e8 > 0.1);
        tb::check_true("T4", "direction label correct for rho >= 1e-6 on both sides of the centre", labels_ok);
        const S::Locus at_centre = S::step_locus(from, anti, 1.0);
        tb::check("T4", "at d = 1 exactly the radius is the floor 0.5e-12", at_centre.radius(), 0.5e-12, 1e-15);
    }

    return tb::finish();
}
