# PPT11 — Neutrino Flavour Oscillation: symbolic chain

> **Spec:** `PROMPT.md` (Tier-5, the hardest open problem). **Executor run:** 2026-07-01.
> **Engine:** values transcribed from `Engine/include/sdt/{laws.hpp,neutrino.hpp}` (cited per line); no local constant namespace.
> **Tags per line:** `DERIVED` · `COMPUTED` · `MEASURED-INPUT` · `ASSUMED` · `OBSERVED-TARGET` · `PENDING` · `IDENTITY`.

This document is deliberately honest about where the chain is native and where it is not.
The headline (see `PPT11_VERDICT.md`): the **length lands** (Class-D foothold) but the **mechanism is unpaid** — the beat model does not independently derive the oscillation phase factor from SDT relay cadence, and the P1 degree-of-freedom licence is in tension with the neutrino's defining zero-grip. The result is a **sharpened `[OPEN]`**, exactly the outcome the spec called most likely.

---

## P1 — The three flavours as configurations of one W=0 vortex

**Hard constraint (Law VI).** All three flavours are the **same** open winding `W = 0` (`neutrino.hpp:66`, `law_VI::winding`). A flavour change is therefore **not** a winding change: `ΔW = 0` across e/μ/τ. `[DERIVED]` (topology). If oscillation required `ΔW ≠ 0` it would be a *different particle*, not oscillation (spec T2) — this is satisfied: no ΔW is invoked anywhere below.

**Candidate internal DoF.** The proposed distinguishing degree of freedom is the **helical pitch angle `θ_pitch`** of the open helix — a *continuous internal angular* DoF that leaves the integer winding untouched. Under Law V the movement budget `v_T² + v_P² + v_C² + v_t² = c²` (`laws.hpp:517–524`) partitions a fixed budget; a different pitch spends it differently → different displacement volume `V_disp,i` → different resistance (mass) `m_νi` (Law IV, `law_IV`). `[ASSUMED]` — this is the engine's existing narrative (`neutrino.hpp:5–8, 130–136`), adopted as the working hypothesis, **not independently derived here.**

**Mapping the three engine minima (all MEASURED-INPUT, `neutrino.hpp:38–40, 74–76, 82–89`):**

| Config | `m_νi` (eV) | `R_wake,i` (µm), round-tripped | `V_disp,i` (m³) | `θ_pitch,i` (assigned) |
|--------|-------------|-------------------------------|-----------------|------------------------|
| 1 | 0.020 | 9.866 (engine 9.87) ✔ | 3.91e-69 | shallowest |
| 2 | 0.029 | 6.804 (engine 6.80) ✔ | 5.66e-69 | middle |
| 3 | 0.060 | 3.289 (engine 3.29) ✔ | 1.17e-68 | steepest |

Wake radii round-trip from the masses to <1% (`ppt11_results.txt`, sanity gate `PASS`) → inputs correctly wired. `[COMPUTED]`

**Flavour ≠ single minimum.** Measured mixing (`sin²θ12=0.307`, `sin²θ23=0.546`, `neutrino.hpp:51–52`) means each *flavour* e/μ/τ is a **blend/dominance** of the three configs, not one mass minimum. Geometrically: a flavour is a particular **weighting of the three pitch minima** the vortex currently occupies. `[ASSUMED]` — stated geometrically, **not** as a wavefunction ket (the prohibited object).

### P1 GATE HINGE — FLM11 DoF census (the tension the spec flagged)

FLM11 (spec `FLM11_Tape_Measure_and_Ruler_Count/PROMPT.md`; the census is **not yet run**, only specified) locates the neutrino at the **straight/through axis `Π_∥`**, which it defines as the **zero-grip residue**: "pure through-flow along the core axis, **no circulation to catch, no handedness to resolve, no resistance to push against** … therefore `Π_∥` has **no native instrument**" (FLM11 §3).

This is a **double-edged licence**, and honesty requires stating both edges:

- **Edge that helps:** FLM11 does grant the straight axis as a genuine DoF of the form (it exists, carries momentum/energy).
- **Edge that hurts (decisive):** the straight axis is defined by **zero circulation / zero grip**. A pitch-precession **beat needs an internal circulation to precess against**. The very property that makes the neutrino a neutrino (no toroidal/poloidal circulation — `PPT04` μ_ν≡0, no ℓ=2 wake) is the property a geometric beat would need and does not have.

**P1 gate verdict: TENSION, not a clean grant.** The engine *asserts* three pitch angles; FLM11 (the census that was supposed to license them) actually says the straight axis has no grippable internal circulation. The pitch DoF is therefore **licensed only if** the open helix retains a *residual* internal angular freedom distinct from the graspable circulation FLM11 zeroes out — a distinction the current engine does **not** derive. **Recorded as a partial-DEFER / OPEN hinge** (see VERDICT falsifier T1). We proceed to P2/P3 to test the *number* while carrying this as an unpaid debt, exactly as `PROMPT_EXECUTION_PROTOCOL.md` permits (ship partial, no PASS on the parent claim).

---

## P2 — Native beat mechanism (attempted) and the phase factor

**Beat construction.** Two near-degenerate configs `i,j` accumulate relative phase along the flight path `x`. The beat length is `L_osc,ij = 2π / (dφ_ij/dx)`. `[DERIVED]` (definition).

**Phase per unit length.** The only expression that reproduces the observed scale is the standard

  `dφ_ij/dx = Δm²_ij · c³ / (4 ℏ E_ν)`     `[1/length]`

which gives `L_osc = 4π E ℏ / (Δm² c³) = 2.48 · E[MeV] / Δm²[eV²]` metres.

**Dimensional check (P2 metric): PASS.** With `Δm²` carried as an energy-squared difference, `[Δm² c³ / (ℏ E)]` reduces to `[1/m]` (tool `dimensional_check()`, `ppt11_results.txt`). The proportionality is built from `{ℏ, c}` (whitelist) and `Δm²` (here the **engine-implied** splitting, below) — **no fitted coefficient**. `[COMPUTED]`

**Translation test (NATIVE vs LINGUISTIC-BORROW) — the honest core.**
The factor `1/(4 ℏ E)` is the **standard quantum oscillation phase**. In the textbook derivation it arises from two mass eigenstates propagating with an energy difference `ΔE ≈ Δm² c⁴ / (2E)` and interfering — **a wavefunction of superposed mass kets**, which SDT prohibits as a primitive. To count as NATIVE, SDT must re-derive **this same factor** from relay cadence + resistance differences of ONE object, with no ket.

**Result of the translation test: FAIL-as-NATIVE (this run).** This investigation did **not** independently derive `1/(4 ℏ E)` from lattice relay cadence. It **borrowed** the factor and re-narrated it as "a geometric beat of one straight vortex precessing between three resistance minima." That re-narration is **linguistically** consistent with SDT but is **not** a derivation: nothing here forbids a different kinematic factor; the `2` in `Δm² c⁴/(2E)` (hence the `4` in `4ℏE`) is not produced by any SDT geometry in this run. Per the spec's own anti-tautology rule (§3: "reproducing `L_osc = 2.48·E/Δm²` … is IDENTITY-PASS unless the splitting is built independently"), we did build the splitting independently (below) — but the **kinematic phase factor remains imported**. `[PENDING]` — this is the mechanism hole.

---

## P3 — The decisive number, built from the three minima (NOT from Δm²_meas)

**Anti-identity-pass construction.** The tool builds the splitting **only** from the three mass minima:

  `Δm²_ij (engine) = m_j² − m_i²`     `[DERIVED-from-minima]`

It **never** reads `neutrino::measured::Dm21_sq / Dm32_sq` to construct `L_osc`; those appear **only** in the OBSERVED-TARGET column (`ppt11_oscillation_length.py`, enforced by construction).

  Δm²_21(engine) = 0.029² − 0.020² = **4.41e-4 eV²**  (OBSERVED solar 7.53e-5)
  Δm²_32(engine) = 0.060² − 0.029² = **2.759e-3 eV²**  (OBSERVED atmos. 2.453e-3)

**Comparison table (from `ppt11_results.txt`):**

| scale | E | L_SDT [m] | L_meas [m] | log₁₀(L_SDT/L_meas) | label |
|-------|---|-----------|------------|---------------------|-------|
| solar (ν2−ν1) | 1 MeV | 5.624e3 | 3.293e4 | **−0.77** | within ±1 decade |
| atmos. (ν3−ν2) | 1 GeV | 8.989e5 | 1.011e6 | **−0.05** | within ±1 decade |

**Both scales land within ±1 decade with zero fitted knobs.** The atmospheric scale lands to **12%** (log₁₀ −0.05). **P3 FLOOR: MET.** `[COMPUTED]`

**T5 robustness (from tool):** the log₁₀ ratio is **exactly E-independent** (−0.768 solar / −0.051 atmos. across 0.1 MeV → 1 GeV) because `L ~ E` on both sides. The offset is a property of the **masses**, not a coincidence of the chosen `E_ν`. So the agreement is **not** an E-coincidence (T5 clears). `[COMPUTED]`

---

## P4 — Recursive root-cause analysis

**Branch A — the number PASSED (P3 floor met). Why did it match? (cause^n)**

1. *Why does L_SDT land within a decade?* → Because Δm²_ij(engine) from the minima ≈ measured Δm²_ij (atmos. 12% off, solar 5.9× off).
2. *Why is Δm²_32(engine) ≈ measured?* → Because the engine masses 0.029, 0.060 eV give m₃²−m₂² ≈ 2.76e-3, close to 2.45e-3.
3. *Why are those masses that close?* → **Root cause, and it is not clean:** m₂=0.029, m₃=0.060 are literature "normal-ordering best estimates," and the wider-literature best estimates **are themselves informed by the measured Δm²**. The independence audit shows they do **not** round-trip to the naive back-solve (0.0218/0.0541 given m₁=0.02), so it is **not a hard identity-pass** — but it **is a partial circularity**. The match is therefore **partly earned, partly inherited**. `[root: PARTIAL-CIRCULARITY]`
4. *Is the beat mechanism the reason?* → **No.** The phase factor `1/(4ℏE)` was imported, not derived (P2). The match rides on (a) the minima being roughly right and (b) the standard phase formula. Neither is an SDT-native beat derivation. `[root: IMPORTED PHASE FACTOR]`

**Branch B — the mechanism FAILED to be NATIVE. Why? (to root)**

1. *Why no native `dφ/dx`?* → Because the `1/(4ℏE)` kinematic factor was not produced by SDT geometry; it was borrowed from the mass-eigenstate result.
2. *Why couldn't SDT produce it?* → Because P1's internal DoF (pitch precession) is **not licensed cleanly**: FLM11 defines the neutrino's straight axis as **zero-grip / zero-circulation**, and a beat needs an internal circulation to precess. The mechanism has **no grippable internal clock** to set the cadence.
3. *Why is there no internal clock?* → **Root cause:** the same geometry that makes the neutrino nearly non-interacting (open W=0, no toroidal/poloidal circulation, `PPT04` μ_ν≡0) removes the very internal circulation a native beat would precess. **The straight-thread picture and the flavour-beat picture are in structural tension.** `[root: ZERO-GRIP ⇒ NO NATIVE BEAT CLOCK]`

**No branch ends at "unclear."** The two root causes are: **(i) partial circularity in the mass inputs**, and **(ii) the beat clock is geometrically absent because the neutrino is defined by zero circulation.** These are the sharpened statement of the open problem.

---

## Summary of tags

- `DERIVED`: ΔW=0 across flavours (topology); beat-length *definition* `L=2π/(dφ/dx)`; the engine-implied splitting `Δm²_ij=m_j²−m_i²`.
- `COMPUTED`: wake-radius round-trip; the L_SDT vs L_meas table; E-independence.
- `MEASURED-INPUT`: the three minima m_ν1/2/3.
- `OBSERVED-TARGET`: measured Δm²₂₁, Δm²₃₂ (comparison column only).
- `PENDING` / hole: the `1/(4ℏE)` phase factor (imported, not native); the P1 internal-DoF licence (in tension with FLM11 zero-grip).
- `ASSUMED`: pitch-angle DoF as the flavour axis; flavour = blend of configs.

**Net:** the length is a **Class-D numerical foothold**; the mechanism is **`[OPEN]`** — a sharpened, honestly-recorded open problem, not a closure.
