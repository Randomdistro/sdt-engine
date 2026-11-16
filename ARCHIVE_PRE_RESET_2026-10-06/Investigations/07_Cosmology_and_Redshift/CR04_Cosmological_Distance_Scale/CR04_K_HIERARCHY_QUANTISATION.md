# CR04 Phase 4: k-Hierarchy Quantisation

**Author:** SDT Canonical Engine — James Tyndall, Melbourne  
**Date:** June 2026  
**Status:** INVESTIGATION  
**Class:** PENDING (unresolved pattern)

## Objective

Extend the k-hierarchy framework (GOM02) to cosmological scales. Define and compute the "cosmological k-value" k_Hubble from the Hubble strain rate. Search for quantisation patterns: Is k_Hubble an integer, rational, or formulaic combination of known k-values?

## Thesis

**The k-hierarchy is complete only if it extends to cosmological scales.**

GOM02 established k = c/v as the universal ordering parameter across ~16 orders of magnitude (proton to Moon). But where does the cosmological scale fit?

The Hubble "parameter" H₀ encodes the strain rate of the pressure gradient:
```
H₀ = d(log a) / dt  [in standard cosmology]
H₀ = d(pressure)/dr / (ρ_eff × c²)  [in SDT interpretation]
```

This defines a cosmological velocity:
```
v_Hubble ≈ H₀ × R_CMB  [expansion velocity at horizon]
```

from which we compute:
```
k_Hubble = c / v_Hubble
```

**Question:** Does k_Hubble fit into the k-hierarchy in a quantised way?

## Theory

### Definition of Cosmological k

In the k-hierarchy, every body (proton, Earth, Moon, star, galaxy) has a k-value determined by its surface orbital velocity:

```
k = c / v_surface
```

For the cosmological scale, the "surface" is the Hubble radius:
```
v_Hubble = H₀ × R_Hubble ≈ H₀ × c/H₀ = c  (naively)
```

Wait, that gives k_Hubble = 1, which is the c-boundary itself!

**Correct interpretation:** The Hubble radius is NOT a physical radius. Instead, we use:
```
v_Hubble = H₀ × R_CMB  (strain rate × causal distance)
k_Hubble = c / v_Hubble = c / (H₀ × R_CMB)
```

This is the "effective surface velocity" for the cosmological strain field.

### Known k-Values (from GOM02)

| Body | k | c/k [m/s] | Regime | Class |
|---|---|---|---|---|
| Proton (surface) | 0.5464 | 5.49 × 10⁸ | Superluminal (k < 1) | A |
| Hydrogen (ground state) | 137.036 | 2.19 × 10⁶ | Subluminal | A |
| Electron (estimated) | ~1.18 × 10⁵ | ~2.5 × 10³ | Subluminal | B |
| Sun | 686.3 | 4.37 × 10⁵ | Subluminal | A |
| Earth | 37,905 | 7,909 | Subluminal | A |
| Moon | 178,448 | 1,680 | Subluminal | A |

### Computing k_Hubble

Using measured parameters:

```
H₀ = 67.4 km/s/Mpc  (Planck CMB)
   = 67.4 × 10³ m/s / (3.086 × 10²² m)
   ≈ 2.184 × 10⁻¹⁸ s⁻¹

R_CMB ≈ 9.527 × 10²⁶ m  (observed comoving distance)

v_Hubble = H₀ × R_CMB
         ≈ 2.184 × 10⁻¹⁸ s⁻¹ × 9.527 × 10²⁶ m
         ≈ 2.081 × 10⁹ m/s  (this is enormous! ~7× speed of light!!)

k_Hubble = c / v_Hubble
         = 299,792,458 m/s / (2.081 × 10⁹ m/s)
         ≈ 0.144
```

**Key observation:** k_Hubble ≈ 0.144, which places it in the **superluminal regime** (k < 1).

More precisely: **k_Hubble is between k_proton ≈ 0.546 and the c-boundary (k = 1).**

## k-Hierarchy Extended

Extending the table:

| Body/Scale | k | c/k [m/s] | Regime | Source |
|---|---|---|---|---|
| **Cosmology** | 0.144 | 2.08 × 10⁹ | Hypersuperluminal | DERIVED |
| Proton | 0.5464 | 5.49 × 10⁸ | Superluminal | OBSERVED |
| **c-boundary** | **1.0** | c | Light speed | CONSTANT |
| Hydrogen | 137 | 2.19 × 10⁶ | Subluminal | OBSERVED |
| ... (other bodies) | ... | ... | ... | ... |

**Extraordinary fact:** The cosmological k-value is MORE superluminal than the proton!

```
k_Hubble < k_proton < 1 < k_H < k_e < k_Sun < k_Moon
```

## Search for Quantisation Patterns

### Pattern 1: Integer or Rational?

Is k_Hubble a simple fraction or integer?

```
k_Hubble ≈ 0.144 ≈ 144/1000 ≈ 18/125

Checking small ratios:
  1/6 ≈ 0.167  (differs by 15%)
  1/7 ≈ 0.143  (differs by 0.7%) ← CLOSE!
  2/14 = 1/7  ← same
```

**Hypothesis 1:** k_Hubble = 1/7 (to within ~1% error)

But this seems arbitrary. Why 7?

### Pattern 2: Product or Ratio of Known k-Values?

Could k_Hubble be a combination of k_proton, k_H, k_e, k_sun?

```
k_p × k_H × k_e ~ 0.5464 × 137.036 × 1.18 × 10⁵
                ~ 8.84 × 10⁶

k_Hubble / (k_p × k_H × k_e) ~ 0.144 / (8.84 × 10⁶)
                               ~ 1.63 × 10⁻⁸  (nope)

k_H / k_p ~ 137 / 0.5464 ~ 251

k_Hubble × k_p ~ 0.144 × 0.5464 ~ 0.0787  (not recognizable)
```

No obvious product relation found.

### Pattern 3: Logarithmic Spacing?

In the k-hierarchy, k-values span many orders of magnitude. Perhaps they follow a logarithmic pattern?

```
log₁₀(k_proton) = log₁₀(0.5464) ≈ -0.262
log₁₀(k_Hubble) = log₁₀(0.144) ≈ -0.842

Δ log₁₀(k) ≈ 0.580  (roughly 1/1.7 decade)

log₁₀(k_H) = log₁₀(137) ≈ 2.136
log₁₀(k_proton) = -0.262

Δ log₁₀(k) from k_proton to k_H ≈ 2.398 ≈ 4 × 0.60  (roughly 4 decades)
```

**Hypothesis 2:** k-values are spaced logarithmically with some fundamental scaling constant.

But the gap structure doesn't reveal an obvious pattern.

### Pattern 4: Topological Linking Number?

From Phase 3, the linking number density drops by factor 4 at recombination.

Could k_Hubble encode this?

```
k_Hubble / k_proton ~ 0.144 / 0.5464 ~ 0.264 ~ 1/(3.8)

Heuristic: 1/(W_p × (1 + small)) where W_p = 3?  Not convincing.
```

### Pattern 5: Fine Structure Constant α?

The fine structure constant α ≈ 1/137 is the k-value for hydrogen:
```
k_H = 1/α ≈ 137
```

Is there an analogous "cosmological fine structure"?

```
α ~ 7.3 × 10⁻³
α² ~ 5.3 × 10⁻⁵

k_Hubble / α ~ 0.144 / 0.0073 ~ 19.7  (not recognizable)
k_Hubble × α ~ 1.05 × 10⁻³  (close to α²? off by factor ~50)
```

No clear pattern emerges.

## Physical Interpretation

### Why k_Hubble < k_proton?

The cosmological k is MORE superluminal (lower k) than the proton.

This might reflect:
1. **Lattice scale hierarchy:** At larger scales, the effective phase velocity increases (less restrained by local pressure gradients).
2. **Inflation remnant:** If inflation happened before the Clearing, the cosmological k might encode the inflationary phase velocity.
3. **Fundamental lattice resonance:** The cosmological scale is where the spation lattice itself exhibits a global resonance.

### The "Missing Physics"

One possibility: k_Hubble cannot be expressed in terms of particle k-values because it's an *orthogonal* feature of the lattice itself.

Just as the BAO scale (147 Mpc) is an emergent property of the coupled lattice (not reducible to atomic scales), k_Hubble might be a **pure lattice property**, independent of particle physics.

In this view:
- **Particle k-values:** (k_p, k_H, k_e, k_sun, k_moon) characterize individual topological defects
- **Lattice k-value:** k_Hubble characterizes the global lattice resonance mode

## Computed Results

| Quantity | Value | Unit | Provenance | Class |
|---|---|---|---|---|
| H₀ (Planck) | 67.4 | km/s/Mpc | MEASURED | X |
| R_CMB | 9.527 × 10²⁶ | m | OBSERVED | X |
| v_Hubble | 2.081 × 10⁹ | m/s | COMPUTED | B |
| k_Hubble | 0.144 | — | COMPUTED | B |
| k_Hubble ≈ 1/7? | 0.143 | — | HYPOTHESIS | PENDING |
| log₁₀(k_Hubble) | -0.842 | — | COMPUTED | B |

## Verdict

**PENDING** — Pattern not yet identified.

✓ **Cosmological k defined:** k_Hubble = c/(H₀ × R_CMB) is well-posed

✓ **Surprising result:** k_Hubble is hypersuperluminal, even more so than proton

✗ **Quantisation not found:** No clear integer, rational, or formulaic relationship with known k-values

✗ **Mechanism unknown:** Why does the cosmological scale have this particular k-value?

## Hypotheses for Future Investigation

1. **Inflaton hypothesis:** k_Hubble traces back to inflationary dynamics; need theory of inflation in SDT
2. **Lattice resonance:** k_Hubble is the global resonance mode of the spation lattice; CR05 lattice stability analysis may clarify
3. **Topological hierarchy:** Extended Law VI might extend the winding number concept to cosmological scales, generating k_Hubble
4. **Dimensional accident:** k_Hubble ≈ 1/7 by coincidence; no deep physics behind it

## Next Steps

**CQ41:** "Lattice Resonance at Cosmological Scale"
- Analyze coupled-oscillator dynamics of entire spation lattice
- Find normal modes and their k-values
- Does the fundamental lattice mode have k ≈ 0.144?

**FLM06:** "Inflation in SDT: Hypersuperluminal Phase Before Clearing"
- If k_Hubble encodes inflationary phase velocity
- Compute required inflation duration, e-folds, and cosmological observables
- Predict tensor-to-scalar ratio vs. observations

**GOM05:** "Extended Law VI: Cosmological Winding Numbers"
- Generalize W±1 conjecture to non-particle structures
- Compute linking number for the cosmological-scale lattice mode
- Does this predict k_Hubble?

## References

- GOM02: k-Hierarchy Advantage (foundation)
- Phase 1: Lattice Resonance Analysis (BAO scale physics)
- Phase 2: Comoving Distance (R_CMB computation)
- Phase 3: Topological Phase Transition (linking number density)
- Theory/02_Inputs_and_Derivations.md (SDT closure stages)
