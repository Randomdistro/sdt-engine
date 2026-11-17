# SDT Om–Bohr and half-pitch spation geometry: integration contract

**Status:** RESEARCH CANON CANDIDATE; NOT promoted to validated mechanism.  
**Base:** `90560eec440180e3994f6d16de73b52c42f6c349`  
**Rule:** Every mathematical equivalence includes its arrival path, purpose and provenance.

## Engine placement

- `Engine/include/sdt/spation_geometry.hpp` owns geometric conversions of *diameter/pitch* versus *physical spherical radius, projected area, surface area and volume*. Accepts a supplied diameter; never infers physical spation size from the conventional Planck formula.
- `Engine/include/sdt/om_atomic.hpp` owns source-length ѻ, radius-specific speed ratio Ѻ, z geometry, closed-circulation spectral ladder, and propagation-versus-orbital separation. Uses no G, GM, Coulomb or measured Bohr radius as inputs.
- `Engine/include/sdt/laws.hpp` remains unchanged, pending full engine benchmark and independent physical operator verification. Existing `measured::l_P`, `l_P3`, Law I and `bridge::koppa_per_baryon` MUST NOT be silently reinterpreted as sphere-radius quantities.

## Radial closure and Bohr equivalence ledger

| Frame | Native relation | Algebraic counterpart | Arrival / preference | Status |
|---|---|---|---|---|
| Spation radius | `r_s=d/2` | geometric definition | contact spherical cell of diameter d; do not confuse with shell spacing | exact conditional geometry |
| Area | `πr_s²=πd²/4` | disc cross section | project spherical occlusion rather than substitute `d²` as area | exact geometry, pressure kernel OPEN |
| Volume | `4πr_s³/3=πd³/6` | enclosed-sphere volume | use actual exclusion volume, not pitch cell volume | exact geometry, packing OPEN |
| Node pitch volume | `d³` | cubic accounting cell | shell-count/throughput bookkeeping; NOT a spherical cell volume | exact geometrical convention |
| Om source | `ѻ=v²R/c²` | `R/Ѻ_R²` | kinematic arrival independent of G input | exact identity |
| Depth | `z=ѻ/r=(v/c)²=1/Ѻ_r²` | weak-field potential scale `GM/(rc²)` | source kinematics and bound radial law; do not import GM into derivation | conditional equivalence |
| Spation deficit | `ΔL/L∞=z` | `L=L∞(1−z)` | variable-closure model assumption; not automatic observed photon redshift | constitutive hypothesis |
| Propagation | `c_far=c∞(1−z)²` | `c∞(1−2z+z²)` | independent hop and tick factors GOM22; conventional first-order agreement, second-order fork | conditional model |
| Circulation | `2πrv=nh/μ` | `μrv=nℏ` | integer topological circulation postulate rather than assuming Bohr angular momentum; mechanism quantum OPEN | exact algebraic equivalence |
| Atomic radius | `r_n=n²(ℏ/μ)²/(c²ѻ)` | `n²a₀` if `β=α` | substitution of independent radial and circulation laws; source length must be independently established | conditional equivalence |
| Atomic depth | `z_n=β²/n²`, `β=μcѻ/ℏ` | Bohr speed `v_n=βc/n` | source and circulation chain, NOT `α` as primitive unless explicitly observed | identity conditional on laws |
| Energy | `E_n=−μc²z_n/2` | Kepler/Coulomb virial | conservative inverse-square radial work, energy-zero infinity | conditional equivalence |
| Spectrum | `1/λ=(μcβ²/(2h))(1/n_f²−1/n_i²)` | Rydberg equation if β=α | transition depth/energy and hν; action quantum independent derivation remains OPEN | exact mathematical correspondence |
| Lattice wake | `l_P²=ѻ_b λ_wake` | Koppa-wake closure inversion | no independent Planck-length prediction when input ѻ_b already contains stored l_P | construction / independence gate OPEN |

## Propagation to existing engine subsystems

1. **Foundations / FLM06:** audit `l_P` as *reference diameter hypothesis*, `l_P³` as pitch-cell ledger volume, `l_P²` as pitch face versus projected physical cross-section. Do not relabel CODATA-derived reference as independently measured spation diameter.
2. **Law I, CMB shell count:** `N=R_CMB/d` counts pitch steps; unchanged under radius/diameter relabelling. Replacing N by R_CMB/r_s would double the shell count without justification.
3. **Law IV, effective density:** where denominator `d³` denotes lattice-node volume, physical sphere substitution multiplies an otherwise fixed-density estimate by `6/π`. If both count and unit-cell volume transform, a distinct occupancy/filling model is required. NO silent 6/π correction.
4. **Law III and occlusion.hpp:** a literal cross-section uses `πr_s²=(π/4)d²`; the existing Law-III `π/4` may already encode projection. Risk of double counting coefficient π/4. Require kernel-level rederivation.
5. **Bridge baryon Koppa:** `ѻ_b=d²/λ_wake` reflects squared *pitch*; replacing d with r_s returns ѻ_b/4 and ruins the baseline. Re-derive source shadow operator and wake normalization before proposing any coefficient change.
6. **Electromagnetism / EMC04 / FLM13:** `om_atomic.hpp` provides a forward path that does NOT import measured a0 as input but still requires independently fixed microscopic ѻ, quantised circulation and h/μ.
7. **APS13 spectral z:** depth z_n and a *measured* photon Δλ/λ are different functions. Atomic emission is generated from Δz and energy conservation; (1+z) gravitational transport is not the hydrogen spectral ladder.
8. **GOM05/GOM22 optics:** do not replace bound v=c√z by c_far√z without rederiving radial acceleration. The c_far formula belongs to propagation.
9. **Isotope/reduced-mass tests:** if ѻ_H is fixed against changing μ, Rydberg coefficient scales μ³; observed baseline expects μ. Derive two-body wake renormalisation or falsify fixed-source ѻ.
10. **Cosmology and galactic / nuclear / materials:** every occurrence of `l_P`, `l_P²`, `l_P³`, `l_P/2`, sphere/cube packing or pitch-based density needs explicit dimensional role. Existing numerical outputs stay comparison baselines until new operators are derived.

## Required promotion gates

- Source ѻ independent of the spectroscopic target.
- Origin of vortex circulation quantum independently established or treated as a measured seed; no circular α/a0 input.
- Propagation of change through exact compiler and benchmark outputs (currently not executed via this connector).
- Full audit of all Law-I through Law-VI consumers and demonstrable conservation of pressure normalization.
- No extraction of G, GM, M or kilograms from ѻ/Ѻ.
- Explicit algebraic-equivalence provenance in every public-facing frame.
