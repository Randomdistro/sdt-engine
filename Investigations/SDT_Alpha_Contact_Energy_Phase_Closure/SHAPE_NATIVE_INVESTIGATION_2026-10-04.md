# Shape-native contraction, conserved tube volume, and nuclear contact investigation

## Authoritative operator specification

Treat the following construction as the physical geometry specification, rather than replacing the construction with a familiar torus-knot label.

One continuous strand follows six windings. Winding 1 passes over; winding 2 passes under; winding 3 passes over. Winding 4 returns to the position of winding 1, passes under and outside winding 1. Winding 5 passes over and inside/through winding 2. Winding 6 passes under and outside winding 3, closing at the starting point. Preserve both crossing order and inside/outside routing. A crossing word without routing and strand orientation is insufficient for numerical reconstruction.

Under rotation and diagonal contraction across the windings, the central crossing region widens and the structure assumes four continuous loops. Each loop performs one complete barrel roll, one poloidal traversal, and one extreme traversal. Preserve “extreme traversal” as operator terminology until a geometric observable is identified. Three hard-point knits occur at crossing-direction changes associated with contraction and rotation. Static winding structure is a physical definition; a coefficient substitution in a different parametrisation cannot disprove the construction.

Corrected speed record: 0.395c, characteristic approximately 1.84c, and 2.23c. Preserve the earlier 1.83c characteristic record separately. Do not assume “median” means arithmetic mean, phase median, arclength median, time median, or RMS. Compute all relevant statistics after a velocity field exists. The corrected endpoints supersede the recalled 0.355c and 2.7–2.9c endpoints.

Optional volume mechanism: a tube whose diameter equals point-electron diameter follows a Möbius closure; contraction to the four-tour length conserves volume. Proton multiplier is exactly 1836 for the requested branch. Neutron multiplier is exactly 1387 for the requested branch. Preserve 1387 without substitution by a mass ratio. Multipliers are declared hypotheses, not derived results.

## Scope and source protection

Use SDT fundamentals and repository-native mechanisms. External measurements serve as comparison targets with explicit input dependencies. Do not introduce an elastic potential, quantum Hamiltonian, relativistic contraction rule, contact law, phase clock, or fitted coefficient as an undisclosed closure.

Preserve canonical source files, previous run outputs, unrelated working-tree changes, and source provenance. New calculation artifacts belong in a separate shape-native run directory. The companion checkout is C:/Users/Jimmi/Spatial_Displacement_Theory, verified by the Randomdistro/Spatial_Displacement_Theory Git remote. Record both revisions and hashes of consumed sources. No publication or outward communication is authorised.

Primary sources: Engine/include/sdt/laws.hpp; Release/HTML_SDT_Website/js/traction-gear-engine.js; companion SDT/Code/trefoil_proton_engine.cpp; companion SDT/SDT_CANONICAL_PHYSICS_ENGINE_v4.md; companion ex_parte/06_nuclear_physics_foundation.md and 07_multi_ai_nuclear_calculator.md. Follow referenced geometry documents and implementations before declaring a missing mechanism. Distinguish the native (2,3), H1 (4,3), and NSEQ16 (4,5) controls from a verified reconstruction of the operator construction.

## Stage 1: crossing receipt and shape identity

Build a directed strand ledger with winding indices, endpoints, crossings, over/under signs, local tangent orientation, outside/inside nesting, closure seam, and material identity. Recover all possible embeddings consistent with the specified receipt; mark any remaining embedding choices as unresolved rather than selecting a convenient knot. Separate projected crossings from physical contact and finite-width penetration.

Construct a continuous family X(s,eta,phi), with strand coordinate s, contraction coordinate eta, and roll phase phi. Validate positional closure, tangent closure, frame closure, winding receipt, and finite-width clearance at every contraction stage. Preserve knot type under continuous non-intersecting deformation; a topology change requires a specified reconnection or actual crossing event. Distinguish four visible lobes, four major tours, four local barrel rolls, and four globally counted poloidal traversals. Compute counts using physical angles and transported frames; report frame holonomy separately. Do not silently identify twist, writhe, linking number, winding number, or apparent strand count.

Evaluate strand continuity and topology independently of dynamics. A shape family can establish geometric feasibility without deriving the contraction force. A dynamic proof requires a force/resistance law, boundary conditions, and an evolution solution.

## Stage 2: conserved-volume thickness

Let d_e denote physical point-electron diameter, L_e the declared initial closure length, L_4 the actual total four-tour strand length, and N the multiplier. For a circular, constant-area tube under accumulated-length accounting:

V_e = pi*d_e^2*L_e/4; V_N = N*V_e; d_N = d_e*sqrt(N*L_e/L_4).

Use four times the per-tour length only when L_4 has not already counted four tours. Multiplying length and multiplier twice is prohibited. The formula gives an equivalent circular diameter; a Möbius ribbon additionally requires width and thickness or an explicitly derived cross-section.

Native source declares r_electron_body_open=3e-20 m as a radius, yielding conditional d_e=6e-20 m. Keep a second explicitly labelled interpretation d_e=3e-20 m for sensitivity only. Neither branch substitutes classical electron radius, wake radius, or exclusion radius. Native orientation closure length is 4*pi*a0. A Möbius orientation closure can traverse the same spatial centreline twice; distinguish orientation traversal volume from simultaneous physical union. Compute both accounting branches without silently selecting physical union semantics.

For variable thickness, integrate A(s) ds = V_N. Constant volume alone supplies one integral constraint and does not determine A(s), local stretching, or speed. A material-volume-conserving map requires A(s,t)*|partial_s X(s,t)| = A_initial(s)*|partial_s X_initial(s)|, with a fixed material label and specified initial area distribution. Derive any speed-to-thickness relation from flux continuity and the relevant material flow, rather than assuming A*v constant for a phase pattern.

Evaluate Np=1836 and Nn=1387 separately. At equal initial diameter and closure length, dn/dp=sqrt((1387/1836)*(L4p/L4n)). The equal-length ratio is sqrt(1387/1836). Report geometric packing, overlap, self-contact, union volume, swept volume, and engagement/displacement volume as different quantities. Include tube curvature and nonlocal clearance bounds before promoting pi*b^2*L to a physical union calculation. Track packing fraction only if independently supplied or derived.

## Stage 3: phase, contraction, and speed

Evaluate v = X_s*sdot + X_eta*etadot + X_phi*phidot, with separate material transport, contraction, and roll contributions. Identify the observable represented by each repository speed. Derive accelerations with all mixed derivative terms, not merely v^2/r on a noncircular moving path. Compute pressure/traction work using the same geometry and velocity field.

Compare the corrected three-speed record against the actual spatial profile and its extrema, time and arclength distributions, mean, median, RMS, and signed components. Record whether each value is an input, geometric result, fitted target, or independent prediction. The companion scalar sinuation model uses measured magnetic moment to obtain charge angular rate and scans aspect ratio toward 1.836c; reproduction is a control, not an independent speed derivation. The formula (3/2)^(3/2)c gives 1.8371173c but requires a mechanism connecting phase ratio to the spatial velocity field.

Retain the earlier static trefoil max/min ratio 1.76904456 only as a constant-parameter-rate control. No universal restriction on the specified double-trefoil geometry follows. Test SDT velocity budgets only after identifying the physical channel and reference frame.

## Stage 4: hard-point knits and complementary interleaving

Identify three physical knit regions from the continuous finite-width geometry and changes in traction/crossing direction. Threefold symmetry alone does not establish three contacts. Calculate centreline separation, closest surface points, normals, tangent velocities, and phase-relative clearance across an entire cycle. Determine whether contact is permanent, intermittent, rolling, sliding, or purely projected. Integrate phase-resolved traction without replacing a tube by a spherical rim.

For complementary tori, search relative pose and phase using fixed geometry and volume-derived widths. Separate geometric access from dynamical capture. Build proton-electron and neutron-electron branches with explicitly distinct connectivity, seat, flow, and resistance structures. Compute perturbation responses and restoring rates; a visually interleaved configuration is not a stability solution. Electron retention, proton fielding, and neutron stabling require definitions tied to measurable trajectories, work barriers, and phase evolution.

## Stage 5: alpha and isotope continuation

Re-evaluate the four-nucleon alpha using the reconstructed moving shapes. Preserve old spherical and static finite-curve runs as controls. Solve contact graph, three-knit availability, body poses, electron connectivity, and phase synchrony jointly. Compute constraint rank after removing rigid-body gauge; evaluate internal modes using a native restoring law. Derive binding work, magnetic response, and frequency from the same physical state. Do not use separate neutron bases without an explicit state map.

Test deuteron and triton stacking on alpha only after the primitive contact law is established. Carry fixed-A EC inventory changes separately from an event pathway. A valid stoichiometric receipt does not establish capture dynamics, a rate, neutrino energy, or a nova mechanism. Couple bulk electron connectivity to contact forcing and electron reseating using the same phase-resolved geometry, with energy and momentum accounting.

## Stage 6: adversarial checks and deliverables

Use analytic volume identities, independent quadrature, finite-difference derivative checks, and resolution convergence. Confirm no physical constants or target observables were fitted implicitly. Check diameter/radius factors, 360/720-degree closure, per-tour/total-length factors, proton/neutron multipliers, units, coordinate gauges, and material/phase distinctions. Repeat only checks justified by a change or unresolved numerical error.

Deliver a crossing receipt, source ledger, explicit shape family or exact reconstruction dependency, numerical volume/thickness ledger, phase-resolved velocity profile when derivable, knit/contact maps, stability spectrum when a native force law exists, and corrected alpha comparisons. Label every result as geometric identity, declared construction, conditional calculation, numerical verification, or experimentally supported claim. Preserve failed controls with the tested assumptions. Produce a journal manuscript only after independent geometric, dynamic, and observable closure; target selection follows the completed evidence rather than an advance claim of bulletproof science.
