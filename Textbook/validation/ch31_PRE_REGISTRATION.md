# Chapter 31 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch31_molecular_bonding_and_reactions.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. What a statement of bonding requires, with no closed bond functional assigned. The engine holds no bond energy functional; the source history (CH07) records that a simple inverse-radius well did not supply the required stiffness and that a rolling-wall repair did not close the curvature/depth account. The chapter executes the determining equations on model energy functions of separation $R$, labelled TOY (generic, no measured input): (a) a bond is a stationary point with $E''>0$; a pure inverse-radius well $E=-A/R$ has no stationary point, and with a hard wall at contact its minimum on the boundary has $E'\ne0$ (a wall, not a restoring response); a Mie family $E=-A/R+B/R^m$ with $m>1$ has $R_*=(mB/A)^{1/(m-1)}$, $E''(R_*)=(A/R_*^3)(m-1)$ and $D=-E(R_*)=(A/R_*)(1-1/m)$, so $kR_*^2/D=m$; (b) isotope scaling $\omega\propto\mu^{-1/2}$ and mass-independent $R_*$, $D$ follow from the form of the response for every family (the surviving block), with reduced masses from the stored $m_p,m_d$; (c) counting: three observables $(R_*,k,D)$ are absorbed exactly by the three Mie parameters, so they cannot discriminate between families; a fourth observable (the cubic coefficient $E'''(R_*)$) does: Mie gives $-k(m+4)/R_*$ and Morse gives $-6D(k/2D)^{3/2}$; (d) pathway dependence: on a two-coordinate TOY surface a localised term lowers the relaxed barrier while leaving both endpoint minima unchanged. No measured molecular constant is loaded.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | Morse $E=D(1-e^{-a(R-R_0)})^2$ with $D=2,a=1.5,R_0=1$: finite-difference $E''(R_0)=2Da^2=9$ and $E'''(R_0)=-6Da^3=-40.5$ | $10^{-4}$ (relative; step $10^{-3}$ with Richardson) |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | (a) $E=-1/R$ on a grid of 2000 log-spaced $R\in[10^{-3},10^{3}]$ has $E'>0$ everywhere (no stationary point); with a wall at $R_c=1$ the minimum over $R\ge R_c$ is at $R_c$ and $E'(R_c)=1\ne0$. (b) For Mie with $(A,B,m)=(1,1,2),(1,0.5,3),(2,1,6),(3,2,12)$: the stationary point found by bisection on $E'$ equals $(mB/A)^{1/(m-1)}$, $E''>0$ there, $D=(A/R_*)(1-1/m)$ and $kR_*^2/D=m$ | $10^{-10}$ relative | yes — a stationary point of the inverse well, or $E''\le0$ for $m>1$, rejects |
| T2 | isotope scaling. For the four Mie families and a Morse family, with $\mu_{\rm H_2}=m_p/2$, $\mu_{\rm HD}=m_pm_d/(m_p+m_d)$, $\mu_{\rm D_2}=m_d/2$: $\omega=\sqrt{E''(R_*)/\mu}$ obeys $\omega_{\rm H_2}/\omega_{\rm D_2}=\sqrt{\mu_{\rm D_2}/\mu_{\rm H_2}}$ and $\omega_{\rm H_2}/\omega_{\rm HD}=\sqrt{\mu_{\rm HD}/\mu_{\rm H_2}}$; $R_*$ and $D$ are identical for the three | $10^{-12}$ relative | yes |
| T3 | counting. For 1000 pseudo-random triples $(R_*,k,D)$ with $kR_*^2/D>1$ the Mie parameters $m=kR_*^2/D$, $A=kR_*^3/(m-1)$, $B=AR_*^{m-1}/m$ reproduce all three observables to $10^{-12}$ (residual 0); for $kR_*^2/D\le1$ no Mie member exists. For $(R_*,k,D)=(1,20,2)$: Mie has $m=10$ and $E'''=-280$; Morse with the same three observables has $E'''=-134.16$; finite differences confirm both to $10^{-3}$ relative, and the two differ by a factor above 2 | as stated | yes |
| T4 | pathway. TOY surface $E(x,y)=(x^2-1)^2+2(y-0.3x^2)^2-g\,e^{-(x^2+y^2)/w^2}$ with $w=0.15$; $g=0$ and $g=0.4$. Relaxed energy $E_{\min}(x)=\min_yE$ (Newton in $y$) on 2001 points of $[-1,1]$. Registered: endpoint energies at $x=\pm1$ ($y$ relaxed) equal the $g=0$ values to $10^{-12}$; the barrier (maximum of $E_{\min}$ above the endpoint) is lowered by at least $0.1$ and by at most $g$ | as stated | yes — an unchanged barrier rejects |

Reported, not criteria: the numerical barrier heights.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch31_molecular_bonding_and_reactions`

## Record of run 1; repair of the T3 parameter-inversion clause (2026-11-10)

Run 1 (`ch31_run1_output.txt`) met V1, T1, T2, T4 and the $E'''$ clauses of T3 ($-279.9992$ against $-280$; $-134.1641$ against $-134.1641$; ratio above 2), and failed the clause that reproduces the three observables for 1000 random triples. The instrument evaluated $E'(R_*)$ and $k$ by finite differences (step $10^{-6}R_*$ and $10^{-3}R_*$); in the random triples $m=kR_*^2/D$ reaches several hundred (up to about 950), where $E'''\sim m^2A/R_*^4$ and the truncation error of those differences exceeds the registered $10^{-9}$. This is an instrument defect, not a finding on the object: the inversion $m=kR_*^2/D$, $A=kR_*^3/(m-1)$, $B=AR_*^{m-1}/m$ is exact. The clause is repaired by evaluating $E'(R_*)$, $E''(R_*)$ and $D$ from the **analytic** derivatives of the Mie function, $E'=A/R^2-mB/R^{m+1}$ and $E''=-2A/R^3+m(m+1)B/R^{m+2}$, at tolerance $10^{-10}$ relative to $A/R_*^2$ and $k$ respectively; the finite-difference evaluation is kept for the $E'''$ comparison at $m=10$. Run 2 is the run of record.
