# GOM27 D5 Absolute-VLBI Discovery Pre-Registration

**Date:** 2026-08-07  
**Status:** PRE-REGISTERED BEFORE RETRIEVAL  
**Purpose:** determine whether an observationally admissible, solar-offset
resolved deflection data product exists for the already-frozen GOM27 prediction.

## Fixed hypothesis and frozen prediction

The comparison target, if one is found, is the GOM27 computed curve from the
already frozen solar parameter. No deflection amplitude, radial profile,
source offset, or bin selection may be adjusted in response to retrieved
measurements. This discovery pass does not calculate a residual or assess
SDT; it classifies candidate data provenance only.

## Required observational product

An admissible product must provide all of the following for at least four solar
elongation or impact-parameter points:

1. directly measured angular offset, differential angular offset, or calibrated
   interferometric phase delay with uncertainty;
2. observation time and source/station geometry sufficient to derive solar
   elongation independently;
3. stated units, sign convention, reference source, and calibration chain;
4. documentation showing that the supplied observable was not first corrected
   with a GR/PPN gamma deflection term; and
5. a stable archive identifier, source URL, licence/access condition, and file
   checksum before parsing.

Raw visibilities are admissible only if correlator metadata, phase-calibration
inputs, and a documented reproducible reduction path are simultaneously
available. A fitted gamma, a residual after an assumed gamma correction, a
single limb summary, or a plot without recoverable uncertainties is excluded
from a numerical comparison.

## Allowed source search

Search archive catalogues and primary investigator release pages for the 2005
VLBA solar-deflection sessions and for independent solar-deflection programs.
Search results, project identifiers, readme files, and data dictionaries are
metadata only until a candidate passes the required-product gate.

## Fixed decision rules

- **ADMISSIBLE:** every required field is present and provenance does not apply
  a gamma-dependent bending correction.
- **MODEL-PROCESSED / EXCLUDED:** a gamma/GR correction, fitted gamma residual,
  or missing uncertainty is part of the observable.
- **PENDING_DATA:** no downloadable candidate meets the full gate, or raw files
  lack the calibration/reduction inputs.
- No candidate is selected because its values appear close to GOM27.

## Stop condition

Stop after a primary archive page and its associated public documentation have
been frozen, checksummed, and entered into the dataset manifest. If the product
is not admissible, retain the negative finding and do not construct an SDT
comparison from it.
