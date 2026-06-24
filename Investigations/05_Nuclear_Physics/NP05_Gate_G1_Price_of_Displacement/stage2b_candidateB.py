"""CQ-32 Stage 2 Candidate B — wake/conscription-overlap deficit.
Parameter-free: r_c = nucleon c-boundary (2.818 fm); separation s = 2*R_ring (ring-edge contact,
R_ring = a_p/sqrt(2/3), a_p = 4 hbar/(m_p c)). V_disp(nucleus) = union volume of the A conscription
spheres at the declared cluster positions. NO reference to energies (R1). Writes volumes_B.json."""
import random, math, json, os
random.seed(42)
HERE = os.path.dirname(os.path.abspath(__file__))
a_p = 0.8412                       # fm (W+1 rule)
R_ring = a_p / math.sqrt(2.0/3.0)  # 1.0303 fm
r_c = 2.818                        # fm  nucleon c-boundary (conscription radius)
s   = 2.0 * R_ring                 # 2.0606 fm  ring-edge contact (parameter-free)
N   = 1_000_000

def tetra(s):                      # regular tetrahedron, edge s  (alpha)
    k = s/(2*math.sqrt(2)); return [(k,k,k),(k,-k,-k),(-k,k,-k),(-k,-k,k)]
def triangle(s):                   # equilateral triangle, edge s (t, h)
    return [(0,0,0),(s,0,0),(s/2, s*math.sqrt(3)/2, 0)]
def dimer(s):                      # d
    return [(0,0,0),(s,0,0)]
def octa(s):                       # Li6 first-cut (compact 6-body; alt to alpha+d) — FLAGGED
    a=s/math.sqrt(2); return [(a,0,0),(-a,0,0),(0,a,0),(0,-a,0),(0,0,a),(0,0,-a)]
def be9(s):                        # 2 alpha (tetra) + bridging n — crude compact arrangement — FLAGGED
    off=s
    return ([(x-off,y,z) for (x,y,z) in tetra(s)]
          + [(x+off,y,z) for (x,y,z) in tetra(s)] + [(0,0,0)])

def union_vol(points, r, N):
    xs=[p[0] for p in points]; ys=[p[1] for p in points]; zs=[p[2] for p in points]
    x0,x1=min(xs)-r,max(xs)+r; y0,y1=min(ys)-r,max(ys)+r; z0,z1=min(zs)-r,max(zs)+r
    boxv=(x1-x0)*(y1-y0)*(z1-z0); r2=r*r; inside=0; rnd=random.random; pts=points
    for _ in range(N):
        x=x0+(x1-x0)*rnd(); y=y0+(y1-y0)*rnd(); z=z0+(z1-z0)*rnd()
        for (px,py,pz) in pts:
            dx=x-px; dy=y-py; dz=z-pz
            if dx*dx+dy*dy+dz*dz<=r2: inside+=1; break
    return boxv*inside/N

Vsph=(4.0/3.0)*math.pi*r_c**3
geom={'p':[(0,0,0)],'n':[(0,0,0)],'d':dimer(s),'t':triangle(s),'h':triangle(s),
      'a':tetra(s),'Li6':octa(s),'Be9':be9(s)}
Vu={k:union_vol(v,r_c,N) for k,v in geom.items()}

def lens(r,sep): return (math.pi*(4*r+sep)*(2*r-sep)**2/12.0) if sep<2*r else 0.0
Vu_d_an = 2*Vsph - lens(r_c,s)
print(f"r_c={r_c} fm  s={s:.4f} fm  Vsph={Vsph:.3f} fm^3")
for k in geom:
    print(f"  Vu({k:4s})={Vu[k]:8.3f}  deficit={len(geom[k])*Vsph-Vu[k]:8.3f} fm^3")
print(f"  [two-stream] d: MC={Vu['d']:.3f}  analytic={Vu_d_an:.3f}  "
      f"diff={100*(Vu['d']-Vu_d_an)/Vu_d_an:+.2f}%")

reactions={'R1_dd_to_a':(['d','d'],['a']),'R2_tp_to_a':(['t','p'],['a']),
 'R3_hn_to_a':(['h','n'],['a']),'R4_dt_to_an':(['d','t'],['a','n']),
 'R5_dd_to_tp':(['d','d'],['t','p']),'R6_dd_to_hn':(['d','d'],['h','n']),
 'R7_ad_to_Li6':(['a','d'],['Li6']),'R8_2an_to_Be9':(['a','a','n'],['Be9'])}
dV={nm: sum(Vu[x] for x in Rr)-sum(Vu[x] for x in L) for nm,(L,Rr) in reactions.items()}
for nm in reactions: print(f"  {nm:14s} dV={dV[nm]:+.3f} fm^3")
json.dump({'B_conscription_rc2.818_s2R':dV}, open(os.path.join(HERE,'volumes_B.json'),'w'), indent=2)
print("wrote volumes_B.json (R7/R8 arrangements FLAGGED — first-cut clusters)")
