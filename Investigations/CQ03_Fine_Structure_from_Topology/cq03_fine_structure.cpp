/**
 * @file cq03_fine_structure.cpp
 * @brief CQ03: Fine Structure Constant from Topology
 *
 * THE QUESTION:
 *   Can α = 1/137.036 be derived from the W=1 torus geometry?
 *
 * FROM CQ02:
 *   Electron = (1,1) torus unknot: v_T = v_P = c/√2, R/a = 1
 *   Proton = (2,3) torus trefoil: v_T = c√(2/5), v_P = c√(3/5)
 *
 * FROM laws.hpp winding namespace:
 *   g_electron = r_e × m_e × c / ℏ = α (EXACT IDENTITY)
 *   g_proton   = R_p × m_p × c / ℏ ≈ 4
 *
 * THE CONJECTURE:
 *   α = v_P / v_T at W=1? CQ02 showed v_P/v_T = 1 for (1,1).
 *   So α ≠ v_P/v_T directly. The question is: WHERE does α enter?
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

// ═══════════════════════════════════════════════════════════════════════
//  PROOF INFRASTRUCTURE
// ═══════════════════════════════════════════════════════════════════════

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
    std::printf("    Derived:  %.10e   Expected: %.10e   Err: %.6f%%\n\n",
                derived, expected, err);
}

// ═══════════════════════════════════════════════════════════════════════
//  SECTION 1: THE EXISTING α IDENTITIES
//
//  α appears in SDT at three distinct places:
//  1. Wake-to-quantum ratio: g(W=1) = R_wake / λ̄_C = r_e / λ̄_Ce = α
//  2. Hydrogen ground state: v_1 = αc (Bohr velocity)
//  3. Koppa of the proton: ϟ_H = (1/α)√(R_p/a_0) = 0.5464
//
//  All three are algebraically identical. The question is whether
//  any of them can be DERIVED from topology alone.
// ═══════════════════════════════════════════════════════════════════════

static void section1_identities()
{
    std::puts("================================================================");
    std::puts("  SECTION 1: The α Identities in SDT");
    std::puts("================================================================\n");

    // Identity 1: g_electron = r_e m_e c / ℏ
    double g_e = r_e * m_e * c / hbar;
    prove("CQ03-1a", "g_electron = r_e m_e c / hbar = alpha",
          g_e, alpha, 0.01);

    // Identity 2: α = e²/(4πε₀ ℏc) = k_e e²/(ℏc)
    double alpha_coulomb = k_e * e_charge * e_charge / (hbar * c);
    prove("CQ03-1b", "alpha from Coulomb coupling",
          alpha_coulomb, alpha, 0.01);

    // Identity 3: r_e = α² a_0
    double r_e_from_a0 = alpha * alpha * a_0;
    prove("CQ03-1c", "r_e = alpha^2 × a_0",
          r_e_from_a0, r_e, 0.01);

    // Identity 4: R_p = α × a_0 × (R_p/r_e)
    // From W+1 conjecture: R_p = 4ℏ/(m_p c)
    // From α: r_e = α ℏ/(m_e c)  [= α × reduced Compton wavelength]
    double r_e_check = alpha * hbar / (m_e * c);
    prove("CQ03-1d", "r_e = alpha * hbar/(m_e c)",
          r_e_check, r_e, 0.01);

    // Identity 5: g_proton = R_p m_p c / ℏ ≈ 4 = W+1
    double g_p = R_p * m_p * c / hbar;
    prove("CQ03-1e", "g_proton = R_p m_p c / hbar ≈ 4 = W+1",
          g_p, 4.0, 0.1);

    // CRITICAL OBSERVATION:
    // g_electron = α = R_wake_e × m_e × c / ℏ
    // g_proton   = 4 = R_wake_p × m_p × c / ℏ
    //
    // g(W) = (W+1) for the proton (W=3 → g=4), exact to 0.02%.
    // For the electron (W=1): g = W+1 = 2? But g_electron = α ≈ 0.00730.
    //
    // THIS IS THE KEY: the electron does NOT satisfy g = W+1.
    // The proton does. The electron's wake radius r_e is MUCH smaller
    // than (W+1)ℏ/(m_e c) = 2ℏ/(m_e c):

    double R_wake_W1 = 2.0 * hbar / (m_e * c);  // W+1 = 2 for electron
    double lambda_bar_e = hbar / (m_e * c);       // reduced Compton

    std::printf("  CRITICAL COMPARISON:\n");
    std::printf("    If g_electron = W+1 = 2: R_wake = 2 hbar/(m_e c) = %.4e m\n", R_wake_W1);
    std::printf("    Actual r_e (classical electron radius) = %.4e m\n", r_e);
    std::printf("    Ratio: r_e / (2 hbar/m_e c) = %.6f = alpha/2\n\n", r_e / R_wake_W1);

    // So: r_e = α × λ̄_C = α × ℏ/(m_e c)
    // But the W+1 conjecture would give: R_wake = 2 × ℏ/(m_e c)
    // The RATIO is: r_e / R_W+1 = α/2
    //
    // For the proton: R_p / [(W+1)ℏ/(m_p c)] = R_p m_p c / (4ℏ) ≈ 1.0002
    // The proton obeys g = W+1. The electron does NOT.
    //
    // This means α is the RATIO of the electron's actual wake radius
    // to its quantum coherence scale. It measures HOW MUCH of the
    // torus's Compton wavelength is occupied by the wake perturbation.
}

// ═══════════════════════════════════════════════════════════════════════
//  SECTION 2: WHAT α IS GEOMETRICALLY
//
//  The CQ02 mode equations give v_P/v_T = 1 for (1,1).
//  But the PHYSICAL electron has v_P/v_T ≠ 1, because:
//    - v_T and v_P are not the raw mode velocities
//    - They are REDUCED by the self-interaction of the circulation
//    - The reduction factor IS α
//
//  Picture: a (1,1) torus with circulation at velocity c/√2 in each mode.
//  But the circulating current generates an electromagnetic field (the wake).
//  The wake fraction α feeds back into the mode partition.
//
//  The ACTUAL mode velocities become:
//    v_T(actual) = c/√2 × (1 - α/2 + ...)  ≈ c/√2
//    v_P(actual) = c/√2 × (1 + α/2 + ...)  ≈ c/√2
//
//  The DIFFERENCE between modes:
//    (v_P - v_T) / (v_P + v_T) ≈ α/2
//
//  This is the fine structure: the self-interaction of the circulation
//  with its own wake field breaks the (1,1) degeneracy by α.
// ═══════════════════════════════════════════════════════════════════════

static void section2_geometric_alpha()
{
    std::puts("================================================================");
    std::puts("  SECTION 2: What α IS Geometrically");
    std::puts("================================================================\n");

    // From the winding namespace: g = R_wake × m × c / ℏ
    // g_electron = α
    //
    // R_wake is the range of the pressure perturbation in the lattice.
    // ℏ/(mc) = λ̄_C is the quantum coherence scale.
    // g = R_wake / λ̄_C = how far the wake extends in Compton units.
    //
    // For the electron:
    //   R_wake = r_e = 2.818e-15 m
    //   λ̄_C = ℏ/(m_e c) = 3.862e-13 m
    //   g = r_e / λ̄_C = α = 7.297e-3

    double lambda_bar_e = hbar / (m_e * c);
    double g_e = r_e / lambda_bar_e;
    std::printf("  Electron wake/quantum ratio:\n");
    std::printf("    R_wake = r_e = %.4e m\n", r_e);
    std::printf("    lambda_bar_C = hbar/(m_e c) = %.4e m\n", lambda_bar_e);
    std::printf("    g = r_e / lambda_bar_C = %.6e = 1/%.2f\n\n", g_e, 1.0/g_e);

    prove("CQ03-2a", "g_electron = alpha",
          g_e, alpha, 0.001);

    // For the proton:
    //   R_wake = R_p = 8.414e-16 m
    //   λ̄_C = ℏ/(m_p c) = 2.103e-16 m
    //   g = R_p / λ̄_C ≈ 4.0008 ≈ W+1 = 4
    double lambda_bar_p = hbar / (m_p * c);
    double g_p = R_p / lambda_bar_p;
    std::printf("  Proton wake/quantum ratio:\n");
    std::printf("    R_wake = R_p = %.4e m\n", R_p);
    std::printf("    lambda_bar_C = hbar/(m_p c) = %.4e m\n", lambda_bar_p);
    std::printf("    g = R_p / lambda_bar_C = %.6f ≈ %d\n\n",
                g_p, static_cast<int>(std::round(g_p)));

    prove("CQ03-2b", "g_proton ≈ W+1 = 4",
          g_p, 4.0, 0.03);

    // KEY DIFFERENCE:
    // Proton: g = 4 = integer → topological (knot crossing number + 1)
    // Electron: g = α ≈ 1/137 → NOT an integer.
    //
    // If g should be W+1 = 2 for the electron, then:
    // α = g_actual / g_topological × (W+1) = α/2 × 2 → circular.
    //
    // Instead: the electron's wake radius is NOT (W+1)ℏ/(mc).
    // The electron's wake is REDUCED from the topological value by
    // a self-interaction correction.
    //
    // What is the self-interaction?
    // The circulation on the torus surface generates an EM field.
    // This field acts BACK on the circulation, reducing the effective
    // wake radius. The reduction factor is:
    //   R_wake_actual / R_wake_topological = α / (W+1) = α/2

    double reduction = alpha / 2.0;
    std::printf("  Wake reduction factor (electron):\n");
    std::printf("    R_actual / R_topological = alpha/(W+1) = alpha/2 = %.6e\n", reduction);
    std::printf("    = 1/%.2f\n\n", 1.0/reduction);

    // So α enters as: α = g × [R_wake_actual / R_wake_topological] × (W+1)
    // No — that's circular. Let's think differently.
    //
    // α = k_e e² / (ℏc)
    // This is the coupling strength of the EM field to charged matter.
    // It is NOT a property of the torus geometry. It is a property of
    // the LATTICE — how strongly the spation lattice responds to
    // a charged perturbation.
    //
    // For the proton: g = 4 = W+1 → the wake extends exactly (W+1) Compton lengths.
    //   This is TOPOLOGICAL — the trefoil knot creates 4 wake layers.
    //
    // For the electron: g = α → the wake extends α Compton lengths.
    //   This is ELECTROMAGNETIC — the wake is limited by the coupling strength.
    //
    // WHY? The proton is a KNOT (topologically protected).
    //   Its wake radius is fixed by the crossing number.
    // The electron is an UNKNOT (topologically trivial).
    //   Its wake radius is fixed by the self-interaction of its charge
    //   with the lattice — which IS α.

    std::puts("  INTERPRETATION:");
    std::puts("    Proton (trefoil): g = W+1 = 4 (topological, integer)");
    std::puts("    Electron (unknot): g = alpha (electromagnetic, non-integer)");
    std::puts("    The proton's wake is topologically fixed.");
    std::puts("    The electron's wake is electromagnetically fixed.");
    std::puts("    alpha is the wake-to-quantum ratio of an unknotted charge.\n");
}

// ═══════════════════════════════════════════════════════════════════════
//  SECTION 3: CAN α BE DERIVED FROM FIRST PRINCIPLES?
//
//  α = k_e e² / (ℏc) = e² / (4πε₀ ℏc)
//  In SDT: α = r_e / λ̄_C = R_wake / (ℏ/mc)
//
//  From CQ01: the transfer function f = P_eff/P_conv couples the
//  local EM interaction to the global convergence field.
//  f = 4αℏcl_P / (π R_p² r_e² R_CMB u_CMB)
//
//  This contains α. Can we extract it?
// ═══════════════════════════════════════════════════════════════════════

static void section3_derivation_attempt()
{
    std::puts("================================================================");
    std::puts("  SECTION 3: Derivation Attempts");
    std::puts("================================================================\n");

    // ATTEMPT 1: α from the proton/electron mass ratio and g-values
    // g_e = α, g_p = 4
    // g_e / g_p = α/4
    // α = 4 × g_e / g_p = 4 × r_e m_e c / (R_p m_p c)
    //   = 4 r_e m_e / (R_p m_p)
    //   = 4 × (2.818e-15 × 9.109e-31) / (8.414e-16 × 1.673e-27)
    double alpha_from_g = 4.0 * r_e * m_e / (R_p * m_p);
    std::printf("  Attempt 1: alpha = 4 r_e m_e / (R_p m_p)\n");
    prove("CQ03-3a", "alpha from g-ratio",
          alpha_from_g, alpha, 0.1);

    // This is exact! Because:
    // g_e = r_e m_e c / ℏ = α
    // g_p = R_p m_p c / ℏ = 4
    // g_e/g_p = α/4 = r_e m_e / (R_p m_p)
    // → α = 4 r_e m_e / (R_p m_p)
    // But this is just restating the input identities. Not a derivation.

    // ATTEMPT 2: α from the hydrogen Bohr model self-consistency
    // In hydrogen: the electron orbits the proton at r = a_0 with v = αc.
    // The orbit is stable when the centripetal force equals Coulomb:
    // m_e v² / r = k_e e² / r²
    // m_e α²c² / a_0 = k_e e² / a_0²
    // α²c² = k_e e² / (m_e a_0)
    // α² = k_e e² / (m_e c² a_0) = (αℏc) / (m_e c² a_0) = α ℏ / (m_e c a_0)
    // α = ℏ / (m_e c a_0) = λ̄_C / a_0
    double alpha_from_Bohr = hbar / (m_e * c * a_0);
    std::printf("  Attempt 2: alpha = hbar / (m_e c a_0) = lambda_bar_C / a_0\n");
    prove("CQ03-3b", "alpha from Bohr radius",
          alpha_from_Bohr, alpha, 0.001);

    // Exact — but circular: a_0 = ℏ/(m_e c α), so α = ℏ/(m_e c × ℏ/(m_e c α)) = α.

    // ATTEMPT 3: α from SDT pressure balance
    // F_coulomb = (π/4) P_eff R_charge⁴ / r²
    // F_coulomb at r = a_0 = m_e v² / a_0 = m_e α²c² / a_0
    //
    // Also F_coulomb = k_e e² / a_0² = αℏc / a_0²
    //
    // SDT: (π/4) P_eff R_charge⁴ / a_0² = αℏc / a_0²
    // (π/4) P_eff R_charge⁴ = αℏc
    // α = (π/4) P_eff R_charge⁴ / (ℏc)
    double R_charge = std::sqrt(R_p * r_e);
    double alpha_from_Peff = (std::numbers::pi / 4.0)
                           * law_III::P_eff
                           * std::pow(R_charge, 4)
                           / (hbar * c);
    std::printf("  Attempt 3: alpha = (pi/4) P_eff R_charge^4 / (hbar c)\n");
    prove("CQ03-3c", "alpha from P_eff",
          alpha_from_Peff, alpha, 0.01);

    // Also exact — but P_eff is DEFINED from k_e e² = αℏc.

    // ATTEMPT 4: α from lattice properties ONLY (the real test)
    // α = (π/4) P_eff R_p² r_e² / (ℏc)
    //   = (π/4) [f × P_conv] R_p² r_e² / (ℏc)
    //   = (π/4) × f × (Φ/l_P³) × R_p² r_e² / (ℏc)
    //
    // From CQ01: f = 4αℏc l_P / (π R_p² r_e² R_CMB u_CMB)
    // So: α = (π/4) × [4αℏc l_P / (π R_p² r_e² R_CMB u_CMB)]
    //       × (Φ/l_P³) × R_p² r_e² / (ℏc)
    //       = α × (l_P Φ) / (l_P³ R_CMB u_CMB)
    //       = α × Φ / (l_P² R_CMB u_CMB)
    //       = α × N ε / (l_P² R_CMB u_CMB)
    //       = α × (R_CMB/l_P)(u_CMB l_P³) / (l_P² R_CMB u_CMB)
    //       = α × 1  → circular.
    //
    // Every path through the SDT identities leads back to α = α.
    // α cannot be derived from the current framework.

    std::puts("  ATTEMPT 4: Extract alpha from lattice constants alone");
    std::puts("    f = 4 alpha hbar c l_P / (pi R_p^2 r_e^2 R_CMB u_CMB)");
    std::puts("    P_eff = f × P_conv");
    std::puts("    alpha = (pi/4) P_eff R_charge^4 / (hbar c)");
    std::puts("    Substituting... alpha = alpha × 1");
    std::puts("    CIRCULAR. Cannot extract alpha from f, P_conv alone.\n");

    // ATTEMPT 5: α from the mass ratio and radii
    // Can we express α using ONLY m_p/m_e and geometric ratios?
    // α = r_e / λ̄_C_e = r_e m_e c / ℏ
    // and R_p = 4ℏ/(m_p c) from W+1 conjecture
    // so ℏ = R_p m_p c / 4
    // α = r_e m_e c / (R_p m_p c / 4) = 4 r_e m_e / (R_p m_p)
    //
    // Now r_e = α² a_0 and a_0 = ℏ/(m_e c α) → still circular.
    //
    // But IF we could derive m_p/m_e and R_p/r_e independently...
    // From CQ02: the torus geometry fixes the RATIO of these.
    // m_p/m_e = 1836.15
    // R_p/r_e = 8.414e-16 / 2.818e-15 = 0.2987

    double mass_ratio = m_p / m_e;
    double radius_ratio = R_p / r_e;
    double alpha_from_ratios = 4.0 * radius_ratio / mass_ratio;
    // This should be... let's check:
    // α = 4 r_e m_e / (R_p m_p) = 4 / [(R_p/r_e)(m_p/m_e)] = 4 / (0.2987 × 1836.15)
    // = 4 / 548.55 = 0.007295 ≈ α ✓
    // But this is just regrouping. 4/(ratio_R × ratio_m) = α because g_e = α.

    std::printf("  Attempt 5: alpha = 4 / [(R_p/r_e)(m_p/m_e)]\n");
    std::printf("    R_p/r_e = %.6f\n", radius_ratio);
    std::printf("    m_p/m_e = %.2f\n", mass_ratio);
    std::printf("    product = %.4f\n", radius_ratio * mass_ratio);
    prove("CQ03-3d", "alpha = 4 / (R_p/r_e × m_p/m_e)",
          4.0 / (radius_ratio * mass_ratio), alpha, 0.1);

    std::puts("    This is EXACT but circular — it restates g_e/g_p = alpha/4.\n");
}

// ═══════════════════════════════════════════════════════════════════════
//  SECTION 4: THE SENSITIVITY ANALYSIS
// ═══════════════════════════════════════════════════════════════════════

static void section4_sensitivity()
{
    std::puts("================================================================");
    std::puts("  SECTION 4: Sensitivity — dα/d(R/a)");
    std::puts("================================================================\n");

    // From CQ02: the mode equations give analytic solutions for each (p,q)
    // The aspect ratio R/a = sqrt(q/p)
    // For (1,1): R/a = 1.0000
    // For (2,3): R/a = sqrt(3/2) = 1.2247
    //
    // α enters through the self-interaction of the circulation with the wake.
    // The wake radius r_e = α × λ̄_C is the effective range of the EM
    // perturbation generated by the toroidal current.
    //
    // For a torus with aspect ratio η = R/a:
    //   - Surface area A = 4π² R a = 4π² R²/η
    //   - Volume V = 2π² R a² = 2π² R³/η²
    //   - Coupling = a/R = 1/η (from Theory/01_Closure)
    //
    // The self-interaction energy of a toroidal current loop:
    //   L_torus = μ₀ R (ln(8R/a) - 2)  [for thin torus, R/a >> 1]
    //
    // For fat torus (η = R/a = 1, electron):
    //   L ~ μ₀ R × (ln(8) - 2) = μ₀ R × 0.079
    //
    // The self-interaction parameter is:
    //   ξ = L I² / (mc²) where I = e × v_T / (2πR)
    //
    // This gives a coupling strength that depends on R/a.
    // Let's compute the inductance correction for different aspect ratios.

    auto inductance_factor = [](double eta) -> double {
        if (eta > 1.5) return std::log(8.0 * eta) - 2.0;
        // For fat torus, use the full expression:
        // L/R = μ₀ [ln(8η) - 2 + 1/(4η²) + ...] (Neumann formula)
        // For η ≈ 1: ln(8) - 2 ≈ 0.079
        return std::log(8.0 * eta) - 2.0 + 1.0/(4.0 * eta * eta);
    };

    std::printf("  Inductance factor L/(μ₀ R) for different R/a:\n\n");
    std::printf("  %8s | %12s | %12s\n", "R/a", "L/(mu_0 R)", "Notes");
    std::puts("  ---------|--------------|------------");

    double etas[] = {1.0, 1.2247, 1.4142, 1.7321, 2.0, 3.0, 5.0, 10.0, 137.036};
    const char* labels[] = {"(1,1) e⁻", "(2,3) p", "(1,2)", "(1,3)", "2:1",
                             "3:1", "5:1", "10:1", "1/alpha"};
    for (int i = 0; i < 9; ++i) {
        double L = inductance_factor(etas[i]);
        std::printf("  %8.4f | %12.6f | %s\n", etas[i], L, labels[i]);
    }
    std::puts("");

    // The self-inductance at η = 1 (electron):
    double L_factor_electron = inductance_factor(1.0);
    std::printf("  At η = 1 (electron): L/(μ₀R) = %.6f\n", L_factor_electron);
    std::printf("  At η = 1/α ≈ 137: L/(μ₀R) = %.6f\n\n",
                inductance_factor(alpha_inv));

    // WHAT THIS TELLS US:
    // α is NOT determined by R/a alone. The inductance factor varies
    // slowly with R/a (logarithmically), but α = 1/137 requires
    // additional input: the CHARGE e.
    //
    // In SDT, e is not derived from topology. It enters through the
    // Coulomb calibration (Law III): P_eff = 4 k_e e² / (π R_p² r_e²).
    //
    // So the input chain is:
    //   e (charge) → α = k_e e²/(ℏc) → r_e = αℏ/(m_e c) → g_electron = α
    //
    // α is NOT derivable from topology. It requires the charge quantum e.

    std::puts("  CONCLUSION:");
    std::puts("    dα/d(R/a) is UNDEFINED because α does not depend on R/a.");
    std::puts("    α depends on e (elementary charge), which enters through");
    std::puts("    the Coulomb coupling k_e e^2 = alpha hbar c.");
    std::puts("    The topology determines WHICH modes exist (W=1,2,3...).");
    std::puts("    The charge determines HOW STRONGLY they couple (alpha).\n");
}

// ═══════════════════════════════════════════════════════════════════════
//  SECTION 5: WHAT WOULD BE NEEDED TO DERIVE α
// ═══════════════════════════════════════════════════════════════════════

static void section5_what_needed()
{
    std::puts("================================================================");
    std::puts("  SECTION 5: What Would Be Needed to Derive α");
    std::puts("================================================================\n");

    // Current SDT input set (from laws.hpp):
    // 1. c (exact, SI)
    // 2. ℏ (exact, SI)
    // 3. k_B (exact, SI)
    // 4. e (exact, SI)
    // 5. α (CODATA 2018)
    // 6. m_e, m_p (CODATA 2018)
    // 7. l_P (CODATA 2018)
    // 8. T_CMB (FIRAS)
    // 9. R_p (muonic H, 2019)
    //
    // If α were derivable from topology:
    //   α = f(l_P, T_CMB, d=3)
    //   Then e would also be derived: e = sqrt(4πε₀ α ℏc)
    //   And r_e = α ℏ/(m_e c)
    //   And a_0 = ℏ/(m_e c α) = r_e/α²
    //
    // But our analysis shows: α = k_e e²/(ℏc)
    // Unless we can show that e = f(l_P, T_CMB, d), α remains an input.

    std::puts("  The derivation of α requires showing that e² = f(l_P, T_CMB, d).");
    std::puts("  Specifically, one would need:");
    std::puts("    e² = 4πε₀ α ℏc = 4πε₀ ℏc × f(lattice geometry)");
    std::puts("");
    std::puts("  The lattice candidate: e = charge quantum of a single");
    std::puts("  topological defect in a d=3 spation lattice.");
    std::puts("  If the lattice has a unique minimum-energy charged defect,");
    std::puts("  its charge WOULD be derivable from (l_P, T_CMB, d).");
    std::puts("  This is the CQ10 investigation (Topological Charge Quantisation).");
    std::puts("");

    // The W+1 conjecture gives us a CONSTRAINT:
    // For the proton: R_p = 4ℏ/(m_p c) to 0.02%
    //   This fixes g_proton = 4 (topological)
    //
    // For the electron: g_electron = α (electromagnetic)
    //
    // If W+1 is UNIVERSAL, then g = W+1 for all particles.
    // But the electron has g = α ≈ 0.00730, not g = 2.
    // This means the electron does NOT follow the W+1 rule.
    //
    // UNLESS: the electron's effective winding number is W = α - 1 ≈ -0.993.
    // That's not physical. The winding number must be a non-negative integer.
    //
    // So: W+1 applies to the PROTON (knot), not the ELECTRON (unknot).
    // α is the coupling constant of the unknotted topology to the lattice.

    std::puts("  CURRENT STATUS:");
    std::puts("    alpha IS an independent input in SDT.");
    std::puts("    It CANNOT be derived from (l_P, T_CMB, d=3) alone.");
    std::puts("    It requires the charge quantum e as an additional input.");
    std::puts("    The minimal input set is {l_P, T_CMB, e, d=3}, not {l_P, T_CMB, d=3}.");
    std::puts("    Reducing to 3 inputs requires deriving e from lattice topology (CQ10).\n");

    // Final count
    std::puts("  SDT INPUT HIERARCHY:");
    std::puts("    Tier 0 (defined):  c, h, k_B, e     — SI exact since 2019");
    std::puts("    Tier 1 (measured): alpha, m_e, m_p   — CODATA 2018");
    std::puts("    Tier 2 (cosmological): l_P, T_CMB    — CODATA/FIRAS");
    std::puts("    Tier 3 (derived):  a_0, r_e, R_p, Ry — from Tiers 0-2");
    std::puts("    alpha sits in Tier 1. It is NOT reducible to Tier 2.\n");
}

// ═══════════════════════════════════════════════════════════════════════
//  MAIN
// ═══════════════════════════════════════════════════════════════════════

int main()
{
    std::puts("================================================================");
    std::puts("  CQ03: FINE STRUCTURE CONSTANT FROM TOPOLOGY");
    std::puts("  Can alpha = 1/137.036 be derived from W=1 geometry?");
    std::puts("  SDT Canonical Engine — James Tyndall, Melbourne");
    std::puts("================================================================\n");

    section1_identities();
    section2_geometric_alpha();
    section3_derivation_attempt();
    section4_sensitivity();
    section5_what_needed();

    std::puts("================================================================");
    std::printf("  RESULTS: %d/%d proofs passed\n", passed_count, total_proofs);
    std::puts("================================================================\n");

    std::puts("  CQ03 RESOLVED:");
    std::puts("    Q: Can alpha be derived from W=1 torus geometry?");
    std::puts("    A: NO.");
    std::puts("");
    std::puts("    alpha = r_e / lambda_bar_C = g_electron (wake/quantum ratio)");
    std::puts("    The proton obeys g = W+1 = 4 (topological, integer).");
    std::puts("    The electron obeys g = alpha ≈ 1/137 (electromagnetic, non-integer).");
    std::puts("    alpha encodes the Coulomb coupling e^2/(4piε₀ hbar c),");
    std::puts("    which requires the charge quantum e as an independent input.");
    std::puts("");
    std::puts("    The minimal SDT input set is {l_P, T_CMB, e, d=3},");
    std::puts("    NOT the conjectured {l_P, T_CMB, d=3}.");
    std::puts("    Reducing to 3 inputs requires CQ10: Topological Charge Quantisation.\n");

    return (passed_count == total_proofs) ? 0 : 1;
}
