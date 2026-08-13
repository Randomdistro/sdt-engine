# NSEQ09 Assessment — Blind δ₂ₙ from pure-shell schedule

**Date:** 2026-08-11  
**Pre-registration:** `NSEQ09_PRE_REGISTRATION.md`  
**Instrument:** `nseq09_blind_delta2n.py`  
**Stdout:** `.audit-tmp/nseq09_run.txt`  
**Data:** AME2020 `e8599c6d…3307` (hash match)  
**Canon edited:** no

## Status

`BLIND_DELTA2N_SURVIVES`

## Gate results

| Gate | Result | Content |
|---|---|---|
| C1 | **PASS** | F/B/R schedule → SEAL `{2,8,20,28,50,82,126,184}` + OPEN_D `{40,70,112,168}`; builders call only `F,B,R` |
| C2 | **PASS** | SEAL `{20,28,50,82,126}` median \(D\) all >0; mean **+4.242 MeV** vs control **+1.004 MeV** |
| C3 | **PASS** | OPEN_D mean med \(D\) **+0.895 MeV** vs SEAL `{28,50,82}` **+4.544 MeV** (diff **+3.649 MeV**) |

### Median \(D(N)=S_{2n}(N)-S_{2n}(N+2)\) [MeV]

| N | Class | med \(D\) | nZ |
|---|---|---:|---:|
| 20 | SEAL | +3.912 | 6 |
| 28 | SEAL | +4.704 | 6 |
| 40 | OPEN_D | +1.412 | 6 |
| 50 | SEAL | +4.786 | 9 |
| 70 | OPEN_D | +0.763 | 8 |
| 82 | SEAL | +4.143 | 11 |
| 112 | OPEN_D | +0.510 | 8 |
| 126 | SEAL | +3.665 | 6 |

## What this pays

The outstanding “blind δ₂ₙ / magic not inserted” debt: candidate neutron
numbers come from **pure-shell geometry alone**. Empirically, AME2020
two-neutron gap indicators are large at SEAL closures and **systematically
weaker** at the pure-shell deuteron intermediates that are *not* traditional
magic numbers. That is the discriminator a magic-table insert cannot claim —
an inserted list has no OPEN_D class.

## Scope / limitations

- Gap *locations* are DERIVED from F/B/R; gap *MeV heights* are OBSERVED
  (AME), not predicted from occlusion energy.
- Even-Z, even-N, experimental B/A only; estimated (`#`) rows excluded.
- N=184 / 168 left as forward / sparse (not required by C2/C3).
- Does not by itself derive spin–orbit phenomenology; it tests packing
  enumeration against separation data.

## Cascade

| Prior | Update |
|---|---|
| Outstanding packing enumeration / CLM-13 complement | **CLOSED** at location+discrimination level |
| NSEQ05 pure-shell schedule | empirically supported by δ₂ₙ SEAL vs OPEN_D |
| `laws.hpp` `magic_numbers[]` | still a convenience table; schedule is the source of truth |
