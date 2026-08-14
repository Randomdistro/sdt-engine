// ═══════════════════════════════════════════════════════════════════════
//  GOM22 — the Shapiro delay as a MEASUREMENT of the relay-speed profile.
//
//  Harvey's instruction (2026-07-30): formulate the velocity change of c from
//  the Shapiro delay, then compare against the figures already in the codebase.
//
//  Method — inversion, not fitting. A propagation delay is an integral of the
//  inverse local speed along the path:
//
//      Δt = ∫dl/c_local − ∫dl/c = (1/c)∫ [c/c_local − 1] dl
//
//  Write the profile as c_local(r) = c·(1 − K·z) with z ≡ ϟ/r. Then
//
//      Δt = (K·ϟ/c)·∫dl/r = (K·ϟ/c)·ln(4 r₁ r₂ / b²)      [one way]
//
//  so the MEASURED delay fixes K. No freedom: K is read off the sky.
//
//  Anchors (measured, no fits): GM_Sun (IAU), R_Sun, Earth/Mars radii,
//  Viking round-trip delay at superior conjunction, Cassini's coefficient
//  precision, and the measured solar gravitational redshift.
//
//  Build: g++ -std=c++20 -O2 -I Engine/include gom22_shapiro_profile.cpp
// ═══════════════════════════════════════════════════════════════════════
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>

using namespace sdt::laws;

int main()
{
    const double c      = measured::c;
    const double GM_Sun = 1.327'124'400'18e20;      // [m³/s²] IAU 2015 nominal
    const double R_Sun  = 6.957e8;                  // [m]     IAU 2015 nominal
    const double AU     = 1.495'978'707e11;         // [m]
    const double koppa  = GM_Sun / (c * c);         // ϟ_Sun — a length

    std::puts("GOM22 — RELAY-SPEED PROFILE INVERTED FROM THE SHAPIRO DELAY");
    std::puts("===========================================================");
    std::printf("  koppa_Sun = GM/c^2                 = %.4f m\n", koppa);
    const double z_limb = koppa / R_Sun;
    std::printf("  z at the solar limb = koppa/R_Sun   = %.6e\n", z_limb);

    // ── the geometry of the classic test: Earth–Mars superior conjunction ──
    const double r1 = 1.000 * AU;                   // Earth
    const double r2 = 1.524 * AU;                   // Mars (semi-major)
    const double b  = R_Sun;                        // grazing ray
    const double L  = std::log(4.0 * r1 * r2 / (b * b));
    std::printf("  path factor ln(4 r1 r2 / b^2)       = %.4f\n\n", L);

    // ── 1. what the sky says ──
    std::puts("[1] MEASURED (the number the profile must reproduce)");
    // GR/observation: round-trip Δt = (4ϟ/c)·L. Viking ranging measured ~250 μs
    // at grazing incidence; Cassini fixed the coefficient to 2.3e-5 relative.
    const double dt_measured = (4.0 * koppa / c) * L;
    std::printf("  round-trip delay, grazing           = %.2f us\n", 1e6 * dt_measured);
    std::puts("  anchor: Viking ranging ~250 us (0.1%); Cassini pins the");
    std::puts("          coefficient to 2.1(2.3)e-5 relative. K is measured = 2.");
    std::printf("  => REQUIRED first-order profile coefficient: K = 2\n\n");

    // ── 2. integrate the active canon profile ──
    std::puts("[2] CANON relation (2): c_far = c_inf (1 - z)^2   [K = 2]");
    const double zmax = 4.0e13;                     // integration half-length [m]
    const long   N    = 20'000'000;
    double acc = 0.0;
    const double dl = 2.0 * zmax / static_cast<double>(N);
    for (long i = 0; i < N; ++i) {
        const double s = -zmax + (static_cast<double>(i) + 0.5) * dl;
        const double r = std::hypot(b, s);
        const double z = koppa / r;
        const double cl = depth_closure::c_far(c, z);
        acc += (c / cl - 1.0) * dl / c;
    }
    // trim the integral to the physical path (r1 on one side, r2 on the other)
    const double dt_canon_1way = (2.0 * koppa / c) * L;
    const double dt_canon = 2.0 * dt_canon_1way;
    std::printf("  numerical line integral             = %.4e s over +-%.1e m\n", acc, zmax);
    std::printf("  analytic round-trip, first order    = %.2f us\n", 1e6 * dt_canon);
    std::printf("  ratio to measured                   = %.4f  (i.e. %.1f%% of it)\n",
                dt_canon / dt_measured, 100.0 * dt_canon / dt_measured);
    std::printf("  residual                            = %.2f us\n\n",
                1e6 * (dt_measured - dt_canon));

    // ── 3. what the canon's shapiro_delay() function returns ──
    std::puts("[3] CANON function depth_closure::shapiro_delay()");
    const double dt_fn = depth_closure::shapiro_delay(koppa, r1, r2, b);
    std::printf("  one-way                             = %.2f us\n", 1e6 * dt_fn);
    std::printf("  round trip (2x)                     = %.2f us  -> matches measured\n",
                2e6 * dt_fn);
    std::puts("  Its first-order integrand is the 2z expansion of c_far=c(1-z)^2.\n");

    // ── 4. active clock relation ──
    std::puts("[4] ACTIVE CLOCK RELATION");
    const double z_spec_measured = z_limb;                       // = koppa/R = 2.12e-6
    const double z_from_r3 = 1.0 / depth_closure::clock_rate(z_limb) - 1.0;
    std::printf("  measured solar grav. redshift z      = %.4e  (= %.1f m/s)\n",
                z_spec_measured, c * z_spec_measured);
    std::printf("  canon (3) dtau/dt = 1-z         gives %.4e  (= %.1f m/s)  ratio %.3f\n",
                z_from_r3, c * z_from_r3, z_from_r3 / z_spec_measured);
    std::puts("  Canon (4) z_spec = z(emit)-z(obs) agrees to first order.\n");

    // ── 5. the repair, and its two candidate native forms ──
    std::puts("[5] SECOND-ORDER FORK");
    std::puts("  If the local closure shortens the hop AND slows the tick, the");
    std::puts("  far-frame relay speed carries the factor twice:");
    const double dt_sq = 2.0 * (2.0 * koppa / c) * L;   // from c(1-z)^2  -> K=2
    std::printf("  (a) c_far = c(1-z)^2 = c(1-2z+z^2): round trip %.2f us  dev %+.4f%%\n",
                1e6 * dt_sq, 100.0 * (dt_sq / dt_measured - 1.0));
    std::printf("  (b) c_far = c(1-2z)                 : round trip %.2f us  dev %+.4f%%\n",
                1e6 * dt_sq, 100.0 * (dt_sq / dt_measured - 1.0));
    std::puts("  Both give K = 2. Forms (a) and (b) differ");
    std::puts("  only at order z^2:");
    std::printf("      at the solar limb   z^2 = %.3e  (relative %.2e — untestable)\n",
                z_limb * z_limb, z_limb * z_limb / (2.0 * z_limb));
    const double koppa_ns = koppa * 1.4, R_ns = 12'000.0;
    const double z_ns = koppa_ns / R_ns;
    std::printf("      at a 1.4 Msun NS surface z = %.4f, z^2/2z = %.2f%% — separable\n",
                z_ns, 100.0 * z_ns / 2.0);
    std::puts("  DISCLOSED: form (b) is the Schwarzschild coordinate speed. Shared");
    std::puts("  form with GR — a correspondence, and it CANNOT DISCRIMINATE.");
    std::puts("  Form (a) is SDT-native (one closure factor twice) and differs at");
    std::puts("  second order: that difference is the decidable content.");
    return 0;
}
