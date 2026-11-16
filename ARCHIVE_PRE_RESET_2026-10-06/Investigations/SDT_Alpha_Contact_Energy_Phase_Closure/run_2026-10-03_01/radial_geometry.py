from pathlib import Path
import json,math,itertools
import numpy as np
from scipy.spatial import cKDTree
from scipy.optimize import minimize,brentq
RUN=Path(__file__).resolve().parent
base=json.loads((RUN/'BASELINE.json').read_text());centres=np.array([n['pos'] for n in base['nodes']])/.8414
Ry=np.array([[0.,0.,1.],[0.,1.,0.],[-1.,0.,0.]])
rot=[]
for i in range(4):
    phi=i*math.pi/2;rot.append(np.array([[math.cos(phi),-math.sin(phi),0],[math.sin(phi),math.cos(phi),0],[0,0,1]])@Ry)
rows=[]
for name,R,h,k,phase,core in [('H1',5.28/(2*math.pi*.8414),.06/(math.sqrt(2)*.8414),3,0.,.03/.8414),('BRAID',.62,.22,5,math.pi,.16)]:
    def curve(u):
        rho=R+h*np.cos(k*u+phase)
        return np.array([rho*np.cos(4*u),rho*np.sin(4*u),h*np.sin(k*u+phase)])
    def tangent(u):
        rho=R+h*math.cos(k*u+phase);dr=-k*h*math.sin(k*u+phase)
        t=np.array([dr*math.cos(4*u)-4*rho*math.sin(4*u),dr*math.sin(4*u)+4*rho*math.cos(4*u),k*h*math.cos(k*u+phase)])
        return t/np.linalg.norm(t)
    u=np.linspace(0,2*math.pi,3000,endpoint=False);shape=curve(u).T
    def closest(a,b,scale):
        first=scale*centres[a]+shape@rot[a].T;second=scale*centres[b]+shape@rot[b].T
        d,j=cKDTree(second).query(first);solutions=[]
        for i in np.argsort(d)[:8]:
            obj=lambda uv:np.sum((scale*centres[a]+rot[a]@curve(uv[0])-scale*centres[b]-rot[b]@curve(uv[1]))**2)
            opt=minimize(obj,[u[i],u[j[i]]],method='BFGS',options={'gtol':1e-12,'maxiter':150})
            solutions.append((math.sqrt(max(0,opt.fun)),opt.x))
        return min(solutions,key=lambda r:r[0])
    fixed=closest(0,1,1.)
    # Search a bracket in the outward separation branch; no target energy enters.
    scales=np.linspace(.4,1.,31);values=[closest(0,1,s)[0]-2*core for s in scales]
    crossings=[(a,b) for a,b,fa,fb in zip(scales,scales[1:],values,values[1:]) if fa<=0 and fb>0]
    selected=brentq(lambda s:closest(0,1,s)[0]-2*core,*crossings[-1],xtol=1e-11) if crossings else None
    contactRows=[]
    if selected is not None:
        for e in base['contacts']:
            a,b=e['a'],e['b'];distance,uv=closest(a,b,selected);ta,tb=rot[a]@tangent(uv[0]),rot[b]@tangent(uv[1]);dot=float(ta@tb)
            contactRows.append({'a':a,'b':b,'gapRp':distance-2*core,'tangentDot':dot,'tangentError':1-abs(dot),'conditionalStrandSlip':float(np.linalg.norm(ta+tb))})
    rows.append({'model':name,'originalRadialGapRp':fixed[0]-2*core,'selectedCentreScale':selected,'contacts':contactRows,'physicalPortPhaseSelection':'OPEN'})
(RUN/'RADIAL_FINITE_GEOMETRY.json').write_text(json.dumps({'scope':'radial ring branch finite-core audit and geometry-only reseating; no magnetic or binding objective','rows':rows},indent=2))
print(json.dumps(rows))
