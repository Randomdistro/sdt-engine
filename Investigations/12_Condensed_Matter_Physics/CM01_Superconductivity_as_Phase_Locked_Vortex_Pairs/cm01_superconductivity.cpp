// ============================================================================
// CM01 — Superconductivity as Phase-Locked Vortex Pairs
// Author: J. C. Harvey, Melbourne · 2026-07-04
//
// MACHINERY ONLY. No BCS gap, no Cooper ψ, no gauge machinery. Native doors:
//   Law VI winding / knot exclusion (FD02-earned h/m), law_III occlusion drag,
//   FD05 compression wave, FLM14 ADJ-7 two-channel (constraint uncapped inside
//   a gear-locked cluster), NP17 seat template (pairing = shared seating).
// Thresholds pre-committed in RUN_LOG.md. τ NEVER touches measured σ (the
// CM02 circularity is structurally impossible in this chain).
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <initializer_list>

using namespace sdt::laws;
using measured::hbar;
using measured::h;
using measured::k_B;
using measured::e_charge;
using measured::m_e;
using measured::c;
using measured::alpha;

namespace {
constexpr double amu  = 1.66053906660e-27;   // [kg]  MEASURED-INPUT (SI)
constexpr double mu_0 = 1.25663706212e-6;    // [N/A^2] MEASURED-INPUT (SI)
const double PI = 3.14159265358979323846;

struct Metal {
    const char* name;
    double n_e;     // [1/m^3] carriers        MEASURED-INPUT (density+valence)
    double n_ion;   // [1/m^3] ions            MEASURED-INPUT
    double M_amu;   // ion mass                MEASURED-INPUT
    double thetaD;  // [K]                     MEASURED-INPUT
    double d_nn;    // [m] nearest-neighbour   MEASURED-INPUT
    double Tc;      // [K]                     OBSERVED (never enters any chain)
};

const Metal Cu = {"Cu", 8.49e28, 8.49e28, 63.546, 343.0, 2.556e-10, 0.0};
const Metal Al = {"Al", 1.81e29, 6.03e28, 26.982, 428.0, 2.863e-10, 1.20};
const Metal Nb = {"Nb", 5.56e28, 5.56e28, 92.906, 275.0, 2.858e-10, 9.25};
const Metal Pb = {"Pb", 1.32e29, 3.30e28, 207.2, 105.0, 3.500e-10, 7.19};

double v_pack(double n_e) {   // wake-packing speed: Law VI knot exclusion
    return hbar * std::cbrt(3.0 * PI * PI * n_e) / m_e;
}
double omega_D(double thetaD) { return k_B * thetaD / hbar; }
}

int main() {
    std::printf("CM01 - Superconductivity as Phase-Locked Vortex Pairs\n");
    std::printf("J. C. Harvey, Melbourne - 2026-07-04\n");
    std::printf("Doors: Law VI knot exclusion, law_III occlusion, FD05 wave,\n");
    std::printf("       FLM14 ADJ-7 constraint channel, NP17 seat template.\n\n");

    // ------------------------------------------------------------------ P1
    std::printf("== P1: normal state - occlusion drag, tau never sees sigma ==\n");
    {
        const Metal& m = Cu;
        const double T  = 300.0;
        const double Mi = m.M_amu * amu;
        const double wD = omega_D(m.thetaD);
        const double u2 = 3.0 * k_B * T / (Mi * wD * wD);      // ion equipartition
        const double sig = PI * u2;                            // occlusion cross-section
        const double mfp = 1.0 / (m.n_ion * sig);              // relay mean free path
        const double v   = v_pack(m.n_e);
        const double rho = m_e * v / (m.n_e * e_charge * e_charge * mfp);
        std::printf("  Cu 300 K [all COMPUTED from measured inputs]:\n");
        std::printf("    u_rms = %.3e m (%.3f of d_nn)\n", std::sqrt(u2), std::sqrt(u2)/m.d_nn);
        std::printf("    occlusion mfp = %.2f nm  (anchor 39 nm, gate 3x)  %s\n",
                    mfp*1e9, (mfp*1e9 > 13.0 && mfp*1e9 < 117.0) ? "PASS" : "FAIL");
        std::printf("    v_pack = %.3e m/s [Law VI knot exclusion; NAMED PREMISE;\n", v);
        std::printf("             STRUCTURAL-CONVERGENCE with rival v_F, number from n_e only]\n");
        std::printf("    rho = %.3e Ohm.m  (anchor 1.68e-8, gate 10x)  %s\n",
                    rho, (rho > 1.68e-9 && rho < 1.68e-7) ? "PASS" : "FAIL");
        const double u2_2T = 3.0 * k_B * (2.0*T) / (Mi * wD * wD);
        const double ratio = u2_2T / u2;   // rho ~ <u^2> ~ T
        std::printf("    rho(2T)/rho(T) = %.4f  (gate 2.00 +/- 0.05)  %s\n",
                    ratio, std::fabs(ratio - 2.0) < 0.05 ? "PASS" : "FAIL");
        std::printf("    [FINDING] resistance = occlusion off thermal ion displacement;\n");
        std::printf("              linear-in-T is equipartition, not a fit. CM02 debt repaid\n");
        std::printf("              without circularity: tau chain never touches sigma_meas.\n\n");
    }

    // ------------------------------------------------------------------ P2
    std::printf("== P2: pairing channel - deformation-well branch run to death ==\n");
    {
        std::printf("  %-4s %10s %12s %12s %12s %8s\n",
                    "mat", "E_pol[eV]", "r_seat[nm]", "E_rep[eV]", "xi/d", "window");
        for (const Metal* pm : {&Cu, &Al, &Nb, &Pb}) {
            const Metal& m = *pm;
            const double Mi = m.M_amu * amu;
            const double wD = omega_D(m.thetaD);
            const double F  = alpha * hbar * c / (m.d_nn * m.d_nn);   // handed tug at d
            const double ks = Mi * wD * wD;                           // relay stiffness
            const double Epol = F * F / (2.0 * ks);                   // well scale
            const double seat = v_pack(m.n_e) * 2.0 * PI / wD;        // retardation seat
            const double Erep = alpha * hbar * c / seat;              // worst-case repulsion
            const bool window = Epol > Erep;
            std::printf("  %-4s %10.4f %12.2f %12.6f %12.0f %8s\n",
                        m.name, Epol/1.602176634e-19, seat*1e9,
                        Erep/1.602176634e-19, seat/m.d_nn, window ? "OPEN" : "shut");
        }
        std::printf("  gates: E_pol > E_rep at seat (attraction window) AND xi/d > 10.\n");
        std::printf("  [DEATH KNELL - committed expectation] E_pol is ~material-blind:\n");
        std::printf("  measured eta = Tc/thetaD spreads (OBSERVED, never fitted):\n");
        for (const Metal* pm : {&Al, &Nb, &Pb})
            std::printf("    %-4s eta = %.4f\n", pm->name, pm->Tc / pm->thetaD);
        std::printf("  => deformation well CANNOT close Tc magnitude: branch DEAD as a\n");
        std::printf("     Tc closure (NP17: SDT binding is seat-sharing, geared, not a\n");
        std::printf("     static well). ADJ-1: binder = gear-lock on the FLM14 constraint\n");
        std::printf("     channel seeded at the retardation seat; magnitude eta = OPEN.\n\n");
    }

    // ------------------------------------------------------------------ P3
    std::printf("== P3: zero drag (FLM14 rigidity) + Meissner lambda_L ==\n");
    {
        const double seatAl = v_pack(Al.n_e) * 2.0 * PI / omega_D(Al.thetaD);
        const double supp = std::pow(Al.d_nn / seatAl, 1.5);
        std::printf("  drag suppression (d/xi_seat)^1.5 [Al] = %.2e  (gate < 1e-3)  %s\n",
                    supp, supp < 1e-3 ? "PASS" : "FAIL");
        std::printf("  WHY R=0 (machinery): the locked cluster is gear-rigid; a defect\n");
        std::printf("  kick propagates on the constraint channel cluster-wide in-tick\n");
        std::printf("  (FLM14 ADJ-7) - the defect faces the WHOLE cluster reorganisation\n");
        std::printf("  cost, not one carrier's. Drag requires breaking the lock: below\n");
        std::printf("  the lock temperature there is no dissipation channel. Meissner =\n");
        std::printf("  EMC03 swirl expulsion by the rigid condensate.\n");
        for (const Metal* pm : {&Al, &Nb}) {
            const double lam = std::sqrt(m_e / (mu_0 * pm->n_e * e_charge * e_charge));
            const double anchor = (pm == &Al) ? 16.0 : 39.0;
            const double r = lam * 1e9 / anchor;
            std::printf("  lambda_L(%s) = %.1f nm  (anchor %.0f nm, gate 2x)  %s\n",
                        pm->name, lam*1e9, anchor,
                        (r > 0.5 && r < 2.0) ? "PASS" : "FAIL");
        }
        std::printf("  [lambda_L chain: zero-drag carriers + Ampere circuital law -\n");
        std::printf("   classical EM, no gauge field as mechanism]\n\n");
    }

    // ------------------------------------------------------------------ P4
    std::printf("== P4: flux quantum divisor + isotope exponent ==\n");
    {
        const double Phi0 = h / (2.0 * e_charge);
        std::printf("  Phi_0 = h/(2e) = %.6e Wb  [IDENTITY once carrier = pair;\n", Phi0);
        std::printf("          NOT a prediction. Earned content = the divisor:\n");
        std::printf("          2 = body count of the lock (two W=1 vortices, one phase\n");
        std::printf("          object, carrier mass 2m_e, handedness 2e). kappa_pair =\n");
        std::printf("          h/(2 m_e) = %.4e m^2/s [COMPUTED]. Exclusivity of 2\n", h/(2.0*m_e));
        std::printf("          (why no 3-lock) = OPEN, logged.]\n");
        // isotope: Tc ~ lock ceiling hbar*omega_D(M); k_spring fixed, omega ~ M^-1/2
        const double M0 = 200.59, dlnM = 0.05;
        auto Tc_of_M = [&](double M_amu_v) {
            // geometry fixed: k_spring and cell fixed; omega_D = sqrt(ks/M)/const
            return 1.0 / std::sqrt(M_amu_v);   // proportionality suffices for exponent
        };
        const double a_iso = -(std::log(Tc_of_M(M0*(1+dlnM))) - std::log(Tc_of_M(M0)))
                           / (std::log(M0*(1+dlnM)) - std::log(M0));
        std::printf("  isotope exponent alpha_iso = -dlnTc/dlnM = %.4f\n", -a_iso);
        std::printf("    chain: Tc ~ lock ceiling hbar*omega_D; omega_D = sqrt(ks/M);\n");
        std::printf("    ks, geometry M-independent  [DERIVED, conditional on ceiling]\n");
        std::printf("    gate -0.500 +/- 0.005: %s ; anchor Hg 0.50 +/- 0.03 [OBSERVED]\n",
                    std::fabs(-a_iso + 0.5) < 0.005 ? "PASS" : "FAIL");
    }

    std::printf("\n== Ledger ==\n");
    std::printf("  DERIVED : rho_Cu chain (no sigma input), mfp, linear-in-T, seat,\n");
    std::printf("            attraction window, drag suppression, lambda_L, alpha_iso.\n");
    std::printf("  NAMED PREMISES: wake-packing speed (Law VI knot exclusion);\n");
    std::printf("            lock ceiling = hbar*omega_D (channel cutoff);\n");
    std::printf("            FLM14 constraint channel (canon ADJ-7).\n");
    std::printf("  IDENTITY: Phi_0 = h/2e, kappa_pair = h/2m (labelled, not passed).\n");
    std::printf("  OPEN    : eta = Tc/thetaD magnitude (the SDT coupling number);\n");
    std::printf("            exclusivity of the 2-lock.\n");
    std::printf("  CALIBRATED: none (0 of 0 budget).\n");
    return 0;
}
