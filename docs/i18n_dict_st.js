/* Technical-register dictionary for the SCROLLTHROUGH SERIES. Consumed by i18n.js.
   Loaded by st_magic_numbers.html and the st_* series. One dictionary serves the
   whole series: each page picks up only the keys whose strings it carries, so
   unmatched keys are inert.

   Coverage: st_magic_numbers — full (every prose block).
             st_00…st_04, st_flm01, st_gom_gravity — spine (tag, chapter titles).
   Convention follows i18n_dict.js: exact text-node → replacement; "@key" holds the
   full HTML for elements carrying data-i18n="key". */
window.SDT_I18N = {

"tp": {

/* ══════════════ st_magic_numbers.html ══════════════ */

"Nuclear Physics · NP33 · The Closure Schedule":
  "Domain 05 · NP33 · Closure Schedule and Capacity Derivation",

"@mn_lead":
  "Two closed forms — a triangular seat layer under bipartite doubling, <b>F(n) = 2·T(n+1) = (n+1)(n+2)</b>, and an antipodally-paired belt admissible only on the equator of the collective roll, <b>B(n) = 2(n+1)</b>, with surface remainder <b>R(n) = F(n) − B(n) = n(n+1)</b> — reproduce the closure sequence <b>{2, 8, 20, 28, 50, 82, 126}</b> sequence-exact, with zero fitted coefficients and no spin–orbit term in the input derivation basis, and extend to <b>closure(7) = 184</b>. Schedule arithmetic on this page is evaluated at run time from the two forms; measured quantities are transcribed from named sources and tagged. Single READ quantity, flagged at its point of use: the descent onset n = 3.",

"@mn_rigcap":
  "Drag to rotate (orthographic projection, painter-sorted depth). Rungs seat successive tiers: red = p-face, blue = n-face, gold = the belt sealing the closure below.",

"The two forms": "The Two Capacity Forms",
"@mn_c1lead":
  "Three geometric facts fix two capacities: two-dimensional close packing is triangular (hexagonal coordination); the bipartite exclusion doubles each seat; a radial rod satisfies the zero-slip condition at exactly one latitude.",
"@mn_c1a":
  "The doubling follows from the exclusion <strong>like never gears like</strong>: a proton gears only with neutrons, a neutron only with protons. A seat is therefore a rod presenting two faces, one p and one n, so the contact graph is bipartite — free of odd cycles, hence of frustration, and traction is guaranteed by construction rather than verified per contact. The belt confinement follows from the rolling condition ω<sub>A</sub> = −ω<sub>B</sub> (zero relative surface velocity at contact): away from the equator of the collective roll a radial rod's contact slips, which the traction condition forbids.",

"First form — the layer, doubled": "First Form — Triangular Layer under Bipartite Doubling",
"@mn_c2lead":
  "Layer n holds T(n+1) = (n+1)(n+2)/2 rod seats; each seat carries one p-face and one n-face; hence F(n) = 2·T(n+1) = (n+1)(n+2).",
"@mn_c2cap":
  "Drag vertically to separate the face sets, horizontally to rotate; click to increment the tier index. Counts evaluate live from T(n+1) and F(n).",
"@mn_c2a":
  "Accumulating this form alone yields the first three closures with no assigned quantity: F(0) = 2; 2 + F(1) = 2 + 6 = <strong>8</strong>; 8 + F(2) = 8 + 12 = <strong>20</strong> — three of seven. F(0) = 2 is the alpha core's own pair: the core satisfies the same capacity formula as every tier above it.",

"Second form — the rolling equator": "Second Form — the Rolling-Equator Constraint on Radial Rods",
"@mn_c3lead":
  "Excess neutrons enter as rigid n–p–n triton rods seated radially (inward-seating direction measured, §6). A radial rod is slip-free at one latitude only, so the belt is a one-dimensional ring rather than a two-dimensional surface: capacity linear in tier girth, antipodally paired.",
"@mn_c3cap":
  "Drag the highlighted rod off the equator: off-band the contact slips (red, forbidden), on-band it rolls (gold). Click on-band to increment the belt index. B(n) = 2(n+1).",
"@mn_c3a":
  "The dimensional order difference between the forms — quadratic for a surface tier, linear for a one-dimensional rolling band — sets the observed closure spacing: gaps of 6 and 12 while surface terms alone act; a compressed gap of 8 at the belt-only step; then 22, 32, 44 as surface remainders re-enter alongside successive belts.",

"The descent at n = 3": "The Descent Onset at n = 3",
"@mn_c4lead":
  "From the fourth tier the belt separates from its tier and descends inward to seal the closure beneath it, producing closure 28. The onset index is the one quantity on this page read from the measured sequence.",
"@mn_c4a":
  "Through tiers n = 0–2 the surface layer fills and closes. From n = 3 the belt descends to the prior shell and seals it; the succeeding tier then completes on a sealed floor. The three ages of a triton follow — <strong>docked → paired → sealed</strong>. Seat positions are fixed by tier geometry, filling order by antipodal pairing with the lone odd rod inward, and occupancy by the neutron ledger at closure time, frozen once the next tier rests upon it.",
"@mn_c4scope":
  "<strong>The descent onset n = 3 is READ from the measured sequence, not derived.</strong> The construction fixes the consequences of a descending belt but does not yet fix, from mesh and void geometry alone, why separation begins at the fourth tier. Candidate mechanism: a field-cost comparison identifying the tier at which sealing below first becomes cheaper than spreading above; that computation is owed (residual NP33 debt). The provenance block in <code>sdt::laws::nuclear</code> carries the disclosure at the definition site.",

"The schedule, computed": "The Assembled Schedule",
"@mn_c5lead":
  "All seven closures from the two capacity forms under one alternation rule, extended one index beyond the measured set.",
"@mn_c5a":
  "The forms carry no termination condition and were not conditioned on the extent of the measured set, so <strong>closure(7) = 184</strong> introduces no additional assumption: it is the same recursion advanced one index. It constitutes the construction's falsification exposure — an eighth closure located at any other count refutes the schedule that carries the preceding seven.",

"The measured closure kinks — all nineteen": "The Closure Kink as an Isotone Invariant — Complete Census",
"@mn_c6lead":
  "If a closure is a sealed floor rather than a filled level, the boundary-radius compaction must be independent of belt occupancy. Measured, whole-range, single-pass, on an instrument first validated against known answers: it is.",
"@mn_c6cap":
  "All computable closure kinks (19 points, milli-fm) against triton count n_t. Coloured markers = measured values, per-isotone mean drawn flat; dashed red = the profile occupancy-proportional compaction would require. Hover for per-member values.",
"@mn_c6a":
  "Two isotones (N = 20, N = 126) carry a single computable member each and are therefore non-adjudicable: the pre-registration required ≥ 2 members, so they are reported and not counted toward the criterion. N = 8 has no computable members — neighbour radii unmeasured. Of the three adjudicable isotones all three select <strong>constant</strong> over occupancy-proportional (RMS_const &lt; RMS_prop in each case), with |kink| span ratios clustering at 0.76, 0.78, 0.76.",
"@mn_c6scope":
  "The lone-rod-inward census (83.1%, threshold 70%) shares its predicted sign with the pairing account: <strong>shared form — cannot discriminate between accounts.</strong> The census tests the direction the seat law asserts (inward); it does not adjudicate between the two accounts.",
"@mn_c6b":
  "Post-hoc, not pre-registered: closure grip peaks at <strong>N = 28</strong> — the first descended belt — at −31.8 milli-fm, and attenuates with tier size (−22.2 at N = 50, −12.3 at N = 82). The pre-belt N = 20 closure is weak at −6.1 (single member). Whether closure grip is a belt property is a follow-up question, not a claim.",

"The assembly ladder, with its label discipline": "The Assembly Ladder and Its Tag Discipline",
"@mn_c7lead":
  "The mesh is constructed one nuclide at a time from hydrogen. Exactly one lock on the ladder is derived; the remainder are measured mass-table differences the construction names, and carry that tag.",
"@mn_c7a":
  "The deuteron lock 2.200 MeV is the ladder's sole <strong>[D]</strong> — evaluated from the shared-electron occlusion sum E = −Σ<sub>i&lt;j</sub> q<sub>i</sub>q<sub>j</sub>·αℏc/r<sub>ij</sub> with no fitted scale (−1.1% against 2.2246). The α ring-closing lock 23.847 MeV is CONVERGENT with the independent scission line-item (23.85 MeV, NP25): independent origins, same value. Every remaining entry is a measured difference the mesh picture names, and the tag records it; the ledger does not inflate one label at a time.",
"@mn_c7wd":
  "An earlier conjecture in this line held that mesh <strong>frustration</strong> selects the closures. It is withdrawn: under like-never-gears-like the contact graph is bipartite, therefore free of odd cycles, so frustration is not available as a selector. The successor account is shell completion — the schedule above.",

"The parity lock — an exact predicate": "The Triton Parity Lock — an Exact Predicate",
"@mn_c8lead":
  "The seat law requires a stable odd-Z nuclide to carry an odd triton count: the lone rod occupies the inward seat. An odd-Z nuclide with an even triton count has no partner to seal against — a parity misfit.",
"@mn_c8a":
  "The misfit class is exactly the five naturally occurring odd–odd quasi-stables. Counting convergent with the odd–odd rule of the prevailing account; the native content is the unpaired rod with no partner to seal against. Corroborating pair: <strong>Ca-48</strong> completes the first triton belt (4 antipodal pairs) and is doubly magic and held, against <strong>Ni-56</strong> with an empty belt and unstable.",

"What this settles and what it does not": "Scope, Residuals, and Falsification Exposure",
"@mn_c9scope":
  "F(n) is numerically identical to the oscillator-level degeneracy of the prevailing shell account, and B(n) to its intruder-orbit capacity. <strong>At sequence level the two accounts are not discriminable — they count the same objects.</strong> This is a shared form, claimed as consistency and nothing further. Not shared: the bipartite doubling and the rolling-equator constraint, neither available to a construction resting on an assigned spin–orbit coupling. No such coupling enters at any step — not by removal, but because the symbol is absent from the permitted namespace.",
"@mn_c9res":
  "Residuals: the descent onset n = 3 is read from data (§4); capacities are closed-form while the alternation's initial index is not; two isotones are non-adjudicable at one member each and N = 8 has no computable members; the lone-rod census shares its sign with pairing and discriminates nothing. The closure(7) = 184 prediction is the standing exposure.",

"Limitation — stated at the point of use": "Limitation",
"Scope on the staggering census": "Scope — Staggering Census",
"Withdrawal on the record": "Withdrawal",
"Scope": "Scope",
"Residuals": "Residuals",

/* ══════════════ st_00_primitives — spine ══════════════ */
"The Foundations · 0 · Primitives": "Foundations · 0 · The Primitive Set",
"Four, and no more": "The Irreducible Set — Cardinality Four",
"Space — the superfluidic hypercrystal": "Space — the Superfluidic Hypercrystal",
"Matter — displacement": "Matter — Persistent Displacement Structure",
"Movement — the one currency": "Movement — the One Currency; Nearest-Neighbour Relay at c",
"The Ever-Present Now — the plane of existence": "The Ever-Present Now — the Plane of Existence; Time as Tick Ordinal",
"Four primitives. The old list is rederived.":
  "Four Primitives; the Old Whitelist is Rederived",

/* ══════════════ st_01_law1 — spine ══════════════ */
"The Laws · I · Convergent Relay Throughput":
  "Law I · Cosmological Relay Throughput (Axioms R1–R6, Theorems T1–T2)",
"Why the far sky should not matter — and does":
  "Distance-Independence of the Per-Shell Contribution",
"Two opposing tides": "Competing Scalings — Inverse-Square Dilution against Quadratic Cell Count",
"The shell cancellation": "The Shell Cancellation Identity (Theorem T1)",
"Add the shells, and you have the pressure":
  "Summation over N Shells — Φ = Nε; P_conv = Φ/ℓ_P³ = N·u_CMB",
"A hundred-year embarrassment, dissolved":
  "The Vacuum-Energy Discrepancy as a Shell-Counting Artefact: S = 4πN²",
"What is earned, and what is next": "Certification and Residuals",

/* ══════════════ st_02_law2 — spine ══════════════ */
"The Laws · II · The Release Cascade": "Law II · The Release Cascade (Corollaries of Law I)",
"Before the Clearing, the medium was shut": "The Pre-Release State — Held Deformation Content",
"The Clearing — a single discharge": "The Clearing — Simultaneous Omnidirectional Release",
"Every point is both source and relay": "Every Site as Source and Relay Node",
"Why the pressure is many, not one": "Superposition of N Shell Arrivals",
"The cosmic microwave background, re-seen":
  "The CMB as Present Operating Pressure: u = aT⁴ = 4.172 × 10⁻¹⁴ J/m³, P = u/3",
"Stars recycle it; each rules a domain":
  "Stars as Convergence-Processing Nodes; Pressure-Domain Radius r = √(L/4πF_CMB)",

/* ══════════════ st_03_law3 — spine ══════════════ */
"The Laws · III · Convergent Boundary Pressure":
  "Law III · Convergent Boundary Pressure (Theorems T3–T4)",
"A pressure so even it hides": "Isotropic Cancellation at Equilibrium",
"Occlusion — a body casts a shadow in the pressure":
  "Occlusion — Flux Attenuation over Solid Angle Ω = πR²/r²",
"The one force law": "The Universal Force Law: F = (π/4)·P_eff·R₁²R₂²/r²",
"One mechanism, three faces":
  "One Mechanism at Three Cross-Section Scales — the Interaction Hierarchy as Geometry",

/* ══════════════ st_04_law4 — spine ══════════════ */
"The Laws · IV · Inertial Mass": "Law IV · Inertial Mass as Reorganisation Cost (Theorems T5–T7)",
"The diverted river": "Throughput Diversion about a Displacement",
"The dipole of motion": "Relay-Doppler Asymmetry under Translation",
"Inertia is the reluctance": "Inertia as Reorganisation Cost: m = Φ·V_disp/(3ℓ_P³c²)",
"Why the two masses are one":
  "Equivalence as an Identity — Both Readings Sample the Same V_disp",
"The ceiling, and the swelling": "The Relay Ceiling and the Movement-Budget Limit",

/* ══════════════ st_flm01 — spine ══════════════ */
"Foundations & Lattice Mechanics · FLM01":
  "Domain 01 · FLM01 · 28-D State and Force-Ratio Constants",
"Where they live": "Location in the State Manifold",
"T₅ — the softening gate": "T₅ — the Softening Gate",
"Φ₅ — the flip barrier": "Φ₅ — the Flip Barrier",
"Four routes, four near-misses": "Four Independent Routes — Four Near-Misses",
"Qualified, pending": "Certification: QUALIFIED — PENDING"
}

};
