import json, numpy as np, collections
d=json.load(open('../../../Datasets/gw/GWTC_eventapi_2026-10-05.json',encoding='utf-8'))['events']
best={}
for k,e in d.items():
    n=e['commonName']
    if n not in best or e['version']>best[n]['version'] or (e['version']==best[n]['version'] and 'final_mass_source' in e and 'final_mass_source' not in best[n]): best[n]=e
have=[e for e in best.values() if all(isinstance(e.get(x),(int,float)) for x in ('mass_1_source','mass_2_source','final_mass_source'))]
print('unique events',len(best),' with m1,m2,final mass:',len(have),' catalogs:',dict(collections.Counter(e['catalog.shortName'] for e in have)))
rows=[]
for e in have:
    m1,m2,mf=e['mass_1_source'],e['mass_2_source'],e['final_mass_source']
    if m1<m2: m1,m2=m2,m1
    M=m1+m2; f=(M-mf)/M; q=m1/m2; eta=q/(1+q)**2
    rows.append((e['commonName'],q,eta,f,e.get('chi_eff'),M))
rows=[r for r in rows if r[3]>0]
print('with f>0:',len(rows))
q=np.array([r[1] for r in rows]);eta=np.array([r[2] for r in rows]);f=np.array([r[3] for r in rows]);chi=np.array([r[4] if isinstance(r[4],(int,float)) else np.nan for r in rows])
fl=eta/4
print('f_obs: median %.4f IQR %.4f-%.4f ; f_ledger median %.4f'%(np.median(f),*np.percentile(f,[25,75]),np.median(fl)))
m=q<1.5; print('G-A: q<1.5 n=%d median f_obs %.4f  f_ledger(median over same events) %.4f  ratio %.3f  within x2: %s'%(m.sum(),np.median(f[m]),np.median(fl[m]),np.median(f[m])/np.median(fl[m]),0.5<=np.median(f[m])/np.median(fl[m])<=2))
for lo,hi in ((1,1.5),(1.5,2),(2,3),(3,5),(5,50)):
    mm=(q>=lo)&(q<hi)
    if mm.sum(): print('   q %.1f-%.1f n=%3d median f_obs %.4f  f_ledger %.4f  ratio %.2f'%(lo,hi,mm.sum(),np.median(f[mm]),np.median(fl[mm]),np.median(f[mm])/np.median(fl[mm])))
def theil(x,y):
    s=[(y[j]-y[i])/(x[j]-x[i]) for i in range(len(x)) for j in range(i+1,len(x)) if abs(x[j]-x[i])>1e-9]
    return np.median(s)
def run(sel,label,B=400,seed=7):
    x=np.log(eta[sel]);y=np.log(f[sel]);s=theil(x,y)
    rng=np.random.default_rng(seed);bs=[]
    for _ in range(B):
        i=rng.integers(0,len(x),len(x)); bs.append(theil(x[i],y[i]))
    lo,hi=np.percentile(bs,[2.5,97.5])
    print(f'G-B {label}: n={sel.sum()} Theil-Sen slope s={s:.2f}  bootstrap 95% [{lo:.2f},{hi:.2f}]  ledger s=1 inside: {lo<=1<=hi}  NR-leading s=2 inside: {lo<=2<=hi}')
run(np.ones(len(f),bool),'all')
ok=np.isfinite(chi)&(np.abs(chi)<0.2); run(ok,'|chi_eff|<0.2')
print('Spearman(eta,f) all: %.3f'%__import__('scipy.stats',fromlist=['x']).spearmanr(eta,f)[0])
