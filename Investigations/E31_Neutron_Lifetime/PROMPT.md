# E31: Neutron Lifetime from Lattice Topology — Data/Prompt

## DATA REQUIREMENTS
| Data | Value | Source |
|------|-------|--------|
| Neutron beam lifetime | 888.0 ± 2.0 s | Yue et al. 2013 |
| Neutron bottle lifetime | 878.4 ± 0.5 s | Serebrov 2018 |
| Neutron lifetime discrepancy | ~8.6 s (4.6σ) | The "neutron lifetime puzzle" |
| n → p + e⁻ + ν̄_e Q-value | 0.782 MeV | m_n − m_p − m_e |
| Proton W=3, Neutron W=3 | Same topology | SDT |

## INVESTIGATION PROMPT

**Target**: Derive the neutron lifetime (~880 s) from the SDT topological transition rate: a W=3 uncharged trefoil rearranges to a W=3 charged trefoil + W=1 torus + open winding.

### SDT Interpretation
Beta decay (n → p + e⁻ + ν̄_e) is NOT a "quark transformation." It is:
1. The uncharged W=3 trefoil (neutron) is metastable — it LACKS the ℓ=1 wake stabilisation
2. The trefoil slowly rearranges: it develops an ℓ=1 wake (becomes proton)
3. The excess energy (1.293 MeV) is released as a W=1 torus (electron, 0.511 MeV) + open winding (antineutrino) + kinetic energy
4. The lifetime = 1/(rearrangement rate)

### Key Question
What determines the ~880 s timescale? In SDT:
- The neutron is trapped in a metastable topological state
- The rearrangement requires tunnelling through a topological barrier
- The barrier height relates to the energy cost of creating the ℓ=1 wake
- The rate ∝ exp(−barrier / kT) where T is the neutron's internal circulation "temperature"

### The Lifetime Puzzle
The 8.6 s discrepancy between beam and bottle measurements suggests either:
- SDT: different boundary conditions (lattice coupling in bottle walls vs free space) affect the decay rate
- Standard: dark decay channel n → p + χ (dark particle)
- SDT prediction: does lattice coupling to container walls modify the topological transition rate?

### Success Criteria
- [ ] Neutron lifetime order of magnitude reproduced from topological argument
- [ ] The 8.6 s beam/bottle discrepancy addressed
- [ ] The decay products (p + e + ν̄) explained as topology rearrangement
