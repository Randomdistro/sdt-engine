# Book III — Electromagnetism & Magnetism
### *De Rerum Todo Existens*, Book the Third: the handed redirection, and the charge that is not there

> **Author:** James Christopher Harvey, Melbourne. 2026.
> **Engine:** every number below is emitted by [`de_rerum.cpp`](de_rerum.cpp) (Book III section) and
> reproduced in [`de_rerum_results.txt`](de_rerum_results.txt). Class labels (A/B/C/F) are the
> engine's own certification, kept verbatim. See [README](README.md) for the class key.

---

## 0. Electromagnetism is a redirection, not a field

Standard physics opens electromagnetism with a *field*: a charge is a source, the field is the
mediator, and force is the field acting at a point. SDT keeps none of this. There is no field, there
is no charge-substance, and there is no source — the convergence that floods every boundary (Book I's
`I_∞`) is a **throughpole**: it passes *through* every point, in one boundary and out the opposite,
and never terminates in a sink or springs from a source. A terminating point would be a **monopole**,
and there are none of any kind.

What we call electromagnetism is then a single move applied to that one through-flow: a vortex
boundary, by its **handedness**, *redirects* the convergence — focusing it into a local surplus or
defocusing it into a local deficit. "Charge" is the name we give to that handedness. Light is a
*separate* channel: an **emission**, a propagating phase-impulse of the through-flow, not a steady
radial source. This book makes three reductions in series — *there is no charge*, *Coulomb is
occlusion*, *repulsion is the inverse of attraction* — and then states honestly which parts of
magnetism are native results and which are still measured inputs SDT has not yet earned.

The honesty contract of the treatise applies in full. The most-quoted electromagnetic line of all —
`k_e e² = αℏc` — is **true and matches CODATA, and is still flagged F**, because it is an identity and
not a derivation. That flag is kept in the open.

## 1. There is no charge (the `k_e e²` identity, honestly F)

**Claim.** Charge is not a substance, a primitive, or a property a particle "carries." What is
*called* charge **is** the handed redirection of the convergent throughpole; "+e" and "−e" are the
two **handednesses** — the proton's (2,3) trefoil versus the electron's (1,1) torus — not two amounts
of a stuff. The elementary charge `e` is an **SI unit-bridge**, the conversion factor between SDT's
redirection magnitude and the Coulomb number; saying "e is irreducible" means *e is a unit*, and you
do not *derive* a unit (EMC02).

**Mechanism.** Inspect what actually loads any electromagnetic force law. It is never `k_e` alone and
never `e` alone — it is always the **product** `k_e e²`. SDT reads that product, in framework terms,
as `αℏc`:

- `k_e e² = αℏc = 2.30708×10⁻²⁸ J·m`, and the engine checks this against CODATA `k_e·e²`:

| quantity | value | check | class |
|---|---|---|---|
| `k_e e² = αℏc` | 2.30708×10⁻²⁸ J·m | — | — |
| `k_e e²` (CODATA) | 2.30708×10⁻²⁸ J·m | matches to `rel = 6.14×10⁻¹⁰` | **F!** |

**Why this is F, not a victory.** The numbers match because the relation is an **identity**:
`α` is *defined* as `α ≡ k_e e²/(ℏc)`, so writing `k_e e² = αℏc` and "verifying" it against
`k_e·e²` is a tautology — it deletes to `α = α`. It is **not** a derivation of `α`; SDT does not
derive `α` and says so wherever `α` enters (the whitelist treats `α` as the hydrogen koppa-rung,
χ = c/v = 137.036, an input, not a coupling computed from charge). The engine labels this line **F**
and prints the disclaimer in `de_rerum.cpp` rather than dressing it up.

**The physics that survives the F.** Two facts pass the delete-test even though the identity does not:
(i) *only the product* `k_e e²` ever enters a force law — neither `k_e` nor `e` is separately
fundamental; (ii) because the load-bearing object is a single product (a coupling *magnitude*), there
is no need — and no room — for a charge *substance* behind it. The identity fails as a derivation but
*motivates* the elimination: there is nothing for a "charge" to be.

**Class: F** (un-earned identity, kept open). **Caveat:** the elimination of charge-as-substance is a
framework reading, not a measurement; what SDT still owes is the *magnitude* of the redirection from
geometry (see §3, the open frontier).

## 2. Coulomb is occlusion (the one force law)

**Claim.** The electrostatic force is not a distinct interaction. It is the **same occlusion law**
(Law III) that gives gravity and nuclear binding, evaluated at a charge-scale radius — one mechanism
at three scales.

**Mechanism.** Law III's universal force between two displacement boundaries is

$$ F = \frac{\pi}{4}\, P_{\text{eff}}\, \frac{R_1^2 R_2^2}{r^2}. $$

Each body occludes a solid angle of the convergence; the imbalance pushes. For the electromagnetic
case both interaction radii are the single **charge-interaction radius** — the geometric mean of the
proton and electron-wake radii, `R_charge = √(R_p · r_e)`, which is *why* e–e, p–p and e–p all share
one coupling strength rather than three. The law then reads
`F = (π/4) P_eff R_charge⁴ / r²`. Tested at the Bohr radius against the textbook Coulomb force:

| quantity | value | class |
|---|---|---|
| `R_charge = √(R_p · r_e)` | 1.539810×10⁻¹⁵ m | **B** |
| `F_occlusion(a₀)` vs textbook Coulomb | equal to `rel = 1.61×10⁻¹⁶` | **C** |

The two agree to the last representable digit. There is no separate "electrostatic constant" doing
work here: the same `P_eff` that binds the electron at the electropause (Book II) and the same `1/r²`
geometry that yields gravity (Book IV) reproduce Coulomb's law without a field and without a charge.

**Class: B** for `R_charge` (built from measured radii); **C** for the force identity (the `1/r²`
structure passes the delete-test on framework terms). **Caveat:** the *coefficient* `P_eff` is the
hinge — its provenance is treated in Book II (the electropause closure, EMC04), and the same
coefficient is what the open step of §3 would fully earn. The `1/r²` *structure* is native; the
*magnitude* rides on `P_eff`.

## 3. Repulsion is the inverse of the convergence (EMC03), and why there is no antigravity

**Claim.** Pure occlusion can only pull (any two boundaries shadow the convergence *between* them, so
the unoccluded outsides win and press them together). Yet like charges repel. SDT's resolution: **
repulsion is the inverse of the convergence** — attraction is a local throughput **deficit** (a
shadow / defocused redirection — through-flow turned *away* from the gap), repulsion is a local
**surplus** (a focused redirection — through-flow turned *into* the gap). One flow, read with opposite
handedness.

**Mechanism.** Model the net force as minus the gradient of the relay throughput a body sits in: it is
pushed *toward* a deficit and *away from* a surplus.

| throughput *between* two bodies | modulation | net force |
|---|---|---|
| **deficit** (shadow / defocused) | − | **attraction** (toward) |
| ambient | 0 | none |
| **surplus** (focused) | + | **repulsion** (apart) |

Because attraction and repulsion are then **one modulation read with ± sign**, their magnitudes are
forced to be equal for equal charge — `|F_repel| = |F_attract|` is not a coincidence to be checked but
a structural consequence. The engine states this as the construction principle (no separate number to
verify): both lobes are the same modulation, so the Coulomb magnitude is symmetric in sign by
construction.

**The throughpole correction — the fork resolved.** An earlier open question asked whether the surplus
lobe is a *literal outflow* (spations streaming out of the proton) or a *redirection* of the inflow.
The corrected ontology decides it: a literal point-outflow would be a **monopole**, and there are
none. The convergence is a throughpole, so a charge cannot be a pole either; and emission is already
spoken for (light). Therefore the surplus is **constructive redirection** — the (2,3) handedness
focuses the convergent through-flow into a directional surplus (read as one sign), the (1,1)
handedness defocuses it the other way (the other sign). Surplus and deficit are one through-flow,
handed — a redirection pattern, not a divergence.

**The payoff — why there is no antigravity.** This is the deepest asymmetry in physics, and SDT
explains it structurally rather than assuming it:

- **Gravity is the symmetric, subtractive occlusion (ℓ=0).** A body can only *block* the throughpole
  (cast a shadow); it can never *add* to it. The symmetric term is therefore **deficit-only** — no
  surplus is possible — so gravity attracts and *only* attracts. There is no antigravity because
  occlusion can shadow but cannot anti-shadow.
- **Charge is the handed redirection (ℓ=1).** It can *focus* or *defocus*, so it has both signs: like
  handedness focuses between the pair (surplus → repulsion), opposite handedness defocuses (deficit →
  attraction).

The same inverse-convergence is the proton repulsion a star's crushing size and electron screening
must defeat to fuse, and it is the dominant term over gravity (the dipole channel is ~10³⁹× the
monopole deficit), which is why like charges visibly fly apart while their underlying mutual
attraction goes unseen.

**Class: [STRUCTURAL, STRONG]** (grounded in the existing wake structure, named in throughpole terms).
**Caveat — the open frontier:** the *quantitative* derivation that the handed (ℓ=1) surplus carries
the **exact** Coulomb magnitude from the (1,1)/(2,3) vortex handedness is **OPEN**. At present the
magnitude still enters through `P_eff`, which is imported/flagged (EMC01, CR03). This is the
highest-value open step on the board: one derivation, two locks — earning the surplus magnitude would
*also* earn `P_eff` and close the EMC01 circularity. Falsifiable signature: the medium state between a
*like* pair (surplus) differs from an *unlike* pair (deficit) at equal separation — an SDT signal with
no standard-model counterpart.

## 4. The trefoil multipole and its selection rules (APS04)

**Claim.** The wake of a circulating vortex boundary has a structured angular spectrum. Its leading
terms fall off with distance as definite power laws, and the proton trefoil's three-fold symmetry
imposes a native selection rule on transitions.

**Mechanism.** Expanding the trefoil wake potential `Φ_ℓ(r) ~ r^{exponent}`, the engine carries three
exponents:

| term | physical reading | `Φ_ℓ(r) ~ r^?` | class |
|---|---|---|---|
| monopole, ℓ=0 | occlusion (Coulomb-like) | `r^{−1}` | **C** |
| quadrupole, ℓ=2 | rotational wake | `r^{−3}` | **C** |
| trefoil harmonic, ℓ=3 | three-fold circulation | `r^{−4}` | **C** |

The three-fold (C₃) symmetry of the (2,3) trefoil gives a **native azimuthal selection rule**: allowed
azimuthal numbers are `m₃ = 3k` (k ∈ ℤ), so spectral transitions obey `Δm₃ ∈ {0, ±3, ±6, …}`. The
same circulation structure underlies the engine's native Lamb-shift candidate (the ℓ=2 quadrupole
amplitude at `a₀`), `1051.8 MHz` vs measured `1057.845 MHz` (0.57%), carried in Book II's spectral
account.

**Honest language flag.** "Multipole", "quadrupole", and "Legendre" are **borrowed mathematical
language** — a coordinate decomposition imported from standard EM. What is **native** to SDT is the
**C₃ periodicity** (the selection rule `m₃ = 3k`, forced by the trefoil's three-fold geometry) and the
**power-law exponents** themselves. The ℓ-labels are bookkeeping for those native quantities, not
SDT primitives.

**Class: C** for the exponents and the selection rule (on framework terms). **Caveat:** the multipole
vocabulary is borrowed; the quadrupole *amplitude* (the Lamb-shift coefficient) still awaits numerical
lattice verification (flagged in the engine).

## 5. Magnetism: what is native, what is still a measured input (honest)

**Claim.** SDT has two genuine native results in magnetism and one honest debt. The natives:
**μ_alpha = 0** for the spin-0 alpha core, and **μ_ν ≡ 0** for the neutrino. The debt: the proton and
neutron magnetic moment *values* are **measured inputs SDT has not yet derived** — they are not
results.

**Mechanism.** A magnetic moment, in SDT, is the tilt of a boundary's internal circulation. Two cases
are forced to zero by topology, with no fit:

- **μ_alpha = 0 [NATIVE, C].** The alpha core is spin-0: its constituent circulations cancel, so there
  is no net circulation to tilt and the moment vanishes identically. This is a structural result, not
  an input.
- **μ_ν ≡ 0 [NATIVE].** The neutrino is an open winding (W=0) with no internal circulation; there is
  nothing to tilt, so its magnetic moment is identically zero — a native consequence of its topology
  (the standard model must *add* the smallness of μ_ν by hand).

The measured inputs, quoted honestly in their measured units:

| moment | value | status |
|---|---|---|
| `μ_proton` | 2.792847 μ_N | **measured input** (not yet derived) |
| `μ_neutron` | −1.913043 μ_N | **measured input** (not yet derived) |
| `μ_alpha` | 0 μ_N | **C** (native: spin-0, no circulation to tilt) |

**The borrowed-unit flag.** `μ_N` (the nuclear magneton) is an *imported* unit. The proton and neutron
moments appear here in `μ_N` **only because they are measured inputs quoted in their measured units** —
not because SDT expresses results in magnetons. SDT does not yet have a native yardstick or a native
derivation for these two values, and this book does not pretend otherwise: the trefoil-circulation
account that *would* derive `μ_proton`/`μ_neutron` from the (2,3) wake is unfinished. Quoting them in
`μ_N` is reporting a measurement, not claiming a closure.

**Class: C** for `μ_alpha` and the `μ_ν ≡ 0` topology result; **input** (no class) for
`μ_proton`/`μ_neutron`. **Caveat:** the proton/neutron moment derivation is the open magnetic frontier,
the ℓ=2 rotational rung of §4 — named, not waved away.

---

## Cross-references

- **Book I** — the eliminations of §5 there (no charge, no monopole, the throughpole) become the
  mechanism of this book: §1 (no charge) and §3 (the throughpole resolution) are those eliminations
  worked out in force.
- **Book II** — the coefficient `P_eff` that sets the Coulomb *magnitude* in §2 is the electropause
  closure (EMC04): the electron held at `a₀` by the centripetal=occlusion balance. The Lamb-shift
  candidate of §4 is carried in Book II's spectral account.
- **Book IV** — gravity is the **symmetric, subtractive occlusion** (deficit-only) of §3: this is why
  gravity attracts only and there is no antigravity, and it is the same `1/r²` occlusion law (§2) read
  without handedness.
- `Engine/include/sdt/laws.hpp` — `coulomb_identity` (the F identity), `law_III` (`R_charge`,
  `F_occlusion`, `F_coulomb`), `law_VI::angular` (multipole exponents, `m₃ = 3k`), `measured`
  (`mu_P`, `mu_N`, `mu_alpha`).
- `Investigations/03_Electromagnetism_and_Charge/CQ47_Repulsion_Inverse_Convergence/` — the full §3
  argument and honest ledger.

## Regenerate

```bash
cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include /Fe:de_rerum.exe \
   Papers\De_Rerum_Todo_Existens\de_rerum.cpp && de_rerum.exe   # see BOOK III section
```

*Spatial Displacement Theory · De Rerum Todo Existens · Book III · J. C. Harvey, Melbourne.*
