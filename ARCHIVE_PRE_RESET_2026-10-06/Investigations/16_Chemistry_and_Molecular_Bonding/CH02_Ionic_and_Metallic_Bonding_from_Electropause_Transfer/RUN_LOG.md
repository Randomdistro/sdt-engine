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
  (derivation basis expression; the engine itself labels it class F / definitional identity — this is DECLARED, not hidden).
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

---

# RUN 2 — ADJ-R2-1 (2026-07-06, committed BEFORE any tool exists): Phase A, the isoelectronic fork

Executes RUN 2 PROMPT Phase A (GATE-A verbatim in PROMPT.md §R2 A.3 — not restated, not modified).

## Declared instrument (sources chosen NOW)

- **S1 (range):** Shannon (1976) effective ionic radii, 6-coordinate, three isoelectronic
  series — He-shell {Li+, Be2+, B3+}, Ne-shell {O2-, F-, Na+, Mg2+, Al3+, Si4+}, Ar-shell
  {S2-, Cl-, K+, Ca2+, Sc3+, Ti4+}. Test: radius strictly decreasing with Z within each shell.
- **S2 (hardness):** measured bulk moduli B0 of STRUCTURE-MATCHED (rocksalt) isoelectronic
  crystal pairs at fixed shell pair: NaF vs MgO [Ne/Ne], KF vs CaO [Ar-cation/Ne-anion],
  KCl vs CaS [Ar/Ar]. Test: B0 rises with cation Z in every pair. LiF vs BeO EXCLUDED from
  the gate (BeO is wurtzite — structure mismatch); reported as a caveat row only.
- **Null:** Z-shuffled Monte-Carlo on each series (exact permutation probabilities also printed).
- **Diagnostic column (REPORT-ONLY, declared with a §G.1 disclosure):** the z-deconvolved
  Born exponent n from the compressibility relation n = 1 + 18*B0*r0^4/(alpha_M*k_e*e^2*z+z-).
  **DISCLOSURE:** during ADJ design this column was previewed by hand for NaF (~7) and MgO
  (~4.5) and found NON-monotone-downward. It is not being buried: it is printed prominently
  as a TENSION row. It is excluded from the gate for a reason stated now, before the tool
  runs: n is the z^2-deconvolved power-law SHAPE of the total equilibrium stiffness, while
  GATE-A's claim concerns the wall's stiffness at engagement; deconvolving by the rival's
  z^2 Coulomb prefactor contaminates the shape parameter with the attraction ledger. If the
  reader judges this exclusion special pleading, the gate may be re-scored with S3 included —
  the verdict will print both scorings. Nothing is hidden.

## §G.2 rival-degeneracy declaration (BEFORE results)

The rival (Z_eff contraction of a fixed shell) predicts the SAME sign: smaller, harder ions
with rising Z at fixed shell. Therefore: **a PASS here is CONVERGENCE-class evidence** —
consistent with transmission, not discriminating against the rival. **Only a FAIL
discriminates** (flat hardness/range at fixed shell would kill the transmission claim's
chemistry expression outright). This run is a KILL-GATE for refinement 8's chemistry leg,
not a NATIVE earn. Any stronger claim in the verdict is contraband.

## Data provenance

All inputs are measured literature values in their measured units (Å, GPa) — data-boundary
per the no-borrowed-units rule; 2–4 s.f.; each row carries its source tag in the tool.
No G, M, or GM anywhere (none is needed). Gates: GATE-A as committed in PROMPT.md — not
widened, not narrowed. Tool: `ch02_r2_isoelectronic_fork.py` → teed
`ch02_r2_isoelectronic_results.txt`.
