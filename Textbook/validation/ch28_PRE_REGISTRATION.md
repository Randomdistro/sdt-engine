# Chapter 28 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch28_emission_absorption_and_linewidth.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The emission event as an outgoing relay excitation and what fixes line energy, width, harmonic content and recoil. (a) A causal response $A(t)=\theta(t)e^{-\Gamma t/2}e^{-i\omega_0t}$ has spectrum $\hat A(\omega)=1/(\Gamma/2-i(\omega-\omega_0))$ and power line $|\hat A|^2$ of full width at half maximum $\Gamma$ (poles and damping of the response set resonance and width); (b) independent broadenings combine by convolution: widths add for Lorentzians, variances add for Gaussians, and a Gaussian detector response of standard deviation $\sigma_d$ turns an intrinsic Gaussian $\sigma$ into $\sqrt{\sigma^2+\sigma_d^2}$; the Lorentzian–Gaussian (Voigt) width is computed and compared with a standard approximate formula (comparison formula only); (c) the harmonic content of the emission of a closed route is fixed by the route geometry: the dipole $x(t)$ of a circular route has only the fundamental, an eccentric route has harmonics with amplitudes $|x_n|=(a/n)\,|J_{n-1}(ne)-J_{n+1}(ne)|$; computed by integrating the route with the kernel of Chapter 17 ($p=2$) and Fourier analysis, with no selection table imported; (d) the recoil term of the event ledger $E_i-E_f=E_{\rm out}+T_{\rm recoil}+(\text{medium})$ for a hydrogen emission, where the recoil energy of the atom is exactly $\Delta E^2/(2M_ic^2)$, evaluated in a form free of cancellation. No measured line width or lifetime is loaded.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $J_0(0)=1$, $J_1(0)=0$, $J_0(2.404826)=0$ and $J_1(1.0)=0.4400505857$ by the integral representation $J_n(x)=\frac1\pi\int_0^\pi\cos(n\tau-x\sin\tau)\,d\tau$ | $10^{-8}$ ($10^{-6}$ for the zero) |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | with $\Gamma=1$, $\omega_0=0$: the numerical transform $\int_0^{T}e^{-t/2}e^{i\delta t}dt$ ($T=60$) equals $1/(\tfrac12-i\delta)$ at $\delta=0,\,0.3,\,1,\,3$; the half-maximum points of $|\hat A|^2$ found by bisection are $\delta=\pm\tfrac12$, i.e. FWHM $=\Gamma$ | $10^{-9}$ (transform), $10^{-8}$ (width) | yes |
| T2 | broadening. (a) Lorentzians $\Gamma_1=1$, $\Gamma_2=2$: their convolution evaluated at $x=0,1,3$ equals the Lorentzian of width $3$ within $2\times10^{-3}$ relative (range $\pm4000$ with tail correction not applied: the tail truncation is the stated error); (b) Gaussians $\sigma_1=1$, $\sigma_2=2$: convolution at $x=0,1,3$ equals the Gaussian of $\sigma=\sqrt5$ to $10^{-10}$; (c) an intrinsic Gaussian $\sigma=1$ seen through a detector $\sigma_d=0.5$: observed $\sigma=\sqrt{1.25}$ to $10^{-10}$; (d) the numerical Voigt FWHM for $\Gamma=1$, Gaussian FWHM $=1$ is printed with the approximate formula $0.5346\Gamma+\sqrt{0.2166\Gamma^2+f_G^2}$ and agrees with it within $0.5\%$ | as stated | yes |
| T3 | route geometry. Route integrated by RK4 for $a=-r^{-2}\hat r$, $\mu=1$, semi-major axis 1, period $2\pi$, 4096 samples per period: circular ($e=0$): $|x_2|,|x_3|\le10^{-9}|x_1|$; eccentric $e=0.51$ (apoapsis start, speed $\sqrt{2/(1+e)-1}$): $|x_n|$ for $n=1,2,3$ equal $(1/n)|J_{n-1}(ne)-J_{n+1}(ne)|$ to $10^{-6}$ relative. Printed: ratios $|x_2/x_1|$, $|x_3/x_1|$ | as stated | yes — a harmonic in the circular route, or a mismatch with the geometry rejects |
| T4 | recoil. For the hydrogen $1\to2$ transition (energy from `level_energy_eV(1,\cdot,m_p)`; $M_f=m_p+m_e$ for the ground state atom is taken as $m_p+m_e$ in the final state, $M_i=M_f+\Delta E/c^2$): the exact two-body ledger gives $E_\gamma=\Delta E(1-\Delta E/(2M_ic^2))$ and $T_{\rm recoil}=\Delta E^2/(2M_ic^2)$; the stable evaluation $T=E_\gamma^2/(\sqrt{M_f^2c^4+E_\gamma^2}+M_fc^2)$ equals it to $10^{-8}$ relative; $E_\gamma+T=\Delta E$ to $10^{-14}$ relative to $\Delta E$. Printed: $T_{\rm recoil}$ and $T/\Delta E$ | as stated | yes |

Reported, not criteria: the Voigt widths, recoil energies.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch28_emission_absorption_and_linewidth`
