# Chapter 43 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch43_constitutive_response.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. What a constitutive operator must supply beyond compatibility, with generic stand-ins (TOY; no measured input). (a) A conditional stationary reduction: minimise a supplied functional $F(J)=\tfrac12J^TQJ+c^TJ$ subject to $CJ=b$; the multipliers satisfy $\nabla_JF+C^T\lambda=0$ and, for the convention $CJ-b=0$, $\partial F^*/\partial b=-\lambda$ (the marginal response of the constrained optimum to the constraint); the mathematics is shared with other allocation problems, but a cost functional must be derived for the physical system and cannot be taken from the analogy; (b) local identifiability of a model $y(t;\theta)$ from the rank and conditioning of the sensitivity matrix $S_{kj}=\partial y(t_k)/\partial\theta_j$: a two-exponential model with nearly equal rates has nearly parallel sensitivity columns and a large condition number, exactly rank-deficient at equal rates; (c) the useful next measurement distinguishes response directions: repeating the same sampling times leaves the condition number exactly unchanged, while adding samples at times where the columns differ reduces it. The state route is $dS/d\tau=F_S(S,\eta)$ separate from the correlated map $Q_i(S;\eta)$ (Chapter 41); a calibrated ladder constrains the first without determining elapsed time.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | the constrained quadratic with $Q=I_2$, $c=0$, one constraint $J_1+J_2=1$: $J=(1/2,1/2)$, $\lambda=-1/2$, $F^*=1/4$; the symmetric Jacobi eigen routine on $\mathrm{diag}(1,4,9,16)$ rotated by a fixed orthogonal matrix returns $1,4,9,16$ | $10^{-12}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | allocation. $Q=\begin{pmatrix}2&.2&0&0\\.2&3&.1&0\\0&.1&4&.3\\0&0&.3&5\end{pmatrix}$, $c=(1,-2,.5,1)$, $C=\begin{pmatrix}1&1&1&1\\1&-1&0&2\end{pmatrix}$, $b=(1,0.3)$: the KKT system is solved by Gaussian elimination; $\lVert\nabla F+C^T\lambda\rVert\le10^{-12}$ and $\lVert CJ-b\rVert\le10^{-12}$; $\partial F^*/\partial b_i$ by central difference (step $10^{-4}$) equals $-\lambda_i$ for $i=1,2$ | $10^{-8}$ relative | yes |
| T2 | identifiability. $y=ae^{-bt}+ce^{-dt}$, $\theta=(1,1,1,1+\Delta)$, $t_k=0.2k$, $k=1\ldots10$: the condition number $\kappa(S)=\sigma_{\max}/\sigma_{\min}$ (from the eigenvalues of $S^TS$) increases as $\Delta$ falls through $1,\,0.1,\,0.01$; at $\Delta=0$ the smallest singular value is below $10^{-6}\sigma_{\max}$ (not identifiable) | as stated | yes |
| T3 | next measurement. For $\Delta=0.1$: appending a second copy of the same 10 times leaves $\kappa$ unchanged to $10^{-12}$ relative; appending 10 samples at $t=4,4.5,\ldots,8.5$ reduces $\kappa$ by at least a factor 2 | as stated | yes |

Reported, not criteria: the condition numbers and multipliers.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch43_constitutive_response`

## Record of run 1; a weak pass and the repair (2026-11-10)

Run 1 (`ch43_run1_output.txt`) met every registered criterion (V1 exact; T1: stationarity and constraint residuals $2.2\times10^{-16}$, multipliers $\lambda=(-0.549290,-0.973820)$, $F^*=0.15862572$, $\partial F^*/\partial b_i=-\lambda_i$ to $1.4\times10^{-12}$ and $1.8\times10^{-12}$; T3: repeating the times leaves $\kappa=2.80\times10^{5}$ unchanged, adding later times gives $5.96\times10^{4}$, a reduction by 4.70) but the T2 pass is **weak**. The instrument computed singular values from the eigenvalues of $S^TS$, which squares the condition number: for $\Delta=0.01$ the smallest eigenvalue fell below the double-precision floor ($\sigma_{\min}/\sigma_{\max}\lesssim10^{-8}$), was read as $0$, and the condition number printed as infinity; the registered "increases through $1,0.1,0.01$" held only because $\infty$ exceeds a finite value. At $\Delta=0.1$ ($\sigma_{\min}=8.06\times10^{-6}$) the value is resolved. This is an instrument limitation, not a finding on the object. The singular values are recomputed by a one-sided Jacobi (Hestenes) iteration on the columns of $S$, which does not form $S^TS$ and keeps small singular values to high relative accuracy; the criteria are unchanged and, in addition, the condition number at $\Delta=0.01$ must be finite and exceed that at $\Delta=0.1$ by a factor of at least 5. Run 2 is the run of record.
