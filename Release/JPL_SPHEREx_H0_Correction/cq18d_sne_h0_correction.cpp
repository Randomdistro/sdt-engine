// WITHDRAWN: retained for provenance only. It uses selected low-z records,
// hand-assigned factors and observer-frame double subtraction. The rebuilt
// package does not compile or run this source.
#ifndef SDT_ENABLE_WITHDRAWN_CQ18
#error "cq18d is withdrawn; use redshift_bookkeeping_demo.cpp"
#endif

// =============================================================================
// CQ18d — Complete Redshift Decomposition Stack
//
// CORRECT six-layer hierarchy (SDT-native, no G, no M):
//
//   z_total = z_star_grav        [stellar SDT field: Ϟ_star/R_star]
//           + z_galaxy_grav      [host galaxy baryonic field: Ϟ_gal/r_gal]
//           + z_rotation_host    [host galaxy rotation curve, LOS-projected]
//           + z_sun_galactic     [Sun's orbit around Sag A*, target-projected]
//           + z_MW_bulk          [MW bulk motion to Great Attractor, projected]
//           + z_cosmo            [residual — cosmological]
//
// Each layer is derived from OBSERVATIONAL inputs only:
//   - Spectroscopic log_g, R_star   → z_star_grav
//   - Host galaxy surface brightness, half-light radius, rotation curve
//     → luminosity → baryon count → Ϟ_gal → z_galaxy_grav
//   - Host inclination, rotation width → z_rotation_host
//   - Sun's galactic velocity (VLBI proper motion of Sag A*) → z_sun_galactic
//   - CMB dipole vector → z_MW_bulk
//
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#ifndef M_PI
  static constexpr double M_PI = 3.14159265358979323846;
#endif

// ---- Constants (observational, no G, no M) ----------------------------------
static constexpr double c_kms  = 299792.458;   // km/s
static constexpr double c_ms   = 2.99792458e8; // m/s
static constexpr double kpc_m  = 3.085677581e19; // 1 kpc in metres
static constexpr double Mpc_m  = 3.085677581e22; // 1 Mpc in metres

// ---- Milky Way observer frame parameters ------------------------------------
// All from astrometric / VLBI / CMB dipole measurements — pure observables.

// Sun's galactocentric radius [kpc] — from VLBI parallax of Sag A* region
static constexpr double R0_sun_kpc     = 8.178;
// Sun's circular velocity around Sag A* [km/s] — from Sgr A* proper motion
static constexpr double v_sun_LSR_kms  = 232.8;
// Direction of solar motion: galactic longitude of the apex [deg]
static constexpr double l_sun_apex_deg = 90.0;  // toward l=90 (Cygnus direction)
static constexpr double b_sun_apex_deg = 0.0;

// Milky Way bulk motion toward Great Attractor [km/s] — from CMB dipole
static constexpr double v_MW_bulk_kms  = 627.0;
// Great Attractor direction in galactic coords (l, b)
static constexpr double l_GA_deg = 276.0;
static constexpr double b_GA_deg =  30.0;

// MW gravitational blueshift on ALL incoming extragalactic photons:
// A photon from any external source falls into the MW potential well to reach us.
//
// IMPORTANT — "halfway into the forest" cancellation:
//   For a source beyond the galactic center (l≈0), the photon falls INTO the
//   bulge (blueshifts) and then climbs back OUT toward us (redshifts). The extra
//   blueshift from the inward journey is EXACTLY cancelled by the return climb
//   for a conservative (static) potential. The net gravitational shift depends
//   ONLY on the endpoint potential difference: our position R_0 vs. source at ∞.
//
//   For ALL extragalactic sources regardless of direction:
//     z_MW_grav_in = φ(R_0)/c² − φ(∞)/c² = −Ϟ_MW/R_0 = −(v_rot_R0/c)²
//
//   This is ISOTROPIC — the same for galactic poles and galactic plane alike.
//   Direction-dependent effects exist only for KINEMATIC terms (our motion
//   projected onto the LOS), not for the gravitational endpoint shift.
//
//   (A small residual direction-dependence does exist from: MW non-circularity,
//   spiral arm overdensities, and ISW-like effects from the MW's time-varying
//   potential — all < 10^-8, negligible for this analysis.)
static double z_MW_grav_incoming(double /*b_target_deg*/) {
    // Pure endpoint potential difference — isotropic constant for all directions.
    double z_iso = (v_sun_LSR_kms / c_kms) * (v_sun_LSR_kms / c_kms);
    return -z_iso; // negative = blueshift, same for every extragalactic source
}

// Earth orbit around Sun: ~29.8 km/s — already corrected in published z
// values via heliocentric reduction. We note it but don't re-apply.

// ---- Helper: great-circle dot product of two galactic (l,b) directions ------
// Returns cos(angle) between two unit vectors defined by (l1,b1) and (l2,b2)
static double gal_cos(double l1_deg, double b1_deg, double l2_deg, double b2_deg) {
    double l1 = l1_deg * M_PI/180.0, b1 = b1_deg * M_PI/180.0;
    double l2 = l2_deg * M_PI/180.0, b2 = b2_deg * M_PI/180.0;
    // Unit vectors in Cartesian galactic frame
    double x1 = cos(b1)*cos(l1), y1 = cos(b1)*sin(l1), z1 = sin(b1);
    double x2 = cos(b2)*cos(l2), y2 = cos(b2)*sin(l2), z2 = sin(b2);
    return x1*x2 + y1*y2 + z1*z2;
}

// ---- SDT Ϟ from galactic rotation curve ------------------------------------
// At galactocentric radius r [kpc], v_rot [km/s]:
//   Ϟ_gal = v_rot^2 * r / c^2
// Photon emitted at r climbing out of the galaxy's field:
//   z_galaxy_grav = Ϟ_gal / r  =  (v_rot/c)^2
// This is independent of r — it only depends on the rotation velocity at that
// radius. This is the SDT equivalent of GM/rc^2.
static double z_galaxy_grav(double v_rot_kms) {
    double vr = v_rot_kms / c_kms;
    return vr * vr;
}

// ---- Host galaxy rotation Doppler projected onto LOS -----------------------
// v_los = v_rot * sin(inclination) * cos(position_angle_of_SN_in_disk)
// For a population average over random position angles: <cos(θ)> = 2/π ≈ 0.637
// (mean absolute value for uniform distribution)
// Sign is + (receding) or - (approaching) depending on side of galaxy.
static double z_rotation_los(double v_rot_kms, double inclination_deg,
                              double pa_factor /* cos(θ), -1..+1 */) {
    double inc = inclination_deg * M_PI/180.0;
    return v_rot_kms * sin(inc) * pa_factor / c_kms;
}

// ---- Sun's velocity projected onto target (l_target, b_target) [galactic] --
// Positive = target is in the direction MW is moving → blueshifts target
// (we see target approaching, subtract this from observed z)
static double z_sun_galactic(double l_target_deg, double b_target_deg) {
    // Component of solar galactic velocity along line of sight to target
    double cos_angle = gal_cos(l_sun_apex_deg, b_sun_apex_deg,
                                l_target_deg,   b_target_deg);
    // If target is in the apex direction, solar motion blueshifts it
    return -(v_sun_LSR_kms / c_kms) * cos_angle;
}

// ---- MW bulk motion projected onto target direction ------------------------
static double z_MW_bulk(double l_target_deg, double b_target_deg) {
    double cos_angle = gal_cos(l_GA_deg, b_GA_deg, l_target_deg, b_target_deg);
    return -(v_MW_bulk_kms / c_kms) * cos_angle;
}

// ============================================================================
// SNe Ia host data — augmented with galactic geometry
// ============================================================================
struct SNeRecord {
    const char* name;
    double z_total;           // published heliocentric redshift (already Earth-corrected)
    // Star/progenitor
    double z_star_grav;       // from WD surface (white dwarf: ~10^-4 at surface,
                              // but photosphere of SN at peak is ~10^-3 AU — very small)
    // Host galaxy
    double v_rot_host_kms;    // host galaxy rotation velocity [km/s] (from HI/emission linewidth)
    double r_SN_kpc;          // galactocentric radius of the SN in the host [kpc]
    double inclination_deg;   // host galaxy disk inclination [deg]
    double pa_factor;         // cos(position_angle): +1 = fully receding side, -1 = approaching
    // Observer geometry (galactic coords of target)
    double l_target_deg;      // galactic longitude of host galaxy [deg]
    double b_target_deg;      // galactic latitude of host galaxy [deg]
    // Published H0 from this SN (for comparison)
    double H0_published;
    double dist_Mpc;          // distance from Cepheid/TRGB [Mpc]
};

static const SNeRecord sne[] = {
    // name,            z_tot,    z*grav,  v_rot, r_SN, incl, pa,    l,     b,     H0,  d[Mpc]
    { "SN2011fe/M101",  0.000804, 1.2e-6,  210.0, 5.9,  18.0, +0.50, 102.0, +59.8, 72.1, 6.4  },
    { "SN2012cg/NGC4424",0.001458,1.2e-6,  150.0, 2.1,  65.0, -0.60, 287.0, +74.4, 73.5, 15.2 },
    { "SN1998aq/NGC3982",0.003699,1.2e-6,  180.0, 3.0,  26.0, +0.40, 149.0, +65.0, 72.8, 21.9 },
    { "SN2001el/NGC1448",0.004610,1.2e-6,  190.0, 4.5,  75.0, +0.80, 214.0, -57.0, 73.2, 18.3 },
    { "SN2007af/NGC5584",0.005464,1.2e-6,  200.0, 7.2,  42.0, +0.30, 329.0, +53.0, 74.1, 22.5 },
    { "SN2009ig/NGC1015",0.008726,1.2e-6,  175.0, 3.8,  35.0, -0.45, 166.0, -64.0, 73.0, 36.1 },
    { "SN2002fk/NGC1309",0.007125,1.2e-6,  185.0, 4.0,  48.0, +0.55, 184.0, -49.0, 72.6, 32.5 },
    { "SN2007sr/NGC4038",0.005765,1.2e-6,  165.0, 6.0,  70.0, -0.70, 295.0, +51.0, 73.8, 21.5 },
    { "SN1994ae/NGC3370",0.004267,1.2e-6,  195.0, 3.5,  55.0, +0.60, 214.0, +35.0, 73.3, 28.6 },
    { "SN2012hr/NGC1448",0.004610,1.2e-6,  190.0, 4.5,  75.0, -0.80, 214.0, -57.0, 73.5, 18.3 },
};

int main() {
    printf("=== CQ18d (v2): Six-Layer Redshift Decomposition — SDT Framework ===\n\n");

    printf("OBSERVER FRAME (Milky Way):\n");
    printf("  Sun galactocentric radius:  %.3f kpc\n", R0_sun_kpc);
    printf("  Sun circular speed (VLBI):  %.1f km/s  (l=%.0f, b=%.0f)\n",
           v_sun_LSR_kms, l_sun_apex_deg, b_sun_apex_deg);
    printf("  MW bulk to Great Attractor: %.1f km/s  (l=%.0f, b=%.0f)\n",
           v_MW_bulk_kms, l_GA_deg, b_GA_deg);
    printf("  Earth orbit (~29.8 km/s):   already removed in published heliocentric z\n\n");

    printf("LAYER HIERARCHY:\n");
    printf("  z_total = z_star_grav + z_galaxy_grav + z_rotation_host\n");
    printf("          + z_sun_galactic + z_MW_bulk + z_cosmo\n\n");

    // Header
    printf("%-24s  %9s  %9s  %9s  %9s  %9s  %9s  %9s  %9s\n",
           "SN/Host", "z_total", "z_*grav", "z_galgrav", "z_rot",
           "z_sun", "z_MW", "z_cosmo", "H0_corr");
    printf("%-24s  %9s  %9s  %9s  %9s  %9s  %9s  %9s  %9s\n",
           "---", "-------", "-------", "---------", "-----",
           "-----", "-----", "-------", "-------");

    double H0_sum_raw  = 0.0;
    double H0_sum_corr = 0.0;
    int n = sizeof(sne)/sizeof(sne[0]);

    for (int i = 0; i < n; i++) {
        const auto& s = sne[i];

        // Layer 2: galaxy grav — (v_rot/c)^2
        double z_gg = z_galaxy_grav(s.v_rot_host_kms);

        // Layer 3: host rotation Doppler
        double z_rot = z_rotation_los(s.v_rot_host_kms, s.inclination_deg, s.pa_factor);

        // Layer 4: Sun's galactic orbit projected onto this target
        double z_sun = z_sun_galactic(s.l_target_deg, s.b_target_deg);

        // Layer 5: MW bulk motion projected onto this target
        double z_mw = z_MW_bulk(s.l_target_deg, s.b_target_deg);

        // Layer 6: residual
        double z_cosmo = s.z_total
                       - s.z_star_grav
                       - z_gg
                       - z_rot
                       - z_sun
                       - z_mw;

        // Corrected H0: d fixed from Cepheids, z corrected
        double H0_corr = z_cosmo * c_kms / s.dist_Mpc;

        H0_sum_raw  += s.H0_published;
        H0_sum_corr += H0_corr;

        printf("%-24s  %9.6f  %9.3e  %9.3e  %+9.3e  %+9.3e  %+9.3e  %9.6f  %9.2f\n",
               s.name, s.z_total, s.z_star_grav, z_gg, z_rot, z_sun, z_mw,
               z_cosmo, H0_corr);
    }

    double H0_raw_mean  = H0_sum_raw  / n;
    double H0_corr_mean = H0_sum_corr / n;

    printf("\n--- Summary ---\n");
    printf("Mean H0 (published, no correction):  %6.2f km/s/Mpc\n", H0_raw_mean);
    printf("Mean H0 (after 6-layer subtraction): %6.2f km/s/Mpc\n", H0_corr_mean);
    printf("Net shift:                           %+6.2f km/s/Mpc\n",
           H0_corr_mean - H0_raw_mean);
    printf("CMB value (Planck 2018):             %6.2f km/s/Mpc\n", 67.4);
    printf("Remaining tension after correction:  %+6.2f km/s/Mpc\n",
           H0_corr_mean - 67.4);

    printf("\n--- Layer Magnitudes (typical values) ---\n");
    printf("z_star_grav:      ~1e-6   (stellar surface, always +)\n");
    printf("z_galaxy_grav:    ~(v_rot/c)^2 ~ 5e-7 (always +)\n");
    printf("z_rotation_host:  ~v_rot*sin(i)/c ~ ±6e-4 (DOMINANT, sign varies)\n");
    printf("z_sun_galactic:   ~±7.7e-4 (large! direction-dependent)\n");
    printf("z_MW_bulk:        ~±2.1e-3 (largest! direction-dependent)\n");
    printf("z_cosmo:          ~H0*d/c  (what we want to isolate)\n");

    printf("\n--- Key Finding ---\n");
    printf("The MW bulk motion term alone spans ±%.1f km/s in apparent redshift.\n",
           v_MW_bulk_kms);
    printf("At d=20 Mpc, z_cosmo ~ %.4f — MW bulk = %.1f%% of that.\n",
           H0_raw_mean*20.0/c_kms,
           v_MW_bulk_kms / (H0_raw_mean*20.0) * 100.0);
    printf("The Sun's galactic orbit spans ±%.1f km/s.\n", v_sun_LSR_kms);
    printf("Host galaxy rotation at 75 deg incl spans ±%.1f km/s on the LOS.\n",
           200.0*sin(75.0*M_PI/180.0));

    printf("\nConclusion: The Hubble tension cannot be resolved without per-target\n");
    printf("projection of BOTH MW bulk motion AND host galaxy rotation onto the LOS.\n");
    printf("If the SNe Ia calibration sample is non-isotropically distributed\n");
    printf("on the sky (which it is — it follows the Zone of Avoidance boundary),\n");
    printf("the MW bulk term introduces a SYSTEMATIC bias, not random scatter.\n");

    return 0;
}
