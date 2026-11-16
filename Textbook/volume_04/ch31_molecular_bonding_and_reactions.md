# Chapter 31 — Molecular Bonding and Reactions

*Volume IV — Atomic Recurrence, Spectra and Material Organisation.*
Draft of 10 November 2026. Notation: $E(R)$ is the energy of a configuration as a function of the separation $R$ (the engine's energy-ledger convention of Chapter 23); $R_*$ the equilibrium separation, $k=E''(R_*)$, $D$ the dissociation energy, $\mu$ the reduced mass. The model functions of this chapter are labelled TOY: generic, with no measured input and no claim to describe a molecule. Executable companion: `Textbook/examples/ch31_molecular_bonding_and_reactions.cpp`; pre-registration and captured output in `Textbook/validation/`. The engine supplies no bond energy functional; this chapter supplies the determining equations and tests of method, and assigns no closed bond potential.

## 31.1 The physical question

Two structures bond when the combined contact and wake configuration admits a lower accessible energy with a restoring separation response. A net inward interaction alone does not establish an equilibrium bond. The questions are: what, precisely, is a bond in terms of the energy of a configuration; which observables follow from the existence of the bond whatever its form; how many observables a candidate form can absorb before it is tested; and how a reaction route differs from its endpoints. The source history (CH07) records that a simple inverse-radius well did not supply the required stiffness and that a rolling-wall repair did not close the curvature and depth account; that bond-well mechanism stays open here, and no closed form is assigned.

## 31.2 A bond is a stationary point with restoring curvature

For separation $R$, $E'(R_*)=0$ and $E''(R_*)>0$ define a local minimum, and dissociation compares $E(R_*)$ with the separated relaxed structures, $D=E(\infty)-E(R_*)$.

**An inverse-radius well has no bond.** For $E=-A/R$, $E'=A/R^2>0$ for every $R>0$: there is no stationary point. **Executed (T1).** On 2000 log-spaced values of $R$ in $[10^{-3},10^{3}]$ the derivative of $-1/R$ was positive at every one. If a hard wall at contact $R_c=1$ bounds the range, the minimum is on the wall and $E'(R_c)=1\ne0$: the configuration is held by the wall, not by a restoring response, and its curvature is the wall's. Stiffness has to come from the same law that gives the depth.

**A family that has a bond.** Take $E=-A/R+B/R^m$ with $m>1$ (a Mie form, TOY). Then

$$R_*=\Big(\frac{mB}{A}\Big)^{\frac1{m-1}},\qquad k=E''(R_*)=\frac{A}{R_*^3}(m-1),\qquad D=\frac A{R_*}\Big(1-\frac1m\Big),\qquad \frac{kR_*^2}{D}=m. \tag{31.1}$$

**Executed (T1).** For $(A,B,m)=(1,1,2),(1,\tfrac12,3),(2,1,6),(3,2,12)$ the stationary point found by bisection on $E'$ equalled the closed form to $1.1\times10^{-16}$, $D$ to $2.2\times10^{-16}$ and $kR_*^2/D=m$ to $2.2\times10^{-16}$, with positive numerical curvature at each.

## 31.3 Isotope response survives whatever the well

For a given energy function of separation, the small-oscillation frequency is $\omega=\sqrt{k/\mu}$, and $R_*$ and $D$ do not depend on the masses. **Executed (T2).** With the reduced masses of the three hydrogen molecules from the stored masses, $\mu_{{\rm H}_2}=8.363110\times10^{-28}$ kg, $\mu_{\rm HD}=1.114897\times10^{-27}$ kg and $\mu_{{\rm D}_2}=1.671792\times10^{-27}$ kg, the ratio $\omega_{{\rm H}_2}/\omega_{{\rm D}_2}=\sqrt{\mu_{{\rm D}_2}/\mu_{{\rm H}_2}}=1.413863$ and $\omega_{{\rm H}_2}/\omega_{\rm HD}=\sqrt{\mu_{\rm HD}/\mu_{{\rm H}_2}}$ held to $2\times10^{-16}$ for the four Mie families and a Morse family alike. The isotope-response block therefore remains valid while the bond-well mechanism is open: it is a property of the response, not of the well, and it is not discarded merely because the parent approximation was incomplete. It also means that the ratio of isotope frequencies is not evidence for any particular well.

## 31.4 Three observables are absorbed; a fourth is needed

A well with three free parameters absorbs three observables exactly. **Executed (T3).** For 1000 pseudo-random triples $(R_*,k,D)$ with $kR_*^2/D>1$ the Mie parameters $m=kR_*^2/D$, $A=kR_*^3/(m-1)$, $B=AR_*^{m-1}/m$ reproduced $k$, $D$ and $E'(R_*)=0$ to $10^{-10}$ (evaluated with the analytic derivatives; $m$ reaches several hundred in this sample); 55 further triples had $kR_*^2/D\le1$ and no Mie member exists for them. Matching the equilibrium separation, the force constant and the dissociation energy is therefore no test of the family: it leaves residual zero by construction.

A fourth observable discriminates. The cubic coefficient is $E'''(R_*)=-k(m+4)/R_*$ for the Mie family, and $-6D\,(k/2D)^{3/2}$ for a Morse function $D(1-e^{-a(R-R_*)})^2$ with the same $R_*$, $k$ and $D$. For $(R_*,k,D)=(1,20,2)$ the Mie family has $m=10$ and $E'''=-280$, the Morse function has $E'''=-134.16$: finite differences gave $-279.9992$ and $-134.1641$, and the two differ by a factor $2.09$. Which fourth observable is available (an anharmonic constant, an overtone, a thermal expansion, the isotope shift of the dissociation limit) depends on the molecule; the principle is that the number of independent observables must exceed the number of parameters before agreement counts.

## 31.5 Pathway dependence

A reaction coordinate $q$ is a reduced route through many contact configurations. The barrier height depends on the relaxed constrained path and not only on the endpoint binding. Rate calculation needs mode populations, coupling and transport of the released excitation. A catalyst changes the accessible routes and barriers; an unchanged endpoint energy does not imply an unchanged rate.

**Executed (T4).** On the TOY surface $E(x,y)=(x^2-1)^2+2(y-0.3x^2)^2-g\,e^{-(x^2+y^2)/w^2}$ with $w=0.15$, the relaxed route (minimum over $y$ at each $x$, Newton in $y$, 2001 points of $[-1,1]$) has the endpoint minima at $x=\pm1$ with $E=0$. The added term is localised at the saddle. With $g=0.4$ the endpoint energy changed by $-3.7\times10^{-22}$ (below the registered $10^{-12}$) while the barrier fell from $1.000000$ to $0.859377$, a reduction of $0.141$. The reduction is smaller than $g$ because the top of the relaxed route moves away from $x=0$ once the saddle is lowered. Two surfaces with identical endpoints, identical binding and different routes have different barriers.

## 31.6 Coupled material response

Bond geometry affects stiffness, optical polarisation, heat capacity and transport. A useful material row carries the same evolving bond state into all sectors; independent fitted coefficients for each sector conceal whether one mechanism predicts several observables (Chapter 32).

## 31.7 The determining test

One molecular construction should predict the equilibrium distance, the small-oscillation frequency, the isotope shift and the dissociation energy. By Section 31.4 these are not four independent tests of a three-parameter well: the isotope shift follows from the frequency (Section 31.3), so the independent observables are the distance, the frequency and the dissociation energy, and a fourth (anharmonic) observable has to be added. No measured molecular constant is loaded here.

## 31.8 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| model functions (inverse well, Mie, Morse) | as stated | CONSTRUCTION (TOY; no measured input) |
| (31.1), the inversion of Section 31.4 | exact | DERIVED (exact), checked numerically |
| $m_p$, $m_d$ | `measured::` | MEASURED-INPUT (reduced masses only) |
| TOY surface of Section 31.5 | as stated | CONSTRUCTION |

**Residuals.**

* **R31.1 — the bond mechanism.** The bond-well functional is not supplied; the CH07 history (inverse well; rolling wall) leaves curvature and depth unclosed.
* **R31.2 — a native stiffness.** Stiffness and depth must come from one contact law; the engine provides neither for molecules.
* **R31.3 — reaction rates.** Mode populations, coupling and transport of released excitation are not computed.
* **R31.4 — measured constants.** No measured equilibrium distance, frequency, isotope shift or dissociation energy is loaded; the determining comparison is outstanding.

## 31.9 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch31_molecular_bonding_and_reactions
```

Criteria were registered in `Textbook/validation/ch31_PRE_REGISTRATION.md` before the instrument existed. Run 1 met every criterion except the 1000-triple clause of T3, whose finite-difference derivatives are inaccurate for the large $m$ of the sample (an instrument defect; the clause was repaired with analytic derivatives). Run 2 (`ch31_run2_output.txt`) is the run of record and met every criterion.

## 31.10 Exercises and answers

**Exercise 1.** Show that $E=-A/R+B/R^m$ has a minimum for $m>1$ and derive $R_*$.

*Answer.* $E'=A/R^2-mB/R^{m+1}=0$ gives $R_*^{m-1}=mB/A$. $E''(R_*)=-2A/R_*^3+m(m+1)B/R_*^{m+2}=(A/R_*^3)(m+1-2)=(A/R_*^3)(m-1)>0$, using $mB/R_*^{m+1}=A/R_*^2$.

**Exercise 2.** Derive $kR_*^2/D=m$.

*Answer.* $k R_*^2=A(m-1)/R_*$ and $D=(A/R_*)(m-1)/m$; the ratio is $m$.

**Exercise 3.** Why does $\omega_{\rm H_2}/\omega_{\rm D_2}$ not test the well?

*Answer.* $\omega=\sqrt{k/\mu}$ with the same $k$ for both isotopes.

**Exercise 4.** Evaluate $\omega_{\rm H_2}/\omega_{\rm D_2}$ from $\mu_{{\rm H}_2}=m_p/2$ and $\mu_{{\rm D}_2}=m_d/2$.

*Answer.* $\sqrt{m_d/m_p}=\sqrt{1.99900750}=1.413863$.

**Exercise 5.** For $(R_*,k,D)=(1,20,2)$ find the Mie exponent.

*Answer.* $m=kR_*^2/D=10$.

**Exercise 6.** Why can two surfaces with the same endpoints have different rates?

*Answer.* The rate depends on the barrier of the relaxed route and on the coupling and populations along it, none of which the endpoint energies fix.

## 31.11 Scope

Established: the definition of a bond as a stationary point with restoring curvature and of dissociation by relaxed separated structures; that an inverse-radius well has no bond and a wall gives no restoring response; the relations (31.1) for a family that has a bond; that isotope response is independent of the well; that three observables are absorbed exactly by a three-parameter well and a fourth is needed; and that a localised term can lower a barrier without changing the endpoints.

Not established: a bond mechanism (R31.1), a native stiffness (R31.2), reaction rates (R31.3) and any comparison with measured molecular constants (R31.4).

*Where it leads.* Chapter 32 turns to condensed phases: constitutive response, coexistence slopes and transport beyond the dilute regime.
