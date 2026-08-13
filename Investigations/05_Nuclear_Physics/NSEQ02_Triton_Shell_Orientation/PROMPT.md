# NSEQ02 — Triton shell orientation (belt nomenclature retired)

> **Status:** PRE-REGISTERED — 2026-08-09.  
> **Class:** SDT claim investigation (geometry / orientation).  
> **Upstream:** Author correction — d/t grammar and shell **capacities** stand;
> “triton **belt**” equatorial-ring orientation was an LLM assumption that
> propagated (sequencer + `laws.hpp` comments). Not a rejection of magic-number
> schedule or enmeshment.  
> **Canon edits:** none (propose-and-wait for nomenclature / orientation in
> `laws.hpp` and sequencer).

## 0. Split (binding)

| Kept | Contested |
|---|---|
| α-grammar `n_d`, `n_t` | Word “belt” as physical orientation |
| Shell / closure **capacities** giving 2,8,20,28,50,82,126 | Planar antipodal equatorial-ring seating in sequencer |
| Tritons open/close internal packing (electron-shell story) | Rolling-equator-only seating as required geometry |
| Enmeshment / shadow defect | — |

## 1. Author geometry under test (first 8-seat triton shell)

For capacity **8** (first triton shell / former “B(3)”):

- **Two offset interlinked tetrahedra** (polar-aligned stella octangula)
- Valences 1–2 on the **poles**
- Remaining **six** alternating near the equator: opening base at
  lat `−arcsin(1/3)≈−19.47°`, closing base at `+19.47°`, azimuth offset 60°
- Partition: opening tetra = N + 3 southern-band; closing = S + 3 northern-band
- **Radius rule (author):** opening triton valence radius **>** closing triton
  valence radius in every case

A literal flat hex-bipyramid (poles + z=0 hex) is recorded as a **rejected
misread** of “equator” — it does not give regular tetrahedra. The sequencer’s
coplanar `beltPlane` rings are a separate, stale orientation.

## 2. Procedure

1. Build unit-sphere orientations for (A) author dual-tetra / hex-bipyramid,
   (B) sequencer-style first belt (4 antipodal pairs on one equator — 8 seats
   degenerate to equatorial octagon if flattened; use sequencer’s actual first
   belt: 4 antipodal pairs ⇒ 8 directions in one plane).  
2. Report pairwise angular separations, min angle, regularity.  
3. Apply `r_open = 1.05`, `r_close = 0.95` (relative units; ratio only) and
   verify opening shell mean radius > closing.  
4. Label sequencer “belt” code path **ORIENTATION_STALE**.  
5. No AME / IAEA; no κ fit; no `laws.hpp` edit.

## 3. Claims

| ID | Claim |
|---|---|
| NSEQ02-C1 | Split ledger published (capacities kept; belt orientation contested). |
| NSEQ02-C2 | Author 8-seat layout: 2 poles + 6 equator; two tetrahedra partition. |
| NSEQ02-C3 | With `r_open > r_close`, mean opening radius > mean closing radius. |
| NSEQ02-C4 | Sequencer first-belt orientation is planar / equatorial — distinct from C2. |
| NSEQ02-C5 | Status: **`BELT_ORIENTATION_STALE`**; shell capacities **not** withdrawn. |
| NSEQ02-C6 | No canon edit; propose-and-wait listed. |

## 4. Non-claims

Does not kill magic numbers, grammar, or F(n)/capacity counting. Does not yet
rebuild the full sequencer `packNucleus` (that is a follow-on engineering task
after orientation freeze).
