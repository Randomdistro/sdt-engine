// ═══════════════════════════════════════════════════════════════════════
//  PM01 — Magnetism as Collective Vortex Circulation
//  Author: J. C. Harvey, Melbourne · 2026-07-03
//  Pre-commitments: RUN_LOG.md (written before this file).
//
//  NATIVE CHAIN FIREWALL:  // NO B-in-tesla / NO qv×B / NO µ_B,µ_N here
//  Native units: circulation quantum κ = 1, lattice density ρ_a = 1,
//  carrier inertia m = 1, lengths in bundle radii. SI appears ONLY in the
//  final reporting section, every such line tagged [IMPORTED].
//
//  Phases:
//   P1  one vortex, one wake — Γ_v = h/m (FD02 quantum), g dimensionless
//   P2a aligned bundle (magnet): w_φ ∝ 1/r forced by circulation count
//   P2b drift bundle (wire): B_φ ∝ 1/r forced by momentum-flux conservation
//       + non-conserving control (1/s²) which must FAIL Ampère
//   P2c ∇·(∇×w) ≡ 0 on an asymmetric 3-D field (pre-flagged: calculus
//       identity — the SDT content is the identification B ≡ ∇×w)
//   P3  Lorentz sign: the two native push channels (Magnus, entrainment/
//       Coriolis) tested against the 4-cell (±carrier × ±field) pattern,
//       plus gyration-frequency-vs-field scaling for both channels
//   P4  DEFERRED (pivot row 5) — OBSERVED-inputs standoff for context only
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <random>
#include <vector>
#include <array>
#include <algorithm>

using namespace sdt::laws;

// ── helpers ─────────────────────────────────────────────────────────────
static double fit_slope(const std::vector<double>& x, const std::vector<double>& y) {
    // least-squares slope of y vs x
    const size_t n = x.size();
    double sx = 0, sy = 0, sxx = 0, sxy = 0;
    for (size_t i = 0; i < n; ++i) { sx += x[i]; sy += y[i]; sxx += x[i]*x[i]; sxy += x[i]*y[i]; }
    return (n*sxy - sx*sy) / (n*sxx - sx*sx);
}

int main() {
    std::printf("PM01 — Magnetism as Collective Vortex Circulation (J. C. Harvey, 2026-07-03)\n");
    std::printf("Native chain: NO B-in-tesla / NO qv:B / NO mu_B,mu_N anywhere before final SI map.\n\n");

    // ═══ P1 — one vortex, one wake ══════════════════════════════════════
    // Native statement: the carrier's wake circulation is one quantum, kappa = 1.
    // FD02 handshake (SI value quoted for the record; a circulation, not a moment):
    const double Gamma_e_SI = measured::h / measured::m_e;   // [m^2/s]
    std::printf("P1  per-vortex circulation quantum  kappa = 1 (native) = h/m_e = %.6e m^2/s [FD02]\n", Gamma_e_SI);
    std::printf("P1  electron moment stays a WAKE-CIRCULATION quantity; g-factor (B17) = 2.0023 (dimensionless).\n");
    std::printf("P1  magneton count used anywhere in this tool: 0\n\n");

    // ═══ P2a — aligned bundle (magnet geometry) ════════════════════════
    // N carriers, each an aligned unit-kappa vortex, uniform in the unit disc.
    // w(r) = sum of per-carrier azimuthal wakes kappa/(2 pi s).
    {
        const int Nc = 20000;
        std::mt19937 rng(42);
        std::uniform_real_distribution<double> U(0.0, 1.0);
        std::vector<double> cx(Nc), cy(Nc);
        for (int i = 0; i < Nc; ++i) {
            const double r = std::sqrt(U(rng)), th = 2.0*std::numbers::pi*U(rng);
            cx[i] = r*std::cos(th); cy[i] = r*std::sin(th);
        }
        auto w_at = [&](double x, double y, double& wx, double& wy) {
            wx = 0; wy = 0;
            for (int i = 0; i < Nc; ++i) {
                const double dx = x - cx[i], dy = y - cy[i];
                const double s2 = dx*dx + dy*dy;
                // per-carrier azimuthal wake: (kappa/2pi) * (-dy, dx)/s^2   (|w| = kappa/(2 pi s))
                wx += (-dy) / (2.0*std::numbers::pi*s2);
                wy += ( dx) / (2.0*std::numbers::pi*s2);
            }
        };
        // exponent of |w|(r) outside the bundle, r in [2,20] (one decade)
        std::vector<double> lr, lw;
        for (int k = 0; k < 12; ++k) {
            const double r = 2.0 * std::pow(10.0, k/11.0);
            double acc = 0;
            for (int a = 0; a < 64; ++a) {
                const double th = 2.0*std::numbers::pi*a/64.0;
                double wx, wy; w_at(r*std::cos(th), r*std::sin(th), wx, wy);
                acc += std::hypot(wx, wy);
            }
            lr.push_back(std::log(r)); lw.push_back(std::log(acc/64.0));
        }
        const double p2a = fit_slope(lr, lw);
        // circulation count: loop integral of w at r = 1.5, 3, 10 vs enclosed kappa (= Nc)
        double worst = 0;
        for (double r : {1.5, 3.0, 10.0}) {
            double circ = 0; const int M = 512;
            for (int a = 0; a < M; ++a) {
                const double th = 2.0*std::numbers::pi*a/M;
                double wx, wy; w_at(r*std::cos(th), r*std::sin(th), wx, wy);
                // dl = r dth * (-sin, cos)
                circ += (wx*(-std::sin(th)) + wy*std::cos(th)) * r * (2.0*std::numbers::pi/M);
            }
            worst = std::max(worst, std::fabs(circ - Nc)/Nc);
        }
        std::printf("P2a aligned bundle (N=%d): |w| exponent (r=2..20)  = %+ .4f   (gate -1 +/- 2%%)\n", Nc, p2a);
        std::printf("P2a enclosed-circulation count, worst rel. err     = %.3e (gate <1e-3)\n", worst);
        std::printf("P2a reading: the -1 is FORCED by conservation of the enclosed circulation count\n");
        std::printf("    (Law VI quantisation: loop integral of w = N_enc * kappa, independent of r).\n\n");
    }

    // ═══ P2b — drift bundle (wire geometry) ═════════════════════════════
    // Per-carrier TRANSVERSE wake of a z-drifting carrier:
    //  candidate C1 (momentum-flux conserving, FD02 Stokes balance):
    //     drag force transmitted through any sphere of radius s is constant
    //     -> stress ~ 1/s^2 -> entrained axial velocity w_z ~ 1/s.
    //  control  C0 (non-conserving): w_z ~ 1/s^2.
    // Line superposition (numerical quadrature over a wire of length L),
    // then B_phi = -dw_z/dr; fit the exponent over one decade r in [1,10].
    {
        const double L = 2000.0, q = 1.0;
        auto wz = [&](double r, int profile) {
            // Simpson quadrature over z in [-L/2, L/2]
            const int N = 200000; const double h = L / N;
            double s = 0;
            for (int i = 0; i <= N; ++i) {
                const double z = -L/2 + i*h;
                const double d = std::sqrt(r*r + z*z);
                const double f = (profile == 1) ? q/d : q/(d*d);
                const double wgt = (i == 0 || i == N) ? 1.0 : (i % 2 ? 4.0 : 2.0);
                s += wgt * f;
            }
            return s * h / 3.0;
        };
        for (int profile : {1, 0}) {
            std::vector<double> lr, lB;
            for (int k = 0; k < 12; ++k) {
                const double r = std::pow(10.0, k/11.0);           // 1 .. 10
                const double dr = 1e-3 * r;
                const double Bphi = -(wz(r+dr, profile) - wz(r-dr, profile)) / (2.0*dr);
                lr.push_back(std::log(r)); lB.push_back(std::log(std::fabs(Bphi)));
            }
            const double slope = fit_slope(lr, lB);
            if (profile == 1)
                std::printf("P2b wire, conserving wake w_z ~ 1/s : B_phi exponent = %+.4f (gate -1 +/- 2%%)\n", slope);
            else
                std::printf("P2b wire, CONTROL wake  w_z ~ 1/s^2: B_phi exponent = %+.4f (must FAIL Ampere, ~ -2)\n", slope);
        }
        std::printf("P2b reading: Ampere's -1 is FORCED by per-carrier momentum-flux conservation\n");
        std::printf("    (FD02 relay drag); a non-conserving wake cannot produce it.\n");
        std::printf("P2b sign caveat: the DIRECTION of B_phi flips with carrier drift x handedness;\n");
        std::printf("    the per-carrier axial-wake amplitude for + vs - carriers is the HANDED GAIN (see P3).\n\n");
    }

    // ═══ P2c — divergence of the curl (pre-flagged identity) ════════════
    {
        const int G = 48; const double Lb = 4.0, h = Lb/(G-1);
        std::vector<double> wx(G*G*G), wy(G*G*G), wz3(G*G*G);
        auto idx = [&](int i,int j,int k){ return (i*G + j)*G + k; };
        // asymmetric superposition of 3 skewed bundles (azimuthal + axial parts)
        const double C[3][3] = {{0.3,-0.2,0.1},{-0.5,0.4,-0.3},{0.1,0.6,0.5}};
        const double A[3][3] = {{0.2,0.5,0.84},{0.7,-0.1,0.70},{-0.3,0.4,0.87}}; // axes (approx unit)
        for (int i = 0; i < G; ++i) for (int j = 0; j < G; ++j) for (int k = 0; k < G; ++k) {
            const double x = -Lb/2 + i*h, y = -Lb/2 + j*h, z = -Lb/2 + k*h;
            double vx=0, vy=0, vz=0;
            for (int b = 0; b < 3; ++b) {
                const double dx=x-C[b][0], dy=y-C[b][1], dz=z-C[b][2];
                const double ax=A[b][0], ay=A[b][1], az=A[b][2];
                const double an = std::sqrt(ax*ax+ay*ay+az*az);
                const double ux=ax/an, uy=ay/an, uz=az/an;
                const double dpar = dx*ux+dy*uy+dz*uz;
                const double px=dx-dpar*ux, py=dy-dpar*uy, pz=dz-dpar*uz;
                const double p2 = px*px+py*py+pz*pz;
                // azimuthal part: u x d_perp / (p2 + 0.1), axial part: u * exp(-p2)
                vx += (uy*pz-uz*py)/(p2+0.1) + 0.6*ux*std::exp(-p2);
                vy += (uz*px-ux*pz)/(p2+0.1) + 0.6*uy*std::exp(-p2);
                vz += (ux*py-uy*px)/(p2+0.1) + 0.6*uz*std::exp(-p2);
            }
            wx[idx(i,j,k)]=vx; wy[idx(i,j,k)]=vy; wz3[idx(i,j,k)]=vz;
        }
        // B = curl w (central differences), then div B (central differences)
        std::vector<double> Bx(G*G*G,0), By(G*G*G,0), Bz(G*G*G,0);
        double maxB = 0;
        for (int i = 1; i < G-1; ++i) for (int j = 1; j < G-1; ++j) for (int k = 1; k < G-1; ++k) {
            const double dwz_dy = (wz3[idx(i,j+1,k)]-wz3[idx(i,j-1,k)])/(2*h);
            const double dwy_dz = (wy [idx(i,j,k+1)]-wy [idx(i,j,k-1)])/(2*h);
            const double dwx_dz = (wx [idx(i,j,k+1)]-wx [idx(i,j,k-1)])/(2*h);
            const double dwz_dx = (wz3[idx(i+1,j,k)]-wz3[idx(i-1,j,k)])/(2*h);
            const double dwy_dx = (wy [idx(i+1,j,k)]-wy [idx(i-1,j,k)])/(2*h);
            const double dwx_dy = (wx [idx(i,j+1,k)]-wx [idx(i,j-1,k)])/(2*h);
            Bx[idx(i,j,k)] = dwz_dy - dwy_dz;
            By[idx(i,j,k)] = dwx_dz - dwz_dx;
            Bz[idx(i,j,k)] = dwy_dx - dwx_dy;
            maxB = std::max({maxB, std::fabs(Bx[idx(i,j,k)]), std::fabs(By[idx(i,j,k)]), std::fabs(Bz[idx(i,j,k)])});
        }
        double maxdiv = 0;
        for (int i = 2; i < G-2; ++i) for (int j = 2; j < G-2; ++j) for (int k = 2; k < G-2; ++k) {
            const double div = (Bx[idx(i+1,j,k)]-Bx[idx(i-1,j,k)])/(2*h)
                             + (By[idx(i,j+1,k)]-By[idx(i,j-1,k)])/(2*h)
                             + (Bz[idx(i,j,k+1)]-Bz[idx(i,j,k+1-2)])/(2*h);
            maxdiv = std::max(maxdiv, std::fabs(div));
        }
        const double ratio = maxdiv * h / maxB;   // dimensionless
        std::printf("P2c max|div B| * h / max|B| = %.3e   (gate <= 1e-9)\n", ratio);
        std::printf("P2c PRE-FLAGGED: div(curl) = 0 is vector calculus (discrete central differences\n");
        std::printf("    commute). The SDT content is ONLY the identification B == curl(w); given it,\n");
        std::printf("    'no monopole' (E58) is a theorem. This gate is a consistency check, not a discovery.\n\n");
    }

    // ═══ P3 — Lorentz sign: the two native channels vs the 4-cell pattern ═
    // Channel M (Magnus, FD07-native):      m dv/dt = h * zhat x (v - w(r))
    // Channel E (entrainment/Coriolis):     m dv/dt = v x (Omega zhat)
    // Ambient swirl: w = (Omega/2) * zhat x r  (uniform vorticity Omega).
    // EM target pattern (with q <-> h): deflection sign flips with EITHER
    // carrier sign OR field sign — i.e. deflection ~ f(h * Omega).
    {
        auto run_magnus = [&](double hnd, double Om, double T, double& sgn_vy, double& freq) {
            double x=0, y=0, vx=1, vy=0; const double dt = 1e-4; const int NS = int(T/dt);
            int zc = 0; double pvx = vx; double t_first = -1, t_last = -1;
            for (int s = 0; s < NS; ++s) {
                auto acc = [&](double X, double Y, double VX, double VY, double& AX, double& AY) {
                    const double wxA = -(Om/2.0)*Y, wyA = (Om/2.0)*X;
                    const double rx = VX - wxA, ry = VY - wyA;
                    AX = hnd * (-ry);  AY = hnd * (rx);   // h * zhat x (v-w)
                };
                // RK4
                double k1x,k1y,k2x,k2y,k3x,k3y,k4x,k4y;
                double a1x,a1y,a2x,a2y,a3x,a3y,a4x,a4y;
                acc(x,y,vx,vy,a1x,a1y);                       k1x=vx; k1y=vy;
                acc(x+0.5*dt*k1x, y+0.5*dt*k1y, vx+0.5*dt*a1x, vy+0.5*dt*a1y, a2x,a2y); k2x=vx+0.5*dt*a1x; k2y=vy+0.5*dt*a1y;
                acc(x+0.5*dt*k2x, y+0.5*dt*k2y, vx+0.5*dt*a2x, vy+0.5*dt*a2y, a3x,a3y); k3x=vx+0.5*dt*a2x; k3y=vy+0.5*dt*a2y;
                acc(x+dt*k3x, y+dt*k3y, vx+dt*a3x, vy+dt*a3y, a4x,a4y);                 k4x=vx+dt*a3x; k4y=vy+dt*a3y;
                x  += dt*(k1x+2*k2x+2*k3x+k4x)/6.0;  y  += dt*(k1y+2*k2y+2*k3y+k4y)/6.0;
                vx += dt*(a1x+2*a2x+2*a3x+a4x)/6.0;  vy += dt*(a1y+2*a2y+2*a3y+a4y)/6.0;
                if (s == 200) sgn_vy = (vy > 0) ? +1.0 : -1.0;       // initial deflection
                if (pvx <= 0 && vx > 0) { if (t_first < 0) t_first = s*dt; t_last = s*dt; ++zc; }
                pvx = vx;
            }
            freq = (zc > 1) ? 2.0*std::numbers::pi*(zc-1)/(t_last - t_first) : 0.0;
        };
        auto run_coriolis = [&](double hnd, double Om, double T, double& sgn_vy, double& freq) {
            (void)hnd; // entrainment turning is handedness-blind by construction
            double vx=1, vy=0; const double dt = 1e-4; const int NS = int(T/dt);
            int zc = 0; double pvx = vx; double t_first=-1, t_last=-1;
            for (int s = 0; s < NS; ++s) {
                const double ax =  vy*Om, ay = -vx*Om;  // v x (Om zhat)
                vx += ax*dt; vy += ay*dt;
                const double n = std::hypot(vx,vy); vx/=n; vy/=n; // renormalise (turning does no work)
                if (s == 200) sgn_vy = (vy > 0) ? +1.0 : -1.0;
                if (pvx <= 0 && vx > 0) { if (t_first<0) t_first = s*dt; t_last = s*dt; ++zc; }
                pvx = vx;
            }
            freq = (zc > 1) ? 2.0*std::numbers::pi*(zc-1)/(t_last - t_first) : 0.0;
        };

        std::printf("P3 four-cell sign matrix. EM target: deflection ~ f(h*Omega) — flips with EITHER sign.\n");
        std::printf("    cell (h,Om)      Magnus vy-sign   Coriolis vy-sign   EM-target sign f(h*Om)\n");
        int magnus_match = 0, coriolis_match = 0;
        for (double hnd : {+1.0, -1.0}) for (double Om : {+1.0, -1.0}) {
            double sM, fM, sC, fC;
            run_magnus(hnd, Om, 2.0, sM, fM);
            run_coriolis(hnd, Om, 2.0, sC, fC);
            const double target = (hnd*Om > 0) ? +1.0 : -1.0;  // any fixed bilinear convention
            if (sM == target) ++magnus_match;
            if (sC == target) ++coriolis_match;
            std::printf("    (%+.0f,%+.0f)          %+.0f              %+.0f                 %+.0f\n",
                        hnd, Om, sM, sC, target);
        }
        std::printf("P3 Magnus channel matches EM bilinear pattern in %d/4 cells (signed by h only).\n", magnus_match);
        std::printf("P3 Coriolis channel matches EM bilinear pattern in %d/4 cells (signed by Om only).\n", coriolis_match);

        double s0, f0, s1, f1, s10, f10;
        run_magnus(+1.0, 0.0, 40.0, s0, f0);
        run_magnus(+1.0, 1.0, 40.0, s1, f1);
        run_magnus(+1.0, 10.0, 40.0, s10, f10);
        std::printf("P3 Magnus gyration freq: Om=0 -> %.4f ; Om=1 -> %.4f ; Om=10 -> %.4f\n", f0, f1, f10);
        std::printf("    (freq set by OWN kappa*rho/m; saturates, never proportional to field. Note: the\n");
        std::printf("    co-handed cell is dynamically UNSTABLE in rigid ambient swirl — runaway, not orbit.)\n");
        double sc1, fc1, sc10, fc10;
        run_coriolis(+1.0, 1.0, 40.0, sc1, fc1);
        run_coriolis(+1.0, 10.0, 40.0, sc10, fc10);
        std::printf("P3 Coriolis gyration freq: Omega=1 -> %.4f ; Omega=10 -> %.4f (ratio %.3f; = field, h-blind)\n",
                    fc1, fc10, fc10/fc1);
        std::printf("P3 CONCLUSION: Magnus = signed (own h), field-magnitude-blind. Coriolis = field-\n");
        std::printf("    proportional, handedness-blind. The qv x B pattern needs a BILINEAR h*swirl\n");
        std::printf("    coupling that NEITHER native channel supplies. That bilinear handed gain is\n");
        std::printf("    dimensionally e-shaped -> the EMC02 wall (e irreducible). Recorded OPEN.\n\n");
    }

    // ═══ Final SI map — every line below is tagged [IMPORTED] ═══════════
    std::printf("SI map [IMPORTED — appears only here, per firewall]:\n");
    std::printf("[IMPORTED] wire field form    B(r) = mu0 I / (2 pi r); per-carrier axial-wake\n");
    std::printf("[IMPORTED] amplitude map      gamma_carrier <-> mu0 e v_drift  (the un-derived handed gain).\n");
    {
        // P4 context only (DEFERRED per pivot row 5): Chapman–Ferraro standoff,
        // all inputs OBSERVED, mu0 imported -> labelled CONVERGENCE, not native.
        const double mu0 = 4.0e-7*std::numbers::pi;          // [IMPORTED]
        const double Bs  = 3.12e-5;                          // [T] OBSERVED (magnetosphere.hpp earth::B_surface)
        const double nsw = 5.0e6;                            // [m^-3] OBSERVED solar wind
        const double vsw = 4.0e5;                            // [m/s]  OBSERVED solar wind
        const double rho = nsw * measured::m_p;
        const double r_mp = std::pow((Bs*Bs/(2.0*mu0)) / (rho*vsw*vsw), 1.0/6.0);
        std::printf("[IMPORTED] P4 context: Chapman-Ferraro standoff = %.2f R_E (observed ~10 R_E;\n", r_mp);
        std::printf("           order-correct; textbook pressure balance, NOT claimed native. P4 DEFERRED.)\n");
    }
    std::printf("\nPM01 done. Verdict: PM01_VERDICT.md\n");
    return 0;
}
