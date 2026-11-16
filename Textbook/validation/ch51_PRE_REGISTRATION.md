# Chapter 51 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch51_measurement_and_enmeshment.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. What a model of separated, jointly prepared systems has to supply, and what each admissible assumption set allows. All distributions are generic stand-ins (TOY) with no engine function and no measured input; the correlation function $E(x,y)=-\cos(\theta_x-\theta_y)$ is used only as a comparison target, the standard-formalism joint distribution that a native model would have to reproduce or explain, and not as an SDT derivation or primitive. For outcomes $a,b\in\{\pm1\}$ under settings $x,y\in\{0,1\}$ the model must supply $p(a,b|x,y)$. (a) A local deterministic hidden-state factorisation $p(a,b|x,y,\lambda)=p(a|x,\lambda)p(b|y,\lambda)$ with settings independent of $\lambda$ limits the correlation sum $S=E(0,0)+E(0,1)+E(1,0)-E(1,1)$ to $|S|\le2$: each of the 16 deterministic strategies gives $S=\pm2$ and every mixture lies in $[-2,2]$. (b) Observable marginal independence requires $\sum_bp(a,b|x,y)$ independent of $y$ (and the mirror condition): the target correlation with uniform marginals satisfies it and gives $S=2\sqrt2$ at the standard angles; the Popescu–Rohrlich box satisfies it and gives $S=4$; a strategy in which station A's outcome depends on B's setting gives $S=4$ but violates marginal independence. (c) Timing: a nearest-neighbour relay model with signal speed $v$ can carry B's setting to A before A's outcome is fixed only if $v\ge D/\delta$ ($D$ the separation, $\delta$ the interval from setting choice to outcome); the minimum $v/c$ for generic $(D,\delta)$ is computed. (d) Protocol: with $n$ trials per setting pair the standard error of $S$ is $\sqrt{\sum_{xy}(1-E_{xy}^2)/n}$; sampled data from the target give $S$ and a separation from $2$ measured in standard errors, and sampled data from a local strategy mixture give $|S|\le2$ within statistics.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $S=2$ for the strategy $a(x)=+1$, $b(y)=+1$ (all four $E=+1$); $S=2$ for $a(x)=(-1)^x$, $b(y)=+1$ ($E(0,0)=E(0,1)=+1$, $E(1,0)=E(1,1)=-1$, so $S=1+1+(-1)-(-1)=2$); $\sum_{a,b}p=1$ for the target and for the PR box | $10^{-15}$ |

For the sampled local mixture of T4 the registration uses the equal mixture of these two strategies: $E=(1,1,0,0)$, $S=2$, $\sigma_S=\sqrt{2/n}$.

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | local strategies. All 16 deterministic strategies give $S\in\{-2,+2\}$; $10^{6}$ random convex mixtures (fixed seed) give $|S|\le2$ (to $10^{-12}$) and the largest found is within $10^{-3}$ of $2$ | as stated | yes |
| T2 | other assumption sets. The target ($\theta_{A}=0,\pi/2$; $\theta_B=\pi/4,3\pi/4$) gives $S=2\sqrt2$ ($10^{-12}$) with uniform marginals independent of the other station's setting ($10^{-15}$); the PR box gives $S=4$ with marginal independence; the signalling strategy gives $S=4$ with a marginal difference of $1$ between the two settings of the other station; the margin of the target over the local limit is $2(\sqrt2-1)$ | as stated | yes |
| T3 | timing. $v_{\min}/c=D/(c\delta)$ for $(D,\delta)\in\{10\ \mathrm{m},400\ \mathrm{m},1.3\ \mathrm{km}\}\times\{1\ \mathrm{ns},100\ \mathrm{ns},10\ \mu\mathrm{s}\}$; the relay at $v=c$ can carry the setting in time in exactly those cells with $D\le c\delta$ (which are: $10$ m with $\delta\ge33.4$ ns, i.e. $100$ ns and $10\ \mu$s; $400$ m with $10\ \mu$s; $1.3$ km with $10\ \mu$s) | as stated | yes |
| T4 | protocol. With $n=1000$ trials per setting pair (fixed seed): $S$ from the target distribution lies within $4\sigma_S$ of $2\sqrt2$ and exceeds $2$ by at least $10\sigma_S$; $S$ from the strategy mixture with the largest local value $|S|=2$ lies within $4\sigma_S$ of $2$; the number of trials per pair needed for a $5\sigma$ separation is $2(5/(2\sqrt2-2))^2/1\approx73$ (computed from $\sigma_S=\sqrt{2/n}$) | as stated | yes |

Reported, not criteria: the sampled $S$ values and their standard errors; the largest random mixture value; $v_{\min}/c$ for each cell.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch51_measurement_and_enmeshment`

## Record of run 1; two registration errors (2026-11-10)

Run 1 (`ch51_run1_output.txt`): V1, the T1 vertex check, the T2 marginal checks, the PR box and signalling cases, T3 and the local-mixture and trial-count criteria of T4 were met. Five criteria failed, from two registration errors.

(1) The angle set. The registration listed $\theta_B=(\pi/4,3\pi/4)$ with $\theta_A=(0,\pi/2)$ and $E=-\cos(\theta_x-\theta_y)$. For that set $E=(-0.7071,+0.7071,-0.7071,-0.7071)$ and $S=E_{00}+E_{01}+E_{10}-E_{11}=0$, not $2\sqrt2$. The arrangement that gives $|S|=2\sqrt2$ for this correlation function and this $S$ is $\theta_B=(\pi/4,-\pi/4)$ ($E=-0.7071$ for the first three pairs and $+0.7071$ for the fourth: $S=-2\sqrt2$). This is an error in the registration, not a finding on the object. It caused the failure of "target $|S|=2\sqrt2$" and "target margin" in T2 and of both target criteria in T4 (the sampled value was $0.076\pm0.045$, consistent with $S=0$). The criteria are unchanged; the angle set is corrected to $(\pi/4,-\pi/4)$.

(2) T1: the registered statement "the largest $|S|$ among $10^6$ random mixtures is within $10^{-3}$ of 2" is **rejected**: the largest found is $1.781$. Uniform random convex weights over 16 vertices concentrate far from the vertices where $|S|=2$ is attained. The bound itself is certified by the first T1 criterion (every vertex has $|S|=2$ and $S$ is linear in the weights, so no mixture exceeds 2). The rejection is kept and asserted in run 2; a **post-run clause**, marked as such, uses mixtures with sparse weights (weights $U^{20}$) and requires the largest $|S|$ to be within $10^{-3}$ of 2.

Run 2 is the run of record.
