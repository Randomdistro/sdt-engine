import json, numpy as np
R=json.load(open('np41_edge_coupling.json',encoding='utf-8'))
kinds=sorted({k for r in R for k in r['kinds']})
print('n',len(R),'kinds',kinds)
for k in kinds:
    n=sum(r['kinds'].get(k,{}).get('n',0) for r in R); s=sum(r['kinds'].get(k,{}).get('sum',0) for r in R); q=sum(r['kinds'].get(k,{}).get('sumsq',0) for r in R)
    m=s/n; sd=(q/n-m*m)**.5
    print(f'  {k:18s} edges {n:6d}  mean contactCoupling {m:.4f}  CV across edges {sd/m:.3f}  total share of coupling {100*s/sum(sum(v["sum"] for v in r["kinds"].values()) for r in R):.1f}%')
A=np.array([r['A'] for r in R],float);Bm=np.array([r['Bmeas'] for r in R])
tot=np.array([sum(v['sum'] for v in r['kinds'].values()) for r in R]);ne=np.array([sum(v['n'] for v in r['kinds'].values()) for r in R],float)
print('mean coupling per edge: median %.4f IQR %.4f-%.4f'%(np.median(tot/ne),*np.percentile(tot/ne,[25,75])))
for lo,hi in ((2,20),(20,60),(60,260)):
    m=(A>=lo)&(A<hi); print(f'  A {lo}-{hi}: mean coupling/edge {np.median((tot/ne)[m]):.4f}  edges per nucleon {np.median((ne/A)[m]):.3f}')
for k in kinds:
    sh=np.array([r['kinds'].get(k,{}).get('sum',0)/max(sum(v['sum'] for v in r['kinds'].values()),1e-12) for r in R])
    ratio=tot*1.7117/Bm
    c=np.corrcoef(sh,ratio)[0,1]; print(f'  share of {k:18s} median {np.median(sh):.3f}  corr with B_calc/B_meas {c:+.3f}')
