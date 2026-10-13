# NP32 prediction-eligibility and data-reproducibility audit — pre-registration

**Status:** FROZEN BEFORE THIS AUDIT PARSES ANY FISSION-YIELD CSV
**Date:** 2026-08-09
**Scope:** Determine whether NP32 supplies an executable, zero-fit SDT predictor for cross-fissioner mass-yield peaks, and separately reproduce the documented observational summaries if source integrity passes.

## Question and initial conditions

The admissible input is a fissile system and its stated incident-energy class.  A genuine forward SDT test must transform those inputs into a selected split (or a distribution over splits) **before** using the corresponding measured fission-yield distribution.  Its selection rule must be native quantities with definitions, units or dimensionless normalization, an objective/cost, tie-breaking, and an executable minimization procedure.  Its output must then be compared with independent IAEA yield data.

This is not a comparison with a shell-model or other standard-model predictor.  It asks only whether the claimed SDT mechanism itself has been specified and executed.  Agreement of an empirically imported `N=82`/`Z=50` location with IAEA peaks neither falsifies nor validates the proposed mechanism unless the location follows from a frozen SDT computation.

## Frozen evidence inventory

### Theory and historical-result artifacts (static audit inputs)

| Path | Role | Required handling |
|---|---|---|
| `PROMPT.md` | stated mechanism and deliverables | hash before conclusion |
| `NP32_PREDICT_PRECOMMIT_2026-07-25.md` | precommitted claims and gates | hash before conclusion |
| `np32_predict_check.py` | only claimed computation | hash and statically inventory functions/imports before execution |
| `NP32_PREDICT_RESULTS_2026-07-25.md` | historical claimed outcome | hash; use only for replication comparison |

### Observational inputs (do not parse before integrity gate)

The manifest at `Datasets/MANIFEST.md` preregisters the listed provenance, byte counts, and shown SHA-256 prefixes.  The audit will require exact byte-count equality and that each computed SHA-256 begins with the registered prefix.  No data value is allowed to repair a hash, substitute a reaction class, choose a window, or revise a gate.

| Dataset | Energy column | Expected bytes | Expected SHA-256 prefix |
|---|---:|---:|---|
| `Datasets/nuclear/IAEA_U235_independent_FY.csv` | thermal | 121193 | `87fcd49503a5` |
| `Datasets/nuclear/fission_yields/IAEA_233U_independent_FY.csv` | thermal | 128347 | `878e4e6c1f39` |
| `Datasets/nuclear/fission_yields/IAEA_239Pu_independent_FY.csv` | thermal | 98073 | `8e9272960f54` |
| `Datasets/nuclear/fission_yields/IAEA_241Pu_independent_FY.csv` | thermal | 93869 | `52bbb5be8087` |
| `Datasets/nuclear/fission_yields/IAEA_237Np_independent_FY.csv` | fast | 88035 | `a14c5e3540fe` |
| `Datasets/nuclear/fission_yields/IAEA_241Am_independent_FY.csv` | fast | 100715 | `a75a4ecd5109` |
| `Datasets/nuclear/fission_yields/IAEA_238U_independent_FY.csv` | fast | 90478 | `e602f666aeb3` |
| `Datasets/nuclear/fission_yields/IAEA_232Th_independent_FY.csv` | fast | 85712 | `6641d35d4f2c` |

The raw observational source is described in that manifest as IAEA Nuclear Data Services LiveChart `independent_fy` data.  The audit will make no claim about the evaluation's physics beyond treating the supplied tables as the independent-yield observations that NP32 selected.

## Frozen reconstruction procedure

1. Hash and byte-count every static and observational input.  If any observational input fails its source gate, stop as `PROVENANCE_BLOCKED`; do not parse or calculate yield statistics.
2. Statistically audit the sole computation source.  Inventory its imports, declared functions, and execution path.  Test whether it implements: (a) a parent-to-contact graph, (b) a native edge/bond/cost rule, (c) a minimization or cut over candidate fragment partitions, and (d) a forward split/distribution emitted before any yield table is opened.
3. Identify any numerical fragment anchor or shell-lock location supplied outside such a computation.  A statement that a location was “measured this session” counts as empirically imported unless a frozen, independently auditable derivation and underlying measurement record are present in the declared input inventory.
4. Only after all source gates pass, independently reproduce the script's explicitly documented data reduction: sum the selected `independent_{energy}_fy` by daughter mass; choose the maximum in the fixed lower and upper search windows split at `A_fiss/2`; compute each centroid in the fixed mode ±8 window; calculate `nu_bc = A_fiss - (A_L + A_H)`, linear slopes, and the stated P4 valley and peak-to-valley checks.  No fitting, exponent scan, coefficient adjustment, data exclusion, reaction-class substitution, or standard-model comparator is permitted.
5. Apply the published gates literally:
   - P1: heavy-centroid slope `< 0.25`.
   - P2: light-centroid slope in `[0.7, 1.3]`.
   - P3: **every** `nu_bc` in `[1.5, 4.0]`.
   - P4: Th-232 has both the shallowest fast-set valley (largest stated valley statistic) and the lowest fast-set peak-to-valley ratio.

## Decision protocol

| Condition | Required classification |
|---|---|
| A raw-source integrity gate fails | `PROVENANCE_BLOCKED` |
| Any of 2(a)–2(d) is absent | `MINIMUM_CUT_MECHANISM_UNIMPLEMENTED` |
| The heavy-fragment lock location is not derived by a frozen native computation | `ANCHOR_EMPIRICALLY_IMPORTED` |
| Observational regularities reproduce but either mechanism condition above holds | `DATA_REGULARITY_REPRODUCED_NOT_SDT_PREDICTION`; empirical SDT verdict `UNADJUDICATED` |
| A published numerical gate is violated | record the historical claim as false under its own precommit; do not use a post hoc relaxation |
| All mechanism and source conditions pass | only then issue a forward-prediction adjudication |

## Error controls and correction path

- A static absence result is limited to the audited `np32_predict_check.py`; it does not prove that no SDT mechanism could ever be written.
- A yield-table reproduction is an observational-data audit, not a derivation of the observed peaks and not evidence for a competing framework.
- If the source audit finds a separate executable, preregistered native derivation elsewhere in the repository, halt this audit's mechanistic conclusion, add that file to a new frozen inventory with hashes, and rerun as a new branch.  It must be available without using the target yield values.
- Any mismatch between this reconstruction and the historical result must be traced to code, source identity, reaction column, statistic definition, or arithmetic; the result must be corrected rather than averaged or rationalized.
- Canonical law files remain read-only.  A repaired predictor must be proposed and independently preregistered before accessing held-out yield data.
