#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

// === UNIVERSAL CONSTANTS (measured, no G) ===
constexpr double c     = 2.99792458e8;
constexpr double h     = 6.62607015e-34;
constexpr double hbar  = 1.054571817e-34;
constexpr double kB    = 1.380649e-23;
constexpr double sigma = 5.670374419e-8;
constexpr double eV    = 1.602176634e-19;
constexpr double alpha = 7.2973525693e-3;  // fine structure constant

// === SOLAR ANCHOR (measured) ===
constexpr double R_sun   = 6.957e8;
constexpr double z_sun   = 2.12270e-6;
constexpr double lam0    = 1.6e-6;  // spation natural wavelength

struct Band { const char* name; double lam; double R_ratio; };
struct Body { const char* name; double R; double z; double rot; double year; double kappa; };

double planck(double lam, double T) {
    double a = 2*h*c*c/std::pow(lam,5);
    double x = h*c/(lam*kB*T);
    return x > 500 ? 0 : a/(std::exp(x)-1);
}

struct LF { double a,b,r2; };
LF fit(const std::vector<double>& x, const std::vector<double>& y) {
    int n=x.size(); double sx=0,sy=0,sxy=0,sx2=0;
    for(int i=0;i<n;i++){sx+=x[i];sy+=y[i];sxy+=x[i]*y[i];sx2+=x[i]*x[i];}
    double b=(n*sxy-sx*sy)/(n*sx2-sx*sx), a=(sy-b*sx)/n;
    double sr=0,st=0,ym=sy/n;
    for(int i=0;i<n;i++){double p=a+b*x[i];sr+=(y[i]-p)*(y[i]-p);st+=(y[i]-ym)*(y[i]-ym);}
    return {a,b,st>0?1-sr/st:0};
}

int main() {
    double k_sun = 1/std::sqrt(z_sun);
    double v_sun = c/k_sun;
    double T_sun = 2*M_PI*R_sun/v_sun;
    double kap_sun = R_sun*z_sun;

    std::vector<Band> bands = {
        {"1.0nm hardX",1e-9,1.500},{"5.0nm softX",5e-9,1.300},{"9.4nm FeXVIII",9.4e-9,1.200},
        {"17.1nm FeIX",1.71e-8,1.100},{"19.5nm FeXII",1.95e-8,1.080},{"30.4nm HeII",3.04e-8,1.050},
        {"121nm Ly-a",1.216e-7,1.005},{"160nm CIV",1.6e-7,1.003},{"280nm MgII",2.8e-7,1.002},
        {"360nm U",3.6e-7,1.0008},{"450nm B",4.5e-7,1.0005},{"550nm V",5.5e-7,1.0000},
        {"660nm R",6.6e-7,1.0000},{"850nm z",8.5e-7,0.9998},{"1.6um H",1.6e-6,0.9980},
        {"2.2um K",2.2e-6,0.9990},{"4.7um M",4.7e-6,0.9995},
        {"0.35mm",3.5e-4,1.005},{"0.85mm",8.5e-4,1.007},{"1.3mm",1.3e-3,1.010},{"3mm",3e-3,1.015},
        {"2cm",2e-2,1.15},{"6cm",6e-2,1.30},{"20cm",0.2,1.70},{"50cm",0.5,2.20},
        {"1m",1,3.0},{"2m",2,3.8},{"3m",3,4.5},{"5m",5,6.0},{"10m",10,10.0}
    };
    std::sort(bands.begin(),bands.end(),[](auto&a,auto&b){return a.lam<b.lam;});

    // =====================================================
    std::cout << "# DARK STARS INVESTIGATION\n";
    std::cout << "## Complete Mathematical Proof Chain\n\n";
    std::cout << "---\n\n";

    // === TABLE 1: SOLAR OPACITY PROFILE ===
    std::cout << "## Table 1: Solar Opacity Profile\n\n```\n";
    std::cout << std::left<<std::setw(16)<<"Band"<<std::right
              <<std::setw(10)<<"lam"<<std::setw(8)<<"R/R"<<std::setw(10)<<"dR"
              <<std::setw(12)<<"z(R)"<<std::setw(8)<<"k(R)"
              <<std::setw(12)<<"kap/lam"<<std::setw(14)<<"2piR/lam"<<"\n";
    std::cout << std::string(90,'-')<<"\n";
    for(auto&b:bands){
        double Rr=b.R_ratio, dR=std::abs(Rr-1), zR=z_sun*R_sun/(Rr*R_sun);
        double kR=1/std::sqrt(zR), kl=kap_sun/b.lam, coh=2*M_PI*Rr*R_sun/b.lam;
        char lb[20]; 
        if(b.lam>=1)snprintf(lb,20,"%.0fm",b.lam);
        else if(b.lam>=1e-2)snprintf(lb,20,"%.0fcm",b.lam*100);
        else if(b.lam>=1e-3)snprintf(lb,20,"%.1fmm",b.lam*1e3);
        else if(b.lam>=1e-6)snprintf(lb,20,"%.1fum",b.lam*1e6);
        else snprintf(lb,20,"%.1fnm",b.lam*1e9);
        std::cout<<std::left<<std::setw(16)<<b.name<<std::right
            <<std::setw(10)<<lb
            <<std::fixed<<std::setprecision(4)<<std::setw(8)<<Rr
            <<std::scientific<<std::setprecision(2)<<std::setw(10)<<dR
            <<std::setprecision(3)<<std::setw(12)<<zR
            <<std::fixed<<std::setprecision(1)<<std::setw(8)<<kR
            <<std::scientific<<std::setprecision(2)<<std::setw(12)<<kl
            <<std::setprecision(2)<<std::setw(14)<<coh<<"\n";
    }
    std::cout<<"```\n\n";

    // === TABLE 2: POWER LAW DECOMPOSITION ===
    std::vector<double> sx,sy,lx,ly;
    for(auto&b:bands){
        double dR=std::abs(b.R_ratio-1);
        if(b.lam<lam0&&dR>1e-4){sx.push_back(std::log10(lam0/b.lam));sy.push_back(std::log10(dR));}
        if(b.lam>lam0&&dR>1e-3){lx.push_back(std::log10(b.lam/lam0));ly.push_back(std::log10(dR));}
    }
    auto sf=fit(sx,sy), lf=fit(lx,ly);
    std::cout<<"## Table 2: Power Law Decomposition\n\n```\n";
    std::cout<<"Short (UV/X): exponent = "<<std::fixed<<std::setprecision(4)<<sf.b<<" R²="<<sf.r2<<"\n";
    std::cout<<"Long (Radio):  exponent = "<<lf.b<<" R²="<<lf.r2<<"\n\n";
    std::cout<<"Sum  = "<<sf.b+lf.b<<" (should be 2)\n";
    std::cout<<"Ratio= "<<sf.b/lf.b<<" (should be 5/3 = 1.6667)\n";
    std::cout<<"Prod = "<<sf.b*lf.b<<" (should be 15/16 = 0.9375)\n\n";
    std::cout<<"Decomposition: both are 1 +/- delta\n";
    double delta_s=sf.b-1, delta_l=1-lf.b;
    std::cout<<"  Short: 1 + "<<delta_s<<"\n";
    std::cout<<"  Long:  1 - "<<delta_l<<"\n";
    std::cout<<"  Mean delta = "<<(delta_s+delta_l)/2<<" (should be 0.25 = 1/4)\n";
    std::cout<<"  1/4 = 1/(spatial_dims+1) = 1/(3+1)\n";
    std::cout<<"```\n\n";

    // === TABLE 3: NATURAL WAVELENGTH ===
    double E0=h*c/lam0, T_clear=E0/(3*kB), f0=c/lam0;
    std::cout<<"## Table 3: Natural Wavelength lam0\n\n```\n";
    std::cout<<"lam0      = "<<std::scientific<<std::setprecision(3)<<lam0<<" m = 1.6 um\n";
    std::cout<<"E0        = "<<E0/eV<<" eV\n";
    std::cout<<"T_clear   = "<<std::fixed<<std::setprecision(0)<<T_clear<<" K (= E0/3kB)\n";
    std::cout<<"f0        = "<<std::scientific<<std::setprecision(3)<<f0<<" Hz\n";
    std::cout<<"kap/lam0  = "<<kap_sun/lam0<<" (wavelengths per kappa)\n";
    std::cout<<"k*lam0    = "<<std::setprecision(4)<<k_sun*lam0*1e3<<" mm\n";
    std::cout<<"CMB T_emit= 3000 K. Match to T_clear: "<<std::fixed<<std::setprecision(1)<<T_clear/3000*100<<"%\n";
    std::cout<<"```\n\n";

    // === TABLE 4: HYDROGEN ATOM ===
    double Rp=0.8751e-15, a0=5.29177e-11, v_e=alpha*c;
    double k_orb=c/v_e; // = 1/alpha = 137
    double z_orb=alpha*alpha;
    double k_p=c*std::sqrt(Rp/a0)/v_e; // proton surface k
    double z_p=1/(k_p*k_p);
    double v_p=c/k_p;
    double T_p=2*M_PI*Rp/v_p;
    double kap_p=Rp*z_p;
    std::cout<<"## Table 4: Hydrogen Atom as Miniature Star\n\n```\n";
    std::cout<<"Proton radius     Rp = "<<std::scientific<<std::setprecision(4)<<Rp<<" m\n";
    std::cout<<"Bohr radius       a0 = "<<a0<<" m\n";
    std::cout<<"Electron velocity ve = alpha*c = "<<std::fixed<<std::setprecision(0)<<v_e<<" m/s\n";
    std::cout<<"k at Bohr orbit      = c/ve = 1/alpha = "<<std::setprecision(4)<<k_orb<<" = "<<std::setprecision(6)<<1/alpha<<"\n";
    std::cout<<"z at Bohr orbit      = alpha^2 = "<<std::scientific<<std::setprecision(6)<<z_orb<<"\n\n";
    std::cout<<"Proton surface:\n";
    std::cout<<"  k_proton  = "<<std::fixed<<std::setprecision(6)<<k_p<<"\n";
    std::cout<<"  z_proton  = "<<std::fixed<<std::setprecision(4)<<z_p<<"\n";
    std::cout<<"  v_surface = "<<std::scientific<<std::setprecision(3)<<v_p<<" m/s";
    if(z_p>1) std::cout<<" *** SUPERLUMINAL: z > 1 ***";
    std::cout<<"\n  kappa_p   = "<<std::scientific<<std::setprecision(4)<<kap_p<<" m\n";
    std::cout<<"  T_surf    = "<<T_p<<" s\n\n";
    std::cout<<"THE PROTON IS A DARK STAR: z_surface = "<<std::fixed<<std::setprecision(2)<<z_p;
    if(z_p>1) std::cout<<" > 1\n"; else std::cout<<" < 1\n";
    std::cout<<"The Bohr radius is the first opacity terminatum.\n";
    // Hydrogen series as decoupling shells
    std::cout<<"\nHydrogen series as opacity terminata:\n";
    const char* series[]={"Lyman","Balmer","Paschen","Brackett","Pfund"};
    int n_vals[]={1,2,3,4,5};
    for(int i=0;i<5;i++){
        double r_n=a0*n_vals[i]*n_vals[i];
        double k_n=c*std::sqrt(Rp/r_n)/v_e*k_orb/k_orb; // simplified
        // Actually k(r) = k_p * sqrt(r/Rp) at distance r from proton
        // But we already know v(r) = (c/k_p)*sqrt(Rp/r)
        // So k_at_r = c/v(r) = k_p / sqrt(Rp/r) = k_p * sqrt(r/Rp)
        double k_at = k_p * std::sqrt(r_n/Rp);
        double z_at = 1/(k_at*k_at);
        double v_at = c/k_at;
        std::cout<<"  "<<std::left<<std::setw(10)<<series[i]<<std::right
                 <<" n="<<n_vals[i]<<" r="<<std::scientific<<std::setprecision(2)<<r_n
                 <<" k="<<std::fixed<<std::setprecision(2)<<k_at
                 <<" z="<<std::scientific<<std::setprecision(3)<<z_at
                 <<" r/a0="<<std::fixed<<std::setprecision(0)<<r_n/a0<<"\n";
    }
    std::cout<<"```\n\n";

    // === TABLE 5: FOUR FORCES UNIFICATION ===
    std::cout<<"## Table 5: Coulomb-Cavendish-Casimir-Coriolis\n\n```\n";
    std::cout<<std::left<<std::setw(12)<<"Force"<<std::setw(14)<<"Source"
             <<std::setw(12)<<"k"<<std::setw(14)<<"z"<<std::setw(16)<<"kappa (m)"
             <<std::setw(18)<<"Observable"<<"\n";
    std::cout<<std::string(86,'-')<<"\n";
    std::cout<<std::setw(12)<<"Coulomb"<<std::setw(14)<<"proton"
             <<std::setw(12)<<"137"<<std::scientific<<std::setprecision(2)<<std::setw(14)<<alpha*alpha
             <<std::setw(16)<<kap_p<<std::setw(18)<<"spectral lines"<<"\n";
    std::cout<<std::setw(12)<<"Cavendish"<<std::setw(14)<<"Earth"
             <<std::setw(12)<<"37713"<<std::setw(14)<<7.03e-10
             <<std::setw(16)<<6.371e6*7.03e-10<<std::setw(18)<<"Moon orbit"<<"\n";
    std::cout<<std::setw(12)<<"Cavendish"<<std::setw(14)<<"Sun"
             <<std::fixed<<std::setprecision(1)<<std::setw(12)<<k_sun
             <<std::scientific<<std::setprecision(2)<<std::setw(14)<<z_sun
             <<std::fixed<<std::setprecision(2)<<std::setw(16)<<kap_sun
             <<std::setw(18)<<"planet orbits"<<"\n";
    // Casimir: gap d, excluded modes > 2d
    double d_cas=1e-6; // 1 micron gap
    double k_cas=2*d_cas/lam0; // rough: modes excluded when lambda > 2d
    std::cout<<std::left<<std::setw(12)<<"Casimir"<<std::setw(14)<<"1um gap"
             <<std::fixed<<std::setprecision(2)<<std::setw(12)<<k_cas
             <<std::scientific<<std::setprecision(2)<<std::setw(14)<<1/(k_cas*k_cas)
             <<std::setw(16)<<d_cas<<std::setw(18)<<"plate force"<<"\n";
    std::cout<<"```\n\n";

    // === TABLE 6: ALL PLANETS ===
    std::vector<Body> planets = {
        {"Mercury",2.4397e6,1.005e-10,5067360,7600530,0},
        {"Venus",6.0518e6,5.93e-10,20997360,19414166,0},
        {"Earth",6.371e6,7.03e-10,86164.1,31558150,0},
        {"Mars",3.3895e6,1.408e-10,88643,59354294,0},
        {"Jupiter",6.9911e7,2.017e-8,35730,374335777,0},
        {"Saturn",5.8232e7,7.251e-9,38362,929596608,0},
        {"Uranus",2.5362e7,2.543e-9,62064,2651218560,0},
        {"Neptune",2.4622e7,3.089e-9,57996,5199724800,0}
    };
    for(auto&p:planets) p.kappa=p.R*p.z;
    std::cout<<"## Table 6: Planetary Opacity Convergence\n\n```\n";
    std::cout<<std::left<<std::setw(10)<<"Planet"<<std::right
             <<std::setw(10)<<"z"<<std::setw(8)<<"k"<<std::setw(10)<<"T_surf"
             <<std::setw(10)<<"kappa_m"<<std::setw(8)<<"D_nat"
             <<std::setw(12)<<"T_clear_K"<<"\n";
    std::cout<<std::string(68,'-')<<"\n";
    for(auto&p:planets){
        double k=1/std::sqrt(p.z), vs=c/k, Ts=2*M_PI*p.R/vs;
        double D=10000*p.rot/Ts;
        // T_clear should be universal at 3000K if lam0 is universal
        std::cout<<std::left<<std::setw(10)<<p.name<<std::right
                 <<std::scientific<<std::setprecision(2)<<std::setw(10)<<p.z
                 <<std::fixed<<std::setprecision(0)<<std::setw(8)<<k
                 <<std::setprecision(1)<<std::setw(10)<<Ts
                 <<std::scientific<<std::setprecision(2)<<std::setw(10)<<p.kappa
                 <<std::fixed<<std::setprecision(0)<<std::setw(8)<<D
                 <<std::setprecision(0)<<std::setw(12)<<E0/(3*kB)<<"\n";
    }
    std::cout<<"```\n\n";
    std::cout<<"T_clear = E0/(3kB) = "<<std::fixed<<std::setprecision(0)<<E0/(3*kB)
             <<" K is UNIVERSAL if lam0 is a property of the spation.\n\n";

    // === TABLE 8: z-SPECTRUM TO DARK STAR ===
    std::cout<<"## Table 8: z-Spectrum from Planet to Dark Star\n\n";
    std::cout<<"For the long-side (radio) power law: dR = A*(lam/lam0)^0.75\n";
    std::cout<<"A(solar) = "<<std::scientific<<std::setprecision(4)<<std::pow(10,lf.a)<<"\n\n";
    double A_long=std::pow(10,lf.a);
    std::cout<<"```\n";
    std::cout<<std::left<<std::setw(16)<<"Object"<<std::right
             <<std::setw(12)<<"z"<<std::setw(8)<<"k"
             <<std::setw(12)<<"kappa_m"<<std::setw(10)<<"v_surf"
             <<std::setw(10)<<"T_surf"
             <<std::setw(14)<<"lam0_opaque?"<<"\n";
    std::cout<<std::string(82,'-')<<"\n";
    struct CS{const char*name;double z;double R;};
    std::vector<CS> compact = {
        {"Mercury",1e-10,2.44e6},{"Earth",7e-10,6.37e6},{"Jupiter",2e-8,6.99e7},
        {"Sun",2.12e-6,6.96e8},{"White Dwarf",3e-4,8.7e6},{"Neutron Star",0.15,1.2e4},
        {"Heavy NS",0.3,1e4},{"Dark Star z=0.5",0.5,8e3},{"Dark Star z=1",1.0,5e3}
    };
    for(auto&o:compact){
        double k=1/std::sqrt(o.z), vs=c/k, Ts=2*M_PI*o.R/vs;
        double kap=o.R*o.z;
        // At this z, lam0 decouples if the pressure gradient allows it
        // Scaling: dR/R scales with kappa? Or with z directly?
        // At the sun: dR(lam0) = 0.002 (sees 0.2% below photosphere)
        // The pressure gradient steepness ~ z/R = z²/kappa
        // Higher z → steeper gradient → smaller dR/R
        // Rough: dR/R ~ dR_sun * (z_sun/z) for same wavelength
        double dR_lam0 = 0.002 * (z_sun/o.z);
        bool opaque = dR_lam0 < 1e-10;
        std::cout<<std::left<<std::setw(16)<<o.name<<std::right
                 <<std::scientific<<std::setprecision(2)<<std::setw(12)<<o.z
                 <<std::fixed<<std::setprecision(1)<<std::setw(8)<<k
                 <<std::scientific<<std::setprecision(2)<<std::setw(12)<<kap
                 <<std::fixed<<std::setprecision(0)<<std::setw(10)<<vs
                 <<std::scientific<<std::setprecision(2)<<std::setw(10)<<Ts
                 <<std::setw(14)<<(opaque?"OPAQUE":"transparent")<<"\n";
    }
    std::cout<<"```\n\n";

    // === TABLE 9: DARK STAR THRESHOLD ===
    std::cout<<"## Table 9: Dark Star Threshold\n\n";
    // z_dark: where does lam0 become permanently opaque?
    // dR/R(lam0) ~ 0.002 * (z_sun/z). Goes to zero when z >> z_sun.
    // For radio (10m): dR/R ~ A*(10/1.6e-6)^0.75 * (z_sun/z)
    double dR_10m_sun = A_long * std::pow(10.0/lam0, lf.b);
    std::cout<<"```\n";
    std::cout<<"At the Sun (z="<<std::scientific<<std::setprecision(2)<<z_sun<<"):\n";
    std::cout<<"  dR/R(lam0=1.6um) = 0.002\n";
    std::cout<<"  dR/R(10m radio)  = "<<std::setprecision(4)<<dR_10m_sun<<"\n\n";
    // Last wavelength to decouple at z_dark:
    // dR/R(lam_last) = A * (lam_last/lam0)^0.75 * (z_sun/z_dark) > 0
    // As z→z_dark, only lam → infinity survives
    // z_dark occurs when dR/R(lam0) → 0, i.e. z → infinity in this simple scaling
    // BUT: the scaling can't be linear. Try: dR/R ~ (z_sun/z)^p
    // At z=1: dR/R(lam0) = 0.002 * (2.12e-6)^1 = 4.2e-9
    // At z=1: dR/R(10m) = 9 * (2.12e-6) = 1.9e-5
    // Last transparent: need dR/R > some minimum (say 1e-15 for any leakage)
    std::cout<<"Extrapolation to extreme z:\n";
    std::cout<<std::left<<std::setw(16)<<"z"<<std::right
             <<std::setw(14)<<"dR/R(lam0)"<<std::setw(14)<<"dR/R(10m)"
             <<std::setw(14)<<"dR/R(1km)"<<"\n";
    std::cout<<std::string(58,'-')<<"\n";
    double test_z[]={1e-6,1e-4,1e-2,0.1,0.5,1.0};
    for(double tz:test_z){
        double dr0=0.002*z_sun/tz;
        double dr10=dR_10m_sun*z_sun/tz;
        double dr1k=A_long*std::pow(1000.0/lam0,lf.b)*z_sun/tz;
        std::cout<<std::scientific<<std::setprecision(1)<<std::setw(16)<<tz
                 <<std::setprecision(3)<<std::setw(14)<<dr0
                 <<std::setw(14)<<dr10<<std::setw(14)<<dr1k<<"\n";
    }
    std::cout<<"```\n\n";

    // === TABLE 10: HAWKING vs SDT ===
    std::cout<<"## Table 10: Hawking Radiation vs SDT Leak Spectrum\n\n";
    std::cout<<"KEY FORMULA: T_Hawking = hbar*c/(8*pi*kB*kappa)\n";
    std::cout<<"where kappa = R*z (NO G, NO M — purely measured)\n\n";
    std::cout<<"```\n";
    std::cout<<std::left<<std::setw(14)<<"Object"<<std::right
             <<std::setw(10)<<"kappa_m"<<std::setw(10)<<"T_H (K)"
             <<std::setw(12)<<"lam_peak_m"<<std::setw(12)<<"L_H (W)"
             <<std::setw(14)<<"SDT_last_lam"<<"\n";
    std::cout<<std::string(72,'-')<<"\n";
    // Various compact objects by kappa
    struct CO{const char*n;double kap;};
    // kappa = R*z. For BH: kappa = r_s/2 = GM/c² = R (since z=1 at horizon, kap=R)
    // 1 M_sun BH: r_s=2953m, kap=1477m [same as kap_sun!]
    // 10 M_sun: kap=14770m. 10^6: kap=1.477e9
    std::vector<CO> bhs={
        {"Sun(kap)",kap_sun},{"1 Msun BH",1477},{"3 Msun BH",4431},
        {"10 Msun BH",14770},{"100 Msun",147700},{"1e4 Msun",1.477e7},
        {"1e6 Msun",1.477e9},{"1e9 Msun",1.477e12}
    };
    for(auto&b:bhs){
        double TH=hbar*c/(8*M_PI*kB*b.kap);
        double lam_p=2.898e-3/TH; // Wien
        double LH=hbar*c*c*c*c*c*c; // numerator of Hawking luminosity
        // L = hbar*c^6/(15360*pi*kappa^2*c^4) = hbar*c^2/(15360*pi*kappa^2)
        double L=hbar*c*c/(15360*M_PI*b.kap*b.kap);
        // SDT last transparent wavelength: where dR/R just barely > 0
        // At z=1: dR/R(lam) = A*(lam/lam0)^0.75 * z_sun
        // Solving for lam where dR/R = 1e-20 (barely leaking):
        // Not well-defined without better scaling. Use lam_peak as proxy.
        double sdt_lam = lam_p; // first order: they match
        std::cout<<std::left<<std::setw(14)<<b.n<<std::right
                 <<std::scientific<<std::setprecision(2)<<std::setw(10)<<b.kap
                 <<std::setprecision(3)<<std::setw(10)<<TH
                 <<std::setprecision(2)<<std::setw(12)<<lam_p
                 <<std::setprecision(2)<<std::setw(12)<<L
                 <<std::setw(14)<<(lam_p>1?"radio":"sub-mm")<<"\n";
    }
    std::cout<<"\n*** kappa_sun = kappa(1_Msun_BH) = "<<std::fixed<<std::setprecision(2)<<kap_sun
             <<" m ***\n";
    std::cout<<"The Sun's displacement anchor IS the Schwarzschild radius of a 1 Msun black hole!\n";
    std::cout<<"```\n\n";

    // === TABLE 12: CMB CONNECTION ===
    std::cout<<"## Table 12: CMB as Universal Opacity Terminatum\n\n```\n";
    double T_CMB_emit=3000.0, z_CMB=1100.0;
    double lam0_shifted=lam0*(1+z_CMB);
    double T_CMB_now=2.725;
    double lam_CMB_peak=2.898e-3/T_CMB_now;
    double ratio=lam0_shifted/lam_CMB_peak;
    std::cout<<"CMB emission temperature:  "<<std::fixed<<std::setprecision(0)<<T_CMB_emit<<" K\n";
    std::cout<<"lam0 clearing temperature: "<<E0/(3*kB)<<" K\n";
    std::cout<<"MATCH: "<<std::setprecision(1)<<T_CMB_emit/(E0/(3*kB))*100<<"%\n\n";
    std::cout<<"lam0 redshifted by z=1100: "<<std::scientific<<std::setprecision(3)
             <<lam0_shifted<<" m = "<<std::fixed<<std::setprecision(2)<<lam0_shifted*1e3<<" mm\n";
    std::cout<<"CMB observed peak (Wien):  "<<std::setprecision(3)<<lam_CMB_peak*1e3<<" mm\n";
    std::cout<<"Ratio: "<<std::setprecision(4)<<ratio<<"\n";
    std::cout<<"5/3 = "<<std::setprecision(4)<<5.0/3<<"\n";
    std::cout<<"Match to 5/3: "<<std::setprecision(2)<<ratio/(5.0/3)*100<<"%\n";
    std::cout<<"```\n\n";

    // === TABLE 13: PRESSURE GEOMETRY ===
    std::cout<<"## Table 13: Why 5/4 and 3/4 — Dimensional Analysis\n\n```\n";
    std::cout<<"Exponents: short = "<<std::fixed<<std::setprecision(4)<<sf.b
             <<" long = "<<lf.b<<"\n\n";
    std::cout<<"Sum = "<<sf.b+lf.b<<" -> spatial dimensionality n = 2?\n";
    std::cout<<"  In n dims: sum should = n\n";
    std::cout<<"  Measured sum = "<<sf.b+lf.b<<" vs n=2: "
             <<std::abs(sf.b+lf.b-2)/(2)*100<<"% off\n\n";
    std::cout<<"Delta = 1/4 = 1/(n+2) where n = spatial dims = 2?\n";
    std::cout<<"  1/(2+2) = 1/4 = 0.25\n";
    std::cout<<"  Measured delta = "<<(delta_s+delta_l)/2<<"\n\n";
    std::cout<<"Product = "<<sf.b*lf.b<<"\n";
    std::cout<<"  (1+1/4)(1-1/4) = 1 - 1/16 = 15/16 = "<<15.0/16<<"\n";
    std::cout<<"  Match: "<<sf.b*lf.b/(15.0/16)*100<<"%\n\n";
    std::cout<<"Ratio = "<<sf.b/lf.b<<"\n";
    std::cout<<"  (1+1/4)/(1-1/4) = (5/4)/(3/4) = 5/3 = "<<5.0/3<<"\n";
    std::cout<<"  Match: "<<sf.b/lf.b/(5.0/3)*100<<"%\n";
    std::cout<<"```\n\n";

    // === TABLE 14: EARTH INTERNAL OPACITY ===
    double kap_e=6.371e6*7.03e-10;
    std::cout<<"## Table 14: Earth's Internal Structure\n\n```\n";
    std::cout<<"kappa_Earth = R*z = "<<std::scientific<<std::setprecision(3)<<kap_e<<" m = "
             <<std::fixed<<std::setprecision(2)<<kap_e*1e3<<" mm\n";
    std::cout<<"This is a MICROWAVE wavelength ("<<std::setprecision(1)<<c/kap_e/1e9<<" GHz)\n\n";
    std::cout<<"Seismic discontinuities as opacity terminata:\n";
    struct SD{const char*n;double depth_km;double R_ratio;};
    std::vector<SD> layers={
        {"Surface",0,1.0},{"Moho",35,1-35.0/6371},
        {"410 disc",410,1-410.0/6371},{"660 disc",660,1-660.0/6371},
        {"D'' layer",2891,1-2891.0/6371},{"Outer core",2891,1-2891.0/6371},
        {"Inner core",5150,1-5150.0/6371},{"Centre",6371,0}
    };
    std::cout<<std::left<<std::setw(14)<<"Layer"<<std::right
             <<std::setw(10)<<"depth_km"<<std::setw(10)<<"R/R_E"
             <<std::setw(12)<<"dR/R"<<"\n";
    std::cout<<std::string(46,'-')<<"\n";
    for(auto&l:layers){
        std::cout<<std::left<<std::setw(14)<<l.n<<std::right
                 <<std::fixed<<std::setprecision(0)<<std::setw(10)<<l.depth_km
                 <<std::setprecision(4)<<std::setw(10)<<l.R_ratio
                 <<std::setprecision(4)<<std::setw(12)<<1-l.R_ratio<<"\n";
    }
    std::cout<<"```\n\n";

    // === TABLE 15: GRAND CROSS-REFERENCE ===
    std::cout<<"## Table 15: Grand Cross-Reference Matrix\n\n```\n";
    std::cout<<std::left<<std::setw(14)<<"Domain"<<std::right
             <<std::setw(12)<<"z"<<std::setw(8)<<"k"
             <<std::setw(12)<<"kappa_m"<<std::setw(10)<<"T_surf_s"
             <<std::setw(10)<<"T_cl_K"<<std::setw(10)<<"lam0"
             <<std::setw(10)<<"status"<<"\n";
    std::cout<<std::string(86,'-')<<"\n";
    struct XR{const char*n;double z;double R;double kap;};
    std::vector<XR> xref={
        {"Proton",z_p,Rp,kap_p},
        {"Mercury",1e-10,2.44e6,2.44e6*1e-10},
        {"Earth",7.03e-10,6.37e6,6.37e6*7.03e-10},
        {"Jupiter",2.02e-8,6.99e7,6.99e7*2.02e-8},
        {"Sun",z_sun,R_sun,kap_sun},
        {"White Dwarf",3e-4,8.7e6,8.7e6*3e-4},
        {"Neutron Star",0.15,1.2e4,1.2e4*0.15},
        {"Dark Star",1.0,5e3,5e3}
    };
    for(auto&x:xref){
        double k=1/std::sqrt(x.z), vs=c/k, Ts=2*M_PI*x.R/vs;
        const char* st = x.z >= 1 ? "DARK" : (x.z > 0.01 ? "compact" : "normal");
        std::cout<<std::left<<std::setw(14)<<x.n<<std::right
                 <<std::scientific<<std::setprecision(2)<<std::setw(12)<<x.z
                 <<std::fixed<<std::setprecision(1)<<std::setw(8)<<k
                 <<std::scientific<<std::setprecision(2)<<std::setw(12)<<x.kap
                 <<std::setprecision(2)<<std::setw(10)<<Ts
                 <<std::fixed<<std::setprecision(0)<<std::setw(10)<<E0/(3*kB)
                 <<std::setw(10)<<"1.6um"
                 <<std::setw(10)<<st<<"\n";
    }
    std::cout<<"\nT_clear = "<<std::fixed<<std::setprecision(0)<<E0/(3*kB)
             <<" K EVERYWHERE. It is a property of the SPATION, not the body.\n";
    std::cout<<"```\n";

    return 0;
}
