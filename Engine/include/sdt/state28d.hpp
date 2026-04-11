/**
 * @file state_28d.hpp
 * @brief 28-Dimensional State Manifold for Spatial Displacement Theory
 * 
 * Complete state vector describing any physical locus in SDT.
 * Organized into 7 hierarchical levels extending Euclidean geometry
 * to dynamic toroidal physics.
 * 
 * Reference: DE_RERUM_TODO_EXISTENS_COMPLETE.md, Chapter Addendum
 */

#ifndef SDT_STATE_28D_HPP
#define SDT_STATE_28D_HPP

#include <cmath>
#include <array>

// M_PI not guaranteed in C++ standard, define if needed
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace sdt {

/**
 * @brief 28-Dimensional State Vector (Ξ ∈ ℝ²⁸)
 * 
 * Hierarchical structure:
 * - Level 1 (1): Zero-Point - Existence
 * - Level 2 (2): Line - Position + Velocity  
 * - Level 3 (3): Plane - Boundaries + Rotation
 * - Level 4 (4): Sphere - Volume + Orientation
 * - Level 5 (5): Torus - Matter Structure (TOPOLOGY)
 * - Level 6 (6): Dynamism - Time Evolution (DYNAMICS)
 * - Level 7 (7): Energy - Force Manifestation (PHYSICS)
 */
struct State28D {
    // ===================================================================
    // LEVEL 1: ZERO-POINT (1 aspect)
    // ===================================================================
    
    double xi_0;  ///< Existence - baseline presence in spation medium
    
    // ===================================================================
    // LEVEL 2: LINE (2 aspects)
    // ===================================================================
    
    double xi_10;  ///< Location - position along axis [m]
    double xi_11;  ///< Relocation - linear velocity [m/s]
    
    // ===================================================================
    // LEVEL 3: PLANE (3 aspects)
    // ===================================================================
    
    double xi_p0;  ///< Internal existence - planar boundary (within/without)
    double xi_p1;  ///< Planar relocation - position within plane [m²]
    double xi_p2;  ///< Planar rotation - orientation in plane [rad]
    
    // ===================================================================
    // LEVEL 4: SPHERE (4 aspects)
    // ===================================================================
    
    double xi_s0;  ///< Shell existence - volumetric presence [m³]
    double xi_s1;  ///< Shell relocation - motion within volume [m³/s]
    double xi_s2;  ///< Shell rotation - rotational state [rad/s]
    double xi_s3;  ///< Orientation - axis direction [unit vector magnitude]
    
    // ===================================================================
    // LEVEL 5: TORUS (5 aspects) - MATTER STRUCTURE
    // ===================================================================
    
    double T_1;  ///< Central ring - constriction line, max compression [m]
    double T_2;  ///< Tube diameter - vortex thickness [m]
    double T_3;  ///< Topological surface - 2D boundary [m²]
    double T_4;  ///< Polarised volume - central aperture + pressure gradient [m³·Pa]
    double T_5;  ///< Aspect gradation - internal pressure/density gradient [Pa/m]
    
    // ===================================================================
    // LEVEL 6: DYNAMISM (6 aspects) - TIME EVOLUTION
    // ===================================================================
    
    double Phi_0;  ///< Omnidirectionality - all surface vectors [4π steradians]
    double Phi_1;  ///< Dynamic translocation - higher-order rates [m/s²]
    double Phi_2;  ///< Oscillation - periodic reversal/precession [Hz]
    double Phi_3;  ///< Inversion/chirality - handedness [±1]
    double Phi_4;  ///< State trajectory variance - potential from external influence [dimensionless]
    double Phi_5;  /// Phase transition - potential for structural change from external exchange [J]
    
    // ===================================================================
    // LEVEL 7: ENERGY (7 aspects) - FORCE MANIFESTATION
    // ===================================================================
    
    double eps_0;  ///< Potential - energy of position/configuration [J]
    double eps_1;  ///< Kinetic - energy of bulk motion [J]
    double eps_2;  ///< Rotational - energy of unencumbered motion [J]
    double eps_3;  ///< Field - energy in pressure-occlusion field [J]
    double eps_b;  ///< Binding energy - energy to decohere structure [J]
    double eps_4;  ///< Flux - rate of energy transfer [W]
    double eps_5;  ///< Transmission - mechanical transfer (sound, percussion) [J]
    
    // ===================================================================
    // GEOMETRIC CALCULATIONS
    // ===================================================================
    
    /**
     * @brief Calculate occlusion function E from Level 5 toroidal geometry
     * 
     * The occlusion function E ∈ [0,1] determines force type:
     * - E → 0: No screening → Coulomb force (full strength)
     * - E → 1: Complete screening → Gravity (heavily screened)
     * 
     * Depends on toroidal geometry (T₁, T₂, T₃, T₄, T₅) and separation.
     * 
     * @param other Another state vector (for mutual occlusion)
     * @param separation Distance between centers [m]
     * @return Occlusion factor E ∈ [0,1]
     */
    double calculate_occlusion(const State28D& other, double separation) const {
        // Solid angle calculation from topological surface T₃
        double self_radius_eff = std::sqrt(T_3 / (4.0 * M_PI));  // Effective radius from surface
        double other_radius_eff = std::sqrt(other.T_3 / (4.0 * M_PI));
        
        if (separation < 1e-30) return 0.0;  // Avoid division by zero
        
        // Mutual occlusion: solid angles
        double solid_angle_self = (self_radius_eff * self_radius_eff) / (separation * separation);
        double solid_angle_other = (other_radius_eff * other_radius_eff) / (separation * separation);
        
        // Eclipse fraction: Ω/(4π)
        double E_mutual = (solid_angle_self + solid_angle_other) / (4.0 * M_PI);
        
        // Additional screening from aspect gradation T₅ (internal shadowing)
        // Higher T₅ → more internal pressure variation → more self-screening
        double gradation_screening = std::tanh(std::abs(T_5) / 1e10);  // Normalize to ~1e10 Pa/m scale
        
        return std::min(1.0, E_mutual * (1.0 + gradation_screening));
    }
    
    /**
     * @brief Calculate force ratio: Coulomb / Gravity
     * 
     * From master equation: Different E values → different forces
     * F_C/F_g ≈ [(1-E_C)/(1-E_g)] × amplification
     * 
     * Atomic scale: E → 0 → Coulomb dominates
     * Bulk scale: E → 0.64 → Gravity (screened)
     * 
     * Expected ratio: ~10³⁹ for proton-electron vs bulk matter
     * 
     * @param E_coulomb Occlusion for Coulomb regime (typically ~0)
     * @param E_gravity Occlusion for gravity regime (typically ~0.64)
     * @param kappa_factor Geometric screening κ ≈ 10⁻⁹
     * @return Force ratio F_C/F_g
     */
    static double force_ratio_coulomb_to_gravity(
        double E_coulomb,
        double E_gravity,
        double kappa_factor = 1e-9
    ) {
        // Effective source strengths
        double rho_eff_coulomb = 1.0 - E_coulomb;  // ≈ 1 (full strength)
        double rho_eff_gravity = (1.0 - E_gravity) * kappa_factor;  // ≈ 0.36 × 10⁻⁹
        
        if (rho_eff_gravity < 1e-50) return 1e50;  // Avoid division by very small number
        
        // CMB pressure amplification factor for Coulomb (~10³⁰)
        const double cmb_amplification = 1e30;
        
        double ratio = (rho_eff_coulomb / rho_eff_gravity) * cmb_amplification;
        
        return ratio;
    }
    
    /**
     * @brief Calculate accessible phase space volume (related to Φ₄)
     * 
     * Φ₄ measures configuration complexity through external interactions.
     * Higher Φ₄ → more accessible states → richer response to environment
     * 
     * Approximation: Φ₄ ≈ log(accessible volume / current volume)
     * 
     * @return Logarithm of accessible state count
     */
    double accessible_phase_space_volume() const {
        // Base volume from toroidal structure (Level 5)
        double structure_volume = T_1 * T_2 * T_2;  // Ring × tube²
        
        // Dynamism contribution (Level 6)
        // Higher Phi_4 directly → more variance → more accessible states
        double variance_factor = 1.0 + std::abs(Phi_4);
        
        // Phase transition potential (Phi_5) opens new regions
        double transition_factor = 1.0 + std::abs(Phi_5) / 1e-20;  // Normalize to ~1e-20 J scale
        
        // Energy distribution (Level 7) - more energy modes → more states
        double energy_modes = 1.0;
        if (eps_0 > 0) energy_modes += 1;  // Potential
        if (eps_1 > 0) energy_modes += 1;  // Kinetic
        if (eps_2 > 0) energy_modes += 1;  // Rotational
        
        // Total accessible volume (log scale)
        double log_accessible = std::log(structure_volume) 
                               + std::log(variance_factor)
                               + std::log(transition_factor)
                               + std::log(energy_modes);
        
        return log_accessible;
    }
    
    /**
     * @brief Get all 28 components as array (for numerical integration)
     */
    std::array<double, 28> to_array() const {
        return {{
            // Level 1 (1)
            xi_0,
            // Level 2 (2)
            xi_10, xi_11,
            // Level 3 (3)
            xi_p0, xi_p1, xi_p2,
            // Level 4 (4)
            xi_s0, xi_s1, xi_s2, xi_s3,
            // Level 5 (5)
            T_1, T_2, T_3, T_4, T_5,
            // Level 6 (6)
            Phi_0, Phi_1, Phi_2, Phi_3, Phi_4, Phi_5,
            // Level 7 (7)
            eps_0, eps_1, eps_2, eps_3, eps_b, eps_4, eps_5
        }};
    }
    
    /**
     * @brief Set from array (for numerical integration)
     */
    void from_array(const std::array<double, 28>& arr) {
        size_t i = 0;
        // Level 1
        xi_0 = arr[i++];
        // Level 2
        xi_10 = arr[i++]; xi_11 = arr[i++];
        // Level 3
        xi_p0 = arr[i++]; xi_p1 = arr[i++]; xi_p2 = arr[i++];
        // Level 4
        xi_s0 = arr[i++]; xi_s1 = arr[i++]; xi_s2 = arr[i++]; xi_s3 = arr[i++];
        // Level 5
        T_1 = arr[i++]; T_2 = arr[i++]; T_3 = arr[i++]; T_4 = arr[i++]; T_5 = arr[i++];
        // Level 6
        Phi_0 = arr[i++]; Phi_1 = arr[i++]; Phi_2 = arr[i++];
        Phi_3 = arr[i++]; Phi_4 = arr[i++]; Phi_5 = arr[i++];
        // Level 7
        eps_0 = arr[i++]; eps_1 = arr[i++]; eps_2 = arr[i++];
        eps_3 = arr[i++]; eps_b = arr[i++]; eps_4 = arr[i++]; eps_5 = arr[i++];
    }
    
    /**
     * @brief Zero-initialize all components
     */
    State28D() : 
        xi_0(0), xi_10(0), xi_11(0),
        xi_p0(0), xi_p1(0), xi_p2(0),
        xi_s0(0), xi_s1(0), xi_s2(0), xi_s3(0),
        T_1(0), T_2(0), T_3(0), T_4(0), T_5(0),
        Phi_0(0), Phi_1(0), Phi_2(0), Phi_3(0), Phi_4(0), Phi_5(0),
        eps_0(0), eps_1(0), eps_2(0), eps_3(0), eps_b(0), eps_4(0), eps_5(0)
    {}
};

/**
 * @brief Factory functions for common configurations
 */
namespace state_factory {
    
    /**
     * @brief Create electron state (atomic scale)
     */
    inline State28D electron_atomic() {
        State28D e;
        e.xi_0 = 1.0;  // Exists
        e.T_2 = 2.43e-12;  // Compton wavelength
        e.T_3 = 4.0 * M_PI * e.T_2 * e.T_2;  // Surface area
        e.Phi_3 = -1.0;  // Chirality (spin)
        return e;
    }
    
    /**
     * @brief Create proton state (nuclear scale)
     */
    inline State28D proton_nuclear() {
        State28D p;
        p.xi_0 = 1.0;  // Exists
        p.T_2 = 0.84e-15;  // Proton radius
        p.T_3 = 4.0 * M_PI * p.T_2 * p.T_2;  // Surface area
        p.Phi_3 = +1.0;  // Chirality (opposite electron)
        return p;
    }
}

} // namespace sdt

#endif // SDT_STATE_28D_HPP
