import csv, numpy as np
D='../../../Datasets/nuclear/'
SYS={'U235':(D+'IAEA_U235_independent_FY.csv',D+'neutron_multiplicity/Nishio1998_U235_nth_f_nuA.csv'),
     'U233':(D+'fission_yields/IAEA_233U_independent_FY.csv',D+'neutron_multiplicity/Nishio1998_U233_nth_f_nuA.csv')}
def zA(path):
    S={};SZ={}
    for r in csv.DictReader(open(path)):
        if r['daughter_level_idx']!='0': continue
        f=float(r['independent_thermal_fy'] or 0); a=int(r['a_daughter']); z=int(r['z_daughter'])
        S[a]=S.get(a,0)+f; SZ[a]=SZ.get(a,0)+f*z
    As=np.array(sorted(a for a in S if S[a]>0)); return As,np.array([SZ[a]/S[a] for a in As]),S
# validation: Sn-130-like mean Z near 50 at A~130; summed yields ~ 200% over all A
for k,(fy,nu) in SYS.items():
    As,Zm,S=zA(fy); i=list(As).index(130)
    print(f'{k}: A range {As.min()}-{As.max()}, total yield sum {sum(S.values()):.1f} (expect ~200 for %), <Z>(130)={Zm[i]:.2f}, <Z>(134)={Zm[list(As).index(134)]:.2f}')
    assert 49<Zm[i]<52
for k,(fy,nuf) in SYS.items():
    As,Zm,_=zA(fy)
    r=list(csv.DictReader(open(nuf)));A=np.array([float(x['MASS']) for x in r]);nu=np.array([float(x['DATA']) for x in r])
    e=np.array([float(x['ERR-S']) if x['ERR-S'] else np.nan for x in r]);e=np.where(np.isnan(e),np.nanmedian(e),e)
    Z=np.interp(A-nu,As,Zm);N=A-Z;m=N>=70;N,y,s=N[m],nu[m],e[m];w=1/s**2;W=np.sqrt(w)
    grid=np.arange(74,92.001,0.25);chi={};par={}
    for nb in grid:
        X=np.c_[np.ones_like(N),np.maximum(0,N-nb)];b=np.linalg.lstsq(X*W[:,None],y*W,rcond=None)[0]
        chi[nb]=float((((y-X@b)*W)**2).sum());par[nb]=b
    dof=len(N)-3;cmin=min(chi.values());sc=max(cmin/dof,1.0);best=min(chi,key=chi.get)
    S4=[nb for nb in grid if (chi[nb]-cmin)/sc<=4]
    ok=abs(best-82)<=1 and 82.0 in [round(x,2) for x in S4] and par[best][1]>0
    print(f'\n[{k}] n={len(N)} chi2/dof={cmin/dof:.2f} best N_b={best:.2f} floor={par[best][0]:.3f} slope={par[best][1]:+.3f}/neutron  dchi2<=4 set {min(S4):.2f}..{max(S4):.2f}')
    print(f'   dchi2 at 82 = {(chi[82.0]-cmin)/sc:.2f}; at 80 = {(chi[80.0]-cmin)/sc:.2f}; at 84 = {(chi[84.0]-cmin)/sc:.2f}   G6 -> {"PASS" if ok else "FAIL"}')
