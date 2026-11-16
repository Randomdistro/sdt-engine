# Chapter 9 — Directional Convergence

*Volume II — Pressure Response, Inertia and Propagation.*
Draft of 3 November 2026. This chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`; the notation question for Chapters 25 onward does not touch it. Executable companion: `Textbook/examples/ch09_directional_convergence.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 9.1 The physical question

Chapter 4 gave the content a point receives, $\Phi = \kappa N\varepsilon$, and its direction-resolved form: along each ray the content arrives at a rate $\kappa\varepsilon/\ell$ per unit path length. A body in that arrival is pushed by it. Three questions fix what the push is.

1. How is the arriving content distributed over directions, and what does that distribution imply for a body at rest, for a body displaced from the centre of the domain, and for a pair of bodies?
2. What does a face or a body do to the content it receives? Arrival fixes the momentum brought to a surface; the momentum transferred depends on what the surface does with it.
3. Which of the factors that appear in the engine ($1/3$, $1/6$, $1/4$, $\pi/4$) belong to the arrival and which to the response of the body?

The chapter derives the moments of the directional distribution (Section 9.3), the tractions of the simplest boundaries (9.4), the anisotropy that a displaced observer sees (9.5), the force on a sphere and the force that a shadow removes (9.6–9.7), and ends with the points the engine leaves open (9.9).

## 9.2 Premises

Premises P1–P6 are those of Chapter 4 (Section 4.2). Two are added.

| id | premise | source |
|---|---|---|
| P7 | Content in transit carries momentum along its direction of travel at the rate (energy rate)$/c_{\rm relay}$. A density $U$ of arriving content, isotropic over directions, therefore has the directional momentum flux $q = U/4\pi$ per steradian. | not derived from P1–P6; recorded as residual R9.1 |
| P8 | A body acts on the content it receives through a stated boundary response: absorb, reverse the normal component, or re-emit with a stated angular distribution. | residual R9.2 |

In the engine's variables $U$ is $P_{\rm conv}=\Phi/\ell^3$ (`law_I::P_conv`, `laws.hpp:288`), read as a density of arriving content. The Ruleset's $\Pi_{ij}=(P_{\rm conv}/3)\delta_{ij}$ (T7) is then the second moment of the distribution (Section 9.3), and $P_{\rm conv}/3$ is the engine's isotropic stress (`law_IV`, `laws.hpp:607`). The vocabulary of P8 (absorb, reverse, re-emit) is the vocabulary of radiation pressure. The author ruled on 2026-11-03 that exclusion does not absorb movement and that spations and particles are different operators (a spation relays; a particle excludes and carries circulation). In this chapter the three responses are therefore *limiting bookkeeping cases* that fix the coefficients of the geometry, and none is offered as the mechanism by which a body acts on the medium (residual R9.6).

### 9.2.1 The medium and the displacement cascade

*Added 16 November 2026 from the author's statements of that date. The arithmetic was evaluated directly from the engine's stored values; it has not yet been placed under a registered instrument (residual R9.7).*

**What the medium is.** The bookkeeping of this chapter (content that arrives, a surface that returns it) can be misread as a picture of fast corpuscles crossing a void and striking bodies. The framework contains none of the three ingredients of that picture: no void, no gas through which matter swims, no corpuscles. The medium is an inviscid, non-solid, superfluid, crystalline-like arrangement at high pressure, of point granularity and volumetric consistency. A persistent form is a dislocating presence in it. The spations about the presence shrink slightly and rise in hardness along a gradient that is radial and omnidirectional. The arrival, the shadow and the responses of Sections 9.4 to 9.7 are the integral bookkeeping of that gradient and are not its mechanism.

Two classical objections to shadow models therefore have no object here. The heating computed for corpuscles that strike and lose energy on impact presupposes impacts; nothing strikes. And a body in steady motion through an inviscid superfluid meets no drag below the medium's limiting speed, which is the relay speed $c$ of the movement budget (Chapter 13).

**The cascade.** Let a presence exclude the volume $V$ (for a sphere, radius $R$ with $V=\tfrac43\pi R^3$). The spations that surrounded that volume are displaced by it, and they displace the next, and so on outward: displacement breeds displacement. Each successive shell holds the same volume $V$. The shell whose inner radius is $r$ has thickness

$$t(r)=\frac{V}{4\pi r^2}\qquad(r\gg R), \tag{9.11}$$

which is the outward displacement of the medium at $r$. The inverse square is the statement that one volume is carried through spheres of growing area. The shells have outer radii $r_k=R\,(k+1)^{1/3}$, and at the excluding surface the first has thickness of order $R/3$. The shells thin until one is a single spation thick, at

$$r_*=\sqrt{\frac{V}{4\pi\,\ell_P}}, \tag{9.12}$$

beyond which each further shell is less than one spation: the displacement continues, below the grain of the medium.

| presence | $V=V_{\rm disp}$ (m³) | $R_{\rm excl}$ (m) | $t(R_{\rm excl})=R_{\rm excl}/3$ (m) | $r_*$ (m) | shells to $r_*$ |
|---|---|---|---|---|---|
| electron | $9.980942\times10^{-62}$ | $2.877582\times10^{-21}$ | $9.5919\times10^{-22}$ | $2.2168\times10^{-14}$ | $4.57\times10^{20}$ |
| proton | $1.832653\times10^{-58}$ | $3.523686\times10^{-20}$ | $1.1746\times10^{-20}$ | $9.4991\times10^{-13}$ | $1.96\times10^{22}$ |

Table 9.1. The displacement cascade for the two exclusion volumes of Chapter 1 (COMPUTED from the Law IV volumes, which carry $m_e$, $m_p$, the stored $\ell_P$ and $R_{\rm CMB}$). The ratio $r_{*,p}/r_{*,e}=\sqrt{m_p/m_e}=42.850$ follows from (9.12). No significance is assigned here to the values of $r_*$.

**Relation to the shadow bookkeeping.** Equation (9.11) and the shadow result (9.10) carry the same $1/r^2$ for one geometric reason, a conserved quantity crossing spheres of area $4\pi r^2$: the displaced volume in the first, the removed solid angle in the second. A map from the displacement $t(r)$ to the push on a second presence, with its coefficient, is not derived (residual R9.7), so the two are set side by side and not yet identified.

## 9.3 The directional distribution and its moments

By Eq. (4.3) the content received from the cone $d\Omega$ about $\hat n$ is $d\Phi = (\kappa\varepsilon/4\pi\ell)\,L(\hat n)\,d\Omega$. Define the directional content

$$\phi(\hat n) = \frac{\kappa\,\varepsilon}{4\pi\,\ell}\,L(\hat n), \qquad \Phi = \oint\phi\,d\Omega. \tag{9.1}$$

At the centre of a ball of radius $R$, $L\equiv R$ and

$$\phi(\hat n) = \frac{\Phi}{4\pi}\quad\text{for every }\hat n \tag{9.2}$$

(Complete Laws, Theorem 3; the Ruleset and the engine do not number it, Chapter 5). The moments of $\phi$ are the physical content of the distribution.

$$M_0 = \oint\phi\,d\Omega = \Phi,\qquad
M_1 = \oint\phi\,\hat n\,d\Omega = \frac{\kappa\varepsilon}{\ell}\langle L\hat n\rangle,\qquad
\Pi_{ij} = \oint\phi\,n_in_j\,d\Omega. \tag{9.3}$$

$M_1$ is Eq. (4.6). For the isotropic distribution (9.2),

$$M_1 = 0,\qquad \Pi_{ij} = \frac{\Phi}{3}\,\delta_{ij}. \tag{9.4}$$

The vanishing of $M_1$ is the first law of motion in this framework (Complete Laws, Corollary 3.1): a body in isotropic arrival has no net direction pushed on it. The value of $\Pi_{ij}$ follows from $\oint n_in_j\,d\Omega=(4\pi/3)\delta_{ij}$ (instrument test V1). Dividing by $\ell^3$ turns $\Phi$ into $U=P_{\rm conv}$ and (9.4) into the Ruleset's T7.

*Numbering.* `Laws/SDT_Complete_Laws.md` writes $P_{\rm conv}=\Phi/(3\ell_P^3)$ in Corollary 3.2. The engine defines $P_{\rm conv}=\Phi/\ell^3$ and $P_{\rm cf}=P_{\rm conv}/3$. The Corollary's expression is the stress $\Pi$ of (9.4), the engine's $P_{\rm cf}$; the two sources use the symbol $P_{\rm conv}$ for different quantities. The supersession ledger carries the entry.

## 9.4 Tractions of a plane

$\Pi_{ij}$ describes the flow of momentum across an imaginary surface. An actual surface also acts on what arrives. Take isotropic arrival with $q=U/4\pi$ and a plane with outward normal $\hat m$; content arrives from the hemisphere $\hat n\cdot\hat m>0$ and travels along $-\hat n$.

*Absorbing plane.* Each direction delivers momentum rate $q\,(\hat n\cdot\hat m)\,d\Omega$ per unit area along $-\hat n$. The tangential parts cancel and

$$t_{\rm abs} = \int_{\hat n\cdot\hat m>0} q\,(\hat n\cdot\hat m)^2\,d\Omega = \frac{2\pi q}{3} = \frac{U}{6}. \tag{9.5}$$

*Specular plane.* Reversal of the normal component doubles the normal impulse:

$$t_{\rm spec} = 2\,t_{\rm abs} = \frac U3 = \frac{\operatorname{tr}\Pi}{3}. \tag{9.6}$$

*Diffusely re-emitting plane, albedo $\rho$.* The energy flux onto the plane per unit area is $c_{\rm relay}\int q\,\mu\,d\Omega = c_{\rm relay}U/4$, where $\mu=\hat n\cdot\hat m$. Re-emission with the cosine distribution of a diffuse surface returns recoil $2/3$ of the emitted momentum rate along the normal. Hence $t = U/6 + (2/3)\rho\,(U/4) = (1+\rho)\,U/6$, which equals (9.5) at $\rho=0$ and (9.6) at $\rho=1$.

*Proposition 9.1.* For the same isotropic arrival, the normal traction on a plane is $U/6$, $(1+\rho)U/6$ or $U/3$ according to the response (absorbing, diffuse with albedo $\rho$, specular). The engine's isotropic stress $P_{\rm conv}/3$ is the specular value and the trace share of the transport tensor; the traction on an absorbing face is half of it.

The earlier factor-six discrepancy in the traction work of 2026-10-27 arose from using $U/4\pi$ as $q$ while calling $U$ the absorbing-face pressure. With $q=U/4\pi$ stated, (9.5) and (9.6) are the same calculation with different responses.

Executed values (test T1, T2): $t_{\rm abs}/U = 0.166666666667$ and $t_{\rm spec}/U = 0.333333333333$, each within $3\times10^{-14}$ of the exact fraction; the tangential part of the absorbing traction was $5\times10^{-18}$.

## 9.5 The displaced observer and the limit of isotropy

For the target displaced a distance $s$ from the centre of a ball of radius $R$ (common-ball premise, Section 4.6), $L(\theta)$ is Eq. (4.10) and $M_1$ is Eq. (4.11). The second moment is no longer a multiple of $\delta_{ij}$. By symmetry it has the form $\Pi_{ij}=\Pi_\parallel\hat s_i\hat s_j+\Pi_\perp(\delta_{ij}-\hat s_i\hat s_j)$. Expanding the square root in (4.10) one order beyond the linear term, the term odd in $\cos\theta$ gives nothing to $\Pi$ and

$$\Pi_\parallel = \frac{\kappa\varepsilon}{\ell}\left[\frac R3 - \frac{s^2}{15R}\right],\qquad
\Pi_\perp = \frac{\kappa\varepsilon}{\ell}\left[\frac R3 - \frac{2s^2}{15R}\right]\qquad (s\ll R). \tag{9.7}$$

The trace is $\operatorname{tr}\Pi=\Phi(s)=(\kappa\varepsilon/\ell)\,R\,[1-s^2/3R^2]$, matching (4.12). The anisotropy is

$$\Pi_\parallel-\Pi_\perp = \frac{\kappa\varepsilon}{\ell}\,\frac{s^2}{15R}\left[1+\frac27\frac{s^2}{R^2}+O\!\left(\frac{s^4}{R^4}\right)\right],\qquad
\frac{\Pi_\parallel-\Pi_\perp}{\Phi} = \frac{s^2}{15R^2}. \tag{9.8}$$

*Proposition 9.2.* Under the common-ball premise, the stress seen by a displaced target is isotropic to relative order $s^2/15R^2$, with the stress larger along the displacement; the net directional content (4.11) is first order, $s/3R$ relative to $\Phi$. The first-order term is the only one that exerts a net force on a small body; the second-order anisotropy is a shear that appears across an extended one.

*Executed values (test T3).* The exact $L(\theta)$ was integrated to $10^{-15}$. The trace equals the closed form $\Phi(s)=\tfrac12[R+(A/s)\operatorname{asinh}(s/\sqrt A)]$, $A=R^2-s^2$, to $8\times10^{-16}$ relative. The scaled anisotropy $(\Pi_\parallel-\Pi_\perp)R/s^2$ is:

| $s/R$ | executed | $1/15$ | relative difference | registered limit $3(s/R)^2$ |
|---|---|---|---|---|
| 0.01 | 0.066668572 | 0.066666667 | $2.9\times10^{-5}$ | $3\times10^{-4}$ |
| 0.05 | 0.066714345 | 0.066666667 | $7.2\times10^{-4}$ | $7.5\times10^{-3}$ |
| 0.10 | 0.066858101 | 0.066666667 | $2.9\times10^{-3}$ | $3\times10^{-2}$ |

The $(2/7)(s/R)^2$ correction in (9.8) is the next term of the same expansion; for $s/R=0.10$ it predicts $0.0668571$, against the executed $0.0668581$.

*Scale.* With $R=R_{\rm CMB}=9.527\times10^{26}$ m (`measured::R_CMB`) and $s=1$ AU $=1.496\times10^{11}$ m, $s^2/15R^2\approx1.6\times10^{-33}$. At that displacement the shear is negligible beside the first-order term, which carries the whole effect. The estimate holds only if the common-ball premise (residual R9.3) holds.

## 9.6 A sphere in a beam

The Law III derivation applies the pressure deficit to the cross-section $\sigma_2=\pi R_2^2$ of body 2. This is exact for a sphere whose response is absorbing or specular, and it is not for every response.

Take a sphere of radius $a$ in a parallel beam of momentum flux $q_b$ (per unit area normal to the beam), travelling along $-\hat z$. A surface element with outward normal $\hat m$ and $\mu=\hat m\cdot\hat z>0$ is lit; it presents the area $\mu\,dA$ to the beam.

* Absorbing: $dF=q_b\,\mu\,dA$ along $-\hat z$. With $dA=a^2d\mu\,d\phi$, $F=q_b\pi a^2=q_b\sigma$.
* Specular: $d\vec F=-2q_b\mu^2\hat m\,dA$. The $z$-component integrates to $q_b\sigma$ (the factor $2\mu^3$ integrates to the same $\pi a^2$ as the absorbing $\mu$) and the transverse components cancel.
* Diffuse re-emission, albedo $\rho$: add the recoil $-(2/3)\rho\,q_b\mu\,\hat m\,dA$, whose $z$-component integrates to $(4/9)\rho\,q_b\sigma$.

*Proposition 9.3.* A sphere's total force from a parallel beam is $q_b\sigma$ for an absorbing or a specular surface, and $q_b\sigma\,(1+4\rho/9)$ for a diffuse surface of albedo $\rho$. The flat-plate coefficient $2\rho/3$ does not carry over to the sphere.

Executed (test T4): absorbing $1.000000000000$, specular $1.000000000000$ with transverse part $2\times10^{-17}$, and the diffuse sphere at $\rho=0.25,\,0.5,\,1$: $1.1111111111$, $1.2222222222$, $1.4444444444$; each within $1.1\times10^{-14}$ of $1+4\rho/9$. The recoil coefficient per unit albedo was $0.444444444444$.

## 9.7 The force that a shadow removes

A body 1 of radius $R_1$ at distance $r$ takes out of the arriving distribution the cap of directions it subtends, half-angle $\alpha$ with $\sin\alpha=R_1/r$. Body 2 is an absorbing or specular sphere, so by Proposition 9.3 each direction $\hat n$ that reaches it contributes the force $\sigma_2\,q\,d\Omega$ along $-\hat n$, whatever the direction. Isotropic arrival gives zero in total; removing the cap leaves the removed part with the sign reversed. Along the axis,

$$F = \sigma_2\,q\int_{\rm cap}\mu\,d\Omega
= \sigma_2\,q\;2\pi\!\int_{\cos\alpha}^{1}\!\mu\,d\mu
= \sigma_2\,q\;\pi\sin^2\alpha
= \sigma_2\,q\,\frac{\pi R_1^2}{r^2}. \tag{9.9}$$

The weight $\mu$ is the projection of each removed direction on the axis. With $q=U/4\pi$ and $\sigma_2=\pi R_2^2$,

$$\boxed{\;F = \frac{\pi}{4}\,U\,\frac{R_1^2R_2^2}{r^2}.\;} \tag{9.10}$$

This is the Law III form with $U$ for the pressure coefficient. The $1/r^2$ and the coefficient $\pi/4$ come from the geometry of the shadow and the response of the target, and (9.9) is exact for every $r\ge R_1$ when the target is of negligible size. For a finite spherical target the partial coverage of its cross-section enters, and Chapter 10 shows that the total, (9.10), is exact for every $r\ge R_1+R_2$.

The projected solid angle $\Omega_{\rm proj}=\pi R_1^2/r^2$ is not the unweighted cap $\Omega_{\rm cap}=2\pi(1-\sqrt{1-R_1^2/r^2})$. Their ratio is $G(x)=2(1-\sqrt{1-x})/x$, $x=(R_1/r)^2$:

| $r/R_1$ | $\Omega_{\rm cap}/\Omega_{\rm proj}$ |
|---|---|
| 1 | 2.000000000 |
| 1.5 | 1.145898034 |
| 2 | 1.071796770 |
| 5 | 1.010205144 |
| 10 | 1.002512579 |
| 100 | 1.000025001 |

They agree in the far field, $G=1+x/4+\dots$, and differ at contact by a factor 2. The force of a single removed direction is $\sigma_2 q$ along the line of the beam; only the axial part survives the sum, so the projected form (9.9) is the force of a removed cap on an absorbing or a specular sphere. The unweighted cap is a different model of near-contact saturation (the engine's E105 form, `solid_angle_cap`, `laws.hpp:578`); it is not a correction of (9.9) and the distinction matters for $r/R_1\lesssim2$.

Executed (test T5): for $r/R_1=1,\,1.5,\,2,\,5,\,10,\,100$, $\int_{\rm cap}\mu\,d\Omega$ and $\Omega_{\rm cap}$ by quadrature agree with $\pi R_1^2/r^2$ and $2\pi(1-\sqrt{1-R_1^2/r^2})$ to $2.3\times10^{-13}$ relative or better. T5 is a check of the instrument and of the algebra of (9.9); it contains no new physical content beyond the statement that $\mu$ is the weight.

## 9.8 Emitting boundaries

A body in the medium is not an inert absorber. Net traction is the momentum of the arriving content minus the momentum carried away by what the body returns, plus any momentum released from stored deformation. Proposition 9.3 gives the first example of the dependence: the same incident beam produces $q_b\sigma$ or $q_b\sigma(1+4\rho/9)$ depending on how the surface returns it. An outgoing distribution that is isotropic in the body's rest state returns no net momentum, so the absorbing value stands. A rotating, occluding or anisotropically processing body can have a net outgoing momentum, and then the force on it differs from (9.10) by that amount. Chapter 10 treats the geometry of occlusion in more detail; Chapter 12 takes up the stored deformation.

## 9.9 Input ledger and residuals

The quantities in Sections 9.4–9.7 are geometric: the executed values depend on no measured input. The scale estimate in Section 9.5 uses `measured::R_CMB` and the IAU astronomical unit.

**Residuals.**

- **R9.1 — momentum carried by content (P7).** That the content in transit carries momentum $(\text{energy})/c_{\rm relay}$, with the isotropic flux $q=U/4\pi$, is assumed here. It is not derived from the relay premises P1–P6, and the identification of $P_{\rm conv}$ with the density $U$ (rather than with a stress) is part of it. The investigation of 2026-10-27 records that the radiation pressure of the microwave background, $u_{\rm CMB}/3$, is not the same quantity as $P_{\rm conv}=Nu_{\rm CMB}$.
- **R9.2 — the boundary response of matter (P8).** Propositions 9.1 and 9.3 show that the traction and the sphere force depend on how a surface returns the content. For the Law III coefficient $\pi/4$ to be universal across Coulomb, gravity and nuclear forces, the effective response must be the same, absorbing or specular, in all three. A derivation of the response of a persistent form from its structure is outstanding.
- **R9.3 — common or own domain.** Whether any anisotropy exists (Section 9.5) depends on residual R4.2.
- **R9.4 — which factor Law IV needs.** The engine's resistance law uses $P_{\rm conv}/3$, the specular value (9.6) and the trace share of $\Pi$. The traction on an absorbing boundary of the engaged volume is $P_{\rm conv}/6$. Which of the two, or an intermediate $(1+\rho)/6$, belongs to the boundary of the engaged volume is not fixed by Law IV's premises; Chapter 12 returns to it. The Ruleset's T7 states $\tau=1/3$ as the normal projection of the isotropic tensor, which is (9.4) and (9.6) and not (9.5).
- **R9.5 — symbol use.** $P_{\rm conv}$ names $\Phi/\ell^3$ in the engine and $\Phi/3\ell^3$ in Corollary 3.2 of the Complete Laws (Section 9.3).
- **R9.6 — operator-level account.** The responses of Sections 9.4 and 9.6 borrow the vocabulary of radiation pressure. A statement of the force in operator terms (the relay operator of a spation against the exclusion and circulation of a particle), with no absorption, is outstanding; the coefficients $U/6$, $U/3$, $\pi/4$ are properties of the geometry under the stated responses and survive only as far as such an account reproduces them.
- **R9.7 — from displacement to push.** The displacement cascade of Section 9.2.1 gives $t(r)=V/(4\pi r^2)$. The law that turns that displacement, and the accompanying shrink and hardening of the spations, into the push on a second presence is not derived, and the arithmetic of Table 9.1 has no registered instrument yet.

## 9.10 Implementation and verification

Build and run:

```
cl /std:c++20 /EHsc /O2 /utf-8 /I Engine/include /Fe:ch09.exe Textbook/examples/ch09_directional_convergence.cpp
./ch09.exe
```

The instrument uses Gauss–Legendre quadrature in $\cos\theta$ and a trapezoid rule in $\phi$; no vector type is used. Tests V1–V3 (instrument validation) and T1–T6 are those of `Textbook/validation/ch09_PRE_REGISTRATION.md`; the criteria were registered before the tool existed. The single run (`ch09_run1_output.txt`) met every criterion. T6 compares `law_III::solid_angle_occluded`, `solid_angle_cap`, `cap_over_projected` (`laws.hpp:567, 578, 587`) and `F_occlusion` (`laws.hpp:535`) with the chapter's closed forms to $2.2\times10^{-16}$ or better. T6 shows that the chapter and the engine state the same expressions; it does not test the magnitude of $P_{\rm eff}$, which is Chapter 11's.

## 9.11 Exercises and answers

**Exercise 1.** Show that the traction of an absorbing plane under isotropic arrival is $U/6$.

*Answer.* $t=\int_{\mu>0}q\,\mu^2\,d\Omega = q\cdot2\pi\int_0^1\mu^2d\mu = 2\pi q/3$. With $q=U/4\pi$, $t=U/6$.

**Exercise 2.** A plane has albedo $\rho$ and re-emits diffusely. Find the normal traction.

*Answer.* The absorbed momentum rate is $U/6$. The absorbed energy flux over $c_{\rm relay}$ is $U/4$; the re-emitted part is $\rho U/4$, and the diffuse recoil carries $2/3$ of it: $\rho U/6$. Total $(1+\rho)U/6$.

**Exercise 3.** Show that $\Pi_{ij}$ of an isotropic distribution has trace $\Phi$.

*Answer.* $\operatorname{tr}\Pi=\oint\phi\,\hat n\cdot\hat n\,d\Omega=\oint\phi\,d\Omega=\Phi$, and isotropy makes $\Pi_{ij}=A\delta_{ij}$, so $3A=\Phi$.

**Exercise 4.** Expand $L(\theta)$ to second order in $s/R$ and derive (9.7).

*Answer.* $L\approx R - s\mu - s^2(1-\mu^2)/2R$. The $-s\mu$ term is odd in $\mu$ and gives zero against $\mu^2$ and $1-\mu^2$. With $\kappa\varepsilon/\ell=1$ and $\phi=L/4\pi$, the remaining integrals are $\int(1-\mu^2)\mu^2d\mu=4/15$ (parallel) and $\tfrac12\int(1-\mu^2)^2d\mu=8/15$ (perpendicular), giving the corrections $-s^2/15R$ and $-2s^2/15R$ added to $R/3$.

**Exercise 5.** Find the force on a sphere of radius $R_2$ from a cap of directions of half-angle $\alpha$ when the response is absorbing.

*Answer.* $F=\sigma_2q\,\pi\sin^2\alpha$ by (9.9). For $\alpha=\pi/2$ (the half-space), $F=\sigma_2q\pi=\sigma_2U/4$.

**Exercise 6.** At what $r/R_1$ does the unweighted cap exceed the projected by 1 %?

*Answer.* $G=1+x/4+\dots=1.01$ gives $x\approx0.04$, so $r/R_1\approx5.0$. The executed value of $G$ at $r/R_1=5$ is $1.010205$.

## 9.12 Scope

Established in this chapter, from P1–P8: the isotropy of the arrival at the centre and the moments (9.2)–(9.4); the tractions of the absorbing, diffuse and specular plane ($U/6$, $(1+\rho)U/6$, $U/3$); the anisotropy of the stress at a displaced target, $s^2/15R^2$; the force on a sphere in a beam for three responses; and the force of a removed cap, $(\pi/4)\,U\,R_1^2R_2^2/r^2$, exact for $r\ge R_1$ with an absorbing or specular target of negligible size, and (Chapter 10) for every $r\ge R_1+R_2$ with a finite spherical target. The quadratures reproduce these to $10^{-12}$ or better.

Not established: the momentum carried by the content (R9.1), the response of a persistent form (R9.2), the choice of domain (R9.3), which traction factor the resistance law needs (R9.4), and the law that takes the displacement cascade of Section 9.2.1 to a push (R9.7). The magnitude of the coefficient $U$ is $P_{\rm conv}$ here; the engine's force law uses the atomic $P_{\rm eff}$, a separate quantity taken up in Chapter 11.

*Where it leads.* Chapter 10 takes the shadow geometry (overlaps, finite-body corrections); Chapter 11 sets (9.10) against the engine's Law III with $P_{\rm eff}$ and the transfer function; Chapter 12 resolves the factor of R9.4 for the engaged volume.
