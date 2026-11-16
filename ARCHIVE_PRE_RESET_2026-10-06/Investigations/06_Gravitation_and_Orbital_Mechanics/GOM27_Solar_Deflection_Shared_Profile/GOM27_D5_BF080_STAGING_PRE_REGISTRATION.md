# GOM27 D5 BF080 Staging Pre-Registration

**Date:** 2026-08-07  
**Status:** PRE-REGISTERED BEFORE ARCHIVE-ACCESS TEST

## Objective

Determine whether a fixed public subset of NRAO project `BF080` can be staged
into locally checksum-verifiable raw VLBA products without an account, e-mail
delivery request, or a theory-dependent reduction. This is an acquisition test,
not a deflection calculation.

## Fixed subset selection

Use only BF080 public execution blocks whose `t_min` begins on
`2005-10-01 UTC`, the earliest published solar-deflection session. Retain every
such product that contains at least one of `3C279`, `J1246-0730`, `J1248-0632`,
or `J1304-0346`; do not select by data quality, solar offset, or agreement with
any predicted curve.

## Accepted staged product

The archive response must supply a stable download URL and a raw FITS-IDI,
UVFITS, or documented equivalent file, with the corresponding execution-block
identifier. Each staged file must be checksumed and added to the dataset
manifest before inspection.

## Prohibited actions

- Do not submit a request that sends e-mail or requires a user identity.
- Do not download a calibrated position, gamma fit, or deflection-corrected
  product as a replacement for raw data.
- Do not run calibration, source-position fitting, solar geometry, or an SDT
  residual on any acquired raw file in this stage.

## Decision rules

- **STAGED:** at least one accepted raw product is directly retrievable and
  manifested.
- **PENDING_ACCESS:** public metadata exists but the archive requires an
  interactive/account/e-mail staging process that cannot be performed here.
- **EXCLUDED:** the available result is only model-corrected or lacks a stable
  raw product identity.

## Stop condition

Stop after the archive access mechanism is verified. If raw products are not
directly retrievable, record the required human-mediated step and preserve the
unreconstructed `PENDING_RECONSTRUCTION` status.
