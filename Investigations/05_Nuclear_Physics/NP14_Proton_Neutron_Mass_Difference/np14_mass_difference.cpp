// ═══════════════════════════════════════════════════════════════════════
// NP14 — Proton-Neutron Mass Difference from Topology
// Author: J. C. Harvey, Melbourne. Date: 2026-07-03.
// Premise (2026-07-03 PROMPT note): neutron = proton + one internal
// electron (NP17), NOT a bare uncharged W=3 trefoil.
// Gates pre-committed in RUN_LOG.md BEFORE this file was written:
//   G1 (primary): |S_native - S_meas|/S_meas <= 15%, with
//       S_native = (1/2)(z-1) m_e c^2, z = r_e/R_p  (NP20 seat route)
//   G2 (legacy Hyp A, record only): E_em = alpha*hbar*c/R_p vs dm;
//       no admissible geometric fraction declared -> cannot pass.
//   G3 (sign): heavier-not-lighter must follow without a sign choice.
// No knobs. Constants from sdt/laws.hpp only.
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>

int main() {
    using namespace sdt::laws;
    using namespace sdt::laws::measured;

    std::printf("NP14 — Proton-Neutron Mass Difference (J. C. Harvey, 2026-07-03)\n");
    std::printf("Engine: sdt/laws.hpp | premise: neutron = proton + internal electron (NP17)\n");
    std::printf("================================================================\n\n");

    // ---------- Phase 0: sanity — the measured ledger (OBSERVED anchors) ----------
    const double mp_MeV = m_p * c * c / MeV_to_J;   // proton rest energy
    const double mn_MeV = m_n * c * c / MeV_to_J;   // neutron rest energy
    const double me_MeV = m_e * c * c / MeV_to_J;   // electron rest energy
    const double dm_MeV = mn_MeV - mp_MeV;          // the target difference

    std::printf("[P0] OBSERVED anchors (CODATA via measured::)\n");
    std::printf("     m_p c^2            = %12.6f MeV\n", mp_MeV);
    std::printf("     m_n c^2            = %12.6f MeV\n", mn_MeV);
    std::printf("     m_e c^2            = %12.6f MeV\n", me_MeV);
    std::printf("     dm = (m_n-m_p)c^2  = %12.6f MeV   (target)\n\n", dm_MeV);

    const bool p0_ok = std::fabs(dm_MeV - 1.29333) < 0.001;
    std::printf("     P0 sanity (dm ~ 1.2933 MeV): %s\n\n", p0_ok ? "PASS" : "FAIL");

    // ---------- Phase 1: NP17 ledger decomposition ----------
    // dm = m_e c^2 (STRUCTURAL: the neutron contains an electron)
    //    + S      (seat surplus; algebraically identical to Q_beta -> the
    //              *decomposition* is IDENTITY; only S_native below predicts)
    const double S_meas = dm_MeV - me_MeV;
    std::printf("[P1] NP17 ledger:  dm = m_e c^2 + S\n");
    std::printf("     m_e c^2 (STRUCTURAL, by construction) = %10.6f MeV\n", me_MeV);
    std::printf("     S_meas = dm - m_e c^2 (IDENTITY = Q_beta) = %10.6f MeV\n\n", S_meas);

    // ---------- Phase 2: native seat surplus (the committed route) ----------
    // z = r_e/R_p is the seat depth (NP20: v_bound = c*sqrt(z) = 1.830c,
    // independently matched by traction c/k_proton_surface to 0.006%).
    const double z      = r_e / R_p;                         // DERIVED (engine lengths)
    const double v_seat = std::sqrt(z);                      // [c] seat speed
    const double v_trac = 1.0 / bridge::k_proton_surface;    // [c] traction cross-check
    const double S_native = 0.5 * (z - 1.0) * me_MeV;        // committed formula
    const double g1_err = (S_native - S_meas) / S_meas * 100.0;

    std::printf("[P2] Native seat surplus (committed: S = (1/2)(z-1) m_e c^2)\n");
    std::printf("     z = r_e/R_p        = %10.5f   (dimensionless depth)\n", z);
    std::printf("     v_seat = c sqrt(z) = %10.5f c\n", v_seat);
    std::printf("     traction check c/k_proton_surface = %.5f c  (agree %.3f%%)\n",
                v_trac, (v_seat - v_trac) / v_trac * 100.0);
    std::printf("     S_native           = %10.6f MeV   vs S_meas = %.6f MeV\n", S_native, S_meas);
    std::printf("     GATE G1 (<=15%%):    error = %+.2f%%  -> %s\n\n",
                g1_err, std::fabs(g1_err) <= 15.0 ? "PASS" : "FAIL -> OPEN");

    // Composite (DILUTED — informational only, per RUN_LOG; not a gate)
    const double dm_pred = me_MeV + S_native;
    std::printf("     composite dm_pred = m_e + S_native = %.6f MeV (err %+.2f%%)\n", dm_pred,
                (dm_pred - dm_MeV) / dm_MeV * 100.0);
    std::printf("     ^ DILUTED: contains the by-construction m_e piece. Informational only.\n");
    std::printf("     knob that WOULD be needed on S: x%.4f  (CALIBRATED(1) — refused)\n\n",
                S_meas / S_native);

    // ---------- Phase 3: legacy Hypothesis A (record only; PREMISE-DEAD) ----------
    const double E_em = coulomb_identity::k_e_e2 / R_p / MeV_to_J;  // alpha*hbar*c / R_p
    std::printf("[P3] Legacy Hyp A (uncharged-trefoil premise — PREMISE-DEAD under NP17)\n");
    std::printf("     E_em = alpha hbar c / R_p = %10.6f MeV  (vs dm: %+.1f%%)\n",
                E_em, (E_em - dm_MeV) / dm_MeV * 100.0);
    std::printf("     required fraction dm/E_em = %.4f — NO prior geometric derivation\n",
                dm_MeV / E_em);
    std::printf("     declared in RUN_LOG -> inadmissible; proximity to 3/4 etc. is\n");
    std::printf("     unexplained numerology. GATE G2: NO PASS. Hypothesis A: KILLED\n");
    std::printf("     (premise superseded by NP17; no derived fraction).\n\n");

    // ---------- Phase 4: sign / mechanism (G3) ----------
    std::printf("[P4] GATE G3 — why HEAVIER, not lighter (qualitative)\n");
    std::printf("     (i)  containment: neutron = p + e -> +m_e c^2, sign forced (+)\n");
    std::printf("     (ii) seat surplus: z > 1 (r_e > R_p) -> (z-1) > 0 -> S_native > 0,\n");
    std::printf("          sign forced (+) by the geometry (no sense/sign knob used).\n");
    std::printf("     The seat is ABOVE the free p+e ground -> beta decay is downhill,\n");
    std::printf("     releasing exactly S (= Q_beta). Sign: EARNED. Magnitude: OWED.\n\n");

    // ---------- Verdict ----------
    std::printf("================================================================\n");
    std::printf("VERDICT (numeric):\n");
    std::printf("  G1 surplus magnitude : %+.2f%% vs +/-15%%  -> %s\n", g1_err,
                std::fabs(g1_err) <= 15.0 ? "PASS" : "FAIL -> OPEN (root: NP20/NP19/NP21)");
    std::printf("  G2 legacy Hyp A      : KILLED (premise-dead + no derived fraction)\n");
    std::printf("  G3 sign/mechanism    : EARNED (both signs forced positive)\n");
    std::printf("  Composite dm         : %.4f vs %.4f MeV (%+.2f%%) — DILUTED, not a pass\n",
                dm_pred, dm_MeV, (dm_pred - dm_MeV) / dm_MeV * 100.0);
    return 0;
}
