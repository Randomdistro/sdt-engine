# CM04 — Crystal Lattice and Phonons as Compression Waves

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

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

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | 3N mode counting | high-T `C_v = 3R` (Dulong–Petit) | DOF not bodies×dims |
| T2 | Debye `g(ω)∝ω²` | low-T `C_v ∝ T³` exponent exact | spectrum not FD05-compression |
| T3 | θ_D = ℏc_s(6π²n)^{1/3}/k_B | θ_D within 10% for 4 solids | cutoff not one-spacing relay |

## Dependencies

**Upstream:** FD05 (`c_s`, compression wave), TD06 (thermal mode counting),
[[project_spation_lattice_structure_fork]] (DOF = bodies×dims). **Downstream:** CM02 (thermal
occlusion ρ∝T), CM01 (the pairing "phonon"), CM07 (thermal disordering → Curie T). **Related:**
the lattice spacing as the shortest relay wavelength.
