# Chapter 45 — Pressure-Origin Redshift

*Volume VI — Sz, Pressure History and Coupled Ratios.*
Draft of 10 November 2026. Notation: $z_e$, $z_o$ the depths $\mathrm{Om}/r$ at emitter and observer (a defined geometric ratio; the identification with a pressure or a slowing is not made here); $C=1-z$ the tick-rate ratio of `depth_closure::clock_rate`; $z_A=z_e-z_o$ the engine's `z_spectral`; $z_B$ the tick-rate-ratio form (45.1). Executable companion: `Textbook/examples/ch45_pressure_origin_redshift.cpp`; pre-registration and captured output in `Textbook/validation/`. No measured shift is read. The solar constants $R_\odot$ and AU (IAU) and the engine's `bridge::koppa_Sun` are used for one matched example.

## 45.1 Emitter, route and observer

Define the measured spectral shift as $z_{\rm spec}=\lambda_{\rm obs}/\lambda_{\rm reference}-1$, where the reference transition is specified in the observer's local state. Four entries are kept apart: the source recurrence, the transported recurrence count, the route, and the detector response. A pressure-dependent relay medium can change the emitter's and the observer's rulers without a cumulative wavelength loss along an unobstructed path. The recovered CR07 branch preserves the transported count, so that static endpoint transformations telescope; absorption and material re-emission are separate events with new boundary conditions; a path-integrated compounding strain law cannot be added to that branch without changing its premise.

**Count bookkeeping (T4).** An emitter with local frequency $f_e$ puts $N=f_eC_e\Delta t$ cycles into a remote window $\Delta t$. An observer who counts those $N$ cycles in their own duration $C_o\Delta t$ has $f_o=N/(C_o\Delta t)$, so $f_e/f_o=C_o/C_e$. Executed with $f_e=5\times10^{14}$ Hz and $\Delta t=10^{-9}$ s, the identity holds to the arithmetic floor. A deeper emitter ($z_e>z_o$) gives a positive shift and a shallower one gives a negative shift, both registered and met.

## 45.2 Two conventions for the depth comparison

The engine's $z_{\rm spec}=z_e-z_o$ is convention A. The tick-rate ratio gives convention B,

$$1+z_{\rm spec}=\frac{C_o}{C_e}=\frac{1-z_o}{1-z_e},\qquad z_B=\frac{z_e-z_o}{1-z_e}. \tag{45.1}$$

Both are conditional on the frequency and tick-rate transport convention that has been specified; the executed tests establish how they differ, not which one the mechanism requires.

**Difference (T1).** The ratio is exact and does not depend on the observer: $z_B/z_A=1/(1-z_e)$. It was tested over $z_e\in\{10^{-6},10^{-3},0.1,0.3,0.9\}$ and $z_o\in\{0,z_e/2\}$. At the solar surface $z_e=2.123108\times10^{-6}$ the two conventions differ by $2.123112\times10^{-6}$ of the shift (an absolute difference of $4.5\times10^{-12}$ in $z$); at $z_e=0.3$ they differ by $42.9$ per cent; at $z_e\approx0.0099$ they differ by 1 per cent. They agree to first order and part at second.

**Composition (T2).** For states $A,B,C$ with depths $(0.30,0.12,0.02)$ and $z_{XY}$ the shift from emitter $X$ to observer $Y$:

| | convention A | convention B |
|---|---|---|
| additive: $z_{AB}+z_{BC}-z_{AC}$ | $0$ | $-0.02922078$ |
| multiplicative: $(1+z_{AB})(1+z_{BC})-(1+z_{AC})$ | $0.018=z_{AB}z_{BC}$ | $0$ |

Convention B composes multiplicatively and convention A additively. The CR07 branch (octaves, $1+z=2^{\Delta n}$) composes multiplicatively, so (45.1) is the form that is consistent with that premise; convention A would need a different composition law. This is a consistency statement. It does not settle the transport convention, which a derivation from the contact mechanism has to fix (R45.2).

**First-order agreement (T3).** Scaling the depths $(0.1,0.03)$ by $s=10^{-3},10^{-2},10^{-1}$ gives relative differences $1.0001\times10^{-4}$, $1.0010\times10^{-3}$, $1.0101\times10^{-2}$, a log-log slope of $1.0022$ (registered between $0.99$ and $1.02$); the difference is first order in the depth of the emitter.

**Strong depth (T5).** Convention A is bounded by 1 for $z_e\le1$. Convention B increases without limit ($z_B(0.999,0)=999$). The two disagree most where the depth is largest, and the engine's `clock_rate` is defined for $0\le z\le1$ only.

## 45.3 One matched experiment

The emitter is the solar surface, $z_e=\varpi_\odot/R_\odot=2.123107587\times10^{-6}$ with $\varpi_\odot$ the engine's `bridge::koppa_Sun`; the observer is at 1 AU, $z_o=\varpi_\odot/\mathrm{AU}=9.873442\times10^{-9}$. Computed before any measured shift was consulted, the velocity equivalents $c\,z_{\rm spec}$ are

* convention A: $633.531658$ m/s,
* convention B: $633.533004$ m/s,

a difference of $1.345\times10^{-3}$ m/s ($2.123\times10^{-6}$ of the shift; predicted in the registration as about $1.35\times10^{-3}$ m/s and met). The conventions are indistinguishable by any solar-line measurement. They separate only where $z_e$ reaches the per-cent level (45.2).

## 45.4 Pressure is not a unique scalar proxy

The map $z_{\rm depth}=\mathrm{Om}/r$ is geometric. Identifying depth with $\Delta\sigma_{rr}/P_{\rm ambient}$ needs a constitutive derivation (Chapter 43), and equal temperatures do not guarantee equal directional stress. This chapter treats $z$ as the defined ratio only and does not compute a pressure.

## 45.5 Numerical note

Forming $z_B$ as $(C_o/C_e)-1$ subtracts 1 from a number within $10^{-6}$ of 1 at the solar depth and loses about ten digits (run 1 of the instrument; recorded in the pre-registration). The difference form $(z_e-z_o)/(1-z_e)$ is stable and was used for the run of record.

## 45.6 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| depths $z_e$, $z_o$ | defined ratios $\mathrm{Om}/r$ | CONSTRUCTION (defined geometric ratio) |
| $\varpi_\odot$ (`koppa_Sun`) | `bridge` | MEASURED-INPUT (stored: $R_\odot/k_\odot^2$ with the four-digit speed ratio $k_\odot=686.3$, scaled from planetary orbital speeds; neither $G$, a mass nor the stored $\ell_P$ enters; Chapter 39 ledger) |
| $R_\odot$, AU | `measured` | IAU values |
| $C=1-z$ | `clock_rate` | the engine's tick-rate ratio (GOM22) |
| (45.1) and the two shifts | Section 45.2 | COMPUTED |

**Residuals.**

* **R45.1 — the depth to pressure map.** No constitutive relation between $\mathrm{Om}/r$ and a pressure or stress is derived.
* **R45.2 — the transport convention.** Whether the shift is (A), (B) or another function of $(z_e,z_o)$ is not derived; the composition test favours (B) for consistency with the multiplicative CR07 premise and does not decide the mechanism.
* **R45.3 — the route.** No route term is computed; the CR07 branch sets it to zero for an unobstructed static path and absorption/re-emission paths were not examined.
* **R45.4 — observer reference.** The reference transition in the observer's local state, and the detector response, are specified but not computed.
* **R45.5 — engine comment (proposal to the author, canon untouched).** The comment on `z_spectral` states the gravitational redshift as $z_e-z_o$; the second-order difference from (45.1) is not recorded there.

## 45.7 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch45_pressure_origin_redshift
```

Criteria were registered in `Textbook/validation/ch45_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch45_run1_output.txt`) failed four criteria through cancellation: the product form of $z_B$ lost digits at shallow depth, and two registered quantities were differences of near-equal numbers whose floating-point floor exceeds the registered $10^{-12}$ (a registration error). Both are recorded in the pre-registration; the criteria were evaluated in their equivalent cancellation-free forms and not retuned. Run 2 (`ch45_run2_output.txt`) is the run of record and met every criterion.

## 45.8 Exercises and answers

**Exercise 1.** A neutron-star-like depth $z_e=0.2$ observed from $z_o=0$: what are $z_A$ and $z_B$?

*Answer.* $z_A=0.2$; $z_B=0.2/0.8=0.25$.

**Exercise 2.** Show that $z_B/z_A=1/(1-z_e)$ for any observer depth.

*Answer.* $z_B=(z_e-z_o)/(1-z_e)$ and $z_A=z_e-z_o$; the observer depth cancels.

**Exercise 3.** Why does (45.1) compose multiplicatively?

*Answer.* $(1+z_{AB})(1+z_{BC})=\dfrac{C_B}{C_A}\dfrac{C_C}{C_B}=\dfrac{C_C}{C_A}=1+z_{AC}$.

**Exercise 4.** Find $z_e$ at which the two conventions differ by 1 per cent.

*Answer.* $z_e/(1-z_e)=0.01$ gives $z_e=0.01/1.01=0.0099$.

**Exercise 5.** Why does the product form lose digits for the Sun?

*Answer.* $(1-z_o)/(1-z_e)$ differs from 1 by about $2\times10^{-6}$; subtracting 1 from a double-precision number near 1 leaves about $10^{-16}/2\times10^{-6}\approx5\times10^{-11}$ relative accuracy.

**Exercise 6.** What bounds $z_B$ for a deeper emitter?

*Answer.* Nothing in (45.1): $z_B\to\infty$ as $z_e\to1$; the domain of the engine's tick-rate function is $0\le z\le1$.

## 45.9 Scope

Established: the count bookkeeping and sign of the shift; the exact ratio of the two conventions, $1/(1-z_e)$; their first-order agreement and second-order difference; that (45.1) composes multiplicatively and the engine's difference form additively; the solar example in both conventions, differing by $1.3\times10^{-3}$ m/s.

Not established: which convention the mechanism gives (R45.2), the depth to pressure map (R45.1), a route term (R45.3), the observer reference and detector response (R45.4).

*Where it leads.* Chapter 46 asks when the hydrogen boundary ratio $\mathrm{Om}_H/R_p$ reaches the proton boundary.
