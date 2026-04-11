# Spation Deep Analysis — Cross-Normalisation & Connections

---

## 1. Cross-Normalisation of Power Laws

Short-side law: dR/R_sun = 0.00020403 * (lambda_0/lambda)^1.2344
Long-side law:  dR/R_sun = 7.5903e-05 * (lambda/lambda_0)^0.7552

### A. Short-side law extrapolated to long wavelengths

If the short-side coupling applied on the long side too,
long wavelengths would decouple at these radii:

```
Band                      R_actual   R_short     ratio
------------------------------------------------------
350 um (ALMA B10)           1.0050    1.1578    1.1520
1.3 mm (ALMA B6)            1.0100    1.7972    1.7794
3.0 mm (ALMA B3)            1.0150    3.2381    3.1903
2.0 cm                      1.1500   24.2766   21.1101
6.0 cm                      1.3000   91.3396   70.2612
20 cm                       1.7000  400.3188  235.4816
1.0 m                       3.0000 2912.5773  970.8591
3.0 m                       4.500011301.2174 2511.3817
10 m                       10.000049950.1754 4995.0175
```

### B. Long-side law extrapolated to short wavelengths

If the long-side coupling applied on the short side too,
short wavelengths would decouple at these radii:

```
Band                      R_actual    R_long     ratio
------------------------------------------------------
1.0 nm  (hard X)            1.5000    1.0200    0.6800
5.0 nm  (soft X)            1.3000    1.0059    0.7738
9.4 nm  (Fe XVIII)          1.2000    1.0037    0.8364
17.1 nm (Fe IX)             1.1000    1.0023    0.9112
30.4 nm (He II)             1.0500    1.0015    0.9538
121.6 nm (Ly-alpha)         1.0050    1.0005    0.9956
160 nm (C IV)               1.0030    1.0004    0.9974
280 nm (Mg II k)            1.0020    1.0003    0.9983
```

### C. Exponent ratio

```
Short exponent: 1.2344
Long exponent:  0.7552
Sum:            1.9896
Product:        0.9322
Ratio (s/l):    1.6345
Ratio (l/s):    0.6118

Sum ~ 1.99 (is this 2?  deviation = -0.52%)
Ratio ~ 1.63 (is this 5/3? deviation = -1.93%)
```

## 2. lambda_0 vs Recombination at 3000 K

```
Spation natural wavelength:
  lambda_0 = 1.600 um
  E_0      = 0.7749 eV
  f_0      = 1.8737e+14 Hz

Recombination at T = 3000 K:
  kT       = 0.2585 eV
  Wien peak: lambda_Wien = 0.966 um
  Wien peak: E_Wien      = 1.2836 eV

RATIOS:
  E_0 / kT            = 2.997452
  E_0 / (3kT)         = 0.999151
  lambda_Wien / lambda_0 = 0.603702
  E_0 / E_Wien        = 0.603702

Temperature where kT = E_0:  T = 8992 K
Temperature where 3kT = E_0: T = 2997 K

Temperature where Wien peak = lambda_0: T = 1811 K
```

### Interpretation

```
E_0 / kT = 3.00

The spation's natural wavelength has energy = 3.0 kT
at the recombination temperature.

E_0 = 3kT at 3000K to within 0.1%

3kT = total thermal energy per particle in 3 dimensions
    = kinetic + potential per degree of freedom * 3

The spation's natural wavelength carries the TOTAL
thermal energy of one particle at the Clearing.

At T=3000K, the Planck occupation number at lambda_0:
  n(lambda_0) = 1/(exp(hf/kT) - 1) = 1/(exp(3.00) - 1) = 0.052536
```

## 3. The 10,007 Seconds and the Spation

```
T_surface = 2*pi*R_sun / v_surface = 10007.8 s
          = (2*pi*R_sun/c) * k = 14.58 s * 686.37 = 10007.8 s

Distance light travels in T_surface:
  d = c * T = 3.0003e+12 m
  d / R_sun = 4312.56
  d / (2*pi*R_sun) = 686.37 = k
  d in AU = 20.06

Number of lambda_0 wavelengths in d:
  N = d / lambda_0 = 1.875157e+18

Number of lambda_0 in one circumference:
  N_circ = 2*pi*R_sun / lambda_0 = 2.732008e+15
  N / N_circ = 686.37 = k

T_surface / T_lambda0 = 1.875157e+18
  = N (same number — obvious: T_surf = N * T_lambda0)

THE CONNECTION TO DECOUPLING:

v(r) = (c/k)*sqrt(R_sun/r)
T_orbital(r) = 2*pi*r / v(r) = T_surface * (r/R_sun)^(3/2)

For each decoupling radius:

Band                       R/R_sun     T_orb (s)  T_orb/T_surf    N_lambda_0
----------------------------------------------------------------------------
1.0 nm  (hard X)            1.5000    1.8385e+04        1.8371    5.5118e+21
5.0 nm  (soft X)            1.3000    1.4834e+04        1.4822    8.8941e+20
9.4 nm  (Fe XVIII)          1.2000    1.3156e+04        1.3145    4.1957e+20
17.1 nm (Fe IX)             1.1000    1.1546e+04        1.1537    2.0242e+20
30.4 nm (He II)             1.0500    1.0768e+04        1.0759    1.0619e+20
121.6 nm (Ly-alpha)         1.0050    1.0083e+04        1.0075    2.4858e+19
160 nm (C IV)               1.0030    1.0053e+04        1.0045    1.8836e+19
280 nm (Mg II k)            1.0020    1.0038e+04        1.0030    1.0747e+19
550 nm (V-band)             1.0000    1.0008e+04        1.0000    5.4550e+18
1.6 um (H-band)             0.9980    9.9778e+03        0.9970    1.8695e+18
2.2 um (K-band)             0.9990    9.9928e+03        0.9985    1.3617e+18
350 um (ALMA B10)           1.0050    1.0083e+04        1.0075    8.6365e+15
1.3 mm (ALMA B6)            1.0100    1.0158e+04        1.0150    2.3426e+15
3.0 mm (ALMA B3)            1.0150    1.0234e+04        1.0226    1.0227e+15
2.0 cm                      1.1500    1.2342e+04        1.2332    1.8500e+14
6.0 cm                      1.3000    1.4834e+04        1.4822    7.4118e+13
20 cm                       1.7000    2.2182e+04        2.2165    3.3251e+13
1.0 m                       3.0000    5.2002e+04        5.1962    1.5590e+13
3.0 m                       4.5000    9.5533e+04        9.5459    9.5467e+12
10 m                       10.0000    3.1647e+05       31.6228    9.4876e+12

N_lambda_0 = how many of THIS wavelength fit in the
distance light travels during one LOCAL orbital period.
This is the 'coherence count' — how many oscillations
the photon makes per orbital cycle at its decoupling radius.
```

### The coherence count hypothesis

```
At the surface (lambda_0, R = 0.998 R_sun):
  T_orb = 9.9778e+03 s
  N_lambda_0 = 1.869534e+18

At R = 1.3 R_sun:
  T_orb = 1.4834e+04 s
  N(5nm)  = 8.894112e+20
  N(6cm)  = 7.411760e+13
  N(5nm)/N(6cm) = 1.2000e+07
  = 6cm/5nm = 1.2000e+07
  These are the SAME ratio — the coherence count
  separates by wavelength ratio, nothing else.

What is constant across the decoupling curve?
N_lambda * lambda = c * T_orb(R) = c * T_surf * (R/R_sun)^(3/2)
This is just the orbital circumference at each R.
The product N*lambda = const at each R is trivially the distance.

The NON-trivial question: why does lambda_d decouple at R_d?
The power law dR = A * |log(lambda/lambda_0)|^p tells us
the PRESSURE coupling. The 3/4 exponent on the long side
and the 5/4 exponent on the short side encode the spation
geometry in each direction from its natural frequency.
```
