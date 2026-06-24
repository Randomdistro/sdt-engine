// =============================================================================
// CQ18h — GA Cone/Shell Velocity Map (SDT-corrected CF4 data)
//
// 2D map: angle_from_GA × Vcmb_shell → mean Vpec_SDT
//
// Standard model GA prediction:
//   Fore (0-45°):  mono-increasing redshift with distance. Flip sign ~80Mpc (GA dist).
//   Perp (90°):    co-movement convergence (positive Vpec) — max co-moving zone.
//   Rear (135-180°): we run away from them — positive Vpec (slower redshift).
//
// SDT prediction:
//   Column pressure builds monotonically toward GA.
//   No sign flip — just monotonic z_grav increase along axis.
//   Rotation component (sin(phi)) in the perp ring = angular momentum of accretion.
//
// GA: l=276, b=30.  H0_CF4=75 -> H0_SDT=66.2.  MW bulk residual 308 km/s.
// =============================================================================

#define _USE_MATH_DEFINES
#include <cstdio>
#include <cmath>
#ifndef M_PI
  static constexpr double M_PI = 3.14159265358979323846;
#endif

static constexpr double c_kms   = 299792.458;
static constexpr double l_GA    = 276.0, b_GA_d = 30.0;
static constexpr double H0_CF4  = 75.0,  H0_SDT = 66.2;
static constexpr double l_CMB   = 264.0, b_CMB  = 48.0, v_CMB = 369.0;
static constexpr double v_MW_GA = 627.0;

struct Vec3 {
    double x,y,z;
    double dot(const Vec3& o) const {return x*o.x+y*o.y+z*o.z;}
    Vec3 cross(const Vec3& o) const {return {y*o.z-z*o.y,z*o.x-x*o.z,x*o.y-y*o.x};}
    double norm() const {return sqrt(x*x+y*y+z*z);}
    Vec3 normalized() const {double n=norm();return {x/n,y/n,z/n};}
    Vec3 operator*(double s) const {return {x*s,y*s,z*s};}
    Vec3 operator-(const Vec3& o) const {return {x-o.x,y-o.y,z-o.z};}
};
static Vec3 uv(double l,double b){
    double lr=l*M_PI/180,br=b*M_PI/180;
    return {cos(br)*cos(lr),cos(br)*sin(lr),sin(br)};
}

static Vec3 eGA, e1r, e2r, v_res;
static void init(){
    eGA = uv(l_GA,b_GA_d);
    Vec3 ez={0,0,1};
    e1r = ez.cross(eGA).normalized();
    e2r = eGA.cross(e1r).normalized();
    v_res = uv(l_GA,b_GA_d)*v_MW_GA - uv(l_CMB,b_CMB)*v_CMB;
}

static double ang_GA(double l,double b){
    double d=eGA.dot(uv(l,b)); d=fmax(-1,fmin(1,d));
    return acos(d)*180/M_PI;
}
static double phi_r(double l,double b){
    Vec3 p=uv(l,b);
    return atan2(p.dot(e2r),p.dot(e1r))*180/M_PI;
}
static double sdt_vpec(double gl,double gb,double vcmb,double vp){
    double dTF=(vcmb-vp)/H0_CF4;
    double dH0=(H0_CF4-H0_SDT)*dTF;
    double dMW=-v_res.dot(uv(gl,gb));
    return vp+dH0+dMW;
}

// Angular bins (deg from GA)
static const int NA=9;
static const double ANG_LO[NA]={  0, 10, 20, 40, 60, 80, 90,120,150};
static const double ANG_HI[NA]={ 10, 20, 40, 60, 80, 90,100,150,180};
static const char*  ANG_LBL[NA]={"0-10","10-20","20-40","40-60",
                                  "60-80","80-90","90-100","100-150","150-180"};

// Distance bins (Vcmb km/s) — GA at ~5300 km/s with H0_SDT
static const int ND=7;
static const double DBIN[ND+1]={0,2000,4000,6000,8000,11000,15000,20000};

struct Cell { double vs=0; int n=0; void add(double v){vs+=v;n++;} double mean()const{return n?vs/n:0;} };
static Cell grid[NA][ND];

// Perpendicular ring (85-95°) split into 4 phi quadrants
struct PhiBin { double vs=0,vs_raw=0; int n=0;
    void add(double v,double vr){vs+=v;vs_raw+=vr;n++;}
    double mean()const{return n?vs/n:0;}
    double raw() const{return n?vs_raw/n:0;}
};
static PhiBin phi4[4]; // N/E/S/W quadrants at 90-deg ring

int main(int argc,char* argv[]){
    const char* fn=(argc>1)?argv[1]
        :"C:\\Users\\Jimmi\\.gemini\\antigravity\\brain\\0d0c445b-c45f-4f12-91e0-8aec737d4e3e\\.system_generated\\steps\\1532\\content.md";

    init();
    printf("=== CQ18h: GA Cone-Shell Velocity Map (CF4, SDT-corrected) ===\n\n");
    printf("GA @ l=%.0f b=%.0f  |  H0: %.0f->%.0f km/s/Mpc  |  MW_res=%.0f km/s\n\n",
           l_GA,b_GA_d,H0_CF4,H0_SDT,v_res.norm());

    FILE* f=fopen(fn,"r"); if(!f){printf("ERR\n");return 1;}
    int total=0;
    char line[256];
    while(fgets(line,256,f)){
        if(line[0]=='#'||line[0]=='\n'||line[0]=='\r'||line[0]==' ') continue;
        double gl,gb; int vcmb,vp;
        if(sscanf(line,"%lf %lf %d %d",&gl,&gb,&vcmb,&vp)!=4) continue;
        if(vcmb<100||vcmb>20000) continue;
        total++;
        double ang=ang_GA(gl,gb);
        double vs=sdt_vpec(gl,gb,(double)vcmb,(double)vp);
        // angular bin
        for(int a=0;a<NA;a++){
            if(ang>=ANG_LO[a]&&ang<ANG_HI[a]){
                // distance bin
                for(int d=0;d<ND;d++){
                    if(vcmb>=DBIN[d]&&vcmb<DBIN[d+1]){
                        grid[a][d].add(vs); break;
                    }
                }
                break;
            }
        }
        // phi quadrant at perp ring
        if(ang>=85&&ang<95){
            double phi=phi_r(gl,gb);
            // N=phi[-45,45) GA-equatorial crossing, E=[45,135), S=[135,225)/[-135,-45), W=[-135,-45)
            int qi;
            if(phi>=-45&&phi<45)      qi=0; // "north" = toward galactic equator crossing l=6
            else if(phi>=45&&phi<135) qi=1; // "east"  = toward northern apex l=96,b=60
            else if(phi>=-135&&phi<-45) qi=3; // "west" = toward southern apex
            else                      qi=2; // "south" = toward anti-equator l=186
            phi4[qi].add(vs,(double)vp);
        }
    }
    fclose(f);
    printf("Total groups: %d\n\n",total);

    // ---- 2D table ----
    printf("=== 2D MAP: rows=angle_from_GA, cols=Vcmb_shell [km/s] ===\n");
    printf("(cell = mean SDT-corrected Vpec [km/s], +approaching -receding)\n\n");
    printf("%-10s","ang\\Vcmb");
    for(int d=0;d<ND;d++) printf(" %8.0f-%.0f",DBIN[d],DBIN[d+1]);
    printf("\n");
    for(int a=0;a<NA;a++){
        printf("%-10s",ANG_LBL[a]);
        for(int d=0;d<ND;d++){
            if(grid[a][d].n>0)
                printf("  %+7.0f(%-3d)",grid[a][d].mean(),grid[a][d].n);
            else
                printf("  %10s","---");
        }
        printf("\n");
    }

    // ---- Radial profile: fore vs rear ----
    printf("\n=== RADIAL PROFILES: Fore (0-10°) vs Rear (150-180°) ===\n");
    printf("Distance prediction — standard GA:\n");
    printf("  Fore: increasingly negative (redshift) until GA dist, then sign flip\n");
    printf("  Rear: positive throughout (we run away from them)\n\n");
    printf("%-15s  %10s  %10s\n","Vcmb_shell","Fore_0-10","Rear_150-180");
    for(int d=0;d<ND;d++){
        printf("  %5.0f-%5.0f    ",DBIN[d],DBIN[d+1]);
        if(grid[0][d].n) printf("  %+7.0f(%-3d)",grid[0][d].mean(),grid[0][d].n);
        else              printf("  %10s","---");
        if(grid[8][d].n) printf("  %+7.0f(%-3d)",grid[8][d].mean(),grid[8][d].n);
        else              printf("  %10s","---");
        printf("\n");
    }

    // ---- Perpendicular ring 4-quadrant phi split ----
    printf("\n=== PERPENDICULAR RING (85-95° from GA) — 4 PHI QUADRANTS ===\n");
    printf("Looking for rotation signature (sin(phi) dipole = angular momentum)\n\n");
    static const char* PN[4]={"phi=[-45, 45) l~6,b~0  (bulge-side)",
                               "phi=[45,135)  l~96,b~60 (Coma-side)",
                               "phi=[135,225) l~186,b~0 (Perseus-side)",
                               "phi=[-135,-45) l~276,b~-60 (Sculptor-side)"};
    double vs_EW=0, vs_NS=0; // asymmetry check
    for(int q=0;q<4;q++){
        printf("  Q%d %s\n     n=%d  raw=%+.0f  sdt=%+.0f km/s\n",
               q,PN[q],phi4[q].n,phi4[q].raw(),phi4[q].mean());
        if(q==0||q==2) vs_NS+=phi4[q].mean()*(q==0?1:-1);
        if(q==1||q==3) vs_EW+=phi4[q].mean()*(q==1?1:-1);
    }
    printf("\n  N-S asymmetry (rotation trace): %+.0f km/s\n", vs_NS);
    printf("  E-W asymmetry (rotation trace): %+.0f km/s\n", vs_EW);
    if(fabs(vs_NS)>100||fabs(vs_EW)>100)
        printf("  => Significant quadrant asymmetry — ROTATION COMPONENT PRESENT\n");
    else
        printf("  => Quadrant asymmetry small — no clear rotation\n");

    printf("\n=== SIGN-FLIP SCAN (fore cone 0-10°) ===\n");
    printf("GA at ~%.0f Mpc = ~%.0f km/s Vcmb\n", 80.0, 80.0*H0_SDT);
    printf("Standard model: Vpec should be negative (redshift) approaching GA dist,\n");
    printf("then FLIP to positive (receding from us = receding faster than Hubble)\n");
    printf("at the GA itself (objects now on the far side being pulled toward GA\n");
    printf("away from us at increasing speed).\n\n");
    bool flipped=false;
    double prev_sign=0;
    for(int d=0;d<ND;d++){
        if(grid[0][d].n<3) continue;
        double m=grid[0][d].mean();
        double mid=(DBIN[d]+DBIN[d+1])/2;
        printf("  d~%.0f km/s (~%.0f Mpc): Vpec=%+.0f km/s [n=%d]\n",
               mid, mid/H0_SDT, m, grid[0][d].n);
        if(prev_sign!=0 && prev_sign*m<0 && !flipped){
            printf("  *** SIGN FLIP HERE at ~%.0f Mpc ***\n", mid/H0_SDT);
            flipped=true;
        }
        prev_sign=(m>0?1:-1);
    }
    if(!flipped) printf("  No sign flip detected in fore cone.\n");

    printf("\nSDT interpretation: monotonic column pressure — no flip expected.\n");
    printf("If no flip found: SDT signature. If flip at ~80 Mpc: standard GA.\n");

    return 0;
}
