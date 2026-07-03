# NP18 — Be7BEC Flux Resonator: the rate-scaling fork

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Does the electron-capture (EC) rate of Be-7 scale with the **weak coupling G_F** (the W boson's fingerprint), or with the **coherence/gaplessness** of the electron substrate it captures from? Nobody has measured Be-7 EC against a Bose–Einstein condensate target — a gapless, single-wavefunction electron environment the standard cross-section was never computed for.
2. **Why does it matter?** — This is the **headline experiment** of the 9-investigation flux-resonator set. If the rate climbs with coherence faster than G_F allows, the W-as-object in **this one process** was a re-description of a medium-grounding event (PPT10: a neutrino is straight-running electron-stuff; it can ground into a wiggling electron in the one substrate with no grain). It does **not** touch g−2, the Lamb shift, or Casimir — the W stays a perfectly good propagator everywhere else. This is a **wedge**, not a wrecking ball.
3. **How will we find out?** — Four gated phases in §④: incoherent baseline rate → coherent-enhanced rate (N vs N²) → divergence population N* against the SQUID femtotesla floor → verdict bucket (tabletop / building / reactor-next-door). Native grammar selection rule first (Be-7 = node (3,−1) underflow), then the rate fork.
4. **What would prove us wrong?** — §⑧ falsifiers with numeric triggers: rate tracks G_F not coherence (KILL the wedge); no magnetisation step above fT at achievable N (PIVOT or OPEN); coherence cannot span the BEC (DEFER to CEνNS scale).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. Executive Summary

The textbook "neutrinos barely interact" cross-section is computed for an **incoherent** target: independent nucleons and electrons with gaps between them. A **coherent, gapless Bose–Einstein condensate** is an unexamined target regime. **NP18 asks: when Be-7 captures an electron from a Li/Be BEC instead of from an ordinary atom, does the rate scale with G_F (standard) or with the condensate's coherence (SDT)?** Be-7 is the clean probe because it decays **only** by EC to a single known neutrino line (0.862 MeV, 90 %; 0.384 MeV, 10 %), and its rate is already known to depend on the electron environment (ionisation gating; bound-state beta-decay precedents). **We expect** to specify, with pre-committed numeric gates, the condensate population N\* at which the N-vs-N² predictions diverge above the SQUID femtotesla floor, and to classify the result as tabletop, building-sized, or reactor-scale. A rate that climbs with coherence faster than G_F permits would localise the "W-as-object" to a removable re-description in this one process — without claiming virtual particles are fictions anywhere else.

## 2. Physical Context

**The device — each link is a separately documented real effect (we say so explicitly):**

1. **Clean source.** Be-7 (Z=4, A=7) decays **only** by electron capture: Be-7 + e⁻ → Li-7 + νₑ. One channel, one well-known neutrino line. No β⁺ competition.
2. **Reversibility (resonant inverse-EC).** The time-reverse Li-7 + νₑ → Be-7 + e⁻ resonates at the **same** line energy. A monochromatic νₑ flux at 0.862 MeV is the resonant drive.
3. **Ionisation gating (PUBLISHED physics).** A **fully stripped** Be-7 nucleus **cannot** EC — there is no K electron to capture — so it sits as a silent trap until an electron is supplied. Be-7's EC rate is measurably electron-environment-dependent. Bound-state beta-decay shows the same lever at extreme range: Re-187 ≈ 41 Gyr neutral vs ≈ 33 yr fully ionised; Dy-163 is stable neutral but **decays** when fully ionised. The electron environment is a real, large rate knob.
4. **Condensation → coherence.** N atoms occupy one macroscopic wavefunction. Coherent absorption from such a target can scale as **N²** (collective), not **N** (independent).
5. **Self-manufacturing read-out.** Product Li-7 arrives with a loose 2s valence electron — a **shallow seat = flux-active** (NP19/NP20). Each capture writes itself as a collective magnetisation step, readable by a SQUID at the ~fT floor. The detector is the chemistry of the product, not an external counter.

**Key variables.** N (condensate atom number, dimensionless); n (number density, m⁻³); λ_ν (neutrino de Broglie wavelength at 0.862 MeV); σ_inc (incoherent inverse-EC cross-section, m²); R_inc = n_targets σ_inc Φ_ν (incoherent rate, s⁻¹); R_coh (coherent rate, with the N² scaling factor); N\* (population where R_coh and R_inc diverge measurably); B_step (per-capture magnetisation increment, T) vs B_floor ≈ 10⁻¹⁵ T (SQUID). **Why it matters:** it is the experimental spine of PPT10 (neutrino = straight light grounded into an electron) and FLM11 (a BEC is *uncommitted cloth* — not pre-committed to any measurement ruler — so it is the one substrate where a straight thread can be grounded into a wiggling electron).

## 3. Theoretical Framework

**Permitted inputs only** (`sdt::laws::measured` whitelist): {ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p} plus measured observables in their measured units (the Be-7 line, the n–p gap 1.293 MeV, CEνNS cross-sections, half-lives, BEC parameters). **No G, no M(kg), no GM. Prohibited as inputs:** wavefunctions-as-primitives, fields-as-primitives, quarks/gluons, virtual particles as real objects, dark matter/energy, ΛCDM. The W boson in β/EC is, by the standard formalism's own statement, a **propagator** — a bookkeeping object, never on-shell here. We do not import the standard-model **story**; we use its **numbers** as anchors.

**Grammar-forced substrate (the native selection rule).** Run the alpha grammar from `nuclear.hpp` (`alpha_grammar(Z,A)`: n_d = 3Z−A−2, n_t = A−2Z):

- **Be-7** (Z=4, A=7): n_d = 3, n_t = **−1** → node **(n_d, n_t) = (3, −1)**. With n_t < 0 this is **below the constructable lattice** — a proton-rich **underflow**, i.e. **EC-cocked**.
- **Li-7** (Z=3, A=7): n_d = 0, n_t = 1 → node **(0, 1)** — clean, on-lattice.
- The EC step carries (3, −1) → (0, 1): the grammar vector **(Δn_d, Δn_t) = (−3, +2)** lands exactly on Li-7.

**Falsifiable SELECTION RULE (state it as such):** *every good resonant-capture substrate must sit in the n_t < 0 underflow, reachable to the on-lattice wedge by a single EC grammar vector.* This is a native prediction — it selects candidate isotopes with no free parameters.

**The SDT grounding claim (PPT10).** A neutrino is straight-running electron-stuff: an open winding (W→0, `sdt::neutrino`) that *propagates with the relay, not against it*. In an ordinary grainy target it cannot ground. In a gapless BEC (FLM11: uncommitted cloth) the straight thread can ground into a **wiggling electron** — νₑ → e⁻ by grounding, **no mediator**. The honest discriminator is whether that grounding rate follows coherence (SDT) or G_F (standard).

## 4. Investigation Strategy

> Be excessive. Four phases, each with a pre-committed numeric threshold, an explicit failure trigger, and a hard gate. Phase N+1 is forbidden until Phase N is PASS-GATE or an explicit DEFER/OPEN is logged. All constants from `laws.hpp`/`nuclear.hpp`/`neutrino.hpp` — no local namespaces. **Out of scope for the whole investigation:** building the apparatus, sourcing a monochromatic 0.862 MeV νₑ beam, and any claim about g−2 / Lamb / Casimir.

### Phase 0 — Grammar selection rule + engine sanity (0.5 day)
- **Goal:** confirm the native selection rule numerically before any rate work.
- **Method:** call `alpha_grammar(4,7)` and `alpha_grammar(3,7)`; assert Be-7 → (n_d,n_t)=(3,−1) with n_t<0 (underflow), Li-7 → (0,1) on-lattice, and that the single EC vector (Δn_d,Δn_t)=(−3,+2) maps one to the other. Print the Be-7 line (0.862/0.384 MeV) and the 478 keV figure **labelled as the Li-7\* de-excitation GAMMA, not a neutrino line**.
- **Pre-committed metric:** all three grammar assertions exact (integer match), labels correct.
- **Failure trigger:** any grammar mismatch, or 478 keV mislabelled as a neutrino line → **STOP**, fix engine refs.
- **Gate:** no rate phase until the (3,−1) underflow check passes.
- **Out of scope:** scanning the whole chart for other underflow isotopes (record as a downstream note only).

### Phase 1 — Incoherent baseline capture rate (1–2 days)
- **Goal:** R_inc, the standard-target inverse-EC capture rate, from the resonant cross-section.
- **Method:** σ_inc from the resonant inverse-EC line (Breit–Wigner peak at 0.862 MeV; width from the EC partial rate). R_inc = n_e σ_inc Φ_ν for a given νₑ flux Φ_ν and electron density n_e of an ordinary (un-condensed) Li/Be target. Tag every number `MEASURED-INPUT` / `DERIVED` / `COMPUTED`. **No N² factor in this phase.**
- **Pre-committed metric:** R_inc reproduces a hand check of σ_inc Φ_ν n_e to within a factor 2 (order-of-magnitude sanity, this is a cross-section the literature bounds).
- **Failure trigger:** R_inc off by >10× from the resonant-cross-section sanity estimate → re-derive σ_inc (likely a width or flux-normalisation error), document ADJ-###.
- **Gate:** Phase 2 forbidden until R_inc is stable and unit-checked (s⁻¹).
- **Out of scope:** any coherence factor; this is the **G_F-only** prediction.

### Phase 2 — Coherent-enhanced rate (N vs N²) (2 days)
- **Goal:** R_coh(N) for a condensate target, with the collective enhancement made explicit.
- **Method:** model the BEC as N atoms in one wavefunction; coherent inverse-EC absorption scales the amplitude ∝ N, hence the rate ∝ **N²** *only while the neutrino wavelength λ_ν spans the coherent volume*. Compute λ_ν at 0.862 MeV (λ_ν = ℏc/E_ν order) and compare to the BEC linear size L(N,n). Define the **coherence span ratio** ρ_coh = λ_ν / L. R_coh = R_inc · f(ρ_coh) · N, where f → N for ρ_coh ≥ 1 (full span) and f → 1 (incoherent) for ρ_coh ≪ 1. State the interpolation explicitly; do not hide the crossover.
- **Pre-committed metric:** for ρ_coh ≥ 1, R_coh/R_inc = N to <1 %; the model must **reduce exactly** to Phase-1 R_inc when N=1 or ρ_coh→0 (limit check).
- **Failure trigger:** the model does not collapse to R_inc in the incoherent limit → the enhancement law is mis-built; **PIVOT** to an explicit per-atom amplitude sum, document ADJ-###.
- **Gate:** Phase 3 forbidden until both limits (N=1 and ρ_coh→0) recover Phase 1 exactly.
- **Out of scope:** asserting ρ_coh ≥ 1 is achievable — that is Phase 3's honest boundary.

### Phase 3 — Divergence population N\* vs the SQUID floor (2 days)
- **Goal:** the condensate population/density N\* at which R_coh and R_inc diverge **measurably above the fT floor**, and the verdict bucket.
- **Method:** per capture, the product Li-7 contributes one 2s flux quantum (NP19/NP20 shallow-seat flux per atom) → a magnetisation increment B_step. The collective signal over an integration time is B_sig(N) ∝ (R_coh−R_inc)·B_step·τ. Solve B_sig(N\*) = B_floor (≈10⁻¹⁵ T). Report N\* and the corresponding density n\*; check ρ_coh(N\*) ≥ 1 self-consistently. **Verdict bucket:** N\* and n\* achievable on a **tabletop** BEC (10⁵–10⁷ atoms), a **building-sized** rig, or only **next to a reactor** (flux-limited).
- **Pre-committed metric:** a finite N\* exists with B_sig(N\*) ≥ 10×B_floor **and** ρ_coh(N\*) ≥ 1 simultaneously; the verdict bucket is reported with the numbers that put it there.
- **Failure trigger:** no N\* satisfies both signal and span at any achievable density → the BEC enhancement is unreachable; **PIVOT** N/density/τ; if still unreachable → **DEFER** to CEνNS scale (see §⑧ honest boundary) or **OPEN**.
- **Gate:** verdict line not written until the signal-AND-span condition is checked together (not separately).
- **Out of scope:** the stripped-Be-7 control — that is the §10.2 clean fork below.

### Phase 4 — Stripped-Be-7 clean fork (1 day) — the discriminator's discriminator
- **Goal:** separate "did the neutrino BECOME an electron" from "did it induce a reshuffle."
- **Method:** with **valence electrons removed** (fully stripped Be-7), the only electrons present are the deep, fast K pair. Any flux on capture is then either (a) K-shell excitation/reshuffle, or (b) a **brand-new electron manufactured from the neutrino** (PPT10 grounding). Compute the predicted magnetisation signature of each: K-reshuffle gives a deep-seat (fast, low-flux) signature; manufactured electron arrives as a **shallow 2s flux** signature identical to the neutral-atom read-out. The two are distinguishable in the B_step spectrum.
- **Pre-committed metric:** the two signatures differ by a pre-stated factor in B_step (deep-K vs shallow-2s flux ratio from NP19/NP20) ≥ 3× — enough to call the fork.
- **Failure trigger:** signatures indistinguishable (<3×) → the stripped control cannot fork; mark that sub-claim **OPEN**.
- **Gate:** none downstream; this phase feeds the §⑧ KILL/OPEN logic.
- **Out of scope:** running the bare-nucleus trap dynamics; specify the signature, not the trap.

**The discriminator, compressed (this is the spine):** measure the Be-7 capture rate **against coherence/gaplessness, not against G_F**. If R tracks G_F → standard story holds (KILL the wedge). If R climbs with coherence faster than G_F allows → the mediator was a re-description of a medium-grounding event **in this process** (the wedge bites). Phase 4 says *which* electron did the work.

## 5. Success Criteria

Use canonical labels; tag every printed number (§5 protocol). **Dual verdict required:** prompt completion (A–F) **and** physics class.

- ✅ **PASS (Class A: Derived/NATIVE):** selection rule (3,−1)→(0,1) exact; R_inc and R_coh both derived with **zero fitted parameters**; a finite N\* with signal ≥10×fT **and** ρ_coh≥1; verdict bucket stated. The N-vs-N² fork is sharp and the stripped control distinguishes manufacture from reshuffle.
- ✅ **QUALIFIED (Class C: Convergence):** fork specified and N\* found, but with 1 documented `CALIBRATED(1)` (e.g. the B_step flux-per-atom absolute, pending NP19/NP20). Coherence span established only by interpolation, not first-principles.
- ⚠️ **PENDING (Class D: Computed/OPEN):** R_inc and R_coh laws built and limit-checked, but N\* unreachable at achievable density, or ρ_coh≥1 not demonstrable → ship the rate table and DEFER span to CEνNS scale.
- ❌ **FAIL (Class F/KILLED):** the rate provably tracks G_F with no coherence channel, **or** the construction cannot be built without importing a wavefunction/field-as-primitive. The wedge is dead; record it with numbers.

**CALIBRATED budget: ≤1** (the read-out flux-per-atom absolute, only if NP19/NP20 has not landed it). Everything else DERIVED/COMPUTED.

## 6. Outputs

1. **`np18_rate_fork.cpp`** (or `.py`) — standalone tool printing: (a) the incoherent-vs-coherent **rate table** R_inc, R_coh(N) across N; (b) the **divergence population N\*** and density n\* with the fT-floor crossing; (c) the **Be-7 = (3,−1) underflow check** and the EC vector (−3,+2)→Li-7; (d) the verdict bucket (tabletop / building / reactor). Every line carries a ledger tag (`MEASURED-INPUT`/`DERIVED`/`COMPUTED`/`CALIBRATED(n)`/`OBSERVED-TARGET`/`PENDING`).
2. **`np18_results.txt`** — captured stdout of the tool.
3. **`NP18_DERIVATION.md`** — the resonant inverse-EC σ, the N-vs-N² enhancement law with its two limit checks, and the λ_ν-span condition; DERIVED vs ASSUMED flagged line by line.
4. **`NP18_OBSERVING_PROPOSAL.md`** — the downstream observing proposal: target N\*, density, νₑ flux, integration time, SQUID floor, and the stripped-Be-7 control run.
5. **`RUN_LOG.md`** — **mandatory**: Pre-Run Commitment Block, ADJ-### entries, per-phase gates and decisions.
6. **`NP18_VERDICT.md`** — dual verdict (prompt A–F + physics class) with the §⑧ falsification table filled.

## 7. Dependencies & References

**Upstream (required):**
- **PPT10** — neutrino as straight-running light/electron-stuff; the grounding mechanism (νₑ→e⁻, no mediator).
- **NP19 / NP20** — mass-defect-as-resistance and neutron-from-one-seat: the **shallow seat = flux** read-out and the B_step flux-per-atom.
- **`nuclear.hpp`** — `alpha_grammar(Z,A)` and the underflow/wedge logic (the selection rule).
- **`neutrino.hpp`** — open-winding (W→0) topology, wake radius, propagates-with-relay.

**Downstream (blocked / fed):**
- **`NP18_OBSERVING_PROPOSAL.md`** — the tabletop/building/reactor experiment design depends on N\* from Phase 3.
- **PPT11** (neutrino oscillation) and **SAR05** (provenance-after-iron) consume the grounding verdict.

**Related (read in parallel):** **FLM11** (tape-measure / ruler-count: the BEC as *uncommitted cloth*), **APS06** (emission ladder), **CM05** (BEC as macroscopic phase-locked wake condensate — the substrate model). Siblings in the 9-set: NP19, NP20, NP21, PPT10, PPT11, FLM11, APS06, SAR05.

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL (decision) |
|------|-----------|-------------------|--------------------|
| T1 | Rate is coherence-driven, not G_F-driven | R climbs ∝ N² as ρ_coh→1; the slope vs coherence exceeds any G_F-only curve | Rate provably tracks **G_F not coherence** → **KILL** the wedge (W-as-object stands here); log with numbers |
| T2 | Captures write a readable magnetisation step | B_step·(R_coh−R_inc)·τ ≥ 10×fT at achievable N | **No magnetisation step above fT** at achievable N → **PIVOT** N / density / τ; if still none → **OPEN** read-out |
| T3 | Coherence can span the BEC (λ_ν ⊇ condensate) | ρ_coh = λ_ν/L ≥ 1 at N\* self-consistently | **Coherence cannot span the BEC** → **DEFER** to CEνNS scale (intra-nucleus coherence only; cross-condensate is the unestablished extension) |
| T4 | Selection rule selects EC substrates | Be-7 sits at (3,−1) underflow, one EC vector to on-lattice Li-7 | Rule mispredicts known EC isotopes → **OPEN** the selection rule; fork still runs on Be-7 alone |
| T5 | Stripped-Be-7 forks manufacture vs reshuffle | deep-K vs shallow-2s B_step differ ≥3× | Signatures indistinguishable → that sub-claim **OPEN**; main fork unaffected |

**Honest boundary (state it loud).** CEνNS (Freedman 1974; COHERENT 2017) **proves** coherence enhances neutrino cross-sections ~N² — but the coherence there is over **nucleons within one nucleus**, where the momentum transfer's wavelength already spans the nucleus. Extending N² across a **whole condensate** requires the neutrino wavelength to span the **BEC** — a far stronger, **unestablished** condition. T3 is exactly where the BEC claim goes beyond known ground; if ρ_coh<1 is forced, the honest result is DEFER, not PASS.

## 9. Implementation Notes

- **Double precision** throughout; rates and cross-sections span many orders. Prefer **dimensionless ratios** (R_coh/R_inc, ρ_coh, B_sig/B_floor) over absolute values to avoid under/overflow.
- **Limit checks are load-bearing:** the coherent law must return exactly R_inc at N=1 and at ρ_coh→0. Assert both in code; a model that fails the incoherent limit is wrong regardless of the headline.
- **Unit hygiene:** λ_ν from E_ν=0.862 MeV (ℏc/E order); BEC size L from N and density n; νₑ flux Φ_ν in m⁻²s⁻¹. Keep s⁻¹ for all rates and print units on every line.
- **Ledger every number.** Be-7 line, n–p gap, CEνNS σ, half-lives = `MEASURED-INPUT`/`OBSERVED-TARGET`. σ_inc, R_inc, R_coh, N\* = `DERIVED`/`COMPUTED`. B_step absolute may be `CALIBRATED(1)` pending NP19/NP20.
- **Plots that earn their place:** (1) R_coh/R_inc vs N (log–log) with the G_F-only flat line for contrast; (2) B_sig(N) crossing the fT floor, with N\* marked; (3) ρ_coh(N) crossing 1, overlaid so signal-and-span are read together.
- **Do not** import G/M/GM, ψ-as-primitive, fields-as-primitive, or G_F into the SDT chain. G_F appears **only** as the OBSERVED comparison column (the standard prediction the fork is measured against).

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN / DEFER** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP18
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or 1 — only the B_step flux-per-atom absolute, pending NP19/NP20]
- Engine namespaces: nuclear.hpp alpha_grammar, neutrino.hpp open-winding, laws::measured
- Phase thresholds (committed before run):
    P0: grammar assertions exact (3,−1)→(0,1), EC vector (−3,+2); 478 keV labelled GAMMA
    P1: R_inc within 2× of σ·Φ·n hand check (fail >10×)
    P2: R_coh/R_inc = N to <1% for ρ_coh≥1; exact reduction to R_inc at N=1 and ρ_coh→0
    P3: finite N* with B_sig≥10×fT AND ρ_coh(N*)≥1 simultaneously
    P4: deep-K vs shallow-2s B_step differ ≥3×
- Forbidden retroactive changes: widen tolerances; plug N* to a target; IDENTITY-PASS;
  import G/M/GM/ψ/field/G_F into the SDT chain; local constant namespaces;
  relabel 478 keV gamma as a neutrino line; call virtual particles fictions in general
```

### Pivot table (Trigger → PIVOT → if-fails → forbidden)

| Trigger (numeric) | First response (PIVOT) | If pivot fails | Forbidden response |
|-------------------|------------------------|----------------|--------------------|
| **P0** grammar mismatch or 478 keV mislabelled | Fix `alpha_grammar` call / labels; verify `nuclear.hpp` symbols | **STOP** — report blocker | Fudge the node to (3,−1) by hand |
| **P1** R_inc off >10× from σ·Φ·n sanity | Re-derive σ_inc width / flux normalisation; ADJ-### | **OPEN** the cross-section | RETRO-PASS the baseline |
| **P2** model ≠ R_inc at N=1 / ρ_coh→0 | Rebuild as explicit per-atom amplitude sum; ADJ-### | **KILL** the enhancement law | Hide the crossover; assert N² always |
| **P3 (T2)** no B_sig ≥10×fT at achievable N | PIVOT N / density / τ; finer SQUID model | **OPEN** read-out; ship rate table | PLUG N* to a tabletop number |
| **P3 (T3)** ρ_coh(N\*) < 1 (can't span BEC) | Tighten N/density to raise L-coverage; recheck λ_ν | **DEFER** to CEνNS scale (honest boundary) | Claim N² span as established |
| **T1** rate ∝ G_F, flat vs coherence | — (no native rescue) | **KILL** the wedge with numbers | Retro-fit a coherence slope |
| **T5** stripped-Be-7 signatures <3× apart | Sharpen deep-K vs 2s flux model (NP19/NP20) | **OPEN** the manufacture-vs-reshuffle sub-claim | Claim the fork without the factor |
| Rival (G_F + CEνNS) matches, SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream NP19/NP20/PPT10 missing | **DEFER** the affected phase; cite blocker ID | — | Fake PASS on the read-out |

### Allowed adjustments
- Finer numerics (N grid, density sweep, τ, SQUID model); phase splits (3a signal / 3b span); filename fix via ADJ entry.
- Alternative **native** routes already in §④ (explicit amplitude sum; interpolated f(ρ_coh)).

### Disallowed adjustments
- Post-hoc tolerance widening · plugging N\* or the rate to a target · IDENTITY-PASS · importing G/M/GM/ψ/field/**G_F** into the SDT chain (G_F is OBSERVED-comparison only) · relabelling the 478 keV gamma · over-claiming "virtual particles are fictions."

### Dual verdict reminder
Report **prompt completion (A–F)** separately from **physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN)**. A KILLed wedge with a complete tool is still prompt-completion A — honesty about the physics is the point.

---

*NP18 · headline of the 9-investigation flux-resonator set · SPEC · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
