# QM03 — VERDICT: Tunnelling as Wake Leakage

**J. C. Harvey, Melbourne — 2026-07-04.**
Tool: `qm03_wake_leakage.py`. Real stdout: `qm03_results.txt`. Pre-commitments: `RUN_LOG.md`
(frozen before coding; ADJ-1 = two P0-class tool faults fixed after first run — a fm→Å factor and
a mis-specified Phase-5 observable — both logged with the first-run numbers preserved; no
threshold moved).

## What the machinery produced (firewall held: the solver never saw WKB)

The solver knows only a relay chain and a pinning rate Ω(x) raised inside a slab (occlusion depth).

1. **Evanescent decay is native and measured.** Field-profile fits give κ_meas = κ_lattice
   (= 2 asinh(√(Ω_c²−ω²)/2), from the same lattice recursion) to 0.13% worst case. Gate P1 PASS.
2. **The Schrödinger evanescent constant is the NR LIMIT of the native form** — a convergence,
   not a source: κ_native² = 2m(V−E)·(1 + (V+E)/2mc²). At V,E ≪ mc² this is √(2m(V−E))/ℏ to
   0.037%. **Prompt-Q1 answered: SDT predicts a high-barrier departure from the WKB form at
   V,E ~ mc² — a falsifiable fork, not a degeneracy.**
3. **Transmission:** ln T linear in d; slope = −2κ_native to 0.20%; prefactor 3.90 vs the
   16E(V−E)/V² = 4.00 comparison (2.5%). The −2 is amplitude→energy-density (the elastic square —
   QM04's Phase 1, machinery). Gates PASS.
4. **STM:** native κ with measured m_e, φ = 4.5 eV → κ = 1.087 Å⁻¹ → **0.94 current decades per
   Å** (gate [0.5,1.5] PASS).
5. **Geiger–Nuttall, zero fitted parameters:** leakage integral over the Coulomb-occlusion slope +
   mechanical assault rate f = v/2R: R² = 0.9997 linearity, predicted slope within 3.4% of the
   measured-data fit, worst nuclide 0.54 decades over 24 decades of half-life (Po-212 → Th-232).
   Gates PASS. (Q,T½ values = standard-table OBSERVED anchors; verify vs ENSDF before publication.)
6. **Traversal time (candidate NATIVE, FLM14 ADJ-7):** total traversal saturates —
   τ_tot = 400.0 ticks independent of d from 2κd = 8.5 to 68 (and 400.0 ≈ 2/(κ·v_g) = 400.6,
   0.15% — the saturation value has a closed lattice form). d/c crossover at d ≈ 480: beyond it
   the leaked *constraint* arrives ahead of any pulse over the same span. Under the two-channel
   doctrine this is a native outcome to hold against attoclock/Hartman DATA (measured near-zero
   tunnelling delay), not a paradox to suppress. Pulses outside the slab stay at c throughout.

## The located ℏ entry point

**One bridge, same as QM02:** Ω_m = mc²/ℏ (the vortex's internal rest rate — the E = ℏω
identification). It converts lattice rates to lab units for STM and α-decay. Everything
dimensionless (exponential form, NR convergence, saturation, linearity) is ℏ-free machinery.
Cascade root: **WAKE-DISPERSION**.

## What is NOT paid here (honest scope)

The run derives the **field** leakage and its intensity ratio T. The step "T is the fraction of
*vortices counted* on the far side" (re-seeding) is the residence law — the same open closure as
QM04/QM05/QM07. Until FLM14 rule-form-4 lands, T-as-particle-count is DEFERRED. Root:
**RESIDENCE-LAW**.

## HUNTER §D — seven questions (on the open re-seeding step)

1. **Why open?** The solver produces a leaked field amplitude; nothing in it counts discrete
   vortex arrivals. The count step was never claimed — it is absent machinery, not a miss.
2. **Recoverable?** Yes pending FLM14 rule-form-4 (the residence/landing law in flight).
3. **Failed to account for?** How a steered vortex commits to the far side when the leaked wake
   is weak — the engagement threshold.
4. **Errored premise?** None demonstrated; a closure debt.
5. **Freedom?** The landing weighting (count vs energy density).
6. **Native or knob?** Native candidate (energy-density residence); nothing tuned here.
7. **Cascade?** YES — RESIDENCE-LAW (with QM04, QM05, QM07). The ℏ bridge cascades to
   WAKE-DISPERSION (with QM01, QM02).

**Recovery grade: PARTIAL** (both roots named, owned elsewhere; everything claimable here earned).

## New questions logged

1. The τ_sat = 2/(κ v_g) closed form: does it survive with real wave-packets (time-domain sim)?
2. The high-barrier fork: is there a nuclear or condensed-matter system with V ~ mc² where the
   (1+(V+E)/2mc²) correction is measurable? (Positron/heavy-ion regimes?)
3. Occlusion saturation (g→2 near contact) as a hard leakage cutoff — not tested here; would
   modify the deepest-barrier end of Geiger–Nuttall.

---
**Prompt completion B · Physics class CONVERGENCE (native leakage machinery; WKB = its NR limit;
one flagged ℏ bridge; count step deferred) · Recovery PARTIAL · Cascade roots WAKE-DISPERSION +
RESIDENCE-LAW**
