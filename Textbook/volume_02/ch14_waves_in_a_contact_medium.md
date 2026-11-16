# Chapter 14 — Waves in a Contact Medium

*Volume II — Pressure Response, Inertia and Propagation.*
Draft of 9 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. Executable companion: `Textbook/examples/ch14_waves_in_a_contact_medium.cpp`; pre-registration and captured output in `Textbook/validation/`. The relay chain of Sections 14.3–14.6 is a TOY model, generic and carrying no measured input.

## 14.1 The physical question

A wave in the contact medium is the propagating change of a contact state. The disturbance that travels and the configuration that carries it are described separately: a persistent form can stay in place while a change of its boundary state spreads outward, and a moving form need not carry the same neighbours along with it. Three levels stay distinct. The contact topology fixes what can transfer to what and the earliest arrival. The contact-response law fixes how a disturbance develops: its dispersion, its damping, its polarisation. A continuum equation describes the response after a justified long-wavelength limit and supplies transport coefficients. The topology alone determines no propagation spectrum.

## 14.2 State, adjacency and response

Let $a$ be a spation and $b$ a member of its neighbour set $\mathcal N(a)$. Let $Q_a$ be the local contact state and $\bar Q_a$ a stationary reference state under the prevailing convergence, with perturbation $\eta_a=Q_a-\bar Q_a$. A general linear causal recurrence is

$$\eta_a(m)=\sum_{b\in\mathcal N(a)}\int_0^\infty K_{ab}(s)\,\eta_b(m-s)\,ds+f_a(m), \tag{14.1}$$

with $m$ a count of a declared oscillator and $K_{ab}$ a response operator, not an additional substance. The source $f_a$ is separated from the retransmission of content that has already arrived. An ideal fixed-delay relay is the special case $K_{ab}(s)=T_{ab}\,\delta(s-\tau_{ab})$: the matrix $T_{ab}$ sets transmission and conversion between components and $\tau_{ab}$ sets the earliest arrival. Nearest-neighbour locality restricts the support of $K_{ab}$. Stability, conservation and rotational covariance impose further conditions on $T_{ab}$, and locality supplies none of them.

## 14.3 A minimal contact-recurrence chain (TOY)

Take a chain of cells carrying content $R_i,L_i\ge0$ moving right and left. At each relay count a fraction $s$ of the content at every cell reverses its direction, and then every parcel hops one cell:

$$R_{i+1}(m+1)=(1-s)R_i(m)+sL_i(m),\qquad L_{i-1}(m+1)=(1-s)L_i(m)+sR_i(m). \tag{14.2}$$

The update conserves content, is nonnegative for $0\le s\le1$, and moves nothing faster than one cell per count, so it has the causal support of Eq. (1.3). Executed (test T1, 500 counts from $R_0=L_0=\tfrac12$, $s=0,0.1,0.3,0.5$): the total content was $1$ to $2.7\times10^{-14}$ and the minimum cell content was nonnegative in every case. Two limits were checked first (V1): at $s=0$ the content of a right-moving parcel sits after seven counts at cell $+7$ and nowhere else, and at $s=1$ it alternates between cells $0$ and $-1$ and never advances.

For a plane wave $R_i,L_i\propto e^{i(\kappa i-\omega m)}$ the update is multiplication by

$$M(\kappa)=\begin{pmatrix}(1-s)e^{-i\kappa}&se^{-i\kappa}\\ se^{i\kappa}&(1-s)e^{i\kappa}\end{pmatrix},\qquad \operatorname{tr}M=2(1-s)\cos\kappa,\quad\det M=1-2s, \tag{14.3}$$

with eigenvalues $\lambda_\pm=(1-s)\cos\kappa\pm\sqrt{(1-s)^2\cos^2\kappa-(1-2s)}$ and $\lambda=e^{-i\omega}$. At $s=0$ they are $e^{\pm i\kappa}$: the speeds of Chapter 3 coincide and equal the hop speed. At $s=1$ they are $\pm1$ (V2). The eigenvalue formula was tested against the direct evolution of complex plane-wave eigenvectors on a periodic chain of 128 cells for $\kappa=\pi/8,\pi/4,\pi/2,3\pi/4$ and $s=0.1,0.3$: after ten counts the amplitude equalled $\lambda^{10}$ to $6.3\times10^{-13}$ over the sixteen modes (T2).

## 14.4 The wave branch and its speeds

For $s<\tfrac12$ the eigenvalues are complex when $(1-s)^2\cos^2\kappa<1-2s$, equivalently

$$\sin\kappa>\frac{s}{1-s},\qquad\text{band }\kappa_c<\kappa<\pi-\kappa_c,\quad \sin\kappa_c=\frac s{1-s}. \tag{14.4}$$

The band edge is $\kappa_c=0.111341$ for $s=0.1$ and $0.442911$ for $s=0.3$ (T3, confirmed against the sign of the imaginary part and, in T3e, $\sin\kappa_c=s/(1-s)$ to $3\times10^{-15}$). On the band the product of the eigenvalues fixes $|\lambda|^2=1-2s$, so the wave decays at the rate $-\tfrac12\ln(1-2s)$ per count, the same for every wavenumber: $0.111572$ for $s=0.1$ and $0.458145$ for $s=0.3$. The phase of $\lambda$ obeys $\cos\varphi=(1-s)\cos\kappa/\sqrt{1-2s}$, giving the phase speed $\varphi/\kappa$ and the group velocity $d\varphi/d\kappa$. With $N=(1-s)^2\sin^2\kappa$ one has $(1-2s)\sin^2\varphi=N-s^2$ and

$$v_g=\frac{(1-s)\sin\kappa}{\sqrt{1-2s}\,\sin\varphi}=\frac1{\sqrt{1-\big(s/((1-s)\sin\kappa)\big)^{2}}}\ >1. \tag{14.5}$$

The group velocity of the real part therefore exceeds the hop speed everywhere on the branch for every $s>0$ and diverges at the band edges. The closed form agreed with the central difference of $\varphi(\kappa)$ from the eigenvalues to $2.6\times10^{-11}$ ($s=0.1$) and $3.6\times10^{-10}$ ($s=0.3$) at five wavenumbers (T3e).

| $\kappa$ | $s=0.1$: phase, group | $s=0.3$: phase, group |
|---|---|---|
| 0.6 | 0.984719, 1.019943 | 0.698403, 1.535922 |
| 1.0 | 0.995994, 1.008833 | 0.929787, 1.162005 |
| $\pi/2$ | 1.000000, 1.006231 | 1.000000, 1.106797 |
| 2.0 | 1.001427, 1.007550 | 1.024728, 1.133836 |
| 2.4 | 1.002845, 1.013810 | 1.052294, 1.293770 |

Table 14.1. Phase speed and group velocity (in hops per count), executed (T3e; the closed form (14.5) for the group velocity).

*The front is a different speed.* The support of the response is the earliest content to arrive, and it is set by the hop count alone. After 300 counts, for $s=0,\,0.1,\,0.5$, no content lay beyond cell $\pm300$, and the right-hand end cell held $\tfrac12(1-s)^{299}$ to $1.5\times10^{-16}$ relative at $s=0.1$ (T4; the first count already carries the reversed half of the initial content, the origin of the exponent $m-1$ and the correction recorded in the pre-registration). A group velocity above the front speed is not a signal speed: the front is exactly one hop per count whatever the dispersion. Phase, group, front and energy speeds coincide only for the undamped, dispersionless relay at $s=0$, and each further coincidence needs a premise.

## 14.5 The diffusive branch and its transport coefficient

For $\sin\kappa<s/(1-s)$ both eigenvalues are real. The larger one, $\lambda_+=1-D\kappa^2+\ldots$, describes content that has lost its direction and spreads; expanding (14.3) gives

$$D=\frac{1-s}{2s}. \tag{14.6}$$

At $\kappa=10^{-3}$ the computed $1-\lambda_+$ equalled $D\kappa^2$ to $1.8\times10^{-5}$ ($s=0.1$) and $7\times10^{-7}$ ($s=0.3$). The same coefficient governs the variance of the content in real space. For an isotropic start, with $\rho=1-2s$ the correlation of successive directions,

$$\sigma^2(m)=m\,\frac{1+\rho}{1-\rho}-\frac{2\rho\,(1-\rho^m)}{(1-\rho)^2}, \tag{14.7}$$

whose late-time rate is $\sigma^2/(2m)\to D$. The simulation at $m=1000$ gave $\sigma^2=8960.000000$, $2331.111111$ and $1000.000000$ for $s=0.1,0.3,0.5$, equal to (14.7) to $5\times10^{-14}$ or better (T5), and $\sigma^2/(2m)=4.480$ against $D=4.500$ at $s=0.1$ ($0.44\%$ below; the offset is the second term of (14.7)). At $s=0.5$ the chain is the symmetric random walk and $\sigma^2=m$ exactly.

The single fraction $s$ therefore fixes the band edge (14.4), the damping rate, the dispersion (14.5) and the diffusion coefficient (14.6). They are coupled consequences of one closure and not four parameters. Transport coefficients in the engine are of this kind: a common collision kernel yields several coefficients with fixed ratios (Chapter 16).

*What the chain implies for propagation of light in the medium.* A wave of wavelength $\lambda$ has $\kappa=2\pi\ell_P/\lambda$ per cell. By (14.4) it travels as a wave only if $s$ is below $\kappa$: $s\lesssim2\times10^{-28}$ for $\lambda=500$ nm and $\lesssim10^{-34}$ for $\lambda=1$ m (COMPUTED from the stored $\ell_P$). Within the chain, propagation of electromagnetic waves over the observed ranges without measurable dispersion or damping requires the reversal fraction to be absent or vanishingly small at relevant wavenumbers. This is a property of the TOY chain; the reversal fraction of the real medium is not known (residual R14.3).

## 14.6 Polarisation

A scalar chain carries one component per direction. A transverse wave with two independent polarisations needs a response with a shear component, and the speeds of transverse and longitudinal branches need not coincide. The response $K_{ab}$ of the real medium, and with it the number and polarisation of its modes, is not specified by the sources (residual R14.2). Anisotropy and polarisation need a mode or tensor response and not a single scalar temperature.

## 14.7 Rays in a gradient

For a stationary isotropic nondispersive branch $\omega=c(\vec x)|\vec\kappa|$, define $n=c_{\rm ref}/c$. Geometric transport gives the ray curvature

$$\frac{d\hat t}{ds}=\nabla_\perp\ln n=-\nabla_\perp\ln c, \tag{14.8}$$

so a bent path follows the native relay-speed gradient, and $c_{\rm ref}$ must be named. The integrator was checked on the medium $n=1/y$, whose rays are circles centred on $y=0$: the ray from $(0,1)$ with initial tangent $(1,0)$ should follow $x^2+y^2=1$. RK4 with step $10^{-3}$ to path length $1.2$ reproduced $(\sin s,\cos s)$ to $9\times10^{-14}$ (T6). The gradient itself requires the contact-response law; Chapter 39 integrates the engine's profile $c_{\rm far}=c(1-z)^2$.

## 14.8 Acoustic loading

The engine's release-acoustic relation gives the sound speed of the relay medium loaded by baryons,

$$\frac{c_s}{c}=\frac1{\sqrt{3\,(1+R_{\rm load})}}\qquad(\texttt{release\_acoustics::sound\_speed},\ \texttt{laws.hpp:1209}). \tag{14.9}$$

Executed (T7): $0.577350$ at $R_{\rm load}=0$, the ceiling $c/\sqrt3$; $0.4564354646$ at $0.6$; and $0.436436$ at $3/4$, the loading at equality of baryon and radiation density. The function falls strictly with loading. The numerator $c$ may be the present measured speed or an epoch speed (Chapters 41–47 keep the two branches apart). When electromagnetic and acoustic propagation share one numerator, $c_s/c_{\rm EM}<1$ for nonnegative loading, and an overtake would need a differential response of the two.

## 14.9 Extinction, emission and source memory

Directional spectral transfer separates extinction, emission and redistribution. For a homogeneous scalar slab of optical depth $\tau$ and direction cosine $\mu$,
$I_{\rm out}=I_{\rm in}e^{-\tau/\mu}+S(1-e^{-\tau/\mu})$. Direct imaging, spectral and timing memory, and the ancestry of reprocessed energy therefore have different depth limits, and a large elastic scattering depth alone does not establish thermalisation. The same chart structure applies to a ring layer, a stellar emitting layer and a cometary coma when each supplies its geometry, opacity, source function and boundary conditions; matching the frames does not authorise one universal coefficient (Chapter 52).

## 14.10 Input ledger and residuals

All executed values of Sections 14.3–14.7 are DERIVED (exact) or COMPUTED for the TOY chain; the acoustic values are COMPUTED from the engine's relation.

**Residuals.**

* **R14.1 — the response operator.** $K_{ab}$ of the real medium is not known; the chain is a TOY.
* **R14.2 — polarisation.** The shear response that would give transverse modes, and their speeds, are not specified.
* **R14.3 — the reversal fraction.** The physical origin of $s$ in the contact medium, and its value at observed wavenumbers, are open. The chain bounds it from above by the existence of waves at all (Section 14.5).
* **R14.4 — energy velocity.** The ratio of transported energy flux to stored energy density has not been computed for the chain.
* **R14.5 — the epoch branch.** The lookback and loading branches of the acoustic relation belong to the Spaz chapters.
* **R14.6 — the acoustic input.** $R_{\rm load}$ enters from outside; the relation is the engine's.

## 14.11 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch14_waves_in_a_contact_medium
```

Criteria were registered in `Textbook/validation/ch14_PRE_REGISTRATION.md` before the instrument existed. Run 1 met every criterion except the end-value clause of T4, whose registered value omitted the factor from the first count; the clause was corrected, and test T3(e), the exact group velocity found while analysing run 1, was registered before it was coded. Run 2 (`ch14_run2_output.txt`) is the run of record and met every criterion.

## 14.12 Exercises and answers

**Exercise 1.** Show that the eigenvalues of $M(\kappa)$ satisfy $\lambda^2-2(1-s)\cos\kappa\,\lambda+(1-2s)=0$.

*Answer.* $\operatorname{tr}M=(1-s)(e^{-i\kappa}+e^{i\kappa})=2(1-s)\cos\kappa$ and $\det M=(1-s)^2-s^2=1-2s$.

**Exercise 2.** Show that on the wave branch $|\lambda|^2=1-2s$.

*Answer.* The eigenvalues are complex conjugates, so their product is $|\lambda|^2=\det M=1-2s$.

**Exercise 3.** Obtain (14.5) from $\cos\varphi=(1-s)\cos\kappa/\sqrt{1-2s}$.

*Answer.* Differentiate: $-\sin\varphi\,\varphi'=-(1-s)\sin\kappa/\sqrt{1-2s}$. And $(1-2s)\sin^2\varphi=(1-2s)-(1-s)^2\cos^2\kappa=(1-s)^2\sin^2\kappa-s^2$, so $v_g^2=N/(N-s^2)$ with $N=(1-s)^2\sin^2\kappa$.

**Exercise 4.** At what wavenumber does the wave branch for $s=0.3$ begin?

*Answer.* $\sin\kappa_c=0.3/0.7=0.428571$, so $\kappa_c=0.442911$.

**Exercise 5.** What is $\sigma^2(m)$ for $s=\tfrac12$?

*Answer.* $\rho=0$, so $\sigma^2=m$: the symmetric random walk.

**Exercise 6.** Evaluate $c_s/c$ for $R_{\rm load}=0.6$.

*Answer.* $1/\sqrt{3\times1.6}=1/\sqrt{4.8}=0.4564354646$.

## 14.13 Scope

Established in this chapter, for the TOY chain: conservation and positivity; the exact dispersion, band edge, damping and group velocity (14.3)–(14.5), checked by direct simulation; the hop-causal front, distinct from the group velocity; the diffusion coefficient and the variance law, checked to $10^{-14}$; the ray equation reproduced on a known medium; and the engine's acoustic relation with its executed values.

Not established: the response operator of the real medium (R14.1), its polarisation (R14.2), the origin and size of a reversal fraction (R14.3), and the epoch and loading inputs of the acoustic relation (R14.5, R14.6).

*Where it leads.* Chapter 15 sets up the energy and momentum ledger of a region traversed by such disturbances. Chapter 16 takes the continuum limit and the engine's transport coefficients. Chapter 39 uses (14.8) for the propagation delay and bending, and Chapter 52 returns to extinction and thermal content.
