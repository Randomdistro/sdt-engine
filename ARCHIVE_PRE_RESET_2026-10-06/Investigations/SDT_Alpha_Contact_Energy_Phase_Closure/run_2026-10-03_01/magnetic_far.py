from pathlib import Path
import json
import numpy as np
RUN=Path(__file__).resolve().parent
s=json.loads((RUN/'MAGNETIC_SEGMENTS.json').read_text())
a=np.array([e['a'] for e in s]);b=np.array([e['b'] for e in s]);mid=(a+b)/2;dl=b-a;weights=np.array([e['weight'] for e in s])
moment=.5*np.sum(np.cross(mid,dl)*weights[:,None],axis=0)
extent=max(np.linalg.norm(a,axis=1).max(),np.linalg.norm(b,axis=1).max())
def field(point):
    r=point-mid
    return np.sum(np.cross(dl,r)*weights[:,None]/(np.sum(r*r,axis=1)[:,None]**1.5),axis=0)
rows=[]
for R in [80*max(1,extent),160*max(1,extent),320*max(1,extent)]:
    design=[];rhs=[]
    for n in np.vstack([np.eye(3),-np.eye(3)]):
        design.append(3*np.outer(n,n)-np.eye(3));rhs.append(R**3*field(R*n))
    extracted=np.linalg.lstsq(np.vstack(design),np.concatenate(rhs),rcond=None)[0]
    rows.append({'radius':R,'momentVectorMuN':extracted.tolist(),'absoluteVectorErrorMuN':float(np.linalg.norm(extracted-moment))})
coefs=np.array([[1,1/r['radius'],1/r['radius']**2] for r in rows]);values=np.array([r['momentVectorMuN'] for r in rows]);extrapolated=np.linalg.solve(coefs,values)[0]
result={'scope':'independent full-vector far-response of calibrated midpoint segment proxy; no native magnetic observable derivation','directVectorMuN':moment.tolist(),'finiteRadiusRows':rows,'extrapolatedVectorMuN':extrapolated.tolist(),'extrapolatedAbsoluteErrorMuN':float(np.linalg.norm(extrapolated-moment)),'zeroVectorPass':float(np.linalg.norm(moment))<=1e-6}
(RUN/'MAGNETIC_FAR_RESPONSE.json').write_text(json.dumps(result,indent=2))
print(json.dumps(result))
