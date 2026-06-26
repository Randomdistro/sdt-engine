# E16: Se-68 Cascade Timer — Selective Step Arrest

> Source: [INV 17 §12 Q4](../ATOMICUS/EC%20Investigations/INVESTIGATION_17_Spallation_Damage_EC_Repair.md)
> SDT Finding: #28 (quadruple EC chain)

---

## 1. Background

Se-68 undergoes the longest known EC cascade: four successive
EC/β⁺ events before reaching stable Zn-68.

```text
Se-68 → As-68 → Ge-68 → Ga-68 → Zn-68 (stable)
t½:  35.5 s   151 s   270.9 d  67.7 min
Z:   34       33      32       31       30
```

Each step has a distinct half-life spanning 4 orders of magnitude.
If individual steps can be selectively halted by ionisation (removing
the electrons needed for EC), the cascade becomes an externally
controllable sequential timer with 4 independent stages.

## 2. SDT Prediction

At any point in the cascade, ionising the current isotope to a
bare charge state halts EC for that step. Re-supplying electrons
(recombination) resumes the cascade.

Predicted control matrix:

| Ion state | Se-68 EC | As-68 EC | Ge-68 EC | Ga-68 EC |
|-----------|---------|---------|---------|---------|
| Neutral | active | active | active | active |
| Se³⁴⁺ (bare) | **HALTED** | — | — | — |
| As³³⁺ (bare) | — | **HALTED** | — | — |
| Ge³²⁺ (bare) | — | — | **HALTED** | — |
| Ga³¹⁺ (bare) | — | — | — | **HALTED** |

The cascade can be frozen at any intermediate step by maintaining
the current isotope in a fully stripped state.

## 3. Observable

### Part I: Freeze at Ge-68
1. Produce Se-68 (heavy-ion reaction)
2. Allow first 2 EC events (Se→As→Ge) to proceed (~5 minutes total)
3. Fully strip Ge-68 to Ge³²⁺
4. Store in ESR/CRYRING
5. Verify: no EC events during storage (Ge-68 half-life should be
   effectively infinite while bare)
6. Inject electrons (recombination)
7. Verify: EC resumes, Ga-68 daughter appears

### Part II: Cascade timing measurement
1. Produce Se-68, store as Se³⁴⁺ (bare)
2. Release electrons → cascade begins
3. Measure timing of each successive EC event
4. Compare half-lives to neutral-atom values
5. Determine whether recombination-initiated EC shows identical
   or modified half-lives

## 4. Apparatus

- Heavy-ion accelerator (GSI/FAIR SIS18 or RIKEN RIBF) for Se-68
  production
- Gas-filled separator for isotope selection
- Stripping foil or ECR charge breeder for full ionisation
- Storage ring (ESR or CRYRING) with electron cooler
- Schottky detector or particle detector for daughter identification
- Electron target for controlled recombination

## 5. Feasibility

**Difficulty: HIGH**

- Se-68 has t½ = 35.5 s; must be produced, ionised, injected, and
  stored within ~30 seconds. This is at the edge of current fast
  beam preparation capabilities but has been demonstrated for
  similar short-lived isotopes at GSI.
- The key technical challenge is the fast injection cycle.
- Once Ge-68 is stored (t½ = 270.9 d), the measurement is
  straightforward — long storage time allows excellent statistics.
- Part II requires precise timing correlation between recombination
  and subsequent EC events. The ~68-minute Ga-68 half-life is
  well-suited for storage ring measurement.

## 6. Impact

- **If cascade arrest confirmed**: Demonstrates external control of
  nuclear decay chain timing. The Se-68 cascade becomes a
  4-stage programmable nuclear timer with applications in:
  - Nuclear chronometry (4 independent time references)
  - Controlled radioactive decay for materials science
  - Proof-of-principle for ionisation-gated nuclear batteries
- **If cascade NOT arrestable**: Indicates that EC can proceed
  via alternative channels even in fully stripped ions (e.g.,
  from virtual electron-positron pairs). This would be a
  discovery in itself.
