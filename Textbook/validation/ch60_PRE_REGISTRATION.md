# Chapter 60 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch60_quadrature_retardation_convergence.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents). All integrands and motions are constructed test problems with known answers (no measured input); the engine's channel-disc quadrature constants (`occlusion_sphere::radial_nodes`, 6 radial and 16 azimuth nodes) are used in one test.

Object. Separating numerical errors. (a) For a smooth asymptotic error $E(h)=Ch^p$ three successive resolutions estimate $p=\log_2|[Q(h)-Q(h/2)]/[Q(h/2)-Q(h/4)]|$; the estimate is unreliable near cancellation, for a discontinuous integrand, or where a different error dominates. (b) Independent controls: the angular quadrature of a disc with a shadow edge has a radial control and an azimuthal control; refining one while the other is fixed reaches a floor set by the other; a smooth axisymmetric integrand is insensitive. (c) Phase-origin effects: rotating the azimuth grid's phase leaves a smooth axisymmetric integral invariant and changes a shadow-edge integral by an amount that falls as the grid is refined. (d) Retardation sensitivity: an iteration residual $\delta t$ gives a source-position uncertainty about $v\delta t$ in a smooth region; near a shadow edge the visibility flips for the fraction of positions within $v\delta t$ of the edge, a jump independent of $\delta t$; the fraction of flipped samples scales as $\delta t$.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | composite Simpson of $e^x$ on $[0,1]$ with $n=64$ equals $e-1$ to $10^{-9}$; the area of the unit disc with $x<0.3$ is $\pi-[\arccos0.3-0.3\sqrt{0.91}]=2.1616708$ (analytic) | $10^{-9}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | order estimate. Simpson on $e^x$ over $[0,1]$ with $n=8,16,32$: $\hat p\in[3.98,4.02]$; composite trapezoid on $e^x$: $\hat p\in[1.98,2.02]$; trapezoid on the step $1[x<1/\pi]$ over $n=2^3\ldots2^{12}$: the estimates $\hat p$ over the 8 consecutive triples have a range above 0.5 (no single order); Simpson at $n=2^{14},2^{15},2^{16}$ on $e^x$: $|\hat p-4|>1$ (cancellation: the differences are at rounding level) | as stated | yes |
| T2 | independent controls. On the unit disc with the engine's 6 radial Gauss–Legendre nodes (generalised by $n_r$) and $n_\varphi$ azimuth midpoints: the smooth integrand $e^{-r^2}$ at $(6,16)$ has an error below $10^{-7}$ against $\pi(1-e^{-1})$; the shadow integrand $1[x<0.3]$ has errors satisfying: $E(6,16)>10^{-3}$; $E(6,256)>10^{-5}$; $E(96,16)>10^{-3}$; $E(96,256)<E(6,256)$ and $E(96,256)<E(96,16)$ | as stated | yes |
| T3 | phase origin. Azimuth grids of $N=16$ and $64$ with phase offsets $\epsilon\,2\pi/N$, $\epsilon\in\{0,0.1,\ldots,0.9\}$: the smooth axisymmetric integral varies by less than $10^{-13}$; the shadow integral's spread (max minus min) exceeds $10^{-4}$ at $N=16$ and the spread at $N=64$ is at least 3 times smaller | as stated | yes |
| T4 | retardation. Source $s(t)=vt$, $v=0.5$, observer at 3 (units with $c=1$), retarded time by fixed-point iteration from the unretarded guess; samples of $t^*\in[0,2]$ ($s^*\in[0,1]$), $2\times10^{5}$ values; force $F=1/(2-s)^2$; smooth-only force error after $n=4$ and $n=8$ iterations: $\max|\Delta F|(n=4)/\max|\Delta F|(n=8)\in[12,20]$; with the visibility step at $s=0.5$: the fraction of samples whose visibility differs from the converged value at $n=4$ over that at $n=8$ is in $[12,20]$; at both $n$ the force error of a flipped sample is $F$ times 1 (a jump independent of $n$) | as stated | yes |

Reported, not criteria: the estimates $\hat p$, the quadrature errors, the spreads, the fractions.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch60_quadrature_retardation_convergence`

## Record of run 1; one registration error and two registered statements rejected (2026-11-10)

Run 1 (`ch60_run1_output.txt`): V1 (Simpson), T1 (Simpson and trapezoid orders; cancellation), the smooth part and three of the four shadow inequalities of T2, all of T3 and all of T4 were met. Three criteria failed.

(1) **V1, a registration error.** The registered check of the analytic disc area compared it with the $96\times4096$ quadrature of the discontinuous indicator to $10^{-6}$. The quadrature of a discontinuous integrand cannot reach that (the instrument returned $2.161553$ against $2.161671$, a difference of $1.2\times10^{-4}$, the size of the floor that T2 measures): using a quadrature with an edge to validate a reference value was the wrong instrument. The criterion is replaced, before any T result is read in run 2, by an independent smooth route: the area from the chord integral with the substitution $y=\sin\theta$, $A=\int_{-\theta_*}^{\theta_*}(0.3\cos\theta+\cos^2\theta)d\theta+2\int_{\theta_*<|\theta|<\pi/2}\cos^2\theta\,d\theta$ with $\theta_*=\arcsin\sqrt{0.91}$, equal to $\pi-[\arccos0.3-0.3\sqrt{0.91}]$ to $10^{-12}$.

(2) **T1, a registered statement rejected.** The registered statement that the order estimates for the step integrand over eight triples have a range above 0.5 is **rejected**: the estimates are $1.00$ at every refinement (the trapezoid error of a step is of order 1 and the estimator returns it steadily for this edge position, $x=1/\pi$). The statement is kept and asserted in run 2; a post-run exploration, marked as such, reports the estimates (four decimals) for five edge positions without a pass criterion.

(3) **T2, a registered statement rejected.** The registered statement $E(96,16)>10^{-3}$ is **rejected**: $E(96,16)=4.59\times10^{-4}$ (the azimuthal floor at 16 midpoints with a fine radial rule is lower than registered). The statement is kept and asserted in run 2; a post-run clause, marked as such, requires $E(96,16)\in[10^{-4},10^{-3}]$ (the registered ordering $E(96,256)<E(96,16)$ was met in run 1).

Run 2 is a further run, not the run of record (see below).

## Record of run 2; one instrument defect in the replacement of V1 (2026-11-10)

Run 2 (`ch60_run2_output.txt`): the rejections of T1 and T2 behaved as registered and asserted ($1.0000$ at every triple and for five other edge positions, range $0.0000$; $E(96,16)=4.589\times10^{-4}$, inside the post-run window $[10^{-4},10^{-3}]$); T3 and T4 criteria were met again. The replacement V1 check failed: the chord integral returned $2.14316$ against the analytic $2.16167$. The instrument integrated $2\int_{\theta_*}^{\pi/2}\cos^2\theta\,d\theta$ (one of the two symmetric ranges), while the registered formula integrates over $\theta_*<|\theta|<\pi/2$, i.e. both ranges: the second term is $4\int_{\theta_*}^{\pi/2}\cos^2\theta\,d\theta$. The shortfall $0.0185$ equals the missing range. This is an instrument defect (a coding slip against the registered formula), not a registration error and not a finding on the object; the criterion is unchanged. Run 3 is the run of record.
