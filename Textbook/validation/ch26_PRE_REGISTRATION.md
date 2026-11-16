# Chapter 26 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch26_quantisation_by_recurrence.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. Discrete closure of a persistent circulation and what it does and does not establish. (a) For a circular route with phase closure $J_n=nJ_1$, $J=mvr$, and circular speed $v^2r=c^2\mathrm{Om}$, the radii and speeds are $r_n\propto n^2$, $v_n\propto1/n$ and the ladder energy scale is $\tfrac12mv_n^2=\tfrac12m\alpha^2c^2/n^2$ for $Z=1$ (the engine's $E_n=-\mathrm{Ry}\,Z^2/n^2$; the identification of $\tfrac12m_e\alpha^2c^2$ with Ry is **shared-input** with the CODATA set); (b) an integer closure condition produces a ladder for every exponent of a central kernel $a=-r^{-p}$: $r_n=n^{2/(3-p)}$ (units $J_1=m=1$), but the route is stable only for $p<3$ (Chapter 17, $\kappa^2=(3-p)\omega^2$), so integer counting without a restoring response is not a quantisation proof; (c) the transition ledger $\Delta E=E_{\rm seat}Z^2(n_{\rm low}^{-2}-n_{\rm high}^{-2})$ obeys the Ritz combination exactly and has series limits; (d) the movement-budget limit of the leading-order ladder, $v_{Z1}<c\iff Z<1/\alpha$. No spectrum is compared with a measured line.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | root finder on $f(r)=r^{(3-p)/2}-n$ for $p=2$, $n=3$: $r=9$; for $p=1$, $n=4$: $r=4$ | $10^{-12}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | closure algebra, $Z=1\ldots5$, $n=1\ldots10$: with $\mathrm{Om}_Z=Zr_e$ and $J_1=m_e\,Z\alpha c\,a_0/Z=\hbar$ (shared-input), $J_n=m_ev_nr_n=n\hbar$; $r_n/r_1=n^2$; $v_n/v_1=1/n$; $\tfrac12m_ev_{1n}^2=\mathrm{Ry}\,Z^2/n^2$ with the engine's Ry (shared-input) | $10^{-14}$ for ratios; $10^{-9}$ for the Ry and $\hbar$ identifications | yes |
| T2 | kernel family. For $p\in\{1,\,1.5,\,2,\,2.5,\,2.9\}$ and $n=1\ldots8$, the radius solving $J=r^{(3-p)/2}=n$ (by bisection) equals $n^{2/(3-p)}$; the radial frequency ratio $\kappa/\omega=\sqrt{3-p}$ is real for all five (stable routes) and imaginary for $p=3.5$ (unstable), so a ladder exists for $p=3.5$ ($r_n=n^{-4}$) though no route persists | $10^{-12}$ | yes |
| T3 | transition ledger. For $Z=1\ldots4$ and all $1\le n_1<n_2<n_3\le12$: $\Delta E(n_1\to n_3)=\Delta E(n_1\to n_2)+\Delta E(n_2\to n_3)$ exactly (Ritz); $\Delta E(n\to\infty)=\mathrm{Ry}Z^2/n^2$; $\Delta E\propto Z^2$ | $10^{-14}$ relative | yes |
| T4 | budget limit. The largest integer $Z$ with $Z\alpha c<c$ is 137; $1/\alpha=137.036$; $(Z\alpha)^2$ at $Z=137$ is 0.9997 (printed) | exact integer | yes |

Reported, not criteria: the ladder radii of the family, the size of $(Z\alpha)^2$.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch26_quantisation_by_recurrence`

## Record of run 1; repair of the root finder (2026-11-10)

Run 1 (`ch26_run1_output.txt`) met V1, T1, T3, T4 and the stability clause of T2 for the five stable kernels, and failed two clauses of T2. Cause: the bisection of the instrument used the fixed bracket $[10^{-12},10^{12}]$ and assumed $f(r)=r^{(3-p)/2}$ increasing. For $p=2.9$ the radii reach $n^{20}$ (up to $1.2\times10^{18}$ at $n=8$), outside the bracket, and for $p=3.5$ the exponent $(3-p)/2$ is negative so $f$ decreases and the direction of the bisection was reversed. Both are instrument defects and the registered criteria are unchanged. The root finder is repaired with the bracket $[10^{-30},10^{30}]$ and the bisection direction chosen from the sign of the exponent. Run 2 is the run of record.
