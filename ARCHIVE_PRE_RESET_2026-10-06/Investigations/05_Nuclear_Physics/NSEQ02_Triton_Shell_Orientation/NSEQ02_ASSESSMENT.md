# NSEQ02 Assessment — Triton shell orientation

**Date:** 2026-08-09  
**Instrument:** `nseq02_orientation.cpp`  
**Stdout:** `.audit-tmp/nseq02_run.txt`  
**Canon edited:** no  

## 1. Author correction

Everything in the sequencer **except belt orientation** stands: shell
distributions / capacities → magic numbers; d/t grammar; tritons open and close
internal packing of electron shells. The word **“belt”** and the planar
antipodal-ring seating were an LLM assumption that propagated (sequencer HTML,
`laws.hpp` shell-schedule comments, NSEQ01 R5 wording) without a reversal.

## 2. Geometry results

| Layout | Class | Regular tetra? | Notes |
|---|---|---|---|
| Sequencer first “belt” | coplanar equator (`max\|z\|=0`) | no | 8 seats = 4 antipodal pairs; **ORIENTATION_STALE** |
| Flat hex-bipyramid (literal poles+z=0) | 3D but wrong | no | dirs 90°/120°; misread of “equator” |
| **Polar dual tetrahedra** | 3D nested | **yes** | poles + 6 at ±19.47° interleaved; all 6 edges equal per tetra |

With `r_open=1.05 > r_close=0.95`: opening tetra edges equal and **larger** than
closing; central angles exact `arccos(−1/3)≈109.47°`.

## 3. Claim ledger

| ID | Status |
|---|---|
| NSEQ02-C1 | **PASS** — split ledger |
| NSEQ02-C2 | **PASS** — dual-tetra built |
| NSEQ02-C2b | **PASS** — regular tetra directions |
| NSEQ02-C3 | **PASS** — `r_open > r_close` |
| NSEQ02-C4 | **PASS** — belt planar / author 3D |
| NSEQ02-C5 | **PASS** — `BELT_ORIENTATION_STALE`; capacities not withdrawn |
| NSEQ02-C6 | **PASS** — no canon edit |

## 4. Headline

**`BELT_ORIENTATION_STALE`** — shell capacities and d/t grammar retained;
triton seating geometry under revision to polar dual tetrahedra
(`r_open > r_close`).

## 5. Amendments / propose-and-wait

- **NSEQ01 R5:** orientation portion marked STALE; capacity / n–p–n rod counting
  retained (see NSEQ01 assessment amendment).
- **Propose-and-wait (not applied):** retire “belt” orientation language in
  sequencer + `laws.hpp` comments; rewrite first 8-seat packing to dual-tetra
  shells. Capacity schedule may stay.

## 6. Next

1. Author freeze on dual-tetra seating (confirm nested radii policy for all
   shells, not only first 8).  
2. Sequencer `packNucleus` orientation rewrite (engineering; site + `docs/`
   mirror).  
3. Shadow-union BE (`κ·ΔA`) as a **later** NSEQ (do not reuse NSEQ02 id).
