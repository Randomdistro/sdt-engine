# E09: Le Sage Thermal Budget — Data/Prompt

## DATA REQUIREMENTS
| Data | Value | Source |
|------|-------|--------|
| Solar luminosity | 3.828×10²⁶ W | IAU 2015 |
| Solar convergence absorbed | L_conv = ∫ F_conv · dA over solar surface | SDT derivation |
| CMB flux F_CMB | 3.131×10⁻⁶ W/m² | law_II |
| Solar surface area | 6.08×10¹⁸ m² | From R_Sun |
| Total intercepted CMB | F_CMB × πR²_Sun ≈ 4.77×10⁷ W | Computed |
| Earth thermal budget | 173 PW solar + 47 TW geothermal | Measured |
| Convergence heating prediction | Depends on occlusion fraction | To compute |

## INVESTIGATION PROMPT

**Target**: Compute the thermal budget of an eclipsing body in the convergence field. Does convergence absorption produce detectable heating?

### The Le Sage Problem
If gravity = convergence occlusion, then matter absorbs convergence flux. Absorbed flux → heating. Classical Le Sage theories fail because the required absorption would melt everything. SDT resolves this because:

1. The transfer function f = 2.125×10⁻¹⁷ means only a TINY fraction of convergence is coupled
2. The convergence flux is recycled (re-radiated), not absorbed as heat
3. The heating rate is: P_heat = f × P_conv × V_disp × (number of nucleons)

### Calculation
1. Compute total convergence power intercepted by Earth: (π R_E²) × P_conv × c × f
2. Compare to geothermal heat flow (47 TW)
3. If convergence heating << geothermal: Le Sage heating is undetectable (SDT passes)
4. If convergence heating >> geothermal: SDT has a heating problem

### Success Criteria
- [ ] Convergence heating rate computed for Earth
- [ ] Ratio to geothermal heat quantified
- [ ] Either: heating is negligible → no Le Sage problem; OR: mechanism for recycling identified
