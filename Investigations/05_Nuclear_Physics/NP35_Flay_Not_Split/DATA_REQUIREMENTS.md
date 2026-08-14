# NP35 — data inventory

## In-repo (hash-registered, use these)

Independent yields = scission observable (pre-β). Cumulative = post-decay smear; not the split.

| System | A* (cn) | File | Energy column | Manifest |
|---|---|---|---|---|
| U-235(n,f) | 236 | `Datasets/nuclear/IAEA_U235_independent_FY.csv` | thermal | `87fcd49503a5` |
| U-233(n,f) | 234 | `Datasets/nuclear/fission_yields/IAEA_233U_independent_FY.csv` | thermal | `878e4e6c1f39` |
| Pu-239(n,f) | 240 | `.../IAEA_239Pu_independent_FY.csv` | thermal | `8e9272960f54` |
| Pu-241(n,f) | 242 | `.../IAEA_241Pu_independent_FY.csv` | thermal | `52bbb5be8087` |
| Np-237(n,f) | 238 | `.../IAEA_237Np_independent_FY.csv` | fast | `a14c5e3540fe` |
| Am-241(n,f) | 242 | `.../IAEA_241Am_independent_FY.csv` | fast | `a75a4ecd5109` |
| U-238(n,f) | 239 | `.../IAEA_238U_independent_FY.csv` | fast | `e602f666aeb3` |
| Th-232(n,f) | 233 | `.../IAEA_232Th_independent_FY.csv` | fast | `6641d35d4f2c` |

Engine closures: `sdt::laws::nuclear::magic_numbers` / NSEQ05 sequence. No new constants.

## Related in-repo (not opened by NP35 instrument)

| Asset | Path | Use later |
|---|---|---|
| U-235 ranked yields | `Datasets/nuclear/U235_FY_ranked.txt` | NP25-Y band |
| Cumulative FY (8 systems) | `Datasets/nuclear/fission_yields/*cumulative*` | β-chain, not scission |
| AME2020 | `Datasets/nuclear/AME2020_mass_excess.txt` | Q / TKE (NP36+) |
| NUBASE2020 | `Datasets/nuclear/NUBASE2020.txt` | fragment stability |
| UVa NCD densities | `Datasets/nuclear/UVaNCD_*.dat` | core compactness (NP30); Sn-132 absent |
| Radii | `Datasets/nuclear/IAEA_ground_states_radii.csv` | freeze kink, not yields |

## Owed (BLOCKED-relnsd — `Datasets/MUST_FETCH_2026-07-23.md` F12)

| Need | Why |
|---|---|
| **Cf-252 SF independent FY** | SF standard; N=154 still T12 — hold-out for F3 without n-capture A* |
| Pu-240/242(sf), Cm-244(sf), U-238(sf) | same |
| Superheavy / N≥168 FY | F3 switch N_H=82 → 126 |
| Bernas ²³⁸U+p fragment table | NP27 peel vs NP35 flay depth (NP37) |
| Joint Y(A,Z,TKE,ν) | NP38 event-resolved; averages cannot place the jacket |

Route: ENDF/B-VIII.0 FY sublibrary MT=454 via NNDC, not the IAEA relnsd CSV endpoint.
