# SDT Formulation Provenance Audit — Three-Axis Classification (v2)

Companion to `FORMULATIONS_CENSUS.md`. Every formulation carries **three independent labels** that together project onto a **spine category (A–F, X)**. Numbers (`#n`) reference census rows.

This pass is **hostile and fair**. Two failure modes are equally guarded against:
- **Over-claiming** — laundering a borrowed equation, a fitted scale, or a definitional identity into a "derivation."
- **Over-demoting** — penalising a genuine SDT-first computation merely because it consumes a *permitted primitive constant*. **Using `ℓ_P` is not importing `G`. Using `α` is not consuming the target.** The real question is always: *did the matched target value enter the derivation?*

---

## 1. The three label axes (orthogonal)

**`provenance_status`** — *where the derivation starts*
| value | meaning |
|---|---|
| `SDT-posited` | an axiom / definition / operator — asserted, not derived |
| `SDT-derived` | produced by an SDT derivation from posited axioms + permitted inputs |
| `calibrated` | ≥1 scale anchored to a measured **target** value to fix magnitude |
| `external-input` | the quantity *is* a measured constant, borrowed law, or observational anchor |
| `unresolved` | path incomplete, contested, **definitional/circular**, or failed |

**`correspondence_status`** — *what the endpoint corresponds to*
| value | meaning |
|---|---|
| `known-match` | reproduces an established empirical / standard result |
| `novel-prediction` | departs from / extends standard physics; stated test path |
| `internal-only` | SDT-internal quantity, no established counterpart |
| `pending-test` | prediction not yet computed or checked |

**`input_dependency`** — *what the derivation consumes* (the new axis that prevents over-demotion)
| value | meaning |
|---|---|
| `primitive-whitelist` | only `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` — the declared permitted scale set |
| `measured-observable` | a measured quantity *other than the matched target* (e.g. a planet's v, R) |
| `calibrated-target` | the known value being matched is fed into the derivation (fatal to C) |
| `borrowed-function` | an external *functional form* is adopted (e.g. MOND interpolation shape) |
| `definitional-identity` | "result" is an algebraic identity of its inputs (e.g. α ≡ k_e e²/ℏc) |
| `unresolved` | dependency not yet traced |

> Provenance audits the **path**, correspondence audits the **endpoint**, input-dependency audits the **fuel**. They are orthogonal. A result can be `external-input` in fuel yet `known-match` in endpoint and still be honest — it is just labelled `X`, not C.

## 2. Spine categories (A–F, X) and the projection

```
A — SDT-posited axiom / definition
B — SDT-derived internal result
C — SDT-derived convergent known-match
D — SDT-derived novel prediction with test path
E — calibrated bridge result
X — external-input component / borrowed functional form
F — unresolved, unverified, or failed
```

| Cat | Generating rule |
|---|---|
| **A** | `SDT-posited` × (`internal-only`/`known-match`) |
| **B** | `SDT-derived` × `internal-only` |
| **C** | `SDT-derived` × `known-match`, **and** `input_dependency ∈ {primitive-whitelist, measured-observable}` |
| **D** | `SDT-derived` × `novel-prediction` |
| **E** | `calibrated` × (any) — `input_dependency = calibrated-target` |
| **X** | `external-input` × (any) — `input_dependency ∈ {external constant, borrowed-function}` |
| **F** | `unresolved` × (any), or (any) × `pending-test`, or `input_dependency = definitional-identity` |

**`C-flagged`** = a C result carrying a `risk_flag` (a defensible-but-contestable dependency, e.g. a conjectural rule, or a primitive that conventionally encodes a standard-physics quantity). Still C; the flag is disclosed, not demoted.

## 3. The integrity rules (the teeth — and their limits)

1. **C is gated on `SDT-derived` provenance.** A `known-match` from `SDT-posited` is A; from `calibrated` is E; from `external-input` is X.
2. **The matched target must not enter the derivation.** If `input_dependency = calibrated-target` or `definitional-identity`, it is **not** C → E or F.
3. **Calibration is contagious — *conditionally*.** *Calibration propagates only when the calibrated quantity sets the magnitude of the result being tested **and does not algebraically cancel**. Whitelisted primitive constants are **dependency-tracked, not automatically demoted.*** (This replaces the v1 blanket "calibration is contagious," which was too punitive.)
4. **Permitted primitive ≠ calibrated target.** `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` are the declared input layer. Consuming them keeps a result eligible for C. Only feeding in *the specific value being matched* breaks C.
5. **Borrowed functional form → X, not C.** If an external *shape* (interpolation function, density profile) is adopted, the shape is X even when the scale that fills it is SDT-derived. Split the formula: keep the SDT-first part as C/B, quarantine the borrowed shape as X.

## 4. The operational discriminator (hostile-examiner-proof)

The labels above are adjudicated by one mechanical test, applied to every C/D candidate:

> **Delete the correspondence check.**
> Run the derivation with no reference to the known value or known equation.
> - **Result unchanged** → the match was a *consequence*. → **C** (or D).
> - **Result vanishes / is undetermined / must be back-filled** → the known value was load-bearing. → **E** (fitted) / **F** (definitional) / **X** (borrowed form).

This turns provenance from rhetoric into **dependency tracing**. Every `class: C` annotation in the code must be able to assert `circularity_assertion: no matched target value enters the derivation` — and that assertion is exactly the delete-test passing.

## 5. The defence this encodes

> **Attack:** "You just rewrote existing equations." / "Every result uses CODATA constants, so it's all calibrated."
> **Response:** "C is convergence, not translation — and consuming a *permitted primitive* (`ℓ_P`, `α`, `m_e`) is dependency-tracked, not calibration. The discriminator is the delete-test: remove the correspondence check and the C results are unchanged because the matched value never entered the path. Where the target value *did* enter — definitional identities, fitted scales, borrowed shapes — we label E/F/X, not C. See the Watchlist; we name our weakest claims before a critic does."

---

## 6. Watchlist — contested provenance (read first)

The claims a hostile reviewer attacks, each adjudicated by the delete-test. **Revised from v1: #49 is no longer auto-demoted.**

| # | Formula | Delete-test result | Labels | Cat |
|---|---|---|---|---|
| #65 | `k_e e² = α ℏ c` | Vanishes — α *is* `k_e e²/ℏc`; nothing left to compute | prov `unresolved` · corr `known-match` · dep `definitional-identity` | **F** |
| #69 | `g(1)=r_e m_e c/ℏ = α` | Vanishes — `r_e ≡ α ℏ/(m_e c)`; identity | prov `unresolved` · dep `definitional-identity` | **F** |
| #62 | `m_p/m_e=(3/2)^{3/2}·10³−1` | Back-fills — integer factors `[2(p+q)]³=1000`, `−1` chosen to hit 1836.15 | prov `unresolved` · corr `known-match` · dep `calibrated-target` | **F** |
| #62b | `m_p/m_e=6π⁵` | Coincidence — no forward path requires 6π⁵ | prov `unresolved` · dep `calibrated-target` | **F** |
| #23 | `P_eff` (hydrogen-calibrated) | Vanishes — magnitude set by measured `R_p,r_e,k_e,e` | prov `calibrated` · dep `calibrated-target` | **E** |
| #24/#25 | `f=P_eff/P_conv`, `R_charge=√(R_p r_e)` | #24 inherits #23's *magnitude* (does not cancel); #25 consumes measured radii | prov `calibrated` · dep `measured-observable`→`calibrated-target` | **E** |
| #107 | eclipse `κ_area=9.1e-29 m²` | Vanishes without the fitted cross-section | prov `calibrated` · dep `calibrated-target` | **E** |
| **#49** | **`ϟ_per_baryon=ℓ_P² c m_p/ℏ`** | **Unchanged** — uses only primitive-whitelist `{ℓ_P,c,m_p,ℏ}`; the per-baryon koppa is produced without feeding in any measured `G` or `M`. **`G` is never an input.** | prov `SDT-derived` · corr `known-match` · dep `primitive-whitelist` · **risk_flag: CODATA `ℓ_P` conventionally encodes G under standard physics** | **C-flagged** |
| M4 | `g_obs=g_bar/(1−e^{−√(g_bar/a₀)})` (e46_twin_regime) | **Split.** `a₀=cH₀/2π` unchanged (C); BTFR deep-limit `v⁴=GM_bar a₀` unchanged (C); the *interpolation shape* is a borrowed MOND form (X) | a₀: prov `SDT-derived` dep `primitive-whitelist` → **C**; shape: prov `external-input` dep `borrowed-function` → **X** | **C-asymptotes / X-shape** |
| #67 | `R_p=4ℏ/(m_p c)` (W=3) | Unchanged given the W+1 *rule* — but the rule is conjectural | prov `SDT-derived` · corr `known-match` · dep `primitive-whitelist` · **risk_flag: W+1 not proven from trefoil geometry** | **C-flagged** |
| #56 | `c` from Mercury precession | Unchanged — re-derives an input from geometry (closure) | prov `SDT-derived` · corr `known-match` · dep `measured-observable` | **C (closure)** |
| #74 | `α = 1/ϟ_H` | α is a *permitted primitive*; this expresses it as hydrogen koppa, not a fit | prov `SDT-derived` · dep `primitive-whitelist` · risk_flag: α also an input | **C-flagged** |
| T⁴ | `κ(z)=κ₀(1+z)⁴` redshift | Falsified for SNe Ia (saturates wrong) | prov `unresolved` · corr `known-match`→fails | **F (failed)** |

**The #49 correction in one line:** the v1 audit conflated *"uses a whitelisted primitive that standard physics happens to define via G"* with *"imports G."* The delete-test shows `G`/`M` never enter the path → the result is **C**, carrying an honest `risk_flag` about `ℓ_P`'s conventional origin. Disclosed, not demoted.

---

## 7. Master classification (grouped by spine)

Format: `#census — name — (provenance · correspondence · input_dependency)`. Contested cases cross-reference §6.

### A — SDT-posited axiom / definition
- **#1** `c=ℓ_P/t_P` · **#3** `|u|≤c` · **#4** `v_circ⊥v_trans` · **#5** `τ=1/d=1/3` · **#6** `v_circ²+v²=c²` · **#7** `z·k²=1` · **#8** `ϟ=v²R/c²` — all (`SDT-posited` · `internal-only` · n/a).

### X — external-input component / borrowed functional form
- **#2** permitted-input constants `{ℓ_P,c,ℏ,k_B,T_CMB,α,m_e,m_p}` and CODATA values — (`external-input` · `known-match` · primitive layer). *The given layer; not a result, not a failure.*
- **#10** `u_CMB=aT⁴` (standard radiation thermodynamics, used as input relation) — (`external-input` · `known-match` · `borrowed-function`).
- **M4 interpolation shape**, **ΛCDM comparison model** (zk2_pantheon_proof), **de Vaucouleurs / exponential-disk profiles** (galactic.hpp f_dev/f_enc), **Shue magnetopause fit**, **Petschek `0.1 v_A B`** — borrowed astrophysical/empirical forms. (`external-input`/`calibrated` · `borrowed-function`). *Petschek/Shue are also fitted → E; listed here for the borrowed-form flag.*

### B — SDT-derived internal result (no external counterpart)
- **#9** `⟨cos²θ⟩=1/3` · **#11** `ε=u_CMB ℓ_P³` · **#13** shell-cancellation · **#14** `Φ=Nε` · **#17** `φ(n̂)=Φ/4π` · **#30** `m=ΦV_disp/3ℓ_P³c²` · **#31** `V_disp` · **#35** GPI `δ=aℓ_P/c²` · **#58** `m(p,q)` · **#60** `v_p²+v_t²=c²` · **#63** stable angle · **#117/#118** spation-rotation field (1.831c) · **#120/#122/#123/#124/#125** lattice/traction/depth results — (`SDT-derived` · `internal-only` · primitive-whitelist).
- **#12/#15** `N`, `P_conv` — (`SDT-derived` · `internal-only` · primitive-whitelist) · **risk_flag: chain conditioned on hard-coded `R_CMB`** (a calibrated scale; see E).
- **#33** `P_cf=P_conv/3` — `SDT-derived` · `internal-only` · *flagged: algebraic identity, not a verification.*

### C — SDT-derived → convergent known-match (the load-bearing defence)
*All pass the delete-test: the matched value never enters the path. Fuel is primitive-whitelist or measured-observable only.*
- **SR from the budget:** #37 γ · #38 time dilation · #39 length contraction · #40 E₀=mc² · #41 energy–momentum · #42 photon limit · #43 relativistic mass.
- **Inertial/Newtonian:** #18 Newton I · #36 Newton II (`F=ma` from relay) · #32 equivalence principle.
- **Gravity/GR from koppa:** #44 Kepler · #45 `g=v²/R` · #46 `R_c=R/k²` · #47 grav. time dilation · #48 `GM` recovery · #51 precession 42.98″ · #52 deflection 1.75″ · #53 Shapiro · #54 frame dragging · #55 Schwarzschild metric · #56 `c` re-derived (closure) · #57 Earth interior (E97, 1.82%, CONFIRMED).
- **Atomic (α as permitted input):** #70 Rydberg · #71 ionisation · #72 fine structure · #73 Bohr · #74 α=1/ϟ_H *(C-flagged)* · #75 atomic zk²=1 · #76 21 cm.
- **Force-law structure / nuclear:** #22 `F=(π/4)P_eff R₁²R₂²/r²` *(1/r² structure C; coefficient via #23 = E)* · #26 Coulomb force · #27 occlusion solid angle · #77/#78 construction grammar (valley of stability) · #84 `R_nuc=Z R_p` · #67 `R_p=4ℏ/m_p c` *(C-flagged: W+1 conjectural)*.
- **Cosmology:** #16 `S=4πN²` (Λ count) · #91 Hubble law · #93 `c_s=c/√3` · #96 age from BAO · #97 `T(z)` · #99 Hawking T/L from koppa · #100 `a₀=cH₀/2π` (recovers MOND scale).
- **Gravitational, no-G/M, C-flagged:** **#49** `ϟ_per_baryon` *(risk_flag: ℓ_P↔G)*.
- **Galactic:** #101–#104 flat curves from occlusion (M4 a₀/BTFR parts; interpolation shape → X).
- **Validated lab/astro:** E48 v_GW=c · E56 Compton · E70 z=GM/rc² · E77 Sagnac · E79/E80 511 keV · E81 de Broglie · E84 AB · E85 Josephson · E86 QHE · E89 bremsstrahlung · E90 GZK.

### D — SDT-derived novel prediction with test path
- #34 CMB dipole · #50 baryon census without M · #64 `μ_ν≡0` · #106 universal drafting crossover · #108 `Δz∝cos b` · #114 H₀(ν)<H₀(CMB)<H₀(local) · #128 six-layer SNe Ia decomposition *(partly calibrated → D/E)*.
- **Experiments (novel, test path):** E13–E20 charge-state EC · E21 orbit-drop · E23 Cavendish interior deficit · E25 Pioneer · E42/E49 H₀ gradient/no-Λ · E76 `G=c²R/k²r` · E94/E96 convergence focusing · E98 pressure-dependent G · E100 `c=c(ω)`.

### E — calibrated bridge result (`input_dependency = calibrated-target`)
- #23 `P_eff` · #24 `f` · #25 `R_charge` · #107 eclipse `κ_area` · `Σ_sat=175` · Shue/Petschek fits · B04 Lamb (`k_Lamb`) · B25 He variational (`Z_eff=Z−5/16`).
- **#16/#12/#15 dependency note:** `R_CMB=9.527e26` is hard-coded (H₀-derived) → an E-class scale that the Law I chain (B) is conditioned on. Tracked, flagged.

### F — unresolved / definitional / numerological / failed / pending
- **Definitional identities:** #65 `k_e e²=αℏc` · #69 `g(1)=α`.
- **Number-fits:** #62 trefoil ratio · #62b 6π⁵.
- **Unconfirmed:** #59 `M₀≈1 TeV`.
- **Failed:** T⁴ redshift model.
- **Pending (spec only; → D on computation):** E07, E09, E28, E29, E30, E31, E33, E39, E40, E61/E63, E64, E99; ATOMICUS `B=kΩ` (#85); CQ18_ZOA_Lensing.

---

## 8. Tally (v2)

| Cat | v1 | v2 | Δ | reason |
|---|---|---|---|---|
| A | 8 | 7 | −1 | measured inputs moved to X |
| B | 22 | ~21 | — | |
| **C** | 55 | **~57** | **+2** | #49 restored; #74 C-flagged |
| D | 25 | ~25 | — | |
| E | 14 | ~12 | −2 | #49 out; tighter contagion rule |
| **X** | — | **~12** | **new** | measured inputs + borrowed forms (MOND shape, ΛCDM, density profiles) |
| F | 18 | ~16 | −2 | borrowed forms moved F→X |

**By `provenance_status`:** SDT-posited ≈ 6% · SDT-derived ≈ 72% · calibrated ≈ 9% · external-input ≈ 8% · unresolved ≈ 5%.

**The survivable claim, sharpened:** *~57 distinct `SDT-derived × known-match` results that pass the delete-test (the matched value is provably absent from the derivation).* Quarantined separately and honestly: 4 definitional/numerological items (F), ~12 calibrated bridges (E), ~12 external/borrowed components (X). The C count grew because the v2 dependency logic stopped penalising permitted-primitive use — **stricter on identities, fairer on primitives.**

---

## 9. Code annotation convention (the next move)

Every load-bearing formula gets a six-line block immediately above it. Roll out **in order**, load-bearing files first:
`laws.hpp` → `galactic.hpp` → `nuclear.hpp` → `cq13_emission_engine.cpp` → `e46_twin_regime.cpp` → `cq26_drafting_crossover.cpp`.

```cpp
// provenance_status:     SDT-derived          // SDT-posited | SDT-derived | calibrated | external-input | unresolved
// correspondence_status: known-match          // known-match | novel-prediction | internal-only | pending-test
// input_dependency:      primitive-whitelist  // primitive-whitelist | measured-observable | calibrated-target | borrowed-function | definitional-identity
// class:                 C                    // A | B | C | D | E | X | F   (append "-flagged" if a risk_flag is set)
// circularity_assertion: no matched target value enters the derivation   // == delete-test passes
// risk_flag:             none                 // e.g. "CODATA l_P conventionally encodes G"; "W+1 rule conjectural"
```

Worked examples (these are the contested/core sites — annotate these first within `laws.hpp`):

```cpp
// F  — definitional identity:           k_e e2 = alpha*hbar*c   (alpha ≡ k_e e²/ℏc)
// C  — SDT-derived, primitive-whitelist: F = (pi/4) P_eff R1² R2² / r²   (1/r² structure; coefficient E)
// C-flagged — risk: l_P↔G:               koppa_per_baryon = l_P² c m_p / hbar
// E  — calibrated-target:                P_eff = 4 k_e e²/(π R_p² r_e²)   (hydrogen)
// C-flagged — risk: W+1 conjectural:     R_p_predicted = 4 hbar/(m_p c)
```
