# Chapter 26 — Quantisation by Recurrence

*Volume IV — Atomic Recurrence, Spectra and Material Organisation.*
Draft of 10 November 2026. Notation: as Chapter 25 ($\mathrm{Om}=R/k^2$, $k=c/v$, $z=\mathrm{Om}/r$ as a defined ratio). $J=mvr$ is the action-like seat of a circular route. Executable companion: `Textbook/examples/ch26_quantisation_by_recurrence.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 26.1 The physical question

A persistent circulation must close its phase after an integer recurrence. The question is what that closure fixes, and what it leaves undetermined. The chapter derives the discrete ladder from closure, shows that integer closure by itself produces a ladder for kernels of every exponent, including kernels for which no route persists, and so states what a quantisation argument must contain beyond counting integers. Comparison with Bohr outcomes is made only after the native derivation, and no measured spectrum is loaded.

## 26.2 Discrete admissibility

In a simple circular branch an action-like seat $J_n=nJ_1$ is a closure condition. With $J\propto vr$ and $v^2r=c^2\mathrm{Om}$ at fixed source $\mathrm{Om}$ and fixed seat scale,

$$r_n\propto n^2,\qquad v_n\propto\frac1n. \tag{26.1}$$

This deduction is conditional on the phase integral producing $J\propto vr$ and on the same source state across the ladder. With $r_n=n^2a_0/Z$ and $v_n=Z\alpha c/n$ the circulation energy scale is $\tfrac12m_ev_n^2=\tfrac12m_e\alpha^2c^2Z^2/n^2$, and the engine's ladder energy is its negative, $E_n=-\mathrm{Ry}\,Z^2/n^2$.

**Executed (T1).** Over $Z=1\ldots5$, $n=1\ldots10$: $r_n/r_1=n^2$ to $2.2\times10^{-16}$, $v_n/v_1=1/n$ to $1.1\times10^{-16}$, $m_ev_nr_n=n\hbar$ to $5.2\times10^{-12}$ and $\tfrac12m_ev_n^2=\mathrm{Ry}Z^2/n^2$ to $1.1\times10^{-11}$. The last two are **shared-input**: $\hbar=m_e\alpha ca_0$ and $\mathrm{Ry}=\tfrac12m_e\alpha^2c^2$ are relations among the stored CODATA entries, so they check the set and are not independent evidence. The engine exposes two spectral routes, routines consuming the stored $\mathrm{Ry}$ and `emission_wavelength_m` consuming $R_\infty^{\rm derived}=m_ec\alpha^2/(2h)$; the second rebuilds the scale from invariants and consumes no measured line energy. The distinction stays in the equation ledger. Removing further measured invariants needs its own contact derivation; it is not a claim that the derived-scale route is absent.

## 26.3 Why discreteness is not enough

An integer closure equation can admit routes for many kernels. Take a central acceleration $a=-r^{-p}$ (Chapter 17) with unit constants: the circular speed is $v^2=r^{1-p}$ and $J=vr=r^{(3-p)/2}$, so $J=n$ gives

$$r_n=n^{2/(3-p)}. \tag{26.2}$$

For $p=2$ this is $n^2$; for $p=1$ it is $n$; for $p=2.9$ it is $n^{20}$; for $p=3.5$ it is $n^{-4}$. **Executed (T2).** The radius found by bisection from $J=n$ equalled (26.2) to $1.8\times10^{-15}$ for $p=1,1.5,2,2.5,2.9$ and $n=1\ldots8$ (radii for $n=1\ldots4$: $1,4,9,16$ at $p=2$; $1,2,3,4$ at $p=1$; $1,\,1.05\times10^{6},\,3.49\times10^{9},\,1.1\times10^{12}$ at $p=2.9$). The radial response of Chapter 17 has $\kappa^2/\omega^2=3-p$: real for all five, so each of these routes is a stable circulation, and imaginary for $p=3.5$, where (26.2) still yields a ladder ($r_n=n^{-4}$) although no route persists. Closure is therefore necessary and not sufficient. A quantisation proof contains three things: the admissible states (closure), their stability (a restoring response, with competing modes excluded) and a transition operator. Counting integers without an energy selector does not explain occupancy.

## 26.4 The transition ledger

For the hydrogenic ladder, the energy of a transition is $\Delta E=E_{\rm seat}Z^2\big(n_{\rm low}^{-2}-n_{\rm high}^{-2}\big)$, with the wavelength from the declared present metrological bridge $hc/\Delta E$. In a varying-pressure epoch the emitted recurrence and the observer's conversion need the separate response of Chapters 41–47, not a changing $c$ inserted only into that last conversion.

**Executed (T3).** For $Z=1\ldots4$ and all $1\le n_1<n_2<n_3\le12$, $\Delta E(n_1\to n_3)=\Delta E(n_1\to n_2)+\Delta E(n_2\to n_3)$ to $2.2\times10^{-16}$ (the Ritz combination, exact because the ladder is a difference of one function of $n$); the series limit equals $\mathrm{Ry}Z^2/n^2$ to $2.2\times10^{-16}$ at $n_{\rm high}=10^5$; and $\Delta E\propto Z^2$ to $2.2\times10^{-16}$. The combination rule holds for any ladder $E_n$, so it is not evidence for this particular one.

## 26.5 A limit of the leading-order ladder

The ladder speed $v_{Z1}=Z\alpha c$ stays below $c$ only for $Z<1/\alpha=137.036$. **Executed (T4).** The largest integer $Z$ with $Z\alpha<1$ is $137$, and $(Z\alpha)^2$ at $Z=137$ is $0.999475$. The leading-order closure is a statement of the circulation at speeds well below $c$; where $Z\alpha$ approaches 1 the omitted movement-budget terms of Chapter 27 are of order unity and the ladder is not a description of the state (residual R26.3). The limit is a property of the leading-order ladder and is not claimed to be a limit on nuclei.

## 26.6 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| (26.1), (26.2) | Sections 26.2–26.3 | DERIVED (exact), conditional on $J\propto vr$ and fixed source |
| $\hbar$, $\mathrm{Ry}$ identifications | Section 26.2 | shared-input (CODATA set) |
| $R_\infty^{\rm derived}$ route | engine's | COMPUTED from $\{m_e,c,\alpha,h\}$ |
| Ritz combination, limits | Section 26.4 | DERIVED (exact) |
| $Z<1/\alpha$ | Section 26.5 | COMPUTED |

**Residuals.**

* **R26.1 — the recurrence seat.** The seat $J_1$ is taken from the stored set; deriving it from contact mechanics is outstanding.
* **R26.2 — stability and selection.** Stability of each rung and the exclusion of competing modes are not derived for the electron construction (R17.1); no selection rule or transition operator is supplied.
* **R26.3 — the leading-order domain.** Corrections of order $(Z\alpha/n)^2$ are omitted (Chapter 27).
* **R26.4 — the epoch.** The varying-pressure conversion is not executed here.

## 26.7 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch26_quantisation_by_recurrence
```

Criteria were registered in `Textbook/validation/ch26_PRE_REGISTRATION.md` before the instrument existed. Run 1 met every criterion except two clauses of T2, whose root finder used too small a bracket for $p=2.9$ and the wrong direction for $p=3.5$; the instrument was repaired without changing the criteria. Run 2 (`ch26_run2_output.txt`) is the run of record and met every criterion.

## 26.8 Exercises and answers

**Exercise 1.** Derive (26.1).

*Answer.* $J=mvr=nJ_1$ and $v^2=c^2\mathrm{Om}/r$ give $mr\,c\sqrt{\mathrm{Om}/r}=nJ_1$, so $\sqrt r=nJ_1/(mc\sqrt{\mathrm{Om}})$ and $r\propto n^2$; then $v\propto r^{-1/2}\propto1/n$.

**Exercise 2.** Derive (26.2).

*Answer.* $v^2=r^{1-p}$ gives $J=vr=r^{(3-p)/2}=n$, so $r=n^{2/(3-p)}$.

**Exercise 3.** Show the Ritz combination.

*Answer.* $E_n=-f(n)$ gives $E_{n_3}-E_{n_1}=(E_{n_2}-E_{n_1})+(E_{n_3}-E_{n_2})$.

**Exercise 4.** For which $p$ does the closure ladder grow slower than $n^2$?

*Answer.* $r_n=n^{2/(3-p)}$ has exponent below 2 when $3-p>1$, i.e. $p<2$.

**Exercise 5.** Why does closure at $p=3.5$ not give a persistent route?

*Answer.* $\kappa^2/\omega^2=3-p<0$: a radial perturbation grows exponentially.

**Exercise 6.** Why is the limit $Z<1/\alpha$ not a limit on nuclei?

*Answer.* It follows from $v=Z\alpha c<c$ for the leading-order ladder; it concerns the route speed of an electron circulation about $Z$ units.

## 26.9 Scope

Established: the ladder (26.1) as a consequence of closure under stated conditions; the kernel family (26.2) showing that closure alone yields ladders for unstable kernels; the exact combination rule and series limits; the limit $Z<1/\alpha$ of the leading-order ladder.

Not established: the recurrence seat from contact mechanics (R26.1), stability, selection and a transition operator (R26.2), and the corrections beyond leading order (R26.3).

*Where it leads.* Chapter 27 treats the corrections to the leading ladder: the power counting of fine structure, finite nuclear size and hyperfine coupling.
