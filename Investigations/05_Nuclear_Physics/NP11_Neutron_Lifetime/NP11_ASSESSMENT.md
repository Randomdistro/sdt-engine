# NP11 Assessment — neutron lifetime from lattice topology

**Date:** 2026-10-03<br>
**Direct execution.** **Canon edits:** none<br>
**Instrument:** `np11_neutron_lifetime.cpp`<br>
**Stdout:** `np11_results.txt`<br>
**Pre-registration:** `PROMPT.md`, section "Pre-registration (2026-10-03)"; run record `RUN_LOG.md`

## Status

`NP11_BARRIER_DEPTH_OPEN__ROUTE_C_PREMISE_UPDATED`

- τ ~ e^B is not derived: B is back-solved from τ and the attempt frequency that sets its value is not supplied. The ambiguity this leaves is quantified.
- A census of 112 natural constructions finds no result distinguishable from chance.
- The beam/bottle premise of Route C has changed with the J-PARC beam result, and the wall-coupling explanation is disfavoured at 2.4σ, not excluded.

## Attempt ledger

| Part | Route | Outcome |
|---|---|---|
| C | Beam/bottle data audit and the wall-coupling reading | Wall coupling alone disfavoured (2.36σ between beam-type results) |
| A1 | B_req over seven engine clocks | Spread 7.5 nats across the nuclear-scale clocks; 644 times the beam–bottle difference in B |
| A2 | Census, B = k ln X (112 constructions, 7 clocks) | 6 hits against 6.78 expected (P = 0.64); none distinguishable |
| A3 | Law V per-tick survival, τ = t·γ₀^N, integer N | No hit (0.22 expected); required N on R_p/c is 65.70 |
| B | Shared seat sets the rate | Not derived; γ₀ and v_phase/c entered the census only |
| 4 | Not run | Candidates listed below |

## Instrument validation

Three known-answer checks passed before any part was run: weighted-mean and difference
arithmetic on a hand-computed case; ħ/(m_ec²) = 1.2881e-21 s and R_p/c = 2.8066e-24 s from
engine constants; and the census null model against its analytic expectation (3.157 against
3.160 expected hits).

## Part C — beam/bottle

| Quantity | Value |
|---|---|
| bottle | 877.8 ± 0.3 s |
| earlier beams | 888.1 ± 2.0 s |
| J-PARC beam (2024) | 877.2 s, σ = 4.16 s (stat 1.7, symmetrised syst 3.8) |
| all beams combined | 886.1 ± 1.8 s |

| Difference | s | in σ |
|---|---:|---:|
| earlier beams − bottle | +10.3 ± 2.0 | +5.09 |
| J-PARC − bottle | −0.6 ± 4.2 | −0.14 |
| J-PARC − earlier beams | −10.9 ± 4.6 | −2.36 |
| all beams − bottle | +8.3 ± 1.8 | +4.52 |

Route C says free-flight beams measure the free-space rate and bottles a wall-modified one, so
beam-type results should agree with each other. They disagree by 2.36σ, which meets the
registered criterion (more than 2σ) and falls short of the 3σ needed to exclude. The reading
"the wall coupling alone explains the beam–bottle difference" is disfavoured, not excluded.
The J-PARC value also bounds a wall effect directly: J-PARC − bottle is −0.6 ± 4.2 s, a
free-flight/wall difference of −0.07% ± 0.5%, against the 1.2% (10.3 s) that Route C needs.

The seed's sign statement ("bottle faster, wall coupling raises the rate") was written with
888 against 878 in view. It is a retrodiction. It stays on record as such and it did not carry
predictive weight.

**What this changes.** If later beams converge toward 877 s, the premise of Route C (an
anomaly to explain) dissolves and the SDT claim of a boundary-dependent rate has no support at
the 1% level. If the earlier beams are right and J-PARC is a fluctuation, Route C remains
alive and the discriminating comparison becomes bottles of different wall material and a
wall-free magnetic trap. That dataset (lifetimes by trap type) was not retrieved and is
what the next test needs.

## Part A1 — what the clock choice does to B

τ = 877.8 s over the engine clocks:

| Clock | t (s) | B_req |
|---|---:|---:|
| R_p/c | 2.807e-24 | 61.007 |
| 2πR_p / v_seat (seat rotation period, 1.830c) | 9.636e-24 | 59.774 |
| ħ/(m_pc²) | 7.015e-25 | 62.394 |
| ħ/(m_ec²) | 1.288e-21 | 54.879 |
| r_e/c | 9.400e-24 | 59.799 |
| ℓ_P/c | 5.391e-44 | 106.406 |
| Bohr period 2πa₀/(αc) | 1.520e-16 | 43.200 |

The five nuclear-scale clocks span 7.5 nats, a factor 1800 in τ. The beam–bottle difference is
0.0117 nats, 644 times smaller. Two consequences:
1. "B ≈ 61" is a statement about the clock chosen. A derived B needs a derived attempt
   frequency (the seat's release rate), and the prefactor ambiguity is larger than any
   structure a geometric B could carry.
2. A barrier picture cannot be what the beam–bottle difference tests. A 1.2% change in rate is
   a 0.019% change in B = 61. Route C, if it is real, is a rate modulation by a separate
   mechanism, not a shift in the barrier depth.

Of the seven clocks, the seat rotation period and r_e/c give B within 0.03 nats of each other
(59.774 and 59.799), because 2πR_p/1.830 and r_e differ by 2.5%. That is a near-coincidence in the
engine's own scales and is recorded without interpretation.

## Parts A2 and A3 — the census

Grammar (registered before running): B_c = k·ln X for k = 1…16 and X in {1/α, m_p/m_e, 4π, 2π,
π, γ₀, v_phase/c}, with γ₀ = (m_n − m_p)/m_e = 2.53099 (the electron's Lorentz factor at the
Q_β seat). A hit is within 1.5% of B_req.

| Clock | Hits | Null mean | P(null ≥ observed) |
|---|---|---:|---:|
| R_p/c | 8 ln(m_p/m_e) = 60.12 (−1.45%) | 1.34 | 0.78 |
| seat period | 12 ln(1/α) (−1.22%), 8 ln(m_p/m_e) (+0.58%) | 1.32 | 0.39 |
| ħ/(m_pc²) | none | 1.37 | 1.00 |
| ħ/(m_ec²) | 11 ln(1/α) (−1.38%) | 1.43 | 0.80 |
| r_e/c | 12 ln(1/α) (−1.26%), 8 ln(m_p/m_e) (+0.54%) | 1.32 | 0.39 |

Together the five nuclear-scale clocks give 6 hits against a null mean of 6.78 (P = 0.64). No
per-clock probability is below 0.05, so the registered criterion for distinguishability is not
met. The construction 8 ln(m_p/m_e) reaches three clocks, but those clocks are tied to the same
nuclear length scale and the shared hit is what the null predicts at this window size.

The window is generous. 1.5% of B is 0.9 nats, a factor 2.5 in τ. At that resolution a hit
means very little. The nearest construction to each clock implies lifetimes between 0.3 and
4.8 times the measured value (R_p/c: 8 ln(m_p/m_e) gives 363 s; the seat clock gives 1245 s).
The best |ΔB| over all clocks is 0.325 nats, 28 times the beam–bottle difference in B, so at
the resolution the data support no construction in this grammar comes close.

**Part A3.** With the per-tick survival q = 1/γ₀ = 0.3951 (the Law V budget ratio at the seat
release speed), τ = t·γ₀^N has no integer N within ±1.5% of 877.8 s for any clock (0.22 hits
expected by chance). On R_p/c the required N is 65.698: 65 gives 455 s and 66 gives 1162 s.

## Failure analysis and alternatives

What fails and why. The barrier picture predicts a form (τ ~ t e^B) and has one measured
number to place into it. Every attempt to place B from a natural construction runs into the
same limit: with 7 clocks, 7 constants and 16 multiples, near-matches at the 1% level in B are
expected by chance, and 1% in B is a factor 2.5 in τ. The census converts that statement
into numbers: observed hits equal the chance rate.

Alternatives considered, each with what it would have to deliver:
- **Mechanism first, then number.** Derive the release rate from the FLM14 rotating-spation
  residence dynamics. Its attempt clock is the seat rotation period (9.64e-24 s), for which
  B_req = 59.77 ± 0.01 is then a sharp target with no clock freedom. This is the route that
  removes the ambiguity of A1 and is the natural Round 4.
- **Non-integer N from a geometric count.** Law V survival per tick needs N = 65.70 ticks on
  R_p/c (64.4 on the seat clock). A mechanism that fixes N from geometry (a count of lobe
  crossings or lock-in steps) can be tested at once; a grammar search for N is subject to the
  same census discipline and gains nothing from a tolerance wider than the measured 1%.
- **Probability reading.** e^−B is a per-tick release probability, 1.1e-26 on the seat clock.
  If it is a ratio of volumes or solid angles of the seat geometry, it is a product of
  dimensionless ratios already in the engine; that is again a census, and must be written down
  with its trial count before it is run.
- **Route C as a separate mechanism.** The 1.2% rate difference is not a barrier effect (A1).
  A bottle-wall coupling would be an additive rate term, Γ_wall/Γ ≈ 1.2% in bottles of a given
  geometry. Its testable consequence is a dependence on wall material and surface-to-volume
  ratio, which the existing bottle data can address once collected.

## Limitations

1. All lifetimes are transcribed from secondary summaries; the primary papers were not
   retrieved. The J-PARC systematic is asymmetric (+4.0/−3.6 s) and is symmetrised here.
2. The "earlier beams" value is an average of few experiments; its error bar does not carry
   the model dependence of the proton-counting efficiency that is the leading beam systematic.
3. Parts A2 and A3 are censuses over a grammar fixed in advance. A different grammar changes
   the counts. The result is a statement about this grammar and this tolerance.
4. T4 (products as topology) and T5 (no imported thermal barrier) have no numerical test here.
5. The shared-seat route (seed Part B) is not derived; γ₀ and v_phase/c enter only as inputs
   to the census.

## Open

- A derived release rate (attempt frequency and barrier) for the internal-electron seat. This is
  the deep open of the seed and the one result that would settle Route A.
- Lifetimes by trap type and wall material, with primary sources, into `Datasets/`.
- Primary J-PARC and beam papers to replace the secondary transcription.
