/* Homepage translations for index.html. Consumed by i18n.js.
   Each language maps an exact English text-node → its translation; "@key" holds
   full-HTML for elements carrying data-i18n="key". Visible spine only (nav, hero,
   section titles, Law names, glossary terms); body prose extends here as needed.
   Swiss German (gsw) is a good-faith Zürich-flavoured rendering, not a standard. */
window.SDT_I18N = {

/* ─────────────────────────── TECHNICAL PHYSICS ─────────────────────────── */
"tp": {
  /* ── opening ── */
  "All of physics. No fitted parameters.":
    "A closed axiomatic dynamical system: 9 axioms, 2 lemmas, 18 theorems. Zero adjustable parameters.",
  "Gravity, electromagnetism, the nuclear force — one push, read three ways, in a discrete spatial medium. Four primitives. One new idea: matter displaces space. Every constant computed, nothing fitted.":
    "The gravitational, electromagnetic, and nuclear interactions are one occlusion law, F = (π/4)·P_eff·R₁²R₂²/r² (Theorem T4), evaluated at three cross-section scales in a discrete relay substrate of pitch ℓ_P. declared dependencies: {ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p} plus measured observables. Every quoted constant is computed and carries a certification label: DERIVED · COMPUTED · CALIBRATED · OBSERVED · PENDING.",

  /* ── nav / titles ── */
  "The Medium": "The Relay Substrate",
  "Six Laws": "Laws I–VI",
  "The Six Laws": "The Six Laws — Formal Statements",
  "Topology": "Vortex Topology",
  "What Matter Is": "Topological Classification of Matter",
  "Particle Topology": "Vortex Topology",
  "Cosmology": "Cosmography",
  "Cosmology Without Dark Components": "Cosmography Without a Dark Sector",
  "Experiments": "Falsification",
  "Falsifiable Predictions": "The Falsification Programme",
  "Glossary": "Nomenclature",
  "Atomicus Lab": "Grammar-Space Census Instrument",

  /* ── ch.1 — the medium ── */
  "You are being pressed — right now, from every direction at once.":
    "Every lattice site receives isotropic convergent throughput; the vanishing resultant at equilibrium is a cancellation of magnitude P_conv ≈ 2.459 × 10⁴⁸ Pa, not an absence of interaction.",
  "@m1":
    "Let each point of the substrate receive convergent relay flux from N = R<sub>CMB</sub>/ℓ<sub>P</sub> ≈ 5.894 × 10⁶¹ nested Planck-thick shells. By the Shell Cancellation Identity (T1) the per-shell contribution ε = u<sub>CMB</sub>·ℓ<sub>P</sub>³ is independent of shell radius, so the local burden Φ = Nε ≈ 1.038 × 10⁻⁵⁶ J is isotropic and the resultant vanishes identically. Now introduce a second displacement structure along direction n̂: it subtends occlusion solid angle Ω = πR²/r², attenuating the convergent flux from that bearing. The unoccluded antipodal flux is left unbalanced by exactly the occluded fraction, and the test body accelerates along −n̂, toward the occluder.",
  "You are not attracted. Nothing pulls you. You are pushed — by the pressure the other body fails to block.":
    "No attractive interaction exists in the formalism. The observed force is the unbalanced remainder of isotropic convergent pressure under partial occlusion: F = (π/4)·P_eff·R₁²R₂²/r² (Theorem T4).",
  "@m3":
    "Formally: space is a discrete, gap-free, contact-only relay network — the spation lattice — of pitch ℓ<sub>P</sub> = 1.616 × 10⁻³⁵ m. All propagation is nearest-neighbour transfer at exactly <em>c</em>; no other transport channel exists. Radiation, gravitation, and static fields are distinct angular orders ℓ of one wake field of the same medium (ℓ = 0 monopole occlusion, ℓ = 1 Coulomb, ℓ = 2 magnetic dipole, ℓ ≥ 3 nuclear form factors). Every interaction reduces to a pressure differential.",
  "On foundations": "Axiomatic basis",
  "SDT is built from exactly four irreducible primitives. Everything else — mass, charge, time, temperature, entropy — is derived. The theory makes no claim about what existed before the Clearing, or whether the lattice is finite.":
    "The formalism admits exactly four irreducible primitives; mass, charge, time, temperature, and entropy enter as theorems, not inputs. The system is agnostic on the pre-Clearing state and on lattice finiteness — neither proposition enters any derivation.",
  "@m_space":
    "Gap-free, contact-only relay medium: individually incompressible, collectively deformable. Icosa-dodecahedral close packing at ℓ<sub>P</sub> = 1.616 × 10⁻³⁵ m — Axiom R1, the single irreducible dimensional seed (FLM06 Seed Theorem: exactly one action/mass/length anchor is unavoidable).",
  "Knots wound tight in the medium — persistent vortex structures that crush the space they displace. What we call particles.":
    "Persistent topological defects: torus-knot circulation states excluding volume V_disp from the substrate. Particle identity is fixed by winding number W (Theorem T18).",
  "@m_move":
    "Nearest-neighbour transfer at exactly <em>c</em>. Every bound structure circulates internally at <em>c</em>; translation debits circulation through the budget constraint v<sub>circ</sub>² + v<sub>trans</sub>² = c² (T10).",
  "Not a moment — the plane of existence itself, with everything inside it moving, always moving. What we call time is the tally that movement keeps; there is no arrow to explain, because un-happening is not an operation the relay has.":
    "Not a coordinate instant: the plane of existence itself, with every structure in continuous motion within it. Time is the ordinal tally that movement keeps — the count of relay ticks, everywhere and simultaneously — and the thermodynamic arrow requires no separate explanation: un-happening is not an operation the relay possesses.",
  "@m_note":
    "declared external dependencies — the complete derivation basis: {ℓ<sub>P</sub>, c, ℏ, k<sub>B</sub>, T<sub>CMB</sub>, α, m<sub>e</sub>, m<sub>p</sub>} plus directly measured observables in their measured units. A quantity absent from this set is not an admissible input. Every load-bearing constant carries provenance metadata: certification class A–F, delete-test assertion, risk flag.",

  /* ── ch.2 — the five laws ── */
  "Every prediction flows from these six principles. No additional postulates.":
    "Laws I–VI generate the complete observable content: 9 axioms → 2 lemmas → 18 theorems. No auxiliary postulate enters any downstream derivation.",
  "Cosmological Relay Throughput": "Cosmological Relay Throughput (Axioms R1–R6, Theorems T1–T2)",
  "Vortex Topology Quantisation": "Vortex Topology Quantisation (Theorem T18; PPT09, class A)",
  "The Release Cascade": "The Release Cascade (Corollaries of Law I)",
  "The Occlusion Force": "Convergent Boundary Pressure — the Occlusion Force (Theorems T3–T4)",
  "Inertial Mass": "Inertial Mass as Reorganisation Cost (Theorems T5–T7)",
  "The Movement Budget": "The Movement Budget (Axioms M1–M3, Theorems T10–T17)",
  "Every point in space receives convergent energy from N ≈ 5.89 × 10⁶¹ nested Planck-thick shells stretching to the Clearing. Each shell contributes exactly ε regardless of distance — the Shell Cancellation Identity. The total convergence burden:":
    "Each point receives convergent relay energy from N = R_CMB/ℓ_P = 5.894 × 10⁶¹ nested Planck-thick shells. The Shell Cancellation Identity (T1) renders the per-shell contribution ε = u_CMB·ℓ_P³ = 1.761 × 10⁻¹¹⁸ J independent of shell radius; Theorem T2 then fixes the total burden:",
  "@l1b":
    "Convergence pressure P<sub>conv</sub> = Φ/ℓ<sub>P</sub>³ = N·u<sub>CMB</sub> = 2.459 × 10⁴⁸ Pa. The boundary source count S = 4πN² = 4.366 × 10¹²⁴ closes the 10¹²³ vacuum-energy discrepancy as a shell-counting artefact. The resultant vanishes identically at equilibrium — isotropic cancellation, not absence.",
  "The Clearing — the epoch when every spation released its deformation content simultaneously — created the cosmic microwave background as a baseline operating pressure. The CMB at 2.7255 K is not a distant relic cooling from a primordial fireball. It is the current operating pressure of the universe. Stars are convergence processors — pressure-processing nodes in the lattice, not isolated furnaces.":
    "At the Clearing every spation discharged its held deformation content simultaneously and omnidirectionally. The CMB is the present baseline operating pressure of the lattice, not a cooling relic: u_CMB = a·T⁴_CMB = 4.172 × 10⁻¹⁴ J/m³, P = u/3 = 1.391 × 10⁻¹⁴ Pa at T_CMB = 2.7255 K. The pressure tensor evolves as P(z) = P_conv·(1+z)⁴ with effective polytropic index γ_eff = 4 (topologically stiff lattice, not a photon gas), dropping by an exact factor 4 at recombination when free W-defects bind into neutral hydrogen. Stars are convergence-processing nodes of the relay network, not isolated furnaces.",
  "Matter stands in the flow and casts a shadow. The unshadowed side pushes harder — that is the force, all of it. One formula carries Coulomb, gravity, and the nuclear force; the only thing that changes between them is the geometry of the shadow:":
    "A displacement structure of boundary radius R subtends occlusion cross-section πR² in the convergent flux; the antipodal flux is unbalanced by exactly the occluded fraction. Coulomb, gravitational, and nuclear couplings are one law evaluated at three cross-section scales — the interaction hierarchy is geometry, not species:",
  "Mass is not a substance a particle carries. It is the price the medium charges to reorganise around a moving displacement — push the knot, and the lattice must restructure, and it resists in proportion to the volume displaced. Inertia and weight read the same geometry twice, so their equivalence costs nothing and explains itself. A century of principle, retired by bookkeeping.":
    "Mass is not substance: m = Φ·V_disp/(3·ℓ_P³·c²) (T5–T7) is the throughput-reorganisation cost of translating an exclusion volume V_disp through the lattice; the factor 3 is the angular-averaging quadrature share, P_cf = P_conv/3 (algebraic identity). Inertial and gravitational mass read the same V_disp — once as reorganisation cost, once as occlusion cross-section — so the equivalence principle holds as an identity, not a postulate. V_disp(e⁻) = 9.988 × 10⁻⁶² m³; V_disp(p) = 1.834 × 10⁻⁵⁸ m³.",
  "Every particle runs its whole budget at c. Standing still, all of it goes to circulation; move, and the travel is paid out of the spin. That one constraint carries all of special relativity — dilation, contraction, E = mc², the speed limit, the energy-momentum relation. Eight theorems from three axioms, and nothing dilates but the bookkeeping.":
    "Axiom M3: v_circ² + v_trans² = c², with full decomposition v_T² + v_P² + v_C² + v_t² = c² (Ruleset §R6). Theorems T10–T17 recover the complete Lorentz sector: dτ/dt = √(1 − v²/c²), L = L₀/γ, E₀ = m₀c², E² = (pc)² + (m₀c²)², and the photon limit v_circ = 0 ⟹ v = c, m = 0, E = pc. Nothing dilates but the allocation of one fixed budget.",
  "The closure z · k² = 1 (z = v²/c², k = c/v) is an identity of the budget — true by construction, and labelled IDENTITY in the benchmarks. The content is the budget itself: eight theorems of special relativity recovered from three axioms, and the k-ladder it hangs on hydrogen (k = 137) through the Sun (k = 686).":
    "The closure z·k² = 1 (z = (v/c)², k = c/v) is an identity of the budget — true by construction, and carried as IDENTITY in the benchmark ledger, never as evidence. The content is the budget itself: Theorems T10–T17 from Axioms M1–M3, and the k-ladder it anchors — k(H) = 1/α = 137.036 through k(☉) = 686.4, verified against 126 measured ionisation levels with zero fitted parameters.",

  /* ── ch.3 — topology ── */
  "Stable particles are persistent vortex structures in the spation lattice — topological defects classified by winding number.":
    "Stable particles are persistent (p,q) torus-knot circulation states of the substrate, classified by winding number W; identity, radius, and coupling follow from knot invariants (Theorem T18; PPT09, class A).",
  "The topology of the lattice permits only certain self-sustaining vortex configurations, and the classification is knot theory, not a parameter choice. A (p,q) mode is a true knot only if gcd(p,q)=1 and min(p,q)≥2; its Alexander polynomial then protects it against any continuous deformation. The (1,1) electron is an unknot, confined by its own displacement. W=2 is an unknot too — merely metastable (≈0.1 GeV barrier, lifetime ~10⁻²¹ s), which is why it is never observed. The (2,3) trefoil is the first protected knot: the proton, which cannot decay. Higher odd knots (W = 5, 7, …) are protected as well and await discovery.":
    "Classification theorem (PPT09, class A): a (p,q) circulation mode is a true knot iff gcd(p,q) = 1 and min(p,q) ≥ 2, and its Alexander polynomial Δ(t) ≠ 1 is invariant under continuous deformation. (1,1): Δ = 1 — unknot, stabilised only by V_disp confinement (electron). (1,2): Δ = 1 — metastable (barrier ≈ 0.1 GeV, τ ~ 10⁻²¹ s), never observed. (2,3): Δ(t) = t⁻² − t⁻¹ + 1 − t + t² ≠ 1 — topologically protected (proton, τ_p > 10³⁴ yr). Mode partition from the budget: v_T = c√(p/(p+q)), v_P = c√(q/(p+q)). Higher odd windings (W = 5, 7, …) are protected and unobserved to date.",
  "Open winding — no closed circuit": "W = 0 — open phase path; no closed circulation",
  "Translates at approximately c. No persistent loop, hence no electromagnetic wake. SDT predicts its magnetic moment is exactly zero — the Standard Model predicts a non-zero value. A direct test.":
    "Open winding translating at ≈ c. No closed loop ⟹ no ℓ ≥ 1 wake components ⟹ magnetic moment identically zero, μ_ν ≡ 0. The rival minimally-extended prediction is non-zero — a direct experimental discriminant.",
  "Simple torus — the (1,1) unknot": "(p,q) = (1,1) unknot; Δ(t) = 1; v_T = v_P = c/√2",
  "The simplest persistent loop. Its circulation generates the electromagnetic wake field. Antimatter (the positron) is the same torus circulating in the opposite sense. Annihilation is unwinding.":
    "The minimal persistent loop, W = 1. Mode partition v_T = v_P = c/√2 follows exactly from the movement budget. Its circulation sources the ℓ = 1 wake; the positron is the identical torus with reversed circulation sense; annihilation is topological unwinding. Wake ratio g(1) = r_e·m_e·c/ℏ ≡ α — a definitional identity (class F, disclosed), not a measurement of α.",
  "Trefoil knot — (2,3) torus knot": "(p,q) = (2,3) trefoil; Δ(t) = t⁻² − t⁻¹ + 1 − t + t² ≠ 1",
  "The simplest irreducible knot. The W+1 radius conjecture, R = (W+1)ℏ/(mc), predicts a boundary radius of 0.84124 fm — matching the muonic hydrogen measurement to 0.02% with no adjustable parameter.":
    "The minimal irreducible knot, W = 3; v_T = c√(2/5) = 0.632c, v_P = c√(3/5) = 0.775c. The W+1 relation R_wake = (W+1)·ℏ/(mc) yields R_p = 4ℏ/(m_p·c) = 0.84124 fm — 0.02% from the muonic-hydrogen boundary radius with no adjustable parameter (class C-flagged: the W+1 scaling is conjectural pending derivation from trefoil geometry; W_eff = R_p·m_p·c/ℏ − 1 = 3.0008).",
  "The wake, sorted by lobes": "The wake multipole",
  "The pressure disturbance around each vortex sorts itself by how many lobes it carries. The historically \"separate\" forces are faces of the same wake field — and the trefoil's own three-fold face carries the native selection rule m₃ = 3k, with no imported quantum numbers.":
    "The vortex wake decomposes by angular order; the historically separate interactions are components of one multipole expansion of the same pressure field. Native content: the trefoil's C₃ selection rule m₃ = 3k (k ∈ ℤ) and the r⁻¹ / r⁻³ / r⁻⁴ power laws (APS04, class C) — no imported quantum numbers.",
  "@t_margin":
    "The 10³⁶ electromagnetic-to-gravitational ratio (the hierarchy problem) reduces to a ratio of occlusion cross-sections under one pressure: πR<sub>p</sub>² ≈ 10⁻³⁰ m² against πR<sub>☉</sub>² ≈ 10¹⁸ m². Identical P<sub>eff</sub>, different geometry. PPT17 resolves 6π⁵ = 1836.118 as the shared-input packing count from the point electron’s 720° Bohr-closure tube into the W=3 torus at R<sub>p</sub> (−0.0019% vs 1836.15267): COMPUTED construction, not an independent prediction of the mass ratio.",

  /* ── ch.4 — atomicus ── */
  "Every stable nucleus with Z ≥ 2 decomposes into exactly one alpha core plus some number of deuterons and tritons. And the grammar admits two distinct lineages depending on whether the core is complete.":
    "Unique factorisation theorem: every nuclide with Z ≥ 2 decomposes as 1α + n_d·d + n_t·t with n_t = A − 2Z, n_d = 3Z − A − 2. Electron-capture nuclides obey the conjugate grammar on a He-3 core: n_t = A − 2Z + 1, n_d = 3Z − A − 3. Free neutrons are forbidden in stable nuclides — an exposed triton remnant is the observable.",
  "The standard grammar builds on a complete He-4 alpha — a closed tetrahedral core. Electron capture isotopes use a He-3 core instead: an incomplete tetrahedron missing one neutron. This structural deficit is the geometric reason EC occurs — the nucleus seeks completion by capturing an orbital electron to convert a proton into a neutron, closing the tetrahedron.":
    "The standard grammar closes on a complete He-4 tetrahedral core; electron-capture nuclides close on He-3, a tetrahedron with one vertex unfilled. The structural deficit is the mechanism of EC: inner-shell capture effects p → n, completes the tetrahedron, and transfers the nuclide from the He-3 lineage to the α lineage. Decay is deterministic geometric completion, not stochastic accident.",
  "@a_ledger":
    "The triton is the grammar's unbalanced cluster: the deuteron's p–n pair is symmetric, the triton carries one excess neutron. One triton enters per neutron excess (n<sub>t</sub> = N − Z), each holding <em>two</em> neutrons; the ledger closes as N = 2 + n<sub>d</sub> + 2n<sub>t</sub>. Discipline (NP24-A): the grammar coordinates (n<sub>t</sub>, n<sub>d</sub>, v) = (N−Z, 2Z−N−2, Z−2) are an invertible map of (Z, N), so any rule expressible purely in the counts restates the neutron ledger — bookkeeping, never independent evidence. What the grammar contributes is structure: the construction map, its lineages, and the two-grammar split.",
  "When a nucleus is built on a He-3 core — an incomplete tetrahedron — it is structurally predisposed to capture an inner-shell electron. The capture converts p → n, completing the tetrahedral alpha. The EC isotope transitions from the He-3 lineage to the α-core lineage. This is not random decay — it is geometric self-repair.":
    "A He-3-cored nuclide (incomplete tetrahedron) is structurally predisposed to inner-shell capture: p → n closes the tetrahedral α and transfers the nuclide from the He-3 lineage to the α-core lineage. Deterministic self-repair with a defined geometric endpoint, not a stochastic decay channel.",
  "High-energy collisions can break structural bonds within the nucleus, knocking a deuteron or triton loose from the scaffold. If the damage exposes or creates an incomplete core, the resulting fragment becomes eligible for electron capture — spallation opens a recombination pathway between construction lineages that thermal processes alone would not access.":
    "Supra-threshold collision ejects a deuteron or triton from the scaffold. Where the damage exposes or creates an incomplete core, the fragment becomes EC-eligible: spallation opens a recombination channel between construction lineages that thermal processes cannot access.",
  "The map below plots each element by its nuclear grammar — deuteron count horizontally, triton count vertically. Elements fall into natural construction lineages visible as horizontal families (shared triton count) and vertical families (shared deuteron count). Toggle the overlay to see magnetic character — a view of the same counts, not an independent law.":
    "The construction map plots each element in grammar coordinates: n_d abscissa, n_t ordinate. Horizontal families share triton count; vertical families share deuteron count. The magnetic overlay is a re-projection of the same (Z, N) counts — displayed as a view, not claimed as an independent law.",
  "Gold is the first element where the triton count (39) exceeds the deuteron count (38). Beyond this threshold, the nuclear construction becomes triton-dominated — magnetically saturated and topologically unstable. The grammar predicts the onset of radioactivity from construction geometry alone.":
    "At Z = 79 the triton count first exceeds the deuteron count (n_t = 39 > n_d = 38). Beyond this threshold construction is triton-dominated and the scaffold approaches topological instability: the grammar locates the onset of natural radioactivity from construction geometry alone — no pairing terms, no fitted coefficients.",
  "The shadow-area account was tested": "The projected-overlap hypothesis was tested against the active packing",
  "@a_shadow":
    "The projected-overlap account prices a candidate binding diagnostic from ΔA = N·πR<sub>p</sub>² − A<sub>∪</sub>. NSEQ04 tested that rule on the active dual-tetra packing. It retains a total-binding correlation but fails the per-nucleon observable and is not promoted as the binding mechanism. The separate packing-radius relation R(A) = R<sub>p</sub>·(A/η)<sup>1/3</sup>, η = π/√18, remains a distinct zero-fit radius result.",
  "NSEQ04 active packing: κ = 31.4485 MeV/fm² [CALIBRATED(1)], R²(total BE) = 0.7918, mean |relative error| = 40.4%; R²(BE/A) = −161.94. Result: excluded as a per-nucleon binding law.":
    "NSEQ04 active packing: κ = 31.4485 MeV/fm² [CALIBRATED(1)], R²(total BE) = 0.7918 and mean absolute relative error = 40.4%; R²(BE/A) = −161.94. The per-nucleon binding law is excluded. The volume-price hypothesis E = P·ΔV is also excluded (NP05); E_bind = ℏ·Δω remains under test.",

  /* ── ch.4b — lab ── */
  "@lab_intro":
    "The census instrument plots every catalogued isotope in grammar space: abscissa n<sub>d</sub> − n<sub>t</sub> (deuteron excess), ordinate n<sub>d</sub> + n<sub>t</sub> (total subunit count). Since (n<sub>t</sub>, n<sub>d</sub>) ↔ (Z, N) is invertible, the plane is a lossless re-coordinatisation of the nuclide chart; construction lineages appear as lattice lines. Stable nuclides saturate; unstable positions attenuate by half-life tier. Overlays: shell bands, magnetic character (a count re-projection), decay vectors, and the n<sub>d</sub> = n<sub>t</sub> boundary. Pan middle-drag · zoom scroll · hover for the per-isotope decomposition.",

  /* ── ch.5 — engine ── */
  "@e_lead":
    "A header-only C++20 constexpr library encoding the axioms, theorems, and certification ledger. Zero external dependencies. Scales: ℓ<sub>P</sub> the dimensional seed; <code>c</code>, k<sub>B</sub>, e unit bridges; one mass/action seat; α = hydrogen’s koppa rung; T<sub>CMB</sub> a clock. <code>sdt::laws::measured</code> is a CODATA/FIRAS lookup.",
  "@e_intro":
    "The single source of truth is <code style=\"color:var(--mint);font-family:'JetBrains Mono',monospace;font-size:0.9em;\">laws.hpp</code>: namespaces law_I…law_VI mirror the Six Laws; <em>bridge</em> carries the k-hierarchy and koppa (ϟ = R/k² = v²R/c²); <em>atomic</em> and <em>nuclear</em> hold the domain functions. Every load-bearing constant carries a provenance block — provenance status, correspondence status, input dependency, certification class A–F, delete-test assertion, risk flag. Orbital mechanics computes without G, nuclear structure without quarks, cosmological observables without a dark sector.",

  /* ── ch.6 — cosmology ── */
  "SDT replaces ΛCDM's six adjustable parameters with geometry.":
    "Six ΛCDM adjustable parameters are replaced by the convergence-depth field z = ϟ/r and one bound-motion law v = c√z.",
  "Every spation released its stored energy simultaneously and omnidirectionally. SDT makes no claim about what existed before. The CMB is not an afterglow — it is the current operating pressure of the lattice. Estimated age: ~48 Gyr.":
    "Simultaneous omnidirectional release of held spation content; the formalism is agnostic on the antecedent state. The CMB is the current operating pressure, P(z) = P_conv·(1+z)⁴ — not an afterglow; recombination is a topological freeze-out with an exact factor-4 pressure drop. Estimated elapsed count since the Clearing: ~48 Gyr.",
  "@c_rot":
    "<strong>Audited status: OPEN.</strong> The eclipse-saturation rotation construction FAILED real SPARC photometry on direct rerun (RMS 66%, BTFR slope 1.33 — GD05; the prior success traced to a circular mock and is VOIDED). Surviving content: the derived acceleration floor a₀ = c·H₀/2π ≈ 1.04 × 10⁻¹⁰ m/s² (deliberately-wrong-floor control degrades the collapse 6×) and the 8.8% cross-scale radial-acceleration collapse, re-earned on real rotation data against a 6×-worse control. The crossover shape remains borrowed and is labelled as debt; the full rotation-curve problem is unsolved in this framework's own ledger.",
  "@c_z":
    "Two native components, no recession: an emission depth stamp z = ϟ/r at the source, plus a propagation squeeze across the Clearing quantised in octaves, 1+z = 2<sup>Δn</sup> (CMB at 10.10 octaves; λ<sub>emit</sub> = 975 nm). The lattice pressure runs P(z) = P<sub>conv</sub>(1+z)⁴ — a shared-input identity with the expanding picture's radiation era: same numbers, different construction, not independent evidence. No Λ term enters anywhere.",
  "In SDT the \"tension\" is a conflation: one number, H₀, is being asked to carry two different mechanisms — the emission-depth stamp and the propagation squeeze. Probes weight the two differently, so they land in a spread rather than on a point:":
    "The discrepancy is a conflation artefact: a single parameter H₀ is asked to carry two distinct mechanisms — the emission depth stamp z = ϟ/r and the propagation compression squeeze. Distinct probes weight the two components differently, so their estimates land in an ordered spread rather than on a point:",
  "Split the two mechanisms and the tension is not resolved — it is dissolved. Not a crisis requiring new physics.":
    "Decomposing the two mechanisms dissolves the tension rather than resolving it: the spread is predicted ordering, not evidence for additional degrees of freedom.",
  "What SDT replaces": "Eliminated entities and their derived successors",

  /* ── ch.7 — experiments ── */
  "SDT carries numbered experiment specifications (E13–E111) spanning nuclear physics, cosmology, orbital mechanics, and electromagnetism. The theory is designed to break.":
    "Numbered experiment specifications (E13–E111), each stating the SDT prediction, the rival prediction, and the observable discriminant, across the nuclear, cosmological, orbital, and electromagnetic sectors. The programme is constructed to expose the framework to refutation.",
  "The k-hierarchy returns 42.98 arcsec/century from ϟ = R/k², with G and M never written; the measured anomalous precession is 42.98. Convergent with GR — same number, half the furniture; the closure also recovers c itself to 0.0009%.":
    "The k-hierarchy closure δφ = 6πR_☉/(k²·a·(1−e²)) returns 42.98″/cy from ϟ = R/k² with G and M absent from the formalism; measured 42.98. CONVERGENT with the rival's value — independent origins, one number; inverting the same closure reconstructs c from orbital observables alone to +0.0009% (GOM04, class C).",
  "Light deflection at solar limb: 1.750 arcsec computed vs 1.751 measured. Derived from convergence gradient, not spacetime curvature.":
    "Solar-limb deflection 1.750″ computed from the accumulated depth gradient, 2∫∇⊥z dl with z = ϟ/r, vs 1.751″ measured — flat substrate, no metric curvature.",
  "Status: the eclipse rotation model FAILED real SPARC on direct rerun (GD05, RMS 66%). The derived floor a₀ = cH₀/2π and the 8.8% collapse stand; the rotation shape is OPEN.":
    "Audited status: the eclipse-saturation rotation construction FAILED real SPARC photometry on direct rerun (GD05; RMS 66%). Surviving content: the derived floor a₀ = c·H₀/2π (wrong-floor control 6×) and the 8.8% cross-scale collapse. The rotation-curve shape remains OPEN.",
  "SDT predicts mechanical signal propagation through vacuum between Casimir plates — sound through empty space via the lattice.":
    "Mechanical signal propagation through evacuated space between Casimir plates — acoustic transmission via the substrate. Field-theoretic vacuum predicts a null; positive detection is SDT-specific.",
  "Mass-independent lateral drift exceeding 10 km — a direct consequence of pressure-gradient mechanics incompatible with general relativity.":
    "Mass-independent lateral drift exceeding 10 km in free orbital descent — a pressure-gradient signature with no geodesic counterpart; incompatible with general relativity.",
  "The cosmological lithium problem resolved through α+d+t nuclear construction grammar constraints on light element formation.":
    "The primordial ⁷Li deficit follows from α+d+t construction-grammar constraints on light-element assembly channels; no stellar depletion mechanism is invoked.",
  "Frequency-dependent speed of light for gamma rays — if the lattice is discrete at Planck scale, propagation velocity should vary with wavelength at extreme energies.":
    "Discreteness at ℓ_P implies frequency-dependent group velocity for γ-rays — a lattice dispersion relation testable on photon arrival-time spreads from gamma-ray bursts at extreme energies.",
  "Displacement pressure predictions for seismic wave propagation through the inner core — testable against existing seismological data.":
    "Displacement-pressure predictions for inner-core seismic propagation, testable against the existing travel-time catalogue without new instrumentation.",

  /* ── ch.8 — glossary ── */
  "Individual element of the spatial lattice. Individually incompressible, collectively deformable. Structured at Planck-length scale (1.616 × 10⁻³⁵ m).":
    "Elementary substrate cell: individually incompressible, collectively deformable; contact-only relay at pitch ℓ_P = 1.616 × 10⁻³⁵ m (Axiom R1 — the single irreducible dimensional seed).",
  "ϟ is the ancient Greek k — same letter, same object. k = c/v is the gear; ϟ = R/k² = v²R/c² is that same gear read as a length on the boundary R. One number, in metres, carries a body's entire gravitational field — same formula for the proton and the Sun. Replaces GM/c² — no G, no kilograms, ever.":
    "ϟ = R/k² = v²R/c², k = c/v. A velocity-defined length carrying a body's entire gravitational field: z = ϟ/r, v(r) = c√(ϟ/r), g = c²ϟ/r². Per baryon: ϟ_b = ℓ_P²·c·m_p/ℏ = 1.2421 × 10⁻⁵⁴ m, whence N_baryons = ϟ_body/ϟ_b — no G, no kilograms. Equals GM/c² as a consequence, never as an input. One invariant v²r = c²ϟ spans the proton to Sgr A*.",
  "The epoch when every spation released its stored energy simultaneously. Replaces the Big Bang. SDT makes no claim about what existed before.":
    "The release epoch: simultaneous omnidirectional discharge of held spation content. Supersedes the singular origin; the formalism makes no claim on the antecedent state. Observable baseline: P(z) = P_conv·(1+z)⁴.",
  "Matter blocking a fraction of convergent pressure from one direction, creating a net force toward the occluding body. The mechanism behind gravity, Coulomb force, and nuclear binding.":
    "Attenuation of convergent flux by a boundary cross-section πR²; the net force is the unbalanced antipodal remainder, F = (π/4)·P_eff·R₁²R₂²/r² (T4). One mechanism: gravitational, Coulomb, nuclear.",
  "Inward-propagating pressure from all Planck shells to every point in space. Total burden: Φ = Nε ≈ 1.04 × 10⁻⁵⁶ J.":
    "Inward relay flux summed over N = R_CMB/ℓ_P = 5.894 × 10⁶¹ Planck shells; burden Φ = Nε = 1.038 × 10⁻⁵⁶ J; pressure P_conv = Φ/ℓ_P³ = 2.459 × 10⁴⁸ Pa.",
  "The volume of lattice a particle excludes. Determines both inertial mass (reorganisation cost) and gravitational mass (occlusion cross-section).":
    "Exclusion volume V_disp: the substrate a structure forbids. Sets inertial mass m = Φ·V_disp/(3ℓ_P³c²) and, via boundary cross-section, gravitational response — the equivalence principle as an identity.",
  "@g_budget":
    "v<sub>circ</sub>² + v<sub>trans</sub>² = c² (Axiom M3); full decomposition v<sub>T</sub>² + v<sub>P</sub>² + v<sub>C</sub>² + v<sub>t</sub>² = c². Source of Theorems T10–T17: the complete Lorentz sector as allocation of one fixed budget.",
  "A vortex's pressure disturbance sorted by angular order ℓ — the lobe count of the wake. ℓ=1 carries Coulomb, ℓ=2 carries the magnetic dipole, ℓ≥3 carries the nuclear reach.":
    "Multipole decomposition of a vortex's pressure disturbance by angular order ℓ: ℓ = 0 isotropic (mass), ℓ = 1 ∝ 1/r² (Coulomb), ℓ = 2 ∝ 1/r³ (magnetic dipole), ℓ ≥ 3 ∝ 1/r^(ℓ+1) (nuclear form factors).",
  "Topological classification of vortex structures. W=0: neutrino (open winding). W=1: electron (unknot, confined). W=3: proton (trefoil, protected). W=2 is an unknot — metastable only (≈0.1 GeV barrier, ~10⁻²¹ s), never observed. Higher odd knots (W=5, 7, …) are protected and await discovery.":
    "Topological class of the circulation state, with radius relation R_wake = (W+1)·ℏ/(mc). W = 0: open phase path (neutrino). W = 1: (1,1) unknot, Δ = 1, V_disp-confined (electron). W = 3: (2,3) trefoil, Δ ≠ 1, protected (proton). W = 2: unknot, metastable (≈0.1 GeV barrier, τ ~ 10⁻²¹ s), never observed. Higher odd windings: protected, unobserved to date.",
  "Historical model: a galactic disk's total occlusion saturating was proposed to flatten rotation curves. FAILED on direct rerun against real SPARC data (GD05: RMS 66%). Kept in the glossary because the theory keeps its assessments; galactic rotation is OPEN.":
    "Historical construction: saturation of integrated disk occlusion, proposed as the rotation-flattening mechanism. FAILED on direct rerun against real SPARC photometry (GD05: RMS 66%); the verdict is retained in the nomenclature because the ledger keeps its kills. Galactic rotation: OPEN.",
  "Z = 79 (Gold). The first element where triton count exceeds deuteron count (39t vs 38d). The onset of topological instability in nuclear construction grammar.":
    "Z = 79: first nuclide family with n_t > n_d (39 vs 38). Onset of triton-dominated construction and of natural radioactivity, located by grammar geometry alone.",
  "@g_transfer":
    "f = P<sub>eff</sub>/P<sub>conv</sub> = 2.125 × 10⁻¹⁷ — the scale map from cosmological convergence pressure to effective interaction pressure. Inherits the class-E calibration of P<sub>eff</sub> (disclosed); upgrade to class C is contingent on the CR05 closure of R<sub>CMB</sub>.",
  "T = 3(W+1) = 12 for the proton: the mismatch between the angular rate the trefoil demands of a contact spation and the fastest the lattice can relay (ω_max = c/R). That slip is the mechanical origin of the wake's faces — Coulomb, magnetic, orbital entrainment. (Separately, the 1/3 in Law IV is the angular-averaging share: P_cf = P_conv/3.)":
    "T = ω_demand/ω_max = 3(W+1) = 12 for the proton: ω_demand = 3m_p·c²/ℏ = 4.27 × 10²⁴ s⁻¹ against the relay ceiling ω_max = c/R_p = 3.56 × 10²³ s⁻¹. The slip is the mechanical origin of the wake orders ℓ = 1 (Coulomb), ℓ = 2 (dipole circulation), ℓ ≥ 3 (entrainment). Distinct object from the Law-IV quadrature share P_cf = P_conv/3.",
  "@g_grammar":
    "Unique factorisation of every Z ≥ 2 nuclide: 1α + n<sub>d</sub>d + n<sub>t</sub>t with n<sub>t</sub> = A − 2Z, n<sub>d</sub> = 3Z − A − 2 (EC grammar: n<sub>t</sub> = A − 2Z + 1, n<sub>d</sub> = 3Z − A − 3). The counts are fixed by (Z, N) arithmetic — unique wherever both are non-negative — so the grammar's content is the structure built on it, not the counts themselves. ATOMICUS characterises 290 isotopes on the decomposition; free neutrons are forbidden in stable species.",
  "@g_triton":
    "p + 2n — the grammar's unbalanced cluster. n<sub>t</sub> = N − Z; ledger N = 2 + n<sub>d</sub> + 2n<sub>t</sub>. Since (n<sub>t</sub>, n<sub>d</sub>) is an invertible function of (Z, N), any count-expressible rule is bookkeeping of the neutron ledger (NP24-A) and is claimed as nothing more.",
  "@g_ec":
    "Deterministic completion of a He-3-cored nuclide: inner-shell capture effects p → n, closing the tetrahedral α and transferring the nuclide between construction lineages. Alternate grammar applies: 1 He-3 + n<sub>d</sub>d + n<sub>t</sub>t.",
  "High-energy collision that breaks structural bonds within a nucleus, knocking deuterons or tritons loose from the scaffold. If spallation exposes an incomplete core, it opens an electron capture pathway — a recombination route between construction lineages.":
    "Supra-threshold ejection of a deuteron or triton from the nuclear scaffold. Exposure of an incomplete core opens the electron-capture channel — a lineage-recombination pathway inaccessible to thermal processes."
},

/* ─────────────────────────── DEUTSCH ─────────────────────────── */
"de": {
  "@hero_title": "Theorie der<br>räumlichen<br><em>Verschiebung</em>",
  "All of physics. No fitted parameters.": "Die gesamte Physik. Keine angepassten Parameter.",
  "Gravity, electromagnetism, the nuclear force — one push, read three ways, in a discrete spatial medium. Four primitives. One new idea: matter displaces space. Every constant computed, nothing fitted.":
    "Gravitation, Elektromagnetismus, Kernkraft — ein Druck, auf drei Arten gelesen, in einem diskreten räumlichen Medium. Vier Urelemente. Eine neue Idee: Materie verdrängt den Raum. Jede Konstante berechnet, nichts angepasst.",
  "The Medium": "Das Medium", "Five Laws": "Fünf Gesetze", "Topology": "Topologie",
  "Lab": "Labor", "Engine": "Engine", "Cosmology": "Kosmologie", "Experiments": "Experimente", "Glossary": "Glossar",
  "The Five Laws": "Die fünf Gesetze", "What Matter Is": "Was Materie ist", "Atomicus Lab": "Atomicus-Labor",
  "The Engine": "Die Engine", "Cosmology Without Dark Components": "Kosmologie ohne dunkle Komponenten",
  "Falsifiable Predictions": "Falsifizierbare Vorhersagen",
  "Convergent Boundary Pressure": "Konvergenter Grenzdruck", "The Release Cascade": "Die Freisetzungskaskade",
  "The Occlusion Force": "Die Okklusionskraft", "Inertial Mass": "Träge Masse", "The Movement Budget": "Das Bewegungsbudget",
  "Spation": "Spation", "Koppa (Ϟ)": "Koppa (Ϟ)", "The Clearing": "Die Klärung", "Occlusion": "Okklusion",
  "Convergence": "Konvergenz", "Displacement": "Verschiebung", "Movement Budget": "Bewegungsbudget",
  "Wake Tensor": "Nachlauf-Tensor", "Winding Number (W)": "Windungszahl (W)", "Eclipse Saturation": "Verfinsterungssättigung",
  "Golden Boundary": "Goldene Grenze", "Transfer Function (f)": "Übertragungsfunktion (f)", "Traction Fraction (τ)": "Traktionsanteil (τ)",
  "Nuclear Construction Grammar": "Nukleare Konstruktionsgrammatik", "Triton": "Triton",
  "Electron Capture (EC)": "Elektroneneinfang (EC)", "Spallation": "Spallation",
  "Dark Matter": "Dunkle Materie", "Dark Energy": "Dunkle Energie", "Gravitational Constant": "Gravitationskonstante",
  "Quantum Wavefunctions": "Quanten-Wellenfunktionen", "Quarks & Gluons": "Quarks & Gluonen", "Curved Spacetime": "Gekrümmte Raumzeit",
  "Theory": "Theorie", "Resources": "Ressourcen", "Technical": "Technisches", "Built with the SDT Engine": "Mit der SDT-Engine gebaut"
},

/* ─────────────────────────── FRANÇAIS ─────────────────────────── */
"fr": {
  "@hero_title": "Théorie du<br>Déplacement<br><em>Spatial</em>",
  "All of physics. No fitted parameters.": "Toute la physique. Aucun paramètre ajusté.",
  "Gravity, electromagnetism, the nuclear force — one push, read three ways, in a discrete spatial medium. Four primitives. One new idea: matter displaces space. Every constant computed, nothing fitted.":
    "La gravité, l'électromagnétisme, la force nucléaire — une seule poussée, lue de trois façons, dans un milieu spatial discret. Quatre primitives. Une idée neuve : la matière déplace l'espace. Chaque constante calculée, rien d'ajusté.",
  "The Medium": "Le milieu", "Five Laws": "Cinq lois", "Topology": "Topologie",
  "Lab": "Labo", "Engine": "Moteur", "Cosmology": "Cosmologie", "Experiments": "Expériences", "Glossary": "Glossaire",
  "The Five Laws": "Les cinq lois", "What Matter Is": "Ce qu'est la matière", "Atomicus Lab": "Laboratoire Atomicus",
  "The Engine": "Le moteur", "Cosmology Without Dark Components": "Une cosmologie sans composantes sombres",
  "Falsifiable Predictions": "Prédictions falsifiables",
  "Convergent Boundary Pressure": "Pression de frontière convergente", "The Release Cascade": "La cascade de libération",
  "The Occlusion Force": "La force d'occlusion", "Inertial Mass": "Masse inertielle", "The Movement Budget": "Le budget du mouvement",
  "Spation": "Spation", "Koppa (Ϟ)": "Koppa (Ϟ)", "The Clearing": "L'Éclaircie", "Occlusion": "Occlusion",
  "Convergence": "Convergence", "Displacement": "Déplacement", "Movement Budget": "Budget du mouvement",
  "Wake Tensor": "Tenseur de sillage", "Winding Number (W)": "Nombre d'enroulement (W)", "Eclipse Saturation": "Saturation d'éclipse",
  "Golden Boundary": "Frontière dorée", "Transfer Function (f)": "Fonction de transfert (f)", "Traction Fraction (τ)": "Fraction de traction (τ)",
  "Nuclear Construction Grammar": "Grammaire de construction nucléaire", "Triton": "Triton",
  "Electron Capture (EC)": "Capture électronique (CE)", "Spallation": "Spallation",
  "Dark Matter": "Matière noire", "Dark Energy": "Énergie noire", "Gravitational Constant": "Constante gravitationnelle",
  "Quantum Wavefunctions": "Fonctions d'onde quantiques", "Quarks & Gluons": "Quarks et gluons", "Curved Spacetime": "Espace-temps courbe",
  "Theory": "Théorie", "Resources": "Ressources", "Technical": "Technique", "Built with the SDT Engine": "Construit avec le moteur SDT"
},

/* ─────────────────────────── ESPAÑOL ─────────────────────────── */
"es": {
  "@hero_title": "Teoría del<br>Desplazamiento<br><em>Espacial</em>",
  "All of physics. No fitted parameters.": "Toda la física. Sin parámetros ajustados.",
  "Gravity, electromagnetism, the nuclear force — one push, read three ways, in a discrete spatial medium. Four primitives. One new idea: matter displaces space. Every constant computed, nothing fitted.":
    "La gravedad, el electromagnetismo, la fuerza nuclear: un solo empuje, leído de tres maneras, en un medio espacial discreto. Cuatro primitivas. Una idea nueva: la materia desplaza el espacio. Cada constante calculada, nada ajustado.",
  "The Medium": "El medio", "Five Laws": "Cinco leyes", "Topology": "Topología",
  "Lab": "Laboratorio", "Engine": "Motor", "Cosmology": "Cosmología", "Experiments": "Experimentos", "Glossary": "Glosario",
  "The Five Laws": "Las cinco leyes", "What Matter Is": "Qué es la materia", "Atomicus Lab": "Laboratorio Atomicus",
  "The Engine": "El motor", "Cosmology Without Dark Components": "Cosmología sin componentes oscuros",
  "Falsifiable Predictions": "Predicciones falsables",
  "Convergent Boundary Pressure": "Presión de frontera convergente", "The Release Cascade": "La cascada de liberación",
  "The Occlusion Force": "La fuerza de oclusión", "Inertial Mass": "Masa inercial", "The Movement Budget": "El presupuesto del movimiento",
  "Spation": "Espación", "Koppa (Ϟ)": "Koppa (Ϟ)", "The Clearing": "El Despeje", "Occlusion": "Oclusión",
  "Convergence": "Convergencia", "Displacement": "Desplazamiento", "Movement Budget": "Presupuesto del movimiento",
  "Wake Tensor": "Tensor de estela", "Winding Number (W)": "Número de enrollamiento (W)", "Eclipse Saturation": "Saturación de eclipse",
  "Golden Boundary": "Frontera dorada", "Transfer Function (f)": "Función de transferencia (f)", "Traction Fraction (τ)": "Fracción de tracción (τ)",
  "Nuclear Construction Grammar": "Gramática de construcción nuclear", "Triton": "Tritón",
  "Electron Capture (EC)": "Captura electrónica (CE)", "Spallation": "Espalación",
  "Dark Matter": "Materia oscura", "Dark Energy": "Energía oscura", "Gravitational Constant": "Constante gravitacional",
  "Quantum Wavefunctions": "Funciones de onda cuánticas", "Quarks & Gluons": "Quarks y gluones", "Curved Spacetime": "Espacio-tiempo curvo",
  "Theory": "Teoría", "Resources": "Recursos", "Technical": "Técnico", "Built with the SDT Engine": "Construido con el motor SDT"
},

/* ─────────────────────────── 日本語 ─────────────────────────── */
"ja": {
  "@hero_title": "空間<br>変位<br><em>理論</em>",
  "All of physics. No fitted parameters.": "物理学のすべて。当てはめのパラメータはゼロ。",
  "Gravity, electromagnetism, the nuclear force — one push, read three ways, in a discrete spatial medium. Four primitives. One new idea: matter displaces space. Every constant computed, nothing fitted.":
    "重力、電磁気力、核力——ひとつの押しを、三通りに読む。離散的な空間媒質のなかで。原素は四つ。新しい考えはひとつ：物質は空間を押しのける。すべての定数は計算され、当てはめは何もない。",
  "The Medium": "媒質", "Five Laws": "五つの法則", "Topology": "トポロジー",
  "Lab": "ラボ", "Engine": "エンジン", "Cosmology": "宇宙論", "Experiments": "実験", "Glossary": "用語集",
  "The Five Laws": "五つの法則", "What Matter Is": "物質とは何か", "Atomicus Lab": "アトミクス・ラボ",
  "The Engine": "エンジン", "Cosmology Without Dark Components": "暗黒成分のない宇宙論",
  "Falsifiable Predictions": "反証可能な予測",
  "Convergent Boundary Pressure": "収束境界圧", "The Release Cascade": "解放カスケード",
  "The Occlusion Force": "遮蔽力", "Inertial Mass": "慣性質量", "The Movement Budget": "運動の予算",
  "Spation": "スペイション", "Koppa (Ϟ)": "コッパ (Ϟ)", "The Clearing": "晴れ上がり", "Occlusion": "遮蔽",
  "Convergence": "収束", "Displacement": "変位", "Movement Budget": "運動の予算",
  "Wake Tensor": "航跡テンソル", "Winding Number (W)": "巻き数 (W)", "Eclipse Saturation": "食の飽和",
  "Golden Boundary": "黄金境界", "Transfer Function (f)": "伝達関数 (f)", "Traction Fraction (τ)": "牽引率 (τ)",
  "Nuclear Construction Grammar": "原子核構築の文法", "Triton": "トリトン",
  "Electron Capture (EC)": "電子捕獲 (EC)", "Spallation": "核破砕",
  "Dark Matter": "暗黒物質", "Dark Energy": "暗黒エネルギー", "Gravitational Constant": "万有引力定数",
  "Quantum Wavefunctions": "量子波動関数", "Quarks & Gluons": "クォークとグルーオン", "Curved Spacetime": "曲がった時空",
  "Theory": "理論", "Resources": "リソース", "Technical": "技術情報", "Built with the SDT Engine": "SDTエンジンで構築"
},

/* ─────────────────────────── 中文 ─────────────────────────── */
"zh": {
  "@hero_title": "空间<br>位移<br><em>理论</em>",
  "All of physics. No fitted parameters.": "全部物理。没有拟合参数。",
  "Gravity, electromagnetism, the nuclear force — one push, read three ways, in a discrete spatial medium. Four primitives. One new idea: matter displaces space. Every constant computed, nothing fitted.":
    "引力、电磁力、核力——同一种推压，三种读法，在离散的空间介质中。四个基元。一个新想法：物质排开空间。每个常数都经计算，没有一个是拟合的。",
  "The Medium": "介质", "Five Laws": "五大定律", "Topology": "拓扑",
  "Lab": "实验室", "Engine": "引擎", "Cosmology": "宇宙学", "Experiments": "实验", "Glossary": "术语表",
  "The Five Laws": "五大定律", "What Matter Is": "物质是什么", "Atomicus Lab": "Atomicus 实验室",
  "The Engine": "引擎", "Cosmology Without Dark Components": "无暗成分的宇宙学",
  "Falsifiable Predictions": "可证伪的预言",
  "Convergent Boundary Pressure": "汇聚边界压强", "The Release Cascade": "释放级联",
  "The Occlusion Force": "遮蔽力", "Inertial Mass": "惯性质量", "The Movement Budget": "运动预算",
  "Spation": "空间子", "Koppa (Ϟ)": "科帕 (Ϟ)", "The Clearing": "放晴事件", "Occlusion": "遮蔽",
  "Convergence": "汇聚", "Displacement": "位移", "Movement Budget": "运动预算",
  "Wake Tensor": "尾流张量", "Winding Number (W)": "绕数 (W)", "Eclipse Saturation": "遮食饱和",
  "Golden Boundary": "黄金边界", "Transfer Function (f)": "传递函数 (f)", "Traction Fraction (τ)": "牵引分数 (τ)",
  "Nuclear Construction Grammar": "核构造语法", "Triton": "氚核",
  "Electron Capture (EC)": "电子俘获 (EC)", "Spallation": "散裂",
  "Dark Matter": "暗物质", "Dark Energy": "暗能量", "Gravitational Constant": "引力常数",
  "Quantum Wavefunctions": "量子波函数", "Quarks & Gluons": "夸克与胶子", "Curved Spacetime": "弯曲时空",
  "Theory": "理论", "Resources": "资源", "Technical": "技术", "Built with the SDT Engine": "由 SDT 引擎构建"
},

/* ─────────────── SCHWEIZER HOCHDEUTSCH (Swiss Standard German) ─────────────── */
"de-CH": {
  "@hero_title": "Theorie der<br>räumlichen<br><em>Verschiebung</em>",
  "All of physics. No fitted parameters.": "Die ganze Physik. Keine angepassten Parameter.",
  "Gravity, electromagnetism, the nuclear force — one push, read three ways, in a discrete spatial medium. Four primitives. One new idea: matter displaces space. Every constant computed, nothing fitted.":
    "Gravitation, Elektromagnetismus, Kernkraft — ein Druck, auf drei Arten gelesen, in einem diskreten räumlichen Medium. Vier Urelemente. Eine neue Idee: Materie verdrängt den Raum. Jede Konstante berechnet, nichts angepasst.",
  "The Medium": "Das Medium", "Five Laws": "Fünf Gesetze", "Topology": "Topologie",
  "Lab": "Labor", "Engine": "Engine", "Cosmology": "Kosmologie", "Experiments": "Experimente", "Glossary": "Glossar",
  "The Five Laws": "Die fünf Gesetze", "What Matter Is": "Was Materie ist", "Atomicus Lab": "Atomicus-Labor",
  "The Engine": "Die Engine", "Cosmology Without Dark Components": "Kosmologie ohne dunkle Komponenten",
  "Falsifiable Predictions": "Falsifizierbare Vorhersagen",
  "Convergent Boundary Pressure": "Konvergenter Grenzdruck", "The Release Cascade": "Die Freisetzungskaskade",
  "The Occlusion Force": "Die Okklusionskraft", "Inertial Mass": "Träge Masse", "The Movement Budget": "Das Bewegungsbudget",
  "Spation": "Spation", "Koppa (Ϟ)": "Koppa (Ϟ)", "The Clearing": "Die Klärung", "Occlusion": "Okklusion",
  "Convergence": "Konvergenz", "Displacement": "Verschiebung", "Movement Budget": "Bewegungsbudget",
  "Wake Tensor": "Nachlauf-Tensor", "Winding Number (W)": "Windungszahl (W)", "Eclipse Saturation": "Verfinsterungssättigung",
  "Golden Boundary": "Goldene Grenze", "Transfer Function (f)": "Übertragungsfunktion (f)", "Traction Fraction (τ)": "Traktionsanteil (τ)",
  "Nuclear Construction Grammar": "Nukleare Konstruktionsgrammatik", "Triton": "Triton",
  "Electron Capture (EC)": "Elektroneneinfang (EC)", "Spallation": "Spallation",
  "Dark Matter": "Dunkle Materie", "Dark Energy": "Dunkle Energie", "Gravitational Constant": "Gravitationskonstante",
  "Quantum Wavefunctions": "Quanten-Wellenfunktionen", "Quarks & Gluons": "Quarks & Gluonen", "Curved Spacetime": "Gekrümmte Raumzeit",
  "Theory": "Theorie", "Resources": "Ressourcen", "Technical": "Technisches", "Built with the SDT Engine": "Mit der SDT-Engine gebaut"
},

/* ─────────────── SCHWIIZERDÜTSCH (Swiss German dialect — approximate) ─────────────── */
"gsw": {
  "@hero_title": "Theorie vo dr<br>ruumliche<br><em>Verschiebig</em>",
  "All of physics. No fitted parameters.": "Di ganzi Physik. Kei aapassti Parameter.",
  "Gravity, electromagnetism, the nuclear force — one push, read three ways, in a discrete spatial medium. Four primitives. One new idea: matter displaces space. Every constant computed, nothing fitted.":
    "Schwärchraft, Elektromagnetismus, Chärnchraft — ei Druck, uf drüü Arte gläse, in eme diskrete ruumliche Medium. Vier Urelemänt. Ei neui Idee: d Materie verdrängt dr Ruum. Jedi Konstante brächnet, nüt aapasst.",
  "The Medium": "S Medium", "Five Laws": "Föif Gsetz", "Topology": "Topologie",
  "Lab": "Labor", "Engine": "D Engine", "Cosmology": "Kosmologie", "Experiments": "Experimänt", "Glossary": "Glossar",
  "The Five Laws": "Di föif Gsetz", "What Matter Is": "Was Materie isch", "Atomicus Lab": "Atomicus-Labor",
  "The Engine": "D Engine", "Cosmology Without Dark Components": "Kosmologie ohni dunkli Komponänte",
  "Falsifiable Predictions": "Falsifizierbari Vorhersaage",
  "Convergent Boundary Pressure": "Konvergänte Gränzdruck", "The Release Cascade": "D Freisetzigskaskade",
  "The Occlusion Force": "D Okklusionschraft", "Inertial Mass": "Trägi Masse", "The Movement Budget": "S Bewegigsbudget",
  "Spation": "Spation", "Koppa (Ϟ)": "Koppa (Ϟ)", "The Clearing": "D Chlärig", "Occlusion": "Okklusion",
  "Convergence": "Konvergänz", "Displacement": "Verschiebig", "Movement Budget": "Bewegigsbudget",
  "Wake Tensor": "Nachlauf-Tensor", "Winding Number (W)": "Windigszaal (W)", "Eclipse Saturation": "Verfinsterigssättigung",
  "Golden Boundary": "Goldigi Gränze", "Transfer Function (f)": "Übertragigsfunktion (f)", "Traction Fraction (τ)": "Traktionsateil (τ)",
  "Nuclear Construction Grammar": "Nukleari Konstruktionsgrammatik", "Triton": "Triton",
  "Electron Capture (EC)": "Elektrone-Iifang (EC)", "Spallation": "Spallation",
  "Dark Matter": "Dunkli Materie", "Dark Energy": "Dunkli Energie", "Gravitational Constant": "Gravitationskonstante",
  "Quantum Wavefunctions": "Quante-Wällefunktione", "Quarks & Gluons": "Quarks & Gluone", "Curved Spacetime": "Chrummi Ruumziit",
  "Theory": "Theorie", "Resources": "Ressource", "Technical": "Technisch", "Built with the SDT Engine": "Mit dr SDT-Engine boue"
},

/* ─────────────────────────── עברית ─────────────────────────── */
"he": {
  "@hero_title": "תזוזה<br>מרחבית<br><em>התיאוריה</em>",
  "All of physics. No fitted parameters.": "כל הפיזיקה. בלי פרמטרים מכוילים.",
  "Gravity, electromagnetism, the nuclear force — one push, read three ways, in a discrete spatial medium. Four primitives. One new idea: matter displaces space. Every constant computed, nothing fitted.":
    "כבידה, אלקטרומגנטיות, הכוח הגרעיני — דחיפה אחת, שלוש קריאות, בתווך מרחבי בדיד. ארבעה יסודות. רעיון חדש אחד: החומר דוחק את המרחב. כל קבוע מחושב, דבר לא כויל.",
  "\"Any theory that produces paradoxes is either incomplete, or incorrect.\"":
    "\"כל תיאוריה שמייצרת פרדוקסים היא בלתי-שלמה, או שגויה.\"",
  "The Medium": "התווך", "Five Laws": "חמשת החוקים", "Topology": "טופולוגיה",
  "Lab": "מעבדה", "Engine": "מנוע", "Cosmology": "קוסמולוגיה", "Experiments": "ניסויים", "Glossary": "מילון מונחים",
  "The Five Laws": "חמשת החוקים", "What Matter Is": "מהו החומר", "Atomicus Lab": "מעבדת אטומיקוס",
  "The Engine": "המנוע", "Cosmology Without Dark Components": "קוסמולוגיה בלי רכיבים אפלים",
  "Falsifiable Predictions": "ניבויים ניתנים להפרכה",
  "You are being pressed — right now, from every direction at once.": "אתם נלחצים — ברגע זה, מכל כיוון בבת אחת.",
  "Convergent Boundary Pressure": "לחץ גבול מתכנס", "The Release Cascade": "מפל השחרור",
  "The Occlusion Force": "כוח ההסתרה", "Inertial Mass": "מסה התמדתית", "The Movement Budget": "תקציב התנועה",
  "Spation": "ספיישן", "Koppa (Ϟ)": "קוֹפָּה (Ϟ)", "The Clearing": "ההתבהרות", "Occlusion": "הסתרה",
  "Convergence": "התכנסות", "Displacement": "היסט", "Movement Budget": "תקציב התנועה",
  "Wake Tensor": "טנזור העקבה", "Winding Number (W)": "מספר הליפוף (W)", "Eclipse Saturation": "רוויית ליקוי",
  "Golden Boundary": "הגבול הזהוב", "Transfer Function (f)": "פונקציית ההעברה (f)", "Traction Fraction (τ)": "שבר האחיזה (τ)",
  "Nuclear Construction Grammar": "דקדוק הבנייה הגרעיני", "Triton": "טריטון",
  "Electron Capture (EC)": "לכידת אלקטרון (EC)", "Spallation": "ריסוק גרעיני (ספָּלַציה)",
  "Dark Matter": "חומר אפל", "Dark Energy": "אנרגיה אפלה", "Gravitational Constant": "קבוע הכבידה",
  "Quantum Wavefunctions": "פונקציות גל קוונטיות", "Quarks & Gluons": "קווארקים וגלואונים", "Curved Spacetime": "מרחב-זמן מעוקם",
  "Theory": "תיאוריה", "Resources": "משאבים", "Technical": "טכני", "Built with the SDT Engine": "נבנה עם מנוע SDT"
}

};
