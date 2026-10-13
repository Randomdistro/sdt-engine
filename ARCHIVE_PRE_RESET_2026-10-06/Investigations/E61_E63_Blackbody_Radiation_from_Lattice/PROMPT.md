# E61–E63: Blackbody Radiation from Lattice — Data/Prompt

## DATA REQUIREMENTS
| Data | Value | Source |
|------|-------|--------|
| Planck spectrum B(ν,T) | Standard formula | Textbook |
| Stefan-Boltzmann constant σ | 5.670374×10⁻⁸ W/(m²K⁴) | CODATA |
| Wien displacement constant | 2.898×10⁻³ m·K | CODATA |
| CMB spectrum (FIRAS) | Blackbody T=2.7255 K (0.01% precision) | COBE FIRAS |
| Radiation constant a | 7.5657×10⁻¹⁶ J/(m³K⁴) | CODATA |
| SDT mode counting | Spation lattice modes per unit volume | To derive |

## INVESTIGATION PROMPT

**Target**: Derive the Planck/blackbody spectrum from SDT lattice mode counting.

### SDT Interpretation
The blackbody spectrum is NOT about "quantised oscillators" (Planck's original). In SDT:
- The spation lattice has a discrete set of modes (like phonons in a crystal)
- Each mode can carry energy in units of ε = hν (this is the lattice's natural quantisation — it's a LATTICE PROPERTY, not a particle property)
- The Planck distribution arises from counting lattice modes + Boltzmann statistics
- No photons needed — just lattice modes

### Three Derivations (E61, E62, E63)

**E61 — Planck spectrum**:
1. Count lattice modes in frequency interval dν: n(ν) = 8πν²/c³ (same as electromagnetic mode counting, because the lattice IS the medium)
2. Average energy per mode at temperature T: ⟨ε⟩ = hν / (exp(hν/kT) − 1)
3. Spectrum: u(ν) = n(ν) × ⟨ε⟩ → standard Planck function

**E62 — Stefan-Boltzmann**:
1. Total energy density: u = ∫ u(ν) dν = aT⁴
2. Show a = 8π⁵k⁴/(15c³h³) emerges from the lattice mode integral
3. SDT interpretation: a = (number of modes per volume) × (average energy per mode) at temperature T

**E63 — Wien's law**:
1. Peak of u(ν): ∂u/∂ν = 0 → ν_max = 2.821 kT/h
2. Equivalently λ_max T = 2.898×10⁻³ m·K
3. SDT: the peak is where the mode density × occupation factor is maximised — a purely geometric/statistical result

### Success Criteria
- [ ] Planck spectrum derived from lattice mode counting
- [ ] σ and a reproduced from the mode integral
- [ ] Wien constant reproduced
- [ ] The derivation uses only lattice properties (no "quantum" postulates beyond lattice discreteness)
