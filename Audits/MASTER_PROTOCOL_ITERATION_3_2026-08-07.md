# Master-Protocol Iteration 3 — 2026-08-07

**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Canon edits:** none  
**Executable loop:** GOM27 (shared-profile deflection)

## Evidence-input rule (binding)

Codebase audits are not inputs. This iteration uses:

- GOM26 calibration `ϟ = 1476.351201 m` from `.audit-tmp/gom26_run.txt` + Horizons 2025;
- `Engine/include/sdt/laws.hpp` as hypothesis (`c_far`, `measured::R_Sun`);
- frozen Fomalont PDF/HTML and Cassini ODF/TDF checksums;
- direct `.audit-tmp/gom27_run.txt`.

Prior `Audits/*.md` and prior deflection-folder assessments are not used for numbers or status.

## Claim-graph update (direct only)

| Root | Status after Iteration 3 |
|---|---|
| R1 IC (ϟ invariant) | RECOVERED (GOM26) — carried as frozen input, not re-litigated |
| R1 spectral | UNADJUDICATED (unchanged; not re-run) |
| R1 deflection δ(b) | COMPUTED ledger published; empirical **PENDING_DATA** |
| R1 delay D4 | PENDING_DATA (ODF/TDF frozen; residual not reconstructed) |

## Checklist

1. Pre-registration — `GOM27/.../PROMPT.md`  
2. Instrument validation A–D — PASS  
3. Execute — `.audit-tmp/gom27_run.txt`  
4. Assessment — `GOM27_ASSESSMENT.md`  
5. Next — absolute VLBI δ vs elongation, or Cassini residual pipeline  

## Headline numbers

| Quantity | Value | Label |
|---|---:|---|
| Limb δ | 1.750844 arcsec | COMPUTED |
| 4ϟ/R_Sun | 1.750866 arcsec | DERIVED weak-field |
| Max |δ−4ϟ/b|/(4ϟ/b) on scan | 2.1×10⁻⁴ | COMPUTED |

## Framework ledger (data-admissible cumulative)

| Bucket | Entries |
|---|---|
| Empirically surviving | GOM26-C1; GOM26-C4 |
| Empirically excluded | (none) |
| COMPUTED predictions | GOM27 δ(b) scan |
| Unadjudicated | spectral mechanism; limb single-point note |
| Pending data | absolute δ(b) table; Cassini residual |
| Next tests | (1) absolute VLBI deflection table (2) Cassini D4 residual (3) direct benchmark re-trace |
