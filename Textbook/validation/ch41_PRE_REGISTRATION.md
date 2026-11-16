# Chapter 41 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch41_the_spaz_state_and_sz.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The Spaz state coordinate $S$ and its reporting convention Sz as a family of ratios $Q_i(S)/Q_i(S_0)$. Neither name fixes an absolute zero, a normalisation or an evolution rate. The chapter executes the structural statements: (a) finite ratios are invariant under a reparameterisation $S\to f(S)$ while derivatives transform by $1/f'$; (b) for monomial relations the log-derivatives $a_i=d\ln Q_i/dS$ obey exactly $a_c=a_{P_l}-a_{P_t}$ for $c=P_l/P_t$, and $a_v=a_c-a_k$, $2a_k=a_r-a_{\rm Om}$ for $v=c/k$, $k^2=r/\mathrm{Om}$; (c) compatibility leaves constitutive freedom: two different routes through the admissible ratio manifold satisfy the same relation with different individual exponents; (d) the logarithmic chart fails at zeros and sign changes, and a signed chart ($\sinh^{-1}$) removes the singularity but does not preserve the additivity of the monomial relations, which is why an atlas of overlapping charts is needed; (e) a law of constant rate in $S$ is not invariant under $S\to S^2$, so a law cannot depend on the numerical spacing of Sz marks unless the spacing is operationally calibrated. All functions are generic test functions (TOY); no measured input.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $a=d\ln Q/dS$ for $Q=e^{2S}$ is 2 and for $Q=S^3$ at $S=2$ is $3/2$ (central difference with Richardson, step $10^{-3}$) | $10^{-8}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | invariance. For $Q(S)=\exp(0.7S+0.2\sin3S)$, $S_0=0.1$, and $f(S)=S+0.3S^3$: the ratio $Q(S)/Q(S_0)$ computed in the variable $S'=f(S)$ equals the original at 50 points to $10^{-14}$; the log-derivative in $S'$ equals $a(S)/f'(S)$ to $10^{-7}$ | as stated | yes |
| T2 | compatibility. For random smooth positive $P_l(S),P_t(S),r(S),\mathrm{Om}(S),c(S)$ at 20 values of $S$: $a_c=a_{P_l}-a_{P_t}$; with $k=\sqrt{r/\mathrm{Om}}$ and $v=c/k$: $a_k=\tfrac12(a_r-a_{\rm Om})$ and $a_v=a_c-a_k$ (with $c$ here the same-named speed function) | $10^{-7}$ | yes |
| T3 | freedom. Route A: $P_l=e^{S}$, $P_t=e^{S/2}$; route B: $P_l=e^{2S}$, $P_t=e^{3S/2}$: both give $c=P_l/P_t=e^{S/2}$ at every $S$ (to $10^{-14}$) while $a_{P_l}=1$ and $2$ differ | exact | yes |
| T4 | charts. $Q(S)=\sin S$ on 1000 points of $[0.1,6.2]$: the logarithmic ratio chart fails (non-positive $Q$) at a counted number of points (printed; must be $>0$); the chart $\sinh^{-1}(Q/Q_{\rm ref})$ is finite at all 1000; for two positive functions $A,B$, $\ln(AB)=\ln A+\ln B$ to $10^{-14}$ but $\sinh^{-1}(AB)\ne\sinh^{-1}A+\sinh^{-1}B$ with the difference above $10^{-2}$ at some point | as stated | yes |
| T5 | spacing. $Q=e^{-kS}$ with $k=0.8$ has constant log-derivative; in $S'=S^2$ the log-derivative $d\ln Q/dS'=-k/(2\sqrt{S'})$ has a coefficient of variation above 0.3 over $S'\in[0.5,9]$ while in $S$ it is 0 to $10^{-8}$ | as stated | yes |

Reported, not criteria: the number of chart failures, the maximum chart additivity violation.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch41_the_spaz_state_and_sz`
