# Redshift Bookkeeping Demonstration Run Log

## Run 1 — 2026-08-15

Environment: Windows, MSVC 19.44, C++20, Release configuration.

The rebuilt instrument was run only on the pre-registered synthetic fixture.
No observational H0 target or astronomical catalogue entered the run.

Results:

- malformed binary-flag rejection: PASS;
- four low-z known-answer rows recovered synthetic
  `H0 = 70 km/s/Mpc`, maximum numerical error below `1e-12`: PASS;
- every component exercised an already-applied state and was not subtracted
  twice: PASS;
- positive and negative correction sensitivities preserved sign: PASS;
- one `z=0.2` row was withheld from the low-z linear diagnostic: PASS;
- CSV row completeness: 5/5 — PASS;
- JSON provenance includes `scientific_result=false` and
  `external_target_h0=null`: PASS;
- CTest: 2/2 passed;
- installed executable self-test: PASS.

The withdrawn CQ18d/e/f programs were not compiled or executed.

