"""Executed shape-native investigation. Witnesses and source controls stay explicit."""
from pathlib import Path
import csv, hashlib, itertools, json, math, subprocess, time
import numpy as np
from scipy.integrate import quad
from scipy.optimize import brentq, minimize, minimize_scalar
from scipy.spatial import cKDTree

RUN = Path(__file__).resolve().parent
ROOT = RUN.parents[2]
OTHER = Path('C:/Users/Jimmi/Spatial_Displacement_Theory')
TAU = 2*math.pi
C = 299792458.
RP = .8414  # fm; centreline radius control, not a hard outer boundary
R_H1 = 5.28/TAU
A_H1 = .06/math.sqrt(2)
DE = 6e-5  # fm: diameter of the native OPEN 3e-20 m radius
A0 = 5.29177210903e4  # fm
LE = 4*math.pi*A0
MULTIPLIERS = {'p':1836,'n':1387}
VOLUMES = {k:math.pi*DE**2*LE*N/4 for k,N in MULTIPLIERS.items()}

def save(name,data):
    (RUN/name).write_text(json.dumps(data,indent=2,allow_nan=False)+'\n',encoding='utf-8')

def emit(message):
    print(message,flush=True)

SOURCES = [
    ROOT/'Engine/include/sdt/laws.hpp',
    ROOT/'Release/HTML_SDT_Website/js/traction-gear-engine.js',
    ROOT/'Release/HTML_SDT_Website/js/nuclear-inputs.js',
    ROOT/'Investigations/05_Nuclear_Physics/NSEQ16_Perfect_Traction_Gear_Engine/PROMPT.md',
    ROOT/'Investigations/05_Nuclear_Physics/NSEQ17_Light_Nucleus_Wake_Mesh/PROMPT.md',
    ROOT/'Investigations/05_Nuclear_Physics/NSEQ18_Universal_Interstitial_Sequencer/PROMPT.md',
    ROOT/'Investigations/05_Nuclear_Physics/NP06_Gear_Frequency_Binding_Functional/PROMPT.md',
    ROOT/'Investigations/SDT_Alpha_Contact_Energy_Phase_Closure/run_2026-10-03_01/VERDICT.md',
    ROOT/'Investigations/SDT_Alpha_Contact_Energy_Phase_Closure/run_2026-10-03_01/BASELINE.json',
    OTHER/'SDT/Code/trefoil_proton_engine.cpp',
    OTHER/'SDT/Code/generate_trefoil_mappings.py',
    OTHER/'SDT/Code/calculate_contraction.py',
    OTHER/'SDT/Code/calculate_precise_contraction.py',
    OTHER/'SDT/data/trefoil_mappings.json',
    OTHER/'SDT/SDT_CANONICAL_PHYSICS_ENGINE_v4.md',
    OTHER/'SDT/website/src/components/atomicus/TrefoilNuclearVisualizer.tsx',
    OTHER/'SDT/website/src/components/atomicus/TrefoilVelocityVectors.tsx',
    OTHER/'SDT/website/src/components/atomicus/TrefoilRotationMechanism.tsx',
    OTHER/'SDT/investigations/nuclear_structure_probe/6PI_TREFOIL_INTERLEAVED_SPEC.md',
    OTHER/'SDT/investigations/nuclear_structure_probe/ELECTRON_SHARING_MODEL.md',
    OTHER/'ex_parte/06_nuclear_physics_foundation.md',
    OTHER/'ex_parte/07_multi_ai_nuclear_calculator.md',
]

def freeze_sources():
    rows=[]
    for p in SOURCES:
        if p.exists():
            content=p.read_bytes()
            rows.append({'path':str(p),'bytes':len(content),'sha256':hashlib.sha256(content).hexdigest()})
        else:
            rows.append({'path':str(p),'status':'MISSING'})
    heads={str(p):subprocess.check_output(['git','-C',str(p),'rev-parse','HEAD'],text=True).strip()
           for p in (ROOT,OTHER)}
    dirty={str(p):subprocess.check_output(['git','-C',str(p),'status','--short'],text=True)
           for p in (ROOT,OTHER)}
    receipt={'sources':rows,'heads':heads,'working_trees_before':dirty,
             'canonical_source_mutations_authorized':False,'new_artifact_directory':str(RUN)}
    save('SOURCE_FREEZE.json',receipt)
    return receipt

def torus(u,R,a,p=4,q=3,flatten=1.):
    u=np.asarray(u)
    r=R+a*np.cos(q*u)
    return np.stack((r*np.cos(p*u),r*np.sin(p*u),flatten*a*np.sin(q*u)),axis=-1)

def torus_d(u,R,a,p=4,q=3,flatten=1.):
    u=np.asarray(u);theta=p*u;r=R+a*np.cos(q*u);dr=-q*a*np.sin(q*u)
    return np.stack((dr*np.cos(theta)-p*r*np.sin(theta),
                     dr*np.sin(theta)+p*r*np.cos(theta),
                     flatten*q*a*np.cos(q*u)),axis=-1)

def torus_dd(u,R,a,p=4,q=3,flatten=1.):
    u=np.asarray(u);theta=p*u;r=R+a*np.cos(q*u);dr=-q*a*np.sin(q*u);ddr=-q*q*a*np.cos(q*u)
    return np.stack(((ddr-p*p*r)*np.cos(theta)-2*p*dr*np.sin(theta),
                     (ddr-p*p*r)*np.sin(theta)+2*p*dr*np.cos(theta),
                     -flatten*q*q*a*np.sin(q*u)),axis=-1)

def length(R,a,p=4,q=3,flatten=1.):
    return quad(lambda u:float(np.linalg.norm(torus_d(u,R,a,p,q,flatten))),0,TAU,
                epsabs=1e-10,epsrel=2e-12,limit=200)[0]

def equivalent_radius(V,L):
    return math.sqrt(V/(math.pi*L))

def nonlocal_distance(R,a,p=4,q=3):
    """Multistart restricted nonlocal minimum; derivative residuals are recorded."""
    def objective(v):
        return float(np.sum((torus(v[0],R,a,p,q)-torus(v[0]+v[1],R,a,p,q))**2))
    candidates=[]
    for u in np.linspace(0,TAU,7,endpoint=False):
        for delta in (TAU/p,2*TAU/p):
            fit=minimize(objective,[u,delta],method='L-BFGS-B',
                         bounds=[(-TAU,2*TAU),(math.pi/p,TAU-math.pi/p)],
                         options={'ftol':1e-15,'gtol':1e-10,'maxiter':150})
            x,y=fit.x[0],fit.x[0]+fit.x[1]
            sep=torus(y,R,a,p,q)-torus(x,R,a,p,q)
            ti=torus_d(x,R,a,p,q);tj=torus_d(y,R,a,p,q)
            d=math.sqrt(max(0,fit.fun))
            res=max(abs(float(sep@ti))/max(d*np.linalg.norm(ti),1e-30),
                    abs(float(sep@tj))/max(d*np.linalg.norm(tj),1e-30))
            candidates.append({'distance_fm':d,'u':float(x%TAU),'v':float(y%TAU),
                               'stationarity_residual':res,'optimizer_success':bool(fit.success),
                               'restricted_delta':float(fit.x[1])})
    return min(candidates,key=lambda r:r['distance_fm'])

def curvature_radius(R,a,p=4,q=3):
    def rho(u):
        d=torus_d(u,R,a,p,q);dd=torus_dd(u,R,a,p,q)
        return float(np.linalg.norm(d)**3/max(np.linalg.norm(np.cross(d,dd)),1e-30))
    grid=np.linspace(0,TAU,2048,endpoint=False)
    vals=np.array([rho(u) for u in grid])
    k=int(vals.argmin());fit=minimize_scalar(rho,bounds=(grid[k]-TAU/2048,grid[k]+TAU/2048),method='bounded',options={'xatol':1e-13})
    return {'minimum_radius_fm':float(fit.fun),'u':float(fit.x%TAU),'samples':2048}

def crossing_receipt():
    rows=[];deformations=[]
    for eta in (0,.25,.5,.75,1.):
        # A geometric flattening witness; no invented contraction force or clock.
        a=RP*math.sqrt(2/3)*(1-.5*eta);flat=1-.5*eta
        points=torus(np.array([math.pi/6+j*math.pi/3 for j in range(6)]),RP,a,2,3,flat)
        mids=torus(np.array([math.pi/3+j*math.pi/3 for j in range(6)]),RP,a,2,3,flat)
        radii=np.linalg.norm(mids[:,:2],axis=1)
        row={'eta':eta,'major_radius_fm':RP,'minor_centreline_radius_fm':a,
             'height_flattening':flat,'length_fm':length(RP,a,2,3,flat),
             'closure_position_residual_fm':float(np.linalg.norm(torus(0,RP,a,2,3,flat)-torus(TAU,RP,a,2,3,flat))),
             'closure_tangent_residual':float(np.linalg.norm(torus_d(0,RP,a,2,3,flat)-torus_d(TAU,RP,a,2,3,flat))),
             'projected_pair_residuals_fm':[float(np.linalg.norm(points[j,:2]-points[j+3,:2])) for j in range(3)],
             'crossing_height_separations_fm':[float(abs(points[j,2]-points[j+3,2])) for j in range(3)],
             'later_minus_first_loop_radial_midpoints_fm':[float(radii[j+3]-radii[j]) for j in range(3)],
             'hole_radius_fm':RP-a,
             'uniform_diameters_fm':{k:2*equivalent_radius(V,row_L) for k,V in VOLUMES.items()
                                    for row_L in [length(RP,a,2,3,flat)]}}
        deformations.append(row)
        if eta==0:
            for j in range(6):
                rows.append({'encounter':j+1,'crossing':j%3+1,'over_under':'over' if j%2==0 else 'under',
                             'u':math.pi/6+j*math.pi/3,'position_fm':points[j].tolist(),
                             'later_loop_relation':('outside' if j in (3,5) else 'inside') if j>=3 else None})
    result={'status':'minimal_three-crossing witness reproduces encounter receipt; double-trefoil interpretation not silently selected',
            'gauss_receipt':['O1','U2','O3','U1','O2','U3'],
            'operator_four_tour_geometry_identity_status':'requires material/embedding bridge; witness is not final physical shape',
            'encounters':rows,'geometric_deformations':deformations}
    save('CROSSING_RECEIPT.json',result)
    return result

# Exact polynomial arithmetic for Alexander controls; no symbolic dependency.
def padd(a,b):
    r=dict(a)
    for k,v in b.items():r[k]=r.get(k,0)+v
    return {k:v for k,v in r.items() if v}
def pneg(a):return {k:-v for k,v in a.items()}
def pmul(a,b):
    r={}
    for i,x in a.items():
        for j,y in b.items():r[i+j]=r.get(i+j,0)+x*y
    return {k:v for k,v in r.items() if v}
def mprod(A,B):
    return [[sum_polys(pmul(A[i][k],B[k][j]) for k in range(len(A))) for j in range(len(A))] for i in range(len(A))]
def sum_polys(items):
    r={}
    for p in items:r=padd(r,p)
    return r
def det_poly(A):
    total={};n=len(A)
    for perm in itertools.permutations(range(n)):
        sign=(-1)**sum(perm[i]>perm[j] for i in range(n) for j in range(i+1,n));term={0:sign}
        for i,j in enumerate(perm):term=pmul(term,A[i][j])
        total=padd(total,term)
    return total
def divide_poly(a,b):
    r=dict(a);q={}
    while r and max(r)>=max(b):
        power=max(r)-max(b);coeff=r[max(r)]//b[max(b)]
        if not coeff or coeff*b[max(b)]!=r[max(r)]:raise ValueError('non-exact polynomial division')
        q[power]=q.get(power,0)+coeff
        r=padd(r,{i+power:-coeff*v for i,v in b.items()})
    if r:raise ValueError('nonzero Alexander division remainder')
    return q
def alexander(n,word):
    I=[[{0:int(i==j)} if i==j else {} for j in range(n-1)] for i in range(n-1)]
    product=I
    for generator in word:
        B=[[{0:1} if i==j else {} for j in range(n)] for i in range(n)]
        i=generator-1
        B[i][i]={0:1,1:-1};B[i][i+1]={1:1};B[i+1][i]={0:1};B[i+1][i+1]={}
        reduced=[[padd(B[i][j],pneg(B[n-1][j])) for j in range(n-1)] for i in range(n-1)]
        product=mprod(product,reduced)
    determinant=det_poly([[padd(I[i][j],pneg(product[i][j])) for j in range(n-1)] for i in range(n-1)])
    quotient=divide_poly(determinant,{i:1 for i in range(n)})
    low=min(quotient);quotient={i-low:v for i,v in quotient.items()}
    if quotient[0]<0:quotient=pneg(quotient)
    slots=list(range(n))
    for g in word:slots[g-1],slots[g]=slots[g],slots[g-1]
    final=[slots.index(j) for j in range(n)]
    seen=set();cycles=[]
    for i in range(n):
        if i in seen:continue
        cycle=[];j=i
        while j not in seen:seen.add(j);cycle.append(j);j=final[j]
        cycles.append(cycle)
    return {'strands':n,'word':word,'alexander_coefficients':quotient,
            'alexander_span':max(quotient),'determinant_abs_at_minus_one':abs(sum(v*(-1)**i for i,v in quotient.items())),
            'final_slot_permutation':final,'closure_cycles':cycles,'components':len(cycles)}

def topology_controls():
    words={'trefoil_2_strand':(2,[1]*3),'four_strand_stabilized_trefoil':(4,[1,1,1,2,3]),
           'H1_T4_3':(4,[1,2,3]*3),'braid_T4_5':(4,[1,2,3]*5),
           'four_strand_trefoil_plus_one_full_cross_section_twist':(4,[1,2,3]*4+[1,1,1,2,3])}
    result={name:alexander(n,w) for name,(n,w) in words.items()}
    assert result['trefoil_2_strand']['alexander_coefficients']==result['four_strand_stabilized_trefoil']['alexander_coefficients']
    save('TOPOLOGY_CONTROLS.json',result)
    return result

class FourBraid:
    """Geometric four-tour trefoil witness, not an inferred SDT force solution."""
    word=[1,1,1,2,3]
    tours=[0,3,2,1]
    period=4*TAU
    def __init__(self,R=RP,spacing=.32):self.R=R;self.spacing=spacing
    def cross_section(self,theta):
        theta=np.atleast_1d(theta);N=len(theta)
        w=np.empty((4,N),complex);dw=np.zeros((4,N),complex);ddw=np.zeros((4,N),complex)
        starts=np.array([-1.5,-.5,.5,1.5],complex)*self.spacing;slots=list(range(4));dt=TAU/len(self.word)
        for k,g in enumerate(self.word):
            mask=(theta>=k*dt)&(theta<(k+1)*dt if k<4 else theta<=TAU)
            t=(theta[mask]-k*dt)/dt
            h=10*t**3-15*t**4+6*t**5;hp=(30*t**2-60*t**3+30*t**4)/dt
            hpp=(60*t-180*t**2+120*t**3)/dt**2
            w[:,mask]=starts[:,None]
            left,right=slots[g-1],slots[g];mid=(starts[left]+starts[right])/2
            for label in (left,right):
                delta=starts[label]-mid;rot=delta*np.exp(1j*math.pi*h)
                w[label,mask]=mid+rot;dw[label,mask]=rot*(1j*math.pi*hp)
                ddw[label,mask]=rot*(1j*math.pi*hpp-(math.pi*hp)**2)
            starts[left],starts[right]=starts[right],starts[left];slots[g-1],slots[g]=slots[g],slots[g-1]
        return w,dw,ddw
    def values(self,u,chi=0):
        scalar=np.ndim(u)==0;u=np.atleast_1d(u)%self.period
        tour=np.floor(u/TAU).astype(int);theta=u%TAU
        w,dw,ddw=self.cross_section(theta)
        labels=np.array(self.tours)[tour];idx=np.arange(len(u));rot=np.exp(1j*chi)
        w=w[labels,idx]*rot;dw=dw[labels,idx]*rot;ddw=ddw[labels,idx]*rot
        r=self.R+w.real;co=np.cos(u);si=np.sin(u)
        x=np.stack((r*co,r*si,w.imag),axis=-1)
        d=np.stack((dw.real*co-r*si,dw.real*si+r*co,dw.imag),axis=-1)
        dd=np.stack(((ddw.real-r)*co-2*dw.real*si,(ddw.real-r)*si+2*dw.real*co,ddw.imag),axis=-1)
        phase=np.stack((-w.imag*co,-w.imag*si,w.real),axis=-1)
        body=np.stack((-r*si,r*co,np.zeros(len(u))),axis=-1)
        return tuple(v[0] if scalar else v for v in (x,d,dd,phase,body))
    def point(self,u):return self.values(u)[0]
    def derivative(self,u):return self.values(u)[1]

def braid_witness():
    braid=FourBraid();levels=[]
    for n in (2000,4000,8000):
        u=np.arange(n)*braid.period/n;x,d,dd,phase,body=braid.values(u)
        speeds=np.linalg.norm(d,axis=1);L=float(speeds.mean()*braid.period)
        curvature=np.linalg.norm(np.cross(d,dd),axis=1)/speeds**3
        area=.5*np.sum(np.cross(x,d),axis=0)*braid.period/n
        levels.append({'samples':n,'length_fm':L,'minimum_curvature_radius_fm':float(1/curvature.max()),
                       'area_vector_fm2':area.tolist(),
                       'uniform_diameters_fm':{k:2*equivalent_radius(V,L) for k,V in VOLUMES.items()},
                       'radial_local_regular_tube_limit_status':'curvature test only; nonlocal union remains separate'})
    eps=1e-6;u=np.linspace(.071,braid.period-.071,99)
    analytic=braid.derivative(u);fd=(braid.point(u+eps)-braid.point(u-eps))/(2*eps)
    seam=braid.point(np.array([0,TAU,2*TAU,3*TAU,4*TAU]))
    moment=levels[-1]['area_vector_fm2'];Rys=np.array([[0,0,1],[0,1,0],[-1,0,0]])
    rotated=[]
    for i in range(4):
        theta=i*math.pi/2;Rz=np.array([[math.cos(theta),-math.sin(theta),0],[math.sin(theta),math.cos(theta),0],[0,0,1]])
        rotated.append(Rz@Rys@np.array(moment))
    result={'status':'constructive topological and geometric witness; physical one-poloidal-traversal interpretation unclosed',
            'word':braid.word,'tour_material_labels':braid.tours,'major_tours':4,
            'spacing_fm':braid.spacing,'major_radius_fm':braid.R,
            'seam_points_fm':seam.tolist(),'positional_closure_fm':float(np.linalg.norm(braid.point(0)-braid.point(braid.period))),
            'analytic_derivative_max_error':float(np.max(np.linalg.norm(fd-analytic,axis=1))),
            'refinement':levels,'relative_director_barrel_rolls':4,
            'relative_director_roll_status':'framing control, not a centreline poloidal-travel substitution',
            'radial_frame_equal_weight_area_sum_fm2':np.sum(rotated,axis=0).tolist()}
    save('FOUR_TOUR_WITNESS.json',result)
    np.savez_compressed(RUN/'FOUR_TOUR_WITNESS.npz',u=np.arange(4000)*braid.period/4000,
                        xyz=braid.point(np.arange(4000)*braid.period/4000))
    return result

def speed_audit():
    samples=np.linspace(0,TAU,65536,endpoint=False);cases=[]
    for label,low in [('operator_corrected_as_renderer_input',.395),('source_generator_reciprocal',1/2.23)]:
        mean=1.84;A=2.23-mean;B=low-mean;amp=math.hypot(A,B)
        v=mean+A*np.cos(samples)+B*np.sin(samples)
        harmonic=math.sqrt(mean*mean-amp*amp)
        cases.append({'case':label,'low_label_c':low,'mean_phase_c':mean,'true_minimum_c':mean-amp,
                      'true_maximum_c':mean+amp,'phase_zero_speed_c':float(v[0]),
                      'phase_median_c':float(np.median(v)),'phase_rms_c':math.sqrt(mean*mean+amp*amp/2),
                      'equal_arclength_harmonic_transport_c':harmonic,
                      'sampled_minimum_c':float(v.min()),'minimum_phase_radians':float((math.atan2(B,A)+math.pi)%TAU),
                      'mean_arclength_weighted_by_speed_c':float(np.mean(v*v)/np.mean(v))})
    mapping=json.loads((OTHER/'SDT/data/trefoil_mappings.json').read_text(encoding='utf-8'))
    fields=[]
    for item in mapping[:5]:
        fields.append({'Z':item.get('Z'),'A':item.get('A'),
                       'nucleon_speed_labels':[ {k:n.get(k) for k in ('type','velocity_v1','velocity_v2','velocity_v3')} for n in item.get('nucleons',[])[:2]]})
    base=(3/2)**1.5
    triangle=(2.23**2-1.84**2-.395**2)/(2*1.84*.395)
    result={'corrected_record_c':[.395,1.84,2.23], 'phase_formula_c':base,
            'characteristic_plus_sinuation_c':base+.395,
            'fast_minus_characteristic_c':2.23-1.84,
            'vector_resultant_angle_degrees':math.degrees(math.acos(triangle)),
            'three_equal_length_segment_harmonic_c':3/(1/.395+1/1.84+1/2.23),
            'characteristic_plus_sinuation_status':'numerical component compatibility, not a derived field',
            'source_renderer_extrema':cases,'source_mapping_samples':fields,
            'phase_field_derivation_status':'OPEN: source renderer phase value is static nucleon.phase_angle; animation rotates meshes separately'}
    save('SPEED_AUDIT.json',result)
    return result

def volume_geometry():
    rows=[];selfconsistent=[]
    for label,R,a,p,q in [('native_H1',R_H1,A_H1,4,3),('canonical_trefoil',RP,RP*math.sqrt(2/3),2,3)]:
        L=length(R,a,p,q);rho=curvature_radius(R,a,p,q);distance=nonlocal_distance(R,a,p,q)
        for species,V in VOLUMES.items():
            b=equivalent_radius(V,L)
            rows.append({'model':label,'species':species,'major_radius_fm':R,'minor_radius_fm':a,
                         'length_fm':L,'volume_fm3':V,'equivalent_radius_fm':b,'equivalent_diameter_fm':2*b,
                         'curvature':rho,'restricted_nonlocal_distance':distance,
                         'same_azimuth_adjacent_lane_gap_fm':math.sqrt(2)*a-2*b if p==4 else None,
                         'restricted_nonlocal_gap_fm':distance['distance_fm']-2*b,
                         'curvature_radius_minus_tube_radius_fm':rho['minimum_radius_fm']-b})
    for species,V in VOLUMES.items():
        square_a=brentq(lambda a:a-math.sqrt(2)*equivalent_radius(V,length(R_H1,a)),.01,.75,xtol=1e-13)
        d_square=nonlocal_distance(R_H1,square_a)
        # Solve an actual 3-D nonlocal contact, not touching circles in one section.
        def gap(a):return nonlocal_distance(R_H1,a)['distance_fm']-2*equivalent_radius(V,length(R_H1,a))
        arange=np.linspace(square_a,min(.7,R_H1*.9),9);gaps=[gap(a) for a in arange]
        brackets=[(arange[i],arange[i+1]) for i in range(8) if gaps[i]*gaps[i+1]<0]
        repaired=brentq(gap,*brackets[0],xtol=2e-10) if brackets else None
        for mode,a in [('same_section_square',square_a),('three_dimensional_self_contact',repaired)]:
            if a is None:continue
            L=length(R_H1,a);b=equivalent_radius(V,L);rho=curvature_radius(R_H1,a);distance=nonlocal_distance(R_H1,a)
            az=math.pi*4*(R_H1**2+a*a/2)
            old_az=math.pi*4*(R_H1**2+A_H1*A_H1/2)
            selfconsistent.append({'species':species,'mode':mode,'major_radius_fm':R_H1,'minor_centreline_radius_fm':a,
                                   'length_fm':L,'volume_fm3':V,'equivalent_tube_radius_fm':b,
                                   'diameter_fm':2*b,'same_section_gap_fm':math.sqrt(2)*a-2*b,
                                   'restricted_nonlocal_contact':distance,'gap_fm':distance['distance_fm']-2*b,
                                   'minimum_curvature_radius_fm':rho['minimum_radius_fm'],
                                   'local_tube_jacobian_positive':b<rho['minimum_radius_fm'],
                                   'charge_path_area_z_fm2':az,
                                   'constant_path_speed_moment_ratio_to_old_H1':(az/L)/(old_az/length(R_H1,A_H1)),
                                   'status':'source T(4,3) control; not certified operator shape or global union proof'})
    nativeV=math.pi*.03**2*length(R_H1,A_H1)
    result={'input_diameter_fm':DE,'input_status':'OPEN body-size input; orientation-traversal volume construction',
            'closure_length_fm':LE,'volume_fm3':VOLUMES,'equal_length_diameter_ratio':math.sqrt(1387/1836),
            'native_H1_tube_volume_fm3':nativeV,'native_H1_effective_electron_closure_count':nativeV/(math.pi*DE**2*LE/4),
            'proton_requested_volume_to_native_H1_volume':VOLUMES['p']/nativeV,
            'single_spatial_lap_volume_factor':.5,'single_spatial_lap_diameter_factor':1/math.sqrt(2),
            'fixed_diameter_3e_minus20_volume_factor':.25,'fixed_diameter_3e_minus20_diameter_factor':.5,
            'common_pressure_mass_engagement_neutron_proton_ratio_required':(1.67492749804e-27/1.67262192369e-27)/(1387/1836),
            'controls':rows,'selfconsistent_T4_3_controls':selfconsistent}
    save('VOLUME_GEOMETRY.json',result)
    with (RUN/'VOLUME_GEOMETRY.csv').open('w',newline='',encoding='utf-8') as f:
        fields=['species','mode','major_radius_fm','minor_centreline_radius_fm','length_fm','volume_fm3','diameter_fm','gap_fm','minimum_curvature_radius_fm','local_tube_jacobian_positive']
        writer=csv.DictWriter(f,fieldnames=fields,extrasaction='ignore');writer.writeheader();writer.writerows(selfconsistent)
    return result

def material_volume_control():
    braid=FourBraid();rows=[]
    for n in (4000,8000):
        u=np.arange(n)*braid.period/n;x,d,dd,phase,body=braid.values(u)
        reference=np.linalg.norm(d,axis=1);L=float(reference.mean()*braid.period)
        Aref=VOLUMES['p']/L
        for chi in (0,math.pi/4,math.pi/2,math.pi,3*math.pi/2,TAU):
            _,d2,_,_,_=braid.values(u,chi);jac=np.linalg.norm(d2,axis=1)
            area=Aref*reference/jac
            V=float(np.mean(area*jac)*braid.period)
            rows.append({'samples':n,'cross_section_phase_radians':chi,'reference_length_fm':L,
                         'instantaneous_length_fm':float(jac.mean()*braid.period),
                         'diameter_min_fm':float(2*np.sqrt(area/math.pi).min()),
                         'diameter_max_fm':float(2*np.sqrt(area/math.pi).max()),
                         'volume_fm3':V,'volume_relative_residual':abs(V/VOLUMES['p']-1)})
    result={'status':'exact material Jacobian conservation on geometric witness, no derived phase clock',
            'local_identity':'A(u,chi)*|X_u(u,chi)| = A_ref*|X_u(u,0)|',
            'rows':rows,'uniform_area_and_local_conservation_compatible_only_if_uniform_stretch':True}
    save('MATERIAL_VOLUME_PHASE.json',result)
    return result

def main():
    start=time.monotonic();freeze=freeze_sources();emit('Source freeze complete')
    crossing=crossing_receipt();topology=topology_controls();emit('Crossing receipt and exact braid polynomial controls complete')
    braid=braid_witness();speeds=speed_audit();emit('Four-tour witness and speed audit complete')
    volume=volume_geometry();emit('Conserved volume, width/spacing, curvature and 3-D self-contact controls complete')
    material=material_volume_control();emit('Phase-resolved material-volume conservation complete')
    integrity=[]
    for row in freeze['sources']:
        if 'sha256' in row:
            current=hashlib.sha256(Path(row['path']).read_bytes()).hexdigest()
            integrity.append({'path':row['path'],'unchanged':current==row['sha256']})
    save('SOURCE_INTEGRITY.json',{'sources':integrity,'all_unchanged':all(x['unchanged'] for x in integrity)})
    save('EXECUTION.json',{'elapsed_seconds':time.monotonic()-start,'source_count':len(integrity),
                           'new_physical_fit_coefficients':0,'operator_shape_identification':'OPEN',
                           'completed':['crossing receipt','exact topology controls','constructive four-tour witness',
                                        'source speed audit','finite-width conservation','3-D self-contact controls',
                                        'phase-resolved local volume','protected source integrity']})
    emit('Initial shape execution complete; alpha coupling follows separately')

if __name__=='__main__':main()
