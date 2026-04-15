/**
 * @file e97_trefoil_test.cpp
 * @brief Test: trefoil partition of convergence into heat/sound/movement
 *
 * Per excluded Planck cell, per Planck tick:
 *   - CMB deposits ε = u_CMB × l_P³ of energy
 *   - Trefoil splits it 3 ways: heat, sound, movement
 *   - Only MOVEMENT creates directed force
 *   - Force per cell per tick = ε / (3 × l_P)
 *
 * Test whether this gives g = 9.81 m/s² at Earth's surface.
 */

#include <cstdio>
#include <cmath>
#include <numbers>

int main() {
    // ── Constants ──
    constexpr double c       = 299'792'458.0;
    constexpr double hbar    = 1.054'571'817e-34;
    constexpr double k_B     = 1.380'649e-23;
    constexpr double l_P     = 1.616'255e-35;
    constexpr double t_P     = 5.391'24e-44;
    constexpr double l_P2    = l_P * l_P;
    constexpr double l_P3    = l_P * l_P * l_P;
    constexpr double a_rad   = 7.565'7e-16;
    constexpr double T_CMB   = 2.7255;
    constexpr double R_CMB   = 9.527e26;
    constexpr double m_p     = 1.672'621'923'69e-27;
    constexpr double m_n     = 1.674'927'498'04e-27;
    constexpr double m_e     = 9.109'383'7015e-31;
    constexpr double m_u     = 1.660'539'07e-27;

    // ── SDT derived ──
    constexpr double u_CMB   = a_rad * T_CMB * T_CMB * T_CMB * T_CMB;
    constexpr double epsilon = u_CMB * l_P3;             // energy per shell per cell
    constexpr double N       = R_CMB / l_P;              // shell count
    constexpr double Phi     = N * epsilon;              // total convergence burden
    constexpr double P_conv  = Phi / l_P3;              // convergence pressure

    // ── Earth ──
    constexpr double R_E     = 6.371e6;
    constexpr double M_Earth = 5.9722e24;
    constexpr double A_avg   = 26.0;                     // average atomic mass
    constexpr double n_baryons = M_Earth / m_u;          // total baryons
    constexpr double n_electrons = n_baryons;            // 1 per baryon (SDT)

    // ── Displacement volumes ──
    constexpr double V_disp_p = 3.0 * m_p * l_P3 * c * c / Phi;
    constexpr double V_disp_n = 3.0 * m_n * l_P3 * c * c / Phi;
    constexpr double V_disp_e = 3.0 * m_e * l_P3 * c * c / Phi;

    // ── Excluded cells ──
    double V_excl = n_baryons * (V_disp_p + V_disp_e) / 2.0 +
                    n_baryons * (V_disp_n + V_disp_e) / 2.0;
    // Simplified: each baryon displaces ~V_disp_baryon + V_disp_e
    V_excl = n_baryons * ((V_disp_p + V_disp_n) / 2.0 + V_disp_e);

    double V_Earth = (4.0/3.0) * std::numbers::pi * R_E * R_E * R_E;
    double a_cells = V_Earth / l_P3;     // Planck cells in spation volume
    double b_cells = V_excl / l_P3;      // Planck cells excluded by matter

    std::printf("╔══════════════════════════════════════════════════════════════════╗\n");
    std::printf("║  TREFOIL PARTITION TEST: heat / sound / movement               ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════════╝\n\n");

    std::printf("── SDT Constants ──\n");
    std::printf("  ε           = %.6e J     (per shell per cell per tick)\n", epsilon);
    std::printf("  Φ           = %.6e J     (total convergence burden)\n", Phi);
    std::printf("  N           = %.6e       (shell count)\n", N);
    std::printf("  P_conv      = %.6e Pa\n", P_conv);
    std::printf("  l_P         = %.6e m\n", l_P);
    std::printf("  t_P         = %.5e s\n\n", t_P);

    std::printf("── Earth ──\n");
    std::printf("  b (excl)    = %.6e Planck cells\n", b_cells);
    std::printf("  a (spation) = %.6e Planck cells\n", a_cells);
    std::printf("  b/a         = %.6e\n\n", b_cells / a_cells);

    // ═══════════════════════════════════════════════════════════
    // TEST 1: ε per cell, per tick, /3 trefoil
    // ═══════════════════════════════════════════════════════════
    std::printf("══ TEST 1: ε per cell per tick, movement = 1/3 ══\n");
    double F1_per_cell = epsilon / (3.0 * l_P);
    double F1_total    = b_cells * F1_per_cell;
    double g1          = F1_total / M_Earth;
    std::printf("  F/cell      = ε/(3 l_P)     = %.6e N\n", F1_per_cell);
    std::printf("  F_total     = b × F/cell    = %.6e N\n", F1_total);
    std::printf("  g           = F/M           = %.6e m/s²\n", g1);
    std::printf("  Ratio to 9.81: %.6e\n\n", 9.81 / g1);

    // ═══════════════════════════════════════════════════════════
    // TEST 2: ε per cell, per tick, NO trefoil split
    // ═══════════════════════════════════════════════════════════
    std::printf("══ TEST 2: ε per cell per tick, full (no /3) ══\n");
    double F2_per_cell = epsilon / l_P;
    double F2_total    = b_cells * F2_per_cell;
    double g2          = F2_total / M_Earth;
    std::printf("  F/cell      = ε/l_P         = %.6e N\n", F2_per_cell);
    std::printf("  F_total     = b × F/cell    = %.6e N\n", F2_total);
    std::printf("  g           = F/M           = %.6e m/s²\n", g2);
    std::printf("  Ratio to 9.81: %.6e\n\n", 9.81 / g2);

    // ═══════════════════════════════════════════════════════════
    // TEST 3: Φ per cell (full convergence), /3 trefoil
    // ═══════════════════════════════════════════════════════════
    std::printf("══ TEST 3: Φ per cell (full convergence), movement = 1/3 ══\n");
    double F3_per_cell = Phi / (3.0 * l_P);
    double F3_total    = b_cells * F3_per_cell;
    double g3          = F3_total / M_Earth;
    std::printf("  F/cell      = Φ/(3 l_P)     = %.6e N\n", F3_per_cell);
    std::printf("  F_total     = b × F/cell    = %.6e N\n", F3_total);
    std::printf("  g           = F/M           = %.6e m/s²\n", g3);
    std::printf("  Ratio to 9.81: %.6e\n\n", 9.81 / g3);

    // ═══════════════════════════════════════════════════════════
    // TEST 4: Full P_conv force, /3 trefoil, / c² movement budget
    // ═══════════════════════════════════════════════════════════
    std::printf("══ TEST 4: P_conv × l_P² / (3 c²) per cell ══\n");
    double F4_per_cell = P_conv * l_P2 / (3.0 * c * c);
    double F4_total    = b_cells * F4_per_cell;
    double g4          = F4_total / M_Earth;
    std::printf("  F/cell      = P l²/(3c²)   = %.6e N\n", F4_per_cell);
    std::printf("  F_total     = b × F/cell    = %.6e N\n", F4_total);
    std::printf("  g           = F/M           = %.6e m/s²\n", g4);
    std::printf("  Ratio to 9.81: %.6e\n\n", 9.81 / g4);

    // ═══════════════════════════════════════════════════════════
    // TEST 5: ε per tick, per cell, × (W+1)² = 16, / (3 c²) 
    // ═══════════════════════════════════════════════════════════
    std::printf("══ TEST 5: 16 × Φ / (l_P × m_p × c²) — trefoil G-test ══\n");
    double G_test = 16.0 * Phi / (l_P * m_p * c * c);
    double g5 = G_test * M_Earth / (R_E * R_E);
    std::printf("  G_SDT       = 16Φ/(l_P m_p c²) = %.6e\n", G_test);
    std::printf("  G_measured  = 6.674300e-11\n");
    std::printf("  Ratio       = %.6f\n", 6.6743e-11 / G_test);
    std::printf("  g = G_SDT × M/R² = %.6e m/s²\n", g5);
    std::printf("  Ratio to 9.81: %.6f\n\n", g5 / 9.81);

    // ═══════════════════════════════════════════════════════════
    // TEST 6: (4/π) × P_conv × 4π l_P² / (m_p c²) 
    // ═══════════════════════════════════════════════════════════
    std::printf("══ TEST 6: (4/π) × 4π P_conv l_P² / (m_p c²) ══\n");
    double G6 = (4.0 / std::numbers::pi) * 4.0 * std::numbers::pi * P_conv * l_P2 / (m_p * c * c);
    double g6 = G6 * M_Earth / (R_E * R_E);
    std::printf("  G_SDT       = %.6e\n", G6);
    std::printf("  G_measured  = 6.674300e-11\n");
    std::printf("  Ratio       = %.6f\n", 6.6743e-11 / G6);
    std::printf("  g = G_SDT × M/R² = %.6e m/s²\n", g6);
    std::printf("  Ratio to 9.81: %.6f\n\n", g6 / 9.81);

    // ═══════════════════════════════════════════════════════════
    // DIAGNOSTIC: What F/cell would give g = 9.81?
    // ═══════════════════════════════════════════════════════════
    std::printf("══ DIAGNOSTIC: Required values ══\n");
    double F_needed = 9.81 * M_Earth;
    double F_per_cell_needed = F_needed / b_cells;
    std::printf("  F_total needed    = %.6e N\n", F_needed);
    std::printf("  F/cell needed     = %.6e N\n", F_per_cell_needed);
    std::printf("  Φ/l_P (full)      = %.6e N  (ratio: %.6e)\n",
                Phi / l_P, F_per_cell_needed / (Phi / l_P));
    std::printf("  ε/l_P (per tick)  = %.6e N  (ratio: %.6e)\n",
                epsilon / l_P, F_per_cell_needed / (epsilon / l_P));
    std::printf("  ε/(3l_P) (trefoil)= %.6e N  (ratio: %.6e)\n",
                epsilon / (3.0 * l_P), F_per_cell_needed / (epsilon / (3.0 * l_P)));

    double ratio_eps = F_per_cell_needed / (epsilon / l_P);
    std::printf("\n  log10(ratio ε/l_P) = %.4f\n", std::log10(ratio_eps));
    std::printf("  log10(N)           = %.4f\n", std::log10(N));
    std::printf("  ratio/N            = %.6e\n", ratio_eps / N);
    std::printf("  ratio × N          = %.6e\n", ratio_eps * N);

    // Check: is the ratio close to M_Earth/(b × m_u)?
    double check1 = M_Earth / (b_cells * m_u);
    std::printf("  M/(b × m_u)        = %.6e\n", check1);
    // Check: is it close to 4πR²/b_l_P²?
    double check2 = 4.0 * std::numbers::pi * R_E * R_E / (b_cells * l_P2);
    std::printf("  4πR²/(b×l_P²)     = %.6e\n", check2);
    // Their product?
    std::printf("  check1 × check2    = %.6e\n", check1 * check2);

    // ═══════════════════════════════════════════════════════════
    // TEST 7: ε per tick × b_surface_steradian
    // Each excluded cell on the surface gets one ε per tick
    // from ONE steradian of the CMB, mapped to one steradian of Earth
    // ═══════════════════════════════════════════════════════════
    std::printf("\n══ TEST 7: Surface steradian mapping ══\n");
    double b_surface = n_baryons * ((V_disp_p + V_disp_n) / 2.0 + V_disp_e);
    double b_per_sr = b_cells / (4.0 * std::numbers::pi);
    std::printf("  b per steradian = %.6e excluded cells\n", b_per_sr);
    // CMB energy per steradian per tick:
    double E_per_sr_per_tick = epsilon;  // one shell, one sr → ε
    // Force per steradian: b_per_sr × ε/l_P
    double F_per_sr = b_per_sr * epsilon / l_P;
    std::printf("  F per sr = %.6e N\n", F_per_sr);
    // Total over 4π:
    double F7 = 4.0 * std::numbers::pi * F_per_sr;
    std::printf("  F total (4π sr) = %.6e N\n", F7);
    // Same as before, just confirming

    // ═══════════════════════════════════════════════════════════
    // TEST 8: What if per-tick ε gets ACCUMULATED over N ticks?
    // i.e., the force builds up over the causal history
    // ═══════════════════════════════════════════════════════════
    std::printf("\n══ TEST 8: ε accumulated × N = Φ (sanity check) ══\n");
    double F8 = b_cells * Phi / l_P;
    std::printf("  F = b × Φ/l_P = %.6e N   (this is 10^77)\n", F8);
    std::printf("  g = %.6e m/s²\n", F8 / M_Earth);
    std::printf("  With /3: g = %.6e m/s²\n", F8 / (3.0 * M_Earth));

    return 0;
}
