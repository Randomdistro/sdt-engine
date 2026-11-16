# GOM16 - The Vulcan Ledger. Native only: a = c^2*kop/r^2 (shadow bookkeeping, Law III).
# The interior shadow's effect on Mercury's apsides is DERIVED by direct orbit integration
# of the native force law - no rival machinery, no borrowed closed forms (one small-x
# analytic limit used solely as an integrator cross-check, i.e. calculus, not physics).
import math
c=299792458.0; DAY=86400.0; AU=1.495978707e11
kop_sun=1476.6332                      # m, kinematic (Earth a,T) - GOM15
aM=5.7909e10; eM=0.2056; TM=87.9691*DAY
kop_b=1.2423e-54                       # m per baryon - THE one seed anchor (FLM13), declared
N_IRON=4.754e30; N_SIL=1.97e30        # baryons/m^3 from lattice constants x A (kg-free)

def ring_radial(r, av, kv, K=256):
    # time-averaged interior ring shadow: radial acceleration on exterior body at r.
    # shadows add: integrate elemental pulls c^2*(kv/K)/d^2 around the ring. Pure quadrature.
    s=0.0
    for i in range(K):
        th=2*math.pi*(i+0.5)/K
        dx=r-av*math.cos(th); dy=-av*math.sin(th)
        d2=dx*dx+dy*dy; d=math.sqrt(d2)
        s+= (dx/d)/d2                  # radial component (toward ring centre line)
    return c*c*kv*s/K                  # [m/s^2], positive = toward Sun for r>av

def drift_arcsec_per_cy(av, kv, orbits=40, steps=3000):
    # integrate Mercury under a = -c^2*kop_sun/r^2 rhat - ring term; track e-vector angle.
    mu=c*c*kop_sun
    r0=aM*(1-eM); v0=math.sqrt(mu*(1+eM)/(aM*(1-eM)))   # perihelion start (native vis-viva)
    x,y,vx,vy=r0,0.0,0.0,v0
    dt=TM/steps
    def acc(x,y):
        r=math.hypot(x,y)
        a0=-mu/r**3
        ar=ring_radial(r,av,kv)/r      # per unit length, radial toward centre
        return (a0*x - ar*x, a0*y - ar*y)
    def evec(x,y,vx,vy):
        r=math.hypot(x,y); L=x*vy-y*vx
        ex=(vy*L)/mu - x/r; ey=(-vx*L)/mu - y/r
        return math.atan2(ey,ex)
    w0=evec(x,y,vx,vy)
    for n in range(orbits*steps):
        ax,ay=acc(x,y)
        x1,y1=x+vx*dt/2, y+vy*dt/2
        vx1,vy1=vx+ax*dt/2, vy+ay*dt/2
        ax1,ay1=acc(x1,y1)
        x+=vx1*dt; y+=vy1*dt; vx+=ax1*dt; vy+=ay1*dt
    w1=evec(x,y,vx,vy)
    dw=(w1-w0)
    while dw>math.pi: dw-=2*math.pi
    while dw<-math.pi: dw+=2*math.pi
    per_orbit=dw/orbits
    return per_orbit*(100*365.25*DAY/TM)*206265.0

print("="*96)
print(" GOM16 - the shaken box. Native force a=c^2*kop/r^2; interior shadow by quadrature;")
print(" apsidal response by direct integration. kop_b seed declared. No G/M anywhere.")
print("="*96)
# integrator null + linearity + small-x cross-check
null=drift_arcsec_per_cy(0.10*AU, 0.0)
print(f"# NULL (kv=0): drift = {null:.3e} arcsec/cy  (numerical floor)")
kv_test=1.0
d1=drift_arcsec_per_cy(0.10*AU, kv_test); d03=drift_arcsec_per_cy(0.10*AU, 0.3*kv_test)
print(f"# linearity @0.10 AU: kv=1.0 -> {d1:.4f}; kv=0.3 -> {d03:.4f}  ratio {d1/d03:.3f} (expect ~3.33)")
x=0.10*AU/aM
analytic=0.75*(kv_test/kop_sun)*x*x/(1-eM**2)**2 *(100*365.25*DAY/TM)*206265.0
print(f"# small-x cross-check (calculus limit): analytic ~{analytic:.4f} vs integrated {d1:.4f}")
print()
print("# Sensitivity S(a_v) and koppa ceilings for the two DECLARED residual bounds:")
print("#  a_v[AU]   S[arcsec/cy per m]   kop_max(0.03\")[m]  kop_max(0.005\")[m]  iron-R[km]  sil-R[km]")
for avAU in (0.06,0.08,0.10,0.125,0.15,0.175,0.21):
    S=drift_arcsec_per_cy(avAU*AU, kv_test)/kv_test
    for bound,label in ((0.03,"c"),(0.005,"a")):
        pass
    k_c=0.03/abs(S); k_a=0.005/abs(S)
    Nb=k_c/kop_b
    Rfe=( (3*Nb/(4*math.pi*N_IRON)) )**(1/3)/1000.0
    Rsi=( (3*Nb/(4*math.pi*N_SIL )) )**(1/3)/1000.0
    print(f"#   {avAU:5.3f}    {S:12.4f}        {k_c:.3e}       {k_a:.3e}      {Rfe:8.1f}   {Rsi:8.1f}")
print()
print("# Discriminator (for ANY announced Vulcan at a_v, size s): its koppa ceiling from the")
print("# ledger -> mean baryon density n = 3*kop/(4*pi*kop_b*s^3) -> class: n>3e30 iron-like,")
print("# ~2e30 silicate, <1e30 rubble/ice(excluded by survival physics inside 0.21 AU anyway).")
print("# Imaged-class vulcanoid (s = 6 km, IRON): ")
s=6000.0; Nb=(4/3)*math.pi*s**3*N_IRON; kv=Nb*kop_b
d=drift_arcsec_per_cy(0.10*AU,kv)
print(f"#   N = {Nb:.3e} baryons  kop = {kv:.3e} m  -> drift {d:.3e} arcsec/cy: INVISIBLE to the apsides.")
print("# CONCLUSION: precession bounds the TOTAL interior shadow (Pluto-class ceilings above);")
print("# for km-class bodies the ledger cannot discriminate composition - SURVIVAL physics does:")
print("# at 0.06-0.21 AU (600-1500 K) ice is excluded, silicates marginal inside ~0.1 AU ->")
print("# PREDICTION: any true Vulcan is refractory, iron-dominant; density class n ~ 4.8e30 b/m^3.")
