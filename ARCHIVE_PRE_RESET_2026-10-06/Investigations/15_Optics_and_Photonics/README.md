# Optics & Photonics — SDT relay-emission optics (OP01–OP07)

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (7 prompts, unstarted).
> Every prompt inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## The through-line

In SDT light is an **emission** — a propagating relay phase-impulse handed spation-to-spation
at one tick, **not** a point photon-quantum with intrinsic mass. Its local speed is set entirely
by the local spation closure: `c_local = c(1−z)`, `z = ϟ/r` (GOM05, [[project_cq43_variable_closure]]).
The refractive index is then nothing but that closure ratio, `n = c/c_local = 1/(1−z)`, and the
**same** formula governs glass, water, and a mass-graded vacuum near the Sun — so optical refraction
and gravitational lensing are **one thing**, not two. Rays follow least-relay-time (Fermat) paths
down the closure gradient; the lattice is granular at ℓ_P, which is the origin of dispersion. These
seven investigations test that claim end to end: each reproduces a standard optical result as a
*convergence target* (Snell, Fresnel, the lens equations, the 1.75″ deflection, Malus's law), never
a borrowed input, narrating the mechanism in SDT primitives (closure, relay, emission, vortex
exchange, handedness) and flagging every gap OPEN rather than fitting it.

## Dependency stack (build/run order — bottom feeds top)

```
OP01  Refraction & dispersion = spation gradient-index    ← the OP root (n = 1/(1−z); GOM05)
  │
  ├─ OP02  Reflection & Fresnel from relay impedance        (closure-impedance mismatch; Brewster)
  │
  ├─ OP03  Diffraction & interference from relay-Huygens     (each interface spation re-emits one tick)
  │     │                                                     └─ ties QM01 wake construction
  │     └─ OP06  Coherence, lasers & stimulated emission      (macroscopic relay phase-lock; CM01)
  │
  ├─ OP04  Polarisation = transverse wake orientation         (handedness EMC03; transverse GOM06; Malus)
  │
  └─ OP05  Photoelectric & Compton = emission↔vortex exchange (no photon-particle; E55/E56)

  ⇒ OP07  Solar lens-artifact experiment (FALSIFIER CAPSTONE) — the dated falsifiable claim from
          OP01-H4 and [[project_solar_lens_artifact_claim]]: a false-colour λ-scan of the solar limb
          where the disk GROWS then partly VANISHES at the ~4400–5000 K temperature-minimum band
          (a caustic FOLD where T(height) turns over) then REAPPEARS — one dispersive surface,
          not "different Suns." The concrete protocol that makes OP01 testable.
```

## The suite

| ID | Title | SDT mechanism | Convergence target / falsifier |
|----|-------|---------------|--------------------------------|
| **OP01** | Refraction & Dispersion as a Spation Gradient-Index | `n(r)=1/(1−z)` is the closure ratio; rays take least-relay-time paths; dispersion from ℓ_P granularity | Snell, thin-lens, TIR, prism dispersion, **1.75″** solar deflection — optics ≡ lensing |
| **OP02** | Reflection & Fresnel from Relay Impedance | closure-impedance mismatch `Z=1/c_local` at an interface partially reflects the relay | Fresnel r/t amplitudes; R+T=1; Brewster `tanθ_B=n₂/n₁`; phase flip on hard reflect |
| **OP03** | Diffraction & Interference from Relay-Huygens | each illuminated interface spation re-emits one tick; sum the relay wavelets | double-slit fringes, grating `d sinθ=mλ`, single-slit `sinc²`, Airy disk; ties [[QM01]] wake |
| **OP04** | Polarisation as Transverse Wake Orientation | the emission's transverse orientation/handedness (EMC03 ± handedness, GOM06 transverse) | Malus `cos²θ`, linear/circular states, optical activity rotation, birefringence sign |
| **OP05** | Photoelectric & Compton as Emission↔Vortex Exchange | sub-attosecond relay absorption into a vortex (threshold); lattice momentum recoil | E55 threshold `hf=W+KE_max`; E56 Compton `Δλ=λ_C(1−cosθ)` — no photon-particle |
| **OP06** | Coherence, Lasers & Stimulated Emission | coherence = phase-locked emissions; laser = macroscopic relay phase-lock (cf. CM01 superconductor) | gain/threshold, Schawlow–Townes linewidth, `g⁽²⁾(0)` coherence; lock-in like E59 |
| **OP07** | Solar Lens-Artifact Experiment *(falsifier capstone)* | one dispersive solar surface as a gradient-index lens; caustic **fold** at the temp-minimum shell | false-colour λ-scan: disk grows→folds→reappears at ~4400–5000 K; **SDT≠standard** = the test |

## Engine hooks (single source of truth: `Engine/include/sdt/laws.hpp`)

`bridge::z` / `bridge::koppa` / `bridge::depth_closure` (`c_local = c(1−z)`, `z = ϟ/r`, the index
gradient) · `depth_closure` namespace (Shapiro, a₀, c∞, lumiopause — the n>1 vacuum case) ·
`law_V` movement budget (`v_circ²+v²=c²`, the emission's transverse budget) · `law_VI::topology`
(emission as relay phase-impulse, vortex exchange) · `law_VI` handedness (EMC03, ± redirection).
Prior results leaned on: **GOM05** (`c_local`, variable closure — the OP root), **GOM01** (depth
engine z(r), Shapiro, light bending, the 1.75″ deflection), **CR07** (the octave/ruler comparison,
`1+z=2^Δn`), **GOM06** (transverse channel, GW speed = c), **EMC03** (handedness ⇒ polarisation),
**E55/E56** (photoelectric/Compton as emission↔vortex exchange), **E57** (Cherenkov shock when a
charge outruns `c_local`), **CM01** (superconducting phase-lock ≡ laser phase-lock).

## Method discipline

Each investigation reports results with certification labels (`DERIVED` / `COMPUTED` /
`CALIBRATED(n)` / `OBSERVED` / `PENDING`) and the audit-spine class (A–F). The standard-optics
number — Snell, Fresnel, `d sinθ=mλ`, Malus `cos²`, the 1.75″ deflection — is always the thing to
*reproduce*, never to *borrow*; measured optical properties (lab `n`, work functions, line
wavelengths) are legitimate measured-unit inputs/tools, but the mechanism must be SDT-native.
**Forbidden as inputs** (these are the *targets*): the photon as a point-quantum with intrinsic
mass, QED vacuum polarisation as the cause of lensing, metric-curvature-as-primitive, "spacetime
bends," the wavefunction. A clean kill outranks a forced pass (R4).
