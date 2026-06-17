"""CQ-32 Stage 2 — Candidate A free-tube volumes (parameter-free) + the conservation test.
No reference to energies (R1). Tube: minor radius a=(W+1)hbar/(m c), major R=a/sqrt(2/3),
torus volume V = 2 pi^2 R a^2."""
import math
hbar=1.054571817e-34; c=2.99792458e8
mp=1.67262192369e-27; mn=1.67492749804e-27
fm=1e-15

def tube(mX, W=3):
    a=(W+1)*hbar/(mX*c); R=a/math.sqrt(2/3); V=2*math.pi**2*R*a**2
    return a/fm, R/fm, V/fm**3
ap,Rp,Vp=tube(mp); an,Rn,Vn=tube(mn)

content={'p':(1,0),'n':(0,1),'d':(1,1),'t':(1,2),'h':(2,1),'a':(2,2),'Li6':(3,3),'Be9':(4,5)}
Vfree=lambda nm:(content[nm][0]*Vp+content[nm][1]*Vn)
reactions={
 'R1_dd_to_a':(['d','d'],['a']), 'R2_tp_to_a':(['t','p'],['a']),
 'R3_hn_to_a':(['h','n'],['a']), 'R4_dt_to_an':(['d','t'],['a','n']),
 'R5_dd_to_tp':(['d','d'],['t','p']), 'R6_dd_to_hn':(['d','d'],['h','n']),
 'R7_ad_to_Li6':(['a','d'],['Li6']), 'R8_2an_to_Be9':(['a','a','n'],['Be9']),
}
print(f"proton tube : a={ap:.4f} fm  R={Rp:.4f} fm  V_free={Vp:.4f} fm^3")
print(f"neutron tube: a={an:.4f} fm  R={Rn:.4f} fm  V_free={Vn:.4f} fm^3")
print("free-tube volumes (linked model, sum of constituent tubes):")
for nm in content: print(f"  V_free({nm:4s}) = {Vfree(nm):8.4f} fm^3")
print("--- dV_free across the 8 reactions (Candidate A, NO overlap term) ---")
allzero=True
for nm,(L,R) in reactions.items():
    dV=sum(Vfree(x) for x in R)-sum(Vfree(x) for x in L)
    if abs(dV)>1e-9: allzero=False
    print(f"  {nm:14s} dV_free = {dV:+.6e} fm^3")
print(f"\nALL dV_free == 0 (nucleon-conserving): {allzero}")
print("=> free-tube volume is a NULL channel; binding lives entirely in the OVERLAP/deficit term.")
