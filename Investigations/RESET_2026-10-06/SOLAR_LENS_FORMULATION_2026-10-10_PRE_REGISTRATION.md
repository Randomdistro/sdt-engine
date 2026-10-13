# Displaced space as the solar prism: formulation, round 1 (pre-registration, 2026-10-10)

## Direction and thesis

**Direction (Harvey, 2026-10-10):** "proceed with the formulation investigation for displaced space to produce this effect."

The effect, measured in rounds 1 and 2:
- a flat floor of apparent solar radius across 536–1025 nm (959.59″);
- steep walls near the UV dip (961.76″ at 170 nm, 963.04″ at 160 nm);
- a raised radio side (961–967″ at 1.3–3 mm);
- the 677 nm – 742 µm gap is unmeasured.

**Thesis (Harvey).** The Sun excludes the spation medium over a gradient. The medium carries the Sun's ring one spation to the next at its pressure depth. A prism separates impulses because the constrained medium passes them along a straight angle through an effectively circular expression. Tunnelling is the same action with most impulses not getting through.

Notation: Ѻ = R/k².

## Step 1: geometry (DERIVED; no free parameter)

Least relay time in a spherically stratified index n(r, λ) (OP01 H2: Fermat) conserves n·r·sinθ along each ray. A ray leaving the boundary tangentially (the limb) therefore arrives with impact parameter b = n(R_t, λ)·R_t. So:

**R_app(λ) = n(R_t, λ)·R_t, and therefore n(R_t, λ) − 1 = R_app(λ)/R_t − 1.**

This is the renormalisation:
- the apparent-size spectrum is a direct readout of the displaced-space index at the boundary;
- the path to the observer adds nothing beyond the tangent-point index.

## Step 2: magnitude (computed before any fit; listed)

The index excess the data require, with R_t between the seismic radius (959.20″) and the floor (959.59″):
- floor: 0 to 4.1e-4
- 170 nm: 2.3e-3 to 2.7e-3
- 160 nm: 3.6e-3 to 4.0e-3
- radio: 1.6e-3 to 7.6e-3

Native candidates at the photosphere:
- **Gravitational depth.** z = Ѻ/R = 2.12e-6. The index n = 1/(1 − z) moves the limb by Ѻ = 1.48e3 m (0.002″). **Short by 10²–10³.**
- **Law-IV exclusion fraction.** n_b·V_disp, with V_disp = 3m_p c²/P_conv = 1.8e-58 m³ per baryon. At the photosphere (n_b ≈ 1e23 m⁻³, a model-atmosphere value) this is about 1e-35. **Negligible.**

Conclusion fixed now: the size of the effect is not a smooth depth term. It has to come from **walls at the dips**, an index that diverges as λ approaches a dip. This is the "nulls sit where s(λ) diverges" structure of E109 §10. Between the walls, the floor is the boundary seen with almost no bending.

## Step 3: the form tested (two walls at the dips)

**Linearised index**, valid while |n² − 1| ≪ 1:
n² = 1 + A·f(λ; λ_U) + B·f(λ; λ_I), with f(λ; p) = λ²/(λ² − p²).

So R_app = R_t + a·f(λ; λ_U) + b·f(λ; λ_I), with a = R_t·A/2 and b = R_t·B/2.

This is the general form of a wall: a term that diverges at p, positive on the long side and negative on the short side. Each wall is a seat where the medium's relay locks at that wavelength. The correspondence with resonance (Sellmeier) dispersion is noted, but the origin stated here is the dip.

- **F2a (walls fixed at the dips).** λ_U = 158 nm, λ_I = 150 µm. Fitted: R_t, a, b (3 parameters).
- **F2b (UV wall position free).** λ_I = 150 µm. Fitted: R_t, a, b and λ_U (4 parameters, scanned on a grid of 100–158 nm in 0.1 nm steps).
  - **Seen before registration (hand calculation):** a single wall through the 160/170 nm pair sits at about 146 nm, not 158 nm. F2b is registered with that knowledge, and the result is reported as "the UV wall the data place".

**Adequacy and comparison.**
- Report χ²/dof and AIC for F2a, F2b and the round-2 floor (F3, 1 parameter on its 5 points).
- A form with χ²/dof > 10 is inadequate.
- The HMI/SODISM offset (about 0.3″) limits every form, and is reported again.

## Step 4: what the form predicts where nothing is measured (registered now; computed from the fit; not tested)

Just short of each wall, n² falls below zero. The medium does not carry the impulse there: it is evanescent, the impulse "tunnels" rather than propagates, and the limb drops out.
- **Prediction P1:** the band below the far-IR wall where n² < 0, with its edges in m. This is the vanish band of the 17 June 2026 claim.
- **Prediction P2:** R_app across 1–150 µm, including its minimum, below the floor, as the wall is approached from the short side.
- **Prediction P3:** the band below the UV wall where n² < 0.

These are printed from the fit, and are what a measured R(λ) in the gap would test.

## Step 5: open, not computed here

The native origin of the wall strengths A and B, the size of the medium's response at each seat, is not computed here. Candidates to formulate next:
- spation pressure-depth loading by matter (E109's "medium's seats");
- the throughput fraction redirected at the boundary.

The fitted A and B are therefore CALIBRATED(2) in F2a, CALIBRATED(3) in F2b.

## Instrument

`solar_renormalisation/solar_lens_form_1.cpp`, on the round-1 data table.

**Validations:**
- V1: the linear 3-parameter fit recovers a constructed (R_t, a, b).
- V2: the grid scan recovers a constructed λ_U.
- V3: f(λ; p) sign checks on each side of p.
- V4: the evanescent band edges of a constructed n² match the analytic roots.

Single pass.
