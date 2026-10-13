# NP32 — cross-fissioner prediction, PRE-COMMITTED (fishbowl, written before any distribution opened)

> **Frozen before opening the 8-fissioner yield data.** Fable direct, 2026-07-25.
> Data to be used: `Datasets/nuclear/fission_yields/` (7 new) + `nuclear/IAEA_U235_*` (canonical).

## What is NOT being claimed (NP25 discipline)
NP25's grammar receipt (2d→α; Σn_t=n_t(P), Σn_d=n_d(P)−2) is a proven **IDENTITY-THEOREM** — it
holds for *every* admissible binary split, so **it cannot select which split occurs.** I do **not**
predict the mass distribution from the grammar. The full selection (minimum-cost cut) is NP32's
unbuilt core.

## The mechanism this prediction DOES come from (separate, and native)
This session's triton-contraction result (NP30 §11 / ATOMICUS rule): **a shell closure is the point
of maximal interleave-lock** — the boundary contracts hardest there (−17 mfm neutron, −25 proton),
i.e. it is the tightest, hardest-to-part region of the mesh. Applied to scission:
> **The cut cannot pass through the tightest lock. The heavy fragment forms *around* the N=82
> (and Z=50) interleave-lock; that lock sits at a fixed nucleon count regardless of the parent.**

This is **not** importing "magic 82" as a shell-model input (NP32 forbids that). The lock position
is the *output* of the contraction mechanism measured this session; here it is *used*, not fitted.

## Pre-committed predictions (checkable across the 8 fissioners)
Let A_H, A_L be the heavy/light **mass-yield peak centroids** (independent yields, Σ over Z at
fixed A → post-prompt-neutron primary fragments).

- **P1 — heavy peak STATIONARY.** A_H ≈ constant ≈ **138 ± 3** across all fissioners (the ¹³²Sn
  lock + a few neutrons), i.e. **|slope of A_H vs A_fiss| < 0.25**.
- **P2 — light peak SLIDES 1:1.** A_L ≈ A_fiss − ν̄ − A_H, so **slope of A_L vs A_fiss ≈ 1**
  (pre-commit band **0.7–1.3**). Light peak moves up ~Th 93 → Pu/Am ~100.
- **P3 — complementarity closes.** A_H + A_L ≈ A_fiss − ν̄, giving a back-computed ν̄ in the
  physical **1.5–4.0** range for every system (data-sanity gate; not a free fit).
- **P4 — the known break is expected, not fatal.** Th-232 (lightest parent) is documented to
  develop a **symmetric/third-peak** component; if its two-peak fit is poorest and its valley
  shallowest, that is the mechanism's own edge (the lock is relatively less dominant for the
  lightest parent), **pre-called here** so it cannot be spun either way.

## Falsifier (what kills the picture)
If A_H slides with A_fiss as steeply as A_L (both peaks symmetric about A_fiss/2 and both moving —
slope A_H vs A_fiss > 0.5), the lock-anchored-heavy-fragment picture is **REFUTED**.

## Honest SM status (stated up front)
Standard fission theory **also** predicts heavy-peak stationarity (via fitted shell corrections /
fragment deformation). So a PASS is **degenerate in VALUE** — not a fork. The SDT-native content is
only the **provenance of the anchor**: derived from the measured interleave-lock (this session),
not installed as a magic number. If it passes: **CONVERGENCE-in-value, native-in-mechanism.** If the
back-computed anchor needed tuning per fissioner → CALIBRATED, fail.

## Verdict slots (fill after data)
- P1 A_H slope vs A_fiss: ____ (gate <0.25) → [PASS/FAIL]
- P2 A_L slope vs A_fiss: ____ (gate 0.7–1.3) → [PASS/FAIL]
- P3 back-computed ν̄ range: ____ (gate 1.5–4.0) → [PASS/FAIL]
- P4 Th-232 poorest/shallowest? ____ → [as pre-called / not]
- Overall: [picture consistent / refuted] · label [convergence-native-mechanism / calibrated / dead]
