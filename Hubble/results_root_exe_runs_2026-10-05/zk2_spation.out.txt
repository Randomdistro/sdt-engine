# Spation Geometry from Solar Multi-Wavelength Radii

> Full mathematical analysis of the wavelength-dependent
> solar radius as a map of spation compression.

> Anchor: z_sun = 2.1227e-06, R_sun = 6.957e+08 m
> kappa_sun = R*z = 1476.76 m (invariant)

---

## 1. Decoupling Radii by Wavelength

```
Band                          lambda   R/R_sun          z(R)      k(R)   v_surf(m/s)  dR/R_sun
----------------------------------------------------------------------------------------------
1.0 nm  (hard X)              1.0 nm    1.5000    1.4151e-06    840.62    3.5663e+05   +0.5000
5.0 nm  (soft X)              5.0 nm    1.3000    1.6328e-06    782.58    3.8308e+05   +0.3000
9.4 nm  (Fe XVIII)            9.4 nm    1.2000    1.7689e-06    751.88    3.9873e+05   +0.2000
17.1 nm (Fe IX)              17.1 nm    1.1000    1.9297e-06    719.87    4.1646e+05   +0.1000
19.5 nm (Fe XII)             19.5 nm    1.0800    1.9655e-06    713.29    4.2029e+05   +0.0800
30.4 nm (He II)              30.4 nm    1.0500    2.0216e-06    703.32    4.2626e+05   +0.0500
0.12 um (Ly-alpha)          121.6 nm    1.0050    2.1121e-06    688.08    4.3569e+05   +0.0050
0.16 um (C IV)              160.0 nm    1.0030    2.1164e-06    687.39    4.3613e+05   +0.0030
0.28 um (Mg II k)           280.0 nm    1.0020    2.1185e-06    687.05    4.3635e+05   +0.0020
0.36 um (U-band)            360.0 nm    1.0008    2.1210e-06    686.64    4.3661e+05   +0.0008
0.45 um (B-band)            450.0 nm    1.0005    2.1216e-06    686.54    4.3667e+05   +0.0005
0.55 um (V-band)            550.0 nm    1.0000    2.1227e-06    686.37    4.3678e+05   +0.0000
0.66 um (R-band)            660.0 nm    1.0000    2.1227e-06    686.37    4.3678e+05   +0.0000
0.85 um (z-band)            850.0 nm    0.9998    2.1231e-06    686.30    4.3683e+05   -0.0002
1.6 um (H-band)              1.60 um    0.9980    2.1270e-06    685.68    4.3722e+05   -0.0020
2.2 um (K-band)              2.20 um    0.9990    2.1248e-06    686.02    4.3700e+05   -0.0010
4.7 um (M-band)              4.70 um    0.9995    2.1238e-06    686.19    4.3689e+05   -0.0005
0.35 mm (ALMA B10)         350.00 um    1.0050    2.1121e-06    688.08    4.3569e+05   +0.0050
0.85 mm (ALMA B7)          850.00 um    1.0070    2.1079e-06    688.76    4.3526e+05   +0.0070
1.3 mm  (ALMA B6)             1.3 mm    1.0100    2.1017e-06    689.79    4.3461e+05   +0.0100
3.0 mm  (ALMA B3)             3.0 mm    1.0150    2.0913e-06    691.49    4.3354e+05   +0.0150
2.0 cm                          2 cm    1.1500    1.8458e-06    736.05    4.0730e+05   +0.1500
6.0 cm                          6 cm    1.3000    1.6328e-06    782.58    3.8308e+05   +0.3000
20 cm                          20 cm    1.7000    1.2486e-06    894.91    3.3500e+05   +0.7000
50 cm                          50 cm    2.2000    9.6486e-07   1018.05    2.9448e+05   +1.2000
1.0 m                            1 m    3.0000    7.0757e-07   1188.82    2.5218e+05   +2.0000
2.0 m                            2 m    3.8000    5.5861e-07   1337.97    2.2406e+05   +2.8000
3.0 m                            3 m    4.5000    4.7171e-07   1456.00    2.0590e+05   +3.5000
5.0 m                            5 m    6.0000    3.5378e-07   1681.25    1.7832e+05   +5.0000
10 m                            10 m   10.0000    2.1227e-07   2170.48    1.3812e+05   +9.0000
```

## 2. The Opacity Minimum — Spation Natural Wavelength

The minimum apparent radius occurs at:

```
lambda_0 = 1.6000 um
R/R_sun  = 0.9980
```

This is the wavelength that propagates MOST EFFICIENTLY
through the spation lattice. It sees deepest into the
pressure gradient. Both shorter AND longer wavelengths
decouple at larger radii.

```
f_0     = c/lambda_0 = 1.8737e+14 Hz
T_0     = lambda_0/c = 5.3370e-15 s
E_0     = hf_0 = 1.2415e-19 J = 0.7750 eV
kappa/lambda_0 = 9.229765e+08
```

## 3. Power Law Analysis

### Short side (lambda < lambda_0): UV/EUV/X-ray

Fit: log10(R/R_sun - 1) = -3.6903 + 1.2344 * log10(lambda_0/lambda)

```
Exponent (short side): 1.2344
R-squared:             0.940670
Amplitude (10^a):      2.0403e-04

=> dR/R_sun = 2.0403e-04 * (lambda_0/lambda)^1.234
```

Residuals:
```
1.0 nm  (hard X)          actual=-0.3010  pred=0.2648  diff=-0.5658
5.0 nm  (soft X)          actual=-0.5229  pred=-0.5980  diff=+0.0751
9.4 nm  (Fe XVIII)        actual=-0.6990  pred=-0.9364  diff=+0.2374
17.1 nm (Fe IX)           actual=-1.0000  pred=-1.2572  diff=+0.2572
19.5 nm (Fe XII)          actual=-1.0969  pred=-1.3276  diff=+0.2307
30.4 nm (He II)           actual=-1.3010  pred=-1.5656  diff=+0.2646
0.12 um (Ly-alpha)        actual=-2.3010  pred=-2.3088  diff=+0.0078
0.16 um (C IV)            actual=-2.5229  pred=-2.4559  diff=-0.0670
0.28 um (Mg II k)         actual=-2.6990  pred=-2.7559  diff=+0.0570
0.36 um (U-band)          actual=-3.0969  pred=-2.8907  diff=-0.2063
0.45 um (B-band)          actual=-3.3010  pred=-3.0103  diff=-0.2908
```

### Long side (lambda > lambda_0): Radio

Fit: log10(R/R_sun - 1) = -4.1197 + 0.7552 * log10(lambda/lambda_0)

```
Exponent (long side):  0.7552
R-squared:             0.991341
Amplitude (10^a):      7.5903e-05

=> dR/R_sun = 7.5903e-05 * (lambda/lambda_0)^0.755
```

Residuals:
```
0.35 mm (ALMA B10)        actual=-2.3010  pred=-2.3525  diff=+0.0515
0.85 mm (ALMA B7)         actual=-2.1549  pred=-2.0615  diff=-0.0934
1.3 mm  (ALMA B6)         actual=-2.0000  pred=-1.9221  diff=-0.0779
3.0 mm  (ALMA B3)         actual=-1.8239  pred=-1.6479  diff=-0.1760
2.0 cm                    actual=-0.8239  pred=-1.0256  diff=+0.2017
6.0 cm                    actual=-0.5229  pred=-0.6653  diff=+0.1424
20 cm                     actual=-0.1549  pred=-0.2704  diff=+0.1155
50 cm                     actual=0.0792  pred=0.0302  diff=+0.0490
1.0 m                     actual=0.3010  pred=0.2575  diff=+0.0435
2.0 m                     actual=0.4472  pred=0.4848  diff=-0.0377
3.0 m                     actual=0.5441  pred=0.6178  diff=-0.0738
5.0 m                     actual=0.6990  pred=0.7854  diff=-0.0864
10 m                      actual=0.9542  pred=1.0127  diff=-0.0585
```

## 4. Spation Geometry

### The natural wavelength

```
lambda_0 = 1.6 um = 1.6e-6 m

This is where the spation is 'transparent' — the wavelength
that couples LEAST to the lattice. The spation geometry
selects this wavelength for maximum penetration.

kappa / lambda_0 = 9.229765e+08
This is the number of natural wavelengths in one kappa length.

Light circumference periods / lambda_0 periods:
  (2*pi*R_sun/c) / (lambda_0/c) = 2*pi*R_sun/lambda_0
  = 2.732008e+15
```

## 5. Pressure Gradient Profile

At each decoupling radius r, the displacement z(r) gives
the local pressure. The mapping R(lambda) therefore gives
the pressure at which each wavelength becomes free:

```
Band                         R/R_sun          z(R)       z/z_sun      dz/z_sun
------------------------------------------------------------------------------
1.0 nm  (hard X)              1.5000    1.4151e-06      0.666667     +0.333333
5.0 nm  (soft X)              1.3000    1.6328e-06      0.769231     +0.230769
9.4 nm  (Fe XVIII)            1.2000    1.7689e-06      0.833333     +0.166667
17.1 nm (Fe IX)               1.1000    1.9297e-06      0.909091     +0.090909
19.5 nm (Fe XII)              1.0800    1.9655e-06      0.925926     +0.074074
30.4 nm (He II)               1.0500    2.0216e-06      0.952381     +0.047619
0.12 um (Ly-alpha)            1.0050    2.1121e-06      0.995025     +0.004975
0.16 um (C IV)                1.0030    2.1164e-06      0.997009     +0.002991
0.28 um (Mg II k)             1.0020    2.1185e-06      0.998004     +0.001996
0.36 um (U-band)              1.0008    2.1210e-06      0.999201     +0.000799
0.45 um (B-band)              1.0005    2.1216e-06      0.999500     +0.000500
0.55 um (V-band)              1.0000    2.1227e-06      1.000000     +0.000000
0.66 um (R-band)              1.0000    2.1227e-06      1.000000     +0.000000
0.85 um (z-band)              0.9998    2.1231e-06      1.000200     -0.000200
1.6 um (H-band)               0.9980    2.1270e-06      1.002004     -0.002004
2.2 um (K-band)               0.9990    2.1248e-06      1.001001     -0.001001
4.7 um (M-band)               0.9995    2.1238e-06      1.000500     -0.000500
0.35 mm (ALMA B10)            1.0050    2.1121e-06      0.995025     +0.004975
0.85 mm (ALMA B7)             1.0070    2.1079e-06      0.993049     +0.006951
1.3 mm  (ALMA B6)             1.0100    2.1017e-06      0.990099     +0.009901
3.0 mm  (ALMA B3)             1.0150    2.0913e-06      0.985222     +0.014778
2.0 cm                        1.1500    1.8458e-06      0.869565     +0.130435
6.0 cm                        1.3000    1.6328e-06      0.769231     +0.230769
20 cm                         1.7000    1.2486e-06      0.588235     +0.411765
50 cm                         2.2000    9.6486e-07      0.454545     +0.545455
1.0 m                         3.0000    7.0757e-07      0.333333     +0.666667
2.0 m                         3.8000    5.5861e-07      0.263158     +0.736842
3.0 m                         4.5000    4.7171e-07      0.222222     +0.777778
5.0 m                         6.0000    3.5378e-07      0.166667     +0.833333
10 m                         10.0000    2.1227e-07      0.100000     +0.900000
```

z/z_sun = 1/R_ratio = displacement fraction relative to photosphere.
Short wavelengths (X-ray) decouple at z = 0.77 z_sun (23% pressure drop).
Long wavelengths (10m radio) decouple at z = 0.10 z_sun (90% pressure drop).

## 6. Short-vs-Long Asymmetry

The decoupling curve is NOT symmetric about lambda_0.

### Same R/R_sun, different lambdas:

```
R/R_sun ~ 1.005:  short=1.22e-07 m  long=3.50e-04 m  ratio=2.878e+03
R/R_sun ~ 1.010:  short=1.22e-07 m  long=1.30e-03 m  ratio=1.069e+04
R/R_sun ~ 1.050:  short=3.04e-08 m  long=3.00e-03 m  ratio=9.868e+04
R/R_sun ~ 1.100:  short=1.71e-08 m  long=2.00e-02 m  ratio=1.170e+06
R/R_sun ~ 1.300:  short=5.00e-09 m  long=6.00e-02 m  ratio=1.200e+07
```

The ratio between the long-side and short-side wavelengths
at each R/R_sun tells us how ASYMMETRICALLY the spation
couples to wavelengths above vs below its natural frequency.

## 7. Key Identity: k * lambda_0

```
k_sun * lambda_0 = 686.37 * 1.60e-06 = 1.098185e-03 m

v_surface = c/k = 436782.3 m/s
lambda_0 * c / v_surface = lambda_0 * k = 1.098185e-03 m
                                         = 1.0982 mm

This is the wavelength that lambda_0 BECOMES when Doppler-
shifted by the surface orbital velocity. It maps the
spation's natural wavelength into the displacement frame.
```
