// ════════════════════════════════════════════════════════════════════════
//  CQ-45 · Redshift = emission(atom) + propagation(spation)
//  EXHAUSTIVE FIT of the binned Pantheon Hubble diagram (Scolnic 2018, 40 bins)
//  to a battery of distance–redshift laws. Honest: if SDT fails, it fails.
//
//  This tool tests the PROPAGATION half (the distance–redshift law). For each
//  model it computes a dimensionless luminosity-distance SHAPE D_L(z); the
//  single nuisance OFFSET a = (M − 5log10 H0 + 25 + 5log10 c) is fit by weighted
//  least squares (it is linear in μ, so a* = Σw(mb−μ_shape)/Σw). The SHAPE is
//  therefore what is being tested — exactly the part that "needs dark energy".
//
//  Models:
//   ΛCDM(Ω_m)  : D_L=(1+z)∫₀ᶻ dz'/√(Ω_m(1+z')³+1−Ω_m)        [2 params: a, Ω_m]
//   EdS        : Ω_m=1 decelerating null, D_L=(1+z)·2(1−1/√(1+z)) [1 param: a]
//   Milne      : empty/coasting, D_L=((1+z)²−1)/2               [1 param: a]
//   Linear     : d=cz/H0, D_L=z(1+z)                            [1 param: a]
//   SDT-exp    : amplitude-squeeze const-κ (n→1), D_L=(1+z)ln(1+z) [1 param: a]
//   SDT n=4    : doc §7.2, D_L=(1+z)[1−(1+z)⁻³]/3               [1 param: a]
//   SDT n-free : D_L=(1+z)[1−(1+z)^−(n−1)]/(n−1), scan n        [2 params: a, n]
//
//  Scoring: χ², χ²/dof, AIC=χ²+2k, BIC=χ²+k·lnN. Lower is better. ΔAIC vs best.
//  Data: data/pantheon_binned_DS17f.txt (mb = standardised peak B mag, dmb error).
//
//  Build: cl /std:c++20 /EHsc /O2 /Fe:cq45.exe cq45_redshift_fit.cpp
//  Author: J.C. Harvey, Melbourne.
// ════════════════════════════════════════════════════════════════════════

#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

// ── REAL DATA: 40 binned Pantheon points {zcmb, mb, dmb} (Scolnic 2018) ──
struct Pt { double z, mb, dmb; };
static const std::vector<Pt> DATA = {
 {0.014,14.57001926,0.0311},{0.0194,15.2279603507,0.02645},{0.0264,15.934102317,0.0231},
 {0.0329,16.4217829558,0.0235},{0.0396,16.836418956,0.02845},{0.0475,17.2346439906,0.0334},
 {0.056,17.5758459622,0.03215},{0.064,17.9104543501,0.0439},{0.0721,18.1780074589,0.03865},
 {0.0811,18.5543855764,0.04225},{0.0889,18.7006554037,0.03635},{0.1001,19.0388242428,0.03515},
 {0.1071,19.1720185353,0.03355},{0.1195,19.3711295152,0.026},{0.1278,19.5555026238,0.02635},
 {0.1396,19.8185930766,0.02335},{0.1519,19.9445025196,0.0237},{0.1635,20.0642537602,0.02585},
 {0.1778,20.3389008923,0.01965},{0.1906,20.5047456137,0.02205},{0.2067,20.6854007995,0.0214},
 {0.2216,20.8610322507,0.0233},{0.2405,21.0518440051,0.0222},{0.2558,21.2037930719,0.02025},
 {0.2762,21.3636137766,0.0221},{0.2972,21.5790014334,0.0216},{0.3215,21.813277279,0.0214},
 {0.3453,21.9665751024,0.0234},{0.3708,22.1428940056,0.02145},{0.4049,22.3799192408,0.03225},
 {0.4355,22.5579272526,0.0254},{0.4738,22.797376642,0.02935},{0.5174,23.0011594448,0.02685},
 {0.5742,23.3004345026,0.0245},{0.6299,23.5036280324,0.031},{0.724,23.8666293039,0.027},
 {0.821,24.2445519795,0.0248},{0.9511,24.6411323707,0.0276},{1.2336,25.3039940191,0.05635},
 {1.6123,25.9259729107,0.0735}
};

// comoving-distance integrand integral ∫₀ᶻ dz'/E(z') by Simpson (E from ΛCDM)
static double lcdm_DC(double z, double Om){
    int N=2000; double h=z/N, s=0;
    auto E=[&](double zz){ return std::sqrt(Om*std::pow(1+zz,3)+(1-Om)); };
    for(int i=0;i<=N;i++){ double zz=i*h, f=1.0/E(zz); s += (i==0||i==N?1:(i%2?4:2))*f; }
    return s*h/3.0;
}
// dimensionless luminosity-distance SHAPE for each model (drop c/H0; absorbed by offset)
static double DL(const std::string& m, double z, double p){
    double zp=1+z;
    if(m=="LCDM")   return zp*lcdm_DC(z,p);
    if(m=="EdS")    return zp*2.0*(1.0-1.0/std::sqrt(zp));
    if(m=="Milne")  return (zp*zp-1.0)/2.0;
    if(m=="Linear") return z*zp;
    if(m=="SDTexp") return zp*std::log(zp);
    if(m=="SDTn4")  return zp*(1.0-std::pow(zp,-3.0))/3.0;
    if(m=="SDTn"){ double e=p-1.0; if(std::fabs(e)<1e-9) return zp*std::log(zp);
                   return zp*(1.0-std::pow(zp,-e))/e; }
    return 0;
}
// fit nuisance offset analytically; return chi2
static double chi2_for(const std::string& m, double p){
    double Sw=0,Swd=0;
    for(auto&d:DATA){ double w=1.0/(d.dmb*d.dmb); double mush=5.0*std::log10(DL(m,d.z,p));
        Sw+=w; Swd+=w*(d.mb-mush); }
    double a=Swd/Sw, c2=0;
    for(auto&d:DATA){ double w=1.0/(d.dmb*d.dmb); double mush=5.0*std::log10(DL(m,d.z,p));
        double r=d.mb-mush-a; c2+=w*r*r; }
    return c2;
}
static double best_offset(const std::string& m,double p){
    double Sw=0,Swd=0; for(auto&d:DATA){double w=1.0/(d.dmb*d.dmb);double mush=5.0*std::log10(DL(m,d.z,p));Sw+=w;Swd+=w*(d.mb-mush);} return Swd/Sw;
}

int main(){
    const int N=(int)DATA.size();
    const double lnN=std::log((double)N);
    struct Res{ std::string name; int k; double chi2,par; };
    std::vector<Res> R;

    // 1-parameter (offset-only) models
    const std::vector<std::string> oneP={"EdS","Milne","Linear","SDTexp","SDTn4"};
    for(const auto& m:oneP)
        R.push_back({m,1,chi2_for(m,0.0),0.0});

    // ΛCDM: scan Ω_m
    { double bOm=0,bc=1e30; for(int i=0;i<=1000;i++){double Om=i/1000.0; double c=chi2_for("LCDM",Om); if(c<bc){bc=c;bOm=Om;}}
      R.push_back({"LCDM",2,bc,bOm}); }
    // SDT n-free: scan n over a wide range (incl. n<1) to find the TRUE optimum
    { double bn=0,bc=1e30; for(int i=0;i<=11000;i++){double n=-3.0+i/1000.0; if(std::fabs(n)<1e-6)continue; double c=chi2_for("SDTn",n); if(c<bc){bc=c;bn=n;}}
      R.push_back({"SDTn(free)",2,bc,bn}); }

    std::sort(R.begin(),R.end(),[&](const Res&a,const Res&b){return (a.chi2+2*a.k)<(b.chi2+2*b.k);});
    double bestAIC=R.front().chi2+2*R.front().k;

    std::printf("================================================================================\n");
    std::printf(" CQ-45 — binned Pantheon Hubble diagram (Scolnic 2018, N=%d bins) vs model battery\n",N);
    std::printf("         SHAPE fit, 1 nuisance offset; lower AIC/BIC = better. HONEST ranking.\n");
    std::printf("================================================================================\n\n");
    std::printf("%-12s %3s %10s %9s %10s %10s %9s  %s\n","model","k","chi2","chi2/dof","AIC","BIC","dAIC","best param");
    std::printf("%s\n",std::string(86,'-').c_str());
    for(auto&r:R){ double aic=r.chi2+2*r.k, bic=r.chi2+r.k*lnN, dof=N-r.k;
        std::string pp = (r.name=="LCDM")?("Om="+std::to_string(r.par)) :
                         (r.name=="SDTn(free)")?("n="+std::to_string(r.par)) : "-";
        std::printf("%-12s %3d %10.2f %9.3f %10.2f %10.2f %9.2f  %s\n",
            r.name.c_str(),r.k,r.chi2,r.chi2/dof,aic,bic,aic-bestAIC,pp.c_str());
    }

    // residual structure (mb_obs - model) for key models, low/mid/high z
    std::printf("\n--- residuals  (mb_obs − mb_model)  [mag] : where each model breaks ---\n");
    std::vector<std::pair<std::string,double>> keys={{"LCDM",0},{"SDTn(free)",0},{"SDTexp",0},{"SDTn4",0},{"EdS",0},{"Milne",0}};
    for(auto&k:keys){ for(auto&r:R) if(r.name==k.first||(k.first=="LCDM"&&r.name=="LCDM")||(k.first=="SDTn(free)"&&r.name=="SDTn(free)")) k.second=r.par; }
    std::printf("%-7s","z");
    for(auto&k:keys) std::printf("%10s",k.first.c_str()); std::printf("\n");
    for(double zt:{0.02,0.1,0.3,0.6,1.0,1.61}){
        // nearest data point
        const Pt* best=nullptr; double bd=1e9; for(auto&d:DATA) if(std::fabs(d.z-zt)<bd){bd=std::fabs(d.z-zt);best=&d;}
        std::printf("%-7.3f",best->z);
        for(auto&k:keys){ double a=best_offset(k.first=="SDTn(free)"?"SDTn":k.first, k.second);
            double mush=5.0*std::log10(DL(k.first=="SDTn(free)"?"SDTn":k.first,best->z,k.second));
            std::printf("%10.3f", best->mb-mush-a); }
        std::printf("\n");
    }

    std::printf("\n--- the 'acceleration' signature: Δμ = μ_obs − μ_Milne(empty) [mag] ---\n");
    std::printf("(ΛCDM needs +Λ to bend up at z~0.4; does any SDT law reproduce the same bend?)\n");
    double aM=best_offset("Milne",0);
    std::printf("%-7s %12s %12s %12s\n","z","obs-Milne","LCDM-Milne","SDTn-Milne");
    double aLC=0,aSn=0,Om=0,nf=0; for(auto&r:R){if(r.name=="LCDM"){Om=r.par;}if(r.name=="SDTn(free)"){nf=r.par;}}
    aLC=best_offset("LCDM",Om); aSn=best_offset("SDTn",nf);
    for(double zt:{0.05,0.2,0.4,0.7,1.0,1.61}){
        const Pt* best=nullptr; double bd=1e9; for(auto&d:DATA) if(std::fabs(d.z-zt)<bd){bd=std::fabs(d.z-zt);best=&d;}
        double muM=5.0*std::log10(DL("Milne",best->z,0))+aM;
        double obs=best->mb-muM;
        double lc =5.0*std::log10(DL("LCDM",best->z,Om))+aLC-muM;
        double sn =5.0*std::log10(DL("SDTn",best->z,nf))+aSn-muM;
        std::printf("%-7.3f %12.4f %12.4f %12.4f\n",best->z,obs,lc,sn);
    }

    std::printf("\n--- VERDICT (read the AIC table) ---\n");
    std::printf("best model: %s (AIC=%.2f). SDT n=4 (doc claim) dAIC=%.2f.\n",
        R.front().name.c_str(), bestAIC, [&]{for(auto&r:R)if(r.name=="SDTn4")return r.chi2+2*r.k-bestAIC;return 0.0;}());
    std::printf("note: binned dmb are tiny (~0.02-0.07 mag) so ALL absolute chi2/dof>1;\n");
    std::printf("the honest comparison is RELATIVE (dAIC) + residual shape, not absolute chi2.\n");
    return 0;
}
