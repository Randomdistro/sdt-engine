# Spatial Displacement Theory — LLM uptake

**J. C. Harvey, Melbourne. 2026-08-13.**  
Single source of numerical truth: `Engine/include/sdt/laws.hpp`. Cycle arithmetic: `Theory/07_Cyclic_Reiteration.md`. People: `Papers/SDT_FOR_PEOPLE.md`. Model: `Papers/SDT_THEORETICAL_MODEL.md`.

Every laboratory number used here already exists as experimental data (CODATA 2018, IAU, FIRAS). The SDT arithmetic recomputes those same quantities from the structure. That recompute is a consistency proof, not a claim that the metre, the second, or a spectral line was invented here. After each section a **strict gate** records the residual or named exclusion that would have failed if a coefficient had been inserted to land.

Labels: DERIVED · COMPUTED · CALIBRATED(n) · OBSERVED · PENDING · EXCLUDED · WITHDRAWN. Correspondence (`GM = c²ϟ`) is not provenance.

The life of the universe is §14, after the structure has been calculated.

---

## 1. What the world is

Space is a gap-free packing of cells — **spations** — that hand movement to their neighbours, one cell per tick. The tick is so short that light is the handoff rate:

```
c = ℓ_P / t_P
```

Matter is a lasting displacement volume: a knot of circulating movement that excludes cells. Force is occluded convergence. Nothing pulls. The universe pushes. A closed path of least resistance through that push is an orbit.

Movement is one budget: circulation plus translation. Now is the tick. There is no first moment and no last one.

Gravity, charge, and the nucleus share one force law:

```
F = (π/4) P_eff R₁² R₂² / r²
```

Domain pressure `P_eff` changes. The shape does not.

G and M are not fundamentals. Gravity is `g = v²/R`, `ϟ = v²R/c²`. Dark matter, dark energy, ΛCDM, quarks, gluons, virtual particles, wavefunctions as primitives, fields as stuff, inflaton, and a first moment of time are not starting points.

**Gate (strict).** Recite the six sentences and the force law. If attraction, G, or M entered as a primitive, the constitution was not taken in. If a second force law was invented for gravity, it was fudged.

---

## 2. Scales — arranged as they sit

The lattice cell is `ℓ_P` — Axiom R1, the one dimensional seed (FLM06 Seed Theorem: exactly one action/mass/length anchor is unavoidable). Time is that cell divided by the relay rate.

`c` is the SI definition of that rate (exact since 1983). `k_B` converts kelvin to energy. `e` converts charge units. Those three are unit bridges.

Action, electron mass, and proton mass are **one mass/action seat** (FLM13): ℏ is the W=1 circulation quantum; the W=3 trefoil carries the proton. The seat’s role is derived. Its absolute magnitude is the baryon-count anchor that seat sits on.

`α` is hydrogen’s ground-state koppa rung: `k_H = c/v = 1/α` (PPT02, APS05). Same ladder as the Sun (`k_☉ = 686`). Not a dialed coupling.

`T_CMB` is the FIRAS reading of the bath now. A clock, not a constant of nature.

`a_0` is the length the hydrogen seat form sits on.

`sdt::laws::measured` stores CODATA/FIRAS numbers so the engine can compute. That is a lookup table of experimental facts.

**Compute — tick from the seed.**

```
ℓ_P = 1.616255×10⁻³⁵ m     (Axiom R1; CODATA Planck length as the seed)
c   = 299 792 458 m/s      (SI exact)
t_P = ℓ_P / c = 5.39124×10⁻⁴⁴ s
```

The second is already defined from caesium. This division is the consistency check that one cell per tick is the SI metre/second pair.

**Compute — hydrogen’s rung from the spectrum, not from a dial.**

APS05 Route B (no `m_e`, no `e`, no `h`): `α² = 16 · (Δν_2P / c R_∞)`, both frequencies measured.

```
1/α = 136.912     residual −0.0905% vs CODATA 137.035999084
pre-registered gate: ≤ 0.2%
```

APS05 Route A (Law V virial, proton-free hydrogen seat): `α = √(2 E_ion / m_e c²)`

```
1/α = 137.0726    residual +0.0267%
```

PPT02 seat closure, α never used: `v = √(2E/m_e)`, `k = c/v` → `k = 137.07` across Lyman, Balmer, Paschen. `ϟ_H = α² a_0 = r_e` exact.

**Gate (strict).** Route B’s residual is −0.0905%, inside 0.2%, and was not tuned toward CODATA. If you “corrected” 136.912 to 137.036 by inserting a coefficient, that is a fudge. The −0.09% is higher-order structure in the measured 2P splitting — reported, not removed. Hydrogen’s geometric origin is this koppa rung. It is not waiting on a torus eigenvalue.

---

## 3. Six laws

| Law | Name | Load-bearing identity |
|---|---|---|
| I | Relay throughput | `Φ = Nε`, `P_conv = Φ/ℓ_P³`. Inner shells cancel (T1). |
| II | Release cascade | domains of pressure after Clearing |
| III | Occlusion | the force law above — Coulomb, gravity, nuclear, one form |
| IV | Inertial mass | reorganisation cost of throughput; `m_inert = m_grav` from the same `V_disp` |
| V | Movement budget | `v_circ² + v² = c²` — special relativity as bookkeeping |
| VI | Vortex topology | W=1 electron, W=3 proton; W=2 not lasting |

Namespaces in `laws.hpp` match the table.

**Gate (strict).** Law III is occlusion inverse-square in the two radii. Law V is `v_circ² + v² = c²`. G is not an input. If a second inverse-square law was written for gravity with G in it, that is a fudge.

---

## 4. Lattice (Law I) — compute the pressure

FIRAS measured `T_CMB = 2.7255 K`. Radiation constant `a = 7.5657×10⁻¹⁶ J m⁻³ K⁻⁴` (from `k_B`, `c`, `ℏ` as the blackbody unit-bridge; TD06 / B07). Observed Clearing scale `R_CMB = 9.527×10²⁶ m` (class X — conditions the chain; not derived from first principles).

```
u_CMB  = a T_CMB⁴                              ≈ 4.172×10⁻¹⁴ J/m³
P_rad  = u_CMB / 3                             ≈ 1.391×10⁻¹⁴ Pa
N      = R_CMB / ℓ_P                           ≈ 5.894×10⁶¹
ε      = u_CMB · ℓ_P³                          ≈ 1.761×10⁻¹¹⁸ J
Φ      = N ε                                   ≈ 1.038×10⁻⁵⁶ J
P_conv = Φ / ℓ_P³ = N u_CMB                    ≈ 2.459×10⁴⁸ Pa
```

Theorem T1: every shell contributes `ε`; inner shells cancel; only the outer count N remains. Planck-face throughput: baryons exclude spheres `r = ℓ_P/2`; `Φ = R_CMB u_CMB ℓ_P²`. Gravity is that pressure shadowed. EMC01: `F ∝ P_conv V₁ V₂ / (ℓ_P² r²)`.

`koppa_per_baryon = ℓ_P² c m_p / ℏ` is C-flagged: CODATA `ℓ_P` still carries conventional G.

**Gate (strict).** Compute `P_conv = N u_CMB` from the three experimental inputs above. You should recover `≈ 2.459×10⁴⁸ Pa`. If you needed a fitted factor to land that pressure, the Law I chain was fudged. The class-X caveat stands: the *magnitude* inherits `R_CMB`. The *cancellation* (only N pays) does not.

---

## 5. Koppa, depth, gravity without G

```
k = c/v
z = 1/k² = (v/c)² = ϟ/r
ϟ = v² R / c² = R/k²
v = c √(ϟ/r) = c √z
z k² = 1
```

Inputs are measured **v** and **R**. `GM = c²ϟ` is algebra.

**Compute — identity.**

```
z k² = (v²/c²) · (c²/v²) = 1
```

**Compute — hydrogen and the Sun on one ladder.**

```
k_H   = 1/α = 137.035999084
ϟ_H   = α² a_0 = r_e = 2.8179403262×10⁻¹⁵ m     (exact)
k_☉   = 686.3
ϟ_☉   = R_☉ / k_☉² ≈ 1477 m
z_☉   = ϟ_☉ / R_☉ = 1/k_☉² = 2.123×10⁻⁶
```

Solar C1 spectral shift: `z = ϟ/R = 2.123×10⁻⁶` vs measured, **0.03%**.

**Gate (strict).** Show `z k² = 1` with no extra factor. Recover `ϟ_H = r_e` exactly from `α² a_0`. Solar C1 residual is 0.03%. Inserting G to “get gravity” is a fudge: `g = v²/R` already.

---

## 6. Movement budget = special relativity

```
v_circ² + v² = c²
γ = 1/√(1 − v²/c²)
dτ/dt = √(1 − v²/c²) = √(1 − z)     (also gravitational: z = ϟ/r)
E₀ = m c²
E² = (p c)² + (m c²)²
photon: v_circ = 0  ⇒  v = c, m = 0
```

At rest, `v_circ = c`. For a photon, `v = c`. Nothing exceeds `c` in translation. Inside a proton c-boundary, phase speed can be >c (`v(R_p) ≈ 1.83c`); that is circulation on a knot, not a signal.

**Gate (strict).** Rest ⇒ `v_circ = c`. Photon ⇒ `v = c`. If a particle at rest was given `v_circ ≠ c`, the budget was fudged.

---

## 7. Variable light speed — one z

Depth–closure is one quantity `z = ϟ/r`. Occlusion of convergence pressure (Law III) sets that depth. The same z is clock, local c, far-frame c, spectral shift, and Shapiro delay.

```
ℓ_P(r)     = ℓ_P,∞ · (1 − z)
c_local    = c_∞ · (1 − z)              hop closes
c_far      = c_∞ · (1 − z)²             hop AND tick close  (GOM22)
dτ/dt      = (1 − z)
z_spectral = z_emit − z_obs
Δt_Shapiro = ∫ dl/c_far − ∫ dl/c_∞
           ≈ (2/c) ∫ z dl               first order
```

There is no curved emptiness here, so none of the delay can be re-attributed to extra geometric path. Hop shortens and the tick dilates, so far-frame speed carries the factor twice. `c(1−z)` alone is **falsified** (exactly half the measured delay). Factor 2 is DERIVED.

**Compute — Earth’s rung is not the ceiling.**

```
z_gal = 3.5×10⁻⁷
c_∞   = c / (1 − z_gal) ≈ c + 105 m/s
```

**Compute — weak-field solar well (ϟ_☉ ≪ R_☉).**

```
c_far(R_☉) = c (1 − z_☉)² ≈ c − 1273 m/s
c_far(1 AU) ≈ c − 6 m/s          (AU/R_☉ = 215)
```

The reverse-map takes the photosphere as through-going speed **0** and Earth orbit as the match to local **c**. Weak-field SI is a crawl of metres per second. The identities at cosmological N are the rest.

Temperature, pressure, and far-frame speed are the same ladder:

```
1 + z  = T/T_CMB = (P/P_now)^{1/4} = 1/(1 − z_depth)
N      = T/T_CMB = λ_now / λ
P      = N⁴ P_now
c_far  = c / N²
```

Do not insert FIRAS `z = 1089` into `(1−z)²`. `z_depth` at Clearing is `1089/1090 ≈ 0.999`.

Wien `b = 2.8978×10⁻³ m·K` (B07, DERIVED). Present peak `λ_now = b/T_CMB = 1.063 mm`.

**Compute — FIRAS Clearing rung.**

```
z_release = 1089                         OBSERVED (FIRAS frame)
N         = 1090
T_release = T_CMB (1 + z_release) = 2970.8 K
λ         = λ_now / 1090 = 975 nm        near-IR
c_far     = c / 1090² = 252 m/s
z_depth   = 1 − 1/1090 = 0.999
```

**Compute — stop-death and pair threshold (same identities, no new knobs).**

| Peak | Band | N | c_far | Role |
|---|---|---|---|---|
| 1.063 mm | microwave | 1 | c | now |
| 975 nm | near-IR | 1090 | 252 m/s | FIRAS Clearing |
| 1571 nm | near-IR | 677 | 655 m/s | CR17b R=1 |
| 750–380 nm | visible | 1418–2798 | 149–38 m/s | behind the wall |
| 100 nm | UV | 1.06×10⁴ | 2.65 m/s | behind |
| 1.21 pm | gamma | 8.76×10⁸ | 3.9×10⁻¹⁰ m/s | Wien photon = 2 m_e c² |
| 4.30 fm | hard gamma | 2.48×10¹¹ | 4.9×10⁻¹⁵ m/s | P = P_eff |
| ℓ_P | — | 6.58×10³¹ | → 0 | lattice |

Down: radio → `λ = R_CMB` (static; +99.5 octaves). `c/√3` is the fluid ceiling on the way **down** (FD05). It is not the recharge target.

### Versus other models

| Model | What it does | SDT |
|---|---|---|
| Expanding space | c fixed; a(t); dark sector | No expansion. Redshift = emission depth ⊕ octave squeeze. |
| Free VSL | extra c(t) or c(r) knobs | `c_far` fixed by one z. |
| GR curvature | ds²; G, M; extra path | Same first-order numbers (`GM = c²ϟ`). Mechanism is relay slowdown. |
| Tired light | E loss; lines smear | Octaves do not compound like fog. EXCLUDED (CR07, sharp QSO lines). |
| ΛCDM SN distances | w, Ω_Λ | Pure z³ EXCLUDED vs Pantheon (CR12). |

**Gate (strict).** (i) `c(1−z)` alone gives half Shapiro — that form is falsified. The surviving law is `c_far = c(1−z)²`. (ii) Compute 975 nm from `λ_now/1090`. If you moved the wall into the visible by changing N, that is a fudge. (iii) FIRAS distortion < 50 ppm is the CMB gate: exceeding it falsifies the CMB mechanism.

---

## 8. Mass, occlusion, P_eff

Mass is the cost of re-routing influx around a displacement volume. Equivalence is the same `V_disp` in inertia and occlusion.

Engine hydrogen calibration (class E):

```
P_eff = 4 k_e e² / (π R_p² r_e²) = 5.225×10³¹ Pa
f     = P_eff / P_conv           = 2.125×10⁻¹⁷
```

Electropause closure (EMC04, delete-test passes, no Coulomb fit):

```
P_eff = m_p² m_e² c⁵ / (4 π α ℏ³)
```

Same magnitude, α-inherited. If either radius → 0, F → 0: no occlusion without a boundary.

**Compute — proton boundary from W+1.**

```
R_p ≟ 4 ℏ / (m_p c) = 8.412×10⁻¹⁶ m
measured R_p          = 8.414×10⁻¹⁶ m
residual              = 0.02%     (shared with the W+1 consistency, one fact not two)
```

**Compute — mass ratio clue (not a derivation).**

```
6π⁵ = 1836.118
m_p/m_e (CODATA) = 1836.15267
residual = 19 ppm
```

Unique simple `a·π^b` within 0.1%. PPT17 closes the physical assignment as
`6π⁵` point-electron 720-degree Bohr-closure tube volumes conserved into the
W=3 torus at `R_p`. Certification: COMPUTED shared-input construction, not an
independent prediction.

**Gate (strict).** Recover `R_p` from `4ℏ/(m_p c)` to 0.02% with no extra coefficient. `P_eff`’s *shape* is Law III. Its *magnitude* is CALIBRATED until `R_CMB` is derived — do not relabel E as C. Report 6π⁵ as a shared-input volume construction, not an independent prediction.

---

## 9. Topology and particles

Stable windings: **W=1** electron (unknot), **W=3** proton (trefoil). W=2 does not last. Neutrino: open W=0, straight, `μ_ν = 0` (PPT04). Neutron = proton + internal electron (structure; magnitude OPEN).

FLM13: `m_e · κ / 2π` agrees with ℏ to `1.000000001` (gate ≤ 10⁻⁶). IDENTITY-CLASS for the *role* (what ℏ is). No ℏ-free VALUE path exists (Seed Theorem). `{ℏ, m_e, m_p}` → one seat.

PPT01: R/a = √(q/p) for (p,q) knots; electron (1,1), proton (2,3); v_T = 0.632c, v_P = 0.775c. PPT06: phase speed 1.831c at R_p; traction T = 12 = 3(W+1).

**Gate (strict).** Proton is W=3. W=2 is not a lasting particle. μ_ν = 0 exactly. If a quark content was imported to “build” the proton, that is a fudge.

---

## 10. Atomic occupancy

Hydrogen = **proton centre**, not a packed seat. Kepler n-ladder is that centre.  
He-4 / He⁺ = **α centre** (two protons).  
Seats = D/T around the α (construction dictates electron pairing).

Lamb (form-switch, pair-form 2S → plane 2P), ACCEPTED OBSERVED:

| Centre | n=2 2S–2P | Tag |
|---|---:|---|
| H | 1057.845 MHz | OBSERVED, Lamb–Retherford |
| He⁺ | 14041.13 MHz | OBSERVED; not derived from H |

n⁻³ scales a Z=1 sticker; it does not derive Lamb. APS04 +0.761 MHz is a nuclear-geometry addend, not the bulk. Fabricated 1051.8 stays deleted.

Emission: `λ = 2L (c/v)` (APS07). `z k² = 1` on ionisation rungs. APS01: Rydberg from the velocity law, not an empirical fit.

**Gate (strict).** 1057.845 MHz is OBSERVED, not derived. He⁺ is a second centre sticker. If 1051.8 reappeared, that is a restored fabrication. If He⁺ was “derived” as H × Z³, that is a fudge.

---

## 11. Nuclear construction

For Z ≥ 2 (He-4 core):

```
n_t = A − 2Z
n_d = 3Z − A − 2
A   = 4 + 2 n_d + 3 n_t
Z   = 2 + n_d + n_t
```

Electron-capture isotopes: He-3 core alternate. No free neutrons in stable nuclei. Packer: α → D6 → D12 → T8 → … `dnn = 1.45 fm` frozen; do not retune to binding or RMS.

Fission is **flay** (unwrap jacket), not liquid-drop split (NP35). Binding MeV from packed contacts: UNDERDETERMINED (NP17b, NSEQ15).

**Compute — Fe-56.**

```
Z = 26, A = 56
n_t = 56 − 52 = 4
n_d = 78 − 56 − 2 = 20
A check = 4 + 40 + 12 = 56
Z check = 2 + 20 + 4 = 26
```

**Gate (strict).** Fe-56 is 1 α + 20 d + 4 t. If a free neutron was seated in a stable nucleus, the grammar was violated. If `dnn` was retuned to fit RMS or MeV, that is a fudge.

---

## 12. The eighteen research fields

Numbered as in `Investigations/`. Conclusions are the ledger’s own, not a polish. Vocabulary: excluded / ruled out / falsified / withdrawn. Shared-input (not an evidence-label “degenerate”).

### 00 — Master cascade

The fields are one stack. A result in FLM feeds PPT, EMC, APS, NP, GOM, CR, and the rest. The unpaid lattice solver (FLM10 / ROOT-SIM) is the bottleneck under OP-1/2/3, FLM09 isotropy residual, PPT07 wake integral, and GD05 rotation shape. Packer reopen (2026-08-13) sits on NP / FLM14 seats.

**Conclusion.** Dependency is real. Parallel “wins” that ignore an unpaid root are not independent evidence.

**Gate.** Name the shared root before treating two downstream PASSes as two facts.

### 01 — Foundations and lattice mechanics (FLM)

FLM02: GPI → F = ma, Newton I–III (IDENTITY relabel on m ↔ V_disp rows). FLM05: tick-by-tick contact/gap; V_torus ≠ V_disp. FLM06: Clearing route to derive ℓ_P **fails**; Seed Theorem proven; ℓ_P stays R1. FLM08: substrate = corner-sharing tetrahedral random network (coordination 4 = W+1); 27/27 geometry; “vacuum is this” is identification. FLM10: isotropy emerges; 1L+2T acoustic branches class C; decay exponent pending. FLM12: mass = field-resistance; computes no mass value; D1 unpaid. FLM13: ℏ ROLE native; VALUE open. FLM14: rotation is defect-carried; residence-law β unpaid.

**Conclusion.** The cell, the seed, and the substrate geometry stand. Absolute mass and the residence exponent do not.

**Gate.** ℓ_P is not derived from N ~ 10⁶¹. Any claim that it was is a fudge of FLM06.

### 02 — Particle physics and topology (PPT)

PPT01 vortex equilibrium resolved. PPT02: α is koppa of H, not a knot eigenvalue (resolved negative for “α from topology”). PPT04: μ_ν ≡ 0. PPT05 confinement / string tension class C. PPT06 v_phase = 1.831c, T = 12. PPT07/PPT17: 6π⁵ tube-volume assignment resolved as shared-input construction. PPT09 winding-stability fabrication **withdrawn**. PPT10/11 neutrino as straight light / flavour: OPEN.

**Conclusion.** Catalogue of lasting windings is W=1 and W=3. α’s origin is the hydrogen rung. Neutrino flavour is unpaid.

**Gate.** μ_ν = 0 with no magneton. Restoring PPT09 as a result is restoring a withdrawn fabrication.

### 03 — Electromagnetism (EMC)

EMC01: 1/r² structure class C; coefficient class E. EMC02: e is a unit bridge; no current dimension to manufacture coulombs. EMC03: attraction = shadow deficit, repulsion = focused surplus; one throughflow, two handednesses; throughpole. EMC04: electropause `P_eff` from centripetal requirement, delete-test passes.

**Conclusion.** Charge is handed redirection, not a substance. The force shape is occlusion. The magnitude still inherits α.

**Gate.** If “charge radius” was used as ontology, EMC was not taken in. Proton **boundary** radius is the object.

### 04 — Atomic physics and spectroscopy (APS)

APS01: Rydberg from the velocity law. APS03 drafting crossover 21.5% RMS; galactic pilot voided. APS04 native Lamb 1051.8 **withdrawn / fabricated**. APS05 α two routes, gates pre-registered, both PASS. APS06 emission ladder native; 13.6 eV IDENTITY; neutron-survey struck (empty counterexample class). APS11 Lamb pair-breaking: sign = incomplete-dyad strain.

**Conclusion.** Spectra are occupancy of centres. Lamb frequencies are OBSERVED stickers. Fine structure’s α² scaling is the second-order movement-budget term (`1 − √(1−α²) = ½α²` to +0.0013%).

**Gate.** APS05 Route B ≤ 0.2% and was not tuned. 1051.8 stays deleted.

### 05 — Nuclear physics (NP) and ATOMICUS

Grammar unique for Z ≥ 2. NP03A 284/287 valid (IDENTITY). Volume-price and gear-frequency binding **excluded**. NP12 `R = Z R_p` **excluded** (RMS hundreds of percent). NP17 deuteron contact 1.1% DERIVED; heavies unpaid. NP19 mass-defect reframe IDENTITY. NP20 1.83c seat; mass/moment need knobs. NP21 iron-at-floor **excluded** (geometry lands U-238). NP22 β-shape FAIL → OPEN. NP35 fission is flay, not drop-split. NP36 jacket Z from seating **excluded**. Packer `dnn = 1.45 fm` frozen.

**Conclusion.** Construction grammar stands. Contact MeV for packed nuclei is underdetermined. Fission unwraps a jacket.

**Gate.** Fe-56 = α+20d+4t. Retuning `dnn` to binding is a fudge. Liquid-drop split as mechanism is withdrawn (NP35).

### 06 — Gravitation and orbital mechanics (GOM)

GOM02 k-hierarchy 15/15. GOM04 Mercury 42.98″/cy from `ϟ = R/k²`; G, M absent; c-from-orbit +0.0009% withdrawn as a *derivation of c* (ephemeris already used c). GOM14 koppa-density 5.91% vs shuffled 50.74% class C (shared-prior confound not ruled out). GOM17 exchange ledger Sun–Jupiter ↔ H, 0.4%. GOM20 GPS clock transport. GOM22 Shapiro `c_far = c(1−z)²`. GOM23 straight line is bought with thrust.

**Conclusion.** One centripetal law from Earth-about-Sun to hydrogen. Shapiro is a speed integral.

**Gate.** Half-Shapiro (`c(1−z)` only) is falsified. Solar C1 0.03%. Importing G to “get” 42.98″ is a fudge of GOM02/GOM04.

### 07 — Cosmology and redshift (CR)

CR05 H₀-from-tensor **withdrawn**. CR07 `1+z = 2^Δn`, non-compounding; tired light excluded. CR08 exponential strain **falsified** on BAO. CR09 tension-as-radial-gradient **excluded**. CR12 pure z³ SN **excluded** (ΛCDM preferred on that catalogue). CR13 CMB coherence < 0.55%; 975 nm release. CR15 ionisation-at-N=1100 FAIL’d. R_CMB class X.

**Conclusion.** No expansion. Two redshift mechanisms, one sky. Dark energy has no row. Fire-time unpaid (see §14).

**Gate.** SN z³ is EXCLUDED. H₀ from P_conv as a closed derivation is withdrawn. FIRAS < 50 ppm remains the CMB gate.

### 08 — Galactic dynamics (GD)

Eclipse-saturation rotation **withdrawn** (stale). GD05 single-regime FAIL (RMS 66%); twin-regime borrows a MOND-shaped crossover; native shape OPEN. GD06 solar lensing 1.7517″ (0.10%) class C. Floor `a_0 = c H_0 / 2π` class C-flagged (inherits H₀).

**Conclusion.** Solar-limb bending stands as depth-gradient. Galaxy rotation as a finished native shape does not.

**Gate.** Do not cite the mock SPARC success. It was voided.

### 09 — Stellar astrophysics (SAR)

Le Sage absorption **excluded** (orders of magnitude). Solar luminosity from that route **excluded**. Blackbody `a` to 4.4 ppm class C. Main-sequence k-ordering ρ = −0.98 convergence; L∝M^3.5 circular. After-iron provenance: formation, not CMB.

**Conclusion.** Stars are local recyclers of Law II inflow. Domain `r = √(L / 4π F_CMB)` ≈ 20 800 AU for the Sun (lumiopause).

**Gate.** Compute the lumiopause from L_☉ and F_CMB with no extra scale. If a fitted Oort radius was inserted, that is a fudge.

### 10 — Fluid dynamics (FD)

FD01–FD10 executed. NS from relay coarse-graining class C. Circulation quantum κ = h/m_He to 0.020%. Kolmogorov −5/3 **derived** (class A on the exponent). `c/√3` native from P = u/3 (class A); boom ≡ Cherenkov. Bernoulli from Law V. Prefactors 6π, 2π, Blasius 0.664 flagged as borrows.

**Conclusion.** The lattice *is* a granular fluid. Two zero-parameter native wins: −5/3 and c/√3.

**Gate.** `c/√3` is the fluid ceiling, not `c_far → 0`. Conflating them is a fudge of the ladder.

### 11 — Thermodynamics (TD)

Entropy from counted microstates. k_B is the kelvin unit-bridge (TD02 delete-test). Blackbody from counted modes (TD06 / SAR02). TD09 freedom-ledger: T = 0.0624 MeV inside BBN deuterium bottleneck 0.06–0.09 MeV, zero fits. ε = hν asserted, not derived (TD-ROOT-3).

**Conclusion.** Heat is disordered throughput. k_B is not a mystery constant. Absolute ε = hν is unpaid.

**Gate.** k_B disappearing in natural units is the delete-test. If a fitted k_B was required to land Stefan–Boltzmann, TD06 was fudged.

### 12 — Condensed matter (CM)

SPEC. Superconductivity = phase-locked W=1 pairs; Φ₀ = h/2e native count. Conduction = occlusion drag. Phonons = FD05 compression waves. No magnetons. Unstarted as a suite; engine hooks exist.

**Conclusion.** The claim is posed. The suite is not yet the paid ledger.

**Gate.** Do not cite CM as executed PASS. SPEC is SPEC.

### 13 — Quantum foundations (QM)

Largest unpaid census item. Double-slit, Born, tunnelling, discrete spectra, spin: posed as wake mechanics. QM05 Bell / CHSH = 2√2: locality audit; may remain OPEN. ψ is not an input.

**Conclusion.** Duality is a shadow of a wrong premise. The deterministic reproductions are not all earned. Bell is allowed to stay OPEN.

**Gate.** Importing a wavefunction to “get” the fringe is a fudge. An OPEN on Bell outranks a fabricated local 2√2.

### 14 — Plasma and magnetism (PM)

SPEC. B ≡ ∇×w (summed handed wakes). ∇·B = 0 is a theorem (throughpole; monopole impossible). Lorentz = differential occlusion. No magnetons.

**Conclusion.** Magnetism is collective circulation of the same lattice. Suite unstarted as paid execution.

**Gate.** No µ_B. Native wake-circulation units only.

### 15 — Optics (OP)

n = 1/(1−z). Refraction and gravitational lensing are one gradient-index. OP01 solar-limb 1.75″. Photoelectric / Compton as emission↔vortex exchange (E55/E56). Solar lens-artifact (OP07) is the dated falsifier. An earlier OP01 lensing fabrication was withdrawn — current claim is the GOM01/depth-gradient 1.75″, not that withdrawn route.

**Conclusion.** Light is an emission. Index is closure.

**Gate.** Recover n = 1/(1−z) and the 1.75″ from z = ϟ/r. A photon-particle as ontology is a fudge.

### 16 — Chemistry (CH)

SPEC. Bonds = electropause sharing / transfer / delocalisation. Geometry = wake cancellation (period-2 map). No orbitals, no hybridisation as input. Rule 18 (chemistry = nuclear geometry) NP03E unrun.

**Conclusion.** The electropause is the atom-scale root (EMC04). Molecular suite unpaid.

**Gate.** Do not import sp³ to “get” 109.5°. Wake-balance is the posed mechanism.

### 17 — Reactions and thrust (RTM)

Opened 2026-08-03. Free fall follows the field’s line (not straight). A straight line is lattice-defined and is bought with thrust (GOM23). RTM01 3/3 gates PASS. RTM02 9/9 gates PASS: velocity derives mass (presence/volume invariant); expulsion ledgers; price floor at relay speed.

**Conclusion.** Newton I holds in the far field. Inside a depth gradient, straightness costs.

**Gate.** RTM01 3/3 and RTM02 9/9 are the executed gates. Do not generalise them to an unrun powered-spiral ledger.

---

## 13. Ledger

| Item | Status |
|---|---|
| Shapiro `c_far = c(1−z)²`; C1 solar redshift | DERIVED / 0.03% |
| APS05 α two spectroscopic routes | PASS inside pre-registered gates |
| Wien reverse-map MW → IR → gamma | COMPUTED |
| Heat death = Law III at P→0 | COMPUTED implication |
| Cycle fire-time | PENDING |
| R_CMB, H₀ from first principles | OPEN (CR05 H₀ withdrawn; R_CMB OBSERVED) |
| Lamb 1057.845 and He⁺ 14041.13 | OBSERVED |
| Lamb native 1051.8 | WITHDRAWN |
| SN z³ | EXCLUDED |
| Tired light | EXCLUDED |
| GD05 native rotation shape | OPEN (mock success voided) |
| P_eff magnitude | CALIBRATED |
| koppa_per_baryon without ℓ_P↔G | PARKED |
| E51 torus v_P/v_T as a formula for α | unpaid experiment — not the origin of 137 |
| 6π⁵ tube-volume assignment | RESOLVED construction; shared-input, 19 ppm correspondence |
| FLM14 residence β | UNPAID |
| Nuclear contact MeV | UNDERDETERMINED |
| QM Bell 2√2 local | OPEN |
| CM / PM / CH suites | SPEC |
| Rule 18 chemistry = nuclear geometry | NP03E unrun |

**Gate (strict).** Name one EXCLUDED result (SN z³ or tired light) and one OBSERVED sticker (a Lamb frequency). Promoting either EXCLUDED item to a win, or either OBSERVED sticker to a derivation, is laundering.

---

## 14. The life of the universe

The structure above is already calculated. What remains is to string it together.

We sit in the microwave. FIRAS: 1.063 mm, 2.7255 K. That is the operating pressure of the lattice, still arriving — not leftover light from a first moment.

Shapiro measured the solar pressure-speed profile of excluded Planck-length spheres, shell by shell. Light is late because it ran slower. Reverse-map: photosphere as through-going speed 0, Earth orbit as match to c. Weak-field: c minus 1273 m/s at the surface, c minus 6 m/s at 1 AU. Same identities at cosmological N.

Climb from here. Infrared is this cycle’s radiation wall (975 nm, N = 1090, c_far = 252 m/s). The Standard Model puts last scattering in the same band — same Wien arithmetic, not an imported mechanism. Visible colour sits behind that wall, impenetrable as a through-going signal. Ultraviolet next. Hard gamma is where through-going light stops: `c_far → 0`. Pair threshold first (1.21 pm); nuclear occlusion ceiling at 4.30 fm.

The other way: radio, then a wave the size of the stack — static (`λ = R_CMB`, one cycle per 100.7 Gyr on the class-X radius).

Take the cold direction all the way. T → 0, P → 0. Gravity is occlusion of that pressure. The push shuts off. Koppa wells flatten. Displacement volumes are no longer held. Matter expands. Seated structure breaks. That is not space stretching. The cells are still Planck-length.

The dump — unseated PRESS, including the SMBH queues — reloads the relay. The ladder runs the other way until `c_far → 0`. That is not a laboratory metre reading zero. `c/√3` is the infrared fluid ceiling on the way down after depinning. It is not the recharge target.

The wall opens. We meet infrared coming down. We sit in the microwave. The bang is this cycle’s wall, still arriving. There is no first moment. There is no last one.

When the door opens is PENDING. The chain is COMPUTED.

```
operating epoch     MW here; c = Earth's rung; gravity = occlusion of the bath
cooling             ladder down: radio → ELF → static; T → 0; P → 0
heat death          gravity shuts off; koppa wells flatten
matter expands      gravitational seats empty
structural breakdown  banked PRESS unseated
re-energisation     dump into the relay; ladder up through IR, visible, UV
c_far → 0           gamma / P_eff / ℓ_P
Clearing            depinning; we meet IR coming down; CMB = still-arriving wall
repeat
```

**Gate (strict).** Order: `0 K → gravity off → unbinding → recharge to c_far = 0 → Clearing`. If the bang was placed first as a singularity, or if fire-time was stated as derived, the chain was fudged. FIRAS < 50 ppm still gates the CMB mechanism.

---

## 15. Where to compute

| Need | Open |
|---|---|
| Numbers | `Engine/include/sdt/laws.hpp` |
| Cycle arithmetic | `Theory/07_Cyclic_Reiteration.md` |
| Scale status | `derivelist/README.md` |
| Rules | `Theory/00_Ruleset.md` |
| Depth / c_far | `Papers/Depth_Closure_Theorem/01_THEOREM.md` |
| Koppa | `Papers/an_argument_for_koppa.md` |
| Causal spine | `Papers/THE_CAUSAL_CHAIN_OF_SDT.md` |
| Nuclear grammar | `ATOMICUS/rules/On the Nature of Atomicus Rules.md` |
| Field stack | `Investigations/INVESTIGATION_STACK.md` |
| Benchmarks | `Benchmarks/B01_B25/benchmarks_suite.cpp` |
| People | `Papers/SDT_FOR_PEOPLE.md` |
| Theoretical model | `Papers/SDT_THEORETICAL_MODEL.md` |
| Lifecycle (web) | `Release/HTML_SDT_Website/universe-lifecycle.html` |

A number not in this file is in `laws.hpp` or a named assessment. The SoT is the header.

**Gate (strict).** Numerical truth is `Engine/include/sdt/laws.hpp`. If a figure here disagrees with that header, the header wins.
