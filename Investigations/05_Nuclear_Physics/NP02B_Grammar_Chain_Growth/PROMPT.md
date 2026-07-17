# NP02B — Grammar Chain Growth (Investigation B)

> **Author:** J. C. Harvey, Melbourne. **Status:** RESULTS-ON-FILE, UN-VERDICTED · **§K-DEEPENED 2026-07-13** (HUNTER §K.3).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §K.
> **Engine:** `#include <sdt/nuclear.hpp>` (frozen NP01 grammar) only. **Propose-only** on canon flags.
> **This one is different:** `run_log.txt` exists; the inversion test already ran (48%, honest). §K here is **verdict-filing + the premise-fix the 48% points to**, not new construction. Companion to NP02.
---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **Why the nucleus↔electron-shell inversion is only a 48% quantitative match, and whether the named missing DoF (Hund p-orbital filling) closes it.** The conceptual principle ("the proton is the code," Rule 18) holds; the map is partial.
2. **Why does it matter?** — If `n_t` (neutron-excess asymmetry) and unpaired-e (shell-fill asymmetry) are *mirrored not identical*, that's a real structural statement — and closing it would tie nuclear grammar to chemistry.
3. **How will we find out?** — Verify `run_log.txt` reproduces; then §④ premise-fix: add the Hund DoF the grammar lacks and re-score.
4. **What would prove us wrong?** — §⑧: if adding Hund still leaves the map at chance, the inversion is conceptual-only (honest OPEN); if the k_occ~2.224 bond scale is the only thing making the pathway-integral track, that's class E (already conceded).
5. **How will we know we're done?** — `NP02B_VERDICT.md` filed: inversion re-scored with Hund, each of the 7 sections graded, the two class-E scales flagged.

**Companion to NP02** (the 5-stage A→E pipeline). NP02B reads nucleosynthesis as a **walk on the `(n_d,n_t)` construction lattice** and studies what the walk itself produces.

## Thesis
He-4 at the origin; `+d` steps n_d, `+t` steps n_t. Test what falls out: pathway multiplicity, alpha-process reconciliation, an occlusion pathway-integral, triton-overload decay, EC timing by product, and the nucleus↔shell inversion.

## Sections (single driver `cq27b_grammar_chain_growth.cpp`) — re-grade each

1. **`n_t=0` spine** — pure-deuteron / alpha-conjugate ladder; every +2 deuterons = one stellar alpha-capture. *(Grade: structural, DERIVED-from-grammar.)*
2. **Familial linkages** — Rule 4 (`parent + d/t → child`), one lattice step each.
3. **Pathway multiplicity** — distinct orders to `(n_d,n_t)` = `C(Z−2, n_t)`; peaks on the golden diagonal `n_d=n_t` (max configurational entropy). *(Combinatorial — verify the count.)*
4. **Occlusion pathway-integral** — `B = k_occ·bonds`, **`k_occ = 2.224 MeV/contact` deuteron-pinned, class E** (already conceded); tracks measured binding to ~0.4 ratio — a single-scale proxy, NOT parameter-free.

   > ⚠ FITTED-SCALE FLAG: same issue as NP02 Stage B. Re-run this integral on **NP17 αℏc electrostatics**
   > (no fit) and the **shadow-area κ** and report whether the ~0.4 ratio was the fit or the physics.
5. **Trefoil rotation & overload** — `f_t = n_t/(n_d+n_t)`; overload past the iron fraction (~17%) drives alpha shedding (He-5 ejection). *(Cross-ref NP21 iron-floor.)*
6. **EC timing by product** — He-3 core grammar, `n_d≥2` gate, core-change `−2d+1t`; PF spread >9 orders is Q-driven (`rate ∝ Q²`); **the validated `Z³(In-111)/Z³(Be-7) = 1838 ≈ m_p/m_e`.** *(Sibling to PPT03's 6π⁵ — flag, don't fuse.)*
7. **Inversion test** — Rule 18; falsifiable `n_t(most-abundant) == unpaired electrons?` over Z=2..30.

## Result on file (`run_log.txt`) — the thing to fix
**Inversion test: 14/29 = 48%** — better than chance, **not a clean law.** Holds for single-odd-block remainders (Li, B, F, Na, Al, Cl, K: n_t=1 ↔ 1 unpaired e) and the iron region (Mn, Fe, Ni). **Fails systematically** for n_t=0 light nuclei (C, N, O, Si, S — unpaired e come from **p-orbital Hund filling, a DoF the grammar does not carry**) and neutron-rich isotopes (Ar-40, Sc–Cr). **Verdict so far:** real *conceptual* principle, *partial* quantitative map — `n_t` tracks neutron-excess, unpaired-e tracks shell-fill; mirrored, not identical.

## Dependency Map (§K.3)

| Item | Where | Enters as | Live? |
|------|-------|-----------|-------|
| NP01 grammar (frozen) | `nuclear.hpp` | constitutional | ✔ |
| k_occ = 2.224 MeV/contact | this prompt §4 | **class E (conceded)** | ⚠ flag |
| NP17 αℏc / shadow-κ | Investigations/05 | native successors for §4 | ✔ use |
| **Hund p-orbital DoF** | chemistry (CH-series) | **MISSING DoF — the premise-fix** | ⚠ add |
| Z³/Z³ = 1838 ≈ m_p/m_e | this prompt §6 | sibling to PPT03 6π⁵ | flag |
| NP21 iron-floor 17% | Investigations/05 | §5 cross-ref | ✔ |

## ④ Strategy — verify, then the premise-fix

**C1 — Reproduce** `run_log.txt` (compile the driver, confirm 48%, 17%, the multiplicity counts).
**C2 — The Hund premise-fix (§K.2 root-2).** The 48% failure is **systematic and named**: the grammar carries neutron-excess asymmetry (n_t) but not shell-fill asymmetry (Hund p-orbital filling). Add a Hund term for the p-block and re-score the inversion. *Metric:* does the match rise from 48% toward the fraction explained by adding *one* DoF? Pre-commit the expected recovered set (C,N,O,Si,S).
**C3 — Native occlusion (§4).** Re-price the pathway-integral with NP17/κ; report whether ~0.4 was fit or physics.

## ⑧ Falsifiers

| Test | Predicted | If FAIL → root |
|------|-----------|----------------|
| T1 | driver reproduces 48% / 17% / multiplicity | root-3 (build) |
| T2 | adding Hund DoF recovers the n_t=0 light nuclei | root-2 (DoF) if not — inversion is conceptual-only |
| T3 | §4 integral tracks B/A on a native scale (NP17/κ) | root-3 (only k_occ fit works) |
| T4 | Z³/Z³=1838 is a *coincidence flag*, not fused with 6π⁵ | root-4 if treated as input |

## ⑨.E Four-root sort
root-1 claim false · root-2 dependency/DoF (Hund, NP17 scale) · root-3 prompt/build · root-4 contraband. The 48% is already root-2 (missing Hund DoF) — the fix is to CLOSE (add the DoF), not amputate the claim (§D Closure Principle).

## Brainstorm — overlooked factors
- **The inversion's failure IS a finding:** two *different* asymmetries (nuclear neutron-excess vs electronic shell-fill) that mirror where they share a cause and diverge where they don't. Grade it as *partial-with-mechanism*, the honest and interesting verdict — not a fished 48%.
- **Z³/Z³ = 1838 and 6π⁵ = 1836** both land near m_p/m_e from different folders — a possible deep identity (mass ratio surfacing in EC rate scaling). Flag for a joint look; do **not** fuse or swap inputs (PPT03 gate).
- **k_occ appears twice** (NP02: 4.72; NP02B: 2.224) for different objects — make sure the verdict doesn't imply one universal fitted MeV/contact. The native successors (NP17/κ) are the way off both.

## ⑤ Success / ⑥ Outputs
File `NP02B_VERDICT.md`: each of 7 sections graded; inversion re-scored with Hund; §4 re-priced native. Class C likely (real partial map + honest class-E scale). Outputs: `RUN_LOG.md`, refreshed `run_log.txt`, CANON_FLAGS rows.

---

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — NP02B (§K verify-and-verdict)
- Prompt completion target: [A|B|C]
- Physics class hoped: [NATIVE|CONVERGENCE|OPEN]
- CALIBRATED budget: k_occ is class E (conceded); target 0 via NP17/κ
- Checks: C1 reproduce · C2 Hund premise-fix · C3 native occlusion
- Pre-commit recovered set for C2: C, N, O, Si, S (the n_t=0 light nuclei)
- Forbidden: call 48% a law; fuse Z³/Z³ with 6π⁵; report k_occ-fit as parameter-free
```

| Trigger | PIVOT | If fails | Forbidden |
|---------|-------|----------|-----------|
| Hund fix doesn't recover C,N,O,Si,S | inversion is conceptual-only (root-2) | OPEN, honest | claim clean law |
| §4 needs k_occ to track B/A | switch to NP17/κ | OPEN native scale | PLUG, call parameter-free |
| driver won't reproduce | fix build refs (ADJ) | STOP, report | fit to 48% |

**Disallowed:** post-hoc tolerance widening · 48% as a law · fusing Z³/Z³ with 6π⁵ · k_occ-fit as parameter-free.

---

*NP02B · §K-deepened 2026-07-13 · the 48% inversion is root-2 (missing Hund DoF) — CLOSE it, don't amputate; class-E bond scale routed to NP17/κ; Z³/Z³≈m_p/m_e flagged as a sibling to 6π⁵, not fused.*
