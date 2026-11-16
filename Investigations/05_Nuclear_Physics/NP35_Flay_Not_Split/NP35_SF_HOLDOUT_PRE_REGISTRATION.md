# NP35 — spontaneous-fission hold-out (pre-registered 2026-10-05, before the files were opened)

**Source of the owed item:** `DATA_REQUIREMENTS.md` ("Owed": Cf-252 SF independent FY as hold-out for F3; Pu-240/242(sf), Cm-244(sf), U-238(sf) — same) and `Datasets/MUST_FETCH_2026-07-23.md` F12 (BLOCKED on relnsd).
**Data (now in repo, byte-verified):** `Datasets/nuclear/fission_yields/endf_b8_sfy/` — ENDF/B-VIII.0 spontaneous fission yield sublibrary (MD5 and SHA1 equal the values NNDC publishes), MF=8 MT=454 independent yields for U-238, Cm-244, Cm-246, Cm-248, Cf-250, Cf-252, Es-253, Fm-254, Fm-256 (evaluation England–Rider 1992). Yields are after prompt-neutron emission, as in the IAEA files.
**Prediction (F3, frozen in NP35_PRE_REGISTRATION.md; nothing retuned):** N_H = 82 (T12, since 112 ≤ N_parent < 168), Z_H = round(82·Z/N_parent), A_H_pre = Z_H + 82, A_L_pre = A_parent − A_H_pre (spontaneous fission: A* = A_parent). Emitted below before any yield file is opened by `np35_sf_holdout.py`.

| System | Z | A* | N_p | Z_H | A_H_pre | A_L_pre |
|---|---|---|---|---|---|---|
| U-238 | 92 | 238 | 146 | 52 | 134 | 104 |
| Cm-244 | 96 | 244 | 148 | 53 | 135 | 109 |
| Cm-246 | 96 | 246 | 150 | 52 | 134 | 112 |
| Cm-248 | 96 | 248 | 152 | 52 | 134 | 114 |
| Cf-250 | 98 | 250 | 152 | 53 | 135 | 115 |
| Cf-252 | 98 | 252 | 154 | 52 | 134 | 118 |
| Es-253 | 99 | 253 | 154 | 53 | 135 | 118 |
| Fm-254 | 100 | 254 | 154 | 53 | 135 | 119 |
| Fm-256 | 100 | 256 | 156 | 53 | 135 | 121 |

(Z_H uses Python's round-half-even exactly as `np35_flay_sim.py`; the script recomputes and asserts this table.)

**Observed A_H, A_L:** `hump_centroid` of `np35_flay_sim.py` (mode ± 8 on the post-neutron mass yield; light range 70..A*/2, heavy range A*/2+1..175), unchanged.
## Gates (the NP35 gates, applied unchanged to the nine hold-out systems)
| Gate | MATCH | EXCLUDED |
|---|---|---|
| H1 F3 A_H, each system | \|ΔA_H\| < 8 | \|ΔA_H\| ≥ 20 |
| H2 F3 A_H in band, all nine | every predicted A_H in [128, 148] (true by prediction) and every observed A_H in [128, 148] | any observed A_H < 120 or > 160 |
| H3 slope of observed A_H vs A* | \|slope\| < 0.25 (NP35 G4 on the observed side) | slope > 0.5 |
| H4 A_L_pre − A_L_obs | in [1.0, 8.0] for each system | negative or > 12 |
ORDER = 8 ≤ |ΔA_H| < 20. No retune after opening. Pass on H1 for all nine is a hold-out confirmation of F3's heavy-peak location on a different fission mode; it is still target-exposed to the heavy-peak location near A ≈ 138–140 as literature knowledge.

## Limitations stated in advance
- The ENDF SFY evaluations for Es-253 and Fm-254/256 are England–Rider extrapolations, not measured distributions; the Fm cases are expected to be the weakest (known shift towards symmetry for the heaviest fermium isotopes). They are scored with the rest and reported separately.
- Z_H is parent composition, not a seating derivation (NP36 excluded the seating route); ν is not predicted; H4 is a residue class only.
