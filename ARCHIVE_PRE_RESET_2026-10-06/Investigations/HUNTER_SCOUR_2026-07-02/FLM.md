# HUNTER SCOUR — Region 01_Foundations_and_Lattice_Mechanics (FLM02–FLM13)

> **Auditor:** HUNTER, maximum pressure, assume-fabrication. **Date:** 2026-07-02.
> **Protocol:** `Investigations/HUNTER_PROTOCOL.md`. **Model hunt reference:** `APS04_HUNTER_AUDIT.md`.
> **Method:** every C++ tool COMPILED + RAN (MSVC 19, `/std:c++20 /O2`, scratchpad); every Python tool
> RAN (py 3.13 + numpy 2.3 + scipy 1.18); every `*_results.txt` diffed against live stdout; every headline
> PASS recomputed by hand for identity/circularity/borrow.
> **FLM01 skipped** (already HUNTER-audited 2026-07-02) — its audit was read and **stands** (it self-corrected
> a wrong grep and correctly downgraded the `1e10` in `state28d.hpp::calculate_occlusion` to a *latent fitted
> parameter*; that is canon-adjacent, outside this remit).

## Headline

**No fabrication found in the FLM region.** Every tool that claims a numerical PASS **actually compiles/runs
and reproduces its stated numbers** — several byte-for-byte against the checked-in results file. This region is
the *opposite* of APS04: results files are genuine UTF-16/UTF-8 captured stdout (not hand-typed prose), scope is
honestly labelled, and the two recent (FLM11/FLM12) self-audits are truthful. The **one real fault** is
**FLM02**: a cluster of "12/12 / 22/22 PASS" tests that recover the proton/electron mass from `V_disp` — but
`V_disp` is *defined from that mass* in `laws.hpp`, so those passes are algebraic tautologies dressed as
Law-IV verifications. Real tool, real run, over-graded → **INFLATED**, not fabricated (and `laws.hpp` itself,
and FLM04, already flag the circularity).

---

## Fault table

| # | Investigation · claim | Fault type | Evidence | Severity |
|---|---|---|---|---|
| 1 | **FLM02** — "Law IV: m_p from V_disp_p [kg] … 0.0000% PASS" (and m_e, and "F=ma V_disp route", and `flm02_local_update_theorem` LUT-5b/5d "m_proton derived", "m_p/m_e from V_disp ratio") | **IDENTITY-PASS / CIRCULAR** | `laws.hpp:464,468` define `V_disp_p = 3·m_p·l_P³·c²/Φ`. The test computes `m_check = Φ·V_disp_p/(3·l_P³·c²)` → identically `m_p`. It is `x·(k/x)·(1/k)==x` — cannot fail. `flm02_local_update_theorem.cpp:461` even comments `// Using the known value to check`. Presented inside a "12/12 numerical verification" table as if it validated Law IV. | **INFLATED** |
| 2 | **FLM02** — SR sub-tests: "T.dilation 1/γ=√0.75 PASS", "Doppler f₀√3 PASS", "budget v_circ²+v²=c² PASS" | Tautology graded as verification | These evaluate the SR closed forms and compare to the same closed forms; algebraic identities, not predictions. Honest but pad the PASS count. | **MINOR** |
| 3 | **FLM02** — INVESTIGATION.md says tool is `cq08_statistical_inertia.cpp`, "12/12"; only documents 1 of 4 tools | Doc drift | Real file is `flm02_statistical_inertia.cpp`; the other three tools (22/22, 15/15, 19/19) are undocumented. No false number, just stale. | **MINOR** |
| 4 | **FLM06** — "5/5 routes snap to machine-exact = ℓ_P" (routes to the Planck length) | IDENTITY (by construction) | Routes 1,2,5 substitute `G→ℓ_P²c³/ℏ` so they *are* ℓ_P re-expressed. **BUT the tool states this itself**: verdict = "NOT self-deriving: every route loops back to ℓ_P (Axiom R1). They were ℓ_P in disguise." Self-flagged, so not a fault — logged for completeness. | **honest (no fault)** |
| 5 | **FLM09** — "self-consistency ratio = 1.000000 [PASS]", Schwinger E_S recovered | INHERITED / tautology, **disclosed** | `E_S = ℏc/(e·λ_C²)` with `λ_C=ℏ/(m_e c)` is algebraically `m_e²c³/(eℏ)` — an identity. Tool labels it `[INHERITED] … not newly derived` and `[KILLED]` for the bare-lattice overclaim. Honest OPEN. | **honest (no fault)** |

**No FABRICATED and no BROKEN findings in this region.**

---

## Per-FLM status (1-line each)

- **FLM02** — **INFLATED.** 4 tools all compile & run (12/12, 22/22, 15/15, 19/19 as claimed); the ⟨cos²θ⟩=1/3 lattice geometry and GPI→c are real, but the "mass from V_disp" passes are circular identities over-graded as Law-IV verifications. Legacy May-2026 (Tyndall byline).
- **FLM03** — **CLEAN** (control). Builds clean, 4/4 PASS, output byte-matches `RUN_LOG.md`; v(R_p)=1.8316c, v(r_e)=c, v(a₀)=αc@0.083%. Honest convergence.
- **FLM04** — **OPEN-honest.** Markdown only, no tool. `FLM04_RERUN.md` is a *self-downgrade*: relabels its own earlier findings "NOT COMPUTED / UNEARNED", catches its own force magnitude as "tautology (class F)". Anti-fabrication document.
- **FLM05** — **CLEAN.** Both tools compile; 9/9 + 6/7 (the 1 FAIL is the *documented intentional* `V_torus≠V_disp` demonstrator) = 15/16 exactly as claimed. Rotorpause 0.9772 is derived `√(m_p/m_e)a₀/(√(m_p/m_e)+1)`, not fitted. Legacy Tyndall byline.
- **FLM06** — **CLEAN (honest identity).** Compiles, 5/5, output byte-matches results.txt. Fundamentally an identity (ℓ_P in disguise) but the tool *says so* and grades itself NOT-self-deriving. Results.txt is genuine UTF-16 stdout (its early mtime is a sync artifact).
- **FLM07** — **CLEAN.** Compiles, output byte-matches results.txt. Parts A–C exact geometry (icosa gap 0.102924, tet/oct voids); Part D explicitly labelled "structural conjecture (numbers align, not proven)." Honest.
- **FLM08** — **CLEAN (strong).** Compiles against its own standalone `sdt/lattice_structure.hpp`; **27 PASS / 0 FAIL** exactly as claimed. All are pure math identities (arccos(1/3), 2π−5δ, void=1−π√3/16) verified to 9 figures — legitimate "machine precision." Separates [GEOMETRY] (proven) from [IDENTIFICATION] (not asserted). Over-determined and honest.
- **FLM09** — **OPEN-honest.** Compiles, output matches results.txt. Schwinger "PASS" is an `[INHERITED]` identity, explicitly labelled; bare-lattice overclaim `[KILLED]`; A2/Arm-B `[OPEN]`. No overclaim.
- **FLM10** — **OPEN-honest (real computation).** `flm10_phase1_isotropy.py` runs (scipy) and **reproduces `phase1_run.log` deterministically**: diamond anchor A^U=0.0725 cubic, amorphous N=216 A^U=0.0492, per-seed 0.6066/0.5351/0.1415, p=−1.78. Verdict QUALIFIED(C)/PENDING(D) with a candid "what is NOT earned" list (2 sizes, noisy N=64, artifact stiffness, no ω(k)). Genuine work, correctly not oversold.
- **FLM11** — **OPEN-honest (CONVERGENCE).** `flm11_ruler_count.py` runs (exit 0), output byte-matches results.txt; count P=4+1 pre-committed in RUN_LOG before the run. Only number is the tautological Law-V residual 1.0. Self-audit correctly grades C/CONVERGENCE and flags the grip→property map as "argued, not proven." Recent J.C.Harvey; self-audit is honest.
- **FLM12** — **OPEN-honest (NATIVE ontology / OWED numbers).** `.cpp` output **byte-identical** to results.txt (only a BOM diff); both D1 python tools run clean. D1 verdict = **UNPAID** (deuteron bracketed 0.51–44 MeV, *not* predicted); D1′ recovery computes TARGET and INFLUX independently, honestly reports the nuclear regime **overshoots 11×**, and **explicitly REJECTS the geometric-mean "1% match" as regime-fragile numerology**. `m_p c²/V_p=6.02e34 Pa` hand-verified. Exemplary self-hunt. Recent J.C.Harvey; self-audit verified honest.
- **FLM13** — **OPEN-honest (SPEC only).** PROMPT.md only, no tool, no PASS. Its R5 rule pre-emptively forbids the identity-pass trap ("distinguish ROLE from VALUE … do not present a tautology as an extraction; else ROLE-only/OPEN, not PASS"). Well-designed, not started.

---

## Verdict line

> **Region completion A** (all 12 folders run to ground; every executable compiled+ran or was confirmed
> tool-less) · **Physics class:** FLM08/FLM03/FLM05/FLM06/FLM07 = NATIVE/CONVERGENCE geometry (honest);
> FLM09/FLM10/FLM11/FLM12/FLM13 = OPEN-honest; **FLM02 = INFLATED** (circular Law-IV mass passes) ·
> **Recovery:** FLM02 is corrected by *relabelling* the `m↔V_disp` round-trips as identities (not deleting
> them — the Closure Principle: they *define* V_disp, they don't *verify* mass) · **Cascade root:** the FLM02
> circularity is the same root already flagged in `laws.hpp` (V_disp defined from mass; `six_pi_5 ↔ V_disp`
> mapping "asserted, not derived", line 1280) and in FLM04's self-downgrade — one shared open closure
> (mass→V_disp is a *definition*, so no Law-IV test built on it can be independent), not 6 separate faults.

## Note on the APS04 signatures — where each landed in FLM

- **Hand-written results.txt:** NOT FOUND. Every results file is real stdout (verified by byte-diff / UTF-16 BOM / live reproduction).
- **Reverse-engineered number:** NOT FOUND. Every recomputed headline matched the tool.
- **Imported scale + fished multiplier:** NOT FOUND as a hidden fit. FLM09's α²Ry-style borrow is *disclosed* `[INHERITED]`; FLM12's αℏc/nuclear-P routes are disclosed and the fished exponent/geo-mean are *rejected in-tool*.
- **False zero-fit range:** NOT FOUND. FLM12 bracket 0.51–44 MeV is honestly called a bracket, not a prediction.
- **Numerology "tests":** the only ones present (FLM12 geometric-mean, D1 squared exponent) are **flagged and discarded by the author**.
- **Identity-pass:** FOUND in FLM02 (undisclosed there) and FLM06/FLM09 (disclosed). FLM02 is the one that needs the label added.
- **Tool never built:** NONE — all 8 C++ tools and all 4 Python tools executed this session.
