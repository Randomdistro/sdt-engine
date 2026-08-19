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
 *   Law VI:  Vortex Topology Quantisation   (Theorem T18, FLM07 lock closure)
 *
 * Status is carried per quantity. The engine contains a mixture of:
 *   irreducible seed, unit bridges, measured seats/anchors, derived relations,
 *   calibrated magnitudes, observed stickers, and shared-input constructions.
 * A formula is not independently predictive unless its provenance block says so.
 *
 * 9 axioms. 2 lemmas. 18 theorems.
 * One medium. One tick. One budget.
 *
 * Dependency contract:
 *   ℓ_P is the irreducible dimensional seed. c, k_B and e are unit bridges.
 *   {ℏ,m_e,m_p} occupy one mass/action seat. α is the hydrogen-spectroscopy
 *   koppa rung recorded by APS05/PPT02, a₀ is an atomic seat, and T_CMB is the
 *   measured mechanical boundary state of present convergence. Other measured
 *   values below are comparison or domain anchors labelled at point of use.
 *   Namespace membership never substitutes for item-level provenance.
 *
 *   Status:
 *     - Dimensionless invariant (no length/time scale)
 *     - Scoped to derivations where electron/atomic structure enters
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
 *   Provenance-scoped uses:
 *     - Setting electron-scale ratios (e.g., v_P / v_T in W=1 topology)
 *     - Internal atomic/quantum structure relations
 *
 *   Forbidden uses:
 *     - Fixing amplitudes or coefficients in z(r) for gravitational tests
 *     - Back-solving α from macroscopic observables
 *
 *   Every use of a measured or shared input in a canonical relation must be
 *   explicit. Derived, calibrated, observed and shared-input results must not
 *   be promoted across classes merely because they agree numerically.
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
 * This pins the contract: derive first, then validate; disclose every anchor.
 *
 * @author SDT Canonical Engine — James Tyndall, Melbourne, Australia
 * @date March 2026
 * @version 6.0 (Six-Law Framework)
 */

#include <algorithm>
#include <array>
#include <cmath>
#include <numbers>

namespace sdt::laws {

// ═══════════════════════════════════════════════════════════════════════
//  ACYCLIC DEPENDENCY LEDGER + VALIDATION ANCHORS
//  Every quantity below carries its own role: seed, unit bridge, seat,
//  spectroscopic derivation, measured mechanical boundary, validation anchor,
//  comparison datum, or derived identity. No list membership confers status.
//
//  The listed validation anchors are retained for empirical
//  checks. They are not upstream dependencies of the relations they validate.
// ═══════════════════════════════════════════════════════════════════════

namespace measured {
    // Numerical seed, bridges and seats; see each provenance block.
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
    // derivation basis {ℓ_P,c,ℏ,k_B,T_CMB,d=3} has no current dimension [A], so no
    // algebraic combination yields [C]; the Coulomb route e=√(αℏc/k_e) is a
    // definitional tautology (class F). e is an SI unit bridge.

    // CODATA 2018 measured values
    inline constexpr double alpha_inv   = 1.0 / alpha;                  // [-]      exact reciprocal in-engine

    // Validation anchors — currently retained for empirical checks only.
    // In a fully closed SDT derivation, these should follow from the base
    // invariants and SDT topology/relational structure.
    inline constexpr double a_0         = 5.291'772'109'03e-11;         // [m]      Bohr radius
    inline constexpr double r_e         = alpha * alpha * a_0;          // [m]      Hydrogen c-boundary; matches classical electron radius
    inline constexpr double R_p         = 8.414e-16;                    // [m]      Proton boundary radius (muonic H, 2019; "charge radius" is the literature's obfuscation)
    // NOTE: FLM07 selects q=4 before comparison; qℏ/(m_p c) agrees to 0.02%.
    inline constexpr double m_e         = 9.109'383'7015e-31;           // [kg]     Electron mass (NIST reference)
    inline constexpr double m_p         = 1.672'621'925'95e-27;         // [kg]     Proton mass (CODATA 2022)
    inline constexpr double m_n         = 1.674'927'500'56e-27;         // [kg]     Neutron mass (CODATA 2022)
    inline constexpr double m_d         = 3.343'583'7768e-27;           // [kg]     Deuteron mass (CODATA 2022)
    inline constexpr double m_t         = 5.007'356'7512e-27;           // [kg]     Triton mass (CODATA 2022)
    inline constexpr double m_He3       = 5.006'412'7862e-27;           // [kg]     Helion mass (CODATA 2022)
    inline constexpr double R_inf       = 1.097'373'156'8160e7;         // [m^-1]   Rydberg constant
    inline constexpr double Ry_eV       = 13.605'693'122'994;           // [eV]     Rydberg energy

    // Compton wavelengths derived from the mass/action seat
    inline constexpr double lambda_C_e  = h / (m_e * c);                // [m]      Electron Compton wavelength
    inline constexpr double lambda_C_p  = h / (m_p * c);                // [m]      Proton Compton wavelength

    // Planck units (derived from l_P)
    inline constexpr double t_P         = l_P / c;                      // [s]      Planck time
    inline constexpr double l_P3        = l_P * l_P * l_P;              // [m^3]    Planck volume

    // Radiation constant
    inline constexpr double a_rad       = 7.565'7e-16;                  // [J/m³/K⁴] Stefan radiation constant

    // CMB (FIRAS/COBE/Planck)
    inline constexpr double T_CMB       = 2.7255;                       // [K]      Present CMB temperature — MEASURED (FIRAS)

    // ── BOUNDARY-RELEASE FRAME — reclassified 2026-07-30 (James Christopher Tyndall-authorized) ──
    // T_rec and z_rec are NOT measured facts. They are the round textbook
    // epoch-frame ballparks (3000 K, 1100) and they were sitting inside the
    // measured derivation basis, which by the ruleset admits only CODATA / IAU / FIRAS
    // values. Found by the derivelist audit (F2): scoring a native result against
    // a round number penalised it — the CR13 release chain reads −0.90% against
    // 3000 K and +0.07% against the FIRAS-frame anchor below.
    // They are RETAINED at their legacy values so the ~10 downstream tools that
    // consume them do not silently change output; they are relabelled, not
    // re-valued. New work uses the *_release pair. Migration is OWED.
    // provenance_status:     epoch-frame ballpark — NOT a measured input
    // correspondence_status: round-number convention of the rival account
    inline constexpr double T_rec       = 3000.0;                       // [K]  LEGACY ballpark — do not cite as measured
    inline constexpr double z_rec       = 1100.0;                       // [-]  LEGACY ballpark — do not cite as measured

    /// The native boundary release: the CMB is the Clearing boundary's
    /// synchronized release, not a "recombination epoch". z is the FIRAS-frame
    /// observed value; the temperature is COMPUTED from it, never typed in.
    /// The native derivation chain (release wavelength ≈ 975 nm, octave count
    /// 1+z = 2^Δn ≈ 10.09 — CR07/CR13) is the open route to deriving both.
    inline constexpr double z_release   = 1089.0;                       // [-]  OBSERVED (FIRAS frame)
    inline constexpr double T_release   = T_CMB * (1.0 + z_release);    // [K]  = 2970.8 K, computed

    // Cosmological scale (observed, not SDT-derived; conditions Law I chain)
    // provenance_status:     external-input
    // correspondence_status: known-match
    // input_dependency:      measured-observable    // from H_0 + z_rec — H_0 is observed
    // class:                 X
    // circularity_assertion: DOES NOT pass delete-test — Law I chain conditioned on this value
    // risk_flag:             derive from BAO θ_s / r_s closure, or accept as observed scale
    inline constexpr double R_CMB       = 9.527e26;                     // [m]      Distance to the Clearing

    // Conversions
    inline constexpr double eV_to_J     = e_charge;                     // [J/eV]
    inline constexpr double MeV_to_J    = 1.0e6 * eV_to_J;              // [J/MeV]

    // Validation anchors for astrophysical scaling only.
    // These values are not part of the minimal external invariant set.
    inline constexpr double R_Sun       = 6.957e8;                      // [m]      Solar radius (IAU 2015)
    inline constexpr double AU          = 1.495'978'707e11;             // [m]      Astronomical unit (IAU 2012)

    // Nuclear (measured)
    inline constexpr double R_He        = 1.6755e-15;                   // [m]      He-4 boundary radius (lit.: "charge radius")

    // Coulomb constant (derived from SI)
    inline constexpr double k_e         = 8.987'551'7923e9;             // [N·m²/C²] Coulomb constant

    // Magnetic moments (in nuclear magnetons, CODATA 2022)
    inline constexpr double mu_P        = 2.792'847'344'63;             // [μ_N]    Proton
    inline constexpr double mu_N        = -1.913'042'76;                // [μ_N]    Neutron
    inline constexpr double mu_D        = 0.857'438'2335;               // [μ_N]    Deuteron
    inline constexpr double mu_T        = 2.978'962'4650;               // [μ_N]    Triton
    inline constexpr double mu_He3      = -2.127'625'3498;              // [μ_N]    Helion
    inline constexpr double mu_alpha    = 0.0;                          // [μ_N]    Alpha (spin-0)

    // Deuteron electric quadrupole moment (OBSERVED spectroscopy anchor;
    // Pachucki 2020, Eq. 24; not a CODATA constant).
    inline constexpr double Q_deuteron_fm2 = 0.285'699;                 // [fm²]

    // Nuclear binding energies derived from the measured 2022 nuclear masses.
    // NP05 (EXCLUDED): binding energy is not a displaced-volume difference —
    // the volume-price hypothesis E=P·ΔV failed (spread 45× across reactions;
    // a units slip masked it as P_conv). Successor under test: E_bind = ℏ·Δω,
    // the change in meshed-circulation frequency (CQ41 gear-frequency binding).
    inline constexpr double B_deuteron  =
        ((m_p + m_n - m_d) * c * c) / MeV_to_J;
    inline constexpr double B_triton    =
        ((m_p + 2.0 * m_n - m_t) * c * c) / MeV_to_J;
    inline constexpr double B_helion    =
        ((2.0 * m_p + m_n - m_He3) * c * c) / MeV_to_J;
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
    // FLM06 (spation-scale closure) SEED THEOREM — negative result: N is
    // RELATIONALLY fixed (N² = S_boundary/4π below), but it CANNOT be built
    // absolutely (~10⁶¹) from the ℏ/G-free derivation basis {R_CMB,c,k_B,T_CMB,z_rec}:
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
    // input_dependency:      primitive-derivation basis
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

    // CR05 pressure/Hubble closure is excluded. Its direct tool hardcodes
    // H₀=67.4, imports Ω normalisations, predicts H₀=1.25×10⁴⁹ km/s/Mpc on
    // its actual native route, and misses R_CMB by 50.8%. The candidate
    // P∝(1+z)^4 and fourfold freeze-out narratives therefore remain research
    // hypotheses, not engine laws. No CR05 H₀, gamma or freeze-out API is
    // exposed here.
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
//  FLM07 CLOSE-PACKED RELAY-LOCK GEOMETRY
// ═══════════════════════════════════════════════════════════════════════

namespace lock_geometry {
    inline constexpr double tetrahedral_void_radius_ratio =
        std::numbers::sqrt3 / std::numbers::sqrt2 - 1.0;
    inline constexpr double octahedral_void_radius_ratio =
        std::numbers::sqrt2 - 1.0;
    inline constexpr double tetrahedral_resistance_price =
        4.0 * tetrahedral_void_radius_ratio * tetrahedral_void_radius_ratio
        * tetrahedral_void_radius_ratio;
    inline constexpr double octahedral_resistance_price =
        6.0 * octahedral_void_radius_ratio * octahedral_void_radius_ratio
        * octahedral_void_radius_ratio;
    inline constexpr int trefoil_lock_coordination =
        tetrahedral_resistance_price < octahedral_resistance_price ? 4 : 6;
    static_assert(trefoil_lock_coordination == 4);

    // TD03 / B37: the W+1 tetrahedral channel set is a spherical 2-design.
    // Rank two is exactly isotropic, M2(n)=1/3, while the first directional
    // fingerprint is rank four:
    //   M4(n) = [1 + 4(nx²ny² + nx²nz² + ny²nz²)]/9
    // for a unit direction n. Hence M4 spans [1/9, 7/27], against the
    // isotropic continuum value 1/5. This is a standing prediction; no
    // measurement is presently available and B37 remains outside the tally.
    namespace rank4 {
        using Direction = std::array<double, 3>;

        inline constexpr double inverse_sqrt3 =
            1.0 / std::numbers::sqrt3;
        inline constexpr std::array<Direction, 4> channels = {{
            { inverse_sqrt3,  inverse_sqrt3,  inverse_sqrt3},
            { inverse_sqrt3, -inverse_sqrt3, -inverse_sqrt3},
            {-inverse_sqrt3,  inverse_sqrt3, -inverse_sqrt3},
            {-inverse_sqrt3, -inverse_sqrt3,  inverse_sqrt3}
        }};

        inline constexpr double second_moment = 1.0 / 3.0;
        inline constexpr double fourth_moment_min = 1.0 / 9.0;
        inline constexpr double fourth_moment_max = 7.0 / 27.0;
        inline constexpr double isotropic_fourth_moment = 1.0 / 5.0;

        [[nodiscard]] constexpr auto norm_squared(
            const Direction& direction
        ) noexcept -> double {
            return direction[0] * direction[0]
                 + direction[1] * direction[1]
                 + direction[2] * direction[2];
        }

        [[nodiscard]] constexpr auto moment2(
            const Direction& direction
        ) noexcept -> double {
            const double norm2 = norm_squared(direction);
            double sum = 0.0;
            for (const auto& channel : channels) {
                const double projection =
                    channel[0] * direction[0]
                    + channel[1] * direction[1]
                    + channel[2] * direction[2];
                sum += projection * projection;
            }
            return sum / (4.0 * norm2);
        }

        [[nodiscard]] constexpr auto moment4(
            const Direction& direction
        ) noexcept -> double {
            const double norm2 = norm_squared(direction);
            double sum = 0.0;
            for (const auto& channel : channels) {
                const double projection =
                    channel[0] * direction[0]
                    + channel[1] * direction[1]
                    + channel[2] * direction[2];
                const double square = projection * projection;
                sum += square * square;
            }
            return sum / (4.0 * norm2 * norm2);
        }

        [[nodiscard]] constexpr auto moment4_analytic(
            const Direction& direction
        ) noexcept -> double {
            const double x2 = direction[0] * direction[0];
            const double y2 = direction[1] * direction[1];
            const double z2 = direction[2] * direction[2];
            const double norm2 = x2 + y2 + z2;
            const double pair_sum =
                (x2 * y2 + x2 * z2 + y2 * z2)
                / (norm2 * norm2);
            return (1.0 + 4.0 * pair_sum) / 9.0;
        }

        static_assert(
            moment2({1.0, 0.0, 0.0}) > second_moment - 1.0e-15
            && moment2({1.0, 0.0, 0.0}) < second_moment + 1.0e-15
        );
        static_assert(
            moment4({1.0, 0.0, 0.0})
                > fourth_moment_min - 1.0e-15
            && moment4({1.0, 0.0, 0.0})
                < fourth_moment_min + 1.0e-15
        );
        static_assert(
            moment4({1.0, 1.0, 1.0})
                > fourth_moment_max - 1.0e-15
            && moment4({1.0, 1.0, 1.0})
                < fourth_moment_max + 1.0e-15
        );
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  LAW III — CONVERGENT BOUNDARY PRESSURE (Theorems T3–T4)
//
//  Force = occluded convergence. Same mechanism: Coulomb, gravity, nuclear.
// ═══════════════════════════════════════════════════════════════════════

namespace law_III {
    using namespace measured;

    /// FLM07 target-free proton lock boundary [m].
    inline constexpr double R_p_lock =
        static_cast<double>(lock_geometry::trefoil_lock_coordination)
        * hbar / (m_p * c);

    /// Effective pressure from the EMC04 electropause balance [Pa]:
    /// P_eff = 4 αℏc/(π R_p_lock² r_e²).
    // provenance_status:     SDT-derived
    // correspondence_status: known-match
    // input_dependency:      hydrogen spectroscopic rung/seat + FLM07 lock
    // class:                 C
    // circularity_assertion: measured R_p, k_e and e absent from forward form
    // risk_flag:             inherits the FLM07 minimum-resistance-path premise
    inline constexpr double P_eff =
        4.0 * alpha * hbar * c
        / (std::numbers::pi * R_p_lock * R_p_lock * r_e * r_e);
    // = 5.227e31 Pa

    /// Transfer function: f = P_eff / P_conv
    // provenance_status:     SDT-computed
    // correspondence_status: internal-only
    // input_dependency:      derived P_eff + observed Clearing boundary through P_conv
    // class:                 B-conditioned
    // circularity_assertion: target-free ratio; absolute value inherits measured R_CMB
    // risk_flag:             not an independent cosmological prediction
    inline constexpr double f_transfer = P_eff / law_I::P_conv;
    // = 2.125e-17
    // CR05 does not close R_CMB; f therefore remains observed-boundary
    // conditioned even though the atomic numerator is now target-free.

    /// Interaction radius: R_charge = sqrt(R_p_lock × r_e)
    /// Resolves e-e / p-p / e-p having same coupling strength
    // provenance_status:     SDT-derived
    // correspondence_status: known-match
    // input_dependency:      FLM07 lock + hydrogen spectroscopic rung/seat
    // class:                 C
    // circularity_assertion: measured R_p absent
    // risk_flag:             same FLM07 premise as P_eff
    inline const double R_charge = std::sqrt(R_p_lock * r_e);
    // = 1.5396e-15 m

    /// Occlusion force between two bodies (Theorem T4)
    /// F = (π/4) P_eff R1² R2² / r²
    // provenance_status:     SDT-derived
    // correspondence_status: known-match            // 1/r² structure: Coulomb, gravity, nuclear
    // input_dependency:      primitive-derivation basis    // STRUCTURE only; the coefficient P_eff is class E
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
    /// CORRECTED 2026-07-07 (interchange sweep, James Christopher Tyndall-authorized): the handed force
    /// transfers movement through redirection COUNT — occluded AREA ∝ Z, so the effective
    /// radius is √Z·R_p_lock, giving F = Z times the unit interaction
    /// strength (measured Coulomb scaling is the comparison).
    /// The previous R_nuc = Z·R_p (excluded NP12 geometry, inlined here and missed by three
    /// audits) gave F ∝ Z² — factor Z wrong for every Z ≥ 2. Per-body radii in F_occlusion
    /// are physical only for gravity-class occlusion (real boundaries); the handed force
    /// signature is (Z₁·Z₂)·(R_p²r_e²) — count product × one universal unit-area.
    [[nodiscard]] inline auto F_nuclear_electron(
        int Z, double r
    ) noexcept -> double {
        double R_nuc = std::sqrt(static_cast<double>(Z)) * R_p_lock;
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
    // input_dependency:      primitive-derivation basis
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

    /// FLM07/FLM15 relay-lock kernel.
    ///
    /// The glancing boundary is |cos(theta)| = k(r). For isotropic
    /// mu=|cos(theta)|, mu is uniform on [0,1], so the fraction whose
    /// projected phase demand remains within one-spation relay capacity is
    /// f_lock=P(mu<=k)=clip(k,0,1).
    ///
    /// Domain: radius >= 0 and boundary > 0.
    // provenance_status:     SDT-derived (FLM07 glancing + FLM15 R4)
    // correspondence_status: internal-only
    // input_dependency:      supplied mechanical boundary
    // class:                 B
    // circularity_assertion: target-free; no particle mass or comparison value
    [[nodiscard]] inline auto relay_lock_fraction(
        double radius, double boundary
    ) noexcept -> double {
        if (radius <= 0.0) return 0.0;
        if (radius >= boundary) return 1.0;
        return std::sqrt(radius / boundary);
    }

    /// Complement whose projected phase demand exceeds relay capacity.
    [[nodiscard]] inline auto wake_emitting_fraction(
        double radius, double boundary
    ) noexcept -> double {
        return 1.0 - relay_lock_fraction(radius, boundary);
    }

    /// Spherical engaged volume inside a supplied c-boundary:
    /// 4π∫r²√(r/b)dr = 8πb³/7.
    [[nodiscard]] constexpr auto locked_engaged_volume_sphere(
        double boundary
    ) noexcept -> double {
        return 8.0 * std::numbers::pi * boundary * boundary * boundary / 7.0;
    }

    /// Over-capacity wake-emitting complement: 4πb³/21.
    [[nodiscard]] constexpr auto wake_volume_sphere(
        double boundary
    ) noexcept -> double {
        return 4.0 * std::numbers::pi * boundary * boundary * boundary / 21.0;
    }

    /// Law-IV isotropic reorganisation resistance: (P_conv/3)V_eng [J].
    [[nodiscard]] constexpr auto resistance_from_engaged_volume(
        double engaged_volume
    ) noexcept -> double {
        return (law_I::P_conv / 3.0) * engaged_volume;
    }

    /// Synchrony resistance relative to separately engaged components [J].
    /// A coherent overlap has joint_volume < parts_volume and therefore a
    /// negative resistance change (a binding/reorganisation saving).
    [[nodiscard]] constexpr auto synchrony_resistance_delta(
        double joint_volume, double parts_volume
    ) noexcept -> double {
        return (law_I::P_conv / 3.0) * (joint_volume - parts_volume);
    }

    // ─── APS03 / B34 — convergence-pressure drafting floor ─────────────
    //
    // T1/T10 + FLM15. Isotropic pressure contributes its normal second
    // moment 1/3. The relay-lock integral engages 6/7 of a spherical domain.
    // Averaged over that domain, the Law-IV phase-resistance load density is
    //
    //   rho_eng = [(P_conv/3) V_eng] / (V c^2)
    //           = 2 P_conv / (7 c^2).
    //
    // The convergence boundary supplies |grad P| = P_conv/(3 R_CMB), hence
    //
    //   a_floor = |grad P|/rho_eng = 7 c^2/(6 R_CMB).
    //
    // APS03 validates the 1/3 and 6/7 by independent quadrature, reruns the
    // unchanged SPARC/atomic controls, and passes both wrong-solid-angle and
    // scrambled-exposure controls. The result is COMPUTED, not an independent
    // cosmological prediction: R_CMB remains an observed boundary and shares
    // provenance with the expansion-rate correspondence used for comparison.
    //
    // provenance_status:     SDT-computed (T1/T10 + FLM15)
    // correspondence_status: known-match (8.28% vs low-acceleration floor)
    // input_dependency:      measured R_CMB boundary, c, Law-I pressure
    // class:                 B-conditioned / COMPUTED
    // circularity_assertion: target value absent from forward function
    // risk_flag:             R_CMB is external and shares cosmological provenance
    namespace convergence_floor {
        inline constexpr double angular_gradient_fraction = 1.0 / 3.0;
        inline constexpr double engaged_volume_fraction = 6.0 / 7.0;

        [[nodiscard]] constexpr auto full_sphere_volume(
            double boundary
        ) noexcept -> double {
            return 4.0 * std::numbers::pi
                 * boundary * boundary * boundary / 3.0;
        }

        [[nodiscard]] constexpr auto average_resistance_density(
            double boundary
        ) noexcept -> double {
            return resistance_from_engaged_volume(
                locked_engaged_volume_sphere(boundary)
            ) / (full_sphere_volume(boundary) * c * c);
        }

        [[nodiscard]] constexpr auto pressure_gradient(
            double boundary
        ) noexcept -> double {
            return angular_gradient_fraction * law_I::P_conv / boundary;
        }

        [[nodiscard]] constexpr auto acceleration(
            double boundary
        ) noexcept -> double {
            return pressure_gradient(boundary)
                 / average_resistance_density(boundary);
        }

        inline constexpr double cosmological_acceleration =
            acceleration(law_I::R_CMB);
    }

    // ─── FD02 / B16 — monatomic relay-lock transport ───────────────────
    //
    // For a supplied mechanical atomic boundary b, FLM15 engages 6/7 of
    // the spherical domain.  Two atoms contact at diameter 2b, giving the
    // reduced collision measure (6/7)(2b)^2.  The pi carried by the physical
    // projected area is already integrated in the isotropic hard-lock
    // collision moments below.
    //
    // The dimensionless hard-lock collision integrals are unity.  Solving
    // their diffusion, trace-free traction and energy moments gives 3/8,
    // 5/16 and 75/64 respectively.  These are geometry coefficients, not
    // property-specific fits.  At fixed pressure:
    //   dynamic viscosity       proportional to T^(1/2)
    //   thermal conductivity    proportional to T^(1/2)
    //   self diffusivity        proportional to T^(3/2)
    // because number density contributes the extra inverse-T only to D.
    //
    // provenance_status:     SDT-computed (FD02 collision integral)
    // correspondence_status: whole-range argon curves, RMS <10%
    // input_dependency:      T, pressure, Law-IV load, mechanical boundary
    // class:                 C
    // circularity_assertion: transport observations do not enter this path
    // risk_flag:             hard-lock/dilute-monatomic domain only
    namespace transport {
        inline constexpr double lock_volume_fraction = 6.0 / 7.0;
        inline constexpr double diffusion_moment = 3.0 / 8.0;
        inline constexpr double traction_moment = 5.0 / 16.0;
        inline constexpr double energy_moment = 75.0 / 64.0;

        inline constexpr double viscosity_temperature_exponent = 0.5;
        inline constexpr double conductivity_temperature_exponent = 0.5;
        inline constexpr double diffusivity_fixed_pressure_exponent = 1.5;

        struct MonatomicState {
            double dynamic_viscosity_Pa_s;
            double thermal_conductivity_W_mK;
            double self_diffusivity_m2_s;
            double collision_measure_m2;
        };

        /// FLM15 lock-weighted collision measure for two equal boundaries.
        [[nodiscard]] constexpr auto collision_measure(
            double mechanical_boundary_m
        ) noexcept -> double {
            const double diameter = 2.0 * mechanical_boundary_m;
            return lock_volume_fraction * diameter * diameter;
        }

        /// Dilute monatomic transport from one common relay-lock collision
        /// kernel.  No observed transport coefficient is an argument.
        [[nodiscard]] inline auto monatomic_state(
            double temperature_K,
            double pressure_Pa,
            double particle_load_kg,
            double mechanical_boundary_m
        ) noexcept -> MonatomicState {
            const double collision =
                collision_measure(mechanical_boundary_m);
            const double traction_speed =
                std::sqrt(
                    particle_load_kg * k_B * temperature_K
                    / std::numbers::pi
                );
            const double relay_speed =
                std::sqrt(
                    k_B * temperature_K
                    / (std::numbers::pi * particle_load_kg)
                );
            const double number_density =
                pressure_Pa / (k_B * temperature_K);

            return {
                traction_moment * traction_speed / collision,
                energy_moment * k_B * relay_speed / collision,
                diffusion_moment * relay_speed
                    / (number_density * collision),
                collision
            };
        }
    }

    /// Electron exclusion volume  [m³]
    inline constexpr double V_disp_e = 3.0 * m_e * l_P3 * c * c / law_I::Phi;
    // = 9.988e-62 m³

    /// Proton exclusion volume  [m³]
    inline constexpr double V_disp_p = 3.0 * m_p * l_P3 * c * c / law_I::Phi;
    // = 1.834e-58 m³

    /// Electron exclusion radius from V_disp  [m]
    inline const double R_excl_e =
        std::cbrt(3.0 * V_disp_e / (4.0 * std::numbers::pi));

    /// Proton exclusion radius from V_disp  [m]
    inline const double R_excl_p =
        std::cbrt(3.0 * V_disp_p / (4.0 * std::numbers::pi));

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

    inline const ParticleRadii electron_radii = {
        R_excl_e,
        r_e,             // R_wake   2.818e-15 m
        lambda_C_e       // R_quantum: full Compton wavelength
    };

    inline const ParticleRadii proton_radii = {
        R_excl_p,
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
    // input_dependency:      primitive-derivation basis
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
    inline const double k_proton_surface =
        alpha_inv * std::sqrt(R_p / a_0);

    /// c-boundary of hydrogen: ϟ = α²a₀ = r_e ≈ 2.818 fm
    inline constexpr double koppa_hydrogen = r_e;
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

    /// T17 circular-orbit bridge: ϟ = 4π²r³/(T²c²).
    /// This is the period form of koppa(v, r) with v = 2πr/T. It is an
    /// algebraic identity / shared-input reparameterisation, not an independent
    /// ephemeris prediction.
    [[nodiscard]] constexpr auto koppa_from_circular_period(
        double orbital_radius, double orbital_period
    ) noexcept -> double {
        return 4.0 * std::numbers::pi * std::numbers::pi
             * orbital_radius * orbital_radius * orbital_radius
             / (orbital_period * orbital_period * c * c);
    }

    /// T17 circular speed from a supplied koppa and radius.
    [[nodiscard]] inline auto circular_speed_from_koppa(
        double koppa_length, double orbital_radius
    ) noexcept -> double {
        return c * std::sqrt(koppa_length / orbital_radius);
    }

    /// T17 radial acceleration magnitude: a = c²ϟ/r².
    [[nodiscard]] constexpr auto radial_acceleration_from_koppa(
        double koppa_length, double radius
    ) noexcept -> double {
        return c * c * koppa_length / (radius * radius);
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
    // input_dependency:      primitive-derivation basis    // l_P, c, m_p, hbar only — G and M never entered
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

    // ─── CR17 / CR08 / B15 — release standing-equilibrium scale ────────
    //
    // At baryon/radiation resistance equality, Prop 13 gives the local
    // obstacle count n_b = n_b,0 N^3 without metric expansion. Integrating
    // the per-baryon phase-resistance length over a uniform sphere gives
    //   v_orb/r = c sqrt[(4 pi/3) koppa_b n_b].
    // Radial Law-III work to infinity is c^2 koppa/r per unit resistance;
    // equating it to v^2/2 gives bridge::v_escape and its factor two without
    // importing a source parameter. A standing relay
    // mode makes one acoustic round trip in that escape-response time:
    //   Gamma_esc = c sqrt[(8 pi/3) koppa_b n_b],
    //   L_eq = c_s/(2 Gamma_esc),  L_present = N_eq L_eq.
    //
    // T2/T3/T10 + Prop 13. No BAO ruler, H_0, R_CMB, metric history, G,
    // source mass or source parameter enters. The external cross-observable
    // input is eta from BBN deuterium; the result is therefore COMPUTED with
    // shared BBN/FIRAS provenance, not an independent cosmological result.
    namespace release_acoustics {
        /// Mathematical constant ζ(3), used in the black-body photon count.
        inline constexpr double zeta3 = 1.2020569031595943;

        /// Local external input: BBN-deuterium baryon/photon number ratio.
        /// It is neither fitted by B15 nor promoted to the SDT derivation basis.
        inline constexpr double eta_bbn_deuterium = 6.1e-10;

        /// At rho_b=rho_gamma, R=(3/4)(rho_b/rho_gamma)=3/4 exactly.
        inline constexpr double equality_loading = 3.0 / 4.0;

        /// Exact parsec definition expressed as a local output-unit conversion.
        inline constexpr double megaparsec_m = 3.0856775814913673e22;

        struct EqualityState {
            double photon_count_m3;
            double present_baryon_count_m3;
            double epoch_index;
            double baryon_count_m3;
            double sound_speed_ms;
            double escape_rate_s;
            double standing_radius_m;
            double present_equivalent_scale_m;
        };

        [[nodiscard]] constexpr auto photon_count(
            double temperature_K
        ) noexcept -> double {
            const double thermal_wave_number =
                k_B * temperature_K / (h * c);
            return 16.0 * std::numbers::pi * zeta3
                * thermal_wave_number
                * thermal_wave_number
                * thermal_wave_number;
        }

        [[nodiscard]] constexpr auto baryon_count(
            double epoch_index,
            double present_count_m3
        ) noexcept -> double {
            return present_count_m3
                * epoch_index * epoch_index * epoch_index;
        }

        [[nodiscard]] inline auto sound_speed(
            double baryon_loading
        ) noexcept -> double {
            return c / std::sqrt(3.0 * (1.0 + baryon_loading));
        }

        [[nodiscard]] inline auto uniform_escape_rate(
            double baryon_count_m3
        ) noexcept -> double {
            return c * std::sqrt(
                (8.0 * std::numbers::pi / 3.0)
                * koppa_per_baryon
                * baryon_count_m3
            );
        }

        [[nodiscard]] inline auto equality_state() noexcept
            -> EqualityState {
            const double photons = photon_count(T_CMB);
            const double present_baryons =
                eta_bbn_deuterium * photons;
            const double radiation_resistance_density =
                a_rad * T_CMB * T_CMB * T_CMB * T_CMB / (c * c);
            const double baryon_resistance_density =
                present_baryons * m_p;
            const double epoch_index =
                baryon_resistance_density
                / radiation_resistance_density;
            const double local_baryons = baryon_count(
                epoch_index,
                present_baryons
            );
            const double relay_speed = sound_speed(equality_loading);
            const double response_rate =
                uniform_escape_rate(local_baryons);
            const double standing_radius =
                relay_speed / (2.0 * response_rate);
            return {
                photons,
                present_baryons,
                epoch_index,
                local_baryons,
                relay_speed,
                response_rate,
                standing_radius,
                epoch_index * standing_radius
            };
        }

        inline const EqualityState state = equality_state();
        inline const double present_equivalent_scale_m =
            state.present_equivalent_scale_m;
        inline const double present_equivalent_scale_Mpc =
            present_equivalent_scale_m / megaparsec_m;

        [[nodiscard]] inline auto optical_depth(
            double mechanical_boundary_m
        ) noexcept -> double {
            return state.baryon_count_m3
                * law_IV::transport::collision_measure(
                    mechanical_boundary_m
                )
                * state.standing_radius_m;
        }
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

    // ─── GOM06 / B09 — eccentric-binary resistance radiation ───────────
    //
    // A constant total Law-IV resistance has no time-varying monopole, and
    // centre-of-resistance motion has no dipole.  The first radiating object is
    // therefore the trace-free resistance quadrupole
    //   Q_ij = sum_a rho_a (x_ai x_aj - delta_ij r_a^2/3).
    //
    // The relay-shear coefficient is geometric rather than imported:
    //   <|TT_n(S)|^2>_sphere / |S|^2 = 2/5,
    //   quadratic work contributes 1/2,
    //   so the angular flux weight is (1/2)(2/5) = 1/5.
    // A circular two-seat orbit gives <Q'''_ij Q'''_ij> = 32 eta^2
    // in units of rho_tot^2 a^4 omega^6.  Orbital-resistance loss then gives
    //   dP_b/dt = -6 pi (1/5)(32) eta z_orb^(5/2) F(e).
    // The GOM06 direct instrument independently obtains 1/5 and 32 by angular
    // and orbital integration, verifies the eccentric enhancement by the same
    // solver, and passes B1913+16 plus J0737-3039A without G, M, GM or aliases.
    //
    // provenance_status:     SDT-derived
    // correspondence_status: independently tested on two timed binaries
    // input_dependency:      P_b, e, periastron timing, Einstein delay
    // class:                 C
    // circularity_assertion: passes delete-test — dP_b/dt enters comparison only
    // risk_flag:             periastron and clock-depth relations consume B10/GOM22
    namespace binary_radiation {
        inline constexpr double sphere_tt_ratio = 2.0 / 5.0;
        inline constexpr double quadratic_work_fraction = 1.0 / 2.0;
        inline constexpr double angular_flux_weight =
            quadratic_work_fraction * sphere_tt_ratio;       // 1/5
        inline constexpr double circular_quadrupole_norm = 32.0;

        /// Orbital depth z_orb = koppa_total/a from anomalous periastron motion.
        [[nodiscard]] constexpr auto depth_from_periastron_timing(
            double orbital_period_s,
            double eccentricity,
            double periastron_advance_deg_per_year
        ) noexcept -> double {
            const double seconds_per_year = 365.25 * 86400.0;
            const double advance_per_orbit =
                periastron_advance_deg_per_year
                * std::numbers::pi / 180.0
                * orbital_period_s / seconds_per_year;
            return advance_per_orbit
                 * (1.0 - eccentricity * eccentricity)
                 / (6.0 * std::numbers::pi);
        }

        /// Companion share f of total phase resistance from the Einstein-delay
        /// amplitude: gamma*n/(e*z) = f(1+f), with n=2pi/P_b.
        [[nodiscard]] inline auto companion_resistance_fraction(
            double orbital_period_s,
            double eccentricity,
            double orbital_depth,
            double einstein_delay_s
        ) noexcept -> double {
            const double mean_motion =
                2.0 * std::numbers::pi / orbital_period_s;
            const double timing_ratio =
                einstein_delay_s * mean_motion
                / (eccentricity * orbital_depth);
            return 0.5 * (
                std::sqrt(1.0 + 4.0 * timing_ratio) - 1.0
            );
        }

        /// Symmetric reduced-resistance ratio eta=f(1-f).
        [[nodiscard]] constexpr auto symmetric_resistance_ratio(
            double companion_fraction
        ) noexcept -> double {
            return companion_fraction * (1.0 - companion_fraction);
        }

        /// Exact orbit average recovered by the GOM06 resistance-quadrupole
        /// integration; F(0)=1.
        [[nodiscard]] inline auto eccentricity_enhancement(
            double eccentricity
        ) noexcept -> double {
            const double e2 = eccentricity * eccentricity;
            const double numerator =
                1.0 + (73.0 / 24.0) * e2 + (37.0 / 96.0) * e2 * e2;
            return numerator / std::pow(1.0 - e2, 3.5);
        }

        /// Binary period loss [s/s] from timing-derived depth and resistance
        /// ratio.  The factor 6pi follows from E_orb proportional to -1/a and
        /// P_b proportional to a^(3/2); all remaining factors are integrated
        /// resistance geometry.
        [[nodiscard]] inline auto period_decay(
            double orbital_depth,
            double eta,
            double eccentricity
        ) noexcept -> double {
            return -6.0 * std::numbers::pi
                 * angular_flux_weight
                 * circular_quadrupole_norm
                 * eta
                 * std::pow(orbital_depth, 2.5)
                 * eccentricity_enhancement(eccentricity);
        }

        /// Complete target-independent timing path.  The observed period decay
        /// is deliberately absent from the function signature.
        [[nodiscard]] inline auto period_decay_from_timing(
            double orbital_period_s,
            double eccentricity,
            double periastron_advance_deg_per_year,
            double einstein_delay_s
        ) noexcept -> double {
            const double depth = depth_from_periastron_timing(
                orbital_period_s,
                eccentricity,
                periastron_advance_deg_per_year
            );
            const double fraction = companion_resistance_fraction(
                orbital_period_s,
                eccentricity,
                depth,
                einstein_delay_s
            );
            return period_decay(
                depth,
                symmetric_resistance_ratio(fraction),
                eccentricity
            );
        }
    }

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
    // risk_flag:             the former 96/5 debt is cleared by the GOM06/B09
    //                        resistance-quadrupole angular and orbit integrals above

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

    // ─── APS14 — Multi-electron dodecardinal resistance closure ─────────
    // T5–T7 / FLM15: the polar dyad remains fixed; added n=2 p lanes occupy
    // the six-ring in three 120-degree lanes followed by their antipodes.
    // Pair prices are exact geometry:
    //   s dyad       8/7 = V_lock/(pi b^3)
    //   1s–2s/p      7/8 = unlike-n relative phase (one shared n^3 period)
    //   2s–2p        pi/3 (60-degree glancing arc/chord)
    //   p 60 deg     1
    //   p 120 deg    (6/7) counterphase_path/chord + 1/14
    //   p 180 deg    (1/7)(1/2) = 1/14
    // The state is the minimum Law-IV resistance in independent shell radii.
    // No measured ionisation energy or element-specific screening enters.
    namespace dodecardinal {
        inline constexpr double lock_fraction = 6.0 / 7.0;
        inline constexpr double wake_fraction = 1.0 / 7.0;
        inline constexpr double coincident_synchrony = 1.0 / 2.0;
        inline constexpr double s_dyad_resistance = 8.0 / 7.0;
        inline constexpr double sp_resistance = std::numbers::pi / 3.0;
        inline constexpr double p60_resistance = 1.0;
        inline constexpr double p180_resistance =
            wake_fraction * coincident_synchrony;

        [[nodiscard]] inline auto complete_elliptic_k_parameter(
            double parameter
        ) noexcept -> double {
            double a = 1.0;
            double b = std::sqrt(1.0 - parameter);
            for (int iteration = 0; iteration < 16; ++iteration) {
                const double next_a = 0.5 * (a + b);
                const double next_b = std::sqrt(a * b);
                a = next_a;
                b = next_b;
            }
            return std::numbers::pi / (2.0 * a);
        }

        [[nodiscard]] inline auto counterphase_to_chord(
            double angle
        ) noexcept -> double {
            const double cosine = std::cos(angle);
            const double parameter = (1.0 - cosine) / 2.0;
            const double path_inverse =
                complete_elliptic_k_parameter(parameter)
                / std::numbers::pi;
            const double chord_inverse =
                1.0 / std::sqrt(2.0 - 2.0 * cosine);
            return path_inverse / chord_inverse;
        }

        [[nodiscard]] inline auto p120_resistance() noexcept -> double {
            return lock_fraction * counterphase_to_chord(
                2.0 * std::numbers::pi / 3.0
            ) + p180_resistance;
        }

        struct Seat {
            int n;
            int group;
            std::array<double, 3> direction;
        };

        struct State {
            double energy_ry;
            double energy_eV;
            std::array<double, 3> radii_a0;
            double force_residual;
            int group_count;
            bool converged;
        };

        [[nodiscard]] inline auto make_seats(
            int electrons, std::array<Seat, 10>& seats
        ) noexcept -> int {
            if (electrons <= 0) {
                return 0;
            }
            const int inner_count = std::min(2, electrons);
            for (int index = 0; index < inner_count; ++index) {
                seats[index] = {
                    1,
                    0,
                    {0.0, 0.0, index == 0 ? 1.0 : -1.0}
                };
            }
            static constexpr int ring_order[6] = {0, 2, 4, 3, 5, 1};
            const int outer_count = std::max(0, electrons - 2);
            for (int index = 0; index < outer_count; ++index) {
                if (index < 2) {
                    seats[inner_count + index] = {
                        2,
                        1,
                        {0.0, 0.0, index == 0 ? 1.0 : -1.0}
                    };
                } else {
                    const int ring_index = ring_order[index - 2];
                    const double angle = std::numbers::pi / 6.0
                        + static_cast<double>(ring_index)
                        * std::numbers::pi / 3.0;
                    seats[inner_count + index] = {
                        2,
                        2,
                        {std::cos(angle), std::sin(angle), 0.0}
                    };
                }
            }
            return inner_count + outer_count;
        }

        [[nodiscard]] inline auto direction_cosine(
            const Seat& first, const Seat& second
        ) noexcept -> double {
            return first.direction[0] * second.direction[0]
                 + first.direction[1] * second.direction[1]
                 + first.direction[2] * second.direction[2];
        }

        [[nodiscard]] inline auto pair_resistance(
            const Seat& first, const Seat& second
        ) noexcept -> double {
            if (first.n != second.n) {
                return 7.0 / 8.0;
            }
            const bool same_group = first.group == second.group;
            const double cosine = direction_cosine(first, second);
            if (same_group && (first.group == 0 || first.group == 1)) {
                return s_dyad_resistance;
            }
            if (same_group && first.group == 2 && cosine < -1.0 + 1.0e-12) {
                return p180_resistance;
            }
            if (same_group && first.group == 2 && cosine < -0.5 + 1.0e-12) {
                return p120_resistance();
            }
            if (same_group && first.group == 2) {
                return p60_resistance;
            }
            if (!same_group) {
                return sp_resistance;
            }
            return 1.0;
        }

        [[nodiscard]] inline auto group_count(int electrons) noexcept -> int {
            if (electrons <= 0) return 0;
            if (electrons <= 2) return 1;
            if (electrons <= 4) return 2;
            return 3;
        }

        [[nodiscard]] inline auto state_energy_ry(
            int Z,
            int electrons,
            const std::array<double, 3>& log_radii
        ) noexcept -> double {
            std::array<Seat, 10> seats{};
            const int count = make_seats(electrons, seats);
            std::array<double, 3> radii{};
            for (int group = 0; group < group_count(electrons); ++group) {
                radii[group] = std::exp(log_radii[group]);
            }
            double energy = 0.0;
            for (int index = 0; index < count; ++index) {
                const Seat& seat = seats[index];
                const double radius = radii[seat.group];
                energy += static_cast<double>(seat.n * seat.n)
                    / (radius * radius)
                    - 2.0 * static_cast<double>(Z) / radius;
            }
            for (int first_index = 0; first_index < count; ++first_index) {
                const Seat& first = seats[first_index];
                const double first_radius = radii[first.group];
                for (
                    int second_index = first_index + 1;
                    second_index < count;
                    ++second_index
                ) {
                    const Seat& second = seats[second_index];
                    const double second_radius = radii[second.group];
                    const double cosine = direction_cosine(first, second);
                    const double distance_squared =
                        first_radius * first_radius
                        + second_radius * second_radius
                        - 2.0 * first_radius * second_radius * cosine;
                    if (distance_squared <= 1.0e-20) {
                        return 1.0e100;
                    }
                    energy += 2.0 * pair_resistance(first, second)
                        / std::sqrt(distance_squared);
                }
            }
            return energy;
        }

        [[nodiscard]] inline auto state_gradient(
            int Z,
            int electrons,
            const std::array<double, 3>& log_radii
        ) noexcept -> std::array<double, 3> {
            std::array<Seat, 10> seats{};
            const int count = make_seats(electrons, seats);
            const int groups = group_count(electrons);
            std::array<double, 3> radii{};
            std::array<double, 3> gradient{};
            for (int group = 0; group < groups; ++group) {
                radii[group] = std::exp(log_radii[group]);
            }
            for (int index = 0; index < count; ++index) {
                const Seat& seat = seats[index];
                const double radius = radii[seat.group];
                gradient[seat.group] +=
                    -2.0 * static_cast<double>(seat.n * seat.n)
                        / (radius * radius)
                    + 2.0 * static_cast<double>(Z) / radius;
            }
            for (int first_index = 0; first_index < count; ++first_index) {
                const Seat& first = seats[first_index];
                const double first_radius = radii[first.group];
                for (
                    int second_index = first_index + 1;
                    second_index < count;
                    ++second_index
                ) {
                    const Seat& second = seats[second_index];
                    const double second_radius = radii[second.group];
                    const double cosine = direction_cosine(first, second);
                    const double distance_squared =
                        first_radius * first_radius
                        + second_radius * second_radius
                        - 2.0 * first_radius * second_radius * cosine;
                    if (distance_squared <= 1.0e-20) {
                        gradient.fill(1.0e100);
                        return gradient;
                    }
                    const double distance = std::sqrt(distance_squared);
                    const double common =
                        -2.0 * pair_resistance(first, second)
                        / (distance * distance * distance);
                    gradient[first.group] += common * first_radius
                        * (first_radius - second_radius * cosine);
                    gradient[second.group] += common * second_radius
                        * (second_radius - first_radius * cosine);
                }
            }
            return gradient;
        }

        [[nodiscard]] inline auto solve_linear(
            std::array<std::array<double, 3>, 3> matrix,
            std::array<double, 3> rhs,
            int size,
            std::array<double, 3>& solution
        ) noexcept -> bool {
            for (int column = 0; column < size; ++column) {
                int pivot = column;
                for (int row = column + 1; row < size; ++row) {
                    if (
                        std::abs(matrix[row][column])
                        > std::abs(matrix[pivot][column])
                    ) {
                        pivot = row;
                    }
                }
                if (std::abs(matrix[pivot][column]) < 1.0e-12) {
                    return false;
                }
                if (pivot != column) {
                    std::swap(matrix[pivot], matrix[column]);
                    std::swap(rhs[pivot], rhs[column]);
                }
                for (int row = column + 1; row < size; ++row) {
                    const double factor =
                        matrix[row][column] / matrix[column][column];
                    for (int entry = column; entry < size; ++entry) {
                        matrix[row][entry] -=
                            factor * matrix[column][entry];
                    }
                    rhs[row] -= factor * rhs[column];
                }
            }
            for (int row = size - 1; row >= 0; --row) {
                double value = rhs[row];
                for (int column = row + 1; column < size; ++column) {
                    value -= matrix[row][column] * solution[column];
                }
                solution[row] = value / matrix[row][row];
            }
            return true;
        }

        [[nodiscard]] inline auto solve_state(
            int Z, int electrons
        ) noexcept -> State {
            if (electrons <= 0) {
                return {0.0, 0.0, {}, 0.0, 0, true};
            }
            if (Z <= 0 || electrons > 10) {
                return {0.0, 0.0, {}, 1.0e100, 0, false};
            }
            const int groups = group_count(electrons);
            State best{
                1.0e100,
                1.0e100,
                {},
                1.0e100,
                groups,
                false
            };
            static constexpr double starts[4] = {0.75, 1.0, 1.5, 2.0};
            constexpr double lower = -6.907755278982137;
            constexpr double upper = 3.912023005428146;
            constexpr double hessian_step = 1.0e-5;

            for (double scale : starts) {
                std::array<double, 3> position{};
                position[0] = std::log(scale / static_cast<double>(Z));
                if (groups > 1) {
                    const double effective =
                        std::max(0.5, static_cast<double>(Z) - 1.5);
                    position[1] = std::log(scale * 4.0 / effective);
                    position[2] = position[1];
                }
                double energy = state_energy_ry(Z, electrons, position);
                for (int iteration = 0; iteration < 160; ++iteration) {
                    const auto gradient =
                        state_gradient(Z, electrons, position);
                    double maximum_gradient = 0.0;
                    for (int group = 0; group < groups; ++group) {
                        maximum_gradient = std::max(
                            maximum_gradient, std::abs(gradient[group])
                        );
                    }
                    const double residual = maximum_gradient
                        / std::max(1.0, std::abs(energy));
                    if (residual < 1.0e-10) {
                        break;
                    }

                    std::array<std::array<double, 3>, 3> hessian{};
                    for (int column = 0; column < groups; ++column) {
                        auto plus = position;
                        auto minus = position;
                        plus[column] += hessian_step;
                        minus[column] -= hessian_step;
                        const auto gradient_plus =
                            state_gradient(Z, electrons, plus);
                        const auto gradient_minus =
                            state_gradient(Z, electrons, minus);
                        for (int row = 0; row < groups; ++row) {
                            hessian[row][column] =
                                (gradient_plus[row] - gradient_minus[row])
                                / (2.0 * hessian_step);
                        }
                    }
                    for (int row = 0; row < groups; ++row) {
                        for (int column = row + 1; column < groups; ++column) {
                            const double average = 0.5
                                * (hessian[row][column]
                                   + hessian[column][row]);
                            hessian[row][column] = average;
                            hessian[column][row] = average;
                        }
                    }
                    std::array<double, 3> rhs{};
                    std::array<double, 3> step{};
                    for (int group = 0; group < groups; ++group) {
                        rhs[group] = -gradient[group];
                    }
                    bool solved = solve_linear(
                        hessian, rhs, groups, step
                    );
                    double directional = 0.0;
                    for (int group = 0; group < groups; ++group) {
                        directional += gradient[group] * step[group];
                    }
                    if (!solved || directional >= 0.0) {
                        double norm = 0.0;
                        for (int group = 0; group < groups; ++group) {
                            norm += gradient[group] * gradient[group];
                        }
                        norm = std::max(1.0, std::sqrt(norm));
                        for (int group = 0; group < groups; ++group) {
                            step[group] = -gradient[group] / norm;
                        }
                    }
                    double maximum_step = 0.0;
                    for (int group = 0; group < groups; ++group) {
                        maximum_step = std::max(
                            maximum_step, std::abs(step[group])
                        );
                    }
                    if (maximum_step > 1.0) {
                        for (int group = 0; group < groups; ++group) {
                            step[group] /= maximum_step;
                        }
                    }

                    bool accepted = false;
                    double damping = 1.0;
                    while (damping > 1.0e-12) {
                        auto trial = position;
                        for (int group = 0; group < groups; ++group) {
                            trial[group] = std::clamp(
                                position[group] + damping * step[group],
                                lower,
                                upper
                            );
                        }
                        const double trial_energy =
                            state_energy_ry(Z, electrons, trial);
                        if (trial_energy < energy) {
                            position = trial;
                            energy = trial_energy;
                            accepted = true;
                            break;
                        }
                        damping *= 0.5;
                    }
                    if (!accepted) {
                        break;
                    }
                }

                const auto gradient =
                    state_gradient(Z, electrons, position);
                double maximum_gradient = 0.0;
                for (int group = 0; group < groups; ++group) {
                    maximum_gradient = std::max(
                        maximum_gradient, std::abs(gradient[group])
                    );
                }
                const double residual = maximum_gradient
                    / std::max(1.0, std::abs(energy));
                if (energy < best.energy_ry) {
                    best.energy_ry = energy;
                    best.energy_eV = energy * Ry_eV;
                    best.force_residual = residual;
                    best.group_count = groups;
                    best.converged = residual < 1.0e-8;
                    for (int group = 0; group < groups; ++group) {
                        best.radii_a0[group] = std::exp(position[group]);
                    }
                }
            }
            return best;
        }

        [[nodiscard]] inline auto first_ionisation_eV(int Z) noexcept -> double {
            const State neutral = solve_state(Z, Z);
            const State ion = solve_state(Z, Z - 1);
            return ion.energy_eV - neutral.energy_eV;
        }
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
    // input_dependency:      primitive-derivation basis
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
    // input_dependency:      primitive-derivation basis
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

    /// Nuclear boundary radius — NP12 canon change (2026-07-05, James Christopher Tyndall-authorized).
    /// R(A) = R_p · (A/η)^(1/3),  η = π/√18 ≈ 0.74048 (close-packing fraction) — ZERO-FIT:
    /// close-packed nucleon volume V = A·(4/3)πR_p³/η  ⇒  R = R_p (A/η)^(1/3).
    /// Graded against 908 measured radii (IAEA / Angeli & Marinova 2013): RMS 4.96%
    /// (shared curve shape with the empirical 0.9295·A^(1/3) reference at 5.00%).
    /// Isotope-chain flattening is a remaining per-isotope mechanism debt.
    /// provenance_status:     SDT-derived (packing geometry; no fitted constant)
    /// correspondence_status: known-match (4.96% RMS, N=908)
    /// evidence:              Investigations/05_Nuclear_Physics/NP12_.../NP12_VERDICT.md
    [[nodiscard]] inline auto nuclear_boundary_radius(int A) noexcept -> double {
        constexpr double eta = std::numbers::pi / 4.242640687119285;  // π/√18
        return R_p * std::cbrt(static_cast<double>(A) / eta);
    }

    /// He-4 alpha-core contact-seat diameter, distinct from the NP12 bulk
    /// RMS-radius law. This measured-R_p construction is a correspondence,
    /// not a prediction of nuclear_boundary_radius(4).
    inline constexpr double R_He_contact_diameter = 2.0 * R_p;

    // ── SHELL SCHEDULE — closure tiers and triton shells ────────────────────
    /// Canon change (2026-07-30, James Christopher Tyndall-authorized: "incorporate this structural
    /// setup into every part of the engine that is relevant").
    /// Nomenclature / geometry correction (2026-08-09, NSEQ02–05, author-approved):
    /// the LLM-propagated planar "triton belt" / rolling-equator seating is
    /// WITHDRAWN. Capacities unchanged. Seating is geometric pure shells:
    ///   · DEUTERON SHELLS (polyhedral / link seats): 6, 12, then 12, 20, 30…
    ///   · TRITON SHELLS (stella / polar / cuboct face-normals): 8, 10, 12, 14…
    /// Species-pure order (grouped +nd+nt lines below are closure SUMS only):
    ///   2 —D6→ 8 —D12→ 20 —T8→ 28 —D12→ 40 —T10→ 50 —D20→ 70
    ///     —T12→ 82 —D30→ 112 —T14→ 126 —D42→ 168 —T16→ 184.
    /// Geometry (NSEQ05): T8 = stella/dual-tetra; post-T8 D12 = cuboct (T8 edge
    /// midpoints, 3+6+3); T14 = cuboct face normals (8△+6□) — not adjacent to
    /// that D12 (T10 intervenes). Opening triton valence radius > closing.
    /// Every closure ("magic number") is a completed seat tier on which the next
    /// tier rests. Tritons enter load-bearing masonry where the ledger
    /// (n_t = N − Z) first forces them (fourth closure / T8 → N=28).
    /// Compact schedule (sums): 2 | +6d → 8 | +12d → 20 | +8t → 28 | +12d+10t → 50 |
    ///           +20d+12t → 82 | +30d+14t → 126.
    /// No spin–orbit force is imported anywhere: the rigid n–p–n rod's seating
    /// (geometric shell, sealed at closure) carries the structure the
    /// prevailing account modelled as a coupling.
    /// Seat law: POSITIONS fixed by shell geometry · FILLING ORDER fixed by the
    /// pure-shell sequence · OCCUPANCY set by the ledger at closure time and
    /// frozen once the next tier rests on it (docked → paired → sealed).
    /// The freeze clause is MEASURED — see the isotone invariant under evidence.
    /// provenance_status:     capacities DERIVED (2026-07-30, mesh completion law
    ///                        below): all nine from two closed forms — tier
    ///                        F(n) = (n+1)(n+2), shell B(n) = V = 2(n+1),
    ///                        link remainder R(n) = E = n(n+1). READ (open):
    ///                        the descent onset n = 3 — why the ledger first
    ///                        forces tritons at the fourth tier (field-cost
    ///                        pricing, residual NP33 debt); D42 contact topology
    ///                        vs 3V−6 (NSEQ05 OPEN debt)
    /// correspondence_status: sequence-exact (2,8,20,28,50,82,126); counting
    ///                        convergent with the shell model — the origin differs
    /// evidence:              Benchmarks/nuclear_grammar_output.txt · NP33 ·
    ///                        Ca-48 all-triton shell (doubly magic, held) vs Ni-56
    ///                        shell-empty (unstable) · contraction maxima at every
    ///                        magic N · MEASURED (pre-registered single pass,
    ///                        2026-07-30): the closure kink is an ISOTONE
    ///                        INVARIANT — constant along N=28/50/82 while n_t
    ///                        varies 2–4×, beating the occupancy-proportional
    ///                        shape on every adjudicable isotone; 19/19 closure
    ///                        kinks negative. The freeze does the compacting;
    ///                        the ledger only decides who sits in the seats.
    ///                        Lone-rod-inward census 83.1% (shared sign with the
    ///                        pairing account — cannot discriminate; the
    ///                        direction is the seat law's). Full record:
    ///                        ATOMICUS/reference/CLOSURE_KINK_ISOTONE_INVARIANT.md
    ///                        · NSEQ05_Pure_Shell_Incidence

    inline constexpr int magic_numbers[7]     = {2, 8, 20, 28, 50, 82, 126};
    inline constexpr int deuteron_tiers[5]    = {6, 12, 12, 20, 30};   // rod seats per d-shell
    inline constexpr int triton_shell_pairs[4] = {4, 5, 6, 7};         // half-caps: B/2 per T-shell

    /// Rebuild the closure sequence from the alternation rule — compile-time
    /// proof the schedule reproduces every measured closure.
    [[nodiscard]] constexpr auto closure(int k) noexcept -> int {
        int n = 2;                                     // the alpha core
        if (k >= 1) n += deuteron_tiers[0];            // → 8
        if (k >= 2) n += deuteron_tiers[1];            // → 20
        if (k >= 3) n += 2 * triton_shell_pairs[0];    // → 28 (first T8 shell)
        if (k >= 4) n += deuteron_tiers[2] + 2 * triton_shell_pairs[1];  // → 50
        if (k >= 5) n += deuteron_tiers[3] + 2 * triton_shell_pairs[2];  // → 82
        if (k >= 6) n += deuteron_tiers[4] + 2 * triton_shell_pairs[3];  // → 126
        return n;
    }
    static_assert(closure(0) == 2 && closure(1) == 8 && closure(2) == 20
               && closure(3) == 28 && closure(4) == 50 && closure(5) == 82
               && closure(6) == 126,
                  "shell schedule must reproduce the measured closure sequence");

    [[nodiscard]] constexpr auto is_closure(int n) noexcept -> bool {
        for (int m : magic_numbers) if (n == m) return true;
        return false;
    }

    // ── COMPLETION LAW — the capacities derived (2026-07-30; geometry 2026-08-09) ─
    /// Mesh facts force two closed forms (counts unchanged; seating corrected):
    ///   (1) like never gears like ⇒ every tier is a bipartite DOUBLE LAYER
    ///       (p-face / n-face);
    ///   (2) the packing's 2D order is triangular ⇒ a layer holds the
    ///       (n+1)-th triangular number of rod seats;
    ///   ⇒ TIER capacity F(n) = 2·T(n+1) = (n+1)(n+2): 2, 6, 12, 20, 30, 42…
    ///       (F(0) = 2 is the alpha's own two deuterons — the core obeys the
    ///        same formula);
    ///   (3) tritons are RADIAL rods on geometric SHELLS (stella / polar /
    ///       cuboct face-normals — NSEQ02/05); vertex count
    ///       B(n) = V = 2(n+1): 8, 10, 12, 14 …;
    ///   (4) intervening deuteron seats are the LINK count on that shell
    ///       R(n) = E = n(n+1): 12, 20, 30, 42 … (face-count 12→16→20 EXCLUDED).
    ///   Identity: F(n) = V + E = B(n) + R(n).
    /// Schedule: closures 2, 8, 20 = ΣF(0..2); from n = 3 the triton shell
    /// separates and DESCENDS to seal the previous closure (measured: kink
    /// maximal at N = 28, first T8; isotone-invariant): +B(3) → 28,
    /// +R(3)+B(4) → 50, +R(4)+B(5) → 82, +R(5)+B(6) → 126.
    /// FORWARD PREDICTION: closure(7) = 126 + R(6) + B(7) = 126 + 42 + 16
    /// = 184 — the next neutron closure, from the same two forms.
    /// correspondence_status: F(n) equals the oscillator degeneracy and B(n)
    /// the intruder-orbit capacity — shared counting, cannot discriminate at
    /// sequence level; the native content is bipartite doubling + vertex/link
    /// shell geometry, neither of which the rival's account owns.
    [[nodiscard]] constexpr auto tier_capacity(int n)            noexcept -> int { return (n + 1) * (n + 2); }
    [[nodiscard]] constexpr auto triton_shell_capacity(int n)    noexcept -> int { return 2 * (n + 1); }
    [[nodiscard]] constexpr auto surface_remainder(int n)        noexcept -> int { return n * (n + 1); }

    /// NP33 synchrony-pricing closure. Tier n exposes n+1 radial contacts;
    /// the FLM07 tetrahedral lock requires q=4. Missing contacts cost one
    /// common engaged-resistance unit; completing the graph saves one unit.
    inline constexpr int triton_lock_contacts =
        lock_geometry::trefoil_lock_coordination;
    [[nodiscard]] constexpr auto triton_delta_resistance_units(
        int n
    ) noexcept -> int {
        const int contacts = n + 1;
        return contacts < triton_lock_contacts
            ? triton_lock_contacts - contacts
            : -(contacts - triton_lock_contacts + 1);
    }
    inline constexpr int triton_descent_onset =
        triton_lock_contacts - 1;
    static_assert(triton_delta_resistance_units(2) > 0
               && triton_delta_resistance_units(3) < 0
               && triton_descent_onset == 3,
                  "NP33 tetrahedral synchrony must select the n=3 onset");

    // The read arrays above are now bound to the closed forms — the canon
    // cannot compile with capacities that disagree with the derivation:
    static_assert(deuteron_tiers[0] == tier_capacity(1)
               && deuteron_tiers[1] == tier_capacity(2)
               && deuteron_tiers[2] == surface_remainder(3)
               && deuteron_tiers[3] == surface_remainder(4)
               && deuteron_tiers[4] == surface_remainder(5),
                  "deuteron tiers must equal the derived capacities");
    static_assert(2 * triton_shell_pairs[0] == triton_shell_capacity(3)
               && 2 * triton_shell_pairs[1] == triton_shell_capacity(4)
               && 2 * triton_shell_pairs[2] == triton_shell_capacity(5)
               && 2 * triton_shell_pairs[3] == triton_shell_capacity(6),
                  "triton shells must equal the derived capacities");
    static_assert(tier_capacity(0) == 2, "the alpha core is tier n=0 of the same law");
    static_assert(126 + surface_remainder(6) + triton_shell_capacity(7) == 184,
                  "forward prediction: the next closure is N = 184");

    /// Triton parity lock: stable odd-Z nuclei carry an ODD triton count — the
    /// lone rod on the inward seat (the mono-isotopic grip: Na, Al, P, Sc, V,
    /// Mn, Co). An odd-Z nucleus with an EVEN triton count is a parity misfit.
    /// Among primordial odd-Z NUBASE entries the misfit set is exactly L ∪ H
    /// (NP34b): light stable odd–odd L={²H,⁶Li,¹⁰B,¹⁴N} and long-lived
    /// radioactive odd–odd H={K-40, V-50, La-138, Lu-176, Ta-180m}. The older
    /// “precisely five” wording is EXCLUDED by whole-range census (NP34).
    /// Counting convergent with the odd-odd rule; native content is the
    /// unpaired rod with no partner to seal.
    [[nodiscard]] constexpr auto triton_parity_misfit(int Z, int A) noexcept -> bool {
        const int n_t = A - 2 * Z;                     // standard grammar
        return (Z % 2 == 1) && (n_t >= 0) && (n_t % 2 == 0);
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
//  FLM07 TREFOIL BOUNDARY:
//    the Law-IV minimum-engaged-resistance test selects the tetrahedral
//    close-packed thread (coordination 4) over the octahedral control
//    before radius comparison. Four action relays give
//    R_p = 4ℏ/(m_p c) = 0.84124 fm (0.02% vs muonic-H), and 4=W+1.
//
//  FALSIFICATION: if |R_p_measured − 4ℏ/(m_p c)| > n σ_combined,
//  the FLM07 branch is false.
// ═══════════════════════════════════════════════════════════════════════

namespace law_VI {
namespace winding {
    using namespace measured;

    // A (p,q) mode is a true knot iff
    // gcd(p,q)=1 and min(p,q)≥2; its Alexander polynomial Δ(t)≠1 is a knot
    // invariant that cannot change under continuous deformation:
    //   (1,1) electron: Δ=1            → unknot, confined by V_disp (stable)
    //   (1,2) "W=2":    Δ=1            → unknot
    //   (2,3) proton:   Δ=t⁻²−t⁻¹+1−t+t² ≠ 1 → trefoil, topologically
    //                                    distinct from an unknot
    // PPT09 validates this classification only. Its first-order energy
    // integral gives the W=2 branch exactly equal to two W=1 branches and
    // does not determine a barrier, lifetime, reconnection direction, or a
    // W={1,3}-only stability spectrum. Those dynamical claims remain open.

    /// Proton winding number (trefoil knot)
    inline constexpr int W_proton = 3;

    /// Electron winding number (simple torus)
    inline constexpr int W_electron = 1;

    /// Exact close-packed void geometry and common-kernel resistance prices.
    inline constexpr double tetrahedral_void_radius_ratio =
        lock_geometry::tetrahedral_void_radius_ratio;
    inline constexpr double octahedral_void_radius_ratio =
        lock_geometry::octahedral_void_radius_ratio;
    inline constexpr double tetrahedral_resistance_price =
        lock_geometry::tetrahedral_resistance_price;
    inline constexpr double octahedral_resistance_price =
        lock_geometry::octahedral_resistance_price;
    inline constexpr int proton_lock_coordination =
        lock_geometry::trefoil_lock_coordination;
    static_assert(proton_lock_coordination == W_proton + 1);

    /// FLM07 predicted proton boundary:
    /// R_p = q_lock ℏ/(m_p c), with q_lock selected before comparison.
    // provenance_status:     SDT-derived
    // correspondence_status: known-match            // 0.02% vs muonic-H proton radius
    // input_dependency:      mass/action seat + FLM07 close-packed geometry
    // class:                 C
    // circularity_assertion: measured R_p and W+1 target absent from selection
    // risk_flag:             conditional on Law-IV minimum-resistance path
    inline constexpr double R_p_predicted = law_III::R_p_lock;
    // = 8.4124e-16 m = 0.84124 fm

    /// R_p residual: ΔR_p = R_p_measured − R_p_predicted
    inline constexpr double delta_R_p = R_p - R_p_predicted;

    /// R_p relative error
    inline constexpr double R_p_error_pct = (R_p - R_p_predicted) / R_p * 100.0;
    // ≈ 0.02%

    /// Effective winding number inferred from measurement:
    /// W_eff = R_p m_p c / ℏ − 1
    /// FLM07 branch predicts W_eff = 3 (integer)
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
    // input_dependency:      primitive-derivation basis   // c + the integers (p,q)
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
//  PPT05 — Trefoil confinement
//  The dimensionally closed result is the linear potential E(L)=σL for a
//  fixed-area throughput tube. Its coefficient is computed below from the
//  proton mass/action seat and the registered trefoil geometry.
// ───────────────────────────────────────────────────────────────────────
namespace confinement {
    using namespace measured;

    /// SDT string tension σ = u_tube A_tube = m_p c²/(2πR_trefoil) [GeV/fm]
    /// with R_trefoil = (ℏ/m_pc)/√3 from the registered PPT05 instrument.
    // provenance_status:     SDT-derived
    // correspondence_status: computed          // ≈1.230 GeV/fm; comparison is not certification
    // input_dependency:      mass/action seat + trefoil geometry
    // class:                 C
    // circularity_assertion: passes delete-test
    // risk_flag:             fixed-area confinement mechanism remains to be independently tested
    inline constexpr double trefoil_major_radius =
        (hbar / (m_p * c)) / std::numbers::sqrt3;
    inline constexpr double string_tension_GeV_per_fm =
        (m_p * c * c / (2.0 * std::numbers::pi * trefoil_major_radius))
        * 1.0e-15 / (1.0e9 * eV_to_J);

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
    inline const double v_phase_proton_surface = c / bridge::k_proton_surface;
    // ≈ 5.488e8 m/s = 1.831 c

    /// Angular velocity demanded of a contact spation:
    /// ω_demand = 6π / T_circ = 3c/ƛ_C = 3 m_p c² / ℏ   (ƛ = reduced; λ/2π — fixed 2026-07-07)
    // provenance_status:     SDT-derived
    // correspondence_status: internal-only
    // input_dependency:      primitive-derivation basis   // m_p, c, ℏ + winding q=3
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
//  PPT07 / PPT17 — Proton/electron tube-volume construction (RESOLVED)
//  The W=1 point electron sweeps its finite-width 720-degree closure tube at
//  the Bohr seat. 6π⁵ copies of that volume are conserved into the W=3 torus
//  seated at R_p. This resolves the geometric volume assignment as a
//  shared-input construction; it is not an independent prediction of the
//  measured mass ratio. FLM15 separately excludes linear phase stiffness as
//  an alternative generator (J_3/J_1 = 2.647).
// ───────────────────────────────────────────────────────────────────────
namespace mass_ratio {
    using namespace measured;

    /// Geometric packing count: 6π⁵ = 1836.118 (−0.0019% vs measured 1836.15267)
    // provenance_status:     construction-resolved
    // correspondence_status: known-match
    // input_dependency:      shared-input          // 6π⁵ is the declared tube packing count
    // class:                 COMPUTED              // resolved construction, not independent prediction
    // circularity_assertion: physical map consumes its own packing count
    // risk_flag:             electron body width affects absolute tube radii, not the volume ratio
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

    /// Point-electron speed at the hydrogen Bohr seat.
    /// T3/T11: v(a₀)=c√(α²a₀/a₀)=αc.
    inline constexpr double point_electron_bohr_velocity = alpha * c;

    /// Hydrogen occlusion length carried by the point-particle orbit.
    inline constexpr double point_electron_koppa = alpha * alpha * a_0;

    /// Point-electron speed along the same occlusion profile at radius r.
    [[nodiscard]] inline auto point_electron_velocity(double r) noexcept -> double {
        return c * std::sqrt(point_electron_koppa / r);
    }

    /// Full 720-degree W=1 orientation closure at the Bohr radius.
    inline constexpr double electron_closure_length =
        4.0 * std::numbers::pi * a_0;

    /// Swept volume of a point electron with physical tube radius b_e.
    [[nodiscard]] constexpr auto electron_orbit_tube_volume(
        double b_e
    ) noexcept -> double {
        return std::numbers::pi * b_e * b_e * electron_closure_length;
    }

    /// Ring-torus envelope volume seated at major radius R with tube radius b.
    [[nodiscard]] constexpr auto torus_envelope_volume(
        double R, double b
    ) noexcept -> double {
        return 2.0 * std::numbers::pi * std::numbers::pi * R * b * b;
    }

    /// Tube radius after conserving `packing_count` electron closure volumes
    /// into a ring torus seated at R_p.
    [[nodiscard]] inline auto proton_tube_radius_from_packing(
        double b_e, double packing_count = six_pi_5
    ) noexcept -> double {
        return b_e * std::sqrt(
            packing_count * electron_closure_length
                / (2.0 * std::numbers::pi * R_p)
        );
    }

    /// The construction's point-electron velocity at the proton torus seat.
    inline const double point_electron_velocity_at_proton =
        point_electron_velocity(R_p);
}

// ───────────────────────────────────────────────────────────────────────
//  APS04 — Trefoil wake multipole & NATIVE angular DOF  (PASS, CLASS C)
//  The proton trefoil's wake carries a native three-fold (C₃) structure
//  that supplies the angular degree of freedom (s-vs-p) WITHOUT importing
//  spherical-harmonic ℓ quantum numbers. The native content is the
//  selection rule m₃ = 3k (C₃ periodicity) and the r⁻¹/r⁻³/r⁻⁴ power laws.
//
//  CAVEATS — do not over-read:
//   • "multipole / quadrupole / Legendre Pℓ" is borrowed MATHEMATICAL
//     language; only the C₃ periodicity and the power laws are native.
//   • APS14 now distinguishes the fixed polar dyad from the six-ring in
//     multi-electron pair resistance. The isolated center's polar-to-ring
//     pressure-work amplitude is still owed, so B04 remains OBSERVED.
//   • APS04's +0.761 MHz is a nuclear-geometry addend, not the bulk interval.
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

    /// Lamb intervals (hydrogenic 2S–2P): OBSERVED form-switch frequencies.
    /// Lamb–Retherford is treated as a driven pair-form → plane-form quench
    /// on the proton center, not as an SDT-derived interval.
    /// Construction names He⁺ as a different center (α, two protons); it does not
    /// compute 14041.13 from 1057.845. PPT08 koppa map = RE-EXPRESSION of the H sticker.
    /// APS04 +0.761 MHz is a nuclear-geometry addend, not the bulk interval.
    // provenance_status:     OBSERVED-INPUT (RF resonances; NOT SDT-derived)
    // correspondence_status: measured
    // input_dependency:      measured-observable
    // class:                 OBSERVED (extraction debt withdrawn)
    inline constexpr double lamb_shift_measured_MHz = 1057.845;  // H n=2; Lamb–Retherford
    inline constexpr double lamb_shift_He_plus_measured_MHz = 14041.13;  // He⁺ n=2; van Wijngaarden 2003
}
} // namespace law_VI

// ═══════════════════════════════════════════════════════════════════════
//  OPEN PROBLEMS — current status
// ═══════════════════════════════════════════════════════════════════════
//
//  1. Discrete validation of the FLM07 proton boundary
//     ANALYTIC ROUTE DERIVED: the minimum-engaged-resistance close-packed path
//     selects tetrahedral coordination q=4 before radius comparison, and
//     qℏ/(m_p c) agrees with the measured boundary to 0.02%. A discrete
//     dynamical-lattice replication remains desirable; it is not used to
//     inflate the earned analytic result.
//
//  2. Quantisation of stable vortex topologies
//     OPEN. PPT09 classifies W=2 as an unknot, but its first-order energy is
//     exactly equal to two separated W=1 branches. The barrier, lifetime,
//     reconnection direction and W={1,3}-only stability claim are unresolved.
//
//  3. Fine structure constant from topology
//     α = g(W=1) = r_e / ƛ_Ce. Can this be derived from the W=1 torus
//     mode partition (v_P / v_T)?  Would eliminate α as input. (PPT02 found
//     α = koppa of the H ground state — electromagnetic, still needs e.)
//
//  4. Proton-electron mass ratio
//     RESOLVED AS A SHARED-INPUT VOLUME CONSTRUCTION (PPT17): the point
//     electron's 720-degree Bohr-seat tube is packed 6π⁵ times into the W=3
//     torus seated at R_p. This certifies the geometric map, not an independent
//     prediction of 1836. FLM15's J_3/J_1 = 2.647 excludes simple phase
//     stiffness as a separate generator and does not alter this construction.
//
//  5. Atomic dodecardinal extension and absolute shelf splitting
//     APS14 COMPUTES He–Ne first ionisation (median 1.48%, max 5.25%), helium
//     total binding (1.22%), and 45 unused higher ionisations (median 1.62%,
//     max 8.63%) from the fixed polar dyad, six-ring and FLM15 resistance
//     kernel. Extension beyond Ne remains open. The same geometry distinguishes
//     polar and ring lanes, but the isolated-center pressure-work amplitude
//     required for an absolute Lamb interval remains open; B04 stays OBSERVED.
//
// ═══════════════════════════════════════════════════════════════════════

// ═══════════════════════════════════════════════════════════════════════
//  THE DEPTH–CLOSURE THEOREM  (capstone — Papers/Depth_Closure_Theorem)
//
//  Unifies GOM01 (depth engine) · GOM02 (k-hierarchy) · GOM04 (koppa closure) ·
//  FLM06/GOM05 (variable spation closure). Numbers
//  reproduce from Papers/Depth_Closure_Theorem/keystone.js.
//
//  Local closure, local relay speed, local clock rate and the gravitational
//  spectral shift are ONE quantity — the convergence depth z = ϟ/r — and one
//  centripetal law v = c√z governs bound motion at every scale:
//
//    z ≡ 1/k² = (v/c)² = ϟ/r,   ϟ ≡ v²R/c² = R/k²   (koppa: a velocity-defined length)
//
//    (1) ℓ_P(r)     = ℓ_P,∞ · (1 − z)        local spation closure
//    (2) c_far(r)   = c_∞   · (1 − z)²        far-frame relay speed  [REPAIRED — see below]
//    (3) dτ/dt      = (1 − z)                 local clock rate (Law V budget) [REPAIRED]
//    (4) z_spec     = z(r_emit) − z(r_obs)    "gravitational redshift" = depth differential
//    (5) v(r)       = c √(ϟ/r) = c √z         bound-motion law (g = v²/r = c²ϟ/r²)
//
//  GOM22 fixes the observed first-order coefficient at two. The active native
//  candidate is c_far=c(1−z)²: one closure factor for path length and one for
//  clock rate. The second-order fork remains undecided: (a) c(1−z)² vs
//  (b) c(1−2z) [Schwarzschild coordinate speed — shared form, CANNOT
//  DISCRIMINATE at first order]. They differ on where the relay
//  speed vanishes: (a) r = ϟ, (b) r = 2ϟ = r_s exactly — i.e. whether SDT has a
//  horizon, and whether GOM06's echo prediction survives. That (a) preserves an
//  SDT prediction is a consequence, NOT evidence for it. Discriminator: a
//  1.4 M☉ neutron-star surface splits them by 8.6% (NICER-class hot-spot
//  modelling); the solar limb splits them by 1.06e-6 — below reach.
//  The absolute closure ℓ_P,∞ and particle-body radii remain debts.
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

    /// GOM01/GOM22 — Shapiro delay is the integrated relay-speed deficit.
    /// The factor 2 below is DERIVED, not inserted: with the repaired profile
    /// c_far = c(1−z)², the integrand 1/c_far − 1/c = (2z + O(z²))/c, so
    ///     Δt = (2/c)∫ z dl = (2ϟ/c)∫ dl/r = (2ϟ/c) ln(4 r₁ r₂ / b²)
    /// for a ray of impact parameter b from r₁ to r₂ — 247.24 μs round-trip at
    /// grazing Earth–Mars, against Viking ~250 μs and Cassini's coefficient at
    /// 2.3e-5. (The previous header asserted "the local light speed stays c",
    /// which contradicted relation (2).)
    [[nodiscard]] inline auto shapiro_delay(
        double koppa, double r1, double r2, double b
    ) noexcept -> double {
        return (2.0 * koppa / c) * std::log(4.0 * r1 * r2 / (b * b));
    }

    /// (3) Local clock rate: dτ/dt = (1 − z)   (Law V movement budget)
    /// Domain: 0 <= z <= 1. Callers must reject depths outside this interval.
    /// GOM22 repair: was √(1 − z), which gave half the measured solar
    /// gravitational redshift (318 vs 633 m/s) and contradicted relation (4).
    /// (1 − z) reproduces it: 636.3 m/s against 633 measured.
    [[nodiscard]] constexpr auto clock_rate(double z) noexcept -> double {
        return 1.0 - z;
    }

    /// (2) Far-frame relay speed: c_far = c_∞ (1 − z)²
    /// Domain: 0 <= z <= 1 and c_inf > 0.
    /// The closure enters twice — once shortening the hop, once dilating the
    /// tick (GOM22). Inverse: z = 1 − √(c_far/c_∞).
    [[nodiscard]] constexpr auto c_far(double c_inf, double z) noexcept -> double {
        return c_inf * (1.0 - z) * (1.0 - z);
    }
    [[nodiscard]] inline auto depth_from_c_far(double c_far_val, double c_inf) noexcept -> double {
        return 1.0 - std::sqrt(c_far_val / c_inf);
    }

    /// (1) Local spation closure: ℓ_P(r) = ℓ_P,∞ (1 − z)
    [[nodiscard]] constexpr auto closure_local(double lP_inf, double z) noexcept -> double {
        return lP_inf * (1.0 - z);
    }

    /// (4) Gravitational redshift as a depth differential: z_spec = z_emit − z_obs
    [[nodiscard]] constexpr auto z_spectral(double z_emit, double z_obs) noexcept -> double {
        return z_emit - z_obs;
    }

    // ─── Corollary quantities ───

    /// C1: solar gravitational redshift = depth at the surface = ϟ_Sun/R_Sun
    /// = 2.123e-6, equal to the observed GM/(c²R) to 0.03% (a consequence)
    inline const double z_spectral_Sun = bridge::koppa_Sun / R_Sun;

    /// C5: spation closure floor (koppa form): ℓ_P = √(ϟ_baryon · ƛ_p)
    /// with ϟ_baryon = bridge::koppa_per_baryon and ƛ_p = ℏ/(m_p c).
    /// Scope (FLM06): this RE-EXPRESSES ℓ_P; it does not derive it. koppa_per_baryon
    /// is itself defined as ℓ_P²·c·m_p/ℏ (bridge), so √(ϟ·ƛ) = √(ℓ_P²) = ℓ_P is an
    /// IDENTITY — a consistency check, not an elimination. FLM06's real result is the
    /// Seed Theorem (one dimensional anchor unavoidable) + re-homing the seed from
    /// {ℏ,G} to one SDT-native length. ℓ_P stays Axiom R1; see measured::l_P provenance.
    [[nodiscard]] inline auto closure_floor(double koppa, double wake) noexcept -> double {
        return std::sqrt(koppa * wake);
    }
    inline const double lP_from_closure_floor =
        closure_floor(bridge::koppa_per_baryon, hbar / (m_p * c));
    // ≈ 1.616e-35 m = ℓ_P  (by construction — identity)

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
