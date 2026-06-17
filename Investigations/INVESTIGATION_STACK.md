# SDT Investigation Stack

> **Master index, rebuilt 2026-06-08.** Supersedes the stale dependency map in `README.md` (which indexed
> only 9 of ~32 CQ folders and had no rotation-field / nuclear / cosmology branches). Every investigation in
> the repo is **identified**, **positioned** in the dependency stack, and given a **build-prompt** — a seed
> from which a full `PROMPT.md` can be written and run. Author: James Christopher Tyndall, Melbourne.

---

## 0 · The SDT-constrained framework (every build-prompt inherits this)

Before any investigation is built or run, it obeys the §0 anti-creep protocol
(`CQ09_Spation_Rotation_Kinematic_Map/PROMPT.md` §0; `CONCEPTUAL_CONTAMINATION_AUDIT.md`):

- **Permitted inputs (whitelist):** `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + measured observables in their
  measured units (`sdt::laws::measured`). **No G, no M (kg), no GM** as fundamentals — gravity is
  `g = v²/R`, `ϟ = v²R/c²`.
- **All spectroscopy is observable.** Every measured spectral line — 21-cm, Rydberg, Lamb, hyperfine — is a
  measured observable in measured units → a legitimate input **and tool** (astronomers used the 21-cm line to
  map neutral hydrogen and rotation curves; SDT may use it the same way). The audit targets the *mechanism
  narration*, **never the measured line**: re-narrate a borrowed explanation, never rip out the observable
  (the over-purge failure mode).
- **Prohibited as inputs:** wavefunctions, fields-as-primitives, quarks/gluons, virtual particles, dark
  matter/energy, ΛCDM, wave-particle duality, magnetic moments/magnetons. A particle is a **hard, localised
  solid vortex** — never a cloud, a probability, or "just displacement."
- **The translation test** (narration audit, orthogonal to the value audit): strip every QM/EM/GR term; does
  a complete SDT-native mechanism remain that gives the same math? → **NATIVE / CONVERGENCE** (keep the
  number) **/ LINGUISTIC-BORROW** (re-narrate, keep number) **/ STRUCTURAL-BORROW** (derive natively or
  quarantine). Never **repaint** (fill a stripped gap with a QM-shaped guess); never **over-purge** a native
  concept (orbits, rotation, pressure are native).
- **Certification labels** on every result: `DERIVED` / `COMPUTED` / `CALIBRATED` (one fitted param — must be
  documented) / `OBSERVED` / `PENDING`. Plus the audit spine (`Theory/05`): provenance × correspondence → A–F.
- **Never import a QM result as a *target*.** Forward from the whitelist; check the match **downstream**;
  flag every borrowed thing; mark genuine gaps **OPEN**, do not fabricate.

### Status tags used below
`[VERIFIED]` benchmarked & passing · `[RESOLVED]` investigation complete, result earned ·
`[PARTIAL]` partial / one fitted parameter · `[ACTIVE]` spec + partial execution ·
`[SPEC]` prompt written, unstarted · `[OPEN]` no honest forward route yet (not fabricated)

---

## 1 · The dependency stack (build/run order — bottom feeds top)

```
L0  FOUNDATIONS        Laws I–VI · OP-1 R/a quantisation · OP-2 winding quantisation · OP-3 α-from-topology
                        └─ the lattice-simulation root: per-spation contact mechanics (CQ09 bottom-of-stack)
L1  LATTICE MECHANICS  CQ08 GPI · CQ10 lattice pulse · CQ09 rotation field · packing/interstices
L2  PARTICLE TOPOLOGY  CQ02 vortex equilibrium · CQ11 confinement · CQ14 traction · α · m_p/m_e · moments · ν
L3  ATOMIC & RADIATION emissions-from-first-principles · CQ12/13 · CQ26 crossover · Lamb · g-2 · blackbody
L4  NUCLEAR GRAMMAR    CQ25 grammar · CQ27/27B growth · CQ28 mirror · CQ29 neutron · ATOMICUS EC · spallation
L5  GRAVITY & ORBITAL  CQ15 depth-engine · CQ16 k-hierarchy · CQ24 closure · planetary/Saturn/seismic/tidal
L6  GALACTIC & COSMO   CQ06 eclipse · CQ18/19/20 · E46 rotation · E47 lensing · Hubble suite · BAO · H0
L7  STELLAR & COMPACT  luminosity · main sequence · Chandrasekhar · TOV · black-hole interior
L8  CORRESPONDENCE     the "already-confirmed" QM/GR phenomena reframed as lattice mechanics (catalogue)
```

**The honest root:** L0/L1 — the **per-spation contact mechanics** (the tetra/octa/penta/hexa interstitial
rolling under pressure with the c-relay) — **has never actually been computed.** OP-1/OP-2/OP-3 and the CQ09
co-rotation coefficient all bottom out here. Everything above is built on continuum summaries of this root.
This is the single most load-bearing open problem; see `CQ09.../DEEPTHINK_PROMPT.md`.

---

## L0 · Foundations (the root)

- **OP-1 — R/a Quantisation** `[OPEN]` · root. *Build:* lattice-simulate the coupled mode equations
  (v_T, v_P, v_C set by R/a and α; modal coupling C_TP = a/R) to find the **discrete** (R/a, α) sets that are
  stable → predicts the mass spectrum. Whitelist only. (Theory/03)
- **OP-2 — Winding-number Quantisation** `[OPEN]` · root. *Build:* simulate vortex reconnection dynamics;
  show W=1, W=3 stable and W=2 (torus *link*, not knot) spontaneously decays → W=1 + energy. Output the full
  stable-particle catalogue from topology alone. (Theory/03)
- **OP-3 — α from Topology** `[OPEN]` · needs OP-1. *Build:* prove (or refute) `α = v_P/v_T` at the W=1
  equilibrium, deriving α from torus geometry. If it holds, α leaves the whitelist; terminal inputs reduce to
  `{ℓ_P, T_CMB, d=3}`. (Theory/03; CQ03 found α=koppa-of-H, electromagnetic, needs `e` — reconcile.)
- **ROOT-SIM — Per-spation contact mechanics** `[OPEN]` · the bottom of L1. *Build:* the simulation spec in
  `CQ09.../DEEPTHINK_PROMPT.md` — per-contact rolling/traction, off-equator `cosθ`, interstitial packing,
  pressure, c-relay anisotropy → derive the per-contact lag coefficient and reproduce `v(r)=v₀√(R_p/r)→αc`
  without plugging it. Feeds OP-1/2/3 and all of L1.

## L1 · Lattice mechanics

- **CQ08 — Granular Pulse Mechanics** `[RESOLVED 12/12]` · Laws III–V. GPI (pulse rate c/ℓ_P²) → F=ma,
  Newton I–III. *Build (maintenance):* re-verify against ROOT-SIM once the per-contact rule is earned.
- **CQ10 — Lattice Pulse Propagation** `[RESOLVED 15/16]` · CQ08, Law IV. Tick-by-tick contact/gap state
  machine; the intentional 16th failure proves V_torus ≠ V_disp.
- **CQ09 — Spation Rotation Field** `[ACTIVE]` · CQ08, ROOT-SIM. Rotation field `v(r)=cα√(a₀/r)`; co-rotation
  formula + stack in `CQ09_COROTATION_AND_STACK.md`; coefficient flagged candidate. *Build:* hand ROOT-SIM to
  DeepThink, propagate up. **Fork: `CQ09_Spation_Rotation` (code-only) is superseded by `_Kinematic_Map`.**
- **PACKING — Close-packing interstices** `[SPEC]` · supports ROOT-SIM. *Build:* enumerate the tetra/octa/
  penta/hexa interstitial geometry of the shell lattice (`packing.hpp` / Tammes) and which contacts rotation
  permits/forbids. Pure geometry; no physics inputs.

## L2 · Particle topology & constants

- **CQ02 — Vortex Equilibrium Quantisation** `[RESOLVED 5/5]` · Law V. R/a = √(q/p) for (p,q) knots; electron
  (1,1), proton (2,3) trefoil; v_T=0.632c, v_P=0.775c.
- **CQ11 — Trefoil Confinement** `[RESOLVED]` · Law III, CQ02. Confinement + string tension from convergent
  pressure on the trefoil; linear potential, string-breaking at 0.23 fm.
- **CQ14 — Spation Traction from Trefoil** `[RESOLVED]` · Law V, CQ11. v_phase=1.831c at R_p; traction ratio
  T=12=3(W+1); 6π winding; three output channels. (Feeds CQ09 hand-off.)
- **CQ03 — Fine Structure from Topology** `[RESOLVED-NEGATIVE]` · CQ02, CQ16. α = koppa of the H ground state
  (electromagnetic, k=1/α=137 rung) — **not** topological; needs charge `e`. *Build:* reconcile with OP-3 /
  **E51**; produce the SDT↔QM α catalogue (deferred from CQ03 scroller).
- **E51 — α from W=1 velocity ratio** `[OPEN]` · = OP-3. *Build:* α from poloidal/toroidal velocity ratio at
  W=1; lattice topology. (Open problem; pairs with CQ03.)
- **Mass ratio m_p/m_e** `[PARTIAL]` · CQ02, Law IV. 6π⁵=1836.118 topological identity confirmed to 0.0019%;
  full derivation blocked by the V_disp equilibrium solver (= OP-1). **Canonical = CQ17** (analytical);
  **CQ05 superseded** (preliminary); **E52** is the experiment spec. *Build:* close via ROOT-SIM/OP-1.
- **CQ07 — Neutrino has no magnetic moment** `[RESOLVED]` · Law VI. W=0 open winding → μ_ν≡0 exactly;
  re-narrate natively (open winding → no EM-deflecting wake), drop the borrowed "moment". Falsifiable vs SM
  ~10⁻²⁰. Pairs with **E58** (monopole forbidden by half-vortex impossibility).
- **E40 — Nuclear magnetic moments** `[SPEC]` · CQ02, CQ14. *Build:* μ for p, n, d, t, He-3 from W=3 trefoil +
  W=1 torus circulation geometry (native wake, **no magneton**); compare to measured ratios.
- **E32 — Proton radius** `[VERIFIED]` · R_p = 0.841 fm from W+1; matches muonic value (B18).
- **E39 — Proton–neutron mass difference** `[OPEN]` · 1.293 MeV from trefoil circulation; derivation
  incomplete. Pairs with the ATOMICUS **neutron-identity** thread (n = p + internal e⁻).
- **E79/E80 — Pair production / annihilation** `[VERIFIED]` · 2×511 keV from vortex creation / counter-vortex
  collision. **E81 — electron diffraction** `[VERIFIED]` (lattice scattering of the vortex).
- **ANGULAR-DOF — native angular (l) degree of freedom** `[OPEN · foundational]` · **blocks all L3 fine
  structure.** SDT currently recovers only **radial / principal-n** structure (node ladder r_n=n²a₀, L_n=nℏ);
  the rotation field v(r)=cα√(a₀/r) is a function of **r only** (CQ09). There is **no native reason l=0 (s)
  differs from l=1 (p)** — the s-vs-p distinction is borrowed spherical-harmonic coordinates (contamination
  audit M1, STRUCTURAL-BORROW). *Build:* derive an angular / orbital-shape DOF from the torus/helix/occlusion
  geometry itself (not imported Y_ℓ^m). **Until it exists, no Lamb shift, no fine structure, no s-vs-p
  splitting — and not even the sign 2S₁/₂ > 2P₁/₂ — can be computed natively.** (Surfaced by the Lamb-dyad
  refutation workflow, 2026-06-08.)

## L3 · Atomic structure, emission & radiation

- **EMISSIONS — All emissions from first principles** `[SPEC]` · CQ12, CQ02/03, Laws III–V. The Layer-3
  spine (`Investigations/PROMPT_all_emissions_from_first_principles.md`, 5 phases). *Build:* H (v₁=αc from
  movement budget) → Rydberg/Lyman/Balmer <0.01% → hydrogen-like Z² (NIST <0.1%) → multi-electron geometric
  void model (dyad/triangle/tetra/cube k-factors) → cross-regime zk²=1 + budget check → novel: nuclear
  grammar (n_d/n_t) → spectral fingerprint. No QM, no wavefunction.
- **CQ12 — Emissions** `[RESOLVED]` · CQ02/03. H <13 ppm, H-like <264 ppm, 118-element zk²=1 closure.
- **CQ13 — Emission Prediction (drag)** `[ACTIVE/code]` · CQ12. Drag factor D vs outer-shell electron count;
  multi-electron drafting; folded into CQ26. *Build:* write up the drafting geometry as a standalone result.
- **CQ26 — Universal Drafting Crossover** `[PARTIAL]` · CQ12, CQ16. B=Φ(ξ), ξ=g_self/a₀ collapses atomic +
  stellar + galactic onto one curve (8.8% RMS); source asymptote confirmed 3 scales; floor asymptote galactic
  only; nuclear excluded. *Build:* close the floor with wide-binary data; derive the crossover shape (still
  borrowed MOND-simple).
- **Lamb shift** `[CALIBRATED]` · B04 (k_Lamb=12.7227 fitted) / **E54** (lattice fluctuation spectrum,
  incomplete). *Build:* derive the shift natively. **NATIVE CANDIDATE (James, 2026-06-08):** the Lamb shift is
  *the cost of breaking a dyad first* — the 2S-vs-2P gap as the work to break/reform the proton–electron
  (co-rotating, contra-rotating) **dyad** bond in the s-geometry that the p-geometry avoids. **VERDICT
  (refutation workflow, 2026-06-08): did NOT survive — 4/4 skeptics refute.** The only worked-out version
  (`ATOMICUS/…/INVESTIGATION_Neutron_Identity.md` Part VI "Dyad vs Plane") fails 3 ways: borrowed **l-multipole**
  language (l=0 vs l=1) though SDT has **no native angular DOF**; a **|ψ(0)|² repaint** (QED's s-at-origin
  asymmetry restated as a long-range integral); and a **category error** (the proton–electron dyad of 1H ≠ the
  Li/Be two-electron gear-pair; ~4.4 µeV vs ~eV, wrong scale/members). It predicts nothing (B04 stays fitted;
  sign supplied externally). Root blocker = **ANGULAR-DOF** (L2). **Parked pending James's reading of
  *dyad / first*** — not killed, not canon. **GUARD (RETRACTED candidate):** *not* "s-orbital
  penetrates the core" (= |ψ(0)|² in disguise; electron is a hard point orbiting at a₀, does **not** enter the
  proton). Native lead = **nuclear-grammar-keyed** (triton content), the Li-6 (n_t=0) vs Li-7 (n_t=1)
  discriminator — opposite of QED's structure-blind contact term. Until earned: **OPEN**.
- **g-2 anomaly** `[SPEC]` · E53 / **E91** (4.2σ). *Build:* lattice-perturbation correction series to the
  magnetic g-factor (B17 = native g); compare to the measured anomaly. No QED loops.
- **Hyperfine / 21-cm line** `[OBSERVED line · mechanism PENDING]` · the **1420.405 MHz / 21-cm line is a
  measured observable** — a valid input and tool (HI maps, rotation curves, 21-cm cosmology; SDT may use it
  likewise). Borrowed is only the **QED hyperfine *mechanism*** (μ_P, spin-flip, magnetons), which B05
  imported. *Build:* re-narrate the splitting natively (whirl-on-whirl overlap of the proton–electron dyad);
  the **line itself is not OPEN** and is not to be ripped out.
- **Blackbody from lattice** `[SPEC]` · **E61/E62/E63**. *Build:* Planck from lattice mode counting
  (n(ν)=8πν²/c³, ⟨ε⟩ Bose) — the lattice is already discrete at ℓ_P, no quantised-oscillator postulate;
  Stefan-Boltzmann a=8π⁵k⁴/15c³h³ and Wien from the mode integral.
- **Photon interactions (reframe, [SPEC]):** **E55** photoelectric (sub-attosecond absorption), **E56**
  Compton (lattice momentum transfer), **E89** bremsstrahlung (vortex deceleration), **E87** vacuum
  birefringence (magnetar-field lattice anisotropy), **E88** Schwinger pair (lattice breakdown field),
  **E83** quantum-oscillator noise (lattice thermal spectrum). Each: native lattice mechanism → show
  convergence with the measured cross-section; falsifier where SDT departs from QED.
- **Condensed-matter correspondence (reframe, [VERIFIED/SPEC]):** **E59** superconductivity (phase-locked
  vortex pairs), **E84** Aharonov-Bohm (relay-phase), **E85** Josephson (phase coupling, defines the volt),
  **E86** quantum Hall (lattice topology, defines the ohm).

## L4 · Nuclear grammar, electron capture & spallation

- **CQ25 — Atomicus Nuclear Grammar** `[RESOLVED/frozen]` · Law IV. 1α + n_d deuterons + n_t tritons; 287
  nuclides classified; the constitution for L4. (`n_t=A−2Z`, `n_d=3Z−A−2`; EC grammar uses He-3 core.)
- **CQ27 — Stellar Fusion & Nuclear Growth** `[SPEC]` · CQ25. 5-stage pipeline (growth compiler, occlusion
  bonds, trefoil rotation, EC gate, nucleus↔shell inversion). *Build:* execute stages A–E; no run output yet.
- **CQ27B — Grammar Chain Growth** `[ACTIVE]` · CQ25, CQ27. (n_d,n_t) lattice walk; inversion test 14/29.
  *Build:* complete the quantitative map.
- **CQ28 — Nuclear↔Electronic Mirror Falsification** `[SPEC]` · CQ25, CQ27. Hostile test of "proton is the
  code": build nucleus and electrons independently, compare geometry vs null models (sub-investigations
  CQ28A–E, strict one-way). *Build:* execute.
- **CQ29 — Neutron Genesis to Tritium** · CQ25. **CQ29A** `[RESOLVED]` decay ledger + tritium keystone
  Q_β=18.3 keV (1836π falsifier passed); **CQ29B** `[OPEN]` 3n→triton energy gate Q=9.264 MeV passes on
  energy but **kinetics/cross-sections unpredicted**. *Build:* the assembly kinetics.
- **ATOMICUS EC — Electron Capture suite** `[RESOLVED, 18 INV]` · CQ25. INV-01…18 proven (grammar
  Δn_t=+2/Δn_d=−3; Be-7 unit; 35-day subshell cluster; protection factors; He-3 core; ionisation-gated rates;
  Keplerian inner-electron redshift). *Open child problems → build each:*
  - **EC-O1** physical meaning of factor 176 in 478keV/19.82eV=137×176 `[OPEN]`
  - **EC-O4/O5** why PF=(m_p/m_e)·Z only for Be-7; is the nuclear matrix element geometric (scaffold
    topology)? `[OPEN]`
  - **EC-O7** does the grammar penalty predict EC t½ quantitatively across all data? `[OPEN]` (the big fit)
  - **EC-O8** free neutron as triton remnant — confinement model `[OPEN]` (ties to E39, neutron-identity)
  - **EC-O9** alternate (He-3 core) grammar stability conditions `[OPEN]`
- **EC charge-state experiments [SPEC]:** **E13** Ge-68 rate scan, **E14** ionisation-controlled halt,
  **E15** Be-7 magnetic-field coupling, **E16** Se-68 cascade timer, **E17** Ba-133 anion, **E18** Co-56
  gamma rearrangement, **E19** He-3/He-4 King-plot nonlinearity, **E20** neutron-budget verification, **E37**
  double-EC Xe-124, **E38** universal EC cessation at full ionisation. Each: SDT EC-grammar prediction vs
  charge state → measurable t½ change.
- **Nuclear binding/structure [SPEC/Calc]:** **E28** triple-alpha/Hoyle (α+4d packing), **E29** deuteron
  binding (occlusion at 2.14 fm), **E30** alpha binding (tetrahedral 2p+2n), **E31** neutron lifetime
  (beam vs bottle from boundary conditions), **E33** charge-radius scaling Z·R_p vs r₀A^(1/3) (NIST
  archival), **E34** Li-7 quadrupole (α+t separation), **E35** Fe-56 vs Ni-62 grammar efficiency, **E36**
  O-16 pure-deuteron scaffold. Dependency: E29 → E30 → E28.
- **Atmospheric Spallation** `[SPEC, 12 items]` · CQ25. **Q01** event geometry · **Q02** neutron-ejection
  selectivity (ℓ=1 wake) · **Q03** multiplicity rule (EXFOR) · **Q04** capture mechanism / 1-over-v · **Q05**
  cosmic ray as relativistic torus (GZK from lattice stability, → **E90**) · **Q06** post-spallation neutron
  fate (C-14 cycle). Archival: **A01** grammar audit (≥500 products) · **A02** multiplicity-vs-energy · **A03**
  atmospheric inventory (validate C-14/Be-7/Be-10/H-3) · **A04** σ ∝ R_disp² vs r₀A^(1/3) · **A05** capture-σ
  vs grammar (10⁹ dynamic range) · **A06** cosmogenic production rates.

## L5 · Gravity, orbital & planetary

- **CQ16 — k-Hierarchy Advantage** `[RESOLVED 15/15]` · CQ01, CQ02. k=c/v, ϟ=v²R/c², GM=ϟc²; nuclear→galactic
  ladder, no test particle. The conversion spine.
- **CQ15 — Spation Depth Engine** `[RESOLVED 27/27]` · CQ16, Law I. z(r)=ϟ/r reproduces redshift, Shapiro,
  bending, cosmological z from one scalar field.
- **CQ24 — Koppa Closure** `[RESOLVED]` · Law I, CQ16. c and ϟ derived from Mercury precession + orbital
  velocity, no GM (the "c from geometry" result).
- **CQ23_Lunar — Lunar Orbital Kinematics** `[ACTIVE]` · CQ15, Law III. Lunar orbit from pendulum
  acceleration time-series via tidal occlusion gradient; no G/M. **(Number collides with CQ23_3D — propose
  renumber, see §3.)**
- **Gravity tests [SPEC]:** **E24** Mercury precession 42.98″/cy from k²-gradient (Calc) · **E21** orbital
  velocity drop / frame-dragging lateral drift · **E23** Cavendish bell (shielding inside dense shell) ·
  **E26** lunar laser ranging k-residuals (archival) · **E27** solar oblateness J₂ (archival) · **E70**
  gravitational redshift `[VERIFIED]` · **E71** gravitational Casimir · **E73** local c near dense object ·
  **E75** equivalence principle (explains *why*) · **E76** G environmental variation · **E77** Sagnac
  `[VERIFIED]` · **E78** time dilation `[VERIFIED]` · **E94** convergence lens (gravity on shadow side) ·
  **E92** solar-sail convergence harvesting · **E25** Pioneer `[not-runnable: thermal recoil explains it]` ·
  **E96** artificial gravity `[not-runnable: planetary-scale]`.
- **E97 — Earth core seismic speed** `[RESOLVED ✅ 1.82% RMS to PREM, 15 Apr 2026]` · CQ15. g(r) from koppa,
  no G/M. (The completed exemplar.)
- **E99 — Ocean tidal harmonics** `[SPEC archival]` · convergence gradient differential. **E98 — Lead-sphere
  displacement field** `[SPEC]` (near-field topology; note two E98 files — keep the multi-gas version).
- **E101 — Solar-system convergence budget** `[SPEC]` · CQ16. Total convergence balances CMB influx; full
  k-hierarchy. **E11/E45 redshift+BAO** also feed here (shared cosmology).
- **SATURN — Gradient / ring persistence** `[ACTIVE: analysis done, writeup pending]` · CQ16.
  `saturn_gradient_check.cpp`: Saturn's surface gradient ϟ/R² ≈79× the Sun's at Saturn → local domination →
  rings protected from solar-wind erosion; only Jupiter/Saturn dominate (Uranus/Neptune don't). *Build:* write
  up as an investigation; predictive test = **ring stability vs gradient-domination ratio across all 8
  planets**. (Pairs with `magnetosphere.hpp`.)

## L6 · Galactic & cosmological

- **CQ06 — Eclipse Saturation Model** `[RESOLVED-framework]` · CQ16, Law I. Flat rotation curves from
  convergence-disk occlusion; BTFR slope 4; G_eff exact. (`galactic.hpp`.)
- **CQ23_3D — 3D Volumetric Integration** `[ACTIVE]` · CQ06. Pure 3D radial occlusion integral replacing the
  2D Σ_sat anchor (fixes LSB galaxies).
- **E46 — Galaxy rotation curves (SPARC)** `[ACTIVE archival]` · CQ06. **NOTE (memory):** canonical 3D eclipse
  FAILS real SPARC (RMS 66%); the **twin-regime / M4 convergence-floor** law wins (RMS 23.8%, BTFR 3.58) but
  its crossover shape is borrowed MOND-simple. *Build:* derive the crossover natively (ties to CQ26 floor).
- **E47 — Gravitational lensing** `[SPEC archival]` · CQ15. Lensing as convergence-gradient refraction; vs
  strong-lensing data; **P5** low-mass-object test.
- **CQ18 — Redshift Decomposition** `[ACTIVE/code]` · CQ16, CQ15. z=1/k², zk²=1 from proton interior to
  cosmological ladder; H₀ correction. (`cq18_unified.cpp` + variants.)
- **CQ18_ZOA — Zone-of-Avoidance lensing** `[FRAMEWORK]` · CQ18, CQ19. Milky-Way foreground systematics in
  redshift residuals. **(Number collides with CQ18_Redshift — propose renumber, §3.)**
- **CQ19 — Milky Way Occlusion Map** `[SPEC]` · CQ06, CQ20. Catalogued sources within 150 pc of Sgr A*; eclipse
  occlusion at the galactic centre.
- **CQ20 — Galactic Spation Topology** `[ACTIVE]` · CQ16, CQ15. Lattice state across 12 radial zones
  (10⁻¹⁶ → 10²¹ m); grand unification of CQ17–19. *Build:* requires CQ17–19 closed.
- **Hubble suite** `[ACTIVE]` · CQ15/CQ16/CQ18. ~19 zk² tools → investigations: **Pantheon+ distance
  relation** (5-model compare incl. ΛCDM/Milne), **host-mass step** (weakest link), **lattice/H₀-gradient
  inference**, **solar/stellar surface-gravity zk²** (M31, ε Eridani), **planetary/Jovian dynamics** (flyby
  anomaly), **dark-matter reframing** (KBC-void underdensity → local κ). **UNBUILT (HIGH):** the unified κ(z)
  multi-survey fit + universe age from r_s/θ_s (Hubble README Open-Calc #1). *Build that first.*
- **Cosmology experiments [SPEC archival]:** **E41** T_CMB from zk²=1 closure · **E42** H₀ tension
  (Pantheon+) · **E43** SN Ia mass step · **E44** CMB dipole (observer motion vs expansion) · **E45** BAO as
  lattice standing waves (DESI) · **E49** dark energy as pressure-gradient misreading (χ² with/without Λ) ·
  **E50** Cν background T_ν `[awaits PTOLEMY]` · **E48** GW speed = c `[VERIFIED GW170817]` · **E90** GZK
  cutoff `[VERIFIED Auger]` · **E100** lattice dispersion (GRB photon timing) · **E72** c in dense media.

## L7 · Stellar & compact objects

- **E64** Solar luminosity (convergence recycling budget) `[SPEC]` · CQ16/E101.
- **E65** Stellar main sequence as k-gradient equilibrium (GAIA) `[SPEC archival]`.
- **E66** White-dwarf Chandrasekhar 1.44 M_⊙ from occlusion saturation `[SPEC]`.
- **E67** Neutron-star TOV ~2.2 M_⊙ from lattice compression limit `[SPEC]`.
- **E68** Black-hole interior = max-compression state (no singularity); LIGO ringdown echoes `[SPEC archival]`.
- **E69** Hawking temperature from lattice surface modes `[not-runnable: unobservable]`.
- **CQ27** stellar fusion pipeline also lands here (growth pathway → element synthesis).

## L8 · Correspondence catalogue (already-confirmed phenomena, reframed)

These are **CONVERGENCE** tests, not open derivations: SDT must reproduce a result QM/GR already measured.
Lower build-priority; each build-prompt is the same template — *state the native lattice mechanism, show it
gives the measured number, name the falsifier where SDT departs.* Compact list:

| E## | Phenomenon | SDT lattice mechanism | Tag |
|-----|-----------|------------------------|-----|
| E57 | Cherenkov radiation | shock above local phase velocity | VERIFIED |
| E58 | Magnetic monopole non-existence | half-vortex topologically impossible | VERIFIED |
| E60 | Casimir 1/d⁴ deviation | lattice granularity (AFM 0.1–10 nm) | SPEC |
| E22 | Casimir vacuum "sound" | pressure-wave transmission across the gap | SPEC |
| E70/E77/E78 | grav redshift / Sagnac / time dilation | lattice compression cycle | VERIFIED |
| E79/E80/E81 | pair prod / annihilation / e⁻ diffraction | vortex creation / collision / scattering | VERIFIED |
| E84/E85/E86 | Aharonov-Bohm / Josephson / quantum Hall | relay phase / phase coupling / lattice topology | VERIFIED |
| E89/E90 | bremsstrahlung / GZK cutoff | vortex deceleration / lattice energy-density limit | VERIFIED |
| E48 | GW speed = c | transverse lattice rigidity | VERIFIED |
| E53/E91 | muon g-2 | lattice perturbation correction series | SPEC |
| E74 | Unruh effect | accel→thermal (a~10²⁰, unmeasurable) | not-runnable |
| E82 | neutrino speed = c | massless lattice mode (awaits SN) | not-runnable |
| E93/E95 | vacuum waveguide / lattice comms | granularity cutoff / non-EM transducers | SPEC/spec. |

---

## 2 · Benchmarks (the verified base — not investigations, the floor they stand on)

`Benchmarks/B01_B25/benchmarks_b01_b25.cpp` — all 25 **PASS**. These are the regression floor, not open work.
Only one carries a fitted parameter and therefore an open investigation: **B04 Lamb shift** (`k_Lamb=12.7227`
CALIBRATED → see L3 Lamb). The rest (B01 Rydberg, B03 α, B05 21-cm*, B07 thermo, B08–B12 orbital/stellar,
B13 CMB, B14 rotation, B15 BAO, B17 g-factor, B18 R_p, B19 β-decay Q, B20 zk², B21–B22 hierarchies, B23
Coulomb identity, B24 V_disp, B25 He-4) are DERIVED/COMPUTED. *(B05's value passes — the 21-cm line is an
OBSERVED spectral line; only its hyperfine *mechanism* narration was borrowed, re-narrated in L3.)*

---

## 3 · Fork / collision resolution (flagged — folder renames need your OK)

| Collision | Keep (canonical) | Resolve |
|-----------|------------------|---------|
| `CQ09_Spation_Rotation` vs `CQ09_Spation_Rotation_Kinematic_Map` | **_Kinematic_Map** | archive/merge the code-only base into it |
| `CQ05` vs `CQ17` (both m_p/m_e) | **CQ17** (analytical) | mark CQ05 superseded-preliminary |
| `CQ18_Redshift_Decomposition` vs `CQ18_ZOA_Lensing` | both distinct | **renumber ZOA → CQ21** (free) |
| `CQ23_3D_Volumetric_Integration` vs `CQ23_Lunar_Orbital_Kinematics` | both distinct | **renumber Lunar → CQ22** (free) |

Free CQ numbers after resolution: CQ21, CQ22 used above; next new investigation = **CQ30**.

---

## 4 · Coverage & priority

**Counts:** ~32 CQ folders · 89 E-specs (E13–E101) · 25 benchmarks · 18 EC INV + 9 EC-open · 12 spallation ·
~6 Hubble investigations · 3 named latent threads · 3 Theory open problems (OP-1/2/3) · 6 falsifiable
predictions (P1–P6).

**Build-priority (where the leverage is):**
1. **ROOT-SIM / OP-1 / OP-2 / OP-3** — the per-spation lattice simulation. Everything else rests on it; it has
   never been computed. (DeepThink prompt ready.)
2. **EMISSIONS-from-first-principles** — the end-to-end atomic test; spec ready, unstarted.
3. **Hubble unified κ(z) fit** — the one missing tool that validates the redshift mechanism at cosmic scale.
4. **EC-O7 quantitative t½ fit** + **CQ29B kinetics** — turn the grammar from descriptive to predictive.
5. **Saturn ring-persistence writeup** + **E46 native crossover** — analyses done, derivations not yet native.
6. Then the L8 correspondence catalogue (lower leverage; mostly confirmation).

> Next: (a) repoint `README.md` to this stack; (b) approve the §3 renames; (c) pick a build-priority target
> and I'll write its full `PROMPT.md` under §0. The ROOT-SIM DeepThink prompt is already staged.
