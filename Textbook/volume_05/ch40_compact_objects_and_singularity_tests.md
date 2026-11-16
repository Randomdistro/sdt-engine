# Chapter 40 — Compact Objects and Singularity Tests

*Volume V — Bodies, Fields and Propagation.*
Draft of 10 November 2026. Notation: $\mathrm{Om}$ is the source length of the object; $\delta=r-\mathrm{Om}$; $z=\mathrm{Om}/r$ a defined geometric ratio (author's ruling of 2026-11-03); $c_{\rm far}=c(1-z)^2$ the engine's far-frame relay speed and $C=1-z$ the tick-rate ratio of the same closure (`depth_closure`). Executable companion: `Textbook/examples/ch40_compact_objects_and_singularity_tests.cpp`; pre-registration and captured output in `Textbook/validation/`. The chapter establishes the structure of the strong-depth branch under stated premises. It does not establish an interior law, a finite stress or a continuation, and no measured compact object is compared.

## 40.1 The exterior branch is not an interior solution

The circular law $v=c\sqrt{\mathrm{Om}/r}$ (`depth_closure::v_bound`) reaches $v=c$ at $r=\mathrm{Om}$, and its extrapolation exceeds $c$ for $r<\mathrm{Om}$. **Executed (T1).** $v/c=1$ at $r=\mathrm{Om}$ and $2$ at $r=\mathrm{Om}/4$ exactly (to round-off), $v/c>1$ at $r/\mathrm{Om}=0.9,0.5,0.1,0.01$, and the engine's function equals $c\sqrt{\mathrm{Om}/r}$ to $2.2\times10^{-16}$. The calculation marks a boundary of the circular branch. Inside it the actual construction may change route topology, cease circular propagation, exchange angular impulse or admit a different interior response. An axial line can have vanishing transverse motion even where a circular extrapolation diverges.

**A conditionally regular interior.** An extended symmetric source whose enclosed source length scales as $\varpi_{\rm enc}(r)=\varpi(r/R)^3$ has the radial acceleration $c^2\varpi r/R^3$: linear in $r$ near and through the centre, finite everywhere. **Executed (T2).** A radial oscillation through the centre with $\omega^2=c^2\varpi/R^3$, started at rest at $r=R$ and integrated over three periods by RK4, has period $2\pi/\omega$ to $1.6\times10^{-12}$ and speed $\omega R$ at the centre to $9\times10^{-15}$; the acceleration at $r=10^{-2}R$ is $10^{-6}$ of the point-source value there. The result is a conditional interior regularity: it depends on the assumed $r^3$ scaling of the enclosed source and is not a derivation of any density profile.

## 40.2 Coordinate arrest

For $c_{\rm far}=c\,[1-\mathrm{Om}/r]^2$ and radial propagation $dr/dt=-c_{\rm far}$, set $r=\mathrm{Om}+\delta$. Then $\dot\delta=-c\,\delta^2/(\mathrm{Om}+\delta)^2\approx-c\,\delta^2/\mathrm{Om}^2$ near the boundary, and the exact integral is

$$ct=\big[r+2\,\mathrm{Om}\ln\delta-\mathrm{Om}^2/\delta\big]_{r}^{r_0}\quad\Longrightarrow\quad\delta\simeq\frac{\mathrm{Om}^2}{ct}\ \ (\text{late times}). \tag{40.1}$$

The boundary is not reached in finite remote coordinate time. **Executed (T3).** The antiderivative was checked (V1): its derivative equals $r^2/(r-\mathrm{Om})^2$ to $10^{-8}$ (the first two runs used a step not scaled to the stiffness at $r=1.01\,\mathrm{Om}$, where the second repair left the worst case unchanged; the third, with a step proportional to $r-\mathrm{Om}$, is the run of record). With $c=\mathrm{Om}=1$, RK4 integration of $\dot\delta=-(\delta/(1+\delta))^2$ from $\delta_0=0.5$ reached $\delta=10^{-3}$ at $ct/\mathrm{Om}=1010.928216$, equal to the exact difference of (40.1) to $3\times10^{-14}$; and $\delta\,ct/\mathrm{Om}^2=1.06594,\ 1.01103,\ 1.00156$ at $ct/\mathrm{Om}=10^2,10^3,10^4$, approaching 1 as (40.1) requires. The coordinate time to reach $\delta=10^{-6}\mathrm{Om}$ would be $1.0\times10^{6}\,\mathrm{Om}/c$: the time grows as $1/\delta$.

**Local duration.** The tick-rate ratio is $C=1-z=\delta/(\mathrm{Om}+\delta)$, and the accumulated local duration along this assumed radial path is $\tau=\int C\,dt=\big[\mathrm{Om}\ln\delta+\delta\big]/c$ (exact), which diverges logarithmically: each decade of $\delta$ adds $\mathrm{Om}\ln10/c$. **Executed (T3).** The numerical integral of $C\,dt$ from $\delta_0=0.5$ to $10^{-3}$ is $6.713608\,\mathrm{Om}/c$ against the closed form, to $1.7\times10^{-8}$ relative; the increment per decade at small $\delta$ equals $\ln10$ to $4\times10^{-5}$. The coordinate time to the same point is $1010.93\,\mathrm{Om}/c$ and the local duration $6.71\,\mathrm{Om}/c$: the divergence in the remote frame is a power law and in local duration a logarithm. The divergence establishes the remote-time barrier under the stated propagation law. It does not establish bounded local stress, and the clock and path premises must be retained: another body trajectory or relay-event law can give another cycle count.

## 40.3 Torque and continuation

For the circular family the specific angular momentum is $h=c\sqrt{\mathrm{Om}\,r}$, so $h=c\,\mathrm{Om}$ at $r=\mathrm{Om}$. A subsequent zero-angular-momentum axial state requires the transfer of the difference into the source circulation, the medium deformation or an outgoing transport; the total angular-impulse ledger supplies the test. A central orbit cannot lose nonzero angular momentum merely by relabelling the path as axial. **Executed (T4, printed).** The specific angular momentum that a continuation would have to transfer is $c\,\mathrm{Om}=4.4281\times10^{11}$ m$^2$/s for the source length of the Sun and $2.2893\times10^{22}$ m$^2$/s for the Milky Way's baryonic total (`milky_way::koppa_mw_m`). No continuation law, no exchange partner and no transport is supplied, so the ledger is stated and not closed.

## 40.4 The determining closure

A complete treatment needs an interior contact law with finite stress, explicit angular exchange and an admissible continuation or a justified arrest boundary. A finite numerical refusal (the engine's refusal of a step at contact, Chapter 15) or a vanishing coordinate speed alone completes neither proof: the first is a property of an integrator and the second of a coordinate time. The strong-depth fork of Chapter 39 ($c_{\rm far}=c(1-z)^2$ against $c(1-2z)$) enters here as well: the arrest result (40.1) is stated for the active branch; for the alternative branch the divergence of the coordinate time is of a different form.

## 40.5 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $v=c\sqrt{\mathrm{Om}/r}$, $c_{\rm far}$, $C$ | `depth_closure` | the engine's relations (repaired, GOM22) |
| (40.1), $\tau$, interior oscillation | Sections 40.1–40.2 | DERIVED (exact), checked by integration |
| $\mathrm{Om}_\odot$, $\varpi_{\rm bar}$ | `bridge::koppa_Sun`, `milky_way::koppa_mw_m` | MEASURED-INPUT (stored $R_\odot/k_\odot^2$, $k_\odot=686.3$; Chapter 39 ledger) / the engine's stored total |
| $c\,\mathrm{Om}$ values | Section 40.3 | COMPUTED |

**Residuals.**

* **R40.1 — the interior law.** No interior contact law is supplied; the $r^3$ scaling of the enclosed source in Section 40.1 is an assumption.
* **R40.2 — stress.** Finite stress at the boundary is not shown; only the coordinate-time barrier under the stated propagation law is.
* **R40.3 — angular exchange.** The partner and mechanism of the angular-impulse transfer are not specified.
* **R40.4 — premises.** The radial path, the null-speed propagation and the tick-rate ratio $1-z$ are premises; other trajectories or event laws can give other cycle counts.
* **R40.5 — the branch.** The result is stated for the active profile; the alternative branch is not treated.
* **R40.6 — observables.** No observable of a compact object (a shadow, a ringdown, an accretion luminosity) is computed or compared.

## 40.6 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch40_compact_objects_and_singularity_tests
```

Criteria were registered in `Textbook/validation/ch40_PRE_REGISTRATION.md` before the instrument existed. Run 1 met every criterion except the first V1 line, whose central-difference step was not scaled to the stiffness near $r=\mathrm{Om}$; run 2's repair left the worst case unchanged (the new step equalled the old one there) and run 3 applied a step proportional to $r-\mathrm{Om}$. Run 3 (`ch40_run3_output.txt`) is the run of record and met every criterion; runs 1 and 2 are kept.

## 40.7 Exercises and answers

**Exercise 1.** Verify (40.1) by differentiation.

*Answer.* $d/dr[r+2\mathrm{Om}\ln(r-\mathrm{Om})-\mathrm{Om}^2/(r-\mathrm{Om})]=1+2\mathrm{Om}/\delta+\mathrm{Om}^2/\delta^2=(\delta+\mathrm{Om})^2/\delta^2=r^2/\delta^2$, which is $1/(1-\mathrm{Om}/r)^2$.

**Exercise 2.** Derive $\tau=(\mathrm{Om}\ln\delta+\delta)/c$.

*Answer.* $C\,dt=(\delta/r)\,r^2d\delta/(c\,\delta^2)=(\mathrm{Om}+\delta)\,d\delta/(c\,\delta)$, which integrates to $(\mathrm{Om}\ln\delta+\delta)/c$.

**Exercise 3.** What is the speed at the centre of the uniform-density interior?

*Answer.* $\omega R=\sqrt{c^2\varpi/R}$: the circular speed at the surface.

**Exercise 4.** By what factor does the coordinate time to reach $\delta$ grow when $\delta$ falls by 1000?

*Answer.* About 1000 ($t\propto1/\delta$), while the local duration grows by $\mathrm{Om}\ln1000/c=6.9\,\mathrm{Om}/c$.

**Exercise 5.** Compute $c\,\mathrm{Om}$ for $\mathrm{Om}=1477.0$ m.

*Answer.* $2.998\times10^8\times1477.0=4.43\times10^{11}$ m$^2$/s.

**Exercise 6.** Why does a vanishing coordinate speed not prove a finite stress?

*Answer.* The coordinate speed is a property of the chosen time; the stress is a property of the interior contact law, which is not supplied.

## 40.8 Scope

Established: the circular branch reaches $c$ at $r=\mathrm{Om}$ and its extrapolation exceeds $c$ inside; a symmetric extended source with enclosed length $\propto r^3$ is regular through the centre; under $c_{\rm far}=c(1-\mathrm{Om}/r)^2$ the boundary is not reached in finite remote coordinate time (exact integral, $\delta\simeq\mathrm{Om}^2/ct$) while the local duration diverges only logarithmically; and the angular-impulse ledger at $r=\mathrm{Om}$ is $c\,\mathrm{Om}$.

Not established: an interior contact law and finite stress (R40.1, R40.2), the angular exchange (R40.3), the premises (R40.4), the alternative branch (R40.5) and any observable of a compact object (R40.6).

*Where it leads.* Volume VI turns to coupled ratios and pressure history: the state coordinate and its relations, thermal recurrence and its octaves, the pressure-origin redshift, the Clearing landmarks and elapsed recurrence (Chapters 41 to 48).
