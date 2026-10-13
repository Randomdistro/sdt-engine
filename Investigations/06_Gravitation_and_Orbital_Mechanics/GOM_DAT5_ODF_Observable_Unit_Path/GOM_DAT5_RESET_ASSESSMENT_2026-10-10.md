# GOM_DAT5 - reset record, verification scope (2026-10-10)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Session sdt-engine-e0. Read: `PROMPT.md`, `graph_v2.json`, and the GOM_DAT8 reset record (a new record under this protocol, permitted). Not opened: this folder's old assessment, tool, or run log.

Verification rows only (decode, structure and field checks), excluded from physics tallies per the prompt's id alias. Supplier evidence under this protocol: `GOM_DAT8_RESET_ASSESSMENT_2026-10-10.md` Phase A (direct execution, other session) re-decoded the P0 K252 ODF from the PDS label. It confirmed the 36-byte layout, the row bounds (records 6-7452, 7447 rows), the time tags inside the label window (+0.5 s), the observable and reference-frequency decode, a median abs(obs) of 50,244.3 Hz, and the label's observable equation (count rate minus the abs(Fb K + B) bias term).

## This item
C1 (the label states a Doppler observable equation from counts and bias, not observed minus predicted) and C2 (type 12, Hertz, format ID 2): covered by the DAT8 reading of the label. C4 magnitude gate (median abs(obs) in [1e3, 1e7] Hz): 50,244.3 Hz, met on P0. C5 (the MESSENGER example magnitude) not checked here. Classification ENGINEERING_DOPPLER_HZ is supported on P0.

## Outcome
**VERIFICATION, met for C1, C2, C4 on P0 (supplier); C5 open.**

## Comparison with the archived record
Deferred.

