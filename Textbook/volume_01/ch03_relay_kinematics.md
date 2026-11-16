# Chapter 3 — Relay Kinematics

*Volume I — Ontology, Geometry and Admissible States.*
Draft of 3 November 2026. Notation: $\mathrm{Om}=R/k^2$ is the circular c-boundary length, $k=c/v$ the speed ratio, $z=\mathrm{Om}/r$ the geometric depth and $z_{\rm spec}$ the spectral shift, as in the production default of `Textbook/NOTATION_LEDGER.md`. Executable companion: `Textbook/examples/ch03_relay_kinematics.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 3.1 The physical question

Chapter 1 gave the causal bound (1.3) in relay intervals and Chapter 2 gave the geometry. This chapter attaches counts to the geometry. How many relay intervals lie in a body, an orbit, a path? What do "speed" and "duration" mean when no clock is assumed? And how is a count made at one place compared with a count made at another?

## 3.2 Duration is an oscillator count

A detector adjacent to moving material contacts the leading edge at one place and finishes when the material leaves at another. The order of the contacts is the direction, fixed by the movement itself. The *duration* between the contacts is the number of cycles of a chosen oscillator in between. The rate of that oscillator against another is what is called time. A quartz crystal counts its vibrations per cycle of a driving voltage; the second is a count of the vibrations of a caesium transition. Nothing in this book needs a clock that is more than an oscillator, and ticks, layers and sweeps are counts of passes of a rule.

The oscillator the framework supplies is the relay itself. A relay interval is one pass of content from a cell to its neighbour. Its length is the cell edge $P_l=\ell_P$ and its duration is one count of the relay oscillator, $P_t$. The declared relay hop gives

$$c_{\rm relay}=\frac{P_l}{P_t}, \tag{3.1}$$

a length over a count of the oscillator that defines the hop. In the engine the constants are fixed by $c=\ell_P/t_P$ (axiom R2). Observables in this book are written as dimensionless ratios: counts per light-crossing, a speed over $c$, a rate over a rate. SI seconds appear only as a unit bridge, and are named as such.

## 3.3 Six speeds and one unit

Equality of different "speeds of light" must be shown. This book keeps six roles apart and gives each its own symbol when more than one is in play.

| role | definition | what fixes it |
|---|---|---|
| local relay speed | hop length over one local relay interval, $P_l/P_t$ | the local cell edge and local relay oscillator |
| phase speed | $\omega/\kappa$ for a wave branch $\omega(\kappa)$ | the medium's dispersion relation |
| group speed | $d\omega/d\kappa$ for a narrow packet on a differentiable branch | the same relation |
| front (signal) speed | the earliest controllable response across a path | the bound (1.3): at most one hop per relay interval |
| far-frame coordinate speed | path length over a count of a remote reference oscillator, $c_{\rm far}$ | the local closure and local oscillator rate along the path (Section 3.7) |
| present SI conversion | $c=299\,792\,458$ m/s | an exact unit bridge between two oscillators' counts |

Table 3.0. The speed roles. Cosmological boundary conditions carry an additional role identifier (Chapter 47).

For uniform nearest-neighbour relay with no back-scatter a pulse advances one hop per interval, and the local relay, phase, group and front speeds all equal the hop speed. They separate once the medium has a dispersion relation, and the relation $\omega(\kappa)$ of the real medium is open (residual R3.3; Chapter 14). A phase convention supplies no response law.

## 3.4 Counts: how many relay intervals

For a length $\Lambda$ in a uniform medium, the number of relay intervals light needs to cross it is $\Lambda/\ell_P$. Table 3.1 gives the counts that the later chapters use.

| length | hops $\Lambda/\ell_P$ |
|---|---|
| proton boundary $R_p$ | $5.2059\times10^{19}$ |
| hydrogen c-boundary $r_e=\alpha^2a_0$ | $1.7435\times10^{20}$ |
| Bohr radius $a_0$ | $3.2741\times10^{24}$ |
| one metre | $6.1871\times10^{34}$ |
| Earth radius | $3.9418\times10^{41}$ |
| Sun radius | $4.3044\times10^{43}$ |
| one astronomical unit | $9.2558\times10^{45}$ |
| $R_{\rm CMB}$ | $5.8945\times10^{61}=N$ |

Table 3.1. Hop counts, executed (labels: COMPUTED from MEASURED-INPUT lengths and the stored $\ell_P$; $N$ equals `law_I::N`, test T5).

The relay rate in SI is $c/\ell_P=1.854859\times10^{43}$ per SI second, a relay interval $5.391246\times10^{-44}$ SI seconds. These two numbers are unit bridges between the caesium oscillator and the relay oscillator; they enter no ratio in the book.

## 3.5 Recurrence counts

For a circular path of reach $r$ at speed $v$, the period and rate are $P_{\rm orb}=2\pi r/v$ and $\omega=v/r$, both with respect to a declared oscillator. In counts of the relay oscillator the number of relay intervals in one orbit is

$$n_{\rm orb}=\frac{P_{\rm orb}\,c}{\ell_P}=2\pi\,k\,\frac{r}{\ell_P}, \tag{3.2}$$

and the angle swept during one light-crossing of the reach is $\omega\,(r/c)=v/c=1/k$ radians. The second form of (3.2) uses only the ratio $k$ and the hop count of the reach.

| state | $k=c/v$ | relay intervals per orbit | rad per light-crossing of $r$ |
|---|---|---|---|
| hydrogen ground state ($r=a_0$, $v=\alpha c$) | $137.036$ | $2.819070\times10^{27}$ | $7.297353\times10^{-3}$ |
| Earth about the Sun ($r=1$ AU, $v=(c/k_\odot)\sqrt{R_\odot/r}$) | $10065.41$ | $5.853651\times10^{50}$ | $9.935016\times10^{-5}$ |

Table 3.2. Recurrence counts, executed (test T4; the two routes of (3.2) agree to $3\times10^{-16}$; the Earth row takes $k_\odot=686.404$ from Mercury's precession, so its $v$ is COMPUTED; $k_\odot$ carries the named input of the anomalous advance, a residual of ephemeris fits whose force model propagates light with $c$ (derivelist addendum of 2026-10-16), and the row is a recurrence count, not a test).

A continuous family of periods satisfies the kinematics. Discrete atomic states need a closure or stability condition that selects admissible recurrences; the shared circular law cannot supply discrete occupancy, transition rates or a nuclear lifetime (Chapters 26, 28 and 33).

## 3.6 Boundary circulation

For uniform tangential circulation at the boundary speed $c_{\rm b}$ around a circle of radius $\mathrm{Om}$,

$$\Gamma=\oint \vec v\cdot d\vec\ell=2\pi\,c_{\rm b}\,\mathrm{Om}. \tag{3.3}$$

$\Gamma$ has the dimension of an area per relay-count. Equation (3.3) is a definition for the stated geometry. A claim that $\Gamma$ is conserved under changes of the environment is a separate dynamical statement about traction, boundary work and transport, and the book does not rest on it (residual R3.4).

## 3.7 Local and remote counts

Two places at different depth do not count the same oscillator at the same rate. The engine collects the relations in one set (`depth_closure`, `laws.hpp:2790–2881`), with depth $z=\mathrm{Om}/r=1/k^2=(v/c)^2$:

$$\begin{aligned}
&\text{(1) local closure } &\ell(z)&=\ell_\infty(1-z),\\
&\text{(2) far-frame relay speed } &c_{\rm far}&=c_\infty(1-z)^2,\\
&\text{(3) local oscillator rate } &C(z)&=1-z,\\
&\text{(4) spectral shift } &z_{\rm spec}&=z_e-z_o .
\end{aligned} \tag{3.4}$$

Relation (2) is not independent of (1) and (3). A hop of local length $\ell_\infty(1-z)$ takes one local relay interval, and one local interval spans $1/(1-z)$ intervals of the remote reference oscillator, because the local oscillator runs at the fraction $1-z$ of the remote rate. The far-frame speed is therefore hop length over remote count,

$$c_{\rm far}=\frac{\ell_\infty(1-z)}{\tau_\infty/(1-z)}=c_\infty(1-z)^2, \tag{3.5}$$

one factor for the path length and one for the oscillator rate. The executed factorisation $c_{\rm far}=c\times(\text{closure factor})\times(\text{rate factor})$ held to the last digit for $z=0,0.1,\dots,0.9$, and the inverse `depth_from_c_far` returned $z$ to $2.8\times10^{-16}$ (test T1).

The domain is $0\le z\le1$. The rate $C=1-z$ vanishes at $z=1$, that is at $r=\mathrm{Om}$, where the circular speed of the shared law reaches $c$ (Chapter 2, Eq. 2.10).

**Status of the depth.** The set (3.4) takes the depth to be $z=\mathrm{Om}/r$, as the engine's convergence-depth block does (`laws.hpp:2797–2836`). The author ruled on 2026-11-03, for the clean-room model, that the relay slowing is not koppa over radius and that it must come out of the model; the engine text and CONDENSA line 71 are untouched. This chapter therefore uses $z=\mathrm{Om}/r$ only as the engine's stated value of the depth, to evaluate the engine's relations, and not as a derived property of the relay (residual R3.6). Where this book writes $z_{\rm depth}=\mathrm{Om}/r$ it means the defined geometric ratio of the notation ledger.

**The two spectral forms.** The count ratio of two oscillators over one sequence of contacts is $C_o/C_e$ when a wavefront passes from emitter to observer, so the ratio form of the shift is $1+z_{\rm spec}=C_o/C_e=(1-z_o)/(1-z_e)$. The engine records the first-order form (4), $z_{\rm spec}=z_e-z_o$. The two differ by an exact amount,

$$\frac{1-z_o}{1-z_e}-1-(z_e-z_o)=\frac{z_e\,(z_e-z_o)}{1-z_e}, \tag{3.6}$$

verified as an identity of rationals for five cases from $z_e=3/10$ to $z_e=10^{-6}$ (test T2). For $z_o=z_e/3$ the difference divided by $z_e^2$ tends to $2/3$; at the depth of the solar surface the two forms agree to a relative $2\times10^{-6}$. Chapter 45 takes up which form the data fix.

For the Sun the engine's depth is $z_\odot=\mathrm{Om}_\odot/R_\odot=2.123108\times10^{-6}$ and the depth at 1 AU is $9.873442\times10^{-9}$, so the shift from a line emitted at the solar surface and observed at 1 AU is $z_e-z_o=2.113234\times10^{-6}$ (COMPUTED; Table 3.3). The comparison with a measured shift is not made here: the measured solar shift is limited by convective blueshift, and the comparison is registered in Chapter 45 before the measured value is loaded.

| place | depth $z=\mathrm{Om}/r$ |
|---|---|
| Sun, surface ($\mathrm{Om}_\odot/R_\odot$; `depth_closure::z_spectral_Sun`) | $2.123108\times10^{-6}$ |
| Sun, at 1 AU | $9.873442\times10^{-9}$ |
| $z_e-z_o$, Sun surface to 1 AU | $2.113234\times10^{-6}$ |
| hydrogen at $a_0$ ($\mathrm{Om}_H/a_0=\alpha^2$) | $5.325135\times10^{-5}$ |
| hydrogen at $r=\mathrm{Om}_H=r_e$ | $1$ |

Table 3.3. Depths, executed.

## 3.8 The integrated relay-speed deficit

A signal sent along a straight path through a depth profile reaches the receiver late, in counts of a remote oscillator, by the integrated difference between the reciprocal far-frame speed and the reciprocal of $c$. From (3.4),

$$\frac1{c_{\rm far}}-\frac1c=\frac{1}{c}\,\frac{z(2-z)}{(1-z)^2}=\frac{2z+3z^2+4z^3+\cdots}{c}. \tag{3.7}$$

The series was checked against direct evaluation at $z=10^{-3}$ to $3\times10^{-12}$ (test V2). With $z=\mathrm{Om}/r$ along a ray of impact parameter $b$, where $r^2=l^2+b^2$, the first-order integral is

$$\Delta=\frac{2\,\mathrm{Om}}{c}\int_{-l_1}^{l_2}\frac{dl}{\sqrt{l^2+b^2}}=\frac{2\,\mathrm{Om}}{c}\Big[\operatorname{asinh}\frac{l_1}{b}+\operatorname{asinh}\frac{l_2}{b}\Big]\approx\frac{2\,\mathrm{Om}}{c}\ln\frac{4r_1r_2}{b^2}, \tag{3.8}$$

with $l_i=\sqrt{r_i^2-b^2}$. The factor 2 is the coefficient of $z$ in (3.7); it comes from the two closure factors of (3.5) and is not inserted separately. The engine's `shapiro_delay` is the last form.

Executed for a ray from 1 AU to 1.523679 AU grazing the solar limb ($b=R_\odot$; $\mathrm{Om}_\odot=1477.046$ m): the engine's logarithmic form gives $1.236552\times10^{-4}$ SI seconds one way, an excess path of $37.07$ km or $2.2936\times10^{39}$ relay intervals. It agrees with the inverse-hyperbolic form to a relative $6.2\times10^{-7}$ and with the quadrature of the exact integrand (3.7) along the ray to $1.8\times10^{-7}$ (test T3; the quadrature used the substitution $l=b\sinh u$, validated on a known integral in V1). The quantities (3.8) and the comparison with the measured delay are the subject of Chapter 39; this chapter records only that the first-order coefficient follows from (3.4) and that the logarithmic form is an accurate evaluation of it for this geometry.

## 3.9 Input ledger and residuals

| quantity | role | label |
|---|---|---|
| $\ell_P$ | cell edge | CALIBRATED(1) as a stored number: the CODATA Planck length, whose definition carries $G$ numerically (`laws.hpp:111–119`) |
| $c$ | unit bridge | MEASURED-INPUT (SI exact) |
| $a_0$, $\alpha$, $r_e$ | hydrogen scales | MEASURED-INPUT (CODATA) |
| $R_\odot$, 1 AU | lengths | MEASURED-INPUT (IAU 2015, IAU 2012) |
| $k_\odot=686.404$ | speed ratio of the Sun | CONSTRUCTION with respect to $c$: contaminating input: the anomalous advance $\delta\phi$ of Mercury, a residual of ephemeris fits whose force model uses $c$, entering through `bridge::k_Sun_from_precession`; $\mathrm{Om}_\odot$ in T3 and Table 3.3 uses the engine's `bridge::koppa_Sun` with $k_\odot=686.3$ |
| closures (1) and (3) of (3.4) | posited relations | the exponent of $1-z$ was set by GOM22 so that the first-order redshift and Shapiro coefficient agree with measured values: contaminating input: measured solar spectral shift and first-order Shapiro coefficient, entering at `laws.hpp:2855–2857` |
| hop counts, recurrence counts | tables | COMPUTED |

**Residuals.**

* **R3.1 — the exponents.** The power of $1-z$ in the oscillator rate and in the closure is set to reproduce measured first-order coefficients (GOM22). A derivation from the contact mechanics is outstanding, and until it exists relations (3.4) are constrained by those measurements and do not predict them.
* **R3.2 — supersession.** `Theory/00_Ruleset.md` lists T16 as $d\tau/dt=\sqrt{1-zR/r}$. The engine's active relation is $C=1-z$ (GOM22: the earlier form gave half the solar shift). The Ruleset text has not been updated, and the canon is edited only on the author's approval; the discrepancy is recorded here and in the supersession ledger.
* **R3.3 — dispersion.** The medium's $\omega(\kappa)$, and with it the separation of phase, group and front speeds, is open (Chapter 14).
* **R3.4 — circulation.** Conservation of $\Gamma$ in (3.3) is not established.
* **R3.5 — the second-order fork.** The engine carries $c_{\rm far}=c(1-z)^2$ and the shared form $c(1-2z)$ as the two candidates; they agree to first order and differ at second order and in where the speed vanishes (Chapter 40).
* **R3.6 — the identification $z=\mathrm{Om}/r$.** The engine's convergence-depth block and CONDENSA line 71 set the relay slowing equal to koppa over radius. The author ruled on 2026-11-03 that this is an error to be removed and that $z(r)$ must come out of the model. The canon is edited only on the author's approval, so the engine values (Table 3.3, Section 3.8) are reported as the engine's, not as derived; every later chapter that uses the engine's depth carries this label.

## 3.10 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch03_relay_kinematics
```

Criteria were registered in `Textbook/validation/ch03_PRE_REGISTRATION.md` before the instrument existed. Two corrections were made before and after the first run and are recorded there. Test T2 was changed to exact rational arithmetic before run 1, because a double-precision evaluation of a quantity of order $z_e^2$ cancels. Run 1 (`ch03_run1_output.txt`) failed instrument validation V1 at $L/b=3\times10^4$ (a uniform-panel rule cannot resolve a kernel of width $b$ over that range); the test was repaired to validate the substituted-variable rule that T3 uses, and the T-results of run 1 were not quoted. Run 2 (`ch03_run2_output.txt`) met every criterion.

## 3.11 Exercises and answers

**Exercise 1.** How many relay intervals does light need to cross the Bohr radius?

*Answer.* $a_0/\ell_P=5.29177\times10^{-11}/1.616255\times10^{-35}=3.274\times10^{24}$.

**Exercise 2.** Show that the angle swept in one light-crossing of the reach of a circular state is $v/c$.

*Answer.* The crossing takes $r/c$ of any oscillator; the rate is $v/r$. The angle is $(v/r)(r/c)=v/c=1/k$.

**Exercise 3.** Evaluate the closure factor, the rate factor and the far-frame speed at $z=1/2$.

*Answer.* $1-z=\tfrac12$ for each, so $c_{\rm far}=c/4$.

**Exercise 4.** Show (3.6).

*Answer.* $\dfrac{1-z_o}{1-z_e}-1=\dfrac{z_e-z_o}{1-z_e}$. Subtract $z_e-z_o$: $(z_e-z_o)\Big[\dfrac{1}{1-z_e}-1\Big]=\dfrac{z_e(z_e-z_o)}{1-z_e}$.

**Exercise 5.** Obtain the logarithmic form of (3.8) from the inverse-hyperbolic form for $r_i\gg b$.

*Answer.* $\operatorname{asinh}x=\ln(x+\sqrt{x^2+1})\to\ln 2x$ for $x\gg1$, and $l_i\to r_i$, so the sum is $\ln(2r_1/b)+\ln(2r_2/b)=\ln(4r_1r_2/b^2)$.

**Exercise 6.** Two oscillators over the same sequence of contacts count $N_e$ and $N_o$. In terms of $z_e,z_o$, what is $N_o/N_e$?

*Answer.* Rates are proportional to $1-z$ for the local oscillator, so $N_o/N_e=C_o/C_e=(1-z_o)/(1-z_e)$ (the ratio form of $1+z_{\rm spec}$).

## 3.12 Scope

Established in this chapter: duration as an oscillator count and the six speed roles; the hop counts of bodies and orbits and the recurrence counts of two circular states; the factorisation of the far-frame relay speed into a closure factor and a rate factor; the exact difference of the two spectral forms; and that the first-order relay-speed deficit follows from the closure relations, with an accurate closed form for a grazing ray (executed).

Not established: the exponent of the closure and the rate (R3.1), the medium's dispersion (R3.3), the conservation of circulation (R3.4), and the comparison of any of these with a measured spectral shift or delay, which Chapters 39 and 45 register before loading the data.

*Where it leads.* Chapter 13 gives the movement budget behind the circular law. Chapter 14 takes the dispersion relation. Chapter 33 uses the recurrence counts and Chapter 45 the two spectral forms.
