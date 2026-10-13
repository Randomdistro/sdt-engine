> **Frozen specification.** Transcribed verbatim from the Operator's message of 2026-10-03
> ("run this first, tell me if this is a decent investigative format"). The Operator's message is
> the separate execution instruction the specification requires. Execution record: `RUN_LOG.md`.
> The file's sha256 is recorded in `SOURCE_FREEZE.json`. Any change after freezing is an
> `ADJ-###` entry in `RUN_LOG.md`, not an edit here.

# SDT Investigation Prompt: Loading, Electron Confinement, Nuclear Reseating, and Bulk Neutrino Emission

**Status:** SPEC  
**Scope:** Computational investigation and mathematical derivation.  
**Execution authority:** Draft only. Execution requires a separate Operator instruction.  
**Repository:** `C:\Users\Jimmi\OneDrive\Desktop\sdt-engine`  
**Inheritance:** `Investigations/PERFECT_PROMPT_TEMPLATE.md`, `Investigations/PROMPT_EXECUTION_PROTOCOL.md`, and `Investigations/HUNTER_PROTOCOL.md`.  
**Canonical engine:** `Engine/include/sdt/laws.hpp`.  
**Modification boundary:** Preserve canonical laws, source datasets, existing investigations, release packages, and published assets. Place execution artifacts in a new investigation directory after execution authorisation.

## ⓪ Investigation contract

**Unresolved mechanism:** A quantitative SDT coupling from many-body loading and electron confinement through nuclear contact conversion, alpha/deuteron/triton reseating, emission, and macroscopic stability.

**Scientific importance:** The coupling connects existing SDT dynamics and nuclear construction engines. Successful closure would convert a cross-scale construction into a predictive dynamical mechanism.

**Investigation method:** Trace canonical dependencies, derive local response and conversion laws, integrate existing engines, freeze predictions, and compare against independently sourced measurements.

**Principal falsifiers:**

- A required capture rate remains arbitrary or contains an inserted empirical reaction coefficient.
- The proposed transition violates constitutional inventory, contact admissibility, movement budget, or total energy–momentum accounting.
- A predicted instability disappears under numerical refinement or consistent pressure and emission accounting.
- Absolute emission energies require measured nuclear binding energies upstream.
- Distinct microscopic configurations produce indistinguishable model states despite different claimed capture responses.

**Completion condition:** Deliver either a reproducible coupled SDT solution or a precise mathematical identification of the missing closure. Investigation completion and physical validation receive separate verdicts.

## 1. Executive Summary

Derive a continuous SDT mechanism connecting celestial or imposed loading, electron confinement, collective plasma connectivity, proton proximity, electron capture, nuclear reseating, and emission. Reuse the existing arbitrary-N retarded-occlusion solver and alpha/deuteron/triton construction engine. Treat atomic seating, collective electron connectivity, transient proton approach, stable proton–neutron traction, and neutrino propagation as distinct regimes requiring explicit interface laws. Establish forward and reverse dynamics from identical local fundamentals. Determine whether capture relieves local contact overload, reduces macroscopic pressure support, produces a stable restructuring event, or generates a growing instability. Produce absolute rates, energies, spectra, and stability predictions only after native dimensional and dynamical closure. Preserve conditional results when unresolved upstream mechanisms prevent absolute prediction.

## 2. Physical Context

Use the repository’s SDT foundation:

- Matter records configuration, circulation, displacement, and reorganisation.
- Space transmits movement through the relay medium.
- Convergence supplies loading and pressure.
- Energy represents mechanically accounted activity and reorganisation.
- Particle topology and admissible traction constrain nuclear construction.
- Emission transports part of the transition budget away from the material configuration.

Investigate the chain:

```text
Retarded many-body convergence
    → local loading and electron confinement
    → collective electron connectivity
    → transient proton-pair approach
    → proton-form/electron rearrangement
    → admissible proton–neutron construction
    → alpha/deuteron/triton reseating
    → material relaxation and neutrino emission
    → changed pressure support and subsequent loading
```

Investigate the plasma-first route independently:

```text
Ionised electron–proton population
    → externally imposed or convergence-driven compression
    → altered electron–proton and proton–proton correlations
    → local conversion opportunity
    → seated-electron neutron construction
    → stable nuclear assembly and emission
```

“Naked proton” means absence of a bound external atomic electron. Collective plasma electrons remain available.

“Connectivity” requires a defined physical state and measurable response. Electrical conductivity, proximity, graph adjacency, and capture probability remain separate quantities.

“Contact overload” requires a calculated residual between imposed loading and admissible local mechanical response. A verbal overload threshold cannot trigger conversion.

“Corrective conversion” means a dynamically accessible transition reducing a defined mechanical imbalance or total state cost. Purpose, optimisation, and automatic stabilisation cannot substitute for dynamics.

Distinguish transient proton–proton proximity from prohibited stable proton–proton nuclear traction. The nuclear construction engine’s unlike-contact restrictions remain active.

Define every symbol with dimensions and domain:

| Symbol | Meaning |
|---|---|
| \(R\) | Fixed reference boundary length |
| \(r\) | Current electron seat or sampling radius |
| \(k_R\) | Reference-normalised circulation ratio |
| \(z_R\) | Fixed reference depth |
| \(\mathrm{Om}\) | Depth length \(R/k_R^2\) |
| \(z_{\mathrm{loc}}\) | Local radial depth |
| \(Z,A\) | Nuclear charge and baryon inventory |
| \(n_D,n_T\) | Constitutional deuteron/triton counts |
| \(N_e^{\mathrm{ext}},N_e^{\mathrm{seat}}\) | External and seated-electron inventories |
| \(\mathcal R\) | Conversion events per volume per time |
| \(q_\nu\) | Neutrino energy generated per volume per time |

Reserve different symbols for global reference \(k_R\) and the local FLM15 relay-lock ratio.

## 3. Theoretical Framework

### Native dependency boundary

Derivation inputs may contain:

- Explicit canonical SDT axioms.
- Canonical relay, convergence, displacement, resistance, circulation, and topology relations.
- Declared primitive scales and unit bridges.
- Measured initial conditions, geometry, composition, and boundary conditions.
- Numerical algorithms implementing the declared mechanics.

Classify each dependency individually. Namespace membership does not establish derivation status.

Disclose the supplied mass/action seat, atomic seats, spectroscopic anchors, convergence boundary, and stored numerical scales. A result dependent on a measured seat remains conditional on the supplied seat.

Exclude load-bearing importation of:

- \(G\), fitted \(GM\), or conventional gravitational mass as a replacement for native loading.
- Coulomb coefficients inserted to recover atomic retention.
- Schrödinger or Dirac wavefunctions.
- Fermi-pressure formulas inserted as the plasma closure.
- Weak-interaction constants, empirical capture cross-sections, or fitted reaction-rate coefficients.
- Measured binding energies inserted into predicted conversion energies.
- Rydberg formulas inserted into predicted emission wavelengths.
- Conventional transport opacities inserted into predicted neutrino escape.

External theories may enter post-seal comparisons. Mathematical techniques remain available when supported by native mechanical definitions.

### Reference-depth structure

Use the proposed reference relation:

\[
k_R=\frac{c}{v(r)}\sqrt{\frac Rr},
\qquad
z_R=\frac1{k_R^2},
\qquad
\mathrm{Om}=z_RR.
\]

For an admissible equilibrium regime satisfying \(v^2r=\text{constant}\),

\[
v^2(r)=\frac{c^2\mathrm{Om}}r,
\qquad
a_{\mathrm{seat}}(r)=\frac{c^2\mathrm{Om}}{r^2},
\qquad
z_{\mathrm{loc}}(r)=\frac{\mathrm{Om}}r.
\]

Establish the regime through the SDT force and response laws. The reference relation alone cannot derive inverse-square mechanics.

Retain \(z_R=\Delta\lambda/\lambda\) as a separate spectroscopic hypothesis. Specify the reference wavelength and derive the wavelength transformation before asserting equality with a measured fractional shift.

### Compression and emission candidates

Audit the preceding conditional candidates:

\[
W_{\mathrm{compression}}
=E_B\left(\frac Rr-1\right)^2,
\]

\[
\lambda
=4\pi k_R\frac{r_lr_u}{r_u-r_l}.
\]

Derive the necessary assumptions from native mechanics. Explicitly establish action closure, allowable seats, circulation response, binding-energy accounting, and emission conversion.

Treat the formulas as low-speed candidate relations until the Law-V movement budget establishes a wider domain. Algebraic light-speed limits do not authorise divergent or superluminal physical states.

### Nuclear inventory

For the admissible alpha-core branch,

\[
X=\alpha+n_DD+n_TT,
\]

\[
n_D=3Z-A-2,\qquad n_T=A-2Z.
\]

At fixed \(A\), EC produces

\[
\Delta Z=-1,\qquad
\Delta n_D=-3,\qquad
\Delta n_T=+2.
\]

Use

\[
3D+e^-\rightarrow2T+\nu_e
\]

as a net constitutional receipt. Derive actual nucleon mappings and mechanical paths separately. Handle light nuclei, alternative core branches, and negative grammar counts explicitly.

Maintain separate accounting for external electrons, seated electrons, nuclear proton/neutron labels, and emitted carrier inventory. Prevent double counting of seated-electron contributions in composite resistance and energy.

## 4. Investigation Strategy

### Phase 0 — Source freeze and dependency audit

**Goal:** Establish the exact executable baseline.

Read primary code before assessments. Record existing target exposure; historical knowledge cannot become a retrospectively blind experiment.

Inspect:

- `Engine/include/sdt/laws.hpp`.
- `Release/SDT_Celestial_Three_Body_Solver/src/occlusion_nbody.cpp`.
- `Release/SDT_Celestial_Three_Body_Solver/src/solver.cpp`.
- `Release/SDT_Celestial_Three_Body_Solver/QUALIFICATION_MANIFEST.json`.
- `Release/HTML_SDT_Website/js/traction-gear-engine.js`.
- `Investigations/05_Nuclear_Physics/pack_nucleus.py`.
- NSEQ16, NSEQ17, NSEQ18, NP33, NP04, FLM15, and relevant particle/emission sources.

Record commit, dirty-tree state, hashes, toolchains, source provenance, and qualification currency.

Construct a directed dependency ledger with classifications:

`AXIOM`, `DERIVED`, `COMPUTED`, `MEASURED_SEAT`, `OBSERVED`, `CALIBRATED(n)`, `CONSTRUCTION`, `OPEN`, `EXCLUDED`.

**Gate:** Zero unclassified load-bearing dependencies. Zero silently inherited numerical constants.

**Planning allowance:** 2–4 hours. Re-estimate after inventory.

**Excluded:** Canonical repair, data migration, scientific promotion.

### Phase 1 — Reference depth, atomic seat, compression, and emission

**Goal:** Derive a consistent native atomic energy and response model.

Separate:

1. Unconstrained circular equilibrium.
2. Fixed-action compression.
3. Electron liberation.
4. Collective electron confinement.
5. Emission during permitted relaxation.

Derive force and reorganisation work from Laws III–V. Establish whether angular action remains fixed, changes through exchange, or ceases to describe the state.

Calculate imposed work, material activity, relay exchange, and emitted energy without counting a contribution twice.

Derive reference-depth and local-depth behaviour independently. Establish whether the atomic depth length and celestial depth length share a derived amplitude mechanism.

Reconstruct the candidate wavelength formula from native circulation closure. Distinguish photon wavelength, orbital circumference, emission duration, and total packet length.

Check H, D, T, He⁺, and selected hydrogenlike ions using measured comparison data only after sealing. Extend isotope scaling through the derived response law; do not insert a reduced-mass correction as an unexplained coefficient.

**Gate:** Numerical recovery of any proven limiting identity within \(10^{-10}\) relative error; native work–energy agreement within \(10^{-6}\) after refinement. Spectral agreement receives a separate uncertainty-based verdict.

**Planning allowance:** 1–3 days; derivation dependencies may extend duration.

**Excluded:** Assumed nuclear conversion, borrowed quantisation, high-speed extrapolation.

### Phase 2 — Plasma connectivity and transient contact loading

**Goal:** Define a calculable collective electron state and overload variable.

Construct electron connectivity from SDT circulation, relay response, phase relations, and accessible proton configurations.

For every proposed connectivity measure, specify:

- Physical carriers.
- Spatial and temporal support.
- Units.
- Evolution law.
- Relationship to proton loading.
- Dependence on electron removal and reseating.
- Independent observables.

Calculate proton-pair approach statistics and electron availability from the native population dynamics. Include screening only through a derived relay-response mechanism.

Define overload as a signed force, traction, circulation, or reorganisation residual. Compare configurations with identical scalar density but different phases and local geometry.

Use the arbitrary-N solver for loading where the existing force model applies. Derive any microscopic extension or coarse-graining rule. Do not assume celestial qualification certifies nuclear contact dynamics.

**Gate:** Connectivity and overload must remain calculable without capture targets. Homogeneous, dilute, disconnected, and electron-depleted controls must match derived limiting behaviour.

**Planning allowance:** 2–5 days.

**Excluded:** Density-only capture triggers, fitted pressure thresholds, conductive-state identification as EC.

### Phase 3 — Electron capture and admissible nuclear construction

**Goal:** Derive an actual local conversion event.

Begin with isolated proton/electron configurations and two-proton/electron configurations. Track seated-electron formation, circulation redistribution, neutron construction, and emerging proton–neutron traction.

Distinguish:

\[
p+e^-\rightarrow n+\nu_e
\]

from

\[
p+p+e^-\rightarrow d+\nu_e.
\]

Derive accessibility and energy budgets independently. A favourable final energy does not establish a conversion rate.

For nuclear EC:

- Identify participating nucleons and electron configuration.
- Produce an explicit inventory mapping.
- Construct an admissible transition path.
- Verify geometry before and after conversion.
- Verify transient and final contact rules separately.
- Apply the constitutional \(3D\mapsto2T\) receipt where admissible.
- Calculate reseating, completed-shell contraction, and reverse feasibility.

Retain finite nucleon geometry. Check body-local contact capacity, port orientation, phase, occupancy, loop compatibility, slip, and unlisted collisions. A connected bipartite graph alone cannot certify full physical traction.

If the contact law requires three oriented ports, enforce the declared port limit. Report incompatible existing exports without pruning edges to manufacture compliance.

Derive the event clock or capture hazard from native dynamics. Determine whether stochastic behaviour emerges from resolved phase distributions or requires an additional axiom.

**Gate:** Exact integer inventory closure; normalized contact slip below \(10^{-10}\); declared port constraints satisfied; no prohibited final like-contact; no arbitrary dimensional rate multiplier.

**Planning allowance:** 3–7 days, followed by dependency-based re-estimation.

**Excluded:** Treating graph rewrites as reaction kinetics, summing isolated module binding energies without a many-contact law.

### Phase 4 — Many-contact energy, emission, and reverse response

**Goal:** Close the complete conversion budget.

Evaluate applicable native candidates:

- Law-IV reorganisation resistance.
- FLM15 engaged-volume and coherent-union relations.
- Circulation-frequency changes.
- Derived pressure work.
- Native wake-flow exchange.

For example, audit applicability of

\[
\Delta E_{\mathrm{reorg}}
=\frac{P_{\mathrm{conv}}}{3}
\left(V_{\mathrm{joint}}-\sum_jV_j\right).
\]

Derive participating domains and mechanical boundaries independently. A measured mass defect cannot determine the domains later compared with the mass defect.

Separate material relaxation, photon emission, neutrino emission, recoil, relay exchange, and stored strain.

Derive the neutrino carrier from the applicable SDT topology and propagation rules. Establish energy, momentum, angular response, and coupling. If the neutrino mechanism remains unresolved, retain a symbolic emitted-carrier budget and mark neutrino-specific predictions `OPEN`.

Derive reverse response using identical local laws:

- Material re-expansion.
- Electron release from seated configurations.
- Neutron-to-proton reconstruction.
- Deuteron breakup.
- Incident-carrier-assisted reverse conversion.

Enforce total material-plus-medium accounting. Retarded interactions may store momentum and activity in the relay medium; instantaneous pair-force balance cannot replace the complete ledger.

**Gate:** Closed-domain energy and momentum residuals below \(10^{-6}\), decreasing under refinement. Forward/reverse budgets close without independent fitted constants.

**Planning allowance:** 3–7 days.

**Excluded:** Inserted \(Q\)-values, borrowed weak amplitudes, assumed neutrino opacity.

### Phase 5 — Bulk feedback, stability, and astronomical consequences

**Goal:** Determine the macroscopic response.

Derive bulk equations from resolved event dynamics or a demonstrated coarse-graining limit.

At minimum, evolve:

- Proton, neutron, deuteron, triton, alpha, and relevant nuclear populations.
- External and seated-electron populations.
- Loading and pressure support.
- Circulation and thermal activity.
- Relay-medium exchange.
- Emission generation, absorption, and escape.

Calculate pressure from the native state response. Identify the required derivative under the declared thermal and boundary conditions.

Compare:

- Closed fixed-volume sample.
- Imposed-pressure sample.
- Prescribed compression trajectory.
- Native convergence-loaded configuration.
- Carrier-transparent and carrier-retaining limits, when derivable.

Perturb an equilibrium state and calculate the linear response operator,

\[
\delta\dot{\mathbf X}=J\,\delta\mathbf X.
\]

A growing mode requires a positive growth exponent stable under timestep, spatial, and population refinement. Confirm the mode with nonlinear evolution.

Classify the outcome as stable restructuring, cooling, oscillation, contraction, or explosive instability. Reserve “nova pathway” for a quantitatively defined event matching the relevant observable class.

**Gate:** Growth rate changes below 5% across three refinement levels; independent integrations agree within the declared error budget; nonlinear evolution reproduces the predicted stability sign.

**Planning allowance:** 3–7 days after local closure.

**Excluded:** Invented luminosities, assumed runaway, deployment or hardware proposals.

### Phase 6 — Held-out validation and novelty assessment

**Goal:** Separate new mechanism from correspondence.

Freeze model outputs before opening selected held-out measurements. Include historical target-awareness records.

Compare:

- Atomic transition wavelengths and isotope shifts.
- Nuclear binding differences and construction-sensitive observables.
- EC dependence on electron occupancy and environment.
- Carrier energy distributions.
- Bulk thermal and mechanical response.
- Applicable celestial loading observations.

Where measured neutrino flavour fluxes require a propagation interpretation, preserve raw detector observables and identify every conversion dependency.

Use external theories only after the native prediction seal. Compare equivalent tasks and inputs for computational-step claims, runtime, conditioning, uncertainty, and explanatory reach.

**Gate:** At least one independent mechanism-sensitive prediction must discriminate the SDT model from established alternatives before asserting new physical validation.

**Planning allowance:** 2–5 days.

**Excluded:** Retrospective blindness, literature absence as proof of novelty.

## 5. Success Criteria

Report separate verdicts for every claimed closure:

1. Reference-depth geometry.
2. Atomic seating and compression.
3. Spectroscopic emission.
4. Collective electron connectivity.
5. Nuclear conversion accessibility.
6. Capture kinetics.
7. Alpha/deuteron/triton reseating.
8. Many-contact energy.
9. Neutrino carrier and transport.
10. Bulk instability.

**DERIVED:** Every load-bearing relation follows from declared SDT fundamentals, with dimensional and dynamical closure.

**COMPUTED:** A fully specified native model executes and converges; physical interpretation remains conditional.

**CONVERGENCE:** A sealed independent prediction agrees with an independently measured observable within the combined error budget.

**CALIBRATED:** Existing calibration remains explicitly identified. Calibration cannot support zero-parameter promotion.

**OPEN:** A necessary mechanism, scale, boundary, or response remains unspecified.

**EXCLUDED:** A particular proposed mechanism fails a committed gate.

Numerical pass does not promote upstream physical status. Construction success does not establish energy or kinetics. Accurate energy does not establish capture rate. Capture events do not establish explosive instability.

For measured comparisons, record

\[
r_j=
\frac{y_{\mathrm{pred},j}-y_{\mathrm{obs},j}}
{\sqrt{\sigma_{\mathrm{pred},j}^2+\sigma_{\mathrm{obs},j}^2}}.
\]

Use \(|r_j|\le3\) as a screening criterion where uncertainties are available. Preserve correlated errors and systematic trends. Missing uncertainty prevents precision-validation claims.

## 6. Outputs

Proposed execution directory:

`Investigations/SDT_Loading_EC_Reseating_Neutrino_Coupling/`

Produce:

- `PROMPT.md` — frozen investigation specification.
- `RUN_LOG.md` — append-only commitments, commands, adjustments, and outcomes.
- `SOURCE_FREEZE.json` — checkout, hashes, dirty-state inventory, toolchains.
- `DEPENDENCY_LEDGER.csv` — every load-bearing quantity and provenance class.
- `STATE_AND_UNITS.md` — state definitions, frames, units, boundaries, and domains.
- `DERIVATION.md` — complete native derivation and conditional branches.
- `MECHANISM_INTERFACES.md` — loading, connectivity, capture, reseating, and transport interfaces.
- `sdt_ec_coupling.cpp` — minimal native implementation using existing engines.
- `CONTACT_AUDIT.csv` — ports, phases, contacts, clearance, and slip.
- `EVENT_LEDGER.csv` — constitutional mappings and conversion budgets.
- `RESULTS.json` — predictions, numerical uncertainty, provenance, and status.
- `VALIDATION.csv` — sealed predictions against held-out measurements.
- `STABILITY_REPORT.md` — equilibrium, growth modes, and nonlinear response.
- `NOVELTY_REPORT.md` — mathematical equivalence, mechanism differences, and prior art.
- `VERDICT.md` — investigation completion and physical-status verdicts.

Produce a manuscript only after the applicable claim gates pass. Potential venues: *Physical Review C* for nuclear conversion, *Physical Review E* for collective dynamics, *The Astrophysical Journal* for validated astronomical consequences, or *Computer Physics Communications* for a validated computational method.

## 7. Dependencies & References

Mandatory primary repository sources:

- `Engine/include/sdt/laws.hpp`.
- `Investigations/HUNTER_PROTOCOL.md`.
- `Investigations/PROMPT_EXECUTION_PROTOCOL.md`.
- `Investigations/PERFECT_PROMPT_TEMPLATE.md`.
- `Release/SDT_Celestial_Three_Body_Solver/`.
- `Release/HTML_SDT_Website/js/traction-gear-engine.js`.
- `Investigations/05_Nuclear_Physics/NSEQ16_Perfect_Traction_Gear_Engine/`.
- `Investigations/05_Nuclear_Physics/NSEQ17_Light_Nucleus_Wake_Mesh/`.
- `Investigations/05_Nuclear_Physics/NSEQ18_Universal_Interstitial_Sequencer/`.
- `Investigations/05_Nuclear_Physics/NP33_Traction_Assembly/`.
- `Investigations/05_Nuclear_Physics/NP04_Neutron_Genesis_to_Tritium/`.
- `Investigations/01_Foundations_and_Lattice_Mechanics/FLM15_Influx_Phase_Resistance_Ratio/`.
- Applicable particle, emission, and neutrino investigations.
- `Audits/atomica_n82_fission_stocktake.md`.

Resolve conflicting historical and current statements through explicit source genealogy. Preserve superseded routes as historical records.

Acquire measured validation data from primary experimental publications, NIST, evaluated nuclear-data sources, and original astronomical datasets. Record extraction method, experimental uncertainty, model-dependent processing, and independence from the prediction.

## 8. Falsification Tests

| Test | Required outcome | Failure interpretation |
|---|---|---|
| Target deletion | Native prediction executes after comparison tables are removed | Hidden empirical dependency |
| Dimensional closure | Every equation has exact dimensional consistency | Incomplete scale or incorrect relation |
| Contact admissibility | Complete geometry satisfies declared contact and port restrictions | Constructed graph lacks physical realisation |
| Compression balance | Input work, state change, and emitted exchange close | Missing confinement or duplicated energy |
| EC receipt | Exact constitutional and carrier inventory closure | Invalid conversion mapping |
| Rate closure | Absolute clock follows native dynamics | Kinetics remains unspecified |
| Reverse response | Identical laws produce consistent reverse accessibility | Asymmetric inserted reaction rule |
| Neutrino identity | Derived carrier supports predicted energy and transport | Emission budget lacks neutrino mechanism |
| Bulk stability | Growth survives refinement and complete pressure accounting | Numerical or bookkeeping instability |
| Held-out prediction | Independent observable matches committed uncertainty criterion | Proposed model lacks demonstrated predictive validity |

A failed mechanism branch does not exclude SDT generally. An unresolved branch cannot support a completed parent claim.

## 9. Implementation Notes

Preserve original architecture. Add adapters around existing engines rather than replacing native implementations.

Use exact integers for constitutional inventory. Use explicit units and frame labels for continuous quantities. Normalise lengths and times before resolving atomic-to-celestial scale differences.

Separate numerical controls from physics gates. Use meaningful conservation, limiting-case, refinement, event, and reverse-response tests.

Prevent:

- Negative radii or populations.
- Division by zero.
- Undefined zero-reference percentage errors.
- Nonfinite pass values.
- Negative real square-root arguments.
- Unclassified speed-limit crossings.
- Invalid grammar branches.
- Event steps violating movement-budget domains.
- Double-counted seated electrons.
- Double-counted coherent overlap.
- Unrecorded relay-medium energy or momentum.

Use event-aware integration for topology changes. Compare independent integration methods where compatible with the retarded dynamics.

Record physical units and significance of every source quantity described as greater than \(c\). Distinguish circulation bookkeeping, pattern propagation, and transport. A label cannot resolve a movement-budget violation.

Use hierarchy or coarse-graining only after demonstrating preservation of local response, conservation, and conversion statistics.

Existing qualification manifests establish historical evidence. Verify current source hashes before associating historical runtime results with current code.

## ⑩ Adaptive Execution Protocol

### Pre-run commitment block

Copy the following block into `RUN_LOG.md` before implementation:

```text
Investigation:
SDT_Loading_EC_Reseating_Neutrino_Coupling

Primary hypothesis:
A native SDT response law couples loading and electron connectivity
to admissible nuclear conversion, reseating, and carrier emission.

New fitted-parameter budget:
0.

Existing calibration:
List every inherited calibrated parameter and every affected prediction.

Canonical-source modifications:
0.

Source-data modifications:
0.

Unclassified load-bearing dependencies:
0.

Inventory residual:
Exactly 0.

Contact-slip tolerance:
1e-10, normalised.

Analytic limiting-identity tolerance:
1e-10 relative, with an explicit absolute tolerance near zero.

Closed-domain energy and momentum residual:
1e-6 or smaller, decreasing under refinement.

Stability-growth convergence:
Less than 5% change across three refinement levels.

Measured comparison:
Combined-uncertainty residual, with correlations and systematic errors retained.

Capture-rate gate:
No empirical dimensional rate multiplier.

Blindness:
Declare historical target exposure.
Seal new hold-out predictions before comparison access.

Parent-claim gate:
No full coupling verdict while a necessary mechanism remains OPEN.

Forbidden adjustments:
Target tuning, tolerance widening, inserted rate constants,
measured binding-energy substitution, edge pruning,
silent state redefinition, and retrospective blindness.
```

### Committed pivot table

| Trigger | Permitted response | Endpoint after unsuccessful response |
|---|---|---|
| Numerical conservation residual above \(10^{-6}\) | Refine integration, quadrature, history, and event handling | `OPEN` numerical implementation |
| Missing absolute capture clock | Search declared native phase and relay response routes | `OPEN` capture kinetics |
| Inadmissible contact geometry | Recompute admissible poses under unchanged port constraints | `EXCLUDED` construction branch |
| Binding mismatch | Revisit native many-contact domain and synchrony derivation | `OPEN` energy closure |
| Movement-budget domain crossing | Apply a derived canonical extension or terminate the branch | `OPEN` high-speed regime |
| Instability vanishes under refinement | Correct numerical or budget error | `EXCLUDED` instability claim |
| Fractional-shift interpretation conflicts with spectral baseline | Separate reference depth from transition wavelength | `OPEN` spectral-shift coupling |
| Neutrino carrier lacks derivation | Retain a symbolic carrier budget | `OPEN` neutrino prediction |
| Held-out measurement exceeds committed uncertainty | Diagnose dependency or mechanism failure without target adjustment | `EXCLUDED` validated claim |

Each adjustment requires a dated `ADJ-###` entry containing the trigger, changed method, unchanged target, affected claims, and rerun evidence.

Continue independent branches after an upstream `OPEN` only with explicit conditional status. Complete the investigation with a precise dependency map even when full physical closure remains unavailable.

**Final deliverable:** A reproducible derivation identifying the solved mechanism, the discriminating prediction, and the exact remaining closure—without promoting construction, calibration, or algebraic correspondence into independent physical validation.
