# SDT Theory Compiler — Technical Audit

**To:** The Architect (James Tyndall)
**Subject:** Trustworthiness of the Theory Compiler and the `report.md` it produced
**Scope:** `Compiler/` (parser → symbols → kernel → dimensions → derivation graph → adversarial → export), with cross-checks against `Engine/include/sdt/laws.hpp` and `Theory/`.
**Method:** Full read of all 17 compiler headers + `main.cpp`; one auditor per module; every finding adversarially re-verified against the source (one verifier **compiled and ran** the tool against `Theory/`). 76 verdicts: 65 confirmed, 9 partial, 1 refuted, 1 reclassified.

---

## 1. Bottom line

The compiler is an impressively complete *scaffold* — the stage pipeline, the dimension algebra, the 28D manifold model, the SHA-256 kernel, and a 10-point adversarial design are all real and well-organised. But its headline verdict is **not yet trustworthy**:

- **"COMPILED / SUCCEEDED" means only "no `FATAL`-severity error was emitted."** It asserts *nothing* about derivation, validation, or coverage — and in the current build every `FATAL` path is effectively unreachable. The green badge certifies that the parser ran, not that SDT was validated.
- **Almost everything alarming in `report.md` is a tooling defect, not a theory defect.** The SDT equations the tool marks ❌ — the universal force law `F = (π/4) P_eff R₁²R₂²/r²`, the mass law `m = Φ V_disp/(3 ℓ_P³ c²)`, `R_p = 4ℏ/(m_p c)` — are **dimensionally correct** (verified by hand and against `laws.hpp`). The tool is manufacturing evidence *against* the physics it is meant to certify.
- **Zero confirmed theory errors** were found by this audit. Every "the theory looks broken" signal in `report.md` traces back to the compiler.

The single most important message: **do not act on `report.md` as a verdict on SDT.** Fix the tool first; right now it is a confident liar in both directions — it green-lights a degenerate run and red-flags correct equations.

---

## 2. How every number in `report.md` actually arises (root-cause trace)

| Symptom in `report.md` | Confirmed cause | Verdict |
|---|---|---|
| ❌ on `F`-law, mass-law, `R_p`, `W_eff` (RHS shown as `1`) | Expression parser has **no implicit multiplication**: `(pi/4) P_eff`, `Phi V_disp`, `m_p c`, `4hbar` all truncate at the first juxtaposition; only the **first `=`** is read, so `= 0.84124` tails are dropped. The physics is correct. | PARSER-1/2/3 — **critical**, confirmed |
| `Passes: 0` while ~50 rows show ✅ | **Metric disconnect.** `report.passes` is fed *only* by adversarial `check_2`, which re-validates derivation-step `output_equation`s — and those are **prose headings** (no `=`), so they resolve to UNRESOLVED, never PASS. The ~50 real dimensional passes computed in Stage 3 are never counted into the summary. | PIPE-1 / EXPORT-3 / COH-4 — **high**, confirmed |
| `Derivation steps: 0` | **Pure reporting bug:** `main.cpp` builds the graph but never copies it into the exported result (`result.derivation_steps` left default). At runtime the graph actually holds **102 nodes (10 axioms + 33 defs + 59 steps)** — the report just drops them. | DERIV-2 / EXPORT-2 / BRIDGE-6 — **high**, confirmed (runtime-verified) |
| Symbol table: ~93 blank "locked" rows + junk (`varepsilon`, `Nepsilon`, `→`, `mc`, `pc`, `ll`, `nablaW`) | Every equation token is auto-registered as a blank `UNRESOLVED` symbol; `clean_latex` strips backslashes and **glues adjacent macros** (`N\varepsilon` → `Nepsilon`); then `lock_all()` flips *everything* to `LOCKED`. | SYMREG-2/5/1 — **high**, confirmed |
| Core inputs `c, ℏ, α, m_e, m_p` shown undefined; `G, M` present | The `measured` derivation basis is **never seeded** into the registry; constants appear only as blank tokens harvested from equations. `G`/`M` enter only via the compiler's own prohibition setup, **not** as inputs in `laws.hpp` (prohibition compliance is OK). | SYMREG-3 / LAWS-10 — **high/info**, confirmed |
| State28D table: all 28 aspects `—` | The **exporter** matches raw aspect field-names (`xi_0`, `T_1`, `eps_b`) against parsed symbols by exact equality → 0 matches. The console path uses `resolve_28d_coverage()` (a real symbol→aspect map) and finds **~15/28**. Two divergent code paths; the durable artifact shows the wrong one. | EXPORT-1 / MANIFOLD-1 / COH-7 — **high**, confirmed |
| `Failures: 1` → `SYMBOL_DRIFT (W)` | **False positive.** The metaphor heuristic substring-matches `"like"` inside `"unlike higher genus"`. The tool's only emitted finding is noise; it also prints no line number in `report.md`. | DRIFT-1 / DRIFT-7 — **high/low**, confirmed |

---

## 3. Systemic themes (the real problems behind the symptoms)

**A. The success contract is "no fatal," not "validated."**
`Status = success ? "COMPILED" : "FAILED"` and `success = !report.has_fatal()`. A run with 0 verified derivations, 0 counted passes, ~93 junk symbols, false dimension-fails, and 0/28 reported coverage still prints **COMPILATION SUCCEEDED** and exits 0. *(COH-1, PIPELINE-1, ADV-3, EXPORT-5 — critical/high)*

**B. The expression parser is too weak for physics notation — and it poisons everything downstream.**
No juxtaposition (`expression.hpp:432-444`), only the first `=` (`:380-391`), no unit suffixes (`0.84124 fm` → `fm` becomes a stray symbol), and prose with `=>`/`,` is accepted as an equation. This one component produces the bulk of the ❌ and ⏳ rows and silently feeds malformed tokens into the symbol table and dimension engine. *(PARSER-1/2/3, UNIT-1, EXTRACT-1)*

**C. The derivation graph has nodes but no edges, and its steps carry prose instead of equations.**
`build_derivation_graph` never populates `DerivationStep.dependencies`, so the graph is **edgeless** — `find_circular_derivations`, `trace_to_axioms`, and `is_reproducible` are all vacuously true (`trace_to_axioms` even treats every node as its own root). Steps' `output_equation` is the normalised *prose heading*, not a parsed equation, so the dimensional check records 0 passes. All steps are stamped `PARSED`, so 4 of 10 adversarial checks (analogy-as-proof, empirical-smuggling, reproducibility, claim-exceeds-level) **can never fire**. The component meant to prove "everything is derived from axioms" verifies nothing. *(DERIV-1 critical, DERIV-4/5/6, COH-2, BRIDGE-1)*

**D. Two metrics, two code paths, contradictory artifacts.**
Passes (0 vs ~50), manifold (0/28 in `report.md` vs ~15/28 on console), derivation steps (0 vs 59 at runtime). The console and the durable report disagree with each other on the same compile. *(COH-4, EXPORT-1/3, MANIFOLD-1)*

**E. "Locking" is meaningless and actively masks a check.**
`lock_all()` locks every entry — including blank `UNRESOLVED` placeholders — and runs *before* the adversarial pass, so `check_1` (undefined-symbol detection) can never fire. Separately, the kernel locks **zero primitives**: `build_from` filters for `LOCKED` symbols but runs in Stage 2 *before* `lock_all()`, so `locked_primitives` is empty (confirmed in `kernel.json`). The kernel hash therefore certifies prose-polluted `locked_definitions`/`locked_equations` over an empty primitive set. *(SYMREG-1 partial, ADV-7, kernel-ordering)*

**F. The "adversarial" pass is structural lint, not falsification.**
`examine()` does no numerical evaluation, no prediction-vs-measurement, no falsification-condition test. Its prohibition/forbidden-term enforcement is substring-based with over-broad negation suppression (a forbidden term in any sentence containing a negation word would be silently dropped), and `detect_symbol_drift` can only fire on three literal phrases. The file's docstring ("runs every derivation through hostile checks") overstates what it does. *(ADV-4, DRIFT-2/3/5/6)*

**G. LaTeX/symbol hygiene is lossy.**
Macros glue (`\pi\alpha\hbar` → `pialphahbar`), backslashes are stripped into bare words (`arrow`, `nabla`), subscripts mangle (`\Pi_{ij}` → `Pi`, `ij`), and the alias-dedup machinery is dead code, so `epsilon`/`varepsilon`/`epsilon_d` proliferate as distinct symbols. *(SYMREG-4/5, EXTRACT-1)*

**H. Engine-side labeling honesty (separate from the tool — for the certification policy).**
These do not affect computed numbers but matter for the "zero free parameters / derive-before-validate" contract:
- `R_charge` is a **hardcoded truncated literal** (`1.5396e-15`) rather than `√(R_p·r_e)`, making the "exact, no free parameters" Coulomb identity ~0.05% wrong as written. *(LAWS-1, high)*
- `P_eff` is "from hydrogen calibration" yet feeds the *universal* force law — a `CALIBRATED` constant presented as derived. *(LAWS-2, high)*
- Several "verifications" are tautologies/definitions, not tests: `P_cf_e == P_conv/3` (guaranteed by the `V_disp` definition), `k_e e² = αℏc` and `g_electron = α` (rearrangements of α's definition), and `koppa_per_baryon`'s "No G" claim is circular (G enters through CODATA `ℓ_P`). `R_CMB = 9.527e26` is hardcoded (effectively H₀-derived). *(LAWS-3/4, COSMO-1)*
- Dead headers `neutrino.hpp`/`magnetosphere.hpp` are never `#include`d; `Benchmarks/neutrino_investigation.cpp` **re-declares CODATA constants** instead of including `laws.hpp` (single-source violation); `magnetosphere.hpp` has a 10× comment error and hardcodes `mu_0` seven times. *(DEAD-1/2, MAG-1/2)*

---

## 4. Tally

**By verified severity (deduplicating findings that name the same root cause across modules):**

| Severity | Distinct issues | Examples |
|---|---|---|
| Critical | 3 | Parser juxtaposition (PARSER-1/2); success contract (PIPELINE-1/COH-1); edgeless/prose-only derivation graph (DERIV-1/COH-2) |
| High | ~9 | Pass-metric disconnect; 28D exporter; symbol auto-lock & derivation basis not seeded; level-gated checks dead; missing-bridge inert; `R_charge`/`P_eff` labeling |
| Medium | ~16 | prose-as-equation extraction; `clean_latex` gluing; severity mis-routing; no JSON/MD cell escaping; build story |
| Low / Info | ~12 | dead headers, stale comments, golden-ratio obfuscation, CLI arg handling |

**By kind:** overwhelmingly **tooling-bug**; a handful of **design-limitation** (single global symbol scope, structural-lint-only examiner); exactly **one "theory-error" that was reclassified to a documentation typo** (MAG-1); the remainder are observations on `laws.hpp` labeling. **No confirmed errors in the SDT physics itself.**

**Verification caveats the verifiers caught (so you don't over-read this audit either):**
- The "graph is empty" framing that several auditors reached is **wrong** — the runtime graph has 102 nodes/59 steps (BRIDGE-5, refuted; DERIV-3/PIPELINE-4, partial). The defects are *edgeless graph* + *prose-as-output_equation* + *the `main.cpp` reporting drop*, not an empty graph.
- `propagate_from_equations` is **not** entirely dead (PROP-1, partial): it fires on trivial single-unknown cases via the SYMBOL path; only its MUL/POW/SQRT branches are unreachable.
- The kernel hash is **not** polluted with the symbol-table junk (SYMREG-1, partial): `locked_primitives` is empty, so the hash covers prose-polluted definitions/equations only.

---

## 5. The five highest-leverage fixes (ordered by payoff)

1. **Harden the expression parser** — add implicit multiplication (juxtaposition → `MUL`), split leading numeric coefficients (`4hbar` → `4 * hbar`), parse full `A = B = C` chains, add a unit-suffix lexer (`fm`, `eV`, SI prefixes), and reject prose containing `=>`/`,`/multiple `=` as non-equations. Add regression tests asserting the `F`-law and mass-law RHS resolve to force/mass. **Clears the majority of ❌ and ⏳ and makes the dimension column trustworthy.** *(PARSER-1/2/3, UNIT-1, EXTRACT-1)*
2. **Unify the dimensional metric** — feed the Stage-3 `eq_records_` into `report.passes`/`failures` (or have `check_2` read them), and drive both the equation table and the summary "Passes" from one source. **Kills the "0 passes vs ~50 ✅" contradiction.** *(PIPE-1, EXPORT-3, COH-4)*
3. **Make the success contract honest** — gate `COMPILED` on positive evidence (verified steps > 0, a minimum pass ratio, honest coverage, no non-fatal failures), add `PARTIAL`/`INCOMPLETE` states and matching exit codes, print a "what COMPILED does and doesn't mean" caveat block, and set `result.derivation_steps` (or route `main.cpp` through `compile()`). **Stops a degenerate run from reading green.** *(COH-1, PIPELINE-1, DERIV-2)*
4. **Make the derivation graph real** — set each step's `output_equation` to a *parsed* `$...$` equation (not the prose heading), populate `dependencies` (edges) from theorem references / symbol provenance, and promote `validation_status` as evidence accrues. **Activates cycle/trace/reproducibility/bridge checks and the 4 level-gated checks — i.e. the actual adversarial value.** *(DERIV-1/4, COH-2, BRIDGE-1)*
5. **Restore symbol & kernel integrity** — don't auto-lock `UNRESOLVED` placeholders; seed the `measured` derivation basis as defined, dimensioned primitives; run `check_1` before locking; build the kernel after locking (so `locked_primitives` is non-empty); fix the exporter's 28D path to use `resolve_28d_coverage`; and add separators/subscript handling to `clean_latex`. **Cleans the symbol table, restores undefined-symbol detection, and gives the kernel hash real meaning.** *(SYMREG-1/2/3/5, ADV-7, EXPORT-1)*

---

## 6. What "COMPILED" *should* mean

A credible green verdict should require all of:
1. **Every kernel equation parsed and dimensionally resolved** — no silent ⏳ that is actually a parser limitation, and no ❌ on equations that are in fact consistent.
2. **A connected derivation graph** — each claim traces to one or more axioms/definitions, with no dangling roots and no cycles, and those edges are checked.
3. **Dependency discipline** — seed, bridge, seat, measured-boundary and comparison roles are represented explicitly, and every symbol used in a derivation is dependency-traced or itself derived; forbidden body-source aliases are registered so derivational use is caught.
4. **The adversarial checks actually executed** — not gated out by every step being `PARSED`; the report states which checks ran and what they covered.
5. **Single-source metrics** — one coverage number, one pass count, console and `report.md` in agreement.

Until then, the badge should read, e.g.:
`COMPILED (structural parse only) — no fatal errors; N equations unresolved (parser-limited), M false dimension-fails pending parser fix, derivation graph unverified.`

That sentence is the honest description of the current `report.md`.

---

*Prepared as a code-trust audit. The job here was the tool's reliability, not adjudicating the physics — and the clearest finding is that the two must not be conflated: the compiler currently does neither job it advertises, but it does not contain evidence against SDT. Detailed per-finding IDs (PARSER-*, DERIV-*, ADV-*, SYMREG-*, LAWS-*, COH-*, …) and their file:line locations are available on request.*
