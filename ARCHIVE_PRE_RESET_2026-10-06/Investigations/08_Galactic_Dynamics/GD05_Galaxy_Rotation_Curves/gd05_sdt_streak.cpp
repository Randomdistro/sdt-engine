// =====================================================================
//  GD05 (SDT streak) : Galaxy Rotation Curves — TWO REGIMES, MASS-FREE
//  ---------------------------------------------------------------------
//  Harvey directive (2026-07-13): eliminate ALL GM / GR structure; run
//  the SDT distance-regime model with ONE law for the bulge and ONE for
//  the disk. A flattened disk occludes incoming convergence flux as a
//  360-degree STREAK across the sky (a great-circle band), NOT a compact
//  spherical patch. That geometry is the whole mechanism.
//
//  NO G. NO M. NO koppa_from_mass. NO a_0. NO MOND interpolation.
//  NO <sdt/galactic.hpp>. Inputs are MEASURED velocities (km/s) and
//  MEASURED geometry (kpc). The only calibrated numbers are the SPARC
//  fiducial 3.6um stellar mass-to-light ratios (Y_disk, Y_bul) — a
//  stellar-population choice, NOT gravity. Gas carries no M/L.
//
//  THE TWO REGIMES
//  ---------------------------------------------------------------------
//  BULGE  -> SPHERICAL occlusion (compact patch on the sky). The bulge
//            sits at the centre; from a star at R it subtends a small
//            solid angle ~ 1/R^2. This is ordinary (Newton-equivalent)
//            declining gravity. SPARC's Vbul(r) already IS that field.
//               v_bulge^2 = Y_bul * Vbul(R)^2                 [declining]
//
//  DISK   -> 360-DEGREE STREAK occlusion. Seen edge-on from within the
//            plane, the disk is a thin band wrapping the entire sky. The
//            depth field of a source is z(r) = koppa/r (~1/r); its
//            transverse gradient is ~1/r^3; integrated along the radial
//            LINE the disk presents, the in-plane acceleration goes as
//            1/R (not 1/R^2). Hence v^2 -> constant: a FLAT curve, from
//            geometry alone.
//
//            MASS-FREE FORM. The Newtonian disk velocity already encodes
//            the baryonic column: outer disk is Keplerian, Vdisk^2 * R ->
//            (mass scale) = const. The line/streak law divides that scale
//            by the disk scale-length h_R instead of by R:
//               point (1/R^2):  v^2 = [Vdisk^2 * R] / R      = Vdisk^2
//               line  (1/R^3):  v^2 = [Vdisk^2 * R] / h_R              (*)
//            (*) is exactly the M3 "1/r^3 line" law with GM_disk removed:
//            GM_disk*f_enc(R) = Vdisk(R)^2 * R  (measured), so
//               v_streak^2(R) = Vdisk(R)^2 * (R / h_R).
//            It flattens automatically (Vdisk^2*R -> const in the outer
//            disk) with NO fitted scale and NO dark matter.
//
//  CROSSOVER (native, geometric — NOT MOND's a_0). A disk looks like a
//  POINT when you are inside it (R < h_R) and like a LINE/STREAK when you
//  are a scale-length out (R > h_R). The transition radius is h_R itself:
//     S2:  v_disk^2(R) = [Y_d Vdisk^2 + Vgas^2] * max(1, R/h_R)
//  S1 is the pure streak (R/h_R everywhere). M0 is the Newtonian
//  baryonic control (the "no dark matter" baseline that is known to fail).
//
//  Data: real published SPARC (Lelli+2016, AJ 152, 157):
//     sparc_rotmod.csv  - per-radius (R,Vobs,eVobs,Vgas,Vdisk,Vbul,SB..)
//     sparc_175.csv     - master (name, M_bar, h_R, v_flat, quality)
//
//  Build (standalone; touches nothing in the engine):
//     g++  -std=c++20 -O2 gd05_sdt_streak.cpp -o gd05_streak
//     cl /std:c++20 /EHsc /O2 gd05_sdt_streak.cpp
//  Run: ./gd05_streak sparc_rotmod.csv sparc_175.csv
//
//  Author: SDT Canonical Engine — J. C. Harvey, Melbourne
// =====================================================================

#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

// SPARC fiducial 3.6um mass-to-light ratios (Lelli+2016). The ONLY
// calibrated numbers here — stellar population, not gravity. CALIBRATED(2).
static constexpr double Y_DISK = 0.5;
static constexpr double Y_BUL  = 0.7;

static constexpr double PI_ = 3.14159265358979323846;
static inline double ssq(double v) { return v * std::fabs(v); }   // signed square (Vgas sign)

struct RCRow { double R, Vobs, eVobs, Vgas, Vdisk, Vbul; };
struct Master { double M_bar, h_R; int quality; bool ok=false; };

static std::map<std::string, Master> load_master(const std::string& fn) {
    std::map<std::string, Master> m; std::ifstream f(fn);
    if (!f) { std::fprintf(stderr, "cannot open %s\n", fn.c_str()); return m; }
    std::string line; std::getline(f, line);
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line); std::string t, name; Master mm;
        std::getline(ss, name, ',');
        std::getline(ss, t, ','); mm.M_bar = t.empty()?0:std::stod(t);
        std::getline(ss, t, ','); mm.h_R   = t.empty()?0:std::stod(t);
        std::getline(ss, t, ',');                       // v_flat (unused)
        std::getline(ss, t, ','); mm.quality = t.empty()?0:std::stoi(t);
        mm.ok = true; m[name] = mm;
    }
    return m;
}

static std::map<std::string, std::vector<RCRow>> load_rotmod(const std::string& fn) {
    std::map<std::string, std::vector<RCRow>> g; std::ifstream f(fn);
    if (!f) { std::fprintf(stderr, "cannot open %s\n", fn.c_str()); return g; }
    std::string line; std::getline(f, line);
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line); std::string t, name; RCRow r{};
        std::getline(ss, name, ',');
        auto nd = [&](double& d){ std::getline(ss,t,','); d = t.empty()?0.0:std::stod(t); };
        nd(r.R); nd(r.Vobs); nd(r.eVobs); nd(r.Vgas); nd(r.Vdisk); nd(r.Vbul);
        g[name].push_back(r);
    }
    for (auto& kv : g)
        std::sort(kv.second.begin(), kv.second.end(),
                  [](const RCRow&a,const RCRow&b){return a.R<b.R;});
    return g;
}

struct Acc {
    double sumsq=0, sum=0; int n=0; std::vector<double> a;
    void add(double rp){ sumsq+=rp*rp; sum+=rp; ++n; a.push_back(std::fabs(rp)); }
    double rms()  const { return n? std::sqrt(sumsq/n):0; }
    double bias() const { return n? sum/n:0; }
    double med()        { if(a.empty())return 0; std::sort(a.begin(),a.end()); return a[a.size()/2]; }
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

    std::printf("=================================================================\n");
    std::printf(" GD05 SDT STREAK : two regimes, MASS-FREE (no G, no M, no a_0)\n");
    std::printf(" bulge = spherical occlusion ; disk = 360deg streak (line) occl.\n");
    std::printf(" real SPARC (Lelli+2016) ; Y_disk=%.2f Y_bul=%.2f (3.6um fiducial)\n",
                Y_DISK, Y_BUL);
    std::printf("=================================================================\n\n");

    Acc M0, S1, S2;                                   // per-radius, all points
    Acc S2_bulge, S2_bless;                           // split by bulge presence
    std::vector<double> logM, logVobs, logVS2;        // BTFR (outer-mean)

    // Winding diagnostic (Harvey 2026-07-13): a MATERIAL spiral arm shears by
    //   dTurns = [Omega(r_in) - Omega(r_out)] * T / (2pi)   over T = 10 Gyr.
    // Omega[rad/Gyr] = 1.0228 * v[km/s] / r[kpc]. If dTurns >> a few, a
    // material arm cannot survive -> arms MUST be a PATTERN, not material.
    const double T_GYR = 10.0, OMK = 1.0227;          // km/s/kpc -> rad/Gyr
    Acc wind_obs, wind_s2, turns_inner;               // windings over 10 Gyr
    Acc spoke_clock;                                  // Myr per ONE relative turn (spoke<->spiral clock)
    std::vector<double> outer_beta;                   // d ln v / d ln r (outer)

    int n_gal=0, n_bulge=0, n_pass25=0;
    std::printf("%-13s %5s %9s  %7s %7s %7s  %4s\n",
                "Galaxy","Npts","M_bar","RMS_M0","RMS_S1","RMS_S2","bul");
    std::printf("%s\n", std::string(63,'-').c_str());

    for (auto& kv : rot) {
        const std::string& name = kv.first;
        auto it = master.find(name);
        if (it==master.end() || !it->second.ok) continue;
        const auto& rows = kv.second;
        if (rows.size() < 3) continue;
        double h_R = it->second.h_R, Mbar = it->second.M_bar;
        if (h_R<=0 || Mbar<=0) continue;

        bool has_bulge=false; for (auto&r:rows) if (r.Vbul>0){has_bulge=true;break;}

        Acc g0, g1, g2;
        double vobs_f=0, vS2_f=0; int nf=0;
        size_t istart = (size_t)(0.6*rows.size());     // outer 40% = "flat" region
        for (size_t i=0;i<rows.size();++i){
            const auto& r = rows[i];
            if (r.Vobs<=0 || r.R<=0) continue;

            double v_bulge2 = Y_BUL*ssq(r.Vbul);                       // spherical regime
            double v_disk2  = Y_DISK*ssq(r.Vdisk) + ssq(r.Vgas);       // baryonic disk+gas
            double streak   = r.R / h_R;                              // 360deg streak factor

            double m0sq = v_disk2 + v_bulge2;                          // Newtonian control
            double s1sq = v_disk2*streak            + v_bulge2;        // pure streak
            double s2sq = v_disk2*std::max(1.0,streak) + v_bulge2;     // point->line at R=h_R

            double vm0 = m0sq>0?std::sqrt(m0sq):0;
            double vs1 = s1sq>0?std::sqrt(s1sq):0;
            double vs2 = s2sq>0?std::sqrt(s2sq):0;

            double e0=(r.Vobs-vm0)/r.Vobs*100.0;
            double e1=(r.Vobs-vs1)/r.Vobs*100.0;
            double e2=(r.Vobs-vs2)/r.Vobs*100.0;
            g0.add(e0); g1.add(e1); g2.add(e2);
            M0.add(e0); S1.add(e1); S2.add(e2);
            (has_bulge?S2_bulge:S2_bless).add(e2);

            if (i>=istart){ vobs_f+=r.Vobs; vS2_f+=vs2; ++nf; }
        }
        if (nf>0 && vobs_f>0){
            vobs_f/=nf; vS2_f/=nf;
            if (vS2_f>0){ logM.push_back(std::log10(Mbar));
                          logVobs.push_back(std::log10(vobs_f));
                          logVS2.push_back(std::log10(vS2_f)); }
        }
        // --- winding diagnostic: inner vs outer shear over 10 Gyr ---
        const RCRow* rin=nullptr; const RCRow* rout=nullptr;
        for (auto& r : rows) if (r.Vobs>0 && r.R>0.5){ rin=&r; break; }
        for (auto it2=rows.rbegin(); it2!=rows.rend(); ++it2)
            if (it2->Vobs>0 && it2->R>0){ rout=&(*it2); break; }
        if (rin && rout && rout->R > rin->R*1.5) {
            double Om_in  = OMK*rin->Vobs /rin->R;    // rad/Gyr (observed)
            double Om_out = OMK*rout->Vobs/rout->R;
            double dturns = (Om_in - Om_out)*T_GYR/(2.0*PI_);
            wind_obs.add(dturns);
            if (std::fabs(dturns)>1e-6)
                spoke_clock.add(1000.0*T_GYR/std::fabs(dturns)); // Myr per one relative turn
            turns_inner.add(Om_in*T_GYR/(2.0*PI_));  // absolute inner windings
            // outer log-slope beta = d ln v / d ln r  (0=flat, 1=solid body)
            double b = std::log(rout->Vobs/rin->Vobs)/std::log(rout->R/rin->R);
            outer_beta.push_back(b);
            // same for the S2 model velocity at those radii
            auto vS2=[&](const RCRow& r){ double vb=Y_BUL*ssq(r.Vbul);
                double vd=(Y_DISK*ssq(r.Vdisk)+ssq(r.Vgas))*std::max(1.0,r.R/h_R);
                double s=vd+vb; return s>0?std::sqrt(s):0.0; };
            double vi=vS2(*rin), vo=vS2(*rout);
            if (vi>0 && vo>0)
                wind_s2.add((OMK*vi/rin->R - OMK*vo/rout->R)*T_GYR/(2.0*PI_));
        }

        ++n_gal; if(has_bulge)++n_bulge; if(g2.rms()<25.0)++n_pass25;
        if (n_gal<=10 || has_bulge)
            std::printf("%-13s %5d %9.2e  %7.1f %7.1f %7.1f  %4s\n",
                        name.c_str(), g2.n, Mbar, g0.rms(), g1.rms(), g2.rms(),
                        has_bulge?"YES":"-");
    }

    std::printf("%s\n\n", std::string(63,'-').c_str());
    std::printf("Galaxies fitted: %d  (with bulge: %d, bulgeless: %d)\n",
                n_gal, n_bulge, n_gal-n_bulge);
    std::printf("Galaxies with S2 per-galaxy RMS < 25%%: %d / %d\n\n", n_pass25, n_gal);

    std::printf("=== PER-RADIUS RESIDUALS (all %d points) ===\n", S2.n);
    std::printf("                                  RMS%%    bias%%   median|.|%%\n");
    std::printf("M0 Newtonian baryonic (control):  %6.1f  %+6.1f   %7.1f\n",
                M0.rms(), M0.bias(), M0.med());
    std::printf("S1 pure 360deg streak  (R/h_R):   %6.1f  %+6.1f   %7.1f\n",
                S1.rms(), S1.bias(), S1.med());
    std::printf("S2 point->streak at R=h_R:        %6.1f  %+6.1f   %7.1f\n\n",
                S2.rms(), S2.bias(), S2.med());

    std::printf("=== S2 by bulge presence ===\n");
    std::printf("  with bulge : RMS %.1f%%  bias %+.1f%%   (%d pts)\n",
                S2_bulge.rms(), S2_bulge.bias(), S2_bulge.n);
    std::printf("  bulgeless  : RMS %.1f%%  bias %+.1f%%   (%d pts)\n\n",
                S2_bless.rms(), S2_bless.bias(), S2_bless.n);

    std::printf("=== BARYONIC TULLY-FISHER (M_bar ~ v^alpha), %zu galaxies ===\n", logM.size());
    std::printf("  observed outer-mean slope : %.2f\n", ols_slope(logVobs, logM));
    std::printf("  S2 streak model slope     : %.2f   (literature ~3.5-4.0)\n\n",
                ols_slope(logVS2, logM));

    // --- winding / spiral-persistence diagnostic ---
    std::sort(outer_beta.begin(), outer_beta.end());
    double beta_med = outer_beta.empty()?0:outer_beta[outer_beta.size()/2];
    std::printf("=== WINDING DIAGNOSTIC (the spiral-arm problem) — %d galaxies ===\n", wind_obs.n);
    std::printf("  A MATERIAL arm survives only if inner-vs-outer shear over the\n");
    std::printf("  galaxy age stays to a few turns. Observed curves give:\n");
    std::printf("    dTurns over 10 Gyr (inner vs outer)  : median %.1f   mean %.1f\n",
                wind_obs.med(), wind_obs.bias());
    std::printf("    absolute inner windings over 10 Gyr  : median %.1f   mean %.1f\n",
                turns_inner.med(), turns_inner.bias());
    std::printf("    outer log-slope beta=dlnv/dlnr       : median %.2f  (0=flat,1=rigid)\n", beta_med);
    std::printf("    -> a material arm winds up ~%.0fx in 10 Gyr. IT CANNOT BE MATERIAL.\n",
                wind_obs.med());
    std::printf("  SPOKE CLOCK (time for inner to lap outer by ONE full turn):\n");
    std::printf("    median %.0f Myr  (mean %.0f Myr) per relative turn.\n",
                spoke_clock.med(), spoke_clock.bias());
    std::printf("    => radial SPOKES wind into a 1-turn spiral in ~%.0f Myr, and an open\n",
                spoke_clock.med());
    std::printf("       spiral UNWINDS to spokes in a fraction of that (~%.0f Myr for a\n",
                spoke_clock.med()*0.4);
    std::printf("       half-turn arm). Galaxy age ~10000 Myr => ~%.0fx too many windings.\n",
                10000.0/spoke_clock.med());
    std::printf("       The arm pattern is ~1%% of the galaxy's age old at most: TRANSIENT\n");
    std::printf("       as matter, PERSISTENT only as a standing pressure/occlusion wave.\n");
    std::printf("    Spiral arms must be a STANDING PATTERN (density/occlusion wave),\n");
    std::printf("    not co-moving matter. Same conclusion for the S2 model curve\n");
    std::printf("    (dTurns median %.1f) — flat rotation of independent orbiters is\n", wind_s2.med());
    std::printf("    self-refuting; the missing ingredient is the pattern mechanism.\n\n");

    std::printf("=== VERDICT (pre-committed: S2 per-radius RMS < 25%%, BTFR in [3.5,4.5]) ===\n");
    double s2slope = ols_slope(logVS2, logM);
    std::printf("  [%s] S2 per-radius RMS < 25%%   (got %.1f%%)\n",
                S2.rms()<25.0?"PASS":"FAIL", S2.rms());
    std::printf("  [%s] S2 BTFR slope in [3.5,4.5] (got %.2f)\n",
                (s2slope>=3.5&&s2slope<=4.5)?"PASS":"FAIL", s2slope);
    std::printf("  [%s] S2 beats Newtonian control (%.1f%% vs %.1f%%)\n",
                S2.rms()<M0.rms()?"PASS":"FAIL", S2.rms(), M0.rms());
    std::printf("\n  NO G, NO M, NO a_0, NO MOND. Bulge=spherical occlusion,\n");
    std::printf("  disk=360deg streak (line) occlusion, crossover at R=h_R (geometry).\n");
    std::printf("  Calibrated: Y_disk,Y_bul (stellar M/L, SPARC fiducial) — not gravity.\n");
    return 0;
}
