# Dependency Provenance & Derived Quantities

> Scale status: `derivelist/README.md`. `ℓ_P` is the dimensional seed; `c`, `k_B`, `e` are unit
> bridges; `{ℏ, m_e, m_p}` are one mass/action seat; `α` is hydrogen’s koppa rung; `T_CMB` is a
> FIRAS clock. Tables below are the engine’s computational cascade from `laws.hpp` lookup values.

The SDT engine keeps numerical seats, bridges, measured boundary facts and
comparison data in `sdt::laws::measured`. That namespace is a lookup location,
not a scientific-status class. The cascade below records how each value enters.

## Dependency roles

| Quantity | Numerical source | Dependency role |
|----------|------------------|-----------------|
| $\ell_P$ | CODATA lookup | Axiom R1: irreducible dimensional seed |
| $c$ | SI exact | Relay-speed unit bridge |
| $\hbar$ | CODATA lookup | One mass/action seat; W=1 circulation role |
| $\alpha$ | hydrogen spectroscopy (APS05/PPT02) | Derived hydrogen koppa rung; topology-only origin remains open |
| $m_e$ | CODATA lookup | Numerical representative of the mass/action seat |
| $m_p$ | CODATA lookup | Same seat through the PPT17 shared-input packing construction |
| $T_{\text{CMB}}$ | FIRAS | Measured mechanical boundary state of present convergence |

## Derived Quantities (Stage by Stage)

### Stage 1: Cosmological (from $c, \hbar, T_{\text{CMB}}$)

| Quantity | Formula | Value |
|----------|---------|-------|
| $u_{\text{CMB}}$ | $aT^4$ | 4.172 × 10⁻¹⁴ J/m³ |
| $\ell_P$ | 1.616255 × 10⁻³⁵ m (measured) | Planck length |
| $N$ | $R_{\text{CMB}}/\ell_P$ | 5.894 × 10⁶¹ |

> **Note:** $\ell_P$ carries Axiom-R1 seed status. It is not obtained from a
> body-source constant or from a benchmark target.
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

## Remaining derivational debts

| Quantity | Status | Path to closure |
|----------|--------|----------------|
| topology-only origin of $\alpha$ | **OPEN** | Derive the spectroscopic rung from W=1 topology without reading it back from the spectrum |
| absolute mass/action-seat magnitude | **OPEN** | Close the Law-IV engaged-volume normalization without consuming a particle mass |
| $m_p/m_e$ packing map | **SHARED-INPUT CONSTRUCTION** | Volumetric map closed by PPT17; not an independent prediction |
| $R_p=(W+1)\hbar/(m_pc)$ | **PENDING** | Derive the W+1 boundary from trefoil lock/action dynamics |

The terminal description is an acyclic ledger: dimensional seed, mass/action
seat, unit bridges, derived relations, and measured mechanical boundary facts.
