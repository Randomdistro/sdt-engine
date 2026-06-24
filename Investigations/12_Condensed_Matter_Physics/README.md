# Condensed Matter Physics — collective vortices in the relay lattice (CM01–CM07)

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (7 prompts, unstarted).
> Every prompt inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## The through-line

Condensed matter is **the collective behaviour of many vortices co-resident in the granular
relay lattice**. There is no second medium and no new ontology: the *same* spation lattice that
relays convergence throughput to give gravity (`g = v²/R`) and Coulomb (occlusion, Law III) also
carries conduction, magnetism, sound, and the superfluid condensate. A conduction electron is a
**drifting W=1 vortex**; resistance is **occlusion drag** dumping organised throughput into
disordered throughput (heat); a "phonon" is the **native FD05 lattice compression wave**; a magnet
is **aligned wake circulation**. These seven investigations reproduce the standard solid-state
catalogue as *convergence targets* — never borrowed inputs — narrating each in SDT primitives and
flagging every gap OPEN rather than fitting it. The forbidden imports (BCS gap/wavefunction, Bloch
wavefunction, gauge-symmetry-breaking as ontology, electron "clouds", phonon field-operators) are
**targets to reproduce**, not machinery to assume.

## Dependency stack (build/run order — bottom feeds top)

```
CM04  Crystal lattice & phonons          ← the substrate (FD05 compression wave + mode counting)
  │     (Debye T³; Dulong–Petit; c_s as relay stiffness)
  │
  └─ CM02  Conduction & Ohm's law          ← the NORMAL-STATE ROOT (occlusion drag of drifting W=1)
        │     (Drude-like; defines the ohm natively; R → heat)
        │
        ├─ CM03  Band structure             (conductor/semi/insulator from lattice packing + gaps)
        │
        ├─ CM01  Superconductivity          (phase-locked vortex PAIRS; R→0; Φ₀=h/2e; isotope)
        │     │   [seed, already written]
        │     │
        │     ├─ CM05  Superfluidity & BEC   (macroscopic phase-locked wake condensate; κ=h/m)
        │     │
        │     ├─ CM06  Quantum Hall & Josephson  (lattice topology → the ohm E86 / the volt E85)
        │     │
        │     └─ CM07  Ferromagnetism        (aligned wake circulation; Curie T; hysteresis)
```

## The suite

| ID | Title | SDT mechanism | Convergence target / falsifier |
|----|-------|---------------|--------------------------------|
| **CM01** | Superconductivity as Phase-Locked Vortex Pairs *(seed)* | two W=1 vortices lock wakes via the lattice compression wave; defect-blind collective mode | R=0; Meissner; Φ₀=h/2e (native count); T_c ∝ M^{−½} |
| **CM02** | Electrical Conduction & Ohm's Law from Occlusion Drag | drifting W=1 vortex occluded by lattice disorder; drift = balance of push vs drag | σ = ne²τ/m form; ρ∝T (metal); native ohm; R→Joule heat |
| **CM03** | Band Structure / Conductor–Insulator from Lattice Packing | occlusion gap set by lattice packing geometry (APS01), not Bloch waves | metal vs semiconductor vs insulator ordering; gap scale; ρ(T) sign |
| **CM04** | Crystal Lattice & Phonons as Compression Waves | FD05 compression wave on the lattice; mode counting in a Debye box | Dulong–Petit 3R; Debye C∝T³; θ_D from c_s |
| **CM05** | Superfluidity & BEC from Phase Lock | macroscopic phase-locked wake condensate; one circulation quantum | He-4 T_λ; κ=h/m (FD02, 0.02%); critical velocity; quantised vortices |
| **CM06** | Quantum Hall & Josephson Metrology | lattice topology (Hall) + relay-phase coupling (Josephson) | R_K=h/e²; K_J=2e/h; ohm (E86) & volt (E85) native |
| **CM07** | Ferromagnetism as Aligned Vortex Wakes | aligned wake circulation; exchange = wake co-rotation energy | Curie T_C; hysteresis loop; M(T); **native wake-circulation units, NO magnetons** |

## Engine hooks (single source of truth: `Engine/include/sdt/laws.hpp`)

`law_III` occlusion (`F_occlusion`, `solid_angle_occluded`) = drag/scattering · `law_VI::traction`
(PPT06: `T = 3(W+1)`, wake ℓ=1/2/3) · `law_VI::topology` / `confinement` (winding = flux count) ·
`law_VI::mass_ratio` · `bridge` (`koppa`, `k`, `z`, `depth_closure`) · **PPT06** (traction grip) ·
**APS04** (angular / Lamb) · **EMC03** (handedness ± → both signs, swirl expulsion = Meissner) ·
**FD02** (`κ = h/m` clean to 0.02% — the circulation quantum) · **FD05** (`c_s` lattice sound =
relay stiffness, the native "phonon") · **B17** (native `g`). Falsifiable specs: **E59**
(phase-locked vortices), **E85** (Josephson volt), **E86** (quantum-Hall ohm).

## Method discipline

Each investigation reports results with certification labels (`DERIVED` / `COMPUTED` /
`CALIBRATED(n)` / `OBSERVED` / `PENDING`) and the audit-spine class (A–F). The standard
solid-state number is always the thing to *reproduce*, never to *borrow*; measured material
properties (lattice spacing, Debye temperature, carrier density, ρ) are legitimate measured-unit
inputs/tools — like spectral lines — but the mechanism must be SDT-native. **Never quote magnetic
results in Bohr magnetons or magnetons** — use native wake-circulation units (this is absolute, see
[[feedback_no_borrowed_units]]). Naming a lattice wave a "phonon" is fine; importing a phonon field
operator is not. A clean kill outranks a forced pass (R4).
