# CQ-44 · Strong-field frontier — ringdown & echoes (the one place SDT ≠ GR)

> **Author:** SDT Canonical Engine — James Christopher Tyndall, Melbourne
> **Status:** EXECUTED — `cq44_echoes.cpp`. Ringdown = **convergence**; echoes = **distinctive, falsifiable,
> NOT confirmed**. This is the SDT≠GR test.
> **Builds on:** E68 (max-compression remnant, no singularity), CQ-42 (z=1 closure floor / self-boundary),
> CQ-43 (`c_local=c(1−z)`), `CQ44_DYNAMIC_CLOSURE.md` (the shear mode that rings).

---

## Why this is the frontier

Gates G1–G4 all live in the weak-field / far-zone sector, where SDT *should* converge with GR (both are wave
equations for the potential). The **strong-field** — the merger interior and ringdown, `z→1` near the
c-boundary — is the only sector where SDT can **depart**, because its picture of the remnant is structurally
different from GR's:

| | GR | SDT |
|---|---|---|
| interior | singularity at r=0 | **max-compression vortex**, no singularity (E68) |
| boundary | event horizon (perfect absorber, one-way) | **no horizon**; `c_local→0` only at `z=1` (r=ϟ), and CQ-42's closure floor is a **hard wall** |
| ringdown | Kerr QNMs, then silence | QNMs, then **echoes** off the wall |

---

## (A) Ringdown — "the pulse, she stop" (CONVERGENCE)

The remnant's damped shear mode (the radiative DOF of `CQ44_DYNAMIC_CLOSURE.md`) rings at a frequency set by
the **final koppa** `ϟ_f` — again a LENGTH:

```
f_QNM = f̂ · c / (2π ϟ_f) ,    f̂ ≈ 0.53  (⟦Kerr-fit⟧, fundamental ℓ=m=2)
```

GW150914 remnant (`M_f≈62 M_⊙`, `a_f≈0.68` → `ϟ_f≈91.6 km`): **f_QNM ≈ 275 Hz vs observed ~250 Hz (10 %)**;
quality factor `Q≈3.2` → damping time `τ≈3.7 ms` — "she stop" in ~3 cycles. **Honest:** `f̂`, `Q` are
`⟦Kerr-fit⟧` convergence inputs (GR perturbation theory); the *native* shear-mode-of-a-max-compression-vortex
derivation is **OPEN** (same status as G2's `96/5`).

---

## (B) Echoes — the SDT-distinctive prediction (SDT ≠ GR)

SDT has **no event horizon**. The relay speed `c_local = c(1−z)` reaches zero only at `z=1` (`r=ϟ`), and CQ-42's
**closure floor** (the spation cannot compress below `ℓ_P`; the `z=1` self-boundary is hard) makes that a
**reflecting wall**. The ringdown therefore partially reflects and re-emerges as a **train of echoes**, spaced
by the cavity light-travel time in the depth-slowed relay:

```
Δt_echo = (2/c) ∫_{r_wall}^{r_peak} dr/(1−ϟ/r)
        = (2ϟ_f/c) · [ (r_peak−r_wall)/ϟ + ln( (r_peak−ϟ)/δ_wall ) ]
```

With the wall one closure-cell from the edge (`δ_wall ~ ℓ_P`, CQ-42) and the light-ring at `r_peak≈3ϟ_f`, the
cavity depth is `ln(2ϟ_f/ℓ_P) ≈ 92` and:

> **Δt_echo ≈ 58 ms for GW150914** — a train of echoes ~58 ms after the main ringdown.

The `ln(ϟ_f/ℓ_P)` factor is the **cavity depth measured in closure units** — a direct fingerprint of the
spation floor. Scaling: `Δt_echo ∝ ϟ_f` (∝ remnant mass), so heavier remnants echo with longer spacing.

---

## Honest caveats (R4/R5)

- **The reflecting wall is a POSIT**, not derived — it follows from CQ-42's hard closure floor + E68's no-horizon
  remnant, but the *reflectivity* (how much reflects vs dissipates) is not computed.
- **Logarithmic sensitivity:** `Δt_echo` depends on `ln(δ_wall)`; `δ_wall=ℓ_P` gives ~58 ms, but the true wall
  placement shifts it across **tens–hundreds of ms**. The structural form (`∝ ϟ_f · ln(ϟ_f/ℓ_P)`) is the robust
  part; the coefficient is not.
- **Observational status — CONTESTED, NOT confirmed.** Echo claims for GW150914 (Abedi, Dykaar & Afshordi 2017,
  Δt≈0.3 s, ~4σ) are disputed; independent reanalyses (Westerweck et al. 2018; Nielsen et al. 2019) find
  low/no significance. SDT predicts echoes **exist**; current data neither confirms nor cleanly excludes them.

---

## Verdict

Ringdown frequency converges (~275 vs 250 Hz, a LENGTH result). **Echoes are the SDT-distinctive, falsifiable
strong-field prediction** — a direct consequence of "no singularity, no horizon, a hard closure floor"
(E68+CQ-42). They are **the** test that could distinguish SDT from GR with existing/near-future ringdown data.
**OPEN:** the wall reflectivity, the native QNM coefficient, and a clean echo detection.
