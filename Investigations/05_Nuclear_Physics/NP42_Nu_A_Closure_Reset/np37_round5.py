import re, csv, numpy as np
RAW='../../../Datasets/nuclear/fission_z_distribution/raw/exa_APP-A1_first140k.txt'
NU='../../../Datasets/nuclear/neutron_multiplicity/Nishio1998_U235_nth_f_nuA.csv'
# --- parse U235T only
sec=None; FI={}
for l in open(RAW,encoding='utf-8',errors='replace'):
    m=re.search(r'Appendix A\.1 - (\S+) Yields',l)
    if m: sec=m.group(1); continue
    m=re.match(r'^\s*(\d+)\s*([A-Z][a-z]?)\s*(\d+)\s+([0-9.]+E[+-]\d+)(\*?)\s',l)
    if m and sec=='U235T': FI.setdefault(int(m.group(3)),[]).append((int(m.group(1)),float(m.group(4)),m.group(5)=='*'))
# validation V1: FI sums to ~1 per A; V2: known Sn-130 row; V3: Z(A) monotone-ish
for A,v in FI.items():
    s=sum(x[1] for x in v); assert abs(s-1)<0.02 or A>170 or A<62,(A,s)
assert any(z==50 and abs(f-0.66625)<1e-4 for z,f,_ in FI[130]),'V2 Sn130'
Zmean={A:sum(z*f for z,f,_ in v)/sum(f for _,f,_ in v) for A,v in FI.items()}
Zmode={A:max(v,key=lambda x:x[1])[0] for A,v in FI.items()}
print('validation V1-V2 passed; A range',min(FI),max(FI))
print('  A  <Z>  modeZ   (post-neutron mass)'); [print(f'{A:4d} {Zmean[A]:6.2f} {Zmode[A]:3d}') for A in range(124,138)]
As=np.array(sorted(Zmean)); Zm=np.array([Zmean[a] for a in As]); Zd=np.array([Zmode[a] for a in As],float)
r=list(csv.DictReader(open(NU)));A=np.array([float(x['MASS']) for x in r]);nu=np.array([float(x['DATA']) for x in r])
e=np.array([float(x['ERR-S']) if x['ERR-S'] else np.nan for x in r]); med=np.nanmedian(e); e=np.where(np.isnan(e),med,e)
print('missing ERR-S replaced by median',round(med,4),'count',int(np.isnan([float(x['ERR-S']) if x['ERR-S'] else np.nan for x in r]).sum()))
Ap=A-nu
def run(Zarr,label):
    Z=np.interp(Ap,As,Zarr); N=A-Z; m=N>=70; N,y,s=N[m],nu[m],e[m]; w=1/s**2
    grid=np.arange(74,92.001,0.25); chi={}; sl={}
    for nb in grid:
        X=np.c_[np.ones_like(N),np.minimum(0,N-nb),np.maximum(0,N-nb)]
        W=np.sqrt(w); b=np.linalg.lstsq(X*W[:,None],y*W,rcond=None)[0]
        chi[nb]=float((((y-X@b)*W)**2).sum()); sl[nb]=(b[1],b[2])
    dof=len(N)-4; cmin=min(chi.values()); scale=max(cmin/dof,1.0)  # scale errors up only if chi2/dof>1
    best=min(chi,key=chi.get); S=[nb for nb in grid if (chi[nb]-cmin)/scale<=4]
    print(f'\n[{label}] n={len(N)} chi2_min={cmin:.1f} dof={dof} (scale {scale:.2f}) best N*_b={best:.2f} slopes b={sl[best][0]:+.3f} c={sl[best][1]:+.3f}')
    print(f'   dchi2<=4 set: {min(S):.2f}..{max(S):.2f}')
    ok=abs(best-82)<=1.0 and (82.0 in [round(x,2) for x in S]) and sl[best][0]<=0<sl[best][1]
    print(f'   G5: |best-82|={abs(best-82):.2f} (<=1)  82 in set: {82.0 in [round(x,2) for x in S]}  slope signs ok: {sl[best][0]<=0<sl[best][1]}  -> {"PASS" if ok else "FAIL"}')
    for t in (80,84): print(f'   null {t}: in set {float(t) in [round(x,2) for x in S]}  dchi2={(chi[float(t)]-cmin)/scale:.2f}')
    print(f'   dchi2 at 82: {(chi[82.0]-cmin)/scale:.2f}')
    i=np.argmin(y); print(f'   lowest-nu point: A*={A[m][i]} nu={y[i]:.3f} N*={N[i]:.2f}')
    return best
run(Zm,'mean Z'); run(Zd,'mode Z')
