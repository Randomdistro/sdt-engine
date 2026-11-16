# Renormalising the Sun, round 2: the real figure (assessment, 2026-10-10)

- **Pre-registration:** `SOLAR_RENORMALISATION_ROUND2_2026-10-10_PRE_REGISTRATION.md`.
- **Instrument:** `solar_renormalisation/solar_renorm_2.cpp`, output `solar_renorm_2_results.txt`. Validations V1–V3 met; single pass, no amendment.

## Results (all forms × sets)

| form | set | χ²/dof | R_true (″) | where | status |
|---|---|---|---|---|---|
| F1 dip-pivot prism | S1 | 694 | 957.86 | 4868 nm | inadequate |
| F2 free pivot | S1 | — | 954.64 | 344 nm | exactly determined |
| F3 floor | S1 | — | 959.570 | 617 nm | single point |
| F1 | S2 | 153 | 957.94 | 4868 nm | inadequate |
| F2 | S2 | 132 | 959.32 | 469 nm | inadequate |
| **F3** | **S2** | **3.45** | **959.589 ± 0.036** | **floor 536–1025 nm** | **adequate** |
| F1 | S3 | 98 | 957.94 | 4868 nm | inadequate |
| F2 | S3 | 112 | 957.59 | 6874 nm | inadequate |
| **F3** | **S3** | **3.45** | **959.589 ± 0.036** | **floor 536–1025 nm** | **adequate** |

## The real figure (by the registered rule)

**R_true = 959.589 ± 0.036″ at 1 AU = 695,962 ± 26 km.** It is seen across a flat floor that spans 536–1025 nm, the whole measured visible to near-IR. There is no single real wavelength: between the steep edges, every wavelength sees the same Sun.

## What the forms say about the prism
- **No parabola fits.** Neither the symmetric prism pivoted on the dips (F1) nor a free-pivot parabola (F2) is adequate on any multi-point set; χ²/dof runs from 98 to 694.
- **The bending is confined to the edges.** Apparent size rises steeply near the UV dip (961.8″ at 170 nm, 963.0″ at 160 nm) and stays flat across 536–1025 nm, where the spread is 0.3″, mostly the HMI–SODISM offset. The far-IR edge is unmeasured (677 nm – 742 µm), and the radio side, beyond the dip, is larger again (961–967″).
- **Shape:** flat floor, steep walls at the dips. This is the shape of Harvey's "bend them back down to the dips": the dips demarcate the edges, and inside them the Sun is undistorted.

## Context only (no criterion refers to these)

| reference | value | R_true minus reference |
|---|---|---|
| helioseismic (Schou 1997) | 959.200″ | **+0.389″ = +282 km** |
| IAU nominal | 959.228″ | +0.361″ |
| Auwers 1891 | 959.63″ | −0.041″ |

The +282 km against the seismic radius is the known "photospheric–seismic" gap (Haberreiter et al. 2008, about 300 km). The standard account attributes it to the limb inflection point sitting above τ = 1. In Harvey's reading it is the depth of the bending shell itself. The figure is recorded here; that mechanism is not tested.

## Limitations
- The floor value is dominated by HMI (σ = 0.02″). The SODISM points (959.78–959.88″, search readings) sit about 0.3″ higher; that offset is what gives χ²/dof = 3.45.
  - On HMI alone the floor is 959.570″.
  - On SODISM alone it is about 959.85″.
  - The floor is determined to about ±0.15″ between instruments, not ±0.04″.
- The far-IR wall and the region from 1 µm to 742 µm are unmeasured. The floor could continue, or dip, inside that gap.
- Limb definitions differ: transit limb against inflection point.

## Grade
- R_true from the floor: G2/G4 boundary. The value is computed; the instrument offset leaves it open at the ±0.15″ level.
- The edge-confined bending shape: G4 as a description (computed, not discriminating).
- Parabolic prisms (F1, F2): G1 as registered.

## Addendum A (2026-10-10): dip-ring ladders, the overlap wavelength, and a pre-registered far-IR radius

At Harvey's direction. Calculation only; nothing tested yet.

**Construction.** Each dip is seen as a ring around the Sun. Its radius starts an octave ladder, halved at each rung.
- UV dip radius: measured at 160 nm, 963.04″ = 698.46e6 m.
- Far-IR dip radius: from the published R(λ) fit at 150 µm, 960.355″ = 696.52e6 m. This is **extrapolated; never measured.**
- The ratio is 1.002796 (0.00403 octave). That is not a power of two, so **no rung of either ladder equals any rung of the other.**

**Overlap.** The two ladders come back into step every 358.66 UV steps (357.66 far-IR steps). That is the beat length R₁R₂/(R₁ − R₂) = **249.81e9 m (1.67 AU) at rung 0**, halving with the rungs. In the optical:
- rung 58: **866.71e-9 m**
- rung 59: **433.36e-9 m**

Sensitivity: ±0.1″ on the far-IR radius moves the overlap by ±3.7%.

**Ladders passing the dips.**
- Rung 52 (155.09e-9 / 154.66e-9 m) lies 1.8–2.1% below the 158 nm UV dip.
- Rung 42 (158.81e-6 / 158.37e-6 m) lies 3.6–5.6% above the far-IR dip (150–153.3 µm).
- Look-elsewhere: about 6% chance, counted once, because the dips sit 9.89 octaves apart.

**PRE-REGISTERED (2026-10-10, before any search for the measurement).**

Harvey's earlier 925–975 nm "real Sun" is placed here only as a conditional. If the rung-58 overlap of the two dip ladders falls in 925–975e-9 m, then the solar radius at the far-IR dip (about 150e-6 m) must be **960.51–960.64″ at 1 AU (696.635e6 – 696.728e6 m)**.

The published-fit extrapolation is 960.36″.
- **Confirmed** if a measured far-IR-dip radius lies in 960.51–960.64″ within its 2σ.
- **Rejected** if it lies outside by more than 2σ.

The UV-dip radius is held at the measured 963.04″. A remeasured UV value moves the band, and the band is then recomputed with the same rule, not refitted.

See also E109 §3: the far-IR dip position itself is unresolved.
