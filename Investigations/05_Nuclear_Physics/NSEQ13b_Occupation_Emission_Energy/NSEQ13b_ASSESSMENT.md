# NSEQ13b Assessment — Occupation/emission energy map

**Date:** 2026-08-12  
**Stdout:** `.audit-tmp/nseq13_run.txt` (v2); v1 preserved as `nseq13_run_v1_binding_leak.txt`  
**Status:** `NSEQ13_UNDERDETERMINED`

## Relationship correction (run 1 → run 2)

Run 1 incorrectly labeled `ENERGY_MAP_SURVIVES` using measured `B_d`, `B_t`, `B_α` products. Those are **SHARED-INPUT leaks**, not seating-derived quanta.

Run 2 decision rule: dependency-traced bridges plus Shared/private seating integers only. All derivation candidates **MISS**. Leaks E7/E8 remain controls.

## Classification

Seating (NSEQ11) does not determine MeV heights. NSEQ09 gap *locations* remain DERIVED; *heights* OBSERVED.
