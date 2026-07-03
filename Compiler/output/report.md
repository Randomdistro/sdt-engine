# Theory Compilation Report

**Theory:** SDT
**Version:** 0.0.1
**Status:** COMPILED [DEFECTIVE TOOL — see Compiler/output/AUDIT_REPORT.md: 'a confident liar in both directions'; badges non-probative]
**Kernel Hash:** `b0042ba2ed12cdc73f8d96e04b16902872e6587fd693222a58254a6e63903bd8`

## Summary

| Metric | Count |
|--------|-------|
| Total items parsed | 329 |
| Symbols registered | 108 |
| Equations validated | 180 |
| Derivation steps | 0 |
| Passes | 0 |
| Warnings | 0 |
| Failures | 1 |
| Fatal errors | 0 |

## ⚠️ Failures

- **SYMBOL_DRIFT** (`W`): Term 'W' used mechanically in one section and metaphorically in another. Distinguish uses or clarify intent.

## Symbol Table

| Symbol | Name | Definition | Status |
|--------|------|------------|--------|
| `l_P` | Spation scale | Substrate grain size | locked |
| `t_P` | Tick | One relay interval | locked |
| `c` | Relay speed | l_P / t_P | locked |
| `epsilon` | Deformation content | Energy per spation | locked |
| `N` | Shell count | R_CMB / l_P | locked |
| `Phi` | Throughput burden | Nepsilon | locked |
| `P_conv` | Convergent pressure | Phi / l_P^3 | locked |
| `tau` | Traction fraction | epsilon_d / epsilon = 1/3 | locked |
| `V_disp` | Displacement volume | Exclusion region of matter | locked |
| `P_eff` | Effective pressure | Occlusion-scale force pressure | locked |
| `f` | Transfer function | P_eff / P_conv | locked |
| `k` | k-number | c / v_orbital | locked |
| `z` | Redshift parameter | (v/c)^2 | locked |
| `beth` | c-boundary radius | R / k^2 = GM/c^2 | locked |
| `W` | Winding number | Topological crossings | locked |
| `**Total**` | **28** |  | locked |
| `varepsilon` |  |  | locked |
| `varepsilond` |  |  | locked |
| `Pi` |  |  | locked |
| `ij` |  |  | locked |
| `P` |  |  | locked |
| `conv` |  |  | locked |
| `delta` |  |  | locked |
| `d` |  |  | locked |
| `ell` |  |  | locked |
| `→` |  |  | locked |
| `vT` |  |  | locked |
| `vP` |  |  | locked |
| `vC` |  |  | locked |
| `vt` |  |  | locked |
| `Nepsilon` |  |  | locked |
| `arrow` |  |  | locked |
| `epsilon_d` |  |  | locked |
| `epsilon_t` |  |  | locked |
| `epsilon_a` |  |  | locked |
| `Pi_ij` |  |  | locked |
| `delta_ij` |  |  | locked |
| `Delta` |  |  | locked |
| `theta` |  |  | locked |
| `nablaW` |  |  | locked |
| `v_T` |  |  | locked |
| `v_P` |  |  | locked |
| `v_C` |  |  | locked |
| `v_t` |  |  | locked |
| `R_CMB` |  |  | locked |
| `i` |  |  | locked |
| `v_circ` |  |  | locked |
| `v` |  |  | locked |
| `F` |  |  | locked |
| `pi` |  |  | locked |
| `R_1` |  |  | locked |
| `R_2` |  |  | locked |
| `r` |  |  | locked |
| `m` |  |  | locked |
| `m_inert` |  |  | locked |
| `m_grav` |  |  | locked |
| `R_charge` |  |  | locked |
| `R_p` |  |  | locked |
| `r_e` |  |  | locked |
| `k_e` |  |  | locked |
| `e` |  |  | locked |
| `alphahbar` |  |  | locked |
| `dtau` |  |  | locked |
| `dt` |  |  | locked |
| `L` |  |  | locked |
| `L_0` |  |  | locked |
| `gamma` |  |  | locked |
| `E_0` |  |  | locked |
| `mc` |  |  | locked |
| `E` |  |  | locked |
| `pc` |  |  | locked |
| `R` |  |  | locked |
| `G` |  |  | locked |
| `M` |  |  | locked |
| `hbar` |  |  | locked |
| `k_B` |  |  | locked |
| `T_CMB` |  |  | locked |
| `alpha` |  |  | locked |
| `m_e` |  |  | locked |
| `m_p` |  |  | locked |
| `sigman` |  |  | locked |
| `n` |  |  | locked |
| `sigma_n` |  |  | locked |
| `n_i` |  |  | locked |
| `n_j` |  |  | locked |
| `C_TP` |  |  | locked |
| `a` |  |  | locked |
| `ll` |  |  | locked |
| `omega` |  |  | locked |
| `R_quantum` |  |  | locked |
| `fm` |  |  | locked |
| `W_eff` |  |  | locked |
| `nsigma` |  |  | locked |
| `u_CMB` |  |  | locked |
| `pialphahbar` |  |  | locked |
| `p` |  |  | locked |
| `P_cf` |  |  | locked |
| `rho_eff` |  |  | locked |
| `electron` |  |  | locked |
| `proton` |  |  | locked |
| `stable` |  |  | locked |
| `winding` |  |  | locked |
| `numbers` |  |  | locked |
| `radius` |  |  | locked |
| `surface` |  |  | locked |
| `v_orbital` |  |  | locked |
| `GM` |  |  | locked |
| `v_surface` |  |  | locked |

## Equation Validation

| Equation | LHS Dim | RHS Dim | Status |
|----------|---------|---------|--------|
| `$$\Phi = N\varepsilon$$` |  |  | ⏳ |
| `$$\tau = \frac{\varepsilond}{\varepsilon} = \frac{1}{3}$$` |  |  | ⏳ |
| `Derived locally from $\Pi{ij} = (P{\text{conv}}/3)\delta{ij}$. The normal projection of an isotropic stress tensor in 3D equals $1/d$. This is geometry, not tuning.` |  |  | ⏳ |
| `Multipole expansion: $\ell=1$ → electric, $\ell=2$ → magnetic, $\ell \geq 3$ → structure.` |  |  | ⏳ |
| `$$vT^2 + vP^2 + vC^2 + vt^2 = c^2$$` |  |  | ⏳ |
| `Phi = Nepsilon` | M L^2 T^-2 | M L^2 T^-2 | ✅ |
| `epsilon arrow (epsilon_d, epsilon_t, epsilon_a)` |  |  | ⏳ |
| `tau = (epsilon_d)/(epsilon) = (1)/(3)` | 1 | 1 | ✅ |
| `\Pi_ij = (P_conv/3)delta_ij` |  |  | ⏳ |
| `1/d` |  |  | ⏳ |
| `W = anisotropic residue of non-traction throughput` | 1 | 1 | ✅ |
| `l=1` | 1 | 1 | ✅ |
| `l=2` | 1 | 1 | ✅ |
| `l >= 3` |  |  | ⏳ |
| `Delta\theta propto nablaW` |  |  | ⏳ |
| `nablaW=0` | 1 | 1 | ✅ |
| `v_T^2 + v_P^2 + v_C^2 + v_t^2 = c^2` | L^2 T^-2 | L^2 T^-2 | ✅ |
| `c^2` |  |  | ⏳ |
| `c = l_P / t_P` | L T^-1 | L T^-1 | ✅ |
| `epsilon` |  |  | ⏳ |
| `N = R_CMB/l_P` | 1 | 1 | ✅ |
| `i` |  |  | ⏳ |
| `Phi = Nepsilon` | M L^2 T^-2 | M L^2 T^-2 | ✅ |
| `v_circ <= c` |  |  | ⏳ |
| `v_circ^2 + v^2 = c^2` | L^2 T^-2 | L^2 T^-2 | ✅ |
| `c` |  |  | ⏳ |
| `N` |  |  | ⏳ |
| `Phi = Nepsilon` | M L^2 T^-2 | M L^2 T^-2 | ✅ |
| `P_conv = Phi/l_P^3` | M L^-1 T^-2 | M L^-1 T^-2 | ✅ |
| `F = (pi/4) P_eff R_1^2 R_2^2 / r^2` | M L T^-2 | 1 | ❌ |
| `m = Phi V_disp / (3l_P^3 c^2)` | M | M L^2 T^-2 | ❌ |
| `m_inert = m_grav` | M | M | ✅ |
| `V_disp` |  |  | ⏳ |
| `tau = 1/3` | 1 | 1 | ✅ |
| `R_charge = sqrt(R_p r_e)` | L | unresolved | ⏳ |
| `k_e e^2 = alphahbar c` |  |  | ⏳ |
| `v_circ^2 + v^2 = c^2` | L^2 T^-2 | L^2 T^-2 | ✅ |
| `dtau/dt = sqrt(1 - v^2/c^2)` | 1 | 1 | ✅ |
| `L = L_0/gamma` | L | L | ✅ |
| `E_0 = mc^2` | M L^2 T^-2 | unresolved | ⏳ |
| `E^2 = (pc)^2 + (mc^2)^2` | M^2 L^4 T^-4 | unresolved | ⏳ |
| `v_circ = 0 => v = c, m = 0` | L T^-1 | 1 | ❌ |
| `dtau/dt = sqrt(1 - z R/r)` | 1 | 1 | ✅ |
| `beth = R/k^2` | L | L | ✅ |
| `c` |  |  | ⏳ |
| `G` |  |  | ⏳ |
| `M` |  |  | ⏳ |
| `\l_P, c, hbar, k_B, T_CMB, alpha, m_e, m_p\` |  |  | ⏳ |
| `$$\Pi{ij} = \frac{P{\text{conv}}}{3}\delta{ij}$$` |  |  | ⏳ |
| `$$\sigman = \hat{n}i \Pi{ij} \hat{n}j = \frac{P{\text{conv}}}{3}$$` |  |  | ⏳ |
| `$$\tau = \frac{\sigman}{\text{tr}(\Pi)} = \frac{1}{3}$$` |  |  | ⏳ |
| `\Pi_ij = (P_conv)/3delta_ij` |  |  | ⏳ |
| `n` |  |  | ⏳ |
| `sigma_n = n_i \Pi_ij n_j = (P_conv)/3` | M L^-1 T^-2 | M L^-1 T^-2 | ✅ |
| `2P_conv/3` |  |  | ⏳ |
| `tau = (sigma_n)/(tr)(\Pi) = (1)/(3)` | 1 | 1 | ✅ |
| `tau = 1/d` | 1 | 1 | ✅ |
| `Phi(r, n)` |  |  | ⏳ |
| `Nepsilon` |  |  | ⏳ |
| `propto 1/r^2` |  |  | ⏳ |
| `propto 1/r^3` |  |  | ⏳ |
| `2l+1` |  |  | ⏳ |
| `v_T` |  |  | ⏳ |
| `C_TP = (a)/(R)` | 1 | 1 | ✅ |
| `a/R \ll 1` |  |  | ⏳ |
| `a/R \sim 1` |  |  | ⏳ |
| `omega \sim c/R_quantum \sim 10^21` |  |  | ⏳ |
| `W=3` | 1 | 1 | ✅ |
| `k_e e^2 = alphahbar c` |  |  | ⏳ |
| `R_p = ((W+1)hbar)/(m_p c) = (4hbar)/(m_p c) = 0.84124  fm` | L | 1 | ❌ |
| `W_eff = (R_p m_p c)/(hbar) - 1 = 3.000` | 1 | L | ❌ |
| `R_p` |  |  | ⏳ |
| `4hbar/(m_p c)` |  |  | ⏳ |
| `nsigma` |  |  | ⏳ |
| `c` |  |  | ⏳ |
| `hbar` |  |  | ⏳ |
| `alpha` |  |  | ⏳ |
| `m_e` |  |  | ⏳ |
| `m_p` |  |  | ⏳ |
| `T_CMB` |  |  | ⏳ |
| `c, hbar, T_CMB` |  |  | ⏳ |
| `u_CMB` |  |  | ⏳ |
| `aT^4` |  |  | ⏳ |
| `l_P` |  |  | ⏳ |
| `sqrt(hbar G/c^3)` |  |  | ⏳ |
| `N` |  |  | ⏳ |
| `R_CMB/l_P` |  |  | ⏳ |
| `epsilon` |  |  | ⏳ |
| `u_CMB l_P^3` |  |  | ⏳ |
| `Phi` |  |  | ⏳ |
| `Nepsilon` |  |  | ⏳ |
| `P_conv` |  |  | ⏳ |
| `Phi/l_P^3` |  |  | ⏳ |
| `alpha, m_e, m_p` |  |  | ⏳ |
| `r_e` |  |  | ⏳ |
| `alphahbar/(m_e c)` |  |  | ⏳ |
| `R_p` |  |  | ⏳ |
| `4hbar/(m_p c)` |  |  | ⏳ |
| `R_charge` |  |  | ⏳ |
| `sqrt(R_p r_e)` |  |  | ⏳ |
| `k_e e^2` |  |  | ⏳ |
| `alphahbar c` |  |  | ⏳ |
| `P_eff` |  |  | ⏳ |
| `m_p^2 m_e^2 c^5 / (4pialphahbar^3)` |  |  | ⏳ |
| `f` |  |  | ⏳ |
| `P_eff/P_conv` |  |  | ⏳ |
| `V_disp,e` |  |  | ⏳ |
| `3 m_e l_P^3 c^2 / Phi` |  |  | ⏳ |
| `V_disp,p` |  |  | ⏳ |
| `3 m_p l_P^3 c^2 / Phi` |  |  | ⏳ |
| `P_cf` |  |  | ⏳ |
| `rho_eff c^2 = P_conv/3` |  |  | ⏳ |
| `alpha` |  |  | ⏳ |
| `v_P/v_T` |  |  | ⏳ |
| `m_p/m_e` |  |  | ⏳ |
| `R_p` |  |  | ⏳ |
| `4hbar/(m_p c)` |  |  | ⏳ |
| `alpha` |  |  | ⏳ |
| `m_p/m_e` |  |  | ⏳ |
| `l_P` |  |  | ⏳ |
| `T_CMB` |  |  | ⏳ |
| `d=3` | 1 | 1 | ✅ |
| `Problem: Why are $W=1$ (electron) and $W=3$ (proton) the only stable winding numbers?` |  |  | ⏳ |
| `C_TP = a/R` | 1 | 1 | ✅ |
| `v_T, v_P, v_C` |  |  | ⏳ |
| `R/a` |  |  | ⏳ |
| `alpha` |  |  | ⏳ |
| `(R/a, alpha)` |  |  | ⏳ |
| `W=1` | 1 | 1 | ✅ |
| `W=3` | 1 | 1 | ✅ |
| `W=3` | 1 | 1 | ✅ |
| `W=2` | 1 | 1 | ✅ |
| `W=2` | 1 | 1 | ✅ |
| `W=1` | 1 | 1 | ✅ |
| `W=3` | 1 | 1 | ✅ |
| `alpha = 1/137.036` | 1 | 1 | ✅ |
| `alpha = v_P/v_T` | 1 | 1 | ✅ |
| `alpha` |  |  | ⏳ |
| `alpha` |  |  | ⏳ |
| `l_P` |  |  | ⏳ |
| `T_CMB` |  |  | ⏳ |
| `d=3` | 1 | 1 | ✅ |
| `R_p = 4hbar/(m_p c) = 0.84124` | L | 1 | ❌ |
| `R_p` |  |  | ⏳ |
| `W_eff = 3.000` | 1 | 1 | ✅ |
| `$$v{\text{orbital}} = \frac{c}{k}\sqrt{\frac{R}{r}} \qquad z \cdot k^2 = 1 \qquad \beth = \frac{R}{k^2}$$` |  |  | ⏳ |
| `Where $R$ is the body radius, $r$ is the orbital radius, and $k = c/v{\text{surface}}$.` |  |  | ⏳ |
| `l_P` |  |  | ⏳ |
| `t_P` |  |  | ⏳ |
| `c` |  |  | ⏳ |
| `l_P / t_P` |  |  | ⏳ |
| `epsilon` |  |  | ⏳ |
| `N` |  |  | ⏳ |
| `R_CMB / l_P` |  |  | ⏳ |
| `Phi` |  |  | ⏳ |
| `Nepsilon` |  |  | ⏳ |
| `P_conv` |  |  | ⏳ |
| `Phi / l_P^3` |  |  | ⏳ |
| `tau` |  |  | ⏳ |
| `epsilon_d / epsilon = 1/3` | 1 | 1 | ✅ |
| `V_disp` |  |  | ⏳ |
| `P_eff` |  |  | ⏳ |
| `f` |  |  | ⏳ |
| `P_eff / P_conv` |  |  | ⏳ |
| `k` |  |  | ⏳ |
| `c / v_orbital` |  |  | ⏳ |
| `z` |  |  | ⏳ |
| `(v/c)^2` |  |  | ⏳ |
| `beth` |  |  | ⏳ |
| `R / k^2 = GM/c^2` | L | L | ✅ |
| `W` |  |  | ⏳ |
| `l` |  |  | ⏳ |
| `1/r^2` |  |  | ⏳ |
| `1/r^3` |  |  | ⏳ |
| `>= 3` |  |  | ⏳ |
| `1/r^l+1` |  |  | ⏳ |
| `v_orbital = (c)/(k)sqrt((R)/(r))   z  k^2 = 1   beth = (R)/(k^2)` | L T^-1 | L T^-1 | ✅ |
| `R` |  |  | ⏳ |
| `r` |  |  | ⏳ |
| `k = c/v_surface` | 1 | 1 | ✅ |

## State28D Manifold

The 28-dimensional state manifold Ξ ∈ ℝ²⁸ organises every physical locus.

| # | Level | Field | Description | Dimension | Registered |
|---|-------|-------|-------------|-----------|------------|
| 0 | L1 | `xi_0` | Existence — baseline presence in spation medium | 1 | — |
| 1 | L2 | `xi_10` | Location — position along axis | L | — |
| 2 | L2 | `xi_11` | Relocation — linear velocity | L T^-1 | — |
| 3 | L3 | `xi_p0` | Internal existence — planar boundary (within/without) | 1 | — |
| 4 | L3 | `xi_p1` | Planar relocation — position within plane | L^2 | — |
| 5 | L3 | `xi_p2` | Planar rotation — orientation in plane | 1 | — |
| 6 | L4 | `xi_s0` | Shell existence — volumetric presence | L^3 | — |
| 7 | L4 | `xi_s1` | Shell relocation — motion within volume | L^3 T^-1 | — |
| 8 | L4 | `xi_s2` | Shell rotation — rotational state | T^-1 | — |
| 9 | L4 | `xi_s3` | Orientation — axis direction | 1 | — |
| 10 | L5 | `T_1` | Central ring — constriction line, max compression | L | — |
| 11 | L5 | `T_2` | Tube diameter — vortex thickness | L | — |
| 12 | L5 | `T_3` | Topological surface — 2D boundary | L^2 | — |
| 13 | L5 | `T_4` | Polarised volume — central aperture + pressure gradient | M L^-1 T^-2 L^3 | — |
| 14 | L5 | `T_5` | Aspect gradation — internal pressure/density gradient | M L^-2 T^-2 | — |
| 15 | L6 | `Phi_0` | Omnidirectionality — all surface vectors | 1 | — |
| 16 | L6 | `Phi_1` | Dynamic translocation — higher-order rates | L T^-2 | — |
| 17 | L6 | `Phi_2` | Oscillation — periodic reversal/precession | T^-1 | — |
| 18 | L6 | `Phi_3` | Inversion/chirality — handedness | 1 | — |
| 19 | L6 | `Phi_4` | State trajectory variance — potential from external influence | 1 | — |
| 20 | L6 | `Phi_5` | Phase transition — potential for structural change | M L^2 T^-2 | — |
| 21 | L7 | `eps_0` | Potential — energy of position/configuration | M L^2 T^-2 | — |
| 22 | L7 | `eps_1` | Kinetic — energy of bulk motion | M L^2 T^-2 | — |
| 23 | L7 | `eps_2` | Rotational — energy of unencumbered motion | M L^2 T^-2 | — |
| 24 | L7 | `eps_3` | Field — energy in pressure-occlusion field | M L^2 T^-2 | — |
| 25 | L7 | `eps_b` | Binding energy — energy to decohere structure | M L^2 T^-2 | — |
| 26 | L7 | `eps_4` | Flux — rate of energy transfer | M L^2 T^-3 | — |
| 27 | L7 | `eps_5` | Transmission — mechanical transfer | M L^2 T^-2 | — |

