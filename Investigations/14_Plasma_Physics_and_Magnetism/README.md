# Plasma Physics & Magnetism — SDT collective vortex circulation (PM01–PM07)

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (7 prompts, unstarted).
> Every prompt inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## The through-line

In SDT the only ontology is a **granular relay lattice of spations** passing convergence
throughput between contacting neighbours at one tick (`c = ℓ_P/t_P`). Gravity and Coulomb are
**occlusion** in that lattice (Law III); **magnetism is the same lattice carrying circulation**.
A moving solid vortex drags a handed convergence wake (PPT06 traction); many vortices moving or
aligned together sum their wakes into a **collective swirl field** — a literal curl in relay
throughput. What electromagnetism calls **B** is the coarse-grained density/curl of that swirl,
not a primitive field; a "field line" is a streamline of relay circulation. Two structural
consequences fall out *for free*: there is **no magnetic charge** — the convergence flow is a
**throughpole** and the monopole is topologically impossible (E58,
[[project_foundational_ontology_influx_monopole]]) — so **∇·B = 0 is a theorem, not an
observation**; and the **Lorentz force `qv×B` is differential occlusion** on a vortex crossing a
swirl gradient, its sign fixed by **relative handedness** (EMC03, focus/defocus). "Light" / the EM
wave is an **emission**: a propagating relay phase-impulse coupled to the swirl. These seven
investigations test that claim end to end — each reproduces a standard plasma/EM result as a
*convergence target* (never a borrowed input), in SDT primitives, flagging every gap OPEN.

## Dependency stack (build/run order — bottom feeds top)

```
PM01  Magnetism as Collective Vortex Circulation   ← the PM root (B=∇×w; ∇·B≡0; qv×B=occlusion)
  │     (rests on PPT06 traction, APS04 wake, EMC03 handedness, B17 native g, magnetosphere.hpp)
  │
  ├─ PM02  Faraday Induction & Lenz from Changing Swirl   (EMF = ∂(swirl)/∂t; Lenz = occlusion back-reaction)
  │
  ├─ PM03  EM Waves as Coupled Relay Pulses              (transverse swirl⊗emission; recover c, no µ₀ε₀ primitive)
  │     │   (related GOM06 transverse lattice rigidity, 15_Optics)
  │     └─ PM07  Magnetohydrodynamics → couples to FD suite
  │              (Alfvén = transverse lattice+swirl mode; frozen-in flux = wake advection)
  │
  ├─ PM04  Plasma Oscillations & Debye Shielding         (ω_p, λ_D from collective vortex-population response)
  │              (rests on TD02 statistical ensemble)
  │
  ├─ PM05  Magnetic Reconnection & Solar Flares          (wake-topology change releases stored throughput; CMEs)
  │              (GOM06 topology; magnetosphere.hpp)
  │
  └─ PM06  Cyclotron & Synchrotron from Differential Occlusion  (circular vortex motion; radiation = vortex decel, E89)
```

## The suite

| ID | Title | SDT mechanism | Convergence target / falsifier |
|----|-------|---------------|--------------------------------|
| **PM01** | Magnetism as Collective Vortex Circulation | B ≡ ∇×w (summed handed wakes); Lorentz = differential occlusion; ∇·B≡0 structural | Ampère 1/r; ∇·B=0 theorem; `qv×B` sign vs ±carrier; magnetosphere standoff |
| **PM02** | Faraday Induction & Lenz from Changing Swirl | EMF = time-varying collective swirl threading a loop; Lenz = occlusion back-reaction opposing the change | `EMF = −dΦ/dt`; transformer ratio; Lenz sign always opposing; eddy-brake drag |
| **PM03** | EM Waves as Coupled Relay Pulses | transverse coupling of swirl (B) and emission phase, propagating at lattice relay speed | wave equation derived; `c` without µ₀ε₀-as-primitive; impedance, polarisation |
| **PM04** | Plasma Oscillations & Debye Shielding | collective vortex-population restoring response in the lattice | `ω_p=√(ne²/ε₀m)` form; `λ_D`; dispersion; screening exponential |
| **PM05** | Magnetic Reconnection & Solar Flares from Wake Topology | reconnection = change of collective wake topology releasing stored throughput | flare energy budget; reconnection rate ~0.1 v_A; CME onset; Sweet–Parker vs fast |
| **PM06** | Cyclotron & Synchrotron from Differential Occlusion | circular vortex orbit from the Lorentz-occlusion push; radiation = vortex deceleration | `ω_c=qB/m` form; relativistic synchrotron spectrum & beaming (E89) |
| **PM07** | Magnetohydrodynamics Coupling to the Fluid Suite | FD fluid lattice coupled to the swirl field; Alfvén = transverse lattice+swirl mode; frozen-in = wake advection | ideal-MHD set reproduced; `v_A=B/√(µ₀ρ)` form; frozen-in flux; magnetic pressure |

## Engine hooks (single source of truth: `Engine/include/sdt/laws.hpp`)

`law_VI::traction` (PPT06: `T=3(W+1)`, wake ℓ=1/2/3) · `law_VI::topology` · `law_III` occlusion
(`F_occlusion`, `solid_angle_occluded`) · `law_V` movement budget (`v_circ²+v²=c²`) · `bridge`
(`koppa`, `k`, `z`). Prior results leaned on: **PPT06** (spation traction / wake handedness),
**APS04** (wake multipole), **EMC03** (focus/defocus handedness sign,
[[project_cq47_repulsion_inverse]]), **B17** (native electron g-factor), **GOM06** (transverse
lattice rigidity / topology), `Engine/include/sdt/magnetosphere.hpp` (Earth dipole / solar-wind
occlusion front), **E58** (monopole topologically forbidden → ∇·B=0 theorem), **E89**
(bremsstrahlung / radiated deceleration). Plasma statistics feed from **TD02** (ensemble), the
fluid coupling from the **FD** suite (FD01 Navier–Stokes, FD02 viscosity, FD05 sound/Alfvén).

## Method discipline

**The no-magneton rule is absolute** ([[feedback_no_borrowed_units]]): never express any magnetic
result in Bohr magnetons / magnetons / µ_B or any imported magnetic unit. Use **native
wake-circulation units** (the vortex's own wake), **koppa**, and **traction `T=3(W+1)`**. "Stop
sneaking GM — and µ_B — into my model." Each investigation reports with certification labels
(`DERIVED` / `COMPUTED` / `CALIBRATED(n)` / `OBSERVED` / `PENDING`) and the audit-spine class
(A–F). The standard EM/plasma number (Ampère's 1/r, `EMF=−dΦ/dt`, `ω_p`, `ω_c`, `v_A`) is always
the thing to *reproduce*, never to *borrow*; measured plasma properties (density, temperature,
core radius, solar-wind flux) are legitimate measured-unit inputs — like spectral lines — but the
mechanism must be SDT-native. **B as a primitive field, monopoles, magnetons, spinors, virtual
photons, gauge-potential-as-ontology, and wholesale-imported MHD equations are FORBIDDEN inputs —
they are targets to reproduce.** A clean kill outranks a forced pass (R4).
