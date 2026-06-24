# PPT02: Fine Structure Constant from Topology — INVESTIGATION RESULTS

> **Status**: RESOLVED (NEGATIVE RESULT)
> **Date**: May 2026; re-run + scroller June 2026
> **Tool**: `cq03_fine_structure.cpp` (11/11 proofs pass, exit 0 — re-verified June 2026)
> **Explainer**: `cq03_scroller.html` — REFRAMED 2026-06 (see note). Single-page scroller whose thesis is **α is koppa at the hydrogen ground state** — one rung of the k-ladder (ϟ=v²R/c², z·k²=1), not a magic constant. Editable inline ladder SVG; live "hydrogen rung" + "deflation test" widgets. NO QM abstractions (no Compton "coherence scale", no Bohr model, no wavefunction). Live JS reproduces the engine ladder exactly (verified in Node).
>
> **Measured anchors (re-run):** g_electron = r_e·m_e·c/ℏ = 7.2973525737e-03 (= α exact); g_proton = R_p·m_p·c/ℏ = 4.0007815131 (= W+1 = 4, 0.0195%). The k-ladder: proton-surface k=0.5464 ϟ=2.818e-15; **hydrogen k=137.04 (=1/α) ϟ=α²a₀=2.818e-15=r_e**; Sun k=686.3 ϟ=1477 m; Earth k=37905 ϟ=4.43 mm; Moon k=178450 ϟ=0.055 mm — z·k²=1 at every rung. Note the engine-confirmed coincidence: hydrogen-ground and proton-surface share the same koppa (2.818e-15 m).
>
> **Seat-closure addendum (2026-06-20):** the koppa-rung reading is now demonstrated from the **raw measured spectrum** — see *Seat-Closure from the Spectrum* below + `cq03_seat_closure.cpp` (2/2 PASS, α never used in the computation). The negative result is unchanged; the addition pins down what *does* close and what does not.

## Framing correction (2026-06, author directive)
The original scroller leaned on QM abstractions (Compton wavelength as "quantum coherence scale", the Bohr model, "wavefunction phase-coherence") and over-dramatised α as Feynman's magic 1/137. **Both were wrong for SDT.** α is already shown (GOM02 k-hierarchy) to be merely **koppa at the H ground state** — `k_hydrogen = 1/α` (laws.hpp:573), `koppa_hydrogen = α²a₀ = r_e` (laws.hpp:581), sitting in the same `bridge` namespace as `koppa_Sun`. So "derive α from a knot?" is the wrong question: a koppa is set by a body's speed and size, not its topology (topology sets WHICH winding modes exist, not their speed). The honest residue is one mundane input — the charge `e` sets which rung EM lands on (α=k_e e²/ℏc); deriving e from lattice topology is FLM05. **Method principle (author):** do not borrow QM formulations/terms unless the mechanism is literally identical; SDT reaches the same numbers by mechanical/geometric relation. A dedicated FINAL investigation should catalogue all SDT-vs-QM parallels, what each means, and where SDT's view is superior — that synthesis is deferred, not done here.

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

The minimal SDT input set is **{ℓ_P, T_CMB, e, d=3}**, not {ℓ_P, T_CMB, d=3}. Reducing to 3 inputs requires FLM05: Topological Charge Quantisation (deriving e from lattice defect structure).

## Proof Results (11/11 PASS)

| Proof | Description | Result |
|-------|-------------|--------|
| PPT02-1a | g_electron = α | **PASS** (exact) |
| PPT02-1b | α from Coulomb coupling | **PASS** (exact) |
| PPT02-1c | r_e = α²a₀ | **PASS** (exact) |
| PPT02-1d | r_e = αℏ/(m_e c) | **PASS** (exact) |
| PPT02-1e | g_proton ≈ 4 = W+1 | **PASS** (0.02%) |
| PPT02-2a | g_electron = α | **PASS** (exact) |
| PPT02-2b | g_proton ≈ 4 | **PASS** (0.02%) |
| PPT02-3a | α from g-ratio | **PASS** (0.02%) |
| PPT02-3b | α from Bohr radius | **PASS** (exact) |
| PPT02-3c | α from P_eff | **PASS** (exact) |
| PPT02-3d | α from radius/mass ratios | **PASS** (0.02%) |

---

## Seat-Closure from the Spectrum (2026-06-20)

> **What this adds:** the "α = koppa rung of hydrogen" reframing above, demonstrated from the **raw measured spectrum** instead of from engine identities. Tool: `cq03_seat_closure.cpp` (compiles against `laws.hpp`; output `cq03_seat_results.txt`; 2/2 PASS). **α is never used to compute the seat** — it appears on exactly one line, the final comparison.

The negative result is intact: α is not derivable from topology, and the input set is unchanged. But there **is** a closure here, and it is worth stating precisely — because "there is no closure" is the wrong reading, and the correct one is narrow and defensible.

### The seat

Hydrogen's **ionisation energy is an independent observable** — the short-wavelength limit of any of its series. Fed through the Law-V virial (½mₑv² = E), it hands back the electron's koppa rung:

| series | n | λ_limit (measured) | E_ion | v/c | k = c/v | k/n |
|---|---|---|---|---|---|---|
| Lyman | 1 | 91.1753 nm | 13.5984 eV | 7.29541×10⁻³ | 137.0725 | 137.0725 |
| Balmer | 2 | 364.7010 nm | 3.3996 eV | 3.64771×10⁻³ | 274.1450 | 137.0725 |
| Paschen | 3 | 820.5780 nm | 1.5109 eV | 2.43180×10⁻³ | 411.2177 | 137.0726 |

`v = √(2E/mₑ)`, `k = c/v` — computed from `{E, mₑ, c}` only. The seat is **k = 137.07**, and `α_H = 1/k` falls straight out of the spectrum. The whole series collapses onto one rung index, **kₙ = 137.07·n** — the koppa ladder, series-independent: Lyman, Balmer and Paschen each read the same seat.

### Why this route is non-circular (where the old attempts were not)

The "Circularity of All Derivation Attempts" table above is correct — g-ratio restates the g-definitions, Bohr smuggles α in through `a₀ = ℏ/(mₑcα)`, P_eff is built from `αℏc`. **This route uses none of them**: no a₀, no P_eff, no anchored field amplitude, no W=1·ℏ machinery — one measured energy and two measured constants. Delete the single comparison line in the tool and the seat **k = 137.07 still computes**. That is the operational meaning of "α is the output, not an input": you do not dial α in, you read it off the light.

### What does NOT close (so the claim survives scrutiny)

- `E_ion = ½mₑ(αc)²` is the Rydberg relation, so reading k from E_ion is **inverting** it — E_ion and α carry the same information. The input count is **unchanged**; the minimal set **{ℓ_P, T_CMB, e, d=3} stands**. The seat trades the abstract coupling for a concrete observable; it does not eliminate it.
- `z·k² = 1` is **definitional bookkeeping** (z ≡ (v/c)², k ≡ c/v) — it cannot fail, so it is not evidence. The content is the *ladder* (hydrogen's levels ARE koppa rungs, kₙ = 137.07n), not the identity.
- The seat is **137.07** — hydrogen's real rung, proton free. CODATA 137.036 is the proton-nailed-to-infinity idealisation; real hydrogen does not sit there, and the value is **not** patched toward it (no reduced mass, no two-body QM correction).

### What it earns

α is **not** a Feynman-magic dimensionless coupling dialed into the universe — it is the koppa rung of hydrogen's ground state, the same kind of object as `koppa_Sun`, and the spectrograph reads it off directly. *Every hydrogen says so.*

**Precise rebuttal to "there is no closure":** the koppa ladder **closes** (kₙ = 137.07n, z·k² = 1, verified across three series from raw measured limits), and the seat is **fixed by the spectrum** with α the output of {E, mₑ, c}. What is *not* claimed is α-from-topology or α-from-nothing — that remains PPT02's standing negative result. Conflating "the ladder closes and the seat is read from data" with "α was derived from first principles" is the skeptic's error; they are different statements, and only the second is false.

---

## Verdict

**PPT02 RESOLVED (negative result).** α requires e. The charge quantum is an independent input. Forward dependency: FLM05.

**Seat-closure addendum (2026-06-20):** the koppa-rung reading is confirmed from the raw measured hydrogen spectrum (`cq03_seat_closure.cpp`, kₙ = 137.07n across Lyman/Balmer/Paschen, α never used in the computation). This does **not** change the input count — it pins the reinterpretation (α = koppa rung of H, read from the spectrum, not dialed in) to data, and locates exactly what closes (the ladder) versus what does not (α-from-nothing).
