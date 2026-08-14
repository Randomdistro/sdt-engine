# APS12a Run Log

**Date:** 2026-08-13  
**Isolation:** APS12a directory only; no APS12/Grok artifact is an input.

## Pre-run commitments

- Prompt completion target: A
- CALIBRATED budget: 0
- Frozen gates: `APS12a_PRE_REGISTRATION.md`
- Instrument: `aps12a_independent.py`
- Hold-outs: `aps12a_holdouts.csv`
- Stdout: `aps12a_results.txt`
- No threshold widening, fitted screening, inverted `Z_eff`, measured-radius
  predictor, or grammar re-sort.

## Execution

### Phase 0a — hold-out freeze

- Rows: 166
- SHA256: `4e3c481f2cffc085809f7b7d8c034749a134fcc6d179cdc07c82799481a1761f`
- Frozen before `aps12a_independent.py` was created.

### Direct execution

- Exit code: 0
- V0: MATCH
- G_EXC_H: MATCH, max 12.5009 ppm
- G_EXC_light: MATCH, max 263.226 ppm
- G_EXC_Fe: EXCLUDED, relative 0.9261%
- G_ION_last: MATCH
- G_ION_S: OPEN; S_bare 3/97, S_ion 14/97
- G_ISO_mass: MATCH, relative 0.0916% on shift
- G_ISO_size: OPEN, sign 2/4
- G_MULTI: table complete
- Parent: not NATIVE-distinct; one-electron CONVERGENCE with high-Z leading
  exclusion and distinct channels OPEN
- Assessment: `APS12a_ASSESSMENT.md`
