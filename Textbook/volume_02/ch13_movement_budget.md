# Chapter 13 — Movement Budget

*Volume II — Pressure Response, Inertia and Propagation.*
Circulation, translation, recurrence and directional resistance. Draft of 9 November 2026: the text of 27 October 2026, reconciled with the sources and re-executed. Notation: $\mathrm{Om}=R/k^2$, $k=c/v$ and $z=\mathrm{Om}/r$ as in the production default of `Textbook/NOTATION_LEDGER.md`; they enter Sections 13.13 and 13.15. In this book a *clock* is a counted recurring mechanism (Chapter 3): a reading $\tau$ is a count of cycles and $d\tau/dt$ is a ratio of two counts. Executable companion: `Textbook/examples/ch13_movement_budget.cpp`; pre-registration and captured output in `Textbook/validation/`.

### 13.1 Physical scope

A persistent displacement structure must maintain circulation while participating in translational motion through the contact medium. The movement budget describes the allocation of a finite relay-processing resource between persistence and translation. The surrounding convergence remains the mechanical loading environment. Translation, clock response and resistance belong to the same contact-response problem.

The engine implements the saturated relation

$$
v_{\mathrm{circ}}^2+v^2=c^2. \tag{13.1}
$$
Here v is translational speed and v_circ is the effective circulation-budget speed. The reference c denotes the applicable relay limit in the declared frame and medium state. The chapter first treats constant c and a persistent structure with constant rest-state resistance. Environmental variation receives separate treatment in Section 13.14.

Equation (13.1) is the native allocation premise implemented by `sdt::laws::law_V`. Consequences must preserve the distinction between the allocation rule, the geometric construction realising the rule and the response of a concrete contact structure. A match between the resulting expressions and established relativistic dynamics is correspondence; the derivation path remains the SDT path presented below.

### 13.2 Operational definitions

| Quantity | Definition | Dimension | Required procedure |
|---|---|---|---|
| c | Applicable relay-processing speed | L/T | Declared hop length divided by compatible hop duration |
| v | Translational speed | L/T | Change in physical locus relative to the declared frame and clock |
| v_circ | Effective circulation-budget speed | L/T | Mode allocation sustaining recurring form |
| beta | v/c | 1 | Compatible speed roles and units |
| chi | v_circ/c | 1 | Normalised persistence allocation |
| gamma | 1/chi on the saturated branch | 1 | Derived budget response |
| tau | Accumulated local clock reading | T | Count of a specified recurring mechanism |
| t | Reference clock reading | T | Declared comparison frame |
| ell_circ | Effective recurrence-path length | L | Specified path and geometry |
| E0 | Rest-state engaged resistance energy | Energy | Law-IV displacement relation |
| m0 | E0/c^2 | Mass | Resistance coefficient; no extraction from koppa |
| p | Translational momentum magnitude | Momentum | Impulse response or corresponding persistence action |

The circulation-budget variable does not automatically equal an unwrapped winding-phase velocity, a surface-coordinate phase speed or a signal-front speed. Such identifications require a propagation and geometry map. The repository explicitly uses super-c phase-winding proxies in some nuclear investigations; substitution of those proxies into Equation (13.1) would exchange operational meanings.

The symbol chi in this chapter denotes circulation fraction, not the phase-loading descriptor used in the arrest discussion. The equation register must retain separate identifiers for both meanings.

### 13.3 Orthogonality: geometric and modal statements

For physical velocity contributions u_circ and u_trans,

$$
\lVert\mathbf u\rVert^2
=\lVert\mathbf u_{\mathrm{circ}}\rVert^2
+\lVert\mathbf u_{\mathrm{trans}}\rVert^2
+2\mathbf u_{\mathrm{circ}}\cdot\mathbf u_{\mathrm{trans}}. \tag{13.2}
$$
Pointwise orthogonality removes the cross term. A fixed translation direction, however, is not perpendicular to every tangent of a general closed circulation path. The physical construction must therefore specify the scope of the orthogonality premise.

A mode-averaged formulation can instead use

$$
\langle\mathbf u_{\mathrm{circ}},\mathbf u_{\mathrm{trans}}\rangle_w
=\int_\mathcal C w(\sigma)
\mathbf u_{\mathrm{circ}}(\sigma)\cdot
\mathbf u_{\mathrm{trans}}(\sigma)\,d\sigma=0, \tag{13.3}
$$
with nonnegative weight w and normalisation integral w d_sigma=1. The weight must follow from engaged contact participation. Equation (13.3) is a possible operational interpretation of orthogonal mode allocation, not an asserted microscopic replacement for the repository premise.

The distinction prevents a scalar budget from silently claiming a pointwise geometric property. A contact calculation must determine the relevant mode measure and cross coupling.

### 13.4 Bound, saturation and persistent equilibrium

Orthogonal composition and a relay limit first establish an inequality:

$$
v_{\mathrm{circ}}^2+v^2\leq c^2. \tag{13.4}
$$
The equality in Equation (13.1) additionally selects a saturated persistence branch. Define a possible unallocated fraction

$$
s=1-\frac{v_{\mathrm{circ}}^2+v^2}{c^2},\qquad s\geq0. \tag{13.5}
$$
The implemented branch has s=0. A sub-saturated branch would need an independent account of structural persistence and available response channels.

For a schematic supporting stress P_support=rho_eng v_circ^2, an unchanged external stress and fixed supporting area require

$$
\rho_{\mathrm{eng}}(v)v_{\mathrm{circ}}^2(v)
=\rho_{\mathrm{eng}}(0)c^2. \tag{13.6}
$$
Under the saturated budget,

$$
\rho_{\mathrm{eng}}(v)=\gamma^2\rho_{\mathrm{eng}}(0). \tag{13.7}
$$
Equation (13.7) is a compatibility condition for that particular supporting-stress model. Alternative responses can redistribute supporting area, contact orientation, engaged content and circulation geometry. The movement budget alone does not determine the redistribution. The physical question is why a moving structure preserves equilibrium despite reduced circulation allocation.

### 13.5 Budget angle and circulation fraction

Normalise Equation (13.1):

$$
\chi^2+\beta^2=1,\qquad 0\leq\beta<1. \tag{13.8}
$$
For a persistent positive-circulation branch,

$$
\chi=\sqrt{1-\beta^2},\qquad
\gamma=(1-\beta^2)^{-1/2}. \tag{13.9}
$$
The angle representation

$$
\beta=\sin\zeta,\qquad\chi=\cos\zeta,
\qquad 0\leq\zeta<\frac\pi2 \tag{13.10}
$$
parameterises the allocation circle. The budget angle zeta is not a spatial orientation or a nuclear seating angle.

The sensitivities are

$$
\frac{d\chi}{d\beta}=-\frac\beta\chi,
\qquad
\frac{d\gamma}{d\beta}=\beta\gamma^3. \tag{13.11}
$$
As beta approaches unity, circulation allocation approaches zero and incremental gamma response becomes large. The mathematical limit specifies the edge of the persistent massive branch. A separate radiative branch is needed to describe finite-energy propagation after persistence disappears.

### 13.6 Recurrence and operational clock response

Let a clock cycle require circulation over effective length ell_circ. The reference-clock period is

$$
T(v)=\frac{\ell_{\mathrm{circ}}(v)}{v_{\mathrm{circ}}(v)}. \tag{13.12}
$$
At rest, T0=ell_circ,0/c. Define lambda_circ=ell_circ(v)/ell_circ,0. Then

$$
\frac{T(v)}{T_0}=\frac{\lambda_{\mathrm{circ}}}{\chi},
\qquad
\frac{d\tau}{dt}=\frac{T_0}{T(v)}
=\frac{\chi}{\lambda_{\mathrm{circ}}}. \tag{13.13}
$$
The engine clock expression follows for a recurrence mechanism with unchanged effective path length:

$$
\boxed{\frac{d\tau}{dt}=\chi
=\sqrt{1-\frac{v^2}{c^2}}=\frac1\gamma.} \tag{13.14}
$$
Thus clock response follows from circulation allocation plus a specified recurrence geometry. A deforming recurrence path must retain the lambda_circ factor until the structure determines the response.

For variable speed in a homogeneous medium and an admissible quasistatic clock response,

$$
\tau(t_1)-\tau(t_0)
=\int_{t_0}^{t_1}\sqrt{1-v^2(t)/c^2}\,dt. \tag{13.15}
$$
Quasistatic validity requires structural relaxation fast enough to track the imposed change. Acceleration-dependent clock deformation cannot be dismissed by the instantaneous-speed expression alone.

### 13.7 Longitudinal extent from round-trip closure

Consider a persistence path with leading and trailing boundaries separated by reference-frame extent L. Let the assembly translate uniformly at v along the separation direction. A signal relayed at reference speed c takes

$$
t_+=\frac L{c-v},\qquad t_-=\frac L{c+v} \tag{13.16}
$$
to complete the respective legs. The total is

$$
T_{\mathrm{round}}
=\frac{2Lc}{c^2-v^2}
=\frac{2L}{c}\gamma^2. \tag{13.17}
$$
At rest, T_round,0=2L0/c. Require the longitudinal closure cycle to remain synchronised with the persistence clock, T_round=gamma T_round,0. Then

$$
\boxed{L=L_0/\gamma.} \tag{13.18}
$$
The result uses a common reference clock, uniform motion during both relay legs, directional reference propagation speeds c, and synchronisation between longitudinal closure and the selected persistence clock. The derivation fixes the factor of two by carrying both legs explicitly. No fixed Cartesian component representation is required: the length and heading can be expressed as a spherical locus and bearing.

Transverse extent requires a separate geometric statement. An isotropic density response cannot be inferred from longitudinal contraction alone.

### 13.8 Law-IV resistance and persistence energy

The preceding chapter gives

$$
E_0=P_{\mathrm{cf}}V_{\mathrm{disp}},\qquad
P_{\mathrm{cf}}=\frac{\Phi}{3P_l^3},\qquad
m_0=\frac{E_0}{c^2}. \tag{13.19}
$$
The rest resistance coefficient follows from engaged displacement and the convergence state. Equation (13.19) does not identify the envelope volume with the engaged volume.

A persistence-action reconstruction supplies a unified route to the engine energy and momentum expressions. Let one local cycle carry action magnitude J0 and let the rest recurrence rate be nu0. Assume constant action per local cycle for the unperturbed structure. The free persistence action is

$$
\mathcal A=-J_0\int dN_{\mathrm{local}}
=-J_0\nu_0\int d\tau. \tag{13.20}
$$
Identify E0=J0 nu0 and use Equation (13.14):

$$
\mathcal A=-E_0\int\sqrt{1-v^2/c^2}\,dt. \tag{13.21}
$$
Equation (13.21) is a conditional reconstruction: constant action per local cycle is an additional persistence-response premise. The movement budget alone does not establish that premise. The action is a variational quantity, not an assertion that a resting structure continuously dissipates E0 per unit time.

No Planck-scale action magnitude is inserted to obtain the following algebra. Absolute action normalisation remains a structural question.

### 13.9 Momentum and energy from the persistence action

For the free persistence Lagrangian

$$
\mathscr L=-E_0\sqrt{1-v^2/c^2}, \tag{13.22}
$$
the directional derivative with respect to translational velocity gives

$$
\mathbf p=\frac{\partial\mathscr L}{\partial\mathbf v}
=\frac{E_0}{c^2}\gamma\mathbf v
=m_0\gamma\mathbf v. \tag{13.23}
$$
The energy follows from the Legendre transform:

$$
E=\mathbf p\cdot\mathbf v-\mathscr L
=E_0(\gamma\beta^2+\chi)=\gamma E_0. \tag{13.24}
$$
The last equality uses chi=1/gamma and beta^2=1−1/gamma^2. Consequently,

$$
\boxed{E^2-c^2p^2=E_0^2.} \tag{13.25}
$$
The path of arrival is circulation allocation → recurrence clock → constant action per local cycle → momentum and energy. The resulting expressions coincide with established relativistic energy and momentum. The correspondence does not substitute for the microscopic derivation of the persistence-action premise.

Kinetic energy is

$$
K=(\gamma-1)E_0
=\frac{\gamma^2\beta^2}{\gamma+1}E_0. \tag{13.26}
$$
The second expression avoids subtracting nearly equal values at small speed. Expansion gives

$$
K=\frac12m_0v^2+\frac38m_0\frac{v^4}{c^2}
+\frac5{16}m_0\frac{v^6}{c^4}+O(v^8/c^6). \tag{13.27}
$$
In particular, the low-speed curvature of the persistence Lagrangian is E0/c^2, agreeing with the Law-IV resistance coefficient.

### 13.10 Direction-dependent acceleration response

For fixed m0 and c,

$$
\frac{d\gamma}{dt}
=\gamma^3\frac{\mathbf v\cdot\mathbf a}{c^2}. \tag{13.28}
$$
Differentiate Equation (13.23):

$$
\mathbf F=\frac{d\mathbf p}{dt}
=m_0\gamma\mathbf a
+m_0\gamma^3\frac{\mathbf v\cdot\mathbf a}{c^2}\mathbf v. \tag{13.29}
$$
Let e_v be the direction of motion. Split acceleration into physical headings parallel and perpendicular to e_v. Then

$$
F_{\parallel}=m_0\gamma^3a_{\parallel},\qquad
F_{\perp}=m_0\gamma a_{\perp}. \tag{13.30}
$$
Given an unmodified acceleration budget a_budget=F/m0,

$$
\boxed{\mathbf a=
\frac{\mathbf a_{\mathrm{budget},\parallel}}{\gamma^3}
+\frac{\mathbf a_{\mathrm{budget},\perp}}\gamma.} \tag{13.31}
$$
Equation (13.31) matches the engine's `law_v_response`. The scalar 1/gamma factor alone is insufficient for a force changing speed along the current heading.

For a_budget with magnitude A and angular separation psi from the velocity heading,

$$
a_{\parallel}=A\chi^3\cos\psi,\qquad
a_{\perp}=A\chi\sin\psi, \tag{13.32}
$$
$$
|\mathbf a|=A\sqrt{\chi^6\cos^2\psi+\chi^2\sin^2\psi}, \tag{13.33}
$$
and the response heading relative to velocity is

$$
\psi_a=\operatorname{atan2}(\chi\sin\psi,\chi^3\cos\psi). \tag{13.34}
$$
The atan2 form preserves the forward/backward quadrant. At v=0 no velocity heading is needed; return the original acceleration. At v≥c the massive response branch is outside the admitted domain.

The spherical implementation obtains psi from angular separation, constructs the perpendicular heading by a quarter-turn offset and combines the scaled loci. An absent vector denotes zero magnitude. The construction changes the physical response without requiring a global Cartesian state triple.

### 13.11 Work, transverse force and steady curvature

For fixed E0 and c,

$$
\frac{dE}{dt}=\mathbf F\cdot\mathbf v. \tag{13.35}
$$
A transverse force has zero instantaneous translational power while changing heading. Zero instantaneous work does not imply zero momentum exchange.

For a steady circular trajectory of curvature radius rho,

$$
a_{\perp}=v^2/\rho,
\qquad F_{\perp}=m_0\gamma v^2/\rho. \tag{13.36}
$$
The relation describes response to an already specified circular trajectory. It neither selects rho nor replaces the source occlusion calculation. Radiation, medium circulation and source recoil require the complete system balance.

### 13.12 Numerical examples from the canonical implementation

The instrument of this edition reads every constant from `laws.hpp` and the spherical response from `occlusion_sphere.hpp`. Its criteria were registered before it was written (`Textbook/validation/ch13_PRE_REGISTRATION.md`); a probe of the same chapter written on 2026-10-27 is a retrieval lead and is not cited. Results are COMPUTED implementation correspondence, not a new experimental validation.

Test T1 evaluated the engine's `v_circ`, `time_dilation`, `gamma`, `total_energy` and `momentum` at six speeds and compared them with the budget arithmetic; the worst relative differences were $4.3\times10^{-13}$ (at $\beta=0.9999$, where $1-\beta^2$ itself carries rounding).

| $\beta$ | $\chi$ = clock fraction | $\gamma$ | $p/(m_0c)$ | $a_\parallel/a_{\rm budget,\parallel}=\chi^3$ | $a_\perp/a_{\rm budget,\perp}=\chi$ | $(E^2-c^2p^2)/E_0^2-1$ |
|---:|---:|---:|---:|---:|---:|---:|
| 0 | 1 | 1 | 0 | 1 | 1 | 0 |
| 0.1 | 0.994987437107 | 1.0050378153 | 0.1005037815 | 0.985037562736 | 0.994987437107 | $-2.2\times10^{-16}$ |
| 0.6 | 0.8 | 1.25 | 0.75 | 0.512 | 0.8 | $-2.2\times10^{-16}$ |
| 0.8 | 0.6 | 1.6666666667 | 1.3333333333 | 0.216 | 0.6 | $-3.3\times10^{-16}$ |
| 0.99 | 0.141067359797 | 7.0888120501 | 7.0179239296 | 0.00280724046 | 0.141067359797 | $-1.2\times10^{-14}$ |
| 0.9999 | 0.014141782066 | 70.7124459519 | 70.7053747073 | $2.828\times10^{-6}$ | 0.014141782066 | $-9.1\times10^{-13}$ |

Table 13.1. The saturated budget, executed (T1, T4). The last column is the energy-momentum invariant in units of $E_0^2$; its growth at large $\gamma$ is the cancellation between $E^2$ and $c^2p^2$, each of order $\gamma^2$.

*Round trip (T2).* $T_{\rm round}=2Lc/(c^2-v^2)$ equalled $2L\gamma^2/c$ to $1.7\times10^{-13}$, and the contraction obtained from the synchronisation $T_{\rm round}=\gamma T_{\rm round,0}$ equalled the engine's `length_contraction` to $2.2\times10^{-16}$.

*Kinetic energy (T3).* The cancellation-free form (13.26) and the direct $(\gamma-1)E_0$ agreed to $1.7\times10^{-12}$ for $\beta\ge0.01$. At $\beta=10^{-4}$ the direct form gives $5.000000191657\times10^{-9}$ against $5.000000037500\times10^{-9}$, a relative difference of $3\times10^{-8}$: about eight digits lost. At $\beta=0.01$ the difference between $K/E_0$ and the three-term series (13.27) equals the next term $35\beta^8/128$ to $4\times10^{-4}$ of itself, and the four-term series equals $K/E_0$ to $2.7\times10^{-16}$.

*Directional response (T4).* With loci for the velocity and the budget acceleration, `law_v_response` returned the magnitude (13.33) to $1.6\times10^{-14}$ over 20 cases ($\beta=0.1,0.6,0.8,0.99$; $\psi=0,45^\circ,90^\circ,135^\circ,180^\circ$) and the heading (13.34) to $4.4\times10^{-16}$ rad over the 12 oblique cases. The parallel factor was $\chi^3$ and the perpendicular factor $\chi$ to $1.6\times10^{-14}$, and at $v=0$ the acceleration was returned unchanged. At $\beta=0.8$ a parallel force produces 21.6% of the unmodified acceleration and a perpendicular force 60%. For a budget heading of $45^\circ$ the ratio $a_\perp/a_\parallel$ is $\gamma^2=25/9$ and the response heading $70.2011^\circ$ (T9); for $\beta=0.6$ and equal components $\tan\psi_a=0.8/0.512=1.5625$. These headings are analytic illustrations, not measured trajectories.

*Independent derivative (T5).* The central difference of the engine's `momentum` with step $c(1-\beta)\times10^{-4}$ divided by $m_0\gamma^3$ gave $1.0000000043$, $1.0000000048$, $1.0000000055$ and $1.0000000062$ for $\beta=0.1,0.6,0.8,0.99$, inside the registered $2\times10^{-6}$; and $d\gamma/d\beta=\beta\gamma^3$ held to $1.6\times10^{-9}$.

*Variable parameters and the radiative limit (T7, T8).* At fixed $v$ and $c(t)=c_0(1+\epsilon t)$, the numerical $\dot\gamma$ equalled $-\gamma^3\beta^2\dot c/c$ to $5.5\times10^{-10}$ at $\beta_0=0.3,0.8$. With $E_0=E_*/\gamma$ the energy is $E_*$ and $pc/E_*=\beta=1-10^{-8}$ exactly.

### 13.13 Translational clock response and pressure-depth response

The current depth implementation uses

$$
C_{\mathrm{depth}}(z)=1-z,\qquad
z=\mathrm{Om}/r. \tag{13.37}
$$
**Status of the depth.** Equation (13.37) takes the depth to be $z=\mathrm{Om}/r$, as the engine's depth-closure block does. The author's ruling of 2026-11-03 is that the relay slowing is not koppa over radius and must come out of the model (Chapter 3, R3.6). The relations of this section are therefore reported as relations among the engine's clock factor, its far-frame speed and the squared loading they require, with the engine's values of $z$ taken as the engine's. Whether $\Lambda_{\rm depth}$ names a physical loading is not claimed. Executed (T6): $(1-z)^2+(2z-z^2)=1$ exactly at $z=0,0.01,0.1,0.25,0.5,0.9$, and the engine's `clock_rate` and `c_far` equal $1-z$ and $c(1-z)^2$ to $1.1\times10^{-16}$. The linear branch $c(1-2z)$ would need the local duration factor $H_h=(1-z)^2/(1-2z)$ of (13.44): $1.000102$ at $z=0.01$, $1.0125$ at $0.1$ and $1.125$ at $0.25$.

An earlier movement-budget text assigns a single depth-cost fraction z directly to a squared-speed budget, producing sqrt(1−z). The two expressions represent different allocations. The earlier expression and current implementation must not be interchanged within a calculation.

If a normalised squared persistence budget is required to reproduce the current clock factor under unchanged recurrence path length, the remaining squared circulation is

$$
\chi_{\mathrm{depth}}^2=(1-z)^2. \tag{13.38}
$$
The complementary squared loading must consequently be

$$
\boxed{\Lambda_{\mathrm{depth}}=1-(1-z)^2=2z-z^2.} \tag{13.39}
$$
Equation (13.39) is an algebraic compatibility requirement, not an independently derived physical flow speed. A material transport velocity must not be manufactured by relabelling sqrt(Lambda_depth)c. The contact mechanism must explain how pressure-depth loading creates the required persistence cost.

The first-order distinction is explicit:

$$
\sqrt{1-z}=1-\frac z2-\frac{z^2}{8}+O(z^3),
\qquad C_{\mathrm{depth}}=1-z. \tag{13.40}
$$
The source header records a solar-redshift motivation for the change. Independent measurement comparison belongs to the dedicated spectral chapter; the present chapter establishes the required budget distinction.

Translation and depth cannot be combined by adding z to beta^2 without a mode-allocation argument. A factorised clock law C_depth sqrt(1−beta_local^2) requires a sequential local-clock construction and a declared local propagation speed. A shared additive squared budget would instead specify another combined law. The physical contact structure must select the composition rule.

### 13.14 Relay duration, reference units and state variation

Let P_l(z) be a hop length expressed in a declared common length convention, Delta_tau_hop(z) the hop duration measured by the local clock, and C_depth=d_tau/d_t. The reference-clock hop duration is

$$
\Delta t_{\mathrm{hop}}=\Delta\tau_{\mathrm{hop}}/C_{\mathrm{depth}}. \tag{13.41}
$$
Therefore

$$
c_{\mathrm{far}}=\frac{P_l C_{\mathrm{depth}}}{\Delta\tau_{\mathrm{hop}}}. \tag{13.42}
$$
Define normalised hop length L_h=P_l/P_l,infty and local hop duration H_h=Delta_tau_hop/Delta_tau_hop,infty. With C_depth,infty=1,

$$
\frac{c_{\mathrm{far}}}{c_\infty}
=\frac{L_h C_{\mathrm{depth}}}{H_h}. \tag{13.43}
$$
The active square branch follows from L_h=C_depth=1−z and H_h=1. Applying another clock-slowing factor afterwards would count the same transformation twice.

For the same L_h and C_depth, an exact linear branch c_far/c_infty=1−2z would require

$$
H_h=\frac{(1-z)^2}{1-2z},\qquad z<\frac12. \tag{13.44}
$$
Thus the branch distinction can be expressed as a local-duration response question. Equation (13.44) is the duration required by the candidate branch, not evidence for the candidate. The clock transformation determines bookkeeping; contact mechanics determines the constitutive functions.

When m0 or c changes physically within one fixed unit and clock convention, differentiate momentum before applying the constant-parameter response. For beta=v/c,

$$
\dot\gamma=\gamma^3\left(
\frac{\mathbf v\cdot\mathbf a}{c^2}
-\beta^2\frac{\dot c}{c}\right), \tag{13.45}
$$
$$
\dot{\mathbf p}
=m_0\gamma\mathbf a
+m_0\dot\gamma\mathbf v
+\dot m_0\gamma\mathbf v. \tag{13.46}
$$
An environmental response therefore adds terms absent from Equation (13.31). Local changes of measurement convention must be distinguished from physical changes in the parameters. A globally varying medium additionally requires an interaction/action law determining force and energy exchange with the environment.

### 13.15 Circular boundaries and axial passage

The orbital branch is

$$
v_{\mathrm{orb}}(r)=c\sqrt{\mathrm{Om}/r}. \tag{13.47}
$$
Identification of v_orb with the translational speed in Equation (13.1) requires compatible local c, clock and medium definitions. Under that identification,

$$
v_{\mathrm{circ}}=c\sqrt{1-\mathrm{Om}/r},\qquad r>\mathrm{Om}. \tag{13.48}
$$
The circular massive branch exhausts the budget as r approaches Om. This is a branch boundary, not a proof that every interior structure or phase pattern is impossible. The repository includes interior phase-winding proxies; propagation role and geometry determine admissibility.

A centre-crossing trajectory has no requirement to remain circular. For physical azimuthal extent rho,

$$
v_\phi=\rho\dot\phi. \tag{13.49}
$$
A zero-width axial line has zero displacement under rotation about the same axis. Longitudinal passage remains a different motion. For finite-speed central passage, nonzero orbital angular momentum must transfer into source, medium or outgoing channels before the transverse radius vanishes.

The full accounting condition is

$$
\frac{d}{dt}(\mathbf L_{\mathrm{body}}+
\mathbf L_{\mathrm{source}}+\mathbf L_{\mathrm{medium}})
+\boldsymbol{\mathcal J}_{L,\mathrm{out}}
=\boldsymbol{\mathcal N}_{\mathrm{external}}. \tag{13.50}
$$
Movement arrest, circular degeneration and contact torque remain connected but distinct calculations. Chapter 40 develops the transition using the actual source and contact response.

### 13.16 Radiative endpoint and finite energy

At chi=0, the saturated speed allocation gives beta=1. The massive formulas cannot be evaluated by independently setting m0=0 and gamma=infinity. A finite-energy endpoint requires a controlled joint limit:

$$
E=\gamma E_0\to E_*>0,
\qquad E_0\to0,\qquad p\to E_*/c. \tag{13.51}
$$
The disappearance of persistent engaged exclusion does not imply disappearance of transported energy. The release-cascade description treats outgoing disturbances as continuing relay content. A finite transition requires matching energy, momentum and any angular-momentum flux across the change of structural branch.

The movement budget does not specify the emitted frequency distribution, polarisation, pulse envelope or conversion rate. Such observables require the wave and emission constructions in later chapters.

### 13.17 Technical implementation specification

1. Accept speed magnitudes only when finite and in 0≤v<c for a persistent massive response. Require positive finite c and an identified speed role.
2. Use a declared reference frame and clock. Never substitute c_far for local c inside beta without the transformation defining the substitution.
3. Compute chi near beta=1 using sqrt((1−beta)(1+beta)) where appropriate to reduce cancellation. The implemented c^2−v^2 expression and the normalised form require comparison at representational limits.
4. Compute kinetic energy with the cancellation-free expression in Equation (13.26) at small beta.
5. At zero velocity, return the unmodified acceleration without constructing a velocity heading.
6. Preserve the sign of the parallel response and the quadrant of the resulting heading. Use spherical separation, bearing and offset operations for native state.
7. Distinguish a mathematical zero vector, a rejected state and an unavailable result. The present optional-locus return surface can represent more than one cause of absence; session diagnostics must retain the cause.
8. Do not clamp an above-c state into validity. Reduce/reject the step or transition under an explicitly defined physical rule.
9. Recalculate environment-dependent rest resistance where the constitutive model requires state variation. Constant-m0 response is a declared regime.
10. Use convergence checks for trajectory integration independently of pointwise formula checks. Numerical agreement at one timestep does not establish dynamics over a trajectory.

### 13.18 Exercises with technical solutions

**Exercise 13.1 — Variable recurrence geometry.** For ell_circ/ell_circ,0=chi^a, derive the clock response.

**Solution.** Equation (13.13) gives d_tau/d_t=chi^(1−a). The engine clock follows for a=0. A path shortening exactly in proportion to circulation fraction, a=1, leaves the cycle rate unchanged in this simplified construction. The physical structure must determine a.

**Exercise 13.2 — Round-trip closure.** Retain a factor-of-two distinction between one-way extent and full recurrence length and recover longitudinal contraction.

**Solution.** T_round=2Lgamma^2/c and T0=2L0/c. Synchronisation T_round=gamma T0 gives L/L0=1/gamma. Omitting the same factor from both expressions leaves the ratio unchanged; omitting the factor from only one expression changes the predicted length by two.

**Exercise 13.3 — Directional response at beta=0.6.** A force-per-rest-resistance budget has equal parallel and perpendicular magnitudes A/sqrt(2). Determine the output components.

**Solution.** chi=0.8. Equation (13.32) gives a_parallel=0.512A/sqrt(2) and a_perp=0.8A/sqrt(2). The response heading satisfies tan(psi_a)=0.8/0.512=1.5625. Both components remain positive and the heading rotates towards the transverse direction.

**Exercise 13.4 — Depth budget.** Determine the complementary squared loading required for C_depth=0.75 under fixed recurrence length.

**Solution.** chi_depth=0.75, so Lambda_depth=1−0.75^2=0.4375. The associated depth is z=0.25. Assigning Lambda=z instead would give sqrt(0.75), a different clock response.

**Exercise 13.5 — Environmental variation.** For a body with fixed physical velocity but time-varying m0 and c, determine whether momentum remains constant.

**Solution.** With a=0, Equations (13.45)–(13.46) give dot_p=[gamma dot_m0−m0 gamma^3 beta^2 dot_c/c]v. Fixed velocity does not imply fixed momentum under physical parameter variation. Environmental exchange must account for the difference.

**Exercise 13.6 — Finite radiative endpoint.** Choose E0=E*/gamma and beta→1. Evaluate energy and momentum.

**Solution.** E=E* for every gamma in the constructed family. p=E* beta/c→E*/c. This demonstrates a mathematically controlled limit; a physical conversion process requires the contact/release dynamics establishing the family.

### 13.19 Source and assessment register

| Item | Source | Treatment in this chapter |
|---|---|---|
| Native saturated budget and scalar responses | `Engine/include/sdt/laws.hpp`, `law_V` (lines 895–954) | existing implemented premise and expressions |
| Rest resistance energy | `laws.hpp`, `law_IV` | existing displacement relation (Chapter 12) |
| Spherical directional response | `Engine/include/sdt/occlusion_sphere.hpp`, `law_v_response` | derived from the momentum response; re-executed |
| Earlier movement-budget narrative | `Laws/SDT_Complete_Laws.md`, Law V | historical derivation with its assumptions made explicit |
| Current depth clock, hop length and far speed | `laws.hpp`, `depth_closure` | the engine's relations; separate from the older depth-cost allocation; R3.6 applies |
| Release and outward content | `Laws/THE_RELEASE_CASCADE_THEOREM.md` | physical context and radiative-branch accounting |
| Persistence-action reconstruction | Eqs. (13.20)–(13.25) | conditional derivation with the constant-action-per-cycle premise stated |
| Numerical examples | `Textbook/validation/ch13_run2_output.txt` | COMPUTED implementation correspondence |

### 13.20 Input ledger and residuals

All executed values are COMPUTED from the engine's relations or DERIVED (exact algebra); no measured input enters except $c$, a unit bridge. The speed role in $\beta$ is the local relay speed.

**Residuals.**

* **R13.1 — scope of orthogonality.** The budget equality $v_{\rm circ}^2+v^2=c^2$ is axiom M3 (posited). Pointwise orthogonality of the circulation and translation velocities is not true of every tangent of a general closed path; the mode-averaged form (13.3) needs a derived weight.
* **R13.2 — the persistence action.** The derivation of $E$ and $\vec p$ in (13.20)–(13.25) uses constant action per local cycle, a premise additional to the budget.
* **R13.3 — transverse extent.** Longitudinal contraction follows from round-trip closure; the transverse extent and the density response (13.7) are not derived.
* **R13.4 — depth composition.** The identification $z=\mathrm{Om}/r$ (Chapter 3, R3.6) and the rule for composing translation with depth (factorised or additive) are open.
* **R13.5 — two sources for $\gamma$.** In this book $\gamma$ is obtained from the budget (13.9); it does not rest on Corollary 7.1 of the Complete Laws, whose distribution does not return $\gamma$ (Chapter 12, R12.2).
* **R13.6 — the radiative branch.** The joint limit (13.51) is a controlled mathematical limit; the conversion dynamics that realise it are not given.
* **R13.7 — an engine surface.** The optional-locus return of the spherical response cannot distinguish a zero vector, a rejected state and an unavailable result (Section 13.17, item 7).

### 13.21 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch13_movement_budget
```

Criteria were registered in `Textbook/validation/ch13_PRE_REGISTRATION.md` before the instrument existed. Run 1 met every criterion except the series clause of T3, whose registered tolerance ($10^{-14}$) was below the truncation error of a three-term series; the clause was replaced by one that compares the difference with the next term and tests the four-term series, and the record is in the pre-registration. Run 2 (`ch13_run2_output.txt`) is the run of record and met every criterion.

### 13.22 Scope

Established in this chapter: the consequences of the saturated budget as stated, with their arithmetic reproduced: the circulation fraction, clock fraction and Lorentz factor (13.9); longitudinal contraction by round-trip closure (13.18); energy and momentum with the invariant $E^2-c^2p^2=E_0^2$ (13.25); the cancellation-free kinetic energy and its series; the direction-dependent response $\chi^3$ and $\chi$ (13.31) in the engine's spherical form; the algebraic depth-loading relation; the variable-parameter derivatives; and the controlled radiative limit.

Not established: the orthogonality scope (R13.1), the persistence-action premise (R13.2), the transverse response (R13.3), the composition of depth and translation (R13.4), and the conversion dynamics of the radiative branch (R13.6).

*Where it leads.* Chapter 14 derives the wave propagation requirements, mode dispersion and the distinction between phase, group and front response; the contact recurrence law must connect those quantities to the budget variables without exchanging operational meanings. Chapter 33 uses the circular branch (13.47), and Chapter 49 the equivalence of the inertial response across compositions.
