# GOM44 RUN_LOG

Verbatim output of `gom44_flyby_depth_control.py` (run 2026-10-16 after PROMPT.md was written; no rule changed between registration and run). A first run applied a tolerance of 1.0 mm/s (2 × 0.5) where PROMPT.md section 3 registers 0.5 mm/s for flybys with unpublished σ; the tool was corrected to the registered value and re-run before any conclusion was written. Effect: EPOXI II moved from pass to fail on G3 and G4.

Command: `python -I gom44_flyby_depth_control.py Datasets/external_audit_2026-10-16/raw/horizons_gom44 .`

```text
GOM44 run log (tool output)

G1a symmetric synthetic: B = 0.000e+00  -> met
G1b closed form: tool 2.000000670256  closed 2.000000670256  diff 0.00e+00 -> met
G1c endpoint radius = R_ref within 1 m for all computed endpoints: met
G1d Earth heliocentric distance in 0.983-1.017 au at all endpoints: met
G1e galileo1   Vinf 8.9481 (PRL 8.949)  dec_in  -12.48 (PRL -12.52)  dec_out  -34.17 (PRL -34.15)  ok
G1e galileo2   Vinf 8.8793 (PRL 8.877)  dec_in  -34.27 (PRL -34.26)  dec_out   -4.82 (PRL -4.87)  ok
G1e near       Vinf 6.8510 (PRL 6.851)  dec_in  -20.57 (PRL -20.76)  dec_out  -71.98 (PRL -71.96)  ok
G1e cassini    Vinf 16.0125 (PRL 16.01)  dec_in  -12.92 (PRL -12.92)  dec_out   -4.99 (PRL -4.99)  ok
G1e rosetta1   Vinf 3.8612 (PRL 3.863)  dec_in   -1.94 (PRL -2.81)  dec_out  -34.07 (PRL -34.29)  ok
G1e messenger  Vinf 4.0579 (PRL 4.056)  dec_in   32.24 (PRL 31.44)  dec_out  -32.74 (PRL -31.92)  ok
G1e Table I reproduced (V-inf 0.003 km/s, declinations 0.9 deg): met

G1 instrument validation: MET  {'a': True, 'b': True, 'c': True, 'd': True, 'e': True}

==== PRIMARY R_ref = 50000 km (spacecraft R_sun) : computed 19 of 20 flybys; equal-depth tercile n = 7 ====
flyby            rmin km   dt h   cos_in  cos_out Rsun_in au Rsun_out au          B    vinf   P mm/s     obs  sigma cls  E
Hayabusa2           9532   4.08  -0.3269  -0.3473   0.985702    0.985670  2.106e-02   4.612    0.291       -      -   U  E
EPOXI II           49829   0.52  -0.8474  -0.9342   0.983067    0.983037  8.981e-02   3.461    0.932   0.000  0.500   N  E
Stardust           12589   3.39   0.4142  -0.2728   0.983804    0.983584  7.099e-01   6.481   13.800       -      -   U  E
MESSENGER           8938   4.29  -0.6264   0.3499   1.014572    1.014875 -9.482e-01   4.058  -11.540   0.020  0.010   N  E
NEAR                7327   3.19   0.6948  -0.3324   0.984515    0.984186  1.060e+00   6.851   21.779  13.460  0.130   A  E
Galileo II          6681   2.66   0.7235  -0.3528   0.985147    0.984773  1.109e+00   8.879   29.543  -4.600  1.000   A  E
Rosetta III         9135   2.57   0.6428  -0.5082   0.989829    0.989421  1.175e+00   9.379   33.057   0.004  0.044   N  E
Rosetta I           8334   4.36   0.9514  -0.2773   0.992118    0.991754  1.248e+00   3.861   14.458   1.800  0.030   A   
JUICE (LEGA)       13249   4.83   0.8937  -0.5235   1.011965    1.011451  1.384e+00   3.304   13.718   0.600      -   U   
Lucy I              7161   3.69  -0.9785   0.4196   0.996625    0.997049 -1.407e+00   5.332  -22.506       -      -   U   
EPOXI I            21945   4.83   0.7188  -0.6441   0.983533    0.983075  1.409e+00   3.448   14.577   0.000  0.500   N   
Juno                7202   2.36  -0.8510   0.6498   0.998443    0.998916 -1.505e+00  10.389  -46.889   0.000  0.800   N   
Solar Orbiter       6956   2.32  -0.8424   0.6501   0.986510    0.986992 -1.533e+00  10.606  -48.762   0.000  0.500   N   
Lucy II             7159   2.31  -0.8778   0.6864   0.984134    0.984647 -1.614e+00  10.662  -51.624       -      -   U   
BepiColombo        19117   4.54  -0.8217   0.8514   1.001585    1.002199 -1.667e+00   3.984  -19.917   0.000  0.500   N   
OSIRIS-REx         23628   3.37   0.8336  -0.9932   1.003892    1.003242  1.814e+00   6.230   33.892       -      -   U   
Rosetta II         11721   2.58   0.9072  -0.9219   0.989857    0.989220  1.868e+00   9.364   52.460   0.000  0.500   N   
Cassini             7568   1.63  -0.9561   0.9598   1.012043    1.012670 -1.869e+00  16.012  -89.777  -2.000  1.000   N   
Galileo I           7964   2.65   0.9982  -0.9349   0.985331    0.984672  1.992e+00   8.948   53.468   3.920  0.080   A   
EPOXI III      not applicable at this R_ref (r_min 1336721 km >= R_ref or window)
G2 anomalous class (|P - obs| <= 2 sigma): NOT MET
    Galileo I      P   53.468  obs   3.920  2sigma  0.160  FAIL
    Galileo II     P   29.543  obs  -4.600  2sigma  2.000  FAIL
    NEAR           P   21.779  obs  13.460  2sigma  0.260  FAIL
    Rosetta I      P   14.458  obs   1.800  2sigma  0.060  FAIL
G3 null class (|P| <= 2 sigma or 0.5):     NOT MET
    Cassini        P  -89.777  obs  -2.000  tol  2.000  FAIL
    MESSENGER      P  -11.540  obs   0.020  tol  0.020  FAIL
    Rosetta II     P   52.460  obs   0.000  tol  0.500  FAIL
    Rosetta III    P   33.057  obs   0.004  tol  0.088  FAIL
    Juno           P  -46.889  obs   0.000  tol  1.600  FAIL
    EPOXI I        P   14.577  obs   0.000  tol  0.500  FAIL
    EPOXI II       P    0.932  obs   0.000  tol  0.500  FAIL
    BepiColombo    P  -19.917  obs   0.000  tol  0.500  FAIL
    Solar Orbiter  P  -48.762  obs   0.000  tol  0.500  FAIL
G4 equal-depth control:                    NOT MET
    Galileo II     B   1.109e+00  P   29.543  obs  -4.600  class A  FAIL
    NEAR           B   1.060e+00  P   21.779  obs  13.460  class A  FAIL
    MESSENGER      B  -9.482e-01  P  -11.540  obs   0.020  class N  FAIL
    Rosetta III    B   1.175e+00  P   33.057  obs   0.004  class N  FAIL
    EPOXI II       B   8.981e-02  P    0.932  obs   0.000  class N  FAIL
    Stardust       B   7.099e-01  P   13.800  obs       -  class U  ok
    Hayabusa2      B   2.106e-02  P    0.291  obs       -  class U  ok
G5 Spearman rho(P, obs) = 0.375 over 14 flybys, permutation p (200000, seed 20261016) = 0.0922; threshold 0.7: NOT MET

==== SENSITIVITY R_ref = 20000 km : computed 16 of 20 flybys; equal-depth tercile n = 6 ====
G2 anomalous class (|P - obs| <= 2 sigma): NOT MET
    Galileo I      P   54.232  obs   3.920  2sigma  0.160  FAIL
    Galileo II     P   30.416  obs  -4.600  2sigma  2.000  FAIL
    NEAR           P   23.133  obs  13.460  2sigma  0.260  FAIL
    Rosetta I      P   16.383  obs   1.800  2sigma  0.060  FAIL
G3 null class (|P| <= 2 sigma or 0.5):     NOT MET
    Cassini        P  -86.407  obs  -2.000  tol  2.000  FAIL
    MESSENGER      P  -12.807  obs   0.020  tol  0.020  FAIL
    Rosetta II     P   46.396  obs   0.000  tol  0.500  FAIL
    Rosetta III    P   32.149  obs   0.004  tol  0.088  FAIL
    Juno           P  -47.152  obs   0.000  tol  1.600  FAIL
    BepiColombo    P   -7.495  obs   0.000  tol  0.500  FAIL
    Solar Orbiter  P  -49.048  obs   0.000  tol  0.500  FAIL
G4 equal-depth control:                    NOT MET
    Galileo II     B   1.142e+00  P   30.416  obs  -4.600  class A  FAIL
    NEAR           B   1.126e+00  P   23.133  obs  13.460  class A  FAIL
    MESSENGER      B  -1.052e+00  P  -12.807  obs   0.020  class N  FAIL
    BepiColombo    B  -6.272e-01  P   -7.495  obs   0.000  class N  FAIL
    Stardust       B   6.351e-01  P   12.345  obs       -  class U  ok
    Hayabusa2      B   3.083e-02  P    0.426  obs       -  class U  ok
G5 Spearman rho(P, obs) = 0.374 over 12 flybys, permutation p (200000, seed 20261016) = 0.1147; threshold 0.7: NOT MET

==== SENSITIVITY R_ref = 100000 km : computed 19 of 20 flybys; equal-depth tercile n = 7 ====
G2 anomalous class (|P - obs| <= 2 sigma): NOT MET
    Galileo I      P   51.992  obs   3.920  2sigma  0.160  FAIL
    Galileo II     P   28.639  obs  -4.600  2sigma  2.000  FAIL
    NEAR           P   20.722  obs  13.460  2sigma  0.260  FAIL
    Rosetta I      P   12.864  obs   1.800  2sigma  0.060  FAIL
G3 null class (|P| <= 2 sigma or 0.5):     NOT MET
    Cassini        P  -89.488  obs  -2.000  tol  2.000  FAIL
    MESSENGER      P  -10.374  obs   0.020  tol  0.020  FAIL
    Rosetta II     P   52.002  obs   0.000  tol  0.500  FAIL
    Rosetta III    P   32.390  obs   0.004  tol  0.088  FAIL
    Juno           P  -45.972  obs   0.000  tol  1.600  FAIL
    EPOXI I        P   14.202  obs   0.000  tol  0.500  FAIL
    EPOXI II       P    9.068  obs   0.000  tol  0.500  FAIL
    BepiColombo    P  -19.175  obs   0.000  tol  0.500  FAIL
    Solar Orbiter  P  -47.815  obs   0.000  tol  0.500  FAIL
G4 equal-depth control:                    NOT MET
    Galileo II     B   1.075e+00  P   28.639  obs  -4.600  class A  FAIL
    NEAR           B   1.008e+00  P   20.722  obs  13.460  class A  FAIL
    Rosetta I      B   1.111e+00  P   12.864  obs   1.800  class A  FAIL
    MESSENGER      B  -8.524e-01  P  -10.374  obs   0.020  class N  FAIL
    EPOXI II       B   8.737e-01  P    9.068  obs   0.000  class N  FAIL
    Stardust       B   6.877e-01  P   13.367  obs       -  class U  ok
    Hayabusa2      B   1.870e-02  P    0.259  obs       -  class U  ok
G5 Spearman rho(P, obs) = 0.341 over 14 flybys, permutation p (200000, seed 20261016) = 0.1152; threshold 0.7: NOT MET

==== SENSITIVITY R_ref = 50000 km, Earth heliocentric distance in place of spacecraft's : computed 19 of 20 flybys; equal-depth tercile n = 7 ====
G2 anomalous class (|P - obs| <= 2 sigma): NOT MET
    Galileo I      P   53.470  obs   3.920  2sigma  0.160  FAIL
    Galileo II     P   29.550  obs  -4.600  2sigma  2.000  FAIL
    NEAR           P   21.784  obs  13.460  2sigma  0.260  FAIL
    Rosetta I      P   14.464  obs   1.800  2sigma  0.060  FAIL
G3 null class (|P| <= 2 sigma or 0.5):     NOT MET
    Cassini        P  -89.777  obs  -2.000  tol  2.000  FAIL
    MESSENGER      P  -11.538  obs   0.020  tol  0.020  FAIL
    Rosetta II     P   52.460  obs   0.000  tol  0.500  FAIL
    Rosetta III    P   33.060  obs   0.004  tol  0.088  FAIL
    Juno           P  -46.882  obs   0.000  tol  1.600  FAIL
    EPOXI I        P   14.578  obs   0.000  tol  0.500  FAIL
    EPOXI II       P    0.931  obs   0.000  tol  0.500  FAIL
    BepiColombo    P  -19.917  obs   0.000  tol  0.500  FAIL
    Solar Orbiter  P  -48.756  obs   0.000  tol  0.500  FAIL
G4 equal-depth control:                    NOT MET
    Galileo II     B   1.110e+00  P   29.550  obs  -4.600  class A  FAIL
    NEAR           B   1.060e+00  P   21.784  obs  13.460  class A  FAIL
    MESSENGER      B  -9.481e-01  P  -11.538  obs   0.020  class N  FAIL
    Rosetta III    B   1.175e+00  P   33.060  obs   0.004  class N  FAIL
    EPOXI II       B   8.970e-02  P    0.931  obs   0.000  class N  FAIL
    Stardust       B   7.100e-01  P   13.801  obs       -  class U  ok
    Hayabusa2      B   2.105e-02  P    0.291  obs       -  class U  ok
G5 Spearman rho(P, obs) = 0.375 over 14 flybys, permutation p (200000, seed 20261016) = 0.0922; threshold 0.7: NOT MET

wrote flyby_depth_control.csv
```

Tool sha256: 8d2f43056098c18adc6588141deea97df8b607759cb76e15229650f0246009ce
CSV sha256: 9a0277f6ce1117747f36dbeedd9a66ab65eb1816949cc655963a3b7fd563cc6d
