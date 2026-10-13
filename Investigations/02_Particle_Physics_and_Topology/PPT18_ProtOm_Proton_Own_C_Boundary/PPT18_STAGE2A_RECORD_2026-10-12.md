# PPT18 stage 2a: canon-consistent windings (2026-10-12)

**Registration:** `PROMPT.md` addendum 2026-10-12, written before the instrument.
**Instrument:** `ppt18_stage2a.cpp`.
- Compile attempt 1 failed: the namespace is `law_VI::topology`, not `topology`. Nothing ran, so it is not counted.
- Output: `ppt18_stage2a_results.txt`. V1 and V2 met.

## Result
Each winding is built from canon rules only: aspect R/a = √(q/p), filament envelope R + a = R_p_lock = 0.84124 fm, and v_P = c√(q/(p+q)).

| (p,q) | R (fm) | a (fm) | ring (C1) | **Ѻ_p (fm)** | Ѻ_p/R_p | z_p at contact | four tours (C2) |
|---|---|---|---|---|---|---|---|
| (2,3) | 0.463 | 0.378 | yes | **0.227** | 0.270 | 0.135 | no (flag) |
| (4,5) | 0.444 | 0.397 | yes | **0.221** | 0.262 | 0.131 | yes |
| (4,3) | 0.390 | 0.451 | **no**: R < a, a spindle, not a ring | 0.193 | 0.230 | 0.115 | yes |

**Findings**
1. **Once the untraced engine constants are removed, Ѻ_p hardly depends on the winding.**
   - The admissible rings give **Ѻ_p = 0.221–0.227 fm**, about a quarter of R_p, sitting about halfway in from the tour radius and inside the tube.
   - The (2,3) / (4,5) ruling moves Ѻ_p by only 3%.
   - The live engine's 0.018–0.025 fm (stage 1) came entirely from its untraced 0.06 fm strand: about 10× smaller than any canon-consistent value.
2. **(4,3) cannot be a ring under the canon aspect law.** "4 tours × 3 cross-section turns", the engine's description, read as a (4,3) torus knot, is excluded under this construction. Among four-tour windings, (4,5), the NSEQ16 braid pair, is the admissible one, but only with canon's aspect, not NSEQ16's registered sizes (stage 1, K2).
3. **The proton's own depth at contact is z_p ≈ 0.13**, against hydrogen's z_H = 1.675. The stage-1 robust result holds with traced geometry.

**Closeness to ħ/(m_p c) = R_p/4 = 0.2103 fm, explained (not evidence).**
- Ѻ_p/R = √(pq)/(p+q), which is ≤ ½, with equality at p = q.
- R/R_p = k/(1 + k), with k = √(q/p) close to 1.
- Both factors are near ½ for any near-equal p and q, so Ѻ_p ≈ R_p/4 holds **generically by algebra**. The (4,5) value is +4.9% from ħ/(m_p c); (2,3) is +7.9%.
- This is recorded as a construction item, not a coincidence.

## Status
| Item | Grade |
|---|---|
| Ѻ_p under canon rules | **G3: 0.221 fm for (4,5), 0.227 fm for (2,3)**. Conditional on two canon rules (aspect law, filament envelope) and on Harvey's winding ruling. |
| Exclusion of (4,3) as a ring | G4, computed |
| Contact-depth asymmetry | G4 |

**Still open (stage 2b).** A known answer not used in building the geometry, registered before computing.
- The proton moment is exposed (0.587 fm hand value). It is also shared-input for the engine geometry.
- The candidate observable left is the neutron (the stabled electron's seat inside this geometry). Its ledger is itself owed (SCT, FLM12).
- So stage 2b waits on Harvey's winding ruling and a choice of observable.

**Propose-only (Release not edited).** The live engine's H1 strand (0.06 fm) and helix length (5.28 fm) should be replaced with the canon-consistent (4,5) sizes: R = 0.444 fm, a = 0.397 fm. This would also remove the stage-1 rim overshoot (1.085 R_p).
