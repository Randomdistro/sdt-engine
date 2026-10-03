# Q03: Neutron Multiplicity Rule — Data Requirements

## 1. Reaction Channel Data

| Data Point | Source | Purpose |
|-----------|--------|---------|
| (p,1n) threshold energies for targets Z=3–92 | EXFOR / TENDL-2023 | First channel opening |
| (p,2n) threshold energies for targets Z=3–92 | EXFOR / TENDL-2023 | Second channel opening |
| (p,3n) threshold energies for targets Z=3–92 | EXFOR / TENDL-2023 | Third channel opening |
| (p,4n) threshold energies for targets Z=3–92 | EXFOR / TENDL-2023 | Fourth channel opening |
| (p,5n) and higher thresholds where measured | EXFOR | Extended multiplicity |
| Excitation functions σ(E) for each channel | EXFOR | Full energy dependence |
| Maximum multiplicity achieved per target | EXFOR / Literature | Upper limit |
| (α,xn) threshold energies for comparison | EXFOR | Composite projectile case |
| (d,xn) threshold energies for comparison | EXFOR | Lighter composite projectile |

## 2. Target Nucleus Properties

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Neutron separation energies S_1n, S_2n, S_3n, S_4n | AME2020 | Sequential ejection cost |
| Cumulative neutron separation energy Σ S_n | AME2020 | Total cost for x neutrons |
| Target grammar (d, t, n_tri, n_deu) | ATOMICUS/isotopes/ | Construction state |
| Number of triton blocks | ATOMICUS grammar | n_o neutron count |
| Number of "open" neutrons n_o | To be computed | Available loose neutrons |
| Nuclear deformation β₂ | FRDM / Möller et al. | Shape effect on multiplicity |
| Shell closure status (magic N or Z) | NNDC | Rigidity of scaffold |
| Neutron skin thickness (N−Z dependent) | Antiproton annihilation data / PREX | Outer neutron availability |

## 3. Energy Budget Quantities

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Incident proton kinetic energy T_p | Variable (10 MeV–10 GeV) | Driver |
| Q-value for each (p,xn) channel | AME2020 (mass differences) | Energy release/absorption |
| Compound nucleus excitation energy E* | T_p + Q | Available energy for evaporation |
| Average neutron evaporation energy <ε_n> | ~T_nucleus ≈ E*/A | Energy per neutron |
| Level density parameter a = A/8 MeV⁻¹ | Conventional / to be replaced by SDT | Conventional benchmark |

## 4. SDT Geometric Parameters

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Nuclear scaffold bond energies per block type | SDT derivation needed | Cost to detach a d or t block |
| ℓ≥3 coupling energy at nuclear surface | SDT derivation needed | Structure bond strength |
| Convergence pressure at nuclear surface | P_conv × f × geometry | External "squeezing" force |
| k-number of target nucleus | k = c/v_surface | Coupling tightness |
| Beth (c-boundary) of target | R/k² | Interaction boundary |
| Triton open-neutron bond energy | SDT / Triton Overload | n_o detachment cost |
| Triton connecting-neutron bond energy | SDT / Triton Overload | n_c detachment cost |

## 5. Systematic Trends

| Data Point | Source | Purpose |
|-----------|--------|---------|
| (p,xn) multiplicity at fixed energy vs A | EXFOR systematic surveys | Mass dependence |
| (p,xn) multiplicity at fixed energy vs N−Z | EXFOR | Neutron excess dependence |
| (p,xn) multiplicity at fixed energy vs triton fraction | ATOMICUS + EXFOR | Grammar correlation |
| Multiplicity vs nuclear deformation | EXFOR + FRDM | Shape correlation |
| Multiplicity near shell closures (N=20,28,50,82,126) | EXFOR | Rigidity effect |
| Average neutron multiplicity <ν> at 200 MeV | Systematic compilations (Cugnon et al.) | High-energy benchmark |
| Neutron multiplicity distribution P(x) at fixed E | EXFOR / spallation facility data (SINQ, SNS) | Full distribution |

## 6. Spallation Facility Data

| Data Point | Source | Purpose |
|-----------|--------|---------|
| SINQ (PSI) neutron yield measurements | PSI reports | Thick-target multiplicity |
| SNS (ORNL) neutron production data | ORNL reports | High-power spallation benchmark |
| LANSCE (Los Alamos) neutron spectra | LANL reports | Energy + multiplicity data |
| J-PARC spallation neutron data | J-PARC reports | Independent verification |
| Target material: Pb, W, Hg, U | Multiple sources | Heavy target benchmarks |
