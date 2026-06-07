# CQ03: Fine Structure Constant from Topology — INVESTIGATION RESULTS

> **Status**: RESOLVED (NEGATIVE RESULT)
> **Date**: May 2026; re-run + scroller June 2026
> **Tool**: `cq03_fine_structure.cpp` (11/11 proofs pass, exit 0 — re-verified June 2026)
> **Explainer**: `cq03_scroller.html` — REFRAMED 2026-06 (see note). Single-page scroller whose thesis is **α is koppa at the hydrogen ground state** — one rung of the k-ladder (ϟ=v²R/c², z·k²=1), not a magic constant. Editable inline ladder SVG; live "hydrogen rung" + "deflation test" widgets. NO QM abstractions (no Compton "coherence scale", no Bohr model, no wavefunction). Live JS reproduces the engine ladder exactly (verified in Node).
>
> **Measured anchors (re-run):** g_electron = r_e·m_e·c/ℏ = 7.2973525737e-03 (= α exact); g_proton = R_p·m_p·c/ℏ = 4.0007815131 (= W+1 = 4, 0.0195%). The k-ladder: proton-surface k=0.5464 ϟ=2.818e-15; **hydrogen k=137.04 (=1/α) ϟ=α²a₀=2.818e-15=r_e**; Sun k=686.3 ϟ=1477 m; Earth k=37905 ϟ=4.43 mm; Moon k=178450 ϟ=0.055 mm — z·k²=1 at every rung. Note the engine-confirmed coincidence: hydrogen-ground and proton-surface share the same koppa (2.818e-15 m).

## Framing correction (2026-06, author directive)
The original scroller leaned on QM abstractions (Compton wavelength as "quantum coherence scale", the Bohr model, "wavefunction phase-coherence") and over-dramatised α as Feynman's magic 1/137. **Both were wrong for SDT.** α is already shown (CQ16 k-hierarchy) to be merely **koppa at the H ground state** — `k_hydrogen = 1/α` (laws.hpp:573), `koppa_hydrogen = α²a₀ = r_e` (laws.hpp:581), sitting in the same `bridge` namespace as `koppa_Sun`. So "derive α from a knot?" is the wrong question: a koppa is set by a body's speed and size, not its topology (topology sets WHICH winding modes exist, not their speed). The honest residue is one mundane input — the charge `e` sets which rung EM lands on (α=k_e e²/ℏc); deriving e from lattice topology is CQ10. **Method principle (author):** do not borrow QM formulations/terms unless the mechanism is literally identical; SDT reaches the same numbers by mechanical/geometric relation. A dedicated FINAL investigation should catalogue all SDT-vs-QM parallels, what each means, and where SDT's view is superior — that synthesis is deferred, not done here.

---

## Question
Can α = 1/137.036 be derived from the W=1 torus geometry?

## Answer: NO

**α is NOT derivable from topology.** It is the electromagnetic coupling constant of an unknotted charge to the lattice. Its value requires the elementary charge e as an independent input.

### The Key Distinction

| Particle | g-number | Type | Meaning |
|----------|----------|------|---------|
| Proton (2,3 trefoil) | g = 4 = W+1 | Topological (integer) | Wake fixed by knot crossings |
| Electron (1,1 unknot) | g = α ≈ 1/137 | Electromagnetic (non-integer) | Wake fixed by charge coupling |

The proton's wake extends exactly 4 Compton lengths (topologically protected). The electron's wake extends only α Compton lengths (electromagnetically limited). The factor α/2 ≈ 1/274 between the actual and topological values IS the EM coupling.

### Circularity of All Derivation Attempts

Every attempt to extract α from SDT identities reduces to α = α:
- g-ratio: α = 4(r_e m_e)/(R_p m_p) — restates the g definitions
- Bohr: α = ℏ/(m_e ca₀) — a₀ contains α
- P_eff: α = (π/4)P_eff R⁴/(ℏc) — P_eff is defined from αℏc
- Lattice: substituting f into P_conv — all factors cancel to 1

### Input Hierarchy Conclusion

The minimal SDT input set is **{ℓ_P, T_CMB, e, d=3}**, not {ℓ_P, T_CMB, d=3}. Reducing to 3 inputs requires CQ10: Topological Charge Quantisation (deriving e from lattice defect structure).

## Proof Results (11/11 PASS)

| Proof | Description | Result |
|-------|-------------|--------|
| CQ03-1a | g_electron = α | **PASS** (exact) |
| CQ03-1b | α from Coulomb coupling | **PASS** (exact) |
| CQ03-1c | r_e = α²a₀ | **PASS** (exact) |
| CQ03-1d | r_e = αℏ/(m_e c) | **PASS** (exact) |
| CQ03-1e | g_proton ≈ 4 = W+1 | **PASS** (0.02%) |
| CQ03-2a | g_electron = α | **PASS** (exact) |
| CQ03-2b | g_proton ≈ 4 | **PASS** (0.02%) |
| CQ03-3a | α from g-ratio | **PASS** (0.02%) |
| CQ03-3b | α from Bohr radius | **PASS** (exact) |
| CQ03-3c | α from P_eff | **PASS** (exact) |
| CQ03-3d | α from radius/mass ratios | **PASS** (0.02%) |

## Verdict

**CQ03 RESOLVED (negative result).** α requires e. The charge quantum is an independent input. Forward dependency: CQ10.
