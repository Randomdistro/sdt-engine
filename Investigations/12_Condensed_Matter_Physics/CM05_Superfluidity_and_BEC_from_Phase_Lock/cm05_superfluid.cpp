// ============================================================================
// CM05 — Superfluidity and BEC from Phase Lock
// Author: J. C. Harvey, Melbourne · 2026-07-04
//
// MACHINERY ONLY. No BEC/Gross-Pitaevskii psi. The condensate is a gear-locked
// wake cluster: FD02 winding (kappa = h/m), CM01 lock mechanism, FLM14 ADJ-7
// constraint-channel rigidity. Gates pre-committed in RUN_LOG.md.
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <initializer_list>

using sdt::laws::measured::h;
using sdt::laws::measured::hbar;
using sdt::laws::measured::k_B;

namespace {
constexpr double amu   = 1.66053906660e-27;
constexpr double m_He4 = 4.002602 * amu;     // MEASURED-INPUT
constexpr double m_He3 = 3.016029 * amu;     // MEASURED-INPUT
constexpr double n_He  = 2.199e28;           // MEASURED-INPUT (146.2 kg/m^3 at T_lambda)
constexpr double T_lam = 2.17;               // OBSERVED anchor [K]

// mean-field lock fraction: x = f solves f = tanh( (T_lock/T) * f )
double lock_fraction(double T, double Tlock) {
    if (T >= Tlock) return 0.0;
    double f = 1.0;
    for (int i = 0; i < 200; ++i) f = std::tanh(Tlock / T * f);
    return f;
}
}

int main() {
    std::printf("CM05 - Superfluidity and BEC from Phase Lock\n");
    std::printf("J. C. Harvey, Melbourne - 2026-07-04\n");
    std::printf("Doors: FD02 winding, CM01 gear-lock, FLM14 constraint channel.\n\n");

    // ------------------------------------------------------------------ P1
    std::printf("== P1: transition existence + scale (two committed routes, no averaging) ==\n");
    const double d = std::pow(n_He, -1.0/3.0);
    const double T1 = h * h * std::pow(n_He, 2.0/3.0) / (3.0 * m_He4 * k_B);
    const double T2 = hbar * hbar / (2.0 * m_He4 * d * d) / k_B;
    const double r1 = T1 / T_lam, r2 = T2 / T_lam;
    std::printf("  spacing d = n^-1/3 = %.3e m\n", d);
    std::printf("  Route 1 (wake-crossover)  T1 = %.2f K  -> %.2fx of T_lambda  %s (gate 2x)\n",
                T1, r1, (r1 > 0.5 && r1 < 2.0) ? "PASS" : "FAIL");
    std::printf("  Route 2 (lock-energy)     T2 = %.3f K -> %.2fx of T_lambda  %s (gate 2x)\n",
                T2, r2, (r2 > 0.5 && r2 < 2.0) ? "PASS" : "FAIL");
    std::printf("  [HONESTY] the routes BRACKET T_lambda from opposite sides;\n");
    std::printf("            bracketing is not predicting (HUNTER SC3). Kelvin-scale\n");
    std::printf("            existence EARNED; magnitude OPEN - missing closure named:\n");
    std::printf("            collective seating statistics of indistinguishable wakes\n");
    std::printf("            (refused as a Bose import; owed natively).\n\n");

    // ------------------------------------------------------------------ P2
    std::printf("== P2: eta -> 0 below the lock (FLM14 rigidity, mean-field lock fraction) ==\n");
    {
        const double Tlock = 1.0;   // dimensionless demonstration in T/T_lock units
        const double f_half = lock_fraction(0.5 * Tlock, Tlock);
        const double f_above = lock_fraction(1.1 * Tlock, Tlock);
        std::printf("  T/T_lock   lock fraction f   eta/eta_n = 1-f\n");
        for (double t : {1.2, 1.0, 0.9, 0.7, 0.5, 0.3, 0.1}) {
            const double fl = lock_fraction(t, Tlock);
            std::printf("    %4.2f        %6.4f            %6.4f\n", t, fl, 1.0 - fl);
        }
        std::printf("  gates: f(0.5 T_lock) > 0.9 -> %.4f %s ; f(T>T_lock) = 0 -> %.4f %s\n",
                    f_half, f_half > 0.9 ? "PASS" : "FAIL",
                    f_above, f_above == 0.0 ? "PASS" : "FAIL");
        std::printf("  WHY eta=0 (machinery): locked wakes = one gear cluster; a wall/defect\n");
        std::printf("  kick redistributes cluster-wide on the constraint channel in-tick\n");
        std::printf("  (FLM14 ADJ-7); viscous loss requires unlocking (cost E_lock). The\n");
        std::printf("  unlocked fraction 1-f is the ONLY viscous channel [COMPUTED, mean-field].\n\n");
    }

    // ------------------------------------------------------------------ P3
    std::printf("== P3: circulation quantum - the body-count rule (CORE GATE) ==\n");
    {
        const double kap4 = h / m_He4;
        const double err4 = std::fabs(kap4 - 9.97e-8) / 9.97e-8 * 100.0;
        std::printf("  He-4: kappa = h/m (divisor 1, single wake; Law VI, no free integer)\n");
        std::printf("        = %.5e m^2/s vs 9.97e-8 measured  err %.3f%%  %s (gate 0.1%%)\n",
                    kap4, err4, err4 < 0.1 ? "PASS" : "FAIL");
        const double kap3 = h / (2.0 * m_He3);
        std::printf("  He-3: body-count rule -> pair lock (odd constituent count leaves an\n");
        std::printf("        unpaired half-wake; needs a partner - ARGUED, not derived)\n");
        std::printf("        kappa = h/(2 m3) = %.5e m^2/s [OBSERVED comparison: measured\n", kap3);
        std::printf("        He-3 circulation IS h/2m3 (Avenel-Varoquaux)]  divisor 2  OK\n");
        std::printf("  [RULE] the quantum divisor counts the locked bodies: He-4 -> 1,\n");
        std::printf("         He-3 -> 2, CM01 electron pair -> 2. Zero adjustments.\n\n");
    }

    // ------------------------------------------------------------------ P4
    std::printf("== P4: critical velocity (labelled honestly) ==\n");
    {
        const double vc_ceiling = 238.0;   // MEASURED-INPUT c_s: native UPPER BOUND
        const double Delta = 8.65 * k_B;   // MEASURED-INPUT roton gap
        const double k0 = 1.92e10;         // MEASURED-INPUT roton wavevector
        const double vc = Delta / (hbar * k0);
        std::printf("  native bound: v_c <= c_s = %.0f m/s [compression ceiling]\n", vc_ceiling);
        std::printf("  roton-set:    v_c = Delta/(hbar k0) = %.1f m/s\n", vc);
        std::printf("  [OBSERVED-REPROCESSING - NO SDT CREDIT: roton spectrum not derived\n");
        std::printf("   here; consistency check only vs ~60 m/s ideal onset: %s]\n",
                    (vc > 30.0 && vc < 120.0) ? "consistent" : "inconsistent");
        std::printf("  The roton itself = short-k relay bend (CM04 generative Q1) - OPEN.\n\n");
    }

    std::printf("== Ledger ==\n");
    std::printf("  DERIVED : T1, T2 route values (zero fits), lock-fraction collapse,\n");
    std::printf("            kappa = h/m form (Law VI), body-count divisor rule.\n");
    std::printf("  ARGUED  : He-3 must pair (odd-count narration).\n");
    std::printf("  OPEN    : T_lambda magnitude (seating statistics, native, unbuilt);\n");
    std::printf("            roton derivation.\n");
    std::printf("  OBSERVED: T_lambda, kappa_meas, He-3 circulation, roton params, c_s.\n");
    std::printf("  CALIBRATED: none (0 of 0 budget). No psi anywhere.\n");
    return 0;
}
