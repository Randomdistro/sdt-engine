# Chapter 12 — Displacement and Resistance

*Volume II — Pressure Response, Inertia and Propagation.*
Draft of 9 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. Executable companion: `Textbook/examples/ch12_displacement_and_resistance.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 12.1 The physical question

Law III gave the push that the unshadowed directions exert on a body. Law IV asks for the body's response to a change of its movement: what resists, what the resistance is proportional to, and why the resistance to being moved and the shadow cast on others are the same quantity. This chapter follows the derivation in the Complete Laws paper, tests its arithmetic, records where its two statements of the key distribution disagree, and sets out the engine's engaged volume, which goes beyond the paper, and the reading of binding as a reduced exclusion volume.

## 12.2 Premises

Premises P1–P8 are those of Chapters 4 and 9. Two are added.

| id | premise | source |
|---|---|---|
| P10 | A form of exclusion volume $V_{\rm disp}$ diverts the content that would otherwise cross it. At rest the arrival is isotropic and no net direction results (Chapter 9, Eq. 9.4). | Complete Laws, Law IV §1–2 |
| P11 | A form moving at velocity $\vec v$ meets the relay fronts ahead and leaves those behind, so that to first order in $v/c$ the directional content in its frame is $\phi'(\hat n)=(\Phi/4\pi)(1+\vec v\cdot\hat n/c)$. | Complete Laws, Eq. 3.1 |

P7 of Chapter 9, that content in transit carries momentum equal to its density over $c$, is used again here (residual R12.1).

## 12.3 Resistance from the dipole

The content inside the exclusion volume is $V_{\rm disp}\Phi/\ell_P^3$ per unit solid angle fraction $1/4\pi$. Its momentum under the dipole (P11) is, by P7,

$$\vec p=\frac{V_{\rm disp}}{\ell_P^3c}\,\frac{\Phi}{4\pi}\oint\Big(1+\frac{\vec v\cdot\hat n}{c}\Big)\hat n\,d\Omega. \tag{12.1}$$

The monopole term vanishes, $\oint\hat n\,d\Omega=0$, and the dipole term is $\oint(\vec v\cdot\hat n)\hat n\,d\Omega=\tfrac{4\pi}{3}\vec v$ (verified by the instrument's quadrature, V1: $4.188790204786=4\pi/3$ to $10^{-15}$). Therefore

$$\vec p=\frac{\Phi\,V_{\rm disp}}{3\,\ell_P^3c^2}\,\vec v\equiv m\,\vec v,\qquad m=\frac{\Phi V_{\rm disp}}{3\,\ell_P^3c^2}, \tag{12.2}$$

and the resisting force is $\vec F=-d\vec p/dm_{\rm osc}=-m\,\vec a$ per count of the oscillator in which the acceleration is written. Mass is the reorganisation cost of the exclusion volume: the resistance of the diverted pattern to being rearranged. The factor $1/3$ is the same second moment, $\langle\hat n\otimes\hat n\rangle=I/3$, that fixes the isotropic stress of Chapter 9.

*Executed (test T1).* The momentum (12.1) by quadrature, with $V_{\rm disp,p}=1.832653\times10^{-58}$ m³ and $V_{\rm disp,e}=9.980942\times10^{-62}$ m³, equalled $m_pv$ and $m_ev$ respectively from the engine's `mass_from_V_disp`, with $p/(mv)=1$ to $6.7\times10^{-15}$ in both cases at $v=0.01\,c$. The integrand is linear in $v$, so the ratio does not depend on $v$. At the registered speed of 1 m/s the dipole term is $3\times10^{-9}$ of the monopole term, which integrates to zero, and the rounding of the cancelling sum was $2\times10^{-7}$ of the result; the first run failed for that reason and the test condition was repaired (recorded in the pre-registration).

*A sensitivity.* The factor 3 in (12.2) is the transport-tensor share of Chapter 9. If the traction of the boundary of the engaged volume were the absorbing-face value (residual R9.4) the factor would be 6, and $V_{\rm disp}$ obtained from a given mass would double: for the proton $V_{\rm disp,p}=1.832653\times10^{-58}$ m³ would become $3.665306\times10^{-58}$ m³, and $R_{\rm excl,p}=3.523686\times10^{-20}$ m would rise by $2^{1/3}=1.259921$ to $4.439566\times10^{-20}$ m. The mass is the measured input in both cases; the exclusion volume is the output and carries the factor.

## 12.4 Equivalence of inertial and gravitational mass

The Complete Laws argue as follows. The gravitational mass of a body is the angular deficit it creates for others, which is set by its shadow cross-section; the inertial mass is the cost of reorganising the diverted pattern, which is set by $V_{\rm disp}$; both are determined by the one displacement, so the identity is geometric. The argument needs the shadow that a body casts to be determined by $V_{\rm disp}$. The engine carries two proton volumes that differ by $1.36\times10^{13}$: the volume inside the boundary radius $R_p$ ($5.9\times10^{59}$ cells), which casts the shadow in the electric case, and the exclusion volume ($4.3\times10^{46}$ cells), which sets the mass (Chapter 1, Table 1.3). Which volume sets the shadow of the gravity class, and how it is tied to $V_{\rm disp}$, is the content of Chapter 49 and the c-boundary of a body (Chapter 33); this chapter records the equivalence as a statement of the source and not as an executed result (residual R12.4).

## 12.5 The speed limit and the Lorentz factor

The source obtains the bound $v\le c$ from the trailing hemisphere of (P11): $\phi'(-\hat v)=(\Phi/4\pi)(1-v/c)\ge0$. That uses the first-order form at $v=c$ and is an extrapolation of a first-order statement to the edge of its range. The source's Corollary 7.1 writes the full aberration as $\phi'(\hat n)\propto(1-\beta\cos\theta)^{-2}$ and states that it gives $m(v)=\gamma m_0$.

*The two forms differ at first order.* The normalised dipole $D(\beta)=\oint\phi'\mu\,d\Omega/\oint\phi'\,d\Omega$ is $\beta/3$ for $\phi'=1+\beta\mu$ and $2\beta/3$ for $\phi'=(1-\beta\mu)^{-2}$. The instrument gave $D/\beta=0.333333333$ and $0.666666668$ at $\beta=10^{-4}$, a ratio of $2.000000$ (test T2). The source therefore states two first-order dipoles of different strength. Used in (12.1), the Corollary's distribution gives a momentum larger than (12.2) by the factor $r(\beta)=3I_1(\beta)/(2\beta)$ with

$$I_1(\beta)=\int_{-1}^{1}\frac{\mu\,d\mu}{(1-\beta\mu)^2}=\frac1{\beta^2}\Big[\frac{2\beta}{1-\beta^2}-\ln\frac{1+\beta}{1-\beta}\Big]. \tag{12.3}$$

The closed form agreed with the quadrature to $4.1\times10^{-14}$ at $\beta=0.1,0.5,0.9$. Then $r\to2$ as $\beta\to0$ ($r(10^{-3})=2.0000024$), so the mass implied at low velocity would be twice that of (12.2) for the same $V_{\rm disp}$. At finite $\beta$ the factor $r(\beta)/2$ is $1.0121$, $1.4083$ and $6.7173$ at $\beta=0.1,0.5,0.9$, against $\gamma=1.0050$, $1.1547$ and $2.2942$ (test T3): the Corollary's distribution, inserted in the derivation of Theorem 5, does not return $\gamma m_0$. In this book the Lorentz factor rests on the movement budget of Law V (Chapter 13, `law_V::gamma`), and Corollary 7.1 is recorded as a statement of the source that is not reproduced by the executed arithmetic (residual R12.2).

## 12.6 The engaged volume

The engine's Law IV goes beyond the paper. A form does not engage its whole exclusion boundary uniformly: the fraction of the projected phase demand at radius $r$ that the relay can lock is $f_{\rm lock}=\sqrt{r/b}$ inside a c-boundary $b$ (`relay_lock_fraction`, `laws.hpp:641`; FLM07, FLM15). Integrating over a sphere,

$$V_{\rm eng}=4\pi\!\int_0^br^2\sqrt{r/b}\,dr=\frac{8\pi}{7}b^3,\qquad V_{\rm wake}=\frac{4\pi}{3}b^3-V_{\rm eng}=\frac{4\pi}{21}b^3, \tag{12.4}$$

so $6/7$ of the sphere is engaged and $1/7$ is over capacity and emits a wake (`locked_engaged_volume_sphere`, `wake_volume_sphere`). Executed (T4): the quadrature gave $56.0998688141$ for $b=2.5$, equal to $8\pi b^3/7$ to $8.9\times10^{-16}$; the two volumes sum to $\tfrac{4\pi}{3}b^3$ and the locked fraction is $0.857142857143=6/7$. The resistance of an engaged volume is $(P_{\rm conv}/3)V_{\rm eng}$ (`resistance_from_engaged_volume`).

**The convergence floor.** Averaged over the sphere the resistance density is $\rho_{\rm eng}=[(P_{\rm conv}/3)V_{\rm eng}]/(Vc^2)=2P_{\rm conv}/(7c^2)=7.822953\times10^{30}$ kg m$^{-3}$, and the pressure gradient across a domain of boundary $R_{\rm CMB}$ is $P_{\rm conv}/(3R_{\rm CMB})$ (Chapter 4, Eq. 4.13). Their quotient is

$$a_{\rm floor}=\frac{|\nabla P|}{\rho_{\rm eng}}=\frac{7\,c^2}{6\,R_{\rm CMB}}=1.100606\times10^{-10}\ \text{m s}^{-2} \tag{12.5}$$

(the engine's `convergence_floor::acceleration`, equal to the closed form to $2.3\times10^{-16}$, T5). The result is COMPUTED, and not an independent cosmological prediction: $R_{\rm CMB}$ is an observed boundary (Chapter 6, R6.2). The engine records agreement with a low-acceleration floor of observed rotation curves at 8.28%, and the book treats the comparison in Chapter 38.

## 12.7 Binding as a reduced exclusion volume

When two or more forms synchronise into one, the joint exclusion volume can be smaller than the sum of the parts, and the resistance changes by

$$\Delta\mathcal R=\frac{P_{\rm conv}}{3}\,(V_{\rm joint}-V_{\rm parts}),\qquad V_{\rm parts}=\sum V_{\rm disp,i}, \tag{12.6}$$

negative for a saving (`synchrony_resistance_delta`). With the measured masses of the nuclei the volumes follow from (12.2), and (12.6) returns the binding:

| nucleus | $V_{\rm joint}$ (m³) | $V_{\rm parts}$ (m³) | reduction | fraction of $V_{\rm joint}$ $=B/(Mc^2)$ |
|---|---|---|---|---|
| deuteron | $3.663488\times10^{-58}$ | $3.667833\times10^{-58}$ | $4.345071\times10^{-61}$ | $1.186048\times10^{-3}$ |
| triton | $5.486445\times10^{-58}$ | $5.503012\times10^{-58}$ | $1.656683\times10^{-60}$ | $3.019592\times10^{-3}$ |
| helion | $5.485411\times10^{-58}$ | $5.500486\times10^{-58}$ | $1.507494\times10^{-60}$ | $2.748189\times10^{-3}$ |

Table 12.1. Exclusion volumes of the three-body nuclei, executed (test T6). $\Delta\mathcal R$ equalled $-B$ in joules to $4.5\times10^{-13}$ or better.

The label is CONSTRUCTION: both sides are built from the same measured masses, so the table shows that the identity "mass defect equals reduced exclusion volume" is applied consistently and not that the volumes are explained. It becomes a result when $V_{\rm joint}$ is computed from the geometry of the nucleus without the measured mass (Chapters 22 and 23; residual R12.3).

## 12.8 Response to a change of vector

The resistance to a change of velocity depends on whether the change is along the velocity or across it. The engine splits the acceleration relative to the velocity and divides the parallel part by $\gamma^3$ and the perpendicular part by $\gamma$ (`occlusion::law_v_response`, `law_V::gamma`). These factors follow from the movement budget and not from (12.1); Chapter 13 derives them.

## 12.9 Input ledger and residuals

| quantity | role | label |
|---|---|---|
| $m=\Phi V_{\rm disp}/(3\ell_P^3c^2)$ | derived from P7, P10, P11 | DERIVED given P7 and P11 |
| $V_{\rm disp}$ of the proton, electron | from measured masses | COMPUTED (output), carrying the measured masses and $\Phi$ |
| factor 3 against 6 | sensitivity | reported |
| engaged volume $8\pi b^3/7$ and wake $4\pi b^3/21$ | relay-lock integral | DERIVED (exact) given $f_{\rm lock}$ |
| $a_{\rm floor}=7c^2/(6R_{\rm CMB})$ | convergence floor | COMPUTED, conditioned on $R_{\rm CMB}$ |
| nuclear volumes of Table 12.1 | from measured masses | CONSTRUCTION |

**Residuals.**

* **R12.1 — momentum of the content.** P7 is assumed (Chapter 9, R9.1); the derivation of (12.2) rests on it.
* **R12.2 — two dipoles.** The Complete Laws state the first-order dipole of the arrival twice, with coefficients that differ by a factor 2 (Eq. 3.1 and Corollary 7.1), and the Corollary's distribution does not return $\gamma$. A single statement of the distribution, with its derivation, is outstanding. If the Corollary's dipole were the correct one, every $V_{\rm disp}$ obtained from a measured mass would halve.
* **R12.3 — an independent exclusion volume.** A $V_{\rm disp}$ from geometry and dynamics without the target mass (Chapter 1, R1.2).
* **R12.4 — equivalence.** The identity of inertial and gravitational mass needs the shadow of a body to be set by its $V_{\rm disp}$; the two proton volumes of the engine differ by $10^{13}$ (Chapter 49).
* **R12.5 — which share.** The share 1/3 against 1/6 for the boundary of the engaged volume (Chapter 9, R9.4) changes every exclusion volume by a factor 2.
* **R12.6 — first order.** The derivation is first order in $v/c$; the speed limit from the trailing hemisphere extrapolates it to $v=c$.

## 12.10 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch12_displacement_and_resistance
```

Criteria were registered in `Textbook/validation/ch12_PRE_REGISTRATION.md` before the instrument existed. Run 1 met every criterion except T1, whose registered test condition ($v=1$ m/s) could not be resolved against the cancelling monopole sum; the condition was repaired to $v=0.01\,c$ with the criterion unchanged. Run 2 (`ch12_run2_output.txt`) is the run of record and met every criterion.

## 12.11 Exercises and answers

**Exercise 1.** Show $\oint(\vec v\cdot\hat n)\hat n\,d\Omega=\tfrac{4\pi}{3}\vec v$.

*Answer.* By symmetry the integral is $A\vec v$. Contract with $\vec v$: $\oint(\vec v\cdot\hat n)^2d\Omega=v^2\cdot2\pi\int_{-1}^1\mu^2d\mu=\tfrac{4\pi}{3}v^2$, so $A=4\pi/3$.

**Exercise 2.** Derive (12.2) from (12.1).

*Answer.* $\vec p=\dfrac{V}{\ell_P^3c}\dfrac{\Phi}{4\pi}\Big(0+\dfrac{1}{c}\dfrac{4\pi}{3}\vec v\Big)=\dfrac{\Phi V}{3\ell_P^3c^2}\vec v$.

**Exercise 3.** Show that the locked and wake fractions of a sphere are $6/7$ and $1/7$.

*Answer.* $4\pi\int_0^br^{5/2}b^{-1/2}dr=4\pi\cdot\tfrac27b^3=\tfrac{8\pi}{7}b^3$. Dividing by $\tfrac{4\pi}{3}b^3$ gives $6/7$, and the remainder is $1/7$.

**Exercise 4.** Find the fractional exclusion-volume reduction of the deuteron.

*Answer.* $B/(M_dc^2)=2.2246\ \text{MeV}/1875.6\ \text{MeV}=1.186\times10^{-3}$ (Table 12.1).

**Exercise 5.** Show that the first-order dipole coefficients of $1+\beta\mu$ and $(1-\beta\mu)^{-2}$ differ by a factor 2.

*Answer.* To first order $(1-\beta\mu)^{-2}\approx1+2\beta\mu$. The normalised dipole of $1+c\beta\mu$ is $c\beta/3$, so $c=1$ and $c=2$ give $\beta/3$ and $2\beta/3$.

**Exercise 6.** By what factor does $R_{\rm excl}$ change if the numerical factor of Law IV is 6 and not 3?

*Answer.* $V_{\rm disp}$ doubles and $R_{\rm excl}\propto V^{1/3}$ rises by $2^{1/3}=1.2599$.

## 12.12 Scope

Established in this chapter: the derivation of the inertial mass from the dipole, with its arithmetic reproduced to $10^{-14}$; the factor-2 discrepancy between the source's two statements of the dipole and the fact that the Corollary's distribution does not return $\gamma$; the engaged and wake volumes of the relay lock and the convergence floor; and the consistent reading of the nuclear mass defects as reduced exclusion volumes.

Not established: the premise that content carries momentum equal to its density over $c$ (R12.1), a single statement of the distribution (R12.2), an independent exclusion volume (R12.3), the equivalence of inertial and gravitational mass as an executed result (R12.4), and the traction share at the boundary of the engaged volume (R12.5).

*Where it leads.* Chapter 13 derives the factors $\gamma^3$ and $\gamma$ and the Lorentz factor from the movement budget. Chapter 23 computes nuclear binding. Chapter 49 treats equivalence.
