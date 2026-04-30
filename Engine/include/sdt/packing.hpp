#pragma once

/**
 * @file packing.hpp
 * @brief SDT Spherical Packing Engine — Geometry & Analysis
 *
 * Pure C++20 header-only library implementing the complete spherical
 * packing data model from the Spherical Packing Workbench.
 *
 * All sphere positions stored as (r, θ, φ):
 *   θ = polar angle from +Y (up)  [0, π]
 *   φ = azimuthal angle in XZ plane  [-π, π]
 *   Conversion to Cartesian happens ONLY at the analysis boundary.
 *
 * Preset geometries map to nuclear configurations:
 *   Tetrahedron  (n=4)  → He-4 alpha core scaffold
 *   Octahedron   (n=6)  → O-16 deuteron shell
 *   Cube         (n=8)  → Ca-40 shell arrangement
 *   Cuboctahedron(n=12) → Fe-56 alpha cluster (Vector Equilibrium)
 *   Cuboct+plugs        → Full Fe-56 with interstitial neutrons
 *
 * Zero dependencies beyond C++20 standard library.
 * No open-source code used — everything hand-written.
 *
 * @author SDT Canonical Engine — James Tyndall, Melbourne, Australia
 * @date April 2026
 */

#include <cmath>
#include <cstdio>
#include <numbers>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <cstring>

namespace sdt::packing {

// ═══════════════════════════════════════════════════════════════════════
//  CONSTANTS
// ═══════════════════════════════════════════════════════════════════════

inline constexpr double TAU = 2.0 * std::numbers::pi;
inline constexpr double PHI_GOLD = (1.0 + std::numbers::sqrt2 * std::numbers::sqrt2
    - std::numbers::sqrt2 * std::numbers::sqrt2
    + 2.2360679774997896964091736687747631) / 2.0;
// Golden ratio: (1 + √5) / 2 — computed precisely
// √5 = 2.2360679774997896964091736687747631
inline constexpr double GOLDEN_RATIO = (1.0 + 2.2360679774997896964091736687747631) / 2.0;
inline constexpr double DEG_PER_RAD = 180.0 / std::numbers::pi;
inline constexpr double RAD_PER_DEG = std::numbers::pi / 180.0;

// ═══════════════════════════════════════════════════════════════════════
//  CORE TYPES
// ═══════════════════════════════════════════════════════════════════════

/// Minimal 3D vector — no external dependencies
struct Vec3 {
    double x = 0.0, y = 0.0, z = 0.0;

    constexpr Vec3() = default;
    constexpr Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    [[nodiscard]] constexpr auto operator+(const Vec3& o) const -> Vec3 {
        return {x + o.x, y + o.y, z + o.z};
    }
    [[nodiscard]] constexpr auto operator-(const Vec3& o) const -> Vec3 {
        return {x - o.x, y - o.y, z - o.z};
    }
    [[nodiscard]] constexpr auto operator*(double s) const -> Vec3 {
        return {x * s, y * s, z * s};
    }
    [[nodiscard]] constexpr auto dot(const Vec3& o) const -> double {
        return x * o.x + y * o.y + z * o.z;
    }
    [[nodiscard]] auto length() const -> double {
        return std::sqrt(x * x + y * y + z * z);
    }
    [[nodiscard]] auto length_sq() const -> double {
        return x * x + y * y + z * z;
    }
    [[nodiscard]] auto normalized() const -> Vec3 {
        double len = length();
        if (len < 1e-15) return {0, 0, 0};
        return {x / len, y / len, z / len};
    }
    [[nodiscard]] auto distance_to(const Vec3& o) const -> double {
        return (*this - o).length();
    }
};

/// Spherical coordinate triplet
struct SphericalCoord {
    double r     = 0.0;    ///< radial distance from origin
    double theta = 0.0;    ///< polar angle from +Y [0, π]
    double phi   = 0.0;    ///< azimuthal angle in XZ plane

    /// Degrees accessors
    [[nodiscard]] auto theta_deg() const -> double { return theta * DEG_PER_RAD; }
    [[nodiscard]] auto phi_deg() const -> double { return phi * DEG_PER_RAD; }
};

/// A single sphere in the packing
struct PackingSphere {
    int            id     = 0;
    SphericalCoord pos    = {};
    double         radius = 1.0;
    int            shell  = 0;      ///< shell index (0 = primary, 1 = oct plug, 2 = tet plug)
    bool           hidden = false;
};

/// Complete packing configuration
struct PackingConfig {
    std::string            name;
    std::string            nuclear_name;    ///< nuclear identity alias (e.g. "Fe-56 core")
    double                 central_radius = 1.0;
    std::vector<PackingSphere> outers;
};

/// Analysis result for a pair of spheres
struct SpherePair {
    int    id_a   = -1;
    int    id_b   = -1;
    double angle  = 0.0;    ///< great-circle angle (radians)
    double gap    = 0.0;    ///< surface-to-surface gap
};

// ═══════════════════════════════════════════════════════════════════════
//  COORDINATE CONVERSION
// ═══════════════════════════════════════════════════════════════════════

/// Convert spherical (r, θ, φ) to Cartesian.
/// Convention: θ = polar from +Y, φ = azimuth in XZ.
[[nodiscard]] inline auto sph2vec(double r, double theta, double phi) -> Vec3 {
    double s = std::sin(theta);
    return {
        r * s * std::cos(phi),
        r * std::cos(theta),
        r * s * std::sin(phi)
    };
}

[[nodiscard]] inline auto sph2vec(const SphericalCoord& c) -> Vec3 {
    return sph2vec(c.r, c.theta, c.phi);
}

/// Convert Cartesian to spherical.
[[nodiscard]] inline auto vec2sph(const Vec3& v) -> SphericalCoord {
    double r = v.length();
    if (r < 1e-15) return {0.0, 0.0, 0.0};
    return {
        r,
        std::acos(std::clamp(v.y / r, -1.0, 1.0)),
        std::atan2(v.z, v.x)
    };
}

/// Great-circle angular separation between two directions (ignoring radial distance).
[[nodiscard]] inline auto angular_separation(
    const SphericalCoord& a, const SphericalCoord& b
) -> double {
    Vec3 va = sph2vec(1.0, a.theta, a.phi);
    Vec3 vb = sph2vec(1.0, b.theta, b.phi);
    return std::acos(std::clamp(va.dot(vb), -1.0, 1.0));
}

/// Compute kissing outer radius from Tammes minimum angular separation (degrees).
/// r_outer = sin(θ/2) / (1 − sin(θ/2))
[[nodiscard]] inline auto r_from_tammes_theta(double theta_deg) -> double {
    double s = std::sin(theta_deg * RAD_PER_DEG / 2.0);
    return s / (1.0 - s);
}

/// Coordinate round-trip error: sph → cart → sph → cart, measure distance.
[[nodiscard]] inline auto roundtrip_error(const SphericalCoord& c) -> double {
    Vec3 v1 = sph2vec(c);
    SphericalCoord c2 = vec2sph(v1);
    Vec3 v2 = sph2vec(c2);
    return v1.distance_to(v2);
}

// ═══════════════════════════════════════════════════════════════════════
//  PRESET GENERATORS
//
//  All 10 presets from the workbench, faithfully translated.
//  Each returns a PackingConfig with named geometry + nuclear alias.
// ═══════════════════════════════════════════════════════════════════════

namespace detail {
    inline void assign_ids(PackingConfig& cfg) {
        for (int i = 0; i < static_cast<int>(cfg.outers.size()); ++i) {
            cfg.outers[i].id = i;
        }
    }

    inline void push_sphere(PackingConfig& cfg, double r, double theta, double phi,
                           double radius, int shell = 0) {
        PackingSphere s;
        s.pos = {r, theta, phi};
        s.radius = radius;
        s.shell = shell;
        cfg.outers.push_back(s);
    }
}

/// Tammes n=3: equilateral triangle on equator
[[nodiscard]] inline auto preset_tammes3() -> PackingConfig {
    PackingConfig cfg;
    cfg.name = "tammes-3 (triangle)";
    cfg.nuclear_name = "triangle (n=3)";
    cfg.central_radius = 1.0;

    // r_outer for 3 on equator: 120° separation
    double r_outer = 2.0 * std::sqrt(3.0) + 3.0;
    double R = 1.0 + r_outer;
    for (int i = 0; i < 3; ++i) {
        detail::push_sphere(cfg, R, std::numbers::pi / 2.0,
            static_cast<double>(i) * TAU / 3.0, r_outer, 0);
    }
    detail::assign_ids(cfg);
    return cfg;
}

/// Tammes n=4: tetrahedron — He-4 alpha core scaffold
[[nodiscard]] inline auto preset_tammes4() -> PackingConfig {
    PackingConfig cfg;
    cfg.name = "tammes-4 (tetrahedron)";
    cfg.nuclear_name = "He-4 alpha tetrahedral scaffold";
    cfg.central_radius = 1.0;

    double r_outer = std::sqrt(6.0) + 2.0;
    double theta1 = std::acos(-1.0 / 3.0);
    double R = 1.0 + r_outer;

    detail::push_sphere(cfg, R, 0.0, 0.0, r_outer, 0);
    detail::push_sphere(cfg, R, theta1, 0.0, r_outer, 0);
    detail::push_sphere(cfg, R, theta1, TAU / 3.0, r_outer, 0);
    detail::push_sphere(cfg, R, theta1, 2.0 * TAU / 3.0, r_outer, 0);

    detail::assign_ids(cfg);
    return cfg;
}

/// Tammes n=6: octahedron — O-16 deuteron shell
[[nodiscard]] inline auto preset_tammes6() -> PackingConfig {
    PackingConfig cfg;
    cfg.name = "tammes-6 (octahedron)";
    cfg.nuclear_name = "O-16 deuteron octahedral shell";
    cfg.central_radius = 1.0;

    double r_outer = std::sqrt(2.0) + 1.0;
    double R = 1.0 + r_outer;
    double half_pi = std::numbers::pi / 2.0;

    detail::push_sphere(cfg, R, 0.0, 0.0, r_outer, 0);                        // +Y pole
    detail::push_sphere(cfg, R, std::numbers::pi, 0.0, r_outer, 0);           // -Y pole
    detail::push_sphere(cfg, R, half_pi, 0.0, r_outer, 0);                    // +X
    detail::push_sphere(cfg, R, half_pi, std::numbers::pi / 2.0, r_outer, 0); // +Z
    detail::push_sphere(cfg, R, half_pi, std::numbers::pi, r_outer, 0);       // -X
    detail::push_sphere(cfg, R, half_pi, 3.0 * std::numbers::pi / 2.0, r_outer, 0); // -Z

    detail::assign_ids(cfg);
    return cfg;
}

/// Tammes n=8: square antiprism
[[nodiscard]] inline auto preset_tammes8() -> PackingConfig {
    PackingConfig cfg;
    cfg.name = "tammes-8 (square antiprism)";
    cfg.nuclear_name = "square antiprism (n=8)";
    cfg.central_radius = 1.0;

    double r_outer = r_from_tammes_theta(74.858);
    double ring_theta = std::numbers::pi / 4.0;
    double R = 1.0 + r_outer;

    for (int i = 0; i < 4; ++i) {
        double phi_top = static_cast<double>(i) * TAU / 4.0;
        double phi_bot = phi_top + TAU / 8.0;
        detail::push_sphere(cfg, R, ring_theta, phi_top, r_outer, 0);
        detail::push_sphere(cfg, R, std::numbers::pi - ring_theta, phi_bot, r_outer, 0);
    }

    detail::assign_ids(cfg);
    return cfg;
}

/// Tammes n=12: icosahedron — 2 poles + 2 pentagons
[[nodiscard]] inline auto preset_tammes12() -> PackingConfig {
    PackingConfig cfg;
    cfg.name = "tammes-12 (icosahedron)";
    cfg.nuclear_name = "icosahedral shell (n=12)";
    cfg.central_radius = 1.0;

    double r_outer = r_from_tammes_theta(std::acos(std::sqrt(5.0) / 5.0) * DEG_PER_RAD);
    double theta_pent = std::atan(2.0);
    double R = 1.0 + r_outer;

    // Two poles
    detail::push_sphere(cfg, R, 0.0, 0.0, r_outer, 0);
    detail::push_sphere(cfg, R, std::numbers::pi, 0.0, r_outer, 0);

    // Two pentagons
    for (int i = 0; i < 5; ++i) {
        double phi1 = static_cast<double>(i) * TAU / 5.0;
        double phi2 = phi1 + TAU / 10.0;
        detail::push_sphere(cfg, R, theta_pent, phi1, r_outer, 0);
        detail::push_sphere(cfg, R, std::numbers::pi - theta_pent, phi2, r_outer, 0);
    }

    detail::assign_ids(cfg);
    return cfg;
}

/// Platonic cube (n=8) — Ca-40 shell arrangement
[[nodiscard]] inline auto preset_cube8() -> PackingConfig {
    PackingConfig cfg;
    cfg.name = "platonic-cube (n=8)";
    cfg.nuclear_name = "Ca-40 cubic shell";
    cfg.central_radius = 1.0;

    // Edge-kissing cube: r = (√3 + 1)/2
    double r = (std::sqrt(3.0) + 1.0) / 2.0;
    double R = 1.0 + r;

    for (int sx : {-1, 1}) {
        for (int sy : {-1, 1}) {
            for (int sz : {-1, 1}) {
                Vec3 v{static_cast<double>(sx), static_cast<double>(sy),
                       static_cast<double>(sz)};
                v = v.normalized() * R;
                auto s = vec2sph(v);
                detail::push_sphere(cfg, s.r, s.theta, s.phi, r, 0);
            }
        }
    }

    detail::assign_ids(cfg);
    return cfg;
}

/// Platonic dodecahedron (n=20)
[[nodiscard]] inline auto preset_dodec20() -> PackingConfig {
    PackingConfig cfg;
    cfg.name = "platonic-dodecahedron (n=20)";
    cfg.nuclear_name = "dodecahedral shell (n=20)";
    cfg.central_radius = 1.0;

    // Dodecahedron vertices: (±1,±1,±1) ∪ (0,±1/φ,±φ) and cyclic permutations
    std::vector<Vec3> verts;

    // Cube vertices
    for (int sx : {-1, 1})
        for (int sy : {-1, 1})
            for (int sz : {-1, 1})
                verts.push_back({static_cast<double>(sx),
                                 static_cast<double>(sy),
                                 static_cast<double>(sz)});

    double a = 1.0 / GOLDEN_RATIO;
    double b = GOLDEN_RATIO;

    // Rectangular face centres (cyclic perms)
    for (int s1 : {-1, 1}) {
        for (int s2 : {-1, 1}) {
            verts.push_back({0.0, s1 * a, s2 * b});
            verts.push_back({s1 * a, s2 * b, 0.0});
            verts.push_back({s2 * b, 0.0, s1 * a});
        }
    }

    // Outer radius: r = φ (edge-kissing condition)
    double r = GOLDEN_RATIO;
    double R = 1.0 + r;

    for (auto& v : verts) {
        Vec3 pos = v.normalized() * R;
        auto s = vec2sph(pos);
        detail::push_sphere(cfg, s.r, s.theta, s.phi, r, 0);
    }

    detail::assign_ids(cfg);
    return cfg;
}

/// Cuboctahedron n=12 (FCC kissing) — Fe-56 alpha cluster / Vector Equilibrium
[[nodiscard]] inline auto preset_cuboct12() -> PackingConfig {
    PackingConfig cfg;
    cfg.name = "cuboctahedron (n=12 kiss)";
    cfg.nuclear_name = "Fe-56 alpha cluster (Vector Equilibrium)";
    cfg.central_radius = 1.0;

    // 12 vertices at permutations of (±1, ±1, 0) — three orthogonal square cross-sections
    double R = 2.0;  // unit radii, kissing

    for (int axis = 0; axis < 3; ++axis) {
        for (int s1 : {-1, 1}) {
            for (int s2 : {-1, 1}) {
                double coords[3] = {0.0, 0.0, 0.0};
                coords[axis] = static_cast<double>(s1);
                coords[(axis + 1) % 3] = static_cast<double>(s2);
                Vec3 v{coords[0], coords[1], coords[2]};
                v = v.normalized() * R;
                auto s = vec2sph(v);
                detail::push_sphere(cfg, s.r, s.theta, s.phi, 1.0, 0);
            }
        }
    }

    detail::assign_ids(cfg);
    return cfg;
}

/// Cuboctahedron + octahedral & tetrahedral plugs — Fe-56 with interstitials
[[nodiscard]] inline auto preset_cuboct_plugged() -> PackingConfig {
    PackingConfig cfg = preset_cuboct12();
    cfg.name = "cuboctahedron + 14 plugs";
    cfg.nuclear_name = "Fe-56 full (cuboct + interstitial neutrons)";

    double r_oct = std::sqrt(2.0) - 1.0;       // ~0.4142
    double r_tet = std::sqrt(3.0 / 2.0) - 1.0; // ~0.2247

    // Octahedral plugs: 6 at (±√2, 0, 0) and permutations
    double oct_pos[][3] = {
        { std::numbers::sqrt2, 0.0, 0.0}, {-std::numbers::sqrt2, 0.0, 0.0},
        {0.0,  std::numbers::sqrt2, 0.0}, {0.0, -std::numbers::sqrt2, 0.0},
        {0.0, 0.0,  std::numbers::sqrt2}, {0.0, 0.0, -std::numbers::sqrt2},
    };
    for (auto& p : oct_pos) {
        auto s = vec2sph({p[0], p[1], p[2]});
        detail::push_sphere(cfg, s.r, s.theta, s.phi, r_oct, 1);
    }

    // Tetrahedral plugs: 8 at corners (±1,±1,±1) × √(3/2)/√3
    double d = std::sqrt(3.0 / 2.0);
    double u = 1.0 / std::sqrt(3.0);
    for (int sx : {-1, 1}) {
        for (int sy : {-1, 1}) {
            for (int sz : {-1, 1}) {
                Vec3 v{sx * u * d, sy * u * d, sz * u * d};
                auto s = vec2sph(v);
                detail::push_sphere(cfg, s.r, s.theta, s.phi, r_tet, 2);
            }
        }
    }

    detail::assign_ids(cfg);
    return cfg;
}

/// Icosahedral inner shell + snub triangle face plugs
[[nodiscard]] inline auto preset_shells_icos() -> PackingConfig {
    // Start from icosahedral base
    PackingConfig inner = preset_tammes12();

    PackingConfig cfg;
    cfg.name = "icos + snub shells";
    cfg.nuclear_name = "icosahedral layered shell";
    cfg.central_radius = 1.0;

    // Copy inner shell
    for (auto& s : inner.outers) {
        cfg.outers.push_back(s);
    }

    // Build Cartesian positions for inner shell
    std::vector<Vec3> verts;
    for (auto& s : inner.outers) {
        verts.push_back(sph2vec(s.pos));
    }

    double r_outer = inner.outers[0].radius;
    double target_edge = 2.0 * r_outer;

    // Find icosahedral triangular faces by triplet edge test
    double plug_r = 0.3;

    for (int i = 0; i < static_cast<int>(verts.size()); ++i) {
        for (int j = i + 1; j < static_cast<int>(verts.size()); ++j) {
            for (int k = j + 1; k < static_cast<int>(verts.size()); ++k) {
                double d_ij = verts[i].distance_to(verts[j]);
                double d_jk = verts[j].distance_to(verts[k]);
                double d_ik = verts[i].distance_to(verts[k]);

                auto eq = [&](double x) {
                    return std::abs(x - target_edge) < 0.01 * target_edge;
                };

                if (eq(d_ij) && eq(d_jk) && eq(d_ik)) {
                    // Face centroid
                    Vec3 c = (verts[i] + verts[j] + verts[k]) * (1.0 / 3.0);
                    Vec3 n = c.normalized();
                    Vec3 plug_pos = c + n * (plug_r * 0.5);
                    auto s = vec2sph(plug_pos);
                    detail::push_sphere(cfg, s.r, s.theta, s.phi, plug_r, 1);
                }
            }
        }
    }

    detail::assign_ids(cfg);
    return cfg;
}

// ═══════════════════════════════════════════════════════════════════════
//  PRESET REGISTRY
// ═══════════════════════════════════════════════════════════════════════

/// All available preset names (geometric)
inline const char* PRESET_NAMES[] = {
    "tammes-3",
    "tammes-4",
    "tammes-6",
    "tammes-8",
    "tammes-12",
    "platonic-cube",
    "platonic-dodec",
    "cuboct-12",
    "cuboct-plugged",
    "shells-icos",
};
inline constexpr int NUM_PRESETS = 10;

/// Nuclear aliases — same order as PRESET_NAMES
inline const char* NUCLEAR_NAMES[] = {
    "triangle (n=3)",
    "He-4 alpha tetrahedral scaffold",
    "O-16 deuteron octahedral shell",
    "square antiprism (n=8)",
    "icosahedral shell (n=12)",
    "Ca-40 cubic shell",
    "dodecahedral shell (n=20)",
    "Fe-56 alpha cluster (Vector Equilibrium)",
    "Fe-56 full (cuboct + interstitial neutrons)",
    "icosahedral layered shell",
};

/// Load a preset by name
[[nodiscard]] inline auto load_preset(const char* name) -> PackingConfig {
    if (std::strcmp(name, "tammes-3") == 0)       return preset_tammes3();
    if (std::strcmp(name, "tammes-4") == 0)       return preset_tammes4();
    if (std::strcmp(name, "tammes-6") == 0)       return preset_tammes6();
    if (std::strcmp(name, "tammes-8") == 0)       return preset_tammes8();
    if (std::strcmp(name, "tammes-12") == 0)      return preset_tammes12();
    if (std::strcmp(name, "platonic-cube") == 0)   return preset_cube8();
    if (std::strcmp(name, "platonic-dodec") == 0)  return preset_dodec20();
    if (std::strcmp(name, "cuboct-12") == 0)       return preset_cuboct12();
    if (std::strcmp(name, "cuboct-plugged") == 0)  return preset_cuboct_plugged();
    if (std::strcmp(name, "shells-icos") == 0)     return preset_shells_icos();

    // Fallback — empty config
    PackingConfig cfg;
    cfg.name = "unknown";
    cfg.nuclear_name = "unknown";
    return cfg;
}

// ═══════════════════════════════════════════════════════════════════════
//  ANALYSIS FUNCTIONS
// ═══════════════════════════════════════════════════════════════════════

/// Find the pair with minimum angular separation.
/// Returns pair IDs and angle in radians.
[[nodiscard]] inline auto min_angular_pair(const PackingConfig& cfg) -> SpherePair {
    SpherePair result;
    result.angle = 1e30;

    for (int i = 0; i < static_cast<int>(cfg.outers.size()); ++i) {
        if (cfg.outers[i].hidden) continue;
        for (int j = i + 1; j < static_cast<int>(cfg.outers.size()); ++j) {
            if (cfg.outers[j].hidden) continue;
            double ang = angular_separation(cfg.outers[i].pos, cfg.outers[j].pos);
            if (ang < result.angle) {
                result.id_a = cfg.outers[i].id;
                result.id_b = cfg.outers[j].id;
                result.angle = ang;
            }
        }
    }
    return result;
}

/// Gap between central sphere surface and outer sphere surface.
/// Negative = overlap, zero = kissing, positive = gap.
[[nodiscard]] inline auto central_outer_gap(
    const PackingConfig& cfg, int sphere_id
) -> double {
    for (auto& s : cfg.outers) {
        if (s.id == sphere_id) {
            return s.pos.r - cfg.central_radius - s.radius;
        }
    }
    return 0.0;
}

/// Find all nearly-kissing outer pairs within tolerance.
[[nodiscard]] inline auto kissing_pairs(
    const PackingConfig& cfg, double tolerance = 0.03
) -> std::vector<SpherePair> {
    std::vector<SpherePair> result;

    for (int i = 0; i < static_cast<int>(cfg.outers.size()); ++i) {
        if (cfg.outers[i].hidden) continue;
        Vec3 va = sph2vec(cfg.outers[i].pos);
        for (int j = i + 1; j < static_cast<int>(cfg.outers.size()); ++j) {
            if (cfg.outers[j].hidden) continue;
            Vec3 vb = sph2vec(cfg.outers[j].pos);
            double d = va.distance_to(vb);
            double target = cfg.outers[i].radius + cfg.outers[j].radius;
            double rel = std::abs(d - target) / target;
            if (rel < tolerance) {
                SpherePair p;
                p.id_a = cfg.outers[i].id;
                p.id_b = cfg.outers[j].id;
                p.gap = d - target;
                p.angle = angular_separation(cfg.outers[i].pos, cfg.outers[j].pos);
                result.push_back(p);
            }
        }
    }
    return result;
}

/// Print a full diagnostic report for a packing configuration.
inline void packing_report(const PackingConfig& cfg) {
    std::printf("╔══════════════════════════════════════════════════════════════╗\n");
    std::printf("║  PACKING: %-49s ║\n", cfg.name.c_str());
    if (!cfg.nuclear_name.empty()) {
        std::printf("║  NUCLEAR: %-49s ║\n", cfg.nuclear_name.c_str());
    }
    std::printf("╠══════════════════════════════════════════════════════════════╣\n");
    std::printf("║  Central radius: %.6f                                     ║\n",
        cfg.central_radius);
    std::printf("║  Outer spheres:  %d                                          ║\n",
        static_cast<int>(cfg.outers.size()));
    std::printf("╠══════════════════════════════════════════════════════════════╣\n");

    // Header
    std::printf("  ID  shell  radius      ρ          θ°          φ°       c-gap\n");
    std::printf("  ──  ─────  ──────   ────────   ─────────   ─────────   ──────\n");

    for (auto& s : cfg.outers) {
        double gap = central_outer_gap(cfg, s.id);
        std::printf("  %2d   %d    %7.4f   %8.5f   %9.4f   %9.4f   %+.5f\n",
            s.id, s.shell, s.radius,
            s.pos.r, s.pos.theta_deg(), s.pos.phi_deg(),
            gap);
    }

    // Min-angle pair
    if (cfg.outers.size() >= 2) {
        auto pair = min_angular_pair(cfg);
        std::printf("\n  Min angular pair: #%d – #%d  →  %.4f° (%.6f rad)\n",
            pair.id_a, pair.id_b, pair.angle * DEG_PER_RAD, pair.angle);
    }

    // Kissing pairs
    auto kp = kissing_pairs(cfg);
    if (!kp.empty()) {
        std::printf("\n  Kissing pairs (%d):\n", static_cast<int>(kp.size()));
        int shown = 0;
        for (auto& p : kp) {
            std::printf("    #%d – #%d  gap=%+.6f  angle=%.4f°\n",
                p.id_a, p.id_b, p.gap, p.angle * DEG_PER_RAD);
            if (++shown >= 20) {
                std::printf("    ... (%d more)\n",
                    static_cast<int>(kp.size()) - shown);
                break;
            }
        }
    }

    // Coordinate round-trip integrity
    double max_err = 0.0;
    for (auto& s : cfg.outers) {
        double err = roundtrip_error(s.pos);
        if (err > max_err) max_err = err;
    }
    std::printf("\n  Coordinate round-trip max error: %.2e\n", max_err);

    std::printf("╚══════════════════════════════════════════════════════════════╝\n\n");
}

} // namespace sdt::packing
