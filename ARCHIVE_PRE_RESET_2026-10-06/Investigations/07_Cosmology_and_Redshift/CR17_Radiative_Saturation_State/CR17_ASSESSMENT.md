# CR17 — The Radiative Saturation State

**c, P_rad and T at radiative saturation, from the P_eff / Shapiro gradient regime.**
Author: J.C. Harvey, Melbourne · 2026-07-31 · Tool `cr17_saturation.py` · Output `cr17_results.txt`

## Anchor discipline

`z = 1100` and `T = 3000 K` are struck — ΛCDM fit outputs, not measurements. CR13's
`λ_emit = 974.7 nm` is **also not used as an anchor**: it was produced by applying Wien to
`T₀(1+z)` with the imported z, so anchoring on it would return the input. The anchor here is the
**near-infrared band itself** — SDT's own claim that the relay unjams when peak emission crosses
out of the visible. The band is swept end to end; nothing is tuned.

## The answer

Anchored on the near-IR band [780, 1400] nm, central value at the log-centre (1045 nm — log
because every vessel variable is monomial in N):

| quantity | central | band |
|---|---|---|
| **speed of light** `v = c/N` | **2.947×10⁵ m/s** (0.0983 % of c) | 2.20×10⁵ … 3.95×10⁵ m/s |
| **radiation pressure** `P = aT⁴/3` | **1.491×10⁻² Pa** | 4.80×10⁻² … 4.63×10⁻³ Pa |
| **matrix temperature** `T = b/λ_sat` | **2773 K** (kT = 0.239 eV) | 2070 … 3715 K |
| epoch index `N` | 1017 | 759 … 1363 |
| energy density `u = 3P` | 4.474×10⁻² J m⁻³ | |

Equivalently: at saturation the matrix carried a **refractive index n ≈ 1017**, and light crawled
at roughly one part in a thousand of its present speed.

## One gradient law, nine orders of depth

The Shapiro regime and the epoch regime are the same refractive form `v = c/n`, `n = 1+z`:

| | `n − 1` | speed deficit |
|---|---|---|
| solar surface | 2.120×10⁻⁶ | 635.6 m/s |
| radiative saturation | 1.016×10³ | 2.995×10⁸ m/s |

The solar leg checks out against the document independently: `om_⊙ = z_⊙R_⊙ = 1474.9 m` against
Prop 6's stated 1476 m, and the 635.6 m/s deficit reproduces P3's calibration term.

## Where saturation sits, and what P_eff decides

| state | P [Pa] | N |
|---|---|---|
| present epoch | 1.3916×10⁻¹⁴ | 1 |
| radiative saturation | 1.491×10⁻² | 1.02×10³ |
| `P_eff` matrix ceiling | 5.225×10³¹ | 2.475×10¹¹ |

Saturation is **12.0 decades of pressure above the present epoch and still 33.5 decades below the
P_eff ceiling** — a factor 2.4×10⁸ in N short of it. That is the structural result of bringing
P_eff in: **radiative saturation is a radiation-side limit, not a lattice-side one.** The photon
field jams the relay while the spations are nowhere near their own atomic-scale pressure. The
Clearing is the radiation letting go, not the lattice unpacking — which is consistent with the
depinning reading in the opacity-logjam thread and puts the lattice ceiling in an entirely
different regime from the CMB.

## Sensitivity to the anchor

Every output is a pure power of `λ_sat`: `T, N ∝ 1/λ`, `v ∝ λ`, `P_rad ∝ 1/λ⁴`. Across the full
near-IR band (factor 1.795):

- `T`, `N`, `v` move by ×1.79 — **robust**; the band choice barely matters.
- `P_rad` moves by ×10.4 — **not robust**. It is the quantity that most needs `λ_sat` pinned by
  mechanism rather than by band convention, and it should be quoted with the band, not alone.

## What is claimed and what is not

The near-IR band, taken as the only anchor, brackets the epoch at **N ≈ 760–1360** with no fitted
number. Stated precisely: this **brackets**, it does not **predict** — a bracket that wide is
consistent with the observed value without discriminating against alternatives near it. What it
does establish is that the "peak crosses out of the visible" criterion is not an arbitrary
narrative: it lands the epoch in the right decade on its own, from Wien plus the ladder.

For reference and explicitly **not** used: CR13's 974.7 nm gives N = 1090.8, T = 2973 K,
v = 2.748×10⁵ m/s, P = 1.970×10⁻² Pa. That N returns the imported redshift because the wavelength
was back-computed from it. Recorded as a restatement, not a check.

## Residual — CLOSED, see below (`cr17b_closure.py`, `cr17b_results.txt`)

`λ_sat` was a band convention, not a derived quantity. It is now closed on the stated depinning
mechanism.

---

# CR17b — Closing the λ_sat debt

Mechanism taken from the opacity-logjam thread verbatim: *the Clearing is a jamming/depinning
transition that releases at a critical density; baryons are pinned defects — the obstacles the
relay traffic jams around — and that obstacle term is the baryon loading `R`.* So the critical
point of the transition is **obstacle loading unity, `R = 1`**.

Baryon density is sourced from **BBN deuterium** (η = 6.1×10⁻¹⁰ → n_b0 = 0.2505 m⁻³), not from
Ω_b of the CMB fit, so the closure cannot be circular with the CMB it explains. It agrees with the
Planck route to 0.3 %, which is a consistency check rather than an input.

## Candidate conditions — all evaluated, failures reported

| condition | N | λ [nm] | T [K] | verdict |
|---|---|---|---|---|
| C1 Ioffe–Regel, `k·mfp = 1` | 1.88×10¹⁶ | 5.6×10⁻² | 5.1×10¹⁶ | excluded, ×5×10⁻¹⁴ off |
| C2 `n_eσ_T v = H₀` | 21.3 | 4.99×10⁴ | 58 | excluded, ×48 off |
| C3 `τ = 1` over R_CMB | 3.98 | 2.67×10⁵ | 11 | excluded, ×256 off |
| **C4 obstacle loading `R = 1`** | **676.6** | **1571** | **1844** | **in near-IR** |
| C5 `ρ_b = ρ_γ` (the 3/4 convention bound) | 902.2 | 1179 | 2459 | in near-IR |

Only the stated mechanism lands in the band. The three alternatives miss by 14 orders, ×48 and
×256 respectively — they are not close calls, which is worth more than the hit.

## The closed state

`R(N) = (3/4)(ρ_b0/ρ_γ0)/N = 676.6/N`, so `R = 1` at **N = 676.6**:

| quantity | CR17 (band convention) | **CR17b (closed)** |
|---|---|---|
| saturation wavelength | 780 – 1400 nm | **1571 nm** |
| speed of light `v = c/N` | 2.20×10⁵ … 3.95×10⁵ m/s | **4.431×10⁵ m/s** (0.1478 % of c) |
| radiation pressure | 4.63×10⁻³ … 4.80×10⁻² Pa | **2.917×10⁻³ Pa** |
| matrix temperature | 2070 … 3715 K | **1844 K** |
| epoch index N | 759 … 1363 | **676.6** |

`P_rad` was the loose quantity (×10.4 across the band); it is now a single number.
Sound speed at the transition: `c_s = c/√(3(1+R)) = 1.224×10⁸ m/s = 0.408 c`, between CR13's
drag-epoch 0.456 c (R = 0.6) and the pure-radiation ceiling 0.577 c.

**Inputs consumed: `T₀` (FIRAS) and η (BBN deuterium). Both measured, neither from a CMB fit.
Fitted parameters: zero.**

## Why this discriminates rather than restates

C4/C5 are matter–radiation equality **with baryons only**, which is a statement SDT can make and
ΛCDM cannot, because ΛCDM's equality is CDM-dominated. Putting cold dark matter back into the
obstacle budget (`ρ_m/ρ_b ≈ 6.0`) moves equality to N ≈ 5413 and the peak to **196 nm — deep
ultraviolet**, nowhere near the observed transition.

So "the jam releases at obstacle loading unity" lands at the right place *only if there is no dark
matter*. The no-dark-matter premise is carrying the prediction, and it is falsifiable in the
obvious direction: restore CDM and the answer leaves the band by a factor ~6.

## What this does not claim

The closure lands at **1571 nm**, in the near-infrared but **not** at the bottom of the visible.
The "one step past red" narration in CR13 (~975 nm, red edge) is **not** what the stated mechanism
produces — R = 1 sits about twice as red, and the ρ_b = ρ_γ convention bound at 1179 nm is still
1.5× redder than the red edge. Either the narration should move to "near-infrared" and drop
"bottom of the visible", or the mechanism is not exactly `R = 1`. The two cannot both stand as
written, and the discrepancy is a factor of 2, not a rounding matter.

Also unaffected: CR15's finding that Prop 5 forbids an ionisation-driven transition. This closure
is deliberately *not* an ionisation criterion — it is an inertial-loading one, which is why it can
coexist with Prop 5 where a Saha route cannot.

---

# CR17c — The ladder read from where the observer stands

**Narrative correction (Harvey).** The "one step past red" wording put the reader *in colour* and
stepped outward. The reader is not in colour. **We are in the microwave** — 2.7255 K, peak
1.0632 mm — and travelling into the past means going **up** the spectrum toward shorter
wavelengths. The Clearing is what you meet coming up; everything shorter is behind it. The earlier
framing (mine included, when I called it a sweep "down through violet to red") narrated from the
colour end, which is nobody's vantage.

Each rung is a wavelength. `T = b/λ`, `N = T/T₀`, `v = c/N`, `P = N⁴P₀`, `R = 676.6/N` — all
forced. No epoch is imported anywhere in the ladder.

| λ_peak | band | T [K] | N | v [m/s] | P [Pa] | R | received? |
|---|---|---|---|---|---|---|---|
| 1.063 mm | **microwave — here, now** | 2.726 | 1 | 2.998×10⁸ | 1.392×10⁻¹⁴ | 677 | yes |
| 300 µm | sub-millimetre | 9.66 | 3.54 | 8.46×10⁷ | 2.20×10⁻¹² | 191 | yes |
| 100 µm | far infrared | 29.0 | 10.6 | 2.82×10⁷ | 1.78×10⁻¹⁰ | 63.6 | yes |
| 10 µm | mid infrared | 290 | 106 | 2.82×10⁶ | 1.78×10⁻⁶ | 6.36 | yes |
| 2.5 µm | short-wave infrared | 1159 | 425 | 7.05×10⁵ | 4.55×10⁻⁴ | 1.59 | yes |
| 2 µm | short-wave infrared | 1449 | 532 | 5.64×10⁵ | 1.11×10⁻³ | 1.27 | yes |
| **1571 nm** | **▸ THE CLEARING (R = 1)** | **1844** | **676.6** | **4.431×10⁵** | **2.917×10⁻³** | **1** | **— wall —** |
| 1400 nm | near infrared | 2070 | 759 | 3.95×10⁵ | 4.63×10⁻³ | 0.891 | behind |
| 1179 nm | near infrared (ρ_b = ρ_γ) | 2458 | 902 | 3.32×10⁵ | 9.20×10⁻³ | 0.750 | behind |
| 975 nm | near infrared | 2972 | 1090 | 2.75×10⁵ | 1.97×10⁻² | 0.620 | behind |
| 780 nm | near infrared onset | 3715 | 1363 | 2.20×10⁵ | 4.80×10⁻² | 0.496 | behind |
| **750 nm** | **RED — the visible edge** | 3864 | 1418 | 2.12×10⁵ | 5.62×10⁻² | 0.477 | behind |
| 625 nm | red / orange | 4636 | 1701 | 1.76×10⁵ | 0.117 | 0.398 | behind |
| 590 nm | orange / yellow | 4911 | 1802 | 1.66×10⁵ | 0.147 | 0.375 | behind |
| 565 nm | yellow / green | 5129 | 1882 | 1.59×10⁵ | 0.175 | 0.360 | behind |
| 500 nm | green / cyan | 5796 | 2126 | 1.41×10⁵ | 0.285 | 0.318 | behind |
| 485 nm | cyan / blue | 5975 | 2192 | 1.37×10⁵ | 0.321 | 0.309 | behind |
| 450 nm | blue / violet | 6439 | 2363 | 1.27×10⁵ | 0.434 | 0.286 | behind |
| 380 nm | violet — far visible edge | 7626 | 2798 | 1.07×10⁵ | 0.853 | 0.242 | behind |
| 100 nm | ultraviolet | 2.90×10⁴ | 1.06×10⁴ | 2.82×10⁴ | 178 | 0.064 | behind |
| 1 nm | X-ray | 2.90×10⁶ | 1.06×10⁶ | 282 | 1.78×10¹⁰ | 6.4×10⁻⁴ | behind |
| 1 pm | gamma | 2.90×10⁹ | 1.06×10⁹ | 0.282 | 1.78×10²² | 6.4×10⁻⁷ | behind |

## What the ladder says

1. **From here to the wall is 2.83 decades in wavelength and ×677 in N** — 1.0632 mm up to
   1571 nm.
2. **Red is never reached.** The visible edge at 750 nm sits at N = 1418, which is **×2.10 beyond
   the wall**. Coming up from the microwave you meet the Clearing in the infrared and stop.
3. **The entire visible spectrum, N = 1418 → 2798, lies behind the wall.** Nothing in colour was
   ever received directly. "One step past red" is the wrong step and the wrong starting point;
   from the observer's real position the wall arrives *before* red, not after it.
4. The visible is a narrow slice of the vessel — 0.30 decades in N, against 11.39 decades from
   here to the P_eff ceiling.

## The Clearing is a sweep, not a knife edge

`R = 676.6/N` runs continuously, so the transition has width:

| loading | N | λ [nm] | T [K] | v [m/s] |
|---|---|---|---|---|
| R = 0.5 — jam still winning | 1353 | 786 | 3688 | 2.22×10⁵ |
| R = 0.6 — drag epoch (CR13) | 1128 | 943 | 3074 | 2.66×10⁵ |
| **R = 1.0 — depinning** | **677** | **1571** | **1844** | **4.43×10⁵** |
| R = 2.0 — obstacles dominant | 338 | 3143 | 922 | 8.86×10⁵ |

The window R = 0.6 → 1.0 runs **943 nm → 1571 nm, N = 1128 → 677** — a swept infrared band,
entirely short of red. That matches the "gradual clearing, not a floor" reading in the
opacity-logjam thread rather than contradicting it. CR13's independently-adopted drag-epoch
R = 0.6 lands inside the window; that is a consistency check on the loading law, not a second
result, and it is not claimed as one.

The rungs are stated as computed. Readers who know the standard values will see where they fall
in the table; no correspondence is asserted here, because the ladder's inputs are `T₀`, `η` and a
list of wavelengths, and it is not this investigation's business to make the comparison for them.
