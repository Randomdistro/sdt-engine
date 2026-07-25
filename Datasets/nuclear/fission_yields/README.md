# Fission-yield cache — per-fissioner independent + cumulative yields

*Pulled 2026-07-25, Fable direct, on Harvey's instruction to cache every commercially/experimentally
used fissionable material. Source: IAEA NDS live chart `nds.iaea.org/relnsd/v1/data`
(`fields=independent_fy|cumulative_fy&parents=<A><SYM>`). Serves the ENDF/B-derived evaluation.*

## What "independent" vs "cumulative" means
- **independent_fy** — yield of a nuclide **as a primary fragment**, before β-decay. This is the
  scission observable (what NP25/NP32 want: the mass split the mesh actually parts on).
- **cumulative_fy** — yield **after** the β-decay chains run to that nuclide. Smeared by decay.

Columns: `..._thermal_fy`, `..._fast_fy`, `..._14mev_fy` (+ `unc_*`) — the three incident-neutron
energies. Empty column = that system does not fission at that energy (physics, not a gap).

## Coverage — the 8 the IAEA relnsd endpoint actually serves

| fissioner | role | thermal | fast | 14 MeV | file prefix |
|---|---|---|---|---|---|
| **U-235** | primary thermal reactor fuel | ✓ | ✓ | ✓ | *(canonical copy in `../IAEA_U235_*_FY.csv`)* |
| **U-233** | thorium-cycle fissile | ✓ | ✓ | ✓ | `IAEA_233U_*` |
| **U-238** | fast/breeder blanket; fast-only | — | ✓ | ✓ | `IAEA_238U_*` |
| **Th-232** | thorium-cycle fertile; fast-only | — | ✓ | ✓ | `IAEA_232Th_*` |
| **Pu-239** | MOX fuel, breeders, weapons | ✓ | ✓ | — | `IAEA_239Pu_*` |
| **Pu-241** | fissile buildup in reactors | ✓ | ✓ | — | `IAEA_241Pu_*` |
| **Np-237** | minor actinide, transmutation | ✓ | ✓ | — | `IAEA_237Np_*` |
| **Am-241** | minor actinide, transmutation | ✓ | ✓ | — | `IAEA_241Am_*` |

U-235 is **not duplicated here** — its canonical cache is `Datasets/nuclear/IAEA_U235_{independent,cumulative}_FY.csv`
(same IAEA route). Load it from there; the 7 files here are the new parents.

## What this endpoint does NOT serve — owed, route named (do not assume unavailable)
The relnsd `independent_fy`/`cumulative_fy` fields return **empty** for these — the data exists in
the ENDF/JEFF/JENDL FY sublibraries but not on this live endpoint:
- **Spontaneous-fission standards:** **Cf-252** (THE SF neutron-source & yield standard), Cm-244,
  Cm-242, Cf-250, Cf-254, Pu-240(sf), Pu-242(sf), U-238(sf). *Cf-252 SF is the single most important
  omission for any experimental cross-check.*
- **Neutron-induced but not on relnsd:** Pu-240, Pu-242, Am-243, Cm-242/243/244/245, U-234, U-236,
  Np-238, Pa-231, Th-229.
- **Route for the owed set:** ENDF/B-VIII.0 (or JEFF-3.3 / JENDL-5) **fission-yield sublibrary**,
  files `MT=454` (independent) and `MT=459` (cumulative), via NNDC (`www.nndc.bnl.gov/endf`) or the
  IAEA ENDF mirror. These are ENDF-format and need a parser, not the CSV endpoint. Logged in
  `Datasets/MUST_FETCH_2026-07-23.md` as a BLOCKED-relnsd row.

## Provenance / integrity
Extraction date is the last CSV column. sha256(12) + byte counts in `Datasets/MANIFEST.md`.
Format validated against the pre-existing U-235 cache (identical header/schema, 1229 rows).
