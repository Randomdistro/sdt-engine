# GOM44 — Assessment (2026-10-16)

Registered rules: `PROMPT.md` (written before the run). Output: `RUN_LOG.md`, `flyby_depth_control.csv`. Inputs: JPL Horizons geocentric and heliocentric tables, 20 flybys, cached unchanged in `Datasets/external_audit_2026-10-16/raw/horizons_gom44/` with `SHA256SUMS.txt`. Labels: P = `COMPUTED`; Δv∞,obs = `OBSERVED`; classification of the formula = `PENDING`.

## Conclusions
The endpoint formula registered for GOM43, with K_SDT = 2.9992×10⁻⁶ unchanged, is **inconsistent within the stated tolerance** on gates G2, G3, G4 and G5 at the registered R_ref = 50 000 km, and at both sensitivity radii (20 000 km, 100 000 km) and for the alternative R_☉ definition. G1 (instrument validation) is met.

| gate | result at R_ref = 50 000 km |
|---|---|
| G1 instrument | met: symmetric synthetic B = 0 exactly; closed-form synthetic B reproduced to 0 (printed difference 0.00e+00); all 38 endpoint radii equal R_ref within 1 m; Earth at 0.983–1.017 au at every endpoint; Table I reproduced (V∞ ≤ 0.003 km/s, declinations ≤ 0.9°) |
| G2 anomalous class | **not met**: 4 of 4 fail |
| G3 null class | **not met**: 9 of 9 fail |
| G4 equal-depth control | **not met**: 5 of 7 fail (Stardust and Hayabusa2 unscored: no published Δv∞) |
| G5 rank | **not met**: ρ = 0.375, permutation p = 0.092 (n = 14; threshold 0.7) |

### G2 (anomalous class)
| flyby | P (mm/s) | observed (mm/s) | 2σ |
|---|---|---|---|
| Galileo I | +53.47 | +3.92 | 0.16 |
| Galileo II | +29.54 | −4.60 | 2.00 |
| NEAR | +21.78 | +13.46 | 0.26 |
| Rosetta I | +14.46 | +1.80 | 0.06 |

### G3 (null class; tolerance 2σ, or 0.5 mm/s where σ is unpublished)
Cassini −89.8 (obs −2.0 ± 1.0), MESSENGER −11.5 (0.02 ± 0.01), Rosetta II +52.5, Rosetta III +33.1 (0.004 ± 0.044), Juno −46.9 (0 ± 0.8), EPOXI I +14.6, EPOXI II +0.93, BepiColombo −19.9, Solar Orbiter −48.8. Observed values for all of these are zero within error. The smallest prediction, EPOXI II (0.93 mm/s), is itself 1.9 × the 0.5 mm/s tolerance.

### Why the formula cannot be rescaled
The bracket B is of order 1 for every flyby (|B| = 0.02 to 2.0) because (D/R_☉)² ≈ 0.97–1.03 and the cosψ difference spans most of [−2, 2]. The required bracket, B_needed = Δv∞,obs / (v∞ K_SDT), is small and varies in sign: **post-hoc diagnostic, not registered**

| flyby | computed B | B_needed | obs/P |
|---|---|---|---|
| Galileo I | +1.992 | +0.146 | +0.073 |
| Galileo II | +1.109 | −0.173 | −0.156 |
| NEAR | +1.060 | +0.655 | +0.618 |
| Rosetta I | +1.248 | +0.155 | +0.125 |
| MESSENGER | −0.948 | +0.002 | −0.002 |
| Rosetta II | +1.868 | 0.000 | 0.000 |
| Rosetta III | +1.175 | +0.0001 | +0.0001 |
| Juno | −1.505 | 0.000 | 0.000 |

obs/P ranges from −0.156 to +0.618 among anomalous flybys and is zero for the null flybys at B between −1.5 and +1.9. No single K rescaling reconciles the set. The measured effect has no dependence on perigee altitude in the formula, while the data show the same B-class at 539 km (NEAR, +13.46) and 561 km (Juno, 0).

## Equal-depth control data
Registered rule (lowest tercile of |B|): E = {Hayabusa2, EPOXI II, Stardust, MESSENGER, NEAR, Galileo II, Rosetta III}. The tercile rule admits flybys with |B| ≈ 1; the rule is recorded as registered and is not altered.

Post-hoc absolute threshold |B| ≤ 0.1 (labelled post-hoc) selects the flybys whose entry and exit sit at the same relative pressure depth:

| R_ref | equal-depth flybys (|B| ≤ 0.1) |
|---|---|
| 20 000 km | Hayabusa2 (B = 0.031) |
| 50 000 km | Hayabusa2 (0.021), EPOXI II (0.090) |
| 100 000 km | Hayabusa2 (0.019) |

- **Hayabusa2** (3090 km altitude, 2015-12-03) has cos ψ_in = −0.327, cos ψ_out = −0.347, R_☉ equal to 0.985702 and 0.985670 au at the endpoints, 4.08 h between endpoints. It is the one genuine equal-depth control with two distinct endpoints. The formula predicts **+0.29 mm/s**. No published Δv∞ exists in the census or in the literature search (JAXA reports a planned-versus-actual velocity offset of 43 cm/s, a trajectory offset, not an isolated anomaly). The control cannot be scored; the prediction stands registered as a prediction.
- **EPOXI II** has B = 0.090 at 50 000 km only because its closest approach (49 829 km) lies 0.35 % inside R_ref: the two endpoints are 0.52 h apart and nearly coincide, so B ≈ 0 is geometric. Even so P = +0.93 mm/s exceeds the 0.5 mm/s tolerance (fail). At 100 000 km, where the endpoints separate, B = 0.874 and P = +9.07 mm/s against an observed 0 (fail). EPOXI III never reaches R_ref (r_min = 1 336 721 km).
- The equal-depth class with a measured Δv∞ therefore contains no scoreable member. Flybys with entry/exit at equal depth are rare because the cosψ difference vanishes only for trajectories symmetric about the Sun–Earth axis.

## Predictions without a measured value (registered outputs, unscored)
Stardust +13.8, Hayabusa2 +0.29, OSIRIS-REx +33.9, Lucy I −22.5, Lucy II −51.6, JUICE +13.7 (observed 0.6, σ unpublished, ratio 0.044) mm/s. Published navigation accounts report no tens-of-mm/s anomalies for these; the census lists their Δv∞ as unknown, so the statement is not a measurement and is not used.

## Master Specification pass
- 2.1 arithmetic: executed by tool, logged verbatim; no value typed from memory. 2.2 dimensions: B dimensionless; v∞ km/s → m/s (×10³), K dimensionless, P in mm/s (×10³); R_ref, R_☉ in km, D in km.
- 3.2 excluded symbols: the Earth GM enters only as the measured combined parameter in the asymptote check (G1e); K_SDT is the burden ratio from GOM43. 3.4 tombstones: none used. 3.5: P `COMPUTED`; shared-geometry agreement is not counted as independent evidence in either direction.
- Gateway §3.8: no downgrade is based on agreement with a standard formula. The outcome rests on numbers: 4 of 4 anomalous and 9 of 9 null flybys outside tolerance; ρ = 0.375.
- Adversarial vantage points. Hostile reviewer: R_ref is a free choice → fixed before the run, sensitivity at two other radii and a second R_☉ definition reproduce the failure (G2 fails 4/4 and ρ ≤ 0.375 in every variant). Design-around engineer: K could be refit → refitting is outside the registration, and the post-hoc table shows no single scale exists. Competing architect: the formula omits altitude and tracking → the data (Juno vs NEAR at 561 vs 539 km) show the effect is not a function of altitude, and gap times are recorded in the register for the flybys where they exist.

## Open
- Tracking-gap and station-schedule data for Cassini, MESSENGER, Rosetta II/III and the 2007–2024 flybys remain outstanding (register §12). A model of Δv∞ as a function of tracking interruption has gap times for three flybys with measured values (NEAR 3 h 39 m → 13.46; Rosetta I 3 h 24 m → 1.80; Galileo I one-way near closest approach → 3.92) and one continuous case (Juno → 0), which is below the data needed to register a test.
- Published Δv∞ for Hayabusa2 would score the only genuine equal-depth control.
- Repair path for the formula: the post-hoc B_needed values (0.146, −0.173, 0.655, 0.155, ≈0 for nulls) are the targets any revised bracket must reproduce without refitting; a revision requires a new registration.
