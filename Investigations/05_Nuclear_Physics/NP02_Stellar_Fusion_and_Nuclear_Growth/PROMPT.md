# NP02: Stellar Fusion, Nuclear Growth, and Reciprocal Shell Mirroring — Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC · **§K-DEEPENED 2026-07-13** (300% rule, HUNTER §K.3).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §K.
> **Engine:** `#include <sdt/laws.hpp>`, `<sdt/nuclear.hpp>` (frozen NP01 grammar) only. **Propose-only** on canon flags.
> **Run:** Pre-commit per stage in `RUN_LOG.md`; four-root sort (§⑨.E) on every FAIL before the next stage.
---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **Whether the deuteron–triton grammar reproduces the H→Ca growth pathways, occlusion structure, EC timing, and shell-mirror valences with NO fitted scale.** The current occlusion unit `k_occ = 28.30/6 MeV/contact` is **fitted (class E)** — the open gap is replacing it with a parameter-free scale.
2. **Why does it matter?** — Tests the Atomicus grammar as *constitutional* (one way to be per nucleus). Downstream: spallation/fission control (nuclear end-goal) needs the growth lattice + mesh geometry.
3. **How will we find out?** — Five gated stages A→E (§3), each with a pre-committed metric; native occlusion (shadow-overlap area) before any binding-energy comparison.
4. **What would prove us wrong?** — §⑧: mirror-shell valence map ≤ chance; k_occ irreplaceable by a native scale; growth pathways miss known stable nuclei.
5. **How will we know we're done?** — Dual verdict (A–F × NATIVE/…/OPEN). Stage E's PASS/FAIL valence columns are the headline falsifier.

## 1. Objectives

Evaluate dynamical growth of nuclei from the ⁴He core to Z ≤ 20 (H→Ca) using the Atomicus deu/tri grammar: a pathway compiler for fusion trajectories; **geometry-only** contact-occlusion scores; trefoil rotational dynamics under local convergence; stellar/BBN electron-capture (EC) delays via Saha; and the mapping of core geometry to electron-shell geometry (the inversion).

## 2. Theoretical Formulations

### A. Pathway Compiler
`Parent(Z,A) + d → Child(Z+1,A+2)` · `Parent(Z,A) + t → Child(Z+1,A+3)`. Grow recursively from ⁴He `(n_d=0,n_t=0)`. *NP01 grammar FROZEN.* Grammar: `n_t = A−2Z`, `n_d = 3Z−A−2` (EC isotopes use the He-3 alternate grammar).

### B. Occlusion — MOVEMENT-ONLY, and the scale flag
Contact count `B_geom = (6 + n_d + 3n_t) + interface_contacts`.

> ### ⚠ FITTED-SCALE FLAG (in-prompt) — the point of Stage B
> `E_occ_unit = k_occ · B_geom` with **`k_occ = 28.30/6 ≈ 4.72 MeV/contact` is a FITTED scale (class E)** —
> normalised to the alpha binding. **Two parameter-free successors now exist and MUST be tried first:**
> (1) **NP17 electrostatics** `E = −Σ q·q·(αℏc)/r` — *no fitted scale* (deuteron PASS, factor-3 exact);
> (2) **shadow-overlap area** (Nuclear Packing Sequencer) `ΔA = A_sum − A_∪`, one scale κ~10.7 MeV/fm²,
> total-BE R²=0.988. **Movement reading:** occlusion is *shared shadow area* (mass defect = overlap of
> occlusion disks), NOT stored binding energy. Stage B's real job: does B_geom, priced by a *native*
> scale (NP17 or κ), track the measured B/A curve? If only the fitted k_occ works → OPEN, do not PLUG.

### C. Trefoil Windings — align with PPT06
W=3 nucleons, surface k_p ≈ 0.5464, v_phase = c/k_p ≈ 1.83c.

> **CROSS-REF (supersedes the old "proxy ONLY" safeguard):** per PPT06, the 1.83c is a **real lattice
> relay deficit**, and the superluminal *demand* IS the force (surplus sheds as ℓ=1/2/3 channels). Do not
> demote it to "a bookkeeping proxy with no physical meaning" — that undersells the mechanism. It is not a
> material/signal transport velocity (correct), but it is a real phase-winding demand (PPT06). Even n_t →
> counter-rotating triton pairs cancel outer wake drag (stability); odd n_t → unpaired wake.

### D. Electron Capture (EC) Timing
Ionization gate (fully ionized → no EC); Saha for bound-e density at the nuclear surface; suppressor: free e⁻ have high v_trans → small v_circ (Law V budget) → no coupling to the W=3 core. High T suppresses EC.

### E. Inverted Mirror Mapping
`(n_d,n_t)` arrangement sets convergence-field symmetry axes; electron shells occupy the geometric voids (n_d=4 C-12 → tetrahedral; n_d=6 O-16 → octahedral). **Validation:** predicted shell categories vs known valences, PASS/FAIL columns, Z=1..20. *(See NP02B: the inversion is partial — n_t tracks neutron-excess, unpaired-e tracks shell-fill; mirrored not identical. Carry that caveat.)*

## Dependency Map (§K.3)

| Item | Where | Enters as | Live? |
|------|-------|-----------|-------|
| NP01 deu/tri grammar | `nuclear.hpp` (FROZEN) | constitutional input | ✔ |
| k_occ = 28.30/6 MeV/contact | this prompt | **FITTED (class E)** — to be replaced | ⚠ flag |
| NP17 `E=−Σqq αℏc/r` | Investigations/05 | **native successor (no fit)** — Stage B | ✔ use |
| shadow-overlap κ~10.7 MeV/fm² | Nuclear Packing Sequencer | native successor — Stage B | ✔ use |
| v_phase=1.83c, k_p=0.5464 | `laws.hpp:450-453,1268`; PPT06 | mechanism (Stage C) | ✔ |
| Saha / E_ion / n_e | measured atomic data | EC gate (Stage D) | ✔ |
| NP02B inversion caveat | Investigations/05 | Stage E prior | ✔ |

## ⑧ Falsifiers

| Test | Predicted | If FAIL → root |
|------|-----------|----------------|
| T1 | growth pathways reach every stable Z≤20 nucleus | root-1 (grammar gap) or root-2 (NP01) |
| T2 | B_geom × NATIVE scale (NP17/κ) tracks B/A curve | root-3 (only fitted k_occ works) → OPEN |
| T3 | EC suppression follows Saha ionization at stellar T | root-1 |
| T4 (headline) | mirror-shell valence PASS > chance, Z=1..20 | root-2 (missing Hund DoF, see NP02B) |
| T5 | 1.83c read per PPT06, not as inert proxy | root-4 (QM proxy hedge) |

## ⑨.E Four-root sort
root-1 claim false · root-2 dependency (NP01 grammar, NP17 scale, Hund DoF) · root-3 prompt under-specified (native scale) · root-4 contraband. Log per FAIL; shared roots once in STACK.

## Brainstorm — overlooked factors
- **Kill the fitted k_occ.** The whole of Stage B should be re-run on NP17's αℏc electrostatics and the shadow-area κ. If the grammar's growth structure only "works" with a fitted MeV/contact, that is a class-E crutch, not a result.
- **Mass defect = shared shadow area** (occlusion overlap), not deposited energy (movement-only; Two-Ledger Lemma). Stage B priced this way is the honest form.
- **Hund DoF is the mirror-map's missing piece** (NP02B): n_t=0 light nuclei (C,N,O,Si,S) get unpaired electrons from p-orbital Hund filling — a DoF the grammar doesn't carry. Stage E should *predict where it will fail* for this reason, not paper over it.
- **1.83c ≡ counter-seat** (NP15 μ_n, NP20 Q_β) — Stage C's rotation is the same object; cross-check, don't re-derive independently and call it confirmation.

## ⑤ Success / ⑥ Outputs
Class A: all 5 stages pass with a NATIVE occlusion scale (no k_occ fit), mirror-map > chance with the Hund caveat stated. Class C: growth + EC clean, occlusion needs the one κ scale (documented). Outputs: `RUN_LOG.md`, `np02_stellar_fusion_growth.cpp`, `NP02_DERIVATION.md`, `NP02_VERDICT.md` (Stage E PASS/FAIL table), CANON_FLAGS rows.

---

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — NP02 (§K-deepened)
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|OPEN]
- CALIBRATED budget: 0 target (k_occ is the fit being REMOVED; if one κ survives, document as CALIBRATED(1))
- Stages this session: A growth · B occlusion(NP17/κ native) · C spin(PPT06) · D EC(Saha) · E mirror
- Native scales to try before k_occ: NP17 αℏc electrostatics; shadow-area κ~10.7 MeV/fm²
- Forbidden: report k_occ-fitted B/A as parameter-free; demote 1.83c to inert proxy; hide Hund-DoF mirror failures
```

| Trigger | PIVOT | If fails | Forbidden |
|---------|-------|----------|-----------|
| B_geom only tracks B/A with fitted k_occ | switch to NP17 αℏc / κ shadow-area | OPEN native scale | PLUG k_occ, call it derived |
| mirror-map fails on n_t=0 light nuclei | add Hund DoF (root-2), state prediction | OPEN partial map | claim clean inversion |
| growth misses a stable nucleus | check NP01 grammar branch (EC alternate) | DEFER to NP01 | invent a decomposition |
| EC curve off | check Saha inputs/units | OPEN | fit to observed half-lives |

**Disallowed:** post-hoc tolerance widening · k_occ PLUG reported as parameter-free · inventing decompositions outside NP01 · 1.83c as inert proxy.

---

*NP02 · §K-deepened 2026-07-13 · fitted k_occ flagged and routed to NP17/κ native successors; 1.83c aligned to PPT06; Hund DoF named as the mirror-map's missing freedom.*
