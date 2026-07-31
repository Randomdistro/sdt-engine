# Scrollthrough Ledger — what exists, what is wired, what is not built

> **Compiled:** 2026-07-30, direct (main loop). **Scope:** every `*_scroller.html`,
> `st_*.html`, and `*walkthrough.html` in the repository, graded against the
> Benchmarks suite and all 190 investigation folders.
> **Method note:** counts below come from a filesystem sweep, not from narration.
> The "not built" lists are complete; the *readiness* column is a judgement call
> and is marked as such.

---

## 1. Built and now wired into the site (19)

All nineteen are reachable from the home page's **Scrollthrough series** row.
Eleven of them lived outside `Release/HTML_SDT_Website/` until this pass and were
copied in (`benchmarks_scroller.html` also had its stylesheet path repointed from
`../Release/HTML_SDT_Website/style.css` to `style.css`).

| Page | Subject | Source home | Was wired before? |
|---|---|---|---|
| `st_00_primitives.html` | The four primitives | site | yes |
| `st_01_law1.html` | Law I — convergent relay | site | yes |
| `st_02_law2.html` | Law II — release cascade | site | yes |
| `st_03_law3.html` | Law III — boundary pressure | site | yes |
| `st_04_law4.html` | Law IV — inertial mass | site | yes |
| `st_flm01.html` | FLM01 — the 28D state | site | yes |
| `st_gom_gravity.html` | Gravity without G | site | **no — now wired** |
| `sdt_walkthrough.html` | Whole-theory guided pass | site | yes (doors) |
| `nuclear-packing-walkthrough.html` | Packing walkthrough | site | yes |
| `flm02_scroller.html` | FLM02 — granular pulse mechanics | Investigations/01 | **no — copied + wired** |
| `ppt01_scroller.html` | PPT01 — vortex equilibrium quantisation | Investigations/02 | **no — copied + wired** |
| `ppt02_scroller.html` | PPT02 — fine structure from topology | Investigations/02 | **no — copied + wired** |
| `ppt04_scroller.html` | PPT04 — neutrino magnetic moment | Investigations/02 | **no — copied + wired** |
| `ppt05_scroller.html` | PPT05 — trefoil confinement | Investigations/02 | **no — copied + wired** |
| `ppt06_scroller.html` | PPT06 — spation traction | Investigations/02 | **no — copied + wired** |
| `emc01_scroller.html` | EMC01 — transfer function | Investigations/03 | **no — copied + wired** |
| `aps01_scroller.html` | APS01 — emissions | Investigations/04 | **no — copied + wired** |
| `aps02_scroller.html` | APS02 — emission prediction | Investigations/04 | **no — copied + wired** |
| `depth_closure_scroller.html` | Depth–Closure Theorem | Papers/ | **no — copied + wired** |
| `benchmarks_scroller.html` | Benchmarks B01–B29 | Benchmarks/ | **no — copied + wired** |

Also present in-repo but **deliberately not wired**: `Laws/laws_scroller.html` — see
defect L1 below. `flm01_scroller.html` (Investigations/01) is superseded by the
site's `st_flm01.html`.

---

## 2. Defects in built scrollthroughs (fix before promoting either)

**L1 · `Laws/laws_scroller.html` renders a superseded Law VI.** The page still
carries the exploratory higher-winding model (electron at "~10²⁵ winding units").
Canonical Law VI is the trefoil (2,3) proton at W = 3 and the (1,1) unknot electron
at W = 1, with R_wake = (W+1)ℏ/(mc). The page has been partly updated (it says "Six
Laws"), so the 10²⁵ figure is a leftover, not a stated position. **Not linked from
the site until corrected.**

**L2 · `benchmarks_scroller.html` is nine rows stale.** It covers B01–B29; the suite
now carries rows through **B38** (B30–B38 exist in `benchmarks_suite.cpp`, including
B38's parity-lock tally at 7/7 and 12/12). The row label on the home page says
"B01–B29" so the page does not overstate itself, but the closing rows are missing.

---

## 3. Not built — Benchmarks

| Gap | Detail |
|---|---|
| **B30–B38** | Nine suite rows with no scrollthrough coverage. B38 (closure schedule + triton parity lock) is the highest-value single addition in the whole ledger: it is the visual companion to the derived magic-number capacities. |

---

## 4. Not built — Investigations (180 of 190)

Ten investigation folders carry a scroller (FLM01, FLM02, PPT01, PPT02, PPT04,
PPT05, PPT06, EMC01, APS01, APS02). **The other 180 do not.** Full list by domain,
with a readiness judgement — *R* = executed with evidence on file, so a scroller can
be built from earned content; *S* = specification or evidence not yet in a
verdict/results file, so a scroller would be premature.

> Readiness is a **judgement**, assigned from the domain verdict files and the
> per-domain READMEs. It is not a re-derivation of each investigation's status, and
> a handful of folders store evidence under non-standard filenames (NP27, NP30,
> NP33, CR07, CR12, GD05 are all executed despite an *S*-looking file layout).
> Treat the ID lists as complete and the letters as a starting sort order.

### 01 — Foundations & Lattice Mechanics (13 missing of 15)
`FLM03`·S `FLM04`·S `FLM05`·S `FLM06`·R `FLM07`·R `FLM08`·S `FLM09`·R `FLM10`·S
`FLM11`·R `FLM12`·R `FLM13`·R `FLM14`·R `FLM15`·S
→ **priority:** FLM12 (mass mechanism — Newton I/II and E₀ = mc² as theorems),
FLM06 (Seed Theorem, an earned negative), FLM14 (rotating substrate, the root the
residence law hangs on).

### 02 — Particle Physics & Topology (11 missing of 16)
`PPT03`·S `PPT07`·R `PPT08`·R `PPT09`·R `PPT10`·R `PPT11`·R `PPT12`·S `PPT13`·S
`PPT14`·S `PPT15`·S `PPT16`·S
→ **priority:** PPT09 (the winding-spectrum classification theorem, class A — the
strongest analytic result in the framework without a scroller), PPT07 (6π⁵).

### 03 — Electromagnetism & Charge (3 missing of 4)
`EMC02`·R `EMC03`·R `EMC04`·R
→ **priority:** EMC03 (repulsion as the inverse of convergence — the handedness
account), EMC04 (electropause, which forces the P_eff closed form).

### 04 — Atomic Physics & Spectroscopy (8 missing of 10)
`APS03`·R `APS04`·R `APS05`·R `APS06`·R `APS07`·R `APS08`·S `APS09`·S `APS10`·S
→ **priority:** APS07 (the movement law λ = 2L(c/v), seven floors at ratio 1.0000).

### 05 — Nuclear Physics (34 missing of 34 — no scroller anywhere in the domain)
`NP01`·S `NP02`·S `NP02B`·S `NP03`·R `NP04`·S `NP05`·S `NP06`·S `NP07`·R `NP08`·R
`NP09`·R `NP10`·R `NP11`·S `NP12`·R `NP13`·S `NP14`·R `NP15`·R `NP16`·S `NP17`·R
`NP18`·R `NP19`·R `NP20`·R `NP21`·R `NP22`·R `NP23`·R `NP24`·S `NP25`·S `NP26`·S
`NP27`·R `NP28`·R `NP29`·S `NP30`·R `NP31`·S `NP32`·S `NP33`·R
→ **priority: the largest hole in the ledger.** NP33 (traction mesh + the derived
closure capacities F(n), B(n), and the N = 184 prediction), NP17 (shared-electron
binding, the deuteron's 2.200 MeV), NP12 (the zero-fit packing radius, 908 radii),
NP27 (beam-peel kinematics, 1.83c confirmed). The `nuclear-packing-sequencer.html`
covers this domain interactively but is not a scrollthrough.

### 06 — Gravitation & Orbital Mechanics (21 missing of 21 — none in-domain)
`GOM01`·R … `GOM18`·R (all eighteen executed) `GOM19`·S `GOM20`·S `GOM21`·S
→ **priority:** GOM04 (c recovered from orbital geometry, +0.0009%), GOM17 (the
two-body exchange ledger across twenty orders), GOM06 (koppa-metry of inspirals).
Partly covered by `st_gom_gravity.html` and `depth_closure_scroller.html`, neither
of which is per-investigation.

### 07 — Cosmology & Redshift (13 missing of 13)
`CR01`·S `CR02`·S `CR03`·R `CR04`·R `CR05`·R `CR06`·R `CR07`·R `CR08`·R `CR09`·S
`CR10`·R `CR11`·S `CR12`·R `CR13`·R
→ **priority:** CR05 (the pressure tensor and topological freeze-out), CR07
(octaves, which excludes the tired-light class), CR12 (the recorded exclusion —
a scroller that shows a loss is worth more than one that shows a win).

### 08 — Galactic Dynamics (7 missing of 7)
`GD01`·S `GD02`·S `GD03`·R `GD04`·R `GD05`·R `GD06`·R `GD07`·S
→ **priority:** GD06 (the collective-displacement root, zero parameters), GD05
(the rotation-curve failure beside the surviving floor — a scroller that carries
its own kill).
Historical `cq06-eclipse.html` covers the superseded saturation model and is
already on display with its assessment attached.

### 09 — Stellar Astrophysics & Radiation (8 missing of 8)
`SAR01`·R `SAR02`·R `SAR03`·R `SAR04`·R `SAR05`·R `SAR06`·R `SAR07`·S `SAR08`·S
→ **priority:** SAR03 (the luminosity chain held OPEN with its audit trail).

### 10 — Fluid Dynamics (12 missing of 12)
`FD01`–`FD12` all ·R (all twelve executed, direct reruns 2026-07-26)
→ **priority:** FD04-P6 (the zero-parameter intermittency number 3−D = 0.0784),
FD02 (κ = h/m with its self-demotion), FD11 (the buildable turbine spec).
**Best-value domain in the ledger:** twelve executed investigations, complete
verdicts, zero scrollers.

### 11 — Thermodynamics & Statistical Mechanics (9 missing of 9)
`TD01`–`TD09` all ·R
→ **priority:** TD09 (the Freedom Ledger — flip at 0.0624 MeV inside the measured
deuterium window, zero fits), TD03 (the rank-4 lattice fingerprint, [1/9, 7/27] vs
the continuum's 1/5 — the domain's one native falsifier).

### 12 — Condensed Matter Physics (7 missing of 7)
`CM01`–`CM07` all ·R by file layout, **but the domain README states SPEC
(unstarted)** — resolve that contradiction before building.

### 13 — Quantum Foundations & Measurement (8 missing of 8)
`QM01`·S `QM02`·R `QM03`·R `QM04`·R `QM05`·R `QM06`·R `QM07`·R `QM08`·S
→ **priority:** QM03 (wake leakage — firewalled solver, 0.13%, and the
Geiger–Nuttall systematics at R² = 0.9997), QM04 (the squared amplitude derived
geometrically), QM05 (the locality audit held OPEN — the framework's largest debt,
and worth a scroller precisely because it does not resolve).

### 14 — Plasma Physics & Magnetism (7 missing of 7)
`PM01`·R (executed) `PM02`–`PM07`·R by layout, README says SPEC
→ **priority:** PM01 (1/r forced by winding-count conservation, with the
discriminating control at −2.0000, and zero magnetons in the chain).

### 15 — Optics & Photonics (8 missing of 8)
`OP01`–`OP07` ·R by layout (README says SPEC) `OP08`·S
→ **priority:** OP07 (the solar-fold falsifier — a dated, cheap, decisive test).

### 16 — Chemistry & Molecular Bonding (9 missing of 9)
`CH01`·R (superseded prototype — flag it) `CH02`–`CH07`·R by layout (README says
SPEC) `CH08`·S `CH09`·S
→ **priority:** CH06 (the −6.022 dispersion exponent), CH02 (the isoelectronic
discriminant, decidable on existing data).

---

## 5. Summary

| Bucket | Count |
|---|---|
| Scrollthroughs built | 19 (+1 in-repo not wired: `laws_scroller.html`) |
| Investigations with a scroller | 10 of 190 |
| **Investigations without a scroller** | **180** |
| Benchmark rows without scroller coverage | 9 (B30–B38) |
| Built-but-defective | 2 (L1 superseded Law VI · L2 nine stale rows) |

**If only five get built:** NP33 (the derived magic numbers), FD04-P6 (the
zero-parameter intermittency number), TD09 (the Freedom Ledger flip), PPT09 (the
winding classification theorem), QM05 (the locality debt, stated as a debt). Those
five carry the framework's strongest earned result, its cleanest parameter-free
number, its best cross-domain gate, its firmest analytic theorem, and its largest
declared debt — one of each kind, rather than five of the same kind.
