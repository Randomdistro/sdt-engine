# VERDICT — GD04: 3D Volumetric Integration

> **Author:** J. C. Harvey, Melbourne. **Executed:** 2026-07-03 (HUNTER audit re-run).
> **Tool:** `gd04_3d_volumetric_integration.cpp` — compiled AS-IS (zero edits), MSVC 19.44,
> exit 0. **Evidence:** `results.txt` (real stdout), `RUN_LOG.md`.

## Dual verdict

- **Prompt completion: F** (against its own PROMPT §15: criterion 2 "LSB galaxies no
  longer fail" is met only in the letter — they return nonzero velocity — while missing
  observation by 90–98%; the model does not describe the data)
- **Physics class: KILLED — and the tool's own verdict line is INFLATED**
- **Superseded by: GD05 twin-regime (RMS 23.8%, BTFR 3.58) — do not rerun GD04**

## What the tool actually shows (real output, 2026-07-03)

| Galaxy | Class | V_obs (km/s) | V_SDT (km/s) | Residual |
|---|---|---|---|---|
| NGC 6503 | HSB | 116.0 | 65.4 | +43.6% |
| NGC 3198 | HSB | 150.0 | 79.3 | +47.2% |
| NGC 2403 | HSB | 131.0 | 49.1 | +62.5% |
| UGC 128 | LSB | 64.0 | **3.7** | **+94.2%** |
| NGC 7331 | Massive HSB | 240.0 | 176.6 | +26.4% |
| NGC 2998 | Massive HSB | 213.0 | 99.7 | +53.2% |
| NGC 801 | Massive HSB | 218.0 | 83.3 | +61.8% |
| DDO 154 | Dwarf | 47.0 | **1.1** | **+97.7%** |
| NGC 3741 | Dwarf | 50.0 | 2.4 | +95.1% |
| IC 2574 | LSB | 67.0 | 6.7 | +90.1% |

**RMS residual: 71.39%. Max: 97.70%.** Systematic: every galaxy is under-predicted; the
lighter and more diffuse, the worse — exactly the regime the 3D column was built to fix.

## The inflation, precisely

1. The tool prints `[SUCCESS] LSB galaxies like UGC 128 and IC 2574 survived!` because of
   `if (predicted_velocity_m_s > 10.0)` — a **10 m/s** gate on a quantity whose own inline
   comment says "Should be ~64 km/s". Any nonzero output passes. UGC 128's 3.7 km/s
   (94% miss) is stamped a success.
2. The second gate `if (rms_err < 30.0)` simply prints nothing when it fails — there is
   no `[FAILED]` branch for RMS. The run therefore ends on a lone [SUCCESS] banner above
   a 71% RMS table. **Silence-instead-of-FAIL is a retro-gate by omission.**
3. This matches the 2026-07-02 scour finding verbatim. The honest reading of the same
   stdout is: the 3D volumetric single-regime model is **falsified on its own sample**.

## Disposition

- Class **KILLED** as a rotation-curve model: replacing the 2D Σ-threshold with the 3D
  radial column does move LSB predictions off exactly-zero (the only literal success),
  but the velocities produced are 10–30× too small — the mechanism, at this
  normalisation, does not carry the phenomenon.
- The kill is clean, not re-homed: no parameter here should be retuned to "rescue" it.
  GD05's twin-regime engine (bulge⊕disk, convergence-floor law M4) is the successor and
  already exists; GD05's own caveat (crossover borrowed MOND-simple) is recorded there.
- The `[[deprecated]]` markers already on `predicted_velocity_3d` in galactic.hpp are
  correct and should stay.
- Historical note: the PROMPT's §13 "must prove LSB galaxies do not return r_sat = 0"
  was achieved; everything beyond that line was aspiration the run never earned.

## §D — Seven questions (on the RMS-71% kill and the inflated gates)

1. **Why (exact mechanism)?** Systematic under-prediction, worst where the model was
   built to win: every LSB/dwarf misses by 90–98% (UGC 128: 3.7 vs 64 km/s; DDO 154:
   1.1 vs 47), best HSB still +26%. Two coupled causes in `predicted_velocity_3d`:
   (i) the eclipse fraction uses τ = κ_per_baryon·Λ/m_p with κ = 9.1e-29 m² — a
   constant **calibrated to the MW Σ_sat threshold** (the header says so), so diffuse
   columns land far below saturation; (ii) the amplitude v_lim² = c²·ϟ_gal/(2r) ties
   the ceiling to enclosed koppa alone, single-regime. Result: RMS 71.39%, max 97.70%.
   The [SUCCESS] stamps are separate faults: a 10 m/s gate (6,400× under the tool's
   own target) and a silent no-FAIL branch on RMS.
2. **Recoverable?** Not by tuning κ — that is the FISHED-RECOVERY trap. Recovery
   requires deriving the per-baryon occlusion cross-section (or the correct
   saturation law) natively. GD05's twin-regime engine partially pays this (RMS
   23.8%) but itself carries a borrowed-crossover caveat — the root is still open.
3. **What did the target fail to account for?** That a single calibrated cross-section
   cannot serve both compact and diffuse columns; and that its own PROMPT's
   zero-parameter doctrine (§5: "SDT may derive κ_per_baryon") was never executed —
   κ was calibrated, not derived, which is a §A PLUG.
4. **Errored premise?** "Single-regime eclipse saturation with an MW-anchored κ
   carries the full rotation amplitude." The deeper premise: that κ_per_baryon could
   be postponed — it is the load-bearing unknown, and everything downstream of it is
   numerology until it is derived.
5. **Correcting freedom?** The occlusion transfer function derived from lattice
   mechanics (the same freedom GD03 §D names). Per the Closure Principle the constant
   is a closure debt: derive it or the model stays dead — deleting it (or hiding the
   miss behind a 10 m/s gate) is amputation/fake-pass, both already committed by this
   tool and now on record.
6. **Native or knob?** As shipped: knob (calibrated κ + fake gate). The required
   correction is native-in-kind and unbuilt.
7. **Cascade?** **Yes.** Same root as GD03's forward models and GOM13's G1/G2 fork:
   **OCCLUSION-MECHANISM** (the un-derived per-mass occlusion coefficient/transfer
   law). GD05 is the current best stand-in, not the payment.

**Recovery grade: NO RECOVERY** (as built — the kill is clean and must not be
re-tuned; the root is owed at OCCLUSION-MECHANISM, partially serviced by GD05).

---

**Prompt completion F · Physics class KILLED (falsified on its own sample; INFLATED
[SUCCESS] stamps documented) · Recovery NO RECOVERY (superseded by GD05) · Cascade
root OCCLUSION-MECHANISM.**
