# Chapter 16 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch16_conservation_and_continuum_limits.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. Three levels of conservation are separated: **exact** (a property of the update rule), **coarse-grained** (a property of a continuum equation obtained from the rule by a scaling limit), and **numerical** (a property of a discretisation of a continuum equation). (a) The TOY chain of Chapter 14 on a ring: total content is conserved exactly and the momentum content $P=\sum(R_i-L_i)$ obeys $P(m)=(1-2s)^mP(0)$ exactly. (b) Its continuum limit: with hop spacing $\varepsilon$, reversal fraction $s=\gamma\varepsilon$, wavenumber $\kappa=k\varepsilon$ and scaled count $t=\varepsilon m$, the chain tends to the telegraph system $\partial_tu=-\partial_xj,\ \partial_tj=-\partial_xu-2\gamma j$ with eigenvalues $\mu_\pm=-\gamma\pm\sqrt{\gamma^2-k^2}$, at first order in $\varepsilon$. (c) A conservative and a non-conservative discretisation of $\partial_tu=\partial_x(D(x)\partial_xu)$ on a ring. (d) The engine's monatomic transport kernel `law_IV::transport` (`laws.hpp:748–827`): fixed ratios and exponents from one collision kernel; and its relation to the textbook hard-sphere first approximation as a comparison of form (agreement is convergence and is not a downgrade).

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | the conservative scheme of T4 with constant $D=1$ on a ring of $n=64$ points ($h=1/64$), initial $u=\cos(2\pi x)$, 50 steps of $\Delta=0.2h^2$: the amplitude equals the exact discrete factor $\big(1-4(\Delta/h^2)\sin^2(\pi h)\big)^{50}$ | relative $10^{-10}$ |
| V2 | the continuum solution factor $F(k,t)=(\mu_+e^{\mu_-t}-\mu_-e^{\mu_+t})/(\mu_+-\mu_-)$ equals $1$ at $t=0$, equals $\cos kt$ at $\gamma=0$ ($k=1.3$, $t=0.7$), and equals $1$ at $k=0$ for $\gamma=1$, $t=2$ | $10^{-14}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | exact conservation. A ring of 200 cells with random content (fixed generator), $s\in\{0.1,0.3\}$, 200 counts: total content stays at its start; $P(m)=(1-2s)^mP(0)$ at every count | content relative $10^{-13}$; momentum relative to $\lvert P(0)\rvert$ at most $10^{-12}$ at every count | yes — a mismatch of the factor $1-2s$ rejects |
| T2 | scaling limit of the dispersion relation. For $\gamma=1$ and $k\in\{0.5,\,2.0\}$ ($k<\gamma$ real branch, $k>\gamma$ wave branch), $\varepsilon\in\{0.1,0.05,0.025,0.0125\}$: $\ln\lambda_+(\kappa=k\varepsilon;\,s=\gamma\varepsilon)/\varepsilon$ from the chain eigenvalues is compared with $\mu_+(k)$. The error shrinks at each halving and the observed order $\log_2(e_\varepsilon/e_{\varepsilon/2})$ lies in $[0.8,1.2]$ for all three successive pairs, both $k$ | as stated | yes — a limit that does not exist or is second order rejects the claim of first order |
| T3 | real-space limit. Ring of length 40, $\gamma=1$, $\varepsilon\in\{0.1,0.05,0.025\}$ (400, 800, 1600 cells, $s=\varepsilon$), initial $R=L=\tfrac12u_0$ with $u_0(x)=\exp(-(x-20)^2/2)$, run to scaled count $t=2$ ($m=t/\varepsilon$). Compared with the continuum solution $u(x,t)=\sum_nc_nF(k_n,t)e^{ik_nx}$ ($k_n=2\pi n/40$, $\lvert n\rvert\le120$, $c_n$ the exact Fourier coefficients of the Gaussian). Relative $L^2$ error $e_\varepsilon$ decreases at each halving and the observed orders lie in $[0.8,1.3]$ | as stated | yes |
| T4 | numerical conservation. $\partial_tu=\partial_x(D\partial_xu)$ on a ring of length 1, $D(x)=1+\tfrac12\sin2\pi x$, $u_0$ Gaussian of width 0.1 at $x=0.3$, $n\in\{64,128,256\}$, $\Delta=0.2h^2/D_{\max}$, run to scaled count $0.05$. (a) Flux-form scheme $D_{i\pm1/2}$ evaluated at interfaces: relative change of $\sum u$ at most $10^{-13}$. (b) Expanded scheme $D_iu_{xx}+D'_iu_x$ with central differences: relative change of $\sum u$ exceeds $10^{-8}$ at every $n$ and shrinks with an observed order in $[1.7,2.3]$ | as stated | yes — a conservative scheme that drifts, or a non-conservative one that does not, rejects |
| T5 | engine transport kernel `transport::monatomic_state(T,P,m,b)`, test values $T=300$ K, $P=101325$ Pa, $m=6.6\times10^{-26}$ kg, $b=1.8\times10^{-10}$ m (CONSTRUCTION; no measured transport value is loaded). (a) $\mathrm{Pr}=c_p\eta/\kappa=2/3$ with $c_p=\tfrac52k_B/m$; $\mathrm{Sc}=\eta/(\rho D)=5/6$; $\mathrm{Le}=\mathrm{Sc}/\mathrm{Pr}=5/4$, $\rho=nm$, $n=P/(k_BT)$. (b) At fixed $P$: $T\to4T$ gives $\eta\times2$, $\kappa\times2$, $D\times8$; $P\to2P$ leaves $\eta,\kappa$ unchanged and halves $D$; $b\to2b$ divides all three by 4; $m\to4m$ multiplies $\eta$ by 2 and $\kappa$ by $\tfrac12$ and $D$ by $\tfrac12$. (c) the textbook hard-sphere first approximations $\eta_{HS}=\tfrac5{16}\sqrt{mk_BT/\pi}/d^2$, $\kappa_{HS}=\tfrac{75}{64}k_B\sqrt{k_BT/(\pi m)}/d^2$, $D_{HS}=\tfrac3{8}\sqrt{k_BT/(\pi m)}/(nd^2)$ with $d=2b$ stand in the ratios $\eta/\eta_{HS}=\kappa/\kappa_{HS}=D/D_{HS}=7/6$ | all to $10^{-13}$ relative | yes |

Reported, not criteria: the numerical values of $\eta,\kappa,D$ at the test point; the errors and orders of T2–T4.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch16_conservation_and_continuum_limits`
