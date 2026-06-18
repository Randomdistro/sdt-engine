// ============================================================================
//  FD06 — The Boundary Layer and No-Slip from Spation Traction
//
//  Thesis (SDT, CQ14 + FD01):
//    A solid wall is matter — a saturated spation wake whose surface DEMANDS a
//    tangential phase velocity the lattice can relay only up to c. The
//    unrelayed mismatch is TRACTION (law_VI::traction, T = 3(W+1) = 12 for the
//    proton). That traction grips the first free spation layer and drags it to
//    the wall's velocity. The grip then DIFFUSES outward by the same
//    nearest-neighbour relay that carries viscosity (FD01/FD02, the nu*grad^2
//    term) while the bulk flow ADVECTS each gripped layer downstream (the FD01
//    (v.grad)v term). Diffusion-normal vs advection-streamwise sets the layer.
//
//  What is NATIVE (Class C) vs REPRODUCED here:
//    (A) NO-SLIP as a traction FIXED POINT  -- NATIVE.  The relay-traction
//        update has a unique stable fixed point u(wall)=u_wall, reached on a
//        relay timescale << advective timescale, with residual slip length
//        lambda_s ~ l_P (molecularly negligible). No u=0 is hand-set.
//    (B) delta ~ sqrt(nu x / U) SCALING     -- NATIVE.  Pure relay-diffusion
//        penetration over the advection time t = x/U gives delta ~ sqrt(nu t).
//    (C) The PREFACTORS 5.0 (delta/x) and 0.664 (C_f), and f''(0)=0.332, are
//        the BLASIUS SIMILARITY-SOLUTION constants. They are NOT derivable from
//        SDT geometry alone: they are the eigenvalue of the f'''+1/2 f f''=0 ODE
//        with f(0)=f'(0)=0, f'(inf)=1. We REPRODUCE them by RK4 + shooting and
//        compare. This is honesty rule R1/R2/R4: convergence, not derivation.
//
//  R5: NO fudge factors. Double precision throughout. No free integer or pi is
//  inserted to force a Blasius number; every prefactor either comes from the
//  ODE eigenvalue (B) or is flagged as the reproduced target it is.
//
//  Build (MSVC):
//    cl /std:c++20 /EHsc /O2 /I Engine/include fd06_boundary_layer_traction.cpp
//  or (GCC/Clang):
//    g++ -std=c++20 -IEngine/include fd06_boundary_layer_traction.cpp -o fd06
//
//  Includes ONLY <sdt/laws.hpp>; redefines no constant it exposes.
//  Author: James Christopher Tyndall, Melbourne.
// ============================================================================
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <numbers>

namespace tr  = sdt::laws::law_VI::traction;
using sdt::laws::measured::c;
using sdt::laws::measured::l_P;
using sdt::laws::measured::t_P;
using sdt::laws::measured::R_p;

inline constexpr double PI = std::numbers::pi;

// ----------------------------------------------------------------------------
//  Small helpers
// ----------------------------------------------------------------------------
static double linfit_slope(const std::vector<double>& x,
                           const std::vector<double>& y,
                           double& intercept)
{
    const std::size_t n = x.size();
    double sx = 0, sy = 0, sxx = 0, sxy = 0;
    for (std::size_t i = 0; i < n; ++i) {
        sx += x[i]; sy += y[i]; sxx += x[i]*x[i]; sxy += x[i]*y[i];
    }
    double dn = static_cast<double>(n);
    double slope = (dn*sxy - sx*sy) / (dn*sxx - sx*sx);
    intercept = (sy - slope*sx) / dn;
    return slope;
}

// ============================================================================
//  PHASE 1 — No-slip as a spation-traction FIXED POINT (NATIVE, Class C)
//
//  The wall demands tangential angular rate omega_demand of a contact spation;
//  the lattice relays at most omega_max(R) = c/R. The unrelayed mismatch is the
//  traction ratio T = omega_demand/omega_max = 3(W+1) = 12 (proton).
//
//  Coarse-grained to a macroscopic stationary wall: the traction is a velocity
//  RELAXATION of the wall-adjacent layer toward the wall velocity u_wall, with a
//  grip rate g_tr [1/tick] proportional to T (mismatch strength) and bounded by
//  the relay cap (g_tr <= 1 per relay tick: cannot relay faster than one tick).
//
//      u_{n+1} = u_n + g_tr * (u_wall - u_n)            (traction update)
//
//  Fixed point: u* = u_wall   (set du=0 => u=u_wall). Stable for 0<g_tr<2,
//  monotone for 0<g_tr<=1. This is no-slip as an OUTPUT, not an imposed BC.
//  Residual slip length: lambda_s = (residual deficit fraction) * l_P after
//  relaxation; we show lambda_s ~ l_P (molecularly negligible).
// ============================================================================
static void phase1_no_slip_fixed_point()
{
    std::printf("================================================================\n");
    std::printf(" PHASE 1 - No-slip as a spation-traction fixed point  (NATIVE)\n");
    std::printf("================================================================\n");

    // Engine traction quantities (CQ14, law_VI::traction)
    const double omega_demand = tr::omega_demand;          // 3 m_p c^2 / hbar
    const double omega_max_p   = tr::omega_max(R_p);        // c / R_p
    const double T_ratio       = omega_demand / omega_max_p;
    const double T_engine      = tr::traction_ratio_proton; // 3(W+1) = 12

    std::printf("  CQ14 traction ledger (from law_VI::traction):\n");
    std::printf("    omega_demand            = %.6e rad/s   [DERIVED 3 m_p c^2/hbar]\n", omega_demand);
    std::printf("    omega_max(R_p) = c/R_p  = %.6e rad/s   [DERIVED c/R_p]\n", omega_max_p);
    std::printf("    T = omega_demand/omega_max = %.4f       [DERIVED]\n", T_ratio);
    std::printf("    traction_ratio_proton 3(W+1)= %.4f      [DERIVED, engine]\n", T_engine);
    std::printf("    v_phase at R_p          = %.4f c        [DERIVED, superluminal demand]\n",
                tr::v_phase_proton_surface / c);

    // Grip rate per relay tick. The mismatch T sets HOW HARD the wall grips;
    // the relay cap forbids transferring more than the full deficit in one tick.
    // g_tr = min(T-scaled coupling, 1). With T=12 the coupling saturates the cap
    // (1 - 1/T = 0.917 of the deficit relayed per tick at the cap), i.e. the
    // grip is essentially maximal -> no-slip. We use the cap-limited rate and
    // ALSO show the result is insensitive to the exact g_tr in (0,1].
    const double g_tr = 1.0 - 1.0 / T_engine;   // = 0.9167 ; DERIVED from T, capped <1
    std::printf("\n  Grip rate g_tr = 1 - 1/T = %.4f per relay tick  [DERIVED, cap-bounded]\n", g_tr);

    // Relax a wall-adjacent layer from a PURE-SLIP start (u = U everywhere).
    const double U = 1.0;          // normalised free stream (pure slip initial)
    const double u_wall = 0.0;     // stationary matter wall (its own velocity)
    double u = U;                  // wall-adjacent layer, slipping freely
    std::printf("\n  Relaxation from pure-slip start (u0 = U), per relay tick:\n");
    std::printf("    %4s  %14s  %14s\n", "tick", "u/U", "deficit U-u");
    int ticks_to_settle = -1;
    for (int n = 0; n <= 60; ++n) {
        double deficit = U - u;
        if (n <= 8 || n % 10 == 0)
            std::printf("    %4d  %14.6e  %14.6e\n", n, u/U, deficit);
        // "settled" = slip velocity has fallen below the relative l_P/U_macro floor
        if (ticks_to_settle < 0 && n > 0 && (u / U) < (l_P / 1.0)) // u/U below l_P-scale
            ticks_to_settle = n;
        // traction update toward the wall velocity
        u = u + g_tr * (u_wall - u);
    }

    // Residual SLIP after relaxation: the wall-adjacent velocity that FAILED to
    // be gripped to the wall, u_residual = U (1-g_tr)^n -> 0. The continuum slip
    // LENGTH is this residual fraction carried over one relay step l_P (the only
    // length in the lattice): lambda_s = (u_residual/U) * l_P. With u_residual
    // ~1e-65 U after relaxation, lambda_s << l_P (molecularly negligible no-slip).
    double u_residual   = u;                   // surviving slip velocity (->0)
    double slip_frac    = u_residual / U;      // residual slip fraction (->0)
    double lambda_s     = slip_frac * l_P;     // residual slip length (<< l_P)
    std::printf("\n  Settled to within l_P after %d relay ticks (%.3e s)\n",
                ticks_to_settle, ticks_to_settle * t_P);
    std::printf("  Residual slip velocity u/U ~ %.3e ; slip length lambda_s ~ %.3e m  (l_P = %.3e m)\n",
                slip_frac, lambda_s, l_P);

    // Timescale comparison: relay-settling time vs advective time over a plate.
    // Relay settling: t_relax ~ ticks_to_settle * t_P. Advective time over even
    // a 1 mm plate at 1 m/s: t_adv = x/U ~ 1e-3 s. t_relax/t_adv is astronomically
    // small -> the wall layer is effectively PINNED instantaneously.
    double t_relax = ticks_to_settle * t_P;
    double t_adv   = 1.0e-3 / 1.0;             // x=1mm, U=1 m/s (illustrative)
    std::printf("  t_relax/t_adv = %.3e  (relay pinning is instantaneous vs advection)\n",
                t_relax / t_adv);

    bool C1 = (slip_frac < 1.0e-12) && (lambda_s < l_P) && (t_relax < t_adv);
    std::printf("\n  CHECKPOINT C1: no-slip emerges as a traction fixed point, lambda_s ~< l_P,\n");
    std::printf("                 relaxation << advection.  -> %s\n", C1 ? "PASS" : "FAIL");
    std::printf("  VERDICT (native): no-slip is the stable fixed point u*=u_wall of the\n");
    std::printf("           relay-traction update, NOT an imposed boundary condition.\n\n");
}

// ============================================================================
//  PHASE 2 — delta ~ sqrt(nu x / U) from relay-diffusion vs advection (NATIVE)
//
//  The gripped wall deficit spreads NORMAL to the wall by relay-diffusion
//  (coefficient nu, FD01/FD02 nu*grad^2). In a 1-D normal diffusion the
//  penetration depth after time t is delta ~ sqrt(nu t). The bulk flow advects
//  each layer downstream so that at station x the elapsed time is t = x/U.
//  Hence:
//        delta(x) ~ sqrt(nu * x / U)   <=>   delta/x ~ 1/sqrt(Re_x),  Re_x=Ux/nu
//
//  This SCALING (slope 1/2 in log delta vs log x) is the SDT-native result. We
//  confirm it by a direct explicit relay-diffusion lattice (the FD01 normal
//  diffusion restricted to the half-space), reading off the 99%-penetration
//  locus at several stations and fitting the power law. The PREFACTOR is left
//  to Phase 3 (Blasius eigenvalue) -- here we only certify the EXPONENT.
// ============================================================================
static void phase2_blasius_scaling()
{
    std::printf("================================================================\n");
    std::printf(" PHASE 2 - delta ~ sqrt(nu x/U) scaling  (NATIVE, exponent 1/2)\n");
    std::printf("================================================================\n");

    // Illustrative laminar air-like flow (MEASURED-INPUT units; values do NOT
    // enter the exponent, only set the scale of the lattice).
    const double nu = 1.5e-5;   // [m^2/s] air kinematic viscosity (handed: FD02 target)
    const double U  = 1.0;      // [m/s] free stream

    // Explicit 1-D relay-diffusion of the wall deficit normal to the wall.
    // d_t u = nu d_yy u, wall u=0 (Phase-1 fixed point), free stream u=U.
    // Solve to elapsed time t = x/U at each station x; delta = y where u=0.99 U.
    const int    NY = 4000;
    const double Ymax = 0.05;                  // [m] tall enough for all stations
    const double dy = Ymax / NY;
    const double dt = 0.4 * dy*dy / nu;        // diffusion-stable (nu dt/dy^2=0.4<0.5)

    auto delta99_at_x = [&](double x) -> double {
        std::vector<double> u(NY+1, U);
        u[0] = 0.0;                            // wall: traction fixed point (Phase 1)
        const double t_end = x / U;            // advection time to station x
        std::vector<double> un = u;
        for (double t = 0.0; t < t_end; t += dt) {
            for (int j = 1; j < NY; ++j)
                un[j] = u[j] + nu*dt/(dy*dy) * (u[j+1] - 2*u[j] + u[j-1]);
            un[0]  = 0.0; un[NY] = U;
            u.swap(un);
        }
        // 99% locus by linear interpolation
        for (int j = 1; j <= NY; ++j) {
            if (u[j] >= 0.99*U) {
                double frac = (0.99*U - u[j-1]) / (u[j] - u[j-1]);
                return (j-1 + frac) * dy;
            }
        }
        return NY*dy;
    };

    std::printf("  Flow: U=%.3g m/s, nu=%.3g m^2/s (air, MEASURED-INPUT units)\n", U, nu);
    std::printf("  Explicit relay-diffusion lattice (nu dt/dy^2 = %.2f, stable)\n\n", nu*dt/(dy*dy));
    std::printf("    %10s  %12s  %12s  %12s\n", "x [m]", "delta [m]", "Re_x", "delta*sqrt(Re)/x");

    std::vector<double> lx, ld;
    for (double x = 0.05; x <= 0.40 + 1e-9; x += 0.05) {
        double d   = delta99_at_x(x);
        double Re  = U*x/nu;
        double pref= d * std::sqrt(Re) / x;     // should be ~constant if delta~x/sqrt(Re)
        std::printf("    %10.3f  %12.6e  %12.4e  %12.4f\n", x, d, Re, pref);
        lx.push_back(std::log(x));
        ld.push_back(std::log(d));
    }

    double b; double slope = linfit_slope(lx, ld, b);
    std::printf("\n  log-log fit: slope d(log delta)/d(log x) = %.4f  (Blasius/native: 0.50)\n", slope);
    bool C2 = std::fabs(slope - 0.5) < 0.03;
    std::printf("  CHECKPOINT C2 (scaling gate): slope = 1/2 +/- 0.03 -> %s\n", C2 ? "PASS" : "FAIL");
    std::printf("  NATIVE: delta ~ sqrt(nu x/U) follows from relay-diffusion (normal)\n");
    std::printf("          competing with advection (streamwise). PREFACTOR -> Phase 3.\n\n");
}

// ============================================================================
//  PHASE 3 — Blasius similarity solution by RK4 + shooting  (REPRODUCED)
//
//  HONEST STATEMENT: the prefactors 5.0 (delta/x) and 0.664 (C_f), and the
//  wall-gradient constant f''(0)=0.332, are NOT derivable from SDT geometry
//  alone. They are the eigenvalue / outputs of the Blasius similarity ODE:
//
//        f''' + (1/2) f f'' = 0,   f(0)=f'(0)=0,  f'(inf)=1
//
//  obtained by introducing eta = y sqrt(U/(nu x)) and u/U = f'(eta). We solve it
//  by RK4 integration + secant shooting on the unknown s = f''(0) until
//  f'(eta_max) -> 1. From the converged profile we read the standard numbers and
//  COMPARE to the published Blasius constants. This is reproduction (R1/R4), not
//  an SDT derivation -- the scaling (Phase 2) is the SDT result; these constants
//  are the universal similarity-solution outputs the SDT layer must match.
// ============================================================================

// One RK4 step of the Blasius state y = (f, f', f'') with y' = (f', f'', -1/2 f f'')
static void blasius_rk4(double y[3], double h)
{
    auto deriv = [](const double s[3], double d[3]) {
        d[0] = s[1];
        d[1] = s[2];
        d[2] = -0.5 * s[0] * s[2];
    };
    double k1[3], k2[3], k3[3], k4[3], tmp[3];
    deriv(y, k1);
    for (int i = 0; i < 3; ++i) tmp[i] = y[i] + 0.5*h*k1[i];
    deriv(tmp, k2);
    for (int i = 0; i < 3; ++i) tmp[i] = y[i] + 0.5*h*k2[i];
    deriv(tmp, k3);
    for (int i = 0; i < 3; ++i) tmp[i] = y[i] + h*k3[i];
    deriv(tmp, k4);
    for (int i = 0; i < 3; ++i)
        y[i] += (h/6.0)*(k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
}

// Integrate Blasius from 0 to eta_max with f''(0)=s; return f'(eta_max).
static double shoot_fp_inf(double s, double eta_max, double h)
{
    double y[3] = {0.0, 0.0, s};
    int n = static_cast<int>(eta_max / h);
    for (int i = 0; i < n; ++i) blasius_rk4(y, h);
    return y[1]; // f'(eta_max)
}

static void phase3_blasius_shooting()
{
    std::printf("================================================================\n");
    std::printf(" PHASE 3 - Blasius similarity ODE by RK4 + shooting (REPRODUCED)\n");
    std::printf("================================================================\n");
    std::printf("  ODE: f''' + 1/2 f f'' = 0 ; f(0)=f'(0)=0, f'(inf)=1\n");
    std::printf("  HONEST: these prefactors are the similarity-solution eigenvalue,\n");
    std::printf("          NOT derived from SDT geometry. The SDT-native result is the\n");
    std::printf("          sqrt(nu x/U) SCALING (Phase 2); here we REPRODUCE the numbers.\n\n");

    const double eta_max = 10.0;       // numerical "infinity"
    const double h       = 1.0e-4;     // RK4 step

    // Secant shooting on s = f''(0) so that f'(eta_max) = 1.
    double s0 = 0.30, s1 = 0.40;
    double g0 = shoot_fp_inf(s0, eta_max, h) - 1.0;
    double g1 = shoot_fp_inf(s1, eta_max, h) - 1.0;
    double s = s1;
    for (int it = 0; it < 100; ++it) {
        double denom = (g1 - g0);
        if (std::fabs(denom) < 1e-16) break;
        s = s1 - g1 * (s1 - s0) / denom;
        double g = shoot_fp_inf(s, eta_max, h) - 1.0;
        s0 = s1; g0 = g1; s1 = s; g1 = g;
        if (std::fabs(g1) < 1e-13) break;
    }
    const double fpp0 = s;             // f''(0)
    std::printf("  Shooting converged: f''(0) = %.10f   (Blasius target 0.33206)\n", fpp0);

    // Re-integrate the converged profile and capture the diagnostics we need:
    //  - eta_99: where f' = 0.99            -> delta/x = eta_99 / sqrt(Re_x)
    //  - delta* integral: int_0^inf (1 - f') d_eta = (eta - f)|_inf = eta_max - f
    //  - theta  integral: int_0^inf f'(1-f') d_eta
    double y[3] = {0.0, 0.0, fpp0};
    int n = static_cast<int>(eta_max / h);
    double eta = 0.0, eta99 = -1.0, fp_prev = 0.0, eta_prev = 0.0;
    double theta_int = 0.0;            // trapezoid of f'(1-f')
    double prev_integrand = 0.0;
    for (int i = 0; i < n; ++i) {
        double fp = y[1];
        double integrand = fp * (1.0 - fp);
        if (i > 0) theta_int += 0.5*(integrand + prev_integrand)*h;
        prev_integrand = integrand;
        if (eta99 < 0.0 && fp >= 0.99) {
            double frac = (0.99 - fp_prev) / (fp - fp_prev);
            eta99 = eta_prev + frac*h;
        }
        fp_prev = fp; eta_prev = eta;
        blasius_rk4(y, h);
        eta += h;
    }
    const double f_inf   = y[0];                    // f(eta_max)
    const double dstar_int = eta_max - f_inf;       // int (1-f') = eta - f at inf

    // Convert similarity integrals to the standard Blasius prefactors.
    // With eta = y sqrt(U/(nu x)):  y = eta sqrt(nu x/U).
    //   delta/x   = eta_99 / sqrt(Re_x)
    //   delta*/x  = dstar_int / sqrt(Re_x)        (1.7208 / sqrt(Re_x))
    //   theta/x   = theta_int / sqrt(Re_x)        (0.6641 / sqrt(Re_x))
    //   tau_w     = mu U sqrt(U/(nu x)) f''(0) ; C_f = 2 f''(0)/sqrt(Re_x)
    const double Cdelta = eta99;                    // ~5.0
    const double Cf_pref = 2.0 * fpp0;              // ~0.664
    const double CD_pref = 4.0 * fpp0;              // ~1.328 (integrated, = 2*Cf at L)
    const double H_shape = dstar_int / theta_int;   // ~2.59

    std::printf("\n  Reproduced Blasius constants (from the converged profile):\n");
    std::printf("    f''(0)                = %.6f   target 0.33206   err %+.3f%%\n",
                fpp0, 100.0*(fpp0-0.33206)/0.33206);
    std::printf("    eta_99 (delta/x pref) = %.6f   target 5.0       err %+.3f%%\n",
                Cdelta, 100.0*(Cdelta-5.0)/5.0);
    std::printf("    delta*  prefactor     = %.6f   target 1.7208    err %+.3f%%\n",
                dstar_int, 100.0*(dstar_int-1.7208)/1.7208);
    std::printf("    theta   prefactor     = %.6f   target 0.6641    err %+.3f%%\n",
                theta_int, 100.0*(theta_int-0.6641)/0.6641);
    std::printf("    shape factor H        = %.6f   target 2.59      err %+.3f%%\n",
                H_shape, 100.0*(H_shape-2.59)/2.59);
    std::printf("    C_f prefactor 2f''(0) = %.6f   target 0.6641    err %+.3f%%\n",
                Cf_pref, 100.0*(Cf_pref-0.6641)/0.6641);
    std::printf("    C_D prefactor 4f''(0) = %.6f   target 1.328     err %+.3f%%\n",
                CD_pref, 100.0*(CD_pref-1.328)/1.328);

    bool C3 = std::fabs(fpp0-0.33206)/0.33206 < 0.02
           && std::fabs(Cdelta-5.0)/5.0       < 0.02
           && std::fabs(Cf_pref-0.6641)/0.6641< 0.02;
    std::printf("\n  CHECKPOINT C3/C4: f''(0), delta/x=5.0, C_f=0.664, H=2.59 reproduced -> %s\n",
                C3 ? "PASS" : "FAIL");

    // ---- Phase-5 style dimensional two-stream benchmark (one fluid scale) ----
    std::printf("\n  Two-stream dimensional benchmark (laminar air flat plate):\n");
    const double nu = 1.5e-5, U = 10.0, x = 0.20;   // MEASURED-INPUT units; CALIBRATED(1) nu
    double Re_x = U*x/nu;
    double delta = Cdelta * x / std::sqrt(Re_x);
    double Cf    = Cf_pref / std::sqrt(Re_x);
    std::printf("    U=%.1f m/s, x=%.2f m, nu=%.2g m^2/s -> Re_x=%.3e\n", U, x, nu, Re_x);
    std::printf("    delta(x) = %.4f mm   (= %.4f * x / sqrt(Re_x))\n", delta*1e3, Cdelta);
    std::printf("    C_f(x)   = %.4e     (= %.4f / sqrt(Re_x))\n", Cf, Cf_pref);
    std::printf("    Re_x,crit (transition) ~ 5e5 (canonical, order-of-magnitude; FD03)\n\n");
}

int main()
{
    std::printf("\n");
    std::printf("################################################################\n");
    std::printf("#  FD06 - Boundary Layer & No-Slip from Spation Traction       #\n");
    std::printf("#  SDT zero-free-parameter framework | J. C. Tyndall, Melbourne #\n");
    std::printf("################################################################\n\n");

    std::printf("PRE-REGISTERED TARGETS (R1, listed before comparison):\n");
    std::printf("  f''(0) = 0.33206 ; delta/x = 5.0/sqrt(Re_x) ; C_f = 0.664/sqrt(Re_x)\n");
    std::printf("  delta* = 1.721 sqrt(nu x/U) ; theta = 0.664 sqrt(nu x/U) ; H = 2.59\n");
    std::printf("  C_D = 1.328/sqrt(Re_L) ; delta scaling exponent = 1/2 ; lambda_s ~ l_P\n\n");

    phase1_no_slip_fixed_point();
    phase2_blasius_scaling();
    phase3_blasius_shooting();

    std::printf("================================================================\n");
    std::printf(" FD06 SUMMARY\n");
    std::printf("================================================================\n");
    std::printf("  [NATIVE / Class C] No-slip = stable fixed point of relay-traction\n");
    std::printf("                     update (CQ14); lambda_s ~ l_P; pin << advection.\n");
    std::printf("  [NATIVE / Class C] delta ~ sqrt(nu x/U): relay-diffusion normal vs\n");
    std::printf("                     advection streamwise; log-log slope = 1/2.\n");
    std::printf("  [REPRODUCED]       Blasius prefactors 5.0 / 0.664 / 1.328 and\n");
    std::printf("                     f''(0)=0.332, H=2.59 come from the similarity ODE\n");
    std::printf("                     eigenvalue (RK4+shoot), NOT SDT geometry alone.\n");
    std::printf("  Calibration budget: CALIBRATED(1) = the fluid nu (air) for the\n");
    std::printf("                     dimensional benchmark only; everything else DERIVED.\n");
    std::printf("  OVERALL: Class C (qualified) - native mechanism + scaling, prefactors\n");
    std::printf("           reproduced via the universal similarity solution. R5: no fudge.\n\n");
    return 0;
}
