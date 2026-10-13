"""Finite tube contact on preserved and volume-consistent source geometries."""
import json,math
import numpy as np
from scipy.optimize import brentq,minimize,root
from scipy.spatial import cKDTree
import analysis as a

SPECIES=['p','n','p','n']
EDGES=[(0,1),(1,2),(2,3),(3,0)]
PAIR_EDGES=list(__import__('itertools').combinations(range(4),2))
BASE_CENTRES=np.array([[math.sqrt(2)*a.RP,0,0],[0,math.sqrt(2)*a.RP,0],
                       [-math.sqrt(2)*a.RP,0,0],[0,-math.sqrt(2)*a.RP,0]])

def orientation(i,radial=True):
    phi=i*math.pi/2;co=math.cos(phi);si=math.sin(phi)
    Rz=np.array([[co,-si,0],[si,co,0],[0,0,1]])
    Ry=np.array([[0,0,1],[0,1,0],[-1,0,0]])
    return Rz@Ry if radial else np.eye(3)

def curve(u,R,h,phase=0):
    # Poloidal phase has an exact reparametrisation/rigid-rotation identity.
    phi=-4*phase/3;co=math.cos(phi);si=math.sin(phi)
    Rz=np.array([[co,-si,0],[si,co,0],[0,0,1]])
    return a.torus(np.asarray(u)+phase/3,R,h)@Rz.T

def derivative(u,R,h,phase=0,second=False):
    phi=-4*phase/3;co=math.cos(phi);si=math.sin(phi)
    Rz=np.array([[co,-si,0],[si,co,0],[0,0,1]])
    return (a.torus_dd(np.asarray(u)+phase/3,R,h) if second else a.torus_d(np.asarray(u)+phase/3,R,h))@Rz.T

def make_bodies(branch,radial=True,nphase=0):
    bodies=[]
    for i,k in enumerate(SPECIES):
        R,h,b=branch[k]
        bodies.append({'species':k,'R':R,'h':h,'b':b,'Q':orientation(i,radial),
                       'phase':0 if k=='p' else nphase})
    return bodies

def point(body,u):return curve(u,body['R'],body['h'],body['phase'])@body['Q'].T
def diff(body,u,second=False):return derivative(u,body['R'],body['h'],body['phase'],second)@body['Q'].T

def closest(bodies,i,j,scale,samples=1000):
    u=np.arange(samples)*a.TAU/samples
    xi=point(bodies[i],u)+BASE_CENTRES[i]*scale;xj=point(bodies[j],u)+BASE_CENTRES[j]*scale
    dd,ii=cKDTree(xj).query(xi)
    starts=np.argsort(dd)[:4]
    def objective(uv):
        return float(np.sum((point(bodies[i],uv[0])+BASE_CENTRES[i]*scale-point(bodies[j],uv[1])-BASE_CENTRES[j]*scale)**2))
    best=None
    for index in starts:
        uv0=[float(u[index]),float(u[ii[index]])]
        fit=minimize(objective,uv0,method='BFGS',options={'gtol':1e-10,'maxiter':150})
        if best is None or fit.fun<best.fun:best=fit
    ui,uj=best.x%a.TAU;pa=point(bodies[i],ui)+BASE_CENTRES[i]*scale;pb=point(bodies[j],uj)+BASE_CENTRES[j]*scale
    distance=float(np.linalg.norm(pb-pa));normal=(pb-pa)/max(distance,1e-30)
    da=diff(bodies[i],ui);db=diff(bodies[j],uj);ta=da/np.linalg.norm(da);tb=db/np.linalg.norm(db)
    bi=bodies[i]['b'];bj=bodies[j]['b'];surface_a=pa+bi*normal;surface_b=pb-bj*normal
    return {'a':i,'b':j,'u':float(ui),'v':float(uj),'centreline_distance_fm':distance,
            'gap_fm':distance-bi-bj,'normal':normal.tolist(),'tangent_a':ta.tolist(),'tangent_b':tb.tolist(),
            'strand_angle_degrees':math.degrees(math.acos(np.clip(float(ta@tb),-1,1))),
            'normal_dot_tangent_max':max(abs(float(normal@ta)),abs(float(normal@tb))),
            'surface_a_fm':surface_a.tolist(),'surface_b_fm':surface_b.tolist(),
            'optimizer_success':bool(best.success),'sampled_distance_fm':float(dd.min()),
            'physical_contact_test':'gap, opposite surface normals, local tubular Jacobian; parallel axes unnecessary'}

def rolling_matrix(bodies,contacts,scale):
    # Four bodies, three independent physical velocity channels each:
    # arclength flow, body-axis rigid spin, circular-section material spin.
    J=np.zeros((3*len(contacts),12))
    for e,row in enumerate(contacts):
        for body_index,key,sgn in [(row['a'],'u',1),(row['b'],'v',-1)]:
            body=bodies[body_index];u=row[key];normal=np.array(row['normal'])*(1 if sgn==1 else -1)
            d=diff(body,u);dd=diff(body,u,True);T=d/np.linalg.norm(d)
            kappa=(dd-T*np.dot(T,dd))/np.dot(d,d)
            point_centreline=point(body,u);surface=point_centreline+body['b']*normal
            axis=body['Q']@np.array([0,0,1])
            flow=(1-body['b']*float(kappa@normal))*T
            body_spin=np.cross(axis,surface)
            tube_spin=body['b']*np.cross(T,normal)
            J[3*e:3*e+3,3*body_index:3*body_index+3]=sgn*np.column_stack([flow,body_spin,tube_spin])
    U,S,Vh=np.linalg.svd(J,full_matrices=True)
    rank=int(np.sum(S>max(S[0],1)*1e-9));null=Vh[rank:]
    normal_rows=np.array([np.array(r['normal'])@J[3*i:3*i+3] for i,r in enumerate(contacts)])
    sn=np.linalg.svd(normal_rows,compute_uv=False)
    # Require a directed unit circulation in all four bodies; solve remaining rates.
    prescribed=np.array([1,-1,1,-1],float);flowcols=[0,3,6,9]
    othercols=[j for j in range(12) if j not in flowcols]
    rhs=-J[:,flowcols]@prescribed
    fitted=np.linalg.lstsq(J[:,othercols],rhs,rcond=1e-10)[0]
    residual=J[:,othercols]@fitted-rhs
    return {'units':'flow arbitrary fm/time; spin inverse time; no time scale derived',
            'unknowns':12,'constraint_rows':len(J),'rank':rank,'nullity':12-rank,'singular_values':S.tolist(),
            'normal_constraint_rank':int(np.sum(sn>max(sn[0],1)*1e-9)),
            'matrix':J.tolist(),'nullspace_basis':null.tolist(),
            'directed_unit_flow':[1,-1,1,-1], 'remaining_body_and_tube_spin_rates':fitted.tolist(),
            'directed_flow_surface_slip_norm':float(np.linalg.norm(residual)),
            'directed_flow_max_contact_slip':float(np.linalg.norm(residual.reshape(-1,3),axis=1).max()),
            'rate_solver_status':'kinematic compatibility control, not a fitted physical coefficient or restoring law'}

def main():
    volume=json.loads((a.RUN/'VOLUME_GEOMETRY.json').read_text())
    consistent={r['species']:(r['major_radius_fm'],r['minor_centreline_radius_fm'],r['equivalent_tube_radius_fm'])
                for r in volume['selfconsistent_T4_3_controls'] if r['mode']=='three_dimensional_self_contact'}
    widened={k:(a.R_H1,a.A_H1,a.equivalent_radius(V,a.length(a.R_H1,a.A_H1))) for k,V in a.VOLUMES.items()}
    branches={'old_H1':{k:(a.R_H1,a.A_H1,.03) for k in SPECIES},
              'volume_widened_without_lane_repair':widened,'volume_and_three_dimensional_lane_repair':consistent}
    baseline=[]
    for name,branch in branches.items():
        for radial in (False,True):
            bodies=make_bodies(branch,radial)
            pairs=[closest(bodies,i,j,1,1200) for i,j in PAIR_EDGES]
            baseline.append({'branch':name,'pose':'radial' if radial else 'identity','centre_scale':1,'pairs':pairs})
    reseated=[];phase_scan=[]
    for phase in np.arange(12)*a.TAU/12:
        bodies=make_bodies(consistent,True,float(phase))
        def contact_gap(scale):return closest(bodies,0,1,scale,600)['gap_fm']
        scales=np.linspace(.55,1.8,14);gaps=[contact_gap(s) for s in scales]
        brackets=[(scales[i],scales[i+1]) for i in range(len(scales)-1) if gaps[i]*gaps[i+1]<0]
        candidates=[]
        for lo,hi in brackets:
            scale=brentq(contact_gap,lo,hi,xtol=2e-9)
            pairs=[closest(bodies,i,j,scale,1600) for i,j in PAIR_EDGES]
            active=[r for r in pairs if (r['a'],r['b']) in [(0,1),(1,2),(2,3),(0,3)]]
            clearance=min(r['gap_fm'] for r in pairs if r not in active)
            maximum=max(abs(r['gap_fm']) for r in active)
            candidates.append({'phase':float(phase),'centre_scale':scale,'nonedge_minimum_gap_fm':clearance,
                               'active_edge_maximum_gap_residual_fm':maximum,'pairs':pairs,
                               'all_declared_contacts_close':maximum<1e-6,'nonedge_clearance':clearance>=-1e-8})
        phase_scan.append({'phase':float(phase),'roots':[{k:v for k,v in r.items() if k!='pairs'} for r in candidates]})
        valid=[r for r in candidates if r['all_declared_contacts_close'] and r['nonedge_clearance']]
        if valid:
            selected=min(valid,key=lambda r:abs(r['centre_scale']-1))
            selected['rolling_compatibility']=rolling_matrix(bodies,[r for r in selected['pairs'] if (r['a'],r['b']) in [(0,1),(1,2),(2,3),(0,3)]],selected['centre_scale'])
            selected['bodies']=[{k:(v.tolist() if isinstance(v,np.ndarray) else v) for k,v in b.items()} for b in bodies]
            reseated.append(selected)
    # C2 symmetry pairs opposite equal-species bodies. Two independent edge
    # gaps require two geometric coordinates: scale AND relative phase.
    joint=[]
    def two_edge_gaps(v,samples=900):
        bodies=make_bodies(consistent,True,float(v[1]))
        return np.array([closest(bodies,0,1,float(v[0]),samples)['gap_fm'],
                         closest(bodies,1,2,float(v[0]),samples)['gap_fm']])
    for phase in (0,math.pi/6,math.pi/3,math.pi/2):
        fit=root(two_edge_gaps,[1.28,phase],method='hybr',options={'xtol':1e-9,'maxfev':90})
        if not np.all(np.isfinite(fit.x)):continue
        scale=float(fit.x[0]);phase=float(fit.x[1]%(math.pi/2))
        if scale<=0 or scale>3:continue
        if any(abs(r['phase']-phase)<1e-5 and abs(r['centre_scale']-scale)<1e-5 for r in joint):continue
        bodies=make_bodies(consistent,True,phase)
        pairs=[closest(bodies,i,j,scale,2400) for i,j in PAIR_EDGES]
        active=[r for r in pairs if (r['a'],r['b']) in [(0,1),(1,2),(2,3),(0,3)]]
        nonedge=min(r['gap_fm'] for r in pairs if r not in active)
        residual=max(abs(r['gap_fm']) for r in active)
        candidate={'phase':phase,'centre_scale':scale,'joint_solver_success':bool(fit.success),
                   'active_edge_maximum_gap_residual_fm':residual,'nonedge_minimum_gap_fm':nonedge,
                   'all_declared_contacts_close':residual<1e-6,'nonedge_clearance':nonedge>=-1e-8,
                   'pairs':pairs,'rolling_compatibility':rolling_matrix(bodies,active,scale),
                   'bodies':[{k:(v.tolist() if isinstance(v,np.ndarray) else v) for k,v in b.items()} for b in bodies]}
        joint.append(candidate)
    # Jacobian phase identity: direct derivative check on the source torus family.
    u=.713;chi=.827;R=a.R_H1;h=consistent['p'][1];eps=1e-6
    phase_fd=(curve(u,R,h,chi+eps)-curve(u,R,h,chi-eps))/(2*eps)
    rhs=diff({'R':R,'h':h,'phase':chi,'Q':np.eye(3)},u)/3-4*np.cross([0,0,1],curve(u,R,h,chi))/3
    result={'status':'finite-volume source four-tour controls; operator double-trefoil embedding identification remains distinct',
            'prior_parallel_strand_gate_superseded':True,'baseline_controls':baseline,'phase_scan':phase_scan,
            'finite_contact_candidates':reseated,'joint_scale_phase_candidates':joint,
            'phase_rate_gauge':{'identity':'X_chi=X_u/3-(4/3)*(ez cross X)',
            'finite_difference_residual':float(np.linalg.norm(phase_fd-rhs)),
            'zero_velocity_parameter_direction':{'udot':-1/3,'chidot':1,'body_axis_spin':4/3},
            'independent_centreline_velocity_channels':2},
            'restoring_spectrum_status':'requires native force/torque derivative; kinematic nullspace is not stiffness'}
    a.save('ALPHA_FINITE_CONTACT.json',result)
    print(json.dumps({'phase_roots':len(reseated),'joint_scale_phase_roots':[{k:r[k] for k in ('phase','centre_scale','nonedge_minimum_gap_fm','active_edge_maximum_gap_residual_fm','all_declared_contacts_close')} for r in joint],
                      'directed_flow_slips':[r['rolling_compatibility']['directed_flow_surface_slip_norm'] for r in joint]},indent=2))

if __name__=='__main__':main()
