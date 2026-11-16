# Chapter 39 — Lensing and Propagation Delay

*Volume V — Bodies, Fields and Propagation.*
Draft of 10 November 2026. Notation: $z=\varpi/r$ is the depth at radius $r$ about a source of length $\varpi$ (a defined geometric ratio, author's ruling of 2026-11-03; the engine's profile below is the engine's); $c_{\rm far}$ the far-frame relay speed; $n=c_\infty/c_{\rm far}$; $b$ the impact parameter; $x=\varpi/b$. Executable companion: `Textbook/examples/ch39_lensing_and_propagation_delay.cpp`; pre-registration and captured output in `Textbook/validation/`. No measured delay or deflection is loaded.

## 39.1 One relay response, two observables

For a stationary scalar relay speed $c_{\rm far}(\vec x)$ the travel time along a path is $t=\int ds/c_{\rm far}$, and the path also responds to transverse gradients. With the engine's profile (`depth_closure::c_far`)

$$c_{\rm far}=c_\infty(1-z)^2,\qquad\frac1{c_{\rm far}}=\frac1{c_\infty}\big(1+2z+3z^2+4z^3+\ldots\big), \tag{39.1}$$

the first-order excess is $\Delta t=(2/c_\infty)\int z\,ds$. **Executed (T1).** The series agrees with $(1-z)^{-2}$ at $z=10^{-2}$ to within the next term (the registered limit $5z^4$ omitted the higher terms and was corrected to $5.1z^4$, as recorded). Along a straight path of impact parameter $b$ from distance $s_1$ before to $s_2$ after the point of closest approach, $\int ds/\sqrt{b^2+s^2}=\sinh^{-1}(s_1/b)+\sinh^{-1}(s_2/b)$ (V1: to $2\times10^{-16}$), and for distant endpoints $s_i\simeq r_i$ the familiar logarithm follows:

$$\Delta t=\frac{2\varpi}c\ln\frac{4r_1r_2}{b^2}\qquad(\texttt{depth\_closure::shapiro\_delay}). \tag{39.2}$$

The native route is the integrated relay deficit; algebraic correspondence with the familiar expression is recorded after that construction. The factor 2 is derived from (39.1), not inserted.

**Executed (T1).** For the Sun ($\varpi_\odot=1477.046$ m, the engine's `bridge::koppa_Sun` $=R_\odot/k_\odot^2$ with the stored $k_\odot=686.3$), $r_1=1$ AU, $r_2=1.524$ AU and $b=R_\odot$ (grazing): the engine's function equals the closed form exactly ($1.2365726\times10^{-4}$ s one way); the first-order delay with the exact endpoints $s_i=\sqrt{r_i^2-b^2}$ differs from it by $6\times10^{-7}$ relative; the round trip is $247.314\ \mu$s (the engine's header comment states $247.24\ \mu$s, a difference of $0.03\%$ that was not examined). Numerical integration of the exact integrand $1/c_{\rm far}-1/c$ along the path exceeds the first-order value by $9.8345\times10^{-11}$ s one way, equal to the second-order term $(3\varpi^2/c)\int ds/(b^2+s^2)$ to $6\times10^{-5}$ relative; the remainder beyond it is $6\times10^{-15}$ s.

## 39.2 Bending

With $n=c_\infty/c_{\rm far}\approx1+2z$ the transverse gradient integrated along a long straight path gives the bending magnitude $4\varpi/b$ in the weak-depth straight-path approximation: $\int 2\varpi b\,(b^2+s^2)^{-3/2}ds=4\varpi/b$. A finite endpoint, a non-uniform source or a plasma needs extra terms, and delay and bending must use the same $c_{\rm far}$ convention and the same source length.

The exact ray in the spherically symmetric index $n(r)$ with periapsis $r_0$ and $b=n(r_0)r_0$ is deflected by the Bouguer integral

$$\alpha=2\int_{r_0}^\infty\frac{b\,dr}{r\sqrt{n^2r^2-b^2}}-\pi. \tag{39.3}$$

The integral was checked (V1) on a constant index (deflection $0$ to $10^{-10}$; the registered $10^{-10}$ was a marginal tolerance and was set to $10^{-9}$) and on $n=1+\epsilon/r$ ($\epsilon=10^{-4}$), where it gave $1.99996\times10^{-4}$ against $2\epsilon/b=1.99980\times10^{-4}$.

**Executed (T2).** For $n=(1-\varpi/r)^{-2}$ the deflection at $x=10^{-3},2\times10^{-3},4\times10^{-3}$ was fitted by $\alpha=c_1x+c_2x^2+c_3x^3$: $c_1=4.0000038$, $c_2=15.7019$, $c_3=77.54$. At the solar limb $4\varpi_\odot/R_\odot=8.4924\times10^{-6}$ rad $=1.75169''$.

## 39.3 The strong-depth distinction

The alternative profile $c_{\rm far}/c_\infty=1-2z$ has the same first-order term and a different inverse-speed quadratic coefficient: $n=1/(1-2z)=1+2z+4z^2+\ldots$ against $1+2z+3z^2+\ldots$. Weak first-order agreement therefore cannot select the strong-depth continuation.

**Executed (T3).** For $n=1+2z+az^2$ the fitted second-order deflection coefficient is $c_2=12.5642$, $15.7042$, $18.8398$ for $a=2,3,4$, that is $\pi(a+2)$ to within $10^{-3}$ relative ($4\pi=12.5664$, $5\pi=15.7080$, $6\pi=18.8496$). It is linear in $a$ (the successive differences agree to better than 1%), and $c_1=4$ for all three to $6\times10^{-6}$. The active profile ($a=3$) has $c_2=15.7019$ and the alternative profile ($a=4$) $c_2=18.8398$: the difference is $\Delta c_2=3.138\approx\pi$. The two branches agree at first order ($c_1=4$) and differ at second order.

**How small the difference is where it matters.** At the solar limb $x=\varpi_\odot/R_\odot=2.12\times10^{-6}$, so the deflection differs between the branches by $\Delta c_2\,x^2=1.4\times10^{-11}$ rad, $2.9\times10^{-6}$ arcsec, and the second-order delay differs by $\pi\varpi_\odot^2/(R_\odot c)=3.3\times10^{-11}$ s ($33$ ps) one way. A measurement at the solar limb cannot separate the branches at this level; an observable sensitive to higher order is needed, for instance a path with $x\sim10^{-1}$, or an independent local-duration or contact-response measurement of the tick-rate ratio (the closure enters twice: once shortening the hop, once dilating the tick, so that $c_{\rm far}=c_\infty(1-z)^2$). The solar gravitational redshift as a depth differential, $z_{\rm spec}=\varpi_\odot/R_\odot=2.1231\times10^{-6}$ (`z_spectral_Sun`), is a first-order quantity and does not select the branch either.

## 39.4 The determining test

Jointly fit propagation delay and bending with shared inputs, then compare an observable sensitive to higher order, rather than reusing first-order agreement as branch selection. The first-order agreement of delay and bending with the familiar results is a consequence of the integrated relay deficit and is not evidence for the strong-depth form.

## 39.5 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| profile (39.1), alternative profile | engine's | the engine's profile (repaired, GOM22); the alternative is a branch of the fork |
| $\varpi_\odot=1477.046$ m | `bridge::koppa_Sun` | MEASURED-INPUT (stored: $R_\odot/k_\odot^2$ with the four-digit speed ratio $k_\odot=686.3$ of $c$ to the surface circular speed, itself scaled from planetary orbital speeds; no $G$ or mass enters; $2.8\times10^{-4}$ above the six-planet value of Chapter 33) |
| (39.2), (39.3) and the fitted coefficients | Sections 39.1–39.3 | DERIVED (exact) and COMPUTED |
| geometry (Earth–Mars grazing), $R_\odot$, AU | as stated | CONSTRUCTION / unit bridge |

**Residuals.**

* **R39.1 — the branch.** The active and alternative strong-depth continuations are not discriminated; the difference at the solar limb is $2.9\times10^{-6}$ arcsec and $33$ ps.
* **R39.2 — measured delay and bending.** No measured delay or deflection (radar ranging, spacecraft tracking, very-long-baseline measurements) is loaded; the engine's header cites such comparisons and they were not re-run.
* **R39.3 — non-point sources and plasma.** The solar corona's plasma delay and the Sun's finite extent and quadrupole are not included.
* **R39.4 — frames.** The delay is a far-frame quantity; the local duration measured at the receiver needs the tick-rate ratio $1-z$.
* **R39.5 — the header comment.** The $247.24\ \mu$s of the engine's header differs from the executed $247.314\ \mu$s by $0.03\%$; its origin was not traced.

## 39.6 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch39_lensing_and_propagation_delay
```

Criteria were registered in `Textbook/validation/ch39_PRE_REGISTRATION.md` before the instrument existed. Run 1 met T2, T3 and the delay clauses of T1 and failed two clauses through marginal registered tolerances (the constant-index line of V1 at $1.01\times10^{-10}$ against $10^{-10}$, and a series limit that omitted the higher terms); both tolerances were corrected and recorded. Run 2 (`ch39_run2_output.txt`) is the run of record and met every criterion.

## 39.7 Exercises and answers

**Exercise 1.** Derive $\Delta t$ to first order from (39.1).

*Answer.* $1/c_{\rm far}-1/c_\infty=(2z+3z^2+\ldots)/c_\infty$; the first term integrated over the path is $(2/c_\infty)\int z\,ds=(2\varpi/c)\int ds/\sqrt{b^2+s^2}$.

**Exercise 2.** Evaluate $4\varpi_\odot/R_\odot$ in arcseconds.

*Answer.* $4\times1477.0/6.957\times10^8=8.49\times10^{-6}$ rad $=1.75''$.

**Exercise 3.** Why do the two branches agree at first order?

*Answer.* Both have $n=1+2z+O(z^2)$.

**Exercise 4.** From $c_2=\pi(a+2)$, find $\Delta c_2$ between $a=3$ and $a=4$.

*Answer.* $\pi$.

**Exercise 5.** How large must $x$ be for the branches to differ in deflection by $10^{-3}$ rad?

*Answer.* $\Delta c_2\,x^2=10^{-3}$ gives $x=\sqrt{10^{-3}/\pi}=0.018$.

**Exercise 6.** Compute the second-order delay difference for $\varpi_\odot$ and $b=R_\odot$.

*Answer.* $\pi\varpi^2/(bc)=\pi(1477.0)^2/(6.957\times10^8\times2.998\times10^8)=3.3\times10^{-11}$ s.

## 39.8 Scope

Established: the integrated relay deficit and its logarithmic form with the factor 2 derived; the first-order delay, its second-order term and the executed Earth–Mars grazing value; the bending $4\varpi/b$ with its second-order coefficient $\pi(a+2)$ for a profile with $z^2$ coefficient $a$; the agreement of the two strong-depth branches at first order and their difference, $\pi$ in the second-order coefficient, at the solar limb ($2.9\times10^{-6}$ arcsec, 33 ps).

Not established: the branch (R39.1), any measured delay or deflection (R39.2), corrections for the corona and extended source (R39.3) and the local-duration relation (R39.4).

*Where it leads.* Chapter 40 takes the strong-depth branch to its limit: the boundary of the circular law, coordinate arrest and the angular-impulse ledger.
