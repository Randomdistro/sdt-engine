# NSEQ07 Assessment — D₄₂ genus-1 topology

**Date:** 2026-08-09  
**Pre-registration:** `NSEQ07_PRE_REGISTRATION.md`  
**Instrument:** `nseq07_d42_genus1.py`  
**Stdout:** `.audit-tmp/nseq07_run.txt`  
**Canon edited:** no  
**Parent debt:** NSEQ05-C6 OPEN (`E=42 > 3V−6=36`)

## Status

`D42_GENUS1_TOPOLOGY_SURVIVES`

## Gate results (both polar branches)

| Gate | Result | Content |
|---|---|---|
| C1 | **PASS** | Surface `S=(T−Q)∪(T−T)`: `\|S\|=36`, triangulation `F=24`, `χ=2` (sphere), connected |
| C2 | **PASS** | `\|QQ\|=6` = excess over `3V−6` = NSEQ06 doublet count |
| C3 | **PASS** | Full graph 6-regular, `E=3V=42`, triangulation `F=28`, `χ=0` (genus 1) |
| C4 | **PASS** | All 6 doublets are exactly one Q−Q chord + one surface edge (no S−S, no QQ−QQ) |

## Corrected relationship

NSEQ05-C6 asked whether `E=42` breaks the D₄₂ seating. It does **not**.

The wrong category was “simple spherical polyhedron.” The right split is:

1. **Surface skeleton** — cuboct face adjacency (24 T−Q) plus tetrahedral T−T (12)  
   → maximal spherical triangulation (`E=36=3V−6`, `χ=2`).  
   Degrees: every T has deg 6 on the surface; every Q has deg 4.
2. **Orientation chords** — the 6 selected polar Q−Q edges  
   → lift the graph off the sphere to a **genus-1 triangulation** (`χ=0`).
3. **Radial doublets** — each of the 6 doubled midpoint rays is the
   coincidence of one chord midpoint with one surface-edge midpoint.

So: **D₄₂ contact topology = spherical triangulation ⊕ 6 polar chords = toroidal 6-regular triangulation.**  
Capacities unchanged; orientation-branch debt (triangles vs hexagon) preserved, not averaged.

## What this does *not* claim

- No emission/transition discriminator between the two branches (still OPEN;
  NSEQ06 shared-vs-private doublet rays now have edge-class provenance for a
  follow-on test).
- No empirical nuclear observable; combinatorial topology only.
- No `laws.hpp` arithmetic change. Optional comment: replace
  “non-simple / internal contact OPEN” with the genus-1 classification above
  (propose-and-wait).

## Propose-and-wait (comments only)

If approved, amend NSEQ05-related `laws.hpp` / proposal prose:

> D₄₂ / 14→42: surface `(T−Q)+(T−T)` is spherical maximal (`E=36`, `χ=2`);
> full degree-6 graph with polar Q−Q selection is genus-1 (`χ=0`);
> six radial mid-point doublets = the six Q−Q chords each aligning with one
> surface edge.

Reply **approve laws.hpp D42 genus-1 comment** to apply.
