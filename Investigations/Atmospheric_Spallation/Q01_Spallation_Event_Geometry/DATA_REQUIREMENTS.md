# Q01: Spallation Event Geometry — Data Requirements

## 1. Incident Proton Properties

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Proton radius R_p | CODATA / SDT (4ℏ/m_p c = 0.84124 fm) | Displacement volume of projectile |
| Proton V_disp | SDT derivation (3m_p ℓ_P³ c²/Φ) | Exclusion region geometry |
| Proton winding number W = 3 | SDT (Theory/03_Open_Problems.md) | Topological identity of projectile |
| Movement budget partition at various KE | SDT (v_circ² + v² = c²) | How much circulation remains at impact |
| Typical cosmic ray proton energies | Literature: 10 MeV → 10²⁰ eV | The energy range to model |
| Cosmic ray energy spectrum (differential flux) | PDG Review / AMS-02 / PAMELA | Weighting function for spallation rates |

## 2. Target Nucleus Properties (for each target Z=1–92)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Nuclear construction grammar (d, t counts) | ATOMICUS/isotopes/*.md | Scaffold structure before impact |
| Nuclear charge radius R_nuc | NNDC / Angeli & Marinova 2013 table | Geometric cross-section baseline |
| Nuclear binding energy (total, per nucleon) | AME2020 (Atomic Mass Evaluation) | Energy budget of scaffold |
| Shell structure (magic numbers, shell closures) | NNDC level schemes | Which shells are occupied/full |
| n_tri and n_deu values | ATOMICUS grammar (computed) | Grammar state before impact |
| Ionisation energies IE₁ through IE_Z | NIST ASD | Shell boundary mapping (per INV 17 §7) |
| Electron binding energies (K, L, M shells) | X-Ray Data Booklet (LBNL) | Nuclear-electron shell correspondence |

## 3. Reaction Outcome Data

| Data Point | Source | Purpose |
|-----------|--------|---------|
| (p,xn) cross-sections σ(E) for x = 1,2,3,4,5 | EXFOR database | Which channels open at which energy |
| (p,xn) threshold energies | EXFOR / TENDL-2023 | Minimum energy for each multiplicity |
| Product isotope identification | EXFOR / NNDC | What is created |
| Product excitation state (ground vs excited) | NNDC level schemes | Whether product is born excited |
| Neutron energy spectra from spallation | EXFOR / Los Alamos data | Energy distribution of ejected neutrons |
| Angular distribution of ejecta | EXFOR | Directionality of neutron release |
| Compound nucleus formation cross-section | EXFOR | Whether the proton is fully absorbed first |
| Direct knockout vs compound nucleus fraction | Literature (Serber model papers) | Mechanism partitioning |

## 4. Post-Impact Data

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Product nucleus grammar (d, t) after impact | Compute from ATOMICUS | Grammar state after damage |
| Product nucleus decay mode | NNDC / NUBASE2020 | Does it EC, β⁺, β⁻, or α? |
| Number of EC events to stability | EC_data/13_Spallation_EC_Chains.md | Repair chain length |
| Neutron budget identity (N_target vs N_endpoint) | E20 data | Conservation check |

## 5. SDT Framework Quantities

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Convergent pressure P_conv | Theory/02_Inputs_and_Derivations.md | Background lattice pressure |
| Effective pressure P_eff | Theory/02_Inputs_and_Derivations.md | Occlusion-scale force pressure |
| Transfer function f = P_eff/P_conv | Theory/02_Inputs_and_Derivations.md | Coupling ratio |
| Traction fraction τ = 1/3 | Theory/00_Ruleset.md | Isotropic stress partition |
| Wake multipole structure (ℓ=0,1,2,3+) | Theory/04_Notation.md | Force hierarchy at nuclear scale |
| k-number of proton at various velocities | k = c/v | Coupling strength parameter |
| Beth (c-boundary) of target nuclei | ℛ = R/k² | Maximum interaction radius |

## 6. Archival Databases Required

| Database | URL | Items Needed |
|----------|-----|-------------|
| EXFOR | www-nds.iaea.org/exfor | All (p,xn) cross-sections for targets Z=3–92 |
| NNDC/NuDat | www.nndc.bnl.gov/nudat3 | Level schemes, decay modes, half-lives |
| NUBASE2020 | via AME2020 | Ground state properties of all nuclides |
| AME2020 | via IAEA | Atomic masses, binding energies |
| NIST ASD | physics.nist.gov/asd | Ionisation energies for all elements |
| TENDL-2023 | tendl.web.psi.ch | Evaluated nuclear data, neutron spectra |
| PDG | pdg.lbl.gov | Cosmic ray spectrum, proton properties |
| LBNL X-Ray Data Booklet | xdb.lbl.gov | Electron binding energies |
