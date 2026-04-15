# Q06: Post-Spallation Neutron Fate — Investigation Prompt

> **Classification**: Theoretical derivation with archival verification
> **Prerequisites**: Q01–Q04, atmospheric physics, nuclear data
> **Output format**: Complete fate-chain narrative from ejection to
> final capture or decay

---

## 1. Background

Cosmic ray spallation of atmospheric N-14 and O-16 nuclei produces fast
neutrons (1–20 MeV). These neutrons do not remain free — they either:

1. **Thermalise** by scattering off air molecules, slowing from MeV to
   thermal energies (~0.025 eV) in ~100 μs
2. **Are captured** by atmospheric nuclei (predominantly N-14) once
   thermalised
3. **Decay** (β⁻, t½ = 878.4 s) — but this is rare because capture
   occurs within milliseconds at sea-level air density

The dominant capture reaction **N-14(n,p)C-14** is responsible for ALL
naturally occurring C-14 on Earth. This single reaction underpins
radiocarbon dating — one of the most important measurement techniques
in archaeology, geology, and climate science.

SDT has never described this complete chain: spallation → thermalisation
→ capture → product. Each step must have a geometric description.

---

## 2. The Core Question

**What is the complete geometric fate-chain of a neutron ejected from
a spallation event in Earth's atmosphere, from the moment of ejection
to its final capture or decay?**

Sub-questions:

1. What happens geometrically when a fast neutron (v ≈ 0.065c, k ≈ 15)
   scatters elastically off an N-14 nucleus? How does the movement
   budget redistribute — does the neutron lose translational velocity
   and REGAIN circulation (increase k)?
2. As the neutron thermalises (k increases from ~15 to ~136,000), does
   its interaction character change? Does it become a "better" capturable
   object as k increases?
3. Why does N-14 capture thermal neutrons via (n,p) → C-14 instead of
   (n,γ) → N-15? What geometric property of N-14's scaffold makes
   proton emission energetically favourable?
4. What is the SDT description of the (n,p) reaction? The neutron
   enters the scaffold and a proton leaves — is this a direct
   substitution (the neutron physically displaces a proton) or a
   rearrangement (the neutron captures, then the scaffold ejects a
   proton through a separate mechanism)?
5. Does the C-14 grammar predict its decay mode (β⁻ to N-14)?

---

## 3. Methodology

### Phase A: Ejection and first collision

1. A cosmic ray proton (1–10 GeV) strikes an N-14 nucleus in the upper
   atmosphere (~15 km altitude, Pfotzer maximum).

2. Spallation produces (among other fragments) a fast neutron at ~5 MeV.
   - k = c / √(2 × 5 MeV / 939.6 MeV) ≈ c / (0.103c) ≈ 9.7
   - Movement budget: v_circ² = c² − v² → v_circ ≈ 0.995c
   - The fast neutron is mostly circulating — a W=3 torus with
     moderate translational drift

3. First collision with N-14:
   - Mean free path at 5 MeV in air: ~20 cm (sea-level equivalent)
   - Average energy loss per collision with N-14: ΔE/E = 2×14/(15)² ≈ 12.4%
   - After collision: E ≈ 4.38 MeV, k increases to ~10.3
   - SDT description: the neutron's ℓ≥3 wake grazes the N-14 scaffold
     surface; momentum transfers through the wake contact; the neutron
     recoils with reduced translational velocity and slightly increased
     circulation

4. Describe the geometry of elastic scattering in SDT:
   - Two displacement volumes approach
   - Their ℓ≥3 wakes overlap at closest approach
   - Momentum transfers through the wake (not through "contact" — there
     is no solid surface, only overlapping wake fields)
   - The exit angle is determined by the wake geometry at contact
   - Compute the SDT-predicted angular distribution and compare to
     measured elastic scattering angular distributions from ENDF

### Phase B: Thermalisation cascade

1. Track the neutron through ~20 collisions to thermalisation:
   - After each collision: compute E, v, k, v_circ
   - After ~20 collisions: E ≈ 0.025 eV (thermal)
   - Final k ≈ 136,000
   - Final v_circ ≈ 0.999999973c — virtually all circulation

2. The neutron has transformed from a moderately drifting, mostly
   circulating torus to an essentially STATIONARY, fully circulating
   torus. Its internal identity (W=3, uncharged) is maximally expressed.

3. Compute the spatial displacement during thermalisation:
   - The neutron scatters ~20 times, each over ~λ = 10–100 cm
   - Random walk displacement: d ≈ λ√N ≈ 50 cm × √20 ≈ 2.2 m
   - This is small compared to the atmospheric scale height (~8 km)
   - The neutron thermalises approximately where it was created

4. SDT observation: as k increases during thermalisation, the neutron's
   coupling to macroscopic convergence gradients CHANGES. At k = 10,
   the neutron is loosely coupled; at k = 136,000, it is tightly coupled
   to the local lattice environment. Does this increasing coupling
   explain the 1/v capture law (Q04)?

### Phase C: The N-14(n,p)C-14 reaction

This is the KEY reaction. It is unusual: most (n,thermal) reactions are
(n,γ) — radiative capture. But N-14 does (n,p) — it ejects a proton.

1. Grammar analysis:
   - N-14: Z=7, N=7, A=14. Grammar: α core + d + t (check ATOMICUS).
     n_tri = ?, n_deu = ?
   - N-14 + n: The neutron adds to the scaffold, creating N-15* (excited).
     New grammar: compute d, t, n_tri, n_deu for A=15, Z=7, N=8
   - But the product is NOT N-15. Instead, a proton is ejected → C-14.
     C-14: Z=6, N=8, A=14. Grammar: α core + d + t (check ATOMICUS).

2. Why (n,p) instead of (n,γ)?
   - Q-value for N-14(n,p)C-14: +0.626 MeV (exothermic!)
   - Q-value for N-14(n,γ)N-15: +10.833 MeV (also exothermic, more so)
   - Conventionally, (n,γ) should dominate because it releases more
     energy. But the (n,p) channel has a cross-section of 1.83 b vs
     only 0.075 b for (n,γ). The (n,p) channel is 24× larger.

   SDT must explain this:
   - Hypothesis: The N-14 scaffold, upon neutron insertion, has a
     grammar state that PREFERS proton ejection over gamma emission
   - Compute the grammar state of N-15* (the compound) and determine
     whether proton ejection produces a more grammar-stable product
     (C-14) than gamma de-excitation produces (N-15 ground state)
   - Is the proton ejected the same one that was part of a destabilised
     triton block? (Analogous to alpha decay mechanics from Triton
     Overload?)

3. Does the C-14 grammar predict β⁻ decay?
   - C-14 decays to N-14 by β⁻ (t½ = 5,730 y)
   - In grammar: β⁻ converts a neutron to a proton (Δn_tri = −1, Δn_deu = +1)
   - Check: C-14 should have higher triton fraction than N-14
   - The beta decay restores the original N-14 grammar — the complete
     cycle is: N-14 → [+n, −p] → C-14 → [β⁻] → N-14
   - SDT must show this is a GRAMMAR CYCLE that returns to the start

### Phase D: Alternative fates

Not all neutrons are captured by N-14. Catalogue ALL fates:

| Fate | Probability | Product | Grammar significance |
|------|------------|---------|---------------------|
| N-14(n,p)C-14 | ~93% | C-14 (β⁻ to N-14) | Grammar cycle |
| N-14(n,γ)N-15 | ~4% | N-15 (stable) | Permanent grammar change |
| O-16(n,γ)O-17 | ~0.01% | O-17 (stable) | Permanent grammar change |
| Ar-40(n,γ)Ar-41 | ~0.3% | Ar-41 (β⁻ to K-41) | Grammar cycle |
| Free decay: n → p + e⁻ + ν̄ | ~0.1% (altitude-dependent) | Proton + electron | Torus unwinding |
| Escape to space | ~2% | Lost | — |
| Capture in ground/ocean | Variable | Various | Cosmogenic production |

For each fate:
1. Compute the grammar of both reactant and product
2. Determine whether the grammar transition is "cycle" (returns to
   original grammar by subsequent decay) or "permanent" (stable product
   with different grammar)
3. Sum probabilities and verify they total 100%

### Phase E: Complete fate-chain diagram

Produce a complete flow diagram:

```text
COSMIC RAY PROTON (1-10 GeV)
        │
        ▼
N-14 / O-16 TARGET (upper atmosphere, ~15 km)
        │
        ├── Spallation fragments (various)
        ├── FAST NEUTRONS (1-20 MeV)
        │         │
        │         ▼ elastic scattering (~20 collisions)
        │   THERMAL NEUTRONS (0.025 eV)
        │         │
        │         ├── 93%: N-14(n,p)C-14 → [5730 y] → N-14 (CYCLE)
        │         ├── 4%: N-14(n,γ)N-15 (PERMANENT)
        │         ├── 0.3%: Ar-40(n,γ)Ar-41 → [109 min] → K-41 (CYCLE)
        │         ├── 0.01%: O-16(n,γ)O-17 (PERMANENT)
        │         ├── 0.1%: β⁻ decay → p + e⁻ + ν̄ (DISSOLUTION)
        │         └── 2%: escape to space
        │
        └── Other secondaries (π, μ, e, γ)
```

---

## 4. Required Outputs

1. **Thermalisation table**: Energy, v, k, v_circ at each of ~20
   scattering steps from 5 MeV to 0.025 eV

2. **N-14(n,p) grammar proof**: Complete grammar analysis showing WHY
   proton ejection is preferred over gamma emission

3. **C-14 cycle proof**: Grammar chain showing N-14 → C-14 → N-14
   is a closed grammar cycle

4. **Fate probability table**: All neutron capture/decay channels with
   probabilities, products, and grammar classification (cycle vs permanent)

5. **C-14 production rate prediction**: Using SDT parameters only,
   predict the global C-14 production rate (benchmark: ~2 atoms/cm²/s)

6. **SDT elastic scattering description**: The geometric mechanism of
   neutron-nucleus elastic scattering via wake overlap

---

## 5. Success Criteria

- [ ] Every step from ejection to capture is described geometrically
- [ ] The N-14(n,p) preference over (n,γ) is explained from grammar
- [ ] The C-14 production rate is predicted within a factor of 2
- [ ] The thermalisation cascade correctly increases k toward thermal
- [ ] The fate probability table sums to 100% within 5%
- [ ] The grammar cycle N-14 → C-14 → N-14 is proven closed
- [ ] No prohibited concepts are used (no nuclear potential, no QM)
