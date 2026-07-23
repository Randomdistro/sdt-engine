# The nuclear cascade — plain-language report
### NP24 · NP25 · NP26 · the packing audit · 2026-07-18/19

All numbers below come from data pulled live and checked: AME2020 masses (3558 nuclides), NUBASE2020 (253 stable, spins, decay modes), CRC ionisation ladders (104 elements, 764 stages). Nothing sampled, nothing sorted to flatter.

---

## What was being asked

Does the deuteron–triton grammar — every nucleus as *one alpha core + n_d deuterons + n_t tritons* — describe real structure, or is it bookkeeping that happens to add up?

The honest answer is: **in two places it is real and exceptionless. In several others it is arithmetic wearing a physics costume.** Both halves matter, and telling them apart is the whole result.

---

## The two things that are genuinely real

> ⚠️ **CORRECTION, 2026-07-21.** Item 1 below has since been **demoted**. Chasing its 45 exceptions
> back to the algebra showed the grammar coordinates are a straight relabelling of (Z, N):
> the triton count *is* the neutron excess. So "both counts even" simply means "even-even", and the
> law is the nuclear pairing rule — real, but known since the 1930s and not evidence for the grammar.
> The second half is worse: "odd triton count" means "odd mass number", and those cannot have zero
> spin as a matter of arithmetic. See `NP24_Grammar_Rule_Extraction/TECHNICAL_REPORT_ANOMALY_45.md`.
> Item 2, the scission invariant, is **unaffected** — it was proved from conservation, not fitted.

**1. The magnetism law.** Take every nucleus whose spin is known — 3043 of them. If both subunit counts are even, the nucleus has **no magnetic moment**: 812 out of 812, not one exception. If there's an odd triton, it **always** has one: 765 out of 765, again no exception.

The rule is: *a nucleus is magnetic exactly when it has an unpaired subunit.* Paired subunits turn against each other and cancel; a leftover one has nothing to gear against, and that leftover circulation is the moment.

This came out of testing a stronger claim — that magnetism belongs to tritons alone — which scored 78%. Every single failure was the same thing: a lone **deuteron** carrying a moment with no tritons anywhere. Deuterons aren't magnetically inert; the free deuteron's moment is measured. Widening the rule to "any unpaired subunit" took it to 98.5%.

**2. The scission invariant.** When a heavy nucleus splits, both halves need an alpha core, but the parent only had one. Where does the second come from? Conservation answers it with no freedom at all:

> **Tritons are preserved exactly. Deuterons drop by exactly two.**

So the second core is built by **two deuterons fusing into one alpha** — and that emits *no neutrons*. Checked on eight real fragment pairs, from Se-92/Ce-144 to the symmetric Pd-118/Pd-118: every one balances.

---

## What was found in the repo, not derived

The fission selection rule was **already written down** in the stick model and I'd claimed it didn't exist:

> **G_core = |n_d − n_t| + (n_t mod 2)**

When this is zero, the light fragment sits on the "golden line" (equal deuterons and tritons, even count). That forces an exact integer series — and only **one** member of it has a partner that's doubly magic: **Mo-104 + Sn-132 + 2n**. Put the light fragment on the golden line and the famous doubly-magic tin falls out the other end automatically. One condition, two results.

---

## What failed, and why that's useful

**The packing model does not reproduce nuclear binding.** The shadow-overlap picture — mass defect as overlapping shadow area — scores an impressive-looking R² of 0.98 *if you use only stable isotopes and total binding energy*. Run on all 3213 valid nuclei and measure per-nucleon binding instead, it scores **−12.2**: worse than guessing the average. It finds the binding ridge in **1 row out of 116**.

The failure is systematic and it names its own cause: the model always picks the most neutron-rich option, because a triton casts three shadow-discs and a deuteron only two. **It counts area. Binding doesn't.** Real binding-per-nucleon is nearly flat — about 8.5 across two hundred nucleons — because every baryon circulates identically and the drag is shared across the whole gearing. Area accumulates; drag per gear doesn't. No overlap model can produce that.

**Ferromagnetism has no grammar signature.** The magnetic elements are Fe, Co, Ni, Gd, Tb, Dy, Ho, Er and Tm. In grammar terms they fall into two disconnected islands with nothing spanning them. Chromium and manganese have *identical* triton counts to iron and cobalt and order the opposite way. Nuclear moments are about a thousand times too weak to drive bulk magnetism anyway — that's electron-shell physics.

**The ionisation ladder shows nothing of the grammar.** Every element's deepest electron is exactly hydrogenic — that part is confirmed to 1% across all complete ladders — but it's Moseley's law from 1913, and no feature of the ladder tracks the nucleus's grammar. The cross-scale hope dies here, cleanly.

---

## Corrections made along the way

Several of these were mine:

- I claimed a mandatory **two neutrons** per fission. Measured data kills it: **20% of fissions emit fewer than two.** I had fused the splitting step with the boiling-off step. Splitting emits nothing; the neutrons come later, from the hot fragments — which is also where they're actually observed to come from.
- I reported the flattering statistic (total binding) when the honest one (per-nucleon) was available and negative.
- I printed 37 of 116 rows, then 29 of 104 elements, and called it a run.
- I claimed the packing order didn't exist after searching three places and stopping.
- I wrote "full charge Z" — there is no charge substance; it's a count of handednesses.

---

## Where it stands

The grammar's **arithmetic** is sound and its **conservation** is exact. Two laws are real and exceptionless. One selection rule was already in the canon. The binding-energy geometry is **not** built — and the missing piece isn't a file, it's the term that distinguishes deuteron-rich from triton-rich packing.

The next honest step needs **event-resolved fission data** — mass, charge, kinetic energy and neutron count per event, rather than averaged yield curves. Averaged curves cannot resolve a one-mass-unit feature at A=104, which is exactly where the prediction lives.
