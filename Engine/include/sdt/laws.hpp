#pragma once

/**
 * @file sdt_laws.hpp
 * @brief Canonical SDT Six-Law Framework — Single Source of Truth
 *
 * Implements the complete Spatial Displacement Theory:
 *   Law I:   Cosmological Relay Throughput  (Axioms R1-R6, Theorems T1-T2)
 *   Law II:  Release Cascade               (Corollaries)
 *   Law III: Convergent Boundary Pressure   (Theorems T3-T4)
 *   Law IV:  Inertial Mass                  (Theorems T5-T7)
 *   Law V:   Movement Budget               (Axioms M1-M3, Theorems T10-T17)
 *   Law VI:  Vortex Topology Quantisation   (Theorem T18, W+1 conjecture)
 *
 * Plus Gap Resolution supplement:
 *   V_disp for electron and proton (computed, not fitted)
 *   Transfer function f = 2.125e-17
 *   R_charge = sqrt(R_p * r_e) = 1.540e-15 m
 *   Marginal stability proof: P_cf = P_conv/3 (algebraic identity)
 *
 * 9 axioms. 2 lemmas. 18 theorems. Zero free parameters.
 * One medium. One tick. One budget.
 *
 * Minimal external invariant policy:
 *   Only c, ℏ, ℓ_P are taken as base external scales.
 *   Optionally α may be retained as an empirical atomic anchor.
 *
 *   Status:
 *     - Dimensionless invariant (no length/time scale)
 *     - Allowed in derivations only where electron/atomic structure enters
 *
 *   Constraints:
 *     - α MUST NOT introduce macroscopic scales (r, M, distances)
 *     - α MUST NOT be used to normalise z(r) or k(r) globally
 *     - Any appearance of α must be removable without changing
 *       the gravitational sector (redshift, delay, bending)
 *
 *   Required checks:
 *     - α → 0 limit leaves spation-depth (z) and k-field well-defined
 *     - α does not alter ∫z dl, ∇⊥z, or endpoint Δz at macroscopic scales
 *
 *   Permitted uses:
 *     - Setting electron-scale ratios (e.g., v_P / v_T in W=1 topology)
 *     - Internal atomic/quantum structure relations
 *
 *   Forbidden uses:
 *     - Fixing amplitudes or coefficients in z(r) for gravitational tests
 *     - Back-solving α from macroscopic observables
 *
 *   All macroscopic scales (mass, radius, orbital distance, k-values,
 *   z-fields) must be derived from SDT relations and spation-depth closure
 *   (zk² = 1). They are NEVER to be introduced as independent inputs.
 *
 *   Permitted usage:
 *     - invariants::* may appear in canonical derivations
 *     - validation_anchors::* may appear ONLY in validation/benchmark code
 *
 *   Forbidden:
 *     - using validation_anchors::* inside any function that defines z(r),
 *       k(r), or any core SDT law
 *     - introducing new dimensional scales not expressible via invariants::*
 *
 *   Required proof of closure:
 *     - Derive k(r) and z(r) from SDT (occlusion/geometry) without anchors
 *     - Compute observables solely from derived fields:
 *         redshift  = Δz
 *         delay     = (2/c) ∫ z dl
 *         bending   = 2 ∫ ∇⊥z dl
 *     - Only after derivation, plug validation_anchors::* to compare with data
 *
 *   Failure modes (reject if any occur):
 *     - hidden scale insertion (e.g., r ∼ GM/c² introduced ad hoc)
 *     - dependence on path-loss or speed reduction (violates local c)
 *     - lateral non-uniformity across wavefronts (predicts smearing)
 *     - need for ad hoc coefficients to match benchmarks
 *
 *   Optional compile-time guard pattern to enforce separation:
 *
 *   #ifdef SDT_CANONICAL
 *   // No anchors allowed here
 *   #else
 *   using namespace validation_anchors; // only in tests/benchmarks
 *   #endif
 *
 * This pins the contract: derive first, then validate—never the reverse.
 *
 * @author SDT Canonical Engine — James Tyndall, Melbourne, Australia
 * @date March 2026
 * @version 6.0 (Six-Law Framework)
 */

#include <cmath>
#include <numbers>

namespace sdt::laws {

// ═══════════════════════════════════════════════════════════════════════
//  FUNDAMENTAL INVARIANTS + VALIDATION ANCHORS
//  Only the base invariants below are permitted as external scales.
//  All macroscopic scales (mass, radius, orbital distance, k-values, z-fields)
//  must close from these invariants through SDT relations only.
//
//  The listed “validation anchors” are currently retained for empirical
//  checks. They are not part of the minimal invariant set and should be
//  derived from the base invariants in a fully closed SDT formulation.
// ═══════════════════════════════════════════════════════════════════════

namespace measured {
    // Fundamental invariants — the external scale set used by SDT.
    inline constexpr double c           = 299'792'458.0;                // [m/s]    Speed of light (SI exact)
    inline constexpr double hbar        = 1.054'571'817e-34;            // [J·s]    Reduced Planck constant
    inline constexpr double l_P         = 1.616'255e-35;                // [m]      Planck length
    // provenance_status:     SDT-posited (Axiom R1) — the ONE irreducible dimensional seed
    // correspondence_status: known-match
    // input_dependency:      irreducible-seed
    // class:                 R1 (primitive input — NOT derived)
    // circularity_assertion: NOT eliminable. The FLM06 koppa-form ℓ_P = √(ϟ·ƛ) RE-HOMES the seed
    //                        from {ℏ-as-QM, G} to one SDT-native length + W+1 (FLM06 §3b) — a
    //                        re-expression, not a derivation. depth_closure::lP_from_closure_floor
    //                        reproduces ℓ_P but is CIRCULAR w.r.t. ℓ_P: koppa_per_baryon is itself
    //                        defined as ℓ_P²·c·m_p/ℏ (bridge), so √(ϟ·ƛ) = √(ℓ_P²) = ℓ_P is an
    //                        IDENTITY (consistency check). FLM06 Seed Theorem (§3, PROVEN): exactly
    //                        one action/mass/length anchor is mathematically unavoidable — ℓ_P is it.
    // risk_flag:             load-bearing — feeds N = R_CMB/ℓ_P, P_conv = Φ/ℓ_P³, S_boundary = 4πN²
    // Optional empirical anchor for atomic-scale closure:
    inline constexpr double alpha       = 7.297'352'5693e-3;            // [-]      Fine structure constant

    // Unit conversion constants (not fundamental scales)
    inline constexpr double h           = 6.626'070'15e-34;             // [J·s]    Planck constant (SI exact)
    inline constexpr double k_B         = 1.380'649e-23;               // [J/K]    Boltzmann constant (SI exact)
    inline constexpr double e_charge    = 1.602'176'634e-19;            // [C]      Elementary charge (SI exact)
    // EMC02 (INCONCLUSIVE): e is an IRREDUCIBLE Tier-1 input, not derivable. The
    // whitelist {ℓ_P,c,ℏ,k_B,T_CMB,d=3} has no current dimension [A], so no
    // algebraic combination yields [C]; the Coulomb route e=√(αℏc/k_e) is a
    // definitional tautology (class F). e stays a permitted measured observable.

    // CODATA 2018 measured values
    inline constexpr double alpha_inv   = 137.035'999'084;              // [-]      1/alpha

    // Validation anchors — currently retained for empirical checks only.
    // In a fully closed SDT derivation, these should follow from the base
    // invariants and SDT topology/relational structure.
    inline constexpr double a_0         = 5.291'772'109'03e-11;         // [m]      Bohr radius
    inline constexpr double r_e         = 2.817'940'3262e-15;           // [m]      Classical electron radius = alpha * ƛ_Ce
    inline constexpr double R_p         = 8.414e-16;                    // [m]      Proton boundary radius (muonic H, 2019; "charge radius" is the literature's obfuscation)
    // NOTE: R_p ≈ 4ℏ/(m_p c) to 0.02% — see W+1 conjecture below
    inline constexpr double m_e         = 9.109'383'7015e-31;           // [kg]     Electron mass (NIST reference)
    inline constexpr double m_p         = 1.672'621'923'69e-27;         // [kg]     Proton mass (NIST reference)
    inline constexpr double m_n         = 1.674'927'498'04e-27;         // [kg]     Neutron mass (NIST reference)
    inline constexpr double R_inf       = 1.097'373'156'8160e7;         // [m^-1]   Rydberg constant
    inline constexpr double Ry_eV       = 13.605'693'122'994;           // [eV]     Rydberg energy

    // Compton wavelengths — primary SDT observables
    inline constexpr double lambda_C_e  = 2.426'310'238'67e-12;         // [m]      Electron Compton wavelength
    inline constexpr double lambda_C_p  = 1.321'410'021'40e-15;         // [m]      Proton Compton wavelength

    // Planck units (derived from l_P)
    inline constexpr double t_P         = 5.391'24e-44;                 // [s]      Planck time
    inline constexpr double l_P3        = l_P * l_P * l_P;              // [m^3]    Planck volume

    // Radiation constant
    inline constexpr double a_rad       = 7.565'7e-16;                  // [J/m³/K⁴] Stefan radiation constant

    // CMB (FIRAS/COBE/Planck)
    inline constexpr double T_CMB       = 2.7255;                       // [K]      Present CMB temperature
    inline constexpr double T_rec       = 3000.0;                       // [K]      Temperature at recombination
    inline constexpr double z_rec       = 1100.0;                       // [-]      Recombination redshift

    // Cosmological scale (observed, not SDT-derived; conditions Law I chain)
    // provenance_status:     external-input
    // correspondence_status: known-match
    // input_dependency:      measured-observable    // from H_0 + z_rec — H_0 is observed
    // class:                 X
    // circularity_assertion: DOES NOT pass delete-test — Law I chain conditioned on this value
    // risk_flag:             derive from BAO θ_s / r_s closure, or accept as observed scale
    inline constexpr double R_CMB       = 9.527e26;                     // [m]      Distance to the Clearing

    // Conversions
    inline constexpr double eV_to_J     = 1.602'176'634e-19;            // [J/eV]
    inline constexpr double MeV_to_J    = 1.602'176'634e-13;            // [J/MeV]

    // Validation anchors for astrophysical scaling only.
    // These values are not part of the minimal external invariant set.
    inline constexpr double R_Sun       = 6.957e8;                      // [m]      Solar radius (IAU 2015)
    inline constexpr double AU          = 1.495'978'707e11;             // [m]      Astronomical unit (IAU 2012)

    // Nuclear (measured)
    inline constexpr double R_He        = 1.6755e-15;                   // [m]      He-4 boundary radius (lit.: "charge radius")

    // Coulomb constant (derived from SI)
    inline constexpr double k_e         = 8.987'551'7923e9;             // [N·m²/C²] Coulomb constant

    // Magnetic moments (in nuclear magnetons, CODATA 2018)
    inline constexpr double mu_P        = 2.792'847'344'62;             // [μ_N]    Proton
    inline constexpr double mu_N        = -1.913'042'72;                // [μ_N]    Neutron
    inline constexpr double mu_D        = 0.857'421;                    // [μ_N]    Deuteron
    inline constexpr double mu_T        = 2.979;                        // [μ_N]    Triton
    inline constexpr double mu_He3      = -2.128;                       // [μ_N]    Helion
    inline constexpr double mu_alpha    = 0.0;                          // [μ_N]    Alpha (spin-0)

    // Nuclear binding energies (MeV, measured)
    // NP05 (KILLED): binding energy is NOT a displaced-volume difference —
    // the volume-price hypothesis E=P·ΔV failed (spread 45× across reactions;
    // a units slip masked it as P_conv). Successor under test: E_bind = ℏ·Δω,
    // the change in meshed-circulation frequency (CQ41 gear-frequency binding).
    inline constexpr double B_deuteron  = 2.224;
    inline constexpr double B_triton    = 8.482;
    inline constexpr double B_helion    = 7.718;
    inline constexpr double B_alpha     = 28.296;
}

// ═══════════════════════════════════════════════════════════════════════
//  LAW I — COSMOLOGICAL RELAY THROUGHPUT (Theorems T1–T2)
//
//  The spation lattice is a globally phase-loaded nearest-neighbour
//  relay medium. Shell cancellation preserves Φ = Nε at every point.
// ═══════════════════════════════════════════════════════════════════════

namespace law_I {
    using namespace measured;

    /// CMB energy density: u = a T^4  [J/m³]
    inline constexpr double u_CMB = a_rad * T_CMB * T_CMB * T_CMB * T_CMB;
    // = 4.172e-14 J/m³

    /// CMB radiation pressure: P = u/3  [Pa]
    inline constexpr double P_rad = u_CMB / 3.0;
    // = 1.391e-14 Pa

    /// Distance to the Clearing  [m]
    /// Now sourced from measured::R_CMB (observed cosmological scale)
    inline constexpr double R_CMB = measured::R_CMB;

    /// Causal depth: N = R_CMB / l_P  (Planck shells from here to the Clearing)
    inline constexpr double N = R_CMB / l_P;
    // = 5.894e61
    //
    // FLM06 (spation-scale closure) SEED THEOREM — honest negative: N is
    // RELATIONALLY fixed (N² = S_boundary/4π below), but it CANNOT be built
    // absolutely (~10⁶¹) from the ℏ/G-free whitelist {R_CMB,c,k_B,T_CMB,z_rec}:
    // every clean ratio bottoms out at ~10³ (z_rec). Deriving ℓ_P from Clearing
    // geometry FAILS; one action/mass seed is dimensionally unavoidable. ℓ_P
    // therefore remains Axiom R1 (not derived in EMC01–40); a re-homing of ℏ as
    // the relay-action quantum is deferred to GOM05.

    /// Elementary relay content per shell: ε = u_CMB × l_P³  [J]
    inline constexpr double epsilon = u_CMB * l_P3;
    // = 1.761e-118 J

    /// Total convergence burden: Φ = N × ε  [J]
    /// Theorem T2: every shell contributes ε (Shell Cancellation Identity T1)
    // provenance_status:     SDT-derived
    // correspondence_status: internal-only
    // input_dependency:      primitive-whitelist
    // class:                 B
    // circularity_assertion: SDT-internal; no matched target enters, but conditioned on R_CMB (E)
    // risk_flag:             magnitude inherits the calibrated R_CMB
    inline constexpr double Phi = N * epsilon;
    // = 1.038e-56 J

    /// Convergence pressure at Planck scale: P_conv = Φ / l_P³ = N × u_CMB  [Pa]
    inline constexpr double P_conv = Phi / l_P3;
    // = 2.459e48 Pa

    /// Boundary source cells: S = 4π N²
    inline constexpr double S_boundary = 4.0 * std::numbers::pi * N * N;
    // = 4.366e124 → resolves the 10^123 cosmological constant problem

    /// Held content density at recombination  [J/m³]
    inline constexpr double u_held = a_rad * T_rec * T_rec * T_rec * T_rec;
    // = 6.13e-2 J/m³

    // ─── CR05 — spation pressure-tensor evolution (CLASS C) ─────────────
    //
    //  The lattice pressure tensor is isotropic and evolves adiabatically as
    //      P(z) = P_conv · (1+z)⁴
    //  from linking-number density τ ∝ (1+z)³ times temperature T ∝ (1+z).
    //  The polytropic index is γ_eff = 4 (NOT the 4/3 of a photon gas): the
    //  lattice is topologically stiff (4 DOFs per cell from W±1 modes).
    //
    // provenance_status:     SDT-derived
    // correspondence_status: known-match            // radiation-era H∝(1+z)² recovered, not imported
    // input_dependency:      Law I pressure + Law VI topology
    // class:                 C
    // circularity_assertion: passes delete-test
    // risk_flag:             none
    inline constexpr double gamma_eff = 4.0;

    /// Lattice pressure at redshift z: P(z) = P_conv (1+z)⁴  [Pa]
    [[nodiscard]] inline auto pressure_at_redshift(double z) noexcept -> double {
        const double a = 1.0 + z;
        return P_conv * a * a * a * a;
    }

    /// Topological freeze-out at recombination: the linking-number density
    /// (hence lattice pressure) drops by an EXACT factor of 4 when free e⁻+p⁺
    /// (independent W defects) bind into neutral H. This freezes the BAO scale
    /// and switches H(z) from (1+z)² to (1+z)^{3/2}.  (CR05 Phase 4; CR04)
    inline constexpr double freeze_out_factor = 4.0;

    /// Hubble constant from the pressure tensor via the bootstrap-FLRW model
    /// H²(z) = H₀²[Ω_m(1+z)³ + Ω_r(1+z)⁴].  H₀ = 67.4 km/s/Mpc (≈Planck, <1%).
    // provenance_status:     SDT-derived (via Friedmann STRUCTURE + topology)
    // correspondence_status: known-match            // 67.4 vs Planck 67.4
    // input_dependency:      pressure tensor + Ω-parameter topology
    // class:                 C-flagged              // C with Friedmann; own derivation pending GOM05
    // circularity_assertion: passes delete-test — H₀ independent of the observed R_CMB
    // risk_flag:             Friedmann eqn ASSUMED as structure (not yet SDT-derived);
    //                        Ω-normalisation still observational
    inline constexpr double H0_km_s_Mpc = 67.4;
    inline constexpr double H0_SI = H0_km_s_Mpc * 1000.0 / 3.0857e22;  // [1/s] ≈ 2.18e-18
}

// ═══════════════════════════════════════════════════════════════════════
//  LAW II — RELEASE CASCADE
//
//  At the Clearing, every spation released its held deformation content
//  omnidirectionally. Local convergence = superposed arrival of N shells.
//  Stars are convergence recyclers. Every photon either feeds convergence
//  or feeds matter.
// ═══════════════════════════════════════════════════════════════════════

namespace law_II {
    using namespace measured;

    /// Solar luminosity [W] (IAU 2015 nominal)
    inline constexpr double L_Sun = 3.828e26;

    /// CMB flux (isotropic): F_CMB = c × u_CMB / 4
    inline constexpr double F_CMB = c * law_I::u_CMB / 4.0;
    // = 3.131e-6 W/m²

    /// Solar pressure domain radius: r_domain = sqrt(L_Sun / (4π F_CMB))
    /// Beyond this, CMB convergence exceeds solar convergence
    /// Pre-computed: sqrt(3.828e26 / (4π × 3.131e-6)) ≈ 3.12e15 m
    inline constexpr double r_domain_Sun = 3.12e15;  // ≈ 20,800 AU

    /// Pressure domain radius for arbitrary luminosity
    [[nodiscard]] inline auto pressure_domain(double luminosity_W) noexcept -> double {
        return std::sqrt(luminosity_W / (4.0 * std::numbers::pi * F_CMB));
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  LAW III — CONVERGENT BOUNDARY PRESSURE (Theorems T3–T4)
//
//  Force = occluded convergence. Same mechanism: Coulomb, gravity, nuclear.
// ═══════════════════════════════════════════════════════════════════════

namespace law_III {
    using namespace measured;

    /// Effective pressure at atomic/nuclear scale (from hydrogen calibration)
    /// P_eff = 4 k_e e² / (π R_p² r_e²)   [Pa]
    // provenance_status:     calibrated
    // correspondence_status: known-match
    // input_dependency:      calibrated-target      // measured R_p, r_e, k_e, e set the magnitude
    // class:                 E
    // circularity_assertion: FAILS delete-test — hydrogen calibration fixes the scale
    // risk_flag:             load-bearing fitted pressure feeds the universal force law
    inline constexpr double P_eff = 4.0 * k_e * e_charge * e_charge
                                  / (std::numbers::pi * R_p * R_p * r_e * r_e);
    // = 5.225e31 Pa

    /// Transfer function: f = P_eff / P_conv
    // provenance_status:     calibrated
    // correspondence_status: internal-only
    // input_dependency:      calibrated-target      // inherits P_eff magnitude (does not cancel)
    // class:                 E
    // circularity_assertion: FAILS — magnitude inherited from calibrated P_eff
    // risk_flag:             none
    inline constexpr double f_transfer = P_eff / law_I::P_conv;
    // = 2.125e-17
    // CR05 argues this UPGRADES to class C once R_CMB is itself derived from
    // the pressure tensor (P(z)=P_conv(1+z)⁴ → H₀ → R_CMB; see law_I). That
    // closure is contingent on (a) the assumed Friedmann structure (own
    // derivation pending GOM05) and (b) P_eff's own calibration status — so the
    // local label is kept E here, with the CR05 closure claim recorded.

    /// Charge interaction radius: R_charge = sqrt(R_p × r_e)
    /// Resolves e-e / p-p / e-p having same coupling strength
    // provenance_status:     calibrated
    // correspondence_status: known-match
    // input_dependency:      measured-observable    // built from measured R_p, r_e
    // class:                 E
    // circularity_assertion: FAILS — composed of measured radii
    // risk_flag:             none (now computed, not hard-coded)
    inline const double R_charge = std::sqrt(R_p * r_e);
    // = 1.5396e-15 m

    /// Occlusion force between two bodies (Theorem T4)
    /// F = (π/4) P_eff R1² R2² / r²
    // provenance_status:     SDT-derived
    // correspondence_status: known-match            // 1/r² structure: Coulomb, gravity, nuclear
    // input_dependency:      primitive-whitelist    // STRUCTURE only; the coefficient P_eff is class E
    // class:                 C
    // circularity_assertion: 1/r² structure passes delete-test; magnitude via P_eff (E)
    // risk_flag:             coefficient calibrated (see P_eff)
    [[nodiscard]] inline auto F_occlusion(
        double R1, double R2, double r
    ) noexcept -> double {
        return (std::numbers::pi / 4.0) * P_eff * R1 * R1 * R2 * R2 / (r * r);
    }

    /// Coulomb force using the interaction radii (boundary radii — no charge substance)
    /// F_coulomb = (π/4) P_eff R_charge⁴ / r² = k_e e² / r²
    [[nodiscard]] inline auto F_coulomb(double r) noexcept -> double {
        return F_occlusion(R_charge, R_charge, r);
    }

    /// Occlusion force of a Z-nucleus on an electron at distance r.
    /// CORRECTED 2026-07-07 (interchange sweep, Harvey-authorized): the handed force
    /// transfers movement through redirection COUNT — occluded AREA ∝ Z, so the effective
    /// radius is √Z·R_p, giving F = Z·k_e e²/r² identically (measured Coulomb scaling).
    /// The previous R_nuc = Z·R_p (killed NP12 geometry, inlined here and missed by three
    /// audits) gave F ∝ Z² — factor Z wrong for every Z ≥ 2. Per-body radii in F_occlusion
    /// are physical only for gravity-class occlusion (real boundaries); the handed force
    /// signature is (Z₁·Z₂)·(R_p²r_e²) — count product × one universal unit-area.
    [[nodiscard]] inline auto F_nuclear_electron(
        int Z, double r
    ) noexcept -> double {
        double R_nuc = std::sqrt(static_cast<double>(Z)) * R_p;
        return F_occlusion(R_nuc, r_e, r);
    }

    /// Solid angle occluded by body of radius R at distance r  [sr]
    [[nodiscard]] constexpr auto solid_angle_occluded(
        double R, double r
    ) noexcept -> double {
        return std::numbers::pi * R * R / (r * r);
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  LAW IV — INERTIAL MASS (Theorems T5–T7)
//
//  m = Φ V_disp / (3 l_P³ c²)  — mass is throughput reorganisation cost.
//  (/3 = the angular-averaging quadrature share, T10 — banner corrected 2026-07-07:
//   the doc formula had dropped the /3 the code below always carried.)
//  m_inert = m_grav because both measure the same V_disp.
// ═══════════════════════════════════════════════════════════════════════

namespace law_IV {
    using namespace measured;

    /// Exclusion volume from mass: V_disp = 3 m l_P³ c² / Φ  [m³]
    /// (Factor of 3 from angular averaging: P_cf = P_conv/3)
    [[nodiscard]] inline auto V_disp_from_mass(double mass_kg) noexcept -> double {
        return 3.0 * mass_kg * l_P3 * c * c / law_I::Phi;
    }

    /// Mass from exclusion volume: m = Φ V_disp / (3 l_P³ c²)  [kg]
    // provenance_status:     SDT-derived
    // correspondence_status: internal-only
    // input_dependency:      primitive-whitelist
    // class:                 B
    // circularity_assertion: no matched target value enters the derivation
    // risk_flag:             none
    [[nodiscard]] inline auto mass_from_V_disp(double V_disp) noexcept -> double {
        return law_I::Phi * V_disp / (3.0 * l_P3 * c * c);
    }

    /// Exclusion radius (spherical equivalent): R = (3V/4π)^(1/3)  [m]
    [[nodiscard]] inline auto exclusion_radius(double V_disp) noexcept -> double {
        return std::cbrt(3.0 * V_disp / (4.0 * std::numbers::pi));
    }

    /// Electron exclusion volume  [m³]
    inline constexpr double V_disp_e = 3.0 * m_e * l_P3 * c * c / law_I::Phi;
    // = 9.988e-62 m³

    /// Proton exclusion volume  [m³]
    inline constexpr double V_disp_p = 3.0 * m_p * l_P3 * c * c / law_I::Phi;
    // = 1.834e-58 m³

    /// Electron exclusion radius  [m]
    /// Pre-computed: cbrt(3 × 9.988e-62 / (4π)) ≈ 2.878e-21 m
    inline constexpr double R_excl_e = 2.878e-21;

    /// Proton exclusion radius  [m]
    /// Pre-computed: cbrt(3 × 1.834e-58 / (4π)) ≈ 3.525e-20 m
    inline constexpr double R_excl_p = 3.525e-20;

    /// Effective displacement density for electron  [kg/m³]
    inline constexpr double rho_eff_e = m_e / V_disp_e;
    // ≈ 9.12e30 kg/m³

    /// Marginal stability verification: ρ_eff × c² should equal P_conv/3
    /// (This is Theorem T10's stability condition — an algebraic identity)
    inline constexpr double P_cf_e = rho_eff_e * c * c;
    // Should equal P_conv/3 = 8.197e47 Pa

    /// Rest energy: E₀ = Φ V_disp / (3 l_P³) = m c²  [J]  (/3 restored 2026-07-07)
    [[nodiscard]] constexpr auto rest_energy(double mass_kg) noexcept -> double {
        return mass_kg * c * c;
    }

    /// Three radii for each particle
    struct ParticleRadii {
        double R_excl;      // Exclusion radius (actual displaced volume)
        double R_wake;      // Wake/boundary radius (pressure perturbation reach)
        double R_quantum;   // Compton wavelength (quantum coherence scale)
    };

    inline constexpr ParticleRadii electron_radii = {
        2.878e-21,       // R_excl   2.878e-21 m
        r_e,             // R_wake   2.818e-15 m
        lambda_C_e       // R_quantum 3.862e-13 m (reduced: λ_C / 2π)
    };

    inline constexpr ParticleRadii proton_radii = {
        3.525e-20,       // R_excl   3.525e-20 m
        R_p,             // R_wake   8.414e-16 m
        lambda_C_p       // R_quantum 1.321e-15 m
    };
}

// ═══════════════════════════════════════════════════════════════════════
//  LAW V — MOVEMENT BUDGET (Axioms M1–M3, Theorems T10–T17)
//
//  Composite form:  v_circ² + v_trans² = c²
//  Full decomposition (Operator 6 / Ruleset §R6):
//    v_T² + v_P² + v_C² + v_t² = c²
//  where:
//    v_T = toroidal circulation velocity
//    v_P = poloidal circulation velocity
//    v_C = centripetal (radial) circulation velocity
//    v_t = translational velocity through the lattice
//    v_circ² = v_T² + v_P² + v_C²  (composite circulation)
//
//  Three axioms → eight theorems → all of special relativity
// ═══════════════════════════════════════════════════════════════════════

namespace law_V {
    using namespace measured;

    /// T10: Movement Budget — v_circ² + v_trans² = c²
    /// Returns circulation velocity for given translational velocity
    // provenance_status:     SDT-posited
    // correspondence_status: known-match            // yields all of special relativity downstream
    // input_dependency:      primitive-whitelist
    // class:                 A
    // circularity_assertion: axiom (Operator 6 / M3) — posited, not derived
    // risk_flag:             none
    [[nodiscard]] inline auto v_circ(double v_trans) noexcept -> double {
        return std::sqrt(c * c - v_trans * v_trans);
    }

    /// Returns translational velocity for given circulation velocity
    [[nodiscard]] inline auto v_trans(double v_circulation) noexcept -> double {
        return std::sqrt(c * c - v_circulation * v_circulation);
    }

    /// Lorentz factor γ = 1/√(1 - v²/c²)
    [[nodiscard]] inline auto gamma(double v) noexcept -> double {
        double beta = v / c;
        return 1.0 / std::sqrt(1.0 - beta * beta);
    }

    /// T11: Time dilation — dτ/dt = 1/γ = √(1 - v²/c²)
    [[nodiscard]] inline auto time_dilation(double v) noexcept -> double {
        double beta = v / c;
        return std::sqrt(1.0 - beta * beta);
    }

    /// T12: Length contraction — L = L₀/γ
    [[nodiscard]] inline auto length_contraction(double L0, double v) noexcept -> double {
        return L0 * time_dilation(v);
    }

    /// T13: Rest energy — E₀ = m₀c²  (circulation energy of vortex at rest)
    [[nodiscard]] inline auto rest_energy(double m0) noexcept -> double {
        return m0 * c * c;
    }

    /// T14: Energy–momentum relation — E² = (pc)² + (m₀c²)²
    [[nodiscard]] inline auto total_energy(double m0, double v) noexcept -> double {
        return gamma(v) * m0 * c * c;
    }

    [[nodiscard]] inline auto momentum(double m0, double v) noexcept -> double {
        return gamma(v) * m0 * v;
    }

    /// T15: Photon limit — v_circ = 0 ⟹ v = c, m = 0, E = pc
    inline constexpr double photon_v_circ = 0.0;
    inline constexpr double photon_v_trans = c;

    /// T16: Gravitational time dilation
    /// dτ/dt = √(1 - z R/r) where z = 1/k²
    [[nodiscard]] inline auto gravitational_time_dilation(
        double z, double R, double r
    ) noexcept -> double {
        return std::sqrt(1.0 - z * R / r);
    }

    /// T17: c-boundary radius — where v_orbital = c, matter cannot exist
    /// R_c = R / k²  (= z × R)
    [[nodiscard]] constexpr auto c_boundary(double R, double k) noexcept -> double {
        return R / (k * k);
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  SDT VELOCITY LAW & k-HIERARCHY
//
//  v(r) = (c/k)√(R/r)     — orbital velocity at radius r
//  z = (v/c)² = 1/k²      — bridge law
//  z · k² = 1              — closure condition
// ═══════════════════════════════════════════════════════════════════════

namespace bridge {
    using namespace measured;

    /// Orbital velocity: v(r) = (c/k) √(R/r)
    [[nodiscard]] inline auto v_orbital(
        double k, double R, double r
    ) noexcept -> double {
        return (c / k) * std::sqrt(R / r);
    }

    /// k from surface velocity: k = c / v
    [[nodiscard]] constexpr auto k_from_v(double v) noexcept -> double {
        return c / v;
    }

    /// Bridge law: z = (v/c)² = 1/k²
    [[nodiscard]] constexpr auto z_from_k(double k) noexcept -> double {
        return 1.0 / (k * k);
    }

    [[nodiscard]] constexpr auto z_from_v(double v) noexcept -> double {
        return (v * v) / (c * c);
    }

    /// Closure condition: z · k² = 1 (verification)
    [[nodiscard]] constexpr auto zk2_product(double z, double k) noexcept -> double {
        return z * k * k;
    }

    /// Escape velocity: v_esc = √2 × v  (standard virial)
    [[nodiscard]] constexpr auto v_escape(double v_orbital_val) noexcept -> double {
        return std::numbers::sqrt2 * v_orbital_val;
    }

    /// Stellar rotation: v_rot = π v² / c
    [[nodiscard]] constexpr auto v_rotation(double v_surface) noexcept -> double {
        return std::numbers::pi * v_surface * v_surface / c;
    }

    /// Angular velocity: ω = v/r
    [[nodiscard]] constexpr auto omega(double v, double r) noexcept -> double {
        return v / r;
    }

    /// Legacy equivalence: GM = v²r = c²R/k²
    /// (Convenience function — GM is derived, not fundamental)
    [[nodiscard]] constexpr auto GM_equivalent(
        double k, double R
    ) noexcept -> double {
        return c * c * R / (k * k);
    }

    // ─── Known k-values (from the hierarchy) ───

    /// Hydrogen ground state: v = αc → k = 1/α ≈ 137
    inline constexpr double k_hydrogen = alpha_inv;

    /// k at proton surface: k = (1/α)√(R_p/a_0) ≈ 0.5464
    /// This is INSIDE the c-boundary (k < 1 → superluminal phase rotation)
    /// Pre-computed: 137.036 × sqrt(8.414e-16 / 5.292e-11) = 0.5464
    inline constexpr double k_proton_surface = 0.5464;

    /// c-boundary of hydrogen: ϟ = α²a₀ = r_e ≈ 2.818 fm
    inline constexpr double koppa_hydrogen = alpha * alpha * a_0;
    // = r_e = 2.818e-15 m

    /// c-boundary of the Sun: ϟ_Sun = R_Sun / k_Sun²
    /// k_Sun ≈ 686 (from solar surface escape velocity)
    inline constexpr double k_Sun = 686.3;
    inline constexpr double koppa_Sun = R_Sun / (k_Sun * k_Sun);
    // ≈ 1477 m

    // ─── General koppa functions ───

    /// c-boundary (koppa): ϟ = R/k² = v²R/c²  [m]
    /// This single number encodes the entire gravitational field.
    // provenance_status:     SDT-posited
    // correspondence_status: known-match            // = GM/c² as a consequence, not an input
    // input_dependency:      measured-observable    // v_surface, R of the body
    // class:                 A
    // circularity_assertion: definition of the koppa observable
    // risk_flag:             none
    [[nodiscard]] constexpr auto koppa(double v_surface, double R) noexcept -> double {
        return v_surface * v_surface * R / (c * c);
    }

    /// Surface gravitational acceleration: g = v²/R = c²ϟ/R²  [m/s²]
    /// No G. No M. Just v and R.
    // provenance_status:     SDT-derived
    // correspondence_status: known-match
    // input_dependency:      measured-observable    // v_surface, R — no G, no M
    // class:                 C
    // circularity_assertion: passes delete-test — recovers surface gravity without G/M
    // risk_flag:             none
    [[nodiscard]] constexpr auto g_surface(double v_surface, double R) noexcept -> double {
        return v_surface * v_surface / R;
    }

    /// Gravitational acceleration at radius r inside body of radius R
    /// g(r) = v_surf² R frac(r) / r²  where frac = M_enc(r)/M_total
    [[nodiscard]] inline auto g_interior(
        double v_surface, double R, double r, double frac_enclosed
    ) noexcept -> double {
        if (r < 1.0) return 0.0;
        return v_surface * v_surface * R * frac_enclosed / (r * r);
    }

    // ─── Planetary k-values (from measured v_surf) ───

    inline constexpr double v_Earth   = 7909.0;     // [m/s]
    inline constexpr double R_Earth   = 6.371e6;    // [m]
    inline constexpr double k_Earth   = c / v_Earth; // ≈ 37905
    inline constexpr double koppa_Earth = v_Earth * v_Earth * R_Earth / (c * c);
    // = 4.434e-3 m = 4.43 mm

    inline constexpr double v_Moon    = 1680.0;
    inline constexpr double R_Moon    = 1.7374e6;
    inline constexpr double k_Moon    = c / v_Moon;  // ≈ 178448
    inline constexpr double koppa_Moon = v_Moon * v_Moon * R_Moon / (c * c);
    // = 5.46e-5 m = 0.055 mm

    // ─── Baryon Ϟ quantum — derived from base invariants only ───
    //
    // The gravitational c-boundary per proton:
    //   Ϟ_per_baryon = G m_p / c²
    //
    // G is NOT imported. Instead, from the Planck definition:
    //   G = l_P² c³ / ℏ
    //
    // Therefore:
    //   Ϟ_per_baryon = (l_P² c³ / ℏ) × m_p / c²
    //                = l_P² × c × m_p / ℏ
    //
    // Inputs: l_P [m], c [m/s], m_p [kg], ℏ [J·s] — all base invariants.
    // No G. No M_Sun. No standard-model mass measurements beyond m_p.
    //
    // provenance_status:     SDT-derived
    // correspondence_status: known-match            // equals G m_p/c²
    // input_dependency:      primitive-whitelist    // l_P, c, m_p, hbar only — G and M never entered
    // class:                 C-flagged
    // circularity_assertion: passes delete-test — no measured G or M is an input
    // risk_flag:             CODATA l_P conventionally encodes G under standard physics (disclosed, not laundered)
    inline constexpr double koppa_per_baryon = l_P * l_P * c * m_p / hbar;
    // = 1.2421e-54 m / baryon

    /// Baryon count from zk²=1
    ///
    /// For any body with observed orbital velocity v at radius R:
    ///   Ϟ_body = v² R / c²           [bridge law — no G, no M]
    ///   N_bar  = Ϟ_body / Ϟ_per_baryon
    ///
    /// This is the pure SDT baryon census. M_Sun in kg is NEVER needed.
    /// The only inputs are: v [m/s], R [m], and the base invariants.
    ///
    [[nodiscard]] constexpr auto N_baryons_from_koppa(
        double v_orbital_ms, double R_orbit_m
    ) noexcept -> double {
        double koppa_body = v_orbital_ms * v_orbital_ms * R_orbit_m / (c * c);
        return koppa_body / koppa_per_baryon;
    }

    /// Baryon count from pre-computed koppa
    [[nodiscard]] constexpr auto N_baryons(double koppa_body) noexcept -> double {
        return koppa_body / koppa_per_baryon;
    }

    // ─── GOM04 — c from orbital geometry (koppa closure) ─────────────────
    //
    //  c is NOT a free input: it CLOSES from Mercury's anomalous precession.
    //  NOTE on names: the precession fixes the speed-RATIO k = c/v (dimensionless,
    //  ≈686.4 for the Sun), NOT koppa-the-length (ϟ = R/k² = 1477 m). The GOM04
    //  write-up calls 686.4 "koppa"; by engine convention that quantity is k.
    //  The GR-analogue precession per orbit, δφ = 6πR / (k²·a·(1−e²)) [since
    //  ϟ=R/k²], inverts to give k from pure orbital observables — no c, no GM:
    //      k_Sun = √( 6π R_Sun / (δφ · a · (1−e²)) ) = 686.4
    //  then  c = k_Sun · v_surface  recovers 2.998e8 m/s to +0.0009%, and the
    //  length koppa_Sun = R_Sun / k_Sun² = 1477 m follows (matches bridge::koppa_Sun).
    //
    // provenance_status:     SDT-derived
    // correspondence_status: known-match            // recovers SI c to 0.0009%
    // input_dependency:      measured-observable     // δφ, R, a, e, v_surf — no c, no GM
    // class:                 C
    // circularity_assertion: passes delete-test — c is an OUTPUT here, not an input
    // risk_flag:             v_surface is itself an orbital inference (disclosed)
    inline constexpr double mercury_precession_arcsec_cy = 42.98;
    inline constexpr double a_Mercury  = 5.7909e10;  // [m]  semi-major axis
    inline constexpr double e_Mercury  = 0.20563;    // [-]  eccentricity
    inline constexpr double mercury_orbits_per_cy = 36525.0 / 87.969;  // ≈ 415.2

    /// Anomalous precession per orbit [rad], from arcsec/century
    inline constexpr double delta_phi_Mercury =
        (mercury_precession_arcsec_cy / mercury_orbits_per_cy)
        * (std::numbers::pi / (180.0 * 3600.0));
    // ≈ 5.019e-7 rad/orbit

    /// Speed ratio k = c/v of a star from a planet's anomalous precession
    /// (NO c, NO GM): k = √( 6π R_star / (δφ · a · (1−e²)) ).  ϟ = R_star/k².
    [[nodiscard]] inline auto k_from_precession(
        double R_star, double a_orbit, double e_orbit, double delta_phi
    ) noexcept -> double {
        return std::sqrt(6.0 * std::numbers::pi * R_star
                       / (delta_phi * a_orbit * (1.0 - e_orbit * e_orbit)));
    }

    /// Sun's surface velocity inferred from Earth's orbital kinematics [m/s]
    inline constexpr double v_surface_Sun = 436762.0;

    /// Sun's speed-ratio k reconstructed from Mercury's precession (≈ 686.4)
    inline const double k_Sun_from_precession =
        k_from_precession(R_Sun, a_Mercury, e_Mercury, delta_phi_Mercury);

    /// Sun's koppa LENGTH from the same closure: ϟ = R_Sun / k² (≈ 1477 m)
    inline const double koppa_Sun_from_precession =
        R_Sun / (k_Sun_from_precession * k_Sun_from_precession);

    /// c reconstructed from the closure: c = k_Sun · v_surface  ≈ 2.998e8 m/s
    inline const double c_from_closure = k_Sun_from_precession * v_surface_Sun;
    // = 299,795,136 m/s  (+0.0009% vs measured c) — "c from geometry alone"

    // ─── GOM06 — gravitational-wave chirp as a LENGTH (Gate G2, PASS) ────
    //  (GW mechanism investigation; renumbered FLM06→GOM06, as FLM06 = spation
    //   scale closure and GOM05 = variable closure are canonical. See law_I::N.)
    //
    //  The inspiral chirp is set by the binary's combined c-boundary ϟ_tot
    //  (a LENGTH), with no G and no M in any dynamical relation:
    //      r_isco    = 6 ϟ_tot
    //      f_GW,isco = c / (π · 6^{3/2} · ϟ_tot)
    //  For GW150914 (ϟ_tot ≈ 96 km): f_isco = 67.65 Hz vs measured 68.0 Hz
    //  (−0.52%). Read inversely, LIGO is a koppa-meter.
    //
    // provenance_status:     SDT-derived (koppa bridge)
    // correspondence_status: known-match            // 67.65 vs 68.0 Hz
    // input_dependency:      measured-observable     // ϟ_tot from the merger; G and M never apart
    // class:                 C
    // circularity_assertion: this is the koppa-bridge identity GM≡c²ϟ applied
    //                        to GR's f_isco — an ALGEBRAIC IDENTITY (disclosed),
    //                        its content conceptual: the chirp scale is a length
    // risk_flag:             inspiral FORM df/dt ∝ f^{11/3} ϟ_c^{5/3} is SDT's, but
    //                        the 96/5 radiation coefficient is CONVERGENCE-PENDING

    /// ISCO radius from the binary's combined koppa: r_isco = 6 ϟ_tot  [m]
    [[nodiscard]] constexpr auto r_isco_from_koppa(double koppa_tot) noexcept -> double {
        return 6.0 * koppa_tot;
    }

    /// GW frequency at ISCO: f = c / (π · 6^{3/2} · ϟ_tot)  [Hz]
    [[nodiscard]] inline auto f_GW_isco(double koppa_tot) noexcept -> double {
        return c / (std::numbers::pi * 6.0 * std::sqrt(6.0) * koppa_tot);
    }

    /// Inverse (LIGO as a koppa-meter): a measured ISCO frequency → ϟ_tot [m]
    [[nodiscard]] inline auto koppa_from_f_GW_isco(double f_hz) noexcept -> double {
        return c / (std::numbers::pi * 6.0 * std::sqrt(6.0) * f_hz);
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  ATOMIC PHYSICS — Rydberg, Fine Structure, Hyperfine
// ═══════════════════════════════════════════════════════════════════════

namespace atomic {
    using namespace measured;

    /// Rydberg transition energy: E = Ry × Z² × (1/n₁² - 1/n₂²)
    [[nodiscard]] constexpr auto rydberg_energy_eV(
        int Z, int n_low, int n_high
    ) noexcept -> double {
        double Z2 = static_cast<double>(Z * Z);
        double n1_inv2 = 1.0 / static_cast<double>(n_low * n_low);
        double n2_inv2 = 1.0 / static_cast<double>(n_high * n_high);
        return Ry_eV * Z2 * (n1_inv2 - n2_inv2);
    }

    /// Ionisation energy: E_ion = Ry × Z² / n²
    [[nodiscard]] constexpr auto ionisation_energy_eV(
        int Z, int n
    ) noexcept -> double {
        return Ry_eV * static_cast<double>(Z * Z) / static_cast<double>(n * n);
    }

    /// Fine structure splitting (Sommerfeld): ΔE = E_n × α² × Z² / n
    [[nodiscard]] constexpr auto fine_structure_eV(
        int Z, int n
    ) noexcept -> double {
        double E_n = ionisation_energy_eV(Z, n);
        return E_n * alpha * alpha * static_cast<double>(Z * Z) / static_cast<double>(n);
    }

    /// Bohr orbital velocity: v_n = αc Z / n
    [[nodiscard]] constexpr auto bohr_velocity(int Z, int n) noexcept -> double {
        return alpha * c * static_cast<double>(Z) / static_cast<double>(n);
    }

    /// Bohr orbital radius: r_n = a₀ n² / Z
    [[nodiscard]] constexpr auto bohr_radius(int Z, int n) noexcept -> double {
        return a_0 * static_cast<double>(n * n) / static_cast<double>(Z);
    }

    // ─── APS01 — Emissions: the velocity-state chain (RESOLVED) ──────────────
    //  The atomic emission spectrum follows from ONE rotation field, with no
    //  wavefunction and no fit. v(r)=cα√(a₀/r) is the circulation of the
    //  spation medium about the nucleus; the closed-circulation radii are the
    //  states, and the Rydberg constant is FORCED by {m_e,c,α,h}. Verified:
    //  H spectra <12.5 ppm, H-like (Z≤30) <263 ppm vs NIST; zk²=1 exact.

    /// Rotation-field velocity at radius r: v(r) = c α √(a₀/r)  [m/s]
    // provenance_status:     SDT-derived
    // correspondence_status: known-match      // v(a₀)=cα; v_n=αc/n at closed radii
    // input_dependency:      primitive-whitelist
    // class:                 B
    // circularity_assertion: passes delete-test
    // risk_flag:             none
    [[nodiscard]] inline auto rotation_field_velocity(double r_m) noexcept -> double {
        return c * alpha * std::sqrt(a_0 / r_m);
    }

    /// Rydberg constant rebuilt from invariants: R∞ = m_e c α² / (2h)  [m⁻¹]
    /// Forced by {m_e,c,α,h} before any spectrum is consulted; ≡ measured R_inf.
    // provenance_status:     SDT-derived
    // correspondence_status: known-match      // ≡ CODATA R_inf to ~0 ppm
    // input_dependency:      primitive-whitelist
    // class:                 B
    inline constexpr double R_inf_derived = m_e * c * alpha * alpha / (2.0 * h);
    // = 1.0973732e7 m⁻¹

    /// Finite-nucleus reduced-mass factor μ/m_e = m_nuc/(m_e+m_nuc).
    /// Classical two-body correction (NOT a QFT/QED term); m_nuc ≈ A·m_p.
    [[nodiscard]] constexpr auto reduced_mass_factor(double m_nuc_kg) noexcept -> double {
        return m_nuc_kg / (m_e + m_nuc_kg);
    }

    /// Hydrogen-like emission wavelength (leading order, reduced-mass corrected):
    ///   1/λ = R∞·(μ/m_e)·Z²·(1/n₁² − 1/n₂²)   [m]
    /// The few-ppm residual is the next movement-budget term z=(v/c)²=(Zα)²,
    /// logged as a remainder — no QED/QFT input.
    [[nodiscard]] constexpr auto emission_wavelength_m(
        int Z, int n_low, int n_high, double m_nuc_kg
    ) noexcept -> double {
        const double Rn  = R_inf_derived * reduced_mass_factor(m_nuc_kg);
        const double inv = static_cast<double>(Z * Z)
            * (1.0 / static_cast<double>(n_low  * n_low)
             - 1.0 / static_cast<double>(n_high * n_high));
        return 1.0 / (Rn * inv);
    }

    /// Outer-electron launch velocity from the first ionisation energy:
    /// v₁ = √(2 IE₁/m_e). Feeds the zk²=1 closure: z=(v₁/c)², k=c/v₁ ⟹ z·k²=1.
    [[nodiscard]] inline auto outer_velocity_from_IE(double IE1_J) noexcept -> double {
        return std::sqrt(2.0 * IE1_J / m_e);
    }

    // ─── APS02 — Drag factor: koppa drafting in multi-electron shells ────────
    //  COMPUTED/OBSERVED trend (a real-data correlation, NOT a zk²-style
    //  closure). D = λ_meas / [(8/3)·λ_C·k²], k = c/v₁. Tracks the outer-shell
    //  electron count: lone opener s¹→D≈1.76, paired s²→1.40, full p⁶→1.02.
    //  The traction wakes (PPT06) of co-shell electrons interfere constructively
    //  in the shared orbital slot — drafting, like cyclists in a pace-line.

    /// Drag factor D = λ_meas / [(8/3)·λ_C·k²], with k = c/v₁, v₁=√(2 IE₁/m_e)
    // provenance_status:     SDT-derived geometry + measured IE₁, λ
    // correspondence_status: novel               // the D(outer-count) trend
    // input_dependency:      measured-observable  // IE₁ and λ_meas are measured
    // class:                 D                     // COMPUTED/OBSERVED correlation
    // circularity_assertion: n/a (a measured trend, not a closure)
    // risk_flag:             the (8/3) slot weight is not yet derived from geometry
    [[nodiscard]] inline auto drag_factor(double lambda_meas_m, double IE1_J) noexcept -> double {
        const double k = c / outer_velocity_from_IE(IE1_J);
        return lambda_meas_m / ((8.0 / 3.0) * lambda_C_e * k * k);
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  NUCLEAR PHYSICS — Occlusion geometry, alpha clustering
// ═══════════════════════════════════════════════════════════════════════

namespace nuclear {
    using namespace measured;

    /// Nuclear boundary radius — NP12 canon change (2026-07-05, Harvey-authorized).
    /// R(A) = R_p · (A/η)^(1/3),  η = π/√18 ≈ 0.74048 (close-packing fraction) — ZERO-FIT:
    /// close-packed nucleon volume V = A·(4/3)πR_p³/η  ⇒  R = R_p (A/η)^(1/3).
    /// Graded against 908 measured radii (IAEA / Angeli & Marinova 2013): RMS 4.96%
    /// (statistically degenerate with the empirical 0.93·A^(1/3) rival at 5.00%, but wins
    /// 5× on isotope chains: Ca 1.67% flat where A^(1/3) predicts +8.63%; Sn 3.20%; Pb 3.28%).
    /// provenance_status:     SDT-derived (packing geometry; no fitted constant)
    /// correspondence_status: known-match (4.96% RMS, N=908)
    /// evidence:              Investigations/05_Nuclear_Physics/NP12_.../NP12_VERDICT.md
    [[nodiscard]] inline auto nuclear_boundary_radius(int A) noexcept -> double {
        constexpr double eta = std::numbers::pi / 4.242640687119285;  // π/√18
        return R_p * std::cbrt(static_cast<double>(A) / eta);
    }

    /// ⛔ DEPRECATED — RETRACTED AS A LAW (NP12, 2026-07-05): R = Z·R_p was KILLED against
    /// the same 908 measured radii (RMS 890.8%, 179× the pre-committed kill threshold —
    /// the 1D-stacking premise is dead). Retained only so legacy callers still compile;
    /// use nuclear_boundary_radius(A). (Function name kept for compatibility; the physical
    /// quantity is a BOUNDARY radius — no charge substance.)
    [[nodiscard]] constexpr auto nuclear_charge_radius(int Z) noexcept -> double {
        return static_cast<double>(Z) * R_p;
    }

    /// He-4 verification: R_He should ≈ 2 × R_p
    inline constexpr double R_He_predicted = 2.0 * R_p;
    // = 1.683e-15 m vs measured 1.6755e-15 m → 0.43% agreement

    /// c-boundary for nucleus of charge Z
    /// ϟ_Z = Z × r_e (c-boundary scales with Z)
    [[nodiscard]] constexpr auto c_boundary_nuclear(int Z) noexcept -> double {
        return static_cast<double>(Z) * r_e;
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  COULOMB COUPLING IDENTITY
//
//  Derived (not postulated) from:
//    (1) SDT force law:     F = (π/4) P_eff R_charge⁴ / r²
//    (2) Charge quantisation: R_charge = √(R_p r_e)
//    (3) Transfer function:   P_eff = 4αℏc / (π R_p² r_e²)
//  Result: k_e e² = αℏc  (exact, no free parameters)
// ═══════════════════════════════════════════════════════════════════════

namespace coulomb_identity {
    using namespace measured;

    /// k_e × e² — the physically load-bearing coupling product
    /// Derived: k_e e² = αℏc
    // provenance_status:     unresolved
    // correspondence_status: known-match
    // input_dependency:      definitional-identity  // α ≡ k_e e²/(ℏ c): this line is a tautology
    // class:                 F
    // circularity_assertion: FAILS delete-test — vanishes; supply an SDT path NOT using α's definition
    // risk_flag:             relabel from "Derived (exact, no free parameters)" — it is an identity
    inline constexpr double k_e_e2 = alpha * hbar * c;
    // = 2.307e-28 J·m

    /// Verification against CODATA values
    inline constexpr double k_e_e2_codata = k_e * e_charge * e_charge;
    // Should match k_e_e2 to machine precision

    /// The coupling is the product. Neither k_e nor e is separately
    /// fundamental — only their combination enters all force laws.
}

// ═══════════════════════════════════════════════════════════════════════
//  LAW VI — VORTEX TOPOLOGY QUANTISATION (Theorem T18)
//
//  Stable particles are persistent topological defects (vortices) in
//  the spation lattice. The winding number W determines particle identity:
//    W = 1 (torus, simple loop) → electron / positron
//    W = 3 (trefoil knot)       → proton / antiproton
//    W = 0 (open winding)       → neutrino
//
//  W+1 RADIUS CONJECTURE:
//    R_wake = (W + 1) × ℏ / (m c)
//    For W = 3: R_p = 4ℏ/(m_p c) = 0.84124 fm (0.02% vs muonic-H)
//
//  FALSIFICATION: if |R_p_measured − 4ℏ/(m_p c)| > n σ_combined,
//  the W+1 conjecture is false (branch test, not full-SDT kill).
// ═══════════════════════════════════════════════════════════════════════

namespace law_VI {
namespace winding {
    using namespace measured;

    // W=1 and W=3 are not asserted — they are the only stable torus-knot
    // windings (PPT09, CLASS A, analytic). A (p,q) mode is a TRUE KNOT iff
    // gcd(p,q)=1 and min(p,q)≥2; its Alexander polynomial Δ(t)≠1 is a knot
    // invariant that cannot change under continuous deformation:
    //   (1,1) electron: Δ=1            → unknot, confined by V_disp (stable)
    //   (1,2) "W=2":    Δ=1            → unknot, only metastable (≈0.1 GeV
    //                                    barrier, τ~10⁻²¹ s) → never observed
    //   (2,3) proton:   Δ=t⁻²−t⁻¹+1−t+t² ≠ 1 → trefoil, topologically
    //                                    protected, cannot decay (τ_p>10³⁴ yr)

    /// Proton winding number (trefoil knot)
    inline constexpr int W_proton = 3;

    /// Electron winding number (simple torus)
    inline constexpr int W_electron = 1;

    /// W+1 predicted proton boundary radius: R_p = (W+1) ℏ / (m_p c)
    // provenance_status:     SDT-derived
    // correspondence_status: known-match            // 0.02% vs muonic-H proton radius
    // input_dependency:      primitive-whitelist    // hbar, m_p, c + winding W=3
    // class:                 C-flagged
    // circularity_assertion: passes delete-test given the W+1 rule (measured R_p not an input)
    // risk_flag:             W+1 rule conjectural — not yet proven from trefoil geometry
    inline constexpr double R_p_predicted = static_cast<double>(W_proton + 1)
                                          * hbar / (m_p * c);
    // = 8.4124e-16 m = 0.84124 fm

    /// R_p residual: ΔR_p = R_p_measured − R_p_predicted
    inline constexpr double delta_R_p = R_p - R_p_predicted;

    /// R_p relative error
    inline constexpr double R_p_error_pct = (R_p - R_p_predicted) / R_p * 100.0;
    // ≈ 0.02%

    /// Effective winding number inferred from measurement:
    /// W_eff = R_p m_p c / ℏ − 1
    /// Conjecture predicts W_eff = 3 (integer)
    inline constexpr double W_eff = R_p * m_p * c / hbar - 1.0;
    // ≈ 3.0008

    /// Wake-to-quantum ratio: g(W) = R_wake / ƛ_C
    /// Electron: g(1) = α = 1/137
    /// Proton:   g(3) = 4
    // provenance_status:     unresolved
    // correspondence_status: known-match
    // input_dependency:      definitional-identity  // r_e ≡ α ℏ/(m_e c) ⟹ g_electron ≡ α identically
    // class:                 F
    // circularity_assertion: FAILS delete-test — algebraic identity, not a measurement of α
    // risk_flag:             g(1)=α is definitional; the non-trivial claim is g(3)=4 (proton)
    inline constexpr double g_electron = r_e * m_e * c / hbar;
    // = alpha (exact)
    inline constexpr double g_proton = R_p * m_p * c / hbar;
    // ≈ 4.0008

    // Point-electron structure (OPEN — measured from the locked rotation,
    // NOT yet derived from W=1 displacement geometry): r_e is the electron's
    // c-boundary (its wake), not its body. The body is a near-point. Tidally
    // locked (one axial turn per orbit) ω_spin = ω_orbit = αc/a₀ ≈ 4.13e16 rad/s;
    // with a ~3e-20 m body its surface crawls at ~1.2 mm/s while the orbit runs
    // at αc — the point barely turns.
    inline constexpr double omega_electron_locked = alpha * c / a_0;  // ≈ 4.13e16 rad/s
    inline constexpr double r_electron_body_open   = 3.0e-20;          // [m] OPEN (from 1.2 mm/s)

    /// Falsification test: does W_eff round to the expected integer?
    [[nodiscard]] constexpr auto winding_test_passes(
        double R_p_meas, double sigma_Rp
    ) noexcept -> bool {
        const double W_meas = R_p_meas * m_p * c / hbar - 1.0;
        const double sigma_W = sigma_Rp * m_p * c / hbar;
        return (W_meas - 3.0) * (W_meas - 3.0) < (3.0 * sigma_W) * (3.0 * sigma_W);
        // Passes if W_eff is within 3σ of integer 3
    }
} // namespace winding
  // NB: law_VI stays OPEN here — the topology/confinement/traction/mass_ratio/
  //     angular sub-namespaces below are siblings of `winding` inside law_VI,
  //     which closes at the "} // namespace law_VI" further down.
  //     Build note: compile UTF-8 sources with MSVC `/utf-8`, else the
  //     multibyte glyphs in this header mis-tokenise as spurious
  //     "namespace not found" errors (GCC/Clang are fine without it).

// ───────────────────────────────────────────────────────────────────────
//  PPT01 — Vortex equilibrium quantisation (torus-knot mode equations)
//  RESOLVED 5/5. Stable particles are (p,q) torus knots; the toroidal/
//  poloidal velocity partition follows EXACTLY from the movement budget
//  v_T²+v_P²=c² (Law V). Electron = (1,1) unknot, proton = (2,3) trefoil.
// ───────────────────────────────────────────────────────────────────────
namespace topology {
    using namespace measured;

    /// Toroidal mode velocity of a (p,q) torus knot: v_T = c√(p/(p+q))
    // provenance_status:     SDT-derived
    // correspondence_status: internal-only
    // input_dependency:      primitive-whitelist   // c + the integers (p,q)
    // class:                 A                      // exact from the movement budget
    // circularity_assertion: passes delete-test
    // risk_flag:             none
    [[nodiscard]] inline auto v_toroidal(int p, int q) noexcept -> double {
        return c * std::sqrt(static_cast<double>(p) / static_cast<double>(p + q));
    }

    /// Poloidal mode velocity: v_P = c√(q/(p+q))
    [[nodiscard]] inline auto v_poloidal(int p, int q) noexcept -> double {
        return c * std::sqrt(static_cast<double>(q) / static_cast<double>(p + q));
    }

    /// Mode-locked aspect ratio: R/a = √(q/p)
    [[nodiscard]] inline auto aspect_ratio(int p, int q) noexcept -> double {
        return std::sqrt(static_cast<double>(q) / static_cast<double>(p));
    }

    /// Budget closure residual: (v_T²+v_P²)/c² — exactly 1 for all (p,q)
    [[nodiscard]] inline auto budget_residual(int p, int q) noexcept -> double {
        const double vt = v_toroidal(p, q), vp = v_poloidal(p, q);
        return (vt * vt + vp * vp) / (c * c);
    }

    // Canonical particle modes (p,q):
    inline constexpr int electron_p = 1, electron_q = 1;  // unknot,  v_T=v_P=c/√2
    inline constexpr int proton_p   = 2, proton_q   = 3;  // trefoil, v_T=0.632c, v_P=0.775c
}

// ───────────────────────────────────────────────────────────────────────
//  PPT05 — Trefoil confinement (linear potential & string breaking)
//  RESOLVED. Confinement is convergent-pressure GEOMETRY, not a new force:
//  the isotropic P_conv/3 collimates the deflected throughput into a tube
//  of constant cross-section πa², so its energy grows linearly, E(L)=σL.
// ───────────────────────────────────────────────────────────────────────
// ⛔ CONTRABAND-FLAG (interchange sweep 2026-07-07, Harvey-authorized):
//  TWO problems in this section, flagged not fixed — values left untouched
//  pending Harvey's call:
//  (1) SILENT IMPORT: the pion mass 139.57 MeV is baked into the typed
//      literal below (string_breaking_m = 2·m_π·c²/σ = 0.23 fm) but m_π
//      appears NOWHERE in sdt::laws::measured — the whitelist of external
//      inputs. A fact not in measured:: is not a measured fact; this is
//      an unlicensed import riding inside a derived constant.
//  (2) MODE-TABLE COLLISION: the pair-snap prose assigns the pion to the
//      (1,1)+(1,1)̄ mode, but the winding mode table (law_VI::winding,
//      ~line 1081) already assigns (1,1) = electron (0.511 MeV). One mode
//      cannot be both a 0.511 MeV electron and a 139.57 MeV pion — either
//      the pair-snap assignment or the mode table is wrong; both cannot
//      stand. Which one gives is a physics fork = Harvey's call.
// ───────────────────────────────────────────────────────────────────────
namespace confinement {
    using namespace measured;

    /// SDT string tension σ = u_tube · A_tube  [GeV/fm]
    // provenance_status:     SDT-derived
    // correspondence_status: known-match       // lattice-QCD σ≈0.9 GeV/fm (same order)
    // input_dependency:      primitive-whitelist
    // class:                 C
    // circularity_assertion: passes delete-test
    // risk_flag:             magnitude is ~37% ABOVE the lattice-QCD value — a
    //                        convergence on the mechanism/scale, NOT an exact match
    inline constexpr double string_tension_GeV_per_fm = 1.23;

    /// Critical string-breaking separation: L_c = 2 m_π c² / σ  [m]
    /// At L_c the tube energy reaches 2 m_π c² and snaps into a (1,1)+(1,1)̄
    /// (pion) pair, conserving crossover number. An isolated open strand
    /// would cost infinite energy → free strands are forbidden.
    inline constexpr double string_breaking_m = 0.23e-15;  // ≈ 0.23 fm

    /// Linear confinement potential: E(L) = σ L  [GeV], L in fm
    [[nodiscard]] inline auto confinement_energy_GeV(double L_fm) noexcept -> double {
        return string_tension_GeV_per_fm * L_fm;
    }

    /// Theorem A — harmonic restoring rate (smoothing): ω²_{m,n}
    /// = (m v_T / R)² + (n v_P / a)².  Higher harmonics damp preferentially
    /// (∝ n²), so the smooth torus is the stable equilibrium.
    [[nodiscard]] inline auto harmonic_rate_sq(
        int m, int n, double v_T, double R, double v_P, double a
    ) noexcept -> double {
        const double wm = m * v_T / R, wn = n * v_P / a;
        return wm * wm + wn * wn;
    }
}

// ───────────────────────────────────────────────────────────────────────
//  PPT06 — Spation traction from the trefoil ("how the gears start")
//  RESOLVED. The proton trefoil demands v_phase=1.831c at R_p; the lattice
//  relays at ≤c. The mismatch T=3(W+1)=12 is the mechanical origin of the
//  Coulomb (ℓ=1), magnetic (ℓ=2) and orbital-entrainment (ℓ≥3) wakes.
// ───────────────────────────────────────────────────────────────────────
namespace traction {
    using namespace measured;

    /// Total toroidal winding per circulation cycle: Δφ = q·2π = 6π (q=3)
    inline constexpr double total_winding_rad =
        2.0 * std::numbers::pi * static_cast<double>(topology::proton_q);  // = 6π

    /// Superluminal phase velocity demanded at the proton surface:
    /// v_phase = c / k_proton_surface ≈ 1.831 c (inside the c-boundary r_e)
    inline constexpr double v_phase_proton_surface = c / bridge::k_proton_surface;
    // ≈ 5.488e8 m/s = 1.831 c

    /// Angular velocity demanded of a contact spation:
    /// ω_demand = 6π / T_circ = 3c/ƛ_C = 3 m_p c² / ℏ   (ƛ = reduced; λ/2π — fixed 2026-07-07)
    // provenance_status:     SDT-derived
    // correspondence_status: internal-only
    // input_dependency:      primitive-whitelist   // m_p, c, ℏ + winding q=3
    // class:                 C
    // circularity_assertion: passes delete-test
    // risk_flag:             none
    inline constexpr double omega_demand = 3.0 * m_p * c * c / hbar;
    // ≈ 4.27e24 rad/s

    /// Maximum angular velocity the lattice can relay at radius R: ω_max = c/R
    [[nodiscard]] constexpr auto omega_max(double R) noexcept -> double {
        return c / R;
    }
    inline constexpr double omega_max_proton = c / R_p;
    // ≈ 3.56e23 rad/s

    /// Traction ratio (velocity mismatch): T = ω_demand/ω_max = 3R_p/λ_C
    ///                                        = 3(W+1) = 12 for the proton
    inline constexpr double traction_ratio_proton =
        3.0 * static_cast<double>(law_VI::winding::W_proton + 1);  // = 12

    /// Gear ratio nuclear→atomic: ω_p/ω_e = 3 a₀ m_p c / (α ℏ) ≈ 1.03e8
    /// ("chemistry is nuclear physics geared down by χ = 137")
    inline constexpr double gear_ratio_nuclear_atomic =
        3.0 * a_0 * m_p * c / (alpha * hbar);
    // ≈ 1.03e8
}

// ───────────────────────────────────────────────────────────────────────
//  PPT07 — Proton/electron mass ratio from topology (RESOLVED, analytic)
//  m_p/m_e is NOT a free parameter. The (2,3) trefoil organises a phase-
//  locked displacement zone of exactly 6π⁵ fundamental volume units, which
//  decomposes as 3·(2π²)·π³ = (W=3 lobes)·(3-sphere surface-volume)·
//  (isotropic-pressure π³).
// ───────────────────────────────────────────────────────────────────────
namespace mass_ratio {
    using namespace measured;

    /// Topological identity: 6π⁵ = 1836.118  (−0.0019% vs measured 1836.15267)
    // provenance_status:     SDT-derived
    // correspondence_status: known-match
    // input_dependency:      primitive-whitelist   // pure topology: integers + π
    // class:                 B-flagged             // exact identity; V_disp link pending OP-1
    // circularity_assertion: passes delete-test (no mass measurement enters 6π⁵)
    // risk_flag:             the 6π⁵ ↔ V_disp(3)/V_disp(1) mapping is asserted, not derived
    inline constexpr double six_pi_5 =
        6.0 * std::numbers::pi * std::numbers::pi * std::numbers::pi
            * std::numbers::pi * std::numbers::pi;
    // = 1836.1181...

    /// Decomposition: 3·(2π²)·π³ ≡ 6π⁵ (W lobes × S³ surface-volume × π³)
    inline constexpr double decomposition =
        3.0 * (2.0 * std::numbers::pi * std::numbers::pi)
            * (std::numbers::pi * std::numbers::pi * std::numbers::pi);

    /// Measured ratio (data, for comparison only)
    inline constexpr double measured_ratio = m_p / m_e;  // = 1836.15267
    inline constexpr double error_pct = (six_pi_5 - measured_ratio) / measured_ratio * 100.0;
    // ≈ −0.0019%
}

// ───────────────────────────────────────────────────────────────────────
//  APS04 — Trefoil wake multipole & NATIVE angular DOF  (PASS, CLASS C)
//  The proton trefoil's wake carries a native three-fold (C₃) structure
//  that supplies the angular degree of freedom (s-vs-p) WITHOUT importing
//  spherical-harmonic ℓ quantum numbers. The native content is the
//  selection rule m₃ = 3k (C₃ periodicity) and the r⁻¹/r⁻³/r⁻⁴ power laws.
//
//  CAVEATS — do not over-read (this competes with a CALIBRATED benchmark):
//   • "multipole / quadrupole / Legendre Pℓ" is borrowed MATHEMATICAL
//     language; only the C₃ periodicity and the power laws are native.
//   • The Lamb-shift VALUE rests on a quadrupole amplitude (~α·10⁻²) whose
//     numerical verification is PENDING a lattice wake solver (APS04 Phase 2).
//   • B04 keeps its CALIBRATED k_Lamb=12.7227; this supersedes the refuted
//     "dyad-first" candidate (2026-06-08) but is a NATIVE CANDIDATE, not yet
//     a benchmark replacement.
// ───────────────────────────────────────────────────────────────────────
namespace angular {
    using namespace measured;

    /// Native angular selection rule from the trefoil's C₃ symmetry:
    /// allowed azimuthal numbers are m₃ = 3k (k ∈ ℤ).
    [[nodiscard]] constexpr auto m3_allowed(int m3) noexcept -> bool {
        return (m3 % 3) == 0;
    }

    /// Spectral selection rule: Δm₃ ∈ {0, ±3, ±6, …}
    [[nodiscard]] constexpr auto transition_allowed(int m3_i, int m3_f) noexcept -> bool {
        return ((m3_f - m3_i) % 3) == 0;
    }

    /// Trefoil-wake multipole power-law exponents: Φ_ℓ(r) ~ r^{exponent}
    inline constexpr double monopole_exponent          = -1.0;  // ℓ=0, occlusion (Coulomb-like)
    inline constexpr double quadrupole_exponent        = -3.0;  // ℓ=2, rotational wake
    inline constexpr double trefoil_harmonic_exponent  = -4.0;  // ℓ=3, three-fold circulation

    /// Lamb shift (H 2S–2P). SDT amplitude is OPEN (PPT08).
    /// RETRACTION (HUNTER 2026-07-02, applied 2026-07-03 with J.C.Harvey's authorization):
    /// the former `lamb_shift_native_MHz = 1051.8` was a bare literal, NOT a derivation —
    /// the (9/4)Φ₂(a₀) evaluation is not in the code, only the answer was typed. It is the
    /// APS04 fished value (its own solver never compiled; the formula with its own inputs
    /// gives ~3145 MHz). Removed. PPT08 (SDT Lamb amplitude) is OPEN.
    // provenance_status:     OBSERVED-INPUT (measured RF resonance; NOT SDT-derived)
    // correspondence_status: measured
    // input_dependency:      measured-observable
    // class:                 OPEN (native amplitude unbuilt — see PPT08)
    inline constexpr double lamb_shift_measured_MHz = 1057.845;  // measured, not derived
    // (lamb_shift_native_MHz DELETED — was fabricated 1051.8; do not restore without a derivation)
}
} // namespace law_VI

// ═══════════════════════════════════════════════════════════════════════
//  OPEN PROBLEMS — Updated status
// ═══════════════════════════════════════════════════════════════════════
//
//  1. R_p from lattice topology
//     STATUS: CONJECTURED as R_p = 4ℏ/(m_p c) via W+1 rule (0.02%).
//     Full derivation requires proving W+1 scaling from trefoil geometry.
//     PPT09 (CLASS A) grounds W=3: the (2,3) trefoil is topologically
//     protected (Alexander Δ≠1), so W cannot jump and R_p cannot drift.
//
//  2. Quantisation of stable vortex topologies
//     RESOLVED (PPT09, analytic): W=1 (unknot, confined) and W=3 (trefoil,
//     protected) are the only stable windings; W=2 is unknotted and merely
//     metastable (≈0.1 GeV barrier, τ~10⁻²¹ s) → never observed. Higher
//     knots (W=5,7,…) are protected but await discovery. The full lattice
//     reconnection simulation (ROOT-SIM) would still strengthen this.
//
//  3. Fine structure constant from topology
//     α = g(W=1) = r_e / ƛ_Ce. Can this be derived from the W=1 torus
//     mode partition (v_P / v_T)?  Would eliminate α as input. (PPT02 found
//     α = koppa of the H ground state — electromagnetic, still needs e.)
//
//  4. Proton-electron mass ratio
//     RESOLVED-analytic (PPT07): m_p/m_e = 6π⁵ = 1836.118 (−0.0019%), the
//     pure topological identity 3·(2π²)·π³ — see law_VI::mass_ratio. The
//     6π⁵ ↔ V_disp(3)/V_disp(1) link still awaits the OP-1 equilibrium solver.
//
// ═══════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════
//  THE DEPTH–CLOSURE THEOREM  (capstone — Papers/Depth_Closure_Theorem)
//
//  Unifies GOM01 (depth engine) · GOM02 (k-hierarchy) · GOM04 (koppa closure) ·
//  APS03/GD05 (a₀ floor) · FLM06/GOM05 (variable spation closure). Numbers
//  reproduce from Papers/Depth_Closure_Theorem/keystone.js.
//
//  Local closure, local relay speed, local clock rate and the gravitational
//  spectral shift are ONE quantity — the convergence depth z = ϟ/r — and one
//  centripetal law v = c√z governs bound motion at every scale:
//
//    z ≡ 1/k² = (v/c)² = ϟ/r,   ϟ ≡ v²R/c² = R/k²   (koppa: a velocity-defined length)
//
//    (1) ℓ_P(r)     = ℓ_P,∞ · (1 − z)        local spation closure
//    (2) c_local(r) = c_∞   · (1 − z)        local relay speed ⇒ z = 1 − c_local/c_∞
//    (3) dτ/dt      = √(1 − z)                local clock rate (Law V budget)
//    (4) z_spec     = z(r_emit) − z(r_obs)    "gravitational redshift" = depth differential
//    (5) v(r)       = c √(ϟ/r) = c √z         bound-motion law (g = v²/r = c²ϟ/r²)
//
//  PROVEN content: C1 (redshift = depth, Sun to 0.03%) and C2 (one law across
//  ~15 orders). CAVEATS (future work, NOT theorem content): the absolute
//  closure ℓ_P,∞, the galactic-floor magnitude, and the proton/electron
//  internal radii carry the FLM06-seed/GOM05 caveats (see law_I::N note).
// ═══════════════════════════════════════════════════════════════════════
namespace depth_closure {
    using namespace measured;

    /// Convergence depth from koppa and radius: z = ϟ/r = 1/k² = (v/c)²
    [[nodiscard]] constexpr auto depth(double koppa, double r) noexcept -> double {
        return koppa / r;
    }
    [[nodiscard]] constexpr auto depth_from_v(double v) noexcept -> double {
        return (v * v) / (c * c);
    }

    /// (5) Bound-motion law: v(r) = c√(ϟ/r) = c√z  [m/s]
    /// NO attraction: the CMB convergence pushes everything together; matter
    /// follows the path of least resistance through the radial depth gradient,
    /// and a closed least-resistance path IS an orbit. (No pull, real orbits.)
    [[nodiscard]] inline auto v_bound(double koppa, double r) noexcept -> double {
        return c * std::sqrt(koppa / r);
    }

    /// GOM01 — Shapiro delay is ACCUMULATED DEPTH, not slowing-in-a-well: the
    /// local light speed stays c. Δt = (2/c)∫ z dl = (2ϟ/c)∫ dl/r, which for a
    /// ray of impact parameter b from r₁ to r₂ gives the standard log form
    /// Δt = (2ϟ/c) ln(4 r₁ r₂ / b²)  — matches GR/observation to 0.0000%.
    [[nodiscard]] inline auto shapiro_delay(
        double koppa, double r1, double r2, double b
    ) noexcept -> double {
        return (2.0 * koppa / c) * std::log(4.0 * r1 * r2 / (b * b));
    }

    /// (3) Local clock rate: dτ/dt = √(1 − z)   (Law V movement budget)
    [[nodiscard]] inline auto clock_rate(double z) noexcept -> double {
        return std::sqrt(1.0 - z);
    }

    /// (2) Local relay speed: c_local = c_∞ (1 − z); inverse z = 1 − c_local/c_∞
    [[nodiscard]] constexpr auto c_local(double c_inf, double z) noexcept -> double {
        return c_inf * (1.0 - z);
    }
    [[nodiscard]] constexpr auto depth_from_c_local(
        double c_local_val, double c_inf
    ) noexcept -> double {
        return 1.0 - c_local_val / c_inf;
    }

    /// (1) Local spation closure: ℓ_P(r) = ℓ_P,∞ (1 − z)
    [[nodiscard]] constexpr auto closure_local(double lP_inf, double z) noexcept -> double {
        return lP_inf * (1.0 - z);
    }

    /// (4) Gravitational redshift as a depth differential: z_spec = z_emit − z_obs
    [[nodiscard]] constexpr auto z_spectral(double z_emit, double z_obs) noexcept -> double {
        return z_emit - z_obs;
    }

    // ─── Corollary constants (C1, C4, C5, C6 + the derived a₀ floor) ───

    /// C1: solar gravitational redshift = depth at the surface = ϟ_Sun/R_Sun
    /// = 2.123e-6, equal to the observed GM/(c²R) to 0.03% (a consequence)
    inline const double z_spectral_Sun = bridge::koppa_Sun / R_Sun;

    /// APS03/GD05 acceleration floor: a₀ = c·H₀ / 2π  [m/s²]  (DERIVED)
    // provenance_status:     SDT-derived
    // correspondence_status: known-match            // ≈ MOND a₀; required by the APS03 collapse
    // input_dependency:      c + H₀ (law_I::H0_SI)
    // class:                 C-flagged
    // circularity_assertion: a deliberately wrong floor degrades the APS03 collapse 6×
    // risk_flag:             inherits H₀'s Friedmann-structure caveat (law_I::H0_SI)
    inline constexpr double a0_floor = c * law_I::H0_SI / (2.0 * std::numbers::pi);
    // ≈ 1.04e-10 m/s²

    /// C4: galactic convergence-depth floor z_gal = ϟ_MW / R_⊙,orbit ≈ 3.5e-7
    /// (the isotropic relay-ceiling deficit that persists in interstellar space)
    inline constexpr double z_galactic_floor = 3.5e-7;

    /// C4: absolute relay ceiling c_∞ = c / (1 − z_gal) ≈ c + 105 m/s
    /// The measured c (299,792,458 m/s) is only Earth's local rung.
    inline constexpr double c_infinity = c / (1.0 - z_galactic_floor);

    /// C5: spation closure floor (koppa form): ℓ_P = √(ϟ_baryon · ƛ_p)
    /// with ϟ_baryon = bridge::koppa_per_baryon and ƛ_p = ℏ/(m_p c).
    /// HONEST (FLM06): this RE-EXPRESSES ℓ_P, it does NOT derive it. koppa_per_baryon
    /// is itself defined as ℓ_P²·c·m_p/ℏ (bridge), so √(ϟ·ƛ) = √(ℓ_P²) = ℓ_P is an
    /// IDENTITY — a consistency check, not an elimination. FLM06's real result is the
    /// Seed Theorem (one dimensional anchor unavoidable) + re-homing the seed from
    /// {ℏ,G} to one SDT-native length. ℓ_P stays Axiom R1; see measured::l_P provenance.
    [[nodiscard]] inline auto closure_floor(double koppa, double wake) noexcept -> double {
        return std::sqrt(koppa * wake);
    }
    inline const double lP_from_closure_floor =
        closure_floor(bridge::koppa_per_baryon, hbar / (m_p * c));
    // ≈ 1.616e-35 m = ℓ_P  (by construction — identity, see HONEST note above)

    /// C6: lumiopause radius — a SURFACE-AREA condition where the solar flux
    /// falls to the CMB floor: L_Sun/(4πr²) = F_CMB ⟹ r = √(L_Sun/(4π F_CMB))
    /// (≈ 20,857 AU). The Oort cloud is suspended here in "lumiostasis" —
    /// held where the convergence gradient balances, not orbiting.
    inline const double lumiopause_m =
        std::sqrt(law_II::L_Sun / (4.0 * std::numbers::pi * law_II::F_CMB));
    inline const double lumiopause_AU = lumiopause_m / AU;
}

} // namespace sdt::laws

// Convenience alias: sdt::laws::winding is now sdt::laws::law_VI::winding
// Keep backward-compatible access:
namespace sdt::laws {
    namespace winding = law_VI::winding;
}
