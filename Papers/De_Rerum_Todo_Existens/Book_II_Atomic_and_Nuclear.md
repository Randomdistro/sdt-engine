# Book II — Atomic & Nuclear Architecture
### *De Rerum Todo Existens*, Book the Second: the electropause, the rotation field, the trefoil, the alpha brick

> **Author:** James Christopher Harvey, Melbourne. 2026.
> **Engine:** every number below is emitted by [`de_rerum.cpp`](de_rerum.cpp) (Book II section) and
> reproduced in [`de_rerum_results.txt`](de_rerum_results.txt). Class labels (A/B/C/F) are the
> engine's own certification, kept verbatim. See [README](README.md) for the class key.

---

## 0. The atom is a pressure structure, not a probability cloud

The standard atom is a wavefunction: a smear of probability whose square tells you where an electron
*might* be found, bound to a nucleus by a Coulomb potential whose coupling `e` is a primitive charge.
SDT keeps none of this. There is no wavefunction, no field, no charge-as-substance, and no quark
inside the proton. What remains is the four primitives of Book I — matrix, boundary, movement, now —
and the one force law of Law III, the **occlusion** of the convergence:

$$ F = \frac{\pi}{4}\,P_{\text{eff}}\,\frac{R_1^2 R_2^2}{r^2}. $$

The atom is then a **mechanical pressure structure**. The nucleus is a dense displacement boundary; it
casts an occlusion shadow into the matrix; the electron is a `W=1` vortex held on a circulation track
at the radius where the inward occlusion gradient balances its outward circulation strength. That
balance radius has a name — the **electropause** — and for hydrogen it is the Bohr radius. Everything
in this book is read off that one picture: the binding (§1), the line spectrum (§2), the proton's
identity and stability (§3), its mass (§4), the grammar that stacks nuclei (§5), their sizes (§6), and
the one honest residual at the level of the fine structure (§7).

The single irreducible input is **α**, read throughout as the hydrogen **koppa-rung** `χ = c/v =
137.036` (Rule 7 of the Atomicus constitution; PPT02), *never* as `k_e e²/ℏc`. The model **does not
derive α**, and every section that leans on it says so.

## 1. The electropause: binding without charge (the P_eff closure)

**Claim.** What holds the electron at the Bohr radius is the **centripetal requirement**, and that
requirement *is* the occlusion push — computable from kinematics with no charge term anywhere. Inverting
the occlusion law for this balance then *derives* `P_eff`, closing the last open joint in the force law.

**Mechanism.** A heliopause is where the Sun's outward output balances the inward CMB convergence. An
**electropause** is the same boundary one rung down: the surface where the electron's outward
circulation balances the nucleus's inward occlusion gradient. The electron does not sit in a potential
well; it sits at a *pressure-balance radius*, exactly as the Oort cloud sits at lumiostasis (Book IV).
To hold a mass `mₑ` on a circle of radius `a₀` at the ground-state speed `v = αc` costs a centripetal
force `F = mₑ v²/a₀` — and no `e`, no `k_e`, ever appears. Invert `F = (π/4) P_eff R_charge⁴/a₀²` with
`R_charge = √(R_p r_e)` and `P_eff` falls out as **output, not input**:

| quantity | expression | value | class |
|---|---|---|---|
| ground-state speed | `v = αc` | 2.187691×10⁶ m/s | B |
| binding (kinematics) | `F = mₑ v²/a₀` | 8.23872×10⁻⁸ N | C, PASS |
| ↳ vs textbook Coulomb | `k_e e²/a₀²` | identical to `rel = 4.13×10⁻¹²` | C, PASS |
| ↳ vs engine occlusion | `law_III::F_coulomb(a₀)` | identical to `rel = 4.13×10⁻¹²` | C, PASS |
| inverted pressure | `4 F a₀² /(π R_charge⁴)` | 5.22521×10³¹ Pa ≡ engine `P_eff` | C, PASS |
| whitelist closed form | `m_p² mₑ² c⁵/(4π α ℏ³)` | 5.22725×10³¹ Pa (`rel = 3.91×10⁻⁴`) | C, PASS |

The closed form contains **only** `{m_e, m_p, c, α, ℏ}` — every one a whitelist input, with `k_e` and
`e` deleted. That is the delete-test, and it passes (to the 2×10⁻⁴ with which `R_p ≈ 4ℏ/(m_p c)`, the
W+1 conjecture of §3). The Bohr radius **is** the electropause, and the binding needs no charge — the
mechanical content of *"there is no charge"* (carried into Book III).

- **Class C** (DERIVED, on framework terms). This upgrades `P_eff` from class **E** (CALIBRATED, the
  state in `laws.hpp::law_III::P_eff`, which still reads `4 k_e e²/(π R_p² r_e²)`) to **C**, and cuts the
  EMC01 coefficient circularity that flagged `f = P_eff/P_conv` as "the same equation twice."
- **Caveat.** α is still the one input. A reader who *insists* `α ≡ k_e e²/ℏc` will call `a₀ =
  ℏ/(mₑcα)` Coulomb-smuggling and the loop unbroken. On SDT's terms (α = koppa-rung) it is broken — but
  the model does not derive α, and says so. The `R_p = 4ℏ/(m_p c)` identity used for the cleanest
  whitelist form is the W+1 *conjecture*, not a theorem.

## 2. Spectra from one rotation field (no wavefunction)

**Claim.** The hydrogen line spectrum follows from **one rotation field** of the spation medium about the
nucleus — no wavefunction, no quantised energy levels imported. The Rydberg constant is *forced* by
`{m_e, c, α, h}` before any spectrum is consulted.

**Mechanism.** The matrix circulates about the nucleus with velocity `v(r) = cα√(a₀/r)`. This is a
classical circulation field, not a probability amplitude; the **closed-circulation radii** (where the
flow phase-closes on itself) are the allowed states, and at those radii `v_n = αc/n` — the koppa ladder
of the atom. From the rotation field alone the Rydberg constant rebuilds, and the `zk² = 1` closure
(`z = (v/c)²`, `k = c/v`) holds exactly at the hydrogen rung:

| quantity | expression | value | class |
|---|---|---|---|
| Rydberg, rebuilt | `R∞ = mₑ c α²/(2h)` | 1.09737×10⁷ /m ≡ CODATA (`rel = 1.95×10⁻¹²`) | B, PASS |
| H-α line (n=3→2) | from `R∞`, reduced-mass corrected | 6.56470×10⁻⁷ m (`rel = 2.89×10⁻⁴` vs measured) | B, PASS |
| ladder closure | `z·k² = 1` at hydrogen rung | 1.00000 (`rel = 4.44×10⁻¹²`) | B, PASS |

- **Class B** (DERIVED; passes the delete-test). No spectroscopic value is fed in to fix `R∞`; the few-
  ppm residual on H-α is the next movement-budget term `z = (Zα)²`, logged as a remainder, not a fit.
- **Caveat.** α enters as the ground-state koppa-rung; this reproduces the spectrum, it does not derive
  α. The reduced-mass factor `μ/mₑ` is a classical two-body correction, not a QED term — and no QED is
  imported. Engine: `atomic::rotation_field_velocity`, `atomic::R_inf_derived`,
  `atomic::emission_wavelength_m`.

## 3. The proton as a trefoil knot (Law VI)

**Claim.** The proton is a `W=3` **trefoil knot** in the spation lattice — a `(2,3)` torus knot — and the
electron is a `W=1` **unknot**. Particle identity is winding number; the proton's topological protection
is why it does not decay.

**Mechanism.** Stable particles are persistent vortex topologies (Law VI, Theorem T18). A `(p,q)` mode
is a true knot iff `gcd(p,q)=1` and `min(p,q)≥2`; its Alexander polynomial `Δ(t) ≠ 1` is an invariant
that cannot change under continuous deformation. The `(2,3)` trefoil has `Δ = t⁻²−t⁻¹+1−t+t² ≠ 1`, so the
proton's winding **cannot jump** — it is topologically locked and cannot decay. The electron `(1,1)` is
an unknot (`Δ = 1`), not protected by topology but **confined by `V_disp`** (the displacement cost of
Book I). A `(1,2)` "W=2" is also an unknot, only metastable, and never observed. The W+1 radius
conjecture then fixes the proton's wake:

| quantity | expression | value | class |
|---|---|---|---|
| proton winding | trefoil `(2,3)` | `W = 3` | A |
| proton wake radius | `R_p = (W+1)ℏ/(m_p c)` | 8.41236×10⁻¹⁶ m (`rel = 1.95×10⁻⁴` vs muonic-H) | C |
| effective winding | `W_eff = R_p m_p c/ℏ − 1` | 3.000782 (→ integer 3) | C |

- **Class A** for `W=3` (analytic topology: the trefoil is the only protected low winding). **Class C**
  for `R_p` (the W+1 *conjecture*; right to 0.02% but not yet proven from trefoil geometry — see the
  OPEN-PROBLEM note in `laws.hpp`).
- **Caveat.** The proton-decay prohibition is genuinely *earned* by the Alexander invariant; the *radius*
  is a conjecture, kept class C. Engine: `law_VI::winding::{W_proton, R_p_predicted, W_eff}`,
  `law_VI::topology::{proton_p, proton_q}`.

## 4. The proton/electron mass ratio: 6π⁵

**Claim.** The mass ratio is pure topology: `m_p/m_e = 6π⁵`, integers and π only.

**Mechanism.** Reorganisation cost (Law IV mass) scales with the displaced volume `V_disp` of the vortex,
and the trefoil-to-unknot volume ratio is asserted to be the topological number `6π⁵ = 3·(2π²)·π³` — three
winding lobes × the `S³` surface-volume `2π²` × `π³`.

- `6π⁵ = 1836.12` vs measured `m_p/m_e = 1836.15` → `rel = 1.88×10⁻⁵`. **Class B** — pure topology,
  passes the delete-test (no mass measurement enters `6π⁵`).
- **Caveat.** The *number* is earned; the *mapping* `6π⁵ ↔ V_disp(3)/V_disp(1)` is **asserted, not
  derived** (it awaits the OP-1 equilibrium solver). Book I flagged the same open seam. Engine:
  `law_VI::mass_ratio::{six_pi_5, decomposition}`.

## 5. The Atomicus construction grammar (the nuclear constitution)

**Claim.** Every nucleus with `Z ≥ 2` decomposes **uniquely** into **1 alpha core + n_d deuterons + n_t
tritons**. This grammar is constitutional — there are no other decompositions, and no free neutrons.

**Mechanism.** The alpha particle (`⁴He`, 2p+2n) is the fundamental brick (Rule 1). A nucleus is one
alpha core plus deuteron "mortar" (D = 1p+1n) and triton "wedges" (T = 1p+2n). Counting protons and
neutrons against the `A`, `Z` of the isotope fixes the counts definitionally:

```
n_t = A − 2Z          n_d = 3Z − A − 2      (standard grammar: He-4 core)
```

For **electron-capture** isotopes the core is **He-3** (one neutron site vacant — a defect the nucleus
heals by capturing an electron, Atomicus Law 21), which shifts the algebra by one neutron:

```
n_t = A − 2Z + 1      n_d = 3Z − A − 3      (alternate grammar: He-3 core)
```

**Free neutrons are forbidden** in a stable nucleus (Rule 2): every neutron is paired into a D or a T,
and what looks like a "free neutron" is an **exposed triton remnant**. The stability rule `D ≥ T` holds up
to the **Golden Boundary** at gold (`Z = 79`); beyond it the structure goes "liquid" and `T > D` is
allowed, opening the heavy radioactive elements (Rules 3–4).

- **Status:** definitional / constitutional. The decompositions are *grammar*, not fitted results — stated
  directly. The He-3 alternate grammar is the same eliminative move that makes stellar neutronisation
  mass electron-capture (Atomicus Law 20, Book IV). Source: `ATOMICUS/rules` (the nuclear constitution).
- **Caveat.** Do not invent other decompositions; the grammar is the constitution. The per-isotope claim
  that *all* EC isotopes are fission/spallation remnants is still under check (Atomicus Law 21, flagged).

## 6. Nuclear occlusion geometry

**Claim.** Nuclear sizes are occlusion geometry: the charge radius scales with `Z`, built from the
proton's wake radius and the electron's wake `r_e`.

**Mechanism.** A nucleus of `Z` protons stacks `Z` displacement boundaries; its occlusion radius scales
as `Z·R_p`, and its **c-boundary** (the radius at which circulation would reach `c`) scales as `Z·r_e`.
He-4 is two proton wakes; carbon is six electron-wakes across:

| quantity | expression | value | class |
|---|---|---|---|
| helium-4 radius | `R_He = 2 R_p` | 1.68280×10⁻¹⁵ m (`rel = 4.36×10⁻³` vs measured) | C |
| carbon c-boundary | `6 r_e` (Z=6) | 1.690764×10⁻¹⁴ m | B |

- **Class C** for `R_He` (rides on the W+1 `R_p`); **class B** for the carbon c-boundary (built directly
  from `r_e` and an integer `Z`).
- **Caveat.** These are leading-order geometric scalings (`R_nuc ≈ Z·R_p`, `ϟ_Z = Z·r_e`); the half-percent
  on `R_He` is the same W+1 conjecture residual as §3. Engine: `nuclear::{R_He_predicted,
  c_boundary_nuclear}`.

## 7. The Lamb shift — a native candidate (honest)

**Claim.** The 2S–2P Lamb shift has a *native SDT candidate* from the trefoil's three-fold (C₃) wake — but
it is a **candidate, not a benchmark replacement**, and its amplitude is pending.

**Mechanism.** The proton trefoil's wake carries a native C₃ structure that supplies the atom's angular
degree of freedom (the s-vs-p distinction) without importing spherical-harmonic `ℓ` quantum numbers. The
native content is the **selection rule** `m₃ = 3k` (C₃ periodicity) and the `r⁻¹/r⁻³/r⁻⁴` power laws. From
the quadrupole term of that wake:

- 2S–2P native candidate = **1051.8 MHz** vs measured **1057.845 MHz** (0.57%). **Class C\*** (candidate).

- **Caveats (do not over-read).** The "multipole / quadrupole / Legendre Pℓ" framing is **borrowed
  mathematical language**; only the C₃ periodicity and the power-law exponents are native. The Lamb *value*
  rests on a quadrupole amplitude (~α·10⁻²) whose numerical verification is **pending a lattice wake
  solver** (APS04 Phase 2). The benchmark **B04 keeps its CALIBRATED `k_Lamb`** — this line does **not**
  replace it. Engine: `law_VI::angular::{m3_allowed, lamb_shift_native_MHz, *_exponent}`.

---

## Cross-references

- **Book I** — the relay's `P_conv` (Law I) is *screened* to the atomic `P_eff` at the electropause (§1);
  the `6π⁵ ↔ V_disp` seam (§4) is the open mapping flagged in Book I §4.
- **Book III** — "there is no charge" (§1) becomes mechanism: Coulomb *is* occlusion, "+e/−e" are the
  trefoil-vs-unknot **handednesses**, and the C₃ wake (§7) becomes the multipole exponents.
- **Book IV** — the koppa ladder underwrites `v = αc` (§1–2); the He-3 alternate grammar (§5) drives
  stellar neutronisation as mass electron-capture.
- `Engine/include/sdt/laws.hpp` — `law_III` (`P_eff`, `F_coulomb`, `R_charge`), `atomic`
  (`rotation_field_velocity`, `R_inf_derived`), `nuclear`, `law_VI::winding`, `law_VI::topology`,
  `law_VI::mass_ratio`, `law_VI::angular`.

## Regenerate

```bash
cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include /Fe:de_rerum.exe \
   Papers\De_Rerum_Todo_Existens\de_rerum.cpp && de_rerum.exe   # see BOOK II section
```

*Spatial Displacement Theory · De Rerum Todo Existens · Book II · J. C. Harvey, Melbourne.*
