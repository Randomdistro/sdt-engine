// Chapter 24 — spin, parity and nuclear moments: worked-example instrument.
// Pre-registration: Textbook/validation/ch24_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch24_spin_parity_and_nuclear_moments
#include <sdt/laws.hpp>

#include "tb_common.hpp"

#include <array>
#include <cmath>
#include <string>
#include <vector>

namespace {

constexpr double kPi = std::numbers::pi;
struct Pt {
    double w, x, y, z;
    char kind;
};
using Set = std::vector<Pt>;

double legendre(int l, double x) {
    double p0 = 1.0, p1 = x;
    if (l == 0) return 1.0;
    for (int k = 2; k <= l; ++k) {
        const double p2 = ((2 * k - 1) * x * p1 - (k - 1) * p0) / k;
        p0 = p1;
        p1 = p2;
    }
    return p1;
}

Set centred(Set s) {
    double W = 0, cx = 0, cy = 0, cz = 0;
    for (auto& p : s) { W += p.w; cx += p.w * p.x; cy += p.w * p.y; cz += p.w * p.z; }
    cx /= W; cy /= W; cz /= W;
    for (auto& p : s) { p.x -= cx; p.y -= cy; p.z -= cz; }
    return s;
}

// Invariant I_l = sum_ij w_i w_j r_i^l r_j^l P_l(cos gamma_ij), normalised by (sum w r^l)^2.
double invariant(const Set& s, int l) {
    double num = 0.0, norm = 0.0;
    for (const auto& a : s) norm += a.w * std::pow(std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z), l);
    for (const auto& a : s) {
        const double ra = std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
        for (const auto& b : s) {
            const double rb = std::sqrt(b.x * b.x + b.y * b.y + b.z * b.z);
            double c = 1.0;
            if (ra > 1e-14 && rb > 1e-14) c = (a.x * b.x + a.y * b.y + a.z * b.z) / (ra * rb);
            if (ra <= 1e-14 || rb <= 1e-14) {
                if (l == 0) num += a.w * b.w;  // r^0 convention
                continue;
            }
            num += a.w * b.w * std::pow(ra, l) * std::pow(rb, l) * legendre(l, std::fmax(-1.0, std::fmin(1.0, c)));
        }
    }
    return norm > 0 ? num / (norm * norm) : 0.0;
}

using M3 = std::array<std::array<double, 3>, 3>;

M3 traceless(const Set& s) {
    M3 q{};
    for (const auto& p : s) {
        const double r[3] = {p.x, p.y, p.z};
        const double r2 = r[0] * r[0] + r[1] * r[1] + r[2] * r[2];
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) q[i][j] += p.w * (3.0 * r[i] * r[j] - (i == j ? r2 : 0.0));
    }
    return q;
}

bool inversion_invariant(const Set& in) {
    const Set s = centred(in);
    for (const auto& a : s) {
        bool found = false;
        for (const auto& b : s)
            if (b.kind == a.kind && std::fabs(b.w - a.w) < 1e-12 && std::fabs(b.x + a.x) < 1e-9 && std::fabs(b.y + a.y) < 1e-9 && std::fabs(b.z + a.z) < 1e-9) found = true;
        if (!found) return false;
    }
    return true;
}

Set ico() {
    const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
    Set s;
    for (int a : {-1, 1})
        for (int b : {-1, 1}) {
            s.push_back({1, 0, a * 1.0, b * phi, 'n'});
            s.push_back({1, a * 1.0, b * phi, 0, 'n'});
            s.push_back({1, b * phi, 0, a * 1.0, 'n'});
        }
    return s;
}

}  // namespace

int main() {
    tb::validate_helpers();

    tb::heading("V1 known answers");
    {
        Set two{{1, 0, 0, 1, 'p'}, {1, 0, 0, -1, 'p'}};
        const M3 q = traceless(two);
        const bool ok = std::fabs(q[0][0] + 2) < 1e-14 && std::fabs(q[1][1] + 2) < 1e-14 && std::fabs(q[2][2] - 4) < 1e-14 && std::fabs(q[0][1]) < 1e-14;
        tb::check_true("V1", "traceless tensor of two unit weights at (0,0,+-1) is diag(-2,-2,4)", ok);
        Set pr = centred({{1, 0.3, 0.1, -0.2, 'p'}, {1, 1.7, -0.4, 0.9, 'n'}});
        tb::check("V1", "I_1 of an equal-weight pair about its centroid is 0", invariant(pr, 1) + 1.0, 1.0, 1e-14, true);
        tb::check_true("V1", "P_2, P_3, P_4 at cos = 1 are 1 and at cos = 0 are -1/2, 0, 3/8", std::fabs(legendre(2, 1) - 1) + std::fabs(legendre(3, 1) - 1) + std::fabs(legendre(4, 1) - 1) < 1e-14 && std::fabs(legendre(2, 0) + 0.5) < 1e-14 && std::fabs(legendre(3, 0)) < 1e-14 && std::fabs(legendre(4, 0) - 0.375) < 1e-14);
    }

    auto zero = [](double v) { return std::fabs(v) <= 1e-12; };
    auto nonzero = [](double v) { return std::fabs(v) >= 1e-6; };
    auto row = [&](const char* name, const Set& s0) {
        const Set s = centred(s0);
        std::string line;
        char buf[64];
        for (int l = 1; l <= 6; ++l) {
            std::snprintf(buf, sizeof buf, "I%d=%.3e ", l, invariant(s, l));
            line += buf;
        }
        tb::note("%-22s %s", name, line.c_str());
    };

    tb::heading("T1 multipole pattern of symmetric solids (equal weights, centred)");
    {
        const double a = 1.0 / std::sqrt(3.0);
        Set tet{{1, a, a, a, 'p'}, {1, a, -a, -a, 'p'}, {1, -a, a, -a, 'p'}, {1, -a, -a, a, 'p'}};
        Set cube;
        for (int x : {-1, 1})
            for (int y : {-1, 1})
                for (int z : {-1, 1}) cube.push_back({1, double(x), double(y), double(z), 'p'});
        Set oct{{1, 1, 0, 0, 'p'}, {1, -1, 0, 0, 'p'}, {1, 0, 1, 0, 'p'}, {1, 0, -1, 0, 'p'}, {1, 0, 0, 1, 'p'}, {1, 0, 0, -1, 'p'}};
        Set ic = ico();
        row("tetrahedron", tet);
        row("cube", cube);
        row("octahedron", oct);
        row("icosahedron", ic);
        auto I = [&](const Set& s, int l) { return invariant(centred(s), l); };
        tb::check_true("T1", "tetrahedron: I1 = I2 = 0, I3 > 0", zero(I(tet, 1)) && zero(I(tet, 2)) && nonzero(I(tet, 3)));
        tb::check_true("T1", "cube: I1 = I2 = I3 = 0, I4 > 0", zero(I(cube, 1)) && zero(I(cube, 2)) && zero(I(cube, 3)) && nonzero(I(cube, 4)));
        tb::check_true("T1", "octahedron: I1 = I2 = I3 = 0, I4 > 0", zero(I(oct, 1)) && zero(I(oct, 2)) && zero(I(oct, 3)) && nonzero(I(oct, 4)));
        tb::check_true("T1", "icosahedron: I1..I5 = 0, I6 > 0", zero(I(ic, 1)) && zero(I(ic, 2)) && zero(I(ic, 3)) && zero(I(ic, 4)) && zero(I(ic, 5)) && nonzero(I(ic, 6)));
    }

    tb::heading("T2 accidental cancellation and the module configurations");
    {
        const double s = std::sqrt(4.5);
        Set acc{{1, 0, 0, 1.5, 'p'}, {1, 0, 0, -1.5, 'p'}, {0.5, s, 0, 0, 'p'}, {0.5, -s, 0, 0, 'p'}, {0.5, 0, s, 0, 'p'}, {0.5, 0, -s, 0, 'p'}};
        const double s2 = std::sqrt(2.0);
        Set ring{{1, s2, 0, 0, 'p'}, {1, 0, s2, 0, 'n'}, {1, -s2, 0, 0, 'p'}, {1, 0, -s2, 0, 'n'}};
        Set pair{{1, 0, 0, 0, 'p'}, {1, 2, 0, 0, 'n'}};
        Set bent{{1, 0, 0, 0, 'p'}, {1, 2, 0, 0, 'n'}, {1, 0, 2, 0, 'n'}};
        row("accidental (Q = 0)", acc);
        row("alpha ring", ring);
        row("pair", pair);
        row("bent triton 90deg", bent);
        auto I = [&](const Set& st, int l) { return invariant(centred(st), l); };
        tb::check_true("T2", "accidental set: I2 = 0, I3 = 0, I4 > 0 (not cubic: h != s)", zero(I(acc, 2)) && zero(I(acc, 3)) && nonzero(I(acc, 4)) && std::fabs(1.5 - s) > 0.1);
        tb::check_true("T2", "alpha ring: I2 > 0, I3 = 0", nonzero(I(ring, 2)) && zero(I(ring, 3)));
        tb::check_true("T2", "pair: I1 = 0, I2 > 0", zero(I(pair, 1)) && nonzero(I(pair, 2)));
        tb::check_true("T2", "bent triton: I2 > 0, I3 > 0", nonzero(I(bent, 2)) && nonzero(I(bent, 3)));
    }

    tb::heading("T3 orientation average of the traceless tensor");
    {
        const double s2 = std::sqrt(2.0);
        std::vector<std::pair<const char*, Set>> sets = {
            {"alpha ring", {{1, s2, 0, 0, 'p'}, {1, 0, s2, 0, 'n'}, {1, -s2, 0, 0, 'p'}, {1, 0, -s2, 0, 'n'}}},
            {"pair", {{1, 0, 0, 0, 'p'}, {1, 2, 0, 0, 'n'}}},
            {"bent triton", {{1, 0, 0, 0, 'p'}, {1, 2, 0, 0, 'n'}, {1, 0, 2, 0, 'n'}}}};
        // Gauss-Legendre nodes (4 points) in cos(beta)
        const double gx[4] = {-0.8611363115940526, -0.3399810435848563, 0.3399810435848563, 0.8611363115940526};
        const double gw[4] = {0.3478548451374538, 0.6521451548625461, 0.6521451548625461, 0.3478548451374538};
        for (auto& [name, st0] : sets) {
            const Set st = centred(st0);
            const M3 q = traceless(st);
            double mx = 0.0;
            for (auto& r : q) for (double v : r) mx = std::fmax(mx, std::fabs(v));
            M3 avg{};
            for (int ia = 0; ia < 8; ++ia)
                for (int ig = 0; ig < 8; ++ig)
                    for (int ib = 0; ib < 4; ++ib) {
                        const double al = 2 * kPi * ia / 8, ga = 2 * kPi * ig / 8, cb = gx[ib], sb = std::sqrt(1 - cb * cb);
                        const double ca = std::cos(al), sa = std::sin(al), cg = std::cos(ga), sg = std::sin(ga);
                        // R = Rz(al) Ry(be) Rz(ga)
                        const double R[3][3] = {{ca * cb * cg - sa * sg, -ca * cb * sg - sa * cg, ca * sb}, {sa * cb * cg + ca * sg, -sa * cb * sg + ca * cg, sa * sb}, {-sb * cg, sb * sg, cb}};
                        for (int i = 0; i < 3; ++i)
                            for (int j = 0; j < 3; ++j) {
                                double t = 0.0;
                                for (int k = 0; k < 3; ++k)
                                    for (int m = 0; m < 3; ++m) t += R[i][k] * q[k][m] * R[j][m];
                                avg[i][j] += gw[ib] / 2.0 * t / 64.0;
                            }
                    }
            double am = 0.0;
            for (auto& r : avg) for (double v : r) am = std::fmax(am, std::fabs(v));
            char label[160];
            std::snprintf(label, sizeof label, "%s: largest intrinsic component %.4f ; largest orientation-averaged component %.2e (relative %.2e)", name, mx, am, am / mx);
            tb::check_true("T3", label, am / mx <= 1e-13);
        }
    }

    tb::heading("T4 inversion invariance of labelled configurations");
    {
        const double s2 = std::sqrt(2.0);
        Set ring{{1, s2, 0, 0, 'p'}, {1, 0, s2, 0, 'n'}, {1, -s2, 0, 0, 'p'}, {1, 0, -s2, 0, 'n'}};
        Set pair{{1, 0, 0, 0, 'p'}, {1, 2, 0, 0, 'n'}};
        Set bent{{1, 0, 0, 0, 'n'}, {1, 2, 0, 0, 'p'}, {1, 2.0 * std::cos(kPi / 2), 2.0 * std::sin(kPi / 2), 0, 'n'}};
        // bent triton with the proton at the vertex
        Set bent2{{1, 0, 0, 0, 'p'}, {1, 2, 0, 0, 'n'}, {1, 0, 2, 0, 'n'}};
        Set lin{{1, -2, 0, 0, 'n'}, {1, 0, 0, 0, 'p'}, {1, 2, 0, 0, 'n'}};
        Set icoshell = ico();
        for (auto& p : icoshell) { p.x *= 2.0 / 1.9021130325903071; p.y *= 2.0 / 1.9021130325903071; p.z *= 2.0 / 1.9021130325903071; }
        icoshell.push_back({1, 0, 0, 0, 'p'});
        (void)bent;
        tb::check_true("T4", "alpha ring: inversion-invariant", inversion_invariant(ring));
        tb::check_true("T4", "two-sphere pair p-n: not invariant", !inversion_invariant(pair));
        tb::check_true("T4", "bent triton n-p-n at 90 degrees: not invariant", !inversion_invariant(bent2));
        tb::check_true("T4", "linear triton n-p-n: invariant", inversion_invariant(lin));
        tb::check_true("T4", "icosahedral shell of 12 n about a p: invariant", inversion_invariant(icoshell));
    }

    return tb::finish();
}
