# Sun — Planetary System

## Host: Sun

```
R       = 6.9570e+08 m
z       = 2.122700e-06
k       = 686.37
v_surf  = 436782.3 m/s (0.001457 c)
kappa   = 1476.7624 m
T_surf  = 10007.76 s
sqrt(T) = 100.0388
T_rot   = 2192832.00 s (609.1200 h)
T_rot / T_surf = 219.113180

c * T_surf = 3.0003e+12 m = 20.0554 AU
c * T_surf / (2*pi*R) = 686.37 = k
```

## Satellites — Raw

```
Moon                     a (m)  a/R_host         P (s)    P/T_surf sqrt(P/T)  v_orb(m/s) v_pred(m/s)  v_err%
------------------------------------------------------------------------------------------------------------
Mercury              5.791e+10     83.24     7.600e+06    759.4107   27.5574     47876.2     47873.9   +0.00
Venus                1.082e+11    155.53     1.941e+07   1939.4951   44.0397     35025.3     35023.7   +0.00
Earth                1.496e+11    215.04     3.156e+07   3153.5530   56.1565     29783.4     29785.9   -0.01
Mars                 2.279e+11    327.58     5.936e+07   5931.3975   77.0156     24122.9     24132.6   -0.04
Jupiter              7.785e+11   1119.02     3.744e+08  37410.9711  193.4192     13064.8     13057.1   +0.06
Saturn               1.434e+12   2061.23     9.295e+08  92877.9316  304.7588      9693.5      9620.6   +0.76
```

## Satellites — Normalised to T_surf and R_host

```
Moon                   a/R    P/T_surf   (a/R)^(3/2)    match%    v/v_surf   1/sqrt(a/R)    match%
--------------------------------------------------------------------------------------------------
Mercury              83.24    759.4107      759.4468   100.005    0.109611      0.109606    99.995
Venus               155.53   1939.4951     1939.5808   100.004    0.080189      0.080186    99.996
Earth               215.04   3153.5530     3153.2934    99.992    0.068188      0.068194   100.008
Mars                327.58   5931.3975     5929.0277    99.960    0.055229      0.055251   100.040
Jupiter            1119.02  37410.9711    37433.0247   100.059    0.029911      0.029894    99.941
Saturn             2061.23  92877.9316    93581.6551   100.758    0.022193      0.022026    99.248
```

## Cross-normalised to Solar T_surface (10007.8 s)

```
Moon              P/T_sun_surf  P/T_jup_surf         ratio
----------------------------------------------------------
Mercury               759.4107      759.4107      1.000000
Venus                1939.4951     1939.4951      1.000000
Earth                3153.5530     3153.5530      1.000000
Mars                 5931.3975     5931.3975      1.000000
Jupiter             37410.9711    37410.9711      1.000000
Saturn              92877.9316    92877.9316      1.000000

T_jup_surf / T_sun_surf = 1.000000
k_jup / k_sun = 1.0000
```

## Moon-to-Moon Period Ratios

```
Venus       /Mercury     = 2.5539  ~= 18/7
Earth       /Mercury     = 4.1526
Mars        /Mercury     = 7.8105
Jupiter     /Mercury     = 49.2632
Saturn      /Mercury     = 122.3026
Earth       /Venus       = 1.6260  ~= 13/8
Mars        /Venus       = 3.0582
Jupiter     /Venus       = 19.2890
Saturn      /Venus       = 47.8877
Mars        /Earth       = 1.8809  ~= 15/8
Jupiter     /Earth       = 11.8631
Saturn      /Earth       = 29.4518
Jupiter     /Mars        = 6.3073  ~= 19/3
Saturn      /Mars        = 15.6587
Saturn      /Jupiter     = 2.4826  ~= 5/2
```

## Rotation Coupling

```
T_rotation / T_surface = 219.113180
Surfaces per rotation = 219.113180
  nearest integer: 219.000000 (off by +0.0517%)

Mercury: 3.4658 rotations/orbit  (nearest half: 3.5000, off -0.98%)
Venus: 8.8516 rotations/orbit  (nearest half: 9.0000, off -1.65%)
Earth: 14.3923 rotations/orbit  (nearest half: 14.5000, off -0.74%)
Mars: 27.0700 rotations/orbit  (nearest half: 27.0000, off +0.26%)
Jupiter: 170.7381 rotations/orbit  (nearest half: 170.5000, off +0.14%)
Saturn: 423.8811 rotations/orbit  (nearest half: 424.0000, off -0.03%)
```

## Distance Normalisation

```
Moon                   a/R   a/kappa  a/(c*T_surf)           a*z
----------------------------------------------------------------
Mercury              83.24 3.921e+07    1.9302e-02   122925.5570
Venus               155.53 7.327e+07    3.6064e-02   229676.1400
Earth               215.04 1.013e+08    4.9862e-02   317555.9200
Mars                327.58 1.543e+08    7.5960e-02   483763.3300
Jupiter            1119.02 5.272e+08    2.5948e-01  1652521.9500
Saturn             2061.23 9.710e+08    4.7796e-01  3043951.8000
```

---
---

# Jupiter — Satellite System

## Host: Jupiter

```
R       = 7.1490e+07 m
z       = 1.971400e-08
k       = 7122.17
v_surf  = 42092.8 m/s (0.000140 c)
kappa   = 1.4094 m
T_surf  = 10671.29 s
sqrt(T) = 103.3020
T_rot   = 35730.00 s (9.9250 h)
T_rot / T_surf = 3.348235

c * T_surf = 3.1992e+12 m = 21.3852 AU
c * T_surf / (2*pi*R) = 7122.17 = k
```

## Satellites — Raw

```
Moon                     a (m)  a/R_host         P (s)    P/T_surf sqrt(P/T)  v_orb(m/s) v_pred(m/s)  v_err%
------------------------------------------------------------------------------------------------------------
Metis                1.280e+08      1.79     2.552e+04      2.3915    1.5464     31514.4     31457.6   +0.18
Adrastea             1.290e+08      1.80     2.573e+04      2.4111    1.5528     31501.4     31335.4   +0.53
Amalthea             1.814e+08      2.54     4.318e+04      4.0464    2.0116     26395.8     26424.8   -0.11
Thebe                2.219e+08      3.10     5.832e+04      5.4651    2.3378     23906.7     23892.0   +0.06
Io                   4.218e+08      5.90     1.528e+05     14.3188    3.7840     17344.6     17329.2   +0.09
Europa               6.711e+08      9.39     3.068e+05     28.7500    5.3619     13744.0     13738.4   +0.04
Ganymede             1.070e+09     14.97     6.182e+05     57.9311    7.6112     10875.1     10880.2   -0.05
Callisto             1.883e+09     26.34     1.442e+06    135.1289   11.6245      8204.7      8201.7   +0.04
Himalia              1.146e+10    160.30     2.177e+07   2040.0525   45.1669      3307.5      3324.6   -0.51
```

## Satellites — Normalised to T_surf and R_host

```
Moon                   a/R    P/T_surf   (a/R)^(3/2)    match%    v/v_surf   1/sqrt(a/R)    match%
--------------------------------------------------------------------------------------------------
Metis                 1.79      2.3915        2.3958   100.181    0.748688      0.747339    99.820
Adrastea              1.80      2.4111        2.4239   100.530    0.748379      0.744437    99.473
Amalthea              2.54      4.0464        4.0419    99.890    0.627085      0.627775   100.110
Thebe                 3.10      5.4651        5.4685   100.062    0.567952      0.567602    99.938
Io                    5.90     14.3188       14.3315   100.089    0.412055      0.411689    99.911
Europa                9.39     28.7500       28.7616   100.040    0.326515      0.326384    99.960
Ganymede             14.97     57.9311       57.9039    99.953    0.258361      0.258482   100.047
Callisto             26.34    135.1289      135.1785   100.037    0.194920      0.194849    99.963
Himalia             160.30   2040.0525     2029.5931    99.487    0.078577      0.078982   100.515
```

## Cross-normalised to Solar T_surface (10007.8 s)

```
Moon              P/T_sun_surf  P/T_jup_surf         ratio
----------------------------------------------------------
Metis                   2.5500        2.3915      1.066302
Adrastea                2.5710        2.4111      1.066302
Amalthea                4.3147        4.0464      1.066302
Thebe                   5.8275        5.4651      1.066302
Io                     15.2682       14.3188      1.066302
Europa                 30.6562       28.7500      1.066302
Ganymede               61.7721       57.9311      1.066302
Callisto              144.0882      135.1289      1.066302
Himalia              2175.3121     2040.0525      1.066302

T_jup_surf / T_sun_surf = 1.066302
k_jup / k_sun = 10.3766
```

## Moon-to-Moon Period Ratios

```
Adrastea    /Metis       = 1.0082  ~= 1/1
Amalthea    /Metis       = 1.6920  ~= 17/10
Thebe       /Metis       = 2.2853  ~= 16/7
Io          /Metis       = 5.9875  ~= 6/1
Europa      /Metis       = 12.0219  ~= 12/1
Ganymede    /Metis       = 24.2241
Callisto    /Metis       = 56.5047
Himalia     /Metis       = 853.0564
Amalthea    /Adrastea    = 1.6782  ~= 5/3
Thebe       /Adrastea    = 2.2666  ~= 9/4
Io          /Adrastea    = 5.9386
Europa      /Adrastea    = 11.9238  ~= 12/1
Ganymede    /Adrastea    = 24.0264
Callisto    /Adrastea    = 56.0435
Himalia     /Adrastea    = 846.0941
Thebe       /Amalthea    = 1.3506
Io          /Amalthea    = 3.5387
Europa      /Amalthea    = 7.1051
Ganymede    /Amalthea    = 14.3168
Callisto    /Amalthea    = 33.3951
Himalia     /Amalthea    = 504.1686
Io          /Thebe       = 2.6200  ~= 13/5
Europa      /Thebe       = 5.2606
Ganymede    /Thebe       = 10.6001
Callisto    /Thebe       = 24.7257
Himalia     /Thebe       = 373.2853
Europa      /Io          = 2.0079  ~= 2/1
Ganymede    /Io          = 4.0458
Callisto    /Io          = 9.4372  ~= 19/2
Himalia     /Io          = 142.4738
Ganymede    /Europa      = 2.0150  ~= 2/1
Callisto    /Europa      = 4.7001  ~= 14/3
Himalia     /Europa      = 70.9583
Callisto    /Ganymede    = 2.3326  ~= 7/3
Himalia     /Ganymede    = 35.2151
Himalia     /Callisto    = 15.0971  ~= 15/1
```

## Rotation Coupling

```
T_rotation / T_surface = 3.348235
Surfaces per rotation = 3.348235
  nearest integer: 3.000000 (off by +11.6078%)

Metis: 0.7142 rotations/orbit  (nearest half: 0.5000, off +42.85%)
Adrastea: 0.7201 rotations/orbit  (nearest half: 0.5000, off +44.02%)
Amalthea: 1.2085 rotations/orbit  (nearest half: 1.0000, off +20.85%)
Thebe: 1.6322 rotations/orbit  (nearest half: 1.5000, off +8.82%)
Io: 4.2765 rotations/orbit  (nearest half: 4.5000, off -4.97%)
Europa: 8.5866 rotations/orbit  (nearest half: 8.5000, off +1.02%)
Ganymede: 17.3020 rotations/orbit  (nearest half: 17.5000, off -1.13%)
Callisto: 40.3582 rotations/orbit  (nearest half: 40.5000, off -0.35%)
Himalia: 609.2919 rotations/orbit  (nearest half: 609.5000, off -0.03%)
```

## Distance Normalisation

```
Moon                   a/R   a/kappa  a/(c*T_surf)           a*z
----------------------------------------------------------------
Metis                 1.79 9.082e+07    4.0010e-05        2.5234
Adrastea              1.80 9.153e+07    4.0323e-05        2.5431
Amalthea              2.54 1.287e+08    5.6702e-05        3.5761
Thebe                 3.10 1.574e+08    6.9362e-05        4.3745
Io                    5.90 2.993e+08    1.3185e-04        8.3154
Europa                9.39 4.762e+08    2.0977e-04       13.2301
Ganymede             14.97 7.592e+08    3.3446e-04       21.0940
Callisto             26.34 1.336e+09    5.8859e-04       37.1215
Himalia             160.30 8.131e+09    3.5822e-03      225.9224
```
