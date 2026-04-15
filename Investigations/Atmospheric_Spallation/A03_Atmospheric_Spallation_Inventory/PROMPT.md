# A03: Atmospheric Spallation Inventory — Investigation Prompt

> **Classification**: Archival data computation + rate calculation
> **Prerequisites**: A01, EXFOR data for N-14 and O-16, cosmic ray spectrum
> **Output format**: Complete product inventory with grammar and rates

---

## 1. Objective

Produce the COMPLETE catalogue of every isotope created by cosmic ray
spallation of atmospheric nuclei (N-14, N-15, O-16, O-17, O-18, Ar-40),
with the SDT grammar computed for every product and every decay-chain
intermediate. Verify that the grammar is valid at every step, and compute
the production rate for each isotope using only archival cross-section
data and the measured cosmic ray spectrum.

This inventory is the definitive SDT description of what cosmic rays
DO to Earth's atmosphere. Every product must be accounted for.

---

## 2. Scope

### Complete product catalogue for:
1. **N-14 + p**: All channels from (p,n) through maximum fragmentation
2. **O-16 + p**: All channels from (p,n) through maximum fragmentation
3. **Ar-40 + p**: All channels (minor contributor but forensically
   important — Ar-37 production is a nuclear test signature)
4. **Secondary reactions**: Products of neutrons produced in primary
   spallation (especially N-14(n,p)C-14, the C-14 production reaction)

### For each product:
- Complete grammar (α, d, t, n_tri, n_deu)
- Grammar validity check
- Decay chain to stable endpoint
- Grammar at each decay step
- Production rate estimate (atoms/cm²/s at Earth's surface)

---

## 3. Methodology

### Phase A: Catalogue all primary products

1. Query EXFOR for ALL measured reactions with:
   - Target: N-14, O-16, Ar-40
   - Projectile: proton
   - Any product
   - Any energy

2. For each reaction entry, record:
   - Reaction notation (e.g., N-14(p,pn)N-13)
   - Product identification
   - Cross-section at relevant energies (100 MeV, 1 GeV, 10 GeV)
   - Threshold energy

3. Supplement with theoretical predictions (TENDL-2023) for reactions
   not yet measured but predicted to have σ > 0.01 mb at any energy.

4. Produce a complete product table:

   | # | Target | Reaction | Product | Z | A | N | σ(1 GeV) mb | Threshold MeV |
   |---|--------|----------|---------|---|---|---|-------------|---------------|
   | 1 | N-14 | (p,pn) | N-13 | 7 | 13 | 6 | ~10 | ~11 |
   | 2 | N-14 | (p,2p) | C-13 | 6 | 13 | 7 | ~5 | ~13 |
   | ... | ... | ... | ... | ... | ... | ... | ... | ... |

### Phase B: Compute grammar for everything

For every isotope in the catalogue (products AND decay intermediates):

1. Compute grammar using ATOMICUS canonical formula
2. Cross-check against ATOMICUS isotope files where they exist
3. Verify grammar validity (n_tri ≥ 0, n_deu ≥ 0)
4. Flag any grammar violations

For each product, track the COMPLETE decay chain:

```
Product → (decay mode, t½) → Intermediate → ... → Stable endpoint
```

At each step:
- Record grammar
- Verify grammar rule: EC (Δn_tri = +2, Δn_deu = −3),
  β⁻ (Δn_tri = −1, Δn_deu = +1), α (Δn_deu = −2, Δn_tri = 0)
- Verify consistency

### Phase C: Production rate computation

For each product isotope, compute the equilibrium production rate:

$$q = \\int_0^\\infty \\sigma(E) \\cdot \\phi(E) \\cdot \\rho \\cdot N_A / M \\, dE$$

Where:
- σ(E) = cross-section from EXFOR (interpolated)
- φ(E) = cosmic ray proton differential flux (AMS-02 spectrum,
  corrected for atmospheric depth using exponential attenuation)
- ρ × N_A / M = target number density (atoms/cm³) integrated over
  atmospheric column

Simplification: use the column-integrated yield:
$$Q = \\int_0^{1030} \\rho(x) \\cdot \\sigma(\\bar{E}(x)) \\cdot \\phi(0) \\cdot e^{-x/\\lambda} \\, dx$$

For each product, report Q in atoms/cm²/s.

### Phase D: Validate against measured rates

Compare computed production rates against measured values:

| Isotope | Computed (atoms/cm²/s) | Measured | Ratio | Status |
|---------|----------------------|----------|-------|--------|
| C-14 | ? | 2.02 | ? | ? |
| Be-7 | ? | 0.062 | ? | ? |
| Be-10 | ? | 0.019 | ? | ? |
| H-3 | ? | 0.25 | ? | ? |

A ratio within 0.5–2.0 is acceptable for this level of calculation.
A ratio outside 0.1–10.0 indicates a systematic error.

### Phase E: Grammar analysis of the full inventory

After computing grammar for all products:

1. Are there ANY grammar violations? If so, what does this mean?
2. What fraction of products undergo EC repair vs β⁻ repair vs α decay?
3. Is there a pattern: do products with more displaced neutrons (higher
   spallation damage) require more EC events?
4. Does every EC chain terminate at a nucleus that already exists in
   the ATOMICUS isotope table (i.e., a known stable isotope)?
5. What is the TOTAL neutron budget? Sum over all products: are the
   total neutrons ejected equal to the total neutrons recovered (by
   capture, primarily via N-14(n,p)C-14)?

---

## 4. Required Outputs

1. **Complete product inventory table**: Every isotope produced by
   cosmic ray spallation in Earth's atmosphere, with grammar, decay
   chain, and production rate. Minimum 50 entries.

2. **Grammar validity report**: "X / Y products have valid grammar at
   ALL decay steps." Target: X = Y (100%).

3. **Production rate comparison**: Table matching computed vs measured
   rates for C-14, Be-7, Be-10, H-3.

4. **Neutron conservation check**: Total neutrons ejected in all primary
   spallation vs total neutrons recovered by atmospheric capture.
   Should balance within 10%.

5. **Product classification**: Sort all products into categories:
   - Stable (no decay needed)
   - EC repair (grammar correction)
   - β⁻ repair (triton fraction reduction)
   - β⁺ repair
   - α decay (triton overload)
   - Complex chains (multiple modes)

6. **Atmospheric grammar footprint**: What does cosmic ray spallation
   DO to the atmosphere's overall nuclear grammar? Is it a net grammar
   validator (producing stable configurations) or a net grammar
   disruptor (producing unstable ones that then repair)?

---

## 5. Success Criteria

- [ ] ≥50 unique spallation products catalogued
- [ ] Grammar computed for every product and every decay intermediate
- [ ] 100% grammar validity (any violation is a critical finding)
- [ ] Production rates for C-14, Be-7, Be-10 within factor of 3 of
      measured values
- [ ] Total neutron budget balances within 10%
- [ ] Every product is classified into the grammar repair taxonomy
- [ ] The inventory is self-contained and machine-readable (CSV/TSV)
