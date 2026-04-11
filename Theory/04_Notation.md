# SDT Notation Guide

## Primary Symbols

| Symbol | Name | Definition | Units |
|--------|------|------------|-------|
| $\ell_P$ | Spation scale | Substrate grain size | m |
| $t_P$ | Tick | One relay interval | s |
| $c$ | Relay speed | $\ell_P / t_P$ | m/s |
| $\varepsilon$ | Deformation content | Energy per spation | J |
| $N$ | Shell count | $R_{\text{CMB}} / \ell_P$ | — |
| $\Phi$ | Throughput burden | $N\varepsilon$ | J |
| $P_{\text{conv}}$ | Convergent pressure | $\Phi / \ell_P^3$ | Pa |
| $\tau$ | Traction fraction | $\varepsilon_d / \varepsilon = 1/3$ | — |
| $V_{\text{disp}}$ | Displacement volume | Exclusion region of matter | m³ |
| $P_{\text{eff}}$ | Effective pressure | Occlusion-scale force pressure | Pa |
| $f$ | Transfer function | $P_{\text{eff}} / P_{\text{conv}}$ | — |
| $k$ | k-number | $c / v_{\text{orbital}}$ | — |
| $z$ | Redshift parameter | $(v/c)^2$ | — |
| $\beth$ | c-boundary radius | $R / k^2 = GM/c^2$ | m |
| $W$ | Winding number | Topological crossings | — |

## Wake Multipoles

| $\ell$ | Name | Physical role | Dependence |
|--------|------|---------------|------------|
| 0 | Monopole | Isotropic background | — |
| 1 | Dipole | Coulomb (electric) | $1/r^2$ |
| 2 | Quadrupole | Magnetic dipole | $1/r^3$ |
| $\geq 3$ | Higher | Nuclear structure | $1/r^{\ell+1}$ |

## State28D Levels

| Level | Dimensions | Domain |
|-------|-----------|--------|
| 1 | 1 | Existence |
| 2 | 2 | Line (position + velocity) |
| 3 | 3 | Plane (boundary + rotation) |
| 4 | 4 | Sphere (volume + orientation) |
| 5 | 5 | Torus (topology) |
| 6 | 6 | Dynamism (time evolution) |
| 7 | 7 | Energy (force manifestation) |
| **Total** | **28** | |

## Bridge Law

$$v_{\text{orbital}} = \frac{c}{k}\sqrt{\frac{R}{r}} \qquad z \cdot k^2 = 1 \qquad \beth = \frac{R}{k^2}$$

Where $R$ is the body radius, $r$ is the orbital radius, and $k = c/v_{\text{surface}}$.
