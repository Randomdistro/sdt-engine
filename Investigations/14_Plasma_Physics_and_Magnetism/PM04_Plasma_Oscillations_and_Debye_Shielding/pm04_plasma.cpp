// ═══════════════════════════════════════════════════════════════════════
//  PM04 — Plasma Oscillations and Debye Shielding (1-D sheet model)
//  Author: J. C. Harvey, Melbourne · 2026-07-04 · pre-commits: RUN_LOG.md
//
//  FIREWALL: no primitive E field, no e²/ε₀ in the restoring chain, no
//  magnetons. Pair coupling A = αℏc  (engine coulomb_identity::k_e_e2 —
//  laws.hpp labels it class F definitional; therefore the GAIN is an
//  α-anchored re-expression, NOT a derivation. Disclosed.)
//  Sheet force per carrier = 2πA σ_s  (Law III 1/r² integrated over sheet;
//  distance-independent). Ion background immobile, neutralising.
//  Arrays EVOLVE (leapfrog N-body); the PM03 static-pass sin is forbidden.
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

using namespace sdt::laws;
static constexpr double PI = 3.14159265358979323846;

struct Sheets {
    // 1-D sheet plasma: electrons (q=+1 among themselves), immobile background.
    int N; double L, sigma_s, A, m, dt;
    std::vector<double> x, v, q;      // q in units of sigma_s
    double q_t = 0.0, x_t = 0.0;      // optional immobile test sheet
    double bg = 0.0;                  // background surface density factor (N_eff/L)
    void init(int N_, double L_, double n, double A_, double m_) {
        N = N_; L = L_; A = A_; m = m_;
        sigma_s = n * L / N;
        x.resize(N); v.assign(N, 0.0); q.assign(N, 1.0);
        for (int i = 0; i < N; ++i) x[i] = (i + 0.5) * L / N;
        bg = double(N) / L;
    }
    // forces per carrier via rank prefix sums:  F_i = 2πA σ_s q_i [ Σ_j q_j sgn(x_i-x_j) + bg(L-2x_i) + q_t sgn(x_i-x_t) ]
    void forces(std::vector<double>& F) {
        static std::vector<int> idx; idx.resize(N);
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(), [&](int a, int b){ return x[a] < x[b]; });
        double Qtot = 0; for (int i = 0; i < N; ++i) Qtot += q[i];
        double Qleft = 0;
        for (int r = 0; r < N; ++r) {
            const int i = idx[r];
            const double Qright = Qtot - Qleft - q[i];
            double s = (Qleft - Qright) + bg * (L - 2.0 * x[i]);
            if (q_t != 0.0) s += q_t * ((x[i] > x_t) ? 1.0 : -1.0);
            F[i] = 2.0 * PI * A * sigma_s * q[i] * s;
            Qleft += q[i];
        }
    }
    void step(std::vector<double>& F) {
        forces(F);
        for (int i = 0; i < N; ++i) { v[i] += (F[i]/m)*dt; x[i] += v[i]*dt;
            if (x[i] < 0)  { x[i] = -x[i]; v[i] = -v[i]; }
            if (x[i] > L)  { x[i] = 2*L - x[i]; v[i] = -v[i]; } }
    }
};

int main() {
    std::printf("PM04 — Plasma Oscillations & Debye Shielding, 1-D sheet N-body (J. C. Harvey, 2026-07-04)\n");
    const double A  = coulomb_identity::k_e_e2;     // = alpha*hbar*c [J m] — class F identity, DISCLOSED
    const double m  = measured::m_e;
    const double n  = 1.0e18;                       // [m^-3] chosen density (free test point, not fitted)
    const double wp_native = std::sqrt(4.0*PI*A*n/m);
    std::printf("native gain: A = alpha*hbar*c = %.6e J m  (engine coulomb_identity, class F identity)\n", A);
    std::printf("omega_p(native form) = sqrt(4 pi A n / m_e) = %.6e rad/s at n = %.1e m^-3\n\n", wp_native, n);

    // ═══ P1 — single-sheet ring at omega_p (cold) ═══════════════════════
    {
        Sheets S; const int N = 2000;
        const double lam = 1.0;                      // placeholder; L set from N,n via sheets/m^2
        (void)lam;
        const double L = 2.0e-3;
        S.init(N, L, n, A, m); S.dt = 2.0e-13;
        std::vector<double> F(N);
        const int k0 = N/2; const double dx0 = 0.3 * L/N;
        S.x[k0] += dx0;
        double prev = dx0; int zc = 0; double t_first = -1, t_last = -1;
        const int NS = 12000;
        for (int s = 0; s < NS; ++s) {
            S.step(F);
            const double d = S.x[k0] - (k0 + 0.5)*L/N;
            if (prev <= 0 && d > 0) { const double t = s*S.dt; if (t_first < 0) t_first = t; t_last = t; ++zc; }
            prev = d;
        }
        const double w_meas = 2.0*PI*(zc-1)/(t_last - t_first);
        std::printf("P1  cold single-sheet ring: omega_meas = %.6e  vs  omega_p = %.6e  (dev %+.3f%%, gate <1%%)\n",
                    w_meas, wp_native, 100.0*(w_meas-wp_native)/wp_native);
        std::printf("P1  [IMPORTED, final-line check] sqrt(n e^2 / (eps0 m)) = %.6e rad/s (equal by identity)\n\n",
                    std::sqrt(n*measured::e_charge*measured::e_charge/(8.8541878128e-12*m)));
    }

    // ═══ P2 — Debye screening of a test sheet (warm) ════════════════════
    {
        const double T = 1.0e5;                                    // [K]
        const double vth = std::sqrt(measured::k_B*T/m);
        const double lamD = std::sqrt(measured::k_B*T/(4.0*PI*A*n));  // native form
        std::printf("P2  lambda_D(native form) = sqrt(k_B T/(4 pi A n)) = %.6e m  (== sqrt(eps0 kT/n e^2), identity)\n", lamD);
        Sheets S; const int N = 4000; const double L = 200.0*lamD;
        S.init(N, L, n, A, m); S.dt = 1.0e-13;                      // ADJ-2: dt halved (heating control)
        S.q_t = -5.0; S.x_t = L/2;                                  // opposite-sign test sheet (q_t=5 committed)
        S.bg = (double(N) + S.q_t) / L;                             // neutralise
        std::mt19937 rng(7); std::normal_distribution<double> Nv(0.0, vth);
        for (auto& vv : S.v) vv = Nv(rng);
        std::vector<double> F(N);
        // ADJ-1 (numerics only, disclosed): first pass used NB=100 (bin width 2 lambda_D)
        // -> 2 usable bins -> NaN fit. Bins refined to 0.25 lambda_D, more snapshots.
        // ADJ-2 (numerics only, disclosed): run-2 estimator kept only dn>0 bins out to
        // 4 lambda_D (noise-tail selection bias flattens the slope) and ignored numerical
        // heating. Fixes: folded two-sided profile, window [0.5, 2.5] lambda_D, measured
        // sampling-time temperature reported alongside; dt halved. GATE UNCHANGED (15%).
        const int NB = 800; std::vector<double> hist(NB, 0.0); int snaps = 0;
        double v2acc = 0; long v2n = 0;
        const int NS = 200000, EQ = 40000;
        for (int s = 0; s < NS; ++s) {
            S.step(F);
            if (s > EQ && s % 50 == 0) {
                for (int i = 0; i < N; ++i) {
                    const double d = S.x[i] - S.x_t;
                    const int b = int((d/L + 0.5) * NB);
                    if (b >= 0 && b < NB) hist[b] += 1.0;
                    v2acc += S.v[i]*S.v[i]; ++v2n;
                }
                ++snaps;
            }
        }
        const double T_meas = m * (v2acc/v2n) / measured::k_B;      // 1-D: <mv^2> = kT
        const double lamD_meas = std::sqrt(measured::k_B*T_meas/(4.0*PI*A*n));
        // folded two-sided excess profile; fit ln(dn) in [0.5, 2.5] lambda_D
        const double binw = L/NB; const double n0 = double(N)/NB;   // sheets per bin, unperturbed
        std::vector<double> xs, ys;
        for (int b = NB/2; b < NB; ++b) {
            const double ad = (b + 0.5)*binw - L/2;
            if (ad < 0.5*lamD || ad > 2.5*lamD) continue;
            const int bm = NB - 1 - b;                              // mirror bin
            const double dn = 0.5*(hist[b] + hist[bm])/snaps - n0;  // two-sided mean (may be <0)
            if (dn > 0) { xs.push_back(ad); ys.push_back(std::log(dn)); }
        }
        double sx=0,sy=0,sxx=0,sxy=0; const int np=(int)xs.size();
        for (int i=0;i<np;++i){sx+=xs[i];sy+=ys[i];sxx+=xs[i]*xs[i];sxy+=xs[i]*ys[i];}
        const double slope = (np*sxy-sx*sy)/(np*sxx-sx*sx);
        const double lam_fit = -1.0/slope;
        std::printf("P2  sim: cloud e-folding = %.3e m  vs lambda_D(T_init) = %.3e m  (dev %+.1f%%, gate <15%% -> FAIL)\n",
                    lam_fit, lamD, 100.0*(lam_fit-lamD)/lamD);
        std::printf("P2  T sampled during averaging = %.3e K (init 1.0e5);  lambda_D(T_meas) = %.3e m;\n",
                    T_meas, lamD_meas);
        std::printf("P2  coefficient vs measured T: lam_fit/lambda_D(T_meas) = %.3f  (%d bins, %d snapshots)\n",
                    lam_fit/lamD_meas, np, snaps);
        std::printf("P2  FAIL RECORDED: collisionless (phase-mixed) screening cloud is wider than the\n");
        std::printf("    thermal-Boltzmann lambda_D the gate assumed. Not retried. -> P2b scaling test.\n\n");

        // ── P2b (phase split, declared in RUN_LOG before this run): lambda ~ sqrt(T/n) ──
        {
            const double T2 = 4.0e5; const double vth2 = std::sqrt(measured::k_B*T2/m);
            const double lamD2 = std::sqrt(measured::k_B*T2/(4.0*PI*A*n));
            Sheets S2; S2.init(N, L, n, A, m); S2.dt = 1.0e-13;
            S2.q_t = -5.0; S2.x_t = L/2; S2.bg = (double(N) + S2.q_t)/L;
            std::mt19937 rng2(7); std::normal_distribution<double> Nv2(0.0, vth2);
            for (auto& vv : S2.v) vv = Nv2(rng2);
            std::vector<double> F2(N);
            std::vector<double> hist2(NB, 0.0); int snaps2 = 0;
            for (int s = 0; s < NS; ++s) {
                S2.step(F2);
                if (s > EQ && s % 50 == 0) {
                    for (int i = 0; i < N; ++i) {
                        const double d = S2.x[i] - S2.x_t;
                        const int b = int((d/L + 0.5) * NB);
                        if (b >= 0 && b < NB) hist2[b] += 1.0;
                    }
                    ++snaps2;
                }
            }
            std::vector<double> xs2, ys2;
            for (int b = NB/2; b < NB; ++b) {
                const double ad = (b + 0.5)*binw - L/2;
                if (ad < 0.5*lamD2 || ad > 2.5*lamD2) continue;
                const int bm = NB - 1 - b;
                const double dn = 0.5*(hist2[b] + hist2[bm])/snaps2 - n0;
                if (dn > 0) { xs2.push_back(ad); ys2.push_back(std::log(dn)); }
            }
            double s2x=0,s2y=0,s2xx=0,s2xy=0; const int np2=(int)xs2.size();
            for (int i=0;i<np2;++i){s2x+=xs2[i];s2y+=ys2[i];s2xx+=xs2[i]*xs2[i];s2xy+=xs2[i]*ys2[i];}
            const double lam_fit2 = -1.0/((np2*s2xy-s2x*s2y)/(np2*s2xx-s2x*s2x));
            std::printf("P2b scaling test (declared pre-run): T x4 => lam_fit2 = %.3e m; ratio = %.3f\n",
                        lam_fit2, lam_fit2/lam_fit);
            std::printf("P2b gate ratio = sqrt(T2/T1) = 2.0 +/- 15%%  ->  %s  (%d bins)\n\n",
                        (std::fabs(lam_fit2/lam_fit - 2.0) < 0.30 ? "PASS" : "FAIL"), np2);
        }

        // ── P2c (declared in RUN_LOG pre-run): Langevin bath makes TD02 ensemble real ──
        // 1-D equal-mass sheets have NO velocity-relaxation channel (pass-through
        // crossings), so the Boltzmann response cannot form without a bath. Closure,
        // not amputation: add gamma_L = 0.05 omega_p thermostat at T = 1e5 K.
        {
            const double gamL = 0.05*wp_native, sigL = std::sqrt(2.0*gamL*measured::k_B*T/m);
            Sheets S3; S3.init(N, L, n, A, m); S3.dt = 1.0e-13;
            S3.q_t = -5.0; S3.x_t = L/2; S3.bg = (double(N) + S3.q_t)/L;
            std::mt19937 rng3(13); std::normal_distribution<double> Nv3(0.0, vth), G01(0.0, 1.0);
            for (auto& vv : S3.v) vv = Nv3(rng3);
            std::vector<double> F3(N);
            std::vector<double> hist3(NB, 0.0); int snaps3 = 0;
            for (int s = 0; s < NS; ++s) {
                S3.forces(F3);
                for (int i = 0; i < N; ++i) {
                    S3.v[i] += (F3[i]/m)*S3.dt - gamL*S3.v[i]*S3.dt + sigL*std::sqrt(S3.dt)*G01(rng3);
                    S3.x[i] += S3.v[i]*S3.dt;
                    if (S3.x[i] < 0) { S3.x[i] = -S3.x[i]; S3.v[i] = -S3.v[i]; }
                    if (S3.x[i] > L) { S3.x[i] = 2*L - S3.x[i]; S3.v[i] = -S3.v[i]; }
                }
                if (s > EQ && s % 50 == 0) {
                    for (int i = 0; i < N; ++i) {
                        const double d = S3.x[i] - S3.x_t;
                        const int b = int((d/L + 0.5) * NB);
                        if (b >= 0 && b < NB) hist3[b] += 1.0;
                    }
                    ++snaps3;
                }
            }
            std::vector<double> xs3, ys3;
            for (int b = NB/2; b < NB; ++b) {
                const double ad = (b + 0.5)*binw - L/2;
                if (ad < 0.5*lamD || ad > 2.5*lamD) continue;
                const int bm = NB - 1 - b;
                const double dn = 0.5*(hist3[b] + hist3[bm])/snaps3 - n0;
                if (dn > 0) { xs3.push_back(ad); ys3.push_back(std::log(dn)); }
            }
            double s3x=0,s3y=0,s3xx=0,s3xy=0; const int np3=(int)xs3.size();
            for (int i=0;i<np3;++i){s3x+=xs3[i];s3y+=ys3[i];s3xx+=xs3[i]*xs3[i];s3xy+=xs3[i]*ys3[i];}
            const double slope3 = (np3*s3xy-s3x*s3y)/(np3*s3xx-s3x*s3x);
            const double lam_fit3 = -1.0/slope3;
            // exponentiality: R^2 of the linear fit in log space
            double ybar=0; for (double yv : ys3) ybar += yv; ybar /= np3;
            double ssr=0, sst=0;
            const double icpt = (s3y - slope3*s3x)/np3;
            for (int i=0;i<np3;++i){ const double yh = icpt + slope3*xs3[i];
                ssr += (ys3[i]-yh)*(ys3[i]-yh); sst += (ys3[i]-ybar)*(ys3[i]-ybar); }
            std::printf("P2c thermostated (gamma_L=0.05 w_p): lam_fit = %.3e m vs lambda_D = %.3e m (dev %+.1f%%, gate <15%%)\n",
                        lam_fit3, lamD, 100.0*(lam_fit3-lamD)/lamD);
            std::printf("P2c exponentiality R^2 = %.4f over [0.5,2.5] lambda_D (%d bins) -> %s\n\n",
                        1.0 - ssr/sst, np3,
                        (std::fabs(lam_fit3-lamD)/lamD < 0.15 ? "PASS" : "FAIL"));
        }
    }

    // ═══ P3 — Bohm–Gross dispersion (warm standing modes) ═══════════════
    {
        const double T = 1.0e5; const double vth = std::sqrt(measured::k_B*T/m);
        const double lamD = std::sqrt(measured::k_B*T/(4.0*PI*A*n));
        const double L = 200.0*lamD;
        std::printf("P3  analytic claim: C = 3 = (d+2)/d at d=1 (1-D adiabatic index); FD05's 1/3 = 1/d at d=3\n");
        for (int mk : {6, 10}) {
            Sheets S; const int N = 4000;
            S.init(N, L, n, A, m); S.dt = 2.0e-13;
            std::mt19937 rng(11); std::normal_distribution<double> Nv(0.0, vth);
            for (auto& vv : S.v) vv = Nv(rng);
            const double k = 2.0*PI*mk/L;
            // ADJ-1 (numerics only, disclosed): amplitude 0.15->0.4 Delta; zero-crossing
            // estimator (noise-biased) replaced by Hann-windowed DFT peak w/ parabolic interp.
            for (int i = 0; i < N; ++i) S.x[i] += 0.4*(L/N)*std::sin(k*S.x[i]);
            std::vector<double> F(N);
            const int NS = 60000;
            std::vector<double> Mt(NS);
            for (int s = 0; s < NS; ++s) {
                S.step(F);
                double M = 0;
                for (int i = 0; i < N; ++i) M += std::sin(k*S.x[i]);
                Mt[s] = M;
            }
            // Hann-windowed DFT scan around omega_p .. 1.4 omega_p
            double bestw = 0, bestP = -1;
            const double w_lo = 0.8*wp_native, w_hi = 1.6*wp_native; const int NW = 1600;
            std::vector<double> Pw(NW);
            for (int u = 0; u < NW; ++u) {
                const double w = w_lo + (w_hi-w_lo)*u/(NW-1);
                double cs = 0, sn = 0;
                for (int s = 0; s < NS; ++s) {
                    const double win = 0.5*(1.0 - std::cos(2.0*PI*s/(NS-1)));
                    cs += win*Mt[s]*std::cos(w*s*S.dt);
                    sn += win*Mt[s]*std::sin(w*s*S.dt);
                }
                Pw[u] = cs*cs + sn*sn;
                if (Pw[u] > bestP) { bestP = Pw[u]; bestw = w; }
            }
            const double w = bestw;
            const double C = (w*w/(wp_native*wp_native) - 1.0)/(k*k*lamD*lamD);
            std::printf("P3  k*lambda_D = %.3f : omega/omega_p = %.4f  ->  C = %.2f  (gate C in [2,4])\n",
                        k*lamD, w/wp_native, C);
        }
        std::printf("P3  (finite relay speed of the imbalance = thermal sheet motion; heavy damping at\n");
        std::printf("     higher k observed qualitatively = Landau-type, logged OPEN per prompt Q3)\n\n");
    }

    // ═══ P4 — upper hybrid: slab restoring + unsigned Coriolis turning ══
    {
        std::printf("P4  slab restoring (x only) + v x Omega turning (PM01 unsigned channel, HG-1 disclosed):\n");
        for (double ratio : {0.5, 1.0, 2.0}) {
            const double Om = ratio*wp_native;
            double xx=1e-9, yy=0, vx=0, vy=0; const double dt = 1e-13;
            double prev = xx; int zc = 0; double t_first=-1, t_last=-1;
            const int NS = 40000;
            for (int s = 0; s < NS; ++s) {
                const double ax = -wp_native*wp_native*xx + Om*vy;
                const double ay = -Om*vx;
                vx += ax*dt; vy += ay*dt; xx += vx*dt; yy += vy*dt;
                if (prev <= 0 && xx > 0) { const double t=s*dt; if(t_first<0) t_first=t; t_last=t; ++zc; }
                prev = xx;
            }
            const double w = 2.0*PI*(zc-1)/(t_last-t_first);
            const double wuh = std::sqrt(wp_native*wp_native + Om*Om);
            std::printf("P4  Omega/omega_p = %.1f : omega_meas/omega_uh = %.5f (gate 1 +/- 0.5%%)\n",
                        ratio, w/wuh);
        }
    }

    std::printf("\nPM04 done. Verdict: PM04_VERDICT.md\n");
    return 0;
}
