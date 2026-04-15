# SDT Laws Reference — Canonical Constants for Atomicus

*Source: `sdt-engine/Engine/include/sdt/laws.hpp` v5.0*
*Date: March 2026*

This reference provides the **exact** constants that Atomicus entries should use. All values trace to the 6 independent measured inputs through the derivation chain documented in `sdt-engine/Theory/02_Inputs_and_Derivations.md`.

---

## Independent Measured Inputs

| Constant | Symbol | Value | Source |
|----------|--------|-------|--------|
| Speed of light | $c$ | 299,792,458 m/s | SI exact |
| Reduced Planck | $\hbar$ | 1.054571817 × 10⁻³⁴ J·s | SI exact |
| Fine structure | $\alpha$ | 7.2973525693 × 10⁻³ | CODATA 2018 |
| Electron mass | $m_e$ | 9.1093837015 × 10⁻³¹ kg | CODATA 2018 |
| Proton mass | $m_p$ | 1.67262192369 × 10⁻²⁷ kg | CODATA 2018 |
| CMB temperature | $T_\text{CMB}$ | 2.7255 K | FIRAS/Planck |

## Derived Atomic Constants

| Constant | Symbol | Formula | Value |
|----------|--------|---------|-------|
| Rydberg energy | $R_y$ | $\alpha^2 m_e c^2 / 2$ | 13.6057 eV |
| Bohr radius | $a_0$ | $\hbar / (\alpha m_e c)$ | 5.29177 × 10⁻¹¹ m |
| Compton wavelength (e) | $\lambdabar_e$ | $\hbar / (m_e c)$ | 3.86159 × 10⁻¹³ m |
| Classical electron radius | $r_e$ | $\alpha \hbar / (m_e c)$ | 2.81794 × 10⁻¹⁵ m |
| Proton charge radius | $R_p$ | $4\hbar / (m_p c)$ | 8.41236 × 10⁻¹⁶ m |
| He-4 charge radius | $R_\text{He}$ | $2 R_p$ | 1.6828 × 10⁻¹⁵ m |
| Charge radius | $R_\text{charge}$ | $\sqrt{R_p \cdot r_e}$ | 1.540 × 10⁻¹⁵ m |
| $\alpha$ inverse | $1/\alpha$ | — | 137.036 |
| Mass ratio | $m_p/m_e$ | — | 1836.15 |

## Derived Force Constants

| Constant | Symbol | Formula | Value |
|----------|--------|---------|-------|
| Coulomb coupling | $k_e e^2$ | $\alpha \hbar c$ | 2.30708 × 10⁻²⁸ J·m |
| Effective pressure | $P_\text{eff}$ | $m_p^2 m_e^2 c^5/(4\pi\alpha\hbar^3)$ | 5.225 × 10³¹ Pa |
| Convergent pressure | $P_\text{conv}$ | $\Phi/\ell_P^3$ | 2.459 × 10⁴⁸ Pa |
| Transfer function | $f$ | $P_\text{eff}/P_\text{conv}$ | 2.125 × 10⁻¹⁷ |
| CMB radiation pressure | $P_\text{CMB}$ | $aT_\text{CMB}^4/3$ | **1.391 × 10⁻¹⁴ Pa** |

> [!CAUTION]
> Older Atomicus entries use **P_CMB = 2.036 × 10⁻² Pa**, which is **wrong by 12 orders of magnitude**. That was the energy density in different units. The correct CMB radiation pressure is **1.391 × 10⁻¹⁴ Pa**.

## Cosmological Constants

| Constant | Symbol | Formula | Value |
|----------|--------|---------|-------|
| CMB energy density | $u_\text{CMB}$ | $aT_\text{CMB}^4$ | 4.172 × 10⁻¹⁴ J/m³ |
| CMB redshift | $z_\text{CMB}$ | $T_\text{rec}/T_\text{CMB} - 1$ | 1099.7 |
| Recombination temp | $T_\text{rec}$ | — | 3000 K |

## Bridge Law (k-number system)

$$v_\text{orbital} = \frac{c}{k}\sqrt{\frac{R}{r}}, \qquad z \cdot k^2 = 1, \qquad \beth = \frac{R}{k^2}$$

| System | $v$ | $k$ | $z$ | $\beth$ |
|--------|-----|-----|-----|---------|
| H atom | $\alpha c$ | $1/\alpha$ | $\alpha^2$ | $\alpha^2 a_0$ |
| Sun surface | 616 m/s | 486,800 | $4.22 \times 10^{-12}$ | 1477 m |
| Earth orbit | 29,783 m/s | 10,063 | $9.87 \times 10^{-9}$ | 4.43 mm |

## Rydberg Formula for Ionization

For any hydrogen-like ion (single electron, nuclear charge $Z$):

$$E_n = -R_y \cdot \frac{Z^2}{n^2}$$

$$\lambda_{n_1 \to n_2} = \frac{hc}{R_y Z^2} \cdot \frac{n_1^2 n_2^2}{n_2^2 - n_1^2}$$

## Kinematic Ratio

The Atomicus $\chi$ value for each ionization level:

$$\chi = \frac{c}{v} = \frac{c}{\sqrt{2 E_\text{ion}/m_e}}$$

For hydrogen: $\chi_1 = 1/\alpha = 137.036$ (the baseline).

## W+1 Conjecture

$$R_p = \frac{(W+1)\hbar}{m_p c} = \frac{4\hbar}{m_p c}$$

- $W = 3$ (trefoil, proton)
- $W = 1$ (simple torus, electron)
- Measured $R_p = 0.8414$ fm → $W_\text{eff} = 3.000$ ± 0.001
