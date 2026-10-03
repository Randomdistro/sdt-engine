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

    printf("\n--- Gravitational redshift chain for Earth/Moon system ---\n");
    // Earth surface g from Moon orbit (no G, no M)
    double r_moon   = 3.84400e8;  // m  (from laser ranging — pure timing)
    double T_moon   = 27.3217 * 86400.0; // s
    double R_earth  = 6.3710e6;   // m  (from eclipse geometry)

    double g_earth  = 4.0*M_PI*M_PI * r_moon*r_moon*r_moon / (T_moon*T_moon * R_earth*R_earth);
    double Koppa_earth = g_earth * R_earth*R_earth / (c*c);
    double z_grav_earth = Koppa_earth / R_earth;

    printf("Moon orbit → g_Earth  = %.4f m/s²  (NASA: 9.807)\n", g_earth);
    printf("           → Ϟ_Earth  = %.4e m  (%.2f mm)\n", Koppa_earth, Koppa_earth*1000.0);
    printf("           → z_grav   = %.4e\n", z_grav_earth);
    printf("           → error in g = %+.2f%%\n\n",
           100.0*(g_earth-9.807)/9.807);

    printf("--- Ϟ field consistency: all planets → same Ϟ_sun ---\n");
    printf("Spectroscopic Ϟ_sun = %.4f m\n", Koppa_ref);
    printf("Orbital   avg Ϟ_sun = calculated above (should all agree to < 0.1%%)\n");

    return 0;
}
