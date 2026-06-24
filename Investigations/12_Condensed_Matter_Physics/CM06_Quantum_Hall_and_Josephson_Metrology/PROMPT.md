# CM06 — Quantum Hall and Josephson Metrology

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

The two most precise constants in metrology come from condensed matter: the **von Klitzing
resistance** `R_K = h/e²` (quantum Hall, defines the ohm — E86) and the **Josephson constant**
`K_J = 2e/h` (defines the volt — E85). Both are *exactly* topological — integers times `h/e`.
**Can `R_K = h/e²` and `K_J = 2e/h` be reproduced from SDT lattice topology and relay-phase coupling
— the Hall plateau as an integer count of occlusion-channel edge states, the Josephson "2e" as the
*two locked vortices* of [[CM01]], with no gauge-field machinery?** If the metrological constants
fall out as native integer counts, SDT inherits the SI's own definitions.

## SDT mechanism & hypotheses

Quantum Hall: in a strong swirl field the drifting vortices are confined to **edge relay channels**;
conduction is an integer count `ν` of those channels, each carrying `e²/h` of throughput → exact
plateaus, immune to disorder (topological = a count cannot vary continuously). Josephson: two
phase-locked condensates (CM01) coupled across a weak link relay a current set by their phase
difference; the voltage–frequency ratio is `2e/h` because the carrier is the **locked pair**.

- **H1 (Hall plateau = channel count):** `σ_xy = ν e²/h`, `ν` an integer edge-channel count; `R_K =
  h/e²` is the one-channel native resistance (closes against CM02's native ohm).
- **H2 (Josephson 2e = the pair):** `K_J = 2e/h`; the "2" is two locked vortices (CM01 H3), so
  `V = (h/2e) f` is a native phase-count relation, not a gauge result.
- **H3 (metrological exactness):** both are integer/topological, so robust to lattice disorder —
  plateaus are flat to the relay-quantisation floor.

## Strategy

**Phase 1 — Edge channels.** *Goal:* confined edge relay states in a swirl field. *Method:* EMC03
handedness + occlusion confinement of drifting vortices to boundaries. *Success:* discrete edge
channels exist; count `ν` integer.

**Phase 2 — Hall plateau.** *Goal:* `σ_xy = ν e²/h`. *Method:* throughput per channel = `e²/h`.
*Success:* `R_K = h/e²` to <0.1%; plateaus flat vs disorder.

**Phase 3 — Josephson.** *Goal:* `K_J = 2e/h`. *Method:* phase-difference current across a weak link
between two CM01 condensates. *Success:* `V = (h/2e) f`; the "2" demonstrably two vortices.

**Phase 4 — Metrology closure.** *Goal:* ohm (E86) + volt (E85) native. *Method:* cross-check
`R_K`, `K_J` vs SI. *Success:* both within the relay-quantisation floor; consistent with CM02 ohm.

## Success criteria

- ✅ **PASS (A):** `R_K = h/e²` and `K_J = 2e/h` both native integer counts, zero fits.
- ✅ **QUALIFIED (C):** both forms derived; one O(1) channel/geometry factor CALIBRATED(1). *(Expected.)*
- ⚠️ **PENDING (D):** edge-channel picture shown; only one of R_K / K_J quantitatively closed.
- ❌ **FAIL (F):** plateaus or 2e cannot be obtained without importing gauge/topological-band theory.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | Hall plateau = channel count | `R_K = h/e²`, integer plateaus | Hall not edge-channel topological |
| T2 | Josephson 2e = locked pair | `K_J = 2e/h`, "2"=two vortices | the 2 is not two vortices |
| T3 | exactness = topology | plateaus flat vs disorder | quantisation not a robust count |

## Dependencies

**Upstream:** [[CM01]] (locked pairs → the Josephson 2e), CM02 (native ohm), EMC03 (handedness /
edge confinement), Law VI (topology / winding count). **Downstream:** metrological closure of the SI
ohm and volt within SDT. **Related:** E85 (Josephson volt), E86 (quantum-Hall ohm); the
relay-quantisation floor as the precision limit.
