# CM03 — Band Structure / Conductor–Insulator from Lattice Packing

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Why is copper a conductor, silicon a semiconductor, and diamond an insulator? Standard theory
answers with **Bloch wavefunctions** and band gaps in k-space — a forbidden import. **Can the
conductor / semiconductor / insulator trichotomy, and the existence and *scale* of an occlusion
("band") gap, be reproduced from the lattice packing geometry alone — how tightly the W=1
conduction vortices are gripped by the lattice traction, with no Bloch waves?** A gap is not a
forbidden energy band; it is a packing configuration in which a drifting vortex finds **no
unoccluded relay path** until it is given enough throughput to break free.

## SDT mechanism & hypotheses

In SDT a "band" is the set of available drift channels through the lattice; a "gap" is a
geometric **occlusion blockade** — the lattice packing (coordination, bond directionality) leaves
no open relay path for a drifting vortex below some throughput threshold. Tight, directional
packing (diamond-cubic, full valence grip) closes all channels → large gap → insulator. Open or
metallic packing (FCC Cu, half-filled grip) leaves channels permanently open → conductor.
Intermediate (Si) → small gap, thermally bridgeable.

- **H1 (gap = packing blockade):** gap scale tracks coordination/directionality, not a fitted band
  parameter; the metal/semi/insulator *ordering* follows from packing geometry (relate APS01).
- **H2 (semiconductor ρ↓ with T):** a small gap is bridged by thermal throughput → carriers
  activate as `exp(−E_g/2k_BT)` (sign of dρ/dT flips vs a metal).
- **H3 (gap magnitude derivable):** `E_g` for Si/Ge/C comes from the lattice traction needed to
  free a gripped vortex (PPT06), to within a fixed O(1) geometric factor.

## Strategy

**Phase 1 — Packing classification.** *Goal:* sort metals/semis/insulators by packing geometry.
*Method:* coordination + bond directionality vs open relay channels. *Success:* correct trichotomy
ordering for ≥9 elements (Cu, Ag, Al, Si, Ge, C-diamond, S, etc.).

**Phase 2 — Gap scale.** *Goal:* predict `E_g` ordering and rough magnitude. *Method:* traction to
free a gripped vortex (PPT06) vs measured lattice constants. *Success:* `E_g(C) > E_g(Si) > E_g(Ge)`
with magnitudes within 2×.

**Phase 3 — Semiconductor ρ(T).** *Goal:* activated conduction. *Method:* thermal throughput
bridges the gap. *Success:* `ρ ∝ exp(E_g/2k_BT)`; dρ/dT < 0 (opposite CM02 metal).

**Phase 4 — Doping (stretch).** *Goal:* show donor/acceptor states as local packing defects.
*Method:* a substitutional defect opening one channel. *Success:* qualitative n/p shift in carrier sign.

## Success criteria

- ✅ **PASS (A):** trichotomy + gap ordering + activated ρ(T) all from packing, zero fits.
- ✅ **QUALIFIED (C):** ordering native; `E_g` magnitudes need one geometric CALIBRATED(1). *(Expected.)*
- ⚠️ **PENDING (D):** trichotomy correct; gap magnitude only ordinal.
- ❌ **FAIL (F):** cannot separate the three classes without invoking Bloch/k-space band structure.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | gap = packing blockade | correct metal/semi/insulator ordering | conduction class not packing-set |
| T2 | semiconductor activation | dρ/dT < 0; `exp(−E_g/2kT)` | gap not thermally bridgeable channel |
| T3 | `E_g` from traction grip | C>Si>Ge magnitudes within 2× | gap scale needs a band import |

## Dependencies

**Upstream:** CM02 (drift channels), CM04 (lattice geometry), Law III (occlusion), PPT06 (traction
grip). **Downstream:** CM06 (Hall sign of carriers), CM01 (gap vs pairing). **Related:** APS01
(lattice geometry); the metal-vs-insulator ordering as a packing theorem.
