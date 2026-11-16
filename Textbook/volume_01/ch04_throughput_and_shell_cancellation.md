# Chapter 4 — Throughput and Shell Cancellation

*Volume I — Ontology, Geometry and Admissible States.*
Draft of 27 October 2026. Executable companion: `Textbook/examples/ch04_shell_cancellation.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 4.1 The physical question

A point of the contact medium receives deformation content from every spation inside its causal domain. The domain holds of order $10^{62}$ shells. Three outcomes are possible in principle: the arriving content grows with the number of shells, with the square of that number, or with its cube; and in each case it can arrive with a net direction or without one.

Law I states that the content a point receives is $\Phi = N\varepsilon$, linear in the shell count, with no net direction at the centre of the domain. This chapter derives that statement from its premises, finds the size of the departures from it, and derives what an observer displaced from the centre of the domain receives instead. The arrival of content at a point, with its direction, is the input to the directional-convergence and occlusion chapters (Chapters 9–11); the resistance law (Chapter 12) uses its pressure form.

## 4.2 Premises

| id | premise | constitutional source |
|---|---|---|
| P1 | The medium consists of contiguous cells of edge $\ell$ and volume $\ell^3$. Each cell holds deformation content $\varepsilon$ [J]. | R1, R3 |
| P2 | The content of every cell was released omnidirectionally. | R5 |
| P3 | Content moves by nearest-neighbour relay. A point receives the content of sources within $N$ relay passes, $N = R/\ell$, where $R$ is the radius of its causal domain. | R2, R4 |
| P4 | Relay is faithful: the content crossing successive spherical surfaces about a source is conserved, up to a per-pass loss fraction $\delta$ (Section 4.7). | Complete Laws §4, Lemma 1 |
| P5 | Euclidean three-dimensional geometry holds across the domain. | geometric |
| P6 | A target of cross-section $\sigma$ intercepts, from a source at distance $D$, the fraction of the source's content equal to the solid angle it subtends divided by $4\pi$. | geometric |

*Numbering.* The Ruleset (`Theory/00_Ruleset.md`) numbers shell structure R4 and omnidirectional release R5, and lists shell cancellation as axiom R6 and as theorem T1. `Laws/SDT_Complete_Laws.md` §4 cites isotropic release as R4 and fidelity as R5. This chapter follows the Ruleset numbering. It derives the shell identity from P1–P6, so R6 is the statement proved here and T1 is its proof; the supersession ledger carries the entry and Chapter 5 resolves the numbering.

## 4.3 The ray-length form

Let a target sit at a point and let $\hat n$ be a direction from it. Consider the cone of solid angle $d\Omega$ about $\hat n$, and let $L(\hat n)$ be the distance along $\hat n$ to the edge of the causal domain.

The sources between distance $D$ and $D + dD$ in the cone number

$$dN_{\rm src} = \rho\, D^2\, d\Omega\, dD, \qquad \rho = \ell^{-3}. \tag{4.1}$$

Each delivers the fraction of its content that the target intercepts. For a spherical target of radius $a$, $\sigma = \pi a^2$, the intercepted fraction is the cap fraction

$$f(D) = \tfrac12\left(1 - \sqrt{1 - a^2/D^2}\right) = \frac{\sigma}{4\pi D^2}\left[1 + \frac{a^2}{4D^2} + O\!\left(\frac{a^4}{D^4}\right)\right]. \tag{4.2}$$

In the far field only the leading term survives, and the product of (4.1) and (4.2) has no $D$ in it:

$$d\Phi = \varepsilon\, f\, dN_{\rm src} = \frac{\kappa\,\varepsilon}{4\pi\,\ell}\, d\Omega\, dD, \qquad \kappa \equiv \sigma\rho\ell = \frac{\sigma}{\ell^2}. \tag{4.3}$$

The growth of the source count as $D^2$ cancels the dilution of each source's content as $D^{-2}$. This is the shell cancellation. Integrating over $D$ from the target out to the edge of the domain, then over direction,

$$\boxed{\;\Phi = \frac{\kappa\,\varepsilon}{\ell}\,\langle L\rangle, \qquad \langle L \rangle = \frac{1}{4\pi}\oint L(\hat n)\, d\Omega.\;} \tag{4.4}$$

*Proposition 4.1 (shell cancellation, continuum form).* Under P1–P6 in the far field, the content received per unit path length along any ray is $\kappa\varepsilon/\ell$, independent of distance. The total content received is $\kappa\varepsilon/\ell$ times the direction-averaged ray length to the edge of the domain.

For a point at the centre of a ball of radius $R$, $L = R$ for every direction and

$$\Phi = \kappa\, N\, \varepsilon, \qquad N = R/\ell. \tag{4.5}$$

Law I takes $\kappa = 1$ (Section 4.9, residual R4.1). Equation (4.5) with $\kappa = 1$ is theorem T2.

The net directional content is the first moment of the same representation:

$$\vec F = \frac{\kappa\,\varepsilon}{\ell}\,\langle L\,\hat n\rangle . \tag{4.6}$$

*Dimension check.* $\kappa$ and $L/\ell$ are dimensionless, so $\Phi$ and $|\vec F|$ carry the dimension of $\varepsilon$, joules. With $\varepsilon = u_{\rm CMB}\ell^3$, $P_{\rm conv} = \Phi/\ell^3$ has the dimension of energy density, pascals.

## 4.4 Shell counting and the kernel exponent

In lattice terms, label the shell at distance $d$ cells from the target. Its population is $4\pi d^2$ to leading order, and each member delivers $\kappa\varepsilon/(4\pi d^2)$, so

$$|S_d|\cdot \frac{\kappa\varepsilon}{4\pi d^2} = \kappa\,\varepsilon \quad\text{for every } d, \qquad \Phi = \sum_{d=1}^{N}\kappa\varepsilon = \kappa N\varepsilon. \tag{4.7}$$

The boundary-cell count $S = 4\pi N^2$ recorded in the engine (`laws.hpp:292`) is the shell population at $d = N$.

The inverse-square dilution is a consequence of P4 and P5: content conserved across spherical surfaces of area $4\pi D^2$ falls as $D^{-2}$. It is not an additional premise. Its role shows when the exponent is varied. If a relay kernel fell as $D^{-q}$, the shell at distance $d$ would contribute in proportion to $d^{\,2-q}$ and

$$\Phi_q \;\propto\; \varepsilon \sum_{d=1}^{N} d^{\,2-q} \;\sim\; \frac{\varepsilon\, N^{\,3-q}}{3-q}. \tag{4.8}$$

*Proposition 4.2.* Only $q = 2$ gives a contribution that is constant per shell and a total linear in $N$. With $q = 1$ the total scales as $N^2 \approx 3.5\times10^{123}$ and with $q = 0$ as $N^3 \approx 2.0\times10^{185}$ in the engine's units, which are the divergent alternatives that Law I excludes. In $n$ spatial dimensions the same construction requires $q = n-1$.

*Correspondence.* Equal contribution from every shell is the counting structure of Olbers' argument for a static uniform source distribution. Here the sum terminates at $N$ because P3 limits the causal domain, so it is finite. The shared structure is recorded as convergent.

## 4.5 Finite-shell corrections

**Solid-angle expansion.** Equation (4.2) gives the relative correction of the exact spherical-target fraction to the far-field form as $+a^2/(4D^2)$. For a face-on disc target the correction is $-3a^2/(4D^2)$. Taking $\sigma = \ell^2$, so $a^2 = \ell^2/\pi$, the executed values are:

| $d$ | exact / far-field $- 1$ | $a^2/(4D^2)$ |
|---|---|---|
| 1 | $+0.0955$ | $+0.0796$ |
| 2 | $+0.0207$ | $+0.0199$ |
| 3 | $+0.0090$ | $+0.0088$ |
| 10 | $+0.000797$ | $+0.000796$ |
| 100 | $+0.000008$ | $+0.000008$ |

The corrections matter for the innermost shells only. Their sum over shells converges: with the leading term, $\sum_{d\ge1} a^2/(4d^2) = \pi/24 \approx 0.131$ in units of $\kappa\varepsilon$.

**Discrete shell population.** For cells at the points of the cubic lattice $\mathbb Z^3$ with Euclidean distance, the shell population is $4\pi d^2 + \pi/3$ plus lattice-point fluctuations, which grow more slowly than $d^2$. The direct lattice sums $S(R) = \sum_{0<|p|\le R} f(|p|)$ for both kernels were evaluated in one pass at $R = 16$ to $256$ (Section 4.10). Their offset from the continuum value $R$ does not grow:

$$S_{\rm pt}(R) - R \approx -0.71, \qquad S_{\rm sph}(R) - R \approx -0.60, \qquad 16 \le R \le 256. \tag{4.9}$$

Hence $\Phi = \kappa\varepsilon\,[N + O(1)]$. The $O(1)$ constant depends on the lattice, the kernel and the boundary convention; the universal content of the result is the term linear in $N$. At $N = 5.9\times10^{61}$ the offset is a relative $10^{-62}$.

**The edge of the domain.** By (4.4), $\Phi$ is linear in the ray length. A taper of width $w$ at the edge changes $\langle L\rangle$ by $O(w)$, and an uncertainty $\delta R$ in the radius of the domain enters as $\delta\Phi/\Phi = \delta R/R$ with Jacobian $J = \kappa\varepsilon/\ell$. In the engine $R$ is the measured Clearing distance (`measured::R_CMB`), so the uncertainty of $\Phi$ is the uncertainty of that measurement.

## 4.6 The displaced observer

Equation (4.6) is exact at the centre of the domain, where $L$ is constant and $\langle L\,\hat n\rangle = 0$. Displace the target a distance $s$ from the centre of a ball of radius $R$ along $\hat s$, and let $\theta$ be the angle between $\hat n$ and $\hat s$. Solving $|s\hat s + L\hat n|^2 = R^2$ gives

$$L(\theta) = -s\cos\theta + \sqrt{R^2 - s^2\sin^2\theta}. \tag{4.10}$$

The component of (4.6) along $\hat s$ is $\langle L\cos\theta\rangle$. The square-root term is even under $\theta \to \pi - \theta$ while $\cos\theta$ is odd, so it integrates to zero against $\cos\theta$; the remaining term gives $-s\langle\cos^2\theta\rangle = -s/3$. Therefore

$$\boxed{\;\vec F = -\frac{\kappa\,\varepsilon}{\ell}\,\frac{s}{3}\,\hat s .\;} \tag{4.11}$$

*Proposition 4.3.* For a target at distance $s < R$ from the centre of a uniform ball of sources, the net directional content is $(\kappa\varepsilon/\ell)(s/3)$, exact in the continuum far-field form, and it points toward the centre of the ball: more content arrives from the side with the longer ray. The coefficient comes from $\langle n_in_j\rangle = \delta_{ij}/3$.

The scalar content falls away from the centre at second order:

$$\Phi(s) = \frac{\kappa\varepsilon}{\ell}\,R\left[1 - \frac{s^2}{3R^2} + O\!\left(\frac{s^4}{R^4}\right)\right], \qquad \frac{|\vec F|}{\Phi} = \frac{s}{3R}\ \ (s\ll R). \tag{4.12}$$

The pressure form follows with $P_{\rm conv} = \Phi/\ell^3$:

$$|\nabla P| = \frac{P_{\rm conv}}{3R}. \tag{4.13}$$

Since $P_{\rm conv} = \kappa\, u_{\rm CMB}\, R/\ell$, (4.13) reduces to $\kappa\, u_{\rm CMB}/(3\ell)$, independent of $R$.

The factor $1/3$ here and the factor $1/3$ in the traction condition $\Pi_{ij} = (P_{\rm conv}/3)\delta_{ij}$ (T7) are the same object: the second moment $\langle n_i n_j\rangle$ of the isotropic direction distribution.

**Domain premise.** Equations (4.10)–(4.13) assume a common source ball: the displaced target and the centre of the ball are different points of the same medium. If each target instead carries its own ball, $L \equiv R$ for every target, $\vec F = 0$ everywhere and there is no gradient. Law I's premises do not select between these two. The engine's convergence floor (`laws.hpp:731`, `convergence_floor::pressure_gradient`) uses the common-ball form. This is residual R4.2.

## 4.7 Fidelity

If each relay pass retains the fraction $\tau = 1-\delta$ of the content, the shell at distance $d$ contributes $\kappa\varepsilon\,\tau^d$, and

$$\Phi_\delta = \kappa\varepsilon\,\frac{\tau\,(1-\tau^N)}{1-\tau} \;\approx\; \kappa N\varepsilon\left(1 - \frac{N\delta}{2}\right) \quad (N\delta \ll 1). \tag{4.14}$$

*Proposition 4.4.* The first-order form is a departure from (4.5) of relative size $N\delta/2$. For the engine's $N = 5.894\times10^{61}$ the premise of faithful relay is therefore quantitative:

$$\delta \ll 1.7\times10^{-62}\ \text{per pass}, \qquad \delta \le 3.4\times10^{-64}\ \text{for a departure below 1\%}. \tag{4.15}$$

For $\delta > 0$ the sum saturates at $\Phi_\infty = \kappa\varepsilon\,\tau/\delta$ however large $N$ becomes. The accumulation rule $d\Phi/dN = \kappa\varepsilon$ (theorem T2: each additional shell brought into the domain adds $\varepsilon$) holds only while $N\delta \ll 1$.

## 4.8 Worked examples and executed values

All figures below are from `Textbook/validation/ch04_run2_output.txt` (source `Textbook/examples/ch04_shell_cancellation.cpp`; repository head `5b3e0c1` with the uncommitted `laws.hpp` of 2026-10-27).

**Example 4.1 — the engine's Law-I quantities.**

| quantity | value | engine reference | inputs |
|---|---|---|---|
| $u_{\rm CMB} = aT_{\rm CMB}^4$ | $4.174783\times10^{-14}$ J m$^{-3}$ | `law_I::u_CMB`, line 252 | $T_{\rm CMB}=2.7255$ K (FIRAS), $a = 7.5657\times10^{-16}$ |
| $N = R_{\rm CMB}/\ell_P$ | $5.894491\times10^{61}$ | `law_I::N`, line 264 | $R_{\rm CMB} = 9.527\times10^{26}$ m, $\ell_P = 1.616255\times10^{-35}$ m |
| $\varepsilon = u_{\rm CMB}\ell_P^3$ | $1.762640\times10^{-118}$ J | `law_I::epsilon`, line 273 | as above |
| $\Phi = N\varepsilon$ | $1.038986\times10^{-56}$ J | `law_I::Phi`, line 284 | as above |
| $P_{\rm conv} = \Phi/\ell_P^3 = N u_{\rm CMB}$ | $2.460822\times10^{48}$ Pa | `law_I::P_conv`, line 288 | as above |
| $\lvert\nabla P\rvert = P_{\rm conv}/(3R_{\rm CMB})$ | $8.609992\times10^{20}$ Pa m$^{-1}$ | `convergence_floor::pressure_gradient`, line 731 | as above |

The engine's closed forms and equations (4.5) and (4.13) agree to $10^{-12}$ relative (test T6). That test establishes that the chapter and the engine state the same expression; the magnitudes carry the measured inputs in the last column. The comments in `laws.hpp` at lines 253, 273, 285 and 289 quote the values for $T_{\rm CMB} = 2.725$ K ($4.172\times10^{-14}$, $1.761\times10^{-118}$, $1.038\times10^{-56}$, $2.459\times10^{48}$); the code as executed uses 2.7255 K and gives the figures in the table.

**Example 4.2 — lattice shell sums (tests V1, V2, T3).** The instrument reproduced the lattice-point counts $7, 33, 123, 257, 515, 4169$ for $R = 1,2,3,4,5,10$ and the simple-cubic sums $\sum'|p|^{-6} = 8.40191$ and $\sum'|p|^{-12} = 6.20215$ before it was applied to the shell sums:

| $R$ | $S_{\rm pt}(R)$ | $S_{\rm sph}(R)$ | $S_{\rm pt}-R$ | $S_{\rm sph}-R$ |
|---|---|---|---|---|
| 16 | 15.2659 | 15.3759 | $-0.734$ | $-0.624$ |
| 32 | 31.2756 | 31.3881 | $-0.724$ | $-0.612$ |
| 64 | 63.2878 | 63.4015 | $-0.712$ | $-0.599$ |
| 128 | 127.2822 | 127.3965 | $-0.718$ | $-0.603$ |
| 256 | 255.2882 | 255.4028 | $-0.712$ | $-0.597$ |

The pre-registered criterion $|S-R|\le1$ was met at every $R$.

**Example 4.3 — displaced observer (test T4).** Lattice units, $\kappa=\varepsilon=\ell=1$:

| $R$ | $s$ | $F_x$ | $\lvert F\rvert$ | $s/3$ | relative difference |
|---|---|---|---|---|---|
| 64 | 4 | $-1.33333$ | 1.33333 | 1.33333 | $1.0\times10^{-6}$ |
| 96 | 8 | $-2.66667$ | 2.66667 | 2.66667 | $6.5\times10^{-7}$ |
| 96 | 24 | $-8.00005$ | 8.00005 | 8.00000 | $6.1\times10^{-6}$ |

The transverse components were below $10^{-15}$. The criterion was agreement within 2 % with the sign of $F_x$ negative; both were met. The case $s/R = 1/4$ lies well outside the small-displacement regime, and (4.11) holds there as an exact statement.

**Example 4.4 — fidelity (test T5).** For $(N,\delta) = (10^3, 10^{-4})$ the direct sum is $951.575897$ against the first-order $950$; for $(10^5, 10^{-7})$ it is $99501.6575$ against $99500$. Closed form and direct sum agree to the last printed digit in both cases.

*Record of the run.* The first run (`ch04_run1_output.txt`) met every criterion except the second case of T5, which gave a relative difference of $2.6\times10^{-12}$ against the registered $10^{-12}$. The two routes had used different roundings of $\tau$ (long double is 64-bit under MSVC). That is an instrument fault; the routes were made to share one stored $\tau$ and the direct sum was compensated, the criterion was left unchanged, and the second run (`ch04_run2_output.txt`) met all criteria.

## 4.9 Input ledger and residuals

| quantity | role | status |
|---|---|---|
| $\ell_P$ | cell edge | `measured::l_P`, stored numeric. The exact koppa–wake closure of $\ell_P$ is recorded in FLM06; the stored number is the reference used by the engine. |
| $T_{\rm CMB}$ | sets $u_{\rm CMB}$ and so $\varepsilon$ | measured (FIRAS), 2.7255 K |
| $a$ | radiation constant | 7.5657e-16 J m$^{-3}$ K$^{-4}$ |
| $R_{\rm CMB}$ | sets $N$ | measured Clearing distance, `measured::R_CMB`. The engine records the magnitude of $N$, $\Phi$ and $P_{\rm conv}$ as inheriting this input (`laws.hpp:282–283`). |
| $\kappa$ | interception constant, $\sigma/\ell^2$ | set to 1 by the engine's definition $\varepsilon = u_{\rm CMB}\ell^3$ |
| $\delta$ | per-pass relay loss | premise P4; bounded by (4.15) |

The relations (4.4)–(4.6), (4.11)–(4.14) are derived from P1–P6. The numbers in Example 4.1 carry the measured inputs above.

**Residuals.**

- **R4.1 — the constant $\kappa$.** The value $\kappa = 1$ means the interception cross-section equals $\ell^2$. A cubic cell presents between $\ell^2$ (face-on) and $\sqrt3\,\ell^2$ (corner-on) and $\tfrac32\ell^2$ averaged over orientation. A value of $\kappa$ other than 1 rescales $P_{\rm conv}$ and every quantity downstream of it, including the transfer function $P_{\rm eff}/P_{\rm conv}$. A derivation of $\kappa$ from the geometry of the cell is outstanding. The exponent and the linear dependence on $N$ do not depend on it.
- **R4.2 — common or own domain.** Section 4.6.
- **R4.3 — fidelity.** Bound (4.15) is a requirement on the medium. A derivation that relay in the contact medium is faithful to that precision is outstanding; Chapter 14 returns to it.
- **R4.4 — the lattice.** The lattice type fixes the $O(1)$ offset in (4.9) and the $O(d)$ term of the shell population; the choice of lattice for the contact medium is open.

## 4.10 Implementation and verification

Build and run:

```
cl /std:c++20 /EHsc /O2 /I Engine/include /Fe:ch04.exe Textbook/examples/ch04_shell_cancellation.cpp
./ch04.exe
```

Tests V1–V2 (instrument validation) and T3–T6 are those of `Textbook/validation/ch04_PRE_REGISTRATION.md`; the criteria were registered before the tool existed.

## 4.11 Exercises and answers

**Exercise 1.** A relay kernel falls as $D^{-1}$. Show that $\Phi \propto N^2$ and evaluate it for the engine's $N$ in units of $\varepsilon$.

*Answer.* By (4.8) with $q=1$ the shell at $d$ contributes in proportion to $d^{2-1} = d$. The sum over $d = 1\ldots N$ is $N(N+1)/2 \approx N^2/2 \approx 1.7\times10^{123}$ in units of the first shell's contribution.

**Exercise 2.** Find the per-pass loss $\delta$ for which $\Phi$ departs from $N\varepsilon$ by 1 %.

*Answer.* From (4.14), $N\delta/2 = 0.01$, so $\delta = 0.02/N = 3.4\times10^{-64}$.

**Exercise 3.** Sources occupy only the shell $R_1 \le D \le R_2$ about the target. Find $\Phi$.

*Answer.* $L$ is replaced by $R_2 - R_1$ in (4.4): $\Phi = \kappa\varepsilon\,(R_2-R_1)/\ell$. $\Phi$ counts the occupied shells along each ray.

**Exercise 4.** Expand $\langle\sqrt{R^2 - s^2\sin^2\theta}\rangle$ for $s \ll R$ and recover (4.12).

*Answer.* $\sqrt{R^2-s^2\sin^2\theta} \approx R(1 - s^2\sin^2\theta/2R^2)$ and $\langle\sin^2\theta\rangle = 2/3$, giving $R\,(1 - s^2/3R^2)$. The $-s\cos\theta$ term averages to zero.

**Exercise 5.** Show $\langle n_in_j\rangle = \delta_{ij}/3$.

*Answer.* Isotropy forces $\langle n_in_j\rangle = A\,\delta_{ij}$. Its trace is $\langle n_in_i\rangle = 1$, so $3A = 1$.

**Exercise 6.** Use (4.13) to show $|\nabla P| = \kappa u_{\rm CMB}/(3\ell_P)$ and evaluate it.

*Answer.* $P_{\rm conv} = \kappa N u_{\rm CMB} = \kappa u_{\rm CMB} R/\ell$, so $P_{\rm conv}/(3R) = \kappa u_{\rm CMB}/(3\ell)$. With the executed values, $4.174783\times10^{-14}/(3\times1.616255\times10^{-35}) = 8.610\times10^{20}$ Pa m$^{-1}$, matching Example 4.1.

## 4.12 Scope

Established in this chapter, from P1–P6: the shell identity (4.3); $\Phi = \kappa N\varepsilon$ with corrections of order $1/N$ at faithful relay; the requirement (4.15) on that fidelity; and the displaced-observer result (4.11)–(4.13), which was confirmed by direct lattice summation to $10^{-5}$.

Not established: the value of $\kappa$ (R4.1), the choice between a common and a per-target domain (R4.2), the fidelity of relay in the medium (R4.3), and the lattice (R4.4). The magnitudes of $N$, $\varepsilon$, $\Phi$ and $P_{\rm conv}$ carry the measured inputs $R_{\rm CMB}$, $T_{\rm CMB}$ and the stored $\ell_P$.

*Where it leads.* Chapters 9–11 take the direction-resolved form (4.4), (4.6) as the input for directional convergence, the occlusion integral and Law III; Chapter 12 takes (4.13) with the engaged volume for the resistance law; Chapter 48 treats the dependence of $N$ on the relay count.
