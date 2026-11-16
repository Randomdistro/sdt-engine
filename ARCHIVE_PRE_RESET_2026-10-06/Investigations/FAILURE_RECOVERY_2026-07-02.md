# Failure Recovery Sweep — the seven questions applied to the 2026-07-01 negative verdicts

> **Author:** J. C. Harvey, Melbourne · method: `PROMPT_EXECUTION_PROTOCOL.md` §8 (the seven questions).
> **Thesis under test (Harvey):** "if you find the problem so easily, you will find a solution just as
> easily — if there is one." **Answer, honestly:** not per-failure — but the failures share a ROOT, and the
> solution lives there. Four of the five hard failures cascade to ONE overlooked piece: the **influx /
> engagement profile** the FLM10 lattice solver is meant to derive.

Grades: `RECOVERED` (freedom justified, target falls out) · `PARTIAL` (premise-error + route named, freedom
not yet justified) · `NO RECOVERY` (premise error fundamental). No recovery was fished (mirror of anti-fake-PASS).

---

## D1 — deuteron binding (was: UNPAID) → **PARTIAL, + a mechanism ruled out**  *(tested: `flm12_d1_recovery.py`)*

1. **Why:** naive overlap used the hard core R_p; at D=1.94 fm the cores don't touch (2R_p=1.68) → brackets, can't predict.
2. **Recoverable:** yes, in form.
3. **Unaccounted:** the extended influx field beyond R_p (binding is far-field).
4. **Errored premise:** "engagement is localized at R_p" — which **contradicts FLM12's own ontology** (mass = the extended field). The test localized what FLM12 says is a field.
5. **Freedom:** the profile ρ_eng(r>R_p) **and** which through-flow (scalar-occlusion vs handed).
6. **Justification:** ρ_eng ∝ 1/r² is the Law-I convergent influx (not a knob). Tested: **scalar occlusion (π/4)P_eff·R_p⁴/D = 0.066 MeV (34× too weak → RULED OUT)**; **handed 3αℏc/D = 2.227 MeV (lands, 0.1%)**. → the deuteron bond is **handed redirection**, not occlusion.
7. **Cascade:** the residual absolute coefficient (factor 3 + αℏc normalization) = the **FLM10 influx-normalization root** — shared with NP20, NP21.

**Grade: PARTIAL.** Premise fixed, one mechanism eliminated, working form recovered; coefficient cascades to FLM10.

---

## NP20 — neutron mass & moment from one seat (was: OPEN) → **PARTIAL (mass) / route (moment)**

1. **Why:** ½(z−1)m_ec² = 0.600 vs 0.782 (−23%); moment sign only present because `sense=−1` was assumed.
2. **Recoverable:** partly.
3. **Unaccounted:** the seat's field-ENGAGEMENT (not a kinetic mass); the moment sign from WINDING handedness.
4. **Errored premise:** mass treated as **kinetic** (½·…) — the **same localized/kinetic premise as D1**, again contradicting FLM12 (mass = engagement, not ½mv²).
5. **Freedom:** the engagement↔kinetic correction (needed ×1.303) and the winding sign.
6. **Justification:** ×1.303 is **not** a clean native quantity → the mass stays **unjustified/OPEN** pending the engagement profile. The moment sign **is** justifiable — it should fall out of the W=1 winding handedness (PPT09), so "assumed" → recoverable, not free.
7. **Cascade:** mass → same FLM10 engagement-profile root as D1; moment sign → PPT09 winding.

**Grade: PARTIAL** — moment sign route named (PPT09); mass factor unjustified, cascades to FLM10.

---

## NP21 — iron floor (was: KILLED geometric) → **PARTIAL, + a suggestive cross-link to D1**

1. **Why:** with geometric a_C=α the floor lands at U-238; iron needs a_C/a_S ≈ **32×** larger (= SEMF's fitted value).
2. **Recoverable:** maybe.
3. **Unaccounted:** the nuclear EM **gearing** — the handed coefficient in the nucleus is not bare α.
4. **Errored premise:** "a_C = bare α." NP17 already says nuclear EM is geared; using bare α is the error.
5. **Freedom:** the Coulomb/surface ratio a_C/a_S from the gearing (not fit).
6. **Justification — the cross-link:** D1's recovery measured **handed / scalar-occlusion ≈ 34×** (2.227/0.066). If a_S (surface) is scalar-occlusion and a_C (Coulomb) is handed, then a_C/a_S ≈ **34 ≈ the needed 32×**. The iron-floor ratio may be the **same handed/scalar strength ratio D1 just found** — suggestive (6%), **not proven** (34 vs 32 could be coincidence; needs the derivation).
7. **Cascade:** shares D1's handed-vs-scalar root → the FLM10 through-flow normalization.

**Grade: PARTIAL** — premise found (bare α), freedom = handed/scalar ratio, a testable cross-link to D1's 34× (do not claim until derived).

---

## PPT11 — neutrino oscillation vs FLM11 zero-grip (was: OPEN) → **RECOVERED (tension) / PARTIAL (number)**

1. **Why:** imported QM phase 1/(4ℏE); FLM11's zero-grip axis has no internal clock; masses partly circular.
2. **Recoverable:** yes — the FLM11↔PPT11 tension resolves.
3. **Unaccounted:** the neutrino's tiny **nonzero mass** (0.02 eV) = a tiny NON-straightness.
4. **Errored premise:** FLM11's "the neutrino is **exactly** zero-grip." Measured mass ≠ 0 ⇒ it is **almost** straight, with the smallest residual winding.
5. **Freedom:** that residual non-straightness (the mass gap) = the **residual clock**.
6. **Justification:** neutrino.hpp's 0.02 eV mass gap is the framework's own minimum V_disp — native, not a knob. The tinier the residual, the **slower** the beat → oscillation over astronomical baselines. FLM11 (zero-grip, leading order) and PPT11 (needs a clock) reconcile: the mass gap IS the clock.
7. **Cascade:** from FLM11's leading-order idealization (a separate root from FLM10), and it is resolvable, not fatal.

**Grade: RECOVERED on the tension** (mass-gap = residual clock, physically motivated); **PARTIAL on the number** (a native phase, not the imported QM kinematic, is still owed).

---

## NP18 — Be7BEC resonator (was: DEFER, 7 orders short) → **RECOVERED (premise) / PARTIAL (payout)**

1. **Why:** neutrino wavelength ~1.4 pm ≪ atomic BEC ~2 µm → coherence unreachable by ~7 orders.
2. **Recoverable:** yes.
3. **Unaccounted:** coherence at the **spation** scale, not the atomic scale.
4. **Errored premise:** "the atomic BEC (atom centres-of-mass, µm) is the coherent medium." (Harvey flagged this live: *it's the spations that condense, not the atoms.*)
5. **Freedom:** the coherence SCALE — spation-scale (sub-fm).
6. **Justification:** monist substrate — atoms phase-lock ⇒ the underlying spation superfluid goes coherent at ITS scale; a denser host (superfluid He, ~10²²/cm³) fields ~10⁶× more coherent spations. Native, not a knob.
7. **Cascade:** whether spation coherence reaches pm/sub-fm is itself the **FLM10 substrate** question.

**Grade: RECOVERED premise** (spation not atomic coherence); **PARTIAL payout** — the spation coherence length cascades to FLM10.

---

## The cascade (§8 Q7) — one root under four failures

> **D1, NP20 (mass), NP21, and NP18 are NOT independent failures.** Every one bottoms out on the same
> unbuilt piece: the **influx / engagement profile** — its magnitude, its handed-vs-scalar split, and its
> coherence length — i.e. exactly what **FLM10 (the per-spation lattice solver)** is meant to derive. PPT11
> is the one separate root (FLM11's zero-grip idealization) and it already reconciles via the mass gap.

What the sweep bought, concretely (not fished):
- **Eliminated:** scalar/gravitational occlusion as the deuteron binder (34× too weak).
- **Identified:** deuteron binding = handed redirection on the 1/D law (D1 → NP17 convergence).
- **Cross-linked (testable, unproven):** NP21's missing iron-floor ratio (~32×) ≈ D1's handed/scalar ratio (~34×).
- **Reconciled:** the FLM11↔PPT11 contradiction (the 0.02 eV mass gap is the neutrino's residual clock).
- **Confirmed:** NP18's atomic-BEC failure points at spation-scale coherence (Harvey's own reframe).

**So the honest answer to "find the problem easily → find the solution easily":** the *individual* numbers did
not fall out any more easily than before — but the seven questions showed the failures **collapse onto one
root**, and paying that root (FLM10's influx profile) may clear four debts at once. The solution was findable;
it just isn't per-failure — it's at the shared premise. **FLM10 is now not "reproduce gravity" but a concrete
acceptance test: derive ρ_eng(r), its handed/scalar split (~34×), and its coherence length.**
