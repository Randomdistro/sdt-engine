# Chemistry & Molecular Bonding — SDT electropause chemistry (CH01–CH07)

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (7 prompts, unstarted).
> Every prompt inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## The through-line

In SDT an electron is not a cloud and a bond is not an orbital. An electron is **held at the
Bohr radius by the electropause** — the pressure-balance boundary where the inward convergence
push equals the outward movement budget, derived kinematically with **no charge invoked**
([[project_electropause_peff_derivation]], EMC04). "Charge" is only shorthand for the **handed
redirection of the convergent phase** ([[project_cq47_repulsion_inverse]]); there is no charge
substance. From this single atom-scale result, all of chemistry is one move generalised:

- **Bonds = electropause sharing / transfer / delocalisation.** A covalent bond is two nuclei
  sharing one merged electropause; an ionic bond is an electropause handed off entirely; a
  metallic bond is electropauses delocalised into a lattice sea.
- **Molecular geometry = wake cancellation.** Shape comes from the **period-2 wake-cancel map**
  ([[project_foundational_ontology_influx_monopole]]): paired fore/aft wakes go silent, lone
  wakes stay active and repel. VSEPR angles, valence, and the octet rule are *targets* recovered
  from wake balance — never from sp³ hybridisation or LCAO.

These seven investigations test that claim end to end. Each reproduces a standard chemistry
result as a **convergence target** (never a borrowed input), narrates the mechanism in SDT
primitives (electropause, occlusion, movement budget, wake), and flags every gap OPEN rather
than fitting it.

## Dependency stack (build/run order — bottom feeds top)

```
CH01  Covalent bond = shared electropause     ← the CH root (rests on EMC04, EMC03, period-2 map)
  │
  ├─ CH02  Ionic & metallic = electropause transfer / delocalisation  (→ conduction CM02)
  │
  ├─ CH03  Periodic table & valence from shell wake-cancellation      (octet from period-2 map)
  │     └─ uses APS01 k-factor core radii; B–O / C–F / N–Ne pairing
  │
  ├─ CH04  Molecular geometry (VSEPR) from wake balance               (deepens CH01-H3)
  │     │     104.5° / 107° / 109.5° / linear / trigonal / octahedral
  │     │
  │     ├─ CH05  Reaction energetics & activation from wake reconfiguration  (TS = wake saddle)
  │     │
  │     └─ CH06  H-bonding & van der Waals from residual wake         (water anomalies)
  │
  └─ CH07  Molecular spectra (vibration / rotation) from bond-wake oscillation  (→ CM04, atomic)
```

## The suite

| ID | Title | SDT mechanism | Convergence target / falsifier |
|----|-------|---------------|--------------------------------|
| **CH01** | Covalent Bond as a Shared Electropause | two nuclei share one merged pressure-balance surface; bond = internuclear electropause well | H₂ R_e=0.741 Å, D_e=4.478 eV; VSEPR ladder; no orbital |
| **CH02** | Ionic & Metallic Bonding from Electropause Transfer | electropause handed off entirely (ionic) or delocalised into a lattice sea (metallic) | NaCl lattice energy ~787 kJ/mol; Na metallic R; ties conduction CM02 |
| **CH03** | Periodic Table & Valence from Shell Wake-Cancellation | period-2 wake-cancel map: paired fore/aft silent, lone active → valence = active-wake count | octet rule, valence, B–O/C–F/N–Ne pairing; period lengths 2/8/8 |
| **CH04** | Molecular Geometry (VSEPR) from Wake Balance | bond angles = wake-torque equilibria; lone-pair wake heavier than bond-pair | 104.5°/107°/109.5°/180°/120°/90° across many molecules; one ratio |
| **CH05** | Reaction Energetics & Activation from Wake Reconfiguration | ΔH = wake-cost difference; barrier = wake saddle; catalysis = lower-wake path | bond-energy ΔH signs; Eₐ ordering; Hammond/BEP-style correlation |
| **CH06** | H-Bonding & van der Waals from Residual Wake | weak bonds = residual/fluctuating wake *outside* the electropause | H-bond ~20 kJ/mol; water density max 4 °C; London ∝ 1/r⁶ scaling |
| **CH07** | Molecular Spectra (Vibration & Rotation) | bond-wake oscillation (vib) + whole-molecule wake rotation (rot) | IR ω(CO)~2143 cm⁻¹; B(CO); ν∝√(k/μ); ties atomic emission APS01 |

## Engine hooks (single source of truth: `Engine/include/sdt/laws.hpp`)

`law_III` occlusion (`F_occlusion`, `solid_angle_occluded`) is the bond/repulsion force law ·
`law_V` movement budget (`v_circ²+v²=c²`) sets the outward half of every electropause balance ·
**EMC04** electropause / `P_eff` (centripetal pressure-balance, charge-free) is the root ·
**EMC03** surplus-deficit sign (handed redirection — both bond signs, no charge substance) ·
**PPT06 / APS04** wake & multipole structure (ℓ=1/2/3) feeds geometry and spectra · **APS01**
k-factor core radii set per-element electropause size and group trends · the **period-2
wake-cancel map** ([[project_foundational_ontology_influx_monopole]]: paired fore/aft silent,
lone active; B–O / C–F / N–Ne) is the valence/geometry engine.

## Method discipline

Each investigation reports results with certification labels (`DERIVED` / `COMPUTED` /
`CALIBRATED(n)` / `OBSERVED` / `PENDING`) and the audit-spine class (A–F). The standard-chemistry
number — bond length/energy, a VSEPR angle, an octet count, a reaction enthalpy, a spectral
line — is always the thing to **reproduce**, never to borrow. Molecular orbitals, LCAO,
hybridisation (sp³ etc.), valence-bond wavefunctions, exchange integrals, and electron "clouds"
are **forbidden inputs** and the very pictures these prompts replace; measured molecular
properties (geometries, energies, spectra) are legitimate measured-unit targets/tools, like
spectral lines, but the mechanism must be SDT-native. A correct **novel** prediction beats a fit,
and a clean kill outranks a forced pass (R4).
