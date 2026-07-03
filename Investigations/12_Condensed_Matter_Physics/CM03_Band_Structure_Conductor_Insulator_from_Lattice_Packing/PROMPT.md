# CM03 — Band Structure / Conductor–Insulator from Lattice Packing

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Is the conductor / semiconductor / insulator trichotomy — and the
   *magnitude* of the "band" gap — fixed by **lattice packing geometry alone** (coordination +
   bond directionality blocking the relay channels of a drifting W=1 vortex), or does any honest
   account of the gap *scale* secretly require a Bloch-wave / k-space band parameter put in by hand?
   Concretely: can `E_g(C) > E_g(Si) > E_g(Ge)` be ordered *and* sized from packing, with no
   dispersion relation imported?
2. **Why does it matter?** — CM03 sits on top of CM02 (the conduction node) in the stack: it decides
   whether "band gap" is a native occlusion blockade or a smuggled QM construct. If packing fixes the
   gap, CM06's carrier-sign and CM01's gap-vs-pairing distinction inherit a native gap; if not, the
   whole semiconductor branch is borrowed.
3. **How will we find out?** — Four gated phases (§④): packing classification (P1) and the
   traction-grip gap scale (P2) run *before* any comparison to measured `E_g`; importing a Bloch
   band parameter or fitting per-solid caps the grade at C.
4. **What would prove us wrong?** — §⑧: three falsifiers with numeric triggers and real failure
   modes — the trichotomy ordering (T1) and the gap-magnitude test (T3) can both come out wrong.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, with no repainting of a fired test.

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

## Falsification tests (each has a real failure mode + numeric kill trigger)

| # | Test | SDT prediction (numeric) | What KILLS it |
|---|------|--------------------------|---------------|
| T1 | Trichotomy = packing blockade | for ≥9 elements (Cu, Ag, Al, Si, Ge, C-diamond, Sn-grey, S, P): metal/semi/insulator class is recovered from coordination + bond directionality, **0 misclassifications** | if packing geometry mis-sorts ≥2 of the 9 (e.g. predicts diamond metallic or Cu insulating) → conduction class is not packing-set; thesis dead |
| T2 | Semiconductor = thermally bridged channel | `dρ/dT < 0` for Si/Ge and `ln ρ` linear in `1/T` with slope `E_g/2k_B` (Si: E_g≈1.12 eV) | if SDT gives `dρ/dT > 0` (metallic sign) for Si/Ge, or no activation, → the gap is not a thermally bridgeable relay channel |
| T3 | `E_g` from traction grip (PPT06) | ordering `E_g(C 5.5 eV) > E_g(Si 1.12) > E_g(Ge 0.67)` AND magnitudes within 2× from one fixed O(1) geometric factor (same factor for all three) | if the *ordering* inverts, or each solid needs its own fitted factor to hit 2×, → the gap scale needs a Bloch/band import (→ C, not A) |

## Dependencies

**Upstream:** CM02 (drift channels), CM04 (lattice geometry), Law III (occlusion), PPT06 (traction
grip). **Downstream:** CM06 (Hall sign of carriers), CM01 (gap vs pairing). **Related:** APS01
(lattice geometry); the metal-vs-insulator ordering as a packing theorem.

## Implementation notes

Double precision; carrier-class as a discrete label, gap in eV. The gap is a geometric **occlusion
blockade**, not a forbidden energy substance — never write "charge band"; "band/gap" here is the
relay-channel-availability narration only. Keep all measured lattice constants / coordination numbers
in one labelled MEASURED-INPUT block; the textbook `E_g` values are the convergence target, never the
hard-coded answer. No Bloch waves, no k-space dispersion, no electron "clouds". Author attribution in
all generated files: **J. C. Harvey, Melbourne.**

## Questions This Opens *(generative — log new ones in `CM03_VERDICT.md`)*

Not required for the verdict; this is the payoff of doing it well.

1. **Is the metal/insulator line a single packing threshold?** Is there one critical
   coordination-×-directionality number above which all channels close — a sharp packing transition —
   and does any borderline solid (grey vs white tin, the Si↔metallic-Si pressure transition) sit
   right on it?
2. **Does pressure (smaller spations, GOM05) close or open gaps the SDT way?** If squeezing the
   lattice changes the relay-channel geometry, can CM03 predict the *sign* of dE_g/dP for Si, Ge,
   diamond — and the metallisation pressure of hydrogen?
3. **Is the O(1) geometric factor universal or element-family-specific?** If one factor sizes C/Si/Ge
   but a different one is needed for III–V compounds, what packing feature distinguishes the families?
4. **Does doping = a single opened channel?** Is a donor exactly one substitutional defect that opens
   one relay channel, so carrier density is a literal *count* of dopant sites — testable against the
   measured 1-carrier-per-dopant rule?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CM03
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the trichotomy chain (one O(1) geometric factor for E_g magnitude may be CALIBRATED(1) — must be the SAME factor for all solids)
- Engine namespaces actually used: law_III (occlusion), law_VI (traction grip / PPT06), bridge; CM02 drift channels
- Phase thresholds (committed before run):
    P1 trichotomy 0 misclassifications over ≥9 elements · P2 E_g ordering C>Si>Ge AND within 2× on one factor
    P3 dρ/dT<0 for Si/Ge, ln ρ vs 1/T slope = E_g/2k_B · P4 carrier sign flips n↔p qualitatively
- Forbidden retroactive changes: import a Bloch/k-space band parameter then claim A; per-solid refit of
    the geometric factor; widen tolerances; plug E_g; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 mis-sorts ≥2 of the 9 elements | refine the directionality metric (bond-angle weighting); re-sort | **OPEN**: report which class fails and why | hand-assign the class to force the sort |
| P2 E_g ordering inverts (e.g. Ge>Si) | re-derive the traction-grip scale from PPT06; check the lattice-constant input | **OPEN** the gap scale; still A on ordering if P1 holds | retro-fit a per-solid factor and grade A |
| P2 magnitudes need a different factor per solid | down-grade to **C** (the per-solid factor is the smuggled band parameter) | — | claim A with one factor per solid |
| P3 dρ/dT sign wrong for Si/Ge | check thermal-throughput coupling (CM04 c_s amplitude) | **OPEN**: report the activation form | fake a linear Arrhenius fit |
| Rivals (band theory) match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |
| Upstream dependency missing (CM02/CM04 not run) | **DEFER** the affected phase; cite dependency ID | — | fake the gap |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** packing metrics (coordination weighting, bond-directionality measures).

### Disallowed adjustments

- Importing a Bloch/k-space band parameter into the native chain and grading A · per-solid refit of the
  geometric factor · post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in any native
  chain · "charge band" substance language.

---

*CM03 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
