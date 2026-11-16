#pragma once
// sdt/sphere_frame.hpp -- the spherical frame the engine's geometry is stated in.
//
// SDT runs on Helix geometry. A place is a radius and a direction (polar angle from the pole, azimuth about it); a direction is a
// place of radius 1; a vector (a velocity, an acceleration, an impulse) is a place whose radius is its magnitude. Nothing here
// takes a direction apart into components and nothing forms one: every geometric step is one of three primitives -- haversine
// separation, bearing, offset direction -- or a triangle solved from them (`relative_locus`, `step_locus`).
//
// AUTHORITY. These are the equations of Helix's frame algebra (hsml_os/core/math/spherical_frame.hpp and
// core/spherical_coords.hpp), stated again here so the engine has no dependency on Helix. A test (GOM43 registration K1)
// compiles both and requires them to agree; if they ever differ, Helix's is right and this file is repaired.
//
// TWO DELIBERATE DIFFERENCES. (1) The angle between two directions is conditioned over the whole range (see
// `Locus::angular_distance`): Helix's haversine loses to sqrt(eps) near antipodal directions, and the engine meets them all the
// time (bodies on opposite sides of the arena centre; a velocity difference is a sum of nearly opposite vectors). Where the
// separation is below 1 rad the two are identical. (2) Helix floors a locus at a radius of 1e-12 m, because its loci are places in metres. The engine also
// sums vectors whose units are m/s, m/s^2 or kg m/s, where 1e-12 is an ordinary size. `add_scaled` and `sum` therefore call a
// result "nothing" only when it has cancelled to within rounding of the larger of its two terms, never by an absolute floor,
// and they use the cancellation-free form of the sum's magnitude. `step_locus` and `relative_locus` (places) keep Helix's floor.
//
// Conventions: theta in [0, pi] from the pole; phi in (0, 2 pi] about it (a whole turn is 2 pi, never 0); a bearing is the
// heading of a great circle, 0 toward the pole and +pi/2 toward increasing phi; angles in radians.
//
// Author: James Christopher Tyndall, Melbourne.

#include <algorithm>
#include <cmath>
#include <numbers>
#include <optional>
#include <stdexcept>

namespace sdt::sphere {

inline constexpr double kPi = std::numbers::pi;
inline constexpr double kHalfPi = kPi / 2.0;
inline constexpr double kTurn = 2.0 * kPi;

// A place: how far from the centre, and which way. Refuses the centre (a radius that is not more than nothing) and any
// non-finite value; carries a polar angle past a pole over it.
class Locus {
public:
    Locus() = delete;
    Locus(double radius, double theta, double phi) : radius_(radius), theta_(theta), phi_(phi) {
        if (!(radius_ > 0.0) || !std::isfinite(radius_)) throw std::domain_error("a locus has a radius: more than nothing, and finite");
        if (!std::isfinite(theta_) || !std::isfinite(phi_)) throw std::domain_error("a locus has a direction: finite angles");
        theta_ = std::fmod(theta_, kTurn);
        if (theta_ < 0.0) theta_ += kTurn;
        if (theta_ > kPi) { theta_ = kTurn - theta_; phi_ += kPi; }
        phi_ = std::fmod(phi_, kTurn);
        if (phi_ <= 0.0) phi_ += kTurn;
    }
    [[nodiscard]] double radius() const noexcept { return radius_; }
    [[nodiscard]] double theta() const noexcept { return theta_; }
    [[nodiscard]] double phi() const noexcept { return phi_; }

    // The angle between the two directions, conditioned over the whole range. Haversine is exact for the smallest separations but
    // loses to sqrt(eps) near antipodal directions (asin near 1); the five-part form atan2(sqrt(sine_rule^2 + five_part^2),
    // cos_polar) is exact there. The haversine value is kept below 1 rad, the five-part form from there up.
    [[nodiscard]] double angular_distance(const Locus& other) const noexcept {
        const double dt = std::sin((other.theta_ - theta_) * 0.5);
        const double dp = std::sin((other.phi_ - phi_) * 0.5);
        const double h = dt * dt + std::sin(theta_) * std::sin(other.theta_) * dp * dp;
        const double hav = 2.0 * std::asin(std::sqrt(std::clamp(h, 0.0, 1.0)));
        if (hav < 1.0) return hav;
        const double dphi = other.phi_ - phi_;
        const double sine_rule = std::sin(dphi) * std::sin(other.theta_);
        const double five_part = std::sin(theta_) * std::cos(other.theta_) - std::cos(theta_) * std::sin(other.theta_) * std::cos(dphi);
        const double cos_polar = std::cos(theta_) * std::cos(other.theta_) + std::sin(theta_) * std::sin(other.theta_) * std::cos(dphi);
        return std::atan2(std::sqrt(sine_rule * sine_rule + five_part * five_part), cos_polar);
    }
    // The distance between the two places: the chord of the triangle they make with the centre, from the difference of the radii
    // and the half-angle (no term cancels another).
    [[nodiscard]] double distance_to(const Locus& other) const noexcept {
        const double dr = other.radius_ - radius_;
        const double half = std::sin(angular_distance(other) * 0.5);
        return std::sqrt(dr * dr + 4.0 * radius_ * other.radius_ * half * half);
    }

private:
    double radius_;
    double theta_;
    double phi_;
};

using Direction = Locus;                 // a locus of radius 1
using Vector = std::optional<Locus>;      // radius = magnitude; absent = nothing (the zero vector)

[[nodiscard]] inline Direction direction(double theta, double phi) { return Locus{1.0, theta, phi}; }
[[nodiscard]] inline Direction unit(const Locus& d) { return Locus{1.0, d.theta(), d.phi()}; }

[[nodiscard]] inline double separation(const Locus& a, const Locus& b) noexcept { return a.angular_distance(b); }

// Bearing of `to` from `from`: the angle at `from` in the triangle (pole, from, to).
[[nodiscard]] inline double bearing(const Locus& from, const Locus& to) noexcept {
    const double dphi = to.phi() - from.phi();
    const double sine_rule = std::sin(dphi) * std::sin(to.theta());
    const double five_part = std::sin(from.theta()) * std::cos(to.theta())
                           - std::cos(from.theta()) * std::sin(to.theta()) * std::cos(dphi);
    return std::atan2(sine_rule, five_part);
}

// The direction reached from `axis` by going `polar` along `brg`.
[[nodiscard]] inline Direction offset_direction(const Locus& axis, double polar, double brg) noexcept {
    const double ct = std::cos(axis.theta()), st = std::sin(axis.theta());
    const double cp = std::cos(polar), sp = std::sin(polar);
    const double cos_polar = ct * cp + st * sp * std::cos(brg);
    const double sine_rule = sp * std::sin(brg), five_part = cp * st - ct * sp * std::cos(brg);
    const double theta2 = std::atan2(std::sqrt(sine_rule * sine_rule + five_part * five_part), cos_polar);
    const double dphi = std::atan2(sine_rule, five_part);
    return Locus{1.0, theta2, axis.phi() + dphi};
}

// The antipode: the direction reversed.
[[nodiscard]] inline Direction antipode(const Locus& d) noexcept { return Locus{1.0, kPi - d.theta(), d.phi() + kPi}; }

// Two places in one frame -> how far apart, and which way the target lies from the observer. Absent when they are one place.
struct Relative {
    double distance;       // same unit as the radii
    Direction direction;   // observer -> target
};

[[nodiscard]] inline std::optional<Relative> relative_locus(const Locus& observer, const Locus& target) noexcept {
    const double ro = observer.radius(), rt = target.radius();
    const double dsigma = separation(observer, target);
    const double hav = std::sin(dsigma * 0.5);
    const double h2 = hav * hav;
    const double dr = rt - ro;
    const double chord = std::sqrt(dr * dr + 4.0 * ro * rt * h2);
    if (chord <= 1e-12) return std::nullopt;
    const double along = dr - 2.0 * rt * h2;
    const double chi = std::atan2(rt * std::sin(dsigma), along);
    const double brg = bearing(observer, target);
    return Relative{chord, offset_direction(observer, chi, brg)};
}

// Advance a place along a direction by `distance`: the forward partner of relative_locus.
[[nodiscard]] inline Locus step_locus(const Locus& from, const Locus& along, double distance) noexcept {
    const double ro = from.radius();
    const double psi = separation(from, along);
    const double r = std::sqrt(ro * ro + distance * distance + 2.0 * ro * distance * std::cos(psi));
    if (r <= 1e-12) return Locus{0.5e-12, along.theta(), along.phi()};
    const double chi = std::atan2(distance * std::sin(psi), ro + distance * std::cos(psi));
    const Locus d = offset_direction(from, chi, bearing(from, along));
    return Locus{r, d.theta(), d.phi()};
}

// ---- vectors: a locus whose radius is a magnitude --------------------------------------------------------------------------

[[nodiscard]] inline double magnitude(const Vector& v) noexcept { return v ? v->radius() : 0.0; }

// `v` plus `amount` along `along`. A sum that has cancelled to within rounding of its larger term is nothing (absent).
[[nodiscard]] inline Vector add_scaled(const Vector& v, const Locus& along, double amount) {
    if (!(amount > 0.0)) return v;
    if (!v) return Locus{amount, along.theta(), along.phi()};
    const double ro = v->radius();
    const double psi = separation(*v, along);
    const double half_cos = std::cos(psi * 0.5);
    const double gap = ro - amount;
    const double r2 = gap * gap + 4.0 * ro * amount * half_cos * half_cos;            // = ro^2 + amount^2 + 2 ro amount cos(psi), no cancellation
    const double r = std::sqrt(r2);
    if (r <= 1e-15 * std::max(ro, amount)) return std::nullopt;
    const double chi = std::atan2(amount * std::sin(psi), ro + amount * std::cos(psi));
    const Direction d = offset_direction(*v, chi, bearing(*v, unit(along)));
    return Locus{r, d.theta(), d.phi()};
}

// a + b
[[nodiscard]] inline Vector sum(const Vector& a, const Vector& b) {
    if (!b) return a;
    if (!a) return b;
    return add_scaled(a, unit(*b), b->radius());
}

// The same direction at `factor` times the magnitude; a factor that is not above 0 leaves nothing.
[[nodiscard]] inline Vector scaled(const Vector& v, double factor) {
    if (!v || !(factor > 0.0)) return std::nullopt;
    return Locus{v->radius() * factor, v->theta(), v->phi()};
}

// The vector reversed.
[[nodiscard]] inline Vector negated(const Vector& v) {
    if (!v) return std::nullopt;
    return Locus{v->radius(), kPi - v->theta(), v->phi() + kPi};
}

// a - b, from the separation of the two vectors themselves (near 0 when they nearly agree, where haversine is exact), never from
// adding an antipode: |a - b|^2 = (|a| - |b|)^2 + 4 |a| |b| sin^2(psi / 2).
[[nodiscard]] inline Vector difference(const Vector& a, const Vector& b) {
    if (!b) return a;
    if (!a) return negated(b);
    const double ra = a->radius(), rb = b->radius();
    const double psi = separation(*a, *b);
    const double half_sin = std::sin(psi * 0.5);
    const double gap = ra - rb;
    const double r = std::sqrt(gap * gap + 4.0 * ra * rb * half_sin * half_sin);
    if (r <= 1e-15 * std::max(ra, rb)) return std::nullopt;
    if (psi == 0.0) return gap > 0.0 ? Vector{Locus{r, a->theta(), a->phi()}} : negated(Vector{Locus{r, a->theta(), a->phi()}});
    const double chi = std::atan2(rb * std::sin(psi), ra - rb * std::cos(psi));
    const Direction away = antipode(unit(*b));
    const Direction d = offset_direction(*a, chi, bearing(*a, away));
    return Locus{r, d.theta(), d.phi()};
}

// The direction of a vector (nothing for the zero vector).
[[nodiscard]] inline std::optional<Direction> heading(const Vector& v) {
    if (!v) return std::nullopt;
    return unit(*v);
}

// The point a fraction `fraction` of the way along the straight line from `a` to `b`.
[[nodiscard]] inline Locus along_line(const Locus& a, const Locus& b, double fraction) {
    const auto rel = relative_locus(a, b);
    if (!rel) return a;
    return step_locus(a, rel->direction, rel->distance * fraction);
}

}  // namespace sdt::sphere
