# Measured Inputs & Derived Quantities

The SDT engine requires **6 independent measured inputs** (or 7 if W+1 is unproven). Everything else derives.

## Independent Inputs

| Constant | Value | Source | Role |
|----------|-------|--------|------|
| $c$ | 299,792,458 m/s | SI exact | Relay speed |
| $\hbar$ | 1.054571817 × 10⁻³⁴ J·s | SI exact | Planck quantum |
| $\alpha$ | 7.2973525693 × 10⁻³ | CODATA 2018 | Wake coupling (W=1 torus) |
| $m_e$ | 9.1093837015 × 10⁻³¹ kg | CODATA 2018 | Electron exclusion cost |
| $m_p$ | 1.67262192369 × 10⁻²⁷ kg | CODATA 2018 | Proton exclusion cost |
| $T_{\text{CMB}}$ | 2.7255 K | FIRAS/Planck | Current convergence temperature |

## Derived Quantities (Stage by Stage)

### Stage 1: Cosmological (from $c, \hbar, T_{\text{CMB}}$)

| Quantity | Formula | Value |
|----------|---------|-------|
| $u_{\text{CMB}}$ | $aT^4$ | 4.172 × 10⁻¹⁴ J/m³ |
| $\ell_P$ | $\sqrt{\hbar G/c^3}$ | 1.616 × 10⁻³⁵ m |
| $N$ | $R_{\text{CMB}}/\ell_P$ | 5.894 × 10⁶¹ |
| $\varepsilon$ | $u_{\text{CMB}} \ell_P^3$ | 1.761 × 10⁻¹¹⁸ J |
| $\Phi$ | $N\varepsilon$ | 1.038 × 10⁻⁵⁶ J |
| $P_{\text{conv}}$ | $\Phi/\ell_P^3$ | 2.459 × 10⁴⁸ Pa |

### Stage 2: Particle Radii (from $\alpha, m_e, m_p$)

| Quantity | Formula | Value |
|----------|---------|-------|
| $r_e$ | $\alpha\hbar/(m_e c)$ | 2.818 × 10⁻¹⁵ m |
| $R_p$ | $4\hbar/(m_p c)$ | 8.412 × 10⁻¹⁶ m |
| $R_{\text{charge}}$ | $\sqrt{R_p r_e}$ | 1.540 × 10⁻¹⁵ m |

### Stage 3: Force Law (from above)

| Quantity | Formula | Value |
|----------|---------|-------|
| $k_e e^2$ | $\alpha\hbar c$ | 2.307 × 10⁻²⁸ J·m |
| $P_{\text{eff}}$ | $m_p^2 m_e^2 c^5 / (4\pi\alpha\hbar^3)$ | 5.225 × 10³¹ Pa |
| $f$ | $P_{\text{eff}}/P_{\text{conv}}$ | 2.125 × 10⁻¹⁷ |

### Stage 4: Mass & Stability (from above)

| Quantity | Formula | Value |
|----------|---------|-------|
| $V_{\text{disp},e}$ | $3 m_e \ell_P^3 c^2 / \Phi$ | 9.988 × 10⁻⁶² m³ |
| $V_{\text{disp},p}$ | $3 m_p \ell_P^3 c^2 / \Phi$ | 1.834 × 10⁻⁵⁸ m³ |
| $P_{\text{cf}}$ | $\rho_{\text{eff}} c^2 = P_{\text{conv}}/3$ | ✓ identity |

## Remaining Open Inputs

| Quantity | Status | Path to closure |
|----------|--------|----------------|
| $\alpha$ | Measured | Derive from W=1 torus mode partition ($v_P/v_T$?) |
| $m_p/m_e$ | Measured | Derive from W=3 vs W=1 equilibrium |
| $R_p$ | **Conjectured** | $4\hbar/(m_p c)$ to 0.02% |

If $\alpha$ and $m_p/m_e$ close, the terminal input set is: $\ell_P$, $T_{\text{CMB}}$, and $d=3$.
