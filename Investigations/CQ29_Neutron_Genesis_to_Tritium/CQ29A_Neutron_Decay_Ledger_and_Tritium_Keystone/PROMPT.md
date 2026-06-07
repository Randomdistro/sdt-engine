# CQ29A — Neutron Decay Ledger and Tritium Keystone *(free neutron → β-decay → tritium decay)*

> **Scope honesty.** This investigation closes the **decay ledger** and the **tritium-Q keystone** only. The `3n → triton` **genesis** step (assembly) is *energy-gated but kinetically unresolved* and is split out to **CQ29B** — do not let this file's narrative arc imply genesis was demonstrated.

> **The arc this ledger traces (decay direction):**
> a **free neutron** is an unbound, strained, *linked* (W=3 trefoil ⊕ W=1 unknot) object; it **unlinks** by β-decay `n → p + e⁻ + ν̄ₑ`, the antineutrino carrying the released linking strain as a topological receipt; the freed **proton** keeps the (2,3) trefoil and its `R_p = 4ℏ/m_pc`; the released **electron** is the W=1 unknot whose displaced volume is exactly **1/1836** of the proton's; that electron **Hopf-threads** into a 1s loop while the proton **binds two neutrons** into the **triton** — and the result is **tritium**, the first complete atom (¹H isotope: 1p + 2n nucleus + 1 electron). The loop closes when tritium itself β-decays, `³H → ³He + e⁻ + ν̄ₑ`, repeating the split one shell up.

This is a **constitutional** investigation: it must touch — and remain consistent with — every load-bearing SDT formulation we have (Law IV mass-as-displacement, the W+1 radius, the trefoil topology, the deuteron–triton grammar, the neutrino receipt, occlusion binding, the Hopf/poloidal electron channel) **without breaking a single one**. Any stage that requires a change to a frozen result (`CQ25` grammar, `laws.hpp::winding`, `laws.hpp::law_IV`) is a *failure of that stage*, not a license to edit the engine.

---

## 0. Overarching question and the conserved-quantity spine

**Q0.** Is the free neutron a **topologically linked** proton-trefoil ⊕ electron-unknot bound by a measurable strain, such that (a) its **lifetime**, (b) its **decay energy** `Q_n`, (c) the **1836 proton:electron mass ratio**, and (d) the **tritium** end-state all fall out of *one* linking-and-unlinking mechanics — rather than four separately fitted facts?

Every stage is checked against the conservation spine for `n → p + e⁻ + ν̄ₑ`:

| quantity | neutron | → | proton | electron | antineutrino | check |
|---|---|---|---|---|---|---|
| charge `q` | 0 | | +1 | −1 | 0 | `0 = +1−1+0` ✓ |
| baryon `B` (trefoil persistence) | 1 | | 1 | 0 | 0 | trefoil survives ✓ |
| lepton `L` | 0 | | 0 | +1 | −1 | unknot⊕receipt ✓ |
| winding `W` | 3⊕1 *(linked)* | | 3 | 1 | 0⁺ *(receipt)* | unlink ✓ |
| rest energy [MeV] | 939.5654 | | 938.2720 | 0.5110 | — | residual `Q_n` |
| `Q_n = m_n−m_p−m_e` | | | | | | **0.7824 MeV** |
| displaced volume `V_disp` | `V_p+V_e+δV` | | `1836·V_e` | `V_e` | ~0 | ratio **1836** |

The two numbers this investigation must *mechanically explain*, not fit, are **`Q_n = 0.7824 MeV`** (the linking strain) and **`m_p/m_e = 1836.15`** (the displaced-volume ratio).

---

## 1. The cast (primitives, constants, and the topological dictionary)

All constants from `sdt::laws::measured` (CODATA 2018). Topology from `CQ02` (vortex equilibrium), `CQ11` (trefoil confinement), `CQ14` (spation traction), `CQ17` (mass-ratio), and `nuclear.hpp` (grammar).

| object | SDT topology | key scale | engine ref |
|---|---|---|---|
| proton `p` | (2,3) torus knot, **6π**, W=3 trefoil | `R_p = 4ℏ/m_pc = 0.84124 fm` | `laws.hpp::winding` |
| electron `e⁻` | (1,1) unknot, **2π**, W=1 simple torus | `r_e = αℏ/m_ec = 2.818 fm` (wake) ; `R_excl,e = 2.878e-21 m` (core) | `laws.hpp::law_IV` |
| antineutrino `ν̄ₑ` | open winding, **W→0⁺**, the *receipt* | mass-gap `≲ 0.02 eV` | `neutrino.hpp`, Rules §7/§19 |
| free neutron `n` | trefoil ⊕ unknot, **linked** under strain | `m_n = 939.5654 MeV`; `τ_n ≈ 880 s` | this investigation |
| triton `t` (³H nucleus) | 1p + 2n weighted wedge | `B(t) = 8.482 MeV` | `nuclear.hpp` (alpha-invalid primitive) |
| measured anchors | `m_n=939.5654`, `m_p=938.2720`, `m_e=0.5110` MeV; `m_n−m_p=1.2933 MeV`; `Q_n=0.7824 MeV`; `τ_n`: bottle 877.75 s / beam 887.7 s (Δ≈9.5 s puzzle); `B(t)=8.482`, `B(³He)=7.718 MeV`; tritium `Q_β=18.591 keV`, `t½=12.32 yr` | | `E31`, `E39` |

**Topological dictionary** (the rules of the game, to be applied uniformly):
- **Charge = signed winding handedness.** `+1` ⟺ right-handed trefoil net winding; `−1` ⟺ left-handed unknot; `0` ⟺ balanced/open.
- **Baryon number = trefoil persistence.** A closed (2,3) knot cannot be undone without cutting → `B` conserved.
- **A free open strand costs `E(L)=σL → ∞`** (`CQ11` Theorem B): every strand must re-close. This is *why nothing is ever a bare half-vortex*.
- **The neutrino is the receipt of any winding reconfiguration** (Rules §7): every β/EC/fusion event files exactly one.

---

## 2. The eight stages

### Stage A — The free neutron as a strained, linked dyad
**Premise.** Model `n = p ⊕ e` as a **Hopf-linked** pair (linking number `Lk = ±1`): the W=3 proton-trefoil with the W=1 electron-unknot threaded through its **poloidal channel** (the same channel the bound atomic electron will later occupy — Stage G). The link is held by a strain energy `ε_link`.

**Formulation.**
```
m_n c²  =  m_p c²  +  m_e c²  +  ε_link
ε_link  =  Q_n  =  m_n − m_p − m_e  =  0.7824 MeV          [the linking strain]
```
**Q-A1.** Is `ε_link` derivable as the *interaction energy of a Hopf link* between a (2,3) tube of radius `R_p` and a (1,1) tube of radius `r_e`, evaluated through the occlusion pressure `P_eff`? Target: `≈ 0.78 MeV`.
**Q-A2.** Does the linked geometry predict the neutron's **net charge 0** (trefoil `+1` ⊕ unknot `−1` superposed) and its small **negative magnetic moment** `μ_n = −1.913 μ_N` from the *unbalanced* poloidal current of the embedded unknot?
**Gate PASS-A.** A Hopf-link interaction energy computed from `P_eff·(overlap solid angle)` lands within a factor ~2 of `Q_n = 0.782 MeV` *without* a new fitted constant. (Honest: `P_eff` is already class-E calibrated; this stage may at best reach class-E, not parameter-free.)
**Prediction.** `μ_n / μ_p = −2/3` exactly from the (unknot-loaded trefoil) vs (bare trefoil) poloidal-current ratio (cross-check `E40`).

### Stage B — β-decay as a winding-conserving unlink
**Premise.** The decay is the **unlinking** of the Stage-A dyad: `Lk: ±1 → 0`. The crossing-change releases the strain; the **antineutrino is the open-winding receipt** carrying the topological residue.
**Formulation.**
```
n → p + e⁻ + ν̄ₑ ;  conserve {q, B, L, W}  per the §0 spine
Q_n = KE_e + E_ν̄ + T_recoil    (T_recoil ~ Q²/2m_p c² ≈ 0.3 eV, negligible)
endpoint:  KE_e^max = Q_n − (m_ν c² ≈ 0) = 0.782 MeV
electron emerges as a W=1 unknot at its wake radius r_e = αℏ/m_ec
```
**Q-B1.** Does winding/lepton conservation **force exactly one** electron and one antineutrino (no di-electron, no two-neutrino channel at tree level)?
**Q-B2.** Is the **β-spectrum shape** (the e⁻/ν̄ energy sharing) reproducible from the phase space of a single unlinking event (Fermi `pE(Q−E)²`), or does the SDT mechanism predict a distortion?
**Gate PASS-B.** The conservation spine closes exactly (it must), and `KE_e^max = Q_n` to the measured 782 keV endpoint.
**Prediction.** The β endpoint is **`782.33 keV`**; any SDT-specific spectral distortion (if predicted) is a falsifiable departure from the Fermi shape.

### Stage C — The free-neutron lifetime from unlink mechanics (and the beam–bottle puzzle)
**Premise.** `τ_n` is the **mean time to execute the crossing-change** that unlinks the dyad — a topological barrier crossing, not a random clock. From `CQ11`, an open strand re-closes on `t_collapse = a/c`; the *forward* unlink is the rare process.
**Formulation (to be derived, not fitted).**
```
Γ_n = 1/τ_n  ≈  f_circ · exp(−B_link / ε_zpf)            [Arrhenius-like barrier form]
f_circ = c / λ_C,p  (proton circulation frequency)
B_link = topological barrier of the Lk: ±1→0 crossing change
```
**Q-C1.** Can `τ_n ≈ 880 s` be reached from `f_circ` and a barrier `B_link` expressed in the *same* `σ_string`/`P_conv/3` units as `CQ11`?
**Q-C2.** **The beam–bottle discrepancy (Δ ≈ 9.5 s, ~1%)**: is it a **branching** between two unlink channels — (i) full `p+e+ν̄` and (ii) a rare bound-state / radiative channel that a *beam* counts but a *bottle* does not (or vice-versa)? Predict the branching ratio `≈ Δτ/τ ≈ 1.0%` and its sign. (This is `E31`'s falsifiable core.)
**Gate PASS-C.** `τ_n` predicted to order-of-magnitude from the barrier model; the beam–bottle gap reproduced in sign and ~1% magnitude as a topological branching.
**Prediction.** A **~1% missing decay channel** (the SDT branching) — testable against the proton-counting (beam) vs neutron-disappearance (bottle) methods.

### Stage D — The 1836 displaced-volume partition (and the falsification of "1836π")
**Premise.** At the split, the displaced spation volume partitions: the proton keeps `1836/1837`, the electron `1/1837`. The ratio is **geometric**, from the torus-knot Pappus volumes — *not* a winding count.
**Formulation.**
```
V_torus(p,q) = 2π² √(q/p) · a³                  [Pappus, CQ02/CQ05/CQ10b/CQ17]
m_p/m_e = V_disp,p / V_disp,e
        = [√(3/2) · a_p³] / [√(1/1) · a_e³]
        = 1.2247 · (a_p/a_e)³  =  1836.15
   ⟹   (a_p/a_e)³ = 1499.0   ⟹   a_p/a_e = 11.442      [the ONE number to derive]
```
**Falsification sub-test (must be shown).** A *literal* `1836π` geometric winding (918 toroidal turns) fed into the W+1 rule gives
```
R_p(W=918) = 919 · ℏ/(m_p c) = 919 · 2.1031e-16 m = 193.3 fm   (230× too large)
```
so **`1836` is a displaced-volume ratio, never a geometric winding.** The trefoil stays 6π/W=3; `R_p = 0.84 fm` is preserved.
**Q-D1.** Derive `a_p/a_e = 11.442` from the (2,3)-vs-(1,1) knot equilibrium (`CQ02`: `R/a=√(q/p)`, budget `v_p²+v_t²=c²`) — i.e. from the *minor-radius* that the trefoil's three-fold confinement forces relative to the unknot's. Target: 11.44 ± 1%.
**Q-D2.** If Q-D1 succeeds, the **class-F numerology** `m_p/m_e = (3/2)^{3/2}·10³ − 1` is *retired* and replaced by a **class-C** geometric volume — state the provenance upgrade explicitly.
**Gate PASS-D.** `1.2247·(a_p/a_e)³ = 1836` reproduced; `a_p/a_e = 11.44` either derived (PASS, → class C) or flagged as the remaining unknown (PARTIAL, stays class F). The `1836π → 193 fm` falsification is printed.
**Prediction.** `a_p/a_e = 11.44`; equivalently `R_excl,p/R_excl,e = 1836^{1/3} = 12.25` (cross-check `laws.hpp::law_IV` literals `3.525e-20 / 2.878e-21 = 12.25`).

### Stage E — Charge and radius of the freed proton (consistency, not novelty)
**Premise.** The freed proton must reproduce the frozen `laws.hpp::winding` results exactly.
**Formulation.**
```
R_p = (W+1)ℏ/(m_pc) = 4ℏ/(m_pc) = 0.84124 fm           [W=3, unchanged]
charge(p) = +1  (trefoil net winding) ;  charge(e) = −1 (unknot opposite handedness)
W_eff = R_p m_p c/ℏ − 1 = 3.000                         [the integer check]
```
**Gate PASS-E.** All `laws.hpp::winding` values reproduced bit-for-bit. **Any deviation here means an earlier stage corrupted the topology — fail back.**

### Stage F — Re-binding: two neutrons + the proton → the triton
**Premise.** Tritium's *nucleus* is the **triton** `t = 1p + 2n` — the grammar's "weighted wedge," an **alpha-invalid primitive** (`alpha_grammar(1,3) → n_d=−2 < 0`): it is not decomposable into α+blocks; it *is* a block.
**Formulation.**
```
triton = 3-nucleon triangle ; occlusion binding B = k·Ω, Ω = 2π(1−cosθ), sinθ = R/d
B(t)_target = 8.482 MeV  (3 pairwise p-n / n-n contacts)
grammar role: t is a building block; B(deuteron)=2.224 → B(triton)=8.482 (3.8×, not 1.5×)
```
**Q-F1.** Predict `B(t) = 8.482 MeV` from the triangle occlusion geometry (3 contacts, two p-n + one n-n) using the deuteron-pinned `k_occ`. Why is the triton bound (8.48 MeV) while the **di-neutron is not** — i.e. the proton is *required* as the geometric keystone?
**Q-F2.** Why does the triton survive as a **stable grammar block inside nuclei** yet **free tritium β-decays**? (Answer must invoke the triton-fraction overload of the *free* 1-α-less wedge vs the sheltered in-nucleus wedge.)
**Gate PASS-F.** `B(t)` reproduced to ~15% (class-E `k_occ`); di-neutron correctly predicted unbound; the "stable-block-but-free-decay" paradox resolved geometrically.
**Prediction.** The **n–n contact** in the triton is the weak link; the triton's "third neutron" is the exposed strand that re-converts (Stage H).

### Stage G — The electron threads in: the first atom
**Premise.** The β-electron (W=1 unknot) does not escape — it **Hopf-fibres into the 1s shell through the proton's poloidal channel** (the exact mechanism of the visualizer). Tritium becomes the first complete **atom** (¹H chemistry, 1 electron).
**Formulation.**
```
electron emerges at wake radius r_e = αℏ/m_ec = 2.818 fm
1s shell scale: a₀ = r_e/α² = αℏ/m_ec / α² = ℏ/(α m_e c) ·(1/α)... ⟹ a₀ = 5.29e-11 m
Hopf link: electron loop ⟂ E×P, threading the proton poloidal channel (Lk = ±1 restored — atomic!)
```
**Q-G1.** Is the **atomic electron just the β-electron re-linked at a larger scale** — i.e. is a hydrogen atom a *neutron re-expressed* with the unknot orbiting (Lk=1, stable) instead of embedded (Lk=±1, strained)? This makes **n ↔ H** a single object at two link-radii.
**Q-G2.** Does the link-radius set `a₀`, and does the `1836` re-appear as the **`a₀ : R_p` lever** via the same `m_p/m_e` (the reciprocal-drive gear, `CQ14`: `ω_p/ω_e = 3(m_p/m_e)/α`)?
**Gate PASS-G.** The electron's emergence radius and Hopf re-link reproduce `a₀ = 5.29e-11 m` within the existing `CQ09`/`CQ16` koppa identities (`α²a₀ = r_e`).
**Prediction.** **A free neutron and a ground-state hydrogen atom are the same topology at two linking radii** — the strained (nuclear, `τ=880 s`) vs the relaxed (atomic, stable). Falsifiable via the `Q_n` ↔ `13.6 eV` binding hierarchy.

### Stage H — Closure: tritium β-decay repeats the split one shell up
**Premise.** Tritium (1p+2n) → He-3 (2p+n): the triton's weak n–n strand (Stage F) re-converts; in the grammar this is the **triton → He-3 core** transition (`nuclear.hpp::h3_grammar`).
**Formulation.**
```
³H → ³He + e⁻ + ν̄ₑ ;  Q_β = 18.591 keV ;  t½ = 12.32 yr
grammar:  (Z=1,A=3) triton  →  (Z=2,A=3) He-3 core   [valence shift: the He-3 grammar]
```
**Q-H1.** Predict the **collapse of the Q-value** from the free-neutron `782 keV` to tritium's `18.6 keV` (a 42× reduction) from the **binding-energy difference** `B(³He) − B(t) = 7.718 − 8.482 = −0.764 MeV` shifting the available energy (`Q_β ≈ Q_n − [B(t)−B(³He)] = 782 − 764 = 18 keV`). **Target hit: 18 keV — this is the keystone numerical prediction of the whole arc.**
**Q-H2.** Why is tritium's lifetime `12.32 yr` (≈ 10⁹× the free neutron's `880 s`)? Relate to the *suppressed phase space* (Q⁵ in the rate ⟹ `(782/18.6)⁵ ≈ 5.3e6`) times the in-nucleus barrier.
**Gate PASS-H.** `Q_β(³H) = Q_n − [B(t) − B(³He)] = 18 ± 2 keV` reproduced; the `Q⁵` phase-space scaling explains the lifetime ratio to within an order of magnitude.
**Prediction.** **`Q_β(³H) = 18.6 keV` falls out of `Q_n − ΔB` with no new parameter** — the single most defensible number in the investigation.

---

## 3. The unifying ledger (what must balance, end to end)

For the full arc **`3n → t + e⁻ + ν̄ₑ → (³H atom) → ³He + e⁻ + ν̄ₑ`** the audit tool must print, at every step, a balance table proving simultaneous conservation of `{q, B, L, W, energy, V_disp}` and flag any non-closure as FATAL. The two "hero numbers" the tool must reproduce *mechanically*:
1. **`Q_n = 0.7824 MeV`** as a Hopf-link strain (Stage A/D), and
2. **`Q_β(³H) = 18.6 keV = Q_n − [B(t) − B(³He)]`** (Stage H).
The two "honesty numbers" it must *not* fudge:
3. **`a_p/a_e = 11.44`** — derive it (class C) or declare it open (class F).
4. **`1836π → R_p = 193 fm`** — the printed falsification that 1836 is volume, not winding.

---

## 4. Falsifiable predictions (consolidated)

| # | prediction | test | class |
|---|---|---|---|
| P1 | `Q_β(³H) = Q_n − [B(t)−B(³He)] = 18.6 keV` | measured 18.591 keV | **C** |
| P2 | `a_p/a_e = 11.44` ⟺ `R_excl,p/R_excl,e = 12.25` | `laws.hpp` literals 12.25 | C if D-derived, else **F** |
| P3 | `μ_n/μ_p = −2/3` from unknot-loaded trefoil current | −1.913/2.793 = −0.685 (1.9%) | C-flagged |
| P4 | free-neutron beam–bottle gap = ~1% topological branching | Δτ/τ ≈ 9.5/880 = 1.08% | **D** (novel) |
| P5 | n ↔ H are one topology at two link radii (`Q_n` ↔ `13.6 eV`) | hierarchy | **D** |
| P6 | di-neutron unbound; proton is the triton keystone | known (²n unbound) | C |
| P7 | `1836π` geometric winding ⟹ `R_p = 193 fm` (falsified) | self-consistency | C (falsification) |

## 5. Provenance discipline (apply `FORMULATIONS_PROVENANCE_AUDIT.md` to every new formula)

- `ε_link = Q_n` (Stage A): `provenance: calibrated` (uses `P_eff`) · `class: E` until a parameter-free link energy is found.
- `a_p/a_e = 11.44` (Stage D): the **crucible** — `class: C` if derived from knot geometry, else **`class: F`** (and the existing `(3/2)^{3/2}·10³−1` stays F, not promoted).
- `Q_β(³H) = Q_n − ΔB` (Stage H): `provenance: SDT-derived` · `correspondence: known-match` · `input_dependency: measured-observable` (uses measured `B(t)`, `B(³He)`) · **`class: C`**.
- `1836π → 193 fm`: a **falsification**, `class: C (negative result)`.
- Charge/baryon/lepton/winding conservation (Stage B): `SDT-posited` (the topological dictionary) · `class: A`.

**Rule:** no stage may quietly consume the *target* value it is trying to predict. The delete-test (`FORMULATIONS_PROVENANCE_AUDIT.md §4`) is applied to P1, P2, P3 before any "C" is claimed.

## 6. Engine connections (build on, do not modify)

`nuclear.hpp` (grammar, `h3_grammar`, triton as alpha-invalid primitive) · `laws.hpp::winding` (R_p, W_eff — **frozen, Stage E verifies**) · `laws.hpp::law_IV` (V_disp, R_excl ladder) · `CQ02` (R/a=√(q/p), budget) · `CQ11` (`E=σL`, open-strand collapse) · `CQ14` (reciprocal-drive gear) · `CQ17`/`CQ05`/`CQ10b` (Pappus torus volume) · `E31` (neutron lifetime) · `E39` (n–p mass diff) · `E40` (nucleon moments) · the visualizer (Stage G electron Hopf-thread).

## 7. Build plan (`cq29_neutron_genesis.cpp`, one-way A→H)

1. **A/B**: conservation-spine ledger (charge/baryon/lepton/winding/energy/volume) for `n→p+e+ν̄`; print FATAL on any non-closure.
2. **C**: barrier-model `τ_n` estimate + beam–bottle branching prediction (label thermal/topological assumptions).
3. **D**: Pappus volume ratio `1.2247·(a_p/a_e)³`; solve `a_p/a_e`; print the `1836π → 193 fm` falsification.
4. **E**: re-emit `laws.hpp::winding` values and `assert` bit-match (Stage-E gate).
5. **F**: triton occlusion binding `B(t)` from 3-contact triangle; di-neutron unbound check.
6. **G**: electron emergence radius → `a₀` via `α²a₀=r_e`; the n↔H link-radius identity.
7. **H**: **`Q_β(³H) = Q_n − [B(t)−B(³He)]`** — the keystone; `Q⁵` lifetime scaling.
8. Final **arc ledger**: `3n → t + e + ν̄ → ³H atom → ³He + e + ν̄`, every conserved quantity balanced, every hero/honesty number printed with its provenance class.

*Author attribution: James Christopher Tyndall, Melbourne.*
