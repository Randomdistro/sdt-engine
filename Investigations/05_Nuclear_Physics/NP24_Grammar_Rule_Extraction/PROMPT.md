# NP24 — THE RULES: Grammar Residual Law · Stability Band · The Ionisation Ladder Scaled to H
## A rule-extraction investigation across the (n_d, n_t) lattice — nuclear and atomic, one coordinate system

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC → RUN 2026-07-18.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §A–§K · `OPERATING_PROTOCOL.md`.
> **Engine:** measured data only. **Propose-only** on canon. **No G/M/a₀/ΛCDM/ψ. No "charge radius" → boundary radius.**
> **Movement rule (Harvey, standing):** *all "energy" is the quantification of movement.* Every MeV and eV below is a movement count at a boundary; BE/A is a **movement density per nucleon**, an ionisation energy is the **movement cost to unseat one electron**. If a term cannot be said in movement, it is carrying an inherited abstraction.

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — **The RULE the packing residual obeys.** The shadow-overlap model fails structurally (R²(BE/A) = −12.2 over 3213 isotopes; BE/A ridge found in 1/116 rows), but it fails *systematically*: within every element the error climbs monotonically with n_t. **A systematic residual is a law with its sign flipped.** We do not know its functional form, whether it is the same law that sets the stability band, or whether it has an atomic counterpart in the ionisation ladder.
2. **Why does it matter?** — If one function of (n_d, n_t) simultaneously (a) corrects the packing residual, (b) predicts which (n_d,n_t) are stable, and (c) appears in the ionisation ladder scaled to H, then the grammar is a **real coordinate system for matter**, not a bookkeeping scheme. If the three refuse to share a law, the grammar is nuclear-only.
3. **How will we find out?** — Six gated phases (§④) over three measured datasets, with **candidate rule forms declared BEFORE fitting** (§③) and a hard anti-FISHED discipline: any rule must be *stated first, tested second, and rejected out loud*.
4. **What would prove us wrong?** — §⑧. Chief kills: the residual has no closed form better than noise; the stability band is not a function of (u,v); the ionisation ladder scaled to H shows no grammar signal (then the cross-scale claim dies and NP24 is nuclear-only).
5. **How will we know we're done?** — Dual verdict + a **RULES LEDGER**: every rule stated with its domain, its residual, its falsifier, and its class (DERIVED / EMPIRICAL-LAW / FITTED / DEGENERATE-with-known / KILLED).

---

## ① The coordinate system (fixed, not chosen)

The ATOMICUS grammar, domain **Z ≥ 3 (after helium — He is the core, not a construction on it)**:

```
n_t = A − 2Z          n_d = 3Z − A − 2          [1 alpha core + n_d deuterons + n_t tritons]
u   = n_d − n_t       v   = n_d + n_t           [the lab's lattice axes]
CONSERVATION (mandatory on every row): A = 4 + 2n_d + 3n_t ,  Z = 2 + n_d + n_t
```
**Golden line** u = 0 (n_d = n_t) — a grammar identity, needs no model.
**Monoisotopic spine** u_mono(v) = u of the sole stable isotope in row v (else mean of stables).
**Energy spine** u_E(v) = u of max BE/A in row v. **deltaMonoEnergy = u_E − u_mono** (measured +5.50 mean).

---

## ② Data (measured only; every number traceable)

| Set | Source | Content | Status |
|---|---|---|---|
| AME2020 | IAEA `mass_1.mas20.txt` | 3558 mass excesses → BE, S_n, S_p, Q_EC | pulled, validated |
| NUBASE2020 | IAEA `nubase_4.mas20.txt` | 253 stable, half-lives, decay modes | pulled, validated |
| CRC ionisation | Wikipedia data page (CRC column, eV) | 104 elements, 764 stages | pulled, 8/8 spot-checks exact |

**Derived, not fitted:** BE(Z,A) = Z·ME(¹H) + N·ME(n) − ME(Z,A). **S_n − S_p ≡ Q_EC(Z,A−1) + 782.347 keV** (proved exact, 3257/3257 — an identity, not a result).

---

## ③ CANDIDATE RULES — DECLARED BEFORE FITTING (anti-FISHED, §A)

> Any form not on this list may be tested **only** as an explicitly-labelled post-hoc exploration, and can never be reported as a prediction. Every rejection is reported.

**R-block (the residual law).** Residual ε = (BE_pred − BE_meas)/BE_meas from the κ-shadow model.
- **R1 linear-in-u:** ε = a + b·u
- **R2 asymmetry:** ε = a + b·(n_t/(n_d+n_t)) — the triton fraction f_t (NP02B's overload variable)
- **R3 classic asymmetry form:** ε = a + b·(N−Z)²/A ≡ b·n_t²/A (the standard term, as a *degeneracy check*)
- **R4 pairing:** ε = a + b·δ(parity of n_d, n_t) — even/odd structure
- **R5 surface/volume:** ε = a + b·A^(−1/3) — the light-nucleus over-binding
- **R6 combination:** the minimal additive set from R1–R5 that survives cross-validation

**S-block (the stability band).**
- **S1:** stability is a band in u alone: u_lo(v) ≤ u ≤ u_hi(v)
- **S2:** stability is a band in the triton fraction f_t
- **S3:** the band edges are set by the two decay channels (EC above, β⁻ below) — i.e. the band **is** the Q_EC = 0 and Q_β = 0 contours in (u,v)

**I-block (ionisation ladder scaled to H).** With z ≡ IE/13.59844 eV (H = 1 by construction) and **k ≡ 1/√z**:
- **I1 hydrogenic:** z(Z, stage s) = (Z − s)² for the last electron → k = 1/(Z−s). Test as the **null hypothesis**.
- **I2 core-breach:** the large jumps in the ladder mark shell closures; their positions are a function of Z only (atomic), NOT of (n_d,n_t) → **cross-scale NULL**
- **I3 grammar coupling:** some ladder feature (jump position, k at a fixed stage, ρ = IE_next/IE) correlates with the nuclear (n_d,n_t) of the element's **stable** isotope → **cross-scale SIGNAL**

**Pre-committed:** I2 is the null. **I3 must beat I2 on out-of-sample elements or the cross-scale claim is dead.**

---

## ④ Phases (gated; each feeds the next)

- **P0 — Rebuild & verify.** Recompute grammar for all AME nuclides; enforce the conservation identity on every row; report any violation as a computation error, never a finding.
- **P1 — The residual map.** Compute ε for all 3213 valid-grammar isotopes. Map ε against u, v, n_t, f_t, A, parity, and shell distance. **Report the full map, in sequence, no sorting by residual.**
- **P2 — Rule extraction (R-block).** Fit R1–R5 *as declared*; cross-validate (fit on even-Z, test on odd-Z, and vice versa) to kill overfitting. Report every form's out-of-sample R², including the failures.
- **P3 — The stability band (S-block).** For every row v, extract the measured stable u-range; test S1–S3. Compare against Q_EC=0 / Q_β=0 contours from AME2020.
- **P4 — The ionisation ladder (I-block).** Scale all 764 stages to H; compute z, k; locate core-breach jumps; test I1 (null), I2 (null), I3 (signal) with out-of-sample validation.
- **P5 — The rules ledger.** Every surviving rule stated with domain, residual, falsifier, class. Every rejected candidate listed with why.

**Gate:** no rule may be reported without (a) being declared in §③ or explicitly labelled post-hoc, (b) an out-of-sample test, (c) a stated falsifier.

---

## ⑧ Falsifiers (numeric, pre-committed)

| # | Test | Pass condition | If FAIL |
|---|---|---|---|
| F1 | residual has a rule | some declared form reaches out-of-sample R² ≥ 0.5 on ε | residual is noise → the packing model is not merely incomplete but wrong in kind |
| F2 | rule beats the trivial | the winning form beats "ε = constant" by ≥ 0.2 R² | no rule; report honestly |
| F3 | stability band is a (u,v) function | ≥90% of stable nuclei inside the extracted band | stability is not a grammar property |
| F4 | band = decay contours | band edges match Q_EC=0 / Q_β=0 within 1 u-unit | S3 dead; band is empirical only |
| F5 | ionisation cross-scale | I3 beats I2 out-of-sample | **cross-scale claim DEAD** — NP24 is nuclear-only (this is the expected honest outcome) |
| F6 | no degeneracy laundering | if the winning residual form ≡ the standard asymmetry term, say so | else IDENTITY-PASS |

---

## ⑨.E Four-root sort (on every failure, before the next phase)
root-1 claim false · root-2 dependency (data/parse) · root-3 prompt under-specified · root-4 contraband (a rival's term imported and renamed). **A residual form that reproduces the semi-empirical mass formula is root-4 unless labelled DEGENERATE.**

## ⑩ Forbidden
Post-hoc tolerance widening · reporting an undeclared form as a prediction · sorting by residual and showing the tail · total-BE R² as the headline when BE/A R² is the honest metric (**the error already made once in this line**) · any "energy" left untranslated into movement.

---

*NP24 · the residual is systematic; a systematic residual is a law with its sign flipped. Find it, name it, or kill it out loud.*
