# GOM07 · RUN LOG (append-only)

Investigation: Reflected-Light Gravitational Redshift Test (Venus vs Jupiter). J.C. Harvey, SDT Depth-Closure.

---

## RUN 1 — PART A (theory) + the SEALED prediction (predict-before-look)

### Part A verdict — does an SDT reflection re-stamp the local depth?
**YES (declared).** By Depth-Closure (z stamped at the *last* emission/interaction) a scatter at the cloud-top
re-radiates the photon from depth `z = ϟ_planet/R_cloud`; there is no continuous-climb to cancel (SDT puts the
shift at the interaction, not along the path). → SDT predicts reflected solar lines carry the reflector's
cloud-top depth. **Hinge flagged:** if elastic scatter does NOT re-stamp, SDT = GR (flat) and the test is not
decisive — to be reported as such, never as a win. CR06/GOM05 do not currently settle this; declared here.

### SEALED PREDICTION (committed BEFORE any spectrum is read) — `cq51_reflection_redshift.py`
**[RUN 1b — GM-free recompute.** First pass wrote `koppa = GM/c²` — an illegal input (G and M are
forbidden; flagged and corrected). Recomputed from the SDT primitives only: `v_surf` (surface circulation
velocity) and `R`. `z = (v_surf/c)²` is the spectral λ→λ shift; `k = c/v_surf`; **seat `z·k² = 1` verified
to five figures for every body.** `koppa = v_surf²·R/c²` and `g = v_surf²/R` are derived, never input. All
sealed numbers below are unchanged — only the provenance is now clean.**]

Solar baseline (Sun surface → 1 AU, from `v_surf,Sun = 436.76 km/s`): **z·c = 633.35 m/s**
(cf. HARPS-LFC Moon 638±6; GR 633.1).

```
body      z_body*c     GR pred      SDT pred (633.35 + z_body*c)
Moon       0.0094 m/s   633.35       633.36      <- passive-mirror baseline / control
Mars       0.0421       633.35       633.39
Venus      0.179        633.35       633.53
Saturn     2.173        633.35       635.52
Jupiter    6.045        633.35       639.40      <- decisive signal
```
**Jupiter − Moon = 6.04 m/s (SDT) vs 0 (GR).** GATE: regress (residual − 633) vs z_body·c → slope 0 (GR) or
1 (SDT); decisive if Jupiter exceeds Moon by > 3σ.

### SEALED PREDICTION 2 — the WITHIN-JUPITER (Galilean-moon) gradient — DATA EXISTS TODAY
A Galilean moon reflects sunlight from depth `z = ϟ_J/r` inside Jupiter's well (its own surface well ≈0.01 m/s,
negligible). SDT → reflected solar lines fall with distance from Jupiter; GR → flat (zero) for all four.

```
moon       r_from_Jupiter (m)   z=koppa_J/r   SDT extra (m/s)
Io          4.217e8             4.74e-9       +1.002
Europa      6.711e8             2.98e-9       +0.630
Ganymede    1.070e9             1.87e-9       +0.395
Callisto    1.883e9             1.06e-9       +0.224
```

**Io − Callisto = 0.778 m/s** · **Europa − Ganymede = 0.235 m/s.** Both are sealed before any reanalysis.
**HARPS reflected-sunlight spectra of Europa AND Ganymede already exist** (per-exposure rms 0.83 m/s;
arXiv:1601.05646) — they were taken to measure the *Sun's* RV, never differenced moon-to-moon. Reanalysed for
the Europa−Ganymede solar-line offset, SDT predicts 0.24 m/s; GR predicts 0. (Io−Callisto 0.78 m/s is the
larger lever if those spectra can be obtained.) This is the test that needs **no new telescope time**.

## RUN 2 — PART B against REAL measured data (Lanza et al. 2016)

Found published data that already contains the signal: **Lanza et al. 2016 (A&A 587, A103;
arXiv:1601.05646)** measured the Sun's RV off the Moon + asteroids + Galilean satellites on one common
HARPS scale, applying **no host-well correction** (Jupiter's potential on the Galileans never removed).
Reduced their Table 2 with `cq51_partB_lanza2016.py` (regress measured RV vs SDT Jupiter-well extra).

**[CORRECTION 2026-06-20 — predictions had been SWAPPED.** SDT = redshift encoded at emission and stable
→ reflector silent → **flat 633 → slope 0**. GR = light fights gravity all the way out → reflected beam
climbing out of the planet's well adds `z·c` → **slope 1**. The earlier draft wrongly invented an SDT
"re-stamp" and put the differential on SDT. Removed; gate re-labelled. *(Caveat: rigorous cancellation-GR
also → slope 0, degenerate with SDT for reflection.)*]**

**RESULT — slope = −1.11 ± 1.28** (SDT flat = 0, GR climb = 1): **0.9σ from SDT, 1.6σ from GR.** Central
value negative (no positive trend with Jupiter depth). Europa−Ganymede = +2.25 ± 1.04 (sign matches
GR-climb but 10× the predicted 0.23 → systematic). Io (deepest, +1.0) is the *lowest* (albedo artifact,
authors-excluded), contradicting GR-climb. **Systematic floor:** the 4 zero-well bodies scatter 1.46 m/s —
~3× the 0.5 m/s signal.

**VERDICT (see `CQ51_VERDICT.md`): CONSISTENT WITH SDT (flat); GR gradual-climb DISFAVOURED, not killed.**
The reflector's well does not show up — exactly as SDT's emission-stamp requires. Floor-limited (~1.5 m/s,
3× the signal) so not decisive, and degenerate with cancellation-GR. The clean SDT-vs-GR separation is the
observer-position test (Parker Solar Probe vs Earth), not reflection.

## RUN 1 — STATUS
- Part A (theory / re-stamp hinge): ✔ declared (SDT predicts the differential; degeneracy caveat logged).
- Sealed prediction table: ✔ committed (this log) before any data.
- Part B (data): ✔ DONE against Lanza 2016 — **null/inconclusive, floor-limited** (RUN 2 above).
- Remaining: Jupiter disk-direct ESPRESSO program (the 6 m/s test that beats the systematic floor).
