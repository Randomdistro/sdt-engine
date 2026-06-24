# FD08 — Derivation: Bernoulli as a Law-V Budget Partition

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Author**: James Christopher Tyndall, Melbourne
**Status**: EXECUTED (compiled + run, MSVC, double precision, exit 0)

> Inherits the §0 anti-creep protocol and rules R0–R5 of the FD spec. Standard-FD
> results (Bernoulli, Venturi, Pitot, compressible stagnation) are CONVERGENCE
> TARGETS to reproduce — never inputs to borrow.

---

## 0. Statement

Along an inviscid, steady streamline the spation lattice carries a fixed local
convergence-pressure **budget**. The Bernoulli invariant

$$ B(s) \;=\; \tfrac12\rho v^2 \;+\; P \;+\; \rho g z \;=\; \text{const} \qquad[\mathrm{Pa}]$$

is **not** an independent axiom. It is the *partition* of one conserved ledger
into a directed-transport draw $\tfrac12\rho v^2$ and an isotropic static draw
$P$ (plus the elevation head $\rho g z$). This is Law V — the movement budget
$v_\text{circ}^2 + v_\text{trans}^2 = c^2$ — read at the continuum scale.

---

## 1. Phase 1 — Streamline integration of the FD01 Euler balance

**Starting point (no energy theorem assumed).** The steady, inviscid limit of
the FD01 momentum balance (its Phase-4 Euler limit) is

$$\rho\,(\mathbf v\!\cdot\!\nabla)\mathbf v \;=\; -\nabla P + \rho\,\mathbf g .$$

Project onto the unit streamline tangent $\hat{\mathbf s}$ and use the steady
streamline identities

$$(\mathbf v\!\cdot\!\nabla)\mathbf v\cdot\hat{\mathbf s} = v\,\frac{dv}{ds},
\qquad \nabla P\cdot\hat{\mathbf s} = \frac{dP}{ds},
\qquad \mathbf g\cdot\hat{\mathbf s} = -g\,\frac{dz}{ds}.$$

This gives the scalar streamline equation

$$\rho\,v\,\frac{dv}{ds} \;+\; \frac{dP}{ds} \;+\; \rho g\,\frac{dz}{ds} \;=\; 0
\;\;\Longleftrightarrow\;\;
\frac{d}{ds}\!\left(\tfrac12\rho v^2 + P + \rho g z\right) = 0 .$$

Integrating along $s$ closes the invariant **exactly**, with *no surplus and no
missing term*:

$$\boxed{\;\tfrac12\rho v^2 + P + \rho g z = B = \text{const}\;}$$

**Numerical verification (tool, Phase 1).** Prescribing arbitrary smooth
$v(s)=3+2\sin(0.6s)$ and $z(s)=0.5s$, the tool integrates $dP/ds = -\rho v\,dv/ds
- \rho g\,dz/ds$ by midpoint rule ($N=1024$) and recovers $B(s)$ flat to a relative
residual of $2.4\times10^{-10}$ — pure $O(\Delta s^2)$ discretisation, no physical
drift. **Checkpoint C1: PASS.**

---

## 2. Phase 2 — The budget-partition identity & the forced sign (core gate)

Holding $B$ and the head $\rho g z$ fixed (one streamtube, constant elevation),
the static pressure is the *remainder* of the ledger after the directed share is
spent:

$$P(v) = B - \tfrac12\rho v^2 - \rho g z
\qquad\Longrightarrow\qquad
\boxed{\;\frac{dP}{dv} = -\rho v < 0\;}$$

The trade is **strictly negative**: faster flow can only buy its extra directed
share *out of* the isotropic static share. There is no suction and no attraction
— only re-allocation of a fixed throughput, cell-to-cell at relay speed $c$.

### Law-V ↔ Bernoulli bijection

| Law V (per cell) | Bernoulli (continuum streamtube) | Role |
|---|---|---|
| $c^2$ (total capacity) | $B/\rho$ (specific budget) | conserved ledger |
| $v_\text{trans}^2$ (directed) | $\tfrac12\rho v^2 / \rho = \tfrac12 v^2$ (directed head) | transport draw |
| $v_\text{circ}^2$ (internal/isotropic) | $P/\rho$ (static push) | isotropic draw |
| capped at $c^2$ | capped at $c_s$ then $c$ | hard ceiling |

Static $P$ is the *isotropic* share of the convergence push (Law I `P_conv`,
the CMB-relay influx); $\tfrac12\rho v^2$ is the *anisotropic* fraction committed
to transport (Law V). Their sum per streamtube is conserved.

**Numerical verification (tool, Phase 2).** At $v=50$ m/s, $\rho=1.225$:
analytic $dP/dv=-61.25$ Pa·(m/s)$^{-1}$ matches a central finite difference to
$1.9\times10^{-11}$. **Checkpoint C2 (core gate): PASS** — a positive sign would
have been an immediate Class F.

---

## 3. Phase 3 — Venturi and stagnation/Pitot, from the same invariant

### 3a. Venturi (continuity ⊕ Bernoulli)

Incompressible continuity (FD01) on a streamtube is $\rho A v = \text{const}$, so
$v_2 = v_1 A_1/A_2$. For a horizontal Venturi ($z$ constant, head drops out),
Bernoulli gives the throat drop directly:

$$\Delta P = P_1 - P_2 = \tfrac12\rho\,(v_2^2 - v_1^2)
= \tfrac12\rho v_1^2\!\left[\left(\tfrac{A_1}{A_2}\right)^2 - 1\right].$$

Worked example (air, $\rho=1.225$, $A_1=0.0100$ m², $A_2=0.0040$ m², $v_1=20$ m/s):
$v_2 = 50.0$ m/s, $\Delta P = 1286.25$ Pa, matching the closed form to 0.000.
Static pressure **falls** in the throat ($\Delta P>0\Rightarrow P_1>P_2$).
**Checkpoint C3a: PASS.**

### 3b. Stagnation / Pitot

Bring the parcel to rest ($v\to0$): the *whole* budget reverts to isotropic
static push. With $z$ constant,

$$\boxed{\;P_0 = P + \tfrac12\rho v^2\;}$$

— the stagnation (Pitot) reading is the entire ledger; the static $P$ is what
remains after the moving fraction $\tfrac12\rho v^2$ is spent on transport.
Worked example (air, $v_\infty=60$ m/s, $P=101325$ Pa): $q=2205$ Pa,
$P_0 = 103530$ Pa. The inverse (the actual Pitot use) recovers
$v=\sqrt{2(P_0-P)/\rho} = 60.000000$ m/s, a round-trip residual $<10^{-9}$.
**Checkpoint C3b: PASS.**

---

## 4. Phase 4 — The c-ceiling corner (compressible correction)

Incompressible Bernoulli is the **low-speed corner** of the same ceiling-capped
budget. The isentropic stagnation relation is

$$\frac{P_0}{P} = \left(1 + \frac{\gamma-1}{2}M^2\right)^{\gamma/(\gamma-1)},
\qquad M = \frac{v}{c_s}.$$

Expanding for small $M$ (using $\rho c_s^2 = \gamma P$, so
$\tfrac12\rho v^2/P = \tfrac{\gamma}{2}M^2$):

$$\frac{P_0}{P} = 1 + \frac{\gamma}{2}M^2 + O(M^4)
\;\;\Longleftrightarrow\;\;
P_0 = P + \tfrac12\rho v^2 + O(M^4),$$

which is exactly the incompressible stagnation relation of Phase 3b. The tool's
$M$-sweep shows the exact ratio agreeing with the incompressible tangent
$1+\tfrac\gamma2 M^2$ to $1.7\times10^{-5}$ at $M=0.1$, $1.3\times10^{-3}$ at
$M=0.3$, and the $M\to0$ ratio $[P_0/P-1]/[\tfrac\gamma2 M^2]\to0.99999999$.
The departure grows with $M$ (7.4% at $M=0.9$) — the expected compressible
correction, *not* a failure of the incompressible corner.

$\gamma=1.4$ is ledgered as the single **MEASURED-INPUT** (diatomic air).

**Law-V ceiling.** As $v_\text{trans}\to c$, Law V keeps the budget bounded:
at $v_\text{trans}=0.999c$ the engine `law_V::v_circ` returns a real, finite
$v_\text{circ}=1.34\times10^7$ m/s. The directed share can never exceed $c^2$;
the budget cannot run away. **Checkpoint C4: PASS.**

---

## 5. Phase 5 — 1-D streamtube two-stream check

Prescribe a smooth nozzle→throat→diffuser area $A(s)$ (throat $0.4\,A_\text{in}$),
solve continuity $\rho A v = \text{const}$ for $v(s)$, set
$P(s) = B - \tfrac12\rho v^2 - \rho g z$ from the budget, then reconstruct
$B(s)$. Over 64 stations the invariant is flat to **machine precision**
($\max|B(s)-B_0|/|B_0| = 0.0$). The pressure field $P(s)$ and stagnation $P_0$
are exportable to FD07 (lift) and FD09 (drag). **Checkpoint C5: PASS.**

---

## 6. The `ρgz` head from SDT gravity (no G, no M)

The elevation head is the work done against the SDT gravity field, computed
**only** from `bridge::g_surface(v_surface, R) = v²/R`:

$$g = \frac{v_\text{Earth}^2}{R_\text{Earth}} = \frac{(7909\ \mathrm{m/s})^2}{6.371\times10^6\ \mathrm{m}}
= 9.8183\ \mathrm{m\,s^{-2}}.$$

The only inputs are a measured surface velocity and a radius — **no mass, no $G$**.
There is no `GM/R²` path anywhere in the code (R0 guard: gravity is obtained
exactly once, via `bridge::g_surface`). In SDT-native yardsticks this head is the
depth term $\rho g z$ with $g$ a pure $v^2/R$ quantity (Law-bridge `koppa`).

---

## 7. Parameter ledger (R2)

| Symbol | Value | Tag | Source |
|---|---|---|---|
| streamline invariant $\tfrac12\rho v^2+P+\rho gz$ | — | **DERIVED** | FD01 Euler balance integrated on $\hat s$ |
| $dP/dv = -\rho v$ | — | **DERIVED** | budget partition (Law V continuum) |
| Venturi $\Delta P=\tfrac12\rho(v_2^2-v_1^2)$ | — | **DERIVED** | continuity ⊕ Bernoulli |
| Pitot $P_0=P+\tfrac12\rho v^2$ | — | **DERIVED** | $v\to0$ limit of the budget |
| $g = v_\text{Earth}^2/R_\text{Earth}$ | 9.8183 m/s² | **DERIVED** (SDT) | `bridge::g_surface`, no G/M |
| $c$ (Law-V ceiling) | 299 792 458 m/s | whitelist | `measured::c` |
| $\gamma$ (air) | 1.40 | **MEASURED-INPUT** | diatomic adiabatic index (compressible part only) |
| $\rho_\text{air}$ | 1.225 kg/m³ | stated scale, CALIBRATED(0) | not fitted; evaluation only |
| $c_s$ (air) | 340.3 m/s | stated scale (FD05 handshake) | not fitted |
| $A_1,A_2,v_1,v_\infty$ | as stated | evaluation inputs | not fitted |

No coefficient, integer, or $\pi$ was inserted to force a match (R5). Every
coefficient traces to Law V / continuity, or carries a MEASURED-INPUT tag.

---

## 8. Note on an engine fix made during execution

Compiling `<sdt/laws.hpp>` standalone exposed a pre-existing dangling reference
at `laws.hpp:1162`: `traction::traction_ratio_proton` referenced
`winding::W_proton`, but `winding` is nested inside `law_VI` (the `sdt::laws::winding`
alias is only declared later at line 1407). The reference was fully-qualified to
`law_VI::winding::W_proton`. **No numeric change** ($W_\text{proton}+1=4$, so
`traction_ratio_proton` is still 12); this only restores standalone compilation
of the single source of truth. All downstream parser errors (lines 1306+) were
fallout from this one desync and cleared with the fix.
