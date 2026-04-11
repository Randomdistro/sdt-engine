# SDT Constitutional Ruleset

## The Six Irreducible Operators

### (1) Continuous throughput
$$\Phi = N\varepsilon$$

### (2) Boundary event
$$\varepsilon \rightarrow (\varepsilon_d, \varepsilon_t, \varepsilon_a)$$

### (3) Traction condition
$$\tau = \frac{\varepsilon_d}{\varepsilon} = \frac{1}{3}$$

Derived locally from $\Pi_{ij} = (P_{\text{conv}}/3)\delta_{ij}$. The normal projection of an isotropic stress tensor in 3D equals $1/d$. This is geometry, not tuning.

### (4) Wake formation
$$\mathcal{W} = \text{anisotropic residue of non-traction throughput}$$

Multipole expansion: $\ell=1$ → electric, $\ell=2$ → magnetic, $\ell \geq 3$ → structure.

### (5) Propagation law
$$\Delta\theta \propto \nabla\mathcal{W}$$

One mechanism: straight line ($\nabla\mathcal{W}=0$), refraction (smooth gradient), scattering (stochastic), lensing (large-scale).

### (6) Persistence constraint
$$v_T^2 + v_P^2 + v_C^2 + v_t^2 = c^2$$

The movement budget. At rest, three orthogonal modes share $c^2$.

---

## Axioms (9)

| # | Axiom | Statement |
|---|-------|-----------|
| R1 | Spation lattice | Space is a gap-free, contact-only relay medium |
| R2 | Nearest-neighbour | Transmission is nearest-neighbour only at rate $c = \ell_P / t_P$ |
| R3 | Phase loading | Every spation carries deformation content $\varepsilon$ |
| R4 | Shell structure | The lattice has $N = R_{\text{CMB}}/\ell_P$ radial shells |
| R5 | Omnidirectional release | At the Clearing, all content was released isotropically |
| R6 | Shell cancellation | Convergent arrival from shell $i$ preserves $\Phi = N\varepsilon$ |
| M1 | Exclusion | Matter is a persistent displacement of spations |
| M2 | Circulation | Displaced spations circulate at speed $v_{\text{circ}} \leq c$ |
| M3 | Budget | $v_{\text{circ}}^2 + v^2 = c^2$ — total velocity is always $c$ |

## Theorems (17)

| # | Theorem | Result |
|---|---------|--------|
| T1 | Shell cancellation identity | Inner shells cancel → only $N$ contributes |
| T2 | Convergent throughput | $\Phi = N\varepsilon$, $P_{\text{conv}} = \Phi/\ell_P^3$ |
| T3 | Occlusion force | $F = (\pi/4) P_{\text{eff}} R_1^2 R_2^2 / r^2$ |
| T4 | Force unification | Same mechanism: Coulomb, gravity, nuclear |
| T5 | Inertial mass | $m = \Phi V_{\text{disp}} / (3\ell_P^3 c^2)$ |
| T6 | Equivalence principle | $m_{\text{inert}} = m_{\text{grav}}$ (same $V_{\text{disp}}$) |
| T7 | Traction | $\tau = 1/3$ from isotropic tensor projection |
| T8 | Charge quantisation | $R_{\text{charge}} = \sqrt{R_p r_e}$ |
| T9 | Coulomb identity | $k_e e^2 = \alpha\hbar c$ |
| T10 | Movement budget | $v_{\text{circ}}^2 + v^2 = c^2$ |
| T11 | Time dilation | $d\tau/dt = \sqrt{1 - v^2/c^2}$ |
| T12 | Length contraction | $L = L_0/\gamma$ |
| T13 | Rest energy | $E_0 = mc^2$ |
| T14 | Energy-momentum | $E^2 = (pc)^2 + (mc^2)^2$ |
| T15 | Photon limit | $v_{\text{circ}} = 0 \Rightarrow v = c, m = 0$ |
| T16 | Gravitational dilation | $d\tau/dt = \sqrt{1 - z R/r}$ |
| T17 | c-boundary | $\beth = R/k^2$: where orbital speed = $c$ |

## Prohibitions

The following are **not permitted** in any SDT derivation:
- Quarks, gluons, virtual particles
- $G$ or $M$ as fundamental constants
- Dark matter, dark energy
- Probabilistic wavefunction collapse
- Fields as ontological primitives
- Any constant not derivable from $\{\ell_P, c, \hbar, k_B, T_{\text{CMB}}, \alpha, m_e, m_p\}$

## Certification Labels

| Label | Meaning |
|-------|---------|
| DERIVED | Computed from axioms, no external input beyond CODATA |
| COMPUTED | Deterministic calculation from the Law framework |
| CALIBRATED | One parameter fitted (must be documented) |
| OBSERVED | Validated against measurement, mechanism established |
| PENDING | Mechanism identified, computation not yet complete |
