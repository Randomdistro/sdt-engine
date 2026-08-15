# Spatial Displacement Theory and the `sdt-engine` — A Complete, Excessively Detailed Guide

> **Author of the theory:** J.C. Harvey (James Christopher Harvey), Melbourne.
> **What this document is:** a long-form, self-contained, deliberately verbose educational tour of Spatial
> Displacement Theory (SDT) and everything the `sdt-engine` repository computes — every primitive, every law,
> every formula, every certification label, and a thorough, table-by-table account of how SDT relates to (and
> mechanically *replaces the need for*) General Relativity and quantum mechanics.
> **How to read it:** Part 0.5 is the dated state-of-the-framework snapshot (updated 2026-07-05). Parts 0–2
> are the foundations (read first). Parts 3–6 are the spine (the Six Laws, the derivation cascade, the koppa
> bridge, the Depth–Closure Theorem). Parts 7–13 are the domains (relativity, the two-channel architecture,
> gravity, atoms, nuclei, particles, cosmology, gravitational waves). Parts 14–15 are the big comparison
> tables. Parts 16–19 are the engine map, the honesty ledger, and the glossary.
> **Honesty contract:** every quantitative claim below carries a certification label
> (`DERIVED / COMPUTED / CALIBRATED / OBSERVED / PENDING`) and, where relevant, an audit class (`A–F`). SDT's
> own ruleset prizes *honesty over success*: where the theory merely **converges** with an established result
> rather than deriving it from scratch, this guide says so plainly. That candour is what makes the wins count.
>
> **Current model (2026-08-13):** cycle chain, T–P–c identities, and ledger live in
> `Papers/SDT_THEORETICAL_MODEL.md` (people: `SDT_FOR_PEOPLE.md`; web: `universe-lifecycle.html`).
> This guide remains the long tour; Part 0.5 is a 2026-07-05 snapshot.

---

## PART 0 — THE ONE-PAGE ORIENTATION

**The thesis in one sentence.** Space is not emptiness and not a smooth manifold; it is a **gap-free lattice of
contacting cells ("spations")** that relay deformation at one cell per tick — and *every* physical
phenomenon (force, mass, light, gravity, charge, the expansion of the universe) is a consequence of how that
relay is loaded, occluded, displaced, and budgeted. There are **no free parameters**: the entire framework is
forwarded from a derivation basis of eight measured constants — compressed, as of FLM13 (2026-07-03), to **four plus
a thermal seat** (Part 2.1) — and a quantity that cannot be built from them is not admitted.

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

## PART 0.5 — STATE OF THE FRAMEWORK

This guide follows the current engine and direct assessments. Lamb intervals are observed inputs; PPT09
establishes knot classification but leaves winding stability dynamics open; CR05 does not derive H₀ or upgrade
the transfer ratio from Class E. Benchmark totals must be taken from the current executable rather than a dated
scoreboard.

**2. The audit layer grew teeth — and a mirror.** The HUNTER protocol (kill-list, cascade ledger, the seven
questions) is now framework law, and on 2026-07-04 it gained **§G**, which audits the auditor: the faith
ledger, the gatekeeper check, and *nothing ruled in or out out of hand*. Its case history already contains
three catches that produced physics (Part 2.5).

**3. Three architectural results landed (2026-07-03/05).**

- **The two-channel architecture and the Synchrony Theorem** (Part 7A): pulses and energy relay at $c$;
  *constraint* through a gear-locked cluster is not a propagating signal and is uncapped — and because matter
  IS lattice structure, matter and space **cannot desynchronise**, so flat marginals (no-signalling) are a
  theorem, not an axiom. The completed theorem opens the sharpest falsifiable fork with QM on the books.
- **FLM13** (Part 2.1): $\{\hbar, m_e, m_p\}$ collapse to **one mass/action seat** — a baryon-count anchor.
  The classical derivation basis compresses to $\{\ell_P,\ c,\ \alpha,\ \text{one seat},\ k_B/T_{\text{CMB}}\}$. The
  seat's VALUE stays OPEN per the Seed Theorem — now explicitly premise-classed under §G.3 (proven inside the
  static-spation class; the FLM14 rotation DOF is the named re-open condition).
- **GOM14** (Part 5): a mass-free koppa-density built from transit observables only holds across **693
  multi-planet systems** (median intra-system scatter 5.9% vs 50.7% shuffled; the tightest duodecile 0.018%
  vs 7.62% — 418× better than chance), and the same formula lands the Sun at $\varkappa_\odot = 1476.6$ m
  (CODATA 1476.6). Class C, earned; gravity runs on lengths, times and ratios with no kilogram anywhere.

**4. The strike-force wave (~30 investigations, 2026-07-04/05)** executed the quantum-foundations, condensed-
matter, plasma, optics and chemistry suites under §G and the two-channel doctrine — zero fabrications, every
FAIL pre-committed. The earned headlines (each with its honest verdict class) are tabled in Part 16.2; the
kills and the roots they exposed are in Part 18.

**5. The convergence.** Essentially every open *number* in the framework now queues behind **one instrument**:
the rotating-lattice solver (ROOT-SIM / FLM14). The residence law's five debts (Born, Bell, tunnelling
re-seeding, spin re-preparation, the double-slit count), the lock-depth of superconductivity and the nuclear
alpha, the charge-closure gain, beta-decay's exit-channel count, and the contact wall (with a registered
three-way numeric cross-check) all name it as owner. FLM14's run 3 delivered the first Born-adjacent exponents
ever measured in the program — honestly **unclaimed** (one β short of the pre-committed licence) — and run 4
(the tour-side constraint channel) is in flight. Part 18.5 is the full ledger of what is owed.

**6. Canon flags remain explicit.** NP12's radius formula remains a separate
decision. The target-defined `cosmology.hpp::t_coupled` remains quarantined for
CR03 Route B; B15 now bypasses it with the CR08 standing-equilibrium route.

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

### 2.1 Scales

> `ℓ_P` is the dimensional seed. `c`, `k_B`, `e` are unit bridges. `{ℏ, m_e, m_p}` are one
> mass/action seat (FLM13). `α` is hydrogen’s koppa rung `k_H = 1/α`. `T_CMB` is a FIRAS clock.
> Record: `derivelist/README.md`. `sdt::laws::measured` is the engine lookup of CODATA/FIRAS
> numbers. The cascade below is how those lookup values are used.

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

**The derivation basis just got smaller (FLM13, executed 2026-07-03).** The koppa route to the action showed that
$\hbar$ *is* the $W{=}1$ rung's Onsager–Feynman circulation action — $m_e\,\kappa/2\pi = m_e(\alpha c)a_0 =
r_e m_e c/\alpha$ agree with $\hbar$ to $10^{-9}$ — but this is honestly labelled **IDENTITY-CLASS**: it
derives what $\hbar$ *is* (the circulation quantum of the fundamental vortex), not its number. The delete-test
then showed **no $\hbar$-free VALUE path exists** (every dimensionful atomic input encodes $\hbar$; the Seed
Theorem held exactly as pre-committed), and $\{\hbar, m_e, m_p\}$ collapse by exhibited bijections into
**one mass/action seat** — physically a *baryon-count anchor* (the one historically $\hbar$-free mass standard
was the artifact kilogram: a counted lump of baryons). The compressed classical-sector derivation basis is therefore

$$ \{\,\ell_P \leftarrow \varkappa(g,\rho,R),\quad c \leftarrow \text{Mercury precession},\quad \alpha \leftarrow \text{pure spectral ratio},\quad \text{ONE mass/action seat},\quad k_B, T_{\text{CMB}}\,\} $$

— eight inputs down to four plus the thermal seat. The seat's VALUE stays **OPEN** behind the Seed Theorem,
and per §G.3 (Part 2.5) that impossibility result is now *premise-classed*: it was proven inside the
static-spation class, and the FLM14 rotation degree of freedom is the named re-open condition. Labels
unchanged until a real derivation lands. (`FLM13_VERDICT.md`)

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
| **DERIVED** | Computed from the axioms with no external input beyond the CODATA derivation basis. |
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

### 2.5 The audit protocol (HUNTER/FARMER — added to the framework's law in July 2026)

The labels and the audit spine above say what a result *is*; the protocol layer says how results are *policed*.
Since 2026-07-02 every investigation runs under `Investigations/HUNTER_PROTOCOL.md`, whose arc is
**FIND → TRACE → GROUND → CORRECT → VERIFY**: a fault named but not run to its premise is half a job, because
*the prey is never the number — the prey is the false premise under it.*

**The kill-list** (any one mode = instant audit fail): IDENTITY-PASS (re-expose an input and "predict" it),
CIRCULARITY, FISHED exponents/coefficients, FISHED RECOVERY (the symmetric trap — a manufactured *fix*),
RETRO-PASS (widen a tolerance after seeing the number), PLUG, BORROW-SMUGGLE (a rival's machinery load-bearing
in the chain) — and, added 2026-07-04, **GATE-CONTRABAND**: a *kill condition* that enforces a rival's axiom
rather than a measured anchor. Gates must trace to a measurement, an internal-consistency requirement, or a
pre-committed native criterion — never to "the rival forbids it."

**The Closure Principle** (correction means CLOSE, never amputate): when the root fault is "a loop isn't
closed" — an orphaned scale, an un-derived constant, a disconnected degree of freedom — the correction is to
*derive the missing link*, not to delete the loose end. Amputation is a fake correction: it destroys the
evidence of the open problem instead of paying it. "Eliminate vs tune" is a false pair; the third and usually
correct option is **close**.

**§G — the mirror (audit the auditor, 2026-07-04).** The hunter's own premises are the one blind spot the rest
of the sheet cannot reach, so two standing questions are asked at every hunt's start and at every kill:

1. **The faith ledger** — *what am I accepting on faith, and is that justified?* Every gate, every "obviously,"
   every inherited constraint gets one explicit look. Faith is permitted only when named as faith.
2. **The gatekeeper check** — *am I allowing the oppositional standpoint to interfere with the datastream?*
   Rivals supply measured numbers; they do not supply the rules of evidence or the permitted instrument
   classes. A kill condition that exists only because the rival's axioms would otherwise be violated is
   contraband — kill the gate, not the route.
3. **Nothing ruled in, nothing ruled out, out of hand** (Harvey's rule). Status labels are a LEDGER;
   impossibility claims are LEGISLATION — the hunter keeps the ledger and refuses the legislation. Every
   "cannot be derived" must carry the premise class it was proven within and its re-open condition.
   "CALIBRATED until derived" stays absolute; "never derivable" is banned.

**Why the mirror exists — the case history.** In 2026-07-03/04 three *auditor* premises were caught by Harvey,
each producing physics on correction: (i) a **static spation** sat unexamined under every executor's solve —
correcting it spawned the FLM14 rotating-spation program; (ii) **Einstein locality** sat inside the FLM14/QM05
kill tables through two days of otherwise-maximum-pressure auditing — correcting it produced the two-channel
architecture (Part 7A), which the simulation's own failure modes then converged on independently; (iii) the
conflation **communication = desynchronisation** turned out to be the rival's, not ours — correcting it opened
the synchronous-channel fork, the sharpest falsifiable divergence from QM on the books. The auditor got
audited; the repo got healthier.

**FARMER** is the protocol's other half: where HUNTER kills, FARMER re-reads finished hunts for *transcription
losses* — real content dropped between Harvey's directives and the executed tools. The 2026-07-03 pass
(`Investigations/FARMER_PASS_2026-07-03.md`) replanted four such losses (QM05's geared rotation, NP10's
saturation-at-contact, GOM13's per-baryon column, SAR01/03's blocked-fraction ledger) and recorded the
refinements this guide cites throughout — including the Synchrony Theorem itself.

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

**CR05 scope.** Direct execution imports the Planck H₀ and Ω normalisations, while its native pressure-balance
route predicts $H_0=1.25\times10^{49}$ km s$^{-1}$ Mpc$^{-1}$ and its comoving-distance route misses
$R_{\rm CMB}$ by 50.8%. It therefore supplies no H₀ law, no transfer-ratio upgrade and no certified
$\gamma_{\rm eff}=4$ freeze-out law. Those pressure forms remain research candidates only.

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

**Scope (this is the framework's most load-bearing calibration).** The coefficient $P_{\text{eff}}=
4k_e e^2/(\pi R_p^2 r_e^2)=5.225\times10^{31}\,\text{Pa}$ and the transfer ratio $f=P_{\text{eff}}/P_{\text{conv}}
=2.125\times10^{-17}$ are **CALIBRATED (Class E)** — the hydrogen scale fixes their magnitude; they fail the
delete-test. The $1/r^2$ **structure** is DERIVED (Class C); the **coefficient** is fitted. CR05 does not
upgrade $f$: $R_{\text{CMB}}/H_0$ remains the open dependency stated in CR03.

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
the proton. **Honest status of $6\pi^5$ (stack, 2026-06-24 scorecard):** it is a *unique, zero-parameter,
19-ppm match* — among all simple $a\cdot\pi^b$ it is the only form within 0.1% of the measured ratio, the 6
has a topological home ($2\times3$, the trefoil), and there is nothing to delete-test — but the **mechanism is
untested**: *why* the proton wake integrates to $3\cdot A(S^3)\cdot A(S^5)=\pi^5$ is the wake phase-space
integral, which queues behind the lattice solver (ROOT-SIM). A strong clue, not killed, not yet derived. (The
*full* first-principles derivation is the open $V_{\text{disp}}$ equilibrium solver, OP-1.)

**The proton radius (DERIVED, B18).** $R_p=(W+1)\hbar/(m_p c)=4\hbar/(m_p c)=0.84124\,\text{fm}$ — matches the
muonic-hydrogen value to $0.02\%$; and inverting, $W_{\text{eff}}=R_p m_p c/\hbar-1=3.000$.

---

## PART 4 — THE DERIVATION CASCADE (FROM SIX NUMBERS TO EVERYTHING)

Everything flows downhill from the derivation basis through four stages. This is the spine of `laws.hpp`.

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
| | $P_{\text{eff}}$ | $m_p^2 m_e^2 c^5/(4\pi\alpha\hbar^3)$ | $5.225\times10^{31}\,\text{Pa}$ | derivation basis-algebraic (CR03); circularity flagged (EMC01) |
| | $f$ | $P_{\text{eff}}/P_{\text{conv}}$ | $2.125\times10^{-17}$ | Class E; CR05 does not remove its observed/calibrated dependencies |
| **4 Mass & stability** | $V_{\text{disp},e}$ | $3m_e\ell_P^3 c^2/\Phi$ | $9.988\times10^{-62}\,\text{m}^3$ | COMPUTED |
| | $V_{\text{disp},p}$ | $3m_p\ell_P^3 c^2/\Phi$ | $1.834\times10^{-58}\,\text{m}^3$ | COMPUTED |
| | $P_{cf}$ | $\rho_{\text{eff}}c^2=P_{\text{conv}}/3$ | identity ✓ | DERIVED |

**The Coulomb identity** $k_e e^2=\alpha\hbar c$ (T9) is *definitional* (Class F): it **defines**
$\alpha\equiv k_e e^2/\hbar c$. SDT's coupling is the dimensionless $\alpha$ (in the derivation basis); **$e$ is not** —
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

### 5.1 GOM14 — the koppa ontology tested on 693 solar systems (2026-07-03, Class C, earned)

If the koppa really is the whole gravitational field of a body, then a *mass-free density* built purely from
what a transit telescope measures — a period $P$ and a scaled semi-major axis $a/R_\star$, both ratios of
lengths and times — must come out the **same for every planet of one star**:

$$ q \equiv \frac{\varkappa_\star}{R_\star^3} = \frac{4\pi^2}{c^2}\,\frac{(a/R_\star)^3}{P^2} $$

No $G$, no kilograms, no stellar mass anywhere in the chain. Run against the NASA Exoplanet Archive
(`GOM14_VERDICT.md`): **693 host stars with ≥2 transiting planets (1,754 planets)** — the median intra-system
deviation of $q$ is **5.9%, versus 50.7% when planets are shuffled between systems** (~9×); the tightest
duodecile agrees to **0.018% versus 7.62% shuffled (418×)** — the best systems fix each other's koppa-density
to parts in $10^4$. The **same formula applied to Earth's orbit** returns the Sun's koppa
$\varkappa_\odot = 1476.6$ m (CODATA $GM_\odot/c^2$ = 1476.6 m) and a mean solar density of 1409.8 kg/m³
(accepted ≈1408). One formula, ratios only, from Kepler field stars to the Sun.

**The ontological point.** "$GM$" is measured superbly (the Sun's to ten digits); $G$ *alone* is the
worst-measured constant in physics (22 ppm) — because $G$ only exists when you insist on factoring the clean
length $c^2\varkappa$ into $G\times\text{kg}$. The kilogram split is where the uncertainty lives; the koppa
formulation never performs it. Named caveat (honest): some archive $a/R_\star$ values carry literature density
priors; the airtight version re-derives $a/R_\star$ prior-free from transit shape, and is logged OPEN.

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

## PART 7A — THE TWO-CHANNEL ARCHITECTURE AND THE SYNCHRONY THEOREM (2026-07-04)

This is the newest structural member of the framework, and it earns its own part because it reorganises how
*everything else* in this guide moves. It arrived twice in one week, from opposite directions: Harvey directed
it as a premise (the ADJ-7 note in FLM14's run log), and the FLM14 simulations independently converged on it
through their own failure modes (Part 9.5) — the isotropy ladder's every intermediate rung died, and the only
survivor was the architecture Harvey had already named.

### 7A.1 The two channels

The lattice carries two categorically different things:

| Channel | What travels | Speed | Examples |
|---|---|---|---|
| **Pulse channel** | deformation pulses — energy, light, signals, radiative waves | exactly $c$, always | photons, GW chirps, every "message" |
| **Constraint channel** | the *rigidity* of a gear-locked cluster — shared structure, not a travelling thing | not a propagation at all; **uncapped** | the static $z=\varkappa/r$ field, the gear phase of a locked cluster |

Nothing "moves faster than light" on the constraint channel, because nothing *moves* — a gear-locked cluster is
**one object**, and modulating its shared constraint is a global reconfiguration, not a relay of pulses. The
movement budget (Law V) caps the pulse channel; it says nothing about rigidity.

**Measured-class support (from GOM06's re-audit).** The classical **Laplace aberration bound** is exactly this
fork observed in the sky: stable planetary orbits require the *static* field's effective action to point at the
attractor's instantaneous position — Laplace/Lightman-class analyses bound the equivalent propagation speed at
$>10^8$–$10^{10}c$, else aberration torque would disrupt orbits on short timescales. GR handles this with
velocity-dependent field-momentum cancellation terms; SDT handles it natively — the static trace $z=\varkappa/r$
is a **constraint**, while everything radiative (the chirp, the memory, the echoes) stays on the pulse channel
at exactly $c$ (GW170817-class timing, untouched).

### 7A.2 The Synchrony Theorem (FARMER refinement 5, 2026-07-04)

**No-signalling is a necessity, not an axiom and not an empirical accident.** The argument is one step deep:
matter is not a substance sitting *in* space — matter **IS** lattice structure (M1: a persistent displacement).
Therefore the movement of matter and the movement of space **cannot desynchronise** — even under an
instantaneous 100-billion-light-year relocation of a constraint. Nothing travels *between* separate things;
one fabric reconfigures as one object. No Bell experiment has ever shown Alice's marginals shifting with Bob's
setting *because none ever can*: a marginal shift would be a desynchronisation of matter from the space it is
made of. The "paradox" Einstein locality was invented to avoid is a category error of substance-dualism
(matter moving *through* space, with $c$ capping everything). SDT gets the flat marginals **as a theorem** —
where Copenhagen postulates them and Einstein locality forbids half of the correlations that produce them.

### 7A.3 The completed theorem: communication ≠ desynchronisation (FARMER refinement 6)

The standard no-communication argument only forbids messages encoded as **local statistical anomalies** — a
marginal shift, which the fabric cannot produce (7A.2 stands untouched). It says nothing about the
**synchronous channel**: a modulation of the shared constraint of a gear-locked cluster is globally synchronous
*by construction* — both ends co-read **one object** rather than transmitting between two; marginals stay flat
forever while the lock itself carries structure. Hence both are possible with zero desynchronisation:
FTL relocation of constraint (transport) and FTL communication (co-rotation reading). The conflation of
"communication" with "desynchronisation" was the rival's, not ours.

### 7A.4 The falsifiable fork with quantum mechanics

QM's formalism contains **no locally-readable shared-state variable** — its correlations are visible only in
coincidence, after comparison over a classical channel. SDT's **gear phase is a local mechanical variable.**
If the constraint phase couples to *anything* locally measurable, there is an experiment: modulate the
constraint at one wing of a gear-locked pair, read the local phase at the other, with marginals flat
throughout. Three outcomes, all publishable. Instrument owner: FLM14 rule-form-4 (Part 9.5). This is, on the
books as of 2026-07-05, the sharpest falsifiable divergence between SDT and quantum mechanics.

**Honest scope.** The Synchrony Theorem is architecture-level: it follows from M1 plus the two-channel split,
and its *support* is (i) the Laplace aberration bound (measured-anchor class) and (ii) the FLM14 simulations
independently converging on the same architecture. The gear-phase experiment is proposed, not performed; the
constraint channel's tour-side implementation is run 4 of FLM14, in flight. Nothing here is sold beyond that.

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

*(Honesty note, canon repair 2026-07-03: B09 rides the disclosed substitution $GM\to c^2\varkappa$ — a
re-expression of the quadrupole result in koppa units, not an independent derivation of it. In the repaired
benchmark ledger B09 is shown as an IDENTITY/display row, no longer tallied as an earned prediction. The
*reinterpretation* is the content; the number was never in doubt.)*

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
*(2026-07 caveat: CH03's O₂-paramagnetism test killed the **static** shell-filling pairing map — the void
picture survives only in the rotating-spation frame below, where a "filled void" is a seat on a tour, not a
parked electron. The fifth independent field to fail at the static-spation premise; see 9.5.)*

### 9.5 The rotating spation and the sequential electron (FLM14 — the all-in premise, runs 1–3)

Harvey's 2026-07 premise sharpens the stroboscopic picture into a program: **the spation itself rotates**, and
the electron's positions are a **deterministic, gear-stepped TOUR** of lattice seats — the "orbital" is a
*sequence*, and the Born weighting is *dwell time*. This is the named premise-root under the residence law
(Born/Bell), the PPT08 Lamb seats, the NP10 nuclear lock, FLM03's rotation field and even $\varepsilon=h\nu$.
Three runs in (`FLM14_VERDICT.md`), the honest state is:

- **Run 1 — the earned support:** antisymmetric contact gearing cannot be globally smooth on a lattice with
  odd rings — **34.7% of bonds are unsatisfiable** (frustration 0.347), so rotation **must be carried by
  defects**. Particles are *forced to exist* by the gearing premise itself — OP-2's carriers falling out as a
  structural necessity, labelled NATIVE.
- **The rule-form ladder (runs 1–3):** global-clock gating ×7.47 anisotropy (KILLED) → bond-local ×2.29 (FAIL)
  → bond-local + entrainment ×1.35 best non-degenerate (KILLED) → **rule-form-4, the two-channel split** (pulse
  at $c$, constraint rigid): anisotropy ×1.0000 ± 0.0000. Stated plainly, as the verdict does: form-4 does not
  *earn* the isotropy gate — it **dissolves** it by architecture; gearing lives on the constraint channel and
  the pulse channel cannot see it. The ladder's lesson was never "anneal harder" but "gearing and relay are
  different channels" (Part 7A).
- **Run 3 — the falsifiable residue:** the constraint network **percolates** — 85.5% of sites join one rigid
  cluster whose collective rotation collapses to $|\Omega|/\omega_0 = 0.0046$ (gear-locking freezes rotation),
  with 47.9% of bonds locked (the $W=0.5$ duty forecast, an honest match). A near-static rigid backbone
  threaded by frustration-forced carriers — **OP-2's picture arrived at from the gearing side.**
- **The first Born-adjacent exponents ever measured — and not claimed:** the seat-occupancy exponent
  $p_{\text{occ}} = +2.375 / +2.325$ at β = 0.2/0.4 (robustness variant +2.291). Two consecutive defined betas;
  the pre-committed licence requires three; split-half and seed-replication checks fail. Direction of travel
  reported, **nothing graded** — the statistics gate held. *(Scoping annotation, 2026-07-05, Harvey's §G audit:
  run 3's constraint channel was implemented in the lattice only — the tour itself ran single-channel, so both
  the exponents and the NP14-seat probe negative are scoped to the uncorrected instrument.)* **Run 4** — the
  tour-side constraint channel, new pre-committed ADJ — is the licensed instrument for both questions, in
  flight as of 2026-07-05.

### 9.6 The Lamb "shift" is a spacing — the native target table (PPT08_KOPPA_TARGET, 2026-07-04)

The angular-DOF problem (why $2S_{1/2} \ne 2P_{1/2}$) remains **OPEN**. The target is
well-posed in native coordinates
(`PPT08_Angular_DOF_from_Trefoil/PPT08_KOPPA_TARGET.md`, class RE-EXPRESSION, not extraction):

- **Reframing (Harvey): a spacing, not a shift — Dirac was simply wrong.** The word "shift" embeds the rival's
  failed expectation: Dirac's structure *forbade* any 2S/2P splitting, and the measurement violated his
  theorem. In SDT two geometrically different seats at the same $n$ have no reason to coincide — the splitting
  is the *null expectation*; degeneracy would have been the anomaly.
- The measured **1057.8 MHz ≡ a 0.703 m/s seat-speed offset ≡ a 0.272 fm radial offset at n = 2** (one
  quantity, three rulers, via $v=c\sqrt{\varkappa/r}$) — RE-EXPRESSION of the Lamb–Retherford sticker.
- Hydrogen is the **proton center**; He⁺ (14041.13 MHz) is a second OBSERVED sticker on the **α center**.
  Construction names two protons; it does not derive 14041 from 1057. The old three-line grading table mixed
  those objects and is withdrawn as a closure target.
- The **$R_p/3$ cluster** (trefoil node radius 0.2805 fm vs the n=2 offset 0.2722 fm, −2.9%) remains
  look-elsewhere, not a match.

The canon carries `lamb_shift_measured_MHz = 1057.845` and `lamb_shift_He_plus_measured_MHz = 14041.13` as
OBSERVED inputs. Extraction of 1057 from trefoil/FLM14 is withdrawn (2026-08-13).

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

### 10.1 The mass defect is shadow overlap — the meshing IS the defect (2026-07-03/04)

The Nuclear Packing Sequencer (`Release/HTML_SDT_Website/nuclear-packing-sequencer.html`, with its narrated
companion `nuclear-packing-walkthrough.html` — part of the site family that also includes `sdt_walkthrough.html`
and the `st_00`–`st_04` law-by-law scrollthroughs) turns the grammar into a live geometric model, and it
carries the framework's current account of binding energy. Occlusion is an *area* phenomenon ($\pi R_p^2$ per nucleon), so
when trefoils interleave, their shadows **overlap** — and the shared occlusion must be counted **once, not
twice**. The bookkeeping is *union, not sum*:

$$ \Delta A = \sum_i A_i - A_{\cup}, \qquad E_{\text{bind}} = \kappa\,\Delta A $$

One scale κ; the shadow union tracks the measured binding of **217 isotopes at R² = 0.981** under the
opposition-packing geometry (α = 4-fold, triton = 3, deuteron = 2, holes toward the shared centre), mean error
under nine parts in a thousand of total binding. The conceptual load-bearer (FARMER refinement 3): **the
meshing IS the mass defect.** When forms mesh they work in parallel, in synchrony — the meshed pair needs less
total movement-resistance than the two isolated forms, and the *saving* is the defect. Corollary: you cannot
use the width of a form to measure movement once forms interleave — the interleaved region is not attributable
to either form separately, which is exactly why the literature's "the proton radius changes in nuclei" puzzles
dissolve. This is the same statement FLM12 earned independently from the relay side ("mass defect = synchrony
saving") — two routes, one fact. Honest residuals: the pure-area model over-binds the α-cluster and misses the
iron peak; the missing piece is the shared-seat well depth — the same ROOT-CONTACT closure as 10.3. And the
stability question answers itself natively: bound rotators don't radiate — *that is what stability is.*

### 10.2 The neutron's 0.782 MeV — the seat, the electron, and the neutrino's complement (NP14/NP22)

The neutron-identity thread ($n = p + \text{internal } e^-$) reached a sharp, honestly-graded state in July:

- **Earned (NP14):** the sign and structure. The neutron is heavier because it *holds* an extra electron
  (+0.511 MeV, structural) on a seat *above* the free $p+e$ ground — which is exactly why β-decay is downhill.
  $\Delta m$ splits cleanly as $1.293 = 0.511 + 0.782$, and the 0.782 is $Q_\beta$ — an identity, never sold as
  a prediction. The native magnitude map came in at **−23.3% (FAIL → OPEN)**; the seat *depth* itself
  (1.830c) is solid to 0.006% by two independent routes, so the debt is the depth→energy map.
- **The appendix candidate ([OPEN], look-elsewhere applies):** the 0.782 MeV the verdict failed to produce is
  *exactly* the relativistic kinetic energy of the internal electron at $v = 0.9186c$:
  $(\gamma-1)m_ec^2 = 0.782$ MeV. The best geometric candidate for that speed — $(m_p/m_e)/2000$, "half of
  1836" — sits 0.06% off. And Law V's budget gives the complement: $\sqrt{1-0.9186^2} = 0.395c$ — **the
  neutrino takes the other side of the speed.** If it holds, it buys the continuous β spectrum (variable
  partition of one fixed internal speed), the endpoint (electron takes all of it), and ν̄ handedness (the
  released gear sense) in one stroke. Logged as a candidate, not a result.
- **The test was run and it taught something bigger (NP22, 2026-07-04):** grading the 0.9186c-seat unwinding
  against the measured free-neutron β *shape* — **FAIL → OPEN, and the entire 1-DOF release-measure class is
  KILLED knob-proof** (the committed isotropic measure missed at KS D = 0.49 vs gate 0.15; verified for four
  declared measures). The reason is structural: the Kurie plot's endpoint exponent +2 and low-energy +½ are
  **per-particle 3-D state-count fingerprints** — one release angle has no sphere. SDT must *earn its spheres*
  from seat geometry: the owed object is a native 3-D exit-channel count $N_{\text{exit}}\propto E^2$, whose
  lineage runs straight to FLM14's sequential occupancy (Part 9.5). The endpoint at $Q = 0.782333$ MeV is an
  IDENTITY, never tallied; the continuum's *existence* is earned (cheap).

### 10.3 Canon decisions pending (propose-and-wait, honoured)

- **NP12 — the nuclear radius formula.** The canon rule $R = Z\cdot R_p$ is **KILLED by 908 IAEA measured
  radii** (RMS 890.8% — 179× off). The zero-fit native replacement is ready:
  $R = R_p\,(A/\eta)^{1/3}$ with $\eta = \pi/\sqrt{18}$ (close-packing density) → **4.96% RMS**, degenerate
  with the fair $A^{1/3}$ rival globally but winning at isotope-chain level (Ca chain 1.67% flat vs 8.63%).
  No canon edit has been made — the decision is Harvey's.
- **`cosmology.hpp` t_coupled** — flagged circular
  ($\equiv$ BAO_scale/$c_s$) and still excluded from CR03 Route B. CR08/B15 no
  longer consumes it: the resistance-standing scale is canonical in
  `laws.hpp::bridge::release_acoustics`.

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
| Pressure evolution | $P(z)\propto(1+z)^4$, $\gamma_{\text{eff}}=4$ (topological stiffness) | **OPEN candidate**; CR05 does not derive the exponent or freeze-out mechanism |
| Hubble constant | $H_0$ from lattice pressure | **OPEN**; CR05 imports the comparison value and fails on its native route; $R_{\text{CMB}}/H_0$ remains underived (CR03) |
| Cosmological "constant problem" | the $10^{123}$ is $N^2=4\pi$-scaled boundary-cell count, not a vacuum-energy failure | DERIVED |
| BAO standing-equilibrium ruler | $L_{\rm BAO}=145.819$ Mpc from energy equality, per-baryon phase resistance and an acoustic round trip | **COMPUTED** (B15; 0.864% vs 147.09 Mpc; shared FIRAS/BBN provenance) |
| Cosmological redshift | depth at emission ($z=\varkappa/r$) + a propagation term along the line of sight | C on emission; the **propagation law $d(z)$ is OPEN** — the exponential strain law is excluded (CR06 SNe; CR08 BAO), the octave/cubic-rung successor has no distance closure yet, and CR09's isotropic radial κ-gradient is excluded 0/122 |
| SDT vs ΛCDM head-to-head | Tolman surface brightness, the CMB $(1+z)^4$ energy density, Pantheon SNe | **shared-input correspondence** (CR10/11/12): SDT *matches* without a dark sector but does not *beat* ΛCDM; the remaining separator is the κ(z)/BAO-CMB acoustic-peak decider |
| Dark matter | convergence-disk occlusion candidate | PARTIAL; the acceleration-floor magnitude is not derived |
| Dark energy | a pressure-gradient *misreading* of the lattice EOS, not a substance | SPEC |

**Scope:** CR05 does not derive $H_0=67.4$; its tool imports that value. Therefore
$R_{\text{CMB}}$ (equivalently $H_0$) is an **observational input**, the Friedmann structure is not
SDT-derived, and the three classical cosmology tests all tie the rival rather than beating it. What SDT's
no-expansion reading *does* buy without a dark sector — the Hubble-tension dissolution (emission and
propagation terms conflated by ΛCDM), the $10^{123}$ as a cell count, the BAO shells as physical structure —
stands, each at its labelled class. The decider is named: the κ(z) unified fit against the CMB acoustic peaks.

---

## PART 13 — GRAVITATIONAL WAVES (GOM06: "MOVE THE SEA, DON'T MAKE WAVES")

SDT's account of LIGO/Virgo events, gate by gate (full investigation in
`Investigations/06_Gravitation_and_Orbital_Mechanics/GOM06_Gravitational_Wave_Mechanism/`).

### 13.1 The mechanism
A GW is **the medium being moved, not a ripple made in it.** The relay-lattice deformation is a strain tensor
$\varepsilon_{ij}$ whose **trace** is the depth $z$ (static gravity, the Depth–Closure scalar) and whose
**traceless shear** is the radiative wave. The sea's *volume* (trace) is the static field; its *shape* (shear)
is the gravitational wave. This makes the GW **tensor-polarised by construction** — exactly GR's two modes
$h_+,h_\times$ — with no scalar–tensor tuning.

*(Two-channel update, 2026-07-04: the split above is now understood as the two channels of Part 7A — the
radiative shear is a **pulse-channel** phenomenon and travels at exactly $c$ (GW170817 timing untouched), while
the static trace $z=\varkappa/r$ is a **constraint** whose effective action the Laplace aberration bound
requires to be $\gg c$. GR pays for the same fact with velocity-dependent cancellation terms; SDT gets it from
the architecture.)*

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
| **Free parameters** | $G$, $\Lambda$, plus initial conditions | zero (derivation basis only); the one calibration ($P_{\text{eff}}$) is flagged |
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
| The Born rule $\lvert\psi\rvert^2$ | postulate | the **square is elastic energy** (derived — see below); the landing law is the one open scalar (RESIDENCE-LAW, owner FLM14) | QM04 |
| Uncertainty $\Delta x\Delta p\ge\hbar/2$ | operator postulate | relay-bandwidth floor from lattice granularity — the ½ floor and the finite spation are the same fact | QM02 |
| Tunnelling | wavefunction leakage | wake leakage through an occlusion slab — native barrier form; Schrödinger's constant is its NR *limit* | QM03 |
| Spin two-valuedness | intrinsic SU(2) | binary circulation handedness $\eta=\pm1$ — two spots, no middle, native | QM07 |
| Entanglement / no-signalling | nonlocality + no-communication *postulates* | the **Synchrony Theorem** (Part 7A): matter IS lattice structure ⇒ marginals cannot shift, as a theorem; correlations ride the constraint channel | QM05/FARMER |

**The angular DOF and the Lamb interval.** **PPT08 is OPEN; the SDT Lamb amplitude is unbuilt.**
The H and He⁺ intervals are observed inputs. Part 9.6 states the target in native coordinates
(Lamb = a seat **spacing**, not a derived "shift"; 0.272 fm at n=2), and any future
mechanism is graded against that table.

**The quantum-foundations strike force (2026-07-04) — what a lattice mechanics actually earned.** Executed
under §G with pre-committed gates, zero fabrications:

- **QM04 (Born rule): the *square* is no longer a postulate.** The field code contains only real travelling
  carriers $\cos(kr-\omega t)$; time-averaging the summed displacement squared produces the full
  envelope·$\cos^2$ fringe to RMS $3.3\times10^{-14}$ — **with $\cos^2$ appearing nowhere in the code.** The
  "amplitude-squared" is the stored elastic energy of a superposed displacement field: geometric, not
  axiomatic. Normalisation ($\Sigma P=1$) and positivity are structural (count conservation; elasticity). What
  remains open is one scalar law — landing counts ∝ energy density — and the run's sharpest result is a
  pre-registered *negative*: naive least-resistance steering misses by 215% RMS, so "any steering gives Born"
  is dead as a hand-wave. The residence law is specific, owned by FLM14 rule-form-4, and its acceptance test
  (<1% RMS from a mechanical rule, beating the killed null) is on file.
- **QM03 (tunnelling): the barrier form is native, and Schrödinger is its limit.** The relay solver (which
  never saw WKB) produces evanescent decay with
  $\kappa_{\text{native}}^2 = 2m(V-E)\bigl(1+(V+E)/2mc^2\bigr)$ — the textbook $\sqrt{2m(V-E)}/\hbar$ is the
  **non-relativistic limit** of the native form, and SDT predicts a *falsifiable high-barrier departure* at
  $V,E\sim mc^2$. Downstream, zero-fit: STM decay 0.94 current-decades/Å; **Geiger–Nuttall α-decay linearity
  R² = 0.9997 across 24 decades of half-life** (worst nuclide 0.54 decades, slope within 3.4%). The traversal
  time *saturates* (Hartman-like) — under the two-channel doctrine a native outcome to hold against attoclock
  data, not a paradox to suppress.
- **QM02 (uncertainty): the ½ floor is lattice granularity.** The energy-weighted width product has a floor of
  ½ for every buildable pulse; at the lattice scale the floor survives *because* a site carries
  $\Delta x \ge a/\sqrt{12}$ — **the uncertainty floor and the finite spation are the same fact**, with a
  testable fingerprint $\tfrac12(1+O(a^2/\Delta x^2))$. The floor binds the pulse channel only.
- **QM07 (spin): two-valuedness is native.** Binary circulation handedness gives two spots and no middle —
  machinery, not postulate. The *sequential* Stern–Gerlach $\cos^2(\theta/2)$ is honestly FAILED by the naive
  hidden-vector law (RMS 0.072) and lands in the same residence law as Born and Bell.
- **QM05 + the Synchrony Theorem (Part 7A): Bell's burden relocated.** A bare marginal-preserving joint rule
  reaches CHSH $S=4.0$, so SDT's entire burden is the specific $\cos^2(a-b)$ joint weighting — the same one
  scalar law again. Flat marginals are a *theorem* (7A.2); FLM14's run 3 measured the first Born-adjacent
  exponents ($p_{\text{occ}}=+2.375/+2.325$) and **did not claim them** (one β short of the licence); CHSH runs
  stay correctly unlicensed until a stable regime exists.

Five apparent postulates; after the wave, **four are machinery and the fifth is one named scalar law with an
owner, an acceptance test, and a killed null.** That is the honest scoreboard — no more, no less.

**The honest boundary that remains.** Two things an earlier draft mislabelled are *dissolved*, not gaps:
**charge** (a QM abstraction — SDT has *occluded influx directionality*, not a charge primitive; $\alpha$, not
$e$, is in the derivation basis) and the **fixed $\ell_P$** (GOM05 makes it a variable closure *field*
$\ell_P(r)=\ell_{P,\infty}(1-z)$, derived as the koppa = wake fixed point from hydrogen geometry, not $G$). What genuinely remains:
multi-electron atoms (**PENDING**, B06); the **$P_{\text{eff}}$ force coefficient calibrated to hydrogen**
(`laws.hpp` Class E); the **observational $R_{\text{CMB}}/H_0$** behind the cosmology (Part 12); the **native
angular DOF / Lamb amplitude** (OPEN, graded against the Part 9.6 table); and **the residence law** — the one
scalar into which measurement, Born, Bell and sequential spin have all been compressed, owner FLM14. The QM
*rule book still computes correctly*; SDT's claim is that where it has supplied a mechanism, the mechanism is
local, hard, and deterministic — and the remaining gaps are honestly logged, not papered over.

---

## PART 16 — THE BENCHMARK LEDGER (B01–B29, THE REGRESSION FLOOR)

`Benchmarks/B01_B25/benchmarks_b01_b25.cpp` is the end-to-end verification; it self-reports PASS/FAIL against
measured constants.

**Benchmark reporting rule:**

> Use the current benchmark executable for totals; identities and calibrated rows are shown but never
> tallied as independent predictions.

This supersedes both the old "all 25 PASS" and the interim "62/73" tallies — the latter counted definitional
identities and calibrated fits as earned passes. The repair's principle: **identities are shown, never
tallied.** A number the tool read in (or that is true by substitution, like $GM\to c^2\varkappa$) is displayed
for the reader as an identity row, and is not allowed to inflate the score. B04 reports H and He⁺ Lamb
intervals as observed stickers with no derived tally. The per-benchmark table below records that scope.

| # | Verifies | Result | Label |
|---|---|---|---|
| B01 | H energy levels | $E_n=-\text{Ry}\,Z^2/n^2$ | DERIVED |
| B02 | Multi-ion Rydberg (He⁺, Li²⁺) | exact spectral match | DERIVED |
| B03 | Fine structure, g-factor | $2P$ split $4.528\times10^{-5}$ eV; $g=2.00232$ | DERIVED |
| B04 | **Lamb interval** | observed H 1057.845 MHz and He⁺ 14041.13 MHz | OBSERVED; APS04 +0.761 MHz addend; no derived tally |
| B05 | Hyperfine 21 cm | $1420.405$ MHz | DERIVED (line OBSERVED; mechanism re-narrated) |
| B06 | Multi-electron ionisation | Slater screening | **PENDING** (open atoms problem) |
| B07 | Stefan–Boltzmann, Wien | $\sigma_{SB}=5.670\times10^{-8}$; $\lambda_{\max}T=2.898\times10^{-3}$ | DERIVED |
| B08 | Earth orbital velocity, $GM_\odot$ | $29783$ m/s; $1.327\times10^{20}$ | DERIVED |
| B09 | Binary-pulsar $\dot P_b$ | B1913+16 and J0737-3039A/B from timing depth and resistance quadrupole | **DERIVED** (GOM06; no source-mass parameter) |
| B10 | Mercury precession; light deflection | $42.98''$; $1.7505''$ | DERIVED |
| B11 | Earth & Jupiter $J_2$ | uniform-fluid estimate | **PENDING** |
| B12 | Stellar $zk^2=1$ (5 stars) | $=1.0$ across 10 orders | DERIVED |
| B13 | CMB redshift | $z=1089$ | DERIVED |
| B14 | Galactic $R_{\text{flat}}\approx2.5R_d$ | 12 % tolerance | COMPUTED |
| B15 | BAO standing-equilibrium ruler | $145.8189$ Mpc vs $147.09$ Mpc | COMPUTED |
| B16 | Dilute-monatomic transport | Ar $\mu,k,D$ whole-curve RMS 9.71%, 9.67%, 7.81%; exponents 0.5, 0.5, 1.5 | COMPUTED |
| B17 | Electron g-factor | $g=2(1+\alpha/2\pi)=2.00231930436$ | DERIVED |
| B18 | Proton radius (W+1), He-4 | $R_p=0.84124$ fm (0.08 %); $R_{He}=2R_p$ | DERIVED |
| B19 | Beta-decay Q-value | $0.782$ MeV | DERIVED |
| B20 | $zk^2$ universality | $=1.0$ exact | DERIVED |
| B21 | EM/grav force ratio | $\approx2.27\times10^{39}$ | **IDENTITY, display-only** (de-tallied 2026-07-03) |
| B22 | Pressure hierarchy | $P_{\text{eff}}=5.225\times10^{31}$; $f=2.125\times10^{-17}$ | COMPUTED |
| B23 | Coulomb identity $k_e e^2=\alpha\hbar c$ | 0.1 % | DERIVED |
| B24 | Exclusion volumes; marginal stability | $P_{cf}/(P_{\text{conv}}/3)=1.0$ | COMPUTED/DERIVED |
| B25 | He total electron binding | $79.968$ eV vs $79.005$ eV (1.22%) | COMPUTED |
| B26 | Trefoil $(2,3)$ budget; $m_p/m_e=6\pi^5$ | $1836.118$; $v_{\text{phase}}=1.830c$ | DERIVED/COMPUTED |
| B27 | Koppa closure: $c$ from Mercury precession | $c$ reconstructed | COMPUTED/DERIVED |
| B28 | Depth-closure $z=\varkappa/r$ | solar redshift; Earth $v=c\sqrt{\varkappa/r}$ | COMPUTED/DERIVED |
| B29 | GW chirp as length (GW150914) | $f_{\text{isco}}$ from $\varkappa_{\text{tot}}\approx96$ km | COMPUTED |

*(The former B15/B16/B25 literal debts were replaced in place on 2026-08-15.
Remaining suite physics debt is B11's whole-corpus interior-resistance profile
and B18's He-contact correspondence; B37 awaits measurement.)*

### 16.2 The strike-force earns (2026-07-04/05) — quantitative table

The July wave ran roughly thirty investigations across quantum foundations, condensed matter, plasma, optics
and chemistry under §G. These are not benchmarks (they live in `Investigations/**/*_VERDICT.md`), but they are
now part of the framework's quantitative floor. Verdict classes are quoted exactly as filed — nothing below is
promoted past its class:

| Inv | The earned thing | Number | Class |
|---|---|---|---|
| QM04 | the Born *square* = elastic energy of the summed displacement field ($\cos^2$ nowhere in code) | cross-term RMS $3.3\times10^{-14}$; steering null killed at 215% RMS | NATIVE machinery; residence law OPEN |
| QM03 | native barrier form; Schrödinger = its NR limit (falsifiable high-barrier fork); Geiger–Nuttall zero-fit | R² = 0.9997 over 24 decades of $t_{1/2}$; STM 0.94 dec/Å | CONVERGENCE + fork |
| QM02 | uncertainty ½-floor from lattice granularity (floor ≡ finite spation) | min 0.5048 with site-width rule; fingerprint $\tfrac12(1+O(a^2/\Delta x^2))$ | CONVERGENCE (pulse channel) |
| QM07 | spin two-valuedness native (binary handedness → two spots, no middle) | sequential $\cos^2(\theta/2)$ FAILS naive law (0.072) → residence law | NATIVE (two-valuedness) / OPEN (sequence) |
| CM01 | superconductivity chain with circularity structurally impossible; isotope effect | isotope exponent **−0.5000** (Hg anchor 0.50±0.03) | NATIVE structure; η = T_c/θ_D magnitude OPEN (ROOT-B) |
| CM04 | Debye temperature from measured sound speeds + one geometric rule | θ_D(Cu) = 341.8 K vs 343 (**−0.4%**); diamond +3.3%; NaCl −10.1% FAIL reported | CONVERGENCE 3/4 |
| CM06 | quantum-Hall edge-channel count robust over disorder | **ν = 2 exact** over three orders of density | CONVERGENCE, conditional on ROOT-A (h-cell) |
| PM01 | the Ampère force exponent is a conservation theorem, not a fit | $\lvert w\rvert$ exponent **−1.0000** (forced); non-conserving control −2.0000 fails as it must | NATIVE |
| PM04 | Debye screening — **the wave's first full RECOVERED** (premise traced, closed via the TD02 bath) | λ_fit vs λ_D **−6.8%**, exponential R² = 0.943 | RECOVERED |
| PM07 | frozen-in magnetic flux as a **counting theorem** (ideal induction with no Ohm's-law postulate) | slip ∝ η verified | NATIVE |
| OP02 | Fresnel coefficients emerge from relay impedance; **Brewster is a true zero** | 0.000e+00 error over 0–89.9° | NATIVE result; component-pairing rule asserted (OP-ROOT) |
| CH02 | the Madelung-analogue computed from pure lattice geometry (Evjen cubes) | **M = 1.747574** (literature 1.747565 as cross-check); NaCl +9.4% in-gate; MgO +21.6% FAIL reported | CONVERGENCE; overshoot = ROOT-CONTACT fingerprint |
| CH06 | the van der Waals −6 **emerges** as second-order correlation of leaked rim residuals (2×(−3)) | fitted slope **−6.0225/−6.0224**, invariant under ×10 parameter changes | NATIVE |
| CH07 | the structural theorem: the NP17 shared-seat well **binds but cannot vibrate** — the IR stretch is direct evidence of the missing short-range wall | measured k(H₂) = 575 N/m = the missing term's curvature | NATIVE theorem + OPEN wall |
| OP07 | the solar temperature-minimum fold **KILLED as claimed** (limb-generic mapping inversion at every λ); the lens-artifact experiment corrected | monotone R(λ) toward the H⁻ opacity minimum + limb pile-up at every λ | KILL + corrected falsifier |

Two things to notice, because they are the culture of the repo in one table: the **kills and FAILs are listed
with the same prominence as the passes** (MgO, NaCl-θ_D, the sequential-spin law, the temp-min fold), and
almost every OPEN names the *same* small set of roots — ROOT-CONTACT, ROOT-A, ROOT-B, HG-1, OP-ROOT, the
residence law. That convergence is Part 18.5.

---

## PART 17 — THE INVESTIGATION MAP (DOMAIN CODES)

The `Investigations/` tree pushes open questions to recorded conclusions. (The old `CQ##` numbering is retired —
investigations carry domain codes: FLM foundations, PPT particle/topology, EMC electromagnetism, APS atomic,
NP nuclear, GOM gravitation/orbital, CR cosmology, GD galactic, SAR stellar, plus the numbered fields 10–16
for fluid/thermo/condensed/quantum/plasma/optics/chemistry.) A representative slice, current to 2026-07-05 —
the rows below state their current scope:

| Investigation | Topic | Status |
|---|---|---|
| PPT01 | Vortex equilibrium $(p,q)$ knots; electron $(1,1)$, proton $(2,3)$ | RESOLVED |
| FLM02/FLM05 | Granular pulse mechanics → $F=ma$, Newton I–III | RESOLVED (with IDENTITY relabels on the $m\leftrightarrow V_{\text{disp}}$ rows) |
| GOM01/GOM02/GOM04 | Depth engine; k-hierarchy; koppa closure ($c$ from geometry) | RESOLVED (GOM01 re-audited 2026-07-03: CONVERGENCE; factor-4 claim PARTIAL) |
| NP01 | Atomicus nuclear grammar (the constitution) | RESOLVED/frozen |
| FLM08 | The vacuum = corner-sharing tetrahedral random network (ten methods converge) | RESOLVED 27/27, class [GEOMETRY] |
| APS03 | Universal drafting crossover (atomic+stellar+galactic on one curve) | PARTIAL (honest RMS 21.5%; galactic pilot VOID) |
| CR03 | Transfer-function closure (bottleneck for $f$) | EXECUTED — states the true open problem ($R_{\text{CMB}}/H_0$ underived) |
| **APS04/PPT08** | Lamb amplitude | **OPEN**; measured H and He⁺ intervals remain observed inputs |
| **PPT08A** | per-spation rolling coefficient | **OPEN**; the frozen-radius calculation does not derive it |
| **PPT09** | winding topology and stability | knot classification **COMPUTED**; W=2 energy direction, barrier, lifetime and W={1,3}-only stability **OPEN** |
| **CR05** | pressure tensor; candidate $H_0$ and $f$ closure route | H₀/f closure **EXCLUDED** by direct execution; pressure exponent and freeze-out mechanism **OPEN** |
| EMC02 | Elementary charge $e$ | **Class X (irreducible)** — the same quantity resurfaces as the PM suite's HG-1 handed-gain root; §G.3 re-open condition: the FLM14 rotation DOF |
| FLM06 | Spation-scale closure $\ell_P=\sqrt{\varkappa\lambda}$ (seed theorem) | EXECUTED (**negative** on $\ell_P$ + koppa win); Seed Theorem now premise-classed per §G.3 |
| GOM05 | Variable closure $\ell_P(r)$, the c-gradient, lumiostasis | EXECUTED (4/4) |
| GOM06 | Gravitational waves ("move the sea") + the two-channel/aberration re-audit | EXECUTED (C) |
| **FLM13** | ℏ = the W=1 circulation action (role); $\{\hbar,m_e,m_p\}\to$ one mass/action seat | **EXECUTED 2026-07-03 — NATIVE (role + collapse); VALUE OPEN per the Seed Theorem** |
| **FLM14** | Rotating spation, sequential occupancy (Born weighting = dwell time) | **Runs 1–3 executed** (Part 9.5): frustration 0.347 NATIVE; ladder killed through form-4; backbone percolates 85.5%; $p_{\text{occ}}$ Born-adjacent, UNCLAIMED; **run 4 in flight** |
| **GOM14** | Mass-free koppa-density, 693 multi-planet systems (Part 5.1) | **EXECUTED — Class C, earned** |
| **NP14 / NP22** | Neutron mass split; β-spectrum shape (Part 10.2) | NP14: sign/structure EARNED, magnitude OPEN (−23.3%) · NP22: FAIL→OPEN, **1-DOF release-measure class KILLED knob-proof** |
| **NP12** | Nuclear radius formula (Part 10.3) | canon $Z\cdot R_p$ **KILLED** vs 908 radii; zero-fit replacement ready — **canon decision pending Harvey** |
| QM02/03/04/07 · CM01–07 · PM01–07 · OP02–07 · CH02–07 | the 2026-07-04/05 strike-force wave | Part 16.2 (earns) and Part 18.5 (roots) |
| OP-1 / OP-2 / OP-3 | $(R/a)$ mass-spectrum quantisation; winding stability; $\alpha$ from geometry | **OPEN** — all three bottom out on the lattice solver (ROOT-SIM) |

---

## PART 18 — THE OPEN FRONTIER

- **PPT08A:** the per-contact lag is OPEN; the frozen-radius calculation does not derive it.
- **PPT09:** knot classification is computed; W=2 dynamics and W={1,3}-only stability are OPEN.
- **APS04/PPT08:** the Lamb amplitude is OPEN; measured intervals are observed inputs.
- **CR05:** H₀/f closure is EXCLUDED; $f$ remains Class E and $R_{\text{CMB}}/H_0$
  remains an observational dependency.

**Two category corrections — dissolved, not open (I earlier mislabelled both by carrying the standard-physics
frame).**

- **Charge.** **SDT has no charge primitive.** What QM calls charge is *occluded influx directionality* — the
  directional signature of the convergence inflow a vortex occludes — and the electrostatic force is occlusion
  geometry (Law III). The canonical derivation basis contains **$\alpha$, not $e$**, and $k_e e^2=\alpha\hbar c$ is the
  **definition** of $\alpha$ (Class F). EMC02's "cannot derive $e$" is not a missing derivation — it is the
  *expected signature of a QM abstraction*: the derivation basis has no current dimension $[\mathrm{A}]$ because the
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
1. **$P_{\text{eff}}$ — derivation basis-algebraic, but circularity unresolved.** CR03 shows
   $P_{\text{eff}}=m_p^2 m_e^2 c^5/(4\pi\alpha\hbar^3)$ — a pure derivation basis combination, *not* a free numerical
   fit. But EMC01's audit flags it may be the hydrogen force-balance rewritten in derivation basis clothing (force
   magnitude and $f$ being "the same equation twice"); `laws.hpp` keeps Class E conservatively. Not a free
   parameter; not yet a clean delete-test-passing derivation.
2. **$R_{\text{CMB}}/H_0$ is an observational input.** CR05 supplies no derived
   $H_0$; the Friedmann structure is not SDT-derived; the propagation law $d(z)$ is OPEN (Part 12).
   This is the real remaining cosmology contingency, and CR03 states it without decoration.
3. **The mass ratio's first-principles root.** $6\pi^5=1836.118$ is the shared packing count in the
   Law-IV point-electron closure-tube to proton-torus construction. The geometric map is resolved, but it is
   not an independent prediction of the count. The absolute W=1 point-body width and mass/action-seat value
   remain open.
4. **Quantum measurement compresses to one scalar law.** After the strike force (Part 15), the square, the
   floor, the barrier form and two-valuedness are machinery; what is *not yet mechanised* is exactly the
   residence law (landing counts ∝ energy density) — owner FLM14, acceptance test on file, run 4 in flight.
5. **GW radiative coefficients are convergence; the strong-field sector is open** (native $\Delta M/M$, wall
   reflectivity, the QNM spectrum of a max-compression vortex, a clean echo detection).
6. **Several investigations are framework/spec, not executed:** GD01 eclipse-saturation (no implementation —
   the galactic-rotation answer leans on GD05/APS03 instead), NP02/NP03 (stellar-growth + mirror-falsification
   specs), NP04B (3n→triton kinetics); and the nuclear binding chain (NP06 killed → NP10 lock OPEN) waits on
   the contact wall below.
7. **Everything is uncommitted.** The entire 2026-07-03/05 arc — canon repair included — lives in the working
   tree, pending Harvey's review and the two canon decisions (Part 10.3).

### 18.5 What is owed — the cascade ledger, and the one instrument it queues behind

The framework's audit keeps a **cascade ledger** (`INVESTIGATION_STACK.md` §3b): every KILL/OPEN names its
root; roots are logged once; *pay the root, clear the debts.* Read as a whole, the ledger's July state makes a
single striking statement — **essentially every open number in the framework now queues behind one
instrument**, the rotating-lattice solver (ROOT-SIM, with FLM14 as its premise program):

| Root (owed once) | The debts it clears when paid |
|---|---|
| **RESIDENCE-LAW** (which lattice seat a landing vortex takes; owner FLM14 rule-form-4) | Born (QM04's <1%-RMS acceptance test), Bell's $\cos^2(a-b)$ joint weighting (QM05), the double-slit landing fringe (QM01), tunnelling re-seeding (QM03), sequential spin $\cos^2(\theta/2)$ (QM07) — **five debts, one law**; plus chemistry's shell-seat map (CH03's O₂ kill) |
| **ROOT-CONTACT** (the short-range contact/lock wall) | the nuclear α lock (×6.35), CH02's 1:1-salt overshoot (NaCl +9.4%) and MgO, CH05's three-centre barrier, CH07's stiffness — with the **registered cross-check**: one derived wall must *simultaneously* give k(H₂) ≈ 575 N/m ∧ the NaCl +9.4% correction ∧ the α lock ×6.35. Pay once, four debts clear |
| **ROOT-B** (lock-depth / gear-engagement magnitude — THE FLM14 number) | superconductivity's $\eta=T_c/\theta_D$ (measured spread 24×), CM05's $T_\lambda$, SCT's barrier B ("SDT's G_F"), the NP17 lock — a per-material engagement number makes $T_c=\eta\,\theta_D$ a zero-fit prediction |
| **HG-1** (the handed bilinear gain ≡ EMC02's irreducible $e$) | PM01's absolute gain, Lenz's sign (PM02), Debye's restoring gain (PM04), synchrotron sense/gain (PM06), the swirl↔momentum conversion (PM07) — the named §G.3 re-open is the FLM14 rotation DOF |
| **NP22 exit-channel count** ($N_{\text{exit}}\propto E^2$, native 3-D state counting) | the β-spectrum shape; lineage = FLM14 sequential occupancy ("SDT must earn its spheres from seat geometry") |
| **ROOT-A** (action per relay event = h beyond vortex winding) | CM04's T³ grade-cap, CM01's lock ceiling, CM03's gap door, CM06's e²/h per channel |
| **WAKE-DISPERSION** (the one ℏ bridge: $v=(\kappa/2\pi)\nabla\phi$, $\Omega_m=mc^2/\hbar$) | upgrades QM01/QM02/QM03's lab-unit conversions in one payment |
| **OP-ROOT / ROOT-RIM / WEOS-1 / PM03-REBUILD** | the transverse relay rule (Fresnel pairing, obliquity), angular-window allocation (VSEPR residuals, multi-rim H-bonds), the wake equation of state ($\gamma_{\text{eff}}=4$ candidate), a validated EM-wave solver |
| **ROOT-SIM itself** (the lattice solver) | OP-1/2/3, FLM03 co-rotation, FLM09's ω(k) isotropy residual, PPT07's wake integral (the 6π⁵ mechanism), GD05's rotation-curve crossover, R1's occlusion transfer function — **six debts before FLM14 joined; its bond-local gearing and structured seat-tour make it the payer-candidate for everything above** |

This is what explicit provenance requires in practice: none of these numbers may be promoted without
its stated dependency class, so they remain in the ledger until a direct build earns them. The RESIDENCE-LAW's
five debts, ROOT-B's lock-depth, HG-1's charge closure, the exit-channel count and the contact wall (with its
three-way numeric cross-check) are the make-or-break queue of the rotating-lattice instrument. FLM14 run 4 is
the next entry in that story.

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
| **Pulse channel / constraint channel** | the two-channel split (Part 7A): deformation pulses relay at exactly $c$; the *rigidity* of a gear-locked cluster is shared structure, not a propagating signal, and is uncapped. |
| **Gear phase** | the locally-readable mechanical phase of a gear-locked cluster — SDT's shared-state variable, and the handle of the falsifiable fork with QM (Part 7A.4). |
| **Seat** | a lattice position an electron (or internal constituent) occupies on its tour; seats have depths (speeds) — the Lamb spacing is a seat-radius offset (Part 9.6), the neutron's surplus is a 1.83c seat (Part 10.2). |
| **Tour / dwell time** | the FLM14 premise: the "orbital" is a deterministic gear-stepped *sequence* of seats; the Born weighting is how long the tour dwells where (Part 9.5). |
| **Residence law** | the one open scalar law — landing counts ∝ wake energy density — into which Born, Bell, tunnelling re-seeding and sequential spin all compress (Part 18.5). |
| **Mass/action seat** | FLM13's collapsed $\{\hbar, m_e, m_p\}$: one irreducible anchor, physically a baryon count; its VALUE is the framework's one seeded number (Part 2.1). |
| **Shadow union** | the binding-energy bookkeeping: overlapping occlusion shadows are counted once ($\Delta A = \Sigma A - A_\cup$); *the meshing IS the mass defect* (Part 10.1). |

---

## CLOSING NOTE

Read this guide as the theory reads itself: **forward from the derivation basis — now compressed to four numbers and
a thermal seat — never backward from a target.** Where SDT *matches* GR and QM — redshift, precession,
deflection, the spectrum, the g-factor, the GW chirp, the Geiger–Nuttall line, the Madelung constant, the
London $-6$ — it does so as a **check passed, not an answer copied** (the delete-test is the proof). Where it
*departs* — no singularities, a local $c$ with a galactic floor, gravitational-wave echoes, memory ≡ breathing,
$\mu_\nu\equiv0$, the high-barrier tunnelling fork, the locally readable gear phase, the nuclear
$\alpha\!+\!d\!+\!t$ grammar — it stakes **falsifiable** claims. Where a route is excluded, the active text
states the negative result and the reopening condition. And where it is *not yet done* — the lattice root,
the calibrated force coefficient, the Lamb amplitude against its native target table, the one residence law
holding Born and Bell — it says so out loud, in a single cascade ledger that queues nearly all of it behind
one buildable instrument. That combination — one mechanism, explicit input provenance, an audit that tests its own
premises, and an unflinching ledger of its own gaps — is the whole of Spatial Displacement Theory and the
`sdt-engine`.

*(Guide last brought current: 2026-07-05, against the ⟐ banners of `INVESTIGATION_STACK.md`, the HUNTER/FARMER
protocol sheets, and the verdict files named throughout. — J. C. Harvey, Melbourne.)*
