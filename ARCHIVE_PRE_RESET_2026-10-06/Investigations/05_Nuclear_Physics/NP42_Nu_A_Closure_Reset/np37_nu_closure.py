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
print('validation V1-V3 pass (V2 planted 88, recovered',best,')\n')
for k,(f,Zp,Ap,g1) in SYS.items():
    A,N,nu=load(f,Zp,Ap)
    m=(N>=82)&(N<126);rho=spearmanr(u(N[m]),nu[m])[0]
    s=scan(N,nu);order=sorted(s,key=lambda k:s[k][0]);best=order[0];rank82=order.index(82)+1
    print(f'{k}: n={len(A)}  G1 rho(nu,u | 82<=N<126, n={m.sum()}) = {rho:+.3f} (gate >={g1})  {"PASS" if rho>=g1 else "FAIL"}')
    print(f'   G2 best break N_b={best}; rank of 82 = {rank82}/31  slopes at best: {s[best][1]:+.3f} -> {s[best][2]:+.3f}  {"PASS" if abs(best-82)<=2 and rank82<=3 else "FAIL"}')
    print('   RSS top5 breaks:',[(k2,round(s[k2][0],3)) for k2 in order[:5]],' RSS@82=',round(s[82][0],3))
    for name,mg in (('80/84/86 shifts',None),):
        for sh in (80,84,86):
            mg2=[sh if x==82 else x for x in MAG]; mm=(N>=sh)&(N<126)
            print(f'   null closure {sh}: rho={spearmanr(u(N[mm],mg2),nu[mm])[0]:+.3f} n={mm.sum()}  rank of break {sh} = {order.index(sh)+1}')
