// Chapter 1 — contact-boundary continuity: worked-example instruments.
// Pre-registration: Textbook/validation/ch01_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch01_contact_boundary_continuity
#include <sdt/laws.hpp>
#include <sdt/lattice_structure.hpp>

#include "tb_common.hpp"

#include <array>
#include <cmath>
#include <map>
#include <tuple>
#include <vector>

namespace {

using V3 = std::array<double, 3>;
constexpr double kPi = std::numbers::pi;

V3 sub(const V3& a, const V3& b) { return {a[0] - b[0], a[1] - b[1], a[2] - b[2]}; }
double dot(const V3& a, const V3& b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
V3 cross(const V3& a, const V3& b) {
    return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]};
}
double norm(const V3& a) { return std::sqrt(dot(a, a)); }
double dist(const V3& a, const V3& b) { return norm(sub(a, b)); }

// Outward unit normal of the face (a, b, c) of a polyhedron whose centroid is `centre`.
V3 outward_normal(const V3& a, const V3& b, const V3& c, const V3& centre) {
    V3 n = cross(sub(b, a), sub(c, a));
    const double m = norm(n);
    n = {n[0] / m, n[1] / m, n[2] / m};
    if (dot(n, sub(a, centre)) < 0.0) n = {-n[0], -n[1], -n[2]};
    return n;
}

// Interior dihedral angle between two faces that share an edge [rad].
double dihedral(const V3& n1, const V3& n2) { return kPi - std::acos(dot(n1, n2)); }

// ---- breadth-first relay reach on a regular lattice (integer coordinates) -----------------------
using Cell = std::tuple<int, int, int>;
using Step = std::array<int, 3>;

std::map<Cell, int> bfs(const std::vector<Step>& steps, int nmax) {
    std::map<Cell, int> d;
    std::vector<Cell> frontier{{0, 0, 0}};
    d[{0, 0, 0}] = 0;
    for (int n = 1; n <= nmax; ++n) {
        std::vector<Cell> next;
        for (const Cell& c : frontier) {
            for (const Step& s : steps) {
                const Cell q{std::get<0>(c) + s[0], std::get<1>(c) + s[1], std::get<2>(c) + s[2]};
                if (!d.count(q)) {
                    d[q] = n;
                    next.push_back(q);
                }
            }
        }
        frontier = std::move(next);
    }
    return d;
}

std::vector<Step> steps_sc() { return {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}}; }
std::vector<Step> steps_fcc() {
    std::vector<Step> s;
    for (int a : {-1, 1})
        for (int b : {-1, 1}) {
            s.push_back({a, b, 0});
            s.push_back({a, 0, b});
            s.push_back({0, a, b});
        }
    return s;
}
std::vector<Step> steps_bcc() {
    std::vector<Step> s;
    for (int a : {-1, 1})
        for (int b : {-1, 1})
            for (int c : {-1, 1}) s.push_back({a, b, c});
    return s;
}

// Support function of the neighbour-vector polytope along unit direction u, in units of one hop.
double support(const std::vector<Step>& steps, const V3& u) {
    double best = -1e300;
    for (const Step& s : steps) {
        const V3 v{double(s[0]), double(s[1]), double(s[2])};
        best = std::fmax(best, dot(v, u) / norm(v));
    }
    return best;
}

V3 unit(double x, double y, double z) {
    const double m = std::sqrt(x * x + y * y + z * z);
    return {x / m, y / m, z / m};
}

}  // namespace

int main() {
    namespace LS = sdt::laws::lattice_structure;
    namespace L = sdt::laws;
    tb::validate_helpers();

    tb::heading("V1 polyhedron dihedral routine on known solids");
    {
        const V3 o{0, 0, 0};
        // cube: faces x = +1 and y = +1
        tb::check("V1", "cube dihedral = 90 deg",
                  dihedral(outward_normal({1, 1, 1}, {1, -1, 1}, {1, 1, -1}, o),
                           outward_normal({1, 1, 1}, {-1, 1, 1}, {1, 1, -1}, o)) * 180.0 / kPi,
                  90.0, 1e-9);
        // octahedron: faces (+,+,+) and (+,+,-)
        tb::check("V1", "octahedron dihedral = arccos(-1/3) = 109.4712206 deg",
                  dihedral(outward_normal({1, 0, 0}, {0, 1, 0}, {0, 0, 1}, o),
                           outward_normal({1, 0, 0}, {0, 1, 0}, {0, 0, -1}, o)) * 180.0 / kPi,
                  109.4712206344907, 1e-9);
        // icosahedron (0,+-1,+-phi) cyclic: faces sharing the edge (0,1,phi)-(0,-1,phi)
        const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
        tb::check("V1", "icosahedron dihedral = 138.1896851 deg",
                  dihedral(outward_normal({0, 1, phi}, {0, -1, phi}, {phi, 0, 1}, o),
                           outward_normal({0, 1, phi}, {0, -1, phi}, {-phi, 0, 1}, o)) * 180.0 / kPi,
                  138.1896851042214, 1e-9);
    }

    tb::heading("V2 breadth-first shell populations (coordination sequences)");
    {
        const auto sc = bfs(steps_sc(), 6), fcc = bfs(steps_fcc(), 6), bcc = bfs(steps_bcc(), 6);
        bool ok_sc = true, ok_fcc = true, ok_bcc = true;
        for (int n = 1; n <= 6; ++n) {
            int csc = 0, cfcc = 0, cbcc = 0;
            for (const auto& kv : sc) csc += (kv.second == n);
            for (const auto& kv : fcc) cfcc += (kv.second == n);
            for (const auto& kv : bcc) cbcc += (kv.second == n);
            ok_sc = ok_sc && csc == 4 * n * n + 2;
            ok_fcc = ok_fcc && cfcc == 10 * n * n + 2;
            ok_bcc = ok_bcc && cbcc == 6 * n * n + 2;
        }
        tb::check_true("V2", "simple cubic shell populations 4n^2+2, n=1..6", ok_sc);
        tb::check_true("V2", "face-centred cubic shell populations 10n^2+2, n=1..6", ok_fcc);
        tb::check_true("V2", "body-centred cubic shell populations 6n^2+2, n=1..6", ok_bcc);
    }

    // diamond cubic cell, lattice constant 1
    std::vector<V3> basis;
    {
        const std::vector<V3> fcc{{0, 0, 0}, {0, .5, .5}, {.5, 0, .5}, {.5, .5, 0}};
        for (const V3& p : fcc) {
            basis.push_back(p);
            basis.push_back({p[0] + .25, p[1] + .25, p[2] + .25});
        }
    }
    double d_nn = 1e300;
    int coordination = 0;
    {
        tb::heading("V3 diamond-cubic cell");
        const V3 origin = basis[0];
        for (int i = -1; i <= 1; ++i)
            for (int j = -1; j <= 1; ++j)
                for (int k = -1; k <= 1; ++k)
                    for (std::size_t b = 0; b < basis.size(); ++b) {
                        const V3 q{basis[b][0] + i, basis[b][1] + j, basis[b][2] + k};
                        const double d = dist(origin, q);
                        if (d > 1e-12) d_nn = std::fmin(d_nn, d);
                    }
        for (int i = -1; i <= 1; ++i)
            for (int j = -1; j <= 1; ++j)
                for (int k = -1; k <= 1; ++k)
                    for (std::size_t b = 0; b < basis.size(); ++b) {
                        const V3 q{basis[b][0] + i, basis[b][1] + j, basis[b][2] + k};
                        if (std::fabs(dist(origin, q) - d_nn) < 1e-12) ++coordination;
                    }
        tb::check_true("V3", "8 atoms per cubic cell", basis.size() == 8);
        tb::check_true("V3", "nearest-neighbour count 4", coordination == 4);
    }

    tb::heading("T1 tetrahedron dihedral from coordinates");
    {
        const V3 a{1, 1, 1}, b{1, -1, -1}, c{-1, 1, -1}, d{-1, -1, 1}, o{0, 0, 0};
        const double delta = dihedral(outward_normal(a, b, c, o), outward_normal(a, b, d, o));
        tb::check("T1", "tetrahedron dihedral vs lattice_structure::dihedral_rad", delta, LS::dihedral_rad, 1e-14,
                  false);
        tb::check("T1", "supplement vs lattice_structure::bond_angle_rad", kPi - delta, LS::bond_angle_rad, 1e-14,
                  false);
        tb::note("dihedral = %.9f deg; bond angle = %.9f deg", delta * 180.0 / kPi, (kPi - delta) * 180.0 / kPi);
    }

    tb::heading("T2 five tetrahedra about an edge");
    {
        const V3 a{1, 1, 1}, b{1, -1, -1}, c{-1, 1, -1}, d{-1, -1, 1}, o{0, 0, 0};
        const double delta = dihedral(outward_normal(a, b, c, o), outward_normal(a, b, d, o));
        const double deficit = 2.0 * kPi - 5.0 * delta;
        tb::check("T2", "deficit 2 pi - 5 delta vs five_edge_deficit_rad", deficit, LS::five_edge_deficit_rad, 1e-14,
                  false);
        tb::check_true("T2", "deficit is positive (five tetrahedra cannot close flat space)", deficit > 0.0);
        tb::note("deficit = %.9f rad = %.6f deg", deficit, deficit * 180.0 / kPi);
    }

    tb::heading("T3 twelve spheres about one (icosahedral kissing shell)");
    {
        const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
        std::vector<V3> v;
        for (int s1 : {-1, 1})
            for (int s2 : {-1, 1}) {
                v.push_back({0, double(s1), s2 * phi});
                v.push_back({double(s1), s2 * phi, 0});
                v.push_back({s2 * phi, 0, double(s1)});
            }
        const double scale = 2.0 / norm(v[0]);  // centres at distance 2 from the central unit sphere's centre
        for (V3& p : v) p = {p[0] * scale, p[1] * scale, p[2] * scale};
        double dmin = 1e300, rmin = 1e300, rmax = 0.0;
        for (std::size_t i = 0; i < v.size(); ++i) {
            rmin = std::fmin(rmin, norm(v[i]));
            rmax = std::fmax(rmax, norm(v[i]));
            for (std::size_t j = i + 1; j < v.size(); ++j) dmin = std::fmin(dmin, dist(v[i], v[j]));
        }
        tb::check_true("T3", "12 centres, all at distance 2 from the origin",
                       v.size() == 12 && std::fabs(rmin - 2.0) < 1e-13 && std::fabs(rmax - 2.0) < 1e-13);
        tb::check("T3", "minimum shell-centre separation minus 2 vs icosa_shell_gap_over_r", dmin - 2.0,
                  LS::icosa_shell_gap_over_r, 1e-13, false);
        tb::check_true("T3", "gap is positive (the twelve touching spheres leave the shell unclosed)", dmin - 2.0 > 0.0);
        tb::note("edge/diameter = %.9f; gap = %.9f sphere radii", dmin / 2.0, dmin - 2.0);
    }

    tb::heading("T4 Boerdijk-Coxeter helix");
    {
        const double rho = LS::bc_radius_over_a, th = LS::bc_twist_rad, h = LS::bc_rise_over_a;
        auto P = [&](int k) { return V3{rho * std::cos(k * th), rho * std::sin(k * th), k * h}; };
        double worst = 0.0, min4 = 1e300;
        for (int k = 0; k <= 40; ++k)
            for (int j = 1; j <= 3; ++j) worst = std::fmax(worst, std::fabs(dist(P(k), P(k + j)) - 1.0));
        for (int k = 0; k <= 40; ++k) min4 = std::fmin(min4, dist(P(k), P(k + 4)));
        tb::check("T4", "|P_k - P_{k+j}| = 1 for j = 1, 2, 3 (worst deviation, k = 0..40)", worst, 0.0, 1e-13, false);
        tb::check_true("T4", "|P_k - P_{k+4}| > 1 (the fifth vertex is not an edge neighbour)", min4 > 1.0);
        tb::note("twist = %.6f deg; |P_k - P_{k+4}| minimum = %.9f", th * 180.0 / kPi, min4);
        tb::note("cos(twist) = -2/3 is rational and not 0, +-1/2, +-1, so twist/pi is irrational (Niven): the helix is aperiodic");
    }

    tb::heading("T5 diamond-cubic packing");
    {
        const double r = d_nn / 2.0;
        const double packing = 8.0 * (4.0 * kPi / 3.0) * r * r * r;  // lattice constant 1
        tb::check("T5", "8 spheres of radius d_nn/2 per cell vs packing_fraction_diamond", packing,
                  LS::packing_fraction_diamond, 1e-14);
        tb::check("T5", "void fraction vs void_fraction_diamond", 1.0 - packing, LS::void_fraction_diamond, 1e-14);
        tb::note("d_nn = %.9f (sqrt(3)/4 = %.9f); packing = %.9f; void = %.9f", d_nn, std::sqrt(3.0) / 4.0, packing,
                 1.0 - packing);
    }

    tb::heading("T6 Law IV volume relations and cell counts (engine consistency)");
    {
        const double Phi = L::law_I::Phi, l3 = L::measured::l_P3, c = L::measured::c;
        const double Vp = 3.0 * L::measured::m_p * l3 * c * c / Phi;
        const double Ve = 3.0 * L::measured::m_e * l3 * c * c / Phi;
        tb::check("T6", "V_disp_p vs 3 m_p l_P^3 c^2 / Phi", L::law_IV::V_disp_p, Vp, 1e-12);
        tb::check("T6", "V_disp_e vs 3 m_e l_P^3 c^2 / Phi", L::law_IV::V_disp_e, Ve, 1e-12);
        tb::check("T6", "V_disp_from_mass(m_p) vs V_disp_p", L::law_IV::V_disp_from_mass(L::measured::m_p),
                  L::law_IV::V_disp_p, 1e-12);
        tb::check("T6", "R_excl_p vs (3 V_disp_p / 4 pi)^(1/3)", L::law_IV::R_excl_p,
                  std::cbrt(3.0 * Vp / (4.0 * kPi)), 1e-12);
        tb::check("T6", "R_excl_e vs (3 V_disp_e / 4 pi)^(1/3)", L::law_IV::R_excl_e,
                  std::cbrt(3.0 * Ve / (4.0 * kPi)), 1e-12);
        tb::check("T6", "mass_from_V_disp(V_disp_p) vs m_p (CONSTRUCTION: one input on both sides)",
                  L::law_IV::mass_from_V_disp(L::law_IV::V_disp_p), L::measured::m_p, 1e-12);
        tb::check("T6", "rho_eff_e c^2 vs P_conv/3 (CONSTRUCTION)", L::law_IV::P_cf_e, L::law_I::P_conv / 3.0, 1e-12);
        const double Venv = 4.0 * kPi / 3.0 * std::pow(L::measured::R_p, 3);
        tb::note("cell volume l_P^3                         = %.6e m^3", l3);
        tb::note("proton boundary volume (4pi/3)R_p^3       = %.6e m^3 = %.4e cells", Venv, Venv / l3);
        tb::note("proton exclusion volume V_disp_p          = %.6e m^3 = %.4e cells", Vp, Vp / l3);
        tb::note("ratio boundary / exclusion volume (proton) = %.4e", Venv / Vp);
        tb::note("electron exclusion volume V_disp_e        = %.6e m^3 = %.4e cells", Ve, Ve / l3);
        tb::note("R_excl_p = %.6e m; R_excl_e = %.6e m; R_p = %.6e m; r_e = %.6e m", L::law_IV::R_excl_p,
                 L::law_IV::R_excl_e, L::measured::R_p, L::measured::r_e);
        tb::note("V_disp_p / V_disp_e = %.6f ; m_p / m_e = %.6f", Vp / Ve, L::measured::m_p / L::measured::m_e);
        tb::note("cells in the causal domain N = R_CMB / l_P = %.6e ; shells counted by Phi = N eps", L::law_I::N);
    }

    tb::heading("T7 directional reach of nearest-neighbour relay on regular lattices");
    {
        const struct {
            const char* name;
            std::vector<Step> steps;
            double ratio;
        } lat[] = {{"simple cubic", steps_sc(), std::sqrt(3.0)},
                   {"face-centred cubic", steps_fcc(), std::sqrt(2.0)},
                   {"body-centred cubic", steps_bcc(), std::sqrt(3.0)}};
        const V3 dirs[3] = {unit(1, 0, 0), unit(1, 1, 0), unit(1, 1, 1)};
        const char* dname[3] = {"[100]", "[110]", "[111]"};
        for (const auto& l : lat) {
            const int n = 6;
            const auto reach = bfs(l.steps, n);
            double h[3], hbfs[3];
            double hmax = 0.0, hmin = 1e300;
            for (int i = 0; i < 3; ++i) {
                h[i] = support(l.steps, dirs[i]);
                const V3 v0{double(l.steps[0][0]), double(l.steps[0][1]), double(l.steps[0][2])};
                const double hop = norm(v0);
                double best = -1e300;
                for (const auto& kv : reach) {
                    const V3 p{double(std::get<0>(kv.first)), double(std::get<1>(kv.first)),
                               double(std::get<2>(kv.first))};
                    best = std::fmax(best, dot(p, dirs[i]) / hop);
                }
                hbfs[i] = best / n;
                hmax = std::fmax(hmax, h[i]);
                hmin = std::fmin(hmin, h[i]);
                tb::check("T7", (std::string(l.name) + " BFS reach along " + dname[i] + " vs n h_P").c_str(),
                          hbfs[i], h[i], 1e-12);
            }
            tb::check("T7", (std::string(l.name) + " reach ratio max/min over [100],[110],[111]").c_str(), hmax / hmin,
                      l.ratio, 1e-12);
            tb::note("%s: reach per hop along [100] %.6f, [110] %.6f, [111] %.6f", l.name, h[0], h[1], h[2]);
        }
    }

    tb::heading("T8 hop distance on the simple cubic lattice");
    {
        const auto sc = bfs(steps_sc(), 6);
        bool ok = true;
        int missing = 0;
        for (const auto& kv : sc)
            ok = ok && kv.second == std::abs(std::get<0>(kv.first)) + std::abs(std::get<1>(kv.first)) +
                                        std::abs(std::get<2>(kv.first));
        for (int x = -6; x <= 6; ++x)
            for (int y = -6; y <= 6; ++y)
                for (int z = -6; z <= 6; ++z)
                    if (std::abs(x) + std::abs(y) + std::abs(z) <= 6 && !sc.count({x, y, z})) ++missing;
        tb::check_true("T8", "BFS distance = |x|+|y|+|z| for every reached cell, none with |x|+|y|+|z| <= 6 missed",
                       ok && missing == 0);
    }

    return tb::finish();
}
