# E42+E49: Hubble Tension and Dark Energy — Investigation Prompt

> **Classification**: Archival data analysis — cosmological model test
> **Experiment files**: E42_Hubble_Constant.md, E49_Dark_Energy.md
> **Data source**: Pantheon+ SN Ia catalogue, Planck CMB, BAO
> **Target**: Fit SN Ia data with pressure gradient model (no Λ, no expansion)

---

## 1. The Questions

**E42**: Can SDT explain the 8.4% Hubble tension (67.4 vs 73.04 km/s/Mpc) as a geometric consequence of sampling different parts of the convergence gradient?

**E49**: Can SDT fit the SN Ia Hubble diagram (distance modulus vs redshift) WITHOUT dark energy (Λ), using only the pressure-gradient redshift model?

## 2. Methodology

### Phase A: The SDT distance-redshift relation

In SDT, redshift is NOT Doppler. It is the wavelength stretching of photons (lattice deformations) traversing the convergence pressure gradient:

$$1 + z = \frac{T_{\text{emitted}}}{T_{\text{CMB}}} \approx e^{\sigma_0 d}$$

where σ₀ is the strain rate (= H₀/c in conventional units) and d is the physical distance.

For a non-uniform gradient (SDT prediction), σ depends on position:

$$1 + z = \exp\left(\int_0^d \sigma(x) \, dx\right)$$

The distance modulus is then:

$$\mu = 5 \log_{10}(d / 10 \text{pc})$$

### Phase B: Fit the Pantheon+ data

1. Download the Pantheon+ catalog (1701 SN Ia with corrected peak magnitudes and redshifts)
2. Fit two models:
   a. **ΛCDM**: μ(z) with Ω_m, Ω_Λ as free parameters (2 params)
   b. **SDT pressure gradient**: μ(z) with σ(d) = σ₀ × f(d/d₀) where f is a gradient profile function (2 params: σ₀, d₀)
3. Compare χ² for both models
4. Compute the difference in AIC/BIC (information criteria)

### Phase C: Hubble tension dissolution

In SDT, the "tension" is resolved because:
- Local SN Ia (z < 0.1) sample the STEEP part of the local pressure gradient
- CMB (z = 1100) samples the AVERAGE gradient over the full path
- SDT predicts H₀(local) > H₀(CMB) — exactly what is observed

Compute:
1. The expected σ_local / σ_CMB ratio from the density distribution of the local universe
2. Whether the 8.4% tension corresponds to the expected gradient steepness near the Milky Way supercluster

### Phase D: BAO scale test

The BAO scale (147 Mpc) is an independent distance ruler. SDT interprets BAO as a lattice equilibrium length (cosmology.hpp bao namespace), not as a frozen sound wave.

Compare:
- SDT-predicted BAO angular scale at each measured redshift
- vs measured BAO angular scale from BOSS/eBOSS/DESI
- vs ΛCDM prediction

## 3. Success Criteria

- [ ] Pantheon+ data fitted with SDT model
- [ ] χ²(SDT) within 10% of χ²(ΛCDM) → SDT is competitive
- [ ] Hubble tension reproduced as a gradient steepness effect
- [ ] BAO scale at z = 0.15–2.33 reproduced within 3%
- [ ] Zero dark energy used in SDT model
- [ ] If SDT fails at high z: identify where and the magnitude of failure
