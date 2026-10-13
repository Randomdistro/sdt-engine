// =============================================================================
// CQ18g_live — Great Attractor Perpendicular Ring Test on REAL 6dFGRS DATA
//
// Input: 6dFGRS peculiar velocity catalogue (Springob et al. 2014)
//        J/MNRAS/445/2677/table1 — 8885 galaxies
//        Columns: RAJ2000, DEJ2000, czgal, log(Dz/DH), e_log(Dz/DH)
//
// The peculiar velocity from log(Dz/DH):
//   v_pec = c * ln(10) * log(Dz/DH) * czgal  [km/s]
//   (first-order approximation valid for czgal << c)
//   More precisely: V_pec ≈ czgal * (1 - 10^log(Dz/DH))
//   Or: log(Dz/DH) > 0 => galaxy is CLOSER than Hubble => positive v_pec (toward us)
//       log(Dz/DH) < 0 => galaxy is FARTHER than Hubble => negative v_pec (away from us)
//
// GA direction: l=276 deg, b=30 deg (Laniakea centroid)
// Perpendicular ring: all galaxies where angle_to_GA = 90 +/- 0.5 deg
//
// Tests:
//   1. Mean v_pec on ring (H0 bias signature)
//   2. cos(2*phi) quadrupole amplitude (tidal/lens signature)
//   3. GA direction vs anti-GA direction comparison (binary existence test)
//
// No G. No M.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#ifndef M_PI
  static constexpr double M_PI = 3.14159265358979323846;
#endif

static constexpr double c_kms   = 299792.458;
static constexpr double l_GA     = 276.0;   // deg
static constexpr double b_GA_deg =  30.0;   // deg

// ---- Vector math -----------------------------------------------------------
struct Vec3 {
    double x, y, z;
    double dot(const Vec3& o) const { return x*o.x + y*o.y + z*o.z; }
    Vec3 cross(const Vec3& o) const {
        return {y*o.z-z*o.y, z*o.x-x*o.z, x*o.y-y*o.x};
    }
    double norm() const { return sqrt(x*x+y*y+z*z); }
    Vec3 normalized() const { double n=norm(); return {x/n,y/n,z/n}; }
    Vec3 operator*(double s) const { return {x*s,y*s,z*s}; }
    Vec3 operator+(const Vec3& o) const { return {x+o.x,y+o.y,z+o.z}; }
};

// Equatorial (RA, Dec) to galactic (l, b) conversion
// Uses IAU 1958 galactic pole: RA_GP=192.85948, Dec_GP=27.12825, l_NCP=122.93192
static void eq_to_gal(double ra_deg, double dec_deg, double& l_deg, double& b_deg) {
    static constexpr double RA_GP  = 192.85948 * M_PI/180.0;
    static constexpr double DEC_GP =  27.12825 * M_PI/180.0;
    static constexpr double L_NCP  = 122.93192 * M_PI/180.0;
    double ra  = ra_deg  * M_PI/180.0;
    double dec = dec_deg * M_PI/180.0;
    double sin_b = sin(dec)*sin(DEC_GP) + cos(dec)*cos(DEC_GP)*cos(ra-RA_GP);
    b_deg = asin(sin_b) * 180.0/M_PI;
    double cos_b = cos(b_deg * M_PI/180.0);
    double sin_l_lncp = cos(dec)*sin(ra-RA_GP)/cos_b;
    double cos_l_lncp = (sin(dec)-sin_b*sin(DEC_GP))/(cos_b*cos(DEC_GP));
    double l_lncp = atan2(sin_l_lncp, cos_l_lncp) * 180.0/M_PI;
    l_deg = l_lncp + L_NCP*180.0/M_PI;
    if (l_deg < 0)   l_deg += 360.0;
    if (l_deg > 360) l_deg -= 360.0;
}

static Vec3 unit_vec(double l_deg, double b_deg) {
    double l = l_deg*M_PI/180.0, b = b_deg*M_PI/180.0;
    return {cos(b)*cos(l), cos(b)*sin(l), sin(b)};
}

// Ring basis vectors (perpendicular to GA)
static Vec3 e_GA, e1_ring, e2_ring;
static void init_ring() {
    e_GA    = unit_vec(l_GA, b_GA_deg);
    Vec3 ez = {0,0,1};
    e1_ring = ez.cross(e_GA).normalized();
    e2_ring = e_GA.cross(e1_ring).normalized();
}

static double ring_phi_deg(double l_deg, double b_deg) {
    Vec3 p = unit_vec(l_deg, b_deg);
    return atan2(p.dot(e2_ring), p.dot(e1_ring)) * 180.0/M_PI;
}

static double angle_to_GA_deg(double l_deg, double b_deg) {
    double d = e_GA.dot(unit_vec(l_deg, b_deg));
    d = fmax(-1.0, fmin(1.0, d));
    return acos(d) * 180.0/M_PI;
}

// ---- Parse one line of 6dFGRS TSV data -------------------------------------
// Format: RAJ2000  DEJ2000  czgal  log(Dz/DH)  e_log(Dz/DH)
// Columns separated by tab or multiple spaces
struct Galaxy6dF {
    double l_deg, b_deg;
    double czgal;          // CMB-frame redshift * c [km/s]
    double logDzDH;        // log10(Dz/DH)
    double e_logDzDH;
    double vpec;           // peculiar velocity [km/s]
    double ang_GA;         // angle from GA [deg]
    double phi;            // ring position angle [deg]
};

static bool parse_line(const char* line, Galaxy6dF& g) {
    if (line[0] == '#' || line[0] == '\n' || line[0] == '\r' || line[0] == ' ' || line[0] == '-')
        return false;
    double ra, dec;
    int czgal;
    double logDzDH, e_logDzDH;
    // Try tab-separated first
    if (sscanf(line, "%lf\t%lf\t%d\t%lf\t%lf",
               &ra, &dec, &czgal, &logDzDH, &e_logDzDH) == 5
        || sscanf(line, "%lf %lf %d %lf %lf",
               &ra, &dec, &czgal, &logDzDH, &e_logDzDH) == 5) {
        double l, b;
        eq_to_gal(ra, dec, l, b);
        g.l_deg      = l;
        g.b_deg      = b;
        g.czgal      = (double)czgal;
        g.logDzDH    = logDzDH;
        g.e_logDzDH  = e_logDzDH;
        // v_pec from Springob et al 2014:
        // log(Dz/DH): if > 0, galaxy is FARTHER than Hubble predicts => receding => v_pec < 0
        // v_pec ≈ czgal * (1 - 10^logDzDH)    [km/s]
        // For small logDzDH: ≈ -czgal * ln(10) * logDzDH (same sign convention)
        // Typical: czgal~10000, logDzDH~0.1 => v_pec ~ -2300 km/s (too large — use ln10 * czgal)
        // Correct linear approximation: v_pec = -czgal * log(10) * logDzDH
        // This gives ~230 km/s at czgal=1000, logDzDH=0.1 — physical
        g.vpec = -(double)czgal * log(10.0) * logDzDH;
        g.ang_GA     = angle_to_GA_deg(l, b);
        g.phi        = ring_phi_deg(l, b);
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    // Path to downloaded 6dFGRS data file
    const char* fname = (argc > 1) ? argv[1]
        : "C:\\Users\\Jimmi\\.gemini\\antigravity\\brain\\0d0c445b-c45f-4f12-91e0-8aec737d4e3e\\.system_generated\\steps\\1481\\content.md";

    FILE* f = fopen(fname, "r");
    if (!f) {
        printf("ERROR: Cannot open %s\n", fname);
        return 1;
    }

    init_ring();

    // Accumulators for directional bins
    // Bin 0: GA direction  (ang < 30 deg)
    // Bin 1: Perp ring     (|ang - 90| < 0.5 deg)
    // Bin 2: Perp ring 5   (|ang - 90| < 5 deg)
    // Bin 3: Anti-GA       (ang > 150 deg)

    struct Bin { double vsum=0, v2sum=0; double cos2sum=0, sin2sum=0;
                 double czsum=0; int n=0;
                 void add(double v, double phi) {
                     vsum+=v; v2sum+=v*v; n++;
                     double ph=phi*M_PI/180.0;
                     cos2sum+=v*cos(2*ph); sin2sum+=v*sin(2*ph);
                 }
    };

    Bin bin_GA, b_ring05, b_ring5, b_antiGA;

    // 360 azimuthal bins around the ring (1 deg each)
    static const int N_PHI = 36;  // 10-deg bins for manageable output
    double phi_vmean[N_PHI]={}, phi_n[N_PHI]={};

    int total = 0;
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        Galaxy6dF g;
        if (!parse_line(line, g)) continue;
        if (g.czgal < 500 || g.czgal > 17000) continue; // quality filter
        total++;

        double ang = g.ang_GA;
        double phi = g.phi;
        double v   = g.vpec;

        if (ang < 30.0)                    bin_GA.add(v, phi);
        if (fabs(ang - 90.0) < 0.5)       b_ring05.add(v, phi);
        if (fabs(ang - 90.0) < 5.0)       b_ring5.add(v, phi);
        if (ang > 150.0)                   b_antiGA.add(v, phi);

        // Azimuthal bin (only for ring ±5 deg)
        if (fabs(ang - 90.0) < 5.0) {
            int pi = (int)((phi + 180.0) / (360.0/N_PHI));
            if (pi >= 0 && pi < N_PHI) {
                phi_vmean[pi] += v;
                phi_n[pi]++;
            }
        }
    }
    fclose(f);

    printf("=== CQ18g LIVE: Great Attractor Perpendicular Ring — REAL 6dFGRS DATA ===\n\n");
    printf("Source: Springob et al. 2014 (6dFGRS peculiar velocity survey)\n");
    printf("Total galaxies loaded: %d\n\n", total);

    printf("GA direction: l=%.0f, b=%.0f\n", l_GA, b_GA_deg);
    printf("Ring phi=0:   l=6.0, b=0.0  (toward galactic bulge)\n");
    printf("Ring phi=90:  l=96.0, b=+60.0  (northern apex — Coma/Ursa Major)\n");
    printf("Ring phi=180: l=186.0, b=0.0  (Perseus/Auriga)\n");
    printf("Ring phi=270: l=276.0, b=-60.0  (Sculptor/Fornax)\n\n");

    auto stats = [](const Bin& b, const char* label) {
        if (b.n == 0) { printf("  %s: no data\n", label); return; }
        double mean = b.vsum / b.n;
        double rms  = sqrt(b.v2sum/b.n - mean*mean);
        double sem  = rms / sqrt((double)b.n);
        double quad = sqrt(b.cos2sum*b.cos2sum + b.sin2sum*b.sin2sum) / b.n;
        double qph  = atan2(b.sin2sum, b.cos2sum) * 90.0/M_PI;
        printf("  %-12s n=%5d  mean=%+8.1f  rms=%6.0f  sem=%6.1f  quad=%6.1f @ phi=%+5.0f deg\n",
               label, b.n, mean, rms, sem, quad, qph);
    };

    printf("--- Directional Bin Statistics ---\n");
    printf("  (v_pec: + = galaxy approaching us / streaming toward observer)\n\n");
    stats(bin_GA,     "GA (ang<30)");
    stats(b_ring05,  "Ring ±0.5");
    stats(b_ring5,   "Ring ±5");
    stats(b_antiGA,  "AntiGA(>150)");

    printf("\n--- Ring Azimuthal Profile (phi bins, 10-deg wide) ---\n");
    printf("  phi_centre  n   mean_vpec\n");
    for (int i = 0; i < N_PHI; i++) {
        if (phi_n[i] > 0) {
            double pc = -180.0 + (i + 0.5) * (360.0/N_PHI);
            printf("  %+9.0f  %3d   %+8.1f\n", pc, (int)phi_n[i],
                   phi_vmean[i]/phi_n[i]);
        }
    }

    printf("\n--- THREE-WAY VERDICT ---\n\n");

    double mean_ring  = (b_ring5.n > 0) ? b_ring5.vsum/b_ring5.n : 0.0;
    double sem_ring   = (b_ring5.n > 0)
        ? sqrt(b_ring5.v2sum/b_ring5.n - mean_ring*mean_ring) / sqrt((double)b_ring5.n)
        : 0.0;
    double quad_ring  = (b_ring5.n > 0)
        ? sqrt(b_ring5.cos2sum*b_ring5.cos2sum + b_ring5.sin2sum*b_ring5.sin2sum)/b_ring5.n
        : 0.0;
    double mean_GA    = (bin_GA.n   > 0) ? bin_GA.vsum/bin_GA.n   : 0.0;
    double mean_anti  = (b_antiGA.n> 0) ? b_antiGA.vsum/b_antiGA.n : 0.0;
    double dipole     = mean_GA - mean_anti;

    printf("TEST 1 — H0 bias (ring mean should be 0 if H0 correct):\n");
    printf("  Ring mean v_pec = %+.1f ± %.1f km/s\n", mean_ring, sem_ring);
    if (fabs(mean_ring) > 2.0*sem_ring)
        printf("  => SIGNIFICANT non-zero mean — H0 bias or systematic present\n");
    else
        printf("  => Ring mean consistent with zero — H0 may be correct\n");

    printf("\nTEST 2 — GA binary existence (kinematic dipole):\n");
    printf("  GA mean    = %+.1f km/s\n", mean_GA);
    printf("  Anti-GA    = %+.1f km/s\n", mean_anti);
    printf("  Dipole     = %+.1f km/s\n", dipole);
    if (dipole > 150.0)
        printf("  => SIGNIFICANT dipole — GA kinematic signal present\n");
    else if (dipole > 50.0)
        printf("  => Marginal dipole — weak GA signal\n");
    else
        printf("  => No significant dipole — GA may not exist as kinematic entity\n");

    printf("\nTEST 3 — SDT tidal quadrupole:\n");
    printf("  Ring quadrupole amplitude = %.1f km/s\n", quad_ring);
    if (quad_ring > 50.0)
        printf("  => Significant quadrupole — tidal/lens field present\n");
    else
        printf("  => No significant quadrupole\n");

    printf("\n=== CONCLUSION ===\n");
    if (dipole > 150.0 && fabs(mean_ring) < sem_ring)
        printf("Great Attractor EXISTS as a kinematic entity. H0 calibration is clean.\n");
    else if (fabs(mean_ring) > 2.0*sem_ring && dipole < 100.0)
        printf("Great Attractor signal is H0 ARTIFACT. Ring is not silent.\n");
    else if (quad_ring > 50.0)
        printf("Tidal/gravitational field present. GA exists as field centre, not point mass.\n");
    else
        printf("Inconclusive — larger sample or wider ring needed.\n");

    return 0;
}
