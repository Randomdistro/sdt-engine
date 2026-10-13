# NP17 — The Nuclear Packing Order: 6π-Trefoil Interleaving with Shared-Electron Binding

> **Domain**: 05 — Nuclear Physics
> **Status**: RESOLVED (mechanism + deuteron) · alpha/heavy magnitude PENDING (geometry import)
> **Author**: J. C. Harvey, Melbourne
> *(Written to the `Investigations/PERFECT_PROMPT_TEMPLATE.md` structure. Ports the model
> from the companion SDT repo: `6PI_TREFOIL_INTERLEAVED_SPEC.md`, `ELECTRON_SHARING_MODEL.md`,
> `NUCLEAR_PACKING_STRUCTURE_AND_DATA.md`, `D-01`.)*

---

## 1. Executive Summary

The long-standing nuclear question in the engine — *what is the actual packing order, and
where does the binding energy come from?* — is answered here. **Nuclei are interleaved 6π
trefoils.** Each nucleon is a 6π-winding torus; a **neutron is a proton plus one internal
electron** (`n = p⁺ + e⁻`, the SDT composite — no free neutrons), and **that internal
electron is shared between adjacent protons**, forming a Coulomb pressure well. Nuclear
binding is therefore the *same shared-electron bond as the `H₂⁺` molecular ion, at
femtometres instead of ångströms* — "chemistry is nuclear physics geared down by 137." The
deuteron drops out cleanly with **no fitted energy scale** (the only scale is the Coulomb
identity `k_e e² = αℏc = 1.44 MeV·fm`): `E = 3αℏc/D = 2.20 MeV` vs measured 2.224. This
replaces NP05's *killed* "binding = a displaced volume" hypothesis with a concrete,
parameter-light mechanism.

## 2. Physical Context

The ATOMICUS grammar already says every nucleus (Z≥2) is **1 alpha core + n_d deuterons +
n_t tritons** (`n_t = A−2Z`, `n_d = 3Z−A−2`), with **no free neutrons** — a "free neutron"
is an exposed remnant. NP17 supplies the *geometry and the binding* underneath that grammar:

- **Nucleon** — a 6π-winding trefoil torus; proton boundary `R_p ≈ 0.84 fm` (`= 4ℏ/m_p c`,
  the W+1 result), minor radius `≈ R_p/3`.
- **Neutron** — `p⁺ + e⁻_internal`; the internal electron sits at a trefoil node
  (`r_node ≈ R_p/3 ≈ 0.28 fm`).
- **Interleaving** — adjacent trefoils *mesh* (don't stack); internal-electron vortices
  synchronise, "donut holes" align so an electron can be **shared** between protons.
  Deuterons interlock L–R–L–R for tetrahedral stability; alphas sit at icosahedral/shell
  interstices for `A ≤ 40`.

The key variable is the **shared electron**: it is the bond. Where standard nuclear physics
posits a residual strong force, SDT has an electron in the gap doing exactly what an
electron does in a molecule — pulling two positive cores together — but at `αℏc/r` with `r`
a thousand times smaller, so the well is a thousand times deeper (MeV, not eV).

## 3. Theoretical Framework

**The one energy scale (no fit):** `k_e e² = αℏc` (the Coulomb identity, the engine's
`coulomb_identity` namespace). Every binding energy below is this number divided by a
geometric length. There is **no fitted nuclear constant** — this is the whole point.

**Binding = shared-electron electrostatics.** For point cores `q_i ∈ {+1 (proton),
−1 (electron)}` at positions `r_i`:
```
U = Σ_{i<j} q_i q_j · αℏc / r_ij ,        E_bind = −U   (positive ⇒ bound)
```

**Deuteron (the clean case, D-01).** `p — e — p` collinear, electron at the gap centre:
```
p–e (×2): −4αℏc/D ;   p–p: +αℏc/D   ⇒   E_bind = 3αℏc/D
```
The **factor 3 is exact electrostatics**, not a parameter (`−4 + 1 = −3`). The gap
`D = 2R_p + r_node ≈ 2R_p + R_p/3` is set by the proton boundaries plus the electron node.

**Alpha (He-4).** `2p + 2n = 4p + 2e`, tetrahedral, two interlocked deuterons (L–R–L–R), the
2 internal electrons weaving four-way. Same electrostatic sum over 4 protons + 2 electrons.

**Grammar extension.** A nucleus `(Z,A) → (n_d, n_t)`; its `A−Z` neutrons supply `A−Z`
internal (shared) electrons that mediate the bond network. The per-isotope `(r,θ,φ)`
placement (icosahedral for `A ≤ 40`) comes from `NUCLEAR_PACKING_STRUCTURE_AND_DATA.md` /
`trefoil_mappings.json`.

**Constraints (hard):** only `αℏc` as the energy scale (no fitted binding constant); the
ATOMICUS grammar honoured (no free neutrons); no QM nuclear potential imported. Honest
labelling of what the electrostatics alone does and does not reach.

## 4. Investigation Strategy

**Phase 1 — Mechanism + deuteron (the certifiable core).** Implement the electrostatic
shared-electron sum; compute the deuteron from geometry (`D = 2R_p + R_p/3`); confirm the
factor 3 and `E ≈ 2.2 MeV` with **no fitted energy**. *Success:* within 3% of 2.224 MeV.

**Phase 2 — Alpha (tetrahedral).** Place 4 protons (regular tetrahedron) + 2 electrons (two
opposite-edge midpoints) and compute the binding at physical spacing (`a = 2R_p`). *Success
criterion is deliberately honest:* report the electrostatic value and **whether it reaches
28.3 MeV**; if not, quantify the shortfall as the "tetrahedral-lock"/occlusion remainder.

**Phase 3 — Grammar decomposition.** For He-4, C-12, O-16, Ne-20, Ca-40, emit `(n_d, n_t)`
and the shared-electron (neutron) count — the bond-mediator inventory the full geometry
will sum over.

**Phase 4 — Honesty boundary.** State exactly where the model is complete (deuteron) and
where it needs the imported per-isotope geometry and/or an occlusion term (alpha, heavy).

## 5. Success Criteria

- ✅ **PASS (deuteron, mechanism):** `E = 3αℏc/D` within 3% of 2.224 MeV from geometry, with
  the factor 3 exact and **no fitted energy scale**. *Publish:* "nuclear binding is a
  shared-electron Coulomb well; the scale is `αℏc`, not a fitted constant."
- ⏳ **PENDING (alpha/heavy):** electrostatics alone may under-bind the alpha; the remainder
  is the tetrahedral-lock/occlusion, named here, magnitude deferred to the imported geometry.
- ❌ **FAIL:** if the deuteron cannot be reached without a fitted constant, or the factor 3
  is not the electrostatic value.

The headline is the **mechanism + the deuteron**, not a from-scratch reproduction of every
binding energy (which needs the per-isotope geometry).

## 6. Outputs

1. **INVESTIGATION.md** — this document.
2. **np17_nuclear_packing.cpp** — standalone C++20 (`#include <sdt/laws.hpp>`): the
   electrostatic shared-electron binding; deuteron, alpha, grammar table.
3. **np17_results.txt** — the run output.
4. **NP17_VERDICT.md** — classification with the measured numbers.

## 7. Dependencies & References

**Upstream (required):** ATOMICUS grammar (`1α + n_d d + n_t t`, no free neutrons); the
Coulomb identity `k_e e² = αℏc`; the W+1 proton boundary `R_p = 4ℏ/(m_p c)` (PPT09).
**Companion repo:** `6PI_TREFOIL_INTERLEAVED_SPEC.md`, `ELECTRON_SHARING_MODEL.md`,
`NUCLEAR_PACKING_STRUCTURE_AND_DATA.md`, `D-01` (deuteron certification),
`trefoil_mappings.json`, `generate_trefoil_mappings.py`.
**Supersedes/completes:** NP05 (KILLED volume-price) — NP17 is the binding mechanism NP05/NP06
were searching for. **Related:** NP08 (triple-alpha), NP09 (deuteron binding), NP10 (alpha
binding) — those graduated experiment specs are now mechanistically grounded here.
**Downstream:** per-isotope binding curve; fission/spallation control (the nuclear end-goal).

## 8. Falsification Tests

| Test | Hypothesis | Outcome | If FAIL |
|---|---|---|---|
| T1 | deuteron factor is 3 | `−4 + 1 = −3αℏc/D` exact | the shared-electron geometry is wrong |
| T2 | `E_d = 3αℏc/D` ≈ 2.224 | 2.20 MeV at `D = 2R_p + R_p/3` (1.1%) | the gap is not `~R_p/3` |
| T3 | no fitted energy scale | only `αℏc` enters | a nuclear constant was smuggled in |
| T4 | alpha from same sum | report value; flag any shortfall | (honest — shortfall = lock/occlusion) |
| T5 | grammar consistency | `A−Z` shared electrons per nucleus | grammar broken |

## 9. Implementation Notes

- Energy scale `αℏc` is engine-sourced: `M::alpha · (M::hbar·M::c/M::MeV_to_J)·1e15`
  [MeV·fm]; `R_p` from `M::R_p` (→ fm). **No hard-coded binding constant.**
- Electrostatic sum is exact (point cores); positions in fm. Electron at the **gap centre**
  for the deuteron (the certified D-01 geometry), at **opposite-edge midpoints** for the alpha.
- The alpha is geometry-sensitive: electrons at edge midpoints under-bind; electrons at the
  trefoil nodes (much closer to protons) over-bind. The *correct* placement is the imported
  `trefoil_mappings.json` — do not tune it here; report the bracket honestly.
- Heavy nuclei (`A > 40`) need the shell/icosahedral placement; flagged as the next stage.
