# Chapter 53 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch53_collapse_and_singularity.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. Which observable diverges in a collapse, and what a regularity statement has to check. All models are generic stand-ins (TOY): power laws in a phase-loading variable $\chi\to\infty$, with no engine function and no measured input. (a) With mobility $\mu\sim\chi^{-p}$ and drive $F\sim\chi^m$ the response velocity is $v=\mu F=\chi^{m-p}$: motion arrests ($v\to0$) only when $p>m$. For a loading that grows as $d\chi/dt=\chi^k$ the displacement accumulated up to $\chi_{\max}$ is $D=\int v\,dt=\int_1^{\chi_{\max}}\chi^{m-p-k}d\chi=[1-\chi_{\max}^{-(k+p-m-1)}]/(k+p-m-1)$ (for $k+p-m-1\ne0$; $\ln\chi_{\max}$ at $0$): finite as $\chi_{\max}\to\infty$ only when $k+p-m>1$, so arrest ($p>m$) and finite late displacement are separate conditions. (b) Stored energy $U\sim\chi^w$ and traction $\tau\sim\chi^m$ are separate checks: velocity can go to zero while the traction diverges ($p>m>0$). (c) Axial degeneration: the physical azimuthal speed is $\rho\dot\varphi$; points on the rotation axis ($\rho=0$) have zero displacement under rotation about that axis though the angular coordinate $\varphi$ is undefined there; a finite segment tilted about a transverse pivot moves its points away from the pivot with displacement $2|s|\sin(\alpha/2)$ at distance $s$; replacing a vanishing circle of radius $R$ by an axial line sends the speed $R\dot\varphi$ to zero at fixed $\dot\varphi$, and so changes the configuration class and needs its own torque/phase-transfer rule. (d) A regularity statement needs four independent checks on a model: arrest, finite late displacement, bounded stored energy and bounded traction; over a parameter grid the fraction of models passing all four is smaller than the fraction passing any one.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $\int_1^{\infty}\chi^{-3}d\chi=\tfrac12$ by the instrument's quadrature in $\ln\chi$ to $\chi_{\max}=10^{12}$ against the truncated closed form; $\int_1^{\chi_{\max}}\chi^{-1}d\chi=\ln\chi_{\max}$; rotation of the point $(0,0,s)$ about $z$ by $\alpha$ returns the same point; about $x$ by $\alpha$ the displacement is $2|s|\sin(\alpha/2)$ | $10^{-9}$, $10^{-12}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | arrest and displacement. For $(m,p,k)\in\{(1,3,1),(1,2,1),(1,1.5,1),(1,1.2,1),(2,2.5,0.5),(2,1,1),(0,0,1)\}$: the quadrature of $D(\chi_{\max})$ at $10^{6}$ and $10^{12}$ equals the closed form to $10^{-9}$; $v(10^{12})<v(10^{6})$ exactly when $p>m$; $D(10^{12})-D(10^{6})$ is below $0.5$ exactly when $k+p-m>1$ and above $5$ otherwise (the registered case $(2,2.5,0.5)$ has $k+p-m=1$ and grows as $\ln10^{6}=13.8$); the case $(2,2.5,0.5)$ arrests but its displacement diverges | as stated | yes |
| T2 | stress and energy. For the same sets the traction $\tau=\chi^m$ at $10^{12}$ exceeds its value at $10^{6}$ exactly when $m>0$; the case $(1,3,1)$ arrests with unbounded traction | as stated | yes |
| T3 | axial degeneration. The displacement of axis points under rotation about the axis is $0$ to $10^{-16}$ for $s\in\{-2,-1,0.5,3\}$ and $\alpha=0.7$; under rotation about a transverse axis it equals $2|s|\sin(\alpha/2)$ to $10^{-12}$; the speed $R\dot\varphi$ at fixed $\dot\varphi=1$ falls by the factor $10^{-4}$ as $R$ falls from $1$ to $10^{-4}$ while the formal coordinate $\varphi=\mathrm{atan2}(y,x)$ at $\rho=0$ is the arbitrary value $0$ of the library's convention (reported) | as stated | yes |
| T4 | four checks on a grid. For $m\in\{-1,-0.5,0,0.5,1\}$, $p\in\{-1,-0.5,0,0.5,1,1.5,2,3\}$, $k=1$, $w=m$: the numbers of grid points satisfying arrest ($p>m$), finite late displacement ($k+p-m>1$), bounded energy ($w\le0$), bounded traction ($m\le0$), and all four are counted from the rules and checked against the numerical classification of the instrument; the number passing all four is less than the number passing arrest alone | as stated | yes |

Reported, not criteria: the displacements, the counts of the grid.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch53_collapse_and_singularity`
