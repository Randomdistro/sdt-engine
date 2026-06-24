# Book I — Foundations
### *De Rerum Todo Existens*, Book the First: the matrix, the relay, the budget

> **Author:** James Christopher Harvey, Melbourne. 2026.
> **Engine:** every number below is emitted by [`de_rerum.cpp`](de_rerum.cpp) (Book I section) and
> reproduced in [`de_rerum_results.txt`](de_rerum_results.txt). Class labels (A/B/C/F) are the
> engine's own certification, kept verbatim. See [README](README.md) for the class key.

---

## 0. The refusal that starts everything

The common habit is to treat empty space as a rule-bound vacuum — a stage with laws but no substance.
SDT refuses this. *If rules exist and distance is coherent, a substrate exists.* SDT names that
substrate the **matrix** and its discrete unit the **spation**. What follows is not philosophy; it is
the scaffolding from which every later equation is built. We name four primitives, and then we are not
permitted to add a fifth.

## 1. The four primitives

1. **Space — the matrix.** An incompressible, discrete medium of spations. It is not nothing; it is the
   thing whose deformations *are* the pressure field, and whose relay carries disturbances at `c`.
2. **Matter — a boundary.** Matter is, for now, simply **matter**: a boundary that **occludes** the
   convergence. The foundations make no claim about what it is *made of* — that constitution is open,
   and we do not guess it. What they fix is what matter *does*: it is hard, present, and substantive (a
   void could not occlude), so matter is *presence*, not *absence*. That single fact — a boundary the
   flux is stopped by, not one it pours through — is what later makes gravity a push and mass a cost.
3. **Movement.** Structured flow of the matrix: shunt dynamics, circulation, the class of all change.
4. **Now.** The ordering of change, measured as an **oscillation count**. Time is the number of
   boundary interactions, not a container in which they happen: `t = N_shunts / ν`.

From these, the **pressure field** is the first equation, not an afterthought:

$$ \Pi(\mathbf{x}) = \int_{4\pi} I_\infty(\hat{\mathbf{n}})\,[1 - E(\mathbf{x}, \hat{\mathbf{n}})]\,d\Omega. $$

The convergence `I_∞` floods in from every direction; a boundary **occludes** a solid angle `E`; the
**imbalance** in what survives is force. Everything in the five books is a reading of this integral.

## 2. The master relay (Law I): the sky is a pressure source

The convergence is not an abstraction — it is the cosmic microwave background, read as the **isotropic
relay throughput** of the matrix. The engine builds it from the whitelist alone:

| quantity | meaning | value | class |
|---|---|---|---|
| `u_CMB = a_rad T⁴` | held energy density of the relay | 4.174783×10⁻¹⁴ J/m³ | B |
| `P_rad = u_CMB/3` | radiation pressure | 1.391594×10⁻¹⁴ Pa | B |
| `ε = u_CMB · ℓ_P³` | the relay quantum | 1.762640×10⁻¹¹⁸ J | B |
| `N = R_CMB/ℓ_P` | relay count to the Clearing | 5.894491×10⁶¹ | B |
| `Φ = N·ε` | total throughput | 1.038986×10⁻⁵⁶ J | B |
| `P_conv = Φ/ℓ_P³` | convergence pressure | 2.460822×10⁴⁸ Pa | B |
| `S_boundary = 4πN²` | holographic boundary count | 4.366188×10¹²⁴ | B |

This `P_conv` is the **reservoir** every force draws on. The huge ratio between `P_conv` and the
effective pressures that appear in atoms and stars is not a fine-tuning embarrassment; it is the
*screening* that the rest of the treatise computes. Note `N` here (≈5.9×10⁶¹) is the same count that
[FLM06](../../Investigations) found it cannot build "clean" from below — the relay count is fixed
**relationally** (`N² = S_boundary/4π`), not handed down absolutely. That caveat travels with Law I.

## 3. The movement budget (Law V): relativity without a postulate

A boundary moving through the matrix must spend its circulation to do so. The budget is exact:

$$ v_{\text{circ}}^2 + v^2 = c^2. $$

Special relativity is the *bookkeeping* of this one constraint — not a postulate about light, but a
statement that a thing's internal circulation and its translation share a fixed budget. The engine
confirms the budget closes and reproduces the Lorentz factor as a consequence:

- `γ(0.6c) = 1.250000` **[A]** — the textbook Lorentz factor, here a budget ratio.
- `v_circ(0.6c) = 2.398340×10⁸ m/s` **[A]**, and `v_circ² + v² = c²` to `rel = 0` **[A, PASS]**.

A photon is the limit `v_circ = 0, v = c`: it spends its entire budget on translation, which is why it
has no rest frame and no internal clock. Time dilation, length contraction, and `E = γm₀c²` all fall
out of the same line; they are derived in the engine (`law_V`), not assumed.

## 4. Mass as a cost (Law IV): inertia is reorganisation

Mass is not stuff and not a coupling to a field. It is the **throughput-reorganisation cost** of
maintaining a displacement boundary against the relay: a quantity of matrix the boundary must keep
displaced, `V_disp ∝ m`. The engine carries the map both ways:

- `V_disp(electron) = 9.980942×10⁻⁶² m³`, `V_disp(proton) = 1.832653×10⁻⁵⁸ m³` **[B]**.
- The map is invertible: `mass_from_V_disp(V_disp(m_e)) = m_e` to `rel = 1.9×10⁻¹⁶` **[A, PASS]**.

Inertia is then the relay's resistance to *moving the hole*: to accelerate a boundary is to
reorganise the throughput it displaces. The same `V_disp` reappears in Book II as the link the
proton/electron mass ratio `6π⁵` is *asserted* to map onto (a known open seam — flagged there, not
hidden).

## 5. The eliminations (what the foundations forbid)

The four primitives are a closed list, and the prohibitions are their direct consequence. Each
"missing" object of standard physics is **reconstructed as a pattern**, never imported as a primitive:

- **No G, no M.** Gravity is `g = v²/R` and `koppa = v²R/c²` (Book IV). The legacy `GM_equivalent()`
  exists only to translate *out* to textbook units.
- **No charge.** "Charge" names the **handedness of the redirected convergence**; the elementary
  charge `e` is a unit-bridge, not a substance (Book III). Only the product `k_e e² = αℏc` ever loads
  a force law — and even that line is flagged **F** (an identity, not a derivation).
- **No monopoles.** The convergence is a **throughpole** — it passes through every point, in and out,
  and never terminates. Light is a separate channel, an *emission*. A terminating point-source would be
  the forbidden monopole.
- **No wavefunctions, no fields-as-primitives, no dark sector.** Spectra (Book II), forces (Book III),
  rotation curves and cosmology (Books IV–V) are rebuilt from occlusion and circulation alone.

These are not gaps awaiting a patch. They are the **price of the four primitives**, and the rest of
*De Rerum Todo Existens* is the demonstration that the price buys the observable world back.

## 6. The derivation tree

```text
SPACE  (matrix)   → pressure Π(x)      → gradient ∇Π        → FORCE          (Laws I–III)
MATTER (boundary) → displacement V_disp → occlusion geometry → MASS, BINDING  (Law IV, II–III)
MOVEMENT          → shunt frequency ν   → v_circ²+v²=c²      → ENERGY, RELATIVITY (Law V)
NOW               → oscillation count   → ordering           → TIME, ENTROPY
```

Energy is shunt frequency, `E = hν`; force is shunt-momentum rate, `F = ν⟨Δp⟩`; entropy is
configuration count, `S = k_B ln Ω`. One root — the matrix pressure field — and every observable is a
structured response to its occlusion and circulation. The books that follow take this tree branch by
branch.

---

## Cross-references

- **Book II** — the relay's `P_conv` is screened to the atomic `P_eff` at the electropause.
- **Book III** — the eliminations of §5 (no charge, no monopole) become mechanism.
- **Book IV** — `koppa = v²R/c²` turns the budget and the relay into gravity with no G.
- `Engine/include/sdt/laws.hpp` — `measured`, `law_I`, `law_IV`, `law_V`.

## Regenerate

```bash
cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include /Fe:de_rerum.exe \
   Papers\De_Rerum_Todo_Existens\de_rerum.cpp && de_rerum.exe   # see BOOK I section
```

*Spatial Displacement Theory · De Rerum Todo Existens · Book I · J. C. Harvey, Melbourne.*
