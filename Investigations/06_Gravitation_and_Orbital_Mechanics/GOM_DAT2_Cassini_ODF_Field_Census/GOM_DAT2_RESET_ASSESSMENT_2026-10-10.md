# GOM_DAT2 - reset record, verification scope (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Session sdt-engine-e0. Read: `PROMPT.md`, `graph_v2.json`, and the GOM_DAT8 reset record (a new record under this protocol, permitted). Not opened: this folder's old assessment, tool, or run log.

Verification rows only (decode, structure and field checks), excluded from physics tallies per the prompt's id alias. Supplier evidence under this protocol: `GOM_DAT8_RESET_ASSESSMENT_2026-10-10.md` Phase A (direct execution, other session) re-decoded the P0 K252 ODF from the PDS label. It confirmed the 36-byte layout, the row bounds (records 6-7452, 7447 rows), the time tags inside the label window (+0.5 s), the observable and reference-frequency decode, a median abs(obs) of 50,244.3 Hz, and the label's observable equation (count rate minus the abs(Fb K + B) bias term).

## This item
C1-C4 (format ID, time tags in window, data-type histogram, station IDs) on the P0 file: covered by the DAT8 Phase A decode (format, time window, rows). The data-type histogram and the station-ID subset check are not restated there; a fresh one-file decode would restate them.

## Outcome
**VERIFICATION, met for format, time and rows (supplier); histogram and station IDs open.**

## Comparison with the archived record
Deferred.

