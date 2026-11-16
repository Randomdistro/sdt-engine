from pathlib import Path
import json,csv,hashlib,math,datetime
RUN=Path(__file__).resolve().parent;ROOT=RUN.parents[2]
def read(n):return json.loads((RUN/n).read_text(encoding='utf-8-sig'))
def write(n,t): (RUN/n).write_text(t.strip()+'\n',encoding='utf8')
base=read('BASELINE.json');native=read('NATIVE_CONTROLS.json');geo=read('CONSTRAINT_SPECTRA.json');braid=read('BRAID_GEOMETRY.json');radial=read('RADIAL_KINEMATIC_CONTROL.json');radial_geo=read('RADIAL_FINITE_GEOMETRY.json');far=read('MAGNETIC_FAR_RESPONSE.json');overlap=read('WEIGHTED_OVERLAP_CONTROL.json');joint=read('JOINT_RESPONSE.json');jac=read('RIGID_CONTACT_JACOBIANS.json');work=read('PATH_WORK.json');radial_energy=read('RADIAL_ENERGY_PROXY.json');freeze=read('SOURCE_FREEZE.json')
changed=[p for p,h in freeze['files'].items() if hashlib.sha256((ROOT/p).read_bytes()).hexdigest()!=h]
write('SOURCE_INTEGRITY.json',json.dumps({'protectedFiles':len(freeze['files']),'changed':changed,'canonicalUnchanged':not changed},indent=2))
dep=[
('D01','c,hbar,alpha','m/s,J s,1','Engine/include/sdt/laws.hpp:95','OBSERVED-INPUT','canonical supplied action/spectral seats; no independent alpha derivation'),
('D02','P_conv','Pa','Engine/include/sdt/laws.hpp:236','DERIVED-CONDITIONAL','depends on supplied CMB boundary, l_P and radiation/action seats'),
('D03','R_p_lock','m','Engine/include/sdt/laws.hpp:448','DERIVED-CONDITIONAL','4 hbar/(mp c), supplied mass/action; not a proven engaged-domain boundary'),
('D04','R_p=0.8414 fm','m','Release/HTML_SDT_Website/js/nuclear-inputs.js','OBSERVED-INPUT','baseline geometry only; predicted lock radius in independent C++ control'),
('D05','H1 body (4,3) form','Rp','Release/HTML_SDT_Website/js/traction-gear-engine.js:20','MODEL-ASSUMPTION','5.28 fm length, 0.06 fm diameter; no current native boundary/width selection derived'),
('D06','NSEQ16 (4,5) braid','Rp','Release/HTML_SDT_Website/js/traction-gear-engine.js:10','MODEL-ASSUMPTION','major .62, minor .22, core .16; distinct representation from H1'),
('D07','canonical trefoil (2,3)','topology','Engine/include/sdt/laws.hpp:2235','AXIOM','relation to consumed H1 and braid parameterisations unresolved'),
('D08','three oriented ports','count','prompt section 3.2','MODEL-CONSTRAINT','cap retained; physical port directions and phase relation OPEN'),
('D09','spherical contact slip','1','Release/HTML_SDT_Website/js/traction-gear-engine.js:2142','COMPUTED','fixed-axis spherical rim calculation, no finite strand contact law'),
('D10','0.05 degree wake compliance','1','Release/HTML_SDT_Website/js/traction-gear-engine.js:3015','MODEL-ASSUMPTION','not derived from collective torque or minimum energy'),
('D11','0.018 degree split shift','1','Release/HTML_SDT_Website/js/traction-gear-engine.js:3016','MODEL-ASSUMPTION','alpha degree2 gives zero; physical coefficient selection unresolved'),
('D12','wake field core .08 Rp','Rp','Release/HTML_SDT_Website/js/traction-gear-engine.js:376','MODEL-ASSUMPTION','regularization is distinct from physical strand width'),
('D13','absolute contact-family overlaps','proxy units','Release/HTML_SDT_Website/js/traction-gear-engine.js:1018','COMPUTED','pointwise sign discarded; signed joint work law absent'),
('D14','alpha hbar c/Rp energy scale','MeV','Release/HTML_SDT_Website/js/traction-gear-engine.js:3049','DERIVED-CONDITIONAL','dimensional scale exists; absolute-overlap-to-binding map OPEN'),
('D15','proton magnetic bridge','muN/proxy','Release/HTML_SDT_Website/js/traction-gear-engine.js:880','CALIBRATED','measured proton moment divided by basis moment'),
('D16','neutron counter coefficient','muN/proxy','Release/HTML_SDT_Website/js/traction-gear-engine.js:885','CALIBRATED(1)','target neutron minus proton contribution divided by counter basis'),
('D17','pi/4 counter phase','rad','Release/HTML_SDT_Website/js/traction-gear-engine.js:872','MODEL-ASSUMPTION','physical selection not derived in the inspected definition'),
('D18','1.83c circulation seat','m/s','Release/HTML_SDT_Website/js/traction-gear-engine.js:35','OPEN','requires phase/pattern-to-material map under Law V'),
('D19','native engaged-volume kernel','m3','Engine/include/sdt/laws.hpp:595','DERIVED-CONDITIONAL','spherical supplied boundary and isotropic response'),
('D20','saturated coherent max union','m3','FLM15_Influx_Phase_Resistance_Ratio/MODEL_SPEC.md','MODEL-ASSUMPTION','coherent supplied-domain control; mixed-phase collective law OPEN'),
('D21','NP05 volume binding','J','Engine/include/sdt/laws.hpp:216','EXCLUDED','simple E=P Delta V rejected; no revival by relabelling'),
('D22','NP06/CQ41 mesh frequency','rad/s','NP06_Gear_Frequency_Binding_Functional/PROMPT.md','OPEN','source requires independently computed geometric frequency; no executable frequency selection located'),
('D23','NP17 point-seat energy','J','NP17_Nuclear_Packing_Order_Discovery/np17_nuclear_packing.cpp','COMPUTED','forward control only; finite neutron/electron geometry and stable alpha state missing'),
('D24','native circulation-to-magnetic observable','muN','traction-gear-engine.js:704','OPEN','source explicitly marks dimensional spation-flow/effective-current map PENDING'),
('D25','native energy/evolution/selection law','J,1/s','alpha prompt ADEP04/07','OPEN','no common native force/torque/storage map supplied'),
('D26','radial ring axes','1','RADIAL_KINEMATIC_CONTROL.json','DERIVED-CONDITIONAL','C4 geometry and rigid-surface velocity; no energy minimisation or field fitting'),
('D27','alpha binding and magnetic zero','MeV,muN','preceding known benchmarks','OBSERVED-COMPARISON','not consumed for state choice; target-aware, not blind'),
]
with (RUN/'DEPENDENCY_LEDGER.csv').open('w',newline='',encoding='utf8') as f:
    w=csv.writer(f);w.writerow(['id','quantity','units','source','status','limitations']);w.writerows(dep)
integration={t:t in (ROOT/'Engine/include/sdt/laws.hpp').read_text(encoding='utf8') for t in ['magic_numbers[8]','triton_opening_scale','triton_closing_scale','triton_closure_scale']}
write('CANONICAL_INTEGRATION.json',json.dumps({'tokenAssertions':integration,'interpretation':'four token assertions fail; token failure is separate from physical construction; no constants inserted'},indent=2))
write('STATE_AND_UNITS.md',f'''# State and units
Baseline centres use fm; normalized geometry uses Rp=0.8414 fm. Quaternion convention is [x,y,z,w]. Body strand parameters use u in [0,2pi), distinct from proxy wake phases. Full body pose has six coordinates, four bodies total24, with six global pose gauges.
Baseline alpha uses K(2,2), four unlike contacts, degree2. Native spherical contact radius is Rp. Native H1 form uses major tours4, cross-section turns3, radius fractions from 5.28/2pi fm and 0.06 fm diameter. NSEQ16 braid uses (4,5), .62/.22/.16 radius fractions. Canonical topology namespace names the (2,3) trefoil. No identity map connecting the consumed parameterisations to a unique physical proton form was established.
Curve audits assume Euclidean tubular cores and identity or radial frames. Native oriented ports, phase offsets, deformation law and physical strand-core selection remain OPEN. Strand tangents are curve derivatives; spherical rim rolling velocities are different objects.
Canonical C=alpha hbar c [J m] and Rp_lock [m] feed conditional NP17 controls. Law-IV resistance has joule units, but joule dimensions alone establish no binding energy. Magnetic vectors are calibrated proxy values in mu_N; SI nuclear magneton uses e hbar/(2mp), separate from canonical mu_N symbol containing the signed neutron moment.
Pattern/phase speed and material movement speed remain distinct. The 1.83c source seat has no resolved material-speed mapping; a material interpretation violates the declared v_circ^2+v_trans^2=c^2 budget by 2.3489 c^2 even at zero translation.
''')
mass_scale=native['constituent_rest_energy_J']/4
radius_ratio=native['lock_resistance_J']/mass_scale
b_equiv=native['R_p_lock_m']*(mass_scale/native['lock_resistance_J'])**(1/3)
signedContact=[]
for row in base['wakeRefinement']:
    signed=sum(v for p in row['pairs'] for key,v in p['byFamily'].items() if all(k in {'convergent','throat','poloidal'} for k in key.split(':')))
    signedContact.append({'grid':row['grid'],'absoluteContact':row['totalAbsoluteContactCoupling'],'signedContact':signed,'allFamilySigned':row['totalSignedCoupling']})
write('SIGNED_OVERLAP_AUDIT.json',json.dumps(signedContact,indent=2))
write('DERIVATION.md',f'''# Conditional mechanisms and missing closure

## Spherical gear constraint and radial cancellation
For active spherical contact normal n=(x_j-x_i)/(2Rp), equal point velocities require
v_i+Omega_i cross (Rp n)=v_j+Omega_j cross (-Rp n).
With fixed centres: (Omega_i+Omega_j) cross n=0. The existing implementation fixes the axis z and circulation signs sigma_p=+1, sigma_n=-1.
Within the existing equal-radius spherical approximation at a common angular rate Omega_0 [1/s], radial axes a_i=x_i/|x_i| and Omega_i=Omega_0 sigma_i a_i satisfy the conditional rolling equation: every unlike-edge angular sum is parallel to the edge normal. Reported slip is normalised by Omega_0 Rp; no physical value of Omega_0 is selected. Opposite same-species axes imply m_p a_0+m_p a_2=0 and m_n a_1+m_n a_3=0 independently of the two magnetic magnitudes. No alpha energy or moment target selects the radial axes. The branch is an admissible spherical kinematic symmetry, not a selected native energy minimum.
Execution gives maximum spherical slip {max(r['slip'] for r in radial['slips']):.3g} and magnetic norm {radial['magnitudeMuN']:.12g} mu_N. Conditional cancellation survives the inherited unequal proton/neutron magnetic calibrations. Physical magnetic mapping, finite strand traction and stable pose selection remain OPEN.

## Finite geometry
The existing H1 identity placement has contact core penetration near0.06552275 Rp. Uniform geometric expansion factor1.07521543 restores contact gaps, but tangent error remains0.00291863, beyond1e-8. The NSEQ16 identity braid instead has positive contact gap0.04625050 Rp; the sampled Lipschitz lower bound exceeds0.04135 Rp at6000 samples.
Radial H1 reseating factor {radial_geo['rows'][0]['selectedCentreScale']:.12g} restores four local closest-contact gaps but tangent error remains about0.00311825. Radial braid reseating factor {radial_geo['rows'][1]['selectedCentreScale']:.12g} restores local gaps but tangent error remains about0.22968974. Neither branch passes G1. Closest-point optimisation is local; global sampling bounds qualify the identity tests, while reseated candidates require complete noncontact/core and phase audits before physical promotion.
Normal-centre constraint rank4, conditional tangential rank8, combined spherical no-slip rank12. After six rigid gauges, the combined model retains six internal instantaneous pose/velocity modes. Constraint rank does not establish an energy minimum, restoring dynamics or finite strand phase closure.

## Joint engagement
For supplied coherent spherical domains: V_eng=8pi b^3/7 and R=(Pconv/3)V_eng. At b=Rp_lock and centres separated by2Rp_lock, overlap sets have zero measure and joint engagement equals summed engagement. Synchrony saving is exactlyzero. Choosing larger b introduces a new physical boundary assumption, not a derived alpha bond.
For b=1.1Rp, no triple overlap occurs; coherent max engagement equals sum(parts) minus sum(pair minima). For two spheres separation d, the overlap minimum weight integral is
I(b,d)=8pi/(5 sqrt(b)) integral_0^(b-d/2) [(b^2-2dx)^(5/4)-(d/2-x)^(5/2)]dx,
for d/2<b<d. Four equal unlike lenses give joint engagement 4(8pi b^3/7)-4I. Independent two-dimensional Gauss quadrature at32/64/128 nodes agrees with the analytic integral to <={max(r['relativeError'] for r in overlap['rows']):.3g} relative. The result is a mathematical supplied-domain control.
At b=1.5Rp, triple and four-body overlap appear; pair-only geometry therefore omits nonzero contributions. A phase-weighted alpha engagement rule still requires actual mechanical domains and collective phase response.

## Scale selection
Using Rp_lock as the spherical engagement boundary gives {native['lock_resistance_J']:.12g} J per sphere, versus a separated constituent average {mass_scale:.12g} J, a ratio {radius_ratio:.12g}. The comparison excludes automatic identification of the lock-radius sphere with the mass-bearing engaged domain. An inverted equivalent engagement radius {b_equiv:.12g} m follows only from a supplied mass seat; the inversion is not a derived boundary or a predicted alpha radius. No filter amplitude was fitted to absorb the mismatch.
The cross-domain scaling exposes the same missing identification: a lock boundary b=q hbar/(mc) scales as1/m, whereas the supplied spherical Law-IV engagement radius satisfying mc^2=(Pconv/3)(8pi b^3/7) scales as m^(1/3). Combining both identities with fixed pressure and q would impose m^4=8pi Pconv q^3 hbar^3/(21c^5), selecting one mass scale rather than providing a universal boundary law. A physical engagement/phase map must distinguish the two radii; no mass-dependent correction was inserted.

## Independent energy routes
NP17 point-seat control: four positive cores on a tetrahedron and two negative seats at opposite-edge midpoints; C=alpha hbar c. Conditional alpha binding at2Rp_lock is {native['NP17_conditional']['alpha_binding_MeV']:.12g} MeV. The control has U(a)=-K/a, positive dU/da and no interior stationary point. Hard contact reaction, finite intrinsic neutron reference and electron motion selection remain absent. Independent path integration reproduces the point-model potential difference and zero closed-loop work. The result proves conservative mathematics for the supplied potential, not physical alpha binding.
NP06 primary source requires Delta omega calculated independently from meshed geometry. E/hbar supplied as Delta omega is an identity and earns no independent route. No executable collective frequency selection was located in the inspected current NP06 source and canonical namespaces.
The existing wake proxy sums absolute local contact-family cross terms. Signed contact terms and all-family terms differ and receive separate records. No independently specified native force/torque law was matched to the proxy gradient. Redefining force as a derivative of the chosen score would create a new constitutive assumption, not verify the existing mechanism.
Energy uses generic handed wake poses; magnetic response uses a proton-form basis plus a calibrated neutron counter basis. A native map establishing a common physical circulation state for both responses remains missing.
''')
write('STABILITY_REPORT.md','''# Stability and non-identifiability
The conditional spherical no-slip model retains six internal instantaneous modes after removal of global translation and rotation. No native restoring force/torque or phase evolution law closes the modes. A rank12 kinematic model cannot establish a stable alpha state.
The radial symmetry branch supplies exact spherical rolling and proxy dipole cancellation but fails finite strand tangency. Symmetry alone selects no equilibrium energy and supplies no perturbation restoration. Nonlinear stability remains OPEN ADEP03/04/07.
The NP17 supplied tetrahedral point-seat potential U=-K/a lacks an interior stationary radius. A hard boundary can constrain shrinking but needs a physically admissible contact reaction and conserved intrinsic neutron reference. No elastic coefficient or conventional potential was introduced.
Non-identifiability is localised: multiple permitted body-axis frames exist under the spherical approximation; existing axis choice is a construction convention. Mechanical boundary and joint phase-response definitions do not select an alpha energy. Native collective frequency selection remains absent. A complete model needs one consistent finite body/port representation, joint circulation response and a state/work or equivalent movement-to-energy map. Choosing a measured-binding winner among states would not close the selection law.
''')
write('NOVELTY_REPORT.md','''# Novelty boundary
The radial-axis conditional cancellation is an explicit kinematic result from equatorial ring geometry: unlike rigid rolling passes, while equal-species vector pairs cancel. The result does not depend on a fitted alpha magnetic coefficient. The result remains conditional on spherical contact and the inherited observable proxy; finite strand tangency and physical pose selection fail or remain missing.
No priority or new physical validation claim follows. A systematic prior-art review was not performed, and mathematical gear symmetry alone does not establish a new nuclear mechanism. The independently integrated weighted sphere-overlap formula is a numerical/analytic control, not a nuclear energy law.
The baseline alpha energy and moment are known targets. Existing light-nucleus fits remain calibrated. No independent mechanism-sensitive nuclear observable was sealed and compared with a new measurement. The energy, physical magnetic mapping and finite-contact gates prevent a manuscript or publication submission.
Core mechanism: simultaneous finite contact plus common collective circulation/energy/observable map. Scaling: alpha/D/T stacking after closure. Deployment and IP assessment: outside the current execution scope.
''')
write('MECHANISM_INTERFACES.md','''# Minimal native closure interfaces
ADEP01: intrinsic proton/neutron circulation state and action ownership. Inputs: topology, supplied seats and native boundaries. Outputs: conserved circulation, vector response and intrinsic separated reference. Calibrated counter coefficients cannot supply a derived neutron closure.
ADEP02/03: one consistent finite body form, core and distinct oriented ports. Inputs: body poses, strand phase and conserved movement. Outputs: contact gap, traction velocity, phase transfer and simultaneous cycle compatibility. Spherical centre normals do not close finite strand contacts.
ADEP04: native joint phase-resolved response and equivalent storage/work law. Inputs: complete collective state. Outputs: joint response, separating work, force/torque or an independently justified circulation-energy correspondence. A supplied radius plus Pconv Delta V is insufficient.
ADEP05: independent mesh movement rate from geometry and conserved action. Inputs: admissible contact state, circulation and synchrony. Output: Delta omega without reading E_bind or alpha target mass. Source NP06 provides the correspondence question, not an executable selecting equation.
ADEP06: measured magnetic response from the same physical circulation. Inputs: collective state and declared probe. Output: vector response in stated units, with existing bridges exposed. Current calibrated vector cancellation can remain a diagnostic.
ADEP07: native evolution or justified conservative invariants. Outputs: equilibrium, restoring response and permissible perturbations.
ADEP08: independent mechanism-sensitive observable, measurement and uncertainty budget after prediction seal. No observable has been fabricated to satisfy the gate.
Smallest next closure: two simultaneous unlike ports on one nucleon within the four-edge alpha cycle, using a unique finite body/phase representation. Radial kinematic symmetry offers a cancellation candidate; a joint traction/phase law must establish an admissible finite embedding before energy promotion.
''')
energies=[{'term':'isolated_lock_sphere','value_J':native['lock_resistance_J'],'status':'conditional response control; no alpha boundary'}, {'term':'separated_2p2n_rest','value_J':native['constituent_rest_energy_J'],'status':'supplied measured resistance seats'}, {'term':'NP17_tetra_point_energy','value_J':-native['NP17_conditional']['alpha_binding_MeV']*1.602176634e-13,'status':'point-seat mathematical control'}, {'term':'native_alpha_energy','value_J':'OPEN','status':'ADEP01/03/04/05'}, {'term':'outgoing_energy','value_J':'OPEN','status':'no closed assembly/emission law'}, {'term':'alpha_binding_proxy','value_MeV':base['observableLedger']['massDefect']['calculatedBindingMeV'],'status':'inherited proxy; not physical closure'}]
with (RUN/'ENERGY_LEDGER.csv').open('w',newline='') as f:
    w=csv.DictWriter(f,fieldnames=['term','value_J','value_MeV','status']);w.writeheader();w.writerows(energies)
ref=[]
for r in base['wakeRefinement']:ref.append({'control':'absolute contact wake','resolution':'x'.join(map(str,r['grid'])),'value':r['totalAbsoluteContactCoupling'],'status':'proxy spatial refinement'})
for r in base['magneticRefinement']:ref.append({'control':'frozen magnetic vector norm','resolution':str(r['samples']),'value':r['magnitudeMuN'],'status':'CALIBRATED proxy'})
for r in native['lock_integrals']:ref.append({'control':'spherical lock relative error','resolution':str(r['N']),'value':r['relative_error'],'status':'analytic control'})
for r in overlap['rows']:ref.append({'control':'weighted overlap relative error','resolution':str(r['N']),'value':r['relativeError'],'status':'analytic control'})
with (RUN/'REFINEMENT.csv').open('w',newline='') as f:
    w=csv.DictWriter(f,fieldnames=ref[0]);w.writeheader();w.writerows(ref)
wake_change=abs(base['wakeRefinement'][-1]['totalAbsoluteContactCoupling']-base['wakeRefinement'][-2]['totalAbsoluteContactCoupling'])/base['wakeRefinement'][-1]['totalAbsoluteContactCoupling']
write('VALIDATION.csv','quantity,prediction,comparison,status\nalpha_binding_proxy_MeV,11.689837263922138,28.296,target-aware diagnostic; physical closure OPEN\nalpha_magnetic_proxy_muN,1.6506325748201107,0,target-aware diagnostic; cancellation fails baseline\nradial_proxy_vector_muN,near zero,known zero,conditional symmetry control; finite traction OPEN\nindependent_mechanism_sensitive_observable,NOT_AVAILABLE,NOT_OPENED,ADEP08 OPEN\n')
gates=[{'gate':'G0','decision':'PASS-GATE','physics':'baseline/provenance controls; inherited calibration'}, {'gate':'G1','decision':'OPEN','physics':'tested identity and radial finite embeddings fail contact/tangency; spherical controls computed'}, {'gate':'G2','decision':'OPEN','physics':'coherent supplied-domain controls computed; actual alpha joint phase response missing'}, {'gate':'G3','decision':'OPEN','physics':'native alpha energy map/selection absent; NP17 point potential computed'}, {'gate':'G4','decision':'OPEN','physics':'radial proxy cancellation PASS; physical common-state observable and admissibility missing'}, {'gate':'G5','decision':'OPEN','physics':'conditional separation/work controls pass; nuclear dissociation/stability incomplete'}, {'gate':'G6','decision':'OPEN','physics':'no independent physical measurement validation'}]
result={'schema':'SDT-ALPHA-CLOSURE-1','head':freeze['head'],'protectedFiles':len(freeze['files']),'changedProtectedFiles':changed,'executionGrade':'B: executable independent controls completed; physical dependency gates remain open','parentPhysicalClass':'OPEN','newPhysicalFitParameters':0,'gates':gates,'baseline':{'bindingProxyMeV':base['observableLedger']['massDefect']['calculatedBindingMeV'],'momentVectorMuN':base['observableLedger']['magnetic']['integralVectorMuN'],'metadataInvariance':base['metadataInvariance'],'lastWakeRelativeChange':wake_change},'radialConditional':radial,'radialFinite':radial_geo,'radialEnergyProxy':radial_energy,'native':native,'originalSourceControls':read('ORIGINAL_SELF_TEST.json')['checks'],'farResponse':far,'engagementBoundaryDiagnostic':{'lockSphereToConstituentRestRatio':radius_ratio,'invertedEquivalentBoundary_m':b_equiv,'status':'not an inferred physical boundary'},'signedContactAudit':signedContact,'tests':{'nativeAnalyticPassed':native['failures']==0,'overlapAnalyticPassed':max(r['relativeError'] for r in overlap['rows'])<=1e-10,'pathWorkPassed':max(r['constituent_scaled_residual'] for r in work)<=1e-6,'baselineCancellationPassed':False,'radialProxyCancellationPassed':radial['magnitudeMuN']<=1e-6,'radialSphericalSlipPassed':max(r['slip'] for r in radial['slips'])<=1e-8,'nativeFiniteRadialTangencyPassed':False,'proxyEnergySpatialRefinementPassed':wake_change<=1e-3,'sourceIntegrityPassed':not changed}}
write('RESULTS.json',json.dumps(result,indent=2))
sealed_names=['BASELINE.json','NATIVE_CONTROLS.json','RADIAL_KINEMATIC_CONTROL.json','RADIAL_FINITE_GEOMETRY.json','DERIVATION.md','RESULTS.json']
write('PREDICTION_SEAL.json',json.dumps({'utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'purpose':'seal conditional outputs and OPEN interfaces, not a held-out physical prediction','knownTargetExposure':freeze['known_targets'],'newMeasurementOpened':False,'newFitBudget':0,'files':{n:hashlib.sha256((RUN/n).read_bytes()).hexdigest() for n in sealed_names}},indent=2))
write('VERDICT.md',f'''# Alpha closure execution verdict

Execution grade: B — independent executable branches completed; named physical dependency gates remain OPEN.
Parent physical class: OPEN. New fitted physical coefficients:0. Canonical/public protected sources unchanged: {not changed}; {len(freeze['files'])} frozen files checked.

## Surviving conditional result
Radial circulation axes on the existing equatorial unlike-contact ring satisfy conditional spherical rolling with zero slip. Opposite equal-species axes cancel the complete calibrated magnetic vector to {radial['magnitudeMuN']:.6g} mu_N. The cancellation requires no alpha-specific coefficient and follows from geometry before measurement comparison. Finite body contact/tangency, native pose selection, common energy and physical observable maps remain unclosed; the result is not a validated nuclear model.

## Numerical and physical gates
| Gate | Decision | Evidence |
|---|---|---|
{chr(10).join('| '+r['gate']+' | '+r['decision']+' | '+r['physics']+' |' for r in gates)}

Baseline: {base['observableLedger']['massDefect']['calculatedBindingMeV']:.12g} MeV proxy binding and {base['observableLedger']['magnetic']['integralVectorMuN'][2]:.12g} mu_N axial moment. Alpha metadata removal leaves state unchanged. The final tested wake grid change is {100*wake_change:.6g}%, exceeding the0.1% convergence gate. Analytic C++ lock and source-supported point-seat controls pass; independent weighted-overlap quadrature passes; point-potential closed-loop work passes. Full-vector far-response extrapolation agrees with the frozen magnetic proxy to {far['extrapolatedAbsoluteErrorMuN']:.6g} mu_N.

## Mechanism debt identified
Existing H1 identity body placement interpenetrates contact cores; native NSEQ16 braid identity placement leaves positive contact gaps. Conditional radial/identity reseating repairs gaps but not strand tangency. The spherical no-slip model retains six internal modes after gauge removal. No finite port/phase or restoring law selects a physical state.
Using Rp_lock automatically as the spherical engaged-domain boundary gives {native['lock_resistance_J']:.8g} J per sphere, about {radius_ratio:.6g} times the supplied constituent rest-energy scale. The test excludes that automatic boundary identification, not Law IV itself. A phase-resolved mechanical engagement domain is required.
NP17 gives {native['NP17_conditional']['alpha_binding_MeV']:.8g} MeV in the supplied point-seat tetrahedron and lacks an interior equilibrium; finite neutron/internal-electron reference and common alpha energy remain OPEN. NP06 contains the movement-correspondence specification but requires an independently derived mesh rate. E/hbar cannot supply independent frequency validation.

## Immediate next native closure
Derive a consistent finite-body two-port contact/phase law inside the alpha cycle, with actual strand velocity and shared engagement. Test the radial cancellation candidate through finite tangency and cycle compatibility. A common joint force/torque/work or equivalent circulation-energy map must then select the same state for binding and magnetic response. No independent physical benchmark or manuscript gate passed.
''')
write('README.md','''# Reproduction
Run commands from the repository root. Preserve SOURCE_FREEZE.json and use a separate directory for a new frozen experiment.

```powershell
$run = 'Investigations/SDT_Alpha_Contact_Energy_Phase_Closure/run_2026-10-03_01'
node "$run/baseline.js"
node "$run/original_controls.js"
cmake -S $run -B "$run/build" -G 'Visual Studio 17 2022' -A x64
cmake --build "$run/build" --config Release --parallel 4
& "$run/build/Release/sdt_alpha_controls.exe" | Set-Content -Encoding UTF8 "$run/NATIVE_CONTROLS.json"
ctest --test-dir "$run/build" -C Release --output-on-failure
py -3 -B "$run/geometry.py"
py -3 -B "$run/braid_geometry.py"
py -3 -B "$run/contact_reseat.py"
py -3 -B "$run/constraints.py"
py -3 -B "$run/joint_response.py"
py -3 -B "$run/overlap_control.py"
py -3 -B "$run/magnetic_far.py"
py -3 -B "$run/path_work.py"
node "$run/radial_control.js"
py -3 -B "$run/radial_geometry.py"
node "$run/radial_energy.js"
py -3 -B "$run/assemble_report.py"
```

Toolchain: Python3.13, NumPy2.2.5, SciPy1.16.3; Node22.14.0; CMake/MSVC19.44 C++20 x64 Release. Native compiler flags /fp:strict. The build emitted a nonfatal missing pwsh post-build message; executable and CTest executed successfully. No PowerShell7 dependency was added.
Read VERDICT.md, DERIVATION.md and MECHANISM_INTERFACES.md together. No source-wide physical absence claim is based solely on a constant namespace: NP06, NP17, FLM15, actual NSEQ implementations and native observable maps were inspected. Source-comment labels, proxy scores, kinematic constraints and physical closure retain separate statuses.
''')
with (RUN/'RUN_LOG.md').open('a',encoding='utf8') as f:
    f.write('\n## Final receipts\nNative CMake/MSVC build and registered CTest passed. baseline.js reproduced target-aware state; numerical-only VM stencil overrides preserved original source bytes. geometry.py, braid_geometry.py and contact_reseat.py audited finite bodies; constraints.py separated normal/tangential ranks. joint_response.py and overlap_control.py computed supplied-domain controls. magnetic_far.py independently extracted the proxy vector. path_work.py integrated the conditional point potential. radial_control.js/radial_geometry.py/radial_energy.js executed ADJ-004 without alpha fitting. assemble_report.py created phase reports, ledgers, seal and source-integrity check. No new measurement, physical potential, rate or correction coefficient was introduced. Parent physical class OPEN; manuscript gate unmet.\n')
print(json.dumps({'physicalClass':'OPEN','radialMomentMuN':radial['magnitudeMuN'],'radialSphericalSlip':max(r['slip'] for r in radial['slips']),'lastWakeRelativeChange':wake_change,'engagementScaleRatio':radius_ratio,'protectedChanges':changed},indent=2))
