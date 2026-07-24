# GOM09: Earth-Core Seismic Speeds from Occlusion Stiffness — the re-adjudication run, with the NP30 shear route

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **full upgrade 2026-07-24** (supersedes
> 2026-06-27). **Register status: this investigation's prior FAIL (v_p 11.5%, v_s 28.0% — E97
> PARTIAL) was agent-run and stands as UNCONFIRMED-FAIL under Harvey's 2026-07-12 voiding ruling.
> The direct re-run specified here IS the re-adjudication** — outcome space per the register:
> KILL-CONFIRMED / OVERTURNED→OPEN / OVERTURNED→PASS, with the §H.LEASH check both ways.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` · `PROMPT_EXECUTION_PROTOCOL.md` · HUNTER §0/§G ·
> register re-adjudication rules (READ SOURCE · RE-RUN · GATE AUDIT · MECHANISM).
> **Engine:** `#include <sdt/laws.hpp>` only. **Execution: DIRECT ONLY — no agents.**
> Prior agent-era VERDICT/RESULTS/outputs deleted 2026-07-24 (git-recoverable).

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — Three separated questions the prior run blurred into one FAIL:
   (a) the **convergent leg**: does the koppa-only interior profile g(r), P(r) still land at
   ~2% RMS on PREM when run direct (it should — the enclosed-mass integral is shared algebra
   with Newton via the bridge; that part is CONVERGENCE and was never the problem);
   (b) the **native leg**: can the bulk stiffness K(r) really be built from occlusion at nuclear
   scale (P_eff, R_p, internuclear spacing) with no material-science modulus — or was the
   11.5%/28% miss structural, meaning bare occlusion cannot price matter stiffness without the
   packing grammar; and
   (c) the **new route that did not exist in June**: NP30 §10's connection law (a contact must be
   shear-free in BOTH poloidal and toroidal rotation → exactly SIX connection orientations per
   nucleon) supplies, for the first time, a native origin for **directed** bonds — i.e. for the
   shear modulus G(r) as a derived FRACTION of K(r) set by connection geometry, and for the
   outer-core G = 0 criterion (connections unlocked past the lock distance). Does that close the
   v_s gap the old run failed at 28%?
2. **Why does it matter?** — E97 sits in the campaign graveyard on its seismic leg while its g(r)
   leg is one of the honest interior results; the register owes this item a direct ruling; and
   the K/G question is the macroscopic face of the NP30 packing program — if connection geometry
   prices shear here, the nuclear and geophysical sectors close on one mechanism. The falsifiable
   SDT≠GR interior claim (centre-of-Earth: crushed vs weightless) also lives downstream of an
   earned interior profile.
3. **How will we find out?** — §④: P0 source+GM audit (the trefoil tool carries a standing
   GM-sweep suspicion — that audit is now a gate); P1 convergent leg re-earned; P2 the occlusion
   K route with every coefficient labeled; P3 the NP30 shear route (new); P4 discontinuities,
   outer-core unlock, anisotropy (stretch); P5 travel times (stretch).
4. **What would prove us wrong?** — §⑧: P2/P3 missing PREM by >30% anywhere after honest
   calculation kills the occlusion-stiffness route (KILL-CONFIRMED — the honest outcome the
   re-adjudication must be ready to file); G > 0 in the outer core kills the unlock criterion;
   the GM audit finding load-bearing GM in the "native" chain voids the prior g(r) credit too.
5. **How will we know we're done?** — Dual verdict + the register ruling line (one of the three
   outcomes, with the mechanism named) + the K/G provenance ledger.

## §0 Reader's contract

1. **Re-adjudication discipline (register rules, verbatim duty):** read the tool sources fully;
   re-run direct; audit every kill-gate for contraband; no ruling without naming the mechanism.
   The prior FAIL numbers (11.5%/28%) are declared here as anchors of the OLD run — the new run
   may not steer toward or away from them; they exist so the re-adjudication can say whether the
   old numbers reproduce.
2. **The split labels.** g(r)/P(r) = CONVERGENCE (shared integral; the bridge makes it Newton's).
   K_SDT, G_SDT = the NATIVE claims. Never quote the 1.82% g(r) as evidence for the native leg.
3. **PREM provenance.** PREM values in-tool must carry their citation (Dziewonski & Anderson
   1981) and a printed row-count/checksum at run; the clean path is MUST_FETCH **F7** (the
   electronic PREM table → `Datasets/geophysics/`) — fetch it, manifest it, and point the tools
   at the cached copy. Hand-embedded arrays without citation = provenance violation.
4. **No material moduli as inputs.** K and G must EMERGE (P2/P3). ⟨A⟩ per layer (22 silicate /
   56 iron) is an OBSERVED-ANCHOR composition fact, labeled. Any laboratory K or G appearing in
   the chain = instant fail of the native claim (they may appear in rival columns).
5. **GM-sweep audit is a gate, not a note** (the register lists this folder under suspicion):
   grep all three tools for G, M_E, GM, 6.674, 5.972e24; every hit classified in-chain vs
   rival-column; in-chain hits patched or the affected leg is relabeled TRANSPLANT.
6. **Direct only; teed stdout; fresh dated files; the deleted June layer is not evidence.**

## §1 Definitions and anchors

| Quantity | Value/form | Label |
|---|---|---|
| g_surface | 9.81 m/s² via c²R_E/(k_E²·R_E²) scaling | CONVERGENCE leg |
| PREM v_p | 5.8 (surf) / 13.7 (CMB mantle) / 8.1 (outer core) / 11.3 km/s (centre) | OBSERVED-anchor (F7) |
| PREM v_s | 0 in outer core; 3.6–7.3 km/s elsewhere | OBSERVED-anchor |
| lattice compression δη | ~1.5×10⁻³⁷ at 364 GPa | DEAD ROUTE (recorded — the lattice is rigid at these pressures; kept as the honest Step-2 self-refutation) |
| K_SDT(r) | (π/4)·P_eff·n^{2/3}·R_p²·R_n²/d(r)² -form (to be re-derived, chain labeled) | NATIVE claim |
| G_SDT(r) | K_SDT × f_shear(connection geometry) — **f_shear from NP30 §10 six-orientation law** | NATIVE claim (new route) |
| prior-run anchors | v_p RMS 11.5% · v_s RMS 28.0% · g(r) 1.82% | OLD-RUN anchors (reproduce-or-explain) |
| 410/670/2891 km transitions | 13.4 / 23.8 / 136 GPa | OBSERVED-anchor (stretch phase) |

## §④ Phases

**P0 — Source + GM audit (gate).** Read `gom09_seismic.cpp`, `gom09_backward.cpp`,
`gom09_trefoil_test.cpp` in full. Deliver: (a) the GM-sweep table (every G/M literal, in-chain vs
rival-column, disposition); (b) the PREM-data provenance report (embedded vs F7); (c) what each
tool actually computes (the backward and trefoil tools' roles stated — the register suspicion
attaches to the trefoil test specifically). No physics phase opens until P0 files.

**P1 — Convergent leg re-earned (direct).** g(r) and P(r) against PREM. Pre-registered gates:
g(r) RMS < 3% (old: 1.82%); P(centre) within 5% of 364 GPa. Labels per contract §2. If the old
1.82% does NOT reproduce, the re-adjudication has found the prior run's g-leg unreliable too —
report either way.

**P2 — The occlusion bulk-stiffness route (native, re-derived not re-trusted).** Re-derive
K_SDT(r) from occlusion at nuclear scale with EVERY factor labeled (P_eff — cite EMC04's
direct-run derivation; R_p, R_n; n(r) from ρ/⟨A⟩m_u; d(r) = n^{-1/3}; the geometric prefactor's
origin stated or marked ASSUMED). Then v_p = √((K + 4G/3)/ρ) using P3's G. Pre-registered gates
(same as the old spec — the re-adjudication re-tests the same claim): v_p RMS < 5% = PASS;
5–30% = FAIL-as-posed with the residual localised and attributed; > 30% anywhere = KILL of the
route. **The old run's 11.5% must be reproduced or the discrepancy explained (root-sorted) —
that reproduction check IS the UNCONFIRMED-FAIL adjudication.**

**P3 — The shear route via the connection law (NEW — the June run had no native G at all).**
From NP30 §10: a nucleon-nucleon contact locks only in the six D₃/lcm(2,3) orientations; in
condensed matter the analogous statement prices how many of a site's contacts are ORIENTED
(shear-bearing) vs free. Derive f_shear = G/K from connection-count geometry per lattice class
(the crystal grammar of the mineral layer — coordination number vs the six-fold lock), with
zero material inputs. Pre-commits: (a) f_shear ∈ (0,1) derived per layer BEFORE comparing to
PREM's K/G ratios; (b) outer core: T above the unlock threshold → zero locked orientations →
G = 0 EMERGES (the criterion stated as a lock-distance/temperature condition, not asserted);
(c) v_s RMS gate: < 10% = the new route lands; 10–30% = partial (localise); > 30% = the shear
claim stays dead (old 28% confirmed at mechanism level).

**P4 — STRETCH (only after P1–P3 verdicts filed).** (i) 410/670 km: do the transition pressures
sit at derivable occlusion/packing thresholds (link NP30's interpenetration bridge)? Look-elsewhere
flagged. (ii) Inner-core anisotropy: compute the axial convergence component's magnitude
honestly (the old spec's own estimate: ~1e-13 of local pressure — probably nothing; print it and
say so). (iii) Centre-of-Earth state: the SDT≠GR "crushed vs weightless" claim restated with the
earned profile — flagged as the falsifiable interior fork, magnitude and observable named or
parked.

**P5 — STRETCH.** PKP/PKIKP/PcP travel times vs ISC (< 2 s over 1000+ s paths) — only if P2+P3
both land; otherwise meaningless.

## §⑧ Falsifiers

| # | trigger | consequence |
|---|---|---|
| F1 | P0 finds load-bearing GM in a "native" chain | affected leg → TRANSPLANT label; if it's the g-leg, the prior 1.82% credit is VOID too |
| F2 | P1 fails 3% | interior integral broken — STOP (this leg cannot honestly fail if inputs are right) |
| F3 | P2 > 30% anywhere | occlusion-K route KILL-CONFIRMED (register ruling filed with mechanism: bare occlusion cannot price matter stiffness) |
| F4 | P3 predicts G > 0 in outer core | unlock criterion wrong — shear route KILLED |
| F5 | P3 f_shear needs a fitted fraction | route is CALIBRATED at best — label or drop; no silent knob |
| F6 | PREM provenance unverifiable | run VOID until F7 cached |

## §⑨.E Four-root sort
root-1 (occlusion genuinely cannot price stiffness — the physical negative, respectable) ·
root-2 (P_eff/R_p inputs; PREM data; NP30 §10 dependency) · root-3 (spec: prefactor/geometry
under-specified — mark ASSUMED, don't guess silently) · root-4 (gate contraband — none expected;
PREM is measured-world, not a rival axiom).

## §⑤ Outputs
Fresh `RUN_LOG.md` · P0 audit report `GOM09_P0_AUDIT_<date>.md` · patched tools + teed
`gom09_*_rerun_<date>.txt` · `GOM09_VERDICT_DIRECT_<date>.md` (dual verdict + **register ruling
line** + K/G provenance ledger) · F7 fetch + `Datasets/MANIFEST.md` row when pulled · register
QUEUED cell update (propose in verdict; Harvey ratifies).

## §6 Dependencies
Upstream: EMC04 (P_eff, direct-class) · NP30 §10 (connection law — the new shear engine) · NP30
§11 (compression floor — the density side of the same packing) · bridge. Data: **F7 PREM**
(MUST_FETCH — currently WANTED; fetch before P1). Downstream: E97 campaign row; the interior
fork (P4-iii); GOM19 P5 (compression-floor cross-checks).

---

## ⑩ Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM09 (2026-07-24 spec; register re-adjudication run)
- Prompt completion target: [A|B|C]
- Register outcome space: KILL-CONFIRMED / OVERTURNED→OPEN / OVERTURNED→PASS — LEASH both ways
- Physics class: P1 CONVERGENCE · P2/P3 NATIVE claims · P4 stretch
- CALIBRATED budget: 0 (F5 enforces)
- Gates: P0 audit filed · P1 g<3% · P2 v_p <5% PASS / >30% KILL + reproduce-or-explain 11.5% ·
  P3 f_shear derived, G=0 emerges, v_s <10% / >30% dead
- Old-run anchors declared: 11.5% / 28.0% / 1.82% (reproduce-or-explain, never steer)
- Forbidden: material moduli in-chain; silent shear fraction; quoting g-leg for the native leg;
  agents.
```

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P0 GM hits in-chain | patch to kinematic form, ADJ-log, re-run | leg relabeled TRANSPLANT | leaving it |
| P2 lands 5–30% | localise residual by depth/layer; root-sort | FAIL-as-posed recorded | tolerance widening |
| P3 f_shear underdetermined for a layer | state the lattice-class assumption as ASSUMED, compute both candidates | partial verdict | picking the better-fitting one silently |
| F7 fetch blocked | BLOCKED-route row; embedded-PREM path with full citation + checksum | — | uncited arrays |

---

*GOM09 · upgraded 2026-07-24 · the g-profile was never the question; the question is whether
occlusion can price stiffness — and NP30's six locks are the first native tool for the shear
half. File the register ruling either way.*
