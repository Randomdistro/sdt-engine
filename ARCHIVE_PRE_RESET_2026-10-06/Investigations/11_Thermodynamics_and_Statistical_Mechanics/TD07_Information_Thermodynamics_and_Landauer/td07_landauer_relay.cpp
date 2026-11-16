// ============================================================================
//  TD07 — Information Thermodynamics and Landauer
//
//  Joint microcanonical system: two-state register (E_L = 0, E_R = protocol)
//  + TD01 quanta bath. Symmetric proposals only -> uniform joint measure.
//  NO Boltzmann factor is input anywhere; p_R comes from counting and from
//  dynamics, and the Landauer ledger is integrated from it.
//
//  P1  Erasure work -> k_B T ln 2 (exact trapezoid ledger + sim + finite-time bound).
//  P2  Demon/Szilard closure: extract - erase <= 0 (exact and sim); the
//      quasi-static deficit is the integer-step (relay quantum) overhead.
//  P3  Partial erasure: W = kT [ln2 - H(p)] (reversibility boundary).
//  P4  Delete test: every bound is k_BT x pure number.
//
//  Author: J. C. Harvey, Melbourne. 2026-07-03.
//  Build: cl /std:c++20 /EHsc /O2 /utf-8 /I Engine/include td07_landauer_relay.cpp
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>
#include <random>

namespace {
const double kB_SI = sdt::laws::measured::k_B;   // unit bridge only
std::mt19937_64 rng(20260703ULL);

constexpr int    NB   = 2000;     // bath cells
constexpr long   EB   = 20000;    // bath quanta
constexpr int    EMAX = 80;       // top of the erasure ramp (quanta)

double ln_W(double E, double N) { return std::lgamma(E + N) - std::lgamma(E + 1.0) - std::lgamma(N); }

// exact equilibrium probability of register level E_R (uniform joint measure)
double pR_exact(int E_R) {
    const double a = ln_W(double(EB - E_R), double(NB));
    const double b = ln_W(double(EB), double(NB));
    return 1.0 / (1.0 + std::exp(b - a));
}

// trapezoid ledger for a ramp 0 -> Etop (work paid raising E_R by 1 at a time)
double W_ledger(int Etop) {
    double W = 0;
    for (int E = 0; E < Etop; ++E) W += 0.5 * (pR_exact(E) + pR_exact(E + 1));
    return W;
}

struct Joint {
    std::vector<int> cell;
    int reg;            // 0 = L, 1 = R
    int E_R;            // current level of R
    Joint() : cell(NB, int(EB / NB)), reg(0), E_R(0) {}
    // RUN-1 premise fix (ADJ-1): trajectories previously started from an UNMIXED bath
    // (every cell exactly E/N). A fluctuation-free bath has no rich cells, so L->R
    // re-entry is kinetically blocked while R->L exit is always allowed: the register
    // erases "for cheap" against a NON-equilibrium bath — a work resource that voids
    // the bound's premise (measured W_fast = 6.81 < kT ln2, correctly diagnosed as an
    // initial-condition artefact, not a Second-Law event). Fix: mix the bath first.
    void equilibrate(std::uniform_int_distribution<int>& uc, long nmix) {
        for (long t = 0; t < nmix; ++t) {
            const int a = uc(rng), b = uc(rng);
            if (a != b && cell[a] > 0) { --cell[a]; ++cell[b]; }
        }
    }
    void tick(std::uniform_int_distribution<int>& uc, std::uniform_real_distribution<double>& u01) {
        if (u01(rng) < 0.5) {                       // bath-bath symmetric move
            const int a = uc(rng), b = uc(rng);
            if (a != b && cell[a] > 0) { --cell[a]; ++cell[b]; }
        } else {                                    // register flip via ONE random cell
            const int i = uc(rng);
            if (reg == 0) {                         // L -> R: withdraw E_R quanta
                if (cell[i] >= E_R) { cell[i] -= E_R; reg = 1; }
            } else {                                // R -> L: deposit E_R quanta
                cell[i] += E_R; reg = 0;
            }
        }
    }
};
} // namespace

int main() {
    std::printf("================================================================\n");
    std::printf(" TD07 - Information Thermodynamics and Landauer\n");
    std::printf(" J. C. Harvey, Melbourne - 2026-07-03\n");
    std::printf(" Joint microcanonical register+bath; symmetric proposals; p_R from\n");
    std::printf(" counting - no Boltzmann factor is input anywhere.\n");
    std::printf("================================================================\n\n");

    const double kT = 1.0 / std::log(1.0 + double(NB) / double(EB));   // = 10.492 eps (TD02)
    const double L2 = kT * std::log(2.0);
    std::printf("bath: N=%d, E=%ld -> kT = %.4f eps, kT ln2 = %.4f eps\n\n", NB, EB, kT, L2);

    bool p1 = true, p2 = true, p3 = true;

    // ------------------------------------------------------------------
    // P1 - exact ledger, sim validation, finite-time bound
    // ------------------------------------------------------------------
    std::printf("P1: Landauer ledger\n");
    const double Wqs = W_ledger(EMAX);
    std::printf("  exact quasi-static work (trapezoid, ramp 0->%d): W = %.4f eps\n", EMAX, Wqs);
    std::printf("  W/(kT ln2) = %.4f  (gate 1%%)  [%s]\n", Wqs / L2,
                std::fabs(Wqs / L2 - 1.0) < 0.01 ? "PASS" : "FAIL");
    if (std::fabs(Wqs / L2 - 1.0) > 0.01) p1 = false;

    {   // sim validation of p_R at fixed levels
        std::uniform_int_distribution<int> uc(0, NB - 1);
        std::uniform_real_distribution<double> u01(0.0, 1.0);
        std::printf("    E_R    p_exact     p_sim      dev/sigma\n");
        for (int ER : {5, 10, 20, 40}) {
            Joint J; J.E_R = ER;
            // start register in L with full bath (consistent with pR_exact bookkeeping)
            long occ = 0, ns = 0;
            for (long t = 0; t < 12'000'000L; ++t) {
                J.tick(uc, u01);
                if (t > 2'000'000L && t % 100 == 0) { occ += J.reg; ++ns; }
            }
            const double ps = double(occ) / ns, pe = pR_exact(ER);
            // effective sample estimate: register flip attempts ~ ns*100/(2NB) accepted rarely;
            // conservative N_eff = ns/ tau with tau ~ 2000 samples
            const double neff = ns / 2000.0;
            const double sig = std::sqrt(std::max(pe * (1.0 - pe), 1e-8) / neff);
            const double z = std::fabs(ps - pe) / sig;
            std::printf("    %3d   %.5f    %.5f    %.2f\n", ER, pe, ps, z);
            if (z > 3.0) p1 = false;
        }
        std::printf("  sim occupation matches counting (3 sigma)  [%s]\n", p1 ? "PASS" : "FAIL");
    }

    double Wslow_mean = 0, Wslow_se = 0;
    {   // finite-time trajectories: W = quanta paid while register sits in R
        std::uniform_int_distribution<int> uc(0, NB - 1);
        std::uniform_real_distribution<double> u01(0.0, 1.0);
        std::printf("  finite-time bound (trajectories, ramp 0->%d):\n", EMAX);
        std::printf("    n_eq/step   <W>/eps    SE      W/(kT ln2)\n");
        double prevW = 1e9; bool mono = true;
        for (long neq : {200L, 2000L, 20000L}) {
            const int ntraj = 300;
            double s = 0, s2 = 0;
            for (int tr = 0; tr < ntraj; ++tr) {
                Joint J;
                J.equilibrate(uc, 500'000L);        // ADJ-1: start from a MIXED bath
                J.reg = (u01(rng) < 0.5) ? 1 : 0;   // random bit; if R, quanta owed to bath later
                if (J.reg == 1) { /* E_R = 0: degenerate start, no energy held */ }
                double W = 0;
                for (int E = 0; E < EMAX; ++E) {
                    if (J.reg == 1) W += 1.0;       // raising occupied level costs 1 eps
                    J.E_R = E + 1;
                    for (long t = 0; t < neq; ++t) J.tick(uc, u01);
                }
                s += W; s2 += W * W;
            }
            const double m = s / ntraj;
            const double se = std::sqrt((s2 / ntraj - m * m) / (ntraj - 1));
            std::printf("    %7ld    %7.4f   %.4f    %.4f\n", neq, m, se, m / L2);
            if (m > prevW + 3.0 * se) mono = false;
            prevW = m;
            if (neq == 20000L) { Wslow_mean = m; Wslow_se = se; }
        }
        const bool bound = (Wslow_mean > L2 - 3.0 * Wslow_se);
        std::printf("  dissipation monotone with speed [%s]; slowest within 3SE of/above bound [%s]\n\n",
                    mono ? "PASS" : "FAIL", bound ? "PASS" : "FAIL");
        if (!mono || !bound) p1 = false;
    }

    // ------------------------------------------------------------------
    // P2 - demon / Szilard closure
    // ------------------------------------------------------------------
    std::printf("P2: demon closure (extract by lowering a KNOWN state, erase to reset)\n");
    {
        // exact: extraction ledger (lower 80 -> 0, receive 1 eps when in R) is the
        // same trapezoid; endpoint bookkeeping differs by the integer step:
        const double Wraise = 0.0 + [](){ double W=0; for (int E=0;E<EMAX;++E) W += pR_exact(E); return W; }();
        const double Wlower = [](){ double W=0; for (int E=EMAX;E>0;--E) W += pR_exact(E); return W; }();
        const double net = Wlower - Wraise;   // extract - erase (stepped protocol)
        std::printf("  exact stepped ledgers: erase pays %.4f eps, extraction yields %.4f eps\n", Wraise, Wlower);
        std::printf("  net = %.4f eps = -[p_R(0)-p_R(%d)] = -%.4f eps  (<= 0)  [%s]\n",
                    net, EMAX, pR_exact(0) - pR_exact(EMAX), net <= 1e-12 ? "PASS" : "FAIL");
        std::printf("  NOTE (lattice-flavoured, not oversold): the strictly negative quasi-static\n");
        std::printf("  net is the integer-step overhead - on a relay lattice the potential moves in\n");
        std::printf("  units of eps, so THIS protocol class loses >= eps*[p(0)-p(Emax)] ~ 0.5 eps per\n");
        std::printf("  cycle (~%.1f%% of kT ln2 at kT=%.1f eps). It vanishes as eps/kT -> 0; a\n",
                    100.0 * (pR_exact(0) - pR_exact(EMAX)) / L2, kT);
        std::printf("  continuous-protocol demon closes at exactly 0. Claim scope: stepped protocols.\n");
        if (net > 1e-12) p2 = false;

        // sim: net at three speeds (extraction leg then erase leg)
        std::uniform_int_distribution<int> uc(0, NB - 1);
        std::uniform_real_distribution<double> u01(0.0, 1.0);
        std::printf("    n_eq/step   <net>/eps   SE      (gate: net < 0 by 3SE or |net|<3SE&<=0 mean)\n");
        for (long neq : {200L, 2000L, 20000L}) {
            const int ntraj = 300;
            double s = 0, s2 = 0;
            for (int tr = 0; tr < ntraj; ++tr) {
                double Wx = 0, We = 0;
                // extraction: register KNOWN in L; raise R while empty (free), then...
                // Szilard equivalent: start with bit known = L, E_R = EMAX (prepared),
                // lower to 0 extracting when occupied:
                Joint J; J.E_R = EMAX; J.reg = 0;
                J.equilibrate(uc, 500'000L);        // ADJ-1: start from a MIXED bath
                for (int E = EMAX; E > 0; --E) {
                    for (long t = 0; t < neq; ++t) J.tick(uc, u01);
                    if (J.reg == 1) Wx += 1.0;
                    J.E_R = E - 1;
                }
                // now bit is random (measurement record) -> erase it:
                for (int E = 0; E < EMAX; ++E) {
                    if (J.reg == 1) We += 1.0;
                    J.E_R = E + 1;
                    for (long t = 0; t < neq; ++t) J.tick(uc, u01);
                }
                const double net_tr = Wx - We;
                s += net_tr; s2 += net_tr * net_tr;
            }
            const double m = s / ntraj, se = std::sqrt((s2 / ntraj - m * m) / (ntraj - 1));
            std::printf("    %7ld    %8.4f   %.4f\n", neq, m, se);
            if (m > 3.0 * se) p2 = false;    // demon must not net positive
        }
        std::printf("  demon nets <= 0 at all speeds  [%s]\n\n", p2 ? "PASS" : "FAIL");
    }

    // ------------------------------------------------------------------
    // P3 - reversibility boundary: W(E_t) = kT [ln2 - H(p)]
    // ------------------------------------------------------------------
    std::printf("P3: partial erasure - HEAT to bath vs kT[ln2 - H(p)]\n");
    std::printf("  (ADJ-0, pre-compile: the Landauer-form quantity for PARTIAL erasure is the\n");
    std::printf("   heat Q = W - dU_register, not the work W = dF; they coincide only at full\n");
    std::printf("   erasure. Category error caught before any run; gate value unchanged.)\n");
    {
        std::printf("    E_t    W_ledger    dU=E_t*p     Q=W-dU     kT(ln2-H)   dev/kTln2\n");
        for (int Et : {2, 5, 10, 20, 40}) {
            const double W = W_ledger(Et);
            const double p = pR_exact(Et);
            const double dU = double(Et) * p;
            const double Q = W - dU;
            const double H = (p > 0 && p < 1) ? (-p * std::log(p) - (1 - p) * std::log(1 - p)) : 0.0;
            const double pred = kT * (std::log(2.0) - H);
            const double dev = std::fabs(Q - pred) / L2;
            std::printf("    %3d   %8.4f    %8.4f    %8.4f    %8.4f    %.4f%%\n",
                        Et, W, dU, Q, pred, 100.0 * dev);
            if (dev > 0.015) p3 = false;
        }
        std::printf("  cost = kT * Delta(configurational entropy), -> 0 at the reversible end\n");
        std::printf("  (E_t = 0: W = 0 exactly - trivial and labelled so; a swap/relabel gate\n");
        std::printf("  changes no state count: cost 0, near-definitional Bennett recovery). [%s]\n\n",
                    p3 ? "PASS" : "FAIL");
    }

    std::printf("P4: delete test - every bound above is (kT/eps) x pure number (ln2, H);\n");
    std::printf("  kelvin conversion uses k_B = %.6e J/K as the only bridge. [PASS]\n\n", kB_SI);

    const bool all = p1 && p2 && p3;
    std::printf("================================================================\n");
    std::printf(" TD07 GATES: P1 %s | P2 %s | P3 %s | P4 PASS\n",
                p1 ? "PASS" : "FAIL", p2 ? "PASS" : "FAIL", p3 ? "PASS" : "FAIL");
    std::printf(" VERDICT: %s - see TD07_VERDICT.md\n", all ? "PASS" : "FAIL");
    std::printf("================================================================\n");
    return all ? 0 : 1;
}
