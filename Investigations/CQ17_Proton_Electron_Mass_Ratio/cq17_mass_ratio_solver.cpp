/**
 * CQ17b v4: ABSOLUTE SCALE DERIVATION
 *
 * The previous versions normalised R₀=a₀=1. That's geometrically clean
 * but loses the physical scale. The mass ratio is a ratio of ABSOLUTE
 * volumes anchored to ℓ_P.
 *
 * THE PHYSICAL PICTURE:
 *
 * Both the electron and proton exist in the SAME lattice. Their sizes
 * are fixed by the lattice equilibrium condition, not by normalisation.
 *
 * ELECTRON:
 *   The electron is a W=1 torus rotating at v_e = αc at the Bohr orbit.
 *   At the torus surface (tube wall), the circulation velocity equals c.
 *   This is the c-boundary: the tube radius a_e = λ̄_e / (2π·something).
 *
 *   From CQ09: the proton surface rotates at v_p = c/ϟ_H = 1.831c.
 *   The c-boundary for the proton is at r_e (classical electron radius).
 *   So the electron TUBE radius = r_e (the classical electron radius).
 *
 *   a_e = r_e = α² a₀ = α λ̄_e  (classical electron radius)
 *   R_e = a_e  (horn torus condition, v=c at tube wall)
 *
 * PROTON:
 *   The trefoil at v=βc with the 6π winding contraction:
 *   R_p' = 3 R₀ / v_T  (from previous derivation)
 *   a_p' = a₀ / v_P
 *
 *   But R₀ and a₀ are the PROTON'S own pre-contraction radii.
 *   Before contraction, the proton's closed loop has circumference 6π R₀.
 *   What is R₀?
 *
 *   R₀ is set by the proton's OWN c-boundary before contraction.
 *   The proton tube before winding = a simple closed loop at the same
 *   lattice scale as the electron, i.e. R₀ = a₀ = r_e (same lattice cell).
 *
 *   After the 6π contraction at v_T = 1.015c:
 *     R_p' = 3 r_e / v_T
 *     a_p' = r_e / v_P
 *
 * MASS RATIO:
 *   m_p / m_e = V_p / V_e
 *             = (2π² R_p' a_p'²) / (2π² R_e a_e²)
 *             = (R_p'/R_e) × (a_p'/a_e)²
 *             = [3/v_T] × [1/v_P]²          (since R₀=a₀=r_e=R_e=a_e)
 *             = 3 / (v_T × v_P²)
 *
 *   Now v_T = β × p/√(p²+q²) = β × 2/√13
 *       v_P = β × q/√(p²+q²) = β × 3/√13
 *
 *   m_p/m_e = 3 / [(β×2/√13) × (β×3/√13)²]
 *           = 3 / [(2β/√13) × (9β²/13)]
 *           = 3 × 13^(3/2) / (18β³)
 *           = 13^(3/2) / (6β³)
 *
 *   Same algebraic form. The ratio is still 1.27.
 *
 * THE MISSING SCALE FACTOR:
 *
 * The data forces: (target)/(derived) = 1836.15 / 1.274 ≈ 1441
 * log₁₀(1441) ≈ 3.16 ≈ π
 * 1441 ≈ 1836/√(1.631) ... no clean form.
 *
 * Try: 1441 = ?
 * 1836.15 / 13^(3/2) = 1836.15 / 46.87 = 39.18
 * 39.18 × 6 = 235.1 = β³ needed
 * β_needed = 235.1^(1/3) = 6.17
 *
 * 6.17 / 1.831 = 3.37 ≈ √(p²+q²)/p = √13/2 = 1.803 ... no.
 *
 * BUT: What if the correct contraction is NOT c/v_axis but the
 * LORENTZ factor of the LATTICE at that speed?
 *
 * For v > c in the lattice, the phase compression factor is:
 *   γ_lattice = v²/c² - 1  (the "imaginary Lorentz" for superluminal)
 *   L_contracted = L₀ × 1/sqrt(β²-1)  (not c/β)
 *
 * Let's test BOTH contraction laws:
 *   Model A: L' = L × c/v  (simple ratio)
 *   Model B: L' = L / √(β²-1)  (superluminal Lorentz analogue)
 *   Model C: L' = L × 1/β   (same as A, since v_T = β×2/√13)
 */

#include <cstdio>
#include <cmath>
#include <numbers>

constexpr double pi = std::numbers::pi;
constexpr double kappa_H = 0.5464;
constexpr double beta    = 1.0 / kappa_H;

int main() {
    std::printf("╔══════════════════════════════════════════════════════════════╗\n");
    std::printf("║  CQ17b v4: CONTRACTION MODEL SURVEY                        ║\n");
    std::printf("║  Searching for the correct superluminal contraction law     ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════╝\n\n");

    int p = 2, q = 3;
    double sq = std::sqrt((double)(p*p + q*q));
    double vT = beta * p / sq;
    double vP = beta * q / sq;
    double target = 1836.15267;

    std::printf("  β = %.6f   v_T = %.6f c   v_P = %.6f c\n\n", beta, vT, vP);

    std::printf("══════════════════════════════════════════════════════════════\n");
    std::printf("  CONTRACTION MODEL COMPARISON\n");
    std::printf("  (All normalised: R₀ = a₀ = r_e = 1)\n");
    std::printf("══════════════════════════════════════════════════════════════\n\n");

    // Electron reference: R_e=1, a_e=1, V_e=2π²
    double V_e = 2.0 * pi * pi;

    auto test_model = [&](const char* name, double contract_R, double contract_a) {
        double R_p = 3.0 * contract_R;  // factor 3 from three-lobe → single-torus
        double a_p = contract_a;
        double V_p = 2.0 * pi * pi * R_p * a_p * a_p;
        double ratio = V_p / V_e;
        std::printf("  %-35s R_p'=%.4f  a_p'=%.6f  ratio=%.5f  (Δ=%.2f%%)\n",
            name, R_p, a_p, ratio, 100.0*(ratio-target)/target);
    };

    // Model A: contraction = c/v_axis
    test_model("A: c/v_T, c/v_P",
        1.0/vT, 1.0/vP);

    // Model B: superluminal Lorentz: 1/sqrt(v²-1)
    test_model("B: 1/√(v_T²-1), 1/√(v_P²-1)",
        1.0/std::sqrt(vT*vT-1.0), 1.0/std::sqrt(vP*vP-1.0));

    // Model C: expansion (v/c) instead of contraction
    test_model("C: v_T/c, v_P/c (expansion)",
        vT, vP);

    // Model D: 1/(v_T² - 1), 1/(v_P² - 1) -- Čerenkov-type
    test_model("D: 1/(v_T²-1), 1/(v_P²-1)",
        1.0/(vT*vT-1.0), 1.0/(vP*vP-1.0));

    // Model E: β expansion on R, c/v_P on a
    test_model("E: β (expansion), c/v_P (contraction)",
        beta, 1.0/vP);

    // Model F: c/v_T on R, β expansion on a
    test_model("F: c/v_T (contract), β on a",
        1.0/vT, beta);

    // Model G: α (fine structure) contraction
    // In CQ09, the electron orbit v_e = αc, so the loop circumference
    // at the electron scale is 2πa₀. The proton scale is fixed to r_e.
    // The ratio a₀/r_e = 1/α² = 137² = 18769.
    // Maybe the "natural" comparison is not r_e vs r_e but a₀ vs r_e?
    double alpha_fs = 1.0/137.036;
    std::printf("\n  ── Scale comparison using α = 1/137.036 ──\n");
    std::printf("  a₀/r_e = 1/α² = %.2f\n", 1.0/(alpha_fs*alpha_fs));
    std::printf("  (a₀/r_e)^(1/3) = %.4f\n\n", std::cbrt(1.0/(alpha_fs*alpha_fs)));

    // Model H: the electron is normalised at a₀, proton at R_p
    // If V_e ~ a₀³ and V_p ~ R_p × a_p²:
    // V_p/V_e = R_p a_p² / a₀³
    //  = (3/vT)(1/vP)² / a₀³   where a₀ = 1/α² in units of r_e
    double a0_over_re = 1.0/(alpha_fs*alpha_fs);
    double ratio_H = (3.0/vT) * (1.0/vP) * (1.0/vP) / (a0_over_re * a0_over_re * a0_over_re);
    std::printf("  Model H (electron at a₀ scale, proton at r_e scale):\n");
    std::printf("    V_p/V_e = 13^(3/2)/(6β³) / (1/α²)³\n");
    std::printf("    = 13^(3/2)/(6β³) × α⁶\n");
    std::printf("    = %.8f × %.8e = %.8e\n",
        std::pow(13.0,1.5)/(6.0*beta*beta*beta),
        std::pow(alpha_fs,6),
        std::pow(13.0,1.5)/(6.0*beta*beta*beta) * std::pow(alpha_fs,6));
    std::printf("    Ratio = %.6e  (vs target 1836.15267)\n\n", ratio_H);

    std::printf("══════════════════════════════════════════════════════════════\n");
    std::printf("  INVERTING: what contraction law naturally gives 1836.15?\n");
    std::printf("══════════════════════════════════════════════════════════════\n\n");

    // m_p/m_e = (R_p'/R_e)(a_p'/a_e)² = (3 f_R) × f_a²
    // where f_R = contraction on major radius, f_a = contraction on minor radius
    // We need: (3 f_R)(f_a)² = 1836.15
    // The speed ratio: v_T/v_P = p/q = 2/3
    // Natural ansatz: f_R = F(v_T), f_a = F(v_P) for some law F

    // From the velocity decomposition v_T/v_P = 2/3:
    // (3 F(vT)) F(vP)² = 1836.15
    // If F(v) = β_axis^n for integer n:
    std::printf("  Scanning exponent n: f = v^n,  ratio = 3 v_T^n × v_P^(2n)\n");
    std::printf("  %-6s  %-12s  %-10s\n", "n", "ratio", "Δ%");
    std::printf("  ────────────────────────────────\n");
    for (int n = -12; n <= 12; ++n) {
        double fR = std::pow(vT, (double)n);
        double fa = std::pow(vP, (double)n);
        double r = 3.0 * fR * fa * fa;
        if (std::abs(r - target)/target < 0.5 || std::abs(n) <= 2) {
            std::printf("  %-6d  %-12.4f  %+.3f%%\n", n, r, 100.0*(r-target)/target);
        }
    }

    // The key search: what power of β_total gives 1836?
    std::printf("\n  Scanning total β^n:  ratio = K × β^n for K from topology\n");
    // From structure: ratio = (13^(3/2)/6) / β^3 in Model A, giving 1.27
    // We need ratio × β^3 = 1836.15 → ratio = 1836.15/β^3 = 1836.15/6.13 = 299.5
    // ratio ≈ 300 = (something topological)
    // 300 = 3 × 100 = 3 × 10² = 3 × (p²+q²+1)²?
    // p²+q² = 13, (13-3)² = 100 → 3×100 = 300 ✓
    std::printf("\n  Is 3×(p²+q²-3)² = 3×(13-3)² = 3×100 = %.0f?\n", 3.0*100);
    double model_I = 3.0 * 100.0 / (beta*beta*beta);
    std::printf("  Model I: 3×(p²+q²-3)² / β³ = %.5f  (Δ=%.3f%%)\n",
        model_I, 100.0*(model_I-target)/target);

    // More systematic: factor × β^3 = 1836.15
    double factor_needed = target * beta * beta * beta;
    std::printf("\n  Factor needed so that F/β³ = 1836.15:\n");
    std::printf("    F = 1836.15 × β³ = 1836.15 × %.4f = %.4f\n",
        beta*beta*beta, factor_needed);
    std::printf("    Is F = 13^(3/2) × 240? 13^(3/2) × 240 = %.4f\n",
        std::pow(13.0,1.5) * 240.0);
    std::printf("    Is F = (p×q)^3? (2×3)^3 = %.0f\n", std::pow(6.0,3));
    std::printf("    Is F = (p+q)^5? (2+3)^5 = %.0f\n", std::pow(5.0,5));
    std::printf("    (p+q)^5 / β³ = %.4f  (Δ=%.3f%%)\n",
        std::pow(5.0,5)/(beta*beta*beta),
        100.0*(std::pow(5.0,5)/(beta*beta*beta)-target)/target);
    std::printf("    Is F = π^5×6? 6π^5 = %.4f\n", 6*std::pow(pi,5));
    std::printf("    6π^5 / β³ = %.4f  (Δ=%.3f%%)\n",
        6*std::pow(pi,5)/(beta*beta*beta),
        100.0*(6*std::pow(pi,5)/(beta*beta*beta)-target)/target);

    // KEY: what if the contraction applies to the CIRCUMFERENCE (6π) not
    // the winding number (p=2) separately?
    // Total uncontracted circumference = 6πR  (3 lobes × 2πR)
    // Effective contracted circumference = 6πR / β_total (pure β, not axis-split)
    // Effective single loop: 2πR' = 6πR/β → R' = 3R/β
    // Minor radius contracts by v_P: a' = a/v_P = a√13/(3β)
    // This is Model A — same result.
    //
    // WHAT IF the contraction is only on the TUBE LENGTH, not radius?
    // V_disp = πa² × L_tube
    // L_tube of trefoil at β contracts: L' = L₀/β (superluminal)
    // a stays the same (the cross-section of the tube is set by the
    // lattice, not the velocity)
    //
    // L₀ for trefoil (2,3) at R=r_e, a=r_e×√(2/3):
    // L₃ ≈ 20.698 r_e  (from Phase 2 data)
    // L_e = 9.508 r_e
    // V_p/V_e = (a_p/a_e)² × (L_p'/L_e)
    //         = (√(2/3))² × (L₃/β) / L_e
    //         = (2/3) × (20.698/(β × 9.508))
    double L_knot = 20.698;  // from earlier
    double L_torus = 9.508;
    double a_ratio_sq = 2.0/3.0;
    double model_J = a_ratio_sq * (L_knot/(beta * L_torus));
    std::printf("\n  Model J (tube length contracts, cross-section fixed):\n");
    std::printf("    V_p/V_e = (a₃/a₁)² × L₃'/(L₁)\n");
    std::printf("            = (√(2/3))² × (L₃/β) / L₁\n");
    std::printf("            = (2/3) × %.4f / (%.4f × %.4f) = %.5f  (Δ=%.3f%%)\n",
        L_knot, beta, L_torus, model_J, 100.0*(model_J-target)/target);

    // FINAL THOUGHT: what is the ratio of the LATTICE POINTS enclosed?
    // Not the geometric volume but the NUMBER OF SPATIONS displaced.
    // Each spation is a cube of side ℓ_P.
    // The displacement radius at the proton surface grows as v_p / (ω_P):
    //   ω_P = v_P / R_P (angular frequency)
    //   displacement depth d = v_P / ω_P × (1/k_P) where k_P = c/v_P...
    // This is getting circular. Let's try the dimensional count directly.
    //
    // Solid angle approach:
    // A vortex at speed v sweeps through (v/c)^3 more lattice cells per
    // unit time than one at c, because it covers β times the area per unit
    // time AND encounters β times more cells per unit length.
    // Total displaced cells: N ∝ v³ = β³ for the proton.
    // For the electron at c: N_e ∝ 1.
    // But this gives ratio = β³ = 6.13, not 1836.
    //
    // For the TREFOIL specifically, the knot topology means the vortex
    // sweeps through the interior of the knot (2,3) crossing region.
    // The number of crossings for (2,3) is 3. Each crossing displaces
    // additional lattice. Total cells ∝ β³ × (topological factor).
    // For trefoil: topological factor = ???
    // 1836 / 6.13 ≈ 299.5 ≈ (5-1)! × something? 4! = 24... no.
    // 299.5 ≈ 300 = 3 × 100 = 3 × 10² = q × (p+q)²×p = 3×25×4 = 300 ✓

    double model_K = (double)(q) * std::pow((double)(p+q), 2) * (double)(p) * (beta*beta*beta) / (beta*beta*beta);
    // Wait: q × (p+q)² × p / β³:
    double model_K2 = (double)q * (double)((p+q)*(p+q)) * (double)p / (beta*beta*beta);
    std::printf("\n  Model K: q(p+q)²p / β³ = 3×25×2/β³ = %.5f\n", model_K2);
    std::printf("    Δ = %.3f%%\n\n", 100.0*(model_K2-target)/target);

    // EXACT:
    // 3 × 25 × 2 = 150 ... /β³ = 150/6.13 = 24.5. No.
    // Try: (p+q)^(p+q) / (p^p × q^q) [the multinomial coefficient base]
    // = 5^5 / (2^2 × 3^3) = 3125 / (4 × 27) = 3125/108 = 28.94. No.
    //
    // Maybe the right formula is simpler. Let's enumerate small integer expressions:
    // 1836.15 × β³ = 1836.15 × 6.1301 = 11261
    // 11261 ≈ ?
    // 11261 / (p²+q²)^(3/2) = 11261 / 46.87 = 240.3 ≈ 240 = 2^4 × 3 × 5 = (p+q)! × (p×q) = 120×6 = 720... no.
    // 240 = 24 × 10 = 4! × 10 = (p!)^(q-1) × p×(p+q)?? 2 × 120 = 240? No.
    // 240 = 2^4 × 15 = 2^4 × 3 × 5 = ???
    // Let's just print this:
    std::printf("  Factor analysis: 1836.15 × β³ = %.2f\n", target * beta * beta * beta);
    std::printf("  %.2f / 13^(3/2) = %.4f\n", target * beta * beta * beta, (target * beta * beta * beta)/std::pow(13.0,1.5));
    std::printf("  Nearest integers: 239, 240, 241\n\n");
    std::printf("  240 = 2⁴ × 3 × 5 = 16 × 15\n");
    std::printf("  240 = 2p × q × (p+q)² = 4 × 3 × 5² = 4 × 3 × 25 = 300 (not 240)\n");
    std::printf("  240 = (p+q)! / p = 5!/2 = 120/... no, 5!=120\n");
    std::printf("  240 = (p²+q²) × p × q × something? 13 × 6 = 78, 78×3=234 (close)\n\n");

    // The number 240 in topology: 240 is significant in the classification
    // of exotic spheres (Kervaire-Milnor) and in the E8 lattice (240 roots).
    std::printf("  NOTE: 240 = number of root vectors in E8 lattice.\n");
    std::printf("        This might be the topological invariant: the E8 packing\n");
    std::printf("        factor that the (2,3) trefoil inherits.\n");
    std::printf("        13^(3/2) × 240 / (6 × β³) = %.4f\n\n",
        std::pow(13.0,1.5)*240.0/(6.0*beta*beta*beta));

    return 0;
}
