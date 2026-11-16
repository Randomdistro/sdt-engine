# NP21 — Derivation: The Binding Curve as a Resistance Landscape

> Author: J. C. Harvey, Melbourne. Tool: `np21_landscape.py`. Engine: `sdt::nuclear`, `sdt::packing`.
> Every step tagged: `DERIVED` / `ASSUMED` / `IDENTITY` / `CALIBRATED(n)` / `OBSERVED-TARGET`.

## 1. The unit of account (inherited from NP19)

**`R(form) ≡ m(form) c²`** — a form's rest energy *is* its accumulated form-resistance (Law IV read
as resistance; shown constant-free in NP19). A mass defect is `ΔR = R(constituents) − R(bound)`, so the
binding energy per nucleon is the per-nucleon *resistance relief* of assembling the form:

> `B/A(Z,A) = [ Z·R(p) + (A−Z)·R(n) − R(nuclide) ] / A`   — **IDENTITY** (this is just B/A in
> resistance language; it is NOT the test).

The **test** is whether an SDT-side functional `R̃(Z,A)` built from grammar + packing *geometry*
reproduces the shape and, decisively, **locates the floor at iron** without importing the measured B/A
and without a fitted exponent.

## 2. The geometric functional and its frozen exponent ledger

Per nucleon, a resistance to be **minimised** at the most-bound form:

```
R̃/A  =  − a_V · 1                          (bulk relief; per-nucleon constant)
        + a_S · A^(−1/3)                    (surface frustration)
        + a_C · Z(Z−1) · A^(−4/3)           (handed-redirection spread, ℓ=1 occlusion term)
        + a_A · (n_t − n_d)^2 / A^2         (grammar asymmetry, NP13 metric)
```

with `(n_d, n_t)` from `sdt::nuclear::alpha_grammar`: **`n_d = 3Z − A − 2`, `n_t = A − 2Z`** — `DERIVED`
(engine, not re-derived).

**Frozen exponent ledger** (committed in `RUN_LOG.md` before any floor search):

| Term | A-exponent | Geometric justification | TAG |
|------|-----------|-------------------------|-----|
| bulk relief | `A^0` per-nucleon | every seated piece shares interior bonds ⇒ relief ∝ count ∝ A | **GEOMETRIC** (`DERIVED`) |
| surface | `A^(−1/3)` per-nucleon | compact packing ⇒ surface ∝ (volume)^(2/3) ∝ A^(2/3); R ∝ A^(1/3) | **GEOMETRIC** (`DERIVED`) |
| spread ℓ=1 | `Z(Z−1)·A^(−4/3)` | proton-form pair count C(Z,2), mutual redirection ∝ 1/R ∝ A^(−1/3) | **GEOMETRIC** (`DERIVED`) |
| asymmetry | `(n_t−n_d)²/A²` | grammar imbalance; **quadratic power is `ASSUMED`**, A-scaling geometric | **GEOMETRIC A-scaling; quadratic ASSUMED** |

The A-exponents `{0, −1/3, −4/3, −2}` are read from *packing geometry* (compact-sphere radius/area laws +
per-pair counting). They coincide with the powers the semi-empirical mass formula (SEMF) uses, but they
are **not imported as fitted numbers** — the SEMF's fitted **coefficients** (`a_V≈15.8, a_S≈18.3,
a_C≈0.71, a_sym≈23.2 MeV`) never enter the SDT chain; they appear only as an `OBSERVED` comparison.

## 3. The crux, stated before the run: the floor is a *ratio*, and the ratio is not derived

Because `a_V` is an A-independent additive constant, it **cannot move `argmin R̃/A`**. The floor location
is therefore set *entirely* by the ratios **a_S : a_C : a_A** (dominantly `a_C/a_S`, since along the valley
of stability `Z ≈ A/2` makes the spread term rise as `~A^(2/3)` while surface falls as `A^(−1/3)` — their
crossover *is* the floor).

SDT does **not** yet supply `a_C/a_S` from first geometry. Two runs were therefore pre-committed:

- **Run G (geometric ratio, 0 fitted):** `a_S = kiss/2 = 6` (cuboctahedron coordination 12 from
  `packing::preset_cuboct12`), `a_C = α` (the single derivation basis redirection constant), `a_A = 1` (grammar
  unit). — `DERIVED`-attempt.
- **Run F (fitted ratio, honest fork):** `a_V, a_S, a_C, a_A` least-squares-fit to the AME B/A curve. —
  `CALIBRATED(3)`; anything it enables is Class C.

## 4. Results (from `np21_landscape.py`, scan domain = engine `natural_basis`, 284 alpha-valid stable rows)

### 4.1 Shape (P2)
- **Run F (fitted):** Spearman(−R̃/A, B/A) = **+0.907** (> 0.85 gate); RMS(model, AME) = **0.203 MeV/n**.
  Rise-then-fall reproduced — **only with 3 fitted coefficients** → `CALIBRATED(3)`.
- **Run G (geometric):** Spearman = **−0.574** (WRONG SIGN). With `a_C = α` the spread term is ~100× too
  weak to overtake surface, so R̃/A is monotone — **no rise-then-fall**. — `COMPUTED`.

### 4.2 Floor (P3) — the decisive test
- **Run G (0 fitted):** floor `argmin R̃/A` = **U-238**, `|A_floor − 56| = 182`. Off iron by the whole chart.
  — `DERIVED` (and it lands nowhere near iron).
- **Ratio diagnostic:** the geometric guess `a_C/a_S = 0.0012`; the ratio that *approaches* iron is `≈ 0.05`
  (→ Ca-48); the SEMF's `a_C/a_S ≈ 0.039` (`OBSERVED` comparison). The geometric guess is a **factor ~32**
  from the value needed. No single ratio lands the floor cleanly inside the pre-committed window `[54,64]`.
- **Run F (fully fitted):** floor = **Ca-48**, `|A_floor − 56| = 8` — **still outside the ±2 window** even
  with a 3-coefficient fit (LSQ minimises global RMS, not floor placement; this per-nucleon functional's
  stable-set minimum sits at Ca-48). — `CALIBRATED(3)`.
- **Robustness:** **0 / 45** perturbations of the geometric ratios put the floor in `[54,64]`. — `COMPUTED`.

### 4.3 Fe-56 vs Ni-62 (P4) — the one consistent sub-result
Pointwise `R̃/A`: Ni-62 = 1.589 < Fe-56 = 1.672 → the landscape places **Ni-62 deeper**, which matches
both the measured B/A ordering (Ni-62 8.7946 > Fe-56 8.7904 MeV) **and** the σ ordering (Ni-62 more
symmetric, σ = 0.538 < 0.667). Consistent with NP13. But this is a two-point ordering, not the floor.
— `COMPUTED` / consistent-with-`OBSERVED-TARGET`.

> Grammar note (supersedes PROMPT §4): the constitutional `alpha_grammar` gives **Fe-56 = (20,4), σ=0.667**
> and **Ni-62 = (20,6), σ=0.538** — NOT "5α+6d+6t, σ=0". The engine grammar governs (NP13, anti-creep).

## 5. Why iron is *asserted* here, not *derived* — the mechanism narrative and its gap

The intended mechanism: bulk relief saturates as the cuboctahedral (Vector-Equilibrium) shell closes near
Fe-56; beyond it, the handed-redirection spread (∝ Z²) and triton-excess asymmetry take over, and their
crossover with the falling surface term **is** the floor. The functional form encodes exactly this
competition — and *with fitted coefficients it does reproduce a rise-then-fall*. **But the crossover
location is a coefficient ratio, and SDT supplies no geometric derivation of that ratio.** The derivation basis
constant `α` (the natural first guess for the redirection weight) is ~32× too small. Placing the floor at
iron requires the SEMF-scale ratio, i.e. **a fit** — which is precisely the outcome flagged as
CALIBRATED, not derived, in the frozen ledger and in FLM12 §D2.

## 6. Ledger of claims

| Claim | Status | Tag |
|-------|--------|-----|
| B/A ≡ per-nucleon resistance relief | trivially true | `IDENTITY` |
| A-exponents `{0,−1/3,−4/3,−2}` are geometric (packing) | holds | `DERIVED` |
| Functional form can reproduce rise-then-fall | yes, with 3 fitted coeffs | `CALIBRATED(3)` |
| **Iron floor from geometry (no fitted exponent/ratio)** | **fails** (U-238; ratio 32× off) | **KILLED** |
| Iron floor with fitted coefficients | approached (Ca-48) but misses ±2 | `CALIBRATED(3)`, un-paid |
| Ni-62 deeper than Fe-56 (fine ordering) | consistent w/ B/A & σ | `COMPUTED` (2-pt) |

**Bottom line:** the *reframe* (whole curve = one resistance landscape) is native and the functional's
**exponents** are geometric, but the **iron floor is not derived** — it lives in an un-derived coefficient
ratio. This is a **CALIBRATED landscape with a KILLED geometric-floor claim**, exactly the OPEN item
FLM12 §D2 houses. Honest FAIL of the hard bar; no fit is dressed up as a derivation.
