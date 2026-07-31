# CQ26: The Universal Drafting Crossover — A Forensic Cross-Scale Investigation

> **Classification:** Cross-scale unification test (atomic ↔ stellar-system ↔ galactic ↔ nuclear)
> **Prerequisites:** `laws.hpp` (bridge, law_I), `galactic.hpp` (a_0_SDT, regime_*), CQ13 emission engine, E101 solar pressure-domain marker, E46 twin-regime result
> **Provenance of the conjecture:** the E46 M4 convergence-floor law (RMS 23.8 %, BTFR 3.58, bias −1.6 %) and the CQ13 emission drag factor `D` were found to exhibit the *same* two-regime structure: a "source/drafting" regime (B → 1) and a "floor/exposed" regime (B → ξ^(−1/2)), separated by a crossover. The Sun's pressure-domain marker `r_domain = √(L/4πF_CMB) ≈ 20 860 AU` is the same crossover seen radially in a single star.
> **Author:** James Christopher Tyndall, Melbourne, Australia
> **Status:** PENDING (specification complete; execution not begun)

---

## 0. Reader's contract (non-negotiable, read before §1)

This is a **forensic** investigation. Every quantity is defined to the digit, every datum is traceable to a primary source, every hypothesis is pre-registered with a numeric falsification threshold, and every regime boundary is a stated inequality, not a vibe. The phrase "approximately" is banned from the deliverables; use a number and an interval.

Three failure modes have already occurred in adjacent work on this phenomenon and are therefore **explicitly forbidden** here:

1. **Circular validation.** (E46 v1 generated its "measured" velocities from the same formula it then tested.) No example's response variable `B` may be computed from, fitted to, or derived using the model being tested. Observables in, model out — never the reverse.
2. **Borrowed-function laundering.** (E46 M4's crossover shape was the MOND "simple" interpolation, not an SDT derivation.) The asymptotes of the universal curve are DERIVED and parameter-free; the **crossover shape is the unknown under test**. Any interpolation function used as a baseline must be labelled BORROWED and may not be reported as a derivation.
3. **Stale/placeholder data.** (A source header was served from a stale OneDrive cache mid-session, an 8× size discrepancy.) Every input file is hashed and line-counted at read time; see §10.

If any deliverable cannot satisfy §10's provenance protocol, it is marked `VOID` and excluded — not estimated, not interpolated, not "reconstructed."

---

## 1. The phenomenon (precise statement)

Every persistent structure in the spation lattice couples to the convergent throughput field `Φ = N·ε` (Law I). Its measurable response to that coupling, `R`, departs from the value `R₀` it would have *in isolation* (a bare, fully self-shadowed source) by a dimensionless **response factor**

$$ B \;\equiv\; \frac{R}{R_0} \;\ge\; \tfrac{1}{2}. $$

The **conjecture** (CQ26-H1) is that `B` is a function of a single dimensionless **exposure ratio**

$$ \xi \;\equiv\; \frac{g_{\text{self}}}{g_{\text{floor}}}, $$

the ratio of the structure's own convergence-gradient amplitude `g_self` to the universal background convergence floor `g_floor`, and that **this function is the same at every scale**:

$$ \boxed{\,B = \Phi(\xi)\,}\qquad\text{(scale-invariant; CQ26-H1).} $$

`g_floor` is **derived, not fitted**, from SDT invariants:
- dynamical floor `a₀ = c·H₀/(2π) = 1.042×10⁻¹⁰ m/s²` (`galactic.hpp:77`, `a_0_SDT`);
- radiative floor `F_CMB = c·u_CMB/4 = σ·T_CMB⁴` (`laws.hpp:247`), used only for the radiative cross-check (§6.B).

### 1.1 The two asymptotes (DERIVED — these are NOT under test)

| Regime | Condition | Limit of Φ | SDT origin |
|---|---|---|---|
| **Source / drafting** | ξ → ∞ | `Φ → 1` | self-shadow dominates; bare law recovered |
| **Floor / exposed** | ξ → 0 | `Φ → ξ^(−1/2)` | `g_obs → √(g_self·g_floor)` ⇒ `B = √(g_floor/g_self) = ξ^(−1/2)` |

The floor asymptote `Φ → ξ^(−1/2)` is the **only** parameter-free prediction with teeth: it forces (a) the Baryonic Tully–Fisher slope to 4 at galactic scale, (b) the alkali "lone-opener" drag ceiling at atomic scale, (c) the Oort radius at stellar scale. It must be confirmed independently in each.

### 1.2 The crossover (MEASURED — this IS the test)

The shape of `Φ(ξ)` for `0 < ξ < ∞` — the bridge between the two asymptotes — is **unknown** and is the object of the investigation. The pre-registered baseline for comparison is the BORROWED "simple" interpolation

$$ \Phi_{\text{simple}}(\xi) = \frac{1}{1 - e^{-\sqrt{\xi}}}, $$

which satisfies both asymptotes. **CQ26 succeeds only if it determines whether the real, measured `Φ` (a) is scale-invariant and (b) is or is not `Φ_simple`, and (c) whether it can be derived from SDT void/occlusion geometry.** Confirming `Φ_simple` is a null-ish result (SDT supplies the scale, MOND supplies the shape). Deriving a *different*, scale-invariant `Φ` from convergence geometry is the DANGEROUS (falsifiable, novel) result.

---

## 2. The four scales and their operational variables

The unit of analysis ("example") differs per scale and is fixed here. For each scale we define `B` (response), `R₀` (bare baseline), `g_self`, `g_floor`, and therefore `ξ`. **All formulas are to be implemented in C++20 against `Engine/include/sdt/` only; comparison data from the listed primary sources only.**

### Scale Ⓐ — ATOMIC (emission events)
- **Example unit:** one electric-dipole emission transition `(species, ionization stage q, upper level → lower level)`.
- **Response:** the emission drag factor `B_Ⓐ = D = λ_meas / [ (8/3)·λ_C·k² ]`, where `k = c/v` is the kinematic ratio of the active electron at the transition (`v = √(2·E_level/m_e)`), `λ_C = 2.42631×10⁻¹² m`. (CQ13 engine, verified D∈[0.87,2.19] monotone in shell occupancy.)
- **Bare baseline `R₀`:** `(8/3)·λ_C·k²` (full-drafting closed-shell emission, `D=1`).
- **g_self / g_floor → ξ_Ⓐ:** drafting is provided by co-shell electrons. **Pre-registered provisional** `ξ_Ⓐ = N_draft / N_void`, where `N_draft` = number of electrons co-occupying the active electron's `n`-shell at emission, `N_void` = unoccupied void slots in that shell (dyad/triangle/tetra/cube capacities, Atomicus §10). Lone opener: `N_draft→0 ⇒ ξ→0`. Closed shell: `N_void→0 ⇒ ξ→∞`. **The geometrically-correct `ξ_Ⓐ` is itself a deliverable (§7.3).**
- **Primary data:** NIST Atomic Spectra Database (https://physics.nist.gov/asd) — observed wavelengths, level energies, configurations. ATOMICUS isotope DB for nuclear grammar tags.

### Scale Ⓑ — STELLAR-SYSTEM (orbiting bodies)
- **Example unit:** one body in orbit about one host `(host, body, semi-major axis a, period P, host mass proxy)`.
- **Response:** `B_Ⓑ = v_obs² / v_Kep²`, where `v_Kep² = c²·koppa_host/a` is the SDT spherical (=Newtonian) bare orbital speed (`koppa_host = v_surf²R/c² = GM/c²`), `v_obs` from measured `a,P` (`v_obs = 2πa/P`).
- **Bare baseline `R₀`:** `v_Kep` (deep-in-wake Keplerian).
- **ξ_Ⓑ = g_host(a)/a₀ = (c²·koppa_host/a²)/a₀.** Planets: `ξ≫1`. Oort/wide-binary/detached TNO: `ξ→0`.
- **Primary data:** NASA Exoplanet Archive (NEXSCI), JPL SSD/Horizons (solar-system bodies, TNOs), Gaia wide-binary catalogue (El-Badry+ 2021), JPL small-body database. Host mass via `koppa` from an independent dynamical channel only (never from the body under test — anti-circularity).

### Scale Ⓒ — GALACTIC (rotation-curve points)
- **Example unit:** one rotation-curve radial sample `(galaxy, R)`.
- **Response:** `B_Ⓒ = g_obs/g_bar = v_obs²/v_bar²`, `v_bar² = Υ_d·V_disk|V_disk| + Υ_b·V_bul|V_bul| + V_gas|V_gas|` (SPARC decomposition, Υ_d=0.5, Υ_b=0.7).
- **Bare baseline `R₀`:** `v_bar` (pure baryonic).
- **ξ_Ⓒ = g_bar/a₀ = (v_bar²/R)/a₀.** Inner HSB/bulge: `ξ≫1`. Outer/LSB/dwarf: `ξ→0`.
- **Primary data:** SPARC `Rotmod_LTG` (already in repo: `Investigations/E46_Galaxy_Rotation_Curves/sparc_rotmod.csv`, 175 galaxies, 3014 usable points), master table `sparc_175.csv`.

### Scale Ⓓ — NUCLEAR (binding events) — STRETCH, run only if Ⓐ–Ⓒ pass §13 STRONG
- **Example unit:** one stable/long-lived nuclide `(Z, A)`.
- **Response:** `B_Ⓓ = (BE/A)_meas / (BE/A)_bare`, bare = single-deuteron drafting reference.
- **ξ_Ⓓ:** deuteron-packing drafting vs exposed-triton fraction; `ξ_Ⓓ = n_deu/(n_tri+1)` from the construction grammar (`n_t=A−2Z`, `n_d=3Z−A−2`). Alpha-only/closed: `ξ≫1`; triton-heavy actinide: `ξ→0`.
- **Primary data:** AME2020 mass evaluation; ATOMICUS isotope DB.

---

## 3. The taxonomy: scale → class → type, and the 40-per-cell mandate

### 3.1 Types (exactly three, defined by ξ-band — identical definition at every scale)

| Type | Symbol | Pre-registered ξ band | Role |
|---|---|---|---|
| **Source / drafting** | **S** | `ξ ≥ 10` | confirms `Φ → 1` asymptote |
| **Transition / crossover** | **T** | `0.1 < ξ < 10`, with ≥10 of the 40 inside `0.3 ≤ ξ ≤ 3` | **the shape test** — mandatory, not optional |
| **Floor / exposed** | **F** | `ξ ≤ 0.1` | confirms `Φ → ξ^(−1/2)` asymptote |

Type T is forensically essential: the asymptotes alone cannot distinguish `Φ_simple` from any other interpolation with the same limits. **A submission lacking the mandated transition-band density is VOID.**

### 3.2 Classes (exactly four per scale — chosen to control the dominant confound at that scale)

Classes are cross-cutting: each class must contain examples of **all three** types. Classes exist to test that `Φ` is invariant *within* a scale across the obvious physical confound, before testing invariance *across* scales.

| Scale | Confound controlled | C1 | C2 | C3 | C4 |
|---|---|---|---|---|---|
| Ⓐ Atomic | active-shell principal number | n=2 row | n=3 row | n=4 row | n=5 row |
| Ⓑ Stellar | host class | main-seq dwarf | giant | binary host | sub-stellar/PSR |
| Ⓒ Galactic | morphology | HSB spiral | LSB galaxy | dwarf irregular | bulge-dominated |
| Ⓓ Nuclear | grammar regime | α-only | deuteron-rich | triton-bearing | electron-capture alt-grammar |

### 3.3 The sampling matrix (the "40 of each" mandate, made literal)

```
            per cell:           40 examples
            cells per scale:    4 classes × 3 types = 12
            examples per scale: 12 × 40            = 480
            CORE scales (Ⓐ,Ⓑ,Ⓒ):                  = 1 440
            + STRETCH scale Ⓓ:                     =   480
            ─────────────────────────────────────────────
            TOTAL forensic corpus:                 = 1 920 examples
```

Each cell `(scale, class, type)` is a numbered stratum `Sᵢⱼₖ` with **exactly 40** examples (not "≥40"; if more qualify, select by the deterministic rule in §4.3). Under-filled cells (< 40 qualifying real examples) are reported as `SHORT(n)` with the achievable `n` and an explicit explanation — **never** padded with synthetic, interpolated, or duplicated entries.

---

## 4. Sampling protocol (deterministic, auditable)

### 4.1 Eligibility gate (applied before typing)
An example enters the pool only if **all** hold:
1. All quantities needed for `(B, ξ)` come from primary sources in §2 (no model-derived inputs).
2. Reported measurement uncertainties exist for the observable entering `B` (so `σ_B` is computable, §5).
3. The example's `ξ` is finite and positive after unit reduction.
4. Provenance record complete (§10).

### 4.2 Typing
Compute `ξ` (§5), assign S/T/F by §3.1 bands. An example whose `ξ` lands in a band whose cell is already full is held in reserve (§4.3), not discarded.

### 4.3 Selection to exactly 40 (deterministic, no cherry-picking)
Within each over-subscribed cell, rank candidates by **measurement precision** `σ_B/B` ascending (most precise first); take the top 40. Ties broken by ascending primary-source catalogue ID (lexicographic). This rule is fixed *before* any `B` is examined and is content-blind to the residual against `Φ` (anti-p-hacking).

### 4.4 Span requirement (prevents degenerate strata)
Within each Type-T cell, the 40 examples must span **at least 1.5 decades in ξ** and include ≥10 in `0.3 ≤ ξ ≤ 3`. Within S and F cells, report the ξ range; if an S or F cell cannot reach `ξ≥10` / `ξ≤0.1`, it is `SHORT` and the asymptote test for that cell is `INCONCLUSIVE`, not failed.

---

## 5. Measurement & error propagation (per example)

For each example produce the immutable record:

```
example_id | scale | class | type | source | source_id |
  raw_observables{…with σ} | k or koppa | g_self | g_floor |
  xi | sigma_xi | B | sigma_B | provenance_hash
```

- `σ_ξ`, `σ_B` by first-order propagation from the primary `σ` on each raw observable (full Jacobian, no dropped terms). Show the propagation algebra in the deliverable appendix.
- Atomic `k = c/√(2E/m_e)` ⇒ `σ_k = (k/2)(σ_E/E)`; `B=D ∝ k⁻²·λ` ⇒ relative errors add in quadrature.
- Stellar `v_obs=2πa/P` ⇒ `σ_v/v = √((σ_a/a)²+(σ_P/P)²)`; `B∝v²` doubles it.
- Galactic `σ_B` from SPARC `eVobs` and the M/L band (Υ varied 0.3–0.7 as a systematic, reported separately).
- All constants from `laws.hpp::measured` only; quote the line for each.

---

## 6. The tests (pre-registered, with numeric falsification thresholds)

### 6.A Per-scale asymptote tests (DERIVED predictions — pass/fail)
- **A-S:** mean `B` over each scale's Type-S pool. **PASS if `|⟨B⟩_S − 1| ≤ 0.10`** (within-scale, per class and pooled).
- **A-F:** regression of `log B` on `log ξ` over each scale's Type-F pool. **PASS if slope ∈ [−0.60, −0.40]** (predicted −0.50) and intercept consistent with 0 at 2σ.
- Report per class and pooled; a scale passes A-F only if ≥3 of 4 classes pass.

### 6.B Stellar radiative cross-check (independent observable, DERIVED)
Independently of dynamics, compute each star's radiative domain `r_domain = √(L/4πF_CMB)`. **PASS if the dynamical crossover `ξ_Ⓑ=1` radius and `r_domain` agree within a factor 2** for the Sun (target ≈ 20 860 AU vs Oort inner edge) and for ≥30 of 40 main-sequence Type-T hosts with measured `L`. This is the "two independent floors locate the same boundary" test.

### 6.C The collapse test (CQ26-H1 — scale invariance, the core)
Pool all examples across all core scales. Bin in `log ξ` (20 bins/decade). In each populated bin compute `⟨B⟩` and its standard error across scales.
- **Master-curve residual:** fit a monotone, asymptote-pinned spline `Φ̂(ξ)` by orthogonal-distance regression (errors in both ξ and B). Report `χ²/dof`.
- **PASS (H1 supported)** if, after fitting one shared `Φ̂`, each scale's points scatter about `Φ̂` with `χ²/dof ≤ 1.5` **and** no scale shows a systematic offset `> 0.10` in `⟨B/Φ̂⟩` averaged over the shared ξ range.
- **FAIL (H1 rejected)** if any scale is offset `> 0.25` or the per-scale best-fit `Φ` shapes differ by `> 3σ` in the transition band.

### 6.D Shape discrimination (MEASURED vs BORROWED)
Compare `Φ̂` to `Φ_simple(ξ)=1/(1−e^{−√ξ})`.
- Report `Δ_simple = ⟨|Φ̂ − Φ_simple|/σ⟩` over the transition band.
- If `Δ_simple ≤ 1`: result is `Φ ≈ Φ_simple` → **SDT supplies the floor scale, not the shape** (state this plainly; do not claim a shape derivation).
- If `Δ_simple > 3`: the data prefer a *different* universal shape → proceed to §7.3 (derive it).

### 6.E Cross-scale KS tests
For each pair of scales, two-sample KS test on the distribution of `B/Φ̂(ξ)` (the collapse residual). **PASS if no pair rejects identical distribution at α=0.01** (Bonferroni-corrected for the 6 pairs across 4 scales → α_eff=0.01/6).

---

## 7. Forensic sub-investigations (the "why," not just the "whether")

### 7.1 Confound regression
For each scale, regress the collapse residual `B/Φ̂` against every available nuisance variable (atomic: Z, ionization stage, n_tri of the nucleus; stellar: host metallicity, age, eccentricity; galactic: inclination, distance, quality flag Q, gas fraction). **Any nuisance with |partial correlation| > 0.2 at p<0.01 is a flagged confound** and the affected examples are re-examined (not silently kept).

### 7.2 Inclination/edge-on audit (galactic & stellar)
The known E46 outliers (NGC 4217, IC 4202) are edge-on/disturbed. Pre-register: are *all* galactic residual outliers (|B/Φ̂−1|>0.3) explained by inclination > 80° or kinematic-disturbance flags? Report the contingency table; this is a stated, falsifiable sub-claim.

### 7.3 Geometric derivation of ξ (the prize)
For each scale, the provisional `ξ` (§2) is a placeholder. Determine, by the collapse-optimisation in 6.C, the `ξ`-definition that best collapses the data, then test whether **that** `ξ` is derivable from SDT geometry:
- Atomic: from void capacities (dyad=2, triangle=3, tetra=4, cube=8) and Atomicus drafting rules — is `ξ_Ⓐ` a ratio of occupied to vacant void slots?
- Galactic/stellar: is the collapse-optimal `ξ` exactly `g_self/a₀`, or does it require a geometric prefactor (disk vs spheroid solid-angle, the `1/r³` line vs `1/r²` point kernel from CQ15)?
- **Deliverable:** for each scale, `ξ_geometric` with a derivation, and the residual `χ²/dof` using `ξ_geometric` vs the empirically-optimised `ξ`. Agreement within errors = the exposure ratio is DERIVED, not fitted.

### 7.4 Derivation attempt for Φ (only if 6.D says `Δ_simple>3`)
Attempt to derive the measured universal `Φ` from the convergence solid-angle integral (Law III occlusion of the `4π` hemisphere as the self-shadow grows). Target: a closed form whose only inputs are `{ℓ_P, c, ℏ, α, m_e, m_p}` and geometry. This, if achieved, is the DANGEROUS result.

---

## 8. Controls, blinding, and the look-elsewhere discipline

1. **Blind typing.** Assign S/T/F and fill cells using `ξ` **before** computing any `B`. The analyst computing `B` must not see the per-example `ξ`-rank until cells are frozen.
2. **Pre-registration freeze.** §6 thresholds, §3 bands, and §4.3 selection rule are frozen by committing this file's SHA to the investigation log before any `B` is computed. No threshold may move afterward; post-hoc analyses are reported in a separately-labelled "exploratory" section and carry no pass/fail weight.
3. **Negative control.** Construct a deliberately wrong floor `g_floor' = 100·a₀` and re-run 6.C. **The collapse must degrade** (χ²/dof must worsen by ≥3×); if a wrong floor collapses equally well, the test has no power and the result is `INCONCLUSIVE`.
4. **Scrambled-label control.** Permute example→scale labels 10⁴ times; the true cross-scale KS agreement (6.E) must sit in the top 1 % of the permutation null.
5. **Look-elsewhere.** All multi-cell pass rates carry Bonferroni or FDR correction; state which and the corrected α.

---

## 9. Required deliverables

1. `cq26_drafting_crossover.cpp` — the engine: ingests the four data files, computes `(ξ, B, σ)` per example, assigns types, applies §4.3 selection, emits the immutable per-example table (§5) as CSV.
2. `cq26_corpus.csv` — the frozen 1 920-row (or `SHORT`-annotated) forensic corpus, one row per §5 record, with provenance hashes.
3. `cq26_collapse.cpp` (or notebook-free C++ + emitted CSV) — the §6 tests, emitting: per-scale asymptote fits, the master curve `Φ̂`, all χ²/dof, KS matrix, `Δ_simple`, control outcomes.
4. `INVESTIGATION.md` — results **from measured program output only**, with the §13 verdict, every number carrying its interval, and a plain statement of which results are DERIVED vs BORROWED vs OBSERVED.
5. `provenance/` — for each primary source: URL, retrieval timestamp (passed in, never `Date.now()`), byte count, SHA-256, and the exact column/byte mapping used (the §10 protocol output).
6. Reproducible fetch scripts (`fetch_*.py`) for NIST, NEXSCI, Gaia, AME2020 — fetch-and-parse, no hand entry.

---

## 10. Anti-fabrication / provenance protocol (load-bearing)

For **every** input file, at read time, the engine records and prints: absolute path, byte count, line count, SHA-256, and first+last data row. Before use it asserts the byte count matches the recorded provenance; on mismatch it aborts with `STALE_SOURCE`. (This exists because a source was once served from a stale cache at 1/8 its true size; the assertion would have caught it.)

- **No datum is hand-typed** into a `.cpp` array if a machine-readable primary source exists. Hand-curated examples are quarantined in a separately-labelled file and excluded from pass/fail unless every value carries a primary citation.
- **No fallback masquerading as real.** If a primary source is unreachable, the affected cells are `SHORT`/`VOID`; a fallback may be used only with a banner stating it is fallback and is excluded from §13 verdicts.
- **Circularity assertion.** The engine statically refuses to let any field of `R₀`, `g_self`, or `g_floor` depend on `B` or on `Φ`. Document the call graph proving observables→model only.

---

## 11. Prohibitions (framework-level, from `Theory/00_Ruleset.md`)

- No `G`, no `M` in kg as fundamentals: gravity enters only via `koppa = v²R/c²`. `GM_equivalent()` is for unit conversion in cross-checks, never as an input.
- No dark matter, no dark energy, no ΛCDM, no NFW halo, no MOND `a₀` **as a fitted input** (the floor `a₀` here is DERIVED `c·H₀/2π`; if the analysis ever tunes it, the result is CALIBRATED and must say so).
- No quantum wavefunctions / fields-as-primitives at the atomic scale: emission via the movement budget + kinematic ratio only (CQ13 lineage).
- Permitted inputs: `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + measured observables in measured units. Every constant cites its `laws.hpp` line.

---

## 12. Certification labels (apply to every reported number)

`DERIVED` (from axioms + CODATA only) · `COMPUTED` (deterministic from the laws) · `CALIBRATED` (one fitted parameter — must be named) · `OBSERVED` (validated vs measurement, mechanism stated) · `PENDING` (mechanism identified, computation incomplete). The asymptotes are DERIVED; the floor scale is DERIVED; the crossover shape is, until §7.4 succeeds, `PENDING` or `BORROWED`.

---

## 13. Success ladder

| Level | Requirement | Verdict |
|---|---|---|
| **PASS** | Full 1 920-example corpus built under §10; per-scale asymptote tests (6.A) pass for all three core scales | the two regimes are real and universal in their limits |
| **STRONG** | + Collapse test (6.C) passes H1 (χ²/dof ≤ 1.5, no scale offset > 0.10) + KS (6.E) + negative control (8.3) shows power | one scale-invariant `Φ` governs all scales |
| **COMPELLING** | + `ξ_geometric` (7.3) reproduces the collapse-optimal `ξ` within errors at every scale | the exposure ratio is DERIVED, not fitted |
| **DANGEROUS** | + `Φ` itself derived from convergence solid-angle geometry (7.4), distinct from `Φ_simple`, with a stated experimental discriminator | SDT predicts a universal law QM/MOND/ΛCDM do not |
| **NULL** | Collapse fails (6.C FAIL) or wrong-floor control collapses equally well | the cross-scale unification is rejected — equally publishable |

---

## 14. First-week execution order (so the corpus is never the bottleneck)

1. Day 1–2: stand up §10 provenance harness; wire SPARC (in-repo, Scale Ⓒ ready now) → compute `(ξ,B)` for all 3014 points → fill Ⓒ cells; this is the pilot that validates the whole pipeline on data already in hand.
2. Day 2–3: NIST ASD fetch (Scale Ⓐ); CQ13 already computes `D` and `k` — extend to multi-line, multi-stage; fill Ⓐ cells.
3. Day 3–4: NEXSCI + JPL + Gaia (Scale Ⓑ); fill Ⓑ cells; run 6.B radiative cross-check.
4. Day 5: freeze corpus (commit SHA), run §6 tests blind, run §8 controls.
5. Day 6–7: §7 forensic sub-investigations; write `INVESTIGATION.md` from measured output only.

> The galactic scale is the pilot because its data and `(ξ,B)` machinery already exist and already pass at the asymptotes (E46 M4: Type-F slope, BTFR 3.58). If the pipeline cannot reproduce the existing M4 numbers exactly on Ⓒ before any new data is added, **stop** — the harness is wrong.

---

### Appendix A — provisional constants (cite `laws.hpp` line at use)
`a₀ = c·H₀/2π = 1.042e-10 m/s²` (`galactic.hpp:77`) · `F_CMB = c·u_CMB/4` (`laws.hpp:247`) · `koppa_Sun = R_Sun/k_Sun² ≈ 1477 m` (`laws.hpp:539`) · `koppa_per_baryon = ℓ_P²c·m_p/ℏ ≈ 1.242e-54 m` (`laws.hpp:594`) · `λ_C = 2.42631e-12 m` (`laws.hpp:137`) · drag law `D = λ/[(8/3)λ_C k²]` (CQ13).

### Appendix B — the one-line statement of the whole investigation
*Does a single, SDT-derived exposure ratio `ξ = g_self/g_floor` collapse the emission drag of atoms, the orbital boost of bodies, and the rotation excess of galaxies onto one scale-invariant curve `B = Φ(ξ)` whose floor limit `ξ^{-1/2}` is forced by the convergence floor — and is `Φ` derivable from occlusion geometry, or merely the borrowed MOND shape with an SDT-supplied scale?*
