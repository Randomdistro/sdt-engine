// ═══════════════════════════════════════════════════════════════════════
//  PM06 — Cyclotron and Synchrotron from Differential Occlusion
//  Author: J. C. Harvey, Melbourne · 2026-07-04 · pre-commits: RUN_LOG.md
//
//  FIREWALL: no primitive qv×B (the turning push is PM01's field-proportional
//  entrainment channel, UNSIGNED — HG-1 disclosed); no µ_B/µ_N; no external
//  Lorentz boost (all kinematics = Law V theorems T10–T17; DEGENERATE w/ SR,
//  disclosed). Rest-frame emission coefficient = E89/PM03 channel, BORROWED
//  (PM03 is flagged DO-NOT-TRUST; only the coefficient is borrowed, none of
//  the scalings). Native units c = 1 (numerics).
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <vector>
#include <random>
#include <algorithm>

static constexpr double PI = 3.14159265358979323846;

// relativistic orbit under unsigned turning push: d(gamma v)/dt = v x (Om zhat)
struct Orbit {
    std::vector<double> t, x, y, vx, vy;
    void run(double beta0, double Om, int periods, int steps_per_period) {
        const double g0 = 1.0/std::sqrt(1.0-beta0*beta0);
        const double w_expect = Om/g0;                       // measured later, not used in dynamics
        const double dt = 2.0*PI/w_expect/steps_per_period;  // step sizing only
        double X=0, Y=0, VX=beta0, VY=0;
        auto acc = [&](double vx_, double vy_, double& ax, double& ay) {
            // d(gamma v)/dt = v x Om zhat ; solve for dv/dt with gamma(v):
            // p = g v ; dp/dt = F ; dv/dt = (F - v (v.F) g^2) / g ... for F ⟂ v: dv/dt = F/g
            const double g = 1.0/std::sqrt(1.0 - vx_*vx_ - vy_*vy_);
            const double Fx =  vy_*Om, Fy = -vx_*Om;          // v x (Om zhat)
            ax = Fx/g; ay = Fy/g;                             // F ⟂ v exactly
        };
        const int NS = periods*steps_per_period;
        t.resize(NS+1); x.resize(NS+1); y.resize(NS+1); vx.resize(NS+1); vy.resize(NS+1);
        for (int s = 0; s <= NS; ++s) {
            t[s]=s*dt; x[s]=X; y[s]=Y; vx[s]=VX; vy[s]=VY;
            double a1x,a1y,a2x,a2y,a3x,a3y,a4x,a4y;
            acc(VX,VY,a1x,a1y);
            acc(VX+0.5*dt*a1x, VY+0.5*dt*a1y, a2x,a2y);
            acc(VX+0.5*dt*a2x, VY+0.5*dt*a2y, a3x,a3y);
            acc(VX+dt*a3x, VY+dt*a3y, a4x,a4y);
            const double k1x=VX, k1y=VY;
            const double k2x=VX+0.5*dt*a1x, k2y=VY+0.5*dt*a1y;
            const double k3x=VX+0.5*dt*a2x, k3y=VY+0.5*dt*a2y;
            const double k4x=VX+dt*a3x,     k4y=VY+dt*a3y;
            X  += dt*(k1x+2*k2x+2*k3x+k4x)/6.0;  Y += dt*(k1y+2*k2y+2*k3y+k4y)/6.0;
            VX += dt*(a1x+2*a2x+2*a3x+a4x)/6.0;  VY += dt*(a1y+2*a2y+2*a3y+a4y)/6.0;
        }
    }
};

static double fit_slope(const std::vector<double>& X, const std::vector<double>& Y) {
    double sx=0,sy=0,sxx=0,sxy=0; const int n=(int)X.size();
    for (int i=0;i<n;++i){sx+=X[i];sy+=Y[i];sxx+=X[i]*X[i];sxy+=X[i]*Y[i];}
    return (n*sxy-sx*sy)/(n*sxx-sx*sx);
}

int main() {
    std::printf("PM06 — Cyclotron & Synchrotron from Differential Occlusion (J. C. Harvey, 2026-07-04)\n");
    std::printf("Turning push = PM01 field-proportional channel (UNSIGNED, HG-1 disclosed). c=1 units.\n\n");

    // ═══ P1 — orbit closure and omega_c ═════════════════════════════════
    {
        const double Om = 1.0;
        // non-relativistic
        {
            Orbit O; const double b = 0.01; O.run(b, Om, 5, 20000);
            const double g = 1.0/std::sqrt(1.0-b*b);
            // measure period from vx zero crossings
            int zc=0; double t1=-1, t2=-1;
            for (size_t s=1;s<O.t.size();++s)
                if (O.vx[s-1]<=0 && O.vx[s]>0){ if(t1<0)t1=O.t[s]; t2=O.t[s]; ++zc; }
            const double w_meas = 2.0*PI*(zc-1)/(t2-t1);
            // closure drift: distance from start after one period / gyro radius
            const int spp = 20000;
            const double drift = std::hypot(O.x[spp]-O.x[0], O.y[spp]-O.y[0]);
            const double rg = g*b/Om;
            std::printf("P1  non-rel: omega_meas/Omega = %.6f (gate 1 +/- 0.1%%); closure drift/r_g = %.2e (gate <1e-3)\n",
                        w_meas/(Om/g), drift/rg);
        }
        // relativistic
        for (double g_target : {2.0, 10.0}) {
            const double b = std::sqrt(1.0-1.0/(g_target*g_target));
            Orbit O; O.run(b, Om, 5, 20000);
            int zc=0; double t1=-1, t2=-1;
            for (size_t s=1;s<O.t.size();++s)
                if (O.vx[s-1]<=0 && O.vx[s]>0){ if(t1<0)t1=O.t[s]; t2=O.t[s]; ++zc; }
            const double w_meas = 2.0*PI*(zc-1)/(t2-t1);
            // radius: max |r| over orbit /2 ... use (max x - min x)/2
            double xmax=-1e9, xmin=1e9;
            for (double xx : O.x) { xmax=std::max(xmax,xx); xmin=std::min(xmin,xx); }
            const double r_meas = 0.5*(xmax-xmin);
            std::printf("P1  gamma=%.0f: omega_rel/(Omega/gamma) = %.6f (gate 1 +/- 0.5%%); r/(gamma v/Omega) = %.6f (gate 1 +/- 0.5%%)\n",
                        g_target, w_meas/(Om/g_target), r_meas/(g_target*b/Om));
        }
        std::printf("P1  omega_c = |curl w| with UNIT gain (unsigned channel). SI map omega_c = qB/m needs\n");
        std::printf("    the HG-1 bilinear gain (PM01: sense-from-handedness 2/4, OPEN). Sense NOT claimed.\n\n");
    }

    // ═══ P2 — proper vs lab acceleration from the orbit arrays ══════════
    {
        const double Om = 1.0;
        std::vector<double> lg, lr;
        for (double g_target : {2.0, 10.0}) {
            const double b = std::sqrt(1.0-1.0/(g_target*g_target));
            Orbit O; O.run(b, Om, 2, 40000);
            // finite-difference lab acceleration and proper acceleration at mid-orbit
            const int s = (int)O.t.size()/2; const double dt = O.t[1]-O.t[0];
            const double ax = (O.vx[s+1]-O.vx[s-1])/(2*dt), ay = (O.vy[s+1]-O.vy[s-1])/(2*dt);
            auto gam = [&](int i){ return 1.0/std::sqrt(1.0-O.vx[i]*O.vx[i]-O.vy[i]*O.vy[i]); };
            // proper velocity u = gamma v ; proper time dtau = dt/gamma (Law V T11)
            const double dux = gam(s+1)*O.vx[s+1]-gam(s-1)*O.vx[s-1];
            const double duy = gam(s+1)*O.vy[s+1]-gam(s-1)*O.vy[s-1];
            const double dtau = 2*dt/gam(s);
            const double ap = std::hypot(dux,duy)/dtau, al = std::hypot(ax,ay);
            std::printf("P2  gamma=%.0f: a_proper/a_lab = %.4f  vs gamma^2 = %.4f  (dev %+.3f%%, gate <0.5%%)\n",
                        g_target, ap/al, g_target*g_target, 100.0*(ap/al/(g_target*g_target)-1.0));
            lg.push_back(std::log(g_target)); lr.push_back(std::log(ap/al));
        }
        std::printf("P2  ledger: P_rad = C_E89 * a_proper^2 (rest-frame coefficient BORROWED, flagged)\n");
        std::printf("    => P(gamma)/P_rest = (a'/a)^2|_freq-fold = gamma^4; measured exponent of a'/a = %.4f\n", fit_slope(lg,lr));
        std::printf("    (2.0000 = gamma^2 per amplitude, squared in power => 4.000; gate 4.000 +/- 0.02)\n\n");
    }

    // ═══ P3 — pulse train: omega_rms / omega_rot ~ gamma^3 ══════════════
    {
        const double Om = 1.0;
        std::vector<double> lg, lw;
        for (double g_target : {4.0, 8.0, 16.0, 32.0}) {
            const double b = std::sqrt(1.0-1.0/(g_target*g_target));
            const int spp = std::max(20000, (int)(4000*g_target));
            Orbit O; O.run(b, Om, 2, spp);
            const double w_rot = (Om/g_target);
            // observer at +x infinity in the orbit plane; Law-V aberration pattern of an
            // isotropic rest emitter: I(theta) = 1/(gamma^2 (1-beta cos th)^2) * 1/(1-beta cos th)
            const size_t NSs = O.t.size();
            std::vector<double> Pr(NSs), tob(NSs);
            for (size_t s = 0; s < NSs; ++s) {
                const double vn = std::hypot(O.vx[s],O.vy[s]);
                const double cth = O.vx[s]/vn;                 // cos(angle between v and +x)
                const double g = 1.0/std::sqrt(1.0-vn*vn);
                const double D = 1.0 - vn*cth;
                Pr[s] = 1.0/(g*g*D*D*D);
                tob[s] = O.t[s] - O.x[s];                       // c = 1
            }
            // RMS spectral width via ||dP/dt_obs|| / ||P|| on the nonuniform grid
            double num = 0, den = 0;
            for (size_t s = 1; s+1 < NSs; ++s) {
                const double dto = tob[s+1]-tob[s-1];
                if (dto <= 0) continue;
                const double dP = (Pr[s+1]-Pr[s-1])/dto;
                const double wgt = 0.5*(tob[s+1]-tob[s-1]);
                num += dP*dP*wgt; den += Pr[s]*Pr[s]*wgt;
            }
            const double w_rms = std::sqrt(num/den);
            std::printf("P3  gamma=%4.0f: omega_rms/omega_rot = %.4e\n", g_target, w_rms/w_rot);
            lg.push_back(std::log(g_target)); lw.push_back(std::log(w_rms/w_rot));
        }
        std::printf("P3  log-log slope of (omega_rms/omega_rot) vs gamma = %.4f (gate 3.0 +/- 0.15)\n\n",
                    fit_slope(lg, lw));
    }

    // ═══ P4 — beaming: Monte-Carlo through Law-V aberration ═════════════
    {
        std::mt19937 rng(3); std::uniform_real_distribution<double> U(-1.0, 1.0);
        for (double g_target : {8.0, 32.0}) {
            const double b = std::sqrt(1.0-1.0/(g_target*g_target));
            std::vector<double> th; th.reserve(200000);
            for (int i = 0; i < 200000; ++i) {
                const double c1 = U(rng);                        // isotropic rest emission
                const double clab = (c1 + b)/(1.0 + b*c1);        // Law-V aberration (T10-T17)
                th.push_back(std::acos(std::min(1.0, std::max(-1.0, clab))));
            }
            std::nth_element(th.begin(), th.begin()+th.size()/2, th.end());
            const double th_med = th[th.size()/2];
            std::printf("P4  gamma=%4.0f: median lab angle x gamma = %.4f (gate 1 +/- 5%%)\n",
                        g_target, th_med*g_target);
        }
        std::printf("P4  half the emission inside theta ~ 1/gamma, from the Law-V budget alone\n");
        std::printf("    (v_circ/c = 1/gamma). DEGENERATE with SR aberration by construction of Law V.\n");
    }

    std::printf("\nPM06 done. Verdict: PM06_VERDICT.md\n");
    return 0;
}
