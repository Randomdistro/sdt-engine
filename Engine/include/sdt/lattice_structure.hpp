#ifndef SDT_LATTICE_STRUCTURE_HPP
#define SDT_LATTICE_STRUCTURE_HPP

// ═══════════════════════════════════════════════════════════════════════
//  sdt/lattice_structure.hpp
//  ──────────────────────────────────────────────────────────────────────
//  LATTICE STRUCTURE — the spation substrate geometry  (CONDENSA, 2026-06)
//  J. C. Harvey, Melbourne.
//
//  Class [GEOMETRY]: every constant below is EXACT, parameter-free
//  mathematics with NO physics input — provable and falsification-proof.
//  They record the tetrahedral-frustration FACTS that force the substrate
//  onto a corner-sharing tetrahedral random network (the CONDENSA result).
//
//  This header is DELIBERATELY standalone — it depends on no other SDT
//  constant (it includes only <cmath> and <numbers>). That independence is
//  the point: the substrate geometry needs no measured input. It lives in
//  the sdt::laws namespace for discoverability but is NOT part of laws.hpp.
//
//  NOT encoded here (it is [IDENTIFICATION], interpretive): the claim that
//  the physical vacuum *is* this network. The numbers stand on their own.
//
//  Ten independent derivations converge on these values — see
//  Investigations/01_Foundations_and_Lattice_Mechanics/
//      CQ53_Lattice_Structure_Geometry/cq53_lattice_structure.cpp  (27/0 PASS)
// ═══════════════════════════════════════════════════════════════════════

#include <cmath>
#include <numbers>

namespace sdt::laws::lattice_structure {

    inline constexpr double pi = std::numbers::pi;

    // ── 1. Frustration source: the regular-tetrahedron dihedral δ = arccos(1/3)
    inline const double dihedral_rad = std::acos(1.0 / 3.0);          // 1.230959417 rad
    inline const double dihedral_deg = dihedral_rad * 180.0 / pi;     // 70.528779°
    /// Supplement = the tetrahedral bond ("methane") angle arccos(−1/3) = 109.47°,
    /// forced by Σ(vertex vectors) = 0 (closure) — see Gram method (M4).
    inline const double bond_angle_rad = std::acos(-1.0 / 3.0);       // 1.910633236 rad ≈ 109.471°

    // ── 2. Five-around-an-edge deficit ⇒ tetrahedra cannot tile E³ (Conway–Torquato)
    inline const double five_edge_deficit_rad = 2.0 * pi - 5.0 * dihedral_rad;       // 0.128388 rad
    inline const double five_edge_deficit_deg = five_edge_deficit_rad * 180.0 / pi;  // 7.356103°
    /// Curvature reading (M7): in S³ five tetrahedra DO close — the {3,3,5}
    /// 600-cell has dihedral 2π/5 = 72°; the deficit = 5·(72° − δ) is exactly
    /// the positive curvature flat space cannot supply.

    // ── 3. Boerdijk–Coxeter tetrahelix: face-sharing → screw that never closes
    inline const double bc_twist_rad = std::acos(-2.0 / 3.0);         // 2.300523983 rad
    inline const double bc_twist_deg = bc_twist_rad * 180.0 / pi;     // 131.810315° (irrational·2π ⇒ aperiodic)
    inline constexpr double bc_radius_over_a = 0.519615242270663;     // R = 3√3/10 · a
    inline constexpr double bc_rise_over_a   = 0.316227766016838;     // h = a/√10

    // ── 4. Channel screw partition (axial : circumferential = 1 : 3) — a MODE
    //       ratio, not a coupling: axial transport implies circulation (current⇒B).
    inline constexpr double screw_axial_frac    = 0.316227766016838;  // 1/√10
    inline constexpr double screw_circum_frac   = 0.948683298050514;  // 3/√10
    inline constexpr double screw_torsion_ratio = 3.0;                // circum/axial
    inline constexpr double screw_energy_ratio  = 9.0;                // (quadratic) torsion/axial

    // ── 5. Same frustration in the 12-around-1 icosahedral kissing shell:
    //       centres at circumradius 2r, icosa edge 8r/√(10+2√5) > 2r ⇒ a gap.
    inline const double icosa_shell_gap_over_r = 8.0 / std::sqrt(10.0 + 2.0 * std::sqrt(5.0)) - 2.0; // 0.1029244
    inline constexpr int kissing_number_3d     = 12;                  // contacts in the shell

    // ── 6. Corner-sharing escape: coordination and the open void it leaves
    inline constexpr int coordination = 4;                            // = law_VI W+1
    inline const double packing_fraction_diamond = pi * std::sqrt(3.0) / 16.0;     // 0.340087 (diamond limit)
    inline const double void_fraction_diamond    = 1.0 - packing_fraction_diamond; // 0.659913 (~66%)

} // namespace sdt::laws::lattice_structure

#endif // SDT_LATTICE_STRUCTURE_HPP
