// =============================================================================
// CQ18a — Solar System Calibration
// Validates z_grav from orbital timing against spectroscopic z_grav
// Chain: T_orbit + r_orbit → Ϟ_star → z_grav_predicted vs z_grav_measured
// No G, No M.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#ifndef M_PI
  static constexpr double M_PI = 3.14159265358979323846;
#endif

static constexpr double c    = 2.99792458e8;   // m/s
static constexpr double AU   = 1.495978707e11; // m
static constexpr double R_sun= 6.957e8;        // m

// Solar gravitational redshift measured from spectral lines [Fe I]
static constexpr double z_grav_sun_measured = 2.12e-6;

// Solar radius from angular diameter at 1 AU (angular diameter = 0.5329 deg)
// R_sun = tan(0.5329/2 * pi/180) * 1 AU
static constexpr double R_sun_geom = 6.957e8; // m — agrees with above

// Orbital data for each planet (raw: period + semi-major axis from parallax geometry)
struct OrbitalData {
    const char* name;
    double r_AU;      // semi-major axis [AU]   — from parallax + angular baseline
    double T_days;    // orbital period [days]   — from timing
};

static const OrbitalData planets[] = {
    { "Mercury",  0.38710,   87.969 },
    { "Venus",    0.72333,  224.701 },
    { "Earth",    1.00000,  365.250 },
    { "Mars",     1.52366,  686.971 },
    { "Jupiter",  5.20336, 4332.589 },
    { "Saturn",   9.53707,10759.220 },
    { "Uranus",  19.19126,30688.500 },
    { "Neptune", 30.06896,60195.000 },
};

int main() {
    printf("=== CQ18a: Solar System Calibration — Ϟ_sun from Orbital Timing ===\n\n");
    printf("Sun spectroscopic z_grav (measured) = %.3e\n", z_grav_sun_measured);
    printf("Sun R_star (geometric) = %.4e m\n\n", R_sun_geom);

    // Ϟ_sun from spectroscopic z_grav
    double Koppa_sun_spectro = z_grav_sun_measured * R_sun_geom;
    printf("Ϟ_sun from spectroscopy:  %.4f m\n\n", Koppa_sun_spectro);

    printf("%-10s  %10s  %12s  %10s  %10s  %8s\n",
           "Planet", "r [AU]", "T [days]", "Ϟ_sun [m]", "Ref [m]", "Error");
    printf("%-10s  %10s  %12s  %10s  %10s  %8s\n",
           "--------", "------", "--------", "---------", "-------", "-----");

    double Koppa_ref = Koppa_sun_spectro;
    int n = sizeof(planets)/sizeof(planets[0]);
    for (int i = 0; i < n; i++) {
        const auto& p = planets[i];
        double r_m = p.r_AU * AU;
        double T_s = p.T_days * 86400.0;

        // SDT Kepler: Ϟ = 4π²r³ / (T²c²)
        double Koppa_orbital = 4.0 * M_PI * M_PI * r_m*r_m*r_m / (T_s*T_s * c*c);
        double err_pct = 100.0*(Koppa_orbital - Koppa_ref) / Koppa_ref;

        printf("%-10s  %10.5f  %12.3f  %10.4f  %10.4f  %+7.3f%%\n",
               p.name, p.r_AU, p.T_days, Koppa_orbital, Koppa_ref, err_pct);
    }

    printf("\n--- Ϟ_Earth: three independent derivations (no G, no M) ---\n\n");

    // Common Earth radius values
    double R_mean   = 6.3710e6;   // m — mean radius (eclipse geometry)
    double R_equat  = 6.3781e6;   // m — equatorial radius (GPS + geodesy)
    double R_polar  = 6.3568e6;   // m — polar radius (geodesy)

    // ── Method 1: Moon orbital period ─────────────────────────────────────
    double r_moon = 3.84400e8;          // m  (lunar laser ranging)
    double T_moon = 27.3217 * 86400.0;  // s  (sidereal period)
    double Koppa_moon = 4.0*M_PI*M_PI * r_moon*r_moon*r_moon / (T_moon*T_moon * c*c);
    double g_from_moon = Koppa_moon * c*c / (R_mean * R_mean);

    printf("  Method 1 — Moon orbital period (T=%.4f days, r=%.4e m):\n",
           T_moon/86400.0, r_moon);
    printf("    Ϟ_Earth = %.6e m\n", Koppa_moon);
    printf("    g_surface (at R_mean=6371 km) = %.4f m/s²\n", g_from_moon);
    printf("    Implied R for g=9.807:  %.2f km  (+%.1f km above equatorial)\n\n",
           sqrt(Koppa_moon*c*c/9.80665)/1000.0,
           sqrt(Koppa_moon*c*c/9.80665)/1000.0 - R_equat/1000.0);

    // ── Method 2: ISS orbital period (independent, much lower orbit) ──────
    // ISS: mean altitude 408 km, period 92.68 min — from public tracking data
    double r_ISS = R_mean + 4.08e5;     // m  (R_earth + 408 km altitude)
    double T_ISS = 92.68 * 60.0;        // s  (orbital period)
    double Koppa_ISS = 4.0*M_PI*M_PI * r_ISS*r_ISS*r_ISS / (T_ISS*T_ISS * c*c);
    double g_from_ISS = Koppa_ISS * c*c / (R_mean * R_mean);

    printf("  Method 2 — ISS orbital period (T=%.2f min, r=%.4e m):\n",
           T_ISS/60.0, r_ISS);
    printf("    Ϟ_Earth = %.6e m\n", Koppa_ISS);
    printf("    g_surface (at R_mean=6371 km) = %.4f m/s²\n", g_from_ISS);
    printf("    Ϟ agreement vs Moon method:  %+.4f%%\n\n",
           100.0*(Koppa_ISS - Koppa_moon)/Koppa_moon);

    // ── Method 3: Surface pendulum  Ϟ = g·R²/c²  ─────────────────────────
    // g = 9.80665 m/s² (SI definition of standard gravity — exact)
    // R_equat from geodesy (independent of orbital mechanics entirely)
    double g_std       = 9.80665;
    double Koppa_pend  = g_std * R_equat*R_equat / (c*c);
    double g_check     = Koppa_pend * c*c / (R_equat*R_equat);

    printf("  Method 3 — Surface pendulum  Ϟ = g·R²/c²  (g=9.80665, R=R_equat):\n");
    printf("    Ϟ_Earth = %.6e m\n", Koppa_pend);
    printf("    g_check (round-trip) = %.5f m/s²\n", g_check);
    printf("    Ϟ agreement vs Moon method:  %+.4f%%\n\n",
           100.0*(Koppa_pend - Koppa_moon)/Koppa_moon);

    // ── Convergence summary ───────────────────────────────────────────────
    double Koppa_earth_true = 3.986004418e14 / (c*c); // GM_E/c² for reference
    printf("  %-28s  %-14s  %-8s\n", "Method", "Ϟ_Earth [m]", "vs GM/c²");
    printf("  %-28s  %-14s  %-8s\n", "------", "-----------", "-------");
    printf("  %-28s  %.6e    %+.3f%%\n", "Moon orbit",        Koppa_moon,  100.0*(Koppa_moon -Koppa_earth_true)/Koppa_earth_true);
    printf("  %-28s  %.6e    %+.3f%%\n", "ISS orbit",         Koppa_ISS,   100.0*(Koppa_ISS  -Koppa_earth_true)/Koppa_earth_true);
    printf("  %-28s  %.6e    %+.3f%%\n", "Surface g (equat)", Koppa_pend,  100.0*(Koppa_pend -Koppa_earth_true)/Koppa_earth_true);
    printf("  %-28s  %.6e    %+.3f%%\n", "GM_E/c² (reference)",Koppa_earth_true, 0.0);
    printf("\n  All three methods derive Ϟ_Earth from different observables.\n");
    printf("  No G or M_Earth entered any calculation.\n");

    double z_grav_earth = Koppa_ISS / R_mean;
    printf("\n  z_grav_Earth (from ISS Ϟ, at mean surface) = %.4e\n", z_grav_earth);

    printf("\n--- Ϟ field consistency: all planets → same Ϟ_sun ---\n");
    printf("Spectroscopic Ϟ_sun = %.4f m\n", Koppa_ref);
    printf("Orbital   avg Ϟ_sun = calculated above (should all agree to < 0.1%%)\n");

    return 0;
}
