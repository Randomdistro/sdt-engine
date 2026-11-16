// Chapter 10 — occlusion geometry: worked-example instrument.
// Pre-registration: Textbook/validation/ch10_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch10_occlusion_geometry
#include <sdt/laws.hpp>
#include <sdt/occlusion.hpp>

#include "tb_common.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <vector>

namespace {

constexpr double kPi = std::numbers::pi;

// Overlap area of two discs of radii R1, R2 whose centres are d apart.
double lens_area(double R1, double R2, double d) {
    if (d >= R1 + R2) return 0.0;
    if (d <= std::fabs(R1 - R2)) {
        const double m = std::fmin(R1, R2);
        return kPi * m * m;
    }
    const double a1 = std::acos(std::clamp((d * d + R1 * R1 - R2 * R2) / (2.0 * d * R1), -1.0, 1.0));
    const double a2 = std::acos(std::clamp((d * d + R2 * R2 - R1 * R1) / (2.0 * d * R2), -1.0, 1.0));
    const double k = (-d + R1 + R2) * (d + R1 - R2) * (d - R1 + R2) * (d + R1 + R2);
    return R1 * R1 * a1 + R2 * R2 * a2 - 0.5 * std::sqrt(std::fmax(k, 0.0));
}

double cap_area(double eta) { return 2.0 * kPi * (1.0 - std::cos(eta)); }

// Overlap of two spherical caps (half-angles a, b; axes separated by delta), closed form.
double cap_overlap(double a, double b, double delta) {
    if (delta >= a + b) return 0.0;
    if (delta <= std::fabs(a - b)) return cap_area(std::fmin(a, b));
    const double sa = std::sin(a), sb = std::sin(b), cd = std::cos(delta), sd = std::sin(delta);
    const double t1 = std::acos(std::clamp((std::cos(b) - std::cos(a) * cd) / (sa * sd), -1.0, 1.0));
    const double t2 = std::acos(std::clamp((std::cos(a) - std::cos(b) * cd) / (sb * sd), -1.0, 1.0));
    const double t3 = std::acos(std::clamp((cd - std::cos(a) * std::cos(b)) / (sa * sb), -1.0, 1.0));
    return 2.0 * kPi - 2.0 * std::cos(a) * t1 - 2.0 * std::cos(b) * t2 - 2.0 * t3;
}

// Independent route 1: integrate the azimuthal width of cap 2 inside cap 1 over the polar angle about axis 1.
double cap_overlap_integral(double a, double b, double delta) {
    auto width = [&](double th) {
        const double kappa = (std::cos(b) - std::cos(th) * std::cos(delta)) / (std::sin(th) * std::sin(delta));
        if (kappa <= -1.0) return 2.0 * kPi;
        if (kappa >= 1.0) return 0.0;
        return 2.0 * std::acos(kappa);
    };
    return tb::integrate([&](double th) { return std::sin(th) * width(th); }, 1e-12, a, 24, 4000);
}

// Independent route 2: equal-area grid (centre-point sampling) on the sphere of directions.
double cap_overlap_grid(double a, double b, double delta, int nmu, int nphi) {
    const double ca = std::cos(a), cb = std::cos(b), cd = std::cos(delta), sd = std::sin(delta);
    long long inside = 0;
    for (int i = 0; i < nmu; ++i) {
        const double mu = -1.0 + 2.0 * (i + 0.5) / nmu;  // cos(theta) about axis 1 (the z axis)
        const double st = std::sqrt(1.0 - mu * mu);
        if (mu < ca) continue;  // outside cap 1
        for (int j = 0; j < nphi; ++j) {
            const double ph = 2.0 * kPi * (j + 0.5) / nphi;
            // axis 2 lies in the xz-plane at angle delta from z
            const double dot2 = mu * cd + st * std::cos(ph) * sd;
            if (dot2 >= cb) ++inside;
        }
    }
    return 4.0 * kPi * static_cast<double>(inside) / (static_cast<double>(nmu) * nphi);
}

// Axial force removed (in units of q) by sphere 1 from sphere 2 at centre distance r, parallel-ray model.
double removed_force(double R1, double R2, double r) {
    const double top = std::fmin(R1 + R2, r);
    std::vector<double> bp{0.0};
    for (double b : {std::fabs(R1 - R2), R1 + R2})
        if (b > 0.0 && b < top) bp.push_back(b);
    bp.push_back(top);
    std::sort(bp.begin(), bp.end());
    double sum = 0.0;
    for (std::size_t i = 0; i + 1 < bp.size(); ++i)
        sum += tb::integrate([&](double d) { return d * lens_area(R1, R2, d); }, bp[i], bp[i + 1], 48, 40);
    return 2.0 * kPi * sum / (r * r);
}

}  // namespace

int main() {
    namespace L = sdt::laws;
    namespace O = sdt::occlusion;
    using sdt::dynamics::Vec3;
    tb::validate_helpers();

    tb::heading("V1 planar lens area");
    tb::check("V1", "unit circles at d = 1: 2 pi/3 - sqrt3/2", lens_area(1, 1, 1), 2.0 * kPi / 3.0 - std::sqrt(3.0) / 2.0, 1e-13);
    tb::check("V1", "d = 0: pi", lens_area(1, 1, 0), kPi, 1e-13);
    tb::check_true("V1", "d >= 2: 0", lens_area(1, 1, 2.0) == 0.0 && lens_area(1, 1, 3.0) == 0.0);
    tb::check("V1", "R1 = 2, R2 = 1, d = 0.5 (nested): pi", lens_area(2, 1, 0.5), kPi, 1e-13);

    tb::heading("V2 spherical lens closed form");
    {
        const double eta = 0.7;
        tb::check("V2", "coincident caps: cap area", cap_overlap(eta, eta, 0.0), cap_area(eta), 1e-13);
        tb::check("V2", "nested caps: the smaller cap", cap_overlap(0.9, 0.4, 0.3), cap_area(0.4), 1e-13);
        tb::check_true("V2", "externally tangent caps: 0", cap_overlap(0.5, 0.3, 0.8) == 0.0);
        tb::check("V2", "hemispheres at 90 deg: pi", cap_overlap(kPi / 2, kPi / 2, kPi / 2), kPi, 1e-13);
        tb::check("V2", "hemispheres at 60 deg: 4 pi/3", cap_overlap(kPi / 2, kPi / 2, kPi / 3), 4.0 * kPi / 3.0, 1e-13);
        tb::check_true("V2", "hemispheres at 180 deg: 0", std::fabs(cap_overlap(kPi / 2, kPi / 2, kPi)) < 1e-13);
    }

    tb::heading("T1 spherical lens: closed form against two independent routes");
    {
        struct Cfg {
            double a, b, d;
        };
        const Cfg cfgs[] = {{0.5, 0.3, 0.4}, {0.5, 0.5, 0.5}, {0.9, 0.4, 0.7}, {1.2, 0.8, 1.0}, {0.3, 0.3, 0.55}, {1.0, 1.0, 1.5}, {0.6, 0.2, 0.7}, {1.4, 0.6, 1.2}};
        double worst_int = 0.0;
        for (const Cfg& c : cfgs) {
            const double cf = cap_overlap(c.a, c.b, c.d), ig = cap_overlap_integral(c.a, c.b, c.d);
            worst_int = std::fmax(worst_int, std::fabs(ig / cf - 1.0));
        }
        tb::check("T1", "closed form vs polar-angle integration, worst relative over 8 configurations", worst_int, 0.0, 1e-5, false);
        double worst_grid = 0.0;
        for (int i : {0, 2, 5}) {
            const Cfg& c = cfgs[i];
            const double cf = cap_overlap(c.a, c.b, c.d), gr = cap_overlap_grid(c.a, c.b, c.d, 3000, 6000);
            worst_grid = std::fmax(worst_grid, std::fabs(gr / cf - 1.0));
            tb::note("(%.1f, %.1f, %.2f): closed form %.9f, grid %.9f", c.a, c.b, c.d, cf, gr);
        }
        tb::check("T1", "closed form vs equal-area grid, worst relative over 3 configurations", worst_grid, 0.0, 3e-3, false);
    }

    tb::heading("T2 union of two shadows");
    {
        const double a = 5.0 * kPi / 180.0, b = 3.0 * kPi / 180.0;
        const double O1 = cap_area(a), O2 = cap_area(b);
        bool ok = true;
        for (double deg : {0.0, 4.0, 7.0, 8.0, 9.0}) {
            const double d = deg * kPi / 180.0;
            const double inter = cap_overlap(a, b, d);
            const double uni = O1 + O2 - inter;
            const bool lo = uni >= std::fmax(O1, O2) - 1e-15, hi = uni <= O1 + O2 + 1e-15;
            const bool strict = (deg < 8.0) ? (uni < O1 + O2 - 1e-12) : (std::fabs(uni - (O1 + O2)) < 1e-12);
            ok = ok && lo && hi && strict;
            tb::note("separation %.0f deg: overlap %.6e sr, union %.6e sr, sum of independent shadows %.6e sr (overstated by %.2f%%)", deg, inter, uni, O1 + O2, 100.0 * inter / uni);
        }
        tb::check_true("T2", "bounds on the union and strictness exactly when the caps overlap", ok);
        tb::check("T2", "nested at 0 deg: union equals the larger cap", O1 + O2 - cap_overlap(a, b, 0.0), O1, 1e-13);
    }

    tb::heading("T3 finite-body occlusion force of two spheres (parallel-ray response model)");
    {
        struct Pair {
            double R1, R2;
        };
        const Pair pairs[] = {{1, 1}, {1, 0.2}, {3, 1}, {1, 3}};
        double worst = 0.0;
        for (const Pair& p : pairs) {
            const double s = p.R1 + p.R2;
            for (double f : {1.0, 1.05, 2.0, 10.0, 100.0}) {
                const double r = f * s;
                const double ratio = removed_force(p.R1, p.R2, r) / (kPi * kPi * p.R1 * p.R1 * p.R2 * p.R2 / (r * r));
                worst = std::fmax(worst, std::fabs(ratio - 1.0));
                if (f == 1.0 || f == 10.0) tb::note("R1 = %.1f, R2 = %.1f, r = %.3f (= %.2f (R1+R2)): F / F_LawIII = %.12f", p.R1, p.R2, r, f, ratio);
            }
        }
        tb::check("T3", "F / (q pi^2 R1^2 R2^2 / r^2) - 1, worst over 20 cases with r >= R1 + R2", worst, 0.0, 1e-9, false);
        bool below = true;
        for (const Pair& p : pairs) {
            const double r = 0.75 * (p.R1 + p.R2);
            const double ratio = removed_force(p.R1, p.R2, r) / (kPi * kPi * p.R1 * p.R1 * p.R2 * p.R2 / (r * r));
            below = below && ratio < 1.0;
            tb::note("R1 = %.1f, R2 = %.1f, r = 0.75 (R1+R2) (overlapping bodies, unphysical): ratio %.6f", p.R1, p.R2, ratio);
        }
        tb::check_true("T3", "ratio < 1 for r < R1 + R2 in all four pairs", below);
    }

    tb::heading("T4 the engine's occlusion quadrature and seven-circle geometry");
    {
        // (a) fixed 6 x 16 disc quadrature against the exact axial form
        const Vec3 centre{0, 0, 0}, normal{0, 0, 1}, first{1, 0, 0}, second{0, 1, 0};
        double wsum = 0.0;
        O::for_each_disc_node(centre, first, second, 1.0, [&](const O::DiscNode& n) { wsum += n.area_weight_m2; });
        tb::check("T4", "quadrature weights sum to pi R^2 (R = 1)", wsum, kPi, 1e-14);
        bool within = true;
        for (double dR : {0.5, 1.0, 2.0, 5.0, 10.0, 100.0}) {
            const Vec3 obs{0, 0, dR};
            const double q = O::disc_solid_angle(obs, centre, normal, first, second, 1.0);
            const double e = O::axial_disc_solid_angle(dR, 1.0);
            tb::note("d/R = %6.1f: quadrature %.12e sr, exact %.12e sr, relative error %.2e", dR, q, e, std::fabs(q / e - 1.0));
            if (dR >= 1.0) within = within && std::fabs(q / e - 1.0) <= 1e-3;
        }
        tb::check_true("T4", "relative error <= 1e-3 for d/R >= 1", within);
        // (b) seven circles
        tb::check("T4", "central_weight + 6 outer_weight = 1", O::central_weight + 6.0 * O::outer_weight, 1.0, 1e-14);
        const O::PairFrame fr = O::pair_frame(Vec3{0, 0, 1});
        std::array<Vec3, 7> c;
        for (std::size_t k = 0; k < 7; ++k) c[k] = O::channel_offset(k, 1.0, fr);
        double ring = 0.0, adj = 0.0, reach = 0.0;
        for (std::size_t k = 1; k < 7; ++k) {
            ring = std::fmax(ring, std::fabs(sdt::dynamics::norm(c[k]) - 2.0 / 3.0));
            const std::size_t nx = k == 6 ? 1 : k + 1;
            adj = std::fmax(adj, std::fabs(sdt::dynamics::norm(c[nx] - c[k]) - 2.0 / 3.0));
            reach = std::fmax(reach, sdt::dynamics::norm(c[k]) + 1.0 / 3.0);
        }
        tb::check("T4", "ring channel centres at 2R/3 from the centre (worst deviation)", ring, 0.0, 1e-14, false);
        tb::check("T4", "adjacent ring centres 2R/3 apart: tangent discs of radius R/3 (worst deviation)", adj, 0.0, 1e-14, false);
        tb::check("T4", "outermost point of the ring discs reaches R", reach, 1.0, 1e-14);
        tb::check("T4", "total area of the seven discs / (pi R^2) = 7/9", 7.0 * kPi / 9.0 / kPi, 7.0 / 9.0, 1e-14);
    }

    return tb::finish();
}
