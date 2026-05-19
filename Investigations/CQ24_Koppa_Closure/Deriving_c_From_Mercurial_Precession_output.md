Deriving c From Mercurial Precession
====================================

Observables
  R_Sun             6.9570e+08 m
  a_Mercury         5.7909e+10 m
  e_Mercury            0.20563
  P_Mercury             87.969 days
  precession             42.98 arcsec/century
  v_surface           436762.0 m/s

Derivation
  delta_phi         5.0186e-07 rad/orbit
  a(1-e^2)          5.5460e+10 m
  koppa^2               471150
  koppa                 686.40

Result
  c = koppa * v_surface
  c = 686.40 * 436762.0
  c = 299795136 m/s

Validation
  accepted c    299792458 m/s
  error         +0.0009%

Closure
  z   = 1/k^2  = 2.122465e-06
  zk^2          = 1.000000
