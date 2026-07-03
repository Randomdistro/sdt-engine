# RUN_LOG — NP21: Binding Curve as a Resistance Landscape (iron at the floor)

> Author: J. C. Harvey, Melbourne. Append-only during the run.
> Protocol: `Investigations/PROMPT_EXECUTION_PROTOCOL.md`. Prompt: `PROMPT.md` §⑩.

---

## Pre-Run Commitments — NP21  (frozen BEFORE any landscape/floor code runs)

- **Prompt completion target:** A (all four phases attempted, gated honestly).
- **Physics class hoped:** NATIVE **only if** the floor is geometric (no tuned exponent);
  honest fork stated up front → CONVERGENCE / CALIBRATED if a coefficient ratio or exponent
  has to be fitted to place the floor at iron.
- **CALIBRATED budget:** ≤ 1 (ONE overall scale weight that maps R̃ units → MeV, used for the
  plotting overlay ONLY; rank-correlation and floor-search are scale-invariant and use it not at all).
  ANY fitted EXPONENT, or MORE THAN ONE free coefficient ratio, pushes the result to Class C and is
  documented as such.

### Engine namespaces used (single source of truth)
- `sdt::nuclear::alpha_grammar(Z,A)` → `(n_d = 3Z−A−2, n_t = A−2Z, valid)` — piece inventory. NOT re-derived.
- `sdt::nuclear::natural_basis[287]` — the alpha-valid nuclide set to scan.
- `sdt::packing` presets → shell-closure map (tetra→He-4, oct→O-16, cube→Ca-40, cuboct→Fe-56).
- OBSERVED-TARGET: AME2020 `BINDING ENERGY/A` column, from the in-repo file
  `Investigations/04_.../APS03_.../mass_1.mas20.txt` (keV → MeV). Used as an anchor (its DATA), never its SEMF story.

> NOTE (from NP13_VERDICT): the constitutional `alpha_grammar` gives **Fe-56 = (n_d=20, n_t=4), σ=0.667**
> and **Ni-62 = (n_d=20, n_t=6), σ=0.538** — NOT the "5α+6d+6t, σ=0" written in PROMPT §4. The engine
> grammar governs (anti-creep). The PROMPT's σ figures for Fe/Ni are superseded by the engine values.

---

## FROZEN EXPONENT LEDGER  (binding contract — frozen 2026-07-01, before P2)

The trial functional (per nucleon), a resistance to be MINIMISED at the most-bound form:

```
R̃/A  =  − a_V · 1                              (bulk relief, per-nucleon constant)
        + a_S · A^(−1/3)                        (surface frustration, per-nucleon)
        + a_C · Z(Z−1) · A^(−4/3)               (handed-redirection spread, per-nucleon)
        + a_A · (n_t − n_d)^2 / A^2             (grammar asymmetry, per-nucleon)
```

| Term | Exponent(s) | Geometric source | TAG |
|------|-------------|------------------|-----|
| bulk relief | `A^1` total → `A^0` per-nucleon | every seated piece shares interior bonds ⇒ relief ∝ count of pieces ∝ A. Combinatorial. | **GEOMETRIC** |
| surface | `A^(2/3)` total → `A^(−1/3)` per-nucleon | surface area of a compact (≈spherical) packing ∝ (volume)^(2/3) ∝ A^(2/3); radius ∝ A^(1/3). Pure packing geometry. | **GEOMETRIC** |
| spread (ℓ=1 handed redirection) | pair count `Z(Z−1)` ÷ shell radius `A^(1/3)` → total `Z(Z−1)/A^(1/3)`, per-nucleon `/A^(4/3)` | number of proton-form pairs = C(Z,2); mutual redirection ∝ 1/separation ∝ 1/R ∝ A^(−1/3). Occlusion-law ℓ=1 term. | **GEOMETRIC** |
| asymmetry σ | `(n_t − n_d)^2 / A` total → `/A^2` per-nucleon | grammar imbalance; quadratic restoring in the (n_d,n_t) plane (NP13 metric). The **quadratic power is a modelling choice, not derived** — flagged below. | **GEOMETRIC exponents on A; the quadratic-in-(n_t−n_d) is ASSUMED (see honesty note)** |

**Exponent honesty notes (frozen):**
1. The A-exponents `{0, −1/3, −4/3, −2}` are all **geometric** — they follow from "compact packing ⇒
   R ∝ A^(1/3), surface ∝ A^(2/3)" and from per-pair / per-nucleon counting. These are the SAME powers
   the SEMF *happens* to use, but they are read here from packing geometry, not imported as fitted numbers.
   The SEMF **coefficients** (a_V≈15.8, a_S≈18.3, a_C≈0.71, a_sym≈23.2 MeV) are the fitted objects and are
   **NOT** used as inputs. They may appear only as an OBSERVED comparison.
2. **THE HARD PART, DECLARED NOW:** the floor location is set by the *ratios* a_S:a_C:a_A (and a_V sets
   scale only). SDT does **not** yet supply those ratios from first geometry. Therefore, to search the
   floor, I must either (a) leave the ratios free — which is exactly the fit the prompt forbids counting
   as a derivation — or (b) fix them by geometry. I will run BOTH:
   - **Run G (geometric-ratio):** fix a_S:a_C from the packing kissing-number / coordination geometry and
     set a_A by the grammar (unit weight, no tuning). Report where the floor lands with ZERO tuned ratios.
   - **Run F (fitted-ratio, honest fork):** allow the ratios to be fit to the AME curve, then report the
     floor. If the floor only reaches iron in Run F, the result is **CALIBRATED / Class C** — said plainly.
   PRE-COMMITMENT: a PASS at Class A requires the floor within ±2 in A of Fe/Ni **in Run G**, robust under
   ±10–20% perturbation of the geometric ratios. Anything that needs Run F is Class C.

- Forbidden retroactive changes: widen the ±2 floor window or the Spearman gate post-run; relabel a FITTED
  ratio/exponent as GEOMETRIC after seeing the floor; tune to place the floor then call it derived; use
  measured B/A as R̃ (IDENTITY-PASS); import SEMF coefficients / G / M / GM / quarks / ψ; write "charge radius".

---

## Phase thresholds (committed before run)
- **P1:** every exponent tagged (done above); ≤1 free scale coefficient; grammar+packing from engine; ledger frozen here.
- **P2:** −R̃/A rises to Z≈26 then falls (≤3 non-monotone steps from pairing); concave-down single broad peak; Spearman(−R̃/A, B/A) > 0.85.
- **P3:** floor argmin within ±2 in A of Fe/Ni window A∈[54,64]; STRONG (Class A) only if achieved in **Run G** (geometric ratios, 0 fitted) AND robust under ±10–20% perturbation.
- **P4:** Fe-56 & Ni-62 both within ±2 of floor; ordering stated vs measured B/A and σ; no re-tune of frozen coeffs.

---

## Phase gates & ADJ entries

### ADJ-001 — tooling: Python instead of C++ (2026-07-01)
- **Trigger:** PROMPT §Tooling explicitly allows `python3` for the per-nuclide landscape + floor search + CSV.
- **Response:** implemented `np21_landscape.py`. Grammar formulas mirror `sdt::nuclear::alpha_grammar`
  EXACTLY (n_d=3Z−A−2, n_t=A−2Z); the scan **domain** (natural_basis 287-row stable set) and the packing
  coordination number (kiss=12, cuboctahedron) are parsed/read straight from the engine headers, not re-listed.
- **Did NOT change:** any threshold; the whitelist; the frozen exponent ledger.

### ADJ-002 — AME2020 parser fix (2026-07-01)
- **Trigger:** first run produced corrupt B/A (e.g. Ca-49 → 0.0002 MeV); Spearman noise (−0.06). Positional
  token index broke on lines carrying an origin flag (`-n`,`-p`,`x`) before the mass-excess field.
- **Response (allowed — a parse/numerics fix):** anchor B/A on the beta-decay flag token (`B-`/`B+`); B/A is
  the token two positions before it. Verified Fe-56=8.7904, Ni-62=8.7946 MeV (match NP13 / AME2020).
- **Did NOT change:** the functional, exponents, ratios, or any pass/fail threshold.

### ADJ-003 — scan domain = engine natural_basis (valley of stability) (2026-07-01)
- **Trigger:** scanning ALL 3554 AME nuclides (incl. far-off-stability up to A=241) made the argmin noisy and
  physically wrong — the "iron floor" is a valley-of-stability statement. PROMPT §④ P2 says scan "alpha-valid
  **stable** nuclides Z=2…83".
- **Response:** restrict the landscape domain to `sdt::nuclear::natural_basis` (284 alpha-valid stable rows),
  parsed from `nuclear.hpp`. Full-AME behaviour retained in the ratio sweep for context.
- **Did NOT change:** exponents/ratios/thresholds. This SHARPENS the test in SDT's favour, not against it.

---

## PHASE GATE RESULTS

**P1 — PASS-GATE.** Functional written; every A-exponent tagged GEOMETRIC in the frozen ledger; grammar +
packing + domain pulled from the engine; one scale weight (a_V) reserved, ratios declared. Ledger frozen above.

**P2 — SHAPE: PARTIAL / conditional.**
- Run F (ratios least-squares-FITTED to AME): Spearman(−R̃/A, B/A) = **+0.907 > 0.85**, RMS = 0.203 MeV/n.
  Rise-then-fall reproduced — **but only with 3 fitted coefficients** (a CALIBRATED reproduction).
- Run G (geometric ratios, a_C = α, 0 fitted): Spearman = **−0.574** (WRONG SIGN). With the whitelist-only
  ratio the spread term never overtakes surface → monotone, NO rise-then-fall.
- **Gate call:** the *form* can reproduce the shape, but *not on geometric ratios*. Proceed to P3 with the
  Class explicitly capped at C (per §⑩: fitted reproduction caps at C). Logged as PARTIAL.

**P3 — FLOOR: FAIL of the geometric bar (the decisive phase).**
- Run G (0 fitted ratios): floor = **U-238**, |A_floor − 56| = **182**. Off iron by the whole chart.
- Ratio diagnostic: the floor is a pure function of a_C/a_S. Geometric guess = 0.0012; the ratio that even
  *approaches* iron ≈ 0.05 (→ Ca-48); **factor ~32 apart**. No ratio lands cleanly inside [54,64].
- Run F (fully fitted): floor = **Ca-48**, |A_floor − 56| = **8** — STILL outside the ±2 window even with a
  3-coefficient fit (the LSQ optimises global RMS, and this per-nucleon functional's stable-set minimum is Ca-48).
- Robustness: **0/45** perturbations of the geometric ratios put the floor in [54,64].
- **Gate call (pre-committed, §⑧ T1/T2):** floor far from iron with geometric exponents/ratios → **KILL the
  geometric-floor claim**; floor reaches the iron *region* only with fitted coefficients and even then misses
  ±2 → the landscape-as-shape is at best **CALIBRATED / Class C**, and the *derived iron floor* is **not paid**.

**P4 — Fe-56 vs Ni-62: consistent (single positive).**
- Pointwise R̃/A: Ni-62 (1.589) < Fe-56 (1.672) → landscape places **Ni-62 deeper**, matching measured B/A
  ordering (Ni-62 8.7946 > Fe-56 8.7904) AND σ ordering (Ni-62 more symmetric, σ=0.538 < 0.667). Both within
  ±2 of each other in A. No re-tune. This local ordering is consistent with NP13 — but it is a 2-point check,
  not the floor.

**NET:** Prompt completion **B** (all four phases executed and gated; strong outcome not reached). Physics class
**KILLED (geometric-floor claim) / CALIBRATED (landscape-as-shape, Class C)**. Matches FLM12 §D2 = OPEN. No RETRO-PASS.
