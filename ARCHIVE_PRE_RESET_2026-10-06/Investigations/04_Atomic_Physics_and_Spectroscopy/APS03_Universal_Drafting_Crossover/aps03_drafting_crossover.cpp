// =====================================================================
//  APS03: The Universal Drafting Crossover  —  forensic engine
//  ---------------------------------------------------------------------
//  Tests APS03-H1: a single scale-invariant curve  B = Phi(xi)  governs
//  the convergence-coupling response at every scale, where
//      xi = g_self / g_floor      (exposure ratio, g_floor DERIVED)
//      B  = R / R0                (response / bare baseline)
//  DERIVED asymptotes (NOT under test):  xi->inf: Phi->1 ;
//                                          xi->0  : Phi->xi^(-1/2).
//  Crossover shape baseline (BORROWED, MOND-simple):
//      Phi_simple(xi) = 1 / (1 - exp(-sqrt(xi))).
//
//  Scales implemented here (real, in-repo / fetched data only):
//    (C) GALACTIC : SPARC Rotmod decomposition. B = Vobs^2 / Vbar^2,
//                   xi = (Vbar^2/R)/a0.  PILOT + stop-check vs GD05 M4.
//    (A) ATOMIC   : APS02 resonance lines. B = D = lam/((8/3) lam_C k^2),
//                   xi from shell-drafting occupancy (stated rule).
//    (B) STELLAR  : stellar_orbits.csv if present (else SHORT).
//    (D) NUCLEAR  : nuclear_binding.csv if present (else SHORT).
//
//  Anti-fabrication (APS03 sec.10): every input file is line-counted and
//  its first/last row echoed; observables -> model only (B never feeds xi).
//  All constants from Engine/include/sdt/ ; cite at use.
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

namespace K = sdt::laws::measured;
namespace gal = sdt::galactic;

static const double cL    = K::c;                // laws.hpp
static const double lamC  = K::lambda_C_e;       // laws.hpp:137 [m]
static const double m_e   = K::m_e;              // laws.hpp:130
static const double eV    = K::eV_to_J;          // laws.hpp:153
static const double kpc_m = gal::kpc_m;

struct FloorClosure {
    double angular_fraction;
    double engaged_fraction;
    double resistance_density;
    double pressure_gradient;
    double acceleration;
    double finite_volume_acceleration;
    double finite_volume_residual;
};

static FloorClosure derive_convergence_floor() {
    using namespace sdt::laws;
    const double radius = law_I::R_CMB;
    const double full_volume =
        4.0 * std::numbers::pi * radius * radius * radius / 3.0;
    const double engaged_volume =
        law_IV::locked_engaged_volume_sphere(radius);
    const double engaged_fraction = engaged_volume / full_volume;
    const double angular_fraction = 1.0 / 3.0;
    const double resistance_density =
        law_IV::resistance_from_engaged_volume(engaged_volume)
        / (full_volume * K::c * K::c);
    const double pressure_gradient =
        angular_fraction * law_I::P_conv / radius;
    const double acceleration = pressure_gradient / resistance_density;

    // Independent finite-volume route: midpoint solid-angle and radial
    // quadratures. Neither quadrature receives the analytic 1/3 or 6/7.
    constexpr int intervals = 200'000;
    double angular_sum = 0.0;
    double radial_sum = 0.0;
    for (int index = 0; index < intervals; ++index) {
        const double fraction =
            (static_cast<double>(index) + 0.5)
            / static_cast<double>(intervals);
        const double cosine = -1.0 + 2.0 * fraction;
        angular_sum += cosine * cosine;
        const double radial = radius * fraction;
        radial_sum += radial * radial
            * law_IV::relay_lock_fraction(radial, radius);
    }
    const double angular_numeric =
        angular_sum / static_cast<double>(intervals);
    const double engaged_numeric =
        4.0 * std::numbers::pi * radius
        * radial_sum / static_cast<double>(intervals);
    const double density_numeric =
        law_IV::resistance_from_engaged_volume(engaged_numeric)
        / (full_volume * K::c * K::c);
    const double gradient_numeric =
        angular_numeric * law_I::P_conv / radius;
    const double acceleration_numeric = gradient_numeric / density_numeric;

    return {
        angular_fraction,
        engaged_fraction,
        resistance_density,
        pressure_gradient,
        acceleration,
        acceleration_numeric,
        std::fabs(acceleration_numeric / acceleration - 1.0)
    };
}

static const FloorClosure floor_closure = derive_convergence_floor();
static const double a0 = floor_closure.acceleration;

static constexpr double Y_DISK = 0.5, Y_BUL = 0.7;
static inline double ssq(double v){ return v*std::fabs(v); }

// BORROWED baseline crossover (MOND simple); asymptotes are the DERIVED part.
static inline double Phi_simple(double xi){
    if (xi<=0) return 0;
    double d = 1.0 - std::exp(-std::sqrt(xi));
    return d>0 ? 1.0/d : 0.0;
}

// ---- one forensic record ----
struct Rec {
    char scale;            // 'C','A','B','D'
    std::string cls;       // class label
    char type;             // 'S','T','F'
    std::string id;        // example id
    double xi, B, sigmaB;
};
static char type_of(double xi){ return xi>=10.0?'S' : (xi<=0.1?'F':'T'); }

// =====================================================================
//  Provenance: line-count + first/last echo, abort on empty
// =====================================================================
static std::vector<std::string> load_lines(const std::string& fn, bool& ok){
    std::vector<std::string> v; std::ifstream f(fn);
    ok=false;
    if(!f){ std::fprintf(stderr,"[provenance] MISSING %s\n",fn.c_str()); return v; }
    std::string l; while(std::getline(f,l)){ if(!l.empty()) v.push_back(l); }
    if(v.size()<2){ std::fprintf(stderr,"[provenance] EMPTY/SHORT %s (%zu lines)\n",fn.c_str(),v.size()); return v; }
    std::fprintf(stderr,"[provenance] %s : %zu lines\n  first: %s\n  last : %s\n",
                 fn.c_str(), v.size(), v[1].c_str(), v.back().c_str());
    ok=true; return v;
}

// =====================================================================
//  SCALE C — GALACTIC  (SPARC) + PILOT STOP-CHECK vs GD05 M4
// =====================================================================
struct RC { double r,Vobs,eV,Vgas,Vdisk,Vbul,SBd,SBb; };

static void scale_galactic(std::vector<Rec>& out,
                           const std::string& rotfn, const std::string& masfn,
                           double& m4_rms_out, double& m4_btfr_out, int& m4_npts){
    bool ok1,ok2;
    auto rl = load_lines(rotfn,ok1);
    auto ml = load_lines(masfn,ok2);
    m4_rms_out=-1; m4_btfr_out=0; m4_npts=0;
    if(!ok1||!ok2){ std::fprintf(stderr,"[C] galactic SHORT (data missing)\n"); return; }

    // master: name -> (M_bar, h_R)
    std::map<std::string,std::pair<double,double>> mas;
    for(size_t i=1;i<ml.size();++i){ std::stringstream s(ml[i]); std::string n,t;
        std::getline(s,n,','); double mb,hr;
        std::getline(s,t,','); mb=std::stod(t); std::getline(s,t,','); hr=std::stod(t);
        mas[n]={mb,hr}; }

    // rotmod grouped by name
    std::map<std::string,std::vector<RC>> g;
    for(size_t i=1;i<rl.size();++i){ std::stringstream s(rl[i]); std::string n,t; RC r;
        std::getline(s,n,',');
        auto nd=[&](double&d){ std::getline(s,t,','); d=t.empty()?0:std::stod(t); };
        nd(r.r);nd(r.Vobs);nd(r.eV);nd(r.Vgas);nd(r.Vdisk);nd(r.Vbul);nd(r.SBd);nd(r.SBb);
        g[n].push_back(r); }

    // M4 stop-check accumulators + BTFR collectors
    double sumsq=0; int npts=0;
    std::vector<double> logM, logVm4;

    for(auto& kv: g){
        auto it=mas.find(kv.first); if(it==mas.end()) continue;
        double Mbar=it->second.first, h_R=it->second.second;
        if(Mbar<=0||h_R<=0) continue;
        auto& rows=kv.second; if(rows.size()<3) continue;
        std::sort(rows.begin(),rows.end(),[](const RC&a,const RC&b){return a.r<b.r;});
        bool bulge=false; for(auto&r:rows) if(r.Vbul>0){bulge=true;break;}
        // crude morphology class proxy: bulge -> C4; else by central SBdisk
        double SBmax=0; for(auto&r:rows) SBmax=std::max(SBmax,r.SBd);
        std::string cls = bulge? "bulge" : (SBmax>100.0? "HSB" : (Mbar<5e9? "dwarf":"LSB"));

        double vm4_outer=0, vobs_outer=0; int nf=0; size_t i0=(size_t)(0.6*rows.size());
        for(size_t i=0;i<rows.size();++i){
            const RC& r=rows[i]; if(r.Vobs<=0||r.r<=0) continue;
            double R=r.r*kpc_m;
            double vbar2 = Y_DISK*ssq(r.Vdisk)+Y_BUL*ssq(r.Vbul)+ssq(r.Vgas); // (km/s)^2
            if(vbar2<=0) continue;
            double vbar = std::sqrt(vbar2);                 // km/s
            double g_bar = (vbar*1e3)*(vbar*1e3)/R;          // m/s^2
            double xi = g_bar/a0;
            double Bmeas = (r.Vobs*r.Vobs)/vbar2;            // = g_obs/g_bar
            // sigma_B from eVobs (km/s): B = Vobs^2/vbar2 -> dB/B = 2 dVobs/Vobs
            double sB = (r.Vobs>0)? Bmeas*2.0*(r.eV/r.Vobs) : 0;
            out.push_back({'C',cls,type_of(xi),kv.first+"@"+std::to_string(r.r),xi,Bmeas,sB});

            // M4 prediction for stop-check: v_pred = vbar*sqrt(Phi_simple(xi))
            double vm4 = vbar*std::sqrt(Phi_simple(xi));
            double e = (r.Vobs-vm4)/r.Vobs*100.0; sumsq+=e*e; ++npts;
            if(i>=i0){ vm4_outer+=vm4; vobs_outer+=r.Vobs; ++nf; }
        }
        if(nf>0 && vm4_outer>0){ logM.push_back(std::log10(Mbar)); logVm4.push_back(std::log10(vm4_outer/nf)); }
    }
    m4_npts=npts;
    m4_rms_out = npts? std::sqrt(sumsq/npts) : -1;
    // BTFR slope d(logM)/d(logV)
    { double sx=0,sy=0,sxy=0,sxx=0; size_t n=logVm4.size();
      for(size_t i=0;i<n;++i){sx+=logVm4[i];sy+=logM[i];sxy+=logVm4[i]*logM[i];sxx+=logVm4[i]*logVm4[i];}
      double d=n*sxx-sx*sx; m4_btfr_out = d!=0?(n*sxy-sx*sy)/d:0; }
}

// =====================================================================
//  SCALE A — ATOMIC  (APS02 resonance lines, in-source table)
//  B = D = lam_meas / ((8/3) lam_C k^2),  k = c/v1, v1=sqrt(2 IE1/m_e).
//  xi_A: drafting occupancy. Active electron in valence shell of capacity
//  cap (2 for n=1/He-closed, else 8). co-drafters = outer-1, vacancies =
//  cap-outer.  xi = (outer-1+0.5)/(cap-outer+0.5).  Full shell -> xi big
//  (source); lone opener -> xi small (floor).  STATED rule; sec.7.3 tests
//  whether this geometric xi collapses onto the galactic Phi.
// =====================================================================
struct El{ int Z; double IE1, lam_nm; int outer; const char* sym; int cap; };
static void scale_atomic(std::vector<Rec>& out){
    // IE1[eV], resonance line[nm], outer s+p electrons, capacity.
    // (same elements as APS02 engine; cap=2 only for He closed 1s2, else 8.)
    static const El E[]={
        {1,13.598,121.567,1,"H",2},{2,24.587,58.433,2,"He",2},{3,5.392,670.776,1,"Li",8},
        {4,9.323,234.861,2,"Be",8},{5,8.298,249.773,3,"B",8},{6,11.260,193.091,4,"C",8},
        {7,14.534,119.955,5,"N",8},{8,13.618,130.217,6,"O",8},{9,17.423,95.483,7,"F",8},
        {10,21.565,73.590,8,"Ne",8},{11,5.139,588.995,1,"Na",8},{12,7.646,285.213,2,"Mg",8},
        {13,5.986,394.401,3,"Al",8},{14,8.152,251.611,4,"Si",8},{15,10.487,213.618,5,"P",8},
        {16,10.360,180.731,6,"S",8},{17,12.968,134.724,7,"Cl",8},{18,15.760,104.822,8,"Ar",8},
        {19,4.341,766.490,1,"K",8},{20,6.113,422.673,2,"Ca",8},{26,7.902,371.994,2,"Fe",8},
        {29,7.726,324.754,1,"Cu",8},{30,9.394,213.856,2,"Zn",8},{31,5.999,403.298,3,"Ga",8},
        {32,7.900,265.118,4,"Ge",8},{34,9.752,196.090,6,"Se",8},{36,14.000,123.584,8,"Kr",8},
        {37,4.177,780.023,1,"Rb",8},{38,5.695,460.733,2,"Sr",8},{47,7.576,328.068,1,"Ag",8},
        {48,8.994,228.802,2,"Cd",8},{49,5.786,410.176,3,"In",8},{50,7.344,283.999,4,"Sn",8},
        {53,10.451,183.038,7,"I",8},{54,12.130,146.961,8,"Xe",8},{55,3.894,894.347,1,"Cs",8},
        {56,5.212,553.548,2,"Ba",8},
    };
    double lamC_nm = lamC*1e9;
    for(const El& e: E){
        double v1=std::sqrt(2.0*e.IE1*eV/m_e);
        double k=cL/v1;
        double D = e.lam_nm / ((8.0/3.0)*lamC_nm*k*k);          // B
        double num = (e.outer-1)+0.5, den=(e.cap-e.outer)+0.5;
        double xi = num/den;                                    // stated geometric xi
        // period/row as class proxy (controls active-shell n)
        std::string cls = e.Z<=2?"n1": e.Z<=10?"n2": e.Z<=18?"n3": e.Z<=36?"n4":"n5+";
        out.push_back({'A',cls,type_of(xi),std::string(e.sym),xi,D,0.0});
    }
}

// =====================================================================
//  Generic CSV scales (stellar / nuclear) — ingest if present
// =====================================================================
static void scale_stellar(std::vector<Rec>& out, const std::string& fn){
    bool ok; auto L=load_lines(fn,ok);
    if(!ok){ std::fprintf(stderr,"[B] stellar SHORT (no %s)\n",fn.c_str()); return; }
    // Catalogue columns 8-9 contain a host-load estimate and uncertainty.
    // They are parsed as text and deliberately excluded from this route.
    int n=0;
    for(size_t i=1;i<L.size();++i){
        std::stringstream s(L[i]); std::string f[12]; int c=0; std::string t;
        while(c<12 && std::getline(s,t,',')) f[c++]=t;
        if(c<8) continue;
        try{
            std::string cls=f[0]; double aAU=std::stod(f[3]);
            double Pyr = f[5].empty()?0:std::stod(f[5]);
            double vobs = f[9].empty()?0:std::stod(f[9])*1e3; // m/s
            // The catalogue host-load column is deliberately not consumed.
            // Only Solar rows have an independent engine koppa in this corpus.
            if(aAU<=0 || f[2]!="Sun") continue;
            double a=aAU*1.495978707e11;
            double koppa = sdt::laws::bridge::koppa_Sun;
            double vKep2 = cL*cL*koppa/a;               // (m/s)^2
            if(vobs<=0){ if(Pyr<=0) continue; vobs=2.0*std::numbers::pi*a/(Pyr*3.15576e7); }
            double Bmeas = (vobs*vobs)/vKep2;
            double g_host = cL*cL*koppa/(a*a);
            double xi = g_host/a0;
            out.push_back({'B',cls,type_of(xi),f[1],xi,Bmeas,0.0}); ++n;
        }catch(...){ continue; }
    }
    std::fprintf(stderr,"[B] stellar: %d rows ingested\n",n);
}

static void scale_nuclear(std::vector<Rec>& out, const std::string& fn){
    bool ok; auto L=load_lines(fn,ok);
    if(!ok){ std::fprintf(stderr,"[D] nuclear SHORT (no %s)\n",fn.c_str()); return; }
    // expected: Z,A,element,BE_per_A_keV,BE_per_A_err_keV,n_deu,n_tri,grammar_class,source
    // bare baseline R0 = deuteron BE/A ~ 1112.283 keV (B_d=2224.566 keV /2)
    const double BEbare = 1112.283;
    int n=0;
    for(size_t i=1;i<L.size();++i){
        std::stringstream s(L[i]); std::string f[9]; int c=0; std::string t;
        while(c<9 && std::getline(s,t,',')) f[c++]=t;
        if(c<8) continue;
        try{
            double bea=std::stod(f[3]); double bea_e=f[4].empty()?0:std::stod(f[4]);
            double nd=std::stod(f[5]), nt=std::stod(f[6]); std::string cls=f[7];
            if(bea<=0) continue;
            double B = bea/BEbare;
            double xi = (nd+0.5)/(nt+0.5);   // deuteron-drafting / triton-exposure
            out.push_back({'D',cls,type_of(xi),f[2]+f[1],xi,B,bea_e/BEbare}); ++n;
        }catch(...){ continue; }
    }
    std::fprintf(stderr,"[D] nuclear: %d rows ingested\n",n);
}

// =====================================================================
//  TESTS
// =====================================================================
struct PoolStat{ int n=0; double meanB=0, slope=0, rmsVsPhi=0; };

static void report_scale(char sc, const std::vector<Rec>& R){
    int nS=0,nT=0,nF=0; double sumS=0;
    std::vector<double> lx,lb;          // floor-pool log-log
    double sumsq_phi=0; int nphi=0;
    int cellcount[5]={};
    for(const Rec& r: R){ if(r.scale!=sc) continue;
        if(r.type=='S'){nS++; sumS+=r.B;}
        else if(r.type=='T') nT++;
        else { nF++; if(r.xi>0&&r.B>0){lx.push_back(std::log(r.xi)); lb.push_back(std::log(r.B));} }
        double pp=Phi_simple(r.xi); if(pp>0){ double e=(r.B-pp)/pp; sumsq_phi+=e*e; ++nphi; }
    }
    int tot=nS+nT+nF; if(tot==0){ std::printf("  scale %c: NO DATA (SHORT)\n",sc); return; }
    double meanS = nS? sumS/nS : 0;
    double slope=0; if(lx.size()>2){ double sx=0,sy=0,sxy=0,sxx=0; size_t n=lx.size();
        for(size_t i=0;i<n;++i){sx+=lx[i];sy+=lb[i];sxy+=lx[i]*lb[i];sxx+=lx[i]*lx[i];}
        double d=n*sxx-sx*sx; slope=d!=0?(n*sxy-sx*sy)/d:0; }
    double rmsphi = nphi? std::sqrt(sumsq_phi/nphi)*100.0 : -1;
    const char* nm = sc=='C'?"GALACTIC":sc=='A'?"ATOMIC":sc=='B'?"STELLAR":"NUCLEAR";
    std::printf("  [%c] %-8s  N=%4d (S=%d T=%d F=%d)\n",sc,nm,tot,nS,nT,nF);
    std::printf("       A-S  <B>_source = %7.3f   %s (PASS if |.-1|<=0.10)\n",
                meanS, (nS>0 && std::fabs(meanS-1.0)<=0.10)?"PASS": nS==0?"no-S":"--");
    std::printf("       A-F  d(logB)/d(logxi)_floor = %+6.3f   %s (PASS if in [-0.60,-0.40])\n",
                slope, (lx.size()>2 && slope>=-0.60 && slope<=-0.40)?"PASS": lx.size()<=2?"no-F":"--");
    std::printf("       vs Phi_simple: rms relative resid = %6.1f%% over %d pts\n", rmsphi, nphi);
}

static double collapse_rms_control(
    const std::vector<Rec>& records,
    double floor_multiplier,
    bool scramble
) {
    std::vector<const Rec*> selected;
    for (const Rec& record : records) {
        if (record.scale!='D' && record.xi>0.0) {
            selected.push_back(&record);
        }
    }
    std::map<int,std::vector<double>> bins;
    const std::size_t rotation =
        selected.empty() ? 0 : selected.size()/3 + 17;
    for (std::size_t index=0; index<selected.size(); ++index) {
        const std::size_t exposure_index = scramble
            ? (index + rotation) % selected.size()
            : index;
        const double xi =
            selected[exposure_index]->xi / floor_multiplier;
        const int bin = static_cast<int>(
            std::floor(std::log10(xi)*2.0)
        );
        bins[bin].push_back(selected[index]->B);
    }
    double squared=0.0; int count=0;
    for (const auto& entry : bins) {
        if (entry.second.size()<3) continue;
        double total=0.0;
        for (double value : entry.second) total+=value;
        const double mean=total/static_cast<double>(entry.second.size());
        const double center=std::pow(10.0,(entry.first+0.5)/2.0);
        const double residual=(mean-Phi_simple(center))/Phi_simple(center);
        squared+=residual*residual; ++count;
    }
    return count>0 ? std::sqrt(squared/static_cast<double>(count))*100.0 : -1.0;
}

int main(int argc, char** argv){
    std::string dir = (argc>1)? argv[1] : ".";
    auto P=[&](const char* f){ return dir+"/"+f; };

    std::fprintf(stderr,"=== APS03 provenance log ===\n");
    std::fprintf(stderr,
        "B34 pressure-gradient candidate sealed before comparison:\n"
        "  angular fraction = %.12f\n"
        "  engaged fraction = %.12f\n"
        "  resistance density = %.8e kg/m^3\n"
        "  convergence gradient = %.8e Pa/m\n"
        "  a_floor analytic = %.8e m/s^2\n"
        "  a_floor finite-volume = %.8e m/s^2 (residual %.3e)\n",
        floor_closure.angular_fraction,
        floor_closure.engaged_fraction,
        floor_closure.resistance_density,
        floor_closure.pressure_gradient,
        floor_closure.acceleration,
        floor_closure.finite_volume_acceleration,
        floor_closure.finite_volume_residual);

    std::vector<Rec> R;
    double m4_rms, m4_btfr; int m4_n;
    scale_galactic(R, P("../../08_Galactic_Dynamics/GD05_Galaxy_Rotation_Curves/sparc_rotmod.csv"),
                      P("../../08_Galactic_Dynamics/GD05_Galaxy_Rotation_Curves/sparc_175.csv"), m4_rms,m4_btfr,m4_n);
    scale_atomic(R);
    scale_stellar(R, P("stellar_orbits.csv"));
    scale_nuclear(R, P("nuclear_binding.csv"));

    std::printf("\n================================================================\n");
    std::printf(" APS03: UNIVERSAL DRAFTING CROSSOVER  —  B = Phi(xi)\n");
    std::printf(" xi = g_self/g_floor ; g_floor=%.3e m/s^2 (Law-I/IV candidate)\n", a0);
    std::printf("================================================================\n\n");

    // ---- PILOT STOP-CHECK (sec.14): galactic harness must reproduce GD05 M4 ----
    std::printf("=== PILOT STOP-CHECK (Scale C must reproduce GD05 M4) ===\n");
    std::printf("  M4 = v_bar*sqrt(Phi_simple(g_bar/a_0)), per SPARC radial point\n");
    std::printf("  points = %d\n", m4_n);
    std::printf("  RMS  = %.1f%%   (GD05 M4 reference: 23.8%%)\n", m4_rms);
    std::printf("  BTFR = %.2f     (GD05 M4 reference: 3.58)\n", m4_btfr);
    bool pilot_ok = (m4_rms>0 && std::fabs(m4_rms-23.8)<2.0 && std::fabs(m4_btfr-3.58)<0.3);
    std::printf("  PILOT: %s\n\n", pilot_ok? "PASS — harness validated, proceeding"
                                            : "FAIL — harness disagrees with M4, results VOID");

    std::printf("=== PER-SCALE ASYMPTOTE TESTS (sec.6.A) ===\n");
    report_scale('C',R); report_scale('A',R); report_scale('B',R); report_scale('D',R);

    // ---- collapse: pool all scales, bin in log10(xi), compare scatter to Phi_simple
    std::printf("\n=== CROSS-SCALE COLLAPSE (sec.6.C/6.D) ===\n");
    std::printf("  bin(log10 xi) :   <B>     Phi_simple   scales-present  N\n");
    std::map<int,std::vector<const Rec*>> bins;
    for(const Rec& r: R){ if(r.xi>0){ int b=(int)std::floor(std::log10(r.xi)*2);/*half-dex*/ bins[b].push_back(&r);} }
    double collapse_sumsq=0; int collapse_n=0;
    for(auto& kv: bins){
        double xc=std::pow(10.0,(kv.first+0.5)/2.0);
        double sB=0; int n=0; std::string sc; bool hC=0,hA=0,hB=0,hD=0;
        for(auto* r: kv.second){ sB+=r->B; ++n; if(r->scale=='C')hC=1; if(r->scale=='A')hA=1; if(r->scale=='B')hB=1; if(r->scale=='D')hD=1; }
        double mB=sB/n; double pp=Phi_simple(xc);
        if(hC)sc+="C"; if(hA)sc+="A"; if(hB)sc+="B"; if(hD)sc+="D";
        if(n>=3){ double e=(mB-pp)/pp; collapse_sumsq+=e*e; ++collapse_n; }
        std::printf("  %+5.1f .. %+5.1f : %7.3f   %7.3f      %-4s            %d\n",
                    kv.first/2.0,(kv.first+1)/2.0, mB, pp, sc.c_str(), n);
    }
    double collapse_rms = collapse_n? std::sqrt(collapse_sumsq/collapse_n)*100.0 : -1;
    std::printf("\n  binned <B> vs Phi_simple: RMS = %.1f%% over %d bins (ALL scales)\n", collapse_rms, collapse_n);

    // ---- CLEAN collapse: C+A+B only (exclude mis-baselined nuclear D) ----
    std::map<int,std::vector<const Rec*>> binsCAB;
    for(const Rec& r: R){ if(r.scale!='D' && r.xi>0){ int b=(int)std::floor(std::log10(r.xi)*2); binsCAB[b].push_back(&r);} }
    double cab_sumsq=0; int cab_n=0;
    for(auto& kv: binsCAB){ double xc=std::pow(10.0,(kv.first+0.5)/2.0);
        double sB=0; int n=0; for(auto* r:kv.second){ sB+=r->B; ++n; }
        if(n>=3){ double pp=Phi_simple(xc); double e=(sB/n-pp)/pp; cab_sumsq+=e*e; ++cab_n; } }
    double cab_rms = cab_n? std::sqrt(cab_sumsq/cab_n)*100.0 : -1;
    std::printf("  binned <B> vs Phi_simple: RMS = %.1f%% over %d bins (C+A+B, nuclear excluded)\n", cab_rms, cab_n);

    // ---- NEGATIVE CONTROL (sec.8.3): wrong floor 100*a0 must DEGRADE the C+A+B collapse ----
    auto phi_wrong=[&](double g_self){ double xi2=g_self/(100.0*a0); return Phi_simple(xi2); };
    // recompute galactic+stellar B vs a wrong-floor Phi at each point's g_self = xi*a0
    double neg_sumsq=0; int neg_n=0;
    std::map<int,std::vector<std::pair<double,double>>> binsNeg; // key: floor(log10 xi_wrong*2) -> (B, xi_wrong)
    for(const Rec& r: R){ if(r.scale=='D'||r.xi<=0) continue; double g_self=r.xi*a0; double xi_w=g_self/(100.0*a0);
        if(xi_w<=0) continue; int b=(int)std::floor(std::log10(xi_w)*2); binsNeg[b].push_back({r.B,xi_w}); }
    for(auto& kv: binsNeg){ double xc=std::pow(10.0,(kv.first+0.5)/2.0); double sB=0; int n=0;
        for(auto&pr:kv.second){ sB+=pr.first; ++n; } if(n>=3){ double pp=Phi_simple(xc); double e=(sB/n-pp)/pp; neg_sumsq+=e*e; ++neg_n; } }
    double neg_rms = neg_n? std::sqrt(neg_sumsq/neg_n)*100.0 : -1;
    std::printf("  NEG-CONTROL wrong floor (100*a0): RMS = %.1f%% over %d bins (must be WORSE than %.1f%%)\n",
                neg_rms, neg_n, cab_rms);
    std::printf("  control verdict: %s\n",
                (cab_rms>0 && neg_rms>1.5*cab_rms)? "PASS (true floor collapses better -> test has power)"
                                                  : "INCONCLUSIVE (wrong floor not clearly worse)");

    const double wrong_solid_angle_rms =
        collapse_rms_control(R, 3.0, false);
    const double scrambled_exposure_rms =
        collapse_rms_control(R, 1.0, true);
    std::printf("  B34 wrong-solid-angle control (full normal load): RMS = %.1f%%\n",
                wrong_solid_angle_rms);
    std::printf("  B34 scrambled-exposure control: RMS = %.1f%%\n",
                scrambled_exposure_rms);

    // ---- emit corpus
    std::string outcsv = dir+"/aps03_corpus.csv";
    std::ofstream o(outcsv);
    o<<"scale,class,type,id,xi,B,sigmaB\n";
    for(const Rec& r:R) o<<r.scale<<","<<r.cls<<","<<r.type<<","<<r.id<<","
                         <<r.xi<<","<<r.B<<","<<r.sigmaB<<"\n";
    std::printf("\n  corpus written: %s  (%zu rows)\n", outcsv.c_str(), R.size());

    // Comparison enters only after the floor and all control predictions have
    // been emitted.
    const double measured_floor = 1.20e-10;
    const double floor_residual =
        std::fabs(a0/measured_floor-1.0);
    const bool controls_pass =
        wrong_solid_angle_rms >= 2.0*cab_rms
        && scrambled_exposure_rms >= 2.0*cab_rms;
    const bool b34_pass =
        floor_closure.finite_volume_residual < 0.01
        && floor_residual <= 0.20
        && controls_pass;
    std::printf("\n=== B34 DIRECT GATE ===\n");
    std::printf("  predicted floor = %.8e m/s^2\n",a0);
    std::printf("  measured floor  = %.8e m/s^2 (comparison only)\n",measured_floor);
    std::printf("  residual = %.2f%% (gate <=20%%)\n",100.0*floor_residual);
    std::printf("  finite-volume gate %s; two-control gate %s\n",
                floor_closure.finite_volume_residual<0.01?"PASS":"FAIL",
                controls_pass?"PASS":"FAIL");
    std::printf("  B34 %s\n",b34_pass?"COMPUTED":"PENDING");

    std::printf("\n=== CURRENT STATUS ===\n");
    std::printf("  Scale C galactic: real SPARC, pilot %s.\n", pilot_ok?"PASS":"FAIL");
    std::printf("  Scale A atomic:   real APS02/NIST resonance lines; xi rule STATED (sec.7.3 open).\n");
    std::printf("  Scale B stellar: Solar-host rows only; catalogue host-load aliases ignored.\n");
    std::printf("  Scale D nuclear: present only if CSV fetched (else SHORT above).\n");
    std::printf("  Phi crossover shape is BORROWED (MOND-simple); only asymptotes DERIVED.\n");
    return pilot_ok && b34_pass ? 0 : 1;
}
