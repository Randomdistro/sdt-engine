# PPT18 stage 2b: Harvey's four-loop volume construction (2026-10-12)

**Registration:** PROMPT.md addendum (b), written before `ppt18_stage2b.cpp`. Single pass; V1–V3 met. Output `ppt18_stage2b_results.txt`. The fill-limit line was appended afterwards by a separate one-line calculation and is labelled so.

## Construction (reading A)
1. V_e = π b_e² · 4πa₀ (canon PPT17 closure tube).
2. V_p = 1836.15 V_e.
3. V_p is stretched into one strand making four toroidal loops, twined as a four-pass bundle (passes touching: a = √2 b), one poloidal traversal per loop.
4. Envelope: outer radius R_p_lock = 0.84124 fm (diameter 1.6825 fm).

## Results
- **Envelope capacity.** The four-loop ring bundle holds at most **1.675 fm³** (at R = a). The proton sphere is 2.494 fm³.
- **Canon's electron body b_e = 3.0e-20 m (OPEN) gives V_p = 3.45 fm³: it does not fit.** It exceeds the bundle's capacity by 2.06× and even the sphere's volume.
- **The largest b_e that fits is 2.09e-20 m.** Canon's open value is 1.44× too large for this construction.
- **Ѻ_p depends steeply on b_e:**

| b_e (m) | strand b (fm) | bundle a (fm) | R (fm) | v_P/c | Ѻ_p (fm) | z_p at contact |
|---|---|---|---|---|---|---|
| 1e-20 | 0.087 | 0.123 | 0.631 | 0.191 | 0.0045 | 0.0027 |
| 2e-20 | 0.208 | 0.294 | 0.339 | 0.656 | 0.127 | 0.075 |
| **2.09e-20 (fill limit, R = a)** | **0.220** | **0.311** | **0.311** | **0.707** | **0.155** | **0.092** |

## Readings (labels)
1. **Construction result (G4).** Under Harvey's rule, canon's open b_e cannot be right: the proton's volume would not fit its own boundary. **b_e ≤ 2.09e-20 m.**
2. **Candidate closure (not registered; for Harvey to rule).** If the four-loop bundle *exactly fills* the envelope (R = a, the tightest ring), the construction **fixes the electron's body radius at b_e = 2.09e-20 m from R_p and m_p/m_e alone.** Canon currently holds b_e as an open input. Then:
   - Ѻ_p = 0.155 fm;
   - the strand radius is 0.220 fm;
   - poloidal and toroidal paths are equal (v_P = v_T = c/√2, as for the electron's own (1,1) partition). That last point is algebra at R = a, not evidence.

   The "exact fill" condition is **my addition**, not part of Harvey's statement.
3. **Contact depth.** In every case that fits, z_p at contact is ≤ 0.09, against hydrogen's 1.675. The robust stage-1 finding still holds.
4. **Shared input.** The packing count is the measured mass ratio, so the construction cannot predict 1836 (PPT17's label carries over). It can fix **b_e** and **Ѻ_p**, which no measured input contains.

## Open (Harvey)
- **(i) Reading A or B.** Does "shrink outer diameter to 1.68" fix the cross-section before the ×1836 (B), or only the final envelope (A, computed here)?
- **(ii) The fill condition.** Does the twined bundle fill the envelope exactly? If so, b_e = 2.09e-20 m and Ѻ_p = 0.155 fm follow.
- **(iii) An independent check on b_e.** Canon's 3e-20 m came from the 1.2 mm/s locked-rotation argument. The two must be reconciled: one of them is wrong under this construction.

## Ruling (Harvey, 2026-10-12): the electron closure tube is 720° (two Bohr orbits, length 4πa₀)
- **Canon's PPT17 closure length stands, and so does the stage 2b computation as run.**
- **The one-orbit (360°) alternative is not used.** Under 360°, canon's b_e would nearly fill the bundle (fit limit 2.96e-20 m, 1.5% under canon's rounded 3e-20 m). That reading is rejected by the ruling, so the near-agreement is **not** entered as a coincidence. It is recorded here only so it is not rediscovered later as one.

**Consequence under 720°:**
- Canon's open electron body radius b_e = 3.0e-20 m overflows the proton envelope by 2.06×.
- The construction requires **b_e ≤ 2.09e-20 m**.
- With an exact fill, **b_e = 2.09e-20 m** and **Ѻ_p = 0.155 fm**.

**Canon conflict (propose-and-wait; nothing edited).** `law_VI::winding::r_electron_body_open = 3.0e-20` (from the 1.2 mm/s locked-rotation argument) is incompatible with Harvey's volume construction at 720°. Either the locked-rotation argument must be revisited, or the construction's envelope must change. Harvey's call.

**Still open:**
- (i) reading A (envelope fixed at the end; computed) against reading B (cross-section fixed before the ×1836);
- (ii) whether the bundle fills the envelope exactly.

## Superseding ruling (Harvey, 2026-10-12): halve the tube; one tour (stage 2b-r)
"Halve it. Just because it connects flipped over doesn't mean it does two tours."
- The 720° closure is a flip connection within **one** tour, so the tube is **2πa₀**.
- The entry above ("720° stands; the one-orbit reading is not used") is **superseded**. It is kept as written.

**Re-run** (`ppt18_stage2b_r.cpp`, output `ppt18_stage2b_r_results.txt`). V1–V3 met.
- **Canon's b_e = 3.0e-20 m gives V_p = 1.726 fm³, 1.030× the bundle's capacity (1.675 fm³).** The overflow is 3%, inside the rounding of canon's one-figure value.
- **Fill limit: b_e = 2.9555e-20 m**, 1.5% below canon's 3.0e-20 m.
- **At the fill limit:** Ѻ_p = 0.155 fm, strand radius 0.220 fm, bundle radius a = R = 0.311 fm, v_P = v_T = c/√2, z_p at contact 0.092. These are unchanged from stage 2b, because the fill geometry depends only on the envelope.

**Labels**
- **Construction result:** under the one-tour tube, the volume construction and canon's locked-rotation electron size are consistent to within canon's rounding.
- **Not counted as confirmation.** The one-orbit numbers were shown to Harvey before this ruling (post-seen). Canon's b_e has one significant figure. The "exact fill" condition is my addition, not Harvey's statement.
- **Entered as C-012** in the coincidence register, with these limits.
- **What would make it serious:** a derivation of b_e from the W = 1 geometry that uses neither the locked-rotation argument nor this fill, landing on about 2.96e-20 m.

**Canon (propose-and-wait):** PPT17's `electron_closure_length` = 4πa₀ is to become 2πa₀ under this ruling (comment: 720° orientation closure made within one tour). Downstream: `proton_tube_radius_from_packing` and B26's tube-radius line. The 6π⁵ count is unaffected. Nothing is edited.
