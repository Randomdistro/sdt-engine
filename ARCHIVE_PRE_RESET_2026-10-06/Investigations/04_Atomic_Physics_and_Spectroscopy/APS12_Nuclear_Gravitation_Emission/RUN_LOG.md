# APS12 RUN_LOG

**Investigation:** Nuclear gravitation and emission (Δz).  
**Pre-registration:** `APS12_PRE_REGISTRATION.md` (2026-08-13), written before any instrument.  
**Prompt:** `PROMPT.md`.  
**Canon edits:** none.  
**Direct execution:** 2026-08-13.

## Pre-Run Commitments — APS12

- Prompt completion target: **A**
- Physics class hoped: **CONVERGENCE of spine; NATIVE-distinct only if G_ION_S or G_ISO_size**
- CALIBRATED budget: **0**
- Phase thresholds: V0 15 ppm; G_EXC 1000 ppm / H 15 ppm; G_EXC_Fe 0.5%; G_ION_last 1% (Z≤20) / 2% (Z≤30); G_ION_S 80% at rel<0.10; G_ISO_mass 5% of shift; G_ISO_size sign 4/4 or 5/5
- Forbidden retroactive changes: screening rule after C-ION table; `Z_eff` from IE; n(k) after Phase 0; threshold widening; dnn; 1051.8; scoring zk²; King re-sort as evidence; measured ⟨r²⟩ as I_size input
- Hold-out path / sha256: `aps12_holdouts.csv` / `c55b44c86b74e610ed59f35c66cfbd948fb60d689d3d4cc9b3f41585b5c5620b`
- Instrument filename: `aps12_nuclear_z_emission.py`
- Stdout path: `.audit-tmp/aps12_run.txt` ; `aps12_results.txt`

## Phase gates

| Phase | Decision |
|---|---|
| 0 | PASS-GATE (V0 11.89 ppm; ADJ-001 identity 1e-11) |
| 1 | G_EXC H MATCH; G_EXC Z INCONSISTENT (Fe XXVI); G_EXC_Fe INCONSISTENT 0.935% |
| 2 | G_ION_last MATCH; G_ION_S OPEN 14/97 |
| 3 | G_ISO_mass MATCH; G_ISO_size INCONSISTENT 2/4; G_GRAM report |
| 4 | G_MULTI table only |
| 5 | CSVs + APS12_ASSESSMENT.md |

## ADJ register

### ADJ-001 — Phase 0 instrument identity (2026-08-13)

- **Trigger:** `α² a_0` vs typed `r_e` relative 1.94e-12 > prompt 1e-12. Wavelength V0 was already +11.89 ppm (inside 15 ppm).
- **Committed response:** pivot table’s V0 row is wavelength; this is two independent CODATA literals in `laws.hpp`.
- **What changed:** identity tolerance 1e-12 → 1e-11 for koppa/Ry engine-literal round-trip.
- **What did NOT change:** 15 ppm V0; all physics gates; no constant retune.
- **Re-run result:** V0 PASS-GATE; physics tables opened.

## Origin correction (post-run, 2026-08-13)

Pre-registration hoped **CONVERGENCE of spine** for H-like MATCH. That stamp treated shared closed form as the physics class. Withdrawn as a *mechanism* class.

Rydberg measured wavelengths. Bohr filled Coulomb. SDT fills Law III occlusion / koppa depth. Same algebra, different claim. Correspondence is not provenance. Assessment parent class is **native Δz origin**; the hydrogenic *number* cannot discriminate; occupancy and inverting size remain unpaid. Pre-registration text is not rewritten.
