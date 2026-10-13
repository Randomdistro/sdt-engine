# Displaced space as the solar prism: formulation, round 1 (assessment, 2026-10-10)

- **Pre-registration:** `SOLAR_LENS_FORMULATION_2026-10-10_PRE_REGISTRATION.md`.
- **Instrument:** `solar_renormalisation/solar_lens_form_1.cpp`, output `solar_lens_form_1_results.txt`. Validations V1–V4 met; single pass, no amendment.

## Step 1 (derived)

Ray invariant: R_app(λ) = n(R_t, λ)·R_t. The apparent-size spectrum is a readout of the displaced-space index at the boundary.

## Step 2 (magnitude)

| native source | value | limb shift | verdict |
|---|---|---|---|
| gravitational depth, z = Ѻ/R | 2.122e-6 | 1.477e3 m (0.002″) | short by 10²–10³ |
| law-IV exclusion, n_b·V_disp | 1.8e-35 | — | negligible |

**The effect is not a smooth depth term.**

## Step 3 (forms)

**F2a, both walls fixed at the dips (158 nm, 150 µm): INADEQUATE.**
- χ²/dof = 318.
- A wall at 158 nm is too close to the 160 nm point: residuals are +40.9σ at 170 nm and −22.3σ at HMI.
- **G1.**

**F2b, UV wall free and far-IR wall at 150 µm: ADEQUATE.** χ²/dof = 2.92 over all 10 points (6 dof), AIC 25.5.
- **UV wall placed by the data at 141.0 nm** (Δχ² = 1: 140.1–141.8 nm), 17 nm short of the 158 nm brightness dip.
- **R_t (the boundary with no bending, n = 1) = 958.527 ± 0.027″** (±0.046″ with χ² scaling), which is 695.19e6 m.
- Wall strengths: A = 2.10e-3 (UV) and B = 8.35e-3 (far-IR). CALIBRATED(4) with R_t and λ_U.
- Residuals are within 1.5σ except SODISM 782.2 nm (+3.1σ), which is the HMI/SODISM offset again.

## Step 4: predictions where nothing is measured (from F2b; untested)

**P2: the apparent solar radius across the gap.**

| λ (m) | R_app (″) |
|---|---|
| 1.00e-6 | 959.555 |
| 3.00e-6 | 959.535 |
| 10.00e-6 | 959.517 |
| 30.00e-6 | 959.368 |
| 100.00e-6 | 956.333 |
| 140.00e-6 | 932.139 |
| 149.00e-6 | 592.758 |

**The Sun looks progressively smaller approaching the far-IR wall.**

**P1: far-IR evanescent band, 149.38e-6 to 150.00e-6 m (width 620.74e-9 m).** Here n² < 0. The medium does not carry the impulse, it tunnels, and **the disk vanishes**, then reappears on the long side, which reads large (961–967″ at mm). This is the 17 June 2026 vanish-and-reappear prediction, now produced by a fitted displaced-space form instead of drawn in by hand.

**P3: UV evanescent band, 140.85e-9 to 141.00e-9 m (width 148.12e-12 m).** Too narrow for broadband imaging.

**F2a, for comparison:** P1 is 149.44–150.00 µm, and the radius reaches 98.4″ at 149.44 µm.

## Context only

R_t = 958.53″ sits 0.67″ (487 km) below the seismic radius (959.20″) and 1.06″ below the round-2 floor (959.59″). In this form the visible floor is the boundary seen through a small residual index, n − 1 ≈ 1.1e-3, from the two walls' far tails.

## Limitations
- **The UV wall rests on 2 points** (160 and 170 nm). A measured radius at 145–155 nm decides whether the wall sits at 141 nm or nearer the 158 nm dip.
- **The far-IR wall position is held at 150 µm** by registration, but the dip is "near 150 µm", unresolved (E109 §3). Every P1/P2 number moves with it: the band edges scale with λ_I, and the band width is about λ_I·B/2.
- **The fitted wall strengths have no native origin yet.** That is the open formulation step (Step 5). Candidates: matter loading of the spation pressure depth (E109's "medium's seats"), and the redirected throughput fraction at the boundary.
- **The form is the general shape of a wall,** a pole with positive long side and negative short side. It corresponds to resonance (Sellmeier) dispersion, so it cannot discriminate on shape alone. What discriminates is where the walls sit (at the dips) and P1/P2 in the gap.
- **The HMI/SODISM offset** (about 0.3″) limits everything at the ±0.15″ level.

## Grades
- Step 1 geometry: DERIVED (G4, convergent with ray optics).
- Step 2 magnitudes: COMPUTED.
- F2a: G1.
- F2b: G2. The form is adequate and the predictions are registered but CALIBRATED(4); the native wall strength is open.

## What would decide it
- Measured solar radii at 145–155 nm (UV wall position).
- Measured solar radii at 30–150 µm. **F2b predicts a shrinking disk: 956.3″ at 100 µm, 932″ at 140 µm, then a dropout band about 0.6 µm wide just short of the far-IR dip.**
- A resolved far-IR dip position.
