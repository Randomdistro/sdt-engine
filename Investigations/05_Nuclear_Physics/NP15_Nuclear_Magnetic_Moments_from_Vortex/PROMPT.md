# NP15: Nuclear Magnetic Moments from Vortex Geometry — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP15] NP15: Nuclear Magnetic Moments from Vortex Geometry — Investigation Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. The Question

The proton's magnetic moment is +2.793 μ_N — anomalous (not 1.0) because it is not a point charge. The neutron has μ = −1.913 μ_N despite being neutral. Standard physics explains these via quark substructure. SDT must explain them from the W=3 trefoil torus circulation.

## 2. Methodology

### Step 1: Magnetic moment from circulation

A current loop produces a magnetic moment μ = IA. For a torus:
- The toroidal circulation (v_T, around the major axis) generates a poloidal magnetic moment
- The poloidal circulation (v_P, around the minor axis) generates a toroidal magnetic moment

For the proton (charged, W=3):
- The charge circulates with the torus flow
- μ_proton = contribution from ALL three circulation modes
- The W=3 trefoil means the charge traces the torus 3 times poloidally per toroidal circuit
- This amplifies the magnetic moment by a factor related to W

### Step 2: Derive μ_proton

$$\mu_p = \frac{e}{2m_p c} \times g_p \times (\text{mode structure factor})$$

Where g_p is the Landé g-factor. SDT predicts g_p from the trefoil geometry:
- g_p = (W+1)/2 × (v_P/v_T ratio) × (helicity correction)
- Must give g_p = 5.586 (since μ_p = g_p × μ_N / 2 = 2.793)

### Step 3: Derive μ_neutron

The neutron has the SAME W=3 topology but NO net charge. However, its internal circulation generates charge separation:
- The neutron's trefoil has regions of + and − charge density (measured)
- The circulating charge distribution generates a NET magnetic moment
- The sign is NEGATIVE because the charge distribution's centroid is opposite to the proton's

SDT must explain:
- Why μ_n / μ_p ≈ −2/3 (is this a geometric ratio from the trefoil?)
- Why the neutron has a negative moment (the charge distribution is inverted)

### Step 4: Composite nuclei

For d (p+n), t (p+2n), He-3 (2p+n):
- Add the constituent moments vectorially
- Account for the relative spin orientations in the ground state
- μ_d should ≈ μ_p + μ_n = 0.880 (measured: 0.857 — 2.6% off → exchange current correction in standard model; what is the SDT equivalent?)

### Step 5: Schmidt limits comparison

Standard nuclear physics has the Schmidt limits: μ_free_nucleon applied to single-particle states. SDT should reproduce these from the vortex geometry of the scaffold.

## 3. Required Outputs

1. **μ_proton derivation**: From W=3 trefoil geometry → 2.793 μ_N
2. **μ_neutron derivation**: From charge-separated W=3 → −1.913 μ_N
3. **Composite nuclei table**: Predicted vs measured for d, t, He-3, He-4
4. **μ_n/μ_p ratio**: Is −2/3 a geometric consequence of the trefoil?
5. **Prediction for heavier nuclei**: Using grammar (d+t block structure), predict moments for Li-7, Be-9, etc.

## 4. Success Criteria

- [ ] μ_proton reproduced within 5% from geometric argument
- [ ] μ_neutron sign (negative) and magnitude explained
- [ ] μ_n/μ_p ratio explained geometrically
- [ ] Deuteron moment predicted within 5%
- [ ] α moment = 0 explained by tetrahedral cancellation
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP15
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): 2.6%, 5%, 5%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

> NOTE: 2.6% equals the known μ_d discrepancy — re-commit a blind threshold before running.

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*NP15 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
