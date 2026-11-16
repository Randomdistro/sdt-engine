# PPT08 — Honest Rebuild · VERDICT (2026-07-02)

> Replaces the FABRICATED APS04 closure. Tool: `ppt08_trefoil_wake_honest.py` → `ppt08_honest_results.txt`
> (python3+numpy, ran clean). **Nothing asserted, no measured frequency used as an input, no QM interpretation imported.**

## Method (Harvey's correction, applied fully)

Use **only the raw data the spectroscopists recorded, interpreted in SDT** — not in borrowed nouns.
No "Coulomb," no "Lamb," no "orbital / s / p / l / SO(3)." Those are QM *interpretations*, not data.

**The raw data (measured frequencies, the same the experiments used):**
- The bulk hydrogen series (Lyman/Balmer…) = SDT's radial **k-ladder** `r_n = n²a₀` — already recovered (FLM03).
- Finer instruments record **extra splittings** of each line: optical ~1.09×10¹⁰ Hz (~3×10⁻⁶ of the 13.6 eV binding)
  and an RF beam resonance ~1.05785×10⁹ Hz (~3×10⁻⁷ of the binding). The extra components come **in twos** (doublets).

**The SDT question (no story):** SDT's radial field gives the ladder but nothing finer. Does the proton's non-spherical
(trefoil) form imprint the extra measured splittings? Pure forward computation.

## What the tool computed

| quantity | APS04 asserted | honest rebuild (computed) |
|---|---|---|
| wake fall-off | r⁻¹ | **r⁻²·⁹⁹** (their power law was invented) |
| angular unevenness/average | ~0.008 (asserted) | **0.667, constant with r** (shape persists) |
| field at the ground rung r₁ | asserted coupling ~8×10⁻³ | **2.4×10⁻¹⁴** of near-proton (r⁻³) |

## Findings (raw data in, SDT out)

1. **The trefoil's shape persists in angle at any distance** (unevenness/average → 0.667, constant). So "the proton's
   non-spherical form reaches out" is true.
2. **But the field the electron sits in dies as r⁻³.** At the ground rung (6.3×10⁴ R_p) it is **2.4×10⁻¹⁴** of the
   near-proton value — the electron samples ~10⁻¹⁴ of the proton's shape.
3. **Against the raw data:** the extra splittings need a coupling ~3×10⁻⁷ … 3×10⁻⁶; the trefoil far field gives
   ~2×10⁻¹⁴ — **short by 10⁷–10⁸.** It cannot make them. APS04 asserted ~8×10⁻³ — **~3×10¹¹× the real value**; that
   single asserted number *was* the fabrication.
4. **Count mismatch:** the trefoil stamps a **three-fold** pattern; the extra lines are measured **in twos**. A
   three-fold source cannot produce two-fold splittings.

## Verdict

> **Prompt: A** (rebuilt + executed) · **Physics: OPEN** (SDT mechanism computed, found insufficient) ·
> **Recovery: hypothesis survives, far-field version refuted** on both magnitude (10⁷–10⁸ short) and count (3 vs 2).

**PPT08 stays OPEN.** The extra measured hydrogen splittings are **not** made by the proton's far field. In SDT they
must come from **where the electron actually touches the core** — the seated / shared-electron geometry (cf. NP17) —
the near contact, not the washed-out far wake. This is the honest inverse of APS04: a mechanism run to ground and
reported insufficient, with nothing faked, no measured frequency used as an input, and no QM noun borrowed.

## Sampler caveat (Harvey, 2026-07-02) — the datum is a DRIVEN, DEPLETING resonance, not a static gap

Even this rebuild carried a residue of the story: it compared a **static** trefoil field to a **static** "splitting."
But that RF datum (Lamb–Retherford 1947) was not a reading of a resting energy gap — it was taken by preparing a
**metastable** population, RF-driving it to a decaying state, and detecting the resonance as the **disappearance** of
the metastable beam. The signal *is* the depletion: the sampled part is driven up and out until nothing is left. So
the raw observable is a **driven reconfiguration RATE in a system the sampler is actively emptying**, not a static
level separation. **Consequence:** the far-static-field kill stands (a 10⁻¹⁴ field cannot drive a 10⁻⁷ anything), but
the *right* SDT question is not "what static field makes a static gap" — it is **"what reconfiguration of the seated /
near-contact electron, when driven, resonates and depletes at these measured rates."** And the deeper gap: **no
"sampler-sampler"** was ever built — no meta-measurement verifies the RF-drive-plus-depletion apparatus reads
something intrinsic rather than shaping the resonance it reports. The number is entangled with the method that took
it. Left OPEN and honestly reframed as dynamical — not modelled here, and not faked.
