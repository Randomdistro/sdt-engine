# GOM27 D5 BF080 Archive-Catalogue Results

**Date:** 2026-08-07  
**Scope:** provenance and reconstructability audit. No solar-deflection number,
PPN parameter, or SDT residual is calculated.

## Frozen inputs

| File | SHA-256 | Role |
|---|---|---|
| `nrao_bf080_obscore_catalogue.csv` | `d5116e07f356015ae4211b0842c6d8b992af87adc41e98c50a46a2172688497d` | NRAO observational archive metadata |
| `nrao_vlba_data_retrieval.html` | `f4a4405297dd1fe72ab6dc89417e80dba96889a6e1b2a9632ad5079d167d9112` | raw-product and calibration-access documentation |
| `nrao_tap_scripted_access.html` | `74264f370f81db999d6e3d4249f4711476cba4b4178062b123da24fe8372b80c` | TAP metadata-access limitation |

All are listed in `Datasets/solar_propagation_2026-08/MANIFEST.md` before this
audit was run. Their checksums are verified by
`gom27_d5_bf080_catalogue_audit.py`.

## Reproducible campaign identification

The 11,400-row extract contains only project `BF080`. The four experiment
sources are present: `3C279` (4,791 rows), `J1246-0730` (1,748),
`J1248-0632` (1,675), and `J1304-0346` (1,635). Restricting those rows to the
reported observation window yields exactly these eight UTC dates:

`2005-10-01`, `2005-10-05`, `2005-10-06`, `2005-10-07`, `2005-10-09`,
`2005-10-10`, `2005-10-11`, and `2005-10-18`.

The catalogue marks 66 candidate products as public `Execution Block` records.
Their reported size sum is `5,102,265,600` in the archive's reported size
field. This verifies campaign identity and public raw-product discovery, not
the contents or calibration of those products.

## Falsification and correction

The former broad label `PENDING_DATA` is too coarse for this path. It is false
that the relevant raw campaign is unidentified: `BF080` is an exact archival
candidate. It would be equally false to say that the catalogue is an absolute
deflection dataset. It contains no angular-offset, uncertainty, solar-elongation,
or impact-parameter field.

The classification is therefore corrected to
**`PENDING_RECONSTRUCTION`**. This is a data-chain result only; it neither
supports nor excludes GOM27's computed deflection curve.

## Mechanism and remaining initial conditions

The owed observable is an uncertainty-bearing differential angular position (or
phase-delay-derived equivalent) at stated solar offsets. An uncalibrated VLBA
execution block cannot supply that observable by itself. The frozen NRAO
documentation states that TAP identifies products but does not download them;
the archive web flow stages VLBA FITS-IDI/UVFITS products, and calibration must
be performed separately.

Before any model comparison, freeze and validate:

1. the selected BF080 product identifiers and raw checksums;
2. a calibrated visibility/phase pipeline with fringe, clock, station, source
   structure, tropospheric, ionospheric, and solar-coronal handling specified;
3. the reference-source convention, time scale, and independently derived
   solar elongation for every retained session;
4. angular-offset uncertainties and their covariance; and
5. a blind separation between calibration validation and the GOM27 residual
   calculation.

No gamma/PPN-deflection correction may be applied as a data input. If a
necessary calibration step is only available through such a correction, that
product is `MODEL-PROCESSED / EXCLUDED` for this comparison.

## Next action

Use the NRAO Archive Access Tool to stage a fixed, documented BF080 subset.
The archive's scripted TAP interface cannot download these products. Once raw
files and associated calibration material are locally frozen, pre-register a
separate reconstruction pipeline with a non-solar validation fixture before
attempting any b-resolved deflection residual.
