# CR15 — The Ionisation Trilemma and the Cold Dense Past

**Pre-registration. Written before the instrument exists (§3.1).**
Author: J.C. Harvey, Melbourne. Category 07 — Cosmology and Redshift. Opened 2026-07-30.
Object: *Spation Dynamics Theory — Cosmological Sector, Complete Mathematical Formulation*
(Harvey, 2026-07-30), PENDING items (1), (2), (5); Propositions 4, 5, 11, 13; postulates P5, P6.
Predecessor: `CR14_Ionisation_Balance_and_the_Clearing_Rung` (R2+R3 fired; Branch E open).

## Why this is not a re-run of CR14

CR14 tested a static vessel with `n_b` **constant** — "no expansion, so no dilution" — and found
the vessel optically thin by 62.8×. The document supersedes that assumption in two places, and
both must be honoured:

- **Prop 13** derives `r(t) ∝ 1/N` for coasting matter: physical separations were *smaller* in the
  past even though space is static, so `n_b ∝ N³`. Matter dilutes by **coasting**, not by
  expansion. CR14's Branch B used the wrong density law and its Branch E objection may not stand.
- **Prop 5** asserts binding energies *and* radiation quanta both scale as `N⁻²`, so their ratio
  is epoch-invariant and **no thermal trigger for recombination exists**.

Prop 5 is the sharper claim, because it collides with **P6** (`T_N = N·T₀`). If the local bath
temperature rises as `N` while binding energies fall as `N⁻²`, the ratio `B/k_BT` runs as `N⁻³`
and a thermal trigger exists after all — just in the wrong place. That collision is the object.

## The trilemma to be decided

Three propositions, any two of which force the third false:

- **(i)** `E_b(N) ∝ N⁻²` — Prop 5 / P5, derived from P4 plus quadratic energy.
- **(ii)** `T_local(N) = N·T₀` — P6, read as a **local** background temperature.
- **(iii)** The bath is thermal at `T_local`, and ionisation equilibrium places the transition at
  the epoch we identify with the CMB, `N = 1100` (Prop 4, Prop 11).

## Tests, with thresholds fixed now

- **T1 — arithmetic audit.** Independently recompute every `[D]`-tagged number in Parts VI, VII,
  VIII, IX: `N_max`, `v_min`, `T_max`, `ρ_s`, `P_min`, `T_end`, `v_dec`, `t_lb(1100)`,
  `t_lb(N_max)`, `D_CMB`, BAO `u_r`, `τ_now`. **PASS** = reproduces the stated value to its
  quoted precision. Any mismatch is reported as an arithmetic defect regardless of how minor,
  and its load-bearing consequences traced.
- **T2 — the trilemma, legs (i)+(ii).** Solve the full Saha balance with `B(N) = B₀/N²`,
  `T(N) = T₀N`, `n_b(N) = n_b₀N³` for the half-ionisation epoch.
  **Registered:** lands within ±10 % of N = 1100 ⟹ (i) and (ii) are jointly consistent with the
  CMB identification and the trilemma dissolves. Outside ±10 % ⟹ the trilemma is real and
  exactly one leg must be withdrawn; the finding is which.
- **T3 — the Prop 5 reading.** Take Prop 5 at face value: bath quanta track atoms, so
  `T_local ∝ N⁻²` and `B/k_BT` is epoch-invariant. Compute `x_e(N)` with `n_b ∝ N³`.
  **Registered:** if `x_e` is monotonically *decreasing* in `N` (more neutral toward the past),
  then **no ionised era exists**, there is no recombination event to trigger, the CMB cannot be a
  last-scattering surface, and `z_rec`/`T_rec` must leave `laws.hpp`'s `measured` namespace.
  If `x_e` rises toward the past, Prop 5 supports a conventional plasma era and this leg passes.
- **T4 — CR14 correction.** Rerun CR14's Branch B with Prop 13's `n_b ∝ N³`.
  **Registered:** if it reproduces the ΛCDM comparator (z ≈ 1379) and `τ ≫ 1`, then **CR14's
  Branch E optical-depth objection is WITHDRAWN** and recorded as withdrawn. This criterion is
  registered against my own prior result before it is run.
- **T5 — the bridge exponent owed.** Granting a constitutive bridge `n ∝ P^s = N^{4s}`
  (PENDING 1), solve for the `s` that places the transition at N = 1100 under whichever reading
  survives T2/T3. Output is a falsifiable target for PENDING (1).

## Instrument

The Saha solver validated in CR14 (V1 limits, V2 known answer z = 1379.3 vs textbook ≈ 1370,
V3 analytic-vs-numerical sensitivity agreeing to 0.0000 %). **All three gates are re-run here**;
no branch result is reportable if any fails (§3.2). Pure hydrogen; helium and the Peebles
non-equilibrium correction remain out of scope, declared here.

## Contraband check, against myself (§G mirror)

CR14's R4 stands: Saha is imported statistical mechanics, legal in its inputs, unearned in its
derivation. Nothing here may be labelled DERIVED on SDT's behalf. But the use is legitimate and
*different* from CR14's: T2 and T3 use Saha only to test **internal consistency between two of
the framework's own postulates**, not to adjudicate SDT against ΛCDM. A framework's own derived
laws are legal inputs to its own chains (§3.7), and an internal contradiction found with imported
machinery is still a contradiction, because both legs are the framework's.

**Registered limit on what a T2/T3 failure may conclude:** it falsifies a *combination* of P5,
P6 and the CMB identification. It does **not** by itself falsify the vessel, the pressure ladder,
or the redshift derivation of Part V, none of which are under test here.

## Expected trap, named in advance

T2 will produce some `N` well below 1100. `1100^{1/3} ≈ 10.3` sits near the observed reionisation
epoch (z ≈ 6–10). Any such proximity is **numerology and must not be reported as a match** —
the cube root of an imported number carries no physics.

## Deliverables

`cr15_trilemma.py`, `cr15_results.txt`, `CR15_ASSESSMENT.md`.
