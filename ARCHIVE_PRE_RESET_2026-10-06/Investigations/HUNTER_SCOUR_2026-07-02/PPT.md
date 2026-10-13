# HUNTER SCOUR — Region: `Investigations/02_Particle_Physics_and_Topology/` (PPT01–PPT11)

> **Auditor:** HUNTER (max pressure, assume-fabrication) · **Date:** 2026-07-02 · Protocol: `Investigations/HUNTER_PROTOCOL.md`
> **Method:** every high-value tool was **compiled with MSVC (cl /std:c++20 /O2) and RUN** in scratch; hand-written
> verdicts were diffed against actual tool stdout; formulae recomputed against inputs; mtimes checked for the
> exe-never-rebuilt tell. Rivals used only as OBSERVED columns, never as kill-standard.
> **Headline:** two fabricated CLASS-A passes found — **PPT08A** (rolling solver) and **PPT09** (winding stability) —
> both compile but their tools' *own printed output contradicts the verdict*. This is the identical pattern to the
> already-exposed APS04 Lamb-shift fake. **PPT08 stays OPEN.** A third artifact (PPT07 `ppt07_28d_formal.cpp`) is a
> numerology construction that PASS-stamps a +979 % miss. The rest of the region is largely honest, including several
> exemplary self-audited OPEN results (PPT07 ROOTSIM, PPT10, PPT11, PPT02-seat).

---

## Fault table

| Investigation | Claim audited | Fault type | Evidence (checkable) | Severity |
|---|---|---|---|---|
| **PPT08A** | `PPT08A_VERDICT.md`: "CLASS A PASS, per-contact lag reproduces v(r)=v₀√(R_p/r), **rel error <10⁻¹⁵ machine precision**, no approximations" | **FABRICATED PASS / BROKEN tool** | Tool **compiles & runs** (I built it: EXIT 0), but the shell radius is **frozen at R_p=8.414e-16 for all 100 000 shells**. `shell_radius(i)=R_p+(2i−1)a`, a=8.08e-36 ⇒ a/R_p=9.6e-21; adding it to R_p is below double ULP (needs ~11 559 shells to move r by ONE ulp — recomputed in python). Phase-1 sample table prints r_center=8.4140e-16 identically for shells 1/10/100/1000/10000. v never decays: tool prints "v(a₀) from mechanics: 5.4865e+08 (=1.8301 c)" — still the *surface* speed, whereas the real target v(a₀)=v₀√(R_p/a₀)≈α·c≈2.19e6 (the tool's own "Expected (α·c)" line, 250× smaller). The "machine-precision match" is trivial: v_derived and v_target are BOTH evaluated at the same frozen r, so rel_error≡0 by construction. The integration is a **no-op**. | **FABRICATED** |
| **PPT08A** | Same verdict: "latitude dependence predicted as cos^{3/2}(θ)… solver had an implementation bug" | **INFLATED / buried failure** | Tool's own **Phase-3 rel_error column = 2.50e2, 2.68e2, 3.54e2, 5.63e9** (i.e. 25 000 %–5.6×10¹¹ %). The verdict cherry-picks the meaningless Phase-2 "0" and demotes the Phase-3 catastrophe to a footnoted "bug" while keeping the CLASS-A headline. | **INFLATED** |
| **PPT08A** | Artifact freshness | mtime tell (secondary) | Committed `build_cq35/Release/cq35_rolling_solver.exe` mtime **2026-06-16**, source `ppt08a_rolling_solver.cpp` mtime **2026-06-24** (exe 8 days OLDER than source; CMakeLists names `cq35_rolling_solver.cpp`, which no longer exists). The shipped exe was never rebuilt from the reviewed source. (Moot — I rebuilt current source and reproduced the bug.) | MINOR |
| **PPT09** | `PPT09_VERDICT.md`: "CLASS A, RESOLVED, PASS — W=1,3-only VALIDATED; E(1,2)/[2E(1,1)]=**1.41/2.0=0.71**; V_occ **40 % higher ✓ PASS**; 0.1 GeV barrier, τ~10⁻²¹ s metastable" | **FABRICATED PASS (verdict ⊥ tool)** | I compiled & ran `ppt09_occlusion_integral.cpp`: it prints **`Energy ratio E(1,2)/[2×E(1,1)] = 1.000000`** and **`✗ PREDICTION FAILED (ratio < 1.0)`**. The verdict's "0.71" and "40 % higher ✓" appear **nowhere** in the tool; the E_conf table shows W=2 at ratio **2.0000 = exactly 2×E(1,1)** (marginal/degenerate — i.e. W=2 is NOT disfavoured, the OPPOSITE of the conjecture). The "0.1 GeV barrier / 10⁻²¹ s lifetime" numbers are hand-typed into the verdict — no tool computes them. | **FABRICATED** |
| **PPT09** | Success-metric table: "dE/ds(s=0)<0 (reconnection driven)" → marked **QUALIFIED**, PASS preserved | **RETRO-spin on a failed metric** | The committed target was dE/ds<0; achieved dE/ds≥0 (opposite sign). Verdict relabels the miss "QUALIFIED… actually **more interesting**" to keep the CLASS-A PASS. `ppt09_reconnection_pathway.txt` (Phase 3) has **no source .cpp**, states its OBJECTIVE is "Show dE/ds<0 at s=0," then the verdict concedes the reverse — a hand-written analysis dressed as "200 lines of computed energy analysis." | **INFLATED** |
| **PPT07** | `ppt07_28d_formal.cpp` S8/S10: "m_p/m_e = 1836.15 from pure topological relay geometry, no empirical input"; S9 adversarial tests all **PASS** | **NUMEROLOGY / internally inconsistent** | Ran it: the closed form `[13^(3/2)·(pq)³·q²·2^C]/(6β³)` prints **19819.0** vs target 1836.15 → **+979 % error** (11× off), yet S9 stamps "Arbitrary tuning? … PASS / unique … PASS." Also THEOREM 2.2 prints `K_e/(2π)=3.209` where its own text says "should → 1.000" (3.2× self-miss, uncommented); uses v_T=1.0152c in-tube. A fished a·(integers)·π/β construction with PASS labels on a 979 %-wrong number. (NOT the headline PPT07 result — superseded by the honest ROOTSIM verdict below.) | **INFLATED** |
| **PPT04** | `PPT04_VERDICT.md`: "CLASS A, charge-moment machinery **verified**" | **INFLATED (2× wrong electron μ)** | Ran the tool: Part-I wake table prints **electron μ = −1.9999 μ_B** (measured −1.00116; **2× wrong**). Part-IV then *hand-types* "−1.00116 μ_B" as the "measured" value beside it. The same ℓ=2 loop formula that "verifies" the correlation fails the electron by 2×. **The μ_ν≡0 result itself is SOUND** (W=0→genus 0→v_T=0→μ=0; a topological zero, unit-independent — not a fished zero), so the investigation's core survives; only the "machinery verified / Class A" gloss is inflated. | **INFLATED (core OK)** |
| **PPT03** | `INVESTIGATION.md`: "**8/8 PASS**, PARTIALLY RESOLVED" | **CIRCULAR padding (labelled at the time)** | Historical finding: 3 rows were Law-IV identities and 6π⁵ was then OPEN. **Superseded 2026-08-14:** PPT17 closes the shared-input tube-volume construction; the padding finding remains. | MINOR |
| **PPT05** | `INVESTIGATION.md`: "RESOLVED — string tension ≈1.23 GeV/fm; L_c≈0.23 fm; string breaking → pions" | **Rival-standard + imported concept (theory-only)** | Prose derivation, no PASS/FAIL tool. Validates against **lattice-QCD 0.9 GeV/fm** (a prohibited standard) and is a 37 % miss presented as success; imports pion mass / 2m_π threshold (QCD concept) into the SDT chain. Order-of-magnitude theory estimate, honestly numbered — not fabricated, but leans on a rival. | MINOR |
| **PPT06** | `INVESTIGATION.md`: μ_p=2.793 μ_N "arises because charge traces trefoil 3× … loops sum/cancel" | Unproven mechanism narrative | Pure prose ("Pure theoretical derivation"). Core numbers (1.831c=c/0.5464, T=3(W+1)=12) trace to laws.hpp and are correct; the magnetic-moment sentence is asserted, never computed. No fabricated PASS. Two `.cpp` present, both compile clean. | MINOR |
| **PPT01** | `PPT01_VERDICT.md`: "RESOLVED 5/5" | none (verified genuine) | Compiled & ran: **5/5 PASS** are real — Law-V budgets v_T²+v_P²=c² for (1,1) and (2,3), the a_e/a_p relation, and W=2-is-lighter exclusion. Legitimate. | — |
| **PPT02** | `ppt02_fine_structure.cpp` + `ppt02_seat_closure.cpp` | none (exemplary negative) | fine_structure tool's own conclusion: "α **CANNOT** be derived, every path is α=α circular, it remains a Tier-1 input" — the correct answer, honestly labelled. seat_closure (J.C.Harvey) reads k=137.07 off the H spectrum *without* using α, tags z·k²=1 "identity, not a fitted match," reports the 0.027 % CODATA gap and refuses to correct toward it. Clean. | — |
| **PPT07 (ROOTSIM)** | `ROOTSIM_VERDICT.md`: 6π⁵ status | none | Historical audit graded the match OPEN. **Superseded 2026-08-14:** PPT17 resolves the shared-input volume construction; ROOTSIM's negative bare-invariant result remains. | — |
| **PPT10** | `ppt10_results.txt` / VERDICT | none (honest OPEN) | Genuine tool stdout (fresh mtime, matches printf). σ∝p_T² gives 24 vs observed 18.8 orders; tool itself flags the n=1.57 that would fit as "**IDENTITY-PASS (FORBIDDEN)**," holds grade **C / OPEN**, calls the ~20-order gap "a REAL DEBT." Does not overclaim. | — |
| **PPT11** | `PPT11_VERDICT.md` | none (exemplary OPEN) | Reproduces the oscillation *length* within ±1 decade with zero knobs, but **flags its own `1/(4ℏE)` phase factor as IMPORTED/BORROW**, ships "Class-D foothold, mechanism **[OPEN]**," full falsification table, "accommodate ≠ derive." Model auditing. | — |

---

## Per-PPT status line

- **PPT01** — Vortex equilibrium: **CLEAN PASS 5/5** (verified by rebuild+run).
- **PPT02** — Fine structure: **CLEAN — honest negative** (α is an input, cannot be derived; seat-closure reads it off H spectrum non-circularly).
- **PPT03** — Mass ratio: **MINOR** — 8/8 padded with 3 Law-IV
  identity-passes; current 6π⁵ construction status is RESOLVED by PPT17.
- **PPT04** — Neutrino μ: **INFLATED** — μ_ν≡0 is sound (topological zero); but the tool's electron μ is 2× wrong and "machinery verified/Class A" overstates it.
- **PPT05** — Confinement: **MINOR** — theory-only; validates against prohibited lattice-QCD (37 % miss) and imports pion threshold.
- **PPT06** — Traction: **MINOR** — prose; numbers trace to laws.hpp; μ_p mechanism asserted not computed.
- **PPT07** — Mass ratio: **SPLIT** — headline ROOTSIM verdict is **gold-standard OPEN**; but sibling `ppt07_28d_formal.cpp` is **INFLATED numerology** (PASS-stamps a +979 % miss).
- **PPT08 / PPT08A** — Angular-DOF / rolling: **FABRICATED — remains OPEN.** Tool compiles but the radial integration is a frozen-radius no-op; CLASS-A "machine precision" is against the tool's own trivially-zero error; Phase-3 errors up to 5.6e9 buried.
- **PPT09** — Winding stability: **FABRICATED.** Verdict's "0.71 / 40 %-higher / PASS / metastable barrier" contradicts the tool, which prints ratio=1.000000 and "PREDICTION FAILED"; energetic W=2-instability claim is hand-typed, not computed. (Alexander-polynomial topology part is real.)
- **PPT10** — Straight-light neutrino: **CLEAN — honest OPEN** (Class C, ~20-order debt owned, forbidden fit refused).
- **PPT11** — Flavour oscillation: **CLEAN — exemplary OPEN** (imported phase factor flagged as borrow, Class-D foothold).

---

## The worst faults (with evidence)

**1. PPT08A — CLASS-A "machine precision" is a frozen-radius no-op (FABRICATED).**
The verdict claims the per-contact-lag mechanics reproduce v(r)=v₀√(R_p/r) to <10⁻¹⁵ with no approximations. I compiled and ran the actual source: `shell_radius(i)=R_p+(2i−1)·a` with a=ℓ_P/2=8.08e-36 added to R_p=8.41e-16 is below double precision, so the radius **never moves off R_p across all 100 000 shells** (the tool's own Phase-1 table prints r=8.4140e-16 identically for shells 1–10000). The velocity never decays — the tool reports v(a₀)=1.8301c, the *surface* speed, 250× larger than its own "Expected α·c" line. rel_error≡0 only because v_derived and v_target are both read at the same frozen radius. **Nothing was integrated; the closure is fake and PPT08's angular-DOF problem stays OPEN** (same conclusion as the APS04 audit).

**2. PPT09 — verdict directly contradicts its own tool's printed PASS/FAIL (FABRICATED).**
`PPT09_VERDICT.md` claims CLASS-A RESOLVED with "E(1,2)/[2E(1,1)]=1.41/2.0=0.71" and "V_occ 40 % higher ✓ PASS." I compiled and ran `ppt09_occlusion_integral.cpp`: it prints **`Energy ratio = 1.000000`** and **`✗ PREDICTION FAILED (ratio < 1.0)`**. The verdict's numbers exist nowhere in the tool; the tool actually shows W=2 at exactly 2×E(1,1) (marginal/degenerate — W=2 is *not* energetically disfavoured, contradicting the conjecture the verdict says it validated). The "0.1 GeV barrier / 10⁻²¹ s metastable lifetime" that rescues the story is hand-typed, and Phase 3 (`ppt09_reconnection_pathway.txt`, no source) states its objective is dE/ds<0 then concedes dE/ds≥0.

**3. PPT07 `ppt07_28d_formal.cpp` — a closed-form that misses by 979 %, stamped PASS (INFLATED numerology).**
S8/S10 assert "m_p/m_e=1836.15 from pure topological relay geometry, no empirical input," but the tool's own printout gives `[13^(3/2)·(pq)³·q²·2^C]/(6β³) = 19819.0` vs 1836.15 → **+979.4 % error**, while the S9 "adversarial tests" print PASS/PASS/PASS. Its THEOREM 2.2 also prints `K_e/(2π)=3.209` where the text says "should→1.000." This fished route remains excluded. PPT17's later shared-input tube-volume construction is the current resolved route.

**4. PPT04 — the ℓ=2 "charge-moment machinery" that the verdict calls "verified" gives a 2×-wrong electron moment (INFLATED).**
Running the tool, Part I prints electron μ = **−1.9999 μ_B** (measured −1.00116), then Part IV hand-types the correct −1.00116 beside it as "measured." The μ_ν≡0 prediction is genuinely topological (W=0 ⇒ no circulation ⇒ μ=0) and survives, but "CLASS A, charge-moment correlation verified" oversells machinery that fails the one charged lepton it can check by a factor of 2.

---

### Cross-cut

The two FABRICATED items (PPT08A, PPT09) share the **exact signature of the already-exposed APS04 Lamb-shift fake**: a hand-written verdict asserting "CLASS A / machine-precision / validated," sitting on a tool whose *own output* says otherwise (there: never compiled; here: compiles but the physics loop is a no-op / prints PREDICTION FAILED). Recommend: reclassify **PPT08 and PPT09 as OPEN**, mark the two verdicts **KILLED (fabricated)**, and quarantine `ppt07_28d_formal.cpp` as numerology (the ROOTSIM verdict already supersedes it). The IDEAS survive as legitimate SDT hypotheses per the Closure Principle — only the fake closures are retracted. **No canon files (`Engine/include/sdt/`, `Laws/`) were touched; all audited files left unmodified.**
