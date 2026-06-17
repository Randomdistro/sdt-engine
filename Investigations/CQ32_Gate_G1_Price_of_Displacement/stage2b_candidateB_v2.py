"""CQ-32 Stage 2 Candidate B (v2) — grammar-faithful R7/R8 arrangements.
Li6 = alpha(tetra) + EXTERNAL deuteron off one face; Be9 = 2 alpha (vertex-in) + bridging n.
Same parameter-free r_c=2.818, s=2*R_ring. NO energies (R1). Writes volumes_B2.json."""
import random, math, json, os
random.seed(42)
HERE=os.path.dirname(os.path.abspath(__file__))
a_p=0.8412; R_ring=a_p/math.sqrt(2.0/3.0); r_c=2.818; s=2.0*R_ring; N=1_000_000

def vadd(a,b): return (a[0]+b[0],a[1]+b[1],a[2]+b[2])
def vsub(a,b): return (a[0]-b[0],a[1]-b[1],a[2]-b[2])
def vscale(a,k): return (a[0]*k,a[1]*k,a[2]*k)
def vnorm(a):
    m=math.sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]); return (a[0]/m,a[1]/m,a[2]/m) if m>1e-12 else (0,0,0)

def tetra(s):
    k=s/(2*math.sqrt(2)); return [(k,k,k),(k,-k,-k),(-k,k,-k),(-k,-k,k)]
def triangle(s): return [(0,0,0),(s,0,0),(s/2,s*math.sqrt(3)/2,0)]
def dimer(s): return [(0,0,0),(s,0,0)]

def li6(s):                                   # alpha + external deuteron off one face
    T=tetra(s)
    cF=vscale(vadd(vadd(T[0],T[1]),T[2]),1.0/3.0)   # centroid of face opposite T[3]
    apex=vsub(vscale(cF,2.0),T[3])                  # close-packed site over face (dist s from T0,T1,T2)
    d2=vadd(apex,vscale(vnorm(cF),s))               # deuteron extends outward
    return T+[apex,d2]

def tetra_xvertex(s):                          # regular tetra, one vertex on +x, circumradius 0.6124 s
    a=2*math.sqrt(2)/3.0; k=s/1.6329931619
    V=[(1.0,0,0),(-1.0/3,a,0),(-1.0/3,-a/2,a*math.sqrt(3)/2),(-1.0/3,-a/2,-a*math.sqrt(3)/2)]
    return [vscale(v,k) for v in V]
def be9(s):                                    # 2 alpha (vertex-in at +-s) bridged by n at origin
    rc=0.6124*s
    T=tetra_xvertex(s)
    a1=[vadd(v,(-s-rc,0,0)) for v in T]        # inner vertex -> (-s,0,0); body extends -x
    a2=[(-x,y,z) for (x,y,z) in a1]            # mirror -> inner vertex (+s,0,0); body +x
    return a1+a2+[(0,0,0)]

def union_vol(points,r,N):
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
      'a':tetra(s),'Li6':li6(s),'Be9':be9(s)}
Vu={k:union_vol(v,r_c,N) for k,v in geom.items()}
print(f"r_c={r_c} s={s:.4f}  (v2: Li6=alpha+external d, Be9=2alpha+bridge n)")
for k in geom: print(f"  Vu({k:4s})={Vu[k]:8.3f}  deficit={len(geom[k])*Vsph-Vu[k]:8.3f}")
reactions={'R1_dd_to_a':(['d','d'],['a']),'R2_tp_to_a':(['t','p'],['a']),
 'R3_hn_to_a':(['h','n'],['a']),'R4_dt_to_an':(['d','t'],['a','n']),
 'R5_dd_to_tp':(['d','d'],['t','p']),'R6_dd_to_hn':(['d','d'],['h','n']),
 'R7_ad_to_Li6':(['a','d'],['Li6']),'R8_2an_to_Be9':(['a','a','n'],['Be9'])}
dV={nm: sum(Vu[x] for x in Rr)-sum(Vu[x] for x in L) for nm,(L,Rr) in reactions.items()}
for nm in reactions: print(f"  {nm:14s} dV={dV[nm]:+.3f}")
json.dump({'B2_grammar_faithful':dV}, open(os.path.join(HERE,'volumes_B2.json'),'w'), indent=2)
print("wrote volumes_B2.json")
