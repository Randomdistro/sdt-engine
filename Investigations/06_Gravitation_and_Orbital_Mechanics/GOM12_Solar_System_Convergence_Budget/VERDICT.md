# VERDICT — GOM12: Solar-System Convergence Budget (E101)

> **Author:** J. C. Harvey, Melbourne. **Executed:** 2026-07-03 (HUNTER discipline).
> **Tool:** `gom12_convergence_budget.cpp` (new, written after RUN_LOG commitments).
> **Run:** exit 1 (3 committed gates failed — kept). **Evidence:** `results.txt`, `RUN_LOG.md`.

## Dual verdict

- **Prompt completion: B** (every deliverable in the PROMPT computed for real; three
  committed gates failed for traceable input-quality/two-body reasons and were left
  failed)
- **Physics class: CONVERGENCE (the census: ϟ ≡ GM/c² disclosed throughout) + two
  honest OPEN items + one clean NULL result (E21)**
- **Earned vs owed: the budget bookkeeping is earned; E101's Law-II "L_Sun balances
  the influx" claim is only half-earned (see §Budget) — the lumiopause number exists,
  the Oort identification stays OPEN**

## The census (all from measured kinematics; no G, no M as inputs)

- **k-hierarchy:** Mercury k=6263 → Neptune k=55210; Σz(planets) = 5.92e-8. zk² = 1 to
  3.3e-16 — **IDENTITY, unscored** (notation, not physics).
- **ϟ_Sun from 8 planetary orbits (v²a/c²):** mean 1477.4 m; σ/μ = 0.301% → **FAIL**
  against the committed 0.1%. Root cause: the PROMPT's velocity table mixes mean
  eccentric-orbit speeds with circular equivalents — Mars and Saturn (the two most
  eccentric probes used) are exactly the outliers. The clean (a,T) probe set
  (4π²a³/T²c², GD03 tool, same day, real output) gives σ/μ = 0.0611%. The invariance
  is real; this probe set is dirty. Both facts reported; gate not widened.
- **Per-body ϟ from satellites (pure kinematics):** Jupiter from Io/Europa/Ganymede/
  Callisto: σ/μ = **0.010%** → PASS — the cleanest parent-invariance result in the
  folder. Earth from the Moon misses GM_E/c² by +0.727% → census gate **FAIL**;
  diagnosis: v²a measures ϟ(Earth)+ϟ(Moon) (two-body), and the Moon is 1.2% of Earth —
  the miss is the Moon's own koppa showing up, which is physically correct and
  numerically consistent (4.435e-3 + 5.4e-5 ≈ 4.49e-3 m). Honest gap kept: Mercury and
  Venus have **no kinematically measurable ϟ** (no satellites).
- **Occlusion budget:** planets shadow Σf = **4.19e-9** of the Sun's 4π influx
  (Jupiter alone 2.0e-9). The solar convergence budget closes to ~1 part in 2.4e8.
- **Jupiter's depth at Earth:** z_J = 2.24e-12, i.e. **4,460× below** the ~1e-8
  residual scale the PROMPT asked about. Jupiter's static depth does NOT explain any
  1e-8 orbital residual. Stated plainly.

## Budget closure (E101's actual question)

Lumiopause r = √(L_Sun/(4π F_CMB)) = **20,857 AU** (laws.hpp, no new inputs). The Oort
inner edge spans ~2,000–20,000 AU in the literature; the PROMPT's "within factor of 2"
is under-specified against a 10×-wide target. Committed handling honoured: **OPEN** —
consistent with the upper end (ratio 1.04) only. E101 remains an open falsifiable
prediction; this run supplies its number without stamping it.

## Null result

**E21 integer-k² conjecture: 0/7 adjacent-planet hits** (closest: Uranus/Saturn at
2.026, just outside the pre-committed 0.02 window — and one near-integer among seven
ratios is look-elsewhere territory anyway). Not supported. Recorded as a clean null.

## Standing

Nothing here discriminates SDT from Newton — nor can it: every quantity is ϟ = v²r/c²,
the disclosed GM identity. The value of GOM12 is bookkeeping: the koppa census from
pure kinematics (including the satellite route and its two-body correction), the
occlusion budget (4e-9), and two honest OPEN/NULL entries that stop E101 and E21 from
inflating. Follow-up owed if wanted: re-run gates 2–3 with ephemeris-grade (a,T)
inputs instead of rounded mean speeds.

## §D — Seven questions (on the 3 FAILs, the OPEN, and the NULL)

1. **Why (exact mechanism)?**
   - Gates 2–3 (Kepler 0.351% worst / invariance σ/μ 0.301% vs 0.1%): the input table
     mixes time-mean speeds of eccentric orbits with circular equivalents; Mars
     (e=0.093) and Saturn (e=0.057) are precisely the outliers (1470.6 m, 1487.5 m).
   - Gate 4 (Earth–Moon +0.727% vs 0.5%): v²a of a satellite returns ϟ(parent)+ϟ(sat);
     the Moon is 1.2% of Earth. Plus rounded v = 1022 m/s (circular value 1024.6).
   - Oort OPEN: target "inner edge" spans 2,000–20,000 AU — a 10×-wide goalpost.
   - E21 NULL: 0/7 integer hits; closest 2.026 (Uranus/Saturn), outside the 0.02 window.
2. **Recoverable?** Gates 2–3: yes (ephemeris (a,T) probes; the same-day GD03 (a,T) run
   already shows σ/μ = 0.0611% — the invariance itself is fine). Gate 4: yes (two-body
   sum ϟ_E+ϟ_Moon ≈ 4.49e-3 m, demonstrated at order level). Oort: only by sharpening
   the observable. E21: no — see Q5/6.
3. **What did the target fail to account for?** Eccentricity in "mean velocity"
   definitions; the satellite's own koppa in the census; the width of the Oort
   literature range; look-elsewhere for one near-integer among seven ratios.
4. **Errored premise?** Gates 2–4: "rounded single-speed rows are precision probes"
   and "a satellite probes the parent alone." NOT the bridge law. Oort: "the Oort
   inner edge is a sharp measured number." E21: "adjacent orbital spacing should
   quantise in k²" — the premise itself found nothing to stand on.
5. **Correcting freedom?** Gates 2–4: input provenance + the two-body term — both
   pre-justified, no fitting. Oort: a defined observable (e.g. LPC aphelion
   statistics for the Hills boundary). E21: none available that is not a fished
   pattern-search — the correcting freedom would be a knob, so the conjecture stays
   dead unless an independent quantisation mechanism is derived first.
6. **Native or knob?** Gates 2–4 freedoms: native (measured data quality, exact
   two-body kinematics). E21 "freedom": knob → refused.
7. **Cascade?** Gates 2–3 (and the rounding component of gate 4) share the
   **INPUT-PRECISION** root with GOM10's μ_ϟ gate — one ephemeris-grade input block
   pays all of them. The two-body component of gate 4 is local (premise now stated).
   Oort/E21 are independent items.

**Recovery grade: PARTIAL** (routes and premises named; clean-input re-run and Oort
observable-sharpening not executed). **E21 sub-item: NO RECOVERY** (clean null; any
"fix" would be fished).

---

**Prompt completion B · Physics class CONVERGENCE (census, ϟ≡GM/c² disclosed) + OPEN
(Oort/E101 closure) + NULL (E21, killed clean) · Recovery PARTIAL · Cascade root
INPUT-PRECISION.**
