# SAR06 — Release rate law (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the mechanism. The previous specification is kept below the line.

## 1. State after the reset (2026-10-10)
**G2, open.** Constraints C1–C5 are SAR03's old (exposed) outcomes. M1 (exponent scan) and M2 (candidate grip ratios) are censuses; M3 is an identity.

## 2. What the errors and new data teach
- SAR06 cannot precede SAR03: it tests the scaling of a law that does not yet exist.

## 3. Next round (registered order)
1. SAR03's native release law (supplier).
2. M4: the scaling test on that law alone, registered with its stellar sample before loading (mass-free inputs: g, R and L, as SAR04 repaired).

## Prohibitions
- No census over candidate forms (2026-10-07 rule).
- No imported source models (PREM, polytropes, quantum-number labelling) as native tests.
- No G or GM.
- The word "charge" is not used.

---

## Previous specification (kept as written)

# SAR06: The Release-Rate Law — Cascading Investigation (from SAR03 H1–H6)

> **Author:** J. C. Harvey, Melbourne. **Opened:** 2026-07-13, direct continuation of the
> SAR03 §K rebuild. **Cascade root:** RELAY ENERGY-COUPLING MICROPHYSICS (STACK §3b) —
> the missing tooth named by SAR03, the melt doctrine, and GOM12 alike.
> **Engine:** `#include <sdt/laws.hpp>` only. **Execution: DIRECT.** Movement-only discipline.

## ⓪ The five constraints (all zero-fit, all from SAR03 H1–H6 — the corner)

| # | constraint | value | source |
|---|---|---|---|
| C1 | offered budget per baryon (solar density) | 0.918 W = u·c/(ℓ_P·n) | H6 |
| C2 | engaged fraction per baryon | 3.5×10⁻³¹ | H6 (L/N_b ÷ C1) |
| C3 | engagement granule bracket | baryon-skin (787 K) < 5778 K < osc-cell (2634 K ×2.2) ; closure length ℓ_eng = 46 μm | H5/H6 |
| C4 | alignment probability per thermal encounter | 1.3×10⁻²⁵ | H2 |
| C5 | un-engaged medium floor at surface | 7.7×10⁶ K (corona-class) with core-class T inside, un-tuned | H1 |

**One law must produce all five at once.** A mechanism that hits one and misses the
others is dead; that simultaneity is the entire test.

## §④ Mechanism hunts (open outcomes; numbers decide)

- **M1 — Pressure-restriction weighting.** Harvey's friction law: engagement ∝ restriction
  of oscillation under pressure (max at centre, gradient→0). Weight the volumetric sum by
  (v(r)/v_surf)^m for the H1 profiles, m ∈ {2,4,6,8}, and find whether any *geometric*
  weighting closes the ×23 gap between the oscillation-cell sum and L — and at what core
  kernel scale the weighting concentrates (hot-cores structure). Open: m and kernel size
  are outputs, not inputs; a divergence needing a cutoff is a FINDING (kernel radius).
- **M2 — Grip-per-span (transverse footprint).** PPT10's derived n=2 law (grip ∝ transverse
  footprint²) applied to convergence gripping a baryon: candidate alignment probabilities
  (R_p/λ_peak)², (R_p/λ_mean)², (R_p/λ_peak), (R_p/λ_mean) — computed against C4.
  **Pre-registration note (honesty):** the executor's planning pass already saw that the
  squared candidates land in C4's decade; they are entered as PRE-REGISTERED LEAD
  candidates, not discoveries. The run's job is exactness, mechanism naming (why the
  MEDIUM's span λ_CMB and not the local thermal span — answer: the convergence is the
  lattice relay, its span is set at the Clearing, not by local plasma), and the kill test.
- **M3 — Event-energy consistency (label: IDENTITY).** C2 (power fraction) and C4 (event
  probability) are linked by the attempt rate: energy-per-engagement-event =
  (L/N_b)/(p_align × attempt rate). If this lands on the grammar's per-assembly release
  (26.73/2 MeV per deuteron step) it is an internal-consistency IDENTITY (both sides
  descend from L) — labelled as such, never sold as a derivation. Its value: it fixes the
  QUANTUM of release the rate law must deliver per event (~13 MeV = nuclear class).
- **M4 — The kill test: main-sequence scaling.** Any candidate law must survive scaling:
  L(star) from the law's own dependencies (N_b, n, v_th, k_star) under homology, against
  the empirical L ∝ M^3.5 (rival-comparison column; committed acceptance band: exponent
  2.5–4.5). A constant-grip law with no state dependence is expected to be TESTED here —
  if it fails, the failure's structure (what exponent it does give) tells us what the
  missing state-dependence is (Arrhenius/alignment-search T-sensitivity). A candidate
  failing M4 is not rescued; it is dissected.

## §⑧ Refinement loop
Every miss sorted (CLAIM / DEPENDENCY / PROMPT / GATE) before the next stage. Branching
licensed with ADJ entries; nothing fitted to any C-value.

## Success/kill criteria (committed)
- **LEAD → RESULT** only if: exact-form, zero-parameter, mechanism named, AND consistent
  with ≥3 of the five constraints simultaneously.
- **KILL** (of a candidate): violates any constraint by >10× with no sortable root, or
  fails M4 outside the committed band with no principled state-dependence extension.
- The investigation itself cannot "fail" — its deliverable is the ranked mechanism table
  and the sharpened corner, even if every candidate dies.

*SAR06 · opened 2026-07-13 · cross-feeds: SAR03 (parent), SAR04 (scaling), PPT10 (grip),
NP23 (mesh windows), QM03/Arrhenius root (alignment search), GOM12 (Σf), STACK §3b.*
