# CR14 — Assessment: Ionisation Balance and the Clearing Rung

> **⚠ PARTIAL WITHDRAWAL 2026-07-30 (same day), by `CR15_Ionisation_Trilemma_and_the_Cold_Dense_Past`.**
> **Branch E is WITHDRAWN.** Branch B assumed `n_b = const` on the reasoning "static space,
> therefore no dilution". That is the wrong density law: Prop 13 of the SDT cosmological-sector
> formulation derives `r(t) ∝ 1/N` for coasting matter, so `n_b ∝ N³` **without** expanding space —
> matter dilutes by coasting. With the correct law the vessel is optically **thick**
> (τ = 4.19×10⁷, not 0.0159), a scattering surface does form, and the "optically thin by 62.8×"
> objection does not stand. The error was in this assessment, not in the framework.
> **What survives unchanged:** R2 (the rung is not reproduced; `z_rec` stays MEASURED-INPUT),
> R3 (the ~3000 K recovery is log-degenerate at ~2 %/decade and is evidence for nobody), R4 (Saha
> is imported machinery), the validated instrument, and the Branch C/D numbers. R3 in fact
> **tightens**: with Prop 13 the corrected branch is numerically *identical* to ΛCDM in this
> sector, not merely indistinguishable. See `CR15_ASSESSMENT.md` §T4.

**Classification: R2 + R3 fire — [DEGENERATE] on the recombination temperature; the
Clearing rung N = 1100 is NOT reproduced by the vessel.**
Author: J.C. Harvey, Melbourne · Tool: `cr14_saha_ladder.py` · Output: `cr14_results.txt`
Pre-registration: `PROMPT.md` (written before the instrument; criteria R1–R4, gates V1–V3).
Date: 2026-07-30.

## What was asked

`laws.hpp:166–167` carries `T_rec = 3000.0` and `z_rec = 1100.0` in the `measured`
namespace. Neither is an instrument reading. The claim under test was that the temperature
ladder `T_N = N·T₀` *recovers* recombination — so the ladder's N = 1100 had to be earned from
the vessel's own density behaviour rather than borrowed from ΛCDM's.

## Instrument validation (all gates PASS, §3.2)

| Gate | Test | Result |
|---|---|---|
| V1 | limits: `x_e → 1` at 10⁵ K, `x_e → 0` at 10³ K | PASS |
| V2 | **known answer** — ΛCDM Saha half-ionisation | **z = 1379.3** vs textbook ≈ 1370 (window 1250–1450) PASS |
| V3 | two-route sensitivity, analytic vs numerical | 0.015492 vs 0.015492, deviation **0.0000 %** PASS |

V2 was deliberately set against z ≈ 1370, the Saha half-point — *not* z ≈ 1090, which is the
last-scattering surface from the full non-equilibrium calculation. Validating against 1090
would have been validating against the wrong known answer.

## Results

| Criterion | Branch | n_b [m⁻³] | T_half [K] | N = T/T₀ |
|---|---|---|---|---|
| x_e = 0.5 | A — ΛCDM, n_b ∝ (1+z)³ | 6.61×10⁸ | 3762.0 | 1380.3 |
| x_e = 0.5 | **B — SDT static vessel** | 2.51×10⁻¹ | **2504.2** | **918.8** |
| x_e = 0.1 | A / B | 5.05×10⁸ / 0.251 | 3439.0 / 2364.7 | 1261.8 / 867.6 |
| x_e = 0.01 | A / B | 3.73×10⁸ / 0.251 | 3110.4 / 2212.2 | 1141.2 / 811.7 |

**R1 does not fire.** The static vessel places half-ionisation at **N = 918.8**, 16.5 % away
from the imported 1100 — outside the pre-registered ±10 %.

**R2 fires.** `z_rec` remains MEASURED-INPUT. The reproduction of 2998 K is **CALIBRATED(1)**:
one imported number, now documented as imported.

**R3 fires, and outranks R1.** The two branches disagree by **9.4 orders of magnitude in
density** and by only a **factor 1.502 in temperature**. The measured logarithmic sensitivity is

```
d ln T_half / d ln n_b  =  1 / (3/2 + B/k_B T)  =  0.0155 (branch B), 0.0230 (branch A)
```

— about 2 % per decade of density. Branch D confirms it across 20 orders of magnitude of
`n_b` (10⁻⁶ … 10¹⁴ m⁻³): `T_half` moves by a factor of only 2.465, mean sensitivity 0.0196.

**This is the finding.** The recombination temperature is set by hydrogen's binding energy
(θ = B/k_B = 157 887 K) divided by a logarithm, and the logarithm barely moves. Any framework
holding B = 13.6 eV and *any* density within tens of orders of magnitude lands near
2000–4000 K. Recovering ~3000 K therefore cannot discriminate the vessel from ΛCDM — **and
may not be cited as evidence for pressurised space.** The pressure law `P_N = N⁴·P₀` never
enters the calculation at all; deleting `P₀` leaves every number in the table unchanged.

**R4 stands unconditionally.** The Saha phase-space factor counts states in ℏ³ cells —
imported statistical mechanics. Its inputs (`m_e`, `k_B`, `ℏ`, `Ry_eV`) are derivation basis-legal;
its derivation is not SDT's. Nothing here is labelled DERIVED. Running the identical solver on
both density laws is legal precisely because the instrument's provenance then cancels: only the
density hypothesis is under test.

### Branch C — the inverse question

To place half-ionisation exactly at N = 1100 (T = 2998.05 K) requires **n_b = 1.07×10⁴ m⁻³**
— 4.2×10⁴ times the static vessel's density. The vessel does not have it.

**Named trap, confirmed and disarmed.** Branch C's required density (1.066×10⁴) sits within
17 % of the geometric mean of branches A and B (1.288×10⁴). This proximity is a **tautology**
of `T_half` being linear in `ln n_b` — the log-midpoint of the densities maps to the
log-midpoint of the temperatures by construction. It is **not** evidence for any
geometric-midpoint or "halfway-now" claim, and was recorded in `PROMPT.md` before the run
precisely so it could not be harvested afterwards.

## Branch E — the discriminator the temperature test cannot be

Declared post-hoc: Branch E was written after the first pass, once R3 showed the temperature
test was degenerate. It retunes no pre-registered criterion — R1/R2/R3 stand as first computed.
It was chosen because its answer depends on `n_b` **linearly**, not logarithmically.

A last-scattering surface requires τ = n_e σ_T L ~ 1.

| Branch | n_e [m⁻³] | mean free path [m] | τ over R_CMB |
|---|---|---|---|
| A — ΛCDM at its own T_half | 6.61×10⁸ | 2.28×10¹⁹ | 4.19×10⁷ |
| **B — SDT static vessel** | 2.51×10⁻¹ | 5.98×10²⁸ | **1.59×10⁻²** |

At present baryon density the vessel is **optically thin by a factor of 62.8 across its entire
radius**. No scattering surface forms. This is a hard fork, and it is where the real work now
sits:

1. **If the CMB is a scattering surface in SDT**, the static vessel fails by ~63× in optical
   depth, and needs a density ~10⁴ m⁻³ at the Clearing — which is also, independently, the
   density Branch C requires to put the rung at N = 1100. Two separate constraints asking for
   the same missing 4–5 orders of magnitude is the substantive result of this investigation.
2. **If the CMB is not a scattering surface** — the reading implied by CR13 ("closest point of
   contact") and by the depth-gradient account of the bath — then `z_rec` and `T_rec` have no
   mechanical role in SDT at all, the word "recombination" is borrowed decoration, and both
   constants should leave the `measured` namespace rather than sit there as inputs.

Either way, the present state — importing ΛCDM's `z_rec` and then reporting the temperature it
implies as a recovery — is not a result.

## Labels

| Quantity | Value | Label |
|---|---|---|
| ΛCDM Saha half-ionisation redshift | 1379.3 | COMPUTED (instrument validation) |
| Static-vessel half-ionisation rung | N = 918.8 | COMPUTED |
| `d ln T_half / d ln n_b` | 0.0155–0.0230 | DERIVED (analytic, two-route verified) |
| `z_rec` = 1100, `T_rec` = 3000 K in `laws.hpp` | — | **MEASURED-INPUT (imported; not reproduced)** |
| T = 2998 K at N = 1100 | — | **CALIBRATED(1)** |
| Density required for the rung / for τ~1 | ~10⁴ m⁻³ | COMPUTED — **owed by the vessel** |

## Scope and limitations

Pure hydrogen; helium omitted. Saha equilibrium only — no Peebles non-equilibrium correction,
which is why the comparator lands at z ≈ 1379 rather than the observed z ≈ 1090. The present
baryon density (0.2512 m⁻³) is comparator-sourced: Planck Ω_b h² converted through ρ_crit,
which contains G. Branch D exists so that no conclusion here depends on that value — the
degeneracy holds across 20 orders of magnitude regardless.

## Residuals

- The 4–5 orders of magnitude of density that the vessel owes, demanded independently by
  Branch C (the rung) and Branch E (optical depth).
- Whether SDT claims a scattering surface at all — the fork above is unresolved and is a
  question for Harvey, not for the instrument.
- `CR05`'s comoving-dilution function `n_b(z) = n_b(0)(1+z)³` (`cr05_pressure_solver.cpp:93`)
  is **dead code, never called** — noted here to correct the record, since it was initially
  flagged as live contamination. The live issue in that region is separate and recorded in
  `Investigations/07_Cosmology_and_Redshift/CR05_.../CR05_VERDICT.md` (retracted 2026-07-02),
  whose kill has not been propagated to `laws.hpp:301–311`. Raised for decision; not acted on.
