# NP21 — Verdict: The Binding Curve as a Resistance Landscape (iron at the floor)

> Author: J. C. Harvey, Melbourne. Tool: `np21_landscape.py`. Data: AME2020 (OBSERVED-TARGET),
> engine `sdt::nuclear` (grammar + stable-set domain), `sdt::packing` (coordination geometry).

## Dual verdict header

- **Prompt completion:** **B** — all four phases (P1–P4) implemented, run, and gated honestly; the
  *strong* outcome (a geometric iron floor) was not reached, so this is not an A.
- **Physics class:** **KILLED** (the geometric-iron-floor claim) **/ CALIBRATED — Class C** (the
  landscape-as-shape, reproducible only with fitted coefficients).
- **Net:** matches **FLM12 §D2 = OPEN**. The reframe is native; the *number* (iron at the floor) is
  **un-paid**. Honest FAIL of the hard bar beats a fake PASS.

## What passed, what failed (against the pre-committed thresholds)

| Phase | Pre-committed threshold | Result | Call |
|-------|-------------------------|--------|------|
| P1 | every exponent tagged; ≤1 free scale coeff; grammar+packing+domain from engine; ledger frozen | done; A-exponents `{0,−1/3,−4/3,−2}` all tagged GEOMETRIC | **PASS-GATE** |
| P2 | rise-then-fall; concave-down; Spearman > 0.85 | Run F (3 fitted coeffs): Spearman **+0.907**, RMS 0.203 MeV/n. Run G (geometric): Spearman **−0.574** (wrong sign, monotone) | **PARTIAL** (shape only with a fit → caps at C) |
| **P3** | floor within ±2 in A of Fe/Ni **with 0 fitted exponents/ratios**, robust | Run G floor **U-238** (|A−56|=182); geometric ratio **32× off**; Run F floor **Ca-48** (|A−56|=8, still >±2); robustness **0/45** | **FAIL of the geometric bar → KILL** |
| P4 | Fe-56 & Ni-62 both within ±2 of floor; ordering stated | landscape places **Ni-62 deeper** (1.589 < 1.672), matching measured B/A and σ | **consistent** (2-point, not the floor) |

## Falsification table (§⑧ — filled)

| Test | Predicted PASS | Actual | Outcome |
|------|----------------|--------|---------|
| **T1 (floor location — crux)** | `argmin R̃/A` within ±2 of Fe/Ni, all-geometric | U-238, gap 182 in A | **KILL** the geometric-floor claim |
| **T2 (no fitted exponent)** | floor stays on iron under perturbation; 0 fitted | 0/45 on iron; needs ~32× ratio change | floor reachable only via fit → **CALIBRATED**, not derived |
| **T3 (shape)** | rise-then-fall, Spearman > 0.85 | +0.907 **but only with 3 fitted coeffs**; geometric run −0.574 | shape **CALIBRATED**, not native |
| **T4 (Fe/Ni ordering)** | both within ±2; ordering stated vs B/A & σ | Ni-62 deeper; matches B/A and σ; no re-tune | **PASS** (local, consistent w/ NP13) |
| **T5 (no SEMF smuggle)** | all exponents geometric / one doc. fit; SEMF only as OBSERVED | A-exponents geometric; SEMF coeffs used only as OBSERVED comparison; no G/M/GM/ψ/quarks | **PASS** (chain clean) |

## Honest reading

The single geometric statement *"whole curve = one resistance landscape, most-bound = least-resistance"*
is a faithful reframe, and the functional's **A-exponents are genuinely geometric** (compact-packing radius
and area laws, per-pair counting — not SEMF-fitted). The functional form even reproduces the famous
rise-then-fall shape well (Spearman 0.907). **But the location of the floor is not geometry — it is a
coefficient ratio `a_C/a_S`, and SDT supplies no derivation of it.** The natural whitelist guess (`α`) puts
the floor at uranium; the ratio that would put it near iron is ~32× larger and coincides with the SEMF's
fitted value — i.e. reaching iron *requires a fit*. Even the full 3-coefficient fit lands the floor at
Ca-48, still outside the ±2 window. So the decisive claim — **iron derived at the floor** — is not paid.

This is precisely the outcome the prompt and FLM12 §D2 pre-flagged as the likely honest ceiling. Per the
watch-point, I have **not** relabelled a fitted ratio as geometric, and I have **not** widened the ±2 window.

## Stack update

- `INVESTIGATION_STACK.md`: NP21 → **KILLED (geometric-floor claim) / DEGENERATE-CALIBRATED (landscape shape)**.
- FLM12 §D2 stays **OPEN**: NP21 does not close it; it *bounds* it — the missing piece is now named exactly
  (a geometric derivation of the spread-to-surface weight ratio `a_C/a_S ≈ 0.04`).
- Downstream **SAR05** cannot yet consume a *derived* floor; it inherits an un-paid one.

---

## STRESS-TEST SELF-AUDIT (mandatory)

1. **Independent, or identity/circular?** The *measured* B/A ≡ per-nucleon resistance relief is an
   **IDENTITY** and was explicitly excluded from the test. The SDT-side functional `R̃(Z,A)` is built from
   the engine's `alpha_grammar` inventory + packing exponents and is **independent** of the measured B/A in
   Run G. No IDENTITY-PASS: the measured curve is used only as an OBSERVED-TARGET anchor (for the Spearman
   comparison and the Run-F fit), never *as* `R̃`. The one consistent sub-result (P4 Ni-62 deeper) is a
   genuine independent pointwise output, not a back-fit.

2. **Fished / fitted exponent?** No exponent was fished. The A-exponents `{0, −1/3, −4/3, −2}` were frozen
   as GEOMETRIC in `RUN_LOG.md` **before** any run and never changed. The failure is *not* a hidden exponent
   fit — it is the opposite: with geometric exponents AND a geometric coefficient guess the floor lands at
   U-238. Reaching iron needs a fitted **coefficient ratio** (`a_C/a_S`), which is reported openly as
   CALIBRATED. A fitted ratio is **not** a derived one and is labelled so; the SEMF's fitted coefficients
   were kept out of the chain (OBSERVED comparison only).

3. **Dimensions.** `R̃/A` is a per-nucleon resistance (∝ energy/nucleon once the one scale weight `a_V` maps
   units to MeV). Each term: bulk `[a_V]`; surface `[a_S]·A^(−1/3)`; spread `[a_C]·(pure count)·A^(−4/3)`;
   asymmetry `[a_A]·(pure count)²·A^(−2)`. Ratios `a_C/a_S`, `a_A/a_S` are dimensionless and are what set the
   floor — consistent, and correctly identified as the un-derived object. No G, M, GM, ψ, or borrowed
   magnetons entered.

4. **Honest class + what is owed.** Prompt completion **B**; physics class **KILLED (geometric floor) /
   CALIBRATED Class C (landscape shape)**. **Owed:** a *geometric derivation of the spread-to-surface weight
   ratio* `a_C/a_S ≈ 0.04` (equivalently, the redirection energy per proton-pair relative to the surface
   frustration per piece). Until that ratio falls out of packing/occlusion geometry, "iron at the floor" is
   asserted and fitted, not derived. FLM12 §D2 remains OPEN; NP21 names the exact gap and refuses to paper
   over it with a fit.
