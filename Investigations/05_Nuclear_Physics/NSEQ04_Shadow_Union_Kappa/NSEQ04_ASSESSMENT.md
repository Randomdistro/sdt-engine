# NSEQ04 Assessment — Shadow-union κ·ΔA

**Date:** 2026-08-09  
**Instrument:** `nseq04_shadow_kappa.py`  
**Stdout:** `.audit-tmp/nseq04_run.txt`  
**Packing:** live dual-tetra `packNucleus` (NSEQ03)  
**Canon edited:** no  

## 1. Policy (frozen)

`BE ≈ κ·ΔA` through origin; `κ = Σ(BE·ΔA)/Σ(ΔA²)`; full ISO N=217;
`dnn=1.45 R_p`, `coul=0.30`, sequencer `DEFAULT_LIGHT`; one pass, no retune.

## 2. Results — CALIBRATED(1)

| Quantity | Value |
|---|---|
| κ | **31.4485 MeV/fm²** |
| N | 217 |
| R²(BE) | 0.7918 |
| R²(BE/A) | **−161.94** (worse than mean BE/A) |
| mean \|rel err\| | 40.4% |

Smoke (packing counts PASS; energy residuals large on light nuclei):

| Nuclide | BE meas | κ·ΔA | \|rel\| |
|---|---|---|---|
| He-4 | 28.3 | 124.1 | 339% |
| C-12 | 92.2 | 333.4 | 262% |
| O-16 | 127.6 | 334.6 | 162% |
| Fe-56 | 492.3 | 625.5 | 27% |
| U-238 | 1801.7 | 1381.8 | 23% |
| Ca-48 | 416.0 | 960.1 | 131% |

## 3. Claim ledger

| ID | Status |
|---|---|
| NSEQ04-C1 | **PASS** |
| NSEQ04-C2 | **PASS** |
| NSEQ04-C3 | **PASS** — metrics published |
| NSEQ04-C4 | **PASS** — counts; energy residuals reported |
| NSEQ04-C5 | **PASS** |

## 4. Headline

**`SHADOW_KAPPA_REPORTED`** — one-scale through-origin κ is **CALIBRATED(1)**
and tracks total BE at R²≈0.79, but **fails as a per-nucleon account**
(R²(BE/A)≪0; light nuclei systematically over-bound). Not promoted to
EMPIRICALLY SURVIVES.

## 5. Reading (residuals, not excuses)

Through-origin LS on total BE is dominated by heavy, high-ΔA nuclei; light
shells then sit above the κ·ΔA line. Dual-tetra reseating did not create this
pattern by itself — it is the known tension of a single area→energy scale
against BE/A structure (sequencer UI already exposes the same κ path).

## 6. Next

1. Explicit approve for `laws.hpp` belt→shell rename (still waiting).  
2. Follow-on NSEQ: alternate κ policies only if pre-registered (e.g. fit on
   BE/A, or stratified light/heavy) — do not silent-retune.  
3. Optional: compare pre-rewrite (planar belt) κ metrics vs dual-tetra for
   orientation sensitivity of ΔA.

## 7. Shared-packer replay (2026-08-15)

The instrument was updated to load `js/pack-nucleus.js` after the website
sequencer stopped carrying a private inline copy. Replaying the same registered
`dnn=1.45 R_p`, `coul=0.30`, and `DEFAULT_LIGHT` policy against
`NSEQ05-WEB-2` (subsequently reclassified as the
`NSEQ05-CONTROL-3` legacy geometric control) gives:

- κ = 36.162887 MeV/fm²
- R²(BE) = 0.817825
- R²(BE/A) = −180.510967
- mean |relative error| = 41.15%

These values do not replace the 2026-08-09 registered result above. They record
the geometry-version sensitivity of the proxy. The adjudication is unchanged:
projected overlap remains excluded as the binding law.

## 8. Live-default unit correction (2026-08-15)

The section 7 replay retained the historical expression `1.45 R_p` while the
shared NSEQ05 packer and website controls now define `defaultBondFm = 1.45 fm`.
That replay therefore did not use the live default requested by the website
publication gate.

The instrument now reads `SDT_NUCLEAR_PACKING.defaultBondFm` directly. The
corrected whole-table replay gives:

- κ = 47.137184 MeV/fm²
- R²(BE) = 0.796231
- R²(BE/A) = −230.641525
- mean |relative error| = 44.39%

Representative residuals are 557.2% for He-4, 218.5% for C-12, 216.4% for
O-16, 42.8% for Fe-56, 11.7% for U-238 and 36.1% for Ca-48. The correction
strengthens the existing adjudication: projected overlap is a
`CALIBRATED(1)` diagnostic and is excluded as the binding law.
