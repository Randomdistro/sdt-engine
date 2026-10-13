import csv, numpy as np, re
from scipy.stats import spearmanr
L='../../../Datasets/nuclear/neutron_multiplicity/'
SYS={'U235':('Nishio1998_U235_nth_f_nuA.csv',92,236,0.8),'U233':('Nishio1998_U233_nth_f_nuA.csv',92,234,0.8),'Cf252':('BudtzJorgensen1988_Cf252_sf_nuA.csv',98,252,0.7)}
src=open('../../../Engine/include/sdt/laws.hpp',encoding='utf-8').read()
MAG=[int(x) for x in re.search(r'magic_numbers\[7\]\s*=\s*\{([^}]*)\}',src).group(1).split(',')]
def u(N,mag=MAG):
    N=np.asarray(N,float); c=np.zeros_like(N)
    for m in sorted(mag): c=np.where(m<=N,m,c)
    return N-c
def load(f,Zp,Ap):
    r=list(csv.DictReader(open(L+f)));A=np.array([float(x['MASS']) for x in r]);nu=np.array([float(x['DATA']) for x in r])
    N=A-A*Zp/Ap; return A,N,nu
def scan(N,nu,lo=70,hi=100):
    out={}
    for nb in range(lo,hi+1):
        X=np.c_[np.ones_like(N),N,np.maximum(0,N-nb)];b,res,*_=np.linalg.lstsq(X,nu,rcond=None)
        out[nb]=(float(((nu-X@b)**2).sum()),b[1],b[1]+b[2])
    return out
# validation
assert list(u([50,81,82,83,125,126,127]))==[0,31,0,1,43,0,1],'V1'
rng=np.random.default_rng(1);Nn=np.linspace(70,110,60);tr=np.where(Nn<88,2-0.05*(Nn-70),1.1+0.12*(Nn-88))+rng.normal(0,.08,60)
s=scan(Nn,tr);best=min(s,key=lambda k:s[k][0]);assert abs(best-88)<=2,'V2 %d'%best
a=np.argsort(np.argsort(tr)).astype(float);b=np.argsort(np.argsort(Nn)).astype(float)
assert abs(np.corrcoef(a,b)[0,1]-spearmanr(tr,Nn)[0])<1e-9,'V3'
#print('validation V1-V3 pass (V2 planted 88, recovered',best,')\n')

print('Round 2: heavy branch N>=70, V-shape, break scan 74..92 (19 breaks)')
for k,(f,Zp,Ap,g1) in SYS.items():
    A,N,nu=load(f,Zp,Ap); m=N>=70; N=N[m]; nu=nu[m]
    res={}
    for nb in range(74,93):
        X=np.c_[np.ones_like(N),np.minimum(0,N-nb),np.maximum(0,N-nb)]
        b=np.linalg.lstsq(X,nu,rcond=None)[0]; res[nb]=(float(((nu-X@b)**2).sum()),b[1],b[2])
    order=sorted(res,key=lambda q:res[q][0]); best=order[0]; r82=order.index(82)+1
    ok=abs(best-82)<=2 and r82<=3 and res[best][1]<=0<res[best][2]
    print(f'{k}: n={m.sum()} best N_b={best} rank82={r82}/19 slopes b={res[best][1]:+.3f} c={res[best][2]:+.3f}  G2prime {"PASS" if ok else "FAIL"}')
    print('   RSS top5:',[(q,round(res[q][0],3)) for q in order[:5]],' RSS@82=',round(res[82][0],3))
    Nmin=N[np.argmin(nu)]; print('   N at minimum nu in data:',round(float(Nmin),1),' nu_min=',round(float(nu.min()),3))
