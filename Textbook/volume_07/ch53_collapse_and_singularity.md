# Chapter 53 — Collapse and Singularity

*Volume VII — Correspondence, Paradoxes and Discriminating Tests.*
Draft of 10 November 2026. Notation: $\chi$ a phase-loading variable, $\mu\sim\chi^{-p}$ mobility, $F\sim\chi^m$ drive, $v=\mu F=\chi^{m-p}$ response velocity, $k$ the loading-growth exponent ($d\chi/dt=\chi^k$), $U\sim\chi^w$ stored energy, $\tau\sim\chi^m$ traction, $\rho$ distance from an axis. Executable companion: `Textbook/examples/ch53_collapse_and_singularity.cpp`; pre-registration and captured output in `Textbook/validation/`. Every model in this chapter is a generic stand-in (TOY): power laws in $\chi$ and rigid rotations, with no engine function and no measured input.

## 53.1 Identify the divergent observable

A coordinate angle, a mathematical phase parameter, a force density and a total energy are different candidates for divergence. A singular coordinate chart can coexist with a finite physical distance and impulse. A physical regularity claim has to specify the observables and the continuation of the state.

For phase loading $\chi\to\infty$ with mobility $\mu\sim\chi^{-p}$ and drive $F\sim\chi^m$ the response velocity is $v=\chi^{m-p}$: motion arrests only when $p>m$. For a loading that grows as $d\chi/dt=\chi^k$ the displacement accumulated up to $\chi_{\max}$ is

$$D=\int_1^{\chi_{\max}}\chi^{m-p-k}d\chi=\frac{1-\chi_{\max}^{-(k+p-m-1)}}{k+p-m-1}, \tag{53.1}$$

(a logarithm at $k+p-m=1$), which stays finite as $\chi_{\max}\to\infty$ only when $k+p-m>1$. Arrest and finite late displacement are therefore separate conditions, and a finite late displacement additionally needs an integrable velocity history.

**Executed (V1, T1).** The quadrature in $\ln\chi$ reproduced $\int_1^{10^{12}}\chi^{-3}d\chi=0.5$ ($9\times10^{-15}$) and $\int_1^{10^6}\chi^{-1}d\chi=\ln10^6=13.8155$ ($1.1\times10^{-13}$). For seven parameter sets $(m,p,k)$ the quadrature equals (53.1) to better than $1.2\times10^{-13}$ at $\chi_{\max}=10^6$ and $10^{12}$, and:

| $(m,p,k)$ | $v(10^6)\to v(10^{12})$ | $D(10^{12})-D(10^{6})$ | arrest | finite displacement |
|---|---|---|---|---|
| $(1,3,1)$ | $10^{-12}\to10^{-24}$ | $0.0000$ ($D=0.5$) | yes | yes |
| $(1,2,1)$ | $10^{-6}\to10^{-12}$ | $0.0000$ ($D\to1$) | yes | yes |
| $(1,1.5,1)$ | $10^{-3}\to10^{-6}$ | $0.0020$ ($D\to2$) | yes | yes |
| $(1,1.2,1)$ | $0.0631\to0.00398$ | $0.2956$ ($D\to5$, slowly) | yes | yes |
| $(2,2.5,0.5)$ | $10^{-3}\to10^{-6}$ | $13.8155$ $(=\ln10^6)$ | yes | **no** |
| $(2,1,1)$ | $10^{6}\to10^{12}$ | $10^{12}$ | no | no |
| $(0,0,1)$ | $1\to1$ | $13.8155$ | no | no |

The set $(2,2.5,0.5)$ arrests (the velocity falls by $10^{-3}$ over six decades) while its displacement grows as $\ln\chi_{\max}$ without limit: a velocity that goes to zero does not by itself give a finite late displacement.

**Stress and energy (T2).** Stored energy $U(\chi)$ and traction are checked independently. For every set the traction $\chi^m$ grows with $\chi$ exactly when $m>0$. The set $(1,3,1)$ arrests ($v\to0$) with a traction $\chi^1$ that grows without limit: zero velocity coexists with diverging stress when the constitutive law permits it.

## 53.2 Axial degeneration

The physical azimuthal speed is $\rho\dot\varphi$, with $\rho$ the distance from the axis. A line on the axis has zero displacement under rotation about that axis. A circular-state formula instead imposes a finite-radius transverse route; replacing a disappearing circle by an axial line changes the configuration class and needs a torque or phase-transfer rule.

**Executed (T3).** Under a rotation by $\alpha=0.7$ about $z$, the axis points $(0,0,s)$, $s=-2,-1,0.5,3$, are displaced by $0$ (worst value $0$, registered $10^{-16}$). Under a rotation by the same angle about the transverse $x$-axis, the displacement of such a point is $2|s|\sin(\alpha/2)$ (worst relative error $0$ at the reported precision). The speed $R\dot\varphi$ at fixed $\dot\varphi=1$ falls by exactly $10^{-4}$ as $R$ falls from $1$ to $10^{-4}$, so a vanishing circle has vanishing speed at a finite angular rate; at $\rho=0$ the angle $\varphi=\mathrm{atan2}(y,x)$ is formally undefined (the library convention returns $0$). The slow turning of a line's orientation concerns a different rotation from spinning the line about its own axis: a finite segment tilting about a transverse direction moves its points away from the pivot. An angular coordinate must not be mistaken for a material speed.

## 53.3 A physical regularity theorem

A completed theorem would establish bounded energy and traction, a finite admissible signal response, and either a unique continuation or a derived terminal arrest state. It must cover the coupled medium, not only the tracked body.

**Executed (T4).** Four independent checks (arrest $p>m$; finite late displacement $k+p-m>1$; bounded energy $w\le0$; bounded traction $m\le0$) were applied to a grid of 40 models, $m\in\{-1,-0.5,0,0.5,1\}$, $p\in\{-1,\ldots,3\}$ (eight values), $k=1$, $w=m$. The rules agree with the numerical classification at every point. The counts: arrest 25; finite displacement 25; bounded energy 24; bounded traction 24; all four 18. Fewer models pass all four checks than pass any one, as registered (18 against 25). A regularity argument that establishes only one condition (for instance that the velocity falls) establishes less than the theorem.

**The depth branch.** In the depth closure the tick-rate ratio $C=1-z$ goes to zero as $z\to1$, and the remote duration to reach it diverges as a logarithm (Chapter 48, T1: $\ln(1/\epsilon)=4.605$ and $9.210$ at $\epsilon=10^{-2}$ and $10^{-4}$ for $C=1-S$). That is a remote-time barrier under the stated assumptions: a statement about the remote duration, not about contact stress or about the interior continuation, both of which remain determining equations (R53.2). The statement that physical motion cannot realise an extrapolated infinity motivates the search for the replacement mechanism; the replacement has to compute the limiting state and its observable response.

## 53.4 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| exponents $(m,p,k,w)$ | Sections 53.1, 53.3 | CONSTRUCTION (no measured input) |
| displacement (53.1), counts | Sections 53.1, 53.3 | DERIVED (exact) and COMPUTED |
| rotation displacements | Section 53.2 | COMPUTED |

**Residuals.**

* **R53.1 — the constitutive law.** The mobility, drive, energy and traction exponents are stand-ins; no contact constitutive law supplies them.
* **R53.2 — the interior.** Contact stress, interior continuation and terminal arrest state in the depth branch are not computed.
* **R53.3 — the coupled medium.** The checks were applied to a tracked quantity, not to the coupled medium with its signal response.
* **R53.4 — axial rule.** The torque and phase-transfer rule for a degenerating circle is not supplied.
* **R53.5 — a theorem.** No regularity theorem is proved; the four conditions are necessary checks, not sufficient ones.

## 53.5 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch53_collapse_and_singularity
```

Criteria were registered in `Textbook/validation/ch53_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch53_run1_output.txt`) met every criterion and is the run of record.

## 53.6 Exercises and answers

**Exercise 1.** For $(m,p,k)=(1,2,1)$ find the limit of $D$.

*Answer.* $k+p-m-1=1$, so $D\to1$.

**Exercise 2.** For which $p$ does a loading with $m=1$, $k=1$ arrest, and for which is the displacement finite?

*Answer.* Arrest needs $p>1$; finite displacement needs $1+p-1>1$, i.e. $p>1$: the two coincide here. They separate when $k<1$ (for $k=\tfrac12$ the displacement needs $p>1.5$ while arrest needs only $p>1$).

**Exercise 3.** Why does $(2,2.5,0.5)$ have a logarithmic displacement?

*Answer.* $m-p-k=-1$, so the integrand is $1/\chi$.

**Exercise 4.** What does a diverging traction with a vanishing velocity mean?

*Answer.* With $p>m>0$ the velocity $\chi^{m-p}$ falls while the traction $\chi^m$ still grows without limit: the material would carry unbounded stress at rest, and arrest alone does not establish regularity.

**Exercise 5.** What is the displacement of a point at distance $s=2$ from the pivot of a segment tilted by $0.7$ rad?

*Answer.* $2s\sin(\alpha/2)=4\sin0.35=1.371$.

**Exercise 6.** Why is the angle undefined on the axis, though the displacement is finite?

*Answer.* The angle is a coordinate ($\mathrm{atan2}(y,x)$ at $x=y=0$); the displacement is the distance moved by the point, which is zero.

## 53.7 Scope

Established: that arrest and finite late displacement are separate conditions with the exact displacement (53.1); that velocity can vanish while the traction diverges; the displacement of axis and off-axis points under rotation; that four independent checks pass for 18 of 40 stand-in models while one check alone passes for 25.

Not established: a constitutive law (R53.1), the interior continuation in the depth branch (R53.2), the coupled medium (R53.3), the axial rule (R53.4) and a regularity theorem (R53.5).

*Where it leads.* Chapter 54 asks what a cosmological model must predict jointly and which observables a pressure-history calibration constrains.
