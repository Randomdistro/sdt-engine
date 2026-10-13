"""
GOM07 — Reflected-Light Gravitational Redshift.  SDT-NATIVE (NO G, NO M).
Author: J.C. Harvey, Melbourne.  SDT — Depth-Closure.

THE PHYSICS (corrected 2026-06-20 — predictions were previously swapped):
  SDT: redshift is ENCODED AT THE POINT OF EMISSION and is STABLE (set without movement).
       Reflected sunlight carries the SUN's emission stamp; it does NOT re-fight gravity at the
       reflector.  The reflector's own well contributes NOTHING.  -> FLAT 633 m/s for every body.
  GR : light must "fight gravity all the way until it escapes the gravitational bounds of a body"
       (gradual climb).  Reflected light climbing out of the planet's well keeps accumulating
       redshift -> +z_body*c, rising with the reflector's well.  -> Jupiter ~639 m/s.
  (Caveat: rigorous cancellation-GR ALSO gives flat, claiming the fall-in blueshift cancels the
   climb-out redshift; reflection is degenerate SDT vs cancellation-GR.  The +z_body*c column is
   the GRADUAL one-way-climb reading -- the one this test can actually refute.)

INPUTS = SDT primitives only:  v_surf (surface circulation velocity, m/s), R (radius, m).
  koppa = v_surf^2 R / c^2  (NO GM).   z = (v_surf/c)^2 = spectral lambda->lambda shift.
  k = c/v_surf.   SEAT z*k^2 = 1 (verified per body).   climb extra = z*c = v_surf^2/c (m/s).
"""
c = 299792458.0
# (v_surf [m/s], R [m]) -- the two SDT primitives.  NO GM anywhere.
bodies = {
    "Moon":    (1680.2,  1.7374e6),   # baseline / control (well negligible)
    "Mars":    (3554.7,  3.3895e6),
    "Venus":   (7326.7,  6.0518e6),
    "Saturn":  (25522.0, 5.8232e7),
    "Jupiter": (42569.0, 6.9911e7),   # the largest lever
}
v_surf_Sun, R_sun, AU = 436762.0, 6.957e8, 1.495978707e11   # Sun surface circ. velocity, radius, AU
v_solar = (v_surf_Sun**2 / c) * (1.0 - R_sun/AU)            # Sun-surface -> 1 AU solar redshift (m/s)
print(f"Solar baseline (Sun surface -> 1 AU)  z*c = {v_solar:.2f} m/s   (HARPS-LFC Moon 638+-6; GR 633.1)\n")

print(f"{'body':9}{'v_surf (m/s)':>13}{'z=(v/c)^2':>13}{'z*k^2':>9}{'climb z*c':>11}"
      f"{'SDT (flat)':>12}{'GR (climb)':>12}")
rows = {}
for b,(v,R) in bodies.items():
    z = (v/c)**2; k = c/v; zk2 = z*k*k; zc = z*c
    rows[b] = zc
    # SDT: flat (emission stamp).   GR: baseline + climb-out of the reflector's well.
    print(f"{b:9}{v:>13.1f}{z:>13.3e}{zk2:>9.5f}{zc:>11.4f}{v_solar:>12.2f}{v_solar+zc:>12.2f}")

print(f"\nSEAT: z*k^2 = 1 for every body  (z = spectral lambda->lambda shift, k = c/v_surf).")
print("DECISIVE DIFFERENTIALS (GR gradual-climb adds z*c; SDT adds 0 -> both bodies flat):")
print(f"  Jupiter - Moon  = {rows['Jupiter']-rows['Moon']:.3f} m/s under GR-climb ; 0 under SDT")
print(f"  Jupiter - Venus = {rows['Jupiter']-rows['Venus']:.3f} m/s under GR-climb ; 0 under SDT")

# --- WITHIN-JUPITER test: Galilean moon at orbital r ; GR-climb adds koppa_J/r, SDT adds 0 ---
v_J, R_J = bodies["Jupiter"]
koppa_J = v_J*v_J*R_J/(c*c)        # koppa = v_surf^2 R / c^2  (DERIVED from primitives; no GM)
gal = {"Io":4.217e8, "Europa":6.711e8, "Ganymede":1.0704e9, "Callisto":1.8827e9}
print("\nWITHIN-JUPITER (Galilean): GR-climb -> +koppa_J/r (falls with distance); SDT -> 0 (flat):")
for m,r in gal.items():
    print(f"  {m:9} r={r:.3e} m   koppa_J/r={koppa_J/r:.3e}   GR-climb +{koppa_J*c/r:.3f} m/s ; SDT +0")
print(f"  Io - Callisto     = {koppa_J*c*(1/gal['Io']-1/gal['Callisto']):.3f} m/s (GR-climb) ; 0 (SDT)")
print(f"  Europa - Ganymede = {koppa_J*c*(1/gal['Europa']-1/gal['Ganymede']):.3f} m/s (GR-climb) ; 0 (SDT)")
print()
print("GATE: regress (measured_residual - 633) against z*c across {Moon,Venus,Mars,Saturn,Jupiter}.")
print("  slope 0  -> SDT (emission stamp; reflector silent, flat 633).")
print("  slope 1  -> GR  (gradual climb; reflector's well adds z*c).")
print("  (Rigorous cancellation-GR also -> slope 0, degenerate with SDT here.)")
