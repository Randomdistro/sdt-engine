# Q05: Cosmic Ray as Relativistic Torus — Investigation Prompt

> **Classification**: Theoretical derivation
> **Prerequisites**: SDT movement budget, vortex topology (Law VI),
> persistence constraint
> **Output format**: State description at 6 energy regimes with
> interaction consequences

---

## 1. Background

A cosmic ray proton is a W=3 torus traversing the spation lattice at
near-luminal velocity. As its translational velocity v approaches c,
the movement budget constraint (v² + v_circ² = c²) forces its
circulation velocity v_circ toward zero.

This has profound consequences that conventional physics does not
address: the proton is LOSING its internal structure as it accelerates.
At v = 0.9999c, the circulation is v_circ = 0.0141c — the torus is
barely spinning. At GZK energies (~10²⁰ eV), v_circ ≈ 10⁻¹²c — the
torus has effectively stopped circulating.

This raises the question: **what IS a W=3 torus that isn't circulating?**
Is it still a proton? Does it interact with matter differently? Does the
cessation of circulation explain the GZK cutoff?

The existing SDT experiment E90 (Cosmic Ray GZK from Lattice Limit)
addresses the cutoff but provides only a stub. This investigation must
provide the complete geometric description.

---

## 2. The Core Question

**What is the complete SDT description of a proton at each decade of
cosmic ray energy, from 10⁹ eV to 10²⁰ eV, and how does the
progressive loss of circulation alter its interaction with nuclear
scaffolds?**

Sub-questions:

1. At what energy does the proton effectively cease to be a "proton"
   in SDT terms (circulation drops below some stability threshold)?
2. Does the Lorentz contraction of the torus geometry change the
   wake multipole structure (ℓ=1,2,3+)?
3. Is the GZK cutoff the energy at which the lattice CANNOT propagate
   a non-circulating displacement? (The lattice requires circulation
   to maintain a stable exclusion — a non-circulating displacement
   may be unstable against dissolution.)
4. Does the pancake geometry of a highly boosted torus explain why
   the p-p cross-section INCREASES with energy (σ_pp: 40 mb → 100 mb)?
   The transverse size is unchanged but the interaction geometry changes.
5. How does the solar wind's convergence field (Earth's local lattice
   environment) modulate the flux of these objects?

---

## 3. Methodology

### Phase A: Movement budget analysis at each energy decade

Construct a master table:

| Energy (eV) | γ | v/c | v_circ/c | k = c/v | v_circ/v_circ,rest | State description |
|-------------|---|-----|----------|---------|-------------------|-------------------|
| 10⁹ (1 GeV) | 1.066 | 0.349 | 0.937 | 2.87 | 93.7% | Slowly moving, fully circulating |
| 10¹⁰ | 10.66 | 0.9956 | 0.094 | 1.004 | 9.4% | Fast, weakly circulating |
| ... | ... | ... | ... | ... | ... | ... |
| 10²⁰ | 1.066×10¹¹ | 1−4.4×10⁻²³ | ~10⁻¹¹·⁵ | ~1 | ~0% | Frozen torus |

For each row, describe:
- The torus shape (how Lorentz-contracted along the motion axis?)
- The wake structure (how do ℓ=1,2,3+ wakes transform under boost?)
- The expected interaction cross-section with a stationary nucleus
- Whether the torus is still self-sustaining (circulation maintains
  the exclusion that defines it as matter)

### Phase B: Wake transformation under boost

The proton at rest has a well-defined wake hierarchy:
- ℓ=1: Coulomb field, 1/r², long range
- ℓ=2: magnetic dipole, 1/r³, medium range
- ℓ≥3: nuclear structure, 1/r^(ℓ+1), short range

Under Lorentz boost along the z-axis:
1. The Coulomb field transforms: E_z unchanged, E_x → γE_x, E_y → γE_y
   In SDT terms: the ℓ=1 wake concentrates into a DISK perpendicular
   to the motion. The wake becomes anisotropic — strong transversely,
   weak longitudinally.

2. The magnetic field transforms: B_z unchanged, B_x → γB_x
   The ℓ=2 wake similarly concentrates transversely.

3. The ℓ≥3 (structure) wakes contract longitudinally: their spatial
   extent along z shrinks by 1/γ. At γ = 10¹¹, the structure wake
   extends only ~10⁻²⁶ m along z — far below the spation scale ℓ_P.

   **Critical question**: Can a wake shorter than ℓ_P exist? If the
   lattice cannot support sub-ℓ_P structure, the ℓ≥3 wakes are
   effectively DESTROYED at ultra-high energies. This would mean the
   proton no longer has nuclear structure when moving at GZK energies.

### Phase C: Interaction with nuclear scaffolds

At each energy decade, describe the spallation interaction:

1. **Low energy (1 GeV)**: Proton approaches with k ≈ 2.87, still
   fully circulating. Full wake structure intact. Interacts as a
   normal proton — compound nucleus formation possible. Spallation
   produces ~2–5 neutrons. The proton may be absorbed.

2. **Medium energy (10–100 GeV)**: Proton is a pancake with weak
   circulation. Its ℓ≥3 structure wakes are compressed but still
   above ℓ_P scale. Interaction transitions from compound nucleus
   to intranuclear cascade — the proton punches through, scattering
   individual nucleons rather than merging with the scaffold.

3. **High energy (TeV)**: Proton is an ultra-thin disk. ℓ≥3 wakes
   are at or near ℓ_P scale. Interaction becomes "transparent" to
   some scaffold components — only the ℓ=1 (Coulomb) and ℓ=2
   (magnetic) wakes interact, as they extend transversely.

4. **Ultra-high energy (10¹⁸+ eV)**: Proton's circulation is
   negligible. Its torus is barely maintaining itself. ℓ≥3 wakes
   are sub-ℓ_P along z. The lattice may not be able to relay the
   displacement at this configuration. This is the GZK limit —
   NOT from CMB photon pileup (the conventional explanation), but
   from lattice inability to propagate a non-circulating displacement.

### Phase D: GZK cutoff prediction

Derive the maximum energy from SDT:

1. The torus stability condition requires v_circ > v_circ,min.
   What sets v_circ,min? Possible candidates:
   - The minimum speed at which the spation lattice can maintain a
     stable exclusion: v_circ,min = ℓ_P/t_P × (some geometric factor)?
   - The minimum circulation rate to maintain the W=3 knot topology?
   - The energy at which ℓ≥3 wake extent equals ℓ_P?

2. Set v_circ = v_circ,min. Then v² = c² − v_circ,min².
   The maximum γ is: γ_max = 1/√(1 − v²/c²) = c/v_circ,min.

3. Maximum energy: E_max = γ_max × m_p c².

4. Compare E_max to the observed GZK cutoff: ~5 × 10¹⁹ eV.

5. If they match, this confirms the lattice limit interpretation.
   If they don't, identify what is missing.

### Phase E: Solar modulation in SDT

Cosmic ray flux is modulated by the solar cycle. In SDT:

1. The Sun's convergence gradient extends throughout the heliosphere
2. The solar wind is a mass flow that creates its own displacement
   field, adding to the convergence gradient
3. Cosmic ray protons must traverse this gradient to reach Earth
4. At solar maximum, the solar wind dynamic pressure is higher →
   stronger convergence gradient → more geometric deflection of
   incoming cosmic rays

Compute:
- The convergence gradient modulation at Earth's orbit (1 AU) during
  solar minimum vs solar maximum
- The expected cosmic ray flux modulation (should match the observed
  ~20% variation for GeV protons)
- The energy-dependent modulation (high-energy cosmic rays are less
  modulated — why? Because their k-number is lower, meaning they
  couple less to the macroscopic convergence gradient)

---

## 4. Required Outputs

1. **Master state table**: 12 rows (one per energy decade from 10⁹
   to 10²⁰ eV) showing: γ, v/c, v_circ/c, k, torus shape, wake
   status (ℓ=1,2,3+), expected interaction type, whether the torus
   is self-sustaining

2. **Wake transformation rules**: How each multipole transforms
   under Lorentz boost, in SDT lattice terms

3. **GZK prediction**: A numeric prediction for E_max from SDT
   lattice stability, compared to the observed cutoff

4. **Interaction regime diagram**: A text diagram showing the
   transition from compound-nucleus (low E) → cascade (medium E) →
   transparent (high E) → unstable (GZK)

5. **Solar modulation prediction**: Expected flux modulation at
   1 AU vs energy, compared to neutron monitor data

---

## 5. Success Criteria

- [ ] The movement budget partition is computed at every energy decade
- [ ] The wake transformation under boost is derived from SDT geometry
- [ ] The GZK cutoff is predicted (or bounded) from lattice properties
- [ ] The transition from compound-nucleus to cascade is explained
      geometrically (not just described phenomenologically)
- [ ] Solar modulation magnitude and energy dependence are predicted
- [ ] All descriptions use only SDT-permitted concepts
