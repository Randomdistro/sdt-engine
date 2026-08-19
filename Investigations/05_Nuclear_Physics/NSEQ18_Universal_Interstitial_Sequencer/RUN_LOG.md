# NSEQ18 Run Log

**Run:** 2026-08-16  
**Instrument:** `nseq18_universal_validate.js`  
**Schema:** `NSEQ18-UNIVERSAL-INTERSTITIAL-1`

## Whole-range construction

- Publicly selectable isotopes: **221**
- Deterministically constructed: **221**
- Construction failures: **0**
- D12 layer count: **3 upper + 6 equatorial + 3 lower**
- Inventory, constitutional grammar, species-pure ordering, parent-interstice,
  connectivity, p-n-only contact, no-slip and no-overlap gates: **PASS**
- Release/docs parity: **PASS**

The triton contraction is closure-triggered. The registered opening-to-closing
interval is divided across the five completed T shells:

```text
0 full T shells → 1.05
1 full T shell  → 1.03
2 full T shells → 1.01
3 full T shells → 0.99
4 full T shells → 0.97
5 full T shells → 0.95
```

A partial T shell retains the scale established by the last completed T shell.
Examples: Ca-48 has one completed T shell and scale 1.03; Pb-208 and U-238 have
four completed T shells and scale 0.97.

## Wake and value spot checks

The closed-wake numerical divergence was `0.00372752`, below the registered
`0.01` gate. Integral and far-field magnetic routes agreed within 5% for all
mandatory spot checks; Pb-208 was `2.23%` and U-238 `0.77%`.

The fixed `alpha*hbar*c/R_p` wake-work map does **not** reproduce measured
binding energies:

```text
He-4   calculated 0.032805 MeV   measured   28.296 MeV
O-16   calculated 0.207335 MeV   measured  127.619 MeV
Fe-56  calculated 1.166721 MeV   measured  492.254 MeV
Pb-208 calculated 5.196407 MeV   measured 1676.720 MeV
U-238  calculated 6.156008 MeV   measured 1801.690 MeV
```

The uncalibrated whole-nucleus magnetic sums likewise do not reproduce all
measured moments; for example the He-4 route gives about `1.65 mu_N` against
the measured spin-zero value. These are exposed as calculated/measured/residual
rows in the public datasheet. No final-value normalization was applied.

## Regression checks

- NSEQ17 light-nucleus calibrated wake validator: **PASS**
- NSEQ16 public sequencer validator: **PASS**
- Public-site global link audit: **FAIL (pre-existing site-wide navigation
  fragments and `welcome.html` mirror drift outside NSEQ18 scope)**

