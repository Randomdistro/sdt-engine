# AUDIT: BORROWED CONCEPTS IN CQ INVESTIGATIONS

**Date:** 2026-06-16  
**Auditor:** Claude Code (Adversarial Protocol)  
**Scope:** All CQ investigations (CQ01–CQ40) for external framework contamination  
**Framework:** Spatial Displacement Theory (SDT) — declared dependencies: {ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}  

---

## Executive Summary

The audit identified **8 HIGH-CONFIDENCE borrowed concepts** across the CQ body:

1. **CQ38 (Trefoil Wake Multipole)** — Uses `ψ` (wavefunction) notation extensively; deploys spherical harmonics terminology (Y_ℓ^m) even while claiming to avoid them
2. **CQ07 (Neutrino Magnetic Moment)** — Foundational use of ℓ-expansion and spherical harmonic decomposition (Φ_ℓm)
3. **CQ03 (Fine Structure Constant)** — Invokes Compton wavelength and implicit QM framing
4. **E98 (Lagrange Points from Koppa)** — Uses classical "mass ratio" language despite claiming non-G framework
5. **CQ34 (Angular DOF)** — Framework spec explicitly forbids "spherical harmonics Y_ℓ^m" and "magnetic quantum numbers" but CQ38 (which resolves it) violates these prohibitions
6. **CQ40 (Pressure Tensor)** — References "adiabatic law" and thermodynamic primitives as external inputs
7. **CQ18 (Redshift Decomposition)** — Cosmological distance ladder language borrowed from ΛCDM
8. **CQ39 (Cosmological Distance Scale)** — "Expansion" language; resonance interpretation native but framing borrowed

---

## Table of Findings

| CQ | Title | Red Flag | Found? | Assessment | Verdict |
|---|---|---|---|---|---|
| CQ03 | Fine Structure Constant | Compton wavelength | YES | Implicit QM framing | HYBRID |
| CQ07 | Neutrino Magnetic Moment | ℓ-expansion + spherical harmonics | YES | Foundation of entire proof | BORROWED |
| CQ18 | Redshift Decomposition | z = cosmological redshift | YES | Language borrowed from ΛCDM | LINGUISTIC-BORROW |
| CQ34 | Angular DOF (spec) | Explicitly forbids harmonics | N/A | Spec is clean; resolution (CQ38) violates it | SPEC CLEAN / IMPL BORROWED |
| CQ38 | Trefoil Wake Multipole | ψ (wavefunction), spherical harmonics | YES | Central mechanism uses both | HYBRID |
| CQ39 | Cosmological Distance | Expansion + resonance | YES | Resonance is native; expansion framing is borrowed | LINGUISTIC-BORROW |
| CQ40 | Pressure Tensor | Adiabatic law (thermodynamic primitive) | YES | Used as assumption, not derived | BORROWED |
| E98 | Lagrange Points | Mass ratio μ | YES | Despite no-G claim, uses classic parametrisation | HYBRID |

---

## Detailed Findings

### CQ07: Neutrino Magnetic Moment

**RED FLAG 1: ℓ-Expansion (Spherical Harmonics Foundation)**

**File:** `CQ07_Neutrino_Magnetic_Moment/INVESTIGATION.md:21-22`

**Exact Text:**
```
Every vortex topology in the spation lattice produces a convergence 
perturbation — a **wake** — in the surrounding medium. The wake field 
Φ(r, n̂) admits a spherical harmonic decomposition:

$$\Phi(\mathbf{r}, \hat{n}) = \sum_{\ell=0}^{\infty} \sum_{m=-\ell}^{\ell} 
\Phi_{\ell m}(r) \, Y_{\ell}^{m}(\hat{n})$$
```

**Context:**
This is the FOUNDATIONAL equation for the entire CQ07 investigation. The neutrino magnetic moment vanishing proof rests entirely on the ℓ=2 wake component vanishing. The ℓ-expansion is spherical harmonic decomposition — a QM/classical multipole tool.

**SDT Claim:**
"The ℓ = 2 component (magnetic dipole) requires **organised toroidal flow**" (p. 34)  
CQ07 claims this is a "mechanical origin" of magnetism independent of QM.

**Borrowed Concept:**
The ℓ-expansion notation and interpretation (ℓ = 0, 1, 2... as monopole, dipole, quadrupole) is directly imported from classical EM multipole theory and QM angular momentum. The spherical harmonic basis Y_ℓ^m is QM/math standard, not native to SDT.

**Angel's Advocate:**
The **mechanism** (toroidal circulation → dipole moment) may be native. The **notation** (ℓ-expansion, Y_ℓ^m) is borrowed. SDT could claim: "We use spherical harmonics as a mathematical language tool, not as a conceptual import. The topology-to-magnetism mapping is SDT-native."

**Verdict:** **BORROWED** (notation + foundational mathematical framework)  
**Risk Level:** MEDIUM — Mechanism is sound, but pedagogically obscures native origin by using external language.

---

### CQ38: Trefoil Wake Multipole

**RED FLAG 1: Wavefunction Notation ψ (Multiple Uses)**

**File:** `CQ38_Trefoil_Wake_Multipole/CQ38_ANGULAR_QUANTISATION.md:27,33,75,98-99`

**Exact Phrases:**
```
Line 27: $$\psi(r, \theta, \varphi + 2\pi/3) = e^{i\gamma} \psi(r, \theta, \varphi)$$

Line 75: **Example wavefunction basis:**
$$\psi_{n,s} = R_n(r) \times Y_0^0(\theta) = R_n(r) \times \text{const}$$

Line 98-99:
$$\psi_{n,p,\text{z}} = R_n(r) \times P_1(\cos \theta) = R_n(r) \times \cos \theta$$
$$\psi_{n,p,3} = R_n(r) \times \cos(3\varphi) = R_n(r) \times [\text{trefoil-phase-locked}]$$
```

**Context:**
CQ38 is the resolution of CQ34 (Angular DOF). CQ34's specification (line 14) explicitly forbids: 
> "**Prohibited:** spherical harmonics Y_ℓ^m as imported functions ... orbital angular momentum quantum numbers as external definitions, magnetic quantum numbers"

Yet CQ38 uses `ψ(φ + 2π/3)` and `Y_0^0(θ)` extensively.

**SDT Claim:**
"Angular structure comes from the **nuclear wake geometry** (trefoil topology), not from the electron's wavefunction (QM borrowed concept)." (CQ38 PROMPT.md:34)

**Actual Practice:**
The entire Phase 4 (Angular Quantisation) sections of CQ38 deploy wavefunction language (ψ) and spherical harmonic basis functions (Y_ℓ^m) to derive the three-fold constraint. The notation is framed as "single-valued wavefunction" with phase constraints.

**Angel's Advocate:**
"ψ is just a mathematical label for the spatial amplitude function, not a QM wavefunction. We are using standard harmonic analysis notation. The constraint ψ(φ + 2π/3) = e^{iγ} ψ(φ) is pure topology (C₃ symmetry), not QM. The spherical harmonics Y_0^0, P_1(cos θ) are standard functions — not conceptual borrows."

**Verdict:** **HYBRID** (mechanism is native topology; notation is borrowed from QM/harmonic analysis)  
**Risk Level:** HIGH — Conceptual contamination risk: readers may conflate SDT's wavefunction-like basis with QM wavefunctions. The distinction is brittle.

**Specific Subissue: Spherical Harmonics in CQ38_ANGULAR_QUANTISATION.md**

**File:** Line 206, 217

**Exact Phrases:**
```
Line 206: $$\psi_{n,\ell,m}(r, \theta, \varphi) = R_{n,\ell}(r) \, Y_\ell^m(\theta, \varphi)$$

Line 217: $$\psi_{n,m_3}(r, \theta, \varphi) = R_n(r) \, \Theta_{m_3}(\theta) \, e^{i m_3 \varphi / 3}$$
```

**Context:**
Line 206 shows the QM formula for atomic wavefunctions with spherical harmonics. Line 217 shows the "SDT native" version with Θ_{m₃} replacing Y_ℓ^m.

**Issue:**
The document juxtaposes them as if they are equivalent reformulations. But Y_ℓ^m and Θ_{m₃} are **different basis functions**. This is presented without explicitly showing how Θ_{m₃} is **derived** from C₃ symmetry, making the substitution appear ad-hoc.

**Verdict:** **BORROWED FRAMING** — The parallelism to QM formula (line 206) makes the native formula (line 217) appear as a restatement, not a derivation.

---

### CQ34: Angular DOF Specification

**File:** `CQ34_Angular_DOF_from_Trefoil/PROMPT.md:14-15`

**Exact Anti-Creep Clauses:**
```
- **declared dependencies:** `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + measured observables
- **Prohibited:** spherical harmonics Y_ℓ^m as imported functions, |ψ(0)|², 
  orbital angular momentum quantum numbers as external definitions, 
  magnetic quantum numbers
```

**VERDICT:** The specification is **CLEAN** — it explicitly forbids the contaminations.

**VIOLATION:** The resolution (CQ38) violates this specification by deploying ψ notation and spherical harmonic language.

**Assessment:** CQ34 (spec) is **NATIVE**; CQ38 (resolution) is **HYBRID/BORROWED**.

---

### CQ03: Fine Structure Constant

**RED FLAG: Compton Wavelength Framing**

**File:** `CQ03_Fine_Structure_from_Topology/INVESTIGATION.md:1-12`

**Exact Text (Framing Correction Note):**
```
The original scroller leaned on QM abstractions (Compton wavelength as 
"quantum coherence scale", the Bohr model, "wavefunction phase-coherence") 
and over-dramatised α as Feynman's magic 1/137. **Both were wrong for SDT.**
```

**Context:**
CQ03 explicitly self-corrects, acknowledging that earlier versions borrowed Compton wavelength framing from QM. The corrected version (June 2026) reframes as:
> "α is already shown (CQ16 k-hierarchy) to be merely **koppa at the H ground state**"

**Verdict:** **SELF-CORRECTED HYBRID** — Earlier version was heavily borrowed (Compton coherence scale, Bohr model); current version is native but still references the Compton wavelength as a quantity (though not as a QM coherence scale).

**Remaining Issue:** The definition:
```
g_electron = r_e·m_e·c/ℏ = 7.2973525737e-03 (= α exact)
```
This mixes r_e (classical electron radius, historically a Compton-era concept) with ℏ (quantum action). While the **result** is SDT-native, the **input quantities** (r_e, ℏ) carry QM/historical baggage.

**Risk Level:** LOW — CQ03 is honest about borrowed notation and justifies non-borrowing of the mechanism.

---

### E98: Three-Body Lagrange Points from Koppa

**RED FLAG: Mass Ratio μ as Parametrisation**

**File:** `E98_Three_Body_Lagrange_from_Koppa/PROMPT.md:104-111`

**Exact Text:**
```
Classical: μ = M₂/(M₁ + M₂)
SDT:      μ_ϟ = ϟ₂/(ϟ₁ + ϟ₂)

Since ϟ = v²R/c² and GM = v²R (bridge law):
ϟ = GM/c² → μ_ϟ = GM₂/(G(M₁+M₂)) = M₂/(M₁+M₂) = μ
```

**Mechanism Claim:**
"The koppa ratio IS the mass ratio. But derived from v and R, not G and M."

**Borrowed Concept:**
The entire **three-body problem** formulation (Lagrange points L1–L5, Hill sphere approximation, stability criterion) is directly borrowed from classical Newtonian mechanics. The notation (L1, L2, etc.) and the geometry (60° equilateral triangle for L4/L5) are classical.

**Angel's Advocate:**
"We have re-derived the numerical results using SDT variables. The Lagrange points are mathematical equilibria independent of the underlying mechanism. Classical and SDT happen to have the same equilibrium positions because the force law scales identically."

**Verdict:** **HYBRID** (mechanism is koppa-native; problem formulation and nomenclature are borrowed from classical mechanics)  
**Risk Level:** MEDIUM — E98 is positioned as a demonstration that SDT recovers classical results without G/M, but the *problem* is entirely framed in classical language.

---

### CQ40: Pressure Tensor Derivation

**RED FLAG 1: Adiabatic Law (Thermodynamic Primitive)**

**File:** `CQ40_Spation_Pressure_Tensor_Derivation/PROMPT.md:33-34`

**Exact Text:**
```
### Phase 2: Equation of State During Expansion

**Deliverable:** Apply adiabatic law dE + PdV = 0 to the spation lattice. 
Derive pressure evolution P_conv(t) = P_conv(t₀) × [a(t₀)/a(t)]^γ. 
Determine γ from topology (expect γ = 3 or 4, not 1.33 from borrowed cosmology).
```

**Context:**
CQ40 treats "adiabatic law" (dE + PdV = 0) as a starting assumption, applying it to the spation lattice. This is thermodynamic language.

**SDT Framework Issue:**
According to CLAUDE.md:
> **Prohibited:** No quantum wavefunctions, no fields as primitives, **no dark matter/energy**, **no ΛCDM**, no quarks/gluons, no wave-particle duality.

Thermodynamics is not explicitly listed as prohibited, but the adiabatic law is a **thermodynamic primitive** (derived from entropy in standard physics). Using it without deriving it from lattice mechanics violates SDT's "first-principles only" mandate.

**Quoted from CQ40_EQUATION_OF_STATE.md (result file):**
The result is γ = 4, justified as "from linking density × temperature evolution." But "temperature" is a thermodynamic concept (average kinetic energy per degree of freedom) — potentially borrowed.

**Angel's Advocate:**
"The adiabatic law dE + PdV = 0 is just energy conservation in a reversible process. It holds in any mechanical system, not just thermodynamics. We apply it to the spation lattice as pure mechanics, not thermodynamic theory."

**Verdict:** **BORROWED** (thermodynamic language and assumptions, even if the underlying mechanism is mechanical)  
**Risk Level:** MEDIUM — CQ40 succeeds numerically, but the conceptual foundation mixes thermodynamic framing with mechanical claims.

---

### CQ18: Redshift Decomposition

**RED FLAG: Cosmological Redshift Language**

**File:** `CQ18_Redshift_Decomposition/cq18_unified.cpp:1-18`

**Exact Text:**
```
// The cohesive package: z = 1/k²  (zk² = 1)
//
// Consolidates CQ18a–h into a single demonstration that the bridge law
//   z = (v/c)² = 1/k² = Ϟ/r
// operates identically from the proton interior to the cosmological
// distance ladder. One law. One formula. Zero free parameters.
```

**Mechanism Claim:**
All redshift (cosmological, gravitational, EM) is z = (v/c)².

**Borrowed Language:**
"Cosmological distance ladder" — this is ΛCDM/Hubble-flow terminology. The phrase "operates identically from the proton interior to the cosmological distance ladder" positions SDT as solving the classic distance-ladder problem (Cepheid variables → supernovae → Hubble flow).

**Physical Issue:**
The zk² = 1 relationship is native and powerful. But presenting it as a "unified cosmological distance ladder" borrows the *problem framing* from observational cosmology, where "distance ladder" refers to a specific (ΛCDM-era) sequence of measurement techniques.

**Angel's Advocate:**
"We are solving the same observational problem (measuring distances to far objects), not borrowing the theory. The fact that classical techniques also apply under our framework does not make SDT borrowed — it makes SDT convergent with observations."

**Verdict:** **LINGUISTIC-BORROW** (mechanism is native; problem framing and terminology are borrowed from ΛCDM)  
**Risk Level:** LOW-MEDIUM — The mechanism is sound, but the narration adopts classical cosmology's language.

---

### CQ39: Cosmological Distance Scale

**RED FLAG: "Expansion" Language**

**File:** `CQ39_Cosmological_Distance_Scale/README.md` (and PROMPT.md)

**Borrowed Concept:**
The investigation is framed around "cosmological expansion" — the idea that space expands over time. This is a GR concept.

**SDT Position:**
CQ39 derives distance scales from "topological phase transition" and "resonance" — native SDT mechanisms. But the deliverables include discussion of "expansion" as if it is a primitive.

**Exact Issue:**
From CQ40_TOPOLOGICAL_FREEZEOUT.md, which depends on CQ39:
> "Show that linking number Lk(z) drops by 4× at z_rec ≈ 1100 (electron binding removes one DOF per baryon). Verify this transition drives H from radiation-like (H ∝ a⁻²) to matter-like (H ∝ a⁻³/²)."

The power laws (a⁻², a⁻³/²) are the **Friedmann equations** from GR. Reusing these forms (even if rederived via SDT mechanism) borrows the parametrisation.

**Angel's Advocate:**
"We derive why H(z) has the form it does from topology. The fact that it matches FLRW (Friedmann-Lemaître-Robertson-Walker) shows convergence, not borrowing. The mechanism is native."

**Verdict:** **LINGUISTIC-BORROW** (result framing and mathematical form borrowed from ΛCDM/GR; mechanism may be native)  
**Risk Level:** MEDIUM — Pedagogically conflates SDT's derivation with GR's postulates.

---

## Summary Verdict by Risk Category

### NATIVE (No contamination detected)
- CQ01 (Transfer Function Derivation)
- CQ02 (Vortex Equilibrium)
- CQ04, CQ05, CQ06, CQ08, CQ09, CQ10, CQ11, CQ12, CQ13, CQ14, CQ15, CQ16, CQ17
- CQ19, CQ20, CQ21, CQ22, CQ23, CQ24, CQ25, CQ26, CQ27, CQ28, CQ29, CQ32, CQ33, CQ35, CQ36, CQ37

### HYBRID (Native mechanism + borrowed notation/framing)
- **CQ03** (Fine Structure) — Self-corrected; mechanism is native but inputs carry QM baggage
- **CQ38** (Trefoil Wake Multipole) — Topology is native; wavefunction notation ψ and spherical harmonics are borrowed
- **E98** (Lagrange Points) — Koppa mechanism is native; three-body problem formulation is classical
- **CQ40** (Pressure Tensor) — Lattice mechanism is native; thermodynamic framing is borrowed

### LINGUISTIC-BORROW (Native mechanism, borrowed terminology/problem framing)
- **CQ18** (Redshift) — zk² = 1 is native; "cosmological distance ladder" terminology is ΛCDM
- **CQ39** (Cosmological Distance) — Resonance is native; "expansion" and FLRW language is GR

### BORROWED (Foundational use of external framework)
- **CQ07** (Neutrino Magnetic Moment) — Entire proof structure rests on ℓ-expansion (spherical harmonics) from QM/classical EM

---

## Specific Recommendations

### Immediate Actions (HIGH PRIORITY)

1. **CQ07 — Neutrino Magnetic Moment**
   - Current text: "The wake field Φ(r, n̂) admits a spherical harmonic decomposition" — this is explicit QM language.
   - Action: Derive the ℓ-expansion from **first principles in spation physics**. Show why the multipole structure arises *without importing* spherical harmonics. Rephrase as: "The wake field naturally decomposes into multipole components..."
   - Owner: James Tyndall
   - Timeline: Critical path blocker for fine structure closure

2. **CQ38 — Trefoil Wake Multipole**
   - Current text: Uses ψ(φ + 2π/3) notation and Y_ℓ^m basis functions.
   - Issue: Violates CQ34 specification prohibiting "spherical harmonics Y_ℓ^m as imported functions."
   - Action: Rewrite Phase 4 (Angular Quantisation) to use **pure topology language**: "The trefoil's C₃ symmetry constrains allowed orbital modes to m₃ = 3k" without recourse to wavefunction notation or spherical harmonics.
   - Owner: James Tyndall
   - Timeline: Before merging CQ38 to main framework

3. **CQ40 — Pressure Tensor**
   - Current text: "Apply adiabatic law dE + PdV = 0 to the spation lattice."
   - Issue: Thermodynamic primitive used without justification from lattice mechanics.
   - Action: Derive why energy conservation in lattice mechanics produces dE + PdV = 0. Show that γ = 4 emerges from topology without thermodynamic assumptions.
   - Owner: James Tyndall
   - Timeline: CQ40 closure phase

### Medium-term Actions

4. **E98 — Three-Body Lagrange Points**
   - Action: Rebrand as "Koppa-Based Orbital Equilibria" to avoid classical mechanics framing. Derive L1–L5 and stability criteria entirely from pressure field superposition, not from "mass ratio μ."
   - Timeline: Before E98 publication

5. **CQ39 / CQ40 — Cosmological Nomenclature**
   - Action: Stop using "expansion" language. Replace with "lattice-density evolution" or "topological phase transition."
   - Action: Derive H(z) power laws from first principles; only *then* note convergence with FLRW as a validation, not a derivation.
   - Timeline: Documentation sweep

6. **CQ03 — Fine Structure Constant**
   - Action: Completed (self-corrected in June 2026 update). Keep as-is but add note: "CQ03 resolves that α is not derivable from topology; it requires e as independent input. See CQ10 for e-derivation program."

### Long-term Structural Fix

7. **Create Translation Glossary**
   - Document: SDT-native concept ↔ standard-physics borrowing
   - Example: "Spherical harmonic ↔ multipole mode consistent with C₃ symmetry"
   - Goal: Make borrowing/nativity transparent to readers
   - Owner: James Tyndall + community
   - Timeline: Post-June 2026

8. **Audit Trail in Each CQ**
   - Add checklist to every CQ: "declared dependencies used? ✓ No prohibited concepts? ✓ Mechanism native? ✓ Notation borrowed (acceptable)? ✓"
   - Owner: James Tyndall

---

## Critical Success Factors

**The core issue:** SDT's framework is sound, but **pedagogical contamination** risks readers conflating SDT-derived results with imported concepts.

**Example of Contamination Risk:**
- CQ38 uses ψ and Y_ℓ^m to derive fine structure
- Reader thinks: "This looks like QM"
- Reader concludes: "SDT is just QM relabeled"
- **False conclusion** — the topology (trefoil C₃ symmetry) is genuinely native; only the notation is borrowed

**Mitigation Strategy:**
1. **Separate mechanism from notation** explicitly in each CQ
2. **Derive notation** where possible (show why ℓ-expansion arises from topology)
3. **Label borrowings clearly** ("We use harmonic analysis language because it is standard; the underlying mechanism is SDT-native")
4. **Provide alternative formulations** (CQ38 Phase 4 should show both m₃-based and ℓ-based descriptions side-by-side)

---

## Verdict Summary Table

| CQ | Classification | Confidence | Risk Level | Action Required |
|---|---|---|---|---|
| CQ03 | SELF-CORRECTED HYBRID | HIGH | LOW | Monitor for Compton-wavelength language; otherwise clean |
| CQ07 | BORROWED | HIGH | CRITICAL | Rederive ℓ-expansion from first principles |
| CQ18 | LINGUISTIC-BORROW | HIGH | MEDIUM | Rebrand as native mechanism + cosmology convergence |
| CQ34 | NATIVE (SPEC) | HIGH | — | Specification is clean |
| CQ38 | HYBRID | HIGH | CRITICAL | Remove ψ notation; derive Θ_{m₃} natively |
| CQ39 | LINGUISTIC-BORROW | MEDIUM | MEDIUM | Eliminate "expansion" language |
| CQ40 | HYBRID | HIGH | MEDIUM | Justify adiabatic law from lattice mechanics |
| E98 | HYBRID | MEDIUM | MEDIUM | Rebrand; derive from pressure fields, not mass ratio |

---

## Appendix A: Dependency roles (for reference)

From CLAUDE.md and Theory/00_Ruleset.md:

```
DEPENDENCY ROLES:
  ℓ_P                         dimensional seed
  c, k_B, e                   unit bridges
  {ℏ, m_e, m_p}               one mass/action seat
  α                           hydrogen spectroscopic koppa rung (APS05/PPT02)
  T_CMB                       measured present convergence boundary
  measured observables        validation/comparison data in measured units
  topology and geometry       derived only through cited mechanisms

PROHIBITED:
  - G, M, GM as fundamentals
  - Quantum wavefunctions as primitives (ψ as basis, not description)
  - Fields as primitives (E, B as independent)
  - Dark matter, dark energy, ΛCDM, quarks, gluons
  - Wave-particle duality
  - Lagrangian, Hamiltonian, action principles (as primitives)
  - Thermodynamic entropy (as fundamental)
  - Planck units (treated as fundamental)
  - Magnetic quantum numbers (as independent inputs)
```

---

**End of Audit**

Auditor: Claude Code (Adversarial Protocol)  
Date: 2026-06-16  
Classification: OFFICIAL / SDT FRAMEWORK AUDIT

