# OP01 — Derivation: Refraction and Dispersion as a Spation Gradient-Index Medium

**Domain:** Optics and Photonics (SDT depth–closure)  
**Author:** James Christopher Tyndall, Melbourne  
**Status:** EXECUTED — Class C (CONVERGENCE) on vacuum limb; matter index OPEN  
**Tool:** `op01_gradient_index.cpp` · cross-check `GOM01` path integral

*Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.*

---

## 0. Thesis in one line

Optical refraction and gravitational light bending are the same mechanism in SDT: local relay speed is set by convergence depth \(z = \varkappa/r\), giving \(c_{\text{local}} = c(1-z)\) and \(n = 1/(1-z)\); Snell's law follows from Fermat least-time on that index, and the solar limb deflection \(\delta = 4\varkappa/b\) is the vacuum limit of the same formalism.

---

## 1. H1 — Index from closure ratio

From the Depth–Closure Theorem (`depth_closure` in `laws.hpp`):

\[
z(r) = \frac{\varkappa}{r} = \frac{1}{k^2} = \left(\frac{v}{c}\right)^2, \qquad
c_{\text{local}} = c_\infty(1-z), \qquad
n(r) = \frac{c_\infty}{c_{\text{local}}} = \frac{1}{1-z}
\]

**Validity:** weak field only (\(z \ll 1\)). If \(z \to 1\), \((1-z)\) diverges — pivot per CR10 precedent.

**Vacuum (solar well):** \(\varkappa_\odot = R_\odot/k_\odot^2\) (`bridge::koppa_Sun`), so at the photosphere

\[
z_\odot = \frac{\varkappa_\odot}{R_\odot} = \frac{1}{k_\odot^2} \approx 2.123\times 10^{-6}, \qquad
n(R_\odot) \approx 1.00000212
\]

**Matter (electropause route — corrected):** hydrogen ground electropause from **native balance** (see `Investigations_Composer/03_Electromagnetism_and_Charge/EMC04_Electropause_SDT_Native/`):

1. `k_H = 1/α`, `v = c/k_H` (k-rung, not Bohr postulate)
2. One closed wake: `r* = ℏ/(m_e v)` **[DERIVED]** — do **not** input `atomic::bohr_radius()`
3. `z* = (v/c)² = 1/k_H²`, `n* = 1/(1-z*) ≈ 1.00005`

Route A/B in the first OP01 run (`z = koppa_H/a₀` or `z = α²` alone) was **lazy** — it tagged identity, not bulk matter. Water needs **stacked** electropause compression, not single-atom `z`.

**zk² identity (anchor, not a fit):**

\[
z_H \cdot k_H^2 = \alpha^2 \cdot (1/\alpha)^2 = 1 \quad \text{[IDENTITY]}
\]

---

## 2. H2 — Snell from Fermat stationarity

Light follows the path of **least relay time** through a piecewise-uniform medium. For a horizontal interface between \(n_1\) and \(n_2\), with source at \((0,h_1)\), receiver at \((d,h_2)\), crossing at \((x,0)\):

\[
T(x) = \frac{n_1 L_1 + n_2 L_2}{c}, \qquad
L_1 = \sqrt{x^2 + h_1^2}, \quad L_2 = \sqrt{(d-x)^2 + h_2^2}
\]

Stationarity \(\mathrm{d}T/\mathrm{d}x = 0\) yields

\[
n_1 \sin\theta_1 = n_2 \sin\theta_2
\]

**Total internal reflection:** when no real refracted angle exists, \(|\sin\theta_2| > 1\) — same algebra, no separate mechanism.

**Protocol note:** demonstrating Snell with **OBSERVED** lab indices (e.g. water 1.333) is a **CONVERGENCE ROW ONLY** — it is not a PASS on H2. H2 requires Fermat on a **computed** \(n_{\text{pred}}\).

---

## 3. H3 — Lensing ≡ refraction (solar limb)

For spherically symmetric \(n(r) = 1/(1-\varkappa/r)\), the small-angle deflection at impact parameter \(b\) is

\[
\boxed{\delta(b) = \frac{4\varkappa}{b}}
\]

**Derivation sketch (GOM01, native):** transverse gradient of depth along the ray path,

\[
\nabla_\perp z = -\frac{\varkappa b}{r^3}, \qquad
\delta = 2\int |\nabla_\perp z|\,\mathrm{d}\ell = \frac{4\varkappa}{b}
\]

where the path integral \(\int (b/r^3)\,\mathrm{d}\ell = 2/b\) for a straight-line grazing ray.

**Equivalent refractive route:** isotropic weak-field form \(n_{\text{eff}} \approx 1 + 2\varkappa/r\) (GOM01 §IV) gives the same factor of 4 from Fermat/eikonal — not an ad hoc doubling.

At the solar limb \(b = R_\odot\):

\[
\delta = \frac{4\varkappa_\odot}{R_\odot} = \frac{4}{k_\odot^2 R_\odot/R_\odot} = \frac{4}{k_\odot^2}\,\text{(in radians when } \varkappa/R = 1/k^2\text{)}
\]

Numerically: \(\delta \approx 8.487\times 10^{-6}\,\text{rad} = 1.7517''\) vs VLBI target **1.750″** (0.10% error).

**DEGENERATE note:** \(\varkappa_\odot = R_\odot/k_\odot^2\) maps to \(GM/c^2\) under bridge equivalency — the 1.75″ match is **CONVERGENCE** with standard GR at 1PN, not an independent optics prediction until matter \(n\) is native.

**Integral cross-check:** the path integral along the ray (GOM01 method) agrees with \(4\varkappa/b\) to \(<10^{-6}\) relative. [PHANTOM — no source computes this; retracted] A radial-only eikonal quadrature in `op01_gradient_index.cpp` (Phase 3) uses incomplete geometry and **does not** reproduce the closed form — see RUN_LOG ADJ-002; use GOM01 integral for gate verification until fixed.

---

## 4. H4 — Dispersion scaffold (Phase 4 minimum)

Leading lattice-granularity coupling (schematic):

\[
n(\lambda) = n_0 + \beta\left(\frac{\ell_P}{\lambda}\right)^2
\]

With \(\beta = 1\) flagged **CALIBRATED(1)** — not yet derived from mode counting (E61). At \(\lambda = 550\,\text{nm}\), \(\Delta n \sim 10^{-42}\): negligible at solar \(n_0\); fold-band ray-trace deferred to **OP01b**.

---

## 5. Parameter ledger

| Quantity | Symbol | Provenance |
|---|---|---|
| Speed of light | \(c\) | **OBSERVED** (`measured::c`) |
| Solar radius | \(R_\odot\) | **OBSERVED** (`measured::R_Sun`) |
| Solar k-rung | \(k_\odot\) | **DERIVED** (`bridge::k_Sun`) |
| Solar koppa | \(\varkappa_\odot\) | **DERIVED** (`bridge::koppa_Sun`) |
| Fine structure | \(\alpha\) | **OBSERVED** (`measured::alpha`) |
| Bohr radius | \(a_0\) | **DERIVED** at electropause (`ℏ/(m_e α c)`) — compare CODATA in OBSERVED column only |
| Hydrogen koppa | \(\varkappa_H\) | **DERIVED** (`bridge::koppa_hydrogen`) |
| Water index | 1.333 | **OBSERVED** — comparison target only |
| Limb deflection | 1.750″ | **OBSERVED** (VLBI) |
| Dispersion \(\beta\) | 1 | **CALIBRATED(1)** — scaffold only |

**Free parameters in derivation chain: 0.** (Phase 4 \(\beta\) is explicitly CALIBRATED, not used in Phases 0–3 gates.)

---

## 6. Weak-field break and open paths

| Regime | Status |
|---|---|
| Vacuum limb \(\delta = 4\varkappa/b\) | **PASS** — CONVERGENCE/DEGENERATE with GR |
| Snell from Fermat on computed \(n\) | **PASS** — algebra verified numerically |
| Bulk matter \(n\) (water 1.333) | **OPEN** — electropause \(z = \alpha^2\) is \(10^4\times\) too small |
| Eikonal integral in OP01 tool | **FAIL** — wrong quadrature geometry; GOM01 path integral PASS [PHANTOM — no source computes this; retracted] |
| Dispersion + solar fold | **DEFER** → OP01b |

**Path to Class A:** derive bulk \(z\) from bound-vortex **compression** (occlusion packing in water/glass) without CALIBRATED \(n\); fix OP01 Phase 3 integral to GOM01 path form; derive \(\beta\) from lattice mode counting.
