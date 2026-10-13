# APS11 Assessment — Lamb as pair-breaking occupancy

**Date:** 2026-08-13  
**Stdout:** `.audit-tmp/aps11_run.txt`  
**Canon edited:** `laws.hpp` Lamb comments + He⁺ sticker (2026-08-13, this session)  
**Instrument:** `aps11_lamb_pair_break.py` · V1 PASS vs PPT08 H2 map

## Status

`APS11_SIGN_SURVIVES_AMPLITUDE_ACCEPTED_OBSERVED`

## What the Lamb interval *is* (this run)

**Kinematically (Phase A, RE-EXPRESSION of measured f):** it is a seat offset on the koppa ladder, not a Dirac anomaly.

| Seat | f OBSERVED | \|Δr\| | Δv |
|---|---:|---:|---:|
| H n=2 | 1057.8450 MHz | 0.2725 fm | 0.7038 m/s |
| H n=3 | 314.819 MHz | 0.4106 fm | 0.3142 m/s |
| He⁺ n=2 | 14041.13 MHz | 0.4518 fm | 4.669 m/s |
| D n=2 | 1059.2341 MHz | 0.2728 fm | 0.7046 m/s |

Δr is **seat-dependent**. A constant node (R_p/3 = 0.2805 fm) can only be the H n=2 line.

**Ontologically (G_sign):** it is the occupancy cost of an **incomplete dyad**. Measured 2S₁/₂ lies *above* 2P₁/₂, so S1 (complete pair more bound ⇒ 2S lower) is **excluded**. S2 (one electron in a two-seat pair geometry ⇒ vacancy strain ⇒ 2S higher) survives. That is the precise pair-breaking reading that is compatible with the sign.

It is **not** the Be/Mg ionization breaking fee (eV). It is **not** the APS04 quadrupole (0.761 MHz = 7.2×10⁻⁴ of H n=2). It is **not** L(1S) (8172.8 MHz). It is **not** the muonic whole 2S–2P (202 meV).

## Magnitude (G_table FAIL)

Twelve declared cells; L1 and E1 are the same Kepler identity (not two tests). **No cell hits H2+H3+He2 at rel<0.10.**

Closest: **L2[R_p/3]** `Δr = (R_p/3)(n/2)`

| Line | pred | obs | class |
|---|---:|---:|---|
| H n=2 | 1088.6 MHz | 1057.8 | MATCH (rel 0.029) |
| H n=3 | 322.5 MHz | 314.8 | MATCH (rel 0.025) |
| He⁺ n=2 | 8716 MHz | 14041 | ORDER (rel 0.38) |

Hydrogen *n*-scaling of a node offset survives this pass. **Z-scaling does not.** H2-only MATCH on L1/E1[R_p/3] is the logged PPT08 cluster (look-elsewhere), not native.

## Other discriminators

- **H–D:** absolute D2 from reduced-mass scaling of H2 is inside 10% (the two frequencies almost coincide). The *split* 1.389 MHz vs 0.288 MHz predicted is **not** reduced mass — leftover is nuclear structure (APS04 isotope residual still owed).
- **L(1S):** E1[R_p/3] 17417 vs 8173 MHz EXCLUDED. Ground-state Lamb is a different object than nS–nP occupancy.
- **μp whole interval:** E1/E2 ~ 10⁻² meV vs 202 meV. Pair-break electronic occupancy is not the muonic 2S–2P. Consistent with APS04 Fork-B death on raw whole shifts.
- **Rival α⁵ Z⁴/n³ (no logs):** ORDER, ~0.32 of each electronic line; control only.

## Classification

Prompt completion: executed as pre-registered.  
Physics: **sign/ontology CONVERGENCE with S2**; **H and He⁺ amplitudes ACCEPTED as OBSERVED stickers** (2026-08-13). Extraction of 1057 from trefoil/FLM14 withdrawn. Construction names the α center; it does not derive 14041 from 1057. No EMPIRICALLY SURVIVES on a derived interval. No fabricated 1051.8.

Canon: `laws.hpp` `lamb_shift_measured_MHz`, `lamb_shift_He_plus_measured_MHz`. See `PPT08_KOPPA_TARGET.md`.

He⁺ is a second OBSERVED sticker, not a Z-factor owed from hydrogen. Koppa Δr remains a re-expression of each sticker.

## Center vs seat (correction)

Hydrogen is a **center**, not a seat. The n⁻³ ladder from 1057.845 MHz is the proton-center Kepler occupancy, not a packed-seat table. Calling H n=2,3,4 “seats” is withdrawn.

| Object | What it is | Lamb / 4π |
|---|---|---|
| H (Z=1) | proton **center**; no α, no D/T | 1057 MHz + n⁻³ is the *center* spectrum |
| He-4 / He⁺ | α **core** (grammar: n_d=n_t=0); still a center, not a D/T seat | 14041 MHz ACCEPTED OBSERVED (α-center sticker). Construction names two protons; it does not derive this from 1057 |
| First seats | D/T around the α (Li-6 = α+d, … NSEQ05 shells) | 4π incomplete-dyad occupancy applies **here** — every packed seat, not every Kepler n of hydrogen |

n⁻³ still holds *inside* a center (H n=3,4 from H n=2; He⁺ n=4 from He⁺ n=2). That is center kinematics. It is not the seat law.

**Seat law (stated, not gated):** the 720° return is occupancy of each packed D/T (and later-shell) proton the electron tours. Hydrogen does not supply those seats. He⁺ does not either. FLM14-P2 tour/dwell remains DEFER until the packer seats are the tour, not a hydrogen ring labelled “seat.”

Do not retune hydrogen n⁻³ to close He⁺. Do not spend L(1S) as an n=1 seat. No EMPIRICALLY SURVIVES on a seat-sum Lamb until a packed-seat instrument is pre-registered.

## Electron pairing is nuclear; Lamb is occupancy of that pair (not nucleon binding)

If construction dictates all, electron pairing is not an independent shell postulate. It is the projection of nuclear pairing (α = two protons; D/T seats thereafter). Rule 18 / NP03E still unadjudicated as a table; this is the ontology.

**Lamb is then the occupancy cost of that nuclear pair geometry**, not the MeV cost of pairing the nucleons (NP17 / NP17b — different object, ~10⁶ times larger).

| Reading | Verdict |
|---|---|
| Lamb = pn / α binding (MeV) | **excluded** — units |
| Lamb = fee of a nucleon pair that is *present* | **excluded by hydrogen** — H has 1057 MHz and no second nucleon. Completing the pair (D) does not remove it: D−H = **+1.389 MHz**, not −1057 |
| Lamb = one electron occupying the nuclear-pair *form* (S, 4π dyad) vs the unpaired plane (P) | **survives the sign** (APS11 S2). H is the vacant-partner center; D is the same occupancy plus a nuclear-structure addend; He⁺ is occupancy of a *complete* α pair by one electron |

The H–D split is the paired-nucleon *perturbation* of the interval (nuclear structure; APS04 residual still owed). It is not the Lamb quantum. Neutral He’s 1s² is the complete electron projection of the α pair — hydrogenic nS–nP Lamb is the incomplete-occupancy case (H, D, He⁺).

This re-origin does not derive Δr(He⁺) from Δr(H). He⁺ is the second OBSERVED sticker.

## Deuterium (what the first nucleon pair looks like)

D is **not** the H→He α-center sticker. It is still a Z=1 **center**: one proton for the electron to tour. Completing the nucleon pair does not add a second proton seat.

```
H      [ p ]           unpaired proton center
D      [ p ── n ]      first nucleon pair (the deuteron); still one proton
He-4   α tetra 2p+2n   two proton seats — second OBSERVED sticker
```

| | H n=2 | D n=2 | He⁺ n=2 |
|---|---:|---:|---:|
| f | 1057.8450 MHz | **1059.2341 MHz** | 14041.13 MHz |
| Δr | 0.2725 fm | **0.2728 fm** | 0.4518 fm |
| proton seats the electron tours | 1 | 1 | 2 |

D−H = **+1.389 MHz** (0.131% of H). Reduced mass predicts ~0.288 MHz of that; leftover ~1.10 MHz is nuclear structure (APS04 quadrupole 0.761 MHz is ORDER, not equal). The pn dumbbell (NP17 D=1.963 fm, prolate) perturbs the proton-center occupancy; it does not replace it.

n⁻³ at Z=1 still applies with D’s own sticker: *f*(n) = 1059.2341 × (2/n)³. That is the same center law as hydrogen, shifted by the pair addend. It is not a packed seat, and it is not helium.
