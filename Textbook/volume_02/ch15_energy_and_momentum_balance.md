# Chapter 15 — Energy and Momentum Balance

*Volume II — Pressure Response, Inertia and Propagation.*
Draft of 9 November 2026. Notation: $\varpi_i$ denotes the source length of body $i$ (the engine's `koppa_m`; the koppa length of Chapter 6, here only a weight and source strength). No other circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md` are used. Durations are counts: the integrator's step is reported as a number of steps per orbit, a dimensionless ratio; the SI second enters the instrument only through the unit bridge $c$. Executable companion: `Textbook/examples/ch15_energy_and_momentum_balance.cpp`; pre-registration and captured output in `Textbook/validation/`. The chain of Section 15.3 is the TOY relay chain of Chapter 14; the source lengths of Section 15.4 are generic CONSTRUCTION values.

## 15.1 The physical question

A balance statement names a region, a quantity, and everything that crosses or exchanges with the region. Such a statement is a test only when the list of exchanges is not completed after the fact by assigning to the unlisted part whatever restores the sum. Two kinds of closure are therefore separated here. A **kernel closure** holds because the rule that moves the bodies has a structure (antisymmetric in each pair, central) that makes a sum over bodies constant. A **medium closure** would hold only when the content carried by the relay medium is added to the body sum. The first can be verified by execution on the rule alone. The second needs the medium's transport computed independently of the demand that the totals balance; defining the medium's momentum as the negative of the body's is an accounting identity (CONSTRUCTION) and is not used as evidence in this chapter.

Three objects are ledgered: a region of the TOY relay chain with a reversing scatterer (Section 15.3), the engine's weighted body ledger (Sections 15.4–15.6), and an emitter with an angular pattern (Section 15.7).

## 15.2 The balance law of a region

Let $Q_V(m)$ be the amount of a quantity in a region $V$ at count $m$, $F_{\rm in}$ and $F_{\rm out}$ the amounts carried across its boundary during one count, and $S_V$ the amount exchanged with agents inside $V$ that are not themselves in the ledger. Then

$$Q_V(m+1)-Q_V(m)=F_{\rm in}-F_{\rm out}+S_V. \tag{15.1}$$

Equation (15.1) is a definition of $S_V$ unless $S_V$ is computed from a stated mechanism. For a quantity with no exchange, $S_V=0$ is a prediction. Content is of that kind in the chain below; momentum is not.

## 15.3 Ledger of a chain region (TOY)

Take the chain of Eq. (14.2) with $s=0.3$, 200 cells, random initial content (fixed generator) and the region $V$ of cells $50$ to $149$. Per count the content in $V$ changes by what enters across the two interfaces minus what leaves, with the interface flux read from the update rule. The momentum content is $P=\sum_i(R_i-L_i)$ in units of content × one hop. The reversal of a fraction $s$ of the content at cell $i$ changes the momentum content there by $-2s(R_i-L_i)$ and conserves content. That change is taken by the reversing agent, so the recoil of the scatterer in $V$ is

$$\text{recoil}_V=\sum_{i\in V}2s\,(R_i-L_i), \tag{15.2}$$

and the momentum balance of the region reads $\Delta P_V+\text{recoil}_V=F^{(P)}_{\rm in}-F^{(P)}_{\rm out}$, where right-moving content carries $+1$ and left-moving $-1$.

Executed over 100 counts (T1): the content residual $\Delta U_V-(\text{inflow}-\text{outflow})$, divided by the content in the region at the start of the count, was at worst $1.28\times10^{-15}$. The momentum residual with the recoil (15.2) included was at worst $1.7\times10^{-15}$. With the recoil omitted the residual of the momentum balance had magnitude equal to the recoil, the worst difference being $1.8\times10^{-15}$, and the recoil was not small: the sum of $\lvert\text{recoil}_V\rvert$ over the 100 counts was $10.97$ (content × hop), against region content of order 100. The content ledger therefore closes without a scatterer term, and the momentum ledger of the region closes only with one. Which agent takes the recoil is not specified by the chain (residual R15.1).

## 15.4 The engine's weighted body ledger

The engine's dynamics kernel gives body $i$ the acceleration

$$\vec a_i=c^2\sum_{j\ne i}\varpi_j\,\frac{\vec r_j-\vec r_i}{\lvert\vec r_j-\vec r_i\rvert^{3}}\qquad(\texttt{dynamics::accelerations},\ \texttt{dynamics.hpp:85–130}). \tag{15.3}$$

No $G$, no source mass, no softening enters; $\varpi_j$ is a length. In SDT language the resultant is the net push on body $i$ from the unshadowed side (Chapter 10); the kernel records the resultant along the line of centres and not the agency. The engine's invariants (`dynamics::invariants`, `dynamics.hpp:239–270`) weight every body by $\varpi_i$:

$$\vec P=\sum_i\varpi_i\vec v_i,\qquad \vec L=\sum_i\varpi_i\,\vec r_i\times\vec v_i,\qquad E=\tfrac12\sum_i\varpi_iv_i^2-c^2\sum_{i<j}\frac{\varpi_i\varpi_j}{r_{ij}}. \tag{15.4}$$

The last sum is the engine's pair term: it is a function of the separations that makes $E$ constant under (15.3), and the engine does not say that it is stored anywhere (residual R15.3).

**Kernel closure.** From (15.3) the pair contributions to $\varpi_i\vec a_i$ and $\varpi_j\vec a_j$ are $\pm c^2\varpi_i\varpi_j\,\vec r_{ij}/r_{ij}^3$, equal and opposite, so $\sum_i\varpi_i\vec a_i=0$ and $\vec P$ is constant. The force on each pair is along the line of centres, so $\sum_i\varpi_i\vec r_i\times\vec a_i=0$ and $\vec L$ is constant. For the pair $(i,j)$ with $\vec r=\vec r_j-\vec r_i$ the contribution of the kinetic term to $dE$ is $-c^2\varpi_i\varpi_j\,(\vec v_j-\vec v_i)\cdot\vec r/r^3$ and that of the pair term is $+c^2\varpi_i\varpi_j\,\vec r\cdot(\vec v_j-\vec v_i)/r^3$, so $E$ is constant (Exercise 3). All three closures are properties of the rule (15.3) with the weights of (15.4). That the same length $\varpi_i$ is both the source strength in (15.3) and the weight of $\vec P$ in (15.4) is a premise of the engine: it is the equality of the strength with which a body sources the interaction and the weight with which it responds (residual R15.4; Chapter 12).

No medium term appears in (15.4). The closure of the body sums is therefore a statement about the bodies and the kernel; it does not show that the relay medium exchanges no momentum with the bodies (residual R15.2).

## 15.5 Executed: body ledger and step order

The test pair has $\varpi=(10^3,\,3\times10^3)$ m at separation $d=10^9$ m (CONSTRUCTION; generic values, not an astronomical pair), on the engine's `circular_pair` (`dynamics.hpp:278–295`) with $\omega=c\sqrt{(\varpi_1+\varpi_2)/d^3}$ (the radius of body 1 is $d\varpi_2/\varpi_{\rm tot}$, so $\omega^2r_1=c^2\varpi_2/d^2$ reproduces (15.3), Exercise 2).

*Instrument check (V1).* RK4 with 4000 steps over one period $T=2\pi/\omega=1.047923\times10^4$ s returned both bodies to their start with position error $6.6\times10^{-13}\,d$.

*Closures (T2).* Over 2000 steps of one orbit, the weighted momentum $\lvert\vec P\rvert/(\varpi_{\rm tot}v_{\max})$ stayed at or below $6.8\times10^{-16}$ (velocity-Verlet) and $5.6\times10^{-16}$ (RK4); the relative drift of $\lvert\vec L\rvert$ over the orbit was $4.8\times10^{-15}$ and $2.6\times10^{-14}$. Momentum and angular momentum are conserved to round-off by both steps, as the pair antisymmetry of (15.3) requires; the integrators keep the antisymmetry exactly because each pair contribution is computed once and applied with opposite sign (`dynamics.hpp:122–126`).

*Order of the step (T2(c)).* The energy is the quantity a step conserves only to its order. On the circular orbit the energy error after one full period is not a probe of the order: with $N=200,400,800$ steps per orbit it was $1.6\times10^{-14},\,5.8\times10^{-16},\,1.2\times10^{-15}$ for velocity-Verlet (round-off) and $5.3\times10^{-9},\,1.7\times10^{-10},\,5.2\times10^{-12}$ for RK4 (observed order $5.00$), because the symmetric trajectory cancels the leading terms of the energy error at a full period. The registered order test was moved to an eccentric orbit (both velocities scaled by $0.7$, eccentricity $0.51$, semi-major axis $a=d/1.51$ from the energy relation of the kernel) and the maximum energy deviation over one period was recorded for $N=400,800,1600$:

| steps per period | velocity-Verlet | RK4 |
|---|---|---|
| 400 | $7.196\times10^{-4}$ | $6.572\times10^{-8}$ |
| 800 | $1.801\times10^{-4}$ | $4.606\times10^{-9}$ |
| 1600 | $4.503\times10^{-5}$ | $3.041\times10^{-10}$ |

Table 15.1. Maximum relative energy deviation over one period of the eccentric orbit, executed (T2(c)).

The observed orders are $1.999$ and $2.000$ for velocity-Verlet and $3.835$ and $3.921$ for RK4, inside the registered ranges $[1.8,2.2]$ and $[3.5,4.5]$. The RK4 value is below 4 and rising with $N$, as expected before the asymptotic regime.

*Three bodies (T3).* The equilateral configuration of equal $\varpi=10^3$ m at side $10^9$ m rotates rigidly: each body's acceleration is $\sqrt3\,c^2\varpi/s^2$ toward the centre, which equals $\omega^2s/\sqrt3$ for $\omega^2=3c^2\varpi/s^3$. RK4 over a quarter period (2000 steps) kept the three side lengths equal to the initial side to $8.0\times10^{-15}$ relative and the weighted momentum to $6.2\times10^{-16}$ of its scale.

## 15.6 Contact: the step is refused

The kernel (15.3) is the point-source form. For finite bodies the exact-to-contact force of Chapter 10 has the same $1/r^2$ form for $r\ge R_1+R_2$, and the engine supplies each body a `collision_radius_m`. A step whose predicted state places two bodies at or inside the sum of their collision radii is refused with status `collision`, and the state is left unmodified (`dynamics.hpp:112–120` and the step at `:134–163`).

Executed (T4): two bodies of $\varpi=10^3$ m with collision radius $10^6$ m each, released at rest from $d=10^8$ m, stepped by velocity-Verlet with $dt=T_{\rm ff}/10^4$. The engine returned `collision` at step 15689; the state after the refused step equalled the state before it in every position and velocity; the last accepted separation was $2.069003\times10^6$ m against the contact distance $2.000000\times10^6$ m. Nothing about what happens at contact follows from the refusal. The engine continues neither the kernel nor any contact law through the boundary (residual R15.5).

## 15.7 An emitter with a pattern

An emitter of luminosity $\mathcal L$ whose angular pattern is $I(\mu)\propto1+\varepsilon\mu$, with $\mu$ the cosine to a fixed axis, carries away momentum at the rate

$$\frac{\dot P}{\mathcal L/c}=\frac{\int_{-1}^{1}(1+\varepsilon\mu)\,\mu\,d\mu}{\int_{-1}^{1}(1+\varepsilon\mu)\,d\mu}=\frac{\varepsilon}{3}. \tag{15.5}$$

Executed (T5), quadrature for $\varepsilon=0,\,10^{-3},\,0.5,\,1$ gave $0,\ 3.33333\times10^{-4},\ 0.166667,\ 0.333333$ in units of $\mathcal L/c$, equal to $\varepsilon/3$ to $5.6\times10^{-17}$. An isotropic emitter therefore carries energy away with no net momentum; a dipole pattern carries both, and the emitter recoils. In a balance of the form (15.1) this is an exchange $S_V$ between the body and the relay content it emits into. The engine's bodies have constant $\varpi_i$ and no emission, so the engine's ledger (15.4) cannot represent this exchange, and the closure of Section 15.4 holds only for systems without it (residual R15.2).

## 15.8 What each ledger includes

| ledger | bodies | exchange term | closed by |
|---|---|---|---|
| chain region, content | cells in $V$ | none | the update rule (15.1 with $S_V=0$) |
| chain region, momentum | cells in $V$ | recoil (15.2), computed from the reversals | the scatterer, unspecified (R15.1) |
| engine body sums (15.4) | all bodies | none in the engine | the pair antisymmetry of (15.3) |
| patterned emitter | the emitter | the emitted content's momentum (15.5) | not represented in the engine (R15.2) |

Table 15.2. Which exchanges each ledger carries, from the executed cases.

## 15.9 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| chain parameters ($s$, cells, region, counts, generator seed) | as stated | CONSTRUCTION |
| body source lengths, separation, collision radii, velocity scale $0.7$, $\varepsilon$ | as stated | CONSTRUCTION |
| kernel (15.3), invariants (15.4), refusal rule | engine's | DERIVED in the engine (bridge, comment T3/T6); checked here by execution |
| $c$ (SI seconds ↔ length) | `measured::c` | MEASURED-INPUT (unit bridge; no result above depends on it) |
| closures, orders, ledger residuals | Sections 15.3–15.7 | COMPUTED |

**Residuals.**

* **R15.1 — the scatterer of the chain.** The agent that takes the recoil (15.2) is not specified in the TOY chain.
* **R15.2 — the medium term for real bodies.** Whether bodies exchange momentum with the relay medium, and how much, is not computed. The engine has no such term, so its closure (15.4) is a statement about the kernel. A computation of the medium's transport that is independent of the requirement of balance is outstanding.
* **R15.3 — the pair term of the energy.** The engine does not say whether the pair term in (15.4) corresponds to content stored anywhere. Its relation to the energy of Chapter 13 is not derived here.
* **R15.4 — one length for source and weight.** The equality of the source strength and the weight of $\vec P$ in the engine is the weak-equivalence premise of Chapter 12; it is not derived in this chapter.
* **R15.5 — contact.** The engine refuses a step at contact; the interaction through contact is not given here (Chapters 21 and 22).
* **R15.6 — circular-orbit test.** The registered energy-order test was placed on a symmetric orbit and failed for a reason of symmetry (Section 15.5); the corrected test is on an eccentric orbit. The corrected criterion was fixed before it was coded and is recorded in the pre-registration.

## 15.10 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch15_energy_and_momentum_balance
```

Criteria were registered in `Textbook/validation/ch15_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch15_run1_output.txt`) met every criterion except three: the content closure of T1, whose absolute tolerance ignored the size of the sum (corrected to a residual relative to the region's content), and the two order ranges of T2, which were placed on a symmetric circular orbit (moved to the eccentric orbit of T2(c), registered before it was coded). Run 2 (`ch15_run2_output.txt`) is the run of record and met every criterion.

## 15.11 Exercises and answers

**Exercise 1.** Show that $\sum_i\varpi_i\vec a_i=0$ under (15.3).

*Answer.* The pair $(i,j)$ contributes $c^2\varpi_i\varpi_j\,\vec r_{ij}/r_{ij}^3$ to $\varpi_i\vec a_i$ with $\vec r_{ij}=\vec r_j-\vec r_i$, and $c^2\varpi_j\varpi_i(\vec r_i-\vec r_j)/r^3$ to $\varpi_j\vec a_j$. They cancel.

**Exercise 2.** For two bodies on a circle about the barycentre, show $\omega^2=c^2(\varpi_1+\varpi_2)/d^3$.

*Answer.* Body 1 sits at radius $r_1=d\varpi_2/\varpi_{\rm tot}$ and has acceleration $c^2\varpi_2/d^2$ toward body 2, which must equal $\omega^2r_1$. Then $\omega^2=c^2\varpi_2/(d^2r_1)=c^2\varpi_{\rm tot}/d^3$.

**Exercise 3.** Show that $E$ in (15.4) is constant under (15.3).

*Answer.* For one pair, $\varpi_i\vec v_i\cdot\vec a_i+\varpi_j\vec v_j\cdot\vec a_j=-c^2\varpi_i\varpi_j\,(\vec v_j-\vec v_i)\cdot\vec r/r^3$. The pair term has $\frac{d}{dm}\big(-c^2\varpi_i\varpi_j/r\big)=+c^2\varpi_i\varpi_j\,\vec r\cdot(\vec v_j-\vec v_i)/r^3$. The sum is zero.

**Exercise 4.** Derive (15.5).

*Answer.* $\int_{-1}^1\mu\,d\mu=0$ and $\int_{-1}^1\mu^2d\mu=\tfrac23$, so the numerator is $2\varepsilon/3$; the denominator is $2$.

**Exercise 5.** Show that reversing a fraction $s$ of the content at a cell changes the momentum content there by $-2s(R-L)$.

*Answer.* A fraction $s$ of $R$ moves from $+1$ to $-1$, a change of $-2sR$ in momentum content, and a fraction $s$ of $L$ moves from $-1$ to $+1$, a change of $+2sL$. The total is $-2s(R-L)$.

**Exercise 6.** From Table 15.1, compute the observed order of velocity-Verlet between $N=400$ and $800$.

*Answer.* $\log_2(7.196\times10^{-4}/1.801\times10^{-4})=\log_2 3.996\approx2.00$.

## 15.12 Scope

Established in this chapter: the content ledger of a chain region closes with interface fluxes alone, while its momentum ledger closes only with the recoil of the reversing agent, and omitting the recoil leaves a residual equal to it; the engine's kernel (15.3) conserves the weighted momentum and angular momentum to round-off for both steps and the energy (15.4) to the order of the step (second order for velocity-Verlet, near fourth for RK4, on an eccentric orbit); the equilateral three-body configuration rotates rigidly; the engine refuses a step at contact and leaves the state unmodified; and an emitter with a dipole pattern recoils with $\varepsilon\mathcal L/(3c)$.

Not established: the scatterer of the chain (R15.1), any exchange of momentum between real bodies and the relay medium (R15.2), the status of the pair term of the energy (R15.3), the equality of source strength and weight (R15.4), and the interaction at contact (R15.5).

*Where it leads.* Chapter 16 takes the continuum limit of the chain's balance and the engine's transport coefficients, where fluxes of content and momentum acquire coefficients. Chapters 21 and 22 take the contact of finite bodies.
