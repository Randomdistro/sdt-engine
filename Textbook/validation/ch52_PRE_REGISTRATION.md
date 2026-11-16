# Chapter 52 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch52_thermal_and_radiation_puzzles.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents). Disclosure: the output file of the earlier FLM15-cas reset run (`flm15cas_reset_1_results.txt`) and its source were read before this registration; the present instrument is written afresh with its own routines and is registered against the analytic results below, not against that file.

Object. Mode geometry and occupation are separate. Counting allowed modes between two ideal parallel plates supplies a density of states; energy needs an occupation or price per mode. (a) For a scale-free mode price $a\hbar\omega$ the regularised energy difference per area is $\Delta E/A=-a\pi^2\hbar c/(360d^3)$ and the pressure $-a\pi^2\hbar c/(120d^4)$ (standard-form ideal-plate result for $a=\tfrac12$: $-\pi^2\hbar c/(720d^3)$ and $-\pi^2\hbar c/(240d^4)$). With the smooth cutoff $e^{-\lambda\omega/c}$ the per-area energy difference in units $a\hbar c/d^3$ is $E(x)=2[\tfrac12g(0)+\sum_{n\ge1}g(n\pi/d)-(d/\pi)\int_0^\infty g\,dq]$ with $g(q)=e^{-\lambda q}(q^2/\lambda+2q/\lambda^2+2/\lambda^3)/(2\pi)$, $\int_0^\infty g\,dq=3/(\pi\lambda^4)$ for this $g$, and $x=\lambda/d$ (lengths in units of $d$ when $d=1$); Euler–Maclaurin gives $E(x)\to-\pi^2/360$ as $x\to0$ with corrections in powers of $x^2$. (b) Thermal occupation at the present CMB temperature leaves a pressure $u_{\rm CMB}/3$ independent of the plate separation; the ideal-plate pressure $\pi^2\hbar c/(240d^4)$ equals it at $d_*=(\pi^2\hbar c/(80u_{\rm CMB}))^{1/4}$ and is larger below. (c) A finite transparency cutoff at fixed $\lambda$ changes the local scaling exponent of $\Delta E$: $-d\ln|\Delta E|/d\ln d\to3$ for $d\gg\lambda$, and $\Delta E$ changes sign at some $d/\lambda$ and is positive for $d\ll\lambda$ (where $E\to g(0)=1/(\pi\lambda^3)$). (d) A length $\lambda$ chosen to reproduce a measured deviation at one separation is a fitted length and makes a prediction for other separations: the deviation $1-|E|/|E_0|\propto x^2$ at fixed $\lambda$, so it falls by a factor 4 when $d$ doubles. Inputs: $\{\hbar,c,k_B\}$ and $T_{\rm CMB}$ (`measured`); the native radiation constant of Chapter 44 is used for $u_{\rm CMB}$; no measured force is loaded.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $\int_0^\infty g\,dq=3/(\pi\lambda^4)$ by quadrature at $\lambda=1$; $\int_0^\infty x^3/(e^x-1)dx=\pi^4/15$; the Euler–Maclaurin coefficient: the series of $g$ at $q=0$ has $g'''(0)=-1/\pi$ (finite difference, $\lambda=1$) | $10^{-9}$, $10^{-10}$, $10^{-5}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | scale-free price. $E(x)$ at $x=0.08,0.06,0.04,0.03$ (compensated summation); the polynomial in $x^2$ through the four points extrapolated to $x=0$ equals $-\pi^2/360$; the leading correction $E(x)/E_0-1$ is negative and proportional to $x^2$ (the ratio $(E(0.06)/E_0-1)/(E(0.03)/E_0-1)$ equals $4$ to 2 per cent) | $10^{-6}$ relative; 2 per cent | yes |
| T2 | occupation. $u_{\rm CMB}=aT^4$ with the native $a$; $u/3=1.3916\times10^{-14}$ Pa ($10^{-4}$); the ratio of $u/3$ to the ideal-plate pressure at $d=1\ \mu$m lies in $[1.0,1.1]\times10^{-11}$; $d_*$ lies in $[4\times10^{-4},7\times10^{-4}]$ m and the thermal pressure is independent of $d$ (a function of $T$ only) | as stated | yes |
| T3 | cutoff. At fixed $\lambda$: $-d\ln|\Delta E|/d\ln d$ at $d/\lambda=100$ lies in $[2.99,3.01]$; $\Delta E>0$ at $d/\lambda=0.1$; a sign change of $\Delta E$ exists between $d/\lambda=0.1$ and $100$ and is located by bisection (reported) | as stated | yes |
| T4 | fitted length. Choose $\lambda$ at $d=1$ so that $|E|/|E_0|=0.99$ (bisection on $x$); at $d=2$ with the same $\lambda$ the deficit $1-|E|/|E_0|$ equals $0.01/4$ to 4 per cent | as stated | yes |

Reported, not criteria: the values of $E(x)$ and the extrapolation; $d_*$; the sign-change position; the fitted $x$ and the predicted deficit.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch52_thermal_and_radiation_puzzles`

## Record of run 1; one registration error and one instrument defect (2026-11-10)

Run 1 (`ch52_run1_output.txt`): every criterion was met except two. (1) V1, $g'''(0)=-1/\pi$: the instrument used a four-point central difference with step $0.05$; its truncation error is $\tfrac14h^2g^{(5)}(0)=-1.2\times10^{-3}$ (with $g^{(5)}(0)=-12\lambda^2/(2\pi)$), so the value $-0.31950$ differs from $-1/\pi=-0.31831$ by $3.75\times10^{-3}$ relative against the registered $10^{-3}$. This is a registration error: the registration did not account for the known $O(h^2)$ error of the stencil. The criterion is unchanged; the instrument now applies one Richardson step (steps $h$ and $h/2$) so that the truncation error is $O(h^4)$. (2) T4: the instrument compared the energy at $d=2$ with the ideal value for $d=1$; the energy difference per area scales as $1/d^3$, so the deficit must be taken against $E_0/d^3$ (the printed deficit $0.875$ is $1-1/8$). This is an instrument defect, not a finding on the object. The criterion is unchanged; the deficit is computed against $E_0/d^3$. The T1, T2 and T3 results of run 1 (extrapolated $E(0)=-2.741556817\times10^{-2}$ against $-\pi^2/360=-2.741556778\times10^{-2}$, relative $1.4\times10^{-8}$; local exponent $2.999775$; sign change at $d/\lambda=0.81402$) are unchanged by the repair. Run 2 is the run of record.
