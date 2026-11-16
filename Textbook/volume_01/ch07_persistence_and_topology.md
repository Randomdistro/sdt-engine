# Chapter 7 — Persistence and Topology

*Volume I — Ontology, Geometry and Admissible States.*
Draft of 9 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. Executable companion: `Textbook/examples/ch07_persistence_and_topology.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 7.1 The physical question

A form that persists is a form that keeps its identity while the medium moves through it. Two kinds of statement can be made about persistence. A topological statement holds for every deformation that avoids a reconnection, and needs no dynamics. A dynamical statement says that a particular state returns to itself after a disturbance, and needs the response law. Law VI says which windings are the stable particles; this chapter separates what is proved by topology, what is stated by the engine as an exact consequence of the movement budget, and what remains a dynamical claim.

## 7.2 Closure of a route

A route closes when the phase matches after one circuit. For a coherent mode along a closed path of length $s_{\rm tot}$,

$$\oint k_{\rm path}\,ds=2\pi n,\qquad n\in\mathbb Z. \tag{7.1}$$

The condition constrains recurrence. It does not fix the shape of the route, the amplitude, the exclusion volume or the restoring response, and distinct windings can share one recurrence count while differing in contact geometry. Closure after one circuit up to a permitted symmetry, $X(\sigma+2\pi)=gX(\sigma)$ (Eq. 1.7), is the geometric statement, and Chapter 1 kept three questions apart: existence of a recurring configuration, its stability, and its rates. Topology answers a part of the first. Sections 7.5 and 7.6 say what is needed for the others.

## 7.3 Winding classes

Law VI identifies a stable particle with a winding on a torus. A $(p,q)$ mode winds $p$ times one way round the torus and $q$ times the other. The identification in the engine is the electron as the $(1,1)$ mode, the proton as the $(2,3)$ trefoil, and the neutrino as an open winding. The winding number $W$ of Law VI is the $q$ of the mode: the proton has $q=3$ and the electron $q=1$ (`law_VI::topology::proton_q`, `electron_q`, `laws.hpp:2531–2532`).

A $(p,q)$ torus curve is a knot when $\gcd(p,q)=1$ and a nontrivial knot when also $\min(p,q)\ge2$. Its type is invariant under any deformation that does not cross the curve through itself. The Alexander polynomial of the torus knot is

$$\Delta_{p,q}(t)=\frac{(t^{pq}-1)(t-1)}{(t^{p}-1)(t^{q}-1)}, \tag{7.2}$$

defined up to a unit $\pm t^k$ and normalised here to a polynomial with nonzero constant term and positive leading coefficient. The instrument evaluated (7.2) in exact integer polynomial arithmetic, after the division routine and the formula had been checked on known results: $(t^2-1)/(t-1)=t+1$, a division with a remainder is reported as inexact, and the formula returns the tabulated trefoil $t^2-t+1$, cinquefoil $t^4-t^3+t^2-t+1$ and $T(3,4)$ polynomial $t^6-t^5+t^3-t+1$ (V1, V2).

| mode | polynomial $\Delta_{p,q}$ | class |
|---|---|---|
| $(1,q)$, $q=1\ldots12$ (the electron $(1,1)$; the $(1,2)$ "$W=2$" mode) | $1$ | unknot |
| $(2,3)$ (the proton) | $t^2-t+1$ | trefoil |
| $(2,5)$ | $t^4-t^3+t^2-t+1$ | cinquefoil |
| $(3,4)$ | $t^6-t^5+t^3-t+1$ | knot $8_{19}$ |

Table 7.1. Alexander polynomials, executed (tests T1, T2, V2).

For all 34 coprime pairs $2\le p<q\le12$ the polynomial differs from 1, has degree $(p-1)(q-1)$ (twice the genus), has palindromic coefficients, equals 1 at $t=1$ after normalisation, and takes an odd value in absolute value at $t=-1$ (T3). For the proton's trefoil the genus is 1 and $|\Delta(-1)|=3$. Because $\Delta_{2,3}\neq1$ the $(2,3)$ mode is topologically distinct from the unknot, which is what the engine's classification claims.

*A discrepancy in the engine's comment.* The header comment at `laws.hpp:2404` quotes, for the $(2,3)$ proton, the polynomial $t^{-2}-t^{-1}+1-t+t^2$. Normalised, that is $[1,-1,1,-1,1]$, the polynomial of the cinquefoil $T(2,5)$, and not of the trefoil (T2: equal to $\Delta_{2,5}$, different from $\Delta_{2,3}$). The conclusion drawn from it, that the proton mode is a nontrivial knot, holds equally for the correct polynomial $t^{-1}-1+t$. The comment is a text error and the canon is not edited here; the correction is proposed (residual R7.1).

A diagram of an unknot and a trefoil establishes a topological distinction. It does not establish an ordering of any physical quantity, and the engine says so: the classification of PPT09 is validated as a classification only.

## 7.4 Mode speeds from the movement budget

The engine gives the toroidal and poloidal speeds of a $(p,q)$ mode and its aspect ratio as

$$v_T=c\sqrt{\frac{p}{p+q}},\qquad v_P=c\sqrt{\frac{q}{p+q}},\qquad \frac Ra=\sqrt{\frac qp}, \tag{7.3}$$

so that $v_T^2+v_P^2=c^2$ for every mode (`topology::v_toroidal`, `v_poloidal`, `aspect_ratio`, `budget_residual`). The budget supplies one relation. The partition between the two speeds, $v_T^2:v_P^2=p:q$, is the mode lock, and it is a premise (residual R7.2), not a consequence of the budget alone. Given the lock, (7.3) follows exactly.

Executed (test T5): over all 144 modes $1\le p,q\le12$ the budget residual $(v_T^2+v_P^2)/c^2-1$ was at most $2.2\times10^{-16}$, the engine's functions equalled the closed forms (7.3) exactly, the electron $(1,1)$ had $v_T=v_P=0.707107\,c$, and the proton $(2,3)$ had $v_T=0.632456\,c$, $v_P=0.774597\,c$. The aspect ratios $R/a$ are $1$ for the electron and $1.224745$ for the proton.

## 7.5 Stability requires a constrained variation

The engine selects configurations by the Law IV test of minimum engaged resistance (FLM07, `law_IV`; Chapter 12). Write $\mathcal R[X]$ for the engaged-resistance functional of a candidate persistent state $X$. A stationary state satisfies $\delta\mathcal R[X_*]=0$ under admissible variations. Stability needs a nonnegative second variation on the constrained tangent space, with symmetry directions treated separately. Zero curvature can mean a free rotation, a marginal mode or an unresolved instability. Positive curvature establishes a local restoring response only. Escape across a finite barrier in $\mathcal R$ remains possible.

The engine states one local result. The restoring rate of a mode of the torus with harmonic numbers $(m,n)$ is

$$\omega^2_{m,n}=\Big(\frac{m\,v_T}{R}\Big)^2+\Big(\frac{n\,v_P}{a}\Big)^2, \tag{7.4}$$

so higher harmonics are damped preferentially, in proportion to $n^2$ and $m^2$, and the smooth torus is the stable equilibrium (`confinement::harmonic_rate_sq`, `laws.hpp:2566`). For the proton's mode with $R/a=\sqrt{q/p}$ the ratios $\omega^2_{0,n}/\omega^2_{0,1}$ and $\omega^2_{m,0}/\omega^2_{1,0}$ equalled $n^2$ and $m^2$ to $2.2\times10^{-16}$ for $m,n=1\ldots6$, every $\omega^2_{m,n}$ with $(m,n)\ne(0,0)$ was positive, and $\omega^2_{0,0}=0$ (T6). The zero is the uniform mode, a symmetry direction.

This is a statement about smoothing, about the decay of corrugations of a given torus. It is not a statement about which windings exist. The engine records that the first-order resistance integral of PPT09 puts the $W=2$ branch exactly level with two separated $W=1$ branches and determines no barrier, lifetime, reconnection direction or $W=\{1,3\}$ stability spectrum (`laws.hpp:2406–2409`; `Theory/03_Open_Problems.md`, problem 2). A proposed activated escape rate involves three separate tasks: the barrier in $\mathcal R$, the distribution of the disturbances that cross it, and the attempt rate. Neither topology nor the form of an exponential supplies any of the three. A deterministic instability would instead follow from the spectrum of the linearised evolution operator.

## 7.6 Reconnection and conservation

A change of knot class needs a local event in which the curve passes through itself. For the trefoil and the unknot the event is a single crossing change, and the skein relation relates the three curves at a crossing:

$$\nabla_+(z)-\nabla_-(z)=z\,\nabla_0(z),\qquad z=t^{1/2}-t^{-1/2}. \tag{7.5}$$

For the trefoil as $L_+$, the unknot as $L_-$ and the Hopf link as $L_0$, with Conway polynomials $1+z^2$, $1$ and $z$, the relation reads $z^2=z\cdot z$. The instrument confirmed at $t=0.5,\,2,\,3.7$ that $1+z^2$ equals $\Delta_{2,3}(t)/t$ to $4.4\times10^{-16}$ and that (7.5) holds to $2.2\times10^{-16}$ (T4). The trefoil therefore lies one crossing change from the unknot, and the change passes through a link of two components.

A reconnection in a contact network must account for the circulation, the linear impulse and the angular content of the outgoing network. A change in winding need not violate conservation when the outgoing relay disturbance or the circulation of the medium carries the difference. A ledger that omits the outgoing channels is incomplete; it does not show a failure of conservation in nature. A determining calculation couples the contact deformation, the topology change and the outgoing flux in one evolution, with no lifetime coefficient added afterwards (Chapter 15).

## 7.7 Input ledger and residuals

| quantity | role | label |
|---|---|---|
| Alexander polynomials, genus, determinants | Table 7.1 and T3 | DERIVED (exact) |
| skein check | (7.5) | DERIVED (exact) |
| mode speeds (7.3) given the lock | engine formulas | DERIVED given the lock premise |
| smoothing rates (7.4) | engine formula | DERIVED given (7.3) |
| assignment electron $(1,1)$, proton $(2,3)$, neutrino open winding | Law VI | posited |
| the lock $v_T^2:v_P^2=p:q$ | PPT01 | posited |

**Residuals.**

* **R7.1 — the quoted polynomial.** The comment at `laws.hpp:2404` gives the polynomial of $T(2,5)$ for the $(2,3)$ mode. Proposed correction, pending approval: replace it by $t^{-1}-1+t$.
* **R7.2 — the mode lock.** Why $v_T^2:v_P^2=p:q$, equivalently $R/a=\sqrt{q/p}$, is not derived. The open problem asks for a lattice calculation that solves the coupled mode equations and finds the discrete set of self-consistent $(R/a,\alpha)$ (`Theory/03_Open_Problems.md`, problem 1).
* **R7.3 — the stability spectrum.** That only $W=1$ and $W=3$ are stable, and the lifetime of $W=2$, need a lattice reconnection calculation that supplies the resistance curve, the barrier and the dissipation law (open problem 2).
* **R7.4 — the identification.** That the electron is $(1,1)$, the proton $(2,3)$ and the neutrino an open winding is the content of Law VI and is posited here.
* **R7.5 — the outgoing ledger.** The outgoing channels of a reconnection are not modelled.

## 7.8 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch07_persistence_and_topology
```

Criteria were registered in `Textbook/validation/ch07_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch07_run1_output.txt`) met every criterion, including T2, the registered statement about the engine's comment.

## 7.9 Exercises and answers

**Exercise 1.** Obtain $\Delta_{2,7}$ and the genus of $T(2,7)$.

*Answer.* $\Delta_{2,7}=t^6-t^5+t^4-t^3+t^2-t+1$ (for $T(2,q)$, $q$ odd, the coefficients alternate). The degree 6 equals $(p-1)(q-1)$, so the genus is 3.

**Exercise 2.** Show that $T(1,q)$ is the unknot by (7.2).

*Answer.* $(t^q-1)(t-1)/((t-1)(t^q-1))=1$.

**Exercise 3.** Find the determinant $|\Delta(-1)|$ of the trefoil and of the cinquefoil.

*Answer.* $t^2-t+1$ at $t=-1$ is $3$; $t^4-t^3+t^2-t+1$ at $t=-1$ is $5$. Both are odd.

**Exercise 4.** For the proton mode find $v_T/v_P$ and check the budget.

*Answer.* $\sqrt{p/q}=\sqrt{2/3}=0.816497$. With $v_T^2=\tfrac25c^2$ and $v_P^2=\tfrac35c^2$ the sum is $c^2$.

**Exercise 5.** Why does $\omega^2_{0,0}=0$ in (7.4) not imply instability?

*Answer.* The $(0,0)$ mode is the uniform one: a rigid rotation or translation of the whole torus along a symmetry direction. A symmetry direction has zero curvature by construction and is excluded from the stability test, which uses the constrained tangent space.

**Exercise 6.** Verify (7.5) at $t=4$ for the trefoil, the unknot and the Hopf link.

*Answer.* $z=2-\tfrac12=\tfrac32$. $\nabla_+=1+z^2=3.25$, $\nabla_-=1$, $\nabla_0=z=1.5$. Then $3.25-1=2.25=z\cdot z=1.5\times1.5$.

## 7.10 Scope

Established in this chapter: the exact Alexander polynomials of the engine's winding modes and the unknot, trefoil and cinquefoil classification; the text error in the engine's comment; the exact closure of the movement budget over all $(p,q)$ modes given the lock; the smoothing rates of the torus; and the crossing-change relation that connects knot classes.

Not established: the mode lock (R7.2), the stability spectrum and the lifetime of the $W=2$ branch (R7.3), and the outgoing ledger of a reconnection (R7.5).

*Where it leads.* Chapter 8 sets out the well-posedness of an evolution on these states. Chapter 17 builds the electron's $(1,1)$ circulation and Chapter 18 the proton's trefoil, with its boundary radius. Chapter 19 treats conversion between winding classes.
