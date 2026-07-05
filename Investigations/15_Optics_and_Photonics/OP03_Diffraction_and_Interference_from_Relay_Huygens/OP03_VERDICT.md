# OP03 — Verdict: Diffraction and Interference from Relay-Huygens Summation

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-04 · Tool: `op03_relay_huygens.cpp` (exit 0; stdout in `results.txt`; ADJ-001 in `RUN_LOG.md`)

## The located λ entry point (the honest headline)

λ enters as the **assumed tick periodicity of the emission** (λ = c_local·T_tick). The CR07 ruler
λ = N·ℓ_P is a re-parameterisation of that assumption, not a derivation of it. Once a periodic
impulse train is summed over re-emission sites with arrival-time offsets, **interference exists by
construction** — Huygens summation IS interference. Nothing in this investigation derives the
periodicity, and no claim is made that it does.

## Earned (real stdout; geometry only, machinery only)

- Discrete relay sum → continuum envelope monotonically (1.4e-03 at M=16 → 2.0e-08 at M=4096); the
  continuum sinc² was a comparison column, never the kernel.
- Two-source maxima at mλ/d exact (m=1..5, rel err 0.0); grating N=10: peak-to-first-zero offset
  = λ/(Nd) to 6e-08 ⇒ **R = mN as a pure site-counting statement**.
- Single-slit first null at λ/a to 2.3e-08; Airy first dark ring at 1.21967λ/D to 1.1e-16, from
  chord site-count columns (counting, not a Bessel import).
- Granularity: deviation ∝ s² confirmed (exponent 2.003); extrapolated to s = ℓ_P at 500 nm:
  **~2.4e-62 — an honest null.** No SDT≠continuum-optics diffraction signature exists; reported, not inflated.

## Owed (the honest caps and opens)

1. **Obliquity/backward wave: OPEN, demonstrated.** Isotropic relay re-emission gives
   backward/forward = 1 identically (run output). The inclination factor does not emerge and was
   not bolted on. Forward directionality of the relay rule is the unbuilt piece.
2. **F4 single-emission build-up: OPEN here**, deferred to QM01's residence-histogram machinery —
   this tool does not simulate one-emission arrival statistics and does not claim to.
3. **Sub-wavelength/near-field: not gated** (§G) — constraint-channel territory (FLM14 ADJ-7),
   owed a two-channel treatment, not legislated away.

## §D seven questions (on the obliquity OPEN — the load-bearing F1 row)

1. **Why open?** Backward/forward ratio = 1 exactly; Kirchhoff's (1+cosχ)/2 requires forward
   preference the isotropic re-emission rule does not contain. Sign/magnitude fully characterised.
2. **Recoverable?** Plausibly: a re-emitting site does not receive isotropically — it receives from
   the incident side and hands on in the direction of impulse arrival. A relay rule carrying the
   incident impulse VECTOR (not just its clock) would break the symmetry natively.
3. **What did the target fail to account for?** The re-emission was modelled as a point clock;
   the impulse's direction of travel was discarded at each site.
4. **Errored premise?** "Secondary re-emission is isotropic" — that premise is refuted by the run
   itself (it forbids the observed absence of backward waves).
5. **What freedom corrects it?** The retained impulse direction (a per-site vector) — no new number.
6. **Native or knob?** Native: the relay tick rule already has an arrival direction; retaining it
   costs no parameter. (If a *specific* angular weight must be inserted to match Kirchhoff, THAT
   would be a knob — the test for the follow-up tool.)
7. **Cascade?** Yes — same root as OP02's pairing rule: the **OP-root debt** (explicit
   transverse/directional relay rule on the discrete lattice; QM01/FLM08 territory).

**Recovery grade: PARTIAL** (freedom named and native; not yet executed).

## Generative questions logged

Q1: the run sharpens it — the obliquity derivation reduces to "does retaining arrival direction
suffice?"; falsifiable in a follow-up tool. Q3/Q4: answered negatively — the granularity floor is
~1e-62 and the N→1 (λ→ℓ_P) breakdown is 28 orders beyond any beam. Q5: R = mN confirmed as a
relay-source count.

---

**Prompt completion C · Physics class CONVERGENCE · Recovery PARTIAL · Cascade root: OP-root (directional relay rule; shared with OP02-pairing)**
