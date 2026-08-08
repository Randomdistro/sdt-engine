# Master Protocol - Iteration 9 (Cassini ODF Revision Falsification)

**Date:** 2026-08-09  
**Branch:** GOM25 D4b Cassini ODF decoder fixture

## Decision

`STRUCTURE_PARTIAL`; observables `UNDECODED`; no empirical, physical-model, or
theory verdict.

## Audit outcome

- The exact official PDS source search falsified the prior working premise that
  the label's "1 August 1996" wording uniquely identifies an available
  revision: PDS supplies Change 1 reissued 15 August 1996, while the frozen
  Cassini SIS cites Change 3 dated 15 June 2000.
- Both sources support Format ID 2 and the broad ODF time-tag grammar, but
  neither supports the unverified transformations needed to reconcile the raw
  creation-date word `1020615` or the 500-ms summary/tag offsets.
- The structure instrument was rerun without a grammar change. It retains
  exactly two failures and continues not to read numeric observable bytes.
- A post-run assertion initially addressed `checks` rather than
  `structure_checks`; the origin was a shell-validator field-name mistake. The
  corrected assertion passed without changing any audit data or result.

## Method boundary

The new PDS documents are technical decoding sources, not observational data.
They may constrain a parser but cannot confirm, reject, or fit SDT, general
relativity, or any other physical theory. No statement in this iteration uses a
standard-model calculation as a rejection gate.

## Next gate

Locate and pre-register a producer-applicable ODE V2.0/ODF specification or a
known binary fixture that independently resolves both date and time conventions.
If no such source exists, retain this conflict as an explicit decoder block and
move the falsification effort to an independently decodable observational
channel rather than repairing the data by assumption.
