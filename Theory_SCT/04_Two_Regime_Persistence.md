# Two-Regime Persistence — Stable Codewords vs Metastable Barriers

> A refinement of the SCT forced by the neutron (Harvey's question: *"is it 89 reconnections, or
> a tug-of-war the proton wins and the neutron loses?"*). The original theorem has **one**
> persistence law, `τ ≥ (1/λ)2^{d_min−1}`. That law is correct **only for structures with no
> lower-resistance valid form**. Structures that *do* have one persist by a different law. Naming
> the two regimes resolves the neutron and turns "persistence" into a landscape statement.
> **Author:** J. C. Harvey, Melbourne.

---

## 0. The discriminator

For any structure `S` in environment `E`, ask one question:

> **Does a lower-resistance valid form `S'` exist that `S` can reach?**

- **No** → `S` sits at a floor of the resistance landscape. The only way out is to climb *up* to
  a different valid form. Persistence is governed by **`d_min`** (the height of the climb counted
  in simultaneous component changes). → **Regime I.**
- **Yes** → `S` sits in a metastable well *above* a lower form. The medium presses *downhill*
  toward `S'` (path of least resistance); the structure is held only by a **barrier `B`**.
  Persistence is governed by `B`, not `d_min`. → **Regime II.**

This is the question the original SCT never asked. A1–A4 (and the `d_min` derivation in `00`)
silently assume Regime I — they model failure as "climb to a *distinct* valid structure," which
presumes no *downhill* one exists. The neutron breaks that assumption, and the proton obeys it.

---

## 1. Regime I — stable codewords (no lower form): the `d_min` law

```
τ_I ≈ (1/λ) · 2^{d_min}          (Regime I: unbiased, simultaneous-corruption)
```

The structure fails only when `d_min` components are corrupted **simultaneously** (the binomial
failure model of `00`, valid here because corruption has no downhill drift to ride — the soliton-
repair, A5, restores every sub-`d_min` excursion). `d_min` is a **literal count**: the minimum
simultaneous changes that carry `S` to a *different* (necessarily higher- or equal-resistance)
valid form.

**Members:** the **proton** (`d_min ≈ 9.5×10³⁸`, unknot the trefoil → eternal); the **electron**
(`W=1` ground); **magic-number nuclei** (closed-shell, maximal `d_min`); **crystals**
(repetition codes, `d_min ∝ n`). For all of these the `2^{d_min}` scaling is right, and the
persistence is *enormous* because `d_min` is macroscopic.

`d_min` is base-meaningful here: `10³⁹` is a *count*, not a log. (Contrast Regime II below.)

---

## 2. Regime II — metastable states (a lower form exists): the barrier law

```
τ_II ≈ (1/λ) · e^{B}             (Regime II: biased escape over a barrier of depth B)
```

A lower-resistance form `S'` exists, so the medium drifts toward it; `S` is held in a well of
depth `B` by the A5 repair (the "hold") against that drift (the "pull"). Decay is a **biased
first-passage / barrier crossing** (Kramers/transition-rate), **not** a wait for `d_min`
simultaneous corruptions. The number that appears is the **well depth `B`** (in nats; `B/ln2` in
bits), which is **base-dependent precisely because it is a log, not a count** — the tell that it
is a barrier, not a reconnection tally.

**Members:** the **free neutron** (`B ≈ 61`, `τ ≈ 880 s`); **every β-radioactive nucleus**;
**nuclear/atomic excited states**; any metastable phase (super-cooled liquid, diamond→graphite).

The original SCT's `2^{d_min−1}` is the *wrong functional form* for these: it would predict
stability set by a corruption count, when in fact it is set by a barrier the structure is
*actively losing* a tug-of-war against.

---

## 3. The resistance landscape (the unifying picture)

Both regimes live on one object: the **form-resistance landscape** (the mass-defect ontology —
mass = the medium's resistance to holding a form). Each valid form is a point at some height
(its mass-per-configuration); the medium always presses toward lower points.

- **Regime I = a local (or global) minimum.** No downhill neighbour. Escape needs a `d_min`
  climb. Lifetime `~2^{d_min}`.
- **Regime II = a ledge above a lower minimum.** A downhill neighbour exists. Lifetime `~e^{B}`,
  `B` = the ledge's retaining wall.
- **The global floor** (least-resistance form the medium can hold) is **iron/nickel** — the
  binding-curve peak read as the *bottom* of the resistance landscape. Everything heavier or
  lighter sits above it; fusion (light side) and fission (heavy side) both run *downhill toward
  iron*. *(This identification is asserted, not yet derived — see §5.)*

`β`-stability is then just **the sign of the local gradient**: a nucleus is β-stable when
`n → p` (or `p → n`) is *uphill* (Regime I, no decay), β-radioactive when it is *downhill*
(Regime II, finite `τ`). The free neutron is the simplest Regime-II case — `p+e` is 0.782 MeV
downhill, so it always decays; bind it where `n → p` is uphill and it joins Regime I and goes
eternal. (See [03](03_The_Neutron.md).)

---

## 4. How this refines the SCT and the axiom audit

- The **persistence bound of `00`** (`τ ≥ (1/λ)2^{d_min−1}`) is hereby scoped to **Regime I**.
  Regime II obeys `τ ≈ (1/λ)e^{B}` instead. The theorem as originally stated is *true where it
  applies* and *mis-applied* to metastable structures.
- **A5 (repair)** acquires a sharper role: in Regime I it makes the renewal assumption exact
  (every excursion repaired); in Regime II it is the **"hold" in the tug-of-war** — the only
  thing standing between the metastable form and its downhill neighbour. Repair doesn't make
  Regime-II structures eternal; it sets `B` (how long the hold lasts).
- **A7 (selection)** becomes the landscape statement: *observed* structures are the Regime-I
  minima plus the Regime-II ledges whose `B` exceeds the observation time. The particle spectrum
  (`W=1,3`) is the set of Regime-I minima; the radioactive isotopes are the Regime-II ledges.

---

## 5. What is solid, what is owed

**Solid:**
- The **discriminator** (lower form? yes/no) cleanly separates proton-type (I) from neutron-type
  (II) and matches the data (proton eternal, neutron 880 s, β-stable vs β-radioactive).
- **Base-dependence is the diagnostic:** a Regime-I `d_min` is a count (base-free, `10³⁹`); a
  Regime-II `B` is a log (base-dependent, `61` nats `= 88` bits) — so the neutron's "89" was
  *always* a barrier, never a reconnection count.
- The resistance-landscape picture **unifies** mass defects, β-stability, fusion/fission
  direction, and the two persistence laws into one geometric statement.

**Owed (named):**
- **What sets `B`.** `B ≈ 61` is back-solved from `880 s`. To *predict* it, SDT must supply the
  **transition rate over the barrier** — the rate at which a fluctuation releases the internal
  electron from its 1.83c counter-seat. That rate is SDT's analog of the weak coupling `G_F`
  (the distillation's central wager: `G_F` as a re-description of a medium-grounding event). This
  is the deep open problem; it is **not** faked here.
- **Iron as the global floor** (§3) is asserted; deriving the binding curve as a one-parameter
  resistance landscape with the iron minimum *computed* is the natural next theorem (distillation
  §2.4) and is **not** done.
- The Regime-II law `τ ≈ (1/λ)e^{B}` uses a generic escape form; the correct prefactor/attempt
  frequency for a topological seat-release (vs thermal Kramers) needs the seat dynamics.

**Net:** the neutron forced a real refinement. The SCT has **two persistence laws, one
landscape**: `2^{d_min}` at the floors (Regime I — proton, magic nuclei, crystals) and `e^{B}` on
the ledges (Regime II — neutron, radioactive nuclei). The proton wins its tug-of-war because it
*has no opponent*; the neutron loses because `p+e` is downhill and the repair can only hold the
ledge for `e^{61}` ticks.
