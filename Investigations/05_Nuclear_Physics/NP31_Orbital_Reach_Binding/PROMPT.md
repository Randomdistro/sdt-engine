# NP31 — The Tour Cap: what limits the internal electron's orbit

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (opened 2026-07-23, direct).
> **Engine:** `#include <sdt/laws.hpp>` only. **Propose-only** on canon flags.
> **Discipline:** one energy scale (`αℏc`), zero fitted energies. No "charge radius" — `R_p` is the
> proton **boundary/displacement** radius. No G/M. No QM orbitals/wavefunctions — the orbit here is
> FLM14's **sequential tour**, a movement, not a probability cloud.

---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **What caps the tour.** FLM14 established the internal electron's orbit
   *is* a sequential tour of proton destinations. NP10 Face T established that binding scales with
   the **tour count**, and for `n ≤ 4` destinations that count is `(n−1)!` — the number of distinct
   closed tours — giving d/t/α with **zero constants**. What is unknown is the **reach**: how many
   destinations one tour can actually visit, and therefore where the count stops being combinatorial.
2. **Why does it matter?** — Because unbounded `(n−1)!` is catastrophically wrong past the alpha
   (over-counting by ~10⁶ at C-12, ~10⁶¹ at Fe-56), while the multiplier the data actually needs grows
   **linearly in A**. One quantity — the tour cap — converts the working light-chart law into a
   whole-chart law, and it is the same geometric quantity owed elsewhere (see §3).
3. **How will we find out?** — Derive the cap from the interleaved-trefoil packing (how many proton
   destinations lie within one electron's tour), then predict binding across d → Fe-56 with no fitted
   energy. Three declared routes (§④).
4. **What would prove us wrong?** — §⑧. If the cap must be fitted per nucleus it is a knob, not a
   derivation (KILL). If "energy ∝ tour count" cannot be derived from FLM14's residence law, Face T
   stays **CONVERGENCE**, not NATIVE — that debt is already registered and is not discharged here by
   assertion.
5. **How will we know we're done?** — Dual verdict. PASS = the cap derived from geometry, the
   factorial→linear crossover falling at A=4 as an *output*, and the light chart landing with zero
   fitted energy.

---

## 1. What is established (do not re-derive)

- **FLM14:** electron positions are **sequential**; the orbital *is* a tour, Born is dwell-time.
- **NP17:** the binding is a shared-electron Coulomb well; scale `αℏc = 1.4400 MeV·fm`, no fitted
  constant; deuteron `E = 3αℏc/D`, `D = 2R_p + R_p/3 = 1.963 fm` → 2.200 MeV (−1.06%).
- **NP10 Face T:** `B = tour_count × electrostatics`, `tour_count = (n−1)!` over `n` destinations —
  d ×1 → 2.200 (−1.06%), t ×2 → 8.557 (+0.88%), α ×6 → 26.721 (−5.57%). **Three nuclei, zero
  constants.** Look-elsewhere logged and lost: Catalan (−21%), `2^C(n,2)` (+26%).
  **Registered debt:** *"energy ∝ tour count is pure faith"* — owed to FLM14's residence law.
  **Registered falsifier:** the `n = 5` seat-tour lock must be **×24**.

## 2. The new measurement that defines this investigation (direct run, 2026-07-23)

`(n−1)!` against the multiplier the data requires (both normalised to the deuteron):

| nucleus | A = n | needed × | (n−1)! | (n−1)! ÷ needed |
|---|--:|--:|--:|--:|
| d | 2 | 1.00 | 1 | 1 |
| t | 3 | 3.81 | 2 | 0.52 |
| α | 4 | 12.72 | 6 | 0.47 |
| Li-6 | 6 | 14.39 | 120 | **8.3** |
| Li-7 | 7 | 17.65 | 720 | **41** |
| Be-9 | 9 | 26.15 | 40 320 | **1.5×10³** |
| C-12 | 12 | 41.44 | 3.99×10⁷ | **9.6×10⁵** |
| Fe-56 | 56 | 221.34 | 1.3×10⁷³ | **5.7×10⁷⁰** |

**Two facts fall out:**
1. **The factorial dies immediately past the alpha.** The registered `n=5 ⇒ ×24` falsifier is
   precisely where it dies — that falsifier does not merely test Face T, it *locates the cap*.
2. **The needed multiplier is extensive, not combinatorial.** `needed/A` = 2.40, 2.52, 2.91, 3.45,
   3.59, 3.95 for Li-6 → Fe-56 — flat to within a factor 1.6 across a 9× span in A. That is one
   local tour per internal electron, i.e. **tours ∝ A**, not `(n−1)!`.

**The crossover sits at A = 4**, independently confirmed: the static all-pairs Coulomb sum is exact
for d (1.00), He-3 (0.86) and α (0.94) and then over-binds monotonically (C-12 by **9.6×**). Two
different routes — combinatorial tour count and static pair sum — break at the same place. **A ≤ 4
is the largest set in which every proton lies inside one tour's reach.** That is the alpha as the
fully-coordinated cell, and it matches the grammar (α core, alphas at icosahedral interstices).

## 3. The cross-check that makes this a real derivation

The same interleave geometry that caps the tour must also deliver the **triton-contraction
magnitude**, which is separately measured and separately owed:

> isobars at fixed A (so the `A^(1/3)` trend cancels): boundary contracts as `n_t` rises in **90%**
> of lines; median **~4 milli-fm/triton**, up to **~11** in the Sn/Te/Xe region.
> **A = 124: Sn-124 (n_t=24) is 0.093 fm tighter than Xe-124 (n_t=16)** ⇒ 0.093/8 = **11.6 mfm/triton**.
> (`ATOMICUS/rules/Triton_Contraction_Rule.md`; the clean native win awaits deriving ~11 mfm/triton
> from the triton-interleave geometry, unfitted.)

**One geometry, two owed numbers.** If the interleave that caps the tour at ~A=4 also yields
11.6 mfm/triton in the heavy region, that is a single geometric statement paying two independent
measured debts — and it is not a function of the counts (NP24-A trap avoided), because it is a
*length* derived from packing, not a re-sort of (Z,N).

---

## ④ Strategy — three routes, gated

### Route A — the cap from the packing (primary)
- Enumerate, in the interleaved-trefoil packing, the proton destinations reachable by one electron's
  sequential tour; define the cap `k_max` geometrically, with **no reference to binding data**.
- **Pre-committed metric:** `k_max` yields `(n−1)!` behaviour for n ≤ 4 and extensive (∝A) behaviour
  above, with the crossover at **A = 4 ± 0** as an output; light chart within **±10%**, zero fitted energy.
- **Kill:** if `k_max` must be chosen per nucleus → PLUG → KILL Route A (root-1).

### Route B — discharge the "energy ∝ tour count" debt
- Derive from FLM14's residence/dwell law why binding scales with tour multiplicity at all.
- **Metric:** an explicit residence argument, or Face T stays **CONVERGENCE** and says so.
- **Forbidden:** asserting proportionality and calling the ladder derived.

### Route C — the shared geometry cross-check
- With `k_max` fixed by Route A, compute the boundary contraction per added triton from the same
  interleave and compare to **11.6 mfm/triton** (Sn/Te/Xe) and the ~4 mfm median.
- **Metric:** within ±25% unfitted → the geometry pays both debts. Otherwise report which one it pays.

**Order:** A → B → C. Do not merge routes to manufacture a pass.

---

## ⑧ Falsification tests

| ID | Hypothesis | Predicted | If FAIL → root |
|---|---|---|---|
| T1 | Face T reproduced at n ≤ 4 | d −1.06%, t +0.88%, α −5.57% | root-1 (model breaks its own anchor) |
| T2 | the cap is geometric, not fitted | one rule, all nuclei | root-1 → KILL (knob) |
| T3 | crossover falls at A = 4 as an output | not inserted | root-3 (cap ill-defined) |
| T4 | tours ∝ A above the cap | needed/A flat ~2.4–4.0 to Fe-56 | root-1 (saturation wrong) |
| T5 | n = 5 is NOT ×24 | the registered falsifier fails *by design* — the cap replaces it | root-3 if ×24 is defended |
| T6 | same geometry gives 11.6 mfm/triton | ±25%, unfitted | OPEN (pays one debt only) |
| T7 | "energy ∝ tour count" derived | FLM14 residence argument | CONVERGENCE, not NATIVE |

## ⑨.E Four-root sort
root-1 claim false (cap doesn't produce the crossover or the saturation) · root-2 dependency
(FLM14 residence law, NP30 packing, NP17 well) · root-3 prompt under-specified (tour/reach
definition ambiguous) · root-4 contraband (fitted energy, QM orbital language, "charge radius",
or a rule that is a pure function of (Z,N)).

## Brainstorm — overlooked factors
- **The α is the cell, not an anomaly.** Both routes break at A=4; the grammar already puts an α core
  at the centre and alphas at icosahedral interstices. The cap may simply *be* the alpha's coordination.
- **Check 2 tours × 3 pairs for the α** before adding anything: two internal electrons, six pairs.
- **Do not add NP17's "tetrahedral lock" term** until the cap is tested — the lock may be the cap
  seen from the energy side, in which case adding both double-counts.
- **The −5.57% α residual is the most informative number on file.** If the cap is exact, that residual
  should be the tour-geometry correction, not noise. Chase it last, and do not tune it.
- **Counts trap (NP24-A):** the cap must come from the packing *geometry*. Any cap expressed as a
  function of (Z,N) is not independent evidence.

## ⑤ Success / ⑥ Outputs
Class A: cap derived, crossover at A=4 as output, chart within ±10%, zero fitted energy, and the
11.6 mfm/triton cross-check paid. Class C: light chart only, ≤1 documented approximation.
**Honest floor:** the crossover measured and the cap named but underived → OPEN.
Outputs: `RUN_LOG.md`, `np31_tour_cap.py`, `NP31_DERIVATION.md`, `NP31_VERDICT.md`.

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — NP31
- Prompt completion target: [A|B|C]
- Physics class hoped: [NATIVE|CONVERGENCE|OPEN]
- CALIBRATED budget: 0 (αℏc only; the cap must be geometric)
- Routes this session: [A|B|C]
- Upstream verify-on-file FIRST: NP10 Face T ladder, NP17 well, FLM14 residence, NP30 packing
- Forbidden: fitting the cap; adding a lock term before the cap is tested; QM orbital language;
  "charge radius"; declaring PASS on d/t/α alone (that is Face T's result, already banked)
```

| Trigger | PIVOT | If pivot fails | Forbidden |
|---|---|---|---|
| cap won't come from geometry | try the alpha-coordination definition | OPEN the cap (root-3) | fit the cap to BE |
| saturation doesn't go ∝A | re-check reachable-destination counting | KILL Route A | import empirical saturation |
| FLM14 gives no residence law | **DEFER Route B**, cite FLM14 | label Face T CONVERGENCE | assert proportionality |
| contraction misses 11.6 mfm | report one-debt-paid honestly | — | tune the geometry to hit both |

**Disallowed:** post-hoc tolerance widening · fitted cap or energy · defending `(n−1)!` past its
crossover · claiming NATIVE while the residence law is unpaid.

---

*NP31 · opened 2026-07-23 direct · the orbit is FLM14's tour and Face T already counted it; the
factorial dies one step past the alpha and the data wants tours ∝ A. One geometric quantity — the
tour cap — closes the chart, and the same interleave owes 11.6 mfm/triton.*
