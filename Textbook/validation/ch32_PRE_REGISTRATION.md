# Chapter 32 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch32_condensed_phases_and_materials.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The determining equations of constitutive and phase response, executed on generic stand-ins (TOY; no measured material input). The engine's `materials.hpp` aggregates bulk state (baryon count, density, koppa density, far acceleration, a normalised helical wake kernel) and carries no elastic tensor, no equation of state and no thermal law; the chapter therefore assigns no closed material law. (a) Linear elasticity $\delta\sigma=C:\delta\varepsilon$ for a cubic stiffness $(C_{11},C_{12},C_{44})$: positive definiteness of the Voigt matrix is equivalent to $C_{11}>|C_{12}|$, $C_{11}+2C_{12}>0$, $C_{44}>0$; stable constants have real wave speeds in every direction (the Christoffel matrix is positive definite); the isotropic reductions obey the Voigt–Reuss inequality $G_R\le G_V$ with equality exactly at the Zener ratio $A=2C_{44}/(C_{11}-C_{12})=1$, so a scalar modulus discards anisotropy; (b) the coexistence slope $dP/dT=\Delta s/\Delta v=L/(T\Delta v)$ on a TOY pair of Gibbs functions, checked against the numerically computed coexistence curve; (c) periodic thermal forcing: the thermal penetration depth $\delta=\sqrt{2\alpha_{\rm th}/\omega}$ with amplitude decay $e^{-x/\delta}$ and phase lag $x/\delta$, checked against a time-domain finite-difference solution of the heat equation. A statement that dilute hard-lock transport ratios do not carry over to dense phases is made in the chapter without numbers because no dense-phase measured values are loaded.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | isotropic constants from $(\lambda,G)=(2,1)$: $C_{11}=\lambda+2G=4$, $C_{12}=\lambda=2$, $C_{44}=G=1$ give Zener $A=1$, bulk modulus $(C_{11}+2C_{12})/3=\lambda+2G/3$ and $G_V=G_R=G$ | $10^{-14}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | for 20000 pseudo-random cubic triples ($C_{11}\in[-2,10]$, $C_{12}\in[-4,6]$, $C_{44}\in[-2,5]$): (a) Cholesky success of the $6\times6$ Voigt matrix equals the three inequalities in every case; (b) for stable triples the smallest eigenvalue of the Christoffel matrix over 50 random directions is positive; for the unstable triple $(3,1,-1)$ the $[100]$ shear branch has eigenvalue $-1$ (imaginary speed); (c) for stable triples $G_R\le G_V$ in every case, with $(G_V-G_R)/G_H$ printed at its maximum over the sample and equal to 0 at $A=1$ (isotropic triples) to $10^{-12}$ | exact / $10^{-12}$ | yes — a mismatch of (a), a negative eigenvalue for a stable triple, or $G_R>G_V$ rejects |
| T2 | TOY Gibbs functions $g_i(T,P)=-s_i\,\theta-\tfrac{c_i}{2T_0}\theta^2+v_i\,\pi-\tfrac{\kappa_i v_i}{2}\pi^2$ with $\theta=T-T_0$, $\pi=P-P_0$, phase 1: $(s,c,v,\kappa)=(1.0,2.0,1.0,0.10)$, phase 2: $(1.5,3.0,1.2,0.12)$, with $g_1(T_0,P_0)=g_2(T_0,P_0)=0$ ($T_0=1$, $P_0=0$). The coexistence curve $P_c(T)$ from $g_1=g_2$ by Newton at 20 temperatures in $[0.9,1.1]$; central-difference $dP_c/dT$ equals $\Delta s/\Delta v$ with $s_i=-\partial g_i/\partial T$, $v_i=\partial g_i/\partial P$ on the curve, to $10^{-6}$ relative; and equals $L/(T\Delta v)$ with $L=T\Delta s$ | $10^{-6}$ | yes |
| T3 | heat equation $\partial_tT=\alpha\,\partial_x^2T$ with $\alpha=1$, $T(0,t)=\cos\omega t$, $\omega=2$ ($\delta=1$), $T(8,t)=0$, Crank–Nicolson, $dx=0.01$, $dt=0.005$, 30 periods, zero initial state; amplitude and phase extracted over the last period at $x=\delta$ and $2\delta$: amplitude ratio to $e^{-1},e^{-2}$ within $3\times10^{-3}$ relative; phase lag within $5\times10^{-3}$ rad of $x/\delta$ | as stated | yes |

Reported, not criteria: maxima of the Voigt–Reuss spread, the coexistence slope values.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch32_condensed_phases_and_materials`
