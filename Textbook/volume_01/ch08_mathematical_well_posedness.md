# Chapter 8 — Mathematical Well-Posedness

*Volume I — Ontology, Geometry and Admissible States.*
Draft of 9 November 2026. Notation: $\mathrm{Om}=R/k^2$ and $k=c/v$ as in the production default of `Textbook/NOTATION_LEDGER.md`; they enter Section 8.5 only. Executable companion: `Textbook/examples/ch08_mathematical_well_posedness.cpp`; pre-registration and captured output in `Textbook/validation/`. Examples marked TOY are generic and carry no measured input.

## 8.1 The physical question

A set of equilibrium formulas is not an evolution. Before a chapter of this book asks what a state does next, it must say what a state is, which states are admissible, what data fix a continuation, and when the continuation is unique. It must also say what does not follow: a solver that refuses a step has not found a singularity, a divergent parameter has not found an infinite motion, and a bounded output has not shown that the state is regular. This chapter states the admissible state space, the conditions for a well-posed evolution, and the numerical-admissibility points that the later chapters rely on.

## 8.2 The admissible state space

Write the state as

$$X=(\text{geometry},\ \text{contact graph},\ \text{phase variables},\ \text{stored deformation},\ \text{relay response}). \tag{8.1}$$

The constraints $C(X)=0$ include contact compatibility (Chapter 1) and recurrence (Chapter 7). The inequalities include nonnegative durations, positive locus radii within a chart (Chapter 2), nonnegative occupied volumes and nonnegative content in every cell, and the movement budget $v_{\rm circ}^2+v^2=c^2$ (Chapter 13). Initial data must lie on the constraint manifold. Boundary data specify the incident relay, the outgoing conditions and any driving reservoir. A constraint that holds at one count and is not preserved by the evolution is not a constraint of the state.

## 8.3 Evolution, existence and uniqueness

An evolution $dX/dm=F(X)$, with $m$ a count of a declared oscillator, requires more than a list of equilibria. Under local Lipschitz continuity of $F$ in a finite-dimensional chart, a solution exists locally and is unique (Picard–Lindelöf). Without it the solution can fail to be unique even when it exists. The standard example is

$$\frac{dq}{dm}=\sqrt{|q|},\qquad q(0)=0, \tag{8.2}$$

which has the solutions $q=0$ and $q=m^2/4$ from the same data. The engine contains a function of this kind. The relay-lock fraction of Law IV is $f_{\rm lock}=\sqrt{r/b}$ for $r<b$ (`law_IV::relay_lock_fraction`, `laws.hpp:641`): it is continuous at $r=0$ with an infinite slope, so an evolution in which it enters the response is not covered by the uniqueness theorem at $r=0$. Existence holds there (Peano), uniqueness is not guaranteed, and the engaged volume obtained by integrating it, $\tfrac{8\pi}{7}b^3$, is unaffected because the integrand is integrable.

Near a chart transition the field $F$ must transform consistently. At a contact creation or a change of topology (Chapter 7) smooth evolution is replaced by an event rule, which must give a unique admissible continuation or state its branching law.

**A path across the polar axis (test T3).** The chart of Chapter 2 is singular on the polar axis, where every azimuth names one place. A straight path $P_k=(-1+0.1k,\,0,\,0.5)$ with $k=0\ldots20$ crosses the axis at $k=10$. The instrument advanced a locus along $+x$ by the engine's `step_locus` in 20 steps. Consecutive loci were $0.1$ apart to $9.7\times10^{-17}$, each locus lay within $6.3\times10^{-16}$ of the Cartesian reference, the polar angle at the crossing was $1.7\times10^{-16}$ (and $0.197396$ on either side), and the azimuth changed from $\pi$ to $2\pi$, a jump of $\pi$, between $k=9$ and $k=11$. The physical speed is constant across the crossing; only the label changes. The state is the place; the chart is an expression of it.

## 8.4 Positivity and conservation of a relay update

A relay update must keep every cell's content nonnegative and must conserve the total. A cell cannot pass on more than it holds. The TOY update

$$u_i'=(1-2f)\,u_i+f\,(u_{i-1}+u_{i+1}) \tag{8.3}$$

passes the fraction $f$ of each cell's content to each neighbour. Its coefficients are nonnegative if and only if $f\le\tfrac12$. The total is conserved identically, since each cell's content is redistributed among itself and its neighbours.

Executed (test T1, a delta initial state):

| $f$ | double precision, 201 cells, 50 steps: minimum cell content | exact rational, 25 cells, 8 steps |
|---|---|---|
| $\tfrac14$ | $0$ (total $1$ to $2.2\times10^{-16}$) | total $=1$, minimum $\ge0$ |
| $\tfrac12$ | $0$ (total $1$) | total $=1$, minimum $\ge0$ |
| $0.55$ (double), $\tfrac35$ (exact) | $-5.3\times10^{2}$ | total $=1$, minimum $<0$ |
| $\tfrac34$ | $-7.2\times10^{13}$ | total $=1$, minimum $<0$ |
| $1$ | $-4.9\times10^{22}$ | total $=1$, minimum $<0$ |

Table 8.1. A relay update at fractions below and above one half (TOY).

The unstable updates conserve content exactly; in double precision the sum is destroyed by the growth of the oscillation, and the totals read $1.0045$ at $f=0.75$ and $1.4\times10^6$ at $f=1$ in the first run, where the registered double-precision criterion could not be met. A conservation defect read in floating point is therefore not a failure of conservation until a resolution study and an exact or reservoir ledger have been made. The positivity criterion, $f\le\tfrac12$, is sharp: the update with $f=0.55$ was negative after the first step.

## 8.5 Arrest and divergent parameters

Suppose a configuration coordinate $q$ obeys $dq/dm=\mu(\chi)F(q,\chi)$ with a phase loading $\chi\to\infty$ (the arrest premise of Chapters 33 and 53). If the mobility falls as $\mu\sim\chi^{-p}$ and the drive grows as $F\sim\chi^{m_F}$, then $\dot q\sim\chi^{m_F-p}$: the motion tends to zero only for $p>m_F$, is constant for $p=m_F$ and diverges for $p<m_F$. A vanishing instantaneous speed does not establish a finite accumulated displacement. For $\chi\sim m^a$ and $|\dot q|\sim\chi^{-b}$ the remaining displacement from a count $1$ to $T$ is

$$I(T)=\int_1^{T}m^{-ab}\,dm=\begin{cases}\dfrac{T^{1-ab}-1}{1-ab},&ab\ne1,\\[2mm] \ln T,&ab=1,\end{cases} \tag{8.4}$$

which converges as $T\to\infty$ only for $ab>1$.

| $ab$ | $I(10^2)$ | $I(10^4)$ | $I(10^6)$ | $I(10^8)$ |
|---|---|---|---|---|
| 0.5 | 18.0 | 198.0 | 1998.0 | 19998.0 |
| 1 | 4.6052 | 9.2103 | 13.8155 | 18.4207 |
| 2 | 0.990000 | 0.999900 | 0.999999 | 0.99999999 |

Table 8.2. Accumulated displacement, executed (test T2; the quadrature in $\ln m$ agreed with (8.4) to $2.1\times10^{-15}$ over the twelve cases).

Three results must be kept apart: the instantaneous motion vanishes; the accumulated displacement is finite; and the stress, content and energy balance stay bounded. None entails the others. The circular branch $v_{\rm circ}=c\sqrt{\mathrm{Om}/r}$ holds for $r\ge\mathrm{Om}$ (Chapter 2, Eq. 2.10). Extrapolating it through a centre where circular geometry no longer exists produces a divergent calculation and not a centre-crossing trajectory. A physical arrest proof must also bound the stored content and the signal response, or justify a terminal boundary (Chapter 53).

## 8.6 Numerical admissibility: refusal is not a singularity

A solver that refuses at a collision or at the c-boundary has found no accepted continuation under its contract. It has not found a physical singularity, and it has not proved a physical arrest. The same holds for a replaced denominator. The engine's `Locus` refuses $r=0$ (Chapter 2), and `step_locus` replaces a result with $r\le10^{-12}$ by a floor of $0.5\times10^{-12}$.

Executed (test T4): advancing a place of radius 1 along the antipodal direction by $d=1\mp\rho$ should give radius $\rho$ in the direction of the origin place ($d<1$) or of its antipode ($d>1$).

| $\rho$ | radius short of the centre | relative error | radius past the centre | relative error |
|---|---|---|---|---|
| $10^{-2}$ | $1.000000000\times10^{-2}$ | $5.5\times10^{-14}$ | $1.000000000\times10^{-2}$ | $1.1\times10^{-12}$ |
| $10^{-4}$ | $9.99999997\times10^{-5}$ | $3.0\times10^{-9}$ | $9.99999997\times10^{-5}$ | $3.0\times10^{-9}$ |
| $10^{-6}$ | $9.999334\times10^{-7}$ | $6.7\times10^{-5}$ | $1.000044\times10^{-6}$ | $4.4\times10^{-5}$ |
| $10^{-8}$ | $1.49\times10^{-8}$ | $0.49$ | $5\times10^{-13}$ (floor) | $1.0$ |

Table 8.3. Accuracy of `step_locus` near the centre.

The relative error follows the budget $8u/\rho^2$ with $u=1.11\times10^{-16}$ (the registered budget was met in all eight cases and the loss at $\rho=10^{-8}$ was observed), and the direction label was correct for $\rho\ge10^{-6}$ on both sides. The cause is the law-of-cosines form $r^2=r_0^2+d^2+2r_0d\cos\psi$, which cancels between nearly equal terms when the result is small. The same file's `add_scaled` uses the cancellation-free half-angle form $(r_0-d)^2+4r_0d\cos^2(\psi/2)$. Using it in `step_locus` is proposed, not applied (canon). At $d=1$ exactly the engine returned its floor, $5\times10^{-13}$, and the exact value is $0$. A floor of this kind is an implementation choice and not a continuation through the centre (Chapter 58).

Convergence of a numerical evolution is reported for step size, angular integration and history interpolation separately (Chapter 60), and conservation defects with a reservoir ledger and a resolution study.

## 8.7 Input ledger and residuals

All executed values of this chapter are DERIVED (exact) or COMPUTED; no measured input enters. T1 and T2 are TOY.

**Residuals.**

* **R8.1 — the state.** The relay-response part of (8.1) is not specified by the sources. The descriptor of a cell is open (Chapter 1, R1.1).
* **R8.2 — existence and uniqueness.** The engine's time-stepping routines come with no existence or uniqueness theorem. The relay-lock fraction is not Lipschitz at $r=0$ (Section 8.3).
* **R8.3 — event rules.** Contact creation and change of winding class have no event rule that gives a unique continuation (Chapter 7, R7.3, R7.5).
* **R8.4 — the arrest exponents.** No exponent $p$, $m_F$, $a$ or $b$ has been assigned to a physical state; (8.4) is a criterion and not a result (Chapter 53).
* **R8.5 — `step_locus` near the centre.** The loss of accuracy of Table 8.3, and the proposed half-angle form.

## 8.8 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch08_mathematical_well_posedness
```

Criteria were registered in `Textbook/validation/ch08_PRE_REGISTRATION.md` before the instrument existed. Run 1 met every criterion except the double-precision conservation criterion of T1 for $f>\tfrac12$, which the instrument could not meet because the unstable update grows beyond the range where the sum is resolved; run 2 replaced it by an exact rational test and failed at one fraction because the instrument's overflow check tripped at $f=\tfrac{11}{20}$ (replaced by $\tfrac35$); run 3 (`ch08_run3_output.txt`) is the run of record and met every criterion. All three records are in the pre-registration file.

## 8.9 Exercises and answers

**Exercise 1.** Show that (8.2) has the two solutions stated.

*Answer.* For $q=0$ both sides are zero. For $q=m^2/4$, $\dot q=m/2$ and $\sqrt{q}=m/2$. Both satisfy $q(0)=0$.

**Exercise 2.** For which $f$ does (8.3) keep every coefficient nonnegative?

*Answer.* $1-2f\ge0$ and $f\ge0$ give $0\le f\le\tfrac12$.

**Exercise 3.** For $\dot q\sim\chi^{-3}\chi^{2}$ and $\chi\sim m^{2}$, does the displacement from count 1 to $T$ converge?

*Answer.* $\dot q\sim\chi^{-1}\sim m^{-2}$, so $ab=2\cdot1=2>1$ with $b=1$, $a=2$, and $I(\infty)=1/(ab-1)=1$. It converges.

**Exercise 4.** Estimate the relative error in $r$ of the law-of-cosines step at a true radius $\rho$.

*Answer.* $r^2$ is a sum of terms of size 1 with rounding error $\sim4u$. The error in $r^2$ is $\sim4u$, so $\delta r\approx2u/\rho$ and $\delta r/r\approx2u/\rho^2$, consistent with the observed errors ($4.4\times10^{-5}$ at $\rho=10^{-6}$ against $2u/\rho^2=2.2\times10^{-4}$).

**Exercise 5.** Why is the engine's floor $0.5\times10^{-12}$ not a continuation through the centre?

*Answer.* A continuation through the centre must give a direction on the far side and a radius growing from zero. The floor returns a fixed radius with the label of the input, without information about the far-side continuation, and it changes the radius by 12 orders for $\rho<10^{-12}$.

## 8.10 Scope

Established in this chapter: the admissible state space and its inequalities; the uniqueness theorem and the engine's one non-Lipschitz function; the sharp positivity threshold of a relay update and the exact conservation of an unstable one; the criteria for arrest and finite accumulated displacement, executed; the invariance of physical speed across a chart singularity; and the measured loss of accuracy of `step_locus` near the centre.

Not established: the relay-response part of the state (R8.1), existence and uniqueness theorems for the engine's evolution (R8.2), event rules (R8.3), or any physical exponent of arrest (R8.4).

*Where it leads.* Chapter 13 gives the movement budget as a constraint. Chapter 53 uses (8.4) to ask for the regularity proof. Chapters 58 and 60 return to conditioning and convergence.
