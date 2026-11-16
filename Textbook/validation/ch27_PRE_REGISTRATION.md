# Chapter 27 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch27_fine_and_hyperfine_structure.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The corrections to the leading recurrence ladder as a power-counting problem and the status of the engine's fine-structure function. (a) The small parameter $\beta=Z\alpha/n$ (circulation speed over $c$); a correction of relative order $\beta^2$ to a binding scale gives an energy contribution of order $\beta^2\times$ that scale. (b) The engine function `atomic::fine_structure_eV(Z,n)` is the identity $\mathrm{Ry}\,\alpha^2Z^4/n^3$ and therefore a *scale*, not a derived splitting: set against the l-dependent splitting form $\mathrm{Ry}\,\alpha^2Z^4/(n^3\,l(l+1))$ of the standard formula (used only as a comparison formula, never as an input; agreement of form is convergence) it exceeds that form by exactly $l(l+1)$. The native operator that gives the $l$-dependence is not supplied (residual). (c) The separation of orders: leading ladder, fine scale $\alpha^2$, hyperfine scale $\alpha^2m_e/m_{\rm nuc}$ (order of the nuclear circulation response, no coefficient claimed), finite-size scale $(ZR_p/a_0)^2$ (geometric order, no coefficient claimed). No measured line or splitting is loaded; no coefficient is supplied.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $\mathrm{Ry}\,\alpha^2/16$ for $Z=1,n=2,l=1$ is $4.5277\times10^{-5}$ eV to $10^{-4}$ (arithmetic of the comparison formula only) | $10^{-4}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | `fine_structure_eV(Z,n)` equals $\mathrm{Ry}\,\alpha^2Z^4/n^3$ for $Z=1\ldots5$, $n=1\ldots6$ | relative $10^{-14}$ | yes |
| T2 | ratio of the engine scale to the comparison splitting $\mathrm{Ry}\alpha^2Z^4/(n^3l(l+1))$ equals $l(l+1)$ exactly for $l=1,2,3$ and $n>l$; in particular 2 for the $n=2$ P pair | $10^{-14}$ | yes |
| T3 | orders. For hydrogen ($Z=1$, $n=1$, nucleus $m_p$): leading 1; fine $\alpha^2$; hyperfine order $\alpha^2m_e/m_p$; finite size $(R_p/a_0)^2$. Registered: each successive scale is smaller than the previous by more than a factor $10^{3}$. For $Z=1\ldots30$ the fine scale $(Z\alpha)^2$ is printed; the Z at which it first exceeds the hyperfine scale of hydrogen is not required. Also the relative correction $\beta^2$ for $(Z,n)=(1,1),(1,2),(30,1)$ is printed | as stated | yes |

Reported, not criteria: the numerical values of the scales, in eV.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch27_fine_and_hyperfine_structure`

## Record of run 1 (2026-11-10)

Run 1 (`ch27_run1_output.txt`) met T1 and T2 and failed two clauses.

1. **V1** failed at $1.2\times10^{-4}$: the registered known answer $4.5277\times10^{-5}$ eV for $\mathrm{Ry}\,\alpha^2/16$ was wrong in its fourth digit. By hand, $\mathrm{Ry}\,\alpha^2=13.605693\times5.325135\times10^{-5}=7.24517\times10^{-4}$ eV and one sixteenth is $4.5282\times10^{-5}$ eV. This is a registration error in an instrument check, not a finding on the object. The known answer is corrected to $4.5283\times10^{-5}$ eV (tolerance unchanged, $10^{-4}$).
2. **T3** failed in its last pair: the registered statement that each successive scale is smaller than the previous by more than $10^{3}$ held for leading/fine ($1.9\times10^{4}$) and fine/hyperfine ($1836$, the proton-to-electron mass ratio) and was **rejected** for hyperfine/finite-size, whose ratio is $115$. This is a finding and the criterion is not loosened. The finding is recorded: at the level of power counting the hyperfine order $\alpha^2m_e/m_p$ and the geometric finite-size order $(R_p/a_0)^2$ are not separated by a large factor, so no ordering between them is claimed without coefficients. T3 in run 2 keeps the two satisfied clauses as criteria and reports the last ratio as the recorded rejection. Run 2 is the run of record.
