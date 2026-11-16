# Chapter 56 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch56_cross_domain_prediction.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. A cross-domain test freezes common parameters on one observable family and predicts another. (a) The hard-lock transport kernel (`law_IV::transport::monatomic_state`): one collision measure $\sigma_{\rm coll}=\tfrac67(2b)^2$ enters viscosity $\eta=\tfrac5{16}\sqrt{mk_BT/\pi}/\sigma_{\rm coll}$, conductivity $\kappa=\tfrac{75}{64}k_B\sqrt{k_BT/(\pi m)}/\sigma_{\rm coll}$ and self-diffusivity $D=\tfrac38\sqrt{k_BT/(\pi m)}/(n\sigma_{\rm coll})$ with $n=P/(k_BT)$. With $c_p=\tfrac52k_B/m$ the ratios are $\mathrm{Pr}=c_p\eta/\kappa=2/3$, $\mathrm{Sc}=\eta/(\rho D)=5/6$, $\mathrm{Le}=\kappa/(\rho c_pD)=5/4$, independent of $T$, $P$, $m$ and $b$; only two are independent since $\mathrm{Le}=\mathrm{Sc}/\mathrm{Pr}$. At fixed pressure $\eta,\kappa\propto T^{1/2}$ and $D\propto T^{3/2}$, $D\propto1/P$. (b) Freezing the kernel on one observable (viscosity at one temperature fixes $\sigma_{\rm coll}$) predicts the others with no further parameter. (c) Optical–hydrodynamic invariant: for a steady spherical outflow $n=Q/(4\pi vr^2)$ with constant extinction cross-section $\sigma_{\rm ext}$ and no destruction the radial optical depth is $\tau=Q\sigma_{\rm ext}/(4\pi vr)$, so $r_{\rm photo}=Q\sigma_{\rm ext}/(4\pi v)$ and, with mean free path $1/(n\sigma_{\rm coll})$, $\mathrm{Kn}(r_{\rm photo})=\sigma_{\rm ext}/\sigma_{\rm coll}$: production and speed cancel. A full tangent column at impact radius $b$ exceeds the outward radial column at $r=b$ by the factor $\pi$ in the infinite constant-speed model. (d) Thermal penetration $\delta=\sqrt{2\alpha_{\rm th}/\omega}$; for a single relaxing reservoir driven sinusoidally the steady modulation gain is $[1+(\omega t_{\rm th})^2]^{-1/2}$ and the lag $\arctan(\omega t_{\rm th})$. Inputs: $k_B$, $\pi$; a generic monatomic load $m=39.948$ u and generic boundaries; no measured transport value is loaded; the outflow numbers are TOY stand-ins.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $\mathrm{Pr}$, $\mathrm{Sc}$, $\mathrm{Le}$ from the hand formulas of the kernel for one state: $2/3$, $5/6$, $5/4$ by algebra; $\int_{-\infty}^{\infty}dl/(b^2+l^2)=\pi/b$ by quadrature to $L=10^4b$ against $2\arctan(L/b)/b$ | $10^{-14}$, $10^{-9}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | kernel ratios. For $T\in\{100,300,1000\}$ K, $P\in\{10^3,10^5,10^7\}$ Pa, $b\in\{1.0,1.9,2.5\}\times10^{-10}$ m: $\mathrm{Pr}=2/3$, $\mathrm{Sc}=5/6$, $\mathrm{Le}=5/4$ and $\mathrm{Le}=\mathrm{Sc}/\mathrm{Pr}$ to $10^{-13}$; the log-log slopes of $\eta$ and $\kappa$ against $T$ at fixed $P$ are $0.5$ and of $D$ is $1.5$, and of $D$ against $P$ is $-1$ (to $10^{-12}$) | as stated | yes |
| T2 | one kernel, three observables. From a viscosity value computed at $T=300$ K, $P=10^5$ Pa, $b=1.9\times10^{-10}$ m the collision measure is recovered as $\tfrac5{16}\sqrt{mk_BT/\pi}/\eta$ and the conductivity and diffusivity predicted from it equal the engine's to $10^{-12}$; the predicted conductivity at 1000 K from the 300 K viscosity equals the engine's value at 1000 K (scaling $T^{1/2}$) to $10^{-12}$ | as stated | yes |
| T3 | optical–hydrodynamic invariant. For 12 combinations of $Q\in[10^{20},10^{32}]$ s$^{-1}$, $v\in[10,10^4]$ m/s, $\sigma_{\rm ext}$, $\sigma_{\rm coll}$ the Knudsen number at $r_{\rm photo}$ equals $\sigma_{\rm ext}/\sigma_{\rm coll}$ to $10^{-12}$; the tangent column from numerical integration over $|l|\le10^4b$ equals $2\arctan(10^4)/b\cdot Q\sigma/(4\pi v)$ to $10^{-9}$ and the ratio to the radial column is within $2\times10^{-4}$ of $\pi$; the generic outflow $Q=10^{28}$ s$^{-1}$, $v=500$ m/s, $\sigma_{\rm ext}=10^{-20}$ m$^2$ gives $r_{\rm photo}$ in $[1.5,1.7]\times10^4$ m | as stated | yes |
| T4 | rotation, heat and appearance. The solution $T=\mathrm{Re}[Ae^{i\omega t-(1+i)x/\delta}]$ satisfies $\partial_tT=\alpha\partial_x^2T$ with $\delta=\sqrt{2\alpha/\omega}$ (finite-difference residual below $10^{-6}$ relative); RK4 integration of $dT/dt=(A\sin\omega t-T)/t_{\rm th}$ for $\omega t_{\rm th}=0.1,1,10$ gives a steady amplitude $[1+(\omega t_{\rm th})^2]^{-1/2}A$ and lag $\arctan(\omega t_{\rm th})$ to $10^{-6}$; at $\omega t_{\rm th}=1$ the gain is $2^{-1/2}$ and the lag $\pi/4$ | as stated | yes |

Reported, not criteria: the transport values, $r_{\rm photo}$, the gains and lags.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch56_cross_domain_prediction`

## Record of run 1; one ambiguity in the registration and one instrument defect (2026-11-10)

Run 1 (`ch56_run1_output.txt`): every criterion was met except one, the T4 heat-equation residual: the worst value $2.03\times10^{-6}$ exceeded the registered $10^{-6}$. The registration said "finite-difference residual below $10^{-6}$ relative" without naming the normaliser. The instrument divided each point's residual $|\partial_tT-\alpha\partial_x^2T|$ by $|\partial_tT|$ at that point; $\partial_tT$ passes through zero along the travelling solution, so that ratio is ill-defined near its zeros and the worst value came from such a point (a defect of the normalisation, not of the solution). The criterion is evaluated with the normaliser fixed to the amplitude of $\partial_tT$ at the same depth, $\omega e^{-x/\delta}$ (the natural scale that does not vanish); the tolerance $10^{-6}$ is unchanged. All other T1–T4 results of run 1 are unchanged. Run 2 is the run of record.
