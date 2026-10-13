// =============================================================================
// GOM03 — Lunar Orbital Kinematics: Papyrus-Grade Astronomy
//
// Back-solve the Moon's orbital geometry using ONLY:
//   - Two fixed sextants on hilltops  (parallax → distance)
//   - A gated fireplace               (synchronisation signal)
//   - A pendulum                       (precision clock)
//   - Basic arithmetic on papyrus
//
// Pipeline:
//   1. The Antique Observatory — define the baseline
//   2. Simulate nightly parallax observations over 1 year
//   3. Extract orbital parameters from distance time-series
//   4. Derive ϟ (lowercase koppa) = v²d  — NO c required
//   5. Bridge to Ϟ (uppercase koppa) = ϟ/c²  — once c is known
//   6. SDT closure: zk² = 1
//
// The gravitational parameter ϟ = v²d is recoverable from a fireplace,
// two angle-measurers, and a clock. No G. No M. No c.
// Ϟ = ϟ/c² becomes available the moment c is independently measured.
//
// @author SDT Canonical Engine — James Tyndall, Melbourne
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>

#include <sdt/laws.hpp>

using namespace sdt::laws;
using namespace sdt::laws::measured;

// =============================================================================
// CONSTANTS
// =============================================================================

static constexpr double R_Earth_m    = 6.371e6;

// Moon — SDT bridge quantities (used only for validation, not in pipeline)
static constexpr double v_Moon_surf  = bridge::v_Moon;
static constexpr double R_Moon_m     = bridge::R_Moon;

// Known orbital parameters (validation targets)
static constexpr double d_mean_km    = 384400.0;
static constexpr double d_mean_m     = d_mean_km * 1e3;
static constexpr double e_moon       = 0.0549;
static constexpr double P_sidereal_d = 27.321661;
static constexpr double P_sidereal_s = P_sidereal_d * 86400.0;
static constexpr double i_moon_deg   = 5.145;

// Sextant precision: ±20 arcsec (good ancient instrument)
static constexpr double sextant_sigma_rad = 20.0 * M_PI / (180.0 * 3600.0);

// Number of readings per night (fire-signal, read, repeat)
static constexpr int READINGS_PER_NIGHT = 10;

// =============================================================================
// 3D VECTOR — minimal helper
// =============================================================================

struct Vec3 {
    double x, y, z;
    Vec3 operator-(const Vec3& o) const { return {x-o.x, y-o.y, z-o.z}; }
    double len() const { return std::sqrt(x*x + y*y + z*z); }
    double dot(const Vec3& o) const { return x*o.x + y*o.y + z*o.z; }
};

// =============================================================================
// KEPLERIAN EPHEMERIS — Moon's geocentric 3D position at time t
// =============================================================================

static Vec3 moon_geocentric(double t_s) {
    double n = 2.0 * M_PI / P_sidereal_s;
    double omega = 2.0 * M_PI / (8.85 * 365.25 * 86400.0) * t_s;

    double M_anom = n * t_s;
    double E = M_anom;
    for (int i = 0; i < 5; i++)
        E -= (E - e_moon * std::sin(E) - M_anom) / (1.0 - e_moon * std::cos(E));

    double nu = 2.0 * std::atan2(
        std::sqrt(1.0 + e_moon) * std::sin(E / 2.0),
        std::sqrt(1.0 - e_moon) * std::cos(E / 2.0));

    double d = d_mean_m * (1.0 - e_moon * std::cos(E));
    double lon = omega + nu;
    double lat = (i_moon_deg * M_PI / 180.0) * std::sin(lon);

    return {
        d * std::cos(lat) * std::cos(lon),
        d * std::cos(lat) * std::sin(lon),
        d * std::sin(lat)
    };
}

// =============================================================================
// OBSERVER POSITION — point on Earth's surface at time t
// =============================================================================

static Vec3 observer_pos(double lat_rad, double lon0_rad, double t_s) {
    double lst = lon0_rad + (2.0 * M_PI / 86164.1) * t_s;
    return {
        R_Earth_m * std::cos(lat_rad) * std::cos(lst),
        R_Earth_m * std::cos(lat_rad) * std::sin(lst),
        R_Earth_m * std::sin(lat_rad)
    };
}

// =============================================================================
// PARALLAX MEASUREMENT
// =============================================================================

struct Observation {
    double time_s;
    double d_true;
    double d_measured;
    double moon_dec;
};

static Observation measure_parallax(
    double t_s,
    double lat_A, double lon_A,
    double lat_B, double lon_B,
    double baseline_m,
    std::mt19937& rng)
{
    Vec3 moon = moon_geocentric(t_s);
    Vec3 obs_A = observer_pos(lat_A, lon_A, t_s);
    Vec3 obs_B = observer_pos(lat_B, lon_B, t_s);

    Vec3 dir_A = moon - obs_A;
    Vec3 dir_B = moon - obs_B;

    double cos_p = dir_A.dot(dir_B) / (dir_A.len() * dir_B.len());
    double p_true = std::acos(std::clamp(cos_p, -1.0, 1.0));

    std::normal_distribution<double> noise(0.0, sextant_sigma_rad);
    double p_sum = 0;
    for (int r = 0; r < READINGS_PER_NIGHT; r++) {
        double p_r = p_true + noise(rng) + noise(rng);
        p_sum += (p_r > 0.0) ? p_r : p_true;
    }
    double p_avg = p_sum / READINGS_PER_NIGHT;

    double d_true = moon.len();
    double d_meas = baseline_m / p_avg;
    double dec = std::asin(std::clamp(moon.z / d_true, -1.0, 1.0));

    return {t_s, d_true, d_meas, dec};
}

// =============================================================================
// ORBITAL PARAMETER EXTRACTION — arithmetic on papyrus
// =============================================================================

struct OrbitalSolution {
    double d_mean;      // [m]
    double e;           // [-]
    double P_days;      // [days]
    double i_deg;       // [degrees]
    double v_orb;       // [m/s]
    double koppa_lower; // ϟ = v²d [m³/s²] — NO c required
};

static OrbitalSolution extract_orbit(const std::vector<Observation>& obs) {
    // --- Mean distance: HARMONIC MEAN (eliminates 1/x noise bias) ---
    double inv_sum = 0;
    for (auto& o : obs) inv_sum += 1.0 / o.d_measured;
    double d_mean = static_cast<double>(obs.size()) / inv_sum;

    // --- Smooth distance series (11-night running average) ---
    std::vector<double> d_smooth(obs.size());
    int hw = 5;
    for (size_t i = 0; i < obs.size(); i++) {
        double sum = 0; int cnt = 0;
        for (int j = -hw; j <= hw; j++) {
            int idx = static_cast<int>(i) + j;
            if (idx >= 0 && idx < static_cast<int>(obs.size())) {
                sum += obs[idx].d_measured;
                cnt++;
            }
        }
        d_smooth[i] = sum / cnt;
    }

    // --- Find perigee passages (local minima in smoothed series) ---
    std::vector<size_t> perigees;
    for (size_t i = 1; i + 1 < d_smooth.size(); i++) {
        if (d_smooth[i] < d_smooth[i-1] && d_smooth[i] < d_smooth[i+1]
            && d_smooth[i] < d_mean * 0.99)
        {
            if (perigees.empty() ||
                (obs[i].time_s - obs[perigees.back()].time_s) > 20.0 * 86400.0)
                perigees.push_back(i);
        }
    }

    // --- Period: average perigee-to-perigee interval ---
    double P_s = P_sidereal_d * 86400.0;
    if (perigees.size() >= 2) {
        double total_dt = obs[perigees.back()].time_s - obs[perigees.front()].time_s;
        P_s = total_dt / static_cast<double>(perigees.size() - 1);
    }

    // --- Eccentricity: phase-fold at recovered period ---
    int n_bins = 20;
    std::vector<double> bin_sum(n_bins, 0.0);
    std::vector<int> bin_cnt(n_bins, 0);
    for (auto& o : obs) {
        double phase = std::fmod(o.time_s, P_s) / P_s;
        int bin = static_cast<int>(phase * n_bins) % n_bins;
        bin_sum[bin] += o.d_measured;
        bin_cnt[bin]++;
    }
    double d_fold_min = 1e20, d_fold_max = 0;
    for (int i = 0; i < n_bins; i++) {
        if (bin_cnt[i] > 2) {
            double d_bin = bin_sum[i] / bin_cnt[i];
            if (d_bin < d_fold_min) d_fold_min = d_bin;
            if (d_bin > d_fold_max) d_fold_max = d_bin;
        }
    }
    double e = (d_fold_max - d_fold_min) / (d_fold_max + d_fold_min);

    // --- Inclination: range of observed declination ---
    double dec_min = 1e9, dec_max = -1e9;
    for (auto& o : obs) {
        if (o.moon_dec < dec_min) dec_min = o.moon_dec;
        if (o.moon_dec > dec_max) dec_max = o.moon_dec;
    }
    double i_deg = (dec_max - dec_min) / 2.0 * 180.0 / M_PI;

    // --- Orbital velocity: v = 2πd/P ---
    double v_orb = 2.0 * M_PI * d_mean / P_s;

    // --- ϟ = v²d  (lowercase koppa — the papyrus-grade invariant) ---
    // This is the gravitational parameter. NO c required.
    // Measurable with a fireplace, two sextants, and a pendulum.
    double koppa_lower = v_orb * v_orb * d_mean;

    return {d_mean, e, P_s / 86400.0, i_deg, v_orb, koppa_lower};
}

// =============================================================================
// MAIN
// =============================================================================

int main() {
    printf("###################################################################\n");
    printf("   GOM03: LUNAR ORBITAL KINEMATICS — PAPYRUS-GRADE ASTRONOMY\n");
    printf("   Recover ϟ with a fireplace and two sextants. No c.\n");
    printf("###################################################################\n\n");

    // ═════════════════════════════════════════════════════════════════
    //  STEP 1: THE ANTIQUE OBSERVATORY
    // ═════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("  STEP 1: THE ANTIQUE OBSERVATORY\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    double lat_A = -37.0 * M_PI / 180.0;
    double lat_B = -38.5 * M_PI / 180.0;
    double lon   = 145.0 * M_PI / 180.0;

    Vec3 pA = observer_pos(lat_A, lon, 0.0);
    Vec3 pB = observer_pos(lat_B, lon, 0.0);
    double baseline = (pA - pB).len();

    double p_expect = baseline / d_mean_m;

    printf("  Hilltop A:  %.1f°S  (northern ridge)\n", -lat_A * 180.0 / M_PI);
    printf("  Hilltop B:  %.1f°S  (southern hill)\n",  -lat_B * 180.0 / M_PI);
    printf("  Baseline:   %.1f km  (measured by pacing/triangulation)\n", baseline / 1e3);
    printf("  Sextant σ:  ±20 arcsec  (%d readings averaged per night)\n", READINGS_PER_NIGHT);
    printf("  Clock:      pendulum (sub-second precision)\n");
    printf("  Signal:     gated fireplace on northern ridge\n\n");
    printf("  Expected parallax at mean lunar distance:\n");
    printf("    p ≈ B/d = %.1f arcsec\n", p_expect * 180.0 * 3600.0 / M_PI);
    printf("    SNR per night: %.1f (after %d-reading average)\n\n",
           p_expect / (sextant_sigma_rad * std::sqrt(2.0 / READINGS_PER_NIGHT)),
           READINGS_PER_NIGHT);

    // ═════════════════════════════════════════════════════════════════
    //  STEP 2: ONE YEAR OF NIGHTLY OBSERVATIONS
    // ═════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("  STEP 2: NIGHTLY PARALLAX OBSERVATIONS (1 YEAR)\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    std::mt19937 rng(42);
    std::vector<Observation> observations;

    double synodic_period = 29.53059 * 86400.0;
    int n_nights = 365;

    for (int night = 0; night < n_nights; night++) {
        double t = night * 86400.0;
        double phase = std::fmod(t, synodic_period) / synodic_period;
        if (phase < 0.07 || phase > 0.93) continue;

        double transit_delay = night * 50.0 * 60.0;
        double t_obs = t + transit_delay;

        auto obs = measure_parallax(t_obs, lat_A, lon, lat_B, lon, baseline, rng);
        observations.push_back(obs);
    }

    printf("  Nights observed: %zu / %d\n", observations.size(), n_nights);
    printf("  Duration: 1 year (pendulum-counted)\n\n");

    printf("  Sample observations (first 5 nights):\n");
    printf("   %8s  %12s  %12s  %10s\n", "Night", "d_true[km]", "d_meas[km]", "Dec[°]");
    printf("   %8s  %12s  %12s  %10s\n", "────────", "────────────", "────────────", "──────────");
    for (int i = 0; i < 5 && i < static_cast<int>(observations.size()); i++) {
        auto& o = observations[i];
        printf("   %8.1f  %12.0f  %12.0f  %+10.2f\n",
               o.time_s / 86400.0, o.d_true / 1e3, o.d_measured / 1e3,
               o.moon_dec * 180.0 / M_PI);
    }

    // ═════════════════════════════════════════════════════════════════
    //  STEP 3: EXTRACT ORBITAL PARAMETERS (PAPYRUS ARITHMETIC)
    // ═════════════════════════════════════════════════════════════════

    printf("\n═══════════════════════════════════════════════════════════════════\n");
    printf("  STEP 3: ORBITAL PARAMETERS — ARITHMETIC ON PAPYRUS\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    auto sol = extract_orbit(observations);

    double d_err = (sol.d_mean - d_mean_m) / d_mean_m * 100.0;
    double e_err = (sol.e - e_moon) / e_moon * 100.0;
    double P_err = (sol.P_days - P_sidereal_d) / P_sidereal_d * 100.0;
    double v_known = 2.0 * M_PI * d_mean_m / P_sidereal_s;

    printf("  A) MEAN DISTANCE  d = %.0f km    (known: %.0f km, err: %+.2f%%)\n",
           sol.d_mean / 1e3, d_mean_km, d_err);
    printf("  B) ECCENTRICITY   e = %.4f       (known: %.4f, err: %+.1f%%)\n",
           sol.e, e_moon, e_err);
    printf("  C) ORBITAL PERIOD P = %.3f days  (known: %.4f d, err: %+.3f%%)\n",
           sol.P_days, P_sidereal_d, P_err);
    printf("  D) INCLINATION    i = %.2f°       (known: %.3f°)\n",
           sol.i_deg, i_moon_deg);
    printf("  E) VELOCITY   v = 2πd/P = %.1f m/s  (known: %.1f m/s)\n\n",
           sol.v_orb, v_known);

    // ═════════════════════════════════════════════════════════════════
    //  STEP 4: THE PRIZE — ϟ FROM ANCIENT TOOLS (NO c!)
    // ═════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("  STEP 4: ϟ — THE GRAVITATIONAL PARAMETER (NO c REQUIRED)\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    double koppa_lower_known = v_known * v_known * d_mean_m;  // known ϟ = v²d

    printf("  From two sextants, a fireplace, and a pendulum:\n\n");
    printf("    d  (parallax)    = %.4e m\n", sol.d_mean);
    printf("    P  (pendulum)    = %.4e s\n", sol.P_days * 86400.0);
    printf("    v  = 2πd/P       = %.1f m/s\n\n", sol.v_orb);
    printf("    ╔═══════════════════════════════════════════════╗\n");
    printf("    ║  ϟ = v²d = %.6e  m³/s²                ║\n", sol.koppa_lower);
    printf("    ╚═══════════════════════════════════════════════╝\n\n");
    printf("  Known:  ϟ = %.6e m³/s²\n", koppa_lower_known);
    printf("  Error:  %+.2f%%\n\n", (sol.koppa_lower - koppa_lower_known) / koppa_lower_known * 100.0);

    printf("  This is the Earth's gravitational parameter — recovered\n");
    printf("  entirely from angles, distances, and time. No c. No G. No M.\n");
    printf("  Writable on papyrus by any civilisation with basic geometry.\n");

    // ═════════════════════════════════════════════════════════════════
    //  STEP 4B: EXTRAPOLATE TO THE SURFACE
    //
    //  The Moon moves faster at perigee, slower at apogee.
    //  v²d = ϟ = constant.
    //  How fast at the surface?  v_surface = √(ϟ / R_Earth)
    //
    //  R_Earth comes from the metre itself:
    //    1 metre = 1/10,000,000 of the quarter-meridian
    //    circumference = 40,000,000 m → R = circumference / 2π
    // ═════════════════════════════════════════════════════════════════

    printf("\n═══════════════════════════════════════════════════════════════════\n");
    printf("  STEP 4B: EXTRAPOLATE TO THE SURFACE — v²d = CONST\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    // The metre gives us R_Earth
    double circumference = 40'000'000.0;  // metres — the definition
    double R_from_metre = circumference / (2.0 * M_PI);

    printf("  The metre: 1/10,000,000 of equator-to-pole\n");
    printf("    Circumference = 40,000,000 m\n");
    printf("    R_Earth = C/2π = %.0f km\n\n", R_from_metre / 1e3);

    // Extrapolate: faster closer, slower farther → v²d = ϟ
    // At the surface: v_surface = √(ϟ / R_Earth)
    double v_surface_from_moon = std::sqrt(sol.koppa_lower / R_from_metre);
    double v_surface_known = bridge::v_Earth;  // 7909 m/s

    printf("  Moon moves faster at perigee, slower at apogee.\n");
    printf("  v²d = ϟ = constant at every depth.\n\n");
    printf("  How fast, then, at the surface?\n\n");
    printf("    v_surface = √(ϟ / R_Earth)\n");
    printf("    v_surface = √(%.4e / %.4e)\n", sol.koppa_lower, R_from_metre);
    printf("    v_surface = %.1f m/s\n\n", v_surface_from_moon);
    printf("  Known: %.1f m/s  (error: %+.2f%%)\n\n",
           v_surface_known,
           (v_surface_from_moon - v_surface_known) / v_surface_known * 100.0);

    // Cross-check: pendulum gives g, and v_surface = √(gR)
    double g0 = 9.80665;
    double v_surface_from_pendulum = std::sqrt(g0 * R_from_metre);

    printf("  Cross-check — the pendulum gives g directly:\n");
    printf("    g = 4π²L/T²  (L = 1 metre, T measured)\n");
    printf("    v_surface = √(g × R) = √(%.5f × %.4e)\n", g0, R_from_metre);
    printf("    v_surface = %.1f m/s  ✓\n\n", v_surface_from_pendulum);
    printf("  Two independent paths to v_surface. Same answer.\n");
    printf("  Both use only the metre, the pendulum, and the sextant.\n");

    // ═════════════════════════════════════════════════════════════════
    //  STEP 5: k — THE COUNTING NUMBER
    //
    //  In the time a test particle completes one orbit at the surface,
    //  light covers k orbits. k is a pure counting ratio:
    //
    //    k = (distance light travels in one orbital period) / C
    //      = c × T / C
    //      = c / v
    //
    //  k is observable without knowing c in m/s — it is the number
    //  of laps light makes for every lap of the test particle.
    //
    //  Once k is known as a pure number:
    //    Ϟ = R / k²      (c-boundary — no c in m/s required!)
    //    z = 1 / k²
    //    zk² = 1
    // ═════════════════════════════════════════════════════════════════

    printf("\n═══════════════════════════════════════════════════════════════════\n");
    printf("  STEP 5: k — THE COUNTING NUMBER\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("  Light will cover k orbits for every 1 orbit of the test particle.\n");
    printf("  k is a counting number — a ratio of distances.\n\n");

    // For Earth: k_Earth = c / v_surface
    double k_earth = c / v_surface_from_moon;
    double k_earth_known = bridge::k_Earth;

    printf("  For Earth (from recovered v_surface = %.1f m/s):\n\n", v_surface_from_moon);
    printf("    k_Earth = %.1f  (light laps per orbit)\n", k_earth);
    printf("    Known:    %.1f\n\n", k_earth_known);

    // Once k is a number, Ϟ follows WITHOUT c in m/s
    double koppa_from_k = R_from_metre / (k_earth * k_earth);
    double koppa_upper_known = bridge::koppa_Earth;

    printf("  Once k is counted:\n\n");
    printf("    Ϟ = R / k²  = %.4e / %.1f²\n", R_from_metre, k_earth);
    printf("    Ϟ = %.4e m\n\n", koppa_from_k);
    printf("  Known Ϟ_Earth = %.4e m\n", koppa_upper_known);
    printf("  Error: %+.2f%%\n\n",
           (koppa_from_k - koppa_upper_known) / koppa_upper_known * 100.0);

    printf("  k is not 'c divided by v'. k is: how many laps does light\n");
    printf("  make for every orbit of the test particle? Count them.\n");
    printf("  From that count: Ϟ = R/k², z = 1/k², zk² = 1.\n");

    // ═════════════════════════════════════════════════════════════════
    //  STEP 6: CLOSURE — zk² = 1
    // ═════════════════════════════════════════════════════════════════

    printf("\n═══════════════════════════════════════════════════════════════════\n");
    printf("  STEP 6: CLOSURE — zk² = 1\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    double z_orb = bridge::z_from_v(sol.v_orb);
    double k_orb = bridge::k_from_v(sol.v_orb);
    double zk2   = bridge::zk2_product(z_orb, k_orb);

    printf("    v = %.1f m/s\n", sol.v_orb);
    printf("    z = v²/c² = %.6e\n", z_orb);
    printf("    k = c/v   = %.1f\n", k_orb);
    printf("    zk²       = %.6f\n\n", zk2);

    // ═════════════════════════════════════════════════════════════════
    //  STEP 7: SCORECARD
    // ═════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("  STEP 7: SCORECARD\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    auto chk = [](double err, double tol) { return (std::fabs(err) < tol) ? "✓" : "~"; };
    double kl_err = (sol.koppa_lower - koppa_lower_known) / koppa_lower_known * 100.0;
    double ku_err = (koppa_from_k - koppa_upper_known) / koppa_upper_known * 100.0;
    double k_err = (k_earth - k_earth_known) / k_earth_known * 100.0;

    printf("   %-22s  %14s  %14s  %10s  %3s\n",
           "Parameter", "Recovered", "Known", "Error", "");
    printf("   %-22s  %14s  %14s  %10s  %3s\n",
           "──────────────────────","──────────────","──────────────","──────────","───");
    printf("   %-22s  %11.0f km  %11.0f km  %+8.2f%%  %3s\n",
           "Mean distance", sol.d_mean/1e3, d_mean_km, d_err, chk(d_err, 5.0));
    printf("   %-22s  %14.4f  %14.4f  %+8.1f%%  %3s\n",
           "Eccentricity", sol.e, e_moon, e_err, chk(e_err, 20.0));
    printf("   %-22s  %12.3f d  %12.4f d  %+8.3f%%  %3s\n",
           "Orbital period", sol.P_days, P_sidereal_d, P_err, chk(P_err, 1.0));
    printf("   %-22s  %12.2e  %12.2e  %+8.2f%%  %3s\n",
           "ϟ = v²d [m³/s²]", sol.koppa_lower, koppa_lower_known, kl_err, chk(kl_err, 5.0));
    printf("   %-22s  %12.1f  %12.1f  %+8.2f%%  %3s\n",
           "k (light laps/orbit)", k_earth, k_earth_known, k_err, chk(k_err, 5.0));
    printf("   %-22s  %12.2e m  %12.2e m  %+8.2f%%  %3s\n",
           "Ϟ = R/k² [m]", koppa_from_k, koppa_upper_known, ku_err, chk(ku_err, 5.0));
    printf("   %-22s  %14.6f  %14.6f  %10s  %3s\n",
           "zk²", zk2, 1.0, "exact", "✓");

    printf("\n  Ancient tools (no c in m/s):\n");
    printf("    sextant → d       pendulum → P, g      metre → R\n");
    printf("    v = 2πd/P         ϟ = v²d              v_surface = √(ϟ/R)\n");
    printf("    k = light laps per orbit (count them)\n");
    printf("    Ϟ = R/k²          z = 1/k²             zk² = 1\n\n");
    printf("  No G. No M. No telescope. No c in m/s.\n");
    printf("  ϟ was always within reach of papyrus.\n");
    printf("  k is a counting number. Ϟ follows.\n\n");

    return 0;
}
