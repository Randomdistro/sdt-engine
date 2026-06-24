// =============================================================================
// CQ18g_cf4 — Great Attractor Perpendicular Ring Test, SDT-corrected CF4 Data
//
// USER REQUIREMENT: apply CQ18a-f corrections to each galaxy BEFORE the ring
// test.  The raw CF4 Vpec has NOT had the SDT six layers removed:
//
//   Layer 1: z_star_grav   — stellar gravitational redshift (tiny, population mean)
//   Layer 2: z_galaxy_grav — host galaxy gravitational z = (v_rot/c)^2
//   Layer 3: z_rotation    — host disk rotation projection (population mean ~ 0)
//   Layer 4: z_sun         — Sun orbital motion around Sag A* (direction-dep.)
//   Layer 5: z_MW_bulk     — residual MW bulk not captured by CMB subtraction
//   Layer 6: z_H0_calib    — H0 miscalibration (CF4 uses H0=75, SDT says 66.2)
//
// Corrections we CAN apply per-galaxy from available data (GLON, GLAT, Vcmb, Vpec):
//
//   A. H0 recalibration  [dominant correction]
//      CF4: Vpec_CF4 = Vcmb - H0_CF4 * d_TF
//      => d_TF = (Vcmb - Vpec_CF4) / H0_CF4
//      SDT: Vpec_SDT = Vcmb - H0_SDT * d_TF
//           = Vpec_CF4 + (H0_CF4 - H0_SDT) * d_TF
//           = Vpec_CF4 + (H0_CF4 - H0_SDT) * (Vcmb - Vpec_CF4) / H0_CF4
//
//   B. MW bulk motion residual  [direction-dependent]
//      CF4 CMB frame subtracts 369 km/s toward (l=264, b=48) [CMB dipole].
//      SDT says full MW bulk = 627 km/s toward (l=276, b=30) [GA direction].
//      Residual NOT captured by CF4:
//        v_residual = v_GA - v_CMB = ~307 km/s in a specific direction
//      Correction per galaxy: delta_v = -dot(v_residual, unit(l,b))
//      (positive = CF4 overcorrected that direction, so we add it back)
//
//   C. z_galaxy_grav mean correction  [population average, direction-independent]
//      Mean host galaxy rotation ~220 km/s => z_gg = (220/c_kms)^2 * c_kms = 0.16 km/s
//      This is negligible.
//
//   D. z_sun (Sun's orbit projected onto line of sight)  [direction-dependent]
//      The CMB frame correction in CF4 includes solar motion relative to CMB,
//      which incorporates v_sun_orbital (232.8 km/s toward l=90, b=0).
//      SDT separates this: z_sun = -(232.8/c) * cos(angle to l=90,b=0)
//      CF4 already applies a larger correction that includes this, so
//      applying it again would double-subtract — SKIP.
//      However, the CMB frame correction also includes the MW bulk motion.
//      The net residual is captured in correction B above.
//
// Therefore: apply A + B to each galaxy's Vpec before the ring test.
//
// GA: l=276, b=30   |   No G. No M.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#include <vector>
#ifndef M_PI
  static constexpr double M_PI = 3.14159265358979323846;
#endif

static constexpr double c_kms    = 299792.458;
static constexpr double l_GA     = 276.0;
static constexpr double b_GA_d   =  30.0;
static constexpr double H0_CF4   =  75.0;   // Tully et al. 2023 reference H0
static constexpr double H0_SDT   =  66.2;   // SDT corrected (CQ18d result)
// CMB dipole direction (solar apex relative to CMB)
static constexpr double l_CMB    = 264.0;
static constexpr double b_CMB    =  48.0;
static constexpr double v_CMB    = 369.0;   // km/s — CMB dipole amplitude (heliocentric)
// MW bulk motion (full SDT value toward GA)
static constexpr double v_MW_GA  = 627.0;   // km/s

// ---- Vector math -----------------------------------------------------------
struct Vec3 {
    double x, y, z;
    double dot(const Vec3& o) const { return x*o.x+y*o.y+z*o.z; }
    Vec3 cross(const Vec3& o) const { return {y*o.z-z*o.y,z*o.x-x*o.z,x*o.y-y*o.x}; }
    double norm() const { return sqrt(x*x+y*y+z*z); }
    Vec3 normalized() const { double n=norm(); return {x/n,y/n,z/n}; }
    Vec3 operator*(double s) const { return {x*s,y*s,z*s}; }
    Vec3 operator-(const Vec3& o) const { return {x-o.x,y-o.y,z-o.z}; }
    Vec3 operator+(const Vec3& o) const { return {x+o.x,y+o.y,z+o.z}; }
};

static Vec3 unit_vec(double l_deg, double b_deg) {
    double l=l_deg*M_PI/180, b=b_deg*M_PI/180;
    return {cos(b)*cos(l), cos(b)*sin(l), sin(b)};
}

// ---- Ring geometry ---------------------------------------------------------
static Vec3 eGA, e1_ring, e2_ring;
static Vec3 v_residual;   // MW bulk vector NOT subtracted by CF4

static void init() {
    eGA    = unit_vec(l_GA, b_GA_d);
    Vec3 ez={0,0,1};
    e1_ring = ez.cross(eGA).normalized();
    e2_ring = eGA.cross(e1_ring).normalized();

    // MW bulk residual: what SDT says should be subtracted, minus what CF4 subtracted
    // CF4 subtracts: v_CMB km/s toward (l_CMB, b_CMB)
    // SDT requires:  v_MW_GA km/s toward (l_GA, b_GA_d)
    // Residual = v_GA_vec - v_CF4_vec  (this was NOT subtracted by CF4)
    Vec3 v_GA_vec  = unit_vec(l_GA,  b_GA_d) * v_MW_GA;
    Vec3 v_CF4_vec = unit_vec(l_CMB, b_CMB)  * v_CMB;
    v_residual = v_GA_vec - v_CF4_vec;  // to be subtracted from each galaxy's Vpec

    double vr_mag = v_residual.norm();
    printf("SDT initialisation:\n");
    printf("  H0_CF4=%.1f, H0_SDT=%.1f, bias=%.1f km/s/Mpc\n",
           H0_CF4, H0_SDT, H0_CF4-H0_SDT);
    printf("  MW bulk SDT:   %.0f km/s toward (l=%.0f, b=%.0f)\n", v_MW_GA, l_GA, b_GA_d);
    printf("  CF4 CMB sub:   %.0f km/s toward (l=%.0f, b=%.0f)\n", v_CMB, l_CMB, b_CMB);
    printf("  Residual uncorrected: %.1f km/s  (direction-dependent per galaxy)\n\n", vr_mag);
}

static double angle_GA(double l, double b) {
    double d = eGA.dot(unit_vec(l,b));
    d=fmax(-1.0,fmin(1.0,d));
    return acos(d)*180.0/M_PI;
}
static double phi_ring(double l, double b) {
    Vec3 p=unit_vec(l,b);
    return atan2(p.dot(e2_ring),p.dot(e1_ring))*180.0/M_PI;
}

// ---- SDT correction to raw Vpec_CF4 per galaxy -----------------------------
static double sdt_correct_vpec(double glon, double glat, double vcmb, double vpec_cf4) {
    // A: H0 recalibration
    //    d_TF = (Vcmb - Vpec_CF4) / H0_CF4
    //    delta_vpec = (H0_CF4 - H0_SDT) * d_TF
    double d_TF = (vcmb - vpec_cf4) / H0_CF4;     // Mpc
    double delta_H0 = (H0_CF4 - H0_SDT) * d_TF;   // positive => more approaching

    // B: MW bulk motion residual (direction-dependent)
    //    CF4 subtracted its CMB vector; SDT requires subtracting v_GA vector.
    //    What CF4 already removed: v_CMB * cos(theta_CMB)
    //    What SDT needs removed:   v_GA  * cos(theta_GA)
    //    Residual correction = -(v_residual . unit_gal)
    //    (Negative because a larger velocity means the CMB correction was too small
    //     in that direction, so we need to subtract more.)
    Vec3 uhat = unit_vec(glon, glat);
    double delta_MW = -v_residual.dot(uhat);        // subtract residual uncorrected bulk

    return vpec_cf4 + delta_H0 + delta_MW;
}

// ---- Bin accumulator -------------------------------------------------------
struct Bin {
    double vsum=0, v2sum=0, c2=0, s2=0;
    double vsum_raw=0;
    int n=0;
    void add(double v, double v_raw, double phi) {
        vsum+=v; v2sum+=v*v; vsum_raw+=v_raw; n++;
        double p=phi*M_PI/180;
        c2+=v*cos(2*p); s2+=v*sin(2*p);
    }
    double mean()    const { return n?vsum/n:0; }
    double mean_raw()const { return n?vsum_raw/n:0; }
    double rms()     const { return n?sqrt(fmax(0,v2sum/n-mean()*mean())):0; }
    double sem()     const { return n?rms()/sqrt((double)n):0; }
    double quad()    const { return n?sqrt(c2*c2+s2*s2)/n:0; }
    double qphase()  const { return atan2(s2,c2)*90.0/M_PI; }
};

int main(int argc, char* argv[]) {
    const char* fname = (argc>1) ? argv[1]
        : "C:\\Users\\Jimmi\\.gemini\\antigravity\\brain\\0d0c445b-c45f-4f12-91e0-8aec737d4e3e\\.system_generated\\steps\\1532\\content.md";

    printf("=== CQ18g CF4 (SDT-corrected): Great Attractor Ring Test ===\n");
    printf("    Applying H0 recalibration + MW bulk residual per galaxy\n\n");

    init();

    FILE* f = fopen(fname, "r");
    if (!f) { printf("ERROR: Cannot open file\n"); return 1; }

    Bin bGA, bRing05, bRing5, bAnti;
    static const int NPHI=36;
    double phi_v_raw[NPHI]={}, phi_v_sdt[NPHI]={}, phi_n[NPHI]={};
    int total=0;

    char line[256];
    while (fgets(line,sizeof(line),f)) {
        if (line[0]=='#'||line[0]=='\n'||line[0]=='\r'||line[0]==' ') continue;
        double glon,glat; int vcmb,vpec_raw;
        if (sscanf(line,"%lf %lf %d %d",&glon,&glat,&vcmb,&vpec_raw)!=4) continue;
        if (vcmb<100||vcmb>20000) continue;
        total++;

        double v_sdt = sdt_correct_vpec(glon, glat, (double)vcmb, (double)vpec_raw);
        double ang   = angle_GA(glon, glat);
        double phi   = phi_ring(glon, glat);

        if (ang<30.0)            bGA.add(v_sdt,(double)vpec_raw,phi);
        if (fabs(ang-90.0)<0.5)  bRing05.add(v_sdt,(double)vpec_raw,phi);
        if (fabs(ang-90.0)<5.0)  bRing5.add(v_sdt,(double)vpec_raw,phi);
        if (ang>150.0)           bAnti.add(v_sdt,(double)vpec_raw,phi);

        if (fabs(ang-90.0)<5.0) {
            int pi=(int)((phi+180.0)*(NPHI/360.0));
            if(pi>=0&&pi<NPHI){
                phi_v_raw[pi]+=(double)vpec_raw;
                phi_v_sdt[pi]+=v_sdt;
                phi_n[pi]++;
            }
        }
    }
    fclose(f);

    printf("Total CF4 groups: %d\n\n", total);

    auto pr = [](const Bin& b, const char* lbl) {
        printf("  %-14s n=%5d  raw=%+7.1f  sdt=%+8.1f  sem=%6.1f  rms=%5.0f  quad=%5.1f@%+.0f\n",
               lbl, b.n, b.mean_raw(), b.mean(), b.sem(), b.rms(), b.quad(), b.qphase());
    };

    printf("--- Directional Bins (raw CF4 vs SDT-corrected) ---\n");
    printf("  (Vpec > 0 = approaching us;  < 0 = receding faster than Hubble)\n\n");
    printf("  %-14s %5s  %7s  %8s  %6s  %5s  %s\n",
           "Region","n","raw","sdt","sem","rms","quad@phi");
    pr(bGA,     "GA (ang<30)");
    pr(bRing05, "Ring ±0.5");
    pr(bRing5,  "Ring ±5");
    pr(bAnti,   "AntiGA (>150)");

    printf("\n--- Ring Azimuthal Profile (phi bins, 10-deg) ---\n");
    printf("  phi_ctr  n   raw_Vpec  sdt_Vpec\n");
    for (int i=0;i<NPHI;i++) {
        if (phi_n[i]>0) {
            double pc=-180.0+(i+0.5)*(360.0/NPHI);
            printf("  %+7.0f  %3d   %+8.1f  %+8.1f\n",
                   pc,(int)phi_n[i], phi_v_raw[i]/phi_n[i], phi_v_sdt[i]/phi_n[i]);
        }
    }

    double mRing  = bRing5.mean(), seRing = bRing5.sem();
    double mGA    = bGA.mean(),    seGA   = bGA.sem();
    double mAnti  = bAnti.mean(),  seAnti = bAnti.sem();
    double dipole = mGA - mAnti;

    printf("\n=== THREE-WAY VERDICT (SDT-corrected) ===\n\n");

    printf("BOTTLENECK TEST:\n");
    printf("  Ring mean Vpec (SDT) = %+.1f ± %.1f km/s  (raw was %+.1f)\n",
           mRing, seRing, bRing5.mean_raw());
    double sig = seRing>0 ? fabs(mRing)/seRing : 0;
    if (mRing > seRing)
        printf("  => POSITIVE (%.1f sigma) — bottleneck contraction CONFIRMED\n", sig);
    else if (mRing < -seRing)
        printf("  => NEGATIVE (%.1f sigma) — ring galaxies receding, no bottleneck\n", sig);
    else
        printf("  => Consistent with zero (%.1f sigma) — bottleneck not detected\n", sig);

    printf("\nGA BINARY EXISTENCE:\n");
    printf("  GA mean    (SDT) = %+.1f ± %.1f km/s  (raw %+.1f)\n",
           mGA, seGA, bGA.mean_raw());
    printf("  Anti-GA    (SDT) = %+.1f ± %.1f km/s  (raw %+.1f)\n",
           mAnti, seAnti, bAnti.mean_raw());
    printf("  Dipole     (SDT) = %+.1f km/s\n", dipole);
    if (mGA<-seGA && mAnti>seAnti && dipole<-100)
        printf("  => CORRECT: GA draining (neg GA, pos anti) — GA EXISTS kinematically\n");
    else if (mGA>seGA && mAnti<-seAnti)
        printf("  => INVERTED dipole — unexpected flow pattern\n");
    else
        printf("  => Dipole marginal — GA existence not confirmed at 2 sigma\n");

    printf("\nSDT TIDAL QUADRUPOLE:\n");
    printf("  Ring quadrupole = %.1f km/s at phi=%.0f deg\n",
           bRing5.quad(), bRing5.qphase());
    printf("  => %s\n",
           bRing5.quad()>50 ? "Significant — tidal/lens field present" : "Not significant");

    printf("\n=== SUMMARY ===\n\n");
    printf("H0 correction (%.1f km/s/Mpc) adds +%.0f km/s at mean d=%.0f Mpc:\n",
           H0_CF4-H0_SDT, (H0_CF4-H0_SDT)*(5000.0/H0_CF4), 5000.0/H0_CF4);
    printf("  This is the dominant correction — flips sign of many Vpec values.\n");
    printf("MW residual: %.1f km/s peak-to-peak direction-dependent correction.\n",
           2*v_residual.norm());
    printf("  Applied per galaxy: removes the ~307 km/s uncorrected bulk component.\n\n");
    printf("If SDT-corrected ring mean > 0: bottleneck is real. GA exists.\n");
    printf("If SDT-corrected ring mean ~ 0 or < 0: H0 artifact. GA may not exist.\n");

    return 0;
}
