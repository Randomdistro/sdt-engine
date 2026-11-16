// =====================================================================
//  GD05 (twin-regime): Galaxy Rotation Curves — Bulge (+) Disk (+) Gas
//  ---------------------------------------------------------------------
//  Treats a galaxy as TWO physical regimes with DIFFERENT SDT laws,
//  per the twin-regime architecture in galactic.hpp (regime_bulge /
//  regime_disk, sourced from CQ20d/CQ20g):
//
//    BULGE -> SPHERICAL GRAVITATION.  v^2 = c^2 * koppa_enc / R.
//             SDT koppa == G*M/c^2, so this law equals Newtonian
//             spheroid gravity. SPARC's decomposed Vbul(r) already IS
//             the SDT spherical-regime prediction (x stellar M/L). The
//             same koppa law nails the solar system (Mercury, GOM04).
//
//    DISK  -> LINE / ECLIPSE OCCLUSION. The flattened disk does NOT obey
//             spherical gravity; its contribution comes from an SDT
//             occlusion law. Two engine variants are tested:
//               M1 eclipse : regime_disk::v_disk_from_koppa
//               M2 bidir   : c*sqrt((K_int+K_ext)/R) on the disk field
//
//    GAS   -> measured baryonic component Vgas(r) (thin HI disk).
//
//  Combined in quadrature (SPARC sign convention v*|v|):
//    M0 Newtonian : Yd*Vdisk|Vdisk| + Yb*Vbul|Vbul| + Vgas|Vgas|
//    M1 twin      : Yb*Vbul|Vbul| + Vgas|Vgas| + v_occl^2
//    M2 twin      : Yb*Vbul|Vbul| + Vgas|Vgas| + v_bidir^2
//
//  Data (real, published SPARC; Lelli+2016, AJ 152, 157):
//    sparc_rotmod.csv  - per-radius decomposition (Rotmod_LTG bundle)
//    sparc_175.csv     - per-galaxy M_bar, h_R (master table)
//
//  Author: SDT Canonical Engine — James Christopher Tyndall, Melbourne
// =====================================================================

#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <sdt/galactic.hpp>

namespace G = sdt::galactic;
namespace B = sdt::laws::bridge;

// SPARC fiducial mass-to-light ratios at 3.6 um (Lelli+2016):
static constexpr double Y_DISK = 0.5;   // disk stellar M/L
static constexpr double Y_BUL  = 0.7;   // bulge stellar M/L
static constexpr double pc_m   = 3.085677581e16;
static constexpr double kpc_m  = 3.085677581e19;
static constexpr double PI_    = 3.14159265358979323846;
static constexpr double TWO_PI = 2.0 * PI_;
static constexpr double C_LIGHT= 299792458.0;          // [m/s]

// ---------------------------------------------------------------------
//  M3 disk law: 1/r^3 transverse-gradient (line-occlusion) kernel.
//
//  SDT convergence-depth field of a source: z(r) = koppa/r. Its TRANSVERSE
//  gradient is grad_perp z = koppa * b / r^3  (GOM01 line 449). Integrating
//  this 1/r^3 kernel along an extended line at impact parameter b gives
//      int (b / r^3) dl = 2 / b   (GOM01: the 4koppa/b lensing result).
//  A flattened disk presents its baryons as such a radial occlusion LINE,
//  not a point. So the in-plane centripetal acceleration goes as 1/R:
//      a(R) = c^2 * koppa_disk * f_enc(R) / (h_R * R)
//  and therefore the rotation velocity SATURATES to a constant:
//      v^2(R) = a(R) * R = c^2 * koppa_disk * f_enc(R) / h_R   ->  FLAT.
//
//  Contrast with the spherical/enclosed law v^2 = c^2*koppa_enc/R, which
//  necessarily DECLINES. The only change is /R (point, 1/r^2) -> /h_R
//  (line, 1/r^3 integrated). h_R is measured geometry; koppa_disk = G*M/c^2
//  is parameter-free. No fitted constant, no dark matter.
// ---------------------------------------------------------------------
static inline double v_disk_line_occlusion(double R_kpc, double h_R_kpc,
                                            double koppa_disk_m) {
    if (R_kpc <= 0.0 || h_R_kpc <= 0.0 || koppa_disk_m <= 0.0) return 0.0;
    double f = sdt::galactic::regime_disk::f_enclosed(R_kpc, h_R_kpc);
    double v2 = C_LIGHT * C_LIGHT * koppa_disk_m * f / (h_R_kpc * kpc_m);
    return v2 > 0.0 ? std::sqrt(v2) / 1e3 : 0.0;          // [km/s]
}

// ---------------------------------------------------------------------
//  M4 disk law: convergence-floor transition (the Oort-marker physics).
//
//  A source structures the convergence field only out to where its own
//  baryonic wake thins to the UNIVERSAL CMB convergence floor a_0. Inside
//  (g_bar > a_0): source-dominated, ordinary baryonic acceleration. Outside
//  (g_bar < a_0): floor-dominated -- the velocity is set by the universal
//  floor, NOT by the local baryon density. This is the SAME crossover that
//  puts the Oort cloud at the Sun's r_domain = sqrt(L/(4pi F_CMB)) ~ 20860 AU.
//
//  a_0 = c*H_0/(2pi) ~ 1.04e-10 m/s^2 is DERIVED in galactic.hpp (a_0_SDT),
//  not fitted. Deep limit g -> sqrt(g_bar * a_0) gives v^4 = G*M_bar*a_0
//  -> BTFR slope EXACTLY 4, independent of surface density / h_R.
//
//  Transition (standard "simple" interpolation, deep limit exact):
//      g_obs = g_bar / ( 1 - exp( -sqrt(g_bar/a_0) ) )
//  Input g_bar here is the full SPARC baryonic acceleration at R:
//      g_bar = v_bar^2 / R,  v_bar^2 = Yd*Vdisk|Vdisk| + Yb*Vbul|Vbul| + Vgas|Vgas|
//  Returns the floor-corrected circular velocity v = sqrt(g_obs * R) [km/s].
// ---------------------------------------------------------------------
static inline double v_floor_transition(double v_bar_kms, double R_kpc, double a0) {
    if (v_bar_kms <= 0.0 || R_kpc <= 0.0) return 0.0;
    double R_m   = R_kpc * kpc_m;
    double v_bar = v_bar_kms * 1e3;                       // m/s
    double g_bar = v_bar * v_bar / R_m;                   // m/s^2
    if (g_bar <= 0.0) return 0.0;
    double x = std::sqrt(g_bar / a0);
    double denom = 1.0 - std::exp(-x);
    if (denom <= 0.0) return 0.0;
    double g_obs = g_bar / denom;
    double v2 = g_obs * R_m;                              // m^2/s^2
    return v2 > 0.0 ? std::sqrt(v2) / 1e3 : 0.0;          // km/s
}

// Signed square preserving SPARC sign convention (Vgas can be < 0).
static inline double ssq(double v) { return v * std::fabs(v); }

struct RCRow {
    double r_kpc, Vobs, eVobs, Vgas, Vdisk, Vbul, SBdisk, SBbul;
};
struct Master { double M_bar_Msun, h_R_kpc; int quality; bool ok=false; };

static std::map<std::string, Master> load_master(const std::string& fn) {
    std::map<std::string, Master> m;
    std::ifstream f(fn);
    if (!f) { std::fprintf(stderr, "cannot open %s\n", fn.c_str()); return m; }
    std::string line; std::getline(f, line);
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line); std::string t; Master mm; std::string name;
        std::getline(ss, name, ',');
        std::getline(ss, t, ','); mm.M_bar_Msun = std::stod(t);
        std::getline(ss, t, ','); mm.h_R_kpc    = std::stod(t);
        std::getline(ss, t, ',');  // v_flat (unused here)
        std::getline(ss, t, ','); mm.quality    = t.empty()?0:std::stoi(t);
        mm.ok = true;
        m[name] = mm;
    }
    return m;
}

static std::map<std::string, std::vector<RCRow>> load_rotmod(const std::string& fn) {
    std::map<std::string, std::vector<RCRow>> g;
    std::ifstream f(fn);
    if (!f) { std::fprintf(stderr, "cannot open %s\n", fn.c_str()); return g; }
    std::string line; std::getline(f, line);
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line); std::string t; std::string name; RCRow r;
        std::getline(ss, name, ',');
        auto nd = [&](double& d){ std::getline(ss,t,','); d = t.empty()?0.0:std::stod(t); };
        nd(r.r_kpc); nd(r.Vobs); nd(r.eVobs); nd(r.Vgas);
        nd(r.Vdisk); nd(r.Vbul); nd(r.SBdisk); nd(r.SBbul);
        g[name].push_back(r);
    }
    for (auto& kv : g)
        std::sort(kv.second.begin(), kv.second.end(),
                  [](const RCRow&a,const RCRow&b){return a.r_kpc<b.r_kpc;});
    return g;
}

// Stellar mass [Msun] from surface-brightness column: M = Y * 2pi * int SB(r) r dr.
// SB in Lsun/pc^2, r converted to pc. Trapezoidal over the sampled radii.
static double stellar_mass_from_SB(const std::vector<RCRow>& rows,
                                   double Y, bool bulge) {
    double M = 0.0;
    for (size_t i = 1; i < rows.size(); ++i) {
        double r0 = rows[i-1].r_kpc*1e3, r1 = rows[i].r_kpc*1e3; // pc
        double s0 = bulge?rows[i-1].SBbul:rows[i-1].SBdisk;
        double s1 = bulge?rows[i].SBbul  :rows[i].SBdisk;
        double f0 = TWO_PI*s0*r0, f1 = TWO_PI*s1*r1;
        M += 0.5*(f0+f1)*(r1-r0);
    }
    return Y*M;
}

struct Acc {
    double sumsq=0, sum=0; int n=0;
    std::vector<double> a;
    void add(double rp){ sumsq+=rp*rp; sum+=rp; ++n; a.push_back(std::fabs(rp)); }
    double rms()  const { return n? std::sqrt(sumsq/n):0; }
    double bias() const { return n? sum/n:0; }
    double med()  { if(a.empty())return 0; std::sort(a.begin(),a.end()); return a[a.size()/2]; }
};

static double ols_slope(const std::vector<double>&x,const std::vector<double>&y){
    double sx=0,sy=0,sxy=0,sxx=0; size_t n=x.size();
    for(size_t i=0;i<n;++i){sx+=x[i];sy+=y[i];sxy+=x[i]*y[i];sxx+=x[i]*x[i];}
    double d=n*sxx-sx*sx; return d!=0?(n*sxy-sx*sy)/d:0;
}

int main(int argc, char** argv) {
    std::string rotfn = (argc>1)?argv[1]:"sparc_rotmod.csv";
    std::string masfn = (argc>2)?argv[2]:"sparc_175.csv";

    auto master = load_master(masfn);
    auto rot    = load_rotmod(rotfn);
    if (master.empty()||rot.empty()){ std::printf("data load failed\n"); return 1; }

    std::printf("================================================================\n");
    std::printf(" GD05 TWIN-REGIME: spherical bulge (+) occlusion disk (+) gas\n");
    std::printf(" Real SPARC decomposition  x  SDT galactic.hpp (regime_bulge/disk)\n");
    std::printf("================================================================\n\n");
    std::printf(" koppa_Sun = %.3f m   (bulge spherical law: koppa == G*M/c^2)\n", B::koppa_Sun);
    std::printf(" Y_disk = %.2f, Y_bul = %.2f (SPARC 3.6um fiducial)\n\n", Y_DISK, Y_BUL);

    Acc m0_all, m1_all, m2_all, m3_all, m4_all;
    Acc m1_bulge, m1_bulgeless, m2_bulge, m2_bulgeless, m3_bulge, m3_bulgeless, m4_bulge, m4_bulgeless;
    std::vector<double> logMbar, logVobs_flat, logVm0_flat, logVm1_flat, logVm2_flat, logVm3_flat, logVm4_flat;

    const double a0 = sdt::galactic::a_0_SDT;   // = c*H_0/(2pi), DERIVED in engine

    int n_gal=0, n_bulge=0;
    std::printf(" a_0 (derived c*H_0/2pi) = %.3e m/s^2\n\n", a0);
    std::printf("%-13s %5s %9s %7s %7s %7s %7s %7s %5s\n",
                "Galaxy","Npts","Mbar","RMS_M0","RMS_M1","RMS_M2","RMS_M3","RMS_M4","bul");
    std::printf("%s\n", std::string(78,'-').c_str());

    for (auto& kv : rot) {
        const std::string& name = kv.first;
        auto it = master.find(name);
        if (it==master.end() || !it->second.ok) continue;
        const auto& rows = kv.second;
        if (rows.size() < 3) continue;
        double h_R = it->second.h_R_kpc;
        double Mbar = it->second.M_bar_Msun;
        if (h_R<=0 || Mbar<=0) continue;

        bool has_bulge=false; for (auto&r:rows) if (r.Vbul>0){has_bulge=true;break;}

        double M_disk = stellar_mass_from_SB(rows, Y_DISK, /*bulge=*/false);
        if (M_disk<=0) M_disk = 0.5*Mbar;
        double K_disk = G::koppa_from_mass(M_disk);

        double h_R_m = h_R*kpc_m;
        double M_disk_kg = M_disk*G::Msun_kg;
        double Sigma0 = M_disk_kg/(TWO_PI*h_R_m*h_R_m);
        double Sigma_sat = 175.0*G::Msun_kg/(pc_m*pc_m);
        double sat = std::min(Sigma0/Sigma_sat, 1.0);

        // Newtonian DISK baryonic velocity interpolator for the bidirectional integrals.
        auto vdisk_bar = [&](double rk)->double{
            if (rows.size()<2) return 0.0;
            if (rk<=rows.front().r_kpc) return std::sqrt(Y_DISK)*std::fabs(rows.front().Vdisk);
            if (rk>=rows.back().r_kpc)  return std::sqrt(Y_DISK)*std::fabs(rows.back().Vdisk);
            for (size_t j=1;j<rows.size();++j){
                if (rk<=rows[j].r_kpc){
                    double f=(rk-rows[j-1].r_kpc)/(rows[j].r_kpc-rows[j-1].r_kpc);
                    double a=std::sqrt(Y_DISK)*std::fabs(rows[j-1].Vdisk);
                    double b=std::sqrt(Y_DISK)*std::fabs(rows[j].Vdisk);
                    return a*(1-f)+b*f;
                }
            }
            return std::sqrt(Y_DISK)*std::fabs(rows.back().Vdisk);
        };
        double R_last = rows.back().r_kpc;

        Acc g_m0, g_m1, g_m2, g_m3, g_m4;
        double vobs_f=0,vm0_f=0,vm1_f=0,vm2_f=0,vm3_f=0,vm4_f=0; int nf=0;
        size_t istart = (size_t)(0.6*rows.size());
        for (size_t i=0;i<rows.size();++i){
            const auto& r = rows[i];
            if (r.Vobs<=0||r.r_kpc<=0) continue;

            double v_occl  = G::regime_disk::v_disk_from_koppa(r.r_kpc, h_R, K_disk, sat);
            double Kint    = G::regime_disk::koppa_interior(r.r_kpc, vdisk_bar, 0.001, 200);
            double Kext    = G::regime_disk::koppa_exterior(r.r_kpc, vdisk_bar, R_last, 200);
            double v_bidir = G::regime_disk::v_from_koppa(Kint+Kext, r.r_kpc);
            double v_line  = v_disk_line_occlusion(r.r_kpc, h_R, K_disk);  // M3: 1/r^3 line kernel

            double m0sq = Y_DISK*ssq(r.Vdisk) + Y_BUL*ssq(r.Vbul) + ssq(r.Vgas);
            double m1sq = Y_BUL*ssq(r.Vbul)  + ssq(r.Vgas) + v_occl*v_occl;
            double m2sq = Y_BUL*ssq(r.Vbul)  + ssq(r.Vgas) + v_bidir*v_bidir;
            double m3sq = Y_BUL*ssq(r.Vbul)  + ssq(r.Vgas) + v_line*v_line;
            double vm0 = m0sq>0?std::sqrt(m0sq):0;
            double vm1 = m1sq>0?std::sqrt(m1sq):0;
            double vm2 = m2sq>0?std::sqrt(m2sq):0;
            double vm3 = m3sq>0?std::sqrt(m3sq):0;
            // M4: floor transition applied to the FULL baryonic velocity (not a
            // quadrature add-on). g_bar = vm0^2/R -> floor-corrected g_obs.
            double vm4 = v_floor_transition(vm0, r.r_kpc, a0);

            double e0 = (r.Vobs-vm0)/r.Vobs*100.0;
            double e1 = (r.Vobs-vm1)/r.Vobs*100.0;
            double e2 = (r.Vobs-vm2)/r.Vobs*100.0;
            double e3 = (r.Vobs-vm3)/r.Vobs*100.0;
            double e4 = (r.Vobs-vm4)/r.Vobs*100.0;
            g_m0.add(e0); g_m1.add(e1); g_m2.add(e2); g_m3.add(e3); g_m4.add(e4);
            m0_all.add(e0); m1_all.add(e1); m2_all.add(e2); m3_all.add(e3); m4_all.add(e4);
            (has_bulge?m1_bulge:m1_bulgeless).add(e1);
            (has_bulge?m2_bulge:m2_bulgeless).add(e2);
            (has_bulge?m3_bulge:m3_bulgeless).add(e3);
            (has_bulge?m4_bulge:m4_bulgeless).add(e4);

            if (i>=istart){ vobs_f+=r.Vobs; vm0_f+=vm0; vm1_f+=vm1; vm2_f+=vm2; vm3_f+=vm3; vm4_f+=vm4; ++nf; }
        }
        if (nf>0 && vobs_f>0){
            vobs_f/=nf; vm0_f/=nf; vm1_f/=nf; vm2_f/=nf; vm3_f/=nf; vm4_f/=nf;
            if (vm0_f>0 && vm1_f>0 && vm2_f>0 && vm3_f>0 && vm4_f>0){
                logMbar.push_back(std::log10(Mbar));
                logVobs_flat.push_back(std::log10(vobs_f));
                logVm0_flat.push_back(std::log10(vm0_f));
                logVm1_flat.push_back(std::log10(vm1_f));
                logVm2_flat.push_back(std::log10(vm2_f));
                logVm3_flat.push_back(std::log10(vm3_f));
                logVm4_flat.push_back(std::log10(vm4_f));
            }
        }

        ++n_gal; if(has_bulge)++n_bulge;
        if (n_gal<=8 || has_bulge)
            std::printf("%-13s %5d %9.2e %7.1f %7.1f %7.1f %7.1f %7.1f %5s\n",
                        name.c_str(), g_m1.n, Mbar,
                        g_m0.rms(), g_m1.rms(), g_m2.rms(), g_m3.rms(), g_m4.rms(),
                        has_bulge?"YES":"-");
    }

    std::printf("%s\n\n", std::string(78,'-').c_str());
    std::printf("Galaxies fitted: %d   (with bulge: %d, bulgeless: %d)\n\n",
                n_gal, n_bulge, n_gal-n_bulge);

    std::printf("=== PER-RADIUS RESIDUALS (all %d points) ===\n", m1_all.n);
    std::printf("                                  RMS%%     bias%%   median|.|%%\n");
    std::printf("M0 Newtonian baryonic:            %6.1f  %+7.1f   %7.1f\n",
                m0_all.rms(), m0_all.bias(), m0_all.med());
    std::printf("M1 twin bulge+eclipse disk:       %6.1f  %+7.1f   %7.1f\n",
                m1_all.rms(), m1_all.bias(), m1_all.med());
    std::printf("M2 twin bulge+bidir disk:         %6.1f  %+7.1f   %7.1f\n",
                m2_all.rms(), m2_all.bias(), m2_all.med());
    std::printf("M3 twin bulge+1/r^3 LINE disk:    %6.1f  %+7.1f   %7.1f\n",
                m3_all.rms(), m3_all.bias(), m3_all.med());
    std::printf("M4 convergence-FLOOR transition:  %6.1f  %+7.1f   %7.1f\n\n",
                m4_all.rms(), m4_all.bias(), m4_all.med());

    std::printf("=== by component presence (RMS%%, bias%%) ===\n");
    std::printf("               bulge gals           bulgeless\n");
    std::printf("M1 eclipse:    %5.1f  %+6.1f        %5.1f  %+6.1f\n",
                m1_bulge.rms(), m1_bulge.bias(), m1_bulgeless.rms(), m1_bulgeless.bias());
    std::printf("M2 bidir:      %5.1f  %+6.1f        %5.1f  %+6.1f\n",
                m2_bulge.rms(), m2_bulge.bias(), m2_bulgeless.rms(), m2_bulgeless.bias());
    std::printf("M3 1/r^3 line: %5.1f  %+6.1f        %5.1f  %+6.1f\n",
                m3_bulge.rms(), m3_bulge.bias(), m3_bulgeless.rms(), m3_bulgeless.bias());
    std::printf("M4 floor:      %5.1f  %+6.1f        %5.1f  %+6.1f\n\n",
                m4_bulge.rms(), m4_bulge.bias(), m4_bulgeless.rms(), m4_bulgeless.bias());

    std::printf("=== BARYONIC TULLY-FISHER (M_bar ~ v^alpha), %zu galaxies ===\n",
                logMbar.size());
    std::printf("Observed slope:               %.2f\n", ols_slope(logVobs_flat, logMbar));
    std::printf("M0 Newtonian-baryonic:        %.2f\n", ols_slope(logVm0_flat,  logMbar));
    std::printf("M1 twin (eclipse disk):       %.2f\n", ols_slope(logVm1_flat,  logMbar));
    std::printf("M2 twin (bidir disk):         %.2f\n", ols_slope(logVm2_flat,  logMbar));
    std::printf("M3 twin (1/r^3 line disk):    %.2f\n", ols_slope(logVm3_flat,  logMbar));
    std::printf("M4 floor transition:          %.2f\n", ols_slope(logVm4_flat,  logMbar));
    std::printf("Literature:                   ~3.5 - 4.0\n\n");

    std::printf("=== VERDICT ===\n");
    std::printf("[%s] M3 (1/r^3 line)    per-radius RMS < 20%%  (got %.1f%%)\n",
                m3_all.rms()<20.0?"PASS":"FAIL", m3_all.rms());
    std::printf("[%s] M4 (floor)         per-radius RMS < 20%%  (got %.1f%%)\n",
                m4_all.rms()<20.0?"PASS":"FAIL", m4_all.rms());
    std::printf("[%s] M4 BTFR slope in [3.5,4.5] (got %.2f)\n",
                (ols_slope(logVm4_flat,logMbar)>=3.5 && ols_slope(logVm4_flat,logMbar)<=4.5)?"PASS":"FAIL",
                ols_slope(logVm4_flat, logMbar));
    std::printf("\nBulge regime: spherical SDT law == Newton (koppa=GM/c^2), exact.\n");
    std::printf("M4 floor law: g_obs = g_bar/(1-exp(-sqrt(g_bar/a_0))), a_0=c*H_0/2pi DERIVED.\n");
    std::printf("   Deep limit g->sqrt(g_bar*a_0) => v^4=G*M_bar*a_0 => BTFR slope 4. Same\n");
    std::printf("   convergence-floor crossover as the Sun's r_domain ~ 20860 AU (Oort edge).\n");
    return 0;
}
