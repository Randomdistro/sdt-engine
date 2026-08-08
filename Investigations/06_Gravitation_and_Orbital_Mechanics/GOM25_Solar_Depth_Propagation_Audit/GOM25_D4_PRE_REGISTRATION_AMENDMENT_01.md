# GOM25 D4 Pre-Registration Amendment 01

**Date:** 2026-08-07  
**Trigger:** frozen-source conflict discovered during the pre-registered
structural census.

## What failed

The original D4 protocol treated the detached PDS3 label as sufficient to
select the header record-format value. It prescribes `2048` for the 2002
file-ID and transponder records, while the raw data contain `8`. The frozen
TRK-2-25 unpacking guide provides an ATDF file-identification example with
format `8`. The two documentation sources therefore do not yield one
unambiguous grammar.

The original protocol also required the raw file-ID data-ID field to decode to
the PDS `DATA_SET_ID`. The available label describes the bit field but does not
provide an expected raw value or an auditable mapping to that PDS identifier.

## Corrected acceptance condition

`READY_FOR_OBSERVABLE_EXTRACTION` is now unavailable unless a source can be
frozen that identifies its own effective date/version and specifies all of:

1. header and tracking-record format values for this file;
2. record-type and bit-offset definitions;
3. file-ID data-ID encoding and its expected value; and
4. a binary fixture whose decoded fields can be reproduced without tuning.

The current result remains `STRUCTURE_PARTIAL`. No record-format convention is
chosen by proximity to the desired observable, and no empirical timing value
may be read from this file under this amendment.

## Retained observations

The checksums, length, physical-block framing, type census, creation timestamp,
and spacecraft-ID extraction remain valid observations of the frozen bytes.
They do not resolve the source-version conflict.
