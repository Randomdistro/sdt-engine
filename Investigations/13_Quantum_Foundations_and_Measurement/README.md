# Quantum Foundations & Measurement — deterministic relay-wake mechanics (QM01–QM07)

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (7 prompts, unstarted).
> Every prompt inherits the §0 anti-creep protocol and rules R0–R5 verbatim.
> **This domain is the single largest standing debt in the SDT paradox census**
> ([[project_paradox_census]] §8.2 #1): SDT owes a *deterministic* account of the double-slit
> pattern, uncertainty, tunnelling, the Born rule, spin, discrete spectra, and Bell correlations.

## The through-line

In SDT there is no wavefunction. There is a **granular relay lattice of spations** passing
convergence throughput between contacting neighbours at one tick (`c = ℓ_P/t_P`), and a particle is
a **hard, localised solid vortex** that goes through exactly **one place at a time**, dragging a
**convergence wake** (the PPT06/APS04 wake) that can spread and diffract. Two channels travel
together: the **solid vortex** (carries which-path, mass, handedness) and the **wake pulse**
(carries phase, spreads). The convergence influx is a **THROUGHPOLE** — it passes through every
point, in and out, and never terminates ([[project_foundational_ontology_influx_monopole]]). There
is **no charge substance and no ψ**.

So "wave–particle duality," "collapse," and "irreducible randomness" are not facts the theory must
absorb — they are **shadows of a wrong premise** (the collapsing wavefunction). Each investigation
reproduces a standard quantum result as a *convergence target* (never a borrowed input) via
deterministic local relay mechanics, and **flags any genuinely non-local step OPEN** rather than
fabricating a local story (above all for Bell). This is the census thesis applied head-on.

## Dependency stack (build/run order — bottom feeds top)

```
QM01  Deterministic double-slit from the lattice relay   ← the QM root (rests on ROOT-SIM, FLM02, FLM05, PPT06/APS04 wake)
  │
  ├─ QM02  Uncertainty as relay bandwidth        (Δx·Δp ≥ ℏ/2 = wake Fourier limit; FD02 κ=h/m sets ℏ)
  │
  ├─ QM03  Tunnelling as wake leakage            (wake leaks an occlusion barrier, vortex follows; α-decay, STM)
  │
  ├─ QM04  Born rule from residence density      (|amp|² = superposed pressure energy density = landing count)
  │
  ├─ QM06  Discrete spectra from standing wakes  (n-ladder = standing-wake boundary conditions; APS01 emissions)
  │
  ├─ QM07  Spin & Stern–Gerlach from handedness  (EMC03 circulation; two-valued; swirl-gradient occlusion)
  │
  └─ QM05  Bell / EPR & the throughpole          ← THE HARDEST / MOST-OPEN. Locality audit; may stay OPEN.
```

## The suite

| ID | Title | SDT mechanism | Convergence target / falsifier |
|----|-------|---------------|--------------------------------|
| **QM01** | Deterministic Double-Slit from the Lattice Relay | vortex through one slit; wake (PPT06/APS04) through both, self-overlaps | cos²·sinc² fringe to <1%; single-particle build-up; λ=h/p derived |
| **QM02** | Uncertainty as Relay Bandwidth | wake's joint position/momentum bandwidth (Fourier-type relay limit), not a commutator | Δx·Δp ≥ ℏ/2 derived; minimum-uncertainty wake = relay Gaussian |
| **QM03** | Tunnelling as Wake Leakage | convergence wake leaks through an occlusion barrier; vortex follows the surviving branch | α-decay Gamow rates; STM I∝e^{−2κd}; resonant transmission |
| **QM04** | Born Rule from Residence Density | \|amplitude\|² = energy density of superposed convergence-pressure field = long-run landing density | the *square* derived geometrically (not axiomatic); residence = intensity to <1% |
| **QM05** | Bell / EPR & the Throughpole *(locality audit)* | can a LOCAL relay-wake model reach CHSH = 2√2? if not, name the throughpole feature invoked | reproduce 2√2 **or** mark OPEN honestly; classify debt vs feature |
| **QM06** | Discrete Spectra from Standing Wakes | energy quantisation = standing-wake boundary conditions on the vortex orbit (n-ladder) | H Rydberg / Balmer (APS01); no quantised-action postulate; degeneracies |
| **QM07** | Spin & Stern–Gerlach from Handedness | "spin" = vortex intrinsic handedness/circulation (EMC03); two-valued; SG via differential occlusion | g≈2; two-spot SG split; sequential SG correlations; ties to magnetism |

## Engine hooks (single source of truth: `Engine/include/sdt/laws.hpp`)

The deepest dependency is **ROOT-SIM** (the per-contact relay rule) — flag where any phase leans on
its unproven core. Build only on: **FLM02** (GPI, the relay state-machine front), **FLM05** (the
tick-by-tick contact/gap state machine), **PPT06/APS04** (the convergence wake — traction and
multipole work; this *is* the "pilot"), **FD02** (`κ = h/m` clean to 0.02% — supplies the lattice
action quantum that fixes ℏ), **EMC03** (handedness = the inverse-of-convergence redirection,
[[project_cq47_repulsion_inverse]] — supplies "spin" and charge-sign two-valuedness), **PPT01**
(vortex equilibrium — orbit/standing-wake stability), **PPT05** (confinement — barrier walls for
tunnelling), and **APS01** (emissions — the spectral ladder). Engine namespaces:
`law_I::P_conv` · `law_III` occlusion · `law_V` movement budget (`v²+v_circ²=c²`) ·
`law_VI::traction` / `topology` / `confinement` · `bridge` (`koppa`, `k`, `z`, `depth_closure`).

## Method discipline

Each investigation reports with certification labels (`DERIVED` / `COMPUTED` / `CALIBRATED(n)` /
`OBSERVED` / `PENDING`) and the audit-spine class (A–F). The standard quantum number is always the
thing to **reproduce**, never to **borrow**; ψ, Schrödinger evolution, the Born postulate-as-axiom,
superposition-as-ontology, "collapse," Hilbert space, and "observer" are **forbidden inputs** — they
are the *targets*. Measured constants (ℏ, m_e, α, spectral lines) are legitimate measured-unit
inputs/tools, but every mechanism must be SDT-native and every gap flagged OPEN.

This is the largest debt in the framework: **be rigorous and honest. A clean kill, or an honest
OPEN, outranks a forced pass (R4).** In particular **QM05 (Bell) may remain OPEN** — a local
relay-wake model may not have a clean route to the 2√2 violation, and if it does not, that is to be
*reported*, not papered over: the census debt then stands, and the throughpole's non-local in/out
is examined as a candidate feature, not asserted as a fix.
