# GOM42 — Koppa N-body integrator (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the next step. The 2026-08-15 registration is kept below the line, superseded where stated.

## 1. State after the reset run (`GOM42_RESET_ASSESSMENT_2026-10-10.md`)
A fresh velocity-Verlet instrument with a = c²Σκ_j(r_j − r_i)/r³ (no softening, collision stop) meets:

| gate | result |
|---|---|
| V0 symmetry | met |
| V1 circular, 100 periods | 4.9e-6 drift |
| V2 order | ratio 4.000 |
| V4 figure-eight | 5e-8 |
| V5 invariants | ~1e-14 |
| V6 collision stop | met |
| **V3 Lagrange equilateral, equal sources, 20 periods** | **not met** (side drift 4.03) |

**Grade:** VERIFICATION. The instrument is validated.

## 2. Errors, and what each teaches
| # | Error | Lesson |
|---|---|---|
| X1 | V3's known answer is **physically unstable**. Equal-source Lagrange triangles violate Routh's criterion, 27(m₁m₂ + m₂m₃ + m₃m₁) < (Σm)². Round-off grew exponentially: 1.2e-6 at 2 periods, then 2.87 at 10. | A known answer used for validation must be dynamically stable, or run only inside its pre-instability window. Check stability before registering it. |
| X2 | Attempt 1's V6 stop left drifted positions in place (overlap 7.8e-5): an instrument fault, fixed by restoring the pre-step state. | Collision handling must be state-restoring. |
| X3 | The 2026-10-05 correction asked for a numeric **physics** gate on a measured system; none was registered. | A validated integrator still says nothing about SDT until it predicts a measured system with native inputs. |

## 3. Round 2 (to register before running)
- **V3′ (stability-correct):** a Lagrange triangle with sources (1, 0.01, 0.01), which meets Routh (27 × 0.0201 = 0.543 < 1.040). Gate: side drift ≤ 1e-4 over 20 periods.
  - The equal-source triangle is also reported within ≤ 2 periods. That is post-seen (drift 1.2e-6 was printed), so it is a diagnostic only.
- **P1 (physics, native inputs only):** Sun–Jupiter–Saturn, with each κ from its own satellite or planet orbit via v²r = c²Ѻ; no GM.
  - Observable: the Jupiter–Saturn long-period mutual term (the "great inequality"). Its period and amplitude are to be sourced from the ephemeris literature, with provenance written into `Datasets/` **before** registration. The value is not to be recalled.
  - Gate: period within 2%.
  - **Label:** convergent with Newtonian N-body at this order (same 1/r² law), so the test is of the native Ѻ inputs and the integrator, not a discriminator.

## 4. Prohibitions
- No G, GM, M or softening.
- No target trajectory.
- No unstable known answer as a validation.

---

## Superseded registration (2026-08-15, kept as written)

# GOM42 — Koppa N-Body Integrator

**Author:** James Christopher Tyndall, Melbourne  
**Status:** PRE-REGISTERED · INSTRUMENT RUN — assessment VALIDATED NUMERICAL INSTRUMENT (see GOM42_ASSESSMENT.md; V5a, V5b and V6 gates pass in gom42_results.txt) [status line corrected 2026-10-05]  
**Date:** 2026-08-15

## Question

Can one shared two- or three-dimensional trajectory engine integrate the SDT
koppa acceleration

\[
\mathbf a_i
=c^2\sum_{j\ne i}\kappa_j
\frac{\mathbf r_j-\mathbf r_i}{|\mathbf r_j-\mathbf r_i|^3}
\]

without importing \(G\), source mass \(M\), \(GM\), force softening, or a
target trajectory?

This is a numerical initial-value solver. Passing the gates below does not
constitute a closed-form solution of the general three-body problem.

## Registered inputs

- `sdt::laws::measured::c`
- `sdt::laws::bridge::koppa_per_baryon`
- Per-body baryon count, or the equivalent source length
  \(\kappa=N_b\kappa_b\)
- Initial position and velocity
- Collision radius, used only as an explicit stop boundary

No weighed source mass is an input. Koppa is the sole source strength and is
also the inertial weighting in the conservation diagnostics.

## Instrument

- Pairwise central acceleration evaluated symmetrically
- Velocity-Verlet stepping
- The same `Vec3` state with `z=0` for two-dimensional runs
- No Plummer softening and no hidden minimum denominator
- A step is rejected if two supplied collision boundaries overlap

## Diagnostics

\[
\mathbf P_\kappa=\sum_i\kappa_i\mathbf v_i,\qquad
\mathbf L_\kappa=\sum_i\kappa_i(\mathbf r_i\times\mathbf v_i)
\]

\[
\mathcal E_\kappa
=\frac12\sum_i\kappa_i|\mathbf v_i|^2
-c^2\sum_{i<j}\frac{\kappa_i\kappa_j}{r_{ij}}.
\]

These are koppa-weighted numerical invariants. They are proportional to the
usual mass-weighted invariants by one common conversion and do not introduce
a mass primitive.

## Validation gates

All thresholds are fixed before the implementation is run.

1. **V0 — pair symmetry and dimensions.** For an isolated pair,
   \(\kappa_1\mathbf a_1+\kappa_2\mathbf a_2=0\) to relative
   \(10^{-14}\). Acceleration must scale as \(r^{-2}\).
2. **V1 — circular two-body limit.** Run 100 periods with
   \(\Delta t=P/2000\). Maximum separation drift must be
   \(\le 5\times10^{-5}\); relative energy drift must be
   \(\le 5\times10^{-6}\).
3. **V2 — second-order convergence.** On the same two-body orbit, halving
   the timestep must reduce the final-state error by a factor of at least
   3.5.
4. **V3 — Lagrange equilateral solution.** Three equal koppa sources run
   for 20 periods at \(\Delta t=P/4000\). Maximum side-length drift must be
   \(\le 10^{-4}\), and barycentre drift must be
   \(\le 10^{-10}\) of the side length.
5. **V4 — figure-eight choreography.** With the published dimensionless
   initial state rescaled only by \(L\) and
   \(T=\sqrt{L^3/(c^2\kappa)}\), one period at
   \(\Delta t=P/50000\) must close with RMS position and velocity errors
   each \(\le 2\times10^{-5}\) of their registered scales.
6. **V5 — invariants.** Across V1, V3 and V4, normalized
   \(\mathbf P_\kappa\) drift must be \(\le10^{-11}\) and normalized
   \(\mathbf L_\kappa\) drift \(\le10^{-10}\).
7. **V6 — collision behavior.** A head-on pair must stop at its supplied
   contact boundary. The instrument must not continue through a zero
   denominator.

## Rejection criteria

The instrument is rejected if any gate fails, if a run requires a
case-specific timestep correction, if softening is introduced to rescue a
trajectory, or if any source strength is reconstructed through \(G\), \(M\),
or \(GM\).

## Whole-range rule

Each validation trajectory is executed once at its registered timestep. The
convergence gate alone uses the declared timestep pair; no mid-run adjustment
or body-specific retuning is permitted.

---

## Audit correction 2026-10-05 (record / status)

**Finding:** The status line says "INSTRUMENT NOT YET RUN" while the folder holds results with V5a, V5b and V6 gates passed, and the prompt itself carries no numeric gates.

**Correction:** Update the status and copy the numeric gates from the output into the pre-registration.

**Status:** ANNOTATED — label, status or tally corrected in the record; no re-score of earlier runs.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
