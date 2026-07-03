# GOM09 — Verdict: Earth Core Seismic Speed

**Classification: PARTIAL — g(r) 1.82% RMS; the named seismic-velocity target FAILS its own gate (v_p RMS 11.5%, v_s 28.0% per RESULTS.md; rebuilt run 6.24%/6.69%).**
**Author**: James Christopher Tyndall, Melbourne · Tool: `gom09_seismic.cpp`.

## Deciding metric

Seismic P-wave speeds through PREM density profile derived from SDT k-gradient and phase moduli — **no G, no M**. [the 1.82% is the g(r) metric, not this deciding metric — metric-swap corrected]

## Key checks (from run)

- ICB pressure within 5% of 329 GPa — **PASS**
- Centre v_p within 10% — **PASS**
- K′₀ = 4 derived from traction τ = 1/3 (not fitted Birch–Murnaghan)

## Class

**Class C (CONVERGENCE with seismology)** — PREM density is measured input; SDT derives g(r), P(r), K(P), v_p, v_s from k_Earth and phase G₀/K₀.

**Sign-off: PARTIAL (g-metric PASS; seismic gate FAIL).**
