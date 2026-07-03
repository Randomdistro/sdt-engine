# HUNTER SCOUR — Region 06: Gravitation & Orbital Mechanics (GOM01–GOM13)

> **Auditor:** HUNTER (maximum pressure) · **Date:** 2026-07-02 · **Protocol:** `Investigations/HUNTER_PROTOCOL.md`
> **Assumption:** fabrication until disproven. **Canon rule enforced:** no G/M/GM in the SDT chain (only as an
> `OBSERVED` comparison column); gravity is `g=v²/R`, `ϟ=v²R/c²`. DEGENERATE results that HONESTLY say "matches
> GR but doesn't beat it" are FINE and NOT faulted; only over-claim (Class A / NATIVE on a degeneracy) is a fault.
> **Compiles reproduced this session with MSVC 2022 BuildTools** in scratchpad. No audited files edited; canon
> (`Engine/include/sdt/`, `Laws/`) untouched.

## Headline

**No FABRICATED or BROKEN result in this region.** In sharp contrast to APS04 (non-compiling tool, hand-typed
"machine-precision" PASS), every *executed* GOM tool that I built **compiles clean and its stdout matches the
committed results file** (GOM08 and GOM06-chirp reproduced number-for-number this session). The GOM authors are
mostly scrupulous about labelling GR-agreement as **CONVERGENCE / DEGENERATE**, and GOM07 in particular is a model
of honesty. The real faults are two **INFLATED verdicts** (GOM09 headline, GOM11 amplitude) and a family of
**IDENTITY/CIRCULAR "PASS" lines** that are true-by-construction and should not be scored as predictions.

## Execution map (executed vs spec)

| Executed (has run artifact) | Spec only (unexecuted — nothing to fault) |
|---|---|
| GOM02, GOM04, GOM05, GOM06, GOM07, GOM08, GOM09, GOM11 | GOM01, GOM03, GOM10, GOM12, GOM13 |

GOM08 is the only dir shipping a compiled `.exe`; I rebuilt it and GOM06-chirp from source anyway.

---

## Fault table

| # | Investigation · claim | Fault type | Evidence | Severity |
|---|---|---|---|---|
| 1 | **GOM09** verdict headline "**RESOLVED — 1.82% RMS to PREM**" for an investigation named *Earth Core Seismic Speed* | INFLATED (metric-swap / cherry-pick) + INTERNALLY INCONSISTENT | The real run `output.txt` reports **P-wave RMS 6.24%, S-wave 6.69%**, and its own success box **`[ ] v_p RMS error < 5%` is UNCHECKED (FAIL)**, as is `[ ] surface v_p`. The "1.82%" is the *g(r)* RMS from the April-dated `RESULTS.md` — a different quantity from the seismic-velocity target. The verdict promotes the passing g-metric as the headline and drops the failing velocity criterion. `RESULTS.md` also lists "v_p RMS 11.5%" vs `output.txt`'s 6.24% — the two artifacts disagree ~2×. | **INFLATED** |
| 2 | **GOM11** "h_M2 (dynamic) = **0.628 m** vs 0.63, 0.4% PASS" | PLUG (undisclosed CALIBRATED knob) | Equilibrium height from koppa is only **0.272 m**; the match to 0.63 rides entirely on `Q_M2 = 2.31` (`gom11_ocean_tidal.cpp:19`), labelled "OBSERVED". Independent recompute: the Q that lands 0.63 *exactly* is **2.319** — i.e. Q is tuned to the target to 3 sig figs. The amplitude "PASS" is a fitted resonance factor, not a prediction. (The **M2/S2 ratio 2.177** in the same tool IS genuine convergence — see #4 — so the tool is half-real.) | **INFLATED** |
| 3 | **GOM08** STEP 5 "**k_Sun and c recovered from geometry alone**, c to 0.0009%", presented as a GOM04 closure/verification | CIRCULAR | `k_Sun_from_precession = k_from_precession(R_Sun,a,e, delta_phi_Mercury)` where `delta_phi_Mercury` is the **measured 42.98″/cy target itself** (`laws.hpp:797,815`). Inverting the same formula on the same measured number to "recover" its own input is the protocol's textbook circularity ("τ from σ → σ from τ"). `c_from_closure = k·v_surface_Sun` then rides on that circular k. GOM08's *headline* (the precession match) is honestly Class-C CONVERGENCE and NOT faulted; only STEP 5's framing as an independent closure is circular. | **CIRCULAR** |
| 4 | **GOM11 / GOM09 / GOM08** "M2/S2 ratio / g / precession **DERIVED from koppa alone, no G, no M**" | IDENTITY (koppa ≡ GM/c², v_surf ≡ √(GM/R)) | `koppa = v_surf²R/c²` is *numerically* `GM/c²`; `v_surf` (e.g. Earth 7909 m/s) is the low-orbit speed `√(GM/R)` (recomputes to 7909.79). So `g=v²/R = GM/R²`, and the M2/S2 koppa ratio (2.177) equals the Newtonian mass tidal ratio (2.178, recomputed). This is **framework-sanctioned** — v_surf/R are measurable without knowing G — and the authors label it CONVERGENCE (Class C), so it is **not a deceptive fault**; logged as the shared degeneracy so it is not mistaken for an independent prediction. | **IDENTITY (disclosed)** |
| 5 | **GOM05** four "0.0000% PASS" proofs (`z = 1−c_local/c`, `z = 1−ℓ_P/ℓ_P,∞`, Shapiro = standard) | IDENTITY-PASS (tautology) + minor inconsistency | The tool *defines* `c_local ≡ c(1−z)` and `ℓ_P(r) ≡ ℓ_P,∞(1−z)`, then "proves" `z = 1−c_local/c` — true by construction, 0.0000% is guaranteed. Shapiro 123.66 µs is stated to equal "the standard formula number." Disclosed in the "Honest scope" section (labelled Class C, identities "exact given ϟ"), so not deceptive. **Minor inconsistency:** solar-surface c-deficit printed as **636.49 m/s** (Section I) and **741.78 m/s** (Section II table) for the same location. | **MINOR** |
| 6 | **GOM02** verdict "**GM recovery … to 0.0000% error**" | IDENTITY-PASS | Source computes `GM_Sun = bridge::GM_equivalent(k_Sun,R_Sun)` then compares to `ϟ·c²` — the same quantity; 0.0000% is definitional. GOM02's own body text says "GM is koppa·c², a DERIVED quantity", so it does not sell this as a prediction. Class labelled A/B but the *content* is the koppa identity + a k-hierarchy tabulation. | **MINOR** |
| 7 | **GOM06** verdict cites chirp "**67.65 vs 68 Hz PASS**" but `gom06_chirp_results.txt` is a truncated/corrupted UTF-16 stub (stops after the koppa header line) | Stale/incomplete run-log (NOT fabrication) | The results file does not contain the quoted number — but I **rebuilt the tool from source: it compiles clean and prints 67.65 Hz, error −0.52%**, and the `.cpp` itself openly states "The PASS is … an ALGEBRAIC IDENTITY of the koppa bridge, not an independent numerical surprise." Number real, honesty exemplary; only the saved artifact is corrupt. | **MINOR** |
| 8 | **GOM09** `RESULTS.md` links to `gom09_displacement_pressure.cpp` (and a `c:/Users/Jimmi/sdt-engine/...` path prefix) that does not exist in the dir | Broken provenance link (dead file reference) | Dir contains `gom09_seismic/backward/trefoil_test.cpp`; the linked `displacement_pressure` file and the `~/sdt-engine/` (non-OneDrive) paths are stale. Cosmetic; the seismic tool is present and runs. | **MINOR** |

---

## Per-investigation status (one line each)

- **GOM01** — SPEC only (zk²=1 depth-engine framework). Unexecuted; no verdict/results. *Nothing to audit; honest spec.*
- **GOM02** — EXECUTED, 15/15. k-hierarchy table + koppa identities. **GM-recovery "0.0000%" is an IDENTITY** (fault #6, disclosed). Otherwise a clean tabulation. **CONVERGENCE.**
- **GOM03** — SPEC only (lunar pendulum inversion). `.cpp` present, never run; no results. *Honest spec.*
- **GOM04** — EXECUTED. "Derive c from Mercury precession to +0.0009%". c IS an output (v_surface from Earth kinematics, no c upstream) — legitimate as a *convergence*, but `zk²=1` closure is a definitional tautology and the k used is the precession-inversion k (feeds the GOM08 circularity, #3). **CONVERGENCE, borderline circular.**
- **GOM05** — EXECUTED, 4/4. Variable-closure / c-gradient / lumiopause. All four "0.0000%" are **IDENTITY-PASSES** (#5), disclosed; 636 vs 742 m/s internal inconsistency. Lumiopause 20857 AU = `pressure_domain()`. **CONVERGENCE (identities), one falsifiable prediction (Oort clustering).**
- **GOM06** — EXECUTED. GW chirp/memory/echoes. **Exemplary honesty:** `GM→c²ϟ` and 96/5 explicitly "borrowed-as-convergence"; chirp 67.65 Hz **rebuilt & confirmed** (#7 = corrupt artifact only). Echoes are the one native falsifiable claim. **CONVERGENCE + 2 native predictions, correctly labelled.**
- **GOM07** — EXECUTED. Reflected-light redshift vs Lanza 2016. **Model honesty:** self-corrects a swapped prediction, flags the cancellation-GR **DEGENERACY** explicitly, does NOT claim Class A. slope −1.11±1.28 (0.9σ from SDT-flat). **DEGENERATE, honestly — no fault.**
- **GOM08** — EXECUTED (rebuilt this session, output matches `results.txt` exactly). Mercury 42.9930″/cy vs 42.98. Honestly **Class C CONVERGENCE**; `ϟ_Sun=R/k²` openly maps to `GM/c²`. **Headline clean; STEP 5 is circular (#3).**
- **GOM09** — EXECUTED (real run with honest FAIL boxes). g(r)/P(r) good (~2–4%), but **v_p/v_s RMS 6.24%/6.69% FAIL the committed <5%**. **Verdict headline "RESOLVED 1.82%" is INFLATED (#1)** — swaps to the passing g-metric, drops the failing velocity target that names the investigation.
- **GOM10** — SPEC only (Lagrange from koppa). `.cpp` present, never run. Openly declares `μ=ϟ₂/(ϟ₁+ϟ₂)` "numerically identical to M₂/(M₁+M₂)" — honest identity. *Honest spec.*
- **GOM11** — EXECUTED. Tides from koppa gradient. **M2/S2 ratio 2.177 is genuine convergence**; **M2 amplitude PASS is a PLUG on Q=2.31 (#2, INFLATED).** Mixed.
- **GOM12** — SPEC only (solar-system convergence budget). No tool/results in dir. *Honest spec.*
- **GOM13** — SPEC only (occlusion-altitude Cavendish; HTML experiment decks, "unflown"). No tool/results. *Honest spec.*

---

## Verdict line

> **Region completion:** no FABRICATED/BROKEN result. **Physics class of executed GOMs:** CONVERGENCE /
> DEGENERATE, mostly honestly labelled. **Faults:** 2 INFLATED verdicts (GOM09 metric-swap, GOM11 Q-plug),
> 1 CIRCULAR closure (GOM08 STEP 5), a family of disclosed IDENTITY-PASSes (GOM02/05/09/11), and minor
> stale-artifact/inconsistency noise. **Cascade root:** all the "no G/M" claims run to ground at the single
> shared identity **`ϟ=v²R/c² ≡ GM/c²` with `v_surf ≡ √(GM/R)`** — which the framework sanctions and the
> honest verdicts label CONVERGENCE. The only place that identity turns into a *fault* is where a verdict sells
> it (or a tuned Q) as a fresh prediction (#1, #2) or re-inverts the target to "recover" its own input (#3).

— HUNTER · GOM region · 2026-07-02
