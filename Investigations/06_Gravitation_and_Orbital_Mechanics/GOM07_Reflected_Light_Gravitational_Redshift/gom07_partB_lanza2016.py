"""
GOM07 Part B — the data test against REAL measured spectra.
Author: J.C. Harvey, Melbourne.  SDT — Depth-Closure.

DATA: Lanza et al. 2016 (A&A 587, A103; arXiv:1601.05646), Table 2.  They measured the Sun's
radial velocity off the Moon, asteroids, and Galilean satellites on ONE common scale with HARPS,
and explicitly applied NO gravitational-well correction for each reflector's host potential
("For the Galilean satellites the effect can be larger than ~1 m/s only for Io ... " -- they mean
ROTATION, not Jupiter's potential; Jupiter's well is never corrected).

THE TEST (the GOM07 gate, now with data).  CORRECTED FRAMING (2026-06-20 -- predictions were swapped):
  SDT -> redshift encoded at emission (the Sun) and STABLE; reflected light does NOT re-fight gravity
         at the reflector.  Jupiter's well contributes 0 -> every body flat -> slope b = 0.
  GR  -> light "fights gravity all the way out"; a Galilean moon's reflected light climbing out of
         Jupiter's well accumulates an EXTRA redshift z*c = koppa_J/r -> slope b = 1.
We regress (measured RV) against the Jupiter-well extra and read the slope.  slope 0 = SDT, 1 = GR.
(Rigorous cancellation-GR also gives slope 0, degenerate with SDT for reflection.)
"""
c = 299792458.0
# Jupiter depth (SDT primitives v_surf, R -- NO GM): koppa_J = v_surf^2 R / c^2
v_J, R_J = 42569.0, 6.9911e7
koppa_J = v_J*v_J*R_J/(c*c)
r_gal = {"Io":4.217e8, "Europa":6.711e8, "Ganymede":1.0704e9, "Callisto":1.8827e9}
def zc(body):                                   # SDT-predicted extra redshift (m/s); 0 if not near Jupiter
    return koppa_J*c/r_gal[body] if body in r_gal else 0.0

# Lanza 2016 Table 2:  (measured solar RV m/s, population SD m/s, N spectra-groups)
T2 = {
    "Moon":     (99.39, 1.67,  6),
    "Vesta":    (101.68,3.39, 24),
    "Pallas":   (99.41, 3.96,  7),
    "Iris":     (97.57, 4.31,  5),
    "Ganymede": (99.07, 1.56, 17),
    "Europa":   (101.32,3.06, 10),
    "Io":       (90.18, 3.36,  7),   # authors exclude: albedo(0.10-0.75) x high airmass artifact
    "Ceres":    (98.21, 6.58,  7),   # authors exclude: fast rotation V_eq~92 m/s + surface inhomogeneity
}

def wls(bodies):
    """Weighted least squares  RV = a + b*x ,  x = SDT Jupiter-well extra,  w = 1/SE^2 (SE = SD/sqrt(N))."""
    S=Sx=Sy=Sxx=Sxy=0.0
    for b in bodies:
        rv,sd,n = T2[b]; x = zc(b); se = sd/(n**0.5); w = 1.0/(se*se)
        S+=w; Sx+=w*x; Sy+=w*rv; Sxx+=w*x*x; Sxy+=w*x*rv
    D = S*Sxx - Sx*Sx
    b_ = (S*Sxy - Sx*Sy)/D
    a_ = (Sxx*Sy - Sx*Sxy)/D
    return a_, b_, (S/D)**0.5, (Sxx/D)**0.5     # a, slope, sigma_slope, sigma_intercept

print(f"Jupiter depth koppa_J = {koppa_J:.4f} m   (from v_surf,R; NO GM)")
print(f"GR-climb-predicted extra redshift per body (m/s)  [SDT predicts 0 for all]:")
for b in ["Moon","Vesta","Pallas","Iris","Ganymede","Europa","Io","Ceres"]:
    rv,sd,n = T2[b]; print(f"  {b:9} x={zc(b):.3f}   measured RV {rv:7.2f} +- {sd/n**0.5:4.2f} (SE)  [N={n}]")

print("\n--- GATE: slope of RV vs Jupiter-well extra.  SDT (flat) predicts 0.0 ; GR (climb) predicts 1.0 ---")
clean = ["Moon","Vesta","Pallas","Iris","Ganymede","Europa"]      # authors' clean set (Io,Ceres excluded)
a,b,sb,sa = wls(clean)
print(f"clean set {clean}")
print(f"  slope = {b:+.2f} +- {sb:.2f}   intercept = {a:.2f} +- {sa:.2f} m/s")
print(f"  -> distance from SDT(0): {abs(b-0)/sb:.1f}sigma ;  from GR(1): {abs(b-1)/sb:.1f}sigma")

allb = clean+["Io"]                                                # add back the most-sensitive (artifact) point
a2,b2,sb2,sa2 = wls(allb)
print(f"\nwith Io added back (its +1.0 lever, but albedo-artifact): slope = {b2:+.2f} +- {sb2:.2f}")

# The single within-Jupiter pair the user named:
e = T2["Europa"]; g = T2["Ganymede"]
dd = e[0]-g[0]; sde = ((e[1]/e[2]**0.5)**2 + (g[1]/g[2]**0.5)**2)**0.5
print(f"\nEuropa - Ganymede  measured = {dd:+.2f} +- {sde:.2f} m/s    GR-climb predicts {zc('Europa')-zc('Ganymede'):+.2f} ; SDT 0")
print(f"  -> {dd/sde:.1f}sigma from 0 (sign {'matches GR-climb' if dd>0 else 'opposes GR-climb'}; but 10x the 0.23 predicted = systematic)")

# Body-to-body scatter among the z=0 bodies = the systematic floor that any real signal must beat:
import statistics as st
z0 = [T2[b][0] for b in ["Moon","Vesta","Pallas","Iris"]]
print(f"\nSYSTEMATIC FLOOR: the 4 zero-well bodies (identical under BOTH theories) span "
      f"{min(z0):.2f}-{max(z0):.2f}, scatter {st.pstdev(z0):.2f} m/s")
print(f"  vs the GR-climb signal being tested: {zc('Europa'):.2f}-{zc('Io'):.2f} m/s.  Floor >> signal.")
