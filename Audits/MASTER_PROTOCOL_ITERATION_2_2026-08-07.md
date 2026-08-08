# Master-Protocol Iteration 2 — 2026-08-07

**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none  
**Executable loop:** GOM26 (completed) — re-audit of GOM25 orbital-invariant reformulation  
**Upstream:** `Audits/MASTER_PROTOCOL_ITERATION_1_2026-08-07.md`

## 1. Scope and coverage

Continues the solar §XII program. Whole-repository inventory from Iteration 1 stands (2307 tracked files). This iteration read/executed:

- GOM25 assessment + PROMPT (prior)
- GOM26 PROMPT (new pre-registration)
- `gom26_koppa_invariant.cpp` direct execution
- solar_propagation dataset files (2025 Horizons; wrong-center 2024 quarantine; Cassini TDF census)
- engine `depth_closure` / `bridge::koppa_Sun` delete-test only (no edit)

Unread regions remain inventoried, not line-reviewed (ATOMICUS, Hubble bulk, Release/docs mirrors).

## 2. Claim ID and exact claim

GOM26-C1…C4 as in `GOM26/.../PROMPT.md`: solar `ϟ` is a Keplerian invariant `μ/c²` from EMB–Sun vectors, spectrally compatible without elliptic-CV inflation, stable on hold-out.

## 3–7. Mechanism / equations / ICs / parameters / data

See `GOM26_ASSESSMENT.md`. Hold-out multi-year Sun-centered product not obtained this cycle; INTRA_YEAR fallback pre-registered and used.

## 8–11. Pre-registration / validation / commands / run log

Complete. Validation A/B PASS. Stdout `.audit-tmp/gom26_run.txt`.

## 12–15. Full-range / delete / formal / empirical

| Gate | Result |
|---|---|
| C1/C2 invariance | PASS — CV 1.18% → 9.94×10⁻⁶ |
| C4 hold-out | PASS on INTRA_YEAR (`3.56×10⁻⁵`); multi-year OPEN |
| C3 spectral | COMPATIBLE / UNADJUDICATED |
| D4 | PENDING_DATA (record count OK) |

## 16. Classification

| Bucket | Iteration-2 update |
|---|---|
| Empirically surviving | still none newly earned |
| Empirically excluded | none |
| Formal defects | unguarded `c_far` (unchanged); wrong-center dataset incident recorded |
| Identities / LO approx | `shapiro_delay` still LEADING_ORDER |
| Calibrated | none introduced |
| Unadjudicated | solar spectral mechanism confirmation |
| Open mechanisms | multi-year invariant proof; endpoint sync; TRK-2-25 residual chain |
| Active discriminating | exact vs LO delay (WF too small); NS/horizon fork (prior) |
| Coverage gaps | admissible ranging residual; deflection vs b; whole-repo claim extraction |
| **IC recovery** | GOM25 instantaneous-ϟ debt → **RECOVERED** at investigation level |

## 17. Root-cause (seven questions)

Answered in `GOM26_ASSESSMENT.md` §17. Faulty premise was instantaneous elliptical sampling; repair freedom is DERIVED under two-body energy conservation.

## 18. Cascade ledger

| Item | Update |
|---|---|
| R1 solar coupled program | Spectral still UNADJUDICATED; IC debt closed at investigation level; delay PENDING_DATA |
| R3 GOM22 constructed delay | unchanged |
| R4 unguarded `c_far` | unchanged |
| Preferred solar `ϟ` for next tests | **1476.348 m** (GOM26 DERIVED), not instantaneous mean |

## 19–20. Reformulation / re-audit

Reformulation from GOM25 §19 executed and re-audited here. No further IC knob added.

## 21. Impact

Benchmarks/public claims must not cite EMPIRICALLY SURVIVES for solar redshift. Investigation records may cite invariant `ϟ` as DERIVED IC for subsequent shared-profile work pending canon propose-and-wait.

## 22. Next highest-value tests

1. Cassini SCE1 residual reconstruction (TRK-2-25 + geometry/clock) — still #1 for empirical delay.  
2. Multi-year Sun-centered Horizons C4 (closes INTRA_YEAR caveat).  
3. Deflection vs impact parameter with frozen GOM26 `ϟ`.  
4. Benchmark detox B15/B16/B25.

## Framework-level statement

This iteration does not conclude that SDT is true or false, nor that it matches or fails a competitor theory. It records that one stated initial-condition defect in the solar depth map has a DERIVED repair that survives its pre-registered formal and hold-out gates under an explicit Keplerian premise, while the spectral confirmation and Shapiro-like marker remain open.
