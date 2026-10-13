# NP22 — β-Spectrum SHAPE from Partition Geometry

> **Author:** J. C. Harvey, Melbourne. **Status:** ACTIVE (named test from NP14 VERDICT, 2026-07-04 appendix).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.

## ⓪ The five answers

1. **What don't we know?** Whether the geometric partition of one fixed internal speed — the
   0.9186c seat electron unwinding, the neutrino taking the Law-V complement — reproduces the
   *SHAPE* of the free-neutron β spectrum.
2. **Why does it matter?** NP14's appendix names this the cashable test: the rival gets the
   continuous spectrum from phase-space integrals; a geared-release geometry that reproduces the
   Kurie shape would be NATIVE class and would recover NP14's FAIL on the spot.
3. **How will we find out?** Commit ONE zero-parameter release measure (isotropic release angle
   on the seat) BEFORE code; map angle → (E_e, E_ν) via the partition + relativistic kinematics
   of the freed electron; compare dN/dE_e shape to the measured allowed shape (OBSERVED anchor).
4. **What would prove us wrong?** (T1) KS distance D > 0.15 vs the anchor; (T2) wrong endpoint
   behaviour — anchor vanishes as (Q−T)², a 1-DOF map gives step/divergence; (T3) wrong low-E
   behaviour — anchor vanishes as √T; (T4) the class-kill lemma: NO analytic 1-DOF measure can
   produce a (Q−T)² zero (see §8).
5. **How will we know we're done?** Dual verdict: prompt completion (all gates evaluated, no
   knob taken) + physics class (NATIVE / QUALIFIED / FAIL→OPEN with cascade root named).

## 1. Executive summary

NP14 (2026-07-04 appendix) found the neutron's 0.782 MeV seat surplus is exactly the kinetic
energy of an internal electron at v₀ = 0.9186c, and proposed: **the continuous β spectrum = the
variable partition of that one fixed speed between the freed electron and the neutrino (Law V:
the neutrino takes the other side of the speed budget).** This investigation runs the named
test: derive the spectrum SHAPE from release geometry alone and grade it against the standard
measured allowed shape dN/dT ∝ p_e E_e (Q−T)², Q = 0.782333 MeV. **The endpoint at Q is an
IDENTITY** (v₀ is constructed from Q) and can earn nothing. The shape is the only earnable
content. Honest FAIL/OPEN is publishable; the anchor's endpoint and low-E exponents are
dimension-counting fingerprints that any 1-DOF geometry may simply be unable to fake — finding
that out cleanly is worth the run.

## 2. Physical context

The NP17/NP20 neutron is a proton holding one internal electron on a metastable seat. At decay
the seat unwinds: the electron leaves with some retained speed v_e ≤ v₀ set by the release
geometry, and the neutrino — the unwound remainder travelling straight (PPT10: W=0, no grip,
no mass-cost) — takes the Law-V complement of the speed budget. Key variables:

- Q = (m_n − m_p − m_e)c² = 0.782333 MeV — decay budget [IDENTITY from engine masses]
- v₀/c = β₀: (γ₀−1)m_ec² = Q ⇒ β₀ = 0.91864 — the seat speed candidate [IDENTITY inversion]
- θ — release angle between the seat velocity vector and the escape direction
- T_e = (γ(v_e)−1)m_ec² — freed-electron kinetic energy; E_ν = Q − T_e (conservation ledger)
- v_ν = √(c²−v_e²) — the Law-V complement speed (reported; NOT used as the ν energy map —
  declared ontology debt: the model has no native budget-speed→E_ν map; conservation does that work)

## 3. Theoretical framework

- Law V (T10): v_circ² + v_trans² = c² — the movement budget that partitions the unbinding.
- NP17/NP20: neutron = proton + internal electron; seat surplus S = Q_β (NP14 ledger).
- PPT10: neutrino = straight light (mass-free remainder).
- Constraint: chain inputs are engine masses {m_e, m_p, m_n, c} only. **The allowed β shape
  p_e E_e (Q−T)² sits in the OBSERVED column ONLY — it is the rival's phase-space machinery and
  is NEVER imported into the SDT chain.** Coulomb (Fermi-function) correction, recoil-order and
  radiative corrections: OMITTED in v1 (declared; for Z=1 these are few-% and do not move the
  qualitative shape).

## 4. Investigation strategy

**Phase 1 — anchor + identities (½ h).** Compute Q, β₀, complement √(1−β₀²) from engine masses.
Build the anchor PDF/CDF on [0,Q]. Label every identity as IDENTITY. Gate: β₀ within 0.1% of
NP14's 0.91859c (bookkeeping consistency, not physics).

**Phase 2 — committed measure M1 (1 h).** Isotropic release direction on the sphere relative to
the seat velocity (the natural zero-parameter choice, committed in RUN_LOG before code);
electron keeps the projection v_e = v₀|cosθ| ⇒ u = |cosθ| ~ U(0,1). Closed-form CDF
F(T) = β(T)/β₀. Monte-Carlo cross-check (10⁷ samples, fixed seed) must agree with the analytic
CDF to < 10⁻³ (numerics gate). Compare to anchor: KS D (primary), total-variation on 50 bins,
means, zone ledger (mass in [0,0.1Q], thirds, [0.9Q,Q]), low-E and endpoint log-log exponents.

**Phase 3 — declared scan (1 h).** Fixed alternates, declared in RUN_LOG before any result is
seen, graded as scan (cannot PASS even if they land): M0 tangential/slingshot limit (line at Q);
M2 energy-projection T = Q cos²θ; M3 planar seat-phase u = |cosφ|, φ ~ U[0,2π). No measure may
be added after results exist.

**Phase 4 — class-kill check (½ h).** Numerically verify the endpoint/low-E exponents of anchor
vs all measures. The lemma (stated here, before running): a 1-DOF release map T(s), analytic,
with bounded non-vanishing measure density w(s), gives spectral density N = w/|dT/ds| whose
endpoint behaviour is a finite step (T′≠0) or an inverse-power divergence (T′→0) — analytic
maps give exponents in {0, −1/2, −2/3, …}, **never +2**. The anchor's (Q−T)² zero (and its √T
low-E zero) are 3D state-count fingerprints — one per light particle. If verified, the whole
1-DOF class is killed, not just M1.

## 5. Success criteria (dual verdict)

- **PASS (NATIVE):** committed M1, zero knobs, KS D ≤ 0.05, endpoint + low-E behaviour
  qualitatively right. Would recover NP14's FAIL; publish as the geared-release derivation.
- **QUALIFIED (Class C):** 0.05 < D ≤ 0.15 with the deviations localised and named.
- **FAIL → OPEN:** D > 0.15 or wrong limit behaviour at either end. Publishable as: the
  partition CONTINUUM is real but the 1-DOF release measure cannot carry the shape; cascade
  root = the release-measure geometry (what counts exit states) → FLM14 gearing / lattice
  direction-count lineage.
- The endpoint T_max = Q is IDENTITY under every outcome and is never sold.

## 6. Outputs

1. `RUN_LOG.md` — pre-commitments (written BEFORE the tool; gates + forbidden retro list)
2. `np22_beta_spectrum.cpp` — standalone C++20 tool, `<sdt/laws.hpp>` only
3. `np22_results.txt` — redirected stdout (tables: identities, per-measure KS/TV/zones/exponents)
4. `NP22_VERDICT.md` — dual verdict, §D seven questions on any kill, canonical verdict line

## 7. Dependencies & references

- **Upstream:** NP14 VERDICT 2026-07-04 appendix (the named test); NP17/NP20 (seat premise);
  PPT10 (neutrino = straight light); Law V (`laws.hpp::law_V`).
- **Downstream:** NP14 recovery (only on PASS); FLM14 (inherits the cascade root on FAIL);
  PPT10/PPT11 ν-energy map (the ontology debt in §2).
- **Related:** NP11 (neutron lifetime), SCT regime II (why decay is downhill).

## 8. Falsification tests

| Test | Hypothesis | Predicted outcome if TRUE | If FAIL |
|------|-----------|---------------------------|---------|
| T1 | M1 shape matches anchor | KS D ≤ 0.05 | D > 0.15 ⇒ measure cannot carry shape |
| T2 | Endpoint behaviour | N → 0 as (Q−T)² | model gives step/divergence ⇒ ν-side 3D count missing |
| T3 | Low-E behaviour | N → 0 as √T | model diverges as T^(−1/2) ⇒ e-side 3D count missing |
| T4 | Class-kill lemma | some 1-DOF measure evades it | no analytic 1-DOF measure can give exponent +2 ⇒ whole class KILLED |

## 9. Implementation notes

Deterministic CDFs (closed-form for M0–M3; fine-grid trapezoid for the anchor), KS on the
common grid — no MC noise in the graded numbers; MC used only as a numerics cross-check.
Double precision throughout; energies in MeV via `measured::MeV_to_J`. Exponent probes: log-log
slope over declared windows T ∈ [10⁻⁴Q, 10⁻²Q] (low end) and (Q−T) ∈ [10⁻³Q, 3·10⁻²Q]
(endpoint) — diagnostic readouts, not fit knobs.

## ⑩ Adaptive execution protocol

Pre-run commitment block: see `RUN_LOG.md` (written before the tool).

| Trigger (numeric) | First response (PIVOT) | If pivot fails | Forbidden response |
|-------------------|------------------------|----------------|--------------------|
| M1 D > 0.15 | Grade declared scan M0/M2/M3 as scan (cannot PASS) | Run Phase 4 class-kill; verdict FAIL→OPEN, cascade root named | Invent a new measure after seeing the miss; reweight the measure; widen D gates |
| MC vs analytic CDF > 10⁻³ | Fix numerics only (grid/seed) | Report tool defect, no verdict | Grade with broken numerics |
| Anchor endpoint exponent ≠ 2±0.2 | Check window/grid | Report anchor-build defect | Tune anchor until it "looks right" |
| Scan member lands D ≤ 0.05 | Log as [OPEN] privileged lead, look-elsewhere applies | — | Promote a scan member to PASS |

**Allowed:** grid refinement, exponent-window sanity checks, phase splits.
**Disallowed:** RETRO-PASS, PLUG, IDENTITY-PASS (selling the endpoint), importing p²dp
state-counting into the chain, post-hoc measures or weights.

---

*NP22 · spec 2026-07-04 · from NP14's named test · J. C. Harvey, Melbourne.*
