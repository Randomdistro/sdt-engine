/**
 * @file cq17_mass_ratio_solver.cpp
 * @brief CQ17: Deriving Proton-Electron Mass Ratio from Pure Topology
 *
 * This solver computes the geometric properties of the W=1 (electron)
 * and W=3 (proton) topological defects, searching for the strict
 * geometric constraint that locks their displacement volumes to a ratio
 * of 1836.15.
 */

#include <cstdio>
#include <cmath>
#include <numbers>
#include <vector>
#include <string>

constexpr double pi = std::numbers::pi;

// Numerical integration of the curve length of a (p,q) torus knot
// R = major radius, a = minor radius
double knot_length(int p, int q, double R, double a, int steps = 100000) {
    double L = 0.0;
    double dt = 2.0 * pi / steps;
    for (int i = 0; i < steps; ++i) {
        double t = i * dt;
        double t_next = (i + 1) * dt;

        // dx/dt, dy/dt, dz/dt formulation:
        // x = (R + a cos(qt)) cos(pt)
        // y = (R + a cos(qt)) sin(pt)
        // z = a sin(qt)
        // ds = sqrt( p^2(R + a cos(qt))^2 + q^2 a^2 ) dt
        
        // Midpoint integration
        double tm = t + dt / 2.0;
        double ds = std::sqrt( p * p * (R + a * std::cos(q * tm)) * (R + a * std::cos(q * tm)) + q * q * a * a );
        L += ds * dt;
    }
    return L;
}

int main() {
    std::printf("╔══════════════════════════════════════════════════════════════╗\n");
    std::printf("║  CQ17: PROTON-ELECTRON MASS RATIO SOLVER                   ║\n");
    std::printf("║  Target Ratio: 1836.15267                                    ║\n");
    std::printf("╚══════════════════════════════════════════════════════════════╝\n\n");

    std::printf("  PHASE 1: TOROIDAL PARAMETRIZATION (W=1)\n");
    std::printf("  ────────────────────────────────────────────────────────────\n");
    // W=1: Simple Torus (1,1)
    int p1 = 1, q1 = 1;
    double R1 = 1.0; // Normalized
    double a1 = R1;  // For W=1, v_T = v_P -> R/a = 1
    
    double V_torus_1 = 2.0 * pi * pi * R1 * a1 * a1;
    double L1 = knot_length(p1, q1, R1, a1);
    double V_tube_1 = pi * a1 * a1 * L1; // Assuming tube fills minor radius
    
    std::printf("    W=1 (1,1) Horn Torus (R=1):\n");
    std::printf("      a1 = %.4f R1\n", a1/R1);
    std::printf("      V_torus_1 = %.4f R1^3\n", V_torus_1);
    std::printf("      L1 (curve) = %.4f R1\n", L1);
    std::printf("      V_tube_1  = %.4f R1^3\n\n", V_tube_1);


    std::printf("  PHASE 2: TREFOIL PARAMETRIZATION (W=3)\n");
    std::printf("  ────────────────────────────────────────────────────────────\n");
    // W=3: Trefoil Knot (2,3)
    int p3 = 2, q3 = 3;
    double R3 = 1.0; // Normalized
    // From CQ02/CQ10b: R/a = (p/q) * (v_P/v_T) = (2/3) * sqrt(3/2) = sqrt(2/3) = 0.816496
    // So a = R * sqrt(3/2) = R * 1.2247
    // Wait! In cq10b_torus_derives_mass.cpp:
    // v_T = c*sqrt(p/(p+q)) = c*sqrt(2/5)
    // v_P = c*sqrt(q/(p+q)) = c*sqrt(3/5)
    // knot closure: p * 2*pi*R / v_T = q * 2*pi*a / v_P
    // a = R * (p/q) * (v_P/v_T) = R * (2/3) * sqrt(3/2) = R * sqrt(2/3) = 0.816496 R
    double a3 = R3 * std::sqrt(2.0 / 3.0); 
    
    double V_torus_3 = 2.0 * pi * pi * R3 * a3 * a3;
    double L3 = knot_length(p3, q3, R3, a3);
    double V_tube_3 = pi * a3 * a3 * L3; 
    
    std::printf("    W=3 (2,3) Trefoil Knot (R=1):\n");
    std::printf("      a3 = %.6f R3  (sqrt(2/3))\n", a3/R3);
    std::printf("      V_torus_3 = %.6f R3^3\n", V_torus_3);
    std::printf("      L3 (curve) = %.6f R3\n", L3);
    std::printf("      V_tube_3  = %.6f R3^3\n\n", V_tube_3);


    std::printf("  PHASE 3: THE RATIO MAPPING\n");
    std::printf("  ────────────────────────────────────────────────────────────\n");
    std::printf("    If we assume R1 = R3 (Equal Major Radii):\n");
    std::printf("      Ratio of V_torus: %.6f\n", V_torus_3 / V_torus_1);
    std::printf("      Ratio of V_tube:  %.6f\n\n", V_tube_3 / V_tube_1);

    std::printf("    If we assume a1 = a3 (Equal Flux Tube Cross Section):\n");
    // If a1 = a3, then R1 = a1 = a3 = R3 * sqrt(2/3)
    // So R3 / R1 = sqrt(3/2) = 1.2247
    double scale_R3 = std::sqrt(1.5);
    double V_torus_3_scaled = V_torus_3 * std::pow(scale_R3, 3);
    double V_tube_3_scaled = V_tube_3 * std::pow(scale_R3, 3);
    std::printf("      Ratio of V_torus: %.6f\n", V_torus_3_scaled / V_torus_1);
    std::printf("      Ratio of V_tube:  %.6f\n\n", V_tube_3_scaled / V_tube_1);
    
    std::printf("    If we assume L1 = L3 (Equal Flux Tube Length):\n");
    double scale_L = L1 / L3;
    double V_tube_3_Lscaled = V_tube_3 * std::pow(scale_L, 3);
    std::printf("      Ratio of V_tube:  %.6f\n\n", V_tube_3_Lscaled / V_tube_1);

    std::printf("  PHASE 4: SEARCHING FOR 1836.15\n");
    std::printf("  ────────────────────────────────────────────────────────────\n");
    
    std::printf("    Target: 1836.15267\n");
    std::printf("    Topological constant 6 * pi^5 = %.5f\n", 6.0 * std::pow(pi, 5));
    std::printf("    Topological constant (3/2)^(3/2) * 1000 = %.5f\n\n", std::pow(1.5, 1.5) * 1000.0);
    
    std::printf("    Is there a combination of geometric properties that yields 1836.15?\n");
    
    // Testing purely analytical topological ratios
    // V_torus_3 / V_torus_1 = (2 pi^2 R3 a3^2) / (2 pi^2 R1 a1^2)
    // If we map topological phase space:
    // Trefoil total winding = 4pi + 6pi = 10pi
    // Simple loop total winding = 2pi
    // Ratio of total winding = 5
    
    // Check various pi combinations
    std::vector<std::pair<const char*, double>> targets = {
        {"6 * pi^5", 6.0 * std::pow(pi, 5)},
        {"2 * pi * 300", 2.0 * pi * 300.0},
        {"V_tube_1 * 60", V_tube_1 * 60.0},
        {"(a1/a3)^13", std::pow(a1/a3, 13)}, // arbitrary
        {"pi^6 / (sqrt(2/3))", std::pow(pi, 6) / std::sqrt(2/3.0)}
    };
    
    for(auto& t : targets) {
        std::printf("    %-25s = %10.5f  (Diff: %+.4f%%)\n", 
            t.first, t.second, 100.0 * (t.second - 1836.15267) / 1836.15267);
    }
    
    // If mass is defined by the number of spations in the flux tube:
    // M = V_tube / l_P^3
    // Ratio = V_tube_p / V_tube_e
    
    std::printf("    If the mass ratio IS exactly 6*pi^5, what geometric condition forces this?\n");
    std::printf("    6*pi^5 = 3 * (2*pi^2) * pi^3\n");
    std::printf("    The volume of a 3-sphere surface is 2*pi^2 * r^3.\n\n");

    std::printf("  PHASE 5: EXHAUSTIVE TOPOLOGICAL SEARCH\n");
    std::printf("  ────────────────────────────────────────────────────────────\n");
    double best_diff = 1000.0;
    std::string best_expr = "";
    
    // Search powers of 2, 3, pi, e
    for (int p_pow = -6; p_pow <= 6; ++p_pow) {
        for (int q_pow = -6; q_pow <= 6; ++q_pow) {
            for (int pi_pow = -6; pi_pow <= 6; ++pi_pow) {
                for (int c_pow = -2; c_pow <= 4; ++c_pow) {
                    double val = std::pow(2.0, p_pow) * std::pow(3.0, q_pow) * std::pow(pi, pi_pow);
                    if (c_pow != 0) val *= std::pow(V_torus_3 / V_torus_1, c_pow);
                    
                    double diff = std::abs(val - 1836.15267);
                    if (diff < best_diff && diff < 5.0) {
                        best_diff = diff;
                        char buf[100];
                        std::snprintf(buf, sizeof(buf), "2^%d * 3^%d * pi^%d * (V3/V1)^%d", p_pow, q_pow, pi_pow, c_pow);
                        best_expr = buf;
                    }
                }
            }
        }
    }
    std::printf("    Closest simple topological expression:\n");
    std::printf("    %s   (diff from 1836.15267: %.5f)\n", best_expr.c_str(), best_diff);
    
    return 0;
}
