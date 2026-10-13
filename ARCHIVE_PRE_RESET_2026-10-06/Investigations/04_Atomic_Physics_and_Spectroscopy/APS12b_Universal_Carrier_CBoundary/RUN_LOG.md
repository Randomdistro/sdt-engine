# APS12b Run Log

**Date:** 2026-08-13  
**Canon edits:** none  
**Calibration policy:** global calibration allowed; held-out prediction required

## Isolation

The collector and instruments read:

- canonical constants copied from `Engine/include/sdt/laws.hpp`;
- `Datasets/nuclear/ionisation_energies.json`;
- `Datasets/nuclear/IAEA_ground_states_radii.csv`;
- APS01's cached measured comparison columns;
- IAEA LiveChart ENSDF gamma responses.

No generated file under APS12 or APS12a is read by any APS12b script.

## Data collection

Command:

`python collect_aps12b_data.py`

Result:

- atomic: 52 rows;
- radii: 908 rows;
- gamma transitions: 3,576 rows;
- exit code 0.

## Carrier run

Command:

`python aps12b_universal_carrier.py`

Result:

- endpoint structural tests completed;
- seven carrier variants plus Ritz and Rydberg comparators evaluated;
- train, H hold-out, element hold-out, series-limit hold-out, and
  multi-electron tables written;
- exit code 0.

Key result: upper/lower endpoint models excluded structurally. Calibrated
two-endpoint carrier fails cross-element prediction. Rydberg/Ritz comparators
dominate held-out accuracy.

## Geometry and opacity run

Command:

`python aps12b_opacity.py`

Result:

- 908/908 radii inside both fixed c-boundaries;
- 3,576 observed gamma transitions inside `q=1`;
- strict zero-gamma opacity excluded;
- ICC benchmark fit on 347 transition rows and tested on 292;
- beta stability and collinearity diagnostics written;
- exit code 0.

## Outputs

- `carrier_structural_tests.csv`
- `carrier_model_summary.csv`
- `carrier_predictions.csv`
- `carrier_results.txt`
- `boundary_geometry.csv`
- `opacity_model_summary.csv`
- `opacity_predictions.csv`
- `opacity_beta_stability.csv`
- `opacity_results.txt`
- `APS12b_ASSESSMENT.md`
