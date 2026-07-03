# VERDICT — GOM10: Three-Body Lagrange Points from Koppa

> **Author:** J. C. Harvey, Melbourne. **Executed:** 2026-07-03 (HUNTER discipline).
> **Tool:** `gom10_lagrange.cpp` — compiled AS-IS (zero edits), MSVC 19.44, exit 0.
> **Evidence:** `results.txt` (real stdout), `RUN_LOG.md` (pre-committed gates).

## Dual verdict

- **Prompt completion: B** (L1–L5 for Sun–Earth, Earth–Moon, Sun–Jupiter delivered;
  stability criterion delivered; shadow-cone force row is defective; full SEM
  superposition map only sketched as a 1-D slice)
- **Physics class: IDENTITY (the μ substitution) + CONVERGENCE (all L-point positions)
  + one OBSERVED anchor (Trojan existence) — no NATIVE content**
- **Earned vs owed: the koppa-language restatement is earned and clean; any claim that
  SDT "solves" or "tames" the three-body problem is NOT earned (see §4)**

## What is IDENTITY (labelled, per the PROMPT's own admission)

μ_ϟ = ϟ₂/(ϟ₁+ϟ₂) with ϟ = v²R/c² is numerically M₂/(M₁+M₂) because ϟ ≡ GM/c²
(bridge law — sanctioned, disclosed CONVERGENCE with the Newtonian gravitational
parameter). The solver `f_rot(x, μ)` is the classical circular-restricted-three-body
collinear equation, verbatim, with μ_ϟ substituted. Therefore every position below is
the classical CR3BP result re-expressed in koppa notation — **not an independent SDT
prediction**. That is the honest deliverable, and it is delivered.

## Real numbers (from `results.txt`)

| Check | SDT/koppa | Observed/classical | Err | Verdict |
|---|---|---|---|---|
| Sun–Earth L1 | 1,490,933 km | ~1.4915e6 km (SOHO region) | ~0.03% (−0.60% vs rounded 1.5e6) | CONVERGENCE, PASS |
| Sun–Earth L2 | 1,500,905 km | ~1.5e6 km (JWST) | +0.06% | CONVERGENCE, PASS |
| Earth–Moon L1 | 58,026 km | ≈58,000 km | +0.04% | CONVERGENCE, PASS |
| L4/L5 geometry | 60.00°, r/a = 1.00000000 | 60° equilateral | exact | geometric necessity, PASS |
| Kepler period from Ω=√(c²Σϟ/a³) | 365.07 d (SE), 27.29 d (EM) | 365.25 d, 27.32 d | ~0.05–0.1% | CONVERGENCE (same GM identity) |
| Routh stability μ < 0.0385 | SE 3.00e-6, EM 1.22e-2, SJ 9.32e-4 → all stable | Jupiter Trojans exist (>10,000 known); Earth Trojan 2010 TK7; Moon L4/L5 Kordylewski clouds | — | **OBSERVED anchor, PASS** — the one genuinely non-identical check: koppa-built μ lands on the correct side of the stability boundary for every system with observed Trojan populations |
| μ_ϟ vs mass ratio (committed 0.1%) | 2.99961e-6 | 3.00327e-6 (IAU GM) | **−0.122%** | **FAIL at the committed gate** — traced to 3-s.f. rounding of v_surf inputs (437,000 m/s), not a bridge systematic; INCONCLUSIVE at this input precision, gate not widened |
| "F₁₂ = c²ϟ₁ϟ₂/D²" printed as N | 2.63e-05 "N" | true F(SE) ≈ 3.5e22 N | — | **DEFECT: dimensionally not a force** (c²ϟϟ/D² is m²/s²). Pre-flagged in RUN_LOG before run; the tool's own comments admit it. Does not feed the L-point solve. |

## What is NOT earned

1. **"The three-body problem becomes DETERMINISTIC / tractable" (PROMPT §2.3):** nothing
   in the tool tests this. The tool solves the *restricted* problem with the *classical*
   equation. Chaos in the full three-body problem is a property of the equations, and the
   koppa equations are numerically the same equations. This claim is rhetoric until an
   SDT-specific regularisation is exhibited and tested. **KILLED as stated; would need
   its own investigation with a committed discriminator.**
2. **"No G, no M anywhere":** literally true of the symbols, but ϟ carries GM's value.
   Correct label is CONVERGENCE, and the run keeps it.
3. Tool policy defect: local `constexpr double c` and hand-typed (v, R) constants instead
   of `#include <sdt/laws.hpp>` — violates the header rule in the PROMPT. Values match
   laws.hpp to the printed digits, so results stand, but the defect is logged.

## Disposition

The honest content of GOM10 is: **the entire restricted three-body geometry can be
written with ϟ = v²R/c² as the only body-descriptor, with the identity μ_ϟ = μ_mass
labelled, and the Routh criterion 27μ(1−μ) < 1 lands correctly against the observed
Trojan populations using koppa built purely from (v_surf, R).** That is delivered.
The μ-vs-mass-ratio falsification check needs higher-precision v_surf inputs (from
laws.hpp/ephemeris-grade values) before it can pass its own 0.1% gate — left OPEN.

## §D — Seven questions (on the failed μ_ϟ gate and the killed §2.3 claim)

1. **Why (exact mechanism)?** μ_ϟ(SE) = 2.99961e-6 vs μ_mass = 3.00327e-6: **−0.122%**
   against a 0.1% gate. Driver: ϟ_Sun = 1478.235 m from the hand-typed v_surf = 437,000
   m/s (3–4 s.f.) vs 1476.63 m from IAU GM; a 0.055% velocity error doubles to 0.11% in
   v². The killed §2.3 claim ("three-body becomes deterministic") failed by absence: no
   computation in the tool addresses it.
2. **Recoverable?** The gate: yes — trivially, with ephemeris-grade v_surf (the required
   precision is ~1 part in 1e4 on v). The §2.3 claim: only by a new investigation with a
   committed chaos discriminator; nothing to recover in this tool.
3. **What did the target fail to account for?** Input significant figures: a sub-0.1%
   falsification test cannot be fed 3-s.f. constants. (And §2.3 failed to account for
   chaos being a property of the equations, which koppa re-notation does not change.)
4. **Errored premise?** "Rounded textbook v_surf values are adequate inputs for a 0.1%
   bridge-law test." NOT the bridge law itself — the residual is fully explained by input
   rounding, so no bridge systematic is indicated (also why this is not RETRO-PASSed:
   the gate stays failed until clean inputs are run).
5. **Correcting freedom?** Input provenance — pull (v_surf, R) from laws.hpp/ephemeris
   sources at ≥6 s.f. A data-quality freedom, pre-justified, not fitted to the target.
6. **Native or knob?** Native (measured values at better precision). Zero CALIBRATED spend.
7. **Cascade?** **Yes.** Same root as GOM12's Kepler-check and ϟ_Sun-invariance failures:
   rounded 3–4 s.f. kinematic tables feeding sub-0.1% gates. Root logged once as
   **INPUT-PRECISION** (pay it by building one ephemeris-grade input block; clears the
   GOM10 μ_ϟ gate and GOM12 gates 2–3 together).

**Recovery grade: PARTIAL** (freedom identified and native; clean-input re-run not
executed here). The §2.3 tractability claim: **NO RECOVERY** as stated.

---

**Prompt completion B · Physics class IDENTITY (μ substitution) + CONVERGENCE (L-points,
Kepler) + OBSERVED anchor (Trojan stability) · Recovery PARTIAL · Cascade root
INPUT-PRECISION.**
