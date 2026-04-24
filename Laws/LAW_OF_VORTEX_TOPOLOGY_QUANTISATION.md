# LAW OF VORTEX TOPOLOGY QUANTISATION

## Formal Full-Form Statement

**Law (Vortex Topology Quantisation).**
Matter in the spation lattice exists only as persistent displacement vortices. A persistent vortex is a closed circulation of lattice deformation that recycles its own Movement Budget within a fixed topological class. Persistence requires the vortex's independent *dynamical* degrees of freedom — the orthogonal channels available to redistribute its budget without translation — to collectively saturate the marginal traction condition $P_{\mathrm{cf}} \geq P_{\mathrm{conv}}/3$ without exceeding the Movement Budget.

The relevant topological object is not the bounding 2-surface alone but the **solid torus** $D^2 \times S^1$ — the filled handlebody the circulation actually occupies. The solid torus carries exactly three independent persistent circulation degrees of freedom: toroidal flow along $S^1$, poloidal flow around the meridian disk $\partial D^2$, and a meridian-flux / central-aperture mode threading $D^2$ itself. The solid ball ($B^3$, genus 0) carries zero persistent circulation degrees of freedom and collapses. Higher-genus handlebodies carry more, but allocate strictly less budget per DoF, dropping each below the marginal threshold. The solid torus is therefore the unique compact region of $\mathbb{R}^3$ whose dynamical DoF count exactly saturates the marginal traction condition.

Within the genus-1 class, two further quantisations apply. First, the winding number $W$ — the number of times the toroidal thread closes on itself before returning to phase — is restricted to the set of values for which a topology-preserving decay channel does not exist. Under nearest-neighbour reconnection dynamics, this set contains only $W=1$ (the unknot) and $W=3$ (the trefoil, the simplest non-trivial knot). Second, the modal-coupling coefficient

$$\mathcal{C}_{TP} = \frac{a}{R}$$

controls how the persistence budget is shared between the three DoFs. Self-consistent mode-locked equilibria exist only at a discrete set of aspect ratios $(R/a)_i$ at which all three DoFs simultaneously satisfy the persistence constraint and the traction identity $\tau = 1/3$.

Let $W \in \{1,3\}$ be the admitted winding and $(R/a)_i$ a mode-locked aspect ratio. Then the wake radius of the vortex obeys, for $W=3$ (the trefoil-scale wake verified below),

$$\boxed{R_{\mathrm{wake}} = \frac{(W+1)\,\hbar}{m c}}$$

the exclusion volume obeys

$$\boxed{V_{\mathrm{disp}} = \mathcal{V}\!\left(W,\,\tfrac{R}{a}\right)\,\ell_P^3}$$

where $\mathcal{V}$ is a dimensionless topological volume functional, and the rest mass is fixed by the Inertial Mass Law:

$$\boxed{m = \frac{\Phi\,V_{\mathrm{disp}}}{3\,\ell_P^3\,c^2}}$$

A vortex is a stable particle if and only if $(W, R/a)$ lies in the intersection of the admitted winding set and the mode-locked aspect-ratio set. The stable particle catalogue is therefore not a list of distinct entities — it is a list of points on a discrete lattice in topology-geometry space.

---

## Expanded Form

### 1. Matter as Persistent Circulation

The Inertial Mass Law establishes that matter is a region of the spation lattice where ordinary straight-line relay is blocked. The Movement Budget Law establishes that every lattice element participates at total speed $c$, split between translation and circulation:

$$v_{\mathrm{circ}}^2 + v^2 = c^2$$

A displacement that does not circulate cannot persist. Isotropic relay from the $4\pi$ convergence domain would drive the exclusion volume to zero in one Planck tick. For a displacement to persist, the throughput its exclusion occludes must be carried instead by circulation *within* the displaced region. The circulation closes the relay locally — at the cost of committing velocity to internal modes rather than to translation.

The persistence question is therefore purely geometric: *which compact handlebodies admit closed circulation that self-consistently balances the occluded throughput on the number of dynamical DoFs they carry?*

---

### 2. Topology Selection — The Solid Torus is Unique

The relevant object is not the bounding 2-surface but the **solid handlebody** the circulation occupies. A persistent vortex in 3-space is a closed displacement with interior, not a sheet. The mode count that matters for persistence is the number of independent dynamical degrees of freedom the interior region supports — that is, the number of orthogonal channels across which the Movement Budget can be distributed while the configuration recycles.

For the solid handlebody of genus $g$, the persistent circulation DoFs are:

- One long-axis flow per non-separating tunnel ($g$ of these — toroidal-type).
- One meridional loop per tunnel ($g$ of these — poloidal-type, around the tube wall).
- One aperture-flux mode per tunnel ($g$ of these — flux threading the meridian disk $D^2$).

The first two classes correspond to the surface homology $H_1(\partial) = \mathbb{Z}^{2g}$; the third arises from the relative cycles of the solid handlebody $D^2 \times S^1$ itself, which are invisible to the surface-only count but physically distinct (the meridian-flux mode is a volume circulation, not a surface circulation). The total count for the solid handlebody is $n = 3g$.

Let the centrifugal pressure a mode sustains at speed $v$ be $P_{\mathrm{cf}} = \rho_{\mathrm{eff}}\,v^2$. The marginal traction condition — derived independently from the isotropic convergence stress tensor in Law III / Closure Derivation §1 — sets $P_{\mathrm{cf}} = P_{\mathrm{conv}}/3$. Writing the Movement Budget as the total persistence budget $B = c^2$ available to redistribute across the $n$ DoFs at rest ($v_t = 0$), the average budget per DoF is $B/n$. A mode sustains the marginal load when its share of $B$ reaches the traction fraction; the whole configuration persists when the sum across all DoFs exactly balances the convergence load without exceeding $B$.

| Genus $g$ | Handlebody | DoFs $n = 3g$ | Average budget per DoF | Persistence |
|-----------|------------|---------------|-------------------------|-------------|
| 0 | $B^3$ (solid ball) | 0 | — | ✗ no circulation; immediate collapse |
| **1** | **$D^2 \times S^1$ (solid torus)** | **3** (toroidal, poloidal, aperture-flux) | **$c^2/3$** | **✓ saturates marginal traction** |
| 2 | genus-2 handlebody | 6 | $c^2/6$ | ✗ below marginal; cannot resist convergence |
| $g \geq 2$ | — | $3g$ | $c^2/(3g)$ | ✗ strictly worse with increasing $g$ |

**Why the solid torus, not the surface torus.** The surface torus alone has only $2$ homology cycles ($H_1 = \mathbb{Z}^2$) and would not close the argument. The third DoF — the meridian-flux / aperture mode — lives on the solid torus's meridian disk and carries circulation threading the aperture rather than flowing along the surface. This is a *dynamical* degree of freedom specific to the circulation problem on the filled handlebody, not a topological cycle of the bounding surface. The SDT persistence argument is a statement about solid-torus dynamics, and the fact that exactly this handlebody yields $n = 3$ at the marginal threshold is the content of the selection.

**Conclusion.** The solid torus is the unique compact region of $\mathbb{R}^3$ for which the dynamical DoF count saturates — without exceeding — the marginal traction threshold. Lower genus has too few DoFs; higher genus has more DoFs competing for the same total budget, dropping each below threshold. Matter is solid-torus-shaped by selection on a budget-counting argument, not by postulate.

---

### 3. Winding Quantisation — The Reconnection Filter

Within the genus-1 class, the toroidal cycle can close on itself after $W$ transits before returning to its starting phase. $W$ is the winding number. Its geometric invariant is the integer number of self-crossings in a generic projection.

The admitted winding set is determined by lattice-level reconnection dynamics, not by energetics. At the Planck scale, nearest-neighbour reconnection is a zero-cost local move: two threads that cross can exchange partners. Any configuration reachable from another by a sequence of such moves is dynamically equivalent.

$W = 1$ — the unknot. A simple ring. Not reducible — there is nothing to reconnect to. **Stable.**

$W = 2$ — the $(2,2)$ torus link, equivalently the Hopf link. Two linked rings. Reconnection at either crossing decomposes the link into two independent $W=1$ rings plus the binding energy released. **Unstable** — decays to $2 \times (W=1)$ + energy, on a reconnection timescale $\sim 1/c$.

$W = 3$ — the $(2,3)$ torus knot, the trefoil. The simplest non-trivial knot. Knot-theoretically irreducible: no sequence of reconnection moves converts a trefoil into unknots without passing through a non-embedded intermediate, which the lattice forbids (no two threads can occupy the same spation at the same tick). **Stable** — the knot is the reason.

$W = 4$ — $(2,4)$ torus link, reduces as $W=2$. Unstable.

$W = 5$ — $(2,5)$ torus knot (cinquefoil). Knot-theoretically distinct from the trefoil. Dynamically stable against reconnection. **Kinematically inaccessible** under SDT lattice conditions: the formation pathway requires simultaneous five-strand convergence of correctly phased threads, which has vanishing measure at the convergence pressures available post-Clearing. Present in principle; absent in practice. Reserved as an open branch.

**Admitted winding set under SDT lattice reconnection:**

$$W \in \{1, 3\}$$

corresponding to the electron and proton. No free parameters. The "two stable elementary particles" empirical fact is the knot count.

---

### 4. Aspect-Ratio Mode-Locking

The solid torus is not fully specified by $W$. It also has a major radius $R$ and a minor radius $a$. The ratio $R/a$ — equivalently the modal-coupling coefficient $\mathcal{C}_{TP} = a/R$ — controls how the three DoFs exchange phase on curvature and therefore how the Movement Budget is distributed among them.

Persistence requires each of the three DoFs to self-consistently close its phase within the Planck tick while the vortex's centrifugal response matches the local convergence load. This is a constraint on the Jacobian of the coupled mode system — a set of three simultaneous closure conditions parameterised by $(R/a)$ and by the toroidal-thread helicity angle. Writing the closure conditions abstractly,

$$\mathcal{F}_i\!\left(\tfrac{R}{a},\,\alpha_{\mathrm{helix}};\,W\right) = 0, \qquad i = 1, 2, 3$$

self-consistent equilibria occur at a discrete set of pairs $(R/a,\,\alpha_{\mathrm{helix}})_j$ where all three closure conditions hold simultaneously.

This is a nonlinear eigenvalue problem. It has a countable discrete solution set. Each solution is a **mode-locked equilibrium** — a stable particle configuration. Between solutions, the mode exchange runs, no steady circulation holds, and no persistent vortex forms.

Note on the interpretation of the mode velocities. The velocities that appear in mode-locking are *not* three orthogonal velocity components of a single volume element evaluated at one radius. They are characteristic speeds of the three DoFs as seen in the vortex body frame — e.g., the Kepler-track speeds the lattice medium runs at its characteristic circulation radii, not vector components at a common point. The Movement Budget appears as a constraint on the *total* circulation content across the three DoFs; its decomposition across the DoFs is a function of the aspect-ratio configuration, not an orthogonal-frame identity.

**Consequence.** Mass is not continuous. At fixed $W$, only the $(R/a)_j$ aspect ratios admit persistent vortices, and each produces a distinct exclusion volume $V_{\mathrm{disp}}$ and therefore a distinct rest mass by the Inertial Mass Law. The mass spectrum is the projected image of the $(R/a)_j$ lattice under the mass functional.

**Prediction.** Within the $W=1$ class, a minimum of three mode-locked aspect ratios must exist to match the observed charged lepton family (electron as ground state; muon and tau as excited mode-locked states of the same winding class). Within the $W=3$ class, at least two must exist to match the proton and its measured excited states. The enumeration is open.

**Status.** The enumeration of $(R/a)_j$ requires lattice simulation of the coupled mode equations. Analytical resolution is open (see Open Problem 1 in `Theory/03_Open_Problems.md`). The existence of a discrete spectrum is forced by the closure condition; the specific values are computational.

---

### 5. The W+1 Wake Radius (Trefoil Scale)

A persistent vortex perturbs the surrounding relay out to a radius at which the perturbation amplitude decays to the background level. This is the **wake radius** $R_{\mathrm{wake}}$ — the scale at which the vortex ends and bulk lattice resumes.

The wake is not the exclusion volume. The exclusion volume is the region from which the vortex has displaced the medium. The wake is the region in which the medium's relay pattern has been measurably reorganised by the presence of the displacement. Typically $R_{\mathrm{wake}} \gg R_{\mathrm{excl}}$.

**The W+1 conjecture (trefoil, $W=3$).** For a trefoil-wound genus-1 vortex of rest mass $m$, the wake radius is

$$R_{\mathrm{wake}} = (W+1)\,\frac{\hbar}{m c}$$

The heuristic: the wake must close $W$ toroidal circuits plus one poloidal closure for phase consistency. Each closure contributes one unit of $\hbar/(mc)$ — one reduced Compton wavelength — to the radial extent. Total extent: $(W+1)$ reduced Compton wavelengths.

**Proton ($W = 3$):**

$$R_p = \frac{4\hbar}{m_p c} = 0.84124\ \mathrm{fm}$$

Measured charge radius (muonic hydrogen, 2019): $0.8414 \pm 0.0019$ fm. **Agreement: 0.02%.**

**Inverse form and falsification.** Writing

$$W_{\mathrm{eff}} = \frac{R_p\,m_p\,c}{\hbar} - 1$$

the conjecture predicts $W_{\mathrm{eff}} = 3$ (integer). The measured value is $W_{\mathrm{eff}} = 3.0008$. Future precision $R_p$ measurements that place $W_{\mathrm{eff}}$ more than $n\sigma$ from integer 3 falsify the trefoil-scale quantisation (branch test — falsifies $(W+1)$, not the Law itself; the Law would then require a revised radial functional).

**The electron wake is a separate structural quantity.** The classical electron radius

$$r_e = \alpha\,\frac{\hbar}{m_e c} = 2.8179\,\mathrm{fm}$$

is *not* a direct measurement of the electron's lattice wake. In SDT, $r_e$ is identified with the **Kepler c-boundary of the atom** — the radius at which the atomic orbital speed equals $c$ under the bridge law $\beth = R/k^2$ (with hydrogen $k = 1/\alpha$, $R = a_0$, giving $\beth_H = \alpha^2 a_0 = r_e$). It is a property of the electron-proton two-body configuration, not of the electron alone. Its appearance in Thomson scattering, the classical electron radius, and the electron's apparent "size" in atomic physics reflects the *atom's* geometric cutoff, not the electron wake.

The electron's own wake radius — the scale at which its solid-torus $W=1$ displacement ceases to perturb the relay — is a separate quantity to be derived from the $(W=1)$ aspect-ratio equilibrium $(R/a)_e$ via the exclusion-volume functional. It is not claimed to equal $r_e$, nor to obey the $(W+1)$ form. Its derivation is open (see Open Problem 3).

The $(W+1)$ rule is therefore stated here as specific to the trefoil ($W=3$), where it is verified. Its extension to $W=1$ is not asserted by this Law.

---

### 6. Mass and Charge from Topology

With $W$ quantised by reconnection and $(R/a)$ quantised by mode-locking, the persistent properties of the vortex that the Law directly fixes are:

**Mass.** From the Inertial Mass Law,

$$m = \frac{\Phi\,V_{\mathrm{disp}}(W, R/a)}{3\,\ell_P^3\,c^2}$$

No free parameter. The proton and electron rest masses are the ground-state evaluations at $(W, R/a) = (3, (R/a)_{p,0})$ and $(1, (R/a)_{e,0})$ respectively; the muon and tau are predicted as additional $W=1$ mode-locked states at excited aspect ratios $(R/a)_{e,1}$, $(R/a)_{e,2}$.

**Charge.** By the charge quantisation identity (Theorem T8),

$$R_{\mathrm{charge}} = \sqrt{R_p\,r_e}$$

is the geometric mean of the proton wake radius and the atomic Kepler c-boundary. The Coulomb coupling is the product

$$k_e e^2 = \alpha\hbar c$$

fixed by the lattice identity (Theorem T9). Electric charge is the ℓ=1 multipole of the wake expansion (see §8); magnetic moment is the ℓ=2 multipole; higher multipoles describe nuclear structure. Under this Law every interaction strength that appears in the Standard Model as a coupling constant is a wake-multipole overlap integral between two topologies — but the residual dimensionless inputs $\alpha$ and $m_p/m_e$ remain framework inputs at present (Open Problems 3 and 4).

**Spin, magnetic moments, and $g$-factors.** The wake-multipole expansion provides the structural framing: ℓ=2 asymmetry of the trefoil is the origin of the proton's anomalous $g$, and the near-symmetric $W=1$ unknot is the structural reason the electron $g_e \approx 2$. Numerical values — the spin-1/2 assignment for both stable windings, the measured $g_p = 5.586$, and the electron anomaly $a_e = (g_e - 2)/2$ — are not derived within this Law. They are **open problems** carried by the Law's framing, not results of it. Attempting to derive them here would require specific circulation-mode calculations on the mode-locked aspect-ratio equilibria of §4, which are themselves open.

---

### 7. The Particle Catalogue is a Lattice, Not a List

The Standard Model lists particles. SDT generates them as points on a two-dimensional discrete lattice in $(W, R/a)$ space, restricted by the reconnection filter to $W \in \{1, 3\}$ and by the mode-locking filter to the discrete spectrum $(R/a)_j$.

| $W$ | Character | Ground state | Excited states (predicted) |
|-----|-----------|--------------|----------------------------|
| 1 | Unknot, simplest | Electron | Muon, tau (additional $(R/a)_{e,j}$ mode-locked equilibria of the same winding) |
| 3 | Trefoil, simplest knot | Proton | Proton excited states and nucleon resonances ($(R/a)_{p,j}$) |
| 5 | Cinquefoil, second knot | — | Reserved (knot-theoretically distinct; kinematically inaccessible post-Clearing) |
| 2, 4, 6, ... | Torus links (reducible) | — | **Forbidden** — decay to unknots by single-reconnection moves |

**The charged lepton family is a feature.** The muon and tau are not anomalies for this Law — they are *predictions*. Given that $W=1$ mode-locking is a discrete eigenvalue problem, a spectrum is expected; three observed charged leptons are consistent with (and required by) the existence of at least three $W=1$ mode-locked aspect ratios. The mass ratios $m_\mu/m_e \approx 207$ and $m_\tau/m_e \approx 3477$ are predicted to emerge from the exclusion-volume ratios of the excited equilibria to the ground state. Enumeration is open.

**The neutron is a $W=3$ variant, not a composite.** The neutron is not an additional elementary topology; it is the trefoil carrying an additional trapped poloidal circulation layer — a $(W=3)$ solid torus whose poloidal mode sustains an extra wind beyond the proton ground state. Equivalently: the neutron occupies a distinct $(R/a)_{p,j}$ on the $W=3$ mode-locked spectrum. Its lifetime (${\sim 880}$ s as a free particle) is the reconnection timescale for the outer winding layer to unwind back to the proton ground state. The decomposition $n \to p + e^- + \bar{\nu}_e$ is the topological statement that the outer winding unwinds, releasing one $W=1$ unknot (electron) and filing an open-winding receipt (antineutrino). No reference to constituent quarks is required — neither as literal entities nor as equivalents.

**Neutrino.** An open winding — a topology that never closes. Since it does not close, it has no exclusion volume, no rest mass in the strict lattice sense, no toroidal circulation and therefore no ℓ=2 multipole, and therefore no magnetic moment. Neutrinos propagate at $c$ and participate in no force mediated by wake overlap — exactly matching observation.

**Photon.** The boundary case of the Movement Budget: $v_{\mathrm{circ}} = 0$, $v_t = c$. No circulation means no topology means no rest mass (Theorem T15). A photon is a transverse deformation of the lattice travelling at $c$ — a wake disturbance, not a vortex.

---

### 8. Wake Multipole Structure

The vortex wake, expanded in spherical harmonics at distance $r \gg R_{\mathrm{wake}}$, carries:

| $\ell$ | Multipole | Physical role | Scaling |
|--------|-----------|---------------|---------|
| 0 | Monopole | Isotropic background ($N\varepsilon$) | none — no force |
| 1 | Dipole (vector) | **Electric** charge interaction | $\propto 1/r^2$ (Coulomb) |
| 2 | Quadrupole (traceless symmetric) | **Magnetic** dipole moment | $\propto 1/r^3$ |
| ≥3 | Higher | Nuclear form factors, hyperfine structure | $\propto 1/r^{\ell+1}$ |

Two topologies interact through the overlap integral of their wakes. The ℓ=0 terms cancel isotropically (giving convergent boundary pressure, not net force). The ℓ=1 overlap gives Coulomb. The ℓ=2 overlap gives magnetic dipole-dipole. Higher multipoles are the nuclear form factors that distinguish, for example, the $W=3$ trefoil proton from a hypothetical $W=3$ configuration of differing aspect ratio.

**Prediction.** A topology without toroidal circulation ($v_T = 0$) has no ℓ=2 multipole, hence no magnetic moment. The SDT neutrino — an open winding — satisfies $v_T = 0$ and is predicted to have $\mu_\nu \equiv 0$ (not merely small; zero by topology). This is a sharp prediction distinguishing SDT from Standard Model extensions that predict $\mu_\nu$ at the level of $10^{-19}$ Bohr magnetons. Measurements below the SM floor — if found — confirm SDT and falsify SM extensions. Measurements above $\mu_\nu = 0$ by any finite amount falsify SDT Law VI as stated here.

---

## Canonical Wording for Paper Use

**Law of Vortex Topology Quantisation.**
Matter is a persistent circulating displacement of the spation lattice. Persistence under convergent boundary pressure requires the circulation to recycle its own Movement Budget within a compact handlebody whose dynamical degree-of-freedom count exactly saturates the marginal traction condition. The unique such region of $\mathbb{R}^3$ is the solid torus $D^2 \times S^1$, whose three persistent circulation degrees of freedom — toroidal flow, poloidal flow, and meridian aperture-flux — each carry an average of $c^2/3$ of the persistence budget. Within this class, the toroidal winding number $W$ is filtered by nearest-neighbour reconnection dynamics to the irreducible knot set $W \in \{1, 3\}$, corresponding to the electron and proton. The aspect ratio $R/a$ is further quantised by mode-locking at a discrete set of self-consistent equilibria; the charged lepton family ($e, \mu, \tau$) is the $W=1$ spectrum, and the proton's excited states are the $W=3$ spectrum. The trefoil-scale wake radius obeys $R_{\mathrm{wake}} = 4\hbar/(m_p c) = 0.84124$ fm in agreement with muonic hydrogen to 0.02%. Coupling strengths reduce to wake multipole overlap integrals between topologies. The residual dimensionless ratios $\alpha$ and $m_p/m_e$ remain irreducible inputs in the current framework; their derivation from the $(W, R/a)$ equilibria is an acknowledged open problem.

---

## Compact Theorem Form

**Theorem (Topology Selection).**
A persistent closed circulation in a three-dimensional nearest-neighbour relay lattice occupies a compact handlebody whose persistent dynamical DoF count $n = 3g$ satisfies $n \cdot P_{\mathrm{cf},\mathrm{per\,DoF}} = P_{\mathrm{conv}}$ at the marginal traction point. The unique solution is the solid torus ($g = 1$, $n = 3$: toroidal, poloidal, and meridian aperture-flux).

**Theorem (Winding Quantisation).**
Under nearest-neighbour reconnection dynamics, the admitted winding set on the solid torus is $\{W \in \mathbb{Z}^+ : W \text{ is an irreducible knot and } W \leq W_{\mathrm{kin}}\}$. Under SDT post-Clearing lattice formation conditions $W_{\mathrm{kin}} = 3$, giving the admitted set $\{1, 3\}$.

**Theorem (Mode-Locking).**
The coupled persistence constraints on the three solid-torus DoFs admit simultaneous self-consistent solutions only at a discrete set of aspect ratios $(R/a)_j$. Each solution is a stable particle configuration; between solutions, no persistent vortex exists.

**Conjecture (Trefoil Wake Radius, $W=3$).**
For a trefoil-wound lattice vortex of rest mass $m$, the wake radius is $R_{\mathrm{wake}} = (W+1)\hbar/(mc) = 4\hbar/(mc)$. Verified for the proton to 0.02%. Extension to $W=1$ is not asserted; the electron's wake is an independent structural quantity distinct from the classical electron radius (which is the atomic Kepler c-boundary).

**Corollary (Neutrino Triviality).**
An open (non-closing) winding has no toroidal circulation, no ℓ=2 wake multipole, and therefore no magnetic moment. $\mu_\nu \equiv 0$ is a topological identity, not a limit.

---

## The Seven-Step Mechanism

1. The Movement Budget Law requires every lattice element to participate at total speed $c$.
2. A persistent displacement must recycle its occluded throughput as internal circulation, or be erased within one Planck tick.
3. Closed circulation in a compact handlebody of genus $g$ supports $n = 3g$ persistent dynamical degrees of freedom (toroidal + poloidal + aperture-flux, per tunnel); average budget per DoF is $c^2/n$.
4. Marginal traction ($\tau = 1/3$) requires $c^2/n \geq c^2/3$, which is saturated only at $g = 1$ — the solid torus.
5. On the solid torus, toroidal winding $W$ is fixed by which configurations survive nearest-neighbour reconnection — only the unknot ($W=1$) and the trefoil ($W=3$) are both knot-theoretically irreducible and kinematically accessible post-Clearing.
6. Aspect ratio $R/a$ is fixed by simultaneous phase-closure of all three DoFs — a discrete eigenvalue problem yielding the mass spectrum.
7. The rest mass follows deterministically from $(W, R/a)$ via the Inertial Mass Law; the Coulomb coupling follows from the Identity theorem; the wake multipole expansion sets the structural form of every interaction. Specific derivations of $\alpha$, $m_p/m_e$, spin, and $g$-factors remain open.

---

## Derivation Status

**Class:**
- DERIVED for topology selection (solid torus is the unique saturating handlebody).
- DERIVED for winding filter (reconnection-dynamics argument, admitted set $\{1,3\}$).
- COMPUTED for mode-locking (existence of discrete spectrum; enumeration pending lattice simulation).
- CONJECTURED for trefoil-scale $(W+1)$ wake radius (verified for the proton to 0.02%).
- OPEN for the electron wake, spin assignments, $g$-factors, $\alpha$, and $m_p/m_e$.

**Measured inputs:** $\hbar$, $m_p$, $m_e$, $c$ (all CODATA). No fitting parameters.

**Framework inputs still treated as irreducible:** $\alpha$ and $m_p/m_e$. These appear in the `sdt::laws::measured` whitelist and are conjectured to emerge from the $(W, R/a)$ equilibria, but are not derived by this Law.

**What this law replaces:**
- The Standard Model particle catalogue (replaced by the $(W, R/a)$ lattice; the charged lepton family becomes the $W=1$ mode-locked spectrum).
- The quark hypothesis (replaced by $W=3$ trefoil single-particle topology; nucleons are distinct $(R/a)_j$ on the $W=3$ spectrum).
- The mass hierarchy as a set of Yukawa couplings (replaced by exclusion-volume ratios across the $(R/a)_j$ spectrum).
- The "why exactly two stable charged particles" puzzle (replaced by the knot count on admissible windings).
- Neutrino masses as beyond-SM parameters (replaced by open-winding identity $\mu_\nu = 0$).

**Structural claims the Law makes but does not compute (flagged for the referee):**
- The ℓ=2 multipole asymmetry of the trefoil is structurally responsible for $g_p \neq 2$; numerical agreement with $g_p = 5.586$ is pending the mode-locked $(R/a)_{p,0}$ calculation.
- The near-symmetry of the unknot is structurally responsible for $g_e \approx 2$ with small lattice corrections; the anomaly $a_e$ is pending the same calculation for $(R/a)_{e,0}$.
- Spin-1/2 for both stable windings is asserted as a framework expectation, not derived here.

**Open problems carried forward (see `Theory/03_Open_Problems.md`):**
1. Explicit enumeration of the $(R/a)_j$ mode-locked spectrum — lattice simulation.
2. Derivation of $\alpha$ from the $W=1$ equilibrium geometry.
3. Derivation of the electron wake radius from the $(W=1, (R/a)_{e,0})$ equilibrium.
4. Derivation of $m_p/m_e \approx 1836.15$ from the ground-state exclusion volume ratio.
5. Derivation of spin-1/2 and the measured $g$-factors from the mode-locked equilibria.
6. Classification of higher-$W$ kinematic accessibility under varying lattice conditions (pre-Clearing topologies).

**Falsification tests:**
- Precision $R_p$ measurement deviating from $4\hbar/(m_p c)$ by more than the quoted experimental $\sigma$ falsifies the trefoil-scale $(W+1)$ conjecture (branch falsification; does not falsify the Law).
- Detection of a fourth charged lepton at a rest mass *not* reproducible as an additional $W=1$ mode-locked equilibrium (once the $(R/a)_j$ spectrum is enumerated) falsifies the mode-locking mechanism (Law-level falsification).
- Failure of enumerated $(R/a)_{e,j}$ ratios to reproduce $m_\mu/m_e$ and $m_\tau/m_e$ to within tolerance falsifies the claim that the charged lepton family is the $W=1$ spectrum (Law-level falsification).
- Measurement of a finite neutrino magnetic moment falsifies the open-winding triviality corollary (Law-level falsification).

**Engine reference:** `Engine/include/sdt/laws.hpp` :: `namespace winding` encodes $W_{\mathrm{proton}} = 3$, $W_{\mathrm{electron}} = 1$, the predicted $R_p$, and the inverse $W_{\mathrm{eff}}$ falsification test. `Theory/01_Closure_Derivations.md` §4 encodes the topology-selection table. `Theory/03_Open_Problems.md` enumerates the computational gaps.

---

## The Key Sentence

> The two stable elementary particles of ordinary matter are the two knot types the lattice permits — the unknot and the trefoil — enumerated not by a coupling-constant list but by a reconnection filter on a persistence-saturating genus.
