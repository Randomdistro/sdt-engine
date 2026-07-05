# RUN_LOG — CH02 Ionic & Metallic Bonding from Electropause Transfer

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-04. **Status:** pre-commit written BEFORE coding.

## Grounding correction (Harvey directive, 2026-07-04)

The CH01 electropause-balance branch (F_in=F_out root-find) is the **failed branch** — NP17 is its
death knell: binding = **shared-electron well at scale αℏc** (deuteron 3αℏc/D, factor 3 exact, no
fitted scale; "chemistry geared down by 137" is literal, so chemistry IS the same machinery at Å).
This run stands on NP17's bones: pure point-source Σ±(αℏc)/r machinery. Corrected frames honoured:
occlusion **saturation at contact** (NP10/FARMER), **angle is the premium** (limited poloidal rim
contact), shared electrons = the binding. No QM machinery anywhere in the chain (HUNTER §G:
rivals supply measured NUMBERS only).

## Faith ledger (§G.1 — named before the run)

1. αℏc as the pairwise coupling: engine `coulomb_identity` (class F identity in-engine); NP17
   carries it as the load-bearing mechanism. Accepted as the cluster's coupling — named.
2. Ion = whole-electropause handoff leaves point-like ±1 handed cores at crystal sites: geometric
   idealisation (point sources for extended forms) — named as faith, size effects unmodelled.
3. Short-range repulsion (what stops the lattice collapsing) is NOT derived here — it is the
   contact-saturation closure (NP10 root). The sum is evaluated at the MEASURED r₀ (OBSERVED
   anchor); the expected systematic overshoot is declared below, before the run.

## Pre-Run Commitments — CH02

- Prompt completion target: C (the prompt's own expected landing)
- Physics class hoped: CONVERGENCE (honest) — NATIVE only if the occlusion sum needs no imported constant
- CALIBRATED budget: 0 fitted parameters. The pairwise coupling is `sdt::laws::coulomb_identity::k_e_e2 = αℏc`
  (whitelist expression; the engine itself labels it class F / definitional identity — this is DECLARED, not hidden).
  The ionic/covalent split threshold is NOT fitted: the test is whether a clean GAP separates the two classes.
- Engine namespaces: `sdt::laws::measured`, `sdt::laws::coulomb_identity`. No local constant namespaces.
- OBSERVED anchors declared up front (measured data, legitimate anchor columns):
  - IE₁ and EA per element (NIST/CRC, eV) for the 15 reference pairs
  - nearest-neighbour crystal distances r₀: NaCl 2.820 Å, KCl 3.146 Å, MgO 2.106 Å
  - measured lattice energies (Born–Haber): NaCl 787, KCl 715, MgO 3791 kJ/mol
  - Na: Wigner–Seitz radius 2.08 Å, cohesive energy 1.113 eV/atom
- Phase thresholds (committed before run):
  - P1 ionic/covalent split correct for ≥13 of 15 ref pairs via well-depth asymmetry Δχ, χ = (IE+EA)/2
    (SDT reading: mean depth at which the outer electropause sits — hold-depth and capture-depth averaged)
  - P2 NaCl lattice energy within 15% of 787 kJ/mol, correct (cohesive) sign; Madelung-analogue computed
    GEOMETRICALLY (Evjen expanding-cubes over the rock-salt lattice) — the literature value 1.7476 is used
    only as a cross-check AFTER the sum converges, never as input
  - P3 Na cohesive energy within 25% of 1.113 eV from a delocalised-sea occlusion balance
    (point core in neutral uniform sea sphere — Wigner–Seitz occlusion sum, no band theory)
  - P4 novel lattice energy KCl within 20% (MgO also reported, same formula, no refit)
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces;
  importing the literature Madelung constant or Born exponent as input.
- Known-in-advance honesty note: NO Born short-range repulsion term is derived anywhere in SDT yet.
  The geometric sum is therefore EXPECTED to overbind by roughly the (1−1/n) Born factor (~10%). If the
  overshoot lands inside 15% it passes the committed gate; the missing repulsion closure is logged either way.

## Run record

- Tool: `ch02_ionic_metallic.cpp` (single file, `#include <sdt/laws.hpp>`)
- Compile: MSVC cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include
- Output: `results.txt` = verbatim stdout.
