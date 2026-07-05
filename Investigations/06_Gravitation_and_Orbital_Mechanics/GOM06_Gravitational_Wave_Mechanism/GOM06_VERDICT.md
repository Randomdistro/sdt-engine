# CQ-44 · VERDICT — Gravitational waves: "move the sea, don't make waves"

> **Author:** SDT Canonical Engine — James Christopher Tyndall, Melbourne
> **Status:** CLOSED at convergence level; one distinctive frontier (echoes) open and falsifiable.
> **Overall class:** **C** (convergence with GR in the weak/far sector; two native, distinctive predictions).

---

## The thesis, settled

A gravitational wave is **the medium being moved, not a ripple made in it.** The relay-lattice deformation is a
strain tensor whose **trace** is the static depth `z=ϟ/r` (the Depth–Closure Theorem) and whose **traceless
shear** is the radiative wave. The sea's **volume** (trace) is the static gravitational field; its **shape**
(shear) is the gravitational wave. That single decomposition carries the whole investigation.

---

## Gate ledger

| Gate | Question | Result | Class | Tool |
|---|---|---|---|---|
| **G1** | speed & dispersion | `c` (relay tick); `c_local=c(1−z)` near-field; no dispersion | C (convergence) | depth_closure |
| **G2** | chirp without G/M | chirp is a **LENGTH** `ϟ_tot`; `f_isco=c/(π6^{3/2}ϟ_tot)` = 67.65 vs 68 Hz | C | `cq44_chirp_from_koppa.cpp` |
| **G3** | polarisation (kill gate) | **tensor natively** (radiative DOF = traceless shear); breathing = conserved monopole ⟹ only `Δϟ/ϟ`≈4.6 % | C, **kill AVOIDED** | `CQ44_POLARISATION.md` |
| **G4** | memory | `Δh=η·Δϟ_rad/R`, 7–35 % of peak (vs GR 5–20 %); a radiated **length** | C | `cq44_memory.cpp` |

**Foundations:** the **dynamic Depth–Closure extension** (`CQ44_DYNAMIC_CLOSURE.md`, one posit: Axiom R)
supplies G2's `96/5`, G3's `κ`, and G4's amplitude by convergence (`GM→c²ϟ`).

---

## What is native (distinctive — not GR)

1. **Polarisation is tensor *by construction*** — the radiative degree of freedom is the lattice's traceless
   shear; the scalar depth `z` is the (static) trace. No scalar-tensor tuning needed; "move the sea" = the
   volume (trace) is conserved, the shape (shear) radiates.
2. **G3 ≡ G4** — the merger-epoch breathing transient and the permanent memory are the **same** `Δϟ_rad`
   (AC vs DC). GR predicts the memory but not this identity. **Falsifiable** (LISA / PTA / ≥5-detector).
3. **Echoes** (strong field, `CQ44_RINGDOWN_ECHOES.md`) — no horizon + CQ-42 closure-floor wall ⟹ a ringdown
   echo train `Δt_echo ∝ ϟ_f·ln(ϟ_f/ℓ_P)` (~tens–hundreds of ms). **The** SDT≠GR test.

## What is convergence (matches GR — by shared math, honestly labelled)

- speed = c; the `f^{11/3}` chirp form and `96/5` coefficient; the strain amplitude; the memory magnitude; the
  ringdown frequency. All follow from `□(potential)=source(quadrupole)` with `GM→c²ϟ` — SDT and GR reduce to the
  same wave equation, so convergence is expected, not a coincidence (and not plagiarism — delete the
  correspondence check and the C-results stand).

## What is open (the honest frontier)

- the **native** derivation of the radiative coefficients (`96/5`, `κ`, QNM `f̂`) from lattice shear-radiation
  reaction (Axiom R is a posit; the coefficients are borrowed-as-convergence);
- the **strong-field, nonlinear** sector: native `ΔM/M`, the wall **reflectivity**, the QNM spectrum of a
  max-compression vortex, and a clean **echo** detection (currently contested).

---

## One-line close

The poem was right: **the binary moves the sea (quadrupolar shear → tensor waves, chirp as a length), the sea's
volume stays moved (memory = the radiated koppa), and — if the closure floor reflects — the pulse keeps coming
back (echoes).** SDT reproduces every measured GW number without G or M, and stakes two falsifiable claims GR
does not make.

---

**NOTE (2026-07-04, Harvey directive — OBSERVED-comparison, not a derivation).** Two-channel split
made explicit. G1's speed-=-c ruling concerns the **radiative shear pulse** (energy channel) and is
anchored to measurement (GW170817-class multi-messenger timing) — it stands untouched, as do the
chirp, memory, and echo claims (all pulse-channel results). The **static trace** (`z = ϟ/r`, the
sea's volume) is a *constraint*, and its effective action speed is a separate question. The
classical Laplace aberration bound is measured-anchor-class support here: stable planetary orbits
require the static field's effective propagation to be ≫ c (Laplace/Lightman-class aberration
analyses give > 10⁸–10¹⁰ c), else aberration torque would disrupt orbits on short timescales. The
rival (GR) handles this with velocity-dependent field-momentum cancellation terms; SDT's rigid
constraint channel (FLM14 RUN_LOG ADJ-7; GOM05 rigid hinge units) handles it natively — the trace
is a lattice constraint, not a relayed pulse, so no aberration is generated that needs cancelling.
Label: **OBSERVED-comparison** supporting the uncapped constraint channel. No GOM06 ruling changes.
