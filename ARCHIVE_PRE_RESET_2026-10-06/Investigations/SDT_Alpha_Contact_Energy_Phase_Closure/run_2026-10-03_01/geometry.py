from pathlib import Path
import json,math,csv,itertools
import numpy as np
from scipy.spatial import cKDTree
from scipy.optimize import minimize
RUN=Path(__file__).resolve().parent
data=json.loads((RUN/'FINITE_CURVES.json').read_text())
Rp=0.8414
nodes=data['modelNodes'];contacts=data['contacts'];centres=np.array([n['pos'] for n in nodes])/Rp
core=data['coreRadiusFm']/Rp
major=(5.28/(2*math.pi))/Rp;helix=(0.06/math.sqrt(2))/Rp
def curve(u):
    r=major+helix*np.cos(3*u)
    return np.array([r*np.cos(4*u),r*np.sin(4*u),helix*np.sin(3*u)])
def tangent(u):
    r=major+helix*math.cos(3*u);dr=-3*helix*math.sin(3*u)
    v=np.array([dr*math.cos(4*u)-4*r*math.sin(4*u),dr*math.sin(4*u)+4*r*math.cos(4*u),3*helix*math.cos(3*u)])
    return v/np.linalg.norm(v)
rows=[]
declared={tuple(sorted([e['a'],e['b']])) for e in contacts}
max_speed=4*major+7*helix
for surface in data['surfaces']:
    N=surface['samples'];curves=np.array(surface['curves'])/Rp
    for i,j in itertools.combinations(range(4),2):
        distances,indices=cKDTree(curves[j]).query(curves[i],workers=1)
        ii=int(np.argmin(distances));jj=int(indices[ii]);upper=float(distances[ii]);lower=max(0,upper-2*max_speed*math.pi/N)
        objective=lambda uv:np.sum((centres[i]+curve(uv[0])-centres[j]-curve(uv[1]))**2)
        opt=minimize(objective,[ii*2*math.pi/N,jj*2*math.pi/N],method='BFGS',options={'gtol':1e-12,'maxiter':200})
        d=math.sqrt(max(0,opt.fun));gap=d-2*core
        rows.append({'samples':N,'a':i,'b':j,'declaredContact':(i,j) in declared,'species':nodes[i]['type']+nodes[j]['type'],'centreDistanceRp':float(np.linalg.norm(centres[j]-centres[i])),'sampledMinDistanceRp':upper,'globalDistanceLowerBoundRp':lower,'refinedDistanceRp':d,'surfaceGapRp':gap,'globalGapLowerBoundRp':lower-2*core,'tangentDot':float(np.dot(tangent(opt.x[0]),tangent(opt.x[1]))),'u':float(opt.x[0]),'v':float(opt.x[1]),'activeContactPass':abs(gap)<=1e-8,'clearancePass':lower-2*core>=-1e-8,'finitePortLaw':'OPEN'})
# Exact centre-normal Jacobian in dimensionless 6-pose coordinates per body.
J=np.zeros((len(contacts),24))
for e,(edge,row) in enumerate(zip(contacts,J)):
    a,b=edge['a'],edge['b'];normal=(centres[b]-centres[a])/np.linalg.norm(centres[b]-centres[a]);row[6*a:6*a+3]=-normal;row[6*b:6*b+3]=normal
s=np.linalg.svd(J,compute_uv=False)
ranks={str(t):int(np.sum(s>s[0]*t)) for t in [1e-6,1e-8,1e-10]}
graphs=[]
edges=[(0,1),(0,3),(2,1),(2,3)]
for mask in range(1,16):
    selected=[e for k,e in enumerate(edges) if mask&(1<<k)];adj={i:set() for i in range(4)}
    for a,b in selected:adj[a].add(b);adj[b].add(a)
    seen={0};todo=[0]
    while todo:
        for j in adj[todo.pop()]-seen:seen.add(j);todo.append(j)
    if len(seen)==4:graphs.append({'edges':selected,'maximumDegree':max(map(len,adj.values())),'portCountPass':True,'finitePortPoseStatus':'OPEN'})
summary={'scope':data['scope'],'nativeCoreFraction':core,'nativeEnvelopeRp':major+helix+core,'contactRows':rows,'graphs':graphs,'conditionalCentreConstraints':{'coordinates':24,'normalRank':ranks,'singularValues':s.tolist(),'globalRigidGauges':6,'internalPoseNullity':24-6-ranks['1e-08'],'physicalPhaseTractionRank':'OPEN; centre-normal rank is not finite contact physics'}}
(RUN/'CONSTRAINT_SPECTRA.json').write_text(json.dumps(summary,indent=2))
with (RUN/'CONTACT_AUDIT.csv').open('w',newline='') as f:
    w=csv.DictWriter(f,fieldnames=rows[0]);w.writeheader();w.writerows(rows)
print(json.dumps({'activeDeclaredContactsPassed':sum(r['activeContactPass'] for r in rows if r['samples']==6000 and r['declaredContact']),'declaredContacts':len(contacts),'minimumRefinedGapRp':min(r['surfaceGapRp'] for r in rows),'normalRank':ranks,'connectedGraphs':len(graphs)}))
