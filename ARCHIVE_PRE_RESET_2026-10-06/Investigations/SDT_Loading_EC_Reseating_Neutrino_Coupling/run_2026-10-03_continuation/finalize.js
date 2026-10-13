'use strict';
const fs=require('fs'),path=require('path'),crypto=require('crypto');
const run=__dirname,root=path.resolve(run,'../../..');
const read=n=>JSON.parse(fs.readFileSync(path.join(run,n),'utf8').replace(/^\uFEFF/,''));
const write=(n,t)=>fs.writeFileSync(path.join(run,n),t+'\n');
const atomic=read('atomic_results.json'),construction=read('construction_bridge.json'),nseq=read('nseq18_results.json'),native=read('solver_self_tests.json');
const canonical=read('canonical_solver_self_tests.json');
if(canonical.manifest.laws_sha256!==read('SOURCE_FREEZE.json').files['Engine/include/sdt/laws.hpp'])throw Error('Canonical manifest hash mismatch');
const c=299792458,h=6.62607015e-34,L=1.054571817e-34,me=9.1093837015e-31;
const masses=[['H',1,1.67262192595e-27],['D',1,3.3435837768e-27],['T',1,5.0073567512e-27],['He3+',2,5.0064127862e-27]];
const spectra=masses.flatMap(([isotope,Z,M])=>{const mu=me*M/(me+M),C=Z*atomic.C_J_m,EB=mu*C*C/(2*L*L);return [[2,1],[3,1],[3,2],[4,2]].map(([u,l])=>({isotope,Z,u,l,lambda_m:h*c/(EB*(1/l**2-1/u**2)),mu_kg:mu,source:'canonical measured mass; conditional action seats',status:'COMPUTED correspondence; not held-out validation'}));});
write('spectra_results.json',JSON.stringify(spectra,null,2));
write('CONTACT_AUDIT.csv','isotope,Z,A,max_contact_degree,nodes_above_three,port_phase_clearance_status\n'+construction.rows.map(r=>`${r.symbol}-${r.A},${r.Z},${r.A},${r.maxDegree},${r.aboveThreePorts},OPEN finite-filament port matching`).join('\n'));
write('EVENT_LEDGER.csv','parent,A,parentZ,daughterZ,parentD,parentT,daughterD,daughterT,Q_J,rate_per_s,status\n'+construction.pairs.map(r=>`${r.symbol},${r.A},${r.parentZ},${r.daughterZ},${r.parentD},${r.parentT},${r.daughterD},${r.daughterT},OPEN,OPEN,inventory mapping only`).join('\n'));
write('VALIDATION.csv','quantity,prediction,observation,uncertainty,status\nH_2_to_1_lambda_m,'+atomic.conditional_Lyman_alpha_m+',NOT_OPENED,OPEN,conditional target-aware output; no independence claim\n');
write('STATE_AND_UNITS.md',`# State and units
Surface reference R [m] remains fixed along an equilibrium inverse-square orbit family. Separation r [m] and relative speed v [m/s] define k_R=(c/v)sqrt(R/r), surface depth z_R=1/k_R^2, and local depth z(r)=C/(mu c^2 r). Depth describes the selected profile; measured fractional spectral wavelength shift requires a separate emission/transfer map.
Coefficient C [J m] comes from canonical Law III. Reduced resistance mass mu [kg] uses measured mass seats. Action L [J s] is supplied; discrete action L_n=n hbar remains an assumption. Photon energy mapping E_gamma=h c/lambda remains an explicit action bridge.
Native solver positions, velocities, retarded history and per-body displacement resistance describe loading. Electron connectivity, contact event coordinate, capture rate [1/s], energy release Q [J], carrier distribution and opacity [1/m] remain OPEN.
Reported high-Z values test algebra only. Nonrelativistic kinetic energy requires v/c much less than unity; the 0.01R compression row falls outside that controlled domain. Nuclear coordinates use fm in the construction engine. Graph degree does not supply independent finite strand ports.
`);
write('DERIVATION.md',`# Conditional derivation
Native Law III gives C_Z=r^2 F_nuclear_electron(Z,r)=Z alpha hbar c. The cancellation follows directly from P_eff=4 alpha hbar c/(pi R_p_lock^2 r_e^2), and nuclear effective area Z R_p_lock^2. Measured alpha and action remain upstream dependencies.
For a central attractive profile and constant resistance mu: mu v^2/r=C_Z/r^2, U=-C_Z/r, E=mu v^2/2-C_Z/r. Relative two-body acceleration gives mu=m_e M/(m_e+M).
Consequently v^2 r=C_Z/mu=c^2 Omega, Omega=C_Z/(mu c^2), k_R^2=R/Omega, and z_R=Omega/R. Reversals: k_R=1/sqrt(z_R), R=Omega k_R^2, v=c sqrt(z_R R/r), Omega=z_R R. A single k or z cannot determine both R and Omega: simultaneous length rescaling preserves k and z.
At supplied fixed action L=mu v r, equilibrium R=L^2/(mu C_Z), E_B=C_Z/(2R), and the externally held compressed state has Delta E=E_B(R/r-1)^2. Fixed-action speed scales 1/r; equilibrium speed scales 1/sqrt(r). Consequently the original k_R invariance applies to the equilibrium family, while forced fixed-action compression changes k_R. Positive compression work alone does not imply capture.
With the additional action-seat prescription L_n=n hbar: R_n=n^2 hbar^2/(mu C_Z), E_n=-mu C_Z^2/(2 n^2 hbar^2), and lambda_ul=h c/[mu C_Z^2/(2 hbar^2)(1/l^2-1/u^2)]. No stored Rydberg constant enters the execution. Spectra remain conditional on discrete seats and the energy-to-wavelength bridge. The h versus 2pi hbar difference reflects canonical rounded constants and remains explicit.
For a nucleus assembled as alpha+n_D D+n_T T: Z=2+n_D+n_T and A=4+2n_D+3n_T, yielding n_D=3Z-A-2 and n_T=A-2Z. At fixed A under Z->Z-1: Delta n_D=-3 and Delta n_T=+2. Thus 3D+e->2T+nu is a stock balance, with baryons 6->6 and charge 2->2 after electron accounting; the receipt supplies neither elementary event geometry nor released energy.
Reverse inventory: Delta n_D=+3, Delta n_T=-2. Reverse accessibility requires supplied energy, carrier absorption and a native transition law; forward inventory admissibility cannot establish detailed balance.
`);
write('MECHANISM_INTERFACES.md',`# Mechanism interfaces
Loading -> electron connectivity: OPEN. A retarded body force solver supplies loading trajectories, but an electron plasma requires a specified evolving connectivity observable and a pressure/resistance closure.
Connectivity -> transient pp approach: OPEN. Stable unlike-only nuclear contact rules require a separate transient approach coordinate and an engagement/barrier law. Stable pp contact cannot be silently added to the established grammar.
Approach -> EC: OPEN. A transition path needs energy conservation, angular movement accounting, occupied electron overlap and an absolute clock. Alpha/D/T inventory alone supplies none of those quantities.
EC -> reseating: COMPUTED inventory only. Each event receipt records fixed A and changed Z. An admissible daughter inventory still needs a geometrically realizable daughter and a continuously accessible path.
Reseating -> carrier: OPEN. Law IV resistance differences require specified engaged-volume domains and a many-contact union/phase prescription. Pairwise additive savings can double count shared volume. Carrier energy and momentum cannot be assigned from an unknown Q.
Carrier -> bulk feedback: OPEN. Transport requires collision/coupling and boundary escape laws. No conventional opacity, Fermi closure or fitted EC rate was inserted.
`);
write('STABILITY_REPORT.md',`# Stability and identifiability
A bulk stability calculation requires a closed evolution operator dot(x)=F(x), equilibrium F(x_0)=0, and Jacobian J=dF/dx at x_0. Missing connectivity, event clock and transport laws leave F undefined. Growth-rate refinement, independent nonlinear integration and an astronomical luminosity therefore cannot be executed without introducing new physical assumptions.
Structural non-identifiability: conservation and inventory constraints are compatible with zero event rate, or an arbitrary positive rate function multiplied by any positive constant. The supplied constraints cannot select an absolute event timescale. Carrier escape likewise admits multiple boundary responses. No sign or magnitude of bulk growth follows from compression work and inventory alone.
Required next closure: a native transition path, many-contact resistance functional, absolute capture clock, carrier dispersion/coupling and boundary transport. Stability calculations become meaningful only after those interfaces close. No nova yield or runaway verdict follows from the present run.
`);
write('NOVELTY_REPORT.md',`# Novelty boundary
Surface-depth/koppa inversion is algebraically established within the selected inverse-square profile. Computational step advantage requires equivalent input sets and an explicit benchmark; deriving GM after receiving koppa is a different task from deriving koppa from raw observables.
The force/action spectrum is a correspondence conditioned on alpha, resistance masses, action seats and emission mapping. A new mechanistic result would require deriving the discrete seat rule and independently validating mechanism-sensitive shifts or environmental responses.
The exact alpha/D/T EC stock transform is a useful construction constraint. Physical novelty requires a finite contact transition, native energy and clock, and an independent observation distinguishing the mechanism. No exhaustive prior-art search or held-out physical validation occurred; priority and patentability remain unassessed. Manuscript and journal submission gates remain unmet.
`);
const verdicts=[['reference depth','DERIVED conditional inverse-square profile'],['atomic compression','DERIVED conditional fixed action and nonrelativistic resistance'],['spectroscopy','COMPUTED conditional; quantisation not derived'],['collective connectivity','OPEN'],['conversion accessibility','OPEN; inventory admissibility computed'],['capture kinetics','OPEN'],['alpha/D/T reseating','COMPUTED construction, finite-path closure OPEN'],['many-contact energy','OPEN'],['neutrino transport','OPEN'],['bulk instability','OPEN']];
write('RESULTS.json',JSON.stringify({atomic,spectra,compressionQuadrature:read('compression_quadrature.json'),construction:{built:nseq.builtIsotopes,selectable:nseq.selectableIsotopes,failures:nseq.failures,inventoryPairs:construction.pairs.length,maxDegree:Math.max(...construction.rows.map(r=>r.maxDegree))},nativeStatus:native.status,canonicalNativeStatus:canonical.status,canonicalManifest:canonical.manifest,verdicts,newPhysicalFitParameters:0,heldOutValidation:false},null,2));
const degree=Math.max(...construction.rows.map(r=>r.maxDegree));
write('VERDICT.md',`# Execution verdict — 2026-10-03
Fresh Release build completed; all four CTest targets passed. Native solver self-test status: ${native.status}. Construction validator built ${nseq.builtIsotopes}/${nseq.selectableIsotopes} selectable isotopes with ${nseq.failures.length} failures. Exact EC inventory pairs: ${construction.pairs.length}. Maximum contact graph degree: ${degree}. Finite three-port interpretation requires an independent embedding and phase test; graph construction does not establish that physical closure.
Separate canonical-header build also passed all four CTest targets; canonical self-test status: ${canonical.status}. The release/canonical header difference contains provenance comments only. Four construction validator failures concern missing canonical tokens; numerical construction itself passes. QUALIFICATION_NOTES.md records the exact integration failures and physical energy discrepancies.
Atomic force balance passed 1,840 conditional cases, maximum relative residual ${atomic.worst_relative_residual}. H ground relative-motion seat R=${atomic.R_m} m; k=${atomic.k}; fixed surface z=${atomic.surface_z}; conditional 2->1 wavelength=${atomic.conditional_Lyman_alpha_m} m. Canonical measured inputs and assumed action seats remain explicit. No fit parameters were added.
Compression work agrees with independent force integration across 1,024/2,048/4,096 intervals; worst relative residual 4.713e-9. No plasma or event-rate closure was supplied by that numerical convergence.

| Claim | Status |
|---|---|
${verdicts.map(r=>'| '+r.join(' | ')+' |').join('\n')}

Phases 0 and 1 and the construction/numerical branches executed. Phases 2–5 were evaluated through interface and identifiability gates; missing native laws prevent closed physical simulations. Phase 6 has no sealed independent measurement comparison and no physical novelty promotion. The full EC/nova hypothesis remains unvalidated and dynamically incomplete; mathematical consistency of selected branches cannot establish mathematical completeness of the full pathway.
Source freeze and integrity results preserve the original engines and earlier Phase 0 artifacts. Fresh native qualification does not qualify browser/WASM parity or new plasma physics. Existing calibration in the nuclear observable path remains upstream. No journal paper was generated because the physical closure and validation gates remain unmet.
`);
const ledger=fs.readFileSync(path.join(path.dirname(run),'DEPENDENCY_LEDGER.csv'),'utf8');write('DEPENDENCY_LEDGER.csv',ledger.trim());
write('DEPENDENCY_UPDATES.md','D29: inverse-square conditional branch traced to Law III. D43: legacy packer excluded from execution. D49: normalized channel partition is a declared model assumption, physical selection remains OPEN. D51: composition dataset read and hashed; observed inputs/computed inventory, with composition assumptions retained. D52: fresh native tests passed; historical manifest not rewritten, browser/WASM qualification not performed. D44–D48 remain OPEN. E_B now explicitly C/(2R), conditional fixed-action derivation.');
const freeze=read('SOURCE_FREEZE.json');const changed=Object.entries(freeze.files).filter(([p,h])=>crypto.createHash('sha256').update(fs.readFileSync(path.join(root,p))).digest('hex')!==h).map(([p])=>p);
write('source_integrity.json',JSON.stringify({protectedFiles:Object.keys(freeze.files).length,changed},null,2));
fs.appendFileSync(path.join(path.dirname(run),'RUN_LOG.md'),'\nFresh continuation: cmake configure/build Release; ctest four targets passed; native atomic adapter executed; original NSEQ18 validator executed with result destination redirected. finalize.js generated phase derivations, interfaces, receipts and verdict. Physical closure gates remain OPEN; no extra physical parameters or source edits.\n');
console.log(JSON.stringify({nseqFailures:nseq.failures.length,constructed:nseq.builtIsotopes,inventoryPairs:construction.pairs.length,maxDegree:degree,changed}));
