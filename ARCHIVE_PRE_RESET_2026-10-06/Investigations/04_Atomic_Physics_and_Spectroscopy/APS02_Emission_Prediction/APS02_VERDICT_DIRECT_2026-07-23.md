# APS02 — Direct re-run verdict (2026-07-23)

> **Run class: DIRECT** (main session, no agents). No prior outcome files existed to delete.
> Prompt = category-root `PROMPT_all_emissions_from_first_principles.md` (APS02 = drag-factor
> stage). Tool: `aps02_emission_engine.cpp`, g++ 15.2 -O2, exit **0**.
> Output: `aps02_rerun_2026-07-23.txt`.

## What the re-run measured

Drag factor D = λ_meas/[(8/3)·λ_C·k²] across 36 elements (measured λ + measured IE₁ → k):

| outer-shell count | ⟨D⟩ | reading |
|---|---|---|
| 1 (lone opener) | **1.766** | most drag |
| 2 (paired s) | 1.405 | |
| 3–7 | 1.395 → 1.073 | monotone descent |
| 8 (full shell) | **1.021** | near-perfect drafting |

Monotone in outer-shell occupancy across the whole table — zero inversions in the class means.

## Verdict

- **Prompt completion: B** · **Physics class: OBSERVED-pattern (honest diagnostic)** — D is a
  *ratio built from measured λ*, so individual D values are diagnostics, not predictions. The
  **finding** is the monotone shell-occupancy law itself: emission drag tracks void occupancy
  exactly as the drafting picture requires. Forward prediction λ = (8/3)λ_C·k²·D(outer) requires
  deriving D(outer) from void geometry — **OPEN** (this is APS03 §7.3's ξ_atomic deliverable).
- **Recovery:** n/a · **Cascade root:** none.
