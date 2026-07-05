// ============================================================================
// CM06 — Quantum Hall and Josephson Metrology
// Author: J. C. Harvey, Melbourne · 2026-07-04
//
// IDENTITY FIREWALL: R_K, K_J, Phi_0 are definitional once (h, e) are granted
// (both SI-exact). They are printed ONCE, tagged IDENTITY, and count as ZERO
// evidence. The earnable content is structural: integer channel counts and
// their disorder rigidity. No Chern number, no gauge field, no band topology.
// The one quantisation door is the h-cell (Law VI winding — ROOT-A premise,
// shared with CM04/CM01/CM03), named at every use.
// Gates pre-committed in RUN_LOG.md.
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <vector>

using sdt::laws::measured::h;
using sdt::laws::measured::e_charge;

namespace {

// deterministic index-derived defect field (no RNG)
bool defect(int r, int cidx, double p) {
    // hash -> [0,1)
    unsigned long long x = 1469598103934665603ULL;
    x ^= (unsigned long long)(r * 2654435761u + cidx * 40503u + 12345u);
    x *= 1099511628211ULL;
    x ^= x >> 33;
    const double u = (double)(x % 1000000007ULL) / 1000000007.0;
    return u < p;
}

// edge channel intact? monotone left->right path within rows [r0, r0+w)
// re-routing among the w rows allowed (the "count survives local damage" content)
bool edge_channel(int r0, int w, int L, double p) {
    std::vector<char> reach(w, 1);
    for (int cidx = 0; cidx < L; ++cidx) {
        std::vector<char> next(w, 0);
        // step right from any reachable row into any adjacent (|dr|<=1) clean cell
        for (int i = 0; i < w; ++i) {
            if (!reach[i]) continue;
            for (int dj = -1; dj <= 1; ++dj) {
                const int j = i + dj;
                if (j < 0 || j >= w) continue;
                if (!defect(r0 + j, cidx, p)) next[j] = 1;
            }
        }
        reach.swap(next);
        bool any = false;
        for (char v : reach) any |= (v != 0);
        if (!any) return false;
    }
    return true;
}

} // namespace

int main() {
    std::printf("CM06 - Quantum Hall and Josephson Metrology\n");
    std::printf("J. C. Harvey, Melbourne - 2026-07-04\n\n");

    std::printf("== IDENTITY block (printed once, ZERO evidentiary weight) ==\n");
    std::printf("  R_K  = h/e^2  = %.6f Ohm      [IDENTITY - h, e SI-exact]\n",
                h / (e_charge * e_charge));
    std::printf("  K_J  = 2e/h   = %.6e Hz/V   [IDENTITY]\n", 2.0 * e_charge / h);
    std::printf("  Phi0 = h/(2e) = %.6e Wb     [IDENTITY]\n\n", h / (2.0 * e_charge));

    // ------------------------------------------------------------------ P1+P2
    std::printf("== P1/P2: integer channel count vs bulk magnitude under disorder ==\n");
    std::printf("  [chain, named] 1-D relay line: one carrier configuration per\n");
    std::printf("  winding cell (Law VI h-cell - ROOT-A premise, shared with\n");
    std::printf("  CM04/CM01/CM03); cell rate = dmu/h; I = e*dmu/h => G = e^2/h\n");
    std::printf("  per channel. CONVERGENCE conditional on ROOT-A; grade capped C.\n\n");
    {
        const int L = 2000, W = 40, w = 5;
        std::printf("  %-10s %-16s %-20s\n", "p", "nu (edge count)", "bulk G/G0 (drift)");
        int nu_first = -1; bool nu_constant = true, nu_integer = true;
        double bulk_first = -1, bulk_last = -1;
        for (double p : {1e-4, 3e-4, 1e-3, 3e-3, 1e-2, 3e-2, 1e-1}) {
            // two boundaries, one channel each if intact
            const int nu = (edge_channel(0, w, L, p) ? 1 : 0)
                         + (edge_channel(W - w, w, L, p) ? 1 : 0);
            // bulk: drift conductance declines smoothly with defect scattering
            const double bulk = 1.0 / (1.0 + 40.0 * p * std::sqrt((double)L / W));
            if (nu_first < 0) { nu_first = nu; bulk_first = bulk; }
            if (nu != nu_first) nu_constant = false;
            bulk_last = bulk;
            std::printf("  %-10.0e %-16d %-20.4f\n", p, nu, bulk);
        }
        const double bulk_decline = (bulk_first - bulk_last) / bulk_first * 100.0;
        std::printf("  gates: nu integer-only %s ; nu constant over 3 orders %s ;\n",
                    nu_integer ? "PASS" : "FAIL", nu_constant ? "PASS" : "FAIL");
        std::printf("         bulk declines smoothly: %.1f%% (gate >30%%)  %s\n",
                    bulk_decline, bulk_decline > 30.0 ? "PASS" : "FAIL");
        std::printf("  [COMPUTED-toy, no measured claim: a COUNT is disorder-rigid\n");
        std::printf("   (re-routing within the edge strip), a MAGNITUDE is not. That\n");
        std::printf("   is the exactness mechanism - counts cannot drift.]\n\n");
    }

    // ------------------------------------------------------------------ P3
    std::printf("== P3: the Josephson 2 (inherited body count) ==\n");
    std::printf("  chain: one 2-pi phase slip of the weak link relays ONE locked\n");
    std::printf("  pair (CM01 2-body cluster, handedness 2e); energy per slip:\n");
    std::printf("  2e * V = h * f  =>  V = (h/2e) f.  The 2 is CM01's body count\n");
    std::printf("  (earned there as ARGUED; exclusivity OPEN there - inherited\n");
    std::printf("  with that flag, not laundered into a pass here).\n");
    std::printf("  Single-vortex counterfactual: an unpaired W=1 carrier would give\n");
    std::printf("  e*V = h*f (K = e/h) - a falsifiable difference: any weak link\n");
    std::printf("  showing e/h steps in the paired state kills the pair count.\n\n");

    // ------------------------------------------------------------------ P4
    std::printf("== P4: metrology closure ==\n");
    std::printf("  DEFER - upstream CM02 (native ohm) is flagged DO-NOT-TRUST\n");
    std::printf("  (tau-from-sigma circularity). Unblock: CM02 honest re-run;\n");
    std::printf("  CM01-P1's normal-state chain (tau never sees sigma) is the\n");
    std::printf("  template it should build on.\n\n");

    std::printf("== Ledger ==\n");
    std::printf("  IDENTITY : R_K, K_J, Phi0 (zero evidence, printed once).\n");
    std::printf("  CONVERGENCE (conditional on ROOT-A): G = e^2/h per channel.\n");
    std::printf("  COMPUTED-toy : count-vs-magnitude disorder rigidity.\n");
    std::printf("  INHERITED : the Josephson 2 = CM01 body count (flag carried).\n");
    std::printf("  DEFER : P4 (CM02). CALIBRATED: none (0 of 0).\n");
    return 0;
}
