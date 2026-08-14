# GOM25 D4b ODF Decoder Amendment 01

**Date:** 2026-08-08  
**Trigger:** unsupported “non-conjunction” premise in the initial D4b decoder
pre-registration.

## Correction

The frozen ODF label identifies the product as SCE1 on 2002 day 157, but the
currently frozen inputs contain no independently verified solar geometry or
conjunction classification. Calling this file a non-conjunction fixture was
therefore unsupported. The label's complete ODF field grammar does not supply
an independent expected Doppler/range value either.

## Revised permitted output

This loop may decode and validate only:

1. 36-byte record framing and the label's file-record count;
2. group headers, group boundaries, format IDs, station IDs, and data-type IDs;
3. file-label metadata and ODF time-tag bounds against the label's start/stop
   metadata; and
4. counts of declared record categories.

It may **not** decode, export, plot, summarize, or compare the numeric
observable fields (Doppler, range, phase, frequency, or residual). Those fields
remain `UNDECODED` until a separately frozen non-conjunction fixture supplies a
known expected value and the signal/clock convention is documented.

## Status consequence

Successful structure checks may reach `READY_FOR_ODF_FIXTURE_ONLY`. They do not
resolve the TDF document-version conflict, establish an ODF measurement value,
or advance a Shapiro-like propagation test.
