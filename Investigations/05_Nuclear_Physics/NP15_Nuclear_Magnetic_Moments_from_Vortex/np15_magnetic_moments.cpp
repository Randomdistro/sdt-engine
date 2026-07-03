// ═══════════════════════════════════════════════════════════════════════
// NP15 — Nuclear Magnetic Moments from Vortex Geometry
// Author: J. C. Harvey, Melbourne. Date: 2026-07-03.
// Candidates C1-C5 and all gates pre-committed in RUN_LOG.md BEFORE this
// file was written. mu_N is a BORROWED comparison unit (flagged).
// mu_neutron: NOT re-derived (NP20 OPEN inherited; premise NP17).
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>

namespace {
    double pct(double pred, double meas) { return (pred - meas) / std::fabs(meas) * 100.0; }
    const char* gate5(double pred, double meas) {
        return std::fabs(pct(pred, meas)) <= 5.0 ? "PASS(5%)" : "FAIL(5%)";
    }
}

int main() {
    using namespace sdt::laws;
    using namespace sdt::laws::measured;
    namespace topo = sdt::laws::law_VI::topology;
    namespace wind = sdt::laws::law_VI::winding;

    std::printf("NP15 — Nuclear Magnetic Moments from Vortex Geometry (J. C. Harvey, 2026-07-03)\n");
    std::printf("Engine: sdt/laws.hpp | unit mu_N = e hbar/2m_p is BORROWED (comparison only)\n");
    std::printf("=================================================================\n\n");

    // ---------- Phase 0: engine anchors + mode speeds ----------
    const double g_p = wind::g_proton;               // R_p m_p c / hbar ~ 4.0008
    const double vT  = topo::v_toroidal(2, 3) / c;   // sqrt(2/5)
    const double vP  = topo::v_poloidal(2, 3) / c;   // sqrt(3/5)
    std::printf("[P0] g_proton = R_p m_p c/hbar = %.5f  (W+1 rim identity)\n", g_p);
    std::printf("     (2,3) trefoil: v_T = %.5f c, v_P = %.5f c  (PPT01, class A)\n", vT, vP);
    std::printf("     anchors (OBSERVED, engine): mu_p=%+.6f mu_n=%+.6f mu_d=%+.6f\n",
                mu_P, mu_N, mu_D);
    std::printf("                                 mu_t=%+.3f  mu_h=%+.3f  mu_a=%.1f\n\n",
                mu_T, mu_He3, mu_alpha);

    // ---------- Phase 1: mu_p candidates (committed C1-C5) ----------
    const double C1 = g_p;                                        // rim at c
    const double C2 = g_p * vT;                                   // toroidal loop at R_p
    const double C3 = g_p * vP;                                   // poloidal variant
    const double Rmaj_frac = std::sqrt(1.5) / (1.0 + std::sqrt(1.5)); // R/(R+a), R/a=sqrt(3/2)
    const double C4 = g_p * vT * Rmaj_frac;                       // toroidal loop at R_major
    const double C5 = g_p * std::sqrt(vT * vP);                   // FLAGGED-POST-HOC

    std::printf("[P1] mu_p candidates (target %+.6f mu_N, gate 5%%, committed a priori)\n", mu_P);
    std::printf("     C1 rim (g_p)              = %8.4f  (%+7.2f%%)  %s\n", C1, pct(C1, mu_P), gate5(C1, mu_P));
    std::printf("     C2 toroidal @R_p          = %8.4f  (%+7.2f%%)  %s\n", C2, pct(C2, mu_P), gate5(C2, mu_P));
    std::printf("     C3 poloidal @R_p          = %8.4f  (%+7.2f%%)  %s\n", C3, pct(C3, mu_P), gate5(C3, mu_P));
    std::printf("     C4 toroidal @R_major      = %8.4f  (%+7.2f%%)  %s\n", C4, pct(C4, mu_P), gate5(C4, mu_P));
    std::printf("     C5 geo-mean [POST-HOC]    = %8.4f  (%+7.2f%%)  [no-PASS-allowed: numerology ledger only]\n",
                C5, pct(C5, mu_P));
    const bool anyPass = std::fabs(pct(C2, mu_P)) <= 5.0 || std::fabs(pct(C3, mu_P)) <= 5.0
                      || std::fabs(pct(C1, mu_P)) <= 5.0 || std::fabs(pct(C4, mu_P)) <= 5.0;
    std::printf("     -> derivable candidates C1-C4: %s\n", anyPass ? "at least one PASS" : "NONE pass -> mu_p OPEN");
    std::printf("     -> C2/C3 bracket the target (%+.2f%% / %+.2f%%): the trefoil modes\n",
                pct(C2, mu_P), pct(C3, mu_P));
    std::printf("        straddle mu_p but no committed single mode lands it.\n");
    std::printf("     -> C5 look-elsewhere ledger: 5 combinations tried at design time;\n");
    std::printf("        geo-mean lands %+.2f%% with NO derivation -> logged [OPEN], not sold.\n\n", pct(C5, mu_P));

    // ---------- Phase 2: mu_n (inherited, NOT re-fished) ----------
    std::printf("[P2] mu_n: PROMPT's uncharged-trefoil route PREMISE-DEAD (NP17).\n");
    std::printf("     NP20 executed the NP17 route: magnitude=IDENTITY, sign assumed -> OPEN.\n");
    std::printf("     NP15 inherits OPEN; named debt = native flux composition + sign dynamics.\n");
    std::printf("     No new mu_n number is computed here (re-fishing forbidden by RUN_LOG).\n\n");

    // ---------- Phase 3: mu_n / mu_p ratio ----------
    const double ratio = mu_N / mu_P;
    std::printf("[P3] mu_n/mu_p = %+.5f (measured). -2/3 = %+.5f (off %+.2f%%).\n",
                ratio, -2.0 / 3.0, pct(-2.0 / 3.0, ratio));
    std::printf("     No SDT derivation of -2/3 exists (SU(6) is the rival's machinery,\n");
    std::printf("     inadmissible). Class: OPEN — proximity is unexplained, not evidence.\n\n");

    // ---------- Phase 4: composites (grammar block rules, committed) ----------
    std::printf("[P4] Composites — grammar block rules (gate 5%% blind; DEGENERACY DECLARED:\n");
    std::printf("     rules coincide with the rival's impulse approximation / Schmidt limits)\n");
    struct Row { const char* name; const char* rule; double pred; double meas; const char* src; };
    const Row rows[] = {
        {"d  (p+n aligned)",   "mu_p + mu_n", mu_P + mu_N, mu_D,      "engine"},
        {"t  (p, nn paired)",  "mu_p",        mu_P,        mu_T,      "engine"},
        {"h  (pp paired, n)",  "mu_n",        mu_N,        mu_He3,    "engine"},
        {"alpha (all paired)", "0",           0.0,         mu_alpha,  "engine"},
        {"Li-7 (a+t, a silent)","mu_p",       mu_P,        3.256427,  "Stone2019 typed anchor"},
        {"Be-9 (2a+n, a silent)","mu_n",      mu_N,       -1.1778,    "Stone2019 typed anchor"},
    };
    for (const auto& r : rows) {
        if (r.meas == 0.0 && r.pred == 0.0) {
            std::printf("     %-22s = %+8.4f  meas %+8.4f  (exact)    PASS — but DEGENERATE (spin-0: every model gives 0)  [%s]\n",
                        r.name, r.pred, r.meas, r.src);
        } else {
            std::printf("     %-22s = %+8.4f  meas %+8.4f  (%+7.2f%%) %s  [%s]\n",
                        r.name, r.pred, r.meas, pct(r.pred, r.meas), gate5(r.pred, r.meas), r.src);
        }
    }
    std::printf("\n");

    // ---------- Verdict ----------
    std::printf("=================================================================\n");
    std::printf("VERDICT (numeric):\n");
    std::printf("  mu_p from trefoil : OPEN — C1-C4 all FAIL 5%%; modes bracket (%+.1f%%/%+.1f%%)\n",
                pct(C2, mu_P), pct(C3, mu_P));
    std::printf("  C5 geo-mean       : %+.2f%% — [OPEN] numerology ledger, no derivation, NOT a pass\n", pct(C5, mu_P));
    std::printf("  mu_n              : OPEN (inherited NP20: IDENTITY magnitude, assumed sign)\n");
    std::printf("  mu_n/mu_p = -2/3? : OPEN (no SDT derivation; proximity unexplained)\n");
    std::printf("  d                 : %+.2f%% %s — DEGENERATE (same as rival's additivity)\n",
                pct(mu_P + mu_N, mu_D), gate5(mu_P + mu_N, mu_D));
    std::printf("  t / h             : %+.2f%% / %+.2f%% both FAIL(5%%) — block rule under-structures\n",
                pct(mu_P, mu_T), pct(mu_N, mu_He3));
    std::printf("  Li-7 / Be-9       : %+.2f%% / %+.2f%% — grammar extension FAILS\n",
                pct(mu_P, 3.256427), pct(mu_N, -1.1778));
    std::printf("  alpha = 0         : consistent (paired cancellation) — DEGENERATE\n");
    return 0;
}
