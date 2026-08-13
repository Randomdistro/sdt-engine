# NP12e — Frozen proton centres → point-proton RMS (IAEA sealed)

> **Status:** PRE-REGISTERED — 2026-08-09.  
> **Class:** SDT claim investigation (O2 branch of NP12d).  
> **Upstream:** NP12d — boundary underdetermined; topology layer O2.  
> **Canon edits:** none. **IAEA:** sealed.

## 0. Objective

For a **stated frozen set** of nuclides with executable proton centre tables,
compute

```text
R_{p,RMS}² = (1/Z) Σ_i |r_i − r̄_p|²
```

with IAEA still sealed. This freezes the point-proton second moment where
positions exist. It does **not** supply continuous `ρ_q` (physical charge RMS
remains UNDERDETERMINED).

Also show that unlabelled packing scaffolds (He-4 tetrahedron, 4 nucleon
centres) leave proton-subset choice free: `C(4,2)` assignments span a range of
`R_{p,RMS}` — packing centres alone are not a unique RMS predictor.

## 1. Frozen set (pre-registered)

| Nuclide | Source of proton centres |
|---|---|
| ⁴He | `ATOMICUS/elements/002_Helium_He_2_2.md` coordinate table |
| ⁹Be | `ATOMICUS/elements/004_Beryllium_Be_4_5.md` |
| ¹²C | `ATOMICUS/elements/006_Carbon_C_6_6.md` |
| ¹⁶O | `ATOMICUS/elements/008_Oxygen_O_8_8.md` |

**Amendment 01 (before re-run):** ⁷Li (`003_Lithium_Li_3_4.md`) withdrawn from the
frozen set — table lists only 2 proton rows while Z=3 (`TABLE_INCOMPLETE`). Not
filled in by hand.

Provenance label for these tables: **STATED_ATOMICUS_TABLE** (not re-derived
from `packing.hpp` in this loop; not claimed MEASURED).

Packing diagnostic (not a second prediction channel):

| Scaffold | Source |
|---|---|
| He-4 Tammes-4 tetrahedron | `packing.hpp` `preset_tammes4` centres (unitless geometry → report dimensionless RMS / R_shell) |

## 2. Procedure

1. Validate point-RMS instrument (reuse NP12d discrete fixtures).  
2. Parse each frozen table; require exactly `Z` proton rows.  
3. Compute `R_{p,RMS}` (fm) and `R_boundary(A)` from engine formula (length
   ledger only — no comparison gate to IAEA).  
4. Packing diagnostic: all `C(4,2)` proton assignments on Tammes-4; report
   min/max `R_{p,RMS}/R_shell`.  
5. IAEA file must not be opened.

## 3. Claims

| ID | Claim |
|---|---|
| NP12e-C1 | Instrument validation PASS. |
| NP12e-C2 | All frozen-set tables (Amendment 01: four nuclides) parse with `n_proton = Z`. |
| NP12e-C3 | `R_{p,RMS}` published for each (COMPUTED from STATED tables). |
| NP12e-C4 | Tammes-4 (regular tetra): all `C(4,2)` share one `R_{p,RMS}` (**DEGENERATE** in value). Asymmetric 4-centre fixture: min ≠ max (**UNDERDETERMINED** without labels). |
| NP12e-C5 | Physical charge RMS still **UNDERDETERMINED** (no `ρ_q`). |
| NP12e-C6 | IAEA sealed; no fitted scale; no EMPIRICALLY SURVIVES. |

## 4. Non-claims

- Not Phase B.  
- ATOMICUS tables are not upgraded to DERIVED packing law by this loop.  
- Close-pack `A^{1/3}` boundary construction not re-litigated.
