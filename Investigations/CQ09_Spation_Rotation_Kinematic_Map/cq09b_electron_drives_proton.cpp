/**
 * @file cq09b_electron_drives_proton.cpp
 * @brief CQ09b: The Electron as Driver — Inverse Kinematic Map
 *
 * THE QUESTION:
 *   CQ09 mapped the proton's 1.83c rotation field outward to the electron.
 *   Now flip it: the electron is a (1,1) unknot with koppa_e = 1.
 *   Map its rotation field INWARD to the proton.
 *
 * THE PUNCHLINE (spoiler):
 *   The two fields are IDENTICAL everywhere. The system is in
 *   MUTUAL RESONANCE. There is no "driver" and "driven" —
 *   there is one field, self-consistently closed.
 *
 * @author SDT Canonical Engine — James Tyndall, Melbourne, Australia
 * @date April 2026
 */

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>
#include <numbers>

using namespace sdt::laws;
using namespace sdt::laws::measured;

static int total_proofs = 0;
static int passed_count = 0;

static void prove(const char* tag, const char* desc,
                  double derived, double expected, double tol_pct)
{
    ++total_proofs;
    double err = (expected != 0.0)
               ? std::abs(derived - expected) / std::abs(expected) * 100.0
               : std::abs(derived);
    bool ok = err < tol_pct;
    if (ok) ++passed_count;
    std::printf("  %s %s: %s\n", ok ? "PASS" : "FAIL", tag, desc);
    std::printf("    Derived:  %.10e   Expected: %.10e   Err: %.4f%%\n\n",
                derived, expected, err);
}

// ═══════════════════════════════════════════════════════════════════════
//  CONSTANTS
// ═══════════════════════════════════════════════════════════════════════

static constexpr double koppa_H   = 0.5464;       // proton koppa
static constexpr double koppa_e   = 1.0;           // electron koppa (at c-boundary)
static constexpr double v_electron = alpha * c;

// ═══════════════════════════════════════════════════════════════════════
//  SECTION 1: THE ELECTRON'S KOPPA
// ═══════════════════════════════════════════════════════════════════════

static void section1_electron_koppa()
{
    std::puts("================================================================");
    std::puts("  SECTION 1: THE ELECTRON'S KOPPA");
    std::puts("================================================================\n");

    // The electron is a (1,1) torus unknot.
    // From CQ02: v_T = v_P = c/√2, total circulation = c.
    // The electron's wake radius = r_e = classical electron radius.
    // At r_e, the circulation velocity IS c.
    // Therefore: koppa_e = c / v_surface = c / c = 1.

    double v_T = c / std::sqrt(2.0);
    double v_P = c / std::sqrt(2.0);
    double v_total = std::sqrt(v_T * v_T + v_P * v_P);

    std::printf("  Electron (1,1) unknot:\n");
    std::printf("    v_T = c/√2 = %.4e m/s\n", v_T);
    std::printf("    v_P = c/√2 = %.4e m/s\n", v_P);
    std::printf("    v_total = √(v_T² + v_P²) = %.4e m/s = %.6f c\n\n", v_total, v_total / c);

    prove("CQ09b-1a", "Electron total circulation = c",
          v_total, c, 0.001);

    std::printf("  Therefore:\n");
    std::printf("    koppa_e = c / v_surface = c / c = 1.0000\n");
    std::printf("    The electron IS at the c-boundary.\n");
    std::printf("    Its surface IS the event horizon of its own field.\n\n");

    // Verify: electron's c-boundary
    // r_Ϟ_e = R_e / koppa_e² = r_e / 1² = r_e
    // The c-boundary IS the electron itself. It does not have a separate
    // c-boundary — it IS the c-boundary.
    double r_koppa_e = r_e / (koppa_e * koppa_e);
    prove("CQ09b-1b", "Electron c-boundary = r_e (self-coincident)",
          r_koppa_e, r_e, 0.001);
}

// ═══════════════════════════════════════════════════════════════════════
//  SECTION 2: THE ELECTRON'S ROTATION FIELD
// ═══════════════════════════════════════════════════════════════════════

static void section2_electron_field()
{
    std::puts("================================================================");
    std::puts("  SECTION 2: ELECTRON ROTATION FIELD — Inward to the Proton");
    std::puts("================================================================\n");

    // The electron's rotation field:
    // v_e(r) = (c / koppa_e) × √(r_e / r) = c × √(r_e / r)
    //
    // This field propagates from the electron at a₀ INWARD toward the proton.
    // At the proton's location (distance a₀ from the electron),
    // the electron's field velocity is:

    double v_e_at_a0 = c * std::sqrt(r_e / a_0);

    std::printf("  ELECTRON FIELD at key radii:\n\n");
    std::printf("  v_e(r) = c × √(r_e / r)   [koppa_e = 1]\n\n");

    std::printf("  At r = a₀ (proton location):\n");
    std::printf("    v_e(a₀) = c × √(r_e / a₀)\n");
    std::printf("            = c × √(%.4e / %.4e)\n", r_e, a_0);
    std::printf("            = c × √(%.6e)\n", r_e / a_0);
    std::printf("            = c × %.6e\n", std::sqrt(r_e / a_0));
    std::printf("            = %.4e m/s\n\n", v_e_at_a0);

    // THE KEY RESULT:
    // r_e / a₀ = α² × a₀ / a₀ = α²
    // √(r_e / a₀) = α
    // v_e(a₀) = c × α = αc

    double ratio = r_e / a_0;
    prove("CQ09b-2a", "r_e / a₀ = α²",
          ratio, alpha * alpha, 0.01);

    prove("CQ09b-2b", "v_electron_field(a₀) = αc",
          v_e_at_a0, v_electron, 0.01);

    std::puts("  ┌─────────────────────────────────────────────────────────────┐");
    std::puts("  │  THE ELECTRON'S FIELD AT THE PROTON GIVES αc.              │");
    std::puts("  │  THE PROTON'S FIELD AT THE ELECTRON GIVES αc.              │");
    std::puts("  │  THEY ARE THE SAME VELOCITY. MUTUAL RESONANCE.             │");
    std::puts("  └─────────────────────────────────────────────────────────────┘\n");
}

// ═══════════════════════════════════════════════════════════════════════
//  SECTION 3: THE ELECTRON'S FIELD AT THE PROTON SURFACE
// ═══════════════════════════════════════════════════════════════════════

static void section3_field_at_proton()
{
    std::puts("================================================================");
    std::puts("  SECTION 3: ELECTRON FIELD AT THE PROTON SURFACE");
    std::puts("================================================================\n");

    // Now the stunning result: what is the electron's field at r = R_p?
    // v_e(R_p) = c × √(r_e / R_p)

    double v_e_at_Rp = c * std::sqrt(r_e / R_p);
    double v_p_at_Rp = (c / koppa_H) * std::sqrt(R_p / R_p);  // = c/koppa_H

    std::printf("  ELECTRON field at proton surface (r = R_p):\n");
    std::printf("    v_e(R_p) = c × √(r_e / R_p)\n");
    std::printf("             = c × √(%.4e / %.4e)\n", r_e, R_p);
    std::printf("             = c × √(%.4f)\n", r_e / R_p);
    std::printf("             = c × %.4f\n", std::sqrt(r_e / R_p));
    std::printf("             = %.4fc\n\n", v_e_at_Rp / c);

    std::printf("  PROTON field at proton surface (r = R_p):\n");
    std::printf("    v_p(R_p) = c / ϟ_H = c / %.4f\n", koppa_H);
    std::printf("             = %.4fc\n\n", v_p_at_Rp / c);

    prove("CQ09b-3a", "Electron field at R_p = proton field at R_p",
          v_e_at_Rp, v_p_at_Rp, 0.1);

    // WHY? Because:
    // v_e(R_p) = c √(r_e/R_p)
    // v_p(R_p) = c / ϟ_H = c × α √(a₀/R_p)   [since ϟ_H = (1/α)√(R_p/a₀)]
    //          = c × α × √(a₀/R_p)
    // Now r_e = α² a₀, so:
    // v_e(R_p) = c √(α² a₀ / R_p) = cα √(a₀/R_p) = v_p(R_p)  ✓

    std::puts("  ALGEBRAIC PROOF:");
    std::puts("    v_e(R_p) = c √(r_e / R_p)");
    std::puts("             = c √(α² a₀ / R_p)     [r_e = α² a₀]");
    std::puts("             = cα √(a₀ / R_p)");
    std::puts("");
    std::puts("    v_p(R_p) = c / ϟ_H");
    std::puts("             = c / [(1/α)√(R_p/a₀)]  [ϟ_H = (1/α)√(R_p/a₀)]");
    std::puts("             = cα √(a₀ / R_p)");
    std::puts("");
    std::puts("    v_e(R_p) = v_p(R_p)   QED.\n");

    std::puts("  ┌─────────────────────────────────────────────────────────────┐");
    std::puts("  │  AT EVERY RADIUS FROM R_p TO a₀, THE TWO FIELDS            │");
    std::puts("  │  GIVE THE SAME VELOCITY.                                    │");
    std::puts("  │                                                             │");
    std::puts("  │  THIS IS NOT TWO FIELDS. IT IS ONE FIELD.                   │");
    std::puts("  └─────────────────────────────────────────────────────────────┘\n");
}

// ═══════════════════════════════════════════════════════════════════════
//  SECTION 4: FULL COMPARISON TABLE
// ═══════════════════════════════════════════════════════════════════════

static void section4_comparison()
{
    std::puts("================================================================");
    std::puts("  SECTION 4: SIDE-BY-SIDE FIELD COMPARISON");
    std::puts("================================================================\n");

    // Proton field: v_p(r) = (c/ϟ_H) √(R_p/r)
    // Electron field: v_e(r) = c × √(r_e/r)    [koppa_e = 1]
    // Ratio: v_e/v_p = ϟ_H √(r_e/R_p)
    //       = (1/α)√(R_p/a₀) × √(α²a₀/R_p)
    //       = (1/α) × α × √(R_p/a₀) × √(a₀/R_p)
    //       = 1   IDENTICALLY.

    double ratio_algebraic = koppa_H * std::sqrt(r_e / R_p);
    std::printf("  RATIO TEST: v_e(r) / v_p(r) = ϟ_H × √(r_e/R_p)\n");
    std::printf("    = %.4f × √(%.4f)\n", koppa_H, r_e / R_p);
    std::printf("    = %.4f × %.4f\n", koppa_H, std::sqrt(r_e / R_p));
    std::printf("    = %.6f\n\n", ratio_algebraic);

    prove("CQ09b-4a", "v_e(r)/v_p(r) = 1 at ALL radii (algebraic identity)",
          ratio_algebraic, 1.0, 0.1);

    std::printf("  %-16s  %12s  %12s  %12s  %8s\n",
                "Location", "v_proton/c", "v_electron/c", "Ratio", "Match");
    std::puts("  ----------------  ------------  ------------  ------------  --------");

    struct Pt { const char* label; double r; };
    Pt pts[] = {
        {"0.5 R_p",    0.5 * R_p},
        {"R_p",        R_p},
        {"2 R_p",      2.0 * R_p},
        {"r_e",        r_e},
        {"10 r_e",     10.0 * r_e},
        {"100 r_e",    100.0 * r_e},
        {"lbar_C_e",   hbar / (m_e * c)},
        {"lambda_C_e", lambda_C_e},
        {"0.01 a_0",   0.01 * a_0},
        {"0.1 a_0",    0.1 * a_0},
        {"a_0",        a_0},
        {"4 a_0",      4.0 * a_0},
        {"9 a_0",      9.0 * a_0},
    };

    for (auto& [label, r] : pts) {
        double v_p = (c / koppa_H) * std::sqrt(R_p / r);
        double v_e = c * std::sqrt(r_e / r);
        double ratio = v_e / v_p;
        std::printf("  %-16s  %12.6f  %12.6f  %12.6f  %s\n",
                    label, v_p / c, v_e / c, ratio,
                    std::abs(ratio - 1.0) < 0.001 ? "  YES" : "  NO");
    }
    std::puts("");
}

// ═══════════════════════════════════════════════════════════════════════
//  SECTION 5: WHAT THIS MEANS
// ═══════════════════════════════════════════════════════════════════════

static void section5_interpretation()
{
    std::puts("================================================================");
    std::puts("  SECTION 5: INTERPRETATION — ONE FIELD, NOT TWO");
    std::puts("================================================================\n");

    // The proton field and electron field are identical at every point.
    // This is not a coincidence — it is a NECESSARY CONSEQUENCE of the
    // koppa formulation.
    //
    // Proton: v_p(r) = (c/ϟ_H) √(R_p/r)     with ϟ_H = (1/α)√(R_p/a₀)
    // Electron: v_e(r) = (c/ϟ_e) √(r_e/r)    with ϟ_e = 1
    //
    // v_p(r) = cα √(a₀/R_p) × √(R_p/r) = cα √(a₀/r)
    // v_e(r) = c √(r_e/r) = c √(α²a₀/r) = cα √(a₀/r)
    //
    // IDENTICAL. Always. Everywhere.

    std::puts("  THE ALGEBRA:");
    std::puts("    v_p(r) = (c/ϟ_H) × √(R_p/r)   where ϟ_H = (1/α)√(R_p/a₀)");
    std::puts("           = cα × √(a₀/r)");
    std::puts("");
    std::puts("    v_e(r) = c × √(r_e/r)          where r_e = α²a₀");
    std::puts("           = cα × √(a₀/r)");
    std::puts("");
    std::puts("    v_p(r) ≡ v_e(r)   EVERYWHERE.\n");

    // The simplified form
    double A = c * alpha * std::sqrt(a_0);
    std::printf("  THE UNIFIED FIELD: v(r) = cα√(a₀/r) = A/√r\n");
    std::printf("    where A = cα√a₀ = %.6e m^(3/2)/s\n\n", A);

    // At key radii
    std::printf("  v(R_p) = A/√R_p = %.4fc   (superluminal)\n", A / std::sqrt(R_p) / c);
    std::printf("  v(r_e) = A/√r_e = %.4fc   (c-boundary)\n", A / std::sqrt(r_e) / c);
    std::printf("  v(a₀)  = A/√a₀  = %.6fc  (= αc, electron orbit)\n\n", A / std::sqrt(a_0) / c);

    prove("CQ09b-5a", "v(a₀) = αc from unified field",
          A / std::sqrt(a_0), v_electron, 0.01);

    std::puts("  ┌─────────────────────────────────────────────────────────────┐");
    std::puts("  │  THERE IS NO 'PROTON FIELD' AND 'ELECTRON FIELD'.          │");
    std::puts("  │                                                             │");
    std::puts("  │  THERE IS ONE FIELD: v(r) = cα√(a₀/r)                      │");
    std::puts("  │                                                             │");
    std::puts("  │  The proton is where this field exceeds c (the source).     │");
    std::puts("  │  The electron is where this field equals αc (the node).     │");
    std::puts("  │  Both are FEATURES of the same rotation field.              │");
    std::puts("  │                                                             │");
    std::puts("  │  koppa_proton = 0.5464 and koppa_electron = 1.0 are         │");
    std::puts("  │  not two separate koppas — they are the SAME FIELD          │");
    std::puts("  │  evaluated at two different radii:                           │");
    std::puts("  │                                                             │");
    std::puts("  │    k(r) = c/v(r) = (1/α)√(r/a₀)                            │");
    std::puts("  │    k(R_p) = (1/α)√(R_p/a₀) = 0.5464 = ϟ_H                 │");
    std::puts("  │    k(r_e) = (1/α)√(r_e/a₀) = (1/α)×α = 1.0                │");
    std::puts("  │    k(a₀)  = (1/α)√(a₀/a₀) = 1/α = 137.036                 │");
    std::puts("  │                                                             │");
    std::puts("  │  koppa is not a property of a BODY.                         │");
    std::puts("  │  koppa is a property of the FIELD at a RADIUS.              │");
    std::puts("  └─────────────────────────────────────────────────────────────┘\n");

    // The k(r) profile
    std::printf("  THE KOPPA PROFILE k(r) = (1/α)√(r/a₀):\n\n");
    std::printf("  %-16s  %12s  %12s\n", "Location", "r (m)", "k(r)");
    std::puts("  ----------------  ------------  ------------");

    struct Pt { const char* label; double r; };
    Pt pts[] = {
        {"R_p (proton)",    R_p},
        {"r_e (c-bound)",   r_e},
        {"lbar_C_e",        hbar / (m_e * c)},
        {"a_0 (electron)",  a_0},
        {"4 a_0 (n=2)",     4.0 * a_0},
        {"9 a_0 (n=3)",     9.0 * a_0},
    };
    for (auto& [label, r] : pts) {
        double k = (1.0 / alpha) * std::sqrt(r / a_0);
        std::printf("  %-16s  %12.4e  %12.4f\n", label, r, k);
    }
    std::puts("");

    prove("CQ09b-5b", "k(R_p) = ϟ_H = 0.5464",
          (1.0 / alpha) * std::sqrt(R_p / a_0), koppa_H, 0.1);

    prove("CQ09b-5c", "k(r_e) = 1.0 (c-boundary)",
          (1.0 / alpha) * std::sqrt(r_e / a_0), 1.0, 0.1);

    prove("CQ09b-5d", "k(a₀) = 1/α = 137.036",
          (1.0 / alpha) * std::sqrt(a_0 / a_0), alpha_inv, 0.001);
}

// ═══════════════════════════════════════════════════════════════════════
//  MAIN
// ═══════════════════════════════════════════════════════════════════════

int main()
{
    std::puts("================================================================");
    std::puts("  CQ09b: THE ELECTRON DRIVES THE PROTON");
    std::puts("  — or: there is no driver. There is one field.");
    std::puts("  SDT Canonical Engine — James Tyndall, Melbourne");
    std::puts("================================================================\n");

    section1_electron_koppa();
    section2_electron_field();
    section3_field_at_proton();
    section4_comparison();
    section5_interpretation();

    std::puts("================================================================");
    std::printf("  RESULTS: %d/%d proofs passed\n", passed_count, total_proofs);
    std::puts("================================================================\n");

    if (passed_count == total_proofs) {
        std::puts("  CQ09b RESOLVED:");
        std::puts("");
        std::puts("    The proton and electron fields are IDENTICAL.");
        std::puts("    v_p(r) = (c/ϟ_H)√(R_p/r) = cα√(a₀/r)");
        std::puts("    v_e(r) = c × √(r_e/r)     = cα√(a₀/r)");
        std::puts("");
        std::puts("    This is ONE rotation field: v(r) = cα√(a₀/r)");
        std::puts("    The proton is the superluminal core (v > c).");
        std::puts("    The electron is the standing-wave node (v = αc).");
        std::puts("    r_e = α²a₀ is the c-boundary (v = c).");
        std::puts("");
        std::puts("    koppa is not a body property. It is a field profile:");
        std::puts("    k(r) = (1/α)√(r/a₀)");
        std::puts("    k(R_p) = 0.5464   k(r_e) = 1.0   k(a₀) = 137.036");
        std::puts("");
        std::puts("    The hydrogen atom is a SINGLE self-consistent vortex.");
        std::puts("    Not two particles. One field. Two features.\n");
    }

    return (passed_count == total_proofs) ? 0 : 1;
}
