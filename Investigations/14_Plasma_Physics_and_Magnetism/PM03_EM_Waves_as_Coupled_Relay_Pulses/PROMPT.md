# PM03 — EM Waves as Coupled Relay Pulses

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC → **ACTIVE** on first gated run (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `measured::c`, `measured::l_P`, `measured::t_P`; μ₀, ε₀ as **OBSERVED** SI dress only.
> **Prior audit:** the stale `PM03_VERDICT.md` signed PASS on a **static Courant=1.0 with no wave
> evolution** — exactly the failure this prompt forbids. That verdict is now banner-flagged SUPERSEDED;
> a PASS requires an **evolved** 1-D wave that visibly propagates at `c`.

---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Does a discrete relay update on the lattice (`Δx = ℓ_P`, `Δt = ℓ_P/c`)
   *actually evolve* a transverse pulse that **moves at `c`** — or is the only thing we can show the
   static algebraic identity `c = ℓ_P/t_P = 1/√(μ₀ε₀)`? The static identity is true by construction and
   teaches nothing about propagation; the open question is whether the lattice *dynamics* carry a wave.
   **A Courant number printed without time-stepping answers nothing** (this is the trap the prior verdict
   fell into).
2. **Why does it matter?** — Light-as-transverse-relay is the spine the whole EM stack hangs on: PM01's
   `∇×w`, PM02's `−dΦ/dt` source term, FD05's `c/√3` compression branch (which must NOT be the transverse
   speed), and GOM06's gravitational wave (also transverse, also `c`). If the pulse doesn't propagate at
   `c` in a real evolution, the relay picture of light is unsupported.
3. **How will we find out?** — Phase 0 the identity (GATE); Phase 1 **evolve** a 1-D wave ≥1000 steps and
   track the peak (the mandatory GATE that the prior run skipped); Phase 2 separate transverse (`c`) from
   longitudinal (`c/√3`, FD05) speeds; Phase 3 (DEFER) the coupled PM01⊕PM02 pair.
4. **What would prove us wrong?** — §⑧: pulse peak speed off `c` by >1%; Courant instability / amplitude
   blow-up; `c_EM` identity mismatch >1e-9; or transverse and longitudinal speeds collapsing together.
5. **How will we know we're done?** — **Dual verdict:** **B** = identity + stable propagation at `c` over
   1000 steps; **D** = identity only (explicitly *not* a PASS); **F** = no evolution. Physics class
   CONVERGENCE (c identity + discrete wave) / OPEN (full EM coupling). No repainting a Courant-only run as PASS.

---

## ① Executive Summary

SDT light = transverse relay at `c`. **Question:** Does a discrete 1-D (then 2-D) update with `Δx = ℓ_P`, `Δt = ℓ_P/c` reproduce wave propagation at measured c and stable Courant ≤ 1?

---

## ② Physical Context

**Native:** relay tick, movement budget caps, transverse rigidity (FLM09 viscoelastic).

**Variables:** `ψ` displacement field on lattice; Courant `C = cΔt/Δx`; `c_long = c/√3` (FD05).

**Anti-tautology firewall.** Two things must not be confused. (i) The *trivial identity*
`c = ℓ_P/t_P = 1/√(μ₀ε₀)` and the *static* Courant number `C = cΔt/Δx = 1` — both are true by the
choice `Δt = ℓ_P/c` and prove nothing about whether a wave propagates. (ii) The *load-bearing*
result: an **evolved** pulse whose tracked peak moves at `c` over ≥1000 steps. **A run that allocates
an array and prints `C = 1.0` without time-stepping is an automatic F (NO-EVOLUTION), not a PASS** —
this is exactly the error the superseded verdict made. The `c/√3` longitudinal speed is tagged
**IDENTIFICATION** (borrowed from FD05) until FD05/FLM10 earn it natively; it must come out *distinct*
from the transverse `c`, never collapsed onto it.

**Native-before-borrowed / forbidden:** Maxwell equations as primitive; photon-field QED; QM
wavefunction as the propagation mechanism; G/M-as-fundamental; any µ_B/µ_N/magneton. μ₀, ε₀ enter only
as the **OBSERVED** SI dressing of the identity, never as a derivation input.

---

## ④ Investigation Strategy

### Phase 0 — Identity (GATE)

`|c − 1/√(μ₀ε₀)|/c < 10⁻⁹`. μ₀, ε₀ from CODATA — **OBSERVED**, not DERIVED.

### Phase 1 — 1-D wave evolution (GATE — mandatory)

- **Method:** Initialize Gaussian on N≥128 cells; leapfrog or equivalent with `c`, `Δx`, `Δt` from engine; run ≥1000 steps; track peak position vs `c t`.
- **Success:** `|v_peak − c|/c < 0.01`; amplitude stable (no blow-up).
- **Forbidden:** Allocate array and print Courant only without time-stepping.

### Phase 2 — Mode speeds

- Print `c_transverse = c`, `c_longitudinal = c/√3`; label IDENTIFICATION until FD05/FLM10 earned.

### Phase 3 — Coupled pulses (DEFER)

PM01+PM02 coupled update — OPEN until PM01/PM02 PASS.

---

## ⑤ Dual verdict

| Prompt | Requirement |
|--------|-------------|
| **B** | Ph 0–1 PASS |
| **D** | Identity only |
| **F** | No evolution |

| Physics | |
|---------|--|
| **CONVERGENCE** | c identity + discrete wave |
| **OPEN** | Full EM coupling |

---

## ⑥ Outputs

`pm03_em_waves.cpp`, `pm03_results.txt`, `RUN_LOG.md`, `PM03_VERDICT.md` (replace the SUPERSEDED one with
an honest re-run; keep the banner on the old until then), optional `PM03_DERIVATION.md`.

---

## ⑧ Falsification Tests (each states the number that kills it)

| # | Test | SDT prediction | If it fails (the killing number) |
|---|------|----------------|----------------------------------|
| F1 | `c` identity (Phase 0 GATE) | `\|c − 1/√(μ₀ε₀)\|/c` < 1e-9 | mismatch > 1e-9 → relay tick ≠ EM speed; relabelling fails |
| F2 | **Evolved pulse moves at `c`** (Phase 1 GATE) | tracked peak: `\|v_peak − c\|/c` < 1% over ≥1000 steps | residual > 1% (real, not boundary artefact) → the lattice dynamics do not carry light; **a Courant-only print is F, not a pass** |
| F3 | Numerical stability | amplitude bounded; no blow-up at `C ≤ 1` | amplitude grows unbounded → instability hidden behind a static Courant claim |
| F4 | Transverse ≠ longitudinal | `c_T = c`, `c_L = c/√3` come out **distinct** (ratio 0.577, not 1) | the two speeds collapse together → the FD05 split is not real on the lattice |

---

## ⑨ Questions This Opens *(generative — log in `PM03_VERDICT.md`)*

1. **Is ε₀ a relay-stiffness and µ₀ a relay-inertia, so `c² = 1/(µ₀ε₀)` is one relay-speed statement?**
   If so, the two SI constants are not independent — they are the same lattice property read two ways.
2. **Does the same transverse-relay evolution carry the gravitational wave (GOM06) at `c`?** If light
   and GW are both transverse lattice modes, the Phase-1 evolution should reproduce both with one stencil.
3. **What is dispersion `ω(k)` near `k ∼ 1/ℓ_P`?** The short-wavelength bend is the FLM10 handoff and
   sets where light departs from exactly `c` — is there an observable high-energy photon delay?
4. **When PM01⊕PM02 are coupled (Phase 3), does the E/B-like pair self-sustain without a primitive
   field?** That is the real test of "Maxwell as relay bookkeeping" — does the coupled update *need* the
   displacement-current term, or generate it?

---

## ⑩ Adaptive Execution Protocol

```markdown
- Phase 0: |c − 1/√(µ₀ε₀)|/c < 1e-9 (identity GATE)
- Phase 1: evolved v_peak within 1% of c over ≥1000 steps (mandatory GATE)
- Forbidden: static Courant-only PASS; allocate-and-print-C without time-stepping; collapse c_T onto c_L
```

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| Amplitude blow-up at `C ≤ 1` | reduce `C`; refine stencil; check boundary | **report instability**; do not claim B | hide instability behind `C = 1.0` |
| `v_peak` off `c` by > 1% | fix `Δt/Δx`; absorbing boundary; longer run | **F (no propagation)** if real | plug `c`; widen the 1% |
| Only the static identity reachable | run the evolution anyway; if no wave moves | **D (identity only)** — explicitly *not* a PASS | sign PASS on Courant = 1.0 |
| `c_T` and `c_L` come out equal | check the transverse vs longitudinal stencil | **OPEN** the FD05 split; report the ratio | assert `c/√3` without distinctness |
| FLM10 `ω(k)` unavailable for dispersion | **DEFER** the short-k bend | — | fabricate a dispersion curve |

---

*PM03 · 10× upgrade 2026-06-29 · the wave must move, not just declare Courant = 1.*
