# E20: Spallation Neutron Budget Verification

> Source: [INV 17 §9](../ATOMICUS/EC%20Investigations/INVESTIGATION_17_Spallation_Damage_EC_Repair.md)
> SDT Finding: #29

---

## 1. Background

SDT analysis of (p,2n) spallation products reveals an exact neutron
budget identity: the neutron count of the target equals the neutron
count of the stable endpoint.

```text
Ga-69(p,2n)Ge-68:  N_target = 38 → N_product = 36 → N_endpoint = 38 (Zn-68)
Y-89(p,2n)Zr-88:   N_target = 50 → N_product = 48 → N_endpoint = 50 (Sr-88)
```

The 2 neutrons ejected in spallation are exactly recovered by 2 EC
events (proton → neutron). The system returns to the same N.

This identity has been verified for (p,2n) reactions. It has NOT been
systematically verified for other reaction channels: (p,3n), (p,4n),
(α,2n), (α,3n), (d,2n), etc.

## 2. SDT Prediction

For ANY spallation reaction that produces an EC-decaying product,
the number of EC events in the subsequent decay chain equals the
number of "excess" protons relative to the stable endpoint. This
number is NOT always equal to the number of ejected neutrons — it
depends on the reaction channel:

| Reaction type | Ejected | Z change | EC events | N_target = N_endpoint? |
|--------------|---------|---------|-----------|----------------------|
| (p,2n) | 2n | +1 | 2 | YES |
| (p,3n) | 3n | +1 | 3 | NO (N_end = N_target − 1) |
| (α,3n) | 3n | +2 | 2 | NO (N_end = N_target − 1) |
| (d,2n) | 2n | +1 | 2 | YES |

The prediction is: **the number of EC events equals ΔZ between
product and stable endpoint**, independent of the number of
ejected neutrons.

## 3. Observable

### Part I: Literature survey
For each of the 56 EC isotopes in the master table, identify the
production reaction (where artificial) and compute:
- N_target
- N_product
- Number of ejected neutrons
- Number of EC events to stability
- N_endpoint
- Verify: EC events = ΔZ_product − ΔZ_endpoint

### Part II: Cross-channel verification
For isotopes producible via multiple reaction channels (e.g.,
Ge-68 can be made by Ga-69(p,2n) OR Zn-66(α,2n)), verify that
the same isotope requires the same number of EC events regardless
of production channel. The product is the same atom — only the
neutron budget of the production differs.

### Part III: Extended (p,xn) series
Produce members of the A=68 chain via systematic (p,xn) reactions:
- Ga-69(p,2n)Ge-68 → 2 EC
- Ge-70(p,3n)As-68 → 3 EC
- As-75(p,8n)Se-68 → 4 EC (if achievable)

Verify that EC count = ΔZ for each product, and that the endpoint
is always Zn-68 (stable).

## 4. Apparatus

### Part I
No apparatus needed. Literature/database analysis using NNDC,
NUBASE2020, and reaction cross-section databases (EXFOR, TENDL).

### Parts II & III
- Proton or α-beam accelerator
- Target assembly (Ga, Ge, As foils or oxides)
- Gamma spectrometry for product identification and decay chain
  monitoring
- Radiochemical separation for isotope purification

## 5. Feasibility

**Difficulty: LOW (Part I), MODERATE (Parts II, III)**

- Part I is a purely computational/archival exercise. Can be done
  immediately with existing nuclear data tables.
- Part II requires access to an accelerator with multiple beam
  types (proton, deuteron, α). Most nuclear physics facilities
  (e.g., TRIUMF, iThemba, Jyvaskyla) can provide this.
- Part III requires high-energy protons (>50 MeV) for the (p,8n)
  reaction on As-75. This is at the limit of standard cyclotrons.

## 6. Impact

- **If identity holds universally**: Confirms that EC is a
  deterministic repair mechanism that restores the nucleus to a
  specific stable configuration. The number of repairs equals
  the structural deficit (ΔZ), regardless of how the deficit
  was created. Strengthens the SDT grammar framework.
- **If exceptions found**: Identifies reaction channels where the
  EC chain does not terminate at the expected endpoint — possibly
  due to competing β⁺ decay exhausting the proton excess before
  all vacancies are filled, or due to intermediate isomeric states
  that bypass the EC channel.
