# A01: Spallation Product Grammar Audit — Investigation Prompt

> **Classification**: Archival data computation (no laboratory work)
> **Prerequisites**: Nuclear construction grammar, EXFOR access
> **Output format**: Master table + statistical analysis

---

## 1. Objective

Compute the SDT nuclear construction grammar (alpha core, deuteron count,
triton count, n_tri, n_deu) for EVERY known spallation product and verify:

1. **Grammar validity**: Every spallation product has n_tri ≥ 0 and
   n_deu ≥ 0 (grammar is valid at every step)
2. **Neutron budget identity**: For (p,xn) reactions, N(target) = N(endpoint)
   (extends E20 beyond the 2 known cases)
3. **Grammar trajectory**: The sequence of grammar states from product
   through decay chain to stable endpoint follows the known grammar
   rules (EC: Δn_tri = +2, Δn_deu = −3; β⁻: Δn_tri = −1, Δn_deu = +1)

---

## 2. Scope

### Tier 1 (Mandatory): All confirmed (p,xn) products
- Every isotope produced by proton-induced spallation in EXFOR
- For x = 1 through x = 10 (or maximum measured)
- Targets: Z = 3 (Li) through Z = 92 (U)
- Estimated: ~500–1000 unique products

### Tier 2 (Required): All confirmed (α,xn) products  
- Every isotope produced by alpha-induced spallation
- More complex: projectile contributes 2p+2n
- Estimated: ~200–400 unique products

### Tier 3 (If time permits): Heavy-ion products
- Products of (¹²C, xn), (⁴⁰Ar, xn), etc.
- Most complex grammar tracking (composite projectile)
- Estimated: ~100–200 unique products

---

## 3. Methodology

### Step 1: Extract all (p,xn) reactions from EXFOR

Query EXFOR for all entries matching:
- Projectile: proton
- Reaction: (p,n), (p,2n), (p,3n), (p,4n), (p,5n), (p,6n), (p,7n),
  (p,8n), (p,9n), (p,10n)
- Any target
- Cross-section measurement type (not just excitation function shape)

For each entry, record:
- Target: Z_t, A_t, N_t = A_t − Z_t
- Product: Z_p = Z_t + 1, A_p = A_t − x + 1, N_p = N_t − x
- (Verify Z_p, A_p against EXFOR product field — some reactions produce
  different products due to isomeric states or competing channels)

### Step 2: Compute grammar for every isotope

For each isotope encountered (target, product, intermediate, endpoint),
compute:

```
alpha_core = floor(min(Z, N) / 2)
remaining_Z = Z − 2 × alpha_core
remaining_N = N − 2 × alpha_core

If remaining_Z ≤ remaining_N:
    n_d = remaining_Z   (each paired as p+n with a remaining neutron)
    n_t = remaining_N − remaining_Z  (wait — this isn't right)
```

**USE THE EXACT GRAMMAR FORMULA FROM ATOMICUS**. Do not improvise.
Cross-check against at least 10 known ATOMICUS isotope files to validate
the formula.

Compute: n_tri = N − Z (or the equivalent per ATOMICUS convention)
Compute: n_deu = (cross-check formula)

### Step 3: Track decay chains

For each spallation product that is radioactive:

1. Look up the decay mode from NNDC
2. If EC: apply grammar rule (Z → Z−1, N → N+1, Δn_tri = +2, Δn_deu = −3)
3. If β⁻: apply grammar rule (Z → Z+1, N → N−1, Δn_tri = −1, Δn_deu = +1)
4. If β⁺: apply grammar rule (same as EC for grammar purposes)
5. If α: apply grammar rule (Z → Z−2, N → N−2, Δn_deu = −2, Δn_tri = 0)
   per Triton Overload
6. Continue until stable endpoint is reached

At EVERY step, verify:
- n_tri ≥ 0
- n_deu ≥ 0
- Grammar rules produce consistent Z, A, N

### Step 4: Neutron budget verification

For each (p,xn) reaction:
- Record N_target, N_product, N_endpoint
- Compute: Does N_endpoint = N_target?
- If not, compute: ΔN = N_endpoint − N_target and identify the source
  of the discrepancy (competing decay channels? isomeric branching?)

### Step 5: Statistical summary

Compute:
- Total number of products audited
- Percentage with valid grammar at every step: should be 100%
- Percentage satisfying neutron budget identity: should be ~100% for
  pure (p,xn) chains
- Any EXCEPTIONS: list them explicitly with full grammar trace

---

## 4. Required Outputs

1. **Master table** (CSV-compatible):

   | Target | Reaction | Product | Product_d | Product_t | Product_n_tri | Product_n_deu | Valid? | Endpoint | Endpoint_d | Endpoint_t | N_target | N_endpoint | N_budget_OK? |
   |--------|----------|---------|-----------|-----------|---------------|---------------|--------|----------|------------|------------|----------|------------|--------------|
   | Ga-69 | (p,2n) | Ge-68 | ... | ... | ... | ... | YES | Zn-68 | ... | ... | 38 | 38 | YES |
   | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... | ... |

2. **Exception report**: Any product or intermediate with invalid grammar
   (n_tri < 0 or n_deu < 0). If none exist, state "ZERO EXCEPTIONS"
   prominently.

3. **Summary statistics**:
   - Products audited: N₁
   - Grammar valid at all steps: N₂ / N₁ (%)
   - Neutron budget satisfied: N₃ / N₁ (%)
   - Average EC chain length by reaction type
   - Correlation between neutron multiplicity x and EC chain length

4. **Findings narrative**: 1-page summary of what the audit reveals
   about SDT grammar's universality across spallation products.

---

## 5. Success Criteria

- [ ] ≥500 unique spallation products audited
- [ ] Grammar validity at every step: 100% (ANY exception is a finding)
- [ ] Neutron budget identity verified for ≥50 (p,xn) reactions
- [ ] All grammar computations use the canonical ATOMICUS formula
- [ ] Master table is machine-readable (CSV or TSV)
- [ ] Exception report is honest — if any grammar violations exist,
      they must be reported and analysed, not hidden
