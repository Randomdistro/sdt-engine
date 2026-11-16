# Chapter 35 — Retarded Many-Body Occlusion

*Volume V — Bodies, Fields and Propagation.*
Draft of 10 November 2026. Notation: $R$ is a body radius; $\rho=R/3$ the radius of a channel circle; $\beta=v_s/c$; $t_r$ the retarded time. Executable companion: `Textbook/examples/ch35_retarded_many_body_occlusion.cpp`; pre-registration and captured output in `Textbook/validation/`. The seven-circle representation is a declared numerical boundary model; it is not the opaque-sphere theorem of Chapter 10 (Proposition 10.1), and the chapter checks the model, not the theorem.

## 35.1 The physical question

A finite body shadows another along a line of centres, and when the bodies move the shadow a target sees depends on where the source was when its influence left it. The questions are how the engine represents a finite body (the channel construction), how accurate that representation is where it matters (near contact and at an occultation edge), how retardation is solved and when it is expensive, and which tests exercise the shielding branch. Agreement on unshielded circular orbits alone does not.

## 35.2 Channel construction

The engine assigns seven channels to a body of radius $R$ facing a pair partner: one central channel with weight $1/9$ and six outer channels with weight $4/27$ each, on a ring of radius $2R/3$ in the plane normal to the line of centres (`occlusion.hpp`, `central_weight`, `outer_weight`, `channel_offset`). The weights sum to one.

The weights are the area bookkeeping of seven circles of radius $\rho=R/3$ packed in the disc of radius $R$. **Executed (T1).** The ring centres are at distance $2\rho$ from the central centre and from their neighbours (touching), to $3.3\times10^{-16}$; every circle lies inside the disc, the outer extent being $R$ to $2.2\times10^{-16}$; the seven circles cover $7/9$ of the disc, leaving $2/9$ uncovered. The central weight $1/9$ is the area fraction of its own circle; each outer weight is its own $1/9$ plus one sixth of the uncovered area, $1/9+(2/9)/6=4/27$, and $w_0+6w_1=1$ (all to $10^{-14}$). The model is therefore a partition of the whole disc area among seven circles, with the uncovered part distributed to the outer six. It is not an area cubature: the second moment $\sum_kw_k|\vec c_k|^2/2$ is $0.197531\,R^2$, against the exact disc value $R^2/4$. Each channel then uses a fixed polar quadrature of a face-on disc (six Gauss–Legendre radial nodes, sixteen azimuth nodes; checked at $\sum w=2$, $\sum wx^2=\tfrac23$, $\sum wx^{10}=\tfrac2{11}$, V1).

## 35.3 Accuracy of the disc quadrature

The apparent solid angle of a face-on disc seen from the axis is $2\pi\big(1-d/\sqrt{d^2+R^2}\big)$. **Executed (T2).** The engine's `disc_solid_angle` against this exact value:

| $d/R$ | 100 | 10 | 3 | 1 | 0.5 | 0.2 | 0.1 |
|---|---|---|---|---|---|---|---|
| relative error | $7.7\times10^{-13}$ | $4.2\times10^{-15}$ | $1.9\times10^{-12}$ | $6.3\times10^{-8}$ | $1.2\times10^{-5}$ | $9.1\times10^{-4}$ | $1.5\times10^{-2}$ |

Table 35.1. Quadrature error of the disc solid angle on the axis, executed (T2).

Off the axis, at $d=2R$, against a reference of 400 radial and 800 azimuth nodes: $0.6228560680$ against $0.6228563085$ for a lateral offset $b=0.5R$ (relative $-3.9\times10^{-7}$), and $0.3943787694$ against $0.3943788052$ for $b=1.5R$ ($-9.1\times10^{-8}$). The quadrature is accurate to better than $10^{-11}$ beyond three body radii, to $6\times10^{-8}$ at one radius, and degrades inside contact range: at $d=0.1R$ the error is $1.5\%$, because the integrand varies on a scale $d$ much smaller than the node spacing. A force computation near contact needs a finer rule or the exact form.

## 35.4 Partial occultation

For a target disc occulted by a half-plane edge at $x=t$ (with $R=1$), the exact occluded fraction is the circular-segment fraction $F(t)=(\arccos t-t\sqrt{1-t^2})/\pi$ for $|t|<1$, $1$ for $t\le-1$ and $0$ for $t\ge1$. The seven-circle model estimates $\sum_kw_kF_k$ with $F_k$ the exact segment fraction of circle $k$; a Boolean model blocks a channel when its centre is behind the edge. **Executed (T3).** On 4001 positions of the edge in $[-1.2,1.2]$: both models are non-increasing in $t$, and the seven-circle model is exactly 0 for $t\ge1$ and 1 for $t\le-1$; its maximum absolute error in the occluded fraction is $0.0207$ and that of the Boolean model is $0.2033$, ten times larger. A model with Boolean visibility saturates between the channel centres and has a staircase of height $4/27$ or $1/9$ at each channel; the seven-circle model with per-circle fractions follows the exact curve to about 2%. The sensitivity of the occluded fraction to the edge position is $dF/dt=-2\sqrt{1-t^2}/\pi$, at most $0.64$ per body radius: a timing error that displaces the apparent edge by a fraction $\delta$ of the body radius changes the occluded fraction by up to $0.64\,\delta$. A residual that is small in seconds therefore does not establish a small force error near a moving occultation edge; the angular and positional sensitivity has to be examined.

Every contributing source-channel path is tested against intervening bodies. A Boolean visibility saturates, and pairwise deficit addition without overlap handling counts blocked routes twice: two identical blockers of occluded fraction $F$ lying on the same path remove $F$, not $2F$. Material emission and transmission need additional channel response and not a hidden opacity replacement. The Law-IV resistance response and the Law-V response of parallel and transverse components act after the geometric integration in the solver; for a speed $v=0.6c$ ($\gamma=1.25$) the factors are $\gamma^{-3}=0.512$ (parallel) and $\gamma^{-1}=0.8$ (transverse), by hand (Exercise 6). A fixed summation order gives deterministic replay; a different order can change floating-point cancellation without changing the mathematical equation.

## 35.5 Retardation

For a target event at time $t$ and a source history $x_s$, the retarded time solves $t_r=t-\lvert\vec x_{\rm target}(t)-\vec x_s(t_r)\rvert/c$. The fixed-point iteration needs a tolerance, a maximum count and an interpolation rule for the stored history. For a source moving uniformly at speed $\beta c$ along the line of centres the map is $\tau_{n+1}=t-D+\beta\tau_n$, a contraction of factor $\beta$, so the number of iterations to a tolerance $\mathrm{tol}$ is $\lceil\ln(\mathrm{tol}/e_0)/\ln\beta\rceil$.

**Executed (T4).** Target at $D=10$, observation time $t=5$, $c=1$; exact $\tau_r=(t-D)/(1-\beta)$:

| $\beta$ | 0.01 | 0.1 | 0.5 | 0.9 | 0.99 |
|---|---|---|---|---|---|
| error ratio per iteration | 0.010000 | 0.100000 | 0.500000 | 0.900000 | 0.990000 |
| iterations to $10^{-9}$ (predicted) | 4 (4) | 9 (9) | 33 (33) | 233 (233) | 2680 (2680) |

Table 35.2. Contraction of the retardation iteration, executed (T4). The observed ratios are measured on the first iteration.

The count grows as $1/(1-\beta)$ and the attainable accuracy degrades as $\epsilon|\tau|/(1-\beta)$: for $\beta=0.99$ and retarded times of order $5\times10^2$ the floor is near $6\times10^{-12}$, so a tolerance of $10^{-12}$ cannot be reached in double precision (this was a defect of the first registration of this test and is recorded in the pre-registration). A relativistic source therefore needs a tolerance chosen above that floor, a count limit and a convergence diagnostic. For a source that has passed the target the map changes branch (the absolute value changes sign) and the registered exact form changes with it: the first design of the test did not respect this and was repaired.

## 35.6 Native spherical implementation

The contract of the spherical implementation states positions, velocities, accelerations and impulses through loci and directions, while the previous contract keeps a coordinate representation. The channel phase origins differ between the two; shielding breaks the exact rotational symmetry that otherwise hides that phase choice. The solver source and its contracts were not re-executed here (residual R35.4). The determining test is to refine retardation, disc quadrature and step size separately, including partial occultation and moving blockers.

## 35.7 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| seven-circle geometry and weights | `occlusion.hpp` | the engine's declared numerical model; geometry DERIVED (exact) and verified |
| quadrature errors, Table 35.1 | Section 35.3 | COMPUTED |
| occulted-fraction errors | Section 35.4 | COMPUTED (exact half-plane reference) |
| retardation contraction | Section 35.5 | DERIVED (exact) and COMPUTED |
| $\gamma^{-3},\gamma^{-1}$ at $0.6c$ | Section 35.4 | DERIVED (hand arithmetic; not executed) |

**Residuals.**

* **R35.1 — the model.** The seven-circle weights are a boundary model, not a derived cubature; why the uncovered area goes to the outer six is a choice of the model.
* **R35.2 — near contact.** The disc quadrature loses accuracy inside about $0.5R$; the force near contact needs another representation.
* **R35.3 — edge sensitivity.** A model error of order $0.02$ in the occluded fraction at an edge is not a limit on the force error for a moving blocker; the full pairwise force near an occultation is not computed.
* **R35.4 — the implementations.** The spherical contract's solver was not executed here; the dependence of results on the channel phase origin under shielding is open.
* **R35.5 — history and interpolation.** The interpolation of the source history and its error were not tested; only the contraction of the iteration was.

## 35.8 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch35_retarded_many_body_occlusion
```

Criteria were registered in `Textbook/validation/ch35_PRE_REGISTRATION.md` before the instrument existed. A first build failed (an accessor); run 1 met every criterion for the geometry, the quadrature and the occultation and failed T4 for $\beta\ge0.5$ because the registered exact retarded time assumed the source had not passed the target (a registration error for $\beta>0.1$). Run 2, with a corrected configuration, failed T4 at $\beta=0.99$ because the registered tolerance $10^{-12}$ lies below the double-precision floor of that iteration. Run 3 (`ch35_run3_output.txt`) is the run of record and met every criterion.

## 35.9 Exercises and answers

**Exercise 1.** Show that the seven circles of radius $R/3$ fit in the disc of radius $R$ and touch.

*Answer.* The ring centres are at $2R/3$ from the centre, and their neighbours on the hexagon are at the ring radius $2R/3=2\rho$; the outer extent is $2R/3+R/3=R$.

**Exercise 2.** Derive $w_1=4/27$.

*Answer.* Each circle has area fraction $\rho^2/R^2=1/9$; seven cover $7/9$; the uncovered $2/9$ is shared among the six outer: $1/9+(2/9)/6=4/27$.

**Exercise 3.** Find $dF/dt$ for the circular-segment fraction at $t=0$.

*Answer.* $F=(\arccos t-t\sqrt{1-t^2})/\pi$ gives $F'=-2\sqrt{1-t^2}/\pi$, which is $-2/\pi=-0.637$ at $t=0$.

**Exercise 4.** How many iterations does $\beta=0.5$ need to reach an error of $10^{-9}$ from the starting error $e_0=5\beta/(1-\beta)=5$?

*Answer.* $\ln(10^{-9}/5)/\ln0.5=32.2$, so 33 iterations, as in Table 35.2.

**Exercise 5.** Why is the Boolean error ten times larger?

*Answer.* A Boolean channel jumps from 0 to its full weight when the edge crosses its centre, while the exact fraction of that circle changes continuously over its diameter.

**Exercise 6.** Compute the Law-V factors at $v=0.6c$.

*Answer.* $\gamma=1/\sqrt{1-0.36}=1.25$; $\gamma^{-3}=0.512$, $\gamma^{-1}=0.8$.

## 35.10 Scope

Established: the geometry and weights of the seven-circle model and their area origin; the quadrature errors as a function of distance and the loss of accuracy inside contact range; the behaviour of the model at an occultation edge against the exact segment, with the Boolean model ten times coarser; the contraction of the retardation iteration, its iteration counts and its precision limit for $\beta\to1$.

Not established: the model as an approximation of the opaque-sphere force (R35.1, R35.3), near-contact accuracy (R35.2), the spherical contract's phase dependence (R35.4) and history interpolation (R35.5).

*Where it leads.* Chapter 36 puts the dynamics on the Solar System: dated initial conditions, a comparison observable defined beforehand, and the dependence of results on input choices.
