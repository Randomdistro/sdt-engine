# Chapter 46 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch46_hydrogen_proton_boundary_crossing.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The ratio of the hydrogen c-boundary $\mathrm{Om}_H=r_e=\alpha^2a_0$ (`measured::r_e`) to the proton boundary, and the condition for a crossing $\mathcal R=1$ along a state route $S$. (a) With the lock radius $R_{p,\rm lock}=4\hbar/(m_pc)$ (`law_III::R_p_lock`, coordination 4) the action-seat relation $a_0=\hbar/(m_ec\alpha)$ gives $\mathcal R_{\rm lock}=\mathrm{Om}_H/R_{p,\rm lock}=(\alpha/4)(m_p/m_e)$; with the measured structural radius $R_p=C_gR_{p,\rm lock}$, $\mathcal R=\mathcal R_{\rm lock}/C_g$ (46.1). (b) The logarithmic change obeys $d\ln\mathcal R=(a_\alpha+a_{m_p}-a_{m_e}-a_{C_g})\,dS$; a crossing satisfies $\int r\,dS=-\ln\mathcal R_0$ with $r=a_\alpha+a_{m_p}-a_{m_e}-a_{C_g}$. (c) A fixed-coordinate crossing (only $\mathrm{Om}_H$ responds) and a contemporaneous crossing (both sectors respond) with the same net rate $r$ cross at the same $S$ but with different end states, so a result stated in an absolute scale (such as a temperature of the crossing state) needs the relative response law. (d) The crossing $S^*$ scales as $1/|r|$: the ratio route alone does not give the progression, which needs a rate $dS/d\tau$ (Chapters 41, 43). Inputs: $\{\hbar,c,\alpha,m_e,m_p,a_0\}$ are CODATA 2022 in `sdt::laws::measured`; $R_p$ is the stored measured proton boundary radius, read after the native lock quantities are printed.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | the reduced proton Compton length $\hbar/(m_pc)=2.103089\times10^{-16}$ m; the classical electron radius $r_e=2.8179403\times10^{-15}$ m; the RK4 integrator on $d\mathcal R/dS=r\mathcal R$ with $r=-1$, $\mathcal R_0=3$ returns $3e^{-1}$ at $S=1$ | $10^{-6}$, $10^{-7}$, $10^{-12}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | the lock ratio. Computed before $R_p$ is read: $\mathcal R_{\rm lock}$ directly from $\mathrm{Om}_H/(4\hbar/(m_pc))$ and from $(\alpha/4)(m_p/m_e)$ agree to $10^{-9}$; the value is $3.34976$ to $10^{-5}$ relative; `trefoil_lock_coordination` equals 4 and `R_p_lock` equals $4\hbar/(m_pc)$ to $10^{-14}$. Then, read: $C_g=R_p/R_{p,\rm lock}$ satisfies $|C_g-1|<10^{-3}$; $\mathcal R=\mathrm{Om}_H/R_p$ is reported | as stated | yes |
| T2 | the crossing. $-\ln\mathcal R_{\rm lock}$ lies in $[-1.2095,-1.2085]$. For constant net rate $r=-1$ the crossing found by RK4 and bisection equals $-\ln\mathcal R_0/r$ to $10^{-9}$ in two scenarios: contemporaneous ($a_{\rm Om}=-2$, $a_{R_p}=-1$) and fixed-coordinate ($a_{\rm Om}=-1$, $a_{R_p}=0$); the end-state proton boundary radii differ by the factor $\mathcal R_0$ to $10^{-9}$. For the non-constant net rate $r(S)=-1-S/2$ the crossing equals $2(\sqrt{1+\ln\mathcal R_0}-1)$ to $10^{-9}$ | as stated | yes |
| T3 | rate and branch. $S^*(r=-0.5)=2S^*(r=-1)$ and $S^*(r=-2)=\tfrac12S^*(r=-1)$ to $10^{-9}$; the two branches (lock and measured radius) differ in the required log change by $\ln C_g$ and $|\ln C_g|<10^{-3}$ | as stated | yes |

Reported, not criteria: $C_g$, $\mathcal R$ for the measured radius, $S^*$ for each scenario.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch46_hydrogen_proton_boundary_crossing`
