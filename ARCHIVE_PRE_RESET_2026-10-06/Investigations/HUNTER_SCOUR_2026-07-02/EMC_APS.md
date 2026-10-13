# HUNTER SCOUR — EMC (03_Electromagnetism_and_Charge) + APS (04_Atomic_Physics_and_Spectroscopy)

> Audit date **2026-07-02**, under `Investigations/HUNTER_PROTOCOL.md`, maximum pressure, assume-fabrication.
> Region: EMC01–04, APS01–06. APS04 SKIPPED (already exposed FABRICATED this session — see below).
> Build harness: MSVC `cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include` via vcvars64
> (VS2022 BuildTools). python3 for APS06. **No repo files edited**; all patches done on copies in scratch.

## Headline

This region is, on the whole, **markedly more honest than APS04**. The two biggest famous-number
targets — **EMC02 (elementary charge e)** and **APS05 (α)** and **APS06 (13.6 eV ceiling)** — each
contains an identity-pass, and in **all three the author caught and correctly labeled it** (Class E /
CONVERGENCE / IDENTITY, "not a prediction"). No fabricated PASS on the scale of APS04 was found here.

The real faults are: (1) **APS03's headline "8.8% RMS" is non-reproducible** and its three result artifacts
mutually disagree; (2) **all 8 APS01 tools fail to compile** (broken include from the CQ→domain rename) so
its "all targets passed" is un-reproducible from repo state, and its framing sells identities (Rydberg,
`zk²=1`) as validated results; (3) **EMC04 / EMC03 / EMC01 over-label an algebraic identity as "DERIVED"**
— though each discloses the circularity in its own caveat.

---

## Fault table

| # | Investigation · claim | Fault type | Evidence | Severity |
|---|---|---|---|---|
| 1 | **APS03** — "cross-scale collapse RMS **8.8%**" (in MEMORY, prompt, `aps03_output.txt`) | NON-REPRODUCIBLE / INTERNALLY INCONSISTENT | Built + ran current `aps03_drafting_crossover.cpp`. Galactic SPARC path hardcoded `../E46_Galaxy_Rotation_Curves/sparc_rotmod.csv` (line 291) **no longer exists** — data moved to `08_Galactic_Dynamics/GD05_.../sparc_rotmod.csv` in the CQ→domain rename. Result: galactic **points=0, PILOT: FAIL, VOID**. With data present my run gives C+A+B **RMS 21.5%** (matches `APS03_VERDICT.md`), NOT 8.8%. The `8.8%`/`pilot PASS`/`3012 pts` in `aps03_output.txt` is a **stale artifact** from before the move; VERDICT.md itself says pilot VOID + 21.5%. **Three artifacts, three different stories.** | **INFLATED / BROKEN** |
| 2 | **APS03** — "8.8%" excludes nuclear (447% resid) | CHERRY-PICK (disclosed) | `aps03_output.txt:30` nuclear resid **447.7%**; `:64` ALL-scales RMS **51.2%**; `:65` 8.8% only "(C+A+B, nuclear excluded)". The exclusion IS printed on the line — honest — but the headline number drops the qualifier. | MINOR |
| 3 | **APS03** — crossover `Φ = Φ_simple` | BORROW (disclosed) | Source line 53–54 + output line 76: "BORROWED baseline crossover (MOND simple); only asymptotes DERIVED." MOND is a prohibited input (§B); here it is **disclosed**, so a flagged borrow not a smuggle. `a₀=G::a_0_SDT` imported from galactic.hpp (c·H₀/2π), tagged DERIVED — provenance out of region. | MINOR |
| 4 | **APS01** — "All targets passed (H <13 ppm …)"; RESOLVED | NON-COMPILING / NO ARTIFACT | **All 8 `.cpp` `#include "cq12_element_data.hpp"`** — file was renamed to `aps01_element_data.hpp`; `cq12_*` does not exist ⇒ **C1083, BUILD_EXIT=2** on every tool (reproduced). No `.exe`, no `results.txt` in the folder. "All targets passed" is not reproducible from repo state. (Fair test: I aliased the header on a scratch copy and `aps01_emissions.cpp` **does** build + reproduce 12.5 ppm / 263.2 ppm — physics is real, repo state is broken.) | **BROKEN** |
| 5 | **APS01** — "Rydberg is not an empirical fit; it is the geometric consequence"; "zk²=1 exact across 118 elements" | IDENTITY-PASS / TAUTOLOGY (un-flagged) | H spectrum comes from `R_∞ = m_e c α²/2h` — the **standard closed-form definition** of the Rydberg energy (identity-grade, exactly as APS06 honestly flags its 13.6 eV). `zk²=1` with `z=(v/c)²,k=c/v` is **≡1 for any v** (verified) — a definitional tautology, zero physics, cannot fail. APS01 sells both as validated results **without** the CONVERGENCE/IDENTITY label APS06 correctly applies. | **CIRCULAR/IDENTITY** |
| 6 | **EMC04** — `P_eff` "E (CALIBRATED) → C (DERIVED)", "RESOLVED [STRONG]", "delete-test passes" | CIRCULAR/IDENTITY (partly disclosed) | Tool prints (`emc04_results.txt:31`, reproduced) its own admission: **"m_e(αc)²/a₀ == k_e e²/a₀² is an algebraic identity."** The `1.0000000000` match and `P_eff = 4αℏc/(πR_p²r_e²)` follow from the definitions `a₀=ℏ/(m_ec α)`, `r_e=αℏ/(m_ec)`. The "delete-test" removes the *symbol* e but keeps α, a₀, r_e, R_p — all of which encode e. So "DERIVED" overstates an identity. Mitigation: honest-residual states "the model does NOT derive α." | **CIRCULAR/IDENTITY** |
| 7 | **EMC03** — `F_occlusion` vs `k_e e²/r²` "relative error 1.4×10⁻¹⁶ PASS" | IDENTITY dressed as agreement (disclosed) | 1.4e-16 = floating-point identity: the occlusion law is built on `P_eff` calibrated to Coulomb. Verdict labels it "COMPUTED (T4 structure + **CALIBRATED P_eff**)" and P_eff-from-geometry "OPEN (EMC01)" — the circularity is disclosed. Class C. | MINOR |
| 8 | **EMC01** — body: "f IS Universal, NOT Fitted"; "EMC01 RESOLVED" | IDENTITY-PASS, self-retracted | Top-of-file audit note (June 2026) **contradicts the May body**: P_eff/f_transfer is "**class E (calibrated)** … the same equation written twice … EMC01-1d confirms algebra, not independent physics … laws.hpp already labels these circularity_assertion: FAILS." Proof `EMC01-1a: αℏc=k_e e²` is a Class-F tautology counted as a PASS. | **CIRCULAR/IDENTITY** |
| 9 | **EMC01** — "G derived; 10¹²² resolved by 4π/N² shell cancellation" | FISHED coefficient (self-flagged FAIL) | `G_naive` off by 10¹²², a factor `4π/N²` applied to cross 122 orders, still misses by **~5×** ("Ratio 0.197"); residual hand-waved as "occlusion geometry." Crossing 122 decades with a chosen factor and landing 5× off is the FISHED tell. Tool logs it **FAIL, exit 1** — disclosed, not hidden. | INFLATED (self-flagged) |
| 10 | **EMC02** — `emc02_results.txt` Candidate-1 numbers (`k=1: 3.319e-12 C, −97.93%`) | STALE HAND-TEXT ≠ tool stdout | Built + ran `emc02_charge_solver.cpp` (BUILD_EXIT=0): current Candidate-1 stdout is `k=1: 1.377e-40 C, −100%`. The `.txt`'s Candidate-1 block is from an older narrative. Candidate 1 FAILS either way and the verdict (e = Tier-1) is unaffected ⇒ cosmetic. | MINOR |
| 11 | **APS05** — Route A "SDT-native, Law V virial" | CONVERGENCE framing (flagged) | `α = √(2·E_ion/m_e c²)` is the standard Bohr/virial relation using measured E_ion + m_e; presented as "Law V native." Verdict itself says "QED reaches the same α² from the same lines" ⇒ flagged convergence, not smuggle. | MINOR |
| — | **APS04** (skipped) — "Lamb shift, zero-fit, machine precision, PPT08 RESOLVED" | FABRICATED (prior audit) | `APS04_HUNTER_AUDIT.md` (2026-07-02) stands: tool never compiled (`std::sqrt` non-constexpr → C2131), results hand-typed, amplitude fished, α²·Ry scale imported. Confirmed still present; **audit holds; PPT08 remains OPEN.** | (already KILLED) |

---

## Per-investigation status

- **EMC01 — Transfer Function.** *CIRCULAR (self-retracted).* Tool builds 6/7, G FAILs exit 1 (disclosed). Force-law geometry = defensible Class C; the "f universal, not fitted" headline is an identity-pass that the file's own audit note retracts to Class E. G is a fished 5× near-miss, honestly logged FAIL. **Honest at the audit-note level; body headline overstates.**
- **EMC02 — Elementary Charge.** *HONEST / OPEN.* Special-focus alarm ("zero-fit, machine precision — is e re-exposed?") is a **false alarm at the verdict level**: the `√(αℏc/k_e)=e` machine-precision line lives inside Candidate 3, explicitly labeled **CIRCULAR, Class E, FAILS**. Overall verdict = INCONCLUSIVE, e stays Tier-1. Tool builds + runs + reproduces. **Model auditee: this is how you handle an identity-pass.** (Only ding: stale Candidate-1 numbers in the .txt, cosmetic.)
- **EMC03 — Repulsion = Inverse Convergence.** *HONEST (Class C).* Builds + runs + reproduces. 1.4e-16 "match" is a calibrated identity, disclosed as CALIBRATED P_eff / OPEN geometry. Sign-symmetry claim is structural. Fine.
- **EMC04 — Electropause Binding.** *CIRCULAR/IDENTITY (over-labeled).* Builds + runs + reproduces 4/4 PASS. The `1.0000000000` binding=Coulomb match is — by the tool's own print — an algebraic identity; "P_eff DERIVED / delete-test clean / RESOLVED [STRONG]" overstates it. The α caveat is stated. **Real work, inflated verdict label.**
- **APS01 — Emissions.** *BROKEN + identity-framed.* All 8 tools non-compiling (C1083, missing `cq12_element_data.hpp`); no exe/txt committed; "all targets passed" un-reproducible. Physics recovers with a 1-line include fix (12.5 / 263.2 ppm real), but Rydberg + `zk²=1` are sold as results without the honesty labels APS06 uses. **Fix the include; relabel the identities.**
- **APS02 — Emission Prediction.** *ANCHOR-DRIVEN (same header break).* Reads measured `IE1` per element, `v1=√(2·IE1/m_e)` (virial) → "predicts" first-resonance lines; that's an anchor-based calc, not from-nothing. Shares the `cq12_element_data.hpp` break. Drag-factor trend (1.76/1.40/1.02) is a real monotone but descriptive.
- **APS03 — Drafting Crossover.** *NON-REPRODUCIBLE headline / inconsistent artifacts.* Builds, but galactic data path is dead ⇒ pilot VOID; "8.8%" is a stale pre-rename number; VERDICT.md (21.5%, Class D PARTIAL, galactic FAIL) is the reproducible state and disagrees with its own `aps03_output.txt`. Crossover is a disclosed MOND borrow; 8.8% excluded nuclear (447%). **Best current honest number 21.5%, not 8.8%.**
- **APS05 — α from Fine/Gross.** *HONEST / PASS.* Builds + runs + reproduces byte-for-byte; independently recomputed Route B (136.912, −0.091%) and Route A (137.073). **Does NOT claim to derive α** — labels it a MEASURED anchor read two independent ways, geometric derivation explicitly `[OPEN] E51/OP-3`. Route B `α²=16·(Δν_2P/cR∞)` is genuinely α-independent (no identity-pass). Strong.
- **APS06 — Emission Ladder / Seat Depth.** *HONEST / PASS.* python3 tool runs exit 0, reproduces. Special-focus check confirmed: the 13.6 eV / 0.000 ppm ceiling is flagged **IDENTITY/CONVERGENCE, "not an independent measurement," QM06 mode explicitly avoided** in three places. Genuinely independent parts (monotone ordering, no-proton-only-nucleus wedge, exceptionless neutron-requirement survey) earn NATIVE/OBSERVED. **Best-practice honesty.**

### Compile/run ledger (mtime + BUILD_EXIT, reproduced 2026-07-02)
- EMC02 `emc02_charge_solver.cpp` → **BUILD_EXIT=0**, runs, matches .txt.
- EMC03 `emc03_repulsion_inverse.cpp` → **BUILD_EXIT=0**, runs, matches .txt.
- EMC04 `emc04_electropause.cpp` → **BUILD_EXIT=0**, runs, matches .txt (prints its own "algebraic identity" admission).
- APS03 `aps03_drafting_crossover.cpp` → **BUILD_EXIT=0**, runs, but galactic pilot VOID (dead data path) → 8.8% not reproducible; 21.5% is.
- APS05 `aps05_alpha_fine_gross.cpp` → **BUILD_EXIT=0**, runs, matches .txt byte-for-byte.
- APS06 `aps06_seat_ladder.py` → **exit 0**, matches .txt.
- APS01 (all 8 `.cpp`) → **BUILD_EXIT=2, C1083** missing `cq12_element_data.hpp`. (Scratch alias → `aps01_emissions.cpp` builds, reproduces 12.5/263.2 ppm.)
