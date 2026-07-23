# NP27 — Technical Report: beam kinematics, the geometric peel, and the fine-tune that didn't land
### RUN 1, 2026-07-21 · J. C. Harvey, Melbourne
### Task: use the ²³⁸U + p beam data (Bernas 2003) and the packing model to fine-tune each other.

> **Data:** Bernas et al., *Nucl. Phys. A* (2003), "Fission-residues produced in the spallation
> reaction ²³⁸U + p at 1 A GeV", GSI FRS, inverse kinematics, 733 identified fragments.
> Table 3 per-Z fragment kinetic energies (Z = 28–64), mean fragment Ā = 108.0 ± 0.3 (σ_A = 17.5),
> mean fissioning parent A₀ ≈ 220, Z₀ ≈ 90, mean TKE 152 MeV.
> **All constants zero-fit from `laws.hpp`:** R_p = 8.414e-16 m, k_proton_surface = 0.5464,
> nuclear radius R(A) = R_p·(A/η)^{1/3}, η = π/√18, movement budget v_circ² + v_trans² = c².

---

## 1. The kinematic chain — CONFIRMED, clean, zero-fit

Harvey's predicted sequence, each step checked against canon:

| step | quantity | result | source |
|---|---|---|---|
| **1** | rotation of a hydrogen-like heavy nucleus | **v_phase = c/k_proton_surface = 1.830 c** | `laws.hpp:672,1269` — matches "1.83 like all the other tests" |
| **2** | 1 A GeV proton beam relative speed | γ = 1 + 1000/938.272 = 2.066 → **β = 0.875 c** | KE per nucleon |
| **3** | movement-budget slowdown of the beam proton | v_circ = √(c²−v²) = **0.484 c = 1/γ** (identity holds) | `law_V` T10 |
| **4** | U-238 boundary radius | **5.76 fm** (measured rms 5.86, −1.6%) | R(A) zero-fit |
| **4** | surface rotation during one transit | ω = 9.52e22 rad/s; **arc swept = 309° ≈ 0.86 turn** | derived |

**Reading:** the beam proton arrives with its internal gear half-stalled — 51.6% of its circulation
budget is spent punching translationally through the lattice, so v_circ has dropped from c (at rest)
to 0.484c. Meanwhile the U surface, whirling at the universal 1.83c counter-seat, turns **most of a
full revolution** under the proton during the ~5.7e-23 s it takes to cross. The setup for a helical
peel is real and the numbers are self-consistent. **This part of the picture holds.**

The 1.83c is confirmed as a **per-baryon** quantity: every surface spation is driven at ω_demand by
its nearest baryon, and the phase velocity demanded is 1.83c independent of Z. It is not special to
hydrogen — "hydrogen-like uranium" and hydrogen give the same surface counter-seat.

---

## 2. The fine-tune via fragment kinetic energies — DEGENERATE (does not test the packing)

The obvious lever: predict Bernas's per-Z fragment kinetic energies from a Coulomb-at-scission model
whose scission distance comes from the packing radii, and read off the fine-tune. It looks superb —
and the null test shows it is a **mirage**.

| model (one free scale each) | RMS vs 37 measured Ekin(Z) | r |
|---|---|---|
| A: constant scission distance — **no radius law**, pure Z(90−Z)² Coulomb shape | **3.22 MeV** | 0.9936 |
| B: SDT packing radii, touching | 3.25 MeV | 0.9926 |
| C: standard r₀ = 1.2 fm radii, touching | 3.25 MeV | 0.9926 |

The naked Coulomb shape (A), with **no radius law at all**, fits *best*. The R² ≈ 0.986 I first
obtained is Coulomb-vs-Coulomb tautology: the measured Ekin(Z) *is* Coulomb-dominated, so any Coulomb
model tracks it. Worse for discrimination: **SDT radii and textbook r₀ = 1.2 fm give identical
numbers** (symmetric-split D = 11.51 vs 11.50 fm; TKE 253.4 vs 253.6 MeV). Both require the same
**+7.68 fm neck elongation** to match the measured 152 MeV TKE (a real, known fission effect — prolate
fragments at scission — but not a packing signature).

> **Verdict: the beam Ekin data cannot fine-tune the packing radius law. The channel is degenerate.**
> This is exactly the trap the stick model already flagged ("Bernas doesn't count neutrons — tested
> wrong observable"): a beautiful correlation on an observable the hypothesis doesn't uniquely predict.

---

## 3. The geometric peel — mean is trivial, width is not reproduced

Testing "fission products are almost always the same or similar variations → simple geometric peel"
by cutting the 91-site greedy-FCC U packing (α core + 36 d + 54 t).

**Central planar cut** (4000 random orientations through the centroid):

| | mean A_light | σ_A |
|---|---|---|
| packed-lattice central cut | **107.6** | 2.6 |
| structureless 91-point ball (control) | 108 | 5.5 |
| **Bernas measured** | **108.0** | **17.5** |

The **mean is a bullseye — and trivially so:** any central bisection of a roughly-spherical ball
splits it in half, and 108 = 0.49 × 220. It is not evidence for packing. The **width fails**: the
lattice gives σ = 2.6, *narrower* than a structureless ball (5.5), so the packing adds **no structure**
to the split distribution, and neither comes near the measured 17.5.

**Impact-parameter peel** (beam at b ~ uniform-in-area, cap cleaved beyond closest approach):
mean A = 16.5, σ = 22.6 — a **grazing-chip** distribution, wrong regime for the symmetric fission mode.

**The two regimes are geometrically distinct, and that is the real structural finding:**

- **central hit (b ≈ 0) → near-symmetric bisection → fission** (mean 108, the Bernas channel)
- **grazing hit (b → R) → thin surface shave → spallation** (small residues, the "peel that snaps closed")

The observed fission **width** σ_A = 17.5 corresponds to the scission plane wandering ~±0.10 R
(≈ one subunit layer, ~0.6 fm) off-centre. That is physically modest and appealing — but it is
**fitted to σ, not predicted**. The packing does not generate the width on its own.

---

## 4. Honest bottom line

| claim | status |
|---|---|
| kinematic chain (1.83c, β=0.875, slowdown 1/γ, 309° sweep) | **CONFIRMED** against zero-fit canon |
| "hydrogen-like uranium rotates at 1.83c" | **CONFIRMED** — per-baryon counter-seat, Z-independent |
| Ekin(Z) fine-tunes the packing radii | **KILLED** (null test — Coulomb-degenerate; SDT ≡ standard radii) |
| fission = geometric peel, mean fragment | mean **reproduced but trivially** (bisection ≈ half) |
| fission = geometric peel, mass width | **NOT reproduced** — width is fitted (±0.1R scission jitter), not derived |
| peel vs split are distinct regimes | **NEW, supported** — central = fission, grazing = spallation |

> **The fine-tune Harvey hoped for does not land through either observable I can compute here.**
> The Ekin channel is Coulomb-degenerate (can't see the radii); the mass channel gives only the
> trivial mean. What survives is (a) a fully consistent kinematic setup for the helical peel, and
> (b) a clean geometric separation of the fission and spallation regimes by impact parameter.

---

## 5. What would actually test it — the open lever

The untested lever is the **helical peel mass**: chord (entry/exit at impact parameter b) + 309°
surface rotation → a band of shell of azimuthal extent φ_b = ω·τ_b and some **radial depth Δr**.
Its mass is computable — *once Δr is specified*. The geometry here fixes the azimuth and the chord;
it does **not** fix how many subunit layers deep the shave bites. That radial depth is the one number
the mechanism still needs from Harvey; I will not invent it. With Δr given, the model makes a sharp,
falsifiable per-b mass prediction that can be folded against the geometric cross-section and compared
to the *full* Bernas mass distribution — width included.

**Data still missing for the decisive test (NP26):** event-resolved Y(A, Z, TKE, ν) rather than the
averaged Table-3 curves used here. Averaged Ekin(Z) is Coulomb-degenerate by construction; only
event-resolved TKE-vs-asymmetry can separate a peel geometry from ordinary Coulomb.

## Verdict
> Kinematics **CONFIRMED** · Ekin fine-tune **KILLED as degenerate** (null test) ·
> geometric-peel mean **trivial**, width **not derived** · peel/split regime split **NEW** ·
> helical-peel radial depth **OPEN — needs Harvey's spec, not a guess.**
