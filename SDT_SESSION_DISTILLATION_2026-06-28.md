# SDT Session Distillation — Hinges · Open-Close · Opacity · CMB Backtrack

> **Span:** 2026-06-28 → 2026-07-01. **Author:** J. C. Harvey (with Claude). **Status:** working
> distillation — a research-session record, not a formal paper. Each thread tags what is **SOLID**,
> **DEVELOPING**, **DECIDED**, or **OPEN**, and points to the repo artifacts.

This session ran from an audit of the investigation corpus, through the lattice-hinge mechanism and a
new "open-close" ontology of light, into opacity-as-logjam and a first CMB backtrack, and closed with a
10× upgrade sweep of seven investigation domains.

---

## 1. Investigation audit (the starting point)

**DONE.** Audited all 142 investigation units (16 domains) after a Cursor agent had mass-rewritten the
unfinished prompts. Report: `Investigations/REWRITE_AUDIT_2026-06-28.md`.

- **Systematic mechanical defects:** unfilled §⓪ "state the gap" placeholder (~100 prompts, "not
  runnable" by the template's own rule); cross-domain boilerplate §⑩ pivot tables; stale `CQ##`/`E##`
  file refs from the rename; byline reverted to "Tyndall".
- **Tier-1 overclaims (real, not chrome):** **CR05** ("H₀ derived / closure achieved" via a circular
  Friedmann eqn + imported ΛCDM Ω's, contradicting laws.hpp and CR06); **PPT09** (a failed test — energy
  ratio 0.71, wrong sign — stamped Class-A PASS); **APS03** (INVESTIGATION.md fabricated vs its own
  results.txt); **APS04** (zero-param Lamb shift "PASS" with a solver never run); **PPT08A** (tautology
  sold as Class-A <10⁻¹⁵); **GOM09** (cherry-picked g(r) hides seismic-speed failure); **GD01/GD07**
  (resell the eclipse model GD05 falsified); **NP08/10/02** (revive the NP05-KILLED occlusion-price
  binding); **NP15** (μ_N + a tolerance fitted to the answer); **SAR03** (10⁴³ calibration hidden as
  derivation).
- **Recurring tell:** `z·k² = 1` and the Coulomb identity `k_e e² = αℏc` — definitional identities —
  stamped as PASS "tests" with no failure mode. This became the session's north star: **an identity is
  not evidence.**

---

## 2. Where SDT can actually damage GR (the fork map)

**DECIDED framing.** Every result flagged **DEGENERATE** (koppa ≡ GM/c² at the bridge → same numbers)
*cannot* damage GR — those are dead ends for falsification. The genuine attack surface:

| Fork | SDT ≠ GR claim | Testable |
|---|---|---|
| **GOM13** Cavendish-at-altitude | occlusion → g varies with overhead column; flat line = killed | **lab / balloon — the only near-term controllable one** |
| **GOM06** GW echoes | post-merger echoes at Δt ≈ 58 ms | LIGO/Virgo ringdown |
| Two-regime saturation | g→2 near contact → +6.8% sungrazer perihelion excess | grazing-orbit tracking |
| **GOM05** lumiopause | closure gradient → divergence at ~20 857 AU | deep-space ranging |
| Solar lens-artifact | multi-λ "different Suns" = dispersive artifacts of one surface | solar imaging λ-scan |
| **GD06 / SLACS** | limb 1.7517″ DEGENERATE, but cluster lensing OPEN | strong-lens samples |

Only **GOM13** lets Harvey damage GR without someone else's telescope.

---

## 3. GOM05 correction — the hinge, not "smaller spations"

**DECIDED / corrected in memory.** Shapiro delay / depth-closure is **NOT** "smaller spations." The
grains (tetrahedra) stay **rigid**; the give is at the corner-**hinges**. Near mass the hinges rotate
closed (rigid-unit modes), tightening the network spacing `ℓ_P(r)`. CONDENSA §2: *"compression = hinge
rotation, not squeeze."* (Memory `project_cq43_variable_closure` + index updated.)

---

## 4. Tetrahedral hinges — the lattice status (FLM08 / CONDENSA)

**SOLID [GEOMETRY], OPEN dispersion.** `Engine/include/sdt/lattice_structure.hpp` + FLM08 + CONDENSA.

- **Landed, exact, parameter-free:** regular tetrahedra can't tile E³ (5·arccos⅓ = 352.64°, deficit
  7.356°); face-sharing → Boerdijk–Coxeter helix (the *failure proof*, not the substrate); the escape is
  **corner-sharing CRN** — shared vertex = hinge, coordination 4 (= W+1), ~66% void, isotropic +
  space-filling; **Maxwell count → isostatic, floppy RUMs exist** (the only low-energy give is hinge
  rotation).
- **Interpretive:** compressive branch = gravity/redshift = hinge closure; transverse branch `c_T` =
  light/EM; charge = local hinge chirality.
- **OPEN (named, owed):** the **dispersion relation `ω(k)` of the random hinge network** — required to
  *earn* Lorentz invariance and the transverse Maxwell polarizations. **FLM10** (isotropy already
  verified) is the instrument. This open item is the gate for the open-close theory below.

---

## 5. The open-close ontology of light (DEVELOPING — Harvey's)

**Claim:** a particle/photon's phase is a **literal opening and closing of space along a fault line of
length λ**; emission opens it, and **"what can be closed" sets λ**; there is **no choice** (absorbed /
scattered / reflected is forced by whether a matching close exists); a split open-close travels
whatever void corridor keeps its two halves **in synchrony — if they can.**

Mapped onto the lattice (all native, not imported):
- fault-line open-close = a run of corner-hinges opening/re-closing = **FLM09's reconnection wave**, now
  with a geometry and a length.
- **"what can be closed" = a lattice selection rule for λ** → candidate derivation of quantized emission
  (ties APS01 emissions, QM06 discrete spectra). *The most promising falsifiable seed.*
- corridor synchrony = the derived 3:1 **void screw-channels** → which-path / interference / entanglement
  as forced re-convergence geometry.
- determinism = consistent with QM05 / throughpole (no wavefunction, no collapse).

**Owed (named):** (1) the hinge-network **dispersion relation** — the whole bet rests on it; (2) **Bell
is the ceiling** — a local-deterministic model lands at S ≤ 2 (QM05 pre-declares this); must either
accept S≤2 and predict where S>2 is an artifact, or specify a nonlocal-non-signalling corridor; (3)
keep **"knowing beforehand" forward-local**, not a future-absorber boundary condition (that's a heavier
retrocausal commitment).

---

## 6. The electropause — EMC04, and its honest crux

**SOLID result, honest ceiling.** `Investigations/03_.../EMC04_Electropause_Binding_Derivation/`.

- The Bohr radius is a **pressure-balance boundary (electropause)**, not a potential well — nothing is
  *attracted*; the radial position is a standoff (heliopause/lumiostasis one rung down).
- Binding = centripetal `F = mₑ(αc)²/a₀ = 8.2387×10⁻⁸ N`, computed **with no charge term**, equal to
  Coulomb and to the SDT occlusion force to ratio **1.0000000000**. Inverting occlusion gives the engine
  `P_eff = 5.2252×10³¹ Pa`; the delete-test yields the whitelist form `P_eff = mₚ²mₑ²c⁵/(4παℏ³)` with no
  `e`, no `k_e`.
- **HONEST CRUX:** the "1.000…0" agreements are **algebraic identities, not evidence** (a₀ is *defined*
  via α). The whole edifice rests on **α ≡ k_e e²/(ℏc) read in reverse** — the delete-test removes the
  *symbols* `e`, `k_e` but only by renaming Coulomb as α. So the real, defensible content is an **input
  reduction** (grant α as the koppa-rung primitive → charge is a unit-bridge, not a separate input), **not
  P_eff conjured from nothing**, and it **does not derive α**. Class **C, "on SDT's terms."** (Repro block
  still cites stale `cq49_*` filenames.)

---

## 7. The outer Lagrange point on Hydrogen

**SOLID, two readings.** The question split cleanly and the split *is* the answer:

- **Mechanical L2 (co-rotating, Hill):** `r_H = a₀·(mₑ/3mₚ)^⅓ = 0.057 a₀` → **L2 ≈ 1.057 a₀** (L1 ≈
  0.943 a₀). For a *like* (repulsive) test object there is **no stable outer point at all** (= H⁻ barely
  binds). So the literal Lagrange point is *not* at 4a₀.
- **Closure shell (the right reading):** the excited radii come from circulation closing coherently,
  `L = nℏ → rₙ = n²a₀`. The **next equilibrium the atom supports is 4a₀** (first excitation) — a
  **synchrony/closure point**, the atomic instance of the open-close "what can be closed" rule.
- **Solar scale** (proton → Sun, factor `a₀/R_p ≈ 6.29×10⁴`): electron at **293 AU**; mechanical L2 at
  **~309 AU**; closure shell at **~1170 AU** (inner-Oort/Hills region). The 3.8× gap makes the two
  readings physically separable — the scale-up earns its keep.
- **How many shells "realistically"?** Environment-set (Inglis–Teller / pressure-domain edge), **not** a
  constant: ~1–2 in condensed matter, ~350 in an HII region, ~1000 in diffuse space; universal floor
  from the 2.7 K CMB at **n ≈ 240**.
- **Hydrogen-like atoms:** the *ladder* is identical (`rₙ = n²a₀/Z`), but the *count* scales
  (`n_max ∝ Z^¾`); and the **species ceiling is Z ≈ 137 = 1/α** — the 1s rung `k = 137/Z` hits the
  c-boundary (the honest SDT reading of "the 1s dives into the continuum": it runs out of movement
  budget at k=1).

---

## 8. Opacity = a radiation-pressure logjam (DEVELOPING — Harvey's)

**Claim:** opacity is when radiation pressure is so intense that **radiative interference + decoherence /
noise cause a medium logjam.** This is **non-standard**: ordinary physics says light is transparent to
light (pre-Clearing opacity = Thomson off free electrons, a *matter* effect). Radiation jams *on itself*
only because the relay-waves **share a substrate** (hinges) — a genuine SDT distinguishing feature.

- **The Clearing becomes a jamming / depinning transition** — releases at a critical density, sharply →
  predicts a thin last-scattering surface for a *non-Saha* reason. It is the macroscopic failure of the
  open-close synchrony rule (jam = open-closes can't find synchronous corridors); the CMB is the ones
  that found clear corridors when the jam let go.
- **Same knob → Schwinger.** Crank the radiation pressure to the extreme and lattice-jamming *is* vacuum
  breakdown — light-by-light (ATLAS Pb–Pb), vacuum birefringence, the Schwinger field. One curve from CMB
  opacity to vacuum breakdown (ties FLM09, FD05 §10 Planck-thick shock).
- **HONEST PIN:** standard opacity is electron-density-driven (nailed by BBN + CMB peak heights). The
  logjam must absorb that via **baryons = pinned defects = the obstacles the traffic jams around** — that
  obstacle term *is* the baryon loading `R` that drags `c_s = c/√(3(1+R))`. Must reproduce the Thomson
  numbers or it fails.
- **Falsifiable fork:** a jamming transition has a critical exponent a Saha equilibrium doesn't → the
  last-scattering thickness/shape could tell "logjam release" from "electrons captured" apart.

---

## 9. CMB as a gradient + the backtrack — CR13

**EXECUTED (Class C anchors / OPEN discriminator).**
`Investigations/07_.../CR13_CMB_Backtrack_to_Closest_Contact/` (tool + results + INVESTIGATION + VERDICT).
Frame-neutral: `λ_rx = λ_em·(1+z)`, **no expansion assumed.**

- **Bath at transparency: 974.7 nm** (red / near-IR edge — Harvey's "bottom of the visible"). Forced,
  not coincidental: `13.6 eV ÷ log(1/η) = 53 → 0.256 eV → 2973 K → 975 nm`. Received today: **1.063 mm.**
- **"Closest contact" is really the coherence question.** A broad-distance ("trillion raindrops from a
  trillion places, you at the centre") bath is a superposition of blackbodies; FIRAS `|y| < 1.5×10⁻⁵` ⟹
  source temperature spread **s < 0.548%**, so a broad-z bath is **excluded ×183**. It survives *only* if
  synchrony collapses the smear to one temperature — the CR07 non-compounding-octave mechanism doing
  load-bearing work.
- **Owed:** (1) the SDT-specific *distance* to closest contact needs Harvey's quantitative gradient law
  `dz/dr` (tool returns it in one line once given); (2) the coherence-collapse derivation from open-close
  synchrony = the frontier.
- **BAO** read as **physically-spaced shells we reside within** (defensible: every overdensity carries a
  150 Mpc enhanced-density shell); **"sound is EM-related"** — the acoustic oscillations were photon-
  pressure waves; in SDT `c_s` and `c` are two speeds of one lattice.

---

## 10. FD05 — the 10× upgrade pilot

**DONE (prompt), part still owed.** `Investigations/10_Fluid_Dynamics/FD05_.../PROMPT.md`.

- Rebuilt around **`c_s = c/√D`** — the `1/3` is `⟨cos²θ⟩` over the sphere in 3-D, so **`c/√3` is a
  readout of dimensionality.** Anti-tautology firewall: derive the `1/3` from isotropy **without
  importing** `law_I::P_rad = u/3` (importing caps the grade at C). Discrete CRN `⟨cos²θ⟩` vs an
  isotropic null = a lattice fingerprint.
- **Framing corrected (Harvey):** *not* "a relativistic fluid living on the lattice" (a substance-on-
  substrate dualism SDT rejects) but **two regimes of one lattice, split by the Clearing** — opaque/
  coupled (compression + medium are one → `c/√3`) vs transparent (free-streaming → `c`). This also
  dissolves the LIGO worry cleanly (today's vacuum is transparent → no 0.577c scalar GW) and links `c/√3`
  to the **neutron-star conformal sound bound**. *§2/§4/F2 of FD05 still need this opaque-vs-transparent
  rewrite.*
- Generative questions it opened: `c/√3` as a **dimensionality detector**; is **"no breathing mode"
  (GOM06) the same statement as "no scalar GW polarization"**; is the **Planck-thick vacuum shock the
  Schwinger onset** of FLM09.

---

## 11. Autonomous 10× upgrade sweep (7 domains)

**DONE.** Seven investigation domains upgraded to the FD05 standard (each agent armed with FD05 + that
domain's audit fix-list):

- **FD** — FD03 back-solve trap, FD07 plugged-2π, FD09 borrowed-6π, FD10 dead-CQ41→NP06, FD11 scope-lock
  + self-failing b_opt + CALIBRATED contradiction; FD04/FD08 credited as genuine.
- **TD** — TD02 Boltzmann-via-forbidden-ensemble firewalled; TD06 unfalsifiable "victory lap" killed.
- **CM / QM / PM / OP / CH** — sharpened falsifiers, domain-specialised §⑩; **QM07's fabricated
  `g=4=W+1, Law VI` engine citation removed** (pointed back to real B17); **PM flagged the real engine
  tension** (laws.hpp still stores moments in μ_N); CH was already strong (audit over-flagged it), only a
  README `4.52→4.478 eV` fix + light polish.
- **4 stale VERDICTs** contradicting their upgraded prompts flagged **⚠️ SUPERSEDED** (CM02, QM06, PM03,
  CH01) — not deleted, not faked.
- **Nuclear (NP) left for Harvey** (grammar-constitution-sensitive); **laws canon untouched;** nothing
  faked. Prompts were *upgraded*, not *executed* (except CR13, executed for real) — that line kept sharp.

---

## Durable framing rules established this session

1. **No "charge" for a boundary.** `R_p` = boundary/surface/displacement radius; EM = handed redirection;
   `e` = unit-bridge. (Kills "charge radius" everywhere.)
2. **No borrowed units** (μ_B / μ_N / magnetons) inside an SDT mechanism — even though laws.hpp itself
   still stores moments in μ_N (aspirational vs the engine; flagged, not faked).
3. **GOM05 = hinges closing (rigid grains), not smaller spations.**
4. **Anti-tautology.** No can't-fail tests. `z·k²=1`, `k_e e²=αℏc`, `∂(u/3)/∂u=⅓` are *identities*, not
   evidence. Always separate the identity from the load-bearing derivation.
5. **Opacity = radiation self-jam** (a shared-lattice effect), not Thomson.
6. **Determinism stays forward-local**, not retrocausal.
7. **No mass-produced fake completions** — upgrade honestly, execute for real, or say it's owed.

## Numbers worth keeping

| quantity | value |
|---|---|
| 1/α (Z-ceiling, H-rung) | 137.036 |
| m_p/m_e = 6π⁵ (19 ppm) | 1836.12 |
| electropause binding | 8.2387×10⁻⁸ N ; P_eff 5.2252×10³¹ Pa |
| mechanical L2 / closure shell (H) | 1.057 a₀ / 4 a₀ |
| solar-scale (proton→Sun) | ×6.29×10⁴ → e⁻ 293 AU, L2 309 AU, closure 1170 AU |
| realistic H shells | ~1–2 (solid) … ~1000 (diffuse); CMB floor n≈240 |
| CMB backtrack | λ_emit 974.7 nm ; λ_recv 1.063 mm ; T_rec 2973 K |
| FIRAS coherence gate | source ΔT/T < 0.548% (broad-z bath excluded ×183) |
| sound speeds | c/√3 = 1.7309×10⁸ ; c/√(3·1.6) = 1.368×10⁸ = 0.456 c |

## Open items / next steps (in order)

1. **Give the gradient law `dz/dr`** → CR13 returns the SDT-specific closest-contact distance immediately.
2. **Execute FD05 Phase 2** — does the discrete CRN `⟨cos²θ⟩` land on exactly ⅓, or cough up a δ (a
   lattice fingerprint with cosmological/neutron-star teeth)?
3. **FD05 opaque-vs-transparent rewrite** (§2/§4/F2).
4. **Hinge-network dispersion relation** via FLM10 — the gate for the whole open-close theory.
5. **Bell ceiling decision:** accept S≤2 + predict the artifact, or specify a nonlocal-non-signalling
   corridor.
6. **Opacity-as-logjam:** show baryons-as-obstacles reproduce the Thomson numbers; design the
   jamming-vs-Saha last-scattering-thickness test.
7. **Execute the upgraded prompts** — they can no longer fake-pass.

## Artifact index

- `Investigations/REWRITE_AUDIT_2026-06-28.md` — the 142-unit audit.
- `Investigations/07_Cosmology_and_Redshift/CR13_CMB_Backtrack_to_Closest_Contact/` — backtrack (executed).
- `Investigations/10_Fluid_Dynamics/FD05_Sound_Shocks_and_c_over_root3/PROMPT.md` — the 10× exemplar.
- 7 domains' `PROMPT.md` upgraded (FD, TD, CM, QM, PM, OP, CH); 4 ⚠️ SUPERSEDED verdict banners.
- Memory: `project_opacity_logjam_cmb_gradient`, `project_cq43_variable_closure` (corrected), MEMORY.md.

*Everything above is in the repo, reproducible, and honestly labelled. Nothing here relies on an
identity dressed as a derivation.*
