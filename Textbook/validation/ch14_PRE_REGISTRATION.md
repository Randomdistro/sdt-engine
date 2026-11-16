# Chapter 14 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch14_waves_in_a_contact_medium.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. A minimal exactly solvable contact-recurrence chain, labelled TOY (generic, no measured input), used to separate the speed roles of Chapter 3: content $R_i,L_i\ge0$ moving right and left at cell $i$; per relay count a fraction $s$ of the content at each cell reverses its direction and then every parcel hops one cell:
$$R_{i+1}(m+1)=(1-s)R_i(m)+sL_i(m),\qquad L_{i-1}(m+1)=(1-s)L_i(m)+sR_i(m).$$
It conserves content, is positive for $0\le s\le1$, and has the hop-causal support of Eq. (1.3). Its plane-wave matrix has trace $2(1-s)\cos\kappa$ and determinant $1-2s$. The predictions registered here: (i) for $s<\tfrac12$ the wave branch has $\lvert\lambda\rvert^2=1-2s$ (decay rate $-\tfrac12\ln(1-2s)$ per count, independent of $\kappa$), phase $\varphi$ with $\cos\varphi=(1-s)\cos\kappa/\sqrt{1-2s}$ for $\kappa>\kappa_c=\arccos(\sqrt{1-2s}/(1-s))$, and group velocity $v_g=(1-s)\sin\kappa/(\sqrt{1-2s}\sin\varphi)$, which exceeds the hop speed 1 in a band while the front speed is exactly 1; (ii) the diffusive branch has $\lambda_+\approx1-D\kappa^2$ with $D=(1-s)/(2s)$, equal to the late-time variance rate; (iii) the variance of the content is $\sigma^2(m)=m\frac{1+\rho}{1-\rho}-\frac{2\rho(1-\rho^m)}{(1-\rho)^2}$ with $\rho=1-2s$ for an isotropic start. The engine's release-acoustic relation (`bridge::release_acoustics::sound_speed`, `laws.hpp:1209`) and a numerical ray integration complete the chapter.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | $s=0$, $R_0=1$: after 7 counts all content sits at cell $+7$ moving right; $s=1$, $R_0=1$: the content alternates between cells $0$ and $-1$ and never advances | exact |
| V2 | the eigenvalue formula $\lambda_\pm=(1-s)\cos\kappa\pm\sqrt{(1-s)^2\cos^2\kappa-(1-2s)}$ at $s=0$ gives $e^{\pm i\kappa}$ and at $s=1$ gives $\pm1$ | $10^{-14}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | conservation and positivity for $s\in\{0,0.1,0.3,0.5\}$ after 500 counts from $R_0=L_0=\tfrac12$ | total $=1$ to $10^{-12}$; minimum $\ge0$ | yes |
| T2 | dispersion by direct simulation. A plane-wave eigenvector in a periodic chain of 128 cells, $\kappa=2\pi j/128$ for $j=8,16,32,48$ ($\kappa=\pi/8,\pi/4,\pi/2,3\pi/4$) and $s\in\{0.1,0.3\}$, evolved 10 counts: amplitude ratio equals $\lambda^{10}$ | within $10^{-10}$ relative | yes — a wrong matrix or eigenvalue rejects |
| T3 | closed forms. (a) $\lvert\lambda\rvert^2=1-2s$ on the wave branch; (b) the cutoff $\kappa_c$ separates real from complex eigenvalues; (c) $v_g(\pi/2)=(1-s)/\sqrt{1-2s}$ equals the central difference of $\varphi(\kappa)$ from the eigenvalues to $10^{-8}$ and exceeds 1 for $s=0.1$ (printed); (d) the diffusive branch $\lambda_+$ at $\kappa=10^{-3}$ equals $1-D\kappa^2$ with $D=(1-s)/(2s)$ to $10^{-9}$ relative to $D\kappa^2$ | as stated, $s\in\{0.1,0.3\}$ | yes — $v_g\le1$ for all $\kappa$ would reject the registered excess |
| T4 | front. After 300 counts the rightmost occupied cell is $+300$, holding exactly $\tfrac12(1-s)^{300}$, and every cell beyond is zero, for $s\in\{0,0.1,0.5\}$ | exact support; the end value within $10^{-12}$ relative | yes — a front faster than one hop per count rejects the causal bound |
| T5 | variance. $\sigma^2(m)$ from the simulation at $m=1000$ equals the closed form (iii) for $s\in\{0.1,0.3,0.5\}$; $\sigma^2/(2m)$ is within 2% of $D$ for $s=0.1$ | $10^{-10}$ relative for the closed form | yes |
| T6 | ray transport in a gradient. For $n(y)=1/y$ the eikonal ray $d\vec t/ds=\nabla_\perp\ln n$ from $(0,1)$ with $\vec t=(1,0)$ follows the circle $x^2+y^2=1$: integrated by RK4 to path length 1.2 with step $10^{-3}$ | position within $10^{-9}$ of $(\sin s,\cos s)$ | yes |
| T7 | engine acoustic relation: $c_s/c=1/\sqrt{3(1+R)}$ at $R=0$ ($0.577350269$), $R=0.6$ ($0.4564354646$) and $R=3/4$; strictly decreasing in $R$ | within $10^{-10}$ | yes |

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch14_waves_in_a_contact_medium`

## Record of run 1; correction of the T4 prediction; added test T3(e) (2026-11-09)

Run 1 (`ch14_run1_output.txt`) met every criterion except the end-value clause of T4. The support clause (no content beyond cell $\pm300$ after 300 counts) was met for all three values of $s$. The registered end value $\tfrac12(1-s)^{300}$ was a derivation slip: in the first count the left-moving half of the initial content at the origin also reverses (fraction $s$) and then hops right, so the right-hand cell after one count holds $(1-s)\tfrac12+s\tfrac12=\tfrac12$, and only the following $m-1$ counts each carry the factor $(1-s)$. The correct end value is $\tfrac12(1-s)^{m-1}$. The observed values were larger than the registered ones by exactly $1/(1-s)$ ($1.1111$ at $s=0.1$, $2$ at $s=0.5$). The clause is corrected to $\tfrac12(1-s)^{m-1}$ with the same tolerance; the support criterion is unchanged.

Run 1 also showed that the printed "maximum group velocity" over a scan to $\kappa=\pi-0.01$ was meaningless: the oscillatory branch exists only for $\kappa_c<\kappa<\pi-\kappa_c$ and the group velocity of the real part diverges at the band edges. Analysing that, an exact result was found that was not registered: with $N=(1-s)^2\sin^2\kappa$ one has $(1-2s)\sin^2\varphi=N-s^2$, hence
$$v_g^2=\frac{N}{N-s^2}=\frac{1}{1-\big(s/((1-s)\sin\kappa)\big)^2}>1,$$
the band edge is at $\sin\kappa_c=s/(1-s)$, and $v_g>1$ throughout the band for every $s>0$. It is registered now as test **T3(e)**, before it is coded: for $s\in\{0.1,0.3\}$ and $\kappa\in\{0.6,1.0,\pi/2,2.0,2.4\}$ inside the band, the closed form equals the central difference of $\varphi(\kappa)$ from the eigenvalues within $10^{-8}$ relative; $\sin\kappa_c=s/(1-s)$ within $10^{-12}$; and $v_g>1$ at every tested $\kappa$. The unregistered scan for a maximum is removed from the instrument. Run 2 is the run of record.
