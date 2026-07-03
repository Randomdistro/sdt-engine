# VERDICT — GOM03: Lunar Orbital Kinematics

> **Author:** J. C. Harvey, Melbourne. **Executed:** 2026-07-03 (HUNTER discipline).
> **Tool:** `gom03_lunar_pendulum.cpp` — compiled AS-IS (zero edits), MSVC 19.44, exit 0.
> **Evidence:** `results.txt` (real stdout), `RUN_LOG.md` (pre-committed gates).

## Dual verdict

- **Prompt completion: D**
- **Physics class: CONVERGENCE (disclosed identity) on the ϟ-bridge; OPEN on the
  measurement pipeline the PROMPT actually asked for**
- **Earned vs owed: partially earned demo; the specified deliverable is still owed**

## What the PROMPT asked vs what the tool does

The PROMPT specifies a **pendulum tidal-inversion** pipeline: extract M2/O1/N2 tidal
constituents from a pendulum acceleration time-series and invert them for d(t), e, i, P.
The committed `.cpp` implements something different: a **two-sextant parallax simulation**
("papyrus-grade astronomy") that synthesises a lunar ephemeris from the known parameters
and recovers them from noisy simulated angle readings. No Fourier tidal decomposition, no
M2/O1/N2, no pendulum acceleration channel exists in the code. The tidal-inversion
deliverable is **unbuilt** — that is the honest gap.

## Real numbers vs pre-committed gates (RUN_LOG.md, committed before run)

| Quantity | Recovered | Known | Error | Committed gate | Result |
|---|---|---|---|---|---|
| d_mean | 398,267 km | 384,400 km | **+3.61%** | 0.1% | **FAIL** |
| eccentricity | 0.0912 | 0.0549 | **+66.2%** | 5% | **FAIL** |
| period | 29.179 d | 27.3217 d | **+6.80%** | 0.01% | **FAIL** |
| ϟ = v²d | 3.924e14 m³/s² | 4.024e14 | −2.49% | (not gated) | note 1 |
| v_surface via v²d=const | 7850.8 m/s | 7909.0 | −0.74% | (not gated) | note 1 |
| zk² | 1.000000 | 1 | exact | — | **IDENTITY** (not a result) |

The tool's own scorecard prints "✓" using 5%/20%/1% tolerances. Those are looser than
the PROMPT's success criteria and are rejected here — no retroactive widening.

**Failure mechanism (diagnosed, not excused):** the recovered period 29.179 d sits at the
synodic month (29.53 d), not the sidereal month (27.32 d). The perigee-finder operates on
a distance series that is gap-punctured by the new-moon observing window (synodic phase
cut in the simulation loop), so perigee detection aliases against the window. The period
error then propagates into e (phase-folding at the wrong period smears the fold) and v.
The hand-fed fallback (P_s defaulting to the true value when <2 perigees are found) did
NOT engage — the failing numbers are genuinely computed, which is the correct honest state.

## Classing

1. **ϟ = v²d "no G, no M":** ϟ is numerically GM_Earth (bridge identity ϟ_upper ≡ GM/c²).
   Sanctioned and disclosed → **CONVERGENCE**, never NATIVE. What the demo shows is that
   the Newtonian gravitational parameter is recoverable from angles + time alone — true,
   historically well known (it is how GM was in effect first measured), and not an
   SDT-discriminating result.
2. **zk² = 1:** algebraic identity by construction → **IDENTITY**. Counted as notation
   self-consistency only.
3. **Synthetic-recovery ceiling:** the ephemeris is synthesised from the same constants it
   "recovers" — even a perfect run would be a pipeline-feasibility mock, not a measurement.

## Disposition

- The parallax demo stands as an honest feasibility sketch that currently **fails its own
  committed accuracy gates** (period aliasing is the root cause; fixable by observing
  through more of the synodic window or by a proper Fourier period search — left OPEN,
  not patched here, since fixing-to-pass post-commitment is prohibited).
- The PROMPT's actual deliverable (pendulum M2/O1/N2 tidal inversion) remains **owed**.
- Nothing here is fabricated: fallback plug did not fire, all numbers are real stdout.

## §D — Seven questions (on the three failed gates)

1. **Why (exact mechanism)?** Recovered P = 29.179 d ≈ the synodic month (29.53 d), not
   the sidereal target (27.32 d): the perigee-finder runs on a distance series gap-cut at
   synodic phase < 0.07 / > 0.93 (new-moon window), so minima detection aliases to the
   window period. The wrong P then corrupts the phase-fold (e +66.2%: apogee smeared into
   perigee bins) and v = 2πd/P; d_mean (+3.61%) carries harmonic-mean bias on 1/p noise
   at per-night SNR ~10.
2. **Recoverable?** Yes in route: sample through more of the synodic window and replace
   minima-counting with a full-series periodogram. Not re-run here (post-commitment
   fixing-to-pass is prohibited).
3. **What did the target fail to account for?** That the observing-window comb convolves
   with the orbital period — sampling design, not sextant noise, sets the recovery floor.
4. **Errored premise?** "Nightly perigee minima are directly countable through a
   synodic-gated window." Folder-level premise slip on top: a parallax sim was built
   where the PROMPT committed a tidal-inversion pipeline — the tool answers a weaker
   question than the one specified.
5. **Correcting freedom?** Sampling schedule + period-search estimator — design freedoms
   with prior justification (standard aliasing arithmetic), fixable before any re-run.
6. **Native or knob?** Native. No physical constant is tuned; zero CALIBRATED spend.
7. **Cascade?** No — independent tool-design fault; shares no root with the rest of the
   cluster. The ϟ≡GM identity content is unaffected by the failure.

**Recovery grade: PARTIAL** (mechanism + premise named, route stated; fix not executed,
gates left failed as committed).

---

**Prompt completion D · Physics class CONVERGENCE (ϟ-bridge, disclosed) / OPEN (committed
tidal-inversion pipeline still owed) · Recovery PARTIAL · Cascade root none.**
