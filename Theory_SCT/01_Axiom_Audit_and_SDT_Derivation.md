# SCT — Axiom Audit (Part 0) + SDT Derivability (Part 8.2)

> **Scope of this document:** the two highest-leverage parts of
> `PROMPT_structural_coding_theorem_proof.md` — a rigorous logical audit of the four
> axioms, and a determination of whether the Structural Coding Theorem (SCT) is a
> *theorem of SDT* or an independent add-on. The remaining parts (the full persistence
> and capacity proofs, the four instances, the predictions) are deferred.
> **Author:** J. C. Harvey, Melbourne. Every claim is traced; gaps are named, not hidden.

---

## 0. Executive verdict (stated up front)

1. **A1 is vacuous** (a type constraint, not a physical axiom). **A3 is load-bearing and
   nearly circular** — it *asserts* the theorem's forward direction ("persistent ⇒ code").
   **A2 (memoryless channel) is essential, not cosmetic** — the binomial failure model
   needs it. **A4 is selection bias** — it restricts the domain, it does not drive the proof.
2. **A1–A4 are NOT sufficient** to prove the core theorem. Three things are missing: a
   **repair/renewal mechanism** (without it the failure model is first-passage and the
   scaling is *polynomial*, not exponential), an explicit **encoder/decoder**, and a
   **selection principle** for the "iff".
3. **Inside SDT, the SCT becomes a genuine theorem.** The three missing pieces are exactly
   three SDT mechanisms: **Law VI (topological protection) = the code → A3 becomes a theorem**;
   **Law IV (soliton-repair) = the decoder → the renewal assumption is justified**; **Laws
   I–II (the per-tick relay) = the memoryless channel → A2 is justified.** What remains open
   is the *quantitative* bound (the exact `2^(d_min−1)` form) and the capacity computation —
   not the *structural* content. **Verdict: case (a), derivable — for the mechanism; the
   numbers are residual computed work.**

---

## 1. The axioms, and which one does the work

| # | Axiom | Role |
|---|-------|------|
| A1 | `τ ≥ 0` | **vacuous** — `τ` is a duration; durations are non-negative by definition |
| A2 | every `E` is a DMC with finite `C_E` | **essential** — the failure model assumes independence |
| A3 | every `S` with `τ ≫ 1/λ` implements a code `(n,k,d_min)` | **load-bearing, near-circular** |
| A4 | `S` observable only if `τ > t_obs` | **selection bias** — restricts domain of discourse |

The core theorem asserts **persistence ⟺ `R < C_E`** plus the bound `τ ≥ (1/λ)2^(d_min−1)`.
A3 *hands you the forward implication by fiat*: it says persistent structures are codes,
which is most of what the theorem claims to prove. **This is the audit's central finding** —
the abstract theorem assumes a large part of its own conclusion.

---

## 2. Part 0.1 — Internal consistency

**A1 ∧ A3.** A1 admits `τ = 0`; A3 constrains only `τ ≫ 1/λ`. Different regimes → no
contradiction. **But the boundary is not sharp:** "`τ ≫ 1/λ`" has no stated threshold, so
structures with `τ ∼ 1/λ` are *unclassified*. The threshold is a **hidden parameter**. A3
should read "`τ ≥ κ/λ` for an explicit `κ`," or the antecedent is vague. (Consistent, but
imprecise.)

**A2 ∧ A3.** A2 = memoryless. Real environments (bursty/correlated noise) have memory. Is
DMC a harmless simplification or essential? **Essential.** The persistence derivation uses
the *binomial* `P_fail = C(n,d_min) p^{d_min}(1−p)^{n−d_min}`, which is valid **only** under
independent component perturbations. With channel memory, corruptions correlate and the
binomial is wrong → the `2^{d_min}` scaling is not guaranteed. So A2 is a **genuine scope
limitation**: the theorem as stated is a *memoryless-channel* theorem. (Consistent; flag the
scope.)

**A3 ∧ A4.** A3 (persistent ⇒ code) ∧ A4 (observable ⇒ persistent) ⇒ observable ⇒ code. **A4
adds no mechanism** — it is a selection statement ("we only ever see persistent things").
The content is entirely in A3. A4 makes the *empirical* claim ("everything we observe is a
code") but contributes nothing to the *mathematical* bound. (Consistent; A4 is selection bias.)

---

## 3. Part 0.2 — Independence

- **A1** — independent but **vacuous/removable**: `τ ≥ 0` is true of any duration; it is a
  type constraint, not a physical assumption. Deleting it does not weaken the theorem.
- **A2** — independent (an assumption about environments); not derivable from {A1,A3,A4}.
- **A3** — independent and **the real axiom**; not derivable from {A1,A2,A4}. All the
  theorem's forward content lives here.
- **A4** — independent (a selection statement); not derivable from {A1,A2,A3}.

**Result:** the substantive axiom set is **{A2, A3}**; A1 is removable, A4 is a domain
restriction. A theorem resting essentially on A3 (which asserts its own conclusion) is, in
the abstract, **weak** — its truth is imported, not proven.

---

## 4. Part 0.3 — Sufficiency (the honest "no")

The core theorem has three claims: **(T1)** persistence ⟺ `R < C_E`; **(T2)** `τ ≥
(1/λ)2^{d_min−1}`; **(T3)** `k ≤ n·C_E`.

- **T3 follows from T1** trivially (`k/n < C_E ⇒ k < nC_E`). No new content.
- **T1-forward** (`R<C_E ⇒ persistence possible`) is Shannon *achievability* — but Shannon
  proves the *existence* of good codes, not that a *given* structure is one. The bridge needs
  an explicit **encoder/decoder**; A1–A4 do not supply it. **Missing assumption #1.**
- **T1-reverse** (`R≥C_E ⇒ no persistence`) needs the **strong converse** (Wolfowitz 1957 /
  Arimoto 1973: `P_e → 1` for `R>C`) **and** a step from "errors occur" to "`τ` is bounded."
  A1–A4 do not supply that step. **Missing assumption #2.**
- **T2** is derived in `00_…md` via `τ = 1/(λ P_fail)`. This is a **renewal** assumption:
  each Poisson event independently re-samples the failure condition, i.e. **corruption does
  not accumulate**. With no repair (`μ = 0`) corruption accumulates and the problem is a
  **first-passage** for a random walk — for which `τ` scales **polynomially** in `d_min`, not
  exponentially. So T2 as stated **requires a repair mechanism**. **Missing assumption #3.**

**Conclusion:** A1–A4 are **insufficient**. The theorem needs, at minimum, an added axiom
**A5 (repair/renewal)** and an explicit encoder/decoder, plus a selection principle to
upgrade Shannon's "good codes exist" to the SCT's "all persistent structures *are* good
codes" (the genuine empirical surplus of the "iff").

---

## 5. The `2^{d_min−1}` vs `(1/p_err)^{d_min}` discrepancy — resolved

The derivation yields `τ ≥ (1/λ)(1/p_err)^{d_min}`; the theorem states `τ ≥ (1/λ)2^{d_min−1}`.
These differ. Resolution:

**Lemma.** If the single-component flip probability satisfies `p_err ≤ ½` *and* the binomial
prefactor obeys `C(n,d_min)(1−p_err)^{n−d_min} ≤ 1`, then
`τ ≥ (1/λ)(1/p_err)^{d_min} ≥ (1/λ)2^{d_min} ≥ (1/λ)2^{d_min−1}`.

*Proof.* The prefactor condition gives `P_fail ≤ p_err^{d_min}`, hence `τ = 1/(λP_fail) ≥
(1/λ)(1/p_err)^{d_min}`. Since `p_err ≤ ½ ⇒ 1/p_err ≥ 2`, we get `(1/p_err)^{d_min} ≥
2^{d_min} ≥ 2^{d_min−1}`. ∎

So **`2^{d_min−1}` is a universal (channel-independent) lower floor**, valid whenever
`p_err ≤ ½`; the **sharp** bound is `(1/p_err)^{d_min}`. The theorem deliberately weakens to
the universal floor.

**But the honest catch (the prompt's 1.2.2):** the prefactor condition
`C(n,d_min)(1−p_err)^{n−d_min} ≤ 1` **can fail** for high-`d_min`, large-`n` codes — e.g. a
crystal as a repetition code with `d_min ∝ n`, where `C(n,d_min)` is astronomically large.
For such codes `P_fail ≤ p_err^{d_min}` is **false** and the clean exponential bound does not
follow as written. So the theorem's universality across *all* scales (crystals → particles)
is **not** established by this derivation; it holds cleanly for **small-`n`, topologically-
large-`d_min`** structures (which is exactly the SDT-particle regime — see §6).

---

## 6. Part 8.2 — Does the SCT follow from SDT? (Yes, mechanistically)

Map the SCT primitives to SDT (extending the prompt's Part 8.1 table) and check whether each
*assumed* axiom becomes a *derived* statement.

### 6.1 The code is not assumed — it is Law VI topology (A3 becomes a theorem)

SDT Law VI: persistent particles are **knots** in the spation lattice (electron = `W=1`
unknot, proton = `(2,3)` trefoil, `W=3`). PPT09 proved the trefoil is a **true** knot
(Alexander `Δ(t) ≠ 1`): it **cannot be unknotted without cutting strands**, and `W=2` is
metastable (decays). This is, verbatim, an **error-correcting code**:

- **codewords** = the topologically distinct, protected knot classes (`W = 1, 3, …`);
- **`d_min`** = the minimum number of spation-level **reconnections** (bond-switches) needed
  to carry one protected knot to a *different* valid class — the unknotting/transition
  barrier. For a topologically protected knot this is **macroscopic** in spation count → a
  large `d_min` → exponential stability.

So in SDT, **A3 is not an axiom — it is a consequence of Law VI**: *persistent ⇒
topologically protected knot ⇒ topological code*. This **dissolves the §1 circularity** — the
one thing the abstract theorem had to assume is the one thing SDT proves.

### 6.2 The decoder is not missing — it is Law IV soliton-repair (fixes the §4 gap)

The prompt's two deepest gaps were **the encoder/decoder identity** (2.2.1) and **the
renewal/repair assumption** (1.2.1). SDT supplies both, concretely:

- **Encoder** = the knot's topological configuration (the structure *is* the codeword).
- **Decoder** = **soliton-repair** (Law IV running cost): the convergent throughput budget
  continuously restores locally-deformed spations to the protected configuration — a physical
  **minimum-distance decoder** that pushes the state back to the nearest valid codeword.

Because Law IV repair runs continuously (`μ > 0`), **corruption does not accumulate**, so the
**renewal assumption is justified** and the **first-passage collapse is avoided** — the
exponential `d_min`-scaling survives. SDT thus **earns the very assumption (A5: repair)** that
§4 found the abstract theorem was missing.

### 6.3 The channel is memoryless because the relay resets each tick (justifies A2)

Laws I–II: the lattice is a **nearest-neighbour relay** that re-equalises every spation each
tick `t_P`. Perturbations from convergent-pressure fluctuations are therefore approximately
**independent across ticks** — a **discrete memoryless channel** at the spation timescale.
So **A2 is justified** in SDT (with the caveat that soliton-repair is *decoder* memory, not
*channel* memory — the channel/decoder split keeps A2 clean).

### 6.4 What SDT does *not* yet give (the honest residue)

- **The exact `2^{d_min−1}` form** still needs the first-passage/renewal computation with the
  *SDT* repair rate `μ` (from the Law-IV throughput) and corruption rate `λ p_err` (from the
  convergent-pressure coupling). SDT makes this *well-posed* (μ and λ are defined), but the
  number is not yet computed.
- **The capacity side** (`persistence ⟺ R < C_E`, T3) needs `C_E` = the spation relay
  capacity (Law I, T2) computed, and the **iff** needs a selection statement — plausibly the
  `W = 1, 3`-only selection (PPT09) *is* the physical "only near-capacity codes persist," but
  that identification is not yet proven.
- The crystal/macroscopic regime inherits the §5 prefactor problem; SDT's clean case is the
  **small-`n`, topologically-protected** particle (proton, electron, α), exactly where Part
  8.3 asks for verification.

---

## 7. Verdict

**Part 0:** the abstract SCT rests essentially on **A3**, which asserts its own forward
conclusion; A1 is vacuous, A4 is selection bias, A2 is an essential scope limitation. A1–A4
are **insufficient** — a repair axiom, an explicit decoder, and a selection principle are
required. The `2^{d_min−1}` bound is a valid universal *floor* for `p_err ≤ ½` **only** when
the binomial prefactor is controlled (fails for high-`d_min` macroscopic codes).

**Part 8.2:** **case (a) — the SCT is derivable from SDT, mechanistically.** Law VI turns the
load-bearing axiom A3 into a *theorem* (topological protection = the code), Law IV supplies
the missing decoder/repair (justifying the renewal assumption the abstract proof needs), and
Laws I–II justify the memoryless channel A2. **The abstract theorem's three weaknesses are
three SDT mechanisms.** The residual open work is *quantitative* (the exact bound from `μ, λ`;
the capacity `C_E`; proving the `W=1,3` selection is the capacity cutoff), not *structural*.

**One-line statement of the result:** *The Structural Coding Theorem is not an independent
theorem and not in tension with SDT — it is Law VI (the code) + Law IV (the decoder) + Laws
I–II (the channel), wearing Shannon's vocabulary. What SDT still owes is the arithmetic, not
the architecture.*

---

## 8. The augmented axiom set — A5, A6, A7 (stated, with SDT realizations)

§4 found A1–A4 insufficient and *named* three missing pieces but did not state them as axioms.
Here they are formally. The point of the table is the last column: **in SDT each is a theorem,
not a free assumption.**

### A5 — Repair (renewal)
**Statement.** Every persistent structure couples to a restoring process that returns each
corrupted component to its valid state at per-component rate `μ` obeying the **renewal
condition** `μ ≳ λ·p_err`, so corruption does not accumulate.
**Gap it closes.** §4 / prompt 1.2.1 — without repair the failure process is *first-passage*
(corruption accumulates) and `τ` scales *polynomially* in `d_min`; A5 is the assumption silently
used in writing `τ = 1/(λ P_fail)`.
**SDT realization (theorem).** **Law IV soliton-repair**: the convergent throughput continuously
restores deformed spations, with `μ ~` relay rate `≫ λ p_err`, so the renewal condition holds
automatically. ⇒ *A5 follows from Law IV.*

### A6 — Decodability (the codeword/decoder identity)
**Statement.** A structure's configuration **is** its codeword (encoder), and the A5 restoring
process is a **minimum-distance decoder** — it maps any state within Hamming radius
`⌊(d_min−1)/2⌋` of a valid configuration back to it.
**Gap it closes.** §4 / prompt 2.2.1 — A1–A4 never identify the encoder/decoder, so A3's
"implements a code" is underspecified (it asserts *parameters*, not a *decoding dynamics*).
**SDT realization (theorem).** Encoder = the **knot topology** (Law VI); decoder = **topological
protection** (a sub-`d_min` perturbation cannot change the knot class, so it is auto-corrected),
backed by Law IV repair. ⇒ *A6 follows from Laws VI + IV.*

### A7 — Selection (the persistence-maximization surplus)
**Statement.** Among configurations admissible in `E`, the *observed* ones **maximize
persistence** — they sit at locally-maximal `d_min` subject to `R < C_E`.
**Gap it closes.** §4 / prompt 2.2.3 — Shannon gives "good codes *exist*"; the SCT's "iff" needs
"the persistent structure *is* the good code," which is a selection/optimization principle, not a
mathematical deduction.
**SDT realization (theorem, with one caveat).** The dynamical selection of **topologically
protected windings** — only `W=1,3` (high-`d_min`) persist (PPT09); that *is* the
`d_min`-maximization. **Caveat (doc 02):** the `R < C_E` clause is vacuously satisfied for
particles (`R ~ 10⁻⁶⁰`), so at the particle scale A7 reduces to its `d_min`-maximization clause;
the capacity clause only bites for macroscopic structures. ⇒ *A7 follows from the PPT09 selection
(its `d_min` clause); its capacity clause is inert below the macroscopic scale.*

### The closure
| Axiom | Role | In SDT it is… |
|---|---|---|
| A1 | `τ ≥ 0` | vacuous (type constraint) |
| A2 | memoryless channel | **Laws I–II** (per-tick relay) |
| A3 | persistent ⇒ code | **Law VI** (topological protection) — a *theorem* |
| A4 | observability selection | selection bias (domain restriction) |
| **A5** | repair / renewal | **Law IV** (soliton-repair) |
| **A6** | encoder = config, decoder = repair | **Laws VI + IV** |
| **A7** | persistence-maximization | **PPT09** protected-winding selection |

So the augmented theorem `{A1–A7}` is **not seven free assumptions**: within SDT it is
`{A2 = Laws I–II, A3+A6 = Law VI, A5 = Law IV, A7 = PPT09}`, with A1 vacuous and A4 selection
bias — **the Six Laws wearing Shannon's vocabulary.** This is the precise sense in which Part 8.2
answers "(a) derivable": the three axioms the *abstract* theorem must add are exactly three SDT
mechanisms.

---

### Connection to tonight's results

This frames the night's geometric findings informationally: the **proton's `(2,3)` trefoil**
is the canonical topological codeword (`d_min` = its unknotting barrier → `τ` effectively
infinite); the **nuclear magic numbers** (the open end of NP17) are **closed-shell, maximal-
`d_min` codewords** — which is *why* they are extra-stable; the **`W=1,3`-only discreteness**
is the *codebook*; and the **near-capacity selection** (Prediction 3) is why the proton's
geometry is fixed (not tuned) — it sits at the persistence-optimal configuration. The
trefoil, the magic numbers, the discreteness, and the fixed geometry are one phenomenon:
*persistent structure = optimal topological code.*
