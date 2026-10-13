// ============================================================================
//  TD05 — Phase Transitions and Latent Heat from Reconfiguration
//
//  3D MD of a packing of wake-bound hard vortices (pair-potential proxy: LJ,
//  the ONE declared measured form). N = 108 FCC, rho* = 1.0, PBC, r_cut = 2.5.
//  NO Landau / order-parameter field anywhere in the dynamics: S(k111) is a
//  diagnostic only. Heating then cooling ramp; latent heat read from the
//  caloric jump; bond ledger = first-shell count x measured per-bond energy.
//
//  P1  sharp transition + hysteresis (first-order character).
//  P2  latent heat vs reconfiguration (bond) ledger; T2 identity DISCLOSED.
//  P3  argon mapping with OBSERVED LJ parameters (order of magnitude only).
//  P4  Clausius-Clapeyron: DEFERRED (declared in RUN_LOG).
//
//  Author: J. C. Harvey, Melbourne. 2026-07-03.
//  Build: cl /std:c++20 /EHsc /O2 /utf-8 /I Engine/include td05_packing_reconfiguration.cpp
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

namespace {
const double kB = sdt::laws::measured::k_B;      // unit bridge (argon mapping)
std::mt19937_64 rng(20260703ULL);

constexpr int    N   = 108;
constexpr double RHO = 1.0;
constexpr double RC  = 2.5, RC2 = RC * RC;
constexpr double DT  = 0.002;

struct Sys {
    double L;
    std::vector<double> x, y, z, vx, vy, vz, fx, fy, fz;
    double Upot = 0;

    Sys() : x(N), y(N), z(N), vx(N), vy(N), vz(N), fx(N), fy(N), fz(N) {
        L = std::cbrt(N / RHO);
        const double a = L / 3.0;
        const double base[4][3] = {{0,0,0},{0.5,0.5,0},{0.5,0,0.5},{0,0.5,0.5}};
        int i = 0;
        for (int cx = 0; cx < 3; ++cx) for (int cy = 0; cy < 3; ++cy)
            for (int cz = 0; cz < 3; ++cz) for (int b = 0; b < 4; ++b) {
                x[i] = (cx + base[b][0]) * a;
                y[i] = (cy + base[b][1]) * a;
                z[i] = (cz + base[b][2]) * a; ++i;
            }
        std::normal_distribution<double> g(0.0, 1.0);
        for (int k = 0; k < N; ++k) { vx[k] = g(rng); vy[k] = g(rng); vz[k] = g(rng); }
        remove_drift();
    }
    void remove_drift() {
        double sx = 0, sy = 0, sz = 0;
        for (int i = 0; i < N; ++i) { sx += vx[i]; sy += vy[i]; sz += vz[i]; }
        for (int i = 0; i < N; ++i) { vx[i] -= sx / N; vy[i] -= sy / N; vz[i] -= sz / N; }
    }
    double mic(double d) const { d -= L * std::round(d / L); return d; }
    void forces() {
        Upot = 0;
        std::fill(fx.begin(), fx.end(), 0.0);
        std::fill(fy.begin(), fy.end(), 0.0);
        std::fill(fz.begin(), fz.end(), 0.0);
        const double ushift = 4.0 * (std::pow(RC, -12.0) - std::pow(RC, -6.0));
        for (int i = 0; i < N - 1; ++i)
            for (int j = i + 1; j < N; ++j) {
                const double dx = mic(x[i]-x[j]), dy = mic(y[i]-y[j]), dz = mic(z[i]-z[j]);
                const double r2 = dx*dx + dy*dy + dz*dz;
                if (r2 >= RC2) continue;
                const double ir2 = 1.0 / r2, ir6 = ir2*ir2*ir2;
                Upot += 4.0 * ir6 * (ir6 - 1.0) - ushift;
                const double f = 24.0 * ir6 * (2.0 * ir6 - 1.0) * ir2;
                fx[i] += f*dx; fy[i] += f*dy; fz[i] += f*dz;
                fx[j] -= f*dx; fy[j] -= f*dy; fz[j] -= f*dz;
            }
    }
    double ke() const {
        double s = 0;
        for (int i = 0; i < N; ++i) s += vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i];
        return 0.5 * s;
    }
    void step() {
        for (int i = 0; i < N; ++i) {
            vx[i] += 0.5*DT*fx[i]; vy[i] += 0.5*DT*fy[i]; vz[i] += 0.5*DT*fz[i];
            x[i] += DT*vx[i]; y[i] += DT*vy[i]; z[i] += DT*vz[i];
        }
        forces();
        for (int i = 0; i < N; ++i) {
            vx[i] += 0.5*DT*fx[i]; vy[i] += 0.5*DT*fy[i]; vz[i] += 0.5*DT*fz[i];
        }
    }
    void rescale(double Tt) {
        const double Tc = 2.0 * ke() / (3.0 * N);
        if (Tc <= 0) return;
        const double s = std::sqrt(Tt / Tc);
        for (int i = 0; i < N; ++i) { vx[i] *= s; vy[i] *= s; vz[i] *= s; }
    }
    double sk111() const {   // structure factor at FCC (111), diagnostic ONLY
        const double a = L / 3.0, k = 2.0 * std::numbers::pi / a;
        double cr = 0, ci = 0;
        for (int i = 0; i < N; ++i) {
            const double ph = k * (x[i] + y[i] + z[i]);
            cr += std::cos(ph); ci += std::sin(ph);
        }
        return (cr*cr + ci*ci) / N;
    }
    // first-shell bond census: count and mean pair energy for r < 1.35
    void bonds(double& nb_per_particle, double& ubond_mean) const {
        long nb = 0; double usum = 0;
        const double ushift = 4.0 * (std::pow(RC, -12.0) - std::pow(RC, -6.0));
        for (int i = 0; i < N - 1; ++i)
            for (int j = i + 1; j < N; ++j) {
                const double dx = mic(x[i]-x[j]), dy = mic(y[i]-y[j]), dz = mic(z[i]-z[j]);
                const double r2 = dx*dx + dy*dy + dz*dz;
                if (r2 >= 1.35 * 1.35) continue;
                const double ir6 = 1.0 / (r2*r2*r2);
                usum += 4.0 * ir6 * (ir6 - 1.0) - ushift; ++nb;
            }
        nb_per_particle = 2.0 * double(nb) / N;      // bonds per particle
        ubond_mean = (nb > 0) ? usum / nb : 0.0;
    }
};

struct Point { double T, U, S, nb, ub; };
} // namespace

int main() {
    std::printf("================================================================\n");
    std::printf(" TD05 - Phase Transitions and Latent Heat from Reconfiguration\n");
    std::printf(" J. C. Harvey, Melbourne - 2026-07-03\n");
    std::printf(" MD of wake-bound vortex packing (LJ proxy, declared). N=%d, rho*=%.1f.\n", N, RHO);
    std::printf(" No Landau field: S(k111) is diagnostic only, never enters dynamics.\n");
    std::printf("================================================================\n\n");

    Sys s; s.forces();

    auto run_T = [&](double Tt) -> Point {
        for (int it = 0; it < 2000; ++it) { s.step(); if (it % 10 == 0) s.rescale(Tt); }
        double U = 0, S = 0; int nm = 0;
        double nb = 0, ub = 0;
        for (int it = 0; it < 3000; ++it) {
            s.step();
            if (it % 50 == 0) {
                U += s.Upot; S += s.sk111(); ++nm;
                double b1, b2; s.bonds(b1, b2); nb += b1; ub += b2;
            }
        }
        return { Tt, U / nm / N, S / nm / N, nb / nm, ub / nm };
    };

    std::vector<Point> heat, cool;
    std::printf("heating ramp (T* 0.40 -> 2.16, dT* = 0.08):\n");
    std::printf("    T*      U/N        S(k111)/N   bonds/N   u_bond\n");
    for (double T = 0.40; T <= 2.161; T += 0.08) {
        Point p = run_T(T);
        heat.push_back(p);
        std::printf("  %5.2f   %8.4f    %7.4f     %6.3f   %7.4f\n", p.T, p.U, p.S, p.nb, p.ub);
    }
    std::printf("\ncooling ramp (2.16 -> 0.40):\n");
    std::printf("    T*      U/N        S(k111)/N\n");
    for (double T = 2.16; T >= 0.399; T -= 0.08) {
        Point p = run_T(T);
        cool.push_back(p);
        std::printf("  %5.2f   %8.4f    %7.4f\n", p.T, p.U, p.S);
    }

    // ------------------------------------------------------------------
    // P1 - sharpness + hysteresis
    // ------------------------------------------------------------------
    std::printf("\nP1: sharpness and hysteresis\n");
    bool p1 = true;
    int jmp = 1; double dmax = 0;
    std::vector<double> dus;
    for (size_t i = 1; i < heat.size(); ++i) {
        const double du = heat[i].U - heat[i-1].U;
        dus.push_back(du);
        if (du > dmax) { dmax = du; jmp = int(i); }
    }
    std::vector<double> dsort = dus; std::sort(dsort.begin(), dsort.end());
    const double dmed = dsort[dsort.size()/2];
    const double Tm = 0.5 * (heat[jmp-1].T + heat[jmp].T);
    std::printf("  largest heating step: dU = %.4f eps/particle at T* = %.2f (median step %.4f)\n",
                dmax, Tm, dmed);
    std::printf("  sharpness: dU > 0.4 [%s], dU > 4x median [%s]\n",
                dmax > 0.4 ? "PASS" : "FAIL", dmax > 4.0*dmed ? "PASS" : "FAIL");
    if (dmax <= 0.4 || dmax <= 4.0*dmed) p1 = false;
    // RUN-1 note: first implementation checked a SINGLE step (S(jmp-1) -> S(jmp)),
    // stricter than the RUN_LOG commitment "collapses from > 0.3 to < 0.1 across
    // <= 2 steps"; the transition straddles two steps (partial melt in the middle
    // point). ADJ-1: implement the committed 2-step-window gate as written.
    bool collapse = false; double Sb = 0, Sa = 0;
    for (int a = std::max(0, jmp - 2); a < jmp; ++a)
        for (int b = jmp; b <= std::min(int(heat.size()) - 1, a + 2); ++b)
            if (heat[a].S > 0.3 && heat[b].S < 0.1) { collapse = true; Sb = heat[a].S; Sa = heat[b].S; }
    std::printf("  order parameter collapse within <= 2 steps of the jump: S/N %.3f -> %.3f\n", Sb, Sa);
    std::printf("  (committed gate: >0.3 -> <0.1 across <= 2 steps)  [%s]\n", collapse ? "PASS" : "FAIL");
    if (!collapse) p1 = false;
    double hyst = 0;
    for (size_t i = 0; i < heat.size(); ++i) {
        const double Tq = heat[i].T;
        for (size_t j = 0; j < cool.size(); ++j)
            if (std::fabs(cool[j].T - Tq) < 1e-6)
                hyst = std::max(hyst, std::fabs(heat[i].U - cool[j].U));
    }
    std::printf("  hysteresis: max |U_heat - U_cool| = %.4f (> 5x median step %.4f) [%s]\n",
                hyst, 5.0*dmed, hyst > 5.0*dmed ? "PASS" : "FAIL");
    const double Send = cool.back().S;
    std::printf("  cooling endpoint S/N = %.3f -> %s\n", Send,
                Send > 0.3 ? "recrystallised" : "glass/defective arrest (FLM09-type, reported)");
    if (hyst <= 5.0*dmed) p1 = false;

    // ------------------------------------------------------------------
    // P2 - latent heat vs bond ledger
    // ------------------------------------------------------------------
    std::printf("\nP2: latent heat vs reconfiguration ledger\n");
    bool p2 = true;
    const double Lsim = dmax;   // eps/particle across the jump
    const double dnb = heat[jmp-1].nb - heat[jmp].nb;           // bonds lost per particle
    const double ub = std::fabs(heat[jmp-1].ub);                // per-bond cost (solid side)
    const double ledger = dnb * ub;
    std::printf("  L_sim = %.4f eps/particle;  bonds lost = %.3f x |u_bond| = %.4f -> ledger %.4f\n",
                Lsim, dnb, ub, ledger);
    const double fac = (ledger > 0) ? std::max(Lsim/ledger, ledger/Lsim) : 1e9;
    std::printf("  ledger factor = %.2f  (gate 1.5)  [%s]\n", fac, fac < 1.5 ? "PASS" : "FAIL");
    if (fac >= 1.5) p2 = false;
    // Post-fire trace (diagnostics only; the committed gate above stands as it fell):
    // decompose the transition-WINDOW energy (jmp-2 .. jmp) into first-shell count
    // vs re-pricing (softening) channels.
    {
        const int a = std::max(0, jmp - 2), b = jmp;
        const double Lwin = heat[b].U - heat[a].U - dmed * (b - a - 1);  // baseline-subtracted
        const double dnbw = heat[a].nb - heat[b].nb;
        const double count_term = 0.5 * dnbw * std::fabs(heat[a].ub);
        const double soften_term = 0.5 * heat[b].nb * (std::fabs(heat[a].ub) - std::fabs(heat[b].ub));
        std::printf("  TRACE (window %0.2f->%0.2f): L_window ~ %.3f eps; first-shell split:\n",
                    heat[a].T, heat[b].T, Lwin);
        std::printf("    bond-COUNT channel  = %.3f eps (%.0f%%)\n", count_term,
                    100.0 * count_term / (count_term + soften_term));
        std::printf("    bond-REPRICING channel (surviving bonds to worse geometry) = %.3f eps (%.0f%%)\n",
                    soften_term, 100.0 * soften_term / (count_term + soften_term));
        std::printf("  -> at FIXED density the latent heat is dominated by re-pricing, not count:\n");
        std::printf("     the committed count-x-cost ledger form is the errored premise (see VERDICT).\n");
    }
    std::printf("  DISCLOSED: 'L = T_m dS' with calorimetric dS is an identity - NOT TESTED;\n");
    std::printf("  flat-T absorption is protocol-set (T controlled) - also disclosed.\n");

    // ------------------------------------------------------------------
    // P3 - argon mapping (OBSERVED LJ parameters)
    // ------------------------------------------------------------------
    std::printf("\nP3: argon order-of-magnitude (OBSERVED eps/kB = 119.8 K, sigma = 3.405 A)\n");
    bool p3 = true;
    {
        const double eps_J = 119.8 * kB;
        const double L_melt_meas = 1.18e3 / 6.02214076e23 / eps_J;   // = 1.185 eps
        const double L_vap_meas = 6.5e3 / 6.02214076e23 / eps_J;     // = 6.55 eps
        const double coh = std::fabs(heat.front().U);                 // |U|/N at T*=0.40
        const double fm = std::max(Lsim/L_melt_meas, L_melt_meas/Lsim);
        const double fv = std::max(coh/L_vap_meas, L_vap_meas/coh);
        std::printf("  L_melt: sim %.3f eps vs argon %.3f eps  -> factor %.2f (gate 3) [%s]\n",
                    Lsim, L_melt_meas, fm, fm < 3.0 ? "PASS" : "FAIL");
        std::printf("  L_vap ledger (cohesion at T*=0.4): %.3f eps vs argon %.3f eps -> factor %.2f (gate 3) [%s]\n",
                    coh, L_vap_meas, fv, fv < 3.0 ? "PASS" : "FAIL");
        std::printf("  ordering L_vap >> L_melt: %.3f >> %.3f [%s]\n",
                    coh, Lsim, coh > 3.0*Lsim ? "PASS" : "FAIL");
        std::printf("  T*_jump x 119.8 K = %.0f K vs argon T_m = 83.8 K - REPORTED ONLY:\n", Tm*119.8);
        std::printf("  fixed rho*=1.0 is off-coexistence and superheats; NOT sold as a T_m prediction.\n");
        if (fm >= 3.0 || fv >= 3.0 || coh <= 3.0*Lsim) p3 = false;
    }

    std::printf("\nP4: Clausius-Clapeyron - DEFERRED as declared in RUN_LOG (needs\n");
    std::printf("  pressure-controlled coexistence; producing a slope here would be fabrication).\n\n");

    const bool all = p1 && p2 && p3;
    std::printf("================================================================\n");
    std::printf(" TD05 GATES: P1 %s | P2 %s | P3 %s | P4 DEFERRED\n",
                p1 ? "PASS" : "FAIL", p2 ? "PASS" : "FAIL", p3 ? "PASS" : "FAIL");
    std::printf(" No order-parameter field entered the dynamics at any point.\n");
    std::printf(" VERDICT: %s - see TD05_VERDICT.md\n", all ? "PASS" : "FAIL");
    std::printf("================================================================\n");
    return all ? 0 : 1;
}
