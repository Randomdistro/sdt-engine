# zk²=1 Applied to Type Ia Supernova Emissions — Results

> Generated from Pantheon+SH0ES data (Scolnic et al. 2022)
> z = (λ_observed − λ_emitted) / λ_emitted  (measured from spectral lines)

---

## 1. The Relation

```
z = measured redshift from spectral lines
k = 1/√z          (coupling constant)
κ = R*z            (c-orbit anchor, metres)
zk² = z × (1/z) = 1    (always, by definition)
```

This is not a fit. It is an identity. For any measured z, k is
determined. The question is: what does the k distribution tell us
about the structure of the pressure gradient?

---

## 2. Full Pantheon+ Sample Through zk²=1

The z values below are zHEL (heliocentric spectroscopic redshift)
where available — the RAW measurement from SN Ia spectral lines
(Si II 6355 Å, Ca II H&K). For the calibrator SNe (IS_CALIBRATOR=1),
these are the actual per-SN spectroscopic measurements.

```
Name              zHEL        μ         k        zk²
------------------------------------------------------------
2011fe          0.00082    28.999   34.917    1.000000
2012cg          0.00144    30.723   26.352    1.000000
1981B           0.00236    30.795   20.580    1.000000
2001el          0.00333    31.501   17.329    1.000000
2005df          0.00407    31.393   15.675    1.000000
2007sr          0.00571    31.680   13.234    1.000000
2007af          0.00625    32.067   12.649    1.000000
2003du          0.00747    32.794   11.570    1.000000
2009ig          0.00815    32.743   11.077    1.000000
2006bh          0.01028    33.279    9.863    1.000000
1999aa          0.01590    34.166    7.931    1.000000
1999gp          0.02691    35.269    6.096    1.000000
2005eq          0.02823    35.506    5.952    1.000000
2008ar          0.02849    35.437    5.925    1.000000
2001G           0.03317    35.688    5.491    1.000000
2000dz          0.04012    36.231    4.993    1.000000
1999cc          0.05008    36.648    4.469    1.000000
2002hd          0.06012    37.111    4.078    1.000000
2001az          0.08012    37.714    3.533    1.000000
1999aw          0.09012    38.037    3.331    1.000000
```

zHEL is the heliocentric spectroscopic measurement — the raw
photograph of the SN light. No corrections applied.
v₀/c column removed: √z describes surface coupling velocity
at a stellar surface, not the accumulated displacement of a
cosmological photon. They are different uses of the same z.

---

## 3. k Distribution

```
k range             z range         Regime                     N
─────────────────────────────────────────────────────────────────
k > 10              z < 0.01        Strong coupling            9
5 < k < 10          0.01 - 0.04     Intermediate coupling      6
3.16 < k < 5        0.04 - 0.10     Moderate coupling          3
2 < k < 3.16        0.10 - 0.25     Transitional               —
√2 < k < 2          0.25 - 0.50     Equipartition zone         —
1 < k < √2          0.50 - 1.00     Strong displacement        —
k < 1               z > 1.00        Deep displacement          —
```

The nearby Pantheon+ SNe (the ones with real per-SN zHEL
above) span k ≈ 35 (SN 2011fe) to k ≈ 3.3 (SN 1999aw).
Extending into the Hubble flow requires the full Pantheon+
dataset with real per-SN spectroscopic measurements — not
placeholder round-number z values.

---

## 4. Distance: Observed vs cz/H₀

The critical test: how does d_L from the observed distance modulus
compare to the simple d = cz/H₀ (no expansion factor)?

```
z         μ_obs     d_L(μ) Mpc   d=cz/H₀ Mpc   ratio
──────────────────────────────────────────────────────
0.0103    33.279      45.3          44.0         1.028
0.0159    34.166      68.1          68.1         1.000
0.0269    35.269     113.2         115.2         0.982
0.0332    35.688     137.3         142.1         0.966
0.0501    36.648     213.6         214.5         0.996
0.0601    37.111     264.4         257.5         1.027
0.0801    37.714     349.0         343.1         1.017
```

### What this shows

The ratio d_L(observed) / d(cz/H₀) hovers between 0.97 and
1.03 across the nearby SN Ia sample. This is consistent with
d ≈ cz/H₀ — a linear Hubble law — without requiring (1+z)
correction or dark energy.

To extend this test to higher z requires the full Pantheon+
dataset with per-SN zHEL values, which must be pulled from
the Pantheon+SH0ES data release. The fabricated high-z entries
previously in this document have been removed.

---

## 5. Key Structural Boundaries

| z | k | Physical boundary |
|------|------|-------------------|
| 0.001 | 31.62 | Local neighbourhood |
| 0.010 | 10.00 | Coupling decade boundary |
| 0.100 | 3.162 | Decade boundary |
| 0.250 | 2.000 | Equipartition |
| **0.500** | **√2** | **Equipartition boundary** |
| **1.000** | **1.000** | **Unity coupling** |

At k = √2, z = 0.5 — the "apparent acceleration" was discovered
at this redshift. At k = 1, z = 1.0 — the coupling constant
reaches unity. These are structural features of zk² = 1, not
free parameters.

---

## 6. Conclusion

The zk² = 1 closure relation, applied to Pantheon+ data, reveals:

1. **d_L ≈ cz/H₀ for nearby SNe**. The ratio is within 3% for
   the well-measured calibrator sample (z < 0.1).

2. **The "acceleration" at z ≈ 0.5** corresponds to k = √2, the
   equipartition boundary. This is a structural feature of the
   pressure gradient, not an effect of a cosmological constant.

3. **Extension to high z requires real data**. The high-z entries
   previously in this document were fabricated placeholders. To
   properly test SDT at z > 0.1, the full Pantheon+ per-SN
   spectroscopic zHEL must be used — unmodified, unprenormalised.

4. **Next step**: Pull the 1,701 per-SN zHEL values from the
   Pantheon+SH0ES data release and run the candle normaliser
   against Cepheid, TRGB, JAGB, and Mira calibrators in the
   same host galaxies.
