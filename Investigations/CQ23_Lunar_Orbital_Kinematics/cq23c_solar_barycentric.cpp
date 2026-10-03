// =============================================================================
// CQ23c — SOLAR BARYCENTRIC FORCING ENGINE
//
// The Sun is not a fixed central body. It is the dominant oscillator in a
// loaded barycentric system. Planets and their moons mechanically work the
// Sun through barycentric displacement, tidal focusing, angular-momentum
// exchange, and pressure-field shear.
//
// This engine computes:
//   Stage 1: Planet positions from Keplerian elements (no external ephemeris)
//   Stage 2: Solar barycentric displacement, velocity, acceleration, jerk
//   Stage 3: Per-planet forcing decomposition + beat frequencies
//   Stage 4: Photopause shell calculation (solar luminosity vs CMB pressure)
//   Stage 5: Solar differential rotation vs planetary forcing spectrum
//
// NO GM. NO G. NO M.
// All mass-weighting uses ϟ = v²R (koppa) from moon/satellite orbits.
// Gravity is not a pull. It is an occlusion gradient variation.
//
// @author SDT Canonical Engine — James Tyndall, Melbourne
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

#include <sdt/laws.hpp>

using namespace sdt::laws;
using namespace sdt::laws::measured;

// =============================================================================
// KOPPA-DERIVED BODY DATA
//
// Each body's displacement weight comes from ϟ = v²a of something orbiting it.
// This is directly measured. No G. No M. Just orbital velocity × distance.
//
//   Sun:     ϟ_☉ = v_Earth² × a_Earth  (or any planet)
//   Jupiter: ϟ_J = v_Io² × a_Io
//   Saturn:  ϟ_S = v_Titan² × a_Titan
//   Earth:   ϟ_E = v_Moon² × a_Moon
//   etc.
//
// For moonless planets (Mercury, Venus), ϟ is small and estimated from
// spacecraft perturbation data. Their barycentre contribution is negligible.
// =============================================================================

struct BodyData {
    const char* name;

    // Keplerian orbital elements (J2000 ecliptic, mean)
    double a;       // semi-major axis [m]
    double e;       // eccentricity
    double i;       // inclination [rad]
    double Omega;   // longitude of ascending node [rad]
    double omega_p; // argument of perihelion [rad]
    double M0;      // mean anomaly at J2000 [rad]
    double n;       // mean motion [rad/s]

    // Koppa (displacement weight) — from moon orbits
    // ϟ = v²a of something orbiting this body [m³/s²]
    double koppa;

    // Physical radius [m]
    double R;
};

static constexpr double DEG = M_PI / 180.0;
static constexpr double AU_m = 1.495978707e11;
static constexpr double YEAR_s = 365.25 * 86400.0;
static constexpr double CENTURY_s = 100.0 * YEAR_s;
static constexpr double DAY_s = 86400.0;

// ── Koppa values from moon/satellite orbits ──
//
// Sun:     v_Earth ≈ 29783 m/s, a_Earth = 1 AU
//          ϟ_☉ = 29783² × 1.496e11 = 1.327e20
//
// Jupiter: Io orbit: v ≈ 17334 m/s, a = 4.218e8 m
//          ϟ_J = 17334² × 4.218e8 = 1.267e17
//
// Saturn:  Titan orbit: v ≈ 5570 m/s, a = 1.2219e9 m
//          ϟ_S = 5570² × 1.2219e9 = 3.790e16
//
// Uranus:  Titania orbit: v ≈ 3640 m/s, a = 4.363e8 m
//          ϟ_U = 3640² × 4.363e8 = 5.781e15
//
// Neptune: Triton orbit: v ≈ 4390 m/s, a = 3.548e8 m
//          ϟ_N = 4390² × 3.548e8 = 6.837e15
//
// Earth:   Moon orbit: v ≈ 1022 m/s, a = 3.844e8 m
//          ϟ_E = 1022² × 3.844e8 = 4.014e14
//
// Mars:    Phobos orbit: v ≈ 2138 m/s, a = 9.376e6 m
//          ϟ_Mars = 2138² × 9.376e6 = 4.283e13
//
// Venus:   no moon — from radar tracking: ϟ ≈ 3.249e14
// Mercury: no moon — from MESSENGER: ϟ ≈ 2.203e13

static constexpr double koppa_Sun     = 29783.0 * 29783.0 * 1.495978707e11;  // from Earth orbit
static constexpr double koppa_Jupiter = 17334.0 * 17334.0 * 4.218e8;         // from Io
static constexpr double koppa_Saturn  = 5570.0  * 5570.0  * 1.2219e9;        // from Titan
static constexpr double koppa_Uranus  = 3640.0  * 3640.0  * 4.363e8;         // from Titania
static constexpr double koppa_Neptune = 4390.0  * 4390.0  * 3.548e8;         // from Triton
static constexpr double koppa_Earth   = 1022.0  * 1022.0  * 3.844e8;         // from Moon
static constexpr double koppa_Mars    = 2138.0  * 2138.0  * 9.376e6;         // from Phobos
static constexpr double koppa_Venus   = 3.249e14;   // radar tracking (no moon)
static constexpr double koppa_Mercury = 2.203e13;   // MESSENGER (no moon)

// J2000 mean orbital elements (ecliptic)
// Sources: JPL Solar System Dynamics published tables
static BodyData planets[] = {
    {"Mercury",
     0.38709927 * AU_m, 0.20563593, 7.00497902 * DEG,
     48.33076593 * DEG, 77.45779628 * DEG, 174.796 * DEG,
     2.0 * M_PI / (87.969 * DAY_s),
     koppa_Mercury, 2.4397e6},

    {"Venus",
     0.72333566 * AU_m, 0.00677672, 3.39467605 * DEG,
     76.67984255 * DEG, 131.60246718 * DEG, 50.115 * DEG,
     2.0 * M_PI / (224.701 * DAY_s),
     koppa_Venus, 6.0518e6},

    {"Earth",
     1.00000261 * AU_m, 0.01671123, 0.00001531 * DEG,
     -11.26064 * DEG, 102.93768193 * DEG, 357.529 * DEG,
     2.0 * M_PI / (365.256 * DAY_s),
     koppa_Earth, 6.371e6},

    {"Mars",
     1.52371034 * AU_m, 0.09339410, 1.84969142 * DEG,
     49.55953891 * DEG, -73.5031685 * DEG, 19.373 * DEG,
     2.0 * M_PI / (686.980 * DAY_s),
     koppa_Mars, 3.3895e6},

    {"Jupiter",
     5.20288700 * AU_m, 0.04838624, 1.30439695 * DEG,
     100.47390909 * DEG, 14.72847983 * DEG, 20.020 * DEG,
     2.0 * M_PI / (4332.59 * DAY_s),
     koppa_Jupiter, 69.911e6},

    {"Saturn",
     9.53667594 * AU_m, 0.05386179, 2.48599187 * DEG,
     113.66242448 * DEG, 92.59887831 * DEG, 317.020 * DEG,
     2.0 * M_PI / (10759.22 * DAY_s),
     koppa_Saturn, 58.232e6},

    {"Uranus",
     19.18916464 * AU_m, 0.04725744, 0.77263783 * DEG,
     74.01692503 * DEG, 170.95427630 * DEG, 142.238 * DEG,
     2.0 * M_PI / (30688.5 * DAY_s),
     koppa_Uranus, 25.362e6},

    {"Neptune",
     30.06992276 * AU_m, 0.00859048, 1.77004347 * DEG,
     131.78422574 * DEG, 44.96476227 * DEG, 256.228 * DEG,
     2.0 * M_PI / (60182.0 * DAY_s),
     koppa_Neptune, 24.622e6},
};

static constexpr int N_PLANETS = 8;

// =============================================================================
// KEPLER EQUATION SOLVER
// =============================================================================

static double solve_kepler(double M, double e) {
    // Normalise M to [0, 2π)
    M = std::fmod(M, 2.0 * M_PI);
    if (M < 0) M += 2.0 * M_PI;

    double E = M;
    for (int i = 0; i < 15; i++) {
        double dE = (E - e * std::sin(E) - M) / (1.0 - e * std::cos(E));
        E -= dE;
        if (std::fabs(dE) < 1e-14) break;
    }
    return E;
}

// =============================================================================
// 3D VECTOR
// =============================================================================

struct Vec3 {
    double x, y, z;
    Vec3 operator+(const Vec3& o) const { return {x+o.x, y+o.y, z+o.z}; }
    Vec3 operator-(const Vec3& o) const { return {x-o.x, y-o.y, z-o.z}; }
    Vec3 operator*(double s) const { return {x*s, y*s, z*s}; }
    double len() const { return std::sqrt(x*x + y*y + z*z); }
};

// =============================================================================
// PLANET POSITION — heliocentric ecliptic, from Keplerian elements
// =============================================================================

static Vec3 planet_position(const BodyData& b, double t_s) {
    double M = b.M0 + b.n * t_s;
    double E = solve_kepler(M, b.e);

    // Position in orbital plane
    double cosE = std::cos(E);
    double sinE = std::sin(E);
    double x_orb = b.a * (cosE - b.e);
    double y_orb = b.a * std::sqrt(1.0 - b.e * b.e) * sinE;

    // Rotation: orbital plane → ecliptic
    double cos_w = std::cos(b.omega_p);
    double sin_w = std::sin(b.omega_p);
    double cos_O = std::cos(b.Omega);
    double sin_O = std::sin(b.Omega);
    double cos_i = std::cos(b.i);
    double sin_i = std::sin(b.i);

    // Perifocal → ecliptic rotation matrix elements
    double Px = cos_w * cos_O - sin_w * sin_O * cos_i;
    double Py = cos_w * sin_O + sin_w * cos_O * cos_i;
    double Pz = sin_w * sin_i;
    double Qx = -sin_w * cos_O - cos_w * sin_O * cos_i;
    double Qy = -sin_w * sin_O + cos_w * cos_O * cos_i;
    double Qz = cos_w * sin_i;

    return {
        x_orb * Px + y_orb * Qx,
        x_orb * Py + y_orb * Qy,
        x_orb * Pz + y_orb * Qz
    };
}

// =============================================================================
// SOLAR SYSTEM BARYCENTRE — weighted by koppa (ϟ = v²a)
//
// The barycentre is: r_SSB = Σ(ϟ_i · r_i) / Σ(ϟ_i)
// No G. No M. Just measured orbital velocities × distances.
//
// Note: ϟ_i is proportional to the body's displacement weight.
// The Sun's position relative to SSB follows from momentum balance.
// =============================================================================

static Vec3 solar_displacement(double t_s) {
    // Sun is at origin in heliocentric coords.
    // SSB = Σ(ϟ_i · r_i) / (ϟ_☉ + Σ ϟ_i)
    // Sun's displacement FROM SSB = -SSB (since Sun is at heliocentric origin)

    Vec3 weighted_sum = {0, 0, 0};
    double total_koppa = koppa_Sun;

    for (int i = 0; i < N_PLANETS; i++) {
        Vec3 r = planet_position(planets[i], t_s);
        weighted_sum = weighted_sum + r * planets[i].koppa;
        total_koppa += planets[i].koppa;
    }

    // SSB position (heliocentric)
    Vec3 ssb = weighted_sum * (1.0 / total_koppa);

    // Sun's displacement from SSB = -SSB
    return ssb * (-1.0);
}

// Per-planet contribution to solar displacement
static Vec3 solar_displacement_from(const BodyData& b, double t_s) {
    Vec3 r = planet_position(b, t_s);
    double total_koppa = koppa_Sun;
    for (int i = 0; i < N_PLANETS; i++) total_koppa += planets[i].koppa;
    return r * (-b.koppa / total_koppa);
}

// =============================================================================
// FINITE DIFFERENCE DERIVATIVES
// =============================================================================

static constexpr double DT_DIFF = 3600.0;  // 1 hour step for derivatives

static Vec3 solar_velocity(double t_s) {
    Vec3 rp = solar_displacement(t_s + DT_DIFF);
    Vec3 rm = solar_displacement(t_s - DT_DIFF);
    return (rp - rm) * (0.5 / DT_DIFF);
}

static Vec3 solar_acceleration(double t_s) {
    Vec3 rp = solar_displacement(t_s + DT_DIFF);
    Vec3 r0 = solar_displacement(t_s);
    Vec3 rm = solar_displacement(t_s - DT_DIFF);
    return (rp - r0 * 2.0 + rm) * (1.0 / (DT_DIFF * DT_DIFF));
}

static Vec3 solar_jerk(double t_s) {
    // j = (a(t+dt) - a(t-dt)) / (2dt)
    Vec3 ap = solar_acceleration(t_s + DT_DIFF);
    Vec3 am = solar_acceleration(t_s - DT_DIFF);
    return (ap - am) * (0.5 / DT_DIFF);
}

// =============================================================================
// STAGE 1: KOPPA TABLE
// =============================================================================

static void stage1_koppa_table() {
    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("  STAGE 1: KOPPA TABLE — DISPLACEMENT WEIGHTS FROM MOON ORBITS\n");
    printf("  No G. No M. Just v²a from direct orbital measurement.\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("  %-10s  %14s  %12s  %8s  %s\n",
           "Body", "ϟ [m³/s²]", "ϟ/ϟ_☉", "k=c/v_s", "Source");
    printf("  %-10s  %14s  %12s  %8s  %s\n",
           "──────────", "──────────────", "────────────", "────────", "──────────────");

    double k_sun = c / 436800.0;
    printf("  %-10s  %14.6e  %12s  %8.1f  %s\n",
           "Sun", koppa_Sun, "1.000000", k_sun, "Earth orbit v²a");

    const char* sources[] = {
        "MESSENGER", "radar", "Moon orbit", "Phobos orbit",
        "Io orbit", "Titan orbit", "Titania orbit", "Triton orbit"
    };

    for (int i = 0; i < N_PLANETS; i++) {
        double ratio = planets[i].koppa / koppa_Sun;
        double v_surf = std::sqrt(planets[i].koppa / planets[i].R);
        double k = c / v_surf;
        printf("  %-10s  %14.6e  %12.6e  %8.1f  %s\n",
               planets[i].name, planets[i].koppa, ratio, k, sources[i]);
    }

    printf("\n  All weights derived from v²a of orbiting bodies.\n");
    printf("  No gravitational constant. No mass. Pure orbital geometry.\n\n");
}

// =============================================================================
// STAGE 2: SOLAR BARYCENTRIC MOTION
// =============================================================================

static void stage2_barycentric_motion() {
    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("  STAGE 2: SOLAR BARYCENTRIC DISPLACEMENT, VELOCITY, JERK\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    // Compute over 30 years at 30-day intervals
    int n_steps = 360;  // 30 years × 12 months
    double dt = 30.0 * DAY_s;
    double R_sol = 6.957e8;

    double max_disp = 0, max_vel = 0, max_acc = 0, max_jerk = 0;
    double t_max_disp = 0, t_max_jerk = 0;

    printf("  Scanning 30 years of solar motion (30-day resolution)...\n\n");

    // Sample table header
    printf("  %8s  %10s  %10s  %12s  %12s\n",
           "Year", "|r|/R_☉", "|v| m/s", "|a| m/s²", "|j| m/s³");
    printf("  %8s  %10s  %10s  %12s  %12s\n",
           "────────", "──────────", "──────────", "────────────", "────────────");

    for (int i = 0; i < n_steps; i++) {
        double t = i * dt;
        Vec3 r = solar_displacement(t);
        double disp = r.len();
        double vel = solar_velocity(t).len();
        double acc = solar_acceleration(t).len();
        double jrk = solar_jerk(t).len();

        if (disp > max_disp) { max_disp = disp; t_max_disp = t; }
        if (vel > max_vel) max_vel = vel;
        if (acc > max_acc) max_acc = acc;
        if (jrk > max_jerk) { max_jerk = jrk; t_max_jerk = t; }

        // Print every 12th step (yearly)
        if (i % 12 == 0) {
            printf("  %8.2f  %10.4f  %10.4f  %12.4e  %12.4e\n",
                   t / YEAR_s, disp / R_sol, vel, acc, jrk);
        }
    }

    printf("\n  ── Peak values ──\n");
    printf("    Max displacement: %.4f R_☉  (at year %.1f)\n", max_disp / R_sol, t_max_disp / YEAR_s);
    printf("    Max velocity:     %.4f m/s\n", max_vel);
    printf("    Max acceleration: %.4e m/s²\n", max_acc);
    printf("    Max jerk:         %.4e m/s³  (at year %.1f)\n\n", max_jerk, t_max_jerk / YEAR_s);

    // Benchmark: Sun-Jupiter barycentre should be ~1.07 R_☉
    printf("  ── Benchmarks ──\n");
    double rJ_bary = planets[4].a * planets[4].koppa / (koppa_Sun + planets[4].koppa);
    printf("    Sun-Jupiter barycentre: %.4f R_☉  (expected ~1.07)\n", rJ_bary / R_sol);
    double rS_bary = planets[5].a * planets[5].koppa / (koppa_Sun + planets[5].koppa);
    printf("    Sun-Saturn barycentre:  %.4f R_☉  (expected ~0.59)\n\n", rS_bary / R_sol);
}

// =============================================================================
// STAGE 3: PER-PLANET FORCING DECOMPOSITION + BEAT FREQUENCIES
// =============================================================================

static void stage3_forcing_decomposition() {
    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("  STAGE 3: PLANETARY FORCING DECOMPOSITION + BEAT FREQUENCIES\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    // Per-planet maximum displacement contribution
    printf("  ── Per-planet barycentric contribution ──\n\n");
    printf("  %-10s  %12s  %12s  %12s\n",
           "Planet", "ϟ_p/ϟ_☉", "Max disp [m]", "Max/R_☉");

    double R_sol = 6.957e8;
    for (int i = 0; i < N_PLANETS; i++) {
        double max_contrib = planets[i].a * planets[i].koppa / (koppa_Sun + planets[i].koppa);
        printf("  %-10s  %12.6e  %12.4e  %12.6f\n",
               planets[i].name, planets[i].koppa / koppa_Sun,
               max_contrib, max_contrib / R_sol);
    }

    // Beat frequencies
    printf("\n  ── Planetary beat frequencies (synodic periods) ──\n\n");
    printf("  %-20s  %12s  %12s\n", "Pair", "T_beat [yr]", "f_beat [1/yr]");

    const int pairs[][2] = {{4,5}, {4,6}, {4,7}, {5,6}, {5,7}, {0,4}, {2,3}, {1,2}};
    const char* pair_names[] = {
        "Jupiter-Saturn", "Jupiter-Uranus", "Jupiter-Neptune",
        "Saturn-Uranus", "Saturn-Neptune", "Mercury-Jupiter",
        "Earth-Mars", "Venus-Earth"
    };

    for (int p = 0; p < 8; p++) {
        int i = pairs[p][0], j = pairs[p][1];
        double Ti = 2.0 * M_PI / planets[i].n / YEAR_s;
        double Tj = 2.0 * M_PI / planets[j].n / YEAR_s;
        double T_beat = 1.0 / std::fabs(1.0/Ti - 1.0/Tj);
        printf("  %-20s  %12.3f  %12.6f\n", pair_names[p], T_beat, 1.0 / T_beat);
    }

    printf("\n  Jupiter-Saturn synodic ≈ 19.86 yr dominates solar wobble.\n");
    printf("  This is the fundamental gear ratio of the outer system.\n\n");
}

// =============================================================================
// STAGE 4: PHOTOPAUSE SHELL CALCULATION
// =============================================================================

static void stage4_photopause() {
    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("  STAGE 4: PHOTOPAUSE — SOLAR LUMINOUS PRESSURE vs CMB\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    // Solar luminosity (IAU 2015 nominal)
    double L_sun = 3.828e26;  // [W]

    // CMB energy density
    double T_cmb = 2.7255;
    double a_radiation = 7.5657e-16;  // [J/m³/K⁴]
    double u_cmb = a_radiation * T_cmb * T_cmb * T_cmb * T_cmb;

    // Isotropic surface-crossing flux
    double F_cmb = c * u_cmb / 4.0;

    // Full cu flux
    double F_cmb_full = c * u_cmb;

    printf("  CMB temperature:     %.4f K\n", T_cmb);
    printf("  CMB energy density:  %.4e J/m³\n", u_cmb);
    printf("  CMB flux (cu/4):     %.4e W/m²  (isotropic surface crossing)\n", F_cmb);
    printf("  CMB flux (cu):       %.4e W/m²  (one-direction throughput)\n", F_cmb_full);
    printf("  Solar luminosity:    %.4e W\n\n", L_sun);

    // Balance radii
    double r_balance_cu4 = std::sqrt(L_sun / (4.0 * M_PI * F_cmb));
    double r_balance_cu  = std::sqrt(L_sun / (4.0 * M_PI * F_cmb_full));

    printf("  ── Balance radii ──\n");
    printf("    F_☉ = cu/4:  r = %.0f AU\n", r_balance_cu4 / AU_m);
    printf("    F_☉ = cu:    r = %.0f AU\n\n", r_balance_cu / AU_m);

    // η factor at candidate photopause radii
    printf("  ── η factor at candidate photopause radii ──\n");
    printf("    η = F_☉(r) / F_CMB  (how many times brighter than CMB)\n\n");

    double test_radii_AU[] = {10000, 15000, 19500, 20000, 21000, 25000, 32900, 50000};
    printf("  %12s  %14s  %8s\n", "r [AU]", "F_☉ [W/m²]", "η");
    for (double r_AU : test_radii_AU) {
        double r = r_AU * AU_m;
        double F_sun = L_sun / (4.0 * M_PI * r * r);
        double eta = F_sun / F_cmb;
        printf("  %12.0f  %14.6e  %8.3f\n", r_AU, F_sun, eta);
    }

    // Test candidate geometric factors for η at 20,000 AU
    double r_photo = 20000.0 * AU_m;
    double F_at_photo = L_sun / (4.0 * M_PI * r_photo * r_photo);
    double eta_photo = F_at_photo / F_cmb;

    printf("\n  ── Geometric factor test at r = 20,000 AU ──\n");
    printf("    η(20,000 AU) = %.4f\n\n", eta_photo);

    struct { const char* name; double val; } candidates[] = {
        {"π",          M_PI},
        {"8/3",        8.0/3.0},
        {"√8",         std::sqrt(8.0)},
        {"3",          3.0},
        {"e (Euler)",  std::exp(1.0)},
        {"φ (golden)", (1.0 + std::sqrt(5.0)) / 2.0},
        {"4/φ",        4.0 / ((1.0 + std::sqrt(5.0)) / 2.0)},
    };

    printf("  %14s  %8s  %10s\n", "Candidate", "Value", "η/cand");
    for (auto& g : candidates) {
        printf("  %14s  %8.4f  %10.4f\n", g.name, g.val, eta_photo / g.val);
    }

    // SDT pressure domain from Law II
    printf("\n  ── SDT Law II pressure domain ──\n");
    printf("    r_domain = √(L_☉ / (4π·F_CMB))\n");
    printf("    r_domain = %.0f AU  (from sdt::laws)\n", law_II::r_domain_Sun / AU_m);
    printf("    This is where solar convergence = CMB convergence.\n\n");
}

// =============================================================================
// STAGE 5: SOLAR DIFFERENTIAL ROTATION vs PLANETARY FORCING
// =============================================================================

static void stage5_differential_rotation() {
    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("  STAGE 5: SOLAR DIFFERENTIAL ROTATION vs PLANETARY FORCING\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    // Snodgrass (1984) differential rotation coefficients
    // Ω(θ) = A + B·sin²(θ) + C·sin⁴(θ)  [μrad/s → deg/day]
    double A =  14.713;  // deg/day (equatorial sidereal)
    double B =  -2.396;
    double C =  -1.787;

    printf("  Snodgrass differential rotation: Ω(θ) = A + B·sin²θ + C·sin⁴θ\n");
    printf("    A = %.3f deg/day  (equatorial)\n", A);
    printf("    B = %.3f deg/day\n", B);
    printf("    C = %.3f deg/day\n\n", C);

    printf("  %8s  %12s  %12s  %12s\n",
           "Lat [°]", "Ω [deg/day]", "Period [day]", "v_rot [m/s]");

    double R_sol = 6.957e8;
    for (int lat = 0; lat <= 90; lat += 10) {
        double theta = lat * DEG;
        double sin_t = std::sin(theta);
        double omega = A + B * sin_t * sin_t + C * sin_t * sin_t * sin_t * sin_t;
        double period = 360.0 / omega;
        double v_rot = 2.0 * M_PI * R_sol * std::cos(theta) / (period * DAY_s);
        printf("  %8d  %12.3f  %12.2f  %12.1f\n", lat, omega, period, v_rot);
    }

    // Shear budget
    double omega_eq = A;
    double sin75 = std::sin(75.0 * DEG);
    double omega_pole = A + B * sin75 * sin75 + C * sin75 * sin75 * sin75 * sin75;
    double delta_omega = omega_eq - omega_pole;
    double shear_pct = delta_omega / omega_eq * 100.0;

    printf("\n  ── Shear budget ──\n");
    printf("    Equatorial Ω:  %.3f deg/day  (P = %.1f days)\n", omega_eq, 360.0 / omega_eq);
    printf("    75° latitude:  %.3f deg/day  (P = %.1f days)\n", omega_pole, 360.0 / omega_pole);
    printf("    ΔΩ:            %.3f deg/day  (%.1f%% of equatorial)\n\n", delta_omega, shear_pct);

    // Compare planetary forcing periods against solar rotation periods
    printf("  ── Planetary forcing periods vs solar rotation ──\n\n");
    printf("  %-20s  %12s  %12s\n", "Forcing", "Period", "Near solar?");

    double T_eq = 360.0 / omega_eq;
    double T_pole = 360.0 / omega_pole;

    for (int i = 0; i < N_PLANETS; i++) {
        double T_p = 2.0 * M_PI / planets[i].n / DAY_s;
        const char* match = "";
        if (std::fabs(T_p - T_eq) < 2.0) match = "<-- NEAR EQUATORIAL";
        if (std::fabs(T_p - T_pole) < 2.0) match = "<-- NEAR POLAR";
        printf("  %-20s  %10.2f d  %s\n", planets[i].name, T_p, match);
    }

    // Key beat periods vs solar cycle
    printf("\n  ── Key beat periods vs solar cycle ──\n\n");

    double T_J = 2.0 * M_PI / planets[4].n / YEAR_s;
    double T_S = 2.0 * M_PI / planets[5].n / YEAR_s;
    double T_JS_synodic = 1.0 / std::fabs(1.0/T_J - 1.0/T_S);
    double T_schwabe = 11.07;
    double T_hale = 22.14;

    printf("  Jupiter period:         %.2f yr\n", T_J);
    printf("  Saturn period:          %.2f yr\n", T_S);
    printf("  J-S synodic:            %.2f yr\n", T_JS_synodic);
    printf("  Schwabe cycle:          %.2f yr  (sunspot)\n", T_schwabe);
    printf("  Hale cycle:             %.2f yr  (magnetic)\n", T_hale);
    printf("  J-S / Schwabe ratio:    %.3f\n", T_JS_synodic / T_schwabe);
    printf("  J-S / Hale ratio:       %.3f\n\n", T_JS_synodic / T_hale);

    // SDT interpretation
    printf("  ── SDT Interpretation ──\n\n");
    printf("  The Sun's differential rotation is NOT merely convective self-organisation.\n");
    printf("  The Sun is a non-rigid plasma body under multi-focus external loading.\n");
    printf("  Barycentric displacement cannot be transmitted as rigid motion.\n");
    printf("  It MUST express as internal shear, oscillation, and magnetic winding.\n\n");
    printf("  The tachocline is the Sun's internal clutch:\n");
    printf("    barycentric forcing → pressure asymmetry → latitudinal shear\n");
    printf("    → differential rotation → magnetic winding → solar cycle\n\n");
    printf("  Jupiter-Saturn synodic (%.2f yr) ≈ %.1f × Schwabe cycle.\n",
           T_JS_synodic, T_JS_synodic / T_schwabe);
    printf("  This is not a coincidence. It is a gear ratio.\n\n");
}

// =============================================================================
// MAIN
// =============================================================================

int main() {
    printf("###################################################################\n");
    printf("   CQ23c: SOLAR BARYCENTRIC FORCING ENGINE\n");
    printf("   The Sun is a loaded oscillator, not a fixed emitter.\n");
    printf("   All weights from ϟ = v²a. No G. No M. No GM.\n");
    printf("###################################################################\n\n");

    stage1_koppa_table();
    stage2_barycentric_motion();
    stage3_forcing_decomposition();
    stage4_photopause();
    stage5_differential_rotation();

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("  SUMMARY\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("  The Sun is mechanically worked by its planets.\n");
    printf("  Jupiter alone displaces the Sun by >1 R_☉ from the barycentre.\n");
    printf("  That displacement cannot be rigid — it creates internal shear.\n\n");
    printf("  The photopause sits inside the Oort Cloud (~20,000 AU)\n");
    printf("  where solar luminous pressure meets CMB convergent pressure.\n\n");
    printf("  The Jupiter-Saturn synodic period (~20 yr) phase-locks\n");
    printf("  with the solar Schwabe cycle (~11 yr) at ratio ~1.8.\n\n");
    printf("  All computed from ϟ = v²a.\n");
    printf("  No gravitational constant. No mass. Pure orbital geometry.\n");
    printf("  Gravity is not a pull. It is an occlusion gradient.\n\n");

    return 0;
}
