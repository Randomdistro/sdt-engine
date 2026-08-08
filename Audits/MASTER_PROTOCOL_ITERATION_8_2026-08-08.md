# Master Protocol — Iteration 8 (Cassini ODF Structure)

**Date:** 2026-08-08  
**Branch:** GOM25 D4b Cassini ODF decoder fixture

## Decision

`STRUCTURE_PARTIAL`; observables `UNDECODED`; no empirical or physical-model
verdict.

## Retained findings

- The ODF label self-consistently frames 7,616 36-byte records, including 7,447
  format-2, type-12 two-way-Doppler metadata records with good validity flags.
- Two source/encoding conflicts remain: raw file creation date `1020615` versus
  the label's documented `YYMMDD` field, and a `500 ms` data-tag offset from
  whole-second summary bounds.
- The audit corrected two of its own errors: an unsupported non-conjunction
  assertion and a date expectation that confused observation with creation date.
- Numeric observable fields remain unread, so no Doppler, range, residual,
  geometry, profile, or rival-framework value has entered the record.

## Next gate

Freeze the exact ODF-specific `TRK-2-18` revision named by the label, then
re-run the structure audit against its documented date and time conventions.
Only an independently expected non-conjunction observable can license field
value decoding; only afterward can TDF reconstruction and the larger
solar-propagation experiment proceed.
