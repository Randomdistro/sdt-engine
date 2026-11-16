# PPT14 — Heavy resonance masses (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the mechanism. The 2026-07-29 seed is kept below the line, superseded.

## 1. What is established (reset 2026-10-10, `PPT14_RESET_ASSESSMENT_2026-10-10.md`)
- **M₀ = [π²ħ³P_conv√3/(2c⁵)]^¼ = 1.786524e-24 kg, so M₀c² = 1.0022 TeV** (two routes agree exactly; M₀/m_p = 1068.1). The "~1 TeV with no tuning" claim is confirmed in its registered band.
- **Grade G3, shared-input.** Contaminating input: R_CMB, the observed cosmological scale, entering at laws.hpp:249–276 through N and P_conv. M₀ ∝ R_CMB^¼ · T_CMB, so this is not a prediction independent of the cosmological boundary (it is the same bottleneck as CR03).
- **The resonance ladder: G2, open.** No native rung rule exists. Choosing one to land on 80.4 / 91.2 / 125.3 / 173 GeV would be a census, which is excluded.

## 2. What opens the ladder (registered order)
1. **Excitation energies of the (p,q) winding modes below M₀**, from the PPT01 mode equations (`law_VI::topology`: v_T, v_P, aspect √(q/p)) with an unwinding barrier (PPT09's open item). Written before any mass is loaded.
   - **Dependency added 2026-10-12:** PPT18 found the corpus carries three different proton windings ((2,3), (4,5), "4 tours × 3 turns"). The excitation ladder inherits whichever winding Harvey rules.
2. **An unwinding rate for the widths**, from the same barrier.
3. **One comparison at ratio level first** (mass ratios, then widths), then absolute values. Each comparison carries a cascade band.

## 3. Prohibitions
- No ladder chosen by agreement.
- No "W/Z/Higgs/top" bookkeeping as mechanism: the measured masses and widths are anchors only.
- R_CMB stays labelled class-X until CR03 Stage 3 closes.

---

## Seed specification (2026-07-29, kept as written)

# PPT14 — Heavy Resonance Masses and the Collider Ladder

> **Status:** OPEN — specification seed (benchmark-coverage alignment 2026-07-29; catalogue
> row B74). **Author:** J. C. Harvey, Melbourne. Gateways binding.

## Target

The heavy resonances the colliders record — 80.4, 91.2, 125.3, 173 GeV in the prevailing
account's W/Z/Higgs/top bookkeeping. Natively these are not particles of the medium's stable
ladder; they are the shortest-lived winding excitations the medium admits before unwinding.
Measured anchors: PDG resonance masses and widths.

## SDT footing

The natural SDT mass unit M₀ = [π²ℏ³P_conv√3/2c⁵]^¼ lands at ~1 TeV with no tuning (the
walkthrough carries this as the scale where the colliders' heaviest resonances live — the
low-winding rungs of that ladder). The open question is whether the specific resonance
masses are rungs of a derivable excitation ladder below M₀, with widths as unwinding rates.
Existing corpus: PPT01 (quantisation), PPT09 (stability), Law VI winding spectrum.

## Pre-registration skeleton (complete before any tool)

- Question: does the sub-M₀ excitation ladder place rungs at the measured resonance masses
  (ratios, not absolute, as the first gate), with widths ordered by unwinding resistance?
- Rejection criterion (populated): no ladder structure fits the measured ratios without
  per-rung fitting, or width ordering comes out inverted.
- Anchors: PDG masses/widths for the four heaviest resonances.
- Tolerance: committed before instrumentation; ratio-level first, absolute second.

## Benchmark linkage

Catalogue row B74 · suite coverage roster · tally on computed number only.

---

## Audit correction 2026-10-05 (opening premise)

**Finding:** The seed gives no ladder structure for the 80.4, 91.2, 125.3 and 173 GeV resonances beyond "shortest-lived windings", and no committed tolerance.

**Correction:** State the ladder rule and the ratio-level tolerance before running.

**Status:** OWED — model, data or derivation missing; requirement and tolerance recorded, nothing run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
