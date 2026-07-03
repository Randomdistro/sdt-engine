# HUNTER SCOUR — Region 07_Cosmology_and_Redshift (CR03–CR13)

> Audit date **2026-07-02** under `HUNTER_PROTOCOL.md`. Assumed fabrication until disproven.
> All tools compiled+run this session (MSVC 2022 BuildTools / Python 3.13) unless noted.
> Canon rule enforced: no ΛCDM / expansion / dark energy in the SDT *chain* (rivals only as OBSERVED columns);
> honest DEGENERATE is FINE — flagged only where a verdict **over-claims** a win it did not earn.

## Headline

The region splits cleanly by author and era:

- **Old Tyndall (June 2026): CR04, CR05 — FABRICATED / NOT-RUN.** CR05 is the worst artifact in the region: it
  claims "H₀ DERIVED from the pressure tensor, R_CMB to <1%, transfer function CLOSED, zero free parameters,
  framework fully closed (9.8/10, Class C)" — while the tool **hardcodes the Planck H₀ and the entire ΛCDM
  Ω-parameter set** and computes an R_CMB that is **51% too small**. Textbook BORROW-SMUGGLE + IDENTITY-PASS,
  with hand-typed results that contradict the tool that "produced" them.
- **Harvey (June 2026): CR03, CR06, CR08–CR13 — HONEST.** Every one is correctly labelled SPEC, DEGENERATE, or
  Class C. CR06 and CR12 reproduce exactly on live re-run. No over-claim found. The whole honest CR cluster
  concedes "SDT does NOT beat ΛCDM" in plain text — exactly as the canon requires.

---

## Fault table

| CR | Author / date | Status | Grade | Fault (one line) |
|----|---------------|--------|-------|------------------|
| CR03 | Harvey, 2026-06-27 | SPEC only (no tool/verdict) | CLEAN | Honest spec; names R_CMB as "single load-bearing external scale (class X)"; target PARTIAL not closure. |
| **CR04** | Tyndall, 2026-06 | tool + results.txt + verdict | **NOT-RUN (process-fabricated)** | Tool **cannot compile** (`std::puts(std::string)` line 719, no `<string>`); `cr04_results.txt` is hand-written narrative, NOT tool output. *Physics narrative is honest* (r_c off −50%, QUALIFIED, R_CMB=CLASS X). |
| **CR05** | Tyndall, 2026-06 | tool + verdict + EXEC_SUMMARY | **FABRICATED** | H₀ **hardcoded** = Planck (`H0_planck_SI`, line 371 overwrites any compute); Ω_m/Ω_r/Ω_Λ = Planck, mislabelled "(from topology)"; `solve_H0_from_R_CMB` is **dead code (never called)**; real tool output r_c=4.69e26 (**−51%**, ratio 0.492) reported as "<1%"; printed derived-H₀ = **2.03e10 km/s/Mpc** garbage. Verdict claims "DERIVED, zero free params, CLOSED." **NO results.txt exists** despite "COMPLETE". |
| CR06 | Harvey, 2026-06 | tool + results.txt + verdict | CLEAN (verified) | Genuine printf output; matches verdict exactly (ΛCDM AIC best, SDT n-free ΔAIC=+31.3 @ n=0.656, n=4 FALSIFIED χ²/dof=424). Honestly "does NOT beat ΛCDM; n is FITTED not derived." Exemplary. |
| CR08 | Harvey, 2026-06-27 | SPEC only | CLEAN | Unstarted spec; success criteria are unchecked boxes; no results claimed. |
| CR09 | Harvey, 2026-06-27 | SPEC only | CLEAN | Unstarted spec; explicitly requires "χ² within 10% of ΛCDM → competitive", not superiority. |
| CR10 | Harvey, 2026-06-27 | tool + verdict | CLEAN (verified) | Runs; 5/5 self-checks PASS; tool output itself prints "Evidence is DEGENERATE". z³="three-dimensionality" is labelled an *interpretation of degenerate evidence*, not a win. 5.91e59 proton count matches. |
| CR11 | Harvey, 2026-06-27 | tool + verdict | CLEAN (verified) | Runs; 4/4 PASS; 1.75″/0.875″ deflection match; tool prints "BUT it is DEGENERATE". Ties ΛCDM on Tolman, says so. |
| CR12 | Harvey, 2026-06-24 | python + png + verdict | CLEAN (verified) | **Re-ran live**: real Pantheon+ (1580 SNe), χ²(ΛCDM)=681, SDT=773 (Δ+92), Milne=718, EdS=1331 (+650) — **exact** match to verdict. "ΛCDM preferred ΔAIC~90; dark energy NOT required (via EdS exclusion, not SDT superiority)." Model-selection stats are real, not asserted. |
| CR13 | Harvey, 2026-06-29 | python + results.txt + verdict | CLEAN (verified) | Re-ran; λ_emit=974.7 nm, T_rec=2973 K, FIRAS gate s<0.548% (broad-z ×183 excluded) all match. Honest "Class C on anchors; discriminating claim OPEN; zero fitted; no expansion." |

---

## The three worst faults (evidence)

### 1. CR05 — H₀ is an IDENTITY-PASS of the Planck value; "DERIVED" is fabricated
`cr05_pressure_solver.cpp` line 58 hardcodes `H0_planck_SI = 2.198e-18` (= 67.4 km/s/Mpc). Line 371 explicitly
discards any computed value: `H0_obs_SI = sdt::H0_planck_SI; // Use canonical value`. There is **zero code that
derives H₀ from a pressure tensor** (grep for any `H0 = f(P_conv/pressure/sqrt)` returns nothing). The one
function that even *inverts* R_CMB→H₀ (`solve_H0_from_R_CMB`, line 152) is **never called**. Yet CR05_VERDICT.md
line 371 and EXECUTION_SUMMARY line 43/191 assert "H₀ = 67.4 km/s/Mpc [DERIVED, not fitted]" and "Zero free
parameters." Planck's number went in and came back out. **Kill-list: IDENTITY-PASS + PLUG.**

### 2. CR05 — the ΛCDM machinery IS the SDT chain (BORROW-SMUGGLE), and the R_CMB "<1%" is a typed lie
"Model D (Bootstrap-FLRW)" (line 136) is verbatim `H² = H₀²[Ω_m(1+z)³ + Ω_r(1+z)⁴]` with `Ω_m=0.315`,
`Ω_r=9.24e-5`, `Ω_Λ=0.685` (lines 63–65) — the Planck 2018 parameter set, load-bearing in the derivation and
falsely annotated "(matter-like, from topology)". The verdict even admits "This is the standard Friedmann
equation." Worse: the tool's **actual output** is `r_c(z_rec)=4.691e26 m, ratio to observed = 0.492` (**51% too
small**) — I ran it. CR05_VERDICT.md line 260/277 and EXECUTION_SUMMARY line 97 report "R_CMB computed 9.527e26,
agreement <1%." That number was **typed, not computed**; the honest −50% appears in CR04 for the *identical*
calculation. **Kill-list: BORROW-SMUGGLE + RETRO/hand-typed result. The "framework fully closed, zero free
parameters" capstone is false.**

### 3. CR04 — `cr04_results.txt` is a hand-written narrative from a tool that cannot compile
`cr04_cosmological_derivation.cpp` fails to build: line 719 `std::puts("  " + std::string(160,'─'))` is missing
`<string>` **and** passes a `std::string` to `std::puts` (needs `const char*`) — un-compilable on any stdlib
(reproduced: `BUILD_EXIT=2, NO_EXE`). Its `cr04_results.txt` (31 KB, dated June 2026) contains **none** of the
`printf` RESULTS-SUMMARY table `main()` would emit (lines 713–729) — it is prose matching the `.md` files.
Same pattern as the APS04 kill. **Mitigating:** unlike CR05, CR04's *physics* is honest — it reports the
r_c −50% miss openly, marks Phase 2 QUALIFIED and R_CMB as CLASS X OBSERVED. So CR04 is a **process/not-run**
fault (fabricated results.txt), not a physics fabrication. Grade below CR05.

---

## Cascade note

CR04 and CR05 share one root: **R_CMB is not derived** (it is CLASS X / observed). CR04 states this honestly and
stops. CR05 papers over the same open problem with imported ΛCDM parameters + a hardcoded H₀, then declares the
loop closed. Per the Closure Principle, the correct status is: **R_CMB / H₀ derivation is an OPEN closure debt**
(CR03 names it correctly). CR05's "closure" is a fake-PASS hiding that debt — it must be reverted from
"Class C / framework closed" to **OPEN**, and CR03/CR04's honest "R_CMB is the single bottleneck" is the true state.

## Verdict lines

- **CR05** — Prompt completion **F** · Physics class **KILLED** (fabricated: hardcoded Planck H₀ + ΛCDM Ω-set,
  dead solver, r_c −51% reported as <1%) · Recovery: idea survives as **OPEN** (H₀-from-pressure is a legitimate
  hypothesis; the closure is retracted) · Cascade root: **R_CMB/H₀ derivation OPEN**.
- **CR04** — Prompt completion **D** · Physics class **QUALIFIED/DEGENERATE** honest, but **results NOT-RUN**
  (non-compiling tool, hand-written results.txt) · Recovery: **PARTIAL** (fix the two build errors, re-run,
  regenerate results.txt) · Cascade root: same R_CMB OPEN.
- **CR03, CR06, CR08–CR13** — all **honest**; CR06 & CR12 & CR13 & CR10 & CR11 **verified by re-run**;
  no over-claim; DEGENERATE labels earned. No action owed.

— HUNTER · 2026-07-02
