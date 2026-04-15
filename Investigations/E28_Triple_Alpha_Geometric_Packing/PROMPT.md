# E28: Triple-Alpha Rate from Geometric Packing — Data/Prompt

## DATA REQUIREMENTS

| Data | Value | Source |
|------|-------|--------|
| C-12 ground state mass | 12.000000 u (definition) | AME2020 |
| He-4 mass | 4.002603 u | AME2020 |
| 3 × He-4 mass | 12.007809 u | Computed |
| Mass excess = 3×m_α − m_C12 | 7.275 MeV | Q-value |
| Hoyle state energy | 7.654 MeV above C-12 g.s. | Measured |
| Hoyle state width | 8.5 eV | Measured |
| C-12 grammar | 1 alpha + 4 deuterons | ATOMICUS/006_C12.md |
| Alpha geometry | Tetrahedral (2p+2n) | SDT |

## INVESTIGATION PROMPT

**Target**: Derive the Hoyle state energy (7.654 MeV) from the geometric packing energy of 4 deuterons closing around an alpha core.

### SDT Interpretation

C-12 is NOT three alphas. It is 1 alpha core + 4 deuterons (α + 4d). The "triple-alpha" process is actually:
1. α + α → Be-8* (unstable — immediately decays unless...)
2. α + Be-8* → C-12* (Hoyle state) → C-12 + γ

SDT re-reads this as:
1. Two alpha cores approach → their ℓ≥3 wakes overlap → forms Be-8 (2α, no deuterons)
2. Be-8 grammar: 2α + 0d is UNSTABLE in SDT (no scaffold bonds — two standalone alphas)
3. A third alpha approaches → the combined 12 nucleons rearrange into α + 4d (C-12 grammar)
4. The 7.654 MeV Hoyle state = the geometric threshold for tetrahedral closure of the 4 deuterons around the central alpha

### Calculation

1. Compute the tetrahedral closure energy: 4 deuterons at the vertices of a tetrahedron surrounding a central alpha → the packing energy when the deuterons lock into their scaffold positions
2. Energy = sum of all d-α occlusion bonds + d-d occlusion bonds − Coulomb repulsion between the 4 deuterons' protons
3. Compare to 7.654 MeV

### Success Criteria
- [ ] Hoyle state energy derived within 20% of 7.654 MeV
- [ ] The instability of Be-8 explained by grammar (2α + 0d = unbonded)
- [ ] The C-12 grammar (α + 4d) confirmed as the stable endpoint
