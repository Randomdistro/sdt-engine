# GOM_DAT3 - reset record, verification scope (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Session sdt-engine-e0. Read: `PROMPT.md`, `graph_v2.json`, and the GOM_DAT8 reset record (a new record under this protocol, permitted). Not opened: this folder's old assessment, tool, or run log.

Verification rows only (decode, structure and field checks), excluded from physics tallies per the prompt's id alias. Supplier evidence under this protocol: `GOM_DAT8_RESET_ASSESSMENT_2026-10-10.md` Phase A (direct execution, other session) re-decoded the P0 K252 ODF from the PDS label. It confirmed the 36-byte layout, the row bounds (records 6-7452, 7447 rows), the time tags inside the label window (+0.5 s), the observable and reference-frequency decode, a median abs(obs) of 50,244.3 Hz, and the label's observable equation (count rate minus the abs(Fb K + B) bias term).

## This item
C1-C3 (finite obs_Hz, positive f_ref, observable summary) on P0: covered (median abs(obs) 50,244.3 Hz; f_ref per record). C4 (the cumindex freeze list for SCE1 157-160) is not covered.

## Outcome
**VERIFICATION, met for C1-C3 (supplier); C4 open.**

## Comparison with the archived record
Deferred.

