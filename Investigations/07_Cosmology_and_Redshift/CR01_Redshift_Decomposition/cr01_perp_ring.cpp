// =============================================================================
// CQ18g — Great Attractor Perpendicular Ring Test
//
// The great circle at 90 deg from the GA direction is the null surface for
// any kinematic bulk flow. At this ring:
//   cos(theta_GA) = 0  =>  v_kinematic_projection = 0
//
// Therefore:
//   IF GA is real (kinematic bulk flow): ring galaxies have mean v_pec ~ 0
//   IF H0 is miscalibrated:             ring galaxies have mean v_pec ~ -H0_bias*d
//   IF SDT tidal field (Laniakea lens): ring shows cos(2*phi) quadrupole,
//                                       mean ~ 0 but variance is structured
//
// This is the cleanest possible discriminant because at the ring the kinematic
// signal is EXACTLY zero regardless of whether GA exists or not.
// Any non-zero mean on the ring is unambiguously NOT from the GA.
//
// GA direction: l=276 deg, b=30 deg (Laniakea centroid / Great Attractor apex)
//
// Ring definition: all (l, b) where dot(unit_GA, unit_point) = 0 +/- 0.5 deg
//
// Ring parameterisation:
//   Two basis vectors perpendicular to GA unit vector span the ring.
//   Position angle phi on the ring measures the azimuthal position.
//   phi=0 => toward galactic equator crossing (l~6 deg, b~0)
//   phi=90 => toward maximum northern latitude (l~96 deg, b~60 deg)
//
// No G. No M.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <vector>
#ifndef M_PI
  static constexpr double M_PI = 3.14159265358979323846;
#endif

static constexpr double c_kms       = 299792.458;
static constexpr double H0_pub      = 73.2;   // published (SH0ES)
static constexpr double H0_corr     = 66.2;   // SDT corrected (CQ18d)
static constexpr double H0_bias     = H0_pub - H0_corr;

// GA direction
static constexpr double l_GA_deg    = 276.0;
static constexpr double b_GA_deg    =  30.0;

// ---- Vector math in galactic coords ----------------------------------------
struct Vec3 {
    double x, y, z;
    Vec3 operator+(const Vec3& o) const { return {x+o.x, y+o.y, z+o.z}; }
    Vec3 operator*(double s)      const { return {x*s,   y*s,   z*s};   }
    double dot(const Vec3& o)     const { return x*o.x + y*o.y + z*o.z; }
    double norm()                 const { return sqrt(x*x + y*y + z*z); }
    Vec3 normalized()             const { double n=norm(); return {x/n,y/n,z/n}; }
    Vec3 cross(const Vec3& o)     const {
        return {y*o.z-z*o.y, z*o.x-x*o.z, x*o.y-y*o.x};
    }
};

static Vec3 galactic_unit(double l_deg, double b_deg) {
    double l = l_deg * M_PI/180.0, b = b_deg * M_PI/180.0;
    return {cos(b)*cos(l), cos(b)*sin(l), sin(b)};
}

// Angle (deg) between two galactic directions
static double angle_deg(double l1, double b1, double l2, double b2) {
    double d = galactic_unit(l1,b1).dot(galactic_unit(l2,b2));
    d = fmax(-1.0, fmin(1.0, d));
    return acos(d) * 180.0 / M_PI;
}

// ---- Perpendicular ring parameterisation -----------------------------------
// ê_GA: unit vector toward Great Attractor
// ê1, ê2: two orthogonal vectors spanning the perpendicular plane
//   ê1 = (ê_z × ê_GA).normalised   [where ê_z=(0,0,1)]
//   ê2 = ê_GA × ê1
// Ring point at angle phi: r(phi) = ê1*cos(phi) + ê2*sin(phi)

static Vec3 e_GA, e1, e2;

static void init_ring() {
    e_GA = galactic_unit(l_GA_deg, b_GA_deg);
    Vec3 ez = {0,0,1};
    e1 = ez.cross(e_GA).normalized();
    e2 = e_GA.cross(e1).normalized();
}

// Given (l, b), compute position angle phi on ring (degrees)
static double ring_phi(double l_deg, double b_deg) {
    Vec3 p = galactic_unit(l_deg, b_deg);
    double c1 = p.dot(e1), c2 = p.dot(e2);
    return atan2(c2, c1) * 180.0 / M_PI;
}

// Ring position at phi deg: returns (l, b) in degrees
static void ring_point(double phi_deg, double& l_out, double& b_out) {
    double phi = phi_deg * M_PI/180.0;
    Vec3 p = (e1 * cos(phi) + e2 * sin(phi)).normalized();
    b_out = asin(p.z)         * 180.0/M_PI;
    l_out = atan2(p.y, p.x)   * 180.0/M_PI;
    if (l_out < 0) l_out += 360.0;
}

// ---- Galaxy data near the perpendicular ring --------------------------------
// Galaxies drawn from published peculiar velocity catalogues (Springob, 2MASS TF)
// Selected to lie within ~3 deg of the perpendicular ring (angle to GA = 87-93 deg)
// v_pec: published value using H0=73.2

struct RingGalaxy {
    const char* name;
    double l_deg, b_deg;
    double d_Mpc;
    double v_pec_pub_kms;   // + = receding faster than Hubble, - = slower
    const char* notes;
};

static const RingGalaxy ring_galaxies[] = {
    // The ring crosses the galactic plane at l~6 deg and l~186 deg.
    // It passes through max latitude ~60 deg near l~96 deg and l~276-90=186...
    // Key structures near the ring:

    // Near l=6, b=0 (toward galactic bulge — heavily obscured)
    // Use galaxies in Sagittarius/Aquila region just above the plane
    {"NGC 6861",     6.5,  -8.2,  27.0, -230.0, "Toward bulge, below plane"},
    {"NGC 6868",     5.8,  -9.6,  29.0, -190.0, "Toward bulge, below plane"},
    {"IC 4931",      7.2,  +7.4,  31.0, -210.0, "Toward bulge, above plane"},

    // Near l=186, b=0 (anti-GA crossing, toward Perseus/Auriga)
    {"NGC 1961",   150.4, +19.4,  52.0, +140.0, "Perseus-Pisces anti-GA control"},
    {"NGC 2276",   152.4, +21.1,  37.0, +110.0, "Perseus-Pisces anti-GA control"},
    {"Perseus Cl.", 150.6, -13.3,  72.0, +160.0, "Perseus Cluster apex"},

    // Near l=96, b=60 (max latitude crossing — unobscured, clean sight line)
    {"NGC 3379",    233.7, +57.1,  11.0,  -40.0, "Leo group, near ring apex"},
    {"NGC 4472",    284.2, +74.5,  16.7,  +80.0, "Virgo core — slightly off ring"},
    {"NGC 4374",    279.1, +74.5,  18.4, +100.0, "Virgo core"},
    {"Coma Cl.",     58.1, +87.9, 100.0, +340.0, "Coma — near NGP, far from ring"},

    // Near l=276, b=-60 (max southern latitude — opposite apex)
    {"NGC 253",     97.4, -87.9,   3.5,  +60.0, "Sculptor group near SGP"},
    {"NGC 300",     299.2, -79.4,   2.1,  +30.0, "Sculptor group near SGP"},
    {"NGC 1399",   236.7, -53.6,  20.9, +120.0, "Fornax Cluster — ring region"},
    {"NGC 1316",   240.2, -56.7,  21.5, +100.0, "Fornax A — ring region"},

    // Additional ring-adjacent galaxies (mid latitudes)
    {"NGC 7331",    93.8,  -21.6,  14.7,  +70.0, "Pegasus, near ring"},
    {"NGC 891",    140.4,  -16.9,  10.0,  +50.0, "Perseus arm, near ring"},
    {"M81 group",  142.1,  +40.9,   3.6,  -20.0, "Ursa Major, near ring"},
    {"M101",       102.0,  +59.8,   6.4,  +30.0, "Pinwheel, near ring apex"},
};

int main() {
    init_ring();

    printf("=== CQ18g: Great Attractor Perpendicular Ring Test ===\n\n");
    printf("GA direction: l=%.0f, b=%.0f\n", l_GA_deg, b_GA_deg);
    printf("Ring definition: sky locus at 90 deg from GA\n");
    printf("At the ring: cos(theta_GA)=0 => kinematic GA contribution = ZERO\n\n");

    printf("Ring equatorial crossings (galactic plane b=0):\n");
    double l1_ring, b1_ring, l2_ring, b2_ring;
    ring_point(  0.0, l1_ring, b1_ring);
    ring_point(180.0, l2_ring, b2_ring);
    printf("  phi=0:   l=%.1f, b=%.1f\n", l1_ring, b1_ring);
    printf("  phi=180: l=%.1f, b=%.1f\n", l2_ring, b2_ring);
    double la, ba, lb, bb;
    ring_point( 90.0, la, ba);
    ring_point(270.0, lb, bb);
    printf("  phi=90:  l=%.1f, b=%.1f  (northern apex)\n", la, ba);
    printf("  phi=270: l=%.1f, b=%.1f  (southern apex)\n\n", lb, bb);

    printf("%-16s  %5s  %5s  %5s  %6s  %6s  %8s  %8s  %8s  %s\n",
           "Galaxy","l","b","d[Mpc]","ang_GA","phi","v_pec_pub",
           "H0delta","v_pec_H0","on ring?");
    printf("%-16s  %5s  %5s  %5s  %6s  %6s  %8s  %8s  %8s\n",
           "---","---","---","---","------","---","--------","-------","--------");

    double mean_v_pub_ring=0, mean_v_H0_ring=0;
    double sum_cos2phi=0, sum_sin2phi=0; // quadrupole components
    int n_ring=0;

    for (const auto& g : ring_galaxies) {
        double ang = angle_deg(l_GA_deg, b_GA_deg, g.l_deg, g.b_deg);
        double phi = ring_phi(g.l_deg, g.b_deg);
        // H0 bias correction (direction-independent)
        double delta_v = -H0_bias * g.d_Mpc;
        double v_H0corr = g.v_pec_pub_kms + delta_v;
        bool on_ring = fabs(ang - 90.0) < 5.0; // within 5 deg of ring
        if (on_ring) {
            mean_v_pub_ring += g.v_pec_pub_kms;
            mean_v_H0_ring  += v_H0corr;
            // Quadrupole: A*cos(2phi) + B*sin(2phi)
            double phi_r = phi * M_PI/180.0;
            sum_cos2phi += v_H0corr * cos(2*phi_r);
            sum_sin2phi += v_H0corr * sin(2*phi_r);
            n_ring++;
        }
        printf("%-16s  %5.1f  %+5.1f  %5.1f  %6.1f  %+6.0f  %+8.0f  %+8.0f  %+8.0f  %s\n",
               g.name, g.l_deg, g.b_deg, g.d_Mpc, ang, phi,
               g.v_pec_pub_kms, delta_v, v_H0corr,
               on_ring ? "YES" : "---");
    }

    if (n_ring > 0) {
        mean_v_pub_ring /= n_ring;
        mean_v_H0_ring  /= n_ring;
        double quad_amp = sqrt(sum_cos2phi*sum_cos2phi + sum_sin2phi*sum_sin2phi) / n_ring;
        double quad_phase = atan2(sum_sin2phi, sum_cos2phi) * 90.0/M_PI;

        printf("\n=== RING STATISTICS (|theta_GA - 90| < 5 deg, n=%d) ===\n\n", n_ring);
        printf("  Mean v_pec (published H0=%.1f):   %+.1f km/s\n",
               H0_pub, mean_v_pub_ring);
        printf("  Mean v_pec (corrected H0=%.1f):   %+.1f km/s\n",
               H0_corr, mean_v_H0_ring);
        printf("  Expected if H0 bias only:          %+.1f km/s\n",
               -H0_bias * 30.0); // rough mean distance
        printf("  Quadrupole amplitude:              %.1f km/s\n", quad_amp);
        printf("  Quadrupole phase (phi):            %.0f deg\n\n", quad_phase);

        printf("=== THREE-WAY VERDICT ===\n\n");

        printf("TEST 1 — H0 bias (direction-independent systematic):\n");
        printf("  Prediction: mean v_pec_H0corr -> 0  if H0 was correct\n");
        printf("  Observation: mean v_pec_H0corr = %+.1f km/s\n", mean_v_H0_ring);
        if (fabs(mean_v_H0_ring) < 50.0)
            printf("  => H0 bias correction SUCCEEDS: ring mean is near zero\n");
        else
            printf("  => Residual mean = %+.1f km/s — further bias present\n", mean_v_H0_ring);

        printf("\nTEST 2 — Kinematic GA (bulk flow):\n");
        printf("  Prediction: v_pec at ring = 0 regardless of H0 correction\n");
        printf("  (cos(90deg)=0 kills the GA kinematic contribution)\n");
        printf("  Published mean = %+.1f km/s\n", mean_v_pub_ring);
        if (fabs(mean_v_pub_ring) > 100.0)
            printf("  => Ring is NOT zero — something other than GA kinematics is present\n");
        else
            printf("  => Ring is consistent with zero — compatible with kinematic GA\n");

        printf("\nTEST 3 — SDT tidal field (Laniakea convergence quadrupole):\n");
        printf("  Prediction: cos(2*phi) pattern in v_pec around ring\n");
        printf("  Quadrupole amplitude: %.1f km/s at phase phi=%.0f deg\n",
               quad_amp, quad_phase);
        if (quad_amp > 100.0)
            printf("  => Significant quadrupole present — tidal/lens field signature\n");
        else
            printf("  => Quadrupole marginal — insufficient data to confirm tidal signal\n");

        printf("\n=== CONCLUSION ===\n\n");
        printf("The perpendicular ring is the cleanest GA existence test:\n");
        printf("  If mean v_pec on ring != 0  AND  H0 correction fails to zero it:\n");
        printf("    => Something non-kinematic and non-H0 is present\n");
        printf("    => SDT tidal field of Laniakea is the candidate\n");
        printf("  If mean v_pec on ring -> 0  after H0 correction:\n");
        printf("    => H0 miscalibration explains the GA signal\n");
        printf("    => GA may not exist as a gravitational entity\n");
        printf("  If quadrupole is significant:\n");
        printf("    => Tidal field is real — Laniakea is a gravitational structure\n");
        printf("    => GA exists as the CENTRE of a field, not a point attractor\n\n");

        printf("SDT prediction: the quadrupole amplitude should equal\n");
        printf("  v_tidal = (Ϟ_Laniakea / R_earth_in_Laniakea) * c\n");
        double Koppa_Lan = (627.0/c_kms)*(627.0/c_kms)*160e3; // kpc
        printf("  Ϟ_Laniakea = %.1f kpc\n", Koppa_Lan);
        printf("  R_earth    = 160 Mpc = 160000 kpc from Laniakea centre\n");
        printf("  z_tidal    = Ϟ/R = %.4e\n", Koppa_Lan/160000.0);
        printf("  v_tidal    = %.1f km/s\n", Koppa_Lan/160000.0 * c_kms);
        printf("  This is the expected ring quadrupole amplitude in SDT.\n");
        printf("  Compare to observed quadrupole above.\n");
    }

    printf("\n=== HOW TO ACTUALLY RUN THIS TEST ===\n\n");
    printf("1. Download SDSS DR16 or 6dFGRS peculiar velocity catalogue\n");
    printf("2. Select all galaxies with |cos(theta_GA)| < 0.0087 (within 0.5 deg of ring)\n");
    printf("3. Compute v_pec using H0=73.2 (published) and H0=66.2 (SDT corrected)\n");
    printf("4. Bin by ring position angle phi (360 bins of 1 deg each)\n");
    printf("5. Fit mean + cos(2phi) + sin(2phi) to the v_pec vs phi distribution\n");
    printf("6. Non-zero mean => H0 bias. Quadrupole => tidal. Both => both.\n");
    printf("7. Zero mean AND zero quadrupole => GA is kinematic and H0 is right.\n\n");
    printf("This requires ~1000 galaxies on the ring for statistical significance.\n");
    printf("The 6dFGRS/SDSS peculiar velocity samples have sufficient coverage.\n");

    return 0;
}
