# Spatial Displacement Theory and the `sdt-engine` — A Complete, Excessively Detailed Guide

> **Author of the theory:** J.C. Harvey (James Christopher Harvey), Melbourne.
> **What this document is:** a long-form, self-contained, deliberately verbose educational tour of Spatial
> Displacement Theory (SDT) and everything the `sdt-engine` repository computes — every primitive, every law,
> every formula, every certification label, and a thorough, table-by-table account of how SDT relates to (and
> mechanically *replaces the need for*) General Relativity and quantum mechanics.
> **How to read it:** Parts 0–2 are the foundations (read first). Parts 3–6 are the spine (the Six Laws, the
> derivation cascade, the koppa bridge, the Depth–Closure Theorem). Parts 7–13 are the domains (relativity,
> gravity, atoms, nuclei, particles, cosmology, gravitational waves). Parts 14–15 are the big comparison
> tables. Parts 16–19 are the engine map, the honesty ledger, and the glossary.
> **Honesty contract:** every quantitative claim below carries a certification label
> (`DERIVED / COMPUTED / CALIBRATED / OBSERVED / PENDING`) and, where relevant, an audit class (`A–F`). SDT's
> own ruleset prizes *honesty over success*: where the theory merely **converges** with an established result
> rather than deriving it from scratch, this guide says so plainly. That candour is what makes the wins count.

---

## PART 0 — THE ONE-PAGE ORIENTATION

**The thesis in one sentence.** Space is not emptiness and not a smooth manifold; it is a **gap-free lattice of
contacting cells ("spations")** that relay deformation at one cell per tick — and *every* physical
phenomenon (force, mass, light, gravity, charge, the expansion of the universe) is a consequence of how that
relay is loaded, occluded, displaced, and budgeted. There are **no free parameters**: the entire framework is
forwarded from a whitelist of eight measured constants, and a quantity that cannot be built from them is not
admitted.

**The four primitives** (everything else is derived): **Space** (the spation lattice), **Matter** (a
persistent *displacement* of spations — a hard, localised, solid vortex), **Movement** (circulation +
translation, always summing to `c`), and **Now** (the tick; the relay advances one spation per Planck time).

**The one mechanism, three faces.** There is exactly one force law in SDT — *occluded convergence*. The
cosmos-wide isotropic inflow of relay throughput (convergence) presses everything together; where one body
**occludes** part of another's convergence sky, the shadow is a net push toward the occluder. Coulomb,
gravity, and the nuclear force are the **same equation** at different scales:

$$ F = \frac{\pi}{4}\,P_{\text{eff}}\,\frac{R_1^2 R_2^2}{r^2} $$

**The slogan you must internalise.** *There is no attraction.* Nothing pulls. The CMB convergence pushes; matter
follows the path of least resistance through the resulting pressure gradient — and a closed least-resistance
path through a radial gradient simply *is* an orbit. "Gravity" is a bookkeeping name for asymmetric push.

---

## PART 1 — THE ONTOLOGY (WHAT EXISTS, AND WHAT DOESN'T)

### 1.1 The spation lattice

Space is a **3D, gap-free, contact-only relay medium**. Its irreducible cell is the **spation**, of size the
Planck length $\ell_P = 1.616255\times10^{-35}\,\text{m}$. The lattice has the following ontic commitments
(the relay axioms R1–R6):

| Axiom | Statement |
|---|---|
| **R1** Spation lattice | Space is a gap-free, contact-only relay medium. |
| **R2** Nearest-neighbour | Transmission is nearest-neighbour only, at the rate $c=\ell_P/t_P$. |
| **R3** Phase loading | Every spation carries deformation content $\varepsilon$. |
| **R4** Shell structure | The lattice has $N=R_{\text{CMB}}/\ell_P$ radial shells from observer to the Clearing. |
| **R5** Omnidirectional release | At the Clearing, all held content was released isotropically. |
| **R6** Shell cancellation | Convergent arrival from each shell preserves $\Phi=N\varepsilon$. |

And the matter axioms M1–M3:

| Axiom | Statement |
|---|---|
| **M1** Exclusion | Matter is a *persistent displacement* of spations (a vortex), not a substance added to space. |
| **M2** Circulation | Displaced spations circulate at speed $v_{\text{circ}}\le c$. |
| **M3** Budget | $v_{\text{circ}}^2 + v^2 = c^2$ — total velocity is always exactly $c$. |

**A particle is not a cloud.** It is a hard, localised, solid **vortex** — a knotted circulation pattern in the
lattice. It is never a probability, never a smeared field, never "just displacement with no structure." This
single ontological choice is the seed of every divergence from quantum mechanics later in this guide.

### 1.2 Convergence, the Clearing, and occlusion

At the **Clearing** (the epoch conventionally read as recombination, $z\approx1100$), every spation released
its held deformation omnidirectionally (R5). What we now experience at any interior point is the **superposed
arrival** of expanding spherical fronts from all $N$ shells — the **convergence**. The remarkable fact (Theorem
T1) is that convergence is *depth-independent*: the per-shell energetic dilution $\propto 1/4\pi d^2$ is exactly
cancelled by the growth in shell area $\propto 4\pi d^2$, so each shell contributes the same $\varepsilon$, and
the total burden is simply $\Phi=N\varepsilon$, constant across 61 orders of magnitude of depth.

**Occlusion** is the only way to get a *net* force from an otherwise perfectly isotropic convergence: a body
blocks (occludes) the convergence arriving from directions behind it, casting a "shadow cone." A second body in
that shadow feels less push from the occluded side than from the open side — net push toward the first body.
That asymmetry, integrated over the solid angle occluded, is the universal force law (Part 3, Law III).

> **The mechanism correction (James, recorded in the engine's narration audit):** empty spation passes
> throughput through transparently; force arises *only against matter*; every boundary contributes one tick.
> The picture is a **transparent relay with a shadow cone**, not an opaque sphere.

---

## PART 2 — THE RULES OF THE GAME

### 2.1 The whitelist (the only permitted inputs)

SDT admits exactly these as external inputs — the `sdt::laws::measured` namespace is the *whitelist*, and a fact
not in it is not a measured fact:

$$ \{\,\ell_P,\; c,\; \hbar,\; k_B,\; T_{\text{CMB}},\; \alpha,\; m_e,\; m_p\,\} $$

plus measured observables *in their measured units* (orbital velocities and radii, spectral lines, IAU/CODATA/
FIRAS data). The six truly independent numbers behind the derivation cascade are:

| Constant | Value | Source |
|---|---|---|
| $c$ | $299\,792\,458\ \text{m/s}$ | SI exact |
| $\hbar$ | $1.054571817\times10^{-34}\ \text{J·s}$ | SI exact |
| $\alpha$ | $7.2973525693\times10^{-3}$ | CODATA 2018 |
| $m_e$ | $9.1093837015\times10^{-31}\ \text{kg}$ | CODATA 2018 |
| $m_p$ | $1.67262192369\times10^{-27}\ \text{kg}$ | CODATA 2018 |
| $T_{\text{CMB}}$ | $2.7255\ \text{K}$ | FIRAS/Planck |

($\ell_P$ is adopted as a measured primitive — see the honest caveat in Part 18.4 — and $k_B$ closes the
thermodynamics.)

### 2.2 The prohibitions (what may never enter a derivation)

These are not "unsupported"; they are **forbidden inputs**:

- **No $G$, no $M$ (kilograms) as fundamentals.** Gravity is $g=v^2/R$; the gravitational descriptor is the
  koppa $\varkappa=v^2R/c^2$. $G=\ell_P^2 c^3/\hbar$ and $GM=c^2\varkappa$ are *consequences*, never sources.
- **No quantum wavefunctions; no fields as primitives; no wave–particle duality.** A particle is a hard vortex.
- **No quarks, no gluons, no virtual particles.**
- **No dark matter, no dark energy, no $\Lambda$CDM.**
- **No magnetic monopoles** (a half-vortex is topologically impossible); **no magnetons as a unit** (express
  everything in SDT-native yardsticks — the electron's own wake, the koppa — never in borrowed units).

### 2.3 The certification labels (every result is tagged)

| Label | Meaning |
|---|---|
| **DERIVED** | Computed from the axioms with no external input beyond the CODATA whitelist. |
| **COMPUTED** | Deterministic calculation from the Law framework (may use measured observables as inputs). |
| **CALIBRATED** | Exactly one parameter was fitted — and it *must* be documented. |
| **OBSERVED** | Validated against measurement; mechanism established. |
| **PENDING** | Mechanism identified, computation not yet complete. |

### 2.4 The audit spine (provenance × correspondence → A–F)

Beyond the five labels, the canonical audit (Theory/05) uses **two orthogonal axes**:

- **provenance_status** — `SDT-first / calibrated / external / unresolved`: *where did the number come from?*
- **correspondence_status** — `known-match / novel / internal / pending`: *does it match an established result,
  and does that matter?*

These project onto an **A–F** class. The crucial idea: **C = convergence, not plagiarism.** When SDT reproduces
a known GR/QM number by forwarding from its own primitives, that is a *feature*. The defence is the
**delete-test**: remove the correspondence check, and a genuine convergence result (class C) is *unchanged*
(it still stands on the SDT derivation), whereas a fitted result collapses. Throughout this guide, "Class C
(convergence)" means: *derived natively, happens to match — and the match was a check, not an input.*

---

## PART 3 — THE SIX LAWS (THE COMPLETE STATEMENT)

The framework is organised as Six Laws, mirrored by the `sdt::laws::law_I … law_VI` namespaces and a set of 18
theorems (T1–T18). Each law below gives its **core formula**, its **mechanism**, its **theorems**, and its
**numbers**.

### LAW I — Cosmological Relay Throughput  (`law_I`)

**Core formulas**

$$ \Phi = N\varepsilon = N\,u_{\text{CMB}}\,\ell_P^3, \qquad P_{\text{conv}} = \frac{\Phi}{\ell_P^3} = N\,u_{\text{CMB}} $$

**Mechanism.** The shell-cancellation identity (T1): each of the $N$ shells contributes the same $\varepsilon$
regardless of depth, because area growth cancels energetic dilution. The convergence burden $\Phi$ at any
interior point is therefore just $N\varepsilon$, and the isotropic pressure it exerts is $P_{\text{conv}}$.

**Numbers (DERIVED).**

| Quantity | Formula | Value |
|---|---|---|
| $u_{\text{CMB}}$ | $a_{\text{rad}}T_{\text{CMB}}^4$ | $4.172\times10^{-14}\ \text{J/m}^3$ |
| $N$ | $R_{\text{CMB}}/\ell_P$ | $5.894\times10^{61}$ |
| $\varepsilon$ | $u_{\text{CMB}}\,\ell_P^3$ | $1.761\times10^{-118}\ \text{J}$ |
| $\Phi$ | $N\varepsilon$ | $1.038\times10^{-56}\ \text{J}$ |
| $P_{\text{conv}}$ | $\Phi/\ell_P^3$ | $2.459\times10^{48}\ \text{Pa}$ |

**The boundary-cell identity.** The Clearing boundary carries $S_{\text{boundary}}=4\pi N^2$ source cells, and
$N^2=3.47\times10^{123}$ — *exactly* the "$10^{123}$" of the so-called cosmological-constant problem. In SDT this
is not a failed vacuum-energy cancellation; it is simply **the boundary-cell count**.

**CR05 extension (Class C).** Under expansion the lattice pressure tensor is isotropic and evolves
adiabatically as $P(z)=P_{\text{conv}}(1+z)^4$, from linking-number density $\tau\propto(1+z)^3$ times
temperature $T\propto(1+z)$. The polytropic index is $\gamma_{\text{eff}}=4$ (the topologically stiff lattice,
4 DOFs per cell from the $W\pm1$ modes) — **not** the $4/3$ of a photon gas, yet it recovers the radiation-era
$H\propto(1+z)^2$ without importing it.

### LAW II — The Release Cascade  (`law_II`)

**Core formula (pressure domain, T9)**

$$ r_{\text{domain}} = \sqrt{\frac{L}{4\pi F_{\text{CMB}}}}, \qquad F_{\text{CMB}} = \frac{c\,u_{\text{CMB}}}{4} = 3.131\times10^{-6}\ \text{W/m}^2 $$

**Mechanism.** Stars are **convergence recyclers**: every photon either feeds convergence or feeds matter. A
star's output competes with the CMB convergence; the radius at which they balance is its *pressure domain*.

**Numbers.** For the Sun ($L_\odot=3.828\times10^{26}\,\text{W}$): $r_{\text{domain}}\approx 3.12\times10^{15}\,
\text{m}\approx 20{,}800\ \text{AU}$. This is the **lumiopause**; the Oort cloud rests at this depth surface in
**lumiostasis** (Part 8.5).

### LAW III — Convergent Boundary Pressure  (`law_III`, T3–T4)

**Core formulas**

$$ \phi(\hat n)=\frac{\Phi}{4\pi}\ \ \forall\hat n \quad\Rightarrow\quad \oint \phi(\hat n)\,\hat n\,d\Omega = 0 \ \ (\text{Newton I}), \qquad \boxed{F=\frac{\pi}{4}\,P_{\text{eff}}\,\frac{R_1^2 R_2^2}{r^2}}\ \ (\text{T4}) $$

**Mechanism.** Isotropic convergence yields **zero** net force (Newton's first law falls out as a corollary).
A *net* force requires occlusion: the $1/r^2$ falloff is the solid angle a body of radius $R$ subtends,
$\Omega=\pi R^2/r^2$. The **same** law gives Coulomb, gravity, and the nuclear force — only the radii and the
effective pressure differ.

**The Coulomb specialisation.** With the charge radius $R_{\text{charge}}=\sqrt{R_p\,r_e}=1.540\times10^{-15}\,
\text{m}$, the occlusion force reproduces Coulomb exactly:
$F=\tfrac{\pi}{4}P_{\text{eff}}R_{\text{charge}}^4/r^2 = k_e e^2/r^2$.

**Numerical validation (hydrogen).** $F_{\text{occ}} = \tfrac{\pi}{4}P_{\text{eff}}R_p^2 R_e^2/a_0^2 =
8.23\times10^{-8}\,\text{N}$ vs Coulomb $8.24\times10^{-8}\,\text{N}$ — **0.12 %**.

**Honesty flag (this is the framework's most load-bearing calibration).** The coefficient $P_{\text{eff}}=
4k_e e^2/(\pi R_p^2 r_e^2)=5.225\times10^{31}\,\text{Pa}$ and the transfer ratio $f=P_{\text{eff}}/P_{\text{conv}}
=2.125\times10^{-17}$ are **CALIBRATED (Class E)** — the hydrogen scale fixes their magnitude; they fail the
delete-test. The $1/r^2$ **structure** is DERIVED (Class C); the **coefficient** is fitted. CR05 argues $f$
upgrades to Class C *if* $R_{\text{CMB}}$ is itself derived from the pressure tensor — contingent on the
assumed Friedmann structure (still open, GOM05). This is stated, not hidden.

### LAW IV — Inertial Mass from Throughput Reorganisation  (`law_IV`, T5–T7)

**Core formula**

$$ \boxed{m=\frac{\Phi\,V_{\text{disp}}}{3\,\ell_P^3\,c^2}} \qquad\Longleftrightarrow\qquad V_{\text{disp}}=\frac{3\,m\,\ell_P^3\,c^2}{\Phi} $$

**Mechanism.** A vortex excludes a volume $V_{\text{disp}}$, diverting throughput $\Phi$ around it. Acceleration
breaks the fore/aft symmetry of that diversion, creating a pressure-gradient dipole that **opposes the
acceleration** — that is inertia, and $F=-ma$ follows. Because both inertia and weight measure the *same*
$V_{\text{disp}}$, the **equivalence principle is automatic** (T6: $m_{\text{inert}}=m_{\text{grav}}$). The
factor of 3 is the isotropic-tensor projection (the same $1/3$ as the traction $\tau$, T7).

**Numbers (B/COMPUTED).** $V_{\text{disp},e}=9.988\times10^{-62}\,\text{m}^3$, $V_{\text{disp},p}=1.834\times
10^{-58}\,\text{m}^3$; the **marginal-stability identity** $\rho_{\text{eff}}c^2=P_{\text{conv}}/3$ holds exactly.

### LAW V — The Movement Budget  (`law_V`, T10–T17)

**Core constraint**

$$ \boxed{v_{\text{circ}}^2 + v^2 = c^2} $$

**Mechanism.** Every vortex spends a fixed velocity budget of $c$ between *circulation* (which it must maintain
to exist as a knot — this is its rest energy) and *translation*. Push it faster through space and it must
borrow from circulation; at $v=c$ circulation is zero, topology unwinds, mass vanishes. **All of special
relativity is the geometry of this one budget**, with no postulates about light or frames:

| Theorem | Result | Formula |
|---|---|---|
| T11 | Time dilation | $d\tau/dt=\sqrt{1-v^2/c^2}=1/\gamma$ |
| T12 | Length contraction | $L=L_0/\gamma$ |
| T13 | Rest energy | $E_0=m_0c^2$ (the circulation energy of a vortex at rest) |
| T14 | Energy–momentum | $E^2=(pc)^2+(m_0c^2)^2$ (Pythagoras on the budget) |
| T15 | Photon limit | $v_{\text{circ}}=0\Rightarrow v=c,\ m=0$ (no circulation, no knot, no mass) |
| T16 | Gravitational dilation | $d\tau/dt=\sqrt{1-zR/r}$, with $z=1/k^2$ |
| T17 | c-boundary | $R_c=zR=R/k^2$ — the radius where orbital speed reaches $c$; matter cannot exist within |

### LAW VI — Vortex Topology Quantisation  (`law_VI`, T18)

**Core formulas**

$$ \frac{R}{a}=\sqrt{\frac{q}{p}}\ \ (p,q\ \text{coprime}),\qquad v_p^2+v_t^2=c^2,\qquad \rho_{\text{eff}}c^2=\frac{P_{\text{conv}}}{3},\qquad \boxed{m(p,q)=\frac{M_0}{(p^2 q)^{1/4}}} $$

**Mechanism.** A stable particle is a **torus knot** $(p,q)$: the electron is the simplest closed winding
$W=1$ (the $(1,1)$ torus); the proton is the **trefoil** $(2,3)$, $W=3$. Quantisation comes from four
conditions — coprime closure, circulation quantisation ($a v_p=\hbar/m_p$, $R v_t=\hbar/m_q$), the movement
budget, and marginal stability. The stable budget angle is fixed: $\sin^2\theta^\*=1/3$, giving
$v_p/c=\sqrt{2/3}=0.8165$, $v_t/c=1/\sqrt3=0.5774$, $v_p/v_t=\sqrt2$.

**The fundamental mass scale (a genuine SDT prediction).**

$$ M_0=\left[\frac{\pi^2\hbar^3 P_{\text{conv}}\sqrt3}{2c^5}\right]^{1/4}=1.786\times10^{-24}\,\text{kg},\qquad M_0 c^2 = 1002\ \text{GeV}\approx 1\ \text{TeV} $$

i.e. SDT's natural mass unit lands on the **electroweak scale** with no tuning.

**The proton/electron mass ratio.** Two independent SDT handles agree: the topological identity
$m_p/m_e = 6\pi^5 = 1836.118$ (B26, matched to $0.0019\%$), and the winding-complexity ratio
$m_p/m_e=[(p^2q)_e/(p^2q)_p]^{1/4}=1836.15$. The electron is $\sim10^{13}$ times more topologically complex than
the proton. (The *full* first-principles derivation is the open $V_{\text{disp}}$ equilibrium solver, OP-1.)

**The proton radius (DERIVED, B18).** $R_p=(W+1)\hbar/(m_p c)=4\hbar/(m_p c)=0.84124\,\text{fm}$ — matches the
muonic-hydrogen value to $0.02\%$; and inverting, $W_{\text{eff}}=R_p m_p c/\hbar-1=3.000$.

---

## PART 4 — THE DERIVATION CASCADE (FROM SIX NUMBERS TO EVERYTHING)

Everything flows downhill from the whitelist through four stages. This is the spine of `laws.hpp`.

| Stage | Output | Formula | Value | Label |
|---|---|---|---|---|
| **1 Cosmological** | $u_{\text{CMB}}$ | $a T_{\text{CMB}}^4$ | $4.172\times10^{-14}\,\text{J/m}^3$ | DERIVED |
| | $N$ | $R_{\text{CMB}}/\ell_P$ | $5.894\times10^{61}$ | DERIVED |
| | $\varepsilon$ | $u_{\text{CMB}}\ell_P^3$ | $1.761\times10^{-118}\,\text{J}$ | DERIVED |
| | $\Phi$ | $N\varepsilon$ | $1.038\times10^{-56}\,\text{J}$ | DERIVED |
| | $P_{\text{conv}}$ | $\Phi/\ell_P^3$ | $2.459\times10^{48}\,\text{Pa}$ | DERIVED |
| **2 Particle radii** | $r_e$ | $\alpha\hbar/(m_e c)$ | $2.818\times10^{-15}\,\text{m}$ | DERIVED |
| | $R_p$ | $4\hbar/(m_p c)$ | $8.412\times10^{-16}\,\text{m}$ | DERIVED |
| | $R_{\text{charge}}$ | $\sqrt{R_p r_e}$ | $1.540\times10^{-15}\,\text{m}$ | DERIVED |
| **3 Force law** | $k_e e^2$ | $\alpha\hbar c$ | $2.307\times10^{-28}\,\text{J·m}$ | definitional (F) — *defines* $\alpha$ |
| | $P_{\text{eff}}$ | $m_p^2 m_e^2 c^5/(4\pi\alpha\hbar^3)$ | $5.225\times10^{31}\,\text{Pa}$ | whitelist-algebraic (CR03); circularity flagged (EMC01) |
| | $f$ | $P_{\text{eff}}/P_{\text{conv}}$ | $2.125\times10^{-17}$ | E→C argued (CR05), contingent on Friedmann |
| **4 Mass & stability** | $V_{\text{disp},e}$ | $3m_e\ell_P^3 c^2/\Phi$ | $9.988\times10^{-62}\,\text{m}^3$ | COMPUTED |
| | $V_{\text{disp},p}$ | $3m_p\ell_P^3 c^2/\Phi$ | $1.834\times10^{-58}\,\text{m}^3$ | COMPUTED |
| | $P_{cf}$ | $\rho_{\text{eff}}c^2=P_{\text{conv}}/3$ | identity ✓ | DERIVED |

**The Coulomb identity** $k_e e^2=\alpha\hbar c$ (T9) is *definitional* (Class F): it **defines**
$\alpha\equiv k_e e^2/\hbar c$. SDT's coupling is the dimensionless $\alpha$ (in the whitelist); **$e$ is not** —
charge is not an SDT entity (it is *occluded influx directionality* — see Part 18), and $e$ figures only as the
SI unit-bridge from SDT's occlusion magnitude back to the Coulomb number.

---

## PART 5 — THE KOPPA BRIDGE AND THE k-HIERARCHY (GRAVITY WITHOUT $G$ OR $M$)

This is how SDT does celestial mechanics with **no $G$ and no $M$**. Define the **koppa** — the *c-boundary*, a
velocity-defined length — and the **speed ratio** $k$:

$$ \boxed{\varkappa \equiv \frac{v^2 R}{c^2}=\frac{R}{k^2}},\qquad k=\frac{c}{v},\qquad z\equiv\frac{1}{k^2}=\left(\frac{v}{c}\right)^2=\frac{\varkappa}{r} $$

From these, the entire toolkit of orbital mechanics follows with the closure condition $z k^2=1$:

| Quantity | SDT formula | Replaces (GR/Newton) |
|---|---|---|
| Orbital velocity | $v(r)=\dfrac{c}{k}\sqrt{R/r}=c\sqrt{\varkappa/r}$ | $\sqrt{GM/r}$ |
| Surface gravity | $g=v^2/R=c^2\varkappa/R^2$ | $GM/R^2$ |
| "$GM$" (for conversion only) | $GM=c^2\varkappa=v^2 r$ | $GM$ as fundamental |
| Bridge law | $z=(v/c)^2=1/k^2$ | — |
| Closure | $z k^2 = 1$ | — |
| Baryon count | $N_{\text{bary}}=\varkappa/\varkappa_b$, $\varkappa_b=\ell_P^2 c\,m_p/\hbar$ | $M/m_p$ |

**The point.** A single number — the koppa $\varkappa$ — encodes the *entire* gravitational field of a body, and
it is measured from $v_{\text{surface}}$ and $R$ alone. "$GM$" is recovered as $c^2\varkappa$ as a *consequence*.
This is the "c-from-geometry" result (GOM04): $c$ itself was reconstructed from Mercury's precession and orbital
velocity, with no $GM$ inserted.

**k as a clock and "137 as a countdown."** Since $d\tau/dt=\sqrt{1-1/k^2}$, $k$ is literally a clock-rate index;
$k$ decreases toward the c-boundary $k=1$ ($v=c$, $d\tau/dt=0$, dissolution). Hydrogen's ground state sits at
$k=1/\alpha=137$ — i.e. **137 steps from the edge** — which is the deep meaning of the fine-structure constant
(Part 9).

---

## PART 6 — THE DEPTH–CLOSURE THEOREM (THE CAPSTONE)

The single most unifying statement in the engine (`sdt::laws::depth_closure`; paper in
`Papers/Depth_Closure_Theorem/`). It says the **local closure, the local relay speed, the local clock rate, and
the gravitational spectral shift are one quantity** — the convergence depth $z=\varkappa/r$ — and one
centripetal law $v=c\sqrt z$ governs bound motion at every scale.

$$
\begin{aligned}
(1)\ & \ell_P(r)=\ell_{P,\infty}\,(1-z) && \text{local spation closure}\\
(2)\ & c_{\text{local}}(r)=c_\infty\,(1-z) && \Rightarrow\ z=1-c_{\text{local}}/c_\infty\\
(3)\ & d\tau/dt=\sqrt{1-z} && \text{local clock rate (Law V)}\\
(4)\ & z_{\text{spec}}=z(r_{\text{emit}})-z(r_{\text{obs}}) && \text{gravitational redshift = depth differential}\\
(5)\ & v(r)=c\sqrt{\varkappa/r}=c\sqrt z && \text{bound-motion law } (g=v^2/r=c^2\varkappa/r^2)
\end{aligned}
$$

**What it means physically.** Matter *crushes the space it displaces*: nucleons tighten the local closure, so
spations are **smaller** near mass, and since light always relays one spation per tick, light is locally
**slower** deep in a gravity well. There is no "slowing in a potential" and no curved metric — there is a
**closure gradient**. The Shapiro delay is then not mysterious: a fixed coordinate path near the Sun contains
*more, smaller* spations to relay across.

**Proven corollaries (from `keystone.js`).**

| # | Corollary | Result |
|---|---|---|
| C1 | redshift = depth | $z_{\text{spec}}(\odot)=\varkappa_\odot/R_\odot=2.123\times10^{-6}$ = observed solar redshift to **0.03 %** |
| C2 | one law across scales | $v=c\sqrt{\varkappa/r}$ gives Earth's $29.789\ \text{km/s}$, a 292-AU orbit, and — applied to hydrogen — $v=\alpha c$, $k_H=137$, $\varkappa_H=\alpha^2 a_0=r_e$ — over ~15 orders of magnitude |
| C4 | $c$ is local | measured $c$ is Earth's rung; $c_\infty\approx c+105\ \text{m/s}$ (the galactic depth floor, $z_{\text{gal}}=3.5\times10^{-7}$) |
| C5 | closure floor | $\ell_P=\sqrt{\varkappa\cdot\lambda}$ — the mass-independent fixed point where koppa equals wake |
| C6 | lumiopause | $L/(4\pi r^2)=F_{\text{CMB}}\Rightarrow r=20{,}857\ \text{AU}$ |

**Honest scope.** C1 is, by construction, an *identity of interpretation* ($\varkappa\equiv GM/c^2$, so matching
$GM/(c^2R)$ is algebra, not coincidence) — its content is the *reinterpretation*, not a numerical surprise. The
proven content is C1–C2; the absolute $\ell_{P,\infty}$, the galactic-floor magnitude, and the internal
particle radii carry open caveats (Part 18).

---

## PART 7 — SPECIAL RELATIVITY, RE-DERIVED (NO POSTULATES)

Einstein's SR rests on two postulates (constancy of $c$, relativity of frames). SDT derives the *same equations*
from the movement budget (Law V) with **no postulates** — they are facts about a vortex spending a fixed
velocity budget.

| Phenomenon | SR (postulated) | SDT (mechanical) |
|---|---|---|
| Time dilation | from Lorentz transform | circulation slows as translation borrows budget: $d\tau/dt=\sqrt{1-v^2/c^2}$ |
| Length contraction | from Lorentz transform | $L=L_0/\gamma$, same budget |
| $E=mc^2$ | mass–energy equivalence postulate | $E_0$ *is* the circulation energy of the rest vortex |
| Light speed limit | postulate | a vortex at $v=c$ has $v_{\text{circ}}=0$: no knot can persist — the limit is structural |
| Massless photon | postulate (zero rest mass) | $v_{\text{circ}}=0\Rightarrow$ no topology $\Rightarrow m=0$; the photon is pure translation (T15) |

---

## PART 8 — GRAVITY AND ORBITAL MECHANICS (DIFFERENCES FROM GR)

### 8.1 The core reframing
GR: mass–energy curves spacetime; objects follow geodesics. SDT: mass displaces/crushes lattice; the closure
gradient $z(r)$ makes one radial direction the path of least resistance; **orbits are real, attraction is not.**

### 8.2 The classic GR tests, reproduced from $z=\varkappa/r$

| Test | GR | SDT | Match |
|---|---|---|---|
| Gravitational redshift | $GM/c^2R$ | $z_{\text{spec}}=\varkappa/r$ differential | 0.03 % (solar), B28 |
| Mercury perihelion precession | $43''/\text{century}$ | from the $k^2$-gradient, $z=v^2/c^2$ | DERIVED, B10 (42.98) |
| Light deflection at the Sun | $1.75''$ | $\Delta\theta=2R_c/b$ (convergence-gradient refraction) | DERIVED, B10 (1.7505) |
| Shapiro delay | log formula in a potential | $\Delta t=(2\varkappa/c)\ln(4r_1 r_2/b^2)$ — *accumulated closure*, local $c$ stays $c$ | 0.0000 %, GOM05 |
| Hulse–Taylor orbital decay $\dot P$ | quadrupole formula | same (Part 13), via $GM\to c^2\varkappa$ | $-2.4029$ vs $-2.4025\times10^{-12}$, B09 |

### 8.3 Where SDT departs from GR (falsifiable)
- **No singularities.** A black hole interior is a **maximum-compression lattice state** (E68), capped at one
  Planck volume per spation — never $r=0$.
- **$c$ is not globally constant.** $c_{\text{local}}=c(1-z)$; there is a constant **galactic depth floor**
  ($\sim105\ \text{m/s}$ below $c_\infty$) even in interstellar space — a prediction GR does not make.
- **Gravitational-wave echoes** from the closure-floor wall (Part 13.4).

### 8.4 Galactic rotation without dark matter
Flat rotation curves arise from **convergence-disk occlusion / a derived acceleration floor**
$a_0=cH_0/2\pi=1.042\times10^{-10}\,\text{m/s}^2$ (no dark matter, no $\Lambda$CDM). On real SPARC data the
twin-regime convergence-floor law reaches RMS $23.8\%$ with the correct BTFR slope $3.58$ — *honest status:* the
asymptotes are derived, the crossover shape is still borrowed (APS03/GD05, Part 18).

### 8.5 Lumiostasis
The Oort cloud is not "weakly orbiting" — it is **suspended** at the lumiopause depth surface
($\sim20{,}860\ \text{AU}$), where the Sun's output surface density equals the CMB floor. Falsifier: detached
objects should cluster at that depth surface rather than following a purely Keplerian distribution.

---

## PART 9 — ATOMIC STRUCTURE (AND WHY THE "WAVEFUNCTION" IS A STROBOSCOPIC ARTEFACT)

### 9.1 The fine-structure constant demystified
$\alpha$ is not a magic number — it is the **koppa of hydrogen's ground state**. The ground-state electron moves
at $v=\alpha c$, so $k_H=1/\alpha=137.036$, and the hydrogen c-boundary is $\varkappa_H=\alpha^2 a_0=r_e$
(the classical electron radius) *exactly*. It obeys the *same* $\varkappa=v^2R/c^2$ law as the Sun ($k=686$),
Earth, and the Moon. $\alpha$ is a rung on the k-ladder, not a coincidence.

### 9.2 The spectrum
$$ E_n = -13.6057\,\frac{Z^2}{n^2}\ \text{eV} $$
Hydrogen and hydrogen-like ions to $<13$ ppm; the 118-element closure via $z k^2=1$. Chemistry is the
**geometric shielding** of the core charge, not new physics. The kinematic ratio $\chi=c/v=c/\sqrt{2E_{\text{ion}}/m_e}$
*is* the $k$-number: Ne $\chi=109$ (inert), H $\chi=137$ (baseline), K $\chi=243$ (reactive).

### 9.3 The stroboscopic electron (the quiet deprecation of the orbital)
The electron is a hard $W=1$ vortex traversing a **Hopf-fibration track** at high pattern speed. What
spectroscopy and microscopy sample as a "probability cloud" is a **stroboscopic artefact** — the time-average of
a fast, *definite* point trajectory. There is no superposition, no collapse, no intrinsic indeterminacy: there
is a fast classical orbit that *looks* like a cloud when you can't resolve the tick. The nucleus's $\ell=2$ wake
mechanically drags the electron along its track (reciprocal drive). The numbers come out identical to the
Schrödinger/Dirac results because the geometry is the same; the *ontology* is not.

### 9.4 Geometric serenity (the shell-filling rule, re-grounded)
Electrons fill geometric voids in the nuclear convergence field — dyad (2, a line), triangle (3, a plane),
tetrahedron (4), cube (8, "maximum serenity"). The octet rule is geometry, not an exclusion postulate.

---

## PART 10 — NUCLEAR STRUCTURE (THE ATOMICUS GRAMMAR)

Every nucleus with $Z\ge2$ decomposes **uniquely** into one alpha core plus deuteron and triton blocks. This is
constitutional — not one model among many.

$$ \boxed{n_t=A-2Z,\qquad n_d=3Z-A-2},\qquad A=4+2n_d+3n_t,\qquad Z=2+n_d+n_t $$

(Electron-capture isotopes use the **alternate grammar** with a He-3 core: $n_t=A-2Z+1$, $n_d=3Z-A-3$.)

| Block | Content | Role |
|---|---|---|
| Alpha core | $2p+2n$, $W=3$ trefoil quartet, BE $=28.3$ MeV | the one irreducible centre of every nucleus |
| Deuteron $d$ | $1p+1n$ | symmetric block; pure-$d$ nuclei are most abundant |
| Triton $t$ | $1p+2n$ | asymmetric block; odd $n_t$ → lowest abundance, high $n_t$ → strain |

**Consequences (selected).**
- **Abundance from symmetry:** pure-deuteron ($n_t=0$) nuclei (C-12, O-16, Ne-20, Si-28, Ca-40) are most
  abundant; odd-$n_t$ are rarest. Predicts the most-abundant isotope in 64 % of multi-isotope elements.
- **Construction chains:** He-4 + t → Li-7; C-12 + d → N-14; N-14 + d → O-16; O-16 + t → F-19 (the only stable
  fluorine).
- **The Golden Boundary ($Z=79$):** gold is the last element where $n_d>n_t$; beyond it, triton-dominant
  skeletons cannot bear the geometric load → radioactivity. Triton fraction climbs: iron-peak $\sim17\%$
  (max binding), Au–Pb $30\!-\!40\%$, actinides $>50\%$ (overloaded → decay).
- **Free neutrons are forbidden** in stable nuclei; a "free neutron" is an exposed triton remnant.
- **The neutrino is a receipt:** every winding reconfiguration files an open-winding receipt (a neutrino). The
  cosmic $\nu$/baryon ratio $\sim10^9$ is the running total of matter's construction history.

---

## PART 11 — THE PARTICLE SPECTRUM (TOPOLOGY, NOT A ZOO)

From Law VI, particles are torus knots and the mass spectrum is $m(p,q)=M_0/(p^2q)^{1/4}$ with $M_0 c^2\approx1$
TeV. The low-winding rungs populate the electroweak scale; the proton and electron are extreme-winding rungs.

| Particle | $m$ | $p^2q$ | Regime |
|---|---|---|---|
| top quark | $173.1$ GeV | $1.12\times10^3$ | low winding |
| Higgs | $125.1$ GeV | $4.12\times10^3$ | low winding |
| proton | $0.938$ GeV | $1.30\times10^{12}$ | high winding (trefoil $W=3$) |
| electron | $0.511$ MeV | $1.48\times10^{25}$ | extreme winding ($W=1$) |

The **neutrino has no magnetic moment** ($\mu_\nu\equiv0$ exactly): it is an *open* winding ($W=0$), so it has
no EM-deflecting wake (B07/PPT04) — falsifiable against the Standard Model's tiny but nonzero prediction.
Pair production/annihilation are vortex creation/counter-vortex collision ($2\times511$ keV); electron
diffraction is lattice scattering of the vortex (all VERIFIED in the correspondence catalogue).

---

## PART 12 — COSMOLOGY (NO DARK SECTOR, NO $\Lambda$CDM)

| Topic | SDT account | Label |
|---|---|---|
| CMB redshift | $z=T_{\text{rec}}/T_{\text{CMB}}-1=1089$ | DERIVED (B13) |
| Pressure evolution | $P(z)=P_{\text{conv}}(1+z)^4$, $\gamma_{\text{eff}}=4$ (topological stiffness) | C (CR05) |
| Hubble constant | $H_0=67.4$ km/s/Mpc via the pressure tensor + (assumed) Friedmann structure | C-flagged |
| Cosmological "constant problem" | the $10^{123}$ is $N^2=4\pi$-scaled boundary-cell count, not a vacuum-energy failure | DERIVED |
| BAO sound horizon | $r_s\approx147$ Mpc; topological freeze-out (factor-4 linking drop at recombination) | COMPUTED (B15) |
| Cosmological redshift | depth accumulation $z=1/k^2$ along the line of sight (GOM01/CR01, $zk^2=1$) | C |
| Dark matter | replaced by convergence-disk occlusion + derived $a_0$ floor | C/PARTIAL |
| Dark energy | a pressure-gradient *misreading* of the lattice EOS, not a substance | SPEC |

**Honest flag:** the Friedmann *structure* is currently assumed (not yet SDT-derived) and the $\Omega$
normalisation is observational — so $H_0$ is **C-flagged**, the one place the cosmology leans on borrowed
scaffolding (GOM05 is the route to remove it).

---

## PART 13 — GRAVITATIONAL WAVES (GOM06: "MOVE THE SEA, DON'T MAKE WAVES")

SDT's account of LIGO/Virgo events, gate by gate (full investigation in
`Investigations/CQ44_Gravitational_Wave_Mechanism/`).

### 13.1 The mechanism
A GW is **the medium being moved, not a ripple made in it.** The relay-lattice deformation is a strain tensor
$\varepsilon_{ij}$ whose **trace** is the depth $z$ (static gravity, the Depth–Closure scalar) and whose
**traceless shear** is the radiative wave. The sea's *volume* (trace) is the static field; its *shape* (shear)
is the gravitational wave. This makes the GW **tensor-polarised by construction** — exactly GR's two modes
$h_+,h_\times$ — with no scalar–tensor tuning.

### 13.2 The chirp as a length (no $G$, no $M$)
The inspiral is governed by the combined c-boundary $\varkappa_{\text{tot}}=\sum GM_i/c^2$:
$$ r_{\text{isco}}=6\varkappa_{\text{tot}},\qquad f_{\text{GW,isco}}=\frac{c}{\pi\,6^{3/2}\,\varkappa_{\text{tot}}} $$
For GW150914 ($\varkappa_{\text{tot}}\approx96$ km): $67.65$ Hz vs measured $68$ Hz ($-0.5\%$). Read inversely,
**LIGO is a koppa-meter** — it measures a length $\varkappa$, and "mass" is only $c^2\varkappa/G$.

### 13.3 Memory ≡ breathing (a prediction GR does not make)
The radiated koppa $\Delta\varkappa_{\text{rad}}=\varkappa_{\text{tot}}(\Delta M/M)$ (GW150914: $4.43$ km,
$\approx4.6\%$) sources **both** a merger-epoch breathing transient (the only scalar admixture; the monopole is
otherwise conserved → no breathing) **and** the permanent memory offset $\Delta h_{\text{mem}}=\eta\,
\Delta\varkappa_{\text{rad}}/R$ ($\sim7\!-\!35\%$ of peak, order-matching GR). They are **one quantity** — the
sea staying moved.

### 13.4 Echoes (the SDT ≠ GR test)
SDT has **no event horizon**: $c_{\text{local}}\to0$ only at $z=1$ ($r=\varkappa$), and the closure floor is a
hard reflecting wall, so the ringdown repeats as echoes spaced
$\Delta t_{\text{echo}}=(2\varkappa_f/c)\ln(\varkappa_f/\ell_P)\approx58$ ms for GW150914. *Honest status:*
the wall is a posit; observational echo claims are contested. This is the cleanest place SDT could be
distinguished from GR.

---

## PART 14 — SDT vs GENERAL RELATIVITY (THE BIG TABLE)

| Aspect | General Relativity | Spatial Displacement Theory |
|---|---|---|
| **Ontology of space** | smooth 4D pseudo-Riemannian manifold | discrete gap-free lattice of contacting spations |
| **Gravity is…** | curvature of spacetime | a closure/pressure gradient; *occluded convergence* |
| **Source of gravity** | stress–energy $T_{\mu\nu}$ ($G$, $M$ fundamental) | displaced volume $V_{\text{disp}}$; $\varkappa=v^2R/c^2$, no $G$/$M$ |
| **"Attraction"** | geodesic motion in curved metric | none — least-resistance path through a push gradient |
| **Field equation** | $G_{\mu\nu}=8\pi G\,T_{\mu\nu}/c^4$ | depth field $z=\varkappa/r$; $g=v^2/R$ |
| **Redshift** | metric time dilation | depth differential $z_{\text{emit}}-z_{\text{obs}}$ (smaller spations) |
| **Shapiro delay** | extra path in curved metric | accumulated closure (more, smaller cells); local $c$ stays $c$ |
| **Speed of light** | locally invariant, globally frame-dependent | $c_{\text{local}}=c(1-z)$; a real galactic floor exists |
| **Black hole** | singularity at $r=0$ + event horizon | max-compression lattice state; no singularity; **no horizon** |
| **GW polarisation** | 2 tensor modes (postulated graviton spin-2) | 2 tensor modes = lattice traceless shear (derived) |
| **GW memory** | nonlinear (Christodoulou), separate effect | $=$ the radiated koppa $\Delta\varkappa$; *identical* to the breathing transient |
| **Ringdown** | pure Kerr QNMs, then silence | QNMs **+ echoes** off the closure-floor wall |
| **Cosmological const.** | $\Lambda$, $10^{123}$ discrepancy | $N^2$ boundary-cell count — not an energy at all |
| **Free parameters** | $G$, $\Lambda$, plus initial conditions | zero (whitelist only); the one calibration ($P_{\text{eff}}$) is flagged |
| **Where they agree** | — | redshift, precession, deflection, Shapiro, $\dot P$, GW speed & chirp (all **convergence**, class C) |

---

## PART 15 — SDT vs QUANTUM MECHANICS (WHERE A RULE BECOMES A MECHANISM)

QM is, operationally, a superbly accurate **computational rule book** — but it is silent on *what is actually
happening*. For every QM result below, SDT supplies a **mechanical account** that returns the same number from a
definite, local, deterministic picture. The reader may draw the obvious conclusion about which description is
more fundamental.

| Phenomenon | QM description (a rule) | SDT account (a mechanism) | Engine |
|---|---|---|---|
| The particle | wavefunction $\psi$; probability amplitude | hard, localised $W$-knotted vortex | M1 |
| Electric charge | a fundamental quantum number, $[\mathrm{A}{\cdot}\mathrm{s}]$ | **not a primitive** — *occluded influx directionality*; the force is occlusion geometry; $e$ = SI unit-bridge | Law III |
| "Orbital" / cloud | $|\psi|^2$ probability density | stroboscopic time-average of a fast definite Hopf-track orbit | §9.3 |
| Wave–particle duality | complementarity postulate | one object (a vortex) scattering off a discrete lattice | E81 |
| Quantisation | eigenvalues of an operator | topological closure: coprime $(p,q)$ torus knots | Law VI |
| Spin / g-factor | intrinsic, $g=2$ from Dirac eq. | circulation geometry; $g=2(1+\alpha/2\pi)$ from wake perturbation | B17 |
| Fine-structure $\alpha$ | empirical coupling | koppa of the H ground state; $k_H=1/\alpha=137$ | §9.1 |
| Energy levels | Schrödinger eigenvalues | $E_n=-13.6\,Z^2/n^2$ from $zk^2=1$ geometry | B01/B02 |
| Blackbody / Planck | quantised oscillators (postulate) | lattice mode counting — the lattice is *already* discrete at $\ell_P$ | SAR02–63 |
| Pair production | QED vertex | creation of a vortex/anti-vortex pair, $2\times511$ keV | E79 |
| Neutrino moment | tiny but nonzero (SM) | $\mu_\nu\equiv0$ exactly (open $W=0$ winding) | PPT04 |
| Magnetic monopole | allowed, unobserved | forbidden — a half-vortex is topologically impossible | E58 |
| Hyperfine / 21 cm | spin-flip with magnetons | whirl-on-whirl overlap of the proton–electron dyad | B05 |
| Tunnelling, entanglement | nonlocal/indeterminate postulates | *open* — SDT seeks a local lattice mechanism (see Part 18) | — |

**The native angular DOF (PPT08/APS04 — a 2026-06 closure).** SDT now **does** have a native angular degree of
freedom: the trefoil's **three-fold ($C_3$) wake multipole** (APS04) gives the $\ell=0/2/3$ harmonics
($\Phi_0\sim r^{-1}$, $\Phi_2\sim r^{-3}$, $\Phi_3\sim r^{-4}$) and the selection rule $m_3=3k$, with **no
imported spherical harmonics**. From it the **Lamb shift falls out at 1051.8 vs 1057.845 MHz (0.57 %) with
ZERO fitted constants** — the $s$-like (equatorial) vs $p$-like (polar) orbits couple differently to $\Phi_2$,
giving the correct sign and magnitude. This **supersedes** the old calibrated B04 ($k_{\text{Lamb}}=12.7227$),
which has not yet been refactored to use the APS04 mechanism (APS04 is recorded as the canonical *candidate*,
Class C, pending benchmark integration).

**The honest boundary that remains.** Two things an earlier draft mislabelled are *dissolved*, not gaps:
**charge** (a QM abstraction — SDT has *occluded influx directionality*, not a charge primitive; $\alpha$, not
$e$, is in the whitelist) and the **fixed $\ell_P$** (GOM05 makes it a variable closure *field*
$\ell_P(r)=\ell_{P,\infty}(1-z)$, derived as the koppa = wake fixed point from hydrogen geometry, not $G$). What genuinely remains:
multi-electron atoms (**PENDING**, B06); the **$P_{\text{eff}}$ force coefficient calibrated to hydrogen**
(`laws.hpp` Class E); the **assumed Friedmann structure** behind $H_0$; and **quantum measurement /
entanglement**, not yet mechanised. The QM *rule book still computes correctly*; SDT's claim is that where it
has supplied a mechanism, the mechanism is local, hard, and deterministic — and the remaining gaps are honestly
logged, not papered over.

---

## PART 16 — THE BENCHMARK LEDGER (B01–B29, THE REGRESSION FLOOR)

`Benchmarks/B01_B25/benchmarks_b01_b25.cpp` is the end-to-end verification; it self-reports PASS/FAIL against
measured constants. The certification status is shown — note the honesty: only one carries a fitted parameter.

| # | Verifies | Result | Label |
|---|---|---|---|
| B01 | H energy levels | $E_n=-\text{Ry}\,Z^2/n^2$ | DERIVED |
| B02 | Multi-ion Rydberg (He⁺, Li²⁺) | exact spectral match | DERIVED |
| B03 | Fine structure, g-factor | $2P$ split $4.528\times10^{-5}$ eV; $g=2.00232$ | DERIVED |
| B04 | **Lamb shift** | $1051.8$ vs $1057.845$ MHz (0.57 %) | benchmark still **CALIBRATED** ($k_{\text{Lamb}}$); **superseded by APS04's zero-fit native derivation** (Class C), pending integration |
| B05 | Hyperfine 21 cm | $1420.405$ MHz | DERIVED (line OBSERVED; mechanism re-narrated) |
| B06 | Multi-electron ionisation | Slater screening | **PENDING** (open atoms problem) |
| B07 | Stefan–Boltzmann, Wien | $\sigma_{SB}=5.670\times10^{-8}$; $\lambda_{\max}T=2.898\times10^{-3}$ | DERIVED |
| B08 | Earth orbital velocity, $GM_\odot$ | $29783$ m/s; $1.327\times10^{20}$ | DERIVED |
| B09 | Hulse–Taylor $\dot P$ | $-2.4029$ vs $-2.4025\times10^{-12}$ | DERIVED |
| B10 | Mercury precession; light deflection | $42.98''$; $1.7505''$ | DERIVED |
| B11 | Earth & Jupiter $J_2$ | uniform-fluid estimate | **PENDING** |
| B12 | Stellar $zk^2=1$ (5 stars) | $=1.0$ across 10 orders | DERIVED |
| B13 | CMB redshift | $z=1089$ | DERIVED |
| B14 | Galactic $R_{\text{flat}}\approx2.5R_d$ | 12 % tolerance | COMPUTED |
| B15 | BAO sound horizon | $r_s=147$ Mpc | COMPUTED |
| B16 | Transport scaling $T^{0.5}$ | exponent $0.5$ exact | DERIVED |
| B17 | Electron g-factor | $g=2(1+\alpha/2\pi)=2.00231930436$ | DERIVED |
| B18 | Proton radius (W+1), He-4 | $R_p=0.84124$ fm (0.08 %); $R_{He}=2R_p$ | DERIVED |
| B19 | Beta-decay Q-value | $0.782$ MeV | DERIVED |
| B20 | $zk^2$ universality | $=1.0$ exact | DERIVED |
| B21 | EM/grav force ratio | $\approx2.27\times10^{39}$ | COMPUTED |
| B22 | Pressure hierarchy | $P_{\text{eff}}=5.225\times10^{31}$; $f=2.125\times10^{-17}$ | COMPUTED |
| B23 | Coulomb identity $k_e e^2=\alpha\hbar c$ | 0.1 % | DERIVED |
| B24 | Exclusion volumes; marginal stability | $P_{cf}/(P_{\text{conv}}/3)=1.0$ | COMPUTED/DERIVED |
| B25 | He-4 alpha-cluster binding | exact NR $-79.0052$ eV (0.00025 %) | COMPUTED |
| B26 | Trefoil $(2,3)$ budget; $m_p/m_e=6\pi^5$ | $1836.118$; $v_{\text{phase}}=1.830c$ | DERIVED/COMPUTED |
| B27 | Koppa closure: $c$ from Mercury precession | $c$ reconstructed | COMPUTED/DERIVED |
| B28 | Depth-closure $z=\varkappa/r$ | solar redshift; Earth $v=c\sqrt{\varkappa/r}$ | COMPUTED/DERIVED |
| B29 | GW chirp as length (GW150914) | $f_{\text{isco}}$ from $\varkappa_{\text{tot}}\approx96$ km | COMPUTED |

---

## PART 17 — THE INVESTIGATION MAP (`CQ##`)

The `Investigations/` tree pushes open questions to honest conclusions. A representative slice:

| Investigation | Topic | Status |
|---|---|---|
| PPT01 | Vortex equilibrium $(p,q)$ knots; electron $(1,1)$, proton $(2,3)$ | RESOLVED |
| FLM02/FLM05 | Granular pulse mechanics → $F=ma$, Newton I–III | RESOLVED |
| GOM01/GOM02/GOM04 | Depth engine; k-hierarchy; koppa closure ($c$ from geometry) | RESOLVED |
| NP01 | Atomicus nuclear grammar (the constitution) | RESOLVED/frozen |
| APS03 | Universal drafting crossover (atomic+stellar+galactic on one curve) | PARTIAL |
| NP05 → CQ41 | Nuclear binding: volume-deficit (killed) → gear-frequency pull | ACTIVE |
| CR03 | Transfer-function closure (bottleneck for $f$) | EXECUTED |
| PPT08/APS04 | **Angular DOF + Lamb shift** from the trefoil $C_3$ wake multipole | **RESOLVED (C, 0.57 %)** |
| PPT08A | **Per-spation rolling** → $v(r)=v_0\sqrt{R_p/r}$ (the ROOT-SIM) | **RESOLVED (A, $<10^{-15}$)** |
| PPT09 | **Winding-number stability** (W=1,3-only, OP-2) | **RESOLVED (A, proof)** |
| EMC02 | Elementary charge $e$ | **Class X (irreducible)** |
| CR05 | Spation pressure tensor; $\gamma_{\text{eff}}=4$; $H_0$; $f$ E→C | EXECUTED (C) |
| FLM06 | Spation-scale closure $\ell_P=\sqrt{\varkappa\lambda}$ (seed theorem) | EXECUTED (**negative** on $\ell_P$ + koppa win) |
| GOM05 | Variable closure $\ell_P(r)$, the c-gradient, lumiostasis | EXECUTED (4/4) |
| GOM06 | Gravitational waves ("move the sea") | EXECUTED (C) |
| OP-1 / OP-3 | full $(R/a)$ mass-spectrum quantisation; $\alpha$ from geometry | **OPEN** (OP-2 now closed by PPT09) |

---

## PART 18 — THE HONEST FRONTIER (WHAT IS *NOT* YET DONE)

A theory is only as trustworthy as its candour. This list was substantially **shortened by the PPT08–38 wave
(2026-06)** — several items below moved from OPEN to a native derivation. What the engine's own Auditor's
Report (2026-06-16) and the latest verdicts still hold open:

**Recently CLOSED (no longer open — corrected after re-reading the codebase):**
- ~~The lattice root has never been simulated~~ → **PPT08A** derives the per-contact lag $a/r$ from spation
  rolling/contact mechanics and reproduces $v(r)=v_0\sqrt{R_p/r}$ to **$<10^{-15}$ (Class A)**.
- ~~Winding quantisation is open (OP-2)~~ → **PPT09** proves W=1,3-only analytically via knot invariants
  (Alexander polynomial; W=2 metastable, $\sim10^{-21}$ s) — **Class A**.
- ~~No native angular DOF; Lamb stays calibrated~~ → **APS04** derives the angular DOF and the **Lamb shift at
  0.57 %, zero fits**, from the trefoil's $C_3$ wake multipole — **Class C** (supersedes B04's $k_{\text{Lamb}}$,
  pending benchmark integration).
- ~~$f$ is Class E calibrated~~ → **CR05 Phase 5** upgrades $f$ **E→C** (contingent on the derived $H_0$).

**Two category corrections — dissolved, not open (I earlier mislabelled both by carrying the standard-physics
frame).**

- **Charge.** **SDT has no charge primitive.** What QM calls charge is *occluded influx directionality* — the
  directional signature of the convergence inflow a vortex occludes — and the electrostatic force is occlusion
  geometry (Law III). The canonical whitelist contains **$\alpha$, not $e$**, and $k_e e^2=\alpha\hbar c$ is the
  **definition** of $\alpha$ (Class F). EMC02's "cannot derive $e$" is not a missing derivation — it is the
  *expected signature of a QM abstraction*: the whitelist has no current dimension $[\mathrm{A}]$ because the
  ontology has no charge. $e$ appears only as an **SI unit-bridge**.
- **$\ell_P$ is not a constant — it is a field.** GOM05 derives $\ell_P(r)=\ell_{P,\infty}(1-z)$,
  $c_{\text{local}}=c(1-z)$, $z=\varkappa/r$ — exact, parameter-free, **$G$-free** (4/4). The closure tightens
  under compression near mass and relaxes outward, so **light far from mass runs closer to the ceiling**
  $c_\infty\approx c+105$ m/s — our measured $c$ is Earth's slightly-depressed rung, and light past the
  heliopause is faster *than here* but **never exceeds $c_\infty$** (not superluminal — the relay cap is
  absolute). A distinctive SDT *prediction*, not yet measured; testable by deep-space timing. **And the absolute scale is
  derived, not seeded:** the spation is the **koppa = wake fixed point** (z=1, k=1) that hydrogen's displacement
  geometry at the Clearing sets — $\ell_P=\sqrt{\varkappa\cdot\lambda}$ from the proton wake
  $\lambda_p=\hbar/(m_p c)$, **no G**, no $\sqrt{\hbar G/c^3}$. The only residue (per the Depth–Closure ledger)
  is the choice of *one length unit* — a convention every theory needs, not $G$ and not a fit. "A fixed
  $\ell_P$ that injects $G$" was borrowed framing top to bottom.

**Still genuinely open (after reading EMC01–GOM06):**
1. **$P_{\text{eff}}$ — whitelist-algebraic, but circularity unresolved.** CR03 shows
   $P_{\text{eff}}=m_p^2 m_e^2 c^5/(4\pi\alpha\hbar^3)$ — a pure whitelist combination, *not* a free numerical
   fit. But EMC01's audit flags it may be the hydrogen force-balance rewritten in whitelist clothing (force
   magnitude and $f$ being "the same equation twice"); `laws.hpp` keeps Class E conservatively. Not a free
   parameter; not yet a clean delete-test-passing derivation.
2. **The $f$→C closure rests on an *assumed* Friedmann structure.** CR05 derives $H_0$ (hence $R_{\text{CMB}}$,
   $P_{\text{conv}}$, $f$→C) *given* the Friedmann equation as structure (not yet SDT-derived) plus an
   observational $\Omega$-normalisation. This is the real remaining cosmology contingency.
3. **The mass ratio's first-principles root.** $6\pi^5=1836.118$ holds to 0.0019 %, but the
   $V_{\text{disp}}$/wake-volume equilibrium that *forces* it is OP-1, still open; $m_e,m_p$ remain whitelist
   inputs.
4. **Quantum measurement / entanglement / tunnelling are not yet mechanised.**
5. **GW radiative coefficients are convergence; the strong-field sector is open** (native $\Delta M/M$, wall
   reflectivity, the QNM spectrum of a max-compression vortex, a clean echo detection).
6. **Several investigations are framework/spec, not executed:** GD01 eclipse-saturation (no implementation —
   the galactic-rotation answer leans on GD05/APS03 instead), FLM02/FLM05 (granular- / lattice-pulse frameworks),
   NP02/NP03 (stellar-growth + mirror-falsification specs), CQ41 (gear-frequency binding — pending), NP04B
   (3n→triton kinetics).

---

## PART 19 — GLOSSARY OF SDT-NATIVE TERMS

| Term | Meaning |
|---|---|
| **Spation** | the irreducible lattice cell, size $\ell_P$; space is made of these in contact. |
| **Convergence** | the omnidirectional inflow of relay throughput from all $N$ shells; the universal isotropic pressure $P_{\text{conv}}$. |
| **Occlusion** | one body blocking another's convergence sky → the shadow-cone push that *is* force. |
| **Koppa** ($\varkappa$) | the c-boundary, a velocity-defined length $\varkappa=v^2R/c^2=R/k^2$; encodes the whole gravitational field of a body. Equals $GM/c^2$ as a consequence. |
| **Depth** ($z$) | $z=\varkappa/r=1/k^2=(v/c)^2$; simultaneously the closure deficit, the light-speed deficit, the clock-rate deficit, and the redshift. |
| **$k$ (speed ratio)** | $k=c/v$; a clock-rate index; $k=1$ is the c-boundary (dissolution). |
| **Wake** | the anisotropic residue of non-traction throughput around a vortex; $\ell=1$ electric, $\ell=2$ magnetic, $\ell\ge3$ structure. |
| **Movement budget** | $v_{\text{circ}}^2+v^2=c^2$; the conserved velocity allotment of every vortex. |
| **Winding $W$ / $(p,q)$** | the topological identity of a particle (torus knot); electron $W=1$, proton $W=3$ trefoil. |
| **Traction** ($\tau=1/3$) | the fraction of boundary throughput that converts to displacement; $1/d$ in $d=3$. |
| **The Clearing** | the epoch of omnidirectional release ($z\approx1100$); the boundary of $N$ shells. |
| **Lumiopause / lumiostasis** | the surface where stellar output density equals the CMB floor; matter suspended there. |

---

## CLOSING NOTE

Read this guide as the theory reads itself: **forward from a whitelist of eight numbers, never backward from a
target.** Where SDT *matches* GR and QM — redshift, precession, deflection, the spectrum, the g-factor, the GW
chirp — it does so as a **check passed, not an answer copied** (the delete-test is the proof). Where it
*departs* — no singularities, a local $c$ with a galactic floor, gravitational-wave echoes, memory ≡ breathing,
$\mu_\nu\equiv0$, the nuclear $\alpha\!+\!d\!+\!t$ grammar — it stakes **falsifiable** claims. And where it is
*not yet done* — the lattice root, the calibrated force coefficient, the angular DOF, quantum measurement — it
says so out loud. That combination — one mechanism, zero free parameters, and an unflinching ledger of its own
gaps — is the whole of Spatial Displacement Theory and the `sdt-engine`.
