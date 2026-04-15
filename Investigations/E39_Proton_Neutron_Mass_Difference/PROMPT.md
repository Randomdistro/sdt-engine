# E39: Proton-Neutron Mass Difference from Topology — Investigation Prompt

> **Classification**: Theoretical derivation
> **Experiment file**: Experiments/E39_Proton_Neutron_Mass_Difference_from_Topology.md
> **Target**: Derive Δm = 1.293 MeV from topological argument

---

## 1. The Question

Both proton and neutron are W=3 trefoil tori. The proton is charged (has ℓ=1 wake), the neutron is not. Yet the neutron is HEAVIER by 1.293 MeV. Why?

In SDT, mass = Φ V_disp / (3 l_P³ c²). So the neutron has a LARGER exclusion volume. The question is: what topological property of the uncharged trefoil gives it a larger V_disp?

## 2. Hypotheses

### Hypothesis A: Missing ℓ=1 wake → Redistributed energy
The proton's ℓ=1 wake (Coulomb field) extends to infinity and carries energy. This energy is OUTSIDE V_disp — it's in the wake, not the body. The neutron, lacking the ℓ=1 wake, has all its energy concentrated in the body (higher V_disp).

Test: Coulomb self-energy of the proton = α ℏc / R_p ≈ 1.71 MeV. If the proton's ℓ=1 wake carries ~1.71 MeV externally, and the neutron retains this energy internally:
Δm_predicted = (some fraction of) 1.71 MeV. Does ~1.293 / 1.71 = 0.756 correspond to a geometric factor?

### Hypothesis B: Different circulation partition
Without the ℓ=1 wake constraining the external pressure profile, the neutron's trefoil equilibrium settles at a slightly different R/a ratio, giving a different V_disp.

### Hypothesis C: Charge stabilisation
The proton's charge (ℓ=1 wake) provides additional stabilisation that slightly compresses V_disp. Remove charge → V_disp expands by ΔV → mass increases by Δm.

## 3. Methodology

1. Compute proton electromagnetic self-energy: E_em = α ℏc / R_p
2. Compute what fraction of E_em is "outside" vs "inside" V_disp
3. For the neutron: E_em = 0 externally, all retained internally
4. Δm = E_em(external) / c² → compare to 1.293 MeV
5. If this doesn't match: investigate the R/a equilibrium shift

## 4. Success Criteria

- [ ] A specific topological mechanism identified for the mass difference
- [ ] Δm predicted within 20% of 1.293 MeV
- [ ] The mechanism explains WHY the uncharged particle is heavier (not lighter)
- [ ] Consistent with the W+1 radius conjecture (both W=3)
