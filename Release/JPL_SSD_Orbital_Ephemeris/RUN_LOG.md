# Horizons Kinematics Demonstration Run Log

## Run 1 — 2026-08-15

Environment: Windows, MSVC 19.44, C++20, Release configuration.

The first synthetic O1 run failed the registered `1e-8` koppa gate with relative
error `1.4464e-5`. The cause was the test fixture, not the estimator: sub-second
synthetic intervals were added to a Julian-date offset of 2,450,000 days, losing
time precision before centred differencing. The repair removed the irrelevant
large epoch offset from the synthetic known-answer fixture. No formula, input
data, gate or threshold changed.

Repair rerun:

- canonical T17 period and acceleration bridges: PASS;
- synthetic koppa relative error: `7.31085e-9` — PASS;
- one-period position closure: `2.06709e-7` of radius — PASS;
- DE441 parser/metadata: 397 rows, Earth (399), Sun (10), KM-S — PASS;
- median koppa: `1483.389092157908 m`;
- relative koppa MAD: `0.0006429688` — PASS;
- maximum position residual: `1237.233332 km` — PASS;
- maximum velocity residual: `0.0056353204 km/s` — PASS;
- output completeness and JSON provenance: PASS;
- CTest: 2/2 passed;
- installed executable self-test: PASS.

The repository benchmark suite was rebuilt against the added canonical bridge
helpers and returned 66/66 earned predictions passed, 19/19 identities passed.

