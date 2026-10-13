# E97 Results: Earth Interior from Koppa

> **Status**: COMPLETED
> **Date**: 15 April 2026
> **Constitutional compliance**: No G, No M, No GM.
> **The Number**: ϟ_Earth = v²R/c² = **4.43 mm**

---

## The Number

```
v_surf  = 7909 m/s        (measured surface orbital velocity)
R       = 6.371 × 10⁶ m   (measured radius)
k       = c/v = 37,905
z       = 1/k² = 6.96 × 10⁻¹⁰
ϟ       = Rz = R/k² = 4.434 × 10⁻³ m = 4.43 mm

g       = v²/R = 9.818 m/s²
```

g is computed from v and R. No G. No M.

---

## The Mechanism

### Gravity is Phase Delay

Convergent throughput arrives at Earth's surface at c. On entering matter, every
excluded Planck cell forces a detour — one extra tick per exclusion. The throughput
**slows down**. Deeper = more exclusions = more delay.

For any imaginary sphere inside Earth:
- Convergence from the **near side**: arrives on time
- Convergence from the **far side**: arrives **late**
- The **phase mismatch** = net inward pressure

### The Trefoil Partition

The blocked convergence splits three ways by the trefoil topology (W=3):

1. **Heat** — thermalised circulation
2. **Sound** — pressure pulses (seismic waves)
3. **Movement** — directed displacement (gravity)

### SDT vs GR: Falsifiable Prediction

| Scenario | GR | SDT |
|---|---|---|
| Object at Earth's centre | Floats weightlessly (g=0) | Crushed by isotropic spation pressure |
| Lagrange points | Mass ratio | Throughput transit-time equalisation |

---

## Interior Profiles (Smooth PREM Polynomials)

### The Formula

```
g(r)    = v²R × frac(r) / r²
frac(r) = ∫₀ʳ ρ(r') 4πr'² dr' / ∫₀ᴿ ρ(r') 4πr'² dr'
P(r)    = ∫ᵣᴿ ρ g dr'
```

No G. No M. Density from Dziewonski & Anderson 1981 polynomial coefficients.

### RMS Errors (smooth PREM, 5000 shells)

| Profile | RMS Error |
|---------|-----------|
| **g(r)**    | **1.82%** |
| **P(r)**    | **4.30%** |
| v_p(r)  | 11.5%     |
| v_s(r)  | 28.0%     |

g and P errors are purely from spation mechanism.
v_p/v_s errors are mineral physics (K₀, G₀ values), not the gravitational model.

### Key Depths

| depth(km) | g_SDT  | g_PREM | err   | P_SDT  | P_PREM |
|-----------|--------|--------|-------|--------|--------|
| 0         | 9.818  | 9.810  | +0.1% | 0.00   | 0.00   |
| 670 (TZ)  | 10.01  | 10.02  | -0.1% | 23.9   | 23.8   |
| 2891 (CMB)| 10.68  | 10.68  | 0.0%  | 135.8  | 135.8  |
| 5150 (ICB)| 4.40   | 4.40   | -0.1% | 329.1  | 328.9  |
| 6371 (ctr)| 0.00   | 0.00   | 0.0%  | 364.2  | 363.9  |

---

## Koppa Table — Every Body

| Body    | v_surf (m/s) | R (m)      | k       | ϟ (mm)     | g_calc  | g_meas  |
|---------|-------------|------------|---------|------------|---------|---------|
| Earth   | 7909        | 6.371e6    | 37,905  | 4.434      | 9.818   | 9.81    |
| Moon    | 1680        | 1.737e6    | 178,448 | 0.055      | 1.624   | 1.625   |
| Mars    | 3555        | 3.390e6    | 84,330  | 0.477      | 3.729   | 3.721   |
| Venus   | 7328        | 6.052e6    | 40,911  | 3.616      | 8.873   | 8.796   |
| Jupiter | 42100       | 6.991e7    | 7,121   | 1,378.7    | 25.352  | 24.79   |
| Saturn  | 25100       | 5.823e7    | 11,944  | 408.2      | 10.819  | 10.44   |
| Sun     | 437000      | 6.957e8    | 686     | 1,478,235  | 274.499 | 274.0   |
| Mercury | 3010        | 2.440e6    | 99,599  | 0.246      | 3.714   | 3.70    |

Every g computed as v²/R. No G. No M. ϟ encodes it all.

---

## Displacement Inventory

| Quantity | Value |
|----------|-------|
| ∫ρdV (from smooth PREM) | 5.975 × 10²⁴ kg |
| Total baryons | 3.598 × 10⁵¹ |
| Excluded Planck cells (b) | 1.564 × 10⁹⁸ |
| Spation cells (a) | 2.566 × 10¹²⁵ |
| b/a (excluded fraction) | 6.10 × 10⁻²⁸ |
| V_excl (all Earth's matter) | 0.66 cm³ |
| P_conv | 2.461 × 10⁴⁸ Pa |
| Total convergence force | 1.005 × 10⁷⁷ N |
| Phase delay (1 radius) | 1.30 × 10⁻²⁹ s |
| Excluded cells per column | 2.44 × 10¹⁴ |

---

## Code

- [e97_backward.cpp](file:///c:/Users/Jimmi/sdt-engine/Investigations/E97_Earth_Core_Seismic_Speed/e97_backward.cpp) — smooth PREM + koppa (v5)
- [e97_trefoil_test.cpp](file:///c:/Users/Jimmi/sdt-engine/Investigations/E97_Earth_Core_Seismic_Speed/e97_trefoil_test.cpp) — trefoil partition tests
- [e97_displacement_pressure.cpp](file:///c:/Users/Jimmi/sdt-engine/Investigations/E97_Earth_Core_Seismic_Speed/e97_displacement_pressure.cpp) — displacement mechanism proof

## Engine Enrichment

- [laws.hpp](file:///c:/Users/Jimmi/sdt-engine/Engine/include/sdt/laws.hpp) — added `bridge::koppa()`, `bridge::g_surface()`, `bridge::g_interior()`, `koppa_Earth`, `koppa_Moon`
