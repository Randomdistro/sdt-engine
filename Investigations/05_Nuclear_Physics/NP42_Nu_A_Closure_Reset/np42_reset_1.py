import csv, statistics, math, random, sys
def load_nu(p):
    out=[]
    for r in csv.DictReader(open(p,encoding='utf-8')):
        e=r.get('ERR-S') or r.get('DATA-ERR') or ''
        out.append([float(r['MASS']),float(r['DATA']),float(e) if e.strip() else None])
    med=statistics.median([x[2] for x in out if x[2] is not None])
    for x in out:
        if x[2] is None: x[2]=med
    return out,med
def zbar(p,Zp,Ap):
    num={};den={}
    for r in csv.DictReader(open(p,encoding='utf-8')):
        if r['daughter_level_idx']!='0' or int(r['z_parent'])!=Zp or int(r['a_parent'])!=Ap-1: continue
        try: fy=float(r['independent_thermal_fy'])
        except: continue
        A=int(r['a_daughter']); Z=int(r['z_daughter'])
        num[A]=num.get(A,0)+Z*fy; den[A]=den.get(A,0)+fy
    return {A:num[A]/den[A] for A in den if den[A]>0}
def interp(zb,A):
    lo=math.floor(A); hi=lo+1
    if lo in zb and hi in zb: return zb[lo]+(zb[hi]-zb[lo])*(A-lo)
    return zb.get(round(A))
def fit(pts,Nb):
    S=[[0,0,0],[0,0,0]]
    for N,nu,s in pts:
        w=1/s/s; x=max(0,N-Nb); S[0][0]+=w; S[0][1]+=w*x; S[1][1]+=w*x*x; S[0][2]+=w*nu; S[1][2]+=w*x*nu
    det=S[0][0]*S[1][1]-S[0][1]**2
    a=(S[0][2]*S[1][1]-S[0][1]*S[1][2])/det; c=(S[0][0]*S[1][2]-S[0][1]*S[0][2])/det
    chi=sum(((nu-(a+c*max(0,N-Nb)))/s)**2 for N,nu,s in pts); return a,c,chi
def scan(pts):
    grid=[74+0.25*i for i in range(73)]; res=[(Nb,)+fit(pts,Nb) for Nb in grid]
    best=min(res,key=lambda r:r[3]); dof=len(pts)-3; scale=max(1.0,best[3]/dof)
    S=[r[0] for r in res if (r[3]-best[3])/scale<=4]
    return best,scale,S,res
print("NP42 reset instrument 1 (2026-10-10)\n====================================\n")
nu235,med235=load_nu('Datasets/nuclear/neutron_multiplicity/Nishio1998_U235_nth_f_nuA.csv')
random.seed(20261010); syn=[(N,1.0+0.12*max(0,N-85.0)+random.gauss(0,med235),med235) for N in [70+0.5*i for i in range(60)]]
b,sc,S,_=scan(syn); ok1=abs(b[0]-85.0)<=0.5; print("[V1] planted break 85.0 recovered at %.2f (Delta-chi2<=4 set %.2f-%.2f) -> %s"%(b[0],min(S),max(S),"met" if ok1 else "NOT MET"))
zb235=zbar('Datasets/nuclear/IAEA_U235_independent_FY.csv',92,236)
dev=[abs(zb235[A]+zb235[234-A]-92) for A in range(85,111) if A in zb235 and 234-A in zb235]; m=sum(dev)/len(dev); ok2=m<0.5
print("[V2] complementary Z balance U-235, A=85-110: mean |Zl+Zh-92| = %.3f (n=%d) -> %s\n"%(m,len(dev),"met" if ok2 else "NOT MET"))
if not(ok1 and ok2): print("VALIDATIONS NOT MET"); sys.exit(1)
print("VALIDATIONS: met\n")
systems=[('U-235','Datasets/nuclear/neutron_multiplicity/Nishio1998_U235_nth_f_nuA.csv','Datasets/nuclear/IAEA_U235_independent_FY.csv',92,236),
         ('U-233','Datasets/nuclear/neutron_multiplicity/Nishio1998_U233_nth_f_nuA.csv','Datasets/nuclear/fission_yields/IAEA_233U_independent_FY.csv',92,234)]
allpass=True
for name,pn,pf,Zp,Ap in systems:
    nu,med=load_nu(pn); zb=zbar(pf,Zp,Ap); pts=[]
    for A,v,s in nu:
        z=interp(zb,A-v)
        if z is None: continue
        N=A-z
        if N>=70: pts.append((N,v,s))
    best,scale,S,res=scan(pts)
    g=(abs(best[0]-82)<=1.0) and (82.0 in S) and best[2]>0; allpass&=g
    chi82=[r for r in res if r[0]==82.0][0]
    print("%s: points N*>=70: %d (median err %.4f) ; best N_b = %.2f, a = %.4f, c = %.4f, chi2/dof = %.2f ; Delta-chi2<=4 set %.2f-%.2f ; 82 in set: %s ; Delta-chi2(82) = %.2f -> G6 %s"%(
        name,len(pts),med,best[0],best[1],best[2],best[3]/(len(pts)-3),min(S),max(S),82.0 in S,(chi82[3]-best[3])/scale,"PASS" if g else "FAIL"))
    for t in (80.0,84.0): r=[x for x in res if x[0]==t][0]; print("   null %.0f: Delta-chi2 = %.2f, in set: %s"%(t,(r[3]-best[3])/scale,t in S))
print("\nG6 (both systems): %s"%("MET" if allpass else "NOT MET"))
