// Chapter 53 — collapse and singularity: worked-example instrument (generic stand-ins, no engine function).
// Pre-registration: Textbook/validation/ch53_PRE_REGISTRATION.md (registered before this file existed).
#include "tb_common.hpp"

#include <array>
#include <cmath>
#include <vector>

namespace {

// D(chimax) = int_1^chimax chi^(m-p-k) dchi, by quadrature in ln chi: int chi^(e+1) dlnchi with e = m-p-k
double D_quad(double m, double p, double k, double chimax) {
    const double e = m - p - k;
    return tb::integrate([&](double u) { return std::exp((e + 1.0) * u); }, 0.0, std::log(chimax), 32, 400);
}
double D_closed(double m, double p, double k, double chimax) {
    const double a = k + p - m - 1.0;
    if (std::fabs(a) < 1e-14) return std::log(chimax);
    return (1.0 - std::pow(chimax, -a)) / a;
}

struct V3 {
    double x, y, z;
};
V3 rot_z(V3 v, double a) { return {std::cos(a) * v.x - std::sin(a) * v.y, std::sin(a) * v.x + std::cos(a) * v.y, v.z}; }
V3 rot_x(V3 v, double a) { return {v.x, std::cos(a) * v.y - std::sin(a) * v.z, std::sin(a) * v.y + std::cos(a) * v.z}; }
double dist(V3 a, V3 b) { return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z)); }

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    tb::check("V1", "int_1^1e12 chi^-3 dchi equals the truncated closed form", D_quad(1, 3, 1, 1e12), D_closed(1, 3, 1, 1e12), 1e-9);
    tb::check("V1", "int_1^1e12 chi^-3 dchi is close to 1/2", D_quad(1, 3, 1, 1e12), 0.5, 1e-9);
    tb::check("V1", "int_1^chimax chi^-1 dchi = ln chimax", D_quad(1, 2, 0, 1e6), std::log(1e6), 1e-9);
    {
        const V3 pt{0, 0, 3.0};
        tb::check("V1", "rotation of (0,0,3) about z by 0.7 leaves it unchanged", dist(rot_z(pt, 0.7), pt), 0.0, 1e-16, false);
        tb::check("V1", "rotation about x by 0.7 displaces it by 2 s sin(alpha/2)", dist(rot_x(pt, 0.7), pt), 2.0 * 3.0 * std::sin(0.35), 1e-12);
    }

    struct Set {
        double m, p, k;
    };
    const Set sets[7] = {{1, 3, 1}, {1, 2, 1}, {1, 1.5, 1}, {1, 1.2, 1}, {2, 2.5, 0.5}, {2, 1, 1}, {0, 0, 1}};

    tb::heading("T1 arrest and late displacement are separate conditions");
    for (const auto& s : sets) {
        const double D6 = D_quad(s.m, s.p, s.k, 1e6), D12 = D_quad(s.m, s.p, s.k, 1e12);
        const double c6 = D_closed(s.m, s.p, s.k, 1e6), c12 = D_closed(s.m, s.p, s.k, 1e12);
        const double v6 = std::pow(1e6, s.m - s.p), v12 = std::pow(1e12, s.m - s.p);
        const bool arrest = v12 < v6, rule_arrest = s.p > s.m;
        const double dD = D12 - D6;
        const bool finite = s.k + s.p - s.m > 1.0;
        char lab[200];
        std::snprintf(lab, sizeof lab, "(m,p,k) = (%g,%g,%g): quadrature equals the closed form at 1e6 and 1e12 (worst relative difference)", s.m, s.p, s.k);
        tb::check("T1", lab, std::fmax(std::fabs(D6 / c6 - 1.0), std::fabs(D12 / c12 - 1.0)), 0.0, 1e-9, false);
        tb::note("v(1e6) = %.3e, v(1e12) = %.3e ; D(1e6) = %.6f, D(1e12) = %.6f, increase %.4f ; k+p-m = %.2f", v6, v12, D6, D12, dD, s.k + s.p - s.m);
        std::snprintf(lab, sizeof lab, "(%g,%g,%g): velocity falls with chi exactly when p > m", s.m, s.p, s.k);
        tb::check_true("T1", lab, arrest == rule_arrest);
        std::snprintf(lab, sizeof lab, "(%g,%g,%g): displacement increase below 0.5 exactly when k+p-m > 1 (above 5 otherwise)", s.m, s.p, s.k);
        const bool ok = finite ? (dD < 0.5) : (dD > 5.0 || dD < 0.0 + 1e-300 ? dD > 5.0 : false);
        tb::check_true("T1", lab, ok);
    }
    {
        const double D6 = D_quad(2, 2.5, 0.5, 1e6), D12 = D_quad(2, 2.5, 0.5, 1e12);
        tb::note("arrest without finite displacement: (2,2.5,0.5): D(1e6) = %.5f, D(1e12) = %.5f, increase %.5f (ln 1e6 = %.5f)", D6, D12, D12 - D6, std::log(1e6));
        tb::check("T1", "arrest with divergent displacement: the increase equals ln(1e6)", D12 - D6, std::log(1e6), 1e-9);
    }

    tb::heading("T2 traction can diverge while the velocity goes to zero");
    for (const auto& s : sets) {
        const double t6 = std::pow(1e6, s.m), t12 = std::pow(1e12, s.m);
        char lab[160];
        std::snprintf(lab, sizeof lab, "(%g,%g,%g): traction chi^m grows with chi exactly when m > 0", s.m, s.p, s.k);
        tb::check_true("T2", lab, (t12 > t6 * (1.0 + 1e-12)) == (s.m > 0.0));
    }
    tb::check_true("T2", "(1,3,1) arrests (v -> 0) while the traction chi^1 grows without limit", std::pow(1e12, 1.0 - 3.0) < std::pow(1e6, 1.0 - 3.0) && std::pow(1e12, 1.0) > std::pow(1e6, 1.0));

    tb::heading("T3 axial degeneration");
    {
        double worst_axis = 0.0, worst_tilt = 0.0;
        for (double s : {-2.0, -1.0, 0.5, 3.0}) {
            const V3 p{0, 0, s};
            worst_axis = std::fmax(worst_axis, dist(rot_z(p, 0.7), p));
            worst_tilt = std::fmax(worst_tilt, std::fabs(dist(rot_x(p, 0.7), p) / (2.0 * std::fabs(s) * std::sin(0.35)) - 1.0));
        }
        tb::check("T3", "displacement of axis points under rotation about the axis (worst)", worst_axis, 0.0, 1e-16, false);
        tb::check("T3", "displacement under rotation about a transverse axis = 2|s| sin(alpha/2) (worst relative error)", worst_tilt, 0.0, 1e-12, false);
        const double s1 = 1.0 * 1.0, s2 = 1e-4 * 1.0;
        tb::check("T3", "speed R phidot falls by 1e-4 as R falls from 1 to 1e-4 at fixed phidot", s2 / s1, 1e-4, 1e-12);
        tb::note("atan2(0,0) = %.1f at rho = 0 (library convention; the angle is formally undefined)", std::atan2(0.0, 0.0));
    }

    tb::heading("T4 four independent checks over a parameter grid");
    {
        const double ms[5] = {-1, -0.5, 0, 0.5, 1};
        const double ps[8] = {-1, -0.5, 0, 0.5, 1, 1.5, 2, 3};
        int n = 0, n_arrest = 0, n_finite = 0, n_energy = 0, n_trac = 0, n_all = 0, mismatch = 0;
        for (double m : ms)
            for (double p : ps) {
                const double k = 1.0, w = m;
                ++n;
                const bool a = p > m, f = (k + p - m > 1.0), e = w <= 0.0, t = m <= 0.0;
                // numerical classification
                const double v6 = std::pow(1e6, m - p), v12 = std::pow(1e12, m - p);
                const bool a_num = v12 < v6 * (1.0 - 1e-12);
                const double dD = D_quad(m, p, k, 1e12) - D_quad(m, p, k, 1e6);
                const bool f_num = dD < 0.5;
                const bool e_num = std::pow(1e12, w) <= std::pow(1e6, w) * (1.0 + 1e-12);
                const bool t_num = std::pow(1e12, m) <= std::pow(1e6, m) * (1.0 + 1e-12);
                if (a != a_num || f != f_num || e != e_num || t != t_num) ++mismatch;
                n_arrest += a;
                n_finite += f;
                n_energy += e;
                n_trac += t;
                n_all += (a && f && e && t);
            }
        tb::note("grid of %d models: arrest %d ; finite displacement %d ; bounded energy %d ; bounded traction %d ; all four %d", n, n_arrest, n_finite, n_energy, n_trac, n_all);
        tb::check_true("T4", "the rules agree with the numerical classification at every grid point", mismatch == 0);
        tb::check_true("T4", "the number passing all four is less than the number passing arrest alone", n_all < n_arrest);
    }

    return tb::finish();
}
