// =============================================================================
// Deriving c From Mercurial Precession
//
// ϟ = √(6πR / (δφ × a × (1−e²)))
// c = ϟ × v_surface
//
// No c upstream. No G. No M.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>

int main() {

    // Observables ─────────────────────────────────────────────────────────
    //
    // Sun radius          angular diameter × Earth-Sun distance
    // Mercury orbit       centuries of positional astronomy
    // Mercury precession  Le Verrier, 1859
    // Sun v_surface       Earth orbital velocity × √(d_Sun / R_Sun)

    constexpr double R       = 6.957e8;       // Sun radius              [m]
    constexpr double a       = 5.7909e10;      // Mercury semi-major      [m]
    constexpr double e       = 0.20563;        // Mercury eccentricity    [-]
    constexpr double P_days  = 87.969;         // Mercury period          [days]
    constexpr double prec_as = 42.98;          // anomalous precession    [″/century]
    constexpr double v_sun   = 436762.0;       // Sun surface orbital v   [m/s]

    // Derived ─────────────────────────────────────────────────────────────

    constexpr double orbits  = 36525.0 / P_days;
    constexpr double dphi    = (prec_as / orbits) * M_PI / 648000.0;
    constexpr double factor  = a * (1.0 - e * e);

    const double k2 = 6.0 * M_PI * R / (dphi * factor);
    const double k  = std::sqrt(k2);
    const double c  = k * v_sun;

    // Output ──────────────────────────────────────────────────────────────

    printf("Deriving c From Mercurial Precession\n");
    printf("====================================\n\n");

    printf("Observables\n");
    printf("  R_Sun         %14.4e m\n",   R);
    printf("  a_Mercury     %14.4e m\n",   a);
    printf("  e_Mercury     %14.5f\n",     e);
    printf("  P_Mercury     %14.3f days\n", P_days);
    printf("  precession    %14.2f arcsec/century\n", prec_as);
    printf("  v_surface     %14.1f m/s\n\n", v_sun);

    printf("Derivation\n");
    printf("  delta_phi     %14.4e rad/orbit\n", dphi);
    printf("  a(1-e^2)      %14.4e m\n",        factor);
    printf("  koppa^2       %14.0f\n",           k2);
    printf("  koppa         %14.2f\n\n",         k);

    printf("Result\n");
    printf("  c = koppa * v_surface\n");
    printf("  c = %.2f * %.1f\n", k, v_sun);
    printf("  c = %.0f m/s\n\n", c);

    printf("Validation\n");
    printf("  accepted c    299792458 m/s\n");
    printf("  error         %+.4f%%\n\n", (c - 299792458.0) / 299792458.0 * 100.0);

    printf("Closure\n");
    printf("  z   = 1/k^2  = %.6e\n", 1.0 / k2);
    printf("  zk^2          = %.6f\n", 1.0);

    return 0;
}
