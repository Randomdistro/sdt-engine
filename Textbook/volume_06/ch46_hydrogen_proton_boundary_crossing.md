# Chapter 46 — Hydrogen–Proton Boundary Crossing

*Volume VI — Sz, Pressure History and Coupled Ratios.*
Draft of 10 November 2026. Notation: $\mathrm{Om}_H=\alpha^2a_0$ the hydrogen c-boundary (`measured::r_e`); $R_{p,\rm lock}=4\hbar/(m_pc)$ the lock radius (`law_III::R_p_lock`); $R_p=C_gR_{p,\rm lock}$ the measured structural radius; $\mathcal R=\mathrm{Om}_H/R_p$; $a_X=d\ln X/dS$ the response of a quantity $X$ along the state coordinate $S$ (Chapter 41). Executable companion: `Textbook/examples/ch46_hydrogen_proton_boundary_crossing.cpp`; pre-registration and captured output in `Textbook/validation/`. Inputs: $\{\hbar,c,\alpha,m_e,m_p,a_0\}$ (CODATA 2022, `measured`); $R_p$ (stored measured proton boundary radius), read after the native lock quantities were printed.

## 46.1 Contemporaneous structures

With $\mathrm{Om}_H=\alpha^2a_0$ and the action-seat relation $a_0=\hbar/(m_ec\alpha)$, the hydrogen boundary against the lock radius is

$$\mathcal R_{\rm lock}=\frac{\mathrm{Om}_H}{R_{p,\rm lock}}=\frac{\alpha}{4}\frac{m_p}{m_e},\qquad \mathcal R=\frac{\mathrm{Om}_H}{R_p}=\frac{\alpha}{4C_g}\frac{m_p}{m_e}. \tag{46.1}$$

$C_g$ stays in the expression unless the lock and the operational structural radius are identified under a justified comparison. A dimensional common rescaling cancels in $\mathcal R$, but a differential response of the sectors does not.

**Executed (V1, T1).** The reduced proton Compton length ($2.103089\times10^{-16}$ m) and the classical electron radius ($2.8179403\times10^{-15}$ m) were reproduced, and the integrator on $d\mathcal R/dS=r\mathcal R$ reproduced $3e^{-1}$ at $S=1$ for $r=-1$ ($8\times10^{-16}$). Before any measured radius was read: $\mathrm{Om}_H=2.817940320\times10^{-15}$ m, $R_{p,\rm lock}=8.412356402\times10^{-16}$ m (coordination 4; the engine's value equals $4\hbar/(m_pc)$ exactly) and $\mathcal R_{\rm lock}=3.349763355$ computed directly and as $(\alpha/4)(m_p/m_e)$, equal to $5\times10^{-12}$ (a statement of the internal consistency of the CODATA values of $a_0$, $\alpha$ and $m_e$ with the action-seat relation). Read afterwards: $R_p=8.4140\times10^{-16}$ m, so $C_g=1.000195$ and $\mathcal R=3.349109$. The lock radius and the measured radius agree to $2\times10^{-4}$.

## 46.2 Crossing condition

$d\ln\mathcal R=(a_\alpha+a_{m_p}-a_{m_e}-a_{C_g})\,dS=r\,dS$. A crossing ($\mathcal R=1$) satisfies

$$\int_0^{S^*}r\,dS=-\ln\mathcal R_0 . \tag{46.2}$$

The lock branch needs a log change of $-1.208890$ and the measured-radius branch $-1.208694$; the two differ by $\ln C_g=1.9536\times10^{-4}$ (registered: below $10^{-3}$).

**Executed (T2).** A constant net rate $r=-1$ was integrated by RK4 with bisection on the crossing: $S^*=1.2088897030$, equal to $-\ln\mathcal R_0/r$ to $10^{-13}$. For a non-constant net rate $r(S)=-1-S/2$ the crossing is $0.9724667891$, equal to the exact $2(\sqrt{1+\ln\mathcal R_0}-1)$ to $4\times10^{-14}$.

**Fixed-coordinate and contemporaneous crossings.** Holding the proton radius fixed while $\mathrm{Om}_H$ changes is a fixed-coordinate crossing; letting both sectors respond is a contemporaneous crossing. With the same net rate $r=-1$ (contemporaneous: $a_{\rm Om}=-2$, $a_{R_p}=-1$; fixed: $a_{\rm Om}=-1$, $a_{R_p}=0$) both cross at $S^*=1.2088897030$, but the end states differ: $R_p/R_{p,0}=0.298529$ in the first and $1$ in the second, a ratio of $3.349763$ ($=\mathcal R_0$, registered and met). An absolute quantity of the crossing state, a temperature for instance, therefore depends on the relative response of the two sectors, not on the ratio alone.

## 46.3 Rate and uncertainty

A closed ratio route fixes where the crossing lies and not when contact occurs. **Executed (T3).** $S^*$ scales inversely with the net rate: $S^*=2.41777941,\ 1.20888970,\ 0.60444485$ for $r=-0.5,-1,-2$ (ratios exact to $10^{-9}$). The progression $dS/d\tau$ is a further function (Chapters 41 and 43).

Radius-definition uncertainty, the covariance of $\alpha$ and the resistance ratio $m_p/m_e$, and the uncertainty in $C_g$ propagate into the crossing condition through $\ln\mathcal R_0$; the measured radius carries the largest relative uncertainty among the inputs and enters through $\ln C_g$. No uncertainties were loaded in this chapter (R46.2).

## 46.4 What $\mathcal R$ is

$z=r_e/R_p$ is hydrogen's own depth ratio at the proton's measured radius. By the author's ruling of 2026-10-12 the proton's own c-boundary is the poloidal rotation radius inside its four tours, a value that remains to be derived. $\mathcal R$ therefore compares two boundaries of two different structures; a crossing of the ratio is not a statement about the proton's own boundary (R46.5).

## 46.5 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $\hbar,c,m_e,m_p,a_0$ | `measured` | CODATA 2022; $\{\hbar,m_e,m_p\}$ one mass/action seat |
| $\alpha$ | `measured` | hydrogen rung $k_H=1/\alpha$ |
| $\mathrm{Om}_H=\alpha^2a_0$ | `measured::r_e` | COMPUTED (shared-input with the CODATA set) |
| $R_{p,\rm lock}=4\hbar/(m_pc)$ | `law_III` | DERIVED (lock coordination 4, FLM07) |
| $R_p$ | `measured` | OBSERVED (stored) |
| $C_g$, $\mathcal R$ | Section 46.1 | COMPUTED |
| response rates $a_X$ | Section 46.2 | CONSTRUCTION (no measured input) |

**Residuals.**

* **R46.1 — the relative response.** No nonzero relative sector response is measured or derived; the rates $a_\alpha,a_{m_p},a_{m_e},a_{C_g}$ were set for the toy only.
* **R46.2 — uncertainty.** The covariance of the CODATA inputs and the radius-definition uncertainty were not propagated.
* **R46.3 — the progression.** $dS/d\tau$ is not supplied, so no time of crossing is computed.
* **R46.4 — contact.** What a crossing does physically (contact of the two boundaries) is not computed.
* **R46.5 — the proton's own boundary.** The poloidal rotation radius of the proton remains to be derived; $\mathcal R$ compares hydrogen's boundary with the proton's lock and measured radii.

## 46.6 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch46_hydrogen_proton_boundary_crossing
```

Criteria were registered in `Textbook/validation/ch46_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch46_run1_output.txt`) met every criterion and is the run of record.

## 46.7 Exercises and answers

**Exercise 1.** Show $\mathrm{Om}_H/R_{p,\rm lock}=(\alpha/4)(m_p/m_e)$.

*Answer.* $\alpha^2a_0=\alpha^2\hbar/(m_ec\alpha)=\alpha\hbar/(m_ec)$; dividing by $4\hbar/(m_pc)$ gives $(\alpha/4)(m_p/m_e)$.

**Exercise 2.** What log change brings $\mathcal R_{\rm lock}=3.349763$ to 1?

*Answer.* $-\ln3.349763=-1.208890$.

**Exercise 3.** Two scenarios have $r=-1$: one lets only $\mathrm{Om}_H$ fall, the other lets $\mathrm{Om}_H$ fall twice as fast and $R_p$ fall as well. Compare $S^*$ and the end states.

*Answer.* Both cross at $S^*=1.20889$; in the first $R_p$ is unchanged, in the second it has fallen by $e^{-1.20889}=0.2985$.

**Exercise 4.** For $r(S)=-1-S/2$, find the crossing.

*Answer.* $S+S^2/4=\ln\mathcal R_0$, so $S^*=2(\sqrt{1+\ln\mathcal R_0}-1)=0.97247$.

**Exercise 5.** What does $C_g\ne1$ do to the required log change?

*Answer.* It shifts it by $\ln C_g$: the measured-radius branch needs $-1.208890+1.9536\times10^{-4}=-1.208694$.

**Exercise 6.** Why does the ratio route not give a date?

*Answer.* $S^*$ is a coordinate value; the elapsed duration is $\int dS/[C\,F_S]$ and needs the progression law.

## 46.8 Scope

Established: the lock ratio $\mathcal R_{\rm lock}=3.349763$ and its closed form (46.1); the measured-radius ratio $3.349109$ and $C_g=1.000195$; the crossing condition (46.2) with exact checks; that the fixed-coordinate and contemporaneous crossings share $S^*$ and differ in end state; that $S^*\propto1/|r|$.

Not established: a measured or derived relative response (R46.1), propagated uncertainty (R46.2), the progression (R46.3), contact (R46.4) and the proton's own boundary (R46.5).

*Where it leads.* Chapter 47 joins the thermal, wavelength and acoustic landmarks of the Clearing under one calibrated branch.
