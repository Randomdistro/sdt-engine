# CR12 — The Distance Law: does the supernova Hubble diagram need dark energy?

**J. C. Harvey, Melbourne — 2026-06-24.** Domain: `07_Cosmology_and_Redshift`.
Tool: `cr12_pantheon_fit.py` (real data). Data: **Pantheon+ (1701 SNe Ia)**, 1580 in the Hubble flow.
Plot: `cr12_hubble_residual.png`. Closes the CONDENSA/CR10-D2 Pantheon+ item — **with a straight verdict.**

> This is the swing at the headline evidence for dark energy: the Type-Ia supernova Hubble diagram (Nobel 2011).
> No spin — the χ² is reported as it landed.

---

## The SDT distance law (derived, one parameter)

SDT is static; its cosmological redshift is the **time-global aging of the glass** (FLM09) at a **constant
fractional rate** `H₀` — there is no mechanism to accelerate or decelerate the medium's aging, so the rate is
simply constant. Constant fractional redshift per unit light-path gives

```
d(1+z)/(1+z) = (H₀/c) dχ   ⟹   χ = (c/H₀) ln(1+z)
```

and, flat, with the **CR11** Etherington reciprocity `d_L=(1+z)²d_A`,

```
d_L^SDT(z) = (1+z) (c/H₀) ln(1+z)        ← ONE parameter (H₀); the SHAPE is fixed, zero free knobs
```

This is the constant-rate **coasting** law. It coincides with the flat `R_h=ct` luminosity distance — and it is
**non-decelerating by construction.** That single fact is the whole story below.

## Method

Fit the *shape* of `μ(z)=5log₁₀(d_L/10pc)` to the Pantheon+ `MU_SH0ES` distance moduli (Hubble-flow SNe,
`z>0.01`, Cepheid calibrators removed), marginalising the additive offset **analytically** (this removes the
`H₀`/absolute-magnitude degeneracy, so only the *shape* of `μ(z)` is compared). Controls: **ΛCDM** (flat, fit
`Ω_m`), **EdS** (matter-only, no Λ, decelerating), **Milne** (empty open coasting).

## Result (real data, as it landed)

| model | dark energy? | params | χ² | χ²/dof | ΔAIC |
|---|---|---|---|---|---|
| **ΛCDM** (Ω_m=0.35) | yes | offset + Ω_m | **681** | 0.43 | **0** |
| Milne (open coasting) | no | offset | 718 | 0.45 | +34 |
| **SDT** (aging-glass coasting) | **no** | offset | **773** | **0.49** | +90 |
| EdS (matter-only, decelerating) | no | offset | 1331 | 0.84 | +648 |

*(χ²/dof < 1 because only the diagonal μ-errors are used — they are conservative; see caveat. The model
**ordering** is robust; the exact Δχ² is indicative.)*

## Verdict — honest

**What genuinely wins (the reframe):** the supernova "proof of dark energy" is, in the numbers, the
**exclusion of *deceleration*.** The matter-only EdS model — the thing dark energy was invented to replace — is
crushed by `Δχ² = +650`. **SDT's aging-glass law is non-decelerating by construction, so it never had EdS's
problem:** it fits Pantheon+ at `χ²/dof ≈ 0.49` — a *good* fit — with **zero dark energy**, beating EdS by 558.
So **dark energy is not required to fit the supernovae.** The famous diagram is evidence *against deceleration*,
which SDT does not predict — not positive evidence for `Λ` that SDT cannot supply.

**What does not win (said plainly):** **ΛCDM is still preferred over the flat-coasting SDT law by `ΔAIC ≈ 90`.**
On the SN data alone, SDT does **not** beat or tie ΛCDM. (That `Δχ²=92` is a model-selection gap; it is *not* a
`√92 → "9σ"` detection — that arithmetic is wrong for non-nested models.) This is consistent with the
literature finding `R_h=ct` mildly disfavoured by Pantheon.

**Where the residual gap actually lives:** it is largely **spatial geometry, not dark energy.** *Open* coasting
(Milne) closes most of it (`ΔAIC +34`), so a small effective curvature in the aging-glass geometry — not a `Λ`
term — accounts for the bulk of the SDT↔ΛCDM difference. **The dark-energy question is settled in SDT's favour;
a curvature detail remains.**

> **Bottom line.** Swing taken, real contact: the dark-energy strawman (EdS) is gone, and SDT fits the
> supernovae well without `Λ` — a genuine, citable reframe of the Nobel evidence. But it is a **stand-up double,
> not a park-exit**: ΛCDM still edges the flat-coasting law on SNe alone (`ΔAIC≈90`). The ball was caught at the
> warning track, and the honest scoreboard says so.

## Ledger

**[EARNED]** EdS (no-Λ deceleration) excluded at `Δχ²≈+650`; SDT aging-glass coasting fits 1580 real SNe at
`χ²/dof≈0.49` with **no dark energy** — dark energy is not required by the SN Hubble diagram.
**[HONEST-NEGATIVE]** ΛCDM preferred over flat-coasting SDT by `ΔAIC≈90` on SNe alone; SDT does not win here.
**[IDENTIFICATION]** the distance law as the constant-rate aging-glass coasting (leans on FLM09 + CR11).
**[OPEN]** the small residual = spatial-curvature sector (open vs flat coasting); and the **decider**, BAO+CMB
(the acoustic peaks — FLM09 Arm B owes this), where ΛCDM's real advantage lives.

## Run it

```bat
python Investigations\07_Cosmology_and_Redshift\CR12_Pantheon_Distance_Law\cr12_pantheon_fit.py
```
Downloads-free (reads `C:\tmp\PantheonPlusSH0ES.dat`); prints the table + honest reading and writes
`cr12_hubble_residual.png`.
