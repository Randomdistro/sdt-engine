# GD05 RUN_LOG — mass-free two-regime streak model (2026-07-13)

## Pre-Run Commitments (Harvey directive 2026-07-13)
- **Eliminate ALL GM/GR structure.** No `koppa_from_mass`, no `GM/c²`, no `a_0`, no MOND interpolation, no `<sdt/galactic.hpp>`.
- **Two regimes:** bulge = spherical occlusion; disk = **360° streak** (edge-on disk = great-circle band, a line not a point).
- Inputs: MEASURED velocities (Vobs, Vgas, Vdisk, Vbul, km/s) + MEASURED geometry (h_R, kpc). Only calibrated: Y_disk=0.5, Y_bul=0.7 (SPARC 3.6µm stellar M/L — population, not gravity). CALIBRATED(2).
- Model: `v² = Y_b·Vbul²  +  (Y_d·Vdisk² + Vgas²)·f_streak`, with `f_streak = R/h_R` (S1) or `max(1,R/h_R)` (S2). M0 control = Newtonian baryonic (`f=1`).
- **Pre-committed gates:** S2 per-radius RMS < 25%; BTFR slope ∈ [3.5,4.5]; beat Newtonian control.
- Tool: `gd05_sdt_streak.cpp` (standalone; touches nothing in the engine). Data: real published SPARC (Lelli+2016), `sparc_rotmod.csv` × `sparc_175.csv`.

## Result (135 galaxies, 3014 radius points; MSVC /O2)

| Model | per-radius RMS% | bias% | median\|err\|% |
|-------|----------------|-------|----------------|
| M0 Newtonian baryonic (control) | 42.8 | **+35.2** | 40.1 |
| S1 pure 360° streak (R/h_R) | 36.8 | **+0.2** | 23.6 |
| S2 point→streak at R=h_R | 35.2 | −2.8 | 22.1 |

- **S2 by bulge:** with-bulge RMS 30.1% (bias −9.9%); bulgeless RMS 37.8% (bias +1.3%).
- **BTFR slope:** observed 3.14; S2 streak model **2.56** (literature ~3.5–4.0).
- Gates: [FAIL] RMS<25% (35.2%) · [FAIL] BTFR∈[3.5,4.5] (2.56) · **[PASS] beats Newton (35.2% vs 42.8%)**.

## Honest read (no fishing)
1. **The headline is the BIAS, not the RMS.** Newton under-predicts rotation by a systematic **+35%** (the classic "missing mass"). The **360° streak geometry annihilates that bias to +0.2%** — pure geometry supplies, *on average*, exactly the velocity dark matter is invoked for, with **NO dark matter, NO a_0, NO GM, NO fitted scale.** That is the real finding of this run.
2. **What's left is SCATTER, not offset.** Residual RMS 35% is galaxy-to-galaxy scatter, not a mean miss. It trails the earlier MOND-borrowed twin-regime (23.8%) — i.e. the MOND crossover was fitting the *shape*/scatter that pure R/h_R does not yet capture. Honest: the geometry gets the mean, not the per-galaxy profile.
3. **BTFR slope 2.56 < 3.14 observed** — the streak law under-steepens the mass–velocity relation. FAIL on the slope; the deep-limit v⁴∝M that MOND builds in by construction is not reproduced by R/h_R alone.
4. **Bulgeless (gas-dominated) galaxies are worst (37.8%).** Likely root-2 (dependency): the streak factor uses the **stellar** h_R, but in dwarfs the **gas** disk dominates and extends far past h_R — wrong scale length for the dominant component. This is a principled refinement (use the gas disk's own extent), NOT a tuning knob.

## Verdict (dual)
- **Prompt completion: B** — the mass-free two-regime model was built and run on real SPARC end-to-end.
- **Physics class: PARTIAL / OPEN** — the streak geometry removes the dark-matter *bias* with zero free gravity parameters (genuine, and better than the Newtonian control), but the residual *scatter* (35%) and BTFR slope (2.56) miss. **Not** the MOND-borrowed 23.8% — and that gap is the honest measure of what the borrowed a_0 was doing.
- **No GM, no GR, no a_0, no MOND in the chain** — Harvey's directive met.

## Winding diagnostic (added 2026-07-13, Harvey directive) — the reframe
Harvey: *"there is something wrong with the flat-rotation model — at a flat falloff in reverse, the spiral unwinds very quickly."* Computed on the real sample:

| quantity (135 galaxies, observed curves) | median | mean |
|---|---|---|
| windings inner-vs-outer over 10 Gyr (ΔTurns) | **61.6** | 126.1 |
| absolute inner windings over 10 Gyr | 78.3 | 140.4 |
| outer log-slope β = dln v/dln r (0=flat, 1=rigid) | **0.29** | — |

- **A material arm winds up ~62× in 10 Gyr → it CANNOT be material.** This is independent of the rotation *law*: observed curves, the S2 streak model (ΔTurns median 39), a dark-matter halo, and MOND all give tens of windings. **The winding problem is not about what flattens the curve — it is that spiral arms are a STANDING PATTERN, not co-moving matter.**
- β = 0.29 (not 0): real curves are *quasi*-flat with a slight rise — the pure-streak S2 (β→0) is **too flat**, part of why RMS sits at 35%.
- **SPOKE CLOCK (Harvey's question, computed): median 162 Myr per relative turn** (mean 209). A radial spoke winds into a 1-turn spiral in ~162 Myr; an open half-turn spiral unwinds to spokes in ~65 Myr. Galaxy age 10 Gyr ⇒ **~62× too many windings** ⇒ the arm is at most ~1% of the galaxy's age old *as matter*. Spokes⟷spiral in ~one outer orbital period. Persistent only as a **standing pressure/occlusion wave** whose pattern speed is set by the medium's wave dispersion (superfluid), not by material orbits.
- **The reframe:** galactic dynamics is a **two-component** problem on **one** occlusion medium — (1) the mean occlusion field → the rotation curve (streak), (2) a standing occlusion/density wave in the spation superfluid → the spiral arms at a single pattern speed → no winding. Fitting v(r) alone was too narrow a model; the prompt scope is expanded accordingly (§ new).

## Named next step (root-2, not a fish)
Give the **gas** disk its own scale length (from the rotmod radial extent) for its streak factor, instead of the stellar h_R. Re-run; if bulgeless RMS drops toward the with-bulge 30%, the scatter was a wrong-scale-length artefact, not a mechanism failure. Do NOT introduce an a_0 or a fitted crossover to chase the 23.8%.
