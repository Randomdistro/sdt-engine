# GOM20 GPS Anchor Provenance Pre-Registration

**Date:** 2026-08-07  
**Status:** PRE-REGISTERED BEFORE RETRIEVAL

## Question

Does the GOM20 statement that GPS provides a measured `+45.9`, `−7.2`, and
net `+38.7` microsecond-per-day anchor distinguish an independently observed
clock effect from a pre-launch engineering frequency setting and/or a
model-processed navigation correction?

This is an anchor-provenance and mechanism-completeness test. It does not use
another framework's vocabulary as a rejection rule, and it does not alter the
SDT hypothesis to make a numerical match.

## Fixed SDT inputs and required mechanism

The only SDT mechanism currently stated by GOM20 is an Earth depth difference
`z = koppa_E/r` plus a Law-V speed-budget contribution. Before any numerical
comparison is admissible, the existing repository must supply, without a new
coefficient:

1. a precise signed clock-rate expression for each contribution;
2. the definition and independently measured provenance of `koppa_E`;
3. ground-clock and satellite-clock reference surfaces and time conventions;
4. the treatment of the satellite's non-circular orbit; and
5. a mapping from predicted fractional rate to the claimed daily microseconds.

If any item is absent, it is reported as `PENDING_MECHANISM`; no repair formula
may be invented during this audit.

## Evidence classes

- **OBSERVATIONAL:** a primary clock-comparison data product with time tags,
  uncertainty, comparison convention, and sufficient calibration information.
- **ENGINEERING CONFIGURATION:** a broadcast specification or documented
  pre-launch oscillator frequency setting.
- **MODEL-PROCESSED:** clock products whose published values include a stated
  propagation, orbit, or relativistic correction model.

An engineering configuration may corroborate that a compensating offset was
implemented, but cannot by itself prove separately observed depth and speed
terms.

## Permitted retrieval targets

1. Current official GPS interface/control documentation defining satellite
   clock frequency and clock-correction fields.
2. Primary institutional documentation or a primary experiment describing an
   on-orbit GPS clock comparison, its uncertainty, and its correction chain.
3. A documented raw or minimally processed GPS clock-observation product only
   if its file format and calibration dependencies are available.

## Fixed classifications

- **MEASURED-ANCHOR:** a qualifying observational clock comparison is found and
  can be separated from engineering configuration and declared corrections.
- **ENGINEERING-ONLY:** the available `38.7`-scale evidence is a programmed
  frequency offset or specification, not a direct separated observation.
- **PENDING_RECONSTRUCTION:** raw clock observations exist but need a frozen,
  validated reduction chain.
- **PENDING_MECHANISM:** the SDT expression or its initial conditions are not
  uniquely specified.

No comparison to the SDT rate is calculated unless both a fixed mechanism and a
qualifying observational anchor exist.
