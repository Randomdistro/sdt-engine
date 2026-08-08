# GOM40 Assessment - Local-K Amplitude Robustness Rerun

**Date:** 2026-08-09
**Status:** `LOCAL_K_REPAIR_DOES_NOT_CLEAR_GOM37_GATES`.
**Empirical SDT verdict:** `UNADJUDICATED`.
**Instrument:** `gom40_local_k_amplitude_robustness.py`
(`a05e02620eb5a4bd467773ef756e3e2b2916f4591a1247824ec4edad8fa8e3f3`).
**Result:** `gom40_results.json`
(`eca0aed034a92f72db48ef236b813a2d46594b8f7f8aeb605dc4808767ff88ce`).

## Question tested

GOM39 repaired the `k`/`K` grammar. GOM37 had used `K = 1476.350 m` and failed
its multi-day Cassini amplitude and delete-test gates. This rerun asks only
whether the fixed GOM39 Earth-proxy value `K = 1455.637 m` repairs those gates.
It does not fit either value, alter the residual construction, or treat a
successful rerun as theory confirmation.

All thirteen registered input hashes passed before numeric parsing. No source was
downloaded. The four Cassini ODFs are primary tracking bytes; the range-rate and
heliocentric inputs are frozen processed geometry, so this loop cannot issue an
unqualified physical verdict even if its statistical gates had changed.

## Recalculation

| Registered case | K (m) | Median abs proxy (Hz) | Amplitude ratio | Corr(residual, delay-rate) | Corr(residual, time) | Gates |
|---|---:|---:|---:|---:|---:|---|
| GOM37 frozen | 1476.350 | 0.03845514 | 7,074,106.90 | -0.991678 | -0.995510 | amplitude fail; time-confounded |
| GOM39 local Earth proxy | 1455.637 | 0.03791562 | 7,174,767.97 | -0.991678 | -0.995510 | amplitude fail; time-confounded |

The baseline exactly reproduces the GOM37 sample counts (125 training and 1,235
test samples), residual standard deviation (272,035.77 Hz), scale, trend, and
gate status. The local-K value is 1.402987% smaller, so its proxy is smaller by
the exact same factor and the amplitude ratio grows by 1.422951%. Both
correlations are invariant under the positive scalar change, as required by
the registered delay formula.

To reach the registered amplitude limit of 100 with this unchanged residual
would require `K = 104,438,577.25 m`, or 70,741.07 times the original frozen
value. The GOM39 correction is a small decrease, not such a recovery.

## Narrow falsification result

The proposition that replacing GOM37's naked frozen `K` by the GOM39 local-K
Earth proxy alone can rescue its Cassini amplitude or time-confound gates is
falsified within this fixed pipeline. This does **not** exclude SDT: the ODF
scale/intermediate-frequency definition and the processed geometry remain
unresolved, and no rival-framework computation was used as a criterion.

## Error audit and repair

Before execution, code review caught an instrument discrepancy: the first draft
subsampled every sixtieth raw record, whereas GOM37 first filters type-12,
RX-25 records and then subsamples every sixtieth selected row. The draft was
corrected before any numeric run; syntax compilation passed, and the baseline
reproduced GOM37. No output from the incorrect sampling path was retained.

## Next gate

Do not retune `K` or add ad hoc terms to this residual. Resolve the producer
applicable ODF scale, intermediate-frequency, ramp, and media definitions, or
obtain an independently calibrated delay/range observable. Re-run only with a
new pre-registration and frozen inputs; until then the Doppler physical claim
remains `UNADJUDICATED`.
