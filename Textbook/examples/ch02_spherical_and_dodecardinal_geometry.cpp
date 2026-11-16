// Chapter 2 — spherical and dodecardinal geometry: worked-example instruments.
// Pre-registration: Textbook/validation/ch02_PRE_REGISTRATION.md (registered before this file existed).
// Build and run: powershell -File Textbook\tools\tb_run.ps1 -Stem ch02_spherical_and_dodecardinal_geometry
//
// The engine under test (sdt/sphere_frame.hpp) takes no directions apart into components. The reference routes in this
// instrument do, and are labelled as such.
#include <sdt/laws.hpp>
#include <sdt/sphere_frame.hpp>

#include "tb_common.hpp"

#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

namespace {

namespace S = sdt::sphere;
using V3 = std::array<double, 3>;
constexpr double kPi = std::numbers::pi;
constexpr double kPiHi = 3.141592653589793116;   // pi = kPiHi + kPiLo (two-part)
constexpr double kPiLo = 1.224646799147353207e-16;
constexpr double kU = 1.11e-16;                  // half the unit roundoff

V3 vec(double th, double ph) { return {std::sin(th) * std::cos(ph), std::sin(th) * std::sin(ph), std::cos(th)}; }
double dot(const V3& a, const V3& b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
V3 cross(const V3& a, const V3& b) {
    return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]};
}
double norm(const V3& a) { return std::sqrt(dot(a, a)); }
V3 unit3(const V3& a) {
    const double m = norm(a);
    return {a[0] / m, a[1] / m, a[2] / m};
}

struct DD {
    double hi, lo;
};
DD two_sum(double a, double b) {
    const double s = a + b, bb = s - a;
    return {s, (a - (s - bb)) + (b - bb)};
}

// Van Oosterom-Strackee solid angle of the triangle with unit vertex vectors a, b, c (Cartesian reference route).
double vos(const V3& a, const V3& b, const V3& c) {
    const double triple = std::fabs(dot(a, cross(b, c)));
    return 2.0 * std::atan2(triple, 1.0 + dot(a, b) + dot(b, c) + dot(c, a));
}

double fold_angle(double x) {
    x = std::fabs(x);
    x = std::fmod(x, 2.0 * kPi);
    return x > kPi ? 2.0 * kPi - x : x;
}

// Interior angle of a spherical triangle at P between the directions to Q and R, from the engine's bearings.
double angle_at(const S::Locus& P, const S::Locus& Q, const S::Locus& R) {
    return fold_angle(S::bearing(P, Q) - S::bearing(P, R));
}

double excess_by_angles(const S::Locus& A, const S::Locus& B, const S::Locus& C) {
    return angle_at(A, B, C) + angle_at(B, C, A) + angle_at(C, A, B) - kPi;
}

double lhuilier(double a, double b, double c) {
    const double s = 0.5 * (a + b + c);
    return 4.0 * std::atan(std::sqrt(std::tan(0.5 * s) * std::tan(0.5 * (s - a)) * std::tan(0.5 * (s - b)) *
                                     std::tan(0.5 * (s - c))));
}

struct Rng {
    std::uint64_t s;
    double next() {
        s = s * 6364136223846793005ULL + 1442695040888963407ULL;
        return static_cast<double>(s >> 11) * (1.0 / 9007199254740992.0);
    }
};

S::Locus random_direction(Rng& g, double radius = 1.0) {
    const double th = std::acos(1.0 - 2.0 * g.next());
    const double ph = 2.0 * kPi * g.next() + 1e-9;
    return S::Locus{radius, th, ph};
}

bool throws_domain(double r, double th, double ph) {
    try {
        S::Locus L(r, th, ph);
        (void)L;
    } catch (const std::domain_error&) {
        return true;
    }
    return false;
}

}  // namespace

int main() {
    namespace L = sdt::laws;
    tb::validate_helpers();

    // ---------------------------------------------------------------------------------------------------------
    tb::heading("V1 octant triangle (known angles and area)");
    {
        const S::Locus A(1.0, 0.0, 1.0), B(1.0, kPi / 2, 0.0), C(1.0, kPi / 2, kPi / 2);
        tb::check("V1", "side BC = pi/2", S::separation(B, C), kPi / 2, 1e-14);
        tb::check("V1", "side AC = pi/2", S::separation(A, C), kPi / 2, 1e-14);
        tb::check("V1", "side AB = pi/2", S::separation(A, B), kPi / 2, 1e-14);
        tb::check("V1", "angle at A = pi/2 (engine bearings)", angle_at(A, B, C), kPi / 2, 1e-14);
        tb::check("V1", "angle at B = pi/2", angle_at(B, C, A), kPi / 2, 1e-14);
        tb::check("V1", "angle at C = pi/2", angle_at(C, A, B), kPi / 2, 1e-14);
        tb::check("V1", "area (spherical excess) = pi/2 sr", excess_by_angles(A, B, C), kPi / 2, 1e-14);
    }
    tb::heading("V2 Locus normalisation and domain");
    {
        const S::Locus a(1.0, kPi + 0.3, 0.5);
        tb::check("V2", "theta beyond pi is carried over the pole: theta = pi - 0.3", a.theta(), kPi - 0.3, 1e-15, false);
        tb::check("V2", "...and azimuth turned by pi: phi = 0.5 + pi", a.phi(), 0.5 + kPi, 1e-15, false);
        tb::check("V2", "phi = 0 is written as a whole turn 2 pi", S::Locus(1.0, 1.0, 0.0).phi(), 2.0 * kPi, 1e-15, false);
        tb::check("V2", "phi = -1 is written 2 pi - 1", S::Locus(1.0, 1.0, -1.0).phi(), 2.0 * kPi - 1.0, 1e-15, false);
        tb::check_true("V2", "radius 0 refused", throws_domain(0.0, 1.0, 1.0));
        tb::check_true("V2", "radius -1 refused", throws_domain(-1.0, 1.0, 1.0));
        tb::check_true("V2", "radius NaN refused", throws_domain(std::numeric_limits<double>::quiet_NaN(), 1.0, 1.0));
        tb::check_true("V2", "radius infinity refused", throws_domain(std::numeric_limits<double>::infinity(), 1.0, 1.0));
        tb::check_true("V2", "theta NaN refused", throws_domain(1.0, std::numeric_limits<double>::quiet_NaN(), 1.0));
    }
    tb::heading("V3 Van Oosterom-Strackee and the pole triangle");
    {
        tb::check("V3", "octant solid angle (Cartesian route) = pi/2", vos({0, 0, 1}, {1, 0, 0}, {0, 1, 0}), kPi / 2, 1e-14);
        const double lam = 2.0 * kPi / 3.0;
        tb::check("V3", "pole + equator 0 + equator 2pi/3 solid angle = 2pi/3",
                  vos({0, 0, 1}, {1, 0, 0}, {std::cos(lam), std::sin(lam), 0}), lam, 1e-14);
        const S::Locus P(1.0, 0.0, 1.0), E0(1.0, kPi / 2, 0.5), E1(1.0, kPi / 2, 0.5 + lam);
        tb::check("V3", "same triangle by the engine's bearings (excess)", excess_by_angles(P, E0, E1), lam, 1e-13);
    }

    // ---------------------------------------------------------------------------------------------------------
    tb::heading("T1 small separations (pairs on one meridian)");
    {
        for (double d : {1e-2, 1e-4, 1e-6, 1e-8, 1e-10}) {
            const double thA = 1.0, thB = 1.0 + d;
            const double dtrue = thB - thA;  // exact (Sterbenz)
            const S::Locus A(1.0, thA, 1.0), B(1.0, thB, 1.0);
            const double eng = A.angular_distance(B);
            const double naive = std::acos(std::cos(thA) * std::cos(thB) + std::sin(thA) * std::sin(thB) * 1.0);
            const double sh = std::sin(0.5 * (thB - thA));
            const double hav = 2.0 * std::asin(std::sqrt(sh * sh));
            const double e_eng = std::fabs(eng - dtrue) / dtrue, e_naive = std::fabs(naive - dtrue) / dtrue,
                         e_hav = std::fabs(hav - dtrue) / dtrue;
            tb::check("T1", ("engine angular_distance, delta = " + std::to_string(d)).c_str(), eng, dtrue, 1e-14);
            tb::note("delta=%.0e  relative error: engine %.2e  haversine %.2e  naive arccos %.2e", d, e_eng, e_hav,
                     e_naive);
            if (d == 1e-8) tb::check_true("T1", "naive arccos relative error > 0.1 at delta = 1e-8", e_naive > 0.1);
        }
    }

    tb::heading("T2 near-antipodal separations (opposite meridian half-planes)");
    {
        for (double e : {1e-2, 1e-4, 1e-6, 1e-8, 1e-10}) {
            const double thA = 0.7, thB = (kPiHi - 0.7) - e;
            const double phA = 1.0, phB = 1.0 + kPiHi;
            const DD s = two_sum(thA, thB);
            const double e_true = (kPiHi - s.hi) + (kPiLo - s.lo);  // pi - (thA + thB), error-free sum
            const S::Locus A(1.0, thA, phA), B(1.0, thB, phB);
            const double eng = A.angular_distance(B);
            const double dphi = B.phi() - A.phi();
            const double naive = std::acos(std::cos(thA) * std::cos(thB) + std::sin(thA) * std::sin(thB) * std::cos(dphi));
            const double dt = std::sin(0.5 * (thB - thA)), dp = std::sin(0.5 * dphi);
            const double hav = 2.0 * std::asin(std::sqrt(dt * dt + std::sin(thA) * std::sin(thB) * dp * dp));
            auto eps_of = [&](double psi) { return (kPiHi - psi) + kPiLo; };
            const double r_eng = std::fabs(eps_of(eng) - e_true) / e_true;
            const double r_naive = std::fabs(eps_of(naive) - e_true) / e_true;
            const double r_hav = std::fabs(eps_of(hav) - e_true) / e_true;
            tb::check_true("T2", ("engine error <= 50 u / epsilon, epsilon = " + std::to_string(e)).c_str(),
                           r_eng <= 50.0 * kU / e_true);
            tb::note("eps=%.0e  relative error in eps: engine %.2e (budget %.2e)  haversine %.2e  naive arccos %.2e", e,
                     r_eng, 50.0 * kU / e_true, r_hav, r_naive);
            if (e == 1e-8) {
                tb::check_true("T2", "haversine relative error > 0.1 at epsilon = 1e-8", r_hav > 0.1);
                tb::check_true("T2", "naive arccos relative error > 0.1 at epsilon = 1e-8", r_naive > 0.1);
            }
        }
    }

    tb::heading("T3 chord conditioning (equal radii, nearly equal directions)");
    {
        const double r = 6.371e6, d = 1e-9;
        const double thA = 1.0, thB = 1.0 + d;
        const double dtrue = thB - thA;
        const S::Locus A(r, thA, 1.0), B(r, thB, 1.0);
        const double chord_true = 2.0 * r * std::sin(0.5 * dtrue);
        const double eng = A.distance_to(B);
        const double psi_naive = A.angular_distance(B);
        const double naive = std::sqrt(r * r + r * r - 2.0 * r * r * std::cos(psi_naive));
        tb::check("T3", "distance_to vs 2 r sin(delta/2)", eng, chord_true, 1e-13);
        tb::check_true("T3", "naive law-of-cosines chord relative error > 0.1",
                       std::fabs(naive - chord_true) / chord_true > 0.1);
        tb::note("r = %.3e m, delta = 1e-9 rad: chord = %.9e m; engine %.9e; naive %.9e", r, chord_true, eng, naive);
    }

    tb::heading("T4 spherical triangle: three routes to the area");
    {
        Rng g{20261103};
        int accepted = 0, tried = 0;
        double worst1 = 0.0, worst2 = 0.0;
        while (accepted < 40 && tried < 100000) {
            ++tried;
            const S::Locus A = random_direction(g), B = random_direction(g), C = random_direction(g);
            const double a = S::separation(B, C), b = S::separation(A, C), c = S::separation(A, B);
            const double area = vos(vec(A.theta(), A.phi()), vec(B.theta(), B.phi()), vec(C.theta(), C.phi()));
            if (area < 0.05 || std::fmax(a, std::fmax(b, c)) > 3.0) continue;
            ++accepted;
            worst1 = std::fmax(worst1, std::fabs(excess_by_angles(A, B, C) - area));
            worst2 = std::fmax(worst2, std::fabs(lhuilier(a, b, c) - area));
        }
        tb::check_true("T4", "40 triangles accepted", accepted == 40);
        tb::check("T4", "excess from engine bearings vs Van Oosterom-Strackee (worst of 40)", worst1, 0.0, 1e-10, false);
        tb::check("T4", "L'Huilier from engine sides vs Van Oosterom-Strackee (worst of 40)", worst2, 0.0, 1e-10, false);
        tb::note("%d candidate triples drawn", tried);
    }

    tb::heading("T5 relative_locus / step_locus round trip");
    {
        Rng g{777};
        double worst = 0.0;
        int n = 0;
        while (n < 200) {
            const S::Locus A = random_direction(g, 0.5 + 1.5 * g.next());
            const S::Locus B = random_direction(g, 0.5 + 1.5 * g.next());
            const auto rel = S::relative_locus(A, B);
            if (!rel || rel->distance < 1e-3) continue;
            const S::Locus Cc = S::step_locus(A, rel->direction, rel->distance);
            worst = std::fmax(worst, Cc.distance_to(B));
            ++n;
        }
        tb::check("T5", "distance from the recovered locus to the target (worst of 200)", worst, 0.0, 1e-10, false);
    }

    tb::heading("T6 dodecardinal set: the 12 icosahedron directions");
    {
        const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
        std::vector<V3> v;
        for (int s1 : {-1, 1})
            for (int s2 : {-1, 1}) {
                v.push_back({0, double(s1), s2 * phi});
                v.push_back({double(s1), s2 * phi, 0});
                v.push_back({s2 * phi, 0, double(s1)});
            }
        std::vector<S::Locus> loci;
        for (const V3& p : v) {
            const V3 u = unit3(p);
            loci.emplace_back(1.0, std::acos(u[2]), std::atan2(u[1], u[0]));
        }
        const double a63 = std::acos(1.0 / std::sqrt(5.0)), a117 = kPi - a63;
        bool ok = loci.size() == 12;
        double worst = 0.0, minsep = 1e9;
        for (std::size_t i = 0; i < loci.size(); ++i) {
            int c63 = 0, c117 = 0, c180 = 0, other = 0;
            for (std::size_t j = 0; j < loci.size(); ++j) {
                if (i == j) continue;
                const double a = loci[i].angular_distance(loci[j]);
                minsep = std::fmin(minsep, a);
                if (std::fabs(a - a63) < 1e-9) { ++c63; worst = std::fmax(worst, std::fabs(a - a63)); }
                else if (std::fabs(a - a117) < 1e-9) { ++c117; worst = std::fmax(worst, std::fabs(a - a117)); }
                else if (std::fabs(a - kPi) < 1e-7) { ++c180; worst = std::fmax(worst, std::fabs(a - kPi)); }
                else ++other;
            }
            ok = ok && c63 == 5 && c117 == 5 && c180 == 1 && other == 0;
        }
        tb::check_true("T6", "each vertex: 5 at 63.43 deg, 5 at 116.57 deg, 1 at 180 deg, none other", ok);
        tb::check("T6", "neighbour angle arccos(1/sqrt5), worst deviation over all pairs", worst, 0.0, 1e-7, false);
        // face centre
        const V3 f = unit3({(v[0][0] + v[1][0] + v[2][0]), 0, 0});  // placeholder replaced below
        (void)f;
        const V3 p1{0, 1, phi}, p2{0, -1, phi}, p3{phi, 0, 1};
        const V3 cen = unit3({p1[0] + p2[0] + p3[0], p1[1] + p2[1] + p3[1], p1[2] + p2[2] + p3[2]});
        const S::Locus Fc(1.0, std::acos(cen[2]), std::atan2(cen[1], cen[0]));
        const double expect = std::acos(std::sqrt((5.0 + 2.0 * std::sqrt(5.0)) / 15.0));
        for (const V3* p : {&p1, &p2, &p3}) {
            const V3 u = unit3(*p);
            const S::Locus Vx(1.0, std::acos(u[2]), std::atan2(u[1], u[0]));
            tb::check("T6", "face-centre to vertex angle = arccos(sqrt((5+2 sqrt5)/15)) = 37.3774 deg",
                      Fc.angular_distance(Vx), expect, 1e-12);
        }
        const double cap = L::law_III::solid_angle_cap(1.0, 2.0);  // sin(eta) = 1/2, eta = 30 deg
        tb::check_true("T6", "minimum separation exceeds 2 x 30 deg: caps do not overlap", minsep > 2.0 * kPi / 6.0);
        tb::check("T6", "coverage of twelve 30-degree caps = 6(1 - sqrt3/2)", 12.0 * cap / (4.0 * kPi),
                  6.0 * (1.0 - std::sqrt(3.0) / 2.0), 1e-13);
        tb::note("minimum separation %.6f deg; cap half-angle 30 deg; coverage %.6f; open fraction %.6f",
                 minsep * 180.0 / kPi, 12.0 * cap / (4.0 * kPi), 1.0 - 12.0 * cap / (4.0 * kPi));
    }

    tb::heading("T7 engine seat geometry (APS14 polar dyad and six-ring)");
    {
        namespace D = sdt::laws::atomic::dodecardinal;
        std::array<D::Seat, 10> seats{};
        const int n = D::make_seats(10, seats);
        tb::check_true("T7", "make_seats(10) returns 10 seats", n == 10);
        std::vector<V3> dirs;
        for (int i = 0; i < n; ++i) {
            const V3 d{seats[i].direction[0], seats[i].direction[1], seats[i].direction[2]};
            bool seen = false;
            for (const V3& q : dirs) seen = seen || dot(q, d) > 1.0 - 1e-12;
            if (!seen) dirs.push_back(d);
        }
        int c60 = 0, c90 = 0, c120 = 0, c180 = 0, other = 0;
        for (std::size_t i = 0; i < dirs.size(); ++i)
            for (std::size_t j = i + 1; j < dirs.size(); ++j) {
                const double c = dot(dirs[i], dirs[j]);
                if (std::fabs(c - 0.5) < 1e-12) ++c60;
                else if (std::fabs(c) < 1e-12) ++c90;
                else if (std::fabs(c + 0.5) < 1e-12) ++c120;
                else if (std::fabs(c + 1.0) < 1e-12) ++c180;
                else ++other;
            }
        tb::check_true("T7", "8 distinct directions (2 poles + 6 ring seats)", dirs.size() == 8);
        tb::check_true("T7", "pair angles: 60 deg x6, 90 deg x12, 120 deg x6, 180 deg x4, none other",
                       c60 == 6 && c90 == 12 && c120 == 6 && c180 == 4 && other == 0);
        tb::note("counts: 60:%d 90:%d 120:%d 180:%d other:%d", c60, c90, c120, c180, other);
    }

    tb::heading("T8 the source's dodecardinal set: 1+12 cuboctahedral directions");
    {
        std::vector<V3> v;
        for (int a : {-1, 1})
            for (int b : {-1, 1}) {
                v.push_back({double(a), double(b), 0});
                v.push_back({double(a), 0, double(b)});
                v.push_back({0, double(a), double(b)});
            }
        std::vector<S::Locus> loci;
        for (const V3& p : v) {
            const V3 u = unit3(p);
            loci.emplace_back(1.0, std::acos(u[2]), std::atan2(u[1], u[0]));
        }
        bool ok = loci.size() == 12;
        double minsep = 1e9, worst = 0.0;
        const double a60 = kPi / 3, a90 = kPi / 2, a120 = 2 * kPi / 3;
        for (std::size_t i = 0; i < loci.size(); ++i) {
            int c60 = 0, c90 = 0, c120 = 0, c180 = 0, other = 0;
            for (std::size_t j = 0; j < loci.size(); ++j) {
                if (i == j) continue;
                const double a = loci[i].angular_distance(loci[j]);
                minsep = std::fmin(minsep, a);
                if (std::fabs(a - a60) < 1e-9) { ++c60; worst = std::fmax(worst, std::fabs(a - a60)); }
                else if (std::fabs(a - a90) < 1e-9) { ++c90; worst = std::fmax(worst, std::fabs(a - a90)); }
                else if (std::fabs(a - a120) < 1e-9) { ++c120; worst = std::fmax(worst, std::fabs(a - a120)); }
                else if (std::fabs(a - kPi) < 1e-7) { ++c180; worst = std::fmax(worst, std::fabs(a - kPi)); }
                else ++other;
            }
            ok = ok && c60 == 4 && c90 == 2 && c120 == 4 && c180 == 1 && other == 0;
        }
        tb::check_true("T8", "each direction: 4 at 60 deg, 2 at 90 deg, 4 at 120 deg, 1 at 180 deg, none other", ok);
        tb::check("T8", "pair angles, worst deviation from 60/90/120 deg over all pairs", worst, 0.0, 1e-12, false);
        tb::check("T8", "minimum separation = 60 deg: 30-degree caps tangent", minsep, kPi / 3, 1e-12);
        const double cap = L::law_III::solid_angle_cap(1.0, 2.0);
        tb::check("T8", "coverage of twelve 30-degree caps = 6(1 - sqrt3/2)", 12.0 * cap / (4.0 * kPi),
                  6.0 * (1.0 - std::sqrt(3.0) / 2.0), 1e-13);
        // hole centres: octahedron-face directions (+-1,+-1,+-1)/sqrt3 and the axes
        int tri = 0, sq = 0;
        double tri_worst = 0.0, sq_worst = 0.0;
        auto holes = [&](const V3& c, double want, int expect_count, int& counter, double& worstdev) {
            const V3 u = unit3(c);
            const S::Locus H(1.0, std::acos(u[2]), std::atan2(u[1], u[0]));
            int near = 0;
            for (const S::Locus& q : loci) {
                const double a = H.angular_distance(q);
                if (std::fabs(a - want) < 1e-9) { ++near; worstdev = std::fmax(worstdev, std::fabs(a - want)); }
            }
            if (near == expect_count) ++counter;
        };
        for (int a : {-1, 1})
            for (int b : {-1, 1})
                for (int c : {-1, 1}) holes({double(a), double(b), double(c)}, std::acos(2.0 / std::sqrt(6.0)), 3, tri, tri_worst);
        for (int s : {-1, 1}) {
            holes({double(s), 0, 0}, kPi / 4, 4, sq, sq_worst);
            holes({0, double(s), 0}, kPi / 4, 4, sq, sq_worst);
            holes({0, 0, double(s)}, kPi / 4, 4, sq, sq_worst);
        }
        tb::check_true("T8", "8 triangular holes, each 35.2644 deg from exactly three vertices", tri == 8);
        tb::check_true("T8", "6 square holes, each 45 deg from exactly four vertices", sq == 6);
        tb::check("T8", "hole-to-vertex angles, worst deviation (triangular, square)", std::fmax(tri_worst, sq_worst), 0.0,
                  1e-12, false);
        tb::note("open margins beyond the 30-degree caps: triangular holes %.4f deg, square holes %.4f deg",
                 (std::acos(2.0 / std::sqrt(6.0)) - kPi / 6) * 180.0 / kPi, (kPi / 4 - kPi / 6) * 180.0 / kPi);
    }

    return tb::finish();
}
