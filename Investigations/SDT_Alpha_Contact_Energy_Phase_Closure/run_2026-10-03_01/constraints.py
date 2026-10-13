from pathlib import Path
import json,math
import numpy as np
RUN=Path(__file__).resolve().parent
base=json.loads((RUN/'BASELINE.json').read_text());x=np.array([n['pos'] for n in base['nodes']])/.8414
def skew(v):
    a,b,c=v;return np.array([[0,-c,b],[c,0,-a],[-b,a,0]])
N=[];T=[];C=[]
for e in base['contacts']:
    a,b=e['a'],e['b'];n=(x[b]-x[a])/2
    J=np.zeros((3,24));J[:,6*a:6*a+3]=np.eye(3);J[:,6*b:6*b+3]=-np.eye(3)
    J[:,6*a+3:6*a+6]=-skew(n);J[:,6*b+3:6*b+6]=-skew(n)
    C.append(J);N.append(n@J);T.append((np.eye(3)-np.outer(n,n))@J)
C=np.vstack(C);N=np.vstack(N);T=np.vstack(T)
gauge=np.zeros((24,6))
for i in range(4):
    gauge[6*i:6*i+3,:3]=np.eye(3);gauge[6*i:6*i+3,3:]=-skew(x[i]);gauge[6*i+3:6*i+6,3:]=np.eye(3)
def audit(J):
    s=np.linalg.svd(J,compute_uv=False);r={str(t):int(np.sum(s>s[0]*t)) for t in [1e-6,1e-8,1e-10]}
    return {'singularValues':s.tolist(),'rankThresholds':r,'gaugeResidual':float(np.max(np.abs(J@gauge))),'conditionalInternalNullity':24-6-r['1e-08']}
result={'scope':'conditional instantaneous rigid spherical contact velocity; a graph/contact-slip model does not supply phase or native energy constraints','normal':audit(N),'tangentialNoSlip':audit(T),'combinedNoSlip':audit(C),'phaseOrientation':'OPEN physical contact law','coordinates':24,'globalGauges':6}
(RUN/'RIGID_CONTACT_JACOBIANS.json').write_text(json.dumps(result,indent=2))
print(json.dumps({k:r['rankThresholds'] for k,r in result.items() if isinstance(r,dict)}))
