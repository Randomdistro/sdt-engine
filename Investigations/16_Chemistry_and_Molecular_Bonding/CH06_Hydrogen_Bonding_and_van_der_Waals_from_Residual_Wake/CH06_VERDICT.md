# CH06 — VERDICT: Hydrogen Bonding & van der Waals from Residual Wake

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-05 · Tool: `ch06_residual_wake.cpp` (exit 1 — honest) · Output: `results.txt`

## Results (gates committed in RUN_LOG.md before the run; every exponent FITTED, never assumed)

| Phase | Result | Call |
|---|---|---|
| P1a static pair-pair exponent | fitted slope **−3.0037** over r/d ∈ [10,100] (gate −3.00±0.05) | **PASS** |
| P1b correlated-fluctuation exponent | fitted slope **−6.0225 / −6.0224** under ×10 changes of seat stiffness κ AND jitter scale T (gate −6.00±0.05, invariance required) — the London −6 **emerges as 2×(−3)**, second-order correlation of leaked rim residuals | **PASS** |
| P1c size trend | structural (ΔF monotone in residual size d); per-species ladder **DEFERRED** (no native per-atom residual sizes yet) | DEFER (declared) |
| P2 H-bond | exact 4-point sums, d = p/e from measured rim moments: **HF 20.35** (measured 19.1), **H₂O 12.40** (20.8, in 10–40 band), **NH₃ 6.01** (13.2, below band); O–H···O > N–H···N ✓; **linearity DERIVED** (attraction maximal at 0° tilt, monotone loss to 60°) | band + ordering + linearity **PASS**; magnitudes ~40% under for H₂O/NH₃, unfitted, reported |
| P4 novel ordering | 2/3 pairwise relations (NH₃-weakest ✓✓; **HF vs H₂O missed** — predicted HF>H₂O, measured dimers 19.1<20.8) | **FAIL** (gate 3/3, as pre-registered risk) |
| P3 water 4 °C | DEFER — needs the H-bond network run on CH04 geometry | DEFER (named debt) |

Earned: the **1/r⁶ exponent out of the machinery** (not assumed — the firewall's exact demand), with the jitter **amplitude** honestly left as the named OPEN closure (substrate influx fluctuation; the C₆ magnitude is not claimed). And one unfitted quantitative landing: HF at 6% with nothing tuned.

## FAILURE RECOVERY (§D seven questions — P4 HF/H₂O + the H₂O/NH₃ magnitude deficit)

1. Why: single-rim-pair sums under-count H₂O (12.4 vs 20.8) and NH₃ (6.0 vs 13.2) but land HF (20.3 vs 19.1). The pattern is exact: HF has ONE rim and one acceptor direction — the single-pair idealisation IS its geometry; H₂O/NH₃ carry multiple rims and lone directions whose contributions (secondary alignment, cooperativity) the single-pair model discards.
2. Recoverable: yes — by summing the full rim geometry (all O–H rims + lone-direction residuals of the acceptor), not by scaling amplitude.
3. Unaccounted: the acceptor's lone-pair residual direction and the second donor rim; both are CH04 outputs (the same wake directions the minimiser places).
4. Errored premise (named): **one residual pair per molecule.** The residual field of a multi-rim molecule is the vector sum of ALL uncancelled rims — the machinery exists (same point sums), only the per-molecule geometry was truncated.
5. Freedom: full-rim summation using CH04's computed directions + the measured moments already anchored.
6. Accounting: native — no new quantity is needed; it is a completeness fix inside the same machinery (a follow-up run, not a knob).
7. Cascade: partially independent — the truncation is CH06-local, but the magnitude of each rim residual traces to the same per-element rim geometry as CH04's misses (ROOT-RIM) at second order.

**Recovery grade: PARTIAL** — the route (full-rim sum on CH04 geometry) is concrete and native; not yet executed. Re-open condition: CH06b run with multi-rim geometry; prediction registered now: H₂O and NH₃ move UP toward band centre, HF stays ≈ fixed — if instead HF inflates, the rim model is wrong. P3 water anomaly re-opens on the same run.

## Cascade root (reported)

**ROOT-RIM (secondary):** the per-element rim/residual geometry (shared with CH04/CH05). **OPEN-JITTER:** dispersion amplitude = substrate influx fluctuation spectrum — new named closure, owner FLM09/FLM14 class (the reconfiguration-noise side of the lattice).

## Canonical line

**Prompt completion C (P1 exponents earned + P2 band/ordering/linearity; P4 2/3; P3 deferred) · Physics class CONVERGENCE (the sums survive the delete-test as classical residual electrostatics; SDT supplies the rim reading and the jitter ontology, whose amplitude stays OPEN) · Recovery PARTIAL · Cascade root ROOT-RIM + OPEN-JITTER**
