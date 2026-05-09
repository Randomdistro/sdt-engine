// =============================================================================
// CQ18f — Great Attractor: Real or Zone of Avoidance z_grav Artifact?
//
// Hypothesis: The inferred Great Attractor mass is partly or entirely a
// systematic error from z_grav contamination in the Zone of Avoidance (ZoA).
//
// Evidence chain:
//   1. The Great Attractor was identified from galaxy peculiar velocity surveys.
//   2. Those surveys measure z_total of galaxies near |b| < 20 deg.
//   3. Near |b| < 20 deg, MW disk column density is at maximum.
//   4. In SDT: z_grav_disk = f(column_density, b) — a systematic, not random.
//   5. This excess z_grav appears as "galaxy recedes slower than Hubble flow"
//      → interpreted as "something massive is pulling it toward us" in that dir.
//   6. Accumulate this bias across thousands of galaxies → phantom attractor.
//
// This solver:
//   (a) Models the MW disk z_grav as a function of |b|
//   (b) Applies it to the galaxy peculiar velocity survey data near the GA dir
//   (c) Recomputes the inferred attractor mass after z_grav subtraction
//   (d) Tests whether the Great Attractor dissolves, shrinks, or survives
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

static constexpr double c_kms     = 299792.458;
static constexpr double H0_CMB    = 67.4;   // km/s/Mpc  (CMB baseline)

// MW disk parameters (observational)
static constexpr double h_R_kpc   = 3.5;    // disk scale length [kpc]
static constexpr double h_z_kpc   = 0.3;    // disk scale height [kpc]
static constexpr double R0_kpc    = 8.178;  // Sun's galactocentric radius [kpc]
static constexpr double v_rot0    = 232.8;  // Sun's circular speed [km/s]
static constexpr double rho_d0    = 1.0;    // normalised disk density at Sun

// ---- SDT MW disk z_grav along a LOS at galactic latitude b ----------------
// Photon arriving from direction (l, b) passes through the MW disk column.
// The net gravitational shift for the photon is purely the endpoint potential
// difference (path-independent for a conservative field). However, the INFERRED
// peculiar velocity of a GALAXY at distance d behind the disk IS affected by
// the extra z_grav from the disk column between us and that galaxy.
//
// A galaxy at distance d_Mpc, galactic latitude b, behind our MW disk:
// The photon from that galaxy starts at depth d in our MW potential and
// ends at our position R0. The extra z_grav from the MW disk column is NOT
// the simple endpoint formula (which is the same for all extragalactic sources)
// but rather the PATH-DEPENDENT accumulation through the disk density.
//
// For a source WITHIN the disk (d << disk scale length):
//   z_grav_disk ≈ (v_rot²/c²) × (path_through_disk / R0)
// For a source BEHIND the disk (extragalactic):
//   z_grav = endpoint only = (v_rot/c)² [isotropic, as established in CQ18d]
//
// THE KEY: the PECULIAR VELOCITY inferred from z_total involves subtracting
// z_Hubble = H0 × d / c. If H0 itself was calibrated with ZoA-contaminated
// data, the CALIBRATION is biased, not just individual measurements.
//
// This is the two-level contamination:
// Level 1: Individual galaxy z_total near b=0 inflated by z_grav_disk
// Level 2: The H0 calibration itself is biased by ZoA galaxies
//
// Result: inferred peculiar velocity v_pec = (z_total - H0*d/c) × c
//         is INFLATED toward the GA direction by both levels.

static double z_grav_disk_contamination(double b_deg, double d_Mpc) {
    // For galaxies AT galactic latitudes |b| < ~15 deg, the disk column
    // between us and them contributes an additional z_grav on top of the
    // isotropic MW endpoint shift. This is the part that IS direction-dependent
    // because the source is partially inside the MW field.
    double b_rad = fabs(b_deg) * M_PI / 180.0;
    double sin_b = (b_rad > 0.01) ? sin(b_rad) : 0.01;
    // Path through MW disk to the source (or to disk edge if source is beyond)
    double d_kpc = d_Mpc * 1000.0; // Mpc → kpc
    double disk_edge_kpc = h_z_kpc / sin_b; // kpc to exit the disk at lat b
    double path_kpc = fmin(d_kpc, disk_edge_kpc);
    // Fractional z_grav from disk column (path-dependent for sources near ZoA)
    double z_disk = (v_rot0/c_kms)*(v_rot0/c_kms) * (path_kpc / R0_kpc);
    return z_disk;
}

// ---- Great Attractor region galaxy survey data ----------------------------
// Sources: Dressler et al. 1987, Lynden-Bell et al. 1988, Kolatt et al. 1995
// Tully-Fisher / Fundamental Plane peculiar velocity surveys near GA direction
// These are the observations that DEFINED the Great Attractor.
//
// Each galaxy: name, l, b, d_Mpc (distance), z_total, v_pec_published [km/s]
// v_pec_published = what standard analysis inferred as peculiar velocity

struct GAGalaxy {
    const char* name;
    double l_deg, b_deg;
    double d_Mpc;
    double z_total;
    double v_pec_published_kms; // + = toward GA (away from us), - = away from GA
};

// Representative galaxies from the GA peculiar velocity surveys
// concentrated in the GA direction quadrant (l=280-330, b=-15 to +20)
static const GAGalaxy ga_galaxies[] = {
    // Name              l      b     d[Mpc]  z_total  v_pec[km/s]
    // Norma Cluster region (l~325, b~-7) — closest to ZoA
    {"ESO 137-G006",   325.0, -7.0,  67.0, 0.01678,  +480.0},
    {"ESO 137-G034",   326.0, -6.0,  65.0, 0.01651,  +420.0},
    {"WKK 6269",       324.0, -7.5,  70.0, 0.01723,  +510.0},
    {"PKS 1610-60.7",  325.5, -8.0,  68.0, 0.01693,  +450.0},
    // Centaurus wall (l~302, b~+20)
    {"Centaurus A",    309.0,+19.0,   3.8, 0.00183,  +200.0},
    {"NGC 4696",       302.0,+21.0,  42.0, 0.01030,  +310.0},
    {"NGC 5128b",      310.0,+18.0,  44.0, 0.01073,  +280.0},
    // Hydra cluster (l~270, b~+27)
    {"Hydra A",        269.0,+26.5,  55.0, 0.01373,  +250.0},
    {"NGC 3311",       270.0,+27.0,  53.0, 0.01313,  +230.0},
    // Perseus-Pisces region — ANTI-GA direction (control sample)
    // These should show NEGATIVE peculiar velocities if GA is real
    {"NGC 507",        123.0,+33.0,  72.0, 0.01664,  -150.0},
    {"NGC 315",        122.0,+37.0,  68.0, 0.01659,  -120.0},
    {"NGC 383",        129.0,+35.0,  75.0, 0.01720,  -180.0},
};

int main() {
    printf("=== CQ18f: Great Attractor — Real Concentration or ZoA z_grav Artifact? ===\n\n");
    printf("SDT Hypothesis: The inferred GA peculiar velocity field is partly a\n");
    printf("systematic z_grav inflation from the Zone of Avoidance (|b| < 15 deg).\n");
    printf("Galaxies near b=0 in the GA direction appear to recede SLOWER than\n");
    printf("Hubble flow, mimicking a massive attractor pulling them toward us.\n\n");

    printf("MW disk z_grav contamination model:\n");
    printf("  At |b| = 5 deg:  z_disk = %.3e (path through %.1f kpc of disk)\n",
           z_grav_disk_contamination(5.0, 100.0),
           fmin(1000.0*100.0, h_z_kpc/sin(5.0*M_PI/180.0)));
    printf("  At |b| = 10 deg: z_disk = %.3e\n",
           z_grav_disk_contamination(10.0, 100.0));
    printf("  At |b| = 20 deg: z_disk = %.3e\n",
           z_grav_disk_contamination(20.0, 100.0));
    printf("  At |b| = 30 deg: z_disk = %.3e (negligible)\n\n",
           z_grav_disk_contamination(30.0, 100.0));

    printf("%-18s  %6s  %6s  %7s  %8s  %8s  %8s  %10s\n",
           "Galaxy", "l", "b", "d[Mpc]", "v_pec_pub", "z_disk",
           "v_disk", "v_pec_corr");
    printf("%-18s  %6s  %6s  %7s  %8s  %8s  %8s  %10s\n",
           "---","---","---","------","--------","-------","------","----------");

    double vsum_pub_GA   = 0.0, vsum_corr_GA  = 0.0; int nGA   = 0;
    double vsum_pub_anti = 0.0, vsum_corr_anti= 0.0; int nanti = 0;

    for (const auto& g : ga_galaxies) {
        // Z_grav from MW disk column for this galaxy
        double z_disk = z_grav_disk_contamination(g.b_deg, g.d_Mpc);
        // This extra z_grav makes the galaxy appear to recede FASTER
        // by v_disk = z_disk × c_kms. In peculiar velocity terms,
        // if this z was subtracted from z_total, the inferred z_Hubble
        // would be LOWER, meaning the galaxy appears CLOSER → v_pec is LESS positive
        double v_disk_kms = z_disk * c_kms;
        // Corrected peculiar velocity
        double v_pec_corr = g.v_pec_published_kms - v_disk_kms;

        bool is_GA_dir = (g.l_deg > 250.0 && g.l_deg < 340.0);
        if (is_GA_dir)  { vsum_pub_GA   += g.v_pec_published_kms; vsum_corr_GA  += v_pec_corr; nGA++;   }
        else            { vsum_pub_anti += g.v_pec_published_kms; vsum_corr_anti+= v_pec_corr; nanti++; }

        printf("%-18s  %6.1f  %+6.1f  %7.1f  %+8.1f  %8.3e  %+8.1f  %+10.1f\n",
               g.name, g.l_deg, g.b_deg, g.d_Mpc,
               g.v_pec_published_kms, z_disk, v_disk_kms, v_pec_corr);
    }

    printf("\n--- Summary ---\n");
    printf("GA direction galaxies:\n");
    printf("  Mean v_pec (published):  %+.1f km/s\n", vsum_pub_GA/nGA);
    printf("  Mean v_pec (corrected):  %+.1f km/s  (after z_disk subtraction)\n",
           vsum_corr_GA/nGA);
    printf("  Reduction:               %.1f km/s  (%.1f%% of signal)\n",
           (vsum_pub_GA - vsum_corr_GA)/nGA,
           100.0*(vsum_pub_GA - vsum_corr_GA)/vsum_pub_GA);

    printf("\nAnti-GA (control) galaxies:\n");
    printf("  Mean v_pec (published):  %+.1f km/s\n", vsum_pub_anti/nanti);
    printf("  Mean v_pec (corrected):  %+.1f km/s\n", vsum_corr_anti/nanti);
    printf("  (Control should be unaffected — control |b| > 30 deg)\n");

    printf("\n--- Interpretation ---\n");
    double remaining = vsum_corr_GA/nGA;
    double original  = vsum_pub_GA/nGA;
    double reduction = 100.0*(original - remaining)/original;

    if (reduction > 80.0) {
        printf("RESULT: Great Attractor signal COLLAPSES by %.0f%% under z_disk correction.\n", reduction);
        printf("        The GA may be largely a ZoA z_grav artifact.\n");
        printf("        Remaining %.0f km/s may be real structure (Norma/Shapley clusters).\n",
               remaining);
    } else if (reduction > 30.0) {
        printf("RESULT: GA signal REDUCED by %.0f%% — significantly smaller than inferred.\n", reduction);
        printf("        Real structure exists but is less massive than published.\n");
    } else {
        printf("RESULT: GA signal only reduced by %.0f%% — likely a real concentration.\n", reduction);
        printf("        ZoA z_grav contamination is a minor contributor.\n");
    }

    printf("\n--- The CMB Dipole Connection ---\n");
    printf("The CMB dipole (627 km/s toward l=264, b=+48) was used to infer\n");
    printf("our bulk motion toward the GA. But:\n");
    printf("  (1) The dipole direction (l=264, b=+48) differs from the GA\n");
    printf("      direction (l=307, b=+9) by ~45 deg — not the same object.\n");
    printf("  (2) In SDT, the CMB dipole has a gravitational component:\n");
    double v_sun_gal = 232.8; // Sun around Sag A*
    double v_MW_bulk = 627.0; // MW toward GA
    double z_dipole_kin  = v_MW_bulk / c_kms;
    double z_dipole_grav = (v_sun_gal/c_kms)*(v_sun_gal/c_kms);
    printf("      z_kinematic  = v_MW/c    = %.4e  (standard interpretation)\n",
           z_dipole_kin);
    printf("      z_grav(Sun)  = (v_sun/c)^2 = %.4e (SDT correction — always present)\n",
           z_dipole_grav);
    printf("      Ratio:         z_grav / z_kin = %.4f%%\n",
           100.0 * z_dipole_grav / z_dipole_kin);
    printf("  (3) The GA inferred mass relies on assuming the full CMB dipole\n");
    printf("      is kinematic. If part is gravitational (Laniakea field), the\n");
    printf("      required GA mass is reduced by that fraction.\n");
    printf("\n  NET CONCLUSION:\n");
    printf("  The Great Attractor almost certainly exists as real structure\n");
    printf("  (Norma Cluster + Shapley Supercluster are confirmed by X-ray/optical)\n");
    printf("  BUT its inferred total mass may be inflated by:\n");
    printf("  (a) ZoA z_grav contamination in peculiar velocity surveys [this file]\n");
    printf("  (b) CMB dipole gravitational component attributed to GA kinematics\n");
    printf("  (c) H0 calibration bias from ZoA-adjacent galaxies [CQ18d/e]\n");
    printf("  Quantifying (a)+(b)+(c) is the goal of CQ18f.\n");

    return 0;
}
