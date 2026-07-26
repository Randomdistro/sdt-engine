// APS04 - Trefoil wake multipole solver, REBUILT 2026-07-26 per the rewritten spec.
// The 2026-07-23 crash class (near-field domination, normalisation error, fit-window
// abuse -> Phi0 exponent -2.99, Phi2 overflow, "Lamb" -2e16 MHz) is addressed by:
//   P0 instrument validation on THREE analytic targets before the trefoil is touched;
//   committed far-field window r/R_p in [10,1e5] with a0 INSIDE it;
//   Kahan-compensated line integrals; SI units ledger printed at stage boundaries;
//   sub-window drift + grid-convergence + aspect-sensitivity checks.
// Gates and coupling form committed in PROMPT.md / RUN_LOG.md / APS04_WAKE_GEOMETRY.md
// BEFORE this file was written. Author: J. C. Harvey, Melbourne. Direct run.
#include <cstdio>
#include <cmath>
#include <vector>
#include <array>
#include <numbers>

static const double PI = std::numbers::pi;
// --- CODATA / measured (SI) ---
static const double c0    = 299792458.0;
static const double hbar  = 1.054571817e-34;
static const double hP    = 6.62607015e-34;
static const double m_e   = 9.1093837015e-31;
static const double m_p   = 1.67262192369e-27;
static const double alpha = 7.2973525693e-3;
static const double eV    = 1.602176634e-19;
static const double a0_m  = 5.29177210903e-11;
static const double Rp_m  = 4.0*hbar/(m_p*c0);          // W+1 rule boundary radius

struct V3 { double x,y,z; };
static V3 sub(V3 a, V3 b){ return {a.x-b.x, a.y-b.y, a.z-b.z}; }
static double nrm(V3 a){ return std::sqrt(a.x*a.x+a.y*a.y+a.z*a.z); }

// ---------------- knot geometry (aspect rho committed = 1/4) ----------------
struct Curve { std::vector<V3> p, dl; };                 // midpoint segments
static Curve make_trefoil(double rho, int N){
    // R + r = 1 (R_p units), r/R = rho
    double R = 1.0/(1.0+rho), r = rho*R;
    Curve c; c.p.resize(N); c.dl.resize(N);
    for (int i=0;i<N;++i){
        double t = 2.0*PI*(i+0.5)/N, dt = 2.0*PI/N;
        double w = R + r*std::cos(3*t);
        c.p[i]  = { w*std::cos(2*t), w*std::sin(2*t), r*std::sin(3*t) };
        // derivative
        double dw = -3*r*std::sin(3*t);
        c.dl[i] = { (dw*std::cos(2*t) - 2*w*std::sin(2*t))*dt,
                    (dw*std::sin(2*t) + 2*w*std::cos(2*t))*dt,
                    (3*r*std::cos(3*t))*dt };
    }
    return c;
}
static Curve make_loop(double a, int N){                 // plain circle, radius a
    Curve c; c.p.resize(N); c.dl.resize(N);
    for (int i=0;i<N;++i){
        double t = 2.0*PI*(i+0.5)/N, dt = 2.0*PI/N;
        c.p[i]  = { a*std::cos(t), a*std::sin(t), 0.0 };
        c.dl[i] = { -a*std::sin(t)*dt, a*std::cos(t)*dt, 0.0 };
    }
    return c;
}
// Kahan-compensated scalar line integral  Phi(x) = sum |dl| / dist
static double phi_line(const Curve& c, V3 x){
    double s=0, comp=0;
    for (size_t i=0;i<c.p.size();++i){
        double d = nrm(sub(x, c.p[i]));
        double term = nrm(c.dl[i])/d;
        double y = term - comp, t = s + y; comp = (t - s) - y; s = t;
    }
    return s;
}
// Biot-Savart magnitude (Gamma=1):  v = (1/4pi) sum dl x (x-p)/d^3
static double bs_mag(const Curve& c, V3 x){
    double vx=0, vy=0, vz=0;
    for (size_t i=0;i<c.p.size();++i){
        V3 rr = sub(x, c.p[i]); double d = nrm(rr); double d3 = d*d*d;
        vx += (c.dl[i].y*rr.z - c.dl[i].z*rr.y)/d3;
        vy += (c.dl[i].z*rr.x - c.dl[i].x*rr.z)/d3;
        vz += (c.dl[i].x*rr.y - c.dl[i].y*rr.x)/d3;
    }
    return std::sqrt(vx*vx+vy*vy+vz*vz)/(4.0*PI);
}

// ---------------- shared extraction pipeline (the instrument) ----------------
// ADJ-2 (finer numerics, allowed class; window/gates untouched): the first run's
// midpoint theta-grid left an O(h^2) P2-projection floor ~1e-4 relative — the
// monopole leaked into c2 and alpha2 fitted the FLOOR (0.93, sub-window sliding
// to 1.0, c2 moving 3x with resolution = its own convergence check firing).
// Replaced with Gauss–Legendre quadrature in cos(theta): spectrally exact
// projections for smooth fields. First-run output preserved as
// aps04_results_2026-07-26_run1.txt.
static void gauss_legendre(int n, std::vector<double>& x, std::vector<double>& w){
    x.resize(n); w.resize(n);
    for (int i=0;i<n;++i){
        double xi = std::cos(PI*(i+0.75)/(n+0.5));            // initial guess
        for (int it=0; it<100; ++it){
            double p0=1, p1=0;                                // P_n and derivative by recurrence
            for (int k=0;k<n;++k){ double p2=p1; p1=p0; p0=((2*k+1)*xi*p1 - k*p2)/(k+1); }
            double dp = n*(xi*p0 - p1)/(xi*xi - 1.0);
            double dx_ = -p0/dp; xi += dx_;
            if (std::fabs(dx_) < 1e-15) break;
        }
        double p0=1, p1=0;
        for (int k=0;k<n;++k){ double p2=p1; p1=p0; p0=((2*k+1)*xi*p1 - k*p2)/(k+1); }
        double dp = n*(xi*p0 - p1)/(xi*xi - 1.0);
        x[i] = xi; w[i] = 2.0/((1.0-xi*xi)*dp*dp);
    }
}
struct ShellDecomp { double mono, dip_rel, c2, a3; };
template<typename F>
static ShellDecomp decompose(F&& f, double r, int Nth=48, int Nph=72){
    std::vector<double> gx, gw; gauss_legendre(Nth, gx, gw);
    double s0=0, sz=0, s2=0, a3acc=0;
    for (int j=0;j<Nth;++j){
        double ct = gx[j], st = std::sqrt(1.0-ct*ct), w = gw[j];
        double A3=0, B3=0, srow=0;
        for (int k=0;k<Nph;++k){
            double ph = 2.0*PI*k/Nph;
            V3 x = { r*st*std::cos(ph), r*st*std::sin(ph), r*ct };
            double v = f(x);
            srow += v;
            A3 += v*std::cos(3*ph); B3 += v*std::sin(3*ph);
        }
        double vbar = srow/Nph;
        s0 += w*vbar;
        sz += w*vbar*ct;
        s2 += w*vbar*0.5*(3.0*ct*ct-1.0);
        a3acc += w*2.0*std::sqrt(A3*A3+B3*B3)/Nph;
    }
    ShellDecomp d;
    d.mono = 0.5*s0;                                   // int dx/2 over [-1,1]
    d.dip_rel = std::fabs(1.5*sz)/std::max(1e-300, d.mono);
    // ADJ-4 (normalisation bug caught by the P3 two-stream): Legendre coefficient
    // A = int(f P2)/int(P2^2) = s2/(2/5) = 2.5*s2 — the first GL run used 1.25*s2
    // (half), which the direct-vs-fitted factor-2.03 exposed. Exponent gates
    // unaffected (prefactor only).
    d.c2  = 2.5*s2;
    d.a3  = 0.5*a3acc;
    return d;
}
// log-log LSQ fit y = A r^-alpha over shells [i0,i1)
static void fitpow(const std::vector<double>& r, const std::vector<double>& y,
                   int i0, int i1, double& alpha_out, double& lnA){
    double n=0, sx=0, sy=0, sxx=0, sxy=0;
    for (int i=i0;i<i1;++i){
        if (y[i]<=0) continue;
        double X = std::log(r[i]), Y = std::log(y[i]);
        n++; sx+=X; sy+=Y; sxx+=X*X; sxy+=X*Y;
    }
    double slope = (n*sxy - sx*sy)/(n*sxx - sx*sx);
    alpha_out = -slope; lnA = (sy - slope*sx)/n;
}

int main(){
    printf("================================================================\n");
    printf(" APS04 wake-field solver - REBUILT (spec 2026-07-26, gates committed)\n");
    printf("================================================================\n");
    printf("[UNITS LEDGER 0] R_p = 4*hbar/(m_p c) = %.6e m ; a0 = %.6e m\n", Rp_m, a0_m);
    double a0R = a0_m/Rp_m;
    printf("               a0/R_p = %.4e  (committed window [1e1,1e5]: INSIDE)\n", a0R);

    // ================= P0 - INSTRUMENT VALIDATION =================
    printf("\n--- P0a: point source (analytic r^-1) through the full pipeline ---\n");
    {
        std::vector<double> rs, mono;
        for (int i=0;i<=24;++i){ double r = std::pow(10.0, 1.0 + 3.0*i/24.0); rs.push_back(r);
            auto d = decompose([](V3 x){ return 1.0/nrm(x); }, r);
            mono.push_back(d.mono); }
        double al, lnA; fitpow(rs, mono, 0, (int)rs.size(), al, lnA);
        printf("  alpha0 = %.5f  (gate 1.00 +/- 0.02) -> %s\n", al, (std::fabs(al-1)<0.02)?"G0b PASS":"G0b FAIL");
    }
    printf("--- P0b/c: circular loop, Biot-Savart (analytic dipole r^-3) ---\n");
    {
        double a = 1.0; Curve L = make_loop(a, 720);
        std::vector<double> rs, mag;
        for (int i=0;i<=24;++i){ double z = std::pow(10.0, 1.0 + 2.0*i/24.0); rs.push_back(z);
            mag.push_back(bs_mag(L, {0,0,z})); }
        double al, lnA; fitpow(rs, mag, 0, (int)rs.size(), al, lnA);
        // analytic on-axis far field: v = a^2/(2 z^3) * (1/1)  [Gamma=1, our 1/4pi conv: a^2/(2z^3)]
        double coef = std::exp(lnA), coef_an = a*a/2.0;
        printf("  loop exponent = %.5f (gate 3.00 +/- 0.05) ; coeff = %.6f vs analytic %.6f (%.2f%%)\n",
               al, coef, coef_an, 100.0*std::fabs(coef/coef_an-1.0));
        bool g0a = std::fabs(al-3.0)<0.05 && std::fabs(coef/coef_an-1.0)<0.02;
        printf("  -> %s\n", g0a?"G0a PASS":"G0a FAIL");
        auto d = decompose([&](V3 x){ return bs_mag(L,x); }, 30.0);
        double m3rel = d.a3/std::max(1e-300,d.mono);
        printf("  loop m=3 content at r=30a: %.2e relative (gate <1e-3) -> %s\n",
               m3rel, (m3rel<1e-3)?"G0c PASS":"G0c FAIL");
    }
    printf("--- P0d: three point sources at 120deg (two-stream on the m=3 machinery) ---\n");
    {
        double dpl = 1.0;
        std::array<V3,3> pts = { V3{dpl,0,0},
                                 V3{dpl*std::cos(2*PI/3), dpl*std::sin(2*PI/3), 0},
                                 V3{dpl*std::cos(4*PI/3), dpl*std::sin(4*PI/3), 0} };
        auto exact = [&](V3 x){ double s=0; for (auto&p:pts) s += 1.0/nrm(sub(x,p)); return s; };
        // analytic multipole sum to l=3 (moments of three points, m=0 and m=3 terms)
        // M0=3 ; Q20 = sum(3z^2-r^2)/2 = -3d^2/2 ; M33: sum (x+iy)^3 = 3 d^3
        auto approx = [&](V3 x){
            double r = nrm(x), ct = x.z/r, ph = std::atan2(x.y,x.x), st = std::sqrt(1-ct*ct);
            double P2 = 0.5*(3*ct*ct-1);
            double mono = 3.0/r;
            double quad = (-1.5*dpl*dpl)*P2/(r*r*r);
            // l=3,m=3 term of 1/|x-x'|: (15/  ... ) use real solid-harmonic form:
            // sum_l (r'^l/r^{l+1}) P_l(cos gamma); the m=3 part for equatorial points:
            // (1/4) * (r'^3/r^4) * ... — validated numerically by the two-stream itself:
            double oct = (dpl*dpl*dpl)*(std::pow(st,3)*std::cos(3*ph))*(3.0*(5.0/8.0))/(r*r*r*r);
            return mono + quad + oct;
        };
        auto de = decompose(exact,  30.0);
        auto da = decompose(approx, 30.0);
        double dev = std::fabs(de.a3-da.a3)/std::max(1e-300, de.a3);
        printf("  m=3 amplitude at r=30d: exact-pipeline %.4e vs multipole-pipeline %.4e (dev %.2f%%)\n",
               de.a3, da.a3, 100*dev);
        printf("  -> %s (gate <1%% on the m=3 machinery two-stream)\n", (dev<0.01)?"G0d PASS":"G0d FAIL");
    }

    // ================= P2 - TREFOIL EXTRACTION =================
    printf("\n--- P2: trefoil (rho=1/4 committed), window r/R_p in [1e1,1e5] ---\n");
    Curve K = make_trefoil(0.25, 720);
    const int NS = 49;
    std::vector<double> rs(NS), mono(NS), diprel(NS), q2(NS), a3(NS);
    for (int i=0;i<NS;++i){
        double r = std::pow(10.0, 1.0 + 4.0*i/(NS-1)); rs[i]=r;
        auto d = decompose([&](V3 x){ return phi_line(K,x); }, r);
        mono[i]=d.mono; diprel[i]=d.dip_rel; q2[i]=std::fabs(d.c2); a3[i]=d.a3;
    }
    double al0, al2, al3, lnA0, lnA2, lnA3;
    fitpow(rs, mono, 0, NS, al0, lnA0);
    fitpow(rs, q2,   0, NS, al2, lnA2);
    // m=3 falls fast: fit only where amplitude is above double-precision noise floor
    int i3max = NS; for (int i=0;i<NS;++i) if (a3[i] < 1e-13*mono[i]) { i3max = i; break; }
    fitpow(rs, a3, 0, i3max, al3, lnA3);
    double dipmax=0; for (double v: diprel) dipmax = std::max(dipmax, v);
    printf("  alpha0 = %.4f (gate 1.0+/-0.2) | alpha2 = %.4f (gate 3.0+/-0.5) | alpha3 = %.4f (gate 4.0+/-0.5, %d shells)\n",
           al0, al2, al3, i3max);
    printf("  dipole content max = %.2e relative (gate <1e-3, analytic ZERO)\n", dipmax);
    // G2e sub-window drift
    double al0a, al0b, al2a, al2b, dumm;
    fitpow(rs, mono, 0, NS/2, al0a, dumm); fitpow(rs, mono, NS/2, NS, al0b, dumm);
    fitpow(rs, q2,   0, NS/2, al2a, dumm); fitpow(rs, q2,   NS/2, NS, al2b, dumm);
    printf("  G2e sub-windows: alpha0 %.4f|%.4f  alpha2 %.4f|%.4f (drift flags if bands split)\n",
           al0a, al0b, al2a, al2b);
    // grid convergence: halve knot step, double angles at one mid shell
    {
        Curve K2 = make_trefoil(0.25, 1440);
        double rmid = 1.0e3;
        auto dA = decompose([&](V3 x){ return phi_line(K, x); }, rmid, 36, 72);
        auto dB = decompose([&](V3 x){ return phi_line(K2,x); }, rmid, 72, 144);
        printf("  grid convergence @r=1e3: mono %.3e vs %.3e (%.2e rel) ; c2 %.3e vs %.3e (%.2e rel)\n",
               dA.mono, dB.mono, std::fabs(dA.mono/dB.mono-1),
               dA.c2, dB.c2, std::fabs(dA.c2/dB.c2-1));
    }
    // G2f aspect sensitivity (exponents must not move)
    for (double rho : {0.125, 0.5}){
        Curve Ka = make_trefoil(rho, 720);
        std::vector<double> m2(NS), m3v(NS);
        for (int i=0;i<NS;++i){
            auto d = decompose([&](V3 x){ return phi_line(Ka,x); }, rs[i]);
            m2[i]=std::fabs(d.c2); m3v[i]=d.a3;
        }
        double b2, b3, dl_;
        fitpow(rs, m2, 0, NS, b2, dl_);
        int j3 = NS; for (int i=0;i<NS;++i) if (m3v[i] < 1e-13) { j3 = i; break; }
        fitpow(rs, m3v, 0, j3, b3, dl_);
        printf("  G2f rho=%.3f : alpha2 = %.4f, alpha3 = %.4f (exponents must stay in-band)\n", rho, b2, b3);
    }
    // circulation channel, report-only (ADJ-0)
    {
        std::vector<double> mg(25), rr(25);
        for (int i=0;i<25;++i){ rr[i]=std::pow(10.0, 1.0+2.0*i/24.0);
            mg[i]=bs_mag(K, {0,0,rr[i]}); }
        double av, dl_; fitpow(rr, mg, 0, 25, av, dl_);
        printf("  [report-only ADJ-0] circulation-channel on-axis exponent = %.4f (dipole 3 expected)\n", av);
    }

    // ================= P3 - ENERGY SPLIT AT a0 =================
    printf("\n--- P3: split at a0 (bands committed; coupling committed in P1) ---\n");
    // ADJ-3 (finer numerics): band averages computed at TWO resolutions to
    // separate instrument from convention; both printed.
    for (int res=1; res<=2; ++res)
    {
        double r = a0R;                        // exact a0 shell, inside window
        int Nth=72*res, Nph=144*res;
        printf("  [P3 resolution %dx: %d x %d]\n", res, Nth, Nph);
        double seq=0, neq=0, spol=0, npol=0, sall=0, nall=0;
        for (int j=0;j<Nth;++j){
            double th = PI*(j+0.5)/Nth, w = std::sin(th), thd = th*180.0/PI;
            for (int k=0;k<Nph;++k){
                double ph = 2.0*PI*k/Nph;
                V3 x = { r*std::sin(th)*std::cos(ph), r*std::sin(th)*std::sin(ph), r*std::cos(th) };
                double v = phi_line(K, x);
                sall += w*v; nall += w;
                if (thd>=80 && thd<=100){ seq += w*v; neq += w; }
                if (thd<=20 || thd>=160){ spol+= w*v; npol+= w; }
            }
        }
        double phibar = sall/nall;
        double d_eq  = (seq/neq)/phibar - 1.0;
        double d_pol = (spol/npol)/phibar - 1.0;
        double ddiff = d_eq - d_pol;
        printf("[UNITS LEDGER 3] phibar(a0) [R_p^-1 units, sigma=1] = %.9e\n", phibar);
        printf("  <delta>_eq = %+.6e   <delta>_pol = %+.6e   diff = %+.6e\n", d_eq, d_pol, ddiff);
        bool valid = std::fabs(d_eq)<0.1 && std::fabs(d_pol)<0.1;
        printf("  G3-valid (|delta|<0.1): %s\n", valid?"PASS":"FAIL - STOP");
        if (valid){
            double E0 = m_e*(alpha*c0)*(alpha*c0);          // J
            double dE = E0*ddiff;                            // J
            double nu_MHz = dE/hP/1e6;
            printf("[UNITS LEDGER 3b] m_e(alpha c)^2 = %.6f eV ; dE = %+.6e eV ; nu = %+.6e MHz\n",
                   E0/eV, dE/eV, nu_MHz);
            printf("  G3-sign  (E(s=eq) > E(p=pol) <=> diff>0): %s\n", (ddiff>0)?"PASS":"FAIL");
            double anu = std::fabs(nu_MHz);
            printf("  G3-order (|nu| in [1e-3,1e5] MHz): %s\n", (anu>=1e-3&&anu<=1e5)?"PASS":"FAIL");
            printf("  G3-fork report (analyst does NOT choose):\n");
            printf("    Fork-B (whole shift 1057.845 MHz): ratio = %.3e\n", anu/1057.845);
            printf("    Fork-C (nuclear line 0.145 MHz)  : ratio = %.3e\n", anu/0.145);
            // cross-check via fitted power laws (two-stream inside window).
            // c2 is NEGATIVE (oblate knot, derived P1); fits ran on |c2| -> restore sign.
            // Band-averaged P2 factors for the committed bands (computed, not idealised):
            // <P2>_eq([80,100]) = -0.4938 ; <P2>_pol([0,20]u[160,180]) = +0.9024
            double q2_a0  = -std::exp(lnA2)*std::pow(r, -al2);   // signed
            double mono_a0=  std::exp(lnA0)*std::pow(r, -al0);
            double ddiff_fit = (q2_a0/mono_a0)*(-0.4938 - 0.9024);
            printf("  two-stream: delta-diff direct %.4e vs fitted-P2-route %.4e (rel dev %.2f%%)\n",
                   ddiff, ddiff_fit, 100.0*std::fabs(ddiff_fit/ddiff-1.0));
        }
    }

    // ================= P5 - SCALING (fork selection by data) =================
    printf("\n--- P5: scaling discriminator (powers from the committed coupling) ---\n");
    {
        double mmu_me = 206.768, a0_amu = 185.84;   // reduced-mass ratio (RUN_LOG anchors)
        double pred = mmu_me * a0_amu * a0_amu;     // Delta-E ratio, quad term: m * (1/a^2)
        double meas_forkC = (3.7e-3*eV) / (0.145e6*hP);   // muonic size term / electronic size line
        double meas_forkB = (202e-3*eV) / (1057.845e6*hP);
        printf("  predicted muonic/electronic (quad term, m/a^2) = %.3e\n", pred);
        printf("  measured Fork-C ratio (3.7 meV / 0.145 MHz)    = %.3e  -> pred/meas = %.2f\n",
               meas_forkC, pred/meas_forkC);
        printf("  measured Fork-B ratio (202 meV / 1057.845 MHz) = %.3e  -> pred/meas = %.1f\n",
               meas_forkB, pred/meas_forkB);
        bool g5 = (pred/meas_forkC < 3.0) && (pred/meas_forkC > 1.0/3.0);
        printf("  G5 (Fork-C tracks within factor 3): %s ; Fork-B: %s\n",
               g5? "PASS":"FAIL",
               (pred/meas_forkB>3.0||pred/meas_forkB<1.0/3.0)? "DIES on scaling (as derived)":"survives");
    }
    printf("\n================================================================\n");
    printf(" grading in APS04_VERDICT_DIRECT (no gate moved after numbers)\n");
    printf("================================================================\n");
    return 0;
}
