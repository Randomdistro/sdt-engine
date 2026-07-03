# PPT02: Ground-State Velocity, Bohr Radius, and the Fine-Structure Constant from Topology

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [PPT02] PPT02: Ground-State Velocity, Bohr Radius, and the Fine-Structure Constant from Topology: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. Mathematical Framework & Definitions

In Spatial Displacement Theory (SDT), space is an inviscid, phase-loaded spation lattice under convergent pressure. Subatomic defects (vortices) act as throughput occluders, generating forces and establishing stable orbits.

| Symbol | Name | SDT Definition / Value | Physical Meaning |
|--------|------|------------------------|------------------|
| $\alpha$ | Fine-structure constant | $7.2973525693 \times 10^{-3}$ | The dimensionless ratio of the electron's wake boundary to its quantum coherence scale: $r_e / \bar{\lambda}_{C,e}$. |
| $\hbar$ | Reduced Planck constant | $1.054571817 \times 10^{-34}$ J·s | Fundamental quantum of action in the spation lattice. |
| $c$ | Speed of light | $299,792,458$ m/s | Nearest-neighbour relay speed of the lattice: $\ell_P / t_P$. |
| $m_e$ | Electron mass | $9.1093837015 \times 10^{-31}$ kg | Spation lattice displacement/exclusion cost of the $W=1$ torus. |
| $r_e$ | Classical electron radius | $2.8179403262 \times 10^{-15}$ m | The electron's wake radius: the boundary of its lattice pressure perturbation. |
| $\bar{\lambda}_{C,e}$ | Reduced Compton wavelength | $\hbar / (m_e c) \approx 3.86159 \times 10^{-13}$ m | The quantum coherence scale of the electron. |
| $a_0$ | Bohr radius | $\hbar / (m_e c \alpha) \approx 5.29177 \times 10^{-11}$ m | The stable ground-state orbital radius of the hydrogen atom. |
| $\ϟ_H$ | Hydrogen Koppa | $\alpha^2 a_0 \approx 2.81794 \times 10^{-15}$ m | The gravitational c-boundary of hydrogen: where local orbital speed equals $c$. |

---

## 2. The Subatomic Force-Quantization Closure

The first-principles derivation of the hydrogen ground-state orbit and velocity proceeds directly from two geometric constraints in SDT, requiring no external field ontology or charge primitives:

### 2.1 The Occlusion Force Balance
In SDT, the electrostatic force arises from the convergent boundary pressure (Law III) and balances the centrifugal pressure of the circulating vortex:
$$F_{\text{occlusion}} = F_{\text{centrifugal}}$$
$$\frac{k_e e^2}{r^2} = \frac{m_e v^2}{r} \implies \frac{k_e e^2}{r} = m_e v^2$$
where $k_e e^2 = \alpha \hbar c$ is the Coulomb coupling product, acting as the scale-dependent coupling strength.

### 2.2 Law VI Circulation Quantization
For the fundamental mode ($n = 1$) of the stable $W=1$ torus vortex:
$$m_e v r = \hbar \implies \frac{1}{r} = \frac{m_e v}{\hbar}$$

### 2.3 Deriving Ground-State Velocity ($v$) and Radius ($a_0$)
Substituting the quantized radius into the force balance equation:
$$k_e e^2 \left( \frac{m_e v}{\hbar} \right) = m_e v^2$$
Dividing both sides by $m_e v$ yields the ground-state velocity:
$$\boxed{v = \frac{k_e e^2}{\hbar} = \alpha c}$$

The stable orbital radius (Bohr radius $a_0$) immediately follows:
$$\boxed{a_0 = \frac{\hbar}{m_e v} = \frac{\hbar}{m_e c \alpha}}$$

### 2.4 Deriving the Hydrogen Koppa ($\ϟ_H$)
The c-boundary ($\ϟ$) of any system represents the scale at which the orbital velocity equals $c$. For the hydrogen ground state:
$$\ϟ_H = \frac{v^2 a_0}{c^2} = \alpha^2 a_0 = \alpha^2 \left( \frac{\hbar}{m_e c \alpha} \right) = \frac{\alpha \hbar}{m_e c} = r_e$$

This establishes the exact identity:
$$\boxed{\ϟ_H = r_e}$$
The gravitational c-boundary of the hydrogen atom is identically the classical electron radius (the electron's wake radius). This is a clean geometric link between atomic and gravitational regimes that general relativity and the Standard Model cannot make.

---

## 3. Ontological Status of Charge and $\alpha$

SDT operates under a strict ruleset prohibiting fields or charge as primitives:
* **No Charge Primitives**: There is no physical "charge quantum" $e$ in the spation lattice. What we call "charge" is a macroscopic measurement of the occlusion of convergent lattice throughput by a vortex defect.
* **$\alpha$ as a Boundary Ratio**: The fine-structure constant $\alpha$ is a purely dimensionless ratio of physical boundaries:
  $$\alpha = \frac{r_e}{\bar{\lambda}_{C,e}}$$
  It measures what fraction of the electron's quantum coherence scale is occupied by its lattice wake perturbation.

---

## 4. The Circularity Proofs (Why $\alpha$ is a Tier-1 Input)

While the relationships between $v$, $a_0$, $\ϟ_H$, and $r_e$ close exactly, they cannot be used to *derive the numerical value* of $\alpha \approx 1/137.036$ from scratch. Every attempt to back-solve $\alpha$ is mathematically circular:

1. **Bohr Orbit Loop**: Back-solving $\alpha = \hbar / (m_e c a_0)$ is circular because the scale of $a_0$ is itself a downstream consequence of $\alpha$ (force balance is scaled by $\alpha$).
2. **Koppa Loop**: Back-solving $\alpha = \sqrt{\ϟ_H / a_0}$ is circular because the c-boundary $\ϟ_H = r_e$ is scaled by $\alpha$.
3. **Lattice Constant Cancellation**: Substituting the transfer function $f$ into the convergence pressure $P_{\text{conv}}$ yields $\alpha = \alpha \times 1$. Every cosmological and lattice factor cancels in pairs, proving $\alpha$ is a load-bearing input that does not depend on the cosmological scale.

### Conclusion:
The numerical value of $\alpha$ cannot be derived from the $W=1$ torus geometry alone. The electron (being an unknotted loop) has no crossing constraints to fix its wake radius $r_e$. Its wake size is fixed by its coupling back to the lattice, which is $\alpha$. 

Therefore, $\alpha$ is a Tier-1 input in the current framework. The minimal input set is **$\{\ell_P, T_{\text{CMB}}, \alpha, d=3\}$**. Reducing to three inputs requires **FLM05: Topological Charge Quantisation**, which aims to derive the defect wake boundary $r_e$ directly from spation lattice reconnection dynamics.

---

## 5. Success Criteria for PPT02

- [x] Prove the exact subatomic closure: $v = \alpha c$ and $a_0 = \hbar / (m_e c \alpha)$ derived from force balance and circulation quantization.
- [x] Prove the Koppa identity: $\ϟ_H = r_e$ exactly.
- [x] Document the 11/11 circularity proofs verifying that $\alpha$ cannot be back-solved from subatomic relations.
- [x] Establish the ontological status of $\alpha$ as the vortex wake-to-quantum ratio $r_e / \bar{\lambda}_{C,e}$.
- [x] Map the forward dependency to FLM05 for the derivation of $\alpha$ from lattice topology.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PPT02
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: law_VI winding, bridge::k_*, PPT01 equilibrium
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

*PPT02 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
