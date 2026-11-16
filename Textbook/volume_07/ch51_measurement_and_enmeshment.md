# Chapter 51 — Measurement and Enmeshment

*Volume VII — Correspondence, Paradoxes and Discriminating Tests.*
Draft of 10 November 2026. Notation: outcomes $a,b\in\{\pm1\}$ under settings $x,y\in\{0,1\}$; $p(a,b|x,y)$ the joint distribution a model must supply; $E_{xy}=\sum_{ab}ab\,p(a,b|x,y)$; $S=E_{00}+E_{01}+E_{10}-E_{11}$; $\lambda$ a shared hidden state; $D$ station separation and $\delta$ the interval from a setting choice to a fixed outcome; $\sigma_S$ the standard error of a sampled $S$. Executable companion: `Textbook/examples/ch51_measurement_and_enmeshment.cpp`; pre-registration and captured output in `Textbook/validation/`. Every distribution here is a generic stand-in (TOY) with no engine function and no measured input. The cosine correlation $E=-\cos(\theta_x-\theta_y)$ is used only as the comparison target that the standard description predicts and experiments are set against; it is not an SDT derivation and not a primitive. No completed correlation derivation is asserted by this chapter.

## 51.1 Shared substrate and controlled correlations

Separated persistent systems remain embedded in a common contact medium. Enmeshment names that general coupling; an experimentally prepared correlation is a more specific state. A shared substrate alone fixes neither the size of a correlation, nor its controllability, nor a communication speed. A predicting model must supply $p(a,b|x,y)$, not a narrative of linkage. Observable marginal independence requires $\sum_bp(a,b|x,y)$ to be independent of $y$, and the mirror condition at the other station, under the tested protocol.

## 51.2 Assumption sets and what each allows

**Local deterministic hidden state (executed, T1).** The factorisation $p(a,b|x,y,\lambda)=p(a|x,\lambda)p(b|y,\lambda)$ with settings independent of $\lambda$ makes the joint distribution a mixture of the 16 deterministic strategies $(a(0),a(1),b(0),b(1))$. Each strategy gives $S=+2$ or $-2$ exactly (all 16 checked), and $S$ is linear in the mixture weights, so every mixture satisfies $|S|\le2$. Of $10^6$ uniform random mixtures the largest $|S|$ found is $1.781$ and none exceeds 2 (the registered statement that the largest would come within $10^{-3}$ of 2 was **rejected**: uniform weights concentrate far from the vertices; recorded and kept). A post-run clause, marked as such, with sparse weights reaches $2.000000000$ and never exceeds it.

**Marginal-independent distributions (executed, T2).** The target correlation with $\theta_A=(0,\pi/2)$ and $\theta_B=(\pi/4,-\pi/4)$ gives $|S|=2\sqrt2=2.828427$, a margin $2(\sqrt2-1)=0.828427$ over the local limit, with uniform marginals independent of the other station's setting (worst difference $0$). The Popescu–Rohrlich box (outcomes satisfying $ab=+1$ except at $x=y=1$ where $ab=-1$, each with probability $\tfrac12$) gives $|S|=4$ and also satisfies marginal independence. A strategy in which station A's outcome depends on both settings reaches $|S|=4$ but its marginal at A changes by $1$ between the two settings of B: it signals, so it fails the marginal condition of Section 51.1. The three values $2$, $2\sqrt2$ and $4$ separate three assumption sets (local factorisation; the target; marginal independence alone). A proposed SDT model has to say which assumptions apply, which change, and derive the resulting distribution; renaming the shared variable as substrate phase does not alter the mathematical implications.

## 51.3 Timing and admissible mechanisms

A nearest-neighbour relay with signal speed $v$ can bring B's setting to A before A's outcome is fixed only if $v\ge D/\delta$. **Executed (T3).** The minimum $v/c$ for generic separations and intervals:

| $D$ | $\delta=1$ ns | $100$ ns | $10\ \mu$s |
|---|---|---|---|
| $10$ m | $33.36$ | $0.3336$ | $3.34\times10^{-3}$ |
| $400$ m | $1334$ | $13.34$ | $0.1334$ |
| $1.3$ km | $4336$ | $43.36$ | $0.4336$ |

A relay at $v=c$ can carry the setting in time exactly in the cells with $D\le c\delta$ ($10$ m with $\delta\ge33.4$ ns; $400$ m and $1.3$ km with $\delta=10\ \mu$s), as registered. Where a relay at the declared speed cannot arrive in time, the correlation must come from preparation history, a shared state or an earlier interaction, and the complete mechanism has to reproduce both the timing and the joint statistics. Detector selection, coincidence windows and setting histories enter the experiment and cannot be discarded as bookkeeping.

## 51.4 Protocol and statistics

**Executed (T4).** With $n=1000$ trials per setting pair (fixed seed $20261110$) the sampled target gives $S=-2.8120\pm0.0450$: $|S|-2=0.812$, $18.1\,\sigma_S$ above the local limit, within $4\sigma_S$ of $2\sqrt2$. The equal mixture of two local strategies ($E=(1,1,0,0)$, $S=2$) gives $1.9700\pm0.0447$, within $4\sigma_S$ of 2. With $\sigma_S=\sqrt{2/n}$ for the target, a $5\sigma$ separation from the local limit needs $2[5/(2\sqrt2-2)]^2=72.9$ trials per setting pair. The sampled data are a statement about the instrument and the arithmetic of a protocol (randomised settings, full timing records, a predicted joint distribution) and not experimental data.

## 51.5 Measurement dynamics

Measurement changes the detector and the local contact network. A complete account includes irreversible registration and energy export without an unexplained instantaneous collapse (Chapter 50 compared two registration rules). The absence of collapse as a primitive is a requirement on the programme; matching measured correlations is a requirement on the calculation.

## 51.6 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| strategies, mixtures, PR box, signalling strategy | Sections 51.2 | CONSTRUCTION (no measured input) |
| $E=-\cos(\theta_x-\theta_y)$ | Section 51.2 | comparison target (standard description); not an SDT input |
| $D$, $\delta$ cells | Section 51.3 | CONSTRUCTION |
| sampled $S$, $\sigma_S$ | Section 51.4 | COMPUTED (seed $20261110$) |
| separation conclusions | Section 51.2 | DERIVED (exact; the limit by linearity over the 16 vertices) |

**Residuals.**

* **R51.1 — the joint distribution.** No $p(a,b|x,y)$ is computed from the contact model; the chapter fixes what such a model must supply and what each assumption set allows.
* **R51.2 — the assumptions.** Which of setting independence, locality of the relay, and the completeness of the shared state apply in the contact framework is not decided.
* **R51.3 — timing in the model.** The relay speed role and the event propagation of the contact model were not computed for any apparatus.
* **R51.4 — measurement dynamics.** Irreversible registration and energy export were not modelled (Chapter 50 supplies a stand-in rule only).
* **R51.5 — data.** No experimental record (timings, coincidence windows, setting histories) was loaded.

## 51.7 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch51_measurement_and_enmeshment
```

Criteria were registered in `Textbook/validation/ch51_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch51_run1_output.txt`) failed five criteria through two registration errors (an angle set giving $S=0$, and an unreachable claim about uniform random mixtures, the latter kept as a rejection). Run 2 (`ch51_run2_output.txt`) is the run of record and met every criterion, with the post-run clause marked.

## 51.8 Exercises and answers

**Exercise 1.** Show that no local deterministic strategy exceeds $|S|=2$.

*Answer.* $S=a(0)[b(0)+b(1)]+a(1)[b(0)-b(1)]$; one bracket is $0$ and the other $\pm2$, so $S=\pm2$.

**Exercise 2.** Why does the mixture limit follow?

*Answer.* $S$ is linear in the mixture weights and each vertex has $|S|=2$.

**Exercise 3.** Compute $S$ for $E=-\cos(\theta_x-\theta_y)$ with $\theta_A=(0,\pi/2)$, $\theta_B=(\pi/4,-\pi/4)$.

*Answer.* $E=(-1,-1,-1,+1)/\sqrt2$, so $S=-3/\sqrt2-1/\sqrt2=-2\sqrt2$.

**Exercise 4.** Why does the signalling strategy not count as a counterexample to the local limit?

*Answer.* A's outcome depends on B's setting, so the factorisation $p(a|x,\lambda)$ does not hold and the marginal at A changes with $y$.

**Exercise 5.** What speed would a relay need to carry a setting across $400$ m in $100$ ns?

*Answer.* $400/10^{-7}=4\times10^{9}$ m/s, $13.3\,c$.

**Exercise 6.** How many trials per pair give $5\sigma$ for the target against the local limit?

*Answer.* $2(5/0.8284)^2=72.9$, so 73.

## 51.9 Scope

Established: the local limit and its exact derivation; the separation of three assumption sets by the values $2$, $2\sqrt2$ and $4$ and by the marginal condition; the minimum relay speeds for generic cells; the protocol arithmetic.

Not established: a joint distribution from the contact model (R51.1), the applicable assumptions (R51.2), timing for an apparatus (R51.3), measurement dynamics (R51.4) and any comparison with a record (R51.5).

*Where it leads.* Chapter 52 separates mode geometry from occupation in the thermal and radiation puzzles, using the Casimir-type instrument of the framework.
