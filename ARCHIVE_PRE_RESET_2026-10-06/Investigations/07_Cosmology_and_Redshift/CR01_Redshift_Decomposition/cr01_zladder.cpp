// =============================================================================
// CQ18e — Cosmological Redshift Gradient Ladder
// Three source classes: SNe Ia (z<0.1), Galaxy Clusters (z<1), Quasars (z>1)
// 100-point graduated decomposition from z=0.001 to z=1, then extended to z=6
// No G. No M.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <vector>
#ifndef M_PI
  static constexpr double M_PI = 3.14159265358979323846;
#endif

static constexpr double c_kms   = 299792.458;
static constexpr double H0_CMB  = 67.4;
static constexpr double H0_SNe  = 73.0;
static constexpr double v_sun   = 232.8;   // km/s, Sun around Sag A*
static constexpr double v_MW    = 627.0;   // km/s, MW toward Great Attractor

// ---- Source type classifications ----
enum class SourceType { SNe_Ia, Galaxy_Cluster, AGN_Quasar, GRB_Host };

const char* type_str(SourceType t) {
    switch(t) {
        case SourceType::SNe_Ia:        return "SNe Ia   ";
        case SourceType::Galaxy_Cluster:return "Gal.Clus.";
        case SourceType::AGN_Quasar:    return "AGN/QSO  ";
        case SourceType::GRB_Host:      return "GRB Host ";
    }
    return "Unknown";
}

// ---- Unified cosmic source record ----
struct CosmicRecord {
    const char*  name;
    SourceType   type;
    double z_total;          // observed total redshift
    double dist_Mpc;         // distance [Mpc] from best available method
    // Observer-frame corrections (our MW)
    double l_deg, b_deg;     // galactic coords of target
    // Source gravitational environment
    double v_rot_host_kms;   // host rotation [km/s]
    double inclination_deg;  // host disk inclination
    double pa_factor;        // LOS position angle factor (-1..+1)
    // AGN-specific: BLR line width (0 if not AGN)
    double delta_v_BLR_kms;  // BLR FWHM [km/s] — for z_grav_BLR = (Δv/c)²
};

// ---- Six-layer decomposition ----
struct ZDecomp {
    double z_star_grav;    // stellar/progenitor gravitational
    double z_galaxy_grav;  // host galaxy gravitational = (v_rot/c)²
    double z_rotation;     // host disk rotation Doppler
    double z_sun;          // Sun's galactic orbit (Sag A*)
    double z_MW_bulk;      // MW bulk motion (Great Attractor)
    double z_BLR_grav;     // AGN BLR gravitational (if applicable)
    double z_cosmo;        // residual
    double H0_apparent;    // derived H0 from residual
};

static double gal_cos(double l1, double b1, double l2, double b2) {
    auto r = [](double d) { return d * M_PI / 180.0; };
    double x1=cos(r(b1))*cos(r(l1)), y1=cos(r(b1))*sin(r(l1)), z1=sin(r(b1));
    double x2=cos(r(b2))*cos(r(l2)), y2=cos(r(b2))*sin(r(l2)), z2=sin(r(b2));
    return x1*x2 + y1*y2 + z1*z2;
}

ZDecomp decompose(const CosmicRecord& s) {
    ZDecomp d{};
    // Layer 1: stellar/progenitor gravity (WD ~10^-6, AGN accretion disk varies)
    d.z_star_grav  = (s.delta_v_BLR_kms > 0.0) ? 0.0 : 1.2e-6;
    // Layer 2: host galaxy gravitational
    d.z_galaxy_grav = (s.v_rot_host_kms / c_kms) * (s.v_rot_host_kms / c_kms);
    // Layer 3: host rotation Doppler
    double inc = s.inclination_deg * M_PI / 180.0;
    d.z_rotation   = s.v_rot_host_kms * sin(inc) * s.pa_factor / c_kms;
    // Layer 4: Sun orbital (Sag A*)
    d.z_sun        = -(v_sun / c_kms) * gal_cos(90.0, 0.0, s.l_deg, s.b_deg);
    // Layer 5: MW bulk (Great Attractor)
    d.z_MW_bulk    = -(v_MW  / c_kms) * gal_cos(276.0, 30.0, s.l_deg, s.b_deg);
    // Layer 6: AGN BLR gravitational redshift
    d.z_BLR_grav   = (s.delta_v_BLR_kms > 0.0)
                     ? (s.delta_v_BLR_kms/c_kms)*(s.delta_v_BLR_kms/c_kms) : 0.0;
    // Residual
    d.z_cosmo = s.z_total - d.z_star_grav - d.z_galaxy_grav
              - d.z_rotation - d.z_sun - d.z_MW_bulk - d.z_BLR_grav;
    d.H0_apparent = (s.dist_Mpc > 0.0) ? d.z_cosmo * c_kms / s.dist_Mpc : 0.0;
    return d;
}

// ============================================================================
// CATALOGUE — Three source classes spanning z = 0.0008 to z = 6.3
// ============================================================================

// --- CLASS A: SNe Ia, z < 0.1 ---
static const CosmicRecord sne[] = {
  {"SN2011fe/M101",    SourceType::SNe_Ia, 0.000804, 6.4,  102.0,+59.8, 210.0,18.0,+0.50, 0.0},
  {"SN2012cg/N4424",   SourceType::SNe_Ia, 0.001458,15.2,  287.0,+74.4, 150.0,65.0,-0.60, 0.0},
  {"SN1998aq/N3982",   SourceType::SNe_Ia, 0.003699,21.9,  149.0,+65.0, 180.0,26.0,+0.40, 0.0},
  {"SN2001el/N1448",   SourceType::SNe_Ia, 0.004610,18.3,  214.0,-57.0, 190.0,75.0,+0.80, 0.0},
  {"SN2007af/N5584",   SourceType::SNe_Ia, 0.005464,22.5,  329.0,+53.0, 200.0,42.0,+0.30, 0.0},
  {"SN2009ig/N1015",   SourceType::SNe_Ia, 0.008726,36.1,  166.0,-64.0, 175.0,35.0,-0.45, 0.0},
  {"SN2002fk/N1309",   SourceType::SNe_Ia, 0.007125,32.5,  184.0,-49.0, 185.0,48.0,+0.55, 0.0},
  {"SN2007sr/N4038",   SourceType::SNe_Ia, 0.005765,21.5,  295.0,+51.0, 165.0,70.0,-0.70, 0.0},
  {"SN1994ae/N3370",   SourceType::SNe_Ia, 0.004267,28.6,  214.0,+35.0, 195.0,55.0,+0.60, 0.0},
  {"SN2012hr/N1448",   SourceType::SNe_Ia, 0.004610,18.3,  214.0,-57.0, 190.0,75.0,-0.80, 0.0},
};

// --- CLASS B: Galaxy Clusters / SDSS Galaxies, z = 0.02 to 0.9 ---
static const CosmicRecord clusters[] = {
  // Abell clusters: well-characterised, known velocity dispersions
  {"Abell 1656 (Coma)",SourceType::Galaxy_Cluster,0.0231, 99.0, 58.1,+88.0, 800.0,30.0,+0.10, 0.0},
  {"Abell 2029",       SourceType::Galaxy_Cluster,0.0773,330.0, 10.5,+44.7, 950.0,40.0,-0.20, 0.0},
  {"Abell 2142",       SourceType::Galaxy_Cluster,0.0909,390.0,  2.4,+47.1, 900.0,35.0,+0.30, 0.0},
  {"Abell 2744",       SourceType::Galaxy_Cluster,0.3080,1290.0,345.3,-59.7,1100.0,50.0,-0.40, 0.0},
  {"Abell 370",        SourceType::Galaxy_Cluster,0.3750,1570.0,167.0,-59.0, 950.0,60.0,+0.50, 0.0},
  {"MACS J0416",       SourceType::Galaxy_Cluster,0.3970,1660.0,181.4,-52.0,1050.0,45.0,-0.35, 0.0},
  {"MACS J0717",       SourceType::Galaxy_Cluster,0.5458,2280.0,179.2,+16.9,1200.0,55.0,+0.25, 0.0},
  {"RXJ1347-1145",     SourceType::Galaxy_Cluster,0.4510,1890.0,316.1,+46.3,1150.0,40.0,-0.60, 0.0},
  {"MS1054-03",        SourceType::Galaxy_Cluster,0.8230,3440.0,264.0,+30.0,1000.0,50.0,+0.45, 0.0},
  {"RDCS1252-2927",    SourceType::Galaxy_Cluster,1.2350,5170.0,295.0,+33.0, 900.0,35.0,-0.55, 0.0},
};

// --- CLASS C: AGN/Quasars, z = 0.003 to 6.3 ---
static const CosmicRecord quasars[] = {
  // Low-z AGN with reverberation mapping
  {"NGC 4151",         SourceType::AGN_Quasar,0.003319,  15.8,155.1,+75.1, 200.0,40.0,+0.20, 5600.0},
  {"NGC 5548",         SourceType::AGN_Quasar,0.017175,  72.0, 31.9,+70.5, 220.0,45.0,-0.30, 5765.0},
  {"3C 273",           SourceType::AGN_Quasar,0.158339, 660.0,289.9,+64.4, 400.0,30.0,+0.50,30000.0},
  // Mid-z quasars (SDSS)
  {"SDSS J0100+2802",  SourceType::AGN_Quasar,6.3258,  28000.0,121.1,-32.5, 500.0,35.0,-0.40,40000.0},
  {"SDSS J1148+5251",  SourceType::AGN_Quasar,6.4189,  28400.0,132.8,+62.8, 480.0,40.0,+0.35,38000.0},
  {"ULAS J1120+0641",  SourceType::AGN_Quasar,7.0842,  31400.0,228.5,+57.4, 510.0,38.0,-0.50,45000.0},
  {"HE 2347-4342",     SourceType::AGN_Quasar,2.885,   12800.0,342.0,-60.0, 350.0,45.0,+0.60,15000.0},
  {"QSO B1422+231",    SourceType::AGN_Quasar,3.620,   16000.0, 47.2,+66.0, 380.0,50.0,-0.45,20000.0},
  {"SDSS J0313-1806",  SourceType::AGN_Quasar,7.6423,  33900.0,186.7,-51.0, 520.0,42.0,+0.30,50000.0},
  // GRB hosts (highest z)
  {"GRB 090423",       SourceType::GRB_Host,  8.2000,  36000.0, 88.5,-24.2, 150.0,60.0,-0.60,    0.0},
};

// ============================================================================
// 100-POINT GRADIENT LADDER: z = 0.001 to 1.0
// Uses average galaxy properties, uniform sky distribution.
// Shows how H0_apparent evolves with z under SDT corrections.
// ============================================================================
static void gradient_ladder() {
    printf("\n");
    printf("=== REDSHIFT GRADIENT LADDER: z=0.001 to z=1.0 (100 points) ===\n");
    printf("Using mean galaxy properties: v_rot=220 km/s, incl=45 deg, isotropic sky\n");
    printf("H0_true = %.1f km/s/Mpc (CMB baseline)\n\n", H0_CMB);
    printf("  %6s  %9s  %9s  %9s  %9s  %9s  %8s  %s\n",
           "z", "z_galgrav", "z_rot", "z_sun", "z_MW", "z_cosmo", "H0_app", "note");
    printf("  %6s  %9s  %9s  %9s  %9s  %9s  %8s\n",
           "------","--------","------","------","-----","-------","------");

    for (int i = 1; i <= 100; i++) {
        double z = i * 0.010;   // 0.01 to 1.0
        // Distance from CMB H0 (what we'd expect in SDT-corrected universe)
        double d_Mpc = z * c_kms / H0_CMB;

        // Average corrections (isotropic sky → mean projections)
        // <|cos(θ)|> = 0.5 for uniform sphere
        double z_gg   = (220.0/c_kms)*(220.0/c_kms);        // always +
        double z_rot  = 220.0*sin(45.0*M_PI/180.0)*0.0/c_kms; // zero mean (random pa)
        double z_sun  = 0.0;   // zero mean over full sky
        double z_MW   = 0.0;   // zero mean over full sky
        // Systematic: if sample clustered near galactic poles (b > 30),
        // cos(b_GA=30, b_target=60) ≈ 0.5 → net z_MW ≈ -0.5×v_MW/c
        double z_MW_systematic = -(v_MW/c_kms) * 0.25; // 25% sky anisotropy estimate

        double z_cosmo_uncorr = z;                          // naive z_cosmo
        double z_cosmo_corr   = z - z_gg - z_MW_systematic; // SDT corrected
        double H0_uncorr = z_cosmo_uncorr * c_kms / d_Mpc;
        double H0_corr   = z_cosmo_corr   * c_kms / d_Mpc;

        // Fractional importance of corrections
        double corr_frac = 100.0 * (z_gg + fabs(z_MW_systematic)) / z;

        const char* note = "";
        if (corr_frac > 10.0)  note = " << CORRECTIONS DOMINANT";
        else if (corr_frac > 1.0) note = " < significant";
        else if (corr_frac > 0.1) note = "  minor";
        else                       note = "  negligible";

        if (i <= 10 || i % 10 == 0) {
            printf("  %6.3f  %9.3e  %9.3e  %9.3e  %9.3e  %9.6f  %8.2f%s\n",
                   z, z_gg, z_rot, z_sun, z_MW_systematic,
                   z_cosmo_corr, H0_corr, note);
        }
    }
    printf("  ...\n");
    printf("  (showing z=0.01-0.10 and every 0.10 thereafter)\n");
}

// ============================================================================
// HIGH-z EXTENSION: z = 1 to 7
// At z > 1, z_grav_BLR dominates over MW kinematic corrections.
// ============================================================================
static void highz_extension() {
    printf("\n=== HIGH-z EXTENSION: z=1 to z=7 (AGN/Quasar regime) ===\n");
    printf("MW corrections now < 0.1%% of z_cosmo — BLR z_grav becomes dominant\n\n");

    // Schematic high-z quasar population
    struct HiZ { double z; double v_BLR_kms; double dist_Gpc; };
    static const HiZ hiz[] = {
        {1.0,  5000.0, 4.41},
        {1.5,  8000.0, 6.30},
        {2.0, 10000.0, 7.87},
        {2.5, 12000.0, 9.10},
        {3.0, 15000.0,10.10},
        {3.5, 18000.0,10.85},
        {4.0, 20000.0,11.44},
        {5.0, 25000.0,12.30},
        {6.0, 30000.0,12.82},
        {7.0, 35000.0,13.14},
    };

    printf("  %5s  %10s  %10s  %10s  %10s  %10s\n",
           "z", "Δv_BLR", "z_BLR_grav", "z_MW(%)", "z_cosmo_corr", "H0_corr");
    printf("  %5s  %10s  %10s  %10s  %10s  %10s\n",
           "---", "--------", "----------", "--------", "------------","-------");

    for (const auto& h : hiz) {
        double z_BLR  = (h.v_BLR_kms/c_kms)*(h.v_BLR_kms/c_kms);
        double z_gg   = (220.0/c_kms)*(220.0/c_kms);
        double z_MW   = (v_MW/c_kms)*0.25; // systematic fraction
        double z_cosmo_corr = h.z - z_BLR - z_gg - z_MW;
        double d_Mpc = h.dist_Gpc * 1000.0;
        double H0_corr = (d_Mpc > 0) ? z_cosmo_corr * c_kms / d_Mpc : 0.0;
        double MW_frac = 100.0 * z_MW / h.z;
        double BLR_frac= 100.0 * z_BLR / h.z;

        printf("  %5.1f  %8.0f km/s  %10.4e  %8.3f%%  %12.6f  %10.2f\n",
               h.z, h.v_BLR_kms, z_BLR, MW_frac, z_cosmo_corr, H0_corr);

        if (BLR_frac > 0.5)
            printf("         BLR z_grav = %.2f%% of z_total — non-negligible!\n", BLR_frac);
    }
}

int main() {
    printf("=== CQ18e: Cosmological Redshift Gradient Ladder ===\n");
    printf("Three source classes: SNe Ia | Galaxy Clusters | AGN/Quasars\n");
    printf("Six-layer decomposition at every redshift\n\n");

    // --- Print each class ---
    auto run_class = [](const CosmicRecord* arr, int n, const char* label) {
        printf("--- %s ---\n", label);
        printf("%-22s  %5s  %9s  %9s  %9s  %9s  %9s  %8s\n",
               "Name", "z_tot", "z_galgrav", "z_rot", "z_sun", "z_MW",
               "z_cosmo", "H0_corr");
        printf("%-22s  %5s  %9s  %9s  %9s  %9s  %9s  %8s\n",
               "---","-----","--------","-----","-----","-----","-------","-------");
        double H0_sum = 0.0; int cnt = 0;
        for (int i = 0; i < n; i++) {
            auto d = decompose(arr[i]);
            if (arr[i].dist_Mpc > 0.0) { H0_sum += d.H0_apparent; cnt++; }
            printf("%-22s  %5.4f  %9.3e  %+9.3e  %+9.3e  %+9.3e  %9.6f  %8.2f\n",
                   arr[i].name, arr[i].z_total,
                   d.z_galaxy_grav, d.z_rotation, d.z_sun, d.z_MW_bulk,
                   d.z_cosmo, d.H0_apparent);
            if (arr[i].delta_v_BLR_kms > 0.0)
                printf("  BLR z_grav = %.4e  (%.2f%% of z_total)\n",
                       d.z_BLR_grav, 100.0*d.z_BLR_grav/arr[i].z_total);
        }
        if (cnt > 0)
            printf("  Mean H0_corrected = %.2f km/s/Mpc  (CMB=67.4, SH0ES=73.0)\n\n",
                   H0_sum/cnt);
    };

    run_class(sne,      sizeof(sne)/sizeof(sne[0]),      "CLASS A: SNe Ia (z < 0.01)");
    run_class(clusters, sizeof(clusters)/sizeof(clusters[0]), "CLASS B: Galaxy Clusters (z = 0.02 to 1.2)");
    run_class(quasars,  sizeof(quasars)/sizeof(quasars[0]),   "CLASS C: AGN/Quasars (z = 0.003 to 7.6)");

    gradient_ladder();
    highz_extension();

    printf("\n=== SDT GRADIENT PREDICTION ===\n");
    printf("If SDT occlusion is the mechanism for z_cosmo:\n");
    printf("  z_cosmo should INCREASE along LOS through denser filaments\n");
    printf("  z_cosmo should DECREASE through cosmic voids\n");
    printf("  The apparent H0 should VARY with sky direction\n");
    printf("  This variation should CORRELATE with 2MASS/SDSS column density\n\n");
    printf("If expansion is the mechanism (Lambda-CDM):\n");
    printf("  z_cosmo should be ISOTROPIC after large-scale structure subtraction\n");
    printf("  H0 should be CONSTANT with direction\n\n");
    printf("The gradient ladder (CQ18e) provides the discriminant.\n");
    printf("Cross-correlate z_cosmo_residual with galaxy density maps → CQ18f.\n");

    return 0;
}
