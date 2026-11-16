# Chapter 28 — Emission, Absorption and Linewidth

*Volume IV — Atomic Recurrence, Spectra and Material Organisation.*
Draft of 10 November 2026. Notation: $\Gamma$ is the full width at half maximum of a power line in angular-frequency units; $A(t)$ the amplitude of a causal response. Durations are counts of a declared oscillator, with the time variable of the response kernel a count measure. Executable companion: `Textbook/examples/ch28_emission_absorption_and_linewidth.cpp`; pre-registration and captured output in `Textbook/validation/`. No measured width or lifetime is loaded.

## 28.1 The physical question

A transition changes the stored circulation and launches an outgoing disturbance through contiguous contact. The questions are what fixes the energy of the line, what fixes its width, what fixes the harmonic content and direction of the emission, and what of the event ledger is recoil and medium reorganisation. A frequency match fixes an allowed energy channel; an event rate needs a coupling strength and the density of outgoing modes. A linewidth cannot be obtained by replacing an energy difference with a wavelength.

## 28.2 Emission as outgoing relay excitation

The event ledger is

$$E_{\rm initial}-E_{\rm final}=E_{\rm out}+T_{\rm recoil}+E_{\rm medium}. \tag{28.1}$$

A linear response is represented by a causal kernel $\chi(t)$ that vanishes for negative delay. A monochromatic perturbation produces an amplitude proportional to $\chi(\omega)$; the poles and damping of the response determine the resonant frequency and the width. The simplest case is an amplitude $A(t)=\theta(t)e^{-\Gamma t/2}e^{-i\omega_0t}$, whose transform is

$$\hat A(\omega)=\frac1{\Gamma/2-i(\omega-\omega_0)},\qquad |\hat A|^2=\frac1{(\Gamma/2)^2+(\omega-\omega_0)^2}, \tag{28.2}$$

a line centred at $\omega_0$ of full width $\Gamma$ at half maximum. **Executed (T1).** With $\Gamma=1$ the numerically integrated transform over $0\le t\le60$ equalled (28.2) to $1.9\times10^{-13}$ at the offsets $0,0.3,1,3$, and the half-maximum points of $|\hat A|^2$, found by bisection, were at $\pm0.5$ to $10^{-8}$: width $=\Gamma$. The width is the decay rate of the response; it is not a function of the line energy.

## 28.3 Selection and the harmonic content of a route

Transition selection depends on the symmetry of the initial mode, the perturbing operator and the final mode. A vanishing overlap can suppress a leading channel while a higher-order channel remains. The overlap has to be derived for the actual circulation geometry; a borrowed selection table may serve as a comparison dataset and does not replace that operator.

A geometric instance that needs no table is the harmonic content of the emission of a closed route. A dipole moment that follows a circular route is a pure fundamental. For an eccentric route under the $1/r^2$ kernel (Chapter 17, $p=2$), the Fourier amplitudes of the coordinate $x(t)$ along the major axis are $|x_n|=(a/n)\,|J_{n-1}(ne)-J_{n+1}(ne)|$ for eccentricity $e$.

**Executed (T3).** The route was integrated by RK4 ($\mu=1$, semi-major axis 1, 4096 samples per period) and Fourier-analysed. For $e=0$ the harmonics $|x_2|,|x_3|$ were at most $6\times10^{-15}$ of $|x_1|$. For $e=0.51$ (apoapsis start) the amplitudes of the first three harmonics equalled the expression above, with the Bessel functions evaluated from their integral representation (checked at $J_0(0)=1$, $J_1(0)=0$, $J_0(2.404826)\approx0$, $J_1(1)=0.4400505857$), to $4.2\times10^{-14}$; the ratios are $|x_2/x_1|=0.235443$ and $|x_3/x_1|=0.083634$. The route geometry sets which harmonics are emitted and how strongly. This is the classical harmonic content of a route and a correspondence for the later quantised ladder, not a derivation of a selection rule for it (residual R28.1).

## 28.4 Coherence and re-emission

Emission, absorption and scattering need not erase phase memory equally. The release cascade of Law II distinguishes faithful relay from material interception. A material re-emission event can reset frequency or direction according to the local state; uninterrupted propagation follows the applicable recurrence transport. A scattered line and a re-emitted line are not the same observable, and the line profile alone does not say which it is.

## 28.5 Broadening

Population decay, collisions, ensemble motion and inhomogeneous medium state produce different profiles. Convolution is justified only for statistically independent broadenings in the chosen representation. **Executed (T2).** The convolution of Lorentzians of widths $1$ and $2$ equalled the Lorentzian of width $3$ to $1.2\times10^{-11}$ at the points $x=0,1,3$ (range $\pm4000$); the convolution of Gaussians of standard deviations $1$ and $2$ equalled the Gaussian of $\sqrt5$ to $2.4\times10^{-15}$; an intrinsic Gaussian of $\sigma=1$ seen through a detector of $\sigma_d=0.5$ is observed as $\sqrt{1.25}=1.118034$. Lorentzian widths add; Gaussian variances add; a detector's finite response has to be included before an intrinsic width is compared with a recorded line. The Lorentzian–Gaussian combination has no closed width: for $\Gamma=1$ and a Gaussian of FWHM 1 the numerical FWHM is $1.63760$, which agrees with the approximate formula $0.5346\,\Gamma+\sqrt{0.2166\,\Gamma^2+f_G^2}$ ($1.63760$; difference $3\times10^{-7}$) used here as a comparison formula only. If two broadenings are correlated (for example collisions that depend on the same motion that produces the Doppler spread), the convolution is not justified and the joint distribution is needed.

## 28.6 Recoil

The recoil term of (28.1) is fixed by energy and momentum. For an atom of final mass $M_f$ emitting an energy $E_\gamma$ with initial mass $M_i=M_f+\Delta E/c^2$, the exact two-body ledger gives $E_\gamma=\Delta E\,(1-\Delta E/(2M_ic^2))$ and

$$T_{\rm recoil}=\frac{\Delta E^2}{2M_ic^2}. \tag{28.3}$$

**Executed (T4).** For hydrogen $1\to2$, $\Delta E=10.198715$ eV (from `level_energy_eV` with the proton mass), $T_{\rm recoil}=5.5398\times10^{-8}$ eV ($T/\Delta E=5.4\times10^{-9}$), evaluated as $E_\gamma^2/(\sqrt{M_f^2c^4+E_\gamma^2}+M_fc^2)$, a form without cancellation (the direct difference of total and rest energy, $\sim10^{-8}$ of $10^{9}$ eV, is below double-precision resolution). It equals (28.3) to $1.1\times10^{-16}$, and $E_\gamma+T_{\rm recoil}=\Delta E$ to $10^{-14}$ of $\Delta E$. The medium term of (28.1) is zero in this ledger, a decision of the isolated-region ledger (Chapter 15, R15.2).

## 28.7 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| (28.2) and the width statement | Section 28.2 | DERIVED (exact), checked numerically |
| harmonic content, route geometry | Section 28.3 | DERIVED and COMPUTED (classical route under the $1/r^2$ kernel) |
| broadening combination rules | Section 28.5 | DERIVED (exact), checked numerically |
| $\Delta E$ for hydrogen $1\to2$ | from `level_energy_eV` | COMPUTED from the stored $\mathrm{Ry}$, masses |
| (28.3) | Section 28.6 | DERIVED (exact) |
| Voigt approximate formula | comparison only | not an input |

**Residuals.**

* **R28.1 — selection and coupling.** The overlap and coupling strength of the real circulation, the density of outgoing modes and so the rate of a transition are not derived; the harmonic content above is a classical route property.
* **R28.2 — the response kernel.** The causal kernel of the real atom (poles, damping) is not supplied; $\Gamma$ is a parameter here.
* **R28.3 — the medium term.** Reorganisation of the medium in an emission is set to zero in the ledger.
* **R28.4 — measured widths.** No measured width, lifetime or angular distribution is loaded; the determining test needs line centres, widths, angular emission and excitation dependence from one mode coupling, with instrument broadening specified separately.

## 28.8 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch28_emission_absorption_and_linewidth
```

Criteria were registered in `Textbook/validation/ch28_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch28_run1_output.txt`) is the run of record and met every criterion.

## 28.9 Exercises and answers

**Exercise 1.** Derive (28.2).

*Answer.* $\int_0^\infty e^{-\Gamma t/2}e^{i(\omega-\omega_0)t}dt=1/(\Gamma/2-i(\omega-\omega_0))$.

**Exercise 2.** Why is the full width at half maximum $\Gamma$?

*Answer.* $|\hat A|^2$ falls to half its peak $4/\Gamma^2$ when $(\omega-\omega_0)^2=(\Gamma/2)^2$, at $\pm\Gamma/2$.

**Exercise 3.** Show that Lorentzian widths add under convolution.

*Answer.* The transform of a Lorentzian of width $\Gamma$ is $e^{-\Gamma|t|/2}$; a product of two such is $e^{-(\Gamma_1+\Gamma_2)|t|/2}$.

**Exercise 4.** What is the first-order estimate of $|x_2/x_1|$ for small $e$?

*Answer.* $|x_2|\approx(1/2)|J_1(2e)|\approx e/2$ and $|x_1|\approx1$, so the ratio is about $e/2$ ($0.255$ at $e=0.51$ against the exact $0.2354$).

**Exercise 5.** Why does a circular route emit only a fundamental?

*Answer.* Its coordinate is $r\cos\omega t$.

**Exercise 6.** Evaluate $T_{\rm recoil}$ for $\Delta E=10.2$ eV and $M_i=938.8$ MeV.

*Answer.* $(10.2)^2/(2\times938.8\times10^6)=5.54\times10^{-8}$ eV.

## 28.10 Scope

Established: the width as the decay rate of a causal response, with the line (28.2); that harmonic content of a closed route is set by its geometry, with the circular route a pure fundamental and the eccentric route's harmonics given by the Bessel expression, executed; the combination rules of independent broadenings and the need to include the detector; and the exact recoil term (28.3).

Not established: selection and coupling for the real circulation (R28.1), its response kernel (R28.2), the medium term (R28.3) and any measured width (R28.4).

*Where it leads.* Chapter 29 treats the many-electron atom: occupancy, occlusion, ionisation and periodic structure from one pair law.
