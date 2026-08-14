# NP39 Assessment — monoisotopy vs pack staircase

**Date:** 2026-08-13  
**Stdout:** `.audit-tmp/np39_run.txt`  
**Canon edited:** no  
**Packer validate:** `.audit-tmp/packer_validate.txt` PASS vs node

## Status

`NP39_LIGHT_PATTERN_ONLY`

## Gates (frozen)

| Gate | Result |
|---|---|
| G1 F/Na/Al/P end at T8 fill=1 | **MATCH** 4/4 |
| G2 no odd-Z double has a T8×1 stable | **FAIL** — Cl-35, K-39 |
| G3 25/25 odd-Z singles mid-T | **FAIL** 23/25 — Co-59 and In-113 stop on leftover D (D12 2/12, D20 2/20) |

## What the staircase does

Light soles sit at the first T8 seat after D6/D12 work. That is the `u = v−2` segment of the lab gold line.

It does **not** pick width. Cl-35 and K-39 occupy the same T8×1 stop as F/Na/Al/P and remain doubles. Co-59 / In-113 show that leftover deuterons after a T-shell are legal odd-Z sole stops — not every sole is mid-T.

## Classification

Lead for the light n_t=1 line. Width discriminator **excluded** at the pre-registered G2. Not native WHICH-A. NP23 mechanism debt stands (NP17 lock / FLM14 dwell still unpaid; this loop did not pay them).
