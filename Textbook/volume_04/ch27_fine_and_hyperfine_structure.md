# Chapter 27 — Fine and Hyperfine Structure

*Volume IV — Atomic Recurrence, Spectra and Material Organisation.*
Draft of 10 November 2026. Notation: $\beta=Z\alpha/n$ is the circulation speed over $c$; $\mathrm{Ry}$ the stored Rydberg energy. Executable companion: `Textbook/examples/ch27_fine_and_hyperfine_structure.cpp`; pre-registration and captured output in `Textbook/validation/`. No coefficient of any correction is derived in this chapter, and no measured splitting is loaded.

## 27.1 The physical question

Fine structure concerns corrections to the leading recurrence ladder of Chapter 26: movement-budget corrections, route orientation, coupled circulation and finite-source geometry. The question is what can be said before a coefficient is derived from the contact and mode-response operator: which orders appear, how they are separated, and what the engine's fine-structure function does and does not supply.

## 27.2 Power counting

A perturbation expansion needs a small dimensionless parameter and a declared retained order. For a hydrogenic circulation $\beta=Z\alpha/n$. A correction of relative order $\beta^2$ to a binding scale of order $\beta^2m_ec^2$ gives an energy contribution of order $\beta^4m_ec^2$, that is, of relative size $\beta^2$ to the leading ladder. Relative sizes executed (T3): $\beta^2=5.325\times10^{-5}$ for $(Z,n)=(1,1)$, $1.331\times10^{-5}$ for $(1,2)$ and $4.793\times10^{-2}$ for $(30,1)$.

The counting identifies candidate importance, not a numerical coefficient. The coefficient has to follow from the contact and mode-response operator. Adding a known spectral correction as an unexplained term would reproduce a line without deriving the mechanism.

## 27.3 The engine's fine-structure function is a scale

The engine provides `atomic::fine_structure_eV(Z,n)` (Sommerfeld form, $\Delta E=E_n\alpha^2Z^2/n$). **Executed (T1).** It equals

$$\Delta E_{\rm scale}=\mathrm{Ry}\,\frac{\alpha^2Z^4}{n^3} \tag{27.1}$$

for $Z=1\ldots5$, $n=1\ldots6$ to $2.2\times10^{-16}$; for hydrogen $n=2$ it is $9.0565\times10^{-5}$ eV. It carries no dependence on the orbital state and is therefore a scale of the order of the splitting, not a derived splitting.

**Comparison with the standard form.** The splitting of a pair of levels of orbital number $l$ in the standard formula for a single circulating unit is $\mathrm{Ry}\,\alpha^2Z^4/\big(n^3\,l(l+1)\big)$; it is used here only as a comparison formula and not as an input (agreement of form is convergence). **Executed (T2).** The ratio of the engine scale (27.1) to it is $l(l+1)$ exactly for $l=1,2,3$ ($n>l$, $Z=1\ldots5$; worst relative deviation $3.3\times10^{-16}$): $2.000000$ for the $n=2$ P pair, where the comparison splitting is $4.5283\times10^{-5}$ eV, and $6$ for a D pair. The engine's function is the common scale from which an $l$-dependent splitting would follow by a factor that the engine does not supply. The native operator that gives the $l$-dependence (route orientation, coupled circulation) remains to be derived (residual R27.1). Until it is, the function must not be quoted as a fine-structure splitting.

## 27.4 Nuclear coupling and finite size

Hyperfine response couples the nuclear circulation orientation to the atomic route and wake. A useful effective scalar is a coupling $A$ times an orientation invariant, but $A$ requires the spatial overlap and transfer calculation; a measured nuclear moment can be a declared input (in a native unit; Chapter 24, R24.3), while a calculated moment requires the frozen nuclear geometry. Finite nuclear size affects modes with different near-core exposure differently, so a line difference can test route geometry more sharply than a gross transition energy.

**Orders (T3).** For hydrogen, $n=1$, nucleus $m_p$, relative to the leading ladder: the fine scale $\alpha^2=5.325\times10^{-5}$ ($7.245\times10^{-4}$ eV); the hyperfine order $\alpha^2m_e/m_p=2.900\times10^{-8}$ ($3.946\times10^{-7}$ eV), the order of the nuclear circulation response with no coefficient; and the geometric finite-size order $(R_p/a_0)^2=2.528\times10^{-10}$ ($3.440\times10^{-9}$ eV), again with no coefficient. The ratios between successive scales were registered as exceeding $10^3$. They do for leading/fine ($1.9\times10^4$) and fine/hyperfine ($1836$, the proton-to-electron mass ratio). They do **not** for hyperfine/finite-size, whose ratio is $115$: that clause was rejected as registered and is kept as a result. At the level of power counting, without coefficients, the hyperfine and finite-size contributions are not separated by a large factor, so no ordering between them is claimed. A test must compare line differences with the coefficients derived from one operator.

## 27.5 The record of line extraction

The APS11 record of the sources distinguishes accepted line centres from a withdrawn extraction. Both statements are preserved: a successful line centre does not rehabilitate an excluded extraction method.

## 27.6 Determining comparison

Fix the leading recurrence state, the nuclear input and the perturbation operator before computing a multiplet. Report all line residuals and the retained orders together. Correspondence to accepted fine and hyperfine formulas is recorded with the native path of arrival. No unsupported coefficient is supplied in place of the missing route-response derivation.

## 27.7 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $\alpha$, $\mathrm{Ry}$, $m_e$, $m_p$, $R_p$, $a_0$ | `measured::` | MEASURED-INPUT |
| (27.1) and the ratio $l(l+1)$ | Section 27.3 | COMPUTED (identity of the engine function; comparison formula not an input) |
| scales of Section 27.4 | executed | COMPUTED (orders only, no coefficient) |

**Residuals.**

* **R27.1 — the $l$-dependence.** The operator that converts the scale (27.1) into a state-dependent splitting is not supplied.
* **R27.2 — hyperfine coefficient.** The coupling $A$ needs the overlap and transfer calculation and a frozen nuclear geometry.
* **R27.3 — finite-size coefficient.** The near-core exposure of each mode is not computed.
* **R27.4 — ordering.** The ordering of hyperfine and finite-size contributions is not determined by power counting (ratio 115).
* **R27.5 — measured splittings.** No measured line or splitting is loaded; all line residuals are outstanding.

## 27.8 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch27_fine_and_hyperfine_structure
```

Criteria were registered in `Textbook/validation/ch27_PRE_REGISTRATION.md` before the instrument existed. Run 1 failed the V1 line (the registered known answer $4.5277\times10^{-5}$ eV was wrong in its fourth digit; the correct value is $4.5283\times10^{-5}$ eV) and rejected the registered $10^3$ separation for hyperfine/finite-size (a finding, kept). Run 2 (`ch27_run2_output.txt`) is the run of record and met every criterion as recorded.

## 27.9 Exercises and answers

**Exercise 1.** Evaluate (27.1) for $Z=1$, $n=2$.

*Answer.* $\mathrm{Ry}\,\alpha^2/8=13.6057\times5.3251\times10^{-5}/8=9.057\times10^{-5}$ eV.

**Exercise 2.** Why is the energy contribution of an order-$\beta^2$ correction of order $\beta^4m_ec^2$?

*Answer.* The leading ladder is of order $\beta^2m_ec^2$; a correction of relative order $\beta^2$ multiplies it by $\beta^2$.

**Exercise 3.** What is the ratio of (27.1) to the comparison splitting for $l=2$?

*Answer.* $l(l+1)=6$.

**Exercise 4.** Which ratio of Section 27.4 equals the proton-to-electron mass ratio?

*Answer.* fine/hyperfine: $\alpha^2/(\alpha^2m_e/m_p)=m_p/m_e=1836$.

**Exercise 5.** Why can no ordering of hyperfine and finite-size be claimed from the orders alone?

*Answer.* Their ratio is 115, and each carries an undetermined coefficient that can be larger or smaller than 1 by more than that.

**Exercise 6.** Why must (27.1) not be quoted as a fine-structure splitting?

*Answer.* It is independent of $l$; the l-dependent factor is missing and not derived.

## 27.10 Scope

Established: the power-counting parameter and its numerical values; that the engine's fine-structure function is the scale (27.1) and exceeds the comparison splitting by exactly $l(l+1)$; the orders of the hydrogen corrections without coefficients; the recorded rejection of a large separation between the hyperfine and finite-size orders.

Not established: the $l$-dependence (R27.1), the hyperfine and finite-size coefficients (R27.2, R27.3), their ordering (R27.4) and any measured splitting (R27.5).

*Where it leads.* Chapter 28 turns to emission and absorption: the event ledger, the response kernel and what determines a line's width.
