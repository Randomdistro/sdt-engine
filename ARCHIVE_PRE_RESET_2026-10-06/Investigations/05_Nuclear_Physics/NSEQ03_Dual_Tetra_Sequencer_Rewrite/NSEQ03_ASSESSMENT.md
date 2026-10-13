# NSEQ03 Assessment — Dual-tetra sequencer rewrite

**Date:** 2026-08-09  
**Instrument:** `nseq03_dual_tetra_rewrite.py`  
**Stdout:** `.audit-tmp/nseq03_run.txt`  
**Edited:** `Release/HTML_SDT_Website/nuclear-packing-sequencer.html`,
`docs/nuclear-packing-sequencer.html`  
**Canon (`laws.hpp`):** not edited — propose-and-wait filed  

## 1. What changed

Triton seating in `packNucleus` no longer uses coplanar antipodal “belts”.
Each shell uses polar dual-tetrahedra seating:

- capacities unchanged: `SHELL_CAPS = [8,10,12,14,16,18]`
- N/S poles first; remaining seats alternate on bands at ±arcsin(1/3)
- `r_open = 1.05 rB`, `r_close = 0.95 rB`

α core, deuteron tiers, grammar, contacts, shadow defect path untouched.

## 2. Claim ledger

| ID | Status |
|---|---|
| NSEQ03-C1 | **PASS** — site + docs markers; `BELT_PAIRS`/`beltPlane` gone |
| NSEQ03-C2 | **PASS** — He/C/O/Fe/U counts |
| NSEQ03-C3 | **PASS** — Ca-48: 2 poles, ±19.47° bands, `r_open>r_close`, not planar |
| NSEQ03-C4 | **PASS** — capacity schedule retained |
| NSEQ03-C5 | **PASS** — `laws.hpp` proposal only |

## 3. Headline

**`DUAL_TETRA_SEQUENCER_APPLIED`**

## 4. Awaiting approval

`PROPOSE_LAWS_HPP_BELT_NOMENCLATURE.md` — rename belt→shell in comments/symbols;
no capacity change.

## 5. Next

1. Author approve/amend `laws.hpp` nomenclature proposal.  
2. Optional: UI/copy sweep for residual “belt” wording elsewhere in the site.  
3. Later NSEQ — shadow-union `κ·ΔA`.
