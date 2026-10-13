from pathlib import Path
import json,math,itertools
import numpy as np
from scipy.spatial import cKDTree
from scipy.optimize import minimize
RUN=Path(__file__).resolve().parent
base=json.loads((RUN/'BASELINE.json').read_text());centres=np.array([n['pos'] for n in base['nodes']])/.8414
def curve(u):
    psi=math.pi+5*u;rho=.62+.22*np.cos(psi)
    return np.array([rho*np.cos(4*u),rho*np.sin(4*u),.22*np.sin(psi)])
def tangent(u):
    psi=math.pi+5*u;rho=.62+.22*math.cos(psi);dr=-5*.22*math.sin(psi)
    v=np.array([dr*math.cos(4*u)-4*rho*math.sin(4*u),dr*math.sin(4*u)+4*rho*math.cos(4*u),5*.22*math.cos(psi)])
    return v/np.linalg.norm(v)
rows=[];edges={tuple(sorted([e['a'],e['b']])) for e in base['contacts']}
for N in [1500,3000,6000]:
    u=np.linspace(0,2*math.pi,N,endpoint=False);shape=curve(u).T
    for a,b in itertools.combinations(range(4),2):
        d,j=cKDTree(centres[b]+shape).query(centres[a]+shape)
        i=int(np.argmin(d));obj=lambda uv:np.sum((centres[a]+curve(uv[0])-centres[b]-curve(uv[1]))**2)
        opt=minimize(obj,[u[i],u[j[i]]],method='BFGS',options={'gtol':1e-12,'maxiter':200})
        distance=math.sqrt(max(0,opt.fun));bound=max(0,float(d[i])-2*(4*.62+10*.22)*math.pi/N)-.32
        rows.append({'samples':N,'a':a,'b':b,'declaredContact':(a,b) in edges,'refinedGapRp':distance-.32,'globalGapLowerBoundRp':bound,'tangentDot':float(tangent(opt.x[0])@tangent(opt.x[1])),'contactPass':abs(distance-.32)<=1e-8})
result={'scope':'native NSEQ16 (4,5) braid at identity orientations; independent of H1 (4,3) form; tubular width is a conditional Euclidean core interpretation','majorRp':.62,'minorRp':.22,'coreRp':.16,'envelopeRp':1.,'rows':rows,'sameSectionAdjacentLaneGapRp':math.sqrt(2)*.22-2*.16,'physicalPortPhaseLaw':'OPEN'}
(RUN/'BRAID_GEOMETRY.json').write_text(json.dumps(result,indent=2))
print(json.dumps({'finestContacts':[r for r in rows if r['samples']==6000 and r['declaredContact']],'sameSectionGap':result['sameSectionAdjacentLaneGapRp']}))
