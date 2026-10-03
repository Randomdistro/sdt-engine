# A01: Spallation Product Grammar Audit — Data Requirements

## 1. Target-Product Pairs (Complete Catalogue)

For EVERY experimentally confirmed spallation reaction in the EXFOR
database, collect:

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Target isotope (Z, A, N) | EXFOR | Starting point |
| Projectile (p, d, α, n, γ, heavy ion) | EXFOR | Reaction initiator |
| Projectile energy range | EXFOR | Conditions |
| Reaction channel: (p,xn), (p,pxn), (α,xn), etc. | EXFOR | Pathway |
| Product isotope (Z', A', N') | EXFOR | Immediate product |
| Product excitation state (ground, isomeric) | EXFOR / NNDC | Initial state of product |
| Cross-section σ(E) at peak | EXFOR | Yield |

**Minimum scope**: All (p,xn) reactions for x=1–10 on targets Z=3–92
where measured cross-section data exists. Estimated: ~2000 target-product pairs.

## 2. Grammar Data for Each Isotope

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Alpha core count | ATOMICUS formula: α = floor(min(Z,N)/2) | Core structure |
| Deuteron count n_d | ATOMICUS formula | Block count |
| Triton count n_t | ATOMICUS formula | Block count |
| n_tri (triton-derived metric) | ATOMICUS formula: N − Z | Triton imbalance |
| n_deu | ATOMICUS formula: Z − 2×α − n_t | Deuteron count |
| Grammar validity check: n_tri ≥ 0 AND n_deu ≥ 0 | Computed | Pass/fail |

Must be computed for:
- Every target isotope
- Every immediate product isotope
- Every decay-chain intermediate
- Every stable endpoint

## 3. Decay Chain Data

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Product decay mode (EC, β⁺, β⁻, α, stable) | NNDC / NUBASE2020 | Repair pathway |
| Half-life of product | NNDC | Timescale |
| Daughter isotope | NNDC | Next step |
| Number of steps to stable endpoint | NNDC | Chain length |
| Stable endpoint isotope (Z_final, A_final, N_final) | NNDC | Terminal state |
| Grammar of stable endpoint | ATOMICUS / compute | Terminal grammar |

## 4. Neutron Budget Quantities

| Data Point | Source | Purpose |
|-----------|--------|---------|
| N_target (neutrons in target before spallation) | Z, A data | Starting neutron count |
| N_product (neutrons in immediate product) | Z', A' data | Post-spallation neutron count |
| Number of neutrons ejected: x = N_target − N_product + ΔZ | Computed | Ejection count |
| N_endpoint (neutrons in stable endpoint) | Z_final, A_final data | Final neutron count |
| Number of EC events in decay chain | Count from NNDC | Repair count |
| Verify: N_endpoint = N_target ? | Computed | Neutron budget identity (E20) |

## 5. Archival Sources

| Database | Specific Tables Needed |
|----------|----------------------|
| EXFOR | All entries with keyword "spallation" or reaction type (p,xn) for x≥1 |
| NNDC/NuDat3 | Decay radiation data for all radioactive products |
| NUBASE2020 | Ground state properties (mass excess, half-life, decay mode) |
| AME2020 | Atomic masses for Q-value computation |
| ATOMICUS/isotopes/ | Grammar files for Z=1–92 stable isotopes |
| TENDL-2023 | Theoretical cross-sections where EXFOR has gaps |
