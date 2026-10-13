# E46: Galaxy Rotation Curves from Eclipse Saturation — Investigation Prompt

> **Classification**: Archival data analysis — the dark matter test
> **Experiment file**: Experiments/E46_Galaxy_Rotation_Curves_from_Eclipse_Saturation.md
> **Data source**: SPARC database (175 galaxies)
> **Target**: Explain flat rotation curves without dark matter

---

## 1. The Question

Galaxy rotation curves are flat at large radii: v(r) → constant instead of falling as r^(-1/2). Standard physics invokes dark matter halos. SDT explains this through **eclipse saturation**: beyond a critical radius, the convergence pressure is fully occluded by the visible disk, and further material experiences a saturated (constant) pressure deficit → constant orbital velocity.

Can SDT's eclipse saturation model reproduce the measured rotation curves for 50+ galaxies from the SPARC database using ONLY the visible baryonic mass, with ZERO free parameters?

## 2. Methodology

### Phase A: The eclipse saturation model

1. At any radius r in the galactic plane, the convergence pressure arrives from all 4π steradians
2. The galactic disk OCCLUDES a fraction of this convergence
3. At small r (inside the disk): occlusion grows with r → v(r) rises
4. At large r: the entire disk subtends a solid angle Ω_disk → if Ω_disk ≥ 2π, the convergence deficit from the disk direction is SATURATED
5. Beyond saturation: v(r) = constant = v_flat

The transition radius where Ω_disk ≈ 2π can be computed from the disk scale length h and scale height z₀:

$$r_{\text{sat}} \approx h \times \Sigma_0 / \Sigma_{\text{crit}}$$

where Σ_crit is the surface density at which the disk becomes convergence-opaque.

### Phase B: Compute SDT rotation curves

For each SPARC galaxy:
1. Take the baryonic surface density profile Σ(r) = Σ_disk(r) + Σ_gas(r)
2. At each radius r, compute the solid angle subtended by ALL baryonic material inside r (treated as an extended occlusion screen)
3. The convergence deficit at r determines v(r)²:
   - Below saturation: v(r)² ∝ integrated occlusion ∝ M_bar(< r) / r (Keplerian)
   - At saturation: v² → constant
4. The flat velocity should be: v_flat² = GM_bar,total × f(geometry) where f encodes the saturation

### Phase C: Fit-free comparison

For each galaxy, compute:
- V_SDT(r) from the baryonic mass profile + eclipse saturation model
- Compare to V_obs(r)
- Compute residuals: (V_obs − V_SDT) / V_obs

### Phase D: The BTFR test

The Baryonic Tully-Fisher Relation (BTFR): M_bar ∝ v_flat⁴
- Standard: this requires fine-tuning of dark matter halos
- SDT: this should emerge NATURALLY from eclipse saturation geometry
- Verify: does the SDT model predict BTFR with the correct normalization?

## 3. Required Outputs

1. **Rotation curve fits**: SDT vs observed for ≥50 SPARC galaxies
2. **Residual statistics**: Mean, RMS, and scatter of (V_obs − V_SDT)/V_obs
3. **BTFR plot**: M_bar vs v_flat⁴ from SDT model
4. **Comparison**: SDT model accuracy vs NFW dark matter halo accuracy vs MOND accuracy
5. **Eclipse saturation diagram**: Showing how the solid angle saturates at r_sat

## 4. Success Criteria

- [ ] ≥50 galaxies fitted
- [ ] RMS residual < 20% (comparable to dark matter models)
- [ ] BTFR reproduced with correct slope (≈4) and normalization
- [ ] Zero free parameters (no dark matter halo mass or concentration fitted)
- [ ] If SDT fails for a galaxy class: identify which class and why
