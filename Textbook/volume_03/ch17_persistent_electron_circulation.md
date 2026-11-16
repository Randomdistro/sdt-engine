# Chapter 17 — Persistent Electron Circulation

*Volume III — Persistent Structures and Nuclear Construction.*
Draft of 9 November 2026. Notation: $\Omega_{\rm H}$ is not used; the hydrogen boundary length is written $r_e$ as in the engine, with $r_e=\alpha^2a_0$ (the length $\mathrm{Om}=R/k^2$ of `Textbook/NOTATION_LEDGER.md` at the hydrogen rung $k_{\rm H}=1/\alpha$, $v_{\rm H}=\alpha c$). Durations are counts of a declared circulation. Executable companion: `Textbook/examples/ch17_persistent_electron_circulation.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 17.1 The physical question

The electron is a persistent circulating deformation of the contact medium with an exclusion boundary and a phase recurrence. The question of this chapter is what a statement of *persistence* requires. A closed route drawn on paper satisfies none of the conditions of persistence. Persistence requires an equilibrium, a closure of phase over the route, and a computed response to small departures from both, all fixed by the same law. The chapter separates three things the sources keep apart: the **route** (a length at which circulation is observed), the **boundary** (a length at which the circulation speed reaches the engine's c-boundary), and the **interaction radius** (a length that sets the external force law). It then executes the method of equilibrium plus response on the one central kernel the engine supplies, and states what the engine does not supply.

## 17.2 The hydrogen rung

The engine's hydrogen rung is $v_{\rm H}=\alpha c$ at the route $a_0$, with $k_{\rm H}=c/v_{\rm H}=1/\alpha$ and boundary length

$$r_e=\alpha^2a_0\qquad(\texttt{measured::r\_e},\ \texttt{laws.hpp:142}),\qquad \text{so that}\quad v_{\rm H}^2\,a_0=c^2\,r_e. \tag{17.1}$$

Equation (17.1) says that at the hydrogen route the product of the squared circulation speed and the route radius equals $c^2$ times a fixed length. For the circulation ladder of the engine, $v_{Zn}=Z\alpha c/n$ and $r_{Zn}=n^2a_0/Z$ (`atomic::bohr_velocity`, `atomic::bohr_radius`, `laws.hpp:1556–1563`), the same product is

$$v_{Zn}^2\,r_{Zn}=Z\,\alpha^2c^2a_0=Z\,c^2r_e\quad\text{for every }n, \tag{17.2}$$

so the boundary length is the same at every $n$ of one $Z$. The phase closure on the route, $m_ev_{Zn}r_{Zn}=n\hbar$, holds with $\hbar=m_e\alpha c\,a_0$, and the circulation period $T_{Zn}=2\pi r_{Zn}/v_{Zn}$ scales as $n^3/Z^2$.

**Executed (T1, T2).** The stored lengths are $a_0=5.29177210544\times10^{-11}$ m, $\bar\lambda_C=\hbar/(m_ec)=3.861592674\times10^{-13}$ m and $r_e=2.817940320\times10^{-15}$ m, in the ratios $a_0:\bar\lambda_C:r_e=1:\alpha:\alpha^2$ (with $a_0/r_e=18778.865071$). The circulation rate $\alpha c/a_0=4.134137333\times10^{16}$ rad s$^{-1}$ equals the engine constant `law_VI::winding::omega_electron_locked` to $10^{-14}$. Over the 50 states $Z=1\ldots5$, $n=1\ldots10$, the product $v^2r/(c^2Zr_e)$ equalled 1 to $3.3\times10^{-16}$, the period ratio $T_{Zn}/T_{11}$ equalled $n^3/Z^2$ to $2.2\times10^{-16}$, and the phase closure $m_evr/(n\hbar)$ equalled 1 to $5.2\times10^{-12}$.

**What these identities show.** $r_e=\alpha\hbar/(m_ec)$ agrees with the stored $\alpha^2a_0$ to $5.2\times10^{-12}$, and the phase closure to the same figure. Both are consequences of the relations among $\alpha$, $a_0$, $m_e$ and $\hbar$ in the CODATA set (the stored $a_0$ is itself derived from the other three), so they are **shared-input** and test the internal consistency of the stored set. They are not independent evidence for the hydrogen rung. The engine's statement that $\alpha$ is hydrogen's koppa rung $k_{\rm H}=1/\alpha$ is a premise of the framework recorded in the derivelist (residual R17.3); the numbers above do not test it.

## 17.3 Three lengths, kept apart

| length | value | role |
|---|---|---|
| $a_0$ | $5.291772105\times10^{-11}$ m | route: the radius at which the circulation speed is $\alpha c$ |
| $r_e$ | $2.817940320\times10^{-15}$ m | boundary: where the circulation speed reaches the c-boundary (17.1) |
| $\sqrt{R_{p,\rm lock}\,r_e}$ | $1.539659647\times10^{-15}$ m | interaction radius of the engine (`laws.hpp:514`), with $R_{p,\rm lock}=4\hbar/(m_pc)=8.412356402\times10^{-16}$ m |

Table 17.1. The three lengths, executed (T5). Their pairwise ratios are $a_0/r_e=18778.87$ and $r_e/R_{\rm int}=R_{\rm int}/R_{p,\rm lock}=1.8302$ (the last two coincide because $R_{\rm int}$ is the geometric mean).

The three lengths differ by factors well above 1.5 pairwise. A calculation that set them equal would impose a geometric result before solving the construction. The engine's picture is not an electron sphere of radius $r_e$ circulating about an independent point source: the persistent source and the responding circulation take part in one contact network. A fourth length, an operationally inferred spectral radius, would need a spectral observable and an inference chain; none is loaded here (residual R17.5).

**The electron's own extent.** *Added 16 November 2026; values evaluated directly, no registered instrument yet (residual R17.7).* None of the three lengths of Table 17.1 is the electron. $r_e$ is hydrogen's c-boundary: it is thrown off by the pair, by the same expression that gives the c-boundary of a planetary system, and it is not the electron or its size (author's statement of 16 November 2026). The sources do not hold one statement of the electron's own extent. They hold three, which disagree:

| source | statement | value |
|---|---|---|
| `law_IV::R_excl_e` | radius of a sphere of the Law IV exclusion volume $V_{\rm disp,e}=3m_ec^2/P_{\rm conv}$ | $2.877582\times10^{-21}$ m (COMPUTED; carries $m_e$, the stored $\ell_P$ and $R_{\rm CMB}$) |
| `law_IV::electron_radii` | lists $r_e$ as the electron's boundary radius | $2.817940\times10^{-15}$ m; this is hydrogen's c-boundary (Chapter 1, R1.7) |
| `mass_ratio` (tube-volume construction) | a "point electron" whose physical tube radius $b_e$ is a free argument | no value; the header notes that the body width does not affect the volume ratio |

An early investigation (CQ02) gives a torus of minor radius $\sqrt2\,\hbar/(m_ec)=5.4611\times10^{-13}$ m; it is a fourth, different, value and was not re-examined. The only computed body size is therefore the exclusion radius, and it inherits the cosmological boundary through $P_{\rm conv}$.

On that surface the confining load can be defined in more than one way, and the definitions differ by an order of magnitude: the rest energy over the radius, $m_ec^2/R_{\rm excl,e}=28.45$ MN; the Law IV pressure $P_{\rm conv}/3$ on the cross-section $\pi R_{\rm excl,e}^2$, $21.34$ MN; and the rest energy over $4\pi R_{\rm excl,e}$, equal to $(P_{\rm conv}/9)R_{\rm excl,e}^2$, $2.264$ MN (COMPUTED). Which of these, if any, is the confinement force of the lepton is not fixed by the sources read for this edition (residual R17.7).

## 17.4 The determining problem

Let $X$ collect the route shape, the phase, the cross-sectional deformation and the surrounding relay response. Persistence requires

$$T[X]=0,\qquad C[X]=2\pi n, \tag{17.3}$$

the balance of contact traction on the construction and the closure of phase over the route. Linearise (17.3) about a solution $X_0$: $T'[X_0]\,\xi=0$ and $C'[X_0]\,\xi=0$ define the admissible perturbations $\xi$. After removing the constraint directions the remaining small-displacement problem has the form $M_{\rm eff}\ddot q+K_{\rm eff}q=0$ in an effective coordinate $q$, and its frequency is $\sqrt{K_{\rm eff}/M_{\rm eff}}$. Two requirements follow. Both coefficients must come from the same deformation response: Law IV fixes $M_{\rm eff}$ through the engaged displacement and the restoring traction fixes $K_{\rm eff}$. And a frequency fitted to an observed transition and reinserted into $T$ is not a prediction.

## 17.5 The method executed on the point-source kernel

The only central kernel the engine supplies is the point-source $1/r^2$ form of Eq. (15.3). Exact to contact for finite spheres (Chapter 10), it applies at the hydrogen route, where $a_0/R_{p,\rm lock}\approx6\times10^4$. To see what the method gives, and what a drawn route does not, consider a central acceleration $a=-r^{-p}$ along the line of centres, with unit route radius and unit speed (so $\omega=1$), and angular momentum $L=r^2\dot\varphi$. The radial equation is $\ddot r=L^2/r^3-r^{-p}$. A circular route exists at $r=1$ for **every** exponent $p$. Linearising about it with $L$ fixed,

$$\delta\ddot r=-\big(3L^2/r_0^4-p\,r_0^{-p-1}\big)\delta r\ \Rightarrow\ \kappa^2=(3-p)\,\omega^2. \tag{17.4}$$

The route is stable (an oscillation) for $p<3$, marginal at $p=3$ (linear drift), and unstable for $p>3$ (exponential growth). At $p=2$, $\kappa=\omega$: the radial and the azimuthal circulation have the same frequency, the route closes after each circuit, and there is no precession. Stability is therefore a statement about the exponent of the law, not about the existence of the route.

**Executed (T3, V1).** With a radial speed $\delta=10^{-6}$ at fixed $L$, RK4 with step $10^{-3}$ reproduced $\delta r(t)=\delta\sin(\kappa t)/\kappa$ for $p=1,\,2,\,2.9$ (with $\kappa=1.414214,\,1,\,0.316228$) at $t=1,2,3,5$ to $2.2\times10^{-6}$, $3.9\times10^{-6}$ and $3.7\times10^{-6}$ of $\delta/\kappa$. At $p=3$ the deviation at $t=6$ was $5.999999931\times10^{-6}$ against the predicted $6\times10^{-6}$. At $p=3.5$ the deviation at $t=6$ was $49.196\,\delta$ against the predicted $\delta\sinh(6\lambda)/\lambda=49.198\,\delta$ with $\lambda=\sqrt{0.5}$ (a growth of the route by a factor of about 49 in six counts). At $p=2$ the deviation was $4\times10^{-12}$ at $t=\pi$ and $-1.3\times10^{-14}$ at $t=2\pi$ (with a step $\pi/3000$ so that both are grid points; run 1 had placed the check at $t=3.142$ and is recorded in the pre-registration). The instrument was first checked on the isotropic oscillator, $p=-1$ ($\kappa=2\omega$), to $8.1\times10^{-7}$ of $\delta/2$ (V1).

## 17.6 The engine's kernel

The same result was checked on the engine's own integrator. `circular_pair` with $\varpi=(10^3,\,3\times10^3)$ m at $d=10^9$ m, with a relative radial speed $u=10^{-6}\omega d$ added (barycentre momentum kept zero) and `dynamics::step_rk4` with $T/4000$ steps, gave a separation obeying $\delta d(t)=(u/\omega)\sin\omega t$ at $T/8,\,T/4,\,3T/8,\,T/2$ to $3.8\times10^{-6}$ of $u/\omega$ (T4). The engine's two-body route therefore responds to a radial perturbation with the orbital frequency, as (17.4) requires at $p=2$.

This is the response of a *route* under a point-source kernel. It is not the response of the electron construction. The engine does not supply the operator $T[X]$ of (17.3) for the electron: it has no cross-section, no wake and no deformation response from which $M_{\rm eff}$ and $K_{\rm eff}$ could be computed (residual R17.1). The stability of the circulation of the real construction is therefore not established here, and the closure of the route at $p=2$ is a property of the kernel, not a proof of persistence.

## 17.7 External response

A directional perturbation of the surrounding relay modifies the wake and the route phase. Polarisation, scattering amplitude and transition rate are different observables of one response, and a common equilibrium geometry should predict all three without a separate adjustment of an effective radius for each measurement. None of the three is computed in this chapter (residual R17.4). The test the chapter sets for later chapters is stated here: one geometry, one response operator, three observables, and no per-observable length.

## 17.8 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $\alpha$, $a_0$, $\hbar$, $m_e$, $m_p$ | `measured::` (CODATA 2022) | MEASURED-INPUT (the relations among $\alpha$, $a_0$, $m_e$, $\hbar$ are shared-input) |
| $c$ | `measured::c` | MEASURED-INPUT (unit bridge) |
| $r_e=\alpha^2a_0$, (17.1), (17.2), $\omega=\alpha c/a_0$ | Section 17.2 | COMPUTED (defined in the engine; identities executed) |
| $R_{p,\rm lock}=4\hbar/(m_pc)$, $R_{\rm int}$ | engine's | the engine's lock premise (FLM07) with measured inputs; not re-derived here |
| epicyclic result (17.4) | Section 17.5 | DERIVED (exact) and COMPUTED |
| route parameters of T3, T4 ($\delta$, step, $\varpi$, $d$) | as stated | CONSTRUCTION |

**Residuals.**

* **R17.1 — the construction operator.** The operator $T[X]$ of the electron construction, its linearisation, $M_{\rm eff}$ and $K_{\rm eff}$ are not supplied by the engine. The stability of the persistent circulation is not established.
* **R17.2 — the effective coordinate.** Which coordinate $q$ carries the small oscillation, and how Law IV's engaged displacement fixes $M_{\rm eff}$ for it, is not computed.
* **R17.3 — the rung.** That $\alpha$ is hydrogen's koppa rung is a premise (derivelist); the identities of Section 17.2 are shared-input and do not test it.
* **R17.4 — external response.** Polarisation, scattering and transition observables are not computed.
* **R17.5 — the spectral radius.** An operationally inferred spectral radius is not entered: it requires a spectral observable and its inference chain.
* **R17.6 — beyond the point kernel.** The route closure at $p=2$ holds for the point-source kernel; finite size, the movement budget (Chapter 13) and the response of the construction can shift it.
* **R17.7 — the electron's own extent and its confining load.** The sources give three inconsistent statements of the electron's size (Section 17.3), and no recorded definition of the lepton's confinement force was found; the three candidate loads span $2.3$ to $28$ MN. One definition, with its derivation, is outstanding.

## 17.9 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch17_persistent_electron_circulation
```

Criteria were registered in `Textbook/validation/ch17_PRE_REGISTRATION.md` before the instrument existed. A first build failed on a namespace path and produced no run. Run 1 (`ch17_run1_output.txt`) met every criterion except the closure clause of T3, whose check point was misplaced on the time grid; the clause was repaired without changing its criterion. Run 2 (`ch17_run2_output.txt`) is the run of record and met every criterion.

## 17.10 Exercises and answers

**Exercise 1.** Derive (17.4).

*Answer.* With $L$ fixed, $\ddot r=L^2r^{-3}-f(r)$. At the route $L^2r_0^{-3}=f(r_0)=r_0^{-p}$. The derivative of the right side is $-3L^2r_0^{-4}-f'(r_0)=-3r_0^{-p-1}+p\,r_0^{-p-1}$, so $\kappa^2=(3-p)r_0^{-p-1}=(3-p)\omega^2$ since $\omega^2=f/r_0$.

**Exercise 2.** Show that $v_{Zn}^2r_{Zn}=Zc^2r_e$.

*Answer.* $v^2r=(Z\alpha c/n)^2(n^2a_0/Z)=Z\alpha^2c^2a_0=Zc^2r_e$.

**Exercise 3.** Show that $T_{Zn}/T_{11}=n^3/Z^2$.

*Answer.* $T=2\pi r/v=2\pi(n^2a_0/Z)(n/Z\alpha c)=2\pi n^3a_0/(Z^2\alpha c)$.

**Exercise 4.** Why is $R_{\rm int}/R_{p,\rm lock}$ equal to $r_e/R_{\rm int}$?

*Answer.* $R_{\rm int}=\sqrt{R_{p,\rm lock}r_e}$, so $R_{\rm int}^2=R_{p,\rm lock}r_e$.

**Exercise 5.** For $p=3.5$, how many counts does a radial deviation take to grow by a factor $e$?

*Answer.* The growth rate is $\lambda=\sqrt{p-3}\,\omega=0.7071\,\omega$, so one count of $1/\lambda=1.414$ in units of $1/\omega$ (once the exponential dominates).

**Exercise 6.** A route is found at every $p$. Why does that not establish persistence?

*Answer.* Persistence needs the linearised response to have restoring eigenvalues. For $p\ge3$ the radial response of the same route is marginal or grows (17.4), so the existence of the route says nothing about its stability.

## 17.11 Scope

Established in this chapter: the identities of the hydrogen rung and the circulation ladder as executed (with the shared-input qualification); the separation of route, boundary and interaction lengths; the epicyclic result (17.4), checked on a family of central kernels and on the engine's own integrator; and the statement of what the engine does not supply.

Not established: the operator $T[X]$ and the stability of the electron construction (R17.1, R17.2), the status of the rung (R17.3), the external-response observables (R17.4), the spectral radius (R17.5) and the effect of finite size and the movement budget on the route closure (R17.6).

*Where it leads.* Chapter 18 turns to the proton: the lock construction, the boundary radius and the wake closure. Chapters 20–24 take composite forms whose contacts, not a single route, carry the construction.
