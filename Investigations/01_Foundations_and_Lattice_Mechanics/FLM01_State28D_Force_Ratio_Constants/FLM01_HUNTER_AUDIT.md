# FLM01 — HUNTER audit (2026-07-02)

> Re-audit of `FLM01_VERDICT.md` (2026-06-16, graded Class C) under `HUNTER_PROTOCOL.md`.
> Arc: FIND → TRACE → GROUND → CORRECT → VERIFY. **The prey is the false premise, not the number.**

---

## ⚠️ SELF-CORRECTION (HUNTER on HUNTER, 2026-07-02) — the "dead code" GROUND was WRONG

The §GROUND kill below ("both constants feed nothing; dead code") rested on a `grep` for
**`occlusion_eclipse_fraction`** — a function name I took from the *old verdict's prose and never verified against
the code*. **That name does not exist.** The real function is **`calculate_occlusion`** (`state28d.hpp:118`) — the
Law-III occlusion selector whose docstring reads *"determines force type: E→0 Coulomb, E→1 Gravity."*
Re-grepped with the correct name:

- **`calculate_occlusion` (holds the `1e10`) IS called** — once, by **`FLM03/flm03_spation_rotation_map.cpp:154`**
  (the tool I graded RESOLVED 4/4). It prints `E(a₀)=0.000168` — a **diagnostic**, not one of FLM03's four proofs,
  so FLM03's PASSes stand; but I never flagged that FLM03 exercises this constant.
- **The `1e10` is inert *only because* the factory leaves `T_5=0`** (`proton_nuclear`/`electron_atomic` never set
  it → `tanh(0/1e10)=0`). It is **NOT dead code — it is a DORMANT fitted parameter inside the force-type selector**,
  live the instant `T_5≠0`.
- **`accessible_phase_space_volume` (holds the `1e-20`) is genuinely uncalled** — that one *is* dead.

**Corrected verdict:** the `1e-20` is dead (quarantine/delete). The `1e10` is a **latent, un-derived parameter in
the Coulomb↔Gravity occlusion selector** — SDT's zero-free-parameter claim is **latently threatened, NOT "not
threatened"** as I wrote below. My original §F self-flag ("direct-name search; an indirect path would change this")
was the right instinct and I under-weighted it — the search itself used a wrong name, the worse failure.

**Method lesson (into HUNTER practice):** never grep a symbol you have not read in the source. Assert nothing about
callers without the verified name. This is exactly a §A/§F failure committed by HUNTER — logged, not hidden.

*(The FIND section below — inconsistent class, the false ✓, CONVERGENCE-on-non-convergence — still stands; only the
GROUND "dead code" claim and its "not threatened" conclusion are corrected here.)*

---

## RECURSIVE CORRECTION (n-to-the-n) — a diagnosis is still a result; correct the PREMISE, then recurse

A finding ("it's a latent parameter") is not the end — it is the next premise. Apply the seven questions to each
correction, **and re-verify at every step** (each level hides the next error):

- **S0 · standing result:** the `1e10` is a latent un-derived parameter in `calculate_occlusion`.
- **S1 · correct the premise** *"occlusion needs a `1 + tanh(T_5/1e10)` screening term."* → It is the multiplicative
  identity whenever `T_5=0`, and its only caller (FLM03) passes `T_5=0`, so it fires nothing. **VERIFY** → the S1
  premise *"T_5 ≡ 0"* is itself **FALSE**: `magnetosphere.hpp:97,180,365` set `T_5` (Earth core ≈ 5.2×10⁴ Pa/m, etc.).
  → S1 corrected.
- **S2 · correct** *"then T_5 is a phantom DoF."* → **FALSE**: `T_5` **is** populated and used — but by the
  magnetosphere module, which **does not call `calculate_occlusion`** (its only caller is FLM03). And every populated
  `T_5` (~10⁴ … 10⁻²⁰ Pa/m) is **6+ orders below 10¹⁰**, so `tanh(T_5/1e10) ≈ 0` even if connected. → S2 corrected.
- **S3 · ROOT premise:** the `1e10` is an **orphaned scale** — disconnected from *both* its only caller (`T_5=0`)
  *and* its DoF's real populated range (~10⁴ Pa/m). It was chosen for an **imagined regime** (FLM01's table guessed
  nuclear ~10⁴⁴, which *would* saturate the tanh); reality populates neither 10⁴⁴ nor 10¹⁰ — it populates ~10⁴. The
  constant answers a regime that never occurs.

**Can the premise be corrected? — CORRECTION (Harvey, 2026-07-02): the answer is CLOSE, not eliminate.**

My first answer here was *"RECOVERED by elimination — drop the term."* **That was an errored verdict.** Amputating an
un-derived term is a **fake correction**: it deletes the *evidence of an open problem* instead of paying it — the
mirror image of a fake-PASS. **The root is not "a bad term"; the root is that a loop isn't closed.** `T_5` is a real,
populated DoF; the framework put a screening term there *because the coupling is real* (internal pressure gradient
self-screens the influx). The `1e10` is a **placeholder for an unclosed derivation**, not garbage.

- **The `1e10`: the debt is CLOSURE.** Derive the screening scale `S` (units [Pa/m]) from the framework instead of
  guessing it — the natural candidate is the **influx pressure-gradient at the body**, `S ~ P_conv/R` (the convergence
  pressure over the occluder's own radius). Then `tanh(T_5/S)` becomes the ratio *internal gradient : influx gradient*
  — self-screening turns on precisely when a body's internal pressure structure rivals the influx it occludes.
- **What closing PREDICTS (and why eliminating would have been a physics loss):** with `S ~ P_conv/R` (~10⁴⁰–10⁶² Pa/m),
  every ordinary `T_5` (~10⁴ Pa/m, geophysical) gives `tanh(T_5/S)≈0` → **negligible self-screening for ordinary matter,
  now for a DERIVED reason**, while the term **turns on only for extreme compact objects** whose internal gradient
  approaches the influx gradient (neutron-star / horizon regime). That is a **falsifiable prediction the term encodes**;
  deletion throws it away.
- **Status:** the closure itself is Law VI / **PPT08** work (the DoF *dynamics*) — **OPEN**, but now framed as a
  **closure to complete**, not a term to cut. The verdict is not "eliminate" and not "tune" — it is **CLOSE**.
- **Next rung (recursion continues):** `E_mutual=(Ω_self+Ω_other)/4π` — is the sum the right mutual measure or a
  double-count the `min(1.0,…)` masks? Ties to **Law III**; the next hunt. The recursion bottoms at an axiom or a
  named OPEN, never at a constant.

**Two meta-lessons (into HUNTER practice):**
1. *Correcting a premise without re-verifying relocates the error one level down.* Three times here the correction was
   itself wrong (dead-code → T_5≡0 → phantom-DoF). Recurse **and re-verify** at every step. *n to the n.*
2. **Correction means CLOSE the loop, never amputate it.** An orphaned scale / dead function / un-derived constant is a
   **closure debt**, not junk. Eliminating it is a fake correction that hides the open problem. Prove a thing is *not*
   a closure the theory wants before you ever cut it.

---

## FIND — faults in the standing verdict

1. **Class not pinned (internally inconsistent):** header says "QUALIFIED PENDING (Class D)", §78 says
   "→ QUALIFIED (Class C)", §120 says "Class C". Three grades, one file.
2. **A false ✓ on a 20-order miss:** the derivation table calls "convergence pressure 10³⁰ Pa ≈ electrostatic ✓"
   a match for a constant that is **10¹⁰** — twenty orders away. That is not a ✓.
3. **Graded CONVERGENCE on non-convergence:** the table's own attempts miss by **10⁴ to 10³⁴**. A 4-to-34-order
   miss is not "found in the vicinity"; it is *not derived*. CONVERGENCE (Class C) is the wrong label.

## TRACE — the errored premise (Q4)

FLM01 assumed `T_5=1e10 Pa/m` and `Phi_5=1e-20 J` are **physics-bearing constants to be derived** (and agonised
"derive or tune?"). That premise is what fails.

## GROUND — run it to the root (Q7)

**VERIFIED in code (`state28d.hpp`):** the constants are real — line 134 `tanh(|T_5|/1e10)`, line 159
`1.0 + |Phi_5|/1e-20`. But:

- **`grep` for callers of `accessible_phase_space_volume` and `occlusion_eclipse_fraction` across all `.cpp`/`.hpp`
  returns NOTHING** outside `state28d.hpp` itself. The only two functions that consume `1e10`/`1e-20` are **never
  called** by any benchmark, tool, or header.
- `T_5` defaults to `0` (line 228) and is only set via `from_array`; `tanh(0/1e10)=0`.

**The constants propagate to zero results.** There is no physics to derive from them because no computation consumes
them. The premise ("fundamental constants") is false at the root: this is **inert regularisation in uncalled code.**

## CORRECT — the seven questions

1. **Why fail:** the scales can't be derived because they encode no result — they soften functions nothing runs.
2. **Recoverable:** the "derive vs tune" dilemma is **moot / premature**, not hard.
3. **Unaccounted:** whether the code is *load-bearing* — the verdict never checked propagation.
4. **Errored premise:** "these are fundamental constants." They are non-load-bearing regularisation.
5. **Freedom:** the two functions are either (a) **dead scaffolding** → quarantine/delete, or (b)
   **intended-but-unwired** → wire them into a benchmark first; only *then* does "derive vs CALIBRATED" apply.
6. **Justification:** determined by intent (Harvey's call) — but the audit stands either way: today they feed nothing.
7. **Cascade:** **none to any result** (inert). The only latent cascade is to **FLM06** (seed count) *if* they are
   ever wired and prove irreducible — at which point they'd be extra dimensional anchors to reconcile.

**Exoneration + demotion, both:** SDT's **zero-free-parameter claim is NOT threatened** by these (they corrupt no
prediction). But FLM01's **Class C is withdrawn** — it inflated inert knobs into fundamental constants.

## VERIFY

- Constants exist as claimed: `state28d.hpp:134,159` (read).
- No external callers: `grep` over `*.cpp`/`*.hpp` (empty). *Caveat:* direct-name search; an indirect/dynamic call
  path would change this, but none is expected in this header-only codebase.

## Verdict line

> **Prompt completion** C (the run located + interpreted the scales) · **Physics class** **KILLED as stated**
> (mis-specified target: inert regularisation, not fundamental constants) · **Recovery** N/A — the target was wrong,
> not the derivation · **Cascade root** none (inert); latent → FLM06 only if wired.

**Action (Harvey's call — canon, not mine to touch):** wire the two functions into a benchmark that actually needs
them, or quarantine them as scaffolding. Do not re-open "derive vs tune" until they compute something.
