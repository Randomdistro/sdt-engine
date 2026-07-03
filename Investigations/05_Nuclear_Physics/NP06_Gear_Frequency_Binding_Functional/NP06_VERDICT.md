# NP06 (CQ-50) — VERDICT / KILL REPORT: Gear-Frequency Binding Functional

> **Author:** J. C. Harvey, Melbourne. **Run:** 2026-07-03. **Engine:** `sdt/laws.hpp` only.
> Tool: `np06_gear_frequency.cpp` (MSVC exit 0) → `np06_results.txt` (redirected stdout).
> Sealed set: NP05's `sealed/answers.json` (AME2020); committed predictions preceded comparison.
> Deliverables D1 (RUN_LOG contact graph) and D2–D6 (this file + tool) folded per ADJ-001 (format only).

## Dual verdict header

| Axis | Grade | One-line |
|------|-------|----------|
| **Prompt completion** | **B** | The hypothesis was given its honest shot in the prompt's own order (derivation → anchor → sealed nuclear gate) and died at every stage; the kill report with named successor is the deliverable the prompt itself ranks first (R4). |
| **Physics class** | **KILLED** (`E_bind = ℏΔω` as a kinematic mesh pull) | κ_geom is not derivable at CALIBRATED(0); the H₂ anchor fails structurally (0 vs 4.52 eV); 8/8 sealed Q-values fail even with a CALIBRATED(1) crutch. |

## D2 — the derivation result (the kill-shot)

The committed inventory of dimensionless quantities in the no-slip ring-contact geometry
(overlap 0, contact-arc 0, axis cosines O(1), speed/winding ratios 1) contains **no energy
scale**: a rigid no-slip constraint locks phase but stores no energy, and a normal-mode
split requires a stiffness U(Δφ) that pure kinematics does not supply. Every derivable κ is
0 or O(1), while the data require κ ≈ 2.4–5.0×10⁻³ (nuclear, ×2.12 spread at *identical*
contact geometry) and 4.8×10⁻⁹ (H₂). **Gω died at the derivation stage** — by the committed
rule, before any energy was compared.

## D3 — the anchor (H₂, committed before comparison)

Protons at 1.4 a₀ sit 44,025 rim-radii apart: a *contact* mesh predicts ε = 0 vs 4.52 eV —
structural FAIL. A contact-blind mesh with the deuteron's κ gives 2.22 MeV — off by ~5×10⁵.
The cross-scale coupling must be carried by a **ranged 1/r interaction**, which is a wake/
field well, not a frequency pull.

## D4 — the sealed nuclear gate (failure-shape, CALIBRATED(1) declared)

With ε locked to the deuteron (a crutch the gate itself forbids): t −21.3%, α −52.8%,
Li6 −37.4%, Be9 −46.5%; **8/8 Q-values FAIL ±15%** (−75% to +202%). Both diagnostic targets
from the prompt fail: (a) the even α mesh does NOT naturally over-bind α (−52.8%); (b) the
loose clusters over-bind per contact (+202%/+183% on R7/R8). The residuals sort exactly like
NP10's: the deficit **grows with coordination** — the same coordination-dependent lock
signature, unreachable by any per-contact constant.

## D5 — parameter ledger

DERIVED: Ω₀ = m_p c²/ℏ (printed once, flagged FORBIDDEN-IDENTITY per R5, never load-bearing);
contact graph integers. MEASURED-INPUT: sealed AME2020 set, H₂ 4.52 eV (OBSERVED, in-prompt).
CALIBRATED: one (ε := B_d), used only to demonstrate failure shape — declared in RUN_LOG
before the run, never claimed as a pass. **CALIBRATED(0) target: not met — and provably not
meetable within the hypothesis.**

## D6 — kill report + successor (named in RUN_LOG before the run)

**KILLED: binding is not a kinematic mesh-coupling frequency pull.** Successor: the **NP17
shared-electron Coulomb well** — it supplies precisely the two things the mesh lacked: an
interaction *scale* (αℏc) and a *range* (1/r), and it has already paid the deuteron
(2.200 vs 2.224 MeV, −1.06%, no fitted scale). The prompt's own §5 contingency is hereby
realised: **two clean kills** (volume price — NP05/CQ-32; frequency pull — NP06) form a
structural result: binding is irreducibly a *mediated ranged interaction plus a
coordination-dependent lock* (NP10's constraint curve: ×1.0 / ×2.0 / ×6.4 for d/t/α),
not any single local geometric or kinematic price.

## §D Seven questions (HUNTER_PROTOCOL)

1. **Why exactly?** No energy scale exists in the kinematic mesh (κ derivable only as 0 or O(1)); magnitude failures follow at every gate (0 vs 4.52 eV; 8/8 Q-values; ×2.12 per-bond spread).
2. **Recoverable?** Not within the hypothesis — recovery would require inserting a stiffness, and any stiffness IS an interaction energy, i.e. the successor mechanism, not a rescue of this one.
3. **What did the target fail to account for?** That "rolling contact" constrains phase but does not bind; binding needs mediated energy exchange with range.
4. **Which premise erred?** "The bond energy is stored in the pulled normal mode of a kinematically meshed pair" — the mesh has no mode-pulling stiffness of its own.
5. **What freedom corrects it?** A ranged interaction well between the rotors: the shared-electron αℏc/r well (NP17), plus the coordination-dependent lock (NP10).
6. **Native or knob?** Native — αℏc is the engine's Coulomb identity and the well geometry is committed; nothing tuned (the lock magnitude remains the known open debt).
7. **Cascades?** The kill itself is terminal (no shared root; the hypothesis was wrong, not blocked). Its residual *pattern* cascades to the same root as NP08/NP10: the NP17-PENDING coordination-dependent lock.

**Recovery grade: NO RECOVERY** (for the frequency-pull hypothesis itself — premise error is
fundamental; the *problem* it addressed is carried forward by the named, partly-paid successor).

## Stress-test self-audit

1. **Identity/circularity:** the R5 trap (ℏΩ_rim = mc²) was printed once, flagged, and never used. The reverse-ledger κ_req values consume sealed data and are labelled REQUIRED-NOT-DERIVED.
2. **Fished factors:** none; the single CALIBRATED(1) was pre-declared as a failure-shape probe and the gate was failed WITH it, which is the opposite of fishing.
3. **Dimensions:** κ dimensionless (ε/m_p c²); all energies MeV; H₂ eV↔MeV conversion explicit.
4. **Two-stream (R3):** the kill needs no numerics to verify — the derivation-stage argument (no stiffness ⇒ no split) and the numeric ledger (spread ×2.12 / ×5×10⁵) are independent routes to the same verdict.

---

> **Prompt completion B · Physics class KILLED (kinematic frequency pull; successor NP17 named-and-partly-paid) · Recovery NO RECOVERY (premise fundamental) · Cascade root: none for the kill itself; residual pattern → NP17-PENDING coordination lock (shared with NP08/NP10)**

*NP06 · executed 2026-07-03 · killed clean at the derivation stage, confirmed at anchor and gate · the successor was already on the books.*
