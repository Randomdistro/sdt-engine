// Chapter 35 — retarded many-body occlusion: worked-example instrument.
// Pre-registration: Textbook/validation/ch35_PRE_REGISTRATION.md (registered before this file existed).
#include <sdt/laws.hpp>
#include <sdt/occlusion.hpp>

#include "tb_common.hpp"

#include <cmath>
#include <vector>

namespace {

namespace O = sdt::occlusion;
using sdt::dynamics::Vec3;
constexpr double kPi = std::numbers::pi;

// Fraction of a disc of radius rho centred at cx lying in the half-plane x >= t.
double seg_fraction(double cx, double rho, double t) {
    const double s = (t - cx) / rho;
    if (s <= -1.0) return 1.0;
    if (s >= 1.0) return 0.0;
    return (std::acos(s) - s * std::sqrt(1.0 - s * s)) / kPi;
}

double ref_solid_angle(double bx, double d, double R, int NR, int NA) {
    double sum = 0.0;
    for (int i = 0; i < NR; ++i) {
        const double r = R * (i + 0.5) / NR;
        for (int j = 0; j < NA; ++j) {
            const double ph = 2.0 * kPi * (j + 0.5) / NA;
            const double x = r * std::cos(ph), y = r * std::sin(ph);
            const double dx = bx - x, dy = -y, dz = d;
            const double d2 = dx * dx + dy * dy + dz * dz;
            sum += (dz / std::sqrt(d2)) / d2 * r * (R / NR) * (2.0 * kPi / NA);
        }
    }
    return sum;
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 quadrature and weights");
    {
        double s0 = 0, s2 = 0, s10 = 0;
        for (std::size_t i = 0; i < O::radial_nodes.size(); ++i) {
            s0 += O::radial_weights[i];
            s2 += O::radial_weights[i] * std::pow(O::radial_nodes[i], 2);
            s10 += O::radial_weights[i] * std::pow(O::radial_nodes[i], 10);
        }
        tb::check("V1", "sum w = 2", s0, 2.0, 1e-14);
        tb::check("V1", "sum w x^2 = 2/3", s2, 2.0 / 3.0, 1e-14);
        tb::check("V1", "sum w x^10 = 2/11", s10, 2.0 / 11.0, 1e-14);
        tb::check("V1", "central + 6 outer channel weights = 1", O::central_weight + 6.0 * O::outer_weight, 1.0, 1e-14);
    }

    tb::heading("T1 geometry of the seven circles");
    {
        const double R = 1.0, rho = R / 3.0, ring = 2.0 * R / 3.0;
        const auto fr = O::pair_frame({0.0, 0.0, 1.0});
        std::vector<Vec3> c;
        for (std::size_t k = 0; k < 7; ++k) c.push_back(O::channel_offset(k, R, fr));
        double w_touch = 0.0, w_nb = 0.0, w_in = 0.0, sum_x2 = 0.0;
        for (std::size_t k = 1; k < 7; ++k) {
            w_touch = std::fmax(w_touch, std::fabs(sdt::dynamics::norm(c[k]) - 2.0 * rho));
            const std::size_t nxt = (k % 6) + 1;
            w_nb = std::fmax(w_nb, std::fabs(sdt::dynamics::norm(c[k] - c[nxt]) - 2.0 * rho));
            w_in = std::fmax(w_in, std::fabs(sdt::dynamics::norm(c[k]) + rho - R));
            sum_x2 += O::channel_weight(k) * std::pow(sdt::dynamics::norm(c[k]), 2) * 0.5;
        }
        tb::check("T1", "ring centre to central centre = 2 rho (touching), worst deviation", w_touch, 0.0, 1e-14, false);
        tb::check("T1", "neighbouring ring centres at 2 rho (touching), worst deviation", w_nb, 0.0, 1e-14, false);
        tb::check("T1", "outer extent = R, worst deviation", w_in, 0.0, 1e-14, false);
        const double area = 7.0 * kPi * rho * rho / (kPi * R * R);
        tb::check("T1", "total circle area fraction = 7/9", area, 7.0 / 9.0, 1e-14);
        tb::check("T1", "w0 = 1/9", O::central_weight, 1.0 / 9.0, 1e-14);
        tb::check("T1", "w1 = 1/9 + (2/9)/6 = 4/27", O::outer_weight, 1.0 / 9.0 + (2.0 / 9.0) / 6.0, 1e-14);
        tb::note("second moment: model sum w x^2 = %.6f ; exact disc R^2/4 = %.6f (the weights are not an exact area cubature)", sum_x2, 0.25);
        (void)ring;
    }

    tb::heading("T2 disc solid angle quadrature");
    {
        const Vec3 f1{1.0, 0.0, 0.0}, f2{0.0, 1.0, 0.0}, n{0.0, 0.0, 1.0};
        const double R = 1.0;
        auto err = [&](double d) {
            const double q = O::disc_solid_angle({0.0, 0.0, d}, {0.0, 0.0, 0.0}, n, f1, f2, R);
            const double ex = O::axial_disc_solid_angle(d, R);
            return std::fabs(q / ex - 1.0);
        };
        const double e100 = err(100.0), e10 = err(10.0), e3 = err(3.0), e1 = err(1.0);
        tb::note("axial relative errors: d/R = 100: %.2e ; 10: %.2e ; 3: %.2e ; 1: %.2e ; 0.5: %.2e ; 0.2: %.2e ; 0.1: %.2e", e100, e10, e3, e1, err(0.5), err(0.2), err(0.1));
        tb::check_true("T2", "relative error <= 1e-8 at d/R = 100, 10, 3", e100 <= 1e-8 && e10 <= 1e-8 && e3 <= 1e-8);
        tb::check_true("T2", "relative error <= 1e-4 at d/R = 1", e1 <= 1e-4);
        for (double b : {0.5, 1.5}) {
            const double q = O::disc_solid_angle({b, 0.0, 2.0}, {0.0, 0.0, 0.0}, n, f1, f2, R);
            const double ref = ref_solid_angle(b, 2.0, R, 400, 800);
            tb::note("off axis b = %.1f R, d = 2 R: quadrature %.10f ; reference %.10f ; relative error %.2e", b, q, ref, q / ref - 1.0);
            if (b == 0.5) tb::check_true("T2", "off-axis relative error <= 1e-5 at b = 0.5 R", std::fabs(q / ref - 1.0) <= 1e-5);
        }
    }

    tb::heading("T3 partial occultation by a half-plane edge");
    {
        const double R = 1.0, rho = R / 3.0;
        const auto fr = O::pair_frame({0.0, 0.0, 1.0});
        // the x coordinate of each channel centre
        std::vector<double> xs;
        for (std::size_t k = 0; k < 7; ++k) xs.push_back(O::channel_offset(k, R, fr).x);
        auto exact = [&](double t) { return t <= -1.0 ? 1.0 : t >= 1.0 ? 0.0 : (std::acos(t) - t * std::sqrt(1.0 - t * t)) / kPi; };
        double max_model = 0.0, max_bool = 0.0, prev_m = 2.0, prev_b = 2.0;
        bool mono = true, ends = true;
        const int NT = 4000;
        for (int i = 0; i <= NT; ++i) {
            const double t = -1.2 + 2.4 * i / NT;
            double m = 0.0, b = 0.0;
            for (std::size_t k = 0; k < 7; ++k) {
                m += O::channel_weight(k) * seg_fraction(xs[k], rho, t);
                b += O::channel_weight(k) * (xs[k] >= t ? 1.0 : 0.0);
            }
            max_model = std::fmax(max_model, std::fabs(m - exact(t)));
            max_bool = std::fmax(max_bool, std::fabs(b - exact(t)));
            if (m > prev_m + 1e-12 || b > prev_b + 1e-12) mono = false;
            prev_m = m;
            prev_b = b;
            if (t >= 1.0 && std::fabs(m) > 1e-12) ends = false;
            if (t <= -1.0 && std::fabs(m - 1.0) > 1e-12) ends = false;
        }
        tb::note("max |error| of the occluded fraction: seven-circle model %.4f ; Boolean model %.4f", max_model, max_bool);
        tb::check_true("T3", "model is 0 for t >= 1 and 1 for t <= -1 (to 1e-12)", ends);
        tb::check_true("T3", "both models are non-increasing in t", mono);
        tb::check_true("T3", "seven-circle model max error <= 0.1", max_model <= 0.1);
        tb::check_true("T3", "Boolean model max error exceeds the seven-circle model's", max_bool > max_model);
    }

    tb::heading("T4 retardation: fixed-point contraction");
    {
        const double D = 10.0, t = 5.0;
        for (double beta : {0.01, 0.1, 0.5, 0.9, 0.99}) {
            const double tr = (t - D) / (1.0 - beta);  // source on x_s = beta*tau (all tau); target at D; D - beta*tau_r > 0 throughout
            double tn = t - D;  // tau_0
            const double e0 = std::fabs(tn - tr);
            double ratio = 0.0;
            long it = 0;
            double e = e0;
            while (e > 1e-9 && it < 100000) {
                const double tn1 = t - std::fabs(D - beta * tn);
                const double en1 = std::fabs(tn1 - tr);
                if (it == 0) ratio = en1 / e;  // first iteration: errors far above the double-precision floor
                tn = tn1;
                e = en1;
                ++it;
            }
            const long predicted = static_cast<long>(std::ceil(std::log(1e-9 / e0) / std::log(beta)));
            char lab[160];
            std::snprintf(lab, sizeof lab, "beta=%.2f: observed ratio %.6f ; iterations %ld (predicted %ld)", beta, ratio, it, predicted);
            tb::note("%s", lab);
            tb::check("T4", "error ratio per iteration equals beta", ratio, beta, 1e-6);
            tb::check_true("T4", "iteration count within 1 of ceil(ln(tol/e0)/ln(beta))", std::labs(it - predicted) <= 1);
        }
    }

    return tb::finish();
}
