# Chapter 34 — Noncircular Trajectories

*Volume V — Bodies, Fields and Propagation.*
Draft of 10 November 2026. Notation: $\mu=c^2\varpi_{\rm tot}$ is the relative-orbit strength of Chapter 15 (units $\mu=1$ in the instrument); $\varepsilon$ the conserved energy per unit reduced mass and $L$ the angular momentum per unit reduced mass; $a=-\mu/(2\varepsilon)$, $e=\sqrt{1+2\varepsilon L^2/\mu^2}$, $p=L^2/\mu$. Executable companion: `Textbook/examples/ch34_noncircular_trajectories.cpp`; pre-registration and captured output in `Textbook/validation/`. The named source condition throughout is a point source of fixed strength.

## 34.1 The physical question

Chapter 33 treated the circular family. A general trajectory has radial and transverse motion, turning points where the radial speed vanishes, and conserved quantities that the source condition guarantees. The questions are what the radial and transverse decomposition gives, which source condition makes a route close, how a departure from that condition appears (apsidal motion), and what an open trajectory does. All are derived and checked by integration.

## 34.2 Radial and transverse motion

For the relative acceleration $-\mu\hat r/r^2$ the angular momentum $L=r^2\dot\varphi$ and the energy $\varepsilon=\tfrac12(\dot r^2+L^2/r^2)-\mu/r$ are conserved (Chapter 15). The radial speed is then fixed by position,

$$\dot r^2=2\Big(\varepsilon+\frac\mu r\Big)-\frac{L^2}{r^2}, \tag{34.1}$$

and the turning points are its zeros, $r_{p,a}=a(1\mp e)$ for $\varepsilon<0$. The orbit equation in $u=1/r$ is $u''+u=\mu/L^2$ with solution $u=(1+e\cos\varphi)/p$; the radial period $2\pi\sqrt{a^3/\mu}$ is independent of $e$ at fixed $a$.

**Executed (T1; V1).** From apoapsis data $r_a=1.51$, $v_a=\sqrt{2/r_a-1}$ the formulas give $\varepsilon=-\tfrac12$ and $e=0.51$ to $4\times10^{-16}$. RK4 integration over three periods ($2\times10^5$ steps per period) for $e=0.3,0.6,0.9$ at $a=1$ gave:

| $e$ | $r_{\min}$ error | $r_{\max}$ error | period error | drift of $\varepsilon$, $L$ | residual of (34.1) |
|---|---|---|---|---|---|
| 0.3 | $1.4\times10^{-13}$ | $7.3\times10^{-14}$ | $1.2\times10^{-13}$ | $1.3\times10^{-13}$, $7.1\times10^{-14}$ | $1.2\times10^{-13}$ |
| 0.6 | $6.4\times10^{-14}$ | $1.7\times10^{-13}$ | $1.2\times10^{-13}$ | $1.4\times10^{-13}$, $3.5\times10^{-14}$ | $1.9\times10^{-13}$ |
| 0.9 | $3.9\times10^{-14}$ | $3.8\times10^{-13}$ | $4.5\times10^{-13}$ | $5.0\times10^{-13}$, $3.3\times10^{-14}$ | $6.3\times10^{-13}$ |

Table 34.1. Turning points ($1\mp e$), period ($2\pi$), conservation and the radial equation along the integrated orbits, executed (T1). Radii are errors against $1\mp e$, the period error is against $2\pi$, and the residual is $\lvert\dot r^2-[2(\varepsilon+1/r)-L^2/r^2]\rvert$ over 1000 samples.

The period between successive apoapsis passages is $2\pi$ for all three eccentricities, so the radial period depends on the source strength and the semi-major axis and not on the shape of the route.

## 34.3 Closure and apsidal motion

The inverse-square route closes: after one radial period the angle advanced is exactly $2\pi$. **Executed (T2).** Starting at $r_a=1.3$ with $v_a=\sqrt{2/r_a-1}$ ($e=0.3$), the angle between successive apoapsis passages for the inverse-square law was $2\pi$ to $8\times10^{-14}$ rad.

Closure is a property of the source condition. A radial acceleration with an extra term, $-\mu/r^2-\kappa/r^3$, gives by Binet's equation

$$u''+\Big(1-\frac\kappa{L^2}\Big)u=\frac\mu{L^2}, \tag{34.2}$$

which is linear, with oscillation frequency $\sqrt{1-\kappa/L^2}$ in $\varphi$; the radial period in $\varphi$ is $2\pi/\sqrt{1-\kappa/L^2}$ and the apsides advance by

$$\Delta\varphi=2\pi\Big(\frac1{\sqrt{1-\kappa/L^2}}-1\Big)\approx\frac{\pi\kappa}{L^2}\quad\text{per radial period.} \tag{34.3}$$

**Executed (T2).** With $\kappa=0.002$ and $L^2=r_a^2v_a^2=0.910000$ the integrated advance was $6.916001\times10^{-3}$ rad, equal to (34.3) to $9.2\times10^{-12}$ relative. A departure from the inverse-square source condition therefore appears as an advance of the apsides of a definite size and sign (for $\kappa>0$ forward), fixed by $\kappa/L^2$; and the advance of a route with a given $\kappa$ grows as the route is made narrower (smaller $L$). Which departure the real source condition has (a term of the form $\kappa/r^3$ from the response of the medium, a finite-size effect, other sources) is a question for Chapters 35 and 36; this chapter supplies the map from a given departure to its apsidal signature.

## 34.4 Open trajectories

For $\varepsilon>0$ the route is open: the periapsis is $r_p=p/(1+e)$ with $e>1$ and the deflection between the incoming and outgoing asymptotes is $2\arcsin(1/e)$. **Executed (T3).** A body started at $(-2000,1)$ with velocity $(1,0)$ ($\mu=1$; $\varepsilon=\tfrac12-1/r_0$, $L=1$, $e=1.41385996$, $p=1$) was integrated until it returned to $r=2000$ (about $2\times10^6$ steps of $2\times10^{-3}$): the periapsis radius was $0.4142742392$ against $p/(1+e)=0.4142742390$ ($4\times10^{-10}$ relative), and the angle between initial and final velocity was $1.57129633$ rad against $2\arcsin(1/e)=1.57129658$ rad ($2.5\times10^{-7}$ rad; the difference is the finite starting radius). The conserved ledger fixes the shape of the route, and the strength $\mu$ is the single source parameter.

## 34.5 What the conserved quantities depend on

All the results above use the conservation of $L$ and $\varepsilon$, which follow from the central form and the pairing of the kernel (Chapter 15). If the source condition changes (a source that is extended, moving, or whose strength depends on its history; Chapter 35), $L$ and $\varepsilon$ of the relative orbit are no longer separately conserved by this argument and the radial equation (34.1) has to be replaced by the corresponding one. The statement of a turning point and a conserved quantity is therefore made under a named source condition, as here: a point source of fixed strength.

## 34.6 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| (34.1)–(34.3), turning points, open-orbit relations | Sections 34.2–34.4 | DERIVED (exact), checked by integration |
| test orbits, $\kappa$, starting data | as stated | CONSTRUCTION (units $\mu=1$; no measured input) |
| the kernel and its conserved quantities | Chapter 15 | the engine's kernel |

**Residuals.**

* **R34.1 — the departure.** Which departure from the inverse-square source condition the real medium has is not determined here; $\kappa/r^3$ is a stand-in.
* **R34.2 — extended and moving sources.** The conserved ledger is stated for a point source of fixed strength; extended, moving and history-dependent sources are treated in Chapter 35.
* **R34.3 — measured orbits.** No measured trajectory is compared; the apsidal signature is a map for later comparison (Chapter 36).

## 34.7 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch34_noncircular_trajectories
```

Criteria were registered in `Textbook/validation/ch34_PRE_REGISTRATION.md` before the instrument existed. Run 1 met every criterion except the $\kappa=0.002$ clause of T2, which failed because the instrument coded the perturbation as $-\kappa/r^4$ instead of $-\kappa/r^3$ (the registered form was correct; the defect was in the code). Run 2 (`ch34_run2_output.txt`) is the run of record and met every criterion.

## 34.8 Exercises and answers

**Exercise 1.** Derive the turning points from (34.1).

*Answer.* $\dot r=0$ gives $2\varepsilon r^2+2\mu r-L^2=0$; the roots are $r=[-\mu\pm\sqrt{\mu^2+2\varepsilon L^2}]/(2\varepsilon)=a(1\mp e)$ with $a=-\mu/(2\varepsilon)$.

**Exercise 2.** What is the advance per orbit for $\kappa/L^2=0.01$?

*Answer.* $2\pi(1/\sqrt{0.99}-1)=0.03165$ rad (the first-order estimate $\pi\kappa/L^2=0.03142$).

**Exercise 3.** Show that $\kappa=0$ closes the orbit.

*Answer.* (34.2) has frequency 1 in $\varphi$: the radial period in $\varphi$ is $2\pi$.

**Exercise 4.** For the open orbit with $e=\sqrt2$, find the deflection.

*Answer.* $2\arcsin(1/\sqrt2)=\pi/2$.

**Exercise 5.** Why does the period depend only on $a$ and $\mu$?

*Answer.* $T=2\pi\sqrt{a^3/\mu}$ follows from integrating the areal rate $L/2$ over the ellipse area $\pi ab$ with $b=a\sqrt{1-e^2}$ and $L=\sqrt{\mu a(1-e^2)}$.

**Exercise 6.** What does a negative $\kappa$ do to the apsides?

*Answer.* The advance (34.3) is negative: the apsides regress.

## 34.9 Scope

Established: the radial equation and turning points of the inverse-square route and their integrated values; the independence of the radial period from $e$; the closure of the inverse-square route and the exact apsidal advance (34.3) for a $\kappa/r^3$ departure; the periapsis and deflection of an open route.

Not established: the actual departure of the real source condition (R34.1), extended and moving sources (R34.2) and any comparison with measured orbits (R34.3).

*Where it leads.* Chapter 35 treats many bodies with retarded occlusion: the seven-circle geometry, history interpolation, shielding and source response.
