# CM04 — Crystal Lattice and Phonons as Compression Waves

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Can the heat capacity of a crystalline solid — the Dulong–Petit `3R`
   high-T limit and the Debye `C ∝ T³` low-T law, with `θ_D` set by the FD05 sound speed `c_s` — be
   reproduced by **counting native lattice compression-wave modes** (FD05 relay waves), with **no
   phonon field operators and no QM oscillator quantisation imported as mechanism**? Concretely: does
   `θ_D = (ℏ c_s/k_B)(6π²n)^{1/3}` predict measured Debye temperatures, or is the `T³` law only
   recoverable by assuming the very quantisation it should derive?
2. **Why does it matter?** — CM04 is the **substrate node** of the CM stack (README, bottom of the
   build order): the same FD05 compression wave is the conduction-limiting thermal defect (CM02 ρ∝T),
   the superconducting pairing channel (CM01), and the thermal-disorder source that beats alignment
   at the Curie point (CM07). If "phonon" is genuinely the FD05 relay wave, the whole stack rests on
   one native object; if it secretly needs field-operator quantisation, the substrate is borrowed.
3. **How will we find out?** — Four gated phases (§④): mode counting → 3R (P1) and the Debye `g(ω)∝ω²`
   spectrum (P2) run from FD05 geometry *before* any oscillator-quantisation step; importing a phonon
   field operator or the Planck oscillator partition as a postulate caps the grade at C.
4. **What would prove us wrong?** — §⑧: three falsifiers with numeric triggers and real failure
   modes — the `T³` exponent (T2) and the `θ_D(c_s)` prediction (T3) can both come out wrong.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, with no repainting of a fired test.

## Question

A "phonon" in SDT is **not** an imported field quantum — it is the **native FD05 lattice
compression wave** running on the granular relay lattice, with sound speed `c_s` set by the relay
stiffness. **Can the specific heat of a crystalline solid — the Dulong–Petit high-T limit `3R` and
the Debye low-T `C ∝ T³` law, with `θ_D` fixed by `c_s` — be reproduced purely by counting
compression-wave modes in the lattice, no phonon field operators?** This is the vibrational
substrate beneath conduction (CM02) and superconductivity (CM01, where the same wave mediates
pairing).

## SDT mechanism & hypotheses

The lattice carries `c_s` compression waves (FD05). The number of modes is fixed by the lattice
geometry: **3N modes for N ions** (three displacement directions × bodies — DOF set by bodies×dims,
not pressure, per [[project_spation_lattice_structure_fork]]). Heat capacity = how energy partitions
across those relay-vibration modes.

- **H1 (mode counting → 3R):** at high T every mode carries `k_BT` of disordered throughput → molar
  `C_v = 3R` (Dulong–Petit), purely from 3N counting + equipartition of relay vibration.
- **H2 (Debye T³):** low T, only long-wavelength compression modes (under `c_s`) are excited;
  density-of-modes ∝ ω² in 3D → `C_v ∝ T³` derived, not assumed.
- **H3 (θ_D from c_s):** the Debye cutoff `θ_D = (ℏ c_s / k_B)(6π²n)^{1/3}` comes from the shortest
  relay wavelength (one lattice spacing) and FD05 `c_s` — predicts θ_D for several solids within ~10%.

## Strategy

**Phase 1 — Mode count.** *Goal:* 3N modes from lattice geometry. *Method:* three displacement DOF
per ion in a finite lattice. *Success:* exactly 3N; high-T `C_v → 3R` (Dulong–Petit) for ≥4 solids.

**Phase 2 — Debye spectrum.** *Goal:* density of compression modes. *Method:* count FD05 modes in a
sphere of radius `ω/c_s`; cutoff at one lattice spacing. *Success:* `g(ω) ∝ ω²`; low-T `C_v ∝ T³`
exponent recovered exactly.

**Phase 3 — θ_D from c_s.** *Goal:* absolute Debye temperatures. *Method:* `c_s` (FD05) + measured
lattice spacing → θ_D. *Success:* θ_D for Cu, Al, diamond, NaCl within 10%.

**Phase 4 — Crossover.** *Goal:* full `C_v(T)`. *Method:* Debye integral over the native spectrum.
*Success:* the 3R→T³ crossover curve matches measured `C_v(T)` shape (no per-solid refit).

## Success criteria

- ✅ **PASS (A):** 3R, T³ exponent, and θ_D(c_s) all native, zero fits.
- ✅ **QUALIFIED (C):** 3R + T³ derived; θ_D needs `c_s` as a measured-material input (legitimate). *(Expected.)*
- ⚠️ **PENDING (D):** mode counting + 3R shown; T³ or θ_D only scaling-correct.
- ❌ **FAIL (F):** cannot get T³ without importing phonon quantisation as a postulate.

## Falsification tests (each has a real failure mode + numeric kill trigger)

| # | Test | SDT prediction (numeric) | What KILLS it |
|---|------|--------------------------|---------------|
| T1 | 3N mode counting → Dulong–Petit | high-T `C_v → 3R = 24.94 J·mol⁻¹·K⁻¹`, within 2% for ≥4 solids (Cu, Al, Pb, NaCl) | if 3N counting gives a high-T limit ≠ 3R (e.g. 3R/2 or 6R), DOF is not bodies×dims; thesis dead |
| T2 | Debye `g(ω) ∝ ω²` → `T³` | fitted low-T exponent `p = 3.0 ± 0.1` in `C_v ∝ T^p`, T < θ_D/10 | if the exponent comes out 1 or 2 (wrong dimensionality of the mode sphere), or `T³` only appears after a Planck oscillator partition is *imported* → spectrum is not the FD05 compression mode (→ C, not A) |
| T3 | `θ_D = ℏc_s(6π²n)^{1/3}/k_B` | θ_D within 10% for Cu (343 K), Al (428), diamond (2230), NaCl (321) using FD05 c_s + measured n, **no per-solid refit** | if θ_D is off by >2× for any of the four, or needs a different multiplier per solid → the cutoff is not the one-spacing relay; θ_D not c_s-set |

## Dependencies

**Upstream:** FD05 (`c_s`, compression wave), TD06 (thermal mode counting),
[[project_spation_lattice_structure_fork]] (DOF = bodies×dims). **Downstream:** CM02 (thermal
occlusion ρ∝T), CM01 (the pairing "phonon"), CM07 (thermal disordering → Curie T). **Related:**
the lattice spacing as the shortest relay wavelength.

## Implementation notes

Double precision; `C_v` in J·mol⁻¹·K⁻¹, T/θ_D dimensionless for the crossover. Keep "phonon" strictly
the FD05 lattice compression wave — naming the mode a phonon is fine (observable), importing a phonon
**field operator** or treating it as a QM oscillator put in by hand is the forbidden mechanism. Keep
measured lattice spacings / n / c_s in one labelled MEASURED-INPUT block; textbook θ_D and C_v(T) are
the convergence target, never the hard-coded answer. Author attribution in all generated files:
**J. C. Harvey, Melbourne.**

## Questions This Opens *(generative — log new ones in `CM04_VERDICT.md`)*

Not required for the verdict; this is the payoff of doing it well.

1. **Does the FLM08 frustration bend `g(ω)` at short k?** FD05's short-wavelength deviation (the
   one-spacing cutoff) is where the continuum `ω = c_s k` fails. Does the CRN frustration leave a
   measurable signature in the Debye spectrum (a deviation from pure `ω²`) that real inelastic-neutron
   dispersion curves already show?
2. **Is the `T³` law the same `1/D` geometry as FD05's `c/√3`?** The Debye `ω²` density-of-modes is a
   3-D mode-sphere count; FD05's `1/3` is the same dimensionality. Can CM04 derive both from one
   `D = 3` statement, making the `T³` law a dimensionality readout?
3. **Where does zero-point come from natively?** The Debye integral has a zero-point term; SDT has no
   QM ground-state postulate. Is the residual lattice motion at T=0 the irreducible relay-tick jitter
   (ℓ_P-scale), and does that fix a native cutoff without an oscillator vacuum?
4. **Does the same c_s set the CM01 isotope effect quantitatively?** If θ_D ∝ c_s ∝ M^{−½}, is the
   CM04 θ_D(M) the *same curve* as CM01's T_c(M) up to the locking-energy factor — one measurement
   checking two investigations?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CM04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the mode-counting chain (c_s and lattice spacing are MEASURED-INPUT, not fits)
- Engine namespaces actually used: FD05 c_s, bridge, TD06 mode counting; lattice_structure.hpp (cutoff geometry)
- Phase thresholds (committed before run):
    P1 high-T C_v → 3R within 2% (≥4 solids) · P2 low-T exponent p = 3.0 ± 0.1, NO imported oscillator partition
    P3 θ_D within 10% for Cu/Al/diamond/NaCl, one cutoff rule · P4 crossover curve shape matches, no per-solid refit
- Forbidden retroactive changes: import a phonon field operator / Planck oscillator partition then claim A;
    per-solid refit of the θ_D cutoff; widen tolerances; plug θ_D; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 high-T limit ≠ 3R within 2% | recheck the 3N DOF count (bodies×dims, not pressure) | **OPEN**: report the actual limit | adjust the DOF count to force 3R |
| P2 exponent p ≠ 3.0 ± 0.1 | recheck the mode-sphere dimensionality (g(ω)∝ω² in 3D) | **OPEN**: report p; still A on P1 if 3R holds | import an oscillator partition to manufacture T³ and grade A |
| P2 T³ only appears with an imported quantisation | down-grade to **C** (the import is the postulate) | — | claim NATIVE while importing the oscillator |
| P3 θ_D off >2× for any solid | recheck c_s (FD05) and n; verify the one-spacing cutoff | **OPEN** θ_D; report which solid fails | refit the cutoff multiplier per solid |
| Rivals (Debye/Einstein) match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |
| Upstream dependency missing (FD05 c_s not run) | **DEFER** P3/P4; cite dependency ID | — | fabricate c_s |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** cutoff conventions (one-spacing vs first-Brillouin-equivalent), both FD05-derived.

### Disallowed adjustments

- Importing a phonon field operator or oscillator partition into the native chain and grading A ·
  per-solid θ_D refit · post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in any native chain.

---

*CM04 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
