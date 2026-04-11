# Closure Derivations

These four results convert assumptions into mechanisms.

## 1. τ = 1/3 — Local Derivation

The convergence stress tensor is isotropic:

$$\Pi_{ij} = \frac{P_{\text{conv}}}{3}\delta_{ij}$$

At a boundary point with outward normal $\hat{n}$:

$$\sigma_n = \hat{n}_i \Pi_{ij} \hat{n}_j = \frac{P_{\text{conv}}}{3}$$

The tangential stress carries $2P_{\text{conv}}/3$. Centrifugal pressure resists the normal component:

$$\tau = \frac{\sigma_n}{\text{tr}(\Pi)} = \frac{1}{3}$$

This is **local** (every boundary point independently), not global. The 1/3 comes from the dimensionality of 3D space: $\tau = 1/d$. T5 (mass equation) is a consequence, not an axiom.

## 2. Wake Tensor (ℓ-expansion)

The convergence field $\Phi(\mathbf{r}, \hat{n})$ expanded in spherical harmonics:

| ℓ | Components | Physical role |
|---|-----------|---------------|
| 0 | 1 (scalar) | Isotropic background $N\varepsilon$ — no force |
| 1 | 3 (vector) | Pressure gradient → **Coulomb** $\propto 1/r^2$ |
| 2 | 5 (traceless symm.) | Organized flow → **Magnetic dipole** $\propto 1/r^3$ |
| ≥3 | $2\ell+1$ | Nuclear form factors |

Two topologies interact through wake overlap integrals. No $v_T$ → no ℓ=2 → no magnetic moment (neutrino prediction).

## 3. Modal Coupling from Curvature

$$\mathcal{C}_{TP} = \frac{a}{R}$$

Thin torus ($a/R \ll 1$): weak coupling, slow error absorption, high stability.
Fat torus ($a/R \sim 1$): strong coupling, fast absorption, resonance risk.

Jacobian eigenvalues are all negative → **stable attractor**. Perturbations decay at $\omega \sim c/R_{\text{quantum}} \sim 10^{21}$ Hz.

## 4. Topology Selection (Genus Elimination)

| Genus | Modes | Budget/mode | Viable? |
|-------|-------|-------------|---------|
| 0 | 0 | — | ✗ No circulation → collapse |
| **1** | **3** | **c²/3** | **✓ Stable** |
| 2 | 6 | c²/6 | ✗ Diluted |
| g | 3g | c²/3g | ✗ Worse |

Proton is genus 1 with winding $W=3$ (trefoil). Higher winding **amplifies**; higher genus **dilutes**.

## 5. Coulomb Identity (Derived)

From the SDT force law + charge quantisation + transfer function:

$$k_e e^2 = \alpha\hbar c$$

The Coulomb coupling product is not free — it collapses from the framework automatically.

## 6. W+1 Radius Conjecture

$$R_p = \frac{(W+1)\hbar}{m_p c} = \frac{4\hbar}{m_p c} = 0.84124 \text{ fm}$$

Agreement with measurement: 0.02%. Inverse form:

$$W_{\text{eff}} = \frac{R_p m_p c}{\hbar} - 1 = 3.000$$

**Falsification**: if future $R_p$ deviates from $4\hbar/(m_p c)$ beyond $n\sigma$, the W+1 conjecture is false (branch test, not full-SDT kill).
