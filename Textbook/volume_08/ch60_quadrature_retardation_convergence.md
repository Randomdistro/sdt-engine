# Chapter 60 — Quadrature, Retardation and Convergence

*Volume VIII — Executable Reference, Verification and Research Closure.*
Draft of 10 November 2026. Notation: $Q(h)$ a numerical result at resolution $h$; $E(h)=Q(h)-I$ its error against the exact value $I$; $\hat p$ the estimated order; $(n_r,n_\varphi)$ the radial and azimuthal node counts of the disc quadrature; $\epsilon$ the phase offset of the azimuth grid in cells; $n$ the number of retarded-time iterations; $v$ the source speed in units of $c$. Executable companion: `Textbook/examples/ch60_quadrature_retardation_convergence.cpp`; pre-registration and captured output in `Textbook/validation/`. Every integrand and motion is a constructed problem with a known answer (no measured input). The engine's six radial Gauss–Legendre nodes (`occlusion_sphere::radial_nodes`) are used at $n_r=6$.

## 60.1 Separate numerical errors

The total trajectory discrepancy can combine time integration, disc quadrature, channel representation, retardation tolerance and source-history interpolation. A single smaller timestep changes only some terms. Refinement should vary each numerical control independently before a plateau is interpreted.

For a smooth asymptotic error $E(h)=Ch^p$, three successive resolutions estimate

$$p=\log_2\left|\frac{Q(h)-Q(h/2)}{Q(h/2)-Q(h/4)}\right|. \tag{60.1}$$

The estimate is unreliable near cancellation, with discontinuous visibility, or where a different error dominates.

**Executed (V1, T1).** Composite Simpson on $e^x$ over $[0,1]$ with $n=8,16,32$ gives $\hat p=3.99789$ and the composite trapezoid rule gives $\hat p=1.99965$. Near cancellation the estimate fails: Simpson at $n=2^{14},2^{15},2^{16}$, where the successive differences are at rounding level, returns $\hat p=-0.939$, which misses 4 by $4.9$. For a step integrand $1[x<x_e]$ the trapezoid estimates were registered to be erratic (range above $0.5$ over eight refinements); that statement is **rejected**: the estimates are $1.0000$ at every one of the eight triples, and a post-run exploration (report only) gives $1.0000$ at all refinements for five other edge positions ($0.3$, $0.41$, $0.618034$, $0.707107$, $0.9$). For a step the estimator returns the true order of the error, 1, steadily; its unreliability in the chapter's text applies to a dominant error of another kind and to cancellation, not to this step. The slower, order-1 convergence itself is the point: contact and occultation events reduce the observed order of a quadrature (here from 2 or 4 to 1).

## 60.2 Phase-origin effects and independent controls

The spherical channel ring starts toward the pole; the older representation uses a least-aligned reference direction. An unshielded pair has enough symmetry to hide the phase origin in the exact integral. A blocker breaks that symmetry, and finite quadrature can retain a phase-dependent difference. Rotating the whole physical setup provides a covariance check.

**Independent controls (T2).** On the unit disc, with the engine's six radial nodes generalised to $n_r$ and $n_\varphi$ azimuth midpoints: for the smooth axisymmetric integrand $e^{-r^2}$ the error at $(6,16)$ is $4.2\times10^{-10}$ relative. For the shadow integrand $1[x<0.3]$ (exact area $2.1616707$, confirmed to $1.2\times10^{-15}$ by the smooth chord integral with $y=\sin\theta$; the first attempt to validate it by quadrature of the edge itself reached only $10^{-4}$, recorded):

| $(n_r,n_\varphi)$ | absolute error |
|---|---|
| $(6,16)$ | $4.941\times10^{-2}$ |
| $(6,256)$ | $1.154\times10^{-2}$ |
| $(96,16)$ | $4.589\times10^{-4}$ |
| $(96,256)$ | $2.259\times10^{-4}$ |

Refining the azimuth alone at $n_r=6$ leaves a floor of $1.2\times10^{-2}$ set by the radial rule; refining the radial rule alone at $n_\varphi=16$ leaves a floor of $4.6\times10^{-4}$ set by the azimuthal grid. The registered statement that the latter floor would exceed $10^{-3}$ was **rejected** (it is $4.6\times10^{-4}$); a post-run clause confirms it lies in $[10^{-4},10^{-3}]$. With both controls refined the error is $2.3\times10^{-4}$: an edge inside the integration region keeps a residual that the node counts tested do not remove, and its cause was not isolated (R60.2). A plateau read after changing one control is a floor of the other.

**Phase origin (T3).** Rotating the azimuth grid by fractions $\epsilon=0,0.1,\ldots,0.9$ of a cell changes the smooth axisymmetric integral by $0$ (to the arithmetic floor), and the shadow integral by a spread (maximum minus minimum) of $9.19\times10^{-2}$ at $N=16$ and $1.64\times10^{-2}$ at $N=64$, a reduction by $5.6$ (registered: at least 3). The phase origin is invisible where the symmetry holds and is a quadrature-level difference where a blocker breaks it.

## 60.3 Retardation sensitivity

An iteration residual $\delta t$ gives a source-position uncertainty of about $v\,\delta t$ only when the local motion is smooth. Near a shadow boundary the visibility can change discontinuously with a tiny angular shift. A controlled treatment resolves the edge or reports a visibility uncertainty, rather than converting $\delta t$ directly into a universal force tolerance.

**Executed (T4).** A source $s(t)=vt$ with $v=0.5$ and an observer at 3 (units $c=1$); the retarded time is found by fixed-point iteration from the unretarded guess, whose error falls by $v$ per iteration; $2\times10^5$ samples of the converged retarded time; force $F=1/(2-s)^2$. Smooth region: the maximum force error falls from $1.378\times10^{-1}$ at $n=4$ to $7.859\times10^{-3}$ at $n=8$, a factor $17.5$ (the expected $2^4=16$; registered $[12,20]$). With a visibility step at $s=0.5$: the number of samples whose visibility differs from the converged value falls from $16\,288$ ($8.1$ per cent) at $n=4$ to $995$ ($0.50$ per cent) at $n=8$, a factor $16.4$, and every flipped sample has a force error equal to the whole force value (a jump of $F$), independent of $n$. The smooth error shrinks with the residual; the edge error does not shrink in size, only in the fraction of positions it affects.

## 60.4 Determining convergence table

Hold the physical initial data fixed; vary timestep, angular resolution, retarded tolerance and history spacing separately; report trajectory and reservoir residuals together. The existing benchmark agreement is retained at the resolutions at which it was tested. This chapter supplies the structure of that table on stand-ins; the table for the engine's trajectories was not generated (R60.1).

## 60.5 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| integrands, motion, node counts | Sections 60.1–60.3 | CONSTRUCTION (known answers; no measured input) |
| engine radial nodes | `occlusion_sphere` | stored constants (Gauss–Legendre, six nodes) |
| estimates, errors, spreads, fractions | Sections 60.1–60.3 | COMPUTED |

**Residuals.**

* **R60.1 — the engine's table.** No convergence table was computed for the engine's trajectories; each numerical control of the solver was not varied independently.
* **R60.2 — the edge floor.** The residual $2.3\times10^{-4}$ with both controls refined was not traced to its source (the radial structure at the ring that first meets the edge, the azimuth midpoint rule, or both).
* **R60.3 — three-dimensional shielding.** The seven-circle channel geometry and the blocker test of the engine were not exercised; a planar edge stood in for them.
* **R60.4 — history interpolation.** The error from interpolating source history was not separated.
* **R60.5 — fixed-point convergence.** The retarded iteration converges at rate $v$ per step for $v<1$; its behaviour near $v\to1$ and for accelerating sources was not examined.

## 60.6 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch60_quadrature_retardation_convergence
```

Criteria were registered in `Textbook/validation/ch60_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch60_run1_output.txt`) failed three criteria (a registration error in the validation of the reference area and two registered statements that were rejected); run 2 repaired the validation but contained a coding slip (a missing symmetric range), recorded. Run 3 (`ch60_run3_output.txt`) is the run of record: it met every criterion, with the rejections asserted and the post-run clauses marked.

## 60.7 Exercises and answers

**Exercise 1.** Estimate $p$ from $Q=(2.0000,\,1.5000,\,1.3750)$ at $h,h/2,h/4$.

*Answer.* $|(2.0-1.5)/(1.5-1.375)|=4$, so $p=2$.

**Exercise 2.** Why is the estimate of (60.1) unreliable near cancellation?

*Answer.* The differences $Q(h)-Q(h/2)$ approach the rounding error of $Q$, so the ratio is a ratio of noise.

**Exercise 3.** Why does the smooth axisymmetric integral not depend on the azimuth phase?

*Answer.* The azimuth integral of a function of $r$ alone is the same constant on every grid, so each ring contributes $2\pi f(r)$ exactly for any phase.

**Exercise 4.** What does a floor of $1.2\times10^{-2}$ at $(6,256)$ say?

*Answer.* The azimuth refinement has removed its own error; the remainder is the radial rule's, which the azimuth cannot reduce.

**Exercise 5.** Convert a retarded-time residual of $10^{-3}$ at $v=0.5$ to a position uncertainty and to a visibility fraction.

*Answer.* $v\,\delta t=5\times10^{-4}$ in a smooth region; at a shadow edge it flips the visibility for the fraction of source positions within $5\times10^{-4}$ of the edge.

**Exercise 6.** Why does a flipped sample's error not shrink as $n$ grows?

*Answer.* The visibility is 0 or 1; a flipped sample misses the whole force at the true position, whatever the residual.

## 60.8 Scope

Established: the order estimator and its failures on the tested cases (steady $1.0000$ for a step; $-0.939$ near cancellation); the floors set by independent quadrature controls; the phase-origin effect with its decay; the different scaling of smooth and edge errors in retardation.

Not established: a convergence table for the engine (R60.1), the origin of the edge floor (R60.2), the three-dimensional channel geometry (R60.3), the history-interpolation error (R60.4) and the iteration near $v\to1$ (R60.5).

*Where it leads.* Chapter 61 turns to experimental instruments: specifying an apparatus, and the controls that separate mechanisms.
