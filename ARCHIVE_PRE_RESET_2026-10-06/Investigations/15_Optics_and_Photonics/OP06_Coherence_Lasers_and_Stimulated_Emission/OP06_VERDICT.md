# OP06 — Verdict: Coherence, Lasers and Stimulated Emission

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-04 · Tool: `op06_phase_lock.cpp` (exit 0; stdout in `results.txt`)

## Earned (real stdout; no Fock states, no boson postulate, no quantised mode anywhere)

- **g²(0) as lock-vs-independence:** independent random-phase emitters give g²(0) = 2.0000
  (2 − 1/N target 1.9950); phase-locked give 1.0000. The 2-vs-1 discriminator falls out of WHETHER
  the emissions are locked — no bunching axiom written anywhere.
- **Threshold:** excitation clamps at κ/G to 0.010% above threshold; output linear above
  (R² = 1.000000); knee contrast ×1504 across 0.8→1.6 P_th. Turn-on is exactly gain = loss.
- **Schawlow–Townes scaling:** phase diffusion of the lock from residual random dumps gives
  Δν ∝ 1/P with exponent −0.992 (gate −1 ± 0.1); simulated diffusion within 1–6% of the
  kick-ledger R_sp/(2A²).
- **Coherence time:** field autocorrelation e-folds at 7865 ticks vs 2/D = 8425 (6.6%), giving
  L_c = c·τ_c ∝ P from the same walk.

## Owed (the honest caps and opens)

1. **CLASS: CONVERGENCE.** g² = 2/1 from summed-register statistics is the classical HBT account;
   the rate-equation structure is generic population bookkeeping. Nothing here required SDT — and
   nothing here required bosons either. Both stories cover this ground; the discriminators lie elsewhere.
2. **Antibunching (g²(0) < 1) is the real quantum discriminator** — unreachable by ANY classical
   summed-field model including this one. SDT's candidate mechanism (single-vortex re-arm dead-time
   between dumps) is native in kind but NOT built here. **The make-or-break follow-up.** Not gated,
   not legislated (§G): logged as the measured fact the lock model must face.
3. **F4 (order parameter ≡ CM01):** structural narration, untested here — OPEN.
4. **Absolute ST prefactor:** hangs on the hν emission quantum → **FLM12/ℏ-entry root** (same debt
   as OP05). Deliberately NOT gated — gating it would smuggle the ℏ debt in as if paid.

## §D seven questions (on the antibunching OPEN — the sharpest row)

1. **Why open?** A classical sum of independent-or-locked registers has ⟨I²⟩ ≥ ⟨I⟩² always;
   g² < 1 needs anti-correlated emission events — a dead-time, not a phase relation.
2. **Recoverable?** Candidate: one vortex cannot dump twice within its re-arm time (a mechanical
   refractory period). That produces g²(0) → 0 for a single emitter natively.
3. **Fail to account for?** Emission as a depletion event on a SINGLE emitter — this tool's field
   is an ensemble sum.
4. **Errored premise?** None yet; the untested premise is that the re-arm dead-time reproduces the
   measured single-emitter g²(τ) curve shape (rise time = re-excitation rate).
5. **Freedom?** The vortex re-arm time — native (the excited state's rebuild tick count), no knob.
6. **Native or knob?** Native in kind; magnitude will need the emitter's rebuild dynamics (Law VI).
7. **Cascade?** Distinct from the OP-root and FLM12 roots — this is its own follow-up (single-vortex
   dead-time tool); the PREFACTOR debt cascades to FLM12/ℏ-entry.

**Recovery grade: PARTIAL** (native route named for antibunching; not built).

## Generative questions logged

Q3 (smooth 2→1 crossover through threshold): the lock model predicts it and the machinery here can
compute it — good follow-up, not run. Q4 (antibunching): sharpened into the dead-time tool above.
Q1 (laser threshold as CM01 critical point): untested narration, OPEN.

---

**Prompt completion C · Physics class CONVERGENCE · Recovery PARTIAL · Cascade root: FLM12/ℏ-entry (ST prefactor, shared with OP05); antibunching = independent named follow-up**
