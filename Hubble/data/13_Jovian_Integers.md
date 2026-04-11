# Jovian Integers — Jupiter in Jupiter's Own Units

> Same RATIO as Earth's units are to Earth

---

## Unit Definitions

```
                      Earth               Jupiter
-------------------------------------------------------
1 'second'     = 1/86400 rotation   = 1/86400 rotation
               = 1.0000 SI s          = 0.4135 SI s
1 'day'        = 1 rotation          = 1 rotation
               = 86400.0 SI s       = 35730.0 SI s
1 'year'       = 1 orbit             = 1 orbit
               = 365.26 days        = 10477.36 days
1 'radius'     = 6.371e+06 m          = 6.991e+07 m
```

## T_surface in Native Seconds

```
IN EARTH SECONDS:
  Sun  T_surf = 10007.76 Earth secs   sqrt = 100.0388
  Jup  T_surf = 10318.87 Earth secs   sqrt = 101.5818

IN JOVIAN SECONDS:
  Sun  T_surf = 24200.12 Jovian secs  sqrt = 155.5639
  Jup  T_surf = 24952.43 Jovian secs  sqrt = 157.9634

IN NATIVE SECONDS (each body in its own planet's seconds):
  Sun  T_surf = 10007.76 Earth secs   sqrt = 100.0388
  Jup  T_surf = 24952.43 Jovian secs  sqrt = 157.9634

RATIO:
  T_jup/T_sun (SI) = 1.031087
  J_sec/E_sec      = 0.413542
  E_day/J_day      = 2.418136
```

## Satellite Periods in Native Days

```
EARTH SYSTEM:
  Moon sidereal period = 27.3217 Earth days
  Moon period / T_surf(Sun) = 235.8765 T_surfs
  Solar day - Sidereal day = 235.9 Earth seconds
  Moon_sid_period / T_surf = 235.88

JUPITER SYSTEM:
  Metis           0.7144 Jov days      61725.34 Jov secs      2.4737 T_surfs
  Adrastea        0.7201 Jov days      62218.64 Jov secs      2.4935 T_surfs
  Amalthea        1.2085 Jov days     104415.11 Jov secs      4.1846 T_surfs
  Thebe           1.6322 Jov days     141025.69 Jov secs      5.6518 T_surfs
  Io              4.2780 Jov days     369621.76 Jov secs     14.8131 T_surfs
  Europa          8.5872 Jov days     741937.33 Jov secs     29.7341 T_surfs
  Ganymede       17.3007 Jov days    1494780.45 Jov secs     59.9052 T_surfs
  Callisto       40.3493 Jov days    3486178.34 Jov secs    139.7130 T_surfs
```

## The '236' Test

Earth system:
```
Moon sidereal / T_surf(Sun) = 235.88
Day - Sidereal day = 235.9 Earth seconds
These are both ~236
```

Jupiter system (testing each moon):
```
Jovian sidereal day   = 35730.00 SI s
Jovian solar day      = 35733.41 SI s
Difference            = 3.41 SI s = 8.2471 Jovian seconds

Metis         P/T_surf = 2.4737  day_diff(Jov_s) = 8.2471  match? no
Adrastea      P/T_surf = 2.4935  day_diff(Jov_s) = 8.2471  match? no
Amalthea      P/T_surf = 4.1846  day_diff(Jov_s) = 8.2471  match? no
Thebe         P/T_surf = 5.6518  day_diff(Jov_s) = 8.2471  match? no
Io            P/T_surf = 14.8131  day_diff(Jov_s) = 8.2471  match? no
Europa        P/T_surf = 29.7341  day_diff(Jov_s) = 8.2471  match? no
Ganymede      P/T_surf = 59.9052  day_diff(Jov_s) = 8.2471  match? no
Callisto      P/T_surf = 139.7130  day_diff(Jov_s) = 8.2471  match? no
```

## Kepler in Native Units

```
Moon           a/R_jup   P(Jov days)  v_orb(m/s)      v/v_surf      err%
------------------------------------------------------------------------
Metis             1.83        0.7144     31507.0      0.740140     +0.15
Adrastea          1.85        0.7201     31501.4      0.740008     +0.52
Amalthea          2.59        1.2085     26395.8      0.620071     -0.12
Thebe             3.17        1.6322     23906.7      0.561599     +0.05
Io                6.03        4.2780     17338.4      0.407302     +0.05
Europa            9.60        8.5872     13743.0      0.322840     +0.02
Ganymede         15.31       17.3007     10880.0      0.255585     +0.01
Callisto         26.93       40.3493      8205.3      0.192752     +0.03
```
