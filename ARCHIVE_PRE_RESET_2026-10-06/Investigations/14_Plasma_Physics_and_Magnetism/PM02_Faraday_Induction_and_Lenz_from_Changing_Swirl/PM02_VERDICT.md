# PM02 — Verdict: Faraday Induction and Lenz from Changing Swirl

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-04
**Tool:** `pm02_faraday.cpp` (MSVC, real run, exit 0) → `pm02_results.txt` (both runs kept)
**Pre-commitments:** `RUN_LOG.md` (+ ADJ-1, bracket-only, gate unchanged).

---

## 1. Deciding metrics

| Phase | Gate | Result | Class |
|---|---|---|---|
| P1 | Φ count-route vs area-route <1% | 3.1e-5 / 1.7e-4 (full + partial enclosure) | **NATIVE** — Φ IS the enclosed wake-circulation count (κ quanta) |
| P2 | EMF residual <1%; turns ratio exact | 1.6e-9; N₂/N₁ exact by count linearity | IDENTITY (pre-flagged: Stokes' theorem — not counted as physics) |
| P3 | Lenz sign | K1/K2 dichotomy ran as committed: **K1 (co-drag) → flux amplification at L_g=0.5, RUNAWAY at L_g=2 (throughput created → KILLED)**; **K2 (reactive) → opposes 4/4, decays, stored energy dissipated** | **CONVERGENCE (energy-fixed)** — see §2 |
| P4a | motional ≡ transformer <1% | 0.0 (by construction at count-kinematics level — flagged; both EMFs are the same object, d/dt of enclosed count) | NATIVE-kinematic; force-level identity HG-1-blocked |
| P4b | eddy drag ∝ v, opposes, slope 1.0±0.1 | opposes 4/4 speeds; slope **0.992** in the committed quasi-static bracket (ADJ-1 disclosed; first bracket hit the real saturation crossover, slope 0.372, kept in results) | NATIVE-mechanism, coefficient = FD02 η (identified, not derived) |

## 2. The load-bearing honesty (P3): where the minus actually comes from

The prompt's own pivot row pre-labelled this outcome: *"sign only closes via energy argument → mark
CONVERGENCE (energy-fixed), not NATIVE."* That is what happened. Occlusion handedness alone cannot
select K2 over K1, because the carrier–swirl coupling sign is the HG-1 bilinear gain (PM01). What the
run DID establish natively: the co-drag alternative is not merely wrong-signed but **structurally
forbidden** — it admits configurations (self-inductive feedback L_g·g² > m) where throughput is
created from a seed perturbation. Lenz's minus = the unique passive branch of the relay ledger.
"No perpetual motion" and "throughput is conserved" are one statement here (prompt's generative Q1:
answered yes, at the level of this model).

### §D seven questions (on the P3 not-NATIVE outcome)

1. **Why?** The sign chain needs the carrier's drive rule under changing swirl; both linear rules
   (±g∂w/∂t) are handedness-consistent; only the ledger discriminates (K1 runaway: I → 1e6 seed-fed).
2. **Recoverable?** Yes, iff HG-1 closes: a derived bilinear grip fixes the drive-rule sign without
   invoking energy.
3. **Target failed to account for:** the drive-rule sign is not in EMC03's static surplus/deficit
   result; it is a dynamic coupling property.
4. **Errored premise:** "the induced wake must occlude the change *because of handedness*" — the
   necessity is real but its source is conservation, not handedness (today).
5. **Freedom:** the HG-1 coefficient g_hb with a derived sign.
6. **Accounting:** native candidates = PPT06 ℓ=2 traction gearing; FLM14 rotation-DOF constraint
   channel. Currently unbuilt.
7. **Cascade?** YES — root **HG-1** (shared with PM01 P3, PM04 gain, PM06 gain).

**§G-3:** "sign not native" is proven inside the linear one-channel coupling class; re-open
condition: a derived HG-1 sign. **§G-1 faith ledger:** L_g > 0 (self wake-overlap positivity) is
taken from PM01 geometry, named here; the ledger-closure arithmetic is structural to the EOM and was
pre-flagged, not claimed as discovery.

## 3. Generative questions logged

- Inductance-as-wake-overlap (prompt Q3): L_g entered as exactly that — a geometric overlap factor;
  a quantitative wake-overlap computation is a clean follow-up (no blocker).
- Eddy dissipation = FD02 η (prompt Q4): the identification is used and named, not derived.
- New from run 1: the drag saturation at v·τ ≳ fringe width is real brake physics (force peaks then
  flattens) — falls out of the same two-parameter model; worth a data comparison someday.

## 4. Verdict

> **Prompt completion C** · **Physics class** NATIVE (Φ-as-count; count-kinematic unification;
> drag mechanism) / CONVERGENCE (Lenz minus, energy-fixed — as the prompt's own pivot anticipated) /
> IDENTITY (P2, pre-flagged) · **Recovery** PARTIAL (premise named: HG-1 sign; freedom not yet
> justified) · **Cascade root** HG-1.
