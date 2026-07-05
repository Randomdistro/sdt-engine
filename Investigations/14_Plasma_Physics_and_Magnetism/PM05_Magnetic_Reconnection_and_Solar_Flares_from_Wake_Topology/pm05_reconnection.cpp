// ═══════════════════════════════════════════════════════════════════════
//  PM05 — Magnetic Reconnection and Solar Flares from Wake Topology
//  Author: J. C. Harvey, Melbourne · 2026-07-05 · pre-commits: RUN_LOG.md
//
//  SCOPE (honest, committed): the snap dynamics need a 3-D lattice
//  wake-topology solver (ROOT-SIM class) that does not exist. This tool
//  does ONLY the analytically-earnable parts: stored-energy geometry,
//  the (pre-flagged trivial) annihilation ledger, the slow-branch rate
//  assembly from PM07's measured slip law, and OBSERVED-inputs orders.
//  NO reconnection dynamics are simulated or claimed.
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace sdt::laws;
static constexpr double PI = 3.14159265358979323846;

// Gaussian-core vortex bundle: azimuthal wake speed v(r) = (G/2πr)(1-exp(-r²/2σ²))
static void bundle_w(double x, double y, double cx, double cy, double G, double sig,
                     double& wx, double& wy) {
    const double dx = x-cx, dy = y-cy; const double r2 = dx*dx+dy*dy;
    const double r = std::sqrt(r2) + 1e-12;
    const double vth = (G/(2.0*PI*r)) * (1.0 - std::exp(-r2/(2.0*sig*sig)));
    wx += vth * (-dy/r); wy += vth * (dx/r);
}

int main() {
    std::printf("PM05 — Reconnection & Flares from Wake Topology (J. C. Harvey, 2026-07-05)\n");
    std::printf("SCOPE: analytic/energetic parts only; snap dynamics OPEN (no 3-D lattice solver).\n\n");

    // ═══ P1 — stored throughput of two opposed bundles (native units) ═══
    {
        const int NG = 500; const double Lb = 20.0, h = Lb/NG, sig = 1.0, G = 1.0;
        auto energy = [&](double d, double& Uint) {
            double U = 0; Uint = 0;
            for (int i = 0; i < NG; ++i) for (int j = 0; j < NG; ++j) {
                const double x = -Lb/2 + (i+0.5)*h, y = -Lb/2 + (j+0.5)*h;
                double w1x=0, w1y=0, w2x=0, w2y=0;
                bundle_w(x,y, -d/2,0.0, +G, sig, w1x,w1y);
                bundle_w(x,y, +d/2,0.0, -G, sig, w2x,w2y);   // ANTI-parallel partner
                const double wx = w1x+w2x, wy = w1y+w2y;
                U    += 0.5*(wx*wx + wy*wy)*h*h;              // rho_a = 1
                Uint += (w1x*w2x + w1y*w2y)*h*h;
            }
            return U;
        };
        std::printf("P1  U = (1/2) rho_a int |w|^2  (native swirl energy; B^2/2mu0 form via the\n");
        std::printf("    rho_a u^2 <-> B^2/mu0 conversion = ORPHAN-1/HG-1-adjacent, PM07 — disclosed)\n");
        double U8i, U4i, U2i;
        const double U8 = energy(8.0, U8i), U4 = energy(4.0, U4i), U2 = energy(2.0, U2i);
        std::printf("    d=8: U=%.4f (U_int=%+.4f) | d=4: U=%.4f (U_int=%+.4f) | d=2: U=%.4f (U_int=%+.4f)\n",
                    U8, U8i, U4, U4i, U2, U2i);
        std::printf("P1  U_int < 0 and deepening as anti-parallel bundles press together: the sheared\n");
        std::printf("    sheet stores LESS than two free bundles — the surplus (U_self-side) is what a\n");
        std::printf("    topology change can dump. Releasable-on-annihilation = U(d) itself (net-zero end).\n\n");

        // ═══ P2 — annihilation ledger (PRE-FLAGGED trivial bookkeeping) ═
        std::printf("P2  ledger (pre-flagged as bookkeeping, per the prompt's own anti-tautology rule):\n");
        std::printf("    quanta: in = +N ⊕ -N ; annihilated pairwise = N ; out = 0 — exact by construction.\n");
        std::printf("    energy released at d=2 (full annihilation): dU = %.4f native units; residual 0.\n", U2);
        std::printf("    THE SNAP (when/whether the wake topology jumps, and what fraction annihilates)\n");
        std::printf("    is NOT computable here. OPEN — missing tool: 3-D lattice wake-topology solver\n");
        std::printf("    (ROOT-SIM class; same family as APS04 Phase-2 / PM03 rebuild).\n");
        std::printf("T4  div B == 0 through annihilation: w remains a superposition of curls under quanta\n");
        std::printf("    removal => structural identity (PM01 P2c; pre-flagged consistency, not discovery).\n\n");
    }

    // ═══ P3 — rates: slow branch assembled; fast branch OPEN ════════════
    {
        std::printf("P3  SLOW BRANCH (pre-classed LINGUISTIC/CONVERGENCE — textbook chain, renamed nouns):\n");
        std::printf("    diffusive matching v_in = eta/delta (PM07 measured slip: leak ∝ eta, slope 0.943)\n");
        std::printf("    + sheet continuity v_in L = v_A delta  =>  v_in/v_A = S^(-1/2), S = L v_A / eta\n");
        std::printf("    S:        1e4      1e8      1e12     1e14\n    M_A:   ");
        for (double S : {1e4, 1e8, 1e12, 1e14}) std::printf("  %.1e", 1.0/std::sqrt(S));
        std::printf("\n    observed fast rate ~ 1e-2..1e-1: at coronal S ~ 1e12-1e14 Sweet-Parker is 4-6\n");
        std::printf("    ORDERS too slow. The fast-reconnection gap is stated, not papered over.\n");
        std::printf("P3  FAST BRANCH: OPEN. Named native candidate (FLM14 ADJ-7 two-channel dynamics):\n");
        std::printf("    a gear-locked flux structure carries phase constraint on the CONSTRAINT channel\n");
        std::printf("    (uncapped rigidity), so a topology snap is a constraint-RELEASE event, not a\n");
        std::printf("    diffusion process — rate set by release geometry, weakly S-dependent. PREDICTION\n");
        std::printf("    (falsifiable vs resistive MHD, matches prompt Q1): fast-rate plateau nearly flat\n");
        std::printf("    in S. CANDIDATE ONLY — needs the 3-D lattice solver. NOT claimed derived.\n\n");
    }

    // ═══ P4 — flare / CME orders (OBSERVED inputs, fixed pre-run) ═══════
    {
        const double mu0 = 4.0e-7*PI;                       // [IMPORTED — final-line SI only]
        std::printf("P4  OBSERVED inputs (fixed in RUN_LOG before computing): B in {0.02,0.03} T,\n");
        std::printf("    L in {3e7,5e7} m, n in {1e15,1e16} m^-3.\n");
        double Umin = 1e99, Umax = 0;
        for (double B : {0.02, 0.03}) for (double L : {3e7, 5e7}) {
            const double U = (B*B/(2.0*mu0)) * L*L*L * 1.0e7; // J -> erg
            Umin = std::min(Umin, U); Umax = std::max(Umax, U);
        }
        std::printf("P4  stored active-region energy band: %.1e .. %.1e erg  (flare band 1e31-1e32: %s)\n",
                    Umin, Umax, (Umin < 1e32 && Umax > 1e31 ? "OVERLAPS - order-correct" : "MISS"));
        double vmin = 1e99, vmax = 0;
        for (double B : {0.02, 0.03}) for (double n : {1e15, 1e16}) {
            const double vA = B/std::sqrt(mu0 * n * measured::m_p) / 1e3;   // km/s
            vmin = std::min(vmin, vA); vmax = std::max(vmax, vA);
        }
        // ADJ-1 (disclosed): first build printed a sloppy "order-correct" for a band that
        // entirely misses the committed 1e2-1e3 km/s gate. Classification corrected; numbers unchanged.
        const bool cme_ok = (vmin <= 1e3 && vmax >= 1e2);
        std::printf("P4  v_A band: %.0f .. %.0f km/s  (CME gate 1e2-1e3 km/s: %s)\n",
                    vmin, vmax, (cme_ok ? "PASS" : "FAIL - band entirely above gate"));
        if (!cme_ok)
            std::printf("P4  CME-speed FAIL recorded: 'CME launch speed = source-region v_A' overshoots by\n"
                        "    ~0.6-1.3 orders with the committed inputs. Premise, not numerics -> VERDICT SS7.\n");
        std::printf("P4  class: CONVERGENCE — dimensional bookkeeping on OBSERVED inputs; no SDT-specific\n");
        std::printf("    content beyond the native reading of B^2/2mu0 as swirl energy (ORPHAN-1 caveat).\n");
    }

    std::printf("\nPM05 done. Verdict: PM05_VERDICT.md\n");
    return 0;
}
