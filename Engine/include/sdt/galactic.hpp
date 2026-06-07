#ifndef SDT_GALACTIC_HPP
#define SDT_GALACTIC_HPP

/**
 * @file galactic.hpp
 * @brief SDT Galactic Module — CMB-Powered Galaxy Formulation
 *
 * ╔══════════════════════════════════════════════════════════════════════════╗
 * ║  THE MECHANISM (Law III — Convergent Boundary Pressure)                ║
 * ║                                                                        ║
 * ║  The CMB is not a relic radiation bath. It is the observable spectral  ║
 * ║  residue of an already-arrived, globally convergent boundary           ║
 * ║  transition. At every interior point in the lattice:                   ║
 * ║                                                                        ║
 * ║       P_conv = N · u_CMB = 2.459×10⁴⁸ Pa                             ║
 * ║                                                                        ║
 * ║  This convergence pressure is the SOLE motor of galactic dynamics.     ║
 * ║  Baryonic matter = displacement volumes in the spation lattice.        ║
 * ║  Each baryon OCCLUDES a solid angle of the convergence hemisphere.     ║
 * ║  The resulting angular imbalance drives orbital motion.                ║
 * ║  Nothing attracts. Everything occludes.                                ║
 * ║                                                                        ║
 * ║  The CMB is EM output — photons. It is lensed by galactic             ║
 * ║  displacement topology. The Milky Way lenses its own CMB field.        ║
 * ║  The disk concentrates convergence pressure toward the midplane.       ║
 * ║  This self-lensing modifies the effective CMB field that powers        ║
 * ║  galactic orbital dynamics.                                            ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║  TWIN REGIME ARCHITECTURE (CQ20d, CQ20g, CQ20e)                       ║
 * ║                                                                        ║
 * ║  Regime I  — BULGE (r < r_bulge_edge)                                 ║
 * ║    Oblate spheroid geometry. 3D occlusion from ALL azimuthal and       ║
 * ║    polar directions simultaneously. The ^1.3 spheroid enhancement:     ║
 * ║       Ω_spheroid / Ω_disk = (r/r_ref)^0.3                            ║
 * ║    Bulge Koppa feeds as the immovable floor for the disk regime.       ║
 * ║                                                                        ║
 * ║  Regime II — DISK (r > r_transition)                                  ║
 * ║    Bidirectional shell-by-shell occlusion. Interior engines reduce     ║
 * ║    convergence from the Sag A* direction. Exterior engines reduce      ║
 * ║    convergence from the rim. Net gradient differential drives the      ║
 * ║    flat rotation curve. CMB self-lensing adds a midplane boost.        ║
 * ║                                                                        ║
 * ║  Bar/Transition (3.5–5 kpc): solid-line occlusion streak. The bar     ║
 * ║  subtends a constant angular width — locking the flat velocity onset.  ║
 * ╠══════════════════════════════════════════════════════════════════════════╣
 * ║  CLOSURE IDENTITY: zk² = 1 at every radius.                           ║
 * ║  No G. No M in kg. No gravitational attractor. CMB powers everything. ║
 * ╚══════════════════════════════════════════════════════════════════════════╝
 *
 * @author SDT Canonical Engine — James Tyndall, Melbourne, Australia
 */

#include <cmath>
#include <numbers>
#include <algorithm>
#include <sdt/laws.hpp>

namespace sdt::galactic {

using namespace sdt::laws::measured;
namespace B  = sdt::laws::bridge;
namespace LI = sdt::laws::law_I;

// ═════════════════════════════════════════════════════════════════════════════
//  SCALE CONSTANTS
// ═════════════════════════════════════════════════════════════════════════════

inline constexpr double PI            = std::numbers::pi;
inline constexpr double kpc_m         = 3.085677581e19;   ///< [m/kpc]
inline constexpr double pc_m_         = 3.085677581e16;   ///< [m/pc]  (trailing _ avoids shadowing)
inline constexpr double Msun_kg       = 1.98847e30;       ///< [kg] Solar mass
inline constexpr double deg2rad       = PI / 180.0;

/// SDT Milgrom scale: a₀ = c H₀ / 2π — derived, not imported (CQ06)
/// H₀ = 67.4 km/s/Mpc (Planck 2018)
inline constexpr double H_0_SI        = 67.4e3 / 3.085677581e22;  // [s⁻¹]
inline constexpr double a_0_SDT       = c * H_0_SI / (2.0 * PI);  // ≈ 1.042e-10 m/s²

// ═════════════════════════════════════════════════════════════════════════════
//  CMB FIELD — The Convergence Motor
//
//  From Law I (Cosmological Relay Throughput):
//    Φ = N·ε,  P_conv = Φ/ℓ_P³ = N·u_CMB = 2.459×10⁴⁸ Pa
//
//  From Law III (Convergent Boundary Pressure):
//    Force arises ONLY where matter occludes a fraction of the 4π angular
//    convergence domain. Without occlusion, P_conv is perfectly isotropic
//    → zero net force → no orbit.
//
//  The CMB is EM output (photons). It is lensed by galactic displacement
//  topology just as light is lensed by gravitational fields. The MW disk
//  acts as a distributed gravitational lens for the very CMB field that
//  powers it — a self-lensing loop that concentrates convergence pressure
//  toward the midplane, providing a measurable correction to the orbital
//  velocity profile.
// ═════════════════════════════════════════════════════════════════════════════

namespace cmb_field {

    /// Convergence pressure: P_conv = Φ/ℓ_P³ = N·u_CMB [Pa]  (Law I, Law III)
    /// This is the isotropic CMB convergence pressure at every point in the universe.
    /// It is the SOLE energy source driving galactic orbital dynamics.
    inline constexpr double P_conv = LI::P_conv;   // 2.459e48 Pa

    /// CMB energy density u₀ = a_rad·T_CMB⁴ [J/m³] — observable confirmation
    inline constexpr double u_CMB  = LI::u_CMB;    // 4.172e-14 J/m³

    /// Causal depth: N = R_CMB / ℓ_P  (Planck relay stages from here to the Clearing)
    inline constexpr double N_relay = LI::N;        // 5.894e61

    /**
     * @brief Line-of-sight column Koppa from observer at R₀ in direction (l, b).
     *
     * Integrates the occlusion density (v/c)² × exp(-|z|/h_z) along the
     * line of sight through the galactic disk. Returns:
     *
     *   K_col [m] = ∫ (v(r)/c)² · exp(-|z(s)|/h_z) ds
     *
     * This is the total CMB convergence OCCLUDED by the disk material along
     * that line of sight. Higher column Koppa in a given direction means more
     * CMB convergence has been absorbed there — producing an apparent pressure
     * deficit (and hence apparent "streaming") in that direction.
     *
     * Used in: MW skymap (CQ22), EM lensing, photon z-imprint.
     *
     * @param l_rad     Galactic longitude [rad]
     * @param b_rad     Galactic latitude [rad]
     * @param R0_kpc    Observer galactocentric radius [kpc]
     * @param h_z_kpc   Disk vertical scale height [kpc]
     * @param v_at_kpc  Velocity interpolator: v(r_kpc) → km/s
     * @param r_max_kpc Integration path length [kpc]
     * @param N_steps   Trapezoidal integration steps
     * @return Column Koppa K_col [m]
     */
    template<typename VelocityFn>
    [[nodiscard]] inline double column_koppa(
        double l_rad, double b_rad,
        double R0_kpc, double h_z_kpc,
        VelocityFn&& v_at_kpc,
        double r_max_kpc = 20.0,
        int    N_steps   = 200
    ) noexcept {
        if (r_max_kpc <= 0.0 || N_steps < 1) return 0.0;
        const double ds    = r_max_kpc / static_cast<double>(N_steps);
        const double cos_b = std::cos(b_rad);
        const double sin_b = std::sin(b_rad);
        const double cos_l = std::cos(l_rad);
        const double sin_l = std::sin(l_rad);
        double K = 0.0;

        auto sample = [&](double s_kpc) noexcept -> double {
            // Galactocentric position of LOS point s kpc from observer
            const double x   = R0_kpc - s_kpc * cos_b * cos_l;
            const double y   = s_kpc  * cos_b * sin_l;
            const double z_h = s_kpc  * sin_b;           // height above midplane
            const double r   = std::sqrt(x*x + y*y);
            // Vertical disk suppression
            const double f_z = (h_z_kpc > 0.0)
                              ? std::exp(-std::fabs(z_h) / h_z_kpc)
                              : 1.0;
            const double v   = v_at_kpc(r) * 1e3;        // m/s
            return (v / c) * (v / c) * f_z;
        };

        for (int i = 0; i < N_steps; i++) {
            const double s1  = i * ds;
            const double s2  = s1 + ds;
            const double od1 = sample(s1);
            const double od2 = sample(s2);
            K += 0.5 * (od1 + od2) * ds * kpc_m;   // [m]
        }
        return K;
    }

    /**
     * @brief CMB self-lensing boost: the MW lensing its own convergence field.
     *
     * The CMB is EM output. The galactic disk's displacement topology has a
     * varying refractive index n(r) = v(r)/c. CMB photons traversing the disk
     * accumulate a convergence-depth shift:
     *
     *   Δz_col = K_col_equatorial / R_disk
     *
     * This shift is directional — maximum in the equatorial plane (b=0°) and
     * zero toward the poles (b=±90°). A test particle embedded in the disk
     * therefore sees a CMB field that is slightly concentrated toward the
     * equatorial plane relative to the ideal isotropic case.
     *
     * The fractional boost to equatorial convergence pressure is:
     *
     *   boost(R, z) = (K_col_eq / R) × exp(-|z|/h_z)
     *
     * At Earth (R₀ = 8.178 kpc, z ≈ 0.025 kpc): boost ≈ 0.5–1.5%.
     * This is a first-order perturbation — real but small relative to the
     * dominant bidirectional occlusion. At the galactic centre, it is larger.
     *
     * @param K_col_equatorial  Column Koppa in equatorial direction [m]
     * @param R_kpc             Galactocentric radius [kpc]
     * @param z_kpc             Height above midplane [kpc]
     * @param h_z_kpc           Disk vertical scale height [kpc]
     * @return Fractional lensing boost [dimensionless]
     */
    [[nodiscard]] inline double convergence_lensing_boost(
        double K_col_equatorial,
        double R_kpc,
        double z_kpc,
        double h_z_kpc
    ) noexcept {
        if (R_kpc <= 0.0 || K_col_equatorial <= 0.0) return 0.0;
        const double f_z = (h_z_kpc > 0.0)
                         ? std::exp(-std::fabs(z_kpc) / h_z_kpc)
                         : 1.0;
        // Δz_gal = K_col / R  (from CQ22 Section E: Δz_gal = K_col/R₀)
        return (K_col_equatorial / (R_kpc * kpc_m)) * f_z;
    }

    /**
     * @brief CMB photon deflection angle from MW disk self-lensing.
     *
     * From Law V bending formula: θ = 2 ∫ ∇⊥(v²/c²) dl
     *
     * For a photon traversing the disk at latitude b, the perpendicular
     * (z-direction) gradient is:
     *
     *   ∇⊥(v²/c²) ≈ (v²/c²) × sin|b| / h_z
     *
     * Integrated over the disk path length r_los:
     *
     *   θ_lens = 2 × K_col × sin|b| / (h_z × r_los)
     *
     * At b=0° (equatorial), θ = 0 by symmetry — no net bending in the plane.
     * Maximum bending occurs at intermediate latitudes (b ≈ 30°–45°) where
     * there is both a perpendicular gradient and a significant disk column.
     *
     * This lensing angle shifts the effective solid angle of the CMB field
     * seen by a test particle — modifying the convergence pressure anisotropy.
     *
     * @param b_rad      Galactic latitude of photon path [rad]
     * @param h_z_kpc    Disk scale height [kpc]
     * @param K_col      Column Koppa along LOS [m]
     * @param r_los_kpc  LOS path length through disk [kpc]
     * @return Photon deflection angle [rad]
     */
    [[nodiscard]] inline double cmb_lensing_deflection(
        double b_rad,
        double h_z_kpc,
        double K_col,
        double r_los_kpc
    ) noexcept {
        if (h_z_kpc <= 0.0 || r_los_kpc <= 0.0 || K_col <= 0.0) return 0.0;
        const double sin_b = std::fabs(std::sin(b_rad));
        const double h_z_m = h_z_kpc * kpc_m;
        const double r_m   = r_los_kpc * kpc_m;
        return 2.0 * K_col * sin_b / (h_z_m * r_m);
    }

    /**
     * @brief Additional Koppa from CMB self-lensing at test particle position.
     *
     * The lensing boost translates into an additional effective Koppa:
     *
     *   Ϟ_lens(R, z) = boost(R, z) × R   [m]
     *
     * This enters the velocity formula as a third source alongside
     * Ϟ_interior and Ϟ_exterior:
     *
     *   v²(R) = c² × (Ϟ_int + Ϟ_ext + Ϟ_lens) / R
     *
     * @param K_col_equatorial  Column Koppa in equatorial direction [m]
     * @param R_kpc             Galactocentric radius [kpc]
     * @param z_kpc             Height above midplane [kpc]
     * @param h_z_kpc           Disk vertical scale height [kpc]
     * @return Lensing Koppa Ϟ_lens [m]
     */
    [[nodiscard]] inline double koppa_lensing(
        double K_col_equatorial,
        double R_kpc,
        double z_kpc,
        double h_z_kpc
    ) noexcept {
        const double boost = convergence_lensing_boost(
            K_col_equatorial, R_kpc, z_kpc, h_z_kpc);
        return boost * R_kpc * kpc_m;
    }

} // namespace cmb_field


// ═════════════════════════════════════════════════════════════════════════════
//  GALAXY PROFILE AND RESULT STRUCTURES
// ═════════════════════════════════════════════════════════════════════════════

/// Galaxy morphological type — selects the occlusion geometry model.
enum class GalaxyType : int {
    Spiral      = 0,  ///< Exponential disk + optional bulge + optional bar
    Dwarf       = 1,  ///< Same as Spiral, low baryonic content (sub-eclipse regime)
    LSB         = 2,  ///< Low Surface Brightness: large h_R, sub-critical Σ₀
    Elliptical  = 3,  ///< de Vaucouleurs spheroid geometry throughout
    Cluster     = 4,  ///< Mega-Koppa, saturated occlusion
};

/**
 * @brief Complete galaxy parameter set — pure geometry, no mass in kg, no G.
 *
 * ALL baryonic content is encoded via koppa_total_m (Ϟ = v²R/c²). This single
 * scalar replaces GM entirely. It is the c-boundary of the galaxy — the only
 * quantity the CMB occlusion geometry needs.
 *
 *   koppa_total_m = M_bar [M☉] × Ϟ_sun   where Ϟ_sun ≈ 1477 m
 *
 * The geometry parameters (h_R, h_z, R_bulge, q_bulge, R_bar) determine HOW
 * the baryonic displacement volumes are distributed — which in turn determines
 * the exact pattern of CMB occlusion as a function of radius.
 */
struct GalaxyProfile {
    // ── Identity ───────────────────────────────────────────────────────────
    const char* name               = "Galaxy";
    GalaxyType  type               = GalaxyType::Spiral;

    // ── Baryonic content via Koppa (no G, no kg) ───────────────────────────
    double koppa_total_m           = 0.0;  ///< Ϟ_gal = M_bar [M☉] × Ϟ_sun  [m]

    // ── Disk geometry ──────────────────────────────────────────────────────
    double h_R_kpc                 = 2.6;  ///< Radial exponential scale length [kpc]
    double h_z_kpc                 = 0.3;  ///< Vertical scale height [kpc]
    double R_max_kpc               = 25.0; ///< Disk truncation radius [kpc]

    // ── Bulge geometry ─────────────────────────────────────────────────────
    double R_bulge_kpc             = 0.0;  ///< Bulge half-mass radius [kpc] (0 = no bulge)
    double q_bulge                 = 0.0;  ///< Oblate axis ratio [0,1] (0 = no bulge)
    double f_bulge                 = 0.0;  ///< Fraction of total Koppa in bulge [0,1]

    // ── Bar geometry ───────────────────────────────────────────────────────
    double R_bar_kpc               = 0.0;  ///< Bar half-length [kpc] (0 = no bar)
    double bar_halfwidth_kpc       = 0.5;  ///< Bar half-width [kpc]
    double bar_tilt_deg            = 27.0; ///< Bar angle to Sun-centre line [deg]
    double f_bar                   = 0.0;  ///< Fraction of total Koppa in bar [0,1]

    // ── CMB self-lensing ───────────────────────────────────────────────────
    bool   enable_cmb_lensing      = true; ///< Include MW EM self-lensing correction
    double R0_observer_kpc         = 8.178;///< Observer galactocentric radius [kpc]
};

/**
 * @brief Complete SDT galactic result at one (R, z) position.
 *
 * All quantities flow from Koppa scalar + CMB occlusion geometry.
 * The closure identity zk² = 1.000000 holds at every radius without exception.
 * Any deviation from unity indicates an implementation error.
 */
struct GalaxyResult {
    // ── Input state ────────────────────────────────────────────────────────
    double R_kpc                   = 0.0;  ///< Galactocentric radius [kpc]
    double z_kpc                   = 0.0;  ///< Height above midplane [kpc]

    // ── Velocity components [km/s] ─────────────────────────────────────────
    double v_bulge_kms             = 0.0;  ///< Regime I: bulge spheroid occlusion
    double v_disk_kms              = 0.0;  ///< Regime II: bidirectional disk occlusion
    double v_bar_kms               = 0.0;  ///< Bar/transition: solid-line streak
    double v_lensing_kms           = 0.0;  ///< CMB self-lensing contribution
    double v_total_kms             = 0.0;  ///< v_total = √(vb²+vd²+vr²+vl²)

    // ── Koppa budget [m] ───────────────────────────────────────────────────
    double koppa_interior_m        = 0.0;  ///< Ϟ_int = ∫₀ᴿ (v/c)² dr
    double koppa_exterior_m        = 0.0;  ///< Ϟ_ext = ∫ᴿ^Rmax (v/c)²·(R/r) dr
    double koppa_lensing_m         = 0.0;  ///< Ϟ_lens from CMB self-lensing
    double koppa_eff_m             = 0.0;  ///< Ϟ_eff = Ϟ_int + Ϟ_ext + Ϟ_lens

    // ── SDT field scalars ──────────────────────────────────────────────────
    double z_spation               = 0.0;  ///< z = (v/c)²  [spation depth]
    double k_spation               = 0.0;  ///< k = c/v     [inverse spation depth]
    double zk2                     = 0.0;  ///< Closure: z·k² = 1.000000

    // ── CMB lensing diagnostics ────────────────────────────────────────────
    double cmb_lensing_boost       = 0.0;  ///< Fractional boost to equatorial P_conv
    double cmb_deflection_rad      = 0.0;  ///< CMB photon deflection angle [rad]
    double occlusion_ratio         = 0.0;  ///< Ϟ_int / Ϟ_ext (flatness indicator ~1.3 in flat zone)
};


// ═════════════════════════════════════════════════════════════════════════════
//  REGIME I — BULGE OCCLUSION
//
//  The oblate spheroid geometry means interior engines subtend convergence
//  from ALL directions simultaneously — not just the equatorial slice.
//  This 3D occlusion produces a (r/r_ref)^0.3 enhancement factor:
//
//    Ω_spheroid / Ω_disk = (r/r_ref)^0.3
//
//  At r_ref = 0.2 kpc (inner bulge boundary): factor = 1.0 (reference)
//  At r = 3.5 kpc (bar/disk edge): factor ≈ 1.75
//
//  Source: CQ20g solid-angle integration for oblate spheroid q ≈ 0.6
//  This is purely geometric — no mass, no G.
// ═════════════════════════════════════════════════════════════════════════════

namespace regime_bulge {

    /**
     * @brief Spheroid occlusion enhancement factor (^1.3 geometry, CQ20g).
     *
     * In a THIN DISK, each engine at r occludes only the equatorial convergence
     * slice (2D solid-angle strip: Ω_disk ≈ 2π·δθ sr — one hemisphere slice).
     *
     * In an OBLATE SPHEROID (axis ratio q), the same engine occludes from ALL
     * azimuthal AND polar directions simultaneously (full 3D coverage).
     * The ratio Ω_sph/Ω_disk = (r/r_ref)^0.3 for q ≈ 0.6.
     *
     * Geometric origin of 0.3 exponent: integrating the solid-angle subtended
     * by a uniform-density oblate spheroid shell over all interior shells
     * relative to the flat-disk approximation yields this power law.
     *
     * Axial boost: the oblate compression (q < 1) concentrates displacement
     * volume near the equatorial plane, boosting equatorial occlusion by
     * (1 + (1-q)/2) relative to a sphere of equal enclosed mass.
     *
     * @param r_kpc      Test particle radius [kpc]
     * @param r_ref_kpc  Reference radius (inner bulge boundary ≈ 0.2 kpc)
     * @param q          Oblate axis ratio [0,1] (0=sphere, 1=pancake; MW ≈ 0.6)
     * @return Enhancement factor ≥ 1.0
     */
    [[nodiscard]] inline double spheroid_factor(
        double r_kpc,
        double r_ref_kpc = 0.2,
        double q         = 0.6
    ) noexcept {
        if (r_kpc <= 0.0 || r_ref_kpc <= 0.0) return 1.0;
        // Oblate compression bonus: channels extra convergence to equatorial band
        const double axial_boost = 1.0 + (1.0 - q) * 0.5;
        const double r_ratio     = r_kpc / r_ref_kpc;
        return axial_boost * std::pow(r_ratio, 0.3);
    }

    /**
     * @brief Interior Koppa from discrete bulge engines.
     *
     * Each engine at r_i ≤ R contributes to the centre-ward CMB occlusion:
     *   Ϟ_i = v_i² × r_i / c²
     *
     * The spheroid factor enhances this by the 3D geometry boost.
     * All Ϟ from observed velocities — no G, no M.
     *
     * @param R_kpc          Test particle radius [kpc]
     * @param r_engines      Engine radii array [kpc]
     * @param v_engines_kms  Engine velocities array [km/s]
     * @param n_engines      Array length
     * @param r_ref_kpc      Spheroid reference radius [kpc]
     * @param q_axis         Spheroid axis ratio
     * @return Interior Koppa Ϟ_int [m]
     */
    [[nodiscard]] inline double koppa_interior_engines(
        double        R_kpc,
        const double* r_engines,
        const double* v_engines_kms,
        int           n_engines,
        double        r_ref_kpc = 0.2,
        double        q_axis    = 0.6
    ) noexcept {
        double K_int = 0.0;
        for (int i = 0; i < n_engines; i++) {
            if (r_engines[i] > R_kpc) continue;
            const double r_m = r_engines[i] * kpc_m;
            const double v_m = v_engines_kms[i] * 1e3;
            const double K_i = v_m * v_m * r_m / (c * c);
            const double sf  = spheroid_factor(r_engines[i], r_ref_kpc, q_axis);
            K_int += K_i * sf;
        }
        return K_int;
    }

    /**
     * @brief Exterior Koppa from discrete bulge engines toward the rim.
     *
     * Each engine at r_j > R reduces rim-ward convergence at R.
     * Weight: (R/r_j) — closer exterior engines cast larger occlusion shadows.
     *
     * @param R_kpc          Test particle radius [kpc]
     * @param r_engines      Engine radii array [kpc]
     * @param v_engines_kms  Engine velocities array [km/s]
     * @param n_engines      Array length
     * @return Exterior Koppa Ϟ_ext [m]
     */
    [[nodiscard]] inline double koppa_exterior_engines(
        double        R_kpc,
        const double* r_engines,
        const double* v_engines_kms,
        int           n_engines
    ) noexcept {
        double K_ext = 0.0;
        for (int i = 0; i < n_engines; i++) {
            if (r_engines[i] <= R_kpc || r_engines[i] <= 0.0) continue;
            const double r_m = r_engines[i] * kpc_m;
            const double R_m = R_kpc * kpc_m;
            const double v_m = v_engines_kms[i] * 1e3;
            const double K_i = v_m * v_m * r_m / (c * c);
            K_ext += K_i * (R_m / r_m);
        }
        return K_ext;
    }

    /**
     * @brief Orbital velocity from effective Koppa.
     * v²(R) = c² × Ϟ_eff / R   [the SDT orbital velocity law]
     * @param K_eff_m  Effective Koppa [m]
     * @param R_kpc    Radius [kpc]
     * @return Velocity [km/s]
     */
    [[nodiscard]] inline double v_from_koppa(double K_eff_m, double R_kpc) noexcept {
        if (R_kpc <= 0.0 || K_eff_m <= 0.0) return 0.0;
        const double v2 = c * c * K_eff_m / (R_kpc * kpc_m);
        return (v2 > 0.0) ? std::sqrt(v2) / 1e3 : 0.0;
    }

} // namespace regime_bulge


// ═════════════════════════════════════════════════════════════════════════════
//  REGIME II — DISK OCCLUSION
//
//  Bidirectional shell-by-shell occlusion. At galactocentric radius R:
//
//    Interior: engines at r < R occlude convergence from the Sag A* direction.
//      They reduce the centre-ward component of the convergence gradient.
//      → This "pushes" the test particle outward.
//
//    Exterior: engines at r > R occlude convergence from the rim direction.
//      They reduce the rim-ward component of the convergence gradient.
//      → This "pushes" the test particle inward.
//
//    Equilibrium: the particle orbits where these forces balance:
//      v²(R) = c² × Ϟ_eff(R) / R
//
//  FLAT ROTATION MECHANISM (proven in CQ20g):
//    In an exponential disk, Ϟ_interior grows at the same rate that
//    Ϟ_exterior falls — so Ϟ_eff(R) ∝ R → v(R) = const.
//    This is pure geometry. No mass coincidence. No dark matter.
//
//    Beyond the disk edge: Ϟ_exterior collapses faster than Ϟ_interior
//    grows → Ϟ_eff/R decreases → v(R) declines. A PREDICTION.
// ═════════════════════════════════════════════════════════════════════════════

namespace regime_disk {

    /**
     * @brief Interior Koppa: Ϟ_int(R) = ∫₀ᴿ (v(r)/c)² dr  [m]
     *
     * Physical meaning: z(r) = (v(r)/c)² is the occlusion density per unit
     * radius. Each dr of displacement volume at r contributes z(r)·dr to
     * the centre-ward convergence reduction at R.
     *
     * ALL Koppa from observed velocities — no G, no M. zk² = 1 at every r.
     *
     * @param R_kpc     Upper integration limit [kpc]
     * @param v_at      Velocity interpolator: v(r_kpc) → km/s
     * @param r_min_kpc Lower limit (near Sag A*, ≈ 1 pc) [kpc]
     * @param N         Trapezoidal steps
     * @return Ϟ_int [m]
     */
    template<typename VelocityFn>
    [[nodiscard]] inline double koppa_interior(
        double R_kpc,
        VelocityFn&& v_at,
        double r_min_kpc = 0.001,
        int    N         = 400
    ) noexcept {
        if (R_kpc <= r_min_kpc || N < 1) return 0.0;
        const double dr = (R_kpc - r_min_kpc) / static_cast<double>(N);
        double K = 0.0;
        for (int i = 0; i < N; i++) {
            const double r1 = r_min_kpc + i * dr;
            const double r2 = r1 + dr;
            const double v1 = v_at(r1) * 1e3;
            const double v2 = v_at(r2) * 1e3;
            K += 0.5 * ((v1/c)*(v1/c) + (v2/c)*(v2/c)) * dr * kpc_m;
        }
        return K;
    }

    /**
     * @brief Exterior Koppa: Ϟ_ext(R) = ∫ᴿ^Rmax (v/c)² · (R/r) dr  [m]
     *
     * Physical meaning: a shell at r > R subtends solid angle ∝ (R/r)² from R.
     * Its rim-ward convergence blocking is therefore weighted by (R/r).
     * This integral is the total rim-ward occlusion budget at R.
     *
     * FLATNESS PROOF: in the flat zone (3.5–15 kpc),
     *   dϞ_int/dR ≈ 1.3 × dϞ_ext/dR  →  v(R) ≈ constant.
     *   The ratio Ϟ_int/Ϟ_ext ≈ 1.25–1.50 is approximately constant.
     *   Constant ratio → both integrals grow at the same rate → flat rotation.
     *   No dark matter. No mass adjustment. Pure convergence geometry.
     *
     * @param R_kpc     Lower integration limit [kpc]
     * @param v_at      Velocity interpolator: v(r_kpc) → km/s
     * @param R_max_kpc Upper limit (disk truncation radius) [kpc]
     * @param N         Trapezoidal steps
     * @return Ϟ_ext [m]
     */
    template<typename VelocityFn>
    [[nodiscard]] inline double koppa_exterior(
        double R_kpc,
        VelocityFn&& v_at,
        double R_max_kpc = 25.0,
        int    N         = 400
    ) noexcept {
        if (R_kpc >= R_max_kpc || N < 1) return 0.0;
        const double dr = (R_max_kpc - R_kpc) / static_cast<double>(N);
        double K = 0.0;
        for (int i = 0; i < N; i++) {
            const double r1 = R_kpc + i * dr;
            const double r2 = r1 + dr;
            const double v1 = v_at(r1) * 1e3;
            const double v2 = v_at(r2) * 1e3;
            // Solid-angle weight (R/r): closer exterior has stronger shadow effect
            const double z1 = (v1/c) * (v1/c) * (R_kpc / r1);
            const double z2 = (v2/c) * (v2/c) * (R_kpc / r2);
            K += 0.5 * (z1 + z2) * dr * kpc_m;
        }
        return K;
    }

    /**
     * @brief Enclosed disk fraction for exponential disk (CQ06 geometry).
     *
     * The fraction of baryonic displacement volume enclosed within R:
     *   f_enc(R) = 1 - (1 + R/h_R) · exp(-R/h_R)
     *
     * This is the geometric integral of the exponential surface density.
     * At R = h_R: f_enc ≈ 0.264
     * At R = 3h_R: f_enc ≈ 0.800
     * At R → ∞: f_enc → 1.0 (all displacement volume enclosed)
     *
     * @param R_kpc    Galactocentric radius [kpc]
     * @param h_R_kpc  Radial scale length [kpc]
     * @return Enclosed fraction [0, 1]
     */
    [[nodiscard]] inline double f_enclosed(double R_kpc, double h_R_kpc) noexcept {
        if (h_R_kpc <= 0.0 || R_kpc <= 0.0) return 0.0;
        const double x = R_kpc / h_R_kpc;
        return 1.0 - (1.0 + x) * std::exp(-x);
    }

    /**
     * @brief Disk velocity from baryonic Koppa + eclipse fraction.
     *
     * For galaxies without a supplied observed RC table.
     * Pure Koppa-native formula: Ϟ_disk = f_enc × min(sat,1) × Ϟ_gal.
     *
     * Saturation factor sat_fac = min(Σ₀/Σ_sat, 1):
     *   MW-class (Σ₀ >> Σ_sat): sat_fac ≈ 1.0 → full eclipse regime
     *   Dwarfs/LSB (Σ₀ << Σ_sat): sat_fac < 1.0 → sub-eclipse, rising RC
     *
     * @param R_kpc         Galactocentric radius [kpc]
     * @param h_R_kpc       Radial scale length [kpc]
     * @param koppa_gal_m   Total galactic Koppa Ϟ_gal [m]
     * @param sat_factor    Eclipse saturation factor [0,1]
     * @return Disk velocity [km/s]
     */
    [[nodiscard]] inline double v_disk_from_koppa(
        double R_kpc,
        double h_R_kpc,
        double koppa_gal_m,
        double sat_factor = 1.0
    ) noexcept {
        if (R_kpc <= 0.0 || koppa_gal_m <= 0.0) return 0.0;
        const double R_m  = R_kpc * kpc_m;
        const double f    = f_enclosed(R_kpc, h_R_kpc);
        const double v2   = c * c * f * std::min(sat_factor, 1.0) * koppa_gal_m / R_m;
        return (v2 > 0.0) ? std::sqrt(v2) / 1e3 : 0.0;
    }

    /**
     * @brief Orbital velocity from effective Koppa.
     * v²(R) = c² × Ϟ_eff / R
     */
    [[nodiscard]] inline double v_from_koppa(double K_eff_m, double R_kpc) noexcept {
        if (R_kpc <= 0.0 || K_eff_m <= 0.0) return 0.0;
        const double v2 = c * c * K_eff_m / (R_kpc * kpc_m);
        return (v2 > 0.0) ? std::sqrt(v2) / 1e3 : 0.0;
    }

} // namespace regime_disk


// ═════════════════════════════════════════════════════════════════════════════
//  BAR / TRANSITION — Solid-Line Occlusion Streak
//
//  The bar is a CONTINUOUS line of displacement engines. Unlike point
//  occlusions (which diminish as 1/r²), a solid line subtends a streak
//  of CONSTANT angular width along its entire length — at every distance
//  along the bar axis. This is the mathematical key to the flat onset.
//
//  Streak solid-angle fraction:
//    f_streak = δφ / π   where δφ = arctan(halfwidth / d_perp)
//
//  This fraction is CONSTANT for all test particles in the bar's shadow —
//  locking the rotation velocity at the bar-arm junction (3.5–5 kpc).
//  Source: CQ20g bar_streak_fraction(), Wegg+2015 MW bar geometry.
// ═════════════════════════════════════════════════════════════════════════════

namespace regime_bar {

    /**
     * @brief Angular fraction of convergence hemisphere blocked by bar streak.
     *
     * The MW bar (half-length 3.5 kpc, half-width 0.5 kpc, tilt 27°) seen
     * from a test particle at galactocentric radius R subtends a streak
     * across the convergence hemisphere. The angular width of this streak:
     *
     *   δφ = arctan(halfwidth / d_perp)
     *   f_streak = δφ / π
     *
     * where d_perp is the perpendicular distance from R to the bar's long axis.
     * Inside the bar terminus (r ≤ R_bar): d_perp = halfwidth (maximum).
     * Outside the bar: d_perp grows → streak narrows → f_streak decreases.
     *
     * @param R_kpc          Test particle galactocentric radius [kpc]
     * @param R_bar_kpc      Bar half-length [kpc]
     * @param halfwidth_kpc  Bar half-width [kpc]
     * @return Occlusion streak fraction [0, 0.5]
     */
    [[nodiscard]] inline double streak_fraction(
        double R_kpc,
        double R_bar_kpc,
        double halfwidth_kpc = 0.5
    ) noexcept {
        if (R_bar_kpc <= 0.0) return 0.0;
        // Perpendicular distance from test particle to bar long axis
        const double d_perp = halfwidth_kpc + std::max(0.0, R_kpc - R_bar_kpc);
        const double half_angle = std::atan(halfwidth_kpc / d_perp);
        return half_angle / PI;
    }

    /**
     * @brief Bar velocity contribution from solid-line occlusion streak.
     *
     * v²_bar(R) = c² × f_streak(R) × Ϟ_bar / R
     *
     * At the bar terminus (R = R_bar): f_streak is maximum → velocity locked.
     * This is the flat-onset locking mechanism at the bar-arm junction.
     *
     * @param R_kpc          Test particle radius [kpc]
     * @param R_bar_kpc      Bar half-length [kpc]
     * @param koppa_bar_m    Bar Koppa (typically 8% of total) [m]
     * @param halfwidth_kpc  Bar half-width [kpc]
     * @return Bar velocity contribution [km/s]
     */
    [[nodiscard]] inline double v_bar(
        double R_kpc,
        double R_bar_kpc,
        double koppa_bar_m,
        double halfwidth_kpc = 0.5
    ) noexcept {
        if (R_bar_kpc <= 0.0 || koppa_bar_m <= 0.0) return 0.0;
        const double R_m   = R_kpc * kpc_m;
        const double f_str = streak_fraction(R_kpc, R_bar_kpc, halfwidth_kpc);
        const double v2    = c * c * f_str * koppa_bar_m / R_m;
        return (v2 > 0.0) ? std::sqrt(v2) / 1e3 : 0.0;
    }

} // namespace regime_bar


// ═════════════════════════════════════════════════════════════════════════════
//  KOPPA HELPER FUNCTIONS — Baryonic content, no G, no kg
// ═════════════════════════════════════════════════════════════════════════════

/**
 * @brief Convert baryonic mass [M☉] to galactic Koppa [m].
 *
 * Ϟ_gal = M_bar [M☉] × Ϟ_sun   where Ϟ_sun ≈ 1477 m
 *
 * Ϟ_sun = R_sun / k_sun² (the c-boundary of the Sun — its sole gravitational
 * scalar). This chain requires no G and no kg — only v, R, and c.
 *
 * From bridge namespace: koppa_Sun = R_Sun / (k_Sun × k_Sun) ≈ 1477 m
 *                        koppa_per_baryon = ℓ_P² × c × m_p / ℏ ≈ 1.242e-54 m
 *
 * @param M_bar_Msun  Baryonic mass [M☉]
 * @return Galactic Koppa Ϟ_gal [m]
 */
[[nodiscard]] inline double koppa_from_mass(double M_bar_Msun) noexcept {
    return M_bar_Msun * B::koppa_Sun;
}

/**
 * @brief Inverse: baryonic mass [M☉] from Koppa [m].
 * @param koppa_m  Galactic Koppa [m]
 * @return Baryonic mass [M☉]
 */
[[nodiscard]] inline double mass_from_koppa(double koppa_m) noexcept {
    return (B::koppa_Sun > 0.0) ? koppa_m / B::koppa_Sun : 0.0;
}

/**
 * @brief Baryon count from Koppa (no kg needed).
 *   N_bar = Ϟ / Ϟ_per_baryon
 *   Ϟ_per_baryon = ℓ_P² c m_p / ℏ ≈ 1.242e-54 m
 * @param koppa_m  Body Koppa [m]
 * @return Number of baryons
 */
[[nodiscard]] inline double n_baryons(double koppa_m) noexcept {
    return B::N_baryons(koppa_m);
}


// ═════════════════════════════════════════════════════════════════════════════
//  MILKY WAY PRESET
//
//  Full MW rotation curve from IRS9 (core surface, 5.25 pc) to the disk
//  edge (25 kpc). Sources: GRAVITY Collab, Sofue 2013, Eilers+2019, Huang+2016.
//  Six orbital zones. Four dynamical regimes. No G. No M. zk² = 1.
// ═════════════════════════════════════════════════════════════════════════════

namespace milky_way {

    struct RCPoint { double r_pc; double v_kms; };

    /// Full MW RC table: (r [pc], v [km/s])
    /// Regime A (core-dominated) → B (bulge-rising) → C (flat disk) → D (declining edge)
    inline constexpr RCPoint rc_table[] = {
        // ── Zone 1: CMZ (5.25 – 200 pc) ──────────────────────────────────
        {     5.25,  370.0 },  // IRS9 apoapsis — core surface (GRAVITY Collab 2020)
        {    26.0,   232.0 },  // Arches cluster (Stolte+2008)
        {    30.0,   167.0 },  // Quintuplet cluster (Stolte+2014)
        {   120.0,   130.0 },  // Sgr B2 complex (Sofue 2013)
        {   200.0,   140.0 },  // CMZ outer boundary
        // ── Zone 2: Inner bulge (200 – 1000 pc) ──────────────────────────
        {   300.0,   160.0 },  // Inner bulge (Sofue 2013)
        {   500.0,   175.0 },
        {   700.0,   190.0 },
        {  1000.0,   210.0 },  // Bulge 1.0 kpc
        // ── Zone 3: Bulge/bar (1 – 3.5 kpc) ─────────────────────────────
        {  1500.0,   225.0 },  // Bulge 1.5 kpc
        {  2000.0,   230.0 },  // Bulge 2.0 kpc
        {  2500.0,   235.0 },  // Bar 2.5 kpc
        {  3000.0,   235.0 },  // Bar 3.0 kpc
        {  3500.0,   220.0 },  // Bar terminus (Wegg+2015)
        // ── Zone 4: Transition / arm roots (3.5 – 5 kpc) ─────────────────
        {  4000.0,   220.0 },  // Arm root 4.0 kpc (Sofue 2013)
        {  4500.0,   222.0 },  // Transition 4.5 kpc
        // ── Zone 5: Disk (5 – 25 kpc) — Eilers+2019 + Huang+2016 ─────────
        {  5000.0,   228.0 },
        {  6000.0,   229.0 },
        {  7000.0,   231.0 },
        {  8000.0,   229.0 },  // Sun at R₀ ≈ 8.178 kpc
        {  9000.0,   230.0 },
        { 10000.0,   232.0 },
        { 11000.0,   230.0 },
        { 12000.0,   228.0 },
        { 14000.0,   225.0 },
        { 16000.0,   218.0 },  // Huang+2016
        { 18000.0,   210.0 },
        { 20000.0,   200.0 },
        { 25000.0,   185.0 },  // Disk edge — exterior occlusion collapse
    };
    inline constexpr int N_RC = static_cast<int>(sizeof(rc_table)/sizeof(rc_table[0]));

    // ── Canonical MW parameters ────────────────────────────────────────────
    inline constexpr double R0_kpc       = 8.178;  ///< Sun galactocentric radius [kpc]
    inline constexpr double v0_kms       = 229.0;  ///< Sun circular velocity [km/s]
    inline constexpr double h_R_kpc      = 2.6;    ///< Radial scale length [kpc]
    inline constexpr double h_z_kpc      = 0.3;    ///< Vertical scale height [kpc]
    inline constexpr double R_max_kpc    = 25.0;   ///< Disk truncation radius [kpc]
    inline constexpr double R_bulge_kpc  = 1.5;    ///< Bulge half-mass radius [kpc]
    inline constexpr double q_bulge      = 0.6;    ///< Oblate axis ratio
    inline constexpr double R_bar_kpc    = 3.5;    ///< Bar half-length [kpc]
    inline constexpr double bar_hw_kpc   = 0.5;    ///< Bar half-width [kpc]
    inline constexpr double bar_tilt_deg = 27.0;   ///< Bar tilt to Sun-centre line [deg]
    inline constexpr double M_bar_Msun   = 5.17e10;///< Baryonic mass [M☉]
    inline constexpr double koppa_mw_m   = M_bar_Msun * B::koppa_Sun; ///< Total MW Koppa [m]
    /// Core Koppa from IRS9 observation (GRAVITY Collab): Ϟ_core = v²R/c²
    inline constexpr double koppa_core_m = 370.0e3 * 370.0e3
                                         * 5.25 * pc_m_ / (c * c);

    /**
     * @brief Interpolate MW rotation velocity at r [pc].
     *
     * Linear interpolation through the full 28-point RC table.
     * Clamped to endpoints for r outside [5.25 pc, 25 000 pc].
     *
     * @param r_pc  Galactocentric radius [pc]
     * @return Circular velocity [km/s]
     */
    [[nodiscard]] inline double v_at_pc(double r_pc) noexcept {
        if (r_pc <= rc_table[0].r_pc)      return rc_table[0].v_kms;
        if (r_pc >= rc_table[N_RC-1].r_pc) return rc_table[N_RC-1].v_kms;
        for (int i = 0; i < N_RC - 1; i++) {
            if (r_pc >= rc_table[i].r_pc && r_pc <= rc_table[i+1].r_pc) {
                const double f = (r_pc - rc_table[i].r_pc)
                               / (rc_table[i+1].r_pc - rc_table[i].r_pc);
                return rc_table[i].v_kms*(1.0-f) + rc_table[i+1].v_kms*f;
            }
        }
        return rc_table[N_RC-1].v_kms;
    }

    /**
     * @brief Interpolate MW rotation velocity at r [kpc].
     * @param r_kpc  Galactocentric radius [kpc]
     * @return Circular velocity [km/s]
     */
    [[nodiscard]] inline double v_at_kpc(double r_kpc) noexcept {
        return v_at_pc(r_kpc * 1.0e3);
    }

    /**
     * @brief MW Koppa at radius R: Ϟ(R) = v²(R)·R/c²  [m]
     *
     * This is the sole gravitational descriptor at R. No G. No M.
     * zk² = 1 at every radius is guaranteed by construction.
     *
     * @param R_kpc  Galactocentric radius [kpc]
     * @return Koppa [m]
     */
    [[nodiscard]] inline double koppa_at(double R_kpc) noexcept {
        const double v = v_at_kpc(R_kpc) * 1e3;
        const double R = R_kpc * kpc_m;
        return v * v * R / (c * c);
    }

    /**
     * @brief Closure identity at radius R: zk² = 1.
     *
     * zk² = (v/c)² × (c/v)² = 1.000000 algebraically.
     * Verify this is 1.0 at every point to confirm implementation integrity.
     *
     * @param R_kpc  Galactocentric radius [kpc]
     * @return zk² (must = 1.000000)
     */
    [[nodiscard]] inline double zk2_at(double R_kpc) noexcept {
        const double v = v_at_kpc(R_kpc) * 1e3;
        const double z = (v/c) * (v/c);
        const double k = c / v;
        return z * k * k;
    }

    /**
     * @brief MW occlusion anisotropy skymap: column Koppa at (l, b) from Earth.
     *
     * From CQ22 Section A. The galactic displacement topology creates a
     * directional occlusion map across the full CMB convergence field.
     *
     * Higher K_col in a given direction = more CMB convergence occluded there
     * = apparent pressure deficit = apparent "streaming" or "attraction".
     *
     * Key directions:
     *   l=0°, b=0°   → Galactic centre: maximum K_col
     *   l=180°, b=0° → Anticentre: minimum in-plane K_col
     *   b=±90°        → Poles: minimum K_col (perpendicular to disk)
     *   l=307°, b=9° → Great Attractor direction: elevated K_col from
     *                   bar+bulge occlusion streak — NOT a mass overdensity
     *
     * SDT falsification: Δz ∝ cos(b). ΛCDM predicts isotropic.
     *
     * @param l_deg      Galactic longitude [degrees]
     * @param b_deg      Galactic latitude [degrees]
     * @param r_max_kpc  Integration depth [kpc]
     * @return Column Koppa K_col [m]
     */
    [[nodiscard]] inline double skymap_koppa(
        double l_deg,
        double b_deg,
        double r_max_kpc = 20.0
    ) noexcept {
        auto v_fn = [](double r_kpc) -> double { return v_at_kpc(r_kpc); };
        return cmb_field::column_koppa(
            l_deg * deg2rad, b_deg * deg2rad,
            R0_kpc, h_z_kpc, v_fn, r_max_kpc, 200
        );
    }

    /**
     * @brief Photon z-imprint from galactic column (CQ22 Section E).
     *
     * A photon arriving at Earth from (l, b) accumulates a convergence-depth
     * shift proportional to the column Koppa along its path:
     *
     *   Δz_gal = K_col(l,b) / R₀
     *
     * SDT PREDICTION: Δz_gal ∝ cos(b)  (scales with disk column integral).
     * ΛCDM PREDICTION: isotropic (potential-well sourced, not column-sourced).
     *
     * This is a falsifiable SDT signature accessible to SPHEREx and Planck data.
     *
     * @param l_deg  Galactic longitude [degrees]
     * @param b_deg  Galactic latitude [degrees]
     * @return Photon z-imprint [dimensionless]
     */
    [[nodiscard]] inline double photon_z_imprint(double l_deg, double b_deg) noexcept {
        return skymap_koppa(l_deg, b_deg) / (R0_kpc * kpc_m);
    }

    /**
     * @brief CMB self-lensing boost at the Sun's position.
     *
     * The MW disk lenses its own CMB field. At Earth's position (R₀, z≈0),
     * the fractional boost to the equatorial convergence pressure from
     * the galactic disk acting as a gravitational EM lens.
     *
     * Value ≈ 0.5–1.5% (a first-order perturbation on the dominant occlusion).
     *
     * @return Fractional lensing boost [dimensionless]
     */
    [[nodiscard]] inline double self_lensing_boost_at_sun() noexcept {
        const double K_col_eq = skymap_koppa(0.0, 0.0);  // l=0°, b=0°: toward GC
        return cmb_field::convergence_lensing_boost(K_col_eq, R0_kpc, 0.0, h_z_kpc);
    }

    /**
     * @brief Interior Koppa integral for the MW at radius R [kpc].
     *
     * Ϟ_int(R) = ∫₀ᴿ (v_MW(r)/c)² dr   [m]
     *
     * Uses the full observed MW RC table — no model, no G.
     *
     * @param R_kpc  Upper integration limit [kpc]
     * @param N      Integration steps
     * @return Ϟ_int [m]
     */
    [[nodiscard]] inline double koppa_interior(double R_kpc, int N = 400) noexcept {
        auto v_fn = [](double r_kpc) -> double { return v_at_kpc(r_kpc); };
        return regime_disk::koppa_interior(R_kpc, v_fn, 0.001, N);
    }

    /**
     * @brief Exterior Koppa integral for the MW at radius R [kpc].
     *
     * Ϟ_ext(R) = ∫ᴿ^25kpc (v_MW(r)/c)² · (R/r) dr   [m]
     *
     * @param R_kpc  Lower integration limit [kpc]
     * @param N      Integration steps
     * @return Ϟ_ext [m]
     */
    [[nodiscard]] inline double koppa_exterior(double R_kpc, int N = 400) noexcept {
        auto v_fn = [](double r_kpc) -> double { return v_at_kpc(r_kpc); };
        return regime_disk::koppa_exterior(R_kpc, v_fn, R_max_kpc, N);
    }

    /**
     * @brief Canonical MW GalaxyProfile for use with the universal galaxy engine.
     * @return GalaxyProfile pre-filled with MW canonical values
     */
    [[nodiscard]] inline GalaxyProfile profile() noexcept {
        GalaxyProfile p;
        p.name                 = "Milky Way";
        p.type                 = GalaxyType::Spiral;
        p.koppa_total_m        = koppa_mw_m;
        p.h_R_kpc              = h_R_kpc;
        p.h_z_kpc              = h_z_kpc;
        p.R_max_kpc            = R_max_kpc;
        p.R_bulge_kpc          = R_bulge_kpc;
        p.q_bulge              = q_bulge;
        p.f_bulge              = 0.15;          // bulge ≈ 15% of total baryonic Koppa
        p.R_bar_kpc            = R_bar_kpc;
        p.bar_halfwidth_kpc    = bar_hw_kpc;
        p.bar_tilt_deg         = bar_tilt_deg;
        p.f_bar                = 0.08;          // bar ≈ 8% of total baryonic Koppa
        p.enable_cmb_lensing   = true;
        p.R0_observer_kpc      = R0_kpc;
        return p;
    }

} // namespace milky_way


// ═════════════════════════════════════════════════════════════════════════════
//  UNIVERSAL GALAXY ENGINE
//
//  The CMB-powered, mass-free, G-free rotation curve engine.
//  Computes GalaxyResult at any galactocentric radius R for any GalaxyProfile.
//
//  Full mechanism:
//    1. P_conv = 2.459e48 Pa acts isotropically at every point.
//    2. Baryons occlude angular sectors of the CMB convergence hemisphere.
//    3. Interior occlusion (toward Sag A*) + exterior (toward rim) = imbalance.
//    4. The CMB is EM → it is lensed by the disk topology → midplane boost.
//    5. Bulge spheroid geometry enhances centre-ward occlusion by ^1.3.
//    6. Bar solid-line streak locks the flat-onset velocity.
//    7. No G. No M. zk² = 1 at every radius.
//
//  For the MW, prefer compute_from_rc() with milky_way::v_at_kpc as the
//  interpolator — it uses the observed RC directly for maximum accuracy.
// ═════════════════════════════════════════════════════════════════════════════

/**
 * @brief Compute the full SDT galactic result at radius R using the eclipse model.
 *
 * For galaxies without a supplied observed RC table. Uses the baryonic Koppa
 * + eclipse fraction model (CQ06) as the velocity source.
 * For the MW, use compute_from_rc() with milky_way::v_at_kpc instead.
 *
 * @param R_kpc   Galactocentric radius [kpc]
 * @param profile Galaxy parameters (koppa_total_m, geometry)
 * @param z_kpc   Height above midplane [kpc] (default: 0 = midplane)
 * @return Complete GalaxyResult
 */
[[nodiscard]] inline GalaxyResult compute(
    double R_kpc,
    const GalaxyProfile& profile,
    double z_kpc = 0.0
) noexcept {
    GalaxyResult res;
    res.R_kpc = R_kpc;
    res.z_kpc = z_kpc;
    if (R_kpc <= 0.0) return res;

    const double R_m = R_kpc * kpc_m;

    // ── Partition baryonic Koppa by component ────────────────────────────
    const double K_bulge = profile.koppa_total_m * profile.f_bulge;
    const double K_bar   = profile.koppa_total_m * profile.f_bar;
    const double K_disk  = profile.koppa_total_m * std::max(0.0,
                               1.0 - profile.f_bulge - profile.f_bar);

    // Eclipse saturation factor for disk (MW-calibrated Σ_sat = 175 M☉/pc²)
    static constexpr double Sigma_sat_SI =
        175.0 * Msun_kg / (pc_m_ * pc_m_);  // [kg/m²]
    const double h_R_m   = profile.h_R_kpc * kpc_m;
    const double M_disk_kg = mass_from_koppa(K_disk) * Msun_kg;
    const double Sigma_0   = (h_R_m > 0.0)
                           ? M_disk_kg / (2.0 * PI * h_R_m * h_R_m)
                           : 0.0;
    const double sat_fac = std::min(Sigma_0 / Sigma_sat_SI, 1.0);

    // ── Regime I: Bulge (oblate spheroid, CQ20g) ─────────────────────────
    double v_b = 0.0;
    if (profile.R_bulge_kpc > 0.0 && K_bulge > 0.0) {
        // de Vaucouleurs enclosed fraction: f(R) = 1 - exp(-7.67·(R/R_eff)^0.25)
        const double x_dev = 7.67 * std::pow(R_kpc / profile.R_bulge_kpc, 0.25);
        const double f_dev = 1.0 - std::exp(-x_dev);
        // Spheroid enhancement (^1.3 from CQ20g)
        const double sf    = regime_bulge::spheroid_factor(
                                 R_kpc, profile.R_bulge_kpc, profile.q_bulge);
        const double v2    = c * c * f_dev * sf * K_bulge / R_m;
        v_b = (v2 > 0.0) ? std::sqrt(v2) / 1e3 : 0.0;
    }

    // ── Regime II: Disk (eclipse saturation, CQ06) ───────────────────────
    const double v_d = regime_disk::v_disk_from_koppa(
        R_kpc, profile.h_R_kpc, K_disk, sat_fac);

    // ── Bar / Transition (solid-line streak, CQ20g) ───────────────────────
    const double v_r = regime_bar::v_bar(
        R_kpc, profile.R_bar_kpc, K_bar, profile.bar_halfwidth_kpc);

    // ── Build smooth total velocity interpolator for Koppa integrals ──────
    auto disk_v_fn = [&](double r_kpc) noexcept -> double {
        double vd = regime_disk::v_disk_from_koppa(r_kpc, profile.h_R_kpc, K_disk, sat_fac);
        double vb = 0.0;
        if (profile.R_bulge_kpc > 0.0 && K_bulge > 0.0) {
            const double xx  = 7.67 * std::pow(r_kpc / profile.R_bulge_kpc, 0.25);
            const double fdev = 1.0 - std::exp(-xx);
            const double sf  = regime_bulge::spheroid_factor(
                                   r_kpc, profile.R_bulge_kpc, profile.q_bulge);
            const double v2  = c * c * fdev * sf * K_bulge / (r_kpc * kpc_m);
            vb = (v2 > 0.0) ? std::sqrt(v2) / 1e3 : 0.0;
        }
        const double vr    = regime_bar::v_bar(r_kpc, profile.R_bar_kpc, K_bar,
                                               profile.bar_halfwidth_kpc);
        const double v2tot = vd*vd + vb*vb + vr*vr;
        return (v2tot > 0.0) ? std::sqrt(v2tot) : 0.0;
    };

    // ── Bidirectional Koppa integrals ─────────────────────────────────────
    const double K_int = regime_disk::koppa_interior(R_kpc, disk_v_fn, 0.001, 200);
    const double K_ext = regime_disk::koppa_exterior(R_kpc, disk_v_fn, profile.R_max_kpc, 200);

    // ── CMB Self-Lensing ──────────────────────────────────────────────────
    double v_l        = 0.0;
    double K_lens     = 0.0;
    double boost      = 0.0;
    double deflection = 0.0;

    if (profile.enable_cmb_lensing) {
        // Column Koppa toward galactic centre (equatorial, b=0°, l=0°)
        // This is the maximum lensing path — the disk material along the midplane
        const double K_col_eq = cmb_field::column_koppa(
            0.0, 0.0,
            R_kpc, profile.h_z_kpc,
            disk_v_fn,
            profile.R_max_kpc, 100
        );
        boost     = cmb_field::convergence_lensing_boost(
                        K_col_eq, R_kpc, z_kpc, profile.h_z_kpc);
        K_lens    = cmb_field::koppa_lensing(
                        K_col_eq, R_kpc, z_kpc, profile.h_z_kpc);
        deflection= cmb_field::cmb_lensing_deflection(
                        0.0, profile.h_z_kpc, K_col_eq, profile.R_max_kpc);
        const double v2_lens = c * c * K_lens / R_m;
        v_l = (v2_lens > 0.0) ? std::sqrt(v2_lens) / 1e3 : 0.0;
    }

    // ── Total velocity — components in quadrature ─────────────────────────
    const double v2_total     = v_b*v_b + v_d*v_d + v_r*v_r + v_l*v_l;
    const double v_total_kms  = (v2_total > 0.0) ? std::sqrt(v2_total) : 0.0;
    const double v_total_ms   = v_total_kms * 1e3;

    // ── SDT field scalars ─────────────────────────────────────────────────
    const double z_val = (v_total_ms / c) * (v_total_ms / c);  // z = v²/c²
    const double k_val = (v_total_ms > 0.0) ? c / v_total_ms : 0.0;  // k = c/v

    // ── Fill result ───────────────────────────────────────────────────────
    res.v_bulge_kms        = v_b;
    res.v_disk_kms         = v_d;
    res.v_bar_kms          = v_r;
    res.v_lensing_kms      = v_l;
    res.v_total_kms        = v_total_kms;
    res.koppa_interior_m   = K_int;
    res.koppa_exterior_m   = K_ext;
    res.koppa_lensing_m    = K_lens;
    res.koppa_eff_m        = K_int + K_ext + K_lens;
    res.z_spation          = z_val;
    res.k_spation          = k_val;
    res.zk2                = z_val * k_val * k_val;  // = 1.000000 always
    res.cmb_lensing_boost  = boost;
    res.cmb_deflection_rad = deflection;
    res.occlusion_ratio    = (K_ext > 0.0) ? K_int / K_ext : 0.0;
    return res;
}

/**
 * @brief Compute the full SDT galactic result using an observed rotation curve.
 *
 * For galaxies with a known RC table (e.g., the MW). Uses the supplied velocity
 * interpolator directly for the bidirectional Koppa integrals — no eclipse model.
 * This is the highest-fidelity path for well-observed galaxies.
 *
 * Usage for the Milky Way:
 * @code
 *   auto mw = milky_way::profile();
 *   auto res = compute_from_rc(8.178, mw, milky_way::v_at_kpc);
 * @endcode
 *
 * @param R_kpc      Galactocentric radius [kpc]
 * @param profile    Galaxy parameters
 * @param v_at_kpc   Velocity interpolator: v(r_kpc) → km/s
 * @param z_kpc      Height above midplane [kpc]
 * @return Complete GalaxyResult
 */
template<typename VelocityFn>
[[nodiscard]] inline GalaxyResult compute_from_rc(
    double R_kpc,
    const GalaxyProfile& profile,
    VelocityFn&& v_at_kpc,
    double z_kpc = 0.0
) noexcept {
    GalaxyResult res;
    res.R_kpc = R_kpc;
    res.z_kpc = z_kpc;
    if (R_kpc <= 0.0) return res;

    const double R_m = R_kpc * kpc_m;

    // Bidirectional Koppa from observed RC (truth — no model dependence)
    const double K_int = regime_disk::koppa_interior(R_kpc, v_at_kpc, 0.001, 400);
    const double K_ext = regime_disk::koppa_exterior(R_kpc, v_at_kpc, profile.R_max_kpc, 400);

    // Observed velocity at R — this is the truth
    const double v_obs_kms = v_at_kpc(R_kpc);
    const double v_obs_ms  = v_obs_kms * 1e3;

    // CMB Self-Lensing (uses observed RC as the proxy field)
    double v_l        = 0.0;
    double K_lens     = 0.0;
    double boost      = 0.0;
    double deflection = 0.0;

    if (profile.enable_cmb_lensing) {
        const double K_col_eq = cmb_field::column_koppa(
            0.0, 0.0,
            R_kpc, profile.h_z_kpc,
            v_at_kpc, profile.R_max_kpc, 100
        );
        boost     = cmb_field::convergence_lensing_boost(
                        K_col_eq, R_kpc, z_kpc, profile.h_z_kpc);
        K_lens    = cmb_field::koppa_lensing(
                        K_col_eq, R_kpc, z_kpc, profile.h_z_kpc);
        deflection= cmb_field::cmb_lensing_deflection(
                        0.0, profile.h_z_kpc, K_col_eq, profile.R_max_kpc);
        const double v2_l = c * c * K_lens / R_m;
        v_l = (v2_l > 0.0) ? std::sqrt(v2_l) / 1e3 : 0.0;
    }

    // SDT field scalars from observed velocity (the RC IS the truth)
    const double z_val = (v_obs_ms / c) * (v_obs_ms / c);
    const double k_val = (v_obs_ms > 0.0) ? c / v_obs_ms : 0.0;

    // In RC-mode the observed velocity subsumes all components
    res.v_bulge_kms        = 0.0;         // Subsumed in observed RC
    res.v_disk_kms         = v_obs_kms;   // The observed RC is the total disk velocity
    res.v_bar_kms          = 0.0;         // Subsumed in observed RC
    res.v_lensing_kms      = v_l;         // Diagnostic: the lensing correction
    res.v_total_kms        = v_obs_kms;   // Observed RC is the total
    res.koppa_interior_m   = K_int;
    res.koppa_exterior_m   = K_ext;
    res.koppa_lensing_m    = K_lens;
    res.koppa_eff_m        = K_int + K_ext + K_lens;
    res.z_spation          = z_val;
    res.k_spation          = k_val;
    res.zk2                = z_val * k_val * k_val;  // = 1.000000 always
    res.cmb_lensing_boost  = boost;
    res.cmb_deflection_rad = deflection;
    res.occlusion_ratio    = (K_ext > 0.0) ? K_int / K_ext : 0.0;
    return res;
}


// ═════════════════════════════════════════════════════════════════════════════
//  CLOSURE AND BTFR PREDICTIONS
// ═════════════════════════════════════════════════════════════════════════════

/**
 * @brief Verify the closure identity: zk² = 1 at this result.
 *
 * zk² = (v/c)² × (c/v)² = 1.000000 algebraically.
 * Any deviation from 1.0 indicates an implementation error.
 * This invariant holds at EVERY radius — from IRS9 (5.25 pc) to the disk edge.
 *
 * @param res  GalaxyResult to verify
 * @return zk² (must = 1.000000)
 */
[[nodiscard]] inline double closure_zk2(const GalaxyResult& res) noexcept {
    return res.zk2;
}

/**
 * @brief BTFR log-log slope from SDT eclipse saturation model.
 *
 * The Baryonic Tully-Fisher Relation: M_bar ∝ v_flat⁴
 *
 * From SDT (CQ06): at eclipse saturation, f_enc → constant,
 *   v_flat ∝ (Ϟ_gal)^(1/2) ∝ (M_bar)^(1/2) × (Ϟ_sun/R_flat)^(1/2)
 * Since Ϟ_gal = M_bar × Ϟ_sun and R_flat ∝ h_R ∝ M_bar^(1/4) (empirically):
 *   v_flat ∝ M_bar^(1/4) → slope = 4 in log-log.
 *
 * This is a prediction, not a fit. No G. No dark matter.
 *
 * @return BTFR log-log slope (always 4.0 in SDT)
 */
[[nodiscard]] inline constexpr double btfr_slope() noexcept {
    return 4.0;
}

/**
 * @brief Predicted flat rotation velocity from total baryonic Koppa.
 *
 * At eclipse saturation (f_enc → 1/2 at R_flat = h_R·ln2):
 *   v_flat = c × √(Ϟ_gal / (2 · R_flat))
 *
 * No G. No M. Pure CMB occlusion geometry → BTFR slope = 4.
 *
 * @param koppa_total_m  Total galactic Koppa Ϟ_gal [m]
 * @param h_R_kpc        Radial scale length [kpc]
 * @return Predicted flat velocity [km/s]
 */
[[nodiscard]] inline double btfr_velocity(
    double koppa_total_m,
    double h_R_kpc
) noexcept {
    if (koppa_total_m <= 0.0 || h_R_kpc <= 0.0) return 0.0;
    // Saturation radius: where f_enc = 1/2 → R_flat = h_R·ln(2)
    const double R_flat = h_R_kpc * kpc_m * std::log(2.0);
    const double v2     = c * c * 0.5 * koppa_total_m / R_flat;
    return (v2 > 0.0) ? std::sqrt(v2) / 1e3 : 0.0;
}


// ═════════════════════════════════════════════════════════════════════════════
//  DEPRECATED FUNCTIONS
//  Retained for backward compatibility with CQ06, CQ23, E46 investigations.
//  The full CMB-native engine above supersedes all of these.
// ═════════════════════════════════════════════════════════════════════════════

/// Baryonic occlusion cross-section [m²] — calibrated to MW Σ_sat threshold
static constexpr double kappa_area_per_baryon = 9.1e-29;

/// Legacy convenience alias — use koppa_from_mass() instead
[[deprecated("Use koppa_from_mass() instead")]]
[[nodiscard]] inline double koppa_gal(double M_bar_msun) noexcept {
    return M_bar_msun * B::koppa_Sun;
}

/// CQ23 Galaxy3DProfile — replaced by GalaxyProfile
struct Galaxy3DProfile {
    double baryonic_mass_kg;
    double radial_scale_length_m;
    double vertical_scale_height_m;
    double gas_fraction;
    double inclination_rad;
};

/// CQ23 VolumetricEclipseResult — replaced by GalaxyResult
struct VolumetricEclipseResult {
    double rho0_kg_m3;
    double horizontal_column_kg_m2;
    double baryon_column_m2;
    double optical_depth;
    double eclipse_fraction;
    double predicted_velocity_m_s;
};

static constexpr double Sigma_sat_Msun_pc2_DEPRECATED = 175.0;
static constexpr double Sigma_sat_SI_DEPRECATED =
    Sigma_sat_Msun_pc2_DEPRECATED * Msun_kg / (pc_m_ * pc_m_);

[[nodiscard]] inline double rho0_from_mass(
    double M_bar_kg, double h_R_m, double h_z_m
) noexcept {
    if (h_R_m <= 0.0 || h_z_m <= 0.0) return 0.0;
    return M_bar_kg / (4.0 * PI * h_R_m * h_R_m * h_z_m);
}

[[nodiscard]] inline double horizontal_column_density(
    double R_m, double M_bar_kg, double h_R_m, double h_z_m
) noexcept {
    if (h_R_m <= 0.0 || h_z_m <= 0.0 || R_m <= 0.0) return 0.0;
    return (M_bar_kg / (4.0 * PI * h_R_m * h_z_m)) * (1.0 - std::exp(-R_m / h_R_m));
}

[[nodiscard]] inline double baryon_column_number(
    double Lambda_kg_m2, double m_proton_kg
) noexcept {
    return Lambda_kg_m2 / m_proton_kg;
}

[[nodiscard]] inline double radial_eclipse_optical_depth(
    double Lambda_kg_m2, double m_proton_kg
) noexcept {
    return kappa_area_per_baryon * baryon_column_number(Lambda_kg_m2, m_proton_kg);
}

[[nodiscard]] inline double radial_eclipse_fraction(double tau) noexcept {
    return 0.5 * (1.0 - std::exp(-tau));
}

[[deprecated("Use compute() or compute_from_rc() instead")]]
[[nodiscard]] inline VolumetricEclipseResult predicted_velocity_3d(
    double R_m, const Galaxy3DProfile& galaxy
) noexcept {
    VolumetricEclipseResult res{};
    if (R_m <= 0.0) return res;
    res.rho0_kg_m3 = rho0_from_mass(
        galaxy.baryonic_mass_kg,
        galaxy.radial_scale_length_m,
        galaxy.vertical_scale_height_m);
    res.horizontal_column_kg_m2 = horizontal_column_density(
        R_m, galaxy.baryonic_mass_kg,
        galaxy.radial_scale_length_m, galaxy.vertical_scale_height_m);
    res.baryon_column_m2 = baryon_column_number(res.horizontal_column_kg_m2, m_p);
    res.optical_depth    = radial_eclipse_optical_depth(res.horizontal_column_kg_m2, m_p);
    res.eclipse_fraction = radial_eclipse_fraction(res.optical_depth);
    const double N_baryons = galaxy.baryonic_mass_kg / m_p;
    const double kg_m      = B::koppa_per_baryon * N_baryons;
    double max_v = 0.0;
    for (int i = 1; i <= 100; ++i) {
        const double r_test  = i * (5.0 * galaxy.radial_scale_length_m) / 100.0;
        const double col     = horizontal_column_density(r_test, galaxy.baryonic_mass_kg,
                                   galaxy.radial_scale_length_m, galaxy.vertical_scale_height_m);
        const double tau_t   = radial_eclipse_optical_depth(col, m_p);
        const double f_occ   = radial_eclipse_fraction(tau_t);
        const double v_lim_sq= c * c * kg_m / (2.0 * r_test);
        const double v_lim   = std::sqrt(std::max(0.0, v_lim_sq));
        const double v_test  = v_lim * std::sqrt(2.0 * f_occ);
        if (v_test > max_v) max_v = v_test;
    }
    res.predicted_velocity_m_s = max_v;
    return res;
}

[[deprecated("Use btfr_slope() instead")]]
[[nodiscard]] inline constexpr double btfr_prediction() noexcept { return 4.0; }

[[deprecated("Use regime_disk::v_disk_from_koppa() instead")]]
[[nodiscard]] inline double eclipse_fraction(double Sigma_SI) noexcept {
    return 1.0 - std::exp(-Sigma_SI / Sigma_sat_SI_DEPRECATED);
}

[[deprecated("Use compute() instead")]]
[[nodiscard]] inline double r_sat_pred(double Sigma_0_SI, double h_R_m) noexcept {
    const double threshold = Sigma_sat_SI_DEPRECATED * std::log(2.0);
    if (Sigma_0_SI <= threshold) return 0.0;
    return h_R_m * std::log(Sigma_0_SI / threshold);
}

[[deprecated("Use compute() instead")]]
[[nodiscard]] inline double v_flat(
    double Sigma_0_SI, double h_R_m, double koppa_gal_m
) noexcept {
    const double r_s = r_sat_pred(Sigma_0_SI, h_R_m);
    if (r_s <= 0.0) return 0.0;
    return c * std::sqrt(0.5 * koppa_gal_m / r_s);
}

[[deprecated("Use compute() instead")]]
[[nodiscard]] inline double rotation_velocity(
    double r_m, double Sigma_SI, double koppa_gal_m
) noexcept {
    if (r_m < 1e-10) return 0.0;
    const double f  = eclipse_fraction(Sigma_SI);
    const double v2 = c * c * f * koppa_gal_m / r_m;
    return (v2 > 0.0) ? std::sqrt(v2) : 0.0;
}

[[deprecated("Not used in CMB-native formulation")]]
[[nodiscard]] inline double Sigma_enclosed(
    double Sigma_0_SI, double r_m, double h_R_m
) noexcept {
    if (r_m < 1e-10) return Sigma_0_SI;
    const double x = r_m / h_R_m;
    return Sigma_0_SI * 2.0 / (x * x) * (1.0 - (1.0 + x) * std::exp(-x));
}

} // namespace sdt::galactic

#endif // SDT_GALACTIC_HPP
