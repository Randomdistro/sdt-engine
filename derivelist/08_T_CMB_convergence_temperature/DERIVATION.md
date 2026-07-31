# T_CMB — present CMB temperature (boundary state, not a constant)

> **J. C. Harvey, Melbourne — 2026-07-30.** Measured anchor: 2.7255 K (FIRAS).
> Whitelist entry: `laws.hpp:165`. Primary records: CR13
> (`Investigations/07_Cosmology_and_Redshift/CR13_CMB_Backtrack_to_Closest_Contact/CR13_VERDICT.md`),
> CR07 (octave ladder), TD06 (blackbody from counted modes).
> Re-run: `../derivelist_results.txt` §[8].

## Role in the framework

T_CMB is the current convergence temperature — the thermal state of the relay
bath *now*. It conditions the Law I chain (u_CMB = aT⁴ → ε → Φ → P_conv). It is
a **boundary condition**, the same class of object as "what time is it", not a
constant of nature.

## What is on record

**CR13 backtrack (executed 2026-06-29; all inputs measured, zero fitted
parameters, no expansion assumed).** The bath peaked at **974.7 nm** (red/near-IR
edge) the moment transparency set in; the "bottom of the visible" is closed
quantitatively (13.6 eV → kT_rec = 0.256 eV → 2973 K → 975 nm). Re-run of the
Wien inverse:

```
T_rec  = b/λ_emit = 2972.99 K                    (−0.90% vs the 3000 K anchor)
T_CMB  = T_rec/(1+z_rec) = 2.7003 K              (−0.93% vs FIRAS 2.7255)
octaves: log₂(1+z_rec) = 10.105                  (CR07 ladder, 1+z = 2^Δn)
```

**Consistency, not derivation — stated exactly.** The backtrack consumes z_rec
(measured) and returns T_CMB from T_rec; z_rec is *defined* through the same
temperature ratio. The chain is **shared-input** — it cannot stand as an
independent origin for the absolute temperature. What it does close is the
wavelength question and the coherence constraint: FIRAS y < 1.5×10⁻⁵ forces
source temperature coherence < 0.55% (broad-distance bath excluded ×183).

**FLM06 cross-link.** T_CMB sits in the thermal seat of the reduced whitelist
(FLM13); the Seed Theorem quantity set includes it and still cannot build ℓ_P —
temperature ratios reach ~10³, not 10⁶¹.

## Scope / Limitations / Residuals

- The absolute value is not derivable from within the framework on the current
  record — and on the cyclic reading it should not be: it is the state the
  detonation-recharge cycle is currently in (a clock reading). Deriving it
  would amount to deriving today's date.
- The SDT-specific distance to nearest contribution is owed (needs the
  quantitative dz/dr gradient law — CR13's stated open item).
- The coherence mechanism (CR07 non-compounding octaves) is asserted, not yet
  derived from open-close synchrony — the live frontier on the record.

## Status

**No line as derivation — reclassified.** T_CMB stays measured (FIRAS), but it
leaves the "underived constant" ledger: it is the thermal boundary state of the
present epoch, with the emission edge (975 nm), the octave count (10.105) and
the coherence gate all earned around it.
