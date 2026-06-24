"""CQ-32 Stage 4 geometry — union VOLUME and SURFACE AREA of conscription spheres (v2 geometry).
No energies (R1). Writes volumes_areas.json = {nucleus: {V, A}} in fm^3 / fm^2."""
import random, math, json, os
random.seed(7)
HERE=os.path.dirname(os.path.abspath(__file__))
a_p=0.8412; R_ring=a_p/math.sqrt(2.0/3.0); r_c=2.818; s=2.0*R_ring
NV=1_000_000; NA=150_000

def vadd(a,b): return (a[0]+b[0],a[1]+b[1],a[2]+b[2])
def vsub(a,b): return (a[0]-b[0],a[1]-b[1],a[2]-b[2])
def vscale(a,k): return (a[0]*k,a[1]*k,a[2]*k)
def vnorm(a):
    m=math.sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]); return (a[0]/m,a[1]/m,a[2]/m) if m>1e-12 else (0,0,0)
def tetra(s):
    k=s/(2*math.sqrt(2)); return [(k,k,k),(k,-k,-k),(-k,k,-k),(-k,-k,k)]
def triangle(s): return [(0,0,0),(s,0,0),(s/2,s*math.sqrt(3)/2,0)]
def dimer(s): return [(0,0,0),(s,0,0)]
def li6(s):
    T=tetra(s); cF=vscale(vadd(vadd(T[0],T[1]),T[2]),1.0/3.0)
    apex=vsub(vscale(cF,2.0),T[3]); d2=vadd(apex,vscale(vnorm(cF),s)); return T+[apex,d2]
def tetra_xvertex(s):
    a=2*math.sqrt(2)/3.0; k=s/1.6329931619
    V=[(1.0,0,0),(-1.0/3,a,0),(-1.0/3,-a/2,a*math.sqrt(3)/2),(-1.0/3,-a/2,-a*math.sqrt(3)/2)]
    return [vscale(v,k) for v in V]
def be9(s):
    rc=0.6124*s; T=tetra_xvertex(s)
    a1=[vadd(v,(-s-rc,0,0)) for v in T]; a2=[(-x,y,z) for (x,y,z) in a1]; return a1+a2+[(0,0,0)]

def union_vol(P,r,N):
    xs=[p[0] for p in P]; ys=[p[1] for p in P]; zs=[p[2] for p in P]
    x0,x1=min(xs)-r,max(xs)+r; y0,y1=min(ys)-r,max(ys)+r; z0,z1=min(zs)-r,max(zs)+r
    bv=(x1-x0)*(y1-y0)*(z1-z0); r2=r*r; ins=0; rnd=random.random
    for _ in range(N):
        x=x0+(x1-x0)*rnd(); y=y0+(y1-y0)*rnd(); z=z0+(z1-z0)*rnd()
        for (px,py,pz) in P:
            dx=x-px; dy=y-py; dz=z-pz
            if dx*dx+dy*dy+dz*dz<=r2: ins+=1; break
    return bv*ins/N

def union_area(P,r,M):
    # sum over spheres of (exposed surface fraction) * 4 pi r^2
    r2=r*r; area_one=4*math.pi*r2; total=0.0; rnd=random.random
    for i,ci in enumerate(P):
        exp=0
        for _ in range(M):
            # uniform point on unit sphere
            u=2*rnd()-1; phi=2*math.pi*rnd(); sq=math.sqrt(1-u*u)
            x=ci[0]+r*sq*math.cos(phi); y=ci[1]+r*sq*math.sin(phi); z=ci[2]+r*u
            inside=False
            for j,cj in enumerate(P):
                if j==i: continue
                dx=x-cj[0]; dy=y-cj[1]; dz=z-cj[2]
                if dx*dx+dy*dy+dz*dz<r2: inside=True; break
            if not inside: exp+=1
        total+=area_one*exp/M
    return total

geom={'p':[(0,0,0)],'n':[(0,0,0)],'d':dimer(s),'t':triangle(s),'h':triangle(s),
      'a':tetra(s),'Li6':li6(s),'Be9':be9(s)}
out={}
for k,v in geom.items():
    V=union_vol(v,r_c,NV); A=union_area(v,r_c,NA); out[k]={'V':V,'A':A}
    print(f"  {k:4s}  V={V:8.3f} fm^3   A={A:8.3f} fm^2")
json.dump(out, open(os.path.join(HERE,'volumes_areas.json'),'w'), indent=2)
print("wrote volumes_areas.json")
