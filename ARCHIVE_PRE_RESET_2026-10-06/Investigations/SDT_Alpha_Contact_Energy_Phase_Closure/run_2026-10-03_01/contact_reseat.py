"""Conditional clearance repair, selected by geometry only; no phase/energy selection."""
from pathlib import Path
import math,json
import numpy as np
from scipy.spatial import cKDTree
from scipy.optimize import minimize,brentq
RUN=Path(__file__).resolve().parent
d=json.loads((RUN/'FINITE_CURVES.json').read_text())
Rp=.8414;core=d['coreRadiusFm']/Rp
c=np.array([n['pos'] for n in d['modelNodes']])/Rp
major=5.28/(2*math.pi*Rp);minor=.06/(math.sqrt(2)*Rp)
def curve(u):
    rr=major+minor*np.cos(3*u)
    return np.array([rr*np.cos(4*u),rr*np.sin(4*u),minor*np.sin(3*u)])
def tangent(u):
    r=major+minor*np.cos(3*u);dr=-3*minor*np.sin(3*u)
    t=np.array([dr*np.cos(4*u)-4*r*np.sin(4*u),dr*np.sin(4*u)+4*r*np.cos(4*u),3*minor*np.cos(3*u)])
    return t/np.linalg.norm(t)
u=np.linspace(0,2*math.pi,3000,endpoint=False);shape=curve(u).T
def closest(a,b,scale):
    first=c[a]*scale+shape;second=c[b]*scale+shape
    dd,jj=cKDTree(second).query(first)
    seeds=np.argsort(dd)[:8];solutions=[]
    for i in seeds:
        obj=lambda uv:np.sum((scale*c[a]+curve(uv[0])-scale*c[b]-curve(uv[1]))**2)
        opt=minimize(obj,[u[i],u[jj[i]]],method='BFGS',options={'gtol':1e-12,'maxiter':150})
        solutions.append((math.sqrt(max(0,opt.fun)),opt.x))
    return min(solutions,key=lambda r:r[0])
root=brentq(lambda scale:closest(0,1,scale)[0]-2*core,1,1.2,xtol=1e-12)
rows=[]
for a,b in [(0,1),(1,2),(2,3),(0,3)]:
    distance,uv=closest(a,b,root);ta,tb=tangent(uv[0]),tangent(uv[1]);dot=float(ta@tb)
    rows.append({'a':a,'b':b,'gapRp':distance-2*core,'tangentDot':dot,'tangentError':1-abs(dot),'conditionalOpposedSpeciesSlip':float(np.linalg.norm(ta+tb)),'strandParameters':uv.tolist(),'gapPass':abs(distance-2*core)<=1e-8,'tangentPass':1-abs(dot)<=1e-8})
result={'scope':'uniform scale repairs core clearance in identity-oriented existing H1 shape; no energy/magnetic fitting; physical port definition and dynamical selection remain OPEN','centreScale':root,'edgeDistanceRp':2*root,'contacts':rows,'G1Pass':False}
(RUN/'CONTACT_RESEATING.json').write_text(json.dumps(result,indent=2))
print(json.dumps({'scale':root,'gaps':[r['gapRp'] for r in rows],'tangentErrors':[r['tangentError'] for r in rows],'slip':[r['conditionalOpposedSpeciesSlip'] for r in rows]}))
