# GD11 — Assessment (2026-10-16)

Pre-registration: `PROMPT.md` (with Amendments 1 and 2). Tool: `gd11_static_disc_cascade.cpp`. Output capture:
`run_output.txt`. Products: `gd11_ridge_metrics.csv` (per ridge node), `mw_throughput.js` (maps for the
GD08 viewer, Depth → Map states 1 and 2). Static disc; no velocity, rotation or redshift entered as input,
comparison or calibration. Labels: inputs OBSERVED (positions, GD09 counts); canon quantities from `laws.hpp`;
every field COMPUTED. σ_occ, s and h₁ PENDING; nothing CALIBRATED; nothing DERIVED beyond the canon identities.

## Instrument validation
V1 `mass_from_V_disp(V_p)` = m_p to 2×10⁻¹⁶. V2 shell theorem for u: outside −1.6×10⁻³, inside 2.2×10⁻³ of the
surface value. V3 flux conservation: −4.5×10⁻⁴ (2 kpc), −5.6×10⁻⁵ (5 kpc). V4 mean column on a uniform ball,
softening-corrected: −9.4×10⁻⁴ (centre), −1.6×10⁻³ (d = 0.6 a); uncorrected the sum was −4.8% and −5.6% (the
analytic Plummer bias −(π/2) ε/a = −4.7%), recorded in Amendment 1. V5 recursion identity exact. V6 particle sum
against ray quadrature on the analytic density: +1.2×10⁻³ at the Sun, +1.4×10⁻² at the centre. All consistent.
Monte-Carlo noise at 10⁶ particles: 1.25% (Θ̃), 1.9% (|u|); at 2.4×10⁵ it was 2.45% and 3.69% with the same
classifications (Amendment 2).

## S2 — the cascade, in lattice units
Per baryon: V_p = 1.8327×10⁻⁵⁸ m³ = 4.3406×10⁴⁶ spations. Galaxy (GD09 counts plus Sgr A* at 5.0×10⁶³
baryon-equivalents): N = 7.815×10⁶⁷, V_enc = 1.432×10¹⁰ m³ (a cube 2.43 km on a side), n_d = 3.392×10¹¹⁴ spations.
Shift of the shell at radius r, δ = V_enc(r)/(4π r²), in pitches:

| r | N_enc | shift (pitches) |
|---|---|---|
| 1 pc | 5.0×10⁶³ (Sgr A* only) | 4.7×10⁶ |
| 100 pc | 5.5×10⁶⁴ | 5.2×10³ |
| 1 kpc | 1.0×10⁶⁷ | 9.7×10³ |
| 4 kpc | 4.4×10⁶⁷ | 2.6×10³ |
| 8.15 kpc | 6.5×10⁶⁷ | 931 |
| 15 kpc | 7.6×10⁶⁷ | 321 |
| 30 kpc | 7.8×10⁶⁷ | 82 |
| 86 kpc | 7.8×10⁶⁷ | 10.0 |
| 300 kpc | 7.8×10⁶⁷ | 0.82 |

Displacement horizon r₁ (shift = one pitch): proton 9.5×10⁻¹³ m; Sun 1.06 pc; Sgr A* alone 2.18 kpc; whole Galaxy
**272 kpc**, 18.1 times the 15 kpc drawing extent of the disc and 8.8×10⁻⁶ of R_CMB. The displacement continues
past the visible disc by a factor of eighteen in radius. The shift at the Clearing is n_d/S = 7.8×10⁻¹¹ pitch,
a fraction 7.8×10⁻¹¹ of the boundary cells. The recursion δ_{k+1} r_{k+1}² = δ_k r_k² holds exactly outside the matter.
The matter volume fraction is φ_V = n_b V_p = 7.4×10⁻⁵² (0.1 M☉ pc⁻³); the strain δ/r at 8.15 kpc is 6.0×10⁻⁵³.

## S3–S5 — the blocked-sky field and the pressure
Mean baryon column Θ̃ and displacement |u| (contrast 1.32):

| | Θ̃ m⁻² | M☉/pc² equiv. | |u| pitches | bridge Z |
|---|---|---|---|---|
| Sun | 2.168×10²⁶ | 173.6 | 1077 | 4.171×10⁻⁷ |
| centre | 6.475×10²⁷ | 5184 | zero by symmetry (noise 384) | 1.660×10⁻⁶ |

Centre/Sun: Θ̃ 29.9; bridge Z 3.98. Arm overdensity raises Θ̃ at the Sun by 4.7% and changes |u| by −1.3%.
Blocked sky Θ = σ_occ Θ̃ at the Sun, per canon-geometric bound: σ_excl = 3.90×10⁻³⁹ m² → 8.5×10⁻¹³;
σ_p = 2.22×10⁻³⁰ m² → 4.8×10⁻⁴; σ_int = 7.45×10⁻³⁰ m² → 1.6×10⁻³. Pressure deficit δP/P_ref = −(1−s) Θ;
with s → 0 the macro change at the Sun is −2.3×10⁻¹⁷ Pa against P_rad = 1.39×10⁻¹⁴ Pa (σ_int bound).
Validity of the first-order form (criterion τ_max ≤ 0.1): longest in-plane column 3.93×10²⁸ m⁻² gives τ_max =
1.5×10⁻¹⁰ (σ_excl), 0.087 (σ_p), 0.29 (σ_int). Valid for σ_excl and σ_p; **not valid for σ_int at the centre**
(first-order truncation error up to about 15% there).
Slow passage (S4): the term φ_V (1/s − 1) exceeds the blocking term σ Θ̃ only for s < 4.6×10⁻⁴⁹. Between that
value and 1 the slow rate does not change the macro field; as s → 0 it reduces to the blocking of S3.

## S6 — the sheaths (pre-registered classification)
Direction of the displacement field against the ridge tangent, ⟨|û·t̂|⟩, against the geometric projection of a
purely radial field, ⟨|r̂·t̂|⟩:

| arm | nodes | ⟨\|u·t\|⟩ | ⟨\|r·t\|⟩ | Θ̃ contrast vs ring | \|u\| contrast vs ring | cos(bulge, disc) | nodes where bulge dominates |
|---|---|---|---|---|---|---|---|
| 3-kpc(N) | 7 | 0.017 | 0.073 | +11.5% | +3.3% | 0.999 | 100% |
| Norma | 335 | 0.127 | 0.139 | +3.4% | −1.1% | 0.996 | 31% |
| Sct-Cen | 490 | 0.227 | 0.225 | +3.1% | −1.2% | 0.997 | 15% |
| Sgr-Car | 551 | 0.139 | 0.130 | +3.4% | −0.1% | 0.998 | 0% |
| Local | 85 | 0.201 | 0.198 | +3.5% | +2.8% | 0.999 | 0% |
| Perseus | 637 | 0.164 | 0.165 | +3.9% | +0.6% | 0.998 | 0% |
| Outer | 535 | 0.113 | 0.112 | +4.6% | +0.6% | 0.998 | 0% |

All arms: M1 = 0.156 against geometric 0.155 (difference 0.001). Displaced-volume flux carried along the sheath
cross-sections against V_enc(R): M2 = 1.4×10⁻⁵ (5 kpc), 8.5×10⁻⁵ (8 kpc), 8.6×10⁻⁵ (12 kpc).
**Classification: not supported** (M1 within 0.05 of the radial projection, and M2 < 1%). In this structure the
displacement field crosses the arms as a radial field does, at about 80° to the ridge, and the sheaths carry about
10⁻⁴ of the outward displaced volume along their length. The bulge and disc displacement fields point the same way at
every ridge node (cosine ≥ 0.996): they reinforce everywhere. The bulge field dominates only inside 3.4–3.9 kpc
(crossings at 3.94 kpc on Norma and 3.42 kpc on Sct-Cen).
Per-node noise is 1.25% (Θ̃) and 1.9% (|u|); the per-arm contrasts above average over 85–637 nodes.

## S7 — emission at depth: patterns, not amplitudes
No closure from blocked sky to emission position is chosen (GD06 h(Θ), h₁ PENDING). Pattern of Θ̃ relative to the Sun
and of the bridge Z (same rings):

| R kpc | 2 | 4 | 6 | 8 | 10 | 12 | 15 |
|---|---|---|---|---|---|---|---|
| Θ̃ / Θ̃_Sun | 7.62 | 3.26 | 1.80 | 1.04 | 0.63 | 0.41 | 0.23 |
| Z / Z_Sun (ϟ_b bridge) | 2.57 | 1.75 | 1.31 | 1.02 | 0.82 | 0.68 | 0.54 |

If z_d = h₁ σ_occ Θ̃ were required to equal the bridge Z at the Sun, the product would be h₁ σ_occ = Z_Sun/Θ̃_Sun
= 1.92×10⁻³³ m², between σ_excl and σ_p. The same product then gives a centre-to-Sun ratio of 29.9 against the bridge's
3.98. The two routes have different kernels (1/r² against 1/r) and cannot both hold for a distributed source with a
single constant. The closure that reconciles them is the open h(Θ) of GD06 (XSD-B).

## Scope and limitations
- σ_occ, s and h₁ are not chosen. The first-order blocked-sky form fails for the σ_int bound at the centre.
- The sheath classification is for the displacement field of canon matter volumes. A mechanism that confines
  displacement to the arms would need a resistance contrast across the sheaths; the contrast available here is
  ≲ τ across a sheath width, about 10⁻⁴, and a conductance law has not been supplied.
- The 7×10⁻⁵² matter volume fraction and the 10⁻⁴ channel fraction follow from V_p and the Reid sheath cross-sections; if the
  occlusion or resistance of displaced spations is carried by something other than the exclusion volume, the
  classification would change.
- The spherical-equivalent cascade uses a Galactic-centre origin; |u| at the centre is zero by symmetry and
  the printed value is noise. Stellar halo and corona are excluded; bulge and thin-disc counts may double count
  inner-disc stars (GD09 limitation).
- Not run: an equalisation operator for this structure (no conductance law); a comparison with any velocity or
  redshift data (excluded by premise).

## Correction 1 (2026-10-16, Operator instruction: no tweaking to match)

Withdrawn: the paragraph under S7 that computes the product h₁σ_occ = Z_Sun/Θ̃_Sun = 1.92×10⁻³³ m² "if z_d = h₁σ_occΘ̃
were required to equal the bridge Z at the Sun", and the sentence that the same product then gives a centre-to-Sun
ratio of 29.9 against 3.98. That is a parameter implied by matching a target, which the Operator ruled out. The
pattern table (Θ̃ and the bridge Z relative to the Sun along rings) stays as computed. Successor: GD12, in which the
pressure is displaced volume per shell volume, (V_p/ℓ_P) Θ̃, with no cross-section, passage rate or closure constant.
