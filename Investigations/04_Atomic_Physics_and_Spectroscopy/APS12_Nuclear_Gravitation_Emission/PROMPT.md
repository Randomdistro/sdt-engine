# APS12 — Nuclear gravitation and emission (Δz)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC / PRE-REGISTERED 2026-08-13.  
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `GATEWAY_PROCEDURAL.md` · `GATEWAY_BEHAVIOURAL.md` · §0 anti-creep (R0–R5).  
> **Engine:** `#include <sdt/laws.hpp>` and `nuclear.hpp` only — no local constant namespaces.  
> **Gates:** `APS12_PRE_REGISTRATION.md` (written before any tool). Data: `DATA_REQUIREMENTS.md`.  
> **Canon edits:** none.  
> **Run:** Copy §⑩ into `RUN_LOG.md` and fill every `[COMMIT]` field before implementation.

Vocabulary: excluded / ruled out / falsified / withdrawn. Pre-registered, not “pre-commit.” Shared-input (not an evidence-label “degenerate”). Assessment file: `APS12_ASSESSMENT.md`. Execution-protocol “KILL” in this prompt is **excluded**.

---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Whether every electronic emission, every isotope displacement of a named line, and every ionisation energy is the gravitational depth difference `Δz = z_lower − z_upper` in the nuclear koppa well, with `z = ϟ_felt / r` evaluated at the actual electron seats — excitation for excitation, isotope for isotope, ionisation for ionisation — including when companions remain and when A changes at fixed Z.
2. **Why does it matter?** — GOM01 already identifies spectral shift with depth. APS01 already lands H-like wavelengths from velocity seats. If those two facts are the same fact, then a heavier nucleus and a stripped ion are not a different spectroscopy: they are deeper seats in a larger nuclear koppa. Nuclear construction (`Z`, `A`, `n_d`, `n_t`, remaining electrons) becomes a spectral predictor. If they are not the same fact, “nuclear gravitation” is a metaphor and this investigation must say so.
3. **How will we find out?** — Six gated phases (§④). Freeze hold-outs first. Validate the instrument on hydrogen (known answers). Then one-pass tables on the three predictive axes. Occupancy (S_bare, S_ion) and size (I_mass, I_size, I_grammar) are named in the pre-registration, not inverted from NIST.
4. **What would prove us wrong?** — §⑧: H-like `Δz` outside the APS01 bar; last-electron IE outside 1%/2%; a MATCH obtained by `Z_eff = n√(IE/Ry)`; King structure “explained” by re-sorting on `n_t` at fixed Z; a new screening fraction after seeing C-ION. Any one of those excludes the corresponding claim. The Δz ontology on H-like can survive while occupancy stays OPEN.
5. **How will we know we're done?** — Dual verdict on every phase and on the parent: prompt completion A–F (did the tables exist, at the required grain) + physics class NATIVE / CONVERGENCE / shared-input / EXCLUDED / OPEN. H-like alignment without a distinct occupancy or size hit is CONVERGENCE of the spine, not NATIVE-distinct.

**Domain:** Atomic physics and spectroscopy, coupled to nuclear construction. **Author:** J. C. Harvey, Melbourne.

*Anti-creep R0–R5: engine constants only; no G/M as fundamentals; no wavefunctions, fields-as-primitives, quarks, dark sector, ΛCDM; every number tagged MEASURED-INPUT · DERIVED · COMPUTED · CALIBRATED(n) · OBSERVED · PENDING · IDENTITY; translation test on borrowed words (Rydberg, field shift, screening — allowed as names of measured series, not as imported mechanisms); a miss stays a residual; CALIBRATED budget 0.*

---

## 1. Executive Summary

The question is whether **emission is gravitational z**: the photon energy between two electron seats is `½ m_e c² Δz`, the same depth law that redshifts the solar photosphere (GOM01 C1, 0.03%). The nucleus hides behind the atom’s c-boundary `ϟ = Z r_e` the way a stellar interior hides behind `r = ϟ`. Light we measure is born outside that surface. A heavier nucleus deepens the well (`z_n = (Zα/n)²` for one remaining electron). A further ionisation uncovers more of the nuclear koppa. A different isotope changes the recoil partner and the nuclear boundary the well sits on.

This investigation does not re-derive hydrogen as a trophy. It demands **predictive tables**: every frozen excitation, every frozen isotope pair, every frozen ionisation stage, with `z`, `ϟ_felt`, grammar, residual, and origin tag on each row. The H-like closed form is shared with Rydberg algebra — alignment there is CONVERGENCE. Distinct content is occupancy (companions) and construction (A, `n_d`, `n_t`, NP12 radius) without inverting the hold-out.

Expected outcome: a ledger that either (i) carries Δz through all three axes with named rules, or (ii) states which axis is CONVERGENCE, which is OPEN, and which is excluded — at the grain of the individual line, nuclide, and IE.

---

## 2. Physical Context

**Picture.** A star’s photosphere emits at depth `z = ϟ/R`. We never see through-going light from inside the koppa kernel. An atom is the same geometry at another pressure domain. Hydrogen’s c-boundary is `ϟ_H = α² a_0 = r_e = 2.818 fm`. The proton is at `R_p = 0.841 fm`, inside, `z = 3.35`, `k = 0.546`. The electron seats that make Lyman and Balmer sit at `r_n = n² a_0`, `z_n = α²/n²`, well outside. Strip carbon to C VI and the last electron sits at `z_1 ≈ 1.9×10⁻³` — nine hundred times the solar photosphere. Strip iron to Fe XXVI and `z_1 ≈ 0.036` — seventeen thousand times the solar photosphere. Those are not “X-ray physics” as a separate kingdom. They are deeper seats in a larger nuclear koppa.

**Excitation.** Raise the electron from seat `n_i` to `n_f` (or from one named term to another). The line is the difference of those depths. Lyman-α is `z_1 − z_2`. A different upper seat is a different Δz. That is the excitation axis.

**Ionisation.** Remove an electron entirely (`n_upper → ∞`). The ionisation energy is `½ m_e c² z_bound` of the seat it left. The next electron down sits in a less-screened well. Core breach (Be IE₂ → IE₃, and the named steps in C-ION-breach) is a drop onto a deeper koppa, not a new force.

**Isotope.** Same Z, different A: the electron still orbits the same nuclear charge, but the recoil partner mass changes (reduced mass) and the nuclear body changes (NP12 boundary; grammar `n_d`, `n_t`). King nonlinearity is what remains after mass and size in the laboratory’s own factorisation. APS07 struck using a re-sort on `n_t` at fixed Z as evidence. Landmarks remain: first triton entry, `n_t = n_d` crossing, EC-core isotopes.

**Key variables (dimensions explicit).**

| Symbol | Meaning | Dimension |
|---|---|---|
| `ϟ` | koppa of the center; H: `α² a_0`; H-like: `Z r_e` | m |
| `ϟ_felt` | koppa the electron actually occupies (bare nuclear or occupancy-reduced) | m |
| `r_n` | seat radius `a_0 n² / Z_geom` | m |
| `z` | depth `ϟ_felt / r = (v/c)² = 1/k²` | 1 |
| `Δz` | `z_lower − z_upper` for a line; `z_bound` for IE | 1 |
| `v` | seat speed `c √z` | m s⁻¹ |
| `k` | `c/v` | 1 |
| `Z` | proton count (nuclear charge number) | 1 |
| `A` | nucleon count | 1 |
| `q` or `k_IE` | ionisation stage index (NIST IE_k) | 1 |
| `N_e` | bound-electron count before the event | 1 |
| `n` | principal seat index of the active electron | 1 |
| `n_d`, `n_t` | deuteron / triton counts from `alpha_grammar` | 1 |
| `R_A` | NP12 nuclear boundary radius | m |
| `Θ` | sky fraction `(1/4)(R_A / r_n)²` | 1 |
| `μ` | reduced mass `m_e m_nuc / (m_e + m_nuc)` | kg |
| `λ`, `E`, `ν` | wavelength, energy, frequency of the line or IE | m, eV, Hz |

**Connection.** Law III is one force. Electropause `P_eff` (EMC04) sets the atomic domain magnitude. Koppa is the well. Depth–closure identifies clocks, relay speed, and spectral shift with `z`. This investigation is that identification applied to nuclear wells, not to the Sun.

---

## 3. Theoretical Framework

**Axioms and paid results used as legal inputs (not re-litigated here).**

1. **Law III.** `F = (π/4) P_eff R₁² R₂² / r²`. Gravity, Coulomb, nuclear contact share the shape. `P_eff` changes by domain.
2. **Koppa.** `ϟ = v² R / c² = R / k²`. Hydrogen: `k_H = 1/α`, `ϟ_H = r_e` (exact, APS05 / PPT02). H-like: `c_boundary_nuclear(Z) = Z r_e`.
3. **Depth–closure (engine).** `z = ϟ/r`; `c_far = c(1−z)²` (GOM22; `c(1−z)` alone is falsified); `z_spec = z(r_emit) − z(r_obs)`; `v = c√z`.
4. **Law V.** `v_circ² + v² = c²`. Leading binding `E = ½ m v² = ½ m c² z`. Next order `m c² (1 − √(1−z))` vs `½ m c² z` is logged at high Z as a remainder, never as a fitted patch.
5. **APS01 seats.** `v_n = Z α c / n`, `r_n = a_0 n² / Z`, `R_∞ = m_e c α² / (2h)`. H < 12.5 ppm, H-like Z≤30 < 263 ppm. Shared closed form with Rydberg algebra: CONVERGENCE, origin = velocity seats / Δz.
6. **Nuclear grammar.** `n_t = A − 2Z`, `n_d = 3Z − A − 2` (EC: He-3 core). Unique for Z ≥ 2. Free neutrons are not seated in stable nuclei.
7. **NP12.** `R(A) = R_p (A/η)^{1/3}`, `η = π/√18`. Input to I_size. Measured `⟨r²⟩` is not an input.
8. **Two-body recoil.** `μ/m_e` in `emission_wavelength_m`. Not QED.

**Claim under test.**

```
hν = ½ m_e c² (z_lower − z_upper)     emission
IE = ½ m_e c² z_bound                   ionisation (upper seat at infinity)
z = ϟ_felt / r
```

For one electron and a point center, `ϟ_felt = Z r_e` and this *is* the Rydberg formula. The investigation’s distinct burden is `ϟ_felt` when companions exist and when the center has size and grammar.

**Frozen occupancy (repeat of pre-registration; do not alter).**

```
S_bare:  ϟ_felt = Z r_e
S_ion:   IE_k uses Z_eff = k,  E_pred = Ry (μ/m_e) k² / n(k)²
```

`n(k)` is the frozen valence index of that electron in the corpus (last electron: n=1; do not fit n to land IE).

**Frozen isotope (repeat).**

```
I_mass:   standard reduced-mass scaling of the same Δz
I_size:   δν/ν = δΘ,  Θ = (1/4)(R_A / r_n)²,  R_A = nuclear_boundary_radius(A)
I_grammar: landmark coincidence report only; no extra scale
```

**Constraints.**

- No G, no M. No ψ. No QED log series as SDT terms. No Slater σ.
- `zk² = 1` is an identity. Print it. Do not gate physics on it.
- Do not invert `Z_eff` from IE. That is a re-expression of the hold-out.
- Do not restore APS04 1051.8. Lamb amplitude is out of scope.
- Do not retune `dnn`.
- Correspondence (`GM = c² ϟ`, Rydberg algebra) is not provenance.

**Law V remainder (logged on every H-like row with z > 10⁻³).**

```
E_bind/mc² = 1 − √(1 − z)     (Law V; v_circ = c √(1−z))
E_lead     = ½ m_e c² Δz
E_LV       = m_e c² [ (1 − √(1 − z_lower)) − (1 − √(1 − z_upper)) ]
δ_LV       = E_LV − E_lead
```

Print `δ_LV / E_lead`. Do not add a free coefficient to absorb `δ_LV` into a MATCH.

---

## 4. Investigation Strategy

Six phases. Phase N+1 is forbidden until PASS-GATE or documented DEFER. Direct execution. Single-pass comparisons: the whole corpus of a phase is computed from the frozen rule, then compared once.

### Phase 0 — Hold-outs, ledger, instrument (must precede all physics tables)

- **Goal.** A frozen `aps12_holdouts.csv` and a tool that reproduces hydrogen identities from `laws.hpp` without touching C-ION or C-ISO.
- **Method.**  
  1. Write `aps12_holdouts.csv` with every OBSERVED cell named in the pre-registration corpora C-EXC, C-ION, C-ISO, C-MULTI. Columns: `corpus_id, species, Z, A, ion_stage, transition, quantity, value, unit, source, citation`. SHA256 the file; record in `RUN_LOG.md`.  
  2. Implement the instrument (`aps12_nuclear_z_emission.py` or `.cpp`). Constants only from `laws.hpp` / `nuclear.hpp` (Python: copy with citation of the header line; do not round-trip a second local CODATA).  
  3. Instrument checks (known answers): `koppa_hydrogen == r_e`; `½ m_e c² α² == Ry_eV`; V0 wavelength; `zk²` print 1e-12.  
  4. Validate reduced-mass helper on ¹H vs a proton-infinite limit (difference must equal the known `μ/m_e − 1 ≈ −5.44×10⁻⁴` relative on R_∞).
- **Success.** V0 MATCH. Hold-out file complete or explicit `NO_DATA` rows. SHA256 in RUN_LOG.
- **Failure trigger.** V0 miss → stop. Tool fault, not a physics class on Δz.
- **Gate.** No C-EXC residuals until V0 PASS-GATE.
- **Duration.** 1–2 h.
- **Out of scope.** Any NIST comparison except the single V0 line 121.5670 nm. No screening. No isotopes.

### Phase 1 — Excitation for excitation (H-like Δz spine)

- **Goal.** For every C-EXC row, compute `z_n`, `Δz`, `E_lead`, `λ_pred` from `ϟ = Z r_e`, `r_n = a_0 n²/Z`, reduced mass, and compare to the frozen hold-out. One pass over the whole set.
- **Method.** Use `atomic::emission_wavelength_m` or the identical algebra. Also compute the explicit Δz path:

```
z_n = (Z α / n)²
E   = ½ m_e c² (z_nlow − z_nhigh) · (μ/m_e)
λ   = hc / E
```

The two routes must agree to 1e-9 relative (two-route verification). Print Law V remainder on C-EXC-deep.

- **Table required (every row, no summaries-only):**

`Z, A, ion, n_high, n_low, ϟ/fm, r_high/a0, r_low/a0, z_high, z_low, Δz, k_low, E_lead/eV, E_LV/eV, δ_LV/E_lead, λ_pred/nm, λ_obs/nm, Δppm, zk², μ/m_e, tag, corpus_id`

- **Success.** G_EXC and G_EXC_Fe as pre-registered.
- **Failure trigger.** Any C-EXC-Z row > 1000 ppm, or H series > 15 ppm, or Fe XXVI 2→1 > 0.5%.
- **Physics class cap.** Even on MATCH this phase is **CONVERGENCE** (shared closed form). NATIVE-distinct cannot be awarded here.
- **Gate.** Phase 2 may run if G_EXC PASS-GATE. If G_EXC fails, the Δz spine is excluded for H-like and later phases are DEFER (occupancy cannot be tested on a broken spine).
- **Duration.** 2–4 h including hold-out fill for Z=1–26.
- **Out of scope.** Neutrals, He-like, Lamb, fine-structure doublets as a scored target (may be printed as remainder).

### Phase 2 — Ionisation for ionisation

- **Goal.** Last-electron IE from the same Δz (upper at infinity). Full series under S_bare and S_ion, one pass each, no mixing.
- **Method.**  
  Last electron: `IE_Z = Ry (μ/m_e) Z²` with `n=1`. Compare C-ION-last.  
  Full series: for each `k=1..Z` in C-ION-full, compute S_bare (`Z_eff=Z`, n frozen) and S_ion (`Z_eff=k`, n frozen). Compare to json.  
  Core-breach: for C-ION-breach, print IE_k / IE_{k−1} and whether S_ion or S_bare places a jump at that k (ratio > 3 pre-registered as “jump”). The jump *location* is a structural claim; the ratio value is not fitted.

- **Tables required.**  
  **T2-last:** `Z, A_ref, μ/m_e, z_1, IE_pred/eV, IE_obs/eV, rel, ppm, tag`.  
  **T2-full:** `Z, k, N_e_before, n_frozen, Z_eff_S_bare, Z_eff_S_ion, E_bare, E_ion, E_obs, rel_bare, rel_ion, jump_flag, rule_closer, tag`.  
  **T2-breach:** one block per named breach: predicted jump k vs ATOMICUS label vs json gap.

- **Success.** G_ION_last MATCH. G_ION_S as pre-registered (80% of intermediate rows at rel<0.10 for **one** named rule). If neither rule hits 80%, occupancy OPEN — this is a legal outcome, not a licence to add S_frac.
- **Failure trigger.** G_ION_last miss → last-electron Δz excluded (inconsistent with Phase 1 if Phase 1 passed; that contradiction must be diagnosed as mass/n error, not a new law). Conduct failure: any `Z_eff` taken from `√(IE/Ry)`.
- **Gate.** Phase 3 does not depend on G_ION_S. Phase 3 depends on G_ION_last or an explicit DEFER.
- **Duration.** 2–3 h.
- **Out of scope.** Plasma Saha; CR15 ionisation epoch; fitting n(k).

### Phase 3 — Isotope for isotope

- **Goal.** Same excitation, different A, three frozen rules.
- **Method.**  
  C-ISO-H, C-ISO-He: I_mass vs measured isotope shift of the named line.  
  C-ISO-Ca, C-ISO-Yb: compute I_mass δν; compute I_size δΘ from NP12 `R_A` at the valence `r_n` of the **transition used in APS07** (state n and r_n on the row; Ca⁺ / Yb⁺ optical — use the lower-state n of that ion as frozen: Ca⁺ 4s n=4; Yb⁺ 6s n=6; do not fit n). Compare **sign** of δΘ steps to sign of tabulated δ⟨r²⟩. Do not ingest δ⟨r²⟩ into the predictor.  
  Grammar: print `(n_d, n_t)` for each A; mark `n_t=0` (Ca-40), `n_t=n_d` (Yb-174, Ca: 2A=5Z−2 → A=49, off the even chain — report that the Ca even chain does not contain the crossing). Landmark coincidence with residual sign-change is a **report**, not a MATCH on kHz.

- **Tables required.**  
  **T3-mass:** `species_pair, Z, A, A', line, μ, μ', δμ, ν_pred, δν_pred, δν_obs, rel_on_shift, tag`.  
  **T3-size:** `pair, R_A, R_A', Θ, Θ', δΘ, sign_δΘ, sign_δr2_obs, agree(0/1), |δν_I_size| if converted via νδΘ, tag`.  
  **T3-grammar:** `A, n_d, n_t, n_t−n_d, landmark(none|nt0|ntd|EC), King_residual_Hz (OBSERVED), δr2 (OBSERVED)`.

- **Success.** G_ISO_mass; G_ISO_size sign count; G_GRAM report complete.
- **Failure trigger.** I_mass miss on H–D Lyα >5% of the shift. Using measured ⟨r²⟩ as I_size input. Awarding MATCH because residuals sort with `n_t`.
- **Gate.** Phase 4 independent of G_ISO_size.
- **Duration.** 3–5 h.
- **Out of scope.** New-boson King terms as SDT; fitting F_i, K_i; APS04 0.761 MHz as a bulk isotope law.

### Phase 4 — Remaining electrons (not H-like lines)

- **Goal.** Apply only S_bare and S_ion to C-MULTI line *energies* (treat the line as Δz between two seats of the named Z_eff, with n_upper, n_lower frozen from the term labels: He I 1s–2p ⇒ n=1→2 at Z_eff from the rule; Na 3s–3p ⇒ n=3→3 is **same n** — then Δz from n-change is zero under a pure-n law, which is a recorded miss, not a prompt to invent ℓ). For same-n term differences, the Δz ontology as written in §3 (principal n only) **cannot** predict the line. Tag `SAME_N_NULL`. That is a limitation of this investigation’s n-only seats, not a licence to import spherical harmonics.
- **Method.** One pass. Print rel. No new rule.
- **Table T4:** `id, λ_obs, E_obs, n_lo, n_hi, E_S_bare, E_S_ion, rel_bare, rel_ion, SAME_N_NULL, tag`.
- **Success.** Table complete. G_MULTI: no MATCH required.
- **Failure trigger.** A coefficient added to land 58.4 nm or 6.700 keV.
- **Gate.** Phase 5 always runs if Phases 1–4 produced tables (including OPEN occupancy).
- **Duration.** 1–2 h.
- **Out of scope.** Fine structure, Lamb, Zeeman, Stark (APS08/09).

### Phase 5 — Whole-range ledger and assessment grain

- **Goal.** The assessment a third party can audit without opening the tool: every row, every gate, every origin tag, every residual, every `NO_DATA`.
- **Method.** Concatenate T1–T4. Compute corpus-level RMS **after** the one-pass (descriptive, not a new gate). Write `APS12_ASSESSMENT.md` to the required outline in §⑥. Write `aps12_results.txt` as full stdout. Write CSVs.
- **Success.** Prompt-completion grade from the checklist in §⑤. Physics class from the gates, not from RMS polishing.
- **Failure trigger.** Summary-only assessment; missing columns; mixing S_bare and S_ion mid-row; quoting APS01 as if it were this run’s stdout.
- **Duration.** 2–3 h.
- **Out of scope.** Canon edits to `laws.hpp`. Website copy.

---

## 5. Success Criteria

Use certification tags on numbers and physics class on claims. Prompt completion is separate.

**Prompt completion**

| Grade | Meaning |
|---|---|
| **A** | Phases 0–5 executed in order; all required tables with all required columns; hold-out SHA256; two-route check; dual verdict; pivot unused or documented |
| **B** | All phases run; ≤2 `NO_DATA` clusters documented; no missing columns on rows that have data |
| **C** | Phase 0–1 complete; later phases partial with DEFER reasons |
| **D** | Instrument only, or tables without gates filled |
| **F** | Tool not run; or assessment written without stdout; or hold-outs filled after seeing predictions |

**Physics class (parent claim: emission is Δz of nuclear-koppa seats)**

| Class | Metric | What you may state | Next |
|---|---|---|---|
| **NATIVE-distinct** | G_EXC MATCH **and** (G_ION_S MATCH on one frozen rule **or** G_ISO_size MATCH) with CALIBRATED(0) | Nuclear occupancy or packing size predicts something Rydberg algebra plus inverted Z_eff does not | Propose canon comment only if Harvey authorises |
| **CONVERGENCE** | G_EXC MATCH, G_ION_last MATCH, G_ION_S OPEN, G_ISO_size miss or untested | Δz is the H-like / last-electron spine; companions and finite-A size unpaid | Occupancy investigation, not a fit |
| **shared-input** | A “win” that is IE inverted into Z_eff, or zk² scored, or King re-sort | Not independent | Strike that row |
| **OPEN** | Spine holds; occupancy and size do not MATCH | Ontology of Δz on one-electron seats stands; `ϟ_felt` unpaid | Stop; do not S_frac |
| **EXCLUDED** | G_EXC fail or G_ION_last fail or prohibited move used to MATCH | Δz-as-emission fails on the spine, or conduct excluded the claim | Do not rescue |

**QUALIFIED / PENDING** in template language map here to CONVERGENCE + OPEN occupancy. There is no Class A DERIVED on companion screening in this prompt unless G_ION_S MATCH on a rule frozen above.

What to publish at CONVERGENCE: the three-axis tables and the statement that H-like emission *is* Δz, ionisation of the last electron *is* z_1, and the rest is occupancy/size debt. What not to publish: a native Fe XXV or Na D wavelength.

---

## 6. Outputs

Exact names. Renames need an ADJ entry.

1. **`RUN_LOG.md`** — pre-run block filled before code; SHA256 of hold-outs; phase decisions; ADJ entries.  
2. **`aps12_holdouts.csv`** — OBSERVED corpus, written before predictions.  
3. **`aps12_nuclear_z_emission.py`** or **`aps12_nuclear_z_emission.cpp`** — the instrument (created only after RUN_LOG commitments). Stdout is the machine record.  
4. **`aps12_results.txt`** — full stdout capture.  
5. **`aps12_T1_excitation.csv`** — Phase 1 every-row table (§④).  
6. **`aps12_T2_ionisation.csv`** — T2-last + T2-full + T2-breach (or three files with those prefixes).  
7. **`aps12_T3_isotope.csv`** — T3-mass + T3-size + T3-grammar.  
8. **`aps12_T4_multi.csv`** — Phase 4.  
9. **`APS12_DERIVATION.md`** — symbolic chain from `z=ϟ/r` to `hν=½mc²Δz` to S_bare/S_ion/I_mass/I_size; every step tagged DERIVED / IDENTITY / ASSUMED. No numerical fishing.  
10. **`APS12_ASSESSMENT.md`** — dual verdict. **Required grain (excessive, mandatory):**  
    - Restate ontology in ≤12 lines.  
    - Gate table: every pre-registered gate, numeric actual, MATCH/OPEN/EXCLUDED.  
    - **Excitation:** reproduce T1 in the assessment body or by inclusion of the CSV with a row count check (`N_rows` vs `N_holdout`). Call out the worst ppm row and the Fe XXVI Law V remainder.  
    - **Ionisation:** last-electron plot-in-words (Z vs rel); full series: per Z, which k S_ion is closer; core-breach location vs label. State 80% test arithmetic (numerator/denominator).  
    - **Isotope:** H–D shift numbers; Ca sign table; Yb-174 landmark sentence; explicit statement that a re-sort was not used as evidence.  
    - **Multi:** each C-MULTI line, rels, SAME_N_NULL flags.  
    - **Residuals / Scope / Limitations / Open problems** as headings (no escort adjectives).  
    - Parameter ledger of every constant read from `laws.hpp`.  
    - Prohibited-move checklist (ticked).  
    - Physics class per axis and parent class.  
    - Canon: no edit.

Missing any of those headings is prompt-completion ≤ C.

---

## 7. Dependencies & References

**Upstream (required).**  
- `Engine/include/sdt/laws.hpp` — `measured`, `bridge::koppa_hydrogen`, `atomic::*`, `depth_closure`, `nuclear::c_boundary_nuclear`, `nuclear::nuclear_boundary_radius`.  
- `Engine/include/sdt/nuclear.hpp` — `alpha_grammar`.  
- GOM01 / GOM22 — redshift = depth; `c_far = c(1−z)²`.  
- APS01 — H / H-like bar (instrument target, not a substitute for this stdout).  
- EMC04 — electropause `P_eff` (domain of the well).  
- NP12 — `R(A)` for I_size.  
- APS07 `DATA_COLLECTION.md` — C-ISO measured columns.  
- NP01 grammar constitution.

**Downstream (blocked on this assessment).**  
- Any claim that a multi-electron line is “just Z² Δz” without an occupancy class.  
- Canon promotion of a nuclear-size field-shift formula.  
- APS03 drafting using a derived D(outer) from this occupancy (only if G_ION_S MATCH, which is not assumed).

**Related.**  
- APS02 drag D(outer) — diagnostic from measured λ, not a predictor.  
- APS06 seat-depth band ordering — provenance of X-ray vs gamma; not this wavelength engine.  
- APS11 / PPT08 — Lamb; **out of scope**.  
- GD06 XSD-A field shift as sky fraction — cousin of I_size; do not import GD06 fitted σ_occ.  
- ATOMICUS `10_Gravitational_Redshift_Tables.md` — uses `z = E/13.606` as a rydberg-unit. **That is not depth z.** This investigation’s z is `ϟ/r = 2E/(m_e c²)`. Do not mix the symbols.

**Experiments.** E13–E20 EC charge-state (related to ionisation stage, not this emission engine).

---

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If inconsistent |
|---|---|---|---|
| T1 G_EXC | H-like lines are `½mc²Δz` at `ϟ=Z r_e` | max \|Δλ/λ\| ≤ 1000 ppm on C-EXC-Z; H ≤ 15 ppm | Δz spine excluded; stop occupancy claims |
| T2 G_EXC_Fe | High-z remainder is Law V, not a new scale | Fe XXVI 2→1 ≤ 0.5%; `δ_LV` logged | If miss, check reduced mass and NIST vacuum λ before excluding |
| T3 G_ION_last | Last IE is z_1 of the bare nucleus | Z=2..20 ≤ 1%; Z=21..30 ≤ 2% | Last-electron Δz excluded |
| T4 G_ION_S | Intermediate IE is S_bare or S_ion | ≥80% of intermediate rows rel<0.10 on one named rule | Occupancy OPEN; **do not** add a fraction |
| T5 invert | `Z_eff=n√(IE/Ry)` as predictor | Forbidden; if used, parent claim shared-input | Conduct exclusion |
| T6 G_ISO_mass | H–D Lyα shift is reduced mass | rel ≤ 5% of the shift | Two-body helper fault or wrong hold-out |
| T7 G_ISO_size | NP12 `R_A` covering fraction tracks δ⟨r²⟩ **sign** on Ca steps | 4/4 or 5/5 sign agreements | I_size OPEN; do not swap in measured ⟨r²⟩ |
| T8 G_GRAM | Landmarks, not a re-sort, are the grammar content | Report only | MATCH claimed from n_t-sort → shared-input, APS07 strike |
| T9 G_MULTI | No new coefficient | Table complete; He I / Na D / Fe XXV not forced | Coefficient → excluded conduct |
| T10 symbol | Depth z confused with E/Ry | Assessment uses `z=ϟ/r` only | Rewrite; do not gate on the rydberg-unit |

Recovery: pivot table §⑩. No recovery by fitting.

---

## 9. Implementation Notes

- **Language.** Python 3 is acceptable (json + csv). C++20 if all of C-ION is parsed without a second constant block. One instrument, one stdout.  
- **Precision.** Double throughout. Energies in eV, wavelengths in nm (vacuum), z dimensionless, ϟ in fm, R_A in fm, ppm as `1e6 (pred−obs)/obs`.  
- **Constants.** Cite `laws.hpp` line for α, a_0, r_e, R_p, Ry_eV, m_e, m_p, c, h, ħ. Do not type 13.6 as a literal except as the engine’s `Ry_eV`.  
- **Reduced mass.** `m_nuc` from AME or `A m_p` — declare per row. Hydrogen must use proton mass, not `A=1` times a nuclear average.  
- **n(k) freeze.** Last electron n=1. For outers, use the ground-configuration principal n of that electron as in NIST (He I 1s ⇒ 1; Na 3s ⇒ 3; Fe 4s ⇒ 4). Write the chosen n into hold-outs in Phase 0. Changing n after T2 is prohibited.  
- **Same-n lines.** Na D is 3s–3p. Principal-n Δz is zero. Tag SAME_N_NULL. That miss is information.  
- **He-like Fe XXV.** S_ion with k=25, n=1→2 is a number you will print; it is not a MATCH target.  
- **Numerical traps.** `z>1` inside the c-boundary: do not emit laboratory λ from `r < ϟ`. If a formula returns z>1 for an electron seat, the seat assignment is wrong — flag `Z_GT_ONE` and stop that row.  
- **Identity trap.** Printing `zk²=1` to 1e-15 is not Phase-1 success.  
- **Two routes.** Δz path vs `emission_wavelength_m` must agree.  
- **No plots required** as files; if made, they are illustrative and not gates.  
- **Windows.** Repo root; utf-8 stdout.

---

## ⑩ Adaptive Execution Protocol

### Pre-Run Commitment Block (copy into `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — APS12
- Prompt completion target: [COMMIT A|B|C]
- Physics class hoped: [COMMIT — CONVERGENCE of spine; NATIVE-distinct only if G_ION_S or G_ISO_size]
- CALIBRATED budget: 0
- Phase thresholds: V0 15 ppm; G_EXC 1000 ppm / H 15 ppm; G_EXC_Fe 0.5%; G_ION_last 1% (Z≤20) / 2% (Z≤30); G_ION_S 80% at rel<0.10; G_ISO_mass 5% of shift; G_ISO_size sign 4/4 or 5/5
- Forbidden retroactive changes: S_frac; Z_eff from IE; n(k) after Phase 0; threshold widening; dnn; 1051.8; scoring zk²; King re-sort as evidence; measured ⟨r²⟩ as I_size input
- Hold-out path / sha256: [COMMIT]
- Instrument filename: [COMMIT]
- Stdout path: [COMMIT]
```

### Pivot table

| Trigger (numeric) | First response (PIVOT) | If pivot fails | Forbidden response |
|---|---|---|---|
| V0 > 15 ppm | Check vacuum vs air λ; μ; `Ry_eV` vs `R_inf_derived` | OPEN instrument; do not open physics tables | Type 121.567 to pass |
| G_EXC one Z > 1000 ppm, others MATCH | Check that Z’s hold-out (air/vacuum, ion stage) | That Z `NO_DATA` or EXCLUDED row; corpus RMS not a rescue | Drop the row to improve max ppm |
| G_EXC_Fe > 0.5% | Compare E_lead vs E_LV; report δ_LV; still score E_lead against gate | EXCLUDED on Fe row; do not retune | Fit a Z⁴ term |
| G_ION_last Z>20 miss, Z≤20 MATCH | High-z remainder; still no fit | OPEN for Z>20 last-IE; keep Z≤20 | Lower the 2% bar after seeing Fe |
| G_ION_S both rules <80% | Occupancy OPEN | Stay OPEN | S_frac = 1 − IE/RyZ² |
| He I 24.6 vs S_ion 13.6 | Expected miss; record | Not a pivot | Average 13.6 and 54.4 to land 24.6 |
| G_ISO_mass H–D miss | Check tritium/deuterium masses in measured | OPEN I_mass helper | Scale μ to land |
| G_ISO_size sign ≤2 | I_size OPEN | Stay OPEN | Switch R_A to Angeli ⟨r²⟩ |
| King kHz looks like n_t | Print grammar table; **no MATCH** | — | Cite sort as evidence (APS07 struck) |
| Na D SAME_N_NULL | Record limitation of n-only seats | — | Import ℓ and “fit” 2.1 eV |
| Two-route Δz vs emission_wavelength_m > 1e-9 | Bug in E↔λ | Fix tool; re-run Phase 1 | Pick the closer to NIST |

### Allowed adjustments

- Mesh / print precision; vacuum-wavelength citation correction **if the hold-out was wrong and is corrected in ADJ before re-predict**.  
- Split T2 into three CSV files.  
- Python vs C++.  
- Phase 2a last-electron / 2b series if stdout is huge — same frozen rules.

### Disallowed adjustments

- RETRO-PASS (widening ppm). PLUG. IDENTITY-PASS on zk². BORROW-SMUGGLE of G, M, ψ, QED logs, Slater. Inverting Z_eff. Restoring 1051.8. Retuning `dnn`. Reading a draft assessment to choose S_ion vs S_bare.

### Dual verdict reminder

Prompt completion answers: were the phases executed at the required grain?  
Physics class answers: what is the origin of any number that landed? Alignment with NIST never counts against a native origin; shared closed form is CONVERGENCE; inverted hold-out is shared-input; a miss is a residual.

---

## Reader’s contract (this investigation)

- Depth `z` is `ϟ/r`, never `E/13.606`.  
- A line is `Δz`. A heavier nucleus or a stripped ion is a deeper seat.  
- H-like success is the spine, not the distinct nuclear-gravitation payload.  
- The payload is occupancy and construction, frozen before the table.  
- The assessment is the tables. If the tables are not there, the investigation did not happen.
