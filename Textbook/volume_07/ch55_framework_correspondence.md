# Chapter 55 — Framework Correspondence

*Volume VII — Correspondence, Paradoxes and Discriminating Tests.*
Draft of 10 November 2026. Notation: $k=c/v$, $\mathrm{Om}=R/k^2$ (the engine's `koppa`), $z=\mathrm{Om}/r$ the defined depth ratio; provenance classes A (derived with no matched target input), B (shared-input: a shared measured input is named through its chain), C (calibrated), letters local to this chapter and distinct from the classes A to F of the two-axis audit of Chapter 5, where class C means convergent; discrimination classes "none known" (the same observable function) and "candidate" (different predictions at a stated scale, unmeasured here). Executable companion: `Textbook/examples/ch55_framework_correspondence.cpp`; pre-registration and captured output in `Textbook/validation/`. Inputs: $c$, $R_\odot$ and AU (IAU), and the stored $k_\odot=686.3$; the sidereal year was read after the native period was printed.

## 55.1 Same result, different derivation chain

The native orbital chain is $k=c/v$, $\mathrm{Om}=R/k^2$, $a=c^2\mathrm{Om}/r^2$. Conic motion follows under a stationary central response. The resemblance to the established orbital expressions is the consequence of obtaining the same observable dynamics; the chain does not extract a source mass or $G$ from the geometric length.

**Executed (V1, T1).** $\mathrm{Om}_\odot=R_\odot/k_\odot^2=1477.0459$ m. Computed before any measured year was read: the circular period at 1 AU is $T=2\pi\sqrt{r^3/(c^2\mathrm{Om}_\odot)}=365.2049$ d and the circular speed $c\sqrt{\mathrm{Om}/r}=29.7889$ km/s (equal to $2\pi r/T$ to $10^{-16}$). Read afterwards, the sidereal year $365.256363$ d differs from the native period by $-1.41\times10^{-4}$ relative, which is the effect of the four-digit stored $k_\odot$ on $\mathrm{Om}$ (a $+2.8\times10^{-4}$ difference, giving a period lower by half of it). The agreement is a convergence of an independently stated chain with a standard expression. It is not a discriminating result: the surface speed behind the stored $k_\odot$ is scaled from planetary orbital speeds (the engine records $v_{\rm surface}=v_{\rm Mercury}\sqrt{a/R_\odot}$), and the standard expression is fixed by the same orbital observations: a shared measured input that is named here (the period is COMPUTED, class B).

The movement budget $v_{\rm circ}^2+v^2=c^2$ gives $\gamma=[1-v^2/c^2]^{-1/2}$ and the energy–momentum relation under the adopted response premises. **Executed (T2).** $E^2-(pc)^2=(mc^2)^2$ for 20 speeds from $0.01c$ to $0.999c$ to $2.9\times10^{-16}$ relative to $E^2$ (to $4.9\times10^{-14}$ relative to the difference at $\beta=0.999$, where the two terms are near 500; the registered tolerance had ignored this cancellation, recorded in the pre-registration); $\gamma(0.6c)=1.25$; the photon limit $v_{\rm circ}=0$ gives $v=c$. Algebraic equivalence explains the correspondence; the physical question is whether contact mechanics supplies the premises and any further predictions.

## 55.2 Provenance and discrimination

A result can be independently derived and still non-discriminating between frameworks. Another can be discriminating but currently unmeasured. These axes stay separate. A shared measured input is named through its actual chain rather than inferred from the appearance of a familiar equation. Standard descriptions supply measurement conventions and comparison calculations without becoming privileged ontological starting points; conversely native terminology cannot make an inserted empirical coefficient a derived constant.

## 55.3 Where differences become testable, and the table

Candidate distinctions include material-dependent transfer, nonlinear shielding, stronger-depth propagation coefficients, topology-dependent rates and joint cross-sector response. Each needs a numerical observable and a matched-fidelity comparison. The correspondence table below carries the native derivation, the equivalent expression, the input dependencies, the retained approximation, and the two separate classes.

| observable | native derivation | equivalent expression | input chain | retained approximation | prov. | discrimination |
|---|---|---|---|---|---|---|
| circular period | $T=2\pi\sqrt{r^3/(c^2\mathrm{Om})}$, $\mathrm{Om}=R/k^2$ | $2\pi\sqrt{r^3/GM}$ | $\mathrm{Om}$ from the stored surface speed ratio, scaled from planetary orbital speeds (shared input) | point source, stationary central response | B | none known |
| circular speed | $v=c\sqrt{\mathrm{Om}/r}=c\sqrt z$ | $\sqrt{GM/r}$ | same $\mathrm{Om}$ (shared input) | circular state | B | none known |
| energy–momentum | movement budget; $\gamma$, $E=\gamma mc^2$ | special-relativistic kinematics | $c$ only (posited budget) | adopted response premises | A | none known |
| shift between depths | $z_e-z_o$ (A) or $(z_e-z_o)/(1-z_e)$ (B) | weak-field shift to first order | depths $\mathrm{Om}/r$ (defined ratio) | transport convention not derived | A | candidate: $0.4286$ at $z_e=0.3$; $2.1231\times10^{-6}$ at the solar surface |
| signal delay, second order | $c_{\rm far}=c(1-z)^2$ profile (Chapter 39) | first-order weak-field delay | $\mathrm{Om}_\odot$ (shared input) | second-order coefficient from the repaired profile | B | candidate (strong depth) |
| composite source strength | additive in baryon count | mass-proportional source | baryon count; $B_\alpha$ stored (rounded) | binding not entering the source | A | candidate: $6.897\times10^{-3}$ (alpha vs four protons) |
| plate-energy amplitude | mode price $a$ (Chapter 52) | ideal-plate value for $a=\tfrac12$ | $a$ calibrated | ideal plates, smooth cutoff | C | candidate (second observable with $a$ fixed) |
| registration statistics | threshold detector, Fano $\le1/(4\mu)$ (Chapter 50) | Poisson counting, ideal steady source | none (stand-in rule) | deterministic accumulation | A | candidate (a factor $\sim87$ in Fano factor) |

**Executed (T3).** The numbers in the candidate rows were computed here: the two redshift conventions differ by $0.428571$ at $z_e=0.3$ and by $2.12311\times10^{-6}$ at the solar surface (to $10^{-4}$ of the registered values); an alpha and four free protons differ in source strength by $6.8974\times10^{-3}$ between the baryon-count convention and a mass-proportional one. The eight rows populate all four combinations of provenance and discrimination: (A, none known) 1, (B, none known) 2, (A, candidate) 3, (B, candidate) 1 (the plate-energy row is class C). The first three rows are correspondences: same observable function, no discrimination. The candidate rows are where a measurement at the stated scale would separate the framework from its comparison expression; none was loaded here.

## 55.4 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| $c$, $R_\odot$, AU | `measured` | exact SI; IAU |
| $k_\odot=686.3$, $\mathrm{Om}_\odot$ | `bridge` | stored, four digits; surface speed scaled from planetary orbital speeds (named shared input); $\mathrm{Om}$ COMPUTED (class B) |
| sidereal year 365.256363 d | IAU | OBSERVED, read after the native period |
| $\gamma$, $E$, $p$ relations | `law_V` | posited movement budget; identities COMPUTED |
| candidate-row numbers | Section 55.3 | COMPUTED |

**Residuals.**

* **R55.1 — the shared input.** Planetary orbital speeds enter the stored $k_\odot$; the correspondence for periods and speeds cannot discriminate and is not offered as an independent prediction.
* **R55.2 — the table's candidates.** No measurement at the stated scale was loaded for any candidate row.
* **R55.3 — the premises.** Whether contact mechanics supplies the movement-budget premises beyond their adoption is not derived here.
* **R55.4 — stored $k_\odot$.** $k_\odot$ carries four digits; the resulting $2.8\times10^{-4}$ difference in $\mathrm{Om}$ is not a result.
* **R55.5 — matched fidelity.** The comparison expressions are first-order; a matched-fidelity comparison (same order) for the second-order rows is not made.

## 55.5 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch55_framework_correspondence
```

Criteria were registered in `Textbook/validation/ch55_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch55_run1_output.txt`) failed one criterion through a registration error (the energy–momentum tolerance ignored cancellation at high speed), recorded. Run 2 (`ch55_run2_output.txt`) is the run of record and met every criterion; the full table is in its output.

## 55.6 Exercises and answers

**Exercise 1.** Show that $c\sqrt{\mathrm{Om}/r}=2\pi r/T$ for the chain's period.

*Answer.* $T=2\pi\sqrt{r^3/(c^2\mathrm{Om})}$, so $2\pi r/T=\sqrt{c^2\mathrm{Om}/r}=c\sqrt{\mathrm{Om}/r}$.

**Exercise 2.** How much does a $2.8\times10^{-4}$ error in $\mathrm{Om}$ change the period?

*Answer.* $T\propto\mathrm{Om}^{-1/2}$, so $-1.4\times10^{-4}$.

**Exercise 3.** Why is the period not a discriminating result?

*Answer.* The input that fixes $\mathrm{Om}$ is the surface speed ratio scaled from planetary orbital speeds; the chain and the standard expression share those observations.

**Exercise 4.** Which rows of the table are candidate discriminators and why?

*Answer.* Those whose native expression departs from the comparison expression at a stated scale: the second-order depth conventions, composite source strength, the plate amplitude (once fixed), and registration statistics.

**Exercise 5.** What is $E^2-(pc)^2$ for $m=1$ kg at $0.999c$, in units $(mc^2)^2$?

*Answer.* $1$ (to $2.9\times10^{-16}$ relative to $E^2$); computing the difference directly leaves a relative error of $5\times10^{-14}$.

**Exercise 6.** How do provenance and discrimination differ for the energy–momentum row?

*Answer.* Provenance: class A, derived from the posited budget with no matched target input. Discrimination: none known, since the observable function is the same as the standard one.

## 55.7 Scope

Established: that the native chain and the movement budget reproduce the standard functions of the stated observables; the period and speed values from the stored $\mathrm{Om}_\odot$ with their input chain named; the table with provenance and discrimination as separate columns and the computed numbers of its candidate rows.

Not established: a discriminating measurement for any candidate (R55.2), the derivation of the movement-budget premises from contact mechanics (R55.3), a matched-fidelity comparison for second-order rows (R55.5).

*Where it leads.* Chapter 56 freezes a common kernel on one observable family and predicts another: the cross-domain tests of the hard-lock transport kernel and the optical–hydrodynamic invariants.
