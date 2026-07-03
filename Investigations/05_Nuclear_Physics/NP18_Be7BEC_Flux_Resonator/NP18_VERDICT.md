# NP18 — VERDICT: Be7BEC Flux Resonator (the rate-scaling fork)

> **Author of run:** executor agent, per J. C. Harvey NP18 SPEC. **Run date:** 2026-07-01.
> **Tool:** `np18_rate_fork.py` → `np18_results.txt`. **Engine:** `laws.hpp`, `nuclear.hpp`, `neutrino.hpp`.

---

## Dual verdict (header)

| Axis | Grade | One-line reason |
|------|-------|-----------------|
| **Prompt completion** | **A** | All four phases implemented, run, gated, and logged; every §6 output produced; no phase skipped, no gate widened. |
| **Physics class** | **NATIVE (selection rule) · OPEN/DEFER (the fork's payout)** | The grammar selection rule is native and exact; the headline whole-condensate N² payout is **geometrically DEFERRED** (λ_ν ≪ L, T3) and the absolute read-out is **PENDING** NP19/NP20. |

**Plain statement:** NP18 is a *complete tool with an honest non-payout*. The zero-parameter
selection rule works. The N-vs-N² fork is built and sharp **as a conditional prediction**, but it
is **not** paid out to an absolute divergence population N\*, because (a) the 0.862 MeV neutrino
wavelength cannot span a tabletop BEC, and (b) the per-capture magnetisation step needs upstream
siblings that have not landed. This is a DEFER/OPEN, not a PASS and not a KILL.

---

## Phase-by-phase result

| Phase | Committed threshold | Result | Decision |
|-------|--------------------|--------|----------|
| **P0** grammar | (3,−1)→(0,1) exact; vector (−3,+2); 478 keV=GAMMA | all integer-exact; gamma labelled correctly | **PASS-GATE · NATIVE** |
| **P1** R_inc | σ within 2× (fail >10×) of resonance/weak sanity | σ_avg=1.63e−47 m²; ratio to weak ref = 0.16 (in band); G_F-free | **PASS-GATE** (dE ASSUMED, flagged) |
| **P2** N-vs-N² | R_coh/R_inc=N to <1% at ρ≥1; exact limits at N=1 & ρ→0 | all three limits exact | **PASS-GATE** |
| **P3** N\* + span | finite N\* with B_sig≥10×fT **AND** ρ_coh≥1 together | ρ_coh≤6.7e−7 (span fails ~7 orders); B_step absolute blocked | **DEFER (T3) + PENDING** |
| **P4** stripped fork | deep-K vs shallow-2s B_step differ ≥3× | seat proxy 11.75× (linear)/1621× (vol) | **PASS (proxy) · absolute OWED** |

---

## §8 Falsification table (filled)

| Test | Predicted | Actual result | Decision |
|------|-----------|---------------|----------|
| **T1** rate coherence-driven not G_F-driven | R ∝ N² as ρ→1; slope > any G_F curve | Not decided by this run — needs the *experiment*; the *slope* falsifier is reachable (see proposal). Tool does NOT claim T1 won. | **UNDECIDED — shipped as the reachable falsifier** |
| **T2** captures write a readable step | B_step·(R_coh−R_inc)·τ ≥ 10×fT | absolute B_step BLOCKED (NP19/NP20 SPEC); illustrative placeholder does not clear at ρ<1 | **PENDING → OPEN read-out** |
| **T3** coherence spans the BEC | ρ_coh=λ_ν/L ≥ 1 at N\* | ρ_coh ≤ 6.7×10⁻⁷ for **all** tabletop N,n — fails by ~7 orders | **FAIL → DEFER to CEνNS scale** (honest boundary, as the SPEC itself flagged) |
| **T4** selection rule selects EC substrates | Be-7 at (3,−1) underflow, one EC vector to Li-7 | exact; (−3,+2) lands on Li-7 | **PASS (rule holds for Be-7)** |
| **T5** stripped-Be-7 forks manufacture vs reshuffle | deep-K vs 2s differ ≥3× | seat proxy 11.75×/1621× ≥ 3× | **PASS (proxy); absolute OWED** |

**Honest boundary (restated loud):** CEνNS (Freedman 1974; COHERENT 2017) proves N² coherence only
where the momentum-transfer wavelength already spans the target — **nucleons within one nucleus**.
Extending N² across a **whole condensate** requires λ_ν ⊇ BEC. NP18 shows numerically that this
condition **fails at every achievable tabletop BEC** (λ_ν ∼ pm vs L ∼ µm). The whole-condensate N²
claim is therefore **UNESTABLISHED and DEFERRED** — exactly as the SPEC's WATCH-POINT warned. The
tool does **not** fabricate a condensate-scale coherence enhancement.

---

## What is owed (the honest ledger of debts)

1. **Absolute N\*** — blocked on NP19/NP20 (the 2s flux-per-atom B_step absolute). PENDING.
2. **Cross-condensate coherence span** — geometrically fails at BEC scale; DEFERRED to the CEνNS
   (intra-nucleus) regime where the span condition already holds.
3. **The P1 σ scale** — carries one ASSUMED bandwidth dE (=1 eV); it sets the *magnitude* of R_inc,
   not the fork. The fork verdict (T3) is independent of dE.
4. **P4 flux-vs-seat-size exponent** — the seat-depth *separation* is robust (>3× on any monotone
   flux law), but the absolute B_step and the exponent are OWED to NP19/NP20.

---

## STRESS-TEST SELF-AUDIT (mandatory)

**(1) Independent of inputs, or identity/circular?**
- The **selection rule** (P0) is a pure integer computation from `alpha_grammar`; it is a
  *prediction about which isotope is EC-cocked*, not a re-exposure of a measured value. NOT an
  identity-pass. NATIVE.
- The **decisive P3 result** (ρ_coh ≤ 7×10⁻⁷) is computed from λ_ν (from ħ,c,E_ν) and L (from
  measured BEC N,n). It does **not** derive any measured quantity and then "predict" it — it is a
  geometric inequality. NOT circular.
- **No IDENTITY-PASS:** the tool never calls an engine function against CODATA and calls the match a
  mechanism. The one place a measured number (t_½) enters σ is the *width*, used honestly as an
  input to the cross-section *scale* — and that scale is explicitly flagged as not deciding the fork.

**(2) Any fished exponents / coefficients?**
- **No exponent/coefficient was tried-until-it-landed.** N vs N² is the textbook coherent-sum
  dichotomy (amplitude ∝ N ⇒ rate ∝ N²), not a fished power. The enhancement law
  K_coh = N + (N²−N)·min(ρ,1) is fixed by the two limit checks *before* seeing any output; both
  limits are exact. The branching "4" and g_spin "0.5" are the standard one-channel resonance
  ceiling and the measured-spin weight — not tuned. The P4 Slater Z_eff values are standard atomic
  screening, not fitted to hit 3×; note the fork clears by 11.75×, far from the threshold, so it is
  not threshold-gamed.

**(3) Dimensional check.**
- λ̄=ħc/E: [J·s][m/s]/[J]=[m] ✓. σ_peak=λ̄²·(dimensionless): [m²] ✓. Γ_EC=ħ·(1/s): [J·s][1/s]=[J] ✓.
  σ_avg=σ_peak·(Γ/dE): [m²]·(dimensionless) ✓. R_inc=σ·Φ: [m²][m⁻²s⁻¹]=[s⁻¹] ✓. ρ_coh=λ/L:
  dimensionless ✓. K_coh, K_inc: dimensionless ✓. All rates in s⁻¹; all ratios dimensionless.

**(4) Honest class + what's owed.**
- **Class: NATIVE on the selection rule (T4 PASS); DEFER on the headline fork (T3 FAIL — span);
  PENDING on the read-out (T2 — NP19/NP20).** Prompt completion **A**. This is *not* a Class-A
  physics PASS and it is honestly *not* claimed as one. It is also *not* a KILL — the wedge is not
  falsified, it is deferred to a regime (CEνNS/intra-nucleus, and a coherence-*slope* tabletop test)
  where it can actually be probed. **Owed:** the absolute N\* (NP19/NP20), the cross-condensate span
  (CEνNS-scale or a shorter-λ probe), and the P4 flux exponent.
- **No forbidden move was made:** no G/M/GM/**G_F** in the SDT chain (G_F appears only as the
  OBSERVED comparison column); no tolerance widened after the run; no N\* plugged; 478 keV kept as a
  gamma; no "virtual particles are fictions" over-claim.

---

## Stack update recommendation

`INVESTIGATION_STACK.md`: **ACTIVE** — Prompt completion A with documented DEFER (T3 cross-condensate
span) and PENDING (NP19/NP20 read-out). NATIVE selection rule banked; headline fork not paid out.
Unblocks on NP19/NP20 (absolute B_step) and, for T3, a probe with λ ⊇ target or the CEνNS regime.

---

*NP18 · dual verdict · a complete tool with an honest non-payout: the rule is native, the fork is deferred, the read-out is owed. An honest DEFER beats a fake PASS.*
