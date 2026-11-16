// ═══════════════════════════════════════════════════════════════════════
// NP08 — Triple-Alpha Rate from Geometric Packing (Hoyle state target)
// Author: J. C. Harvey, Melbourne. Date: 2026-07-03.
// Premise corrected per 2026-07-03 PROMPT note: occlusion route (NP09)
// FAILED -97.3%; linear volume price killed (FLM12-D1). Only paid
// mechanism = NP17 shared-electron Coulomb well (alpha/heavy PENDING).
// All phases + decision rules pre-committed in RUN_LOG.md.
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <sdt/nuclear.hpp>
#include <cmath>
#include <cstdio>

int main() {
    using namespace sdt::laws;
    using namespace sdt::laws::measured;

    // Typed OBSERVED anchors (AME2020, flagged in RUN_LOG)
    const double B_d   = 2.224573;   // MeV (engine has 2.224; AME precision used)
    const double B_a   = 28.295674;  // MeV
    const double B_Be8 = 56.49951;   // MeV
    const double B_C12 = 92.161753;  // MeV
    const double E_Hoyle = 7.65407;  // MeV above C-12 g.s.

    std::printf("NP08 — Triple-Alpha / Hoyle State from Geometric Packing (J. C. Harvey, 2026-07-03)\n");
    std::printf("Engine: sdt/laws.hpp + sdt/nuclear.hpp | anchors AME2020 (OBSERVED, flagged)\n");
    std::printf("====================================================================\n\n");

    // ---------- P0: constitutional grammar (exact integers) ----------
    constexpr auto gBe8 = sdt::nuclear::alpha_grammar(4, 8);
    constexpr auto gC12 = sdt::nuclear::alpha_grammar(6, 12);
    std::printf("[P0] Constitutional grammar  n_t = A-2Z, n_d = 3Z-A-2\n");
    std::printf("     Be-8 (Z=4,A=8):  alpha + %d d + %d t   (valid=%d)\n", gBe8.n_d, gBe8.n_t, (int)gBe8.valid);
    std::printf("     C-12 (Z=6,A=12): alpha + %d d + %d t   (valid=%d)\n", gC12.n_d, gC12.n_t, (int)gC12.valid);
    std::printf("     PREMISE CHECK: PROMPT asserted 'Be-8 = 2a + 0d (no scaffold bonds)'.\n");
    std::printf("     The constitutional formulas give Be-8 = alpha + 2d. The PROMPT text\n");
    std::printf("     CONTRADICTS the grammar it cites -> PROMPT premise CORRECTED here.\n\n");

    // ---------- P1: grammar ledger (IDENTITY-class bookkeeping, labelled) ----------
    const double blocks_Be8 = B_a + gBe8.n_d * B_d;
    const double blocks_C12 = B_a + gC12.n_d * B_d;
    const double scaf_Be8 = B_Be8 - blocks_Be8;
    const double scaf_C12 = B_C12 - blocks_C12;
    const double Q_3a  = B_C12 - 3.0 * B_a;      // 3a -> C-12
    const double dBe8  = B_Be8 - 2.0 * B_a;      // Be-8 vs 2a (negative = unbound)

    std::printf("[P1] Grammar ledger (uses measured BEs -> IDENTITY-class bookkeeping,\n");
    std::printf("     NOT predictions; labelled per RUN_LOG)\n");
    std::printf("     Be-8: B=%9.4f  blocks(a+2d)=%8.4f  scaffold required = %8.4f MeV (%.2f/d)\n",
                B_Be8, blocks_Be8, scaf_Be8, scaf_Be8 / gBe8.n_d);
    std::printf("     C-12: B=%9.4f  blocks(a+4d)=%8.4f  scaffold required = %8.4f MeV (%.2f/d)\n",
                B_C12, blocks_C12, scaf_C12, scaf_C12 / gC12.n_d);
    std::printf("     Q(3a->C12) = B(C12)-3B(a) = %8.4f MeV  (PROMPT: 7.275 — check ok)\n", Q_3a);
    std::printf("     Be-8 vs 2a = %+8.4f MeV -> a+2d packing is metastable against 2a by 0.092\n", dBe8);
    std::printf("     Rearrangement audit (exact algebra): dissolve 2a -> 4d costs %8.4f MeV,\n",
                2.0 * B_a - 4.0 * B_d);
    std::printf("     scaffold formation repays %8.4f MeV, net %+8.4f = -Q  (identity check)\n\n",
                scaf_C12, (2.0 * B_a - 4.0 * B_d) - scaf_C12);

    // ---------- P2: native attempt at the Hoyle target (gate 20%) ----------
    // Committed geometry (RUN_LOG): 4 d at tetrahedron vertices, alpha at centre;
    // centre-to-vertex r_cv = R_He + D/2, D = 2R_p + R_p/3 (NP17); edge s = r_cv*sqrt(8/3).
    const double fm    = 1.0e-15;
    const double aHc   = coulomb_identity::k_e_e2 / MeV_to_J / fm;  // MeV*fm = 1.44
    const double D_np17 = (2.0 * R_p + R_p / 3.0) / fm;             // fm
    const double r_cv  = R_He / fm + D_np17 / 2.0;                  // fm
    const double s_dd  = r_cv * std::sqrt(8.0 / 3.0);               // fm
    // Point-Coulomb repulsion ledger of the configuration (computable knob-free):
    const double E_rep = 6.0 * (1.0 * 1.0) * aHc / s_dd             // 6 d-d edges (+1,+1)
                       + 4.0 * (2.0 * 1.0) * aHc / r_cv;            // 4 a-d spokes (+2,+1)

    std::printf("[P2] Native tetrahedral-closure attempt (committed geometry, gate 20%%)\n");
    std::printf("     alpha-hbar-c = %.4f MeV*fm | D(NP17) = %.4f fm | r_cv = %.4f fm | s_dd = %.4f fm\n",
                aHc, D_np17, r_cv, s_dd);
    std::printf("     Point-Coulomb REPULSION ledger of a+4d closure = %.3f MeV (knob-free)\n", E_rep);
    std::printf("     ATTRACTIVE side (shared-electron wells d<->a core): electron count and\n");
    std::printf("     placement are NP17-PENDING (alpha under-binds ~6x on pure electrostatics).\n");
    std::printf("     Decision rule (RUN_LOG): no signed closure energy can be written knob-free\n");
    std::printf("     -> P2 = DEFERRED (dependency: NP17-PENDING tetrahedral-lock magnitude).\n");
    std::printf("     NO number is scored against the 7.654 MeV gate. Inventing electron\n");
    std::printf("     placements to reach it is forbidden.\n\n");

    // ---------- P3: stability directions (sign-only, ledger-consistency) ----------
    std::printf("[P3] Stability directions from the ledger (sign-only; measured BEs)\n");
    std::printf("     (i)  Be-8 -> 2a: %+.4f MeV -> downhill to 2a  (Be-8 decays, tau~1e-16 s)  OK\n", -dBe8);
    std::printf("     (ii) 3a -> C-12 (a+4d): %+.4f MeV -> downhill to a+4d (C-12 stable)      OK\n", Q_3a);
    std::printf("     Both directions come out of the packing comparison with no sign choice.\n");
    std::printf("     Hoyle = 7.654 MeV = Q (%.4f) + barrier %.4f MeV above the 3a threshold;\n",
                Q_3a, E_Hoyle - Q_3a);
    std::printf("     the 0.379 MeV closure barrier is the quantity SDT OWES (geometric\n");
    std::printf("     threshold of tetrahedral closure) — un-derived until NP17's lock term.\n\n");

    // ---------- Verdict ----------
    std::printf("====================================================================\n");
    std::printf("VERDICT (numeric):\n");
    std::printf("  P0 grammar        : Be-8 = a+2d, C-12 = a+4d (exact); PROMPT's 'Be-8 = 2a+0d'\n");
    std::printf("                      premise CONTRADICTS the constitutional grammar -> corrected\n");
    std::printf("  P1 ledger         : scaffold required: Be-8 23.75 MeV, C-12 54.97 MeV (IDENTITY)\n");
    std::printf("  P2 Hoyle 7.654    : DEFERRED — dependency NP17-PENDING (no knob-free attractive\n");
    std::printf("                      side; repulsion ledger alone = %.2f MeV)\n", E_rep);
    std::printf("  P3 directions     : Be-8 unstable / C-12 stable both downhill in the ledger —\n");
    std::printf("                      consistency, not prediction (measured BEs consumed)\n");
    std::printf("  Barrier owed      : %.3f MeV above 3a threshold (the actual Hoyle content)\n", E_Hoyle - Q_3a);
    return 0;
}
