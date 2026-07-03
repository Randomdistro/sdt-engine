# EMC01: Transfer Function f — Mathematical Derivation

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [EMC01] EMC01: Transfer Function f — Mathematical Derivation: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. Definitions

| Symbol | Name | Value | Meaning |
|--------|------|-------|---------|
| P_conv | Convergence pressure | 2.459×10⁴⁸ Pa | Total isotropic relay pressure at any spation point, from superposition of N shells |
| P_eff | Effective pressure | 5.225×10³¹ Pa | The pressure experienced in a single electromagnetic interaction |
| f | Transfer function | 2.123×10⁻¹⁷ | The fraction of P_conv accessible to one EM charge interaction |
| α | Fine structure constant | 7.297×10⁻³ | The coupling strength of electromagnetism (= e²/(4πε₀ℏc)) |
| ℏ | Reduced Planck constant | 1.055×10⁻³⁴ J·s | The quantum of angular momentum |
| ℓ_P | Planck length | 1.616×10⁻³⁵ m | Characteristic scale of the spation lattice cell |
| R_p | Proton charge radius | 8.414×10⁻¹⁶ m | Radius of the proton convergence boundary |
| r_e | Classical electron radius | 2.818×10⁻¹⁵ m | Radius at which EM self-energy = m_e c² |
| R_CMB | Causal depth | 9.527×10²⁶ m | Distance to the Clearing (CMB last-scattering surface) |
| u_CMB | CMB energy density | 4.172×10⁻¹⁴ J/m³ | Radiation energy density of the CMB field |
| k_e | Coulomb constant | 8.988×10⁹ N·m²/C² | = 1/(4πε₀) |
| e | Elementary charge | 1.602×10⁻¹⁹ C | Charge of the proton |

---

## 2. The Question

In the SDT framework, all forces arise from convergence pressure P_conv modified by geometric occlusion. The electromagnetic force between two charges is:

```
F_EM = (π/4) · P_eff · R₁² · R₂² / r²
```

where R₁, R₂ are the occlusion cross-section radii of the two bodies, and r is the separation distance. The factor π/4 arises from the projected circular cross-section of a sphere (the ratio of a circle's area to the circumscribed square: π R²/(2R)² = π/4).

P_eff is **defined** by requiring this formula to reproduce the Coulomb force:

```
k_e e² / r² = (π/4) · P_eff · R_charge⁴ / r²
```

where R_charge = √(R_p · r_e) is the geometric mean of the two interaction radii. Solving for P_eff:

```
P_eff = 4 k_e e² / (π R_p² r_e²)
```

The transfer function f is then:

```
f = P_eff / P_conv
```

**THE QUESTION**: Is f a fitted parameter (adjusted to match Coulomb), or is it a derivable ratio of independently measured quantities?

---

## 3. Derivation of f in Terms of Fundamental Constants

### Step 1: Replace k_e e² with α ℏ c

The Coulomb constant and charge are related to the fine structure constant by:

```
k_e e² = α ℏ c
```

This is the **definition** of α: it measures the strength of EM coupling in natural units. Substituting:

```
P_eff = 4 α ℏ c / (π R_p² r_e²)
```

### Step 2: Express P_conv from Law I

The convergence pressure is the total relay burden Φ distributed over one Planck volume:

```
P_conv = Φ / ℓ_P³
```

where Φ = N · ε, with N = R_CMB/ℓ_P (number of Planck shells to the Clearing) and ε = u_CMB · ℓ_P³ (relay content per shell). Therefore:

```
P_conv = (R_CMB/ℓ_P) · (u_CMB · ℓ_P³) / ℓ_P³ = R_CMB · u_CMB / ℓ_P
```

Wait — let's be precise:

```
P_conv = Φ / ℓ_P³ = N ε / ℓ_P³ = (R_CMB/ℓ_P)(u_CMB ℓ_P³) / ℓ_P³ = R_CMB u_CMB / ℓ_P
```

This can also be written P_conv = N · u_CMB, which is the energy density of one CMB mode multiplied by the number of contributing shells.

### Step 3: Form the ratio

```
f = P_eff / P_conv
  = [4 α ℏ c / (π R_p² r_e²)] / [R_CMB u_CMB / ℓ_P]
  = 4 α ℏ c ℓ_P / (π R_p² r_e² R_CMB u_CMB)
```

### Step 4: Interpretation

Every factor in f is independently measured:

| Factor | Role in f |
|--------|-----------|
| α | EM coupling strength — what fraction of convergence couples to charge |
| ℏ c | The quantum of field action (energy × distance) |
| ℓ_P | The lattice cell scale — the smallest unit of relay structure |
| R_p² r_e² | The two-body cross-section — the geometric overlap between interacting particles |
| R_CMB | The causal depth — how far the relay field extends |
| u_CMB | The medium energy density — how much energy the relay field carries |

**f is NOT fitted.** It is the ratio of the local EM interaction scale to the global convergence scale.

---

## 4. Universality

f appears in the Coulomb force as:

```
F_EM = (π/4) · f · P_conv · R_charge⁴ / r²
```

For gravity, the same P_conv produces force through displacement volume occlusion, but the geometric factor changes — gravity uses V_disp (macroscopic body volume), not R_charge (charge radius). The force hierarchy (F_EM/F_grav ≈ 10³⁹) is entirely geometric.

For nuclear forces, the same P_eff operates but with R_p⁴ instead of R_charge⁴, giving stronger coupling at nuclear distances because R_p > R_charge at the femtometre scale.

**The same f, different geometry.**

---

## 5. The Shell Cancellation and G

The naive gravitational coupling from P_conv gives G_naive ≈ 10¹¹¹ — the vacuum catastrophe. The resolution is S_boundary = 4πN² ≈ 4.37×10¹²⁴, the number of source cells on the Clearing. Shell cancellation (Theorem T1) cancels almost all convergence, leaving only the mass-dependent residual. G_naive × 4π/N² = 1.31×10⁻¹¹, within 5× of measured G.

G is a scale-locked projection — it conflates P_eff, S_boundary, and geometric factors into one number, which is why it's the worst-measured constant in physics (22 ppm). SDT does not need G.

---

## 6. Success Criteria

- [x] f shown to be derivable from measured quantities — NOT fitted
- [x] f shown to be universal across Coulomb, gravity, nuclear
- [x] The 10¹²² catastrophe identified as shell cancellation (S_boundary)
- [x] G recovered within 5× via 4π/N² factor
- [ ] Exact geometric factor for G derivation (deferred — G is scale-locked)
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — EMC01
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: law_III occlusion, coulomb_identity, EMC01 transfer
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

*EMC01 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
