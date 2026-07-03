# NP02: Stellar Fusion, Nuclear Growth, and Reciprocal Shell Mirroring — Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP02] NP02: Stellar Fusion, Nuclear Growth, and Reciprocal Shell Mirroring — Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## 1. Objectives

This investigation evaluates the dynamical growth of atomic nuclei from the $^4\text{He}$ core to $Z \le 20$ (H to Ca) using the Atomicus deu/tri construction grammar. We construct a pathway compiler to trace fusion trajectories, compute geometry-only contact occlusion scores and alpha-normalised occlusion units, evaluate trefoil rotational dynamics under local convergence pressure, model stellar/BBN temperature-driven electron capture (EC) delays via Saha ionization, and map the spatial coordinates of the core to the geometry of the electron shells.

## 2. Theoretical Formulations

### A. Pathway Compiler
Every nuclear addition step represents the fusion of a deuteron ($d$) or triton ($t$):
$$\text{Parent}(Z, A) + d \to \text{Child}(Z+1, A+2)$$
$$\text{Parent}(Z, A) + t \to \text{Child}(Z+1, A+3)$$

Growth pathways start at the $^4\text{He}$ core $(n_d=0, n_t=0)$ and grow recursively to target stable states.
*NP01 Atomicus Nuclear Grammar is declared FROZEN.*

### B. Occlusion Bond Symmetries & Shielding
The occlusion contact count $B_{\text{geom}}$ determines geometric occlusion structure:
$$B_{\text{geom}} = (6 + n_d + 3 n_t) + \text{interface contacts}$$
The alpha-normalised occlusion unit is calculated as:
$$E_{\text{occ\_unit}} = k_{\text{occ}} \cdot B_{\text{geom}}$$
where $k_{\text{occ}} = 28.30 / 6.0$ MeV/contact.
*Note: $E_{\text{occ\_unit}}$ represents the alpha-normalised occlusion unit scale, NOT the total binding energy $E_B$ (which would require Coulomb repulsion and saturation term integrations).*

### C. Trefoil Phase Windings & Symmetries
- **Winding W=3**: Nucleons are modeled as trefoil vortices with surface $k_p \approx 0.5464$ (superluminal rotation speed $v_p = c/k_p \approx 1.83c$).
- **Safeguard**: The rotational velocity is a *phase-winding velocity proxy* ONLY. It is not a material transport velocity and not a signal velocity.
- **Magnetic Gears**: Pairings of tritons ($n_t$ even) form counter-rotating modes, cancelling outer wake drag and maximizing stability. Odd $n_t$ results in an unpaired wake (office-pop active).

### D. Electron Capture (EC) Timing
- **Ionization Gate**: Fully ionized species at temperature $T$ cannot undergo EC due to the absence of bound electrons.
- **Saha Equation**: Determines the bound electron density at the nuclear surface:
  $$\frac{x_{\text{ion}}^2}{1 - x_{\text{ion}}} = \frac{1}{n_e} \left(\frac{m_e k_B T}{2\pi \hbar^2}\right)^{3/2} e^{-\frac{E_{\text{ion}}}{k_B T}}$$
- **Suppressor Factor**: Free electrons have high $v_{\text{trans}}$, yielding small $v_{\text{circ}}$ (movement budget), which prevents coupling to the $W=3$ core. This suppresses EC at high $T$.

### E. Inverted Mirror Mapping
- The spatial arrangement of $(n_d, n_t)$ dictates the symmetry axes of the convergence field.
- The electronic shells adjust to occupy the resulting geometric voids:
  - $n_d = 4$ (C-12) $\implies$ tetrahedral shell symmetry.
  - $n_d = 6$ (O-16) $\implies$ octahedral/cubic shell symmetry.
- **Validation**: Expand the mirror-shell mapping across the first 20 elements (H to Ca), comparing predicted shell categories (valence electron equivalents) directly to known valences with PASS/FAIL columns.

## 3. Verification Stages

- **Stage A**: Tree search from $^4\text{He}$ to $Z=10$ outputting all valid pathways and identifying bottlenecks. Declare NP01 grammar frozen.
- **Stage B**: Calculate $B_{\text{geom}}$ and $E_{\text{occ\_unit}}$, separating the occlusion-unit scale from total binding energy.
- **Stage C**: Calculate trefoil phase velocity, labeling it as a phase-winding proxy and warning against material/signal interpretations.
- **Stage D**: Temperature-dependent EC rate curves for Be-7, Tl-205, and Re-187 showing ionization state transitions.
- **Stage E**: Mirror-shell predictions across the first 20 elements with validation columns comparing against known valences.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP02
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): [commit per phase in RUN_LOG]
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

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

*NP02 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
