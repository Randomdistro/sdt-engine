// =============================================================================
// CQ20f — Proton Trefoil: Differential Sinusoidal Toroidal Rotation
//
// The 6π trefoil knot on the proton torus:
//   - 3 toroidal winds × 2 poloidal winds = 6 crossing events
//   - 6 crossings + 6 apices per complete circuit
//   - Under superluminal deformation: apices/crossings become PHASE-related
//   - Each segment changes speed along its length (teacup ride)
//   - At crossings: near axis → faster (inner Keplerian)
//   - At apices: near outer edge → slower (outer Keplerian)
//   - Overall toroidal convection: steady, even rotation at 1.831c mean
//
// The spations on the torus surface experience this differential
// sinusoidal velocity profile, NOT uniform rotation.
//
// Torus: R = R_p = 0.84 fm (major), r = 0.70 × R (tube), from CQ20c.
//
// zk² = 1.  No G.  No M.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <sdt/laws.hpp>

using namespace sdt::laws;
using namespace sdt::laws::measured;

static constexpr double r_s = l_P / 2.0;

int main() {
    printf("###################################################################\n");
    printf("   CQ20f: Proton Trefoil — Sinusoidal Toroidal Convection\n");
    printf("   6Pi wound, 6 crossings, 6 apices, phase-locked\n");
    printf("   Teacup ride: differential speed, steady overall rotation\n");
    printf("###################################################################\n\n");

    // Torus geometry (from CQ20c: r/R = 0.70 gives trefoil 3:2)
    double R = R_p;                    // major radius = 0.84 fm
    double r_tube = 0.70 * R;         // tube radius
    double r_outer = R + r_tube;      // outer equator from axis
    double r_inner = R - r_tube;      // inner equator from axis

    printf("=== TORUS GEOMETRY ===\n\n");
    printf("   R (major):       %.4e m  (= R_p = 0.84 fm)\n", R);
    printf("   r (tube):        %.4e m  (= 0.70 × R)\n", r_tube);
    printf("   r_outer:         %.4e m  (R + r)\n", r_outer);
    printf("   r_inner:         %.4e m  (R - r)\n", r_inner);
    printf("   r_outer/r_inner: %.4f\n", r_outer/r_inner);
    printf("   r/R ratio:       0.70 (trefoil 3:2 from CQ20c)\n\n");

    // Velocity at outer equator = 1.831c (measured)
    double v_outer = 1.831 * c;

    // Keplerian: v(d) = v_outer × sqrt(r_outer / d)
    // where d = distance from torus axis
    double v_inner = v_outer * std::sqrt(r_outer / r_inner);
    double v_mid   = v_outer * std::sqrt(r_outer / R);

    printf("   v_outer:         %.4f c  (measured)\n", v_outer/c);
    printf("   v_mid:           %.4f c  (at major circle)\n", v_mid/c);
    printf("   v_inner:         %.4f c  (at inner equator)\n\n", v_inner/c);

    // =================================================================
    // THE 6Pi TREFOIL PATH
    //
    // Parametric: the trefoil (2,3) torus knot is:
    //   phi = toroidal angle (around torus hole) [0, 6π]
    //   theta = poloidal angle (around tube) [0, 4π]
    //   For (p=2, q=3): theta = (p/q) × phi = (2/3) × phi
    //
    // Position on torus surface:
    //   d(phi) = R + r_tube × cos(theta(phi))
    //          = R + r_tube × cos((2/3) × phi)
    //
    // The distance from the torus axis oscillates sinusoidally
    // between r_inner (d_min) and r_outer (d_max) as the knot
    // winds around the torus.
    //
    // The velocity at each point follows Keplerian:
    //   v(phi) = v_outer × sqrt(r_outer / d(phi))
    //
    // This gives a SINUSOIDAL velocity modulation along the path.
    //
    // Complete circuit: phi goes from 0 to 6π (3 toroidal loops).
    // In that span, theta goes from 0 to 4π (2 poloidal loops).
    // The knot crosses the outer equator 6 times (apices)
    // and the inner equator 6 times (crossings).
    // =================================================================

    printf("=================================================================\n");
    printf("   THE 6Pi TREFOIL PATH\n");
    printf("   phi: 0 → 6π (3 toroidal winds)\n");
    printf("   theta = (2/3)phi: 0 → 4π (2 poloidal winds)\n");
    printf("   12 events: 6 crossings (inner) + 6 apices (outer)\n");
    printf("=================================================================\n\n");

    // Sample the trefoil path at fine resolution
    int N_samples = 360;  // per toroidal wind
    int N_total = 3 * N_samples;  // 3 winds

    printf("   %-6s  %8s  %8s  %12s  %10s  %10s  %8s\n",
           "phi/pi", "phi[deg]", "theta[d]",
           "d_axis [m]", "v [c]", "v [m/s]", "event");
    printf("   %-6s  %8s  %8s  %12s  %10s  %10s  %8s\n",
           "------", "--------", "--------",
           "----------", "-----", "-------", "-----");

    double v_sum = 0;
    double v_min = 1e30, v_max = -1e30;
    int n_crossings = 0, n_apices = 0;
    double prev_d = 0;
    bool prev_rising = false;

    // Print key events only (every 30 deg of phi + extrema)
    for (int i = 0; i <= N_total; i++) {
        double phi = 6.0 * M_PI * i / N_total;
        double theta = (2.0 / 3.0) * phi;

        double d = R + r_tube * std::cos(theta);
        double v = v_outer * std::sqrt(r_outer / d);

        if (v < v_min) v_min = v;
        if (v > v_max) v_max = v;
        if (i > 0) v_sum += v;

        // Detect crossings (inner, d near d_min) and apices (outer, d near d_max)
        bool at_inner = (d < r_inner + 0.01 * r_tube);
        bool at_outer = (d > r_outer - 0.01 * r_tube);
        bool rising = (d > prev_d);

        const char* event = "";
        if (i > 0 && prev_rising && !rising) {
            event = "APEX";
            n_apices++;
        } else if (i > 0 && !prev_rising && rising) {
            event = "CROSS";
            n_crossings++;
        }

        // Print at every 0.5π of phi (90 deg) or at events
        double phi_over_pi = phi / M_PI;
        bool print_it = false;
        if (i % (N_samples/4) == 0) print_it = true;
        if (event[0] != '\0') print_it = true;

        if (print_it) {
            printf("   %6.2f  %8.1f  %8.1f  %12.4e  %10.4f  %10.4e  %8s\n",
                   phi_over_pi, phi*180/M_PI, theta*180/M_PI,
                   d, v/c, v, event);
        }

        prev_d = d;
        prev_rising = rising;
    }

    double v_mean = v_sum / N_total;

    printf("\n=== VELOCITY STATISTICS ===\n\n");
    printf("   v_min  (at apices):    %.4f c  (outer equator)\n", v_min/c);
    printf("   v_max  (at crossings): %.4f c  (inner equator)\n", v_max/c);
    printf("   v_mean (along path):   %.4f c\n", v_mean/c);
    printf("   v_max / v_min:         %.4f\n", v_max/v_min);
    printf("   v_max / v_mean:        %.4f\n", v_max/v_mean);
    printf("   v_mean / v_outer:      %.4f\n\n", v_mean/v_outer);
    printf("   Crossings detected:    %d  (expect 6)\n", n_crossings);
    printf("   Apices detected:       %d  (expect 6)\n\n", n_apices);

    // =================================================================
    // SPATION COUNT: Differential sinusoidal
    //
    // Each element dL of the trefoil path has spations proportional
    // to its arc length. The local velocity determines the LOCAL
    // spation engagement — faster sections drag more spations.
    //
    // The differential element on the torus:
    //   dx = (d × dphi)² + (r_tube × dtheta)²
    //   dL = sqrt(d² × (dphi)² + r_tube² × (dtheta)²)
    //   dL/dphi = sqrt(d² + r_tube² × (2/3)²)
    //          = sqrt(d² + (2r_tube/3)²)
    //
    // Contact spations per dL: dL / (2 × r_s) per row
    // Surface band width: ~ 2 × r_s (single contact line)
    // But the trefoil sweeps the ENTIRE torus surface over
    // its 6π winding — every point on the surface is touched.
    // =================================================================

    printf("=================================================================\n");
    printf("   SPATION COUNT ON TREFOIL PATH\n");
    printf("=================================================================\n\n");

    double total_length = 0;
    double weighted_v_sum = 0;

    for (int i = 0; i < N_total; i++) {
        double phi = 6.0 * M_PI * i / N_total;
        double theta = (2.0/3.0) * phi;
        double d = R + r_tube * std::cos(theta);

        double dphi = 6.0 * M_PI / N_total;
        double dtheta = (2.0/3.0) * dphi;

        // Arc length element
        double dL = std::sqrt(d*d*dphi*dphi + r_tube*r_tube*dtheta*dtheta);
        total_length += dL;

        double v = v_outer * std::sqrt(r_outer / d);
        weighted_v_sum += v * dL;
    }

    double v_weighted = weighted_v_sum / total_length;

    // Spation count along the path
    double N_path = total_length / (2.0 * r_s);

    // Torus surface area
    double S_torus = 4.0 * M_PI * M_PI * R * r_tube;
    double N_surface = S_torus / (M_PI * r_s * r_s);

    printf("   Trefoil path length:   %.4e m\n", total_length);
    printf("   Torus circumference:   %.4e m  (2πR)\n", 2.0*M_PI*R);
    printf("   Path / circumference:  %.2f  (wound 3×, but sinuous)\n",
           total_length / (2.0*M_PI*R));
    printf("\n");
    printf("   Spations along path:   %.4e  (path_len / 2r_s)\n", N_path);
    printf("   Spations on surface:   %.4e  (area / πr_s²)\n", N_surface);
    printf("\n");
    printf("   v_weighted (by arc):   %.4f c\n", v_weighted/c);
    printf("   v_mean (uniform):      %.4f c\n", v_mean/c);
    printf("   Difference:            %.4f c\n\n", (v_weighted-v_mean)/c);

    // =================================================================
    // THE TEACUP RIDE
    //
    // Despite the sinusoidal velocity variation along the path,
    // the OVERALL toroidal circulation is steady. The fast sections
    // (crossings) and slow sections (apices) average out.
    //
    // Mean toroidal velocity = integral of v(phi) × d(phi) / integral
    // The toroidal period T_tor = 2πR / v_mean_toroidal
    // =================================================================
    printf("=================================================================\n");
    printf("   THE TEACUP RIDE: Steady overall rotation\n");
    printf("=================================================================\n\n");

    // Toroidal component of velocity: v_tor = v × (d/sqrt(d² + (2r/3)²))
    double T_sum = 0;
    for (int i = 0; i < N_total; i++) {
        double phi = 6.0 * M_PI * i / N_total;
        double theta = (2.0/3.0) * phi;
        double d = R + r_tube * std::cos(theta);
        double v = v_outer * std::sqrt(r_outer / d);

        // Toroidal component: velocity projected onto toroidal direction
        double dL_tor = d * (6.0*M_PI/N_total);  // toroidal arc
        double dL_pol = r_tube * (2.0/3.0) * (6.0*M_PI/N_total);
        double dL = std::sqrt(dL_tor*dL_tor + dL_pol*dL_pol);

        // Time to traverse this element
        double dt = dL / v;
        T_sum += dt;
    }

    // T_sum is the time for one complete circuit (6π toroidal)
    // But we want the period for one toroidal loop (2π)
    double T_circuit = T_sum;
    double T_per_loop = T_circuit / 3.0;  // 3 toroidal loops per circuit

    double v_eff_toroidal = 2.0 * M_PI * R / T_per_loop;

    printf("   Full circuit (6π tor, 4π pol): %.4e s\n", T_circuit);
    printf("   Per toroidal loop (2π):        %.4e s\n", T_per_loop);
    printf("   Effective v_toroidal:          %.4f c\n", v_eff_toroidal/c);
    printf("   (steady rotation despite sinusoidal local speed)\n\n");

    // Poloidal period
    double T_pol_loop = T_circuit / 2.0;  // 2 poloidal loops per circuit
    double v_eff_poloidal = 2.0 * M_PI * r_tube / T_pol_loop;

    printf("   Per poloidal loop (2π):        %.4e s\n", T_pol_loop);
    printf("   Effective v_poloidal:          %.4f c\n", v_eff_poloidal/c);
    printf("   T_tor / T_pol:                 %.4f  (expect 3/2)\n\n",
           T_per_loop / T_pol_loop);

    // Phase velocity of the trefoil pattern
    printf("   Phase speed of trefoil:        %.4f c\n", v_weighted/c);
    printf("   This is what the spation lattice sees:\n");
    printf("   a differential sinusoidal wave at %.4fc mean,\n", v_weighted/c);
    printf("   with 6 fast nodes (crossings) and 6 slow nodes (apices),\n");
    printf("   all phase-locked into a steady toroidal convection.\n\n");

    printf("   This IS the proton. The spation engagement is\n");
    printf("   differential: each spation on the torus surface\n");
    printf("   sees a velocity that oscillates sinusoidally,\n");
    printf("   creating the differential convergence occlusion pattern\n");
    printf("   that IS the electromagnetic field.\n");

    return 0;
}
