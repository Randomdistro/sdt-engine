from pathlib import Path
import json,math,csv
import numpy as np
from numpy.polynomial.legendre import leggauss
RUN=Path(__file__).resolve().parent
native=json.loads((RUN/'NATIVE_CONTROLS.json').read_text(encoding='utf-8-sig'))
unit=native['C_J_m']/native['R_p_lock_m']
charges=np.array([1.,1.,1.,1.,-1.,-1.])
def positions(q):
    a,delta=q;t=a/(2*math.sqrt(2))
    return np.array([[t,t,t],[t,-t,-t],[-t,t,-t],[-t,-t,t],[t,0,delta],[-t,0,-delta]])
def energy(q):
    r=positions(q);return sum(charges[i]*charges[j]/np.linalg.norm(r[i]-r[j]) for i in range(6) for j in range(i+1,6))
def gradient(q):
    r=positions(q);forcegrad=np.zeros_like(r)
    for i in range(6):
        for j in range(i+1,6):
            d=r[i]-r[j];g=-charges[i]*charges[j]*d/np.linalg.norm(d)**3
            forcegrad[i]+=g;forcegrad[j]-=g
    dpda=positions([1.,0.]);dpdd=positions([0.,1.])
    return np.array([np.sum(forcegrad*dpda),np.sum(forcegrad*dpdd)])
def work(vertices,N):
    x,w=leggauss(N);total=0
    for q0,q1 in zip(vertices,vertices[1:]):
        q0=np.array(q0);dq=np.array(q1)-q0
        total+=sum(wi*np.dot(gradient(q0+.5*(xi+1)*dq),dq)*.5 for xi,wi in zip(x,w))
    return total
start=[2.,0.];end=[6.,0.];paths={'radial':[start,end],'deformed':[start,[4.,.25],end],'closed_loop':[start,[4.,.25],end,[4.,-.25],start]}
rows=[]
for name,p in paths.items():
    exact=(energy(p[-1])-energy(p[0]))*unit
    for N in [16,32,64]:
        actual=work(p,N)*unit
        rows.append({'route':'NP17 point-seat mathematical control only','path':name,'N':N,'work_J':actual,'potential_difference_J':exact,'absolute_residual_J':abs(actual-exact),'constituent_scaled_residual':abs(actual-exact)/native['constituent_rest_energy_J'],'physicalAlphaPathStatus':'OPEN finite internal-electron geometry and work coupling'})
with (RUN/'PATH_WORK.csv').open('w',newline='') as f:
    w=csv.DictWriter(f,fieldnames=rows[0]);w.writeheader();w.writerows(rows)
(RUN/'PATH_WORK.json').write_text(json.dumps(rows,indent=2))
print(json.dumps({'worstConstituentScaledResidual':max(r['constituent_scaled_residual'] for r in rows),'unit_J':unit}))
