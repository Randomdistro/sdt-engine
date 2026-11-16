"""Three-knit geometry, crossed-tube rolling and director closure controls."""
import math
import numpy as np
from scipy.optimize import brentq, minimize_scalar
from scipy.integrate import quad
import analysis as a

def symmetric_contact(R,h):
    def d2(delta):
        return 4*((R+h*math.cos(1.5*delta))**2*math.sin(2*delta)**2
                  +h*h*math.sin(1.5*delta)**2)
    fit=minimize_scalar(d2,bounds=(math.pi/2,math.pi/2+.35),method='bounded',options={'xatol':1e-14})
    delta=fit.x
    return float(delta),math.sqrt(fit.fun)

def rotate(v,axis,theta):
    co=math.cos(theta);si=math.sin(theta)
    return v*co+np.cross(axis,v)*si+axis*np.dot(axis,v)*(1-co)

def holonomy(R,h,samples=2048):
    u=np.linspace(0,a.TAU,samples+1)
    tangents=a.torus_d(u,R,h);tangents/=np.linalg.norm(tangents,axis=1)[:,None]
    normal=np.cross(tangents[0],[0,0,1]);normal/=np.linalg.norm(normal);initial=normal.copy()
    for prev,current in zip(tangents[:-1],tangents[1:]):
        axis=np.cross(prev,current);mag=np.linalg.norm(axis)
        if mag>1e-14:normal=rotate(normal,axis/mag,math.atan2(mag,np.dot(prev,current)))
        normal-=current*np.dot(normal,current);normal/=np.linalg.norm(normal)
    correction=math.atan2(np.dot(tangents[0],np.cross(normal,initial)),np.dot(normal,initial))
    return correction

def torsion_holonomy(R,h):
    """Independent smooth-Frenet integral, valid away from zero curvature."""
    def integrand(u):
        p,q=4,3;r=R+h*math.cos(q*u);dr=-q*h*math.sin(q*u)
        ddr=-q*q*h*math.cos(q*u);dddr=q**3*h*math.sin(q*u)
        third=np.array([(dddr-3*p*p*dr)*math.cos(p*u)+(p**3*r-3*p*ddr)*math.sin(p*u),
                        (dddr-3*p*p*dr)*math.sin(p*u)+(3*p*ddr-p**3*r)*math.cos(p*u),
                        -q**3*h*math.cos(q*u)])
        d=a.torus_d(u,R,h);dd=a.torus_dd(u,R,h);cross=np.cross(d,dd)
        return float(np.dot(cross,third)/np.dot(cross,cross)*np.linalg.norm(d))
    total,error=quad(integrand,0,a.TAU,epsabs=2e-11,epsrel=2e-12,limit=200)
    correction=math.atan2(math.sin(total),math.cos(total))
    return correction,total,error

def knit(R,h,b):
    delta,D=symmetric_contact(R,h);rows=[]
    for k in range(3):
        u=-delta/2+k*a.TAU/3;v=delta/2+k*a.TAU/3
        x=a.torus(u,R,h);y=a.torus(v,R,h);n=(y-x)/np.linalg.norm(y-x)
        da=a.torus_d(u,R,h);db=a.torus_d(v,R,h);ta=da/np.linalg.norm(da);tb=db/np.linalg.norm(db)
        dda=a.torus_dd(u,R,h);ddb=a.torus_dd(v,R,h)
        ka=(dda-ta*np.dot(ta,dda))/np.dot(da,da);kb=(ddb-tb*np.dot(tb,ddb))/np.dot(db,db)
        ja=1-b*np.dot(ka,n);jb=1+b*np.dot(kb,n)
        flow=ja*ta-jb*tb;roll=b*np.cross(ta+tb,n)
        rate=-float(np.dot(flow,roll)/np.dot(roll,roll))
        rows.append({'knit':k+1,'u':u%a.TAU,'v':v%a.TAU,'centreline_a_fm':x.tolist(),'centreline_b_fm':y.tolist(),
                     'surface_point_fm':((x+y)/2).tolist(),'normal':n.tolist(),'tangent_a':ta.tolist(),'tangent_b':tb.tolist(),
                     'gap_fm':D-2*b,'strand_angle_degrees':math.degrees(math.acos(np.clip(np.dot(ta,tb),-1,1))),
                     'normal_dot_tangent_max':max(abs(float(n@ta)),abs(float(n@tb))),
                     'surface_flow_jacobians':[float(ja),float(jb)],'rolling_spin_per_flow_inverse_fm':rate,
                     'perfect_rolling_velocity_residual_per_unit_flow':float(np.linalg.norm(flow+rate*roll)),
                     'parameter_speed_norm_fm':float(np.linalg.norm(da))})
    return rows

def dimensionless_roll(alpha,samples=512):
    delta,D=symmetric_contact(1,alpha);b=D/2
    row=knit(1,alpha,b)[0]
    corr=holonomy(1,alpha,samples)
    # Director angle = correction*u/TAU + q_roll*u; local spin/flow includes |X_u|.
    required=row['rolling_spin_per_flow_inverse_fm']*row['parameter_speed_norm_fm']-corr/a.TAU
    return required,corr,row

def main():
    data=__import__('json').loads((a.RUN/'VOLUME_GEOMETRY.json').read_text())
    controls=[]
    for r in data['selfconsistent_T4_3_controls']:
        if r['mode']!='three_dimensional_self_contact':continue
        R=r['major_radius_fm'];h=r['minor_centreline_radius_fm'];b=r['equivalent_tube_radius_fm']
        rows=knit(R,h,b);corrections=[{'samples':n,'closure_correction_radians':holonomy(R,h,n)} for n in (512,1024,2048)]
        corr,total,error=torsion_holonomy(R,h);local=rows[0]
        required=local['rolling_spin_per_flow_inverse_fm']*local['parameter_speed_norm_fm']-corr/a.TAU
        trials=[]
        for qroll in (-4,-3,3,4):
            prescribed=(qroll+corr/a.TAU)/local['parameter_speed_norm_fm']
            # Residual scales linearly with roll-rate departure, using actual vectors.
            t1=np.array(local['tangent_a']);t2=np.array(local['tangent_b']);n=np.array(local['normal'])
            spin_column=b*np.cross(t1+t2,n)
            trials.append({'director_roll_turns':qroll,'spin_per_flow_inverse_fm':prescribed,
                           'surface_slip_per_unit_flow':float(np.linalg.norm(spin_column*(prescribed-local['rolling_spin_per_flow_inverse_fm'])))})
        controls.append({'species':r['species'],'knits':rows,'holonomy_refinement':corrections,
                         'independent_torsion_holonomy_radians':corr,'torsion_integral_radians':total,
                         'torsion_quadrature_error':error,
                         'required_signed_director_roll_turns_uniform_parameter':required,
                         'required_signed_roll_turns_uniform_arclength':local['rolling_spin_per_flow_inverse_fm']*r['length_fm']/a.TAU,
                         'prescribed_roll_controls':trials})
    # Geometric inverse: fixed four director rolls + three first-contact knits + conserved volume.
    # Root selection is imposed geometry, not fitting a nuclear observable.
    grid=np.linspace(.035,.80,23);scan=[]
    for alpha in grid:
        q,corr,row=dimensionless_roll(float(alpha),512)
        scan.append({'alpha':float(alpha),'required_signed_roll':q,'closure_correction':corr})
    roots=[]
    for left,right in zip(scan[:-1],scan[1:]):
        if (left['required_signed_roll']+4)*(right['required_signed_roll']+4)>=0:continue
        if abs(left['closure_correction']-right['closure_correction'])>math.pi:continue
        def exact_four_roll(alpha):
            delta,D=symmetric_contact(1,alpha);row=knit(1,alpha,D/2)[0]
            corr,_,_=torsion_holonomy(1,alpha)
            return row['rolling_spin_per_flow_inverse_fm']*row['parameter_speed_norm_fm']-corr/a.TAU+4
        root=brentq(exact_four_roll,left['alpha'],right['alpha'],xtol=2e-12)
        corr,total,error=torsion_holonomy(1,root)
        delta,D=symmetric_contact(1,root);row=knit(1,root,D/2)[0]
        q=row['rolling_spin_per_flow_inverse_fm']*row['parameter_speed_norm_fm']-corr/a.TAU
        delta,D=symmetric_contact(1,root);beta=D/2;Lunit=a.length(1,root)
        species=[]
        for name,V in a.VOLUMES.items():
            R=(V/(math.pi*beta**2*Lunit))**(1/3);h=root*R;b=beta*R
            rho=a.curvature_radius(R,h)
            species.append({'species':name,'major_radius_fm':R,'minor_centreline_radius_fm':h,'tube_radius_fm':b,
                            'length_fm':Lunit*R,'major_radius_ratio_to_Rp_input':R/a.RP,
                            'volume_relative_residual':abs(math.pi*b*b*Lunit*R/V-1),
                            'local_jacobian_positive':b<rho['minimum_radius_fm'],
                            'knits':knit(R,h,b)})
        roots.append({'aspect_a_over_R':root,'required_signed_roll_exact_torsion_quadrature':q,
                      'holonomy_refinement':[{'samples':n,'closure_correction_radians':holonomy(1,root,n)} for n in (1024,2048,4096)],
                      'closure_correction_radians':corr,'inverse_scale_geometry':species,
                      'status':'conditional source T(4,3) geometry; director roll does not establish physical poloidal travel'})
    result={'status':'executed crossed-tube rolling and conditional inverse geometry',
            'parallel_strand_tangents_required':False,
            'surface_velocity_formula':'v_surface = f*(1-b*kappa dot n)*T + omega*b*(T cross n)',
            'four_roll_convention':'relative periodic transported director; physical centreline traversal remains separately audited',
            'three_knit_controls':controls,'dimensionless_scan':scan,'four_roll_inverse_roots':roots}
    a.save('THREE_KNIT_PHASE.json',result)
    print(__import__('json').dumps({'controls':[(r['species'],r['required_signed_director_roll_turns_uniform_parameter']) for r in controls],
                                  'four_roll_roots':[(r['aspect_a_over_R'],[(s['species'],s['major_radius_fm']) for s in r['inverse_scale_geometry']]) for r in roots]},indent=2))

if __name__=='__main__':main()
