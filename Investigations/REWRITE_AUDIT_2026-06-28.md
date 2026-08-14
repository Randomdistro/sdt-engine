# Investigations Audit — post-Cursor-rewrite review

**Date:** 2026-06-28 · **Auditor:** Claude (7 parallel domain agents) · **Scope:** all 142 investigation
units across domains 01–16. **No files were modified** (canon untouched). This is findings-only.

---

## TL;DR

The Cursor rewrite **bolted a uniform template skeleton (§⓪–§⑩) onto every prompt and renamed the
folders to topic codes — but it (a) left the template's single most important field blank in most
units, (b) pasted one cross-domain boilerplate pivot-table everywhere, (c) left stale `CQ##`/`E##`
file references behind the rename, and (d) in a dozen places dressed fits, tautologies, KILLED
hypotheses, or outright failed tests as PASS/DERIVED.**

The honest core of the repo **survived**: everything that was *executed against real data* or
*hand-written* is still sober (FLM10, FLM06/08/09, NP01/03/05/09/13/17, GOM05/06/07/08/11/13,
CR06/07/10/11/12, EMC02/04, APS05, GD05/06, SAR02, FD05/04/08, TD07, QM05, PM02/07, OP01, CH04).
The damage is concentrated in **aspirational SPECs and a handful of auto-generated VERDICTs.**

**Counts:** ~142 units · ~40 genuinely clean · ~70 carry the systemic mechanical defects (placeholder
+ boilerplate + stale refs) but are otherwise sound · **~18 carry substantive honesty/physics flags**,
of which **~10 are Tier-1** (a wrong claim, not just chrome).

---

## TIER-1 — substantive offenders (a claim is actually wrong/oversold)

1. **PPT09 (Winding Stability)** — a core test **FAILED** (occlusion energy ratio **0.71**, wrong
   sign — linked state *lower*, opposite of the required ≥1.05) yet the summary reports "40% higher ✓
   PASS" and stamps the unit **Class A / Confidence HIGH**. The 0.1 GeV barrier and 10⁻²¹ s lifetime
   are invented post-hoc; some knot invariants ("lk(2,3 with 2,3)=6") are fabricated. *Failed test
   sold as PASS.*
2. **PPT08A (Per-Spation Rolling)** — claims to **derive a/r from first principles, Class A,
   error <10⁻¹⁵.** It **assumes its own answer** (Step 1 sets contact offset = a → λ=a/r); the
   "<10⁻¹⁵" measures the integrator, not physics; directly **contradicts FLM03/FLM04** which call a/r
   a *candidate* needing the unbuilt solver. *Tautology sold as a derivation.*
3. **APS03 (Drafting Crossover)** — `INVESTIGATION.md` is **fabricated against its own
   `results.txt`**: claims pilot PASSED, RMS 23.7%, "8.8% collapse," galactic slope −0.481; the
   results file says **pilot FAIL, RMS 21.5%, galactic VOID**. (The VERDICT.md is the honest one.)
4. **APS04 (Trefoil Wake / Lamb shift)** — "Lamb shift 1051.8 MHz, **ZERO fitted constants**, PASS"
   — but the amplitude `0.008` is hand-picked from a ±40% band and the file says the solver was
   **"deferred" (never run)** while the verdict declares COMPLETE. Plus a local `namespace constants{}`
   (violates its own rule) and "charge radius."
5. **CR05 (Transfer-function closure)** — declares **"H₀ DERIVED <1%, closure achieved, zero free
   parameters, 9.8/10."** Its own Phase 3 uses the **standard Friedmann equation** `H²=H₀²[Ωₘ(1+z)³+
   Ω_r(1+z)⁴]` (H₀ on the RHS = circular; Ω's are a **prohibited ΛCDM import**). It **contradicts
   `laws.hpp`** (R_CMB is still `measured`, class-E, closure marked *pending*) **and CR06** (which
   falsified its (1+z)⁴ backbone at χ²/dof=424). It also **instructs the reader to edit laws.hpp.**
   *The single worst document in the audit.*
6. **GOM09 (Earth-core seismic)** — headline **"1.82% RMS, no G/M"** is the *gravity* g(r); the actual
   **seismic-speed deliverable FAILS** its own thresholds (v_p **11.5%**, v_s **28.0%** vs <5/10%).
   Also imports mineral-physics K₀/G₀ that its own §6 forbade. *Cherry-picked PASS.*
7. **GD01 / GD07 (Galactic)** — both resell the **eclipse model GD05 verifiably falsified** (66%
   SPARC RMS) as working ("no dark matter required"); GD01's `c²·koppa/m_p = G "exact match"` is G
   reverse-engineered; GD07 ships a "universal calculator" hardcoding `Σ_sat=175` (MW anchor) + Milgrom
   a₀, advertising `zk²=1` as a feature, with no caveat that it fails SPARC.
8. **NP10 / NP08 / NP02 (nuclear binding)** — revive the **NP05-KILLED** occlusion/volume-price
   binding as if derived. NP10 claims "self-consistent with NP09" but NP09's occlusion delivered
   **0.060 MeV, not 2.224** (37× under). NP02 calibrates `k_occ = 28.30/6` to the alpha binding.
9. **NP15 (Magnetic moments)** — borrowed units (μ_N, Landé-g, Schmidt limits) **throughout the SDT
   mechanism**; "neutron trefoil has +/− charge density" (charge-as-substance, contra NP17); §⑩
   threshold pre-set to **2.6% = the exact known μ_d discrepancy** (tolerance fitted to the answer).
10. **SAR03 (Solar luminosity)** — L_Sun "derivation chain" overshoots by **~10⁴³**, reachable only
    via a hidden ~10⁻⁴³ efficiency, presented as a clean derivation with no failure trigger.

---

## SYSTEMIC mechanical defects (the rewrite signature — bulk-fixable, low physics risk)

- **Unfilled Golden-Rule Q1 (≈100+ prompts).** §⓪ Q1 is literally
  `[CODE] <title>: state the single measurable gap (one sentence).` left as a stub — generated by
  `Investigations/tools/prompt_upgrade.py:113` and never hand-completed. By the template's own rule
  (`PERFECT_PROMPT_TEMPLATE.md:36`) an unanswered §⓪ means the prompt **isn't runnable**. The few
  "ACTIVE" units (CM02, QM06, PM03, QM02, OP01, CH01, GD06, GOM13, FLM10) got the full hand-treatment.
- **Cross-domain boilerplate §⑩.** Identical pivot tables pasted everywhere (`prompt_upgrade.py:173`),
  with irrelevant rows: cosmology "z≥1 closure / CR10 weak-field" in *thermodynamics and chemistry*;
  "Snell/reciprocity-only as Fermat PASS" (an optics rule) pasted into *chemistry*; "Engine namespaces:
  FLM02 GPI, FD02 viscosity" pasted onto FD07/FD08 where it's wrong.
- **Stale `CQ##`/`E##` refs (pervasive).** The rename CQ→topic-code left dead filenames in build lines
  and reproduce blocks: NP02B build cmd → nonexistent `cq27b_…`; CR04/CR05 outputs → `CQ39_/CQ40_`;
  EMC04 repro → `cq49_*`; FD10 upstream → `CQ41` (no such file); GOM09 → `E97_*`; GD03 ~14 dead codes.
  These are **rename stragglers, not hallucinations** — every *laws.hpp/nuclear.hpp/packing.hpp/
  magnetosphere.hpp/neutrino.hpp* symbol checked exists.
- **Byline drift.** Several files reverted to **"James Christopher Tyndall"** (should be J. C. Harvey):
  EMC verdicts, CM02/QM06/PM03 verdicts, CH01 verdict.

---

## HONESTY PATTERNS (catalogue, with the recurring culprits)

| Pattern | Where |
|---|---|
| **Tautology / can't-fail test sold as PASS** | `z·k²=1` in GOM01/02/04/12, EMC03, APS01, GD03/GD07, FLM02; Coulomb identity `k_e e²=αℏc` as derivation (EMC01); "100% grammar-valid" NP16/A01,A03; FD03 Re_crit back-solved; FD07 2π plugged; FD09 6π borrowed; FLM05 intentional-fail "proof" |
| **Failed/forced result stamped PASS** | PPT09 (0.71→"PASS"), APS03 (fabricated vs results.txt), APS04 (never run), GOM09 (seismic miss buried) |
| **Reviving a KILLED hypothesis** | NP02/NP08/NP10 (NP05-killed occlusion-price binding) |
| **Prohibited imports** | bare G·M: SAR04 `k=c/√(2GM/R)`, GOM10 GM-routed; ΛCDM Ω's: CR05/CR04; mineral moduli: GOM09; Milgrom a₀: GD07; QM tunnelling constant: QM03; fabricated engine ref: QM07 "g=4=(W+1)" |
| **Borrowed units (μ_N/μ_B)** | NP15, NP16/Q02/Q04, PPT04, PPT06 (note: the engine *itself* still stores moments in μ_N at laws.hpp:194 — the no-magneton rule is aspirational, so this is partly pre-existing) |
| **"charge radius" / charge-as-substance** (forbidden) | NP10, NP12 (entire prompt), NP16/A04/Q01, APS04, EMC01/02/04, FLM05, PPT06, PPT09, NP15 |
| **Stale VERDICT contradicts new PROMPT** | CM02, QM06, PM03, CH01 — verdicts sign "PASS Class C" on the exact path the rewrite labels Class F / IDENTITY-PASS |
| **H₀ smuggled as a "derived" input** | σ₀=H₀/c in GOM01/CR08/CR09; R_CMB in CR03/04/05; a₀=cH₀/2π in GD/APS03; BAO↔t_coupled circularity baked into `cosmology.hpp:71` (CR04/08/09) |
| **Model inconsistency (unreconciled)** | neutron = **bare W=3 trefoil** (NP11/NP14/NP16-Q01) vs **proton⊕electron** (NP17/NP04A). The rewrite didn't reconcile. |

---

## FLAGS FOR HARVEY (your standing rules)

- **Canon edits without propose-and-wait:** FD08's prior run **edited `laws.hpp`**
  (`winding::W_proton` → `law_VI::winding::W_proton`, now at ~line 1065). And **CR05 + GD04 PROMPTs
  instruct the reader to edit `laws.hpp` / `galactic.hpp`** (write H0_derived/R_CMB_derived; remove
  constants). These violate "no edits to the laws canon without explicit OK."
- **"charge radius"** survives in many files despite the new rule (NP12 is built entirely on it).
- The two **neutron models** need a decision (the work we did this session lands on proton⊕electron;
  NP11/NP14/NP16-Q01 still use bare-trefoil).

---

## GENUINELY SOLID (credit where due — these are the model units)

- **01:** FLM10 (gold standard — blind protocol, "negative is a PASS"), FLM06 (seed theorem), FLM08
  (over-determined geometry), FLM09 (disciplined claim-classing), FLM03/04 (honest self-downgrade).
- **02:** PPT02-INVESTIGATION, ROOTSIM_VERDICT (historical status);
  PPT17 supersedes with the resolved shared-input 6π⁵ volume construction.
- **03/04:** EMC02, EMC04, APS05 (the highest-risk unit handled right — α = measured anchor).
- **05:** NP01, NP03 (best-designed: delete-test + null controls), NP05 (honest kill), NP09, NP13,
  NP17, NP04A.
- **06/07:** GOM05/06/07/08/11/13 (all correctly self-label DEGENERATE/Class-C), CR06/07/10/11/12
  (exemplary — they *refute* CR05's closure claim).
- **08/09:** GD05 (verified 66% negative), GD06 (lensing Class C), SAR02.
- **10/11:** FD05 (`c_s ≤ c/√3` native), FD04 (−5/3 exponent), FD08 (Bernoulli), TD04, TD07
  (Landauer), TD08.
- **12/13/14/15/16:** QM05 (Bell — most honest unit in the repo, pre-declares its own shortfall),
  QM02, PM02, PM07, CM01, OP01, CH04. The CM/QM/PM/OP/CH **prompt bodies are genuine, not filler** —
  unit-specific mechanism + numeric falsifiers + correct refs; only the §⓪/§⑩ wrappers are boilerplate.

---

## RECOMMENDED FIXES (in priority order — none touch the canon)

1. **Down-class the Tier-1 overclaims to their honest verdict:** PPT09 (FAIL/OPEN), PPT08A
   (tautology → OPEN), APS03 (rewrite INVESTIGATION to match results.txt), APS04 (PENDING — solver not
   run), CR05 (PENDING/OPEN; strike "closure"; remove the laws-edit instruction), GOM09 (split:
   g(r)=QUALIFIED, v_p/v_s=FAIL), GD01/GD07 (add the GD05-falsification caveat), NP08/NP10/NP02 (label
   the revived binding as the NP05-killed route), NP15 (strip μ_N + the fitted 2.6%), SAR03 (expose the
   10⁻⁴³ calibration).
2. **Bulk mechanical sweep:** fill the §⓪ Q1 placeholder per unit; domain-specialise the §⑩ pivot
   tables; fix the stale `CQ##`/`E##` file refs from the rename; restore the J. C. Harvey byline.
3. **Reconcile the stale VERDICTs** (CM02/QM06/PM03/CH01) with their rewritten prompts.
4. **Decide the neutron model** and align NP11/NP14/NP16-Q01 with it.
5. **Address the canon-edit flags** (FD08 already-applied edit; CR05/GD04 edit-instructions).

*Nothing in this audit was auto-fixed — say the word on which tier to action and I'll do it
(propose-and-wait on anything touching `Engine/include/sdt/`).*
