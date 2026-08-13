# NP30 triton-contraction root audit — pre-registration

**Status:** FROZEN BEFORE THIS AUDIT PARSES ANY RADIUS CSV
**Date:** 2026-08-09
**Purpose:** Audit the claimed empirical root for NP32's interleave-lock anchor: whether isotope-radius observations establish a triton-contraction mechanism, a closure-maximal effect, or only a descriptive regularity.

## Initial conditions and claim separation

NP30 §11 claims that, in a radius table, the radius rises slower than `A^(1/3)` in one-neutron steps, that a residual is more negative at stated shell closures, and that closure tightness accumulates toward the close-pack floor.  NP32 subsequently treats this as the origin of an N=82/Z=50 lock.  These are distinct propositions:

1. **Observation:** adjacent isotopes display a reproducible trend in the reduced radius `r0 = R / A^(1/3)`.
2. **Classification:** the strength of the trend differs in steps ending at a pre-specified set of closure labels.
3. **Mechanism:** a defined SDT interleave/triton construction predicts both the trend and the closure locations without importing those locations.

This audit can use evaluated experimental/observational radius values only for propositions 1 and 2.  It must not call a closure list a derived SDT output merely because the same list organizes the observations.  No standard-model prediction, fitted coefficient, or external radius law may set the verdict.

## Frozen source inventory

| Source | Required handling |
|---|---|
| `Datasets/nuclear/IAEA_ground_states_radii.csv` | primary observational target; hash and byte-count before parse |
| `Datasets/nuclear/radii_compact.csv` | historical compact target if used by the recorded method; hash and byte-count before parse |
| `Datasets/MANIFEST.md` | source provenance and observable description |
| `NP30_INTERLEAVED_TREFOIL_COMPLETE.md` | claim, numerical statements, and limitations |
| `ATOMICUS/reference/BOUNDARY_RADIUS_TRITON_CONTRACTION.md` | stated data-reduction method and labels |
| `ATOMICUS/tools/enrich_boundary_radius.py` | executable provenance, if it supplies the reported table or statistic |
| `ATOMICUS/reference/CLOSURE_KINK_ISOTONE_INVARIANT.md` | closure interpretation, if cited |
| `NP32_PREDICT_PRECOMMIT_2026-07-25.md` | downstream use of the alleged anchor |

If an observational input hash fails, stop as `PROVENANCE_BLOCKED` before numeric parsing.  If the recorded NP30 material does not supply an executable reduction from frozen inputs to the stated `−6`, `−10`, `−17`, or `−25 mfm` quantities, classify those numbers as `UNREPRODUCED_HISTORICAL_SUMMARY` unless this audit independently reconstructs an explicitly defined statistic.

## Frozen reconstruction

1. Hash and byte-count every source; freeze full identities before observation parsing.
2. Inspect static artifacts for the definition of `n_t`, `n_d`, reduced radius, closure criterion, sample restriction, uncertainty treatment, and any script that creates the claimed result.
3. After all identity gates pass, parse the IAEA table using only rows with integer `Z >= 1`, integer `N >= 0`, finite `radius > 0.1 fm`.  Form same-element adjacent-neutron pairs `(Z,N) -> (Z,N+1)`.
4. For each pair, calculate the observational reduced-radius step

```text
delta_r0 = R(Z,N+1)/(Z+N+1)^(1/3) - R(Z,N)/(Z+N)^(1/3).
```

Report the number and fraction of negative steps, plus median and mean `delta_r0` in milli-fm for all pairs, `A_endpoint >= 40`, `120 <= A_endpoint <= 140`, and endpoints at the frozen historical labels `N in {20,28,50,82,126}`.  A closure label is an empirical classification input here, not an SDT output.
5. If the recorded method defines `n_t` and a separate residual, reproduce it exactly as a descriptive check; otherwise do not invent one.  No refit, choice of a different radius convention, post hoc subset selection, or relaxation of a claimed error bound is allowed.

## Decision protocol

| Condition | Required conclusion |
|---|---|
| Any observational identity gate fails | `PROVENANCE_BLOCKED` |
| Direct pair statistic contradicts the stated sign/range under a defined historical method | `HISTORICAL_CONTRACTION_STATEMENT_FALSE_OR_METHOD_UNSPECIFIED` |
| Pair regularity reproduces but source material has no pre-data prediction or executable native mechanism | `OBSERVATIONAL_REGULARITY_REPRODUCED_MECHANISM_UNADJUDICATED` |
| Closure list is inserted rather than computed from frozen SDT primitives | `CLOSURE_LOCATION_EMPIRICALLY_IMPORTED` |
| A complete native mechanism predicts trend and labels before observations | eligible for a separate held-out physical adjudication |

## Scope and correction path

- A reduced-radius trend is not by itself evidence for an interleave lock, a fission cut, or the origin of N=82/Z=50.
- The direct radius table is an RMS charge-radius observable in the cached provenance.  This audit reports its trend as an observational summary and does not relabel it into an unmeasured boundary without a derived map.
- Any repair must first define the triton/deuteron inventory, the geometric radius observable, the closure rule, units, and uncertainty model.  It must pre-register a held-out isotope set before reading that set.
- Canonical source files are read-only.  No coefficient or closure number may be adjusted in response to this audit.
