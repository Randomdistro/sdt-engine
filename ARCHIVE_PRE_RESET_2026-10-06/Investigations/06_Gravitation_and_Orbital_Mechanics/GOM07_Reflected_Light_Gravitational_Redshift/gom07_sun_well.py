"""
GOM07 — CORRECTED DEPTH: the reflector's position in the SUN'S well (not its own surface well).
Author: J.C. Harvey, Melbourne.  SDT — Depth-Closure.

Harvey's correction (2026-06-20): "Venus is deeper in the gravitational influence of the Sun."
The relevant depth for reflected SUNLIGHT is where the reflector sits in the SUN's field:
    z_sun(r) = koppa_sun / r ,   koppa_sun = v_surf_sun^2 R_sun / c^2   (SDT primitives, NO GM)
This FALLS with distance from the Sun -> explains why Saturn (farther) < Jupiter, monotonically.

Reflection = absorption + re-emission (minus wavelengths kept as heat = albedo).  Two readings:
  RE-STAMP : re-emission encodes the LOCAL solar depth z_sun(r) -> reflected light tracks z_sun(r)
             -> VENUS (0.72 AU, deep) MORE shifted than JUPITER (5.2 AU, shallow).
  PRESERVE : elastic scatter carries the Sun's ORIGINAL surface stamp (633) through unchanged
             -> reflector silent -> flat 633 (this is SDT 'encoded at emission, stable', and GR).
DECISIVE FACT: reflected sunlight is observed to carry the FULL ~633 m/s solar redshift.  If
re-emission re-stamped to the local depth it would carry only z_sun(r)~a few m/s, NOT 633.
-> the Sun's-surface stamp IS preserved through reflection -> PRESERVE wins, RE-STAMP falsified.
"""
c = 299792458.0
v_surf_Sun, R_sun = 436762.0, 6.957e8            # SDT primitives (NO GM)
koppa_sun = v_surf_Sun*v_surf_Sun*R_sun/(c*c)    # = ϟ_sun
AU = 1.495978707e11
def zsun_c(r_AU):                                 # Sun's-well depth at heliocentric r, in m/s
    return koppa_sun*c/(r_AU*AU)

print(f"koppa_sun = {koppa_sun:.1f} m   (from v_surf_sun, R_sun; NO GM)\n")
print("THE COMPARISON YOU ASKED FOR — position in the SUN's well (falls with distance):")
planets = {"Venus":0.7233,"Earth":1.0,"Mars":1.5237,"Jupiter":5.2044,"Saturn":9.5826}
for p,a in planets.items():
    print(f"  {p:8} r={a:6.3f} AU   z_sun*c = {zsun_c(a):6.3f} m/s")
print(f"\n  VENUS - JUPITER = {zsun_c(0.7233)-zsun_c(5.2044):+.3f} m/s   (Venus deeper -> MORE shift, RE-STAMP)")
print(f"  SATURN < JUPITER: {zsun_c(9.5826):.3f} < {zsun_c(5.2044):.3f}  (farther = shallower = less; your point)")

# --- Re-test Lanza 2016 with the CORRECT predictor: x = z_sun(r_body), not the body's own well ---
# (heliocentric distance ~ semi-major axis; asteroid epoch distances vary, flagged as approximate)
# (RV m/s, SD, N, a_AU)
T2 = {
 "Moon":(99.39,1.67,6,1.00),"Vesta":(101.68,3.39,24,2.362),"Pallas":(99.41,3.96,7,2.773),
 "Iris":(97.57,4.31,5,2.386),"Ganymede":(99.07,1.56,17,5.204),"Europa":(101.32,3.06,10,5.204),
 "Io":(90.18,3.36,7,5.204),"Ceres":(98.21,6.58,7,2.766),
}
def wls(bodies):
    S=Sx=Sy=Sxx=Sxy=0.0
    for b in bodies:
        rv,sd,n,a = T2[b]; x=zsun_c(a); se=sd/n**0.5; w=1/se**2
        S+=w;Sx+=w*x;Sy+=w*rv;Sxx+=w*x*x;Sxy+=w*x*rv
    D=S*Sxx-Sx*Sx
    return (Sxx*Sy-Sx*Sxy)/D,(S*Sxy-Sx*Sy)/D,(S/D)**0.5

print("\n--- Lanza 2016 RV vs z_sun(r_body).  RE-STAMP predicts slope +1 ; PRESERVE/SDT-stable/GR predicts 0 ---")
print(f"{'body':9}{'r(AU)':>7}{'z_sun*c':>9}{'meas RV':>9}{'SE':>6}")
for b in ["Moon","Vesta","Pallas","Iris","Ganymede","Europa","Io","Ceres"]:
    rv,sd,n,a=T2[b]; print(f"{b:9}{a:>7.2f}{zsun_c(a):>9.3f}{rv:>9.2f}{sd/n**0.5:>6.2f}")
clean=["Moon","Vesta","Pallas","Iris","Ganymede","Europa"]
a,b,sb=wls(clean)
print(f"\nclean set slope = {b:+.2f} +- {sb:.2f}  (intercept {a:.1f})")
print(f"  -> from RE-STAMP(+1): {abs(b-1)/sb:.1f}sigma ;  from PRESERVE(0): {abs(b)/sb:.1f}sigma")
print("\nDECISIVE without any fit: reflected sunlight carries the FULL ~633 m/s solar stamp.")
print("Re-stamp to local depth would give ~1-3 m/s, not 633.  -> stamp PRESERVED -> reflector silent.")
