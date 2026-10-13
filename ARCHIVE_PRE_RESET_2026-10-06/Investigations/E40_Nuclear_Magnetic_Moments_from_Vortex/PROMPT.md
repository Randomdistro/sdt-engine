# E40: Nuclear Magnetic Moments from Vortex Geometry — Investigation Prompt

> **Classification**: Theoretical derivation + archival validation
> **Experiment file**: Experiments/E40_Nuclear_Magnetic_Moments_from_Vortex_Geometry.md
> **Target**: Derive μ for p, n, d, t, He-3, He-4 from toroidal circulation

---

## 1. The Question

The proton's magnetic moment is +2.793 μ_N — anomalous (not 1.0) because it is not a point charge. The neutron has μ = −1.913 μ_N despite being neutral. Standard physics explains these via quark substructure. SDT must explain them from the W=3 trefoil torus circulation.

## 2. Methodology

### Step 1: Magnetic moment from circulation

A current loop produces a magnetic moment μ = IA. For a torus:
- The toroidal circulation (v_T, around the major axis) generates a poloidal magnetic moment
- The poloidal circulation (v_P, around the minor axis) generates a toroidal magnetic moment

For the proton (charged, W=3):
- The charge circulates with the torus flow
- μ_proton = contribution from ALL three circulation modes
- The W=3 trefoil means the charge traces the torus 3 times poloidally per toroidal circuit
- This amplifies the magnetic moment by a factor related to W

### Step 2: Derive μ_proton

$$\mu_p = \frac{e}{2m_p c} \times g_p \times (\text{mode structure factor})$$

Where g_p is the Landé g-factor. SDT predicts g_p from the trefoil geometry:
- g_p = (W+1)/2 × (v_P/v_T ratio) × (helicity correction)
- Must give g_p = 5.586 (since μ_p = g_p × μ_N / 2 = 2.793)

### Step 3: Derive μ_neutron

The neutron has the SAME W=3 topology but NO net charge. However, its internal circulation generates charge separation:
- The neutron's trefoil has regions of + and − charge density (measured)
- The circulating charge distribution generates a NET magnetic moment
- The sign is NEGATIVE because the charge distribution's centroid is opposite to the proton's

SDT must explain:
- Why μ_n / μ_p ≈ −2/3 (is this a geometric ratio from the trefoil?)
- Why the neutron has a negative moment (the charge distribution is inverted)

### Step 4: Composite nuclei

For d (p+n), t (p+2n), He-3 (2p+n):
- Add the constituent moments vectorially
- Account for the relative spin orientations in the ground state
- μ_d should ≈ μ_p + μ_n = 0.880 (measured: 0.857 — 2.6% off → exchange current correction in standard model; what is the SDT equivalent?)

### Step 5: Schmidt limits comparison

Standard nuclear physics has the Schmidt limits: μ_free_nucleon applied to single-particle states. SDT should reproduce these from the vortex geometry of the scaffold.

## 3. Required Outputs

1. **μ_proton derivation**: From W=3 trefoil geometry → 2.793 μ_N
2. **μ_neutron derivation**: From charge-separated W=3 → −1.913 μ_N
3. **Composite nuclei table**: Predicted vs measured for d, t, He-3, He-4
4. **μ_n/μ_p ratio**: Is −2/3 a geometric consequence of the trefoil?
5. **Prediction for heavier nuclei**: Using grammar (d+t block structure), predict moments for Li-7, Be-9, etc.

## 4. Success Criteria

- [ ] μ_proton reproduced within 5% from geometric argument
- [ ] μ_neutron sign (negative) and magnitude explained
- [ ] μ_n/μ_p ratio explained geometrically
- [ ] Deuteron moment predicted within 5%
- [ ] α moment = 0 explained by tetrahedral cancellation
